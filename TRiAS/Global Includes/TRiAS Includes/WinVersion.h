// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 02:48:55 PM
//
// @doc
// @module WinVersion.h | WindowsVersion feststellen

#if !defined(_WINVERSION_H__4674526B_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _WINVERSION_H__4674526B_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CWinVersion 
{
public:
	CWinVersion() { PreCalcVersion(); }
	~CWinVersion() {}

private:
	bool s_fWin31;
	bool s_fWin40;
	bool s_fWin41;	// Memphis (#HK970827)
	bool s_fWin50;	// Cairo (#HK980223)
	bool s_fWinNT;
	bool s_fWin32s;

protected:
	void PreCalcVersion (void)
	{
	// Initialise Version Info
	DWORD dwVersion = GetVersion();

		s_fWin31 = false;
		s_fWinNT = false;
		s_fWin32s = false;
		s_fWin40 = false;
		s_fWin41 = false;
		s_fWin50 = false;

		if (dwVersion < ~0x7fffffff) {			// Windows NT
			s_fWinNT = true;
			if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
				if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
					s_fWin31 = true;
			} else if (LOBYTE(LOWORD(dwVersion)) > 4) {
				s_fWin50 = true;	// NT5.0
				s_fWin40 = true;
				s_fWin31 = true;
			} else if (LOBYTE(LOWORD(dwVersion)) > 3) {
				s_fWin40 = true;	// NT4.0
				s_fWin31 = true;
			}
		} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
			if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
				HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
			s_fWin32s = true;
		} else {					// Chicago or Memphis
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin41 = true;	// 4.10
			s_fWin31 = true;
			s_fWin40 = true;
		}
	}

public:
	bool IsWin31 (void) { return s_fWin31; }
	bool IsWin40 (void) { return s_fWin40; }
	bool IsWin41 (void) { return s_fWin41; }
	bool IsWin50 (void) { return s_fWin50; }
	bool IsWin32s (void) { return s_fWin32s; }
	bool IsWinNT (void) { return s_fWinNT; }
};

#endif // !defined(_WINVERSION_H__4674526B_9CBA_11D2_9F09_006008447800__INCLUDED_)
