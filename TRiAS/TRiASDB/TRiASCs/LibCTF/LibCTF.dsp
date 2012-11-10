# Microsoft Developer Studio Project File - Name="LibCTF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibCTF - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibCTF.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibCTF.mak" CFG="LibCTF - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibCTF - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibCTF - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibCTF - Win32 Release Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/LibCTF", OFBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe

!IF  "$(CFG)" == "LibCTF - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\_Release
TargetName=LibCTF
InputPath=.\_Release\LibCTF.lib
SOURCE=$(InputPath)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"_Debug/LibCTFD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"_Debug\LibCTFD.lib"
# Begin Custom Build
OutDir=.\_Debug
TargetName=LibCTFD
InputPath=.\_Debug\LibCTFD.lib
SOURCE=$(InputPath)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Release Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Debug"
# PROP BASE Intermediate_Dir "Release Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_RDebug"
# PROP Intermediate_Dir "_RDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /O2 /D "_RDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"_RDebug\LibCTFR.lib"
# Begin Custom Build
OutDir=.\_RDebug
TargetName=LibCTFR
InputPath=.\_RDebug\LibCTFR.lib
SOURCE=$(InputPath)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ENDIF 

# Begin Target

# Name "LibCTF - Win32 Release"
# Name "LibCTF - Win32 Debug"
# Name "LibCTF - Win32 Release Debug"
# Begin Group "Common Headers"

# PROP Default_Filter "*.h;*.hpp"
# Begin Source File

SOURCE=.\LibCTF\DS_ThroughECEF.h

!IF  "$(CFG)" == "LibCTF - Win32 Release"

# Begin Custom Build
InputPath=.\LibCTF\DS_ThroughECEF.h
InputName=DS_ThroughECEF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Debug"

# Begin Custom Build
InputPath=.\LibCTF\DS_ThroughECEF.h
InputName=DS_ThroughECEF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Release Debug"

# Begin Custom Build
InputPath=.\LibCTF\DS_ThroughECEF.h
InputName=DS_ThroughECEF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LibCTF\LibCTF.h

!IF  "$(CFG)" == "LibCTF - Win32 Release"

# Begin Custom Build
InputPath=.\LibCTF\LibCTF.h
InputName=LibCTF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Debug"

# Begin Custom Build
InputPath=.\LibCTF\LibCTF.h
InputName=LibCTF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Release Debug"

# Begin Custom Build
InputPath=.\LibCTF\LibCTF.h
InputName=LibCTF

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_GaussKrueger.h

!IF  "$(CFG)" == "LibCTF - Win32 Release"

# Begin Custom Build
InputPath=.\LibCTF\PCS_GaussKrueger.h
InputName=PCS_GaussKrueger

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Debug"

# Begin Custom Build
InputPath=.\LibCTF\PCS_GaussKrueger.h
InputName=PCS_GaussKrueger

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Release Debug"

# Begin Custom Build
InputPath=.\LibCTF\PCS_GaussKrueger.h
InputName=PCS_GaussKrueger

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_Generic.h

!IF  "$(CFG)" == "LibCTF - Win32 Release"

# Begin Custom Build
InputPath=.\LibCTF\PCS_Generic.h
InputName=PCS_Generic

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Debug"

# Begin Custom Build
InputPath=.\LibCTF\PCS_Generic.h
InputName=PCS_Generic

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ELSEIF  "$(CFG)" == "LibCTF - Win32 Release Debug"

# Begin Custom Build
InputPath=.\LibCTF\PCS_Generic.h
InputName=PCS_Generic

"$(TRIASINCLUDE)\LIBCTF\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\LIBCTF

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\DS_ThroughECEF.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTFImpl.h
# End Source File
# Begin Source File

SOURCE=.\PCS_GaussKrueger.cpp
# End Source File
# Begin Source File

SOURCE=.\PCS_Generic.cpp
# End Source File
# End Target
# End Project
