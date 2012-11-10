///////////////////////////////////////////////////////////////////////////
// @doc 
// @module SelOProp.h | Auswahl einer Objekteigenschaft und Klassifikation 
// von Objekten nach dieser

#if !defined(_SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_)
#define _SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <SelObjProp.h>

#include "propactb.hxx"	// JG
#include "SelectObjectProperty.h"

// Dialog, der Objekteigenschaft abfragt ------------------------------------------------

class CClsfyPropAct;

typedef struct tagOBJPROPRESULT {
	os_string m_strObjProp;
	size_t m_iCntMatch;
	BOOL m_fSelectAll;
	BOOL m_fIgnoreCase;
	BOOL m_fMatchBOB;
} OBJPROPRESULT;

class CClassifyDlg : 
	public CPropertyPage,
	public CPropertyActionExtUsage	   // JG980914
{
private:
	DWORD m_dwFlags;
	OBJPROPRESULT *m_pSelInfo;

	CSelectObjectProperty m_ObjPropSrc;
	CheckBox m_cbSelAll;
	CheckBox m_cbIgnoreCase;
	CheckBox m_cbMatchBOB;
	SingleLineEdit m_sleCnt;
	CSpinButtonCtrl m_Spin;
	
// alle registrierten Objekteigenschaften
	WObjectProps m_ObjProps;

// Listen der vorhandenen Objekteigenschaften/ObjektGruppen
	class CCompareForClassify :
		public os_less<os_string>
	{
	public:
		CCompareForClassify(size_t &rCnt, bool &fIgnoreCase) :
			m_riCmpCount(rCnt), m_rfIgnoreCase(fIgnoreCase)
		{
		}
		~CCompareForClassify() {}

		bool operator()(const os_string& x, const os_string& y) const 
		{
			return GetActualKey(x) < GetActualKey(y);
		}
		bool Equal (const os_string& x, const os_string& y) const 
		{
			return GetActualKey(x) == GetActualKey(y);
		}

		static os_string to_upper (os_string str) 
		{
			for (size_t i = 0; i < str.size(); ++i)
				toupper(str[i]);
			return str;
		}
		os_string GetActualKey (const os_string &rstr) const
		{
			if (m_rfIgnoreCase) {
			// Groß-/Kleinschreibung ignorieren
				if (m_riCmpCount > 0)
					return to_upper(rstr.substr (0, m_riCmpCount));

				return to_upper(rstr);
			} 
			else if (m_riCmpCount > 0)
				return rstr.substr(0, m_riCmpCount);
			return rstr;
		}

	private:
	// die folgenden Variablen sind Referenzen, da das VergleichsObjekt in den Baum
	// _kopiert_ wird!
		size_t &m_riCmpCount;		// 0 -> alles vergleichen
		bool &m_rfIgnoreCase;
	};

	typedef map<os_string, LONG, CCompareForClassify > CProperties;
	typedef multimap<os_string, LONG, CCompareForClassify > CDupObjects;

	CProperties m_Props;
	CProperties::const_iterator m_PropIt;
	CDupObjects m_DupObjs;

	size_t m_iCntMatch;
	bool m_fIgnoreCase;
	long m_lPacket;

	CClsfyPropAct *m_pParent;

protected:
// EventHandler
	void WindowInit (Event);

	void OnSelChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);
	void ButtonClick (ControlEvt e);
	void VertScroll (ScrollEvt e);
	void EditChange (ControlEvt e);

	BOOL GetDisableNextPage();

protected:
// Konstruktor nicht direkt rufen
		CClassifyDlg (CClsfyPropAct *pParent, ResID uiRes, LPCSTR pcCaption, IObjectProps *pIObjProp);

	bool FInit (ResourceFile &rRF);

// sonstige member
	bool PrepareResult (void);
	void AdjustOK (bool fDisableNext = false);
	void AdjustSelectedInfo();
	
public:
// Konstruktor/Destruktor/Initialisierung
		~CClassifyDlg (void);

static CClassifyDlg *CreateInstance (CClsfyPropAct *pParent, UINT uiDlg, LPCSTR pcCaption, 
			ResourceFile &rRF, IObjectProps *pIObjProps);

// Ergenisse abfragen und bearbeiten
	HRESULT SetEnumLONG (IEnum<LONG> *pInEnum);
	HRESULT GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr, long &rlPacket);
	
//	bool GetObjProp (os_string &rstr) { rstr = m_strObjProp; return true; }
//	bool GetSelectAll() { return m_fSelectAll; }

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (OBJPROPRESULT *pSelInfo, bool fNoShow = false);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }
};

#endif // !defined(_SELOPROP_H__8FB5DAD6_E4BD_11D1_8610_00600875138A__INCLUDED_)
