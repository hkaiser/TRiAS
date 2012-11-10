// Wrapper für OBJGEOMETRIE
// OBJGEOMW.CPP

#include "trias03p.hxx"
#include "ObjGeomW.h"

///////////////////////////////////////////////////////////////////////////////
// CObjGeometrie
CObjGeometrie::CObjGeometrie (void)
{
	memset(this, '\0', sizeof(OBJGEOMETRIE));
	dwSize = sizeof(OBJGEOMETRIE);
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

	return true;
}

bool CObjGeometrie:: FillObjGeometrie (long lONrToFill)
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
			td.m_dwSize = sizeof (GETTEXTDATA);
			td.m_lONr = lONr;
			td.m_pText = ((TEXTGEOMETRIE *)this)->pText;
			td.m_iLen = iKCnt+1;
			if (!DEX_GetTextObjectText(td))
				return false;

		} catch (...) {
			return false;
		}
	}

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
	return *this;
}
