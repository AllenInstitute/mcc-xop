/**
	\file MultiClamp700xCommander_Functions.cpp

	Code that provides external functions to Igor for communicating
	with MultiClamp Commander.


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
#include "MultiClamp700xCommander_Functions.h"
#include "MultiClamp700xCommander.h"

extern UINT gExecuting;		// Flag variable that reflects whether the XOP is in the middle of executing and used to prevent recursion.


//******************
// Utility functions
//******************
/**
* Determine if a numerical parameter provided by the user is a valid number.
* @access	public
* @param double value
* 	The numeric value provided by the user.
* @return int
* 	Truth of whether the value is valid.
*/
int IsValidNumber(double value) {
	if (IsINF64(&value) || IsNaN64(&value)) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**
\brief Generic function wrapper for XOP external functions of the form:
double Function()
\access	public
*/
int Generic_ReturnDouble_Wrapper(MCC_ReturnDouble_Params* p, MCCFunctions mccFx) {
	int err = 0;
	int mccError;
	SetNaN64(&p->result);		// A result of NaN means there was an error. The user should call GetRTError() to get the error code.

	HMCCMSG hMCCmsg = GetMCCDLLHandle();
	if (hMCCmsg == NULL) {
		// Couldn't get the MCC DLL handle.
		err = MCC_DLL_HANDLE_IS_NULL;
	}
	else {
		// The XOP external function always returns a double but the DLL
		// functions take different pointer types, so we need a few different
		// function pointer variables here.
		BOOL(WINAPI *mccdll_UINTParam_Function)(HMCCMSG, UINT*, int*) = NULL;
		BOOL(WINAPI *mccdll_DoubleParam_Function)(HMCCMSG, double*, int*) = NULL;
		BOOL(WINAPI *mccdll_BoolParam_Function)(HMCCMSG, BOOL*, int*) = NULL;
		BOOL(WINAPI *mccdll_NoParam_Function)(HMCCMSG, int*) = NULL;

		switch (mccFx) {
		case FX_MCC_GetHoldingEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetHoldingEnable;
			break;

		case FX_MCC_GetHolding:
			mccdll_DoubleParam_Function = &MCCMSG_GetHolding;
			break;


		case FX_MCC_GetMode:
			mccdll_UINTParam_Function = &MCCMSG_GetMode;
			break;


		case FX_MCC_GetBridgeBalEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetBridgeBalEnable;
			break;

		case FX_MCC_GetBridgeBalResist:
			mccdll_DoubleParam_Function = &MCCMSG_GetBridgeBalResist;
			break;

		case FX_MCC_AutoBridgeBal:
			mccdll_NoParam_Function = &MCCMSG_AutoBridgeBal;
			break;


		case FX_MCC_GetNeutralizationEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetNeutralizationEnable;
			break;

		case FX_MCC_GetNeutralizationCap:
			mccdll_DoubleParam_Function = &MCCMSG_GetNeutralizationCap;
			break;


		case FX_MCC_GetWholeCellCompEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetWholeCellCompEnable;
			break;

		case FX_MCC_GetWholeCellCompCap:
			mccdll_DoubleParam_Function = &MCCMSG_GetWholeCellCompCap;
			break;

		case FX_MCC_GetWholeCellCompResist:
			mccdll_DoubleParam_Function = &MCCMSG_GetWholeCellCompResist;
			break;

		case FX_MCC_AutoWholeCellComp:
			mccdll_NoParam_Function = &MCCMSG_AutoWholeCellComp;
			break;


		case FX_MCC_GetRsCompEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetRsCompEnable;
			break;

		case FX_MCC_GetRsCompBandwidth:
			mccdll_DoubleParam_Function = &MCCMSG_GetRsCompBandwidth;
			break;

		case FX_MCC_GetRsCompCorrection:
			mccdll_DoubleParam_Function = &MCCMSG_GetRsCompCorrection;
			break;

		case FX_MCC_GetRsCompPrediction:
			mccdll_DoubleParam_Function = &MCCMSG_GetRsCompPrediction;
			break;

		case FX_MCC_GetOscKillerEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetOscKillerEnable;
			break;

		case FX_MCC_GetPrimarySignalGain:
			mccdll_DoubleParam_Function = &MCCMSG_GetPrimarySignalGain;
			break;

		case FX_MCC_GetPrimarySignalLPF:
			mccdll_DoubleParam_Function = &MCCMSG_GetPrimarySignalLPF;
			break;

		case FX_MCC_GetPrimarySignalHPF:
			mccdll_DoubleParam_Function = &MCCMSG_GetPrimarySignalHPF;
			break;

		case FX_MCC_GetSecondarySignalGain:
			mccdll_DoubleParam_Function = &MCCMSG_GetSecondarySignalGain;
			break;

		case FX_MCC_GetSecondarySignalLPF:
			mccdll_DoubleParam_Function = &MCCMSG_GetSecondarySignalLPF;
			break;

		case FX_MCC_AutoPipetteOffset:
			mccdll_NoParam_Function = &MCCMSG_AutoPipetteOffset;
			break;

		case FX_MCC_GetPipetteOffset:
			mccdll_DoubleParam_Function = &MCCMSG_GetPipetteOffset;
			break;

		case FX_MCC_GetFastCompCap:
			mccdll_DoubleParam_Function = &MCCMSG_GetFastCompCap;
			break;

		case FX_MCC_GetSlowCompCap:
			mccdll_DoubleParam_Function = &MCCMSG_GetSlowCompCap;
			break;

		case FX_MCC_GetFastCompTau:
			mccdll_DoubleParam_Function = &MCCMSG_GetFastCompTau;
			break;

		case FX_MCC_GetSlowCompTau:
			mccdll_DoubleParam_Function = &MCCMSG_GetSlowCompTau;
			break;

		case FX_MCC_GetSlowCompTauX20Enable:
			mccdll_BoolParam_Function = &MCCMSG_GetSlowCompTauX20Enable;
			break;

		case FX_MCC_AutoFastComp:
			mccdll_NoParam_Function = &MCCMSG_AutoFastComp;
			break;

		case FX_MCC_AutoSlowComp:
			mccdll_NoParam_Function = &MCCMSG_AutoSlowComp;
			break;

		case FX_MCC_GetSlowCurrentInjEnable:
			mccdll_BoolParam_Function = &MCCMSG_GetSlowCurrentInjEnable;
			break;

		case FX_MCC_GetSlowCurrentInjLevel:
			mccdll_DoubleParam_Function = &MCCMSG_GetSlowCurrentInjLevel;
			break;

		case FX_MCC_GetSlowCurrentInjSetlTime:
			mccdll_DoubleParam_Function = &MCCMSG_GetSlowCurrentInjSettlingTime;
			break;



		default:
			// Should never get here.
			XOPNotice("BUG: MultiClamp700xCommander XOP, Generic_ReturnDouble_Wrapper(). Unexpected value for mccFx parameter.\r");
			return MCC_XOP_BUG;
			break;
		}

		BOOL mccdll_fx_return = FALSE;
		BOOL boolOutParam = FALSE;
		UINT uintOutParam = 0;
		double dOutParam = 0.0;

		double dllOutputValue = 0;
		if (mccdll_UINTParam_Function) {
			mccdll_fx_return = mccdll_UINTParam_Function(hMCCmsg, &uintOutParam, &mccError);
			dllOutputValue = static_cast<double>(uintOutParam);
		}
		else if (mccdll_DoubleParam_Function) {
			mccdll_fx_return = mccdll_DoubleParam_Function(hMCCmsg, &dOutParam, &mccError);
			// AL 06Oct2014:
			// MCCMSG_GetPipetteOffset() returns the opposite of the actual
			// value when in current clamp or I=0 mode (but not voltage clamp).
			// This appears to be a bug. To work around the bug, we check the mode
			// and, if necessary, flip the sign. Obviously, we only do this when
			// we've been asked to get the pipette offset value.
			if (mccdll_fx_return && (mccdll_DoubleParam_Function == &MCCMSG_GetPipetteOffset)) {
				UINT modeID = -1;
				int modeError = 0;
				BOOL modeReturn = MCCMSG_GetMode(hMCCmsg, &modeID, &modeError);
				if (modeReturn) {
					if (modeID != MCCMSG_MODE_VCLAMP) {
						dOutParam = -1.0 * dOutParam;
					}
					dllOutputValue = dOutParam;
				}
			}
			else {
				dllOutputValue = dOutParam;
			}
		}
		else if (mccdll_BoolParam_Function) {
			mccdll_fx_return = mccdll_BoolParam_Function(hMCCmsg, &boolOutParam, &mccError);
			dllOutputValue = static_cast<double>(boolOutParam);
		}
		else if (mccdll_NoParam_Function) {
			mccdll_fx_return = mccdll_NoParam_Function(hMCCmsg, &mccError);
			dllOutputValue = 0;		// Function returns nothing.
		}
		else {
			// Should never get here.
			XOPNotice("BUG: MultiClamp700xCommander XOP, Generic_ReturnDouble_Wrapper(). All function pointers are NULL.\r");
			return MCC_XOP_BUG;
		}

		if (!mccdll_fx_return) {
			err = MCCErrorCodeToXOPErrorCode(mccError);
		}
		else {
			p->result = dllOutputValue;
		}
	}
	return err;
}

/**
	\brief Generic function wrapper for XOP external functions of the form:
		double Function(double)
	\access	public
*/
int Generic_P1Double_ReturnDouble_Wrapper(MCC_P1Double_ReturnDouble_Params* p, MCCFunctions mccFx) {
	int err = 0;
	int mccError;
	SetNaN64(&p->result);		// A result of NaN means there was an error. The user should call GetRTError() to get the error code.

	HMCCMSG hMCCmsg = GetMCCDLLHandle();
	if (hMCCmsg == NULL) {
		// Couldn't get the MCC DLL handle.
		err = MCC_DLL_HANDLE_IS_NULL;
	}
	else {
		// Since the parameter coming in from Igor is a double, but the
		// DLL function call might take a UINT or BOOL parameter instead of
		// a double, we need a few different function pointer variables.
		BOOL(WINAPI *mccdll_UINTParam_Function)(HMCCMSG, UINT, int*) = NULL;
		BOOL(WINAPI *mccdll_DoubleParam_Function)(HMCCMSG, double, int*) = NULL;
		BOOL(WINAPI *mccdll_BoolParam_Function)(HMCCMSG, BOOL, int*) = NULL;
		switch (mccFx) {
			case FX_MCC_SetTimeoutMs:
				mccdll_UINTParam_Function = &MCCMSG_SetTimeOut;
				break;


			case FX_MCC_SetHolding:
				mccdll_DoubleParam_Function = &MCCMSG_SetHolding;
				break;

			case FX_MCC_SetHoldingEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetHoldingEnable;
				break;


			case FX_MCC_SetMode:
				mccdll_UINTParam_Function = &MCCMSG_SetMode;
				break;


			case FX_MCC_SetBridgeBalEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetBridgeBalEnable;
				break;

			case FX_MCC_SetBridgeBalResist:
				mccdll_DoubleParam_Function = &MCCMSG_SetBridgeBalResist;
				break;


			case FX_MCC_SetNeutralizationEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetNeutralizationEnable;
				break;

			case FX_MCC_SetNeutralizationCap:
				mccdll_DoubleParam_Function = &MCCMSG_SetNeutralizationCap;
				break;


			case FX_MCC_SetWholeCellCompEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetWholeCellCompEnable;
				break;

			case FX_MCC_SetWholeCellCompCap:
				mccdll_DoubleParam_Function = &MCCMSG_SetWholeCellCompCap;
				break;

			case FX_MCC_SetWholeCellCompResist:
				mccdll_DoubleParam_Function = &MCCMSG_SetWholeCellCompResist;
				break;


			case FX_MCC_SetRsCompEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetRsCompEnable;
				break;

			case FX_MCC_SetRsCompBandwidth:
				mccdll_DoubleParam_Function = &MCCMSG_SetRsCompBandwidth;
				break;

			case FX_MCC_SetRsCompCorrection:
				mccdll_DoubleParam_Function = &MCCMSG_SetRsCompCorrection;
				break;

			case FX_MCC_SetRsCompPrediction:
				mccdll_DoubleParam_Function = &MCCMSG_SetRsCompPrediction;
				break;


			case FX_MCC_SetOscKillerEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetOscKillerEnable;
				break;

			case FX_MCC_SetPrimarySignalGain:
				mccdll_DoubleParam_Function = &MCCMSG_SetPrimarySignalGain;
				break;

			case FX_MCC_SetPrimarySignalLPF:
				mccdll_DoubleParam_Function = &MCCMSG_SetPrimarySignalLPF;
				break;

			case FX_MCC_SetPrimarySignalHPF:
				mccdll_DoubleParam_Function = &MCCMSG_SetPrimarySignalHPF;
				break;

			case FX_MCC_SetSecondarySignalGain:
				mccdll_DoubleParam_Function = &MCCMSG_SetSecondarySignalGain;
				break;

			case FX_MCC_SetSecondarySignalLPF:
				mccdll_DoubleParam_Function = &MCCMSG_SetSecondarySignalLPF;
				break;

			case FX_MCC_SetPipetteOffset:
				mccdll_DoubleParam_Function = &MCCMSG_SetPipetteOffset;
				break;

			case FX_MCC_SetFastCompCap:
				mccdll_DoubleParam_Function = &MCCMSG_SetFastCompCap;
				break;

			case FX_MCC_SetSlowCompCap:
				mccdll_DoubleParam_Function = &MCCMSG_SetSlowCompCap;
				break;

			case FX_MCC_SetFastCompTau:
				mccdll_DoubleParam_Function = &MCCMSG_SetFastCompTau;
				break;

			case FX_MCC_SetSlowCompTau:
				mccdll_DoubleParam_Function = &MCCMSG_SetSlowCompTau;
				break;

			case FX_MCC_SetSlowCompTauX20Enable:
				mccdll_BoolParam_Function = &MCCMSG_SetSlowCompTauX20Enable;
				break;

			case FX_MCC_SetSlowCurrentInjEnable:
				mccdll_BoolParam_Function = &MCCMSG_SetSlowCurrentInjEnable;
				break;

			case FX_MCC_SetSlowCurrentInjLevel:
				mccdll_DoubleParam_Function = &MCCMSG_SetSlowCurrentInjLevel;
				break;

			case FX_MCC_SetSlowCurrentInjSettlingTime:
				mccdll_DoubleParam_Function = &MCCMSG_SetSlowCurrentInjSettlingTime;
				break;

			default:
				// Should never get here.
				XOPNotice("BUG: MultiClamp700xCommander XOP, Generic_P1Double_ReturnDouble_Wrapper(). Unexpected value for mccFx parameter.\r");
				return MCC_XOP_BUG;
				break;
		}

		BOOL mccdll_fx_return = FALSE;
		if (mccdll_UINTParam_Function) {
			mccdll_fx_return = mccdll_UINTParam_Function(hMCCmsg, static_cast<UINT>(p->p1), &mccError);
		}
		else if (mccdll_DoubleParam_Function) {

			// AL 06Oct2014:
			// MCCMSG_SetPipetteOffset() sets the offset to the opposite of value passed
			// when in current clamp or I=0 mode (but not voltage clamp).
			// This appears to be a bug. To work around the bug, we check the mode
			// and, if necessary, flip the sign of the parameter value. Obviously, we only do this when
			// we've been asked to get the pipette offset value.
			if (mccdll_DoubleParam_Function == &MCCMSG_SetPipetteOffset) {
				UINT modeID = -1;
				mccdll_fx_return = MCCMSG_GetMode(hMCCmsg, &modeID, &mccError);
				if (mccdll_fx_return) {
					if (modeID != MCCMSG_MODE_VCLAMP) {
						p->p1 = -1.0 * p->p1;
					}
					mccdll_fx_return = mccdll_DoubleParam_Function(hMCCmsg, p->p1, &mccError);
				}
			}
			else {
				mccdll_fx_return = mccdll_DoubleParam_Function(hMCCmsg, p->p1, &mccError);
			}
		}
		else if (mccdll_BoolParam_Function) {
			mccdll_fx_return = mccdll_BoolParam_Function(hMCCmsg, static_cast<BOOL>(p->p1), &mccError);
		}
		else {
			// Should never get here.
			XOPNotice("BUG: MultiClamp700xCommander XOP, Generic_P1Double_ReturnDouble_Wrapper(). All function pointers are NULL.\r");
			return MCC_XOP_BUG;
		}

		if (!mccdll_fx_return) {
			err = MCCErrorCodeToXOPErrorCode(mccError);
		}
		else {
			p->result = 0;
		}
	}
	return err;
}


/**
* XOP function for MCC_SelectMultiClamp700B external function.
* @access	public
*/
int MCC_SelectMultiClamp700B(MCC_SelectMultiClamp700BParams* p) {
	int err = 0;
	if (p == NULL) {
		err = SYNERR;
		goto done;
	}

	SetNaN64(&p->result);		// A result of NaN means there was an error. The user should call GetRTError() to get the error code.

	if (gExecuting) {
		err = XOP_RECURSION_ATTEMPTED;
		// NOTE:  We don't goto done: here because
		// doing so would reset gExecuting, which
		// is not what we want.
		if (p->serialNumberStrHandle != NULL) {		// We have do dispose of the string handle ourselves.
			DisposeHandle(p->serialNumberStrHandle);
		}
		return err;
	}
	gExecuting = TRUE;

	// Test input parameters.
	if (!IsValidNumber(p->channelID)) {
		err = NO_NAN_OR_INFS_ALLOWED;
		goto done;
	}

	if (p->serialNumberStrHandle == NULL) {
		err = INVALID_SERIAL_NUMBER;
		goto done;
	}

	HMCCMSG hMCCmsg = GetMCCDLLHandle();
	if (hMCCmsg == NULL) {
		// Couldn't get the MCC DLL handle.
		err = MCC_DLL_HANDLE_IS_NULL;
		goto done;
	}
	else {
		// Get a C string from parameterStrHndl
		char szSerialNum[16];
		if (err = GetCStringFromHandle(p->serialNumberStrHandle, szSerialNum, 16)) {
			goto done;
		}

		// Default values for these variables, which aren't used for a 700B amplifier.
		UINT uCOMPortID = 0; // COM port ID of MultiClamp 700A (1-16)
		UINT uDeviceID = 0; // Device ID of MultiClamp 700A (1-8)

		// This function is specific to 700B amplifiers, so we hard code this value.
		UINT uModel = MCCMSG_HW_TYPE_MC700B;

		// The value of this parameter comes from the Igor function call.
		UINT uChannelID = static_cast<UINT>(p->channelID); // Headstage channel ID
		int nError = 0;
		if (!MCCMSG_SelectMultiClamp(hMCCmsg, uModel, szSerialNum, uCOMPortID, uDeviceID, uChannelID, &nError)) {
			err = MCCErrorCodeToXOPErrorCode(nError);
			goto done;
		}
		else {
			p->result = 0;
		}
	}

done:
	// We have do dispose of the string handle ourselves.
	if (p->serialNumberStrHandle != NULL) {
		DisposeHandle(p->serialNumberStrHandle);
	}
	gExecuting = FALSE;
	return err;
}

// TODO: FUTURE Implement MCC_SelectMultiClamp700A()
