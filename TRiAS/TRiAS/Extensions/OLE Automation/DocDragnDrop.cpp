// File DocDragnDrop.cpp

#include "precomp.hxx"

#include <dirisole.h>
#include <bscrguid.h>

#include "oleautor.h"
#include "GlobalFuncs.h"
#include "Strings.h"
#include "MonikerStream.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef void_FILE
static char void_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(ExtendBScript);						// WExtendBScript
DefineSmartInterface2(_DDocument, IID_DDocument);			// W_DDocument
DefineSmartInterface2(_DView, IID_DView);					// W_DView
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);			// W_DGeoObject
DefineSmartInterface2(_DGeoObjects, IID_DGeoObjects);		// W_DGeoObjects
DefineSmartInterface2(_DGeoClass, IID_DGeoClass);			// W_DGeoClass

///////////////////////////////////////////////////////////////////////////////
// eigentliche Drag'n Drop Aktion für Dokument
bool CGeoDoc::FQueryPasteFromData (IDataObject *pIDO)
{
	if (S_OK != GetMonikerData (pIDO, &c_feMkGeoDocument))
		return false;		// GeoDocument _muß_ da sein

// ansonsten muß wenigstens eins der anderen Formate vorhanden sein
	if (S_OK == GetMonikerData (pIDO, &c_feMkGeoObjects))
		return true;
	if (S_OK == GetMonikerData (pIDO, &c_feMkGeoClass))
		return true;
	if (S_OK == GetMonikerData (pIDO, &c_feMkGeoView))
		return true;
	if (S_OK == GetMonikerData (pIDO, &c_feMkGeoObject))
		return true;

	return false;
}

namespace {
// stellt sicher, daß die derzeit aktive Ansicht wieder neu eingestellt wird
	class CReInitView 
	{
	public:
		CReInitView() 
		{
		// aktuelle Ansicht speichern
		char cbBuffer[_MAX_PATH];

			cbBuffer[0] = '\0';
			if (DEX_GetActiveSight(cbBuffer))
				m_strView = cbBuffer;

		// aktuelle Ausschnitt speichern
			DEX_GetActiveSightContainer(m_lCont);

		// PreventRepaintstatus speichern
			m_fPreventRePaint = DEX_IsPreventRepaintActive();
			DEX_SetPreventRepaint(TRUE);
		}
		~CReInitView()
		{
			DEX_SetPreventRepaint(m_fPreventRePaint);		// RePaintFlag richten
			if (m_strView.size() > 0) {						// ggf. aktuelle Ansicht setzen
				DEX_SetActiveSightContainer(m_lCont);		// Container setzen
//				DEX_SelectNewSight(m_strView.c_str());
				DEX_RePaint();
			}
		}
		
	private:
		os_string m_strView;
		long m_lCont[4];
		BOOL m_fPreventRePaint;
	};
}

bool CGeoDoc::FPasteFromData (IDataObject *pIDO, HPROJECT hPr, BOOL fShowORWindow)
{
CWaitCursor Wait;		// EierUhr zeigen

// diverse Moniker aus DataObject herauslesen
WUnknown Unk;
W_DDocument Doc;
HRESULT hr = BindMonikerFromDataObject (pIDO, &c_feMkGeoDocument, IID_IDispatch, Unk.ppv()); //IID_DDocument, Doc.ppv());

	if (FAILED(hr)) return false;	// GeoDoc wird gebraucht
	ATLTRY(Doc = Unk);

CReInitView ViewParams;		// Ansicht so wieder einstellen, wie vorgefunden

// nachsehen, was uns beschehrt wird
W_DView View;
W_DGeoObject Obj;
W_DGeoObjects Objs;
W_DGeoClass Cls;

// eine Ansicht sollte dabei sein (muß aber nicht)
	BindMonikerFromDataObject (pIDO, &c_feMkGeoView, IID_DView, View.ppv());

// ansonsten eine der folgenden Möglichkeiten
	hr = BindMonikerFromDataObject (pIDO, &c_feMkGeoObjects, IID_DGeoObjects, Objs.ppv());
	if (SUCCEEDED(hr)) 
		return FPasteGeoObjects (Doc, View, Objs, hPr, fShowORWindow);

	hr = BindMonikerFromDataObject (pIDO, &c_feMkGeoClass, IID_DGeoClass, Cls.ppv());
	if (SUCCEEDED(hr)) 
		return FPasteGeoClass (Doc, View, Cls, hPr, fShowORWindow);

	hr = BindMonikerFromDataObject (pIDO, &c_feMkGeoObject, IID_DGeoObject, Obj.ppv());
	if (SUCCEEDED(hr)) 
		return FPasteGeoObject (Doc, View, Obj, hPr, fShowORWindow);

	return false;		// nichts passendes gefunden
}

UINT CGeoDoc::TestDroppablePoint (POINTL *pPt)
{
	return UDROP_CLIENT;
}

