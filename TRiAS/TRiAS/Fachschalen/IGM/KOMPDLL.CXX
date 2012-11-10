//-----------KOMPAKT-Objekt-Klasse : Rufen Malte ----------
// File: KOMPDLL.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <oleguid.h>
#include <dirisole.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "kompdef.h"  
#include "kompprof.hxx"

#include "kompdll.hxx"

#include <igeometr.hxx> 
#include "triasdef.h"  

#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"
#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompias.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

/// --------------------

// DllBind dll ("KOMPAKT1.DLL");


#pragma warning (disable: 4355)

/////////////////////////////////////////////////////////////////////////////
CKompaktDLL :: CKompaktDLL ( DWORD p, HWND hWnd, const char *pLibrary)
			: CDllBindX ( pLibrary)

{

try {


	_isValid = false;

	if ( ((CKompiasExtension *)g_pTE)->GetDLLInitKey() == KP_NoPart ) {
		_isValid = true;
		return;
	}


	KOMPAKTINITPROC pFcn = (KOMPAKTINITPROC ) GetProcAddress("IGMRufen");
//	KOMPAKTINITPROC pFcn = (KOMPAKTINITPROC ) GetProcAddress("KompaktRufen");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) {
		pFcn( p, hWnd );
		_isValid = true;
	} else {
		_isValid = false;
	}
	
} catch (...) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNOLOAD, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);

}


}
////////////////////////////////////////////////////////////////////////////////



#pragma warning (default: 4355)

CKompaktDLL ::~CKompaktDLL (void)
{

	if ( ((CKompiasExtension *)g_pTE)->GetDLLInitKey() == KP_NoPart )
		return;

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocProt ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf (pT," ************ IGM beenden - Aufruf : \n");
			KompaktProtokoll ( pLocProt,pT);
			DELETE_OBJ(pT);
		}
	}

try {

	KOMPAKTUNLOADPROC pFcn = (KOMPAKTUNLOADPROC)GetProcAddress("IGMBeenden");
//	KOMPAKTUNLOADPROC pFcn = (KOMPAKTUNLOADPROC)GetProcAddress("KompaktBeenden");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) 
		pFcn();

} catch (...) {

	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNOSTORE, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);

}

	char *pLocP = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocP ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf (pT," ************ IGM beenden - Fertig : \n");
			KompaktProtokoll ( pLocProt,pT);
			DELETE_OBJ(pT);
		}
	}

}

//-----------------------------------------------------------------
//
bool CKompaktDLL::IGMMenuCommand (short iCommand, HWND hWnd)
//bool CKompaktDLL::KompaktMenuCommand (short iCommand, HWND hWnd)
{

	if ( ((CKompiasExtension *)g_pTE)->GetDLLInitKey() == KP_NoPart )
		return true;


	bool iFlag = true;

try  {

	KOMPAKTCOMMANDPROC pFcn = (KOMPAKTCOMMANDPROC)GetProcAddress("IGMMenuCommand");
//	KOMPAKTCOMMANDPROC pFcn = (KOMPAKTCOMMANDPROC)GetProcAddress("KompaktMenuCommand");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) {
		_iOperation = true;
		iFlag = false;

		try {
		iFlag = pFcn(iCommand, hWnd);	// Kein RC ausgewertet !!!
		if (!iFlag)
			_iOperation = false;

		} catch ( ... ) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOCOMMAND, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			_iOperation = false;

		}
//		return pFcn(iCommand, hWnd);
	} else {
		_iOperation = false;
	}
} catch (...) {

	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNOCOMMAND, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	_iOperation = false;

}

return _iOperation;


}
////////////////////////////////////////////////////////////////////////
////////// DialogFunktionen ///////////////////////////////////////////

