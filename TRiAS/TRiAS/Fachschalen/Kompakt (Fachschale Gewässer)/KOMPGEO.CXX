//-----------KOMPAKT-MEMBER : Objektdefinition Kompakt/Trias----------
// File: KOMPGEO.CXX


#include "kompp.hxx"

#include <shellapi.h>
#include <ErrCodes.hxx>

#include <oleguid.h>
#include <dirisole.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "kompdef.h"
#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>
#include "triasdef.h"
#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"

#include "kpstatus.hxx"

#include "version.h"
#include "kompias.h"
#include "about.h"

#include "about.hxx"
#include "cobjtree.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
bool CKompiasExtension :: SpeicherePunktInTrias ( KPTree * pGew)
{
	bool iFlag = false;
	if ( !pGew)
		return iFlag;
	CEierUhr Wait (MVWind());
	CTable t (*pGew);
	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();
	GW.lStartPunkt = 0L;

	for ( t.First(); t.Valid(); t.Next()) {

		KP_GEWLock l(t);
		GW.lONr = l->Objekt();

		if ( !l->GewNr() || *l->GewNr() == '\0') {
			MessageBox (__hWndM,
			 ResString (ResID(IDS_GEWNICHTDEFINIERT, &RF()),80),
			 ResString (ResID(IDS_GEWAESSERUEBERSICHT, &RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			continue;
		}

		if (GW.lONr == -1L || GW.lONr == 0L ) {
			char *pError = new char [_MAX_PATH];
			if ( pError ) {
				wsprintf (pError, ResString (ResID(IDS_ERRNOGEWAESSEROBJEKT, &RF()),80),l->GewNr());
//			wsprintf (pError,"Zum Gewässer '%s' existiert kein Datenbankobjekt !");
				MessageBox (__hWndM,
				 pError,
				 ResString (ResID(IDS_GEWAESSERUEBERSICHT, &RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);
				DELETE_OBJ(pError);
			} else {

				MessageBox (__hWndM,
				 ResString (ResID(IDS_GEWNICHTDEFINIERT, &RF()),80),
				 ResString (ResID(IDS_GEWAESSERUEBERSICHT, &RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);
			}
			continue;
		}


		long lONr = GW.lONr;
		GW.lStartPunkt = ObjektStartPunkt(lONr,m_pKH->CodeBauwAnfStat());
		short Status = DEX_GetObjectType (lONr);

		if ( Status != OGLinie )
			continue;

		GW.lLaenge = l->Ende()-l->Beginn();
		if ( GW.lLaenge <= 0L) {
			long lLen = LinienLaenge(lONr);
			GW.lLaenge = lLen;
		}

		GW.pMText = l->GewNr();
		if ( !PruefeTriasObjekt ( &GW))
			continue;
		if (! LadeTriasObjekt(&GW))
			continue;
		if ( !SpeicherePunkt (&GW, l->LA()))
			continue;
		iFlag = true;
	}
	return iFlag;
}
//------------------------------------------------------------
bool CKompiasExtension :: SpeichereLeistungInTrias ( KPTree * pGew)
{
	bool iFlag = false;

	if ( !pGew)
		return iFlag;

	CEierUhr Wait (MVWind());

	CTable t (*pGew);
	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();
	GW.lStartPunkt = 0L;
	GW.iLinksRechtsMitte = Leist_Mitte;	//default

	short iNum = AnzahlDerLeistungen ( pGew);
	if ( iNum == 0)
		return false;

	m_iCount = 0;

//---------OBJRechercheFenster vorbereiten
	short iNumber = 0;
	long *pObj = new long [ iNum + 1];
	if ( !pObj)
		return false;
	*pObj = 0L;



	m_pStatus = new CStatus ( MVWind(), &RF(), long(iNum),  ResString (ResID(IDS_LEISTUNGEN, &RF()),50).Addr());
	m_pStatus->Show();


    if ( m_pStatus->Break()) {

		MessageBox ( __hWndM ,
		 ResString (ResID(IDS_STOPCONTROL, &RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);

		DELETE_OBJ ( m_pStatus);
		DELETE_OBJ ( pObj);
		return false;
	}

	char *pT = new char [_MAX_PATH];	

	if ( pT) {
		*pT = '\0';
		wsprintf(pT," Leistungen in TRiAS :\n");
		KompaktProtokoll(m_pLocProt,pT);
	}

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		GW.lONr = l->Objekt();

		m_iLeiSchritt = 0;	// Schrittweite definieren

		if ( !l->GewNr() || *l->GewNr() == '\0') {
			if ( pT) {
				*pT = '\0';
				wsprintf(pT," *\tTRiAS-Objektnummer %ld : Gewässernummer nicht definiert\n",GW.lONr);
				KompaktProtokoll(m_pLocProt,pT);
			}

// Originalmeldungen bei SpeicherPunktInTRiAS
//			MessageBox (__hWndM,
//			 "Gewässer nicht definiert !",
//			 "Gewässerübersicht",
//			 MB_OK);
			continue;
		}

		if ( GW.lONr == -1L || GW.lONr == 0L ) {
			if ( pT) {
				*pT = '\0';
				wsprintf(pT," *\tTRiAS-Objektnummer für Gewässer %s nicht definiert\n",l->GewNr());
				KompaktProtokoll(m_pLocProt,pT);
			}

//			MessageBox (__hWndM,
//			 "Gewässer nicht definiert !",
//			 "Gewässerübersicht",
//			 MB_OK);
			continue;
		}


		GW.lStartPunkt = ObjektStartPunkt(GW.lONr,m_pKH->CodeBauwAnfStat());

		GW.pMText = l->GewNr();

		if ( pT) {
			*pT = '\0';
			wsprintf(pT,"\n ***\tGewässernummer %s - Start :\n\n",GW.pMText);
			KompaktProtokoll(m_pLocProt,pT);
		}

		KP_LATree * pLA = l->LA();

		if ( !pLA)
			continue;
		long lONr = GW.lONr;
		short Status = DEX_GetObjectType (lONr);

		if ( Status != OGLinie )
			continue;

		GW.lLaenge = l->Ende()-l->Beginn();

		if ( GW.lLaenge <= 0L) {
			long lLen = LinienLaenge(lONr);
			GW.lLaenge = lLen;
		}

		if ( !PruefeTriasObjekt ( &GW))
			continue;
		if (! LadeTriasObjekt(&GW))
			continue;
		if ( !SpeichereLeistung (&GW, l->LA()))
			continue;
		CTable d (*pLA);
		for ( d.First(); d.Valid(); d.Next()) {
			KP_LALock e(d);
			if ( e->Objekt() > 0L) {
				iNumber++;
				*(pObj+iNumber) = e->Objekt();
			}
		}
		if ( pT) {
			*pT = '\0';
			wsprintf(pT,"\n ***\tGewässernummer %s - Ende \n\n",GW.pMText);
			KompaktProtokoll(m_pLocProt,pT);
		}

		iFlag = true;
	}

	DELETE_OBJ (pT);

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	if ( iNumber > 0 ) {
		*pObj = iNumber;
		short Flag = ROSortObjNr;
		CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_LEISTUNGSLISTE, &RF()),50).Addr(), 255, 255, 0);
	}
	DELETE_OBJ ( pObj);
	return iFlag;
}
//------------------------------------------------------------
//------------------------------------------------------------
bool CKompiasExtension :: SpeichereBauwerkeInTrias ( KPTree * pGew)
{
	bool iFlag = false;
	m_isWork = false;

	if ( !pGew) {
		MessageBox (__hWndM, 
//		 "Keine Bauwerke zuordenbar !",
		 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);
		return iFlag;
	}

	CEierUhr Wait (MVWind());

	CTable t (*pGew);

	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();

	short iNum = AnzahlDerLeistungen ( pGew);
	if ( iNum == 0) {
		MessageBox (__hWndM, 
//		 "Keine Bauwerke zuordenbar !",
		 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	m_iCount = 0;
	m_isWork = true;
//---------OBJRechercheFenster vorbereiten

	short iNumber = 0;
	long *pObj = new long [ iNum + 1];
	if ( !pObj)
		return false;
	*pObj = 0L;


	m_pStatus = new CStatus ( MVWind(), &RF(), long(iNum), ResString (ResID(IDS_BILDEEREIGNISSE, &RF()),50).Addr());
	m_pStatus->Show();


    if ( m_pStatus->Break()) {

		MessageBox ( __hWndM ,
//		"Speichern abgebrochen", 
		 ResString (ResID(IDS_SPEICHERNSTOP, &RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);

		DELETE_OBJ ( m_pStatus);
		DELETE_OBJ ( pObj);
		return false;
	}

	char *pT = new char [_MAX_PATH];	

	if ( pT) {
		*pT = '\0';
		wsprintf(pT,"+++ EreignisÜbernahme in TRiAS-DB :\n");
		KompaktProtokoll(m_pLocProt,pT);
	}

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);

		if ( !l->GewNr() || *l->GewNr() == '\0')
			continue;

		GW.lONr = l->Objekt();
		if ( GW.lONr == -1L || GW.lONr == 0L ) {

			if ( pT) {
				*pT = '\0';
				wsprintf(pT," *\tTRiAS-Objektnummer für Gewässer nicht definiert\n");
				KompaktProtokoll(m_pLocProt,pT);
			}

//		MessageBox (__hWndM,
//		 "Gewässer nicht definiert !",
//		 l->GewNr(),
//		 MB_OK);
			continue;
		}

		if ( !l->GewNr() || *l->GewNr() == '\0') {
			if ( pT) {
				*pT = '\0';
				wsprintf(pT," *\tTRiAS-Objektnummer %ld : Gewässernummer nicht definiert\n",GW.lONr);
				KompaktProtokoll(m_pLocProt,pT);
			}

//			MessageBox (__hWndM,
//			 "Gewässer nicht definiert !",
//			 "Gewässerübersicht",
//			 MB_OK);
			continue;
		}


		GW.pMText = l->GewNr();

		KP_LATree * pLA = l->LA();

		if ( !pLA)
			continue;

		long lONr = GW.lONr;
		short Status = DEX_GetObjectType (lONr);

		if ( pT) {
			*pT = '\0';
			wsprintf(pT," *\tGewässernummer %s - Start :\n",GW.pMText);
			KompaktProtokoll(m_pLocProt,pT);
		}


		if ( Status != OGLinie )
			continue;

		GW.lLaenge = l->Ende()-l->Beginn();
		if ( GW.lLaenge <= 0L ) {
			long lLen = LinienLaenge(lONr);
			GW.lLaenge = lLen;
		}

		if ( !PruefeTriasObjekt ( &GW))
			continue;
		if (! LadeTriasObjekt(&GW))
			continue;
		if ( !SpeichereLeistung (&GW, l->LA()))
			continue;
	    if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
//			"Speichern abgebrochen", 
			 ResString (ResID(IDS_SPEICHERNSTOP, &RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			DELETE_OBJ ( pObj);
			return false;
		}

		CTable d (*pLA);

		for ( d.First(); d.Valid(); d.Next()) {
			KP_LALock e(d);
			if ( e->Objekt() > 0L) {
				long lIdent = DEX_GetObjIdent(e->Objekt());
				SpeichereBauwMerkmal (lIdent);
				iNumber++;
				*(pObj+iNumber) = e->Objekt();
			}
		    if ( m_pStatus->Break()) {

				MessageBox ( __hWndM ,
//				"Speichern abgebrochen", 
				 ResString (ResID(IDS_SPEICHERNSTOP, &RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				DELETE_OBJ ( pObj);
				return false;
			}

		}

		if ( pT) {
			*pT = '\0';
			wsprintf(pT," *\tGewässernummer %s - Ende \n\n",GW.pMText);
			KompaktProtokoll(m_pLocProt,pT);
		}

		iFlag = true;
	}


	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	if ( pT) {
		*pT = '\0';
		wsprintf(pT," *\t *** Aktualisieren Bauwerke ");
		KompaktProtokoll(m_pLocProt,pT);
	}

	m_pKH->Aktualisieren(PM_BAUWERKE);


	if ( iNumber > 0 ) {
		*pObj = iNumber;
		short Flag = ROSortObjNr;
		CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_BAUWERKSLISTE, &RF()),50).Addr(), 0, 255, 255);
	} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);
	}


	DELETE_OBJ (pT);

	DELETE_OBJ ( pObj);

	return iFlag;
}
//----------------------------------------------------------------

//------------------------------------------------------------
short CKompiasExtension :: AnzahlDerLeistungen ( KPTree *pGew)
{
	short iNumber = 0;
	if ( !pGew)
		return iNumber;
	CTable t(*pGew);

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if (!l)
			continue;
		if ( !l->LA())
			continue;
		KP_LATree *pLA = l->LA();
		short iCnt = (short) pLA->Count();
		iNumber = iNumber + iCnt;
	}
	return iNumber;
}
//------------------------------------------------------------
bool CKompiasExtension :: PruefeTriasObjekt ( GEWSTRUKTUR *p)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  p->lONr;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE) 
		return false;
	}
	p->iObjTyp = OS.iObjTyp;
	p->lCnt = OS.lCnt;
	
	if ( OS.lCnt > 0L )
		return true;
	else
		return false;
}
//------------------------------------------------------------------
bool CKompiasExtension :: LadeTriasObjekt ( GEWSTRUKTUR *p )
{
	if (p->lONr == -1L || p->lONr == 0L  || p->lCnt == 0L )
		return false;


	if ( !LadeObjektGeometrie ( p->lONr)) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_STRKEINOBJEKT, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);
		return false;
	}


	// Startpunkt vom BezugsObjekt holen
	p->lStartPunkt = ObjektStartPunkt(p->lONr,m_pKH->CodeBauwAnfStat());

	// als Anfangspunkt für die Kilometrierung den 1. Stützpunkt, als Endpunkt den letzten
	// Stützpunkt von pIOG vorgeben
	KoOrd *plXK, *plYK;
	long lSPAnz;

	m_pIOG -> GetX ((void**)&plXK);
	m_pIOG -> GetY ((void**)&plYK);
	m_pIOG -> GetCnt (&lSPAnz);

// Gewaesser allgemein
	p->lGXA = plXK [0];
	p->lGYA = plYK [0];
	p->lGXE = plXK [lSPAnz-1];
	p->lGYE = plYK [lSPAnz-1];

	p->lXA = plXK [0];
	p->lYA = plYK [0];
	p->lXE = plXK [lSPAnz-1];
	p->lYE = plYK [lSPAnz-1];

	return true;

}

