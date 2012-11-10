// ----------------Auswahl der Gewaesserklassen -----------------------------
// File: KOMPGEW.CXX

#include "kompp.hxx"   

#include "kompaktr.h"
#include "kompdef.h"

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "igeometr.hxx"
#include "triasdef.h"
#include "gewbaum.hxx"
#include "komphead.hxx"
#include "txtedit.hxx"
#include "kpmcode.hxx"
#include "kpstatus.hxx"
#include "kompdll.hxx"
#include "kompgew.hxx"
#include "cobjtree.hxx"
#include "kompias.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

//--------------------------------------------------------------------------
//-------------------------Gew.Klasse---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster ----------------------------

#pragma warning (disable: 4355)

KompaktKlassenAuswahl :: KompaktKlassenAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH, short iTyp)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDLB_TROBJCLASSAUSWAHL),
	       _GewClass ( this, IDLB_TRGEWCLASSAUSWAHL),
	       OKButton (this, IDOK),
	       StoreButton (this, IDB_TRGEWZUORDNEN),
	       DeleteButton (this, IDB_TRGEWENTFERNEN),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_iChanged = false;
	_pW = pW;
	_iTyp = iTyp;
	_iRefTyp = -1;
	_pMText = new char [_MAX_PATH];
	if ( !_pMText)
		return;

	if ( !pKH)
		return;
	_pKH = pKH;

	short iBase = DEX_GetMkBase();
	if ( iTyp == PM_GEWAESSER ) {

		*_pMText = '\0';
		strcat ( _pMText, ResString(ResID(IDS_DEFGEWAESSER,&_RF),70));

		SetCaption ( _pMText);

//		SetCaption ( "Definieren von Gewässern");

		_pGew = pKH->GewClass();
		_lIDCode = pKH->CodeGewKl();
			
		if (iBase == 16) {
			if ( pKH->GewDiffProzent())
				wsprintf (_pMText, "%lx;%lx;P%d",pKH->CodeGewNr(),pKH->CodeGewName(),pKH->GewDiffLaenge());
			else
				wsprintf (_pMText, "%lx;%lx;%d",pKH->CodeGewNr(),pKH->CodeGewName(),pKH->GewDiffLaenge());
		} else {
			if ( pKH->GewDiffProzent())
				wsprintf (_pMText, "%ld;%ld;P%d",pKH->CodeGewNr(),pKH->CodeGewName(),pKH->GewDiffLaenge());
			else
				wsprintf (_pMText, "%ld;%ld;%d",pKH->CodeGewNr(),pKH->CodeGewName(),pKH->GewDiffLaenge());
		}

	}

	if ( iTyp == PM_HYDRAULIK ) {

		*_pMText = '\0';
		strcat ( _pMText, ResString(ResID(IDS_DEFUEBERSCHWEMMUNG,&_RF),70));

		SetCaption ( _pMText);
//		SetCaption ( "Definieren von potentiellen Überschwemmungsgebieten");
		_pGew = pKH->HydrClass();
		_lIDCode = pKH->CodeHydrKl();

		if (iBase == 16)
			wsprintf (_pMText, "%lx;%lx",pKH->CodeHydrWert(),pKH->CodeHydrHoehe());
		else
			wsprintf (_pMText, "%ld;%ld",pKH->CodeHydrWert(),pKH->CodeHydrHoehe());
	}

	if ( iTyp == PM_FLAECHEN ) {
		_pGew = pKH->FlaClass();
		_lIDCode = pKH->CodeFlaKl();

// Standard = AlleFlaechen
		_iRefTyp = cAlleFlaechen;
		{
		GebietsFlaechen GF ( this,GEBIETSFLAECHEN,_RF);
		GF.Show(Centre);
		if ( GF.Result() == 1 )
			_iRefTyp = GF.FlaechenTyp();

		}

		*_pMText = '\0';
		strcat ( _pMText, ResString(ResID(IDS_DEFADMIN,&_RF),70));
		
		if ( _iRefTyp != cAlleFlaechen) {

			if ( _iRefTyp == cGemeindenFlaeche) {
				strcat ( _pMText,"[");
				strcat (_pMText,ResString(ResID(IDS_GEMEINDEFLAECHE,&_RF),70));
				strcat ( _pMText,"]");
//				SetCaption ( "Definieren von administrativen Gebieten[Gemeinden]");
			}
		
			if ( _iRefTyp == cBehoerdenFlaeche) {
				strcat ( _pMText,"[");
				strcat (_pMText,ResString(ResID(IDS_BEHOERDENFLAECHE,&_RF),70));
				strcat ( _pMText,"]");

//				SetCaption ( "Definieren von administrativen Gebieten[Behörden]");
			}
		
			if ( _iRefTyp == cSchaubezirkFlaeche) {
				strcat ( _pMText,"[");
				strcat (_pMText,ResString(ResID(IDS_SCHAUBEZIRKSFLAECHE,&_RF),70));
				strcat ( _pMText,"]");

//				SetCaption ( "Definieren von administrativen Gebieten[Schaubezirke]");
			}
		
			if ( _iRefTyp == cEinzugsgebietsFlaeche) {
				strcat ( _pMText,"[");
				strcat (_pMText,ResString(ResID(IDS_EINZUGSGEBIETFLAECHE,&_RF),70));
				strcat ( _pMText,"]");

//				SetCaption ( "Definieren von administrativen Gebieten[Einzugsgebiete]");
			}
		}

		SetCaption ( _pMText);

		wsprintf (_pMText, "%d",_iRefTyp);
		
	}

	_lClassIdent = _lGewIdent = NULL;
	if (!_pGew )
		_pGew = new TR_OCLTree;

//	pW->Disable();
	StoreButton.Disable();
	DeleteButton.Disable();
	FillObjClassList();
	FillGewClassList();

	return;
}

#pragma warning (default: 4355)


KompaktKlassenAuswahl :: ~KompaktKlassenAuswahl (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _lClassIdent);
	DELETE_OBJ ( _lGewIdent);
	DELETE_OBJ ( _pMText);
}

void _XTENSN_EXPORT KompaktKlassenAuswahl :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDLB_TROBJCLASSAUSWAHL:
		{
		int iIndex = _ObjClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _ObjClass.GetCount();
		DELETE_OBJ ( _lClassIdent);

		_lClassIdent = new long [ Count + 1];
		*_lClassIdent = 0L;
		ErfasseObjKlasse ( iIndex );


		iIndex=_ObjClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseObjKlasse ( iIndex );
			iIndex=_ObjClass.GetNextSelected ();
		}
		StoreButton.Enable();
		DeleteButton.Disable();
		DELETE_OBJ ( _lGewIdent);
		}
		break;

		case IDLB_TRGEWCLASSAUSWAHL:
		{
		int iIndex = _GewClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _GewClass.GetCount();
		DELETE_OBJ ( _lGewIdent);
		_lGewIdent = new long [ Count + 1];
		*_lGewIdent = 0L;
		ErfasseGewKlasse ( iIndex );


		iIndex=_GewClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseGewKlasse ( iIndex );
			iIndex=_GewClass.GetNextSelected ();
		}
		DeleteButton.Enable();
		StoreButton.Disable();
		DELETE_OBJ ( _lClassIdent);

		}
		break;
	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT KompaktKlassenAuswahl :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{

		((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();

		Aktualisieren();

		_isValid = true;
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		Korrigieren();
		_isValid = false;
		EndDlg (0);
		}
		break;


		case IDB_TRGEWZUORDNEN: // Gew zuordnen
		{

		if ( _lClassIdent && *_lClassIdent > 0L ) {
			AddGewInformation();
			StoreButton.Disable();
//			OKButton.SetText("&Speichern");
			OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
		}
		DELETE_OBJ (_lClassIdent);
		FillGewClassList();
		}
		break;

		case IDB_TRGEWENTFERNEN:
		{
		if ( _lGewIdent && *_lGewIdent > 0L ) {
			DeleteGewInformation( );
			DeleteButton.Disable();
			OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
		}
		DELETE_OBJ (_lGewIdent);
		FillGewClassList();
		}
		break;

	}
	return;
}
//Member
//------------------------------------------------------------------
//-------------------------------------------------------------------
Bool KompaktKlassenAuswahl :: FillObjClassList ( void )
{
//	Alle O'Klassen formal durchzählen und Baum anlegen
	ENUMNOKEYLONG ENT;
//	ENT.eKey = NULL;	// NULL = aktuelle Sicht
//	Bestimmen der Anzahl der Objektklassen

// KK991129
	if ( _iTyp == PM_HYDRAULIK || _iTyp == PM_FLAECHEN ) 
		ENT.eFcn = ( ENUMTEXTKEYPROC) FillFullIDListBox;
	else
		ENT.eFcn = ( ENUMTEXTKEYPROC) FillIDListBox;

	
	ENT.ePtr = &_ObjClass;
	DEX_EnumIdents(ENT);
    return true;
}

