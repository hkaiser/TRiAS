// Document Linking support
// DocLink.cpp

#include "precomp.hxx"

#include <AfxDocOb.h>					// #AD991101

#include <dirisole.h>
#include <ospace/com/iterenum.h>
#include <registrx.hxx>

#include <comcat.h>			// #AD000411, benötigt für GetProperty...
#include <math.h>

#include <GMObjects/PBasic.tlh>
//#include <ictf.h>
#define __ITRiASSpatialRelationService_INTERFACE_DEFINED__
#include <tdbgeo.h>			// #AD000412, benötigt für ITRiASSimpleRectangle
#include <xtensnn.h>		// #AD000510, benötigt für DexNotificationProc

#if _TRiAS_VER >= 0x0300
#include <TRiASDB.h>
#endif // _TRiAS_VER >= 0x0300

#include <Com/PropertyHelper.h>			// #AD000411

#include "Strings.h"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "objs.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG


///////////////////////////////////////////////////////////////////////////////
// verwendete SmartInterface's etc.
DefineSortingEnumerator(LONG);					// SEnumLONG

#if _TRiAS_VER >= 0x0300
// CLSID_OleDocumentWrapper == CLSID_TRiASProject
EXTERN_C const CLSID __declspec(selectany) CLSID_OleDocumentWrapper = {0x1CB3AB64,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID __declspec(selectany) IID_ITRiASProject = {0x1CB3AB62,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

DefineSmartInterface(OleItemContainer);			// WOleItemContainer
DefineSmartInterface(TRiASProject);				// WTRiASProject
DefineSmartInterface(Storage);					// #AD991027
DefineSmartInterface(PersistStreamInit);		// #AD991027
DefineSmartInterface(OleObject);				// #AD991102
DefineSmartInterface(PersistFile);				// #AD991102
DefineSmartInterface(TRiASPropertyBase);		// #AD000411
DefineSmartInterface(TRiASProperties);			// #AD000411
DefineSmartInterface(TRiASSimpleRectangle);		// #AD000412
#endif // _TRiAS_VER >= 0x0300

// Kopierte Helperfunktionen (Deklarationen)
HDC WINAPI _AfxOleCreateDC(DVTARGETDEVICE* ptd);

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CGeoDoc::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID) 
		return E_POINTER;

	*pClsID = CLSID_OleDocumentWrapper;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistFile methods
STDMETHODIMP CGeoDoc::IsDirty (void)
{
	return DEX_IsGeoDBDirty() ? S_OK : S_FALSE;
}

// Dokument in TRiAS eröffnen und lokal als geöffnet registrieren
STDMETHODIMP CGeoDoc::Load (LPCOLESTR pszFileName, DWORD dwMode)
{
	D_OUTF(1, "[%p] CGeoDoc::Load", this);
	USES_CONVERSION;
	if (m_FileMK.IsValid())
		return E_UNEXPECTED;

// funktioniert lediglich für COM-Projekte
	if (S_OK != StgIsStorageFile (pszFileName))
		return E_NOTIMPL;

// jetzt Doc fertig initialisieren
	if (!FInitInternal (OLE2A(pszFileName))) 
		return E_OUTOFMEMORY;

// Dokument eröffnen und bei TRiAS anmelden
	if (!m_pApp -> FAddDoc (this))		// im DocTree anmelden
		return E_OUTOFMEMORY;

// OpenDocument findet dieses Dokument wieder
	COM_TRY {
		THROW_FAILED_HRESULT(m_pApp -> OpenDocument (OLE2A(pszFileName), NULL, NULL, 0, dwMode));

	// establish connection to the application-supplied notifications
		THROW_FAILED_HRESULT(FConnect (&m_dwCookie));

	// Dokument bei OLE anmelden
		THROW_FAILED_HRESULT(Rename (OLE2A(pszFileName)));
		Validate();

	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppv()))
			_com_issue_error(E_UNEXPECTED);

	WTRiASPropertyBase PropBase(Prj);
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(PropBase -> get_Properties (Props.ppi()));

		m_SizeExtContent.cx = GetProperty (Props, g_cbExtContX, 3000);
		m_SizeExtContent.cy = GetProperty (Props, g_cbExtContY, 3000);

	} COM_CATCH;
    return S_OK;
}

STDMETHODIMP CGeoDoc::Save (LPCOLESTR pszFileName, BOOL fRemember)
{
	D_OUTF(1, "[%p] CGeoDoc::Save (not used here)", this);
	return NOERROR;		// not used here
}

STDMETHODIMP CGeoDoc::SaveCompleted (LPCOLESTR pszFileName)
{
	D_OUTF(1, "[%p] CGeoDoc::SaveCompleted (not used here)", this);
	return NOERROR;		// not used here
}

