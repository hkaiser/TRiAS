# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Trias323 - Win32 Debug DCOM
!MESSAGE No configuration specified.  Defaulting to Trias323 - Win32 Debug\
 DCOM.
!ENDIF 

!IF "$(CFG)" != "Trias323 - Win32 Release" && "$(CFG)" !=\
 "Trias323 - Win32 Debug" && "$(CFG)" != "Trias323 - Win32 Debug DCOM" &&\
 "$(CFG)" != "Trias323 - Win32 Pseudo Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRIAS423.MAK" CFG="Trias323 - Win32 Debug DCOM"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias323 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Trias323 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Trias323 - Win32 Debug DCOM" (based on "Win32 (x86) Application")
!MESSAGE "Trias323 - Win32 Pseudo Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Trias323 - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=Trias323
# End Custom Macros

ALL : "$(OUTDIR)\Trias323.dll" "$(OUTDIR)\TRIAS423.bsc"\
 "c:\trias.mvc\trias200.rel\Trias323.dll" "..\lib32\Trias323.lib"\
 ".\TRiASHelper_i.c" ".\dlldata.c" ".\TRiASHelper_p.c"

CLEAN : 
	-@erase "$(INTDIR)\bmpbtn.obj"
	-@erase "$(INTDIR)\bmpbtn.sbr"
	-@erase "$(INTDIR)\cextreg.obj"
	-@erase "$(INTDIR)\cextreg.sbr"
	-@erase "$(INTDIR)\CheckTreeView.obj"
	-@erase "$(INTDIR)\CheckTreeView.sbr"
	-@erase "$(INTDIR)\CLSFYPRP.OBJ"
	-@erase "$(INTDIR)\CLSFYPRP.SBR"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\Dataobj.sbr"
	-@erase "$(INTDIR)\DATATRAN.OBJ"
	-@erase "$(INTDIR)\DATATRAN.SBR"
	-@erase "$(INTDIR)\dblcoord.obj"
	-@erase "$(INTDIR)\dblcoord.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
	-@erase "$(INTDIR)\DelObPrp.obj"
	-@erase "$(INTDIR)\DelObPrp.sbr"
	-@erase "$(INTDIR)\DstObDlg.obj"
	-@erase "$(INTDIR)\DstObDlg.sbr"
	-@erase "$(INTDIR)\DstObWnd.obj"
	-@erase "$(INTDIR)\DstObWnd.sbr"
	-@erase "$(INTDIR)\Enumonr.obj"
	-@erase "$(INTDIR)\Enumonr.sbr"
	-@erase "$(INTDIR)\enumundo.obj"
	-@erase "$(INTDIR)\enumundo.sbr"
	-@erase "$(INTDIR)\GenTextDlg.obj"
	-@erase "$(INTDIR)\GenTextDlg.sbr"
	-@erase "$(INTDIR)\GenTextPropAct.obj"
	-@erase "$(INTDIR)\GenTextPropAct.sbr"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\Idataobj.obj"
	-@erase "$(INTDIR)\Idataobj.sbr"
	-@erase "$(INTDIR)\Ienumfe.obj"
	-@erase "$(INTDIR)\Ienumfe.sbr"
	-@erase "$(INTDIR)\ImportDataDlg.obj"
	-@erase "$(INTDIR)\ImportDataDlg.sbr"
	-@erase "$(INTDIR)\ImportProp.obj"
	-@erase "$(INTDIR)\ImportProp.sbr"
	-@erase "$(INTDIR)\InPlaceCombo.obj"
	-@erase "$(INTDIR)\InPlaceCombo.sbr"
	-@erase "$(INTDIR)\INTOPROP.OBJ"
	-@erase "$(INTDIR)\INTOPROP.SBR"
	-@erase "$(INTDIR)\JUSTIFY.OBJ"
	-@erase "$(INTDIR)\JUSTIFY.SBR"
	-@erase "$(INTDIR)\LIBMAIN3.OBJ"
	-@erase "$(INTDIR)\LIBMAIN3.SBR"
	-@erase "$(INTDIR)\LISTHSCR.OBJ"
	-@erase "$(INTDIR)\LISTHSCR.SBR"
	-@erase "$(INTDIR)\MatchingObjects.obj"
	-@erase "$(INTDIR)\MatchingObjects.sbr"
	-@erase "$(INTDIR)\Modident.obj"
	-@erase "$(INTDIR)\Modident.sbr"
	-@erase "$(INTDIR)\Modidprp.obj"
	-@erase "$(INTDIR)\Modidprp.sbr"
	-@erase "$(INTDIR)\MultiPI.obj"
	-@erase "$(INTDIR)\MultiPI.sbr"
	-@erase "$(INTDIR)\MUSCROLL.OBJ"
	-@erase "$(INTDIR)\MUSCROLL.SBR"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.SBR"
	-@erase "$(INTDIR)\ObjekteDoppeln.obj"
	-@erase "$(INTDIR)\ObjekteDoppeln.sbr"
	-@erase "$(INTDIR)\ObjekteVereinigen.obj"
	-@erase "$(INTDIR)\ObjekteVereinigen.sbr"
	-@erase "$(INTDIR)\ObjGeomW.obj"
	-@erase "$(INTDIR)\ObjGeomW.sbr"
	-@erase "$(INTDIR)\opropcf.obj"
	-@erase "$(INTDIR)\opropcf.sbr"
	-@erase "$(INTDIR)\oprpfeat.obj"
	-@erase "$(INTDIR)\oprpfeat.sbr"
	-@erase "$(INTDIR)\OWNCOMBO.OBJ"
	-@erase "$(INTDIR)\OWNCOMBO.SBR"
	-@erase "$(INTDIR)\OWNLIST.OBJ"
	-@erase "$(INTDIR)\OWNLIST.SBR"
	-@erase "$(INTDIR)\OWNLISTE.OBJ"
	-@erase "$(INTDIR)\OWNLISTE.SBR"
	-@erase "$(INTDIR)\PRNTPARS.OBJ"
	-@erase "$(INTDIR)\PRNTPARS.SBR"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\Propname.obj"
	-@erase "$(INTDIR)\Propname.sbr"
	-@erase "$(INTDIR)\Propseq.obj"
	-@erase "$(INTDIR)\Propseq.sbr"
	-@erase "$(INTDIR)\queryfld.obj"
	-@erase "$(INTDIR)\queryfld.sbr"
	-@erase "$(INTDIR)\REGISTER.OBJ"
	-@erase "$(INTDIR)\REGISTER.SBR"
	-@erase "$(INTDIR)\RegisterExt.obj"
	-@erase "$(INTDIR)\RegisterExt.sbr"
	-@erase "$(INTDIR)\REGOBJ.OBJ"
	-@erase "$(INTDIR)\REGOBJ.SBR"
	-@erase "$(INTDIR)\regprop.obj"
	-@erase "$(INTDIR)\regprop.sbr"
	-@erase "$(INTDIR)\ROTATE.OBJ"
	-@erase "$(INTDIR)\ROTATE.SBR"
	-@erase "$(INTDIR)\ScriptPropAct.obj"
	-@erase "$(INTDIR)\ScriptPropAct.sbr"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selident.sbr"
	-@erase "$(INTDIR)\SELIDLST.OBJ"
	-@erase "$(INTDIR)\SELIDLST.SBR"
	-@erase "$(INTDIR)\selidlvc.obj"
	-@erase "$(INTDIR)\selidlvc.sbr"
	-@erase "$(INTDIR)\Selidprp.obj"
	-@erase "$(INTDIR)\Selidprp.sbr"
	-@erase "$(INTDIR)\Selobdlg.obj"
	-@erase "$(INTDIR)\Selobdlg.sbr"
	-@erase "$(INTDIR)\SelObjProp.obj"
	-@erase "$(INTDIR)\SelObjProp.sbr"
	-@erase "$(INTDIR)\SelObjPropDlg.obj"
	-@erase "$(INTDIR)\SelObjPropDlg.sbr"
	-@erase "$(INTDIR)\Selobwnd.obj"
	-@erase "$(INTDIR)\Selobwnd.sbr"
	-@erase "$(INTDIR)\SelOProp.obj"
	-@erase "$(INTDIR)\SelOProp.sbr"
	-@erase "$(INTDIR)\SelOPrpTree.obj"
	-@erase "$(INTDIR)\SelOPrpTree.sbr"
	-@erase "$(INTDIR)\SPINCTRL.OBJ"
	-@erase "$(INTDIR)\SPINCTRL.SBR"
	-@erase "$(INTDIR)\statimpl.obj"
	-@erase "$(INTDIR)\statimpl.sbr"
	-@erase "$(INTDIR)\STATUS.OBJ"
	-@erase "$(INTDIR)\STATUS.SBR"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\TextSearchEngine.obj"
	-@erase "$(INTDIR)\TextSearchEngine.sbr"
	-@erase "$(INTDIR)\trias03p.obj"
	-@erase "$(INTDIR)\trias03p.sbr"
	-@erase "$(INTDIR)\Trias323.pch"
	-@erase "$(INTDIR)\Trias323.res"
	-@erase "$(INTDIR)\TRiASHelper.tlb"
	-@erase "$(INTDIR)\TriASTrans.obj"
	-@erase "$(INTDIR)\TriASTrans.sbr"
	-@erase "$(INTDIR)\txtsrchd.obj"
	-@erase "$(INTDIR)\txtsrchd.sbr"
	-@erase "$(INTDIR)\undocf.obj"
	-@erase "$(INTDIR)\undocf.sbr"
	-@erase "$(INTDIR)\UndoCreo.obj"
	-@erase "$(INTDIR)\UndoCreo.sbr"
	-@erase "$(INTDIR)\undodelo.obj"
	-@erase "$(INTDIR)\undodelo.sbr"
	-@erase "$(INTDIR)\undodelr.obj"
	-@erase "$(INTDIR)\undodelr.sbr"
	-@erase "$(INTDIR)\undodelt.obj"
	-@erase "$(INTDIR)\undodelt.sbr"
	-@erase "$(INTDIR)\undofeat.obj"
	-@erase "$(INTDIR)\undofeat.sbr"
	-@erase "$(INTDIR)\undohelp.obj"
	-@erase "$(INTDIR)\undohelp.sbr"
	-@erase "$(INTDIR)\undohwnd.obj"
	-@erase "$(INTDIR)\undohwnd.sbr"
	-@erase "$(INTDIR)\undomodi.obj"
	-@erase "$(INTDIR)\undomodi.sbr"
	-@erase "$(INTDIR)\undomodo.obj"
	-@erase "$(INTDIR)\undomodo.sbr"
	-@erase "$(INTDIR)\undomodr.obj"
	-@erase "$(INTDIR)\undomodr.sbr"
	-@erase "$(INTDIR)\undomodv.obj"
	-@erase "$(INTDIR)\undomodv.sbr"
	-@erase "$(INTDIR)\undopbd.obj"
	-@erase "$(INTDIR)\undopbd.sbr"
	-@erase "$(INTDIR)\undoredo.obj"
	-@erase "$(INTDIR)\undoredo.sbr"
	-@erase "$(INTDIR)\undotext.obj"
	-@erase "$(INTDIR)\undotext.sbr"
	-@erase "$(OUTDIR)\Trias323.dll"
	-@erase "$(OUTDIR)\Trias323.exp"
	-@erase "$(OUTDIR)\Trias323.lib"
	-@erase "$(OUTDIR)\TRIAS423.bsc"
	-@erase "..\lib32\Trias323.lib"
	-@erase ".\dlldata.c"
	-@erase ".\TRiASHelper.h"
	-@erase ".\TRiASHelper_i.c"
	-@erase ".\TRiASHelper_p.c"
	-@erase "c:\trias.mvc\trias200.rel\Trias323.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinRel\TRIAS323.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE" /Fr /Fp"Release/Trias323.pch" /Yu"trias03p.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__"\
 /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D\
 "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE"\
 /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Trias323.pch" /Yu"trias03p.hxx" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "./obj32" /d "NDEBUG" /d "_OLDCATIDS"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /d "NDEBUG" /d\
 "_OLDCATIDS" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRIAS423.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bmpbtn.sbr" \
	"$(INTDIR)\cextreg.sbr" \
	"$(INTDIR)\CheckTreeView.sbr" \
	"$(INTDIR)\CLSFYPRP.SBR" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Dataobj.sbr" \
	"$(INTDIR)\DATATRAN.SBR" \
	"$(INTDIR)\dblcoord.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\DelObPrp.sbr" \
	"$(INTDIR)\DstObDlg.sbr" \
	"$(INTDIR)\DstObWnd.sbr" \
	"$(INTDIR)\Enumonr.sbr" \
	"$(INTDIR)\enumundo.sbr" \
	"$(INTDIR)\GenTextDlg.sbr" \
	"$(INTDIR)\GenTextPropAct.sbr" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\Idataobj.sbr" \
	"$(INTDIR)\Ienumfe.sbr" \
	"$(INTDIR)\ImportDataDlg.sbr" \
	"$(INTDIR)\ImportProp.sbr" \
	"$(INTDIR)\InPlaceCombo.sbr" \
	"$(INTDIR)\INTOPROP.SBR" \
	"$(INTDIR)\JUSTIFY.SBR" \
	"$(INTDIR)\LIBMAIN3.SBR" \
	"$(INTDIR)\LISTHSCR.SBR" \
	"$(INTDIR)\MatchingObjects.sbr" \
	"$(INTDIR)\Modident.sbr" \
	"$(INTDIR)\Modidprp.sbr" \
	"$(INTDIR)\MultiPI.sbr" \
	"$(INTDIR)\MUSCROLL.SBR" \
	"$(INTDIR)\NUMEDIT.SBR" \
	"$(INTDIR)\ObjekteDoppeln.sbr" \
	"$(INTDIR)\ObjekteVereinigen.sbr" \
	"$(INTDIR)\ObjGeomW.sbr" \
	"$(INTDIR)\opropcf.sbr" \
	"$(INTDIR)\oprpfeat.sbr" \
	"$(INTDIR)\OWNCOMBO.SBR" \
	"$(INTDIR)\OWNLIST.SBR" \
	"$(INTDIR)\OWNLISTE.SBR" \
	"$(INTDIR)\PRNTPARS.SBR" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\Propname.sbr" \
	"$(INTDIR)\Propseq.sbr" \
	"$(INTDIR)\queryfld.sbr" \
	"$(INTDIR)\REGISTER.SBR" \
	"$(INTDIR)\RegisterExt.sbr" \
	"$(INTDIR)\REGOBJ.SBR" \
	"$(INTDIR)\regprop.sbr" \
	"$(INTDIR)\ROTATE.SBR" \
	"$(INTDIR)\ScriptPropAct.sbr" \
	"$(INTDIR)\Selident.sbr" \
	"$(INTDIR)\SELIDLST.SBR" \
	"$(INTDIR)\selidlvc.sbr" \
	"$(INTDIR)\Selidprp.sbr" \
	"$(INTDIR)\Selobdlg.sbr" \
	"$(INTDIR)\SelObjProp.sbr" \
	"$(INTDIR)\SelObjPropDlg.sbr" \
	"$(INTDIR)\Selobwnd.sbr" \
	"$(INTDIR)\SelOProp.sbr" \
	"$(INTDIR)\SelOPrpTree.sbr" \
	"$(INTDIR)\SPINCTRL.SBR" \
	"$(INTDIR)\statimpl.sbr" \
	"$(INTDIR)\STATUS.SBR" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\TextSearchEngine.sbr" \
	"$(INTDIR)\trias03p.sbr" \
	"$(INTDIR)\TriASTrans.sbr" \
	"$(INTDIR)\txtsrchd.sbr" \
	"$(INTDIR)\undocf.sbr" \
	"$(INTDIR)\UndoCreo.sbr" \
	"$(INTDIR)\undodelo.sbr" \
	"$(INTDIR)\undodelr.sbr" \
	"$(INTDIR)\undodelt.sbr" \
	"$(INTDIR)\undofeat.sbr" \
	"$(INTDIR)\undohelp.sbr" \
	"$(INTDIR)\undohwnd.sbr" \
	"$(INTDIR)\undomodi.sbr" \
	"$(INTDIR)\undomodo.sbr" \
	"$(INTDIR)\undomodr.sbr" \
	"$(INTDIR)\undomodv.sbr" \
	"$(INTDIR)\undopbd.sbr" \
	"$(INTDIR)\undoredo.sbr" \
	"$(INTDIR)\undotext.sbr"

