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
	os_string m_strGroup;
	os_string m_strSubGroup;
	os_string m_strName;
	PROPTYPE m_rgType;

protected:
	bool ParseName (LPCSTR pcName);

public:
		CPropertyName (void);
		CPropertyName (LPCSTR pcFullName);
		CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, 
					   LPCSTR pcSubGroup, LPCSTR pcName);
		~CPropertyName (void) {}

inline	PROPTYPE GetType (void) { return m_rgType; }
inline	os_string &GetGroup (void) { return m_strGroup; }
inline	os_string &GetSubGroup (void) { return m_strSubGroup; }
inline	os_string &GetName (void) { return m_strName; }

	bool GetFullName (os_string &);
	bool SetType (PROPTYPE rgType);
	bool SetGroup (LPCSTR pcGroup);
	bool SetSubGroup (LPCSTR pcSubGroup);
	bool SetName (LPCSTR pcName);

	bool operator== (CPropertyName &rP);

friend	int Compare (CPropertyName &rP1, CPropertyName &rP2);
};


#endif // _PROPNAME_HXX
