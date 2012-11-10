// Select ObjectProperties from PopUpTree
// File: SelObjPropDlg.h

#if !defined(_SELOBJPROPDLG_H)
#define _SELOBJPROPDLG_H

#include <SelObjProp.h>

class _TRIAS03_ENTRY CSelObjPropsDlg 
	: public DialogWindow 
{
private:
	CSelObjPropTree m_ObjProps;
	string m_strSelected;
	string m_strSelectedFull;
	bool m_fInitializingOrDestroying;
	bool m_fSelected;

protected:
	void OnSelChanged (NotifyEvt);
	void ButtonClick (ControlEvt);
	LRESULT Dispatch (Event);
	void ReSize (ReSizeEvt);

	void AdjustParentImage (HTREEITEM hItem);

public:
		CSelObjPropsDlg (Window *pW, IObjectProps *pIObjProps, INCLUDEOBJPROP pFcn = IncludeObjProp);
		~CSelObjPropsDlg (void);

	bool FInit (LPCSTR pcSelect);
	void OnItemExpanded (NotifyEvt);

	void GetSelectedObjProp (string &rStr) { rStr = m_strSelected; }
	void GetSelectedFullName (string &rStr) { rStr = m_strSelectedFull; }
};

#endif // _SELOBJPROPDLG_H
