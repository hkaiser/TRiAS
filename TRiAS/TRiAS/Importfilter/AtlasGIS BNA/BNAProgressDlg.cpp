// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 23.04.2002 09:48:01 
//
// @doc
// @module BNAProgressDlg.cpp | Definition of the <c CBNAProgressDlg> class

#include "bnaimpp.hpp"

#include <fnamestr.h>
#include <ospace/std/vector>
#include <ospace/string/tokenize.h>

#include "BNAProgressDlg.h"
#include "BNAImportConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT WM_PARSEFILES = RegisterWindowMessage("WM_PARSEFILES");
const UINT WM_SWITCHTONEXTPAGE = RegisterWindowMessage("WM_SWITCHTONEXTPAGE");
short DatLayer( char const*);

///////////////////////////////////////////////////////////////////////////////
// CBNAProgressDlg
/*static*/
CBNAProgressDlg *CBNAProgressDlg::CreateInstance(LPCSTR pcCaption, CBNAImportConfig *pBack)
{
CBNAProgressDlg *pDlg = NULL;

	COM_TRY {
	// Dialog neu anlegen
	ResourceFile RF (g_pDLLName);

		pDlg = new CBNAProgressDlg(ResID(IDD, &RF), 
			pcCaption, pBack);
		if (NULL == pDlg || !pDlg->FInit()) {
			DELETE_OBJ(pDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pDlg, NULL);
	return pDlg;
}

CBNAProgressDlg::CBNAProgressDlg(ResID uiDlg, LPCSTR pcCaption, CBNAImportConfig*pBack) :
	CPropertyPage(uiDlg, pcCaption),
	m_FilesStatus(this, IDPB_FILES_STATUS),
	m_ftFilesPrompt(this, IDT_FILESPROMPT),
	m_Status(this, IDPB_STATUS),
	m_ftFileName(this, IDT_FILENAME),
	m_aviSearch(this, IDC_ANIMATE_SEARCH),
	m_pBack(pBack),
	m_fAviStarted(false)
{
}

CBNAProgressDlg::~CBNAProgressDlg()
{
	m_pBack -> ResetData();
}

///////////////////////////////////////////////////////////////////////////////
// MessageHandling

///////////////////////////////////////////////////////////////////////////////
// MessageHandler
void CBNAProgressDlg::WindowInit(Event e)
{
	m_FilesStatus.FInit();
	m_ftFilesPrompt.FInit();
	m_ftFileName.FInit();
	m_Status.FInit();
	m_aviSearch.FInit();
}

void CBNAProgressDlg::ButtonClick(ControlEvt e)
{
}

int CBNAProgressDlg::OnWizNext (NotifyEvt e)
{
	if (m_fAviStarted) {
		m_aviSearch.Stop();
		m_fAviStarted = false;
	}
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CBNAProgressDlg::OnWizBack (NotifyEvt e)
{
	if (m_fAviStarted) {
		m_aviSearch.Stop();
		m_fAviStarted = false;
	}
	return 0;
}

int CBNAProgressDlg::OnSetActive (NotifyEvt e)
{
	_ASSERTE(NULL != m_pBack);

	if (!m_pBack -> GetFilesParsed()) {
		COM_TRY {
		WEnumString Enum;
		LPOLESTR poleString = NULL;

			THROW_FAILED_HRESULT(m_pBack -> GetEnumFiles(Enum.ppi()));

		// Zählen, wieviele Dateien bearbeitet werden sollen
		ULONG ulCount = 0;

			for (Enum -> Reset(); S_OK == Enum -> Next(1, &poleString, NULL); /**/) {
				++ulCount;
				CoTaskMemFree(poleString);
			}

		// ggf. zweiten Progressbar ausblenden
			if (ulCount == 1) {
				m_FilesStatus.Hide();
				m_ftFilesPrompt.Hide();
			}
			else {
				m_FilesStatus.SetRange(0, ulCount);
				m_FilesStatus.SetPos(0);
			}

		// Dateien bearbeiten
			PostEvent(WM_PARSEFILES, ulCount);

		} COM_CATCH;
		m_fAviStarted = m_aviSearch.Open (IDR_ANI_SEARCH) ? true : false;
	}
	else
		PostEvent (WM_SWITCHTONEXTPAGE);

	AdjustSheetButtons();
	return 0;
}

LRESULT CBNAProgressDlg::Dispatch(Event e)
{
	if (WM_PARSEFILES == e.Msg()) {
		Update();

	// Registryeinträge einlesen
		m_pBack -> InitConfigDataFromRegistry();

	// Dateien untersuchen
	WEnumString Enum;
	LPOLESTR poleString = NULL;

		THROW_FAILED_HRESULT(m_pBack -> GetEnumFiles(Enum.ppi()));

	ULONG ulCount = 0;

		for (Enum -> Reset(); S_OK == Enum->Next(1, &poleString, NULL); /**/) {
			USES_CONVERSION;

	//KK020904-NOT ===========================================================

			short m_iMode = DatLayer(OLE2A(poleString));

////////////////////////////////////////////////////////////////////////////////
			if ( m_iMode ) {
				if ( m_iMode == DATIMPORT)
					ParseFileDat(OLE2A(poleString), ++ulCount, e.WParam());

				if ( m_iMode == GPSIMPORT)
					VideoFileDat(OLE2A(poleString), ++ulCount, e.WParam());

				if ( m_iMode == GCAIMPORT)
					GCAFileDat(OLE2A(poleString), ++ulCount, e.WParam());

			} else
				ParseFile(OLE2A(poleString), ++ulCount, e.WParam());
	//KK020904-NOT ===========================================================

			CoTaskMemFree(poleString);
		}
		PostEvent (WM_SWITCHTONEXTPAGE);
		return TRUE;
	}

	if (WM_SWITCHTONEXTPAGE == e.Msg())
		GetPropertySheet()->PressButton(PSBTN_NEXT);

	if (WM_CTLCOLORSTATIC == e.Msg()) {
		if ((HWND)e.LParam() == m_aviSearch.Handle()) {
			::SetBkColor ((HDC)e.WParam(), ::GetSysColor (COLOR_3DFACE));
			return (LRESULT)::GetSysColorBrush(COLOR_3DFACE);
		}
	}
	return CPropertyPage::Dispatch(e);
}

///////////////////////////////////////////////////////////////////////////////
// 
void CBNAProgressDlg::AdjustSheetButtons()
{
// nicht erste Seite
DWORD dwBttns = PSWIZB_BACK;

// letzte Seite
	if (!GetDisableNextPage()) 
		dwBttns |= PSWIZB_NEXT;

	SetSheetWizardButtons(dwBttns);
}

BOOL CBNAProgressDlg::GetDisableNextPage()
{
	_ASSERTE(NULL != m_pBack);
	return !m_pBack -> GetFilesParsed();
}

HRESULT CBNAProgressDlg::PrepareResult (void)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eine Datei Parsen
class CCloseFileOnExit
{
public:
	CCloseFileOnExit(FILE *pFile) : m_pFile(pFile) {}
	~CCloseFileOnExit() { if (NULL != m_pFile) fclose(m_pFile); }

	bool IsOpen() { return NULL != m_pFile; }
	FILE *Ptr() { return m_pFile; }

private:
	FILE *m_pFile;
};

///////////////////////////////////////////////////////////////////////////////
// Objekttyp aus Geometriefeld des Kopfsatzes berechnen
DWORD GetObjType (string &rStr, long *pulCount = NULL)
{
size_t iPos = rStr.find_first_not_of(", \t");

	_ASSERTE(os_npos != iPos);

long iKoords = atol(rStr.substr(iPos).c_str());

	if (NULL != pulCount)
		*pulCount = iKoords;

	if (1 == iKoords)
		return OTPunkt;
	return iKoords < 0 ? OTLinie : OTFlaeche;
}
//////////////////////////////////////////////////////////////////////////////
HRESULT CBNAProgressDlg::ParseFile(LPCSTR pcFile, ULONG ulAct, ULONG ulCount)
{
// gg. globalen Status weitersetzen
	if (ulCount > 1) {
	ResourceFile RF (g_pDLLName);
	ResString resPrompt (ResID(IDS_FILES_PROMPT, &RF), 64);
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, resPrompt, ulAct, ulCount);
		m_ftFilesPrompt.SetText(cbBuffer);
		m_FilesStatus.StepIt();
	}

// Datei untersuchen
CCloseFileOnExit File (fopen (pcFile, "r"));

	if (!File.IsOpen())
		return STG_E_PATHNOTFOUND;

	fseek (File.Ptr(), 0L, SEEK_END);		// Dateilänge bestimmen

long lLen = ftell (File.Ptr());
int iToShift = 0;

	while (lLen > SHRT_MAX) {
		lLen >>= 1;
		++iToShift;
	}

char cbLine[4*_MAX_PATH];

	m_Status.SetRange(0, lLen);
	m_Status.SetPos(0);
	m_ftFileName.SetText(pcFile);

	fseek (File.Ptr(), 0L, SEEK_SET);			// wieder am Anfang
	while (fgets (cbLine, sizeof(cbLine)-1, File.Ptr())) {
	long lPos = ftell(File.Ptr());

		lPos >>= iToShift;
		m_Status.SetPos (lPos);		// nächste Zeile gelesen
		App::Exec(ExecWhileEvent);			// ggf. Cancel bearbeiten

		if ('\"' != cbLine[0])
			continue;			// nur Kopfzeilen auswerten

	// tokenizer zerteilt die Kopfzeile in Tokens:
	// token 0: leer
	// token 1: NAME1
	// token 2: ','
	// token 3: NAME2
	// token 4: ','
	// token 5: ID
	// token 6: ','
	// token 7: LAYER
	// token 8: ",Geometrie" (Anzahl der Stützpunkte)
	os_tokenizer token("\"", true, "", "\n", "", false);
	vector<string> tokens = token.tokenize(cbLine);

		if (9 == tokens.size() && tokens[7].size() > 0)
			m_pBack -> StoreLayer(tokens[7], GetObjType(tokens[8]));
	}

// einmal geparst müßte reichen
	m_pBack -> SetFilesParsed(true);
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////////////

