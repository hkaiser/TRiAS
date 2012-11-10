# Microsoft Developer Studio Generated NMAKE File, Based on Gak.dsp
!IF "$(CFG)" == ""
CFG=gak - Win32 Release
!MESSAGE No configuration specified. Defaulting to gak - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "gak - Win32 Release" && "$(CFG)" != "gak - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gak.mak" CFG="gak - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gak - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gak - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "gak - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
TargetName=Gak
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\Gak.exe"

!ELSE 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\Gak.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AbfallP.obj"
	-@erase "$(INTDIR)\AbfArSet.obj"
	-@erase "$(INTDIR)\AbfDoc.obj"
	-@erase "$(INTDIR)\AbfFrame.obj"
	-@erase "$(INTDIR)\AbfPage.obj"
	-@erase "$(INTDIR)\AbfSet.obj"
	-@erase "$(INTDIR)\AbfSetEx.obj"
	-@erase "$(INTDIR)\AbfSheet.obj"
	-@erase "$(INTDIR)\AbfView.obj"
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\Afidlg.obj"
	-@erase "$(INTDIR)\anfpage.obj"
	-@erase "$(INTDIR)\BetrPage.obj"
	-@erase "$(INTDIR)\BrancheP.obj"
	-@erase "$(INTDIR)\BranPage.obj"
	-@erase "$(INTDIR)\ChangeNr.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Compact.obj"
	-@erase "$(INTDIR)\daotools.obj"
	-@erase "$(INTDIR)\DocumExt.obj"
	-@erase "$(INTDIR)\DoImpPge.obj"
	-@erase "$(INTDIR)\EnterNr.obj"
	-@erase "$(INTDIR)\EntPage.obj"
	-@erase "$(INTDIR)\Entspage.obj"
	-@erase "$(INTDIR)\EntsSet.obj"
	-@erase "$(INTDIR)\ErzFrame.obj"
	-@erase "$(INTDIR)\ErzPar.obj"
	-@erase "$(INTDIR)\ErzSheet.obj"
	-@erase "$(INTDIR)\Exportre.obj"
	-@erase "$(INTDIR)\FeldInfo.obj"
	-@erase "$(INTDIR)\FirmaSet.obj"
	-@erase "$(INTDIR)\firmpage.obj"
	-@erase "$(INTDIR)\gak.obj"
	-@erase "$(INTDIR)\Gak.pch"
	-@erase "$(INTDIR)\gak.res"
	-@erase "$(INTDIR)\gakDoc.obj"
	-@erase "$(INTDIR)\gakSet.obj"
	-@erase "$(INTDIR)\Gaksete.obj"
	-@erase "$(INTDIR)\gakView.obj"
	-@erase "$(INTDIR)\GebietP.obj"
	-@erase "$(INTDIR)\Getodbci.obj"
	-@erase "$(INTDIR)\Importty.obj"
	-@erase "$(INTDIR)\ImpParPg.obj"
	-@erase "$(INTDIR)\ImpQuery.obj"
	-@erase "$(INTDIR)\ImpResPg.obj"
	-@erase "$(INTDIR)\ImprtDlg.obj"
	-@erase "$(INTDIR)\ImpSumPg.obj"
	-@erase "$(INTDIR)\InTablPg.obj"
	-@erase "$(INTDIR)\KreisSet.obj"
	-@erase "$(INTDIR)\Listext.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NewQuery.obj"
	-@erase "$(INTDIR)\Numedit.obj"
	-@erase "$(INTDIR)\OutTbPg.obj"
	-@erase "$(INTDIR)\PartPage.obj"
	-@erase "$(INTDIR)\Peplus.obj"
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\QueryDlg.obj"
	-@erase "$(INTDIR)\QueryPar.obj"
	-@erase "$(INTDIR)\querypr.obj"
	-@erase "$(INTDIR)\QueryRes.obj"
	-@erase "$(INTDIR)\Recview.obj"
	-@erase "$(INTDIR)\ResultP.obj"
	-@erase "$(INTDIR)\SearchSe.obj"
	-@erase "$(INTDIR)\SearRes.obj"
	-@erase "$(INTDIR)\Selectex.obj"
	-@erase "$(INTDIR)\SelNum.obj"
	-@erase "$(INTDIR)\Selset.obj"
	-@erase "$(INTDIR)\StatBarE.obj"
	-@erase "$(INTDIR)\StatDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\TablNDlg.obj"
	-@erase "$(INTDIR)\TransPge.obj"
	-@erase "$(INTDIR)\TransSet.obj"
	-@erase "$(INTDIR)\UserInfo.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\waitcext.obj"
	-@erase "$(OUTDIR)\Gak.exe"
	-@erase "$(OUTDIR)\Gak.ilk"
	-@erase "$(OutDir)\$(TargetName).hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG"\
 /Fp"$(INTDIR)\Gak.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\gak.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gak.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=crpe32m.lib odbccp32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\Gak.pdb" /machine:I386\
 /out:"$(OUTDIR)\Gak.exe" /stub:"rights.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AbfallP.obj" \
	"$(INTDIR)\AbfArSet.obj" \
	"$(INTDIR)\AbfDoc.obj" \
	"$(INTDIR)\AbfFrame.obj" \
	"$(INTDIR)\AbfPage.obj" \
	"$(INTDIR)\AbfSet.obj" \
	"$(INTDIR)\AbfSetEx.obj" \
	"$(INTDIR)\AbfSheet.obj" \
	"$(INTDIR)\AbfView.obj" \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\Afidlg.obj" \
	"$(INTDIR)\anfpage.obj" \
	"$(INTDIR)\BetrPage.obj" \
	"$(INTDIR)\BrancheP.obj" \
	"$(INTDIR)\BranPage.obj" \
	"$(INTDIR)\ChangeNr.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Compact.obj" \
	"$(INTDIR)\daotools.obj" \
	"$(INTDIR)\DocumExt.obj" \
	"$(INTDIR)\DoImpPge.obj" \
	"$(INTDIR)\EnterNr.obj" \
	"$(INTDIR)\EntPage.obj" \
	"$(INTDIR)\Entspage.obj" \
	"$(INTDIR)\EntsSet.obj" \
	"$(INTDIR)\ErzFrame.obj" \
	"$(INTDIR)\ErzPar.obj" \
	"$(INTDIR)\ErzSheet.obj" \
	"$(INTDIR)\Exportre.obj" \
	"$(INTDIR)\FeldInfo.obj" \
	"$(INTDIR)\FirmaSet.obj" \
	"$(INTDIR)\firmpage.obj" \
	"$(INTDIR)\gak.obj" \
	"$(INTDIR)\gak.res" \
	"$(INTDIR)\gakDoc.obj" \
	"$(INTDIR)\gakSet.obj" \
	"$(INTDIR)\Gaksete.obj" \
	"$(INTDIR)\gakView.obj" \
	"$(INTDIR)\GebietP.obj" \
	"$(INTDIR)\Getodbci.obj" \
	"$(INTDIR)\Importty.obj" \
	"$(INTDIR)\ImpParPg.obj" \
	"$(INTDIR)\ImpQuery.obj" \
	"$(INTDIR)\ImpResPg.obj" \
	"$(INTDIR)\ImprtDlg.obj" \
	"$(INTDIR)\ImpSumPg.obj" \
	"$(INTDIR)\InTablPg.obj" \
	"$(INTDIR)\KreisSet.obj" \
	"$(INTDIR)\Listext.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NewQuery.obj" \
	"$(INTDIR)\Numedit.obj" \
	"$(INTDIR)\OutTbPg.obj" \
	"$(INTDIR)\PartPage.obj" \
	"$(INTDIR)\Peplus.obj" \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\QueryDlg.obj" \
	"$(INTDIR)\QueryPar.obj" \
	"$(INTDIR)\querypr.obj" \
	"$(INTDIR)\QueryRes.obj" \
	"$(INTDIR)\Recview.obj" \
	"$(INTDIR)\ResultP.obj" \
	"$(INTDIR)\SearchSe.obj" \
	"$(INTDIR)\SearRes.obj" \
	"$(INTDIR)\Selectex.obj" \
	"$(INTDIR)\SelNum.obj" \
	"$(INTDIR)\Selset.obj" \
	"$(INTDIR)\StatBarE.obj" \
	"$(INTDIR)\StatDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TablNDlg.obj" \
	"$(INTDIR)\TransPge.obj" \
	"$(INTDIR)\TransSet.obj" \
	"$(INTDIR)\UserInfo.obj" \
	"$(INTDIR)\waitcext.obj"

