// Alle ObjektPropertyExtensions aller Erweiterungen --------------------------
// File: ALLOPROP.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtsnguid.h>
#include <ienumobj.hxx>
#include <propname.hxx>

#if defined(WIN32)
#include <funcs03.h>
#include <istatus.h>

#include <oprpguid.h>
#include <ioprpini.hxx>
#include <triastlb.h>
#define _TriasTLB_H_
#include <dirisole.h>

#include "extmain3.hxx"
#endif // WIN32

#include "objprop.hxx"
#include "eallprop.hxx"
#include "eallcprp.hxx"
#include "alloprop.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
//DefineSmartInterface(ObjectProperty);		// WObjectProperty

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
bool WriteMCodeToPbd (LONG lMCode, DWORD dwFlags, LPCSTR pcKText, LPCSTR pcLText = NULL);

// Konstruktor/Destruktor -----------------------------------------------------
CAllProperties :: CAllProperties (ExtensionList *pEL)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
	m_pEL = pEL;
	m_pObjEnum = NULL;
	m_pClsEnum = NULL;

	m_lRefONr = -1L;
}

CAllProperties :: ~CAllProperties (void)
{
	if (m_pObjEnum) m_pObjEnum -> Release();
	if (m_pClsEnum) m_pClsEnum -> Release();
}

CAllProperties *CAllProperties :: CreateInstance (ExtensionList *pEL)
{
CAllProperties *pProps = new CAllProperties (pEL);

	if (NULL == pProps || !pProps -> FInit()) {
		DELETE(pProps);
		return NULL;
	}
// kein AddRef !!

return pProps;
}

bool CAllProperties :: FInit (void)
{
// Enumeratoren anlegen
	m_pObjEnum = CEnumAllObjectProperties :: CreateInstance();
	if (NULL == m_pObjEnum) return false;

	m_pClsEnum = CEnumAllClassProperties :: CreateInstance();
	if (NULL == m_pClsEnum) return false;

return true;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP_(HRESULT) CAllProperties :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pEL -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CAllProperties :: AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;		// debug purposes only
#endif // _DEBUG
	return m_pEL -> AddRef();
}

STDMETHODIMP_(ULONG) CAllProperties :: Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;		// debug purposes only
#endif // _DEBUG
	return m_pEL -> Release();
}

// *** IObjectProps specific functions *** ------------------------------------
STDMETHODIMP CAllProperties :: EnumObjectProps (IEnumObjProps **ppEnumProp)
{
	if (NULL == ppEnumProp || NULL == m_pObjEnum) 
		return ResultFromScode (E_FAIL);

return m_pObjEnum -> QueryInterface (IID_IEnumObjProps, (LPVOID *)ppEnumProp);
}

STDMETHODIMP CAllProperties :: EnumClassProps (IEnumClassProps **ppEnumProp)
{
	if (NULL == ppEnumProp || NULL == m_pClsEnum) 
		return ResultFromScode (E_FAIL);

return m_pClsEnum -> QueryInterface (IID_IEnumClassProps, (LPVOID *)ppEnumProp);
}

STDMETHODIMP CAllProperties :: OnNewReferenceObject (LONG lRefONr)
{
	if (-1L != lRefONr && m_lRefONr == lRefONr) 
		return S_OK;

// Enumerator für das BezugsObjekt neu füllen
	RemoveAllObjPropertyFunctions();		// alle alten freigeben

	if (-1L != lRefONr) {	// nicht nur rücksetzen
	// interne Objekteigenschaften eintragen
		AddInternalObjProperties (lRefONr);

	// Objekteigenschaften der Erweiterungen abfragen und eintragen
	CTable t(*m_pEL);
	HRESULT hr = NOERROR;

		for (t.First(); t.Valid(); t.Next()) {
		ExtensionLock l(t);
		Extension *pExt = (Extension *)l;

			TX_ASSERT(NULL != pExt);
	//		if (Extension::DirectExt == pExt -> isA())	continue;

		// nur für neue Erweiterungen
			hr = CopyObjPropsToEnum ((COleExtension *)pExt, lRefONr);
			if (FAILED(hr)) return hr;
		}
	}
			
	m_lRefONr = lRefONr;
	DEX_SetMustInitOPFs(TRUE);		// müssen ggf. neu eingelesen werden
	return S_OK;
}

STDMETHODIMP CAllProperties :: OnNewReferenceClass (IEnumLONG *pEnumObjs)
{
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

return NOERROR;
}

