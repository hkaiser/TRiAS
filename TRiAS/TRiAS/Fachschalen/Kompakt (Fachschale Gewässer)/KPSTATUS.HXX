// Fenster, welches, den ExportStatus anzeigt ---------------------------------
// File: KPSTATUS.HXX

#if !defined(_KPSTATUS_HXX)
#define _KPSTATUS_HXX

#include <istatus.h>

class CStatus {
private:
	LPPROGRESSINDICATOR m_pIStatus;
	ResourceFile *_pResTarget;

public:
		CStatus (pWindow pW, ResourceFile *pRes, long AllCnt, LPCSTR pcFName);
		~CStatus (void);

	void SetValue (long newCnt, long lON = -1);
	bool Break (void);
	void Show (void) { SetValue(0); }
};

#endif // _KPSTATUS_HXX
