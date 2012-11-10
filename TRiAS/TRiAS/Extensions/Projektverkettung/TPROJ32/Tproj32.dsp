# Microsoft Developer Studio Project File - Name="Tproj32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Tproj32 - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Tproj32.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Tproj32.mak" CFG="Tproj32 - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Tproj32 - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tproj32 - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Projektverkettung/TPROJ32", JPFAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /Yu"tprojp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr50.lib ospace5r.lib containr.lib tfrmwork.lib stdstr5r.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinRel\Tproject.ext"
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\WinRel
TargetPath=.\WinRel\Tproject.ext
TargetName=Tproject
InputPath=.\WinRel\Tproject.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F /R  /Y  $(TargetPath) $(TRIASDIR_R) 
	xcopy /F  /R  /Y $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /FR /Yu"tprojp.hxx" /Fd".\WinDebug/Tprojecd.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd50.lib ospace5d.lib cont50d.lib tfrm32d.lib stdStr5d.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinDebug\Tprojecd.ext" /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none /map
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\WinDebug
TargetPath=.\WinDebug\Tprojecd.ext
TargetName=Tprojecd
InputPath=.\WinDebug\Tprojecd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F /R  /Y $(TargetPath) $(TRIASDIR_D) 
	xcopy /F /R  /Y $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Tproj32 - Win32 Release"
# Name "Tproj32 - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\MENUKEY.CXX
# End Source File
# Begin Source File

SOURCE=..\PROJPROF.CXX
# End Source File
# Begin Source File

SOURCE=..\TEPRODEF.CXX
# End Source File
# Begin Source File

SOURCE=..\TPMCODE.CXX
# End Source File
# Begin Source File

SOURCE=..\TPMEMBER.CXX
# End Source File
# Begin Source File

SOURCE=.\TPROJ32.DEF
# End Source File
# Begin Source File

SOURCE=.\TPROJ32.RC
# End Source File
# Begin Source File

SOURCE=..\TPROJECT.CXX
# End Source File
# Begin Source File

SOURCE=..\TPROJP.CXX
# ADD CPP /Yc"tprojp.hxx"
# End Source File
# Begin Source File

SOURCE=..\TXTEDIT.CXX
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\about.h
# End Source File
# Begin Source File

SOURCE=..\MENUKEY.HXX
# End Source File
# Begin Source File

SOURCE=..\PROJPROF.HXX
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=..\TEPRODEF.HXX
# End Source File
# Begin Source File

SOURCE=..\TPMCODE.HXX
# End Source File
# Begin Source File

SOURCE=..\tproject.h
# End Source File
# Begin Source File

SOURCE=..\TPROJECT.HXX
# End Source File
# Begin Source File

SOURCE=..\TPROJP.HXX
# End Source File
# Begin Source File

SOURCE=..\TXTEDIT.HXX
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Region.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\About.src
# End Source File
# Begin Source File

SOURCE=.\Tproj32.rcv
# End Source File
# End Target
# End Project
