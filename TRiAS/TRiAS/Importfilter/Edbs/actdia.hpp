///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			actdia.hpp
//
//	Stand:			08.12.1994
//	Beschreibung:	Import - Dialog
//	Entwicklung:	08.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef _ACTDIA_HPP_
#define _ACTDIA_HPP_

#if defined(_USE_CONFIG_DIALOGS)

class CActiDialog : public CDialog
{
public:
				CActiDialog( CWnd* = NULL );
	void		Open();
	void		Close();
	BOOL		Break()		{ return m_Break; }
	void		SetFileName( const char* );
	void		SetFileSize( const char* );
	void		SetFilePos( const char* );
	//{{AFX_DATA(CActiDialog)
	enum		{ IDD = IDD_DIALOG1 };
	//}}AFX_DATA

protected:
	BOOL			m_Break;
	virtual void	DoDataExchange( CDataExchange* pDX );

	//{{AFX_MSG(CActiDialog)
	afx_msg void	OnCancelClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _ACTDIA_HPP_
