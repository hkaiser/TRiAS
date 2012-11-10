// StatPage.cpp: GeoDB Statistik als PropPage anzeigen

#include "statistp.hxx"

#include <shlobj.h>
#include <ixtnext.hxx>
#include <xtsnguid.h>

#include "geosguid.h" 

#include "geostatr.h"		// ResourceKonstanten
#include "statpage.h"

///////////////////////////////////////////////////////////////////////////////
// required ATL stuff
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_StatistikPropPage, CStatistikPageExt)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap für Initialisierung etc. liefern
}

///////////////////////////////////////////////////////////////////////////////
// PropSheetExtDialog 
#pragma warning (disable: 4355)		// this used in constructor

CStatistikPage::CStatistikPage (ResID uiID, LPCSTR pcCaption)
			: CPropertyPage (uiID, pcCaption),
			  m_ftObjCnt (this, IDC_OBJECTCOUNT),
			  m_ftClsCnt (this, IDC_CLASSCOUNT),
			  m_ftViewCnt (this, IDC_VIEWCOUNT),
			  m_ftName (this, IDC_PROJECTNAME)
{
// Bei ProertyPages müssen alle Controls explizit erst in WindowInit initialisiert
// werden (s.u.). Hier also nicht auf selbige zugreifen!
}

#pragma warning (default: 4355)

CStatistikPage::~CStatistikPage (void)
{
}

void CStatistikPage::WindowInit (Event)
{
// Controls initialisieren
	m_ftObjCnt.FInit();
	m_ftClsCnt.FInit();
	m_ftViewCnt.FInit();
	m_ftName.FInit();

// Informationen besorgen und Anzeigen
char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetActiveProject (cbBuffer)) {
		m_ftName.SetText (cbBuffer);

		ltoa (DEX_GetObjectCount(), cbBuffer, 10);
		m_ftObjCnt.SetText (cbBuffer);
		ltoa (DEX_GetClassCount(), cbBuffer, 10);
		m_ftClsCnt.SetText (cbBuffer);
		ltoa (DEX_GetViewCount(), cbBuffer, 10);
		m_ftViewCnt.SetText (cbBuffer);
	}
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheetExtension
// Konstruktor/Destruktor/Initialisierung
CStatistikPageExt::CStatistikPageExt (void)
{
	m_pDlgPage = NULL;
}

CStatistikPageExt::~CStatistikPageExt (void)
{
	DELETE_OBJ(m_pDlgPage);
}

///////////////////////////////////////////////////////////////////////////////
// *** ITriasExtInit methods 
// unser Objekt initialisieren
STDMETHODIMP CStatistikPageExt::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
// wenn unsere Erweiterung nicht geladen ist, dann wieder raus
	if (NULL == g_pTE || !g_pTE -> isLoaded())
		return E_FAIL;

// jetzt gehts wirklich los
	DELETE_OBJ(m_pDlgPage);		// für alle Fälle

// PropertyPage anlegen
	try {
	ResourceFile RF (g_pDLLName);
	ResString resCaption (ResID(IDS_STATPAGECAPTION, &RF), 128);

		m_pDlgPage = new CStatistikPage (ResID (IDD_STATISTIK_PAGE, &RF), resCaption);
	} catch (...) {
		return E_OUTOFMEMORY;		// Speicherfehler abfangen
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITriasPropSheetExt
// Page in Dialog einhängen
STDMETHODIMP CStatistikPageExt::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
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
STDMETHODIMP CStatistikPageExt::ReplacePage (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return E_NOTIMPL;
}

