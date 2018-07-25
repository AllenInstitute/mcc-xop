/**
 * @file MultiClamp700xCommander_Operations.cpp
 * Code that provides external operations to Igor for communicating
 * with MultiClamp Commander.

	Copyright 2017 WaveMetrics, Inc.

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software
	and associated documentation files (the "Software"), to deal in the Software without restriction,
	including without limitation the rights to use, copy, modify, merge, publish, distribute,
	sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
	is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MultiClamp700xCommander_Operations.h"
#include "MultiClamp700xCommander.h"
#include <vector>

extern UINT gExecuting;		// Flag variable that reflects whether the XOP is in the middle of executing and used to prevent recursion.

// In TelegraphServer.h.  This value for ComPortID and AxoBusID indicates
// that the server is a 700B server.  Otherwise it is a 700A server.
extern const UINT VALUE_INVALID;


// Operation template: MCC_FindServers /TOUT=number:timeoutMs /Z[=number:errorType]
int ExecuteMCC_FindServers(MCC_FindServersRuntimeParamsPtr p) {
	int err = 0;
	int errorType = defaultErrorType;
	int mccError = MCCMSG_ERROR_NOERROR;

	if (p == NULL) {
		err = SYNERR;
		goto done;
	}
	if (p->ZFlagEncountered) {
		// Default errorType if /Z flag is present is AXON_TELEGRAPH_ERROR_IGNORE.
		errorType = MCC_ERROR_IGNORE;
		if (p->ZFlagParamsSet[0]) {
			// Optional parameter: p->errorType
			errorType = (int)Process_Z_FlagValue(p->errorType);
		}
	}

	if (gExecuting) {
		err = XOP_RECURSION_ATTEMPTED;
		// NOTE:  We don't goto done: here because
		// doing so would reset gExecuting, which
		// is not what we want.
		if (errorType == MCC_ERROR_YES) {
			// Only create a run time error if /Z flag not set or set to 0.
			return err;
		}
		else {
			return 0;
		}
	}
	gExecuting = TRUE;

	HMCCMSG hMCCmsg = GetMCCDLLHandle();
	if (hMCCmsg != NULL) {
		char szSerialNum[16] = ""; // Serial number of MultiClamp 700B
		UINT uModel = 0; // Identifies MultiClamp 700A or 700B model
		UINT uCOMPortID = 0; // COM port ID of MultiClamp 700A (1-16)
		UINT uDeviceID = 0; // Device ID of MultiClamp 700A (1-8)
		UINT uChannelID = 0; // Headstage channel ID

		std::vector<MultiClamp> multiClampVector;

		// Find the first multiclamp.
		if (!MCCMSG_FindFirstMultiClamp_FuncPtr(hMCCmsg, &uModel, szSerialNum, sizeof(szSerialNum), &uCOMPortID, &uDeviceID, &uChannelID, &mccError)) {
			goto done;
		}

		// Add the device to the vector of multi clamps.
		multiClampVector.push_back(MultiClamp(szSerialNum, uModel, uCOMPortID, uDeviceID, uChannelID));

		// Iterate through all other MultiClamps.
		while (1) {
			// find the next MultiClamp
			if (MCCMSG_FindNextMultiClamp_FuncPtr(hMCCmsg, &uModel, szSerialNum, sizeof(szSerialNum), &uCOMPortID, &uDeviceID, &uChannelID, &mccError)) {
				// Add the device to the vector of multi clamps.
				multiClampVector.push_back(MultiClamp(szSerialNum, uModel, uCOMPortID, uDeviceID, uChannelID));
			}
			else {
				// We've found them all. Make sure to ignore any value of mccError, since in testing
				// it seems that this sometimes gets set to indicate an error when there isn't actually
				// an error.
				mccError = MCCMSG_ERROR_NOERROR;
				break;
			}
		}

		// Return information about the servers found
		// to the user.
		if (err = CreateMultiClampListWave(multiClampVector)) {
			goto done;
		}
	}
	else {
		// Couldn't get the MCC DLL handle.
		err = MCC_DLL_HANDLE_IS_NULL;
		goto done;
	}

done:
	// Possibly translate a MCC DLL error code into an Igor error code.
	if (!err && mccError != MCCMSG_ERROR_NOERROR) {
		// Translate the MCC error code into an Igor error code.
		err = MCCErrorCodeToXOPErrorCode(mccError);
	}
	SetOperationNumVar("V_flag", (double)err);
	gExecuting = FALSE;
	if (errorType == MCC_ERROR_YES) {
		// Only create a run time error if /Z flag not set or set to 0.
		return err;
	}
	else {
		return 0;
	}
}

int RegisterMCC_FindServers() {
	// NOTE: If you change this template, you must change the MCC_FindServersRuntimeParams structure as well.
	const char* cmdTemplate = "MCC_FindServers /Z[=number:errorType]";
	const char* runtimeNumVarList = "V_Flag;";
	const char* runtimeStrVarList = "";
	return RegisterOperation(cmdTemplate, runtimeNumVarList, runtimeStrVarList, sizeof(MCC_FindServersRuntimeParams), (void*)ExecuteMCC_FindServers, 0);
}


//****************************************
// Utility functions for processing flags.
//****************************************
/**
 * Process the value of the Z flag provided by the user
 * to make sure it is valid.
 * @access	public
 * @param double valueFromUser
 * 	The value of the Z flag provided by the user.
 * @return double
 * 	The value of the Z flag that should be used by the calling function.
 */
