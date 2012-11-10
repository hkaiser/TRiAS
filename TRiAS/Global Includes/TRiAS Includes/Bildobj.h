// Bildobj.h

#if !defined(_BILDOBJ_H)
#define _BILDOBJ_H

#define BFT_BITMAP	0x4d42	/* 'BM' */
#define ISDIB(bft)	((bft) == BFT_BITMAP)
#define WIDTHBYTES(i)	((i+31)/32*4)

// BildObjekt - Enthält Bitmap aus vorgegebener Datei -------------------------
class CBildObjekt  
{
private:
	HBITMAP m_hDIB;		// device independent bitmap (DIB)
	HBITMAP m_hDDB;		// device dependent bitmap (DDB)
	HPALETTE m_hPal;		// zugehörige Palette
	CSize m_dim;

protected:
// Memberfunktionen
	bool InitDIB (LPCSTR FullName);		// Bitmap lesen, Palette bilden
	HBITMAP ReadDIB (unsigned int fh);
	bool DIBInfo (BITMAPINFOHEADER *lpBI);
	HBITMAP ReadDIBitmapInfo (unsigned int fh);
	HPALETTE CreateDIBPalette (void);
	HPALETTE CreateBIPalette (BITMAPINFOHEADER *lpBI);
	unsigned int DIBNumColors (BITMAPINFOHEADER *lpBI);
	void FreeDIB (void);
	HBITMAP DIBToBitmap (void);

public:
// Konstruktor
		CBildObjekt (void);
		~CBildObjekt (void);

	HBITMAP ReadFile (LPCSTR pcFileName);

	HPALETTE DetachHPal (void) { HPALETTE hPal = m_hPal; m_hPal = NULL; return hPal; }
	HBITMAP Detach (void) { HBITMAP hBmp = m_hDDB; m_hDDB = NULL; return hBmp; }
};

#endif // _BILDOBJ_H
