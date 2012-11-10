# Microsoft Developer Studio Project File - Name="fakemfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=fakemfc - Win32 Debug Subclass ORWnd
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fakemfc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fakemfc.mak" CFG="fakemfc - Win32 Debug Subclass ORWnd"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fakemfc - Win32 Debug with OT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fakemfc - Win32 Release with OT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fakemfc - Win32 Debug Subclass ORWnd" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/FakeMFC", ZJDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\fakemfc_"
# PROP BASE Intermediate_Dir ".\fakemfc_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\fakeot.deb"
# PROP Intermediate_Dir ".\fakeot.deb"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_ATL_SINGLETHREAD" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /FR /Yu"fakemfcp.hxx" /Fd"Debug/fakemfcd.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "_AFXEXT" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"fakemfcp.hxx" /Fd".\fakeot.deb\fakemfcd.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_SEC_CLASSES"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 triastld.lib ota42d.lib stdcppd.lib ospace2d.lib netapi32.lib largeint.lib /nologo /dll /debug /machine:I386 /out:"Debug/fakemfcd.ext" /stub:"rights.exe" /subsystem:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ospace5d.lib delayimp.lib netapi32.lib largeint.lib /nologo /dll /incremental:no /debug /machine:I386 /out:".\fakeot.deb\fakemfcd.ext" /delayload:crp32dll.dll /delayload:advapi32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\fakeot.deb
TargetPath=.\fakeot.deb\fakemfcd.ext
TargetName=fakemfcd
InputPath=.\fakeot.deb\fakemfcd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\fakemfc_"
# PROP BASE Intermediate_Dir ".\fakemfc_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\fakeot.rel"
# PROP Intermediate_Dir ".\fakeot.rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_ATL_SINGLETHREAD" /D "_SECDLL" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /FR /Yu"fakemfcp.hxx" /Fd"fakeot.deb/fakemfcd.pdb" /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "_AFXEXT" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"fakemfcp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_SEC_CLASSES"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_USE_SEC_CLASSES"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 triastld.lib ot5042d.lib stdcppd.lib ospace2d.lib netapi32.lib largeint.lib /nologo /dll /debug /machine:I386 /out:"fakeot.deb/fakemfcd.ext" /stub:"rights.exe" /subsystem:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 triastlb.lib ospace5r.lib delayimp.lib netapi32.lib largeint.lib /nologo /dll /incremental:no /debug /machine:I386 /out:".\fakeot.rel\fakemfc.ext" /delayload:crp32dll.dll /delayload:advapi32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\fakeot.rel
TargetPath=.\fakeot.rel\fakemfc.ext
TargetName=fakemfc
InputPath=.\fakeot.rel\fakemfc.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "fakemfc___Win32_Debug_Subclass_ORWnd"
# PROP BASE Intermediate_Dir "fakemfc___Win32_Debug_Subclass_ORWnd"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "fakemfc___Win32_Debug_Subclass_ORWnd"
# PROP Intermediate_Dir "fakemfc___Win32_Debug_Subclass_ORWnd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "_AFXEXT" /D "MSWIND" /Yu"fakemfcp.hxx" /Fd".\fakeot.deb\fakemfcd.pdb" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "_AFXEXT" /D "MSWIND" /D "_SEC_SUBCLASS_ORWND" /Yu"fakemfcp.hxx" /Fd".\fakeot.deb\fakemfcd.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_SEC_CLASSES"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_SEC_CLASSES"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ospace5d.lib netapi32.lib largeint.lib /nologo /dll /incremental:no /debug /machine:I386 /out:".\fakeot.deb\fakemfcd.ext" /stub:"rights.exe" /subsystem:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ospace5d.lib netapi32.lib largeint.lib /nologo /dll /incremental:no /debug /machine:I386 /out:".\fakeot.deb\fakemfcd.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /stub:"rights.exe" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\fakeot.deb
TargetPath=.\fakeot.deb\fakemfcd.ext
TargetName=fakemfcd
InputPath=.\fakeot.deb\fakemfcd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetPath) $(TRIASDIR_D) 
	copy "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "fakemfc - Win32 Debug with OT"
# Name "fakemfc - Win32 Release with OT"
# Name "fakemfc - Win32 Debug Subclass ORWnd"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "Extension Source Files"

# PROP Default_Filter "*.cpp;*.cxx"
# Begin Source File

SOURCE=.\Cimpxtsn.cxx
# End Source File
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\CtfxmfcObsolete.cpp
# End Source File
# Begin Source File

SOURCE=.\Dummy2.cxx
# End Source File
# Begin Source File

