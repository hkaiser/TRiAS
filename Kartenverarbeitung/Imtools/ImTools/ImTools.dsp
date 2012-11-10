# Microsoft Developer Studio Project File - Name="ImTools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImTools - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImTools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImTools.mak" CFG="ImTools - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImTools - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImTools - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImTools - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTOOLS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\libsdsc\Include" /I "..\Include" /I "..\Libim\Include" /I "..\Tools\Include" /I "..\Jpeg-6b" /I "..\Tiff-v3.5.5\libtiff" /I "..\libgeotiff-1.1.2" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /D "IMTOOLS_EXPORTS" /D "STRICT" /D "MSWIND" /D "__STDC__" /D "USE_TIFF_LIB" /D "USE_JPEG_LIB" /YX /FD /c
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
TargetPath=.\Release\ImTools.dll
TargetName=ImTools
InputPath=.\Release\ImTools.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT)

# End Custom Build

!ELSEIF  "$(CFG)" == "ImTools - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMTOOLS_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\libsdsc\Include" /I "..\Include" /I "..\Libim\Include" /I "..\Tools\Include" /I "..\Jpeg-6b" /I "..\Tiff-v3.5.5\libtiff" /I "..\libgeotiff-1.1.2" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "IMTOOLS_EXPORTS" /D "STRICT" /D "MSWIND" /D "__STDC__" /D "USE_TIFF_LIB" /D "USE_JPEG_LIB" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 binmode.obj kernel32.lib user32.lib gdi32.lib /nologo /dll /debug /machine:I386 /out:"Debug/ImToolsd.dll"
# Begin Custom Build
TargetPath=.\Debug\ImToolsd.dll
TargetName=ImToolsd
InputPath=.\Debug\ImToolsd.dll
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT_DEBUG)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(IMTOOLS_ROOT_DEBUG)

# End Custom Build

!ENDIF 

# Begin Target

# Name "ImTools - Win32 Release"
# Name "ImTools - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Libsdsc Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libsdsc\arg.c
# End Source File
# Begin Source File

SOURCE=..\libsdsc\bin.c
# End Source File
# Begin Source File

SOURCE=..\libsdsc\tag.c
# End Source File
# End Group
# Begin Group "Libimaux Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tools\imfeedback.c
# End Source File
# Begin Source File

SOURCE=..\tools\imregister.c
# End Source File
# Begin Source File

SOURCE=..\tools\imtools.c
# End Source File
# End Group
# Begin Group "ImTools Sources"

# PROP Default_Filter ""
# Begin Group "Core Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libim\im.c
# End Source File
# Begin Source File

SOURCE=..\libim\imclt.c
# End Source File
# Begin Source File

SOURCE=..\libim\imerrno.c
# End Source File
# Begin Source File

SOURCE=..\libim\imfile.c
# End Source File
# Begin Source File

SOURCE=..\libim\imfmt.c
# End Source File
# Begin Source File

SOURCE=..\libim\imgiflzw.c
# End Source File
# Begin Source File

SOURCE=..\libim\imlzw.c
# End Source File
# Begin Source File

SOURCE=..\libim\immiscschemes.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\libim\imschemes.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfb.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbadjust.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbchan.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbcomp.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbflip.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbhist.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfblight.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbresize.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbrotate.c
# End Source File
# Begin Source File

SOURCE=..\libim\imvfbto.c
# End Source File
# Begin Source File

SOURCE=..\libim\macpack.c
# End Source File
# End Group
# Begin Group "Format Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libim\imbmp.c
# End Source File
# Begin Source File

SOURCE=..\libim\imcur.c
# End Source File
# Begin Source File

SOURCE=..\libim\imeps.c
# End Source File
# Begin Source File

SOURCE=..\libim\imgif.c
# End Source File
# Begin Source File

SOURCE=..\libim\imhdfread.c
# End Source File
# Begin Source File

SOURCE=..\libim\imhdfwrite.c
# End Source File
# Begin Source File

SOURCE=..\libim\imico.c
# End Source File
# Begin Source File

SOURCE=..\libim\imicon.c
# End Source File
# Begin Source File

SOURCE=..\libim\imiff.c
# End Source File
# Begin Source File

SOURCE=..\libim\imjpeg.c
# End Source File
# Begin Source File

SOURCE=..\libim\immiff.c
# End Source File
# Begin Source File

SOURCE=..\libim\immpnt.c
# End Source File
# Begin Source File

SOURCE=..\libim\impbm.c
# End Source File
# Begin Source File

SOURCE=..\libim\impcx.c
# End Source File
# Begin Source File

SOURCE=..\libim\impic.c
# End Source File
# Begin Source File

SOURCE=..\libim\impict.c
# End Source File
# Begin Source File

SOURCE=..\libim\impix.c
# End Source File
# Begin Source File

SOURCE=..\libim\imps.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\libim\imras.c
# End Source File
# Begin Source File

SOURCE=..\libim\imrgb.c
# End Source File
# Begin Source File

SOURCE=..\libim\imrla.c
# End Source File
# Begin Source File

SOURCE=..\libim\imrle.c
# End Source File
# Begin Source File

SOURCE=..\libim\imsoftimage.c
# End Source File
# Begin Source File

SOURCE=..\libim\imsynu.c
# End Source File
# Begin Source File

SOURCE=..\libim\imtga.c
# End Source File
# Begin Source File

SOURCE=..\libim\imtiff.c
# End Source File
# Begin Source File

SOURCE=..\libim\imviff.c
# End Source File
# Begin Source File

SOURCE=..\libim\imx.c
# End Source File
# Begin Source File

SOURCE=..\libim\imxbm.c
# End Source File
# Begin Source File

SOURCE=..\libim\imxpm.c
# End Source File
# Begin Source File

SOURCE=..\libim\imxwd.c
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\imtools.def

!IF  "$(CFG)" == "ImTools - Win32 Release"

!ELSEIF  "$(CFG)" == "ImTools - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\imtoolsd.def

!IF  "$(CFG)" == "ImTools - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ImTools - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImToolsDLL.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Libsdsc Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libsdsc\include\arg.h
# End Source File
# Begin Source File

SOURCE=..\libsdsc\include\bin.h
# End Source File
# Begin Source File

SOURCE=..\libsdsc\include\sdsc.h
# End Source File
# Begin Source File

SOURCE=..\libsdsc\include\sdscconfig.h
# End Source File
# Begin Source File

SOURCE=..\libsdsc\include\sdsccopyright.h
# End Source File
# Begin Source File

SOURCE=..\libsdsc\include\tag.h
# End Source File
# End Group
# Begin Group "ImTools Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libim\include\im.h
# End Source File
# Begin Source File

SOURCE=..\libim\include\imhdfinternal.h
# End Source File
# Begin Source File

SOURCE=..\libim\include\iminternal.h
# End Source File
# Begin Source File

SOURCE=..\libim\include\impref.h
# End Source File
# Begin Source File

SOURCE=..\tools\include\imtools.h
# End Source File
# Begin Source File

SOURCE=..\Include\ImToolsApi.h
# End Source File
# Begin Source File

SOURCE=..\libim\include\imxpm.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Tools\Include\imVersion.h
# End Source File
# End Group
# End Target
# End Project
