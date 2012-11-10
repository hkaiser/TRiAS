// Konkreter StringEnumerator (DateiNamen) ------------------------------------
// File: ENUMFNAM.HXX

#if !defined(_ENUMFNAM_HXX)
#define _ENUMFNAM_HXX

// Enumeration aller FileNamen, die in einer OpenFileBox eingegeben wurden
class CEnumFileNames : public CImpIEnumStrings {
public:
		CEnumFileNames (void);
		~CEnumFileNames (void);
		
	bool Init (char *pDesc, DWORD dwFlags);	// Initialisieren

static CEnumFileNames *CreateInstance (char *pInit, DWORD dwFlags);
};

#endif // _ENUMFNAM_HXX
