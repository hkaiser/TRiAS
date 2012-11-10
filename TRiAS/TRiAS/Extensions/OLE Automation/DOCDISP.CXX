// Collection der geöffneten Dokumente (ProgrammierInterface) -----------------
// File: DOCDISP.CXX

#include "precomp.hxx"

#include <Atl/Ciid.h>

#include <dirisole.h>
#include <resstrg.h>
#include <hdrentrx.hxx>
#include <xtensnn.h>
#include <Com/MemoryHelper.h>

#include "Strings.h"

#include "viewarry.hxx"
#include "enuviews.hxx"
#include "view.hxx"
#include "views.hxx"

#include "clsarray.hxx"
#include "enumclss.hxx"
#include "class.hxx"
#include "classes.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "obwarray.hxx"
#include "enumobws.hxx"
#include "objwin.hxx"
#include "objwins.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
bool InternalCoords (double dblX, double dblY, LONG *plX, LONG *plY);

///////////////////////////////////////////////////////////////////////////////
// benötige Interfaces
DefineSmartInterface(Dispatch);			// WDispatch
DefineSmartInterface2(_DGeoObjects, IID_DGeoObjects);	// W_IGeoObjects
DefineSmartInterface2(DGeoFeature, IID_DGeoFeature);

DefineSmartInterface(TRiASProject);		// WTRiASProject

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CGeoDoc :: get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_isA");
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_Document;
	return NOERROR;
}

