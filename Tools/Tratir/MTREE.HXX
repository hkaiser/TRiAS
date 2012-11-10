// Klassendefinitionen fuer MerkmalsBaum, der Merkmale enthaelt, 
// die angehaengt werden sollen
// File: MTREE.HXX

#if !defined(_MTREE_HXX)
#define _MTREE_HXX

// Klasse, die in MTree reingehÑngt wird --------------------------------------
// Beschreibt ein Merkmal, welches zusÑtzlich in das DIRIASC-File mit 
// aufgenommen werden soll
class MInfo {
private:
	long _MCode;		// MerkmalsCode
	short _MTyp;		// MerkmalsTyp 'A', 'I' oder 'F'
	char *_pUIdent;		// SchlÅssel: Unique Ident
	char *_pMText;		// MerkmalsText

public:
		MInfo (char *pUIdent, long MCode, char *pMText, short MTyp);
		~MInfo (void);

friend void *GetUIdent (void *pObj);

	long GetMCode (void) { return _MCode; }
	short GetMTyp (void) { return _MTyp; }
	char *&GetMText (void) const { return (char *&)_pMText; }	
	char *&UIdent (void) const { return (char *&)_pUIdent; }
};


class MTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		MTree (void);
		~MTree (void);
};
DeclareLock (MTree, MInfo);

#endif // _MTREE_HXX
