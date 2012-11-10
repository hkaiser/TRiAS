// Eine Bitmap, die mehrere Bilder in einer Zeile enthält ---------------------
// File: BMPBAR.HXX

#if !defined(_BMPBAR_HXX)
#define _BMPBAR_HXX

class CBitmapBar : public Bitmap {
private:
	CoOrd m_iSize;		// Breite/Höhe eines der Bildchen

public:
		CBitmapBar (HBITMAP hBmp) : Bitmap (hBmp) 
			{ m_iSize = GetSize().Height(); }
		CBitmapBar (ResID uiRes) : Bitmap (uiRes)
			{ m_iSize = GetSize().Height(); }
		~CBitmapBar (void) {}
		
inline	CoOrd FWidth (void) { return m_iSize; }
inline	CoOrd FXOffset (short iIndex) { return (iIndex-1) * FWidth(); }
};

#endif // _BMPBAR_HXX
