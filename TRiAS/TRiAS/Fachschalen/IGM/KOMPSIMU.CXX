// KOMPIAS-MEMBER 
// File: KOMPSIMU.CXX


#include "kompp.hxx"   
#include "version.h"
#include "kompaktr.h"

#include "kompdef.h"  

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>
#include <igeometr.hxx>
#include "cobjtree.hxx"

#include "triasdef.h"  

#include "gewbaum.hxx"
#include "txtedit.hxx"
#include "kompdll.hxx"
#include "kompias.hxx"
#include "kompsimu.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

//-------------------------------------------------------------------

//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------Trias.Simu.Gew.Klasse---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

SimuGewaesser :: SimuGewaesser (pWindow pW, uint res, ResourceFile &RF, KPTree * pGew, KPTree *pNGew)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _GewClass ( this, IDLB_SIMUGEWAESSER), 
	       _ZuoClass ( this, IDLB_SIMUZUORDNUNG), 
	       _LenTRiAS( this, IDS_SIMUGEWLAENGETRIAS),
	       _Von( this, IDS_SIMUVON),
	       _Bis( this, IDS_SIMUBIS),
		_UButton( this, IDB_SIMUUNTERHALTUNG),
		_AusButton( this, IDB_SIMUAUSSCHREIBUNG),
		_AufButton( this, IDB_SIMUAUFTRAG),
		_AumButton( this, IDB_SIMUAUFMASS),
		_ArchivButton( this, IDB_SIMUARCHIV),

	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	if ( !pGew)
		return;
	_pGew = pGew;
	_pNGew = pNGew;
//	pW->Disable();
	FillGewClassList();
	FillZuoClassList();
	_ArchivButton.Disable();
	_LenTRiAS.SetText(NULL);
	_Von.SetText(NULL);
	_Bis.SetText(NULL);
	_UButton.SetState(true);
	_iB = 1;
	_iG = -1;
	_iZ = -1;
	return;
}

#pragma warning (default: 4355)


SimuGewaesser :: ~SimuGewaesser (void)
{
//	_pW->Enable();
}

