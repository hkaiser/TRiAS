//-----------Kompias-MEMBER : Interface - Trias----------
// File: KOMPIFCE.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <igeometr.hxx>

#include <shellapi.h>
#include <triastlb.h>

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <abstguid.h>
#include <trelguid.h>
#include <buffguid.h>
#include <xtsnguid.h>
#include <operguid.h>

#include <initguid.h>	// beim für Linken CLSID_UndoRedoObject erforderlich
#include <undoguid.h>	// CLSID_UndoRedoObject, IID_IUndoRedoModifyObject
#include <iunredo.hxx>	// LPUNDOREDOMODIFYOBJECT

#include <oleguid.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "triasdef.h"
#include "kompdef.h"
#include "cobjtree.hxx"
#include "ctopobj.hxx"

#include "komphead.hxx"
#include "kompdll.hxx"
#include "gewbaum.hxx"
#include "kompias.hxx"

const IID IID_DApplication = {0x8DE4E3C4,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};


//--------------------------------------------------------------------------
//-------------------- TRiAS - Interface -----------------------------------
//--------------------------------------------------------------------------

bool CKompiasExtension :: LadeObjektGeometrie ( long lONr )
{

//--------Objektgeometrie-Interface holen !!!!
	if ( m_pIOG ) {
		m_pIOG->Release();
		m_pIOG = NULL;
	}

	return CreateInterfaceOG (&m_pIOG, lONr);
}
//------------------------------------------------------------------

bool CKompiasExtension :: CreateInterfaceOG ( IObjektGeometrie ** ppIOG, long lONr )
{
	TX_ASSERT (lONr > 0);

	IInitObjektGeometrie* pInitOG = NULL;

	HRESULT hr = CoCreateInstance (CLSID_ObjektGeometrie, NULL, CLSCTX_INPROC_SERVER,
								IID_IInitObjektGeometrie, (LPVOID*) &pInitOG);

	if (FAILED(hr)) 
		return false;
	
	HRESULT hrRet = pInitOG -> InitObjGeometry (lONr);

	if (hrRet != S_OK) {
		if (pInitOG) {
			pInitOG -> Release ();
			pInitOG = NULL;
		}
		return false;
	}

	hr = pInitOG -> QueryInterface (IID_IObjektGeometrie, (LPVOID*) ppIOG);

	pInitOG -> Release ();
	pInitOG = NULL;

	if (FAILED(hr) )
		return false;

	return true;
} // CreateInterfaceOG
//--------------------------------------------------------------------

bool CKompiasExtension :: LadeAbstandsErweiterung ( void )
{
//-------Abstandserweiterung laden------------------------------------

	if ( !m_pAbst ) {
		HRESULT hr = 0;

		if (m_pXtnSite)
			hr = m_pXtnSite -> GetXtension ( CLSID_Abstand, IID_IExtendAbstand2, (LPVOID*)&m_pAbst);

		if (FAILED (hr) ||	// Fehler
			! m_pXtnSite)
			return false;
	}
	return true;
}
//-------------------------------------------------------------------

bool CKompiasExtension :: LadeTopRel ( void )
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

bool CKompiasExtension :: LadePuffer ( void )
{
//-------ObjektPuffer laden------------------------------------

	if ( !m_pPuf) {
		HRESULT hr = 0;

		if (m_pXtnSite)
			hr = m_pXtnSite -> GetXtension ( CLSID_BufferExtension, IID_IExtendBuffer, (LPVOID*)&m_pPuf);

		if (FAILED (hr) ||	// Fehler
			! m_pXtnSite)
			return false;
	}
	return true;
}
//-------------------------------------------------------------------

