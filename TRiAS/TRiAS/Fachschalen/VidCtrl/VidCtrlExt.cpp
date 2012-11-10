// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.06.2002 16:35:25
//
// @doc
// @module VidCtrl.cpp | Implementation of the <c CVidCtrlExtension> class

#include "stdafx.h"

#include "VidCtrl.h"
#include "VidCtrlExt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TriasXtensionSite);

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules VidCtrl
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_VidCtrl;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVidCtrlExtension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CVidCtrlExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

	RegisterNotification (DEX_N_PROJECTTOCLOSE);
	RegisterNotification (WM_MOUSEMOVE, false);

	CVideoPaneWindowImpl::RegisterTabWindow(this);
	InitToolbar();
	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CVidCtrlExtension::UnLoadExtension (void)
{
	UnRegisterNotification (WM_MOUSEMOVE, false);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);

	FreeToolbar();
	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// Notifikationen behandeln
STDMETHODIMP_(LRESULT) CVidCtrlExtension::Notification (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEX_N_PROJECTTOCLOSE:
		OnProjectToClose();
		break;
	}
	return CTriasExtension::Notification (wParam, lParam);
}

HRESULT CVidCtrlExtension::OnProjectToClose()
{
	FreeBar();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Systemnotifikationen behandeln
STDMETHODIMP_(LRESULT) CVidCtrlExtension::WindowsNotification (UINT wMsg, 
	WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_MOUSEMOVE:
		OnMouseMove (CPoint(LOWORD(lParam), HIWORD(lParam)));
		break;

	default:
		_ASSERTE(FALSE);
		break;	
	}
	return false;
}

void CVidCtrlExtension::OnMouseMove(CPoint ptScreen)
{
}

///////////////////////////////////////////////////////////////////////////////
// Docking support
bool CVidCtrlExtension::CreateBar()
{
	_ASSERTE(NULL == m_pVideoPane);
	m_pVideoPane = CVideoPaneWindowImpl::CreateInstance(this);
	if (NULL == m_pVideoPane) 
		return false;
		
	ShowTurtle();
	return true;
}

bool CVidCtrlExtension::ShowBar()
{
	_ASSERTE(NULL != m_pVideoPane);
	m_pVideoPane -> ReShow(this);
	ShowTurtle();
	return true;
}

bool CVidCtrlExtension::FreeBar()
{
	if (NULL != m_pVideoPane) {
	// Turtle ausblenden
		HideTurtle();

	// Rekursion verhindern
	CVideoPaneWindowImpl *pProjBar = m_pVideoPane;

		m_pVideoPane = NULL;
		CVideoPaneWindowImpl::DeleteInstance(this, pProjBar);
		_ASSERTE(NULL == pProjBar);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Support für Positionskreuz
HRESULT CVidCtrlExtension::ShowTurtle()
{
	if (!m_Turtle.IsValid()) {
	WTriasXtensionSite Site;

		RETURN_FAILED_HRESULT(m_Turtle.CreateInstance(CLSID_HotSpot));
		RETURN_FAILED_HRESULT(GetXtensionSite(Site.ppi()));
		RETURN_FAILED_HRESULT(m_Turtle->SetExtensionSite(Site));
		RETURN_FAILED_HRESULT(m_Turtle->RePaint());
	}
	return S_OK;
}

HRESULT CVidCtrlExtension::HideTurtle()
{
	if (m_Turtle.IsValid()) {
		RETURN_FAILED_HRESULT(m_Turtle->DisconnectFromServer());
		m_Turtle.Assign(NULL);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IVideoControl
STDMETHODIMP CVidCtrlExtension::TrackObject(INT_PTR hObject)
{
	// TODO: Add your implementation code here

	return S_OK;
}
