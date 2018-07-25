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

#define EXPORT_SAVE EXPORT
#define EXPORT
#include "AxMultiClampMsg.h"
#undef EXPORT
#define EXPORT EXPORT_SAVE

using mccdll_UINTParam_FuncType      = BOOL(WINAPI *)(HMCCMSG, UINT, int*);
using mccdll_PtrUINTParam_FuncType   = BOOL(WINAPI *)(HMCCMSG, UINT*, int*);
using mccdll_DoubleParam_FuncType    = BOOL(WINAPI *)(HMCCMSG, double, int*);
using mccdll_PtrDoubleParam_FuncType = BOOL(WINAPI *)(HMCCMSG, double*, int*);
using mccdll_BoolParam_FuncType      = BOOL(WINAPI *)(HMCCMSG, BOOL, int*);
using mccdll_PtrBoolParam_FuncType   = BOOL(WINAPI *)(HMCCMSG, BOOL*, int*);
using mccdll_NoParam_FunctType       = BOOL(WINAPI *)(HMCCMSG, int*);

using MCCMSG_CheckAPIVersion_FuncType               = BOOL(WINAPI *)(LPCTSTR);
using MCCMSG_CreateObject_FuncType                  = HMCCMSG(WINAPI *)(int*);
using MCCMSG_DestroyObject_FuncType                 = void(WINAPI *)(HMCCMSG);
using MCCMSG_SetTimeOut_FuncType                    = BOOL(WINAPI *)(HMCCMSG, UINT, int*);
using MCCMSG_FindFirstMultiClamp_FuncType           = BOOL(WINAPI *)(HMCCMSG, UINT*, char*, UINT, UINT*, UINT*, UINT*, int*);
using MCCMSG_FindNextMultiClamp_FuncType            = BOOL(WINAPI *)(HMCCMSG, UINT*, char*, UINT, UINT*, UINT*, UINT*, int*);
using MCCMSG_SelectMultiClamp_FuncType              = BOOL(WINAPI *)(HMCCMSG, UINT, char*, UINT, UINT, UINT, int*);
using MCCMSG_SetMode_FuncType                       = BOOL(WINAPI *)(HMCCMSG, UINT, int*);
using MCCMSG_GetMode_FuncType                       = BOOL(WINAPI *)(HMCCMSG, UINT*, int*);
using MCCMSG_SetModeSwitchEnable_FuncType           = mccdll_BoolParam_FuncType;
using MCCMSG_GetModeSwitchEnable_FuncType           = mccdll_PtrBoolParam_FuncType;
using MCCMSG_GetFeedbackResistorVC1_FuncType        = mccdll_PtrUINTParam_FuncType;
using MCCMSG_GetFeedbackResistorIC1_FuncType        = mccdll_PtrUINTParam_FuncType;
using MCCMSG_GetFeedbackResistorVC2_FuncType        = mccdll_PtrUINTParam_FuncType;
using MCCMSG_GetFeedbackResistorIC2_FuncType        = mccdll_PtrUINTParam_FuncType;
using MCCMSG_SetHoldingEnable_FuncType              = mccdll_BoolParam_FuncType;
using MCCMSG_GetHoldingEnable_FuncType              = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetHolding_FuncType                    = mccdll_DoubleParam_FuncType;
using MCCMSG_GetHolding_FuncType                    = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetTestSignalEnable_FuncType           = mccdll_BoolParam_FuncType;
using MCCMSG_GetTestSignalEnable_FuncType           = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetTestSignalAmplitude_FuncType        = mccdll_DoubleParam_FuncType;
using MCCMSG_GetTestSignalAmplitude_FuncType        = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetTestSignalFrequency_FuncType        = mccdll_DoubleParam_FuncType;
using MCCMSG_GetTestSignalFrequency_FuncType        = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_AutoPipetteOffset_FuncType             = mccdll_NoParam_FunctType;
using MCCMSG_SetPipetteOffset_FuncType              = mccdll_DoubleParam_FuncType;
using MCCMSG_GetPipetteOffset_FuncType              = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSlowCurrentInjEnable_FuncType       = mccdll_BoolParam_FuncType;
using MCCMSG_GetSlowCurrentInjEnable_FuncType       = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetSlowCurrentInjLevel_FuncType        = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSlowCurrentInjLevel_FuncType        = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSlowCurrentInjSettlingTime_FuncType = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSlowCurrentInjSettlingTime_FuncType = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetFastCompCap_FuncType                = mccdll_DoubleParam_FuncType;
using MCCMSG_GetFastCompCap_FuncType                = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSlowCompCap_FuncType                = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSlowCompCap_FuncType                = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetFastCompTau_FuncType                = mccdll_DoubleParam_FuncType;
using MCCMSG_GetFastCompTau_FuncType                = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSlowCompTau_FuncType                = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSlowCompTau_FuncType                = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSlowCompTauX20Enable_FuncType       = mccdll_BoolParam_FuncType;
using MCCMSG_GetSlowCompTauX20Enable_FuncType       = mccdll_PtrBoolParam_FuncType;
using MCCMSG_AutoFastComp_FuncType                  = mccdll_NoParam_FunctType;
using MCCMSG_AutoSlowComp_FuncType                  = mccdll_NoParam_FunctType;
using MCCMSG_SetNeutralizationEnable_FuncType       = mccdll_BoolParam_FuncType;
using MCCMSG_GetNeutralizationEnable_FuncType       = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetNeutralizationCap_FuncType          = mccdll_DoubleParam_FuncType;
using MCCMSG_GetNeutralizationCap_FuncType          = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetWholeCellCompEnable_FuncType        = mccdll_BoolParam_FuncType;
using MCCMSG_GetWholeCellCompEnable_FuncType        = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetWholeCellCompCap_FuncType           = mccdll_DoubleParam_FuncType;
using MCCMSG_GetWholeCellCompCap_FuncType           = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetWholeCellCompResist_FuncType        = mccdll_DoubleParam_FuncType;
using MCCMSG_GetWholeCellCompResist_FuncType        = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_AutoWholeCellComp_FuncType             = mccdll_NoParam_FunctType;
using MCCMSG_SetRsCompEnable_FuncType               = mccdll_BoolParam_FuncType;
using MCCMSG_GetRsCompEnable_FuncType               = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetRsCompBandwidth_FuncType            = mccdll_DoubleParam_FuncType;
using MCCMSG_GetRsCompBandwidth_FuncType            = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetRsCompCorrection_FuncType           = mccdll_DoubleParam_FuncType;
using MCCMSG_GetRsCompCorrection_FuncType           = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetRsCompPrediction_FuncType           = mccdll_DoubleParam_FuncType;
using MCCMSG_GetRsCompPrediction_FuncType           = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetOscKillerEnable_FuncType            = mccdll_BoolParam_FuncType;
using MCCMSG_GetOscKillerEnable_FuncType            = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetPrimarySignal_FuncType              = mccdll_UINTParam_FuncType;
using MCCMSG_GetPrimarySignal_FuncType              = mccdll_PtrUINTParam_FuncType;
using MCCMSG_SetPrimarySignalGain_FuncType          = mccdll_DoubleParam_FuncType;
using MCCMSG_GetPrimarySignalGain_FuncType          = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetPrimarySignalLPF_FuncType           = mccdll_DoubleParam_FuncType;
using MCCMSG_GetPrimarySignalLPF_FuncType           = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetPrimarySignalHPF_FuncType           = mccdll_DoubleParam_FuncType;
using MCCMSG_GetPrimarySignalHPF_FuncType           = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetScopeSignalLPF_FuncType             = mccdll_DoubleParam_FuncType;
using MCCMSG_GetScopeSignalLPF_FuncType             = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSecondarySignal_FuncType            = mccdll_UINTParam_FuncType;
using MCCMSG_GetSecondarySignal_FuncType            = mccdll_PtrUINTParam_FuncType;
using MCCMSG_SetSecondarySignalGain_FuncType        = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSecondarySignalGain_FuncType        = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_SetSecondarySignalLPF_FuncType         = mccdll_DoubleParam_FuncType;
using MCCMSG_GetSecondarySignalLPF_FuncType         = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_BuildErrorText_FuncType                = BOOL (WINAPI *)(HMCCMSG, int, LPSTR, UINT);
using MCCMSG_SetBridgeBalEnable_FuncType            = mccdll_BoolParam_FuncType;
using MCCMSG_GetBridgeBalEnable_FuncType            = mccdll_PtrBoolParam_FuncType;
using MCCMSG_SetBridgeBalResist_FuncType            = mccdll_DoubleParam_FuncType;
using MCCMSG_GetBridgeBalResist_FuncType            = mccdll_PtrDoubleParam_FuncType;
using MCCMSG_AutoBridgeBal_FuncType                 = mccdll_NoParam_FunctType;