STDMETHODIMP CGeoDoc::GetCurFile (LPOLESTR *ppszFileName)
{
	D_OUTF(1, "[%p] CGeoDoc::GetCurFile", this);

	if (NULL == ppszFileName) 
		return E_POINTER;

	USES_CONVERSION;
	*ppszFileName = SysAllocString (A2OLE(GetName()));
	return (NULL != ppszFileName) ? S_OK : E_OUTOFMEMORY;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStorage methods
STDMETHODIMP CGeoDoc::InitNew (IStorage *pIStg)
{
	D_OUTF(1, "[%p] CGeoDoc::InitNew", this);

// jetzt Doc fertig initialisieren
CString strNoName;

	VERIFY(strNoName.LoadString(IDS_NONAME));
	if (!FInitInternal (strNoName)) {
		D_OUTF(1, "[%p] CGeoDoc::InitNew ==> FInitInternal failed", this);
		return E_OUTOFMEMORY;
	}

// Dokument eröffnen und bei TRiAS anmelden
	if (!m_pApp -> FAddDoc (this)) {		// im DocTree anmelden
		D_OUTF(1, "[%p] CGeoDoc::InitNew ==> FAddDoc failed", this);
		return E_OUTOFMEMORY;
	}

// DatenBasis mit gegebenen Parametern anlegen und evtl. eröffnen
CREATEDBEX cDB;
CGeoDoc *pDoc = NULL;

	INITSTRUCT (cDB, CREATEDBEX);
	cDB.m_pName = (LPSTR)(LPCSTR)strNoName;
	cDB.m_pUser = NULL;
	cDB.m_pPassWd = NULL;
	cDB.m_iMode = OPENMODE_HideDocument|OPENMODE_DoNotAddToMRU|OPENMODE_CreateInternalDatasource;
	cDB.m_pIStorage = pIStg;
	cDB.m_pClsID = NULL;	// ClassID, (NULL für CLSID_DirisProject)
	cDB.m_pCFStr = NULL;	// ClipboarFormat (NULL für TRiAS.Document.2)

// GeoDB erzeugen
ErrCode EC = DEX_CreateNewGeoDB(cDB);	// Projekt erzeugen

	if (EC != EC_OKAY && EC != WC_RETURN) {
	// Fehler aufgetreten
		D_OUTF(1, "[%p] CGeoDoc::InitNew ==> DEX_CreateNewGeoDB failed", this);
		return EC;							 // WC_WDHLG ==> TRUE! #AD991103
	}

	m_SizeExtContent.cx = 3000;		// Himetric
	m_SizeExtContent.cy = 3000;
	m_SizeExtThumbnail.cx = 3000;	// Himetric
	m_SizeExtThumbnail.cy = 3000;
	m_SizeExtIcon.cx = 3000;		// Himetric
	m_SizeExtIcon.cy = 3000;
	m_SizeExtPrint.cx = 3000;		// Himetric
	m_SizeExtPrint.cy = 3000;

// If execution has reached this point, then no errors have occurred.
	Validate();		// CGeoDoc is now valid

	D_OUTF(1, "[%p] CGeoDoc::InitNew ==> S_OK", this);
	return S_OK;
}

STDMETHODIMP CGeoDoc::Load (IStorage *pIStg)
{
	D_OUTF( 1, "[%p] CGeoDoc::Load(IStorage*)", this);
	COM_TRY {
	// jetzt Doc fertig initialisieren
	CString strNoName;

		VERIFY(strNoName.LoadString(IDS_NONAME));
		if (!FInitInternal (strNoName)) {
			D_OUTF(1, "[%p] CGeoDoc::Load(IStorage*) ==> FInitInternal failed", this);
			return E_OUTOFMEMORY;
		}

	// Dokument eröffnen und bei TRiAS anmelden
		if (!m_pApp -> FAddDoc (this)) {		// im DocTree anmelden
			D_OUTF(1, "[%p] CGeoDoc::Load(IStorage*) ==> FAddDoc failed", this);
			return E_OUTOFMEMORY;
		}

	TRIAS_OPENSTG tos;

		INITSTRUCT (tos, TRIAS_OPENSTG);
		tos.pcProject = strNoName;
		tos.iMode = OM_NoStandard|OM_ActivateDBO;
		tos.m_pIStorage = pIStg;

	// GeoDB aus Storage öffnen
	ErrCode EC = DEX_OpenProject(tos);	// Projekt eröffnen

		if (EC != EC_OKAY && EC != WC_RETURN) {
		// Fehler aufgetreten
			D_OUTF(1, "[%p] CGeoDoc::Load(IStorage*) ==> DEX_OpenProject failed", this);
			return EC;							 // WC_WDHLG ==> TRUE! #AD991103
		}

	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppv()))
			return E_UNEXPECTED;

	// letzte aktuelle Ansicht laden
	WTRiASPropertyBase PropBase(Prj);
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(PropBase -> get_Properties (Props.ppi()));

	CComBSTR bstrLastView (GetProperty (Props, g_cbLastView, CComBSTR(g_cbNil)));

		if (!!bstrLastView && bstrLastView.Length() > 0)
		{
			THROW_FAILED_HRESULT(put_ActiveViewName (bstrLastView));
		}

	// letzte Größen laden
		m_SizeExtContent.cx = GetProperty (Props, g_cbExtContX, 3000);
		m_SizeExtContent.cy = GetProperty (Props, g_cbExtContY, 3000);

	long c[4];

		c[0] = GetProperty (Props, g_cbLastContLeft, 0L);
		c[1] = GetProperty (Props, g_cbLastContRight, 0L);
		c[2] = GetProperty (Props, g_cbLastContTop, 0L);
		c[3] = GetProperty (Props, g_cbLastContBottom, 0L);
		if (0 != c[0] && 0 != c[1] && 0 != c[2] && 0 != c[3])
			DEX_SetActiveSightContainer(c);

	// If execution has reached this point, then no errors have occurred.
		Validate();		// CGeoDoc is now valid

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	D_OUTF(1, "[%p] CGeoDoc::Save(IStorage*) ", this);

	COM_TRY {
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppv()))
			return E_UNEXPECTED;

	WTRiASPropertyBase PropBase(Prj);
	WTRiASProperties Props;
	PROPERTY_TYPE rgType = PROPERTY_TYPE (PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_Hidden);

		THROW_FAILED_HRESULT(PropBase -> get_Properties (Props.ppi()));

	CComBSTR bstrLastView;

		if (SUCCEEDED(get_ActiveViewName (&bstrLastView)))
		{
			THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbLastView, bstrLastView, rgType, true));
		}

	long c[4];

		DEX_GetActiveSightContainer(c);

		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbLastContLeft, c[0], rgType, true));
		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbLastContRight, c[1], rgType, true));
		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbLastContTop, c[2], rgType, true));
		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbLastContBottom, c[3], rgType, true));
		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbExtContX, m_SizeExtContent.cx, rgType, true));
		THROW_FAILED_HRESULT(SetPropertyAndType (Props, g_cbExtContY, m_SizeExtContent.cy, rgType, true));

	// jetzt an alle anderen weiterreichen
	WStorage IStg(pIStg);

		if (fSameAsLoad) {
			THROW_FAILED_HRESULT(DEX_SaveSameStorage(pIStg));
		} else {
			THROW_FAILED_HRESULT(DEX_SaveOtherStorage(pIStg));
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::SaveCompleted (IStorage *pIStg)
{
	D_OUTF(1, "[%p] CGeoDoc::SaveCompleted()\n", this);

HRESULT hr = DEX_SaveCompleted(pIStg);

	if (FAILED(hr)) return hr;

// evtl. vorliegende Änderungen auch den Clients mitteilen!
	OnDataChanged();
	return S_OK;
}

STDMETHODIMP CGeoDoc::HandsOffStorage (void)
{
	D_OUTF(1, "[%p] CGeoDoc::HandsOffStorage\n", this);

HRESULT hr = E_FAIL;

	return DEX_HandsOffStorage(pIStg);
/*
	if ( m_lpRootStg != NULL )
	{
		// first call HandsOffStorage for all the embedded client items
		POSITION pos = pThis->GetStartPosition();
		COleClientItem* pItem;
		while ((pItem = pThis->GetNextClientItem(pos)) != NULL)
		{
			ASSERT(pItem->m_lpObject != NULL);
			LPPERSISTSTORAGE lpPersistStorage =
				QUERYINTERFACE(pItem->m_lpObject, IPersistStorage);
			ASSERT(lpPersistStorage != NULL);
			lpPersistStorage->HandsOffStorage();
			lpPersistStorage->Release();
		}

		// for now, can't access the storage
		RELEASE( m_lpRootStg );
	}
	return S_OK;
*/
}

///////////////////////////////////////////////////////////////////////////////
// IOleContainer methods
STDMETHODIMP CGeoDoc::EnumObjects (DWORD grfFlags, IEnumUnknown **ppenum)
{
#if defined(_DEBUG)
bool isSource = ((OLE2AutoExtension *)g_pTE) -> IsSource();

	MessageBox (NULL, "EnumObjects", isSource ? "Source" : "Dest", MB_OK);
#endif // _DEBUG
	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::LockContainer (BOOL fLock)
{
//	return CoLockObjectExternal ((_DDocument *)this, fLock, true);
	if (fLock)
		((_DDocument *)this)->AddRef();
	else
		((_DDocument *)this)->Release();
	return S_OK;
}

// IOleItemContainer methods
STDMETHODIMP CGeoDoc::GetObject (LPOLESTR pszItem, DWORD dwSpeedNeeded,
	IBindCtx *pbc, REFIID riid, void **ppvObject)
{
HRESULT hr = GetRunning (pszItem, dwSpeedNeeded, pbc, riid, ppvObject, false);

	if (BINDSPEED_IMMEDIATE == dwSpeedNeeded && S_OK != hr)
		return MK_E_EXCEEDEDDEADLINE;

// if object was running we are done!
	if (S_OK == hr) return S_OK;

// alles andere muß explizit erst geladen und instantiiert werden
// ...
	return hr;
}

STDMETHODIMP CGeoDoc::GetObjectStorage (LPOLESTR pszItem, 
	IBindCtx *pbc, REFIID riid, void **ppvStorage)
{
	D_OUTF(1, "[%p] CGeoDoc::GetObjectStorage ==> E_NOTIMPL", this);
	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::IsRunning (LPOLESTR pszItem)
{
#if defined(_DEBUG)
bool isSource = ((OLE2AutoExtension *)g_pTE) -> IsSource();

	MessageBox (NULL, "IsRunning", isSource ? "Source" : "Dest", MB_OK);
#endif // _DEBUG
	return GetRunning (pszItem, 0L, NULL, IID_NULL, NULL, true);
}

///////////////////////////////////////////////////////////////////////////////
// umbenennen eines Dokumentes
HRESULT CGeoDoc::Rename (LPCSTR pcName)
{
	USES_CONVERSION;

	RenamingFile();

	if (NULL == pcName) return S_OK;

#if defined(_DEBUG)
// BoundsChecker hat Probleme mit dem folgenden Code, 
// also evtl. einfach weitermachen
CCurrentUser regCfg (KEY_READ, "Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
DWORD dwFlags = 0;

	if (regCfg.GetDWORD ("FakeBoundsChecker", dwFlags) && dwFlags != 0)
		return S_OK;
#endif

HRESULT hr = CreateFileMoniker (A2OLE(pcName), m_FileMK.ppi());

	if (SUCCEEDED(hr)) {
	FILETIME ft;

		CoFileTimeNow (&ft);
		hr = RegisterAsRunning(ROTFLAGS_REGISTRATIONKEEPSALIVE, (_DDocument *)this, m_FileMK, &m_dwRegROT); 
		if (SUCCEEDED(hr))
			NoteChangeTime (m_dwRegROT, &ft);

	// give moniker to linked objects in tenants (InsideOLE S. 997)
	// ...

	// register a File!"\" wildcard moniker as well
	WMoniker mkAll;

		hr = CreateItemMoniker(g_cbuMkDel, L"\\", mkAll.ppi());
		if (SUCCEEDED(hr)) {
		WMoniker mkWild;

			hr = m_FileMK -> ComposeWith (mkAll, false, mkWild.ppi());
			if (SUCCEEDED(hr)) 
				hr = RegisterAsRunning(0, (_DDocument *)this, mkWild, &m_dwRegROTAll);
			if (SUCCEEDED(hr))
				NoteChangeTime (m_dwRegROTAll, &ft);
		}
	}
	return S_OK;
}

// Datei soll umbennant werden
HRESULT CGeoDoc::RenamingFile (void)
{
	RevokeAsRunning (&m_dwRegROT);
	RevokeAsRunning (&m_dwRegROTAll);
	return S_OK;
}

// Projekt wurde gespeichert
HRESULT CGeoDoc::ProjectSaved (void)
{
FILETIME ft;

	CoFileTimeNow (&ft);
	NoteChangeTime (m_dwRegROT, &ft);
	NoteChangeTime (m_dwRegROTAll, &ft);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob das gesuchte Objekt bereits aktiv ist
static KNOWNOBJECT g_cbKnownObjects[] = {
	{ g_cbMkGeoClass, _tcsclen(g_cbMkGeoClass), CGeoDoc::GetGeoClass, true, CGeoDoc::NoParseDisplayName },
	{ g_cbMkGeoView, _tcsclen(g_cbMkGeoView), CGeoDoc::GetGeoView, true, CGeoDoc::NoParseDisplayName },
	{ g_cbMkGeoObjects36, _tcsclen(g_cbMkGeoObjects36), CGeoDoc::GetGeoObjects36, true, CGeoDoc::NoParseDisplayName },
	{ g_cbMkGeoObjects, _tcsclen(g_cbMkGeoObjects), CGeoDoc::GetGeoObjects10, true, CGeoDoc::NoParseDisplayName },
	{ g_cbMkGeoObject, _tcsclen(g_cbMkGeoObject), CGeoDoc::GetGeoObject, true, CGeoDoc::NoParseDisplayName },
	{ g_cbMkConnection, _tcsclen(g_cbMkConnection), CGeoDoc::GetFromProject, false, CGeoDoc::ParseFromProject },
	{ g_cbMkObjectsDef, _tcsclen(g_cbMkObjectsDef), CGeoDoc::GetFromProject, false, CGeoDoc::ParseFromProject },
	{ NULL, 0, NULL, },		// EndeKennung
};

HRESULT CGeoDoc::GetRunning (LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, 
	REFIID riid, void **ppvObject, bool fTestRunningOnly)
{
	USES_CONVERSION;

KNOWNOBJECT *pObjs = g_cbKnownObjects;
LPCTSTR pcItem = OLE2A(pszItem);

	while (NULL != pObjs->pcObjName) {
		if (0 == _tcsnccmp (pcItem, pObjs->pcObjName, pObjs->iObjNameSize)) {
		// retrieve object, eat ObjectTypeName and ':'
			if (pObjs -> fEatGetObjectPrefix)
				return (this ->* (pObjs->fnGetObject)) (pcItem+pObjs->iObjNameSize+1, dwSpeedNeeded, pbc, riid, ppvObject, fTestRunningOnly);
			else
				return (this ->* (pObjs->fnGetObject)) (pcItem, dwSpeedNeeded, pbc, riid, ppvObject, fTestRunningOnly);
		}

	// next objecttype
		pObjs++;
	}

// hier noch nach embedded objects sehen (s.Inside OLE S. 484)
// ...
	return E_FAIL;		// not supported or not found
}

// IParseDisplayName methods
STDMETHODIMP CGeoDoc::ParseDisplayName (IBindCtx *pbc, LPOLESTR pcItem, ULONG *pchEaten, IMoniker **ppmkOut)
{
LPOLESTR pcOrigItem = pcItem;

	if (*pcItem == '!') {
		(*pchEaten)++;
		pcItem++;
	}

KNOWNOBJECT *pObjs = g_cbKnownObjects;

	USES_CONVERSION;
	while (NULL != pObjs -> pcObjName) {
		if (0 == _tcsnccmp (OLE2A(pcItem), pObjs -> pcObjName, pObjs -> iObjNameSize))
		// delegate fully to given Parsing procedure
			return (this ->* (pObjs -> fnParseDisplayName)) (pbc, pcOrigItem, pchEaten, ppmkOut);
			
	// next objecttype
		pObjs++;
	}
	return MK_E_SYNTAX;
}

///////////////////////////////////////////////////////////////////////////////
// Heraussuchen eines bestimmten Objektes aus unseren DatenStrukturen
HRESULT CGeoDoc::GetGeoClass (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	return E_NOTIMPL;
}

HRESULT CGeoDoc::GetGeoView (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	return E_NOTIMPL;
}

HRESULT CGeoDoc::GetGeoObject (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	return E_NOTIMPL;
}

HRESULT CGeoDoc::GetGeoObjects36 (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, 
	bool fTestRunningOnly)
{
	if (fTestRunningOnly) return S_FALSE;	// muß erst instantiiert werden

// Enumerator mit gewünschten Objektnummern bilden
HOBJECT lONr = INVALID_HOBJECT;
HOBJECT lLastONr = INVALID_HOBJECT;
LPTSTR pNext = const_cast<LPTSTR>(pcItem);
LPTSTR pBegin = pNext;
SEnumLONG EnumOut;			// wird mit ObjektNummern gefüllt
HRESULT hr = E_FAIL;
bool fFirst = true;

	while (TEXT('\0') != *pNext) {
		if (fFirst) {
			fFirst = false;
			lONr = _tcstoul (pBegin, &pNext, 36);
		}
		else {
		long lONrDelta = 0;

			_ASSERTE(INVALID_HOBJECT != lLastONr);
			if (TEXT('+') == *pNext) {
				lONrDelta = _tcstoul (pBegin, &pNext, 36);
				lONr = lLastONr + lONrDelta;
			}
			else {
				_ASSERTE(TEXT('-') == *pNext);
				lONrDelta = _tcstoul (pBegin, &pNext, 36);
				lONr = lLastONr - lONrDelta;
			}
		}
		if (pBegin == pNext)
			break;				// nichts mehr gefunden

		hr = EnumOut.AddItem (lONr);
		if (FAILED(hr)) return hr;

		pBegin = pNext+1;		// Komma überspringen
		lLastONr = lONr;
	}

// GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
		(_DDocument *)this, m_pApp, this, GetObjectsFromEnum, 
		(DWORD)(IEnum<LONG> *)&EnumOut, NULL);

// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	hr = ((_DGeoObjects *)pCObjects) -> QueryInterface (riid, (LPVOID *)ppvObj);
	((_DGeoObjects *)pCObjects) -> Release();

	return hr;
}

HRESULT CGeoDoc::GetGeoObjects10 (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, 
	bool fTestRunningOnly)
{
	if (fTestRunningOnly) return S_FALSE;	// muß erst instantiiert werden

// Enumerator mit gewünschten Objektnummern bilden
LONG lONr = INVALID_ONR;
LPTSTR pNext = const_cast<LPTSTR>(pcItem);
LPTSTR pBegin = pNext;
SEnumLONG EnumOut;			// wird mit ObjektNummern gefüllt
HRESULT hr = E_FAIL;

	while (TEXT('\0') != *pNext) {
		lONr = _tcstoul (pBegin, &pNext, 10);
		if (pBegin == pNext)
			break;			// nichts mehr gefunden

		hr = EnumOut.AddItem (lONr);
		if (FAILED(hr)) return hr;

		pBegin = pNext+1;	// Komma überspringen
	}

// GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
		(_DDocument *)this, m_pApp, this, GetObjectsFromEnum, 
		(DWORD)(IEnum<LONG> *)&EnumOut, NULL);

// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	hr = ((_DGeoObjects *)pCObjects) -> QueryInterface (riid, (LPVOID *)ppvObj);
	((_DGeoObjects *)pCObjects) -> Release();

	return hr;
}

HRESULT CGeoDoc::GetFromProject (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, 
	LPVOID *ppvObj, bool fTestRunningOnly)
{
#if _TRiAS_VER >= 0x0300
// Die Anfrage an das Objekt TRiASProject weiterleiten (soweit vorhanden)
	COM_TRY {
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppv()))
			return E_UNEXPECTED;

	WOleItemContainer Item (Prj);
	CComBSTR bstrItem (pcItem);

		if (fTestRunningOnly)
			return Item -> IsRunning(bstrItem);
		
		THROW_FAILED_HRESULT(Item -> GetObject (bstrItem, dwSpeedNeeded, pbc, riid, ppvObj));

	} COM_CATCH;
	return S_OK;
#else
	return E_NOTIMPL;
#endif // _TRiAS_VER >= 0x0300
}

///////////////////////////////////////////////////////////////////////////////
// ParseDisplayName's
HRESULT CGeoDoc::NoParseDisplayName (
	IBindCtx *pbc, LPOLESTR pszDisplayName,	ULONG *pchEaten, IMoniker **ppmkOut)
{
	return MK_E_SYNTAX;
}

HRESULT CGeoDoc::ParseFromProject (
	IBindCtx *pbc, LPOLESTR pszDisplayName,	ULONG *pchEaten, IMoniker **ppmkOut)

{
#if _TRiAS_VER >= 0x0300
// Die Anfrage an das Objekt TRiASProject weiterleiten (soweit vorhanden)
	COM_TRY {
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppv()))
			return E_UNEXPECTED;

		THROW_FAILED_HRESULT(WOleItemContainer(Prj) -> ParseDisplayName (pbc, pszDisplayName, pchEaten, ppmkOut));

	} COM_CATCH;
	return S_OK;