STDMETHODIMP CGeoDoc::get_Value (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Value");

	if (NULL == pbstrValue) return E_POINTER;

// Testen, ob Projekt ge÷ffnet
	if (NULL == ProjectName()) 
		return E_UNEXPECTED;

// HeaderEntry abfragen
GEODBHDRENTRY DBEntry;
char cbBuffer[_MAX_PATH+1];
CString rsCaption;

	TRY {
		rsCaption.LoadString (IDS_CAPTIONTEXT);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
	
	INITSTRUCT (DBEntry, GEODBHDRENTRY);
	strcpy (DBEntry.hdrKey, rsCaption);
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;

#if defined(DEX_ReadHeaderEntry)
	if (DEX_ReadHeaderEntry (HACTPROJECT, DBEntry) != 0)
		return get_FullName (pbstrValue); // kein Caption gegeben, FullPath verwenden
#else
	if (DEX_ReadGeoDBHdrEntry(DBEntry) != 0)
		return get_FullName (pbstrValue); // kein Caption gegeben, FullPath verwenden
#endif // DEX_ReadHeaderEntry

// Caption ins Resultat kopieren
	*pbstrValue = SysAllocString (WideString(cbBuffer));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Das StandardProperty Parent liefert das übergeordnete Objekt, über welches 
// diese DocumenCollection angelegt wurde.
STDMETHODIMP CGeoDoc :: get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Objekten übergeordnete)
STDMETHODIMP CGeoDoc :: get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoDoc :: put_Parent (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Parent");
	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc :: put_Application (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Application");
	return E_NOTIMPL;
}

// Eigentliches IDispatchInterface --------------------------------------------
// Caption befragen, welchen Namen das Kind hat, ansonsten FullPath
STDMETHODIMP CGeoDoc::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Name");

	if (NULL == pbstrValue) return E_POINTER;

// Testen, ob Projekt geöffnet
	*pbstrValue = NULL;
	if (NULL == ProjectName()) 
		return E_UNEXPECTED;

string strName = ProjectName();

	strName = get_name(strName) + get_ext(strName);

	USES_CONVERSION;
	*pbstrValue = SysAllocString (A2OLE(strName.c_str()));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Liefert den aktuellen Pfad, in dem sich das Projekt befindet ---------------
STDMETHODIMP CGeoDoc::get_Path (BSTR *pbstrPath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Path");

	if (NULL == pbstrPath) return E_POINTER;

// Testen, ob Projekt geöffnet ist
	if (NULL == ProjectName()) 
		return E_UNEXPECTED;

string strName = ProjectName();

	USES_CONVERSION;
	strName = get_drive(strName) + get_path(strName);
	*pbstrPath =  SysAllocString (A2OLE(strName.c_str()));
	if (NULL == *pbstrPath)
		return E_OUTOFMEMORY;

return NOERROR;
}

// Liefert den vollen DateiNamen des Projektes (Steuerdatei) ------------------
STDMETHODIMP CGeoDoc::get_FullName (BSTR *pbstrVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_FullName");

	if (NULL == pbstrVal) return E_POINTER;

	USES_CONVERSION;
	*pbstrVal = NULL;
	if (NULL != ProjectName()) 
		*pbstrVal = SysAllocString (A2OLE(ProjectName()));

	if (NULL == *pbstrVal)
		return E_OUTOFMEMORY;

return NOERROR;
}

STDMETHODIMP CGeoDoc::get_ActiveViewName (BSTR *pbstrView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_ActiveViewName");

	if (NULL == pbstrView) return E_POINTER;

CString strActView; 

	TRY {
		strActView.GetBuffer (_MAX_PATH);

	char *pView = DEX_GetActiveSight ((LPCSTR)strActView);

		strActView.ReleaseBuffer();
		if (NULL == pView)
			strActView = g_cbNil;		// keine Aktuelle Ansicht

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
		
	USES_CONVERSION;
	*pbstrView = SysAllocString (A2OLE(strActView));
	if (NULL == *pbstrView)
		return E_OUTOFMEMORY;
	
return NOERROR;
}

STDMETHODIMP CGeoDoc::put_ActiveViewName (BSTR bstrView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_ActiveViewName");

	if (SysStringLen(bstrView) == 0)
		return E_FAIL;		// einfach nichts machen

	USES_CONVERSION;
	if (!DEX_SelectNewSight(OLE2A(bstrView)))
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CGeoDoc::get_ObjectCount (long *plCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_ObjectCount");

	if (NULL == plCnt) return E_POINTER;

	*plCnt = DEX_GetObjectCount();
	return NOERROR;
}

STDMETHODIMP CGeoDoc::get_ViewCount (long *plCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_ViewCount");

	if (NULL == plCnt) return E_POINTER;

	*plCnt = DEX_GetViewCount();
	return NOERROR;
}

STDMETHODIMP CGeoDoc::get_ClassCount (long *plCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_ClassCount");

	if (NULL == plCnt) return E_POINTER;

	*plCnt = DEX_GetClassCount();
	return NOERROR;
}

// Abschließen des geöffneten Dokumentes --------------------------------------
STDMETHODIMP CGeoDoc::CloseIt (VARIANT /*vtSave*/, VARIANT /*vtFName*/)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::CloseIt");

	Remove();		// -->> notification deletes from DocTree
	return NOERROR;
}

// Abspeichern des aktuellen Standes des Projektes ----------------------------
STDMETHODIMP CGeoDoc::Save (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::Save");

	DEX_FlushModifications();
	return NOERROR;
}

// Abspeichern des Projektes unter einem anderen NAmen ------------------------
STDMETHODIMP CGeoDoc :: SaveAs (BSTR bstrName)
{
	// sorry, not implemented
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SaveAs");
	return E_NOTIMPL;
}

// Liefert HeaderEintrag aus GeoDB Header -------------------------------------
STDMETHODIMP CGeoDoc::GetHeaderEntry (BSTR bstrKey, BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetHeaderEntry");

	if (NULL == pbstrText) 
		return E_POINTER;
	*pbstrText = NULL;

GEODBHDRENTRY DBEntry;
char cbBuffer[_MAX_PATH+1];

	INITSTRUCT (DBEntry, GEODBHDRENTRY);
	strncpy (DBEntry.hdrKey, AnsiString(bstrKey), 16);
	
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;
	
	if (EC_OKAY == DEX_ReadGeoDBHdrEntry (DBEntry)) {
	// Entry ins Resultat kopieren
		*pbstrText = SysAllocString(WideString(DBEntry.lphdrText));
		if (NULL == *pbstrText)
			return E_OUTOFMEMORY;
	} 

return NOERROR;
}

STDMETHODIMP CGeoDoc::GetHeaderEntry2 (BSTR bstrKey, HEADERFLAG *prgFlags, 
	BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetHeaderEntry");

	if (NULL == pbstrText || NULL == prgFlags) 
		return E_POINTER;
	*pbstrText = NULL;

GEODBHDRENTRYEX DBEntry;
char cbBuffer[_MAX_PATH+1];

	INITSTRUCT (DBEntry, GEODBHDRENTRYEX);
	strncpy (DBEntry.hdrKey, AnsiString(bstrKey), 16);
	
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;
	
	if (EC_OKAY == DEX_ReadGeoDBHdrEntry (DBEntry)) {
	// Entry ins Resultat kopieren
		*pbstrText = SysAllocString(WideString(DBEntry.lphdrText));
		if (NULL == *pbstrText)
			return E_OUTOFMEMORY;
		*prgFlags = HEADERFLAG(DBEntry.dwFlags);
	} 
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert HeaderEintrag aus GeoDB Header 
STDMETHODIMP CGeoDoc::GetHeaderEntryEx (BSTR bstrDataSource, BSTR bstrKey, BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetHeaderEntryEx");

	USES_CONVERSION;
	if (NULL == pbstrText) 
		return E_POINTER;
	*pbstrText = NULL;

GEODBHDRENTRY DBEntry;
char cbBuffer[_MAX_PATH+1];
HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(OLE2A(bstrDataSource));

	if (NULL == hPrDest)
		return E_INVALIDARG;

	INITSTRUCT (DBEntry, GEODBHDRENTRY);
	strncpy (DBEntry.hdrKey, OLE2A(bstrKey), 16);
	
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;
	
	if (EC_OKAY == DEX_ReadHeaderEntry (hPrDest, DBEntry)) {
	// Entry ins Resultat kopieren
		*pbstrText = SysAllocString(A2OLE(DBEntry.lphdrText));
		if (NULL == *pbstrText)
			return E_OUTOFMEMORY;
	} 
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert HeaderEintrag aus GeoDB Header 
STDMETHODIMP CGeoDoc::GetHeaderEntryEx2 (BSTR bstrDataSource, BSTR bstrKey,	
	HEADERFLAG *prgFlags, BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetHeaderEntryEx");

	USES_CONVERSION;
	if (NULL == pbstrText || NULL == prgFlags) 
		return E_POINTER;
	*pbstrText = NULL;
	*prgFlags = HEADERFLAG_Normal;

GEODBHDRENTRYEX DBEntry;
char cbBuffer[_MAX_PATH+1];
HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(OLE2A(bstrDataSource));

	if (NULL == hPrDest)
		return E_INVALIDARG;

	INITSTRUCT (DBEntry, GEODBHDRENTRYEX);
	strncpy (DBEntry.hdrKey, OLE2A(bstrKey), 16);
	
	DBEntry.lphdrText = cbBuffer;
	DBEntry.hdrTextLen = _MAX_PATH;
	
	if (EC_OKAY == DEX_ReadHeaderEntry (hPrDest, DBEntry)) {
	// Entry ins Resultat kopieren
		*pbstrText = SysAllocString(A2OLE(DBEntry.lphdrText));
		if (NULL == *pbstrText)
			return E_OUTOFMEMORY;
		*prgFlags = HEADERFLAG(DBEntry.dwFlags);
	} 
	return NOERROR;
}

// Setzen/Löschen eines HeaderEintrages aus dem GeoDB-Header ------------------
STDMETHODIMP CGeoDoc::SetHeaderEntry (BSTR bstrHeaderKey, VARIANT vHeaderText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SetHeaderEntry");

HeaderEntryX Hdr (AnsiString(bstrHeaderKey));
CComVariant vArg; 
HRESULT hr = vArg.ChangeType (VT_BSTR, &vHeaderText);

	if (FAILED(hr)) {
		hr = vArg.ChangeType (VT_ERROR, &vHeaderText);
		if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) {
		// Eintrag löschen
		ErrCode RC = Hdr.DeleteEntry();

			return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
		} 
	} else {
	// Eintrag verändern
		Hdr.SetEntryText (AnsiString(V_BSTR(&vArg)));

	ErrCode RC = Hdr.WriteBack();

		return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
	}
	return hr;
}

STDMETHODIMP CGeoDoc::SetHeaderEntry2 (BSTR bstrHeaderKey, VARIANT vHeaderText,
	VARIANT vArgFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SetHeaderEntry");

HeaderEntryX Hdr (AnsiString(bstrHeaderKey));
CComVariant vArg; 
HRESULT hr = vArg.ChangeType (VT_BSTR, &vHeaderText);

	if (FAILED(hr)) {
		hr = vArg.ChangeType (VT_ERROR, &vHeaderText);
		if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) {
		// Eintrag löschen
		ErrCode RC = Hdr.DeleteEntry();

			return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
		} 
	} 
	else {
	// Eintrag verändern
	DWORD rgFlags = HEADERFLAG_Normal;
	CComVariant vFlags;

		if (SUCCEEDED(vFlags.ChangeType(VT_I4, &vArgFlags)))
			rgFlags = HEADERFLAG(V_I4(&vFlags));

		Hdr.SetEntryText (AnsiString(V_BSTR(&vArg)));
		Hdr.Flags() = rgFlags;

	ErrCode RC = Hdr.WriteBack();

		return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Setzen/Löschen eines HeaderEintrages aus dem GeoDB-Header 
STDMETHODIMP CGeoDoc::SetHeaderEntryEx (BSTR bstrDataSource, BSTR bstrHeaderKey, VARIANT vHeaderText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SetHeaderEntryEx");

	USES_CONVERSION;

HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(OLE2A(bstrDataSource));

	if (NULL == hPrDest)
		return E_INVALIDARG;

HeaderEntryX Hdr (OLE2A(bstrHeaderKey), hPrDest);
CComVariant vArg; 
HRESULT hr = vArg.ChangeType (VT_BSTR, &vHeaderText);

	if (FAILED(hr)) {
		hr = vArg.ChangeType (VT_ERROR, &vHeaderText);
		if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) {
		// Eintrag löschen
		ErrCode RC = Hdr.DeleteEntry();

			return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
		} 
	} else {
	// Eintrag verändern
		Hdr.SetEntryText (OLE2A(V_BSTR(&vArg)));

	ErrCode RC = Hdr.WriteBack();

		return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Setzen/Löschen eines HeaderEintrages aus dem GeoDB-Header 
STDMETHODIMP CGeoDoc::SetHeaderEntryEx2 (BSTR bstrDataSource, BSTR bstrHeaderKey, 
	VARIANT vHeaderText, VARIANT vArgFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SetHeaderEntryEx2");

	USES_CONVERSION;

HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(OLE2A(bstrDataSource));

	if (NULL == hPrDest)
		return E_INVALIDARG;

HeaderEntryX Hdr (OLE2A(bstrHeaderKey), hPrDest);
CComVariant vArg; 
HRESULT hr = vArg.ChangeType (VT_BSTR, &vHeaderText);

	if (FAILED(hr)) {
		hr = vArg.ChangeType (VT_ERROR, &vHeaderText);
		if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) {
		// Eintrag löschen
		ErrCode RC = Hdr.DeleteEntry();

			return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
		} 
	} 
	else {
	// Eintrag verändern
	DWORD rgFlags = HEADERFLAG_Normal;
	CComVariant vFlags;

		if (SUCCEEDED(vFlags.ChangeType(VT_I4, &vArgFlags)))
			rgFlags = HEADERFLAG(V_I4(&vFlags));

		Hdr.SetEntryText(OLE2A(V_BSTR(&vArg)));
		Hdr.Flags() = rgFlags;

	ErrCode RC = Hdr.WriteBack();

		return (EC_OKAY == RC) ? NOERROR : HRESULT_FROM_ERRCODE(RC);
	}
	return hr;
}

inline 
void CondSwap (long &rlMin, long &rlMax)
{
	if (rlMin > rlMax) {
	long temp = rlMin;

		rlMax = rlMin;
		rlMin = temp;
	}
}

STDMETHODIMP CGeoDoc::RePaint (
	VARIANT vXMin, VARIANT vYMin, VARIANT vXMax, VARIANT vYMax)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::RePaint");

VARIANT vCoord;

	VariantInit (&vCoord);
	
double dXMin, dXMax, dYMin, dYMax;
bool fXMin = false, fXMax = false, fYMin = false, fYMax = false;
HRESULT hr = VariantChangeType (&vCoord, &vXMin, 0, VT_R8);

	if (SUCCEEDED(hr)) { dXMin = V_R8(&vCoord); fXMin = true; }
	VariantChangeType (&vCoord, &vYMin, 0, VT_R8);
	if (SUCCEEDED(hr)) { dYMin = V_R8(&vCoord); fYMin = true; }
	VariantChangeType (&vCoord, &vXMax, 0, VT_R8);
	if (SUCCEEDED(hr)) { dXMax = V_R8(&vCoord); fXMax = true; }
	VariantChangeType (&vCoord, &vYMax, 0, VT_R8);
	if (SUCCEEDED(hr)) { dYMax = V_R8(&vCoord); fYMax = true; }

	if (fXMin && fXMax && fYMin && fYMax) {		// Ausschnitt gegeben
	long iXMin, iXMax, iYMin, iYMax;
	long Pts[2];
	double rcPts[2];
	COORDTRANSFORM CT;
	
		CT.m_Pts = Pts;
		CT.m_rcPts = rcPts;
		
		rcPts[0] = dXMin; rcPts[1] = dYMin;
		DEX_RCtoOC (CT);
		iXMin = Pts[0]; iYMin = Pts[1];
		
		rcPts[0] = dXMax; rcPts[1] = dYMax;
		DEX_RCtoOC (CT);
		iXMax = Pts[0]; iYMax = Pts[1];

	// Korrektur des neues Ausschnittes (kippen)
		CondSwap (iXMin, iXMax);
		CondSwap (iYMin, iYMax);

		RePaint (iXMin, iYMin, iXMax, iYMax);
	} else
		RePaint();

return NOERROR;
}

STDMETHODIMP CGeoDoc::ReBuild (VARIANT vFull)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::ReBuild");

CComVariant v;
HRESULT hr = VariantChangeType (&v, &vFull, 0, VT_BOOL);
bool fFull = false;

	if (SUCCEEDED(hr)) fFull = V_BOOL(&v);

	ReBuildMethod(fFull);
	return NOERROR;
}

// DELETEVIEWCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteViewFromDoc (LPCSTR bName, CGeoDoc *pDoc)
{
	return pDoc -> FDelView (bName);
}

// Liefert eine Collection von Views  ----------------------
typedef struct tagENUMVIEWDATA {
	CGeoViewCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMVIEWDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetViewsFromDoc (LPCSTR bName, BOOL, void *pData)
{
ENUMVIEWDATA *pEOD = (ENUMVIEWDATA *)pData;
CGeoView *pView = pEOD -> m_pDoc -> FGetViewDisp (bName);

	if (pView && pEOD -> m_pCr -> InsertPtr (pView)) 
		((_DView *)pView) -> AddRef(); 

	return true;	
}


extern "C" 
int PASCAL _CreateViewDoc (ENUMVIEWDATA *pEDD, string &bName)
{
CGeoView *pView = pEDD -> m_pDoc -> FGetViewDisp (bName.c_str());
int iResult = CVExists;

	if (pView == NULL) {
		pView = pEDD -> m_pDoc -> FGetViewDisp (bName.c_str(), NULL, VIEWMODE_Add);
		iResult = CVCreated;
	}
	if (pView && pEDD -> m_pCr -> InsertPtr (pView)) {
		((_DView *)pView) -> AddRef();
		return iResult;
	}
	
return CVError;
}


// INITVIEWCOLLECTIONPROC -----------------------------------------------------
extern "C" 
INITVIEWSTATUS PASCAL GetViewsFromDoc (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD, string *pbName)
{
ENUMVIEWDATA EFD;

	EFD.m_pCr = (CGeoViewCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	
	if (pbName == NULL) {							// Complete fill
		ENUMNOKEY ENK;
	
		ENK.eFcn = (ENUMNOKEYPROC)_GetViewsFromDoc;	// zu rufende Funktion
		ENK.ePtr = &EFD;							// durchzureichende Daten

		if(DEX_EnumSights (ENK))			// mit Views füllen
                   	return INITVIEWSTATUS_Exists;
			
	} else {
	int iR = _CreateViewDoc (&EFD, *pbName);
	
		if (iR == CVCreated) return INITVIEWSTATUS_Created;
		if (iR == CVExists) return INITVIEWSTATUS_Exists;
	}

return INITVIEWSTATUS_Error;		
} 

// Liefert die Liste aller in diesem Projekt existierenden Ansichten ----------
STDMETHODIMP CGeoDoc::GetViews (DViews **ppIViews)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetViews");

	TEST_E_POINTER("CGeoDoc::GetViews", ppIViews);

CGeoViews *pCGeoViews = CGeoViews :: CreateInstance (
	(_DDocument *)this, m_pApp, this, GetViewsFromDoc, 
	NULL, DeleteViewFromDoc);

	if (NULL == pCGeoViews) return E_OUTOFMEMORY;

	*ppIViews = (DViews *)pCGeoViews;	// übernimmt AddRef
	return S_OK;
}

// Liefert den Namen der aktuell ausgewählten Ansicht -------------------------
STDMETHODIMP CGeoDoc::GetView (BSTR bstrName, VARIANT vMode, DView **ppIView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetView");

	TEST_E_POINTER("CGeoDoc::GetView", ppIView);

CComVariant vArgMode; 
HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
VIEWMODE rgMode = VIEWMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (VIEWMODE)V_I4(&vArgMode);

	switch (rgMode) {
	case VIEWMODE_Get:		// get default
	case VIEWMODE_Replace:	// remove old, create new
	case VIEWMODE_Add:		// create, if not existent
		{
		CGeoView *pView = FGetViewDisp (AnsiString(bstrName), ppIView, rgMode);

			if (NULL == pView) 
				return E_OUTOFMEMORY;
		}
		break;

	case  VIEWMODE_Remove:		// remove item 
		FDelView (AnsiString(bstrName));
		*ppIView = NULL;
		break;
		
	default:
		return E_UNEXPECTED;
	}
	return NOERROR;
}


// DELETECLSCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteClassFromDoc (ULONG lIdent, CGeoDoc *pDoc, DWORD)
{
	return pDoc -> FDelClass (lIdent);
}


// Liefert eine Collection von GeoClass's, die in dieser GeoDB enthalten sind -
typedef struct tagENUMIDENTDATA {
	CClassCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMIDENTDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetAllIdents (long lIdent, BOOL, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;
CClass *pClass = pEID -> m_pDoc -> FGetClassDisp ((ULONG)lIdent);

	if (pClass && pEID -> m_pCr -> InsertPtr (pClass)) 
		((_DGeoClass *)pClass) -> AddRef();

	return true;
}

extern "C" 
bool PASCAL _CreateClassDoc (ENUMIDENTDATA *pEID, ULONG *plNewIdent)
{
CClass *pClass = pEID -> m_pDoc -> FGetClassDisp (*plNewIdent, NULL, GEOCLASSMODE_Add);

	if (pClass && pEID -> m_pCr -> InsertPtr (pClass)) {
		((_DGeoClass *)pClass) -> AddRef();
		*plNewIdent = pClass -> GetValue();
		return true;
	}
	*plNewIdent = INVALID_IDENT;
	
return false;
}


// INITCLASSCOLLECTIONPROC ----------------------------------------------------
extern "C" INITCLSSTATUS PASCAL GetAllIdents (LPUNKNOWN pUnk, 
											  CTriasApp *pApp, 
				     						  CGeoDoc *pDoc, 
				     						  container_wrappers::CCreator &rCollCr, 
				     						  DWORD, 
				     						  ULONG *plIdent)
{
ENUMIDENTDATA EID;

	EID.m_pCr = (CClassCreator *)&rCollCr;
	EID.m_pUnk = pUnk;
	EID.m_pApp = pApp;
	EID.m_pDoc = pDoc; 
		
        if (plIdent == NULL) {		// Complete fill
	ENUMNOKEY EIds;

		EIds.eFcn = (ENUMNOKEYPROC)_GetAllIdents;	// zu rufende Funktion
		EIds.ePtr = &EID;				// durchzureichende Daten
	
		if (DEX_EnumIdents (EIds))			// mit Idents füllen
			return INITCLSSTATUS_Exists;
			
	} else if (*plIdent != INVALID_IDENT) {				// Fill only dwSingle
		if (_GetAllIdents (*plIdent, true, &EID))
			return INITCLSSTATUS_Exists;
	} else if (_CreateClassDoc (&EID, plIdent))
		return INITCLSSTATUS_Created;			// Create New Class

	return INITCLSSTATUS_Error;
}


// Liefert die Liste aller in diesem Projekt enthaltenen Objektklassen 
// (Identifikatoren)
STDMETHODIMP CGeoDoc::GetClasses (VARIANT /*vClss*/, VARIANT /*vLogMode*/, DGeoClasses **ppIClss)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetClasses");

	TEST_E_POINTER("CGeoDoc::GetClasses", ppIClss);

CClasses *pCIdents = CClasses :: CreateInstance (
	(_DDocument *)this, m_pApp, this, GetAllIdents, NULL, DeleteClassFromDoc);

	if (NULL == pCIdents) return E_OUTOFMEMORY;

	*ppIClss = (DGeoClasses *)pCIdents;
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetClass (VARIANT vCls, VARIANT vMode, DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetClass");

	TEST_E_POINTER("CGeoDoc::GetClass", ppICls);
	SetLastError (S_OK);

CComVariant vArg; 
CComVariant vArgMode; 

HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOCLASSMODE rgMode = GEOCLASSMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOCLASSMODE)V_I4(&vArgMode);

ULONG lIdent = INVALID_IDENT;	

	if (VT_BSTR != V_VT(&vCls)) {
		hr = VariantChangeType (&vArg, &vCls, 0, VT_I4); // If Argument is Class Ident	
		if (SUCCEEDED(hr)) {
			lIdent = V_I4(&vArg);

			switch (rgMode) {		
			case GEOCLASSMODE_Get:		// default
			case GEOCLASSMODE_Add:    	// create new, if not exists
				{
				CClass *pClass = FGetClassDisp (lIdent, ppICls, rgMode);
				
					if (NULL == pClass) {
						if (GEOCLASSMODE_Add == rgMode) {
							if (S_OK == GetLastError())
								return E_OUTOFMEMORY;
							return GetLastError();
						}
					}
				}
				break;

			case GEOCLASSMODE_Remove:	// remove item
				FDelClass (lIdent);
				*ppICls = NULL;
				break;
				
			case GEOCLASSMODE_Replace:	// remove old, create new
			default:
				return E_UNEXPECTED;
			}

			return NOERROR;
		} 
	}
		
	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR); // If Argument is Class Name
	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));

		switch (rgMode) {		
		case GEOCLASSMODE_Get:		// default
		case GEOCLASSMODE_Add:		// create, if not existent
			{
			CClass *pClass = FGetClassDisp (strName.c_str(), ppICls, rgMode);
						
				if (NULL == pClass) {
					if (GEOCLASSMODE_Add == rgMode) {
						if (S_OK == GetLastError())
							return E_OUTOFMEMORY;
						return GetLastError();
					}
				}
			}
			break;

		case  GEOCLASSMODE_Remove:	// remove item
			FDelClass (AnsiString(V_BSTR(&vArg)));
			*ppICls = NULL;
			break;
			
		case GEOCLASSMODE_Replace:	// remove old, create new
		default:
			return E_UNEXPECTED;
		}		

		return NOERROR;
	}	

return hr;
}

