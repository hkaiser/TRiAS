// DatenStrukturen fuer GETRCODE.CXX
// File: GETRCODE.HXX

#if !defined(_GETRCODE_HXX)
#define _GETRCODE_HXX

// Funktionsprototypen --------------------------------------------------------
class RCodes;
class ObjRelFeld;

ErrCode GetRelationsCodes (HPROJECT hPr, long ONr, RCodes &RelC, short iMaske = OUREL|GREL|BRELAP);
ErrCode GetRelation (HPROJECT hPr, long ONr, long RelCode, ObjFeld &OF);
_TRIAS02_ENTRY ErrCode EXPORT02 RetrieveORCode (HPROJECT hPr, INT_PTR ONr, INT_PTR &RCode);

ErrCode DelRelationCode (HPROJECT hPr, long ONr, ObjRelFeld &OF);


// Klassendefinitionen --------------------------------------------------------
class RCode {
private:
	long _RelCode;		// RelationsCode
	short _RelTyp;		// RelationsTyp

public:
// Konstruktor
		RCode (long RelCode, short RTyp);
		RCode (RCode &RelC);

		~RCode (void) {}

	long RelCode (void) { return _RelCode; }
	short RelTyp (void) { return _RelTyp; }
};

// Zugriffsfunktionen für RCodes ----------------------------------------------
inline void *GetRelCode (void *pObj) { return pObj; }

inline int CmpRelCode (void *pObj1, void *pObj2) 
{
int Result;
long RCode1 = ((RCode *)pObj1) -> RelCode();
long RCode2 = ((RCode *)pObj2) -> RelCode();

	if (RCode1 > RCode2) Result = 1;
	else if (RCode1 < RCode2) Result = -1;
	else Result = 0;

return Result;
}	


// BaumStruktur, die RCode-Elemente enthält -----------------------------------
class RCodes : public CTree {
protected:
	void UserDelete (void *pObj) { ((RCode *)pObj) -> /*RCode :: */ ~RCode (); }

public:
// Konstruktor
		RCodes (void) : CTree (GetRelCode, CmpRelCode) {}
		~RCodes (void) { EveryDelete(); }
};
DeclareLock (RCodes, RCode);

#endif // _GETRCODE_HXX
