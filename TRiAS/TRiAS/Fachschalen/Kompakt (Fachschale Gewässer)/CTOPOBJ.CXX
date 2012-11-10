// Klasse, die zu einem Flächenobjekt alle innenliegenden Objekte 
// einer vorgegeben Klasse liefert ------------------------
// File: CTOPOBJ.CXX


#include "kompp.hxx"
#include "version.h"
#include <triashelper.h>
//#include <triashelper_i.c>

//#include <ienumonr.hxx>	// CEnumObjectsByNumber

#include <igeometr.hxx>

//#include <iterenum.h>


#include "kompias.h"
#include "about.h"
#include "triasdef.h"
#include "kompdef.h"

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "gewbaum.hxx"

#include "komphead.hxx"

//#include <ipropseq.hxx>
#include "kompdll.hxx"
#include "kompgew.hxx"

#include <xtsnguid.h>
#include <eonrguid.h>

#include <xtsnaux.hxx>
#include <initguid.h>

//#include <istatus.h>
#include <trelguid.h>
#include <operguid.h>
#include "kpstatus.hxx"
#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompias.hxx"



// --------------------------------------------------------------------------------------------
// benötigte SmartInterfaces
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber
DefineSmartInterface(EnumLONG);	// WEnumLONG

/////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor -----------------------------------------------------
CTopObject :: CTopObject (LONG lONr, long *pObj, long **ppInnen, long **ppInAus)
{
	INITSTRUCT (m_osObj, OBJSTATISTIK);
	m_osObj.lONr = lONr;

	m_pOBJ = NULL;
	m_pInnen = NULL;
	m_pInMod = NULL;
	m_pOriginal = NULL;
	_ppInnen = NULL;
	_ppInAus = NULL;

	m_pOBJ = pObj;
		
	m_ifTop = NULL;
	m_ifObjOp = NULL;
	if ( ppInnen )
		_ppInnen = ppInnen;
	if ( ppInAus )
		_ppInAus = ppInAus;

	m_fInitialized = false;
}