bool CKompaktDLL::IGMEinzelGewaesser (HWND hWnd, char *pGew)
//bool CKompaktDLL::KompaktEinzelGewaesser (HWND hWnd, char *pGew)
{
	if ( !pGew || *pGew == '\0'){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return false;
	}

	try {

		KOMPAKTCOMMANDWINPROC pFcn = (KOMPAKTCOMMANDWINPROC)GetProcAddress("IGMEinzelGewaesser");
//		KOMPAKTCOMMANDWINPROC pFcn = (KOMPAKTCOMMANDWINPROC)GetProcAddress("KompaktEinzelGewaesser");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(hWnd,pGew);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWINFO, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return false;

}
////////////////////////////////////////////////////////////////////////
////////// DialogFunktionen ///////////////////////////////////////////

 
bool CKompaktDLL::KompaktObjektEigenschaft (HWND hWnd, BAUWERKE *p)  
{
	if ( !p ){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return false;
	}

	try {

		KOMPAKTOBJPROPPROC pFcn = (KOMPAKTOBJPROPPROC)GetProcAddress("IGMSachDatenZeigen");
//		KOMPAKTOBJPROPPROC pFcn = (KOMPAKTOBJPROPPROC)GetProcAddress("SachDatenKompaktZeigen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn (hWnd,p);
			
		} else {
			_iOperation = false;
		}


	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return false;

}
////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::KompaktDatenPfad (char *pPfad)  
{
	if ( ((CKompiasExtension *)g_pTE)->GetDLLInitKey() == KP_NoPart )
		return false;

	if ( !pPfad ){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return false;
	}

	try {

		KOMPAKTDATENPFADPROC pFcn = (KOMPAKTDATENPFADPROC)GetProcAddress("DatenPfadZuordnen2");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;

			char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
			if ( pLocProt ) {
				KompaktProtokoll(pLocProt,"\t*** DatenPfad einstellen :\n");
				KompaktProtokoll(pLocProt,pPfad);
				KompaktProtokoll(pLocProt,"\n\t*** DatenPfad eingestellt\n");
			}

			return pFcn (pPfad);
			
		} else {
			_iOperation = false;
		}


	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return false;

}
////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::GewaesserStrukturHolen (GEWAESSER *pG)
{

	if ( !pG || !pG->pcGewaesserNr) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return cGewaesserNummerFalsch;
	}

	try {

		KOMPAKTKATASTERHOLPROC pFcn = (KOMPAKTKATASTERHOLPROC)GetProcAddress("GewaesserStrukturHolen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pG);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWLEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return cGewaesserNummerFalsch;
}
////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
//KK010913
bool CKompaktDLL::BemerkungenBauwerkGewaesserEinAus(int iKey)
{
	try {

		KOMPAKTDATENFLAGPROC pFcn = (KOMPAKTDATENFLAGPROC)GetProcAddress("BemerkungenBauwerkGewaesserEinAus");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(iKey);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_NOBEMERKUNGEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::GewaesserStrukturSetzen (GEWAESSER *pG)
{
	if ( !pG || !pG->pcGewaesserNr) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return cGewaesserNummerFalsch;
	}

	try {

		KOMPAKTKATASTERSTRUCPROC pFcn = (KOMPAKTKATASTERSTRUCPROC)GetProcAddress("GewaesserStrukturSetzen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pG);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWLEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return cGewaesserNummerFalsch;
}
////////////////////////////////////////////////////////////////////////

long CKompaktDLL::GewaesserKatasterLaengeHolen (char *pGew, long lLaenge, long lEta)
{
	if ( !pGew || *pGew == '\0') {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return cGewaesserNummerFalsch;
	}

	try {

		KOMPAKTKATASTERGETPROC pFcn = (KOMPAKTKATASTERGETPROC)GetProcAddress("GewaesserKatasterLaengeHolen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pGew,lLaenge,lEta);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWLEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return cGewaesserNummerFalsch;
}
////////////////////////////////////////////////////////////////////////

long CKompaktDLL::GewaesserNeueLaenge (char *pGew, long lLaenge)
{
	if ( !pGew || *pGew == '\0'){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return cGewaesserNummerFalsch;
	}
	if ( lLaenge <= 0L){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWLENINFO, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return cGewaesserNummerFalsch;
	}

	try {

		KOMPAKTKATASTERMODPROC pFcn = (KOMPAKTKATASTERMODPROC)GetProcAddress("GewaesserNeueLaenge");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pGew,lLaenge);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWLEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

	return cGewaesserNummerFalsch;
}
////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::GewaesserNeuAnlegen (char *pGew, char *pGewName, long lLaenge)
{
	if ( !pGew || *pGew == '\0'){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
	}
	if ( strncmp ( pGew,"Noname",6) == 0 ) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
	}
	if ( lLaenge <= 0L){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWLENINFO, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
	}

	try {

		KOMPAKTKATASTERADDPROC pFcn = (KOMPAKTKATASTERADDPROC)GetProcAddress("GewaesserNeuAnlegen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pGew,pGewName,lLaenge);
		} else {
			_iOperation = false;
		}
	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOSETGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

return false;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

char *CKompaktDLL::GewaesserNameHolen (char *pGew)
{
	if ( !pGew || *pGew == '\0'){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);

		return NULL;
	}

	try {

		KOMPAKTKATASTERNAMEPROC pFcn = (KOMPAKTKATASTERNAMEPROC)GetProcAddress("GewaesserNameHolen");

		TX_ASSERT(NULL != pFcn);

		if (pFcn) {
			_iOperation = true;
			return pFcn(pGew);
		} else {
			_iOperation = false;
		}

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWNAME, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

	}

return NULL;
}
////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::EnumeriereLeistung (short iTyp, LEISTUNGPROC p, DWORD dwData)
{

if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}



CKompiasExtension *pK = ( CKompiasExtension *)dwData;
char *pT = pK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}

try {

	ENUMLEISTUNGPROC pFcn = (ENUMLEISTUNGPROC)GetProcAddress("HoleLeistung");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) {
		_iOperation = true;
		return pFcn( iTyp, p, dwData);
	} else {
		_iOperation = false;
	}

} catch (...) {

	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	_iOperation = false;

}

return false;
}
////////////////////////////////////////////////////////////////////////

bool CKompaktDLL::EnumeriereBauwerke (short iTyp, BAUWERKEPROC p, DWORD dwData)
{

if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}


CKompiasExtension *pK = ( CKompiasExtension *)dwData;
char *pT = pK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}


try {

	ENUMBAUWERKEPROC pFcn = (ENUMBAUWERKEPROC)GetProcAddress("HoleBauwerke");

	TX_ASSERT(NULL != pFcn);
	if (pFcn) {
		_iOperation = true;
		return pFcn( iTyp, p, dwData);
	} else {
		_iOperation = false;
	}

} catch (...) {

	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	_iOperation = false;

}

return false;
}
////////////////////////////////////////////////////////////////////////////
bool CKompaktDLL::EnumeriereKompaktKatalog (short iTyp, KOMPAKTKATALOGPROC p,DWORD dwData)
{


try {

	ENUMKATALOGPROC pFcn = (ENUMKATALOGPROC)GetProcAddress("HoleKatalogItems");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) {
		_iOperation = true;
		return pFcn( iTyp, p, dwData);
	} else {
		_iOperation = false;
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWINFO, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

}

return false;
}
//-------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
bool CKompaktDLL::EnumeriereGewaesser (short iTyp, GEWAESSERPROC p, DWORD dwData)
{

if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}



CKompiasExtension *pK = ( CKompiasExtension *)dwData;
char *pT = pK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}


try {

	ENUMGEWAESSERPROC pFcn = (ENUMGEWAESSERPROC)GetProcAddress("HoleGewaesser");

	TX_ASSERT(NULL != pFcn);

	if (pFcn) {
		_iOperation = true;
		return pFcn( iTyp, p, dwData);
	} else {
		_iOperation = false;
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWINFO, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		_iOperation = false;

}

return false;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// KOMPDLL.CXX

///////////////////////////////////////////////////////////////////////////////
// Von außen zu rufende Funktionen
// Auf Wunsch von Malte 4.9.96
extern "C"
bool _XTENSN_EXPORT PASCAL HydraulikTest ( HYDRAULIK *p, DWORD dwData)
{

if ( !p || dwData == 0) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}



//-----geplant : DWORD mein THIS

CKompiasExtension *pKK = ( CKompiasExtension *)dwData;

if ( !pKK) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	return false;
}

char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}

