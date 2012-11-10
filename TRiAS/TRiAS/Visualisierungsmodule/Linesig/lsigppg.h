// TKPpg.h : Declaration of the CLinesigPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CLinesigPropPage : See TKPpg.cpp for implementation.

class CLinesigPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CLinesigPropPage)
	DECLARE_OLECREATE_EX(CLinesigPropPage)

// Constructor
public:
	CLinesigPropPage();

// Dialog Data
	//{{AFX_DATA(CLinesigPropPage)
	enum { IDD = IDD_PROPPAGE_LINESIG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CLinesigPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
