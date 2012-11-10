///////////////////////////////////////////////////////////////////////////
// @doc 
// @module SelOProp.h | Auswahl einer Objekteigenschaft und Klassifikation 
// von Objekten nach dieser

#if !defined(_SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_)
#define _SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SelOPrpTree.h"
#include "propactb.hxx"	// JG
// Dialog, der Objekteigenschaft abfragt ------------------------------------------------

typedef struct tagOBJPROPRESULT {
	os_string m_strObjProp;
	bool m_fSelectAll;
} OBJPROPRESULT;

class CClassifyDlg : 
	public CPropertyPage,
	public CPropertyActionExtUsage	   // JG980914
{
private:
	DWORD m_dwFlags;

	CSelectObjectPropTree *m_pObjProps;
	CheckBox m_cbSelAll;

// alle registrierten Objekteigenschaften
	WObjectProps m_ObjProps;

// Listen der vorhandenen Objekteigenschaften/ObjektGruppen
	typedef map<os_string, LONG, less<os_string> > CProperties;
	typedef multimap<os_string, LONG, less<os_string> > CDupObjects;

	CProperties m_Props;
	CProperties::const_iterator m_PropIt;
	CDupObjects m_DupObjs;

	os_string m_strObjProp;
	bool m_fSelectAll;

protected:
// EventHandler
	void WindowInit (Event);

	void OnSelChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

protected:
// Konstruktor nicht direkt rufen
		CClassifyDlg (ResID uiRes, LPCSTR pcCaption, IObjectProps *pIObjProp);

	bool FInit (ResourceFile &rRF);

// sonstige member
	bool PrepareResult (void);
	void AdjustOK (bool fDisableNext = false);
	void AdjustSelectedInfo();
	
public:
// Konstruktor/Destruktor/Initialisierung
		~CClassifyDlg (void);

static CClassifyDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
			ResourceFile &rRF, IObjectProps *pIObjProps);

// Ergenisse abfragen und bearbeiten
	HRESULT SetEnumLONG (IEnum<LONG> *pInEnum);
	HRESULT GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr);
	bool GetObjProp (os_string &rstr) { rstr = m_strObjProp; return true; }
	bool GetSelectAll() { return m_fSelectAll; }

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (OBJPROPRESULT *pSelInfo, bool fNoShow = false);
};

#endif // !defined(_SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_)
