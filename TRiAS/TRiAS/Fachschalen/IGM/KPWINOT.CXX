
//-----------KOMPAKT-MEMBER : Auswerten WindowsNotificationen Kompakt/Trias----------
// File: KPWINOT.CXX


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

bool CKompiasExtension :: HydraulikPunkt ( LPARAM p )
{

// Achtung - TESTEN - real = 4 , double = 8, long double = 10;

	TX_ASSERT(NULL != p);
	TX_ASSERT(sizeof(HYDRAULIK) == ((HYDRAULIK *)p)->dwSize);
	TX_ASSERT( 0L <= ((HYDRAULIK *)p)->lPos);
	TX_ASSERT( 0.0 <= ((HYDRAULIK *)p)->dHoehe);
	TX_ASSERT( NULL != ((HYDRAULIK *)p)->pcGewaesserNr);
	TX_ASSERT( NULL != *(((HYDRAULIK *)p)->pcGewaesserNr));

	//--------------Hier kommt Malte -----------
//------------Versuch Hydraulik-Test------------------------

	if ( !p) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKEINPUNKT, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		return false;
	}

	

	KPTree *pGewP = HolePunktVonKompakt(p);

	if ( !pGewP) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKEINPUNKT, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		return false;
	}

	if ( pGewP->Count() == 0 ) {
		DELETE_OBJ ( pGewP);
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKEINPUNKT, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		return false;
	}
	bool iFlag = false;
	if ( m_pKH && m_pKH->GewClass()) {
//---------------Objekte an Ident hängen

		if ( m_pGewAlle)  {
//			m_pGewAlle = GesamtGewaesser();
		
			AbgleichGewKataster( pGewP,m_pGewAlle);
		} else {
			if( !EinzelGewaesser(pGewP)) {
				DELETE_OBJ ( pGewP);
				MessageBox (__hWndM, 
				 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),180),
				 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
				 MB_OK|MB_ICONHAND);

				return false;
			}
		}
//--------------------------------------------------------------------
		m_lONr = -1L;
		if (!SpeicherePunktInTrias ( pGewP)) {
			DELETE_OBJ ( pGewP);
			MessageBox (__hWndM, 
//			 "Punkt konnte Gewässer nicht zugeordnet werden",
			 ResString (ResID(IDS_KEINGEWAESSERPUNKT, &RF()),180),
			 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
			MB_OK);
			return false;
		}

		iFlag = BildeUeberschwemmungsGebiet (pGewP);

//		if ( !iFlag ) 
//			ZeigeUeberschwemmungsPunkt ();

//		Aufruf eine Ebene höher

	}


	DELETE_OBJ ( pGewP);

	return iFlag;

}

bool CKompiasExtension :: HydraulikPunkte ( LPARAM p )
{

// Achtung - TESTEN - real = 4 , double = 8, long double = 10;

	TX_ASSERT(NULL != p);
	TX_ASSERT(sizeof(HYDRAULIK) == ((HYDRAULIK *)p)->dwSize);
	TX_ASSERT( 0L <= ((HYDRAULIK *)p)->lPos);
	TX_ASSERT( 0.0 <= ((HYDRAULIK *)p)->dHoehe);
	TX_ASSERT( NULL != ((HYDRAULIK *)p)->pcGewaesserNr);
	TX_ASSERT( NULL != *(((HYDRAULIK *)p)->pcGewaesserNr));

	//--------------Hier kommt Malte -----------
//------------Versuch Hydraulik-Test------------------------


	if ( !p) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKEINPUNKT, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		return false;
	}

	
	if ( !m_pGewHyd) {
		KompaktProtokoll(m_pLocProt,"\t==> Hydraulik : Keine Gebiete definiert !\n");
		return false;
	}

	if (!HolePunkteVonKompakt(m_pGewHyd,p)) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKEINPUNKT, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		KompaktProtokoll(m_pLocProt,"\t==> Hydraulik : Keine Punkte von Gewässerkataster übergeben !\n");
		return false;
	}

