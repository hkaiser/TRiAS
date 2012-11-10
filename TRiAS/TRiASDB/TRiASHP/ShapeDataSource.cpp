// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.05.2000 17:13:37
//
// @doc
// @module ShapeDataSource.cpp | Implementation of the <c CShapeDataSource> class

#include "stdafx.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <ospace/file/path.h>

#include "resource.h"
#include "Strings.h"
#include "TRiASHP.h"
#include "DBUtil.h"

#include "ShapeDataSource.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Open a ShapeDatasource (all shp files in a directory)
HRESULT CShapeDataSource::Open(const char *pszNewName, bool fUpdate, bool fTestOpen)
{
	_ASSERTE(0 == m_Layers.size());
	_ASSERTE(NULL != pszNewName);

struct _stat stat;
	
	m_strName = pszNewName;
	m_fUpdatable = fUpdate;
	
// Is the given path a directory or a regular file?
os_string strPath (pszNewName);		// evtl. abschlieﬂendes '\' abschneiden
size_t pos = strPath.find_last_of("\\/");

	if (os_npos != pos && pos == strPath.size()-1) 
		strPath.replace(pos, 1, "");

	if (0 != _stat(strPath.c_str(), &stat) || (!(stat.st_mode & _S_IFDIR) && !(stat.st_mode & _S_IFREG)))
	{
		if (fTestOpen)
			return S_FALSE;
		return TRIASHP_E_BADFILENAME; 
	}
	
// Build a list of filenames we figure are Shape files.
	if (stat.st_mode & _S_IFREG) {
	// given name relates to a file
		if (S_OK != OpenFile(pszNewName, fUpdate, fTestOpen)) {
			if (fTestOpen)
				return S_FALSE;
			return TRIASHP_E_OPENFILE_FAILED;
		}
		return S_OK;
	}
	else {
	vector<os_string> Candidates;
	vector<os_string> Failed;
	os_path dir (pszNewName);

		RETURN_FAILED_HRESULT(ReadDir (pszNewName, Candidates));
		for (vector<os_string>::iterator it = Candidates.begin(); it != Candidates.end(); ++it) {
		os_path path (*it);

			if (stricmp (path.extension().c_str(), g_cbShp))
				continue;

		// vollst‰ndigen Dateinamen bauen
			if (dir.has_directory()) 
				path.directory(dir.directory());
			if (dir.has_drive()) 
				path.drive(*dir.drive().c_str());

			if (S_OK != OpenFile (os_string(path).c_str(), fUpdate, fTestOpen) && !fTestOpen) 
				Failed.push_back(os_string(path));
		}

		if (!fTestOpen && 0 == m_Layers.size() && !fUpdate) {
			if (!m_fDeniedToOpen) {
			os_path datasource(strPath);

				VMessageBox(IDS_DBENGINE_DESC, MB_ICONEXCLAMATION|MB_OK, 
					IDS_COULDNOTOPENSHAPE, datasource.base().c_str());
				m_fDeniedToOpen = true;
			}
			return TRIASHP_W_NOFILESFOUND;
		}

	// Fehlerbahandlung
		if (Failed.size() > 0) {
		int iResult = IDNO;

			if (!m_fDeniedToOpen) {
			os_path datasource(strPath);

				if (1 == Failed.size()) {
					iResult = VMessageBox(IDS_DBENGINE_DESC, MB_ICONQUESTION|MB_YESNO, 
						IDS_COULDNOTOPENFILE, Failed[0].c_str(), datasource.base().c_str());
				}
				else {
				os_string failed;

					for (vector<os_string>::iterator it = Failed.begin();
						 it != Failed.end(); ++it)
					{
						failed += "    ";
						failed += *it;
						failed += '\n';
					}
					iResult = VMessageBox(IDS_DBENGINE_DESC, MB_ICONQUESTION|MB_YESNO, 
						IDS_COULDNOTOPENFILES, failed.c_str(), datasource.base().c_str());
				}
				m_fDeniedToOpen = true;
			}
			if (IDNO == iResult) {
				m_Layers.clear();
				return TRIASHP_E_OPENFILE_FAILED;
			}
		}
	}


// Datenbank jetzt geˆffnet
	m_fOpened = true;
	return (m_Layers.size() > 0 || fUpdate) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Eine Shapedatei ˆffnen
HRESULT CShapeDataSource::OpenFile(const char *pszNewName, bool fUpdate, bool fTestOpen)
{
	_ASSERTE(NULL != pszNewName);
	if (NULL == pszNewName)
		return E_POINTER;

SHPHandle hSHP = NULL;
DBFHandle hDBF = NULL;

	if (fUpdate)
		hSHP = SHPOpen (pszNewName, "r+");
	else
		hSHP = SHPOpen (pszNewName, "r");
	if (NULL == hSHP)
		return S_FALSE;
	
// Open the .dbf file, if it exists.
	if (fUpdate)
		hDBF = DBFOpen (pszNewName, "rb+");
	else
		hDBF = DBFOpen (pszNewName, "rb");

// Extract the basename of the file.
	COM_TRY {
	// Create the layer object and add layer to data source layer list.
	os_path path (pszNewName);

		m_Layers.push_back (new CShapeLayer(path.base().c_str(), hSHP, hDBF, fUpdate));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Schlieﬂen einer Datenbank
HRESULT CShapeDataSource::Close()
{
	COM_TRY {
	// Layer schlieﬂen
		for (CShapeLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) 
			(*it) -> Close();

	// alles freigeben
		m_Layers.clear();
		m_fOpened = false;		// nicht mehr geˆffnet

	} COM_CATCH;
	return S_OK;
}

#if defined(_READWRITE)
///////////////////////////////////////////////////////////////////////////////
// Neuen Layer erzeugen
CShapeLayer *CShapeDataSource::CreateLayer (
	const char *pcName, OBJECTTYPE rgType, ITRiASCSTransform *pSpatRef)
{
	_ASSERTE(NULL != pcName);
	if (NULL == pcName) {
		SetLastError(E_POINTER);
		return NULL;
	}

// Verify we are in update mode.
    if (!m_fUpdatable) {
		SetLastError(TRIASDB_W_ISREADONLY);
		return NULL;
	}

// Verify uniqueness of the Shapename
	for (CShapeLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) {
		if (!stricmp ((*it) -> GetName(), pcName)) {
		// Layername muﬂ unique sein
			SetLastError (TRIASHP_W_LAYERNAME_NOT_UNIQUE);
			return NULL;
		}
	}

// Figure out what type of layer we need
int nShapeType = -1;

	if (rgType == OBJECTTYPE_Line)
		nShapeType = SHPT_ARC;
	else if (rgType == OBJECTTYPE_Point)
		nShapeType = SHPT_POINT;
	else if (rgType == OBJECTTYPE_Area)
		nShapeType = SHPT_POLYGON;
	else 
		nShapeType = -1;

//	if (-1 == nShapeType) {
//		SetLastError (TRIASHP_E_BADGEOMETRYTYPE);
//		return NULL;
//	}

CShapeLayer *poLayer = NULL;

	COM_TRY {
	// Create the shapefile
	os_path dir (m_strName);
	os_path path (pcName);

	// vollst‰ndigen Dateinamen bauen
		path.extension(g_cbShp);
		if (dir.has_directory()) 
			path.directory(dir.directory());
		if (dir.has_drive()) 
			path.drive(*dir.drive().c_str());
		
	SHPHandle hSHP = SHPCreate(os_string(path).c_str(), nShapeType);

		if (NULL == hSHP) {
			SetLastError (TRIASHP_E_OPENFILE_FAILED);
			return NULL;
		}

	// Create a DBF file
		path.extension(g_cbDbf);

	DBFHandle hDBF = DBFCreate(os_string(path).c_str());

		if (NULL == hDBF) {
			SetLastError (TRIASHP_E_OPENFILE_FAILED);
			return NULL;
		}

// Create the layer object and add layer to data source layer list
		m_fUpdatable = true;
		poLayer = new CShapeLayer (pcName, hSHP, hDBF, TRUE);
		m_Layers.push_back (poLayer);

	} COM_CATCH_RETURN(NULL);

	SetLastError (S_OK);
	return poLayer;
}
#endif // defined(_READWRITE)
