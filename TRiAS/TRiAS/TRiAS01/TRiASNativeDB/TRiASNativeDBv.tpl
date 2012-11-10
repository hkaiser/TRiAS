// VersionsInfoStruktur fuer TRiASNativeDB.DLL --------------------------------------
// File: TRiASNativeDB.RCV

#ifndef VS_FF_DEBUG
// ----------------------------------------------------------------------------
// In VER.H sind die notwendigen Konstantendefinitionen enthalten -------------
#include <ver.h>
#endif

// ----------------------------------------------------------------------------
// Die folgenden Zeilen sollten vom Produktverantwortlichen für jedes Build 
// aktualisiert werden 

#define VER_FILEVERSION_STR     "@A.@B.@C\0"
#define VER_FILEVERSION          @A,@B,0,@C

#define VER_PRODUCTVERSION_STR  "@G.@H\0"
#define VER_PRODUCTVERSION      @G,@H,0,0

// ----------------------------------------------------------------------------
// Produkt-Spezifische Informationen ------------------------------------------

// Default ist NODEBUG
#ifndef DEBUG
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

// Default ist PrivateBuild
#ifndef OFFICIAL
#define VER_PRIVATEBUILD            VS_FF_PRIVATEBUILD
#else
#define VER_PRIVATEBUILD            0
#endif

// Default ist PreRelease
#ifndef FINAL
#define VER_PRERELEASE              VS_FF_PRERELEASE
#else
#define VER_PRERELEASE              0
#endif

#define VER_FILEFLAGSMASK    VS_FFI_FILEFLAGSMASK
#define VER_FILEFLAGS        (VER_PRIVATEBUILD|VER_PRERELEASE|VER_DEBUG|VS_FF_SPECIALBUILD)

#define VER_FILEOS           VOS_NT_WINDOWS32

#define VER_COMPANYNAME_STR  	"@I\0"
#define VER_LEGALCOPYRIGHT_STR	"Copyright © @I 1991 - 2005, #@D\0"
#define VER_PRODUCTNAME_STR  	\
	"TRiAS® - Territoriales Raumbezogenes Informations- und Abfragesystem\0"
#define VER_LEGALTRADEMARKS_STR	\
	"TRiAS® ist ein eingetragenes Warenzeichen.\0"

// ----------------------------------------------------------------------------
// Datei-Spezifische Informationen --------------------------------------------

#define VER_FILETYPE                VFT_DLL

#define VER_FILESUBTYPE             VFT2_UNKNOWN
#define VER_FILEDESCRIPTION_STR		\
	"Territoriales Raumbezogenes Informations- und Abfragesystem, "	\
	"DB-Schnittstelle für TRiAS eigene Projekte.\0"
#define VER_INTERNALNAME_STR		"TRiASNativeDB\0"
#define VER_ORIGINALFILENAME_STR	"TRiASNativeDB.DLL\0"
#define VER_SPECIALBUILD_STR		"PersonalisierungsInfo: " \
	"@E " "@F " "\0"

// Die eigentliche VersionsStruktur -------------------------------------------
#ifdef RC_INVOKED

VS_VERSION_INFO	VERSIONINFO
FILEVERSION	VER_FILEVERSION
PRODUCTVERSION  VER_PRODUCTVERSION
FILEFLAGSMASK   VER_FILEFLAGSMASK
FILEFLAGS       VER_FILEFLAGS
FILEOS          VER_FILEOS
FILETYPE        VER_FILETYPE
FILESUBTYPE     VER_FILESUBTYPE
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040704E4"	// Deutsch und multilinguale CodePage
	BEGIN
		VALUE "CompanyName",		VER_COMPANYNAME_STR
		VALUE "FileDescription",	VER_FILEDESCRIPTION_STR
		VALUE "FileVersion",		VER_FILEVERSION_STR
		VALUE "InternalName",    	VER_INTERNALNAME_STR
		VALUE "LegalCopyright",		VER_LEGALCOPYRIGHT_STR
		VALUE "LegalTrademarks",	VER_LEGALTRADEMARKS_STR
		VALUE "OriginalFileName",	VER_ORIGINALFILENAME_STR
 		VALUE "ProductName",		VER_PRODUCTNAME_STR
		VALUE "ProductVersion",		VER_PRODUCTVERSION_STR
	// Hier sollten zusätzliche Informationen für lokale Versionen 
	// enthalten sein.
		VALUE "SpecialBuild",5		VER_SPECIALBUILD_STR
		VALUE "TRiASSelfRegister\0", "\0"
		VALUE "OleSelfRegister\0", "\0"
	END
    END

    BLOCK "VarFileInfo"
    BEGIN
	// Die folgende Informationen werden lediglich für lokalisierte 
	// Produktversionen verändert. Jeweils ein WORD, WORD - Paar 
	// definiert eine konkrete Sprache bzw. unterstützte CodeSeite.

        VALUE "Translation", 0x407, 1252
    END
END

#endif


