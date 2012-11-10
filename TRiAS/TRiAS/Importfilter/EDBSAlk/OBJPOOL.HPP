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
#include "Atkissat.H"

class CObjektPool
{
	CMapStringToOb		m_omGeoObjekte;
	CGeoObj				*m_pgoReady;
	CString				m_strLastGetGeoObj;
	CGeoObj				*m_pLastGetGeoObj;

public:
						CObjektPool();
						~CObjektPool();

	CGeoObj				*GetGeoObj(const char* pID);
//	void				AddGeometry( const char* pID, CGeometry* pG,
//							const char* teil, const char* folie, const char* art );
	void				AddLine( const char*, CPunktFolge*, CGeoObj *pGO, 
								const char*, const char*, const char* );
	void				AddLineBI( const char*, CPunktFolge*, CGeoObj *pGO, 
								const char*, const char*, const char* );
	void				DefType( const char*, const char*, const char*, const char* );
	void				BesondInfo( const short, const short, CAtkisSatz* );
	BOOL				AddMerkmal( CString &, CString &, CString & );
	CGeoObj				*Fertig();
	void				WriteBack( bool fStatus = false );
	short				GetSize()	{ return m_omGeoObjekte.GetCount(); }
	void				Clear();
	void				Lookup( const char* UID,CObject*& pGO ) { m_omGeoObjekte.Lookup( UID, pGO); }		
	void				Add(const char* pID, CGeoObj *pGO ) { m_omGeoObjekte.SetAt( pID, pGO ); }
};

extern CObjektPool* g_pObjektPool;

#endif // _OBJPOOL_H_
