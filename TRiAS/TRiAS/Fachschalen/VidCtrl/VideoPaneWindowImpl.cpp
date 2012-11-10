// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.06.2002 09:13:44 
//
// @doc
// @module VideoPaneWindowImpl.cpp | Definition of the <c CVideoPaneWindowImpl> class

#include "stdafx.h"
#include "VidCtrl.h"

#include <SidManageTabs.h>
#include <Com/ComBool.h>

#include "VideoPaneCallback.h"
#include "VideoPaneWindowImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(ServiceProvider);
DefineSmartInterface(ManageTabWindows);

//////////////////////////////////////////////////////////////////////////
// CVideoPaneWindowImpl

// Constructor
CVideoPaneWindowImpl::CVideoPaneWindowImpl() :
	m_hIcon(NULL), m_rgLayoutType(LAYOUTTYPE_Middle)
{
}

// Destructor
CVideoPaneWindowImpl::~CVideoPaneWindowImpl()
{
}

///////////////////////////////////////////////////////////////////////////////
// Verwalten des Fensters im Dockingbereich
/*static*/
HRESULT CVideoPaneWindowImpl::RegisterTabWindow(CVidCtrlExtension *pXtsn)
{
	_ASSERTE(NULL != pXtsn);
	COM_TRY {
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		if (SUCCEEDED(pXtsn -> GetXtensionSite(Site.ppi())) &&
			SUCCEEDED(Site -> QueryInterface(SP.ppi())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageVideoTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		CComObject<CVideoPaneCallback> *pValuesCB = NULL;

			THROW_FAILED_HRESULT(CComObject<CVideoPaneCallback>::CreateInstance(&pValuesCB));

		WUnknown Unk (pValuesCB -> GetUnknown());		// pending AddRef
		CComBSTR bstrValues;
		
			bstrValues.LoadString(IDS_VIDEOPANE);
			pValuesCB -> SetCmdTarget (pXtsn);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindowDelayed(bstrValues, pValuesCB));
		}
	} COM_CATCH;
	return S_OK;
}

/*static*/
CVideoPaneWindowImpl *CVideoPaneWindowImpl::CreateInstance(CVidCtrlExtension *pXtsn) 
{
CVideoPaneWindowImpl *pClient = NULL;

	_ASSERTE(NULL != pXtsn);
	COM_TRY {
	// ProjectValueFenster erzeugen
	CWaitCursor Wait;

	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		if (SUCCEEDED(pXtsn -> GetXtensionSite(Site.ppi())) &&
			SUCCEEDED(Site -> QueryInterface(SP.ppi())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageVideoTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgt im DockingTab
		INT_PTR hHandle = NULL;
		CComBSTR bstrValues;
		
			bstrValues.LoadString(IDS_VIDEOPANE);
			pClient = new CVideoPaneWindowImpl();

		INT_PTR hParent = NULL;

			THROW_FAILED_HRESULT(Tabs -> get_ParentWindow(&hParent));

		HWND hWnd = pClient -> Create(reinterpret_cast<HWND>(hParent));

			_ASSERTE(NULL != hWnd);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindow(reinterpret_cast<INT_PTR>(hWnd), bstrValues, pClient -> GetIcon(), &hHandle));
			_ASSERTE(reinterpret_cast<HWND>(hHandle) == HWND(*pClient));

			THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

		// ggf. Tabfenster anzeigen
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (!fVisible)
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));
		}
	} COM_CATCH_RETURN(NULL);
	return pClient;
}

bool CVideoPaneWindowImpl::ReShow(CVidCtrlExtension *pXtsn)
{
	COM_TRY {
	// Projektfenster wieder anzeigen
	CWaitCursor Wait;

	// ProjektStatistics muß im DockingFenster angezeigt sein
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(pXtsn -> GetXtensionSite(Site.ppi()));
		THROW_FAILED_HRESULT(Site -> QueryInterface(SP.ppi()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageVideoTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

	INT_PTR hHandle = NULL;
	CComBSTR bstrValues;
	
		bstrValues.LoadString(IDS_VIDEOPANE);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(bstrValues, &hHandle));
		THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

	// ggf. Tabfenster anzeigen
#if defined(_DEBUG)
	CComBool fVisible;

		THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
		_ASSERTE(!fVisible);
#endif // defined(_DEBUG)
		THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));

	} COM_CATCH_RETURN(false);
	return true;
}

void CVideoPaneWindowImpl::DeleteInstance(CVidCtrlExtension *pXtsn, CVideoPaneWindowImpl *& pValues)
{
	COM_TRY {
	// ProjektStatistics muß im DockingFenster angezeigt sein
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(pXtsn -> GetXtensionSite(Site.ppi()));
		THROW_FAILED_HRESULT(Site -> QueryInterface(SP.ppi()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageVideoTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

		THROW_FAILED_HRESULT(Tabs -> DeleteTabWindow(reinterpret_cast<INT_PTR>(HWND(*pValues))));

	// Fenster und Objekt zerlegen
		pValues -> DestroyWindow();
		DELETE_OBJ(pValues);

	// ggf. TabFenster ausblenden (wenns die letzte TabLasche war)
	int iCount = 0;

		THROW_FAILED_HRESULT(Tabs -> get_Count(&iCount));
		if (0 == iCount) {
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (fVisible) 
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_FALSE));
		}
	} COM_CATCH_NORETURN;
}

