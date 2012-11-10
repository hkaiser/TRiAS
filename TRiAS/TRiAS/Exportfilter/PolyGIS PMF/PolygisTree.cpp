// KlassenBaum -------------------------------------------------------------
// File: PolygisTree.CPP

#include "stdafx.h"

#include "PolygisTree.hxx"


char TRiTyp [7][2] = {"P","K","K","T","M","L","F"};


//#pragma warning (disable: 4355)


////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OBJ ------------------------------------------------
TR_OBJ :: TR_OBJ (long lIdent, const char *pKurzText , short iTyp)

{

	_lIdent = 0L;
	_pKurzText = NULL;
	_pRefText = NULL;
	_lIdent = lIdent;

	for ( short i = 0; i < 4; i++)
		_iTyp[i] = 0;

	_iFirstTyp = -1;

	if ( pKurzText && *pKurzText != '\0') {
		_pKurzText = new char [_MAX_PATH];
		if ( _pKurzText)
			strcpy(_pKurzText,pKurzText);

		_pRefText = new char [_MAX_PATH];
		if ( _pRefText)
			strcpy(_pRefText,pKurzText);

	}

	_iFirstTyp = iTyp;
	_iTyp[iTyp] = 1;

}

TR_OBJ :: ~TR_OBJ (void) {
	DELETE_OBJ ( _pRefText);
	DELETE_OBJ ( _pKurzText);
}

void TR_OBJ :: SetTyp( short iTyp)
{
	if (_iFirstTyp < 0)
		_iFirstTyp = iTyp;
	_iTyp[iTyp] = 1;
}
/////////////////////////////////////////////////////////////////
char * TR_OBJ :: GetLayerText(short iTyp)
{
	if ( iTyp == _iFirstTyp)
		return NULL;

	if ( _pRefText)
		DELETE_OBJ(_pRefText);

	if ( !_pRefText) {
		_pRefText = new char [_MAX_PATH];

		if ( _pRefText) {
			*_pRefText = '\0';

			strcat(_pRefText,_pKurzText);
			strcat(_pRefText,"_");
			strcat(_pRefText,TRiTyp[iTyp]);
		}
	}

	return _pRefText;
}

//////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// Memberfunktionen für TR_OCLTree ---------------------------------
TR_OBJTree :: TR_OBJTree (void) 
	 : CTree (GetObject, CmpObjects)
{
	// nothing else to do
}

TR_OBJTree :: ~TR_OBJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OBJTree :: UserDelete (void *pObj) 
{
	((TR_OBJ *)pObj) -> TR_OBJ :: ~TR_OBJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetObject (void *pObj) 
{
	return (void*)& (((TR_OBJ *)pObj) -> Ident());
}

int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2) 
{
long l1 = ((TR_OBJ *)pObj1) -> Ident();
long l2 = ((TR_OBJ *)pObj2) -> Ident();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//////////