#else
	return E_NOTIMPL;
#endif // _TRiAS_VER >= 0x0300
}

///////////////////////////////////////////////////////////////////////////////
// IDataObject methods
HRESULT CGeoDoc::CreateDataObject()
{
	D_OUTF(1, "[%p] CreateDataObject", this );

	RETURN_FAILED_HRESULT(m_DataObject.CreateInstance(CLSID_DataTransferObject));
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetData(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
#if defined(_DEBUG)
	switch (pFE -> cfFormat) {
	case CF_METAFILEPICT:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_METAFILEPICT) !!", this);
		break;

	case CF_TEXT:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_TEXT)", this);
		break;

	case CF_BITMAP:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_BITMAP) !!", this);
		break;

	case CF_SYLK:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_SYLK)", this);
		break;

	case CF_DIF:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_DIF)", this);
		break;

	case CF_TIFF:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_TIFF)", this);
		break;

	case CF_OEMTEXT:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_OEMTEXT)", this);
		break;

	case CF_DIB:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_DIB) !!", this);
		break;

	case CF_UNICODETEXT:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_UNICODETEXT)", this);
		break;

	case CF_ENHMETAFILE:
		D_OUTF(1,"[%p] CGeoDoc::GetData (CF_ENHMETAFILE) !!", this);
		break;

	default:
		D_OUTF(1,"[%p] CGeoDoc::GetData (other Format)", this);
		break;
	}
#endif // defined(_DEBUG)

	if (!m_DataObject)
		CreateDataObject();

// zuerst DataObject auf den aktuellen Stand bringen
	memset (pSTM, 0, sizeof(STGMEDIUM));
	if (CF_METAFILEPICT == pFE ->cfFormat || CF_ENHMETAFILE == pFE ->cfFormat)
	{
		if (OnRenderData (pFE, pSTM))
			return S_OK;
		else
			return E_FAIL;
	}

// alle anderen Formate weiterreichen
	if (m_DataObject.IsValid())
		return m_DataObject -> GetData(pFE, pSTM);

	return E_UNEXPECTED;
}

