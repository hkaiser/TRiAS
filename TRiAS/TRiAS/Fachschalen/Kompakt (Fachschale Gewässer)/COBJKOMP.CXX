
// File: COBJKOMP.CXX

#include "kompp.hxx"

#include <shellapi.h>

#include <triashelper.h>
#include <triashelper_i.c>

#include <oleguid.h>
#include <dirisole.h>
#include <eonrguid.h>
//#include <ienumonr.hxx>	// CEnumObjectsByNumber

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include "kompdef.h"
#include <xtsnaux.hxx>
#include <igeometr.hxx>
#include "triasdef.h"
#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"

#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kpstatus.hxx"

#include "version.h"
#include "kompias.h"
#include "about.h"
#include "kompcls.hxx"
#include "about.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32


// --------------------------------------------------------------------------------------------
// benötigte SmartInterfaces
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber
DefineSmartInterface(EnumLONG);	// WEnumLONG

/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
long CKompiasExtension :: ObjektPuffer( long lONr) 
{
	long lPONr = 0L;

	if ( !m_pPuf)
		return lPONr;

	IEnumLONG * pIEnum = NULL;

	double dBr = m_iDefPuffer;		// 10 Meter reichen !
	if (dBr <= 0)
		dBr = PUFFERZONE;

	short iAnz = 1;			// 1 Puffer

	long lIdent = DEX_GetObjIdent(lONr);

	try {


		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

		HRESULT hr = m_pPuf->RealBuffering_ONr (lONr,dBr,iAnz,PBAU_VOLL,SFORM_PERM,lIdent,&pIEnum);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

		if ( FAILED(hr))
			_com_issue_error(hr);

	} catch (_com_error&){
		return lPONr;
	}


	ULONG ulCount = pIEnum->Count();

	if ( 0L >= ulCount) {
		pIEnum->Release();
		return lPONr; 
	}

	long ONr;

	for ( pIEnum->Reset(); S_OK == pIEnum->Next(1,&ONr,NULL); /**/)
	{

		// Objekt auf GI Testen !!
		short Status = DEX_GetObjectType (ONr);

	//--------------Zuordnung----------------------------
		if ( Status == OGFlaeche ) {
			lPONr = ONr;
		} else {
			MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			DEX_DeleteObject(ONr);
			MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		}
	}


	pIEnum->Release();

	return lPONr;
}
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
void CKompiasExtension ::  TopologieRecherche ( long lONF)
{
	CEierUhr Wait (MVWind());
	if ( 0L >= lONF )
		return;

	CTop_ObjTree * pObj = BildeObjektKlasse ( m_pKH->GewClass());
	if ( !pObj ) 
		return;


	long lCount = (long) pObj->Count();
	long *plONR = new long [lCount+1];
	if ( !plONR)
		return;

	lCount = 0L;

	CTable d(*pObj);

	for (d.First(); d.Valid(); d.Next()) {
		CTop_ObjLock e(d);
		if ( !e)
			continue;
		long lONr = e->PObject();
		if ( 0 < lONr ) {
			lCount++;
			*(plONR + lCount) = lONr;
		}
	}	


	if ( 0L == lCount) {
		DELETE_OBJ ( plONR);
		return;
	}

	*plONR = lCount;

	if ( m_pModObj) {
		CTreeLoeschen ( m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}

	long *pInnen = NULL;
	long *pInAus = NULL;
	long *pErgObj = NULL;
	
	{
		CTopObject *m_pTopCLS = new CTopObject(lONF,plONR,&pInnen,&pInAus);
		m_pTopCLS->FInit();
		m_pTopCLS->SetWindowHandle( ORWind(m_hWnd));
		pErgObj = m_pTopCLS->LinienTeile();
		short Flag = ROSortObjNr;
		if ( pInnen )
			CreateORWindow ( Flag, 80, 300, pInnen, "Innenliegende Objekte", 0, 255, 255);
		if ( pInAus )
			CreateORWindow ( Flag, 80, 100, pInAus, "Modifizierte Objekte", 255, 255, 0);
	}
	
	DELETE_OBJ ( plONR);
	DELETE_OBJ ( pErgObj);
	DELETE_OBJ ( pInnen);
	if ( pInAus) {
		Loeschen ( pInAus );
		DELETE_OBJ ( pInAus);
	}
	DELETE_OBJ ( pObj);

	return;
}
/////////////////////////////////////////////////////////////////////////
void CKompiasExtension ::  FlaechenAnalyse ( long lONF)
{
	if ( 0L == lONF || -1L == lONF)
		return;

// Flaechen auswaehlen
	long *plONR = NULL;
	long lIdent = DEX_GetObjIdent(lONF);
	{
	TriasFlaechen TF ( MVWind(),FLAECHENCLSAUSWAHL, RF(), lIdent);
	TF.Show(Centre);  
	if (TF.Result() == 1) {
		plONR = TF.FlaechenCls();
	} else
		return;
	}

	if ( !plONR)
		return;

	if ( m_pModObj) {
		CTreeLoeschen ( m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}

	long *pInnen = NULL;
	long *pInAus = NULL;
	long *pErgObj = NULL;
	
	{
		CTopObject *m_pTopCLS = new CTopObject(lONF,plONR,&pInnen,&pInAus);
		m_pTopCLS->FInit();
		m_pTopCLS->SetWindowHandle( ORWind(m_hWnd));
		pErgObj = m_pTopCLS->FlaechenTeile();
		short Flag = ROSortObjNr;
		if ( pInnen )
			CreateORWindow ( Flag, 80, 300, pInnen, "Innenliegende Objekte", 0, 255, 255);
		if ( pInAus )
			CreateORWindow ( Flag, 80, 100, pInAus, "Modifizierte Objekte", 255, 255, 0);
	}
	
	DELETE_OBJ ( plONR);
	DELETE_OBJ ( pErgObj);
	DELETE_OBJ ( pInnen);

	if ( pInAus) {
		if ( 0L < *pInAus) 
			CTreeLaden( pInAus);
		DELETE_OBJ ( pInAus);
	}

	return;
}
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
CTop_ObjTree * CKompiasExtension :: BildeObjektKlasse ( TR_OCLTree *pGewClass)
{
	if ( !pGewClass)
		return NULL;

	CTable t (*pGewClass);

	CTop_ObjTree *pOBJ = new CTop_ObjTree;
	if ( !pOBJ)
		return NULL;

	CEierUhr Wait (MVWind());

	long lCount = 0L;

	lCount = pGewClass->Count();

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheObjekte;
	lCount = 0;

	{
	CTable d( *pOBJ);
//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		ELK.eKey = Ident;
		ELK.ePtr = pOBJ;
		DEX_EnumIdentObjects(ELK);
		lCount ++;


	}

	if ( 0 == pOBJ->Count()) {
		DELETE_OBJ ( pOBJ);
		return NULL;
	}

	}

	return pOBJ;
}
////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
TR_OBJTree * CKompiasExtension :: LadeObjektTeilKlasse ( short iTyp, long lONF, TR_OCLTree *pGewClass)
{
	if ( 0 >= lONF || !pGewClass)
		return NULL;


	TR_OBJTree *pModi = new TR_OBJTree;
	if ( !pModi)
		return NULL; 				

	CTable t (*pGewClass);

	CEierUhr Wait (MVWind());

	long lCount = 0L;


	lCount = pGewClass->Count();

	OBJEKTKLASSENTYP OT;
	OT.iTyp = iTyp;

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheGewaesserObjekt;
	lCount = 0;


	if ( m_pModObj ) {
		CTreeLoeschen ( m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();

		TR_OBJTree *pOBJ;
		pOBJ = l->OBJ();
		if (pOBJ) 
			l->DeleteObj();

		pOBJ = new TR_OBJTree;
		if ( !pOBJ)
			continue;

		ELK.eKey = Ident;
		OT.pOBJ = pOBJ;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);
		lCount ++;

		if ( pOBJ->Count() == 0 ) {
			DELETE_OBJ ( pOBJ);
		} else {
			m_pStop = false;
			TR_OBJTree *pNewOBJ = ObjektKontrolle ( lONF, pOBJ, pModi);
			if ( pNewOBJ)
				l->StoreObj( pNewOBJ);	// Auch NULL
			DELETE_OBJ ( pOBJ);
			if ( m_pStop) {		// Abbrechen gedrueckt !!
				DELETE_OBJ (pModi);
				m_pStop = false;
				return NULL;
			}
		}

	}


	if (pModi->Count() == 0 )
		DELETE_OBJ (pModi);

	return pModi;
}
//----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
TR_OBJTree *CKompiasExtension :: ObjektKontrolle ( long lONF, TR_OBJTree *pObj, TR_OBJTree *pModi)
{

	if ( 0 >= lONF || !pObj )
		return NULL;

	if (!pModi)
		return NULL;

	long lCount = (long) pObj->Count();
	if ( 0 == lCount)
		return NULL;

	long *plONR = new long [lCount+1];
	if ( !plONR)
		return NULL;


	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	m_pStatus = new CStatus ( ORWind(m_hWnd), &RF(),lCount, "Objektkontrolle");
	m_pStatus->Show();

	lCount = 0L;

	CTable d(*pObj);


	for (d.First(); d.Valid(); d.Next()) {
		TR_OBJLock e(d);
		if ( !e)
			continue;
		long lONr = e->Object();
		if ( 0 < lONr ) {
			lCount++;
			*(plONR + lCount) = lONr;
		}

		if ( m_pStatus->Break()) {

			MessageBox ( m_hWnd,
			 ResString (ResID(IDS_STOPCONTROL, &RF()),50),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),50),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			DELETE_OBJ ( plONR);
			m_pStop = true;
			return NULL;
		}

		if ( m_pStatus) 
			m_pStatus->SetValue( lCount, lONr);
		
	}	

	DELETE_OBJ ( m_pStatus);

	if ( 0L == lCount) {
		DELETE_OBJ ( plONR);
		return NULL;
	}

	*plONR = lCount;


	long *pInnen = NULL;
	long *pInAus = NULL;
	long *pErgObj = NULL;
	long *pModObjekt = NULL;
	
	{
		CTopObject *m_pTopCLS = new CTopObject(lONF,plONR,&pInnen,&pInAus);
		m_pTopCLS->FInit();
		m_pTopCLS->SetWindowHandle( ORWind(m_hWnd));
		pErgObj = m_pTopCLS->LinienTeile();
		pModObjekt = m_pTopCLS->ZuModifizieren();
	}

	if ( pModObjekt ) {
		for ( long j = 0; j < *pModObjekt; j++ ) {
			
			long lONr = *(pModObjekt + j + 1);
	
			CTable f(*pModi);
			if ( !f.Find ( &lONr) ) {
				TR_OBJCreator OCr ( *pModi);
				ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
			}
		} 
		DELETE_OBJ ( pModObjekt);
	}	

	DELETE_OBJ ( pInnen);

	if ( pInAus) {
		if ( 0L < *pInAus) 
			CTreeLaden( pInAus);
		DELETE_OBJ ( pInAus);
	}
	DELETE_OBJ ( plONR);

	if (!pErgObj)
		return NULL;

	long lDim = *pErgObj;
	if ( 0L == lDim ) {
		DELETE_OBJ ( pErgObj);
		return NULL;
	}


	// Bäumchen pflanzen
	TR_OBJTree *pNewObj = new TR_OBJTree;
	if ( !pNewObj) {
		DELETE_OBJ ( pErgObj);
		return NULL;
	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	m_pStatus = new CStatus ( ORWind(m_hWnd), &RF(),lDim, "Objektzusammenstellung");
	m_pStatus->Show();

	for ( long i = 0L; i < lDim; i++ ) {
		long lONr = *(pErgObj + i + 1);
	
		CTable t(*pNewObj);
		if ( !t.Find ( &lONr) ) {
			TR_OBJCreator OCr ( *pNewObj);
			ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
		}
		if ( m_pStatus) 
			m_pStatus->SetValue( i+1, lONr);

	}

	DELETE_OBJ ( m_pStatus);

	DELETE_OBJ ( pErgObj);

	if ( 0 == pNewObj->Count() ) 
		DELETE_OBJ ( pNewObj);

	return pNewObj;

}
///////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
long CKompiasExtension :: AnzahlTRiASGewaesser ( TR_OCLTree *pTRGew )
{

	if ( !pTRGew )
		return 0L;

	CTable t (*pTRGew);
	long lNumber = 0L;

	if ( pTRGew->Count() == 0L)
		return lNumber;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		lNumber = lNumber + l->OBJ()->Count();
	}

	return lNumber;

}
///////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
KPTree *CKompiasExtension :: SpeichernGewaesserNummer_Flaeche ( long lONF,ulong lMCode, ulong lMCodeN, TR_OCLTree *pTRGew , TR_OBJTree *pModi)
{
	if ( lONF == -1L || lONF == 0L || 0L == lMCode || 0L == lMCodeN)
		return NULL;

	if ( !pTRGew )
		return NULL;

	KPTree *pGew = new KPTree;
	if ( !pGew)
		return NULL;

	long lCount = AnzahlTRiASGewaesser ( pTRGew);

	if ( lCount > 0L) {

		if ( m_pStatus)
			DELETE_OBJ ( m_pStatus);
		m_pStatus = new CStatus ( MVWind(), &RF(),lCount, "Modifizierte Gewässer");
		m_pStatus->Show();
		lCount = 0L;

		CTable t (*pTRGew);
		long lOrig = -1;
	
		for ( t.First(); t.Valid(); t.Next()) {
			TR_OCLLock l(t);
			if ( !l)
				continue;
			TR_OBJTree * pOBJ = l->OBJ();
			if ( !pOBJ)
				continue;
			CTable e (*pOBJ);
			for (e.First(); e.Valid(); e.Next() ) {
				TR_OBJLock n(e);
				lOrig = -1;
				long ONr = n->Object();
				lCount++;
				if ( m_pStatus)
					m_pStatus->SetValue( lCount, ONr);

				char *pGewNr = HoleGewaesserNummer ( ONr, lMCode);			
				if (!pGewNr )
					continue;
				n->SpeichernGewaesserNummer (pGewNr);
				char *pGewName = HoleGewaesserName ( ONr, lMCodeN, pGewNr,true); // Mit Malte
				if (pGewName && *pGewName != '\0')
					n->SpeichernGewaesserName (pGewName);

				LadeGewaesserKataster (pGewNr, pGewName,pGew);

				long lLLen = 0L;
				lLLen = LinienLaenge(ONr);
				n->StoreObjLaenge ( lLLen );

				CTable f (*pGew);
				if ( f.Find (pGewNr)) {
					short iVerarb = false;
					KP_GEWLock g(f);

					TR_OBJTree *pTObj = g->GetOBJ();
					if ( !pTObj) {
						iVerarb = true;
						pTObj = new TR_OBJTree;
					}
					if ( OriginalObjekt(n->Object(),pTObj,lLLen)) {
						lOrig = n->Object();
						g->SpeichereObjekt(n->Object());
						g->SpeichereObjektLaenge ( lLLen );
	// Auf zu Malte !!!
						long lLaenge = 0L;
						long lEta = 0L;
						long lLen = 0L;
						lLaenge = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr,lLen, lEta);
						if ( lLaenge > 0L ) 
							g->SetKompaktLen ( lLaenge );

					} else {
						g->SpeichereObjekt ( 0L);
						g->SpeichereObjektLaenge (0L);
					}
	
					if ( iVerarb ) {
						if ( pTObj->Count() == 0 ) {
							DELETE_OBJ ( pTObj);
						} else {
							g->SetOBJ ( pTObj);
						}
					}
				}

				DELETE_OBJ ( pGewNr);
				DELETE_OBJ ( pGewName);
			
			}
		}

		if ( m_pStatus)
			DELETE_OBJ ( m_pStatus);
	}