bool CKompiasExtension :: LadeObjOp ( void )
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
//--------------------------------------------------------------------
bool CKompiasExtension :: LadeObjektEigenschaft ( void )
{
	
//-------ObjektEigenschaft laden------------------------------------
	if ( m_pObjPropL && m_pObjPropF && m_pObjRechts && m_pObjHoch )
		return true;

	bool iFlag = true;

	IObjectProps *pIOProps = NULL;
	HRESULT hr = 0;

	if (m_pXtnSite)
		hr = m_pXtnSite -> QueryInterface (IID_IObjectProps, (LPVOID *)&pIOProps);
	if (FAILED(hr) || ! m_pXtnSite)
		return false;

// Initialisierung für alle Objekteigenschaften
	pIOProps -> OnNewReferenceObject (0L);

// jetzt lassen wir uns die Liste der OProps geben
	IEnumObjProps *pIEnum = NULL;

	hr = pIOProps -> EnumObjectProps (&pIEnum);
	if (FAILED(hr)) 
		iFlag = false;
	
	pIOProps -> Release();		// wird nicht mehr gebraucht
	pIOProps = NULL;

	if (!iFlag)
		return false; 
//-------------------------------------------------------------------
	pIEnum -> Reset(); 
	iFlag = true;
	
	if ( !m_pObjPropL) {
		hr = pIEnum -> FindByName (ResString (ResID(IDS_PROPLINIENLAENGE, &RF()),50).Addr(), &m_pObjPropL);
		if (FAILED(hr)) 
			iFlag = false;

		if (!iFlag) {
			if (m_pLocProt)
				KompaktProtokoll (m_pLocProt,"\n\t *Interface: LinienLänge nicht ladbar!\n");
			pIEnum -> Release();
			pIEnum = NULL;
			m_pObjPropL = NULL;
			return false;
		}
		pIEnum -> Reset(); 
		iFlag = true;

	}

	if ( !m_pObjPropF) {
		hr = pIEnum -> FindByName (ResString (ResID(IDS_PROPFLAECHENINHALT, &RF()),50).Addr(), &m_pObjPropF);
		if (FAILED(hr)) 
			iFlag = false;

		if (!iFlag) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_KEINEFLAECHE, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			 MB_OK);
			pIEnum -> Release();
			pIEnum = NULL;
			m_pObjPropF = NULL;
			return false;
		}
		pIEnum -> Reset(); 
		iFlag = true;
	}


	if ( !m_pObjRechts) {
		hr = pIEnum -> FindByName (ResString (ResID(IDS_PROPRECHTSWERT, &RF()),50).Addr(), &m_pObjRechts);
		if (FAILED(hr)) 
			iFlag = false;

		if (!iFlag) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_KEINREFPUNKTX, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			 MB_OK);
			pIEnum -> Release();
			pIEnum = NULL;
			return false;
		}
		pIEnum -> Reset(); 
		iFlag = true;
	}

	if ( !m_pObjHoch) {
		hr = pIEnum -> FindByName (ResString (ResID(IDS_PROPHOCHWERT, &RF()),50).Addr(), &m_pObjHoch);
		if (FAILED(hr)) 
			iFlag = false;

		if (!iFlag) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_KEINREFPUNKTY, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			 MB_OK);
			pIEnum -> Release();
			pIEnum = NULL;
			return false;
		}
	}

	pIEnum -> Release();
	pIEnum = NULL;

	return iFlag;

}
///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: LadeBasicScript ( void )
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
bool CKompiasExtension :: LadeBasicDocument ( void )
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
void CKompiasExtension :: ReleaseInterface ( void )
{

	if ( m_pIOG) {
		m_pIOG->Release();
		m_pIOG = NULL;
	}

	if ( m_pAbst) {
		m_pAbst->Release();
		m_pAbst = NULL;
	}

	if ( m_pTop) {
		m_pTop->Release();
		m_pTop = NULL;
	}

	if ( m_pPuf) {
		m_pPuf->Release();
		m_pPuf = NULL;
	}

	if ( m_pObjOp) {
		m_pObjOp->Release();
		m_pObjOp = NULL;
	}


	if ( m_pObjPropL) {
		m_pObjPropL->Release();
		m_pObjPropL = NULL;
	}

	if ( m_pObjPropF) {
		m_pObjPropF->Release();
		m_pObjPropF = NULL;
	}

	if ( m_pObjRechts) {
		m_pObjRechts->Release();
		m_pObjRechts = NULL;
	}

	if ( m_pObjHoch) {
		m_pObjHoch->Release();
		m_pObjHoch = NULL;
	}



	if ( m_pScript) {
		m_pScript->Release();
		m_pScript = NULL;
	}

	if ( m_pDoc) {
		m_pDoc->Release();
		m_pDoc = NULL;
	}

	return;
}
/////////////////////////////////////////////////////////////////////
//------------
// Doppeltes Setzen von RegisterNotification () verhindern
void CKompiasExtension :: MyRegisterNotification (UINT wMsg, bool &isOK)
{
	if (! isOK)
	{
		RegisterNotification (wMsg);
		isOK = true;
	}
	
	return;

} // MyRegisterNotification
////////////////////////////////////////////////////////////////////////
// Doppeltes Setzen von UnRegisterNotification () verhindern
void CKompiasExtension :: MyUnRegisterNotification (UINT wMsg, bool &isOK)
{

	if ( isOK)
	{
		UnRegisterNotification (wMsg);
		isOK = false;
	} 
	
	return;

} // MyUnRegisterNotification
// Doppeltes Setzen von RegisterNotification () verhindern
void CKompiasExtension :: ExtModifyRegisterNotification (void)
{
	MyRegisterNotification ( DEX_MODIFYMERKMAL,m_bMerkmal);	
	return;

} // MyRegisterNotification
// Doppeltes Setzen von RegisterNotification () verhindern
void CKompiasExtension :: ExtModifyUnRegisterNotification (void)
{
	MyUnRegisterNotification ( DEX_MODIFYMERKMAL,m_bMerkmal);	
	return;

} // MyRegisterNotification
// OBJECTCHANGED
void CKompiasExtension :: ExtObjectChangedRegisterNotification (void)
{
	MyRegisterNotification ( DEX_OBJECTCHANGED,m_bChange);	
	return;

} // MyRegisterNotification
// Doppeltes Setzen von RegisterNotification () verhindern
void CKompiasExtension :: ExtObjectChangedUnRegisterNotification (void)
{
	MyUnRegisterNotification ( DEX_OBJECTCHANGED,m_bChange);	
	return;

} // MyRegisterNotification

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//---------------------KOMPIFCE.CXX-----------------------------------    
