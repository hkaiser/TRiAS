// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 11:40:10 
//
// @doc
// @module Usage.cpp | Definition of the <c CUsage> class

#include "stdafx.h"

#include "resource.h"

#include <Com/VariantHelpers.h>

#include "CvrtCoords_i.h"
#include "CvrtCoordsApp.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSTransformService);
DefineSmartInterface(EnumCoordSystemNames);
DefineSmartInterface(EnumVARIANT);

///////////////////////////////////////////////////////////////////////////////
// StartupLogo ausgeben
string CCvrtCoordsApp::LoadStringRes (UINT uiID)
{
TCHAR cbBuffer[_MAX_PATH];
string str;

	if (!::LoadString (_Module.GetResourceInstance(), uiID, cbBuffer, sizeof(cbBuffer)))
		throw false;

	str = cbBuffer;
	return str;
}

bool CCvrtCoordsApp::PrintStartupLogo (void)
{
	try {
	string strLogo = LoadStringRes (IDS_STARTUP);		// throws bool
	string strVersion = LoadStringRes (IDS_VERSION);
	string strCopyright = LoadStringRes (IDS_COPYRIGHT);
	char cbBuffer[_MAX_PATH];

		sprintf (cbBuffer, strLogo.c_str(), strVersion.c_str(), strCopyright.c_str());
		fprintf (stdout, cbBuffer);
	} 
	catch (bool fResult) {
		return fResult;
	}
	return true;
}

bool CCvrtCoordsApp::PrintModuleVersion()
{
CComBSTR bstrVersion;

	if (SUCCEEDED(m_Transform->get_Version(&bstrVersion))) {
	string strFormat (LoadStringRes(IDS_FORMAT));

		USES_CONVERSION;
		fprintf (stdout, "%s%s\n", strFormat.c_str(), OLE2A(bstrVersion));
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Help ausgeben
const TCHAR *cbUsage[] =
{
	_T("Kommandozeile: CvrtCoords [Optionen] Eingabedatei Ausgabedatei"),
	_T("Verwendbare Optionen:"),
	_T("\t-i Dateiname\tEingabe-Koordinatensystem (Standard: Bessel GK 12/3)"),
	_T("\t-o Dateiname\tAusgabe-Koordinatensystem (Standard: Bessel GK 12/3)"),
	_T("\t-l\t\tGibt eine Liste der installierten Koordinatensysteme aus"),
	_T("\t-t ProgId\tZu verwendendes Dateiformat (Standard: BNA)"),
	_T("\t-h\t\tGibt diesen Hilfetext aus"),
	_T("\t-n\t\tKein Programmlogo ausgeben"),
	_T("\t-v\t\tGibt nur das Programmlogo aus"),
	NULL,
};

int CCvrtCoordsApp::PrintUsage (void)
{
const TCHAR **pT = cbUsage;

	while (NULL != *pT) {
		fprintf (stderr, "%s\n", *pT);
		pT++;
	}
	return 2;
}

int CCvrtCoordsApp::PrintCoordSystems()
{
	fprintf (stderr, _T("%sListe der installierten Koordinatensysteme:\n\n"), 
		m_fNoLogo ? "" : "\n");
	COM_TRY {
	WTRiASCSTransformService CsService (CLSID_TRiASCSTransformService);
	WEnumCoordSystemNames EnumNames;
	WEnumVARIANT Enum;
	CComVariant vName;

		THROW_FAILED_HRESULT(CsService->EnumCoordSystemNames(EnumNames.ppi()));
		THROW_FAILED_HRESULT(EnumNames->_NewEnum(Enum.ppu()));

		for (Enum->Reset(); S_OK == Enum->Next(1, CLEARED(vName), NULL); /**/)
		{
			THROW_FAILED_HRESULT(vName.ChangeType(VT_BSTR));

		WTRiASCS CS (CLSID_TRIASCS);
		
			if (FAILED(CS->LoadFromFile(V_BSTR(&vName))))
				continue;
	
		CComBSTR bstrDesc;
		char cbBuffer[_MAX_PATH];

			THROW_FAILED_HRESULT(CS->get_Description(&bstrDesc));
			wsprintf (cbBuffer, "\t%ls :\t%ls\n", V_BSTR(&vName), bstrDesc);
		
			CharToOem(cbBuffer, cbBuffer);
			fprintf (stderr, cbBuffer);
		}

	} COM_CATCH;
	return 1;
}
