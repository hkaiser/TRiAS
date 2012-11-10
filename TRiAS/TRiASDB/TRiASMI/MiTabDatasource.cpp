// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.01.2001 20:15:21 
//
// @doc
// @module MiTabDatasource.cpp | Definition of the <c CMiTabDatasource> class

#include "StdAfx.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <ospace/file/path.h>

#include "Strings.h"
#include "MiTabDatasource.h"

///////////////////////////////////////////////////////////////////////////////
// Datenbank öffnen
HRESULT CMiTabDatasource::Open(const char *pszNewName, bool fUpdate, bool fTestOpen)
{
	_ASSERTE(0 == m_Layers.size());
	_ASSERTE(NULL != pszNewName);

struct _stat stat;
	
	m_strName = pszNewName;
	m_fUpdatable = fUpdate;
	
// Is the given path a directory or a regular file?
os_string strPath (pszNewName);		// evtl. abschließendes '\' abschneiden
size_t pos = strPath.find_last_of("\\/");

	if (os_npos != pos && pos == strPath.size()-1) 
		strPath.replace(pos, 1, "");

	if (0 != _stat(strPath.c_str(), &stat) || (!(stat.st_mode & _S_IFDIR) && !(stat.st_mode & _S_IFREG)))
	{
		if (fTestOpen)
			return S_FALSE;
		return TRIASMI_E_BADFILENAME; 
	}
	
// Build a list of filenames we figure are MapInfo files.
	if (stat.st_mode & _S_IFREG) {
	// given name relates to a file
		if (S_OK != OpenFile(pszNewName, fUpdate, fTestOpen)) {
			if (fTestOpen)
				return S_FALSE;
			return TRIASMI_E_OPENFILE_FAILED;
		}
		return S_OK;
	}
	else {
	vector<os_string> Candidates;
	os_path dir (pszNewName);

		RETURN_FAILED_HRESULT(ReadDir (pszNewName, Candidates));
		for (vector<os_string>::iterator it = Candidates.begin(); it != Candidates.end(); ++it) {
		os_path path (*it);

			if (stricmp (path.extension().c_str(), g_cbMif) && stricmp (path.extension().c_str(), g_cbTab))
				continue;

		// vollständigen Dateinamen bauen
			if (dir.has_directory()) 
				path.directory(dir.directory());
			if (dir.has_drive()) 
				path.drive(*dir.drive().c_str());

			if (S_OK != OpenFile (os_string(path).c_str(), fUpdate, fTestOpen) && !fTestOpen)
			{
				return TRIASMI_E_OPENFILE_FAILED;
			}
		}

		if (!fTestOpen && 0 == m_Layers.size() && !fUpdate) 
		{
			return TRIASMI_W_NOFILESFOUND;
		}
	}

// Datenbank jetzt geöffnet
	m_fOpened = true;
	return (m_Layers.size() > 0 || fUpdate) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Eine MapInfodatei öffnen
HRESULT CMiTabDatasource::OpenFile(const char *pszNewName, bool fUpdate, bool fTestOpen)
{
	_ASSERTE(NULL != pszNewName);
	if (NULL == pszNewName)
		return E_POINTER;

mitab_handle hMIF = NULL;

#if defined(_READWRITE)
	if (fUpdate)
		hMIF = mitab_c_create(pszNewName, NULL, NULL, 0.0, 0.0, 0.0, 0.0);
	else
#endif // defined(_READWRITE)
		hMIF = mitab_c_open (pszNewName);
	if (NULL == hMIF)
		return S_FALSE;
	
// Extract the basename of the file.
	COM_TRY {
	// Create the layer object and add layer to data source layer list.
	os_path path (pszNewName);

		m_Layers.push_back (new CMiTabLayer(path.base().c_str(), hMIF, fUpdate));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Schließen der Datenbank
HRESULT CMiTabDatasource::Close()
{
	COM_TRY {
	// Layer schließen
		for (CMiTabLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) 
			(*it) -> Close();

	// alles freigeben
		m_Layers.clear();
		m_fOpened = false;		// nicht mehr geöffnet

	} COM_CATCH;
	return S_OK;
}

