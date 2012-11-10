# Microsoft Developer Studio Project File - Name="TriasDB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRIASDB - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TriasDB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TriasDB.mak" CFG="TRIASDB - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TriasDB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TriasDB - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/DBEngine", HPLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /Zm150 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 TRiAS31D.lib OSpace5d.lib delayimp.lib iprop.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"Debug/TRiASDBD.dll" /delayload:msvcp60d.dll /delayload:msvcirtd.dll /delayload:iprop.dll /delayload:advapi32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none /map
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\TRiASDBD.dll
TargetName=TRiASDBD
InputPath=.\Debug\TRiASDBD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O2 /Ob2 /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_AFXDLL" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 TRiAS321.lib ospace5r.lib delayimp.lib iprop.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\TriasDB.def" /delayload:iprop.dll /delayload:advapi32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TriasDB.dll
TargetName=TriasDB
InputPath=.\ReleaseMinSize\TriasDB.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TriasDB - Win32 Debug"
# Name "TriasDB - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Helper Objects"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ConnectionMoniker.cpp
# End Source File
# Begin Source File

SOURCE=.\CSFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugSupport.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DirDialog.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GenObjectMap.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalVars.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PathDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertySupportImpl.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDataServerRegEntries.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDataServerRegEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectHandleMap.cpp
# End Source File
# End Group
# Begin Group "Property Objects"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DatabaseFeatureMap.cpp
# End Source File
# Begin Source File

SOURCE=.\MetaDataMap.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectCTF.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectStg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASVariantProperty.cpp
# End Source File
# End Group
# Begin Group "TRiASDB Objects"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\TRiASConnection.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASConnections.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASFeatures.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# ADD CPP /GR

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASRelation.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASRelations.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASView.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItems.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASViews.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "TRiAS Objects"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "User Interface Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\CreateNewParamWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateNewTemplateWiz.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OpenWizPropExt.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateWizPropExt.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASAccessDatabase.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASDatabase.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGuidFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjectsCollection.cpp
# End Source File
# End Group
# Begin Group "Interface Definitions"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\TriasDB.idl

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating type library ...
InputPath=.\TriasDB.idl

BuildCmds= \
	midl /win32 /Oicf /h "TRiASDB.h" /iid "TRiASDB_i.c"  "TRiASDB.idl" \
	xcopy /F "TRiASDB.h" $(TRIASINCLUDE) \
	xcopy /F "TRiASDB_i.c" $(TRIASINCLUDE) \
	xcopy /F "TRiASDB.tlb" $(TRIASTLB) \
	

"$(TRIASINCLUDE)\TRiASDB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\TRiASDB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASDB.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating type library ...
InputPath=.\TriasDB.idl

BuildCmds= \
	midl /win32 /Oicf /h "TRiASDB.h" /iid "TRiASDB_i.c"  /I c:\Msdev5\vc\include                                                                                                                                                                          "TRiASDB.idl" \
	xcopy /F "TRiASDB.h" $(TRIASINCLUDE) \
	

"TRiASDB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASDB.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASDB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Idl\TRiASDBEvents.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\Include\Idl\TRiASDBInterfaces.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\Include\Idl\TRiASDBNativeInterfaces.idl
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Performance Counter Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\PerfCounters.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# ADD CPP /Yc"stdafx.h"
# SUBTRACT CPP /Fr

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TriasDB.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Helper Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActDB.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionMoniker.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASDBEngineEvents.h
# End Source File
# Begin Source File

SOURCE=.\CSFactory.h
# End Source File
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\DebugUtil.h
# End Source File
# Begin Source File

SOURCE=.\DirDialog.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\EnumProperty.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHandling.h
# End Source File
# Begin Source File

SOURCE=.\FindInMapOrCreateObject.h
# End Source File
# Begin Source File

SOURCE=.\GenObjectMap.h
# End Source File
# Begin Source File

SOURCE=.\GlobalVars.h
# End Source File
# Begin Source File

SOURCE=.\MessageBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\PathDialog.h
# End Source File
# Begin Source File

SOURCE=.\PersistEnum.h
# End Source File
# Begin Source File

SOURCE=.\PersistStgImpl.h
# End Source File
# Begin Source File

SOURCE=.\PropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\PropertySupport.h
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilter.h
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilters.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDataServerRegEntries.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDataServerRegEntry.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDBApp.h
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectHandleMap.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Connection Points"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CPTRiASConnectionEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASFeatureEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASObjectEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASObjectsEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASProjectEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASPropertyEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASViewEvents.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASViewItemEvents.h
# End Source File
# End Group
# Begin Group "Property Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DatabaseFeatureMap.h
# End Source File
# Begin Source File

