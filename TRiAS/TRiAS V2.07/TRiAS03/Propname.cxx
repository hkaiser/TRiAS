// Klasse, die einen vollständigen Property-Namen behandeln kann 
// File: PROPNAME.CXX

#include "trias03p.hxx"

#include <ixtensn.hxx>
#include <propname.hxx>

#if defined(__NOTRIASSTRINGS__)
#define NPOS os_npos
#endif // __NOTRIASSTRINGS__

CPropertyName::CPropertyName (void)
{
	m_rgType = UNKNOWN_ROOT;
	m_fhasGroup = false;
	m_fhasSubGroup = false;
}

CPropertyName::CPropertyName (LPCSTR pcFullName)
{
	ParseName (pcFullName);
}

CPropertyName::CPropertyName (IObjectProperty *pIObjProp)
{
char cbBuffer[2*_MAX_PATH];
HRESULT hr = pIObjProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer)-1, NULL);
string strFullName (cbBuffer);

	if (SUCCEEDED(hr)) {
		ParseName (strFullName.c_str());
	} else 
		m_rgType = UNKNOWN_ROOT;
}

CPropertyName::CPropertyName (
	PROPTYPE rgType, LPCSTR pcGroup, LPCSTR pcSubGroup, LPCSTR pcName)
	       : m_rgType(rgType)
{
	try {
		m_strGroup = pcGroup;
		m_fhasGroup = true;
		m_strName = pcName;

		if (pcSubGroup) {
			m_strSubGroup = pcSubGroup;
			m_fhasSubGroup = true;
		}
	} catch (...) {
		m_rgType = UNKNOWN_ROOT;
		m_fhasGroup = false;
		m_fhasSubGroup = false;
	}
}

bool CPropertyName::ParseName (LPCSTR pcName)
{
	try {
	string str = pcName;
	size_t pos = str.find ("\\");

		m_strGroup.remove();
		m_fhasGroup = false;
		m_strSubGroup.remove();
		m_fhasSubGroup = false;
		m_rgType = UNKNOWN_ROOT;

		if (NPOS == pos) {
		// nur Name gegeben
			m_rgType = OBJPROP_ROOT;
			m_strName = pcName;
			return true;
		}

	// Wurzel feststellen
	string sstr = str.substr (0, pos);
	 
		if (sstr == "OBJPROP_ROOT")
			m_rgType = OBJPROP_ROOT;
		else
		if (sstr == "CLSPROP_ROOT")
			m_rgType = CLSPROP_ROOT;
		else {
			m_rgType = OBJPROP_ROOT;
			return SetName (pcName);	// nur Name/SubGruppe gegeben
		}

	// Gruppe feststellen
	size_t posn = str.find ("\\", pos+1);

		if (NPOS == posn)
			m_strName = str.substr (pos+1);	// keine Gruppe gegeben
		else {
			m_strGroup = str.substr (pos+1, posn-pos-1);
			m_fhasGroup = true;

		size_t posn2 = str.find ("\\", posn+1);

			if (NPOS == posn2) // keine Sub-Gruppe
				m_strName = str.substr (posn+1);
			else {
				m_strSubGroup = str.substr (posn+1, posn2-posn-1);
				m_fhasSubGroup = true;
				m_strName = str.substr (posn2+1);
			}
		}
		return true;

	} catch (...) {
		m_rgType = UNKNOWN_ROOT;
		return false;
	}
}


bool CPropertyName::GetFullName (string &str)
{
	if (UNKNOWN_ROOT == m_rgType)
		return false;

	try {
		if (0 < m_strGroup.length()) {
			str = (OBJPROP_ROOT == m_rgType) ? 
					"OBJPROP_ROOT\\" : 
					"CLSPROP_ROOT\\";
			if (m_fhasGroup) {
				str += m_strGroup;
				str += "\\";
			}
			if (m_fhasSubGroup) {
				str += m_strSubGroup;
				str += "\\";
			}
			str += m_strName;
		} else
			str = m_strName;
	} catch (...) {
		return false;
	}
}

bool CPropertyName::GetFullName (LPSTR pBuffer, WORD wLen)
{
string str;

	if (!GetFullName (str)) return false;

WORD iLen = min ((unsigned int)(wLen-1), str.length());

	strncpy (pBuffer, str.c_str(), iLen);
	pBuffer[iLen] = '\0';

return true;
}

bool CPropertyName::SetType (PROPTYPE rgType)
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

bool CPropertyName::SetGroup (LPCSTR pcGroup)
{
	try {
		if (pcGroup) {
			m_strGroup = pcGroup;
			m_fhasGroup = true;
		} else {
			m_strGroup.remove();
			m_fhasGroup = false;
		}
		return true;
	} catch (...) {
		return false;
	}
}

bool CPropertyName::SetSubGroup (LPCSTR pcSubGroup)
{
	try {
		if (pcSubGroup) {
			m_strSubGroup = pcSubGroup;
			m_fhasSubGroup = true;
		} else {
			m_strSubGroup.remove();
			m_fhasSubGroup = false;
		}
		return true;
	} catch (...) {
		return false;
	}
}

bool CPropertyName::SetName (LPCSTR pcName)
{
	try {
	string str (pcName);
	size_t pos = str.find ("\\");

		if (pos != NPOS) {
			m_strSubGroup = str.substr (0, pos);
			m_fhasSubGroup = true;

			m_strName = str.substr (pos+1);
		} else
			m_strName = pcName;
		return true;

	} catch (...) {
		return false;
	}
}

bool CPropertyName::operator== (CPropertyName &rP)
{
	return 0 == Compare(*this, rP);
}

int Compare (CPropertyName &rP1, CPropertyName &rP2)
{
// Bezeichner vergleichen
int iCmp = strcmp (rP1.GetName().c_str(), rP2.GetName().c_str());

	if (iCmp != 0) return iCmp;

// Bezeichner sind identisch, Gruppen vergleichen
	if (rP1.hasGroup() && rP2.hasGroup()) {
		if (iCmp = strcmp (rP1.GetGroup().c_str(), rP2.GetGroup().c_str()))
			return iCmp;
	}

	if (rP1.hasSubGroup() && rP2.hasSubGroup()) {
		if (iCmp = strcmp (rP1.GetSubGroup().c_str(), rP2.GetSubGroup().c_str()))
			return iCmp;
	}

// Typen vergleichen
	if (rP1.GetType() < rP2.GetType())
		return -1;
	if (rP1.GetType() > rP2.GetType())
		return 1;

	return 0;	// alles identisch
}

