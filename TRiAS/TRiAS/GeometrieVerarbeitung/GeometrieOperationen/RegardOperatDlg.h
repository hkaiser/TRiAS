// Deklarationen: Dialog zu PropertyAction für Operationen von GeoObjekten mit Bezugsobjekt(en)
// File: RegardOperatDlg.h
// W. Mörtl

#ifndef _REGARDOPERATDLG_H
#define _REGARDOPERATDLG_H


#include "SmartInterfaces.h"


// Zustand des Dialogs
typedef struct tagREGOPERATRESULT
{
	BOOL bClassKey;	// neue Objekte übernehmen Objektklasse der Originalobjekte (true)
	BOOL bInter;	// neue Objekte sollen innerhalb (true)
	BOOL bExter;	//  außerhalb (true)
	BOOL bBound;	//  auf dem Rand der schneidenden Fläche liegen (true)
} REGOPERATRESULT;


///////////////////////////////////////////////////////////////////////////////////////////////
class CRegardOperatDlg : public CPropertyPage
{
private:
	DWORD m_dwFlags;

//	CheckBox m_CBoxClassKey;
	CheckBox m_CBoxInter, m_CBoxBound, m_CBoxExter;
	FixedText m_Location, m_Descript;

	bool m_bClassKey;	// neue Objekte übernehmen Objektklasse der Originalobjekte (true)
	bool m_bClassKeyEnable;	// m_CBoxClassKey ist Enable (true)
	bool m_bInter;		// neue Objekte sollen innerhalb (true)
	bool m_bExter;		//  außerhalb (true)
	bool m_bBound;		//  auf dem Rand der schneidenden Fläche liegen (true)

	long m_lRegObjONr;	// Objektnummer des Bezugsobjektes
	int m_iRegObjOT;	// Objekttyp des Bezugsobjektes

	class CRegOperatPropAct* m_pROPA;

protected:
// Konstruktor nicht direkt rufen
		CRegardOperatDlg (ResID uiRes, LPCSTR pcCaption, CRegOperatPropAct* pROPA,
						  REGOPERATRESULT caSelInfo);

	bool FInit (void);

// sonstige Member
	void PrepareResult (void);

// EventHandler
	void WindowInit (Event);
	void ButtonClick (ControlEvt);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	int OnWizBack (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

public:
// Konstruktor/Destruktor/Initialisierung
		~CRegardOperatDlg (void);

static CRegardOperatDlg* CreateInstance (UINT uiDlg, LPCSTR pcCaption,
				CRegOperatPropAct* pROPA, REGOPERATRESULT caSelInfo, ResourceFile& rRF);

// die dem Dialog übergebenen Objekte bearbeiten
	HRESULT ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
							  IEnumLONG** ppEnumOut, IProgressIndicator2* pPI = 0);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (REGOPERATRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (REGOPERATRESULT* pSelInfo, bool& bIsDirty);

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

	void SetRegObjectONr (long lONr) { m_lRegObjONr = lONr; }
	void SetRegObjectOT (int iOT) { m_iRegObjOT = iOT; }
};

#endif // _REGARDOPERATDLG_H
