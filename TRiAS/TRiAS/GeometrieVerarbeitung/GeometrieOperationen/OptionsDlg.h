// Deklarationen: Dialog für Optionen der Objektoperationen
// File: OptionsDlg.h
// W. Mörtl

#ifndef _OPTIONSDLG_H
#define _OPTIONSDLG_H


#include "SmartInterfaces.h"


// Zustand des Dialogs
typedef struct tagOPTIONSRESULT
{
	BOOL bFeat;			// Merkmale der Originalobjekte sollen übernommen werden (true)
	BOOL bDelete;		// Originalobjekte sollen gelöscht werden (true)
	BOOL bMark;			// Originalobjekte sollen markiert werden (true)
	BOOL bShowNew;		// neue Objekte sollen angezeigt werden (true)
	BOOL bShowOrig;		// Originalobjekte sollen angezeigt werden (true)
} OPTIONSRESULT;


///////////////////////////////////////////////////////////////////////////////////////////////
class COptionsDlg : public CPropertyPage
{
private:
	DWORD m_dwFlags;

	CheckBox m_CBoxFeature, m_CBoxDelete, m_CBoxMark;
	CheckBox m_CBoxShowNew, m_CBoxShowOrig;
	FixedText m_Descript;

	OPTIONSRESULT m_OR;	// die ausgewählten Optionen

protected:
// Konstruktor nicht direkt rufen
		COptionsDlg (ResID uiRes, LPCSTR pcCaption, OPTIONSRESULT caSelInfo);

	bool FInit (void);

// sonstige Member
	void PrepareResult (void);

// EventHandler
	void WindowInit (Event);
	void ButtonClick (ControlEvt e);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	int OnWizBack (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

public:
// Konstruktor/Destruktor/Initialisierung
		~COptionsDlg (void);

static COptionsDlg* CreateInstance (UINT uiDlg, LPCSTR pcCaption, OPTIONSRESULT caSelInfo,
									ResourceFile& rRF);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (OPTIONSRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (OPTIONSRESULT* pSelInfo, bool& bIsDirty);

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }
};

#endif // _OPTIONSDLG_H
