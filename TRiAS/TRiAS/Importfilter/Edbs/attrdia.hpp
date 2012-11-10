///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			attrdia.hpp
//
//	Stand:			07.04.1995
//	Beschreibung:	Dialog zu Definition von TRiAS-Identifikatoren
//	Entwicklung:	07.04.95	Beginn der Kodierung
//					19.05.95	Umstellung auf CDefMMList
//////////////////////////////////////////////////////////////////////

#ifndef _ATTRDIA_HPP_
#define _ATTRDIA_HPP_

#if defined(_USE_CONFIG_DIALOGS)

#include "defmm.hpp"

class CAttributeDialog : public CDialog
{
	CMapStringToString	AttrMap, WertMap, BezMap;
	CMapStringToString	AttrWerteMap;
	CString				m_strStartIdent;
	CString				m_strCurrAttr;
	BOOL				m_modified;

	CDefMMList			m_AL, m_WL;

public:
	CMapStringToString	*pOrigAttrMap;
	CMapStringToString	*pOrigWertMap;

						CAttributeDialog( CWnd* = NULL );

	void				SetStartIdent( const char* );

	//{{AFX_DATA(CAttributeDialog)
	enum		{ IDD = IDD_EDBS_ATTR };
	//}}AFX_DATA

protected:
	virtual void	DoDataExchange( CDataExchange* pDX );
	virtual BOOL	OnInitDialog();
	void			InitWL();
	void			SaveWL();

	//{{AFX_MSG(CAttributeDialog)
	afx_msg void	OnOK();
	afx_msg void	OnCancel();
	afx_msg void	OnClickedDelAttribut();
	afx_msg void	OnClickedModAttribut();
	afx_msg void	OnEditAttrKode();
	afx_msg void	OnAuswahlAttrKode();
	afx_msg void	OnEditAttrBez();
	afx_msg void	OnClickedDelWert();
	afx_msg void	OnClickedModWert();
	afx_msg void	OnEditWertKode();
	afx_msg void	OnAuswahlWertKode();
	afx_msg void	OnEditWertBez();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _ATTRDIA_HPP_
