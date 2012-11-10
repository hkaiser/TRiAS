// Implementation der Anzeige von TextElementen 
// File: GEOTEXT.CXX

#include "trias02p.hxx"

#include "trias02.h"

#include <initguid.h>
#include <xtsnguid.h>
#include <CSTextPointGeom.h>

#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
HRESULT GetObjectProperty (LPCSTR pcName, LONG lONr, IObjectProperty **ppIObjProp);
HRESULT GetEnumObjProps (LONG lONr, IEnumObjProps **ppIEnum);
HRESULT GetObjProps (REFIID riid, LPVOID *ppIObjProps);

/////////////////////////////////////////////////////////////////////////////
// Geometrie in Feldern bereitstellen 
long BasicGeoText::RetrievePureGeometrie (KoOrd **pX, KoOrd **pY, long **pKCnt)
{
	if (NULL == pX || NULL == pY) return 0L;

	COM_TRY {
		*pX = new KoOrd [1];
		*pY = new KoOrd [1];
		if (NULL == *pX || NULL == *pY) {
			DELETE_OBJ (*pX);
			db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
			_com_issue_error(E_OUTOFMEMORY);
		}

	// Geometrie holen
		(*pX)[0] = GetX();
		(*pY)[0] = GetY();

	} COM_CATCH_RETURN(0L);
	return 1;	// ein Stützpunkt
}

/////////////////////////////////////////////////////////////////////////////
// Konstruktoren 
GeoText::GeoText (GeoDB &rDB, long ONr, long Id, char *Text) 
	 : BasicGeoText (rDB, ONr, Id)
{
	TX_TRY(_ShowedText = new char [Text ? strlen (Text)+1 : 2]);
	if (_ShowedText) {
		strcpy (_ShowedText, Text ? Text : "");

		if (NULL != Text) {
			COM_TRY {
			CCSTextPointGeometry text (GetGeometry());

				TX_ASSERT(text.IsValid()); 
				text.put_Text (CComBSTR (_ShowedText));
			} COM_CATCH_NORETURN;
		}
	}
}

GeoText::GeoText (GeoDB &rDB, long ONr, long Id, const Punkt &Pt, char *Text)
	 : BasicGeoText (rDB, ONr, Id, Pt)
{
	TX_TRY(_ShowedText = new char [Text ? strlen (Text)+1 : 2]);
	if (_ShowedText) {
		strcpy (_ShowedText, Text ? Text : "");

		if (NULL != Text) {
			COM_TRY {
			CCSTextPointGeometry text (GetGeometry());

				TX_ASSERT(text.IsValid()); 
				text.put_Text (CComBSTR (_ShowedText));
			} COM_CATCH_NORETURN;
		}
	}
}

GeoText::GeoText (GeoText &GT) 
	 : BasicGeoText (GT.DB(), GT.ObjNr(), GT.Id(), Punkt (GT.GetX(), GT.GetY()))
{
	TX_TRY(_ShowedText = new char [GT.Text() ? strlen (GT.Text())+1 : 2]);
	if (_ShowedText) {
		strcpy (_ShowedText, GT.Text() ? GT.Text() : "");

		if (NULL != GT.Text()) {
			COM_TRY {
			CCSTextPointGeometry text (GetGeometry());

				TX_ASSERT(text.IsValid());
				text.put_Text (CComBSTR (_ShowedText));
			} COM_CATCH_NORETURN;
		}
	}
}

#if defined(_USE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
//
GeoTextInd::GeoTextInd (GeoDB &rDB, long ONr, long Id, long MCode) 
	    : BasicGeoText (rDB, ONr, Id)
{
	_MCode = MCode;

CActDB ActDB (rDB);	// DB aktivieren

	_AssocONr = labs (AssociatedObjekt (DB().DBDesc(), ONr));
}

GeoTextInd::GeoTextInd (GeoDB &rDB, long ONr, long Id, const Punkt &Pt, long MCode)
	    : BasicGeoText (rDB, ONr, Id, Pt)
{
	_MCode = MCode;

CActDB ActDB (rDB);	// DB aktivieren

	_AssocONr = labs (AssociatedObjekt (DB().DBDesc(), ONr));
}

GeoTextInd::GeoTextInd (GeoTextInd &GTI) 
	    : BasicGeoText (GTI.DB(), GTI.ObjNr(), GTI.Id(), Punkt (GTI.GetX(), GTI.GetY()))
{
	_MCode = GTI._MCode;
	_AssocONr = GTI._AssocONr;
}
#endif // defined(_USE_LEGACY_CODE)

