// ----------------Aufbau neuer Attribute -----------------------------
// File: BILDEN.CXX

#include "attribp.hxx"

#include <triastlb_i.c>
#include <triastlb.h>

#include <oleguid.h>
#include <dirisole.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>
#include <igeometr.hxx>

#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>

#include <igeometr.hxx>


#include "attribut.h" 
#include "about.h"
#include "define.h"
#include "about.hxx"
#include "idkey.hxx"
#include "objkey.hxx"
#include "clstree.hxx"
#include "stohwnd.hxx"
#include "attribut.hxx"
#include "bilden.hxx"

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

CreateFeature :: CreateFeature (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDLB_CFOBJCLASS),
	       _MClass ( this, IDLB_CFMCLASS),
	       _NewM ( this, IDS_CFNEWTEXT),
	       _Anhang ( this, IDB_CFANHANG),
	       _Vorsatz ( this, IDB_CFVORSATZ),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	OKButton.Disable();
	_pIDM = pIDM;
	CEierUhr Wait(_pW);
	_IDFlag = false;
	_MCFlag = false;
	_pMCode = NULL;
	_NewM.SetText(NULL);
	_pText = NULL;
	_pText = new char [_MAX_PATH];
	if ( !_pText)
		return;

	if ( !FillObjClassList())
		return;
	if ( !FillMClassList())
		return;

	_Vorsatz.SetState(TRUE);
	_Anhang.SetState(FALSE);
	_isVorsatz = true;

	return;
}

#pragma warning (default: 4355)


CreateFeature :: ~CreateFeature (void)
{
//	_pW->Enable();
	DELETE (_pText);
}

void _XTENSN_EXPORT CreateFeature :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_CFOBJCLASS:
		{
		int iIndex = _ObjClass.GetFirstSelected();
		if ( iIndex == -1 ) {
			_IDFlag = false;
			return;
		}

		CTable t ( *_pIDM);
		for ( t.First(); t.Valid();t.Next()) {
			IDMLock l(t);
			l->SetTypZero();
		}
		short Typ;
		_IDFlag = true;
		long Key = GetIdent ( iIndex , &Typ);
		if ( t.Find ( &Key)) {
			IDMLock l(t);
  			l->SetTyp ( Typ);
		}
		iIndex=_ObjClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			IDMLock l(t);
			Key = GetIdent ( iIndex , &Typ);
			if ( t.Find ( &Key)) {
				IDMLock l(t);
	  			l->SetTyp ( Typ);
			}
			iIndex=_ObjClass.GetNextSelected ();
		}
		if ( _IDFlag && _MCFlag ) {
			OKButton.Enable();
		}
		}
		break;

	case IDLB_CFMCLASS:
		{
		int iIndex = _MClass.GetCurrentIndex();
		if ( iIndex == -1 ) {
			_MCFlag = false;
			return;
		}

		long Key = GetMCode ( iIndex );
		if ( !_pMCode)
			_pMCode = new long [2];
		if ( !_pMCode)
			return;
		*_pMCode = 1L;
		*(_pMCode + 1) = Key;

		_MCFlag = true;

		if ( _IDFlag && _MCFlag ) {
			OKButton.Enable();
		}
		}
		break;
	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT CreateFeature :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		if ( _pMCode ) {
			_NewM.GetText ( _pText , _MAX_PATH );
			CTable t(*_pIDM);
			for ( t.First();t.Valid();t.Next() ) {
				IDMLock l(t);
				if ( _pText)
					l->SetText ( _pText);
			}
		}
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

		case IDB_CFANHANG :
		{
		_Vorsatz.SetState(FALSE);
		_Anhang.SetState(TRUE);
		_isVorsatz = false;
		}
		break;

		case IDB_CFVORSATZ :
		{
		_Vorsatz.SetState(TRUE);
		_Anhang.SetState(FALSE);
		_isVorsatz = true;
		}
		break;

	}
	return;
}
//Member

//-------------------------------------------------------------------
Bool CreateFeature :: FillObjClassList ( void )
{
	if ( !_pIDM )
		return false;

	CTable t ( *_pIDM);
	for ( t.First(); t.Valid(); t.Next() ) {
		IDMLock l(t);
		DWORD Type = (DWORD) l->GiTyp();
		GetIdentWithTyp ( l->Ident(), Type, &_ObjClass);
	}

	return true;
}
//----------------------------------------------------------------
//
Bool CreateFeature :: FillMClassList ( void )
{
	
// ------------MerkmalListBox füllen

ENUMNOKEY ENK;

	ENK.eFcn = ( ENUMNOKEYPROC) FillMKListBox;
	ENK.ePtr = &_MClass;
	
	DEX_EnumMCodes(ENK);

	return true;
}
//----------------------------------------------------------------
long CreateFeature :: GetIdent ( int iIndex , short *Typ)
{
char * pBuff = new char [_MAX_PATH];
*Typ = 0;
	if ( pBuff == NULL ) 
		return 0;
long Ident;
	_ObjClass.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';

	ulong uIdent;
	IdentFromClassX ( pBuff, &uIdent);
	Ident = (long)uIdent;

/*----------23.1.97
	if ( DEX_GetIdBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);
----------*/

	*ptr = ':';
	if ( *(ptr+1) == 'F' )
		*Typ = OTFlaeche;
	if ( *(ptr+1) == 'L' )
		*Typ = OTLinie;
	if ( *(ptr+1) == 'P' )
		*Typ = OTPunkt;
	if ( *(ptr+1) == 'T' )
		*Typ = OTText;

	DELETE ( pBuff);

	return Ident;	

}
//----------------------------------------------------------------
long CreateFeature :: GetMCode ( int iIndex )
{
char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return 0;
long Ident;
	_MClass.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';
	if ( DEX_GetMkBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);

	*ptr = ':';
	DELETE ( pBuff);

	return Ident;	

}

//------------------------------------------------------------------
//----------------------BILDEN.CXX-------------------------------------
