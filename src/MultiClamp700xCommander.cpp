/**
	\file MultiClamp700xCommander.cpp

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

#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "MultiClamp700xCommander.h"

#include "MultiClamp700xCommander_Functions.h"
#include "MultiClamp700xCommander_Operations.h"

/* Global Variables */
UINT gExecuting = FALSE;				// Flag variable that reflects whether the XOP is in the middle of executing and used to prevent recursion.


namespace  {

// Static MCC DLL handle.
HMCCMSG s_hMCCmsg = NULL;

// Utility functions
/**
	\brief Stores an error message for \a nError in \a sTxtBuf.

	\param hMCCmsg
	A MCC DLL handle.
	\param nError
	A MCC error code.
	\a sTxtBuf
	A text buffer of size \a uMaxLen into which the error message string will be placed.
	\param uMaxLen
	The size of \a sTxtBuf in bytes.
*/
void GetMCCErrorMessage(HMCCMSG hMCCmsg, int nError, LPSTR	sTxtBuf, UINT uMaxLen) {
	MCCMSG_BuildErrorText(hMCCmsg, nError, sTxtBuf, uMaxLen);
}

/**
	\brief Prints the text of MCC error message \a nError to
	the Igor command line.

	\param hMCCmsg
	A MCC DLL handle.
	\param nError
	A MCC error code.
*/
void PrintErrorMessageToCommandLine(HMCCMSG hMCCmsg, int nError) {
	char buffer[256];
	GetMCCErrorMessage(hMCCmsg, nError, buffer, sizeof(buffer));
	XOPNotice(buffer);
	XOPNotice("\r");		// Terminate the line.
}

// NOTE: To enable me to write less code, most external functions
// are handled using the FUNCTION message, not directly.
XOPIORecResult RegisterFunction() {
	int funcIndex;

	funcIndex = (int)GetXOPItem(0);	/* which function invoked ? */
	switch (funcIndex) {
		case FX_MCC_SelectMultiClamp700B:						/* MCC_SelectMultiClamp700B(p1, p2) */
			return (XOPIORecResult)MCC_SelectMultiClamp700B;
			break;
	}
	return 0;
}

// Register XOPs operations with Igor.
int RegisterOperations() {
  int err;

  // Register AxonTelegraphFindServers operation.
  if (err = RegisterMCC_FindServers())
    return err;

  // There are no more operations added by this XOP.

  return 0;
}

/**
	\brief Handles calls to functions via the FUNCTION message from Igor.
*/
int DoFunction() {
	int funcIndex;
	void *p;				/* pointer to structure containing function parameters and result */
	int err;				/* error code returned by function */

	funcIndex = (int)GetXOPItem(0);	/* which function invoked ? */
	p = (void*)GetXOPItem(1);		/* get pointer to params/result */
	switch (funcIndex) {
		// Functions following prototype double Function()
		case FX_MCC_GetHoldingEnable:	// fall through
		case FX_MCC_GetHolding:	// fall through
		case FX_MCC_GetMode:	// fall through
		case FX_MCC_GetBridgeBalEnable:	// fall through
		case FX_MCC_GetBridgeBalResist:	// fall through
		case FX_MCC_AutoBridgeBal:		// fall through
		case FX_MCC_GetNeutralizationEnable:	// fall through
		case FX_MCC_GetNeutralizationCap:	// fall through
		case FX_MCC_GetWholeCellCompEnable:	// fall through
		case FX_MCC_GetWholeCellCompCap:	// fall through
		case FX_MCC_GetWholeCellCompResist:	// fall through
		case FX_MCC_AutoWholeCellComp:	// fall through
		case FX_MCC_GetRsCompEnable:	// fall through
		case FX_MCC_GetRsCompBandwidth:	// fall through
		case FX_MCC_GetRsCompCorrection:	// fall through
		case FX_MCC_GetRsCompPrediction:	// fall through
		case FX_MCC_GetOscKillerEnable:	// fall through
		case FX_MCC_GetPrimarySignalGain:	// fall through
		case FX_MCC_GetPrimarySignalLPF:	// fall through
		case FX_MCC_GetPrimarySignalHPF:	// fall through
		case FX_MCC_GetSecondarySignalGain:	// fall through
		case FX_MCC_GetSecondarySignalLPF:	// fall through
		case FX_MCC_AutoPipetteOffset:	// fall through
		case FX_MCC_GetPipetteOffset:	// fall through
		case FX_MCC_GetFastCompCap:	// fall through
		case FX_MCC_GetSlowCompCap:	// fall through
		case FX_MCC_GetFastCompTau:	// fall through
		case FX_MCC_GetSlowCompTau:	// fall through
		case FX_MCC_GetSlowCompTauX20Enable:	// fall through
		case FX_MCC_AutoFastComp:	// fall through
		case FX_MCC_AutoSlowComp:	// fall through
		case FX_MCC_GetSlowCurrentInjEnable:	// fall through
		case FX_MCC_GetSlowCurrentInjLevel:	// fall through
		case FX_MCC_GetSlowCurrentInjSetlTime:	// fall through

			err = Generic_ReturnDouble_Wrapper((MCC_ReturnDouble_Params*)p, static_cast<MCCFunctions>(funcIndex));
			break;

		// Functions following prototype double Function(double)
		case FX_MCC_SetTimeoutMs:	// fall through
		case FX_MCC_SetHoldingEnable:	// fall through
		case FX_MCC_SetHolding:		// fall through
		case FX_MCC_SetMode:		// fall through
		case FX_MCC_SetBridgeBalEnable:		// fall through
		case FX_MCC_SetBridgeBalResist:		// fall through
		case FX_MCC_SetNeutralizationEnable:		// fall through
		case FX_MCC_SetNeutralizationCap:		// fall through
		case FX_MCC_SetWholeCellCompEnable:	// fall through
		case FX_MCC_SetWholeCellCompCap:	// fall through
		case FX_MCC_SetWholeCellCompResist:	// fall through
		case FX_MCC_SetRsCompEnable:	// fall through
		case FX_MCC_SetRsCompBandwidth:	// fall through
		case FX_MCC_SetRsCompCorrection:	// fall through
		case FX_MCC_SetRsCompPrediction:	// fall through
		case FX_MCC_SetOscKillerEnable:	// fall through
		case FX_MCC_SetPrimarySignalGain:	// fall through
		case FX_MCC_SetPrimarySignalLPF:	// fall through
		case FX_MCC_SetSecondarySignalGain:	// fall through
		case FX_MCC_SetSecondarySignalLPF:	// fall through
		case FX_MCC_SetPrimarySignalHPF:	// fall through
		case FX_MCC_SetPipetteOffset:	// fall through
		case FX_MCC_SetFastCompCap:	// fall through
		case FX_MCC_SetSlowCompCap:	// fall through
		case FX_MCC_SetFastCompTau:	// fall through
		case FX_MCC_SetSlowCompTau:	// fall through
		case FX_MCC_SetSlowCompTauX20Enable:	// fall through
		case FX_MCC_SetSlowCurrentInjEnable:	// fall through
		case FX_MCC_SetSlowCurrentInjLevel:	// fall through
		case FX_MCC_SetSlowCurrentInjSettlingTime:	// fall through

			err = Generic_P1Double_ReturnDouble_Wrapper((MCC_P1Double_ReturnDouble_Params*)p, static_cast<MCCFunctions>(funcIndex));
			break;


		default:
			// Should never get here.
			XOPNotice("BUG: MultiClamp700xCommander XOP, DoFunction(). Unexpected value for funcIndex.\r");
			return MCC_XOP_BUG;
	}
	return(err);
}

/*	XOPQuit()

Called to clean things up when XOP is about to be disposed.
This happens when Igor is quitting.
*/
void XOPQuit(void) {
	if (s_hMCCmsg != NULL) {
		// destroy DLL handle
		MCCMSG_DestroyObject_FuncPtr(s_hMCCmsg);
		s_hMCCmsg = NULL;
	}
}

} // anonymous namespace

