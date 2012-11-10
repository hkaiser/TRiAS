// Klasse, die einen vollständigen Property-Namen behandeln kann --------------
// File: PROPNAME.CXX

#include "featurep.hxx"

#include "propname.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPropertyName :: CPropertyName (void)
{
	m_rgType = UNKNOWN_ROOT;
}

CPropertyName :: CPropertyName (LPCSTR pcFullName)
{
	ParseName (pcFullName);
}

CPropertyName :: CPropertyName (PROPTYPE rgType, 
		LPCSTR pcGroup, LPCSTR pcSubGroup, LPCSTR pcName)
	       : m_rgType(rgType)
{
	try {
		m_strGroup = pcGroup;
		m_strName = pcName;

		if (pcSubGroup) m_strSubGroup = pcSubGroup;
	} catch (...) {
		TX_ASSERT(false);
		m_rgType = UNKNOWN_ROOT;
	}
}

bool CPropertyName :: ParseName (LPCSTR pcName)
{
	try {
	os_string str = pcName;
	size_t pos = str.find ("\\");

		m_rgType = UNKNOWN_ROOT;
		if (NPOS == pos) throw false;

	// Wurzel feststellen
	os_string sstr = str.substr (0, pos);
	 
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

		size_t posn2 = str.find ("\\", posn+1);

			if (NPOS == posn2) 
				m_strName = str.substr (posn+1);
			else {
				m_strSubGroup = str.substr (posn+1, posn2-posn-1);
				m_strName = str.substr (posn2+1);
			}
		}
		return true;
	} catch (...) {
		TX_ASSERT(false);
		m_rgType = UNKNOWN_ROOT;
		return false;
	}
}


bool CPropertyName :: GetFullName (os_string &str)
{
	if (UNKNOWN_ROOT == m_rgType)
		return false;

	try {
		if (0 < m_strGroup.size()) {
			str = (OBJPROP_ROOT == m_rgType) ? 
					"OBJPROP_ROOT\\" : 
					"CLSPROP_ROOT\\";
			str += m_strGroup;
			str += "\\";
			if (0 != m_strSubGroup.length()) {
				str += m_strSubGroup;
				str += "\\";
			}
			str += m_strName;
		} else
			str = m_strName;
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}
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
	try {
		m_strGroup = pcGroup;
		return true;
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}
}

bool CPropertyName :: SetSubGroup (LPCSTR pcSubGroup)
{
	try {
		m_strSubGroup = pcSubGroup;
		return true;
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}
}

bool CPropertyName :: SetName (LPCSTR pcName)
{
	try {
		m_strName = pcName;
		return true;
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}
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
	if (rP1.GetGroup() < rP2.GetGroup())
		return -1;
	if (rP1.GetGroup() > rP2.GetGroup())
		return 1;

// SubGruppen vergleichen
	if (rP1.GetSubGroup() < rP2.GetSubGroup())
		return -1;
	if (rP1.GetSubGroup() > rP2.GetSubGroup())
		return 1;

// Gruppen sind auch gleich, also an Hand der Namen entscheiden
	if (rP1.GetName() < rP2.GetName())
		return -1;
	if (rP1.GetName() > rP2.GetName())
		return 1;

return 0;	// sind wohl identisch
}

