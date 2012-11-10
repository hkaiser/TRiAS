// FlAbgleichDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "FlAbgleichDlg.h"

#include "SetZW_PG1GB.h"
#include "SetZW_PG2D.h"
#include "SetZW_PG2H.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase* g_pDatabase;
extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CFlAbgleichDlg dialog


CFlAbgleichDlg::CFlAbgleichDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlAbgleichDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlAbgleichDlg)
	m_iAnzahlGS = 0;
	m_iAnzahlGeb = 0;
	m_iAnzahlDT = 0;
	m_iAnzahlVF = 0;
	//}}AFX_DATA_INIT
	m_pdbZW_PG1GB = NULL;
	m_pdbZW_PG2D  = NULL;
	m_pdbZW_PG2H  = NULL;
}

CFlAbgleichDlg::~CFlAbgleichDlg()
{
	if ( m_pdbZW_PG1GB )
	{
		if ( !m_pdbZW_PG1GB -> IsEOF() || !m_pdbZW_PG1GB -> IsBOF())
		{
			m_pdbZW_PG1GB -> MoveFirst();
			while ( m_iAnzahlGeb > 0 )
			{
				m_pdbZW_PG1GB -> Delete();
				if ( --m_iAnzahlGeb > 0 )
					m_pdbZW_PG1GB -> MoveNext();
			}
		}
	}
	if ( m_pdbZW_PG2D )
	{
		if ( !m_pdbZW_PG2D -> IsEOF() || !m_pdbZW_PG2D -> IsBOF())
		{
			m_pdbZW_PG2D -> MoveFirst();
			while ( m_iAnzahlDT > 0 )
			{
				m_pdbZW_PG2D -> Delete();
				if ( --m_iAnzahlDT > 0 )
					m_pdbZW_PG2D -> MoveNext();
			}
		}
	}
	if ( m_pdbZW_PG2H )
	{
		if ( !m_pdbZW_PG2H -> IsEOF() || !m_pdbZW_PG2H -> IsBOF())
		{
			m_pdbZW_PG2H -> MoveFirst();
			while ( m_iAnzahlVF > 0 )
			{
				m_pdbZW_PG2H -> Delete();
				if ( --m_iAnzahlVF > 0 )
					m_pdbZW_PG2H -> MoveNext();
			}
		}
	}

	if ( m_pdbZW_PG1GB )	delete m_pdbZW_PG1GB;
	if ( m_pdbZW_PG2D )		delete m_pdbZW_PG2D;
	if ( m_pdbZW_PG2H )		delete m_pdbZW_PG2H;
}


void CFlAbgleichDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlAbgleichDlg)
	DDX_Text(pDX, IDC_EDIT1, m_iAnzahlGS);
	DDX_Text(pDX, IDC_EDIT2, m_iAnzahlGeb);
	DDX_Text(pDX, IDC_EDIT3, m_iAnzahlDT);
	DDX_Text(pDX, IDC_EDIT4, m_iAnzahlVF);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlAbgleichDlg, CDialog)
	//{{AFX_MSG_MAP(CFlAbgleichDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlAbgleichDlg message handlers

BOOL CFlAbgleichDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_pdbZW_PG1GB = new CSetZW_PG1GB( g_pDatabase );
	m_pdbZW_PG2D  = new CSetZW_PG2D( g_pDatabase );
	m_pdbZW_PG2H  = new CSetZW_PG2H( g_pDatabase );

	if (( m_pdbZW_PG1GB == NULL ) ||
		( m_pdbZW_PG2D  == NULL ) ||
		( m_pdbZW_PG2H  == NULL ))
		return FALSE;

	m_pdbZW_PG1GB -> Open();
	m_pdbZW_PG2D  -> Open();
	m_pdbZW_PG2H  -> Open();

	while ( !m_pdbZW_PG1GB -> IsEOF())
	{
		m_iAnzahlGeb++;
		m_pdbZW_PG1GB -> MoveNext();
	}

	while ( !m_pdbZW_PG2D -> IsEOF())
	{
		m_iAnzahlDT++;
		m_pdbZW_PG2D -> MoveNext();
	}

	while ( !m_pdbZW_PG2H -> IsEOF())
	{
		m_iAnzahlVF++;
		m_pdbZW_PG2H -> MoveNext();
	}

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlAbgleichDlg::OnOK() 
{
	RewriteGeb();
	RewriteDT();
	RewriteVF();

	CDialog::OnOK();
}