//-------------------------------------------------------------------
Bool KompaktKlassenAuswahl :: FillGewClassList ( void )
{
	if (!_pGew )
		return false;

	_GewClass.Clear();
	if( _pGew->Count() == 0L )
		return true;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;
	CTable t(*_pGew);

	short iBase = DEX_GetIdBase();
	
	PBDDATA pbdData;
	char KText[TEXTLEN+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = KText;
	pbdData.pbdLTextLen = 0;


	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		if ( l->Define() == OC_LOESCHEN)
			continue;
		*pBuffer = '\0';
		long Ident = l->Ident();
		if ( _iTyp == PM_FLAECHEN) {
			if (_iRefTyp != cAlleFlaechen ) {
				if ( !KlassenTyp (_iRefTyp, Ident))
					continue;
			}
		}
		pbdData.pbdCode = Ident;
		KText[0] = '\0';
		pbdData.pbdKTextLen = sizeof(KText) -1;

#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(Ident);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif

		if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&_RF),70));
		KText[TEXTLEN] = '\0';

		ulong ulIdent = (ulong) Ident;
		char NewIdent[MAX_OKS_LENX];

	#if _MSC_VER < 1100
		ClassFromIdentX ( ulIdent, NewIdent);
	#else
		ClassFromIdentX ( hPr,ulIdent, NewIdent);
	#endif

		wsprintf (pBuffer, "%s:%s", NewIdent, KText);


	#if _MSC_VER < 1100
		_GewClass.AddString ( pBuffer);
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (pBuffer, " (");
				strcat (pBuffer, cbBuffer);
				strcat (pBuffer, ")");
			}
		}

		// Ident am jeweiligen Item speichern
		int iIndex = _GewClass.AddString (pBuffer);

		_GewClass.SetItemData (iIndex, Ident);
	#endif // _MSC_VER < 1200

	}
	DELETE_OBJ ( pBuffer);
	return true;
}
/////////////////////////////////////////////////////////////////////
bool KompaktKlassenAuswahl :: KlassenTyp ( short iTyp, long lIdent)
{
	bool iFlag = false;

	if ( !_pKH)
		return iFlag;

	if ( 0L == lIdent )
		return iFlag;

	ulong ulFClass = _pKH->CodeFlaKl();
	if ( 0L == ulFClass )
		return iFlag;

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return iFlag;

	// MerkmalsWert holen
#if _MSC_VER >= 1100
	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView =KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;
#else
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif
	tm.lTarget = lIdent;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long)ulFClass;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ (pBuff);
		return iFlag;
	}
	}

	short iKTyp = atoi ( pBuff);
	DELETE_OBJ (pBuff);

	if ( iKTyp == iTyp)
		iFlag = true;
	return iFlag;

}
//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: ErfasseObjKlasse ( int iIndex) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_ObjClass.GetString (pClassName,iIndex,_MAX_PATH);


	char *ptr = strchr (pClassName, ':');
	if ( ptr ) {
		long Num = *_lClassIdent;
		*ptr = '\0';
		long Ident;
		ulong uIdent;

#if _MSC_VER < 1100
		IdentFromClassX(pClassName,&uIdent);
#else
		uIdent = _ObjClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif

		Ident = (long) uIdent;

/*----------23.1.97
		if ( DEX_GetIdBase() == 16 )
			Ident = strtoul ( pClassName, NULL, 16 );
		else
			Ident = atol(pClassName);
----------------*/

		Num++;
		*_lClassIdent = Num;
		*(_lClassIdent + Num) = Ident;
	}
	DELETE_OBJ ( pClassName);
	return;
}
//-----------------------------------------------------------------
void KompaktKlassenAuswahl :: ErfasseGewKlasse ( int iIndex) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_GewClass.GetString (pClassName,iIndex,_MAX_PATH);

	char *ptr = strchr (pClassName, ':');
	if ( ptr ) {
		*ptr = '\0';
		long Ident;
		long Num = *_lGewIdent;
		ulong uIdent;

#if _MSC_VER < 1100
		IdentFromClassX(pClassName,&uIdent);
#else
		uIdent = _GewClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif


		Ident = (long) uIdent;

/*----------23.1.97
		if ( DEX_GetIdBase() == 16 )
			Ident = strtoul ( pClassName, NULL, 16 );
		else
			Ident = atol(pClassName);
-------------------*/

		Num++;
		*_lGewIdent = Num;
		*(_lGewIdent + Num) = Ident;
	}
	DELETE_OBJ ( pClassName);
	return;
}
//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: AddGewInformation (void) 
{    
	if ( !_pGew)
		return;
	CTable t ( *_pGew);
	for ( long l = 0L; l < *_lClassIdent; l++) {
		long Ident = *(_lClassIdent + l + 1);
		if ( !t.Find ( &Ident )) {
			long MCode = 0L;
			TR_OCLCreator TRCr ( *_pGew);
			ContCreate ( TRCr, TR_OCL) ( Ident, MCode,OC_TEMPORAER,NULL);
			StoreIdentFeature(Ident);
		} else {
				StoreIdentFeature(Ident);
		}
	}
}
//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: DeleteGewInformation (void) 
{    
	CTable t ( *_pGew);
	for ( long l = 0L; l < *_lGewIdent; l++) {
		long Ident = *(_lGewIdent + l + 1);
		if ( t.Find ( &Ident )) {
			TR_OCLLock l(t);
			if ( l) {
				l->StoreDefinition ( OC_LOESCHEN);
			}
		}
	}
	return;
}

//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: StoreIdentFeature ( long Ident) 
{

	if ( !_pMText)
		return;

	SetzePBDIDCode ( _iTyp,Ident,_lIDCode);
	ulong lIDCode = (ulong)_lIDCode;

#if _MSC_VER >= 1100
	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView =KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;

	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	
	if ( m_hPr != hPr ) {
		ResString StrH (ResID(IDS_HYDRAULIKCODE,&g_pTE->RF()),60);
		ResString StrF (ResID(IDS_FLAECHENCODE,&g_pTE->RF()),60);
		if ( _iTyp == PM_FLAECHEN)
			lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrF.Addr());
		else
			lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrH.Addr());
	
	}
 
	
