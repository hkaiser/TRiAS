# Microsoft Developer Studio Project File - Name="ImTiff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImTiff - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImTiff.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImTiff.mak" CFG="ImTiff - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImTiff - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImTiff - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Imtools/ImTiff", MLBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImTiff - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTIFF_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "..\..\..\jpeg-6b" /I "..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTIFF_EXPORTS" /D "STRICT" /D "unix" /D "JPEG_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 binmode.obj kernel32.lib user32.lib gdi32.lib /nologo /dll /debug /machine:I386
# Begin Custom Build
TargetPath=.\Release\ImTiff.dll
TargetName=ImTiff
InputPath=.\Release\ImTiff.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT)

# End Custom Build

!ELSEIF  "$(CFG)" == "ImTiff - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTIFF_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\jpeg-6b" /I "..\..\..\include" /D "_DEBUG" /D "STRICT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTIFF_EXPORTS" /D "unix" /D "JPEG_SUPPORT" /YX /Fd"Debug/ImTiffd.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 binmode.obj kernel32.lib user32.lib gdi32.lib /nologo /dll /debug /machine:I386 /out:"Debug/ImTiffd.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetPath=.\Debug\ImTiffd.dll
TargetName=ImTiffd
InputPath=.\Debug\ImTiffd.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT_DEBUG)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT_DEBUG)

# End Custom Build

!ENDIF 

# Begin Target

# Name "ImTiff - Win32 Release"
# Name "ImTiff - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ImTiff.cpp

!IF  "$(CFG)" == "ImTiff - Win32 Release"

!ELSEIF  "$(CFG)" == "ImTiff - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\libtiff.def
# End Source File
# Begin Source File

SOURCE=..\tif_aux.c
# End Source File
# Begin Source File

SOURCE=..\tif_close.c
# End Source File
# Begin Source File

SOURCE=..\tif_codec.c
# End Source File
# Begin Source File

SOURCE=..\tif_compress.c
# End Source File
# Begin Source File

SOURCE=..\tif_dir.c
# End Source File
# Begin Source File

SOURCE=..\tif_dirinfo.c
# End Source File
# Begin Source File

SOURCE=..\tif_dirread.c
# End Source File
# Begin Source File

SOURCE=..\tif_dirwrite.c
# End Source File
# Begin Source File

SOURCE=..\tif_dumpmode.c
# End Source File
# Begin Source File

SOURCE=..\tif_error.c
# End Source File
# Begin Source File

SOURCE=..\tif_fax3.c
# End Source File
# Begin Source File

SOURCE=..\tif_fax3sm.c
# End Source File
# Begin Source File

SOURCE=..\tif_flush.c
# End Source File
# Begin Source File

SOURCE=..\tif_getimage.c
# End Source File
# Begin Source File

SOURCE=..\tif_jpeg.c
# End Source File
# Begin Source File

SOURCE=..\tif_lzw.c
# End Source File
# Begin Source File

SOURCE=..\tif_next.c
# End Source File
# Begin Source File

SOURCE=..\tif_open.c
# End Source File
# Begin Source File

SOURCE=..\tif_packbits.c
# End Source File
# Begin Source File

SOURCE=..\tif_predict.c
# End Source File
# Begin Source File

SOURCE=..\tif_print.c
# End Source File
# Begin Source File

SOURCE=..\tif_read.c
# End Source File
# Begin Source File

SOURCE=..\tif_strip.c
# End Source File
# Begin Source File

SOURCE=..\tif_swab.c
# End Source File
# Begin Source File

SOURCE=..\tif_thunder.c
# End Source File
# Begin Source File

SOURCE=..\tif_tile.c
# End Source File
# Begin Source File

SOURCE=..\tif_unix.c
# End Source File
# Begin Source File

SOURCE=..\tif_version.c
# End Source File
# Begin Source File

SOURCE=..\tif_warning.c
# End Source File
# Begin Source File

SOURCE=..\tif_win32.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\tif_write.c
# End Source File
# Begin Source File

SOURCE=..\tif_zip.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\port.h
# End Source File
# Begin Source File

SOURCE=..\t4.h
# End Source File
# Begin Source File

SOURCE=..\tif_dir.h
# End Source File
# Begin Source File

SOURCE=..\tif_fax3.h
# End Source File
# Begin Source File

SOURCE=..\tif_predict.h
# End Source File
# Begin Source File

SOURCE=..\tiff.h
# End Source File
# Begin Source File

SOURCE=..\tiffcomp.h
# End Source File
# Begin Source File

SOURCE=..\tiffconf.h
# End Source File
# Begin Source File

SOURCE=..\tiffio.h
# End Source File
# Begin Source File

SOURCE=..\tiffiop.h
# End Source File
# Begin Source File

SOURCE=..\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