STDMETHODIMP CGeoDoc::AddClass (VARIANT vCls, VARIANT vDataSrc, DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::AddClass");

	TEST_E_POINTER("CGeoDoc::AddClass", ppICls);

CComVariant vArg; 
CComVariant vArgSrc; 

HRESULT hr = VariantChangeType (&vArgSrc, &vDataSrc, 0, VT_BSTR);
CComBSTR bstrSrc (g_cbNil);

	USES_CONVERSION;
	if (SUCCEEDED(hr)) 
		bstrSrc = V_BSTR(&vArgSrc);

ULONG lIdent = INVALID_IDENT;	

	if (VT_BSTR != V_VT(&vCls)) {
		hr = VariantChangeType (&vArg, &vCls, 0, VT_I4); // If Argument is Class Ident	
		if (SUCCEEDED(hr)) {
		CClass *pClass = FGetClassDisp (V_I4(&vArg), ppICls, GEOCLASSMODE_Add, !bstrSrc ? NULL : OLE2A(bstrSrc));
		
			if (NULL == pClass) {
				if (S_OK == GetLastError())
					return E_OUTOFMEMORY;
				return GetLastError();
			}
			return S_OK;
		} 
	}
		
	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR); // If Argument is Class Name
	if (SUCCEEDED(hr)) {
	CClass *pClass = FGetClassDisp (OLE2A(V_BSTR(&vArg)), ppICls, GEOCLASSMODE_Add, !bstrSrc ? NULL : OLE2A(bstrSrc));
						
		if (NULL == pClass) {
			if (S_OK == GetLastError())
				return E_OUTOFMEMORY;
			return GetLastError();
		}
		return NOERROR;
	}	
	return hr;
}

