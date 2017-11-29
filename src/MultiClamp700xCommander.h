/**
	\file MultiClamp700xCommander.h

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

#ifndef MULTICLAMP700XCOMMANDER_H
#define MULTICLAMP700XCOMMANDER_H

#include "AxMultiClampMsg.h"

/* MultiClamp700xCommander custom error codes */
enum XOPErrors {
	OLD_IGOR = 1 + FIRST_XOP_ERR,
	UNUSED_1,
	WRONG_MCC_API_VERSION,
	FAILURE_CREATING_MCC_DLL_HANDLE,
	MCC_DLL_HANDLE_IS_NULL,
	NO_NAN_OR_INFS_ALLOWED,
	INVALID_SERIAL_NUMBER,
	MCC_XOP_BUG,


	// MCCMSG Errors (errors from the API)
	XOP_MCCMSG_ERROR_OUTOFMEMORY,
	XOP_MCCMSG_ERROR_MCCNOTOPEN,
	XOP_MCCMSG_ERROR_INVALIDDLLHANDLE,
	XOP_MCCMSG_ERROR_INVALIDPARAMETER,
	XOP_MCCMSG_ERROR_MSGTIMEOUT,
	XOP_MCCMSG_ERROR_MCCCOMMANDFAIL,
};

/**
	\brief An enumeration of MCC API functions that are
	implemented by this XOP as external functions.

	\warning This enum must be zero-based and the order of
	functions in this enum *must* be identical to the order of
	external functions defined in the 1100 XOPF resource in
	MultiClamp700xCommanderWinCustom.rc.
*/
enum MCCFunctions {
	FX_MCC_SetTimeoutMs = 0,
	FX_MCC_SelectMultiClamp700B,

	FX_MCC_SetHoldingEnable,
	FX_MCC_GetHoldingEnable,
	FX_MCC_SetHolding,
	FX_MCC_GetHolding,

	FX_MCC_SetMode,
	FX_MCC_GetMode,

	FX_MCC_SetBridgeBalEnable,
	FX_MCC_GetBridgeBalEnable,
	FX_MCC_SetBridgeBalResist,
	FX_MCC_GetBridgeBalResist,
	FX_MCC_AutoBridgeBal,

	FX_MCC_SetNeutralizationEnable,
	FX_MCC_GetNeutralizationEnable,
	FX_MCC_SetNeutralizationCap,
	FX_MCC_GetNeutralizationCap,

	FX_MCC_SetWholeCellCompEnable,
	FX_MCC_GetWholeCellCompEnable,
	FX_MCC_SetWholeCellCompCap,
	FX_MCC_GetWholeCellCompCap,
	FX_MCC_SetWholeCellCompResist,
	FX_MCC_GetWholeCellCompResist,
	FX_MCC_AutoWholeCellComp,

	FX_MCC_SetRsCompEnable,
	FX_MCC_GetRsCompEnable,
	FX_MCC_SetRsCompBandwidth,
	FX_MCC_GetRsCompBandwidth,
	FX_MCC_SetRsCompCorrection,
	FX_MCC_GetRsCompCorrection,
	FX_MCC_SetRsCompPrediction,
	FX_MCC_GetRsCompPrediction,

	FX_MCC_SetOscKillerEnable,
	FX_MCC_GetOscKillerEnable,

	FX_MCC_SetPrimarySignalGain,
	FX_MCC_GetPrimarySignalGain,
	FX_MCC_SetPrimarySignalLPF,
	FX_MCC_GetPrimarySignalLPF,
	FX_MCC_SetPrimarySignalHPF,
	FX_MCC_GetPrimarySignalHPF,

	FX_MCC_SetSecondarySignalGain,
	FX_MCC_GetSecondarySignalGain,
	FX_MCC_SetSecondarySignalLPF,
	FX_MCC_GetSecondarySignalLPF,

	FX_MCC_AutoPipetteOffset,
	FX_MCC_SetPipetteOffset,
	FX_MCC_GetPipetteOffset,

	FX_MCC_SetFastCompCap,
	FX_MCC_GetFastCompCap,
	FX_MCC_SetSlowCompCap,
	FX_MCC_GetSlowCompCap,
	FX_MCC_SetFastCompTau,
	FX_MCC_GetFastCompTau,
	FX_MCC_SetSlowCompTau,
	FX_MCC_GetSlowCompTau,
	FX_MCC_SetSlowCompTauX20Enable,
	FX_MCC_GetSlowCompTauX20Enable,
	FX_MCC_AutoFastComp,
	FX_MCC_AutoSlowComp,

	FX_MCC_SetSlowCurrentInjEnable,
	FX_MCC_GetSlowCurrentInjEnable,
	FX_MCC_SetSlowCurrentInjLevel,
	FX_MCC_GetSlowCurrentInjLevel,
	FX_MCC_SetSlowCurrentInjSettlingTime,
	FX_MCC_GetSlowCurrentInjSetlTime,

	//FX_MCC_,
	//FX_MCC_,
	//FX_MCC_,
	//FX_MCC_,
	//FX_MCC_,
	//FX_MCC_,
};

/* Prototypes */
HOST_IMPORT int XOPMain(IORecHandle ioRecHandle);
HMCCMSG GetMCCDLLHandle();
int MCCErrorCodeToXOPErrorCode(int mccError);

class MultiClamp {
public:
	MultiClamp() :
		uModel(0),
		uCOMPortID(0),
		uDeviceID(0),
		uChannelID(0)
	{
		strcpy(szSerialNum, "");
	}

	MultiClamp(const char* serialNum, UINT Model, UINT COMPortID, UINT DeviceID, UINT ChannelID) :
		uModel(Model),
		uCOMPortID(COMPortID),
		uDeviceID(DeviceID),
		uChannelID(ChannelID)
	{
		strncpy(szSerialNum, serialNum, sizeof(szSerialNum));
	}

	char szSerialNum[16]; // Serial number of MultiClamp 700B
	UINT uModel; // Identifies MultiClamp 700A or 700B model
	UINT uCOMPortID; // COM port ID of MultiClamp 700A (1-16)
	UINT uDeviceID; // Device ID of MultiClamp 700A (1-8)
	UINT uChannelID; // Headstage channel ID
};

#endif		// MULTICLAMP700XCOMMANDER_H
