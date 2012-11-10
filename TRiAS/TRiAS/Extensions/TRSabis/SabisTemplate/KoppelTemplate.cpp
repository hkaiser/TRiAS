// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 16.09.99 18:18:18
//
// @doc
// @module KoppelTemplate.cpp | Implementation of the <c CMainApplication> class

#include "stdafx.h"

#include <atlwin.h>
#include <Ospace/Com/ComErrorMacros.h>

#include "SabisTmplate.h"
#include "KoppelTemplate.h"

/////////////////////////////////////////////////////////////////////////////
// CMainApplication

STDMETHODIMP CMainApplication::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMainApplication,
		&IID_MainApplicationLink,
		&DIID___DLLApplicationLinkTarget,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// zu implementierendes Interface
//Private Function MainApplicationLink_OpenProject(ByVal Info As implUserInfo, _
//    ByVal ProjectFilename As String, ByVal LinkClient As GISLinkTarget) _
//    As ApplicationLinkTarget
//
//  'für Client as Zugriff
//    
//  Set MainApplicationLink_OpenProject = Nothing
//  If IsNothing(LinkClient) Then Exit Function
//  Set mSabisLink = New APPLink.DLLApplicationLinkTarget
//  If IsNothing(mSabisLink) Then Exit Function
//  With mSabisLink
//    .AppValue = App.ProductName
//    .AppFullname = FullName
//    .AppVersion = Version
//    Call .OnOpenDataProject(Info, ProjectFilename, LinkClient)
//  End With
//  If OpenData(ProjectFilename) Then
//    Set MainApplicationLink_OpenProject = mSabisLink
//  Else
//    If Not IsNothing(mSabisLink) Then
//      Call mSabisLink.CloseDataProject(False, True)
//    End If
//    Set mSabisLink = Nothing
//  End If
//End Function
STDMETHODIMP CMainApplication::OpenProject(
	implUserInfo *pInfo, BSTR ProjectFilename, GISLinkTarget *pLinkClient, ApplicationLinkTarget **ppTarget)
{
	TEST_OUT_PARAM(ppTarget);

// für Client as Zugriff
	if (NULL == pLinkClient)
		return S_OK;
  
	COM_TRY {
	_DLLApplicationLinkTargetPtr SabisLink;

		THROW_FAILED_HRESULT(SabisLink.CreateInstance (CLSID_DLLApplicationLinkTarget));
		THROW_FAILED_HRESULT(Connect (SabisLink));

		THROW_FAILED_HRESULT(SabisLink -> put_AppValue (CComBSTR("AppValue")));
		THROW_FAILED_HRESULT(SabisLink -> put_AppFullname (CComBSTR("AppFullName")));
		THROW_FAILED_HRESULT(SabisLink -> put_AppVersion (CComBSTR("AppVersion")));

	VARIANT_BOOL fOk = VARIANT_FALSE;		// dummy Parameter (return value)

		THROW_FAILED_HRESULT(SabisLink -> OnOpenDataProject (pInfo, ProjectFilename, pLinkClient, &fOk));

		if (OpenData (ProjectFilename)) {
			m_SabisLink = SabisLink;

		ApplicationLinkTargetPtr Target (SabisLink);

			*ppTarget = Target.Detach();	// implicit QueryInterface
		} 
		else {
			THROW_FAILED_HRESULT(Disconnect (SabisLink));
			THROW_FAILED_HRESULT(SabisLink -> CloseDataProject (VARIANT_FALSE, VARIANT_TRUE, &fOk));
		}

	} COM_CATCH_RETURN(S_OK);
	return S_OK;
}