STDMETHODIMP CGeoDoc::GetDataHere(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
	D_OUTF(1,"[%p] CGeoDoc::GetDataHere", this);
/*
	if ( m_DataObject == NULL )	CreateDataObject();

	// zuerst DataObject auf den aktuellen Stand bringen
	if ( m_DataObject != NULL )
		return m_DataObject ->GetDataHere(pFE,pSTM);
	else
		return E_UNEXPECTED;
*/
	return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::QueryGetData(FORMATETC __RPC_FAR *pformatetc)
{
	if (!m_DataObject)
		CreateDataObject();

#if defined(_DEBUG)
//#define CF_TEXT             1
//#define CF_BITMAP           2
//#define CF_METAFILEPICT     3
//#define CF_SYLK             4
//#define CF_DIF              5
//#define CF_TIFF             6
//#define CF_OEMTEXT          7
//#define CF_DIB              8
//#define CF_PALETTE          9
//#define CF_PENDATA          10
//#define CF_RIFF             11
//#define CF_WAVE             12
//#define CF_UNICODETEXT      13
//#define CF_ENHMETAFILE      14
	switch (pformatetc -> cfFormat) {
	case CF_METAFILEPICT:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_METAFILEPICT)", this);
		break;

	case CF_TEXT:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_TEXT)", this);
		break;

	case CF_BITMAP:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_BITMAP) ==> S_OK", this);
		break;

	case CF_SYLK:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_SYLK)", this);
		break;

	case CF_DIF:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_DIF)", this);
		break;

	case CF_TIFF:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_TIFF)", this);
		break;

	case CF_OEMTEXT:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_OEMTEXT)", this);
		break;

	case CF_DIB:
		D_OUTF(1 ,"[%p] CGeoDoc::QueryGetData (CF_DIB) ==> S_OK", this);
		break;

	case CF_UNICODETEXT:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_UNICODETEXT)", this);
		break;

	case CF_ENHMETAFILE:
		D_OUTF(1,"[%p] CGeoDoc::QueryGetData (CF_ENHMETAFILE) ==> S_OK", this);
		break;

	default:
		D_OUTF( 1,"[%p] CGeoDoc::QueryGetData (other Format)", this);
		break;
	}
#endif // defined(_DEBUG)

	switch (pformatetc -> cfFormat) {
	case CF_BITMAP:
	case CF_DIB:
	case CF_METAFILEPICT:
	case CF_ENHMETAFILE:
		return S_OK;

	default:
		break;
	}
	return DV_E_FORMATETC;
}

STDMETHODIMP CGeoDoc::GetCanonicalFormatEtc(
	FORMATETC *pformatetcIn, FORMATETC *pformatetcOut)
{
	D_OUTF(1,"[%p] CGeoDoc::GetCanonicalFormatEtc", this);

    if (NULL == pformatetcOut)
        return E_INVALIDARG;

	memcpy (pformatetcOut, pformatetcIn, sizeof(FORMATETC));
    pformatetcOut -> ptd = NULL;
    return DATA_S_SAMEFORMATETC;
}

STDMETHODIMP CGeoDoc::SetData (FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease)
{
	D_OUTF(1,"[%p] CGeoDoc::SetData", this);
/*
HRESULT hr = NOERROR;

	if ( m_DataObject != NULL )
		hr = m_DataObject -> SetData(pformatetc, pmedium, fRelease);

//	if (SUCCEEDED(hr))
//		Daten auf den neuesten Stand bringen

	return hr;
*/
    return E_NOTIMPL;
}

STDMETHODIMP CGeoDoc::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc)
{
	D_OUTF(1,"[%p] CGeoDoc::EnumFormatEtc", this);
	RETURN_FAILED_HRESULT(OleRegEnumFormatEtc(CLSID_GeoDocument, dwDirection, ppenumFormatEtc));
	return S_OK;
}

STDMETHODIMP CGeoDoc::DAdvise(
	FORMATETC *pFormatEtc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
	D_OUTF(1,"[%p] CGeoDoc::DAdvise", this);
	*pdwConnection = 0;

// this special case is for apps like Excel which ask for DAdvise
// on CF_METAFILEPICT, DVASPECT_ICON for insert as icon.
FORMATETC formatEtc = *pFormatEtc;

	if (formatEtc.cfFormat == CF_METAFILEPICT && formatEtc.dwAspect == DVASPECT_ICON)
	{
		formatEtc.dwAspect = DVASPECT_CONTENT;
	}

// make sure the FORMATETC is valid
	if (!(pFormatEtc->cfFormat == 0 && pFormatEtc->ptd == NULL &&
		  pFormatEtc->dwAspect == -1 && pFormatEtc->lindex == -1 &&
		  pFormatEtc->tymed == -1) &&
		QueryGetData(&formatEtc) != S_OK)
	{
		// it is not a wildcard advise -and- the format is not acceptable
		return DATA_E_FORMATETC;
	}

	// create the advise holder, if necessary
	if (!m_DataAdviseHolder && S_OK != CreateDataAdviseHolder(m_DataAdviseHolder.ppi()))
	{
		return E_OUTOFMEMORY;
	}

	ASSERT(m_DataAdviseHolder != NULL);
	return m_DataAdviseHolder->Advise(this, pFormatEtc, advf, pAdvSink, pdwConnection);
}

STDMETHODIMP CGeoDoc::DUnadvise(DWORD dwConnection)
{
	D_OUTF(1,"[%p] CGeoDoc::DUnadvise", this);

	if (m_DataAdviseHolder == NULL)
		return E_FAIL;

	_ASSERTE(m_DataAdviseHolder.IsValid());
	return m_DataAdviseHolder -> Unadvise(dwConnection);
}

STDMETHODIMP CGeoDoc::EnumDAdvise(IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
{
 	D_OUTF( 1,"[%p] CGeoDoc::EnumDAdvise", this);
 	*ppenumAdvise = NULL;

	if (!m_DataAdviseHolder)
		return E_FAIL;

	_ASSERTE(m_DataAdviseHolder.IsValid());
	return m_DataAdviseHolder -> EnumAdvise(ppenumAdvise);
}

//////////////////////////////////////////////////////////////////////////////
// special CItemDataSource implementation
BOOL CGeoDoc::CItemDataSource::OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal)
{
	D_OUTF(1,"[%p] CGeoDoc::CItemDataSource::OnRenderGlobalData", this);

CGeoDoc *pItem = (CGeoDoc *)((BYTE *)this - offsetof(CGeoDoc, m_dataSource));

	return pItem -> OnRenderGlobalData(lpFormatEtc, phGlobal);	// Note: COleDataSource has no implementation
}

BOOL CGeoDoc::CItemDataSource::OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile)
{
//	TRACE("[%p] CGeoDoc::CItemDataSource::OnRenderFileData", this);
	D_OUTF( 1,"[%p] CGeoDoc::CItemDataSource::OnRenderFileData", this);

CGeoDoc *pItem = (CGeoDoc *)((BYTE *)this - offsetof(CGeoDoc, m_dataSource));

	return pItem -> OnRenderFileData(lpFormatEtc, pFile);		// Note: COleDataSource has no implementation
}

BOOL CGeoDoc::CItemDataSource::OnRenderData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	D_OUTF(1,"[%p] CGeoDoc::CItemDataSource::OnRenderData", this);

CGeoDoc *pItem = (CGeoDoc *)((BYTE *)this - offsetof(CGeoDoc, m_dataSource));

	if (pItem -> OnRenderData(lpFormatEtc, lpStgMedium))
		return TRUE;

	return COleDataSource::OnRenderData(lpFormatEtc, lpStgMedium);
}

BOOL CGeoDoc::CItemDataSource::OnSetData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL bRelease)
{
	D_OUTF(1,"[%p] CGeoDoc::CItemDataSource::OnSetData", this);

CGeoDoc *pItem = (CGeoDoc *)((BYTE *)this - offsetof(CGeoDoc, m_dataSource));

	return pItem->OnSetData(lpFormatEtc, lpStgMedium, bRelease);	// Note: COleDataSource has no implementation
}

// Helper methods
BOOL CGeoDoc::OnSetData(LPFORMATETC /*lpFormatEtc*/, LPSTGMEDIUM /*lpStgMedium*/,
								BOOL /*bRelease*/)
{
	D_OUTF(1,"[%p] CGeoDoc::OnSetData", this);
	return FALSE;   // default does nothing
}

BOOL CGeoDoc::OnRenderGlobalData(LPFORMATETC /*lpFormatEtc*/, HGLOBAL* /*phGlobal*/)
{
	D_OUTF(1,"[%p] CGeoDoc::OnRenderGlobalData", this);
	return FALSE;   // default does nothing
}

BOOL CGeoDoc::OnRenderFileData(LPFORMATETC /*lpFormatEtc*/, CFile* /*pFile*/)
{
	D_OUTF( 1,"[%p] CGeoDoc::OnRenderFileData", this);
	return FALSE;   // default does nothing
}

BOOL CGeoDoc::OnRenderData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	D_OUTF( 1,"[%p] CGeoDoc::OnRenderData", this);
	ASSERT(AfxIsValidAddress(lpFormatEtc, sizeof(FORMATETC), FALSE));
	ASSERT(AfxIsValidAddress(lpStgMedium, sizeof(STGMEDIUM)));

	// this implementation does not support extended layout
	if (lpFormatEtc->lindex != -1)
		return FALSE;

	if (lpFormatEtc->cfFormat == CF_METAFILEPICT ||	lpFormatEtc->cfFormat == CF_ENHMETAFILE)
		return GetMetafileData(lpFormatEtc, lpStgMedium);

	return FALSE;   // cfFormat not supported
}

// Hilfsdeklaration
HMETAFILE ConvEMFtoWMF(HDC hrefDC, HENHMETAFILE hEMF);
void SaveEMF(HENHMETAFILE hEMF);
void SaveWMF(HMETAFILE hMF);

BOOL CGeoDoc::GetMetafileData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	D_OUTF( 1,"[%p] CGeoDoc::GetMetafileData", this);

//	if ( m_bPaintStarted )
//	{
//		m_bWait4StopPaint = TRUE;
//		return TRUE;
//	}

	_ASSERTE(AfxIsValidAddress(lpFormatEtc, sizeof(FORMATETC), FALSE));
	_ASSERTE(AfxIsValidAddress(lpStgMedium, sizeof(STGMEDIUM)));

	_ASSERTE(lpStgMedium->tymed == TYMED_NULL);		// GetDataHere not valid
	_ASSERTE(lpStgMedium->pUnkForRelease == NULL);