"$(OUTDIR)\Gak.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
TargetName=Gak
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\Gak.exe" "$(OUTDIR)\Gak.bsc"

!ELSE 

ALL : "$(OutDir)\$(TargetName).hlp" "$(OUTDIR)\Gak.exe" "$(OUTDIR)\Gak.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AbfallP.obj"
	-@erase "$(INTDIR)\AbfallP.sbr"
	-@erase "$(INTDIR)\AbfArSet.obj"
	-@erase "$(INTDIR)\AbfArSet.sbr"
	-@erase "$(INTDIR)\AbfDoc.obj"
	-@erase "$(INTDIR)\AbfDoc.sbr"
	-@erase "$(INTDIR)\AbfFrame.obj"
	-@erase "$(INTDIR)\AbfFrame.sbr"
	-@erase "$(INTDIR)\AbfPage.obj"
	-@erase "$(INTDIR)\AbfPage.sbr"
	-@erase "$(INTDIR)\AbfSet.obj"
	-@erase "$(INTDIR)\AbfSet.sbr"
	-@erase "$(INTDIR)\AbfSetEx.obj"
	-@erase "$(INTDIR)\AbfSetEx.sbr"
	-@erase "$(INTDIR)\AbfSheet.obj"
	-@erase "$(INTDIR)\AbfSheet.sbr"
	-@erase "$(INTDIR)\AbfView.obj"
	-@erase "$(INTDIR)\AbfView.sbr"
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\Afidlg.obj"
	-@erase "$(INTDIR)\Afidlg.sbr"
	-@erase "$(INTDIR)\anfpage.obj"
	-@erase "$(INTDIR)\anfpage.sbr"
	-@erase "$(INTDIR)\BetrPage.obj"
	-@erase "$(INTDIR)\BetrPage.sbr"
	-@erase "$(INTDIR)\BrancheP.obj"
	-@erase "$(INTDIR)\BrancheP.sbr"
	-@erase "$(INTDIR)\BranPage.obj"
	-@erase "$(INTDIR)\BranPage.sbr"
	-@erase "$(INTDIR)\ChangeNr.obj"
	-@erase "$(INTDIR)\ChangeNr.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\Compact.obj"
	-@erase "$(INTDIR)\Compact.sbr"
	-@erase "$(INTDIR)\daotools.obj"
	-@erase "$(INTDIR)\daotools.sbr"
	-@erase "$(INTDIR)\DocumExt.obj"
	-@erase "$(INTDIR)\DocumExt.sbr"
	-@erase "$(INTDIR)\DoImpPge.obj"
	-@erase "$(INTDIR)\DoImpPge.sbr"
	-@erase "$(INTDIR)\EnterNr.obj"
	-@erase "$(INTDIR)\EnterNr.sbr"
	-@erase "$(INTDIR)\EntPage.obj"
	-@erase "$(INTDIR)\EntPage.sbr"
	-@erase "$(INTDIR)\Entspage.obj"
	-@erase "$(INTDIR)\Entspage.sbr"
	-@erase "$(INTDIR)\EntsSet.obj"
	-@erase "$(INTDIR)\EntsSet.sbr"
	-@erase "$(INTDIR)\ErzFrame.obj"
	-@erase "$(INTDIR)\ErzFrame.sbr"
	-@erase "$(INTDIR)\ErzPar.obj"
	-@erase "$(INTDIR)\ErzPar.sbr"
	-@erase "$(INTDIR)\ErzSheet.obj"
	-@erase "$(INTDIR)\ErzSheet.sbr"
	-@erase "$(INTDIR)\Exportre.obj"
	-@erase "$(INTDIR)\Exportre.sbr"
	-@erase "$(INTDIR)\FeldInfo.obj"
	-@erase "$(INTDIR)\FeldInfo.sbr"
	-@erase "$(INTDIR)\FirmaSet.obj"
	-@erase "$(INTDIR)\FirmaSet.sbr"
	-@erase "$(INTDIR)\firmpage.obj"
	-@erase "$(INTDIR)\firmpage.sbr"
	-@erase "$(INTDIR)\gak.obj"
	-@erase "$(INTDIR)\Gak.pch"
	-@erase "$(INTDIR)\gak.res"
	-@erase "$(INTDIR)\gak.sbr"
	-@erase "$(INTDIR)\gakDoc.obj"
	-@erase "$(INTDIR)\gakDoc.sbr"
	-@erase "$(INTDIR)\gakSet.obj"
	-@erase "$(INTDIR)\gakSet.sbr"
	-@erase "$(INTDIR)\Gaksete.obj"
	-@erase "$(INTDIR)\Gaksete.sbr"
	-@erase "$(INTDIR)\gakView.obj"
	-@erase "$(INTDIR)\gakView.sbr"
	-@erase "$(INTDIR)\GebietP.obj"
	-@erase "$(INTDIR)\GebietP.sbr"
	-@erase "$(INTDIR)\Getodbci.obj"
	-@erase "$(INTDIR)\Getodbci.sbr"
	-@erase "$(INTDIR)\Importty.obj"
	-@erase "$(INTDIR)\Importty.sbr"
	-@erase "$(INTDIR)\ImpParPg.obj"
	-@erase "$(INTDIR)\ImpParPg.sbr"
	-@erase "$(INTDIR)\ImpQuery.obj"
	-@erase "$(INTDIR)\ImpQuery.sbr"
	-@erase "$(INTDIR)\ImpResPg.obj"
	-@erase "$(INTDIR)\ImpResPg.sbr"
	-@erase "$(INTDIR)\ImprtDlg.obj"
	-@erase "$(INTDIR)\ImprtDlg.sbr"
	-@erase "$(INTDIR)\ImpSumPg.obj"
	-@erase "$(INTDIR)\ImpSumPg.sbr"
	-@erase "$(INTDIR)\InTablPg.obj"
	-@erase "$(INTDIR)\InTablPg.sbr"
	-@erase "$(INTDIR)\KreisSet.obj"
	-@erase "$(INTDIR)\KreisSet.sbr"
	-@erase "$(INTDIR)\Listext.obj"
	-@erase "$(INTDIR)\Listext.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\NewQuery.obj"
	-@erase "$(INTDIR)\NewQuery.sbr"
	-@erase "$(INTDIR)\Numedit.obj"
	-@erase "$(INTDIR)\Numedit.sbr"
	-@erase "$(INTDIR)\OutTbPg.obj"
	-@erase "$(INTDIR)\OutTbPg.sbr"
	-@erase "$(INTDIR)\PartPage.obj"
	-@erase "$(INTDIR)\PartPage.sbr"
	-@erase "$(INTDIR)\Peplus.obj"
	-@erase "$(INTDIR)\Peplus.sbr"
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\Progress.sbr"
	-@erase "$(INTDIR)\QueryDlg.obj"
	-@erase "$(INTDIR)\QueryDlg.sbr"
	-@erase "$(INTDIR)\QueryPar.obj"
	-@erase "$(INTDIR)\QueryPar.sbr"
	-@erase "$(INTDIR)\querypr.obj"
	-@erase "$(INTDIR)\querypr.sbr"
	-@erase "$(INTDIR)\QueryRes.obj"
	-@erase "$(INTDIR)\QueryRes.sbr"
	-@erase "$(INTDIR)\Recview.obj"
	-@erase "$(INTDIR)\Recview.sbr"
	-@erase "$(INTDIR)\ResultP.obj"
	-@erase "$(INTDIR)\ResultP.sbr"
	-@erase "$(INTDIR)\SearchSe.obj"
	-@erase "$(INTDIR)\SearchSe.sbr"
	-@erase "$(INTDIR)\SearRes.obj"
	-@erase "$(INTDIR)\SearRes.sbr"
	-@erase "$(INTDIR)\Selectex.obj"
	-@erase "$(INTDIR)\Selectex.sbr"
	-@erase "$(INTDIR)\SelNum.obj"
	-@erase "$(INTDIR)\SelNum.sbr"
	-@erase "$(INTDIR)\Selset.obj"
	-@erase "$(INTDIR)\Selset.sbr"
	-@erase "$(INTDIR)\StatBarE.obj"
	-@erase "$(INTDIR)\StatBarE.sbr"
	-@erase "$(INTDIR)\StatDlg.obj"
	-@erase "$(INTDIR)\StatDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\Strutil.sbr"
	-@erase "$(INTDIR)\TablNDlg.obj"
	-@erase "$(INTDIR)\TablNDlg.sbr"
	-@erase "$(INTDIR)\TransPge.obj"
	-@erase "$(INTDIR)\TransPge.sbr"
	-@erase "$(INTDIR)\TransSet.obj"
	-@erase "$(INTDIR)\TransSet.sbr"
	-@erase "$(INTDIR)\UserInfo.obj"
	-@erase "$(INTDIR)\UserInfo.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\waitcext.obj"
	-@erase "$(INTDIR)\waitcext.sbr"
	-@erase "$(OUTDIR)\Gak.bsc"
	-@erase "$(OUTDIR)\Gak.exe"
	-@erase "$(OUTDIR)\Gak.ilk"
	-@erase "$(OUTDIR)\Gak.pdb"
	-@erase "$(OutDir)\$(TargetName).hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\Gak.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\gak.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gak.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AbfallP.sbr" \
	"$(INTDIR)\AbfArSet.sbr" \
	"$(INTDIR)\AbfDoc.sbr" \
	"$(INTDIR)\AbfFrame.sbr" \
	"$(INTDIR)\AbfPage.sbr" \
	"$(INTDIR)\AbfSet.sbr" \
	"$(INTDIR)\AbfSetEx.sbr" \
	"$(INTDIR)\AbfSheet.sbr" \
	"$(INTDIR)\AbfView.sbr" \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\Afidlg.sbr" \
	"$(INTDIR)\anfpage.sbr" \
	"$(INTDIR)\BetrPage.sbr" \
	"$(INTDIR)\BrancheP.sbr" \
	"$(INTDIR)\BranPage.sbr" \
	"$(INTDIR)\ChangeNr.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\Compact.sbr" \
	"$(INTDIR)\daotools.sbr" \
	"$(INTDIR)\DocumExt.sbr" \
	"$(INTDIR)\DoImpPge.sbr" \
	"$(INTDIR)\EnterNr.sbr" \
	"$(INTDIR)\EntPage.sbr" \
	"$(INTDIR)\Entspage.sbr" \
	"$(INTDIR)\EntsSet.sbr" \
	"$(INTDIR)\ErzFrame.sbr" \
	"$(INTDIR)\ErzPar.sbr" \
	"$(INTDIR)\ErzSheet.sbr" \
	"$(INTDIR)\Exportre.sbr" \
	"$(INTDIR)\FeldInfo.sbr" \
	"$(INTDIR)\FirmaSet.sbr" \
	"$(INTDIR)\firmpage.sbr" \
	"$(INTDIR)\gak.sbr" \
	"$(INTDIR)\gakDoc.sbr" \
	"$(INTDIR)\gakSet.sbr" \
	"$(INTDIR)\Gaksete.sbr" \
	"$(INTDIR)\gakView.sbr" \
	"$(INTDIR)\GebietP.sbr" \
	"$(INTDIR)\Getodbci.sbr" \
	"$(INTDIR)\Importty.sbr" \
	"$(INTDIR)\ImpParPg.sbr" \
	"$(INTDIR)\ImpQuery.sbr" \
	"$(INTDIR)\ImpResPg.sbr" \
	"$(INTDIR)\ImprtDlg.sbr" \
	"$(INTDIR)\ImpSumPg.sbr" \
	"$(INTDIR)\InTablPg.sbr" \
	"$(INTDIR)\KreisSet.sbr" \
	"$(INTDIR)\Listext.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\NewQuery.sbr" \
	"$(INTDIR)\Numedit.sbr" \
	"$(INTDIR)\OutTbPg.sbr" \
	"$(INTDIR)\PartPage.sbr" \
	"$(INTDIR)\Peplus.sbr" \
	"$(INTDIR)\Progress.sbr" \
	"$(INTDIR)\QueryDlg.sbr" \
	"$(INTDIR)\QueryPar.sbr" \
	"$(INTDIR)\querypr.sbr" \
	"$(INTDIR)\QueryRes.sbr" \
	"$(INTDIR)\Recview.sbr" \
	"$(INTDIR)\ResultP.sbr" \
	"$(INTDIR)\SearchSe.sbr" \
	"$(INTDIR)\SearRes.sbr" \
	"$(INTDIR)\Selectex.sbr" \
	"$(INTDIR)\SelNum.sbr" \
	"$(INTDIR)\Selset.sbr" \
	"$(INTDIR)\StatBarE.sbr" \
	"$(INTDIR)\StatDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Strutil.sbr" \
	"$(INTDIR)\TablNDlg.sbr" \
	"$(INTDIR)\TransPge.sbr" \
	"$(INTDIR)\TransSet.sbr" \
	"$(INTDIR)\UserInfo.sbr" \
	"$(INTDIR)\waitcext.sbr"

