// AssertDlg.CPP

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#include "StdAfx.h"

#include "cont32.h"
#include "AssertDlg.h"
#include "DumpBuffer.h"


// Necessary to load dialog resource
extern HINSTANCE g_hInst;

AssertDialog :: AssertDialog (const DumpBuffer& buf)
{
HWND hWndParent = GetActiveWindow();

	if (hWndParent != NULL)
		hWndParent = GetLastActivePopup(hWndParent);

	userChoice = (Choice)DialogBoxParam (g_hInst, MAKEINTRESOURCE(IDD_ASSERTDIALOG), hWndParent, (DLGPROC)AssertDlgProc, (LPARAM)&buf);
}

AssertDialog::Choice AssertDialog::userChoice;
int AssertDialog::iOrigHeight;

AssertDialog::Choice AssertDialog::GetUserChoice()
{
	return userChoice;
}

BOOL CALLBACK AssertDialog::AssertDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg) {
    case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_ABORT:
				EndDialog (hwndDlg, abort);
				return (TRUE);

			case IDC_IGNORE:
				EndDialog (hwndDlg, ignore);
				return (TRUE);

			case IDC_DEBUG:
				EndDialog (hwndDlg, debug);
				return (TRUE);

			case IDC_DETAILS:
				{
				RECT r;

					GetWindowRect (hwndDlg, &r);
					SetWindowPos (hwndDlg, 0, 0, 0, r.right - r.left, AssertDialog::iOrigHeight, SWP_NOMOVE);
					ShowWindow (GetDlgItem (hwndDlg, IDC_MESSAGE), SW_SHOW);
					EnableWindow (GetDlgItem (hwndDlg, IDC_DETAILS), FALSE);
				}
				return TRUE;

			default:
				break;
			}
		}
		break;

    case WM_INITDIALOG:
		{
		// Center on screen
		RECT r;

			GetWindowRect (hwndDlg, &r);

		int cx = r.right - r.left;
		int cy = r.bottom - r.top;

			AssertDialog::iOrigHeight = cy;

		int x = (GetSystemMetrics (SM_CXSCREEN) - cx) / 2;
		int y = (GetSystemMetrics (SM_CYSCREEN) - cy) / 2;

		HWND hEdit = GetDlgItem (hwndDlg, IDC_MESSAGE);
		RECT rcEdit;

			GetWindowRect (hEdit, &rcEdit);
			cy = rcEdit.top - r.top + 1;
			SetWindowPos (hwndDlg, 0, x, y, cx, cy, 0);
			ShowWindow (hEdit, SW_HIDE);

		// Change to monospaced font
			SendDlgItemMessage (hwndDlg, IDC_MESSAGE, WM_SETFONT, (WPARAM)GetStockObject (ANSI_FIXED_FONT), 0);

		// Set text
		const DumpBuffer *db = (const DumpBuffer *)lParam;

			db -> SetWindowText (hEdit);
			db -> StaticSetWindowText (GetDlgItem (hwndDlg, IDC_STATICMESSAGE));

			MessageBeep (MB_ICONHAND);
			return TRUE;
		}
		break;

	default:
		break;
    }
	return FALSE;
}
