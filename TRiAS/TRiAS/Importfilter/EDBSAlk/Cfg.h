// Cfg.h: Schnittstelle für die Klasse CCfg.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFG_H__BE00DF76_9C09_11D3_8E57_00105AF354F9__INCLUDED_)
#define AFX_CFG_H__BE00DF76_9C09_11D3_8E57_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>		// CRegKey

#include <xtension.h>

#define EDBSCFG_DEFAULTOBJECTMAPPING		0x00000001
#define EDBSCFG_OVERWRITERULES				0x00000002

#define EDBSCFG_IMPORTAREAS					0x00000010
#define EDBSCFG_IMPORTLINES					0x00000020
#define EDBSCFG_IMPORTPOINTS				0x00000040
#define EDBSCFG_IMPORTTEXT					0x00000080

#define EDBSCFG_CREATEBIGEOM				0x00000700
#define EDBSCFG_CREATEBITEXT				0x00000800

#define EDBSCFG_IMPORTATTR					0x00001000
#define EDBSCFG_CREATEEDBSATTR				0x00002000
#define EDBSCFG_CREATEBIATTR				0x00004000

#define EDBSCFG_IMPORTKSIG					0x00010000
#define EDBSCFG_IMPORTVPKT					0x00020000

#define EDBSCFG_CREATEATTRDATEINAME			0x01000000
#define EDBSCFG_CREATEATTRFOLIE				0x02000000
#define EDBSCFG_CREATEATTROBJEKTART			0x04000000
#define EDBSCFG_CREATEATTROBJEKTNUMMER		0x08000000
#define EDBSCFG_CREATEATTROBJEKTTEILNUMMER	0x10000000
#define EDBSCFG_CREATEATTROBJEKTTEILNUMMERK	0x20000000
#define EDBSCFG_CREATEATTRAKTUALITAET		0x40000000
#define EDBSCFG_CREATEATTRREGELN			0x80000000

BOOL UpdateEDBSRegistry( BOOL fRegister );

class CCfg  
{
public:
	CString GetCfgDbEntry( CString strKey );
	void ConnectCfgDb( void );
	void LoadCfgDbs( void );
	void Save( void );
	void Load();
	CCfg();
	~CCfg();

	CString				m_strAccessDriverName;
	CString				m_strTRiASName;
	DWORD				m_dwSystemAdministration;
	CString				m_strConfigPath;
	CString				m_strConfigFile;
	bool				m_tEnabled;
	CMapStringToOb		m_CfgDbs;
	CDatabase			m_dbCfg;
	DWORD				m_dwConfigBase;
	DWORD				m_dwReportBase;

	short				m_sCodePage;
	bool				m_tDefaultObjectMapping;
	bool				m_tOverwriteRules;
	CString				m_strObjectClassesTRiAS;
	CString				m_strObjectAttributesTRiAS;
	bool				m_tCreateBIgeom;
	bool				m_tCreateBItext;

	bool				m_tImportAttr;
	bool				m_tCreateEDBSattr;
	bool				m_tCreateBIattr;
	
	bool				m_tImportKSIG;
	bool				m_tImportVPKT;

	bool				m_tImportAreas;
	bool				m_tImportLines;
	bool				m_tImportPoints;
	bool				m_tImportText;

	bool				m_tCreateAttributeDateiname;
	bool				m_tCreateAttributeFolie;
	bool				m_tCreateAttributeObjektart;
	bool				m_tCreateAttributeObjektnummer;
	bool				m_tCreateAttributeObjektteilnummer;
	bool				m_tCreateAttributeObjektteilnummerK;
	bool				m_tCreateAttributeAktualitaet;
	bool				m_tCreateAttributeRegeln;
};

#endif // !defined(AFX_CFG_H__BE00DF76_9C09_11D3_8E57_00105AF354F9__INCLUDED_)
