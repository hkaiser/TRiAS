//-----------KOMPAKT-MEMBER : Eintragen von Bauwerken Kompakt/Trias----------
// File: KPBAUW.CXX


#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "kompdef.h"
#include <ienumonr.hxx>	// CEnumObjectsByNumber

#include <igeometr.hxx>
#include "triasdef.h"
//#include <smartif.h>
//#include <iterenum.h>

#include <trelguid.h>
#include <operguid.h>

#include "kompdll.hxx" 
#include "komphead.hxx"
#include "gewbaum.hxx"

#include "cobjtree.hxx"
#include "ctopobj.hxx"

#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------------
//Member
//----------------------------------------------------------------------
long CKompiasExtension :: KompaktBauwerkEx ( LPARAM p)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = (long) p;
	long lONr = -1L;
	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE || OS.iObjTyp == OT_PUNKT) {
			if ( ObjektIstBauwerk(OS.lONr)) {
				lONr = OS.lONr;	// ON wurde angefasst
			} else {
				if ( ObjektWirdBauwerk (OS.lONr)) {
					lONr = OS.lONr;	// erstes Objekt der Klasse
					m_pKH->Aktualisieren(PM_BAUWERKE);
				}
			}
		}
	}
	}
	return lONr;
}
//---------------------------------------------------------------------


//----------------------------------------------------------------------
long CKompiasExtension :: KompaktBauwerk ( LPARAM p)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = (long) p;
	long lONr = -1L;
	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE || OS.iObjTyp == OT_PUNKT) {
			if ( ObjektIstBauwerk(OS.lONr)) {
				lONr = OS.lONr;	// ON wurde angefasst
			}
		}
	}
	}
	return lONr;
}
//---------------------------------------------------------------------
// KK010808
// Bauwerke über Puffer einfangen
bool CKompiasExtension :: SetInBauwerksKataster ( long lOBauw,long lOGew)
{
	if ( lOBauw == lOGew)
		return false;
	if ( lOBauw == 0L || lOBauw == -1L)
		return false;
	if ( lOGew == 0L || lOGew == -1L)
		return false;

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

		m_lONrBauw = lOBauw;
		m_lONrGew = lOGew;

		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		m_isBauw = true;

//		if ( SetzeKompaktName (lOBauw,1)) {
//			m_isBauw = true;
//		}

		if(!BestimmeBauwerk(m_hWnd, true)) {	// Kompaktname nach Kilometrierung

			m_lONrBauw = -1L;
			m_lONrGew = -1L;
			m_lONr = -1L;
			m_isBauw = false;
			return false;
		}
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		return true;

}
//---------------------------------------------------------------------
bool CKompiasExtension :: BestimmeBauwerk(HWND hWnd, bool iflag)
{

	if ( !m_pAbst)
		return false;
	m_isBauw = false;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  m_lONrGew;
	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return false;
		if ( !ObjektIstGewaesser(OS.lONr))
			return false;

	} else {
		return false;
	}
	}
