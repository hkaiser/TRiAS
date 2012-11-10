// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 13:55:01 
//
// @doc
// @module ExportHelper.h | Declaration of the <c CExportHelper> class

#if !defined(_EXPORTHELPER_H__A6C85B60_836B_4D29_B363_16DA7CD0FEDE__INCLUDED_)
#define _EXPORTHELPER_H__A6C85B60_836B_4D29_B363_16DA7CD0FEDE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Shapelib/Shapefil.h>
#include "ArcViewDataSource.h"

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
	HRESULT CreateLayer (INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, CArcViewLayer **ppLayer)
	{
		return m_DataSource.OpenLayer(lIdent, pcName, rgType, 
			CArcViewDataSource::OPENMODE_Create, ppLayer);
	}
//	HRESULT OpenLayer (INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, CArcViewLayer **ppLayer)
//	{
//		return m_DataSource.OpenLayer(lIdent, pcName, rgType, 
//			CArcViewDataSource::OPENMODE_Append, ppLayer);
//	}
	HRESULT GetLayer (INT_PTR lIdent, OBJECTTYPE rgType, CArcViewLayer **ppLayer = NULL)
	{
		return m_DataSource.GetLayer(lIdent, rgType, ppLayer);
	}
	HRESULT GetLayer (LPCSTR pcName, OBJECTTYPE rgType, CArcViewLayer **ppLayer = NULL)
	{
		return m_DataSource.GetLayer(pcName, rgType, ppLayer);
	}
	HPROJECT GetActDataSource() { return m_hPr; }
	
protected:
	CArcViewDataSource m_DataSource;
	HPROJECT m_hPr;
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
OBJECTTYPE ObjType2OBJECTTYPE (long lObjType, bool fTreatTextAsPoint = false);

#endif // !defined(_EXPORTHELPER_H__A6C85B60_836B_4D29_B363_16DA7CD0FEDE__INCLUDED_)
