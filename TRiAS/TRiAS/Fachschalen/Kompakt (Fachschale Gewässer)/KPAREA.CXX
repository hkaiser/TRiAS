//-----------KOMPAKT-MEMBER : Topologie Gewaesser <-> Flaechen----------
// File: KPAREA.CXX


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

#include "kompdef.h"
//#include <ienumonr.hxx>	// CEnumObjectsByNumber

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
// benötigte SmartInterfaces
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber
DefineSmartInterface(EnumLONG);	// WEnumLONG

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------------
//Member

//---------------------------------------------------------------------
void CKompiasExtension :: HoleFlaechenVonTRiAS ( LPSTR pGewaesserNr,short iTyp, KPBTree *pGEB )
{
	if ( !pGEB)
		return;

	if ( !pGewaesserNr || *pGewaesserNr == '\0')
		return;

	CEierUhr Wait (MVWind());

	long lONr = HoleEinzelGewaesser ( m_pKH->CodeGewNr(),pGewaesserNr);

	if ( lONr == 0L) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);

		return;
	}

	LadeObjektKlasse ( OTFlaeche, m_pKH->FlaClass());

	if (!LinienTest ( lONr, pGewaesserNr,pGEB, iTyp, m_pKH->FlaClass()))
		return;

	return;
}
//////////////////////////////////////////////////////////////////////

bool CKompiasExtension :: LinienTest ( long lONr , LPSTR pGewNr, KPBTree *pGEB,short iTyp, TR_OCLTree *pFla)
{
	bool iFlag = false;

//------------Versuch Topologie-Test------------------------
	if ( !pGEB || !pFla || lONr == 0L)
		return iFlag;

	CTable f(*pFla);

//-Zusammenstellen aller möglichen Flächen in pGEB--------
	Relat Rel;

	for ( f.First(); f.Valid(); f.Next()) {
		TR_OCLLock g(f);
		if (!g)
			continue;

		if (iTyp != cAlleFlaechen ) {
			if ( !KlassenTyp ( iTyp,g->Ident()))
				continue;
		}

		TR_OBJTree *pOBJ = g->OBJ();
		if ( !pOBJ)
			continue;
		CTable h(*pOBJ);
		long lOrig = -1L;
		for ( h.First(); h.Valid(); h.Next() ) {
			TR_OBJLock i(h);
			if ( !i)
				continue;
			long lONF = i->Object();

			if (!TopologieLinieInFlaeche ( lONF,lONr, &Rel)) {
				continue;
			} else {
				if ( Rel == REL_INN)
					LinieInFlaeche ( lONF,lONr,lOrig,iTyp,pGewNr,pGEB);
				if ( Rel == REL_INAUS)
					LinieInAusFlaeche ( lONF,lONr,iTyp,pGewNr,pGEB);

				iFlag = true;
			}
		}
	
	}
	return iFlag;
}

//////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: KlassenTyp ( short iTyp, long lIdent)
{
	bool iFlag = false;

	if ( !m_pKH)
		return iFlag;

	if ( 0L == lIdent )
		return iFlag;

	ulong ulFClass = m_pKH->CodeFlaKl();
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
///////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
bool CKompiasExtension :: TopologieLinieInFlaeche ( long ONF, long ONr,Relat *pRel )
{

//------------Versuch Topologie-Test------------------------

	if ( m_pTop) {
		Relat Rel;
		HRESULT hr = m_pTop->TopoRelationObjObj_ONr ( ONF,ONr,&Rel);
		if (FAILED(hr)) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINETOPOLOGIE, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			MB_ICONSTOP);
			return false;
		}
		*pRel = Rel;
		if ( Rel == REL_INN || Rel == REL_INAUS)
			return true;

		return false;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
bool CKompiasExtension :: LinieInFlaeche ( long lONF, long lONr,long lOrig, short iTyp,LPSTR pGewNr,KPBTree *pGEB )
{
	if ( !pGEB)
		return false;
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONF;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_FLAECHE) 
			return false;
	} else
		return false;

	OS.lONr =  lONr;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return false;
	} else
		return false;


	OS.lONr =  lOrig;
	if ( lOrig != -1L) {
		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp != OT_KANTE ) 
				return false;
		} else
			return false;
	}

	char *pName = new char [_MAX_PATH];
	if ( !pName)
		return false;


	long lIdent = DEX_GetObjIdent(lONF);

	*pName = '\0';
	ulong lSMCode = DEX_GetObjNameMCode(lIdent);
	GetStandardMCode ( lONF, lSMCode, pName);

	CTable t(*pGEB);

	long lPos;

	FLAECHENANABSCHNITTEN FA;
   	memset (&FA,'\0',sizeof(FLAECHENANABSCHNITTEN));

	FA.dwSize = sizeof(FLAECHENANABSCHNITTEN);
	FA.pcGewaesserNr = pGewNr;

	FA.iIdentNr = iTyp;
	FA.iLinksRechtsBeide = 2;
	FA.dQuadratMeter = FlaechenGroesse(lONF);
	if ( lOrig == -1L ) {
		FA.lBeginn = 0L;
		FA.lEnde = LinienLaenge(lONr);
	} else {
		long lStart = LinienStartPunkt(lOrig,lONr);
		FA.lBeginn = lStart;
		FA.lEnde = lStart + LinienLaenge(lONr);
	}
	FA.pObjektKlasse = HoleKurzText(lIdent);
	FA.pObjektBezeichnung = pName;
	lPos = FA.lBeginn;	

	KP_GEBCreator GBCr ( *pGEB);
	ContCreate ( GBCr, KP_GEB) ( lPos, lONF, &FA);

	DELETE_OBJ ( pName);
	return true;
}
///////////////////////////////////////////////////////////////////////
long CKompiasExtension :: LinienStartPunkt ( long lOrig, long lONr)
{
	long lDist = 0L;

	if ( !m_pAbst)
		return lDist;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lOrig;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return lDist;
	} else {
		return lDist;
	}

