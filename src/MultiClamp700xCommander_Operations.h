/**
 * @file MultiClamp700xCommander__Operations.h
 * Headers for MultiClamp700xCommander__Operations.cpp, which provides
 * external operations to Igor for communicating with MultiClamp Commander.

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
#include <vector>

class MultiClamp;

// Operation template: MCC_FindServers /Z[=number:errorType]

// Runtime param structure for MCC_FindServers operation.
#pragma pack(2)	// All structures passed to Igor are two-byte aligned.
struct MCC_FindServersRuntimeParams {
	// Flag parameters.

	// Parameters for /Z flag group.
	int ZFlagEncountered;
	double errorType;						// Optional parameter.
	int ZFlagParamsSet[1];

	// Main parameters.

	// These are postamble fields that Igor sets.
	int calledFromFunction;					// 1 if called from a user function, 0 otherwise.
	int calledFromMacro;					// 1 if called from a macro, 0 otherwise.
};
typedef struct MCC_FindServersRuntimeParams MCC_FindServersRuntimeParams;
typedef struct MCC_FindServersRuntimeParams* MCC_FindServersRuntimeParamsPtr;
#pragma pack()		// Reset structure alignment to default.


// Operation error type constants.
#define MCC_ERROR_YES			 0		// Create a run time error on error conditions.
#define MCC_ERROR_IGNORE		 1		// Ignore all errors

// Constants
static const int defaultErrorType = MCC_ERROR_YES;			// Default to display errors.

// Function declarations.
int ExecuteMCC_FindServers(MCC_FindServersRuntimeParamsPtr p);
int RegisterMCC_FindServers();

// Utility functions.
double Process_Z_FlagValue(double valueFromUser);
int CreateMultiClampListWave(std::vector<MultiClamp> multiClampVector);