void CFlAbgleichDlg::RewriteGeb()
{
	CSetNF_PG1GB		pg1gb;
	CMapStringToPtr		mapFertig;
	CString				strOldIDE, sql;
	void				*ptr;

	pg1gb.Open();
	if ( !pg1gb.CanUpdate() || !pg1gb.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Gebäude-Datenbank nicht möglich!" );
		pg1gb.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	TRY
	{
		if ( !m_pdbZW_PG1GB -> IsEOF() || !m_pdbZW_PG1GB -> IsBOF())
		{
			m_pdbZW_PG1GB -> MoveFirst();
			while ( !m_pdbZW_PG1GB -> IsEOF())
			{
				strOldIDE = m_pdbZW_PG1GB -> m_NFP1_IDE;
				if ( !mapFertig.Lookup( strOldIDE, ptr ))
				{
					sql = "DELETE FROM NF_PG1GB WHERE (NFP1_IDE = '";
					sql += strOldIDE;
					sql += "')";

					if ( g_iMessageStatus >= 3 )
						DEX_SetMessageString((const char*)sql );

					pg1gb.m_pDatabase -> ExecuteSQL( sql );

					if ( g_iMessageStatus >= 3 )
					{
						sql = "Gelöscht!";
						DEX_SetMessageString((const char*)sql );
					}

					mapFertig.SetAt( strOldIDE, (void*)1 );
				}

				m_pdbZW_PG1GB -> MoveNext();
			}
		}
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( sql, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( sql );
	}
	END_CATCH
/*
	if ( !m_pdbZW_PG1GB -> IsEOF() || !m_pdbZW_PG1GB -> IsBOF())
	{
		m_pdbZW_PG1GB -> MoveFirst();
		while ( !m_pdbZW_PG1GB -> IsEOF())
		{
			strOldIDE = m_pdbZW_PG1GB -> m_NFP1_IDE;
			if ( !pg1gb.IsEOF() || !pg1gb.IsEOF())
			{
				pg1gb.MoveFirst();
				while ( !pg1gb.IsEOF())
				{
					if ( pg1gb.m_NFP1_IDE == strOldIDE )
					{
						pg1gb.Delete();
						pg1gb.MoveNext();
					}
					else
					{
						if ( pg1gb.m_NFP1_IDE > strOldIDE )
							pg1gb.MoveLast();
						pg1gb.MoveNext();
					}
				}
			}
			erledigt = strOldIDE;
			if ( !m_pdbZW_PG1GB -> IsEOF() || !m_pdbZW_PG1GB -> IsBOF())
			{
				m_pdbZW_PG1GB -> MoveNext();
				strOldIDE = m_pdbZW_PG1GB -> m_NFP1_IDE;
				while (( strOldIDE == erledigt ) && !m_pdbZW_PG1GB -> IsEOF())
				{
					m_pdbZW_PG1GB -> MoveNext();
					strOldIDE = m_pdbZW_PG1GB -> m_NFP1_IDE;
				}
			}
		}
	}
*/

	// Dann komplett anfügen
	if ( !m_pdbZW_PG1GB -> IsEOF() || !m_pdbZW_PG1GB -> IsBOF())
	{
		m_pdbZW_PG1GB -> MoveFirst();
		while ( !m_pdbZW_PG1GB -> IsEOF())
		{
			pg1gb.AddNew();
			pg1gb.m_NFP1_IDE = m_pdbZW_PG1GB -> m_NFP1_IDE;
			pg1gb.m_NFP1_ANL = m_pdbZW_PG1GB -> m_NFP1_ANL;
			pg1gb.m_NFP1_GFL = m_pdbZW_PG1GB -> m_NFP1_GFL;
			pg1gb.m_NFP1_GNR = m_pdbZW_PG1GB -> m_NFP1_GNR;
			pg1gb.m_NFP1_HOH = m_pdbZW_PG1GB -> m_NFP1_HOH;
			pg1gb.m_NFP1_VOL = m_pdbZW_PG1GB -> m_NFP1_VOL;
			pg1gb.Update();
			m_pdbZW_PG1GB -> MoveNext();
		}
	}

	sql.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)sql );
}

