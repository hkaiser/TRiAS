// Klasse, die einen vollständigen Property-Namen behandeln kann --------------
// File: PROPNAME.CXX

#include "precomp.hxx"

#include <propname.hxx>

CPropertyName :: CPropertyName (void)
{
	m_rgType = UNKNOWN_ROOT;
}

CPropertyName :: CPropertyName (LPCSTR pcFullName)
{
	ParseName (pcFullName);
}

CPropertyName :: CPropertyName (IObjectProperty *pIObjProp)
{
 	m_pIObjProp = pIObjProp;
}

CPropertyName :: CPropertyName (PROPTYPE rgType, 
								LPCSTR pcGroup, 
								LPCSTR pcSubGroup,
								LPCSTR pcName)
	       : m_rgType(rgType)
{
	TRY {
		m_strSubGroup = pcSubGroup;
		m_strGroup = pcGroup;
		m_strName = pcName;
	} CATCH_ALL (e) {
		m_rgType = UNKNOWN_ROOT;
	} END_CATCH_ALL
}

bool CPropertyName :: ParseName (LPCSTR pcName)
{
	TRY {
	string str = pcName;
	size_t pos = str.find ("\\");

		m_rgType = UNKNOWN_ROOT;
		if (NPOS == pos) throw false;

	// Wurzel feststellen
	string sstr = str.substr (0, pos);
	 
		if (sstr == "OBJPROP_ROOT")
			m_rgType = OBJPROP_ROOT;
		else
		if (sstr == "CLSPROP_ROOT")
			m_rgType = CLSPROP_ROOT;
		else {
			m_rgType = OBJPROP_ROOT;
			m_strName = str.substr (pos);
			return true;	// nur Name gegeben
		}

	// Gruppe feststellen
	size_t posn = str.find ("\\", pos+1);

		if (NPOS == posn)
			m_strName = str.substr (pos+1);	// keine Gruppe gegeben
		else {
			m_strGroup = str.substr (pos+1, posn-pos-1);
			m_strName = str.substr (posn+1);
		}
		return true;
	} CATCH_ALL (e) {
		m_rgType = UNKNOWN_ROOT;
		return false;
	} END_CATCH_ALL
}


bool CPropertyName :: GetFullName (string &str)
{
	if (UNKNOWN_ROOT == m_rgType)
		return false;

	TRY {
		if (0 < m_strGroup.length()) {
			str = (OBJPROP_ROOT == m_rgType) ? 
					"OBJPROP_ROOT\\" : 
					"CLSPROP_ROOT\\";
			str += m_strGroup;
			str += "\\";
			str += m_strName;
		} else
			str = m_strName;
	} CATCH_ALL (e) {
		return false;
	} END_CATCH_ALL
}

bool CPropertyName :: GetFullName (LPSTR pBuffer, WORD wLen)
{
string str;

	if (!GetFullName (str)) return false;

WORD iLen = min (wLen-1, WORD(str.length()));

	strncpy (pBuffer, str.c_str(), iLen);
	pBuffer[iLen] = '\0';

return true;
}

bool CPropertyName :: SetType (PROPTYPE rgType)
{
	switch (rgType) {
	case OBJPROP_ROOT:
	case CLSPROP_ROOT:
	case UNKNOWN_ROOT:
		m_rgType = rgType;
		return true;

	default:
		return false;
	}
}

bool CPropertyName :: SetGroup (LPCSTR pcGroup)
{
	TRY {
		m_strGroup = pcGroup;
		return true;
	} CATCH_ALL (e) {
		return false;
	} END_CATCH_ALL
}

bool CPropertyName :: SetName (LPCSTR pcName)
{
	TRY {
		m_strName = pcName;
		return true;
	} CATCH_ALL (e) {
		return false;
	} END_CATCH_ALL
}

bool CPropertyName :: operator== (CPropertyName &rP)
{
	return	(GetType() == rP.GetType()) && 
		(GetGroup() == rP.GetGroup()) &&
		(GetName() == rP.GetName());
}

int Compare (CPropertyName &rP1, CPropertyName &rP2)
{
// Typen vergleichen
	if (rP1.GetType() < rP2.GetType())
		return -1;
	if (rP1.GetType() > rP2.GetType())
		return 1;

// Typen sind gleich, Gruppen vergleichen
int iCmp = 0;

	if (iCmp = strcmp (rP1.GetGroup().c_str(), rP2.GetGroup().c_str()))
		return iCmp;

// Gruppen sind auch gleich, also an Hand der Namen entscheiden
	return strcmp (rP1.GetName().c_str(), rP2.GetName().c_str());
}
