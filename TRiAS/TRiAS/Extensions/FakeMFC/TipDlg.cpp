#include "fakemfcp.hxx"
#include "fakemfc.h"
// CG: This file added by 'Tip of the Day' component.

#include <registrx.hxx>
#include "tipdlg.h"

#include <winreg.h>
#include <sys\stat.h>
#include <sys\types.h>

#include "Strings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

#define MAX_BUFLEN 1000

extern char g_cbHelpPath[];			// Pfad, in dem DLL liegt

static const TCHAR szSection[] = _T("TipOfTheDay");
static const TCHAR szIntFilePos[] = _T("FilePos");
static const TCHAR szTimeStamp[] = _T("TimeStamp");

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTipDlg)
	m_bStartup = TRUE;
	m_strTip = _T("");
	//}}AFX_DATA_INIT

// We need to find out what the startup and file position parameters are
// If startup does not exist, we assume that the Tips on startup is checked TRUE.
UINT iFilePos = 0;
CString strStoredTime;

#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	CCurrentUser regTip (KEY_READ, g_cbRegSection);
	DWORD dwVal = 0;

		if (regTip.GetDWORD (g_cbIntStartup, dwVal))
			m_bStartup = dwVal ? true : false;
		if (regTip.GetDWORD (szIntFilePos, dwVal))
			iFilePos = dwVal;
	} 
#if defined(_USE_WIN32S_CODE)
	else {
	CWinApp* pApp = AfxGetApp();

		m_bStartup = !pApp->GetProfileInt (szSection, g_cbIntStartup, 0);
		iFilePos = pApp->GetProfileInt (szSection, szIntFilePos, 0);
	}
#endif // defined(_USE_WIN32S_CODE)

// Now try to open the tips file
CString strPath = g_cbHelpPath;

	strPath += _T("trias.tip");
	m_pStream = fopen(strPath, "r");
	if (m_pStream == NULL) {
		VERIFY(m_strTip.LoadString(CG_IDS_FILE_ABSENT));
		return;
	} 

// If the timestamp in the INI file is different from the timestamp of
// the tips file, then we know that the tips file has been modified
// Reset the file position to 0 and write the latest timestamp to the
// ini file
struct _stat buf;

	_fstat(_fileno(m_pStream), &buf);

	CString strCurrentTime = ctime(&buf.st_ctime);
	strCurrentTime.TrimRight();

#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	CCurrentUser regTip (g_cbRegSection, true);
	char *pT = strStoredTime.GetBuffer (_MAX_PATH);
	DWORD dwLen = _MAX_PATH;

		if (pT) regTip.GetSubSZ (szTimeStamp, pT, dwLen);
		strStoredTime.ReleaseBuffer();

		if (strcmp(strCurrentTime, strStoredTime)) {
			iFilePos = 0;
			regTip.SetSubSZ (szTimeStamp, strCurrentTime);
		}
	}
#if defined(_USE_WIN32S_CODE)
	else {
	CWinApp* pApp = AfxGetApp();

		strStoredTime = pApp->GetProfileString(szSection, szTimeStamp, NULL);
		if (strcmp(strCurrentTime, strStoredTime))	 {
			iFilePos = 0;
			pApp->WriteProfileString(szSection, szTimeStamp, strCurrentTime);
		}
	}
#endif // defined(_USE_WIN32S_CODE)

	if (fseek(m_pStream, iFilePos, SEEK_SET) != 0)
		VERIFY(m_strTip.LoadString(CG_IDP_FILE_CORRUPT));
	else
		GetNextTipString(m_strTip);
}

CTipDlg::~CTipDlg()
{
// This destructor is executed whether the user had pressed the escape key
// or clicked on the close button. If the user had pressed the escape key,
// it is still required to update the filepos in the ini file with the 
// latest position so that we don't repeat the tips! 

// But make sure the tips file existed in the first place....
	if (m_pStream != NULL) {
#if defined(_USE_WIN32S_CODE)
		if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
		{
		CCurrentUser regTip (g_cbRegSection, true);
		DWORD dwVal = ftell(m_pStream);

			regTip.SetDWORD (szIntFilePos, dwVal);
		}
#if defined(_USE_WIN32S_CODE)
		else {
		CWinApp* pApp = AfxGetApp();
		
			pApp->WriteProfileInt(szSection, szIntFilePos, ftell(m_pStream));
		}
#endif // defined(_USE_WIN32S_CODE)
		fclose(m_pStream);
	}
}
        
void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipDlg)
	DDX_Check(pDX, IDC_STARTUP, m_bStartup);
	DDX_Text(pDX, IDC_TIPSTRING, m_strTip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTipDlg, CDialog)
	//{{AFX_MSG_MAP(CTipDlg)
	ON_BN_CLICKED(IDC_NEXTTIP, OnNextTip)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipDlg message handlers

void CTipDlg::OnNextTip()
{
	GetNextTipString(m_strTip);
	UpdateData(FALSE);
}