//--------------------------------------------------------------------------
bool CKompiasExtension :: StartWertKorrekt (long lONr, long lBeginn, long lStartPunkt)
{



// StartPunkt des Gewässers prüfen
	if ( lBeginn >= lStartPunkt)
		return true;
	char *pBuffer = new char [_MAX_PATH];
	if (pBuffer) {
		*pBuffer = '\0';
		wsprintf (pBuffer,ResString (ResID(IDS_ABGLEICHGEWAESSER, &RF()),200),lONr,lStartPunkt);

		MessageBox (__hWndM,
		 pBuffer,
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
		 MB_OK);
		DELETE_OBJ ( pBuffer);
	}
	return false;

}
//-------------------------------------------------------------------------
bool CKompiasExtension :: SpeicherePunkt (GEWSTRUKTUR *p, KP_LATree *pLA)
{
	if ( !m_pAbst)
    		return false;

	if ( p->lONr == -1L || p->lONr == 0L || p->lCnt == 0L )
		return false;

	if ( !pLA)
		return false;

	CTable d( *pLA);
	bool iFlag = false;
	for ( d.First(); d.Valid(); d.Next()) {
		KP_LALock e(d);
		p->lIdent = BildeObjektKlasse (e->Herkunft(),e->Zuordnung());
		if ( 0L == p->lIdent)
			continue;
		long lBeginn = e->Ende();

		if ( !StartWertKorrekt ( p->lONr,lBeginn,p->lStartPunkt))
			continue;

		if ( lBeginn > p->lLaenge + p->lStartPunkt)
			continue;

		long lEnde = lBeginn + 10L;
		p->lStation = lBeginn;
		p->dHoehe = e->Kosten();
    	
		if ( !BildeKompaktObjekt(p, lBeginn, lEnde))
			return false;
		if ( !BildePunkt(p)) {
			continue;
		} else {
			iFlag = true;
			e->SpeichereObjekt ( p->lNewONr);
		}
	}
	return iFlag;

}
//----------------------------------------------------------------
bool CKompiasExtension :: BildePunkt (GEWSTRUKTUR *p)
{
	long lONr = 0L;
	long *pX = &(p->lXA);
	long *pY = &(p->lYA);
	OBJGEOMETRIE OG;
	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lIdent = (long) p->lIdent;
	OG.lONr = lONr;
//	OG.lCnt = p->lCnt;
	OG.lCnt = 1;
	OG.iObjTyp = OT_PUNKT;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGNewObject|OGAddToView;

	if ( !DEX_ModObjGeometrie (OG)) 
		return false;

//-------Neue ON merken !!!
	p->lNewONr = OG.lONr;
	return LadeMerkmalsWert(p);
}
//------------------------------------------------------------------
bool CKompiasExtension :: LadeMerkmalsWert ( GEWSTRUKTUR *p)
{

	char Buff[20];

	char * pMText = new char [_MAX_PATH];
	if ( !pMText)
		return false;

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = p->lNewONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =p->pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)p->lMCode;		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );

