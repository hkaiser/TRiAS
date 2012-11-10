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
	string m_strGroup;
	string m_strName;
	PROPTYPE m_rgType;

protected:
	bool ParseName (LPCSTR pcName);

public:
		CPropertyName (void);
		CPropertyName (LPCSTR pcFullName);
		CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, LPCSTR pcName);
		~CPropertyName (void) {}

inline	PROPTYPE GetType (void) { return m_rgType; }
inline	string &GetGroup (void) { return m_strGroup; }
inline	string &GetName (void) { return m_strName; }

	bool GetFullName (string &);
	bool GetFullName (LPSTR pBuffer, WORD wLen);
	bool SetType (PROPTYPE rgType);
	bool SetGroup (LPCSTR pcGroup);
	bool SetName (LPCSTR pcName);

	bool operator== (CPropertyName &rP);

friend	int Compare (CPropertyName &rP1, CPropertyName &rP2);
};


#endif // _PROPNAME_HXX
