// Deklarationen: Dialog zu PropertyAction für Bilden von Flächen und Linien aus Linienelementen
// File: AreasBuildingDlg.h
// W. Mörtl

#ifndef _AREASBUILDINGDLG_H
#define _AREASBUILDINGDLG_H


#include "SmartInterfaces.h"


// Zustand des Dialogs
typedef struct tagAREABUILDRESULT
{
	BOOL bLines;	// Linienvereinigung der restlichen Linien (true)
	double dFuzzy;	// Fangbereich bei Linienvereinigung (in Meter)
} AREABUILDRESULT;


///////////////////////////////////////////////////////////////////////////////////////////////
class CAreasBuildingDlg : public CPropertyPage
{
private:
	DWORD m_dwFlags;

	CheckBox m_CBoxLines;		// Linien, die sich nicht zu Flächen vereinigen lassen, sollen
								// wenigstens zu größeren Linien vereinigt werden
	FixedText m_TextFuzzy;		// beschreibender Text und
	DoubleNumEditX m_EditFuzzy;	//  Eingabefeld für den Fangbereich bei Linienvereinigung
	FixedText m_Descript;

	bool m_bLines;				// Linienvereinigung der restlichen Linien (true)
	double m_dFuzzy;			// Fangbereich bei Linienvereinigung (in Meter)

	bool m_bKnowOC;				// für die Ergebnisobjekte kann die Objektklasse der
								// Ursprungsobjekte genutzt werden (true)

	class CAreaBuildPropAct* m_pABPA;

protected:
// Konstruktor nicht direkt rufen
		CAreasBuildingDlg (ResID uiRes, LPCSTR pcCaption, CAreaBuildPropAct* pABPA,
						   AREABUILDRESULT caSelInfo);

	bool FInit (void);

// sonstige Member
	void PrepareResult (void);

// EventHandler
	void WindowInit (Event);
	void ButtonClick (ControlEvt);
	void EditFocusChg (EditFocusChgEvt e);
	void EditChange (ControlEvt e);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	int OnWizBack (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

public:
// Konstruktor/Destruktor/Initialisierung
		~CAreasBuildingDlg (void);

static CAreasBuildingDlg* CreateInstance (UINT uiDlg, LPCSTR pcCaption,
					   CAreaBuildPropAct* pABPA, AREABUILDRESULT caSelInfo, ResourceFile& rRF);

// die dem Dialog übergebenen Objekte bearbeiten
	HRESULT ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
							  IEnumLONG** ppEnumOut, IProgressIndicator2* pPI = 0);
	HRESULT RestLinesUnion (HPROJECT hPr, IEnumLONG* pEnumIn, IEnumLONG* pEnumUsedA,
							bool bCopyFeat, VARIANT varPI, IEnumLONG** ppEnumUsedL,
							IEnumObjectsByNumber** ppEnumOutRest);
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (AREABUILDRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (AREABUILDRESULT* pSelInfo, bool& bIsDirty);

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }
};

#endif // _AREASBUILDINGDLG_H