SOURCE=.\Dummy3.cxx
# End Source File
# Begin Source File

SOURCE=.\Dummy4.cxx
# End Source File
# Begin Source File

SOURCE=.\Extreg.cxx
# End Source File
# Begin Source File

SOURCE=.\Fakemfcx.cxx
# ADD BASE CPP /Gi-
# ADD CPP /Gi-
# End Source File
# Begin Source File

SOURCE=.\Hdrentrx.cpp
# End Source File
# Begin Source File

SOURCE=.\Impxtcf.cxx
# End Source File
# Begin Source File

SOURCE=.\JumpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
# End Source File
# Begin Source File

SOURCE=.\triasext.cxx
# End Source File
# Begin Source File

SOURCE=.\Xtencunk.cxx
# End Source File
# End Group
# Begin Group "General Purpose Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\Debug.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dllbindx.cpp
# End Source File
# Begin Source File

SOURCE=.\dllfloat.cpp
# End Source File
# Begin Source File

SOURCE=.\Dtwinver.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\MsgHook.cpp
# End Source File
# Begin Source File

SOURCE=.\Propset.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\summary.cxx
# End Source File
# Begin Source File

SOURCE=.\Summinfo.cpp
# End Source File
# End Group
# Begin Group "User Interface Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\CoolControlManager.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\LicenseMsg.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\mfxWhlPan.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\PaintConnectionFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\SCROLTIP.CPP
# End Source File
# Begin Source File

SOURCE=.\Statpage.cpp
# End Source File
# Begin Source File

SOURCE=.\Summpage.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# ADD BASE CPP /Gi-
# ADD CPP /Gi-
# End Source File
# End Group
# Begin Group "Toolbar Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\AuxUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\Bildobj.cpp
# ADD BASE CPP /Yu"StdAfx.h"
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\CoordStaticsSec.cpp
# End Source File
# Begin Source File

SOURCE=.\DispUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatComboBox.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\MainUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\ManageTabWindow.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# ADD BASE CPP /Yu"StdAfx.h"
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\StatusProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarButton.cpp
# ADD BASE CPP /D "EBWIN32"
# ADD CPP /D "EBWIN32"
# End Source File
# Begin Source File

SOURCE=.\ToolBarManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolbarsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASBarCont.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASBarObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASButtonCont.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCmdUI.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCustomizeToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewComboBoxSec.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomComboBoxSec.cpp
# End Source File
# End Group
# Begin Group "TRiASDB Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "TRiASDB User Interface Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\CoolBtn.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\CreateConnectfilter.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateNewParamWiz.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CreateNewWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\DropMenuButton.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ManageConnectionFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\ManageConnections.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectAdvancedDlg.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OpenNewPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\SelectConnectionOpenNew.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectConnectionPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectConnectParams.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticFilespec.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CompareFileNames.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectedCtf.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleProject.cpp
# End Source File
# End Group
# Begin Group "Faking MFC Sources"

# PROP Default_Filter ""
# Begin Group "Print Preview Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\MappedBitmapButton.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASPreviewView.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ViewPrintPreview.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# ADD CPP /Yu"StdAfx.h"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# ADD BASE CPP /Gi-
# ADD CPP /Gi-
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDocTempl.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASView.cpp
# End Source File
# End Group
# Begin Group "Property Action Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PropertyChoice.cpp
# End Source File
# End Group
# Begin Group "Interface Definition"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\Toolbar.idl

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
InputDir=.
OutDir=.\fakeot.deb
InputPath=.\Toolbar.idl
InputName=Toolbar

BuildCmds= \
	echo $(InputDir)\$(InputName).idl \
	midl /win32 /tlb "$(OutDir)\$(InputName).tlb" /h  $(TRIASINCLUDE)\DToolBar.h /iid  "$(TRIASINCLUDE)\$(InputName)_i.c"  $(InputPath) \
	xcopy /F "$(OutDir)/$(InputName).tlb" $(TRIASTLB) \
	

"$(OutDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\DToolBar.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
OutDir=.\fakeot.rel
InputPath=.\Toolbar.idl
InputName=Toolbar

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /tlb "$(OutDir)/$(InputName).tlb" /h  "$(TRIASINCLUDE)\DToolBar.h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath) 
	xcopy /F "$(OutDir)/$(InputName).tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Idl\TRiASToolbars.idl
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Docking Tab Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "Project Value Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ProjectValueCategories.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\ProjectValues.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\ProjectValueStore.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\ResizableDialog.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\Docking3DTab.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Docking3DTabControl.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\DockingTabFrame.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\Fakemfc.def
# End Source File
# Begin Source File

