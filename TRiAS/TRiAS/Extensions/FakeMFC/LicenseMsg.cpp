// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.11.2000 19:12:58 
//
// @doc
// @module LicenseMsg.cpp | Definition of the <c CLicenseMsg> class

#include "stdafx.h"

#include <EsnecilExt.h>

#include "Version.h"
#include "Strings.h"
#include "fakemfc.h"
#include "DTWinVer.h"
#include "LicenseMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseMsg dialog

CLicenseMsg::CLicenseMsg(CWnd* pParent /*=NULL*/, LPCSTR pcCaption,
		LPCSTR pcLicText)
	: CDialog(CLicenseMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenseMsg)
	m_LicText = _T("");
	//}}AFX_DATA_INIT
	if (NULL != pcCaption)
		m_strCaption = pcCaption;
	if (NULL != pcLicText)
		m_LicText.Format(pcLicText, g_cbTRiAS, g_cbTRiAS);
}


void CLicenseMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseMsg)
	DDX_Control(pDX, IDC_EMAIL, m_Email);
	DDX_Text(pDX, IDC_LICENSETEXT, m_LicText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseMsg, CDialog)
	//{{AFX_MSG_MAP(CLicenseMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseMsg message handlers

BOOL CLicenseMsg::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Caption korrigieren
	if (!m_strCaption.IsEmpty()) {
	CString strT;

		strT.Format ("%s - %s", g_cbTRiAS, m_strCaption);
		SetWindowText (strT);

	// Anzeigetext korrigieren
		m_LicText.Format (IDS_LICENSETEXT, m_strCaption, g_cbTRiAS);
	}
	else if (m_LicText.IsEmpty()) {
	// Anzeigetext korrigieren
		m_LicText.Format (IDS_LICENSETEXT_AUX, g_cbTRiAS);
	}

// url format:
// mailto:info@trias-gis.de?subject=Lizensierung von TRiAS&body=TRiAS V..., Standortcode: ...
CString strURL;

	VERIFY(strURL.LoadString(IDS_EMAILURL));
	m_Email.SetURL(strURL);
	m_Email.SetURLEx (GetURLEx());
	
	UpdateData(FALSE);

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CLicenseMsg::GetURLEx()
{
CString strLic, strPref;
CEsnecilExt Lic;

	strPref.LoadString (IDS_EMAILBODY_PREFIX);
	strLic.Format (IDS_EMAILBODY, strPref, GetOSVersion(), TRiAS_VERSION, Lic.GetSiteCode(), Lic.GetInstallDate());
	return strLic;
}

CString CLicenseMsg::GetOSVersion()
{
	OS_VERSION_INFO osvi;
	memset(&osvi, 0, sizeof(OS_VERSION_INFO));

COSVersion Version;
CString strOSVersion;
TCHAR sBuf[512];

	if (Version.GetVersion(&osvi)) {                                           
		strOSVersion = _T("Emuliertes OS: ");
		strOSVersion += GetOSName(Version, osvi.dwEmulatedPlatformId, osvi);

		_stprintf(sBuf, _T(" v%d."), osvi.dwEmulatedMajorVersion);
		strOSVersion += sBuf;
		_stprintf(sBuf, _T("%02d "), osvi.dwEmulatedMinorVersion);
		strOSVersion += sBuf;

		if (osvi.dwEmulatedBuildNumber)
		{
			_stprintf(sBuf, _T("Build: %d"), osvi.dwEmulatedBuildNumber);
			strOSVersion += sBuf;
		}
		if (osvi.wEmulatedServicePack)       
		{
			_stprintf(sBuf, _T(" Service Pack: %d"), osvi.wEmulatedServicePack);
			strOSVersion += sBuf;
		}                            
		strOSVersion += _T("%0D%0A");

		strOSVersion += _T("Unterliegendes OS: ");
		strOSVersion += GetOSName (Version, osvi.dwUnderlyingPlatformId, osvi);

		_stprintf(sBuf, _T(" v%d."), osvi.dwUnderlyingMajorVersion);
		strOSVersion += sBuf;
		_stprintf(sBuf, _T("%02d "), osvi.dwUnderlyingMinorVersion);
		strOSVersion += sBuf;
		if (osvi.dwUnderlyingBuildNumber)
		{
			_stprintf(sBuf, _T("Build: %d"), osvi.dwUnderlyingBuildNumber);
			strOSVersion += sBuf;
		}
		if (osvi.wUnderlyingServicePack)       
		{
			_stprintf(sBuf, _T(" Service Pack: %d"), osvi.wUnderlyingServicePack);
			strOSVersion += sBuf;
		}                    
		strOSVersion += _T("%0A%0D");
	}
	else
		strOSVersion = _T("Fehler in GetOSVersion%0A%0D");

	return strOSVersion;
}