"$(OUTDIR)\Gak.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=crpe32m.lib odbccp32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\Gak.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\Gak.exe" /stub:"rights.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AbfallP.obj" \
	"$(INTDIR)\AbfArSet.obj" \
	"$(INTDIR)\AbfDoc.obj" \
	"$(INTDIR)\AbfFrame.obj" \
	"$(INTDIR)\AbfPage.obj" \
	"$(INTDIR)\AbfSet.obj" \
	"$(INTDIR)\AbfSetEx.obj" \
	"$(INTDIR)\AbfSheet.obj" \
	"$(INTDIR)\AbfView.obj" \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\Afidlg.obj" \
	"$(INTDIR)\anfpage.obj" \
	"$(INTDIR)\BetrPage.obj" \
	"$(INTDIR)\BrancheP.obj" \
	"$(INTDIR)\BranPage.obj" \
	"$(INTDIR)\ChangeNr.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Compact.obj" \
	"$(INTDIR)\daotools.obj" \
	"$(INTDIR)\DocumExt.obj" \
	"$(INTDIR)\DoImpPge.obj" \
	"$(INTDIR)\EnterNr.obj" \
	"$(INTDIR)\EntPage.obj" \
	"$(INTDIR)\Entspage.obj" \
	"$(INTDIR)\EntsSet.obj" \
	"$(INTDIR)\ErzFrame.obj" \
	"$(INTDIR)\ErzPar.obj" \
	"$(INTDIR)\ErzSheet.obj" \
	"$(INTDIR)\Exportre.obj" \
	"$(INTDIR)\FeldInfo.obj" \
	"$(INTDIR)\FirmaSet.obj" \
	"$(INTDIR)\firmpage.obj" \
	"$(INTDIR)\gak.obj" \
	"$(INTDIR)\gak.res" \
	"$(INTDIR)\gakDoc.obj" \
	"$(INTDIR)\gakSet.obj" \
	"$(INTDIR)\Gaksete.obj" \
	"$(INTDIR)\gakView.obj" \
	"$(INTDIR)\GebietP.obj" \
	"$(INTDIR)\Getodbci.obj" \
	"$(INTDIR)\Importty.obj" \
	"$(INTDIR)\ImpParPg.obj" \
	"$(INTDIR)\ImpQuery.obj" \
	"$(INTDIR)\ImpResPg.obj" \
	"$(INTDIR)\ImprtDlg.obj" \
	"$(INTDIR)\ImpSumPg.obj" \
	"$(INTDIR)\InTablPg.obj" \
	"$(INTDIR)\KreisSet.obj" \
	"$(INTDIR)\Listext.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NewQuery.obj" \
	"$(INTDIR)\Numedit.obj" \
	"$(INTDIR)\OutTbPg.obj" \
	"$(INTDIR)\PartPage.obj" \
	"$(INTDIR)\Peplus.obj" \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\QueryDlg.obj" \
	"$(INTDIR)\QueryPar.obj" \
	"$(INTDIR)\querypr.obj" \
	"$(INTDIR)\QueryRes.obj" \
	"$(INTDIR)\Recview.obj" \
	"$(INTDIR)\ResultP.obj" \
	"$(INTDIR)\SearchSe.obj" \
	"$(INTDIR)\SearRes.obj" \
	"$(INTDIR)\Selectex.obj" \
	"$(INTDIR)\SelNum.obj" \
	"$(INTDIR)\Selset.obj" \
	"$(INTDIR)\StatBarE.obj" \
	"$(INTDIR)\StatDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TablNDlg.obj" \
	"$(INTDIR)\TransPge.obj" \
	"$(INTDIR)\TransSet.obj" \
	"$(INTDIR)\UserInfo.obj" \
	"$(INTDIR)\waitcext.obj"