#define DECLARE_FUNC_PTR(A)         \
 extern A ##_FuncType A ##_FuncPtr;

DECLARE_FUNC_PTR(MCCMSG_CheckAPIVersion)
DECLARE_FUNC_PTR(MCCMSG_CreateObject)
DECLARE_FUNC_PTR(MCCMSG_DestroyObject)
DECLARE_FUNC_PTR(MCCMSG_SetTimeOut)
DECLARE_FUNC_PTR(MCCMSG_FindFirstMultiClamp)
DECLARE_FUNC_PTR(MCCMSG_FindNextMultiClamp)
DECLARE_FUNC_PTR(MCCMSG_SelectMultiClamp)
DECLARE_FUNC_PTR(MCCMSG_SetMode)
DECLARE_FUNC_PTR(MCCMSG_GetMode)
DECLARE_FUNC_PTR(MCCMSG_SetModeSwitchEnable)
DECLARE_FUNC_PTR(MCCMSG_GetModeSwitchEnable)
DECLARE_FUNC_PTR(MCCMSG_GetFeedbackResistorVC1)
DECLARE_FUNC_PTR(MCCMSG_GetFeedbackResistorIC1)
DECLARE_FUNC_PTR(MCCMSG_GetFeedbackResistorVC2)
DECLARE_FUNC_PTR(MCCMSG_GetFeedbackResistorIC2)
DECLARE_FUNC_PTR(MCCMSG_SetHoldingEnable)
DECLARE_FUNC_PTR(MCCMSG_GetHoldingEnable)
DECLARE_FUNC_PTR(MCCMSG_SetHolding)
DECLARE_FUNC_PTR(MCCMSG_GetHolding)
DECLARE_FUNC_PTR(MCCMSG_SetTestSignalEnable)
DECLARE_FUNC_PTR(MCCMSG_GetTestSignalEnable)
DECLARE_FUNC_PTR(MCCMSG_SetTestSignalAmplitude)
DECLARE_FUNC_PTR(MCCMSG_GetTestSignalAmplitude)
DECLARE_FUNC_PTR(MCCMSG_SetTestSignalFrequency)
DECLARE_FUNC_PTR(MCCMSG_GetTestSignalFrequency)
DECLARE_FUNC_PTR(MCCMSG_AutoPipetteOffset)
DECLARE_FUNC_PTR(MCCMSG_SetPipetteOffset)
DECLARE_FUNC_PTR(MCCMSG_GetPipetteOffset)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCurrentInjEnable)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCurrentInjEnable)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCurrentInjLevel)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCurrentInjLevel)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCurrentInjSettlingTime)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCurrentInjSettlingTime)
DECLARE_FUNC_PTR(MCCMSG_SetFastCompCap)
DECLARE_FUNC_PTR(MCCMSG_GetFastCompCap)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCompCap)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCompCap)
DECLARE_FUNC_PTR(MCCMSG_SetFastCompTau)
DECLARE_FUNC_PTR(MCCMSG_GetFastCompTau)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCompTau)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCompTau)
DECLARE_FUNC_PTR(MCCMSG_SetSlowCompTauX20Enable)
DECLARE_FUNC_PTR(MCCMSG_GetSlowCompTauX20Enable)
DECLARE_FUNC_PTR(MCCMSG_AutoFastComp)
DECLARE_FUNC_PTR(MCCMSG_AutoSlowComp)
DECLARE_FUNC_PTR(MCCMSG_SetNeutralizationEnable)
DECLARE_FUNC_PTR(MCCMSG_GetNeutralizationEnable)
DECLARE_FUNC_PTR(MCCMSG_SetNeutralizationCap)
DECLARE_FUNC_PTR(MCCMSG_GetNeutralizationCap)
DECLARE_FUNC_PTR(MCCMSG_SetWholeCellCompEnable)
DECLARE_FUNC_PTR(MCCMSG_GetWholeCellCompEnable)
DECLARE_FUNC_PTR(MCCMSG_SetWholeCellCompCap)
DECLARE_FUNC_PTR(MCCMSG_GetWholeCellCompCap)
DECLARE_FUNC_PTR(MCCMSG_SetWholeCellCompResist)
DECLARE_FUNC_PTR(MCCMSG_GetWholeCellCompResist)
DECLARE_FUNC_PTR(MCCMSG_AutoWholeCellComp)
DECLARE_FUNC_PTR(MCCMSG_SetRsCompEnable)
DECLARE_FUNC_PTR(MCCMSG_GetRsCompEnable)
DECLARE_FUNC_PTR(MCCMSG_SetRsCompBandwidth)
DECLARE_FUNC_PTR(MCCMSG_GetRsCompBandwidth)
DECLARE_FUNC_PTR(MCCMSG_SetRsCompCorrection)
DECLARE_FUNC_PTR(MCCMSG_GetRsCompCorrection)
DECLARE_FUNC_PTR(MCCMSG_SetRsCompPrediction)
DECLARE_FUNC_PTR(MCCMSG_GetRsCompPrediction)
DECLARE_FUNC_PTR(MCCMSG_SetOscKillerEnable)
DECLARE_FUNC_PTR(MCCMSG_GetOscKillerEnable)
DECLARE_FUNC_PTR(MCCMSG_SetPrimarySignal)
DECLARE_FUNC_PTR(MCCMSG_GetPrimarySignal)
DECLARE_FUNC_PTR(MCCMSG_SetPrimarySignalGain)
DECLARE_FUNC_PTR(MCCMSG_GetPrimarySignalGain)
DECLARE_FUNC_PTR(MCCMSG_SetPrimarySignalLPF)
DECLARE_FUNC_PTR(MCCMSG_GetPrimarySignalLPF)
DECLARE_FUNC_PTR(MCCMSG_SetPrimarySignalHPF)
DECLARE_FUNC_PTR(MCCMSG_GetPrimarySignalHPF)
DECLARE_FUNC_PTR(MCCMSG_SetScopeSignalLPF)
DECLARE_FUNC_PTR(MCCMSG_GetScopeSignalLPF)
DECLARE_FUNC_PTR(MCCMSG_SetSecondarySignal)
DECLARE_FUNC_PTR(MCCMSG_GetSecondarySignal)
DECLARE_FUNC_PTR(MCCMSG_SetSecondarySignalGain)
DECLARE_FUNC_PTR(MCCMSG_GetSecondarySignalGain)
DECLARE_FUNC_PTR(MCCMSG_SetSecondarySignalLPF)
DECLARE_FUNC_PTR(MCCMSG_GetSecondarySignalLPF)
DECLARE_FUNC_PTR(MCCMSG_BuildErrorText)
DECLARE_FUNC_PTR(MCCMSG_SetBridgeBalEnable)
DECLARE_FUNC_PTR(MCCMSG_GetBridgeBalEnable)
DECLARE_FUNC_PTR(MCCMSG_SetBridgeBalResist)
DECLARE_FUNC_PTR(MCCMSG_GetBridgeBalResist)
DECLARE_FUNC_PTR(MCCMSG_AutoBridgeBal)

#undef DECLARE_FUNC_PTR

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
