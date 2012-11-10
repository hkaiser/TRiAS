# Microsoft Developer Studio Project File - Name="Geoedit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Geoedit - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Geoedit.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Geoedit.mak" CFG="Geoedit - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Geoedit - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Geoedit - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Geoedit - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"GeoEditP.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtAtr50.lib tfrmwork.lib containr.lib ospace5r.lib triastlb.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ebn.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:".\Release\GeoEdit.ext" /delayload:sumnpb22.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\GeoEdit.ext
TargetName=GeoEdit
InputPath=.\Release\GeoEdit.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\Z_HXX" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Fp".\Debug\GEOEDITD.pch" /Yu"GeoEditP.h" /Fd".\Debug\GEOEDITD.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtAtd50.lib tfrm32d.lib cont50d.lib ospace5d.lib triastld.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ebn.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:".\Debug\GeoEditD.ext" /delayload:sumnpb22.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /nodefaultlib
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\GeoEditD.ext
TargetName=GeoEditD
InputPath=.\Debug\GeoEditD.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Geoedit - Win32 Release"
# Name "Geoedit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AreaPartition.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonBorder.cpp
# End Source File
# Begin Source File

SOURCE=.\CrossObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DesignDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Designing.cpp
# End Source File
# Begin Source File

SOURCE=.\DragMultiLine.cpp
# End Source File
# Begin Source File

SOURCE=.\EditBaseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCoordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumObjektGeometrie.cpp
# End Source File
# Begin Source File

SOURCE=.\FixPointsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoEdit.def
# End Source File
# Begin Source File

SOURCE=.\Geoedit.rc
# End Source File
# Begin Source File

SOURCE=.\GeoEditInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoEditLib.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoEditOutside.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoEditP.cpp
# ADD CPP /Yc"GeoEditP.h"
# End Source File
# Begin Source File

SOURCE=.\IGeoEdit.idl

!IF  "$(CFG)" == "Geoedit - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\IGeoEdit.idl

BuildCmds= \
	midl /Oicf /h IGeoEdit.h /iid IGeoEdit.c IGeoEdit.idl

"IGeoEdit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\IGeoEdit.idl

BuildCmds= \
	midl /Oicf /h IGeoEdit.h /iid IGeoEdit.c IGeoEdit.idl

"IGeoEdit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IntersectLineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IslandAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\Jumptab.cpp
# End Source File
# Begin Source File

SOURCE=.\Kreis.cpp
# ADD CPP /Yu"GeoEditP.h"
# End Source File
# Begin Source File

SOURCE=.\LineElongation.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeRectangular.cpp
# End Source File
# Begin Source File

SOURCE=.\Marker.cpp
# End Source File
# Begin Source File

SOURCE=.\NewArea.cpp
# End Source File
# Begin Source File

SOURCE=.\NewLine.cpp
# End Source File
# Begin Source File

SOURCE=.\NewPoint.cpp
# ADD CPP /Yu"GeoEditP.h"
# End Source File
# Begin Source File

SOURCE=.\ObjectModify.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectModifyFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectMove.cpp
# End Source File
# Begin Source File

SOURCE=.\PropExt.cpp
# End Source File
# Begin Source File

SOURCE=.\RestrictCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\RestrictLine.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleDesignDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBars.cpp
# End Source File
# Begin Source File

SOURCE=.\TopicalObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\UIOwnerFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\VertexAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\VertexModDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VertexMove.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AreaPartition.h
# End Source File
# Begin Source File

SOURCE=.\BmpBtn.h
# End Source File
# Begin Source File

SOURCE=.\CommonBorder.h
# End Source File
# Begin Source File

SOURCE=..\Z_HXX\Datbank.hxx
# End Source File
# Begin Source File

SOURCE=.\DragMultiLine.h
# End Source File
# Begin Source File

SOURCE=.\EditBaseDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditCoordDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditKonst.h
# End Source File
# Begin Source File

SOURCE=.\EnumObjektGeometrie.h
# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GEO_INL.HXX
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geo_obj.hxx
# End Source File
# Begin Source File

SOURCE=.\GeoEdit.h
# End Source File
# Begin Source File

SOURCE=.\GeoEditConfig.h
# End Source File
# Begin Source File

SOURCE=.\GeoEditLib.h
# End Source File
# Begin Source File