//--------------Nun die Originale draufsetzen
	if ( pModi && pModi->Count() > 0 )
		SetOriginalObjekt ( pModi , pGew, lMCode);
	
	return pGew;
}
///////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
KPTree *CKompiasExtension :: HoleGewaesserNummer_Flaeche ( long lONF,ulong lMCode, ulong lMCodeN, KPTree *pGewAlle)
{
	if (  lONF == -1L || lONF == 0L || 0L == lMCode || 0L == lMCodeN)
		return NULL;

	if ( !pGewAlle || pGewAlle->Count() == 0L)
		return NULL;

	long lNCount = pGewAlle->Count();
	if ( lNCount <= 0L)
		return NULL;

	KPTree *pGew = new KPTree;
	if ( !pGew)
		return NULL;


	if ( m_pStatus)
			DELETE_OBJ ( m_pStatus);
	m_pStatus = new CStatus ( MVWind(), &RF(),lNCount, "Modifizierte Gewässer");
	m_pStatus->Show();
	long lCount = 0L;

	if ( m_pModObj) {
		CTreeLoeschen ( m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}
	
	long Cont[4];
	DEX_GetObjContainer(lONF,Cont);


	{

	CTable t (*pGewAlle);

//	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

		
	for ( t.First(); t.Valid(); t.Next()) {
			KP_GEWLock l(t);

			lCount ++;

			if ( !l)
				continue;

			long lONr = l->Objekt();

			if (lONr == -1L || lONr == 0L)
				continue;

			if ( m_pStatus)
				m_pStatus->SetValue( lCount, lONr);


			if ( DEX_GetObjectType(lONr) != OGLinie)
				continue;

			if ( l->Ende() <= 0L)
				continue;

			if ( !ContainerVergleich ( lONr, Cont))
				continue;

			Relat Rel;
			if ( !GewaesserRelation ( lONF,lONr, &Rel))
				continue;
			if ( Rel != REL_INN && Rel != REL_INAUS)
				continue;

			{
			CTable f (*pGew);

			LadeGewaesserKataster ( l->GewNr(),l->GewName(),pGew);

			if ( f.Find (l->GewNr())) {
				KP_GEWLock g(f);
				g->StoreBeginnKompakt ( l->BeginnKompakt());
				g->StoreEndeKompakt ( l->EndeKompakt());
				g->SpeichereObjektLaenge ( l->Ende());
				g->SpeichereObjekt(l->Objekt());
				g->StoreCount( l->Count());
		

				if ( Rel == REL_INAUS) {

		// Hier pModObj füllen
					TR_OBJTree *pTObj = NULL;
					pTObj = GewaesserVerschnitt(lONF,lONr);
					if ( pTObj) {
						g->SetOBJ ( pTObj);

						char Buff[20];
						{
						CTable e ( *pTObj);
						for ( e.First(); e.Valid(); e.Next()){
							TR_OBJLock n(e);
							if (!n)
								continue;
							long lNewONr = n->Object();
							long lStart = LinienStartPunkt(lONr,n->Object());
							long lEnde = LinienLaenge(lNewONr);
							n->SetIntervall(lStart,lStart+lEnde);
							ModifiziereMerkmal ( lNewONr,m_pKH->CodeBauwAnfStat(), ltoa(lStart,Buff,10));
							ModifiziereMerkmal ( lNewONr,m_pKH->CodeBauwEndStat(), ltoa(lStart+lEnde,Buff,10));
						}
						}
	
					}
				}
			}
			}

	}

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return pGew;
}
//////////////////////////////////////////////////////////////////
bool CKompiasExtension :: ContainerVergleich ( long lONr, long Cont[])
{
	return true;
	/*__________________
	if ( lONr <= 0L)
		return false;

	long NCont[4];
	DEX_GetObjContainer(lONr,NCont);

	if ( NCont[0] >= Cont[0] &&
		NCont[0] <= Cont[1] &&
		NCont[2] >= Cont[2] &&
		NCont[2] <= Cont[3] )
		return true;
 
	if ( NCont[0] >= Cont[0] &&
		NCont[0] <= Cont[1] &&
		NCont[3] <= Cont[3] &&
		NCont[3] >= Cont[2] )
		return true;
 
	if ( NCont[1] >= Cont[0] &&
		NCont[1] <= Cont[1] &&
		NCont[2] >= Cont[2] &&
		NCont[2] <= Cont[3] )
		return true;
 
	if ( NCont[1] >= Cont[0] &&
		NCont[1] <= Cont[1] &&
		NCont[3] <= Cont[3] &&
		NCont[3] >= Cont[2] )
		return true;
	
	if ( Cont[0] >= NCont[0] &&
		Cont[1] <= NCont[1] &&
		Cont[2] >= NCont[2] &&
		Cont[3] <= NCont[3])
		return true;
	return false;
	----------------------------------*/
}
//////////////////////////////////////////////////////////////////
bool CKompiasExtension :: GewaesserRelation ( long lONF, long lONr, Relat *pRel)
{
	if ( !m_pTop) 
		return false;

	Relat Rel;
	HRESULT hr = m_pTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
	if (FAILED(hr)) {
		return false;
	}

	*pRel = Rel;
	return true;

}

//////////////////////////////////////////////////////////////////
TR_OBJTree *CKompiasExtension :: GewaesserVerschnitt( long lONF,long lONr) 
{
	if ( !m_pObjOp)
		return NULL;

	IEnumLONG * pIEnum = NULL;

	try {

		WEnumObjectsByNumber wIEnumObj (CLSID_EnumObjectsByNumber);

		wIEnumObj -> AddItem(lONr);

		DWORD Lage = LINN | LKONT;

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

		HRESULT hr = m_pObjOp->SectionObjObjs_ONr (lONF,WEnumLONG(wIEnumObj),Lage,SFORM_PERM,&pIEnum);
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

		if ( FAILED(hr))
			_com_issue_error(hr);

	} catch (_com_error&){
		return NULL;
	}


	ULONG ulCount = pIEnum->Count();

	if ( 0L >= ulCount) {
		pIEnum->Release();
		return NULL; 
	}


	ulong lMCode = GetClonedCode(lONr);
	if ( 0L == lMCode ) {
		pIEnum->Release();
		return NULL;
	}

	TR_OBJTree *pTOBJ = new TR_OBJTree;

	if ( !pTOBJ ) {
		pIEnum->Release();
		return NULL;
	}

	long lCount = 0L;
	long *pObj = new long [ulCount + 1];

	if ( !pObj ) {
		DELETE_OBJ ( pTOBJ);
		pIEnum->Release();
		return NULL;
	}

	{
	CTable tt ( *pTOBJ);
	long ONr;
	for ( pIEnum->Reset(); S_OK == pIEnum->Next(1,&ONr,NULL); /**/)
	{

		// Objekt auf GI Testen !!
		short Status = DEX_GetObjectType (ONr);

	//--------------Zuordnung----------------------------
		if ( Status == OGLinie ) {
			lCount++;
			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			
			SetObjektCloned ( ONr, lMCode);

			if ( !tt.Find ( &ONr) ) {
				TR_OBJCreator OCr ( *pTOBJ);
				ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
				*(pObj+lCount) = ONr;
				*pObj = lCount;
			}

		} else {
			MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//			MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			DEX_DeleteObject(ONr);
//			MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		}
	}
	}

	CTreeLaden(pObj);

	DELETE_OBJ ( pObj);

	pIEnum->Release();
	return pTOBJ;
}
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für Cloned in definieren/holen
//-------------------------------------------------------------------
ulong CKompiasExtension :: GetClonedCode (long lONr)
{
	ulong lMCode = 0L;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		return lMCode;
	}

	*pCode = '\0';

	strcat( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),90));

#if _MSC_VER < 1100
	lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#else
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	HPROJECT hPr = DEX_GetObjectProject(lONr);
	lMCode = DEX_GetMCodeFromFeatureNameEx (hPr ,pCode );
#endif

	DELETE_OBJ ( pCode);

	if ( 0L == lMCode ) {

#if _MSC_VER < 1100
		lMCode = DEX_GetUniqueSysMCode ();
#else
//		lMCode = DEX_GetUniqueSysMCodeEx (hPr);
		lMCode = DEX_GetUniqueSysMCode ();
#endif

		if ( 0L == lMCode ) {
			return lMCode;
		}

		if ( !SetPBDClonedMCode( lMCode,lONr)) {
			lMCode = 0L;
			return lMCode;
		}

	}

	return lMCode;

}
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für Cloned in PBD setzen
//-------------------------------------------------------------------
bool CKompiasExtension :: SetPBDClonedMCode ( ulong MCode,long lONr)
{

char KText[32+1];

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
	strncpy ( KText,  ResString (ResID(IDS_OBJEKTSYSCODE,&g_pTE->RF()),40) , sizeof(KText)-1);
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;

	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär



#if _MSC_VER >= 1100

	long lIdent = DEX_GetObjIdent(lONr);
	pbdData.lIdent = lIdent;


	DefineFeatureSet ( &pbdData);

/*-----------------------------------
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

// Test, ob OE bereits definiert
	long lRefCode = DEX_GetMCodeFromFeatureNameEx(hPr,KText);
	if (lRefCode != 0L && lRefCode != MCode)
		ModifyObjFeature(lRefCode,lIdent,&KText[0]);

	{
	ErrInstall EI (WC_NOMERKMAL);
		if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
			return false;
		else
			DEXN_PBDMCodeChanged (MCode);
	}
		
--------------------------*/

	return true;

#else

	{
	ErrInstall EI (WC_NOMERKMAL);
		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return false;
		else
			DEXN_PBDMCodeChanged (MCode);
	}
	return true;

#endif

}
#if _MSC_VER >= 1100
//------------------------------------------------------------------------
void CKompiasExtension :: ModifyObjFeature(long lMCode, long lIdent, char *pText)
{

	if (!pText || *pText == '\0')
		return;

	if (lMCode == 0L)
		return;

	char KText[32+1];

	strncpy (KText,pText,sizeof(KText)-1);
	char *ptr = strchr(KText,'\0');
	int len = strlen(KText);
	if ( len - 3 <= sizeof(KText)-1 -1 ) {
		strcat (KText,"(2)");
	} else {
		ptr = ptr - 3;
		*ptr = '\0';
		strcat (KText,"(2)");
	}

	PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;

	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär

	pbdData.lIdent = lIdent;

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}

	return;
}
#endif
//------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für Objekte setzen
//-------------------------------------------------------------------
void CKompiasExtension :: SetObjektCloned ( long lONr, ulong MCode)
{
	char * pMText = new char [_MAX_PATH];
	if ( !pMText)
		return;
	wsprintf( pMText, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),90));

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)MCode;		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );

	DELETE_OBJ ( pMText);
	return;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
