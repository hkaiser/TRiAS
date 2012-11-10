///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			setupdlg.hpp
//
//	Stand:			20.02.1995
//	Beschreibung:	Setup - Dialog
//	Entwicklung:	20.02.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef	_SETUPDLG_HPP
#define _SETUPDLG_HPP

#if defined(_USE_CONFIG_DIALOGS)

class CSetupDialog : 
	public CDialog
{
	CMapStringToString		mapTRIAS_Ident;
	CMapStringToString		mapTRIAS_xIdent;
	CMapStringToString		mapTRIAS_MM;
	CMapStringToString		mapEDBS_Ident;
	CMapStringToString		mapArtTexte;
	CMapStringToString		mapAttribTexte;
	CMapStringToString		mapWertTexte;
	CMapStringToString		mapBedingungen;
	CMapStringToString		mapAlias;
	BOOL					m_bIgnoreUndef;
	CComboBox				*pCBIdent;

	BOOL					modified;

	BOOL					OnInitDialog();
	void					InitZuordnungsListe();
	CString					FindMMK( const char* );
	void					OnOKFrage();
	void					OnCancelFrage();

	BOOL					SaveFile( const char* );
	BOOL					TestFile( const char* );
	BOOL					LoadFile( const char* );
	void					ResetListen();

	afx_msg void			OnEditEdbsIdent();
	afx_msg void			OnAuswahlEdbsIdent();
	afx_msg void			OnAuswahlAttribut();
	afx_msg void			OnAuswahlAlias();

	afx_msg void			OnDefineObjArt();
	afx_msg void			OnDefineMerkmale();
	afx_msg void			OnDefineTriasIdent();
	afx_msg void			OnDefineAttribute();
	afx_msg void			OnDefineTriasXIdent();
	afx_msg void			OnIgnoreUndef();
	afx_msg void			OnSaveFile();
	afx_msg void			OnLoadFile();

	afx_msg virtual void	OnOK();
	afx_msg virtual void	OnCancel();

	DECLARE_MESSAGE_MAP()

public:
							CSetupDialog();
	BOOL					IsModified()	{ return modified; }
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _SETUPDLG_HPP
