# Microsoft Developer Studio Project File - Name="Stat32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Stat32 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Stat32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stat32.mak" CFG="Stat32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stat32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stat32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Statistische Auswertungen", KREAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Stat32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /Fr /Yu"statistp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr50.lib ospace5r.lib containr.lib tfrmwork.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinRel\geostat.ext"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\WinRel
TargetPath=.\WinRel\geostat.ext
TargetName=geostat
InputPath=.\WinRel\geostat.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /Fr /Yu"statistp.hxx" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 GMObjectsD.lib ospace5d.lib ixtnsd50.lib cont50d.lib tfrm32d.lib stdStr5d.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\geostatd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\WinDebug
TargetPath=.\Debug\geostatd.ext
TargetName=geostatd
InputPath=.\Debug\geostatd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Stat32 - Win32 Release"
# Name "Stat32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Classgi.cxx
# End Source File
# Begin Source File

SOURCE=.\Classkey.cxx
# End Source File
# Begin Source File

SOURCE=.\Dbclass.cxx
# End Source File
# Begin Source File

SOURCE=.\Dbinfo.cxx
# End Source File
# Begin Source File

SOURCE=.\Dblnumed.cxx
# End Source File
# Begin Source File

SOURCE=.\Geostat.cxx
# End Source File
# Begin Source File

SOURCE=.\Idkey.cxx
# End Source File
# Begin Source File

SOURCE=.\Objkey.cxx
# End Source File
# Begin Source File

SOURCE=.\Objprop.cxx
# End Source File
# Begin Source File

SOURCE=.\Sclipbrd.cxx
# End Source File
# Begin Source File

SOURCE=.\Stat32.def
# End Source File
# Begin Source File

SOURCE=.\Stat32.rc
# End Source File
# Begin Source File

SOURCE=.\Statifce.cxx
# End Source File
# Begin Source File

SOURCE=.\Res\StatistikPageExt.rgs
# End Source File
# Begin Source File

SOURCE=.\Statistp.cxx
# ADD CPP /Yc"statistp.hxx"
# End Source File
# Begin Source File

SOURCE=.\StatPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Stohwnd.cxx
# End Source File
# Begin Source File

SOURCE=.\Strutil.cxx
# End Source File
# Begin Source File

SOURCE=.\Macro\Topolog.ebs

!IF  "$(CFG)" == "Stat32 - Win32 Release"

# Begin Custom Build
InputPath=.\Macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

# Begin Custom Build
InputPath=.\Macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Trfkoord.cxx
# End Source File
# Begin Source File

SOURCE=.\Trfvect.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ABOUT.H
# End Source File
# Begin Source File

SOURCE=.\ABOUT.HXX
# End Source File
# Begin Source File

SOURCE=.\CLASSGI.HXX
# End Source File
# Begin Source File

SOURCE=.\CLASSKEY.HXX
# End Source File
# Begin Source File

SOURCE=.\DBCLASS.HXX
# End Source File
# Begin Source File

SOURCE=.\Dbinfo.hxx
# End Source File
# Begin Source File

SOURCE=.\DIRMATH.H
# End Source File
# Begin Source File

SOURCE=.\GEOSGUID.H
# End Source File
# Begin Source File

SOURCE=.\GEOSTAT.H
# End Source File
# Begin Source File

SOURCE=.\GEOSTAT.HXX
# End Source File
# Begin Source File

SOURCE=.\GeoStatConfig.h
# End Source File
# Begin Source File

SOURCE=.\GEOSTATR.H
# End Source File
# Begin Source File

SOURCE=.\Idkey.hxx
# End Source File
# Begin Source File

SOURCE=.\OBJKEY.HXX
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SCLIPBRD.HXX
# End Source File
# Begin Source File

SOURCE=.\STATISTP.HXX
# End Source File
# Begin Source File

SOURCE=.\STATPAGE.H
# End Source File
# Begin Source File

SOURCE=.\STOHWND.HXX
# End Source File
# Begin Source File

SOURCE=.\TRFKOORD.HXX
# End Source File
# Begin Source File

SOURCE=.\TRFVECT.HXX
# End Source File
# Begin Source File

SOURCE=.\VERSIO16.H
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Lupe.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\About.src
# End Source File
# Begin Source File

SOURCE=.\Stat32.rcv
# End Source File
# Begin Source File

SOURCE=.\MACRO\Topolog.ebc
# End Source File
# End Target
# End Project