"$(OUTDIR)\TRIAS423.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 trias322.lib trias321.lib tfrmwork.lib cont32r.lib ospace2r.lib stdcppr.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"./obj32/rights.exe" /out:"Release/Trias323.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=trias322.lib trias321.lib tfrmwork.lib cont32r.lib ospace2r.lib\
 stdcppr.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib\
 /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Trias323.pdb" /machine:I386\
 /def:".\obj32\trias323207.def" /stub:"./obj32/rights.exe"\
 /out:"$(OUTDIR)/Trias323.dll" /implib:"$(OUTDIR)/Trias323.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\trias323207.def"
LINK32_OBJS= \
	"$(INTDIR)\bmpbtn.obj" \
	"$(INTDIR)\cextreg.obj" \
	"$(INTDIR)\CheckTreeView.obj" \
	"$(INTDIR)\CLSFYPRP.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DATATRAN.OBJ" \
	"$(INTDIR)\dblcoord.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\DelObPrp.obj" \
	"$(INTDIR)\DstObDlg.obj" \
	"$(INTDIR)\DstObWnd.obj" \
	"$(INTDIR)\Enumonr.obj" \
	"$(INTDIR)\enumundo.obj" \
	"$(INTDIR)\GenTextDlg.obj" \
	"$(INTDIR)\GenTextPropAct.obj" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\Idataobj.obj" \
	"$(INTDIR)\Ienumfe.obj" \
	"$(INTDIR)\ImportDataDlg.obj" \
	"$(INTDIR)\ImportProp.obj" \
	"$(INTDIR)\InPlaceCombo.obj" \
	"$(INTDIR)\INTOPROP.OBJ" \
	"$(INTDIR)\JUSTIFY.OBJ" \
	"$(INTDIR)\LIBMAIN3.OBJ" \
	"$(INTDIR)\LISTHSCR.OBJ" \
	"$(INTDIR)\MatchingObjects.obj" \
	"$(INTDIR)\Modident.obj" \
	"$(INTDIR)\Modidprp.obj" \
	"$(INTDIR)\MultiPI.obj" \
	"$(INTDIR)\MUSCROLL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\ObjekteDoppeln.obj" \
	"$(INTDIR)\ObjekteVereinigen.obj" \
	"$(INTDIR)\ObjGeomW.obj" \
	"$(INTDIR)\opropcf.obj" \
	"$(INTDIR)\oprpfeat.obj" \
	"$(INTDIR)\OWNCOMBO.OBJ" \
	"$(INTDIR)\OWNLIST.OBJ" \
	"$(INTDIR)\OWNLISTE.OBJ" \
	"$(INTDIR)\PRNTPARS.OBJ" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Propname.obj" \
	"$(INTDIR)\Propseq.obj" \
	"$(INTDIR)\queryfld.obj" \
	"$(INTDIR)\REGISTER.OBJ" \
	"$(INTDIR)\RegisterExt.obj" \
	"$(INTDIR)\REGOBJ.OBJ" \
	"$(INTDIR)\regprop.obj" \
	"$(INTDIR)\ROTATE.OBJ" \
	"$(INTDIR)\ScriptPropAct.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\SELIDLST.OBJ" \
	"$(INTDIR)\selidlvc.obj" \
	"$(INTDIR)\Selidprp.obj" \
	"$(INTDIR)\Selobdlg.obj" \
	"$(INTDIR)\SelObjProp.obj" \
	"$(INTDIR)\SelObjPropDlg.obj" \
	"$(INTDIR)\Selobwnd.obj" \
	"$(INTDIR)\SelOProp.obj" \
	"$(INTDIR)\SelOPrpTree.obj" \
	"$(INTDIR)\SPINCTRL.OBJ" \
	"$(INTDIR)\statimpl.obj" \
	"$(INTDIR)\STATUS.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TextSearchEngine.obj" \
	"$(INTDIR)\trias03p.obj" \
	"$(INTDIR)\Trias323.res" \
	"$(INTDIR)\TriASTrans.obj" \
	"$(INTDIR)\txtsrchd.obj" \
	"$(INTDIR)\undocf.obj" \
	"$(INTDIR)\UndoCreo.obj" \
	"$(INTDIR)\undodelo.obj" \
	"$(INTDIR)\undodelr.obj" \
	"$(INTDIR)\undodelt.obj" \
	"$(INTDIR)\undofeat.obj" \
	"$(INTDIR)\undohelp.obj" \
	"$(INTDIR)\undohwnd.obj" \
	"$(INTDIR)\undomodi.obj" \
	"$(INTDIR)\undomodo.obj" \
	"$(INTDIR)\undomodr.obj" \
	"$(INTDIR)\undomodv.obj" \
	"$(INTDIR)\undopbd.obj" \
	"$(INTDIR)\undoredo.obj" \
	"$(INTDIR)\undotext.obj"

"$(OUTDIR)\Trias323.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\Trias323.dll
TargetName=Trias323
InputPath=.\Release\Trias323.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" c:\trias.mvc\trias200.rel \
	copy "$(OutDir)\$(TargetName).lib" \triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug.207"
# PROP Intermediate_Dir "Debug.207"
OUTDIR=.\Debug.207
INTDIR=.\Debug.207
# Begin Custom Macros
TargetName=trias33d
# End Custom Macros

ALL : "$(OUTDIR)\trias33d.dll" "$(OUTDIR)\TRIAS423.bsc"\
 "c:\trias.mvc\trias209.deb\trias33d.dll" "..\lib32\trias33d.lib"\
 ".\TRiASHelper_i.c" ".\dlldata.c" ".\TRiASHelper_p.c"

CLEAN : 
	-@erase "$(INTDIR)\bmpbtn.obj"
	-@erase "$(INTDIR)\bmpbtn.sbr"
	-@erase "$(INTDIR)\cextreg.obj"
	-@erase "$(INTDIR)\cextreg.sbr"
	-@erase "$(INTDIR)\CheckTreeView.obj"
	-@erase "$(INTDIR)\CheckTreeView.sbr"
	-@erase "$(INTDIR)\CLSFYPRP.OBJ"
	-@erase "$(INTDIR)\CLSFYPRP.SBR"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\Dataobj.sbr"
	-@erase "$(INTDIR)\DATATRAN.OBJ"
	-@erase "$(INTDIR)\DATATRAN.SBR"
	-@erase "$(INTDIR)\dblcoord.obj"
	-@erase "$(INTDIR)\dblcoord.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
	-@erase "$(INTDIR)\DelObPrp.obj"
	-@erase "$(INTDIR)\DelObPrp.sbr"
	-@erase "$(INTDIR)\DstObDlg.obj"
	-@erase "$(INTDIR)\DstObDlg.sbr"
	-@erase "$(INTDIR)\DstObWnd.obj"
	-@erase "$(INTDIR)\DstObWnd.sbr"
	-@erase "$(INTDIR)\Enumonr.obj"
	-@erase "$(INTDIR)\Enumonr.sbr"
	-@erase "$(INTDIR)\enumundo.obj"
	-@erase "$(INTDIR)\enumundo.sbr"
	-@erase "$(INTDIR)\GenTextDlg.obj"
	-@erase "$(INTDIR)\GenTextDlg.sbr"
	-@erase "$(INTDIR)\GenTextPropAct.obj"
	-@erase "$(INTDIR)\GenTextPropAct.sbr"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\Idataobj.obj"
	-@erase "$(INTDIR)\Idataobj.sbr"
	-@erase "$(INTDIR)\Ienumfe.obj"
	-@erase "$(INTDIR)\Ienumfe.sbr"
	-@erase "$(INTDIR)\ImportDataDlg.obj"
	-@erase "$(INTDIR)\ImportDataDlg.sbr"
	-@erase "$(INTDIR)\ImportProp.obj"
	-@erase "$(INTDIR)\ImportProp.sbr"
	-@erase "$(INTDIR)\InPlaceCombo.obj"
	-@erase "$(INTDIR)\InPlaceCombo.sbr"
	-@erase "$(INTDIR)\INTOPROP.OBJ"
	-@erase "$(INTDIR)\INTOPROP.SBR"
	-@erase "$(INTDIR)\JUSTIFY.OBJ"
	-@erase "$(INTDIR)\JUSTIFY.SBR"
	-@erase "$(INTDIR)\LIBMAIN3.OBJ"
	-@erase "$(INTDIR)\LIBMAIN3.SBR"
	-@erase "$(INTDIR)\LISTHSCR.OBJ"
	-@erase "$(INTDIR)\LISTHSCR.SBR"
	-@erase "$(INTDIR)\MatchingObjects.obj"
	-@erase "$(INTDIR)\MatchingObjects.sbr"
	-@erase "$(INTDIR)\Modident.obj"
	-@erase "$(INTDIR)\Modident.sbr"
	-@erase "$(INTDIR)\Modidprp.obj"
	-@erase "$(INTDIR)\Modidprp.sbr"
	-@erase "$(INTDIR)\MultiPI.obj"
	-@erase "$(INTDIR)\MultiPI.sbr"
	-@erase "$(INTDIR)\MUSCROLL.OBJ"
	-@erase "$(INTDIR)\MUSCROLL.SBR"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.SBR"
	-@erase "$(INTDIR)\ObjekteDoppeln.obj"
	-@erase "$(INTDIR)\ObjekteDoppeln.sbr"
	-@erase "$(INTDIR)\ObjekteVereinigen.obj"
	-@erase "$(INTDIR)\ObjekteVereinigen.sbr"
	-@erase "$(INTDIR)\ObjGeomW.obj"
	-@erase "$(INTDIR)\ObjGeomW.sbr"
	-@erase "$(INTDIR)\opropcf.obj"
	-@erase "$(INTDIR)\opropcf.sbr"
	-@erase "$(INTDIR)\oprpfeat.obj"
	-@erase "$(INTDIR)\oprpfeat.sbr"
	-@erase "$(INTDIR)\OWNCOMBO.OBJ"
	-@erase "$(INTDIR)\OWNCOMBO.SBR"
	-@erase "$(INTDIR)\OWNLIST.OBJ"
	-@erase "$(INTDIR)\OWNLIST.SBR"
	-@erase "$(INTDIR)\OWNLISTE.OBJ"
	-@erase "$(INTDIR)\OWNLISTE.SBR"
	-@erase "$(INTDIR)\PRNTPARS.OBJ"
	-@erase "$(INTDIR)\PRNTPARS.SBR"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\Propname.obj"
	-@erase "$(INTDIR)\Propname.sbr"
	-@erase "$(INTDIR)\Propseq.obj"
	-@erase "$(INTDIR)\Propseq.sbr"
	-@erase "$(INTDIR)\queryfld.obj"
	-@erase "$(INTDIR)\queryfld.sbr"
	-@erase "$(INTDIR)\REGISTER.OBJ"
	-@erase "$(INTDIR)\REGISTER.SBR"
	-@erase "$(INTDIR)\RegisterExt.obj"
	-@erase "$(INTDIR)\RegisterExt.sbr"
	-@erase "$(INTDIR)\REGOBJ.OBJ"
	-@erase "$(INTDIR)\REGOBJ.SBR"
	-@erase "$(INTDIR)\regprop.obj"
	-@erase "$(INTDIR)\regprop.sbr"
	-@erase "$(INTDIR)\ROTATE.OBJ"
	-@erase "$(INTDIR)\ROTATE.SBR"
	-@erase "$(INTDIR)\ScriptPropAct.obj"
	-@erase "$(INTDIR)\ScriptPropAct.sbr"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selident.sbr"
	-@erase "$(INTDIR)\SELIDLST.OBJ"
	-@erase "$(INTDIR)\SELIDLST.SBR"
	-@erase "$(INTDIR)\selidlvc.obj"
	-@erase "$(INTDIR)\selidlvc.sbr"
	-@erase "$(INTDIR)\Selidprp.obj"
	-@erase "$(INTDIR)\Selidprp.sbr"
	-@erase "$(INTDIR)\Selobdlg.obj"
	-@erase "$(INTDIR)\Selobdlg.sbr"
	-@erase "$(INTDIR)\SelObjProp.obj"
	-@erase "$(INTDIR)\SelObjProp.sbr"
	-@erase "$(INTDIR)\SelObjPropDlg.obj"
	-@erase "$(INTDIR)\SelObjPropDlg.sbr"
	-@erase "$(INTDIR)\Selobwnd.obj"
	-@erase "$(INTDIR)\Selobwnd.sbr"
	-@erase "$(INTDIR)\SelOProp.obj"
	-@erase "$(INTDIR)\SelOProp.sbr"
	-@erase "$(INTDIR)\SelOPrpTree.obj"
	-@erase "$(INTDIR)\SelOPrpTree.sbr"
	-@erase "$(INTDIR)\SPINCTRL.OBJ"
	-@erase "$(INTDIR)\SPINCTRL.SBR"
	-@erase "$(INTDIR)\statimpl.obj"
	-@erase "$(INTDIR)\statimpl.sbr"
	-@erase "$(INTDIR)\STATUS.OBJ"
	-@erase "$(INTDIR)\STATUS.SBR"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\TextSearchEngine.obj"
	-@erase "$(INTDIR)\TextSearchEngine.sbr"
	-@erase "$(INTDIR)\trias03p.obj"
	-@erase "$(INTDIR)\trias03p.sbr"
	-@erase "$(INTDIR)\Trias323.res"
	-@erase "$(INTDIR)\trias323d.idb"
	-@erase "$(INTDIR)\trias323d.pch"
	-@erase "$(INTDIR)\trias323d.pdb"
	-@erase "$(INTDIR)\TriASTrans.obj"
	-@erase "$(INTDIR)\TriASTrans.sbr"
	-@erase "$(INTDIR)\txtsrchd.obj"
	-@erase "$(INTDIR)\txtsrchd.sbr"
	-@erase "$(INTDIR)\undocf.obj"
	-@erase "$(INTDIR)\undocf.sbr"
	-@erase "$(INTDIR)\UndoCreo.obj"
	-@erase "$(INTDIR)\UndoCreo.sbr"
	-@erase "$(INTDIR)\undodelo.obj"
	-@erase "$(INTDIR)\undodelo.sbr"
	-@erase "$(INTDIR)\undodelr.obj"
	-@erase "$(INTDIR)\undodelr.sbr"
	-@erase "$(INTDIR)\undodelt.obj"
	-@erase "$(INTDIR)\undodelt.sbr"
	-@erase "$(INTDIR)\undofeat.obj"
	-@erase "$(INTDIR)\undofeat.sbr"
	-@erase "$(INTDIR)\undohelp.obj"
	-@erase "$(INTDIR)\undohelp.sbr"
	-@erase "$(INTDIR)\undohwnd.obj"
	-@erase "$(INTDIR)\undohwnd.sbr"
	-@erase "$(INTDIR)\undomodi.obj"
	-@erase "$(INTDIR)\undomodi.sbr"
	-@erase "$(INTDIR)\undomodo.obj"
	-@erase "$(INTDIR)\undomodo.sbr"
	-@erase "$(INTDIR)\undomodr.obj"
	-@erase "$(INTDIR)\undomodr.sbr"
	-@erase "$(INTDIR)\undomodv.obj"
	-@erase "$(INTDIR)\undomodv.sbr"
	-@erase "$(INTDIR)\undopbd.obj"
	-@erase "$(INTDIR)\undopbd.sbr"
	-@erase "$(INTDIR)\undoredo.obj"
	-@erase "$(INTDIR)\undoredo.sbr"
	-@erase "$(INTDIR)\undotext.obj"
	-@erase "$(INTDIR)\undotext.sbr"
	-@erase "$(OUTDIR)\trias33d.dll"
	-@erase "$(OUTDIR)\trias33d.exp"
	-@erase "$(OUTDIR)\trias33d.ilk"
	-@erase "$(OUTDIR)\trias33d.lib"
	-@erase "$(OUTDIR)\trias33d.pdb"
	-@erase "$(OUTDIR)\TRIAS423.bsc"
	-@erase "..\lib32\trias33d.lib"
	-@erase ".\dlldata.c"
	-@erase ".\obj32\..\Debug4\TRiASHelper.tlb"
	-@erase ".\TRiASHelper.h"
	-@erase ".\TRiASHelper_i.c"
	-@erase ".\TRiASHelper_p.c"
	-@erase "c:\trias.mvc\trias209.deb\trias33d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\TRIAS323.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE" /FR /Fp"Debug.207/trias323d.pch" /Yu"trias03p.hxx" /Fd"Debug.207/trias323d.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D\
 "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/trias323d.pch" /Yu"trias03p.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/trias323d.pdb" /c 
