///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			objpool.hpp
//
//	Stand:			02.12.1994
//	Beschreibung:	ObjektPool-Objekt
//					- Erzeugen der GeoObjekte
//					- Verändern der GeoObjekte
//					- Schreiben der GeoObjekte nach TRIAS
//	Entwicklung:	02.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef _OBJPOOL_H_
#define _OBJPOOL_H_

#include "geoobj.hpp"

class CObjektPool
{
	CMapStringToOb		m_omGeoObjekte;
	CMapStringToOb		m_omObsoleteGO;
	CMapStringToPtr		m_mapMultiObj;
	CGeoObj				*m_pgoReady;

public:
	BOOL				PrepareObjTeile();
	void				SetupObjTeile( const char*, CGeoObj* );
						CObjektPool();
						~CObjektPool();

	void				AddLine( const char*, CPunktFolge*,
								const char*, const char*, const char* );
	void				DefType( const char*, const char*, const char*, const char* );
	void				BesondInfo( const char*, const char*, const char*, const char*, double, double );
	BOOL				AddMerkmal( const char*, const char*, const char* );
	CGeoObj				*Fertig();
	void				WriteBack( bool = false );
	short				GetSize()	{ return m_omGeoObjekte.GetCount(); }
	void				Clear();
	BOOL ConvertToText (class CGeoObj *pGO, class CTriasObjekt *pTO);
	BOOL AddFloeDelta (const char *pObjNr, const char *pObjTeilNr);

// #HK000813: BEGIN
	BOOL Lookup (LPCSTR pcId, CGeoObj **ppGO)
	{ 
	CGeoObj *pGO = NULL;
		
		if (m_omGeoObjekte.Lookup (pcId, (CObject *&)pGO)) {
			*ppGO = pGO;
			return TRUE;
		}
		return FALSE;
	}
// #HK000813: END
};


#endif // _OBJPOOL_H_
