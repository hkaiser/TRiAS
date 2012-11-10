// Zuordnen eines Identifikators zu einer Objektklassenbschreibung
// File: IDENTCLS.H

#if !defined(_IDENTCLS_H)
#define _IDENTCLS_H

///////////////////////////////////////////////////////////////////////////////
// Diese Klasse ordnet einem externen ObjektklassenSchlüssel (z.B. Generali-
// sierungsschlüssel) einen eindeutigen Identifikator zur Verwendung in diesem
// TRiAS® Projekt zu.
// Damit ist es möglich mehr als 8 Stellen für einem ObjektklassenSchlüssel zu 
// verwenden.
// Die Zuordnung erfolgt durch die DEX_-Messages 'DEX_GetClassFromIdent()' 
// und 'DEX_GetIdentFromClass()'

#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>

#if defined(_DEBUG)
#define THIS_FILE __FILE__
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
//
class CMapIdentToClass
{
private:
	friend inline HRESULT CorrectZeros (string &rStr);

	typedef pair<HPROJECT, os_string> CIdentData;
	class CHProject 
	{
	public:
		CHProject (HPROJECT hPr) : m_hPr(hPr) {}
		inline bool operator< (const CHProject &rhs)
		{
			if (NULL == m_hPr || NULL == rhs.m_hPr)
				return false;		// einer von beiden nicht gegeben: Identität annehmen
			return m_hPr < rhs.m_hPr;
		}

	private:
		HPROJECT m_hPr;
	};
		
	friend inline bool operator< (const CIdentData &lhs, const CIdentData &rhs)
	{
	string strlhs = lhs.second;
	string strrhs = rhs.second;

		TX_VERIFY(SUCCEEDED(CorrectZeros (strlhs)));
		TX_VERIFY(SUCCEEDED(CorrectZeros (strrhs)));

	// OKS vergleichen: evtl. führende Nullen ignorieren
	int iCmp = strcmp (strlhs.c_str(), strrhs.c_str());

	// ProjektHandles spielen genau dann eine Rolle, wenn Oks identisch sind, sonst nicht
		if (iCmp != 0) 
			return (iCmp < 0) ? true : false;	// OKS nicht identisch, alles nicht identisch
		return CHProject(lhs.first) < CHProject(rhs.first);
	}
	typedef map<CIdentData, HOBJECTS, less<CIdentData> > CIdentClsMap;

	CIdentClsMap m_mapIdents;
	DatenBasisObjekt &m_rDBO;
	os_regexp m_strRegExpr;
	int m_iIdBase;
	static bool m_fAllowLeadingZeros;		// wird nur einmal gebraucht

#if defined(_FORCE_LEGACY_CODE)
	LONG m_lMCode;
#endif // _FORCE_LEGACY_CODE

public:
		CMapIdentToClass (DatenBasisObjekt &rDBO);
		~CMapIdentToClass (void);

static CMapIdentToClass *CreateInstance (DatenBasisObjekt &rDBO);


	bool FInit (void);

// sonstige member
	HRESULT AddEntry (LPCSTR pCls, HOBJECTS ulIdent);
	HRESULT ClassFromIdent (HPROJECT hPr, HOBJECTS ulIdent, os_string &rClass);
	HRESULT IdentFromClass (HPROJECT hPr, LPCSTR pcClass, HOBJECTS *pulIdent, bool fCreateNew = false)
		{ return IdentFromClass (hPr, os_string(pcClass), pulIdent, fCreateNew); }
	HRESULT IdentFromClass (HPROJECT hPr, const os_string &rClass, HOBJECTS *pulIdent, bool fCreateNew = false);
	HRESULT ModObjClassCode (HPROJECT hPr, HOBJECTS ulIdent, LPCSTR pcClass, bool fOverWrite = false);
	BOOL EnumClassProjects (LPCSTR pcClass, BOOL (CALLBACK *pFcn) (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData), UINT_PTR dwData);

#if defined(_FORCE_LEGACY_CODE)
	LONG MCode (void) { return m_lMCode; }
#endif // _FORCE_LEGACY_CODE

	bool IsCompatible() { return m_rDBO.Compatibility(); }
	DatenBasisObjekt &DBO() { return m_rDBO; }
};

///////////////////////////////////////////////////////////////////////////////
// 
inline HRESULT CorrectZeros (string &rStr)
{
	if (!CMapIdentToClass::m_fAllowLeadingZeros) {
	os_string::size_type iPos = rStr.find_first_not_of ('0');

		if (iPos == os_npos) return E_INVALIDARG;		// Nur Nullen
		if (iPos > 0)
			rStr = rStr.substr (iPos);
	} 
	else {
	// nicht nur nichts vorn abschneiden, sondern sogar auf 8 Stellen aufüllen
	size_t iLen = rStr.size();

		if (iLen < 8) 
			rStr = os_string(8-iLen, '0') + rStr;
	}
	return S_OK;
}

#endif // _IDENTCLS_H
