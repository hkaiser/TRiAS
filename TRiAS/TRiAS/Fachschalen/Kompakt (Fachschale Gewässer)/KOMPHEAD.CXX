// KOMPAKT-HEADER 
// File: KOMPHEAD.CXX

#include "kompp.hxx"

#include "kompdef.h"
// BasicScript
#include <eb.h>
#include <ibscript.hxx>

#include <igeometr.hxx>
#include "triasdef.h"
#include "kompdll.hxx" 
#include "cobjtree.hxx"

#include "gewbaum.hxx"
#include "kompias.hxx"

#include "kompias.hxx"
#include "komphead.hxx"
#include "kpstatus.hxx"
#include "version.h"
#include "kompias.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//---------------------------------------------------------------------------
KompaktHeader :: KompaktHeader ( ResourceFile *pResTarget )
{
	_pResTarget = pResTarget;
//------------------------------------------------------
	_pGewClass = NULL;
	_MCGewNr = _MCGewKl = _MCGewName = 0L;
	_lProzentL = 0L;
// KK010809
	_lSchrittweite = _lPuffer = 1L;

	// KK010726
	_iProzFlag = false;		// MeterAngabe

//-------------------------------------------------------
	_pBauwClass = NULL;
	_MCBauwNr = _MCBauwKl = _MCBauwName = 0L;
	_MCBauwAnfStat = _MCBauwEndStat = _MCBauwAnlNr = _MCBauwBez = 0L;
	_MCBauwStauziel = _MCBauwWasserSp = _MCBauwSensib = _MCBauwArt = _MCBauwLeist = 0L;
//-------------------------------------------------------
	_pHydrClass = NULL;
	_MCHydrWert = _MCHydrKl = _MCHydrHoehe = 0L;
//-------------------------------------------------------
	_pFlaClass = NULL;
	_MCFlaKl = 0L;

//------Counter------------------------------------------
	_lGewCount = 0L;
	_lBWCount = 0L;

	_isValid = false;

	_pLocProt = NULL;
	_pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();

#if _MSC_VER >= 1100
	_hPr = NULL;
	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
#endif


//-----HeaderEintag Gew + Bauwerke + Hydro
	if (!GetHeaderInformation())
		return;

// Möglichkeit suchen, Objektklassendefinitionen zu säubern
	CleanOKS();

	_isValid = true;
//-----Klassen zusammensuchen---------------------------
	SetzeBauwerkeKlassen();
	SetzeLeistungsKlassen();
	SetzeTopKlassen();
	SetzeGewaesserKlassen();
	SetzeHydraulikKlassen();

	_pGewClass = LadeKompaktKlassen ( _MCGewKl,PM_GEWAESSER);
	LadeObjektMCode(PM_GEWAESSER);

	_pBauwClass = LadeKompaktKlassen (_MCBauwKl,PM_BAUWERKE);
	LadeObjektMCode(PM_BAUWERKE);

	_pHydrClass = LadeKompaktKlassen (_MCHydrKl,PM_HYDRAULIK);
	LadeObjektMCode(PM_HYDRAULIK);

	_pFlaClass = LadeKompaktKlassen (_MCFlaKl,PM_FLAECHEN);
	LadeObjektMCode(PM_FLAECHEN);

}
//-------------------------------------------------------------------------
KompaktHeader :: ~KompaktHeader (void)
{
	DELETE_OBJ ( _pGewClass);
	DELETE_OBJ ( _pBauwClass);
	DELETE_OBJ ( _pHydrClass);
	DELETE_OBJ ( _pFlaClass);
}
////////////////DEFINITIONEN/////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: CleanOKS ( void )
{

	TR_OKSTree *pOKSTree = new TR_OKSTree;
	if (!pOKSTree)
		return;

	ENUMLONGKEY ENK;

	ENK.eKey = 'i';
	ENK.eFcn = (ENUMNOKEYLONGPROC) FillOKSListBox;
	ENK.ePtr = pOKSTree;
	
	DEX_EnumPBDData(ENK);

	if ( pOKSTree->Count() > 0L) {

		CTable t ( *pOKSTree);

		for ( t.First(); t.Valid(); t.Next()) {
			TR_OKSLock l(t);
			if (l->UIdent2() != 0L ) {
				OKSCleaner(l->UIdent1(),l->UIdent2());
			}
		}

	}

	DELETE_OBJ(pOKSTree);

}
//-------------------------------------------------------
void KompaktHeader :: OKSCleaner ( ulong lIdent1, ulong lIdent2 )
{

	PBDDATA pbdData;

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = NULL;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 0;

	IDENTOBJECTCOUNT IDC;
	memset (&IDC, '\0', sizeof(IDENTOBJECTCOUNT));
	IDC.dwSize = sizeof(IDENTOBJECTCOUNT);
	IDC.iOTypes = OTPunkt|OTLinie|OTFlaeche|OTText;
	IDC.ulIdent = lIdent1;

	long lCount1 = DEX_GetIdentObjectCount(IDC);

	IDC.ulIdent = lIdent2;
	long lCount2 = DEX_GetIdentObjectCount(IDC);

	if ( lCount1 < lCount2)
		pbdData.pbdCode = lIdent1;
	else
		pbdData.pbdCode = lIdent2;

#if _MSC_VER < 1200
	DEX_DeleteAllIdentObjects(pbdData.pbdCode);
	DEX_DelPBDData (pbdData);

//	char * pT = new char [_MAX_PATH];
//	if ( pT ) {
//		wsprintf ( pT," ID1 = %ld / ID2 = %ld : gelöscht : %ld ",lIdent1,lIdent2,pbdData.pbdCode);
//		MessageBox (0,pT,"OKSCleaner",MB_OK);
//		DELETE_OBJ(pT);
//	}

#else
	HPROJECT hPro = DEX_GetObjectsProject(pbdData.pbdCode);
	DEX_DeleteAllIdentObjects(pbdData.pbdCode);
	DEX_DelPBDDataEx (hPro,pbdData);

#endif


}
//-------------------------------------------------------
void KompaktHeader :: SetzeBauwerkeKlassen ( void )
{
	short iHk = cBauwerkeIdent;

	short iZuo;

	iZuo = cBauwerkeSchoepfwerke;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeStauanlagen;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeRechte;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeKreuzungen;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeSohlbauwerke;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeSchaechte;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeOekologie1;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeRohrleitungen;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeDurchlaesse;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeOekologie2;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeBebauungLinks;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeBebauungRechts;
	BildeBauwerkeKlassen(iHk,iZuo);

	iZuo = cBauwerkeEinmuendung;
	BildeBauwerkeKlassen(iHk,iZuo);

	return;
}
//-------------------------------------------------------
void KompaktHeader :: BildeBauwerkeKlassen ( short iHk, short iZuo )
{
	
	ulong lIdent = KompaktIdentifikatorEx (_pLocProt,iHk,iZuo);

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	if (0L == lIdent ) {
		wsprintf(KText," H%ld Z%ld abgelehnt\n",iHk,iZuo);
		KompaktProtokoll(_pLocProt,KText);
		return;
	}

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;

	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
//#else
//	_hPr = DEX_GetObjectsProject(lIdent);
//	if (_hPr > 0 ) {
//		if (DEX_GetPBDDataEx (_hPr,pbdData) == EC_OKAY) 
//			return;
//	} else
//		_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

#endif

	}

	char *pLText = new char [_MAX_PATH];
	if ( !pLText)
		return;
	*pLText = '\0';

// --------------------Bauwerke -----------------------------------------

	if (iHk == cBauwerkeIdent) {
		if (iZuo == cBauwerkeSchoepfwerke)
			strcat ( pLText,  ResString (ResID(IDS_SCHOEPFWERKE,_pResTarget),40));
		if (iZuo == cBauwerkeStauanlagen)
			strcat ( pLText,  ResString (ResID(IDS_STAUANLAGEN,_pResTarget),40));
		if (iZuo == cBauwerkeRechte)
			strcat ( pLText,  ResString (ResID(IDS_RECHTE,_pResTarget),40));
		if (iZuo == cBauwerkeKreuzungen)
			strcat ( pLText,  ResString (ResID(IDS_KREUZUNGEN,_pResTarget),40));
		if (iZuo == cBauwerkeSohlbauwerke)
			strcat ( pLText,  ResString (ResID(IDS_SOHLBAUWERKE,_pResTarget),40));
		if (iZuo == cBauwerkeSchaechte)
			strcat ( pLText,  ResString (ResID(IDS_SCHAECHTE,_pResTarget),40));
		if (iZuo == cBauwerkeOekologie1)
			strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE1,_pResTarget),40));
		if (iZuo == cBauwerkeRohrleitungen)
			strcat ( pLText,  ResString (ResID(IDS_ROHRLEITUNGEN,_pResTarget),40));
		if (iZuo == cBauwerkeDurchlaesse)
			strcat ( pLText,  ResString (ResID(IDS_DURCHLAESSE,_pResTarget),40));
		if (iZuo == cBauwerkeOekologie2)
			strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE2,_pResTarget),40));
		if (iZuo == cBauwerkeBebauungLinks)
			strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGLINKS,_pResTarget),40));
		if (iZuo == cBauwerkeBebauungRechts)
			strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGRECHTS,_pResTarget),40));
		if (iZuo == cBauwerkeEinmuendung)
			strcat ( pLText,  ResString (ResID(IDS_EINMUENDUNG,_pResTarget),40));
		if ( iZuo < cBauwerkeSchoepfwerke || iZuo > cBauwerkeEinmuendung )
			MessageBox ( __hWndM ,"Hilfe", "Hilfe", MB_OK);
	}