SOURCE=.\Fakemfc.rc
# End Source File
# Begin Source File

SOURCE=.\Fakemfcp.cxx
# ADD BASE CPP /Yc"fakemfcp.hxx"
# ADD CPP /Yc"fakemfcp.hxx"
# End Source File
# Begin Source File

SOURCE=..\..\Trias\Tips\triastip.hdr
# End Source File
# Begin Source File

SOURCE=..\..\Trias\Tips\Triastip.tpl
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "Extension Header Files"

# PROP Default_Filter "*.h;*.hxx"
# Begin Source File

SOURCE=.\CIMPXTSN.HXX
# End Source File
# Begin Source File

SOURCE=.\DexCommands.h
# End Source File
# Begin Source File

SOURCE=.\Fakemfc.hxx
# End Source File
# Begin Source File

SOURCE=.\FakeMFCConfig.h
# End Source File
# Begin Source File

SOURCE=.\FakeMFCConfigVersion.h
# End Source File
# Begin Source File

SOURCE=.\fmfcguid.h
# End Source File
# Begin Source File

SOURCE=.\Impxtcf.hxx
# End Source File
# Begin Source File

SOURCE=.\InlineFuncs.h
# End Source File
# Begin Source File

SOURCE=.\JumpTable.h
# End Source File
# Begin Source File

SOURCE=.\OlePro32Wrap.h
# End Source File
# Begin Source File

SOURCE=.\PropPageExt.h
# End Source File
# Begin Source File

SOURCE=.\ThisDll.h
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBarCustomizePage.h
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBarPage.h
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "User Interface Headers"

# PROP Default_Filter "*.h;*.hxx"
# Begin Source File

SOURCE=.\CoolControlManager.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.h
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\LicenseMsg.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\PaintConnectionFilter.h
# End Source File
# Begin Source File

SOURCE=.\SCROLTIP.H
# End Source File
# Begin Source File

SOURCE=.\statpage.h
# End Source File
# Begin Source File

SOURCE=.\summpage.h
# End Source File
# Begin Source File

SOURCE=.\tipdlg.h
# End Source File
# End Group
# Begin Group "General Purpose Headers"

# PROP Default_Filter "*.h;*.hxx"
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\Dtwinver.h
# End Source File
# Begin Source File

SOURCE=.\mfxWhlPan.h
# End Source File
# Begin Source File

SOURCE=.\MsgHook.h
# End Source File
# Begin Source File

SOURCE=.\Propset.h
# End Source File
# Begin Source File

SOURCE=.\summary.hxx
# End Source File
# Begin Source File

SOURCE=.\summcf.hxx
# End Source File
# Begin Source File

SOURCE=.\Summinfo.h
# End Source File
# Begin Source File

SOURCE=.\Syncthrd.hxx
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Toolbar Headers"

# PROP Default_Filter "*.h;*.hxx"
# Begin Source File

SOURCE=.\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\CoordStaticsSec.h
# End Source File
# Begin Source File

SOURCE=.\DispUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\FlatComboBox.h
# End Source File
# Begin Source File

SOURCE=.\MainUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\ManageTabWindow.h
# End Source File
# Begin Source File

SOURCE=.\StatusProgress.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarButton.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarManager.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarsPage.h
# End Source File
# Begin Source File

SOURCE=.\TRiASBarCont.h
# End Source File
# Begin Source File

SOURCE=.\TRiASBarObj.h
# End Source File
# Begin Source File

SOURCE=.\TRiASButtonCont.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCmdUI.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCustomizeToolBar.h
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusObj.h
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBar.h
# End Source File
# Begin Source File

SOURCE=.\ViewComboBoxSec.h
# End Source File
# Begin Source File

SOURCE=.\ZoomComboBoxSec.h
# End Source File
# End Group
# Begin Group "Fake MFC Headers"

# PROP Default_Filter "*.h;*.hxx"
# Begin Group "Print Preview Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\MappedBitmapButton.h
# End Source File
# Begin Source File

SOURCE=.\TRiASPreviewView.h
# End Source File
# Begin Source File

SOURCE=.\ViewPrintPreview.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDoc.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDocTempl.h
# End Source File
# Begin Source File

SOURCE=.\triasview.h
# End Source File
# End Group
# Begin Group "TRiASDB Headers"

# PROP Default_Filter "*.h"
# Begin Group "TRiASDB User Interface Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\CoolBtn.h
# End Source File
# Begin Source File