// Reiner Punkt aus Hydraulik

	if ( p->dHoehe > 0.0 ) {

		m_lONr = p->lNewONr;

		ST_DtoA ( pMText, "%f",p->dHoehe);
		tm.lTarget = p->lNewONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =pMText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeHydrHoehe();		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );

		ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwAnfStat(), ltoa(p->lStation,Buff,10));
	}


// Bauwerke abfangen
	if ( p->pSText && *(p->pSText) != NULL ) {
		tm.lTarget = p->lNewONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pMText;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)p->lMCode;		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );

		tm.lTarget = p->lNewONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pSText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwNr();		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );

// BauwerksIdent als Unique

		char *pUniq = new char [_MAX_PATH];

		if ( pUniq) {
			*pUniq = '\0';
			wsprintf (pUniq,"BWIdent-%ld_%ld",p->lNewONr,p->lObjectIdent);
			tm.lTarget = p->lNewONr;		// ObjektNummer
			tm.imaxLen = _MAX_PATH-1;
			tm.pMText =pUniq;		// Puffer

		#if _MSC_VER < 1100
				tm.lMCode = DEX_GetUniqueIdentMCode();		// MerkmalsCode
		#else
				HPROJECT hPr = DEX_GetObjectsProject(p->lIdent);
				tm.lMCode = DEX_GetUniqueIdentMCodeEx(hPr);		// MerkmalsCode
			
		#endif


			DEX_ModTextMerkmal ( tm );

			DELETE_OBJ(pUniq);
		}



		//----BauwerkeAttribute
		// SText : Gewaesser,AnlageNr,Anfang,Ende,Bezeichnung
		BauwerkeAttribute ( p );
	}

	DELETE_OBJ ( pMText);
	return true;

}
//////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: BauwerkeAttribute ( GEWSTRUKTUR *p )
{

	if ( !p)
		return;

	if ( !p->pSText || *(p->pSText) == '\0')
		return;

	char *ptr = strchr ( p->pSText,';');
	char *nptr;
	if ( !ptr)
		return;

	if ( ptr && *(ptr+1) != '\0') {
		ptr++;
		nptr = strchr (ptr, ';');

		if ( nptr ) {
			*nptr = '\0';
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwAnlNr(),ptr);
			*nptr = ';';
			ptr = nptr+1;
			if ( *ptr == '\0')
				return;
			nptr = strchr (ptr, ';');
		} else {
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwAnlNr(),ptr);
			return;
		}

		if ( nptr ) {
			*nptr = '\0';
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwAnfStat(),ptr);
			*nptr = ';';
			ptr = nptr+1;
			if ( *ptr == '\0')
				return;
			nptr = strchr (ptr, ';');
		} else {
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwAnfStat(),ptr);
			return;
		}

		if ( nptr ) {
			*nptr = '\0';
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwEndStat(),ptr);
			*nptr = ';';
			ptr = nptr+1;
			if ( *ptr == '\0')
				return;
		} else {
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwEndStat(),ptr);
			return;
		}

		if ( ptr && *ptr != '\0') {
			if (p->lIdent != 0L) {		// Oekologie2 = Sensibilitaet

				char NewIdent[MAX_OKS_LENX+1];

			#if _MSC_VER < 1100
				ClassFromIdentX ( p->lIdent, NewIdent);
			#else
				HPROJECT hPr = DEX_GetObjectsProject(p->lIdent);
				ClassFromIdentX ( hPr,p->lIdent, NewIdent);
			#endif

				long lRef = 0L;

				// Version 3.0
				lRef = atol (NewIdent+1);
//				lRef = atol (NewIdent);

				lRef = lRef - (cBauwerkeIdent*1000);
				if ( lRef == (long) cBauwerkeOekologie2)
					ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwSensib(),ptr);

			}
			ModifiziereMerkmal ( p->lNewONr,m_pKH->CodeBauwBez(),ptr);
		} else {
			return;
		}

	}
	return;
}
///////////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: ModifiziereMerkmal ( long lONr, ulong ulMCode, char *ptr)
{
	if (lONr == -1L || lONr == 0L || ulMCode == 0L || !ptr || *ptr == '\0')
		return;

	char *pBuff = new char [_MAX_PATH];
	if (!pBuff)
		return;

	*pBuff = '\0';

	strcat (pBuff,ptr);

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pBuff;		// Puffer
	tm.lMCode = (long)ulMCode;		// MerkmalsCode
	DEX_ModTextMerkmal ( tm );
	DELETE_OBJ(pBuff);
	return;
}
//------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: LoescheMerkmal ( long lONr, ulong ulMCode)
{
	if ( lONr == -1L || lONr == 0L || ulMCode == 0L )
		return;

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;
	tm.imaxLen = NULL;
	tm.pMText =NULL;		// Puffer
	tm.lMCode = (long)ulMCode;		// MerkmalsCode
	DEX_ModTextMerkmal ( tm );

	return;
}
///////////////////////////////////////////////////////////////////////////////
char * CKompiasExtension :: HoleMerkmalsWert ( long lONr, ulong ulMCode)
{
	if ( lONr == -1L || lONr == 0L || ulMCode == 0L )
		return NULL;
	char *pFeat = new char [_MAX_PATH];
	if (!pFeat )
		return NULL;

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pFeat;		// Puffer
	tm.lMCode = (long)ulMCode;		// MerkmalsCode

	if( DEX_GetTextMerkmal ( tm )) {
		return pFeat;
	} else {
		DELETE_OBJ(pFeat);
		return NULL;
	}

}
//------------------------------------------------------------------
//------------------------------------------------------------------
bool CKompiasExtension :: SpeichereLeistung (GEWSTRUKTUR *p, KP_LATree *pLA)
{

	if ( p->lONr == -1L || p->lONr == 0L  || p->lCnt == 0L )
		return false;

	if ( !pLA || !p)
		return false;

	char * pMText = new char [_MAX_PATH];
	if ( !pMText )
		return false;

	bool iFlag = false;
	char Buff[10];

	long lBeginn = -1L;
	long lEnde = -1L;

// KK010222
// iTyp = True : Leistg. = links,rechts , sonst false;

	short iTyp = true;

	CTable d( *pLA);

	for ( d.First(); d.Valid(); d.Next()) {
		KP_LALock e(d);
		if (!e)
			continue;
		if ( e->Beginn() > p->lLaenge )
			continue;
// StartPunkt des Gewässers prüfen
		if ( !StartWertKorrekt ( p->lONr,e->Beginn(),p->lStartPunkt))
			continue;


		if (e->Herkunft() != cBauwerkeIdent)
			p->lIdent = BildeLeistungsKlasse ( e->Herkunft(),e->Zuordnung(),e->Leistung());
		else
			p->lIdent = BildeObjektKlasse ( e->Herkunft(),e->Zuordnung());

		if ( 0L == p->lIdent)
			continue;

		if ( Leist_Mitte ==	e->LinksRechtsMitte())
			iTyp = false;
		else
			iTyp = true;

// Schrittweiten ??
		if ( SchrittweitenAnalyse(iTyp,&lBeginn,&lEnde,e->Beginn(),e->Ende()))
			m_iLeiSchritt = m_iLeiSchritt + m_iDefSchritt;
		else
			m_iLeiSchritt = m_iDefSchritt;	// Neues Intervall - Neuanfang


// neu 8.1.97
		if ( e->Herkunft() == cBauwerkeIdent ) {
			p->lStation = e->Beginn();
			p->lObjectIdent = e->ObjectIdent();	// Maltes Bauwerksident

			*pMText = '\0';
			if ( p->pMText && *(p->pMText) != '\0')
				strcat ( pMText ,p->pMText); // GewNr
	
			strcat ( pMText, ";");
	
			strcat ( pMText, ltoa(e->AnlageNr(),Buff,10));
			strcat ( pMText, ";");
			strcat ( pMText, ltoa(e->Beginn(),Buff,10));
			strcat ( pMText, ";");
			strcat ( pMText, ltoa(e->Ende(),Buff,10));
			strcat ( pMText, ";");

			if ( e->BauwerksBez())
				strcat ( pMText, e->BauwerksBez());
			p->pSText = pMText;
		}


	// Lage der Leistung bestimmen
		p->iLinksRechtsMitte = e->LinksRechtsMitte();


		if ( p->iLinksRechtsMitte == Leist_Beide ) {


			p->iLinksRechtsMitte = Leist_Links;
			if ( !BildeLeistungsArt ( p,e->Beginn(),e->Ende())) 
				continue;
			e->SpeichereObjekt ( p->lNewONr);
	
			// Leistungen zusaetzliche Codes anhaengen
			if ( e->Herkunft() != cBauwerkeIdent ) 
				SpeichereLeistungsCodes ( p->lNewONr,e->Beginn(),e->Ende(),e->Leistung());
				SpeichereAnomalie (p->lNewONr, p->dDefDist,p->dRCDist);

			// Gleicher Abstand !!!

//			m_iLeiSchritt = m_iLeiSchritt - m_iDefSchritt;
			
			p->iLinksRechtsMitte = Leist_Rechts;
			if ( !BildeLeistungsArt ( p,e->Beginn(),e->Ende())) 
				continue;
			e->SpeichereObjekt ( p->lNewONr);

			// Leistungen zusaetzliche Codes anhaengen
			if ( e->Herkunft() != cBauwerkeIdent ) 
				SpeichereLeistungsCodes ( p->lNewONr,e->Beginn(),e->Ende(),e->Leistung());
				SpeichereAnomalie (p->lNewONr, p->dDefDist,p->dRCDist);

			
			iFlag = true;

		} else {

			if (!BildeLeistungsArt (p,e->Beginn(),e->Ende())) {
				continue;
			} else {
				iFlag = true;
				e->SpeichereObjekt ( p->lNewONr);
	// Leistungen zusaetzliche Codes anhaengen
				if ( e->Herkunft() != cBauwerkeIdent ) {
					SpeichereLeistungsCodes ( p->lNewONr,e->Beginn(),e->Ende(),e->Leistung());
					SpeichereAnomalie (p->lNewONr, p->dDefDist,p->dRCDist);
				}
				
			}
			m_iCount++;

			if ( m_pStatus) 
				m_pStatus->SetValue((long)m_iCount, p->lONr);
			
		}

	}


	DELETE_OBJ ( pMText);

	return iFlag;
}
//-------------------------------------------------------------------
bool CKompiasExtension :: SchrittweitenAnalyse (short iTyp, long *lBeginn,long *lEnde, long lBegLA, long lEndLA)
{

// KK010226
// iTyp = false : SW erhöhen , Intervall ignorieren
// iTyp = true  : Intervall bestimmen, je Abschnitt auf true ( SW erhöhen ) oder false stellen
	if ( !iTyp)
		return true;

	if ( *lBeginn == -1L ) { // StartIntervall : nur setzen
		*lBeginn = lBegLA;
		*lEnde = lEndLA;
		return true;
	}
//
	if ( lBegLA < *lEnde ) {		// Überlappung - SW erhöhen
		*lBeginn = lBegLA;
		if ( lEndLA > *lEnde )
			*lEnde = lEndLA;
		return true;
	}
//	lBegLa > lBeginn und lEndLa >= lEnde : Neustart der SW : Neues Intervall
	*lBeginn = lBegLA;
	*lEnde = lEndLA;
	return false;		// Keine Erhöhung
}