// medium must be TYMED_MFPICT -- cannot fill in existing HGLOBAL
	if (lpStgMedium->hGlobal != NULL)
	{
		::GlobalFree(lpStgMedium->hGlobal);
		lpStgMedium->hGlobal = NULL;
	}

// medium must be TYMED_MFPICT
	if (!(lpFormatEtc->tymed & TYMED_MFPICT || lpFormatEtc->tymed & TYMED_ENHMF) ||
		lpStgMedium -> hGlobal != NULL)
		return FALSE;

// create appropriate memory metafile DC
CMetaFileDC dc;

// create attribute DC according to lpFormatEtc->ptd
CDC hAttribDC;

	hAttribDC.Attach(_AfxOleCreateDC(lpFormatEtc->ptd));
	if (NULL == hAttribDC.m_hDC)
		return FALSE;

CSize size(m_SizeExtContent);
BOOL bResult = TRUE;
CFont font;
CFont *pFont = NULL;
CRect rectEll(CRect( 100, -100, m_SizeExtContent.cx-100, -(m_SizeExtContent.cy-100) ));
CString	strText (g_cbTRiAS);

long c[4];
RECTL cont;
RECTL rclClipBox, rclFrame, rectl;

	if (lpFormatEtc->cfFormat == CF_ENHMETAFILE || lpFormatEtc->cfFormat == CF_METAFILEPICT) {
		::SaveDC (hAttribDC.m_hDC);
		::SetMapMode (hAttribDC.m_hDC, MM_HIMETRIC);

	CRect rectBounds;
	RENDERGEODB sRend;
	double dV1, dV2;
	double dB;
	HRESULT	hr = DEX_GetActiveSightContainer(c);

		cont.left = c[0];
		cont.top = c[3];
		cont.right = c[1];
		cont.bottom = c[2];

	double xT = fabs((cont.left - cont.right) * 0.2);
	double yT = fabs((cont.top - cont.bottom) * 0.2);

		cont.left = cont.left + xT;
		cont.top = cont.top - yT;
		cont.right = cont.right - xT;
		cont.bottom = cont.bottom + yT;

		xT = fabs(cont.left - cont.right);
		yT = fabs(cont.top - cont.bottom);

	double xB = fabs(m_SizeExtContent.cx);
	double yB = fabs(m_SizeExtContent.cy);

		dV1 = xT / yT;
		dV2 = xB / yB;
		if (dV1 > dV2) {
		// Der TRiAS-Ausschnitt ist breiter als das Zielfenster
			dB = (xT - xB*yT / yB) * 0.5;
			cont.left += dB;
			cont.right -= dB;
		} else {
		// Dann also höher!
			dB = (yT - yB*xT / xB) * 0.5;
			cont.top += dB;
			cont.bottom -= dB;
		}

	// Strukturen fürs rendern vorbereiten
		rclFrame.left = 0;
		rclFrame.right = m_SizeExtContent.cx;
		rclFrame.top = 0;
		rclFrame.bottom = - m_SizeExtContent.cy;

		rclClipBox.left = rclFrame.left + 100;
		rclClipBox.right = rclFrame.right - 100;
		rclClipBox.top = rclFrame.top - 100;
		rclClipBox.bottom = rclFrame.bottom + 100;

		rectl.bottom = labs(rclFrame.bottom - rclFrame.top);
		rectl.top = 0L;
		rectl.right = labs(rclFrame.right - rclFrame.left);
		rectl.left = 0L;

		rectBounds.top = rectl.top;
		rectBounds.bottom = rectl.bottom;
		rectBounds.left = rectl.left;
		rectBounds.right = rectl.right;

//		if (!dc.CreateEnhanced(CDC::FromHandle( hAttribDC ), "C:\\OLE.emf", &rectBounds, "TRiAS OLE\0Embedded\0\0"))
//		if (!dc.CreateEnhanced(NULL, "C:\\OLE.emf", &rectBounds, "TRiAS OLE\0Embedded\0\0"))
//		if (!dc.CreateEnhanced(CDC::FromHandle( hAttribDC ), "C:\\OLE.emf", NULL, "TRiAS OLE\0Embedded\0\0"))

//		if (!dc.CreateEnhanced(CDC::FromHandle( hAttribDC ), "C:\\OLE.emf", &rectBounds, "TRiAS OLE\0Embedded\0\0"))
//		if (!dc.CreateEnhanced(NULL, "C:\\OLE.emf", &rectBounds, "TRiAS OLE\0Embedded\0\0"))
		if (!dc.CreateEnhanced(NULL, NULL, &rectBounds, "TRiAS OLE\0Embedded\0\0"))
			return FALSE;
		dc.SetMapMode(MM_HIMETRIC);

		dc.SetAttribDC(hAttribDC.m_hDC);

		INITSTRUCT( sRend, RENDERGEODB );
		sRend.m_hDC = dc.m_hDC;
		sRend.m_hTargetDC = hAttribDC.m_hDC;

		sRend.m_rclFrame.left =  rectl.left;
		sRend.m_rclFrame.top = -rectl.top;
		sRend.m_rclFrame.right =  rectl.right;
		sRend.m_rclFrame.bottom = -rectl.bottom;

		rclClipBox.left = rectl.left - 100;
		rclClipBox.right = rectl.right + 100;
		rclClipBox.top = rectl.top - 100;
		rclClipBox.bottom = rectl.bottom + 100;

		sRend.m_rclClipBox = rclClipBox;
//		sRend.m_rclClipBox       = sRend.m_rclFrame;

	// Paint directly into the metafile.
//		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetWindowOrg( 0, 0);
		dc.SetWindowExt(m_SizeExtContent.cx, -m_SizeExtContent.cy);
//		dc.SetWindowOrg( 0, -m_SizeExtContent.cy);
//		dc.SetWindowExt(m_SizeExtContent.cx, m_SizeExtContent.cy);

		sRend.m_rclGeoDB = cont;

	// den Rahmen zeichnen wir hier
		rectEll.top = - rectBounds.top;
		rectEll.left =   rectBounds.left;
		rectEll.bottom = - rectBounds.bottom;
		rectEll.right = rectBounds.right;
		dc.Rectangle (rectEll);

		{
		CRgn rgn;
		CSize sz (m_SizeExtContent);
		int	res;

			dc.HIMETRICtoDP (&sz);
			if (rgn.CreateRectRgn (1, 1, sz.cx-1, sz.cy-1)) {
				res = dc.SelectClipRgn (&rgn, RGN_COPY);
	//			if ( ERROR != res )		::SetMetaRgn (dc.m_hDC);
			}
			DEX_RePaintWait();		// sollte TRiAS zeichnen, dann hier warten

			D_OUTF( 1,"  sRend.m_rclGeoDB.top\t= %d", sRend.m_rclGeoDB.top );
			D_OUTF( 1,"  sRend.m_rclGeoDB.bottom\t= %d", sRend.m_rclGeoDB.bottom );
			D_OUTF( 1,"  sRend.m_rclGeoDB.left\t= %d", sRend.m_rclGeoDB.left );
			D_OUTF( 1,"  sRend.m_rclGeoDB.right\t= %d", sRend.m_rclGeoDB.right );

			D_OUTF( 1,"  sRend.m_rclFrame.top\t= %d", sRend.m_rclFrame.top );
			D_OUTF( 1,"  sRend.m_rclFrame.bottom\t= %d", sRend.m_rclFrame.bottom );
			D_OUTF( 1,"  sRend.m_rclFrame.left\t= %d", sRend.m_rclFrame.left );
			D_OUTF( 1,"  sRend.m_rclFrame.right\t= %d", sRend.m_rclFrame.right );

			D_OUTF( 1,"  sRend.m_rclClipBox.top\t= %d", sRend.m_rclClipBox.top );
			D_OUTF( 1,"  sRend.m_rclClipBox.bottom\t= %d", sRend.m_rclClipBox.bottom );
			D_OUTF( 1,"  sRend.m_rclClipBox.left\t= %d", sRend.m_rclClipBox.left );
			D_OUTF( 1,"  sRend.m_rclClipBox.right\t= %d", sRend.m_rclClipBox.right );

			DEX_RenderGeoDB(sRend);		// hier passierts
			rgn.DeleteObject();
		}

		::RestoreDC(hAttribDC.m_hDC, -1);
		dc.SetAttribDC(NULL);			// attribute DC is no longer necessary
	}

	if (!bResult) {
		D_OUTF(1,"[%p] COleServerItem::OnDrawEx() failed.\n", this);
		return FALSE;
	}

// jetzt das Erzeugte abliefern
	if (lpFormatEtc->cfFormat == CF_ENHMETAFILE) {
	HENHMETAFILE hHMF = dc.CloseEnhanced();

		if (hHMF == NULL) 
			return FALSE;

#if defined(_DEBUG)
		SaveEMF(hHMF);
#endif // defined(_DEBUG)

		lpStgMedium->hEnhMetaFile = hHMF;
		lpStgMedium->tymed = TYMED_ENHMF;
	}
	else {
	HENHMETAFILE hHMF = dc.CloseEnhanced();

		if (hHMF == NULL) 
			return FALSE;

#if defined(_DEBUG)
		SaveEMF(hHMF);
#endif // defined(_DEBUG)

	HMETAFILE hMF = ConvEMFtoWMF (hAttribDC.m_hDC, hHMF);

		DeleteEnhMetaFile (hHMF);
		if (hMF == NULL) 
			return FALSE;
#if defined(_DEBUG)
		SaveWMF(hMF);
#endif // defined(_DEBUG)

	HGLOBAL hPict = ::GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE, sizeof(METAFILEPICT));

		if (NULL == hPict) {
			DeleteMetaFile(hMF);
			return FALSE;
		}

	LPMETAFILEPICT lpPict = (LPMETAFILEPICT)::GlobalLock(hPict);

		if (NULL == lpPict) {
			::GlobalFree(hPict);
			return FALSE;
		}

	// set the metafile size
		lpPict->mm = MM_ANISOTROPIC;
		lpPict->hMF = hMF;
		if (size.cx == 0 && size.cy == 0) {
			size.cx = m_SizeExtContent.cx;
			size.cy = m_SizeExtContent.cy;
		}

		lpPict->xExt = size.cx;
		lpPict->yExt = size.cy;  // HIMETRIC height
		if (lpPict -> yExt < 0) {
			TRACE0("Warning: HIMETRIC natural size is negative.\n");
			lpPict->yExt = -lpPict->yExt;   // backward compatibility fix
		}

