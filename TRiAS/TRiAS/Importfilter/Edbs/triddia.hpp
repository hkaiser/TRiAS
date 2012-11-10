///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			triddia.hpp
//
//	Stand:			07.04.1995
//	Beschreibung:	Dialog zu Definition von TRiAS-Identifikatoren
//	Entwicklung:	07.04.95	Beginn der Kodierung
//					19.05.95	Umstellung auf CDefMMList
//////////////////////////////////////////////////////////////////////

#ifndef _TRIDDIA_HPP_
#define _TRIDDIA_HPP_

#if defined(_USE_CONFIG_DIALOGS)

#include "defmm.hpp"

class CTriasIdentDialog : public CDialog
{
	CMapStringToString	MerkmalMap;
	CString				m_strCaption;
	CString				m_strText1, m_strText2;
	CString				m_strStartIdent;
	short				m_iTestProc;

	CDefMMList			m_DL;

public:
	CMapStringToString	*pOriginalMap;

						CTriasIdentDialog( CWnd* = NULL );

	void				SetCaptText( const char* );
	void				SetText1( const char* );
	void				SetText2( const char* );
	void				SetStartIdent( const char* );
	void				SetTestProc( short i ) { m_iTestProc = i; }

	//{{AFX_DATA(CTriasIdentDialog)
	enum		{ IDD = IDD_TRIAS_ID };
	//}}AFX_DATA

protected:
	virtual void	DoDataExchange( CDataExchange* pDX );
	virtual BOOL	OnInitDialog();

	//{{AFX_MSG(CTriasIdentDialog)
	afx_msg void	OnClickedDelMerkmal();
	afx_msg void	OnClickedModMerkmal();
	afx_msg void	OnOK();
	afx_msg void	OnCancel();
	afx_msg void	OnEditIdentKode();
	afx_msg void	OnAuswahlIdentKode();
	afx_msg void	OnEditIdentBez();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _TRIDDIA_HPP_
