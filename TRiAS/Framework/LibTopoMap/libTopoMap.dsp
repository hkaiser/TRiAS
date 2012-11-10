# Microsoft Developer Studio Project File - Name="libTopoMap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libTopoMap - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libTopoMap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libTopoMap.mak" CFG="libTopoMap - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libTopoMap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libTopoMap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Bibliotheken/libTopoMap", HQDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libTopoMap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build - Copy Target
OutDir=.\_Release
TargetName=libTopoMap
InputPath=.\_Release\libTopoMap.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "libTopoMap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /ZI /Od /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"_Debug/libTopoMapD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"_Debug\libTopoMapD.lib"
# Begin Custom Build - Copy Target
OutDir=.\_Debug
TargetName=libTopoMapD
InputPath=.\_Debug\libTopoMapD.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ENDIF 

# Begin Target

# Name "libTopoMap - Win32 Release"
# Name "libTopoMap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AscFile.cpp
# End Source File
# Begin Source File

SOURCE=.\AscIo.cpp
# End Source File
# Begin Source File

SOURCE=.\AscParse.cpp
# End Source File
# Begin Source File

SOURCE=.\GMapTree.cpp
# End Source File
# Begin Source File

SOURCE=.\LgeoHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PARSE_AS.CPP
# End Source File
# Begin Source File

SOURCE=.\PARSE_AV.CPP
# End Source File
# Begin Source File

SOURCE=.\PARSE_N.CPP
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\libTopoMap\AscFile.h
# End Source File
# Begin Source File

SOURCE=.\libTopoMap\AscIo.h
# End Source File
# Begin Source File

SOURCE=.\libTopoMap\LibTopoMap.h
# End Source File
# Begin Source File

SOURCE=.\libTopoMap\LibTopoMapRes.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\libTopoMap\LibTopoMap.rc
# End Source File
# End Group
# Begin Group "YACC-Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PARSE_AS.Y

!IF  "$(CFG)" == "libTopoMap - Win32 Release"

# Begin Custom Build
InputPath=.\PARSE_AS.Y
InputName=PARSE_AS

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ELSEIF  "$(CFG)" == "libTopoMap - Win32 Debug"

# Begin Custom Build
InputPath=.\PARSE_AS.Y
InputName=PARSE_AS

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PARSE_AV.Y

!IF  "$(CFG)" == "libTopoMap - Win32 Release"

# Begin Custom Build
InputPath=.\PARSE_AV.Y
InputName=PARSE_AV

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ELSEIF  "$(CFG)" == "libTopoMap - Win32 Debug"

# Begin Custom Build
InputPath=.\PARSE_AV.Y
InputName=PARSE_AV

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PARSE_N.Y

!IF  "$(CFG)" == "libTopoMap - Win32 Release"

# Begin Custom Build
InputPath=.\PARSE_N.Y
InputName=PARSE_N

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ELSEIF  "$(CFG)" == "libTopoMap - Win32 Debug"

# Begin Custom Build
InputPath=.\PARSE_N.Y
InputName=PARSE_N

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\GeoTiffTags.txt
# End Source File
# End Target
# End Project