void _XTENSN_EXPORT SimuGewaesser :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDLB_SIMUGEWAESSER:
		{

		int iIndex = _GewClass.GetCurrentIndex();
		if ( iIndex == -1)
			return;

		char *pGewNr = new char [_MAX_PATH];
		_iG = iIndex;
		_GewClass.GetString ( pGewNr, iIndex, _MAX_PATH);

		if ( !_pGew)  {
			DELETE_OBJ (pGewNr);
			return;
		}
		char Buf[20];	

		CTable t(*_pGew);
		if ( t.Find (pGewNr)) {
			KP_GEWLock l(t);
			if (l->Ende() > 0 ) {
				_LenTRiAS.SetText ( ltoa (l->Ende(),Buf,10));
				_Von.SetText( ltoa (l->Beginn(),Buf,10));
				_Bis.SetText( ltoa (l->Ende(),Buf,10));
			} else {
				_LenTRiAS.SetText( NULL);
			}
				
		}		
		DELETE_OBJ ( pGewNr);
		}
		break;

		case IDLB_SIMUZUORDNUNG:
		{
		_iZ = 100;

		int iIndex = _ZuoClass.GetCurrentIndex();
		if ( iIndex == -1)
			return;
		if ( iIndex == 0)
			_iZ = 100;
		if ( iIndex == 1)
			_iZ = 210;
		if ( iIndex == 2)
			_iZ = 230;
		if ( iIndex == 3)
			_iZ = 250;
		if ( iIndex == 4)
			_iZ = 270;
		if ( iIndex == 5)
			_iZ = 300;
		if ( iIndex == 6)
			_iZ = 350;
		if ( iIndex == 7)
			_iZ = 400;
		}
		break;

	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT SimuGewaesser :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
			char * pWert = new char [_MAX_PATH];
			char * pNum = new char [_MAX_PATH];

			LEISTUNGEN L;
			memset (&L, '\0', sizeof(LEISTUNGEN));
			L.dwSize = sizeof(LEISTUNGEN);

			L.iIdentNrHerkunft = (short)_iB;
			L.iIdentNrZuordnung = (short) _iZ;
			_GewClass.GetString ( pNum, _iG, _MAX_PATH);
			L.pcGewaesserNr = pNum;

			_Von.GetText ( pWert,_MAX_PATH);
			L.lBeginn = atol(pWert);

			_Bis.GetText ( pWert,_MAX_PATH);
			L.lEnde = atol(pWert);

			if ( _iZ == -1 || _iG == -1 || _iB > 5 || L.lEnde == 0L) {
				MessageBox (0,
				"Nicht alle notwendigen Werte angegeben !! ",
				"Fehlerhafte Definition",
				MB_OK);

//				EndDlg(0);
				return;
			}


			if ( L.lBeginn > L.lEnde ) {
				MessageBox (0,
				"Beginn > Ende !!",
				"Fehlerhafte Definition",
				MB_OK);
//				EndDlg(0);
				return;
			}

			UebergebeLeistungen ( &L, DWORD(_pNGew));

			DELETE_OBJ ( pWert);	
			DELETE_OBJ ( pNum);

			EndDlg(1);

		}
		
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

		case IDB_SIMUUNTERHALTUNG:
		{
		_iB = 1;
		_UButton.SetState(true);
		_AusButton.SetState(false);
		_AufButton.SetState(false);
		_AumButton.SetState(false);
		}
		break;

		case IDB_SIMUAUSSCHREIBUNG:
		{
		_iB = 2;
		_UButton.SetState(false);
		_AusButton.SetState(true);
		_AufButton.SetState(false);
		_AumButton.SetState(false);
		}
		break;

		case IDB_SIMUAUFTRAG:
		{
		_iB = 3;
		_AufButton.SetState(true);
		_UButton.SetState(false);
		_AusButton.SetState(false);
		_AumButton.SetState(false);
		}
		break;

		case IDB_SIMUAUFMASS:
		{
		_iB = 4;
		_UButton.SetState(false);
		_AusButton.SetState(false);
		_AufButton.SetState(false);
		_AumButton.SetState(true);
		}
		break;
	}
	return;
}


//-----------------------------------------------------------------------------
//Member
//-------------------------------------------------------------------
//-------------------------------------------------------------------
Bool SimuGewaesser :: FillZuoClassList ( void )
{
	_ZuoClass.Clear();
	_ZuoClass.AddString( ResString (ResID(IDS_IDRANDSTREIFEN,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDBOESCHUNGLINKS,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDBOESCHUNGRECHTS,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDBOESCHUNGBEIDE,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDBOESCHUNGTEILPROFIL,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDSOHLKRAUTUNG,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDGRUNDRAEUMUNG,&_RF),40));

	_ZuoClass.AddString(ResString (ResID(IDS_IDSTUNDENSTUECKLOHN,&_RF),40));
	return true;
}
//-------------------------------------------------------------------
Bool SimuGewaesser :: FillGewClassList ( void )
{
	if (!_pGew )
		return false;
	_GewClass.Clear();
	if( _pGew->Count() == 0L )
		return true;

	CTable t(*_pGew);

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if (!l) continue;
		if ( !l->GewNr() || *l->GewNr() == '\0')
			continue; 
		_GewClass.AddString ( l->GewNr());
	}
	return true;
}
//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------KompaktNamenVergabe------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

