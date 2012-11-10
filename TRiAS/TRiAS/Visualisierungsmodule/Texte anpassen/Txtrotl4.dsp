# Microsoft Developer Studio Project File - Name="txtrotl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=txtrotl - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Txtrotl4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Txtrotl4.mak" CFG="txtrotl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "txtrotl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "txtrotl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "txtrotl - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /Yu"txtrotlp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib tfrmwork.lib containr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\txtrotl.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\txtrotl.vmd
TargetName=txtrotl
InputPath=.\Release\txtrotl.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /FR /Fp".\Debug\txtrotld.pch" /Yu"txtrotlp.hxx" /Fd".\Debug\txtrotld.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5d.lib tfrm32d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\txtrotl.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetPath=.\Debug\txtrotl.vmd
TargetName=txtrotl
InputPath=.\Debug\txtrotl.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "txtrotl - Win32 Release"
# Name "txtrotl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DCUSTVIS.CXX
# End Source File
# Begin Source File

SOURCE=.\Dumpout.cxx
# End Source File
# Begin Source File

SOURCE=.\ITXTROTL.CXX
# End Source File
# Begin Source File

SOURCE=.\Regvism.cxx
# End Source File
# Begin Source File

SOURCE=.\TxtRotl.def
# End Source File
# Begin Source File

SOURCE=.\obj32\txtrotl.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# End Source File
# Begin Source File

SOURCE=.\TXTROTLP.CXX
# ADD CPP /Yc"txtrotlp.hxx"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\dcustvis.hxx
# End Source File
# Begin Source File

SOURCE=.\itxtrotl.hxx
# End Source File
# Begin Source File

SOURCE=.\TXTROTL.H
# End Source File
# Begin Source File

SOURCE=.\txtrotlp.hxx
# End Source File
# Begin Source File

SOURCE=.\txtrotlr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\Txtrotl.tpl

!IF  "$(CFG)" == "txtrotl - Win32 Release"

USERDEP__TXTRO="Version.mak"	
# Begin Custom Build
InputPath=.\Txtrotl.tpl

"TxtRotl.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TxtRotl.def

# End Custom Build

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

USERDEP__TXTRO="Version.mak"	
# Begin Custom Build
InputPath=.\Txtrotl.tpl

"TxtRotl.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TxtRotl.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TXTROTlv.tpl

!IF  "$(CFG)" == "txtrotl - Win32 Release"

USERDEP__TXTROT="Version.mak"	
# Begin Custom Build
InputPath=.\TXTROTlv.tpl

"TxtRotl.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TxtRotl.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

USERDEP__TXTROT="Version.mak"	
# Begin Custom Build
InputPath=.\TXTROTlv.tpl

"TxtRotl.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TxtRotl.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# End Target
# End Project
