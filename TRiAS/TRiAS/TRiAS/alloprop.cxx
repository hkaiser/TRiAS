// Alle ObjektPropertyExtensions aller Erweiterungen --------------------------
// File: ALLOPROP.CXX
//
// 24.02.2001 19:50:53
//		Objektnummer jetzt unter Objektinformationen (nicht mehr systeminterne 
//		Objekteigenschaften)

#include "triaspre.hxx"

#include "triasres.h"

#include <xtsnguid.h>
#include <ienumobj.hxx>
#include <propname.hxx>

#if !defined(WIN16)
#include <funcs03.h>
#include <istatus.h>

#include <oprpguid.h>
#include <ioprpini.hxx>
#include <triastlb.h>
#define _TriasTLB_H_
#include <dirisole.h>

#include "extmain3.hxx"
#endif // !WIN16

#include "objprop.hxx"
#include "eallprop.hxx"
#if _TRiAS_VER < 0x0400
#include "eallcprp.hxx"
#endif // _TRiAS_VER < 0x0400
#include "alloprop.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(ObjectProperty);		// WObjectProperty
#if _TRiAS_VER >= 0x0300
DefineSmartInterface(TRiASLockFeatureEx);		// WTRiASLockFeatureEx
DefineSmartInterface(InitInnerObject);			// WInitInnerObject
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(PropertyInfo);
DefineSmartInterface(PropertyInfo2);
DefineSmartInterface(InitObjPropMerkmal);
#endif // _TRiAS_VER >= 0x0300

#if defined(_USE_XML_GEOCOMPONENTS)
DefineSmartInterface(Dispatch);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(ConfigSequenceForObjectProperty);
#endif // defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
bool WriteMCodeToPbd (LONG lIdent, LONG lMCode, DWORD dwFlags, LPCSTR pcKText, LPCSTR pcLText = NULL);

// Konstruktor/Destruktor -----------------------------------------------------
CAllProperties::CAllProperties (ExtensionList *pEL)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
	m_pEL = pEL;
	m_pObjEnum = NULL;
#if _TRiAS_VER < 0x0400
	m_pClsEnum = NULL;
#endif // _TRiAS_VER < 0x0400

	m_lRefONr = -1L;
	m_lRefObjs = -1L;
}

CAllProperties::~CAllProperties (void)
{
	if (m_pObjEnum) m_pObjEnum -> Release();
#if _TRiAS_VER < 0x0400
	if (m_pClsEnum) m_pClsEnum -> Release();
#endif // _TRiAS_VER < 0x0400
	ResetMCodeProps();
}

CAllProperties *CAllProperties::CreateInstance (ExtensionList *pEL)
{
CAllProperties *pProps = new CAllProperties (pEL);

	if (NULL == pProps || !pProps -> FInit()) {
		DELETE_OBJ(pProps);
		return NULL;
	}
// kein AddRef !!
	return pProps;
}

bool CAllProperties::FInit (void)
{
// Enumeratoren anlegen
	m_pObjEnum = CEnumAllObjectProperties::CreateInstance();
	if (NULL == m_pObjEnum) return false;

#if _TRiAS_VER < 0x0400
	m_pClsEnum = CEnumAllClassProperties::CreateInstance();
	if (NULL == m_pClsEnum) return false;
#endif // _TRiAS_VER < 0x0400

	return true;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP_(HRESULT) CAllProperties::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return ((ITriasXtensionSite *)m_pEL) -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CAllProperties::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;		// debug purposes only
#endif // _DEBUG
	return ((ITriasXtensionSite *)m_pEL) -> AddRef();
}

STDMETHODIMP_(ULONG) CAllProperties::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;		// debug purposes only
#endif // _DEBUG
	return ((ITriasXtensionSite *)m_pEL) -> Release();
}

// *** IObjectProps specific functions *** ------------------------------------
STDMETHODIMP CAllProperties::EnumObjectProps (IEnumObjProps **ppEnumProp)
{
	if (NULL == ppEnumProp || NULL == m_pObjEnum) 
		return E_POINTER;

	return m_pObjEnum -> QueryInterface (IID_IEnumObjProps, (LPVOID *)ppEnumProp);
}

///////////////////////////////////////////////////////////////////////////////
// ACTUNG: folgende Regeln gelten für OnNewReferenceObject und OnNewReferenceObjects:
// OnNewReferenceObject liefert alle Objekteigenschaften für ein konkreten Objekt
// OnNewReferenceObjects liefert alle Objekteigenschaften für die Objekte einer
// Objektklasse (nicht mehr beides, selbst wenn die Objektnummer zusätzlich gegeben ist)

