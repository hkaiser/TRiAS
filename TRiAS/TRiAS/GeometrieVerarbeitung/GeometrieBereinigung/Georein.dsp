# Microsoft Developer Studio Project File - Name="Georein" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Georein - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Georein.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Georein.mak" CFG="Georein - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Georein - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Georein - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Georein - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"georeinp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr50.lib tfrmwork.lib containr.lib ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\GeoRein.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\georein.ext
TargetName=georein
InputPath=.\Release\georein.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Fp".\Debug\GEOREIND.pch" /Yu"georeinp.hxx" /Fd".\Debug\GEOREIND.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd50.lib tfrm32d.lib cont50d.lib ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /debug /machine:I386 /out:".\Debug\georeind.ext" /SUBSYSTEM:windows,4.0
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\georeind.ext
TargetName=georeind
InputPath=.\Debug\georeind.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Georein - Win32 Release"
# Name "Georein - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Badpunkt.cxx
# End Source File
# Begin Source File

SOURCE=.\Doppunkt.cxx
# End Source File
# Begin Source File

SOURCE=.\Entartet.cxx
# End Source File
# Begin Source File

SOURCE=.\Geofehl.cxx
# End Source File
# Begin Source File

SOURCE=.\Geomtest.cxx
# End Source File
# Begin Source File

SOURCE=.\GEOREIN.CXX
# End Source File
# Begin Source File

SOURCE=.\GEOREIN.DEF
# End Source File
# Begin Source File

SOURCE=.\Georein.rc
# End Source File
# Begin Source File

SOURCE=.\GEOREINP.CXX
# ADD CPP /Yc"georeinp.hxx"
# End Source File
# Begin Source File

SOURCE=.\Gerrlist.cxx
# End Source File
# Begin Source File

SOURCE=.\Greinext.cxx
# End Source File
# Begin Source File

SOURCE=.\Insel_ex.cxx
# End Source File
# Begin Source File

SOURCE=.\Insel_in.cxx
# End Source File
# Begin Source File

SOURCE=.\Kollinea.cxx
# End Source File
# Begin Source File

SOURCE=.\Kontinzi.cxx
# End Source File
# Begin Source File

SOURCE=.\Offen.cxx
# End Source File
# Begin Source File

SOURCE=.\Pa.cxx
# End Source File
# Begin Source File

SOURCE=.\Selbinzi.cxx
# End Source File
# Begin Source File

SOURCE=.\Spitze.cxx
# End Source File
# Begin Source File

SOURCE=.\Umlauf.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Badpunkt.hxx
# End Source File
# Begin Source File

SOURCE=..\Z_HXX\Datbank.hxx
# End Source File
# Begin Source File

SOURCE=.\Doppunkt.hxx
# End Source File
# Begin Source File

SOURCE=.\Entartet.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\FormatString.hxx
# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GEO_INL.HXX
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geo_obj.hxx
# End Source File
# Begin Source File

SOURCE=.\Geofehl.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geokonst.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geomdll.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geometrm.hxx
# End Source File
# Begin Source File

SOURCE=.\Georein.hxx
# End Source File
# Begin Source File

SOURCE=.\GeoreinConfig.h
# End Source File
# Begin Source File

SOURCE=.\Georeinm.hxx
# End Source File
# Begin Source File

SOURCE=.\Georeinp.hxx
# End Source File
# Begin Source File

SOURCE=.\Georeinr.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geotrias.hxx
# End Source File
# Begin Source File

SOURCE=.\Gerrlist.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\igeometr.hxx
# End Source File
# Begin Source File

SOURCE=.\Insel_ex.hxx
# End Source File
# Begin Source File

SOURCE=.\Insel_in.hxx
# End Source File
# Begin Source File

SOURCE=.\Kollinea.hxx
# End Source File
# Begin Source File

SOURCE=.\Kontinzi.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\koord.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\objgext.hxx
# End Source File
# Begin Source File

SOURCE=.\Offen.hxx
# End Source File
# Begin Source File

SOURCE=.\Pa.hxx
# End Source File
# Begin Source File

SOURCE=.\ReinKonst.hxx
# End Source File
# Begin Source File

SOURCE=.\Selbinzi.hxx
# End Source File
# Begin Source File

SOURCE=.\SmartInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\Spitze.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\strecke.hxx
# End Source File
# Begin Source File

SOURCE=.\Umlauf.hxx
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Win32\Georein.rcv
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\GEOREIN.TPL

!IF  "$(CFG)" == "Georein - Win32 Release"

USERDEP__GEORE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GEOREIN.TPL

"georein.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile georein.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

USERDEP__GEORE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GEOREIN.TPL

"georein.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile georein.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeoReinV.tpl

!IF  "$(CFG)" == "Georein - Win32 Release"

USERDEP__GEOREI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoReinV.tpl

"georein.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile georein.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

USERDEP__GEOREI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoReinV.tpl

"georein.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile georein.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Georein - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