STDMETHODIMP CAllProperties :: GetGroupInfo (
		LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags) 
{
	return ResultFromScode (E_NOTIMPL);	// placeholder only 
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

// eine ObjektPropertyFunktion hinzufügen -------------------------------------
bool CAllProperties :: AddPropertyFunction (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup)
{
	TX_ASSERT (NULL != pIObjProp);

	if (NULL == pcGroup) 
		return m_pObjEnum -> AddProp (pIObjProp, FakeTRiASName(IDS_INTERNOPROPGROUP, g_cbTRiAS).c_str());

	return m_pObjEnum -> AddProp (pIObjProp, pcGroup);
}

bool CAllProperties :: AddPropertyFunction (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup)
{
	TX_ASSERT (NULL != pIClsProp);

	if (NULL == pcGroup) 
		return m_pClsEnum -> AddProp (pIClsProp, FakeTRiASName(IDS_INTERNOPROPGROUP, g_cbTRiAS).c_str());

	return m_pClsEnum -> AddProp (pIClsProp, pcGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Entfernen einer PropertyFunction
bool CAllProperties::RemovePropertyFunction (LPCSTR pcName)
{
	return m_pObjEnum -> DeleteProp(pcName);
}

// Freigeben aller OPFs -------------------------------------------------------
bool CAllProperties :: RemoveAllObjPropertyFunctions (void)
{
	m_lRefONr = -1L;
	return m_pObjEnum -> EveryDelete();
}

bool CAllProperties :: RemoveAllClsPropertyFunctions (void)
{
	return m_pClsEnum -> EveryDelete();
}

// alle ObjektProperties einer Erweiterung zum Enumerator hinzufügen ----------
HRESULT CAllProperties :: CopyObjPropsToEnum (COleExtension *pExt, LONG lRefONr)
{
LPENUMOBJPROPS pIEnumOPs = NULL;
LPOBJECTPROPERTY pIOP = NULL;
LPOBJECTPROPS pIOPs = NULL;
HRESULT hr = pExt -> EnumObjPropFuncs (lRefONr, &pIEnumOPs, &pIOPs);

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

HRESULT CAllProperties :: CopyClsPropsToEnum (COleExtension *pExt, IEnumLONG *pIEnum)
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


// Interne EigenschaftsFunktionen hinzufügen ----------------------------------
extern "C" 
bool EXPORTTRIAS WINAPI EnumMCodesForObjProp (long lMCode, DWORD dw, void *pData)
{
LPOBJECTPROPERTY pIProp = NULL;
HRESULT hr = ObjPropCreateInstance (NULL, CLSID_ObjPropFeature, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);

	if (FAILED(hr)) return false;		// E_OUTOFMEMORY

IInitObjPropMerkmal *pIInit = NULL;
		
	hr = pIProp -> QueryInterface (IID_IInitObjPropMerkmal, (LPVOID *)&pIInit);
	if (SUCCEEDED(hr)) {
	UINT uiRes = IDS_INTERNOPROPGROUP;

		if (dw & MPSystemFeatures) 
			uiRes = IDS_SYSTEMPROPGROUP;

	ResString res (uiRes, 64);
	char cbBuffer[64];

		wsprintf (cbBuffer, res, g_cbTRiAS);

		pIInit -> Init (lMCode, (dw & MPSystemFeatures) ? true : false);
		pIInit -> Release();
		((CAllProperties *)pData) -> AddPropertyFunction (pIProp, cbBuffer);
	}
	pIProp -> Release();

return true;
}

bool CAllProperties :: AddInternalObjProperties (LONG lRefONr)
{
LPOBJECTPROPERTY pIProp = NULL;
HRESULT hr = ResultFromScode (E_FAIL);
string strName (FakeTRiASName(IDS_SYSTEMPROPGROUP, g_cbTRiAS));

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropONr, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp, strName.c_str()); 	// ObjektNummer (systemintern)
		pIProp -> Release();
	} else
		return false;

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropGUID, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp, strName.c_str()); 	// ObjektGUID (systemintern)
		pIProp -> Release();
	} else
		return false;

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropIdent, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp, strName.c_str()); 	// Identifikator (systemintern)
		pIProp -> Release();
	} else
		return false;

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjClassCode, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp); 	// ObjektKlassenSchlüssel
		pIProp -> Release();
	} else
		return false;

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjTypLong, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp); 	// ObjektTyp
		pIProp -> Release();
	} else
		return false;

	hr = ObjPropCreateInstance (NULL, CLSID_ObjPropObjTypShort, IID_IObjectProperty, 
				    (LPVOID *)&pIProp);
	if (SUCCEEDED(hr)) {
		AddPropertyFunction (pIProp); 	// ObjektTyp (Kurz)
		pIProp -> Release();
	} else
		return false;

// Eingabefelder als Objekteigenschaften
	{
		strName = FakeTRiASName (IDS_OBJPROPINTERACTIVE, g_cbTRiAS);
		for (int i = 1; i <= 4; i++) {
			hr = ObjPropCreateInstance (NULL, CLSID_ObjPropQueryField, IID_IObjectProperty, 
							(LPVOID *)&pIProp);
			if (SUCCEEDED(hr)) {
			IInitObjPropQueryField *pIInit = NULL;

				hr = pIProp -> QueryInterface (IID_IInitObjPropQueryField, (LPVOID *)&pIInit);
				if (SUCCEEDED(hr)) {
					pIInit -> Init (__hWndM, i);
					pIInit -> Release();

					AddPropertyFunction (pIProp, strName.c_str()); 
				}
				pIProp -> Release();
			} else
				break;
		}
	}
	if (0L == lRefONr) {
	// alle ObjektMerkmale als Objekteigenschaften generieren
	ENUMNOKEYEX ENK;
	ErrInstall EI (WC_NOMERKMAL);

		ENK.eFcn = (ENUMNOKEYEXPROC)EnumMCodesForObjProp;
		ENK.ePtr = this;
		ENK.eData = DWORD('a')|PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY;

		return DEX_EnumMCodesEx (ENK);
	} else {
	// existierende Objektmerkmale dieses Objektes verwenden
	ENUMLONGKEYEX ELK;
	ErrInstall EI (WC_NOMERKMAL);

		ELK.eFcn = (ENUMLONGKEYEXPROC)EnumMCodesForObjProp;
		ELK.ePtr = this;
		ELK.eKey = lRefONr;
		ELK.eData = DWORD('a')|PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY;

		return DEX_EnumObjektMerkmaleEx(ELK);
	}
}