//-------------------------------------------------------------------
bool CKompiasExtension :: SpeichereAnomalie ( long lONr, double dOldDist, double dNewDist)
{

	// KK010226
	// Falls bei Leistungen Links,Rechts Abweichungen der Schrittweite, dann Merkmal ausgeben !!!
	if ( dNewDist > 0.0 && dOldDist != dNewDist) {
		ulong lMCode = GetSWAnomalieCode(lONr);
		if ( 0L != lMCode) {
			char *pCode = new char [_MAX_PATH];
			if ( !pCode ) 
				return false;
			wsprintf ( pCode ,ResString( ResID( IDS_SWANOMALIE,&g_pTE->RF()),90),(long)dOldDist,(long)(dNewDist+0.5)); 	

			ModifiziereMerkmal (lONr,lMCode,pCode);
			DELETE_OBJ ( pCode);
			return true;
		}
	}
	return false;

}

//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für SchrittweitenAnomalie in definieren/holen
//-------------------------------------------------------------------
ulong CKompiasExtension :: GetSWAnomalieCode (long lONr)
{
	ulong lMCode = 0L;
	ulong lMHandle = 0L;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		return lMCode;
	}

	*pCode = '\0';

	strcat( pCode, ResString( ResID( IDS_LEISTUNGSSCHRITT,&g_pTE->RF()),90));

#if _MSC_VER < 1100
	lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#else
	HPROJECT hPr = DEX_GetObjectProject(lONr);
	lMCode = DEX_GetMCodeFromFeatureNameEx (hPr ,pCode );
#endif

	DELETE_OBJ ( pCode);

	if ( 0L == lMCode ) {

		lMHandle = DEX_GetUniqueSysMCode ();
		lMCode = DEX_MapHandleToMCode(lMHandle);

		if ( 0L == lMCode ) {
			return lMCode;
		}

		SetNewPBDMCode (DEX_GetObjIdent(lONr),lMCode,ResString(ResID(IDS_LEISTUNGSSCHRITT,&RF()),50));

	}
	return lMCode;

}

//--------------------------------------------------------------------
bool CKompiasExtension :: SpeichereLeistungsCodes ( long lONr,long lBeginn,long lEnde, char *pLeistung)
{
	if (lONr == -1L || lONr == 0L)
		return false;
	if ( lBeginn < 0 || lBeginn >= lEnde)
		return false;
	if ( !pLeistung || *pLeistung == '\0')
		return false;
		
	char * pMText = new char [_MAX_PATH];
	if (!pMText)
		return false;

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.iTTyp = TT_Objekt;

	if ( m_pKH->CodeBauwAnfStat()) {
		wsprintf ( pMText,"%ld",lBeginn);
		tm.pMText =pMText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwAnfStat();		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );
	}

	if ( m_pKH->CodeBauwEndStat()) {
		wsprintf ( pMText,"%ld",lEnde);
		tm.pMText =pMText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwEndStat();		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );
	}
	
	if ( m_pKH->CodeBauwLeist()) {
		tm.pMText =pLeistung;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwLeist();		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );
	}
	
	DELETE_OBJ (pMText);
	
	return true;
}
//-------------------------------------------------------------------