SOURCE=.\MetaDataMap.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectCTF.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProjectStg.h
# End Source File
# Begin Source File

SOURCE=.\TRiASVariantProperty.h
# End Source File
# End Group
# Begin Group "TRiASDB Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\TRiASConnection.h
# End Source File
# Begin Source File

SOURCE=.\TRiASConnections.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\TRiASFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsCollection.h
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsOperations.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProperties.h
# End Source File
# Begin Source File

SOURCE=.\TRiASProperty.h
# End Source File
# Begin Source File

SOURCE=.\TRiASRelation.h
# End Source File
# Begin Source File

SOURCE=.\TRiASRelations.h
# End Source File
# Begin Source File

SOURCE=.\TRiASView.h
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItem.h
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItems.h
# End Source File
# Begin Source File

SOURCE=.\TRiASViews.h
# End Source File
# End Group
# Begin Group "TRiAS Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "User Interface Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\CreateNewParamWiz.h
# End Source File
# Begin Source File

SOURCE=.\OpenWizPropExt.h
# End Source File
# Begin Source File

SOURCE=.\PropSheetExt.h
# End Source File
# Begin Source File

SOURCE=.\TemplateWizPropExt.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASGuidFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjectsCollection.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDBConfig.h
# End Source File
# Begin Source File

SOURCE=..\Include\TRiASDBDispIds.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDBGuids.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Buchv2.ico
# End Source File
# Begin Source File

SOURCE=.\Buchv3.ico
# End Source File
# Begin Source File

SOURCE=.\RES\dbdold.bin
# End Source File
# Begin Source File

SOURCE=.\RES\Idt1024.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Idt1024c.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Idt_v12.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Idt_v13.dbd
# End Source File
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\Release\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\ReleaseMinSize\Msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\project.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Question.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Ris2048c.011
# End Source File
# Begin Source File

SOURCE=.\RES\Ris2048c.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\ris2048c_v17.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\ris2048c_v19.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Riwn_com.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Topkarte.bmp
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\ConnectionMoniker.rgs
# End Source File
# Begin Source File

SOURCE=.\DatabaseFeatureMap.rgs
# End Source File
# Begin Source File

SOURCE=.\GenObjectMap.rgs
# End Source File
# Begin Source File

SOURCE=.\MetaDataMap.rgs
# End Source File
# Begin Source File

SOURCE=.\OpenWizPropExt.rgs
# End Source File
# Begin Source File

SOURCE=.\TemplateWizPropExt.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASAutoSaveProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCompatibleDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASConnection.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilter.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASConnectionFilters.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASConnections.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASDatabaseOnStg.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASDataServerRegEntries.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASFeatureHandleMap.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASGenericHandleMap.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASGuidFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObject.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectHandleMap.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsHandleMap.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASObjectsOperations.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASProject.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASProjects.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASProperties.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASRelation.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASRelations.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObject.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleObjectsCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASVariantProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASView.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItem.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASViewItems.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASViews.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\TriasDB.tpl

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build - Generating definition file (.DEF) ...
InputPath=.\TriasDB.tpl

"TRiASDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASDB.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build - Generating definition file (.DEF) ...
InputPath=.\TriasDB.tpl

"TRiASDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASDB.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASDBv.Tpl

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__TRIASD="Version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\TRiASDBv.Tpl

"TRiASDB.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASDB.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__TRIASD="Version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\TRiASDBv.Tpl

"TRiASDB.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASDB.Rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\Version.tpl

"x" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc;*.hmc"
# Begin Source File

SOURCE=.\DBMSG.hmc
# End Source File
# Begin Source File

SOURCE=.\DBMSG.MC

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build - Generating message tables ...
InputDir=.
OutDir=.\Debug
InputPath=.\DBMSG.MC
InputName=DBMSG

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	xcopy /F DBMsg.hmc $(TRIASINCLUDE) \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\help\DBMsg.d" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\DBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build - Generating message tables ...
InputDir=.
OutDir=.\ReleaseMinSize
InputPath=.\DBMSG.MC
InputName=DBMSG

BuildCmds= \
	cl -nologo -TC -C -EP -DNDEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Help\DBMsg.d" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Database Schemes"

# PROP Default_Filter "*.dds"
# Begin Source File

SOURCE=.\Idt_v11.dds

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build
InputPath=.\Idt_v11.dds

".\Res\Idt1024c.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\Idt1024c $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build
InputPath=.\Idt_v11.dds

".\Res\Idt1024c.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\Idt1024c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Idt_v12.dds

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build
InputPath=.\Idt_v12.dds

".\Res\Idt_v12.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\Idt_v12 $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build
InputPath=.\Idt_v12.dds

