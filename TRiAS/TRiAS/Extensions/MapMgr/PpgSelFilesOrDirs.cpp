// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 22:00:53 
//
// @doc
// @module PpgSelFilesOrDirs.cpp | Definition of the <c CPpgSelFilesOrDirs> class

#include "stdafx.h"
#include <WinVersion.h>
#include <ospace/file/path.h>
#include <Com/ComBool.h>

#include "DDXGetFolder.h"
#include "ImportDlg.h"
#include "PpgSelFilesOrDirs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinVersion g_Version;

/////////////////////////////////////////////////////////////////////////////
// CPpgSelFilesOrDirs property page

IMPLEMENT_DYNCREATE(CPpgSelFilesOrDirs, CPropertyPage)

CPpgSelFilesOrDirs::CPpgSelFilesOrDirs() : 
	CPropertyPage(CPpgSelFilesOrDirs::IDD)
{
	//{{AFX_DATA_INIT(CPpgSelFilesOrDirs)
	m_strDestDir = _T("");
	m_strRefDir = _T("");
	m_strSrcDir = _T("");
	m_strFileOrDir = _T("");
	//}}AFX_DATA_INIT

	m_rgFlags = COPYFLAG_Default;
	m_fSelectedRefDir = FALSE;
	m_fSelectedDestDir = FALSE;
}

CPpgSelFilesOrDirs::~CPpgSelFilesOrDirs()
{
}

void CPpgSelFilesOrDirs::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgSelFilesOrDirs)
	DDX_Control(pDX, IDC_STATIC_ALTFILES, m_ftAltFiles);
	DDX_Control(pDX, IDC_STATIC_DESTINATION, m_ftDest);
	DDX_Text(pDX, IDC_SELDESTINATION, m_strDestDir);
	DDX_Text(pDX, IDC_SELREFFILES, m_strRefDir);
	DDX_Text(pDX, IDC_SELSOURCE, m_strSrcDir);
	DDX_Text(pDX, IDC_STATIC_FILESORDIR, m_strFileOrDir);
	//}}AFX_DATA_MAP

DWORD dwDirFlags = 0;

	if (!g_Version.IsWin40())
		dwDirFlags |= GFLDR_OLD_STYLE_DIALOG;
	if (g_Version.IsWin50())
		dwDirFlags |= GFLDR_SAVEASDIALOG;

// alle Controls sicher initialisieren
	DDX_PrepareFolderControl(pDX, IDC_SELDESTINATION, m_sleDestFolder);
	DDX_PrepareFolderControl(pDX, IDC_SELREFFILES, m_sleAltFolder);

// Quelle auswählen
	if (COPYFLAG_SourceIsDirectory & m_rgFlags) {
		if (NULL != m_sleGetFileName.m_hWnd) {
		// war File, ist jetzt Verzeichnis
			m_sleGetFileName.UnsubclassEdit();
			DDX_PrepareFolderControl(pDX, IDC_SELSOURCE, m_sleSrcFolder);
		}

	// Verzeichnis auswählen
	CString strCaption;
	os_path fileordir = os_string(m_pParent->m_strSrcMap);

		fileordir.no_extension();
		fileordir.filename("");

		VERIFY(strCaption.LoadString(IDS_SELECTDIRTITLE_SRC));
		DDX_GetFolderControl(pDX, IDC_SELSOURCE, 
			m_sleSrcFolder, dwDirFlags, strCaption,
			(LPCTSTR)fileordir);
	} 
	else {
		if (NULL != m_sleSrcFolder.m_hWnd) {
		// war Verzeichnis, ist jetzt File
			m_sleSrcFolder.UnsubclassEdit();
			DDX_PrepareFilenameControl(pDX, IDC_SELSOURCE, m_sleGetFileName);
		}

	// Dateinamen auswählen
	DWORD dwFlags = 0;

		if (!g_Version.IsWin40())
			dwFlags |= GF_OLD_STYLE_DIALOG;

		dwFlags |= GF_HIDEREADONLY;
		if (m_pParent->m_bMulti)
			dwFlags |= GF_MULTIPLESELECTION;
	
	CString strCaption;
	os_path fileordir = os_string(m_pParent->m_strSrcMap);

		fileordir.no_extension();
		fileordir.filename("");

	CString strPath ((LPCTSTR)fileordir);

		if (strPath.GetLength() > 0 && '\\' == strPath[strPath.GetLength()-1]) {
			if (!m_pParent->m_strDefExt.IsEmpty()) {
				strPath += _T("*");
				strPath += m_pParent->m_strDefExt;
			} else
				strPath = strPath.Left(strPath.GetLength()-1);
		}

		VERIFY(strCaption.LoadString (IDS_OPENFILETITLE));
		DDX_GetFilenameControl(pDX, IDC_SELSOURCE, 
				m_sleGetFileName, dwFlags, 
				strCaption, m_pParent->m_strPictFileFilter, 
				m_pParent->m_strDefExt, strPath);
	} 

