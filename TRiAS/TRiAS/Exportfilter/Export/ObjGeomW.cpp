// Wrapper für OBJGEOMETRIE
// OBJGEOMW.CPP
// geklaut bei Hartmut; weiß er aber... ;-)
#include "stdafx.h"
#include "ExportImpl.h"
#include "ObjGeomW.h"

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <tstring>

///////////////////////////////////////////////////////////////////////////////
// CObjGeometrie
CObjGeometrie::CObjGeometrie (ITRiASCS *pICS)
:	m_CS(pICS)
{
	INITSTRUCT(m_OG, OBJGEOMETRIE);
	this->dwSize = sizeof(GEOMETRIEWITHCS);
	this->pOG = &m_OG;
	this->pICS = m_CS;
}

CObjGeometrie::~CObjGeometrie (void)
{
	Tidy();
}

void CObjGeometrie::Tidy (void)
{
	DELETE_OBJ (m_OG.pdblX);
	DELETE_OBJ (m_OG.pdblY);
	DELETE_OBJ (m_OG.plCnt);
}

bool CObjGeometrie::InitObjGeometrie (bool fIsInitialized)
{
	Tidy();
	if (!fIsInitialized && !DEX_GetObjStatistik(m_OG)) 
		return false;

	TX_TRY(m_OG.pdblX = new double [m_OG.lCnt]);
	TX_TRY(m_OG.pdblY = new double [m_OG.lCnt]);
	if (m_OG.pdblX == NULL || m_OG.pdblY == NULL)
		return false;

	if (m_OG.iKCnt > 0) {
		if (m_OG.iObjTyp == OGFlaeche) {
			TX_TRY(m_OG.plCnt = new long [m_OG.iKCnt]);
			if (m_OG.plCnt == NULL) 
				return false;
		} else if (m_OG.iObjTyp == OGText) {
		int iLen = m_OG.iKCnt;

			if (0 == iLen) iLen = _MAX_PATH;
			TX_TRY(((TEXTGEOMETRIE *)&m_OG)->pText = new char [iLen+1]);
			if (((TEXTGEOMETRIE *)&m_OG)->pText == NULL) 
				return false;
		}
	} else
		m_OG.plCnt = NULL;

	return true;
}

bool CObjGeometrie:: FillObjGeometrie (long lONrToFill)
{
	m_OG.lONr = lONrToFill;
	if (!InitObjGeometrie(false) || !DEX_GetObjGeometrie (*this)) 
		return false;

	if (m_OG.iObjTyp == OGText) {
	// Text des Textes besorgen
		try {
		GETTEXTDATA td;

			TX_TRY(((TEXTGEOMETRIE *)&m_OG)->pText = new char[m_OG.iKCnt+1]);

		// KK000203
			*((TEXTGEOMETRIE *)&m_OG)->pText = '\0';

			memset (&td, '\0', sizeof(GETTEXTDATA));
			td.dwSize = sizeof (GETTEXTDATA);
			td.m_lONr = m_OG.lONr;
			td.m_pText = ((TEXTGEOMETRIE *)&m_OG)->pText;
			td.m_iLen = m_OG.iKCnt+1;
			if (!DEX_GetTextObjectText(td)) 
				return false;

			if (*((TEXTGEOMETRIE *)&m_OG)->pText == '\0')
				strcat(((TEXTGEOMETRIE *)&m_OG)->pText, "?");

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
	m_OG.lONr = rOG.lONr;
	m_OG.iObjTyp = rOG.iObjTyp;
	m_OG.lIdent = rOG.lIdent;
	m_OG.lCnt = rOG.lCnt;		// #HK980831
	m_OG.iKCnt = rOG.iKCnt;

	if (!InitObjGeometrie(true)) 
		_com_issue_error(E_OUTOFMEMORY);

	if (rOG.iFlags & OGConverted) {
		memcpy (m_OG.pdblX, rOG.pdblX, rOG.lCnt*sizeof(double));
		memcpy (m_OG.pdblY, rOG.pdblY, rOG.lCnt*sizeof(double));
	} else {
		memcpy (m_OG.pdblX, rOG.pdblX, rOG.lCnt*sizeof(long));
		memcpy (m_OG.pdblY, rOG.pdblY, rOG.lCnt*sizeof(long));
	}

	if (rOG.iKCnt > 0) {
		if (rOG.iObjTyp == OGFlaeche) 
			memcpy (m_OG.plCnt, rOG.plCnt, rOG.iKCnt*sizeof(long));
		else if (rOG.iObjTyp == OGText) {
		TEXTGEOMETRIE &TG = (TEXTGEOMETRIE &)rOG;
		TEXTGEOMETRIE &oldTG = (TEXTGEOMETRIE &)m_OG;

			if (NULL != TG.pText) {
				TX_TRY(oldTG.pText = new char[rOG.iKCnt+1]);
				if (NULL == oldTG.pText)
					_com_issue_error(E_OUTOFMEMORY);
				strcpy (oldTG.pText, TG.pText);
			}
		}
	} 
	return m_OG;
}