CPP_OBJS=.\Debug.207/
CPP_SBRS=.\Debug.207/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "./obj32" /d "_DEBUG" /d "_OLDCATIDS"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /d "_DEBUG" /d\
 "_OLDCATIDS" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRIAS423.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bmpbtn.sbr" \
	"$(INTDIR)\cextreg.sbr" \
	"$(INTDIR)\CheckTreeView.sbr" \
	"$(INTDIR)\CLSFYPRP.SBR" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Dataobj.sbr" \
	"$(INTDIR)\DATATRAN.SBR" \
	"$(INTDIR)\dblcoord.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\DelObPrp.sbr" \
	"$(INTDIR)\DstObDlg.sbr" \
	"$(INTDIR)\DstObWnd.sbr" \
	"$(INTDIR)\Enumonr.sbr" \
	"$(INTDIR)\enumundo.sbr" \
	"$(INTDIR)\GenTextDlg.sbr" \
	"$(INTDIR)\GenTextPropAct.sbr" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\Idataobj.sbr" \
	"$(INTDIR)\Ienumfe.sbr" \
	"$(INTDIR)\ImportDataDlg.sbr" \
	"$(INTDIR)\ImportProp.sbr" \
	"$(INTDIR)\InPlaceCombo.sbr" \
	"$(INTDIR)\INTOPROP.SBR" \
	"$(INTDIR)\JUSTIFY.SBR" \
	"$(INTDIR)\LIBMAIN3.SBR" \
	"$(INTDIR)\LISTHSCR.SBR" \
	"$(INTDIR)\MatchingObjects.sbr" \
	"$(INTDIR)\Modident.sbr" \
	"$(INTDIR)\Modidprp.sbr" \
	"$(INTDIR)\MultiPI.sbr" \
	"$(INTDIR)\MUSCROLL.SBR" \
	"$(INTDIR)\NUMEDIT.SBR" \
	"$(INTDIR)\ObjekteDoppeln.sbr" \
	"$(INTDIR)\ObjekteVereinigen.sbr" \
	"$(INTDIR)\ObjGeomW.sbr" \
	"$(INTDIR)\opropcf.sbr" \
	"$(INTDIR)\oprpfeat.sbr" \
	"$(INTDIR)\OWNCOMBO.SBR" \
	"$(INTDIR)\OWNLIST.SBR" \
	"$(INTDIR)\OWNLISTE.SBR" \
	"$(INTDIR)\PRNTPARS.SBR" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\Propname.sbr" \
	"$(INTDIR)\Propseq.sbr" \
	"$(INTDIR)\queryfld.sbr" \
	"$(INTDIR)\REGISTER.SBR" \
	"$(INTDIR)\RegisterExt.sbr" \
	"$(INTDIR)\REGOBJ.SBR" \
	"$(INTDIR)\regprop.sbr" \
	"$(INTDIR)\ROTATE.SBR" \
	"$(INTDIR)\ScriptPropAct.sbr" \
	"$(INTDIR)\Selident.sbr" \
	"$(INTDIR)\SELIDLST.SBR" \
	"$(INTDIR)\selidlvc.sbr" \
	"$(INTDIR)\Selidprp.sbr" \
	"$(INTDIR)\Selobdlg.sbr" \
	"$(INTDIR)\SelObjProp.sbr" \
	"$(INTDIR)\SelObjPropDlg.sbr" \
	"$(INTDIR)\Selobwnd.sbr" \
	"$(INTDIR)\SelOProp.sbr" \
	"$(INTDIR)\SelOPrpTree.sbr" \
	"$(INTDIR)\SPINCTRL.SBR" \
	"$(INTDIR)\statimpl.sbr" \
	"$(INTDIR)\STATUS.SBR" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\TextSearchEngine.sbr" \
	"$(INTDIR)\trias03p.sbr" \
	"$(INTDIR)\TriASTrans.sbr" \
	"$(INTDIR)\txtsrchd.sbr" \
	"$(INTDIR)\undocf.sbr" \
	"$(INTDIR)\UndoCreo.sbr" \
	"$(INTDIR)\undodelo.sbr" \
	"$(INTDIR)\undodelr.sbr" \
	"$(INTDIR)\undodelt.sbr" \
	"$(INTDIR)\undofeat.sbr" \
	"$(INTDIR)\undohelp.sbr" \
	"$(INTDIR)\undohwnd.sbr" \
	"$(INTDIR)\undomodi.sbr" \
	"$(INTDIR)\undomodo.sbr" \
	"$(INTDIR)\undomodr.sbr" \
	"$(INTDIR)\undomodv.sbr" \
	"$(INTDIR)\undopbd.sbr" \
	"$(INTDIR)\undoredo.sbr" \
	"$(INTDIR)\undotext.sbr"

"$(OUTDIR)\TRIAS423.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib ospace2d.lib stdcppd.lib largeint.lib TriasTld.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"./obj32\rights.exe" /out:"Debug.207/trias33d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib ospace2d.lib\
 stdcppd.lib largeint.lib TriasTld.lib comctl32.lib muscrl32.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib\
 /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/trias33d.pdb" /debug\
 /machine:I386 /def:".\obj32\trias33d207.def" /stub:"./obj32\rights.exe"\
 /out:"$(OUTDIR)/trias33d.dll" /implib:"$(OUTDIR)/trias33d.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\trias33d207.def"
LINK32_OBJS= \
	"$(INTDIR)\bmpbtn.obj" \
	"$(INTDIR)\cextreg.obj" \
	"$(INTDIR)\CheckTreeView.obj" \
	"$(INTDIR)\CLSFYPRP.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DATATRAN.OBJ" \
	"$(INTDIR)\dblcoord.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\DelObPrp.obj" \
	"$(INTDIR)\DstObDlg.obj" \
	"$(INTDIR)\DstObWnd.obj" \
	"$(INTDIR)\Enumonr.obj" \
	"$(INTDIR)\enumundo.obj" \
	"$(INTDIR)\GenTextDlg.obj" \
	"$(INTDIR)\GenTextPropAct.obj" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\Idataobj.obj" \
	"$(INTDIR)\Ienumfe.obj" \
	"$(INTDIR)\ImportDataDlg.obj" \
	"$(INTDIR)\ImportProp.obj" \
	"$(INTDIR)\InPlaceCombo.obj" \
	"$(INTDIR)\INTOPROP.OBJ" \
	"$(INTDIR)\JUSTIFY.OBJ" \
	"$(INTDIR)\LIBMAIN3.OBJ" \
	"$(INTDIR)\LISTHSCR.OBJ" \
	"$(INTDIR)\MatchingObjects.obj" \
	"$(INTDIR)\Modident.obj" \
	"$(INTDIR)\Modidprp.obj" \
	"$(INTDIR)\MultiPI.obj" \
	"$(INTDIR)\MUSCROLL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\ObjekteDoppeln.obj" \
	"$(INTDIR)\ObjekteVereinigen.obj" \
	"$(INTDIR)\ObjGeomW.obj" \
	"$(INTDIR)\opropcf.obj" \
	"$(INTDIR)\oprpfeat.obj" \
	"$(INTDIR)\OWNCOMBO.OBJ" \
	"$(INTDIR)\OWNLIST.OBJ" \
	"$(INTDIR)\OWNLISTE.OBJ" \
	"$(INTDIR)\PRNTPARS.OBJ" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Propname.obj" \
	"$(INTDIR)\Propseq.obj" \
	"$(INTDIR)\queryfld.obj" \
	"$(INTDIR)\REGISTER.OBJ" \
	"$(INTDIR)\RegisterExt.obj" \
	"$(INTDIR)\REGOBJ.OBJ" \
	"$(INTDIR)\regprop.obj" \
	"$(INTDIR)\ROTATE.OBJ" \
	"$(INTDIR)\ScriptPropAct.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\SELIDLST.OBJ" \
	"$(INTDIR)\selidlvc.obj" \
	"$(INTDIR)\Selidprp.obj" \
	"$(INTDIR)\Selobdlg.obj" \
	"$(INTDIR)\SelObjProp.obj" \
	"$(INTDIR)\SelObjPropDlg.obj" \
	"$(INTDIR)\Selobwnd.obj" \
	"$(INTDIR)\SelOProp.obj" \
	"$(INTDIR)\SelOPrpTree.obj" \
	"$(INTDIR)\SPINCTRL.OBJ" \
	"$(INTDIR)\statimpl.obj" \
	"$(INTDIR)\STATUS.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TextSearchEngine.obj" \
	"$(INTDIR)\trias03p.obj" \
	"$(INTDIR)\Trias323.res" \
	"$(INTDIR)\TriASTrans.obj" \
	"$(INTDIR)\txtsrchd.obj" \
	"$(INTDIR)\undocf.obj" \
	"$(INTDIR)\UndoCreo.obj" \
	"$(INTDIR)\undodelo.obj" \
	"$(INTDIR)\undodelr.obj" \
	"$(INTDIR)\undodelt.obj" \
	"$(INTDIR)\undofeat.obj" \
	"$(INTDIR)\undohelp.obj" \
	"$(INTDIR)\undohwnd.obj" \
	"$(INTDIR)\undomodi.obj" \
	"$(INTDIR)\undomodo.obj" \
	"$(INTDIR)\undomodr.obj" \
	"$(INTDIR)\undomodv.obj" \
	"$(INTDIR)\undopbd.obj" \
	"$(INTDIR)\undoredo.obj" \
	"$(INTDIR)\undotext.obj"

"$(OUTDIR)\trias33d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug.207
TargetPath=.\Debug.207\trias33d.dll
TargetName=trias33d
InputPath=.\Debug.207\trias33d.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy "$(TargetPath)" c:\trias.mvc\trias20.deb \
	rem copy "$(OutDir)\$(TargetName).lib" \triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias209.deb\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Trias323"
# PROP BASE Intermediate_Dir "Trias323"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Trias323"
# PROP Intermediate_Dir "Trias323"
# PROP Target_Dir ""
OUTDIR=.\Trias323
INTDIR=.\Trias323
# Begin Custom Macros
TargetName=trias33d
# End Custom Macros

ALL : ".\Debug4\trias33d.dll" "$(OUTDIR)\TRIAS423.bsc"\
 "c:\trias.mvc\trias200\trias33d.dll" "e:\triasdev.mvc\lib32\trias33d.lib"\
 ".\TRiASHelper_i.c"