STDMETHODIMP CGeoDoc::GetClassEx (VARIANT vCls, VARIANT vDataSrc, VARIANT vMode, DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetClassEx");

	TEST_E_POINTER("CGeoDoc::GetClassEx", ppICls);
	SetLastError (S_OK);

CComVariant vArg; 
CComVariant vArgMode; 
CComVariant vArgSrc; 

HRESULT hr = VariantChangeType (&vArgSrc, &vDataSrc, 0, VT_BSTR);
CComBSTR bstrSrc (g_cbNil);

	USES_CONVERSION;
	if (SUCCEEDED(hr)) 
		bstrSrc = V_BSTR(&vArgSrc);

GEOCLASSMODE rgMode = GEOCLASSMODE_Get;

	hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
	if (SUCCEEDED(hr)) 
		rgMode = (GEOCLASSMODE)V_I4(&vArgMode);

ULONG lIdent = INVALID_IDENT;	

	if (VT_BSTR != V_VT(&vCls)) {
		hr = VariantChangeType (&vArg, &vCls, 0, VT_I4); // If Argument is Class Ident	
		if (SUCCEEDED(hr)) {
			lIdent = V_I4(&vArg);

			switch (rgMode) {		
			case GEOCLASSMODE_Get:		// default
			case GEOCLASSMODE_Add:    	// create new, if not exists
				{
				CClass *pClass = FGetClassDisp (lIdent, ppICls, rgMode, !bstrSrc ? NULL : OLE2A(bstrSrc));
				
					if (NULL == pClass) {
						if (GEOCLASSMODE_Add == rgMode) {
							if (S_OK == GetLastError())
								return E_OUTOFMEMORY;
							return GetLastError();
						}
					}
				}
				break;

			case GEOCLASSMODE_Remove:	// remove item
				FDelClass (lIdent);
				*ppICls = NULL;
				break;
				
			case GEOCLASSMODE_Replace:	// remove old, create new
			default:
				return E_UNEXPECTED;
			}

			return NOERROR;
		} 
	}
		
	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR); // If Argument is Class Name
	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));

		switch (rgMode) {		
		case GEOCLASSMODE_Get:		// default
		case GEOCLASSMODE_Add:		// create, if not existent
			{
			CClass *pClass = FGetClassDisp (strName.c_str(), ppICls, rgMode, !bstrSrc ? NULL : OLE2A(bstrSrc));
						
				if (NULL == pClass) {
					if (GEOCLASSMODE_Add == rgMode) {
						if (S_OK == GetLastError())
							return E_OUTOFMEMORY;
						return GetLastError();
					}
				}
			}
			break;

		case  GEOCLASSMODE_Remove:	// remove item
			FDelClass (OLE2A(V_BSTR(&vArg)), !bstrSrc ? NULL : OLE2A(bstrSrc));
			*ppICls = NULL;
			break;
			
		case GEOCLASSMODE_Replace:	// remove old, create new
		default:
			return E_UNEXPECTED;
		}		

		return NOERROR;
	}	
	return hr;
}

// DELETEOBJCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteObjectFromDoc (LONG lONr, CGeoDoc *pDoc, DWORD)
{
	return pDoc -> FDelObject (lONr);
}

// Liefert eine Collection von GeoObject's, die in dieser GeoDB enthalten sind -
typedef struct tagENUMDOCDATA {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMDOCDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsFromIdentDoc (LONG lONr, BOOL, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject)) 
		((_DGeoObject *)pObject) -> AddRef();
	
	return true;
}

extern "C" 
bool PASCAL _CreateObjectDoc (ENUMDOCDATA *pEDD, long *plNewONr)
{
CGeoObject *pObject = pEDD -> m_pDoc -> FGetObjectDisp (INVALID_ONR, NULL, GEOOBJECTMODE_Add);

	if (pObject && pEDD -> m_pCr -> InsertPtr (pObject)) {
		((_DGeoObject *)pObject) -> AddRef();
		*plNewONr = pObject -> GetValue();
		return true;
	}
	*plNewONr = INVALID_ONR;
	
return false;
}

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetIdentsFromDoc (long lIdent, BOOL, void *pData)
{
ENUMLONGKEY ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYPROC)_GetObjectsFromIdentDoc;
	ELK.ePtr = pData;
	
	return DEX_EnumIdentObjects (ELK);
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromDoc (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
ENUMDOCDATA EDD;

	EDD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EDD.m_pUnk = pUnk;
	EDD.m_pApp = pApp;
	EDD.m_pDoc = pDoc;

	if (plONr == NULL) {
	// complete fill 
	ENUMNOKEYEX ENK;
	GETOBJECTSDATA *pGOD = (GETOBJECTSDATA *)dwData;
		
		ENK.eFcn = (ENUMNOKEYEXPROC)_GetIdentsFromDoc;	// zu rufende Funktion
		ENK.ePtr = &EDD;				// durchzureichende Daten
		ENK.eData = pGOD->iObjBits;		// gewünschte Objekttypen

		if (DEX_EnumIdentsEx (ENK))		// mit Idents füllen
			return INITOBJSTATUS_Exists;
	} else if (*plONr != INVALID_ONR) {
	// fill only dwSingle
		if (_GetObjectsFromIdentDoc (*plONr, true, &EDD))
			return INITOBJSTATUS_Exists;
	} else if (_CreateObjectDoc (&EDD, plONr))
		return INITOBJSTATUS_Created;	// create new object

	return INITOBJSTATUS_Error;
}

