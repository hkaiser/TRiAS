// Zuordnen eines Identifikators zu einer Objektklassenbschreibung
// File: IDENTCLS.CPP

#include "triaspre.hxx"

#include <Atl/Ciid.h>
#include <ospace/std/map>
#include <errinst.hxx>

#include "strings.h"
#include "triasres.h"
#include "IdentCls.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma optimize("", off)		// problems with map

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
inline CComBSTR MakeOKSFromClass (BSTR bstrClass)
{
	_ASSERTE(NULL != bstrClass);

	if (L'[' != bstrClass[0]) {
	// ggf. in '[...]' einbetten
	CComBSTR bstr (L"[");

		bstr += bstrClass;
		bstr += L"]";
		return bstr;
	}
	return CComBSTR(bstrClass);
}

///////////////////////////////////////////////////////////////////////////////
// 
bool CMapIdentToClass::m_fAllowLeadingZeros = false;

CMapIdentToClass *CMapIdentToClass::CreateInstance (DatenBasisObjekt &rDBO)
{
CMapIdentToClass *pIdentCls = NULL;

	TX_TRY(pIdentCls = new CMapIdentToClass(rDBO));
	if (NULL == pIdentCls || !pIdentCls -> FInit()) {
		DELETE_OBJ(pIdentCls);
		return NULL;
	}
	return pIdentCls;
}

CMapIdentToClass::CMapIdentToClass (DatenBasisObjekt &rDBO)
	: m_rDBO(rDBO)
{
#if defined(_FORCE_LEGACY_CODE)
	m_lMCode = -1L;
#endif // _FORCE_LEGACY_CODE
	m_iIdBase = 10;
	m_fAllowLeadingZeros = false;
}

extern "C" 
BOOL CALLBACK EnumIdentsForClsMap (long lIdent, BOOL, void *pData)
{
CMapIdentToClass *pMap = (CMapIdentToClass *)pData;

#if defined(_FORCE_LEGACY_CODE)
	if (!pMap -> DBO().IsTRiASDBBased()) {
	char cbBuffer[_MAX_PATH];

		if (ReadTextMerkmal (TT_Identifikator, lIdent, pMap->MCode(), cbBuffer, sizeof(cbBuffer)))
			pMap -> AddEntry (cbBuffer, lIdent);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		USES_CONVERSION;
		COM_TRY {
		WTRiASObjects Objs;
		CComBSTR bstrOKS;

			THROW_FAILED_HRESULT(pMap -> DBO().GetObjectsFromMap (lIdent, Objs));
//			if (S_OK == Objs -> get_OKS(&bstrOKS))
			if (SUCCEEDED(Objs -> get_OKS(CLEARED(&bstrOKS))))
				pMap -> AddEntry (OLE2A(bstrOKS), lIdent);

		} COM_CATCH;
	}
	return true;
}

bool CMapIdentToClass::FInit (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!DBO().IsTRiASDBBased()) {
	// IdentBase speichern (wird später evtl. gebraucht)
		m_iIdBase = DEX_GetIdBase();

	// IdentMerkmalsCode holen/erzeugen
		m_lMCode = DBO().GetHeaderMCode (true, IDS_OBJCLASSMCODE, NULL, 
						IDS_OBJCLASSDESC_KT, IDS_OBJCLASSDESC_KT);
		if (-1L == m_lMCode) return false;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		m_iIdBase = 16;
	}

// evtl. alte Einträge vollständig löschen
	m_mapIdents.erase();

// Liste mit existierenden Objektklassenschlüsseln füllen
	try {
	ErrInstall EI (WC_NOIDENT);
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMNOKEYLONGPROC)EnumIdentsForClsMap;
		ENK.ePtr = this;
		if (!DEX_EnumIdents (ENK))
			return false;

		m_strRegExpr.pattern(g_cbHexDigits);

	// #HK980108
	// aus Header lesen, ob evtl. führende Nullen nicht ausgeblendet werden sollen
	CPrjHeaderEntry HE (m_rDBO.DB(), IDS_ALLOWLEADINGZEROS);

		m_fAllowLeadingZeros = HE.EntryLong(0) ? true : false;		// default ist false

	} catch (os_invalid_argument) {
	// invalid pattern
		TX_ASSERT(false);		// compile time error
		return false;
	} catch (...) {
		return false;			// out of memory in EnumCallBack
	}
	return true;
}