"$(OUTDIR)\Gak.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "gak - Win32 Release" || "$(CFG)" == "gak - Win32 Debug"
SOURCE=.\AbfallP.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFAL=\
	".\AbfallP.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfallP.obj" : $(SOURCE) $(DEP_CPP_ABFAL) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFAL=\
	".\AbfallP.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfallP.obj"	"$(INTDIR)\AbfallP.sbr" : $(SOURCE) $(DEP_CPP_ABFAL)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfArSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFAR=\
	".\Abfarset.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfArSet.obj" : $(SOURCE) $(DEP_CPP_ABFAR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFAR=\
	".\Abfarset.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfArSet.obj"	"$(INTDIR)\AbfArSet.sbr" : $(SOURCE) $(DEP_CPP_ABFAR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfDoc.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFDO=\
	".\Abfdoc.h"\
	".\AbfSet.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfDoc.obj" : $(SOURCE) $(DEP_CPP_ABFDO) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFDO=\
	".\Abfdoc.h"\
	".\AbfSet.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfDoc.obj"	"$(INTDIR)\AbfDoc.sbr" : $(SOURCE) $(DEP_CPP_ABFDO)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfFrame.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFFR=\
	".\Abfframe.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfFrame.obj" : $(SOURCE) $(DEP_CPP_ABFFR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFFR=\
	".\Abfframe.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfFrame.obj"	"$(INTDIR)\AbfFrame.sbr" : $(SOURCE) $(DEP_CPP_ABFFR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfPage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFPA=\
	".\Abfarset.h"\
	".\AbfPage.h"\
	".\AbfSet.h"\
	".\Abfsheet.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfPage.obj" : $(SOURCE) $(DEP_CPP_ABFPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFPA=\
	".\Abfarset.h"\
	".\AbfPage.h"\
	".\AbfSet.h"\
	".\Abfsheet.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfPage.obj"	"$(INTDIR)\AbfPage.sbr" : $(SOURCE) $(DEP_CPP_ABFPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFSE=\
	".\AbfSet.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSet.obj" : $(SOURCE) $(DEP_CPP_ABFSE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFSE=\
	".\AbfSet.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSet.obj"	"$(INTDIR)\AbfSet.sbr" : $(SOURCE) $(DEP_CPP_ABFSE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfSetEx.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFSET=\
	".\Abfsetex.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSetEx.obj" : $(SOURCE) $(DEP_CPP_ABFSET) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFSET=\
	".\Abfsetex.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSetEx.obj"	"$(INTDIR)\AbfSetEx.sbr" : $(SOURCE) $(DEP_CPP_ABFSET)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfSheet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFSH=\
	".\AbfPage.h"\
	".\Abfsheet.h"\
	".\AbfView.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Recview.h"\
	".\Stdafx.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSheet.obj" : $(SOURCE) $(DEP_CPP_ABFSH) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFSH=\
	".\AbfPage.h"\
	".\Abfsheet.h"\
	".\AbfView.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Recview.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfSheet.obj"	"$(INTDIR)\AbfSheet.sbr" : $(SOURCE) $(DEP_CPP_ABFSH)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\AbfView.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABFVI=\
	".\Abfarset.h"\
	".\Abfdoc.h"\
	".\AbfPage.h"\
	".\AbfSet.h"\
	".\Abfsheet.h"\
	".\AbfView.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\Recview.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfView.obj" : $(SOURCE) $(DEP_CPP_ABFVI) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABFVI=\
	".\Abfarset.h"\
	".\Abfdoc.h"\
	".\AbfPage.h"\
	".\AbfSet.h"\
	".\Abfsheet.h"\
	".\AbfView.h"\
	".\BetrPage.h"\
	".\Branpage.h"\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\EntPage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\Recview.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\TransPge.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\AbfView.obj"	"$(INTDIR)\AbfView.sbr" : $(SOURCE) $(DEP_CPP_ABFVI)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\about.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ABOUT=\
	".\About.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\about.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ABOUT=\
	".\About.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) $(DEP_CPP_ABOUT)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Afidlg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_AFIDL=\
	".\Afidlg.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\KreisSet.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Afidlg.obj" : $(SOURCE) $(DEP_CPP_AFIDL) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_AFIDL=\
	".\Afidlg.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\KreisSet.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Afidlg.obj"	"$(INTDIR)\Afidlg.sbr" : $(SOURCE) $(DEP_CPP_AFIDL)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\anfpage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ANFPA=\
	".\Anfpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\anfpage.obj" : $(SOURCE) $(DEP_CPP_ANFPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ANFPA=\
	".\Anfpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\anfpage.obj"	"$(INTDIR)\anfpage.sbr" : $(SOURCE) $(DEP_CPP_ANFPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\BetrPage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_BETRP=\
	".\AbfSet.h"\
	".\BetrPage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BetrPage.obj" : $(SOURCE) $(DEP_CPP_BETRP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_BETRP=\
	".\AbfSet.h"\
	".\BetrPage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BetrPage.obj"	"$(INTDIR)\BetrPage.sbr" : $(SOURCE) $(DEP_CPP_BETRP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\BrancheP.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_BRANC=\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BrancheP.obj" : $(SOURCE) $(DEP_CPP_BRANC) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_BRANC=\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BrancheP.obj"	"$(INTDIR)\BrancheP.sbr" : $(SOURCE) $(DEP_CPP_BRANC)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\BranPage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_BRANP=\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BranPage.obj" : $(SOURCE) $(DEP_CPP_BRANP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_BRANP=\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\BranPage.obj"	"$(INTDIR)\BranPage.sbr" : $(SOURCE) $(DEP_CPP_BRANP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ChangeNr.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_CHANG=\
	".\Changenr.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Searchse.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ChangeNr.obj" : $(SOURCE) $(DEP_CPP_CHANG) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_CHANG=\
	".\Changenr.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Searchse.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ChangeNr.obj"	"$(INTDIR)\ChangeNr.sbr" : $(SOURCE) $(DEP_CPP_CHANG)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_CHILD=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Recview.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_CHILD=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Recview.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Compact.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_COMPA=\
	".\Compact.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Compact.obj" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_COMPA=\
	".\Compact.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Compact.obj"	"$(INTDIR)\Compact.sbr" : $(SOURCE) $(DEP_CPP_COMPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\daotools.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_DAOTO=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\daotools.obj" : $(SOURCE) $(DEP_CPP_DAOTO) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_DAOTO=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\daotools.obj"	"$(INTDIR)\daotools.sbr" : $(SOURCE) $(DEP_CPP_DAOTO)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\DocumExt.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_DOCUM=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\DocumExt.obj" : $(SOURCE) $(DEP_CPP_DOCUM) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_DOCUM=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\DocumExt.obj"	"$(INTDIR)\DocumExt.sbr" : $(SOURCE) $(DEP_CPP_DOCUM)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\DoImpPge.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_DOIMP=\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\DoImpPge.obj" : $(SOURCE) $(DEP_CPP_DOIMP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_DOIMP=\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\DoImpPge.obj"	"$(INTDIR)\DoImpPge.sbr" : $(SOURCE) $(DEP_CPP_DOIMP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\EnterNr.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ENTER=\
	".\Daotools.h"\
	".\Enternr.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EnterNr.obj" : $(SOURCE) $(DEP_CPP_ENTER) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ENTER=\
	".\Daotools.h"\
	".\Enternr.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EnterNr.obj"	"$(INTDIR)\EnterNr.sbr" : $(SOURCE) $(DEP_CPP_ENTER)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\EntPage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ENTPA=\
	".\AbfSet.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Entsset.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EntPage.obj" : $(SOURCE) $(DEP_CPP_ENTPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ENTPA=\
	".\AbfSet.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\EntPage.h"\
	".\Entsset.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EntPage.obj"	"$(INTDIR)\EntPage.sbr" : $(SOURCE) $(DEP_CPP_ENTPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Entspage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ENTSP=\
	".\Daotools.h"\
	".\Entspage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Entspage.obj" : $(SOURCE) $(DEP_CPP_ENTSP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ENTSP=\
	".\Daotools.h"\
	".\Entspage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Entspage.obj"	"$(INTDIR)\Entspage.sbr" : $(SOURCE) $(DEP_CPP_ENTSP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\EntsSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ENTSS=\
	".\Daotools.h"\
	".\Entsset.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EntsSet.obj" : $(SOURCE) $(DEP_CPP_ENTSS) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ENTSS=\
	".\Daotools.h"\
	".\Entsset.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\EntsSet.obj"	"$(INTDIR)\EntsSet.sbr" : $(SOURCE) $(DEP_CPP_ENTSS)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ErzFrame.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ERZFR=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Erzframe.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzFrame.obj" : $(SOURCE) $(DEP_CPP_ERZFR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ERZFR=\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Erzframe.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzFrame.obj"	"$(INTDIR)\ErzFrame.sbr" : $(SOURCE) $(DEP_CPP_ERZFR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ErzPar.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ERZPA=\
	".\Changenr.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\FirmaSet.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzPar.obj" : $(SOURCE) $(DEP_CPP_ERZPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ERZPA=\
	".\Changenr.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\FirmaSet.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzPar.obj"	"$(INTDIR)\ErzPar.sbr" : $(SOURCE) $(DEP_CPP_ERZPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ErzSheet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_ERZSH=\
	".\Anfpage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Entspage.h"\
	".\Erzsheet.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Partpage.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzSheet.obj" : $(SOURCE) $(DEP_CPP_ERZSH) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_ERZSH=\
	".\Anfpage.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Entspage.h"\
	".\Erzsheet.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Partpage.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ErzSheet.obj"	"$(INTDIR)\ErzSheet.sbr" : $(SOURCE) $(DEP_CPP_ERZSH)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Exportre.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_EXPOR=\
	".\Daotools.h"\
	".\Exportre.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Exportre.obj" : $(SOURCE) $(DEP_CPP_EXPOR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_EXPOR=\
	".\Daotools.h"\
	".\Exportre.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Exportre.obj"	"$(INTDIR)\Exportre.sbr" : $(SOURCE) $(DEP_CPP_EXPOR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\FeldInfo.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_FELDI=\
	".\Daotools.h"\
	".\FeldInfo.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\FeldInfo.obj" : $(SOURCE) $(DEP_CPP_FELDI) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_FELDI=\
	".\Daotools.h"\
	".\FeldInfo.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\FeldInfo.obj"	"$(INTDIR)\FeldInfo.sbr" : $(SOURCE) $(DEP_CPP_FELDI)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\FirmaSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_FIRMA=\
	".\Daotools.h"\
	".\FirmaSet.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\FirmaSet.obj" : $(SOURCE) $(DEP_CPP_FIRMA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_FIRMA=\
	".\Daotools.h"\
	".\FirmaSet.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\FirmaSet.obj"	"$(INTDIR)\FirmaSet.sbr" : $(SOURCE) $(DEP_CPP_FIRMA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\firmpage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_FIRMP=\
	".\Daotools.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\firmpage.obj" : $(SOURCE) $(DEP_CPP_FIRMP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_FIRMP=\
	".\Daotools.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\firmpage.obj"	"$(INTDIR)\firmpage.sbr" : $(SOURCE) $(DEP_CPP_FIRMP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\gak.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GAK_C=\
	".\Abfdoc.h"\
	".\Abfframe.h"\
	".\AbfSet.h"\
	".\AbfView.h"\
	".\About.h"\
	".\Childfrm.h"\
	".\Compact.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Enternr.h"\
	".\Erzframe.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\gakView.h"\
	".\Getodbci.h"\
	".\MainFrm.h"\
	".\numedit.h"\
	".\peplus.h"\
	".\Querydlg.h"\
	".\Recview.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Statbare.h"\
	".\Stdafx.h"\
	".\Userinfo.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\gak.obj" : $(SOURCE) $(DEP_CPP_GAK_C) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GAK_C=\
	".\Abfdoc.h"\
	".\Abfframe.h"\
	".\AbfSet.h"\
	".\AbfView.h"\
	".\About.h"\
	".\Childfrm.h"\
	".\Compact.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Enternr.h"\
	".\Erzframe.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\gakView.h"\
	".\Getodbci.h"\
	".\MainFrm.h"\
	".\numedit.h"\
	".\peplus.h"\
	".\Querydlg.h"\
	".\Recview.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Statbare.h"\
	".\Userinfo.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\gak.obj"	"$(INTDIR)\gak.sbr" : $(SOURCE) $(DEP_CPP_GAK_C)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\hlp\gak.hpj

!IF  "$(CFG)" == "gak - Win32 Release"

OutDir=.\.\Release
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

OutDir=.\.\Debug
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

!ENDIF 

SOURCE=.\gak.rc
DEP_RSC_GAK_R=\
	".\res\artchad.bmp"\
	".\res\artchaf.bmp"\
	".\res\artchau.bmp"\
	".\res\artchax.bmp"\
	".\res\artdeld.bmp"\
	".\res\artdelf.bmp"\
	".\res\artdelu.bmp"\
	".\res\artdelx.bmp"\
	".\res\ARTNEUD.bmp"\
	".\res\artneuf.bmp"\
	".\res\artneuu.bmp"\
	".\res\artneux.bmp"\
	".\res\gak.rc2"\
	".\res\gakDoc.ico"\
	".\res\idr_main.ico"\
	".\res\imageli.bmp"\
	".\res\Toolbar.bmp"\
	".\resource.hm"\
	

"$(INTDIR)\gak.res" : $(SOURCE) $(DEP_RSC_GAK_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\gakDoc.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GAKDO=\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\gakDoc.obj" : $(SOURCE) $(DEP_CPP_GAKDO) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GAKDO=\
	".\Daotools.h"\
	".\Documext.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\gakDoc.obj"	"$(INTDIR)\gakDoc.sbr" : $(SOURCE) $(DEP_CPP_GAKDO)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\gakSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GAKSE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\gakSet.obj" : $(SOURCE) $(DEP_CPP_GAKSE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GAKSE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\gakSet.obj"	"$(INTDIR)\gakSet.sbr" : $(SOURCE) $(DEP_CPP_GAKSE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Gaksete.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GAKSET=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Gaksete.obj" : $(SOURCE) $(DEP_CPP_GAKSET) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GAKSET=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Gaksete.obj"	"$(INTDIR)\Gaksete.sbr" : $(SOURCE) $(DEP_CPP_GAKSET)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\gakView.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GAKVI=\
	".\AbfSet.h"\
	".\Anfpage.h"\
	".\Branpage.h"\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Entspage.h"\
	".\Erzsheet.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\gakView.h"\
	".\numedit.h"\
	".\Partpage.h"\
	".\peplus.h"\
	".\Recview.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\gakView.obj" : $(SOURCE) $(DEP_CPP_GAKVI) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GAKVI=\
	".\AbfSet.h"\
	".\Anfpage.h"\
	".\Branpage.h"\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Documext.h"\
	".\Entspage.h"\
	".\Erzsheet.h"\
	".\Firmpage.h"\
	".\Gak.h"\
	".\Gakdoc.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\gakView.h"\
	".\numedit.h"\
	".\Partpage.h"\
	".\peplus.h"\
	".\Recview.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\gakView.obj"	"$(INTDIR)\gakView.sbr" : $(SOURCE) $(DEP_CPP_GAKVI)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\GebietP.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GEBIE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\GebietP.obj" : $(SOURCE) $(DEP_CPP_GEBIE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GEBIE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\GebietP.obj"	"$(INTDIR)\GebietP.sbr" : $(SOURCE) $(DEP_CPP_GEBIE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Getodbci.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_GETOD=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Getodbci.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Getodbci.obj" : $(SOURCE) $(DEP_CPP_GETOD) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_GETOD=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Getodbci.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Getodbci.obj"	"$(INTDIR)\Getodbci.sbr" : $(SOURCE) $(DEP_CPP_GETOD)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Importty.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPOR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Importty.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPOR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Importty.obj"	"$(INTDIR)\Importty.sbr" : $(SOURCE) $(DEP_CPP_IMPOR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ImpParPg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPPA=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpParPg.obj" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPPA=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpParPg.obj"	"$(INTDIR)\ImpParPg.sbr" : $(SOURCE) $(DEP_CPP_IMPPA)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ImpQuery.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPQU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Impquery.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpQuery.obj" : $(SOURCE) $(DEP_CPP_IMPQU) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPQU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Impquery.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpQuery.obj"	"$(INTDIR)\ImpQuery.sbr" : $(SOURCE) $(DEP_CPP_IMPQU)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ImpResPg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPRE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Imprespg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpResPg.obj" : $(SOURCE) $(DEP_CPP_IMPRE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPRE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Imprespg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpResPg.obj"	"$(INTDIR)\ImpResPg.sbr" : $(SOURCE) $(DEP_CPP_IMPRE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ImprtDlg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPRT=\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Imprespg.h"\
	".\Imprtdlg.h"\
	".\Impsumpg.h"\
	".\Intablpg.h"\
	".\Outtbpg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImprtDlg.obj" : $(SOURCE) $(DEP_CPP_IMPRT) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPRT=\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Imprespg.h"\
	".\Imprtdlg.h"\
	".\Impsumpg.h"\
	".\Intablpg.h"\
	".\Outtbpg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImprtDlg.obj"	"$(INTDIR)\ImprtDlg.sbr" : $(SOURCE) $(DEP_CPP_IMPRT)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ImpSumPg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_IMPSU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impsumpg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpSumPg.obj" : $(SOURCE) $(DEP_CPP_IMPSU) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_IMPSU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Impsumpg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ImpSumPg.obj"	"$(INTDIR)\ImpSumPg.sbr" : $(SOURCE) $(DEP_CPP_IMPSU)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\InTablPg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_INTAB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Intablpg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\InTablPg.obj" : $(SOURCE) $(DEP_CPP_INTAB) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_INTAB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Intablpg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\InTablPg.obj"	"$(INTDIR)\InTablPg.sbr" : $(SOURCE) $(DEP_CPP_INTAB)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\KreisSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_KREIS=\
	".\Daotools.h"\
	".\Gak.h"\
	".\KreisSet.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\KreisSet.obj" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_KREIS=\
	".\Daotools.h"\
	".\Gak.h"\
	".\KreisSet.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\KreisSet.obj"	"$(INTDIR)\KreisSet.sbr" : $(SOURCE) $(DEP_CPP_KREIS)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Listext.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_LISTE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\Listext.obj" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_LISTE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\Listext.obj"	"$(INTDIR)\Listext.sbr" : $(SOURCE) $(DEP_CPP_LISTE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_MAINF=\
	".\Abfarset.h"\
	".\Abfsetex.h"\
	".\Afidlg.h"\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Exportre.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Getodbci.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Imprespg.h"\
	".\Imprtdlg.h"\
	".\Impsumpg.h"\
	".\Intablpg.h"\
	".\MainFrm.h"\
	".\Outtbpg.h"\
	".\Progress.h"\
	".\Selectex.h"\
	".\Selset.h"\
	".\Statbare.h"\
	".\Statdlg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_MAINF=\
	".\Abfarset.h"\
	".\Abfsetex.h"\
	".\Afidlg.h"\
	".\Daotools.h"\
	".\Doimppge.h"\
	".\Exportre.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Getodbci.h"\
	".\Importty.h"\
	".\Impparpg.h"\
	".\Imprespg.h"\
	".\Imprtdlg.h"\
	".\Impsumpg.h"\
	".\Intablpg.h"\
	".\MainFrm.h"\
	".\Outtbpg.h"\
	".\Progress.h"\
	".\Selectex.h"\
	".\Selset.h"\
	".\Statbare.h"\
	".\Statdlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\NewQuery.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_NEWQU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Newquery.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\NewQuery.obj" : $(SOURCE) $(DEP_CPP_NEWQU) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_NEWQU=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Newquery.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\NewQuery.obj"	"$(INTDIR)\NewQuery.sbr" : $(SOURCE) $(DEP_CPP_NEWQU)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Numedit.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_NUMED=\
	".\Daotools.h"\
	".\numedit.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Numedit.obj" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_NUMED=\
	".\Daotools.h"\
	".\numedit.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Numedit.obj"	"$(INTDIR)\Numedit.sbr" : $(SOURCE) $(DEP_CPP_NUMED)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\OutTbPg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_OUTTB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Outtbpg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\OutTbPg.obj" : $(SOURCE) $(DEP_CPP_OUTTB) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_OUTTB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Importty.h"\
	".\Outtbpg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\OutTbPg.obj"	"$(INTDIR)\OutTbPg.sbr" : $(SOURCE) $(DEP_CPP_OUTTB)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\PartPage.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_PARTP=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Partpage.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\PartPage.obj" : $(SOURCE) $(DEP_CPP_PARTP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_PARTP=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gakset.h"\
	".\Gaksete.h"\
	".\Partpage.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\PartPage.obj"	"$(INTDIR)\PartPage.sbr" : $(SOURCE) $(DEP_CPP_PARTP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Peplus.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_PEPLU=\
	".\Daotools.h"\
	".\peplus.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\Peplus.obj" : $(SOURCE) $(DEP_CPP_PEPLU) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_PEPLU=\
	".\Daotools.h"\
	".\peplus.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\Peplus.obj"	"$(INTDIR)\Peplus.sbr" : $(SOURCE) $(DEP_CPP_PEPLU)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Progress.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_PROGR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Progress.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Progress.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_PROGR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Progress.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Progress.obj"	"$(INTDIR)\Progress.sbr" : $(SOURCE) $(DEP_CPP_PROGR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\QueryDlg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_QUERY=\
	".\AbfallP.h"\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\Impquery.h"\
	".\Newquery.h"\
	".\numedit.h"\
	".\Querydlg.h"\
	".\Querypar.h"\
	".\Queryres.h"\
	".\ResultP.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\QueryDlg.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_QUERY=\
	".\AbfallP.h"\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\Impquery.h"\
	".\Newquery.h"\
	".\numedit.h"\
	".\Querydlg.h"\
	".\Querypar.h"\
	".\Queryres.h"\
	".\ResultP.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\QueryDlg.obj"	"$(INTDIR)\QueryDlg.sbr" : $(SOURCE) $(DEP_CPP_QUERY)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\QueryPar.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_QUERYP=\
	".\AbfallP.h"\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\numedit.h"\
	".\Querypar.h"\
	".\ResultP.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\QueryPar.obj" : $(SOURCE) $(DEP_CPP_QUERYP) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_QUERYP=\
	".\AbfallP.h"\
	".\BrancheP.h"\
	".\Daotools.h"\
	".\ErzPar.h"\
	".\Gak.h"\
	".\GebietP.h"\
	".\numedit.h"\
	".\Querypar.h"\
	".\ResultP.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\QueryPar.obj"	"$(INTDIR)\QueryPar.sbr" : $(SOURCE) $(DEP_CPP_QUERYP)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\querypr.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_QUERYPR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\querypr.obj" : $(SOURCE) $(DEP_CPP_QUERYPR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_QUERYPR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\querypr.obj"	"$(INTDIR)\querypr.sbr" : $(SOURCE) $(DEP_CPP_QUERYPR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\QueryRes.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_QUERYR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Queryres.h"\
	".\Stdafx.h"\
	".\TablNDlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\QueryRes.obj" : $(SOURCE) $(DEP_CPP_QUERYR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_QUERYR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Queryres.h"\
	".\TablNDlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\QueryRes.obj"	"$(INTDIR)\QueryRes.sbr" : $(SOURCE) $(DEP_CPP_QUERYR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Recview.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_RECVI=\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\peplus.h"\
	".\Recview.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\Recview.obj" : $(SOURCE) $(DEP_CPP_RECVI) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_RECVI=\
	".\Changenr.h"\
	".\Childfrm.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\numedit.h"\
	".\peplus.h"\
	".\Recview.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"crpe.h"\
	

"$(INTDIR)\Recview.obj"	"$(INTDIR)\Recview.sbr" : $(SOURCE) $(DEP_CPP_RECVI)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\ResultP.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_RESUL=\
	".\Daotools.h"\
	".\Gak.h"\
	".\ResultP.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ResultP.obj" : $(SOURCE) $(DEP_CPP_RESUL) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_RESUL=\
	".\Daotools.h"\
	".\Gak.h"\
	".\ResultP.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\ResultP.obj"	"$(INTDIR)\ResultP.sbr" : $(SOURCE) $(DEP_CPP_RESUL)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\SearchSe.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_SEARC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Searchse.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\SearchSe.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_SEARC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Searchse.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\SearchSe.obj"	"$(INTDIR)\SearchSe.sbr" : $(SOURCE) $(DEP_CPP_SEARC)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\SearRes.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_SEARR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\SearRes.obj" : $(SOURCE) $(DEP_CPP_SEARR) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_SEARR=\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Searchse.h"\
	".\Searres.h"\
	".\Waitcext.h"\
	{$(INCLUDE)}"listext.hpp"\
	

"$(INTDIR)\SearRes.obj"	"$(INTDIR)\SearRes.sbr" : $(SOURCE) $(DEP_CPP_SEARR)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Selectex.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_SELEC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selectex.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Selectex.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_SELEC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selectex.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Selectex.obj"	"$(INTDIR)\Selectex.sbr" : $(SOURCE) $(DEP_CPP_SELEC)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\SelNum.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_SELNU=\
	".\Daotools.h"\
	".\FeldInfo.h"\
	".\Gak.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\SelNum.obj" : $(SOURCE) $(DEP_CPP_SELNU) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_SELNU=\
	".\Daotools.h"\
	".\FeldInfo.h"\
	".\Gak.h"\
	".\Selnum.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\SelNum.obj"	"$(INTDIR)\SelNum.sbr" : $(SOURCE) $(DEP_CPP_SELNU)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\Selset.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_SELSE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Selset.obj" : $(SOURCE) $(DEP_CPP_SELSE) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_SELSE=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Selset.obj"	"$(INTDIR)\Selset.sbr" : $(SOURCE) $(DEP_CPP_SELSE)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\StatBarE.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_STATB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Statbare.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\StatBarE.obj" : $(SOURCE) $(DEP_CPP_STATB) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_STATB=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Statbare.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\StatBarE.obj"	"$(INTDIR)\StatBarE.sbr" : $(SOURCE) $(DEP_CPP_STATB)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\StatDlg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_STATD=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Statdlg.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\StatDlg.obj" : $(SOURCE) $(DEP_CPP_STATD) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_STATD=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Statdlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\StatDlg.obj"	"$(INTDIR)\StatDlg.sbr" : $(SOURCE) $(DEP_CPP_STATD)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Daotools.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

!IF  "$(CFG)" == "gak - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG"\
 /Fp"$(INTDIR)\Gak.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Gak.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Gak.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Gak.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Strutil.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_STRUT=\
	".\Daotools.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_STRUT=\
	".\Daotools.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\Strutil.obj"	"$(INTDIR)\Strutil.sbr" : $(SOURCE) $(DEP_CPP_STRUT)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\TablNDlg.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_TABLN=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Stdafx.h"\
	".\TablNDlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TablNDlg.obj" : $(SOURCE) $(DEP_CPP_TABLN) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_TABLN=\
	".\Daotools.h"\
	".\Gak.h"\
	".\TablNDlg.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TablNDlg.obj"	"$(INTDIR)\TablNDlg.sbr" : $(SOURCE) $(DEP_CPP_TABLN)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\TransPge.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_TRANS=\
	".\AbfSet.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\TransPge.h"\
	".\Transset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TransPge.obj" : $(SOURCE) $(DEP_CPP_TRANS) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_TRANS=\
	".\AbfSet.h"\
	".\Branpage.h"\
	".\Daotools.h"\
	".\Gak.h"\
	".\Gaksete.h"\
	".\Selset.h"\
	".\TransPge.h"\
	".\Transset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TransPge.obj"	"$(INTDIR)\TransPge.sbr" : $(SOURCE) $(DEP_CPP_TRANS)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\TransSet.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_TRANSS=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Stdafx.h"\
	".\Transset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TransSet.obj" : $(SOURCE) $(DEP_CPP_TRANSS) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_TRANSS=\
	".\Daotools.h"\
	".\Gak.h"\
	".\Selset.h"\
	".\Transset.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\TransSet.obj"	"$(INTDIR)\TransSet.sbr" : $(SOURCE) $(DEP_CPP_TRANSS)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\UserInfo.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_USERI=\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Stdafx.h"\
	".\Userinfo.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\UserInfo.obj" : $(SOURCE) $(DEP_CPP_USERI) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_USERI=\
	".\Daotools.h"\
	".\Gak.h"\
	".\numedit.h"\
	".\Userinfo.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\UserInfo.obj"	"$(INTDIR)\UserInfo.sbr" : $(SOURCE) $(DEP_CPP_USERI)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 

SOURCE=.\waitcext.cpp

!IF  "$(CFG)" == "gak - Win32 Release"

DEP_CPP_WAITC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\MainFrm.h"\
	".\Statbare.h"\
	".\Stdafx.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\waitcext.obj" : $(SOURCE) $(DEP_CPP_WAITC) "$(INTDIR)"\
 "$(INTDIR)\Gak.pch"


!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

DEP_CPP_WAITC=\
	".\Daotools.h"\
	".\Gak.h"\
	".\MainFrm.h"\
	".\Statbare.h"\
	".\Waitcext.h"\
	

"$(INTDIR)\waitcext.obj"	"$(INTDIR)\waitcext.sbr" : $(SOURCE) $(DEP_CPP_WAITC)\
 "$(INTDIR)" "$(INTDIR)\Gak.pch"


!ENDIF 


!ENDIF 

