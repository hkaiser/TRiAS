// Includefile für IRIS -- Version für Windows 3.1 ----------------------------
// File: IRIS.HXX

#if !defined(_IRIS_HXX)
#define _IRIS_HXX

#include "iris.h"       // Konstantendefinitionen
#include "objekte.hxx"
#include "stack.hxx"    // generischer Stack
#include "dboarray.hxx"

#if !defined(WIN16)
#include "mru.h"
#endif

#if !defined(NODRAGRECTOBJ)
// Erweitertes Rechteck-Objekt ------------------------------------------------
typedef enum tagDRAGTYPE {
	DT_DRAGRECTANGLE = 1,
	DT_DRAGLINE = 2,
	DT_SHIFTRECTANGLE = 3,
	DT_UNKNOWN = 4,
} DRAGTYPE;

class CDragObject {
private:
	DrawObject *m_pDO;

public:

		CDragObject (DrawObject *pDO) { m_pDO = pDO; }
	virtual ~CDragObject (void) {}

	virtual DRAGTYPE isA (void) = 0;

	operator DrawObject *() { return m_pDO; }
	DrawObject * operator-> () { return m_pDO; }

	virtual void ProcessKey (KeyEvt) = 0;		// TastenDruck verarbeiten
	virtual bool ToProcessKey (void) = 0;
	virtual bool isDirty (void) = 0;
	virtual bool isValidDragObject() = 0;
};

#pragma warning (disable:4355)

class DragRectangleObject : public RectangleObject, public CDragObject {
protected:
	Point m_pt;		// MittelPunkt
	Point m_end;	// letzter Endpunkt
	bool m_fControl;	// letzter Zustand des KeyBoars
	bool m_fShift;

	Pen m_pen;

public:
// Konstruktor
		DragRectangleObject (Point Pt, Dimension Dim, pBrush pB = NULL) :
			m_pen (SolidLine, 1, Color ((ColorVal)128, (ColorVal)128, (ColorVal)128)),
			RectangleObject (Pt, Dim, &m_pen, pB), CDragObject (this) 
				{ m_pt = m_end = Pt; m_fControl = m_fShift = false; }

	DRAGTYPE isA (void); // { return DT_DRAGRECTANGLE; }

	void Process (Point end);		// neue Größe einstellen
	void ProcessKey (KeyEvt); 		// TastenDruck verarbeiten
	bool ToProcessKey (void);
	bool isDirty (void);

// Rechteckpunkte liefern
	Point UpperLeft (void) { return pt; }
	Point LowerRight (void) {
		return Point (pt.X()+dim.Width()-1, pt.Y()+dim.Height()+1);
	}
	Point LowerLeft (void) {
		return Point (pt.X(), pt.Y()+dim.Height()+1);	}
	Point UpperRight (void) {
		return Point (pt.X()+dim.Width()-1, pt.Y());
	}

// Rechteck liefern
	Rectangle GetRect (void) {
		return Rectangle (pt, dim);
	}
// Rechteck von außen setzen
	void InflateRect (int iPixels);
	void SetRect (Point Pt, Dimension Dim) { pt = Pt; dim = Dim; }

// Testen, ob Rechteck entartet ist
	bool isValid (void) 
		{ return (dim.Width()-1 != 0 && dim.Height()+1 != 0); }
	bool isNull() { return (dim.Width() == 0 || dim.Height() == 0); }
	bool isValidDragObject() { return isValid() && !isNull(); }

// Rechteck ggf. kippen
	void CorrectCoOrds (void);
};

class DragLineObject : public LineObject, public CDragObject {
public:
// Konstruktor
		DragLineObject (Point Pt) : 
			LineObject (Pt, Pt, NULL), CDragObject (this)  {}
// Member
	void Process (Point Pt);
	DRAGTYPE isA (void); // { return DT_DRAGLINE; }

	void ProcessKey (KeyEvt);		// TastenDruck verarbeiten
	bool ToProcessKey (void);
	bool isDirty (void);
	bool isNull() { Dimension d = GetSize(); return d.Width() == 0 || d.Height() == 0; }
	bool isValidDragObject() { return !isNull(); }
};

#pragma warning (default:4355)

#endif // NODRAGRECTOBJ

#if !defined(NOGITTER)
// Gitternetzlinien -----------------------------------------------------------
class GitterObjekt : public ExtShapeObject {
private:
	bool _GitterFlag;

protected:
	void Draw (void);               // Gitter zeichnen

public:
	GitterObjekt (bool GFlag, pPen pP = NULL, pBrush pB = NULL) :
		ExtShapeObject (Point (0, 0), Dimension (), pP, pB)
			{ _GitterFlag = GFlag; }

	bool & GitterFlag (void) { return _GitterFlag; }
	ObjTyp isTyp (void) { return O_GITTER; }
};
#endif // NOGITTER

#include "iriswind.hxx"

// Initialisierungsfunktion ---------------------------------------------------
BOOL InitIrisApp (Rectangle &, BOOL &, BOOL &);
BOOL TestEnv (HINSTANCE);
bool TriasRegInit (bool fForce = false, bool fFull = false, bool fSilent = false, bool fSetup = false);
bool RegisterDemoRegNum (void);
#if !defined(WIN16)
bool TriasRegUnInit (bool fSilent = false, bool fFull = false);
#else
bool TriasRegUnInit (bool fSilent = false);
#endif // WIN16

// MenuInitFunktionen
void MenuCheck (pMenu pM, int MenuItem, bool Flag);
void MenuEnable (pMenu pM, int MenuItem, bool Flag);

// neue GeoDB anlegen ---------------------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes);
#if !defined(WIN16)
bool CreateNewGeoDB (LPCSTR pFile, LPSTORAGE *pIStorage, int rgMode = 0, LPCSTR pUser = NULL, LPCSTR pPWD = NULL);	// force filename
#else
bool CreateNewGeoDB (LPCSTR pFile, LPCSTR pUser = NULL, LPCSTR pPWD = NULL, bool fNew = false);	// force filename
#endif // WIN16
	
#endif  // _IRIS_HXX
