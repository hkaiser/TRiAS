// Klassendefinitionen fuer TPRJ-Baum ------------------------------------------
// File: MENUKEY.HXX

#if !defined(_MENUKEY_HXX)
#define _MENUKEY_HXX

class PROJ {
private: 
	char *_pProj;
	char *_pDBName;
	char *_pUserName;
	char *_pSightName;
	char *_pDrive;
	char *_pPath;
	char *_pExt;
	char *_pOwner;
	char *_pPrev;
	char *_pNext;
	short _iStatus;
	short _iLevel;
	short _iPrevMenuPoint;
	HMENU _hMenu;
	UINT _MenuID;
	long _lYmin;
	long _lXmin;
	long _lYmax;
	long _lXmax;
	class TPRJTree *_pTPRJ;

public:
// Konstruktor/Destruktor
		PROJ (char *pKey, struct DBPROJECT *p );

		~PROJ (void);

// ZugriffsFunktionen für Baum
friend void _XTENSN_EXPORT *GetProj (void *pProj);
friend int _XTENSN_EXPORT CmpProjs (void *pProj1, void *pProj2);
                                             
	char * Proj ( void ) { return _pProj; }
	char * Prev ( void ) { return _pPrev; };
	char * Next ( void ) { return _pNext; };
	char * DBName ( void ) { return _pDBName; };
	char * UserName ( void ) { return _pUserName; };
	char * SightName ( void ) { return _pSightName; };
	char * Path ( void ) { return _pPath; };
	char * Drive ( void ) { return _pDrive; };
	char * Ext ( void ) { return _pExt; };
	char * Owner ( void ) { return _pOwner; };
	short &Status ( void ) { return _iStatus; };
	short &Level ( void ) { return _iLevel; };
	short &PrevMenuPoint ( void ) { return _iPrevMenuPoint; };
	long &Xmin ( void ) { return _lXmin; };
	long &Xmax ( void ) { return _lXmax; };
	long &Ymin ( void ) { return _lYmin; };
	long &Ymax ( void ) { return _lYmax; };
	HMENU &hMenu ( void) { return _hMenu; };
	UINT &MenuID ( void) { return _MenuID; };
	TPRJTree *pTPRJ ( void ) { return _pTPRJ;};
	void StoreTProjects ( TPRJTree * );
	void DeleteTProjects ( void );
	void StoreTPMenu ( HMENU );
	void StoreMenuID ( UINT );
	void StoreSightName ( char * );
	void StorePreviousProject ( char * );
	void StoreOwner ( char * );


};

class PROJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		PROJTree (void);
		~PROJTree (void);
};
DeclareLock (PROJTree, PROJ);		// notwendige Klassendefinitionen
//-----------------------------------------------------------------------
class TPRJ {
private: 
	char *_pMenu;
	char *_pDBName;
	char *_pUserName;
	char *_pSightName;
	char *_pDrive;
	char *_pPath;
	char *_pExt;
	char *_pOwner;
	short _iStatus;
	short _iLevel;
	UINT _MenuID;
	long _lYmin;
	long _lXmin;
	long _lYmax;
	long _lXmax;

public:
// Konstruktor/Destruktor
		TPRJ (char *pKey, struct DBPROJECT *p );

		~TPRJ (void);

// ZugriffsFunktionen für Baum
friend void _XTENSN_EXPORT *GetMenu (void *pMenu);
friend int _XTENSN_EXPORT CmpMenus (void *pMenu1, void *pMenu2);
                                             
	char *Menu ( void ) { return _pMenu; };
	char * DBName ( void ) { return _pDBName; };
	char * SightName ( void ) { return _pSightName; };
	char * UserName ( void ) { return _pUserName; };
	char * Path ( void ) { return _pPath; };
	char * Drive ( void ) { return _pDrive; };
	char * Ext ( void ) { return _pExt; };
	char * Owner ( void ) { return _pOwner; };
	short &Level ( void ) { return _iLevel; };
	UINT &MenuID ( void) { return _MenuID; };
	long &Xmin ( void ) { return _lXmin; };
	long &Xmax ( void ) { return _lXmax; };
	long &Ymin ( void ) { return _lYmin; };
	long &Ymax ( void ) { return _lYmax; };
	void StoreSightName ( char * );
	void StoreMenuID ( UINT );
	void StoreNewTPAddress ( char *,char*,char*,char*);
};

class TPRJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TPRJTree (void);
		~TPRJTree (void);
};
DeclareLock (TPRJTree, TPRJ);		// notwendige Klassendefinitionen

//-----------------------------------------------------------------------
class MMenu {
private: 
	char *_pMenu;
	char *_pDBName;
	char *_pReferenz;
	short _iMenuNr;
	short _iStatus;
	short _iModKZ;

public:
// Konstruktor/Destruktor
		MMenu (char *pKey, struct MODMENU *p );

		~MMenu (void);

// ZugriffsFunktionen für Baum
friend void _XTENSN_EXPORT *GetMNr (void *pMenu);
friend int _XTENSN_EXPORT CmpMNrs (void *pMenu1, void *pMenu2);
                                             
	short &MenuNr ( void ) { return _iMenuNr; };
	char *Menu ( void ) { return _pMenu; };
	char * DBName ( void ) { return _pDBName; };
	char * Referenz ( void ) { return _pReferenz; };
	short &Status ( void ) { return _iStatus; };
	short &ModKZ ( void ) { return _iModKZ; };
	void StoreReferenz ( char *pProject, char *pReferenz);
};

class MMenuTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		MMenuTree (void);
		~MMenuTree (void);
};
DeclareLock (MMenuTree, MMenu);		// notwendige Klassendefinitionen

//-----------------------------------------------------------------------

#endif // _MENUKEY_HXX
