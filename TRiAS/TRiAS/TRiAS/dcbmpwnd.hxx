// Spezielles DC-Window zum zeichnen einer Bitmap in einem gegebenen DC -------
// File: DCBMPWND.HXX

#if !defined(_DCBMPWND_HXX)
#define _DCBMPWND_HXX

class CDCBmpWindow : public CDCWindow {
private:
	CColorBitmapObject &m_rCBO;
	
protected:
	BOOL DCExpose (CDCExposeEvt) { DrawEx (&m_rCBO, NULL); return true; }

public:
		CDCBmpWindow (HDC hDC, Rectangle &rRc, CColorBitmapObject &rCBO)
			: CDCWindow (hDC, rRc, hDC), m_rCBO (rCBO) {}
		~CDCBmpWindow (void) {}
};

#endif // _DCBMPWND_HXX