void CFlAbgleichDlg::RewriteDT()
{
	CSetNF_PG2D			pg2d;
	CMapStringToPtr		mapFertig;
	CString				strOldIDE, sql;
	CString				text;
	void				*ptr;

	pg2d.Open();
	if ( !pg2d.CanUpdate() || !pg2d.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Dachflächen-Datenbank nicht möglich!" );
		pg2d.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	TRY
	{
		if ( !m_pdbZW_PG2D -> IsEOF() || !m_pdbZW_PG2D -> IsBOF())
		{
			m_pdbZW_PG2D -> MoveFirst();
			while ( !m_pdbZW_PG2D -> IsEOF())
			{
				strOldIDE = m_pdbZW_PG2D -> m_NFP2_IDE;
				if ( !mapFertig.Lookup( strOldIDE, ptr ))
				{
					sql = "DELETE FROM NF_PG2D WHERE (NFP2_IDE = '";
					sql += strOldIDE;
					sql += "')";

					if ( g_iMessageStatus >= 3 )
						DEX_SetMessageString((const char*)sql );

					pg2d.m_pDatabase -> ExecuteSQL( sql );

					if ( g_iMessageStatus >= 3 )
					{
						sql = "Gelöscht!";
						DEX_SetMessageString((const char*)sql );
					}

					mapFertig.SetAt( strOldIDE, (void*)1 );
				}

				m_pdbZW_PG2D -> MoveNext();
			}
		}
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( sql, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( sql );
	}
	END_CATCH
/*
	if ( !m_pdbZW_PG2D -> IsEOF() || !m_pdbZW_PG2D -> IsBOF())
	{
		m_pdbZW_PG2D -> MoveFirst();
		while ( !m_pdbZW_PG2D -> IsEOF())
		{
			strOldIDE = m_pdbZW_PG2D -> m_NFP2_IDE;
			if ( !pg2d.IsEOF() || !pg2d.IsBOF())
			{
				pg2d.MoveFirst();
				while ( !pg2d.IsEOF())
				{
					if ( pg2d.m_NFP2_IDE == strOldIDE )
					{
						pg2d.Delete();
						pg2d.MoveNext();
					}
					else
					{
						if ( pg2d.m_NFP2_IDE > strOldIDE )
							pg2d.MoveLast();
						pg2d.MoveNext();
					}
				}
			}
			erledigt = strOldIDE;
			if ( !m_pdbZW_PG2D -> IsEOF() || !m_pdbZW_PG2D -> IsBOF())
			{
				m_pdbZW_PG2D -> MoveNext();
				strOldIDE = m_pdbZW_PG2D -> m_NFP2_IDE;
				while (( strOldIDE == erledigt ) && !m_pdbZW_PG2D -> IsEOF())
				{
					m_pdbZW_PG2D -> MoveNext();
					strOldIDE = m_pdbZW_PG2D -> m_NFP2_IDE;
				}
			}
		}
	}
*/

	// Dann komplett anfügen
	if ( !m_pdbZW_PG2D -> IsEOF() || !m_pdbZW_PG2D -> IsBOF())
	{
		m_pdbZW_PG2D -> MoveFirst();
		while ( !m_pdbZW_PG2D -> IsEOF())
		{
			pg2d.AddNew();
			pg2d.m_NFP2_IDE = m_pdbZW_PG2D -> m_NFP2_IDE;
			pg2d.m_NFP2_ABF = m_pdbZW_PG2D -> m_NFP2_ABF;
			if ( TestYES( m_pdbZW_PG2D -> m_NFP2_ANS ))	text = "Y";
			else										text = "N";
			pg2d.m_NFP2_ANS = text;
			pg2d.m_NFP2_FLG = m_pdbZW_PG2D -> m_NFP2_FLG;
			pg2d.m_NFP2_FLN = m_pdbZW_PG2D -> m_NFP2_FLN;
			pg2d.Update();
			m_pdbZW_PG2D -> MoveNext();
		}
	}

	sql.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)sql );
}