try {
//	CKompiasExtension *pK = ( CKompiasExtension *)dwData;

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocProt ) 
		KompaktProtokoll(pLocProt,"\t==> Hydraulik : Start der Bearbeitung !\n");

	pKK->HydraulikPunkte ((LPARAM) p );

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOHYDRAULIK, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}

	return true;
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL TRiASTest (DWORD, long lTest)
{
	char * pText = new char[_MAX_PATH];
	if ( pText) {
		wsprintf ( pText, " Maltes Zahl war %ld " , lTest);
//		MessageBox (__hWndM, pText, "M A L T E", MB_OK);
		DELETE_OBJ  ( pText);
	}
	return true;
}
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeLeistungen( LEISTUNGEN *p, DWORD dwData)
{
	if ( !p) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);
		return false;
	}


	TX_ASSERT(NULL != p);
	TX_ASSERT(sizeof(LEISTUNGEN) == ((LEISTUNGEN *)p)->dwSize);
	TX_ASSERT(TIsValidAddress(p, sizeof(LEISTUNGEN), false)); // nur lesbar
//		TX_ASSERT( 0L <= ((LEISTUNGEN *)p)->lBeginn);
	TX_ASSERT( ((LEISTUNGEN *)p)->lEnde > ((LEISTUNGEN *)p)->lBeginn);