//--------------------------------------------------------------------
	strncpy ( KText,pLText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pLText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (_hPr,pbdData); 
#endif


	DEXN_PBDIdentsChanged();
	}

	strcat (pLText,"\n");

	KompaktProtokoll ( _pLocProt, pLText);

	DELETE_OBJ (pLText);

	return;
}
///////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetzeLeistungsKlassen ( void )
{

	short iHk = cLeistungenUnterhaltung;
	SetzeLeistungsEinzelKlasse(iHk);

	iHk = cLeistungenAusschreibung;
	SetzeLeistungsEinzelKlasse(iHk);

	iHk = cLeistungenAuftrag;
	SetzeLeistungsEinzelKlasse(iHk);

	iHk = cLeistungenAufmass;
	SetzeLeistungsEinzelKlasse(iHk);

	return;
}
///////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetzeLeistungsEinzelKlasse ( short iHk )
{

	short iZuo;

	iZuo = cLeistZuordnungRandStreifen;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungRandStreifen;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungBoeschungLinks;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungBoeschungRechts;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungBoeschungBeide;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungBoeschungTeilprofil;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungSohlkrautung;
	BildeLeistungsKlassen(iHk,iZuo);
	
	iZuo = cLeistZuordnungGrundraeumung;
	BildeLeistungsKlassen(iHk,iZuo);

	iZuo = cLeistZuordnungStundenStueckLohn;
	BildeLeistungsKlassen(iHk,iZuo);

	return;
}
//--------------------------------------------------------
//-------------------------------------------------------
void KompaktHeader :: BildeLeistungsKlassen ( short iHk, short iZuo )
{

	ulong lIdent = KompaktIdentifikatorEx (_pLocProt,iHk,iZuo);

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	if (0L == lIdent ) {
		wsprintf(KText," H%ld Z%ld abgelehnt\n",iHk,iZuo);
		KompaktProtokoll(_pLocProt,KText);
		return;
	}

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;

	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
//#else
//	if ( _hPr > 0 ) {
//		if (DEX_GetPBDDataEx (_hPr,pbdData) == EC_OKAY) 
//			return;
//	} else
//		_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

#endif

	}

	char *pLText = new char [_MAX_PATH];
	if ( !pLText)
		return;
	*pLText = '\0';

// --------------------Leistungen -----------------------------------------

	if (iHk == cLeistungenUnterhaltung) 
		strcat ( pLText,  ResString (ResID(IDS_IDUNTERHALTUNG,_pResTarget),40));

	if (iHk == cLeistungenAusschreibung) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUSSCHREIBUNG,_pResTarget),40));

	if (iHk == cLeistungenAuftrag) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUFTRAG,_pResTarget),40));

	if (iHk == cLeistungenAufmass) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUFMASS,_pResTarget),40));


//-----------------Untergruppen---------------------------------------

	if (iZuo == cLeistZuordnungRandStreifen) 
		strcat ( pLText,  ResString (ResID(IDS_IDRANDSTREIFEN,_pResTarget),40));

	if (iZuo == cLeistZuordnungBoeschungLinks) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGLINKS,_pResTarget),40));

	if (iZuo == cLeistZuordnungBoeschungRechts) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGRECHTS,_pResTarget),40));

	if (iZuo == cLeistZuordnungBoeschungBeide) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGBEIDE,_pResTarget),40));

	if (iZuo == cLeistZuordnungBoeschungTeilprofil) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGTEILPROFIL,_pResTarget),40));

	if (iZuo == cLeistZuordnungSohlkrautung) 
		strcat ( pLText,  ResString (ResID(IDS_IDSOHLKRAUTUNG,_pResTarget),40));

	if (iZuo == cLeistZuordnungGrundraeumung) 
		strcat ( pLText,  ResString (ResID(IDS_IDGRUNDRAEUMUNG,_pResTarget),40));

	if (iZuo == cLeistZuordnungStundenStueckLohn) 
		strcat ( pLText,  ResString (ResID(IDS_IDSTUNDENSTUECKLOHN,_pResTarget),40));