//------------Interface ------------------------------------
//	ObjektGeometrie der Kante holen - m_pIOG
	if ( !LadeObjektGeometrie ( lOrig))
		return lDist;

	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE) 
			return lDist;
	} else {
		return lDist;
	}

	OBJGEOMETRIE OG;
	long *pX = new long [OS.lCnt];
	long *pY = new long [OS.lCnt];
    
	if (pX == NULL || pY == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return lDist;
	}

	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lCnt = OS.lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = ~OGConverted;
	if (!DEX_GetObjGeometrie (OG)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return lDist;
	}

	double dAbstand = 0.0;

	HRESULT hr = m_pAbst->DistanceFromOrigin_Geom(m_pIOG,pX,pY,&dAbstand);
	if (FAILED(hr)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}
	dAbstand = dAbstand + 0.5;
	long lStart = ObjektStartPunkt(lOrig,m_pKH->CodeBauwAnfStat());
	lDist = (long) dAbstand + lStart;
	return lDist;
}
///////////////////////////////////////////////////////////////////////
long CKompiasExtension :: ObjektStartPunkt ( long lONr,ulong ulMCode)
{
	long lStart = 0;
	if (lONr == -1L || lONr == 0L || ulMCode == 0L)
		return lStart;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return lStart;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)ulMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( DEX_GetTextMerkmal ( tm ))  {
		if ( *pBuffer != '\0') 
			lStart = atol(pBuffer);
	}
	DELETE_OBJ ( pBuffer);
	return lStart;
	
}
///////////////////////////////////////////////////////////////////////
double CKompiasExtension :: FlaechenGroesse ( long lONF)
{

	double dFla = 0.0;

	if ( m_pObjPropF ) {

		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  lONF;

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp == OT_FLAECHE) {

				char *pName = new char [_MAX_PATH];
				if ( pName ) {
					m_pObjPropF->Eval(lONF,pName,64,NULL);
					dFla = atof ( pName);
					dFla = dFla + 0.5;
					DELETE_OBJ ( pName);
				}
			}
		}
	}
	return dFla;
}
///////////////////////////////////////////////////////////////////////
long CKompiasExtension :: LinienLaenge ( long lONL)
{

	long lLen = 0L;
	double dLen;

///*-----------------------------------------
	
	if ( !m_pCTF ) {
		m_pCTF = new CoordTransX;

		if ( !m_pCTF ) 
			return lLen;
	}
/*--------------------------------------------------------
	ObjPropClass *pObjProp = new ObjPropClass(m_pCTF);
	if ( pObjProp) {
		char *pName = new char [_MAX_PATH];
		if ( pName ) {
			pObjProp->Eval(lONL,pName,64,NULL);
			dLen = atof ( pName);
			dLen = dLen + 0.5;
			DELETE_OBJ ( pName);
			lLen = ( long ) dLen;
		}

		DELETE_OBJ ( pObjProp);
	}

------------------------------*/
	if ( m_pObjPropL ) {

		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  lONL;

		try {

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp == OT_KANTE) {

				char *pName = new char [_MAX_PATH];
				if ( pName ) {


					m_pObjPropL->Eval(lONL,pName,64,NULL);
				// km oder m
					char *ptr = strchr(pName,'[');
					double dFak = 1.0;
					if (ptr) {
						ptr++;
						if ('k' == *ptr)
							dFak = 1000.0;
					}

					dLen = atof ( pName);
					dLen = dLen * dFak;
					dLen = dLen + 0.5;

					DELETE_OBJ ( pName);
					lLen = ( long ) dLen;
				}
			}
		}

		} catch (...) {
				KompaktProtokoll ( m_pLocProt,"\t Linienlänge nicht definiert !");
				lLen = 0;
		}


	}
//----------------------------------------------*/


	return lLen;
}
//-------------------------------------------------------------------------
bool CKompiasExtension :: LinieInAusFlaeche ( long lONF, long lONr,short iTyp, LPSTR pGewNr, KPBTree *pGEB )
{
	if ( !pGEB)
		return false;

	if ( !m_pObjOp)
		return false;

	CTable t(*pGEB);


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
		return false;
	}


	ULONG ulCount = pIEnum->Count();
	if ( 0 >= ulCount) {
		pIEnum->Release();
		return false; 
	}

	long lON;

	for ( pIEnum->Reset(); S_OK == pIEnum->Next(1,&lON,NULL); /**/)
	{
		LinieInFlaeche ( lONF,lON,lONr,iTyp,pGewNr,pGEB);

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
		DEX_DeleteObject ( lON);
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	}

	pIEnum->Release();

	return true;
}	
//////////////////////////////////////////////////////////////////////
char * CKompiasExtension :: HoleKurzText ( long lIdent)
{
	char * pText = new char [_MAX_PATH];
	if ( !pText)
		return NULL;
	*pText = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
#endif

	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pText;
	pbdData.pbdKTextLen = _MAX_PATH-1;
	pbdData.pbdLTextLen = 0;

#if _MSC_VER < 1100
	DEX_GetPBDData (pbdData);
#else
	DEX_GetPBDDataEx (hPr,pbdData);
#endif

	return pText;
}

//----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//----------KPAREA.CXX