CLEAN : 
	-@erase "$(INTDIR)\bmpbtn.obj"
	-@erase "$(INTDIR)\bmpbtn.sbr"
	-@erase "$(INTDIR)\cextreg.obj"
	-@erase "$(INTDIR)\cextreg.sbr"
	-@erase "$(INTDIR)\CheckTreeView.obj"
	-@erase "$(INTDIR)\CheckTreeView.sbr"
	-@erase "$(INTDIR)\CLSFYPRP.OBJ"
	-@erase "$(INTDIR)\CLSFYPRP.SBR"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\Dataobj.sbr"
	-@erase "$(INTDIR)\DATATRAN.OBJ"
	-@erase "$(INTDIR)\DATATRAN.SBR"
	-@erase "$(INTDIR)\dblcoord.obj"
	-@erase "$(INTDIR)\dblcoord.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
	-@erase "$(INTDIR)\DelObPrp.obj"
	-@erase "$(INTDIR)\DelObPrp.sbr"
	-@erase "$(INTDIR)\DLLDATAX.OBJ"
	-@erase "$(INTDIR)\DLLDATAX.SBR"
	-@erase "$(INTDIR)\DstObDlg.obj"
	-@erase "$(INTDIR)\DstObDlg.sbr"
	-@erase "$(INTDIR)\DstObWnd.obj"
	-@erase "$(INTDIR)\DstObWnd.sbr"
	-@erase "$(INTDIR)\Enumonr.obj"
	-@erase "$(INTDIR)\Enumonr.sbr"
	-@erase "$(INTDIR)\enumundo.obj"
	-@erase "$(INTDIR)\enumundo.sbr"
	-@erase "$(INTDIR)\GenTextDlg.obj"
	-@erase "$(INTDIR)\GenTextDlg.sbr"
	-@erase "$(INTDIR)\GenTextPropAct.obj"
	-@erase "$(INTDIR)\GenTextPropAct.sbr"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\Idataobj.obj"
	-@erase "$(INTDIR)\Idataobj.sbr"
	-@erase "$(INTDIR)\Ienumfe.obj"
	-@erase "$(INTDIR)\Ienumfe.sbr"
	-@erase "$(INTDIR)\ImportDataDlg.obj"
	-@erase "$(INTDIR)\ImportDataDlg.sbr"
	-@erase "$(INTDIR)\ImportProp.obj"
	-@erase "$(INTDIR)\ImportProp.sbr"
	-@erase "$(INTDIR)\InPlaceCombo.obj"
	-@erase "$(INTDIR)\InPlaceCombo.sbr"
	-@erase "$(INTDIR)\INTOPROP.OBJ"
	-@erase "$(INTDIR)\INTOPROP.SBR"
	-@erase "$(INTDIR)\JUSTIFY.OBJ"
	-@erase "$(INTDIR)\JUSTIFY.SBR"
	-@erase "$(INTDIR)\LIBMAIN3.OBJ"
	-@erase "$(INTDIR)\LIBMAIN3.SBR"
	-@erase "$(INTDIR)\LISTHSCR.OBJ"
	-@erase "$(INTDIR)\LISTHSCR.SBR"
	-@erase "$(INTDIR)\MatchingObjects.obj"
	-@erase "$(INTDIR)\MatchingObjects.sbr"
	-@erase "$(INTDIR)\Modident.obj"
	-@erase "$(INTDIR)\Modident.sbr"
	-@erase "$(INTDIR)\Modidprp.obj"
	-@erase "$(INTDIR)\Modidprp.sbr"
	-@erase "$(INTDIR)\MultiPI.obj"
	-@erase "$(INTDIR)\MultiPI.sbr"
	-@erase "$(INTDIR)\MUSCROLL.OBJ"
	-@erase "$(INTDIR)\MUSCROLL.SBR"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.SBR"
	-@erase "$(INTDIR)\ObjekteDoppeln.obj"
	-@erase "$(INTDIR)\ObjekteDoppeln.sbr"
	-@erase "$(INTDIR)\ObjekteVereinigen.obj"
	-@erase "$(INTDIR)\ObjekteVereinigen.sbr"
	-@erase "$(INTDIR)\ObjGeomW.obj"
	-@erase "$(INTDIR)\ObjGeomW.sbr"
	-@erase "$(INTDIR)\opropcf.obj"
	-@erase "$(INTDIR)\opropcf.sbr"
	-@erase "$(INTDIR)\oprpfeat.obj"
	-@erase "$(INTDIR)\oprpfeat.sbr"
	-@erase "$(INTDIR)\OWNCOMBO.OBJ"
	-@erase "$(INTDIR)\OWNCOMBO.SBR"
	-@erase "$(INTDIR)\OWNLIST.OBJ"
	-@erase "$(INTDIR)\OWNLIST.SBR"
	-@erase "$(INTDIR)\OWNLISTE.OBJ"
	-@erase "$(INTDIR)\OWNLISTE.SBR"
	-@erase "$(INTDIR)\PRNTPARS.OBJ"
	-@erase "$(INTDIR)\PRNTPARS.SBR"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\Propname.obj"
	-@erase "$(INTDIR)\Propname.sbr"
	-@erase "$(INTDIR)\Propseq.obj"
	-@erase "$(INTDIR)\Propseq.sbr"
	-@erase "$(INTDIR)\queryfld.obj"
	-@erase "$(INTDIR)\queryfld.sbr"
	-@erase "$(INTDIR)\REGISTER.OBJ"
	-@erase "$(INTDIR)\REGISTER.SBR"
	-@erase "$(INTDIR)\RegisterExt.obj"
	-@erase "$(INTDIR)\RegisterExt.sbr"
	-@erase "$(INTDIR)\REGOBJ.OBJ"
	-@erase "$(INTDIR)\REGOBJ.SBR"
	-@erase "$(INTDIR)\regprop.obj"
	-@erase "$(INTDIR)\regprop.sbr"
	-@erase "$(INTDIR)\ROTATE.OBJ"
	-@erase "$(INTDIR)\ROTATE.SBR"
	-@erase "$(INTDIR)\ScriptPropAct.obj"
	-@erase "$(INTDIR)\ScriptPropAct.sbr"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selident.sbr"
	-@erase "$(INTDIR)\SELIDLST.OBJ"
	-@erase "$(INTDIR)\SELIDLST.SBR"
	-@erase "$(INTDIR)\selidlvc.obj"
	-@erase "$(INTDIR)\selidlvc.sbr"
	-@erase "$(INTDIR)\Selidprp.obj"
	-@erase "$(INTDIR)\Selidprp.sbr"
	-@erase "$(INTDIR)\Selobdlg.obj"
	-@erase "$(INTDIR)\Selobdlg.sbr"
	-@erase "$(INTDIR)\SelObjProp.obj"
	-@erase "$(INTDIR)\SelObjProp.sbr"
	-@erase "$(INTDIR)\SelObjPropDlg.obj"
	-@erase "$(INTDIR)\SelObjPropDlg.sbr"
	-@erase "$(INTDIR)\Selobwnd.obj"
	-@erase "$(INTDIR)\Selobwnd.sbr"
	-@erase "$(INTDIR)\SelOProp.obj"
	-@erase "$(INTDIR)\SelOProp.sbr"
	-@erase "$(INTDIR)\SelOPrpTree.obj"
	-@erase "$(INTDIR)\SelOPrpTree.sbr"
	-@erase "$(INTDIR)\SPINCTRL.OBJ"
	-@erase "$(INTDIR)\SPINCTRL.SBR"
	-@erase "$(INTDIR)\statimpl.obj"
	-@erase "$(INTDIR)\statimpl.sbr"
	-@erase "$(INTDIR)\STATUS.OBJ"
	-@erase "$(INTDIR)\STATUS.SBR"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\TextSearchEngine.obj"
	-@erase "$(INTDIR)\TextSearchEngine.sbr"
	-@erase "$(INTDIR)\trias03p.obj"
	-@erase "$(INTDIR)\trias03p.sbr"
	-@erase "$(INTDIR)\Trias323.res"
	-@erase "$(INTDIR)\TriASTrans.obj"
	-@erase "$(INTDIR)\TriASTrans.sbr"
	-@erase "$(INTDIR)\txtsrchd.obj"
	-@erase "$(INTDIR)\txtsrchd.sbr"
	-@erase "$(INTDIR)\undocf.obj"
	-@erase "$(INTDIR)\undocf.sbr"
	-@erase "$(INTDIR)\UndoCreo.obj"
	-@erase "$(INTDIR)\UndoCreo.sbr"
	-@erase "$(INTDIR)\undodelo.obj"
	-@erase "$(INTDIR)\undodelo.sbr"
	-@erase "$(INTDIR)\undodelr.obj"
	-@erase "$(INTDIR)\undodelr.sbr"
	-@erase "$(INTDIR)\undodelt.obj"
	-@erase "$(INTDIR)\undodelt.sbr"
	-@erase "$(INTDIR)\undofeat.obj"
	-@erase "$(INTDIR)\undofeat.sbr"
	-@erase "$(INTDIR)\undohelp.obj"
	-@erase "$(INTDIR)\undohelp.sbr"
	-@erase "$(INTDIR)\undohwnd.obj"
	-@erase "$(INTDIR)\undohwnd.sbr"
	-@erase "$(INTDIR)\undomodi.obj"
	-@erase "$(INTDIR)\undomodi.sbr"
	-@erase "$(INTDIR)\undomodo.obj"
	-@erase "$(INTDIR)\undomodo.sbr"
	-@erase "$(INTDIR)\undomodr.obj"
	-@erase "$(INTDIR)\undomodr.sbr"
	-@erase "$(INTDIR)\undomodv.obj"
	-@erase "$(INTDIR)\undomodv.sbr"
	-@erase "$(INTDIR)\undopbd.obj"
	-@erase "$(INTDIR)\undopbd.sbr"
	-@erase "$(INTDIR)\undoredo.obj"
	-@erase "$(INTDIR)\undoredo.sbr"
	-@erase "$(INTDIR)\undotext.obj"
	-@erase "$(INTDIR)\undotext.sbr"
	-@erase "$(OUTDIR)\trias33d.exp"
	-@erase "$(OUTDIR)\trias33d.lib"
	-@erase "$(OUTDIR)\trias33d.pdb"
	-@erase "$(OUTDIR)\TRIAS423.bsc"
	-@erase ".\Debug4\trias323d.idb"
	-@erase ".\Debug4\trias323d.pch"
	-@erase ".\Debug4\trias323d.pdb"
	-@erase ".\Debug4\trias33d.dll"
	-@erase ".\Debug4\trias33d.ilk"
	-@erase ".\dlldata.c"
	-@erase ".\obj32\..\Debug4\TRiASHelper.tlb"
	-@erase ".\TRiASHelper.h"
	-@erase ".\TRiASHelper_i.c"
	-@erase ".\TRiASHelper_p.c"
	-@erase "c:\trias.mvc\trias200\trias33d.dll"
	-@erase "e:\triasdev.mvc\lib32\trias33d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_MERGE_PROXYSTUB" /D "_WIN32_DCOM" /D "_ATL_TRIAS_REGISTER" /FR /Fp"Debug4/trias323d.pch" /Yu"trias03p.hxx" /Fd"Debug4/trias323d.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_MERGE_PROXYSTUB" /D "_WIN32_DCOM" /D "_ATL_TRIAS_REGISTER" /FR /Fp"Debug4/trias323d.pch" /Yu"trias03p.hxx" /Fd"Debug4/trias323d.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D\
 "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_MERGE_PROXYSTUB" /D\
 "_WIN32_DCOM" /D "_ATL_TRIAS_REGISTER" /FR"$(INTDIR)/"\
 /Fp"Debug4/trias323d.pch" /Yu"trias03p.hxx" /Fo"$(INTDIR)/"\
 /Fd"Debug4/trias323d.pdb" /c 
CPP_OBJS=.\Trias323/
CPP_SBRS=.\Trias323/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /i "./obj32" /d "_DEBUG"
# ADD RSC /l 0x407 /i "./obj32" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRIAS423.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bmpbtn.sbr" \
	"$(INTDIR)\cextreg.sbr" \
	"$(INTDIR)\CheckTreeView.sbr" \
	"$(INTDIR)\CLSFYPRP.SBR" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Dataobj.sbr" \
	"$(INTDIR)\DATATRAN.SBR" \
	"$(INTDIR)\dblcoord.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\DelObPrp.sbr" \
	"$(INTDIR)\DLLDATAX.SBR" \
	"$(INTDIR)\DstObDlg.sbr" \
	"$(INTDIR)\DstObWnd.sbr" \
	"$(INTDIR)\Enumonr.sbr" \
	"$(INTDIR)\enumundo.sbr" \
	"$(INTDIR)\GenTextDlg.sbr" \
	"$(INTDIR)\GenTextPropAct.sbr" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\Idataobj.sbr" \
	"$(INTDIR)\Ienumfe.sbr" \
	"$(INTDIR)\ImportDataDlg.sbr" \
	"$(INTDIR)\ImportProp.sbr" \
	"$(INTDIR)\InPlaceCombo.sbr" \
	"$(INTDIR)\INTOPROP.SBR" \
	"$(INTDIR)\JUSTIFY.SBR" \
	"$(INTDIR)\LIBMAIN3.SBR" \
	"$(INTDIR)\LISTHSCR.SBR" \
	"$(INTDIR)\MatchingObjects.sbr" \
	"$(INTDIR)\Modident.sbr" \
	"$(INTDIR)\Modidprp.sbr" \
	"$(INTDIR)\MultiPI.sbr" \
	"$(INTDIR)\MUSCROLL.SBR" \
	"$(INTDIR)\NUMEDIT.SBR" \
	"$(INTDIR)\ObjekteDoppeln.sbr" \
	"$(INTDIR)\ObjekteVereinigen.sbr" \
	"$(INTDIR)\ObjGeomW.sbr" \
	"$(INTDIR)\opropcf.sbr" \
	"$(INTDIR)\oprpfeat.sbr" \
	"$(INTDIR)\OWNCOMBO.SBR" \
	"$(INTDIR)\OWNLIST.SBR" \
	"$(INTDIR)\OWNLISTE.SBR" \
	"$(INTDIR)\PRNTPARS.SBR" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\Propname.sbr" \
	"$(INTDIR)\Propseq.sbr" \
	"$(INTDIR)\queryfld.sbr" \
	"$(INTDIR)\REGISTER.SBR" \
	"$(INTDIR)\RegisterExt.sbr" \
	"$(INTDIR)\REGOBJ.SBR" \
	"$(INTDIR)\regprop.sbr" \
	"$(INTDIR)\ROTATE.SBR" \
	"$(INTDIR)\ScriptPropAct.sbr" \
	"$(INTDIR)\Selident.sbr" \
	"$(INTDIR)\SELIDLST.SBR" \
	"$(INTDIR)\selidlvc.sbr" \
	"$(INTDIR)\Selidprp.sbr" \
	"$(INTDIR)\Selobdlg.sbr" \
	"$(INTDIR)\SelObjProp.sbr" \
	"$(INTDIR)\SelObjPropDlg.sbr" \
	"$(INTDIR)\Selobwnd.sbr" \
	"$(INTDIR)\SelOProp.sbr" \
	"$(INTDIR)\SelOPrpTree.sbr" \
	"$(INTDIR)\SPINCTRL.SBR" \
	"$(INTDIR)\statimpl.sbr" \
	"$(INTDIR)\STATUS.SBR" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\TextSearchEngine.sbr" \
	"$(INTDIR)\trias03p.sbr" \
	"$(INTDIR)\TriASTrans.sbr" \
	"$(INTDIR)\txtsrchd.sbr" \
	"$(INTDIR)\undocf.sbr" \
	"$(INTDIR)\UndoCreo.sbr" \
	"$(INTDIR)\undodelo.sbr" \
	"$(INTDIR)\undodelr.sbr" \
	"$(INTDIR)\undodelt.sbr" \
	"$(INTDIR)\undofeat.sbr" \
	"$(INTDIR)\undohelp.sbr" \
	"$(INTDIR)\undohwnd.sbr" \
	"$(INTDIR)\undomodi.sbr" \
	"$(INTDIR)\undomodo.sbr" \
	"$(INTDIR)\undomodr.sbr" \
	"$(INTDIR)\undomodv.sbr" \
	"$(INTDIR)\undopbd.sbr" \
	"$(INTDIR)\undoredo.sbr" \
	"$(INTDIR)\undotext.sbr"

"$(OUTDIR)\TRIAS423.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib ospace2d.lib stdcppd.lib largeint.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"./obj32\rights.exe" /out:"Debug4/trias33d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib ospace2d.lib stdcppd.lib largeint.lib TriasTld.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"./obj32\rights.exe" /out:"Debug4/trias33d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib ospace2d.lib\
 stdcppd.lib largeint.lib TriasTld.lib comctl32.lib muscrl32.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib\
 /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/trias33d.pdb" /debug\
 /machine:I386 /def:".\obj32\TRIAS33D.DEF" /stub:"./obj32\rights.exe"\
 /out:"Debug4/trias33d.dll" /implib:"$(OUTDIR)/trias33d.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRIAS33D.DEF"
LINK32_OBJS= \
	"$(INTDIR)\bmpbtn.obj" \
	"$(INTDIR)\cextreg.obj" \
	"$(INTDIR)\CheckTreeView.obj" \
	"$(INTDIR)\CLSFYPRP.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DATATRAN.OBJ" \
	"$(INTDIR)\dblcoord.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\DelObPrp.obj" \
	"$(INTDIR)\DLLDATAX.OBJ" \
	"$(INTDIR)\DstObDlg.obj" \
	"$(INTDIR)\DstObWnd.obj" \
	"$(INTDIR)\Enumonr.obj" \
	"$(INTDIR)\enumundo.obj" \
	"$(INTDIR)\GenTextDlg.obj" \
	"$(INTDIR)\GenTextPropAct.obj" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\Idataobj.obj" \
	"$(INTDIR)\Ienumfe.obj" \
	"$(INTDIR)\ImportDataDlg.obj" \
	"$(INTDIR)\ImportProp.obj" \
	"$(INTDIR)\InPlaceCombo.obj" \
	"$(INTDIR)\INTOPROP.OBJ" \
	"$(INTDIR)\JUSTIFY.OBJ" \
	"$(INTDIR)\LIBMAIN3.OBJ" \
	"$(INTDIR)\LISTHSCR.OBJ" \
	"$(INTDIR)\MatchingObjects.obj" \
	"$(INTDIR)\Modident.obj" \
	"$(INTDIR)\Modidprp.obj" \
	"$(INTDIR)\MultiPI.obj" \
	"$(INTDIR)\MUSCROLL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\ObjekteDoppeln.obj" \
	"$(INTDIR)\ObjekteVereinigen.obj" \
	"$(INTDIR)\ObjGeomW.obj" \
	"$(INTDIR)\opropcf.obj" \
	"$(INTDIR)\oprpfeat.obj" \
	"$(INTDIR)\OWNCOMBO.OBJ" \
	"$(INTDIR)\OWNLIST.OBJ" \
	"$(INTDIR)\OWNLISTE.OBJ" \
	"$(INTDIR)\PRNTPARS.OBJ" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Propname.obj" \
	"$(INTDIR)\Propseq.obj" \
	"$(INTDIR)\queryfld.obj" \
	"$(INTDIR)\REGISTER.OBJ" \
	"$(INTDIR)\RegisterExt.obj" \
	"$(INTDIR)\REGOBJ.OBJ" \
	"$(INTDIR)\regprop.obj" \
	"$(INTDIR)\ROTATE.OBJ" \
	"$(INTDIR)\ScriptPropAct.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\SELIDLST.OBJ" \
	"$(INTDIR)\selidlvc.obj" \
	"$(INTDIR)\Selidprp.obj" \
	"$(INTDIR)\Selobdlg.obj" \
	"$(INTDIR)\SelObjProp.obj" \
	"$(INTDIR)\SelObjPropDlg.obj" \
	"$(INTDIR)\Selobwnd.obj" \
	"$(INTDIR)\SelOProp.obj" \
	"$(INTDIR)\SelOPrpTree.obj" \
	"$(INTDIR)\SPINCTRL.OBJ" \
	"$(INTDIR)\statimpl.obj" \
	"$(INTDIR)\STATUS.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TextSearchEngine.obj" \
	"$(INTDIR)\trias03p.obj" \
	"$(INTDIR)\Trias323.res" \
	"$(INTDIR)\TriASTrans.obj" \
	"$(INTDIR)\txtsrchd.obj" \
	"$(INTDIR)\undocf.obj" \
	"$(INTDIR)\UndoCreo.obj" \
	"$(INTDIR)\undodelo.obj" \
	"$(INTDIR)\undodelr.obj" \
	"$(INTDIR)\undodelt.obj" \
	"$(INTDIR)\undofeat.obj" \
	"$(INTDIR)\undohelp.obj" \
	"$(INTDIR)\undohwnd.obj" \
	"$(INTDIR)\undomodi.obj" \
	"$(INTDIR)\undomodo.obj" \
	"$(INTDIR)\undomodr.obj" \
	"$(INTDIR)\undomodv.obj" \
	"$(INTDIR)\undopbd.obj" \
	"$(INTDIR)\undoredo.obj" \
	"$(INTDIR)\undotext.obj"