/*	XOPEntry()

	This is the entry point from the host application to the XOP for all messages after the
	INIT message.
*/
extern "C" void XOPEntry(void)
{
	XOPIORecResult result = 0;

	switch (GetXOPMessage()) {
		case CLEANUP:								// XOP about to be disposed of.
			XOPQuit();								// Do any necessary cleanup.
			break;

		case FUNCADDRS:
			result = RegisterFunction();
			break;

		case FUNCTION:
			// NOTE: To enable me to write less code, most external functions
			// are handled in this message.
			result = DoFunction();
			break;
	}
	SetXOPResult(result);
}

/*	XOPMain(ioRecHandle)

	This is the initial entry point at which the host application calls XOP.
	The message sent by the host must be INIT.

	XOPMain does any necessary initialization and then sets the XOPEntry field of the
	ioRecHandle to the address to be called for future messages.
*/

HOST_IMPORT int XOPMain(IORecHandle ioRecHandle)			// The use of XOPMain rather than main means this XOP requires Igor Pro 6.20 or later
{
	XOPInit(ioRecHandle);					// Do standard XOP initialization
	SetXOPEntry(XOPEntry);					// Set entry point for future calls

	if (igorVersion < 700) {		// Requires Igor Pro 7.00 or later
		SetXOPResult(OLD_IGOR);
		return EXIT_FAILURE;
	}

  // Register the XOP's operations.
	if (int ret = RegisterOperations()) {
		SetXOPResult(ret);
		return EXIT_FAILURE;
	}

	HMODULE hLib = LoadLibrary("AxMultiClampMsg.dll");
	(void)hLib;		// Prevent unused variable compiler warning.

	// check the API version matches the expected value
	if (!MCCMSG_CheckAPIVersion(MCCMSG_APIVERSION_STR))
	{
		SetXOPResult(WRONG_MCC_API_VERSION);
		return EXIT_FAILURE;
	}

	// create DLL handle
	int nError = MCCMSG_ERROR_NOERROR;
	s_hMCCmsg = MCCMSG_CreateObject(&nError);
	if (!s_hMCCmsg)
	{
		SetXOPResult(FAILURE_CREATING_MCC_DLL_HANDLE);
		return EXIT_FAILURE;
	}

	return 0;

	SetXOPResult(0);
	return EXIT_SUCCESS;
}

