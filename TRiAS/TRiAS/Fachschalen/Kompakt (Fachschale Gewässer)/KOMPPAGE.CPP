// KOMPPage.cpp: Gew_Kataster als PropPage anzeigen

#include "kompp.hxx"

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>
#include "kompguid.h"

#include <shlobj.h>
#include <ixtnext.hxx>
#include <xtsnguid.h>
#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>


#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompias.h"
#include "triasdef.h"
#include "kompdef.h"
#include "gewbaum.hxx"
#include "komphead.hxx"
#include "kompdll.hxx"
#include "kompgew.hxx"
#include "kompias.hxx"

#include "komppage.h"

///////////////////////////////////////////////////////////////////////////////
// required ATL stuff

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_KompaktPropPage, CKompaktPageExt)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap für Initialisierung etc. liefern
}

///////////////////////////////////////////////////////////////////////////////
// PropSheetExtDialog 
#pragma warning (disable: 4355)		// this used in constructor

CKompaktPage::CKompaktPage (ResID uiID, LPCSTR pcCaption)
			: CPropertyPage (uiID, pcCaption),
			  m_ftGewCnt (this, IDC_GEWAESSERCOUNT),
			  m_ftBauwCnt (this, IDC_BAUWERKECOUNT),
			  m_cbDefButton ( this, IDC_DEFBUTTON),
#if _MSC_VER >= 1100
			_DefQuelle( this,IDC_DATAQUELL),
#endif
			  m_ftName (this, IDC_PROJECTNAME),
			  m_ftVerband (this, IDC_VERBANDSNAME)
{
// Bei PropertyPages müssen alle Controls explizit erst in WindowInit initialisiert
// werden (s.u.). Hier also nicht auf selbige zugreifen!

}

#pragma warning (default: 4355)

CKompaktPage::~CKompaktPage (void)
{

}