STDMETHODIMP CAllProperties::OnNewReferenceObject (INT_PTR lRefONr)
{
	if (-1L != lRefONr && m_lRefONr == lRefONr) 
		return S_OK;	// das Objekt ist immer noch das gleiche

// zuerst alle Objekteigenschaften, die zur zugehörigen Objektklasse gehören
INT_PTR lRefObjs = -1;
HRESULT hr = S_OK;

	if (0 != lRefONr && -1 != lRefONr) 
		lRefObjs = DEX_GetObjIdent(lRefONr);
	if (0 == lRefONr)
		lRefObjs = 0;	// Neueinlesen aller Objekteigenschaften erzwingen

	if (FAILED(hr = OnNewReferenceObjects(lRefObjs, lRefONr, false)))
		return hr;

// jetzt nur noch Objektspezifika dranhängen

// Enumerator für das BezugsObjekt neu füllen
	if (-1L != lRefONr) {		// nicht nur rücksetzen
	// interne Objekteigenschaften eintragen
		AddInternalObjProperties (lRefONr);

	// Objekteigenschaften der Erweiterungen abfragen und eintragen
	CTable t(*m_pEL);

		for (t.First(); t.Valid(); t.Next()) {
		ExtensionLock l(t);
		Extension *pExt = (Extension *)l;
  
			TX_ASSERT(NULL != pExt);

		HRESULT hr = CopyObjPropsToEnum ((COleExtension *)pExt, lRefONr);

			if (FAILED(hr)) {
				_ASSERTE(SUCCEEDED(hr));
				return hr;
			}
		}

		m_lRefONr = lRefONr;
		m_lRefObjs = lRefObjs;
	}
	else {
	// Objekteigenschaften der Erweiterungen rücksetzen
	CTable t(*m_pEL);

		for (t.First(); t.Valid(); t.Next()) {
		ExtensionLock l(t);
		Extension *pExt = (Extension *)l;
  
			TX_ASSERT(NULL != pExt);

		HRESULT hr = CopyObjPropsToEnum ((COleExtension *)pExt, -1);

			if (FAILED(hr)) {
				_ASSERTE(SUCCEEDED(hr));
				return hr;
			}
		}

		m_lRefONr = -1;
		m_lRefObjs = -1;
	}

	DEX_SetMustInitOPFs(TRUE);		// müssen ggf. neu eingelesen werden
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// liefert alle Objekteigenschaften von Objekten der gegebenen Objektklasse
STDMETHODIMP CAllProperties::OnNewReferenceObjects (INT_PTR lRefObjs, INT_PTR lRefObj)
{
	return OnNewReferenceObjects (lRefObjs, lRefObj, true);
}

HRESULT CAllProperties::OnNewReferenceObjects (
	INT_PTR lRefObjs, INT_PTR lRefObj, bool fExternal)
{
// Enumerator für das BezugsObjektklasse neu füllen
	if (-1L != lRefObjs && m_lRefObjs == lRefObjs && 0 == m_lRefONr) 
		return S_OK;

	if (-1L != lRefObjs) {	// nicht nur rücksetzen
	// Enumerator für das BezugsObjekt neu füllen
		RemoveAllObjPropertyFunctions();		// alle alten freigeben

	// interne Objekteigenschaften eintragen
		AddInternalObjPropertiesClass (lRefObjs);

	// Objekteigenschaften der Erweiterungen abfragen und eintragen
		if (fExternal) {
		CTable t(*m_pEL);

			for (t.First(); t.Valid(); t.Next()) {
			ExtensionLock l(t);
			Extension *pExt = (Extension *)l;
  
				TX_ASSERT(NULL != pExt);

			HRESULT hr = CopyObjPropsToEnum ((COleExtension *)pExt, lRefObj, lRefObjs);

				if (FAILED(hr)) {
					_ASSERTE(SUCCEEDED(hr));
					return hr;
				}
			}
		}

		m_lRefObjs = lRefObjs;	// Objekteigenschaften für alle Objekte einer Objektklasse
		m_lRefONr = 0;			// (keine Objektspezifik)
	}
	else {
	// Objekteigenschaften der Erweiterungen rückstzen
		if (fExternal) {
		CTable t(*m_pEL);

			for (t.First(); t.Valid(); t.Next()) {
			ExtensionLock l(t);
			Extension *pExt = (Extension *)l;
  
				TX_ASSERT(NULL != pExt);

			HRESULT hr = CopyObjPropsToEnum ((COleExtension *)pExt, -1, -1);

				if (FAILED(hr)) {
					_ASSERTE(SUCCEEDED(hr));
					return hr;
				}
			}
		}

		m_lRefObjs = -1;		// Rücksetzen
		m_lRefONr = -1;
	}
	DEX_SetMustInitOPFs(TRUE);		// müssen ggf. neu eingelesen werden
	return S_OK;
}

STDMETHODIMP CAllProperties::GetGroupInfo (LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags) 
{
	return E_NOTIMPL;	// placeholder only 
}

///////////////////////////////////////////////////////////////////////////////
// *** IObjectProps2 specific functions ***
STDMETHODIMP CAllProperties::CreateNewProp (
	LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, 
	REFIID riid, LPVOID *ppIObjProp)
{
HRESULT hr = CreateNewInternalProp (pcName, dwFlags, lONr, vOptData, riid, ppIObjProp);

	if (S_FALSE != hr) return hr;	// Fehler oder alles ok

CTable t(*m_pEL);
CPropertyName PropName (pcName);
string strGroup = PropName.GetGroup();
string strSubGroup = strGroup;
bool fHasSubGroup = false;

	if (PropName.hasSubGroup()) {
		strSubGroup += "\\";
		strSubGroup += PropName.GetSubGroup();
		fHasSubGroup = true;
	}

	for (t.First(); t.Valid(); t.Next()) {
	ExtensionLock l(t);
	Extension *pExt = (Extension *)l;

		TX_ASSERT(NULL != pExt);

	// nur für neue Erweiterungen
	IObjectProps *pIOPs = NULL;

		hr = ((COleExtension *)pExt) -> EnumObjPropFuncs (lONr, NULL, &pIOPs);
		if (S_OK != hr) continue;

	char cbBuffer[64] = { '\0' };
	DWORD dwFlags = 0;

		hr = pIOPs -> GetGroupInfo (cbBuffer, sizeof(cbBuffer), &dwFlags);
		pIOPs -> Release();

		if (SUCCEEDED(hr) && 
			( !strcmp (cbBuffer, strGroup.c_str()) || 
			  (fHasSubGroup && !strcmp(cbBuffer, strSubGroup.c_str()))
			) 
		   ) 
		{
		IObjectProps2 *pIGenOPs = NULL;

			hr = pIOPs -> QueryInterface (IID_IObjectProps2, (LPVOID *)&pIGenOPs);
			if (SUCCEEDED(hr)) {
			// an entsprechende Erweiterung weiterreichen
				hr = pIGenOPs -> CreateNewProp (PropName.GetName().c_str(), dwFlags, lONr, vOptData, riid, ppIObjProp);
				pIGenOPs -> Release();
			}
			return hr;		// abgearbeitet
		} 
	}
	
	return E_FAIL;		// Gruppe nicht gefunden
}

STDMETHODIMP CAllProperties::DeleteProp (LPCSTR pcName, LONG lONr)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// *** IObjectProps2 specific functions ***
STDMETHODIMP CAllProperties::CreateNewPropClass (
	LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData, 
	REFIID riid, LPVOID *ppIObjProp)
{
HRESULT hr = CreateNewInternalPropIdent (pcName, dwFlags, lIdent, vOptData, riid, ppIObjProp);

	if (S_FALSE != hr) return hr;	// Fehler oder alles ok

CTable t(*m_pEL);
CPropertyName PropName (pcName);
string strGroup = PropName.GetGroup();
string strSubGroup = strGroup;
bool fHasSubGroup = false;

	if (PropName.hasSubGroup()) {
		strSubGroup += "\\";
		strSubGroup += PropName.GetSubGroup();
		fHasSubGroup = true;
	}

	for (t.First(); t.Valid(); t.Next()) {
	ExtensionLock l(t);
	Extension *pExt = (Extension *)l;

		TX_ASSERT(NULL != pExt);

	// nur für neue Erweiterungen
	IObjectProps *pIOPs = NULL;

		hr = ((COleExtension *)pExt) -> EnumObjPropFuncsClass (lIdent, 0L, NULL, &pIOPs);
		if (S_OK != hr) continue;

	char cbBuffer[64] = { '\0' };
	DWORD dwFlags = 0;

		hr = pIOPs -> GetGroupInfo (cbBuffer, sizeof(cbBuffer), &dwFlags);
		pIOPs -> Release();

		if (SUCCEEDED(hr) && 
			( !strcmp (cbBuffer, strGroup.c_str()) || 
			  (fHasSubGroup && !strcmp(cbBuffer, strSubGroup.c_str()))
			) 
		   ) 
		{
		IObjectProps3 *pIGenOPs = NULL;

			hr = pIOPs -> QueryInterface (__uuidof(IObjectProps3), (LPVOID *)&pIGenOPs);
			if (SUCCEEDED(hr)) {
			// an entsprechende Erweiterung weiterreichen
				hr = pIGenOPs -> CreateNewPropClass (PropName.GetName().c_str(), dwFlags, lIdent, vOptData, riid, ppIObjProp);
				pIGenOPs -> Release();
			}
			return hr;		// abgearbeitet
		} 
	}
	return E_FAIL;		// Gruppe nicht gefunden
}

STDMETHODIMP CAllProperties::DeletePropClass (LPCSTR pcName, LONG lIdent)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// eine ObjektPropertyFunktion hinzufügen
bool CAllProperties::AddPropertyFunction (
	LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup, INT_PTR lRefObjs, bool fTestExisting)
{
	TX_ASSERT (NULL != pIObjProp);

WObjectProperty ObjProp (pIObjProp);

#if _TRiAS_VER >= 0x0300
	if (0 != lRefObjs) {
	WPropertyInfo2 Info;

		if (SUCCEEDED(pIObjProp -> QueryInterface(Info.ppi())) &&
			S_OK != Info -> EvaluatesForClass (lRefObjs))
		{
			return true;		// gehört nicht zu der Objektklasse
		}
	}

// Das folgende ist eigentlich nur ein Notanker für Objekteigenschaften, die
// ITRiASFeatureLock nicht unterstützen. Das Ganze führt jedoch i.A. zu heftigen
// Leaks, da die aggregierte Objekteigenschaft nichts von ihrem Glück weis und
// deshalb Interfacepointer herumschwirren, die nicht über den Delegator gewrappt 
// sind.
WTRiASLockFeatureEx Lock;

	if (FAILED(pIObjProp -> QueryInterface (Lock.ppi()))) {
	// wenn die Objekteigenschaft ITRiASLockFeatureEx nicht unterstützt, dann selbige
	// aggregieren und ein solches Interface hinzufügen
	WInitInnerObject FakeLock;

		if (SUCCEEDED(FakeLock.CreateInstance(CLSID_FakeTRiASLockFeature))) {
			FakeLock -> SetInnerObject (pIObjProp, IID_IObjectProperty, ObjProp.ppu());
			if (!ObjProp.IsValid())
				ObjProp = pIObjProp;
		}
	}
#endif // _TRiAS_VER >= 0x0300

	if (NULL == pcGroup) 
		return m_pObjEnum -> AddProp (ObjProp, FakeTRiASName(IDS_INTERNOPROPGROUP, g_cbTRiAS).c_str(), fTestExisting);

	return m_pObjEnum -> AddProp (ObjProp, pcGroup, fTestExisting);
}

///////////////////////////////////////////////////////////////////////////////
// Entfernen einer PropertyFunction
bool CAllProperties::RemovePropertyFunction (LPCSTR pcName)
{
	return m_pObjEnum -> DeleteProp(pcName);
}

// Freigeben aller OPFs -------------------------------------------------------
bool CAllProperties::RemoveAllObjPropertyFunctions (void)
{
	m_lRefONr = -1L;
	return m_pObjEnum -> EveryDelete();
}

#if _TRiAS_VER < 0x0400
bool CAllProperties::RemoveAllClsPropertyFunctions (void)
{
	return m_pClsEnum -> EveryDelete();
}
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// alle ObjektProperties einer Erweiterung zum Enumerator hinzufügen 
HRESULT CAllProperties::CopyObjPropsToEnum (
	COleExtension *pExt, INT_PTR lRefONr, INT_PTR lRefObjs)
{
WEnumObjProps EnumOPs;
WObjectProps IOPs;
HRESULT hr = E_NOTIMPL;

	if (0 != lRefObjs) 
		hr = pExt -> EnumObjPropFuncsClass (lRefObjs, lRefONr, EnumOPs.ppi(), IOPs.ppi());

	if (E_NOTIMPL == hr)	// nicht alle Erweiterungen können (brauchen) das
		hr = pExt -> EnumObjPropFuncs (lRefONr, EnumOPs.ppi(), IOPs.ppi());

	if (S_OK != hr) return hr;

char cbBuffer[64] = { '\0' };
DWORD dwFlags = 0;
bool fUseInfo = false;

	if (IOPs.IsValid()) {
		hr = IOPs -> GetGroupInfo (cbBuffer, sizeof(cbBuffer), &dwFlags);
		if (FAILED(hr)) {
			dwFlags = 0;
			cbBuffer[0] = '\0';
		} else
			fUseInfo = true;
	}

WObjectProperty IOP;

	for (EnumOPs -> Reset(); S_OK == EnumOPs -> Next(1, IOP.ppu(), NULL); /**/) {
	// alle Objekteigenschaften dieser Erweiterung hinzufügen
		TX_ASSERT(IOP.IsValid());
		AddPropertyFunction (IOP, fUseInfo ? cbBuffer : (pExt -> ExtName()).c_str(), lRefObjs);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Interne EigenschaftsFunktionen hinzufügen (pData == vector<HOBJECTS> * !)
BOOL CAllProperties::EnumMCodesForObjProp (long lMCode, DWORD dw, vector<HOBJECTS> *pIdents)
{
// Vielleicht gibt es diese Objekteigenschaft schon.
char cbBuffer[_MAX_PATH];
WObjectProperty Prop;

	TX_VERIFY(NULL != MCodeObjPropFuncName (cbBuffer, lMCode));

// hack für TRiASDB :-(, Objekteigenschaften mit "__" werden nicht hier eingebaut
	if (!strncmp (cbBuffer, g_cb2UnderScore, strlen(g_cb2UnderScore)))
		return TRUE;

bool fCreatedNew = false;
bool fHasToAdd = false;

	if (FAILED(m_pObjEnum -> FindByName (cbBuffer, Prop.ppi()))) {
	// noch nicht in dieser Menge von Objekteigenschaften drin
		if (FAILED(FindMCodeProp (cbBuffer, Prop.ppi()))) {
		// existiert noch nicht, muß also neu erzeugt werden
			if (FAILED(ObjPropCreateInstance (NULL, CLSID_ObjPropFeature, IID_IObjectProperty, Prop.ppv()))) 
				return FALSE;		// E_OUTOFMEMORY
			fCreatedNew = true;
		} 
		fHasToAdd = true;
	} 
	_ASSERTE(Prop.IsValid());

// neu bzw. nachinitialisieren
	_ASSERTE(NULL != pIdents);		// wenigstens eine Objektklasse muß hier ankommen

HOBJECTS hObjs = (*pIdents)[0];
WInitObjPropMerkmal Init;
HRESULT hr = Prop -> QueryInterface (Init.ppi());
bool fAddToPropCache = false;		// der Cache enthält lediglich MCode basierte Features

	_ASSERTE(INVALID_HOBJECTS != hObjs);
	if (SUCCEEDED(hr)) {
	// Zuordnung der Objektklasse zum MCode initialisieren
	HRESULT hr = Init -> InitWithObjectsEx (pIdents->size(), pIdents->begin(), 
		lMCode, (dw & MPReadOnlyFeatures) ? TRUE : FALSE);

		_ASSERTE(SUCCEEDED(hr));
		fAddToPropCache = (S_OK == hr) ? true : false;
	}

	if (fHasToAdd || fAddToPropCache) {
	// wenn mehr als ein Identifikator übergeben wurde, muß es eine TRiAS-DQ sein
		_ASSERTE(1 == pIdents->size() || DEX_GetTRiASDataSourceEx(DEX_GetObjectsProject(hObjs)));
		
	// UniqueIdent und OldUniqueIdent sind Objekttinformationen
	UINT uiResID = IDS_INTERNOPROPGROUP;
	INT_PTR lNativeMCode = DEX_MapHandleToMCode(lMCode);

		if (51200000L == lNativeMCode || 51300000L == lNativeMCode)
			uiResID = IDS_OBJECTINFOPROPGROUP;
		else if ((dw & MPSystemFeatures) || 99999000L == lNativeMCode || lMCode == DEX_GetTextFeature(hObjs)) 
		// SystemAttribute und der angezeigte Text eines Textobjektes ebenfalls
			uiResID = IDS_SYSTEMPROPGROUP;

	CPropertyName PropName(cbBuffer);
	ResString res (uiResID, 64);
	char cbGroup[_MAX_PATH];

		wsprintf (cbGroup, res, g_cbTRiAS);
		PropName.SetGroup(cbGroup);

		if (fHasToAdd) {
		// #HK021213: wenn mehr als ein Ident im Feld ist, dann gehören diese
		// alle zu einer (TRiAS-)Datenquelle und der MCode kommt auch von dort, 
		// der 'EvaluatesForClass' Test, der in der Funktion 'AddPropertyFunction'
		// an der Bedingung hObjs != NULL hängt kann daher entfallen
#if defined(_DEBUG)
			if (pIdents->size() > 1) {
			vector<HOBJECTS>::const_iterator cit = pIdents->begin();
			vector<HOBJECTS>::const_iterator end = pIdents->end();
			HPROJECT hPrMCode = DEX_GetFeatureProject(lMCode);

				for (/**/; cit != end; ++cit) {
					_ASSERTE(hPrMCode == DEX_GetObjectsProject(*cit));
				}
			}
#endif // defined(_DEBUG)

			AddPropertyFunction (Prop, cbGroup, pIdents->size() > 1 ? 0 : hObjs);	// zur aktuellen Liste hinzufügen

		// zum Cache hinzufügen (beim Neuerzeugen immer)
			m_PropsCache.AddProperty(hObjs, PropName, Prop);
		}
		else if (fAddToPropCache) {
		// zum Cache hinzufügen (nur wenn gefordert)
			m_PropsCache.AddProperty(hObjs, PropName, Prop);
		}
	}

// zu den Cache's hinzufügen
	if (fCreatedNew) 
		AddMCodeProp(cbBuffer, Prop);			// zur globalen MCodeListe hinzufügen
	
	return TRUE;
}

bool CAllProperties::AddInternalObjProperties (INT_PTR lRefONr)
{
	return true;	// derzeit hat TRiAS keine objektspezifischen Objekteigenschaften
}

bool CAllProperties::AddInternalObjPropertiesClass (INT_PTR lRefObjs)
{
// allgemeine Props werden hier lokal gecached
	if (FAILED(AddGeneralObjProperties(lRefObjs)))
		return false;

// nachsehen, ob die Menge der Objekteigenschaften schon bekannt ist
	if (0 != lRefObjs) {
	CPropsMapEx *pObjProps = NULL;

		if (S_OK == m_PropsCache.FindProps(lRefObjs, &pObjProps)) {
		// alle Objekteigenschaften hier dazufügen, nicht mehr gegen 
		// Objektklasse testen (3. Parameter == 0)
			CPropsMapEx::iterator end = pObjProps -> end();
			for (CPropsMapEx::iterator it = pObjProps -> begin(); it != end; ++it) {
				AddPropertyFunction((*it).second, (*it).first.GetGroup().c_str(), 
					0/*lRefObjs*/, true);
			}
			return true;	// alles fertig
		}
	}

// hier der Objektklasse auf die Sprünge verhelfen (speichert gefundene OE's im Cache)
CEnumThunk Thunk(this);
BOOL fResult = FALSE;

	if (0L == lRefObjs) {
	// alle ObjektMerkmale als Objekteigenschaften generieren
	ENUMNOKEYEX ENK;
	ErrInstall EI (WC_NOMERKMAL);

		ENK.eFcn = (ENUMNOKEYEXPROC)Thunk.GetThunk();
		ENK.ePtr = NULL;		// alle Objekteigenschaften
		ENK.eData = DWORD('a')|MPSystemFeatures|MPPbdOnly|MPListAllClasses;

		fResult = DEX_EnumMCodesEx (ENK);
	} 
	else {
	// existierende Objektmerkmale dieser Objektklasse verwenden
	ENUMLONGKEYEX ELK;
	ErrInstall EI (WC_NOMERKMAL);
	vector<HOBJECTS> Idents(1);

		Idents[0] = lRefObjs;
		ELK.eFcn = (ENUMLONGKEYEXPROC)Thunk.GetThunk();
		ELK.ePtr = &Idents;
		ELK.eKey = lRefObjs;
		ELK.eData = DWORD('a')|MPSystemFeatures|MPPbdOnly;

		fResult = DEX_EnumObjektMerkmaleClassEx(ELK);
	}
	return fResult;
}

bool CAllProperties::AddGeneralObjProperties(INT_PTR lRefObjs)
{
	if (m_GenProps.size() > 0) {
	// nicht das erste mal, also direkt registrieren
		for (CGenProps::iterator it = m_GenProps.begin(); it != m_GenProps.end(); ++it)
			AddPropertyFunction((*it).second, (*it).first.c_str(), 0/*lRefObjs*/, false);
		return true;
	}

	COM_TRY {
	// alles neu instantiieren
	WObjectProperty Prop;
	HRESULT hr = E_FAIL;
	// systeminterne Objekteigenschaften
	string strName (FakeTRiASName(IDS_SYSTEMPROPGROUP, g_cbTRiAS));

		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropIdent, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// Identifikator (systemintern)
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

	// Objektinformation
		strName = FakeTRiASName(IDS_OBJECTINFOPROPGROUP, g_cbTRiAS);
		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropONr, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// ObjektNummer (systemintern)
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropGUID, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// ObjektGUID (Objektinformation)
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

#if _TRiAS_VER >= 0x0300
		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropDataSource, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// Datenquelle
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropDataSourceDesc, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// Datenquellenbeschreibung
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;
#endif // _TRiAS_VER >= 0x0300

		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjTypLong, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 	// ObjektTyp
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

#if _TRiAS_VER < 0x0300
		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjTypShort, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, NULL, lRefObjs); 	// ObjektTyp (Kurz)
		} else
			return false;
#endif // _TRiAS_VER < 0x0300

	// zu den Beschreibungsdaten
		strName = FakeTRiASName(IDS_DESCRIPTIONPROPGROUP, g_cbTRiAS);
		hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjClassCode, IID_IObjectProperty, Prop.ppv());
		if (SUCCEEDED(hr)) {
			AddPropertyFunction (Prop, strName.c_str(), lRefObjs);				// ObjektKlassenSchlüssel
			m_GenProps.push_back(CGenProps::value_type(strName, Prop));
		} else
			return false;

	// Eingabefelder als Objekteigenschaften
		strName = FakeTRiASName (IDS_OBJPROPINTERACTIVE, g_cbTRiAS);
		for (int i = 1; i <= 4; i++) {
			hr = ObjPropCreateInstance (NULL, CLSID_ObjPropQueryField, IID_IObjectProperty, Prop.ppv());
			if (SUCCEEDED(hr)) {
			IInitObjPropQueryField *pIInit = NULL;

				hr = Prop -> QueryInterface (IID_IInitObjPropQueryField, (LPVOID *)&pIInit);
				if (SUCCEEDED(hr)) {
					pIInit -> Init (__hWndM, i);
					pIInit -> Release();

					AddPropertyFunction (Prop, strName.c_str(), lRefObjs); 
					m_GenProps.push_back(CGenProps::value_type(strName, Prop));
				}
			} else
				break;
		}

#if defined(_USE_XML_GEOCOMPONENTS_OBJECTPROPS)
	// Xml-Objekteigenschaften
		LoadXMLObjectProperties(lRefObjs);
#endif // defined(_USE_XML_GEOCOMPONENTS_OBJECTPROPS)

	} COM_CATCH_RETURN(false);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// neu erzeugen einer Objekteigenschaft
HRESULT CAllProperties::CreateNewInternalProp (
	LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData,
	REFIID riid, LPVOID *ppIObjProp)
{
	TX_ASSERT(0 != lONr && -1 != lONr);		// Objekt muß gegeben sein

INT_PTR lIdent = DEX_GetObjIdent(lONr);

	return CreateNewInternalPropIdent (pcName, dwFlags, lIdent, vOptData, riid, ppIObjProp);
}

HRESULT CAllProperties::CreateNewInternalPropIdent (
	LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData,
	REFIID riid, LPVOID *ppIObjProp)
{
// jetzt neu erzeugen, da noch nicht vorhanden
CPropertyName PropName (pcName);
CComVariant vData;
LONG lMCode = 0L;
LPCSTR pcOPName = PropName.GetName().c_str();

	if (FAILED(vData.ChangeType (VT_I4, &vOptData))) {
	// MCode der richtigen Datenquelle wiederfinden
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);	// #HK030111

		_ASSERTE(HACTCONNECTION != hPr);	 
		lMCode = DEX_GetMCodeFromFeatureNameEx(hPr, pcOPName);
	}
	else {
	// MCode ist gegeben, dieser muß aus der Datenquelle des Idents kommen
		lMCode = V_I4(&vData);
		_ASSERTE(DEX_GetObjectsProject(lIdent) == DEX_GetFeatureProject(lMCode));
	}

	if (0L == lMCode) {
		lMCode = (dwFlags & PROPCAPS_RESTRICTED) ? 
					DEX_GetUniqueMCode() :
					DEX_GetUniqueSysMCode();
	}

// evtl. einer bestimmten Gattung zuordnen
//vector<HOBJECTS> Idents(1);
//
//	Idents[0] = lIdent;
	if (PropName.hasGroup()) {
	ResString resIntern (IDS_INTERNOPROPGROUP, 64);
	ResString resSystem (IDS_SYSTEMPROPGROUP, 64);
	string const &rStr = PropName.GetGroup();

	// Objekteigenschaft finden/erzeugen
	DWORD dwData = DWORD('a');
	DWORD dwPbdFlags = DWORD('a');

		if (!(dwFlags & PROPCAPS_NOTREADONLY)) {
			dwData |= MPReadOnlyFeatures;
			dwPbdFlags |= PBDMERKMAL_READONLY;
		}
		
	// Objekteigenschaft in Pbd nachtragen
		if (rStr == resIntern.Addr()) {
			if (!WriteMCodeToPbd (lIdent, lMCode, dwPbdFlags, pcOPName)) 
				return E_FAIL;

//			if (!EnumMCodesForObjProp (lMCode, dwData, &Idents))
//				return E_FAIL;
		}
		else if (rStr == resSystem.Addr()) {
			if (!WriteMCodeToPbd (lIdent, lMCode, dwPbdFlags|PBDMERKMAL_SYSTEMFLAG, pcOPName)) 
				return E_FAIL;
//			if (!EnumMCodesForObjProp (lMCode, dwData|MPSystemFeatures, &Idents))
//				return E_FAIL;
		} 
		else
			return S_FALSE;		// nicht für uns
	} 
	else {
	// als normale ObjektEigenschaft erzeugen
	// Objekteigenschaft finden/erzeugen
	DWORD dwData = DWORD('a');
	DWORD dwPbdFlags = DWORD('a');

		if (dwFlags & PROPCAPS_RESTRICTED) {
			dwData |= MPSystemFeatures;
			dwPbdFlags |= PBDMERKMAL_SYSTEMFLAG;
		}
		if (!(dwFlags & PROPCAPS_NOTREADONLY)) {
			dwData |= MPReadOnlyFeatures;
			dwPbdFlags |= PBDMERKMAL_READONLY;
		}

	// Objekteigenschaft in Pbd nachtragen
		if (!WriteMCodeToPbd (lIdent, lMCode, dwPbdFlags, pcOPName)) 
			return E_FAIL;
//		if (!EnumMCodesForObjProp (lMCode, dwData, &Idents))
//			return E_FAIL;
	}

// Objekteigenschaften neu einlesen (wurden in DEXN_FeatureSetModified freigegeben)
	m_lRefObjs = 0;
	RETURN_FAILED_HRESULT(OnNewReferenceObjects (INVALID_HOBJECTS, INVALID_HOBJECT, true));

// jetzt OProp wiederfinden und liefern
WObjectProperty OProp;
HRESULT hr = m_pObjEnum -> FindByName (pcName, OProp.ppi());

	if (FAILED(hr)) return hr;
	
	return OProp -> QueryInterface (riid, ppIObjProp);
}