STDMETHODIMP CGeoDoc::GetObjects (VARIANT vObjType, VARIANT /*vLogMode*/, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetObjects");

	TEST_E_POINTER("CGeoDoc::GetObjects", ppIObjs);

CComVariant vArg; 
HRESULT hr = VariantChangeType (&vArg, &vObjType, 0, VT_I4);
long iObjBits = OTPunkt|OTLinie|OTFlaeche|OTText;

	if (SUCCEEDED(hr)) iObjBits = V_I4(&vArg);

GETOBJECTSDATA GOD;

	INITSTRUCT(GOD, GETOBJECTSDATA);
	GOD.iObjBits = iObjBits;

CGeoObjects *pCObjects = CGeoObjects :: CreateInstance (
		(DDocument *)this, m_pApp, this, GetObjectsFromDoc, 
		(DWORD)&GOD, DeleteObjectFromDoc);

	if (NULL == pCObjects) return E_OUTOFMEMORY;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetObject (VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetObject");

	TEST_E_POINTER("CGeoDoc::GetObject", ppIObj);

CComVariant vArg; 
CComVariant vArgMode; 

HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get;

	if (SUCCEEDED(hr)) rgMode = (GEOOBJECTMODE)V_I4(&vArgMode);
		
long lONr = INVALID_ONR;

	if (VT_BSTR != V_VT(&vObj)) {
	// nur auf Zahl testen, wenn nicht direkt als BSTR gegeben
	// damit Objektnamen eine Zahl sein dürfen
		hr = VariantChangeType (&vArg, &vObj, 0, VT_I4); // If Argument is Object Number	
		if (SUCCEEDED(hr)){
			lONr = V_I4(&vArg);

			switch (rgMode) {		
			case GEOOBJECTMODE_Get:		// get default
			case GEOOBJECTMODE_Replace:	// get new (oObj and nObj in database exists)
				{
				CGeoObject *pObject = FGetObjectDisp (lONr, ppIObj, rgMode);
				
					if (NULL == pObject)
						return E_UNEXPECTED;
				}
				break;
				
			case GEOOBJECTMODE_Add: 	// TRiAS generate Object Number
				{
				CGeoObject *pObject = FGetObjectDisp ((long)INVALID_ONR, ppIObj, rgMode);
				
					if (NULL == pObject)
						return E_UNEXPECTED;
				}
				break;

			case GEOOBJECTMODE_Remove:	// remove item
				FDelObject (lONr);
				*ppIObj = NULL;
				break;
				
			default:
				return E_UNEXPECTED;
			}

			return NOERROR;
		} 
	}

	hr = VariantChangeType (&vArg, &vObj, 0, VT_BSTR); // If Argument is Object Name
	if (SUCCEEDED(hr)) {

		switch (rgMode) {
		case GEOOBJECTMODE_Get:		// get default
		case GEOOBJECTMODE_Replace:	// get new (oObj and nObj in database exists)
		case GEOOBJECTMODE_Add:		// create, if not existent
			{
			CGeoObject *pObject = FGetObjectDisp (V_BSTR(&vArg), ppIObj, rgMode);
						
				if (NULL == pObject) 
					return E_UNEXPECTED;
			}
			break;

		case GEOOBJECTMODE_Remove:	// remove item
			{
				USES_CONVERSION;
				FDelObject (OLE2A(V_BSTR(&vArg)));
				*ppIObj = NULL;
			}
			break;
			
		default:
			return E_UNEXPECTED;
		}		
		return NOERROR;
	}	
	return hr;
}

STDMETHODIMP CGeoDoc::AddObject (VARIANT vObj, VARIANT vClass, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::AddObject");

	TEST_E_POINTER("CGeoDoc::AddObject", ppIObj);

CComVariant vArg; 
long lONr = INVALID_ONR;
HRESULT hr = E_FAIL;

//	if (VT_BSTR != V_VT(&vObj)) {
//	// nur auf Zahl testen, wenn nicht direkt als BSTR gegeben
//	// damit Objektnamen eine Zahl sein dürfen
//		hr = VariantChangeType (&vArg, &vObj, 0, VT_I4); // If Argument is Object Number	
//		if (SUCCEEDED(hr)){
//			lONr = V_I4(&vArg);
//
//		CGeoObject *pObject = FGetObjectDisp ((long)INVALID_ONR, ppIObj, GEOOBJECTMODE_Add, &vClass);
//			
//			if (NULL == pObject)
//				return E_UNEXPECTED;
//		}
//		return hr;
//	}

	hr = vArg.ChangeType (VT_BSTR, &vObj);	// If Argument is Object Name
	if (SUCCEEDED(hr)) {
	CGeoObject *pObject = FGetObjectDisp (V_BSTR(&vArg), ppIObj, GEOOBJECTMODE_Add, &vClass);
						
		if (NULL == pObject) 
			return E_UNEXPECTED;
		return NOERROR;
	}

// testen, ob der Parameter weggelassen wurde, dann Guid verwenden
	hr = vArg.ChangeType (VT_ERROR, &vObj);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) {
	CIID ObjGuid;
	CGeoObject *pObject = FGetObjectDisp (CComBSTR(ObjGuid), ppIObj, GEOOBJECTMODE_Add, &vClass);
						
		if (NULL == pObject) 
			return E_UNEXPECTED;
		return NOERROR;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Objektrecherche
namespace {
// Set enthält alle zu untersuchenden MCodes
	typedef set<INT_PTR> CQueryMCodes;

// Zusammen sämtlicher relevanter MCodes
	typedef struct tagENUMQUERYDATA {
		LPCSTR pFeatName;
		BOOL fIsTRiASDataSource;
		CQueryMCodes *psetMCodes;
	} ENUMQUERYDATA;

	BOOL CALLBACK EnumMCodesForQuery (long lMCode, DWORD dwData, void *pData)
	{
	ENUMQUERYDATA *pEQD = (ENUMQUERYDATA *)pData;
	PBDMERKMAL pbdData;
	char cbKText[_MAX_PATH] = { '\0' };

		INITSTRUCT(pbdData, PBDMERKMAL);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = lMCode;
		pbdData.pbdKText = cbKText;
		pbdData.pbdKTextLen = sizeof(cbKText) -1;
		pbdData.pbdLTextLen = 0;
		pbdData.ipbdMTyp = dwData;
		if (EC_OKAY == DEX_GetPBDData (pbdData) && !strcmp (cbKText, pEQD -> pFeatName)) {

			pEQD -> psetMCodes -> insert (lMCode);
			return !pEQD -> fIsTRiASDataSource;		// TRiAS-DQ's: es reicht der erste
		}
		return TRUE;	// weitermachen
	}

// sämtliche Objektklassen einer Datenquelle enumerieren
	BOOL CALLBACK EnumClassesForQuery (long lIdent, BOOL, void *pData)
	{
	ENUMLONGKEYEX ELK;

		ELK.eKey = lIdent;
		ELK.eFcn = (ENUMLONGKEYEXPROC)EnumMCodesForQuery;
		ELK.ePtr = pData;
		ELK.eData = MPObjectFeature|MPAllFeatures|MPSystemFeatures;
		return DEX_EnumObjektMerkmaleClassEx (ELK);
	}

// sämtliche Datenquellen enumerieren
	BOOL CALLBACK EnumDataSourceForQuery (long hPr, BOOL, void *pData)
	{
	// wenn TRiAS-DQ, dann nur den ersten MCode einer Datenquelle behandeln
		((ENUMQUERYDATA *)pData) -> fIsTRiASDataSource = DEX_GetTRiASDataSourceEx((HPROJECT)hPr);

	ENUMNOKEY ENK;

		ENK.eFcn = (ENUMNOKEYPROC)EnumClassesForQuery;
		ENK.ePtr = pData;
		DEX_EnumClasses((HPROJECT)hPr, ENK);
		return TRUE;		// immer weiter machen
	}

// Prozeduren für eigentliche Recherche
	typedef struct tagQUERYOBJECTSFEATDATA {
		DWORD dwSize;
		LPSTR pView;
		CQueryMCodes *psetMCodes;
		LPSTR pToSearch;
		int iMode;
	} QUERYOBJECTSFEATDATA;

	typedef struct tagENUMOBJECTDATA {
		CGeoObjectCreator *m_pCr;
		LPUNKNOWN  m_pUnk;
		CTriasApp *m_pApp;
		CGeoDoc   *m_pDoc;
	} ENUMOBJECTDATA;

	BOOL CALLBACK QueryObjectFromSearchFeat (long lONr, BOOL, void *pData)
	{
	ENUMOBJECTDATA *pEOD = reinterpret_cast<ENUMOBJECTDATA *>(pData);
	CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

		if (pObject && pEOD -> m_pCr -> InsertPtr (pObject))
			((_DGeoObject *)pObject) -> AddRef();
		
		return TRUE;
	}

	INITOBJSTATUS PASCAL QueryObjectsFromFeat (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
	{
		if (plONr != NULL)	
			return INITOBJSTATUS_Error;		// Einzelobjekt soll hinzugefügt werden
		
	ENUMRECHTEXTMERKMAL ERTM;
	QUERYOBJECTSFEATDATA *pGOD = reinterpret_cast<QUERYOBJECTSFEATDATA *>(dwData);
	ENUMOBJECTDATA EOD;

		EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
		EOD.m_pUnk = pUnk;
		EOD.m_pApp = pApp;
		EOD.m_pDoc = pDoc;

		INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
		ERTM.pView = pGOD -> pView;	
		ERTM.pMWert = pGOD -> pToSearch;	// Suchpattern
		ERTM.iMode = pGOD -> iMode;		// Suchmode
		ERTM.eFcn = reinterpret_cast<RECHTEXTMERKMALCALLBACK>(QueryObjectFromSearchFeat);
		ERTM.pData = &EOD;

		for (CQueryMCodes::iterator it = pGOD -> psetMCodes -> begin(); it != pGOD -> psetMCodes -> end(); ++it) {
			ERTM.lMCode = *it;	// MerkmalsCode
			if (!DEX_EnumRechTextMerkmal (ERTM))					// mit Objekten füllen
				return INITOBJSTATUS_Error;
		}
		return INITOBJSTATUS_Exists;
	}
}

STDMETHODIMP CGeoDoc::QueryObjects (VARIANT vFeature, VARIANT vToSearch, VARIANT vMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoDoc::QueryObjects", ppIObjs);
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::QueryObjects");

	COM_TRY {
	// wenn vFeature eine Objekteigenschaft ist, dann diese direkt arbeiten lassen
	CComVariant vArg;

		if (SUCCEEDED(vArg.ChangeType (VT_DISPATCH, &vFeature))) 
			return WDGeoFeature(V_DISPATCH(&vArg)) -> GetObjects (vToSearch, vMode, ppIObjs);

		if (SUCCEEDED(vArg.ChangeType (VT_BSTR, &vFeature))) {
		// lediglich der Name einer Objekteigenschaft ist gegeben, alle betreffenden MCodes finden
		// dazu alle Datenquellen durchgehen, da TRiAS-DQ's anders behandelt werden können

			USES_CONVERSION;

		CQueryMCodes setMCodes;
		ENUMNOKEYLONG ENK;
		ENUMQUERYDATA EQD;

			EQD.pFeatName = OLE2A(V_BSTR(&vArg));
			EQD.fIsTRiASDataSource = FALSE;
			EQD.psetMCodes = &setMCodes;
			
			ENK.eFcn = (ENUMNOKEYLONGPROC)EnumDataSourceForQuery;
			ENK.ePtr = &EQD;
			if (!DEX_EnumDataSourceHandles(ENK) && FAILED(GetLastError()))
				THROW_FAILED_HRESULT(GetLastError());

		// jetzt eigentliche Recherche durchführen
		int rgMode = SMExactMatch;		// default: exakt suchen
		LPSTR pToSearch = NULL;			// default: alle Objekte, kein Suchkriterium

			if (SUCCEEDED(vArg.ChangeType (VT_BSTR, &vToSearch))) {
				pToSearch = OLE2A(V_BSTR(&vArg));
				if (SUCCEEDED(vArg.ChangeType (VT_I4, &vMode)))
					rgMode = V_I4(&vArg);
			} 
			else {
			// kein Suchtext gegeben, also lediglich Existenz testen
				if (SUCCEEDED(vArg.ChangeType (VT_I4, &vMode)))
					rgMode = (V_I4(&vArg) & ~SMActionFlag) | SMExistanceOnly;
				else
					rgMode = SMExistanceOnly;
			}

		QUERYOBJECTSFEATDATA QOD;

			INITSTRUCT(QOD, QUERYOBJECTSFEATDATA);
			QOD.pView = NULL;				// aktuelle Ansicht
			QOD.psetMCodes = &setMCodes;
			QOD.pToSearch = pToSearch;
			QOD.iMode = rgMode;

		CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
									(DDocument *)this, m_pApp, this,
									QueryObjectsFromFeat, (DWORD)&QOD, NULL);

			if (NULL == pCObjects) 
				return E_OUTOFMEMORY;

			pCObjects -> m_dwData = NULL;		// can't regenerate
			*ppIObjs = (DGeoObjects *)pCObjects;
		}

	} COM_CATCH;
	return S_OK;
}

// DELETEOBJWINCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteObjWinFromDoc (HWND hWnd, CGeoDoc *pDoc)
{
	return pDoc -> FDelObjWin (hWnd); //Remove Physically !
}

// Liefert eine Collection von GeoObjWins
typedef struct tagENUMDOCWINDATA {
	CGeoObjectWinCreator *m_pCr;
	LPUNKNOWN			  m_pUnk;
	CTriasApp			 *m_pApp;
	CGeoDoc				 *m_pDoc;
} ENUMDOCWINDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjWinFromDoc (HWND hWnd, BOOL, void *pData)
{
ENUMDOCWINDATA *pEOD = (ENUMDOCWINDATA *)pData;
CGeoObjectWin *pObjWin = pEOD -> m_pDoc -> FGetObjWinDisp (hWnd);

	if (pObjWin && pEOD -> m_pCr -> InsertPtr (pObjWin)) 
		((_DGeoObjectWin *)pObjWin) -> AddRef();
	
	return true;
}

extern "C" 
bool PASCAL _CreateObjWinDoc (ENUMDOCWINDATA *pEDD, HWND *pNewHWND)
{
CGeoObjectWin *pObjWin = pEDD -> m_pDoc -> FGetObjWinDisp (
					(HWND)INVALID_HWND, NULL, GEOOBJWINMODE_Add);

	if (pObjWin && pEDD -> m_pCr -> InsertPtr (pObjWin)) {
		((_DGeoObjectWin *)pObjWin) -> AddRef();
		*pNewHWND = pObjWin -> GetValue();
		return true;
	}

	*pNewHWND = INVALID_HWND;
	return false;
}



// INITOBJWINCOLLECTIONPROC ------------------------------------------------------
extern "C" INITOBJWINSTATUS PASCAL GetObjWinsFromDoc (LPUNKNOWN  pUnk, 
												      CTriasApp *pApp, 
												      CGeoDoc   *pDoc, 
												      container_wrappers::CCreator &rCollCr, 
														  DWORD, 
														   HWND *phWnd)
{
ENUMDOCWINDATA EDWD;

	EDWD.m_pCr = (CGeoObjectWinCreator *)&rCollCr;
	EDWD.m_pUnk = pUnk;
	EDWD.m_pApp = pApp;
	EDWD.m_pDoc = pDoc;

	if (phWnd == NULL) {
	// complete fill 
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMNOKEYLONGPROC)_GetObjWinFromDoc;	// zu rufende Funktion
		ENK.ePtr = &EDWD;									// durchzureichende Daten

		if (DEX_EnumORWindows (ENK))	
			return INITOBJWINSTATUS_Exists;

	} else if (*phWnd != INVALID_HWND) {
	// fill only dwSingle
	
		if (_GetObjWinFromDoc (*phWnd, true, &EDWD))
			return INITOBJWINSTATUS_Exists;

	} else if (_CreateObjWinDoc (&EDWD, phWnd))
	// create new window
			return INITOBJWINSTATUS_Created;

	return INITOBJWINSTATUS_Error;
}


STDMETHODIMP CGeoDoc::GetGeoObjectWins (THIS_ VARIANT /*vObjWins*/, VARIANT /*vLogMode*/, DGeoObjectWins **ppIWins)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetGeoObjectWins");

	TEST_E_POINTER("CGeoDoc::GetGeoObjectWins", ppIWins);

CGeoObjectWins *pCObjWins = CGeoObjectWins::CreateInstance (
	(DDocument *)this, m_pApp, this, GetObjWinsFromDoc, 
	NULL, DeleteObjWinFromDoc);

	if (NULL == pCObjWins) return E_OUTOFMEMORY;

	*ppIWins = (DGeoObjectWins *)pCObjWins;
	return S_OK;
}
																	 
