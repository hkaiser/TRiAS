// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 10:59:02 
//
// @doc
// @module GPSImportThread.cpp 

/////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"		// main symbols

#include "GPSImportDlg.h"

#include <ospace/file/path.h>
#include "boost/directory.h"

using namespace boost::filesystem;



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT WM_GPSIMPORTSTATUS = RegisterWindowMessage("WM_GPSIMPORTSTATUS");
const UINT WM_THREADCALLBACK = RegisterWindowMessage("WM_THREADCALLBACK");
const UINT WM_THREADERROR = RegisterWindowMessage("WM_THREADERROR");

/////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Threadinitialisierung
bool IsValidDLKName (os_path &rName)
{
string base (rName.base());

	if (3 > base.size())
		return false;		// falsche Länge

	return true;
}

void FindFilesFromPattern (os_path &rPath, set<string> &rFiles, LPCSTR pcPattern)
{

		rFiles.insert(string(rPath));
/*
dir_it end;

	for (dir_it it (string(rPath).c_str(), pcPattern); it != end; ++it) {
		if (get<is_directory>(it))
			continue;

	// Namenskonvention prüfen
	os_path file = *it;

		if (!IsValidDLKName(file))
			continue;

	// Datei speichern
		if (rPath.has_directory())
			file.directory(string(rPath));
		else if (rPath.has_drive())
			file.drive(rPath.drive()[0]);
		else if (rPath.has_unc())
			file.unc(rPath.server(), rPath.share());

		rFiles.insert(string(file));
	}

  */

}
///////////////////////////////////////////////////////////////////////////////////////////
BOOL CGPSImportDlg::OnInitializeHandler()
{


	_ASSERTE(m_CopyData.m_strDestPath.GetLength() > 0 &&
			 m_CopyData.m_strSourcePath.GetLength() > 0);

	os_path src = (LPCSTR)m_CopyData.m_strSourcePath;

//	FindFilesFromPattern(src, m_vecFiles, "*.bna");

	m_vecFiles = m_sleSourcePath.m_Files;

	if (0 == m_vecFiles.size())
		return FALSE;		// nothing to copy

	m_iMinRange = 0;;
	m_iMaxRange = m_vecFiles.size();

// Thread
//	void *pOwner = this->GetActiveWindow();
//	((CWnd *)pOwner) -> SendMessage(WM_THREADCALLBACK,CMD_INITIALIZE, FALSE);
	OnThreadCallback(CMD_INITIALIZE, 0);


// Progressbar initialisieren
	OnGPSImportStatus(PBM_SETRANGE, MAKELPARAM(0, m_vecFiles.size()));
	OnGPSImportStatus(PBM_SETPOS, 0);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Hier erfolgt das eigentliche Kopieren
bool CalculateDestinationPath (string const &rName, string Ext,os_path &rRelPath)
{
os_path fullname = rName;
string base = fullname.base();
char cbBuffer[_MAX_PATH];

	if (!IsValidDLKName(os_path(base.c_str())))
		return false;

	wsprintf(cbBuffer, ".\\%s.%s",
		base.c_str(), Ext.c_str());

	rRelPath = cbBuffer;
	return true;
}

bool EnsureDestinationPath (os_path const &rPath, os_path const &rName, 
	os_path &rFullName)
{
	rFullName = string(rPath) + string(rName);
	rFullName.become_simplified();

string dir_to_create;

	if (rFullName.has_drive()) {
		dir_to_create = rFullName.drive() + rFullName.drive_separator() + 
			rFullName.default_path_separator();
	} else if (rFullName.has_unc()) {
		dir_to_create = string("\\\\") + rFullName.server() + 
			rFullName.default_path_separator() + rFullName.share() + 
			rFullName.default_path_separator();
	}

	for (int i = 0; i < rFullName.levels(); ++i) {
		dir_to_create += rFullName[i];
		dir_to_create += rFullName.default_path_separator();
		CreateDirectory(dir_to_create.c_str(), NULL);
	}
	return true;
}

void CGPSImportDlg::OnRunHandler()
{

	OnThreadCallback(CMD_RUN,0);

	os_path destpath = (LPCSTR)m_CopyData.m_strDestPath;

	if (destpath.base().size() > 0)
		destpath.base("");
	if (destpath.has_extension())
		destpath.no_extension();

	set<string>::iterator end = m_vecFiles.end();
	int i = 0;

	for (set<string>::iterator it = m_vecFiles.begin(); it != end; ++it, ++i) {
	os_path dest, fulldest;
	string Ext;

		if (m_iType)
			Ext = m_Extrte;
		else
			Ext = m_Exttrk;

		if (CalculateDestinationPath (*it, Ext,dest) &&				// Zielpfad berechnen
			EnsureDestinationPath (destpath, dest, fulldest))	// Zielpfad physisch erzeugen
		{
		// Datei bearbeiten und kopieren
			if (!ImportBNA((*it).c_str(),string(fulldest).c_str())) {
				break;
			}
		}

	// Progressbar weitersetzen
		OnGPSImportStatus(PBM_SETPOS, i+1);

		if (m_fMustStop)
			break;		// wir sollen aufhören

	}

}
