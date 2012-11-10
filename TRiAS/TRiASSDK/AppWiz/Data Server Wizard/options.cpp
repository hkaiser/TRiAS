// options.cpp : implementation of COptions class
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "TRiASDBDS.h"
#include "TRiASDBDSaw.h"
#include "options.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// On construction, set the default values of user-selectable options
COptions::COptions()
{
	m_AccessMode = ACCESSMODE_READONLY;
	m_AccessType = ACCESSTYPE_FILE;
	m_FileExt = _T("rit");
	m_fEmitSampleCode = TRUE;
}

// Defines step-related template macros, which depend on which
//  options were selected.
CString MakeProgID (LPCTSTR pcRoot, LPCTSTR pcObj, int iVersion = 1)
{
CString str (pcRoot);

	str.Format (_T("TRiASDB.%s%s.%d"), pcRoot, pcObj, iVersion);
	return str;
}

void COptions::DefineDlgMacros()
{
// sonstige Keys
	m_FileExt.MakeLower();
	DefineStringMacro(_T("def_extension"), m_FileExt);
	m_FileExt.MakeUpper();
	DefineStringMacro(_T("DEF_EXTENSION"), m_FileExt);

	if (m_Name.GetLength() == 0)
		TRiASDBDSaw.m_Dictionary.Lookup(_T("root"), m_Name);
	_toupper(m_Name[0]);
	DefineStringMacro (_T("dataserver_name"), m_Name);

	DefineBoolMacro(_T("NAME_IS_FILE"), ACCESSTYPE_FILE == m_AccessType);
	DefineBoolMacro(_T("NAME_IS_DIR"), ACCESSTYPE_DIRECTORY == m_AccessType);

	DefineBoolMacro(_T("READ_WRITE"), ACCESSMODE_READWRITE == m_AccessMode);
	DefineBoolMacro(_T("EMIT_SAMPLE_CODE"), m_fEmitSampleCode);

// derzeit feststehende Optionen
	DefineBoolMacro(_T("EMIT_OBJECTCOUNT_DEBUG"), TRUE);

// Guids erzeugen bzw. wiederfinden
CString strSafeRoot;

	TRiASDBDSaw.m_Dictionary.Lookup(_T("Safe_root"), strSafeRoot);
	TRiASDBDSaw.FindOrCreateLibID (_T("GUID_LIBID"), MakeProgID(strSafeRoot, _T("Database")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_DBENGINE_OBJECT"), MakeProgID(strSafeRoot, _T("DBEngine")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_DATABASE_OBJECT"), MakeProgID(strSafeRoot, _T("DatabaseObject")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_OBJECTSCOLLECTION_OBJECT"), MakeProgID(strSafeRoot, _T("ObjectsCollection")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_OBJECTS_OBJECT"), MakeProgID(strSafeRoot, _T("Objects")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_OBJECT_OBJECT"), MakeProgID(strSafeRoot, _T("Object")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_FEATURES_OBJECT"), MakeProgID(strSafeRoot, _T("Features")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_FEATURE_OBJECT"), MakeProgID(strSafeRoot, _T("Feature")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_GEOFEATURES_OBJECT"), MakeProgID(strSafeRoot, _T("GeoFeatures")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_GEOFEATURE_OBJECT"), MakeProgID(strSafeRoot, _T("GeoFeature")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_OBJECTCURSORPROPERTY_OBJECT"), MakeProgID(strSafeRoot, _T("ObjectCursorProperty")));
	TRiASDBDSaw.FindOrCreateGuid (_T("GUID_CURSORPROPERTY_OBJECT"), MakeProgID(strSafeRoot, _T("CursorProperty")));
}

// Create one global instance of this class anyone can see.
COptions g_Options;