#else
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =_pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = lIDCode;		// MerkmalsCode

	if ( EC_OKAY != DEX_ModTextMerkmal ( tm ))
		return;

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();

	if ( pLocProt ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {

			*pT = '\0';
			wsprintf(pT," - Ident %ld mit MCode %ld : Wert = %s \n",Ident,_lIDCode,_pMText);

			KompaktProtokoll (pLocProt,pT);

			DELETE_OBJ(pT);

		}
	}

	return;

}
//------------------------------------------------------------------
void KompaktKlassenAuswahl :: BaumAktualisieren ( void) 
{
	if ( !_pGew || !_lGewIdent || *_lGewIdent == 0L)
		return;

	CTable t(*_pGew);

	for ( long l = 0L; l < *_lGewIdent; l++) {
		long Ident = *(_lGewIdent + l + 1);
		if ( t.Find(&Ident)) {
			t.Delete();
		}
	}
	_pGew->Optimize();
	return;
}
////////////////////////////////////////////////////////////////////
void KompaktKlassenAuswahl :: DeleteIdentGewaesser ( long Ident, long lCount) 
{

	if ( !_pKH)
		return;
	if ( _iTyp == PM_FLAECHEN)
		return;			// Keine Attribute

	if ( _iTyp == PM_GEWAESSER) {
		if(_pKH->CodeGewNr() == 0L || _pKH->CodeGewName() == 0L)
			return;
	}
	if ( _iTyp == PM_HYDRAULIK) {
		if(_pKH->CodeHydrHoehe() == 0L )
			return;
	}

	CEierUhr Wait (g_pTE->MVWind());

	//	Anzahl der Objekte bestimmen
	long lRefCount = 0L;

	if ( lCount == 0L) {
		ENUMLONGKEY ELK;
		memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
		ELK.eFcn = ( ENUMLONGKEYPROC) EnumeriereObjekte;
		ELK.eKey = Ident;
		ELK.ePtr = &lRefCount;
		DEX_EnumIdentObjects(ELK);
		lCount = lRefCount;

	}

	if ( lRefCount == 0L)
		lCount = 100L;


	
	MERKMALSDEFINITION MD;
	memset (&MD,'\0',sizeof(MERKMALSDEFINITION) );

	if ( _iTyp == PM_GEWAESSER) {
		MD.lNummer = _pKH->CodeGewNr();
		MD.lName = _pKH->CodeGewName();
		MD.lStartPunkt = _pKH->CodeBauwAnfStat();
	}
	if ( _iTyp == PM_HYDRAULIK) {
		MD.lNummer = _pKH->CodeHydrHoehe();
		MD.lName = 0L;
		MD.lStartPunkt = 0L;
	}


	MD.lCount = lCount;
	MD.lRefCount = 0L;

	ResString resCaptionG (ResID(IDS_DELETEGEWAESSER, &_RF), 50);

	ResString resCaptionH (ResID(IDS_DELETEHOEHE, &_RF), 50);
	
	CStatus *pStatus;
	if ( _iTyp == PM_GEWAESSER) 
		pStatus = new CStatus ( _pW, &_RF, lCount, resCaptionG);
	if ( _iTyp == PM_HYDRAULIK) 
		pStatus = new CStatus ( _pW, &_RF, lCount, resCaptionH);

//	CStatus *pStatus = new CStatus ( _pW, &_RF, lCount, "Gewässernummer löschen");
	pStatus->Show();
	MD.pStatus = pStatus;

//	GewNr + GewName aus Objekte des Ident raus

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) LoescheGewaesserObjekt;
	ELK.eKey = Ident;
	ELK.ePtr = &MD;
	DEX_EnumIdentObjects(ELK);

	if (pStatus)
		DELETE_OBJ (pStatus);

	return;

}
////////////////////////////////////////////////////////////////////
void KompaktKlassenAuswahl :: StoreIdentGewaesser ( long Ident, long lCount) 
{
//	GewNr in Objekte des Ident

	if ( !_pKH)
		return;

	if ( _iTyp == PM_FLAECHEN)
		return;			// Keine Attribute

	if ( _iTyp == PM_GEWAESSER) {
		if(_pKH->CodeGewNr() == 0L )
			return;
	}
	if ( _iTyp == PM_HYDRAULIK) {
		if(_pKH->CodeHydrHoehe() == 0L )
			return;
	}

	CEierUhr Wait (g_pTE->MVWind());

	//	Anzahl der Objekte bestimmen
	long lRefCount = 0L;

	if ( lCount == 0L) {
		ENUMLONGKEY ELK;
		memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
		ELK.eFcn = ( ENUMLONGKEYPROC) EnumeriereObjekte;
		ELK.eKey = Ident;
		ELK.ePtr = &lRefCount;
		DEX_EnumIdentObjects(ELK);
		lCount = lRefCount;

	}


	if ( lRefCount == 0L)
		lCount = 100L;


	MERKMALSDEFINITION MD;
	memset (&MD,'\0',sizeof(MERKMALSDEFINITION) );
	if ( _iTyp == PM_GEWAESSER) 
		MD.lNummer = _pKH->CodeGewNr();
	if ( _iTyp == PM_HYDRAULIK) 
		MD.lNummer = _pKH->CodeHydrHoehe();
	MD.lCount = lCount;
	MD.lRefCount = 0L;


	ResString resCaptionG (ResID(IDS_LISTGEWAESSER, &_RF), 50);
	ResString resCaptionH (ResID(IDS_LISTHOEHE, &_RF), 50);

	CStatus *pStatus;

	if ( _iTyp == PM_GEWAESSER) 
		pStatus = new CStatus ( _pW, &_RF, lCount, resCaptionG);
	if ( _iTyp == PM_HYDRAULIK) 
		pStatus = new CStatus ( _pW, &_RF, lCount, resCaptionH);

//	CStatus *pStatus = new CStatus ( _pW, &_RF, lCount, "Gewässernummer eintragen");
	pStatus->Show();

	MD.pStatus = pStatus;


//	GewNr in Objekte 

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SetzeGewaesserObjekt;
	ELK.eKey = Ident;
	ELK.ePtr = &MD;

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocProt ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf (pT,"\n\t+++ Gewässernummer eintragen Ident = %ld +++\n",Ident); 
			KompaktProtokoll (pLocProt,pT);
			DELETE_OBJ(pT);
		}
	}
	DEX_EnumIdentObjects(ELK);

	if (pStatus)
		DELETE_OBJ(pStatus);

	return;
}
////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: DeleteIdentFeature ( long Ident) 
{
//	Ident aus Baum raus

	if ( Ident == 0L)
		return;

	long Num = *_lGewIdent;
	Num++;
	*_lGewIdent = Num;
	*(_lGewIdent + Num) = Ident;

#if _MSC_VER >= 1100
	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;
#else
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif


	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = NULL;
	tm.pMText = NULL;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = _lIDCode;		// MerkmalsCode
	DEX_ModTextMerkmal ( tm );
	return;

}
//-------------------------------------------------------------------------
void KompaktKlassenAuswahl :: Aktualisieren ( void) 
{
	if ( !_pGew || _pGew->Count() == 0)
		return;

	CEierUhr Wait ( _pW);

	{

	CTable t(*_pGew);

	long Count = _pGew->Count();

	if ( _lGewIdent)
		DELETE_OBJ ( _lGewIdent);
	_lGewIdent = new long [ Count + 1];
	*_lGewIdent = 0L;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		long lCount = 0L;
		if (l->OBJ()) {
			TR_OBJTree *pObj = l->OBJ();
			lCount = pObj->Count();
		}

		if ( l->Define() == OC_LOESCHEN ) {
			((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();
			DeleteIdentFeature ( Ident);
			DeleteIdentGewaesser ( Ident, lCount);
			_iChanged = true;
			((CKompiasExtension *)g_pTE)->ExtModifyRegisterNotification ();
		}

		if ( l->Define() == OC_TEMPORAER) {
			l->StoreValidation ( OC_ANLEGEN);
			l->StoreDefinition ( OC_ANLEGEN);
			SetzePBDMCode (Ident,_pKH->CodeGewNr(),ResString(ResID(IDS_GEWAESSERMCODENR,&_RF),50));
			SetzePBDMCode (Ident,_pKH->CodeGewName(),ResString(ResID(IDS_GEWAESSERMCODENAME,&_RF),50));
			StoreIdentGewaesser(Ident, lCount);
			_iChanged = true;
		}

	}

	}
	BaumAktualisieren();
	DELETE_OBJ ( _lGewIdent);

	if ( _pGew->Count() == 0)  {

		if ( _iTyp == PM_GEWAESSER) {
			_pKH->DeleteGewClass();
			_pGew = _pKH->GewClass();
		}
		if ( _iTyp == PM_HYDRAULIK) {
			_pKH->DeleteHydrClass();
			_pGew = _pKH->HydrClass();
		}

		if ( _iTyp == PM_FLAECHEN) {
			_pKH->DeleteFlaClass();
			_pGew = _pKH->FlaClass();
		}

	} else {

		if ( _iTyp == PM_GEWAESSER) {
			if ( !_pKH->GewClass())
				_pKH->StoreGewClass( _pGew);
		}
		if ( _iTyp == PM_HYDRAULIK) {
			if ( !_pKH->HydrClass())
				_pKH->StoreHydrClass(_pGew);
		}

		if ( _iTyp == PM_FLAECHEN) {
			if ( !_pKH->FlaClass())
				_pKH->StoreFlaClass(_pGew);
		}

	}

}
//-------------------------------------------------------------------------
//------------------------------------------------------------------
// Code für IDCode in PBD setzen
//-------------------------------------------------------------------
void KompaktKlassenAuswahl :: SetzePBDIDCode ( short iTyp, long lIdent, long MCode)
{
	char KText[TEXTLEN];
	KText[0] = NULL;

#if _MSC_VER >= 1100

PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);


#else

	PBDMERKMAL pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMAL));
	
	pbdData.dwSize = sizeof(PBDMERKMAL);

#endif


	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	if ( iTyp == PM_GEWAESSER)
		strcat ( KText,  ResString (ResID(IDS_GEWAESSERCODE,&_RF),40));
	if ( iTyp == PM_BAUWERKE)
		strcat ( KText,  ResString (ResID(IDS_BAUWERKECODE,&_RF),40));
	if ( iTyp == PM_HYDRAULIK)
		strcat ( KText,  ResString (ResID(IDS_HYDRAULIKCODE,&_RF),40));
	if ( iTyp == PM_FLAECHEN)
		strcat ( KText,  ResString (ResID(IDS_FLAECHENCODE,&_RF),40));

	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.ipbdMTyp = MPIdentFeature | PBDMERKMAL_SYSTEMFLAG;	
	pbdData.ipbdMLen = 256;


#if _MSC_VER >= 1100

	pbdData.lIdent = lIdent;

	DefineFeatureSet(&pbdData);
/*--------------

	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
 
	HPROJECT _hPr = DEX_GetObjectsProject(lIdent);



// Test, ob OE bereits definiert
	long lRefCode = DEX_GetMCodeFromFeatureNameEx(_hPr,KText);

	if ( m_hPr == _hPr && 0L != lRefCode && lRefCode == MCode)
			return;

	if ( m_hPr != _hPr && 0L != lRefCode )
			return;

	if (lRefCode != 0L && lRefCode != MCode) {
		if ( m_hPr == _hPr)
			((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);


		{
		ErrInstall EI (WC_NOMERKMAL);
		if (DEX_ModPBDDataEx (_hPr,pbdData) != EC_OKAY) {
			return;
		} else {
			char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();

			if ( pLocProt ) {
				char *pT = new char [_MAX_PATH];
				if (pT) {
					*pT = '\0';
					wsprintf(pT," - ID-Def Ident %ld MCode %ld Wert %s\n",lIdent,MCode,KText);
					KompaktProtokoll(pLocProt,pT);
					DELETE_OBJ(pT);
				}
			}

			DEXN_PBDMCodeChanged (MCode);
		}
		}

	}
	
	if (0L == lRefCode ) {		// nicht in Datenquelle
		long lNewCode = MCode;
		if ( _hPr != m_hPr ) {
			lNewCode = DEX_GetUniqueSysMCode();
		}

		if ( 0L == lNewCode)
			return;

		pbdData.pbdCode = lNewCode;

		{
		ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (_hPr,pbdData) != EC_OKAY)
				return;
			else
				DEXN_PBDMCodeChanged (MCode);
		}

	}
	----------------------------------------------*/

	return;

#else

	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (MCode);
	}

#endif

}
//-----------------------------------------------------------------

//-------------------------------------------------------------------------
void KompaktKlassenAuswahl :: SetzePBDMCode ( long lIdent ,long MCode, ResString rs ) 
{

// MCode für GewNr in PBD setzen
//-------------------------------------------------------------------

	char KText[TEXTLEN];
	KText[0] = NULL;

#if _MSC_VER >= 1100

PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

#else

PBDMERKMAL pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMAL));
	
	pbdData.dwSize = sizeof(PBDMERKMAL);

#endif


	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

	strcat ( KText, rs);

	pbdData.pbdKText = KText;

	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;


#if _MSC_VER >= 1100

	pbdData.lIdent = lIdent;

	DefineFeatureSet ( &pbdData);

/*-------------

	HPROJECT _hPr = DEX_GetObjectsProject(lIdent);


// Test, ob OE bereits definiert
	long lRefCode = DEX_GetMCodeFromFeatureNameEx(_hPr,KText);
	if (lRefCode != 0L && lRefCode != MCode)
		((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);

	{
	ErrInstall EI (WC_NOMERKMAL);
		if (DEX_ModPBDDataEx (_hPr,pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (MCode);
	}

  --------------------------------------*/
		
#else

	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (MCode);
	}

