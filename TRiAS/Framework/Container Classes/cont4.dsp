# Microsoft Developer Studio Project File - Name="cont32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cont32 - Win32 Container Debug TrueTime
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cont4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cont4.mak" CFG="cont32 - Win32 Container Debug TrueTime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cont32 - Win32 Container Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cont32 - Win32 Container Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cont32 - Win32 Container Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/Framework/Container Classes", CAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /Yu"contpre.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:3.0 /dll /debug /machine:I386 /out:".\Release\containr.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\containr.dll
TargetName=containr
InputPath=.\Release\containr.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR /Fp".\Debug\cont50d.pch" /Yu"contpre.hxx" /Fd".\Debug\cont50d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:".\Debug\cont50d.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:".\Debug\containd.dll" /implib:".\Debug\cont50d.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetPath=.\Debug\containd.dll
TargetName=containd
InputPath=.\Debug\containd.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\cont50d.pdb" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\cont50d.lib" $(TRIASLIB) \
	xcopy /F "$(OutDir)\cont50d.pdb" $(TRIASLIB) \
	

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\cont50d.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cont32___Win32_Container_Debug_TrueTime"
# PROP BASE Intermediate_Dir "cont32___Win32_Container_Debug_TrueTime"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "cont32___Win32_Container_Debug_TrueTime"
# PROP Intermediate_Dir "cont32___Win32_Container_Debug_TrueTime"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR /Fp".\Debug\cont50d.pch" /Yu"contpre.hxx" /Fd".\Debug\cont50d.pdb" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR /Fp"cont32___Win32_Container_Debug_TrueTime\cont50d.pch" /Yu"contpre.hxx" /Fd"cont32___Win32_Container_Debug_TrueTime\cont50d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:".\Debug\cont50d.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:".\Debug\containd.dll" /implib:".\Debug\cont50d.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:"cont32___Win32_Container_Debug_TrueTime\cont50d.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"cont32___Win32_Container_Debug_TrueTime\containd.dll" /implib:"cont32___Win32_Container_Debug_TrueTime\cont50d.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\cont32___Win32_Container_Debug_TrueTime
TargetPath=.\cont32___Win32_Container_Debug_TrueTime\containd.dll
TargetName=containd
InputPath=.\cont32___Win32_Container_Debug_TrueTime\containd.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\cont50d.pdb" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\cont50d.lib" $(TRIASLIB) \
	

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\cont50d.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "cont32 - Win32 Container Release"
# Name "cont32 - Win32 Container Debug"
# Name "cont32 - Win32 Container Debug TrueTime"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ARRAY.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AssertDlg.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\BINNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cont32.rc
# End Source File
# Begin Source File

SOURCE=.\CONTAIND.DEF

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CONTAINR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /MDd /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /MDd /Yu"contpre.hxx"
# ADD CPP /MDd /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CONTASRT.CPP

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CONTPRE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /GX /Yc"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yc"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yc"contpre.hxx"
# ADD CPP /Yc"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\copttree.cxx
# End Source File
# Begin Source File

SOURCE=.\CRSTART.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DCREATOR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DEF.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DELTREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DumpBuffer.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\HASH.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HASHNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HLISNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KEYED.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KEYNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LIST.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LOCK.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NAVIGATR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OPTTREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\P5TICKER.CPP
# End Source File
# Begin Source File

SOURCE=.\PE_Debug.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
# End Source File
# Begin Source File

SOURCE=.\RING.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SEQ.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TABLE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRANSEX.CPP

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Intermediate_Dir ".\Release"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP Intermediate_Dir ".\Debug"
# ADD CPP /Yu"contpre.hxx"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug TrueTime"

# PROP BASE Intermediate_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /Yu"contpre.hxx"
# ADD CPP /Yu"contpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VerbAssert.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\contpre.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\Syncthrdcs.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