bool WriteMCodeToPbd (LONG lIdent, LONG lMCode, DWORD dwFlags, LPCSTR pcKText, LPCSTR pcLText)
{
PBDMERKMALEX TM;
bool iResult = true;
int iLen = strlen (pcKText);
int iLLen = 0;

	if (NULL == pcLText) {
		pcLText = pcKText;
		iLLen = iLen;
	} else
		iLLen = strlen(pcLText);

	INITSTRUCT(TM, PBDMERKMALEX);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.pbdKText = (char *)pcKText;
	TM.pbdLText = (char *)pcLText;
	TM.pbdKTextLen = iLen;
	TM.pbdLTextLen = iLLen;
	TM.ipbdMTyp = short(dwFlags);
	TM.ipbdMLen = 64;
	TM.lIdent = lIdent;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}
	return iResult;
}
	
///////////////////////////////////////////////////////////////////////////////
// Liste der existierenden MCodeprops verwalten
HRESULT CAllProperties::FindMCodeProp(LPCSTR pcName, IObjectProperty **ppIOP)
{
CMCodeProps::iterator it = m_MCodeProps.find(pcName);

	if (it == m_MCodeProps.end())
		return E_FAIL;

	if (NULL != ppIOP) {
	WObjectProperty OP ((*it).second);

		*ppIOP = OP.detach();
	}
	return S_OK;
}

