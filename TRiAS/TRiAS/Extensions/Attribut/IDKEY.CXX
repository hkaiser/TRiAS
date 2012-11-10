// Einlesen einer Datei, die Idents bzw. MKode definiert
// File: IDKEY.CXX

#include "attribp.hxx"
#include <shellapi.h>
#include <igeometr.hxx>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include "attribut.h"
#include "define.h"   
#include "stohwnd.hxx"
#include "idkey.hxx"
#include "objkey.hxx"  
#include "clstree.hxx"
#include "attribut.hxx"


// Member für Klasse IDM ------------------------------------------------------
IDM :: IDM (long Ident , short iTyp)

{
	_lIdent = Ident;
	_pText = NULL;
	_iTyp = _iRTyp = _iModus = 0;
	if ( iTyp )
		_iTyp = _iTyp | iTyp;
	
}
void IDM :: SetText ( char *pText)
{
	if ( pText ) {
		if ( _pText)
			DELETE ( _pText);
		_pText = StrDuplicat( pText);
	}
}
void IDM :: SetGiTyp ( short iTyp)
{
	if ( iTyp )
		_iTyp = _iTyp | iTyp;
}

void IDM :: SetTyp ( short iTyp)
{
	if ( iTyp )
		_iRTyp = _iRTyp | iTyp;
}

void IDM :: SetModus ( short iModus)
{
	if ( iModus > -1 )
		_iModus = iModus;
}

void IDM :: SetTypZero ( void )
{
	_iRTyp = 0;
}

IDM :: ~IDM (void) {
	DELETE (_pText);
}

// Memberfunktionen für IDMTree -----------------------------------------------
IDMTree :: IDMTree (void) 
	 : CTree (GetIdent, CmpIdents)
{
	// nothing else to do
}

IDMTree :: ~IDMTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT IDMTree :: UserDelete (void *pObj) 
{
	((IDM *)pObj) -> IDM :: ~IDM();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetIdent (void *pObj) 
{
	return (void*)& (((IDM *)pObj) -> Ident());
}

int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2) 
{
long l1 = ((IDM *)pObj1) -> Ident();
long l2 = ((IDM *)pObj2) -> Ident();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//-------------------------------------------------------------
char *StrDuplicat ( char *cptr ) 
{
char *newPtr = NULL;

	if (cptr != NULL) {
		newPtr = new char [strlen(cptr)+1];
		if (newPtr != NULL) 
			strcpy (newPtr, cptr);

	}

return newPtr;
}

// File: IDKEY.CXX