void CFlAbgleichDlg::RewriteVF()
{
	CSetNF_PG2H			pg2h;
	CMapStringToPtr		mapFertig;
	CString				strOldIDE, sql;
	CString				text;
	void				*ptr;

	pg2h.Open();
	if ( !pg2h.CanUpdate() || !pg2h.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Versiegelungsflächen-Datenbank nicht möglich!" );
		pg2h.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	TRY
	{
		if ( !m_pdbZW_PG2H -> IsEOF() || !m_pdbZW_PG2H -> IsBOF())
		{
			m_pdbZW_PG2H -> MoveFirst();
			while ( !m_pdbZW_PG2H -> IsEOF())
			{
				strOldIDE = m_pdbZW_PG2H -> m_NFP2_IDE;
				if ( !mapFertig.Lookup( strOldIDE, ptr ))
				{
					sql = "DELETE FROM NF_PG2H WHERE (NFP2_IDE = '";
					sql += strOldIDE;
					sql += "')";

					if ( g_iMessageStatus >= 3 )
						DEX_SetMessageString((const char*)sql );

					pg2h.m_pDatabase -> ExecuteSQL( sql );

					if ( g_iMessageStatus >= 3 )
					{
						sql = "Gelöscht!";
						DEX_SetMessageString((const char*)sql );
					}

					mapFertig.SetAt( strOldIDE, (void*)1 );
				}

				m_pdbZW_PG2H -> MoveNext();
			}
		}
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( sql, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( sql );
	}
	END_CATCH
/*
	if ( !m_pdbZW_PG2H -> IsEOF() || !m_pdbZW_PG2H -> IsBOF())
	{
		m_pdbZW_PG2H -> MoveFirst();
		while ( !m_pdbZW_PG2H -> IsEOF())
		{
			strOldIDE = m_pdbZW_PG2H -> m_NFP2_IDE;
			if ( !pg2h.IsEOF() || !pg2h.IsBOF())
			{
				pg2h.MoveFirst();
				while ( !pg2h.IsEOF())
				{
					if ( pg2h.m_NFP2_IDE == strOldIDE )
					{
						pg2h.Delete();
						pg2h.MoveNext();
					}
					else
					{
						if ( pg2h.m_NFP2_IDE > strOldIDE )
							pg2h.MoveLast();
						pg2h.MoveNext();
					}
				}
			}
			erledigt = strOldIDE;
			if ( !m_pdbZW_PG2H -> IsEOF() || !m_pdbZW_PG2H -> IsBOF())
			{
				m_pdbZW_PG2H -> MoveNext();
				strOldIDE = m_pdbZW_PG2H -> m_NFP2_IDE;
				while (( strOldIDE == erledigt ) && !m_pdbZW_PG2H -> IsEOF())
				{
					m_pdbZW_PG2H -> MoveNext();
					strOldIDE = m_pdbZW_PG2H -> m_NFP2_IDE;
				}
			}
		}
	}
*/
	// Dann komplett anfügen
	if ( !m_pdbZW_PG2H -> IsEOF() || !m_pdbZW_PG2H -> IsBOF())
	{
		m_pdbZW_PG2H -> MoveFirst();
		while ( !m_pdbZW_PG2H -> IsEOF())
		{
			pg2h.AddNew();
			pg2h.m_NFP2_IDE = m_pdbZW_PG2H -> m_NFP2_IDE;
			pg2h.m_NFP2_ABF = m_pdbZW_PG2H -> m_NFP2_ABF;
			if ( TestYES( m_pdbZW_PG2H -> m_NFP2_ANS ))	text = "Y";
			else										text = "N";
			pg2h.m_NFP2_ANS = text;
			pg2h.m_NFP2_FLG = m_pdbZW_PG2H -> m_NFP2_FLG;
			pg2h.m_NFP2_FLN = m_pdbZW_PG2H -> m_NFP2_FLN;
			pg2h.Update();
			m_pdbZW_PG2H -> MoveNext();
		}
	}

	sql.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)sql );
}
