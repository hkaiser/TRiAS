// ----------------Auswahl der Attributverarbeitung -----------------------------
// File: AUSWAHL.CXX

#include "attribp.hxx"

#include <igeometr.hxx>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "attribut.h" 
#include "about.h"
#include "define.h"
#include "about.hxx"
#include "idkey.hxx"
#include "objkey.hxx" 
#include "clstree.hxx"
#include "stohwnd.hxx"
//#include "attinfo.hxx"
#include "attribut.hxx"
#include "auswahl.hxx"

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ObjClassAuswahl :: ObjClassAuswahl (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDLB_AUSWOBJCLASS),
	       _MClass ( this, IDLB_AUSWMCLASS),
	       _MCDelete (this, IDB_AUSWDELETE),
	       _MCModify (this, IDB_AUSWMODIFY),
	       _MCVergleich (this, IDB_AUSWVERGLEICH),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
	pW->Disable();
	OKButton.Disable();
	_MCDelete.Disable();
	_MCModify.Disable();
	_MCVergleich.Disable();
	_pIDM = pIDM;
	CEierUhr Wait(_pW);
	_pMCode = NULL;
	_IDFlag = false;
	_MCFlag = false;

	if ( !FillObjClassList())
		return;
	if ( !FillMClassList())
		return;
	return;
}

#pragma warning (default: 4355)


ObjClassAuswahl :: ~ObjClassAuswahl (void)
{
	_pW->Enable();
}

void _XTENSN_EXPORT ObjClassAuswahl :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_AUSWOBJCLASS:
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
			_MCDelete.Enable();
			_MCModify.Enable();
			_MCVergleich.Enable();
		}
		}
		break;

	case IDLB_AUSWMCLASS:
		{
		int iIndex = _MClass.GetFirstSelected();
		if ( iIndex == -1 ) {
			_MCFlag = false;
			return;
		}

		int Count = _MClass.GetCount();
		short Number = 0;
		if (_pMCode)
			DELETE ( _pMCode);

		_pMCode = new long [ Count +1];
		if ( !_pMCode )
			return;
	
		long Key = GetMCode ( iIndex );
		_MCFlag = true;
		Number++;
		*(_pMCode+Number) = Key;
		iIndex=_MClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			Key = GetMCode ( iIndex );
			Number++;
			*(_pMCode+Number) = Key;

			iIndex=_MClass.GetNextSelected ();

		}
		*_pMCode = (long) Number;

		if ( _IDFlag && _MCFlag ) {
			OKButton.Enable();
			_MCDelete.Enable();
			_MCModify.Enable();
			_MCVergleich.Enable();
		}
		}
		break;
	}
	return;
}
//----------------------------------------------------------------------
//
Bool ObjClassAuswahl :: FillMClassList ( void )
{
	
// ------------MerkmalListBox füllen

ENUMNOKEY ENK;

	ENK.eFcn = ( ENUMNOKEYPROC) FillMKListBox;
	ENK.ePtr = &_MClass;
	
	DEX_EnumMCodes(ENK);

	return true;
}
//----------------------------------------------------------------

void _XTENSN_EXPORT ObjClassAuswahl :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

		case IDB_AUSWDELETE:
		{
		EndDlg (-1);
		}
		break;

		case IDB_AUSWMODIFY:
		{
		EndDlg (-2);
		}
		break;

		case IDB_AUSWVERGLEICH:
		{
		EndDlg (-3);
		}
		break;
	}
	return;
}
//Member

//-------------------------------------------------------------------
Bool ObjClassAuswahl :: FillObjClassList ( void )
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
long ObjClassAuswahl :: GetIdent ( int iIndex , short *Typ)
{
char * pBuff = new char [_MAX_PATH];
*Typ = 0;
	if ( pBuff == NULL ) 
		return 0;
	_ObjClass.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';
	long Ident;

	ulong uIdent;
	IdentFromClassX ( pBuff, &uIdent);
	Ident = (long)uIdent;

/*----------23.1.97
	if ( DEX_GetIdBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);
---------*/

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
long ObjClassAuswahl :: GetMCode ( int iIndex )
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
//------------------------------------------------------------------------
extern "C" Bool PASCAL _XTENSN_EXPORT StoreIdentWithTyp (long Ident, DWORD Typ , void *pData)
{

	CTable t(*( IDMTree * )pData);
	if ( !t.Find (&Ident) ) {
		short Type = (short) Typ;
		IDMCreator IDMCr ( * (IDMTree * )pData );
		ContCreate ( IDMCr, IDM ) ( Ident , Type);
	}

	return TRUE;

}

//----------------------AUSWAHL.CXX-------------------------------------
