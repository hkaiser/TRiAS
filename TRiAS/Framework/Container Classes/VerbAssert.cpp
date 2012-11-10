// VerbAssert.CPP

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#include "StdAfx.h"

#include "DumpBuffer.h"
#include "AssertDlg.h"
#include "PE_Debug.h"


void DumpCallsStack (DumpBuffer& dumpBuffer)
{
const char* separator = "------------------------------------------------------------------\r\n";
static PE_Debug PE_debug;

	dumpBuffer.Printf ("Call stack:\r\n");
	dumpBuffer.Printf (separator);

// The structure of the stack frames is the following:
// EBP -> parent stack frame EBP
//        return address for this call ( = caller )
// The chain can be navigated iteratively, after the
// initial value of EBP is loaded from the register
DWORD parentEBP;

	__asm MOV parentEBP, EBP

// Skip the first EBP as it points to AssertionFailed, which is
// uninteresting for the user
	parentEBP = *(DWORD*)parentEBP;
	do {
	BYTE* caller = *((BYTE**)parentEBP + 1);

		parentEBP = *(DWORD*)parentEBP ;
    
	// Get the instance handle of the module where caller belongs to
	MEMORY_BASIC_INFORMATION mbi;

		VirtualQuery (caller, &mbi, sizeof(mbi));
    
	// The instance handle is equal to the allocation base in Win32
    HINSTANCE hInstance = (HINSTANCE)mbi.AllocationBase;
	
		if (hInstance)
			PE_debug.DumpDebugInfo (dumpBuffer, caller, hInstance);
    else
		break; // End of the call chain
	} while (TRUE);

	dumpBuffer.Printf (separator);
	PE_debug.ClearReport();  // Prepare for future calls
}


// This ought to be local to VerboseAssert, but it
// causes problems in Visual C++ (in the CRTL init phase)
DumpBuffer dumpBuffer;

_CTR_ENTRY32 BOOL WINAPI VerboseAssertFailedLine (LPCSTR lpszExpr, LPCSTR file, int line)
{
	dumpBuffer.Clear();
	dumpBuffer.StaticPrintf ("File: %hs\r\nLine: %d\r\n(%hs)\r\n", file, line, lpszExpr);
	DumpCallsStack (dumpBuffer);  

AssertDialog dlg (dumpBuffer);
AssertDialog::Choice res = dlg.GetUserChoice();

	switch (res) {
    case AssertDialog::abort:
		abort();     // should not return (but otherwise DebugBreak)
		break;

    case AssertDialog::ignore:
		return false;

    case AssertDialog::debug:
		break;	// DebugBreak;

	default:
	// Not reached, cannot use assert!
		MessageBeep (0);
	}
	return true;
}