#endif
	return;

}
//-------------------------------------------------------------------------
void KompaktKlassenAuswahl :: Korrigieren ( void) 
{
	if ( !_pGew)
		return;

	CEierUhr Wait ( _pW);

	CTable t(*_pGew);

	long Count = _pGew->Count();

	if ( _lGewIdent)
		DELETE_OBJ ( _lGewIdent);
	_lGewIdent = new long [ Count + 1];
	*_lGewIdent = 0L;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( l->Define() == OC_LOESCHEN) {
			l->StoreValidation ( OC_ANLEGEN);
			l->StoreDefinition ( OC_ANLEGEN);
		}
		if ( l->Define() == OC_TEMPORAER) {
			DeleteIdentFeature ( Ident);
		}
	}
	BaumAktualisieren();
	DELETE_OBJ ( _lGewIdent);
	
}
//--------------------------------------------------------------------------
//-------------------------Trias.Gew.Klasse---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TriasGewaesser :: TriasGewaesser (pWindow pW, uint res, ResourceFile &RF, KPTree *pGew, CKompaktDLL * hLib,long lDiff, short iFlag)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _GewClass ( this, IDLB_TRIASGEWAESSER), 
	       _LenKompakt( this, IDS_TRIASGEWLAENGEKOMPAKT),
	       _LenTRiAS( this, IDS_TRIASGEWLAENGETRIAS),
	       _Name ( this, IDS_TRIASGEWAESSERNAME),
	       _Von ( this, IDS_TRIASGEWAESSERVON),
	       _Bis ( this, IDS_TRIASGEWAESSERBIS),
	       _KompShow (this, IDC_KOMPSHOW),
		   _Alle ( this, IDC_RADIOALLE),
		   _Kataster( this, IDC_RADIOKATASTER),
		   _Graphik ( this, IDC_RADIOGRAPHIK),
		   _NurKataster( this, IDC_RADIONURKATASTER),
		   _NurGraphik ( this, IDC_RADIONURGRAPHIK),
		   _Laenge ( this, IDC_RADIOLAENGE),
		   _Multi ( this, IDC_RADIOMULTI),
		   _GesLaenge (this , IDC_GESAMTLAENGE),
		   _Ueb (this, IDC_GEWCAPTION),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	if ( !pGew)
		return;
	_pGewNr = NULL;
	_pGewNr = new char [_MAX_PATH];
	_pGew = pGew;
	_pObj = NULL;
	_hLib = hLib;

	_iFlag = iFlag;
	_iTyp = 0;	// Alle Gewaesser

	_lDiff = 0L;

	if ( lDiff > 0L)
		_lDiff = lDiff;

	_KompShow.Disable();
	OKButton.Disable();

	FillGewClassList();
	_Name.SetText(NULL);
	_LenKompakt.SetText(NULL);
	_Von.SetText(NULL);
	_Bis.SetText(NULL);
	_LenTRiAS.SetText(NULL);
	_GesLaenge.SetText(NULL);

	_Alle.SetState(true);
	_NurKataster.SetState(false);
	_NurGraphik.SetState(false);
	_Kataster.SetState(false);
	_Graphik.SetState(false);
	_Laenge.SetState(false);
	_Multi.SetState(false);

//-------------Ueberschrift---------------------------

	char * pOut = new char [_MAX_PATH];
	if ( !pOut ) 
		return;

	wsprintf ( pOut," %ld Gewässer ", (long)pGew->Count());
	_Ueb.SetText ( pOut);

	DELETE_OBJ (pOut);
	if ( !iFlag ) {			// lokal
		_Alle.Disable();
		_Kataster.Disable();
		_Graphik.Disable();
		_NurKataster.Disable();
		_NurGraphik.Disable();
		_Laenge.Disable();
		_Multi.Disable();
	}

	return;
}

#pragma warning (default: 4355)


TriasGewaesser :: ~TriasGewaesser (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _pObj);
	DELETE_OBJ ( _pGewNr);
}