//		TX_ASSERT( 0L < ((LEISTUNGEN *)p)->lEnde);
	TX_ASSERT( NULL != ((LEISTUNGEN *)p)->pcGewaesserNr);
	TX_ASSERT( NULL != *(((LEISTUNGEN *)p)->pcGewaesserNr));

#if _MSC_VER >= 1100
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
#endif
		

try {

	CEierUhr Wait (g_pTE->MVWind());
// Anpassung an Philosophie Bauwerke

//	KPTree *pGew = (KPTree *) dwData;

	KPTree *pGew = ((BAUWERKSINPUT *) dwData) ->pGew;
	TR_OCLTree *pIdent = ((BAUWERKSINPUT *) dwData) ->pIdent;
	((BAUWERKSINPUT *) dwData) ->lCount++;

	if ( !pIdent || !pGew) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOLEISTUNGEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);

		return false;
	}


	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = p->pcGewaesserNr;
	GW.pcGewaesserName = NULL;
	GW.lBeginn = p->lBeginn;
	GW.lEnde = p->lEnde;



// Uebergabe in Kompaktdaten
	KOMPAKTDATEN KD;

	if (!LeistungenInKompakt ( p, &KD)) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOLEISTUNGEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);
		return true;
	}

	// Analog Bauwerke , nur spezielle Leistungsarten !!!!

	CTable d( *pIdent);

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheEinzelBauwerke;

	OBJEKTKLASSENTYP OT;

	ulong lIdent = KompaktIdentifikator(NULL,p->iIdentNrHerkunft ,p->iIdentNrZuordnung);

	if ( 0L != lIdent) {

		OT.lONr = -1L;
		OT.iTyp = OTLinie;
//		OT.lMCode = DEX_GetObjNameMCode(lIdent);
		OT.lMCode = ((CKompiasExtension *)g_pTE)->KPHeader()->CodeGewNr();
		OT.pMWert = p->pcGewaesserNr;



		if ( !d.Find ( &lIdent )) {
			TR_OBJTree *pObj = new TR_OBJTree;
			if ( pObj) {
				OT.pOBJ = pObj;
				ELK.eKey = lIdent;
				ELK.ePtr = &OT;
				DEX_EnumIdentObjects(ELK);

				long MCode = 0L;
				TR_OCLCreator TRCr ( *pIdent);
				ContCreate ( TRCr, TR_OCL) ( lIdent, MCode,OC_ANLEGEN, pObj);
			}
		} else {
			TR_OCLLock f(d);
			TR_OBJTree *pObj = f->OBJ();
			OT.pOBJ = pObj;
			ELK.eKey = lIdent;
			ELK.ePtr = &OT;
			DEX_EnumIdentObjects(ELK);
		}

	}


	// Finden der einzelnen Leistungen

	//////////////////////////////////////////////////////////////////////////////

	lIdent = 0L;

	short iHk = p->iIdentNrHerkunft;
	short iZuo = p->iIdentNrZuordnung;	

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

		rRefIdent = 0L;

#if _MSC_VER < 1100
		IdentFromClassX ( Ident,&rRefIdent);
#else
		HRESULT hr = IdentFromClassX ( m_hPr,Ident,&rRefIdent);
		if (hr == S_FALSE ) {
			break;
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
			break;
		}
		}

		OT.lONr = -1L;
		OT.iTyp = OTLinie;
//		OT.lMCode = DEX_GetObjNameMCode(lIdent);
		OT.lMCode = ((CKompiasExtension *)g_pTE)->KPHeader()->CodeGewNr();
		OT.pMWert = p->pcGewaesserNr;
	

		if ( !d.Find ( &lIdent )) {
			TR_OBJTree *pObj = new TR_OBJTree;
			if ( !pObj)
				return true;

			OT.pOBJ = pObj;
			ELK.eKey = lIdent;
			ELK.ePtr = &OT;
			DEX_EnumIdentObjects(ELK);

			long MCode = 0L;
			TR_OCLCreator TRCr ( *pIdent);
			ContCreate ( TRCr, TR_OCL) ( lIdent, MCode,OC_ANLEGEN, pObj);
		} else {
			TR_OCLLock f(d);
			TR_OBJTree *pObj = f->OBJ();
			OT.pOBJ = pObj;
			ELK.eKey = lIdent;
			ELK.ePtr = &OT;
			DEX_EnumIdentObjects(ELK);
		}
		

	}

