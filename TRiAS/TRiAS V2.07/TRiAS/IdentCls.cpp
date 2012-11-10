// Zuordnen eines Identifikators zu einer Objektklassenbschreibung
// File: IDENTCLS.CPP

#include "triaspre.hxx"

#include <ospace/std/map>

#include "strings.h"
#include "triasres.h"
#include "IdentCls.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma optimize("", off)		// problems with map

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
long GetHeaderMCode (bool fGenerate, uint resID, LPCSTR pView, uint uiResKT, uint uiResLT);
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen);
bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0);

///////////////////////////////////////////////////////////////////////////////
// 
CMapIdentToClass *CMapIdentToClass::CreateInstance (DatenBasisObjekt &rDBO)
{
	try {
	CMapIdentToClass *pIdentCls = new CMapIdentToClass(rDBO);

		if (NULL == pIdentCls || !pIdentCls -> FInit()) {
			DELETE(pIdentCls);
			return NULL;
		}
		return pIdentCls;

	} catch (bad_alloc) {
		return NULL;
	}
}

CMapIdentToClass::CMapIdentToClass (DatenBasisObjekt &rDBO)
	: m_rDBO(rDBO)
{
	m_lMCode = -1L;
	m_iIdBase = 10;
	m_fAllowLeadingZeros = false;
}

extern "C" 
bool CALLBACK EnumIdentsForClsMap (long lIdent, bool, void *pData)
{
char cbBuffer[_MAX_PATH];
CMapIdentToClass *pMap = (CMapIdentToClass *)pData;

	if (ReadTextMerkmal (TT_Identifikator, lIdent, pMap->MCode(), 
						 cbBuffer, sizeof(cbBuffer)))
	{
		pMap -> AddEntry (cbBuffer, lIdent);
	}

	return true;
}

bool CMapIdentToClass::FInit (void)
{
// IdentBase speichern (wird später evtl. gebraucht)
	m_iIdBase = DEX_GetIdBase();

// IdentMerkmalsCode holen/erzeugen
	m_lMCode = GetHeaderMCode (true, IDS_OBJCLASSMCODE, NULL, 
					IDS_OBJCLASSDESC_KT, IDS_OBJCLASSDESC_KT);
	if (-1L == m_lMCode) return false;

	try {
	// Liste mit existierenden Objektklassenschlüsseln füllen
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMNOKEYLONGPROC)EnumIdentsForClsMap;
		ENK.ePtr = this;
		if (!DEX_EnumIdents (ENK))
			return false;

		m_strRegExpr.pattern(g_cbHexDigits);

	// #HK980108
	// aus Header lesen, ob evtl. führende Nullen nicht ausgeblendet werden sollen
	HeaderEntry HE (m_rDBO.DB(), IDS_ALLOWLEADINGZEROS);

		m_fAllowLeadingZeros = HE.EntryLong(0) ? true : false;		// default ist false

	} catch (os_invalid_argument) {
	// invalid pattern
		TX_ASSERT(false);		// compile time error
		return false;
	} catch (bad_alloc) {
		return false;			// out of memory in EnumCallBack
	}
	return true;
}

CMapIdentToClass::~CMapIdentToClass (void)
{
}

