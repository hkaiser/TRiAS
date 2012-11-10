// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 19:50:54 
//
// @doc
// @module GenerateObjectPropertiesDlg.cpp | Definition of the 
// <c CGenerateObjectPropertiesOptionsDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ospace/file/path.h>

#include <eieruhr.hxx>
#include <StdDlg.hxx>
#include <TrCatIds.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DataHelp.h"
#include "GenerateObjectProperties.h"
#include "GenerateObjectPropertiesOptionsDlg.h"

///////////////////////////////////////////////////////////////////////////////
// 
extern TCHAR g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesOptionsDlg

CGenerateObjectPropertiesOptionsDlg* CGenerateObjectPropertiesOptionsDlg::CreateInstance (
		CGenerateObjectProperties *pParent, LPCSTR pcCaption)
{
CGenerateObjectPropertiesOptionsDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CGenerateObjectPropertiesOptionsDlg(pParent, ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CGenerateObjectPropertiesOptionsDlg::CGenerateObjectPropertiesOptionsDlg(
		CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption) :
	CPropertyPage(uiResID, pcCaption), m_pParent(pParent),
	m_cbHeadline(this, IDCB_OBJPROPHEADLINE),
	m_cbCumulate(this, IDCB_OBJPROPCUMULATE),
	m_cbProps(this, IDCB_OBJPROPPROPS),
	m_cbCounter(this, IDCB_OBJPROPCOUNT),
	m_rbClipboard(this, IDR_OBJPROPCLIPBOARD),
	m_rbWindow(this, IDR_OBJPROPWINDOW),
	m_rbFile(this, IDR_OBJPROPFILE),
	m_rbProperty(this, IDR_OBJPROPMCODE),
	m_pbSelFile(this, IDC_OBJPROPFILE),
	m_sleSelFile(this, IDE_OBJPROPFILE),
	m_Property(this, IDC_OBJPROPERTY, IDC_SELECT_OBJPROP, IncludeWritable),
	m_cboxDelim(this, IDC_SEPARATOR)
{
	m_dwFlags = 0;
	m_rgDest = OBJPROPDEST_Clipboard;

	m_fHeadLine = false;
	m_fCumulate = false;
	m_fProps = true;
	m_fCounter = false;

	m_iFileType = -1;

	m_cDelimiter = '\t';
}

CGenerateObjectPropertiesOptionsDlg::~CGenerateObjectPropertiesOptionsDlg()
{
}

BOOL CGenerateObjectPropertiesOptionsDlg::FInit (void)
{
	return TRUE;
}

void CGenerateObjectPropertiesOptionsDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons(dwBttns);
}

BOOL CGenerateObjectPropertiesOptionsDlg::GetDisableNextPage()
{
// wenn keine Datei gegeben ist, aber generiert werden soll, dann OK passiv
	if ((m_rbFile.GetState() && 0 == m_sleSelFile.GetTextLen()) ||
	    (m_rbProperty.GetState() && !m_Property.hasSelection()))
	{
		return TRUE;
	}
	return FALSE;
}

CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST 
CGenerateObjectPropertiesOptionsDlg::CalcDestination()
{
OBJPROPDEST rgDest = OBJPROPDEST_Clipboard;

	if (m_rbWindow.GetState())
		rgDest = OBJPROPDEST_Window;
	else if (m_rbFile.GetState()) {
		_ASSERTE(-1 != m_iFileType);
		rgDest = OBJPROPDEST(OBJPROPDEST_File + m_iFileType -1);
	} else if (m_rbProperty.GetState())
		rgDest = OBJPROPDEST_Property;

	return rgDest;
}

namespace {
	bool IsEqual (LPCSTR pcBuffer, UINT uiRes)
	{
	ResourceFile RF (g_pDLLName);
	ResString res (ResID(uiRes, &RF), 32);

		return !strcmp (pcBuffer, res);
	}
}

HRESULT CGenerateObjectPropertiesOptionsDlg::PrepareResult()
{
	m_fHeadLine = m_cbHeadline.isChecked() ? true : false;
	m_fCumulate = m_cbCumulate.isChecked() ? true : false;
	m_fProps = m_cbProps.isChecked() ? true : false;
	m_fCounter = m_cbCounter.isChecked() ? true : false;

	m_rgDest = CalcDestination();
	switch (m_rgDest) {
	case OBJPROPDEST_Property:
		m_Property.SaveData(m_strObjPropName);
		break;
	
	case OBJPROPDEST_FileCsv:
	case OBJPROPDEST_FileOpr:
		{
		char cbBuffer[_MAX_PATH];

			m_sleSelFile.GetText(cbBuffer, sizeof(cbBuffer));
			m_strFileName = cbBuffer;
		}
		break;
	
	case OBJPROPDEST_Window:
	case OBJPROPDEST_Clipboard:
		break;
	
	default:
		break;
	}

// Trennzeichen 
char cbBuffer[32];

	m_cboxDelim.GetText(cbBuffer, sizeof(cbBuffer));
	if (IsEqual (cbBuffer, IDS_DELIMITER_SPACE))
		m_cDelimiter = ' ';
	else if (IsEqual (cbBuffer, IDS_DELIMITER_COMMA))
		m_cDelimiter = ',';
	else if (IsEqual (cbBuffer, IDS_DELIMITER_SEMICOLON))
		m_cDelimiter = ';';
	else if (IsEqual (cbBuffer, IDS_DELIMITER_TABULATOR))
		m_cDelimiter = '\t';
	else if (IsEqual (cbBuffer, IDS_DELIMITER_NODELIMITER))
		m_cDelimiter = '\0';
	else
		m_cDelimiter = cbBuffer[0];
		
	return S_OK;
}

void CGenerateObjectPropertiesOptionsDlg::AdjustControls()
{
	if (m_rbProperty.GetState()) {
		m_fHeadLine = m_cbHeadline.isChecked();
		m_fCumulate = m_cbCumulate.isChecked();
		m_cbHeadline.SetChecked(false);
		m_cbCumulate.SetChecked(false);
		m_cbHeadline.Disable();
		m_cbCumulate.Disable();
	} 
	else {
		m_cbHeadline.Enable();
		m_cbCumulate.Enable();
		m_cbHeadline.SetChecked(m_fHeadLine);
		m_cbCumulate.SetChecked(m_fCumulate);
	}

	if (m_rbClipboard.GetState() || m_rbWindow.GetState()) {
		m_cboxDelim.ChangeCurrentIndex(0);		// Tabulator
		m_cboxDelim.Disable();
	} 
	else if (1 == m_pParent -> GetCountSelectedProps()) {
		m_cboxDelim.SetText("");
		m_cboxDelim.ChangeCurrentIndex(-1);
		m_cboxDelim.Disable();
	} 
	else
		m_cboxDelim.Enable();
}

bool CGenerateObjectPropertiesOptionsDlg::ShowSaveAsDlg()
{
// ggf. Voreinstellungen berechnen
os_string strPath, strName;

	if (m_sleSelFile.GetTextLen() > 0) {
	char cbBuffer[_MAX_PATH];

		m_sleSelFile.GetText(cbBuffer, sizeof(cbBuffer));

	os_path path = os_string(cbBuffer);

		strName = path.filename();
		strPath = path.file_path();
	}

// Dialog anzeigen
CSaveAsDialog SFDlg (this, (char *)ResString (IDS_OBJPROPFILETEMPLATE, 80).Addr());

	if (IsWin40()) {
		SFDlg.AddFlags (OFN_EXPLORER);
#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50())) {
			SFDlg.AddFlags (OFN_ENABLESIZING);
#if defined(OFN_DONTADDTORECENT)
			SFDlg.AddFlags(OFN_DONTADDTORECENT);
#endif // defined(OFN_DONTADDTORECENT)
		}
#endif // defined(OFN_ENABLESIZING)
	}
	SFDlg.AddFlags (OFN_LONGNAMES);
	if (strName.size() > 0)
		SFDlg.SetFileName(strName.c_str());
	if (strPath.size() > 0)
		SFDlg.SetInitialDir(strPath.c_str());

char cbBuffer[_MAX_PATH];

	if (SUCCEEDED(m_pParent -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL)))
		SFDlg.SetCaption(cbBuffer);	
	if (!SFDlg.Show()) 
		return false;

