// Klassendeklarationen fuer BildObjekte
// File: BILDOBJ.HXX

#if !defined(_BILDOBJ_HXX)
#define _BILDOBJ_HXX

#include <dllbind.hxx>

#define BFT_BITMAP	0x4d42	/* 'BM' */
#define ISDIB(bft)	((bft) == BFT_BITMAP)
#define WIDTHBYTES(i)	((i+31)/32*4)

///////////////////////////////////////////////////////////////////////////////
// Dynamisches Binden der LZ32.DLL
class CBindLZ32 :
	public DLLBind
{
private:

	typedef INT (APIENTRY * LZOPENFILEPROC)(LPSTR, LPOFSTRUCT, WORD);
	typedef LONG (APIENTRY * LZSSEEKPROC)(INT, LONG, INT);
	typedef INT (APIENTRY * LZRREADPROC)(INT, LPSTR, INT);
	typedef VOID (APIENTRY * LZCLOSEPROC)(INT);

	LZOPENFILEPROC m_pLZOpenFile;
	LZSSEEKPROC m_pLZSeek;
	LZRREADPROC m_pLZRead;
	LZCLOSEPROC m_pLZClose;

	bool m_fIsValid;

public:
		CBindLZ32 (void);

	INT LZOpenFile (LPSTR, LPOFSTRUCT, WORD);
	LONG LZSeek (HFILE, LONG, INT);
	INT LZRead (HFILE, LPSTR, INT);
	VOID LZClose (HFILE);
	DWORD LZHugeRead (HFILE fh, void *pv, ULONG ul);

	bool IsValid (void) { return m_fIsValid; }
};

// BildObjekt - Enthält Bitmap aus vorgegebener Datei -------------------------
class CBildObjekt : 
	public DrawObject 
{
private:
	char *m_pFileName;	// DateiName
	Window *m_pWnd;		// ClientFenster auf dem gezeichnet werden soll
	HBITMAP m_hDIB;		// device independent bitmap (DIB)
	HBITMAP m_hDDB;		// device dependent bitmap (DDB)
	HPALETTE m_hPal;	// zugehörige Palette
	Point m_ptOrg;		// BitmapBezugspunkt
	Dimension m_dimSize;	// Bitmapgröße
	Bool m_fOKFlag;		// Objekt richtig generiert

// private Memberfunktionen
	Bool InitDIB (void);		// Bitmap lesen, Palette bilden
	HBITMAP ReadDIB (CBindLZ32 &rLib, HFILE fh);
	Bool DIBInfo (BITMAPINFOHEADER *lpBI);
	HBITMAP ReadDIBitmapInfo (CBindLZ32 &rLib, HFILE fh);
	HPALETTE CreateDIBPalette (void);
	HPALETTE CreateBIPalette (BITMAPINFOHEADER *lpBI);
	unsigned int DIBNumColors (BITMAPINFOHEADER *lpBI);
	void FreeDIB (void);
	HBITMAP DIBToBitmap (void);

protected:
	void Draw (void);	// Zeichenroutine

public:
// Konstruktor/Destruktor
		CBildObjekt (pWindow pW, Point pt);
		~CBildObjekt (void);

	BOOL FInit (char *pFileName);
	
// Member
	Point &Org (void) { return m_ptOrg; }	// BitmapBezugspunkt liefern
	Dimension GetSize (void) {		// Bitmapabmessungen liefern
		return m_dimSize;
	}
	Bool OK (void) { return m_fOKFlag; }
};

// Klasse, die Zugriff auf HWND erlaubt
class NakedWindow : public Window {
public:
	HWND Handle (Service s) { return Window :: Handle (s); }
};

#endif // _BILDOBJ_HXX