// Konvertieren der EscapeZeichen ---------------------------------------------
static bool ConvertEscapes (LPCTSTR pcTip, CString &rStr)
{
	if (NULL == pcTip) return false;

LPTSTR pT = rStr.GetBuffer (MAX_BUFLEN);		// genug Speicher vorsehen
TCHAR ch;

	while (*pcTip) {
		ch = *pcTip++;
		if ('\\' == ch) {
			ch = *pcTip++;
			
			switch (ch) {
			case '\0':		// EOL
				*pT++ = '\0';
				rStr.ReleaseBuffer();
				return false;

			case 'a':		// Alert
				ch = '\a';
				break;

			case 'n':		// LF
				ch = '\n';
				break;

			case 't':		// Tab
				ch = '\t';
				break;

			case 'r':		// CR
				ch = '\r';
				break;

			case 'b':		// BackSpace
				ch = '\b';
				break;

			case '\'':		// quotation mark
				ch = '\'';
				break;

			case '\"':		// double quotation mark
				ch = '\"';
				break;

			case '\\':		// backslash
				ch = '\\';
				break;

			default:
				{	// ZahlenEscape ?
					if (ch >= '0' && ch <= '9') {
					LPTSTR pNext = NULL;
					int iDigits = strtol (pcTip, &pNext, 8);

						*pT++ = (char)iDigits;	// nächstes Zeichen
						pcTip = pNext;
						continue;
					} else if (ch == 'x' || ch == 'X') {
					LPTSTR pNext = NULL;
					int iDigits = strtol (pcTip+1, &pNext, 16);

						if (pNext > pcTip+1) {
							*pT++ = (char)iDigits;	// nächstes Zeichen
							pcTip = pNext;
							continue;
						} 
					
					// ansonsten einfach das 'x' übernehmen
					}
				}
				
			// einfach dieses Zeichen kopieren
				break;
			}
		}

		*pT++ = ch;	// nächstes Zeichen
	}
	*pT++ = '\0';
	rStr.ReleaseBuffer();

return true;
}

void CTipDlg::GetNextTipString(CString &strNext)
{
LPTSTR lpsz = strNext.GetBuffer(MAX_BUFLEN);

// This routine identifies the next string that needs to be
// read from the tips file
bool bStop = false;
bool bError = false;

	while (!bStop) {
		if (_fgetts (lpsz, MAX_BUFLEN, m_pStream) == NULL) {
		// We have either reached EOF or encountered some problem
		// In both cases reset the pointer to the beginning of the file
		// This behavior is same as VC++ Tips file
			if (fseek(m_pStream, 0, SEEK_SET) != 0) {
				bStop = true;
				bError = true;
			}
		} else {
			switch (*lpsz) {
			case ' ':	// no space allowed at BOL
			case '\t':
			case '\n':
			case ';':	// comment
			// There should be no space at the beginning of the tip
			// This behavior is same as VC++ Tips file
			// Comment lines are ignored and they start with a semicolon
				break;	// next line

			case '#':
			// special command, ignored so far
				break;

			default:
				{
					strNext.ReleaseBuffer();

				int iLen = strNext.GetLength();

					if (iLen < 5) {
						if (fseek(m_pStream, 0, SEEK_SET) != 0) 
						// error: Format must be cat=... or cat,tip
							bError = true;
						bStop = true;
					} else {
					TCHAR ch = strNext[3];
				
						if (ch != ',' && ch != '=') {
							if (fseek(m_pStream, 0, SEEK_SET) != 0) 
								bError = true;
	
							bStop = true;
							break;
						}
						if (ch == '=') break;	// description, ignored so far

					// normal tip
						strNext.ReleaseBuffer();
						ConvertEscapes (strNext.Right(iLen-4), strNext);
						bStop = true;					
					}
				}
				break;
			} // end of switch
		} 
	} // end of while

	if (bError)
		VERIFY(strNext.LoadString(CG_IDP_FILE_CORRUPT));
}

HBRUSH CTipDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_TIPSTRING)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CTipDlg::OnOK()
{
	CDialog::OnOK();
	
// Update the startup information stored in the INI file
#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	CCurrentUser regTip (g_cbRegSection, true);
	DWORD dwVal = m_bStartup ? true : false;

		regTip.SetDWORD (g_cbIntStartup, dwVal);
	} 
#if defined(_USE_WIN32S_CODE)
	else {
	CWinApp* pApp = AfxGetApp();

		pApp->WriteProfileInt(szSection, g_cbIntStartup, !m_bStartup);
	}
#endif // defined(_USE_WIN32S_CODE)
}

BOOL CTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// If Tips file does not exist then disable NextTip
	if (m_pStream == NULL)
		GetDlgItem(IDC_NEXTTIP)->EnableWindow(FALSE);

	CenterWindow(GetParent());
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTipDlg::OnPaint()
{
CPaintDC dc(this); // device context for painting

// Get paint area for the big static control
CRect rect;

	GetDlgItem (IDC_FRAME) -> GetWindowRect (&rect);
	ScreenToClient (&rect);

// Paint the background white.
CBrush brush;

	brush.CreateStockObject(WHITE_BRUSH);
	dc.FillRect (rect, &brush);

// Load bitmap and get dimensions of the bitmap
CBitmap bmp;
BITMAP bmpInfo;

	bmp.LoadBitmap (IDB_LIGHTBULB);
	bmp.GetBitmap (&bmpInfo);

// Draw bitmap in top corner and validate only top portion of window
//CDC dcTmp;

//	dcTmp.CreateCompatibleDC(&dc);
//	dcTmp.SelectObject(&bmp);
//	rect.bottom = bmpInfo.bmHeight + rect.top;
//	dc.BitBlt(rect.left, rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight, // rect.Width(), rect.Height(), 
//		&dcTmp, 0, 0, SRCCOPY);

// Draw out "Did you know..." message next to the bitmap
CString strMessage;

	VERIFY(strMessage.LoadString(CG_IDS_DIDYOUKNOW));
	rect.bottom = rect.top + bmpInfo.bmHeight;
	rect.top += bmpInfo.bmHeight/2;
	rect.left += 2*bmpInfo.bmWidth;
	dc.DrawText(strMessage, rect, DT_VCENTER | DT_SINGLELINE);

	// Do not call CDialog::OnPaint() for painting messages
}