// Loeschen alter Punkte
	long lPIdent = BildeObjektKlasse(cHydraulikHochwasser,cUeberschwemmungsPunkt);
// Loeschen alter Flächen
	long lFIdent = BildeObjektKlasse(cHydraulikHochwasser,cUeberschwemmungsGebiet);

	CTable t (*m_pGewHyd);

	for (t.First();t.Valid();t.Next()) {

		KP_GEWLock l(t);
		char *pGewNr = new char [_MAX_PATH];
		if ( pGewNr && l->GewNr()) {
			strcpy(pGewNr,l->GewNr());
	
			LoeschenUeberschwemmungsGebiet ( lPIdent,pGewNr);
			LoeschenUeberschwemmungsGebiet ( lFIdent,pGewNr);

			DELETE_OBJ(pGewNr);
		}
	}
// KK010123
	DEX_RebuildSight();

	return true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool CKompiasExtension :: MischeHydraulik ( void )
{
	bool iFlag = false;

	if ( !m_pGewHyd || m_pGewHyd->Count() == 0L)
		return iFlag;

	if ( m_pKH && m_pKH->GewClass()) {
//---------------Objekte an Ident hängen

		if ( m_pGewAlle)  {
//			m_pGewAlle = GesamtGewaesser();
		
			AbgleichGewKataster( m_pGewHyd,m_pGewAlle);
		} else {
			if( !EinzelGewaesser(m_pGewHyd)) {
				DELETE_OBJ ( m_pGewHyd);
				MessageBox (__hWndM, 
				 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),180),
				 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
				 MB_OK|MB_ICONHAND);
				return false;
			}
		}
//--------------------------------------------------------------------
		m_lONr = -1L;
		if (!SpeicherePunktInTrias ( m_pGewHyd)) {
			DELETE_OBJ ( m_pGewHyd);
			MessageBox (__hWndM, 
//			 "Punkt konnte Gewässer nicht zugeordnet werden",
			 ResString (ResID(IDS_KEINGEWAESSERPUNKT, &RF()),180),
			 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
			MB_OK);
			return false;
		}

		iFlag = BildeUeberschwemmungsGebiet (m_pGewHyd);


	}


	DELETE_OBJ ( m_pGewHyd);

	return iFlag;

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: ZeigeUeberschwemmungsPunkt ( void )
{
	if (m_lONr == -1L)
		return;

	long Cont[4];
	DEX_GetObjContainer(m_lONr,Cont);

	Cont[0] = Cont[0] - 100000;
	Cont[1] = Cont[1] + 100000;
	Cont[2] = Cont[2] - 100000;
	Cont[3] = Cont[3] + 100000;

	DEX_SetActiveSightContainer(Cont);
	DEX_RePaint();

}
//-------------------------------------------------------------------------
bool CKompiasExtension :: BildeUeberschwemmungsGebiet ( KPTree *pGewP )
{
	if ( !pGewP)
		return false;
	if ( !m_pKH || !m_pKH->HydrClass()) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_DEFNOUEBERSCHWEMMUNG, &RF()),180),
		 ResString (ResID(IDS_STRCAPTION, &RF()),180),
		MB_ICONSTOP);

		return false;
	}



	CEierUhr Wait (MVWind());


	LadeObjektKlasse ( OTFlaeche, m_pKH->HydrClass());
	
	TR_OBJTree * pVerschn = new TR_OBJTree;
	if (!pVerschn)
		return false;

	CTable t( *pGewP);
	bool iFlag = false;
	long lONP = 0L;

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if (!l)
			continue;
		KP_LATree *pOBJ = l->LA();
		if ( !pOBJ)
			continue;
		CTable d(*pOBJ);

		for ( d.First(); d.Valid(); d.Next() ) {
			KP_LALock e(d);
			if ( !e)
				continue;
			lONP = e->Objekt();

			if (lONP ==0L || lONP == -1L)
				continue;

			char *pT = new char [_MAX_PATH];

			if (pT) {
				wsprintf(pT,"\n\t+++ TopologieTest PunktObjekt %ld \n",lONP);
				KompaktProtokoll ( m_pLocProt,pT);
				DELETE_OBJ(pT);
			}

			TR_OBJTree * pVers = new TR_OBJTree;
			if (!pVers)
				continue;

			if (!TopologieTest ( lONP,m_pKH->HydrClass(),pVers)) {
				continue;
			} else {
				iFlag = true;
				HydroMerge ( pVerschn,pVers);
			}

			DELETE_OBJ(pVers);

		}
		
	}

	if (pVerschn->Count() == 0L ) {
		DELETE_OBJ ( pVerschn);
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_NOHYDROAREA, &RF()),180),
		 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
		MB_OK);
		return false;
	}