CString CLicenseMsg::GetOSName(COSVersion &os, DWORD dwPlatFormId, OS_VERSION_INFO &osvi)
{
TCHAR sBuf[100];

	switch (dwPlatFormId) {
	case DT_PLATFORM_DOS:               
		_stprintf(sBuf, _T("DOS"));  
		break;

	case DT_PLATFORM_WINDOWS3x:         
		_stprintf(sBuf, _T("Windows"));
		if (os.IsWin32sInstalled(&osvi))
			_stprintf(sBuf, _T(" (Win32s)"));
		break;

	case DT_PLATFORM_WINDOWSCE:
		_stprintf(sBuf, _T("Windows CE"));
		break;

	case DT_PLATFORM_WINDOWS9x:
		if (os.IsWindows95(&osvi))
			_stprintf(sBuf, _T("Windows 95"));
		else if (os.IsWindows95SP1(&osvi))
			_stprintf(sBuf, _T("Windows 95 SP1"));
		else if (os.IsWindows95OSR2(&osvi))
			_stprintf(sBuf, _T("Windows 95 OSR2"));
		else if (os.IsWindows98(&osvi))
			_stprintf(sBuf, _T("Windows 98"));
		else if (os.IsWindows98SP1(&osvi))
			_stprintf(sBuf, _T("Windows 98 SP1"));
		else if (os.IsWindows98SE(&osvi))
			_stprintf(sBuf, _T("Windows 98 Second Edition"));
		else if (os.IsWindowsME(&osvi))
			_stprintf(sBuf, _T("Windows Millenium Edition"));
		else
			_stprintf(sBuf, _T("Windows ??"));
		break;

	case DT_PLATFORM_NT:
		if (os.IsNTPreWin2k(&osvi)) {
			_stprintf(sBuf, _T("Windows NT"));
			if (os.IsNTWorkstation(&osvi))
				_stprintf(sBuf, _T(" (Workstation)"));
			else if (os.IsNTStandAloneServer(&osvi))
				_stprintf(sBuf, _T(" (Server)"));
			else if (os.IsNTPDC(&osvi))
				_stprintf(sBuf, _T(" (Primary Domain Controller)"));
			else if (os.IsNTBDC(&osvi))
				_stprintf(sBuf, _T(" (Backup Domain Controller)"));
			
			if (os.IsNTDatacenterServer(&osvi))
				_stprintf(sBuf, _T(", (Datacenter)"));
			else if (os.IsNTEnterpriseServer(&osvi))
				_stprintf(sBuf, _T(", (Enterprise)"));
		}
		else if (os.IsWindows2000(&osvi)) {
			_stprintf(sBuf, _T("Windows 2000"));
			if (os.IsWin2000Professional(&osvi))
				_stprintf(sBuf, _T(" (Professional)"));
			else if (os.IsWin2000Server(&osvi))
				_stprintf(sBuf, _T(" (Server)"));
			else if (os.IsWin2000DomainController(&osvi))
				_stprintf(sBuf, _T(" (Domain Controller)"));
			
			if (os.IsWin2000DatacenterServer(&osvi))
				_stprintf(sBuf, _T(", (Datacenter)"));
			else if (os.IsWin2000AdvancedServer(&osvi))
				_stprintf(sBuf, _T(", (Advanced Server)"));
			
			if (os.IsTerminalServicesInstalled(&osvi))
				_stprintf(sBuf, _T(", (Terminal Services)"));
			if (os.ISSmallBusinessEditionInstalled(&osvi))
				_stprintf(sBuf, _T(", (BackOffice Small Business Edition)"));
		}
		else if (os.IsWindowsXP(&osvi)) {
			_stprintf(sBuf, _T("Windows XP"));
			if (os.IsXPPersonal(&osvi))
				_stprintf(sBuf, _T(" (Personal)"));
			else if (os.IsXPProfessional(&osvi))
				_stprintf(sBuf, _T(" (Professional)"));
			else if (os.IsXPServer(&osvi))
				_stprintf(sBuf, _T(" (Server)"));
			else if (os.IsXPDomainController(&osvi))
				_stprintf(sBuf, _T(" (Domain Controller)"));
			
			if (os.IsXPDatacenterServer(&osvi))
				_stprintf(sBuf, _T(", (Datacenter)"));
			else if (os.IsXPAdvancedServer(&osvi))
				_stprintf(sBuf, _T(", (Advanced Server)"));
			
			if (os.IsTerminalServicesInstalled(&osvi))
				_stprintf(sBuf, _T(", (Terminal Services)"));
			if (os.ISSmallBusinessEditionInstalled(&osvi))
				_stprintf(sBuf, _T(", (BackOffice Small Business Edition)"));
			
			if (os.Is64Bit(&osvi))
				_stprintf(sBuf, _T(", (64 Bit Edition)"));
		}
		break;

	default: 
		_stprintf(sBuf, _T("Unknown OS"));
		break;
	}
	return CString(sBuf);
}