void CKompaktPage::WindowInit (Event)
{


// Controls initialisieren
	m_ftGewCnt.FInit();
	m_ftBauwCnt.FInit();
	m_ftName.FInit();
	m_ftVerband.FInit();
	m_cbDefButton.FInit();

#if _MSC_VER >= 1100
	m_hPr = 0;
#endif
	InitMyPage();


}
///////////////////////////////////////////////////////////////////////////
void CKompaktPage :: InitMyPage(void)
{

	m_pKH = NULL;

#if _MSC_VER >= 1100
	m_hPr = 0;
#endif

	_isValid = false;

	CEierUhr Wait (g_pTE->MVWind());

//	m_pKH = ((CKompiasExtension *)g_pTE)->DeleteKPHeader();

	bool iFlag = false;

#if _MSC_VER >= 1100
	m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (m_hPr == 0 )	// Keine Datenquelle ausgewählt !!
		iFlag = true;
#endif


	if ( !m_pKH) {
		((CKompiasExtension *)g_pTE)->KatasterLaden(iFlag);
		m_pKH = ((CKompiasExtension *)g_pTE)->KPHeader();
		if (!m_pKH) {
			ResourceFile RF (g_pDLLName);
			ResString resCaption (ResID(IDS_KOMPAKTHEADER, &RF), 128);
			ResString resText (ResID(IDS_NOLOADKOMPAKTHEADER, &RF), 128);

			MessageBox (0,
			resText,
			resCaption,
			MB_ICONSTOP);
			return;
		}

	}


	_isValid = true;

	if ( !m_pKH->isValid()) {
		if (!((CKompiasExtension *)g_pTE)->KatasterAnlegen())
			return;
	}

	m_pKH->Aktualisieren (PM_GEWAESSER);
	m_pKH->Aktualisieren (PM_BAUWERKE);
	m_pKH->Aktualisieren (PM_HYDRAULIK);

// Informationen besorgen und Anzeigen
	char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetActiveProject (cbBuffer)) {
		m_ftName.SetText (cbBuffer);
		if ( m_pKH->Name (cbBuffer,sizeof(cbBuffer)))
			m_ftVerband.SetText (cbBuffer);

		ltoa (m_pKH->GewaesserCount(), cbBuffer, 10);
		m_ftGewCnt.SetText (cbBuffer);

		ltoa (m_pKH->BauwerkeCount(), cbBuffer, 10);
		m_ftBauwCnt.SetText (cbBuffer);
	}

	m_ftName.SetText(((CKompiasExtension *)g_pTE)->HoleKompaktDatenPfad());

}
///////////////////////////////////////////////////////////////////////////
void _XTENSN_EXPORT CKompaktPage :: ButtonClick (ControlEvt e)
{
	CEierUhr Wait (g_pTE->MVWind());

	switch ((unsigned int)e.GetControlID()) {

		case IDC_DEFBUTTON: 
		{


		if ( !_isValid)
			return;


		if (m_pKH) {
			CEierUhr Wait (g_pTE->MVWind());

			{

			ParameterEinstellung PE ( this ,PARAMETEREINSTELLUNG, g_pTE->RF(), m_pKH);

			PE.Show(); 
			if ( PE.Result() == 1 ) {
			// Informationen besorgen und Anzeigen
				char cbBuffer[_MAX_PATH];
				if ( m_pKH->Name (cbBuffer,sizeof(cbBuffer)))
					m_ftVerband.SetText (cbBuffer);
				if ( PE.isChanged()) {
					ltoa (m_pKH->GewaesserCount(), cbBuffer, 10);
					m_ftGewCnt.SetText (cbBuffer);
				}
			}

			}

		}

		}
		break;

		case IDC_DATAQUELL:
		{

#if _MSC_VER >= 1100
		if (((CKompiasExtension *)g_pTE)->DatenQuelleWechseln()) {
			m_pKH = ((CKompiasExtension *)g_pTE)->KPHeader();
			if (!m_pKH)
				InitMyPage();
		}
#endif

		}
		break;

	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheetExtension
// Konstruktor/Destruktor/Initialisierung
CKompaktPageExt::CKompaktPageExt (void)
{
	m_pDlgPage = NULL;
}

CKompaktPageExt::~CKompaktPageExt (void)
{
	DELETE_OBJ (m_pDlgPage);
}

///////////////////////////////////////////////////////////////////////////////
// *** ITriasExtInit methods 
// unser Objekt initialisieren
STDMETHODIMP CKompaktPageExt::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
// wenn unsere Erweiterung nicht geladen ist, dann wieder raus
	if (NULL == g_pTE || !g_pTE -> isLoaded())
		return E_FAIL;

// jetzt gehts wirklich los
	DELETE_OBJ (m_pDlgPage);		// für alle Fälle

// PropertyPage anlegen
	try {
	ResourceFile RF (g_pDLLName);

#if _MSC_VER >= 1100
	ResString resCaption (ResID(IDS_KOMPPAGECAPTIONX, &RF), 128);
		m_pDlgPage = new CKompaktPage (ResID (IDD_KOMPAKT_PAGEEX, &RF), resCaption);
#else
	ResString resCaption (ResID(IDS_KOMPPAGECAPTION, &RF), 128);
		m_pDlgPage = new CKompaktPage (ResID (IDD_KOMPAKT_PAGE, &RF), resCaption);
#endif
	} catch (...) {
		return E_OUTOFMEMORY;		// Speicherfehler abfangen
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITriasPropSheetExt
// Page in Dialog einhängen
STDMETHODIMP CKompaktPageExt::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
HPROPSHEETPAGE hPSP = NULL;

	if (NULL != m_pDlgPage) {					// SummaryPage einhängen
	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pDlgPage))
			return E_UNEXPECTED;

		return NOERROR;
	}

return E_UNEXPECTED;
}

// wird hier nicht benötigt
STDMETHODIMP CKompaktPageExt::ReplacePage (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return E_NOTIMPL;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//	KOMPPAGE.CPP
