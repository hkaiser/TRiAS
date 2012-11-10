// BitmapButton ---------------------------------------------------------------
// File: BmpBtn.h

#if !defined(_BMPBTN_HXX)
#define _BMPBTN_HXX

//class _TRIAS03_ENTRY CBmpButton : public PushButton {
class CBmpButton : public PushButton {
private:
// all bitmaps must be the same size
	Bitmap *m_pBitmap;          // normal image (REQUIRED)
	Bitmap *m_pBitmapSel;       // selected image (OPTIONAL)
	Bitmap *m_pBitmapFocus;     // focused but not selected (OPTIONAL)
	Bitmap *m_pBitmapDisabled;  // disabled bitmap (OPTIONAL)

	bool m_fIsBmpBtn;			// ist neuer Button (BS_BITMAP)
	HBITMAP m_hBmp;				// in diesem Fall: alte Bitmap 

public:
		CBmpButton (pDialogWindow parent, ResID);
		CBmpButton (pWindow, CvID id, Point, Dimension, const char * InitText = 0);
		~CBmpButton (void);

	bool LoadBitmaps (ResID resBitmap, ResID resBitmapSel = ResID(0U), 
					  ResID resBitmapFocus = ResID(0U), ResID resBitmapDisabled = ResID(0U));
	void SizeToContent (void);
	bool AutoLoad (ResourceFile *pRF = NULL);
	bool DrawItem (DrawItemEvt e);

	bool FInit (void);
};

#endif // _BMPBTN_HXX
