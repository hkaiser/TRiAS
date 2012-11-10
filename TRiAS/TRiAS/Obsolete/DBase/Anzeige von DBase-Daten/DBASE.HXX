/*------------------------------------------------------------------------

File: DBASE.HXX

DBASE - Interface
beinhaltet allgemeine Funktionen für die Arbeit mit dBase-Dateien.

Erarbeitet: J. Benkenstein					  begonnen am: 16. Sept. 1992
----------------------------------------------------------------------------*/

#ifndef _DBASE_HXX
#define _DBASE_HXX

class CodeBase;
class ShowFile;

class dBaseDispatch : public CListContainer {
private:
// Attribute
		CodeBase *_pCB;
		pWindow _pW;					
		HWND _hWnd;			 // ORFenster, für welches dieser Dispatcher
								// zuständig ist
		long _lActObj;		  // BezugsObjekt
		
protected:
		void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		dBaseDispatch (pWindow pParent, long ActObj);
		~dBaseDispatch (void);

// sonst. Member
		ErrCode ShowDBaseWindowField (char *pDBaseName, char *pFieldName,
									  char *pValue, ResourceFile *pRF,
									  short Type);
		void DeleteOldWindows (void);		 
		
		HWND &hWnd (void) { return _hWnd; }	
		long ActObj (void) { return _lActObj; }
		
friend void *RetrievehWnd (void *pObj);
friend int CmphWnd (void *pKey1, void *pKey2);
};
DeclareLock (dBaseDispatch, ShowFile);

//
// Die Klasse DBaseDispatchTree verwaltet die DBaseDispatcher aller offenen
// ObjektrechercheFenster. Jedes dieser ObjektRechercheFenster verwaltet die
// für ein Objekt eröffneten DBaseFenster in einem dieser DDaseDispatcher.
// Der ZugriffsSchlüssel auf die DBaseDispatcher ist das FensterHandle des 
// ObjektRechercheFensters.
//
class DBaseDispatchTree : public CTree {
protected:
		void UserDelete (void *pObj);

public:
				DBaseDispatchTree (void);
				~DBaseDispatchTree (void);
				
		void AllDelete (HWND hWnd);
		ErrCode ShowDBaseWindowField (HWND hWnd, 
									  char *pDBaseName, char *pFieldName,
									  char *pValue, ResourceFile *pRF, short ParamType);
									  
		long ActObj (HWND);								   
};
DeclareLock (DBaseDispatchTree, dBaseDispatch);

#endif // _DBASE_HXX