ulong CKompiasExtension :: BildeObjektKlasse ( short iHk , short iZuo)
{

	ulong lIdent = KompaktIdentifikatorEx (m_pLocProt,iHk,iZuo);
	if ( 0L == lIdent)
		return lIdent;

	SetPBDIdent (lIdent,iHk,iZuo);


	return lIdent;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
// Kompakt-Identifikatoren in PBD setzen
//-------------------------------------------------------------------
void CKompiasExtension :: SetPBDIdent ( long lIdent, short iHk, short iZuo)
{


	char KText[TEXTLEN+1];
	KText[0] = '\0';


	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;

	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText= KText;

//	KompaktProtokoll (m_pLocProt,KText);
	
	{
	ErrInstall EI (WC_NOIDENT);
#if _MSC_VER < 1100
	if (DEX_GetPBDData (pbdData) == EC_OKAY) 
		return;
#else
	if (DEX_GetPBDDataEx (m_hPr,pbdData) == EC_OKAY) 
		return;
#endif

	}

	if ( iHk == cBauwerkeIdent && iZuo == cBauwerkeUnbekannt )
		return;

	char *pLText = new char [_MAX_PATH];
	if ( !pLText)
		return;
	*pLText = '\0';


//-----------Leistungen-------------------------------------
	if (iHk == cLeistungenUnterhaltung) 
		strcat ( pLText,  ResString (ResID(IDS_IDUNTERHALTUNG,&RF()),40));

	if (iHk == cLeistungenAusschreibung) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUSSCHREIBUNG,&RF()),40));

	if (iHk == cLeistungenAuftrag) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUFTRAG,&RF()),40));

	if (iHk == cLeistungenAufmass) 
		strcat ( pLText,  ResString (ResID(IDS_IDAUFMASS,&RF()),40));

//-------------------Sonstige---------------------

	if (iHk == cHydraulikHochwasser) 
		strcat ( pLText,  ResString (ResID(IDS_IDHYDRAULIK,&RF()),40));

	if (iHk == cSensibilitaetsStufe) 
		strcat ( pLText,  ResString (ResID(IDS_IDSENSIBILITAET,&RF()),40));

// --------------------Bauwerke -----------------------------------------

	if (iHk == cBauwerkeIdent) {
		if (iZuo == cBauwerkeSchoepfwerke)
			strcat ( pLText,  ResString (ResID(IDS_SCHOEPFWERKE,&RF()),40));
		if (iZuo == cBauwerkeStauanlagen)
			strcat ( pLText,  ResString (ResID(IDS_STAUANLAGEN,&RF()),40));
		if (iZuo == cBauwerkeRechte)
			strcat ( pLText,  ResString (ResID(IDS_RECHTE,&RF()),40));
		if (iZuo == cBauwerkeKreuzungen)
			strcat ( pLText,  ResString (ResID(IDS_KREUZUNGEN,&RF()),40));
		if (iZuo == cBauwerkeSohlbauwerke)
			strcat ( pLText,  ResString (ResID(IDS_SOHLBAUWERKE,&RF()),40));
		if (iZuo == cBauwerkeSchaechte)
			strcat ( pLText,  ResString (ResID(IDS_SCHAECHTE,&RF()),40));
		if (iZuo == cBauwerkeOekologie1)
			strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE1,&RF()),40));
		if (iZuo == cBauwerkeRohrleitungen)
			strcat ( pLText,  ResString (ResID(IDS_ROHRLEITUNGEN,&RF()),40));
		if (iZuo == cBauwerkeDurchlaesse)
			strcat ( pLText,  ResString (ResID(IDS_DURCHLAESSE,&RF()),40));
		if (iZuo == cBauwerkeOekologie2)
			strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE2,&RF()),40));
		if (iZuo == cBauwerkeBebauungLinks)
			strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGLINKS,&RF()),40));
		if (iZuo == cBauwerkeBebauungRechts)
			strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGRECHTS,&RF()),40));
		if (iZuo == cBauwerkeEinmuendung)
			strcat ( pLText,  ResString (ResID(IDS_EINMUENDUNG,&RF()),40));
//		if ( iZuo < cBauwerkeSchoepfwerke || iZuo > cBauwerkeEinmuendung )
		if ( iZuo < cBauwerkeSchoepfwerke || iZuo > cBauwerkeUnbekannt )
			MessageBox ( __hWndM ,
					 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
					 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
					MB_OK);
	}


///////////////////////////////////////////////////////////////////////////////
//-----------------Untergruppen---------------------------------------

	if (iZuo == cLeistZuordnungRandStreifen) 
		strcat ( pLText,  ResString (ResID(IDS_IDRANDSTREIFEN,&RF()),40));

	if (iZuo == cLeistZuordnungBoeschungLinks) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGLINKS,&RF()),40));

	if (iZuo == cLeistZuordnungBoeschungRechts) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGRECHTS,&RF()),40));

	if (iZuo == cLeistZuordnungBoeschungBeide) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGBEIDE,&RF()),40));

	if (iZuo == cLeistZuordnungBoeschungTeilprofil) 
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGTEILPROFIL,&RF()),40));

	if (iZuo == cLeistZuordnungSohlkrautung) 
		strcat ( pLText,  ResString (ResID(IDS_IDSOHLKRAUTUNG,&RF()),40));

	if (iZuo == cLeistZuordnungGrundraeumung) 
		strcat ( pLText,  ResString (ResID(IDS_IDGRUNDRAEUMUNG,&RF()),40));

	if (iZuo == cLeistZuordnungStundenStueckLohn) 
		strcat ( pLText,  ResString (ResID(IDS_IDSTUNDENSTUECKLOHN,&RF()),40));

//-Sonstige----------------------------------------------
	if (iZuo == cUeberschwemmungsPunkt) 
		strcat ( pLText,  ResString (ResID(IDS_IDUEBERSCHWEMMUNGSPUNKT,&RF()),40));

	if (iZuo == cUeberschwemmungsGebiet) 
		strcat ( pLText,  ResString (ResID(IDS_IDUEBERSCHWEMMUNGSGEBIET,&RF()),40));

	if (iZuo == cSensibilitaetsStufe1) 
		strcat ( pLText,  ResString (ResID(IDS_IDSTUFE1,&RF()),40));

	if (iZuo == cSensibilitaetsStufe2) 
		strcat ( pLText,  ResString (ResID(IDS_IDSTUFE2,&RF()),40));

	if (iZuo == cSensibilitaetsStufe3) 
		strcat ( pLText,  ResString (ResID(IDS_IDSTUFE3,&RF()),40));

//--------------------------------------------------------------------
	strncpy ( KText,pLText,TEXTLEN);
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pLText;


	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100

	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (m_hPr,pbdData);
	SetNewPBDKlasse (lIdent,iHk);
