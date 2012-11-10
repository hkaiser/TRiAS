// Dialog, welcher Objekteigenschaft etc. auswählt, um Texte zu erzeugen
// File: CREATEXT.HXX

#if !defined(_CREATEXT_HXX)
#define _CREATEXT_HXX

#include "SelObjProp.h"

class CCreateTextObjectsDlg 
	: public CPropertyPage 
{ 
private:
	DWORD m_dwFlags;

	CSelObjPropTree *m_pProps;
	CheckBox m_cbCreateDependend;
	RadioButton m_rbDeleteExistent;
	RadioButton m_rbReplaceExistent;
	CheckBox m_cbDoNotMove;

	os_string m_strObjProp;		// Resultate
	bool m_fCreateDependend;
	bool m_fDeleteExistent;
	bool m_fDoNotMove;

	WEnumObjectsByNumber EnumObjs;
	class CCreateTextObjectsPropAct *m_pParent;

	void AdjustOK (bool fDisableNext = false);

protected:
	void WindowInit (Event);

	void OnItemChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);
	void HelpRequest(HelpRequestEvt);

	bool PrepareResult (void);

// Konstruktor nicht direkt rufen
		CCreateTextObjectsDlg (CCreateTextObjectsPropAct *pParent, ResID uiRes, LPCSTR pcCaption);

	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CCreateTextObjectsDlg (void);
		
static CCreateTextObjectsDlg *CreateInstance (CCreateTextObjectsPropAct *pParent, ResID resID, 
										LPCSTR pcCaption);
	
	void SetFlags (DWORD dwFlags);

// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
// ZugriffsFunktionen auf ausgewählte Identifikatoren
	void SetObjProp (os_string strObjProp) { m_strObjprop = strObjProp; }
	void SetCreateDependend (bool fCreateDependend) { m_fCreateDependend = fCreateDependend; }
	void SetDeleteExistent (bool fDeleteExistent) { m_fDeleteExistent = fDeleteExistent; }
	void SetReplaceExistent (bool fDoNotMove) { m_fDoNotMove = fDoNotMove; }

	os_string GetObjProp (void) { return m_strObjProp; }
	bool GetCreateDependend (void) { return m_fCreateDependend; }
	bool GetDeleteExistent (void) { return m_fDeleteExistent; }
	bool GetDoNotMove (void) { return m_fDoNotMove; }

	HRESULT SetEnumLONG (IEnumObjectsByNumber *pIEnum);		// übergibt zu modifizierende Objektmenge
	HRESULT GetEnumLONG (IEnumObjectsByNumber **ppIEnum);	// Fragt den Dialog nach seinen Daten 

// Sonstiges
	void SetDirty (bool fDirty);
};

#endif // _CREATEXT_HXX

