# Microsoft Developer Studio Project File - Name="TRiASCs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRIASCS - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASCs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASCs.mak" CFG="TRIASCS - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASCs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASCs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiASCs", GEBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /D "_MERGE_PROXYSTUB" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib delayimp.lib shfolder.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/TRiASCsD.dll" /delayload:shlwapi.dll /delayload:shfolder.dll /delayload:version.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:comctl32.dll /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\_Debug
TargetName=TRiASCsD
InputPath=.\_Debug\TRiASCsD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TRiASCs_"
# PROP BASE Intermediate_Dir "TRiASCs_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "$(TRIASINCLUDE)/atl" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O2 /Ob2 /D "_WINDLL" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_MERGE_PROXYSTUB" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/TRiASCsD.dll" /pdbtype:sept
# ADD LINK32 delayimp.lib shfolder.lib shlwapi.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /delayload:shfolder.dll /delayload:shlwapi.dll /delayload:version.dll /delayload:version.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:comctl32.dll /delayload:olepro32.dll /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\_Release
TargetName=TRiASCs
InputPath=.\_Release\TRiASCs.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TRiASCs - Win32 Debug"
# Name "TRiASCs - Win32 Release"
# Begin Group "TRiASCS"

# PROP Default_Filter ""
# Begin Group "CoordinateSystems"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPTRiASCsEvents.h
# End Source File
# Begin Source File

SOURCE=.\EnumCoordSystemNames.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumCoordSystemNames.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordSystem.h
# End Source File
# Begin Source File

SOURCE=.\TRiASGeographicCS.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGeographicCS.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectedCS.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectedCS.h
# End Source File
# End Group
# Begin Group "CoordinateTransformations"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CompareCoordSystems.cpp
# End Source File
# Begin Source File

SOURCE=.\CompareCoordSystems.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordTransform.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSDatumTransformation.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSDatumTransformation.h
# End Source File
# End Group
# Begin Group "CoordinateContainers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRIASCSSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TRIASCSSet.h
# End Source File
# End Group
# Begin Group "LibCTF"

# PROP Default_Filter ""
# Begin Group "gctpc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LibCTF\gctpc\cproj.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\LibCTF\gctpc\cproj.h
# End Source File
# Begin Source File

SOURCE=.\ECEF.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\gctpc\lamccfor.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\LibCTF\gctpc\lamccinv.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\LibCTF\DS_Through7Parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\DS_Through7Parameter.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\DS_ThroughECEF.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\DS_ThroughECEF.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\LibCTF.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\LIBCTFImpl.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_CassiniSoldner.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_CassiniSoldner.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_CylindricEquirectangular.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_CylindricEquirectangular.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_GaussKrueger.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_GaussKrueger.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_Generic.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_Generic.h
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_LambertConicConformal2P.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\PCS_LambertConicConformal2P.h
# End Source File
# End Group
# Begin Group "Property Pages"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASCSPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPpg.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUI.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUI.h
# End Source File
# Begin Source File

SOURCE=.\TRiASGCSPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGCSPpg.h
# End Source File
# Begin Source File

SOURCE=.\TRiASPCSPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASPCSPpg.h
# End Source File
# End Group
# Begin Group "TestTools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\vb\CSSet.bas
# End Source File
# Begin Source File

SOURCE=.\vb\CSSet2.bas
# End Source File
# Begin Source File

SOURCE=.\vb\Form1.frm
# End Source File
# Begin Source File

SOURCE=.\vb\GeoZuGau.bas
# End Source File
# Begin Source File

SOURCE=.\vb\Main.bas
# End Source File
# Begin Source File

SOURCE=.\vb\Module1.bas
# End Source File
# Begin Source File

SOURCE=.\vb\Project1.vbp
# End Source File
# Begin Source File

SOURCE=.\vb\TestAbstandsberechnung.frm
# End Source File
# End Group
# Begin Group "Build Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\epsg\epsg_v32.reg
# End Source File
# Begin Source File

SOURCE=.\epsg\V3.2\Epsg_v32_95.mdb
# End Source File
# Begin Source File

