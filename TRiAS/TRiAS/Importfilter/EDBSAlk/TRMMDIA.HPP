///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trmmdia.hpp
//
//	Stand:			20.03.1995
//	Beschreibung:	Dialog zu Definition von TRiAS-Merkmalen
//	Entwicklung:	20.03.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef _TRMMDIA_HPP_
#define _TRMMDIA_HPP_

#if defined(_USE_CONFIG_DIALOGS)

class CTriasMerkmaleDialog : public CDialog
{
	CMapStringToString	MerkmalMap;
	BOOL				m_MMKgeaendert, m_MMBgeaendert;
	BOOL				m_bListeGeaendert;
	CString				m_strMerk;

public:
	CMapStringToString	*pOriginalMap;

						CTriasMerkmaleDialog( CWnd* = NULL );

	//{{AFX_DATA(CTriasMerkmaleDialog)
	enum		{ IDD = IDD_TRIAS_MM };
	//}}AFX_DATA

protected:
	virtual void	DoDataExchange( CDataExchange* pDX );
	virtual BOOL	OnInitDialog();
	BOOL			EingabeOK();

	//{{AFX_MSG(CTriasMerkmaleDialog)
	afx_msg void	OnClickedDelMerkmal();
	afx_msg void	OnClickedModMerkmal();
	afx_msg void	OnOK();
	afx_msg void	OnCancel();
	afx_msg void	OnEditMerkmalsKode();
	afx_msg void	OnAuswahlMerkmalsKode();
	afx_msg void	OnEditMerkmalsBez();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _TRMMDIA_HPP_