".\Debug4\trias33d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Trias323
TargetPath=.\Debug4\trias33d.dll
TargetName=trias33d
InputPath=.\Debug4\trias33d.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" c:\trias.mvc\trias200 \
	copy "$(OutDir)\$(TargetName).lib" e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Trias320"
# PROP BASE Intermediate_Dir "Trias320"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Pseudo"
# PROP Intermediate_Dir "Pseudo"
# PROP Target_Dir ""
OUTDIR=.\Pseudo
INTDIR=.\Pseudo
# Begin Custom Macros
TargetName=Trias323
# End Custom Macros

ALL : "$(OUTDIR)\Trias323.dll" "$(OUTDIR)\TRIAS423.bsc"\
 "c:\trias.mvc\trias200.rel\Trias323.dll" ".\TRiASHelper_i.c" ".\dlldata.c"\
 ".\TRiASHelper_p.c"

CLEAN : 
	-@erase "$(INTDIR)\bmpbtn.obj"
	-@erase "$(INTDIR)\bmpbtn.sbr"
	-@erase "$(INTDIR)\cextreg.obj"
	-@erase "$(INTDIR)\cextreg.sbr"
	-@erase "$(INTDIR)\CheckTreeView.obj"
	-@erase "$(INTDIR)\CheckTreeView.sbr"
	-@erase "$(INTDIR)\CLSFYPRP.OBJ"
	-@erase "$(INTDIR)\CLSFYPRP.SBR"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\Dataobj.sbr"
	-@erase "$(INTDIR)\DATATRAN.OBJ"
	-@erase "$(INTDIR)\DATATRAN.SBR"
	-@erase "$(INTDIR)\dblcoord.obj"
	-@erase "$(INTDIR)\dblcoord.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
	-@erase "$(INTDIR)\DelObPrp.obj"
	-@erase "$(INTDIR)\DelObPrp.sbr"
	-@erase "$(INTDIR)\DstObDlg.obj"
	-@erase "$(INTDIR)\DstObDlg.sbr"
	-@erase "$(INTDIR)\DstObWnd.obj"
	-@erase "$(INTDIR)\DstObWnd.sbr"
	-@erase "$(INTDIR)\Enumonr.obj"
	-@erase "$(INTDIR)\Enumonr.sbr"
	-@erase "$(INTDIR)\enumundo.obj"
	-@erase "$(INTDIR)\enumundo.sbr"
	-@erase "$(INTDIR)\GenTextDlg.obj"
	-@erase "$(INTDIR)\GenTextDlg.sbr"
	-@erase "$(INTDIR)\GenTextPropAct.obj"
	-@erase "$(INTDIR)\GenTextPropAct.sbr"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\Idataobj.obj"
	-@erase "$(INTDIR)\Idataobj.sbr"
	-@erase "$(INTDIR)\Ienumfe.obj"
	-@erase "$(INTDIR)\Ienumfe.sbr"
	-@erase "$(INTDIR)\ImportDataDlg.obj"
	-@erase "$(INTDIR)\ImportDataDlg.sbr"
	-@erase "$(INTDIR)\ImportProp.obj"
	-@erase "$(INTDIR)\ImportProp.sbr"
	-@erase "$(INTDIR)\InPlaceCombo.obj"
	-@erase "$(INTDIR)\InPlaceCombo.sbr"
	-@erase "$(INTDIR)\INTOPROP.OBJ"
	-@erase "$(INTDIR)\INTOPROP.SBR"
	-@erase "$(INTDIR)\JUSTIFY.OBJ"
	-@erase "$(INTDIR)\JUSTIFY.SBR"
	-@erase "$(INTDIR)\LIBMAIN3.OBJ"
	-@erase "$(INTDIR)\LIBMAIN3.SBR"
	-@erase "$(INTDIR)\LISTHSCR.OBJ"
	-@erase "$(INTDIR)\LISTHSCR.SBR"
	-@erase "$(INTDIR)\MatchingObjects.obj"
	-@erase "$(INTDIR)\MatchingObjects.sbr"
	-@erase "$(INTDIR)\Modident.obj"
	-@erase "$(INTDIR)\Modident.sbr"
	-@erase "$(INTDIR)\Modidprp.obj"
	-@erase "$(INTDIR)\Modidprp.sbr"
	-@erase "$(INTDIR)\MultiPI.obj"
	-@erase "$(INTDIR)\MultiPI.sbr"
	-@erase "$(INTDIR)\MUSCROLL.OBJ"
	-@erase "$(INTDIR)\MUSCROLL.SBR"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.SBR"
	-@erase "$(INTDIR)\ObjekteDoppeln.obj"
	-@erase "$(INTDIR)\ObjekteDoppeln.sbr"
	-@erase "$(INTDIR)\ObjekteVereinigen.obj"
	-@erase "$(INTDIR)\ObjekteVereinigen.sbr"
	-@erase "$(INTDIR)\ObjGeomW.obj"
	-@erase "$(INTDIR)\ObjGeomW.sbr"
	-@erase "$(INTDIR)\opropcf.obj"
	-@erase "$(INTDIR)\opropcf.sbr"
	-@erase "$(INTDIR)\oprpfeat.obj"
	-@erase "$(INTDIR)\oprpfeat.sbr"
	-@erase "$(INTDIR)\OWNCOMBO.OBJ"
	-@erase "$(INTDIR)\OWNCOMBO.SBR"
	-@erase "$(INTDIR)\OWNLIST.OBJ"
	-@erase "$(INTDIR)\OWNLIST.SBR"
	-@erase "$(INTDIR)\OWNLISTE.OBJ"
	-@erase "$(INTDIR)\OWNLISTE.SBR"
	-@erase "$(INTDIR)\PRNTPARS.OBJ"
	-@erase "$(INTDIR)\PRNTPARS.SBR"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\Propname.obj"
	-@erase "$(INTDIR)\Propname.sbr"
	-@erase "$(INTDIR)\Propseq.obj"
	-@erase "$(INTDIR)\Propseq.sbr"
	-@erase "$(INTDIR)\queryfld.obj"
	-@erase "$(INTDIR)\queryfld.sbr"
	-@erase "$(INTDIR)\REGISTER.OBJ"
	-@erase "$(INTDIR)\REGISTER.SBR"
	-@erase "$(INTDIR)\RegisterExt.obj"
	-@erase "$(INTDIR)\RegisterExt.sbr"
	-@erase "$(INTDIR)\REGOBJ.OBJ"
	-@erase "$(INTDIR)\REGOBJ.SBR"
	-@erase "$(INTDIR)\regprop.obj"
	-@erase "$(INTDIR)\regprop.sbr"
	-@erase "$(INTDIR)\ROTATE.OBJ"
	-@erase "$(INTDIR)\ROTATE.SBR"
	-@erase "$(INTDIR)\ScriptPropAct.obj"
	-@erase "$(INTDIR)\ScriptPropAct.sbr"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selident.sbr"
	-@erase "$(INTDIR)\SELIDLST.OBJ"
	-@erase "$(INTDIR)\SELIDLST.SBR"
	-@erase "$(INTDIR)\selidlvc.obj"
	-@erase "$(INTDIR)\selidlvc.sbr"
	-@erase "$(INTDIR)\Selidprp.obj"
	-@erase "$(INTDIR)\Selidprp.sbr"
	-@erase "$(INTDIR)\Selobdlg.obj"
	-@erase "$(INTDIR)\Selobdlg.sbr"
	-@erase "$(INTDIR)\SelObjProp.obj"
	-@erase "$(INTDIR)\SelObjProp.sbr"
	-@erase "$(INTDIR)\SelObjPropDlg.obj"
	-@erase "$(INTDIR)\SelObjPropDlg.sbr"
	-@erase "$(INTDIR)\Selobwnd.obj"
	-@erase "$(INTDIR)\Selobwnd.sbr"
	-@erase "$(INTDIR)\SelOProp.obj"
	-@erase "$(INTDIR)\SelOProp.sbr"
	-@erase "$(INTDIR)\SelOPrpTree.obj"
	-@erase "$(INTDIR)\SelOPrpTree.sbr"
	-@erase "$(INTDIR)\SPINCTRL.OBJ"
	-@erase "$(INTDIR)\SPINCTRL.SBR"
	-@erase "$(INTDIR)\statimpl.obj"
	-@erase "$(INTDIR)\statimpl.sbr"
	-@erase "$(INTDIR)\STATUS.OBJ"
	-@erase "$(INTDIR)\STATUS.SBR"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\TextSearchEngine.obj"
	-@erase "$(INTDIR)\TextSearchEngine.sbr"
	-@erase "$(INTDIR)\trias03p.obj"
	-@erase "$(INTDIR)\trias03p.sbr"
	-@erase "$(INTDIR)\Trias323.res"
	-@erase "$(INTDIR)\TriASTrans.obj"
	-@erase "$(INTDIR)\TriASTrans.sbr"
	-@erase "$(INTDIR)\txtsrchd.obj"
	-@erase "$(INTDIR)\txtsrchd.sbr"
	-@erase "$(INTDIR)\undocf.obj"
	-@erase "$(INTDIR)\undocf.sbr"
	-@erase "$(INTDIR)\UndoCreo.obj"
	-@erase "$(INTDIR)\UndoCreo.sbr"
	-@erase "$(INTDIR)\undodelo.obj"
	-@erase "$(INTDIR)\undodelo.sbr"
	-@erase "$(INTDIR)\undodelr.obj"
	-@erase "$(INTDIR)\undodelr.sbr"
	-@erase "$(INTDIR)\undodelt.obj"
	-@erase "$(INTDIR)\undodelt.sbr"
	-@erase "$(INTDIR)\undofeat.obj"
	-@erase "$(INTDIR)\undofeat.sbr"
	-@erase "$(INTDIR)\undohelp.obj"
	-@erase "$(INTDIR)\undohelp.sbr"
	-@erase "$(INTDIR)\undohwnd.obj"
	-@erase "$(INTDIR)\undohwnd.sbr"
	-@erase "$(INTDIR)\undomodi.obj"
	-@erase "$(INTDIR)\undomodi.sbr"
	-@erase "$(INTDIR)\undomodo.obj"
	-@erase "$(INTDIR)\undomodo.sbr"
	-@erase "$(INTDIR)\undomodr.obj"
	-@erase "$(INTDIR)\undomodr.sbr"
	-@erase "$(INTDIR)\undomodv.obj"
	-@erase "$(INTDIR)\undomodv.sbr"
	-@erase "$(INTDIR)\undopbd.obj"
	-@erase "$(INTDIR)\undopbd.sbr"
	-@erase "$(INTDIR)\undoredo.obj"
	-@erase "$(INTDIR)\undoredo.sbr"
	-@erase "$(INTDIR)\undotext.obj"
	-@erase "$(INTDIR)\undotext.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Trias323.dll"
	-@erase "$(OUTDIR)\Trias323.exp"
	-@erase "$(OUTDIR)\Trias323.lib"
	-@erase "$(OUTDIR)\Trias323.pdb"
	-@erase "$(OUTDIR)\TRIAS423.bsc"
	-@erase ".\dlldata.c"
	-@erase ".\obj32\..\Release\TRiASHelper.tlb"
	-@erase ".\Release\Trias323.pch"
	-@erase ".\TRiASHelper.h"
	-@erase ".\TRiASHelper_i.c"
	-@erase ".\TRiASHelper_p.c"
	-@erase "c:\trias.mvc\trias200.rel\Trias323.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /Fp"Release/Trias323.pch" /Yu"trias03p.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr /Fp"Release/Trias323.pch" /Yu"trias03p.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__"\
 /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D\
 "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"Release/Trias323.pch" /Yu"trias03p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Pseudo/
CPP_SBRS=.\Pseudo/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /i "./obj32" /d "NDEBUG"
# ADD RSC /l 0x407 /i "./obj32" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRIAS423.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bmpbtn.sbr" \
	"$(INTDIR)\cextreg.sbr" \
	"$(INTDIR)\CheckTreeView.sbr" \
	"$(INTDIR)\CLSFYPRP.SBR" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Dataobj.sbr" \
	"$(INTDIR)\DATATRAN.SBR" \
	"$(INTDIR)\dblcoord.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\DelObPrp.sbr" \
	"$(INTDIR)\DstObDlg.sbr" \
	"$(INTDIR)\DstObWnd.sbr" \
	"$(INTDIR)\Enumonr.sbr" \
	"$(INTDIR)\enumundo.sbr" \
	"$(INTDIR)\GenTextDlg.sbr" \
	"$(INTDIR)\GenTextPropAct.sbr" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\Idataobj.sbr" \
	"$(INTDIR)\Ienumfe.sbr" \
	"$(INTDIR)\ImportDataDlg.sbr" \
	"$(INTDIR)\ImportProp.sbr" \
	"$(INTDIR)\InPlaceCombo.sbr" \
	"$(INTDIR)\INTOPROP.SBR" \
	"$(INTDIR)\JUSTIFY.SBR" \
	"$(INTDIR)\LIBMAIN3.SBR" \
	"$(INTDIR)\LISTHSCR.SBR" \
	"$(INTDIR)\MatchingObjects.sbr" \
	"$(INTDIR)\Modident.sbr" \
	"$(INTDIR)\Modidprp.sbr" \
	"$(INTDIR)\MultiPI.sbr" \
	"$(INTDIR)\MUSCROLL.SBR" \
	"$(INTDIR)\NUMEDIT.SBR" \
	"$(INTDIR)\ObjekteDoppeln.sbr" \
	"$(INTDIR)\ObjekteVereinigen.sbr" \
	"$(INTDIR)\ObjGeomW.sbr" \
	"$(INTDIR)\opropcf.sbr" \
	"$(INTDIR)\oprpfeat.sbr" \
	"$(INTDIR)\OWNCOMBO.SBR" \
	"$(INTDIR)\OWNLIST.SBR" \
	"$(INTDIR)\OWNLISTE.SBR" \
	"$(INTDIR)\PRNTPARS.SBR" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\Propname.sbr" \
	"$(INTDIR)\Propseq.sbr" \
	"$(INTDIR)\queryfld.sbr" \
	"$(INTDIR)\REGISTER.SBR" \
	"$(INTDIR)\RegisterExt.sbr" \
	"$(INTDIR)\REGOBJ.SBR" \
	"$(INTDIR)\regprop.sbr" \
	"$(INTDIR)\ROTATE.SBR" \
	"$(INTDIR)\ScriptPropAct.sbr" \
	"$(INTDIR)\Selident.sbr" \
	"$(INTDIR)\SELIDLST.SBR" \
	"$(INTDIR)\selidlvc.sbr" \
	"$(INTDIR)\Selidprp.sbr" \
	"$(INTDIR)\Selobdlg.sbr" \
	"$(INTDIR)\SelObjProp.sbr" \
	"$(INTDIR)\SelObjPropDlg.sbr" \
	"$(INTDIR)\Selobwnd.sbr" \
	"$(INTDIR)\SelOProp.sbr" \
	"$(INTDIR)\SelOPrpTree.sbr" \
	"$(INTDIR)\SPINCTRL.SBR" \
	"$(INTDIR)\statimpl.sbr" \
	"$(INTDIR)\STATUS.SBR" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\TextSearchEngine.sbr" \
	"$(INTDIR)\trias03p.sbr" \
	"$(INTDIR)\TriASTrans.sbr" \
	"$(INTDIR)\txtsrchd.sbr" \
	"$(INTDIR)\undocf.sbr" \
	"$(INTDIR)\UndoCreo.sbr" \
	"$(INTDIR)\undodelo.sbr" \
	"$(INTDIR)\undodelr.sbr" \
	"$(INTDIR)\undodelt.sbr" \
	"$(INTDIR)\undofeat.sbr" \
	"$(INTDIR)\undohelp.sbr" \
	"$(INTDIR)\undohwnd.sbr" \
	"$(INTDIR)\undomodi.sbr" \
	"$(INTDIR)\undomodo.sbr" \
	"$(INTDIR)\undomodr.sbr" \
	"$(INTDIR)\undomodv.sbr" \
	"$(INTDIR)\undopbd.sbr" \
	"$(INTDIR)\undoredo.sbr" \
	"$(INTDIR)\undotext.sbr"