void CKompiasExtension :: SetOriginalObjekt ( TR_OBJTree *pModi, KPTree *pGew, long lMCode)
{
	if ( !pGew || !pModi)
		return;
	if ( pGew->Count() == 0 || pModi->Count() == 0)
		return;

	if ( lMCode == 0L)
		return;

	CEierUhr Wait (MVWind());

	CTable e (*pModi);
	for (e.First(); e.Valid(); e.Next() ) {
		TR_OBJLock n(e);
		long ONr = n->Object();

		char *pGewNr = HoleGewaesserNummer ( ONr, lMCode);
		if (!pGewNr || *pGewNr == '\0')
			continue;

		long lLLen = 0L;
		lLLen = LinienLaenge(ONr);
		n->StoreObjLaenge ( lLLen );

		CTable f (*pGew);
		if ( f.Find (pGewNr)) {
			KP_GEWLock g(f);
			g->SpeichereObjekt(n->Object());

	// Auf zu Malte !!!
			long lLaenge = 0L;
			long lEta = 0L;
			long lLen = 0L;
			lLaenge = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLen, lEta);
			if ( lLaenge > 0L ) 
				g->SetKompaktLen ( lLaenge );

			g->SpeichereObjektLaenge ( lLLen );
		// ------ Kilometrierungen definieren --------

			TR_OBJTree *pTObj = g->GetOBJ();
			if ( !pTObj) 
				continue;
			char Buff[20];
			CTable t (*pTObj);
			for ( t.First(); t.Valid(); t.Next()){
				TR_OBJLock l(t);
				if (!l)
					continue;
				long lNewONr = l->Object();
				long lStart = LinienStartPunkt(ONr,l->Object());
				long lEnde = LinienLaenge(l->Object());
				l->SetIntervall(lStart,lStart+lEnde);
				ModifiziereMerkmal ( lNewONr,m_pKH->CodeBauwAnfStat(), ltoa(lStart,Buff,10));
				ModifiziereMerkmal ( lNewONr,m_pKH->CodeBauwEndStat(), ltoa(lStart+lEnde,Buff,10));

			}
		}

		DELETE_OBJ ( pGewNr);
	}
	return;
}
///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void CKompiasExtension :: Loeschen ( long *pObj)
{
	if ( !pObj)
		return;

	if ( 0L >= *pObj) {
		return;
	}

	long lDim = *pObj;
	for ( long i = 0L ; i < lDim; i++ ) {
		long lONr = *(pObj + i + 1);
		short Status = DEX_GetObjectStatus ( lONr );
		if ( Status != -1 && Status != OSNormal && Status != OSModified ) 
			continue;
		if ( 0L < lONr ) 
			DEX_DeleteObject ( lONr);
	}

	return;
}
///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void CKompiasExtension :: CTreeLoeschen ( TR_OBJTree *pObj)
{
	if ( !pObj)
		return;

	if ( pObj->Count() == 0L) {
		return;
	}

	CTable t (*pObj);

	UnRegisterNotification (DEX_DELOBJECT);
	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	for (t.First();t.Valid();t.Next()) {
		TR_OBJLock l(t);
		if (!l)
			continue;
		long lONr = l->Object();
		if ( 0L < lONr ) {
			DEX_DeleteObject ( lONr);
		}
	}

	RegisterNotification (DEX_DELOBJECT);
	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	return;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void CKompiasExtension :: CTextLoeschen ( void)
{
	if ( !m_pGewText)
		return;

	if ( m_pGewText->Count() == 0L) {
		DELETE_OBJ ( m_pGewText);
		return;
	}
//	DeleteAllTextObjects();
	DELETE_OBJ ( m_pGewText);

	return;
}
////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void CKompiasExtension :: CTextLaden ( long lONr, long lStart, long lEnde)
{

	if ( !m_pGewText) {
		m_pGewText = new TS_OBJTree;
		if ( !m_pGewText) 
			return;
	}

	CTable t (*m_pGewText);

	if ( !t.Find ( &lONr) ) {
		TS_OBJCreator OCr ( *m_pGewText);
		ContCreate ( OCr, TS_OBJ ) (lONr,lStart,lEnde);
	} else {
		TS_OBJLock l(t);
		l->SetTextInformation(lStart,lEnde);
	}
	return;
}
///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
/*----------------
void CKompiasExtension :: DeleteAllTextObjects ( void)
{


	if ( !m_pGewText)
		return;

	CTable t (*m_pGewText);
	UnRegisterNotification (DEX_DELOBJECT);
	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	for (t.First();t.Valid();t.Next()) {
		TS_OBJLock l(t);
		if (!l)
			continue;
		long lONr = l->Start();
		if ( 0L < lONr ) {
			DEX_DeleteObject ( lONr);
		}
		lONr = l->Ende();
		if ( 0L < lONr ) {
			DEX_DeleteObject ( lONr);
		}
	}

	RegisterNotification (DEX_DELOBJECT);
	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	return;
}
------------------------*/
///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void CKompiasExtension :: CTreeLaden ( long *pObj)
{
	if ( !pObj)
		return;
	if ( !m_pModObj)
		m_pModObj = new TR_OBJTree;
	if (!m_pModObj)
		return;

	CTable ct (*m_pModObj);
	long lDim = *pObj;
	for ( long i = 0L ; i < lDim; i++ ) {
		long lONr = *(pObj + i + 1);
		if ( lONr == -1L || lONr == 0L)
			continue;
		
		if ( !ct.Find ( &lONr) ) {
			TR_OBJCreator OCr ( *m_pModObj);
			ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
		}

	}

	return;
}
//////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: GewaesserInWindow ( HWND hWnd)
{
	long Count = 0L;

	TR_OBJTree * pOBJ = new TR_OBJTree;
	if ( !pOBJ )
		return Count;

	CEierUhr Wait (MVWind());

	DEXOR_SelectedObjectsCount ( hWnd , &Count);

	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie;

	ENUMLONGKEY ENL;
	ENL.eFcn = ( ENUMLONGKEYPROC ) SucheGewaesserObjekt;
	ENL.eKey = (long ) (void *)hWnd;
	OT.pOBJ = pOBJ;
	ENL.ePtr = &OT;
//	ENL.ePtr = pOBJ;
	DEX_EnumSelectedObjects (ENL);

	Count = 0L;
//------------Bearbeiten
	{

	CTable e (*pOBJ);
	for (e.First(); e.Valid(); e.Next() ) {
		TR_OBJLock n(e);
		long ONr = n->Object();
		if ( !ObjektIstGewaesser(ONr))
			continue;
		char *pGewNr = HoleGewaesserNummer ( ONr, m_pKH->CodeGewNr());
		if (!pGewNr || *pGewNr == '\0')
			continue;

		char *pGewName = HoleGewaesserName ( ONr, m_pKH->CodeGewName(), pGewNr,true);	// Mit Malte
		if (!pGewName) {
			DELETE_OBJ ( pGewNr);
			continue;
		}

		long lLLen = 0L;
		lLLen = LinienLaenge(ONr);

		if ( lLLen > 0L) {
			long lEta = 0L;
			long lLen = 0L;
			long lLaenge = 0L;
			Count++;
			// TRiAS -Laenge in KompaktKataster
			lLen = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLaenge, lEta);
			if (lLen > 0L) {	// L da, damit Objekt da - sonst GP

				char *pMalte = m_hLib->GewaesserNameHolen ( pGewNr);
				if ( pMalte && *pMalte != '\0') {
					strcpy (pGewName,pMalte);
					SetObjektWert( ONr, m_pKH->CodeGewName(), pGewName);
				}
			} else {
//--------------------> GewNr existiert in KompaktKataster nicht- anlegen !
				if ( lLen != cGewaesserNummerFalsch ) {
					lLaenge = lLLen;
					m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewName, lLaenge);
//					if ( !m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewName, lLaenge))
//						Count--;
				}
			}
		}
		DELETE_OBJ ( pGewNr);
		DELETE_OBJ ( pGewName);
	}

	}

	DELETE_OBJ ( pOBJ);

	return Count;

}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: GewaesserInWindowZuKataster ( HWND hWnd)
{
// TRiAS - Objekte korrigieren Kompaktkataster 
	long Count = 0L;

	TR_OBJTree * pOBJ = new TR_OBJTree;
	if ( !pOBJ )
		return Count;

	CEierUhr Wait (MVWind());

	DEXOR_SelectedObjectsCount ( hWnd , &Count);
	long lCount = Count;

	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie;

	ENUMLONGKEY ENL;
	ENL.eFcn = ( ENUMLONGKEYPROC ) SucheGewaesserObjekt;
	ENL.eKey = (long ) (void *)hWnd;
	OT.pOBJ = pOBJ;
	ENL.ePtr = &OT;
	DEX_EnumSelectedObjects (ENL);

	Count = 0L;

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

//------------Bearbeiten
	{

	CTable e (*pOBJ);
	for (e.First(); e.Valid(); e.Next() ) {
		TR_OBJLock n(e);
		long ONr = n->Object();
		if ( !ObjektIstGewaesser(ONr))
			continue;
		char *pGewNr = HoleGewaesserNummer ( ONr, m_pKH->CodeGewNr());			
		if (!pGewNr)
			continue;

		char *pGewName = HoleGewaesserName ( ONr, m_pKH->CodeGewName(),pGewNr,true);	// Mit Malte
		if (!pGewName) {
			DELETE_OBJ ( pGewNr);
			continue;
		}

		long lLLen = 0L;
		lLLen = LinienLaenge(ONr);

		if ( lLLen > 0L) {
			long lEta = 0L;
			long lLen = 0L;
			long lLaenge = 0L;
			Count++;
			// TRiAS -Laenge in KompaktKataster
			lLen = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLaenge, lEta);
			if (lLen > 0L) {	// L da, damit Objekt da - sonst GP

// Nur bei einem Gewässer----------------------------------
				if ( lCount == 1 ) {
						char *pBuffer = new char [_MAX_PATH];
						*pBuffer = '\0';
						wsprintf (pBuffer,ResString (ResID(IDS_ABGLEICHTEXT, &RF()),90),lLLen,lLen);
					int flag = MessageBox (__hWndM,
						 pBuffer,
						 ResString (ResID(IDS_ABGLEICHKATASTER, &RF()),50),
						 MB_YESNO|MB_ICONEXCLAMATION);
					DELETE_OBJ (pBuffer);

					if ( flag == IDNO ) {
							DELETE_OBJ (pGewNr);
							DELETE_OBJ ( pGewName);
							return 0;
					}


				}
//------------------------------------------------------------

				lLaenge = lLLen;

//				lLen = m_hLib->GewaesserNeueLaenge ( pGewNr, lLaenge);

				char *pMalte = m_hLib->GewaesserNameHolen ( pGewNr);
				if ( pMalte && *pMalte != '\0') {
					strcpy (pGewName,pMalte);
					SetObjektWert( ONr, m_pKH->CodeGewName(), pGewName);
				}
			} else {
//--------------------> GewNr existiert in KompaktKataster nicht- anlegen !
				lLaenge = lLLen;
				m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewName, lLaenge);
			}
			if ( m_pGewAlle)
//				AktualisiereGesamtGewaesser(ONr, pGewNr,lLLen);
				KorrigiereGesamtGewaesser(true,ONr, pGewNr,lLLen);
			else
				KorrigiereEinzelGewaesser (true, ONr, pGewNr, lLLen);
		}
		DELETE_OBJ ( pGewNr);
		DELETE_OBJ ( pGewName);
	}

	}

	DELETE_OBJ ( pOBJ);

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	return Count;

}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: ModGewaesserInWindow ( HWND hWnd)
{
// TRiAS - Objekte werden nach Kompaktkataster ausgerichtet
	long Count = 0L;

	TR_OBJTree * pOBJ = new TR_OBJTree;
	if ( !pOBJ )
		return Count;

	CEierUhr Wait (MVWind());

	DEXOR_SelectedObjectsCount ( hWnd , &Count);
	long lCount = Count;

	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie;

	ENUMLONGKEY ENL;
	ENL.eFcn = ( ENUMLONGKEYPROC ) SucheGewaesserObjekt;
	ENL.eKey = (long ) (void *)hWnd;
	OT.pOBJ = pOBJ;
	ENL.ePtr = &OT;
	DEX_EnumSelectedObjects (ENL);

	Count = 0L;
//------------Bearbeiten

	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	{

	CTable e (*pOBJ);
	for (e.First(); e.Valid(); e.Next() ) {
		TR_OBJLock n(e);
		long ONr = n->Object();
		if ( !ObjektIstGewaesser(ONr))
			continue;
		char *pGewNr = HoleGewaesserNummer ( ONr, m_pKH->CodeGewNr());
		if (!pGewNr)
			continue;

		char *pGewName = HoleGewaesserName ( ONr, m_pKH->CodeGewName(),pGewNr,true);	// Mit Malte
		if (!pGewName) {
			DELETE_OBJ ( pGewNr);
			continue;
		}

		long lTRiASLen = 0L;
		lTRiASLen = LinienLaenge(ONr);

		if ( lTRiASLen > 0L) {
			long lEta = 0L;
			long lKPLen = 0L;
			long lLaenge = 0L;
			Count++;

			lKPLen = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLaenge, lEta);	

			if (lKPLen > 0L) {	// L da, damit Objekt da - sonst GP

// Nur bei einem Gewässer----------------------------------
				if ( lCount == 1 ) {
						char *pBuffer = new char [_MAX_PATH];
						*pBuffer = '\0';
						wsprintf (pBuffer,ResString (ResID(IDS_ABGLEICHTEXT, &RF()),90),lTRiASLen,lKPLen);
					int flag = MessageBox (__hWndM,
						 pBuffer,
						 ResString (ResID(IDS_ABGLEICHGRAPHIK, &RF()),50),
						 MB_YESNO|MB_ICONEXCLAMATION);
					DELETE_OBJ (pBuffer);

					if ( flag == IDNO ) {
							DELETE_OBJ (pGewNr);
							DELETE_OBJ ( pGewName);
							return 0;
					}


				}
//------------------------------------------------------------


				long lMyLen = 0L;

				if ( lKPLen < lTRiASLen ) {
					GewaesserKuerzen ( ONr, lKPLen);
					lMyLen = lKPLen;
				} else {
					GewaesserVerlaengern ( ONr, lKPLen - lTRiASLen);
					lMyLen = lTRiASLen;
				}

				if ( m_pGewAlle )
//					AktualisiereGesamtGewaesser(ONr,pGewNr,lMyLen);
					KorrigiereGesamtGewaesser(false,ONr, pGewNr,lMyLen);
				else
					KorrigiereEinzelGewaesser(false,ONr,pGewNr,lMyLen);
			}
		}
		DELETE_OBJ ( pGewNr);
		DELETE_OBJ ( pGewName);
	}

	}

	DELETE_OBJ ( pOBJ);

	return Count;

}
///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: KorrigiereGesamtGewaesser ( bool iFlag,long lONr, char *pGewNr, long lLen)
{
//	Neu 10.02.98
//	iFlag = true -> Kompaktkataster wird korrigiert
//	iFlag = false -> TRiASObjekt wird korrigiert

	if ( lONr == -1L || lONr == 0L)
		return;
	if ( !pGewNr || *pGewNr == '\0')
		return;
	if ( !m_pGewAlle)
		return;
	CTable t(*m_pGewAlle);

	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = pGewNr;
	GW.pcGewaesserName = NULL;
	GW.lBeginn = 0L;
	GW.lEnde = lLen;

	if ( !t.Find ( pGewNr)){

		KP_GEWCreator KPCr ( *m_pGewAlle);
		ContCreate (KPCr,KP_GEW) (&GW, NULL);

	} else {
		KP_GEWLock l(t);
		l->SpeichereObjekt(lONr);

		if (iFlag) {
		// Korrigieren Kompaktkataster
			GW.lBeginn = l->Beginn();
			GW.lEnde = l->Ende();
			m_hLib->GewaesserStrukturSetzen(&GW);
			l->TRiASKompaktAbgleich();
		} else {

			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

//	AnfangsStation anlegen
			long lBeginn = l->BeginnKompakt();
			if (lBeginn != 0L) {
				char *pText = new char[20];
				if (pText) {
					wsprintf(pText,"%ld",lBeginn);
					ModifiziereMerkmal(lONr,m_pKH->CodeBauwAnfStat(),pText);
					DELETE_OBJ (pText);
				}
			} else {
				LoescheMerkmal(lONr,m_pKH->CodeBauwAnfStat());
			}

			l->KompaktTRiASAbgleich();				
		}
		
	}
}
//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: KorrigiereEinzelGewaesser ( bool iFlag,long lONr, char *pGewNr, long lLen)
{
//	Neu 10.02.98
//	iFlag = true -> Kompaktkataster wird korrigiert
//	iFlag = false -> TRiASObjekt wird korrigiert

	if ( lONr == -1L || lONr == 0L)
		return;
	if ( !pGewNr || *pGewNr == '\0')
		return;

	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = pGewNr;
	GW.pcGewaesserName = NULL;
	GW.lBeginn = 0L;
	GW.lEnde = lLen;


	if (iFlag) {
		// Korrigieren Kompaktkataster
		long lMBeginn = ObjektStartPunkt(lONr,m_pKH->CodeBauwAnfStat());
		long lMEnde = LinienLaenge(lONr);

		GW.lBeginn = lMBeginn;
		GW.lEnde = lMEnde+lMBeginn;
		m_hLib->GewaesserStrukturSetzen(&GW);
	} else {

		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

//	AnfangsStation anlegen
		m_hLib->GewaesserStrukturHolen(&GW);
		long lBeginn = GW.lBeginn;
		if (lBeginn != 0L) {
			char *pText = new char[20];
			if (pText) {
				wsprintf(pText,"%ld",lBeginn);
				ModifiziereMerkmal(lONr,m_pKH->CodeBauwAnfStat(),pText);
				DELETE_OBJ (pText);
			}
		} else {
			LoescheMerkmal(lONr,m_pKH->CodeBauwAnfStat());
		}

	}
}
//--------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: LoeschenKompaktKlassen ( void)
{
	if (!m_isActive)
		return;

//	Alle KompaktKlassen formal durchzählen
	ENUMNOKEYLONG ENT;
//	Bestimmen der Anzahl der Objektklassen
	ENT.eFcn = ( ENUMTEXTKEYPROC) DeleteKompaktClass;
	ENT.ePtr = NULL;
	DEX_EnumIdents(ENT);
	return;
}
///////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: SucheDifferenzGewaesser ( KPTree *pGew)
{
	if ( !pGew || pGew->Count() == 0)
		return false;

	KPTree *pGewN = new KPTree;
	if ( !pGewN)
		return false;

	{

	CTable t (*pGew);

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);

		if (!l->Objekt()) {	// NurKataster
			SichereGewaesser ( pGewN, l->GewNr());
			continue;
		}

		if (!l->EndeKompakt()) {	// Nur TRiAS
			SichereGewaesser ( pGewN, l->GewNr());
			continue;
		}

		if ( l->Ende() == l->EndeKompakt()) {
			SichereGewaesser ( pGewN, l->GewNr());
			continue;
		}

		if ( l->Ende() != l->EndeKompakt()) {
		// KK010726
			long lDiff = abs (l->Ende() - l->EndeKompakt());
			long lGewLen = l->Ende();
			if ( lGewLen < l->EndeKompakt())
				lGewLen = l->EndeKompakt();

//			if ( lDiff <= m_pKH->GewDiffLaenge()) {

			if ( !GewaesserDiffLaenge(lDiff,lGewLen)) {
				SichereGewaesser ( pGewN, l->GewNr());
			}
		}

	}
	}

	if ( pGewN->Count() == 0) {
		DELETE_OBJ ( pGewN);
		return true;
	}

	{
	CTable d (*pGewN);
	for ( d.First(); d.Valid(); d.Next()) {
		KP_GEWLock m(d);
		LoescheGewaesser ( pGew, m->GewNr());
	}
	}

	DELETE_OBJ (pGewN);
	pGew->Optimize();

	if ( pGew->Count() == 0)
		return false;

	return true;
}
///////////////KK010726////////////////////////////////////////////////////
bool CKompiasExtension :: GewaesserDiffLaenge(long lDiff, long lMax)
{
	if ( m_pKH->GewDiffProzent()) {		// Prozentangabe
		long lDiffM = lMax * m_pKH->GewDiffLaenge()/100;
		return ( lDiff > lDiffM);
	} else {
		return ( lDiff > m_pKH->GewDiffLaenge());
	}
}

