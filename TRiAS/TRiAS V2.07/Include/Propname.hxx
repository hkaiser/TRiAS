// Klasse, die einen vollständigen Property-Namen behandeln kann --------------
// File: PROPNAME.HXX

#if !defined(_PROPNAME_HXX)
#define _PROPNAME_HXX

typedef enum tagPROPTYPE {
	UNKNOWN_ROOT = 0,
	OBJPROP_ROOT = 1,
	CLSPROP_ROOT = 2,
} PROPTYPE;

class CPropertyName {
private:
	PROPTYPE m_rgType;
	string m_strGroup;
	string m_strSubGroup;
	string m_strName;

	bool m_fhasGroup;
	bool m_fhasSubGroup;

protected:
	bool ParseName (LPCSTR pcName);

public:
	_TRIAS03_ENTRY CPropertyName (void);
	_TRIAS03_ENTRY CPropertyName (LPCSTR pcFullName);
	_TRIAS03_ENTRY CPropertyName (IObjectProperty *pIObjProp);
	_TRIAS03_ENTRY CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, 
					   LPCSTR pcSubGroup, LPCSTR pcName);
	inline ~CPropertyName (void) {}

inline	PROPTYPE GetType (void) { return m_rgType; }
inline	string &GetGroup (void) { return m_strGroup; }
inline	string &GetSubGroup (void) { return m_strSubGroup; }
inline	string &GetName (void) { return m_strName; }

inline bool hasGroup() { return m_fhasGroup ? true : false; }
inline bool hasSubGroup() { return m_fhasSubGroup ? true : false; }

_TRIAS03_ENTRY bool GetFullName (string &);
_TRIAS03_ENTRY bool GetFullName (LPSTR pBuffer, WORD wLen);
_TRIAS03_ENTRY bool SetType (PROPTYPE rgType);
_TRIAS03_ENTRY bool SetGroup (LPCSTR pcGroup);
_TRIAS03_ENTRY bool SetSubGroup (LPCSTR pcGroup);
_TRIAS03_ENTRY bool SetName (LPCSTR pcName);

_TRIAS03_ENTRY bool operator== (CPropertyName &rP);

friend _TRIAS03_ENTRY int Compare (CPropertyName &rP1, CPropertyName &rP2);
};

#endif // _PROPNAME_HXX