SOURCE=.\epsg\epsg_v40.reg
# End Source File
# Begin Source File

SOURCE=.\epsg\V4.0\epsg_v40_95.mdb
# End Source File
# Begin Source File

SOURCE=.\epsg\makeepsg.cmd
# End Source File
# Begin Source File

SOURCE=.\epsg\MakeEPSG.pl
# End Source File
# End Group
# Begin Group "EPSG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EPSG.cpp
# End Source File
# Begin Source File

SOURCE=.\EPSG.h

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EPSGMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\EPSGMgr.h
# End Source File
# End Group
# Begin Group "CoordinateServices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASCSDistanceService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSDistanceService.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTransformService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTransformService.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUIService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUIService.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSWktService.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSWktService.h
# End Source File
# End Group
# Begin Group "Proxy Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlldatax.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# End Source File
# End Group
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LibCTF\DtoACTF.cpp
# End Source File
# Begin Source File

SOURCE=.\LibCTF\DtoACTF.h
# End Source File
# Begin Source File

SOURCE=.\EllipsParams.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceWrappers.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCs.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCs.idl

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASCs.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASCs.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TRiASCs.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASCs.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TRiASCs.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\TRiASCs.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASCsConfig.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCSImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCSImpl.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASCs.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TRiASCs.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASCs.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DOCJET.DJT

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\help\Koordinatentransformation.d
# End Source File
# Begin Source File

SOURCE=.\help\TRiasCS.d

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiasCS.d
InputName=TRiasCS

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiasCS.d
InputName=TRiasCS

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\help\TRiASCs.hh
# End Source File
# Begin Source File

SOURCE=.\help\TRIASCS.HLP
# End Source File
# Begin Source File

SOURCE=.\TRiasCS.mc

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiasCS.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASCs.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiasCS.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TRiASCs.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\help\TRiASCs.tpl
# End Source File
# Begin Source File

SOURCE=.\help\TRiASCshh.awk
# End Source File
# Begin Source File

SOURCE=.\help\TRiASCshh.sed
# End Source File
# Begin Source File

SOURCE=.\help\TRiASCsTpl.cnt
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\DefHKLM.rgs
# End Source File
# Begin Source File

SOURCE=.\DistanceService.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordSystem.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCoordTransform.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSDatumTransformation.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSPpg.rgs
# End Source File
# Begin Source File

SOURCE=.\TRIASCSSet.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSTransformService.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUI.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSUIService.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCSWktService.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASGCSPpg.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASGeographicCS.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASPCSPpg.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectedCS.rgs
# End Source File
# End Group
# Begin Group "CoordSystems"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\BeGeod.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGeodDeg.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGk12_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGk15_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGk3_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGk6_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGk9_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGkAuto3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGkRd8312_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGkRd8315_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGkRd839_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BeGkRd83Auto3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\BesD.tcf
# End Source File
# Begin Source File

SOURCE=.\res\EtUtm15_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\EtUtm3_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\EtUtm9_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\EtUtmAuto6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGeod.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGeodDeg.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk12_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk15_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk15_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk3_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk6_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk9_3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGk9_6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGkAuto3.tcf
# End Source File
# Begin Source File

SOURCE=.\res\KrGkAuto6.tcf
# End Source File
# Begin Source File

SOURCE=.\res\SoldnerBerlin.tcf
# End Source File
# Begin Source File

SOURCE=.\res\WgsGeod.tcf
# End Source File
# Begin Source File

SOURCE=.\res\WgsGeodDeg.tcf
# End Source File
# End Group
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCs.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASCs.def
# End Source File
# Begin Source File

SOURCE=.\TRiASCS.rcv
# End Source File
# Begin Source File

SOURCE=.\TRiASCS.ver
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\CONTENTS.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\msg00407.bin
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASCs.h

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiasCS.hmc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\help\TRiASCS.HPJ
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASCs.tlb
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASCs_i.c

!IF  "$(CFG)" == "TRiASCs - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASCs - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
