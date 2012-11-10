# Microsoft Developer Studio Project File - Name="TDBGEO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TDBGEO - Win32 Debug MT
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TDBGEO.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TDBGEO.MAK" CFG="TDBGEO - Win32 Debug MT"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TDBGEO - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TDBGEO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TDBGEO - Win32 Debug MT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TDBGEO - Win32 Release MT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TDBGeo", NIAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_APARTMENT_THREADED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_USE_PERFMON_COUNTERS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TDBGEOd.dll"
# SUBTRACT LINK32 /incremental:no /map
# Begin Custom Build
OutDir=.\Debug
TargetName=TDBGEOd
InputPath=.\Debug\TDBGEOd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TDBGEO_0"
# PROP BASE Intermediate_Dir "TDBGEO_0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O2 /Ob2 /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_APARTMENT_THREADED" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build
OutDir=.\Release
TargetName=TDBGEO
InputPath=.\Release\TDBGEO.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TDBGEO___Win32_Debug_MT"
# PROP BASE Intermediate_Dir "TDBGEO___Win32_Debug_MT"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TDBGEO___Win32_Debug_MT"
# PROP Intermediate_Dir "TDBGEO___Win32_Debug_MT"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_FREE_THREADED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_USE_PERFMON_COUNTERS"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_USE_PERFMON_COUNTERS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TDBGEOd.dll"
# SUBTRACT BASE LINK32 /incremental:no /map
# ADD LINK32 ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"TDBGEO___Win32_Debug_MT/TDBGEOMTd.dll"
# SUBTRACT LINK32 /incremental:no /map
# Begin Custom Build
OutDir=.\TDBGEO___Win32_Debug_MT
TargetName=TDBGEOMTd
InputPath=.\TDBGEO___Win32_Debug_MT\TDBGEOMTd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUGMT VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TDBGEO___Win32_Release_MT"
# PROP BASE Intermediate_Dir "TDBGEO___Win32_Release_MT"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "TDBGEO___Win32_Release_MT"
# PROP Intermediate_Dir "TDBGEO___Win32_Release_MT"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_FREE_THREADED" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"TDBGEO___Win32_Release_MT/TDBGEOMT.dll"
# Begin Custom Build
OutDir=.\TDBGEO___Win32_Release_MT
TargetName=TDBGEOMT
InputPath=.\TDBGEO___Win32_Release_MT\TDBGEOMT.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUGMT VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TDBGEO - Win32 Debug"
# Name "TDBGEO - Win32 Release"
# Name "TDBGEO - Win32 Debug MT"
# Name "TDBGEO - Win32 Release MT"
# Begin Group "Geometries"

# PROP Default_Filter ""
# Begin Group "Points"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASCSOrientedPointGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSOrientedPointGeometry.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoint.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointEnum.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointGeometry.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoints.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoints.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTextPointGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTextPointGeometry.h
# End Source File
# End Group
# Begin Group "MultiplePoints"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASCSBoundaryGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSBoundaryGeometry.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSGeometryCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSGeometryCollection.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSLine.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSLine.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolygon.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolyline.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolyline.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSRectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSRectangle.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSVector.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSVector.h
# End Source File
# End Group
# Begin Group "Base Geometries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Geometries\ClipListe.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\ErrorCorrection.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\ErrorCorrection.inl
# End Source File
# Begin Source File

SOURCE=.\Geometries\Flaeche.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Flaeche.inl
# End Source File
# Begin Source File

SOURCE=.\GeometryObjects.h
# End Source File
# Begin Source File

SOURCE=.\GeometryObjects.inl
# End Source File
# Begin Source File

SOURCE=.\GeometryObjectsFwd.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Kante.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Kante.inl
# End Source File
# Begin Source File

SOURCE=.\Geometries\MarkObjects.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\MarkObjects.inl
# End Source File
# Begin Source File

SOURCE=.\Geometries\Punkt.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Punkt.inl
# End Source File
# Begin Source File

SOURCE=.\Geometries\Rechteck.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Rechteck.inl
# End Source File
# Begin Source File

SOURCE=.\Geometries\Strecke.h
# End Source File
# Begin Source File

SOURCE=.\Geometries\Strecke.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\SpatialTree.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SpatialTree.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSStorageService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSStorageService.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTearOff.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSpatialRelationService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSpatialRelationService.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dlldatax.c

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeometryMoniker.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBGEO.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBGEO.rc

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407 /d "_ATL_APARTMENT_THREADED"

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ClassFactoryMap.h
# End Source File
# Begin Source File

SOURCE=.\coordfield.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GeometryMoniker.h
# End Source File
# Begin Source File

SOURCE=.\GeoUtil.h
# End Source File
# Begin Source File

SOURCE=..\Include\GMObjects\PBasic.tlh
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\TDBGeoApp.h
# End Source File
# Begin Source File

SOURCE=.\TDBGeoConfig.h
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\TDBGeo.d

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TDBGeo.d
InputName=TDBGeo

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TDBGeo.d
InputName=TDBGeo

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TDBGeo.d
InputName=TDBGeo

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TDBGeo.d
InputName=TDBGeo

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TDbGeo.mc

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDbGeo.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TDBGEO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDbGeo.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TDBGEO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDbGeo.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TDBGEO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDbGeo.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TDBGEO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\TDBGEO.def
# End Source File
# Begin Source File

SOURCE=.\TDBGeo.rcv
# End Source File
# Begin Source File

SOURCE=.\TDBGeo.ver
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Group "Apartment Threading"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\OGCPoint.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSBoundaryGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSGeometryCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSLine.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSOrientedPointGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoint.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPoints.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolygonGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolylineGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSRectangle.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTextPointGeometry.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSVector.rgs
# End Source File
# End Group
# Begin Group "Free Threading"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\OGCPointMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSBoundaryGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSGeometryCollectionMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSLineMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSOrientedPointGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPointsMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolygonGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPolylineGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSRectangleMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTextPointGeometryMT.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSVectorMT.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\GeometryMoniker.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSStorageService.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSpatialRelationService.rgs
# End Source File
# End Group
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\TDBGEO.h

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# Begin Custom Build
InputPath=.\TDBGEO.h
InputName=TDBGEO

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# Begin Custom Build
InputPath=.\TDBGEO.h
InputName=TDBGEO

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# Begin Custom Build
InputPath=.\TDBGEO.h
InputName=TDBGEO

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# Begin Custom Build
InputPath=.\TDBGEO.h
InputName=TDBGEO

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TDbGeo.hmc
# End Source File
# Begin Source File

SOURCE=.\TDBGEO.tlb
# End Source File
# Begin Source File

SOURCE=.\Debug\TRiASCS.tlh
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TDBGEO.idl

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP Intermediate_Dir "se"
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDBGEO.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TDBGEO.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDBGEO.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TDBGEO.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Intermediate_Dir "se"
# PROP BASE Ignore_Default_Tool 1
# PROP Intermediate_Dir "se"
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDBGEO.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUGMT

".\TDBGEO.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TDBGEO.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUGMT

".\TDBGEO.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TDBGEO.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TDBGeoImpl.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "TDBGEO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TDBGEO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TDBGEO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Debug MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUGMT

".\TDBGEO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TDBGEO - Win32 Release MT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUGMT

".\TDBGEO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TDBGEO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "OGC Geometries"

# PROP Default_Filter ""
# Begin Group "OGC Points"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OGCPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\OGCPoint.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GeometryIdl.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SpatialReferenceIdl.idl
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