int iLen = SFDlg.GetFileNameLen();

	iLen = min(sizeof(cbBuffer), (UINT)iLen);
	SFDlg.GetFileName (cbBuffer, iLen);
	m_iFileType = SFDlg.GetFilterIndex();
	if (m_iFileType <= 0 || m_iFileType > 2)
		m_iFileType = 1;	// default: *.opr

	m_sleSelFile.SetText (cbBuffer);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesOptionsDlg message handlers

void CGenerateObjectPropertiesOptionsDlg::WindowInit (Event e)
{
// Controls initialisieren
CEierUhr Wait (this);		// EierUhr anzeigen

	m_cbHeadline.FInit();
	m_cbCumulate.FInit();
	m_cbProps.FInit();
	m_cbCounter.FInit();
	m_rbClipboard.FInit();
	m_rbWindow.FInit();
	m_rbFile.FInit();
	m_rbProperty.FInit();
	m_pbSelFile.FInit();
	m_sleSelFile.FInit();
	m_Property.FInit();
	m_cboxDelim.FInit();

// was soll ausgegeben werden
	m_cbHeadline.SetChecked (m_fHeadLine);
	m_cbCumulate.SetChecked (m_fCumulate);
	m_cbCounter.SetChecked (m_fCounter);
	m_cbProps.SetChecked (m_fProps);

// Trennzeichen vorbereiten
ResourceFile RF (g_pDLLName);
ResString resDelSpace (ResID(IDS_DELIMITER_SPACE, &RF), 32);
ResString resDelComma (ResID(IDS_DELIMITER_COMMA, &RF), 32);
ResString resDelSemicolon (ResID(IDS_DELIMITER_SEMICOLON, &RF), 32);
ResString resDelTabulator (ResID(IDS_DELIMITER_TABULATOR, &RF), 32);
ResString resNoDelimiter (ResID(IDS_DELIMITER_NODELIMITER, &RF), 32);

	m_cboxDelim.AddString(resDelTabulator);	// 0
	m_cboxDelim.AddString(resDelSpace);		// 1
	m_cboxDelim.AddString(resDelComma);		// 2
	m_cboxDelim.AddString(resDelSemicolon);	// 3
	m_cboxDelim.AddString(resNoDelimiter);	// 4

	switch (m_cDelimiter) {
	case '\t':
		m_cboxDelim.ChangeCurrentIndex(0);
		break;

	case ' ':
		m_cboxDelim.ChangeCurrentIndex(1);
		break;

	case ',':
		m_cboxDelim.ChangeCurrentIndex(2);
		break;

	case ';':
		m_cboxDelim.ChangeCurrentIndex(3);
		break;

	case '\0':
		m_cboxDelim.ChangeCurrentIndex(4);
		break;

	default:
		{
		char cbBuffer[2] = { m_cDelimiter, '\0' };

			m_cboxDelim.ChangeCurrentIndex(-1);
			m_cboxDelim.SetText(cbBuffer);
		}
		break;
	}

// wohin soll's gehen
	m_rbClipboard.SetState(false);
	m_rbWindow.SetState(false);
	m_rbFile.SetState(false);
	m_rbProperty.SetState(false);
	
	switch (m_rgDest) {
	case OBJPROPDEST_Clipboard:
		m_rbClipboard.SetState(true);
		break;

	case OBJPROPDEST_Window:
		m_rbWindow.SetState(true);
		break;

	case OBJPROPDEST_FileCsv:
	case OBJPROPDEST_FileOpr:
		m_rbFile.SetState(true);
		m_sleSelFile.SetText(m_strFileName.c_str());		// alten Dateinamen voreinstellen
		break;

	case OBJPROPDEST_Property:
		m_rbProperty.SetState(true);
		m_Property.InitFromData(m_strObjPropName.c_str());	// alte Objekteigenschaft voreinstellen
		break;
	}

	AdjustControls();
	AdjustSheetButtons();
}