#ifdef _DEBUG
		if (lpPict->xExt == 0 || lpPict->yExt == 0)
		{
			// usually the natural extent is set to something interesting
			TRACE0("Warning: COleServerItem has no natural size --\n");
			TRACE0("\twill not work with some apps like MS Write.\n");
		}
#endif

	// return the medium with the hGlobal to the METAFILEPICT
		::GlobalUnlock(hPict);
		lpStgMedium -> hGlobal = hPict;
		lpStgMedium -> tymed = TYMED_MFPICT;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// IOleObject methods
STDMETHODIMP CGeoDoc::SetClientSite(LPOLECLIENTSITE pIOleClientSite)
{
	D_OUTF( 1, "[%p] CGeoDoc::SetClientSite", this);

	m_ClientSite = pIOleClientSite;

// do we already have doc object support enabled?
	if (m_pDocObjectServer != NULL)	{
	// If we currently have a document site pointer, release it.
		D_OUTF( 1, "[%p] CGeoDoc::SetClientSite  ReleaseDocSite", this);
		m_pDocObjectServer -> ReleaseDocSite();
	}

	if (pIOleClientSite != NULL) {
	LPOLEDOCUMENTSITE pDocSite;

		if (SUCCEEDED(pIOleClientSite->QueryInterface(IID_IOleDocumentSite,	(LPVOID*) &pDocSite)))
		{
			if (m_pDocObjectServer != NULL)
			{
				D_OUTF( 1, "[%p] CGeoDoc::SetClientSite  SetDocSite", this);
				m_pDocObjectServer -> SetDocSite(pDocSite);
			}
			else {
			// by default, we're not DocObject enabled
//				UNUSED_ALWAYS(pDocSite);
//				return NULL;
//				this->m_pDocObjectServer =	this->GetDocObjectServer(pDocSite);
				D_OUTF(1, "[%p] CGeoDoc::SetClientSite  m_pDocObjectServer = NULL", this);
				m_pDocObjectServer = NULL;
			}
		}
		else
			D_OUTF( 1, "[%p] CGeoDoc::SetClientSite  no IOleDocumentSite", this);
	}
	else
		D_OUTF( 1, "[%p] CGeoDoc::SetClientSite(pIOleClientSite == NULL)", this);

	return S_OK;
}

STDMETHODIMP CGeoDoc::GetClientSite(LPOLECLIENTSITE *ppSite)
{
	D_OUTF( 1, "[%p] CGeoDoc::GetClientSite", this);

	if (NULL == ppSite) {
		D_OUTF( 1, "[%p] CGeoDoc::GetClientSite ==> E_POINTER", this);
		return E_POINTER;
	}

	if (m_ClientSite.IsValid()) {
	WOleClientSite ocs (m_ClientSite);

		*ppSite = ocs.detach();
		return S_OK;
	}
	D_OUTF( 1, "[%p] CGeoDoc::GetClientSite ==> E_UNEXPECTED", this);
	return E_UNEXPECTED;
}

STDMETHODIMP CGeoDoc::SetHostNames(LPCOLESTR pszApp, LPCOLESTR pszObj)
{
	USES_CONVERSION;
	OnSetHostNames(OLE2CT(pszApp), OLE2CT(pszObj));

	D_OUTF( 1,"[%p] CGeoDoc::SetHostNames returns S_OK", this );
	return S_OK;
}

void CGeoDoc::OnSetHostNames(LPCTSTR lpszHost, LPCTSTR lpszHostObj)
{
	ASSERT(lpszHost == NULL || AfxIsValidString(lpszHost));
	ASSERT(lpszHostObj == NULL || AfxIsValidString(lpszHostObj));
	UNUSED(lpszHost);    // unused in release builds

	D_OUTF3(1, "[%p]", this,
			 " CGeoDoc::OnSetHostNames(%s,", lpszHost,
			 " %s)", lpszHostObj);

// only change the title for embedded documents
	if (m_ClientSite.IsValid())	{
	// save name of document for File.Exit update
		if (lpszHostObj == NULL)
			m_strHostObj.LoadString(AFX_IDS_UNTITLED);
		else
			m_strHostObj = lpszHostObj;

		// change title of document to that for an embedded item
		//  (this call will update all of the frames)
		((OLE2AutoExtension *)g_pTE) -> SetTitle (lpszHost, m_strHostObj);
	}
}

STDMETHODIMP CGeoDoc::Close(DWORD dwSaveOption)
{
	D_OUTF( 1, "[%p] CGeoDoc::Close", this);

WUnknown oRef(GetControllingUnknown());

HRESULT hr = S_OK;

	COM_TRY {
	// Notes to Implementers
	// Upon receiving a call to IOleObject::Close, a running object should do the following: 
	//
	// If the object has been changed since it was last opened for editing, it should request
	// to be saved, or not, according to instructions specified in dwSaveOption. If the option
	// is to save the object, then it should call its container's IOleClientSite::SaveObject 
	// interface. 
	// If the object has IDataObject::DAdvise connections with ADVF_DATAONSTOP flags, then it 
	// should send an OnDataChange notification. See IDataObject::DAdvise for details. 
	// If the object currently owns the Clipboard, it should empty it by calling OleFlushClipboard. 
	// If the object is currently visible, notify its container by calling 
	// IOleClientSite::OnShowWindow with the fshow argument set to FALSE. 
	// Send IAdvise::OnClose notifications to appropriate advise sinks. 
	// Finally, forcibly cut off all remoting clients by calling CoDisconnectObject. 
	// If the object application is a local server (an EXE rather than a DLL), closing the 
	// object should also shut down the object application unless the latter is supporting 
	// other running objects or has another reason to remain in the running state. Such reasons 
	// might include the presence of IClassFactory::LockServer locks, end-user control of the 
	// application, or the existence of other open documents requiring access to the application.
	//
	// Calling IOleObject::Close on a linked object disconnects it from, but does not shut down, 
	// its source application. A source application that is visible to the user when the object 
	// is closed remains visible and running after the disconnection and does not send an OnClose 
	// notification to the link container.

		// dwSaveOption == OLECLOSE_SAVEIFDIRTY or OLECLOSE_PROMPTSAVE
		// dann speichern

	// Alle angehängten advise sinks benachrichtigen!
		if (m_AdviseHolder.IsValid())
			m_AdviseHolder -> SendOnClose();

	// delegate through document for most of the work
		if (!Remove())
			hr = E_FAIL;
		else
			DEX_AppQuit(true);

	} COM_CATCH;

	m_ClientSite = (IUnknown*)NULL;
	return S_OK;
}

