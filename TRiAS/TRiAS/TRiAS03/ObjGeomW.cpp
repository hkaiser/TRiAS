// Wrapper für OBJGEOMETRIE
// OBJGEOMW.CPP

#include "trias03p.hxx"
#include "ObjGeomW.h"

#include <iunredo.hxx>
#include <undoguid.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(UndoRedoModifyObject);

///////////////////////////////////////////////////////////////////////////////
// CObjGeometrie
CObjGeometrie::CObjGeometrie (void) :
	m_rgState(OBJGEOMSTATE_Uninitialized)
{
	memset(this, '\0', sizeof(OBJGEOMETRIE));
	dwSize = sizeof(OBJGEOMETRIE);
    iFlags = OGConverted;
}

CObjGeometrie::~CObjGeometrie (void)
{
	Tidy();
}

void CObjGeometrie::Tidy (void)
{
	DELETE_OBJ (pdblX);
	DELETE_OBJ (pdblY);
	DELETE_OBJ (plCnt);
	m_rgState = OBJGEOMSTATE_Uninitialized;
    iFlags = OGConverted;
}

bool CObjGeometrie::InitObjGeometrie (bool fIsInitialized)
{
	Tidy();
	if (!fIsInitialized && !DEX_GetObjStatistik (*this)) 
		return false;

	TX_TRY(pdblX = new double [lCnt]);
	TX_TRY(pdblY = new double [lCnt]);
	if (pdblX == NULL || pdblY == NULL)
		return false;

	if (iKCnt > 0) {
		if (iObjTyp == OGFlaeche) {
			TX_TRY(plCnt = new long [iKCnt]);
			if (plCnt == NULL) 
				return false;
		} else if (iObjTyp == OGText) {
		int iLen = iKCnt;

			if (0 == iLen) iLen = _MAX_PATH;
			TX_TRY(((TEXTGEOMETRIE *)this)->pText = new char [iLen+1]);
			if (((TEXTGEOMETRIE *)this)->pText == NULL) 
				return false;
		}
	} else
		plCnt = NULL;

	m_rgState = OBJGEOMSTATE_Initialized;
	return true;
}

bool CObjGeometrie:: FillObjGeometrie (HOBJECT lONrToFill)
{
	lONr = lONrToFill;
	if (!InitObjGeometrie(false) || !DEX_GetObjGeometrie (*this)) 
		return false;

	if (iObjTyp == OGText) {
	// Text des Textes besorgen
		try {
		GETTEXTDATA td;

			TX_TRY(((TEXTGEOMETRIE *)this)->pText = new char[_MAX_PATH+1]);

			memset (&td, '\0', sizeof(GETTEXTDATA));
			td.dwSize = sizeof (GETTEXTDATA);
			td.m_lONr = lONr;
			td.m_pText = ((TEXTGEOMETRIE *)this)->pText;
			td.m_iLen = iKCnt+1;
			if (!DEX_GetTextObjectText(td))
				return false;

		} catch (...) {
			return false;
		}
	}
	m_rgState = OBJGEOMSTATE_Filled;
	return true;
}

// throws bad_alloc
OBJGEOMETRIE &CObjGeometrie::operator= (const OBJGEOMETRIE &rOG)
{
// verschiedenes aus der alten Struktur übernehmen
	lONr = rOG.lONr;
	iObjTyp = rOG.iObjTyp;
	lIdent = rOG.lIdent;
	lCnt = rOG.lCnt;		// #HK980831
	iKCnt = rOG.iKCnt;

	if (!InitObjGeometrie(true)) 
		_com_issue_error(E_OUTOFMEMORY);

	if (rOG.iFlags & OGConverted) {
		memcpy (pdblX, rOG.pdblX, rOG.lCnt*sizeof(double));
		memcpy (pdblY, rOG.pdblY, rOG.lCnt*sizeof(double));
	} else {
		memcpy (pdblX, rOG.pdblX, rOG.lCnt*sizeof(long));
		memcpy (pdblY, rOG.pdblY, rOG.lCnt*sizeof(long));
	}

	if (rOG.iKCnt > 0) {
		if (rOG.iObjTyp == OGFlaeche) 
			memcpy (plCnt, rOG.plCnt, rOG.iKCnt*sizeof(long));
		else if (rOG.iObjTyp == OGText) {
		TEXTGEOMETRIE &TG = (TEXTGEOMETRIE &)rOG;
		TEXTGEOMETRIE &oldTG = (TEXTGEOMETRIE &)(*this);

			if (NULL != TG.pText) {
				TX_TRY(oldTG.pText = new char[rOG.iKCnt+1]);
				if (NULL == oldTG.pText)
					_com_issue_error(E_OUTOFMEMORY);
				strcpy (oldTG.pText, TG.pText);
			}
		}
	} 

	m_rgState = OBJGEOMSTATE_Filled;
	return *this;
}

namespace {
	class CUndoGeom
	{
	public:
		CUndoGeom()
		{
		}
		~CUndoGeom()
		{
			if (m_Undo.IsValid()) 
				DEX_AddUndoRedo (m_Undo.p);
		}

		bool ModObjGeometrie(HPROJECT hPr, OBJGEOMETRIE &rOG)
		{
			_ASSERTE(!m_Undo.IsValid());		// nur einmal rufen

			if (DEX_ModObjGeometrieEx(hPr, rOG)) {
			HRESULT hr = m_Undo.CreateInstance(CLSID_UndoRedoObject);

				if (SUCCEEDED(hr)) 
					hr = m_Undo -> Init(rOG.lONr, &rOG, NULL);
				if (FAILED(hr))
					m_Undo.Assign(NULL);
				return true;
			}
			return false; 
		}

	private:
		WUndoRedoModifyObject m_Undo;
	};
}

bool CObjGeometrie::CreateNewObject (HPROJECT hPrDest, HOBJECTS lNewIdent, bool fUndo)
{
	_ASSERTE(m_rgState == OBJGEOMSTATE_Filled);
	_ASSERTE(DEX_GetObjectsProject(lNewIdent) == hPrDest);		// Zieldatenquelle muß stimmen

	iFlags |= OGNewObject|OGForceGeometry;
    iFlags &= ~OGModObject;
	lIdent = lNewIdent;

	if (fUndo) {
	// Undo selbst machen
	CUndoGeom UndoGeom;

		return UndoGeom.ModObjGeometrie(hPrDest, *this);		
	}
	else {
	// auf Undo verzichten (lt. Anweisung!)
		return DEX_ModObjGeometrieEx(hPrDest, *this);
	}
}

HRESULT CObjGeometrie::AreaToLine()
{
    _ASSERTE(OGFlaeche == iObjTyp);
    _ASSERTE(OBJGEOMSTATE_Uninitialized != m_rgState);

    iObjTyp = OGLinie;
    DELETE_OBJ(plCnt);
    iKCnt = 0;

    return S_OK;
}

HRESULT CObjGeometrie::LineToArea()
{
    _ASSERTE(OGLinie == iObjTyp);
    _ASSERTE(OBJGEOMSTATE_Uninitialized != m_rgState);

    iObjTyp = OGFlaeche;
    iKCnt = 1;

    DELETE_OBJ(plCnt);
    plCnt = new long[1];
    if (NULL == plCnt) 
        return E_OUTOFMEMORY;

    plCnt[0] = lCnt;
    return S_OK;
}