STDMETHODIMP CGeoDoc::GetGeoObjectWin (VARIANT vWnd, VARIANT vMode, DGeoObjectWin **ppIWin)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetGeoObjectWin");

	TEST_E_POINTER("CGeoDoc::GetGeoObjectWin", ppIWin);

CComVariant vArg;
CComVariant vArgMode;

HRESULT hr = vArgMode.ChangeType (VT_I4, &vMode);
GEOOBJWINMODE rgMode = GEOOBJWINMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOOBJWINMODE)V_I4(&vArgMode);
		
HWND hWnd = INVALID_HWND;

// If Argument is Window hWnd
	if (VT_BSTR != V_VT(&vWnd)) {
		hr = vArg.ChangeType (VT_I4, &vWnd);
		if (SUCCEEDED(hr)){
			hWnd = (HWND)V_I4(&vArg);

			switch (rgMode) {		
			case GEOOBJWINMODE_Get:		// default
			case GEOOBJWINMODE_Replace:	// remove old, create new
				{
				CGeoObjectWin *pObjWin = FGetObjWinDisp (hWnd, ppIWin, rgMode);

					if (NULL == pObjWin) 
						return E_UNEXPECTED;
				}
				break;
													  
			case GEOOBJWINMODE_Add: 	// WINDOWS generates hWnd !
				{
				CGeoObjectWin *pObjWin = FGetObjWinDisp ((HWND)INVALID_HWND, ppIWin, rgMode);

					if (NULL == pObjWin) 
						return E_UNEXPECTED;
				}
				break;

			case GEOOBJECTMODE_Remove:	// remove item  Tut!
				FDelObjWin (hWnd);
				*ppIWin = NULL;
				break;
				
			default:
				return E_UNEXPECTED;
			}

			return NOERROR;
		}
	}
		
// If Argument is Window Name
	hr = vArg.ChangeType (VT_BSTR, &vWnd);
	if (SUCCEEDED(hr)) {
	string strName (AnsiString(V_BSTR(&vArg)));

		switch (rgMode) {		
		case GEOOBJWINMODE_Get:		// default
		case GEOOBJWINMODE_Replace:	// remove old, create new
		case GEOOBJWINMODE_Add: 	// create new (if not existent) with WINDOWS generated hWnd !
			{
			CGeoObjectWin *pObjWin = FGetObjWinDisp (strName.c_str(), ppIWin, rgMode);

				if (NULL == pObjWin) 
					return E_UNEXPECTED;
			}
			break;

		case GEOOBJWINMODE_Remove:		// remove item  Tut!
			hWnd = GethWndFromObjWinName (strName.c_str());
			FDelObjWin (hWnd);
			*ppIWin = NULL;
			break;
			
		default:
			return E_UNEXPECTED;
		}		
		return NOERROR;
	}	

	return hr;
}

// neue (leere und unabhängige) GeoObjects-Collection erzeugen ----------------
STDMETHODIMP CGeoDoc::CreateGeoObjectsCollection (DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::CreateGeoObjectsCollection");

	return CreateNewGeoObjects (ppIObjs);
}

STDMETHODIMP CGeoDoc::get_Author (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Author");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::put_Author (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Author");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Comments (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Comments");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::put_Comments (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Comments");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Keywords (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Keywords");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::put_Keywords (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Keywords");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Subject (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Subject");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::put_Subject (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Subject");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Title (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Title");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::put_Title (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Title");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Saved (VARIANT_BOOL *pfSaved)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Saved");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_ReadOnly (VARIANT_BOOL *pfReadOnly)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_ReadOnly");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::RevertToSaved (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::RevertToSaved");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_Properties (_DTRiASProperties **ppIProps)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Properties");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::CreateProperty");

	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::get_RefScale (long *plRefScale)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_RefScale");

	if (NULL == plRefScale) return E_POINTER;

HeaderEntryX hdrScale (g_cbBezugsMasstab);

	*plRefScale = hdrScale.EntryLong(0L);
	return S_OK;
}

STDMETHODIMP CGeoDoc::put_RefScale (long lRefScale)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_RefScale");

HeaderEntryX hdrScale (g_cbBezugsMasstab);

	if (lRefScale != 0) {
	char cbBuffer[32];

		hdrScale.SetEntryText (ltoa(lRefScale, cbBuffer, 10));
		hdrScale.WriteBack();
	} else
		hdrScale.DeleteEntry();

	DEXN_ReReadHeader();
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetViewRect (
	double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::GetViewRect");

	ATLTRACENOTIMPL("CGeoDoc::GetViewRect");
}