void _XTENSN_EXPORT TriasGewaesser :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {


		case IDLB_TRIASGEWAESSER:
		{
		_Name.SetText(NULL);

		int iIndex = _GewClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		_iCount = _GewClass.GetCount();
		if ( _iTyp == PM_MULTIOBJEKTE )
			_iCount = _iCount * 5;
		long lNumber = 0L;
		_pObj = new long [ _iCount +1];
		if ( _pObj == NULL )
			return;
		*_pObj = 0L;
		long lKLen = 0L;
		long lKey = GetObjNumber ( iIndex , &lKLen);
		if ( lKey > 0L ) {
			OKButton.Enable();
			lNumber++;
			*(_pObj+lNumber) = lKey;
			*_pObj = lNumber;
			if (_iTyp == PM_MULTIOBJEKTE )
				lNumber = GetAllObjects ( iIndex);
		} else
			OKButton.Disable();

	
		iIndex=_GewClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			if ( lNumber > _iCount - 1)
				break;
			lKey = GetObjNumber ( iIndex , &lKLen);
			if ( lKey > 0L ) {
				OKButton.Enable();
				lNumber++;
				*(_pObj+lNumber) = lKey;
				*_pObj = lNumber;
				if (_iTyp == PM_MULTIOBJEKTE )
					lNumber = GetAllObjects ( iIndex);
			} else 
				OKButton.Disable();

			iIndex=_GewClass.GetNextSelected ();
		}

		*_pObj = lNumber;
		if ( lNumber == 0L)
			DELETE_OBJ ( _pObj);
		}
		break;
	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT TriasGewaesser :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		if ( _pObj) {
			_isValid = true;
			EndDlg (1);
		} else {
			_isValid = false;
			EndDlg(0);
		}
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;

		case IDC_KOMPSHOW:
		{
		if (_hLib ) {
			if ( _pGewNr && *_pGewNr != '\0')
				_hLib->IGMEinzelGewaesser(this->Handle(),_pGewNr);
//				_hLib->KompaktEinzelGewaesser(this->Handle(),_pGewNr);
		}
		}
		break;

		case IDC_RADIOALLE:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(true);
		_Kataster.SetState(false);
		_Graphik.SetState(false);
		_NurKataster.SetState(false);
		_NurGraphik.SetState(false);
		_Multi.SetState(false);
		_Laenge.SetState(false);
		_iTyp = PM_ALLEGEWAESSER;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
			}
		break;



		case IDC_RADIOKATASTER:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_Kataster.SetState(true);
		_Graphik.SetState(false);
		_NurKataster.SetState(false);
		_NurGraphik.SetState(false);
		_Laenge.SetState(false);
		_Multi.SetState(false);
		_iTyp = PM_NURKATASTER;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;



		case IDC_RADIONURKATASTER:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_NurKataster.SetState(true);
		_Graphik.SetState(false);
		_Kataster.SetState(false);
		_NurGraphik.SetState(false);
		_Laenge.SetState(false);
		_Multi.SetState(false);
		_iTyp = PM_SOLOKATASTER;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;


		case IDC_RADIOGRAPHIK:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_Kataster.SetState(false);
		_Graphik.SetState(true);
		_NurKataster.SetState(false);
		_NurGraphik.SetState(false);
		_Laenge.SetState(false);
		_Multi.SetState(false);
		_iTyp = PM_NURGRAPHIK;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;


		case IDC_RADIONURGRAPHIK:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_Kataster.SetState(false);
		_NurGraphik.SetState(true);
		_NurKataster.SetState(false);
		_Graphik.SetState(false);
		_Laenge.SetState(false);
		_Multi.SetState(false);
		_iTyp = PM_SOLOGRAPHIK;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;


		case IDC_RADIOLAENGE:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_Kataster.SetState(false);
		_Graphik.SetState(false);
		_NurKataster.SetState(false);
		_NurGraphik.SetState(false);
		_Laenge.SetState(true);
		_Multi.SetState(false);
		_iTyp = PM_LAENGENDIFF;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;

		case IDC_RADIOMULTI:
		{
		_KompShow.Disable();
		OKButton.Disable();
		_Alle.SetState(false);
		_Kataster.SetState(false);
		_Graphik.SetState(false);
		_NurKataster.SetState(false);
		_NurGraphik.SetState(false);
		_Laenge.SetState(false);
		_Multi.SetState(true);
		_iTyp = PM_MULTIOBJEKTE;
		FillGewClassList ();
		_Name.SetText(NULL);
		_GesLaenge.SetText(NULL);
		_LenKompakt.SetText(NULL);
		_Von.SetText(NULL);
		_Bis.SetText(NULL);
		_LenTRiAS.SetText(NULL);
		}
		break;


	}
	return;
}
//Member
//-------------------------------------------------------------------
long TriasGewaesser :: GetObjNumber ( int iIndex ,long *lKLen)
{
	_Name.SetText(NULL);
	_Bis.SetText ( NULL );
	_Von.SetText(NULL);

	_KompShow.Disable();
	if ( _pGewNr )
		*_pGewNr = '\0';

	long lONr = 0L;
	char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return lONr;
	if ( !_pGew)
		return lONr;

	_GewClass.GetString (pBuff, iIndex, _MAX_PATH);

	char Buf[20];	
	CTable t(*_pGew);
	if ( t.Find (pBuff)) {
		KP_GEWLock l(t);


		if (l)
			lONr = l->Objekt();
//-------------Gewaessername------------------------
		if (l->GewName())
			_Name.SetText( l->GewName());
		else
			_Name.SetText(NULL);

//-------------Laenge-Kompakt--------------------			
		if (l->EndeKompakt() > l->BeginnKompakt()) {
			_LenKompakt.SetText ( ltoa (l->EndeKompakt()-l->BeginnKompakt(),Buf,10));
			if ( _pGewNr ) {
				_KompShow.Enable();
				*_pGewNr = '\0';
				strcat (_pGewNr,pBuff);
			}
		} else {
			_LenKompakt.SetText( NULL);
		}

//--------------Laenge -TRiAS------------------------------
		if (l->Ende() > l->Beginn() )	{

			if ( _iFlag ) 	// global
	 			*lKLen = *lKLen + l->Ende()-l->Beginn(); //Teillängen kumulieren
			_LenTRiAS.SetText ( ltoa (l->Ende()-l->Beginn(),Buf,10));
//			_LenTRiAS.SetText ( ltoa (*lKLen,Buf,10));
			_GesLaenge.SetText ( ltoa (*lKLen,Buf,10));
		} else {
			_LenTRiAS.SetText( NULL);
			_GesLaenge.SetText ( NULL);
		}

		if ( _iTyp == PM_MULTIOBJEKTE ) {

//			if ( l->Beginn() >= 0 && l->Ende() > 0 ) {
			if ( l->Ende() > l->Beginn() ) {
				_Von.SetText ( ltoa (l->Beginn(),Buf,10));
				_Bis.SetText ( ltoa (l->Ende(),Buf,10));
			
				if ( !_iFlag) {
 					*lKLen = *lKLen + l->Ende()-l->Beginn(); //Teillängen kumulieren
					_GesLaenge.SetText ( ltoa (*lKLen,Buf,10));
				}
			}

		} else {

			_Von.SetText ( ltoa (l->Beginn(),Buf,10));
			_Bis.SetText ( ltoa (l->Ende(),Buf,10));
				
//-------------- Von / Bis Variablen -----------------------
			if ( !l->GetOBJ()) {	// Original Innen

//				if ( l->Beginn() >= 0 && l->Ende() > 0 ) {
				if ( l->Ende() > l->Beginn() ) {
					_Von.SetText ( ltoa (l->Beginn(),Buf,10));
					_Bis.SetText ( ltoa (l->Ende(),Buf,10));
					if ( !_iFlag) {
		 				*lKLen = *lKLen + l->Ende()-l->Beginn(); //Teillängen kumulieren
						_GesLaenge.SetText ( ltoa (*lKLen,Buf,10));
					}
				}
			} else {
				TR_OBJTree *myOBJ = l->GetOBJ();
				CTable m (*myOBJ);
				short iPos = l->GetPosition();
				short iFind = (short)iIndex - iPos;
				// Verzweiflungskorrektur : 22.10.97
				if ( iFind < 0) 
					iFind = 0;

				short iCnt = 0;
				_Von.SetText ( NULL);
				_Bis.SetText ( NULL );
				for ( m.First(); m.Valid(); m.Next()) {
					TR_OBJLock n(m);

					if ( iCnt == iFind ) {

						lONr = n->Object();
						if (((CKompiasExtension *)g_pTE)->CheckOriginalObjekt(lONr)) {	// doppelte Objekte
							_pW->Disable();
							MessageBox (this->Handle(),
							 ResString (ResID(IDS_ERRMULTIWASSER, &g_pTE->RF()),80),
							 ResString (ResID(IDS_GEWAESSERUEBERSICHT, &g_pTE->RF()),80),
							 MB_OK|MB_ICONEXCLAMATION);
							_pW->Enable();

		// KK010829

							_iTyp = PM_MULTIOBJEKTE;

							DELETE_OBJ ( pBuff);
							return lONr;
						}
//						if ( n->Von() >= 0 && n->Bis() > 0 ) {
						if ( n->Bis() > 0 ) {
							_Von.SetText ( ltoa (n->Von(),Buf,10));
							_Bis.SetText ( ltoa (n->Bis(),Buf,10) );
						}

						lONr = n->Object();

						long lMyLen = n->Bis() - n->Von();

						if ( !_iFlag ) 	// lokal
				 			*lKLen = *lKLen + lMyLen; //Teillängen kumulieren
						_GesLaenge.SetText ( ltoa (*lKLen,Buf,10));
					}
					iCnt++;
				}
			}
		}

//----------------------------------------------------------

	}
	DELETE_OBJ ( pBuff);
	return lONr;
}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
long TriasGewaesser :: GetAllObjects ( int iIndex )
{
	long lNumber = 0L;
	if ( !_pObj || !_pGew )
		return lNumber;

	lNumber = *_pObj;
	
	if ( iIndex < 0)
		return lNumber;

	char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return lNumber;

	_GewClass.GetString (pBuff, iIndex, _MAX_PATH);

	CTable t(*_pGew);
	if ( t.Find (pBuff)) {
		KP_GEWLock l(t);
		if (l) {
			TR_OBJTree *pObj = l->GetOBJ();
			if ( pObj) {
				CTable d(*pObj);
				for (d.First(); d.Valid(); d.Next()){
					TR_OBJLock e(d);
					if (!e)
						continue;
					if ( lNumber >= _iCount - 1)
						continue;
					long lONr = e->Object();
					lNumber ++;
					*(_pObj+lNumber) = lONr;
					*(_pObj) = lNumber;
				}
			}
		}

	}
	DELETE_OBJ ( pBuff);
	return lNumber;
}
//-------------------------------------------------------------------
Bool TriasGewaesser :: FillGewClassList ( void )
{
	if (!_pGew )
		return false;

	_GewClass.Clear();
	if( _pGew->Count() == 0L )
		return true;

	CTable t(*_pGew);
	short iPos = 0;
	long lKLen = 0L;
	long lCount = 0L;

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);

		if (!l) continue;
		if ( !l->GewNr() || *l->GewNr() == '\0')
			continue; 
		if (_iTyp == PM_NURKATASTER) {	// nur Kataster
			if (!l->EndeKompakt())
				continue;
		}
		if (_iTyp == PM_SOLOKATASTER) {	// nur Kataster
			if (!l->EndeKompakt())
				continue;
			if (l->Ende())
				continue;
		}
		if (_iTyp == PM_NURGRAPHIK) {	// nur Graphik
			if (!l->Ende())
				continue;
		}
		if (_iTyp == PM_SOLOGRAPHIK) {	// nur Graphik
			if (!l->Ende())
				continue;
			if (l->EndeKompakt())
				continue;
		}
		if (_iTyp == PM_LAENGENDIFF) {	// nur Laengendifferenz
			if (!l->EndeKompakt() || !l->Ende())
				continue;
			if ( abs(l->EndeKompakt() - l->Ende()) <= _lDiff) {
				if ( abs(l->BeginnKompakt() - l->Beginn()) <= _lDiff)
				continue;
			}
		}
		if (_iTyp == PM_MULTIOBJEKTE) {	// nur mehrere Gewaesser
			if (l->Count() == 0L)
				continue;

// KK011123 ----------------------------------------------------------------------
			char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
			if ( pLocProt ) {
				char *pT = new char [_MAX_PATH];
				if (pT) {
					*pT = '\0';
					wsprintf (pT,"Doppelte Gewässer : %ld\n",l->Count() );
					KompaktProtokoll (pLocProt,pT);
					wsprintf ( pT, " *** Gewässernummer %s \n", l->GewNr());
					KompaktProtokoll (pLocProt,pT);
					char * pIdent = ObjektKlassenSchluessel(l->Objekt());
					char * pGITyp = GeometrieTyp( l->Objekt());
					wsprintf ( pT, " ObjektNr %ld ObjektTyp %s OKS %s\n", l->Objekt(),pGITyp,pIdent);
					DELETE_OBJ(pIdent);
					DELETE_OBJ(pGITyp);
					KompaktProtokoll (pLocProt,pT);
					char * pStart = LinienAnfangsPunkt( l->Objekt());
					wsprintf ( pT, " Von %ld ( AP = %s) - Bis %ld  \n",l->Beginn() ,pStart,l->Ende());
					KompaktProtokoll (pLocProt,pT);
					DELETE_OBJ(pStart);

					if ( l->GetOBJ()) {
						TR_OBJTree *pOBJ = l->GetOBJ();
//						long lnCount = pOBJ->Count() - 1;
						long lnCount = pOBJ->Count();
						if ( lnCount ) {
							CTable m (* pOBJ);
							for ( long i = 0L; i < lnCount; i++ ) {
								for ( m.First(); m.Valid(); m.Next()) {
									TR_OBJLock n(m);
									pIdent = ObjektKlassenSchluessel(n->Object());
									pGITyp = GeometrieTyp( n->Object());
									wsprintf ( pT, " ObjektNr %ld ObjektTyp %s OKS %s\n", n->Object(),pGITyp,pIdent);
									KompaktProtokoll (pLocProt,pT);
									DELETE_OBJ(pIdent);
									DELETE_OBJ(pGITyp);
									pStart = LinienAnfangsPunkt( n->Object());
									wsprintf ( pT, " Von %ld ( AP = %s) - Bis %ld \n", n->Von(),pStart,n->Bis());
									KompaktProtokoll (pLocProt,pT);
									DELETE_OBJ(pStart);
								}
							}
						}
					}

					DELETE_OBJ(pT);
				}
		}
//---------------------------------------------------------------------------------
		

		}
		
		int iIndex = _GewClass.AddString ( l->GewNr());
		lKLen = lKLen + l->Ende()-l->Beginn();
		lCount++;
//		l->SetPosition( iPos );
		l->SetPosition( (short)iIndex );
		iPos++;

		if ( !_iFlag ) {			// lokal

			if ( l->GetOBJ()) {
				TR_OBJTree *pOBJ = l->GetOBJ();
				long lnCount = pOBJ->Count() - 1;
				if ( lnCount ) {
					for ( long i = 0L; i < lnCount; i++ ) {
						_GewClass.AddString ( l->GewNr());
						iPos++;
					}
				}
			}
		}

	}
	char Buf[20];
	_GesLaenge.SetText ( ltoa (lKLen,Buf,10));

	char * pOut = new char [_MAX_PATH];
	if ( !pOut ) 
		return true;

	wsprintf ( pOut," %ld Gewässer ", lCount);
	_Ueb.SetText ( pOut);

	DELETE_OBJ (pOut);

	return true;

}
//-------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------ParameterAuswahl---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ParameterAuswahl :: ParameterAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _GewClass ( this, IDLB_PARMGEWAESSER),
	       _DefGew ( this, IDB_PARMDEFGEWAESSER),
	       _DefProzent ( this, IDC_LDIFFPROZENT),
	       _DefMeter ( this, IDC_LDIFFMETER),
			_GewDiff ( this,IDS_PARMDIFFGEWLAENGE),
			_GewSW ( this,IDC_LEISTUNGSSW),
			_GewPuffer ( this,IDC_PUFFERBEREICH),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	if ( !pKH)
		return;
	_pKH = pKH;

