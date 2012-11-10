# Microsoft Developer Studio Generated NMAKE File, Based on Fakemfc.dsp
!IF "$(CFG)" == ""
CFG=fakemfc - Win32 Debug with OT
!MESSAGE No configuration specified. Defaulting to fakemfc - Win32 Debug with\
 OT.
!ENDIF 

!IF "$(CFG)" != "fakemfc - Win32 Debug with OT" && "$(CFG)" !=\
 "fakemfc - Win32 Release with OT"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fakemfc.mak" CFG="fakemfc - Win32 Debug with OT"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fakemfc - Win32 Debug with OT" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fakemfc - Win32 Release with OT" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

OUTDIR=.\fakeot.deb
INTDIR=.\fakeot.deb
# Begin Custom Macros
OutDir=.\.\fakeot.deb
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "rights.exe" "e:\triasdev.mvc\include\DToolBar.h"\
 "e:\triasdev.mvc\include\$(InputName)_i.c" "$(OutDir)/$(InputName).tlb"\
 "$(OUTDIR)\fakemfcd.ext" "$(OUTDIR)\Fakemfc.bsc"

!ELSE 

ALL : "rights.exe" "e:\triasdev.mvc\include\DToolBar.h"\
 "e:\triasdev.mvc\include\$(InputName)_i.c" "$(OutDir)/$(InputName).tlb"\
 "$(OUTDIR)\fakemfcd.ext" "$(OUTDIR)\Fakemfc.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\AuxUIOwner.sbr"
	-@erase "$(INTDIR)\Bildobj.obj"
	-@erase "$(INTDIR)\Bildobj.sbr"
	-@erase "$(INTDIR)\Cimpxtsn.obj"
	-@erase "$(INTDIR)\Cimpxtsn.sbr"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\CntrItem.sbr"
	-@erase "$(INTDIR)\ConnectedCtf.obj"
	-@erase "$(INTDIR)\ConnectedCtf.sbr"
	-@erase "$(INTDIR)\CoordStaticsSec.obj"
	-@erase "$(INTDIR)\CoordStaticsSec.sbr"
	-@erase "$(INTDIR)\CreateNewParamWiz.obj"
	-@erase "$(INTDIR)\CreateNewParamWiz.sbr"
	-@erase "$(INTDIR)\CreateNewWiz.obj"
	-@erase "$(INTDIR)\CreateNewWiz.sbr"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\DDXGetFile.obj"
	-@erase "$(INTDIR)\DDXGetFile.sbr"
	-@erase "$(INTDIR)\DDXGetFolder.obj"
	-@erase "$(INTDIR)\DDXGetFolder.sbr"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\DispUIOwner.obj"
	-@erase "$(INTDIR)\DispUIOwner.sbr"
	-@erase "$(INTDIR)\Dlgdir.obj"
	-@erase "$(INTDIR)\Dlgdir.sbr"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dllbindx.sbr"
	-@erase "$(INTDIR)\dllfloat.obj"
	-@erase "$(INTDIR)\dllfloat.sbr"
	-@erase "$(INTDIR)\Dummy2.obj"
	-@erase "$(INTDIR)\Dummy2.sbr"
	-@erase "$(INTDIR)\Dummy3.obj"
	-@erase "$(INTDIR)\Dummy3.sbr"
	-@erase "$(INTDIR)\Dummy4.obj"
	-@erase "$(INTDIR)\Dummy4.sbr"
	-@erase "$(INTDIR)\Extreg.obj"
	-@erase "$(INTDIR)\Extreg.sbr"
	-@erase "$(INTDIR)\Fakemfc.pch"
	-@erase "$(INTDIR)\Fakemfc.res"
	-@erase "$(INTDIR)\fakemfcd.idb"
	-@erase "$(INTDIR)\Fakemfcp.obj"
	-@erase "$(INTDIR)\Fakemfcp.sbr"
	-@erase "$(INTDIR)\Fakemfcx.obj"
	-@erase "$(INTDIR)\Fakemfcx.sbr"
	-@erase "$(INTDIR)\HandleProject.obj"
	-@erase "$(INTDIR)\HandleProject.sbr"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\Hdrentrx.sbr"
	-@erase "$(INTDIR)\Impxtcf.obj"
	-@erase "$(INTDIR)\Impxtcf.sbr"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ListCtrlEx.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MainUIOwner.obj"
	-@erase "$(INTDIR)\MainUIOwner.sbr"
	-@erase "$(INTDIR)\ManageConnections.obj"
	-@erase "$(INTDIR)\ManageConnections.sbr"
	-@erase "$(INTDIR)\MsgHook.obj"
	-@erase "$(INTDIR)\MsgHook.sbr"
	-@erase "$(INTDIR)\NewProjectAdvancedDlg.obj"
	-@erase "$(INTDIR)\NewProjectAdvancedDlg.sbr"
	-@erase "$(INTDIR)\OpenNewPropertySheet.obj"
	-@erase "$(INTDIR)\OpenNewPropertySheet.sbr"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\Picture.sbr"
	-@erase "$(INTDIR)\PropActBase.obj"
	-@erase "$(INTDIR)\PropActBase.sbr"
	-@erase "$(INTDIR)\PropertyChoice.obj"
	-@erase "$(INTDIR)\PropertyChoice.sbr"
	-@erase "$(INTDIR)\Propset.obj"
	-@erase "$(INTDIR)\Propset.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\SCROLTIP.OBJ"
	-@erase "$(INTDIR)\SCROLTIP.SBR"
	-@erase "$(INTDIR)\SelectConnectionOpenNew.obj"
	-@erase "$(INTDIR)\SelectConnectionOpenNew.sbr"
	-@erase "$(INTDIR)\SelectConnectionPage.obj"
	-@erase "$(INTDIR)\SelectConnectionPage.sbr"
	-@erase "$(INTDIR)\SelectConnectParams.obj"
	-@erase "$(INTDIR)\SelectConnectParams.sbr"
	-@erase "$(INTDIR)\SrvrItem.obj"
	-@erase "$(INTDIR)\SrvrItem.sbr"
	-@erase "$(INTDIR)\Statpage.obj"
	-@erase "$(INTDIR)\Statpage.sbr"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\summary.obj"
	-@erase "$(INTDIR)\summary.sbr"
	-@erase "$(INTDIR)\Summinfo.obj"
	-@erase "$(INTDIR)\Summinfo.sbr"
	-@erase "$(INTDIR)\Summpage.obj"
	-@erase "$(INTDIR)\Summpage.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\ToolBarButton.obj"
	-@erase "$(INTDIR)\ToolBarButton.sbr"
	-@erase "$(INTDIR)\ToolBarManager.obj"
	-@erase "$(INTDIR)\ToolBarManager.sbr"
	-@erase "$(INTDIR)\ToolbarsDlg.obj"
	-@erase "$(INTDIR)\ToolbarsDlg.sbr"
	-@erase "$(INTDIR)\TRiASBarCont.obj"
	-@erase "$(INTDIR)\TRiASBarCont.sbr"
	-@erase "$(INTDIR)\TRiASBarObj.obj"
	-@erase "$(INTDIR)\TRiASBarObj.sbr"
	-@erase "$(INTDIR)\TRiASButtonCont.obj"
	-@erase "$(INTDIR)\TRiASButtonCont.sbr"
	-@erase "$(INTDIR)\TRiASCmdUI.obj"
	-@erase "$(INTDIR)\TRiASCmdUI.sbr"
	-@erase "$(INTDIR)\TRiASDoc.obj"
	-@erase "$(INTDIR)\TRiASDoc.sbr"
	-@erase "$(INTDIR)\TRiASDocTempl.obj"
	-@erase "$(INTDIR)\TRiASDocTempl.sbr"
	-@erase "$(INTDIR)\triasext.obj"
	-@erase "$(INTDIR)\triasext.sbr"
	-@erase "$(INTDIR)\TRiASStatusBar.obj"
	-@erase "$(INTDIR)\TRiASStatusBar.sbr"
	-@erase "$(INTDIR)\TRiASStatusObj.obj"
	-@erase "$(INTDIR)\TRiASStatusObj.sbr"
	-@erase "$(INTDIR)\TRiASToolBar.obj"
	-@erase "$(INTDIR)\TRiASToolBar.sbr"
	-@erase "$(INTDIR)\TRiASView.obj"
	-@erase "$(INTDIR)\TRiASView.sbr"
	-@erase "$(INTDIR)\ViewComboBoxSec.obj"
	-@erase "$(INTDIR)\ViewComboBoxSec.sbr"
	-@erase "$(INTDIR)\WelcomePage.obj"
	-@erase "$(INTDIR)\WelcomePage.sbr"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\Xtencunk.sbr"
	-@erase "$(INTDIR)\ZoomComboBoxSec.obj"
	-@erase "$(INTDIR)\ZoomComboBoxSec.sbr"
	-@erase "$(OUTDIR)\Fakemfc.bsc"
	-@erase "$(OUTDIR)\fakemfcd.exp"
	-@erase "$(OUTDIR)\fakemfcd.ext"
	-@erase "$(OUTDIR)\fakemfcd.ilk"
	-@erase "$(OUTDIR)\fakemfcd.lib"
	-@erase "$(OUTDIR)\fakemfcd.pdb"
	-@erase "$(OutDir)/$(InputName).tlb"
	-@erase "e:\triasdev.mvc\include\$(InputName)_i.c"
	-@erase "e:\triasdev.mvc\include\DToolBar.h"
	-@erase "rights.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL" /D\
 "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 
