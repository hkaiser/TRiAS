//	FILE: ACTWIND.HPP

#ifndef _ACTIVATE_WINDOW_HPP
#define _ACTIVATE_WINDOW_HPP

class CActivateWindow
{
private:
	HWND m_hWnd;

public:
	CActivateWindow (HWND hWnd) { if (hWnd) :: EnableWindow (m_hWnd = hWnd, FALSE); }
	~CActivateWindow (void) { if (m_hWnd) :: EnableWindow (m_hWnd, TRUE); }
};

#endif 			// _ACTIVATE_WINDOW_HPP
