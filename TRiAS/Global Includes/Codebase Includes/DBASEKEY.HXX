// Spezielles YACC-Stack-Elemente, welches DBaseKeyAnkopplung realiseren
// File: DBASEKEY.HXX


#if !defined(_DBASEKEY_HXX)
#define _DBASEKEY_HXX

#ifndef NODBASEKEY
enum DBaseKeyType { 
	DBUnknown = -1, 
	DBField = 0, DBCode = 1, DBParameter = 2, 
	DBTag = 4, DBTagCode = 5, DBTagParameter = 6,
};

class DBaseKey {
protected:         
	Bool _bOnlyExpr;
	char *_DBaseKeyString;		// eigentliche Information
        long _DBaseKeyLong;
	DBaseKeyType _DBKType;

public:
// Konstruktor
		DBaseKey (DBaseKeyType, char *, BOOL bOnlyExpr = FALSE); // direkter Feldname oder TagName
		DBaseKey (DBaseKeyType, long, BOOL bOnlyExpr = FALSE);	 // MKode oder Parameter
		DBaseKey (DBaseKey &);

		~DBaseKey (void);

	long DBaseKeyLong (void) { return _DBaseKeyLong; }
	char *DBaseKeyName (void) { return _DBaseKeyString; }
	DBaseKeyType isA (void) { return _DBKType; }
	BOOL OnlyExpression (void) { return _bOnlyExpr; }

	operator char * (void) { return _DBaseKeyString; }
};
#endif

#ifndef NOGOEDBKEY
enum GeoDBKeyType { DBKUnknown, DBKCode, DBKParameter, };

class GeoDBKey {
protected:
	long _GeoDBKeyLong;
	GeoDBKeyType _GDKType;

public:
// Konstruktor
		GeoDBKey (GeoDBKeyType, long);	 // MKode oder Parameter
		GeoDBKey (GeoDBKey &);
		~GeoDBKey (void) {}

	long GeoDBKeyLong (void) { return _GeoDBKeyLong; }
	GeoDBKeyType isA (void) { return _GDKType; }
};
#endif

#ifndef NOKEYFILTER
class KeyFilter {
private:
	E4EXPORT_FCT friend Bool DetectTag (char *, Bool = False);

protected:
	GeoDBKey *_pGDBK;
	DBaseKey *_pDBK;
	Bool _isUnique;

public:
// Konstruktor
		KeyFilter (GeoDBKey *, DBaseKey *, Bool);
		KeyFilter (DBaseKey *, Bool);		
		~KeyFilter (void);

	Bool isUnique (void) { return _isUnique; }
        Bool hasTag (long, int, long *, char **);
        char *FieldName (long, int, long *, char **);
        char *FieldValue (long, int, long *, char **);
        char *TagName (long, int, long *, char **);
        char *KeyValue (long, int, long *, char **);
	GeoDBKey & GeoDBkey (void) { return *_pGDBK; }
	DBaseKey & DBasekey (void) { return *_pDBK; }
};
#endif

#ifndef NOTERM
class StringTerm {
private:
	char *_pStr1;		// erstes String
	char *_pStr2;

protected:
		StringTerm (char *pS1, char *pS2);
		~StringTerm (void);

	char * &String1 (void) { return _pStr1; }
	char * &String2 (void) { return _pStr2; }	
};

class MasterTerm : public StringTerm {
public:
		MasterTerm (char *pMaster, char *pField)
			: StringTerm (pMaster, pField) {}
		~MasterTerm (void) {}

	char * &MasterDBName (void) { return String1(); }
	char * &MasterField (void) { return String2(); }
};

class SlaveTerm : public StringTerm {
public:
		SlaveTerm (char *pSlave, char *pTag) 
			: StringTerm (pSlave, pTag) {}
		~SlaveTerm (void) {}

	char * &SlaveDBName (void) { return String1(); }
	char * &SlaveTag (void) { return String2(); }
};
#endif

#endif // _DBASEKEY_HXX