KompaktName :: KompaktName(pWindow pW, uint res, ResourceFile &RF, long lONr, short iTyp)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _KName( this, IDC_OBJEKTNAME),
	       _KBezeichnung( this, IDC_OBJEKTBEZEICHNUNG),
	       _TName( this, IDC_NAMETEXT),
	       _TBezeichnung( this, IDC_BEZEICHNUNGTEXT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	short MaxKeyGew = 15;
	short MaxKeyBauw = 6;
	_isValid = false;
	_pW = pW;
	_KName.SetText(NULL);
	_KBezeichnung.SetText(NULL);
	OKButton.Disable();
	_KName.SetButton ( &OKButton);
	_KName.SetTextLimit ( (uint)MaxKeyGew); 

	bool iStatus = false;
	_KName.SetStatus(&iStatus);
	_KBezeichnung.SetStatus(&iStatus);

	_lONr = lONr;

	long lIdent = DEX_GetObjIdent(lONr);

	_iBTyp = ((CKompiasExtension *)g_pTE)->BauwerkeTyp(lIdent);

	_pName = NULL;
	_pBezeichnung = NULL;

	_iTyp = iTyp;

	char *pString = new char [_MAX_PATH];
	if (pString) {
		if ( iTyp == 0 ) {	//Gewässer
			*pString = '\0';

			strcat (pString,ResString (ResID(IDS_GEWAESSERDATEN, &_RF),50));
			SetCaption( pString);

//		SetCaption ( "Gewässerdaten");
			*pString = '\0';
			strcat (pString,ResString (ResID(IDS_GEWAESSERMCODENR, &_RF),50));
			_TName.SetText (pString);
		
//		_TName.SetText ("Gewässernummer");
			*pString = '\0';

			strcat (pString,ResString (ResID(IDS_GEWAESSERMCODENAME, &_RF),50));
			_TBezeichnung.SetText (pString);

//		_TBezeichnung.SetText ("Gewässername");

		} else {
			*pString = '\0';

//			strcat (pString,ResString (ResID(IDS_EREIGNISDATEN, &_RF),50));
			strcat (pString,ResString (ResID(IDS_EINMUENDUNG, &_RF),50));
			SetCaption( pString);

//		SetCaption ( "Ereignisdaten");

/*
			*pString = '\0';
			strcat (pString,ResString (ResID(IDS_EREIGNISKURZ, &_RF),50));
			_TName.SetText (pString);

//		_TName.SetText ("Ereigniskurztext");

			*pString = '\0';

			strcat (pString,ResString (ResID(IDS_EREIGNISLANG, &_RF),50));
			_TBezeichnung.SetText (pString);
*/

//		_TBezeichnung.SetText ("Ereignislangtext");

		}

		DELETE_OBJ(pString);
	} else 
		return;


	_KName.SetFocus();

	return;
}

#pragma warning (default: 4355)


KompaktName :: ~KompaktName (void)
{
	DELETE_OBJ (_pName);
	DELETE_OBJ (_pBezeichnung);
}
//----------------------------------------------------------------------
void _XTENSN_EXPORT KompaktName :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
			_pName = new char [_MAX_PATH];

			_KName.GetText ( _pName,_MAX_PATH);

			_pBezeichnung = new char [_MAX_PATH];

			_KBezeichnung.GetText ( _pBezeichnung,_MAX_PATH);

			EndDlg(1);

		}
		
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;


	}
	return;
}
//---------------------------------------------------------------------------------
void KompaktName :: SetKompaktName ( char * pName) 
{
	_KName.SetText ( pName);
	OKButton.Enable();

}
//------------------------------------------------------------------------------
short KompaktName :: BauwerkeKeyLen ( long lONr)
{

	short iLen = 0;

	if (lONr == -1L || lONr == 0L )
		return iLen;

	long lIdent = DEX_GetObjIdent ( lONr);

	char NewIdent[MAX_OKS_LENX+1];


#if _MSC_VER < 1100
	ClassFromIdentX ( lIdent, NewIdent);
#else
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	ClassFromIdentX ( hPr,lIdent, NewIdent);
#endif

	
	long RefIdent = atol(NewIdent+1);	

	RefIdent = RefIdent/1000L;

	if ( (short)RefIdent != cBauwerkeIdent) {
		return iLen;
	}

//	StartWerte
	short MaxKeyGew = 15;
	short MaxKeyBauw = 6;

	iLen = MaxKeyBauw;	

//	RefIdent = atol(NewIdent+1);	
	RefIdent = atol(NewIdent+2);	

	if ( RefIdent == cBauwerkeEinmuendung)
		iLen = MaxKeyGew;
	return iLen;
}

