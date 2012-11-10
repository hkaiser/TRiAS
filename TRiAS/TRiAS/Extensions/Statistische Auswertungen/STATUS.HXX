// Fenster, welches, den ExportStatus anzeigt ---------------------------------
// File: STATUS.HXX

#if !defined(_STATUS_HXX)
#define _STATUS_HXX

#include <istatus.h>

class CStatus {
private:
	LPPROGRESSINDICATOR m_pIStatus;
	ResourceFile *_pResTarget;
	HWND _hStatusWnd;

public:
		CStatus (pWindow pW, ResourceFile *pRes, long AllCnt, LPCSTR pcFName);
		~CStatus (void);

	void SetValue (long newCnt, long lON = -1);
	bool Break (void);
	void Show (void) { SetValue(0); }
	HWND GetHWND ( void ) { return _hStatusWnd; };
};

#endif // _STATUS_HXX
