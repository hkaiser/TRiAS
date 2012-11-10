// Deklarationen: Dialog zu PropertyAction für Mengenoperationen von GeoObjekten
// File: SetsOperatDlg.h
// W. Mörtl

#ifndef _SETSOPERATDLG_H
#define _SETSOPERATDLG_H


#include "SmartInterfaces.h"


// Zustand des Dialogs
typedef struct tagSETSOPERATRESULT
{
	ObjOp OpMode;		// ausgewählte Objektoperation
	double dFuzzy;		// Fangbereich bei Linienvereinigung (in Meter)

} SETSOPERATRESULT;


///////////////////////////////////////////////////////////////////////////////////////////////
class CSetsOperatDlg : public CPropertyPage
{
private:
	DWORD m_dwFlags;

	RadioButton m_RBttnOr, m_RBttnAnd, m_RBttnXOr;
	FixedText m_TextFuzzy;		// beschreibender Text und
	DoubleNumEditX m_EditFuzzy;	//  Eingabefeld für den Fangbereich bei Linienvereinigung
	FixedText m_Descript;

	ObjOp m_OpMode;		// ausgewählte Objektoperation
	double m_dFuzzy;	// Fangbereich bei Linienvereinigung (in Meter)

	long m_lNumber[4];	// m_lNumber[0]: Anzahl der selektierten (markierten) Objekte
						// (ausschließlich dem aktivierten, d.h. blinkenden Objekt)
						// m_lNumber[1]: Anzahl der selektierten Flächen (einschl. der aktivierten Fläche)
						// m_lNumber[2]: Anzahl der selektierten Kanten (einschl. der aktivierten Kante)
						// m_lNumber[3]: Anzahl der selektierten Punkte (einschl. des aktivierten Punktes)
	bool m_bKnowOC;		// für die Ergebnisobjekte kann die Objektklasse der Ursprungsobjekte
						// genutzt werden (true)

	class CSetsOperatPropAct* m_pSOPA;

//	bool GetStartTolerances (void);
	bool m_fHasInitData;

protected:
// Konstruktor nicht direkt rufen
		CSetsOperatDlg (ResID uiRes, LPCSTR pcCaption, CSetsOperatPropAct* pSOPA,
						SETSOPERATRESULT caSelInfo);

	bool FInit (void);

// sonstige Member
	bool PrepareResult (void);

// EventHandler
	void WindowInit (Event);
	void ButtonClick (ControlEvt e);
	void EditFocusChg (EditFocusChgEvt e);
	void EditChange (ControlEvt e);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	LRESULT Dispatch (Event e);
	LRESULT OnSetMyMessage (void);
	int OnWizBack (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);
	void OnCancel (NotifyEvt);

public:
// Konstruktor/Destruktor/Initialisierung
		~CSetsOperatDlg (void);

static CSetsOperatDlg* CreateInstance (UINT uiDlg, LPCSTR pcCaption,
					 CSetsOperatPropAct* pSOPA, SETSOPERATRESULT caSelInfo, ResourceFile& rRF);

// die dem Dialog übergebenen Objekte bearbeiten
	HRESULT ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
							  IEnumLONG** ppEnumOut, IProgressIndicator2* pPI = 0);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (SETSOPERATRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (SETSOPERATRESULT* pSelInfo, bool& bIsDirty);

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }
};

const UINT WM_SETMYMESSAGE = WM_USER+1000;

#endif // _SETSOPERATDLG_H