HRESULT CMapIdentToClass::ClassFromIdent (ULONG ulIdent, os_string &rClass)
{
char cbBuffer[MAX_OKS_LEN];

	if (IsCompatible()) {// im CompatibilityMode Ident selbst als OKS verwenden
		try {
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%08lu" : "%08lx", ulIdent);
			rClass = cbBuffer;
		
		} catch (bad_alloc) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

// jetzt in der Map suchen
	for (CIdentClsMap::iterator it = m_mapIdents.begin(); 
		 it != m_mapIdents.end(); it++)
	{
		if ((*it).second == ulIdent) {
			rClass = (*it).first;
			return S_OK;
		}
	}

// Ident ist nicht in der Liste, daher diesen selbst als OKS liefern
	try {
	// #HK980113
		if (m_fAllowLeadingZeros) 
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%08lu" : "%08lx", ulIdent);
		else
			wsprintf (cbBuffer, (10 == m_iIdBase) ? "%lu" : "%lx", ulIdent);
		rClass = cbBuffer;
	
	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	}

	return S_FALSE;		// ok, aber nur Ident kopiert
}

HRESULT CMapIdentToClass::IdentFromClass (
	const os_string &rClass, ULONG *pulIdent, bool fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

	if (IsCompatible())	{	// im CompatibilityMode OKS selbst als Ident verwenden
		*pulIdent = strtoul (rClass.c_str(), NULL, m_iIdBase);
		return S_OK;
	}

// über RegExpr entweder Folge von HexDigits oder Folge von HexDigits in
// '[]' herausfiltern
int iMatched = m_strRegExpr.match(rClass);

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
	if (!m_fAllowLeadingZeros) {
	os_string::size_type iPos = strT.find_first_not_of ('0');

		if (iPos == os_npos) return E_INVALIDARG;		// Nur Nullen
		if (iPos > 0)
			strT = strT.substr (iPos);
	} else {
	// nicht nur nichts vorn abschneiden, sondern sogar auf 8 Stellen aufüllen
	size_t iLen = strT.size();

		if (iLen < 8) 
			strT = os_string(8-iLen, '0') + strT;
	}

// versuchen OKS wiederzufinden
CIdentClsMap::iterator it = m_mapIdents.find(strT);

	if (it != m_mapIdents.end()) {
		*pulIdent = (*it).second;
		return S_OK;
	}

// nichts gefunden also evtl. neuen Ident erzeugen
	if (fCreateNew) {
		try {
		ULONG ulIdent = DEX_GetUniqueSysICode();

		// in GeoDB nachziehen
			if (!WriteTextMerkmal (TT_Identifikator, ulIdent, 
					m_lMCode, (LPSTR)strT.c_str(), TMCreateNewTarget))
				return E_FAIL;

		// im Speicher anlegen
		pair<CIdentClsMap::iterator, bool> p = m_mapIdents.insert (CIdentClsMap::value_type(strT, ulIdent));

			if (!p.second)
				return E_FAIL;	// nichts eingefügt
			*pulIdent = ulIdent;

		} catch (bad_alloc) {
			return E_OUTOFMEMORY;	// auch Neuerzeugen ist fehlgeschlagen	
		}

	} else {
	// OKS selbst als Ident verwenden
		*pulIdent = strtoul (strT.c_str(), NULL, m_iIdBase);
	}

	return S_FALSE;		// ok, aber nur Ident übernommen
}

///////////////////////////////////////////////////////////////////////////////
// evtl. existierenden Eintrag modifizieren/löschen
HRESULT CMapIdentToClass::ModObjClassCode (ULONG ulIdent, LPCSTR pcClass, bool fOverWrite)
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
CIdentClsMap::iterator it1 = m_mapIdents.find (os_string(pcClass));

	if (it1 != m_mapIdents.end()) {
		if (!fOverWrite) 
			return E_ACCESSDENIED;		// Eintrag existiert/nicht überschreiben

	// ansonsten diesen Eintrag löschen
		m_mapIdents.erase (it1);
	}

// in GeoDB nachziehen
	if (!WriteTextMerkmal (TT_Identifikator, ulIdent, m_lMCode, 
		(LPSTR)pcClass, TMCreateNewTarget))
	{
		return E_FAIL;
	}

// Eintrag neu schreiben
	return AddEntry (pcClass, ulIdent);
}

///////////////////////////////////////////////////////////////////////////////
// Anfangsinitialisierung aus der GeoDB
HRESULT CMapIdentToClass::AddEntry (LPCSTR pCls, ULONG ulIdent)
{
	try {
		pair<CIdentClsMap::iterator, bool> p = m_mapIdents.insert(CIdentClsMap::value_type(os_string(pCls), ulIdent));
		if (!p.second) return E_FAIL;

	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Mapping Ident/Objektklassenschlüssel
bool DatenBasisObjekt::InitClsIdentMap (void)
{
	m_pClsIdents = CMapIdentToClass::CreateInstance (*this);
	return (NULL != m_pClsIdents) ? true : false;
}

void DatenBasisObjekt::DeleteClsIdentMap (void)
{
	DELETE(m_pClsIdents);
}

HRESULT DatenBasisObjekt::IdentFromClass(IDENTFROMCLASS *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);
	return m_pClsIdents -> IdentFromClass (
		pData->pcClass, &pData->ulIdent, pData->fCreateNew);
}

HRESULT DatenBasisObjekt::ClassFromIdent (CLASSFROMIDENT *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);

os_string str;
HRESULT hr = m_pClsIdents -> ClassFromIdent (pData->ulIdent, str);

	if (FAILED(hr)) return hr;

int iLen = min (pData->iBuffLen, (int)str.size()+1);

	strncpy (pData->pClass, str.c_str(), iLen);
	pData->pClass[iLen-1] = '\0';

	return hr;
}

HRESULT DatenBasisObjekt::ModObjClassCode (MODOBJCLASSCODE *pData)
{
	if (NULL == m_pClsIdents) {
	// Idents <--> Objektklassenschlüssel initialisieren
		if (!InitClsIdentMap())
			return E_OUTOFMEMORY;
	}

	TX_ASSERT(NULL != m_pClsIdents);
	return m_pClsIdents -> ModObjClassCode (
			pData->ulIdent, pData->pcClass, pData->fOverWrite);
}