HRESULT CAllProperties::AddMCodeProp(LPCSTR pcName, IObjectProperty *pIOP)
{
CMCodeProps::iterator it = m_MCodeProps.find(pcName);

	if (it != m_MCodeProps.end())
		return E_UNEXPECTED;		// existiert bereits

	ATLTRY(m_MCodeProps.insert(CMCodeProps::value_type(pcName, pIOP)));
	return S_OK;
}

HRESULT CAllProperties::RemoveMCodeProp(LPCSTR pcName)
{
CMCodeProps::iterator it = m_MCodeProps.find(pcName);

	if (it == m_MCodeProps.end())
		return E_UNEXPECTED;		// existiert nicht

	m_MCodeProps.erase(it);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// obsolete functionality
#if _TRiAS_VER >= 0x200 && _TRiAS_VER < 0x0400
bool AddClsProperty (IClassProperty *pIClsProp, LPCSTR pcGroup, DWORD dwData)
{
	return reinterpret_cast<CAllProperties *>(dwData) -> AddPropertyFunction (pIClsProp, pcGroup);
}
#endif _TRiAS_VER >= 0x200 && _TRiAS_VER < 0x0400

bool CAllProperties::AddInternalClsProperties (void)
{
#if _TRiAS_VER >= 0x200 && _TRiAS_VER < 0x0300
// alle bisherigen ClsProps sind in TRiAS03 implementiert
	return RegisterPropertyActions (AddClsProperty, reinterpret_cast<DWORD>(this));
#else
	return true;		// keine definiert
#endif // _TRiAS_VER >= 0x200 && _TRiAS_VER < 0x0300
}

#if _TRiAS_VER < 0x0400
HRESULT CAllProperties::CopyClsPropsToEnum (COleExtension *pExt, IEnumLONG *pIEnum)
{
LPENUMCLASSPROPS pIEnumOPs = NULL;
LPCLASSPROPERTY pIOP = NULL;
LPOBJECTPROPS pIOPs = NULL;
HRESULT hr = pExt -> EnumClsPropFuncs (pIEnum, &pIEnumOPs, &pIOPs);

	if (S_OK != GetScode(hr)) 
		return hr;

char cbBuffer[64] = { '\0' };
DWORD dwFlags = 0;
bool fUseInfo = false;

	if (NULL != pIOPs) {
		hr = pIOPs -> GetGroupInfo (cbBuffer, sizeof(cbBuffer), &dwFlags);
		if (FAILED(hr)) {
			dwFlags = 0;
			cbBuffer[0] = '\0';
		} else
			fUseInfo = true;
		pIOPs -> Release();
	}

	for (pIEnumOPs -> Reset(); 
	     S_OK == pIEnumOPs -> Next(1, (LPUNKNOWN *)&pIOP, NULL); )
	{
		TX_ASSERT(NULL != pIOP);
		AddPropertyFunction (pIOP, fUseInfo ? cbBuffer : (pExt -> ExtName()).c_str());
		pIOP -> Release();
	}
	pIEnumOPs -> Release();
	return NOERROR;
}
#endif // _TRiAS_VER < 0x0400

STDMETHODIMP CAllProperties::EnumClassProps (IEnumClassProps **ppEnumProp)
{
#if _TRiAS_VER < 0x0400
	if (NULL == ppEnumProp || NULL == m_pClsEnum) 
		return ResultFromScode (E_FAIL);

	return m_pClsEnum -> QueryInterface (IID_IEnumClassProps, (LPVOID *)ppEnumProp);
#else
	return E_NOTIMPL;
#endif // _TRiAS_VER < 0x0400
}

STDMETHODIMP CAllProperties::OnNewReferenceClass (IEnumLONG *pEnumObjs)
{
#if _TRiAS_VER < 0x0400
// Enumerator für das BezugsObjekt neu füllen
	RemoveAllClsPropertyFunctions();		// alle alten freigeben

// interne ObjektKlassenEigenschaften eintragen
	AddInternalClsProperties();

// Objekteigenschaften der Erweiterungen abfragen und eintragen
CTable t(*m_pEL);
HRESULT hr = NOERROR;

	for (t.First(); t.Valid(); t.Next()) {
	ExtensionLock l(t);
	Extension *pExt = (Extension *)l;

		TX_ASSERT(NULL != pExt);
//		if (Extension::DirectExt == pExt -> isA())	continue;

	// nur für neue Erweiterungen
		hr = CopyClsPropsToEnum ((COleExtension *)pExt, pEnumObjs);
		if (FAILED(hr)) return hr;
	}
#endif // _TRiAS_VER < 0x0400
	return S_OK;
}

#if _TRiAS_VER < 0x0400
bool CAllProperties::AddPropertyFunction (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup)
{
	TX_ASSERT (NULL != pIClsProp);

	if (NULL == pcGroup) 
		return m_pClsEnum -> AddProp (pIClsProp, FakeTRiASName(IDS_INTERNOPROPGROUP, g_cbTRiAS).c_str());

	return m_pClsEnum -> AddProp (pIClsProp, pcGroup);
}
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// XML basierte Objekteigenschaften
#if defined(_USE_XML_GEOCOMPONENTS_OBJECTPROPS)
HRESULT CAllProperties::LoadXMLObjectProperties(INT_PTR lRefObjs)
{
	COM_TRY {
	// den XML-Katalog aller bekannten Objekteigenschaften laden
	WDispatch DocDisp;
	__Interface<TRiASCFG::ILoadXmlService> XmlService(TRiASCFG::CLSID_LoadXmlService);

		THROW_FAILED_HRESULT(XmlService -> LoadXmlFromResource(CComBSTR("ObjectPropertyCatalog.xml"), DocDisp.ppi()));

	// Root des Documentes validieren
	__Interface<xml::IXMLDOMDocument> Doc (DocDisp);
	__Interface<xml::IXMLDOMElement> Root;

		THROW_FAILED_HRESULT(Doc -> get_documentElement(Root.ppi()));

	// es muß ein GeoKomponentenKatalog sein
	__Interface<xml::IXMLDOMNodeList> Nodes;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Root -> raw_getElementsByTagName(CComBSTR(g_cbCatalogFolder), Nodes.ppi()));
		THROW_FAILED_HRESULT(Nodes -> get_length(&lCnt));

		for (long lItem = 0; lItem < lCnt; ++lItem) {
		__Interface<xml::IXMLDOMNode> Node;

			THROW_FAILED_HRESULT(Nodes -> get_item(lItem, Node.ppi()));
			LoadXMLObjectPropertiesFromThisGroup (Node, lRefObjs);		// Fehler nicht fatal
		}

	// alles, was nicht mehr gebraucht wird, wieder loslassen
		CoFreeUnusedLibraries();

	} COM_CATCH;
	return S_OK;
}

