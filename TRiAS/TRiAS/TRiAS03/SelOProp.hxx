// Auswahl einer Objekteigenschaft und Klassifikation von Objekten nach dieser
// File: SELOPROP.HXX

#if !defined(_SELOPROP_HXX)
#define _SELOPROP_HXX

#include "seloprpt.hxx"

///////////////////////////////////////////////////////////////////////////////
// Dialog, der Objekteigenschaft abfragt 

typedef tagOBJPROPRESULT {
	string m_strObjProp;
} OBJPROPRESULT;

class CClassifyDlg : 
	public CPropertyPage 
{
private:
	DWORD m_dwFlags;

	RadioButton m_rbEqual;
	RadioButton m_rbExists;
	class CSelObjPropTree *m_pObjProps;

// alle registrierten Objekteigenschaften
	WObjectProps m_ObjProps;

// Listen der vorhandenen Objekteigenschaften/ObjektGruppen
	typedef map<os_string, LONG, less<os_string> > CProperties;
	typedef multimap<os_string, LONG, less<os_string> > CDupObjects;
	CProperties m_Props;
	CProperties::const_iterator m_PropIt;
	CDupObjects m_DupObjs;

	unsigned int m_fEqual : 1;
	unsigned int m_fExists : 1;
	os_string m_strObjProp;

protected:
// EventHandler
	void ButtonClick (ControlEvt);
	void WindowInit (Event);

	void OnSelChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

protected:
// Konstruktor nicht direkt rufen
		CClassifyDlg (ResID uiRes, LPCSTR pcCaption, DWORD dwFlags, IObjectProps *pIObjProp);

	bool FInit (ResourceFile &rRF);

// sonstige member
	bool PrepareResult (void);
	void AdjustOK (bool fDisableNext = false);
	
public:
// Konstruktor/Destruktor/Initialisierung
		~CClassifyDlg (void);

static CClassifyDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
			DWORD dwFlags, ResourceFile &rRF, IObjectProps *pIObjProps);

// Ergenisse abfragen und bearbeiten
	HRESULT SetEnumLONG (IEnum<LONG> *pInEnum);
	HRESULT GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr);
	bool GetObjProp (os_string &rstr) { rstr = m_strObjProp; return true; }
};

#endif // _SELOPROP_HXX