/**
* Utility function that can be called from functions in other
* files so that those functions can access the global MCC DLL handle.
*/
HMCCMSG GetMCCDLLHandle() {
	return s_hMCCmsg;
}

/**
	\brief Returns an XOP error code corresponding to the MCC error
	code \a mccError.
*/
int MCCErrorCodeToXOPErrorCode(int mccError) {
	switch (mccError) {
		case MCCMSG_ERROR_NOERROR:
			return 0;		// No error
			break;

		case MCCMSG_ERROR_OUTOFMEMORY:
			return XOP_MCCMSG_ERROR_OUTOFMEMORY;
			break;

		case MCCMSG_ERROR_MCCNOTOPEN:
			return XOP_MCCMSG_ERROR_MCCNOTOPEN;
			break;

		case MCCMSG_ERROR_INVALIDDLLHANDLE:
			return XOP_MCCMSG_ERROR_INVALIDDLLHANDLE;
			break;

		case MCCMSG_ERROR_INVALIDPARAMETER:
			return XOP_MCCMSG_ERROR_INVALIDPARAMETER;
			break;

		case MCCMSG_ERROR_MSGTIMEOUT:
			return XOP_MCCMSG_ERROR_MSGTIMEOUT;
			break;

		case MCCMSG_ERROR_MCCCOMMANDFAIL:
			return XOP_MCCMSG_ERROR_MCCCOMMANDFAIL;
			break;

		default:
			return 0;
			break;
	}

	// Should never get here.
	return 0;
}