HRESULT CAllProperties::LoadXMLObjectPropertiesFromThisGroup(xml::IXMLDOMNode *pINode, INT_PTR lRefObjs)
{
	_ASSERTE(NULL != pINode);

	USES_CONVERSION;
	COM_TRY {
	// Description ist der Name der Gruppe der Objekteigenschaften
	CComBSTR bstrDesc;

		if (S_OK != xml::GetAttribute(pINode, g_cbInitDesc, &bstrDesc))
			return E_UNEXPECTED;

	// jetzt alle bekannten Einträge dieser Gruppe analysieren
	LPCSTR pcGroup = OLE2A(bstrDesc);

	__Interface<xml::IXMLDOMElement> Elem (pINode);
	__Interface<xml::IXMLDOMNodeList> Nodes;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Elem -> raw_getElementsByTagName(CComBSTR(g_cbCatalogNode), Nodes.ppi()));
		THROW_FAILED_HRESULT(Nodes -> get_length(&lCnt));

		for (long lItem = 0; lItem < lCnt; ++lItem) {
		// jeder CatalogNode verkörpert eine Objekteigenschaft
		__Interface<xml::IXMLDOMNode> Node;
		CComBSTR bstrNodeName;

			THROW_FAILED_HRESULT(Nodes -> get_item(lItem, Node.ppi()));
			if (S_OK != xml::GetAttribute(Node, g_cbInitName, &bstrNodeName))
			{
				continue;
			}

		// jetzt diese Objekteigenschaft laden
		WObjectProperty ObjProp;

			if (SUCCEEDED(LoadXMLObjectProperty (bstrNodeName, ObjProp.ppi()))) {
				AddPropertyFunction (ObjProp, pcGroup, lRefObjs);
				m_GenProps.push_back(CGenProps::value_type(pcGroup, ObjProp));
			}
		}
	
	} COM_CATCH;
	return S_OK;
}

