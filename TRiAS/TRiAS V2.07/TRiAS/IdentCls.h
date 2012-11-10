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

class CMapIdentToClass
{
private:
	typedef map<os_string, ULONG, less<os_string> > CIdentClsMap;
	CIdentClsMap m_mapIdents;
	DatenBasisObjekt &m_rDBO;
	LONG m_lMCode;
	int m_iIdBase;
	os_regexp m_strRegExpr;
	bool m_fAllowLeadingZeros;

public:
		CMapIdentToClass (DatenBasisObjekt &rDBO);
		~CMapIdentToClass (void);

static CMapIdentToClass *CreateInstance (DatenBasisObjekt &rDBO);

	bool FInit (void);

// sonstige member
	HRESULT AddEntry (LPCSTR pCls, ULONG ulIdent);
	HRESULT ClassFromIdent (ULONG ulIdent, os_string &rClass);
	HRESULT IdentFromClass (LPCSTR pcClass, ULONG *pulIdent, bool fCreateNew = false)
		{ return IdentFromClass (os_string(pcClass), pulIdent, fCreateNew); }
	HRESULT IdentFromClass (const os_string &rClass, ULONG *pulIdent, bool fCreateNew = false);
	HRESULT ModObjClassCode (ULONG ulIdent, LPCSTR pcClass, bool fOverWrite = false);

	LONG MCode (void) { return m_lMCode; }

	bool IsCompatible() { return m_rDBO.Compatibility(); }
};

#endif // _IDENTCLS_H
