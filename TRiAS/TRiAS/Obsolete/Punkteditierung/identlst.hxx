// Liste aller Identifikatoren einer PBD --------------------------------------
// File :: IDENTLST.HXX

#if !defined(_IDENTLST_HXX)
#define _IDENTLST_HXX

class IdentListEntry {
private:
	long _Ident;
	char *_pKText;
	
public:
		IdentListEntry (long Ident, char *pKText);
		~IdentListEntry (void);

	long Ident (void) { return _Ident; }
	char *& KText (void) const { return (char *&)_pKText; }

friend int ULongCmp (void *, void *);
friend void *GetIdentKey (void *);
};

extern "C" 
BOOL _XTENSN_ENTRY FAR PASCAL FillIdentsList (long, BOOL, void *);

// Baum enthält alle Identifikatoren einer PBD
class IdentList : public CTree {
protected:
	void UserDelete (void *pObj);
	
	Bool AddIdent (long Ident, char *pDesc);

public:
		IdentList (void);
		~IdentList (void);
		
	Bool UpdateEntry (long Ident);

friend BOOL _XTENSN_ENTRY PASCAL FillIdentsList (long, BOOL, void *);
};
DeclareLock (IdentList, IdentListEntry);

#endif // _IDENTLST_HXX
