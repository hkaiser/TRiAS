// $Header: /TRiAS/TRiAS/TRiAS03/GenTextDlg.h 3     4.06.98 9:50 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/01/1998 12:34:58 PM
//
// @doc
// @module GenTextDlg.h | PropertyAction: Textobjekte generieren

#if !defined(_GENTEXTDLG_H__51976423_F91C_11D1_8639_00600875138A__INCLUDED_)
#define _GENTEXTDLG_H__51976423_F91C_11D1_8639_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <bmpbtn.hxx>
#include "propactb.hxx"	// JG 980914

///////////////////////////////////////////////////////////////////////////////
// PropertyPage für Textobjekte erzeugen
typedef list<os_string> CDirectTextList;		// Liste der zuletzt eingegebenen Texte

/////////////////////////////////////////////////////////////////////////////
// Predikat testet auf gültige Objektnummer
//inline
class TextIsValidONr :
	public unary_function<LONG, bool>
{
public:
	bool operator() (LONG lONr) { return (-1L != lONr && 0L != lONr) ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces et.al.

#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

#if !defined(_DEFINED_ENUMLONG)
#define _DEFINED_ENUMLONG
DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator(LONG);		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
#endif // CIID_LONGEnum
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIteratorIf(LONG, TextIsValidONr);		// definiert OutEnumIfLONG für gültige Objektnummern

///////////////////////////////////////////////////////////////////////////////
// sonstige Typdefinitionen
typedef list<os_string> CDirectTextList;

class CGenTextDlg : 
	public CPropertyPage,
	public CPropertyActionExtUsage	   // JG980914 
{
private:
	class CGenTextPropAct *m_pParent;

	RadioButton m_rbFromObjProp;
	SingleLineEdit m_sleObjProp;
	CBmpButton m_SelObjProp;

	RadioButton m_rbDirectText;
	ComboBox m_cbDirectText;

	CheckBox m_cbDependend;
	FixedText m_ftDepOption;
	RadioButton m_rbDelete;
	RadioButton m_rbReplace;

	CheckBox m_cbDynamic;
	CheckBox m_cbRotate;
	CheckBox m_cbDoNotMove;
	CheckBox m_cbOnlyExistant;
	CheckBox m_cbDeleteTarget;

	DWORD m_dwFlags;
	BOOL m_fIsInitialized;

	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge

// zu Controls gehörende Variablen
	WObjectProps m_Props;
	WObjectProperty m_ObjProp;

protected:
	void WindowInit (Event);
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);
	void ListBoxSel (ControlEvt);

	int OnSetActive (NotifyEvt);
	void OnCancel (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

	BOOL FInit (void) { return true; }
	BOOL ShowRegExprMenu (void);
	BOOL ShowObjPropDlg (void);

	void AdjustControls(BOOL fFromOP, BOOL fDependend);
	HRESULT RetrieveObjProp (LPCSTR, IObjectProps *pIProps, IObjectProperty **ppIOP);

	void PrepareResult (void);
	BOOL AdjustOK (void);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

	HRESULT ResetEnumLONG (void);
	HRESULT GetEnumLONG (HPROJECT hPr, IEnum<LONG> **ppIEnumObjs);
	HRESULT SetEnumLONG (IEnum<LONG> *pIEnumObjs);
	HRESULT GetSelectedProperty (IObjectProperty **ppIOP);

public:
		CGenTextDlg (CGenTextPropAct *pParent, ResID uiDlg, LPCSTR pcCaption);
		~CGenTextDlg (void);

static CGenTextDlg *CreateInstance (CGenTextPropAct *pParent, ResID uiDlg, LPCSTR pcCaption);

public:
// Statusvariablen für Persistenz
	class CDlgStatus {
	public:
		BOOL m_fFromObjProp;
		BOOL m_fDependend;
		BOOL m_fDelete;
		BOOL m_fRotate;
		BOOL m_fDoNotMove;
		BOOL m_fDynamic;
		BOOL m_fOnlyExistant;
		BOOL m_fDeleteTarget;
		CComBSTR m_bstrDataSource;
		
		os_string m_strObjProp;
		os_string m_strDirectText;
		CDirectTextList m_lstDirectText;

		void erase (void) 
		{ 
			m_lstDirectText.clear(); 
			m_fFromObjProp = m_fDependend = m_fDelete = false;
			m_fRotate = m_fDoNotMove = m_fDynamic = false;
			m_fOnlyExistant = m_fDeleteTarget = false;
		}

		CDlgStatus (void) 
		{
			erase();
		}
	};
	HRESULT InitWithData (CGenTextDlg::CDlgStatus &rStatus);

private:
	CDlgStatus *m_pStatus;
};

#define MAXLASTITEMS	20		// Anzahl der gespeicherten letzten Suchstrings

#endif // !defined(_GENTEXTDLG_H__51976423_F91C_11D1_8639_00600875138A__INCLUDED_)