STDMETHODIMP CGeoDoc::SetMoniker(DWORD /*dwWhich*/, LPMONIKER /*pmk*/)
{
	D_OUTF( 1, "[%p] CGeoDoc::SetMoniker (does nothing)", this);
/*
	if (m_lpClientSite == NULL)
		return E_FAIL;

	// get current full moniker from client-site
	LPMONIKER lpMoniker = NULL;
	if (m_lpClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE,
		OLEWHICHMK_OBJFULL, &lpMoniker) != S_OK)
	{
		// just to make sure -- always set moniker to NULL on failure
		lpMoniker = NULL;
	}

	// update all embedded items with new moniker
	POSITION pos = GetStartPosition();
	COleClientItem* pItem;
	while ((pItem = GetNextClientItem(pos)) != NULL)
	{
		if (pItem->m_bMoniker)
			pItem->m_lpObject->SetMoniker(OLEWHICHMK_CONTAINER, lpMoniker);
	}

	// send Rename advises
	NotifyAllItems(OLE_RENAMED, (DWORD)lpMoniker);
	RELEASE(lpMoniker);
*/
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetMoniker(DWORD dwAssign, DWORD /*dwWhich*/, LPMONIKER *ppmk)
{
	D_OUTF( 1, "[%p] CGeoDoc::GetMoniker (returns E_FAIL)", this);
//	*ppmk = GetMoniker((OLEGETMONIKER)dwAssign);
	*ppmk = NULL;
	return *ppmk == NULL ? E_FAIL : S_OK;
}

STDMETHODIMP CGeoDoc::InitFromData(LPDATAOBJECT pIDataObject, BOOL fCreation,
								   DWORD /*dwReserved*/)
{
	D_OUTF( 1, "[%p] CGeoDoc::InitFromData (does nothing)", this);
/*
	COleServerItem* pItem;
	SCODE sc;
	try
	{
		// delegate through item
		pItem = this->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		COleDataObject dataObject;
		dataObject.Attach(pDataObject,  FALSE);
		sc = pItem->OnInitFromData(&dataObject, fCreation) ? S_OK : S_FALSE;

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return sc;
*/
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetClipboardData(DWORD dwReserved, LPDATAOBJECT *ppIDataObj)
{
	D_OUTF(1, "[%p] CGeoDoc::GetClipboardData (does nothing)", this);
/*
	*ppIDataObj = NULL;

	COleServerItem* pItem;
	SCODE sc = S_OK;
	try
	{
		// delegate through item
		pItem = pThis->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		COleDataSource* pDataSource =
			pItem->OnGetClipboardData(TRUE, NULL, NULL);
		ASSERT(pDataSource != NULL);

		*ppIDataObj =
			(LPDATAOBJECT)pDataSource->GetInterface(&IID_IDataObject);
		ASSERT(*ppIDataObj != NULL);

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return sc;
*/
	return S_OK;
}

STDMETHODIMP CGeoDoc::DoVerb(LONG iVerb, LPMSG pMSG, LPOLECLIENTSITE pActiveSite, LONG lIndex, HWND hWndParent, LPCRECT pRectPos)
{
	D_OUTF2(1, "[%p]", this, " CGeoDoc::DoVerb( %ld )", iVerb);

WUnknown oRef (GetControllingUnknown());
HRESULT hr = S_OK;

	COM_TRY {
		switch (iVerb) {
		// open - maps to OnOpen
		case OLEIVERB_OPEN:
		case -OLEIVERB_OPEN-1:  // allows positive OLEIVERB_OPEN-1 in registry
			OnOpen();
			break;

		// primary, show, and unknown map to OnShow
		case OLEIVERB_PRIMARY:  // OLEIVERB_PRIMARY is 0 and "Edit" in registry
		case OLEIVERB_SHOW:
			OnShow();
			break;

		// hide maps to OnHide
		case OLEIVERB_HIDE:
		case -OLEIVERB_HIDE-1:  // allows positive OLEIVERB_HIDE-1 in registry
			OnHide();
			break;

		default:
			// negative verbs not understood should return E_NOTIMPL
			if (iVerb < 0)
			{
				hr = E_NOTIMPL;
				break;
			}

			// positive verb not processed --
			//  according to OLE spec, primary verb should be executed
			//  instead.
//			OnDoVerb(OLEIVERB_PRIMARY);
			OnShow();

			// also, OLEOBJ_S_INVALIDVERB should be returned.
			hr = OLEOBJ_S_INVALIDVERB;
		}

	} COM_CATCH;
	return hr;
}

void CGeoDoc::OnOpen()
{
	DEX_ShowAppWindow(SW_SHOW);		// Zunächst ganz simpel, nur damit etwas zu sehen ist!
}

void CGeoDoc::OnShow()
{
	DEX_ShowAppWindow(SW_SHOW);		// Zunächst ganz simpel, nur damit etwas zu sehen ist!

// send OnShowWindow notifications to the container
//	if (m_ClientSite != NULL && (bShow || m_bCntrVisible != bShow))
	if (m_ClientSite.IsValid())
	{
	// allow the container to shade the object appropriately
		m_ClientSite -> OnShowWindow(TRUE);
//		m_bCntrVisible = bShow;
	}
}

void CGeoDoc::OnHide()
{
	DEX_HideAppWindow();

	// send OnShowWindow notifications to the container
//	if (m_ClientSite != NULL && (bShow || m_bCntrVisible != bShow))
	if (m_ClientSite.IsValid())
	{
	// allow the container to shade the object appropriately
		m_ClientSite -> OnShowWindow(FALSE);
//		m_bCntrVisible = bShow;
	}
}

void CGeoDoc::OnDataChanged()
{
// Nachricht an Client: Es gibt frische Daten!
	D_OUTF(1, "[%p] CGeoDoc::OnDataChanged", this);
	if (m_DataAdviseHolder.IsValid())
		m_DataAdviseHolder -> SendOnDataChange(this, 0, 0);
}

STDMETHODIMP CGeoDoc::EnumVerbs(LPENUMOLEVERB *ppEnum)
{
	*ppEnum = NULL;
	COM_TRY {
	WOleObject Obj(this);
	CLSID clsid;

		THROW_FAILED_HRESULT(Obj -> GetUserClassID(&clsid));
		THROW_FAILED_HRESULT(OleRegEnumVerbs (clsid, ppEnum));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::Update(void)
{
	D_OUTF( 1, "[%p] CGeoDoc::Update (does nothing)", this);
/*
	COleServerItem* pItem;
	SCODE sc = S_OK;
	try
	{
		// delegate through item
		pItem = this->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);
		pItem->OnUpdateItems();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return sc;
*/

// tell the client site to save the object
	DEX_RePaintWait();		// evtl. Zeichnen beenden
	if (m_ClientSite.IsValid() && !::InSendMessage())
	{
		RETURN_FAILED_HRESULT(m_ClientSite -> SaveObject());
	}
	return S_OK;
}

STDMETHODIMP CGeoDoc::IsUpToDate(void)
{
	D_OUTF(1, "[%p] CGeoDoc::IsUpToDate (does nothing)", this);
/*
	COleServerItem* pItem;
	SCODE sc;
	try
	{
		// delegate through item
		pItem = this->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		sc = pItem->OnQueryUpdateItems() ? S_FALSE : S_OK;

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return sc;
*/
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetUserClassID(LPCLSID pClsID)
{
	COM_TRY {
	WPersistFile file (this);

		THROW_FAILED_HRESULT(file -> GetClassID(pClsID));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::GetUserType(DWORD dwForm, LPOLESTR *ppszType)
{
	*ppszType = NULL;

	COM_TRY {
	WOleObject Obj (this);
	CLSID clsid;

		THROW_FAILED_HRESULT(Obj -> GetUserClassID(&clsid));
		THROW_FAILED_HRESULT(OleRegGetUserType(clsid, dwForm, ppszType));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::SetExtent(DWORD dwAspect, LPSIZEL pszl)
{
	D_OUTF( 1, "[%p] CGeoDoc::SetExtent", this);

HRESULT hr = E_FAIL;

	COM_TRY {
		switch (dwAspect)	{
		case DVASPECT_CONTENT:
			m_SizeExtContent.cx = (int)pszl -> cx;
			m_SizeExtContent.cy = (int)pszl -> cy;
			// if (OnSetExtent((DVASPECT)dwAspect, m_SizeExtContent))
				hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::SetExtent (DVASPECT_CONTENT, %d,", m_SizeExtContent.cx, 
					 " %d)", m_SizeExtContent.cy);

			OnDataChanged();	// Wen der Client die Abmessungen ändert,
								// sollte er die Darstellung neu anfordern!!
			break;

		case DVASPECT_THUMBNAIL:
			m_SizeExtThumbnail.cx = (int)pszl -> cx;
			m_SizeExtThumbnail.cy = (int)pszl -> cy;
			// if ( OnSetExtent((DVASPECT)dwAspect, m_SizeExtThumbnail))
				hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::SetExtent (DVASPECT_THUMBNAIL, %d,", m_SizeExtThumbnail.cx, 
					 " %d)", m_SizeExtThumbnail.cy);
			break;

		case DVASPECT_ICON:
			m_SizeExtIcon.cx = (int)pszl -> cx;
			m_SizeExtIcon.cy = (int)pszl -> cy;
			// if ( OnSetExtent((DVASPECT)dwAspect, m_SizeExtIcon))
				hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::SetExtent (DVASPECT_ICON, %d,", m_SizeExtIcon.cx, 
					 " %d)", m_SizeExtIcon.cy);
			break;

		case DVASPECT_DOCPRINT:
			m_SizeExtPrint.cx = (int)pszl -> cx;
			m_SizeExtPrint.cy = (int)pszl -> cy;
			// if ( OnSetExtent((DVASPECT)dwAspect, m_SizeExtPrint))
				hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::SetExtent (DVASPECT_DOCPRINT, %d,", m_SizeExtPrint.cx, 
					 " %d)", m_SizeExtPrint.cy);
			break;
		}
	} COM_CATCH;
	return hr;
}

STDMETHODIMP CGeoDoc::GetExtent(DWORD dwAspect, LPSIZEL pszl)
{
	D_OUTF( 1, "[%p] CGeoDoc::GetExtent", this);

HRESULT hr = E_INVALIDARG;

	COM_TRY {
		switch (dwAspect) {
		case DVASPECT_CONTENT:
			// extents are always positive
			if (m_SizeExtContent.cy < 0)
				m_SizeExtContent.cy = -m_SizeExtContent.cy;
			pszl -> cx = m_SizeExtContent.cx;
			pszl -> cy = m_SizeExtContent.cy;
			hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::GetExtent (DVASPECT_CONTENT, %d,", m_SizeExtContent.cx, 
					 " %d)", m_SizeExtContent.cy);
			break;

		case DVASPECT_THUMBNAIL:
			// extents are always positive
			if (m_SizeExtThumbnail.cy < 0)	
				m_SizeExtThumbnail.cy = -m_SizeExtThumbnail.cy;
			pszl -> cx = m_SizeExtThumbnail.cx;
			pszl -> cy = m_SizeExtThumbnail.cy;
			hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::GetExtent (DVASPECT_THUMBNAIL, %d,", m_SizeExtThumbnail.cx, 
					 " %d)", m_SizeExtThumbnail.cy);
			break;

		case DVASPECT_ICON:
			// extents are always positive
			if (m_SizeExtIcon.cy < 0)	
				m_SizeExtIcon.cy = -m_SizeExtIcon.cy;
			pszl -> cx = m_SizeExtIcon.cx;
			pszl -> cy = m_SizeExtIcon.cy;
			hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::GetExtent (DVASPECT_ICON, %d,", m_SizeExtIcon.cx, 
					 " %d)", m_SizeExtIcon.cy);
			break;

		case DVASPECT_DOCPRINT:
			// extents are always positive
			if (m_SizeExtPrint.cy < 0)	
				m_SizeExtPrint.cy = -m_SizeExtPrint.cy;
			pszl -> cx = m_SizeExtPrint.cx;
			pszl -> cy = m_SizeExtPrint.cy;
			hr = S_OK;

			D_OUTF3(1, "[%p]", this,
					 " CGeoDoc::GetExtent (DVASPECT_DOCPRINT, %d,", m_SizeExtPrint.cx, 
					 " %d)", m_SizeExtPrint.cy);
			break;
		}

		if (m_dwLastAskedAspect != dwAspect || dwAspect == DVASPECT_CONTENT)
			OnDataChanged();

		m_dwLastAskedAspect = dwAspect;

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CGeoDoc::Advise(LPADVISESINK pAdvSink, LPDWORD pdwConn)
{
	D_OUTF(1, "[%p] CGeoDoc::Advise", this);

	*pdwConn = 0;
	if (!m_AdviseHolder && S_OK != ::CreateOleAdviseHolder(m_AdviseHolder.ppi()))
	{
		D_OUTF( 1, "[%p] CGeoDoc::Advise failed", this);
		return E_OUTOFMEMORY;
	}
	_ASSERTE(m_AdviseHolder.IsValid());

	D_OUTF( 1, "[%p] CGeoDoc::Advise !", this);
	return m_AdviseHolder -> Advise (pAdvSink, pdwConn);
}

STDMETHODIMP CGeoDoc::Unadvise(DWORD dwConn)
{
	D_OUTF(1, "[%p] CGeoDoc::Unadvise", this);
	
	if (!m_AdviseHolder) {
		D_OUTF( 1, "[%p] CGeoDoc::Unadvise failed", this);
		return E_FAIL;
	}

	_ASSERTE(m_AdviseHolder.IsValid());
	D_OUTF( 1, "[%p] CGeoDoc::Unadvise !", this);
	return m_AdviseHolder -> Unadvise(dwConn);
}

STDMETHODIMP CGeoDoc::EnumAdvise(LPENUMSTATDATA *ppEnum)
{
	*ppEnum = NULL;

	if (!m_AdviseHolder)
		return E_FAIL;

	_ASSERTE(m_AdviseHolder.IsValid());
	return m_AdviseHolder -> EnumAdvise(ppEnum);
}

STDMETHODIMP CGeoDoc::GetMiscStatus(DWORD dwAspect, LPDWORD pdwStatus)
{
	*pdwStatus = 0;
	COM_TRY {
	WOleObject Obj(this);
	CLSID clsid;

		THROW_FAILED_HRESULT(Obj -> GetUserClassID(&clsid));
		THROW_FAILED_HRESULT(OleRegGetMiscStatus(clsid, dwAspect, pdwStatus));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CGeoDoc::SetColorScheme(LPLOGPALETTE pLP)
{
	D_OUTF( 1, "[%p] CGeoDoc::SetColorScheme (does nothing)", this);
/*
	COleServerItem* pItem;
	SCODE sc = E_NOTIMPL;
	try
	{
		pItem = this->GetEmbeddedItem();
		ASSERT_VALID(pItem);
		ASSERT_KINDOF(COleServerItem, pItem);

		// delegate to embedded item
		if (pItem->OnSetColorScheme(lpLP))
			sc = S_OK;

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return sc;
*/
	return S_OK;
}

void CGeoDoc::RegisterStartPaint()
{
	m_bPaintStarted = TRUE;
}

void CGeoDoc::RegisterStopPaint()
{
	m_bPaintStarted = FALSE;
	if (m_bWait4StopPaint)
		DexNotificationProc ((WPARAM)DEX_OLEUPDATECLIENT, (LPARAM)0);
	m_bWait4StopPaint = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Kopien verschiedener Helperfunktionen (später besser unterbringen)!
HDC WINAPI _AfxOleCreateDC(DVTARGETDEVICE* ptd)
{
	USES_CONVERSION;

	// return screen DC for NULL target device
	if (ptd == NULL)
		return ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

LPDEVMODEOLE lpDevMode;
LPOLESTR lpszDriverName;
LPOLESTR lpszDeviceName;
LPOLESTR lpszPortName;

	if (ptd->tdExtDevmodeOffset == 0)
		lpDevMode = NULL;
	else
		lpDevMode  = (LPDEVMODEOLE) ((LPSTR)ptd + ptd->tdExtDevmodeOffset);

	lpszDriverName = (LPOLESTR)((BYTE*)ptd + ptd->tdDriverNameOffset);
	lpszDeviceName = (LPOLESTR)((BYTE*)ptd + ptd->tdDeviceNameOffset);
	lpszPortName   = (LPOLESTR)((BYTE*)ptd + ptd->tdPortNameOffset);

	return ::CreateDC(OLE2CT(lpszDriverName), OLE2CT(lpszDeviceName),
		OLE2CT(lpszPortName), DEVMODEOLE2T(lpDevMode));
}

//  FUNCTION   : ConvertEMFtoWMF
//
//  PARAMETERS : HENHMETAFILE hEMF - handle to enhanced metafile
//               LPSTR lpszFileName - filename of disked based metafile
//
//
//  PURPOSE    : Convert an enhanced metafile to an Windows metafile
//
//  MESSAGES   : none
//
//  RETURNS    : int
//
//  COMMENTS   : 
//  
//  HISTORY    : created 7/22/93 - denniscr
//BOOL ConvertEMFtoWMF (HDC hrefDC, HENHMETAFILE hEMF, LPSTR lpszFileName)
//{
//  void*        lpEMFBits;
//  UINT         uiSizeBuf;
//  HMETAFILE    hWMF;
//  BOOL         bRet = TRUE;
//  //
//  //get the size of the Windows metafile associated with hMF
//  //
//  if ((uiSizeBuf = GetWinMetaFileBits(hEMF, 0, NULL, MM_TEXT, hrefDC)))
//  {
//    //
//    //allocate enough memory to hold metafile bits
//    //
//    lpEMFBits = GlobalAllocPtr(GHND, uiSizeBuf);
//    //
//    //get the bits of the enhanced metafile associated with hEMF
//    //
//    if (lpEMFBits && GetWinMetaFileBits(hEMF, uiSizeBuf,(LPBYTE)lpEMFBits, 
//                                        MM_TEXT, hrefDC))
//
//    {
//      //
//      //copy the bits into a memory based Windows metafile
//      //
//      hWMF = SetMetaFileBitsEx(uiSizeBuf, (LPBYTE)lpEMFBits);
//      //
//      //copy the Windows metafile to a disk based Windows metafile
//      //
//      CopyMetaFile(hWMF, lpszFileName);
//      //
//      //done with the memory base enhanced metafile so get rid of it
//      //
//      DeleteMetaFile(hWMF);
//      //
//      //done with the actual memory used to store bits so nuke it
//      //
//      GlobalFreePtr(lpEMFBits);
//    }
//    else 
//      bRet = FALSE;
//  }
//  else
//    bRet = FALSE;
//  return (bRet);
//}

// Meine Anpassung! #AD000614
HMETAFILE ConvEMFtoWMF(HDC hrefDC, HENHMETAFILE hEMF)
{
void *lpEMFBits;
UINT uiSizeBuf;
HMETAFILE hWMF;

// get the size of the Windows metafile associated with hMF
	if ((uiSizeBuf = GetWinMetaFileBits(hEMF, 0, NULL, MM_TEXT, hrefDC))) {
    // allocate enough memory to hold metafile bits
	    lpEMFBits = GlobalAllocPtr(GHND, uiSizeBuf);

    // get the bits of the enhanced metafile associated with hEMF
	    if (lpEMFBits && GetWinMetaFileBits(hEMF, uiSizeBuf,(LPBYTE)lpEMFBits, MM_TEXT, hrefDC))
	    {
		// copy the bits into a memory based Windows metafile
			hWMF = SetMetaFileBitsEx(uiSizeBuf, (LPBYTE)lpEMFBits);

		// done with the actual memory used to store bits so nuke it
			GlobalFreePtr(lpEMFBits);
		} else 
			hWMF = NULL;
	}
	else
		hWMF = NULL;
	return hWMF;
}

#if defined(_DEBUG)
//  Function: FileExist
//
//  Summary:  Function to test for the existance of a file.
//
//  Args:     TCHAR* pszFileName
//              String pointer to file's path/name.
//
//  Returns:  BOOL.  TRUE if file exists; FALSE if not.
BOOL FileExist(const char* pszFileName)
{
BOOL bExist = FALSE;
HANDLE hFile;

	if (NULL != pszFileName) {
	// Use the preferred Win32 API call and not the older OpenFile.
		hFile = CreateFile(
		          pszFileName,
		          GENERIC_READ,
		          FILE_SHARE_READ | FILE_SHARE_WRITE,
		          NULL,
		          OPEN_EXISTING,
		          0,
		          0);

	    if (hFile != INVALID_HANDLE_VALUE) {
		// If the handle is valid then the file exists.
			CloseHandle(hFile);
			bExist = TRUE;
	    }
	}
	return bExist;
}

void SaveEMF(HENHMETAFILE hEMF)
{
	if (NULL == hEMF) 
		return;

CString	strFilename;
int n = 1;

	strFilename.Format("C:\\OLE%d.EMF",n);
	while (FileExist(strFilename))
	{
		strFilename.Format("C:\\OLE%d.EMF",++n);
	}

	D_OUTF(1," ==> GetMetafileData (%s)", (const char *)strFilename);
    CopyEnhMetaFile(hEMF, (const char*)strFilename);
}

void SaveWMF(HMETAFILE hMF)
{
	if (NULL == hMF) 
		return;

CString strFilename;
int n = 1;

	strFilename.Format("C:\\OLE%d.WMF",n);
	while (FileExist(strFilename))
	{
		strFilename.Format("C:\\OLE%d.WMF",++n);
	}

	D_OUTF(1," ==> GetMetafileData (%s)", (const char*)strFilename);
    CopyMetaFile(hMF, (const char*)strFilename);
}
#endif // defined(_DEBUG)