// Zielverzeichnis auswählen
	if (COPYFLAG_ShouldCopyFiles & m_rgFlags) {
	CString strCaption;
	os_path fileordir = os_string(m_pParent->m_strDstDir);

		fileordir.no_extension();
		fileordir.filename("");

		VERIFY(strCaption.LoadString(IDS_SELECTDIRTITLE));
		DDX_GetFolderControl(pDX, IDC_SELDESTINATION, 
			m_sleDestFolder, dwDirFlags, strCaption,
			(LPCTSTR)fileordir);
	}

// Verzeichnis mit Beschreibungsdateien auswählen
	if (!m_pParent->m_strMapExt.IsEmpty()) {
	CString strCaption;
	os_path fileordir = os_string(m_pParent->m_strRefDir);

		fileordir.no_extension();
		fileordir.filename("");

		VERIFY(strCaption.LoadString(IDS_SELECTDIRTITLE_ALT));
		DDX_GetFolderControl(pDX, IDC_SELREFFILES, 
			m_sleAltFolder, dwDirFlags, strCaption,
			(LPCTSTR)fileordir);
	}
}

void CPpgSelFilesOrDirs::UpdateControls()
{
	m_pParent->m_pTopoMap->CopyFlags(&m_rgFlags);
	m_fSelectedRefDir = FALSE;
	m_fSelectedDestDir = FALSE;

	m_strSrcDir.Empty();
	m_strDestDir.Empty();
	m_strRefDir.Empty();

	AdjustControls();
	AdjustNextPage();
	AdjustButtons();

	UpdateData(FALSE);
}

void CPpgSelFilesOrDirs::AdjustNextPage()
{
CComBool fNeedsCoordSys;

	m_pParent->m_pTopoMap->NeedsCoordSystem(&fNeedsCoordSys);

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		m_pParent->m_nNextStep = 
			fNeedsCoordSys ? CSelectCoordSys::IDD : CPpgSelDataSource::IDD;
		m_pParent->SetCoordSystemIsLast(false);
	}
	else {
		m_pParent->m_nNextStep = fNeedsCoordSys ? CSelectCoordSys::IDD : -1;
		m_pParent->SetCoordSystemIsLast(true);
	}
}

void CPpgSelFilesOrDirs::AdjustButtons()
{
DWORD dwButtons = PSWIZB_BACK;

	if (m_strSrcDir.IsEmpty() || 
		((COPYFLAG_ShouldCopyFiles & m_rgFlags) && m_strDestDir.IsEmpty()) ||
		(!m_pParent->m_strMapExt.IsEmpty() && m_strRefDir.IsEmpty()))
	{
		dwButtons |= (-1 == m_pParent->m_nNextStep) ? PSWIZB_DISABLEDFINISH : 0;
	} 
	else
		dwButtons |= (-1 == m_pParent->m_nNextStep) ? PSWIZB_FINISH : PSWIZB_NEXT;

	m_pParent->SetWizardButtons(dwButtons);
}

