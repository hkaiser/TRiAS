// Liste aller zu einem Objekt gehoerenden Merkmale ---------------------------
// File: OBJMLIST.HXX

#if !defined(_OBJMLIST_HXX)
#define _OBJMLIST_HXX

class ObjMerkmal {
	long _lMCode;
	char *_pMText;
	short _iSelected;

public:
		ObjMerkmal (long MCode, char *pMText);
		~ObjMerkmal (void);

	long & MCode (void) { return _lMCode; }
	char *& pMText (void) { return _pMText; }
	short &isSelected (void) { return _iSelected; }

	void ResetMWert (void);

friend void *GetMCodeKey (void *);
friend int LongCmp (void *, void *);
};


class ObjMerkmalsListe : public CTree {
private:
	long _lONr;

protected:
	void UserDelete (void *);

public:
		ObjMerkmalsListe (long lONr = -1L);
		~ObjMerkmalsListe (void);

	long lONr (void) { return _lONr; }

	void SetSelection (long lMCode = -1L);
	void ResetSelection (void);
	void SelectAll (void) { SetSelection(); }
};
DeclareLock (ObjMerkmalsListe, ObjMerkmal);

#endif 	// _OBJMLIST_HXX
