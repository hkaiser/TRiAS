// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 11:40:34 
//
// @doc
// @module CvrtCoordsApp.h | Declaration of the <c CCvrtCoordsApp> class

#if !defined(_CvrtCoordsAPP_H_A881622B_6D0A_4913_9E2A_9FDC4C8B6DE2_INCLUDED_)
#define _CvrtCoordsAPP_H_A881622B_6D0A_4913_9E2A_9FDC4C8B6DE2_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BnaCoordSystems.h"
#include "TransformCallback.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TransformLineOfText);

/////////////////////////////////////////////////////////////////////////////
// CCvrtCoordsApp class

class CCvrtCoordsApp 
{
public:
	CCvrtCoordsApp();
	~CCvrtCoordsApp();

// Attributes
public:

// Operations
public:

// Implementation
public:
	int doWork(LPCTSTR pcInFile, LPCSTR pcOutFile);			// do the main work
	int ConvertCoords(LPCSTR pcInFile, LPCSTR pcOutFile);

	int AnalyzeCmdLine (int iArgc, char *cbArgv[]);
	bool PrintStartupLogo (void);
	int PrintUsage (void);
	bool PrintModuleVersion();
	int PrintCoordSystems();

	bool GetNoLogo() { return m_fNoLogo; }
	int OptIndex() { return m_iOptIndex; }

// workhorses
	HRESULT TransformCoords (double *pdX, double *pdY);

protected:
	string LoadStringRes (UINT uiID);
	int GetNextOption (int argc, char *argv[], char *optstring);

private:
	bool m_fNoLogo;

	string m_strOutCoordFile;	// Ausgabe-Koordinatensystem
	string m_strInCoordFile;	// Eingabe-Koordinatensystem
	CCoordSystems m_CoordSys;

	string m_strFormatProgId;	// Transformations-Engine
	WTransformLineOfText m_Transform;
	CComObject<CTransformCallback> *m_pCallback;

// command line support
	char *m_pOptArg;
	int m_iOptIndex;
	int m_iOptError;
	int m_iInOpt;

	HINSTANCE m_hInstance;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_CvrtCoordsAPP_H_A881622B_6D0A_4913_9E2A_9FDC4C8B6DE2_INCLUDED_)