/////////////////////////////////////////////////////////////////////////////
// dynamisches Label-Objekt
GeoTextIndOP::GeoTextIndOP (GeoDB &rDB, long lONr, long Id, char *pText) 
	    : GeoText (rDB, lONr, Id, pText), _AssocONr(0L)
{
	if (-1L != lONr && 0L != lONr) {
	CActDB ActDB (rDB);	// DB aktivieren

		_AssocONr = AssociatedObjekt (lONr, NULL);
		if (0 == _AssocONr)
			_AssocONr = lONr;
	}
	if (NULL != pText)
		GetObjectProperty (pText, _AssocONr, m_ObjProp.ppi());
}

GeoTextIndOP::GeoTextIndOP (GeoDB &rDB, long lONr, long Id, const Punkt &Pt, char *pText)
	    : GeoText (rDB, lONr, Id, Pt, pText), _AssocONr(0L)
{
	if (-1L != lONr && 0L != lONr) {
	CActDB ActDB (rDB);	// DB aktivieren

		_AssocONr = AssociatedObjekt (lONr, NULL);
		if (0 == _AssocONr)
			_AssocONr = lONr;
	}
	if (NULL != pText)
		GetObjectProperty (pText, _AssocONr, m_ObjProp.ppi());
	else {
		USES_CONVERSION;

		COM_TRY {
		// ggf. Text aus Geometrieobjekt besorgen
		CComBSTR bstrText;
		CCSTextPointGeometry text(const_cast<Punkt &>(Pt).GetGeometry());

			text -> get_text(&bstrText);
			if (bstrText.Length() > 0) {
			// Text sollte/könnte mit "@@" anfangen
			LPCSTR pcText = OLE2A(bstrText);

				GetObjectProperty(!strncmp (pcText, "@@", 2) ? pcText+2 : pcText, _AssocONr, m_ObjProp.ppi());
			}
		} COM_CATCH_NORETURN;
	}
}

GeoTextIndOP::GeoTextIndOP (GeoTextIndOP &GTI) 
	    : GeoText (GTI.DB(), GTI.ObjNr(), GTI.Id(), Punkt (GTI.GetX(), GTI.GetY()), GTI.TextBase())
{
	_AssocONr = GTI._AssocONr;
	m_ObjProp = GTI.m_ObjProp;
	m_strText = GTI.m_strText;
}

#if defined(_USE_LEGACY_CODE)

static char *tmp = "No text, no fun.";

char *GeoTextInd::Text (void) const 
{
	if (_AssocONr == 0) 	// kein BezugsObjekt
		return tmp;

	{
	ErrInstall EI (WC_NOTFOUND);	// WC_NOTFOUND abfangen und umdeuten
	ErrCode RC;

		if (_ShowedText == NULL &&
		    (RC = (ErrCode)GetMiText (((GeoDB &)cDB()).DBDesc(), _MCode, _AssocONr, 
		    			OBL_OLD, (char **)&_ShowedText)) != EC_OKAY) 
		{
			if (RC == WC_NOTFOUND)
				db_error (WC_NOTEXTMK, RC_GeoTextIndText);
			return tmp;
		}
	}
	return _ShowedText;
}

#endif // defined(_USE_LEGACY_CODE)

char *GeoTextIndOP::TextBase (void) const 
{
	return GeoText::Text();
}

char *GeoTextIndOP::Text (void) const 
{
GeoTextIndOP *pThis = const_cast<GeoTextIndOP *>(this);

	if (0 == _AssocONr)	{	// vielleicht gibts ja jetzt ein Bezugsobjekt
	CActDB ActDB (m_rDB);	// DB aktivieren

		pThis -> _AssocONr = AssociatedObjekt (GetONr(), NULL);
		if (0 == _AssocONr)
			pThis -> _AssocONr = GetONr();
	}

char cbBuffer[_MAX_PATH];

	if (_AssocONr == 0 || NULL == m_ObjProp.p) {
	// kein BezugsObjekt oder Objekteigenschaft existiert nicht
	ResourceFile RF (g_pDLLName);
	UINT uiResID = (_AssocONr == 0) ? IDS_NODEPOBJECT : IDS_NODEPOBJPROP;
	ResString resError (ResID (uiResID, &RF), 128);

		wsprintf (cbBuffer, resError, GeoText::Text());
		pThis -> m_strText = cbBuffer;
		return (char *)m_strText.c_str();
	}

// Objekteigenschaft jedesmal berechnen (dynamisch eben)
	if (SUCCEEDED(pThis -> m_ObjProp -> Eval (_AssocONr, cbBuffer, sizeof(cbBuffer), NULL)))
		pThis -> m_strText = cbBuffer;
	else
		pThis -> m_strText = g_cbNil;	

	return (char *)m_strText.c_str();
}

