// $Header: /TRiAS/TRiAS/TRiAS03/ImportDataDlg.h 4     4.06.98 9:51 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/27/1998 10:23:24 AM
//
// @doc
// @module ImportDataDlg.h | PropertyActionDlg für Datenimport

#if !defined(_IMPORTDATADLG_H__BCA92A33_F530_11D1_8631_00600875138A__INCLUDED_)
#define _IMPORTDATADLG_H__BCA92A33_F530_11D1_8631_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// ExtensionFlag
typedef enum tagEXTENSIONFLAG {
	EF_Global = 0x01,
	EF_UnLoadable = 0x02,
	EF_Visible = 0x04,
	EF_CanImport = 0x08,
	EF_DynImportCfg = 0x10,
	EF_Aggregate = 0x20,
	EF_NoFlags = 0x00,
	EF_Flags = 0x1f,
} EXTENSIONFLAG;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ImportGeoData);		// WImportGeoData

/////////////////////////////////////////////////////////////////////////////
// Dialog, der Datenimport regelt

typedef struct tagIMPORTFILTERINFO {
	os_string m_strProgID;		// ProgID des Filters
	os_string m_strFilterName;	// Bezeichnung des ImportFilters
	os_string m_strShortName;	// Formatbezeichner
	os_string m_strFilterExt;	// StandardExtension der Ausgabedatei
} IMPORTFILTERINFO;

typedef struct tagIMPORTDATA {
	os_string m_strProgID;
	list<os_string> m_listNames;
	DWORD m_dwFlags;
	BOOL m_fShowErrors;
} IMPORTDATA;

typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;

class CImportDataDlg : 
	public CPropertyPage 
{
private:
	DWORD m_dwFlags;

	ComboBox m_cbDataFormat;
	SingleLineEdit m_sleFileName;
	PushButton m_pbSelectFile;
	CheckBox m_cbOemToAnsi;
	CheckBox m_cbGeometry;
	CheckBox m_cbRelations;
	CheckBox m_cbObjProps;
	CheckBox m_cbVisInfo;
	PushButton m_pbCoordSystem;
	PushButton m_pbConfig;

	list<os_string> m_Names;
	os_string m_strProgID;
	os_string m_strInitFile;
	os_string m_strInitDir;

	unsigned int m_fGeometry : 1;
	unsigned int m_fFeatures : 1;
	unsigned int m_fRelations : 1;
	unsigned int m_fVisualisation : 1;
	unsigned int m_fAnsiOem : 1;

	unsigned int m_fCanGeometry : 1;
	unsigned int m_fCanFeatures : 1;
	unsigned int m_fCanRelations : 1;
	unsigned int m_fCanVisualisation : 1;
	unsigned int m_fCanAnsiOem : 1;

	unsigned int m_fCanConfig : 1;
	unsigned int m_fMultiSel : 1;

	unsigned int m_fWndExists : 1;
	unsigned int m_fHasImportData : 1;

	unsigned int m_fShowErrors : 1;

	typedef list<pair<os_string, os_string> > CExtensions;
	CExtensions m_Exts;
	CExtensions::iterator m_it;

	WImportGeoData m_ImportExt;

protected:
// EventHandler
	void WindowInit (Event);
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);

	void OnSelChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

protected:
// Konstruktor nicht direkt rufen
		CImportDataDlg (ResID uiRes, LPCSTR pcCaption);

	bool FInit (ResourceFile &rRF);

// sonstige member
	bool PrepareResult (void);
	void AdjustOK (bool fDisableNext = false);

	DWORD GetImportFlags (void);
	void SetImportFlags (DWORD rgFlags, bool fInitActFlags = true);

	void InitControls();
	bool UpdateControls (CExtensions::iterator it, bool fInitFlags = true);
	bool LoadExtension (LPCSTR pcProgID, LPCSTR pcName, IImportGeoData **ppIImport);
	void UnLoadExtension (LPCSTR pcProgID, LPCSTR pcName);

	bool SelectImportFiles();

	os_string GetActualFilterString();
	HRESULT GetNamesAsEnum (IEnumString **ppIEnum);

public:
// Konstruktor/Destruktor/Initialisierung
		~CImportDataDlg (void);

static CImportDataDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, ResourceFile &rRF);

// Ergebnisse abfragen und bearbeiten
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetImportInfo (IMPORTDATA *pSelInfo);
	HRESULT GetNextEnumLONG (IEnum<LONG> **ppIEnum);
	bool GetFileNames(list<os_string> &rNames);

	bool AddImportExtension (LPCSTR pcName, LPCSTR pcDLLName);
	LRESULT OnWmInitDialog (HWND hDlg, HWND hDlgP);

// Flags behandeln
	bool FImportGeometry (void) { return m_fGeometry ? true : false; }
	bool FImportFeatures (void) { return m_fFeatures ? true : false; }
	bool FImportRelations (void) { return m_fRelations ? true : false; }
	bool FImportVisualisation (void) { return m_fVisualisation ? true : false; }
	bool FImportAnsiOem (void) { return m_fAnsiOem ? true : false; }

	void SetGeometry (bool fFlag) { m_fGeometry = fFlag ? true : false; }
	void SetFeatures (bool fFlag) { m_fFeatures = fFlag ? true : false; }
	void SetRelations (bool fFlag) { m_fRelations = fFlag ? true : false; }
	void SetVisualisation (bool fFlag) { m_fVisualisation = fFlag ? true : false; }
	void SetAnsiOem (bool fFlag) { m_fAnsiOem = fFlag ? true : false; }

	bool FCanGeometry (void) { return m_fCanGeometry ? true : false; }
	bool FCanFeatures (void) { return m_fCanFeatures ? true : false; }
	bool FCanRelations (void) { return m_fCanRelations ? true : false; }
	bool FCanVisualisation (void) { return m_fCanVisualisation ? true : false; }
	bool FCanAnsiOem (void) { return m_fCanAnsiOem ? true : false; }

	void SetCanGeometry (bool fFlag) { m_fCanGeometry = fFlag ? true : false; }
	void SetCanFeatures (bool fFlag) { m_fCanFeatures = fFlag ? true : false; }
	void SetCanRelations (bool fFlag) { m_fCanRelations = fFlag ? true : false; }
	void SetCanVisualisation (bool fFlag) { m_fCanVisualisation = fFlag ? true : false; }
	void SetCanAnsiOem (bool fFlag) { m_fCanAnsiOem = fFlag ? true : false; }

	bool FCanConfig (void) { return m_fCanConfig ? true : false; }
	void SetCanConfig (bool fFlag) { m_fCanConfig = fFlag ? true : false; }

	bool FMultiSel (void) { return m_fMultiSel ? true : false; }
	void SetMultiSel (bool fFlag) { m_fMultiSel = fFlag ? true : false; }
};

#endif // !defined(_IMPORTDATADLG_H__BCA92A33_F530_11D1_8631_00600875138A__INCLUDED_)