//------------Interface ------------------------------------
//	ObjektGeometrie der Kante holen - m_pIOG
	if ( !LadeObjektGeometrie ( m_lONrGew))
		return false;
	

	OS.lONr =  m_lONrBauw;
	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE && OS.iObjTyp != OT_PUNKT) 
			return false;
		if ( !ObjektIstBauwerk(OS.lONr)) {
			if (!ObjektWirdBauwerk(OS.lONr))
				return false;
		}
	} else {
		return false;
	}
	}

	OBJGEOMETRIE OG;
	long *pX = new long [OS.lCnt];
	long *pY = new long [OS.lCnt];
    
	if (pX == NULL || pY == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}

	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = m_lONrBauw;
	OG.lCnt = OS.lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = ~OGConverted;
	if (!DEX_GetObjGeometrie (OG)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}

	double dAbstand = 0.0;
	double dEndStand = 0.0;


	char * pBuffer = new char [_MAX_PATH];
	if (!pBuffer) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}
	// Hier offensichtlich CHANGED angesprungen !!

	HRESULT hr = m_pAbst->DistanceFromOrigin_Geom(m_pIOG,pX,pY,&dAbstand);
	if (FAILED(hr)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}

	if ( OS.iObjTyp == OT_KANTE )  {
//		hr = m_pAbst->DistanceFromOrigin_Geom(m_pIOG,pX+1,pY+1,&dEndStand);
		hr = m_pAbst->DistanceFromOrigin_Geom(m_pIOG,pX+OS.lCnt-1,pY+OS.lCnt-1,&dEndStand);
		if (FAILED(hr)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return false;
		}
		if ( dEndStand < dAbstand ) {
			double dRef = dAbstand;
			dAbstand = dEndStand;
			dEndStand = dRef;
		}

		double dDist = dEndStand - dAbstand;
		IObjektGeometrie *pIOG = NULL;

		HRESULT hr = m_pAbst->LinePart ( m_pIOG,*pX,*pY,*(pX+OS.lCnt-1),*(pY+OS.lCnt-1),dDist, &pIOG);

		if (FAILED(hr)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return false;
		}

		KoOrd *plXK, *plYK;
		long lSPAnz;

		pIOG -> GetX ((void**)&plXK);
		pIOG -> GetY ((void**)&plYK);
		pIOG -> GetCnt (&lSPAnz);

		OG.lONr = m_lONrBauw;
		OG.iObjTyp = OS.iObjTyp;
		OG.lCnt = lSPAnz;
		OG.pdblX = plXK;
		OG.pdblY = plYK;
		OG.iFlags = OGModObject;

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		DEX_ModObjGeometrie (OG);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

		pIOG->Release();

		m_pKH->Aktualisieren(PM_BAUWERKE);


	} else {

// Korrigiertes Objekt ablegen

		OG.lONr = m_lONrBauw;
		OG.iObjTyp = OS.iObjTyp;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.iFlags = OGModObject;

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

		DEX_ModObjGeometrie (OG);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	}

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);



	*pBuffer = '\0';
	char *pGewNr = HoleGewaesserNummer (m_lONrGew,m_pKH->CodeGewNr());
	long lStartPunkt =  ObjektStartPunkt(m_lONrGew,m_pKH->CodeBauwAnfStat());

	
