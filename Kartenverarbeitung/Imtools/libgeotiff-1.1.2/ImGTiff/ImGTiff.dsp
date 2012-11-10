# Microsoft Developer Studio Project File - Name="ImGTiff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImGTiff - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImGTiff.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImGTiff.mak" CFG="ImGTiff - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImGTiff - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImGTiff - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImGTiff - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMGTIFF_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\libxtiff" /I "..\..\tiff-v3.5.5\libtiff" /I ".." /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMGTIFF_EXPORTS" /D "unix" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386
# Begin Custom Build
TargetPath=.\Release\ImGTiff.dll
TargetName=ImGTiff
InputPath=.\Release\ImGTiff.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT)

# End Custom Build

!ELSEIF  "$(CFG)" == "ImGTiff - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMGTIFF_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\libxtiff" /I "..\..\tiff-v3.5.5\libtiff" /I ".." /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMGTIFF_EXPORTS" /D "unix" /Fp"Debug/ImGTiffd.pch" /YX /Fd"Debug/ImGTiffd.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/ImGTiffd.dll" /pdbtype:sept
# Begin Custom Build
TargetPath=.\Debug\ImGTiffd.dll
TargetName=ImGTiffd
InputPath=.\Debug\ImGTiffd.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT_DEBUG)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT_DEBUG)

# End Custom Build

!ENDIF 

# Begin Target

# Name "ImGTiff - Win32 Release"
# Name "ImGTiff - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\cpl_csv.c
# End Source File
# Begin Source File

SOURCE=..\cpl_serv.c
# End Source File
# Begin Source File

SOURCE=..\geo_extra.c
# End Source File
# Begin Source File

SOURCE=..\geo_free.c
# End Source File
# Begin Source File

SOURCE=..\geo_get.c
# End Source File
# Begin Source File

SOURCE=..\geo_names.c
# End Source File
# Begin Source File

SOURCE=..\geo_new.c
# End Source File
# Begin Source File

SOURCE=..\geo_normalize.c
# End Source File
# Begin Source File

SOURCE=..\geo_print.c
# End Source File
# Begin Source File

SOURCE=..\geo_set.c
# End Source File
# Begin Source File

SOURCE=..\geo_tiffp.c
# End Source File
# Begin Source File

SOURCE=..\geo_trans.c
# End Source File
# Begin Source File

SOURCE=..\geo_write.c
# End Source File
# Begin Source File

SOURCE=..\geotiff_proj4.c
# End Source File
# Begin Source File

SOURCE=.\ImGTiff.cpp
# End Source File
# Begin Source File

SOURCE=..\WINNT\libgeog.def
# End Source File
# Begin Source File

SOURCE=..\libxtiff\xtiff.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\epsg_datum.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_ellipse.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_gcs.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_pcs.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_pm.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_proj.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_units.inc
# End Source File
# Begin Source File

SOURCE=..\epsg_vertcs.inc
# End Source File
# Begin Source File

SOURCE=..\geo_config.h
# End Source File
# Begin Source File

SOURCE=..\geo_ctrans.inc
# End Source File
# Begin Source File

SOURCE=..\geokeys.inc
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