//	pW->Disable();
	char *pBuff = new char [50];

// GewaesserParameterEinstellungen
// KK010809
	if ( pKH->GewDiffLaenge() >= 0L )
		_GewDiff.SetText ( ltoa ( pKH->GewDiffLaenge(),pBuff,10));

	if ( pKH->GewSchrittweite() >= 0L )
		_GewSW.SetText ( ltoa ( pKH->GewSchrittweite(),pBuff,10));

	if ( pKH->GewPuffer() >= 0L )
		_GewPuffer.SetText ( ltoa ( pKH->GewPuffer(),pBuff,10));

	_GewDiff.SetButton(&OKButton);
	_GewSW.SetButton(&OKButton);
	_GewPuffer.SetButton(&OKButton);
	_iStatus = false;
	_GewDiff.SetStatus(&_iStatus);
	_GewSW.SetStatus(&_iStatus);
	_GewPuffer.SetStatus(&_iStatus);


	DELETE_OBJ ( pBuff);
	FillGewClassList();

//-----------StandardWerte-------------------------------------
	_lGewDiffLaenge = pKH->GewDiffLaenge();
	_iChangeGew = false;
	_iChange = false;

// KK010725

	_DefMeter.SetState(true);
	_DefProzent.SetState(false);
	if (pKH->GewDiffProzent() ){
		_DefMeter.SetState(false);
		_DefProzent.SetState(true);
	}

	OKButton.SetText (ResString(ResID(IDS_TEXTCLOSE,&_RF),30));
	OKButton.Disable();
	return;
}

#pragma warning (default: 4355)


ParameterAuswahl :: ~ParameterAuswahl (void)
{
//	_pW->Enable();
}

void _XTENSN_EXPORT ParameterAuswahl :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {


		case IDLB_PARMGEWAESSER:
		{
		
		}
		break;

	}
	return;
}


//----------------------------------------------------------------------

void _XTENSN_EXPORT ParameterAuswahl :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;

		if (_iStatus)
			OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));

		char * pWert = new char [_MAX_PATH];
		_GewDiff.GetText ( pWert,_MAX_PATH);
		_lGewDiffLaenge = atol(pWert);
	// KK010809
		_GewSW.GetText ( pWert,_MAX_PATH);
		_lGewSchrittweite = atol(pWert);

		_GewPuffer.GetText ( pWert,_MAX_PATH);
		_lGewPuffer = atol(pWert);

		DELETE_OBJ ( pWert);
		
		if ( CodeModifikation())
			SpeichereNeuenCode();
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;

		case IDB_PARMDEFGEWAESSER:
		{

			{
			KompaktKlassenAuswahl KKA ( this, OBJCLASSAUSWAHL, _RF,_pKH, PM_GEWAESSER);
			KKA.Show(Centre);
			if ( KKA.Result() == 1) {
				FillGewClassList();
				_iChange = KKA.isChanged();
				if ( _iChange) {
					_pKH->Aktualisieren(PM_GEWAESSER);
					// KK010918
					((CKompiasExtension *)g_pTE)->ResetGewInfo();
					OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
					OKButton.Enable();
				}
						
			}
			}

		}
		break;

		case IDC_LDIFFMETER:
		{
// KK010725
			_dGewDiffMeter = 0.0;
			_dGewDiffProzent = 0.0;
			_GewDiff.SetText ( "0");
//			_GewDiff.SetText ( NULL);
			_pKH->SetGewDiffProzent(false);

			((CKompiasExtension *)g_pTE)->ResetGewInfo();
			OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
			OKButton.Enable();
		}
		break;

		case IDC_LDIFFPROZENT:
		{
// KK010725
			_dGewDiffMeter = 0.0;
			_dGewDiffProzent = 0.0;
			_GewDiff.SetText ( "0");
//			_GewDiff.SetText ( NULL);
			_pKH->SetGewDiffProzent(true);
			((CKompiasExtension *)g_pTE)->ResetGewInfo();
			OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
			OKButton.Enable();
		}
		break;

	}
	return;
}
//Member
//-------------------------------------------------------------------
bool ParameterAuswahl :: CodeModifikation ( void )
{
	bool iFlag = false;

// -------LaengenDifferenz
	if ( _lGewDiffLaenge != _pKH->GewDiffLaenge() || 
		_lGewSchrittweite != _pKH->GewSchrittweite() || 
		_lGewPuffer != _pKH->GewPuffer()) {
			_pKH->StoreGewDiffLaenge(_lGewDiffLaenge);
			_pKH->SetGewSchrittweite(_lGewSchrittweite);
			_pKH->SetGewPuffer(_lGewPuffer);
			iFlag = true;
			_iChangeGew = true;
	}
/////////////////////////////////////////////////////////////
	return iFlag;
}
//------------------------------------------------------------------
void ParameterAuswahl :: SpeichereNeuenCode ( void )
{
	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;

	if ( _iChangeGew) {

		if (DEX_GetMkBase() == 16) {
			if (_pKH->GewDiffProzent())
				wsprintf (pMText, "%lx;%lx;P%d;%d;%d",_pKH->CodeGewNr(),_pKH->CodeGewName(),_pKH->GewDiffLaenge(),_pKH->GewSchrittweite(),_pKH->GewPuffer());
			else
				wsprintf (pMText, "%lx;%lx;%d;%d;%d",_pKH->CodeGewNr(),_pKH->CodeGewName(),_pKH->GewDiffLaenge(),_pKH->GewSchrittweite(),_pKH->GewPuffer());
		} else {
			if (_pKH->GewDiffProzent())
				wsprintf (pMText, "%ld;%ld;P%d;%d;%d",_pKH->CodeGewNr(),_pKH->CodeGewName(),_pKH->GewDiffLaenge(),_pKH->GewSchrittweite(),_pKH->GewPuffer());
			else
				wsprintf (pMText, "%ld;%ld;%d;%d;%d",_pKH->CodeGewNr(),_pKH->CodeGewName(),_pKH->GewDiffLaenge(),_pKH->GewSchrittweite(),_pKH->GewPuffer());
		}

		SpeichereNeuenGewCode(pMText);
	}

	DELETE_OBJ ( pMText);
}
//-----------------------------------------------------------------
void ParameterAuswahl :: SpeichereNeuenGewCode ( char *pMText )
{
	if ( !pMText || !_pKH->GewClass())
		return;

	// MerkmalsWert holen
#if _MSC_VER >= 1100
	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;
#else
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = _pKH->CodeGewKl();		// MerkmalsCode

	CTable t ( *_pKH->GewClass());
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		tm.lTarget = l->Ident();		// ObjektKlasse
		tm.imaxLen = _MAX_PATH-1;
		DEX_ModTextMerkmal ( tm );
	}
// DB-Header aktualisieren
/////////////////////////////////////////////////////////////////

	GEODBHDRENTRY hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);

	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTGEWCODE,&_RF),HEADERKEYSIZE+1),HEADERKEYSIZE);

	hdrEntry.lphdrText = new char [HEADERSIZE +1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	strcpy( hdrEntry.lphdrText, pMText);

#if _MSC_VER >= 1100
	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->HandleKompaktProject();
	DEX_WriteGeoDBHdrEntryEx (hPr,hdrEntry); 
#else
	DEX_WriteGeoDBHdrEntry (hdrEntry);
#endif

	DELETE_OBJ ( hdrEntry.lphdrText);

	return;

}
//-----------------------------------------------------------------
//-------------------------------------------------------------------
Bool ParameterAuswahl :: FillGewClassList ( void )
{

	_GewClass.Clear();

	if (!_pKH->GewClass() )
		return false;

	if( _pKH->GewClass()->Count() == 0L )
		return true;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;

	CTable t(*_pKH->GewClass());

	short iBase = DEX_GetIdBase();
	
	PBDDATA pbdData;
	char KText[TEXTLEN+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = KText;
	pbdData.pbdLTextLen = 0;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		*pBuffer = '\0';
		pbdData.pbdCode = Ident;
		KText[0] = '\0';
		pbdData.pbdKTextLen = sizeof(KText) -1;
#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(Ident);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif


		if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&_RF),70));
		KText[TEXTLEN] = '\0';

		ulong ulIdent = (ulong) Ident;
		char NewIdent[MAX_OKS_LENX + 1];


	#if _MSC_VER < 1100
		ClassFromIdentX ( ulIdent, NewIdent);
	#else
		ClassFromIdentX ( hPr,ulIdent, NewIdent);
	#endif

		wsprintf (pBuffer, "%s:%s", NewIdent, KText);


/*-----------23.1.97
		if ( iBase == 16 )
			wsprintf (pBuffer, "%08lx:%s", Ident, KText);
		else
			wsprintf (pBuffer, "%08ld:%s", Ident, KText);
-------------*/


	#if _MSC_VER < 1100
		_GewClass.AddString ( pBuffer);
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (pBuffer, " (");
				strcat (pBuffer, cbBuffer);
				strcat (pBuffer, ")");
			}
		}

		// Ident am jeweiligen Item speichern
		int iIndex = _GewClass.AddString (pBuffer);

		_GewClass.SetItemData (iIndex, Ident);
	#endif // _MSC_VER < 1200

	
	}                   
	DELETE_OBJ ( pBuffer);
	_GewClass.ChangeCurrentIndex(0);
	return true;
}
//-------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------HydraulikAuswahl---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

HydraulikAuswahl :: HydraulikAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH, short iTyp)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _HydrClass ( this, IDLB_HYDRAULIKKLASSE),
	       _DefHydr ( this, IDB_HYDRAULIKDEF),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_iChange = false;
	_isValid = false;
	_iTyp = iTyp;
	_pW = pW;
	if ( !pKH)
		return;
	_pKH = pKH;


	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;
	*pMText = '\0';

	if ( iTyp == PM_HYDRAULIK )
		strcat ( pMText, ResString(ResID(IDS_DEFUEBERSCHWEMMUNG,&_RF),70));
