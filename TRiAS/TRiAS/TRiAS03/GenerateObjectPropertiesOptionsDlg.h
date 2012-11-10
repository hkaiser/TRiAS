// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 17:38:25
//
// @doc
// @module GenerateObjectPropertiesOptionsDlg.h | Declaration of the <c CGenerateObjectPropertiesOptionsDlg> class

#if !defined(_GENERATEOBJECTPROPERTIESOPTIONSDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
#define _GENERATEOBJECTPROPERTIESOPTIONSDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include "SelectObjectProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesOptionsDlg dialog
class CGenerateObjectProperties;

class CGenerateObjectPropertiesOptionsDlg : 
	public CPropertyPage
{
// Construction
public:
	CGenerateObjectPropertiesOptionsDlg(CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption);
	~CGenerateObjectPropertiesOptionsDlg();

	BOOL FInit (void);
	HRESULT PrepareResult (void);
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

// Dialog Data
	enum { IDD = IDD_GENERATEOBJECTPROPERTIES_OPTIONS };

// Overrides
	void WindowInit (Event e);
	int OnSetActive (NotifyEvt e);
	int OnWizBack (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);

	void ButtonClick (ControlEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CGenerateObjectPropertiesOptionsDlg *CreateInstance (CGenerateObjectProperties *pParent, LPCSTR pcCaption);

	enum OBJPROPDEST {
		OBJPROPDEST_Clipboard = 1,
		OBJPROPDEST_Window = 2,
		OBJPROPDEST_Property = 3,
		OBJPROPDEST_File = 4,
		OBJPROPDEST_FileOpr = 4,
		OBJPROPDEST_FileCsv = 5,
	};

// Einstellungen lesen
	bool HasHeadline() { return m_fHeadLine; }
	bool HasCumulate() { return m_fCumulate; }
	bool HasCounter() { return m_fCounter; }
	bool HasProps() { return m_fProps; }
	OBJPROPDEST GetDestination() { return m_rgDest; }
	os_string GetFileName() { _ASSERTE(OBJPROPDEST_File <= GetDestination()); return m_strFileName; }
	os_string GetPropName() { _ASSERTE(OBJPROPDEST_Property == GetDestination()); return m_strObjPropName; }
	char GetDelimiter() { return m_cDelimiter; }

// Einstellungen voreinstellen
	void SetHeadline(bool fFlag) { m_fHeadLine = fFlag; }
	void SetCumulate(bool fFlag) { m_fCumulate = fFlag; }
	void SetCounter (bool fFlag) { m_fCounter = fFlag; }
	void SetProps (bool fFlag) { m_fProps = fFlag; }

	void SetFileName (LPCSTR pcFileName) { m_strFileName = pcFileName; }
	void SetFileType (OBJPROPDEST rgDest) 
	{ 
		_ASSERTE(OBJPROPDEST_FileOpr == rgDest || OBJPROPDEST_FileCsv == rgDest);
		m_iFileType = rgDest - OBJPROPDEST_File + 1;
	}
	void SetPropName (LPCSTR pcPropName) { m_strObjPropName = pcPropName; }
	void SetDelimiter (char cDel) { m_cDelimiter = cDel; }

	void SetDestination (OBJPROPDEST rgDest) { m_rgDest = rgDest; }
	
// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	void AdjustControls();
	OBJPROPDEST CalcDestination();

	bool ShowSaveAsDlg();

private:
	DWORD m_dwFlags;
	CGenerateObjectProperties *m_pParent;

	bool m_fHeadLine;
	bool m_fCumulate;
	bool m_fProps;
	bool m_fCounter;

	OBJPROPDEST m_rgDest;
	int m_iFileType;
	os_string m_strObjPropName;
	os_string m_strFileName;
	char m_cDelimiter;

// Controls
	CheckBox m_cbHeadline;
	CheckBox m_cbCumulate;
	CheckBox m_cbProps;
	CheckBox m_cbCounter;

	RadioButton m_rbClipboard;
	RadioButton m_rbWindow;
	RadioButton m_rbFile;
	RadioButton m_rbProperty;

	PushButton m_pbSelFile;
	SingleLineEdit m_sleSelFile;
	CSelectObjectProperty m_Property;

	ComboBox m_cboxDelim;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_GENERATEOBJECTPROPERTIESOPTIONSDLG_H__6B9FAEB2_AE46_46C5_8EC5_2CC2368B6409__INCLUDED_)
