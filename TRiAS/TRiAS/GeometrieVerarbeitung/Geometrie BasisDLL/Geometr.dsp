# Microsoft Developer Studio Project File - Name="Geometr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Geometr - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Geometr.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Geometr.mak" CFG="Geometr - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Geometr - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Geometr - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Geometr - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\..\z_hxx" /I "..\z_hxx" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"geometrp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\..\z_hxx" /i "..\z_hxx" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib containr.lib ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetDir=.\Release
TargetPath=.\Release\Geometr.dll
TargetName=Geometr
InputPath=.\Release\Geometr.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) \
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Geometr - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\..\z_hxx" /I "..\z_hxx" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"geometrp.hxx" /Fd".\Debug\GEOMETRD.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\..\z_hxx" /i "..\z_hxx" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont50d.lib ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:".\Debug\geometd.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetDir=.\Debug
TargetPath=.\Debug\geometd.dll
TargetName=geometd
InputPath=.\Debug\geometd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Geometr - Win32 Release"
# Name "Geometr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BasicFunctions.cxx
# End Source File
# Begin Source File

SOURCE=.\Cf.cxx
# End Source File
# Begin Source File

SOURCE=.\CLIPLIST.CXX
# End Source File
# Begin Source File

SOURCE=.\CLIPPING.CXX
# End Source File
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
# End Source File
# Begin Source File

SOURCE=.\DataObjectHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DATBANK.CXX
# End Source File
# Begin Source File

SOURCE=.\DLLBIND.CXX
# End Source File
# Begin Source File

SOURCE=.\DLLINIT.CXX
# End Source File
# Begin Source File

SOURCE=.\ErrorCorrection.cxx
# End Source File
# Begin Source File

SOURCE=.\FormatString.cxx
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ1.CXX
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ2.CXX
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ3.CXX
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ4.CXX
# End Source File
# Begin Source File

SOURCE=.\GEOMETR.DEF
# End Source File
# Begin Source File

SOURCE=.\Geometr.rc
# End Source File
# Begin Source File

SOURCE=.\GEOMETRP.CXX
# ADD CPP /Yc"geometrp.hxx"
# End Source File
# Begin Source File

SOURCE=.\GEOTRIAS.CXX
# End Source File
# Begin Source File

SOURCE=.\HDRENTRX.CXX
# End Source File
# Begin Source File

SOURCE=.\Helptext.cxx
# End Source File
# Begin Source File

SOURCE=.\Identlst.cxx
# End Source File
# Begin Source File

SOURCE=.\KOORD.CXX
# End Source File
# Begin Source File

SOURCE=.\LIBMAIN.CXX
# End Source File
# Begin Source File

SOURCE=.\MARK_OBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\Numeditx.cxx
# End Source File
# Begin Source File

SOURCE=.\Objgeocf.cxx
# End Source File
# Begin Source File

SOURCE=.\OBJGEOM.CXX
# End Source File
# Begin Source File

SOURCE=.\Objgext.cxx
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cxx
# End Source File
# Begin Source File

SOURCE=.\REGISTRY.CXX
# End Source File
# Begin Source File

SOURCE=.\ScreenGeometry.cxx
# End Source File
# Begin Source File

SOURCE=.\Selidlst.cxx
# End Source File
# Begin Source File

SOURCE=.\STRECKE.CXX
# End Source File
# Begin Source File

SOURCE=.\ZEICHNEN.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\Z_HXX\CtfxMfc.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\dragline.hxx
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

SOURCE=..\z_hxx\geo_obj1.hxx
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

SOURCE=.\Geometrp.hxx
# End Source File
# Begin Source File

SOURCE=.\GeometryConfig.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geotrias.hxx
# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\HELPTXTX.HXX
# End Source File
# Begin Source File

SOURCE=..\z_hxx\identlst.hxx
# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\Ienumobj.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\koord.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\mark_obj.hxx
# End Source File
# Begin Source File

SOURCE=.\Objgeocf.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\objgeom.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\objgext.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\objgguid.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\opdeklar.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\selidlsx.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\strecke.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\zeichnen.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Win32\Geometr.rcv
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\geometrv.tpl

!IF  "$(CFG)" == "Geometr - Win32 Release"

USERDEP__GEOME="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\geometrv.tpl

"geometr.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geometr.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Geometr - Win32 Debug"

USERDEP__GEOME="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\geometrv.tpl

"geometr.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geometr.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Group
# End Target
# End Project