//		SetCaption ( "Definieren von potentiellen Überschwemmungsgebieten");


	if ( iTyp == PM_FLAECHEN ) 
		strcat ( pMText, ResString(ResID(IDS_DEFADMIN,&_RF),70));
//		SetCaption ( "Definieren von administrativen Gebieten");

	SetCaption (pMText);
	DELETE_OBJ(pMText);
	
//	pW->Disable();

	FillHydrClassList();

//-----------StandardWerte-------------------------------------
	_iChange = false;

	return;
}

#pragma warning (default: 4355)


HydraulikAuswahl :: ~HydraulikAuswahl (void)
{
//	_pW->Enable();
}

void _XTENSN_EXPORT HydraulikAuswahl :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {


		case IDLB_HYDRAULIKKLASSE:
		{
		
		}
		break;

	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT HydraulikAuswahl :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;

		case IDB_HYDRAULIKDEF:
		{

			{
			KompaktKlassenAuswahl KKA ( this, OBJCLASSAUSWAHL, _RF,_pKH, _iTyp);
			KKA.Show(Centre);
			if ( KKA.Result() == 1)
				FillHydrClassList();
				_iChange = KKA.isChanged();
				if ( _iChange ) {
					_pKH->Aktualisieren(_iTyp);
				}
			}
		}
		break;

	}
	return;
}
//Member
//-------------------------------------------------------------------
//------------------------------------------------------------------
//-----------------------------------------------------------------
//-------------------------------------------------------------------
Bool HydraulikAuswahl :: FillHydrClassList ( void )
{

	_HydrClass.Clear();

	TR_OCLTree *pClass;

	if ( _iTyp == PM_HYDRAULIK)
		pClass = _pKH->HydrClass();

	if ( _iTyp == PM_FLAECHEN)
		pClass = _pKH->FlaClass();

	if (!pClass)
		return false;

	if( pClass->Count() == 0L )
		return true;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;

	CTable t(*pClass);

	short iBase = DEX_GetIdBase();
	
	PBDDATA pbdData;
	char KText[TEXTLEN+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = KText;
	pbdData.pbdLTextLen = 0;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		*pBuffer = '\0';
		pbdData.pbdCode = Ident;
		KText[0] = '\0';
		pbdData.pbdKTextLen = sizeof(KText) -1;

#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(Ident);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif


	if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&_RF),70));
		KText[TEXTLEN] = '\0';

		ulong ulIdent = (ulong) Ident;
		char NewIdent[MAX_OKS_LENX + 1];


	#if _MSC_VER < 1100
		ClassFromIdentX ( ulIdent, NewIdent);
	#else
		ClassFromIdentX ( hPr,ulIdent, NewIdent);
	#endif


		wsprintf (pBuffer, "%s:%s", NewIdent, KText);


	#if _MSC_VER < 1100
		_HydrClass.AddString ( pBuffer);
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (pBuffer, " (");
				strcat (pBuffer, cbBuffer);
				strcat (pBuffer, ")");
			}
		}

		// Ident am jeweiligen Item speichern
		int iIndex = _HydrClass.AddString (pBuffer);

		_HydrClass.SetItemData (iIndex, Ident);
	#endif // _MSC_VER < 1200


	}                   
	DELETE_OBJ ( pBuffer);
	_HydrClass.ChangeCurrentIndex(0);
	return true;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------

//--------------------------------------------------------------------------
//-------------------------ParameterEinstellung---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ParameterEinstellung :: ParameterEinstellung (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
		_DefName ( this, IDC_NAMEVERBAND),
		_DefGew ( this,IDB_PEGEWAESSER),
		_DefHydr ( this,IDB_PEHYDRAULIK),
		_DefFla ( this,IDB_PEFLAECHEN),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_iFlag = false;
	_isValid = false;
	_pW = pW;
	if ( !pKH)
		return;
	_pKH = pKH;

//	pW->Disable();

	_pName = new char [_MAX_PATH];

	if ( _pName) {
		if ( GetKompaktUserName(_pName,_MAX_PATH))
			_DefName.SetText(_pName);
		else
			_DefName.SetText(NULL);
	}

	OKButton.SetText (ResString(ResID(IDS_TEXTCLOSE,&_RF),30));

	return;
}

#pragma warning (default: 4355)


ParameterEinstellung :: ~ParameterEinstellung (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _pName);
}
//----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////
bool ParameterEinstellung :: GetKompaktUserName (char *pBuffer, short iLen)
{
	bool iFlag = false;
	if ( !pBuffer)
		return iFlag;

	*pBuffer = '\0';

	GEODBHDRENTRY hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTNAME,&_RF),HEADERKEYSIZE +1),HEADERKEYSIZE);
	hdrEntry.lphdrText = pBuffer;
	hdrEntry.hdrTextLen = iLen;

#if _MSC_VER >= 1100
	HPROJECT hPr =((CKompiasExtension *)g_pTE)->HandleKompaktProject();
	if (DEX_ReadGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) 
#else
	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) 
#endif

	// HeaderEintrag existiert
		iFlag = true;

	return iFlag;
}
///////////////////////////////////////////////////////////////////////
bool ParameterEinstellung :: SetKompaktUserName (char *pBuffer, short iLen)
{
	bool iFlag = false;
	if ( !pBuffer || *pBuffer == '\0')
		return iFlag;

	GEODBHDRENTRY hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTNAME,&_RF),HEADERKEYSIZE +1),HEADERKEYSIZE);
	hdrEntry.lphdrText = pBuffer;
	hdrEntry.hdrTextLen = iLen;

#if _MSC_VER >= 1100
	HPROJECT hPr =((CKompiasExtension *)g_pTE)->HandleKompaktProject();
	if (DEX_WriteGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) 
#else
	if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY) 
#endif

	// HeaderEintrag existiert und angelegt
		iFlag = true;

	return iFlag;
}
///////////////////////////////////////////////////////////////////////
void _XTENSN_EXPORT ParameterEinstellung :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;
		if ( _pName ) {
			_DefName.GetText(_pName,_MAX_PATH);
			SetKompaktUserName (_pName,_MAX_PATH);		
		}
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;

/////////////////////////////////////////////////////////////////////////////
		case IDB_PEGEWAESSER:
		{
			{
			ParameterAuswahl PA ( this, PARAMETERAUSWAHL, _RF,_pKH);
			PA.Show(Centre);
			if (PA.Result() == 1 )
				_iFlag = PA.isChanged();
				if ( _iFlag ) {
					UINT wMsg = RegisterWindowMessage ("GEWAESSERABGLEICH");
					PostMessage ( __hWndM,wMsg,0,0);
					OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
				}
			}
		}
		break;
/////////////////////////////////////////////////////////////////////////////
		case IDB_PEHYDRAULIK:
		{
			{
			HydraulikAuswahl HA ( this, HYDRAULIKAUSWAHL, _RF,_pKH,PM_HYDRAULIK);
			HA.Show(Centre);
			if (HA.Result() == 1 )
				_iFlag = HA.isChanged();

			if ( _iFlag) {
		// Abgleich Objektname / Höhe vornehmen !!

				UINT wMsg = RegisterWindowMessage ("HYDRAULIKABGLEICH");
				PostMessage ( __hWndM,wMsg,0,0);
				OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
			}

			}
		}
		break;


/////////////////////////////////////////////////////////////////////////////
		case IDB_PEFLAECHEN:
		{
			{
			HydraulikAuswahl HA ( this, HYDRAULIKAUSWAHL, _RF,_pKH,PM_FLAECHEN);
			HA.Show(Centre);
			_iFlag = HA.isChanged();
			if ( _iFlag)
				_pKH->Aktualisieren(PM_FLAECHEN);
				OKButton.SetText (ResString(ResID(IDS_TEXTSTORE,&_RF),30));
			}
		}
		break;

	}
	return;
}
/////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
//-------------------------GewaesserStatistik-------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

GewaesserStatistik :: GewaesserStatistik (pWindow pW, uint res, ResourceFile &RF, long lDiff, KPTree *pGew)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
		_NurKatGew ( this, IDC_GEWSTATKAT),
		_NurTRiASGew ( this, IDC_GEWSTATTRIAS),
		_BeideGew ( this, IDC_GEWSTATBEIDE),
		_DiffLaenge ( this, IDC_GEWSTATDIFF),
		_DiffLaengenTyp ( this, IDC_LDIFFTEXT),
	       OKButton (this, IDOK)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	if ( !pGew)
		return;
	_pGew = pGew;

//	pW->Disable();
	_NurKatGew.SetText(NULL);
	_NurTRiASGew.SetText(NULL);
	_BeideGew.SetText(NULL);
	_DiffLaenge.SetText(NULL);
	_DiffLaengenTyp.SetText(NULL);

	_lDiff = lDiff;
	_lCntKat = _lCntTRiAS = _lCntBeide = _lCntDiff = 0L;

	ListeGewaesser();
	return;
}

#pragma warning (default: 4355)


GewaesserStatistik :: ~GewaesserStatistik (void)
{
//	_pW->Enable();
}
//----------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
void GewaesserStatistik :: ListeGewaesser (void )
{
	if ( !_pGew || _pGew->Count() == 0)
		return;
	CTable t (*_pGew);
	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if (!l->Objekt()) {	// NurKataster
			_lCntKat++;
			continue;
		}
		if (!l->EndeKompakt()) {	// Nur TRiAS
			_lCntTRiAS++;
			continue;
		}
		_lCntBeide++;
		if ( l->Ende() != l->EndeKompakt()) {

// KK010731
			long lGewLen = l->Ende();
			if ( lGewLen < l->EndeKompakt())
				lGewLen = l->EndeKompakt();

			long lDiff = abs (l->Ende() - l->EndeKompakt());

			if ( ((CKompiasExtension *)g_pTE)->GewaesserDiffLaenge(lDiff,lGewLen)) 

//			if ( lDiff > _lDiff)
				_lCntDiff++;
		}
	}

	char Buf[20];	
	_NurKatGew.SetText( ltoa (_lCntKat,Buf,10));
	_NurTRiASGew.SetText( ltoa (_lCntTRiAS,Buf,10));
	_BeideGew.SetText( ltoa (_lCntBeide,Buf,10));
	_DiffLaenge.SetText( ltoa (_lCntDiff,Buf,10));

