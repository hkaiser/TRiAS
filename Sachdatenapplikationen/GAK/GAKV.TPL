/////////////////////////////////////////////////////////////////////////////
//
// Version
//

#include "ver.h"

VS_VERSION_INFO VERSIONINFO
 FILEVERSION 1,0,0,1
 PRODUCTVERSION @A,@B,0,@C
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS 0x1L
#else
 FILEFLAGS 0x0L
#endif
 FILEOS 0x40004L
 FILETYPE 0x1L
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040704b0"
        BEGIN
            VALUE "Comments", "Version f\374r das Land Brandenburg\0"
            VALUE "CompanyName", "uve FEZ Potsdam\0"
            VALUE "FileDescription", "GAK\0"
            VALUE "FileVersion", "1, 0, 0, 1\0"
            VALUE "InternalName", "GAK\0"
            VALUE "LegalCopyright", "Copyright © 1996-1998\0"
            VALUE "OriginalFilename", "gak.exe\0"
            VALUE "ProductName", "GAK - Gewerbeabfallkataster (32-Bit-Version).\0"
            VALUE "ProductVersion", "@A, @B, @C, 1\0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x407, 1200
    END
END