CPP_OBJS=.\fakeot.deb/
CPP_SBRS=.\fakeot.deb/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Fakemfc.res" /d "_DEBUG" /d "_AFXDLL" /d\
 "_USE_SEC_CLASSES" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Fakemfc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AuxUIOwner.sbr" \
	"$(INTDIR)\Bildobj.sbr" \
	"$(INTDIR)\Cimpxtsn.sbr" \
	"$(INTDIR)\CntrItem.sbr" \
	"$(INTDIR)\ConnectedCtf.sbr" \
	"$(INTDIR)\CoordStaticsSec.sbr" \
	"$(INTDIR)\CreateNewParamWiz.sbr" \
	"$(INTDIR)\CreateNewWiz.sbr" \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\DDXGetFile.sbr" \
	"$(INTDIR)\DDXGetFolder.sbr" \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\DispUIOwner.sbr" \
	"$(INTDIR)\Dlgdir.sbr" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dllfloat.sbr" \
	"$(INTDIR)\Dummy2.sbr" \
	"$(INTDIR)\Dummy3.sbr" \
	"$(INTDIR)\Dummy4.sbr" \
	"$(INTDIR)\Extreg.sbr" \
	"$(INTDIR)\Fakemfcp.sbr" \
	"$(INTDIR)\Fakemfcx.sbr" \
	"$(INTDIR)\HandleProject.sbr" \
	"$(INTDIR)\Hdrentrx.sbr" \
	"$(INTDIR)\Impxtcf.sbr" \
	"$(INTDIR)\ListCtrlEx.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MainUIOwner.sbr" \
	"$(INTDIR)\ManageConnections.sbr" \
	"$(INTDIR)\MsgHook.sbr" \
	"$(INTDIR)\NewProjectAdvancedDlg.sbr" \
	"$(INTDIR)\OpenNewPropertySheet.sbr" \
	"$(INTDIR)\Picture.sbr" \
	"$(INTDIR)\PropActBase.sbr" \
	"$(INTDIR)\PropertyChoice.sbr" \
	"$(INTDIR)\Propset.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\SCROLTIP.SBR" \
	"$(INTDIR)\SelectConnectionOpenNew.sbr" \
	"$(INTDIR)\SelectConnectionPage.sbr" \
	"$(INTDIR)\SelectConnectParams.sbr" \
	"$(INTDIR)\SrvrItem.sbr" \
	"$(INTDIR)\Statpage.sbr" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\summary.sbr" \
	"$(INTDIR)\Summinfo.sbr" \
	"$(INTDIR)\Summpage.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\ToolBarButton.sbr" \
	"$(INTDIR)\ToolBarManager.sbr" \
	"$(INTDIR)\ToolbarsDlg.sbr" \
	"$(INTDIR)\TRiASBarCont.sbr" \
	"$(INTDIR)\TRiASBarObj.sbr" \
	"$(INTDIR)\TRiASButtonCont.sbr" \
	"$(INTDIR)\TRiASCmdUI.sbr" \
	"$(INTDIR)\TRiASDoc.sbr" \
	"$(INTDIR)\TRiASDocTempl.sbr" \
	"$(INTDIR)\triasext.sbr" \
	"$(INTDIR)\TRiASStatusBar.sbr" \
	"$(INTDIR)\TRiASStatusObj.sbr" \
	"$(INTDIR)\TRiASToolBar.sbr" \
	"$(INTDIR)\TRiASView.sbr" \
	"$(INTDIR)\ViewComboBoxSec.sbr" \
	"$(INTDIR)\WelcomePage.sbr" \
	"$(INTDIR)\Xtencunk.sbr" \
	"$(INTDIR)\ZoomComboBoxSec.sbr"

"$(OUTDIR)\Fakemfc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=triastld.lib ot51asd.lib ospace5d.lib netapi32.lib largeint.lib\
 /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\fakemfcd.pdb" /debug\
 /machine:I386 /def:".\Fakemfc.def" /out:"$(OUTDIR)\fakemfcd.ext"\
 /implib:"$(OUTDIR)\fakemfcd.lib" /stub:"rights.exe" /subsystem:windows,4.0 
DEF_FILE= \
	".\Fakemfc.def"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\Bildobj.obj" \
	"$(INTDIR)\Cimpxtsn.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\ConnectedCtf.obj" \
	"$(INTDIR)\CoordStaticsSec.obj" \
	"$(INTDIR)\CreateNewParamWiz.obj" \
	"$(INTDIR)\CreateNewWiz.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DDXGetFile.obj" \
	"$(INTDIR)\DDXGetFolder.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\DispUIOwner.obj" \
	"$(INTDIR)\Dlgdir.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dllfloat.obj" \
	"$(INTDIR)\Dummy2.obj" \
	"$(INTDIR)\Dummy3.obj" \
	"$(INTDIR)\Dummy4.obj" \
	"$(INTDIR)\Extreg.obj" \
	"$(INTDIR)\Fakemfc.res" \
	"$(INTDIR)\Fakemfcp.obj" \
	"$(INTDIR)\Fakemfcx.obj" \
	"$(INTDIR)\HandleProject.obj" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\Impxtcf.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MainUIOwner.obj" \
	"$(INTDIR)\ManageConnections.obj" \
	"$(INTDIR)\MsgHook.obj" \
	"$(INTDIR)\NewProjectAdvancedDlg.obj" \
	"$(INTDIR)\OpenNewPropertySheet.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\PropActBase.obj" \
	"$(INTDIR)\PropertyChoice.obj" \
	"$(INTDIR)\Propset.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\SCROLTIP.OBJ" \
	"$(INTDIR)\SelectConnectionOpenNew.obj" \
	"$(INTDIR)\SelectConnectionPage.obj" \
	"$(INTDIR)\SelectConnectParams.obj" \
	"$(INTDIR)\SrvrItem.obj" \
	"$(INTDIR)\Statpage.obj" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\summary.obj" \
	"$(INTDIR)\Summinfo.obj" \
	"$(INTDIR)\Summpage.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\ToolBarButton.obj" \
	"$(INTDIR)\ToolBarManager.obj" \
	"$(INTDIR)\ToolbarsDlg.obj" \
	"$(INTDIR)\TRiASBarCont.obj" \
	"$(INTDIR)\TRiASBarObj.obj" \
	"$(INTDIR)\TRiASButtonCont.obj" \
	"$(INTDIR)\TRiASCmdUI.obj" \
	"$(INTDIR)\TRiASDoc.obj" \
	"$(INTDIR)\TRiASDocTempl.obj" \
	"$(INTDIR)\triasext.obj" \
	"$(INTDIR)\TRiASStatusBar.obj" \
	"$(INTDIR)\TRiASStatusObj.obj" \
	"$(INTDIR)\TRiASToolBar.obj" \
	"$(INTDIR)\TRiASView.obj" \
	"$(INTDIR)\ViewComboBoxSec.obj" \
	"$(INTDIR)\WelcomePage.obj" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\ZoomComboBoxSec.obj"

