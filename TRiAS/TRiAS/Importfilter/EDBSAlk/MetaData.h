// MetaData.h: interface for the CMetaData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METADATA_H__1000E1D1_2D04_11D2_BE23_08003616D303__INCLUDED_)
#define AFX_METADATA_H__1000E1D1_2D04_11D2_BE23_08003616D303__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxcoll.h>
#include <afxdb.h>
#include "Cfg.h"
#include "CxString.h"
#include "geoobj.hpp"

#include "Rule_Line.h"
#include "Rule_Layer.h"
#include "Rule_Info.h"
#include "Rule_Geom.h"
#include "Rule_Attr.h"
#include "Rule_Text.h"


#define EDBS_IMPORTALWAYS		255
#define EDBS_IMPORTAUTOMATIC	1
#define EDBS_IMPORTNEVER		0

class CRegel
{
	CStringList			m_listMerkmale;
	CMapStringToString	m_mapWerte;

	void				And( CString&, const char* );
	void				LiesRegel( const char*, char&, const char* );

public:
						CRegel( const char*, const CString& strIniFileName );
	BOOL				GetIdent( CMapStringToString*, CString& );
	CMapStringToString	*MapWerte()		{ return &m_mapWerte; }
};

//=== TRiAS ===================================================================================
class CObjectClassTRiAS : public CObject
{
private:
	unsigned long	m_lIdent;			// in TRiAS intern verwendeter Identifikator
	unsigned long	m_ulClassId;		// in TRiAS intern verwendeter Identifikator
	CString			m_strClassX;
	CString			m_strClassName;
	CString			m_strClassDescription;
	bool			m_bUsed;
	long			m_lImportMode;
	bool			m_tRegelwidrig;
	CMapStringToOb	m_Attributes;

public:
					CObjectClassTRiAS( const char* strClassDefinition, bool bHexbase );
					~CObjectClassTRiAS();
					
	unsigned long	&ClassIdentTRiAS()	{ return m_lIdent; }
	unsigned long	&ClassId()			{ return m_ulClassId; }
	CString			&ClassX()			{ return m_strClassX; }
	CString			&ClassName()		{ return m_strClassName; }
	CString			&ClassDescription()	{ return m_strClassDescription; }
	CMapStringToOb	&Attributes( void )	{ return m_Attributes; }

	bool			&Used()				{ return m_bUsed; }
	long			&ImportMode()		{ return m_lImportMode; }
	void			Regelwidrig( bool tRegelwidrig )	{ m_tRegelwidrig = tRegelwidrig; }
	bool			Regelwidrig()		{ return m_tRegelwidrig; }
};

//=== EDBS ====================================================================================
/*
class CEDBSFolie : public CObject
{
protected:
	CString			m_strFolie;
	CString			m_strKurztext;
	CString			m_strLangtext;
	CString			m_strOKS_TRiAS;
	bool			m_tImport;
	bool			m_tResolve;

public:
					CEDBSFolie( const char* strDefinition );
	CString			&Folie()			{ return m_strFolie; }
	CString			&Kurztext()			{ return m_strKurztext; }
	CString			&Langtext()			{ return m_strLangtext; }
	CString			&OKS_TRiAS()		{ return m_strOKS_TRiAS; }
	void			Import( bool tImport ) { m_tImport = tImport; }
	bool			Import( void )		{ return m_tImport; }
	void			Resolve( bool tResolve ) { m_tResolve = tResolve; }
	bool			Resolve( void )		{ return m_tResolve; }
};
*/
class CObjectClassEDBS : public CObject
{
	unsigned long	m_lClassId;
	CString			m_strClassX;
	CString			m_strClassName;
	CString			m_strClassDescription;
	bool			m_bIgnored;
public:
					CObjectClassEDBS( const char* strClassDefinition );
	unsigned long	&ClassId()			{ return m_lClassId; }
	CString			&ClassName()		{ return m_strClassName; }
	CString			&ClassDescription()	{ return m_strClassDescription; }
	void			Ignore( bool bIgnore )	{ m_bIgnored = bIgnore; }
	bool			Ignored(void)		{ return m_bIgnored; }
};

class CObjectClassesEDBS : public CObArray
{
public:
						CObjectClassesEDBS()	{}
						~CObjectClassesEDBS();
	void				Add( const char* strObjectClassEDBS );
	void				Ignore( const char* strObjectClassEDBS, bool bIgnore );
	bool				Ignored( const char* strObjectClassEDBS );
	bool				Ignored( unsigned long ulObjectClassId );
	CObjectClassEDBS*	Get( unsigned long );
	CObjectClassEDBS*	Get( const char* strObjectClassEDBS );
};

//=== Klassifikation ==========================================================================
class CClassificator : public CObject
{
	unsigned long	m_lClassIdTRiAS;	// TRIAS - Kode
	unsigned long	m_lClassIdEDBS;		// EDBS - Kode
	CString			m_strObjectClassTRiAS;
	bool			m_tImportieren;			// Objektklasse nicht importieren
	bool			m_tRegelwidrig;
public:
					CClassificator( const char *strKeyEDBS, const char* strKeyTRiAS, bool );
					~CClassificator()		{}
	CString			&ObjectClassTRiAS()		{ return m_strObjectClassTRiAS; }
	unsigned long	ClassIdTRiAS()			{ return m_lClassIdTRiAS; }
	long			ClassIdEDBS()			{ return m_lClassIdEDBS; }
	void			Importieren( bool tImportieren )	{ m_tImportieren = tImportieren; }
	bool			Importieren()				{ return m_tImportieren; }
	void			Regelwidrig( bool tRegelwidrig )	{ m_tRegelwidrig = tRegelwidrig; }
	bool			Regelwidrig()		{ return m_tRegelwidrig; }
};