SOURCE=.\GeoEditM.h
# End Source File
# Begin Source File

SOURCE=.\GeoEditOutside.h
# End Source File
# Begin Source File

SOURCE=.\GeoEditP.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geokonst.hxx
# End Source File
# Begin Source File

SOURCE=..\z_hxx\geometrm.hxx
# End Source File
# Begin Source File

SOURCE=.\IntersectLineDlg.h
# End Source File
# Begin Source File

SOURCE=.\IslandAdd.h
# End Source File
# Begin Source File

SOURCE=.\jumptab.h
# End Source File
# Begin Source File

SOURCE=..\z_hxx\koord.hxx
# End Source File
# Begin Source File

SOURCE=.\Kreis.h
# End Source File
# Begin Source File

SOURCE=.\LineElongation.h
# End Source File
# Begin Source File

SOURCE=.\MakeRectangular.h
# End Source File
# Begin Source File

SOURCE=.\Marker.h
# End Source File
# Begin Source File

SOURCE=.\NewArea.h
# End Source File
# Begin Source File

SOURCE=.\NewLine.h
# End Source File
# Begin Source File

SOURCE=.\NewPoint.h
# End Source File
# Begin Source File

SOURCE=.\ObjectModify.h
# End Source File
# Begin Source File

SOURCE=.\ObjectMove.h
# End Source File
# Begin Source File

SOURCE=..\Z_HXX\ProgressProxy.h
# End Source File
# Begin Source File

SOURCE=.\PropExt.h
# End Source File
# Begin Source File

SOURCE=..\Z_HXX\Reinguid.h
# End Source File
# Begin Source File

SOURCE=.\SmartInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\TopicalObjects.h
# End Source File
# Begin Source File

SOURCE=..\Z_HXX\uiowner.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\VertexAdd.h
# End Source File
# Begin Source File

SOURCE=.\VertexModDlg.h
# End Source File
# Begin Source File

SOURCE=.\VertexMove.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cross_m.cur
# End Source File
# Begin Source File

SOURCE=.\Delete.cur
# End Source File
# Begin Source File

SOURCE=.\DesignToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\EditToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\GeoEdit.rcv
# End Source File
# Begin Source File

SOURCE=.\GeoEditOutside.rc
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\IGeoEdit.tlb
# End Source File
# Begin Source File

SOURCE=.\Innerh.cur
# End Source File
# Begin Source File

SOURCE=.\Move.cur
# End Source File
# Begin Source File

SOURCE=.\Palette.cur
# End Source File
# Begin Source File

SOURCE=.\Split.cur
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\AreaPartition.rgs
# End Source File
# Begin Source File

SOURCE=.\CommonBorder.rgs
# End Source File
# Begin Source File

SOURCE=.\Designing.rgs
# End Source File
# Begin Source File

SOURCE=.\DragMultiLine.rgs
# End Source File
# Begin Source File

SOURCE=.\EnumObjektGeometrie.rgs
# End Source File
# Begin Source File

SOURCE=.\IslandAdd.rgs
# End Source File
# Begin Source File

SOURCE=.\LineElongation.rgs
# End Source File
# Begin Source File

SOURCE=.\MakeRectangular.rgs
# End Source File
# Begin Source File

SOURCE=.\NewArea.rgs
# End Source File
# Begin Source File

SOURCE=.\NewLine.rgs
# End Source File
# Begin Source File

SOURCE=.\NewPoint.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectModify.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectMove.rgs
# End Source File
# Begin Source File

SOURCE=.\RestrictCursor.rgs
# End Source File
# Begin Source File

SOURCE=.\RestrictLine.rgs
# End Source File
# Begin Source File

SOURCE=.\TopicalObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\VertexAdd.rgs
# End Source File
# Begin Source File

SOURCE=.\VertexMove.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\GeoEdit.tpl

!IF  "$(CFG)" == "Geoedit - Win32 Release"

USERDEP__GEOED="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoEdit.tpl

"geoedit.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geoedit.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

USERDEP__GEOED="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoEdit.tpl

"geoedit.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geoedit.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeoEditV.tpl

!IF  "$(CFG)" == "Geoedit - Win32 Release"

USERDEP__GEOEDI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoEditV.tpl

"geoedit.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geoedit.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

USERDEP__GEOEDI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\GeoEditV.tpl

"geoedit.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile geoedit.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Geoedit - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

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
