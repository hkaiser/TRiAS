# Microsoft Developer Studio Project File - Name="torten" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=torten - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Torten4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Torten4.mak" CFG="torten - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "torten - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "torten - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Visualisierungsmodule/Torten- und Balkendiagramme", SDFAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "torten - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"tortenp.hxx" /FD /c
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
# ADD LINK32 tfrmwork.lib containr.lib ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\torten.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\torten.vmd
TargetName=torten
InputPath=.\Release\torten.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /Fp".\Debug\tortend.pch" /Yu"tortenp.hxx" /Fd".\Debug\tortend.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont50d.lib ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\tortend.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\tortend.vmd
TargetName=tortend
InputPath=.\Debug\tortend.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "torten - Win32 Release"
# Name "torten - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CBMPBOX.CXX
# End Source File
# Begin Source File

SOURCE=.\CPALETTE.CXX
# End Source File
# Begin Source File

SOURCE=.\CPICBOX.CXX
# End Source File
# Begin Source File

SOURCE=.\DCUSTVIS.CXX
# End Source File
# Begin Source File

SOURCE=.\DRAWBALK.CXX
# End Source File
# Begin Source File

SOURCE=.\DRAWRECT.CXX
# SUBTRACT CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\DRAWTORT.CXX
# End Source File
# Begin Source File

SOURCE=.\FIXUPDC.CXX
# End Source File
# Begin Source File

SOURCE=.\IMPCUSTM.CXX
# End Source File
# Begin Source File

SOURCE=.\NUMEDITX.CXX
# End Source File
# Begin Source File

SOURCE=.\PALTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\Regvism.cxx
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJ32\TORTEN32.DEF
# End Source File
# Begin Source File

SOURCE=.\OBJ32\TORTEN32.RC
# ADD BASE RSC /l 0x407 /i "OBJ32"
# ADD RSC /l 0x407 /i "OBJ32" /i ".\OBJ32"
# End Source File
# Begin Source File

SOURCE=.\TORTENP.CXX
# ADD CPP /Yc"tortenp.hxx"
# End Source File
# Begin Source File

SOURCE=.\TYPESEL.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\cpalette.hxx
# End Source File
# Begin Source File

SOURCE=.\cpicbox.hxx
# End Source File
# Begin Source File

SOURCE=.\dcustvis.hxx
# End Source File
# Begin Source File

SOURCE=.\fixupdc.hxx
# End Source File
# Begin Source File

SOURCE=.\impcustm.hxx
# End Source File
# Begin Source File

SOURCE=.\paltree.hxx
# End Source File
# Begin Source File

SOURCE=.\paltree.inl
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\torten.h
# End Source File
# Begin Source File

SOURCE=.\TortenConfig.h
# End Source File
# Begin Source File

SOURCE=.\tortenid.h
# End Source File
# Begin Source File

SOURCE=.\tortenp.hxx
# End Source File
# Begin Source File

SOURCE=.\tortenr.h
# End Source File
# Begin Source File

SOURCE=.\typesel.h
# End Source File
# Begin Source File

SOURCE=.\typesel.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\OBJ32\TORTEN16.MAK
# End Source File
# Begin Source File

SOURCE=.\OBJ32\TORTEN32.TPL

!IF  "$(CFG)" == "torten - Win32 Release"

USERDEP__TORTE=".\obj32\torten16.mak"	
# Begin Custom Build
InputPath=.\OBJ32\TORTEN32.TPL

"torten32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f .\obj32\torten16.mak .\obj32\torten32.def

# End Custom Build

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

USERDEP__TORTE=".\obj32\torten16.mak"	
# Begin Custom Build
InputPath=.\OBJ32\TORTEN32.TPL

"torten32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f .\obj32\torten16.mak .\obj32\torten32.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OBJ32\tortenv.tpl

!IF  "$(CFG)" == "torten - Win32 Release"

USERDEP__TORTEN=".\obj32\torten16.mak"	
# Begin Custom Build
InputPath=.\OBJ32\tortenv.tpl

"torten32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f .\obj32\torten16.mak .\obj32\torten32.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

USERDEP__TORTEN=".\obj32\torten16.mak"	
# Begin Custom Build
InputPath=.\OBJ32\tortenv.tpl

"torten32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f .\obj32\torten16.mak .\obj32\torten32.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
