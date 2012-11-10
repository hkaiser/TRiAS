///////////////////////////////////////////////////////////////////////////
// @doc 
// @module PROPNAME.HXX | Klasse, die einen vollständigen Property-Namen behandeln kann

#if !defined(_PROPNAME_HXX__B22F49A7_1833_11D2_9E90_006008447800__INCLUDED_)
#define _PROPNAME_HXX__B22F49A7_1833_11D2_9E90_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef enum tagPROPTYPE {
	UNKNOWN_ROOT = 0,
	OBJPROP_ROOT = 1,
	CLSPROP_ROOT = 2,
} PROPTYPE;

class CPropertyName 
{
private:
	PROPTYPE m_rgType;
	string m_strGroup;
	string m_strSubGroup;
	string m_strName;
	string m_strFullName;

	bool m_fhasGroup;
	bool m_fhasSubGroup;
	bool m_fHasFullName;

protected:
	bool ParseName (LPCSTR pcName);

public:
	_TRIAS03_ENTRY CPropertyName (void);
	_TRIAS03_ENTRY CPropertyName (PROPTYPE rgType);
	_TRIAS03_ENTRY CPropertyName (LPCSTR pcFullName);
	_TRIAS03_ENTRY CPropertyName (IObjectProperty *pIObjProp);
	_TRIAS03_ENTRY CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, 
					   LPCSTR pcSubGroup, LPCSTR pcName);
	inline ~CPropertyName (void) {}

inline PROPTYPE GetType (void) const { return m_rgType; }
inline string const &GetGroup (void) const { return m_strGroup; }
inline string const &GetSubGroup (void) const { return m_strSubGroup; }
inline string const &GetName (void) const { return m_strName; }
inline string GetCompareName() const 
	{
		if (m_fhasSubGroup)
			return m_strSubGroup + '\\' + m_strName;
		return m_strName;
	}

inline bool hasGroup() const { return m_fhasGroup ? true : false; }
inline bool hasSubGroup() const { return m_fhasSubGroup ? true : false; }

_TRIAS03_ENTRY bool GetFullName (string &);
_TRIAS03_ENTRY bool GetFullName (LPSTR pBuffer, WORD wLen);
_TRIAS03_ENTRY bool SetType (PROPTYPE rgType);
_TRIAS03_ENTRY bool SetGroup (LPCSTR pcGroup);
_TRIAS03_ENTRY bool SetSubGroup (LPCSTR pcGroup);
_TRIAS03_ENTRY bool SetName (LPCSTR pcName);

_TRIAS03_ENTRY bool operator== (CPropertyName const &rP) const;
_TRIAS03_ENTRY bool operator< (CPropertyName const &rP) const;

friend _TRIAS03_ENTRY int Compare (CPropertyName const &rP1, CPropertyName const &rP2);
};

#endif // !defined(_PROPNAME_HXX__B22F49A7_1833_11D2_9E90_006008447800__INCLUDED_)
