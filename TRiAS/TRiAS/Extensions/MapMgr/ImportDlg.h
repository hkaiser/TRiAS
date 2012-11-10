// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 21:23:58 
//
// @doc
// @module ImportDlg.h | Declaration of the <c CImportDlg> class

#if !defined(AFX_IMPORTLSAANHDLG_H__245D2DA8_FE26_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_IMPORTLSAANHDLG_H__245D2DA8_FE26_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#import "TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_implementation \
	no_namespace named_guids

/////////////////////////////////////////////////////////////////////////////
// PUNKTREE ist kein Baum mit bunten Haaren,
// sondern einer der Pointer auf Unknowns hält ;-))
struct TREENODE;
struct PUNKINSPECTOR;

class PUNKTREE : 
	public map<CComBSTR, struct TREENODE> 
{
public:
	virtual ~PUNKTREE();
	HRESULT Add( LPCTSTR lpszDisplay, CComPtr<IUnknown>& p );
	int Traverse( PUNKINSPECTOR& inspector );
};

typedef struct TREENODE {
	CComPtr<IUnknown>	m_data;
	PUNKTREE	m_childs;
	TREENODE(CComPtr<IUnknown>& data);
	TREENODE();
	virtual ~TREENODE();
} TREENODE;

struct PUNKINSPECTOR 
{
	virtual void OnNode( const CComBSTR& strName, TREENODE& node ) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CMapImportDlg dialog

class CMapImportDlg;

#include "MapMgrImpl.h"
#include "PictHolder.h"

#include "PpgBase.h"
#include "PpgSelMapType.h"
#include "PpgSelFilesOrDirs.h"
#include "PpgSelDataSource.h"
#include "SelectCoordSys.h"

// KK010307
//#include "PpgSelDocFile.h"

#include "PpgSelAddFile.h"
#include "PpgNomenclatur.h"
#include "PpgMapInfo.h"
#include "PpgImportFile.h"
#include "PpgRefPoints.h"
#include "PpgIntergraph.h"

class CMapImportDlg : 
	public CPropertySheet 
{
private:
	DECLARE_DYNAMIC(CMapImportDlg)
	
	CPpgSelMapType	m_ppgSelMapType;
	CPpgSelFilesOrDirs m_ppgFiles;
	CSelectCoordSys m_ppgSelCoordSys;
	CPpgSelDataSource m_ppgDataSource;

	CPpgSelAddFile	m_ppgSelAddFile;
	CPpgNomenclatur	m_ppgNomenclatur;
	CPpgMapInfo		m_ppgMapInfo;
	CPpgImportFile	m_ppgImportFile;
	CPpgRefPoints	m_ppgRefPoints;
	CPpgIntergraph	m_ppgIntergraph;

// KK010307
//	CPpgSelDocFile	m_ppgSelDocFile;

	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_pCS;

	HRESULT	ReadEngines();
	void CorrectDirectory();

public:
	PUNKTREE	m_treeOfEngines;			// Import - Engines
	MAPPOINTER	m_pTopoMap;					// aktuelle Engine
	PICTPOINTER	m_pTopoPict;				// aktuelles Bild

	UINT		m_nNextStep;				// die nächste Seite
	vector<UINT>	m_pageWay;				// wie geht's zurück?

// KK001120
	bool	m_bMulti;						// mehrere Dateien importieren
	long	m_lMultiCount;					// Anzahl der zu importierenden Dateien

// KK010315
	list_char	 m_TopKart;					// Namen der zu importierenden Dateien
	bool		m_bNoReduce;
//	BOOL		m_bDstDir;

	CString		m_strLastDirUsed;			// Letztes benutztes Verzeichnis

	CString		m_strSrcMap;				// Name der Bilddatei
	CString		m_strIdent;					// Identifikator der Karte
	CString		m_strName;					// (nutzerfreundlicher) Name der Karte
	CSize		m_sizeOfPicture;			// physische Bildgröße
	CString		m_strMapType;				// Art der Karte
	CString		m_strDstDir;				// Name des Zielverzeichnisses beim runterrechnen

	CString		m_strAddMap;				// ggf. zusätzliche Beschreibungsdatei
	
	CString		m_strRefDir;				// Name des Verzeichnisses mit Referenzdateien
	CString		m_strMapExt;				// Extension der Beschreibungsdateien

	CString		m_strPictFileFilter;		// FilterString für Datei Öffnen Dialog
	CString		m_strDefExt;				// Default Dateierweiterung

// KK010320
	GCPList		m_gcpList;

	HPROJECT	m_hPr;

	CMapImportDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMapImportDlg();

	TOPOMAP			m_mapInfo;		// aus libtopomap.h

	bool	CheckInfile();
	bool	ReduceInFile(CFilterProgress &progressChunk, CFilterProgress &progressItem);
	bool	Finish();

	bool	ReduceMapFile(void );

	void	SetCoordSystemIsLast(bool fFlag);

// Dialog Data
	//{{AFX_DATA(CMapImportDlg)
	enum { IDD = IDS_MAPIMPORTCAPTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMapImportDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTLSAANHDLG_H__245D2DA8_FE26_11D1_8F55_0060085FC1CE__INCLUDED_)