class CClassification : public CMapStringToOb
{
public:
					CClassification()	{}
					~CClassification();
	void			Add( const char* strKeyEDBS, const char* strKeyTRiAS, bool bHexbase);
	void			Importieren( const char* def, bool bIgnore );
	unsigned long	Classify( const char* def );
	bool			Importieren( const char* def );
};

class CKodeTabelle : public CObArray
{
	char			m_Typ;

public:
	void			LoadAttributes();
					CKodeTabelle()		{ m_Typ = '\0'; }
					~CKodeTabelle();
	void			SetTyp( char t )	{ if ( m_Typ == '\0' ) m_Typ = t; }
	long			FindeKode( const char* );
	bool			Add( unsigned long ulObjectClassTRiAS, long, const char*, const char* = NULL );
	bool			AddMMK( unsigned long ulObjectClassTRiAS, const char*, bool );
	bool			Mod( long, const char*, const char* = NULL );
	bool			KodeExist( long );
};

class CMetaData  
{
	bool				m_bHexIdents;
	bool				m_bHexMKodes;

	bool				m_bCreateErrorLog;
	bool				m_bCompleteAttr;
	CObjectClassesEDBS	m_ObjectClassesEDBS;
	CMapStringToOb		m_ObjectClassesTRiAS;
//	CKodeTabelle		m_UsedObjectClassesTRiAS;
	CKodeTabelle		m_ObjectAttributesTRiAS;
	CClassification		m_Classification;

	CMapStringToPtr		m_B_Rules;
	CString				m_strKomplexobjekte;	//Notlösung zur Erzwingung der Erstellung mehrerer Einzelobjekte
//	CMapStringToPtr		m_EDBSXXinstances;

public:
	long				m_lVerDatabase;
	CRule_Info* GetRule_Info( CString &strKey );
	void LoadRules_Info( void );
	CRule_Line* GetRule_Line( CString &strKey );
	void LoadRules_Line( void );
//	void LoadRules( const CxString& strKeyEDBS, const CxString& strRules  );
	void LoadRules_Layer( void );
	void LoadRules_Attr( void );
	void LoadRules_Geom( void );
	void LoadRules_Text( void );
	CRule_Layer *MapObjectClassEDBStoObjectClassTRiAS( CGeoObj& GeoObject, CString &strObjectClassTRiAS );
	CCfg				*pConfiguration;
	CxString			strIniFileName;
	CxString			strIniFileName2;
// Vorgaben für Verarbeitung der Koordinaten
	double				m_dKoeffEDBS;
// Vorgaben für das Koordinatensystem
	long				m_lOffsetX;
	long				m_lOffsetY;
	double				m_dKoeff11;
	double				m_dKoeff12;
	double				m_dKoeff21;
	double				m_dKoeff22;
	short				m_sRH;
	short				m_sKoordinatensystem;

	CxString			m_strObjectClassesTRiAS;
	CxString			m_strObjectAttributesTRiAS;
	CxString			m_strObjectClassesEDBS;

	CMapStringToOb		m_Rules_Line;
	CMapStringToOb		m_Rules_Layer;
	CMapStringToOb		m_Rules_Info;
	CMapStringToOb		m_Rules_Geom;
	CMapStringToOb		m_Rules_Attr;
	CMapStringToOb		m_Rules_Text;

	bool Komplexobjekt( CString strFolieObjektart ); //Notlösung
	CMetaData();
	virtual ~CMetaData();
	void Load( void );
	void LoadObjectClassesTRiAS( void );
	void LoadObjectAttributesTRiAS( unsigned long ulObjectClassTRiAS );
	void LoadObjectClassesEDBS( void );
	void LoadClassification( void );

	CMapStringToOb		&ObjectClassesTRiAS()	{ return m_ObjectClassesTRiAS; }

	void SetDefinition( const CString& strDef );

	CObjectClassTRiAS * GetObjectClassTRiAS( CString &strObjectClassTRiAS);
	CRule_Layer *GetRule_Layer( CString &strKey,  BOOL fDefault = TRUE );
	CRule_Attr *GetRule_Attr( CString &strKey );
	CRule_Text *GetRule_Text( CString &strKey );
	CRule_Geom *GetRule_Geom( CString &strKey );

//	void AddRule( const char* );
//	void GetClassX( const char* strK, CMapStringToString* pmm, CString &strClassX );
//	CObjectClassTRiAS* GetObjectClassTRiAS( unsigned long x ) { return m_ObjectClassesTRiAS.Get(x); }
	CObjectClassEDBS* GetObjectClassEDBS( const char* x ) { return m_ObjectClassesEDBS.Get(x); }
	long GetTriasAttributeIdent( const char* kurz );
	bool ClassifyGeoObject( CGeoObj& GeoObject );
//	unsigned long BildeIdent( const char *objart );
	bool CreateErrorLog( void ) { return m_bCreateErrorLog; }
	CStringList ErrorLogAttributes;
	CxString	Filter;
	double	dArcPrecision;
};

extern CMetaData	*g_pMetaData;

#endif // !defined(AFX_METADATA_H__1000E1D1_2D04_11D2_BE23_08003616D303__INCLUDED_)