// Liefern der Anzahl der Zeilen und Spalten des anzuzeigenden Textes ---------
Dimension BasicGeoText::Size (void) 
{
char *cptr = Text();
short Lines = 0;
short Columns = 0;
short locCols = 0;

	if (cptr == NULL) 
		return Dimension (0, 0);	// kein Text gegeben
	while (*cptr) {
		locCols++;		// Spalten zählen
		if (*cptr == '\n') {
			Lines++;	// Zeilen zählen
			Columns = max (locCols, Columns);
			locCols = 0;
		}
		cptr++;
	}
	return Dimension (Columns, Lines);
}

// nur für den internen Gebrauch ! --------------------------------------------
void BasicGeoText::SetText (char *newText) 
{
	DELETE_OBJ (_ShowedText);
	_ShowedText = newText;
}

char *BasicGeoText::ChangeText (char *lpNewText) 
{
char *oldText = Text();
char *newText = new char [strlen (lpNewText) +1];

	if (newText == NULL) {
		db_error (EC_NOMEMORY, RC_ChangeText);
		return NULL;
	}
	strcpy (newText, lpNewText);		// neuen Text kopieren
	_ShowedText = newText;
	return oldText;		// Resultat muß explizit freigegeben werden
}

/////////////////////////////////////////////////////////////////////////////
// virtuelle Funktionen 
char *BasicGeoText::TextBase() const { return Text(); }
ObjTyp BasicGeoText::isA (void) { return OT_TEXT; }
GEOMETRYTYPE BasicGeoText::GType() { return GEOMETRYTYPE_Text; }

TextObjTyp GeoText::isText (void) { return TOT_TEXT; }
#if defined(_USE_LEGACY_CODE)
TextObjTyp GeoTextInd::isText (void) { return TOT_TEXTIND; }
#endif // defined(_USE_LEGACY_CODE)

ObjTyp GeoTextIndOP::isA (void) { return OT_LABEL; }
TextObjTyp GeoTextIndOP::isText (void) { return TOT_TEXTINDOBJPROP; }
char *GeoTextIndOP::ChangeText (char *lpNewText) { return NULL; }

/////////////////////////////////////////////////////////////////////////////
// Objekteigenschafte verwalten

HRESULT GetObjectProperty (LPCSTR pcName, LONG lONr, IObjectProperty **ppIObjProp)
{
	*ppIObjProp = NULL;

IEnumObjProps *pIEnumObjP = NULL;
HRESULT hr = GetEnumObjProps (lONr, &pIEnumObjP);

	if (FAILED(hr)) return hr;

	hr = pIEnumObjP -> FindByName (pcName, ppIObjProp);	 //???return value
	pIEnumObjP -> Release();

	if (FAILED(hr)) 
		return S_FALSE;		// not found
	return S_OK;
}

HRESULT GetEnumObjProps (LONG lONr, IEnumObjProps **ppIEnum)
{
	*ppIEnum = NULL;

IObjectProps *pIObjProps = NULL;
HRESULT	hr = GetObjProps (IID_IObjectProps, (LPVOID *)&pIObjProps);
	
	if (FAILED(hr)) return hr;

	hr = pIObjProps -> EnumObjectProps (ppIEnum);
	pIObjProps -> Release();

	return hr;
}

HRESULT GetObjProps (REFIID riid, LPVOID *ppIObjProps)
{
// Get all installed ObjectProperties for lONr
IObjectProps *pIObjProps = NULL;
BOOL fMustReInit = DEX_GetObjectProps (&pIObjProps);

	if (NULL != pIObjProps) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			pIObjProps -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			RETURN_FAILED_HRESULT(pIObjProps -> OnNewReferenceObject (0L));
		}
	
	HRESULT hr = pIObjProps -> QueryInterface (riid, ppIObjProps);

		pIObjProps -> Release();
		return hr;
	}
	return E_UNEXPECTED;
}