///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: DiffLaengenText(char * pText,short iLen)
{
	*pText = '\0';
	
	if ( m_pKH->GewDiffProzent()) {		// Prozentangabe
		wsprintf(pText,"%d Prozent",m_pKH->GewDiffLaenge());
	} else {
		wsprintf(pText,"%d Meter",m_pKH->GewDiffLaenge());
	}
	return;
}

///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: SichereGewaesser ( KPTree *pGewN, char *pGewNr)
{
	if ( !pGewN )
		return;

	CTable t(*pGewN);

	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = pGewNr;

	if (!t.Find(pGewNr)){
		KP_GEWCreator KPCr ( *pGewN);
		ContCreate (KPCr,KP_GEW) (&GW, NULL);
	}
	return;
}
///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: LoescheGewaesser ( KPTree *pGew, char *pGewNr)
{

	if ( !pGew || pGew->Count() == 0)
		return;
	if ( !pGewNr || *pGewNr == '\0')
		return;

	CTable t(*pGew);

	if (t.Find(pGewNr)){
		t.Delete();
	}
	pGew->Optimize();

	return;
}
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////////////////// EXTERN C //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheObjekte ( long lONr, Bool , void *pData)
{
	CTop_ObjTree *pObj = (CTop_ObjTree *)pData;

	short iStatus = DEX_GetObjectType (lONr);
	
	CTable t(*pObj);
	if ( !t.Find ( &lONr) ) {
		CTop_ObjCreator OCr ( *pObj);
		ContCreate ( OCr, CTop_Obj ) (lONr,iStatus);
	}
	return TRUE;

}
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheFlaechenObjekte ( long lONr, Bool , void *pData)
{
	CTop_ObjTree *pObj = (CTop_ObjTree *)pData;

	short iStatus = DEX_GetObjectType (lONr);
	if ( OGFlaeche != iStatus)
		return TRUE;

	CTable t(*pObj);
	if ( !t.Find ( &lONr) ) {
		CTop_ObjCreator OCr ( *pObj);
		ContCreate ( OCr, CTop_Obj ) (lONr,iStatus);
	}
	return TRUE;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-----------File COBJKOMP.CXX