// KK010222 - Trick - siehe GewBaum Def LA
// Sortierfolge wird von sequ. Eingabe aus Kompakt(lCount) auf Beginn geändert !!!
// d.h. - Sortierung aufsteigend nach Kilometrierung - Start

	CTable t( *pGew);
	if ( !t.Find ( p->pcGewaesserNr)) {
		KP_LATree *pLA = new KP_LATree;
		if (!pLA)
			return false;
		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( 1, &KD);
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (&GW, pLA);
	} else {
		KP_GEWLock l(t);
		KP_LATree *pLA = l->LA();
		if (!pLA)
			return false;
		long lCount = (long) pLA->Count() + 1;
		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( lCount, &KD);
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOLEISTUNG, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}


return true;

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeBauwerke( BAUWERKE *p, DWORD dwData)
{
if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}


	TX_ASSERT(NULL != p);
	TX_ASSERT(sizeof(BAUWERKE) == ((BAUWERKE *)p)->dwSize);
	TX_ASSERT(TIsValidAddress(p, sizeof(BAUWERKE), false)); // nur lesbar
	TX_ASSERT( 0L <= ((BAUWERKE *)p)->lObjectIdent);
//	TX_ASSERT( 0L <= ((BAUWERKE *)p)->lBeginn);
	TX_ASSERT( ((BAUWERKE *)p)->lEnde >= ((BAUWERKE *)p)->lBeginn);
//	TX_ASSERT( 0L <= ((BAUWERKE *)p)->lEnde);
	TX_ASSERT( NULL != ((BAUWERKE *)p)->pcGewaesserNr);
	TX_ASSERT( NULL != *(((BAUWERKE *)p)->pcGewaesserNr));

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocProt ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf (pT," Bauwerke(Struktur) von Gewässerkataster : \n\tGew %s  Zuo %d Bez %s Beginn %ld Ende %ld Ident %ld\n\n",p->pcGewaesserNr,p->iIdentNrZuordnung,p->pcBauwerksBezeichnung,p->lBeginn,p->lEnde,p->lObjectIdent);
			KompaktProtokoll ( pLocProt,pT);
			DELETE_OBJ(pT);
		}
	}

try {

	CEierUhr Wait (g_pTE->MVWind());

// Neu
//	KPTree *pGew = (KPTree *) dwData;

	KPTree *pGew = ((BAUWERKSINPUT *) dwData) ->pGew;
	TR_OCLTree *pIdent = ((BAUWERKSINPUT *) dwData) ->pIdent;
	((BAUWERKSINPUT *) dwData) ->lCount++;

	if ( !pIdent || !pGew) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);

		return false;
	}
	
	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = p->pcGewaesserNr;
	GW.pcGewaesserName = NULL;
	GW.lBeginn = p->lBeginn;
	GW.lEnde = p->lEnde;

	KOMPAKTDATEN KD;
	if (!BauwerkeInKompakt (p, &KD)){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);

		return true;
	}

	CTable d( *pIdent);

	long lIdent = KompaktIdentifikator(NULL,cBauwerkeIdent ,p->iIdentNrZuordnung);
	if ( 0L == lIdent) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);
		return true;
	}


	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheEinzelBauwerke;


	OBJEKTKLASSENTYP OT;
	OT.lONr = -1L;
	OT.iTyp = OTLinie | OTPunkt;
//	OT.lMCode = DEX_GetObjNameMCode(lIdent);
	OT.lMCode = ((CKompiasExtension *)g_pTE)->KPHeader()->CodeGewNr();
	OT.pMWert = p->pcGewaesserNr;

	if ( !d.Find ( &lIdent )) {
		TR_OBJTree *pObj = new TR_OBJTree;
		if ( !pObj)
			return true;

		OT.pOBJ = pObj;
		ELK.eKey = lIdent;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);

		long MCode = 0L;
		TR_OCLCreator TRCr ( *pIdent);
		ContCreate ( TRCr, TR_OCL) ( lIdent, MCode,OC_ANLEGEN, pObj);
	} else {
		TR_OCLLock f(d);
		TR_OBJTree *pObj = f->OBJ();
		OT.pOBJ = pObj;
		ELK.eKey = lIdent;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);
	}


	CTable t( *pGew);
	if ( !t.Find ( p->pcGewaesserNr)) {
		KP_LATree *pLA = new KP_LATree;
		if (!pLA)
			return false;
		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( 1, &KD);
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (&GW, pLA);
	} else {
		KP_GEWLock l(t);
		KP_LATree *pLA = l->LA();
		if (!pLA)
			return false;
		long lCount = (long) pLA->Count() + 1;
		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( lCount, &KD);
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}

	return true;

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeGewaesser( GEWAESSER *p, DWORD dwData)
{
if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK);
	return false;
}


	TX_ASSERT(NULL != p);
	TX_ASSERT(sizeof(GEWAESSER) == ((GEWAESSER *)p)->dwSize);
	TX_ASSERT(TIsValidAddress(p, sizeof(GEWAESSER), false)); // nur lesbar