CTopObject :: ~CTopObject (void)
{
	if ( m_ifTop) {
		m_ifTop->Release();
		m_ifTop = NULL;
	}
	if ( m_ifObjOp) {
	    m_ifObjOp->Release();
		m_ifObjOp = NULL;
	}

	DELETE_OBJ ( m_pOriginal);
}
//////////////////////////////////////////////////////////////////////
// ObjektStatistik ---------------------------------------------------
bool CTopObject :: FInit (void)
{
	if (m_fInitialized)
		return true;

// Statistik anfordern
	if (!DEX_GetObjStatistik (m_osObj))
		return false;

	if (m_osObj.iObjTyp != OGFlaeche) 
		return false;
		
	if ( 0 >= *m_pOBJ )
		return false;

	_pW = g_pTE->MVWind(); 

// Und nun zu den Interfaces

//-------TopologischeRelationen laden------------------------------------
	if (!isTopoRel())
		return false;

//-------ObjektOperationen laden------------------------------------
	if (!isObjOper())
		return false;
	long lDim = *m_pOBJ;
	m_pInnen = new long [lDim + 1];
	if ( !m_pInnen)
		return false;

	m_pInMod = new long [lDim + 1];
	if ( !m_pInMod) {
		DELETE_OBJ ( m_pInnen);
		return false;
	}
	*m_pInnen = 0L;
	*m_pInMod = 0L;

	m_fInitialized = true;

return true;
}
//////////////////////////////////////////////////////////////////////////
void CTopObject :: SetWindowHandle( pWindow pW ) 
{
	_pW = pW;
}
//////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// Topologie abfragen ---------------------------------------------------
bool CTopObject :: isTopoRel ( void )
{
	if ( !m_ifTop) {
		HRESULT hr = 0;

		if (g_pTE->m_pXtnSite)
			hr = g_pTE->m_pXtnSite -> GetXtension ( CLSID_Topologie, IID_IExtendTopRel2, (LPVOID*)&m_ifTop);

		if (FAILED (hr) ||	// Fehler
			! g_pTE->m_pXtnSite)
			return false;
	}
	return true;

}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// Objektoperationen abfragen ---------------------------------------------
bool CTopObject :: isObjOper ( void )
{

	if ( !m_ifObjOp) {
		HRESULT hr = 0;

		if (g_pTE->m_pXtnSite)
			hr = g_pTE->m_pXtnSite -> GetXtension ( CLSID_GeometrieOperationen, IID_IExtendObjOper, (LPVOID*)&m_ifObjOp);

		if (FAILED (hr) ||	// Fehler
			! g_pTE->m_pXtnSite)
			return false;
	}
	return true;

}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// FlaechenStatistik ------------------------------------------------------
long * CTopObject :: FlaechenTeile ( void)
{
	if (!m_fInitialized)
		return NULL;

	long lONF = m_osObj.lONr;

	if ( !TopologieTest(lONF, OGFlaeche))
		return NULL;

	if ( !ObjektOperation ( lONF, OGFlaeche))
		return NULL;

	return ErgebnisVektor();
}
/////////////////////////////////////////////////////////////////////////////
long * CTopObject :: ErgebnisVektor ( void ) 
{
	long lCount = 0L;
	lCount = *m_pInnen + *m_pInMod;
	if ( 0L == lCount ) {
		DELETE_OBJ (m_pInnen);
		DELETE_OBJ (m_pInMod);
		return NULL;
	}

	long *pErg = new long [ lCount + 1];
	if ( !pErg) {
		DELETE_OBJ (m_pInnen);
		DELETE_OBJ (m_pInMod);
		return NULL;
	}

	*pErg = lCount;

	lCount = 0L;
	if ( 0L < *m_pInnen ) {
		for ( long i = 0L; i < *m_pInnen; i++) {
			*(pErg + i + 1 ) = *(m_pInnen + i + 1);
			lCount++;
		}
		*_ppInnen = m_pInnen;
	} else
		DELETE_OBJ ( m_pInnen);
 

	if ( 0L < *m_pInMod ) {
		for ( long i = 0L; i < *m_pInMod; i++) {
			*(pErg + lCount + i + 1) = *(m_pInMod + i + 1);
		}
		*_ppInAus = m_pInMod;
	} else 
		DELETE_OBJ ( m_pInMod);

	return pErg;
}
//--------------------------------------------------------------------
// LinienStatistik ---------------------------------------------------
long * CTopObject :: LinienTeile ( void)
{
	if (!m_fInitialized)
		return NULL;

	long lONF = m_osObj.lONr;

	if ( !TopologieTest(lONF, OGLinie))
		return NULL;

	if ( !ObjektOperation ( lONF, OGLinie))
		return NULL;

	return ErgebnisVektor();

}
//-------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
// TopologieTest
//////////////////////////////////////////////////////////////////////////
bool CTopObject :: TopologieTest ( long lONF, short iGiTyp)
{
	if ( !m_pOBJ || !m_pInnen || !m_pInMod) {
		DELETE_OBJ ( m_pInnen);
		DELETE_OBJ ( m_pInMod);
		return false;
	}

	if ( !m_ifTop) {
		DELETE_OBJ ( m_pInnen);
		DELETE_OBJ ( m_pInMod);
		return false;
	}

	long lIn = 0L;
	long lInAus = 0L;
	long lMax = *m_pOBJ;
	long lCount = 0L;

	ResString resCaption (ResID(IDS_TOPOLOGIETEST, &g_pTE->RF()), 50);

	CStatus *pStatus = new CStatus ( _pW, &g_pTE->RF(),lMax, resCaption);
//	CStatus *pStatus = new CStatus ( _pW, &g_pTE->RF(),lMax, "Topologietest");
	if ( pStatus)
		pStatus->Show();

	for (long i = 0L; i < lMax; i++ ) {
		long lONr = *(m_pOBJ+i+1);
		lCount++;
		if ( iGiTyp != DEX_GetObjectType (lONr))
			continue;
		Relat Rel;
		HRESULT hr = m_ifTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
		if (FAILED(hr)) 
			continue;
		if ( REL_INN == Rel ) {
			lIn++;
			*(m_pInnen + lIn ) = lONr;
		}
		if ( REL_INAUS == Rel ) {
			lInAus++;
			*(m_pInMod + lInAus ) = lONr;
		}
		if ( pStatus) 
			pStatus->SetValue( lCount, lONr);
		
	}
	if (pStatus)
		DELETE_OBJ ( pStatus);

	*m_pInnen = lIn;
	*m_pInMod = lInAus;
	return true;
}
//-------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
// ObjektOperationen
//////////////////////////////////////////////////////////////////////////
bool CTopObject :: ObjektOperation ( long lONF, short iGiTyp)
{
	if ( !m_pInMod) {
		DELETE_OBJ (m_pInnen);
		return false;
	}

	if ( 0L == *m_pInMod )
		return true;

	if ( !m_ifObjOp) {
		DELETE_OBJ ( m_pInMod);
		DELETE_OBJ ( m_pInnen);
		return false;
	}


	long lONr;
	long lCount = *m_pInMod;
	m_pOriginal = new long [ lCount + 1 ];
	if ( !m_pOriginal) {
		DELETE_OBJ ( m_pInMod);
		DELETE_OBJ ( m_pInnen);
		return false;
	}

	((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();
	
	*m_pOriginal = lCount;

	// Übertragen der Objektnummern 

	IEnumLONG * pIEnum = NULL;

	try {

		WEnumObjectsByNumber wIEnumObj (CLSID_EnumObjectsByNumber);

		for (long i = 0; i < lCount; i++) {
			wIEnumObj -> AddItem (m_pInMod[i+1]);
			m_pOriginal[i+1] = m_pInMod[i+1];
		}


		DWORD Lage = LINN;
		if ( iGiTyp == OT_KANTE)
			Lage = LINN | LKONT;
		((CKompiasExtension *)g_pTE)->ExtObjectChangedUnRegisterNotification();
		
//		g_pTE->UnRegisterNotification (DEX_N_OBJECTCREATED);

		HRESULT hr = m_ifObjOp->SectionObjObjs_ONr (lONF,WEnumLONG(wIEnumObj),Lage,SFORM_PERM,&pIEnum);
		((CKompiasExtension *)g_pTE)->ExtObjectChangedRegisterNotification();
		
//		g_pTE->RegisterNotification (DEX_N_OBJECTCREATED);

		if (FAILED(hr))
			_com_issue_error(hr);
	} catch (_com_error&){
		DELETE_OBJ ( m_pInMod);
		DELETE_OBJ ( m_pInnen);
		((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();
		return false;
	}

	DELETE_OBJ ( m_pInMod);

	ULONG ulCount = pIEnum->Count();
	if ( 0 >= ulCount) {
		pIEnum->Release();
		DELETE_OBJ ( m_pInnen);
		return false; 
	}

	m_pInMod = new long [ulCount+1];
	if ( !m_pInMod ) {
		pIEnum->Release();
		DELETE_OBJ ( m_pInnen);
		return false; 
	}

	lCount = 0L;
	*m_pInMod = 0L;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		pIEnum->Release();
		DELETE_OBJ ( m_pInnen);
		DELETE_OBJ ( m_pInMod);
		return false;
	}

	// Cloned Object
	ulong lMCode = 0L;
	wsprintf( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),40));

#if _MSC_VER < 1100

	lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#else
	HPROJECT hPro = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	lMCode = DEX_GetMCodeFromFeatureNameEx(hPro,pCode);
#endif

	DELETE_OBJ ( pCode);

	((CKompiasExtension *)g_pTE)->ExtModifyRegisterNotification ();

	if ( 0L == lMCode ) {
		lMCode = DEX_GetUniqueSysMCode ();
		if ( 0L == lMCode ) {
			pIEnum->Release();
			DELETE_OBJ ( m_pInnen);
			DELETE_OBJ ( m_pInMod);
			return false;
		}

		if ( !SetPBDMCode( lMCode,pIEnum)) {
			pIEnum->Release();
			DELETE_OBJ ( m_pInnen);
			DELETE_OBJ ( m_pInMod);
			return false;
		}
	}

	ResString resCaption (ResID(IDS_OBJEKTOPERATIONEN, &g_pTE->RF()), 50);
	CStatus *pStatus = new CStatus ( _pW, &g_pTE->RF(),(long) ulCount, resCaption);
	if ( pStatus)
		pStatus->Show();

	for ( pIEnum->Reset(); S_OK == pIEnum->Next(1,&lONr,NULL); /**/)
	{
		// Objekt auf GI Testen !!
		short Status = DEX_GetObjectType (lONr);

	//--------------Zuordnung----------------------------
		if ( Status == iGiTyp ) {
			lCount++;
			*(m_pInMod+lCount) = lONr;

			((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();
	
			SetObjektWert ( lONr, lMCode);

			((CKompiasExtension *)g_pTE)->ExtModifyRegisterNotification ();
		
			if ( pStatus) 
				pStatus->SetValue( lCount, lONr);
		} else {
			((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();
//			g_pTE->UnRegisterNotification (DEX_N_OBJECTCREATED);

			DEX_DeleteObject(lONr);
			((CKompiasExtension *)g_pTE)->ExtObjectChangedRegisterNotification();

//			g_pTE->RegisterNotification (DEX_N_OBJECTCREATED);
		}
	}
	if (pStatus)
		DELETE_OBJ ( pStatus);

	*m_pInMod = lCount;

	pIEnum->Release();

	((CKompiasExtension *)g_pTE)->ExtModifyUnRegisterNotification ();

//////////////////////////////////////////////////////////////////////////
	return true;
}
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für TeilProjekte in PBD setzen
//-------------------------------------------------------------------
bool CTopObject :: SetPBDMCode ( ulong MCode, IEnumLONG *pIEnum)
{
if ( !pIEnum )
	return false;

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
	pbdData.ipbdMLen = MAX_PATH;


#if _MSC_VER >= 1100

	long lONr = 0L;

	for ( pIEnum->Reset(); S_OK == pIEnum->Next(1,&lONr,NULL); /**/)

	{
		// Objekt auf GI Testen !!
		short Status = DEX_GetObjectType (lONr);
		short iGiTyp = OT_KANTE;

	//--------------Zuordnung----------------------------
		if ( Status == iGiTyp ) {

			long lIdent = DEX_GetObjIdent ( lONr);

			pbdData.lIdent = lIdent;

			DefineFeatureSet (&pbdData);

/*--------------------
			HPROJECT hPro = DEX_GetObjectProject(lONr);

	// Test, ob OE bereits definiert
			long lRefCode = DEX_GetMCodeFromFeatureNameEx(hPro,KText);
			if (lRefCode != 0L && lRefCode != MCode)
				((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,lIdent,&KText[0]);
	
			{
			ErrInstall EI (WC_NOMERKMAL);
				if (DEX_ModPBDDataEx (hPro,pbdData) != EC_OKAY)
					continue;
				else
					DEXN_PBDMCodeChanged (MCode);
			}

  --------------------------------------*/
		}
		
	}
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
//------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
// MCode für Objekte setzen
//-------------------------------------------------------------------
void CTopObject :: SetObjektWert ( long lONr, ulong MCode)
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
///////////////////////////////////////////////////////////////////////////
//-----------File CTOPOBJ.CXX
