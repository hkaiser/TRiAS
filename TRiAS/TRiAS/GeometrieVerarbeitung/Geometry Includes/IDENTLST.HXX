// Liste aller Identifikatoren einer PBD
// File :: IDENTLST.HXX
// H. Kaiser

#if !defined(_IDENTLST_HXX)
#define _IDENTLST_HXX

class IdentListEntry {
private:
	ulong _ulIdent;
	char *_pKText;
	
public:
		IdentListEntry (ulong ulIdent, char *pKText);
		~IdentListEntry (void);

	long Ident (void) { return _ulIdent; }
	char *& KText (void) const { return (char *&)_pKText; }

friend int ULongCmp (void *, void *);
friend void *GetIdentKey (void *);
};

extern "C" {

	BOOL _XTENSN_EXPORT FAR PASCAL FillIdentsList (ulong, BOOL, void *);
}                                                         

// Baum enthält alle Identifikatoren einer PBD
class _GEOMETR_ENTRY IdentList : public COptTree {
protected:
	void UserDelete (void *pObj);
	
	bool AddIdent (ulong ulIdent, char *pDesc);

public:
		IdentList (void);
		~IdentList (void);
		
	bool UpdateEntry (ulong ulIdent);

friend BOOL _XTENSN_EXPORT PASCAL FillIdentsList (ulong, BOOL, void *);
};

	DeclareOptLock (IdentList, IdentListEntry);

#endif // _IDENTLST_HXX