//	TX_ASSERT( 0L <= ((GEWAESSER *)p)->lBeginn);
	TX_ASSERT( ((GEWAESSER *)p)->lEnde > ((GEWAESSER *)p)->lBeginn);
//	TX_ASSERT( 0L < ((GEWAESSER *)p)->lEnde);
	TX_ASSERT( NULL != ((GEWAESSER *)p)->pcGewaesserNr);
	TX_ASSERT( NULL != *(((GEWAESSER *)p)->pcGewaesserNr));



try {

	CEierUhr Wait (g_pTE->MVWind());
	KPTree *pGew = (KPTree *) dwData;
	if ( !pGew){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWANALYSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK);

		return false;
	}


	CTable t( *pGew);
	if ( !t.Find ( p->pcGewaesserNr)) {
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (p, NULL);
	} else {
		KP_GEWLock l(t);
		l->AddCountKompakt();
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWANALYSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}

	return true;
}
///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasBauwerke( KOMPAKTBAUWERKEPROC pFct, DWORD dwData)
{
if ( !pFct) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	return false;
}


//-----geplant : DWORD mein THIS

CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}


CKompiasExtension *pK = ( CKompiasExtension *)dwData;

try {


	pK->HoleBauwerkeVonTRiAS();
	TR_OBJTree *pBauw = pK->Bauwerke();

	if ( !pBauw) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_NOTRIASBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
	}


// KK010918
	long lGlobalBW = pK->GetGlobalBW();
	long lGlobalGW = pK->GetGlobalGW();
	
	
	CTable t( *pBauw);

	BAUWERKE BW;
   	memset (&BW,'\0',sizeof(BAUWERKE));
	BW.dwSize = sizeof(BAUWERKE);

	short iTyp = 0;
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OBJLock l(t);
		if ( !l)
			continue;


		BW.pcGewaesserNr = l->GewNr();

		if (BW.pcGewaesserNr == NULL || *BW.pcGewaesserNr == '\0')
			continue;

		BW.pcBauwerksBezeichnung = l->Bez();
		BW.pcBezeichner1 = l->Bez();
		BW.pcBezeichner2 = l->GewName();	// hier Bauwerksname
		BW.lRechts = l->Rechts();
		BW.lHoch = l->Hoch();
		BW.lBeginn = l->Von();
		BW.lEnde = l->Bis();
		BW.iIdentNrZuordnung = l->Typ();
//		BW.lObjectIdent = l->Object();
		BW.lObjectIdent = l->ObjectIdent();
		
		lGlobalGW++;

		bool flag = true;
		iTyp++;
		try {
			char * pM = new char [_MAX_PATH];
			if ( pM) {
				wsprintf (pM,"\t Bauwerke an Gewässerkataster :\n\t Obj %ld : Bez. %s Gew %s von %ld bis %ld Zuo %d Ident %ld\n",
				l->Object(),
				BW.pcBauwerksBezeichnung,
				BW.pcGewaesserNr,
				BW.lBeginn,
				BW.lEnde,
				BW.iIdentNrZuordnung,
				BW.lObjectIdent);

				KompaktProtokoll ( pK->KompaktProtokollPointer(),pM);

				DELETE_OBJ(pM);
			}

	//	Maltes Verzweiflung

			KOMPAKTMALTEPROC pFcn = (KOMPAKTMALTEPROC ) pK->KompaktDLL()->GetProcAddress("BauwerkImKatasterEintragen");

			TX_ASSERT(NULL != pFcn);

			long lRefIdent = BW.lObjectIdent;

			if (pFcn) 
				pFcn( &BW );
			

//			flag = pFct ( iTyp,&BW,dwData);

			if ( lRefIdent != BW.lObjectIdent )
			
				SetzeBauwerkeIdent(l->Object(),BW.lObjectIdent);

			lGlobalBW++;

			if ( !flag ) 
				break;
		} catch ( ... ) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOBAUWERKE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			pK->KompaktDLL()->SetOperation(false);	// Malte umgehen
			return false;
		}

		pK->SetGlobalBW(lGlobalBW);
		pK->SetGlobalGW(lGlobalGW);


	}


} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOBAUWERKE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		pK->KompaktDLL()->SetOperation(false);	// Malte umgehen
		return false;
}


	return true;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasFlaechen( KOMPAKTFLAECHENPROC pFct, DWORD dwData, LPSTR GewNr, short iTyp)
{
if ( !pFct) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	return false;
}


	if ( !GewNr || *GewNr == '\0'){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOGEWAESSER, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
	}

