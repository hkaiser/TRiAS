// OpenNewPropertySheet.h : header file
//

#include "ConnectParams.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASOpenWizardPropExt);	// WTRiASOpenWizardPropExt
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs
DefineSmartInterface(TRiASAccessDatabase);		// WTRiASAccessDatabase

/////////////////////////////////////////////////////////////////////////////
// COpenNewPropertySheet

class COpenNewPropertySheet : 
	public CPropertySheet
{
	DECLARE_DYNAMIC(COpenNewPropertySheet)

// Construction
public:
	COpenNewPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COpenNewPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	HRESULT ReadDataServerParams (DWORD &rdwPos);
	HRESULT HandleConnectString();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenNewPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenNewPropertySheet();
	long CountAvailableDataServers();

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenNewPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	HRESULT CountAvailableDataServers (REFGUID rGuid, long &rlCount);
	HRESULT IsDataServerAvailable (LPCSTR pcProgID);

public:
// Parameter, die Page-übergreifend verfügbar sein müssen
	PROJECTOPENMODE m_rgOpenMode;	
	CREATEMODE m_rgCreateMode;
	DATASOURCEMODE m_rgDatasource;
	CConnectParams m_Params;

// support für zusätzliche Pages
	WTRiASOpenWizardPropExt m_ExtPages;
	WComposeStringPairs m_Pairs;

	PROJECTOPENMODE GetOpenMode() { return m_rgOpenMode; }
	CREATEMODE GetCreateMode() { return m_rgCreateMode; }
	DATASOURCEMODE GetDatasourceMode() { return m_rgDatasource; }
	CConnectParams *GetConnectParams() { return &m_Params; }
};

/////////////////////////////////////////////////////////////////////////////