// Flächenverschnitt

// auf Vektor korrigieren !

	long lCount = (long) pVerschn->Count();
	long * plONF = new long [lCount + 1];
	*plONF = 0L;

	long lONF = 0L;
	lCount = 0L;
	
	
	char *pGewNr = NULL;

	if (lONP > 0L )
		pGewNr = HoleTRiASGewaesserNummer(lONP,m_pKH->CodeGewNr());

	{
	CTable h(*pVerschn);
	for ( h.First(); h.Valid(); h.Next() ) {
		TR_OBJLock i(h);
		if ( !i)
			continue;
		long lONF = i->Object();

		lCount++;
		*plONF = lCount;
		*(plONF+lCount) = lONF;

	}
	}

	DELETE_OBJ (pVerschn);

	if ( lCount > 0L) {

		long lIdent = BildeObjektKlasse(cHydraulikHochwasser,cUeberschwemmungsGebiet);

		if (!DoppelnObjekt ( plONF, lIdent ,pGewNr)) {
			DELETE_OBJ (plONF);
			DELETE_OBJ (pGewNr);
			return false;
		}

		ShowObjsContainer (plONF);

	}

	DELETE_OBJ (plONF);
	DELETE_OBJ (pGewNr)


	return iFlag;
}
//-------------------------------------------------------------------------
void CKompiasExtension :: HydroMerge ( TR_OBJTree *pVerschn, TR_OBJTree *pVers)
{
	if ( !pVerschn || !pVers)
		return;
	if (pVers->Count()<= 0L)
		return;
	CTable t(*pVerschn);

	CTable d(*pVers);

	for (d.First(); d.Valid(); d.Next()) {

		TR_OBJLock m(d);

		long lONr = m->Object();

		if ( !t.Find (&lONr)) {
			TR_OBJCreator OCr (*pVerschn);
			ContCreate (OCr,TR_OBJ) (lONr, NULL);	//neu in pVerschn einarbeiten
			
		}
	}
	
}

//--------------------------------------------------------------------------
void CKompiasExtension :: ShowObjsContainer ( long *plONR)
{

	if ( !plONR || *plONR <= 0L)
		return;
	long lCnt = *plONR;

	long RefCont[4];
	long Cont[4];

	long lONF = *(plONR+1);
	DEX_GetObjContainer(lONF,RefCont);
	DEX_GetObjContainer(lONF,Cont);


	for ( long i = 2; i < lCnt+1; i++ ) {

		long lONF = *(plONR+i);

		DEX_GetObjContainer(lONF,RefCont);

		if ( Cont[0] > RefCont[0] )
			Cont[0] = RefCont[0];
		if ( Cont[1] < RefCont[1] )
			Cont[1] = RefCont[1];
		if ( Cont[2] > RefCont[2] )
			Cont[2] = RefCont[2];
		if ( Cont[3] < RefCont[3] )
			Cont[3] = RefCont[3];

	}


	Cont[0] = Cont[0] - ( Cont[1] - Cont[0])/2;
	Cont[1] = Cont[1] + ( Cont[1] - Cont[0])/2;
	Cont[2] = Cont[2] - ( Cont[3] - Cont[2])/2;
	Cont[3] = Cont[3] + ( Cont[3] - Cont[2])/2;

	DEX_SetActiveSightContainer(Cont);
	DEX_RePaint();

}