".\Res\Idt_v12.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\Idt_v12 $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Idt_v13.dds

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build
InputPath=.\Idt_v13.dds

".\Res\Idt_v13.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\Idt_v13 $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RISN_V16.DDS

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build - Generating database scheme ...
InputPath=.\RISN_V16.DDS

".\Res\ris2048c.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\ris2048c $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build - Generating database scheme ...
InputPath=.\RISN_V16.DDS

".\Res\ris2048c.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\ris2048c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RISN_V17.DDS

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build - Generating database scheme ...
InputPath=.\RISN_V17.DDS

".\Res\ris2048c_v17.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\ris2048c_v17 $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build
InputPath=.\RISN_V17.DDS

".\Res\ris2048c_v17.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\ris2048c_v17 $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RISN_V19.DDS

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build
InputPath=.\RISN_V19.DDS

".\Res\ris2048c_v19.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp  -h- -o .\Res\ris2048c_v19 $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RIWN_COM.DDS

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

# Begin Custom Build - Generating project database scheme ...
InputPath=.\RIWN_COM.DDS

".\Res\riwn_com.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\riwn_com $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# Begin Custom Build - Generating project database scheme ...
InputPath=.\RIWN_COM.DDS

".\Res\riwn_com.dbd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ddsp -s -h- -o .\Res\riwn_com $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.d;*.hpj;*.fmt"
# Begin Source File

SOURCE=.\HELP\CONTENTS.D

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__CONTE=".\Help\TRiASDB.Fmt"	".\Help\DBMsg.d"	".\Help\Contents.Hpj"	".\help\Recherche.d"	
# Begin Custom Build - Generating documentation ...
InputPath=.\HELP\CONTENTS.D

".\help\TRiASDB.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autoduck /L .\help\contents.log /s .\help\TRiASDB.Fmt /rh /t4 /o  .\help\contents.rtf  .\help\contents.d .\help\Recherche.d .\help\dbmsg.d *.h *.cpp  *.idl .\QueryDef\*.idl .\QueryDef\*.cpp .\Querydef\*.h $(TRIASINCLUDE)\idl\*.idl 
	hcrtf /a /o .\help\TRiASDB.hlp /xn .\help\contents.hpj 
	xcopy /F .\help\TRiASDB.hlp $(TRIASINCLUDE)\help 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__CONTE=".\Help\TRiASDB.Fmt"	".\Help\DBMsg.d"	".\Help\Contents.Hpj"	".\help\Recherche.d"	
# Begin Custom Build - Generating documentation ...
InputPath=.\HELP\CONTENTS.D

".\help\TRiASDB.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autoduck /L .\help\contents.log /s .\help\TRiASDB.Fmt /rh /t4 /o  .\help\contents.rtf  .\help\contents.d .\help\Recherche.d .\help\dbmsg.d *.h *.cpp  *.idl .\QueryDef\*.idl .\QueryDef\*.cpp .\Querydef\*.h $(TRIASINCLUDE)\idl\*.idl 
	hcrtf /a /o .\help\TRiASDB.hlp /xn .\help\contents.hpj 
	xcopy /F .\help\TRiASDB.hlp $(TRIASINCLUDE)\help 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HELP\CONTENTS.TPL

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__CONTEN="Version.mak"	
# Begin Custom Build - Generating help project file (.HPJ) ...
InputPath=.\HELP\CONTENTS.TPL

".\Help\Contents.Hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\Contents.Hpj

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__CONTEN="Version.mak"	
# Begin Custom Build - Generating help project file (.HPJ) ...
InputPath=.\HELP\CONTENTS.TPL

".\Help\Contents.Hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\Contents.Hpj

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEHELP.BAT
# End Source File
# Begin Source File

SOURCE=.\HELP\Recherche.d
# End Source File
# Begin Source File

SOURCE=.\HELP\TRIASDB.HLP
# End Source File
# Begin Source File

SOURCE=.\HELP\TRiASDBFmt.tpl

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

USERDEP__TRIASDB="version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\HELP\TRiASDBFmt.tpl

".\Help\TRiASDB.Fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\TRiASDB.Fmt

# End Custom Build

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

USERDEP__TRIASDB="version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\HELP\TRiASDBFmt.tpl

".\Help\TRiASDB.Fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\TRiASDB.Fmt

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\truetime\TrueTime.xls
# End Source File
# End Group
# Begin Group "General Purpose Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# ADD CPP /D "_MERGE_PROXYSTUB"
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\TriasDB.def

!IF  "$(CFG)" == "TriasDB - Win32 Debug"

!ELSEIF  "$(CFG)" == "TriasDB - Win32 Release MinSize"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TriasDB.rc
# End Source File
# Begin Source File

SOURCE=.\TRiASDBDispIds.h
# End Source File
# End Group
# End Target
# End Project