// KK010726
	char * pKText = new char [_MAX_PATH];
	char * pRText = new char [_MAX_PATH];
	if ( pKText && pRText) {
		*pRText = '\0';
		strcat (pRText,ResString(ResID(IDS_KOMPDIFFLAENGE,&_RF),70).Addr());

		((CKompiasExtension *)g_pTE)->DiffLaengenText(&Buf[0],20);
//		wsprintf ( pKText, ResString(ResID(IDS_KOMPDIFFLAENGE,&_RF),70).Addr(),Buf[0]);
		wsprintf ( pKText, pRText,&Buf[0]);
		_DiffLaengenTyp.SetText( pKText);
	}

	DELETE_OBJ(pKText);
	DELETE_OBJ(pRText);

	return;
}
///////////////////////////////////////////////////////////////////////
void _XTENSN_EXPORT GewaesserStatistik :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;
		EndDlg (1);
		}
		break;

	}
	return;
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
//-------------------------BauwerkeStatistik-------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

BauwerkeStatistik :: BauwerkeStatistik (pWindow pW, uint res, ResourceFile &RF,TR_OCLTree *pBauw)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _BauwClass ( this, IDLB_TRIASBAUWERKE), 
		   _BauwCount ( this, IDC_BAUWERKECOUNT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	if ( !pBauw)
		return;
	_pBauw = pBauw;
	_pObj = NULL;
	_lCount = 0L;
//	pW->Disable();
	OKButton.Disable();
	_BauwCount.SetText(NULL);

	FillBauwClassList();

	return;
}

#pragma warning (default: 4355)

//////////////////////////////////////////////////////////////////////////
BauwerkeStatistik :: ~BauwerkeStatistik (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _pObj);
}

//----------------------------------------------------------------------

void _XTENSN_EXPORT BauwerkeStatistik :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {


		case IDLB_TRIASBAUWERKE:
		{

		int iIndex = _BauwClass.GetFirstSelected();
		if ( iIndex == -1)
			return;

		OKButton.Enable();

		_pObj = new long [ _lCount +1];
		if ( _pObj == NULL )
			return;

		*_pObj = 0L;

		char Buff[20];

		long lCnt = 0;
		long lIdent = GetIdentNumber(iIndex, &lCnt);
		_BauwCount.SetText(ltoa (lCnt,Buff,10));
		while ( iIndex != -1 ) {

			iIndex=_BauwClass.GetNextSelected ();

			long lIdent = GetIdentNumber(iIndex,&lCnt);
			_BauwCount.SetText(ltoa (lCnt,Buff,10));
			
		}

		if ( *_pObj == 0)
			DELETE_OBJ ( _pObj);
		}
		break;
	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT BauwerkeStatistik :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		if ( _pObj) {
			_isValid = true;
			EndDlg (1);
		} else {
			_isValid = false;
			EndDlg(0);
		}
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;


	}
	return;
}
//Member
//-------------------------------------------------------------------
Bool BauwerkeStatistik :: FillBauwClassList ( void )
{
	if (!_pBauw )
		return false;

	_BauwClass.Clear();
	if( _pBauw->Count() == 0L )
		return false;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;



	CTable t(*_pBauw);


	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheBauwObjekt;
	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie | OTPunkt;

	short iBase = DEX_GetIdBase();
	
	PBDDATA pbdData;
	char KText[TEXTLEN+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = KText;
	pbdData.pbdLTextLen = 0;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		*pBuffer = '\0';
		pbdData.pbdCode = Ident;
		KText[0] = '\0';
		pbdData.pbdKTextLen = sizeof(KText) -1;
#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(Ident);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif


		if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&_RF),70));
		KText[TEXTLEN] = '\0';


		ulong ulIdent = (ulong) Ident;
		char NewIdent[MAX_OKS_LENX];


	#if _MSC_VER < 1100
		ClassFromIdentX ( ulIdent, NewIdent);
	#else
		ClassFromIdentX ( hPr,ulIdent, NewIdent);
	#endif

		wsprintf (pBuffer, "%s:%s", NewIdent, KText);


/*----------23.1.97
		if ( iBase == 16 )
			wsprintf (pBuffer, "%08lx:%s", Ident, KText);
		else
			wsprintf (pBuffer, "%08ld:%s", Ident, KText);
----------------*/


	#if _MSC_VER < 1200
		_BauwClass.AddString ( pBuffer);
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (pBuffer, " (");
				strcat (pBuffer, cbBuffer);
				strcat (pBuffer, ")");
			}
		}

		// Ident am jeweiligen Item speichern
		int iIndex = _BauwClass.AddString (pBuffer);

		_BauwClass.SetItemData (iIndex, Ident);
	#endif // _MSC_VER < 1200



		if ( l->OBJ()) {
			_lCount = _lCount + l->OBJ()->Count();
			continue;
		}	

		TR_OBJTree *pOBJ = new TR_OBJTree;
		ELK.eKey = Ident;
		OT.pOBJ = pOBJ;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);

		if ( pOBJ->Count() == 0 ) {
			DELETE_OBJ ( pOBJ);
		} else {
			l->StoreObj( pOBJ);
			_lCount = _lCount + pOBJ->Count();
		}
	}                   
	DELETE_OBJ ( pBuffer);

	return true;

}
///////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
long BauwerkeStatistik :: GetIdentNumber ( int iIndex , long *lCount)
{
	long lIdent = 0L;

	if ( iIndex < 0 )
		return lIdent;

	char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return lIdent;

	_BauwClass.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr ( pBuff, ':');
	if ( ptr)
		*ptr = '\0';
	ulong uIdent;

#if _MSC_VER < 1100
	IdentFromClassX ( pBuff, &uIdent);
#else
	uIdent = _BauwClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif

	lIdent = (long)uIdent;

/*------------23.1.97
	if ( DEX_GetIdBase() == 16 )
		lIdent = strtoul ( pBuff, NULL, 16 );
	else
		lIdent = atol(pBuff);
--------------*/

	DELETE_OBJ ( pBuff);

	CTable t (*_pBauw);
	if (t.Find(&lIdent)) {

		TR_OCLLock l(t);
		if (!l)
			return lIdent;

		TR_OBJTree *pObj = l->OBJ();
		if ( !l->OBJ())
			return lIdent;
		*lCount = *lCount + l->OBJ()->Count();
		CTable d(*pObj);
		long lNum = *_pObj;
		for (d.First();d.Valid();d.Next()) {
			TR_OBJLock e(d);
			lNum++;
			*(_pObj+lNum) = e->Object();
		}
		*_pObj = lNum;
	}
	return lIdent;
}
//--------------------------------------------------------------------------
//-------------------------Auswahl FlaechenTypen----------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

GebietsFlaechen :: GebietsFlaechen (pWindow pW, uint res, ResourceFile &RF)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
		_Alle ( this, IDC_RADIOALLEFLAECHEN),
		_Gemeinde( this, IDC_RADIOGEMEINDE),
		_Behoerde ( this, IDC_RADIOBEHOERDE),
		_Bezirk ( this, IDC_RADIOSCHAUBEZIRK),
		_Einzug ( this, IDC_RADIOEINZUGSGEBIET),
	       OKButton (this, IDOK)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	_iTyp = cAlleFlaechen;	// Alle Flaechen

	_Alle.SetState(true);
	_Gemeinde.SetState(false);
	_Behoerde.SetState(false);
	_Bezirk.SetState(false);
	_Einzug.SetState(false);

	return;
}

#pragma warning (default: 4355)


GebietsFlaechen :: ~GebietsFlaechen (void)
{

}

//----------------------------------------------------------------------

void _XTENSN_EXPORT GebietsFlaechen :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		EndDlg(1);
		}
		break;

		case IDC_RADIOALLEFLAECHEN:
		{
		_Alle.SetState(true);
		_Gemeinde.SetState(false);
		_Bezirk.SetState(false);
		_Behoerde.SetState(false);
		_Einzug.SetState(false);
		_iTyp = cAlleFlaechen;
		}
		break;



		case IDC_RADIOGEMEINDE:
		{
		_Alle.SetState(false);
		_Gemeinde.SetState(true);
		_Bezirk.SetState(false);
		_Behoerde.SetState(false);
		_Einzug.SetState(false);
		_iTyp = cGemeindenFlaeche;
		}
		break;


		case IDC_RADIOBEHOERDE:
		{
		_Alle.SetState(false);
		_Gemeinde.SetState(false);
		_Bezirk.SetState(false);
		_Behoerde.SetState(true);
		_Einzug.SetState(false);
		_iTyp = cBehoerdenFlaeche;
		}
		break;


		case IDC_RADIOSCHAUBEZIRK:
		{
		_Alle.SetState(false);
		_Gemeinde.SetState(false);
		_Bezirk.SetState(true);
		_Behoerde.SetState(false);
		_Einzug.SetState(false);
		_iTyp = cSchaubezirkFlaeche;
		}
		break;

		case IDC_RADIOEINZUGSGEBIET:
		{
		_Alle.SetState(false);
		_Gemeinde.SetState(false);
		_Bezirk.SetState(false);
		_Behoerde.SetState(false);
		_Einzug.SetState(true);
		_iTyp = cEinzugsgebietsFlaeche;
		}
		break;


	}
	return;
}
//---------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------KOMPGEW.CXX-------------------------------------