double Process_Z_FlagValue(double valueFromUser) {
	double errorType;

	// Ignore value of errorType provided by user
	// if it is not an actual number.
	if (IsINF64(&valueFromUser) || IsNaN64(&valueFromUser)) {
		errorType = MCC_ERROR_IGNORE;
	}
	else {
		errorType = valueFromUser;
	}
	return errorType;
}

/**
 * Create an Igor wave with a row containing information about each multiclamp
 * that was found.
 *
 * @return int
 * 	Zero if there was no error or an Igor error code.
 */
int CreateMultiClampListWave(std::vector<MultiClamp> multiClampVector) {
	// Make the output wave.
	waveHndl serverListWaveHndl;

	CountInt numServers = multiClampVector.size();

	// Make string with desired wave name.
	char waveName[MAX_OBJ_NAME + 1];
	strcpy(waveName, "W_MultiClamps");

	CountInt dimensionSizes[3];
	dimensionSizes[0] = numServers;		// rows
	dimensionSizes[1] = 4;				// cols
	dimensionSizes[2] = 0;				// layers

	// Actually make the wave.
	int err = 0;
	if (err = MDMakeWave(&serverListWaveHndl, waveName, NULL, dimensionSizes, NT_I32, 1)) {
		return err;
	}

	// Set the column dimension labels of the wave (the
	// serial number will go in the row dimension label
	// later on).
	if (err = MDSetDimensionLabel(serverListWaveHndl, 1, 0, "Model")) {
		return err;
	}
	if (err = MDSetDimensionLabel(serverListWaveHndl, 1, 1, "ComPortID")) {
		return err;
	}
	if (err = MDSetDimensionLabel(serverListWaveHndl, 1, 2, "DeviceID")) {
		return err;
	}
	if (err = MDSetDimensionLabel(serverListWaveHndl, 1, 3, "ChannelID")) {
		return err;
	}

	// Loop through the rows and columns of the wave and set the values.
	CountInt rowNum = 0;

	// Set the values in the wave
	CountInt destIndicies[2];
	double value[2];

	// Marker of whether the server is a 700A or 700B server.
	int is700BServer = 1;

	// Loop through all telegraph servers found.
	for (rowNum = 0; rowNum < numServers; rowNum++) {
		MultiClamp thisMultiClamp(multiClampVector.at(rowNum));
		if ((thisMultiClamp.uModel) == MCCMSG_HW_TYPE_MC700B) {
			is700BServer = 1;
		}
		else {
			is700BServer = 0;
		}

		// Since the serial number is a char array and this is a
		// numeric wave, we store ththe serial number in
		// the row dimension label.
		if (is700BServer) {
			if (err = MDSetDimensionLabel(serverListWaveHndl, 0, rowNum, thisMultiClamp.szSerialNum)) {
				return err;
			}
		}
		else {
			if (err = MDSetDimensionLabel(serverListWaveHndl, 0, rowNum, "")) {		// Serial number not used for 700A amp, so set empty string as dim label instead.
				return err;
			}
		}

		// Set Model column.
		destIndicies[0] = rowNum;
		destIndicies[1] = 0;
		value[0] = is700BServer;
		if (err = MDSetNumericWavePointValue(serverListWaveHndl, destIndicies, value)) {
			return err;
		}

		// Set ComPortID column.
		destIndicies[1] = 1;
		if (is700BServer) {
			value[0] = -1;		// ComPortID not used for 700B, so set to -1.
		}
		else {
			value[0] = thisMultiClamp.uCOMPortID;
		}
		if (err = MDSetNumericWavePointValue(serverListWaveHndl, destIndicies, value)) {
			return err;
		}

		// Set DeviceID column.
		destIndicies[1] = 2;
		if (is700BServer) {
			value[0] = -1;		// DeviceID not used for 700B, so set to -1.
		}
		else {
			value[0] = thisMultiClamp.uDeviceID;
		}
		if (err = MDSetNumericWavePointValue(serverListWaveHndl, destIndicies, value)) {
			return err;
		}

		// Set ChannelID column.
		destIndicies[1] = 3;
		value[0] = thisMultiClamp.uChannelID;
		if (err = MDSetNumericWavePointValue(serverListWaveHndl, destIndicies, value)) {
			return err;
		}
	}
	return 0;		// No error
}