//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------EreignisNamenVergabe------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

EreignisName :: EreignisName(pWindow pW, uint res, ResourceFile &RF, long lONr, short iTyp)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _KName( this, IDC_OBJEKTNAMEBAU),
	       _NameClass ( this, IDC_OBJEKTNAMELISTE), 
	       _KBezeichnung( this, IDC_OBJEKTBEZEICHNUNGBAU),
	       _TName( this, IDC_NAMETEXT),
	       _TBezeichnung( this, IDC_BEZEICHNUNGTEXT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte

	_isValid = false;
	_iCount = -1;
	_pW = pW;

	_KName.SetText(NULL);
	_KBezeichnung.SetText(NULL);
	OKButton.Disable();

	_lONr = lONr;

	long lIdent = DEX_GetObjIdent(lONr);
	_iBTyp = ((CKompiasExtension *)g_pTE)->BauwerkeTyp(lIdent);

	_pName = NULL;
	_pBezeichnung = NULL;
	_hLib = NULL;
	_iTyp = iTyp;

	char *pString = new char [_MAX_PATH];
	if (pString) {

// KK010808
// Bauwerke (OKS) - Kurztext liefern

		PBDDATA pbdData;
		char KText[TEXTLEN+1];

		memset (&pbdData, '\0', sizeof(PBDDATA));

		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdKText = KText;
		pbdData.pbdLTextLen = 0;

		pbdData.pbdCode = lIdent;
		KText[0] = '\0';
		pbdData.pbdKTextLen = sizeof(KText) -1;

#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif


		*pString = '\0';
		if ( '\0' == KText[0] )
			strcat (pString,ResString (ResID(IDS_EREIGNISDATEN, &_RF),50));
		else
			wsprintf(pString,ResString (ResID(IDS_EREIGNISDATENEX, &_RF),50),KText);

		SetCaption( pString);

//		SetCaption ( "Ereignisdaten");

		*pString = '\0';
		strcat (pString,ResString (ResID(IDS_EREIGNISKURZ, &_RF),50));
		_TName.SetText (pString);

//		_TName.SetText ("Ereigniskurztext");

		*pString = '\0';
		strcat (pString,ResString (ResID(IDS_EREIGNISLANG, &_RF),50));
		_TBezeichnung.SetText (pString);

//		_TBezeichnung.SetText ("Ereignislangtext");

	} else
		return;


	//Einmündungen abfangen
//	StartWerte
	short MaxKeyGew = 15;
	short MaxKeyBauw = 6;

	short iLen = BauwerkeKeyLen ( lONr);

	if (iLen > MaxKeyBauw ) {
		_iCount = -1;
		return;
	}



	if ( !FillKatalog()) {
		if ( 0 == ((CKompiasExtension *)g_pTE)->GetKatasterKommentarEin ())
			return;
	
		char *pProt = new char [_MAX_PATH];
		if (pProt ) {
			char *pName = BauwerkeName(_iBTyp);
			if ( pName ) {
				wsprintf (pProt,ResString (ResID(IDS_KPKATALOGERROR1, &_RF),120),pName);
//				wsprintf (pProt," Katalogeintrag fehlt für '%s' \n   bitte eintragen !",pName);
				DELETE_OBJ(pName);
			} else {
				wsprintf (pProt,ResString (ResID(IDS_KPKATALOGERROR2, &_RF),80));
//				wsprintf (pProt," Katalogeintrag fehlt für 'Name unbekannt' \n   bitte eintragen !");
			}
			MessageBox (__hWndM,
			 pProt,
			 ResString (ResID(IDS_BILDEEREIGNISSE, &_RF),50),
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE_OBJ(pProt);
			return;
		} else {
			MessageBox (__hWndM,
			ResString (ResID(IDS_KPKATALOGERROR3, &_RF),50),
//			 "Katalogeintrag fehlt - bitte eintragen",
			 ResString (ResID(IDS_BILDEEREIGNISSE, &_RF),50),
			 MB_OK|MB_ICONEXCLAMATION);
			return;
		}
	}

	_NameClass.SetFocus();

	return;
}

#pragma warning (default: 4355)


EreignisName :: ~EreignisName (void)
{
	DELETE_OBJ (_pName);
	DELETE_OBJ (_pBezeichnung);
}
//----------------------------------------------------------------------
void _XTENSN_EXPORT EreignisName :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
			_pName = new char [_MAX_PATH];

			_KName.GetText ( _pName,_MAX_PATH);

			_pBezeichnung = new char [_MAX_PATH];

			_KBezeichnung.GetText ( _pBezeichnung,_MAX_PATH);

			EndDlg(1);

		}
		
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;


	}
	return;
}
//---------------------------------------------------------------------------------

