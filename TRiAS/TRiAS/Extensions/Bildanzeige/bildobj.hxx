// Klassendeklarationen fuer BildObjekte
// File: BILDOBJ.HXX

#if !defined(_BILDOBJ_HXX)
#define _BILDOBJ_HXX

#define BFT_BITMAP	0x4d42	/* 'BM' */
#define ISDIB(bft)	((bft) == BFT_BITMAP)
#define WIDTHBYTES(i)	((i+31)/32*4)

// BildObjekt - Enthält Bitmap aus vorgegebener Datei -------------------------
class BildObjekt : public DrawObject {
private:
	char *_FileName;	// DateiName
	Window *pWnd;		// ClientFenster auf dem gezeichnet werden soll
	HBITMAP _hDIB;		// device independent bitmap (DIB)
	HBITMAP _hDDB;		// device dependent bitmap (DDB)
	HPALETTE _hPal;		// zugehörige Palette
	Point _Org;		// BitmapBezugspunkt
	Dimension _Size;	// Bitmapgröße
	Bool _OKFlag;		// Objekt richtig generiert

// private Memberfunktionen
	Bool InitDIB (char *FullName);		// Bitmap lesen, Palette bilden
	HBITMAP ReadDIB (unsigned int fh);
	Bool DIBInfo (BITMAPINFOHEADER *lpBI);
	HBITMAP ReadDIBitmapInfo (unsigned int fh);
	HPALETTE CreateDIBPalette (void);
	HPALETTE CreateBIPalette (BITMAPINFOHEADER *lpBI);
	unsigned int DIBNumColors (BITMAPINFOHEADER *lpBI);
	void FreeDIB (void);
	HBITMAP DIBToBitmap (void);

protected:
	void Draw (void);	// Zeichenroutine

public:
// Konstruktor
		BildObjekt (pWindow pW, char *FileName, Point Pt);

// Member
	Point &Org (void) { return _Org; }	// BitmapBezugspunkt liefern
	Dimension GetSize (void) {		// Bitmapabmessungen liefern
		return _Size;
	}
	Bool OK (void) { return _OKFlag; }

// Destruktor
		~BildObjekt (void);
};

// Klasse, die Zugriff auf HWND erlaubt
class NakedWindow : public Window {
public:
	HWND Handle (Service s) { return Window :: Handle (s); }
};

#endif // _BILDOBJ_HXX