//-------------------------------------------------------------------------
bool CKompiasExtension :: TopologieTest ( long lONP , TR_OCLTree *pHydr, TR_OBJTree *pVerschn)
{
//------------Versuch Topologie-Test------------------------
	if ( !pHydr || !pVerschn || lONP == 0L)
		return false;

	bool iFlag = false;

	TR_OBJTree *pHObj = new TR_OBJTree;
	 
	CTable f(*pHydr);
//-Zusammenstellen aller möglichen Flächen in pHObj--------
	for ( f.First(); f.Valid(); f.Next()) {
		TR_OCLLock g(f);
		if (!g)
			continue;
		TR_OBJTree *pOBJ = g->OBJ();
		if ( !pOBJ)
			continue;
		CTable h(*pOBJ);

		for ( h.First(); h.Valid(); h.Next() ) {
			TR_OBJLock i(h);
			if ( !i)
				continue;
			long lONF = i->Object();

			if (!PunktInFlaeche ( lONF,lONP)) {
				continue;
			} else {
				TR_OBJCreator OCr ( *pHObj);
				ContCreate ( OCr, TR_OBJ ) (lONF,NULL);
				iFlag = true;			
			}

		}
	}
//--------------------------------------------------------------------
	if ( iFlag) {	//wenigstens eine Fläche ist gefunden
//-----------Jetzt Hoehenwerte vergleichen
		if ( !EchterInnenPunkt ( lONP, pHObj, pVerschn)) {
//-------Hoehenwerte nicht ausreichend-------------------------------
			iFlag = false;
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINPUNKTINFLAECHE, &RF()),180),
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);

		} else {

	// Nun Flächenvereinigung ???
			short iCtrl = true;
			while ( iCtrl)
				iCtrl = NachbarFlaechen ( lONP,pVerschn);

			char *pT = new char [_MAX_PATH];

			if (pT) {
				wsprintf(pT,"+++ PunktObjekt %ld mit Nachbarflächen +++ \n",lONP, pVerschn->Count());
				KompaktProtokoll ( m_pLocProt,pT);
				DELETE_OBJ(pT);
			}

		}

	} else {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_STRKEINEFLAECHE, &RF()),180),
		 ResString (ResID(IDS_STRCAPTION, &RF()),180),
		MB_ICONSTOP);
	}

	DELETE_OBJ ( pHObj);

	return iFlag;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