void _XTENSN_EXPORT EreignisName :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDC_OBJEKTNAMELISTE:
		{
		
		int iIndex = _NameClass.GetCurrentIndex();
		if (iIndex != -1) {
			OKButton.Enable();
			char *pBuffer = new char [_MAX_PATH];
			_NameClass.GetCurrentString (pBuffer);
			char *ptr = strchr (pBuffer, ':');
			if ( ptr ) {
				*ptr = '\0';
				_KName.SetText(pBuffer);
				ptr++;
				_KBezeichnung.SetText ( ptr);
			}
			DELETE_OBJ(pBuffer);
		}
		}
		break;

	}
	return;
}

//-----------------------------------------------------------------------------
bool EreignisName :: FillKatalog (void) 
{
// Für Ereigniskatalog vorbereitet
	_hLib = ((CKompiasExtension *)g_pTE)->KompaktDLL();
		
	return HoleKatalogVonKompakt(_iBTyp);

}
//---------------------------------------------------------------------
bool EreignisName :: HoleKatalogVonKompakt ( short iTyp )
{


	KOMPAKTKATALOGPROC pFcn = ( KOMPAKTKATALOGPROC) THoleKatalogProc;


	if (_hLib)
		_hLib->EnumeriereKompaktKatalog ( iTyp, pFcn, (DWORD)&_NameClass );
	else
		return false;

//	int iIndex = _NameClass.GetCurrentIndex();

	int iIndex = _NameClass.GetCount();

	if (iIndex <= 0) 
		return false;

	_iCount = iIndex;

	return true;

}

//------------------------------------------------------------------------------
short EreignisName :: BauwerkeKeyLen ( long lONr)
{

	short iLen = 0;

	if (lONr == -1L || lONr == 0L )
		return iLen;

	long lIdent = DEX_GetObjIdent ( lONr);

	char NewIdent[MAX_OKS_LENX+1];


#if _MSC_VER < 1100
	ClassFromIdentX ( lIdent, NewIdent);
#else
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	ClassFromIdentX ( hPr,lIdent, NewIdent);
#endif

	
	long RefIdent = atol(NewIdent+1);	

	RefIdent = RefIdent/1000L;

	if ( (short)RefIdent != cBauwerkeIdent) {
		return iLen;
	}

//	StartWerte
	short MaxKeyGew = 15;
	short MaxKeyBauw = 6;

	iLen = MaxKeyBauw;	

//	RefIdent = atol(NewIdent+1);	
	RefIdent = atol(NewIdent+2);	

	if ( RefIdent == cBauwerkeEinmuendung)
		iLen = MaxKeyGew;
	return iLen;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------

//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
// File: KOMPSIMU.CXX
