// TRiAS Component categories
// File: TRCATIDS.H

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