void CPpgSelFilesOrDirs::AdjustControls()
{
CString strT;

	VERIFY(m_strFileOrDir.LoadString((COPYFLAG_SourceIsDirectory & m_rgFlags) ? 
		IDS_SRCDIRECTORY : IDS_SRCFILES));

	if (!(COPYFLAG_ShouldCopyFiles & m_rgFlags)) {
		m_ftDest.ShowWindow(SW_HIDE);
		m_sleDestFolder.ShowWindow(SW_HIDE);
	}
	else {
		m_ftDest.ShowWindow(SW_SHOW);
		m_sleDestFolder.ShowWindow(SW_SHOW);
	}

	if (m_pParent->m_strMapExt.IsEmpty()) {
		m_ftAltFiles.ShowWindow(SW_HIDE);
		m_sleAltFolder.ShowWindow(SW_HIDE);
	}
	else {
		m_ftAltFiles.ShowWindow(SW_SHOW);
		m_sleAltFolder.ShowWindow(SW_SHOW);

	// Prompt mit Kartentyp versehen
	CString strT;

		strT.Format (IDS_ALTFILEPROMPT, m_pParent->m_strMapExt);
		m_ftAltFiles.SetWindowText(strT);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen, daß das gegebene Quellverzeichnis im aktuellen Kontext Sinn
// macht
BOOL CPpgSelFilesOrDirs::ValidateSourceDirectory (LPCTSTR pcSrcDir)
{
CWaitCursor wait;

	_ASSERTE(m_pParent->m_pTopoPict != NULL);
	_ASSERTE(NULL != pcSrcDir);

	COM_TRY {
	CComQIPtr<IPictHolder, &IID_IPictHolder> p (m_pParent->m_pTopoPict);
	CComBSTR bstrFullName;

		THROW_FAILED_HRESULT(m_pParent->m_pTopoMap->
			MakeFullName(CComBSTR(pcSrcDir), &bstrFullName));
		if (S_OK == p->OpenPictureFile(bstrFullName)) {
		long bValid;

			THROW_FAILED_HRESULT(m_pParent->m_pTopoMap->
				CheckPictureFile(m_pParent->m_pTopoPict, &bValid));
			if (bValid) {
				m_pParent->m_strSrcMap = pcSrcDir;
				return TRUE;
			}
		} 

	// Fehlerhinweis ausgeben
	CString	S;

		S.Format(IDS_NOMAP_DIR, pcSrcDir, (LPCTSTR)m_pParent->m_strMapType);
		::AfxMessageBox(S);

	} COM_CATCH_IGNORE;
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen, das wenigstens eine der gegebenen Dateien im aktuellen Kontext 
// Sinn macht
BOOL CPpgSelFilesOrDirs::ValidateSourceFiles(CFiles &rFiles)
{
CWaitCursor wait;

	_ASSERTE(m_pParent->m_pTopoPict != NULL);

	COM_TRY {
	long fValid = FALSE;
	CFiles::iterator end = rFiles.end();
	CFiles badFiles;

		for (CFiles::iterator it = rFiles.begin(); it != end; ++it) {
		CComQIPtr<IPictHolder, &IID_IPictHolder> p (m_pParent->m_pTopoPict);

			if (S_OK == p->OpenPictureFile(CComBSTR((*it).c_str()))) {
			long bValid;

				m_pParent->m_pTopoMap->CheckPictureFile(m_pParent->m_pTopoPict, &bValid);
				if (bValid) {
				os_path filename = (*it).c_str();

					m_pParent->m_strSrcMap = (*it).c_str();
					m_pParent->m_TopKart.push_back(filename.base());
					m_pParent->m_lMultiCount++;
					fValid = TRUE;		// wenigstens einer ist richtig
					continue;
				}
			} 

		// Datei ist nicht vom gewünschten Typ
			badFiles.insert(*it);
		}

	// ggf. Fehlerhinweis ausgeben
		if (badFiles.size() > 0) {
			if (1 == badFiles.size()) {
			CString	S;

				S.Format(IDS_NOMAPTYPE, (*badFiles.begin()).c_str(), (LPCTSTR)m_pParent->m_strMapType);
				::AfxMessageBox(S);
			}
			else {
			CString	S;

				S.Format(IDS_NOMAP_MULTI, (LPCTSTR)m_pParent->m_strMapType);
				for (CFiles::iterator itbad = badFiles.begin(); itbad != badFiles.end(); ++itbad) {
					S += (*it).c_str();
					S += '\n';
				}
				::AfxMessageBox(S);
				m_pParent->m_strSrcMap.Empty();
			}
		}
	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPpgSelFilesOrDirs, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgSelFilesOrDirs)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FILESELECTED, OnFileOrDirSelected)
	ON_MESSAGE(WM_DIRSELECTED, OnFileOrDirSelected)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgSelFilesOrDirs message handlers

BOOL CPpgSelFilesOrDirs::OnInitDialog()  
{
CMapImportDlg *pParent = (CMapImportDlg *)GetParent();
	
	ASSERT_KINDOF(CMapImportDlg, pParent);

	m_strSrcDir = pParent->m_strLastDirUsed;
	pParent->m_pTopoMap->CopyFlags(&m_rgFlags);

	CPropertyPage::OnInitDialog();

	AdjustButtons();
	UpdateData (FALSE);

	return TRUE;
}

LRESULT CPpgSelFilesOrDirs::OnFileOrDirSelected (WPARAM wParam, LPARAM lParam)
{
	UpdateData (TRUE);		// Daten übernehmen

	switch (wParam) {
	case IDC_SELSOURCE:
		{
		BOOL fValid = FALSE;

			if (COPYFLAG_SourceIsDirectory & m_rgFlags) 
				fValid = ValidateSourceDirectory(m_strSrcDir);
			else 
				fValid = ValidateSourceFiles(m_sleGetFileName.GetFiles());

			if (fValid) {
				m_pParent->m_strSrcMap = m_strSrcDir;

			os_path dir = (LPCSTR)m_strSrcDir;

				dir.no_extension();
				dir.filename("");
				if (!m_fSelectedDestDir) 
					m_pParent->m_strDstDir = m_strDestDir = (LPCSTR)dir;
				if (!m_fSelectedRefDir) 
					m_pParent->m_strRefDir = m_strRefDir = (LPCSTR)dir;

			// ggf. Koordinatensystem abfragen
			CComPtr<IUnknown> pUCS;
				
				_ASSERTE(m_pParent->m_pTopoMap != NULL);
				if (S_OK == m_pParent->m_pTopoMap->GetCoordSystem(&pUCS)) {
				CComQIPtr<ITRiASCS, &IID_ITRiASCS> pCS = pUCS;
#if defined(_DEBUG)
				TRIASCSTYPE	t;

					pCS->get_CoordSystemType(&t);
					_ASSERTE(tcsCS_Undefined != t);
#endif // defined(_DEBUG)
					m_pParent->m_pCS = pCS;
				} else
					m_pParent->m_pCS.Release();
			}
			else {
				m_pParent->m_strSrcMap.Empty();
				m_strSrcDir.Empty();
				m_pParent->m_pCS.Release();
			}
		}
		break;

	case IDC_SELDESTINATION:
		m_fSelectedDestDir = TRUE;
		m_pParent->m_strDstDir = m_strDestDir;
		break;

	case IDC_SELREFFILES:
		m_fSelectedRefDir = TRUE;
		m_pParent->m_strRefDir = m_strRefDir;
		break;

	default:
		_ASSERTE(FALSE);
		break;
	}

	UpdateData (FALSE);		// Daten übernehmen
	AdjustButtons();
	return TRUE;
}

BOOL CPpgSelFilesOrDirs::OnWizardFinish()
{
	if (!(COPYFLAG_MustReduceFiles & m_rgFlags))
		m_pParent->m_bNoReduce = true;
	return CPropertyPage::OnWizardFinish();
}

LRESULT CPpgSelFilesOrDirs::OnWizardNext() 
{
	if (!(COPYFLAG_MustReduceFiles & m_rgFlags))
		m_pParent->m_bNoReduce = true;
	return CPropertyPage::OnWizardNext();
}