//-----geplant : DWORD mein THIS

CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}



	if ( !GewNr || *GewNr == '\0')
		return false;


	CEierUhr Wait (g_pTE->MVWind());

try {

	CKompiasExtension *pK = ( CKompiasExtension *)dwData;


	KPBTree *pGEB = new KPBTree;
	if ( !pGEB)
		return false;


// KK010919 - Löschen der Gew.def (TriasGewaesser verhindern)
	pK->ExtModifyUnRegisterNotification ();


	pK->HoleFlaechenVonTRiAS(GewNr,iTyp,pGEB);
	if ( pGEB->Count() == 0L) {
		MessageBox ( __hWndM,
//		 "Keine Flächen in der Graphik gefunden",
		 ResString (ResID(IDS_FINDNOAREA, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		MB_ICONSTOP);
		DELETE_OBJ  (pGEB)
		return false;
	}


	FLAECHENANABSCHNITTEN FA;
   	memset (&FA,'\0',sizeof(FLAECHENANABSCHNITTEN));
	FA.dwSize = sizeof(FLAECHENANABSCHNITTEN);
	FA.pcGewaesserNr = GewNr;

	CTable t(*pGEB);
	for ( t.First();t.Valid();t.Next()) {
		KP_GEBLock l(t);
		if ( !l)
			continue;
	   	memset (&FA,'\0',sizeof(FLAECHENANABSCHNITTEN));
		FA.dwSize = sizeof(FLAECHENANABSCHNITTEN);
		FA.pcGewaesserNr = GewNr;
		FA.iIdentNr =l->IdentNr();
		FA.iLinksRechtsBeide = l->LRBeide();
		FA.dQuadratMeter = l->Flaeche();
		FA.lBeginn = l->Beginn();
		FA.lEnde = l->Ende();
		FA.pObjektKlasse = l->ObjKlasse();
		FA.pObjektBezeichnung = l->ObjBez();

		short iTyp = 0;
		try {
			bool flag = pFct ( iTyp,&FA,dwData);
		} catch ( ... ) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOFLAECHEN, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			return false;

		}
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOFLAECHEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}

	return true;
}
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  HoleKoordinaten( HWND hWnd, KOORDINATEN *p, DWORD dwData)
{

p->lError = 0L;

if ( !p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	p->lError = cFehlerhafteDaten;
	return false;
}

if (p->lIdent == 0L){
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	p->lError = cFehlerhafteDaten;
	return false;
}
	
if (strlen(p->pcRechtsWert) < 7L){
	MessageBox (__hWndM, 
//	 " Feld für Rechtswert kleiner 7 ",
	 ResString (ResID(IDS_ERRRECHTSWERT, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);

	if (strlen(p->pcHochWert) < 7L){
		MessageBox (__hWndM, 
//		 " Feld für Hochwert kleiner 7 ",
		 ResString (ResID(IDS_ERRHOCHWERT, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		return false;
	}
}


CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		DELETE_OBJ  ( pT);
		return false;
}



try {

	TX_ASSERT(NULL != p);
	TX_ASSERT(0L <= p->lIdent);


	CKompiasExtension *pK = ( CKompiasExtension *)dwData;

//	lIdent auswerten :

	if ( p->lIdent < lfctGibKoordSystem || p->lIdent > lfctGibStation) {
		p->lError = cKoordinatenAnfrageFalsch;
		return false;
	}

	pK->HoleKoordinatenVonTRiAS(hWnd,p);


	if ( p->lError != 0L) {

	/*------------------------
		char *pText = new char [_MAX_PATH];
		if ( pText) {
			*pText = '\0';
			strcat ( pText," Fehler : ");
			if ( p->lError == cGewaesserNummerFalsch)
				strcat ( pText ,"Gew.Nr falsch");

			if ( p->lError == cGewaesserZuKurz)
				strcat ( pText, "Gew zu kurz");

			if ( p->lError == cGewaesserZuLang )
				strcat ( pText," GewNr zu lang");

			if ( p->lError == cKoordinatenFalsch)
				strcat (pText,"Koordinate falsch");

			if ( p->lError == cStationFalsch)
				strcat (pText, "Station falsch ");

			if ( p->lError == cMultiGewaesser)
				strcat ( pText, "Multigewässer");

			if ( p->lError == cKoordinatenAnfrageFalsch)
				strcat (pText, " Koordinatenanfrage falsch !");

			if ( p->lError == cGewaesserNichtVorhanden)
				strcat ( pText, " Gewässer nicht vorhanden !");

			if ( p->lError == cFehlerhafteDaten)
				strcat ( pText, " Fehlerhafte Daten !");
			MessageBox (__hWndM, 
			 pText,
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);

			DELETE_OBJ  (pText);
		}
---------------------------------------------------------*/
		
		return false;
	}

} catch (...) {

		p->lError = cKoordinatenAnfrageFalsch;

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOKOORDINATEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;

}


	return true;
}
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  ZeigeTopKarteExt ( HWND hWnd, KOORDINATEN *p, DWORD dwData,short BWIdent,long ObjectIdent)
{

	p->lError = 0L;

	if (!p) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		return false ;
	}



	CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
	char *pT = pKK->FSTest();

	if ( pT && *pT != '\0') {
		if ( strcmp ( pT,"Meine Extension") != 0){
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			p->lError = cFehlerhafteDaten;
			DELETE_OBJ  ( pT);
			return false;
		}

		DELETE_OBJ  (pT);
	} else {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			p->lError = cFehlerhafteDaten;
			DELETE_OBJ  ( pT);
			return false;
	}


	try {


		CKompiasExtension *pK = ( CKompiasExtension *)dwData;
		pK->ZeigeBauwerkVonTRiAS(hWnd,p,BWIdent,ObjectIdent);


	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOKOORDINATEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		return false;

	}

	return true;
}

//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  ZeigeTopKarte ( HWND hWnd, KOORDINATEN *p, DWORD dwData)
{

p->lError = 0L;

if (!p) {
	MessageBox (__hWndM, 
	 ResString (ResID(IDS_ERRKPNODATEN, &g_pTE->RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
	 MB_OK|MB_ICONHAND);
	p->lError = cFehlerhafteDaten;
	return false ;
}



CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		DELETE_OBJ  ( pT);
		return false;
}


	try {


		CKompiasExtension *pK = ( CKompiasExtension *)dwData;

		pK->ZeigeObjektVonTRiAS(hWnd,p);

	} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOKOORDINATEN, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;
		return false;

	}

	return true;
}

//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasGewaesser( KOMPAKTGEWAESSERPROC pFct, DWORD dwData)
{

if ( !pFct) {

}
//-----geplant : DWORD mein THIS

CKompiasExtension *pKK = ( CKompiasExtension *)dwData;
char *pT = pKK->FSTest();

if ( pT && *pT != '\0') {
	if ( strcmp ( pT,"Meine Extension") != 0){
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
	}

	DELETE_OBJ  (pT);
} else {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOADRESSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		DELETE_OBJ  ( pT);
		return false;
}

try {

	CKompiasExtension *pK = ( CKompiasExtension *)dwData;

	pK->HoleGewaesserVonTRiAS();
	KPTree *pGew = pK->Gewaesser();

	if ( !pGew)
		return false;

	CTable t( *pGew);
	GEWAESSER GW;
   	memset (&GW,'\0',sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);

	short iTyp = 0;
	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if ( !l)
			continue;
		GW.pcGewaesserNr = l->GewNr();
		GW.lBeginn = l->Beginn();
		GW.lEnde = l->Ende();
		bool flag = true;
		iTyp++;
		try {
			flag = pFct ( iTyp,&GW,dwData);
			if ( !flag ) {
				return true;
			}
		} catch ( ... ) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOGEWANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			return false;

		}
	}

} catch (...) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWANALYSE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		return false;
}


	return true;
}
//---------------------------------------------------------------------
//-----------------------------------------------------------------
extern "C"
bool _XTENSN_EXPORT PASCAL  THoleKatalogProc ( char *pKurz, char *pLang, DWORD dwData)
{
		ListBox *p = (ListBox *)dwData;
		char *outBuff = new char [_MAX_PATH];
		*outBuff = '\0';
		strcat ( outBuff,pKurz);
		strcat (outBuff,":");
		strcat (outBuff, pLang);
//		((ListBox *)dwData) -> AddString (outBuff);
		p -> AddString (outBuff);
		
		DELETE_OBJ(outBuff);

	return true;
}

//-----------------------------------------------------------------


////////////////////////////////////////////////////////////////////
/////////// KOMPDLL.CXX ///////////////////////////////////////////