#endif

	DEXN_PBDIdentsChanged();
	}

	DELETE_OBJ (pLText);

	return ;
}
//////////////////////////////////////////////////////////////////////////////
// MCode für neue Klassen in PBD setzen
void CKompiasExtension :: SetNewPBDKlasse(long lIdent,short iHk)
{

	if ( !m_pKH)
		return;

	if (iHk == cLeistungenUnterhaltung || iHk == cLeistungenAusschreibung || cLeistungenAuftrag || cLeistungenAufmass) {

		SetNewPBDMCode (lIdent,m_pKH->CodeGewNr(),ResString(ResID(IDS_GEWAESSERMCODENR,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwAnfStat(),ResString(ResID(IDS_ANFANGSSTATION,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwEndStat(),ResString(ResID(IDS_ENDSTATION,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwLeist(),ResString(ResID(IDS_LEISTUNGSART,&RF()),50));
		return;
	}
	if ( iHk == cBauwerkeIdent) {

		SetNewPBDMCode (lIdent,m_pKH->CodeGewNr(),ResString(ResID(IDS_GEWAESSERMCODENR,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwNr(),ResString(ResID(IDS_BAUWERKEMCODENR,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwName(),ResString(ResID(IDS_BAUWERKEMCODENAME,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwAnfStat(),ResString(ResID(IDS_ANFANGSSTATION,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwEndStat(),ResString(ResID(IDS_ENDSTATION,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwAnlNr(),ResString(ResID(IDS_ANLAGENUMMER,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwBez(),ResString(ResID(IDS_BEZEICHNUNG,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwStauziel(),ResString(ResID(IDS_STAUZIEL,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwWasserSpiegel(),ResString(ResID(IDS_WASSERSPIEGEL,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwSensib(),ResString(ResID(IDS_SENSIBILITAETSSTUFE,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwArt(),ResString(ResID(IDS_ARTFAUNAFLORA,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwLeist(),ResString(ResID(IDS_LEISTUNGSART,&RF()),50));
		return;

	}
	if (iHk == cHydraulikHochwasser) {
		SetNewPBDMCode (lIdent,m_pKH->CodeGewNr(),ResString(ResID(IDS_GEWAESSERMCODENR,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeHydrHoehe(),ResString(ResID(IDS_HYDRAULIKMCODEHOEHE,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeHydrWert(),ResString(ResID(IDS_HYDRAULIKMCODEWERT,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwAnfStat(),ResString(ResID(IDS_ANFANGSSTATION,&RF()),50));
		SetNewPBDMCode (lIdent,m_pKH->CodeBauwEndStat(),ResString(ResID(IDS_ENDSTATION,&RF()),50));

	}

	return;

}

//-------------------------------------------------------------------
void CKompiasExtension :: SetNewPBDMCode (long lIdent,long lMCode,ResString rs)
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
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

	strcat ( KText, rs);

	pbdData.pbdKText = KText;

	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;


#if _MSC_VER >= 1100

	pbdData.lIdent = lIdent;

	DefineFeatureSet ( &pbdData);


	/*------------------

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

// Test, ob OE bereits definiert
	long lRefCode = DEX_GetMCodeFromFeatureNameEx(hPr,KText);

	if (lRefCode != 0L && lRefCode != lMCode)	// Doppelt benutzt
		ModifyObjFeature(lRefCode,lIdent,&KText[0]);


		{
		ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
				return;
			else
				DEXN_PBDMCodeChanged (lMCode);
		}
		
---------------------------*/

#else


	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}
#endif

	return;

}
//////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// Erweiterte Kompakt-Identifikatoren in PBD setzen
//-------------------------------------------------------------------
ulong CKompiasExtension :: BildeLeistungsKlasse ( short iHk, short iZuo, char *pLeistung)
{

	ulong lIdent = 0;

	if (!pLeistung || *pLeistung == '\0')
		return lIdent;

	char *pLText = new char [_MAX_PATH];
	if ( !pLText)
		return lIdent;
	*pLText = '\0';

	char *pKText = new char [_MAX_PATH];
	if ( !pKText) {
		DELETE_OBJ ( pLText);
		return lIdent;
	}
	*pKText = '\0';

//-----------Leistungen-------------------------------------
	if (iHk == cLeistungenUnterhaltung) {
		strcat ( pKText,  ResString (ResID(IDS_IDSHORTUNTERHALTUNG,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDUNTERHALTUNG,&RF()),40));
	}
	if (iHk == cLeistungenAusschreibung) {
		strcat ( pKText,  ResString (ResID(IDS_IDSHORTAUSSCHREIBUNG,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDAUSSCHREIBUNG,&RF()),40));
	}

	if (iHk == cLeistungenAuftrag) {
		strcat ( pKText,  ResString (ResID(IDS_IDSHORTAUFTRAG,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDAUFTRAG,&RF()),40));
	}

	if (iHk == cLeistungenAufmass) {
		strcat ( pKText,  ResString (ResID(IDS_IDSHORTAUFMASS,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDAUFMASS,&RF()),40));
	}

///////////////////////////////////////////////////////////////////////////////
//-----------------Untergruppen---------------------------------------

	if (iZuo == cLeistZuordnungRandStreifen) {
		strcat ( pKText,  ResString (ResID(IDS_IDRANDSTREIFEN,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDRANDSTREIFEN,&RF()),40));
	}
	if (iZuo == cLeistZuordnungBoeschungLinks) {
		strcat ( pKText,  ResString (ResID(IDS_IDBOESCHUNGLINKS,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGLINKS,&RF()),40));
	}
	if (iZuo == cLeistZuordnungBoeschungRechts) {
		strcat ( pKText,  ResString (ResID(IDS_IDBOESCHUNGRECHTS,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGRECHTS,&RF()),40));
	}
	if (iZuo == cLeistZuordnungBoeschungBeide) {
		strcat ( pKText,  ResString (ResID(IDS_IDBOESCHUNGBEIDE,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGBEIDE,&RF()),40));
	}
	if (iZuo == cLeistZuordnungBoeschungTeilprofil) {
		strcat ( pKText,  ResString (ResID(IDS_IDBOESCHUNGTEILPROFIL,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDBOESCHUNGTEILPROFIL,&RF()),40));
	}
	if (iZuo == cLeistZuordnungSohlkrautung) {
		strcat ( pKText,  ResString (ResID(IDS_IDSOHLKRAUTUNG,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDSOHLKRAUTUNG,&RF()),40));
	}
	if (iZuo == cLeistZuordnungGrundraeumung) {
		strcat ( pKText,  ResString (ResID(IDS_IDGRUNDRAEUMUNG,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDGRUNDRAEUMUNG,&RF()),40));
	}
	if (iZuo == cLeistZuordnungStundenStueckLohn) {
		strcat ( pKText,  ResString (ResID(IDS_IDSTUNDENSTUECKLOHN,&RF()),40));
		strcat ( pLText,  ResString (ResID(IDS_IDSTUNDENSTUECKLOHN,&RF()),40));
	}
//------------------------------------------------------------------
	strcat ( pKText,"/");
	strcat ( pLText,"/");
	strcat (pKText, pLeistung);
	strcat (pLText, pLeistung);

	KompaktProtokoll (m_pLocProt,pKText);

	char KText[TEXTLEN+1];
	KText[0] = NULL;
	strncpy ( KText,pKText,TEXTLEN);
	short iFlag = False;		

	lIdent = FindePBDUnterGruppe(iHk,iZuo,KText,&iFlag);

	if ( lIdent == 0L ) {
		DELETE_OBJ ( pKText);
		DELETE_OBJ ( pLText);
		return lIdent;
	}
	if ( iFlag) {		// bereits in PBD definiert
		DELETE_OBJ (pLText);
		DELETE_OBJ (pKText);
		return lIdent;
	}

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;

	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = _MAX_PATH;
	pbdData.pbdLText = pLText;
	pbdData.pbdKText = KText;

//--------------------------------------------------------------------

	{
	ErrInstall EI (WC_NOIDENT);

#if _MSC_VER < 1100

	DEX_ModPBDData (pbdData);

#else

	DEX_ModPBDDataEx (m_hPr,pbdData);

//  Merkmale definieren

	SetNewPBDKlasse (lIdent,iHk);

#endif


	DEXN_PBDIdentsChanged();
	}

	DELETE_OBJ (pLText);
	DELETE_OBJ (pKText);

	return lIdent;
}

//////////////////////////////////////////////////////////////////////////////

ulong CKompiasExtension :: FindePBDUnterGruppe (  short iHk, short iZuo, char *pText, short *iFlag)
{

	ulong lIdent = 0L;
	*iFlag = false;
		
	char Ident[MAX_OKS_LENX + 1];
	ulong rIdent = (ulong)iHk * 1000 + (ulong)iZuo;
	rIdent = rIdent * 100;
	ulong rRefIdent = 0L;

	char KText[TEXTLEN+1];
	KText[0] = NULL;

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';

	for ( long i = 0; i < 100; i++ ) {

		rIdent = rIdent + 1;
		
		char KomSign = KompaktIdentifikatorTabelle[iHk-1];

		wsprintf ( Ident,"%c%ld",KomSign,rIdent);
//		wsprintf ( Ident,"%ld",rIdent);
		rRefIdent = 0L;
#if _MSC_VER < 1100
		IdentFromClassX ( Ident,&rRefIdent);
#else
		HRESULT hr = IdentFromClassX ( m_hPr,Ident,&rRefIdent,true);
		if (hr == S_FALSE ) {
			*iFlag = false;
			if (rRefIdent != 0L)
				lIdent = rRefIdent;
			return lIdent;
		}
		 
#endif
		lIdent = rRefIdent;
		
		pbdData.pbdCode = (long)lIdent;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;
		pbdData.pbdKText = KText;

		{
		ErrInstall EI (WC_NOIDENT);

		if (DEX_GetPBDData (pbdData) != EC_OKAY) {
			*iFlag = false;
			return lIdent;
		}

		}

		if ( strcmp ( pText,KText) == 0 ) {
			*iFlag = true;	// bereits definiert
			return lIdent;
		}
	}

	return lIdent;
}
//////////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: SpeichereBauwMerkmal ( long lIdent)
{

	if (lIdent == 0L)
		return;

//	if (!DEX_isIdentUsed(lIdent))
//		return;

	char * pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;

	*pMText = '\0';
	strcat(pMText ,"16");

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = lIdent;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long) m_pKH->CodeBauwKl();		// MerkmalsCode

	if( DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ ( pMText);
		return ;
	}

	tm.lTarget = lIdent;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer

	*pMText = '\0';
	strcat(pMText ,"16");


	DEX_ModTextMerkmal ( tm );

	DELETE_OBJ (pMText);
}
//------------------------------------------------------------------
//-------------------------------------------------------------------
bool CKompiasExtension :: BildeLeistungsArt ( GEWSTRUKTUR *p , long lBeginn, long lEnde)
{
    if ( !m_pAbst)
    	return false;
    	
	if ( !BildeKompaktObjekt(p, lBeginn, lEnde))
		return false;
	// neu 8.1.96

	if ( lBeginn == lEnde ) {
		return BildePunkt(p);
	}

	IObjektGeometrie *pIOG = NULL;

	// Wolfgangs neueste Kreation :
	// ShiftedLinePart
	//  IObjektGeometrie * Ausgangsobjekt
	//	long,long	Koord. AP
	//	double Länge Teilabschnitt
	//	Side : ABST_LEFT,ABST_RIGHT
	//	double * Abstand in Meter ( Rückgabe)
	//	ulong Objektklasse
	//	IObjektGeometrie **		ErgebnisObjekt

	double dDist = (double)m_iLeiSchritt;	// Schrittweite

	long lMyONr;

	m_pIOG -> GetONr (&lMyONr);


	HRESULT hr;
	
	if ( p->iLinksRechtsMitte == Leist_Mitte) {

		if ( (m_iLeiSchritt-m_iDefSchritt) >= 0 )
			m_iLeiSchritt = m_iLeiSchritt - m_iDefSchritt;
		

		try {
		{
		ErrInstall EI (EC_ILLPARS);

			hr = m_pAbst->LinePart ( m_pIOG,p->lXA,p->lYA,p->lXE,p->lYE,p->dDist, &pIOG);
			if (FAILED(hr)) throw hr;

			char *pT = new char [_MAX_PATH];
			if (pT ) {
				wsprintf (pT,"\n\t Leistung Mitte :\n\tObjekt %ld - Länge %ld(%ld/%ld)\n",lMyONr,(long)p->dDist,lBeginn,lEnde);
				KompaktProtokoll(m_pLocProt,pT);
				DELETE_OBJ (pT);
			}
		}

		} catch (...) {


			char *pT = new char [_MAX_PATH];

			if (pT ) {
				wsprintf (pT,"\n * ERROR-Leistung Mitte :\n\tObjekt %ld - Länge  %ld\n",lMyONr,(long)p->dDist);
				KompaktProtokoll(m_pLocProt,pT);
				DELETE_OBJ (pT);
			}
			
			return false;

		}

	
	} else {

		if ( p->iLinksRechtsMitte == Leist_Links ) {	// Verlauf in Gegenrichtung => links zu rechts

			try {
				long lRefDist = (long) dDist;
				p->dDefDist = dDist;

				hr = m_pAbst->ShiftedLinePart ( m_pIOG,p->lXA,p->lYA,p->dDist,ABST_RIGHT,&dDist,p->lIdent, &pIOG);
				p->dRCDist = dDist;

				char *pT = new char [_MAX_PATH];
				if (pT ) {	
					wsprintf (pT,"\n\t Leistung Rechts :\n\tObjekt %ld(X = %ld Y = %ld) - Länge %ld(%ld/%ld) : Breite = %ld(%ld)\n",lMyONr,p->lXA,p->lYA,(long)p->dDist,lBeginn,lEnde,(long)dDist,lRefDist);
					KompaktProtokoll(m_pLocProt,pT);
					DELETE_OBJ (pT);
				}

			} catch (...) {
	//			MessageBox ( __hWndM,"ShiftedLinePart fehlgeschlagen" , " Rechts",MB_OK);

				char *pT = new char [_MAX_PATH];
				if (pT ) {	
					wsprintf (pT,"\n * ERROR-Leistung Rechts :\n\tObjekt %ld(X = %ld Y = %ld) - Länge %ld  Breite = %ld\n",lMyONr,p->lXA,p->lYA,(long)p->dDist,(long)dDist);
					KompaktProtokoll(m_pLocProt,pT);
					DELETE_OBJ (pT);
				}

				return false;
			}
		}

		if ( p->iLinksRechtsMitte == Leist_Rechts ) {

			try {

				long lRefDist = (long) dDist;
				p->dDefDist = dDist;
				hr = m_pAbst->ShiftedLinePart ( m_pIOG,p->lXA,p->lYA,p->dDist,ABST_LEFT,&dDist,p->lIdent, &pIOG);
				p->dRCDist = dDist;

				char *pT = new char [_MAX_PATH];
				if (pT ) {	
					wsprintf (pT,"\n\t Leistung Links :\n\tObjekt %ld (X = %ld Y = %ld) - Länge %ld(%ld/%ld) : Breite = %ld(%ld)\n",lMyONr,p->lXA,p->lYA,(long)p->dDist,lBeginn,lEnde,(long)dDist,lRefDist);
					KompaktProtokoll(m_pLocProt,pT);
					DELETE_OBJ (pT);
				}

			} catch (...) {

				char *pT = new char [_MAX_PATH];
				if (pT ) {	
					wsprintf (pT,"\n * ERROR-Leistung Links :\n\tObjekt %ld (X = %ld Y = %ld) - Länge %ld  Breite = %ld\n",lMyONr,p->lXA,p->lYA,(long)p->dDist,(long)dDist);
					KompaktProtokoll(m_pLocProt,pT);
					DELETE_OBJ (pT);
				}

				return false;
			}
		}


		if (FAILED(hr)) 
			return false;

		bool iFlag = true;

		if (!LadeEndKompaktObjekt(p, pIOG))
			iFlag = false;

		pIOG->Release();

		return iFlag;	
	}


	if (FAILED(hr)) 
		return false;

	bool iFlag = true;

	if (!LadeKompaktObjekt(p, pIOG))
		iFlag = false;

	pIOG->Release();

	return iFlag;
}
//------------------------------------------------------------------------
bool CKompiasExtension :: BildeKompaktObjekt ( GEWSTRUKTUR *p,long lStart, long lEnde )
{

	if ( !m_pIOG || !m_pAbst)
		return false;
	
	if ( lStart == p->lStartPunkt && lEnde > lStart) {
		p->dDist = ( double ) (lEnde-lStart);
		p->lXA = p->lGXA;
		p->lYA = p->lGYA;
		return true;
	}

//	if ( lStart > 0L && lEnde > lStart ) {
	if ( lStart > p->lStartPunkt && lEnde >= lStart ) {	// neu 8.1.97
		p->dDist = (double)(lStart-p->lStartPunkt);
		if (!StuetzPunktAusAbstand(p))
			return false;

		long lDist = lEnde - lStart;
		p->dDist = (double) lDist;
	}

	return true;
}

//-------------------------------------------------------------
bool CKompiasExtension :: StuetzPunktAusAbstand ( GEWSTRUKTUR *p )
{
	if ( !p || !m_pIOG)
		return false;

	IObjektGeometrie *pIOG = NULL;

	try {


		HRESULT hr = m_pAbst->LinePart ( m_pIOG,p->lGXA,p->lGYA,p->lGXE,p->lGYE,p->dDist, &pIOG);

		if (FAILED(hr)) 
			return false;


	} catch ( ... ) {
		return false;
	}
		
	KoOrd *plXK, *plYK;
	long lSPAnz;

	pIOG -> GetX ((void**)&plXK);
	pIOG -> GetY ((void**)&plYK);
	pIOG -> GetCnt (&lSPAnz);

	p->lXA = plXK [lSPAnz-1];
	p->lYA = plYK [lSPAnz-1];

	pIOG->Release();

	return true;
}
//------------------------------------------------------------------
//-------------------------------------------------------------
bool CKompiasExtension :: LadeKompaktObjekt ( GEWSTRUKTUR *p, IObjektGeometrie *pIOG)
{
	if ( !pIOG )
		return false;

	pIOG->SetIdent ( p->lIdent);
	pIOG->SetFlags ( OGNewObject | OGAddToView | OGForceGeoError);


	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
	UnRegisterNotification (DEX_OBJECTSELECTED);
	UnRegisterNotification (DEX_N_OBJECTCREATED);

// Temporärer Zwischendruck
	long lSPAnz;
	KoOrd *plXK, *plYK;

	char *pTK = new char [_MAX_PATH];
	if ( pTK ) {
		*pTK = '\0';
		wsprintf (pTK,"\tpIOG - TRiASObjekt : %ld auf BezugsObjekt %ld / Gewässer %s \n",p->lNewONr,p->lONr,p->pMText);


		pIOG -> GetX ((void**)&plXK);
		pIOG -> GetY ((void**)&plYK);
		pIOG -> GetCnt (&lSPAnz);
		wsprintf (pTK,"\tStützpunktanzahl : %ld \n",lSPAnz);
		KompaktProtokoll ( m_pLocProt, pTK);

		for ( long i = 0 ; i < lSPAnz; i++ ) {
			wsprintf ( pTK, " RW %ld - HW %ld \n",plXK[i],plYK[i]);
			KompaktProtokoll ( m_pLocProt, pTK);
		}

//		DELETE_OBJ ( pTK);
	}
	
	#if _MSC_VER < 1100
		HRESULT hr = pIOG->GeometrieAnTRiAS ( false, NULL);
	#else
		HPROJECT hPr = DEX_GetObjectsProject(p->lIdent);
		HRESULT hr = pIOG->GeometrieAnTRiASEx (INT_PTR(hPr), false, NULL);
	#endif

	for ( long i = 0 ; i < lSPAnz; i++ ) {
		wsprintf ( pTK, "\t Korr RW %ld - HW %ld \n",plXK[i],plYK[i]);
		KompaktProtokoll ( m_pLocProt, pTK);
	}
	DELETE_OBJ ( pTK);



	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
	RegisterNotification (DEX_OBJECTSELECTED);
	RegisterNotification (DEX_N_OBJECTCREATED);


// Korrektur 30.09.99
//	if ( hr != S_OK )
	if ( FAILED(hr))
		return false;

	long lONr;
	HRESULT ho = pIOG->GetONr ( &lONr );	
	if ( ho != S_OK )
		return false;
	
	if ( lONr == -1L || lONr == 0L)
		return false;

	p->lNewONr = lONr;


	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =p->pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)p->lMCode;		// MerkmalsCode

	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	DEX_ModTextMerkmal ( tm );

	char *pT = new char [_MAX_PATH];
	if ( pT ) {
		*pT = '\0';
		wsprintf (pT,"\tNeues TRiASObjekt : %ld auf BezugsObjekt %ld / Gewässer %s \n",p->lNewONr,p->lONr,p->pMText);
		KompaktProtokoll ( m_pLocProt, pT);
		DELETE_OBJ ( pT);
	}


// Bauwerke abfangen
	if ( p->pSText && *(p->pSText) != NULL ) {
		tm.lTarget = lONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pMText;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)p->lMCode;		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );

		tm.lTarget = p->lNewONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pSText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwNr();		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );

		char *pUniq = new char [_MAX_PATH];

		if ( pUniq) {
			*pUniq = '\0';
			wsprintf (pUniq,"BWIdent-%ld_%ld",p->lNewONr,p->lObjectIdent);
			tm.lTarget = p->lNewONr;		// ObjektNummer
			tm.imaxLen = _MAX_PATH-1;
			tm.pMText =pUniq;		// Puffer

		#if _MSC_VER < 1100
				tm.lMCode = DEX_GetUniqueIdentMCode();		// MerkmalsCode
		#else
				HPROJECT hPr = DEX_GetObjectsProject(p->lIdent);
				tm.lMCode = DEX_GetUniqueIdentMCodeEx(hPr);		// MerkmalsCode
			
		#endif


			DEX_ModTextMerkmal ( tm );

			DELETE_OBJ(pUniq);
		}
	//_-------------------------------------------------

		//----BauwerkeAttribute
		// SText : Gewaesser,AnlageNr,Anfang,Ende,Bezeichnung
		BauwerkeAttribute ( p );

	}
	return true;
}
//------------------------------------------------------------------
//-------------------------------------------------------------
bool CKompiasExtension :: LadeEndKompaktObjekt ( GEWSTRUKTUR *p, IObjektGeometrie *pIOG)
{
	if ( !pIOG )
		return false;


	long lONr;
	HRESULT ho = pIOG->GetONr ( &lONr );	
	if ( ho != S_OK )
		return false;
	
	if (lONr == -1L || lONr == 0L)
		return false;

	p->lNewONr = lONr;

	VIEWIDENTOBJECT VIO;
	memset (&VIO, '\0', sizeof(VIEWIDENTOBJECT));
	VIO.dwSize = sizeof(VIEWIDENTOBJECT);
	VIO.m_pView = NULL;
	VIO.m_lIdent = p->lIdent;
//	VIO.m_lONr=lONr;
	VIO.m_iOTyp=OTLinie;
#pragma message ("KOMPGEO.CPP:==> Achtung : DEX_AddIdentToView scheint nur für TRiAS 3.0 zu gehen")

	DEX_AddIdentToView(VIO);


	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =p->pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)p->lMCode;		// MerkmalsCode
	DEX_ModTextMerkmal ( tm );

	char *pT = new char [_MAX_PATH];
	if ( pT ) {
		*pT = '\0';
		wsprintf (pT,"\tNeues TRiASObjekt : %ld auf BezugsObjekt %ld / Gewässer %s \n",p->lNewONr,p->lONr,p->pMText);
		KompaktProtokoll ( m_pLocProt, pT);
		DELETE_OBJ ( pT);
	}

// Bauwerke abfangen
	if ( p->pSText && *(p->pSText) != NULL ) {
		tm.lTarget = lONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pMText;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)p->lMCode;		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );

		tm.lTarget = p->lNewONr;		// ObjektNummer
		tm.imaxLen = _MAX_PATH-1;
		tm.pMText =p->pSText;		// Puffer
		tm.lMCode = (long)m_pKH->CodeBauwNr();		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );
	//_-------------------------------------------------

		//----BauwerkeAttribute
		// SText : Gewaesser,AnlageNr,Anfang,Ende,Bezeichnung
		BauwerkeAttribute ( p );

	}
	return true;
}
//------------------------------------------------------------------
//-----KOMPGEO.CXX