//--------------------------------------------------------------------
	strncpy ( KText,pLText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pLText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (_hPr,pbdData); 
#endif

	DEXN_PBDIdentsChanged();
	}

	strcat (pLText,"\n");
	KompaktProtokoll ( _pLocProt,pLText);

	DELETE_OBJ (pLText);

	return;
}
///////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetzeTopKlassen ( void)
{
	char *pText = new char [_MAX_PATH];
	char *pKey = new char [_MAX_PATH];
	if (!pText || !pKey) {
		DELETE_OBJ(pText);
		DELETE_OBJ(pKey);
		return;
	}


//	Grenzen -------------------------------------

	strcpy (pKey,ResString(ResID(IDS_DEFGEMEINDEKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEMEINDE,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFLANDGEMEINDEKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFLANDGEMEINDE,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFSTADTGEMEINDEKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFSTADTGEMEINDE,_pResTarget),60));
	BildeTopKlassen(pKey,pText);


	strcpy (pKey,ResString(ResID(IDS_DEFGEMARKUNGKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEMARKUNG,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFFLURKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFFLUR,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFFLURSTUECKKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFFLURSTUECK,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFGRUNDSTUECKKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGRUNDSTUECK,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

//----------------------------------------------------------
//	Schutzgebiete

	strcpy (pKey,ResString(ResID(IDS_DEFWASSERSCHUTZKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFWASSERSCHUTZ,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFNATURSCHUTZKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFNATURSCHUTZ,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFNATIONALPARKKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFNATIONALPARK,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFLANDSCHAFTSCHUTZKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFLANDSCHAFTSCHUTZ,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

//--------------------------------------------------------------------
	DELETE_OBJ (pText);
	DELETE_OBJ (pKey);
}
/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: BildeTopKlassen ( char *pKey, char *pText )
{
	if (!pKey || *pKey == '\0' || !pText || *pText == '\0')
		return;

	char Ident[MAX_OKS_LENX + 1];
	strcpy (Ident,pKey);

	ulong rIdent = 0L;


	
#if _MSC_VER < 1100
	IdentFromClassX ( Ident,&rIdent);
#else
	HRESULT hr = IdentFromClassX ( _hPr,Ident,&rIdent,true);
	if (hr == S_OK )
		return;			// OKS vorhanden
#endif

	long lIdent = (long) rIdent;

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;

	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100

	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
//#else
//	if ( _hPr > 0 ) {
//		if (DEX_GetPBDDataEx (_hPr,pbdData) == EC_OKAY) 
//			return;
//	} else
//		_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

#endif

	}

	strncpy ( KText,pText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (_hPr,pbdData); 
#endif

	DEXN_PBDIdentsChanged();
	}

	return;
}
///////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetzeGewaesserKlassen ( void)
{
	char *pText = new char [_MAX_PATH];
	char *pKey = new char [_MAX_PATH];
	if (!pText || !pKey) {
		DELETE_OBJ(pText);
		DELETE_OBJ(pKey);
		return;
	}

	strcpy (pKey,ResString(ResID(IDS_DEFGEWAESSER1KEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEWAESSER1,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFGEWAESSER2KEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEWAESSER2,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFGEWKANALKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEWKANAL,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

	strcpy (pKey,ResString(ResID(IDS_DEFGEWGRABENKEY,_pResTarget),35));
	strcpy ( pText,ResString(ResID(IDS_DEFGEWGRABEN,_pResTarget),60));
	BildeTopKlassen(pKey,pText);

//--------------------------------------------------------------------
	DELETE_OBJ(pKey);
	DELETE_OBJ (pText);
}
/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: BildeGewaesserKlassen ( long lFIdent, char *pText )
{
	if (lFIdent == 0L || !pText || *pText == '\0')
		return;

	char Ident[MAX_OKS_LENX + 1];
	ulong rIdent = (ulong)lFIdent;

	wsprintf ( Ident,"%ld",rIdent);

	
#if _MSC_VER < 1100
	IdentFromClassX ( Ident,&rIdent);
#else
	HRESULT hr = IdentFromClassX ( _hPr,Ident,&rIdent,true);
	if ( hr == S_OK )
		return;
#endif

	long lIdent = (long) rIdent;

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;

	{
	ErrInstall EI (WC_NOIDENT);


#if _MSC_VER < 1100
	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
//#else
//	if ( _hPr > 0 ) {
//		if (DEX_GetPBDDataEx (_hPr,pbdData) == EC_OKAY) 
//			return;
//	} else
//		_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();


#endif

	}

	strncpy ( KText,pText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (_hPr,pbdData); 
#endif

	DEXN_PBDIdentsChanged();
	}

	return;
}
////////////////DEFINITIONEN-HYDRAULIK/////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetzeHydraulikKlassen ( void )
{
	short iHk = cHydraulikHochwasser;

	short iZuo;

	iZuo = cUeberschwemmungsPunkt;
	BildeHydraulikKlassen(iHk,iZuo);

	iZuo = cUeberschwemmungsGebiet;
	BildeHydraulikKlassen(iHk,iZuo);


	return;
}
//---------------------------------------------------------------------
void KompaktHeader :: BildeHydraulikKlassen ( short iHk, short iZuo )
{
	
	ulong lIdent = KompaktIdentifikatorEx (_pLocProt,iHk,iZuo);

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	if (0L == lIdent ) {
		wsprintf(KText," H%ld Z%ld abgelehnt\n",iHk,iZuo);
		KompaktProtokoll(_pLocProt,KText);
		return;
	}

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;

	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
//#else
//	_hPr = DEX_GetObjectsProject(lIdent);
//	if (_hPr > 0 ) {
//		if (DEX_GetPBDDataEx (_hPr,pbdData) == EC_OKAY) 
//			return;
//	} else
//		_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

#endif

	}

	char *pLText = new char [_MAX_PATH];
	if ( !pLText)
		return;
	*pLText = '\0';

// --------------------Hydraulik -----------------------------------------

	if (iHk == cHydraulikHochwasser) {
		strcat ( pLText,  ResString (ResID(IDS_IDHYDRAULIK,_pResTarget),40));
		if (iZuo == cUeberschwemmungsPunkt)
			strcat ( pLText,  ResString (ResID(IDS_IDUEBERSCHWEMMUNGSPUNKT,_pResTarget),80));
		if (iZuo == cUeberschwemmungsGebiet)
			strcat ( pLText,  ResString (ResID(IDS_IDUEBERSCHWEMMUNGSGEBIET,_pResTarget),80));
	}


//--------------------------------------------------------------------
	strncpy ( KText,pLText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pLText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (_hPr,pbdData); 
#endif


	DEXN_PBDIdentsChanged();
	}

	strcat (pLText,"\n");

	KompaktProtokoll ( _pLocProt, pLText);

	DELETE_OBJ (pLText);

	return;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//-------------------------------------------------------
void KompaktHeader :: SetValidation ( char * pLocProt )
{

	if ( !_pLocProt && pLocProt)
		_pLocProt = pLocProt;

	if (!SetHeaderInformation()) {
		_isValid = false;
		return;
	}

	_isValid = true;

//-----Klassen zusammensuchen---------------------------
//	_pGewClass = LadeKompaktKlassen ( _MCGewKl,PM_GEWAESSER);
//	_pBauwClass = LadeKompaktKlassen (_MCBauwKl,PM_BAUWERKE);
//	_pHydrClass = LadeKompaktKlassen (_MCHydrKl,PM_HYDRAULIK);
//	_pFlaClass = LadeKompaktKlassen (_MCFlaKl,PM_FLAECHEN);

	SetzeBauwerkeKlassen();
	SetzeLeistungsKlassen();
	SetzeTopKlassen();
	SetzeGewaesserKlassen();
	SetzeHydraulikKlassen();

}
//-------------------------------------------------------
void KompaktHeader :: Aktualisieren ( short iTyp )
{


//-----Klassen zusammensuchen---------------------------
	if ( iTyp == PM_GEWAESSER) {
		if ( _pGewClass)
			DELETE_OBJ ( _pGewClass);
		_pGewClass = LadeKompaktKlassen ( _MCGewKl,iTyp);
		LadeObjektMCode(PM_GEWAESSER);
	}

	if ( iTyp == PM_BAUWERKE) {
		if ( _pBauwClass)
			DELETE_OBJ ( _pBauwClass);


		_pBauwClass = LadeKompaktKlassen (_MCBauwKl,iTyp);


		LadeObjektMCode(PM_BAUWERKE);
	}

	if ( iTyp == PM_HYDRAULIK) {
		if ( _pHydrClass)
			DELETE_OBJ ( _pHydrClass);
		_pHydrClass = LadeKompaktKlassen (_MCHydrKl,iTyp);
		LadeObjektMCode(PM_HYDRAULIK);
	}
	
	if ( iTyp == PM_FLAECHEN) {
		if ( _pFlaClass)
			DELETE_OBJ ( _pFlaClass);
		_pFlaClass = LadeKompaktKlassen (_MCFlaKl,iTyp);
		LadeObjektMCode(PM_FLAECHEN);
	}
	
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
bool KompaktHeader :: Name ( char *pBuffer, short lLen)
{
	bool iFlag = false;
	if(!pBuffer)
		return iFlag;

	*pBuffer = '\0';

	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
//	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTNAME,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTNAME,&g_pTE->RF()),HEADERKEYSIZE +1),HEADERKEYSIZE);
	hdrEntry.lphdrText = pBuffer;
	hdrEntry.hdrTextLen = lLen;
	hdrEntry.dwFlags = HEADER_READONLY;

	#if _MSC_VER >= 1100
		if (DEX_ReadGeoDBHdrEntryEx (_hPr,hdrEntry) == EC_OKAY) 
	#else
		if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) 
	#endif


	// HeaderEintrag existiert
		iFlag = true;

	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}

	return iFlag;
}
//////////////////////////////////////////////////////////////////
long KompaktHeader :: GewaesserCount ( void )
{
	long lCount = _lGewCount;
	if ( lCount > 0L)
		return lCount;

	lCount = 0L;

	if ( !_pGewClass || _pGewClass->Count() == 0)
		return lCount;

	CTable t (*_pGewClass);

	CEierUhr Wait (g_pTE->MVWind());
	long lNum = _pGewClass->Count();

//	CStatus *pStatus = new CStatus ( g_pTE->MVWind(), _pResTarget, lNum,  ResString (ResID(IDS_GEWAESSERCODE, _pResTarget),50).Addr());
//	pStatus->Show();

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) EnumeriereObjekte;
	long lCnt = 0L;

//------------GewaesserKlassen laden ----------------------------

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();
		ELK.eKey = lIdent;
		ELK.ePtr = &lCount;
		lCnt++;
//		if ( pStatus) 
//			pStatus->SetValue(lCnt, lCount);

		DEX_EnumIdentObjects(ELK);
	}

//	DELETE_OBJ(pStatus);

	_lGewCount = lCount;

	return lCount;

}
//////////////////////////////////////////////////////////////////
long KompaktHeader :: BauwerkeCount ( void )
{
	long lCount = _lBWCount;
	if (lCount > 0L)
		return lCount;

	lCount = 0L;

	if ( !_pBauwClass || _pBauwClass->Count() == 0)
		return lCount;

	CTable t (*_pBauwClass);

	CEierUhr Wait (g_pTE->MWind());

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) EnumeriereObjekte;

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();
		ELK.eKey = lIdent;
		ELK.ePtr = &lCount;
		DEX_EnumIdentObjects(ELK);
	}
	_lBWCount = lCount;
	return lCount;

}
//////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void KompaktHeader :: StoreGewClass ( TR_OCLTree *pClass)
{
	if ( _pGewClass)
		DELETE_OBJ (_pGewClass);
	_pGewClass = pClass;
}
//------------------------------------------------------------------
void KompaktHeader :: StoreBauwClass ( TR_OCLTree *pClass)
{
	if ( _pBauwClass)
		DELETE_OBJ (_pBauwClass);
	_pBauwClass = pClass;
}
//------------------------------------------------------------------
void KompaktHeader :: StoreHydrClass ( TR_OCLTree *pClass)
{
	if ( _pHydrClass)
		DELETE_OBJ (_pHydrClass);
	_pHydrClass = pClass;
}
//------------------------------------------------------------------
void KompaktHeader :: StoreFlaClass ( TR_OCLTree *pClass)
{
	if ( _pFlaClass)
		DELETE_OBJ (_pFlaClass);
	_pFlaClass = pClass;
}
//---------------------------------------------------------------------
void KompaktHeader :: DeleteGewClass ( void)
{
	if ( _pGewClass)
		DELETE_OBJ (_pGewClass);
	_pGewClass = NULL;
	_lGewCount = 0L;
}
//------------------------------------------------------------------
void KompaktHeader :: DeleteBauwClass ( void)
{
	if ( _pBauwClass)
		DELETE_OBJ (_pBauwClass);
	_pBauwClass = NULL;
	_lBWCount = 0L;
}
//------------------------------------------------------------------
void KompaktHeader :: DeleteHydrClass ( void)
{
	if ( _pHydrClass)
		DELETE_OBJ (_pHydrClass);
	_pHydrClass = NULL;
}
//------------------------------------------------------------------
void KompaktHeader :: DeleteFlaClass ( void)
{
	if ( _pFlaClass)
		DELETE_OBJ (_pFlaClass);
	_pFlaClass = NULL;
}
//--------------------------------------------------------------------
void KompaktHeader :: LadeObjektMCode ( short iTyp)
{


	if ( iTyp == PM_GEWAESSER) {

		if ( !_pGewClass)
			return;

		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCGewName,ResString(ResID(IDS_GEWAESSERMCODENAME,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwAnfStat,ResString(ResID(IDS_ANFANGSSTATION,_pResTarget),50),iTyp);
		return;

	}

	if ( iTyp == PM_BAUWERKE) {

		if(! _pBauwClass)
			return;

		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwNr,ResString(ResID(IDS_BAUWERKEMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwName,ResString(ResID(IDS_BAUWERKEMCODENAME,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwAnfStat,ResString(ResID(IDS_ANFANGSSTATION,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwEndStat,ResString(ResID(IDS_ENDSTATION,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwAnlNr,ResString(ResID(IDS_ANLAGENUMMER,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwBez,ResString(ResID(IDS_BEZEICHNUNG,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwStauziel,ResString(ResID(IDS_STAUZIEL,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwWasserSp,ResString(ResID(IDS_WASSERSPIEGEL,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwSensib,ResString(ResID(IDS_SENSIBILITAETSSTUFE,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwArt,ResString(ResID(IDS_ARTFAUNAFLORA,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwLeist,ResString(ResID(IDS_LEISTUNGSART,_pResTarget),50),iTyp);
		return;
	}


	if ( iTyp == PM_HYDRAULIK) {

		if(!_pHydrClass)
			return;

		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwAnfStat,ResString(ResID(IDS_ANFANGSSTATION,_pResTarget),50),iTyp);
		SetPBDMCode (_MCHydrHoehe,ResString(ResID(IDS_HYDRAULIKMCODEHOEHE,_pResTarget),50),iTyp);
		SetPBDMCode (_MCHydrWert,ResString(ResID(IDS_HYDRAULIKMCODEWERT,_pResTarget),50),iTyp);
		return;

	}

//	if ( iTyp == PM_FLAECHEN) {

//	}

	if ( iTyp == PM_LEISTUNGEN) {


		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwAnfStat,ResString(ResID(IDS_ANFANGSSTATION,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwEndStat,ResString(ResID(IDS_ENDSTATION,_pResTarget),50),iTyp);
		SetPBDMCode (_MCBauwLeist,ResString(ResID(IDS_LEISTUNGSART,_pResTarget),50),iTyp);
		return;
	}

	return;

}
//--------------------------------------------------------------------
void KompaktHeader :: LadeObjektCode ( short iTyp)
{

	char *pMerkmal;
	ulong lMCode = 0L;
	TR_OCLTree *pClass;

	if ( iTyp == PM_GEWAESSER) {
		pClass = _pGewClass;
		lMCode = _MCGewKl;
	}

	if ( iTyp == PM_BAUWERKE) {
		pClass = _pBauwClass;
		lMCode = _MCBauwKl;
	}


	if ( iTyp == PM_HYDRAULIK) {
		pClass = _pHydrClass;
		lMCode = _MCHydrKl;
	}

	if ( iTyp == PM_FLAECHEN) {
		pClass = _pFlaClass;
		lMCode = _MCFlaKl;
	}

	if ( !pClass)
		return;

	CTable t (*pClass);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		pMerkmal = HoleIdentMerkmal( l->Ident(),lMCode);
		if (pMerkmal)
			break;
	}

	if ( BestimmeAltMerkmalsKode ( iTyp, pMerkmal)) {
		TauscheMerkmal ( iTyp );
	}
		

	DELETE_OBJ ( pMerkmal);

//----------IdentMerkmale aktualisieren------------------------

	char *pHDR = GetHeaderTypEintrag ( iTyp);
	if ( pHDR ) {
		for ( t.First(); t.Valid(); t.Next()) {
			TR_OCLLock l(t);
			if ( !l)
				continue;
			AktualisiereIdentMerkmal( l->Ident(),lMCode,pHDR);

		}
	}

}

//////////////////////////////////////////////////////////////////////
void KompaktHeader :: AktualisiereIdentMerkmal ( long lIdent,ulong lMCode,char *pHDR)
{
	if ( lIdent == 0L || !pHDR || lMCode == 0L)
		return;


#if _MSC_VER >= 1100
	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;
#else
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = lIdent;		// ObjektKlasse
	tm.imaxLen = HEADERSIZE +1;
	tm.pMText =pHDR;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long) lMCode;	// MerkmalsCode

	DEX_ModTextMerkmal ( tm );

	return;

}
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------
void KompaktHeader :: BestimmeMerkmalsKode ( short iTyp, char *pMerkmal)
{
	if ( !pMerkmal)
		return;

	if ( iTyp == PM_BAUWERKE ) {
		BestimmeBauwerke ( pMerkmal);
		return;
	}

	char *cptr;
	char *ptr = strchr ( pMerkmal, ';');

	if ( ptr ) {	// 1.Kode = Nr
		*ptr = '\0';
		if ( iTyp == PM_GEWAESSER )
			_MCGewNr = GetHeaderMCode ( pMerkmal);

		if ( iTyp == PM_BAUWERKE )
			_MCBauwNr = GetHeaderMCode ( pMerkmal);

		if ( iTyp == PM_HYDRAULIK )
			_MCHydrHoehe = GetHeaderMCode ( pMerkmal);
			
			
		cptr = ptr + 1;		// 2.Kode = Name

		if ( iTyp == PM_GEWAESSER ) {
			ptr = strchr ( cptr, ';');
		// KK010726
		// Differenz in Meter / in Prozent ( Kommastellen beachten )
			if ( ptr) {
				*ptr = '\0';
				_MCGewName = GetHeaderMCode ( cptr);
				cptr = ptr + 1;

		// KK010809 - nun auch Schrittweite und Puffer möglich

				_iProzFlag = false;

				if ('P' == *cptr) {
					_iProzFlag = true;
					cptr++;
				}

				ptr = strchr ( cptr, ';');

				if ( ptr) {
					*ptr = '\0';
					_lProzentL = atol ( cptr);
					cptr = ptr + 1;
					ptr = strchr ( cptr, ';');
					if ( ptr) {
						*ptr = '\0';
						_lSchrittweite = atol ( cptr);
						cptr = ptr + 1;
						_lPuffer = atol ( cptr);
					}

				} else {
					_lProzentL = atol ( cptr);
				}
			}
		}

		if ( iTyp == PM_BAUWERKE ) {
			_MCBauwName = GetHeaderMCode ( cptr);
		}

		if ( iTyp == PM_HYDRAULIK ) {
			_MCHydrWert = GetHeaderMCode ( cptr);
		}
	} 
}
//---------------------------------------------------------------------
//--------------------------------------------------------------------
bool KompaktHeader :: BestimmeAltMerkmalsKode ( short iTyp, char *pMerkmal)
{
	if ( !pMerkmal)
		return false;

	char *cptr;
	char *ptr = strchr ( pMerkmal, ';');

	if ( ptr ) {	// 1.Kode = Nr
		*ptr = '\0';
		if ( iTyp == PM_GEWAESSER )
			_RFGewNr = GetHeaderMCode ( pMerkmal);

		if ( iTyp == PM_BAUWERKE )
			_RFBauwNr = GetHeaderMCode ( pMerkmal);

		if ( iTyp == PM_HYDRAULIK )
			_RFHydrWert = GetHeaderMCode ( pMerkmal);
			
		cptr = ptr + 1;		// 2.Kode = Name
		if ( iTyp == PM_GEWAESSER ) {
			ptr = strchr ( cptr, ';');
			if ( ptr) {
				*ptr = '\0';
				_RFGewName = GetHeaderMCode ( cptr);
				cptr = ptr + 1;
				// KK010726
				_iProzFlag = false;
				if ('P' == *cptr) {
					_iProzFlag = true;
					cptr++;
				}
				_lProzentL = atol ( cptr);
			}
		}
		if ( iTyp == PM_BAUWERKE ) {
			_RFBauwName = GetHeaderMCode ( cptr);
		}

		if ( iTyp == PM_HYDRAULIK ) {
			_RFHydrHoehe = GetHeaderMCode ( cptr);
		}
	} 
	return true;
}
//---------------------------------------------------------------------
//--------------------------------------------------------------------
void KompaktHeader :: TauscheMerkmal ( short iTyp)
{

	TR_OCLTree *pClass;

	if ( iTyp == PM_GEWAESSER) 
		pClass = _pGewClass;

	
	if ( iTyp == PM_HYDRAULIK) 
		pClass = _pHydrClass;

	
	if ( iTyp == PM_BAUWERKE) 
		pClass = _pBauwClass;

	
	if ( !pClass || pClass->Count() == 0)
		return;

	CTable t (*pClass);

	CEierUhr Wait (g_pTE->MWind());

	MERKMALSWECHSEL MW;
	if ( iTyp == PM_GEWAESSER) {
		MW.lMCodeV1 = _RFGewNr;
		MW.lMCodeV2 = _RFGewName;
		MW.lMCodeZ1 = _MCGewNr;
		MW.lMCodeZ2 = _MCGewName;
	}

	if ( iTyp == PM_HYDRAULIK) {

		MW.lMCodeV1 = _RFHydrHoehe;
		MW.lMCodeV2 = _RFHydrWert;
		MW.lMCodeZ1 = _MCHydrHoehe;
		MW.lMCodeZ2 = _MCHydrWert;
	}

	if ( iTyp == PM_BAUWERKE) {
		MW.lMCodeV1 = _RFBauwNr;
		MW.lMCodeV2 = _RFBauwName;
		MW.lMCodeZ1 = _MCBauwNr;
		MW.lMCodeZ2 = _MCBauwName;
	}

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) ModifiziereObjekte;

//------------GewaesserKlassen laden ----------------------------

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();
		ELK.eKey = lIdent;
		ELK.ePtr = &MW;
		DEX_EnumIdentObjects(ELK);
	}

}
//--------------------------------------------------------------------
#if _MSC_VER >= 1100
long KompaktHeader :: KP_GetUniqueSysMCodeEx ( HPROJECT hPr)
{
	long lMCode = 0L;
	long lMHandle = 0L;
	lMHandle = DEX_GetUniqueSysMCode();
	lMCode = DEX_MapHandleToMCode(lMHandle);
	return lMCode;
}
#endif
//--------------------------------------------------------------------
void KompaktHeader :: BestimmeBauwerke ( char *pMerkmal)
{
	if ( !pMerkmal)
		return;

	char *cptr = pMerkmal;
	char *ptr = strchr ( pMerkmal, ';');

	short i = 0;

#if _MSC_VER >= 1100
	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
#endif

	while ( ptr ) {
		i++;
		*ptr = '\0';

		if ( i == 1 )
			_MCBauwNr = GetHeaderMCode ( cptr);

		if ( i == 2 )
			_MCBauwName = GetHeaderMCode ( cptr);

		if ( i == 3 )
			_MCBauwAnfStat = GetHeaderMCode ( cptr);

		if ( i == 4 )
			_MCBauwEndStat = GetHeaderMCode ( cptr);

		if ( i == 5 )
			_MCBauwAnlNr = GetHeaderMCode ( cptr);

		if ( i == 6 )
			_MCBauwBez = GetHeaderMCode ( cptr);

		if ( i == 7 )
			_MCBauwStauziel = GetHeaderMCode ( cptr);

		if ( i == 8 )
			_MCBauwWasserSp = GetHeaderMCode ( cptr);

		if ( i == 9 )
			_MCBauwSensib = GetHeaderMCode ( cptr);

		if ( i == 10 )
			_MCBauwArt = GetHeaderMCode ( cptr);

		cptr = ptr + 1;		// next
		*ptr = ';';
		ptr = strchr ( cptr, ';');

	}

	short iBase = DEX_GetMkBase();

	if ( i == 9 )  {
	// Noch kein Merkmal MCBauwLeist
		_MCBauwArt = GetHeaderMCode ( cptr);

#if _MSC_VER < 1100
		_MCBauwLeist = DEX_GetUniqueSysMCode();
#else
		_MCBauwLeist = KP_GetUniqueSysMCodeEx(_hPr);
#endif

		ptr = strchr ( pMerkmal, '\0');
		if ( !ptr) 
			return;
				
		if ( iBase == 16 )
			wsprintf (ptr, ";%08lx",_MCBauwLeist);
		else
			wsprintf (ptr, ";%08ld",_MCBauwLeist);

		SetPBDMCode (_MCBauwLeist,ResString(ResID(IDS_LEISTUNGSART,_pResTarget),50),PM_BAUWERKE);

/////////////////////////////////////////////////////////////////

		GEODBHDRENTRYEX hdrEntry;

		hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTBAUWCODE,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);

		hdrEntry.lphdrText = new char [HEADERSIZE +1];
		hdrEntry.hdrTextLen = HEADERSIZE;
		hdrEntry.dwFlags = HEADER_READONLY;

		strcpy( hdrEntry.lphdrText, pMerkmal);

#if _MSC_VER < 1100
		DEX_WriteGeoDBHdrEntry (hdrEntry);
#else
		DEX_WriteGeoDBHdrEntryEx (_hPr,hdrEntry);
#endif

		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
			KompaktProtokoll(_pLocProt,pT);
			DELETE_OBJ(pT);
		}

		DELETE_OBJ ( hdrEntry.lphdrText);
				
	} else {
		_MCBauwLeist = GetHeaderMCode ( cptr);
	}
	
	return;
}
//---------------------------------------------------------------------
char *KompaktHeader :: HoleIdentMerkmal ( long lIdent, ulong lMCode )
{
	if ( lIdent == 0L || lMCode == 0L )
		return NULL;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

#if _MSC_VER >= 1100

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	TARGETMERKMALEX tm;
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;
	tm.iFlags = TMCreateNewTarget;

#else

	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);

#endif


	tm.lTarget = lIdent;		// IdentNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Identifikator;


	if( DEX_GetTextMerkmal ( tm )) {
		return pBuffer;
	}

	DELETE_OBJ ( pBuffer);
	return NULL;

}
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------
// Code für KompaktSystem holen
//-------------------------------------------------------------------

bool KompaktHeader :: GetHeaderInformation (void)
{
	if (!GetHeaderClassInformation())
		return false;

	if (!GetHeaderTypInformation ( PM_GEWAESSER )) {
		if (!SetHeaderTypInformation ( PM_GEWAESSER))
			return false;
		if (!ErfasseAltInformationen(PM_GEWAESSER))
			return false;
	}

	if (!GetHeaderTypInformation ( PM_HYDRAULIK )) {
		if (!SetHeaderTypInformation ( PM_HYDRAULIK))
			return false;
		if (!ErfasseAltInformationen(PM_HYDRAULIK))
			return false;
	}


	if (!GetHeaderTypInformation ( PM_BAUWERKE )) {
		if (!SetHeaderTypInformation ( PM_BAUWERKE))
			return false;
		if (!ErfasseAltInformationen(PM_BAUWERKE))
			return false;
	}

	return true;

}
/////////////////////////////////////////////////////////////////////////
bool KompaktHeader :: GetHeaderClassInformation (void)
{
	bool iFlag = false;

	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTIDENT,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);
	hdrEntry.lphdrText = new char [HEADERSIZE+1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	hdrEntry.dwFlags = HEADER_READONLY;



	_MCGewKl = 0L;
	_MCBauwKl = 0L;
	_MCHydrKl = 0L;
	_MCFlaKl = 0L;


#if _MSC_VER < 1100

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {

#else

	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

	if (DEX_ReadGeoDBHdrEntryEx (_hPr,hdrEntry) == EC_OKAY) {

#endif

	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}

	// HeaderEintrag existiert
	
		iFlag = ClassHeaderAnalyse(&_MCGewKl,&_MCBauwKl,&_MCHydrKl,&_MCFlaKl, hdrEntry.lphdrText);

// KK000418 - Adm.Gebiete + Hydr
//		if ( iFlag && _MCFlaKl == 0L) { // nicht vollstaendig !!
//			iFlag = AktualisiereHeaderParameter(&_MCGewKl,&_MCBauwKl,&_MCHydrKl,&_MCFlaKl);

//		}
	
	}
	DELETE_OBJ (  hdrEntry.lphdrText);
	return iFlag;
}
////////////////////////////////////////////////////////////////////////////
bool KompaktHeader :: ClassHeaderAnalyse (ulong *lM1, ulong *lM2, ulong *lM3, ulong *lM4, char *pString)
{
	bool iFlag = false;

	if ( !pString || *pString == '\0')
		return iFlag;

	*lM1 = *lM2 = *lM3 = *lM4 = 0L;

// ------------------Zeile auseinandernehmen--------------

	char *cptr = pString;
	char *ptr = strchr ( cptr, ';');
	while ( ptr) {
		*ptr = '\0';
		if ( *lM1 == 0L) {
			*lM1 = GetHeaderMCode ( cptr);
			cptr = ptr + 1;
		} else if ( *lM2 == 0L) {
			*lM2 = GetHeaderMCode ( cptr);
			cptr = ptr + 1;
		} else if ( *lM3 == 0L) {
			*lM3 = GetHeaderMCode ( cptr);
			cptr = ptr + 1;
		}
		*ptr = ';';
		ptr = strchr ( cptr, ';');
		iFlag = true;
	}

	if ( *lM1 == 0L) {
		*lM1 = GetHeaderMCode ( cptr);
		iFlag = true;
	} else if ( *lM2 == 0L) {
		*lM2 = GetHeaderMCode ( cptr);
		iFlag = true;
	} else if ( *lM3 == 0L) {
		*lM3 = GetHeaderMCode ( cptr);
		iFlag = true;
	} else if ( *lM4 == 0L) {
		*lM4 = GetHeaderMCode ( cptr);
		iFlag = true;
	}

	return iFlag;
}
////////////////////////////////////////////////////////////////////////////
bool KompaktHeader :: AktualisiereHeaderParameter (ulong *lM1, ulong *lM2, ulong *lM3, ulong *lM4)
{
	bool iFlag = false;

	if ( *lM1 == 0L )
		return iFlag;

	char *pKey = new char [_MAX_PATH];
	if ( !pKey) 
		return iFlag;

// letzten freien MCode besorgen

	short iBase = DEX_GetMkBase();

	if ( iBase == 16 )
		wsprintf (pKey, "%08lx;",*lM1);
	else
		wsprintf (pKey, "%08ld;",*lM1);

	char *ptr = strrchr ( pKey, ';');
	ptr++;

	if ( *lM2 == 0L) 

#if _MSC_VER < 1100
		*lM2 = DEX_GetUniqueSysMCode();
#else
		*lM2 = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	
	if ( iBase == 16 )
		wsprintf (ptr, "%08lx;",*lM2);
	else
		wsprintf (ptr, "%08ld;",*lM2);

	ptr = strrchr ( pKey, ';');
	ptr++;

	if ( *lM3 == 0L) 

#if _MSC_VER < 1100
		*lM3 = DEX_GetUniqueSysMCode();
#else
		*lM3 = KP_GetUniqueSysMCodeEx(_hPr);
#endif
	
	if ( iBase == 16 )
		wsprintf (ptr, "%08lx;",*lM3);
	else
		wsprintf (ptr, "%08ld;",*lM3);

	ptr = strrchr ( pKey, ';');
	ptr++;

	if ( *lM4 == 0L) 

#if _MSC_VER < 1100
		*lM4 = DEX_GetUniqueSysMCode();
#else
		*lM4 = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	if ( iBase == 16 )
		wsprintf (ptr, "%08lx",*lM4);
	else
		wsprintf (ptr, "%08ld",*lM4);



	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTIDENT,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);
	hdrEntry.lphdrText = new char [HEADERSIZE +1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	strcpy( hdrEntry.lphdrText, pKey);
	hdrEntry.dwFlags = HEADER_READONLY;

#if _MSC_VER < 1100
		DEX_WriteGeoDBHdrEntry (hdrEntry);
#else
		DEX_WriteGeoDBHdrEntryEx (_hPr,hdrEntry);
#endif

	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}


	DELETE_OBJ ( hdrEntry.lphdrText);
	SetPBDIDCode ( PM_GEWAESSER, *lM1);
	SetPBDIDCode ( PM_BAUWERKE,*lM2);
	SetPBDIDCode ( PM_HYDRAULIK,*lM3);
	SetPBDIDCode ( PM_FLAECHEN,*lM4);

	DELETE_OBJ ( pKey);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool KompaktHeader :: GetHeaderTypInformation (short iTyp)
{
	bool iFlag = false;

	char *pHDR = GetHeaderTypEintrag ( iTyp);

	if (!pHDR )
		return false;

	BestimmeMerkmalsKode( iTyp, pHDR );

	DELETE_OBJ ( pHDR);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
char *KompaktHeader :: GetHeaderTypEintrag (short iTyp)
{

	char *pHDRText = new char[HEADERSIZE+1];

	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
	hdrEntry.lphdrText = pHDRText;
	hdrEntry.hdrTextLen = HEADERSIZE;
	hdrEntry.dwFlags = HEADER_READONLY;


	if ( iTyp == PM_GEWAESSER )
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTGEWCODE,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);

	if ( iTyp == PM_HYDRAULIK )
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTHYDROCODE,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);

	if ( iTyp == PM_FLAECHEN )
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTFLACODE,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);

	if ( iTyp == PM_BAUWERKE )
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTBAUWCODE,_pResTarget),HEADERKEYSIZE +1),HEADERKEYSIZE);


#if _MSC_VER < 1100
	if (DEX_ReadGeoDBHdrEntry (hdrEntry) != EC_OKAY) {
		DELETE_OBJ ( pHDRText);
		return NULL;
	}
#else
	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (DEX_ReadGeoDBHdrEntryEx (_hPr,hdrEntry) != EC_OKAY) {
		DELETE_OBJ ( pHDRText);
		return NULL;
	}
#endif
	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}

	return pHDRText;
}

/////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
ulong KompaktHeader :: GetHeaderMCode ( char * ptr)
{
	ulong uCode = 0L;
	if (!ptr)
		return uCode;

	short iBase = DEX_GetMkBase();
	if ( iBase == 16 )
		uCode = strtoul ( ptr, NULL, 16 );
	else
		uCode = (ulong) atol (ptr);

	return uCode;
}
//--------------------------------------------------------------------
// Code für KompaktSystem definieren
//-------------------------------------------------------------------
bool KompaktHeader :: SetHeaderInformation (void)
{
	if (!SetHeaderClassInformation())
		return false;

	if (!SetHeaderTypInformation(PM_GEWAESSER))
		return false;

	if (!SetHeaderTypInformation(PM_BAUWERKE))
		return false;

	if (!SetHeaderTypInformation(PM_HYDRAULIK))
		return false;


	return true;
}
			
//-------------------------------------------------------------------
bool KompaktHeader :: SetHeaderClassInformation (void)
{
	char *pKey = new char [_MAX_PATH];
	if ( !pKey) 
		return false;


// letzten freiem MCode besorgen

#if _MSC_VER < 1100
	_MCGewKl = DEX_GetUniqueSysMCode();
#else
	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	_MCGewKl = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	short iBase = DEX_GetMkBase();

	if ( iBase == 16 )
		wsprintf (pKey, "%08lx;",_MCGewKl);
	else
		wsprintf (pKey, "%08ld;",_MCGewKl);

#if _MSC_VER < 1100
	_MCBauwKl = DEX_GetUniqueSysMCode();
#else
	_MCBauwKl = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	char *ptr = strrchr ( pKey, ';');
	if ( !ptr) {
		DELETE_OBJ (pKey);
		return false;
	}
	ptr++;

	if ( iBase == 16 )
		wsprintf (ptr, "%08lx;",_MCBauwKl);
	else
		wsprintf (ptr, "%08ld;",_MCBauwKl);

// KK000419 - Hydr + Admin noch nicht


#if _MSC_VER < 1100
	_MCHydrKl = DEX_GetUniqueSysMCode();
#else
	_MCHydrKl = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	ptr = strrchr ( pKey, ';');
	if ( !ptr) {
		DELETE_OBJ (pKey);
		return false;
	}
	ptr++;

	if ( iBase == 16 )
		wsprintf (ptr, "%08lx;",_MCHydrKl);
	else
		wsprintf (ptr, "%08ld;",_MCHydrKl);

#if _MSC_VER < 1100
	_MCFlaKl = DEX_GetUniqueSysMCode();
#else
	_MCFlaKl = KP_GetUniqueSysMCodeEx(_hPr);
#endif

	ptr = strrchr ( pKey, ';');
	if ( !ptr) {
		DELETE_OBJ (pKey);
		return false;
	}
	ptr++;

	if ( iBase == 16 )
		wsprintf (ptr, "%08lx",_MCFlaKl);
	else
		wsprintf (ptr, "%08ld",_MCFlaKl);


	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTIDENT,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);
	hdrEntry.lphdrText = new char [HEADERSIZE +1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	strcpy( hdrEntry.lphdrText, pKey);
	hdrEntry.dwFlags = HEADER_READONLY;

#if _MSC_VER < 1100
	DEX_WriteGeoDBHdrEntry (hdrEntry);
#else
	DEX_WriteGeoDBHdrEntryEx (_hPr,hdrEntry);
#endif

	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}

	
	DELETE_OBJ ( hdrEntry.lphdrText);
	SetPBDIDCode ( PM_GEWAESSER, _MCGewKl);
	SetPBDIDCode ( PM_BAUWERKE,_MCBauwKl);
	SetPBDIDCode ( PM_HYDRAULIK,_MCHydrKl);
	SetPBDIDCode ( PM_FLAECHEN,_MCFlaKl);
	DELETE_OBJ ( pKey);
	return true;
}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
bool KompaktHeader :: SetHeaderTypInformation ( short iTyp)
{
	char *pKey = new char [_MAX_PATH];
	if ( !pKey) 
		return false;

	SetPBDObjectCode(iTyp);

#if _MSC_VER >= 1100
	_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
#endif

	if ( iTyp == PM_GEWAESSER ) {

// letzten freiem MCode besorgen

	#if _MSC_VER < 1100
		_MCGewNr = DEX_GetUniqueSysMCode();
	#else
		_MCGewNr = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		short iBase = DEX_GetMkBase();

		if ( iBase == 16 )
			wsprintf (pKey, "%08lx;",_MCGewNr);
		else
			wsprintf (pKey, "%08ld;",_MCGewNr);

		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),iTyp);
		SetPBDMCode (_MCGewNr,ResString(ResID(IDS_GEWAESSERMCODENR,_pResTarget),50),PM_BAUWERKE);

	#if _MSC_VER < 1100
		_MCGewName = DEX_GetUniqueSysMCode();
	#else
		_MCGewName = KP_GetUniqueSysMCodeEx(_hPr);
	#endif
		char *ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCGewName);
		else
			wsprintf (ptr, "%08ld;",_MCGewName);

		SetPBDMCode (_MCGewName,ResString(ResID(IDS_GEWAESSERMCODENAME,_pResTarget),50),iTyp);

		_lProzentL = 0;
		
		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;
		if ( _iProzFlag)
			wsprintf (ptr, "P%ld",_lProzentL);
		else
			wsprintf (ptr, "%ld",_lProzentL);

	}
//-----------------Hydraulik-----------------------------------

	if ( iTyp == PM_HYDRAULIK ) {
	
// letzten freiem MCode besorgen

	#if _MSC_VER < 1100
		_MCHydrHoehe = DEX_GetUniqueSysMCode();
	#else
		_MCHydrHoehe = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		short iBase = DEX_GetMkBase();

		if ( iBase == 16 )
			wsprintf (pKey, "%08lx;",_MCHydrHoehe);
		else
			wsprintf (pKey, "%08ld;",_MCHydrHoehe);

		SetPBDMCode (_MCHydrHoehe,ResString(ResID(IDS_HYDRAULIKMCODEHOEHE,_pResTarget),50),iTyp);


	#if _MSC_VER < 1100
		_MCHydrWert = DEX_GetUniqueSysMCode();
	#else
		_MCHydrWert = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		char *ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx",_MCHydrWert);
		else
			wsprintf (ptr, "%08ld",_MCHydrWert);

		SetPBDMCode (_MCHydrWert,ResString(ResID(IDS_HYDRAULIKMCODEWERT,_pResTarget),50),iTyp);

	}

//-----------------Bauwerke------------------------------------

	if ( iTyp == PM_BAUWERKE ) {

// letzten freiem MCode besorgen

	#if _MSC_VER < 1100
		_MCBauwNr = DEX_GetUniqueSysMCode();
	#else
		_MCBauwNr = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		short iBase = DEX_GetMkBase();

		if ( iBase == 16 )
			wsprintf (pKey, "%08lx;",_MCBauwNr);
		else
			wsprintf (pKey, "%08ld;",_MCBauwNr);

		SetPBDMCode (_MCBauwNr,ResString(ResID(IDS_BAUWERKEMCODENR,_pResTarget),50),iTyp);

	#if _MSC_VER < 1100
		_MCBauwName = DEX_GetUniqueSysMCode();
	#else
		_MCBauwName = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		char *ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwName);
		else
			wsprintf (ptr, "%08ld;",_MCBauwName);

		SetPBDMCode (_MCBauwName,ResString(ResID(IDS_BAUWERKEMCODENAME,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwAnfStat = DEX_GetUniqueSysMCode();
	#else
		_MCBauwAnfStat = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwAnfStat);
		else
			wsprintf (ptr, "%08ld;",_MCBauwAnfStat);

		SetPBDMCode (_MCBauwAnfStat,ResString(ResID(IDS_ANFANGSSTATION,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwEndStat = DEX_GetUniqueSysMCode();
	#else
		_MCBauwEndStat = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwEndStat);
		else
			wsprintf (ptr, "%08ld;",_MCBauwEndStat);

		SetPBDMCode (_MCBauwEndStat,ResString(ResID(IDS_ENDSTATION,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwAnlNr = DEX_GetUniqueSysMCode();
	#else
		_MCBauwAnlNr = KP_GetUniqueSysMCodeEx(_hPr);
	#endif


		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwAnlNr);
		else
			wsprintf (ptr, "%08ld;",_MCBauwAnlNr);

		SetPBDMCode (_MCBauwAnlNr,ResString(ResID(IDS_ANLAGENUMMER,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwBez = DEX_GetUniqueSysMCode();
	#else
		_MCBauwBez = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwBez);
		else
			wsprintf (ptr, "%08ld;",_MCBauwBez);

		SetPBDMCode (_MCBauwBez,ResString(ResID(IDS_BEZEICHNUNG,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwStauziel = DEX_GetUniqueSysMCode();
	#else
		_MCBauwStauziel = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwStauziel);
		else
			wsprintf (ptr, "%08ld;",_MCBauwStauziel);

		SetPBDMCode (_MCBauwStauziel,ResString(ResID(IDS_STAUZIEL,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwWasserSp = DEX_GetUniqueSysMCode();
	#else
		_MCBauwWasserSp = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwWasserSp);
		else
			wsprintf (ptr, "%08ld;",_MCBauwWasserSp);

		SetPBDMCode (_MCBauwWasserSp,ResString(ResID(IDS_WASSERSPIEGEL,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwSensib = DEX_GetUniqueSysMCode();
	#else
		_MCBauwSensib = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwSensib);
		else
			wsprintf (ptr, "%08ld;",_MCBauwSensib);

		SetPBDMCode (_MCBauwSensib,ResString(ResID(IDS_SENSIBILITAETSSTUFE,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwArt = DEX_GetUniqueSysMCode();
	#else
		_MCBauwArt = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx;",_MCBauwArt);
		else
			wsprintf (ptr, "%08ld;",_MCBauwArt);


		SetPBDMCode (_MCBauwArt,ResString(ResID(IDS_ARTFAUNAFLORA,_pResTarget),50),iTyp);

//------------------------------------------------------------

	#if _MSC_VER < 1100
		_MCBauwLeist = DEX_GetUniqueSysMCode();
	#else
		_MCBauwLeist = KP_GetUniqueSysMCodeEx(_hPr);
	#endif

		ptr = strrchr ( pKey, ';');
		if ( !ptr) {
			DELETE_OBJ (pKey);
			return false;
		}
		ptr++;

		if ( iBase == 16 )
			wsprintf (ptr, "%08lx",_MCBauwLeist);
		else
			wsprintf (ptr, "%08ld",_MCBauwLeist);


		SetPBDMCode (_MCBauwLeist,ResString(ResID(IDS_LEISTUNGSART,_pResTarget),50),iTyp);

	}

/////////////////////////////////////////////////////////////////

	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);

	if ( iTyp == PM_GEWAESSER)
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTGEWCODE,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);

	if ( iTyp == PM_BAUWERKE)
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTBAUWCODE,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);

	if ( iTyp == PM_HYDRAULIK)
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTHYDROCODE,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);

	if ( iTyp == PM_FLAECHEN)
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTFLACODE,_pResTarget),HEADERKEYSIZE+1),HEADERKEYSIZE);

	hdrEntry.lphdrText = new char [HEADERSIZE +1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	hdrEntry.dwFlags = HEADER_READONLY;

	strcpy( hdrEntry.lphdrText, pKey);

	#if _MSC_VER < 1100
		DEX_WriteGeoDBHdrEntry (hdrEntry);
	#else
		DEX_WriteGeoDBHdrEntryEx (_hPr,hdrEntry);
	#endif

	char *pT = new char [_MAX_PATH];
	if (pT) {
		*pT = '\0';
		wsprintf(pT," - HeaderDef Key %s  <=> Wert %s\n",hdrEntry.hdrKey,hdrEntry.lphdrText);
		KompaktProtokoll(_pLocProt,pT);
		DELETE_OBJ(pT);
	}


	DELETE_OBJ ( hdrEntry.lphdrText);
	DELETE_OBJ ( pKey);
	return true;
}
///////////////////////////////////////////////////////////////////////////
bool KompaktHeader :: ErfasseAltInformationen ( short iTyp) 
{

	if ( iTyp == PM_GEWAESSER) {
		if (!_pGewClass)
			_pGewClass = LadeKompaktKlassen( _MCGewKl,iTyp);
		if (!_pGewClass)
			return false;
		LadeObjektCode (PM_GEWAESSER);
		return true;
	}

	if ( iTyp == PM_HYDRAULIK) {
		if (!_pHydrClass)
			_pHydrClass = LadeKompaktKlassen( _MCHydrKl,iTyp);
		if (!_pHydrClass)
			return false;
		LadeObjektCode (PM_HYDRAULIK);

		return true;
	}

	if ( iTyp == PM_BAUWERKE) {
		if (!_pBauwClass)
			_pBauwClass = LadeKompaktKlassen( _MCBauwKl,iTyp);
		if (!_pBauwClass)
			return false;
		LadeObjektCode (PM_BAUWERKE);

		return true;
	}


	return false;
}
//------------------------------------------------------------------
// MCode für GewNr in PBD setzen
//-------------------------------------------------------------------
void KompaktHeader :: SetPBDMCode (long MCode, ResString rs, short iTyp)
{
	char KText[TEXTLEN];
	KText[0] = NULL;

	if ( 0L == MCode) {
		char *pText = new char [_MAX_PATH];
		if ( pText ) {
			wsprintf (pText,ResString (ResID(IDS_ERRKPHEADEROBEIG, &g_pTE->RF()),80),rs);

			MessageBox (__hWndM,
			 pText,
			 ResString (ResID(IDS_KOMPAKTHEADER, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE_OBJ(pText);
		} else {
			MessageBox (__hWndM,
			 ResString (ResID(IDS_ERRKPHEADEROBEIG, &g_pTE->RF()),80),
			 ResString (ResID(IDS_KOMPAKTHEADER, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);
		}

		return;
	}

#if _MSC_VER >= 1100

PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

	TR_OCLTree *pClass;

	if ( iTyp == PM_GEWAESSER)
		pClass = GewClass();

	if ( iTyp == PM_BAUWERKE)
		pClass = BauwClass();

	if ( iTyp == PM_HYDRAULIK)
		pClass = HydrClass();

	if ( iTyp == PM_FLAECHEN)
		pClass = FlaClass();
	if (!pClass)
		return;

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


	CTable t (*pClass);

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();
		pbdData.lIdent = lIdent;

		DefineFeatureSet ( &pbdData);

/*-----------
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);

// Test, ob OE bereits definiert
		long lRefCode = DEX_GetMCodeFromFeatureNameEx(hPr,KText);

		if ( hPr == _hPr && 0L != lRefCode && lRefCode == MCode)
			continue;
		if ( hPr != _hPr && 0L != lRefCode )
			continue;

		if (lRefCode != 0L && lRefCode != MCode) {
			if ( _hPr == hPr)
				((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);

			{
			ErrInstall EI (WC_NOMERKMAL);
				if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
					continue;
				else
					DEXN_PBDMCodeChanged (MCode);
			}
		}

		if (0L == lRefCode ) {		// nicht in Datenquelle
			long lNewCode = MCode;
			if ( _hPr != hPr ) {
				lNewCode = DEX_GetUniqueSysMCode();
			}

			if ( 0L == lNewCode)
				continue;

			pbdData.pbdCode = lNewCode;

			{
			ErrInstall EI (WC_NOMERKMAL);
				if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
					continue;
				else
					DEXN_PBDMCodeChanged (MCode);
			}

		}
-------------------------------------------*/
		
	}
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
	return;

}
// MCode für GewNr in PBD setzen
//-------------------------------------------------------------------
void KompaktHeader :: SetPBDObjectCode (short iTyp)
{
	char KText[TEXTLEN];
	KText[0] = NULL;

	long MCode = 51100000;

	TR_OCLTree *pClass;

	if ( iTyp == PM_GEWAESSER)
		pClass = GewClass();

	if ( iTyp == PM_BAUWERKE)
		pClass = BauwClass();

	if ( iTyp == PM_HYDRAULIK)
		pClass = HydrClass();

	if ( iTyp == PM_FLAECHEN)
		pClass = FlaClass();

	if (!pClass)
		return;

	CTable t (*pClass);


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

	strcat ( KText, "Objektname");

	pbdData.pbdKText = KText;
	pbdData.ipbdMTyp = MPObjectFeature;	
	pbdData.ipbdMLen = 256;


#if _MSC_VER >= 1100


//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();

		MCode = DEX_GetObjNameMCode(lIdent);
		pbdData.pbdCode = MCode;
		
		_hPr = DEX_GetObjectsProject(lIdent);

		pbdData.lIdent = lIdent;


		DefineFeatureSet(&pbdData);

	/*-------------------------------
// Test, ob OE bereits definiert
		long lRefCode = DEX_GetMCodeFromFeatureNameEx(_hPr,KText);
		if (lRefCode != 0L && lRefCode != MCode)
			((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);

		{
		ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (_hPr,pbdData) != EC_OKAY)
				continue;
			else
				DEXN_PBDMCodeChanged (MCode);
		}
		

  --------------------------------------*/

	}
	return;

#else
	t.First();
	TR_OCLLock l(t);

	long lIdent = l->Ident();

	MCode = DEX_GetObjNameMCode(lIdent);
	pbdData.pbdCode = MCode;

	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (MCode);
	}

#endif
}
//------------------------------------------------------------------
// Code für IDCode in PBD setzen
//-------------------------------------------------------------------
void KompaktHeader :: SetPBDIDCode ( short iTyp, long MCode)
{
	char KText[TEXTLEN];
	KText[0] = NULL;

#if _MSC_VER >= 1100

PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

	TR_OCLTree *pClass;

	if ( iTyp == PM_GEWAESSER)
		pClass = GewClass();

	if ( iTyp == PM_BAUWERKE)
		pClass = BauwClass();

	if ( iTyp == PM_HYDRAULIK)
		pClass = HydrClass();

	if ( iTyp == PM_FLAECHEN)
		pClass = FlaClass();
	if (!pClass)
		return;

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
		strcat ( KText,  ResString (ResID(IDS_GEWAESSERCODE,_pResTarget),40));
	if ( iTyp == PM_BAUWERKE)
		strcat ( KText,  ResString (ResID(IDS_BAUWERKECODE,_pResTarget),40));
	if ( iTyp == PM_HYDRAULIK)
		strcat ( KText,  ResString (ResID(IDS_HYDRAULIKCODE,_pResTarget),40));
	if ( iTyp == PM_FLAECHEN)
		strcat ( KText,  ResString (ResID(IDS_FLAECHENCODE,_pResTarget),40));

	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.ipbdMTyp = MPIdentFeature | PBDMERKMAL_SYSTEMFLAG;	
	pbdData.ipbdMLen = 256;


#if _MSC_VER >= 1100


	CTable t (*pClass);

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long lIdent = l->Ident();

		_hPr = DEX_GetObjectsProject(lIdent);

		pbdData.lIdent = lIdent;


		DefineFeatureSet(&pbdData);

/*------------------------------------
// Test, ob OE bereits definiert
		long lRefCode = DEX_GetMCodeFromFeatureNameEx(_hPr,KText);
		if (lRefCode != 0L && lRefCode != MCode)
			((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);

		{
			ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (_hPr,pbdData) != EC_OKAY) {
				continue;
			} else {
				char *pT = new char [_MAX_PATH];
				if (pT) {
					*pT = '\0';
					wsprintf(pT," - ID-Def Ident %ld MCode %ld Wert %s\n",lIdent,MCode,KText);
					KompaktProtokoll(_pLocProt,pT);
					DELETE_OBJ(pT);
				}
				DEXN_PBDMCodeChanged (MCode);
			}
		}

  -------------------------------------*/

		
	}
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
//---------------------------------------------------------------------
TR_OCLTree *KompaktHeader :: LadeKompaktKlassen ( ulong lMCode , short iTyp)
{


	if ( lMCode == 0L)
		return NULL;

	CEierUhr Wait (g_pTE->MVWind());

	TR_OCLTree *pKPClass = new TR_OCLTree;

	if ( !pKPClass)
		return NULL;

//------------KompaktKlassen laden ----------------------------
//--------------alle Idents nach Code..Kl durchsuchen
//	Alle O'Klassen formal durchzählen und Baum anlegen

//-------vorher HeaderEintrag pruefen------------------------------------

	GEWAESSERKLASSE GK;
	GK.pTRGew = pKPClass;
	GK.lGewCode = lMCode;
	GK.iTyp = iTyp;

// KK000418 - Daten für 3.0 pro Typ datenquellenweise aufbereiten !!!

	ENUMNOKEYLONG ENL;
//	Bestimmen der Anzahl der Objektklassen
	ENL.eFcn = ( ENUMNOKEYLONGPROC) SucheKompaktKlassen;
	ENL.ePtr = &GK;

#if _MSC_VER >= 1100

// Für 3.0 je Typ datenquellenweise

	ulong lIDCode = 0L;

	if ( iTyp == PM_GEWAESSER || iTyp == PM_BAUWERKE ) {
		DEX_EnumClasses(_hPr,ENL); 
	}

	if ( iTyp == PM_FLAECHEN || iTyp == PM_HYDRAULIK ) {

		ENUMNOKEY EN;
		//	Bestimmen der Anzahl der Datenquellen

		EN.eFcn = ( ENUMNOKEYPROC) SucheKompaktDaten;
	//	EN.ePtr = &_DataClass;
		EN.ePtr = &GK;

		DEX_EnumDataSourceHandles(EN);

	}
		
#else
	DEX_EnumIdents(ENL);
#endif

	if ( pKPClass->Count() == 0) {
		DELETE_OBJ ( pKPClass);
		return NULL;
	} else
		return pKPClass;
}
	
//----------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// File: KOMPHEAD.CXX
