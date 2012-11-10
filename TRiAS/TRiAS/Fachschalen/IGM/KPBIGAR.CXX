//-----------KOMPAKT-MEMBER : GroﬂFl‰chenAnalyse----------
// File: KPBIGAR.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <shellapi.h>

#include <triashelper.h>
//#include <triashelper_i.c>

#include <oleguid.h>
#include <dirisole.h>
#include <eonrguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>
//#include <ienumonr.hxx>	// CEnumObjectsByNumber

#include <igeometr.hxx>

//#include <smartif.h>
#include "triasdec.h"
#include "triasdef.h"
#include "kompdef.h"
//#include <iterenum.h>

#include <trelguid.h>
#include <operguid.h>

#include "kpstatus.hxx"
#include "kompdll.hxx" 
#include "komphead.hxx"
#include "gewbaum.hxx"

#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompcls.hxx"
#include <Esnecil.h>

#include "vobjprop.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32


// --------------------------------------------------------------------------------------------
// benˆtigte SmartInterfaces
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber
DefineSmartInterface(EnumLONG);	// WEnumLONG

//------------------------------------------------------------

//------------------------------------------------------------------
//Member
void CKompiasExtension :: GrossFlaechenAnalyse ( long lONr, HWND hWnd)
{
	if ( 0L >= lONr )
		return;
	// lONr ist Fl‰che

// Objekte im Container/ Fl‰che lONr sammeln

	if ( !m_pTop) 
		LadeTopRel();

	long *pCont = ObjectContainer ( lONr, OT_FLAECHE);

	TR_OCLTree *pObj = new TR_OCLTree;

	if ( !pObj)
		return;

	TOPOLOGIETYP ET;
	ET.pOutClass = pObj;
	ET.lONF = lONr;
	ET.pTop = m_pTop;
	
	ENUMRECHGEOMETRIE ERGI;
	memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
	ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
	ERGI.lCont = pCont;
	ERGI.iMode = ERGActSight;
//	Objekte z‰hlen
	ERGI.eFcn = (RECHGEOMETRIEPROC) EnumTRiASObjekte;
	ERGI.pData = &ET;
	DEX_EnumRechGeometrie( ERGI );

	DELETE_OBJ ( pCont);

	if ( pObj->Count() == 0) {
		DELETE_OBJ ( pObj);
		return;
	}

	IGMAnlagenFilter ( pObj);	// Nur Gew‰sser + Bauwerke

	ObjektKompaktAnalyse (lONr,hWnd,pObj);	// Listenauswahl

	return;
}
//----------------------------------------------------------------------
void CKompiasExtension :: IGMAnlagenFilter ( TR_OCLTree *pObj)
{
	if ( !pObj)
		return;

	CTable t (*pObj);

	for ( t.First(); t.Valid(); t.Next()){

		TR_OCLLock l(t);
		if (!l)
			continue;

		long lIdent = l->Ident();

		if (!BauwerksIdentifikator (lIdent) && !GewaesserIdentifikator (lIdent)) {
				l-> StoreDefinition ( false );
		}
		
	}

}

//----------------------------------------------------------------------