CMapIdentToClass::~CMapIdentToClass (void)
{
}

HRESULT CMapIdentToClass::ClassFromIdent (HPROJECT hPr, HOBJECTS ulIdent, os_string &rClass)
{
char cbBuffer[MAX_OKS_LEN];

	if (IsCompatible()) {// im CompatibilityMode Ident selbst als OKS verwenden
		try {
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%08lu" : "%08lx", ulIdent);
			rClass = cbBuffer;
		
		} catch (...) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

// jetzt in der Map suchen
	for (CIdentClsMap::iterator it = m_mapIdents.begin(); 
		 it != m_mapIdents.end(); it++)
	{
		if ((*it).second == ulIdent) {
			rClass = (*it).first.second;
			return S_OK;
		}
	}

// Ident ist nicht in der Liste, daher diesen selbst als OKS liefern
	try {
		if (m_fAllowLeadingZeros) 
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%08lu" : "%08lx", ulIdent);
		else
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%lu" : "%lx", ulIdent);
		rClass = cbBuffer;
	
	} catch (...) {
		return E_OUTOFMEMORY;
	}

	return S_FALSE;		// ok, aber nur Ident kopiert
}

HRESULT CMapIdentToClass::IdentFromClass (HPROJECT hPr, 
	const os_string &rClass, HOBJECTS *pulIdent, bool fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

	if (IsCompatible())	{	// im CompatibilityMode OKS selbst als Ident verwenden
		*pulIdent = strtoul (rClass.c_str(), NULL, m_iIdBase);
		return S_OK;
	}

// evtl. steht vorn dran ein Guid '{...}':
CComBSTR bstrProgId (g_cbNil);
os_string strClass = rClass;
CIID Guid;

	if ('{' == rClass[0] && '}' == rClass[37]) {
		Guid = CIID(rClass.substr (0, 38).c_str(), CIID::INITCIID_InitFromGuid);	// Guid herauslösen
		if (!!Guid)
			bstrProgId = Guid.ProgID().c_str();
		strClass = rClass.substr(38);
	}

// über RegExpr entweder Folge von HexDigits oder Folge von HexDigits in
// '[]' herausfiltern
int iMatched = m_strRegExpr.match(strClass);

	if (0 >= iMatched) return E_INVALIDARG;	// kein gültiger OKS

os_string strT;

	if (m_strRegExpr.group(1).size() > 0) {
	// ersten Fall gefunden ('[hexdigits]'), [] wegmachen
	os_string str (m_strRegExpr.group(1));

		strT = os_substring (str, 1, iMatched-2);
	} else if (m_strRegExpr.group(3).size() > 0) {
	// zweiten Fall gefunden, hexdigits rauslösen
		strT = m_strRegExpr.group(3);
	} else
		TX_ASSERT(false);

	if (0 == strT.size()) return E_INVALIDARG;	// kein gültiger OKS

// evtl. führende Nullen übergehen
HRESULT hr = CorrectZeros (strT);

	if (FAILED(hr)) return hr;

// versuchen OKS wiederzufinden
CIdentClsMap::iterator it = m_mapIdents.find(CIdentData(hPr, strT));

	if (it != m_mapIdents.end()) {
		*pulIdent = (*it).second;
		return S_OK;
	}

// nichts gefunden also evtl. neuen Ident erzeugen
	if (fCreateNew) {
		try {
		ULONG ulIdent = 0;

#if defined(_FORCE_LEGACY_CODE)
			if (!DBO().IsTRiASDBBased()) {
			ULONG ulIdent = DEX_GetUniqueSysICode();

			// in GeoDB nachziehen
				if (!WriteTextMerkmal (TT_Identifikator, ulIdent, m_lMCode, (LPSTR)strT.c_str(), TMCreateNewTarget))
					return E_FAIL;
			} else
#endif // _FORCE_LEGACY_CODE
			{
			WTRiASObjects Objs;
			CComBSTR bstrOKS(strT.c_str());

				bstrOKS = MakeOKSFromClass (bstrOKS);
				if (HACTPROJECT == hPr) {
				WTRiASProject Prj;

					RETURN_FAILED_HRESULT(DBO().GetTRiASProject (Prj.ppi()));
					RETURN_FAILED_HRESULT(Prj -> get_ObjectsDef (CComVariant(bstrOKS), VARIANT_TRUE, bstrProgId, Objs.ppi()));
				} else {
					if (!DBO().IsValidConnection(hPr))
						return E_INVALIDARG;
					RETURN_FAILED_HRESULT(DBO().DB(hPr).GetObjectsDef (0L, CComVariant(bstrOKS), VARIANT_TRUE, bstrProgId, Objs.ppi()));
				}

			// das neue Objekt wenigstens nach seinem Handle fragen
				RETURN_FAILED_HRESULT(Objs -> get_Handle ((INT_PTR *)&ulIdent));
				RETURN_FAILED_HRESULT(Objs -> put_OKS(bstrOKS));
			}

		// im Speicher anlegen
		pair<CIdentClsMap::iterator, bool> p = m_mapIdents.insert (CIdentClsMap::value_type(CIdentData(hPr, strT), ulIdent));

			if (!p.second)
				return E_FAIL;	// nichts eingefügt
			*pulIdent = ulIdent;

		} catch (...) {
			return E_OUTOFMEMORY;	// auch Neuerzeugen ist fehlgeschlagen	
		}

	} else {
	// OKS selbst als Ident verwenden
		*pulIdent = strtoul (strT.c_str(), NULL, m_iIdBase);
	}

	return S_FALSE;		// ok, aber nur Ident übernommen, bzw, Objs neu erzeugt
}

///////////////////////////////////////////////////////////////////////////////
// evtl. existierenden Eintrag modifizieren/löschen
HRESULT CMapIdentToClass::ModObjClassCode (HPROJECT hPr, HOBJECTS ulIdent, LPCSTR pcClass, bool fOverWrite)
{
// erstmal überprüfen, ob Code schon verzeichnet ist
	for (CIdentClsMap::iterator it = m_mapIdents.begin(); 
		 it != m_mapIdents.end(); it++)
	{
		if ((*it).second == ulIdent) {
			if (!fOverWrite) 
				return E_ACCESSDENIED;		// Eintrag existiert/nicht überschreiben

		// ansonsten diesen Eintrag löschen
			m_mapIdents.erase (it);
			break;
		}
	}

// jetzt noch überprüfen, ob OKS eindeutig ist
CIdentClsMap::iterator it1 = m_mapIdents.find (CIdentData(hPr, os_string(pcClass)));

	if (it1 != m_mapIdents.end()) {
		if (!fOverWrite) 
			return E_ACCESSDENIED;		// Eintrag existiert/nicht überschreiben

	// ansonsten diesen Eintrag löschen
		m_mapIdents.erase (it1);
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!DBO().IsTRiASDBBased()) {
	// in GeoDB nachziehen
		if (!WriteTextMerkmal (TT_Identifikator, ulIdent, m_lMCode, (LPSTR)pcClass, TMCreateNewTarget))
		{
			return E_FAIL;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
	WTRiASObjects Objs;
	CComBSTR bstrOKS(pcClass);

		bstrOKS = MakeOKSFromClass (bstrOKS);
		if (FAILED(DBO().GetObjectsFromMap (ulIdent, Objs))) {
		// wenn diese Objektmenge noch nicht existiert, dann neu erzeugen
		// als Namen erstmal den Objektklassenschlüssel verwenden
			if (HACTPROJECT == hPr) {
			WTRiASProject Prj;

				RETURN_FAILED_HRESULT(DBO().GetTRiASProject (Prj.ppi()));
				RETURN_FAILED_HRESULT(Prj -> get_ObjectsDef (CComVariant(bstrOKS), VARIANT_TRUE, CComBSTR(g_cbNil), Objs.ppi()));
			} else {
				hPr = DBO().GetIdentDBHandle (ulIdent, hPr);
				if (!DBO().IsValidConnection(hPr))
					return E_INVALIDARG;
				RETURN_FAILED_HRESULT(DBO().DB(hPr).GetObjectsDef (ulIdent, CComVariant(bstrOKS), VARIANT_TRUE, CComBSTR(g_cbNil), Objs.ppi()));
			}

		// das neue Objekt wenigstens von seinem Handle informieren
			RETURN_FAILED_HRESULT(Objs -> put_Handle (ulIdent));
		}
		RETURN_FAILED_HRESULT(Objs -> put_OKS(bstrOKS));
	}

// Eintrag neu schreiben
	return AddEntry (pcClass, ulIdent);
}

///////////////////////////////////////////////////////////////////////////////
// Anfangsinitialisierung aus der GeoDB
HRESULT CMapIdentToClass::AddEntry (LPCSTR pCls, HOBJECTS ulIdent)
{
	_ASSERTE(NULL != pCls);
	try {
	HPROJECT hPr = DBO().GetIdentDBHandle (ulIdent, NULL);
	os_string strT;

		if ('[' == pCls[0]) {
		// über RegExpr entweder Folge von HexDigits oder Folge von HexDigits in
		// '[]' herausfiltern
		os_string strClass (pCls);
		int iMatched = m_strRegExpr.match(strClass);

			if (0 >= iMatched) return E_INVALIDARG;	// kein gültiger OKS

		os_string strT;

			if (m_strRegExpr.group(1).size() > 0) {
			// ersten Fall gefunden ('[hexdigits]'), [] wegmachen
			os_string str (m_strRegExpr.group(1));

				strT = os_substring (str, 1, iMatched-2);
			} else if (m_strRegExpr.group(3).size() > 0) {
			// zweiten Fall gefunden, hexdigits rauslösen
				strT = m_strRegExpr.group(3);
			} else
				TX_ASSERT(false);

			if (0 == strT.size()) 
				return E_INVALIDARG;	// kein gültiger OKS
		} else
			strT = pCls;

		pair<CIdentClsMap::iterator, bool> p = m_mapIdents.insert(CIdentClsMap::value_type(CIdentData(hPr, strT), ulIdent));
		if (!p.second) 
			return E_FAIL;

	} catch (...) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

BOOL CMapIdentToClass::EnumClassProjects (
	LPCSTR pcClass, BOOL (CALLBACK *pFcn) (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData), UINT_PTR dwData)
{
os_string strClass(pcClass);
CIdentData Key (NULL, strClass);
CIdentClsMap::iterator it = m_mapIdents.lower_bound(Key);

	if (it == m_mapIdents.end())
		return TRUE;		// no entries at all

	for (/**/; it != m_mapIdents.end() && strClass == (*it).first.second; ++it)
	{
		if (!(pFcn)((*it).first.first, (*it).first.second.c_str(), dwData))
			return FALSE;		// abgebrochen
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Mapping Ident/Objektklassenschlüssel
bool DatenBasisObjekt::InitClsIdentMap (void)
{
// evtl. existierende freigeben
	DELETE_OBJ(m_pClsIdents);

// neue Map erzeugen
	m_pClsIdents = CMapIdentToClass::CreateInstance (*this);
	return (NULL != m_pClsIdents) ? true : false;
}

void DatenBasisObjekt::DeleteClsIdentMap (void)
{
	DELETE_OBJ(m_pClsIdents);
}

HRESULT DatenBasisObjekt::IdentFromClass(HPROJECT hPr, IDENTFROMCLASS *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);
	TX_ASSERT(HACTCONNECTION != hPr);			// Projekt muß (neuerdings) gegeben sein

	return m_pClsIdents -> IdentFromClass (hPr,
		pData->pcClass, &pData->ulIdent, pData->fCreateNew);
}

HRESULT DatenBasisObjekt::ClassFromIdent (HPROJECT hPr, CLASSFROMIDENT *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);
	if (NULL == hPr)
		hPr = GetIdentParentHandle (pData->ulIdent, TRUE);

os_string str;
HRESULT hr = m_pClsIdents -> ClassFromIdent (hPr, pData->ulIdent, str);

	if (FAILED(hr)) return hr;

int iLen = min (pData->iBuffLen, (int)str.size()+1);

	strncpy (pData->pClass, str.c_str(), iLen);
	pData->pClass[iLen-1] = '\0';

	return hr;
}

HRESULT DatenBasisObjekt::ModObjClassCode (HPROJECT hPr, MODOBJCLASSCODE *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);
	TX_ASSERT(hPr == GetIdentDBHandle (pData->ulIdent, hPr));	// Datenquelle muß stimmen
	if (NULL == hPr)
		hPr = GetIdentDBHandle (pData->ulIdent, hPr);


	return m_pClsIdents -> ModObjClassCode (hPr, pData->ulIdent, pData->pcClass, pData->fOverWrite);
}

BOOL DatenBasisObjekt::EnumClassProjects (
	LPCSTR pcClass, BOOL (CALLBACK *pFcn) (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData), UINT_PTR dwData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}
	TX_ASSERT(NULL != m_pClsIdents);

	return m_pClsIdents -> EnumClassProjects (pcClass, pFcn, dwData);
}