"$(OUTDIR)\fakemfcd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\fakeot.deb\fakemfcd.ext
SOURCE=$(InputPath)
PostBuild_Desc=Copying target to destination ...
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\.\fakeot.deb
# End Custom Macros

$(DS_POSTBUILD_DEP) : "rights.exe" "e:\triasdev.mvc\include\DToolBar.h"\
 "e:\triasdev.mvc\include\$(InputName)_i.c" "$(OutDir)/$(InputName).tlb"\
 "$(OUTDIR)\fakemfcd.ext" "$(OUTDIR)\Fakemfc.bsc"
   copy ".\fakeot.deb\fakemfcd.ext" c:\trias.mvc\trias200
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

OUTDIR=.\fakeot.rel
INTDIR=.\fakeot.rel
# Begin Custom Macros
OutDir=.\.\fakeot.rel
TargetName=fakemfc
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "rights.exe" "e:\triasdev.mvc\include\DToolBar.h"\
 "e:\triasdev.mvc\include\$(InputName)_i.c" "$(OutDir)/$(InputName).tlb"\
 "$(OUTDIR)\fakemfc.ext" "c:\trias.mvc\trias200.rel\$(TargetName).ext"

!ELSE 

ALL : "rights.exe" "e:\triasdev.mvc\include\DToolBar.h"\
 "e:\triasdev.mvc\include\$(InputName)_i.c" "$(OutDir)/$(InputName).tlb"\
 "$(OUTDIR)\fakemfc.ext" "c:\trias.mvc\trias200.rel\$(TargetName).ext"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\Bildobj.obj"
	-@erase "$(INTDIR)\Cimpxtsn.obj"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\ConnectedCtf.obj"
	-@erase "$(INTDIR)\CoordStaticsSec.obj"
	-@erase "$(INTDIR)\CreateNewParamWiz.obj"
	-@erase "$(INTDIR)\CreateNewWiz.obj"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\DDXGetFile.obj"
	-@erase "$(INTDIR)\DDXGetFolder.obj"
	-@erase "$(INTDIR)\DispUIOwner.obj"
	-@erase "$(INTDIR)\Dlgdir.obj"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dllfloat.obj"
	-@erase "$(INTDIR)\Dummy2.obj"
	-@erase "$(INTDIR)\Dummy3.obj"
	-@erase "$(INTDIR)\Dummy4.obj"
	-@erase "$(INTDIR)\Extreg.obj"
	-@erase "$(INTDIR)\Fakemfc.pch"
	-@erase "$(INTDIR)\Fakemfc.res"
	-@erase "$(INTDIR)\Fakemfcp.obj"
	-@erase "$(INTDIR)\Fakemfcx.obj"
	-@erase "$(INTDIR)\HandleProject.obj"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\Impxtcf.obj"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainUIOwner.obj"
	-@erase "$(INTDIR)\ManageConnections.obj"
	-@erase "$(INTDIR)\MsgHook.obj"
	-@erase "$(INTDIR)\NewProjectAdvancedDlg.obj"
	-@erase "$(INTDIR)\OpenNewPropertySheet.obj"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\PropActBase.obj"
	-@erase "$(INTDIR)\PropertyChoice.obj"
	-@erase "$(INTDIR)\Propset.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\SCROLTIP.OBJ"
	-@erase "$(INTDIR)\SelectConnectionOpenNew.obj"
	-@erase "$(INTDIR)\SelectConnectionPage.obj"
	-@erase "$(INTDIR)\SelectConnectParams.obj"
	-@erase "$(INTDIR)\SrvrItem.obj"
	-@erase "$(INTDIR)\Statpage.obj"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\summary.obj"
	-@erase "$(INTDIR)\Summinfo.obj"
	-@erase "$(INTDIR)\Summpage.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\ToolBarButton.obj"
	-@erase "$(INTDIR)\ToolBarManager.obj"
	-@erase "$(INTDIR)\ToolbarsDlg.obj"
	-@erase "$(INTDIR)\TRiASBarCont.obj"
	-@erase "$(INTDIR)\TRiASBarObj.obj"
	-@erase "$(INTDIR)\TRiASButtonCont.obj"
	-@erase "$(INTDIR)\TRiASCmdUI.obj"
	-@erase "$(INTDIR)\TRiASDoc.obj"
	-@erase "$(INTDIR)\TRiASDocTempl.obj"
	-@erase "$(INTDIR)\triasext.obj"
	-@erase "$(INTDIR)\TRiASStatusBar.obj"
	-@erase "$(INTDIR)\TRiASStatusObj.obj"
	-@erase "$(INTDIR)\TRiASToolBar.obj"
	-@erase "$(INTDIR)\TRiASView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\ViewComboBoxSec.obj"
	-@erase "$(INTDIR)\WelcomePage.obj"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\ZoomComboBoxSec.obj"
	-@erase "$(OUTDIR)\fakemfc.exp"
	-@erase "$(OUTDIR)\fakemfc.ext"
	-@erase "$(OUTDIR)\fakemfc.lib"
	-@erase "$(OutDir)/$(InputName).tlb"
	-@erase "c:\trias.mvc\trias200.rel\$(TargetName).ext"
	-@erase "e:\triasdev.mvc\include\$(InputName)_i.c"
	-@erase "e:\triasdev.mvc\include\DToolBar.h"
	-@erase "rights.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\fakeot.rel/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Fakemfc.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "_USE_SEC_CLASSES" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Fakemfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=triastlb.lib ot5050r.lib ospace5r.lib netapi32.lib largeint.lib\
 /nologo /dll /incremental:no /pdb:"$(OUTDIR)\fakemfc.pdb" /machine:I386\
 /def:".\Fakemfc.def" /out:"$(OUTDIR)\fakemfc.ext"\
 /implib:"$(OUTDIR)\fakemfc.lib" /stub:"rights.exe" /subsystem:windows,4.0 
DEF_FILE= \
	".\Fakemfc.def"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\Bildobj.obj" \
	"$(INTDIR)\Cimpxtsn.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\ConnectedCtf.obj" \
	"$(INTDIR)\CoordStaticsSec.obj" \
	"$(INTDIR)\CreateNewParamWiz.obj" \
	"$(INTDIR)\CreateNewWiz.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DDXGetFile.obj" \
	"$(INTDIR)\DDXGetFolder.obj" \
	"$(INTDIR)\DispUIOwner.obj" \
	"$(INTDIR)\Dlgdir.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dllfloat.obj" \
	"$(INTDIR)\Dummy2.obj" \
	"$(INTDIR)\Dummy3.obj" \
	"$(INTDIR)\Dummy4.obj" \
	"$(INTDIR)\Extreg.obj" \
	"$(INTDIR)\Fakemfc.res" \
	"$(INTDIR)\Fakemfcp.obj" \
	"$(INTDIR)\Fakemfcx.obj" \
	"$(INTDIR)\HandleProject.obj" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\Impxtcf.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MainUIOwner.obj" \
	"$(INTDIR)\ManageConnections.obj" \
	"$(INTDIR)\MsgHook.obj" \
	"$(INTDIR)\NewProjectAdvancedDlg.obj" \
	"$(INTDIR)\OpenNewPropertySheet.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\PropActBase.obj" \
	"$(INTDIR)\PropertyChoice.obj" \
	"$(INTDIR)\Propset.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\SCROLTIP.OBJ" \
	"$(INTDIR)\SelectConnectionOpenNew.obj" \
	"$(INTDIR)\SelectConnectionPage.obj" \
	"$(INTDIR)\SelectConnectParams.obj" \
	"$(INTDIR)\SrvrItem.obj" \
	"$(INTDIR)\Statpage.obj" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\summary.obj" \
	"$(INTDIR)\Summinfo.obj" \
	"$(INTDIR)\Summpage.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\ToolBarButton.obj" \
	"$(INTDIR)\ToolBarManager.obj" \
	"$(INTDIR)\ToolbarsDlg.obj" \
	"$(INTDIR)\TRiASBarCont.obj" \
	"$(INTDIR)\TRiASBarObj.obj" \
	"$(INTDIR)\TRiASButtonCont.obj" \
	"$(INTDIR)\TRiASCmdUI.obj" \
	"$(INTDIR)\TRiASDoc.obj" \
	"$(INTDIR)\TRiASDocTempl.obj" \
	"$(INTDIR)\triasext.obj" \
	"$(INTDIR)\TRiASStatusBar.obj" \
	"$(INTDIR)\TRiASStatusObj.obj" \
	"$(INTDIR)\TRiASToolBar.obj" \
	"$(INTDIR)\TRiASView.obj" \
	"$(INTDIR)\ViewComboBoxSec.obj" \
	"$(INTDIR)\WelcomePage.obj" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\ZoomComboBoxSec.obj"