int CGenerateObjectPropertiesOptionsDlg::OnWizBack (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return (m_pParent -> GetCountSelectedProps() > 1) ? 0 : IDD_GENERATEOBJECTPROPERTIES_SELECTPROPS;
	return -1;
}

int CGenerateObjectPropertiesOptionsDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CGenerateObjectPropertiesOptionsDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CGenerateObjectPropertiesOptionsDlg::OnSetActive (NotifyEvt e)
{
	AdjustControls();
	AdjustSheetButtons();
	return 0;
}

void CGenerateObjectPropertiesOptionsDlg::ButtonClick (ControlEvt e)
{
unsigned int uiID = (uint)e.GetControlID();

	switch (uiID) {
	case IDR_OBJPROPWINDOW:
		if (m_rbWindow.GetState())
			m_cbHeadline.SetChecked(true);

		m_cbHeadline.Enable();
		m_cbHeadline.SetChecked(true);				// Überschrift sollte da sein
		if (!IsWindowEnabled(m_cbCumulate.Handle(API_WINDOW_HWND))) {
			m_cbCumulate.Enable();
			m_cbCumulate.SetChecked(m_fCumulate);
		}
		m_cboxDelim.ChangeCurrentIndex(0);			// Tabulator
		m_cboxDelim.Disable();
		AdjustSheetButtons();
		break;

	case IDR_OBJPROPCLIPBOARD:
		if (m_rbClipboard.GetState()) {
			m_cboxDelim.ChangeCurrentIndex(0);		// Tabulator
			m_cboxDelim.Disable();
		} 
		m_cbHeadline.Enable();
		m_cbCumulate.Enable();
		m_cbHeadline.SetChecked(m_fHeadLine);
		m_cbCumulate.SetChecked(m_fCumulate);
		AdjustSheetButtons();
		break;

	case IDR_OBJPROPFILE:
		if (m_rbFile.GetState())
			m_sleSelFile.SetFocus();

		m_cbHeadline.Enable();
		m_cbCumulate.Enable();
		m_cbHeadline.SetChecked(m_fHeadLine);
		m_cbCumulate.SetChecked(m_fCumulate);
		if (m_pParent -> GetCountSelectedProps() > 1)
			m_cboxDelim.Enable();
		else {
			m_cboxDelim.SetText("");
			m_cboxDelim.ChangeCurrentIndex(-1);
			m_cboxDelim.Disable();
		}
		AdjustSheetButtons();
		break;

	case IDR_OBJPROPMCODE:
		if (m_rbProperty.GetState()) {
			m_fHeadLine = m_cbHeadline.isChecked();
			m_fCumulate = m_cbCumulate.isChecked();
			m_cbHeadline.SetChecked(false);
			m_cbCumulate.SetChecked(false);
			m_cbHeadline.Disable();
			m_cbCumulate.Disable();
			m_Property.SetFocus();
		}
		if (m_pParent -> GetCountSelectedProps() > 1) {
			m_cboxDelim.Enable();
			m_cboxDelim.ChangeCurrentIndex(2);		// Komma voreinstellen
		} else {
			m_cboxDelim.SetText("");
			m_cboxDelim.ChangeCurrentIndex(-1);
			m_cboxDelim.Disable();
		}
		AdjustSheetButtons();
		break;

	case IDC_OBJPROPFILE:
		if (ShowSaveAsDlg()) {
			m_cboxDelim.ChangeCurrentIndex((1 == m_iFileType) ? 0 : 2);		// Tabulator oder Komma
			m_rbFile.SetState (true);
			m_rbClipboard.SetState (false);
			m_rbWindow.SetState (false);
			m_rbProperty.SetState (false);

			AdjustSheetButtons();
		}
		break;

	case IDC_SELECT_OBJPROP:
		if (m_Property.ShowObjPropDlg()) {
			if (m_pParent -> GetCountSelectedProps() > 1) {
				m_cboxDelim.Enable();
				m_cboxDelim.ChangeCurrentIndex(2);		// Komma voreinstellen
			} else {
				m_cboxDelim.SetText("");
				m_cboxDelim.ChangeCurrentIndex(-1);
				m_cboxDelim.Disable();
			}
			m_rbProperty.SetState(true);
			m_rbFile.SetState (false);
			m_rbClipboard.SetState (false);
			m_rbWindow.SetState (false);

			AdjustSheetButtons();
		}
		break;
	}
}
