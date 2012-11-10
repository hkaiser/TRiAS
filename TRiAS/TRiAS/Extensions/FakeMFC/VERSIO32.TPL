// VersionsInfo der Beispiel-Erweiterung --------------------------------------
// File: VERSION.H

#define FAKEMFC_MAJORVERSION	@A
#define FAKEMFC_MINORVERSION	@B

#define COMPANY_NAME	"@C"
#if defined(_DEBUG)
#define TRiAS_VERSION	"@D.@E.@F (Debug), #@H"
#else
#define TRiAS_VERSION	"@D.@E.@F (@G), #@H"
#endif // defined(_DEBUG)