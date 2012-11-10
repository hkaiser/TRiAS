///////////////////////////////////////////////////////////////////////////////
// StatusIndExt.cpp: StatusIndicator support

#include "precomp.hxx"

#include <istatus.h>
#include <statguid.h>
#include <TRiASHelper.h>

#include "olebsext.hxx"			// function  prototypes

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// StatusIndicator
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(ProgressIndicator);
DefineSmartInterface(ProgressIndicator2);

// ----------------------------------------------------------------------------
// StatusIndicator_refcnt
// ----------------------------------------------------------------------------
void StatusIndicator_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(StatusIndicator_refcnt);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

			try {
			WTriasXtensionSite XtsnSite;
			WProgressIndicator Status;

				THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite (XtsnSite.ppi()));
				THROW_FAILED_HRESULT(XtsnSite->CreateInstance(
					NULL, CLSID_ProgressIndicator, IID_IProgressIndicator, Status.ppv()));

			HWND hWnd = Status -> InitNew(g_pTE -> hWnd(), PI_INIT_LATER);

				ebSetObject (lpArgs, 0, (DWORD)Status.detach());

			} catch (...) {
				TRACE("Couldn't instantiate StatusIndicator\r\n");
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// StatusIndicator_propget_Caption
// ----------------------------------------------------------------------------
void StatusIndicator_propget_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propget_Caption);

WProgressIndicator Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));
char cbBuffer[_MAX_PATH];
ULONG ulWritten = 0;
HRESULT hr = Status -> RetrieveText (PIFLAG_CAPTION, cbBuffer, _MAX_PATH);

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}
	ebSetString (lpArgs, 0, ebCreateString (hThread, cbBuffer));
}

// ----------------------------------------------------------------------------
// StatusIndicator_propset_Caption
// ----------------------------------------------------------------------------
void StatusIndicator_propset_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propset_Caption);

ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> ChangeText (PIFLAG_CAPTION, lpstr);
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// StatusIndicator_propget_Flags
// ----------------------------------------------------------------------------
void StatusIndicator_propget_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propget_Flags);

WProgressIndicator2 Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));
PIFLAGS rgFlags = (PIFLAGS)0;
HRESULT hr = Status -> get_Flags (&rgFlags);

	if (FAILED(hr))	{
		ebSetLong (lpArgs, 0, 0);
		return;
	}
	ebSetLong (lpArgs, 0, rgFlags);
}

// ----------------------------------------------------------------------------
// StatusIndicator_propset_Flags
// ----------------------------------------------------------------------------
void StatusIndicator_propset_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propset_Flags);

WProgressIndicator2 Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));

	Status -> put_Flags ((PIFLAGS)ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_IncrementPosition
// ----------------------------------------------------------------------------
void StatusIndicator_func_IncrementPosition (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_cmd_IncrementPosition);

WProgressIndicator2 Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));
INT iPercent = 0;
HRESULT hr = Status -> IncrementPosition (&iPercent);

	if (lpArgs[0])	// nur wenn als Function gerufen wurde
		ebSetLong (lpArgs, 0, SUCCEEDED(hr) ? iPercent : 0);
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_InitNew
// ----------------------------------------------------------------------------
void StatusIndicator_func_InitNew (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_func_InitNew);
	// nothing to do here
}

// ----------------------------------------------------------------------------
// StatusIndicator_propget_Field
// ----------------------------------------------------------------------------
DWORD GetFieldFlag (int iField)
{
	switch (iField) {
	default:
	case 1: return PIFLAG_FILE;
	case 2:	return PIFLAG_FILENAME;
	case 3:	return PIFLAG_STATUS;
	case 4:	return PIFLAG_RESULT;
	}
}

void StatusIndicator_propget_Field (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propget_Field);

WProgressIndicator Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));
DWORD dwField = GetFieldFlag(ebGetInt (lpArgs, 2));
char cbBuffer[_MAX_PATH];
ULONG ulWritten = 0;
HRESULT hr = Status -> RetrieveText (dwField, cbBuffer, _MAX_PATH);

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}
	ebSetString (lpArgs, 0, ebCreateString (hThread, cbBuffer));
}

// ----------------------------------------------------------------------------
// StatusIndicator_propset_Field
// ----------------------------------------------------------------------------
void StatusIndicator_propset_Field (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_propset_Field);

DWORD dwField = GetFieldFlag (ebGetInt (lpArgs, 2));
ebHSUB hStr = ebGetString (lpArgs, 3);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> ChangeText (dwField, lpstr);
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_ChangeText
// ----------------------------------------------------------------------------
void StatusIndicator_func_ChangeText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_func_ChangeText);

DWORD dwField = ebGetLong (lpArgs, 2);
ebHSUB hStr = ebGetString (lpArgs, 3);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> ChangeText (dwField, lpstr);
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_RetrieveText
// ----------------------------------------------------------------------------
void StatusIndicator_func_RetrieveText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_func_RetrieveText);

DWORD dwField = ebGetLong (lpArgs, 2);
char cbBuffer[_MAX_PATH];
ULONG ulWritten = 0;
HRESULT hr = ((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> RetrieveText (dwField, cbBuffer, _MAX_PATH);

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}
	ebSetString (lpArgs, 0, ebCreateString (hThread, cbBuffer));
}

// ----------------------------------------------------------------------------
// StatusIndicator_cmd_Restart
// ----------------------------------------------------------------------------
void StatusIndicator_cmd_Restart (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_cmd_Restart);

ULONG ulMin = (ULONG)ebGetLong (lpArgs, 2);
ULONG ulMax = (ULONG)ebGetLong (lpArgs, 3);
DWORD dwFlags = (DWORD)ebGetLong (lpArgs, 4);

	((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> Restart (ulMin, ulMax, dwFlags);
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_SetPosition
// ----------------------------------------------------------------------------
void StatusIndicator_func_SetPosition (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_func_SetPosition);

ULONG ulPos = ebGetLong (lpArgs, 2);
int iPercent = ((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> SetPosition (ulPos);

	if (NULL != lpArgs[0]) 
		ebSetInt (lpArgs, 0, iPercent);
}

// ----------------------------------------------------------------------------
// StatusIndicator_func_WasCaceled
// ----------------------------------------------------------------------------
void StatusIndicator_func_WasCaceled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_func_WasCaceled);

bool fBreak = ((IProgressIndicator *)ebGetObject (lpArgs, 1)) -> WasCanceled();

	ebSetBool (lpArgs, 0, fBreak);
}

// ----------------------------------------------------------------------------
// StatusIndicator_method_Show
// ----------------------------------------------------------------------------
void StatusIndicator_method_Show (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_method_Show);

WProgressIndicator2 Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));

	Status -> Show();
}

// ----------------------------------------------------------------------------
// StatusIndicator_method_Hide
// ----------------------------------------------------------------------------
void StatusIndicator_method_Hide (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StatusIndicator_method_Hide);

WProgressIndicator2 Status ((IProgressIndicator *)ebGetObject (lpArgs, 1));

	Status -> Hide();
}