bool CKompiasExtension :: NachbarFlaechen ( long lONP, TR_OBJTree *pVerschn)
{
	if ( !pVerschn)
		return false;
	
	CEierUhr Wait (MVWind());

	double dHP = HoleHoehe ( lONP);
	if ( dHP == 0.0)
		return false;


	double dHF = 0.0;

	short iFlag = false;


	CTable t (*pVerschn);

	TR_OBJTree *pRefVer = new TR_OBJTree;

	{
	CTable d ( *pRefVer);

	for (t.First(); t.Valid(); t.Next()) {

		TR_OBJLock l(t);

		//	 hier Schleife anlegen 
		//	 noch keine Nachbarn untersucht

		short iTyp = l->Typ();

		if ( !iTyp ) {	

			long * plRand = EchteRandFlaeche ( dHP,l->Object());

			if (plRand) {

				long lCnt = *plRand;

				for ( long i = 1L; i < lCnt + 1; i++) {

					long lRef = *(plRand+i);
					if ( !d.Find (&lRef)) {
						TR_OBJCreator OCr (*pRefVer);
						ContCreate (OCr,TR_OBJ) (lRef, NULL);	//neu
						iFlag = true;
					}
				}

				DELETE_OBJ(plRand);

			}

			l->SetTyp(true);

		}

	}

	}

//	Abgleich der Objekte

	if ( pRefVer && pRefVer->Count() == 0L) {
		DELETE_OBJ(pRefVer);
		return iFlag;
	}

	{
	CTable dd(*pRefVer);
	for (dd.First(); dd.Valid(); dd.Next()) {

		TR_OBJLock mm(dd);

		long lONr = mm->Object();

		if ( !t.Find (&lONr)) {
			TR_OBJCreator OCr (*pVerschn);
			ContCreate (OCr,TR_OBJ) (lONr, NULL);	//neu in pVerschn einarbeiten

			iFlag = true;			
		}
	}
	}

	DELETE_OBJ(pRefVer);


	return iFlag;

}
//-------------------------------------------------------------------------
bool CKompiasExtension :: PunktInFlaeche ( long ONF, long ONP )
{
//------------Versuch Topologie-Test------------------------

	if ( m_pTop) {
		Relat Rel;
		HRESULT hr = m_pTop->TopoRelationObjObj_ONr ( ONF,ONP,&Rel);
		if (FAILED(hr)) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINETOPOLOGIE, &RF()),180),
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);
			return false;
		}
		if ( Rel != REL_INN)
			return false;

		return true;
	}
	return false;
}
//

//-------------------------------------------------------------------------
bool CKompiasExtension :: EchterInnenPunkt ( long lONP, TR_OBJTree *pObj ,TR_OBJTree *pVerschn)
{
	if ( !pObj || !pVerschn)
		return false;

	double dHP = HoleHoehe ( lONP);
	if ( dHP == 0.0)
		return false;

	char *pT = new char [_MAX_PATH];

	if (pT) {
		wsprintf(pT,"\n\t**** Objekt %ld echter InnenPunkt mit Höhe %ld ***\n",lONP,(long)(dHP*100));
		KompaktProtokoll ( m_pLocProt,pT);
		DELETE_OBJ(pT);
	}

	double dHF = 0.0;

	
	CTable t (*pObj);
	CTable v (*pVerschn);

	for (t.First(); t.Valid(); t.Next()) {
		TR_OBJLock l(t);
		dHF = HoleHoehe ( l->Object());
		if ( dHF == 0.0)
			continue;


		if ( dHF < dHP ) {
			long lONF = l->Object();

			// Echte Randflächen einsetzen !
			if ( !v.Find(&lONF)) {
				TR_OBJCreator OCr (*pVerschn);
				ContCreate (OCr,TR_OBJ) (lONF, NULL);
			} else {
				TR_OBJLock x(v);
				if (x)
					x->SetTyp(false);		// neue Umgebung mit neuer Höhe
			}
	
// hier Schleife anlegen 

			long * plRand = EchteRandFlaeche ( dHP,lONF);

			if (plRand) {

				long lCnt = *plRand;
				for ( long i = 1L; i < lCnt + 1; i++) {
					long lRef = *(plRand+i);
					if ( !v.Find (&lRef)) {
						TR_OBJCreator OCr (*pVerschn);
						ContCreate (OCr,TR_OBJ) (lRef, NULL);	// Nur Neue aufnehmen
					} else {
						TR_OBJLock x(v);
						if (x)
							x->SetTyp(false);		// neue Umgebung mit neuer Höhe

					}
				}

				DELETE_OBJ(plRand);
			}

		}
		
	}


	return true;
}
//-------------------------------------------------------------------------
long * CKompiasExtension :: EchteRandFlaeche ( double dHP, long lONF)
{
	if (dHP <= 0.0 || lONF == 0L || lONF == -1L)
		return NULL;

	long Cont[4];

	DEX_GetObjContainer(lONF,Cont);

	TR_OBJTree * pObj = new TR_OBJTree;
	if (!pObj)
		return NULL;

	ENUMRECHGEOMETRIE ERGI;
	memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
	ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
	ERGI.lCont = &Cont[0];
	ERGI.iMode = ERGActSight;
// Objekte zählen
	ERGI.eFcn = (RECHGEOMETRIEPROC) EnumNachbarObjects;

	ERGI.pData = pObj;
	DEX_EnumRechGeometrie( ERGI );

	if ( pObj->Count() == 0L) {
		DELETE_OBJ(pObj);
		return NULL;
	}

	long *plONR = new long [pObj->Count()+1];
	*plONR = 0L;
	
	{
	CTable t (*pObj);


	for (t.First(); t.Valid(); t.Next()) {
		TR_OBJLock l(t);

		if (lONF !=  l->Object()) {

			if ( HydraulikFlaeche( l->Object(),dHP))
				EchteNachbarFlaeche (lONF,l->Object(),plONR);
		}

	}
	}

	DELETE_OBJ(pObj);

	if (*plONR == 0L) {
		DELETE_OBJ(plONR);
		return NULL;
	} 

	return plONR;
}
//------------------------------------------------------------------------
bool CKompiasExtension :: HydraulikFlaeche ( long lONr , double dHP)
{
	if ( lONr == -1L || lONr == 0L)
		return false;

	if ( dHP <= 0.0)
		return false;

	long lIdent = DEX_GetObjIdent(lONr);

	CTable t(*m_pKH->HydrClass());

	if (!t.Find (&lIdent))
		return false;

//	Definiertes pot.Ueberschwemmungsgebiet

	double dHF = HoleHoehe ( lONr);
	if ( dHF <= 0.0)
		return false;


	if ( dHF > dHP ) 
		return false;


	return true;
}
//------------------------------------------------------------------------
//-------------------------------------------------------------------------
bool CKompiasExtension :: EchteNachbarFlaeche ( long lONF1, long lONF2, long *plListe )
{
//------------Moertl-Touch------------------------

	if ( m_pTop) {

//		Relat Rel;
		UINT Rel;


		HRESULT hr = m_pTop->TopoRelationObjObj2_ONr ( lONF1,lONF2,&Rel);
		if (FAILED(hr)) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINETOPOLOGIE, &RF()),180),
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);
			return false;
		}

		UINT RREL = REL_TOUCH;

		if (( Rel & RREL) <= 0)
			return false;

		long lCnt = *plListe;
		lCnt++;
		*(plListe + lCnt) = lONF2;
		*plListe = lCnt;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------
