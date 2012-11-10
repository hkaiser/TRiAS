// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 13:57:56
//
// @doc
// @module ExportHelper.cpp | Implementation of the <c CExportHelper> class

#include "StdAfx.h"
#include "ArcViewImpl.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "Strings.h"
#include "ArcView.hmc"
#include "../ExtDataEngineImpl.h"
#include "ExportHelper.h"

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
OBJECTTYPE ObjType2OBJECTTYPE (long lObjType, bool fTreatTextAsPoint)
{
	switch (lObjType) {
	case OT_PUNKT:
		return OBJECTTYPE_Point;

	case OT_TEXT:
		return fTreatTextAsPoint ? OBJECTTYPE_Point : OBJECTTYPE_Text;

	case OT_KANTE:
		return OBJECTTYPE_Line;

	case OT_FLAECHE:
		return OBJECTTYPE_Area;

	default:
		return OBJECTTYPE_Unknown;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Wurzelverzeichnise setzen und auf Korrektheit testen
HRESULT CExportHelper::SetRootDir(LPCSTR pcDirName, OutMode rgOutFlag)
{
// Is the given path a directory or a regular file?
os_string strPath (pcDirName);		// evtl. abschlieﬂendes '\' abschneiden
size_t pos = strPath.find_last_of("\\/");
struct _stat stat;

	if (os_npos != pos && pos == strPath.size()-1) 
		strPath.replace(pos, 1, "");

	if (0 != _stat(strPath.c_str(), &stat) || (!(stat.st_mode & _S_IFDIR) && !(stat.st_mode & _S_IFREG)))
		return ARCVIEW_E_BADFILENAME; 
	
	m_DataSource.SetRootDir(pcDirName, rgOutFlag);
	return S_OK;
}

HRESULT CExportHelper::GetRootDir(LPSTR pBuffer)
{
LPCSTR pcRoot = m_DataSource.GetRootDir();

	if (NULL != pcRoot && '\0' != pcRoot[0]) {
		if (NULL != pBuffer)
			strcpy (pBuffer, pcRoot);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CExportHelper::ResetRootDir()
{
	m_DataSource.SetRootDir(g_cbNil, OMUnknown);
	return S_OK;
}

HRESULT CExportHelper::SetDataSource (LPCSTR pcDataSource)
{
	m_hPr = DEX_GetDataSourceHandleEx(pcDataSource);
	return (NULL != m_hPr) ? S_OK : E_UNEXPECTED;
}