#if defined(WIN32)
bool AddClsProperty (IClassProperty *pIClsProp, LPCSTR pcGroup, DWORD dwData)
{
	return reinterpret_cast<CAllProperties *>(dwData) -> AddPropertyFunction (pIClsProp, pcGroup);
}
#endif // WIN32

bool CAllProperties :: AddInternalClsProperties (void)
{
#if defined(WIN32)
// alle bisherigen ClsProps sind in TRiAS03 implementiert
	return RegisterPropertyActions (AddClsProperty, reinterpret_cast<DWORD>(this));
#else
	return true;		// keine definiert
#endif // WIN32
}

HRESULT CAllProperties::CreateNewInternalProp (
	LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData,
	REFIID riid, LPVOID *ppIObjProp)
{
	{
	// Vielleicht gibt es diese Objekteigenschaft schon.
	WObjectProperty OProp;	
	HRESULT hr = m_pObjEnum -> FindByName (pcName, OProp.ppi());

		if (SUCCEEDED(hr))
			return OProp -> QueryInterface (riid, ppIObjProp);
	}

// jetzt neu erzeugen, da noch nicht vorhanden
CPropertyName PropName (pcName);
CComVariant vData;
LONG lMCode = 0L;
LPCSTR pcOPName = PropName.GetName().c_str();

	if (FAILED(vData.ChangeType (VT_I4, &vOptData))) 
		lMCode = DEX_GetMCodeFromFeatureName(pcOPName);
	else 
		lMCode = V_I4(&vData);

	if (0L == lMCode) {
		lMCode = (dwFlags & PROPCAPS_RESTRICTED) ? 
					DEX_GetUniqueMCode() :
					DEX_GetUniqueSysMCode();
	}

// evtl. einer bestimmten Gattung zuordnen
	if (PropName.hasGroup()) {
	ResString resIntern (IDS_INTERNOPROPGROUP, 64);
	ResString resSystem (IDS_SYSTEMPROPGROUP, 64);
	string &rStr = PropName.GetGroup();

	// Objekteigenschaft finden/erzeugen
	DWORD dwData = DWORD('a');
	DWORD dwPbdFlags = DWORD('a');

		if (!(dwFlags & PROPCAPS_NOTREADONLY)) {
			dwData |= MPReadOnlyFeatures;
			dwPbdFlags |= PBDMERKMAL_READONLY;
		}
		
	// Objekteigenschaft in Pbd nachtragen
		if (rStr == resIntern.Addr()) {
			if (!WriteMCodeToPbd (lMCode, dwPbdFlags, pcOPName)) 
				return E_FAIL;
			if (!EnumMCodesForObjProp (lMCode, dwData, this))
				return E_FAIL;
		}
		else if (rStr == resSystem.Addr()) {
			if (!WriteMCodeToPbd (lMCode, dwPbdFlags|PBDMERKMAL_SYSTEMFLAG, pcOPName)) 
				return E_FAIL;
			if (!EnumMCodesForObjProp (lMCode, dwData|MPSystemFeatures, this))
				return E_FAIL;
		} 
		else
			return S_FALSE;		// nicht für uns

	} else {
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
		if (!WriteMCodeToPbd (lMCode, dwPbdFlags, pcOPName)) 
			return E_FAIL;
		if (!EnumMCodesForObjProp (lMCode, dwData, this))
			return E_FAIL;
	}

WObjectProperty OProp;
HRESULT hr = m_pObjEnum -> FindByName (pcName, OProp.ppi());

	if (FAILED(hr)) return hr;
	
	return OProp -> QueryInterface (riid, ppIObjProp);
}

bool WriteMCodeToPbd (LONG lMCode, DWORD dwFlags, LPCSTR pcKText, LPCSTR pcLText)
{
PBDMERKMAL TM;
bool iResult = true;
int iLen = strlen (pcKText);
int iLLen = 0;

	if (NULL == pcLText) {
		pcLText = pcKText;
		iLLen = iLen;
	} else
		iLLen = strlen(pcLText);

	INITSTRUCT(TM, PBDMERKMAL);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.pbdKText = (char *)pcKText;
	TM.pbdLText = (char *)pcLText;
	TM.pbdKTextLen = iLen;
	TM.pbdLTextLen = iLLen;
	TM.ipbdMTyp = short(dwFlags);
	TM.ipbdMLen = 64;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}

	return iResult;
}
	