// KK010808
// Bauwerke (OKS) - Kurztext liefern

	PBDDATA pbdData;
	char KText[TEXTLEN+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = KText;
	pbdData.pbdLTextLen = 0;

	long Ident = DEX_GetObjIdent(m_lONrBauw);

	pbdData.pbdCode = Ident;
	KText[0] = '\0';
	pbdData.pbdKTextLen = sizeof(KText) -1;

#if _MSC_VER < 1100
		DEX_GetPBDData (pbdData);
#else
		HPROJECT hPr = DEX_GetObjectsProject(Ident);
		DEX_GetPBDDataEx (hPr,pbdData);
#endif




//-----------------------------------------------------------------------
// KK010808
//-----------------------------------------------------------------------

	if ( m_iComment) {

		if ( OS.iObjTyp == OT_PUNKT )
			wsprintf( pBuffer, ResString( ResID( IDS_BAUWERKKILOMETER,&g_pTE->RF()),90),pGewNr,(long) (dAbstand + 0.5)+lStartPunkt);
//		wsprintf( pBuffer, ResString( ResID( IDS_BAUWERKKILOMETER,&g_pTE->RF()),90),pGewNr,(long) (dAbstand + 0.5),(long) ( dEndStand - dAbstand + 0.5));
//		wsprintf (pBuffer," Gewässer %s \n Ereignis an Kilometrierungspunkt %ld \n\n Ereignis übernehmen ?",pGewNr,(long) (dAbstand + 0.5),(long) ( dEndStand - dAbstand + 0.5));
		else
			wsprintf( pBuffer, ResString( ResID( IDS_LENBAUWERKKILOMETER,&g_pTE->RF()),90),pGewNr,(long) (dAbstand + 0.5)+lStartPunkt,(long) ( dEndStand - dAbstand + 0.5));
//		wsprintf( pBuffer, ResString( ResID( IDS_LENBAUWERKKILOMETER,&g_pTE->RF()),90),pGewNr,(long) (dAbstand + 0.5),(long) ( dEndStand - dAbstand + 0.5));
//		wsprintf (pBuffer," Gewässer %s \n Ereignis an Kilometrierungspunkt %ld \n Länge %ld m\n Ereignis übernehmen ?",pGewNr,(long) (dAbstand + 0.5),(long) ( dEndStand - dAbstand + 0.5));


		char *pUeb = new char [_MAX_PATH];

		int flag = 0;

		if (pUeb ) {

			if ( '\0' == KText[0] )
				strcat(pUeb,ResString( ResID( IDS_BILDEEREIGNISSE,&g_pTE->RF()),90));
			else
				wsprintf( pUeb, ResString( ResID( IDS_BILDEEREIGNISSEEX,&g_pTE->RF()),90),KText);


			flag = MessageBox (hWnd,
				 pBuffer,
				 pUeb,
//			 ResString (ResID(IDS_BILDEEREIGNISSE, &RF()),50),
				 MB_YESNO|MB_ICONEXCLAMATION);

			DELETE_OBJ(pUeb);
		}

		if ( flag == IDNO ) {
			DELETE_OBJ (pBuffer);
			DELETE_OBJ (pGewNr);
//		DEX_DeleteObject(m_lONrBauw);
			return false;
		}

// Hier BauwerkeTypAbfrage bei iflag = true
		if ( iflag ) {
			SetzeKompaktName (m_lONrBauw,1);

		}

	}	// m_iComment


	KompaktProtokoll ( m_pLocProt,pBuffer);


	*pBuffer = '\0';
	wsprintf (pBuffer,"%ld",(long) (dAbstand + 0.5)+lStartPunkt);

	m_pKH->Aktualisieren(PM_BAUWERKE);


	ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwAnfStat(),pBuffer);
	if ( OS.iObjTyp == OT_PUNKT) {
		ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwEndStat(),pBuffer);
	} else {
		wsprintf (pBuffer,"%ld",(long) (dEndStand + 0.5)+lStartPunkt);
		ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwEndStat(),pBuffer);
	}

	ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeGewNr(),pGewNr);


	char *pFeat = HoleMerkmalsWert(m_lONrBauw,m_pKH->CodeBauwAnlNr());

	if ( pFeat && *pFeat != '\0') {
		strcpy(pBuffer,pFeat);
	} else {
		long lIdent = DEX_GetObjIdent ( m_lONrBauw);
		ulong lSMCode = DEX_GetObjNameMCode(lIdent);
		GetStandardMCode ( m_lONrBauw, lSMCode, pBuffer);
		if ( pBuffer && *pBuffer != '\0') {
			ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwAnlNr(),pBuffer);
			ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwBez(),pBuffer);
		}
	}

	DELETE_OBJ(pFeat);

	char * pRef = new char [_MAX_PATH];
	if ( pRef) {
		*pRef = '\0';
		strcat ( pRef,pGewNr);	// GewNr
		strcat ( pRef, ";");
		strcat ( pRef,pBuffer);	// AnlNr
		strcat ( pRef, ";");
		*pBuffer = '\0';
		wsprintf (pBuffer,"%ld",(long) (dAbstand + 0.5)+lStartPunkt);
		strcat ( pRef, pBuffer);
		strcat ( pRef, ";");
		if ( OS.iObjTyp == OT_PUNKT) {
			strcat ( pRef, pBuffer);
		} else {
			wsprintf (pBuffer,"%ld",(long) (dEndStand + 0.5)+lStartPunkt);
			strcat ( pRef, pBuffer);
		}
		strcat ( pRef, ";");

		char *pFeat = HoleMerkmalsWert(m_lONrBauw,m_pKH->CodeBauwBez());

		if ( pFeat && *pFeat != '\0') {
			strcat(pRef,pFeat);
		}

		DELETE_OBJ(pFeat);

		ModifiziereMerkmal ( m_lONrBauw,m_pKH->CodeBauwNr(),pRef);

		DELETE_OBJ (pRef);
	}


//	m_pKH->Aktualisieren(PM_BAUWERKE);

	DELETE_OBJ ( pBuffer);
	DELETE_OBJ (pGewNr);

	m_iFunction = KP_BAUWZUKOMPAKT;

	if ( !KompaktFunktion ( m_iFunction, hWnd)) {
		return false;
	}

