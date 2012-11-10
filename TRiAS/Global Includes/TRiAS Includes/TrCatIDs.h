// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.10.2000 20:15:06 
//
// @doc
// @module TrCatIDs.h | TRiAS Component categories

///////////////////////////////////////////////////////////////////////////////
// Eine normale TRiAS-Erweiterung; unterstützte Interface's:
//		ITriasXtension
//		ITriasXtension2
//		IObjectProps (optional)
// 079639C0-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASExtension, 0x079639C0L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-Importerweiterung; unterstützte Interface's:
//		alle Interface's von CATID_TRiASExtension
//		IImportGeoData
// 079639C1-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASImportModule, 0x079639C1L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-Exporterweiterung
//		noch nicht näher definiert
// 079639C2-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASExportModule, 0x079639C2L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Ein TRiAS-Koordinatensystem
//		noch nicht näher definiert
// 079639C3-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASCoordsystem, 0x079639C3L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-GeoKomponente
// 079639C4-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASGeoComponent, 0x079639C4L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Ein Objekt, welches andere Objekte als Erweiterung registriert
//		IRegisterDTRiASExtension
// 079639C5-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASSelfRegister, 0x079639C5L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-GeoKomponente
// 079639C7-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CATID_TRiASGeoComponentContainer, 0x079639C7L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-Objekteigenschaft (schreibgeschützt)
// {CE5D4A01-C1A2-4F3F-BE80-F2B9E2F9912F}
DEFINE_GUID(CATID_TRiASObjectProperty, 0xCE5D4A01, 0xC1A2, 0x4F3F, 0xBE, 0x80, 0xF2, 0xB9, 0xE2, 0xF9, 0x91, 0x2F);

///////////////////////////////////////////////////////////////////////////////
// Eine TRiAS-Objekteigenschaft (beschreibbar)
// {F74B444E-D766-470A-989F-BB3F9C6BFFD9}
DEFINE_GUID(CATID_TRiASObjectPropertyRO, 0xF74B444E, 0xD766, 0x470A, 0x98, 0x9F, 0xBB, 0x3F, 0x9C, 0x6B, 0xFF, 0xD9);