bool CKompiasExtension :: DoppelnObjekt ( long *plONr , long lIdent, char *pGewNr)
{
	if ( !plONr || *plONr <= 0L || lIdent == 0L )
		return false;

	long *plNewO = new long [*plONr + 1];
	if ( !plNewO)
		return false;
	*plNewO = 0L;

	long lEnd = *plONr;

	LoeschenUeberschwemmungsGebiet ( lIdent,pGewNr);

	for ( long i = 1L ; i < lEnd + 1 ; i++ ) {

		long lONr = *(plONr+i);
		if ( lONr == -1L ||  lONr == 0L)
			continue;

		if (!LadeObjektGeometrie ( lONr)) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINOBJEKT, &RF()),180),
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);
			continue;
		}

		m_pIOG->SetIdent ( lIdent);

	#if _MSC_VER < 1100
		HRESULT hr = m_pIOG->GeometrieAnTRiAS ( false, NULL);
	#else
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);
		HRESULT hr = m_pIOG->GeometrieAnTRiASEx (INT_PTR(hPr), false, NULL);
	#endif

		if ( hr != S_OK )
			continue;

		long lNewONr;
		HRESULT ho = m_pIOG->GetONr ( &lNewONr );	
		if ( hr != S_OK )
			continue;


		if ( pGewNr && *pGewNr != '\0')
			ModifiziereMerkmal (lNewONr,m_pKH->CodeGewNr(), pGewNr);

		long lCnt = *plNewO;
		lCnt++;

		*(plNewO + lCnt) = lNewONr;
		*plNewO = lCnt;

	}

	long lCount = *plNewO;

	bool MyFlag = FlaechenBlinkeln ( lIdent, plNewO,pGewNr);


	DELETE_OBJ (plNewO);
	return MyFlag;