"$(OUTDIR)\TRIAS423.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 trias322.lib trias321.lib tfrmwork.lib cont32r.lib ospace2r.lib stdcppr.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"./obj32/rights.exe" /out:"Release/Trias323.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 trias322.lib trias321.lib tfrmwork.lib cont32r.lib ospace2r.lib stdcppr.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"./obj32/rights.exe" /out:"Pseudo/Trias323.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=trias322.lib trias321.lib tfrmwork.lib cont32r.lib ospace2r.lib\
 stdcppr.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib uuid2.lib odbc32.lib odbccp32.lib\
 /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Trias323.pdb" /debug /machine:I386\
 /def:".\obj32\trias323207.def" /stub:"./obj32/rights.exe"\
 /out:"$(OUTDIR)/Trias323.dll" /implib:"$(OUTDIR)/Trias323.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\trias323207.def"
LINK32_OBJS= \
	"$(INTDIR)\bmpbtn.obj" \
	"$(INTDIR)\cextreg.obj" \
	"$(INTDIR)\CheckTreeView.obj" \
	"$(INTDIR)\CLSFYPRP.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DATATRAN.OBJ" \
	"$(INTDIR)\dblcoord.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\DelObPrp.obj" \
	"$(INTDIR)\DstObDlg.obj" \
	"$(INTDIR)\DstObWnd.obj" \
	"$(INTDIR)\Enumonr.obj" \
	"$(INTDIR)\enumundo.obj" \
	"$(INTDIR)\GenTextDlg.obj" \
	"$(INTDIR)\GenTextPropAct.obj" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\Idataobj.obj" \
	"$(INTDIR)\Ienumfe.obj" \
	"$(INTDIR)\ImportDataDlg.obj" \
	"$(INTDIR)\ImportProp.obj" \
	"$(INTDIR)\InPlaceCombo.obj" \
	"$(INTDIR)\INTOPROP.OBJ" \
	"$(INTDIR)\JUSTIFY.OBJ" \
	"$(INTDIR)\LIBMAIN3.OBJ" \
	"$(INTDIR)\LISTHSCR.OBJ" \
	"$(INTDIR)\MatchingObjects.obj" \
	"$(INTDIR)\Modident.obj" \
	"$(INTDIR)\Modidprp.obj" \
	"$(INTDIR)\MultiPI.obj" \
	"$(INTDIR)\MUSCROLL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\ObjekteDoppeln.obj" \
	"$(INTDIR)\ObjekteVereinigen.obj" \
	"$(INTDIR)\ObjGeomW.obj" \
	"$(INTDIR)\opropcf.obj" \
	"$(INTDIR)\oprpfeat.obj" \
	"$(INTDIR)\OWNCOMBO.OBJ" \
	"$(INTDIR)\OWNLIST.OBJ" \
	"$(INTDIR)\OWNLISTE.OBJ" \
	"$(INTDIR)\PRNTPARS.OBJ" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Propname.obj" \
	"$(INTDIR)\Propseq.obj" \
	"$(INTDIR)\queryfld.obj" \
	"$(INTDIR)\REGISTER.OBJ" \
	"$(INTDIR)\RegisterExt.obj" \
	"$(INTDIR)\REGOBJ.OBJ" \
	"$(INTDIR)\regprop.obj" \
	"$(INTDIR)\ROTATE.OBJ" \
	"$(INTDIR)\ScriptPropAct.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\SELIDLST.OBJ" \
	"$(INTDIR)\selidlvc.obj" \
	"$(INTDIR)\Selidprp.obj" \
	"$(INTDIR)\Selobdlg.obj" \
	"$(INTDIR)\SelObjProp.obj" \
	"$(INTDIR)\SelObjPropDlg.obj" \
	"$(INTDIR)\Selobwnd.obj" \
	"$(INTDIR)\SelOProp.obj" \
	"$(INTDIR)\SelOPrpTree.obj" \
	"$(INTDIR)\SPINCTRL.OBJ" \
	"$(INTDIR)\statimpl.obj" \
	"$(INTDIR)\STATUS.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TextSearchEngine.obj" \
	"$(INTDIR)\trias03p.obj" \
	"$(INTDIR)\Trias323.res" \
	"$(INTDIR)\TriASTrans.obj" \
	"$(INTDIR)\txtsrchd.obj" \
	"$(INTDIR)\undocf.obj" \
	"$(INTDIR)\UndoCreo.obj" \
	"$(INTDIR)\undodelo.obj" \
	"$(INTDIR)\undodelr.obj" \
	"$(INTDIR)\undodelt.obj" \
	"$(INTDIR)\undofeat.obj" \
	"$(INTDIR)\undohelp.obj" \
	"$(INTDIR)\undohwnd.obj" \
	"$(INTDIR)\undomodi.obj" \
	"$(INTDIR)\undomodo.obj" \
	"$(INTDIR)\undomodr.obj" \
	"$(INTDIR)\undomodv.obj" \
	"$(INTDIR)\undopbd.obj" \
	"$(INTDIR)\undoredo.obj" \
	"$(INTDIR)\undotext.obj"

"$(OUTDIR)\Trias323.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Pseudo\Trias323.dll
TargetName=Trias323
InputPath=.\Pseudo\Trias323.dll
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Trias323 - Win32 Release"
# Name "Trias323 - Win32 Debug"
# Name "Trias323 - Win32 Debug DCOM"
# Name "Trias323 - Win32 Pseudo Debug"

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LIBMAIN3.CXX

!IF  "$(CFG)" == "Trias323 - Win32 Release"

DEP_CPP_LIBMA=\
	".\CLSFYPRP.HXX"\
	".\CoDelegator.h"\
	".\DelObPrp.hxx"\
	".\DLLDATAX.H"\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\Enumonr.hxx"\
	".\GenTextDlg.h"\
	".\GenTextPropAct.h"\
	".\ImportDataDlg.h"\
	".\ImportProp.h"\
	".\Intoprop.hxx"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ObjekteDoppeln.h"\
	".\ObjekteVereinigen.h"\
	".\ObjPropFeature.h"\
	".\Propactb.hxx"\
	".\Propseq.hxx"\
	".\RegisterExt.h"\
	".\REGOBJ.H"\
	".\ScriptPropAct.h"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\statimpl.hxx"\
	".\Strings.h"\
	".\TextSearchEngine.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\triastrans.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteDoppelnGuid.h"\
	{$(INCLUDE)}"\ObjekteVereinigenGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\LIBMAIN3.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\LIBMAIN3.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

DEP_CPP_LIBMA=\
	".\CLSFYPRP.HXX"\
	".\CoDelegator.h"\
	".\DelObPrp.hxx"\
	".\DLLDATAX.H"\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\Enumonr.hxx"\
	".\GenTextDlg.h"\
	".\GenTextPropAct.h"\
	".\ImportDataDlg.h"\
	".\ImportProp.h"\
	".\Intoprop.hxx"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ObjekteDoppeln.h"\
	".\ObjekteVereinigen.h"\
	".\ObjPropFeature.h"\
	".\Propactb.hxx"\
	".\Propseq.hxx"\
	".\RegisterExt.h"\
	".\REGOBJ.H"\
	".\ScriptPropAct.h"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\statimpl.hxx"\
	".\Strings.h"\
	".\TextSearchEngine.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\triastrans.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteDoppelnGuid.h"\
	{$(INCLUDE)}"\ObjekteVereinigenGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\LIBMAIN3.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\LIBMAIN3.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

DEP_CPP_LIBMA=\
	".\CLSFYPRP.HXX"\
	".\CoDelegator.h"\
	".\DelObPrp.hxx"\
	".\DLLDATAX.H"\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\Enumonr.hxx"\
	".\GenTextDlg.h"\
	".\GenTextPropAct.h"\
	".\ImportDataDlg.h"\
	".\ImportProp.h"\
	".\Intoprop.hxx"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ObjekteDoppeln.h"\
	".\ObjekteVereinigen.h"\
	".\ObjPropFeature.h"\
	".\Propactb.hxx"\
	".\Propseq.hxx"\
	".\RegisterExt.h"\
	".\REGOBJ.H"\
	".\ScriptPropAct.h"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\statimpl.hxx"\
	".\Strings.h"\
	".\TextSearchEngine.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\triastrans.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteDoppelnGuid.h"\
	{$(INCLUDE)}"\ObjekteVereinigenGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\LIBMAIN3.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\LIBMAIN3.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

DEP_CPP_LIBMA=\
	".\CLSFYPRP.HXX"\
	".\CoDelegator.h"\
	".\DelObPrp.hxx"\
	".\DLLDATAX.H"\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\Enumonr.hxx"\
	".\GenTextDlg.h"\
	".\GenTextPropAct.h"\
	".\ImportDataDlg.h"\
	".\ImportProp.h"\
	".\Intoprop.hxx"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ObjekteDoppeln.h"\
	".\ObjekteVereinigen.h"\
	".\ObjPropFeature.h"\
	".\Propactb.hxx"\
	".\Propseq.hxx"\
	".\RegisterExt.h"\
	".\REGOBJ.H"\
	".\ScriptPropAct.h"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\statimpl.hxx"\
	".\Strings.h"\
	".\TextSearchEngine.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\triastrans.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteDoppelnGuid.h"\
	{$(INCLUDE)}"\ObjekteVereinigenGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\LIBMAIN3.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\LIBMAIN3.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\trias03p.cxx
DEP_CPP_TRIAS=\
	".\STATIC\STATREG.CPP"\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# ADD CPP /Yc"trias03p.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__"\
 /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D\
 "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE"\
 /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Trias323.pch" /Yc"trias03p.hxx" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\trias03p.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias03p.sbr" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Trias323.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# ADD CPP /Yc"trias03p.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D\
 "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_ATL_TRIAS_REGISTER" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /D "_FORCE_LEGACY_CODE" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/trias323d.pch" /Yc"trias03p.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/trias323d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\trias03p.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias03p.sbr" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias323d.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# ADD BASE CPP /Yc"trias03p.hxx"
# ADD CPP /Yc"trias03p.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D\
 "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_MERGE_PROXYSTUB" /D\
 "_WIN32_DCOM" /D "_ATL_TRIAS_REGISTER" /FR"$(INTDIR)/"\
 /Fp"Debug4/trias323d.pch" /Yc"trias03p.hxx" /Fo"$(INTDIR)/"\
 /Fd"Debug4/trias323d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\trias03p.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias03p.sbr" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

".\Debug4\trias323d.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# ADD BASE CPP /Yc"trias03p.hxx"
# ADD CPP /Yc"trias03p.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__"\
 /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "__ATL_USED__" /D "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D\
 "_ATL_TRIAS_REGISTER" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"Release/Trias323.pch" /Yc"trias03p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\trias03p.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias03p.sbr" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

".\Release\Trias323.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DATATRAN.CXX
DEP_CPP_DATAT=\
	".\CoDelegator.h"\
	".\DATATRAN.HXX"\
	".\DLLDATAX.H"\
	".\STATIC\STATREG.H"\
	".\Trias03p.hxx"\
	".\UNDOCF.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\DATATRAN.OBJ" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\DATATRAN.SBR" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\DATATRAN.OBJ" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\DATATRAN.SBR" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\DATATRAN.OBJ" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\DATATRAN.SBR" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\DATATRAN.OBJ" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\DATATRAN.SBR" : $(SOURCE) $(DEP_CPP_DATAT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undocf.cxx
DEP_CPP_UNDOC=\
	".\ObjGeomW.h"\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOCF.HXX"\
	".\UndoCreo.hxx"\
	".\UNDODELO.HXX"\
	".\UNDODELR.HXX"\
	".\UNDODELT.HXX"\
	".\UNDOFEAT.HXX"\
	".\UNDOHWND.HXX"\
	".\UNDOMODI.HXX"\
	".\UNDOMODO.HXX"\
	".\UNDOMODR.HXX"\
	".\UNDOMODV.HXX"\
	".\UNDOPBD.HXX"\
	".\UNDOTEXT.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undocf.obj" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undocf.sbr" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undocf.obj" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undocf.sbr" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undocf.obj" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undocf.sbr" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undocf.obj" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undocf.sbr" : $(SOURCE) $(DEP_CPP_UNDOC) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undodelo.cxx
DEP_CPP_UNDOD=\
	".\ObjGeomW.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDODELO.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undodelo.obj" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undodelo.sbr" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undodelo.obj" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undodelo.sbr" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undodelo.obj" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undodelo.sbr" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undodelo.obj" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undodelo.sbr" : $(SOURCE) $(DEP_CPP_UNDOD) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undodelr.cxx
DEP_CPP_UNDODE=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDODELR.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undodelr.obj" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undodelr.sbr" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undodelr.obj" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undodelr.sbr" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undodelr.obj" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undodelr.sbr" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undodelr.obj" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undodelr.sbr" : $(SOURCE) $(DEP_CPP_UNDODE) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undodelt.cxx
DEP_CPP_UNDODEL=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDODELT.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undodelt.obj" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undodelt.sbr" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undodelt.obj" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undodelt.sbr" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undodelt.obj" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undodelt.sbr" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undodelt.obj" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undodelt.sbr" : $(SOURCE) $(DEP_CPP_UNDODEL) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undofeat.cxx
DEP_CPP_UNDOF=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOFEAT.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undofeat.obj" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undofeat.sbr" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undofeat.obj" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undofeat.sbr" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undofeat.obj" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undofeat.sbr" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undofeat.obj" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undofeat.sbr" : $(SOURCE) $(DEP_CPP_UNDOF) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undohelp.cxx
DEP_CPP_UNDOH=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undohelp.hxx"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undohelp.obj" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undohelp.sbr" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undohelp.obj" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undohelp.sbr" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undohelp.obj" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undohelp.sbr" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undohelp.obj" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undohelp.sbr" : $(SOURCE) $(DEP_CPP_UNDOH) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undohwnd.cxx
DEP_CPP_UNDOHW=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOHWND.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undohwnd.obj" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undohwnd.sbr" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undohwnd.obj" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undohwnd.sbr" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undohwnd.obj" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undohwnd.sbr" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undohwnd.obj" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undohwnd.sbr" : $(SOURCE) $(DEP_CPP_UNDOHW) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undomodo.cxx
DEP_CPP_UNDOM=\
	".\ObjGeomW.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOMODO.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undomodo.obj" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undomodo.sbr" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undomodo.obj" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undomodo.sbr" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undomodo.obj" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undomodo.sbr" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undomodo.obj" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undomodo.sbr" : $(SOURCE) $(DEP_CPP_UNDOM) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undomodr.cxx