long CKompiasExtension :: ObjektKompaktAnalyse ( long lONr, HWND hWnd, TR_OCLTree *pObj)
{

	long *plONR = NULL;
	long lIdent = DEX_GetObjIdent(lONr);
	TR_IDMTree * pIDM;

	{
	AlleTRiASKlassen TF ( ORWind(hWnd),TRIASCLSAUSWAHL, RF(), lONr, pObj);
	TF.Show(Centre);  
	if (TF.Result() == 1) {
		plONR = TF.TRiASCls();
		pIDM = TRiASKlassen (pObj,lONr,plONR,hWnd);
	} else
		return -1L;
	}

// RechercheErgebnis anzeigen
	long lMyObj;
	{
	TRiASRechercheKlassen TR ( ORWind(hWnd),IDD_FLAECHENSTATISTIK, RF(), lONr,pIDM);
	TR.Show(Centre);  
	if ( TR.Result() == 1) {
		long *pObj = TR.ObjIn();
		if ( pObj && *pObj > 0L) {
			short Flag = ROSortObjNr;
//			CreateORWindow ( Flag, 80, 100, pObj, "Rechercheergebnis", 125, 128, 255);
			CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_INNENOBJEKTE, &RF()),50).Addr(), 125, 128, 255);
		}

		long *pObj1 = TR.ObjIn();
		if ( pObj1 && *pObj1 > 0L) {
			short Flag = ROSortObjNr;
//			CreateORWindow ( Flag, 80, 100, pObj, "Rechercheergebnis", 125, 128, 255);
			CreateORWindow ( Flag, 80, 130, pObj1,ResString (ResID(IDS_INAUSOBJEKTE, &RF()),50).Addr(), 125, 128, 255);
		}
		return -1L;
	}

	if ( TR.Result() == -1) {
		lMyObj = TR.Objekt();
	}

	if ( TR.Result() == 0) 
		return -1L;
	}
	DELETE_OBJ (pIDM);
	return lMyObj;
}
////////////////////////////////////////////////////////////////////////
TR_IDMTree *CKompiasExtension :: TRiASKlassen ( TR_OCLTree *pObj, long lONF,long *lClassIdent, HWND hWnd) 
{

	if ( !lClassIdent || 0L == *lClassIdent )
		return NULL;

	long lDim = *lClassIdent;
	lDim = lDim/2L;

	TR_IDMTree *pIDM = new TR_IDMTree;
	if ( !pIDM)
		return NULL;

// Einfach nur Idents + Typ sammeln
	CTable t (*pIDM);
	for ( long i = 0L; i < lDim; i++ ) {
		long j = i*2;
		long lIdent = *(lClassIdent + j + 1);
		short iGITyp = (short)*(lClassIdent + j + 2);
		if ( !t.Find ( &lIdent)) {
			if ( BauwerksIdentifikator(lIdent) || GewaesserIdentifikator ( lIdent) ) {
				TR_IDMCreator TRCr ( *pIDM);
				ContCreate ( TRCr, TR_IDM) ( lIdent, iGITyp);
			}
		} else {
			TR_IDMLock l(t);
			l->SetTyp(iGITyp);
		}

	}

	TRIASKLASSE TK;
	TK.pIDM = pIDM;
	TK.lONF = lONF;
	TK.pTop = m_pTop;

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	m_pStatus = new CStatus ( ORWind(hWnd), &RF(),lDim,ResString (ResID(IDS_OBJEKTKLASSEN, &RF()),50).Addr());
	m_pStatus->Show();

	long lCount = 0L;

	for (t.First();t.Valid();t.Next()) {
		TR_IDMLock l(t);
		long lIdent = l->Ident();

		EnumIdentObjects(lIdent,pObj,&TK);
		lCount++;

		if ( m_pStatus) {
			m_pStatus->SetValue( lCount, lIdent);
		}

	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return pIDM;
}
//--------------------------------------------------------------------------
bool CKompiasExtension :: EnumIdentObjects ( long lIdent, TR_OCLTree * pObj , void *pTK) 
{
		bool iFlag = false;

		CTable t(*pObj);

		if ( !t.Find(&lIdent))
			return false;

		TR_OCLLock l(t);
		if (!l)
			return false;

		TR_OBJTree *pON = l->OBJ();

		if (pON->Count() > 0L) {

			CTable e(*pON);

			for (e.First();e.Valid();e.Next()) {
				TR_OBJLock f(e);
				long lONr = f->Object();

				SucheTRiASObjekte (lONr, iFlag ,( TRIASKLASSE *) pTK);
			}

		}
		return true;
}
//------------------------------------------------------------------------
bool CKompiasExtension :: FlaechenBlinkeln ( long lIdent, long *plONr , char *pString) 
{
	if ( !plONr || *plONr <= 0L || lIdent == 0L)
		return false;

	if ( !m_pScript)
		return false;
	if ( !m_pDoc)
		return false;

//-------Mit Hilfe von Basic ‹berschwemmungsgebiete zusammenfassen

#if _MSC_VER >= 1100
	HPROJECT hPro = DEX_GetObjectsProject(lIdent);

	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if ( hPr != hPro)
		return false;
#endif

	char *pName = new char [_MAX_PATH];
	char *pQuelle = new char [_MAX_PATH];
	if (!pName || !pQuelle ) {
		DELETE_OBJ(pName);
		DELETE_OBJ(pQuelle);
		return false;
	}

	*pName = '\0';
	*pQuelle = '\0';

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pName;
	pbdData.pbdKTextLen = _MAX_PATH -1;
	pbdData.pbdLTextLen = 0;

#if _MSC_VER < 1100
	DEX_GetPBDData (pbdData);
#else
	DEX_GetPBDDataEx (hPr,pbdData);

	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif


	ebPARAM PA[4];
	PA[0].wType = TYP_BOOLEAN;
	PA[0].szExtType[0] = '\0';

	// Gew‰ssernummer
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pString);

	//ObjektKlassenName
	PA[2].wType = TYP_STRING;
	strcpy ( PA[2].szExtType,pName);

	//DatenQuelle
	PA[3].wType = TYP_STRING;
	strcpy ( PA[3].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pVals[4] = {&iHKS,pString,pName,pQuelle};


	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pVals;

	m_pScript->RunCode(g_hInstance,IDR_SCRIPTBLINKEL,"UeberSchwemmung",3,&BS);

	DELETE_OBJ(pName);
	DELETE_OBJ(pQuelle);

	MERKMALSDEFINITION MD;
	memset (&MD,'\0',sizeof(MERKMALSDEFINITION) );
	MD.lNummer = m_pKH->CodeGewNr();
	MD.lCount = 0L;
	MD.lRefCount = 0L;
	MD.pStatus = NULL;
	
	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) DoppelnAttribut;
	ELK.eKey = lIdent;
	ELK.ePtr = &MD;

	DEX_EnumIdentObjects(ELK);

	
	return iHKS;

	}

//--------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//----------KPBIGAR.CXX
