# Microsoft Developer Studio Project File - Name="GMObjects" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GMObjects - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GMObjects.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GMObjects.mak" CFG="GMObjects - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GMObjects - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GMObjects - Win32 Release Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GMObjects - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GMObjects", SUAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GMObjects - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\_Release
TargetName=GMObjects
InputPath=.\_Release\GMObjects.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build
# Begin Special Build Tool
OutDir=.\_Release
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy     /F    $(OutDir)\*.tlh     $(TRIASINCLUDE)\GMObjects\    	xcopy     /F    /D    GMObjects\tlb\*.tlb     $(TRIASINCLUDE)\GMObjects\tlb\    	xcopy     /F    /D    GMObjects\tlb\*.dll     $(TRIASINCLUDE)\GMObjects\tlb\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Release Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GMObject"
# PROP BASE Intermediate_Dir "GMObject"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_RDebug"
# PROP Intermediate_Dir "_RDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "e:/Entwickl/Geomedia" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /Od /D "_RDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"_RDebug\GMObjectsR.lib"
# Begin Custom Build
OutDir=.\_RDebug
TargetName=GMObjectsR
InputPath=.\_RDebug\GMObjectsR.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build
# Begin Special Build Tool
OutDir=.\_RDebug
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy     /F    $(OutDir)\*.tlh     $(TRIASINCLUDE)\GMObjects\    	xcopy     /F    /D    GMObjects\tlb\*.tlb     $(TRIASINCLUDE)\GMObjects\tlb\    	xcopy     /F    /D    GMObjects\tlb\*.dll     $(TRIASINCLUDE)\GMObjects\tlb\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GMObject"
# PROP BASE Intermediate_Dir "GMObject"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /I "e:/Entwickl/Geomedia" /D "_RDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"_Debug/GMObjectsD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\_RDebug\GMObjectsR.lib"
# ADD LIB32 /nologo /out:"_Debug\GMObjectsD.lib"
# Begin Custom Build
OutDir=.\_Debug
TargetName=GMObjectsD
InputPath=.\_Debug\GMObjectsD.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build
# Begin Special Build Tool
OutDir=.\_Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy     /F    $(OutDir)\*.tlh     $(TRIASINCLUDE)\GMObjects\    	xcopy     /F    /D    GMObjects\tlb\*.tlb     $(TRIASINCLUDE)\GMObjects\tlb\    	xcopy     /F    /D    GMObjects\tlb\*.dll     $(TRIASINCLUDE)\GMObjects\tlb\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "GMObjects - Win32 Release"
# Name "GMObjects - Win32 Release Debug"
# Name "GMObjects - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h,hpp,hxx"
# Begin Source File

SOURCE=.\GMObjects\GMConstants.h

!IF  "$(CFG)" == "GMObjects - Win32 Release"

# Begin Custom Build
InputPath=.\GMObjects\GMConstants.h
InputName=GMConstants

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Release Debug"

# Begin Custom Build
InputPath=.\GMObjects\GMConstants.h
InputName=GMConstants

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Debug"

# Begin Custom Build
InputPath=.\GMObjects\GMConstants.h
InputName=GMConstants

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GMObjBuild.h
# End Source File
# Begin Source File

SOURCE=.\GMObjects\GMObjects.h

!IF  "$(CFG)" == "GMObjects - Win32 Release"

# Begin Custom Build
InputPath=.\GMObjects\GMObjects.h
InputName=GMObjects

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Release Debug"

# Begin Custom Build
InputPath=.\GMObjects\GMObjects.h
InputName=GMObjects

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Debug"

# Begin Custom Build
InputPath=.\GMObjects\GMObjects.h
InputName=GMObjects

"$(TRIASINCLUDE)\GMObjects\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\GMObjects

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp,c"
# Begin Source File

SOURCE=.\GMConstants.idl

!IF  "$(CFG)" == "GMObjects - Win32 Release"

# Begin Custom Build
InputPath=.\GMConstants.idl

".\GMConstants.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "GMConstants.h" /iid "GMConstants_i.c" "GMConstants.idl"

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Release Debug"

# Begin Custom Build
InputPath=.\GMConstants.idl

".\GMConstants.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "GMConstants.h" /iid "GMConstants_i.c" "GMConstants.idl"

# End Custom Build

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Debug"

# Begin Custom Build
InputPath=.\GMConstants.idl

"GMObjects\GMConstants.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "GMObjects\GMConstants.h" /iid "GMConstants_i.c" "GMConstants.idl"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GMObjects.cpp

!IF  "$(CFG)" == "GMObjects - Win32 Release"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Release Debug"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "GMObjects - Win32 Debug"

# ADD CPP /YX

!ENDIF 

# End Source File
# End Group
# Begin Group "Geomedia Type Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GMObjects\tlb\CADIGDSScanner.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\CADODBCScanner.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\dataview.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\DefCoordSystem.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\dgtabif.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\ExportDgnService.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\ExtendedPS.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GCADServer.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GDO.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GDOFRM.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GenericExtPS.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GeoMedia.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GMAdvSnap.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GMFeatureControls.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GMInsertAreaTopo.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\GMOracleOriginatingPipe.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\Mapview.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\NthArrw.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PAdvGMth.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PAdvLgd.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PBasic.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PClCmd.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PClient.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PCmdMgr.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PCmdSupt.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PCSS.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PDBPipe.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PGeoMath.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PPipe.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PProPipe.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PRaster.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PROPCOL.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PService.dll
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PService.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\PView.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\ScaleBar.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\styctl.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\UGEOM.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\UGEOM2D.tlb
# End Source File
# Begin Source File

SOURCE=.\GMObjects\tlb\UMATH.tlb
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
