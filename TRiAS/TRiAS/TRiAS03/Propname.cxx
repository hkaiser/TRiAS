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
	m_fHasFullName = false;
}

CPropertyName::CPropertyName (PROPTYPE rgType)
{
	m_rgType = rgType;
	m_fhasGroup = false;
	m_fhasSubGroup = false;
	m_fHasFullName = false;
}

CPropertyName::CPropertyName (LPCSTR pcFullName)
{
	m_fHasFullName = false;
	ParseName (pcFullName);
}

CPropertyName::CPropertyName (IObjectProperty *pIObjProp)
{
	m_fHasFullName = false;

char cbBuffer[2*_MAX_PATH];
HRESULT hr = pIObjProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer)-1, NULL);
string strFullName (cbBuffer);

	if (SUCCEEDED(hr)) {
		ParseName (strFullName.c_str());
	} else 
		m_rgType = UNKNOWN_ROOT;
}

CPropertyName::CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, LPCSTR pcSubGroup, LPCSTR pcName)
	: m_rgType(rgType)
{
	m_fHasFullName = false;
	m_fhasSubGroup = false;

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
	m_fHasFullName = false;
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

	} catch (...) {
		m_rgType = UNKNOWN_ROOT;
		return false;
	}
	return true;
}


bool CPropertyName::GetFullName (string &str)
{
	if (UNKNOWN_ROOT == m_rgType)
		return false;

	try {
		if (!m_fHasFullName) {
			if (0 < m_strGroup.length()) {
				m_strFullName = (OBJPROP_ROOT == m_rgType) ? 
						"OBJPROP_ROOT\\" : 
						"CLSPROP_ROOT\\";
				if (m_fhasGroup) {
					m_strFullName += m_strGroup;
					m_strFullName += "\\";
				}
				if (m_fhasSubGroup) {
					m_strFullName += m_strSubGroup;
					m_strFullName += "\\";
				}
				m_strFullName += m_strName;
			} else
				m_strFullName = m_strName;

			m_fHasFullName = true;
		}
		str = m_strFullName;

	} catch (...) {
		m_fHasFullName = false;
		return false;
	}
	return true;
}

bool CPropertyName::GetFullName (LPSTR pBuffer, WORD wLen)
{
string str;

	if (!GetFullName (str))		
		return false;

unsigned int iLen = min ((unsigned int)(wLen-1), str.length());

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
		_ASSERTE(UNKNOWN_ROOT != rgType && OBJPROP_ROOT != rgType && CLSPROP_ROOT != rgType);
		break;
	}
	return false;
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
		m_fHasFullName = false;

	} catch (...) {
		return false;
	}
	return true;
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

		m_fHasFullName = false;
	
	} catch (...) {
		return false;
	}
	return true;
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

		m_fHasFullName = false;

	} catch (...) {
		return false;
	}
	return true;
}

bool CPropertyName::operator== (CPropertyName const &rP) const 
{
	return 0 == Compare(*this, rP) ? true : false;
}

bool CPropertyName::operator< (CPropertyName const &rP) const
{
	return Compare(*this, rP) < 0 ? true : false;
}

int Compare (CPropertyName const &rP1, CPropertyName const &rP2) 
{
// Bezeichner vergleichen
int iCmp = strcmp (rP1.GetCompareName().c_str(), rP2.GetCompareName().c_str());

	if (iCmp != 0) 
		return iCmp;

// Bezeichner sind identisch, Gruppen vergleichen
	if (rP1.hasGroup() && rP2.hasGroup()) {
		if (iCmp = strcmp (rP1.GetGroup().c_str(), rP2.GetGroup().c_str()))
			return iCmp;
	}

// bereits im CompareName enthalten
//	if (rP1.hasSubGroup() && rP2.hasSubGroup()) {
//		if (iCmp = strcmp (rP1.GetSubGroup().c_str(), rP2.GetSubGroup().c_str()))
//			return iCmp;
//	}

// Typen vergleichen
	if (rP1.GetType() < rP2.GetType())
		return -1;
	if (rP1.GetType() > rP2.GetType())
		return 1;

	return 0;	// alles identisch
}