// Objekt in ORFenster ablegen
	if ( m_isNewOR ) {

		long *pObj = new long [2];
		*pObj = 1;
		*(pObj + 1) = m_lONrBauw;
		short Flag = ROSortObjNr;
		CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_BAUWNUMMER, &RF()),50).Addr(), 0, 255, 255);
		DELETE_OBJ(pObj);
		m_isNewOR = false;
	}

	DEX_RePaint();

	return true;
}
/////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
bool CKompiasExtension :: DefineEreignisObjekt ( long lONr)
{
	m_lONr = -1;

	if ( lONr == -1L || lONr == 0L )
		return false;

	OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {

	// Für V3 Datenquellen prüfen !!
#if _MSC_VER >= 1100
			HPROJECT hPr = NULL;
			long lIdent = DEX_GetObjIdent(lONr);
			hPr = DEX_GetObjectsProject(lIdent);

			if ( !GetKompaktInformation (hPr))			// Kein Kataster angelegt
				return false;

			if ( m_pKH) {
				if ( hPr != m_pKH->HKompaktProject() )
					DELETE_OBJ(m_pKH);
			}

			m_hPr = hPr;		// Handle an Ext -> an Header
			if (!m_pKH)
				m_pKH = new KompaktHeader ( &RF());

#endif
	

			KatasterLaden();

			if ( m_pKH ) {
				if ( !m_pKH->BauwClass())
					m_pKH->Aktualisieren (PM_BAUWERKE);
			}


			if ( OS.iObjTyp == OT_PUNKT) {

				if ( ObjektIstBauwerk (OS.lONr)) {
					m_lONr = OS.lONr;
					return true;
				}
			}

			if ( OS.iObjTyp == OT_KANTE) {

				if ( !ObjektIstBauwerk ( OS.lONr))
					return false;
				m_lONr = OS.lONr;
				return true;
			}
	}
	return false;

}
/////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
bool CKompiasExtension :: ObjektIstBauwerk ( long lONr)
{
	if (lONr == -1L || lONr == 0L )
		return false;
	if ( !m_pKH)
		return false;

	if ( !m_pKH->BauwClass())
		return false;

	long lIdent = DEX_GetObjIdent ( lONr);

	TR_OCLTree *pBauwClass = m_pKH->BauwClass();

	CTable t (*pBauwClass);

//------------BauwerkKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( lIdent == Ident)
			return true;
	}

// KK011024 - Abschwächung
//	if ( ObjektWirdBauwerk ( lONr))
//		return true;

	return false;
}
/////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
bool CKompiasExtension :: BauwerksIdentifikator ( long lIdent)
{
	if ( !m_pKH)
		return false;

	if ( !m_pKH->BauwClass())
		return false;

	if (lIdent == -1L || lIdent == 0L )
		return false;

	TR_OCLTree *pBauwClass = m_pKH->BauwClass();

	CTable t (*pBauwClass);

//------------BauwerkKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( lIdent == Ident)
			return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
bool CKompiasExtension :: GewaesserIdentifikator ( long lIdent)
{
	if ( !m_pKH)
		return false;

	if ( !m_pKH->GewClass())
		return false;

	if (lIdent == -1L || lIdent == 0L )
		return false;

	TR_OCLTree *pGewClass = m_pKH->GewClass();

	CTable t (*pGewClass);

//------------BauwerkKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( lIdent == Ident)
			return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------
bool CKompiasExtension :: ObjektWirdBauwerk ( long lONr)
{

	if (lONr == -1L || lONr == 0L )
		return false;

	if ( !m_pKH)
		return false;

	long lIdent = DEX_GetObjIdent ( lONr);

	char NewIdent[MAX_OKS_LENX+1];

#if _MSC_VER < 1100
	ClassFromIdentX ( lIdent, NewIdent);
#else
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	if ( hPr != AktuellesProjekt())
		return false;

	ClassFromIdentX ( hPr,lIdent, NewIdent);
#endif

	
	long RefIdent = atol(NewIdent+1);	
	RefIdent = RefIdent/1000L;
	if ( (short)RefIdent == cBauwerkeIdent) {
		StoreBauwerkIdentFeature(lIdent);
		return true;
	}

	return false;
}
////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: StoreGewIdentFeature ( long Ident) 
{
	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;

	*pMText = '\0';

	short iBase = DEX_GetMkBase();

	if ( iBase == 16 )
		wsprintf (pMText, "%08lx;%08lx",m_pKH->CodeGewNr(),m_pKH->CodeGewName());
	else
		wsprintf (pMText, "%08ld;%08ld",m_pKH->CodeGewNr(),m_pKH->CodeGewName());


#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(Ident);

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;

	tm.lMCode = (long) m_pKH->CodeGewKl();		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );
	
	DELETE_OBJ ( pMText);
	return;

}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: StoreBauwerkIdentFeature ( long Ident) 
{
	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;


#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(Ident);

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;

	tm.lMCode = (long) m_pKH->CodeBauwKl();		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( NULL == DEX_GetTextMerkmal ( tm )) {


		*pMText = '\0';
		strcat(pMText ,"16");

		if ( EC_OKAY != DEX_ModTextMerkmal ( tm ))
			MessageBox (0,"ModifyIdentMerkmal fehlgeschlagen","KPBauw-StoreBauwerkIdentFeature",MB_ICONSTOP);
	}
	}
	
	DELETE_OBJ ( pMText);
	return;

}
////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//----------KPBAUW.CXX