DEP_CPP_UNDOMO=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOMODR.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undomodr.obj" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undomodr.sbr" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undomodr.obj" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undomodr.sbr" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undomodr.obj" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undomodr.sbr" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undomodr.obj" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undomodr.sbr" : $(SOURCE) $(DEP_CPP_UNDOMO) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undoredo.cxx
DEP_CPP_UNDOR=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undoredo.obj" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undoredo.sbr" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undoredo.obj" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undoredo.sbr" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undoredo.obj" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undoredo.sbr" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undoredo.obj" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undoredo.sbr" : $(SOURCE) $(DEP_CPP_UNDOR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undotext.cxx
DEP_CPP_UNDOT=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOTEXT.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undotext.obj" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undotext.sbr" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undotext.obj" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undotext.sbr" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undotext.obj" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undotext.sbr" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undotext.obj" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undotext.sbr" : $(SOURCE) $(DEP_CPP_UNDOT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\enumundo.cxx
DEP_CPP_ENUMU=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\enumundo.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\enumundo.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\enumundo.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\enumundo.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\enumundo.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\enumundo.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\enumundo.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\enumundo.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undopbd.cxx
DEP_CPP_UNDOP=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOPBD.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undopbd.obj" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undopbd.sbr" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undopbd.obj" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undopbd.sbr" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undopbd.obj" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undopbd.sbr" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undopbd.obj" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undopbd.sbr" : $(SOURCE) $(DEP_CPP_UNDOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLNUMED.CXX
DEP_CPP_DBLNU=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dblnumed.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\NUMEDIT.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HELPTEXT.CXX
DEP_CPP_HELPT=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\HELPTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MUSCROLL.CXX
DEP_CPP_MUSCR=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MUSCRL32.H"\
	{$(INCLUDE)}"\MUSCROLL.HXX"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\MUSCROLL.OBJ" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\MUSCROLL.SBR" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\MUSCROLL.OBJ" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\MUSCROLL.SBR" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\MUSCROLL.OBJ" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\MUSCROLL.SBR" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\MUSCROLL.OBJ" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\MUSCROLL.SBR" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDIT.CXX
DEP_CPP_NUMED=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\NUMEDIT.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\NUMEDIT.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\NUMEDIT.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\NUMEDIT.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\NUMEDIT.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OWNCOMBO.CXX
DEP_CPP_OWNCO=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\OWNCOMBO.OBJ" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\OWNCOMBO.SBR" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\OWNCOMBO.OBJ" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\OWNCOMBO.SBR" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\OWNCOMBO.OBJ" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\OWNCOMBO.SBR" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\OWNCOMBO.OBJ" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\OWNCOMBO.SBR" : $(SOURCE) $(DEP_CPP_OWNCO) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OWNLIST.CXX
DEP_CPP_OWNLI=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\OWNLIST.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\OWNLIST.OBJ" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\OWNLIST.SBR" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\OWNLIST.OBJ" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\OWNLIST.SBR" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\OWNLIST.OBJ" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\OWNLIST.SBR" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\OWNLIST.OBJ" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\OWNLIST.SBR" : $(SOURCE) $(DEP_CPP_OWNLI) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OWNLISTE.CXX
DEP_CPP_OWNLIS=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\OWNLIST.HXX"\
	{$(INCLUDE)}"\OWNLISTE.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\OWNLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\OWNLISTE.SBR" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\OWNLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\OWNLISTE.SBR" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\OWNLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\OWNLISTE.SBR" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\OWNLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\OWNLISTE.SBR" : $(SOURCE) $(DEP_CPP_OWNLIS) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SELIDLST.CXX
DEP_CPP_SELID=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SELIDLST.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SELIDLST.OBJ" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SELIDLST.SBR" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SELIDLST.OBJ" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SELIDLST.SBR" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SELIDLST.OBJ" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SELIDLST.SBR" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SELIDLST.OBJ" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SELIDLST.SBR" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SPINCTRL.CXX
DEP_CPP_SPINC=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MUSCROLL.HXX"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\NUMEDIT.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SPINCTRL.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SPINCTRL.OBJ" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SPINCTRL.SBR" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SPINCTRL.OBJ" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SPINCTRL.SBR" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SPINCTRL.OBJ" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SPINCTRL.SBR" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SPINCTRL.OBJ" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SPINCTRL.SBR" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dblcoord.cxx
DEP_CPP_DBLCO=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\dblcoord.hxx"\
	{$(INCLUDE)}"\Dblnumed.hxx"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\NUMEDIT.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\dblcoord.obj" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\dblcoord.sbr" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\dblcoord.obj" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\dblcoord.sbr" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\dblcoord.obj" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\dblcoord.sbr" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\dblcoord.obj" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\dblcoord.sbr" : $(SOURCE) $(DEP_CPP_DBLCO) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PRNTPARS.CXX
DEP_CPP_PRNTP=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\prntpars.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\PRNTPARS.OBJ" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\PRNTPARS.SBR" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\PRNTPARS.OBJ" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\PRNTPARS.SBR" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\PRNTPARS.OBJ" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\PRNTPARS.SBR" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\PRNTPARS.OBJ" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\PRNTPARS.SBR" : $(SOURCE) $(DEP_CPP_PRNTP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROTATE.CXX
DEP_CPP_ROTAT=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ROTATE.OBJ" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ROTATE.SBR" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ROTATE.OBJ" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ROTATE.SBR" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ROTATE.OBJ" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ROTATE.SBR" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ROTATE.OBJ" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ROTATE.SBR" : $(SOURCE) $(DEP_CPP_ROTAT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JUSTIFY.CXX
DEP_CPP_JUSTI=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\JUSTIFY.OBJ" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\JUSTIFY.SBR" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\JUSTIFY.OBJ" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\JUSTIFY.SBR" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\JUSTIFY.OBJ" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\JUSTIFY.SBR" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\JUSTIFY.OBJ" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\JUSTIFY.SBR" : $(SOURCE) $(DEP_CPP_JUSTI) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\opropcf.cxx
DEP_CPP_OPROP=\
	".\Intoprop.hxx"\
	".\ObjPropFeature.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\opropcf.obj" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\opropcf.sbr" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\opropcf.obj" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\opropcf.sbr" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\opropcf.obj" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\opropcf.sbr" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\opropcf.obj" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\opropcf.sbr" : $(SOURCE) $(DEP_CPP_OPROP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INTOPROP.CXX
DEP_CPP_INTOP=\
	".\Intoprop.hxx"\
	".\ObjPropFeature.h"\
	".\QUERYFLD.HXX"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\INTOPROP.OBJ" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\INTOPROP.SBR" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\INTOPROP.OBJ" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\INTOPROP.SBR" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\INTOPROP.OBJ" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\INTOPROP.SBR" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\INTOPROP.OBJ" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\INTOPROP.SBR" : $(SOURCE) $(DEP_CPP_INTOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\queryfld.cxx
DEP_CPP_QUERY=\
	".\QUERYFLD.HXX"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\queryfld.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\queryfld.sbr" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\queryfld.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\queryfld.sbr" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\queryfld.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\queryfld.sbr" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\queryfld.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\queryfld.sbr" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\oprpfeat.cxx
DEP_CPP_OPRPF=\
	".\Intoprop.hxx"\
	".\ObjPropFeature.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ioprpini.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\oprpfeat.obj" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\oprpfeat.sbr" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\oprpfeat.obj" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\oprpfeat.sbr" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\oprpfeat.obj" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\oprpfeat.sbr" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\oprpfeat.obj" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\oprpfeat.sbr" : $(SOURCE) $(DEP_CPP_OPRPF) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\statimpl.cxx
DEP_CPP_STATI=\
	".\STATIC\STATREG.H"\
	".\statimpl.hxx"\
	".\STATUS.HXX"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\statimpl.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\statimpl.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\statimpl.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\statimpl.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\statimpl.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\statimpl.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\statimpl.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\statimpl.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STATUS.CPP
DEP_CPP_STATU=\
	".\STATIC\STATREG.H"\
	".\STATUS.HXX"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\STATUS.OBJ" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\STATUS.SBR" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\STATUS.OBJ" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\STATUS.SBR" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\STATUS.OBJ" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\STATUS.SBR" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\STATUS.OBJ" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\STATUS.SBR" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propname.cxx
DEP_CPP_PROPN=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Propname.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Propname.sbr" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Propname.sbr" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Propname.sbr" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Propname.sbr" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\regprop.cxx
DEP_CPP_REGPR=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\regprop.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\regprop.obj" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\regprop.sbr" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\regprop.obj" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\regprop.sbr" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\regprop.obj" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\regprop.sbr" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\regprop.obj" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\regprop.sbr" : $(SOURCE) $(DEP_CPP_REGPR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\selidlvc.cxx
DEP_CPP_SELIDL=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\selidlvc.obj" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\selidlvc.sbr" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\selidlvc.obj" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\selidlvc.sbr" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\selidlvc.obj" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\selidlvc.sbr" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\selidlvc.obj" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\selidlvc.sbr" : $(SOURCE) $(DEP_CPP_SELIDL) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bmpbtn.cxx
DEP_CPP_BMPBT=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\bmpbtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\bmpbtn.sbr" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\bmpbtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\bmpbtn.sbr" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\bmpbtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\bmpbtn.sbr" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\bmpbtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\bmpbtn.sbr" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undomodv.cxx
DEP_CPP_UNDOMOD=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOMODV.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undomodv.obj" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undomodv.sbr" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undomodv.obj" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undomodv.sbr" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undomodv.obj" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undomodv.sbr" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undomodv.obj" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undomodv.sbr" : $(SOURCE) $(DEP_CPP_UNDOMOD) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\undomodi.cxx
DEP_CPP_UNDOMODI=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UNDOMODI.HXX"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Funcs02.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\undomodi.obj" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\undomodi.sbr" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\undomodi.obj" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\undomodi.sbr" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\undomodi.obj" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\undomodi.sbr" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\undomodi.obj" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\undomodi.sbr" : $(SOURCE) $(DEP_CPP_UNDOMODI) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selidprp.cxx
DEP_CPP_SELIDP=\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Selidprp.sbr" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Selidprp.sbr" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Selidprp.sbr" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Selidprp.sbr" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selident.cxx
DEP_CPP_SELIDE=\
	".\Enumonr.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propactb.cxx
DEP_CPP_PROPA=\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Helper_i.c"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Modidprp.cxx
DEP_CPP_MODID=\
	".\DataHelp.h"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Modidprp.obj" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Modidprp.sbr" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Modidprp.obj" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Modidprp.sbr" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Modidprp.obj" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Modidprp.sbr" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Modidprp.obj" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Modidprp.sbr" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Modident.cxx
DEP_CPP_MODIDE=\
	".\Enumonr.hxx"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ownmacros.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Funcs02.h"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Modident.obj" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Modident.sbr" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Modident.obj" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Modident.sbr" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Modident.obj" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Modident.sbr" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Modident.obj" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Modident.sbr" : $(SOURCE) $(DEP_CPP_MODIDE) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Enumonr.cxx
DEP_CPP_ENUMO=\
	".\Enumonr.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Enumonr.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Enumonr.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Enumonr.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Enumonr.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propseq.cxx
DEP_CPP_PROPS=\
	".\DataHelp.h"\
	".\Modident.hxx"\
	".\Modidprp.hxx"\
	".\MultiPI.h"\
	".\ownmacros.h"\
	".\Propactb.hxx"\
	".\Propseq.hxx"\
	".\Selident.hxx"\
	".\Selidprp.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\triastrans.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\Modidprp.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\Selidlvc.hxx"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Propseq.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Propseq.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Propseq.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Propseq.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selobwnd.cxx
DEP_CPP_SELOB=\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Selobwnd.sbr" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Selobwnd.sbr" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Selobwnd.sbr" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Selobwnd.sbr" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selobdlg.cxx
DEP_CPP_SELOBD=\
	".\Enumonr.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\Selobdlg.hxx"\
	".\Selobwnd.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Selobdlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Selobdlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Selobdlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Selobdlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ienumfe.cxx
DEP_CPP_IENUM=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Ienumfe.obj" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Ienumfe.sbr" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Ienumfe.obj" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Ienumfe.sbr" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Ienumfe.obj" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Ienumfe.sbr" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Ienumfe.obj" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Ienumfe.sbr" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dataobj.cxx
DEP_CPP_DATAO=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Idataobj.cxx
DEP_CPP_IDATA=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Idataobj.obj" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Idataobj.sbr" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Idataobj.obj" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Idataobj.sbr" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Idataobj.obj" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Idataobj.sbr" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Idataobj.obj" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Idataobj.sbr" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Datahelp.cxx
DEP_CPP_DATAH=\
	".\DataHelp.h"\
	".\Enumonr.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Strmhelp.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DstObDlg.cxx
DEP_CPP_DSTOB=\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\Enumonr.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iFndLong.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\DstObDlg.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\DstObDlg.sbr" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\DstObDlg.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\DstObDlg.sbr" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\DstObDlg.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\DstObDlg.sbr" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\DstObDlg.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\DstObDlg.sbr" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DstObWnd.cxx
DEP_CPP_DSTOBW=\
	".\DstObDlg.hxx"\
	".\DstObWnd.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\DstObWnd.obj" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\DstObWnd.sbr" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\DstObWnd.obj" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\DstObWnd.sbr" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\DstObWnd.obj" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\DstObWnd.sbr" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\DstObWnd.obj" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\DstObWnd.sbr" : $(SOURCE) $(DEP_CPP_DSTOBW) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\Trias323.def

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\Trias323.RC
DEP_RSC_TRIAS3=\
	".\obj32\..\Release\TRiASHelper.tlb"\
	".\obj32\res\Chckmark.bmp"\
	".\obj32\res\checkmar.bmp"\
	".\obj32\res\Copy.avi"\
	".\obj32\res\CopyObjectsd.ebc"\
	".\obj32\res\CopyObjectsr.ebc"\
	".\obj32\res\Delete.avi"\
	".\obj32\res\DelObPrp.rgs"\
	".\obj32\res\down.bmp"\
	".\obj32\res\downdis.bmp"\
	".\obj32\res\downfoc.bmp"\
	".\obj32\res\downsel.bmp"\
	".\obj32\res\DstObWnd.rgs"\
	".\obj32\res\EnumONr.rgs"\
	".\obj32\res\FakeTRiASLockFeature.rgs"\
	".\obj32\res\GenTextPropAct.rgs"\
	".\obj32\res\HEADERST.BMP"\
	".\obj32\res\ImportData.rgs"\
	".\obj32\res\ModIdPrp.rgs"\
	".\obj32\res\Move.avi"\
	".\obj32\res\MultiPI.rgs"\
	".\obj32\res\ObjekteDoppeln.rgs"\
	".\obj32\res\ObjekteVereinigen.rgs"\
	".\obj32\res\ObjekteVereinigend.ebc"\
	".\obj32\res\ObjekteVereinigenr.ebc"\
	".\obj32\res\plft.bmp"\
	".\obj32\res\plft_lar.bmp"\
	".\obj32\res\PropSeq.rgs"\
	".\obj32\res\Register.rgs"\
	".\obj32\res\RegisterExt.rgs"\
	".\obj32\res\ScriptPropAct.rgs"\
	".\obj32\res\SelIdPrp.rgs"\
	".\obj32\res\SelObjPrp.rgs"\
	".\obj32\res\SelObWnd.rgs"\
	".\obj32\res\StatImpl.rgs"\
	".\obj32\res\TextSearchEngine.rgs"\
	".\obj32\res\TRiAS03.rgs"\
	".\obj32\res\TxtObPrp.rgs"\
	".\obj32\trias323.rcv"\
	
NODEP_RSC_TRIAS3=\
	".\obj32\..\Debug4\TRiASHelper.tlb"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Trias323.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"\
 "$(INTDIR)\TRiASHelper.tlb"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /i "obj32" /d\
 "NDEBUG" /d "_OLDCATIDS" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Trias323.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"\
 ".\obj32\..\Debug4\TRiASHelper.tlb"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /i "obj32" /d\
 "_DEBUG" /d "_OLDCATIDS" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Trias323.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"\
 ".\obj32\..\Debug4\TRiASHelper.tlb"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /i "obj32" /d\
 "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Trias323.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"\
 ".\obj32\..\Release\TRiASHelper.tlb"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias323.res" /i "./obj32" /i "obj32" /d\
 "NDEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TextSearchEngine.cpp
DEP_CPP_TEXTS=\
	".\DataHelp.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\TextSearchEngine.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\OLESTREA.H"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\TextSearchEngine.obj" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\TextSearchEngine.sbr" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\TextSearchEngine.obj" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\TextSearchEngine.sbr" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\TextSearchEngine.obj" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\TextSearchEngine.sbr" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\TextSearchEngine.obj" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\TextSearchEngine.sbr" : $(SOURCE) $(DEP_CPP_TEXTS) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\txtsrchd.cpp
DEP_CPP_TXTSR=\
	".\MatchingObjects.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\SelObjProp.h"\
	".\SelObjPropDlg.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	".\txtsrchd.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\ALGORITHM"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\txtsrchd.obj" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\txtsrchd.sbr" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\txtsrchd.obj" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\txtsrchd.sbr" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\txtsrchd.obj" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\txtsrchd.sbr" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\txtsrchd.obj" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\txtsrchd.sbr" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\Register.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REGOBJ.CPP
DEP_CPP_REGOB=\
	".\REGOBJ.H"\
	".\STATIC\STATREG.CPP"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\REGOBJ.OBJ" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGOBJ.SBR" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\REGOBJ.OBJ" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGOBJ.SBR" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\REGOBJ.OBJ" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGOBJ.SBR" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\REGOBJ.OBJ" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGOBJ.SBR" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REGISTER.CPP
DEP_CPP_REGIS=\
	".\REGOBJ.H"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\REGISTER.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGISTER.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\REGISTER.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGISTER.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\REGISTER.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGISTER.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\REGISTER.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\REGISTER.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\TextSearchEngine.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\SelIdPrp.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\ModIdPrp.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\SelObWnd.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\PropSeq.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\DstObWnd.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\EnumONr.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelObjProp.cpp
DEP_CPP_SELOBJ=\
	".\SelObjProp.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Propname.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SelObjProp.obj" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SelObjProp.sbr" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SelObjProp.obj" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SelObjProp.sbr" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SelObjProp.obj" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SelObjProp.sbr" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SelObjProp.obj" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SelObjProp.sbr" : $(SOURCE) $(DEP_CPP_SELOBJ) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelObjPropDlg.cpp
DEP_CPP_SELOBJP=\
	".\SelObjProp.h"\
	".\SelObjPropDlg.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SelObjPropDlg.obj" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SelObjPropDlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SelObjPropDlg.obj" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SelObjPropDlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SelObjPropDlg.obj" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SelObjPropDlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SelObjPropDlg.obj" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SelObjPropDlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBJP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MatchingObjects.cpp
DEP_CPP_MATCH=\
	".\MatchingObjects.h"\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\MatchingObjects.obj" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\MatchingObjects.sbr" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\MatchingObjects.obj" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\MatchingObjects.sbr" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\MatchingObjects.obj" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\MatchingObjects.sbr" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\MatchingObjects.obj" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\MatchingObjects.sbr" : $(SOURCE) $(DEP_CPP_MATCH) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRiASHelper.IDL

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /old /win32 /D_MSC_VER=1020 /tlb $(InputDir)/Release/$(InputName).tlb\
   $(InputPath) \
	

"$(InputDir)/Release/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /old /win32 /D_MSC_VER=1020 /tlb $(InputDir)/Debug4/$(InputName).tlb\
   $(InputPath) \
	

"$(InputDir)/Debug4/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /old /win32 /tlb $(InputDir)/Debug4/$(InputName).tlb $(InputPath) \
	

"$(InputDir)/Debug4/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /old /win32 /D_MSC_VER=1020 /tlb $(InputDir)/Release/$(InputName).tlb\
   $(InputPath) \
	

"$(InputDir)/Release/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\headerst.bmp

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLLDATAX.C
DEP_CPP_DLLDA=\
	".\dlldata.c"\
	".\TRiASHelper.h"\
	".\TRiASHelper_p.c"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_USED__" /D\
 "_ATL_STATIC_REGISTRY" /D "OS_NO_ALLOCATORS" /D "_MERGE_PROXYSTUB" /D\
 "_WIN32_DCOM" /D "_ATL_TRIAS_REGISTER" /FR"$(INTDIR)/" /Fo"$(INTDIR)/"\
 /Fd"Debug4/trias323d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DLLDATAX.OBJ" : $(SOURCE) $(DEP_CPP_DLLDA) "$(INTDIR)"\
 ".\TRiASHelper.h" ".\dlldata.c" ".\TRiASHelper_p.c"
   $(BuildCmds)

"$(INTDIR)\DLLDATAX.SBR" : $(SOURCE) $(DEP_CPP_DLLDA) "$(INTDIR)"\
 ".\TRiASHelper.h" ".\dlldata.c" ".\TRiASHelper_p.c"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjGeomW.cpp
DEP_CPP_OBJGE=\
	".\ObjGeomW.h"\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ObjGeomW.obj" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ObjGeomW.sbr" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ObjGeomW.obj" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ObjGeomW.sbr" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ObjGeomW.obj" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ObjGeomW.sbr" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ObjGeomW.obj" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ObjGeomW.sbr" : $(SOURCE) $(DEP_CPP_OBJGE) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UndoCreo.cpp
DEP_CPP_UNDOCR=\
	".\ObjGeomW.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\UndoCreo.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\ENUMUNDO.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\undoredo.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\UndoCreo.obj" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\UndoCreo.sbr" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\UndoCreo.obj" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\UndoCreo.sbr" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\UndoCreo.obj" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\UndoCreo.sbr" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\UndoCreo.obj" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\UndoCreo.sbr" : $(SOURCE) $(DEP_CPP_UNDOCR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LISTHSCR.CPP
DEP_CPP_LISTH=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\LISTHSCR.OBJ" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\LISTHSCR.SBR" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\LISTHSCR.OBJ" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\LISTHSCR.SBR" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\LISTHSCR.OBJ" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\LISTHSCR.SBR" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\LISTHSCR.OBJ" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\LISTHSCR.SBR" : $(SOURCE) $(DEP_CPP_LISTH) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TRIAS33D.DEF

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\StatImpl.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MultiPI.cpp
DEP_CPP_MULTI=\
	".\MultiPI.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\MultiPI.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\MultiPI.sbr" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\MultiPI.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\MultiPI.sbr" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\MultiPI.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\MultiPI.sbr" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\MultiPI.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\MultiPI.sbr" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DelObPrp.cxx
DEP_CPP_DELOB=\
	".\DelObPrp.hxx"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DelObPrp.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\DelObPrp.obj" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\DelObPrp.sbr" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\DelObPrp.obj" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\DelObPrp.sbr" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\DelObPrp.obj" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\DelObPrp.sbr" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\DelObPrp.obj" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\DelObPrp.sbr" : $(SOURCE) $(DEP_CPP_DELOB) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strings.cpp
DEP_CPP_STRIN=\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CheckTreeView.cpp
DEP_CPP_CHECK=\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CheckTreeView.h"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\CheckTreeView.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\CheckTreeView.sbr" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\CheckTreeView.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\CheckTreeView.sbr" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\CheckTreeView.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\CheckTreeView.sbr" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\CheckTreeView.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\CheckTreeView.sbr" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cextreg.cxx
DEP_CPP_CEXTR=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\cextreg.hxx"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\VersionWrap.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\cextreg.obj" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\cextreg.sbr" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\cextreg.obj" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\cextreg.sbr" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\cextreg.obj" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\cextreg.sbr" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\cextreg.obj" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\cextreg.sbr" : $(SOURCE) $(DEP_CPP_CEXTR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegisterExt.cpp
DEP_CPP_REGIST=\
	".\RegisterExt.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\cextreg.hxx"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\VersionWrap.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\RegisterExt.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\RegisterExt.sbr" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\RegisterExt.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\RegisterExt.sbr" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\RegisterExt.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\RegisterExt.sbr" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\RegisterExt.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\RegisterExt.sbr" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\RegisterExt.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\InPlaceCombo.cpp
DEP_CPP_INPLA=\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\InPlaceCombo.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\InPlaceCombo.obj" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\InPlaceCombo.sbr" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\InPlaceCombo.obj" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\InPlaceCombo.sbr" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\InPlaceCombo.obj" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\InPlaceCombo.sbr" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\InPlaceCombo.obj" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\InPlaceCombo.sbr" : $(SOURCE) $(DEP_CPP_INPLA) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelOPrpTree.cpp
DEP_CPP_SELOP=\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Propname.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SelOPrpTree.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SelOPrpTree.sbr" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SelOPrpTree.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SelOPrpTree.sbr" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SelOPrpTree.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SelOPrpTree.sbr" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SelOPrpTree.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SelOPrpTree.sbr" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelOProp.cpp
DEP_CPP_SELOPR=\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\SelOProp.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\SelOProp.sbr" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\SelOProp.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\SelOProp.sbr" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\SelOProp.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\SelOProp.sbr" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\SelOProp.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\SelOProp.sbr" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CLSFYPRP.CXX
DEP_CPP_CLSFY=\
	".\CLSFYPRP.HXX"\
	".\Propactb.hxx"\
	".\SelOProp.h"\
	".\SelOPrpTree.h"\
	".\STATIC\STATREG.H"\
	".\TRIAS03.H"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\CLSFYPRP.OBJ" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\CLSFYPRP.SBR" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\CLSFYPRP.OBJ" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\CLSFYPRP.SBR" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\CLSFYPRP.OBJ" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\CLSFYPRP.SBR" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\CLSFYPRP.OBJ" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\CLSFYPRP.SBR" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\trias33d207.def

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ImportDataDlg.cpp
DEP_CPP_IMPOR=\
	".\ImportDataDlg.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ImportDataDlg.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ImportDataDlg.sbr" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ImportDataDlg.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ImportDataDlg.sbr" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ImportDataDlg.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ImportDataDlg.sbr" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ImportDataDlg.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ImportDataDlg.sbr" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ImportProp.cpp
DEP_CPP_IMPORT=\
	".\ImportDataDlg.h"\
	".\ImportProp.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\importprp.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ImportProp.obj" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ImportProp.sbr" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ImportProp.obj" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ImportProp.sbr" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ImportProp.obj" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ImportProp.sbr" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ImportProp.obj" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ImportProp.sbr" : $(SOURCE) $(DEP_CPP_IMPORT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GenTextPropAct.cpp
DEP_CPP_GENTE=\
	".\DataHelp.h"\
	".\GenTextDlg.h"\
	".\GenTextPropAct.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\TRiASHelper.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\OLESTREA.H"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\SRCHGUID.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\GenTextPropAct.obj" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\GenTextPropAct.sbr" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\GenTextPropAct.obj" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\GenTextPropAct.sbr" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\GenTextPropAct.obj" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"

"$(INTDIR)\GenTextPropAct.sbr" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 ".\Debug4\trias323d.pch" ".\TRiASHelper.h"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\GenTextPropAct.obj" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"

"$(INTDIR)\GenTextPropAct.sbr" : $(SOURCE) $(DEP_CPP_GENTE) "$(INTDIR)"\
 ".\Release\Trias323.pch" ".\TRiASHelper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GenTextDlg.cpp
DEP_CPP_GENTEX=\
	".\GenTextDlg.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\SelObjProp.h"\
	".\SelObjPropDlg.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\ALGORITHM"\
	{$(INCLUDE)}"\bmpbtn.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GenTGuid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\GenTextDlg.obj" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\GenTextDlg.sbr" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\GenTextDlg.obj" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\GenTextDlg.sbr" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\GenTextDlg.obj" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\GenTextDlg.sbr" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\GenTextDlg.obj" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\GenTextDlg.sbr" : $(SOURCE) $(DEP_CPP_GENTEX) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\GenTextPropAct.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\trias323207.def

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScriptPropAct.cpp
DEP_CPP_SCRIP=\
	".\DataHelp.h"\
	".\MultiPI.h"\
	".\Propactb.hxx"\
	".\ScriptPropAct.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCS03.H"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\JUSTIFY.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ROTATE.HXX"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ScriptPropAct.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ScriptPropAct.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ScriptPropAct.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ScriptPropAct.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ScriptPropAct.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ScriptPropAct.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ScriptPropAct.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ScriptPropAct.sbr" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjekteDoppeln.cpp
DEP_CPP_OBJEK=\
	".\ObjekteDoppeln.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteDoppelnGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ObjekteDoppeln.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ObjekteDoppeln.sbr" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ObjekteDoppeln.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ObjekteDoppeln.sbr" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ObjekteDoppeln.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ObjekteDoppeln.sbr" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ObjekteDoppeln.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ObjekteDoppeln.sbr" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\ObjekteDoppeln.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\ScriptPropAct.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjekteVereinigen.cpp
DEP_CPP_OBJEKT=\
	".\ObjekteVereinigen.h"\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRIAS03.H"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ObjekteVereinigenGuid.h"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\ObjekteVereinigen.obj" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\ObjekteVereinigen.sbr" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\ObjekteVereinigen.obj" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\ObjekteVereinigen.sbr" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\ObjekteVereinigen.obj" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\ObjekteVereinigen.sbr" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\ObjekteVereinigen.obj" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\ObjekteVereinigen.sbr" : $(SOURCE) $(DEP_CPP_OBJEKT) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\res\ObjekteVereinigen.rgs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TriASTrans.cpp
DEP_CPP_TRIAST=\
	".\STATIC\STATREG.H"\
	".\Strings.h"\
	".\TRiAS03Config.h"\
	".\Trias03p.hxx"\
	".\triastrans.h"\
	"C:\MSDev\MsSdk\INCLUDE\msxml.h"\
	"C:\MSDev\MsSdk\INCLUDE\servprov.h"\
	"C:\MSDev\MsSdk\INCLUDE\urlmon.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\memory"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\OWNCOMBO.HXX"\
	{$(INCLUDE)}"\PALCHEVT.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Trias323 - Win32 Release"


"$(INTDIR)\TriASTrans.obj" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"

"$(INTDIR)\TriASTrans.sbr" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 "$(INTDIR)\Trias323.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"


"$(INTDIR)\TriASTrans.obj" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"

"$(INTDIR)\TriASTrans.sbr" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 "$(INTDIR)\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug DCOM"


"$(INTDIR)\TriASTrans.obj" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"

"$(INTDIR)\TriASTrans.sbr" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 ".\Debug4\trias323d.pch"


!ELSEIF  "$(CFG)" == "Trias323 - Win32 Pseudo Debug"


"$(INTDIR)\TriASTrans.obj" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 ".\Release\Trias323.pch"

"$(INTDIR)\TriASTrans.sbr" : $(SOURCE) $(DEP_CPP_TRIAST) "$(INTDIR)"\
 ".\Release\Trias323.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