// eine Objekteigenschaft laden
HRESULT CAllProperties::LoadXMLObjectProperty(BSTR bstrRsc, IObjectProperty **ppIObjProp)
{
	if (NULL == ppIObjProp)
		return E_POINTER;
	*ppIObjProp = NULL;

	USES_CONVERSION;
	COM_TRY {
	// XML Dokument laden
	WDispatch DocDisp;
	__Interface<TRiASCFG::ILoadXmlService> XmlService(TRiASCFG::CLSID_LoadXmlService);

		THROW_FAILED_HRESULT(XmlService -> LoadXmlFromResource(bstrRsc, DocDisp.ppi()));
		
	// Root des Documentes validieren
	__Interface<xml::IXMLDOMDocument> Doc (DocDisp);
	__Interface<xml::IXMLDOMElement> Root;

		THROW_FAILED_HRESULT(Doc -> get_documentElement(Root.ppi()));

	// Daten einlesen
	CCalClsId calPropSeqData;
	HRESULT hr = calPropSeqData.InitDataFromXml (Root);

		if (FAILED(hr)) {
			if (E_ABORT == hr)
				return hr;
			THROW_FAILED_HRESULT(hr);
		}

	// das hier muß eine Objekteigenschaft sein
		_ASSERTE(SEQTYPE_Property == calPropSeqData.GetSequenceType());

	// Objekteigenschaft erzeugen
	WObjectProperty ObjProp;
	
		hr = ObjProp.CreateInstance(calPropSeqData.GetSeqGuid());
		if (FAILED(hr)) {
			if (!calPropSeqData.GetMayFail()) {
				THROW_FAILED_HRESULT(hr);		// darf eigentlich nicht fehlschlagen
			} else {
				return hr;
			}
		}

	// Rücksetzen/Initialisieren der Objekteigenschaft
		THROW_FAILED_HRESULT(WPersistStreamInit(ObjProp) -> InitNew());
		if (NULL != calPropSeqData.GetName() && 
			::SysStringLen(calPropSeqData.GetName()) > 0) {
		DWORD dwFlags = 0;

			if (!calPropSeqData.GetFlags(&dwFlags)) {
			// bisherige Flags beibehalten
				THROW_FAILED_HRESULT(ObjProp -> GetPropInfo(NULL, 0, &dwFlags));
			}

		// Namen/Flags der Objekteigenschaft setzen
			THROW_FAILED_HRESULT(WPropertyInfo(ObjProp) -> SetPropInfo(OLE2A(calPropSeqData.GetName()), dwFlags));
		}
		
	// ggf. Beschreibungsinfo setzen
		if (NULL != calPropSeqData.GetDesc() &&
			::SysStringLen(calPropSeqData.GetDesc()) > 0) 
		{
			THROW_FAILED_HRESULT(WPropertyInfo(ObjProp) -> SetHelpInfo(OLE2A(calPropSeqData.GetDesc()), NULL, 0));
		}

	// hinzufügen der einzelnen Aktionen
	WConfigSequenceForObjectProperty Config (ObjProp);

		THROW_FAILED_HRESULT(Config -> AddActionsByCLSID (calPropSeqData.GetInitInfo()));
		*ppIObjProp = ObjProp.detach();

	} COM_CATCH;
	return S_OK;
}
#endif // defined(_USE_XML_GEOCOMPONENTS_OBJECTPROPS)