"$(OUTDIR)\fakemfc.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\fakeot.rel\fakemfc.ext
TargetName=fakemfc
InputPath=.\fakeot.rel\fakemfc.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	copy "$(TargetPath)" c:\trias.mvc\trias200.rel

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "fakemfc - Win32 Debug with OT" || "$(CFG)" ==\
 "fakemfc - Win32 Release with OT"
SOURCE=.\AuxUIOwner.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_AUXUI=\
	".\AuxUIOwner.h"\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\AuxUIOwner.obj"	"$(INTDIR)\AuxUIOwner.sbr" : $(SOURCE)\
 $(DEP_CPP_AUXUI) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_AUXUI=\
	".\AuxUIOwner.h"\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
NODEP_CPP_AUXUI=\
	".\CoordStatics.h"\
	".\ZoomComboBox.h"\
	

"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Bildobj.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_BILDO=\
	{$(INCLUDE)}"bildobj.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL"\
 /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32"\
 /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"StdAfx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\Bildobj.obj"	"$(INTDIR)\Bildobj.sbr" : $(SOURCE) $(DEP_CPP_BILDO)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_BILDO=\
	".\Fakemfcp.hxx"\
	".\stdafx.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bildobj.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT"\
 /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\Bildobj.obj" : $(SOURCE) $(DEP_CPP_BILDO) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Cimpxtsn.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CIMPX=\
	".\CIMPXTSN.HXX"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Cimpxtsn.obj"	"$(INTDIR)\Cimpxtsn.sbr" : $(SOURCE) $(DEP_CPP_CIMPX)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CIMPX=\
	".\CIMPXTSN.HXX"\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CNTRI=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\SCROLTIP.H"\
	".\TRiASDoc.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\CntrItem.obj"	"$(INTDIR)\CntrItem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CNTRI=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\Fakemfcp.hxx"\
	".\SCROLTIP.H"\
	".\TRiASDoc.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\CntrItem.obj" : $(SOURCE) $(DEP_CPP_CNTRI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ConnectedCtf.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CONNE=\
	".\ConnectedCtf.h"\
	".\Strings.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\ConnectedCtf.obj"	"$(INTDIR)\ConnectedCtf.sbr" : $(SOURCE)\
 $(DEP_CPP_CONNE) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CONNE=\
	".\ConnectedCtf.h"\
	".\Fakemfcp.hxx"\
	".\Strings.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ConnectedCtf.obj" : $(SOURCE) $(DEP_CPP_CONNE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\CoordStaticsSec.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_COORD=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\CoordStaticsSec.obj"	"$(INTDIR)\CoordStaticsSec.sbr" : $(SOURCE)\
 $(DEP_CPP_COORD) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_COORD=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\CoordStaticsSec.obj" : $(SOURCE) $(DEP_CPP_COORD) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\CreateNewParamWiz.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CREAT=\
	".\ConnectParams.h"\
	".\CreateNewParamWiz.h"\
	".\NewProjectAdvancedDlg.h"\
	".\OpenNewPropertySheet.h"\
	".\Strings.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\CreateNewParamWiz.obj"	"$(INTDIR)\CreateNewParamWiz.sbr" : $(SOURCE)\
 $(DEP_CPP_CREAT) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CREAT=\
	".\ConnectParams.h"\
	".\CreateNewParamWiz.h"\
	".\Fakemfcp.hxx"\
	".\NewProjectAdvancedDlg.h"\
	".\OpenNewPropertySheet.h"\
	".\Strings.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\CreateNewParamWiz.obj" : $(SOURCE) $(DEP_CPP_CREAT) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\CreateNewWiz.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CREATE=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CreateNewParamWiz.h"\
	".\CreateNewWiz.h"\
	".\DDXGetFile.h"\
	".\DDXGetFolder.h"\
	".\Fakemfc.hxx"\
	".\fmfcguid.h"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\SelectConnectionOpenNew.h"\
	".\SelectConnectionPage.h"\
	".\SelectConnectParams.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\WelcomePage.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	