STDMETHODIMP CGeoDoc::SetViewRect (
	double dX1, double dY1, VARIANT vX2, VARIANT vY2)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::SetViewRect");

	ATLTRACENOTIMPL("CGeoDoc::SetViewRect");
}

STDMETHODIMP CGeoDoc::get_IsDirty (VARIANT_BOOL *pfValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_IsDirty");

	if (NULL == pfValue)
		return E_POINTER;

	*pfValue = DEX_IsGeoDBDirty() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CGeoDoc::put_IsDirty (VARIANT_BOOL fValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_IsDirty");

	DEX_SetDirtyGeoDB (fValue ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CGeoDoc::get_PreventRepaint (VARIANT_BOOL *pfValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_PreventRepaint");

	if (NULL == pfValue)
		return E_POINTER;

	*pfValue = DEX_IsPreventRepaintActive() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CGeoDoc::put_PreventRepaint (VARIANT_BOOL fValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_PreventRepaint");

	DEX_SetPreventRepaint (fValue ? TRUE : FALSE);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Connection
STDMETHODIMP CGeoDoc::get_Connections (ITRiASConnections **ppIConns)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Connections");

	COM_TRY {
	// alle Connections durchgehen und feststellen:
	// aktuelle Connection, ob beschreibbare Connection existiert
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

		THROW_FAILED_HRESULT(Prj -> get_Connections (ppIConns));

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Wrapper für RenderGeoDb
	HDC GetPrinterDC (VARIANT &vDriver, VARIANT &vDevice, VARIANT &vPort)
	{
		USES_CONVERSION;

	CComVariant vDriverName, vDeviceName, vPortName;
	HDC hTargetDC = NULL;

		if (FAILED(vDriverName.ChangeType(VT_BSTR, &vDriver)) ||
			FAILED(vDeviceName.ChangeType(VT_BSTR, &vDevice)) ||
			FAILED(vPortName.ChangeType(VT_BSTR, &vPort)))
		{
		CPrintDialog pd(TRUE);
			
			if (!pd.GetDefaults())
				return NULL;

			hTargetDC = ::CreateIC (pd.GetDriverName(), 
				pd.GetDeviceName(), pd.GetPortName(), pd.GetDevMode());
		}
		else {
			hTargetDC = ::CreateIC (OLE2A(V_BSTR(&vDriverName)), 
				OLE2A(V_BSTR(&vDeviceName)), OLE2A(V_BSTR(&vPortName)), NULL);
		}
		return hTargetDC;
	}

///////////////////////////////////////////////////////////////////////////////
// ein IPicture aus einem Metafile erzeugen
	HRESULT CreatePicture (HENHMETAFILE hMetaF, IDispatch **ppIDisp)
	{
		if (NULL == hMetaF)
			return E_INVALIDARG;

	PICTDESC pdesc;

		pdesc.cbSizeofstruct = sizeof(pdesc);
		pdesc.picType = PICTYPE_ENHMETAFILE;
		pdesc.emf.hemf = hMetaF;

	HRESULT hr = ::OleCreatePictureIndirect (&pdesc, IID_IDispatch, TRUE, (LPVOID *)ppIDisp);

		if (FAILED(hr)) {
			::DeleteEnhMetaFile (hMetaF);
			return hr;
		}
		return S_OK;
	}
}

STDMETHODIMP CGeoDoc::Render(
	long lLeft, long lBottom, long lRight, long lTop,
	VARIANT vLeftDbArg, VARIANT vBottomDbArg, VARIANT vRightDbArg, VARIANT vTopDbArg,
	VARIANT vDriverArg, VARIANT vDeviceArg, VARIANT vPortArg, IDispatch **ppIPictDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::Render");

RECTL rclFrame;

	rclFrame.left = lLeft;
	rclFrame.bottom = lBottom;
	rclFrame.right = lRight;
	rclFrame.top = lTop;

CComVariant vLeftDb, vBottomDb, vRightDb, vTopDb;
RECTL rclGeoDB;

	if (SUCCEEDED(vLeftDb.ChangeType(VT_R8, &vLeftDbArg)) &&
		SUCCEEDED(vBottomDb.ChangeType(VT_R8, &vBottomDbArg)) &&
		SUCCEEDED(vRightDb.ChangeType(VT_R8, &vRightDbArg)) &&
		SUCCEEDED(vTopDb.ChangeType(VT_R8, &vTopDbArg)))
	{
	// gültiges Datenbankrechteck gegeben
		if (!InternalCoords (V_R8(&vLeftDb), V_R8(&vBottomDb), &rclGeoDB.left, &rclGeoDB.bottom) || 
			!InternalCoords (V_R8(&vRightDb), V_R8(&vTopDb), &rclGeoDB.right, &rclGeoDB.top))
		{
			return E_UNEXPECTED;
		}
	}
	else {
	// aktuellen Sichtausschnitt verwenden
	long lCont[4];

		if (!DEX_GetActiveSightContainer(lCont))
			return E_UNEXPECTED;
		rclGeoDB.left = lCont[0];
		rclGeoDB.right = lCont[1];
		rclGeoDB.bottom = lCont[2];
		rclGeoDB.top = lCont[3];
	}

// BegrenzungsRechteck des Metafiles berechnen
RECT rcMF;

	rcMF.top = 0;
	rcMF.bottom = rclFrame.top; 
	rcMF.right = rclFrame.right;
	rcMF.left = 0;

HDC hTargetDC = GetPrinterDC(vDriverArg, vDeviceArg, vPortArg);

	if (NULL == hTargetDC)
		return E_INVALIDARG;

	SetMapMode (hTargetDC, MM_HIMETRIC);

HDC hDCMeta = CreateEnhMetaFile (hTargetDC, NULL, (RECT *)&rcMF, g_cbTRiASPict);

	if (NULL == hDCMeta) {
		DeleteDC(hTargetDC);
		return E_UNEXPECTED;
	}

	SetMapMode (hDCMeta, MM_HIMETRIC);			// Bezugsauflösung
	SetWindowOrgEx (hDCMeta, 0, rclFrame.top-rclFrame.bottom, NULL);

RENDERGEODB2 RDB;

	INITSTRUCT(RDB, RENDERGEODB2);
	RDB.m_hDC = hDCMeta;
	RDB.m_hTargetDC = hTargetDC;
	RDB.m_rclGeoDB = rclGeoDB;
	RDB.m_rclFrame = rclFrame;
	RDB.m_rclClipBox = rclFrame;
	RDB.m_rclClipBox.right += 1;
	RDB.m_rclClipBox.bottom += 1;
	RDB.m_iFlags = RDB_CoordsScaled;
	DEX_RenderGeoDB(RDB);

HENHMETAFILE hMetaF = CloseEnhMetaFile (hDCMeta);	// MetaFile schließen
WDispatch Picture;

	DeleteDC(hTargetDC);
	RETURN_FAILED_HRESULT(CreatePicture(hMetaF, Picture.ppi()));
	*ppIPictDisp = Picture.detach();

//// temporären Dateinamen erzeugen
//char cbBuffer[_MAX_PATH];
//
//	GetTempPath(sizeof(cbBuffer), cbBuffer);
	return S_OK;
}

STDMETHODIMP CGeoDoc::get_Tag (BSTR bstrTagName, VARIANT *pvTagData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::get_Tag");

	if (NULL == bstrTagName || 0 == ::SysStringLen(bstrTagName))
		return E_INVALIDARG;
	if (NULL == pvTagData)
		return E_POINTER;

	return m_mapTags.GetTag(bstrTagName, pvTagData);
}

STDMETHODIMP CGeoDoc::put_Tag (BSTR bstrTagName, VARIANT vTagData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoDoc::put_Tag");

	if (NULL == bstrTagName || 0 == ::SysStringLen(bstrTagName))
		return E_INVALIDARG;

	if (VT_EMPTY == V_VT(&vTagData))
		return m_mapTags.DeleteTag(bstrTagName);

	return m_mapTags.AddTag(bstrTagName, vTagData);
}

