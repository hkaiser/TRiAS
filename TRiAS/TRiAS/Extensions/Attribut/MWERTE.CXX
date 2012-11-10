// ----------------Zuordnen von Attributwerten -----------------------------
// File: MWERTE.CXX

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
#include "txtedit.hxx"
#include "attribut.hxx"
#include "erben.hxx"
#include "mwerte.hxx"

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DefineMerkmalsWert :: DefineMerkmalsWert (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _MClass ( this, IDLB_ATTSELMCLASS),
	       _MWert (this,IDT_ATTMERKMALSWERT),
	       _StoreMWert (this, IDB_ATTSTOREMWERT),
	       _RechArt (this, IDCB_ATTSELMODUS),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{
	if ( !pIDM)
		return;
	_pText = new char [_MAX_PATH];
	if ( !_pText)
		return;
	
//	StartWerte
	_pW = pW;
	pW->Disable();
	_MWert.SetButton ( &_StoreMWert);
	_MWert.SetCombo ( &_RechArt);
	_MWert.SetTextLimit ( (uint)MAXKEY); 

	_MWert.SetText(NULL);
	_MWert.Disable();

	_pIDM = pIDM;

	_StoreMWert.Disable();
	_RechArt.Disable();

	CEierUhr Wait(_pW);
	if ( !FillMClassList())
		return;
	if ( !FillModusList())
		return;
	_lMCode = 0L;
	_iModus = -1;

	return;
}

#pragma warning (default: 4355)


DefineMerkmalsWert :: ~DefineMerkmalsWert (void)
{
	_pW->Enable();
	DELETE (_pText);
}

void _XTENSN_EXPORT DefineMerkmalsWert :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDCB_ATTSELMODUS:
		{
		if ( _lMCode == 0L)
			return;		// Kein Merkmal selektiert !!!

		int iIndex = _RechArt.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		if ( iIndex <= 1 )  {
			_RechArt.ChangeCurrentIndex ( 2 );	//DEFAULT
			iIndex = 2;
		}
		_iModus = iIndex;
		}
		break;

	case IDLB_ATTSELMCLASS:
		{
		int iIndex = _MClass.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		char * pBuffer = new char [_MAX_PATH];
		if ( !pBuffer ) 
			return;

		_MWert.Enable();
		_StoreMWert.Disable();
		_RechArt.Disable();
		_RechArt.ChangeCurrentIndex ( 0 );	//DEFAULT

		_MClass.GetCurrentString (pBuffer);

		char *ptr = strchr (pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE ( pBuffer);
			return;
		} else
			*ptr = '\0';

		if ( DEX_GetMkBase() == 16 )
			_lMCode = strtoul ( pBuffer, NULL, 16 );
		else
			_lMCode = atol(pBuffer);


		CTable t(*_pIDM);
		if ( t.Find( &_lMCode) ) {
			IDMLock l(t);
			if ( !l->Text() || *l->Text() == '\0')
				_MWert.SetText(NULL);
			else
				_MWert.SetText(l->Text ());

			_iModus = l->Modus();
			_RechArt.ChangeCurrentIndex ( _iModus );	//DEFAULT

		} else {
			_iModus = 0;
			_RechArt.ChangeCurrentIndex ( _iModus);	//DEFAULT
			_MWert.SetText(NULL);
		}
		if ( _iModus == 0)
			
		_MWert.SetFocus();

		DELETE ( pBuffer);

		}
		break;

	}
}
//-------------------------------------------------------------------

void _XTENSN_EXPORT DefineMerkmalsWert :: ListBoxClk (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_ATTSELMCLASS:
		{
		int iIndex = _MClass.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		char * pBuffer = new char [_MAX_PATH];
		if ( !pBuffer ) 
			return;

		_MWert.Enable();
		_StoreMWert.Disable();
		_MClass.GetCurrentString (pBuffer);

		char *ptr = strchr (pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE ( pBuffer);
			return;
		} else
			*ptr = '\0';

		if ( DEX_GetMkBase() == 16 )
			_lMCode = strtoul ( pBuffer, NULL, 16 );
		else
			_lMCode = atol(pBuffer);


		CTable t(*_pIDM);
		if ( t.Find( &_lMCode) ) {
			IDMLock l(t);
			if ( !l->Text() || *l->Text() == '\0')
				_MWert.SetText(NULL);
			else
				_MWert.SetText(l->Text ());

			_iModus = l->Modus();
//			_RechArt.ChangeCurrentIndex ( _iModus );	//DEFAULT

			_RechArt.Disable();
			if ( _iModus == 0 ) 
				_iModus = 1;
			else
				_iModus = 0;
	
			l->SetModus(_iModus);
	
			l->SetText (NULL);
		}
		_RechArt.ChangeCurrentIndex ( _iModus );	//DEFAULT
		_MWert.SetText(NULL);
		
		if ( _iModus == 0 || _iModus == 1 )
			_MWert.SetFocus();

		DELETE ( pBuffer);

		}
		break;

	}
}
//-------------------------------------------------------------------

void _XTENSN_EXPORT DefineMerkmalsWert :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		if ( _lMCode != 0L) {
			_MWert.GetText ( _pText , _MAX_PATH );
			CTable t(*_pIDM);
			if ( t.Find( &_lMCode) ) {
				IDMLock l(t);
				if ( _pText)
					l->SetText ( _pText);
				if ( _iModus > -1)
					l->SetModus ( _iModus);
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

		case IDB_ATTSTOREMWERT:
		{
		_MWert.GetText ( _pText , _MAX_PATH );
		CTable t(*_pIDM);
		if ( t.Find( &_lMCode) ) {
			IDMLock l(t);
			if ( _pText)
				l->SetText ( _pText);
			if ( _iModus > -1 )
				l->SetModus ( _iModus);
		}
		_MWert.SetText(NULL);
		_lMCode = 0L;
		_iModus = -1;
		_StoreMWert.Disable();
		_RechArt.Disable();
		_RechArt.ChangeCurrentIndex ( 0 );	//DEFAULT
		}
		break;
	}
	return;
}
//Member

//-------------------------------------------------------------------
//
Bool DefineMerkmalsWert :: FillMClassList ( void )
{
	if ( !_pIDM )
		return FALSE;
	short Flag = true;
// ------------MerkmalListBox füllen
	CTable t ( *_pIDM);
	for ( t.First(); t.Valid(); t.Next()) {
		IDMLock l(t);
		FillMKListBox ( l->Ident(),Flag, &_MClass);
	}
	return true;
}
//------------------------------------------------------------------
Bool DefineMerkmalsWert :: FillModusList ( void)
{

	_RechArt.AddString ( ResString (ResID (IDS_EXISTIERT, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_NOEXIST, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_EXAKT, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_TEILMENGE, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_INVERS, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_ANFANG, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_ENDE, &_RF), 30));
	_RechArt.AddString ( ResString (ResID (IDS_LAENGE, &_RF), 30));
	_RechArt.ChangeCurrentIndex ( 0 );	//DEFAULT

	return true; 
}

//----------------------------------------------------------------
long DefineMerkmalsWert :: GetMCode ( int iIndex )
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

	ulong uIdent;
	IdentFromClassX ( pBuff,&uIdent);
	Ident = (long)uIdent;

/*---------23.1.97
	if ( DEX_GetIdBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);
-----------*/

	*ptr = ':';
	DELETE ( pBuff);

	return Ident;	

}
//------------------------------------------------------------------
//	File MWERT.CXX