bool CVideoPaneWindowImpl::EnsureIcon()
{
	if (NULL == m_hIcon) {
		m_hIcon = AtlLoadIcon(IDI_VIDEOPANE);
		_ASSERTE(NULL != m_hIcon);
	}
	return (NULL != m_hIcon) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Messagehandlers
LRESULT CVideoPaneWindowImpl::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
// Attach controls
	m_axLeft.Attach(GetDlgItem(IDC_LEFTCHANNEL));
	m_axMiddle.Attach(GetDlgItem(IDC_MIDDLECHANNEL));
	m_axRight.Attach(GetDlgItem(IDC_RIGHTCHANNEL));

	AtlAdviseSinkMap(this, true);

	SetMsgHandled(FALSE);
	return TRUE;
}

void CVideoPaneWindowImpl::OnDestroy()
{
	AtlAdviseSinkMap(this, false);
	SetMsgHandled(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
// AutoResize initialisieren
const UINT CVideoPaneWindowImpl::_controlsToClip[] = 
{
	IDC_LEFTCHANNEL,
	IDC_MIDDLECHANNEL,
	IDC_RIGHTCHANNEL,
};

void CVideoPaneWindowImpl::DefineLayout()
{
	RepositionLayout(m_rgLayoutType);
	DefineLayout(m_rgLayoutType);
}

namespace {
// Daten für die Positionierung der Controls
	typedef LayoutMgr<CVideoPaneWindowImpl> LM;
	typedef struct tagLAYOUTDATA {
		UINT uiID;
		LM::Side rgSide;
		int nPos;
	} LAYOUTDATA;
	
	const LAYOUTDATA g_ldLeft[] = {
		{ IDC_LEFTCHANNEL, LM::ATTACH_TOP, 1 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_BOTTOM, 21 },

		{ IDC_LEFTCHANNEL, LM::ATTACH_LEFT, 1 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_RIGHT, 11 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_LEFT, 12 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_RIGHT, 17 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_LEFT, 18 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_RIGHT, 23 },
	};
	
	const LAYOUTDATA g_ldMiddle[] = {
		{ IDC_MIDDLECHANNEL, LM::ATTACH_TOP, 1 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_BOTTOM, 21 },

		{ IDC_LEFTCHANNEL, LM::ATTACH_LEFT, 1 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_RIGHT, 6 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_LEFT, 7 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_RIGHT, 17 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_LEFT, 18 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_RIGHT, 23 },
	};

	const LAYOUTDATA g_ldRight[] = {
		{ IDC_RIGHTCHANNEL, LM::ATTACH_TOP, 1 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_BOTTOM, 21 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_TOP, 11 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_BOTTOM, 21 },

		{ IDC_LEFTCHANNEL, LM::ATTACH_LEFT, 1 },
		{ IDC_LEFTCHANNEL, LM::ATTACH_RIGHT, 6 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_LEFT, 7 },
		{ IDC_MIDDLECHANNEL, LM::ATTACH_RIGHT, 12 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_LEFT, 13 },
		{ IDC_RIGHTCHANNEL, LM::ATTACH_RIGHT, 23 },
	};

///////////////////////////////////////////////////////////////////////////////
// Größeninformationen
	typedef struct tagSIZEDATA {
		UINT uiID;
		int nPosLeft;
		int nPosRight;
		int nPosTop;
		int nPosBottom;
	} SIZEDATA;

	const SIZEDATA g_sdLeft[] = {
		{ IDC_LEFTCHANNEL, 1, 11, 1, 21 },
		{ IDC_MIDDLECHANNEL, 12, 17, 11, 21 },
		{ IDC_RIGHTCHANNEL, 18, 23, 11, 21 },
	};

	const SIZEDATA g_sdMiddle[] = {
		{ IDC_LEFTCHANNEL, 1, 6, 11, 21 },
		{ IDC_MIDDLECHANNEL, 7, 17, 1, 21 },
		{ IDC_RIGHTCHANNEL, 18, 23, 11, 21 },
	};

	const SIZEDATA g_sdRight[] = {
		{ IDC_LEFTCHANNEL, 1, 6, 11, 21 },
		{ IDC_MIDDLECHANNEL, 7, 12, 11, 21 },
		{ IDC_RIGHTCHANNEL, 13, 23, 1, 21 },
	};

	const int nPosX = 24;
	const int nPosY = 22;
}

void CVideoPaneWindowImpl::DefineLayout(LAYOUTTYPE rgLayoutType)
{
	SetNPositionsX(nPosX);
	SetNPositionsY(nPosY);

	switch (rgLayoutType) {
	case LAYOUTTYPE_Left:
		{
			for (int i = 0; i < _countof(g_ldLeft); ++i) {
			LAYOUTDATA const &rLD = g_ldLeft[i];

				AttachPosition(rLD.uiID, rLD.rgSide, rLD.nPos);
			}
		}
		break;

	default:
	case LAYOUTTYPE_Middle:
		{
			for (int i = 0; i < _countof(g_ldMiddle); ++i) {
			LAYOUTDATA const &rLD = g_ldMiddle[i];

				AttachPosition(rLD.uiID, rLD.rgSide, rLD.nPos);
			}
		}
		break;

	case LAYOUTTYPE_Right:
		{
			for (int i = 0; i < _countof(g_ldRight); ++i) {
			LAYOUTDATA const &rLD = g_ldRight[i];

				AttachPosition(rLD.uiID, rLD.rgSide, rLD.nPos);
			}
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Neupositionierung der Controls
void CVideoPaneWindowImpl::RecalcLayout(LAYOUTTYPE rgLayoutType)
{
	if (rgLayoutType != m_rgLayoutType) {
	// Controls neu positionieren
		RepositionLayout(rgLayoutType);

	// neues Layout einstellen
		DefineLayout(rgLayoutType);
		if (ComputeLayout())
			DoLayout();

		m_rgLayoutType = rgLayoutType;
	}
}

void CVideoPaneWindowImpl::RepositionLayout(LAYOUTTYPE rgLayoutType)
{
	_ASSERTE(_countof(g_sdLeft) == _countof(g_sdMiddle));
	_ASSERTE(_countof(g_sdLeft) == _countof(g_sdRight));

HDWP hdwp = ::BeginDeferWindowPos(_countof(g_sdLeft));
CRect rcClient;

	GetClientRect(rcClient);
	switch (rgLayoutType) {
	case LAYOUTTYPE_Left:
		{
			for (int i = 0; i < _countof(g_sdLeft); ++i) {
			SIZEDATA const &rSD = g_sdLeft[i];
			CRect rc;
			
				rc.left = (rcClient.Width() * rSD.nPosLeft) / nPosX;
				rc.right = (rcClient.Width() * rSD.nPosRight) / nPosX;	
				rc.top = (rcClient.Height() * rSD.nPosTop) / nPosY;
				rc.bottom = (rcClient.Height() * rSD.nPosBottom) / nPosY;
				::DeferWindowPos(hdwp, GetDlgItem(rSD.uiID), NULL, 
					rc.left, rc.top, rc.Width(), rc.Height(),
					SWP_NOZORDER|SWP_NOREDRAW);
			}
		}
		break;

	default:
	case LAYOUTTYPE_Middle:
		{
			for (int i = 0; i < _countof(g_sdMiddle); ++i) {
			SIZEDATA const &rSD = g_sdMiddle[i];
			CRect rc;
			
				rc.left = (rcClient.Width() * rSD.nPosLeft) / nPosX;
				rc.right = (rcClient.Width() * rSD.nPosRight) / nPosX;	
				rc.top = (rcClient.Height() * rSD.nPosTop) / nPosY;
				rc.bottom = (rcClient.Height() * rSD.nPosBottom) / nPosY;
				::DeferWindowPos(hdwp, GetDlgItem(rSD.uiID), NULL, 
					rc.left, rc.top, rc.Width(), rc.Height(),
					SWP_NOZORDER|SWP_NOREDRAW);
			}
		}
		break;

	case LAYOUTTYPE_Right:
		{
			for (int i = 0; i < _countof(g_sdRight); ++i) {
			SIZEDATA const &rSD = g_sdRight[i];
			CRect rc;
			
				rc.left = (rcClient.Width() * rSD.nPosLeft) / nPosX;
				rc.right = (rcClient.Width() * rSD.nPosRight) / nPosX;	
				rc.top = (rcClient.Height() * rSD.nPosTop) / nPosY;
				rc.bottom = (rcClient.Height() * rSD.nPosBottom) / nPosY;
				::DeferWindowPos(hdwp, GetDlgItem(rSD.uiID), NULL, 
					rc.left, rc.top, rc.Width(), rc.Height(),
					SWP_NOZORDER|SWP_NOREDRAW);
			}
		}
		break;
	}

	::EndDeferWindowPos(hdwp);
	Invalidate();
}

///////////////////////////////////////////////////////////////////////////////
// ActiveX Events
void CVideoPaneWindowImpl::OnLeftMouseUp(short iButton, short iShiftState, 
	OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	if (WMP_BUTTON_LEFT == iButton)
		RecalcLayout(LAYOUTTYPE_Left);
}

void CVideoPaneWindowImpl::OnMiddleMouseUp(short iButton, short iShiftState, 
	OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	if (WMP_BUTTON_LEFT == iButton)
		RecalcLayout(LAYOUTTYPE_Middle);
}

void CVideoPaneWindowImpl::OnRightMouseUp(short iButton, short iShiftState, 
	OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	if (WMP_BUTTON_LEFT == iButton)
		RecalcLayout(LAYOUTTYPE_Right);
}

