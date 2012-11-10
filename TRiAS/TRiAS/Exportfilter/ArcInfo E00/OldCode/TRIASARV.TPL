// VersionsInfoStruktur fuer CADDYASC.DLL --------------------------------------
// File: TRIASARV.RCV

#ifndef VS_FF_DEBUG
// ----------------------------------------------------------------------------
// In VER.H sind die notwendigen Konstantendefinitionen enthalten -------------
#include <ver.h>
#endif

// ----------------------------------------------------------------------------
// Die folgenden Zeilen sollten vom Produktverantwortlichen f¸r jedes Build 
// aktualisiert werden 

#define VER_PRODUCTVERSION_STR     "@A.@B.@C\0"
#define VER_PRODUCTVERSION          @A,@B,@C,0

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

#define VER_FILEOS           VOS_DOS_WINDOWS16

#define VER_COMPANYNAME_STR	"uve GmbH Fernerkundungszentrum Potsdam\0"
#define VER_LEGALCOPYRIGHT_STR	"Copyright © uve GmbH Fernerkundungszentrum Potsdam 1991-1998 - #@D\0"
#define VER_PRODUCTNAME_STR  	\
	"TRIASÆ - Territoriales Raumbezogenes Informations- und Abfragesystem\0"
#define VER_LEGALTRADEMARKS_STR	\
	"TRIASÆ ist ein eingetragenes Warenzeichen der uve GmbH Fernerkundungszentrum Potsdam.\0"

// ----------------------------------------------------------------------------
// Datei-Spezifische Informationen --------------------------------------------

#define VER_FILETYPE                VFT_DLL

#define VER_FILESUBTYPE             VFT2_UNKNOWN
#define VER_FILEVERSION             VER_PRODUCTVERSION

#define VER_FILEVERSION_STR		VER_PRODUCTVERSION_STR
#define VER_FILEDESCRIPTION_STR		\
	"Territoriales Raumbezogenes Informations- und Abfragesystem, "	\
	"CADdy-Filter fÅr ASDCII-Format der Version 7.0.\0"
#define VER_INTERNALNAME_STR		"ACADDXF\0"
#define VER_ORIGINALFILENAME_STR	"ACADDXF.DLL\0"
#define VER_SPECIALBUILD_STR		"PersonalisierungsInfo: " \
	"@E " "@F" 

// Die eigentliche VersionsStruktur -------------------------------------------
#ifdef RC_INVOKED

VS_VERSION_INFO         VERSIONINFO
FILEVERSION     VER_FILEVERSION
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
	// Hier sollten zus‰tzliche Informationen f¸r lokale Versionen 
	// enthalten sein.
		VALUE "SpecialBuild",		VER_SPECIALBUILD_STR
	END
    END

    BLOCK "VarFileInfo"
    BEGIN
	// Die folgende Informationen werden lediglich f¸r lokalisierte 
	// Produktversionen ver‰ndert. Jeweils ein WORD, WORD - Paar 
	// definiert eine konkrete Sprache bzw. unterst¸tzte CodeSeite.

        VALUE "Translation", 0x407, 1252
    END
END

#endif



