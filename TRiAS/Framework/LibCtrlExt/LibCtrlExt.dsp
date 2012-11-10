# Microsoft Developer Studio Project File - Name="LibCtrlExt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibCtrlExt - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibCtrlExt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibCtrlExt.mak" CFG="LibCtrlExt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibCtrlExt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibCtrlExt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibCtrlExt - Win32 Release Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/LibCtrlExt", JWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibCtrlExt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\_Release
TargetName=LibCtrlExt
InputPath=.\_Release\LibCtrlExt.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Z7 /Od /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"_Debug/LibCtrlExtD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"_Debug\LibCtrlExtD.lib"
# Begin Custom Build
OutDir=.\_Debug
TargetName=LibCtrlExtD
InputPath=.\_Debug\LibCtrlExtD.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Release Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Debug"
# PROP BASE Intermediate_Dir "Release Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_RDebug"
# PROP Intermediate_Dir "_RDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /O2 /D "_RDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\LibCtrlExt.lib"
# ADD LIB32 /nologo /out:"_RDebug\LibCtrlExtR.lib"
# Begin Custom Build
OutDir=.\_RDebug
TargetName=LibCtrlExtR
InputPath=.\_RDebug\LibCtrlExtR.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ENDIF 

# Begin Target

# Name "LibCtrlExt - Win32 Release"
# Name "LibCtrlExt - Win32 Debug"
# Name "LibCtrlExt - Win32 Release Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\CtrlExt.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlExtInl.cpp
# End Source File
# End Group
# Begin Group "Include Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lmfcx\LafxCtrl.h

!IF  "$(CFG)" == "LibCtrlExt - Win32 Release"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.h
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Debug"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.h
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Release Debug"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.h
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lmfcx\LafxCtrl.inl

!IF  "$(CFG)" == "LibCtrlExt - Win32 Release"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.inl
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Debug"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.inl
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCtrlExt - Win32 Release Debug"

# Begin Custom Build
InputPath=.\lmfcx\LafxCtrl.inl
InputName=LafxCtrl

"$(TRIASINCLUDE)\lmfcx\$(InputName).inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\lmfcx

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