//Private Function MainApplicationLink_CloseProject(ByVal DoAsk As Boolean, _
//    ByVal CleanUp As Boolean) As Boolean
//  'Dieser Ruf kommt immer von außen, vorsorglich für den Fehlerfall !!
//  Dim Ok As Boolean
//  
//  Call mSabisLink_CloseDataProject(DoAsk, CleanUp, Ok)
//  MainApplicationLink_CloseProject = Ok
//End Function
STDMETHODIMP CMainApplication::CloseProject(
	VARIANT_BOOL DoAsk, VARIANT_BOOL CleanUp, VARIANT_BOOL *pfOk)
{
	TEST_OUT_PARAM(pfOk);

// Dieser Ruf kommt immer von außen, vorsorglich für den Fehlerfall !!
	CloseDataProject(DoAsk, CleanUp, pfOk);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// zu implementierendes EventSink

//Private Sub mSabisLink_GetVisible(Status As Boolean)
//  Status = Mainform.Visible
//End Sub
void CMainApplication::GetVisible(VARIANT_BOOL* Status)
{
}

//Private Sub mSabisLink_LetVisible(ByVal DoShow As Boolean)
//  Mainform.Visible = DoShow
//End Sub
void CMainApplication::LetVisible(VARIANT_BOOL DoShow)
{
}

//Private Sub mSabisLink_ShowStatusText(ByVal AText As String)
//  With Mainform.Statuszeile
//    .Caption = AText
//    .Refresh
//  End With
//End Sub
void CMainApplication::ShowStatusText(BSTR AText)
{
}

//Private Sub mSabisLink_OpenDataProject(ByVal Info As implUserInfo, _
//    ByVal ProjectFilename As String, Done As Boolean)
//
//End Sub
void CMainApplication::OpenDataProject(implUserInfo* Info, BSTR ProjectFilename, VARIANT_BOOL* Done)
{
}

//Private Sub mSabisLink_CloseDataProject(ByVal DoAsk As Boolean, ByVal CleanUp As Boolean, Done As Boolean)
//  If Not IsNothing(mSabisLink) Then
//    Unload Mainform
//    Call mSabisLink.OnCloseDataProject
//    Set mSabisLink = Nothing
//    Done = True
//  End If
//End Sub
void CMainApplication::CloseDataProject(VARIANT_BOOL DoAsk, VARIANT_BOOL CleanUp, VARIANT_BOOL *pDone)
{
	if (NULL == pDone)
		return;
	*pDone = VARIANT_FALSE;

	COM_TRY {
		if (NULL != m_SabisLink.GetInterfacePtr()) {
			THROW_FAILED_HRESULT(m_SabisLink -> OnCloseDataProject());
			THROW_FAILED_HRESULT(Disconnect (m_SabisLink));
			m_SabisLink.Release();
			*pDone = VARIANT_TRUE;
		}
	} COM_CATCH_NORETURN;
}

//Private Sub mSabisLink_ShowProjectInfo()
//  Call MsgBox("Projektinformation")
//End Sub
void CMainApplication::ShowProjectInfo()
{
CWindow hwndParent;

	hwndParent.MessageBox ("Projektinformation");
}

void CMainApplication::BreakGetData()
{
}

void CMainApplication::BreakSendData(BSTR Linkgroup)
{
}

//Private Sub mSabisLink_GetMaxDataCount(ByVal Linkgroup As String, Selected As Long)
//  With Mainform
//    If .FormFrame.Visible And Len(.LinkId) > 0 Then
//      Selected = 1
//    Else
//      Selected = 0
//    End If
//  End With
//End Sub
void CMainApplication::GetMaxDataCount(BSTR Linkgroup, long* Selected)
{
}

//Private Sub mSabisLink_GetData(ByVal Linkgroup As String, AName As String, Done As Boolean)
//  With Mainform
//    If .FormFrame.Visible Then
//      AName = .LinkId
//      Done = True
//    End If
//  End With
//End Sub
void CMainApplication::GetData(BSTR Linkgroup, BSTR* AName, VARIANT_BOOL* Done)
{
}

void CMainApplication::AddToSendData(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem, VARIANT_BOOL* Done)
{
}

void CMainApplication::DoSendData(implUserInfo* Info, BSTR Linkgroup, BSTR Source)
{
}

//Private Sub mSabisLink_OpenForm(ByVal Info As implUserInfo, _
//    ByVal Linkgroup As String, ByVal LinkItem As String, ByVal OpenID As Variant, Done As Boolean)
//
//  Call mSabisLink_RefreshForm(Info, Linkgroup, LinkItem)
//  Mainform.FormFrame.Visible = True
//End Sub
void CMainApplication::OpenForm(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem, VARIANT OpenID, VARIANT_BOOL* Done)
{
}

//Private Sub mSabisLink_CloseChilds(ByVal Art As Variant, Done As Boolean)
//  Mainform.FormFrame.Visible = False
//End Sub
void CMainApplication::CloseChilds(VARIANT Art, VARIANT_BOOL* Done)
{
}

//Private Sub mSabisLink_OpenFormCount(ByVal GrpArt As Variant, Anzahl As Long)
//  With Mainform
//    If .FormFrame.Visible And Len(.LinkId) > 0 Then
//      Anzahl = 1
//    Else
//      Anzahl = 0
//    End If
//  End With
//End Sub
void CMainApplication::OpenFormCount(VARIANT GrpArt, long* Anzahl)
{
}

//Private Sub mSabisLink_RefreshForm(ByVal Info As implUserInfo, _
//    ByVal Linkgroup As String, ByVal LinkItem As String)
//
//  With Mainform
//    .GroupId = Linkgroup
//    .LinkId = LinkItem
//  End With
//End Sub
void CMainApplication::RefreshForm(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem)
{
}

//Private Sub mSabisLink_TestCurrentgroup(ByVal Linkgroup As String, Ok As Boolean)
//  Ok = Len(Linkgroup) > 0
//End Sub
void CMainApplication::TestCurrentgroup(BSTR Linkgroup, VARIANT_BOOL* Ok)
{
}

//Private Sub mSabisLink_GetCurrentLinkgroup(Gruppe As String)
//  Gruppe = Mainform.GroupId
//End Sub
void CMainApplication::GetCurrentLinkgroup(BSTR* Gruppe)
{
}

//Private Sub mSabisLink_GetCurrentLinkgroupName(Name As String)
//  Name = Mainform.LinkId
//End Sub
void CMainApplication::GetCurrentLinkgroupName(BSTR* Name)
{
}

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
//Private Function OpenData(ByVal Projektname$) As Boolean
//  Load Mainform
//  Mainform.FormFrame.Caption = " " + Projektname + " "
//  OpenData = True
//End Function
BOOL CMainApplication::OpenData (BSTR ProjektName)
{
	ATLTRACE("OpenData für Projekt: %ls\r\n", ProjektName);
	return TRUE;
}

// Eventsink beim connectionpoint anmelden
HRESULT CMainApplication::Connect (_DLLApplicationLinkTarget *pTarget)
{
	_ASSERTE(0 == m_dwCookie);
	return AtlAdvise (pTarget, GetUnknown(), DIID___DLLApplicationLinkTarget, &m_dwCookie);
}

// Eventsink beim connectionpoint abmelden
HRESULT CMainApplication::Disconnect (_DLLApplicationLinkTarget *pTarget)
{
	_ASSERTE(0 != m_dwCookie);

	RETURN_FAILED_HRESULT(AtlUnadvise (pTarget, DIID___DLLApplicationLinkTarget, m_dwCookie));
	m_dwCookie = 0L;
	return S_OK;
}

