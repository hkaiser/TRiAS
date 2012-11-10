// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:41:19 
//
// @doc
// @module ExportHelper.h | Declaration of the <c CExportHelper> class

#if !defined(_EXPORTHELPER_H__028AC580_D703_4346_92CD_A9916D72F460__INCLUDED_)
#define _EXPORTHELPER_H__028AC580_D703_4346_92CD_A9916D72F460__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Shapelib/Shapefil.h>
#include "MapInfoDataSource.h"

///////////////////////////////////////////////////////////////////////////////
// hält sämtliche für den laufenden Export relevanten Informationen
class CExportHelper
{
public:
	CExportHelper() : m_hPr(NULL) {}
	~CExportHelper() {}

	HRESULT DeleteAllFiles()		// alles bisherige löschen
	{
		return m_DataSource.DeleteAllFiles();
	}
	HRESULT CloseAll()				// alles geöffnete wieder schließen
	{
		return m_DataSource.CloseAll();
	}

	HRESULT SetRootDir (LPCSTR pcDirName, OutMode OutFlag);
	HRESULT GetRootDir (LPSTR pBuffer = NULL);
	HRESULT ResetRootDir();
	
	HRESULT SetDataSource (LPCSTR pcDataSource);
	HRESULT CreateLayer (INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, CMapInfoLayer **ppLayer)
	{
		return m_DataSource.CreateLayer(lIdent, pcName, rgType, ppLayer);
	}
	HRESULT GetLayer (INT_PTR lIdent, OBJECTTYPE rgType, CMapInfoLayer **ppLayer)
	{
		return m_DataSource.GetLayer(lIdent, rgType, ppLayer);
	}
	HPROJECT GetActDataSource() { return m_hPr; }
	
protected:
	CMapInfoDataSource m_DataSource;
	HPROJECT m_hPr;
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
OBJECTTYPE ObjType2OBJECTTYPE (long lObjType, bool fTreatTextAsPoint = false);

#endif // !defined(_EXPORTHELPER_H__028AC580_D703_4346_92CD_A9916D72F460__INCLUDED_)