SOURCE=.\CreateConnectfilter.h
# End Source File
# Begin Source File

SOURCE=.\CreateNewParamWiz.h
# End Source File
# Begin Source File

SOURCE=.\CreateNewWiz.h
# End Source File
# Begin Source File

SOURCE=.\DropMenuButton.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ManageConnectionFilters.h
# End Source File
# Begin Source File

SOURCE=.\ManageConnections.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectAdvancedDlg.h
# End Source File
# Begin Source File

SOURCE=.\OpenNewPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\SelectConnectionOpenNew.h
# End Source File
# Begin Source File

SOURCE=.\SelectConnectionPage.h
# End Source File
# Begin Source File

SOURCE=.\SelectConnectParams.h
# End Source File
# Begin Source File

SOURCE=.\StaticFilespec.h
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ConnectedCtf.h
# End Source File
# Begin Source File

SOURCE=.\ConnectParams.h
# End Source File
# Begin Source File

SOURCE=.\CoordSysKeys.h
# End Source File
# End Group
# Begin Group "Property Action Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\PropActBase.h
# End Source File
# Begin Source File

SOURCE=.\propertychoice.h
# End Source File
# End Group
# Begin Group "Docking Tab Headers"

# PROP Default_Filter "*.h"
# Begin Group "Project Value Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ProjectValueCategories.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValues.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValueStore.h
# End Source File
# Begin Source File

SOURCE=.\ResizableDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Docking3DTab.h
# End Source File
# Begin Source File

SOURCE=.\Docking3DTabControl.h
# End Source File
# Begin Source File

SOURCE=.\DockingTabFrame.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\fakemfc.hm
# End Source File
# Begin Source File

SOURCE=.\Fakemfcp.hxx
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Toolbar Buttons"

# PROP Default_Filter "*.bmp"
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ConnectFilter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ConnectFilterDlg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ConnectFilterDlgMask.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Copy of Toolneu1.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\dataserv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DataServerMask.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\downdis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\downfoc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\downsel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fullscrn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoclass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoobjec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\macrobtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\objoper.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev_con.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev_rep.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PrevEnd.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PreviewHome.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PreviewNext.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PreviewOne.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PreviewTwo.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PrevPrevious.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PrevPrint.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PrevZoomin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PrevZoomout.BMP
# End Source File
# Begin Source File

SOURCE=.\res\standard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tool1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool23.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool25.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool26.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool27.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool28.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool29.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool30.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool31.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool33.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool34.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool35.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool36.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool37.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool38.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool39.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool40.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool41.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool42.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool43.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool44.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool45.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool46.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool47.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool48.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool49.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool50.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool51.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool52.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool53.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool54.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool55.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool56.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool57.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool58.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool59.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tools.bmp
# End Source File
# End Group
# Begin Group "Icons"

# PROP Default_Filter "*.ico"
# Begin Source File

SOURCE=.\res\dataimpo.ico
# End Source File
# Begin Source File

SOURCE=.\Docbuch.ico
# End Source File
# Begin Source File

SOURCE=.\res\document.ico
# End Source File
# Begin Source File

SOURCE=.\res\documentnew.ico
# End Source File
# Begin Source File

SOURCE=.\res\editnew.ico
# End Source File
# Begin Source File

SOURCE=.\res\fakemfc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\idc_newp.ico
# End Source File
# Begin Source File

SOURCE=.\idc_open.ico
# End Source File
# Begin Source File

SOURCE=..\..\Trias\obj32\license.ico
# End Source File
# Begin Source File

SOURCE=.\res\license.ico
# End Source File
# Begin Source File

SOURCE=.\res\PrintPreview.ico
# End Source File
# Begin Source File

SOURCE=.\res\Statistics.ico
# End Source File
# End Group
# Begin Group "Cursors"

# PROP Default_Filter "*.cur"
# Begin Source File

SOURCE=.\cross_m.cur
# End Source File
# Begin Source File

SOURCE=.\res\cross_m.cur
# End Source File
# Begin Source File

SOURCE=.\res\horzdrag.cur
# End Source File
# Begin Source File

SOURCE=.\res\pan_all.cur
# End Source File
# Begin Source File

SOURCE=.\res\pan_down.cur
# End Source File
# Begin Source File

SOURCE=.\res\pan_left.cur
# End Source File
# Begin Source File

SOURCE=.\res\pan_right.cur
# End Source File
# Begin Source File

SOURCE=.\res\pan_up.cur
# End Source File
# Begin Source File