///////////////////////////////////////////////////////////////////////////////
// macht das, wie's heißt
HRESULT CreateItemMonikerFromEnumLONG (IEnumLONG *pEnum, IMoniker **ppIMk)
{
	if (NULL == pEnum || NULL == ppIMk) return E_POINTER;

string strMk (g_cbMkGeoObjects36);
HOBJECT lONr = INVALID_HOBJECT;
HOBJECT lLastONr = INVALID_HOBJECT;
char cbBuffer[32];
bool fFirst = true;

	USES_CONVERSION;
	strMk += g_cbColon;
	for (pEnum -> Reset(); S_OK == pEnum->Next (1, &lONr, NULL); /**/)
	{
		if (fFirst) {
			strMk += ultoa (lONr, cbBuffer, 36);
			fFirst = false;
		}
		else {
			_ASSERTE(INVALID_HOBJECT != lLastONr);

		long lONrDelta = lONr - lLastONr;

			if (lONrDelta > 0) {
				strMk += "+";
				strMk += ultoa (lONrDelta, cbBuffer, 36);
			} 
			else {
				strMk += '-';
				strMk += ultoa (-lONrDelta, cbBuffer, 36);
			}
		}
		lLastONr = lONr;
	}
	return CreateItemMoniker (g_cbuMkDel, A2OLE(strMk.c_str()), ppIMk);
}

///////////////////////////////////////////////////////////////////////////////
// FPasteSowieSo Funktionen, Wrapper für BasicRoutinen
// Function CopyGeoClass (Doc As GeoDocument, _
//		DocX As GeoDocument, ViewX As GeoView, ClsX As GeoClass) As Boolean
HRESULT CGeoDoc::FPasteGeoClass (
	_DDocument *pIDocX, _DView *pIViewX, _DGeoClass *pIClsX, HPROJECT hPr, BOOL fShowORWindow)
{
	return E_NOTIMPL;
}

// Function CopyGeoObjects (Doc As GeoDocument, _
//		DocX As GeoDocument, ViewX As GeoView, ObjsX As GeoObjects) As Boolean
HRESULT CGeoDoc::FPasteGeoObjects (
	_DDocument *pIDocX, _DView *pIViewX, _DGeoObjects *pIObjsX, HPROJECT hPr, BOOL fShowORWindow)
{
WExtendBScript Bscript;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIBScript (Bscript.ppi());

const int COPYGEOOBJECTS_NUMPARS = 6;
ebPARAM Pars[COPYGEOOBJECTS_NUMPARS+1];
LPVOID cbParam[COPYGEOOBJECTS_NUMPARS+1];
BSPARAM bs = { Pars, cbParam };
ebBOOL fResult = false;

	Pars[0].wType = TYP_BOOLEAN;	// return value: Boolean
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = &fResult;

W_DDocument Doc ((_DDocument *)this);
_DDocument *pIDoc = (_DDocument *)this;

	Pars[1].wType = TYP_APPOBJECT;	// Doc As GeoDocument
	_tcscpy (Pars[1].szExtType, g_cbGeoDocument);
	cbParam[1] = &pIDoc;

W_DDocument DocX (pIDocX);

	Pars[2].wType = TYP_APPOBJECT;	// DocX As GeoDocument
	_tcscpy (Pars[2].szExtType, g_cbGeoDocument);
	cbParam[2] = &pIDocX;

W_DView ViewX (pIViewX);

	Pars[3].wType = TYP_APPOBJECT;	// ViewX As GeoView
	_tcscpy (Pars[3].szExtType, g_cbGeoView);
	cbParam[3] = &pIViewX;

W_DGeoObjects ObjsX (pIObjsX);

	Pars[4].wType = TYP_APPOBJECT;	// ObjsX As GeoObjects
	_tcscpy (Pars[4].szExtType, g_cbGeoObjects);
	cbParam[4] = &pIObjsX;

char cbBuffer[_MAX_PATH];

	cbBuffer[0] = '\0';
	DEX_GetDataSourceShortName(hPr, cbBuffer);
	Pars[5].wType = TYP_STRING;
	Pars[5].szExtType[0] = '\0';
	cbParam[5] = cbBuffer;			// [in], daher direkter Stringpointer

ebBOOL fShowOR = fShowORWindow ? ebTRUE : ebFALSE;

	Pars[6].wType = TYP_BOOLEAN;
	Pars[6].szExtType[0] = '\0';
	cbParam[6] = &fShowOR;

	hr = Bscript -> RunCode (g_hInstance, IDR_SCRIPT_COPYGEOOBJECT,
					g_cbCopyGeoObjects, COPYGEOOBJECTS_NUMPARS, &bs);
	if (FAILED(hr)) return hr;
	
	return fResult ? S_OK : S_FALSE;
}

// Function CopyGeoObject (Doc As GeoDocument, _
//		DocX As GeoDocument, ViewX As GeoView, ObjX As GeoObject) As Boolean
HRESULT CGeoDoc::FPasteGeoObject (
	_DDocument *pIDocX, _DView *pIViewX, _DGeoObject *pIObjX, HPROJECT hPr, BOOL fShowORWindow)
{
	return E_NOTIMPL;
}

