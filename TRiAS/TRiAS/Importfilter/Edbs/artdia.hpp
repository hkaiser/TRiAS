///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			artdia.hpp
//
//	Stand:			01.06.1995
//	Beschreibung:	Dialog zur Zuordnung von EDBS- und TRiAS-Ident.
//	Entwicklung:	01.06.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef _ARTDIA_HPP_
#define _ARTDIA_HPP_

#if defined(_USE_CONFIG_DIALOGS)

#include "defmm.hpp"

class CArtDialog : public CDialog
{
	CMapStringToString	ArtTexteMap;
	CMapStringToString	TriasIdentMap;
	CMapStringToString	TriasXIdentMap;
	CMapStringToString	TriasMMMap;
	CMapStringToString	EdbsIdentMap;
	CMapStringToString	AttribTexteMap;
	CMapStringToString	WertTexteMap;
	CMapStringToString	AliasMap;
	CMapStringToString	BedingungenMap;
	CString				m_strStartIdent;
	CString				m_strCurrIdent;

	CDefMMList			m_DL;
	BOOL				m_modified;

public:
	CMapStringToString	*pmapArtTexte;
	CMapStringToString	*pmapTRIAS_Ident;
	CMapStringToString	*pmapTRIAS_xIdent;
	CMapStringToString	*pmapTRIAS_MM;
	CMapStringToString	*pmapEDBS_Ident;
	CMapStringToString	*pmapAttribTexte;
	CMapStringToString	*pmapWertTexte;
	CMapStringToString	*pmapBedingungen;
	CMapStringToString	*pmapAlias;

	CMapStringToString	*pmapLastMap;

						CArtDialog( CWnd* = NULL );

	void				SetStartIdent( const char* );

	//{{AFX_DATA(CArtDialog)
	enum		{ IDD = IDD_EDBS_ART };
	//}}AFX_DATA

protected:
	virtual void	DoDataExchange( CDataExchange* pDX );
	virtual BOOL	OnInitDialog();
	void			InitTriasIdents();
	void			CopyMap( CMapStringToString*, CMapStringToString* );
	void			EnableButton( int, BOOL = TRUE );
	BOOL			Modified();

	//{{AFX_MSG(CArtDialog)
	afx_msg void	OnClickedDelMerkmal();
	afx_msg void	OnClickedModMerkmal();
	afx_msg void	OnOK();
	afx_msg void	OnCancel();
	afx_msg void	OnEditIdentKode();
	afx_msg void	OnAuswahlIdentKode();
	afx_msg void	OnEditIdentBez();
	afx_msg void	OnChangeXMark();
	afx_msg void	OnAuswahlTriasIdent();
	afx_msg void	OnClickedDelBed();
	afx_msg void	OnClickedModBed();
	afx_msg void	OnClickedAdvBed();
	afx_msg void	OnClickedDelAlias();
	afx_msg void	OnClickedModAlias();
	afx_msg void	OnClickedAdvAlias();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _ARTDIA_HPP_