SOURCE=.\res\SplitH.cur
# End Source File
# Begin Source File

SOURCE=.\res\SplitV.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\autopan.bmp
# End Source File
# Begin Source File

SOURCE=.\FAKEMFC.RCV
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SteckBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\fakeot.deb\Toolbar.tlb
# End Source File
# Begin Source File

SOURCE=.\fakeot.rel\Toolbar.tlb
# End Source File
# Begin Source File

SOURCE=.\res\Topkarte.bmp
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\FAKEMFC.TPL

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

USERDEP__FAKEM="makefile"	
# Begin Custom Build - Generating module definition file ...
InputPath=.\FAKEMFC.TPL

"fakemfc.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.def

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

USERDEP__FAKEM="makefile"	
# Begin Custom Build - Generating module definition file ...
InputPath=.\FAKEMFC.TPL

"fakemfc.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.def

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

USERDEP__FAKEM="makefile"	
# Begin Custom Build - Generating module definition file ...
InputPath=.\FAKEMFC.TPL

"fakemfc.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FAKEMFCV.TPL

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

USERDEP__FAKEMF="makefile"	
# Begin Custom Build - Generating version strings ...
InputPath=.\FAKEMFCV.TPL

"fakemfc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

USERDEP__FAKEMF="makefile"	
# Begin Custom Build - Generating version strings ...
InputPath=.\FAKEMFCV.TPL

"fakemfc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

USERDEP__FAKEMF="makefile"	
# Begin Custom Build - Generating version strings ...
InputPath=.\FAKEMFCV.TPL

"fakemfc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo fakemfc.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

USERDEP__VERSI="makefile"	
# Begin Custom Build - Generating version numbers ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

USERDEP__VERSI="makefile"	
# Begin Custom Build - Generating version numbers ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug Subclass ORWnd"

USERDEP__VERSI="makefile"	
# Begin Custom Build - Generating version numbers ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\ManageTabWindow.rgs
# End Source File
# Begin Source File

SOURCE=.\res\PropertyChoice.rgs
# End Source File
# Begin Source File

SOURCE=.\res\StatusProgress.rgs
# End Source File
# Begin Source File

SOURCE=.\res\ToolBarButton.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASBarObj.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASButtonCont.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASToolBarCustomizePage.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASToolBarPage.rgs
# End Source File
# End Group
# End Target
# End Project
# Section fakemfc : {AC9258A4-3558-11CF-BA55-00AA0018497C}
# 	0:8:TipDlg.h:E:\Triasdev.mvc\Xtension\Fakemfc\TipDlg.h
# 	0:10:TipDlg.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\TipDlg.cpp
# 	1:17:CG_IDS_DIDYOUKNOW:106
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:105
# 	1:18:CG_IDS_TIPOFTHEDAY:104
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:109
# 	1:19:CG_IDP_FILE_CORRUPT:108
# 	1:7:IDD_TIP:103
# 	1:13:IDB_LIGHTBULB:102
# 	1:18:CG_IDS_FILE_ABSENT:107
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
# Section fakemfc : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:26:CG_IDR_POPUP_TRIASTOOL_BAR:22115
# End Section
# Section OLE Controls
# 	{16E349E0-702C-11CF-A3A9-00A0C9034920}
# End Section
# Section fakemfc : {2DCC3987-AA53-11CF-BA69-00AA0018497C}
# 	0:14:EnumToolBars.h:E:\Triasdev.mvc\Xtension\Fakemfc\EnumToolBars.h
# 	0:16:EnumToolBars.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\EnumToolBars.cpp
# 	2:14:EnumToolBars.h:EnumToolBars.h
# 	2:20:CLASS: CEnumToolBars:CEnumToolBars
# 	2:19:Application Include:fakemfc.h
# 	2:16:EnumToolBars.cpp:EnumToolBars.cpp
# End Section
# Section fakemfc : {16E349E0-702C-11CF-A3A9-00A0C9034920}
# 	0:11:PreLoader.h:E:\Triasdev.mvc\Xtension\Fakemfc\PreLoader.h
# 	0:13:PreLoader.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\PreLoader.cpp
# 	2:21:DefaultSinkHeaderFile:preloader.h
# 	2:16:DefaultSinkClass:CPreLoader
# End Section
# Section fakemfc : {146EA060-702C-11CF-A3A9-00A0C9034920}
# 	2:5:Class:CPreLoader
# 	2:10:HeaderFile:preloader.h
# 	2:8:ImplFile:preloader.cpp
# End Section
