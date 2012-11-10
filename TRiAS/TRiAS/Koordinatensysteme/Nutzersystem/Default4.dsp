# Microsoft Developer Studio Project File - Name="Default" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Default - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Default4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Default4.mak" CFG="Default - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Default - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Default - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Default - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /Yu"defaultp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:".\DEFAULT.DEF" /out:".\Release\DefCtfs.css" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\DefCtfs.css
TargetName=DefCtfs
InputPath=.\Release\DefCtfs.css
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Default - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug4"
# PROP Intermediate_Dir ".\Debug4"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /Yu"defaultp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib ospace5d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:".\DEFAULT.DEF" /out:".\Debug4\DefCtfsd.css" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\DefCtfsd.css
TargetName=DefCtfsd
InputPath=.\Debug4\DefCtfsd.css
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) \
	

"$(TRIASDIR_D)\$(TargetName).css" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_D)\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "Default - Win32 Release"
# Name "Default - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CTF.idl

!IF  "$(CFG)" == "Default - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\CTF.idl

BuildCmds= \
	midl /Oicf /h "ICTF.h" /iid "ICTF_i.c" "CTF.idl"

".\CTF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ICTF.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ICTF_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Default - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\CTF.idl

BuildCmds= \
	midl /Oicf /h "ICTF.h" /iid "ICTF_i.c" "CTF.idl" \
	xcopy /F .\CTF.tlb $(TRIASTLB) \
	xcopy /F .\ICTF.h $(TRIASINCLUDE) \
	xcopy /F .\ICTF_i.c $(TRIASINCLUDE) \
	

".\CTF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ICTF.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ICTF_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DEFAULT.DEF
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DEFAULT.RC
# End Source File
# Begin Source File

SOURCE=.\DefaultCoordTrans.cpp

!IF  "$(CFG)" == "Default - Win32 Release"

!ELSEIF  "$(CFG)" == "Default - Win32 Debug"

# SUBTRACT CPP /WX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\defaultp.cxx
# ADD CPP /Yc"defaultp.hxx"
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\dllfloat.cxx
# End Source File
# Begin Source File

SOURCE=.\libmain.cxx
# End Source File
# Begin Source File

SOURCE=.\ManageParamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\default.h
# End Source File
# Begin Source File

SOURCE=.\DefaultCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\defaultp.hxx
# End Source File
# Begin Source File

SOURCE=.\ManageParamDlg.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CTF.tlb
# End Source File
# Begin Source File

SOURCE=.\DEFAULT.RCV
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\res\default.rgs
# End Source File
# Begin Source File

SOURCE=.\res\DefaultCoordTrans.rgs
# End Source File
# Begin Source File

SOURCE=.\ManageCoordParam.rgs
# End Source File
# Begin Source File

SOURCE=.\res\Soldner.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\DEFAULT.MAK
# End Source File
# Begin Source File

SOURCE=.\DEFAULT.TPL

!IF  "$(CFG)" == "Default - Win32 Release"

!ELSEIF  "$(CFG)" == "Default - Win32 Debug"

USERDEP__DEFAU="default.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\DEFAULT.TPL

"default.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f default.mak default.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DEFAULTV.TPL

!IF  "$(CFG)" == "Default - Win32 Release"

!ELSEIF  "$(CFG)" == "Default - Win32 Debug"

USERDEP__DEFAUL="default.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\DEFAULTV.TPL

"default.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f default.mak -nologo default.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