"$(INTDIR)\CreateNewWiz.obj"	"$(INTDIR)\CreateNewWiz.sbr" : $(SOURCE)\
 $(DEP_CPP_CREATE) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CREATE=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CreateNewParamWiz.h"\
	".\CreateNewWiz.h"\
	".\DDXGetFile.h"\
	".\DDXGetFolder.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\fmfcguid.h"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\SelectConnectionOpenNew.h"\
	".\SelectConnectionPage.h"\
	".\SelectConnectParams.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\WelcomePage.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\CreateNewWiz.obj" : $(SOURCE) $(DEP_CPP_CREATE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Ctfxmfc.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_CTFXM=\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"xtensnn.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL"\
 /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32"\
 /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\Ctfxmfc.obj"	"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_CTFXM=\
	".\Fakemfcp.hxx"\
	".\stdafx.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT"\
 /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DDXGetFile.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DDXGE=\
	".\DDXGetFile.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\DDXGetFile.obj"	"$(INTDIR)\DDXGetFile.sbr" : $(SOURCE)\
 $(DEP_CPP_DDXGE) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DDXGE=\
	".\DDXGetFile.h"\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\DDXGetFile.obj" : $(SOURCE) $(DEP_CPP_DDXGE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\DDXGetFolder.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DDXGET=\
	".\DDXGetFolder.h"\
	".\Dlgdir.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\DDXGetFolder.obj"	"$(INTDIR)\DDXGetFolder.sbr" : $(SOURCE)\
 $(DEP_CPP_DDXGET) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DDXGET=\
	".\DDXGetFolder.h"\
	".\Dlgdir.h"\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\DDXGetFolder.obj" : $(SOURCE) $(DEP_CPP_DDXGET) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Debug.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DEBUG=\
	".\Debug.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Debug.obj"	"$(INTDIR)\Debug.sbr" : $(SOURCE) $(DEP_CPP_DEBUG)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

!ENDIF 

SOURCE=.\DispUIOwner.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DISPU=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\DispUIOwner.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\DispUIOwner.obj"	"$(INTDIR)\DispUIOwner.sbr" : $(SOURCE)\
 $(DEP_CPP_DISPU) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DISPU=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\DispUIOwner.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\DispUIOwner.obj" : $(SOURCE) $(DEP_CPP_DISPU) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Dlgdir.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DLGDI=\
	".\Dlgdir.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Dlgdir.obj"	"$(INTDIR)\Dlgdir.sbr" : $(SOURCE) $(DEP_CPP_DLGDI)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DLGDI=\
	".\Dlgdir.h"\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Dlgdir.obj" : $(SOURCE) $(DEP_CPP_DLGDI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\dllbindx.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DLLBI=\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\dllbindx.obj"	"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DLLBI=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\dllfloat.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DLLFL=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\dllfloat.obj"	"$(INTDIR)\dllfloat.sbr" : $(SOURCE) $(DEP_CPP_DLLFL)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DLLFL=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\dllfloat.obj" : $(SOURCE) $(DEP_CPP_DLLFL) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Dummy2.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DUMMY=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Dummy2.obj"	"$(INTDIR)\Dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DUMMY=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Dummy3.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DUMMY3=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Dummy3.obj"	"$(INTDIR)\Dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DUMMY3=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Dummy4.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_DUMMY4=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Dummy4.obj"	"$(INTDIR)\Dummy4.sbr" : $(SOURCE) $(DEP_CPP_DUMMY4)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_DUMMY4=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Dummy4.obj" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Extreg.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_EXTRE=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"resstrg.h"\
	{$(INCLUDE)}"trcatids.h"\
	

"$(INTDIR)\Extreg.obj"	"$(INTDIR)\Extreg.sbr" : $(SOURCE) $(DEP_CPP_EXTRE)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_EXTRE=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"resstrg.h"\
	{$(INCLUDE)}"trcatids.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Extreg.obj" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Fakemfc.rc
DEP_RSC_FAKEM=\
	".\Docbuch.ico"\
	".\fakemfc.hm"\
	".\FAKEMFC.RCV"\
	".\fakeot.deb\Toolbar.tlb"\
	".\fakeot.rel\Toolbar.tlb"\
	".\idc_newp.ico"\
	".\idc_open.ico"\
	".\res\bitmap3.bmp"\
	".\res\Copy of Toolneu1.bmp"\
	".\res\dataimpo.ico"\
	".\res\dataserv.bmp"\
	".\res\editnew.ico"\
	".\res\fakemfc.ico"\
	".\res\fullscrn.bmp"\
	".\res\geoclass.bmp"\
	".\res\geoobjec.bmp"\
	".\res\geoview.bmp"\
	".\res\horzdrag.cur"\
	".\res\litebulb.bmp"\
	".\res\macrobtn.bmp"\
	".\res\objoper.bmp"\
	".\res\PropertyChoice.rgs"\
	".\res\standard.bmp"\
	".\res\SteckBtn.bmp"\
	".\res\Tool1.bmp"\
	".\res\tool10.bmp"\
	".\res\tool11.bmp"\
	".\res\tool12.bmp"\
	".\res\tool13.bmp"\
	".\res\tool14.bmp"\
	".\res\tool15.bmp"\
	".\res\tool16.bmp"\
	".\res\tool17.bmp"\
	".\res\tool18.bmp"\
	".\res\tool19.bmp"\
	".\res\tool2.bmp"\
	".\res\tool20.bmp"\
	".\res\tool21.bmp"\
	".\res\tool22.bmp"\
	".\res\tool23.bmp"\
	".\res\tool24.bmp"\
	".\res\tool25.bmp"\
	".\res\tool26.bmp"\
	".\res\tool27.bmp"\
	".\res\tool28.bmp"\
	".\res\tool29.bmp"\
	".\res\tool3.bmp"\
	".\res\tool30.bmp"\
	".\res\tool31.bmp"\
	".\res\tool32.bmp"\
	".\res\tool33.bmp"\
	".\res\tool34.bmp"\
	".\res\tool35.bmp"\
	".\res\tool36.bmp"\
	".\res\tool37.bmp"\
	".\res\tool38.bmp"\
	".\res\tool39.bmp"\
	".\res\tool4.bmp"\
	".\res\tool40.bmp"\
	".\res\tool41.bmp"\
	".\res\tool42.bmp"\
	".\res\tool43.bmp"\
	".\res\tool44.bmp"\
	".\res\tool45.bmp"\
	".\res\tool46.bmp"\
	".\res\tool47.bmp"\
	".\res\tool48.bmp"\
	".\res\tool49.bmp"\
	".\res\tool5.bmp"\
	".\res\tool50.bmp"\
	".\res\tool51.bmp"\
	".\res\tool52.bmp"\
	".\res\tool53.bmp"\
	".\res\tool54.bmp"\
	".\res\tool55.bmp"\
	".\res\tool56.bmp"\
	".\res\tool57.bmp"\
	".\res\tool58.bmp"\
	".\res\tool6.bmp"\
	".\res\tool7.bmp"\
	".\res\tool8.bmp"\
	".\res\tool9.bmp"\
	".\res\toolbar2.bmp"\
	".\res\ToolBarButton.rgs"\
	".\res\Tools.bmp"\
	".\res\Topkarte.bmp"\
	".\res\TRiASBarObj.rgs"\
	

"$(INTDIR)\Fakemfc.res" : $(SOURCE) $(DEP_RSC_FAKEM) "$(INTDIR)"\
 "$(INTDIR)\Toolbar.tlb" ".\FAKEMFC.RCV"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Fakemfcp.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_FAKEMF=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triasdb_i.c"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL"\
 /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32"\
 /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yc"fakemfcp.hxx"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\Fakemfcp.obj"	"$(INTDIR)\Fakemfcp.sbr"	"$(INTDIR)\Fakemfc.pch" : \
$(SOURCE) $(DEP_CPP_FAKEMF) "$(INTDIR)" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_FAKEMF=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triasdb_i.c"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT"\
 /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yc"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\Fakemfcp.obj"	"$(INTDIR)\Fakemfc.pch" : $(SOURCE) $(DEP_CPP_FAKEMF)\
 "$(INTDIR)" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Fakemfcx.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_FAKEMFC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\fmfcguid.h"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\ThisDll.h"\
	".\tipdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\VERSIO32.H"\
	".\Version.h"\
	".\WelcomeDlg.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"objgguid.h"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"trcatids.h"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "_SECDLL" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\Fakemfcx.obj"	"$(INTDIR)\Fakemfcx.sbr" : $(SOURCE)\
 $(DEP_CPP_FAKEMFC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"\
 ".\VERSIO32.H"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_FAKEMFC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\fmfcguid.h"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\ThisDll.h"\
	".\tipdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\VERSIO32.H"\
	".\Version.h"\
	".\WelcomeDlg.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"objgguid.h"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"trcatids.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /Gi- /GX /O1 /D "NDEBUG" /D "_SECDLL" /D\
 "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\Fakemfcx.obj" : $(SOURCE) $(DEP_CPP_FAKEMFC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h" ".\VERSIO32.H"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HandleProject.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_HANDL=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"gdo_i.c"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\HandleProject.obj"	"$(INTDIR)\HandleProject.sbr" : $(SOURCE)\
 $(DEP_CPP_HANDL) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_HANDL=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"gdo_i.c"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\HandleProject.obj" : $(SOURCE) $(DEP_CPP_HANDL) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Hdrentrx.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_HDREN=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Hdrentrx.obj"	"$(INTDIR)\Hdrentrx.sbr" : $(SOURCE) $(DEP_CPP_HDREN)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_HDREN=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Impxtcf.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_IMPXT=\
	".\Impxtcf.hxx"\
	".\Syncthrd.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	

"$(INTDIR)\Impxtcf.obj"	"$(INTDIR)\Impxtcf.sbr" : $(SOURCE) $(DEP_CPP_IMPXT)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_IMPXT=\
	".\Fakemfcp.hxx"\
	".\Impxtcf.hxx"\
	".\Syncthrd.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Impxtcf.obj" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ListCtrlEx.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_LISTC=\
	".\ListCtrlEx.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\ListCtrlEx.obj"	"$(INTDIR)\ListCtrlEx.sbr" : $(SOURCE)\
 $(DEP_CPP_LISTC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_LISTC=\
	".\Fakemfcp.hxx"\
	".\ListCtrlEx.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ListCtrlEx.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_MAINF=\
	".\AuxUIOwner.h"\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\cptriasbarnotifysink.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\MainUIOwner.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\ToolBarManager.h"\
	".\toolbarsdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASBarObj.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASToolBar.h"\
	".\triasview.h"\
	".\ViewComboBoxSec.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbardock.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"scopevar.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "_SECDLL" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_MAINF=\
	".\AuxUIOwner.h"\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\CoordStaticsSec.h"\
	".\cptriasbarnotifysink.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\MainUIOwner.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\ToolBarManager.h"\
	".\toolbarsdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASBarObj.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASToolBar.h"\
	".\triasview.h"\
	".\ViewComboBoxSec.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbardock.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"scopevar.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
NODEP_CPP_MAINF=\
	".\CoordStatics.h"\
	".\ViewComboBox.h"\
	".\ZoomComboBox.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /Gi- /GX /O1 /D "NDEBUG" /D "_SECDLL" /D\
 "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MainUIOwner.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_MAINU=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\MainUIOwner.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\MainUIOwner.obj"	"$(INTDIR)\MainUIOwner.sbr" : $(SOURCE)\
 $(DEP_CPP_MAINU) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_MAINU=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\MainUIOwner.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\MainUIOwner.obj" : $(SOURCE) $(DEP_CPP_MAINU) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ManageConnections.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_MANAG=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\mainfrm.h"\
	".\ManageConnections.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\ManageConnections.obj"	"$(INTDIR)\ManageConnections.sbr" : $(SOURCE)\
 $(DEP_CPP_MANAG) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_MANAG=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\mainfrm.h"\
	".\ManageConnections.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ManageConnections.obj" : $(SOURCE) $(DEP_CPP_MANAG) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\MsgHook.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_MSGHO=\
	".\Debug.h"\
	".\MsgHook.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\MsgHook.obj"	"$(INTDIR)\MsgHook.sbr" : $(SOURCE) $(DEP_CPP_MSGHO)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_MSGHO=\
	".\Debug.h"\
	".\Fakemfcp.hxx"\
	".\MsgHook.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\MsgHook.obj" : $(SOURCE) $(DEP_CPP_MSGHO) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\NewProjectAdvancedDlg.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_NEWPR=\
	".\NewProjectAdvancedDlg.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\NewProjectAdvancedDlg.obj"	"$(INTDIR)\NewProjectAdvancedDlg.sbr" : \
$(SOURCE) $(DEP_CPP_NEWPR) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch"\
 {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_NEWPR=\
	".\Fakemfcp.hxx"\
	".\NewProjectAdvancedDlg.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\NewProjectAdvancedDlg.obj" : $(SOURCE) $(DEP_CPP_NEWPR) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\OpenNewPropertySheet.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_OPENN=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\OpenNewPropertySheet.obj"	"$(INTDIR)\OpenNewPropertySheet.sbr" : \
$(SOURCE) $(DEP_CPP_OPENN) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch"\
 {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_OPENN=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\OpenNewPropertySheet.obj" : $(SOURCE) $(DEP_CPP_OPENN) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Picture.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_PICTU=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"picture.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL"\
 /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32"\
 /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"StdAfx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\Picture.obj"	"$(INTDIR)\Picture.sbr" : $(SOURCE) $(DEP_CPP_PICTU)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_PICTU=\
	".\Fakemfcp.hxx"\
	".\stdafx.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"picture.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT"\
 /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\Picture.obj" : $(SOURCE) $(DEP_CPP_PICTU) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PropActBase.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_PROPA=\
	".\PropActBase.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\PropActBase.obj"	"$(INTDIR)\PropActBase.sbr" : $(SOURCE)\
 $(DEP_CPP_PROPA) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_PROPA=\
	".\Fakemfcp.hxx"\
	".\PropActBase.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\PropActBase.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\PropertyChoice.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_PROPE=\
	".\PropActBase.h"\
	".\propertychoice.h"\
	".\Strings.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"int64.h"\
	{$(INCLUDE)}"ipropseq.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"statguid.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	

"$(INTDIR)\PropertyChoice.obj"	"$(INTDIR)\PropertyChoice.sbr" : $(SOURCE)\
 $(DEP_CPP_PROPE) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_PROPE=\
	".\Fakemfcp.hxx"\
	".\PropActBase.h"\
	".\propertychoice.h"\
	".\Strings.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"int64.h"\
	{$(INCLUDE)}"ipropseq.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"statguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\PropertyChoice.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Propset.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_PROPS=\
	".\Propset.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Propset.obj"	"$(INTDIR)\Propset.sbr" : $(SOURCE) $(DEP_CPP_PROPS)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_PROPS=\
	".\Fakemfcp.hxx"\
	".\Propset.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Propset.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Registry.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_REGIS=\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	

"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) $(DEP_CPP_REGIS)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_REGIS=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Registry.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\SCROLTIP.CPP

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SCROL=\
	".\SCROLTIP.H"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\SCROLTIP.OBJ"	"$(INTDIR)\SCROLTIP.SBR" : $(SOURCE) $(DEP_CPP_SCROL)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SCROL=\
	".\Fakemfcp.hxx"\
	".\SCROLTIP.H"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\SCROLTIP.OBJ" : $(SOURCE) $(DEP_CPP_SCROL) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\SelectConnectionOpenNew.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SELEC=\
	".\ConnectParams.h"\
	".\OpenNewPropertySheet.h"\
	".\SelectConnectionOpenNew.h"\
	".\Strings.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\SelectConnectionOpenNew.obj"	"$(INTDIR)\SelectConnectionOpenNew.sbr"\
 : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch"\
 {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SELEC=\
	".\ConnectParams.h"\
	".\Fakemfcp.hxx"\
	".\OpenNewPropertySheet.h"\
	".\SelectConnectionOpenNew.h"\
	".\Strings.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\SelectConnectionOpenNew.obj" : $(SOURCE) $(DEP_CPP_SELEC)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\SelectConnectionPage.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SELECT=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\SelectConnectionPage.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\SelectConnectionPage.obj"	"$(INTDIR)\SelectConnectionPage.sbr" : \
$(SOURCE) $(DEP_CPP_SELECT) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch"\
 {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SELECT=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\ListCtrlEx.h"\
	".\OpenNewPropertySheet.h"\
	".\SCROLTIP.H"\
	".\SelectConnectionPage.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\SelectConnectionPage.obj" : $(SOURCE) $(DEP_CPP_SELECT) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\SelectConnectParams.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SELECTC=\
	".\ConnectParams.h"\
	".\DDXGetFile.h"\
	".\DDXGetFolder.h"\
	".\OpenNewPropertySheet.h"\
	".\SelectConnectParams.h"\
	".\Strings.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\file\path.h"\
	{$(INCLUDE)}"ospace\file\path.ipp"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	

"$(INTDIR)\SelectConnectParams.obj"	"$(INTDIR)\SelectConnectParams.sbr" : \
$(SOURCE) $(DEP_CPP_SELECTC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch"\
 {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SELECTC=\
	".\ConnectParams.h"\
	".\DDXGetFile.h"\
	".\DDXGetFolder.h"\
	".\Fakemfcp.hxx"\
	".\OpenNewPropertySheet.h"\
	".\SelectConnectParams.h"\
	".\Strings.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\file\path.h"\
	{$(INCLUDE)}"ospace\file\path.ipp"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\SelectConnectParams.obj" : $(SOURCE) $(DEP_CPP_SELECTC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\SrvrItem.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SRVRI=\
	".\CntrItem.h"\
	".\SrvrItem.h"\
	".\TRiASDoc.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\SrvrItem.obj"	"$(INTDIR)\SrvrItem.sbr" : $(SOURCE) $(DEP_CPP_SRVRI)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SRVRI=\
	".\CntrItem.h"\
	".\Fakemfcp.hxx"\
	".\SrvrItem.h"\
	".\TRiASDoc.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\SrvrItem.obj" : $(SOURCE) $(DEP_CPP_SRVRI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Statpage.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_STATP=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\statpage.h"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\Statpage.obj"	"$(INTDIR)\Statpage.sbr" : $(SOURCE) $(DEP_CPP_STATP)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_STATP=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\statpage.h"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Statpage.obj" : $(SOURCE) $(DEP_CPP_STATP) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Strings.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_STRIN=\
	".\Strings.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Strings.obj"	"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_STRIN=\
	".\Fakemfcp.hxx"\
	".\Strings.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\summary.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SUMMA=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\statpage.h"\
	".\summary.hxx"\
	".\summcf.hxx"\
	".\summpage.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtnext.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\clasfact.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	

"$(INTDIR)\summary.obj"	"$(INTDIR)\summary.sbr" : $(SOURCE) $(DEP_CPP_SUMMA)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SUMMA=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\statpage.h"\
	".\summary.hxx"\
	".\summcf.hxx"\
	".\summpage.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ixtnext.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\clasfact.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\summary.obj" : $(SOURCE) $(DEP_CPP_SUMMA) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Summinfo.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SUMMI=\
	".\Propset.h"\
	".\Strings.h"\
	".\Summinfo.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\Summinfo.obj"	"$(INTDIR)\Summinfo.sbr" : $(SOURCE) $(DEP_CPP_SUMMI)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SUMMI=\
	".\Fakemfcp.hxx"\
	".\Propset.h"\
	".\Strings.h"\
	".\Summinfo.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Summinfo.obj" : $(SOURCE) $(DEP_CPP_SUMMI) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Summpage.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_SUMMP=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\summpage.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\Summpage.obj"	"$(INTDIR)\Summpage.sbr" : $(SOURCE) $(DEP_CPP_SUMMP)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_SUMMP=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\Propset.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\Summinfo.h"\
	".\summpage.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Summpage.obj" : $(SOURCE) $(DEP_CPP_SUMMP) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TipDlg.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TIPDL=\
	".\tipdlg.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "_SECDLL" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\TipDlg.obj"	"$(INTDIR)\TipDlg.sbr" : $(SOURCE) $(DEP_CPP_TIPDL)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TIPDL=\
	".\Fakemfcp.hxx"\
	".\tipdlg.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /Gi- /GX /O1 /D "NDEBUG" /D "_SECDLL" /D\
 "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Toolbar.idl

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

OutDir=.\.\fakeot.deb
InputPath=.\Toolbar.idl
InputName=Toolbar

"$(OutDir)/$(InputName).tlb"	"e:\triasdev.mvc\include\DToolBar.h"\
	"e:\triasdev.mvc\include\$(InputName)_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /tlb $(OutDir)/$(InputName).tlb /h\
                e:\triasdev.mvc\include\DToolBar.h /iid\
                "e:\triasdev.mvc\include\$(InputName)_i.c" $(InputPath)

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

OutDir=.\.\fakeot.rel
InputPath=.\Toolbar.idl
InputName=Toolbar

"$(OutDir)/$(InputName).tlb"	"e:\triasdev.mvc\include\DToolBar.h"\
	"e:\triasdev.mvc\include\$(InputName)_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /tlb $(OutDir)/$(InputName).tlb /h\
                e:\triasdev.mvc\include\DToolBar.h /iid\
                "e:\triasdev.mvc\include\$(InputName)_i.c" $(InputPath)

!ENDIF 

SOURCE=.\ToolBarButton.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TOOLB=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\OlePro32Wrap.h"\
	".\SCROLTIP.H"\
	".\ToolBarButton.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"bildobj.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eb.h"\
	{$(INCLUDE)}"eboem.h"\
	{$(INCLUDE)}"ibscript.hxx"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"itriasap.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"picture.h"\
	{$(INCLUDE)}"toolguid.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_SECDLL"\
 /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32"\
 /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D\
 "__ATL_20_USED__" /D "EBWIN32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Fakemfc.pch"\
 /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\fakemfcd.pdb" /FD /c 

"$(INTDIR)\ToolBarButton.obj"	"$(INTDIR)\ToolBarButton.sbr" : $(SOURCE)\
 $(DEP_CPP_TOOLB) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TOOLB=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\OlePro32Wrap.h"\
	".\SCROLTIP.H"\
	".\ToolBarButton.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bildobj.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eb.h"\
	{$(INCLUDE)}"eboem.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ibscript.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"itriasap.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"picture.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	
NODEP_CPP_TOOLB=\
	"c:\msdev5\vc\ebn21\include\dc.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_SECDLL" /D "_AFXEXT"\
 /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_USE_SEC_CLASSES" /D "__ATL_20_USED__" /D "EBWIN32"\
 /Fp"$(INTDIR)\Fakemfc.pch" /Yu"fakemfcp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\ToolBarButton.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ToolBarManager.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TOOLBA=\
	".\cptriasbarnotifysink.h"\
	".\mainfrm.h"\
	".\ToolBarManager.h"\
	".\TRiASBarObj.h"\
	".\TRiASToolBar.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\ToolBarManager.obj"	"$(INTDIR)\ToolBarManager.sbr" : $(SOURCE)\
 $(DEP_CPP_TOOLBA) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TOOLBA=\
	".\cptriasbarnotifysink.h"\
	".\Fakemfcp.hxx"\
	".\mainfrm.h"\
	".\ToolBarManager.h"\
	".\TRiASBarObj.h"\
	".\TRiASToolBar.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ToolBarManager.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ToolbarsDlg.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TOOLBAR=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\toolbarsdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\ToolbarsDlg.obj"	"$(INTDIR)\ToolbarsDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_TOOLBAR) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TOOLBAR=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\toolbarsdlg.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ToolbarsDlg.obj" : $(SOURCE) $(DEP_CPP_TOOLBAR) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASBarCont.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIAS=\
	".\mainfrm.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"fnamestr.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASBarCont.obj"	"$(INTDIR)\TRiASBarCont.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIAS) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIAS=\
	".\Fakemfcp.hxx"\
	".\mainfrm.h"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"fnamestr.h"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASBarCont.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASBarObj.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASB=\
	".\cptriasbarnotifysink.h"\
	".\DispUIOwner.h"\
	".\mainfrm.h"\
	".\TRiASBarObj.h"\
	".\TRiASCmdUI.h"\
	".\TRiASToolBar.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"itriasap.h"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASBarObj.obj"	"$(INTDIR)\TRiASBarObj.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASB) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASB=\
	".\cptriasbarnotifysink.h"\
	".\DispUIOwner.h"\
	".\Fakemfcp.hxx"\
	".\mainfrm.h"\
	".\TRiASBarObj.h"\
	".\TRiASCmdUI.h"\
	".\TRiASToolBar.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"itriasap.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"oleguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASBarObj.obj" : $(SOURCE) $(DEP_CPP_TRIASB) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASButtonCont.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASBU=\
	".\TRiASButtonCont.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\TRiASButtonCont.obj"	"$(INTDIR)\TRiASButtonCont.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASBU) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASBU=\
	".\Fakemfcp.hxx"\
	".\TRiASButtonCont.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASButtonCont.obj" : $(SOURCE) $(DEP_CPP_TRIASBU) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASCmdUI.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASC=\
	".\TRiASCmdUI.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\TRiASCmdUI.obj"	"$(INTDIR)\TRiASCmdUI.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASC=\
	".\Fakemfcp.hxx"\
	".\TRiASCmdUI.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASCmdUI.obj" : $(SOURCE) $(DEP_CPP_TRIASC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASDoc.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASD=\
	".\CntrItem.h"\
	".\SrvrItem.h"\
	".\TRiASDoc.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\TRiASDoc.obj"	"$(INTDIR)\TRiASDoc.sbr" : $(SOURCE) $(DEP_CPP_TRIASD)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASD=\
	".\CntrItem.h"\
	".\Fakemfcp.hxx"\
	".\SrvrItem.h"\
	".\TRiASDoc.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASDoc.obj" : $(SOURCE) $(DEP_CPP_TRIASD) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASDocTempl.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASDO=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASDocTempl.obj"	"$(INTDIR)\TRiASDocTempl.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASDO) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASDO=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASDocTempl.obj" : $(SOURCE) $(DEP_CPP_TRIASDO) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\triasext.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASE=\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	

"$(INTDIR)\triasext.obj"	"$(INTDIR)\triasext.sbr" : $(SOURCE) $(DEP_CPP_TRIASE)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASE=\
	".\Fakemfcp.hxx"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\triasext.obj" : $(SOURCE) $(DEP_CPP_TRIASE) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASStatusBar.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASS=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASCmdUI.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASStatusBar.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASStatusBar.obj"	"$(INTDIR)\TRiASStatusBar.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASS) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASS=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASCmdUI.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASStatusBar.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASStatusBar.obj" : $(SOURCE) $(DEP_CPP_TRIASS) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASStatusObj.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASST=\
	".\cptriasbarnotifysink.h"\
	".\mainfrm.h"\
	".\TRiASCmdUI.h"\
	".\TRiASStatusBar.h"\
	".\TRiASStatusObj.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASStatusObj.obj"	"$(INTDIR)\TRiASStatusObj.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASST) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASST=\
	".\cptriasbarnotifysink.h"\
	".\Fakemfcp.hxx"\
	".\mainfrm.h"\
	".\TRiASCmdUI.h"\
	".\TRiASStatusBar.h"\
	".\TRiASStatusObj.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASStatusObj.obj" : $(SOURCE) $(DEP_CPP_TRIASST) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASToolBar.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIAST=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASCmdUI.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASToolBar.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbardock.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	

"$(INTDIR)\TRiASToolBar.obj"	"$(INTDIR)\TRiASToolBar.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIAST) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIAST=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\mainfrm.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASCmdUI.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\TRiASToolBar.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbardock.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASToolBar.obj" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\TRiASView.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_TRIASV=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASDoc.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defattr.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"igeometr.hxx"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"objgguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"vinfomfc.h"\
	

"$(INTDIR)\TRiASView.obj"	"$(INTDIR)\TRiASView.sbr" : $(SOURCE)\
 $(DEP_CPP_TRIASV) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_TRIASV=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASDoc.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defattr.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"igeometr.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"objgguid.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"vinfomfc.h"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\TRiASView.obj" : $(SOURCE) $(DEP_CPP_TRIASV) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ViewComboBoxSec.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_VIEWC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\ViewComboBoxSec.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\ViewComboBoxSec.obj"	"$(INTDIR)\ViewComboBoxSec.sbr" : $(SOURCE)\
 $(DEP_CPP_VIEWC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_VIEWC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\SCROLTIP.H"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\ViewComboBoxSec.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ViewComboBoxSec.obj" : $(SOURCE) $(DEP_CPP_VIEWC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\WelcomePage.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_WELCO=\
	".\ConnectParams.h"\
	".\OpenNewPropertySheet.h"\
	".\Strings.h"\
	".\WelcomePage.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"registrx.hxx"\
	

"$(INTDIR)\WelcomePage.obj"	"$(INTDIR)\WelcomePage.sbr" : $(SOURCE)\
 $(DEP_CPP_WELCO) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_WELCO=\
	".\ConnectParams.h"\
	".\Fakemfcp.hxx"\
	".\OpenNewPropertySheet.h"\
	".\Strings.h"\
	".\WelcomePage.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\WelcomePage.obj" : $(SOURCE) $(DEP_CPP_WELCO) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\Xtencunk.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_XTENC=\
	".\CIMPXTSN.HXX"\
	".\cptriasbarnotifysink.h"\
	".\fmfcguid.h"\
	".\Impxtcf.hxx"\
	".\mainfrm.h"\
	".\MainUIOwner.h"\
	".\PropActBase.h"\
	".\propertychoice.h"\
	".\Strings.h"\
	".\summary.hxx"\
	".\summcf.hxx"\
	".\Syncthrd.hxx"\
	".\ThisDll.h"\
	".\ToolBarButton.h"\
	".\TRiASBarObj.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"ibscript.hxx"\
	{$(INCLUDE)}"ipropseq.hxx"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtnext.hxx"\
	{$(INCLUDE)}"ospace\com\clasfact.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"statguid.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtsnguid.h"\
	

"$(INTDIR)\Xtencunk.obj"	"$(INTDIR)\Xtencunk.sbr" : $(SOURCE) $(DEP_CPP_XTENC)\
 "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_XTENC=\
	".\CIMPXTSN.HXX"\
	".\cptriasbarnotifysink.h"\
	".\Fakemfcp.hxx"\
	".\fmfcguid.h"\
	".\Impxtcf.hxx"\
	".\mainfrm.h"\
	".\MainUIOwner.h"\
	".\PropActBase.h"\
	".\propertychoice.h"\
	".\Strings.h"\
	".\summary.hxx"\
	".\summcf.hxx"\
	".\Syncthrd.hxx"\
	".\ThisDll.h"\
	".\ToolBarButton.h"\
	".\TRiASBarObj.h"\
	".\Wrapper.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"bscrguid.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ibscript.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"ipropseq.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ixtnext.hxx"\
	{$(INCLUDE)}"ospace\com\clasfact.h"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"ospace\views\domain.h"\
	{$(INCLUDE)}"ospace\views\mapview.h"\
	{$(INCLUDE)}"ospace\views\predicate.h"\
	{$(INCLUDE)}"ospace\views\transform.h"\
	{$(INCLUDE)}"ospace\views\view.h"\
	{$(INCLUDE)}"ospace\views\views.h"\
	{$(INCLUDE)}"progress.h"\
	{$(INCLUDE)}"propactn.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarcust.h"\
	{$(INCLUDE)}"sbarstat.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"sectlf.h"\
	{$(INCLUDE)}"srchoice.h"\
	{$(INCLUDE)}"statguid.h"\
	{$(INCLUDE)}"swinfrm.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\ZoomComboBoxSec.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

DEP_CPP_ZOOMC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\InlineFuncs.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	

"$(INTDIR)\ZoomComboBoxSec.obj"	"$(INTDIR)\ZoomComboBoxSec.sbr" : $(SOURCE)\
 $(DEP_CPP_ZOOMC) "$(INTDIR)" "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

DEP_CPP_ZOOMC=\
	".\CntrItem.h"\
	".\ConnectedCtf.h"\
	".\ConnectParams.h"\
	".\Fakemfc.hxx"\
	".\Fakemfcp.hxx"\
	".\InlineFuncs.h"\
	".\MsgHook.h"\
	".\SCROLTIP.H"\
	".\Strings.h"\
	".\TRiASBarCont.h"\
	".\TRiASDoc.h"\
	".\TRiASDocTempl.h"\
	".\triasview.h"\
	".\Wrapper.h"\
	".\ZoomComboBoxSec.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dirisole.h"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"DToolBar.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"gdo.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"itoolbar.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\iterenum.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\header.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\rtti\class.h"\
	{$(INCLUDE)}"ospace\rtti\class.ipp"\
	{$(INCLUDE)}"ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"ospace\std\algorithm"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\typeinfo"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"ospace\stl\advalgo.h"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\heap.cc"\
	{$(INCLUDE)}"ospace\stl\heap.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\randgen.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rawiter.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\sort.cc"\
	{$(INCLUDE)}"ospace\stl\sort.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\stream\hmacros.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"sbarcore.h"\
	{$(INCLUDE)}"sbarmgr.h"\
	{$(INCLUDE)}"sdocksta.h"\
	{$(INCLUDE)}"secdll.h"\
	{$(INCLUDE)}"tbarcust.h"\
	{$(INCLUDE)}"tbarmgr.h"\
	{$(INCLUDE)}"tbtncmbo.h"\
	{$(INCLUDE)}"tbtnstd.h"\
	{$(INCLUDE)}"tbtnwnd.h"\
	{$(INCLUDE)}"toolguid.h"\
	{$(INCLUDE)}"triasdb.h"\
	{$(INCLUDE)}"triastlb.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

"$(INTDIR)\ZoomComboBoxSec.obj" : $(SOURCE) $(DEP_CPP_ZOOMC) "$(INTDIR)"\
 "$(INTDIR)\Fakemfc.pch" {$(INCLUDE)}"DToolBar.h"


!ENDIF 

SOURCE=.\FAKEMFC.TPL
USERDEP__FAKEMFC_="makefile"	

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

InputPath=.\FAKEMFC.TPL

"fakemfc.def"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FAKEMFC_)
	nmake -nologo fakemfc.def

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

InputPath=.\FAKEMFC.TPL

"fakemfc.def"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FAKEMFC_)
	nmake -nologo fakemfc.def

!ENDIF 

SOURCE=.\FAKEMFCV.TPL
USERDEP__FAKEMFCV="makefile"	

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

InputPath=.\FAKEMFCV.TPL

"fakemfc.rcv"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FAKEMFCV)
	nmake -nologo fakemfc.rcv

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

InputPath=.\FAKEMFCV.TPL

"fakemfc.rcv"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FAKEMFCV)
	nmake -nologo fakemfc.rcv

!ENDIF 

SOURCE=.\RIGHTS.TPL
USERDEP__RIGHT="makefile"	

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

InputPath=.\RIGHTS.TPL

"rights.exe"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__RIGHT)
	nmake -nologo rights.exe

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

InputPath=.\RIGHTS.TPL

"rights.exe"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__RIGHT)
	nmake -nologo rights.exe

!ENDIF 

SOURCE=.\VERSIO32.TPL
USERDEP__VERSI="makefile"	

!IF  "$(CFG)" == "fakemfc - Win32 Debug with OT"

InputPath=.\VERSIO32.TPL

"versio32.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__VERSI)
	nmake -nologo versio32.h

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Release with OT"

InputPath=.\VERSIO32.TPL

"versio32.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__VERSI)
	nmake -nologo versio32.h

!ENDIF 


!ENDIF 

