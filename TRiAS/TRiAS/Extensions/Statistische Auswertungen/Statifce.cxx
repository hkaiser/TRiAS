//-----------Statistik-MEMBER : Interface - Trias----------
// File: STATIFCE.CXX

#include "statistp.hxx"

#include <shellapi.h>

#include <igeometr.hxx>

#include "dirmath.h"
#include "version.h"

//#include <triastlb_i.c>
const IID IID_DApplication = {0x8DE4E3C4,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};

#include <triastlb.h>
#include <dirisole.h>


#include <trelguid.h>
#include <operguid.h>

#include <xtsnguid.h>

#include <initguid.h>	// beim für Linken CLSID_UndoRedoObject erforderlich
#include <undoguid.h>	// CLSID_UndoRedoObject, IID_IUndoRedoModifyObject
#include <iunredo.hxx>	// LPUNDOREDOMODIFYOBJECT

#include <oleguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "geostat.h" 
#include "about.h"


#include "about.hxx"
#include "trfkoord.hxx"
#include "trfvect.hxx"
#include "idkey.hxx"    
#include "objkey.hxx"
#include "classkey.hxx"
#include "dbclass.hxx"
#include "classgi.hxx"
#include "stohwnd.hxx"
#include "dbinfo.hxx"
#include "geostat.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "geostat.h"
#include "about.h"
#include "about.hxx"
#include "geostat.hxx"

//--------------------------------------------------------------------------
//-------------------- TRiAS - Interface -----------------------------------
//--------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
bool StatistExtension :: LadeBasicScript ( void )
{

	if ( !m_pScript) {

		HRESULT hr = 0;

		if (g_pTE->m_pXtnSite)
			hr = g_pTE->m_pXtnSite -> GetXtension ( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if (FAILED (hr) ||	// Fehler
			! g_pTE->m_pXtnSite)
			return false;
	}
	return true;

}
///////////////////////////////////////////////////////////////////////
bool StatistExtension :: LadeBasicDocument ( void )
{
	if ( m_pDoc)
		return true;

// 1. ApplicationObjekt von OleAuto geben lassen
	IGetTRiASApplication *pIGetApp = NULL;
	HRESULT hr = g_pTE->m_pXtnSite -> GetXtension (CLSID_OleAutoExtension, IID_IGetTRiASApplication, (LPVOID*)&pIGetApp);

	if (FAILED(hr)) 
		return false;

	_DApplication *pIApp = NULL;

//	hr = pIGetApp -> GetApplication (IID__DApplication, (LPVOID *)&pIApp);
	hr = pIGetApp -> GetApplication (IID_DApplication, (LPVOID *)&pIApp);
	pIGetApp -> Release();
	if (FAILED(hr)) 
		return false;

// 2. Aktives Dokument über _DApplication geben lassen
	m_pDoc = NULL;

	hr = pIApp -> get_ActiveDocument (&m_pDoc);
	pIApp -> Release();
	if (FAILED(hr))
		return false;

	return true;

}
//-------------------------------------------------------------------
bool StatistExtension :: LadeTopRel ( void )
{
//-------TopologischeRelationen laden------------------------------------

	if ( !m_pTop) {
		HRESULT hr = 0;

		if (m_pXtnSite)
			hr = m_pXtnSite -> GetXtension ( CLSID_Topologie, IID_IExtendTopRel2, (LPVOID*)&m_pTop);

		if (FAILED (hr) ||	// Fehler
			! m_pXtnSite)
			return false;
	}
	return true;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
bool StatistExtension :: LadeObjOp ( void )
{
//-------ObjektOperationen laden------------------------------------

	if ( !m_pObjOp) {
		HRESULT hr = 0;

		if (m_pXtnSite)
			hr = m_pXtnSite -> GetXtension ( CLSID_GeometrieOperationen, IID_IExtendObjOper, (LPVOID*)&m_pObjOp);

		if (FAILED (hr) ||	// Fehler
			! m_pXtnSite)
			return false;
	}
	return true;
}

//-------------------------------------------------------------------
void StatistExtension :: ReleaseInterface ( void )
{

	if ( m_pScript) {
		m_pScript->Release();
		m_pScript = NULL;
	}

	if ( m_pDoc) {
		m_pDoc->Release();
		m_pDoc = NULL;
	}

	if ( m_pTop) {
		m_pTop->Release();
		m_pTop = NULL;
	}

	if ( m_pObjOp) {
		m_pObjOp->Release();
		m_pObjOp = NULL;
	}

	return;
}
//////////////////////////////////////////////////////////////////
bool StatistExtension :: GetGeoObjectFromONr( long lONr, _DGeoObject **ppIObj)
{
	if ( !m_pDoc)
		LadeBasicDocument();

	if ( !m_pDoc )
		return false;


// 3. Vom aktiven Dokument ein konkretes Objekt geben lassen
	CComVariant vONr;
	CComVariant vMode;

	V_VT(&vONr) = VT_I4;		// ObjektNummer ist immer LONG
	V_I4(&vONr) = lONr;
	V_VT(&vMode) = VT_I2;		// Mode ist immer GEOOBJECTMODE_Get
	V_I2(&vMode) = GEOOBJECTMODE_Get;

	HRESULT hr = m_pDoc -> GetObject (vONr, vMode, ppIObj);
	if (FAILED(hr)) 
		return false;

	return true;

}
//////////////////////////////////////////////////////////////////
void StatistExtension :: LoescheStatistikFlaechen (void)
{

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) 
		return;

	strcpy( pCode, ResString ( ResID ( IDS_BASICUROBJEKT,&RF()),50));
	ulong lMCode = DEX_GetMCodeFromFeatureName ( pCode );
	DELETE_OBJ ( pCode);
	if ( 0L == lMCode )
		return;


	CEierUhr Wait ( MVWind());
	long lON;

	ENUMRECHTEXTMERKMAL EM;
	memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
	EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	EM.lMCode = lMCode;
	EM.iMode = SMExactMatch;
	EM.eFcn = (RECHTEXTMERKMALCALLBACK) DelStatObjects;
	EM.pData = &lON;
	DEX_EnumRechTextMerkmal(EM);

	return;

}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//---------------------STATIFCE.CXX-----------------------------------    
