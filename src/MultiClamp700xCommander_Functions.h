/**
 * @file MultiClamp700xCommander__Functions.h
 * Headers for MultiClamp700xCommander__Functions.cpp, which provides
 * external functions to Igor for communicating with MultiClamp Commander.

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

// Utility functions
int IsValidNumber(double value);

// Function parameter structures

// double Function() parameters
#pragma pack(2)
struct MCC_ReturnDouble_Params {
	// No parameters
	double result;		// Return value
};
typedef struct MCC_ReturnDouble_Params MCC_ReturnDouble_Params;
#pragma pack()

int Generic_ReturnDouble_Wrapper(MCC_ReturnDouble_Params* p, MCCFunctions mccFx);


// double Function(double) parameters.
#pragma pack(2)
struct MCC_P1Double_ReturnDouble_Params {
	double p1; // p1 is the first (and only) parameter.
	double result;		// Return value
};
typedef struct MCC_P1Double_ReturnDouble_Params MCC_P1Double_ReturnDouble_Params;
#pragma pack()

int Generic_P1Double_ReturnDouble_Wrapper(MCC_P1Double_ReturnDouble_Params* p, MCCFunctions mccFx);



// MCC_SelectMultiClamp700B()
#pragma pack(2)
struct MCC_SelectMultiClamp700BParams {
	double channelID;			// p2
	Handle serialNumberStrHandle;		// p1: serialNumberString
	double result;
};
typedef struct MCC_SelectMultiClamp700BParams MCC_SelectMultiClamp700BParams;
#pragma pack()

int MCC_SelectMultiClamp700B(MCC_SelectMultiClamp700BParams* p);
