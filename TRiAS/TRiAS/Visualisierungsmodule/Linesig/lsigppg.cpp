#include "stdafx.h"
#include "LinesigImpl.h"
#include "lsigppg.h"

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CLinesigPropPage, COlePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CLinesigPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CLinesigPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {E7EED71C-0567-11d0-AC39-00A024145748}
IMPLEMENT_OLECREATE_EX(CLinesigPropPage, "TRiAS.VMLinesigPPg.1",
	0xe7eed71c, 0x567, 0x11d0, 0xac, 0x39, 0x0, 0xa0, 0x24, 0x14, 0x57, 0x48);

/////////////////////////////////////////////////////////////////////////////
// CLinesigPropPage::CKartenPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CLinesigPropPage

BOOL CLinesigPropPage::CLinesigPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_LINESIG_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CLinesigPropPage::CLinesigPropPage - Constructor

CLinesigPropPage::CLinesigPropPage() :
	COlePropertyPage(IDD, IDS_LINESIG_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CLinesigPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CLinesigPropPage::DoDataExchange - Moves data between page and properties

void CLinesigPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CLinesigPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CLinesigPropPage message handlers
