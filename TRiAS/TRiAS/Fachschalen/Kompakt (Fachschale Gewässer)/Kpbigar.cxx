//-----------KOMPAKT-MEMBER : GroﬂFl‰chenAnalyse----------
// File: KPBIGAR.CXX


#include "kompp.hxx"

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
#include "version.h"
#include "kompias.h"
#include "about.h"

#include "about.hxx"
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
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------------
//Member
void CKompiasExtension :: GrossFlaechenAnalyse ( long lONr, HWND hWnd)
{
	if ( 0L >= lONr )
		return;
/*----------------------------------
// Basic hilf mir
	_DGeoObject *pIObj = NULL;
	if ( GetGeoObjectFromONr (lONr,&pIObj)) {

		ebPARAM PA[2];

		PA[0].wType = 0;
		PA[0].szExtType[0] = '\0';

		PA[1].wType = TYP_APPOBJECT;
		strcpy (PA[1].szExtType, "GeoObject");

		LPVOID pTyp = NULL;

		LPVOID pVals[2] = { NULL, &pIObj };

		BSPARAM BS;
		BS.pTypes = PA;
		BS.pValues = pVals;

		if ( m_pScript) 
			m_pScript->RunCode(g_hInstance,IDR_SCRIPTTOPO,"TOPOLOG",1,&BS);

		pIObj->Release();

	}

--------*/

// Klassen ausw‰hlen
	long lMyObj = lONr;
	while ( lMyObj != -1L ) {
		lMyObj = ObjektKompaktAnalyse(lMyObj,hWnd);
	}
	return;
}
//----------------------------------------------------------------------
long CKompiasExtension :: ObjektKompaktAnalyse ( long lONr, HWND hWnd)
{

	long *plONR = NULL;
	long lIdent = DEX_GetObjIdent(lONr);
	TR_IDMTree * pIDM;

	{
	AlleTRiASKlassen TF ( ORWind(hWnd),TRIASCLSAUSWAHL, RF(), lIdent);
	TF.Show(Centre);  
	if (TF.Result() == 1) {
		plONR = TF.TRiASCls();
		pIDM = TRiASKlassen (lONr,plONR,hWnd);
	} else
		return -1L;
	}

// RechercheErgebnis anzeigen
	long lMyObj;
	{
	TRiASRechercheKlassen TR ( ORWind(hWnd),IDD_FLAECHENSTATISTIK, RF(), lONr,pIDM);
	TR.Show(Centre);  
	if ( TR.Result() == 1) {
		long *pObj = TR.Obj();
		if ( pObj && *pObj > 0L) {
			short Flag = ROSortObjNr;
			CreateORWindow ( Flag, 80, 100, pObj, "Rechercheergebnis", 125, 128, 255);
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
TR_IDMTree *CKompiasExtension :: TRiASKlassen ( long lONF,long *lClassIdent, HWND hWnd) 
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
			TR_IDMCreator TRCr ( *pIDM);
			ContCreate ( TRCr, TR_IDM) ( lIdent, iGITyp);
		} else {
			TR_IDMLock l(t);
			l->SetTyp(iGITyp);
		}

	}

	TRIASKLASSE TK;
	TK.pIDM = pIDM;
	TK.lONF = lONF;
	TK.pTop = m_pTop;

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheTRiASObjekte;

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	m_pStatus = new CStatus ( ORWind(hWnd), &RF(),lDim, "Objektklassen");
	m_pStatus->Show();

	long lCount = 0L;

	for (t.First();t.Valid();t.Next()) {
		TR_IDMLock l(t);
		long lIdent = l->Ident();
		ELK.eKey = lIdent;
		ELK.ePtr = &TK;
		DEX_EnumIdentObjects(ELK);
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