//	}
//	return false;
}
//------------------------------------------------------------------------
void CKompiasExtension :: LoeschenUeberschwemmungsGebiet ( long lIdent, char *pGewNr)
{

	if ( !pGewNr || *pGewNr == '\0' || lIdent == 0L)
		return;


	MERKMALSDEFINITION MD;
	memset (&MD,'\0',sizeof(MERKMALSDEFINITION) );
	MD.lNummer = m_pKH->CodeGewNr();
	MD.pNummer = pGewNr;

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) LoescheTRiASObjekte;
	ELK.eKey = lIdent;
	ELK.ePtr = &MD;
	DEX_EnumIdentObjects(ELK);

	return;

}

//------------------------------------------------------------------------
bool CKompiasExtension :: FlaechenVereinigung ( long lIdent, long *plONr ) 
{
	if ( !plONr || *plONr <= 0L || lIdent == 0L)
		return false;

	if ( !m_pObjOp)
		return false;

	try {
///////////////////////////////////////////////////////////////////////
// Klasse für die Rückgabe der Objektnummern der erzeugten Teilflächen
	CEnumObjectsByNumber* pIEnumObj = CEnumObjectsByNumber :: CreateInstance ();

		if (! pIEnumObj) 
			return false;
//////////////////////////////////////////////////////////////////////

		long lCount = *plONr;

	// Übertragen der Objektnummern 

		for (long i = 0; i < lCount; i++) {
			pIEnumObj -> AddObject (*(plONr+i+1));
		}

		IEnumLONG * pIEnum = NULL;

		HRESULT hr = m_pObjOp->OrArea (pIEnumObj,(ulong) lIdent,SFORM_PERM,&pIEnum);
		if (FAILED(hr)){
			pIEnumObj->Release();
			return false;
		}

		pIEnumObj->Release();
		ULONG ulCount = pIEnum->Count();
		if ( 0 >= ulCount  ) {
			pIEnum->Release();
			return false; 
		}

		pIEnum->Release();

		return true;

	} catch ( ... ) {

		MessageBox ( __hWndM,
			 " Fehler bei der Flächenvereinigung ",
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);
		return false;

	}

	return false; 

}
//-------------------------------------------------------------------------
double CKompiasExtension :: HoleHoehe ( long lONr )
{
	double dH = 0.0;
	if ( lONr == -1L ||  lONr == 0L)
		return dH;
	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return dH;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)m_pKH->CodeHydrHoehe();	// MerkmalsCode

	if ( DEX_GetTextMerkmal ( tm )) {
		
		char *ptr = strchr(pMText,',');
		if (ptr)
			*ptr = '.';

		dH = atof ( pMText);

	}
	DELETE_OBJ ( pMText);
	return dH;

}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void CKompiasExtension :: AktualisiereHoehenWert ( long lONr )
{

	if ( lONr == -1L || lONr == 0L)
		return;
	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return;

//	Objektname durchsuchen

	long lIdent = DEX_GetObjIdent ( lONr);
	ulong lSMCode = DEX_GetObjNameMCode(lIdent);
	GetStandardMCode ( lONr, lSMCode, pBuffer);
	long lMCode = m_pKH->CodeHydrHoehe();

	if ( pBuffer && *pBuffer != '\0') {

		char *ptr = strchr(pBuffer,',');
		if ( ptr)
			*ptr = '.';

		SetObjektWert ( lONr,lMCode,pBuffer);
	}
	

	DELETE_OBJ ( pBuffer);
	return;

}
//-------------------------------------------------------------------------
//----------KPWINOT.CXX
