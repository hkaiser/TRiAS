# Microsoft Developer Studio Generated NMAKE File, Based on Oleauto4.dsp
!IF "$(CFG)" == ""
CFG=Oleauto - Win32 Debug TrueTime
!MESSAGE No configuration specified. Defaulting to Oleauto - Win32 Debug TrueTime.
!ENDIF 

!IF "$(CFG)" != "Oleauto - Win32 Debug with BasicScript" && "$(CFG)" != "Oleauto - Win32 Release with BasicScript" && "$(CFG)" != "Oleauto - Win32 Debug TrueTime"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Oleauto4.mak" CFG="Oleauto - Win32 Debug TrueTime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Oleauto - Win32 Debug with BasicScript" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oleauto - Win32 Release with BasicScript" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oleauto - Win32 Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\oleauto.rcv" ".\Documentation\OleAuto.hlp" ".\Documentation\OleAuto.fmt" ".\Documentation\OleAuto.cnt" ".\Documentation\contents.hpj" ".\Debug/Triastlb.tlb" "$(TRIASINCLUDE)\Triastlb_i.c" "$(TRIASINCLUDE)\Triastlb.h" "$(OUTDIR)\oleautod.ext" "$(TRIASDIR_D)\oleautod.ext"


CLEAN :
	-@erase "$(INTDIR)\APP.OBJ"
	-@erase "$(INTDIR)\APPCF.OBJ"
	-@erase "$(INTDIR)\APPDISP.OBJ"
	-@erase "$(INTDIR)\APPNTFY.OBJ"
	-@erase "$(INTDIR)\ARRAY.OBJ"
	-@erase "$(INTDIR)\BILDOBJ.OBJ"
	-@erase "$(INTDIR)\BScriptNotify.obj"
	-@erase "$(INTDIR)\CLASS.OBJ"
	-@erase "$(INTDIR)\CLASSES.OBJ"
	-@erase "$(INTDIR)\CLIDTREE.OBJ"
	-@erase "$(INTDIR)\CLNMTREE.OBJ"
	-@erase "$(INTDIR)\CLSARRAY.OBJ"
	-@erase "$(INTDIR)\CLSDISP.OBJ"
	-@erase "$(INTDIR)\CLSSDISP.OBJ"
	-@erase "$(INTDIR)\CLSTREES.OBJ"
	-@erase "$(INTDIR)\CONMTREE.OBJ"
	-@erase "$(INTDIR)\Connect.obj"
	-@erase "$(INTDIR)\CONRTREE.OBJ"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\DLLDATAX.OBJ"
	-@erase "$(INTDIR)\DOC.OBJ"
	-@erase "$(INTDIR)\DOCARRAY.OBJ"
	-@erase "$(INTDIR)\DOCDISP.OBJ"
	-@erase "$(INTDIR)\DocDragnDrop.obj"
	-@erase "$(INTDIR)\DocLink.obj"
	-@erase "$(INTDIR)\DOCS.OBJ"
	-@erase "$(INTDIR)\DOCSDISP.OBJ"
	-@erase "$(INTDIR)\DOCTREE.OBJ"
	-@erase "$(INTDIR)\DragDrop.obj"
	-@erase "$(INTDIR)\ENUMCLSS.OBJ"
	-@erase "$(INTDIR)\ENUMDOCS.OBJ"
	-@erase "$(INTDIR)\ENUMFTS.OBJ"
	-@erase "$(INTDIR)\ENUMOBJS.OBJ"
	-@erase "$(INTDIR)\EnumObWs.obj"
	-@erase "$(INTDIR)\ENUVIEWS.OBJ"
	-@erase "$(INTDIR)\FEAT.OBJ"
	-@erase "$(INTDIR)\FEATDISP.OBJ"
	-@erase "$(INTDIR)\FTCLTREE.OBJ"
	-@erase "$(INTDIR)\FTOBTREE.OBJ"
	-@erase "$(INTDIR)\FTS.OBJ"
	-@erase "$(INTDIR)\FTSARRAY.OBJ"
	-@erase "$(INTDIR)\FTSDISP.OBJ"
	-@erase "$(INTDIR)\FTVWTREE.OBJ"
	-@erase "$(INTDIR)\GEOMETRY.OBJ"
	-@erase "$(INTDIR)\jumptab.obj"
	-@erase "$(INTDIR)\OBJ.OBJ"
	-@erase "$(INTDIR)\OBJARRAY.OBJ"
	-@erase "$(INTDIR)\OBJDISP.OBJ"
	-@erase "$(INTDIR)\ObjectProperty.obj"
	-@erase "$(INTDIR)\ObjectPropertyDual.obj"
	-@erase "$(INTDIR)\OBJS.OBJ"
	-@erase "$(INTDIR)\Objsdisp.obj"
	-@erase "$(INTDIR)\OBJTREES.OBJ"
	-@erase "$(INTDIR)\OBJWIN.OBJ"
	-@erase "$(INTDIR)\ObjWins.obj"
	-@erase "$(INTDIR)\ObWarray.obj"
	-@erase "$(INTDIR)\ObWdisp.obj"
	-@erase "$(INTDIR)\OLE2AUTO.OBJ"
	-@erase "$(INTDIR)\Oleauto.res"
	-@erase "$(INTDIR)\OLEAUTOD.idb"
	-@erase "$(INTDIR)\OLEAUTOD.pch"
	-@erase "$(INTDIR)\OLEBSEXT.OBJ"
	-@erase "$(INTDIR)\OWinTree.obj"
	-@erase "$(INTDIR)\PICTURE.OBJ"
	-@erase "$(INTDIR)\PictureExt.obj"
	-@erase "$(INTDIR)\PRECOMP.OBJ"
	-@erase "$(INTDIR)\PropActSeq.obj"
	-@erase "$(INTDIR)\PropNamex.obj"
	-@erase "$(INTDIR)\Rgb_hsb.obj"
	-@erase "$(INTDIR)\StatusIndExt.obj"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\ToolBarExt.obj"
	-@erase "$(INTDIR)\TRiASNotify.obj"
	-@erase "$(INTDIR)\TRiASNotifyDual.obj"
	-@erase "$(INTDIR)\VIEW.OBJ"
	-@erase "$(INTDIR)\VIEWARRY.OBJ"
	-@erase "$(INTDIR)\VIEWDISP.OBJ"
	-@erase "$(INTDIR)\ViewDropTarget.obj"
	-@erase "$(INTDIR)\VIEWS.OBJ"
	-@erase "$(INTDIR)\VIEWSDSP.OBJ"
	-@erase "$(INTDIR)\VIEWTREE.OBJ"
	-@erase "$(INTDIR)\VisInfoExt.obj"
	-@erase "$(INTDIR)\WrapperExtension.obj"
	-@erase "$(OUTDIR)\oleautod.exp"
	-@erase "$(OUTDIR)\oleautod.ext"
	-@erase "$(OUTDIR)\oleautod.ilk"
	-@erase "$(OUTDIR)\oleautod.lib"
	-@erase "$(OUTDIR)\OLEAUTOD.pdb"
	-@erase "$(TRIASDIR_D)\oleautod.ext"
	-@erase "$(TRIASINCLUDE)\Triastlb.h"
	-@erase "$(TRIASINCLUDE)\Triastlb_i.c"
	-@erase ".\Debug/Triastlb.tlb"
	-@erase ".\Documentation\contents.hpj"
	-@erase ".\Documentation\OleAuto.cnt"
	-@erase ".\Documentation\OleAuto.fmt"
	-@erase ".\Documentation\OleAuto.hlp"
	-@erase "oleauto.rcv"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Oleauto.res" /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oleauto4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ixtmad50.lib cont50d.lib ospace5d.lib ebn.lib Triastld.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\oleautod.pdb" /debug /machine:I386 /def:".\oleauto.def" /out:"$(OUTDIR)\oleautod.ext" /implib:"$(OUTDIR)\oleautod.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\oleauto.def"
LINK32_OBJS= \
	"$(INTDIR)\jumptab.obj" \
	"$(INTDIR)\OLEBSEXT.OBJ" \
	"$(INTDIR)\PictureExt.obj" \
	"$(INTDIR)\PropActSeq.obj" \
	"$(INTDIR)\PropNamex.obj" \
	"$(INTDIR)\StatusIndExt.obj" \
	"$(INTDIR)\ToolBarExt.obj" \
	"$(INTDIR)\VisInfoExt.obj" \
	"$(INTDIR)\CONMTREE.OBJ" \
	"$(INTDIR)\CONRTREE.OBJ" \
	"$(INTDIR)\ENUMOBJS.OBJ" \
	"$(INTDIR)\GEOMETRY.OBJ" \
	"$(INTDIR)\OBJ.OBJ" \
	"$(INTDIR)\OBJARRAY.OBJ" \
	"$(INTDIR)\OBJDISP.OBJ" \
	"$(INTDIR)\OBJS.OBJ" \
	"$(INTDIR)\Objsdisp.obj" \
	"$(INTDIR)\OBJTREES.OBJ" \
	"$(INTDIR)\ENUVIEWS.OBJ" \
	"$(INTDIR)\VIEW.OBJ" \
	"$(INTDIR)\VIEWARRY.OBJ" \
	"$(INTDIR)\VIEWDISP.OBJ" \
	"$(INTDIR)\ViewDropTarget.obj" \
	"$(INTDIR)\VIEWS.OBJ" \
	"$(INTDIR)\VIEWSDSP.OBJ" \
	"$(INTDIR)\VIEWTREE.OBJ" \
	"$(INTDIR)\DOC.OBJ" \
	"$(INTDIR)\DOCARRAY.OBJ" \
	"$(INTDIR)\DOCDISP.OBJ" \
	"$(INTDIR)\DocDragnDrop.obj" \
	"$(INTDIR)\DocLink.obj" \
	"$(INTDIR)\DOCS.OBJ" \
	"$(INTDIR)\DOCSDISP.OBJ" \
	"$(INTDIR)\DOCTREE.OBJ" \
	"$(INTDIR)\ENUMDOCS.OBJ" \
	"$(INTDIR)\APP.OBJ" \
	"$(INTDIR)\APPCF.OBJ" \
	"$(INTDIR)\APPDISP.OBJ" \
	"$(INTDIR)\APPNTFY.OBJ" \
	"$(INTDIR)\CLASS.OBJ" \
	"$(INTDIR)\CLASSES.OBJ" \
	"$(INTDIR)\CLIDTREE.OBJ" \
	"$(INTDIR)\CLNMTREE.OBJ" \
	"$(INTDIR)\CLSARRAY.OBJ" \
	"$(INTDIR)\CLSDISP.OBJ" \
	"$(INTDIR)\CLSSDISP.OBJ" \
	"$(INTDIR)\CLSTREES.OBJ" \
	"$(INTDIR)\ENUMCLSS.OBJ" \
	"$(INTDIR)\ENUMFTS.OBJ" \
	"$(INTDIR)\FEAT.OBJ" \
	"$(INTDIR)\FEATDISP.OBJ" \
	"$(INTDIR)\FTCLTREE.OBJ" \
	"$(INTDIR)\FTOBTREE.OBJ" \
	"$(INTDIR)\FTS.OBJ" \
	"$(INTDIR)\FTSARRAY.OBJ" \
	"$(INTDIR)\FTSDISP.OBJ" \
	"$(INTDIR)\FTVWTREE.OBJ" \
	"$(INTDIR)\EnumObWs.obj" \
	"$(INTDIR)\OBJWIN.OBJ" \
	"$(INTDIR)\ObjWins.obj" \
	"$(INTDIR)\ObWarray.obj" \
	"$(INTDIR)\ObWdisp.obj" \
	"$(INTDIR)\OWinTree.obj" \
	"$(INTDIR)\ARRAY.OBJ" \
	"$(INTDIR)\BILDOBJ.OBJ" \
	"$(INTDIR)\BScriptNotify.obj" \
	"$(INTDIR)\Connect.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\DLLDATAX.OBJ" \
	"$(INTDIR)\DragDrop.obj" \
	"$(INTDIR)\ObjectProperty.obj" \
	"$(INTDIR)\ObjectPropertyDual.obj" \
	"$(INTDIR)\OLE2AUTO.OBJ" \
	"$(INTDIR)\PICTURE.OBJ" \
	"$(INTDIR)\PRECOMP.OBJ" \
	"$(INTDIR)\Rgb_hsb.obj" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TRiASNotify.obj" \
	"$(INTDIR)\TRiASNotifyDual.obj" \
	"$(INTDIR)\WrapperExtension.obj" \
	"$(INTDIR)\Oleauto.res"

"$(OUTDIR)\oleautod.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\Debug
TargetPath=.\Debug\oleautod.ext
TargetName=oleautod
InputPath=.\Debug\oleautod.ext
SOURCE="$(InputPath)"

"..\..\..\TRiAS\TRiAS200\oleautod.ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\versio32.h" ".\olebsext.rc" ".\oleauto.rcv" ".\WIN32\Res\CopyObjr.ebc" ".\Release/Triastlb.tlb" ".\Documentation\OleAuto.hlp" "$(TRIASINCLUDE)\Triastlb_i.c" "$(TRIASINCLUDE)\Triastlb.h" "$(OUTDIR)\oleauto.ext" "$(TRIASDIR_R)\oleauto.ext"


CLEAN :
	-@erase "$(INTDIR)\APP.OBJ"
	-@erase "$(INTDIR)\APPCF.OBJ"
	-@erase "$(INTDIR)\APPDISP.OBJ"
	-@erase "$(INTDIR)\APPNTFY.OBJ"
	-@erase "$(INTDIR)\ARRAY.OBJ"
	-@erase "$(INTDIR)\BILDOBJ.OBJ"
	-@erase "$(INTDIR)\BScriptNotify.obj"
	-@erase "$(INTDIR)\CLASS.OBJ"
	-@erase "$(INTDIR)\CLASSES.OBJ"
	-@erase "$(INTDIR)\CLIDTREE.OBJ"
	-@erase "$(INTDIR)\CLNMTREE.OBJ"
	-@erase "$(INTDIR)\CLSARRAY.OBJ"
	-@erase "$(INTDIR)\CLSDISP.OBJ"
	-@erase "$(INTDIR)\CLSSDISP.OBJ"
	-@erase "$(INTDIR)\CLSTREES.OBJ"
	-@erase "$(INTDIR)\CONMTREE.OBJ"
	-@erase "$(INTDIR)\Connect.obj"
	-@erase "$(INTDIR)\CONRTREE.OBJ"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\DLLDATAX.OBJ"
	-@erase "$(INTDIR)\DOC.OBJ"
	-@erase "$(INTDIR)\DOCARRAY.OBJ"
	-@erase "$(INTDIR)\DOCDISP.OBJ"
	-@erase "$(INTDIR)\DocDragnDrop.obj"
	-@erase "$(INTDIR)\DocLink.obj"
	-@erase "$(INTDIR)\DOCS.OBJ"
	-@erase "$(INTDIR)\DOCSDISP.OBJ"
	-@erase "$(INTDIR)\DOCTREE.OBJ"
	-@erase "$(INTDIR)\DragDrop.obj"
	-@erase "$(INTDIR)\ENUMCLSS.OBJ"
	-@erase "$(INTDIR)\ENUMDOCS.OBJ"
	-@erase "$(INTDIR)\ENUMFTS.OBJ"
	-@erase "$(INTDIR)\ENUMOBJS.OBJ"
	-@erase "$(INTDIR)\EnumObWs.obj"
	-@erase "$(INTDIR)\ENUVIEWS.OBJ"
	-@erase "$(INTDIR)\FEAT.OBJ"
	-@erase "$(INTDIR)\FEATDISP.OBJ"
	-@erase "$(INTDIR)\FTCLTREE.OBJ"
	-@erase "$(INTDIR)\FTOBTREE.OBJ"
	-@erase "$(INTDIR)\FTS.OBJ"
	-@erase "$(INTDIR)\FTSARRAY.OBJ"
	-@erase "$(INTDIR)\FTSDISP.OBJ"
	-@erase "$(INTDIR)\FTVWTREE.OBJ"
	-@erase "$(INTDIR)\GEOMETRY.OBJ"
	-@erase "$(INTDIR)\jumptab.obj"
	-@erase "$(INTDIR)\OBJ.OBJ"
	-@erase "$(INTDIR)\OBJARRAY.OBJ"
	-@erase "$(INTDIR)\OBJDISP.OBJ"
	-@erase "$(INTDIR)\ObjectProperty.obj"
	-@erase "$(INTDIR)\ObjectPropertyDual.obj"
	-@erase "$(INTDIR)\OBJS.OBJ"
	-@erase "$(INTDIR)\Objsdisp.obj"
	-@erase "$(INTDIR)\OBJTREES.OBJ"
	-@erase "$(INTDIR)\OBJWIN.OBJ"
	-@erase "$(INTDIR)\ObjWins.obj"
	-@erase "$(INTDIR)\ObWarray.obj"
	-@erase "$(INTDIR)\ObWdisp.obj"
	-@erase "$(INTDIR)\OLE2AUTO.OBJ"
	-@erase "$(INTDIR)\Oleauto.res"
	-@erase "$(INTDIR)\Oleauto4.pch"
	-@erase "$(INTDIR)\OLEBSEXT.OBJ"
	-@erase "$(INTDIR)\OWinTree.obj"
	-@erase "$(INTDIR)\PICTURE.OBJ"
	-@erase "$(INTDIR)\PictureExt.obj"
	-@erase "$(INTDIR)\PRECOMP.OBJ"
	-@erase "$(INTDIR)\PropActSeq.obj"
	-@erase "$(INTDIR)\PropNamex.obj"
	-@erase "$(INTDIR)\Rgb_hsb.obj"
	-@erase "$(INTDIR)\StatusIndExt.obj"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\ToolBarExt.obj"
	-@erase "$(INTDIR)\TRiASNotify.obj"
	-@erase "$(INTDIR)\TRiASNotifyDual.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VIEW.OBJ"
	-@erase "$(INTDIR)\VIEWARRY.OBJ"
	-@erase "$(INTDIR)\VIEWDISP.OBJ"
	-@erase "$(INTDIR)\ViewDropTarget.obj"
	-@erase "$(INTDIR)\VIEWS.OBJ"
	-@erase "$(INTDIR)\VIEWSDSP.OBJ"
	-@erase "$(INTDIR)\VIEWTREE.OBJ"
	-@erase "$(INTDIR)\VisInfoExt.obj"
	-@erase "$(INTDIR)\WrapperExtension.obj"
	-@erase "$(OUTDIR)\oleauto.exp"
	-@erase "$(OUTDIR)\oleauto.ext"
	-@erase "$(OUTDIR)\oleauto.lib"
	-@erase "$(OUTDIR)\oleauto.pdb"
	-@erase "$(TRIASDIR_R)\oleauto.ext"
	-@erase "$(TRIASINCLUDE)\Triastlb.h"
	-@erase "$(TRIASINCLUDE)\Triastlb_i.c"
	-@erase ".\Documentation\OleAuto.hlp"
	-@erase ".\Release/Triastlb.tlb"
	-@erase ".\WIN32\Res\CopyObjr.ebc"
	-@erase "oleauto.rcv"
	-@erase "olebsext.rc"
	-@erase "versio32.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Oleauto4.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Oleauto.res" /d "NDEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oleauto4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ixtmar50.lib containr.lib ospace5r.lib ebn.lib Triastlb.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\oleauto.pdb" /debug /machine:I386 /def:".\oleauto.def" /out:"$(OUTDIR)\oleauto.ext" /implib:"$(OUTDIR)\oleauto.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\oleauto.def"
LINK32_OBJS= \
	"$(INTDIR)\jumptab.obj" \
	"$(INTDIR)\OLEBSEXT.OBJ" \
	"$(INTDIR)\PictureExt.obj" \
	"$(INTDIR)\PropActSeq.obj" \
	"$(INTDIR)\PropNamex.obj" \
	"$(INTDIR)\StatusIndExt.obj" \
	"$(INTDIR)\ToolBarExt.obj" \
	"$(INTDIR)\VisInfoExt.obj" \
	"$(INTDIR)\CONMTREE.OBJ" \
	"$(INTDIR)\CONRTREE.OBJ" \
	"$(INTDIR)\ENUMOBJS.OBJ" \
	"$(INTDIR)\GEOMETRY.OBJ" \
	"$(INTDIR)\OBJ.OBJ" \
	"$(INTDIR)\OBJARRAY.OBJ" \
	"$(INTDIR)\OBJDISP.OBJ" \
	"$(INTDIR)\OBJS.OBJ" \
	"$(INTDIR)\Objsdisp.obj" \
	"$(INTDIR)\OBJTREES.OBJ" \
	"$(INTDIR)\ENUVIEWS.OBJ" \
	"$(INTDIR)\VIEW.OBJ" \
	"$(INTDIR)\VIEWARRY.OBJ" \
	"$(INTDIR)\VIEWDISP.OBJ" \
	"$(INTDIR)\ViewDropTarget.obj" \
	"$(INTDIR)\VIEWS.OBJ" \
	"$(INTDIR)\VIEWSDSP.OBJ" \
	"$(INTDIR)\VIEWTREE.OBJ" \
	"$(INTDIR)\DOC.OBJ" \
	"$(INTDIR)\DOCARRAY.OBJ" \
	"$(INTDIR)\DOCDISP.OBJ" \
	"$(INTDIR)\DocDragnDrop.obj" \
	"$(INTDIR)\DocLink.obj" \
	"$(INTDIR)\DOCS.OBJ" \
	"$(INTDIR)\DOCSDISP.OBJ" \
	"$(INTDIR)\DOCTREE.OBJ" \
	"$(INTDIR)\ENUMDOCS.OBJ" \
	"$(INTDIR)\APP.OBJ" \
	"$(INTDIR)\APPCF.OBJ" \
	"$(INTDIR)\APPDISP.OBJ" \
	"$(INTDIR)\APPNTFY.OBJ" \
	"$(INTDIR)\CLASS.OBJ" \
	"$(INTDIR)\CLASSES.OBJ" \
	"$(INTDIR)\CLIDTREE.OBJ" \
	"$(INTDIR)\CLNMTREE.OBJ" \
	"$(INTDIR)\CLSARRAY.OBJ" \
	"$(INTDIR)\CLSDISP.OBJ" \
	"$(INTDIR)\CLSSDISP.OBJ" \
	"$(INTDIR)\CLSTREES.OBJ" \
	"$(INTDIR)\ENUMCLSS.OBJ" \
	"$(INTDIR)\ENUMFTS.OBJ" \
	"$(INTDIR)\FEAT.OBJ" \
	"$(INTDIR)\FEATDISP.OBJ" \
	"$(INTDIR)\FTCLTREE.OBJ" \
	"$(INTDIR)\FTOBTREE.OBJ" \
	"$(INTDIR)\FTS.OBJ" \
	"$(INTDIR)\FTSARRAY.OBJ" \
	"$(INTDIR)\FTSDISP.OBJ" \
	"$(INTDIR)\FTVWTREE.OBJ" \
	"$(INTDIR)\EnumObWs.obj" \
	"$(INTDIR)\OBJWIN.OBJ" \
	"$(INTDIR)\ObjWins.obj" \
	"$(INTDIR)\ObWarray.obj" \
	"$(INTDIR)\ObWdisp.obj" \
	"$(INTDIR)\OWinTree.obj" \
	"$(INTDIR)\ARRAY.OBJ" \
	"$(INTDIR)\BILDOBJ.OBJ" \
	"$(INTDIR)\BScriptNotify.obj" \
	"$(INTDIR)\Connect.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\DLLDATAX.OBJ" \
	"$(INTDIR)\DragDrop.obj" \
	"$(INTDIR)\ObjectProperty.obj" \
	"$(INTDIR)\ObjectPropertyDual.obj" \
	"$(INTDIR)\OLE2AUTO.OBJ" \
	"$(INTDIR)\PICTURE.OBJ" \
	"$(INTDIR)\PRECOMP.OBJ" \
	"$(INTDIR)\Rgb_hsb.obj" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TRiASNotify.obj" \
	"$(INTDIR)\TRiASNotifyDual.obj" \
	"$(INTDIR)\WrapperExtension.obj" \
	"$(INTDIR)\Oleauto.res"

"$(OUTDIR)\oleauto.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\Release
TargetPath=.\Release\oleauto.ext
TargetName=oleauto
InputPath=.\Release\oleauto.ext
SOURCE="$(InputPath)"

"..\..\..\TRiAS\TRiAS300\oleauto.ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

OUTDIR=.\Oleauto___Win32_Debug_TrueTime
INTDIR=.\Oleauto___Win32_Debug_TrueTime
# Begin Custom Macros
OutDir=.\Oleauto___Win32_Debug_TrueTime
# End Custom Macros

ALL : ".\versio32.h" ".\olebsext.rc" ".\oleauto.rcv" ".\WIN32\Res\CopyObjd.ebc" ".\Oleauto___Win32_Debug_TrueTime/Triastlb.tlb" "$(TRIASINCLUDE)\Triastlb_i.c" "$(TRIASINCLUDE)\Triastlb.h" "$(OUTDIR)\oleautod.ext" "$(TRIASDIR_D)\oleautod.ext"


CLEAN :
	-@erase "$(INTDIR)\APP.OBJ"
	-@erase "$(INTDIR)\APPCF.OBJ"
	-@erase "$(INTDIR)\APPDISP.OBJ"
	-@erase "$(INTDIR)\APPNTFY.OBJ"
	-@erase "$(INTDIR)\ARRAY.OBJ"
	-@erase "$(INTDIR)\BILDOBJ.OBJ"
	-@erase "$(INTDIR)\BScriptNotify.obj"
	-@erase "$(INTDIR)\CLASS.OBJ"
	-@erase "$(INTDIR)\CLASSES.OBJ"
	-@erase "$(INTDIR)\CLIDTREE.OBJ"
	-@erase "$(INTDIR)\CLNMTREE.OBJ"
	-@erase "$(INTDIR)\CLSARRAY.OBJ"
	-@erase "$(INTDIR)\CLSDISP.OBJ"
	-@erase "$(INTDIR)\CLSSDISP.OBJ"
	-@erase "$(INTDIR)\CLSTREES.OBJ"
	-@erase "$(INTDIR)\CONMTREE.OBJ"
	-@erase "$(INTDIR)\Connect.obj"
	-@erase "$(INTDIR)\CONRTREE.OBJ"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\DLLDATAX.OBJ"
	-@erase "$(INTDIR)\DOC.OBJ"
	-@erase "$(INTDIR)\DOCARRAY.OBJ"
	-@erase "$(INTDIR)\DOCDISP.OBJ"
	-@erase "$(INTDIR)\DocDragnDrop.obj"
	-@erase "$(INTDIR)\DocLink.obj"
	-@erase "$(INTDIR)\DOCS.OBJ"
	-@erase "$(INTDIR)\DOCSDISP.OBJ"
	-@erase "$(INTDIR)\DOCTREE.OBJ"
	-@erase "$(INTDIR)\DragDrop.obj"
	-@erase "$(INTDIR)\ENUMCLSS.OBJ"
	-@erase "$(INTDIR)\ENUMDOCS.OBJ"
	-@erase "$(INTDIR)\ENUMFTS.OBJ"
	-@erase "$(INTDIR)\ENUMOBJS.OBJ"
	-@erase "$(INTDIR)\EnumObWs.obj"
	-@erase "$(INTDIR)\ENUVIEWS.OBJ"
	-@erase "$(INTDIR)\FEAT.OBJ"
	-@erase "$(INTDIR)\FEATDISP.OBJ"
	-@erase "$(INTDIR)\FTCLTREE.OBJ"
	-@erase "$(INTDIR)\FTOBTREE.OBJ"
	-@erase "$(INTDIR)\FTS.OBJ"
	-@erase "$(INTDIR)\FTSARRAY.OBJ"
	-@erase "$(INTDIR)\FTSDISP.OBJ"
	-@erase "$(INTDIR)\FTVWTREE.OBJ"
	-@erase "$(INTDIR)\GEOMETRY.OBJ"
	-@erase "$(INTDIR)\jumptab.obj"
	-@erase "$(INTDIR)\OBJ.OBJ"
	-@erase "$(INTDIR)\OBJARRAY.OBJ"
	-@erase "$(INTDIR)\OBJDISP.OBJ"
	-@erase "$(INTDIR)\ObjectProperty.obj"
	-@erase "$(INTDIR)\ObjectPropertyDual.obj"
	-@erase "$(INTDIR)\OBJS.OBJ"
	-@erase "$(INTDIR)\Objsdisp.obj"
	-@erase "$(INTDIR)\OBJTREES.OBJ"
	-@erase "$(INTDIR)\OBJWIN.OBJ"
	-@erase "$(INTDIR)\ObjWins.obj"
	-@erase "$(INTDIR)\ObWarray.obj"
	-@erase "$(INTDIR)\ObWdisp.obj"
	-@erase "$(INTDIR)\OLE2AUTO.OBJ"
	-@erase "$(INTDIR)\Oleauto.res"
	-@erase "$(INTDIR)\OLEAUTOD.idb"
	-@erase "$(INTDIR)\OLEAUTOD.pch"
	-@erase "$(INTDIR)\OLEBSEXT.OBJ"
	-@erase "$(INTDIR)\OWinTree.obj"
	-@erase "$(INTDIR)\PICTURE.OBJ"
	-@erase "$(INTDIR)\PictureExt.obj"
	-@erase "$(INTDIR)\PRECOMP.OBJ"
	-@erase "$(INTDIR)\PropActSeq.obj"
	-@erase "$(INTDIR)\PropNamex.obj"
	-@erase "$(INTDIR)\Rgb_hsb.obj"
	-@erase "$(INTDIR)\StatusIndExt.obj"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\ToolBarExt.obj"
	-@erase "$(INTDIR)\TRiASNotify.obj"
	-@erase "$(INTDIR)\TRiASNotifyDual.obj"
	-@erase "$(INTDIR)\VIEW.OBJ"
	-@erase "$(INTDIR)\VIEWARRY.OBJ"
	-@erase "$(INTDIR)\VIEWDISP.OBJ"
	-@erase "$(INTDIR)\ViewDropTarget.obj"
	-@erase "$(INTDIR)\VIEWS.OBJ"
	-@erase "$(INTDIR)\VIEWSDSP.OBJ"
	-@erase "$(INTDIR)\VIEWTREE.OBJ"
	-@erase "$(INTDIR)\VisInfoExt.obj"
	-@erase "$(INTDIR)\WrapperExtension.obj"
	-@erase "$(OUTDIR)\oleautod.exp"
	-@erase "$(OUTDIR)\oleautod.ext"
	-@erase "$(OUTDIR)\oleautod.ilk"
	-@erase "$(OUTDIR)\oleautod.lib"
	-@erase "$(OUTDIR)\OLEAUTOD.pdb"
	-@erase "$(TRIASDIR_D)\oleautod.ext"
	-@erase "$(TRIASINCLUDE)\Triastlb.h"
	-@erase "$(TRIASINCLUDE)\Triastlb_i.c"
	-@erase ".\Oleauto___Win32_Debug_TrueTime/Triastlb.tlb"
	-@erase ".\WIN32\Res\CopyObjd.ebc"
	-@erase "oleauto.rcv"
	-@erase "olebsext.rc"
	-@erase "versio32.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\Oleauto.res" /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oleauto4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ixtmad50.lib cont50d.lib ospace5d.lib ebn.lib Triastld.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\oleautod.pdb" /debug /machine:I386 /def:".\oleauto.def" /out:"$(OUTDIR)\oleautod.ext" /implib:"$(OUTDIR)\oleautod.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\oleauto.def"
LINK32_OBJS= \
	"$(INTDIR)\jumptab.obj" \
	"$(INTDIR)\OLEBSEXT.OBJ" \
	"$(INTDIR)\PictureExt.obj" \
	"$(INTDIR)\PropActSeq.obj" \
	"$(INTDIR)\PropNamex.obj" \
	"$(INTDIR)\StatusIndExt.obj" \
	"$(INTDIR)\ToolBarExt.obj" \
	"$(INTDIR)\VisInfoExt.obj" \
	"$(INTDIR)\CONMTREE.OBJ" \
	"$(INTDIR)\CONRTREE.OBJ" \
	"$(INTDIR)\ENUMOBJS.OBJ" \
	"$(INTDIR)\GEOMETRY.OBJ" \
	"$(INTDIR)\OBJ.OBJ" \
	"$(INTDIR)\OBJARRAY.OBJ" \
	"$(INTDIR)\OBJDISP.OBJ" \
	"$(INTDIR)\OBJS.OBJ" \
	"$(INTDIR)\Objsdisp.obj" \
	"$(INTDIR)\OBJTREES.OBJ" \
	"$(INTDIR)\ENUVIEWS.OBJ" \
	"$(INTDIR)\VIEW.OBJ" \
	"$(INTDIR)\VIEWARRY.OBJ" \
	"$(INTDIR)\VIEWDISP.OBJ" \
	"$(INTDIR)\ViewDropTarget.obj" \
	"$(INTDIR)\VIEWS.OBJ" \
	"$(INTDIR)\VIEWSDSP.OBJ" \
	"$(INTDIR)\VIEWTREE.OBJ" \
	"$(INTDIR)\DOC.OBJ" \
	"$(INTDIR)\DOCARRAY.OBJ" \
	"$(INTDIR)\DOCDISP.OBJ" \
	"$(INTDIR)\DocDragnDrop.obj" \
	"$(INTDIR)\DocLink.obj" \
	"$(INTDIR)\DOCS.OBJ" \
	"$(INTDIR)\DOCSDISP.OBJ" \
	"$(INTDIR)\DOCTREE.OBJ" \
	"$(INTDIR)\ENUMDOCS.OBJ" \
	"$(INTDIR)\APP.OBJ" \
	"$(INTDIR)\APPCF.OBJ" \
	"$(INTDIR)\APPDISP.OBJ" \
	"$(INTDIR)\APPNTFY.OBJ" \
	"$(INTDIR)\CLASS.OBJ" \
	"$(INTDIR)\CLASSES.OBJ" \
	"$(INTDIR)\CLIDTREE.OBJ" \
	"$(INTDIR)\CLNMTREE.OBJ" \
	"$(INTDIR)\CLSARRAY.OBJ" \
	"$(INTDIR)\CLSDISP.OBJ" \
	"$(INTDIR)\CLSSDISP.OBJ" \
	"$(INTDIR)\CLSTREES.OBJ" \
	"$(INTDIR)\ENUMCLSS.OBJ" \
	"$(INTDIR)\ENUMFTS.OBJ" \
	"$(INTDIR)\FEAT.OBJ" \
	"$(INTDIR)\FEATDISP.OBJ" \
	"$(INTDIR)\FTCLTREE.OBJ" \
	"$(INTDIR)\FTOBTREE.OBJ" \
	"$(INTDIR)\FTS.OBJ" \
	"$(INTDIR)\FTSARRAY.OBJ" \
	"$(INTDIR)\FTSDISP.OBJ" \
	"$(INTDIR)\FTVWTREE.OBJ" \
	"$(INTDIR)\EnumObWs.obj" \
	"$(INTDIR)\OBJWIN.OBJ" \
	"$(INTDIR)\ObjWins.obj" \
	"$(INTDIR)\ObWarray.obj" \
	"$(INTDIR)\ObWdisp.obj" \
	"$(INTDIR)\OWinTree.obj" \
	"$(INTDIR)\ARRAY.OBJ" \
	"$(INTDIR)\BILDOBJ.OBJ" \
	"$(INTDIR)\BScriptNotify.obj" \
	"$(INTDIR)\Connect.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\DLLDATAX.OBJ" \
	"$(INTDIR)\DragDrop.obj" \
	"$(INTDIR)\ObjectProperty.obj" \
	"$(INTDIR)\ObjectPropertyDual.obj" \
	"$(INTDIR)\OLE2AUTO.OBJ" \
	"$(INTDIR)\PICTURE.OBJ" \
	"$(INTDIR)\PRECOMP.OBJ" \
	"$(INTDIR)\Rgb_hsb.obj" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\TRiASNotify.obj" \
	"$(INTDIR)\TRiASNotifyDual.obj" \
	"$(INTDIR)\WrapperExtension.obj" \
	"$(INTDIR)\Oleauto.res"

"$(OUTDIR)\oleautod.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetDir=.\Oleauto___Win32_Debug_TrueTime
TargetPath=.\Oleauto___Win32_Debug_TrueTime\oleautod.ext
TargetName=oleautod
InputPath=.\Oleauto___Win32_Debug_TrueTime\oleautod.ext
SOURCE="$(InputPath)"

"..\..\..\TRiAS\TRiAS200\oleautod.ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Oleauto4.dep")
!INCLUDE "Oleauto4.dep"
!ELSE 
!MESSAGE Warning: cannot find "Oleauto4.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Oleauto - Win32 Debug with BasicScript" || "$(CFG)" == "Oleauto - Win32 Release with BasicScript" || "$(CFG)" == "Oleauto - Win32 Debug TrueTime"
SOURCE=.\jumptab.cpp

"$(INTDIR)\jumptab.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OLEBSEXT.CXX

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\OLEBSEXT.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

CPP_SWITCHES=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Oleauto4.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\OLEBSEXT.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oleauto4.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\OLEBSEXT.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PictureExt.cpp

"$(INTDIR)\PictureExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\PropActSeq.cpp

"$(INTDIR)\PropActSeq.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\PropNamex.cpp

"$(INTDIR)\PropNamex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\StatusIndExt.cpp

"$(INTDIR)\StatusIndExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ToolBarExt.cpp

"$(INTDIR)\ToolBarExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VisInfoExt.cpp

"$(INTDIR)\VisInfoExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CONMTREE.CXX

"$(INTDIR)\CONMTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CONRTREE.CXX

"$(INTDIR)\CONRTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ENUMOBJS.CXX

"$(INTDIR)\ENUMOBJS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\GEOMETRY.CXX

"$(INTDIR)\GEOMETRY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJ.CXX

"$(INTDIR)\OBJ.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJARRAY.CXX

"$(INTDIR)\OBJARRAY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJDISP.CXX

"$(INTDIR)\OBJDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJS.CXX

"$(INTDIR)\OBJS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\Objsdisp.cxx

"$(INTDIR)\Objsdisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJTREES.CXX

"$(INTDIR)\OBJTREES.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ENUVIEWS.CXX

"$(INTDIR)\ENUVIEWS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEW.CXX

"$(INTDIR)\VIEW.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEWARRY.CXX

"$(INTDIR)\VIEWARRY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEWDISP.CXX

"$(INTDIR)\VIEWDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ViewDropTarget.cpp

"$(INTDIR)\ViewDropTarget.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEWS.CXX

"$(INTDIR)\VIEWS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEWSDSP.CXX

"$(INTDIR)\VIEWSDSP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\VIEWTREE.CXX

"$(INTDIR)\VIEWTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOC.CXX

"$(INTDIR)\DOC.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOCARRAY.CXX

"$(INTDIR)\DOCARRAY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOCDISP.CXX

"$(INTDIR)\DOCDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DocDragnDrop.cpp

"$(INTDIR)\DocDragnDrop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DocLink.cpp

"$(INTDIR)\DocLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOCS.CXX

"$(INTDIR)\DOCS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOCSDISP.CXX

"$(INTDIR)\DOCSDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DOCTREE.CXX

"$(INTDIR)\DOCTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ENUMDOCS.CXX

"$(INTDIR)\ENUMDOCS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\APP.CXX

"$(INTDIR)\APP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\APPCF.CXX

"$(INTDIR)\APPCF.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\APPDISP.CXX

"$(INTDIR)\APPDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\APPNTFY.CXX

"$(INTDIR)\APPNTFY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLASS.CXX

"$(INTDIR)\CLASS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLASSES.CXX

"$(INTDIR)\CLASSES.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLIDTREE.CXX

"$(INTDIR)\CLIDTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLNMTREE.CXX

"$(INTDIR)\CLNMTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLSARRAY.CXX

"$(INTDIR)\CLSARRAY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLSDISP.CXX

"$(INTDIR)\CLSDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLSSDISP.CXX

"$(INTDIR)\CLSSDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\CLSTREES.CXX

"$(INTDIR)\CLSTREES.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ENUMCLSS.CXX

"$(INTDIR)\ENUMCLSS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ENUMFTS.CXX

"$(INTDIR)\ENUMFTS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FEAT.CXX

"$(INTDIR)\FEAT.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FEATDISP.CXX

"$(INTDIR)\FEATDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTCLTREE.CXX

"$(INTDIR)\FTCLTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTOBTREE.CXX

"$(INTDIR)\FTOBTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTS.CXX

"$(INTDIR)\FTS.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTSARRAY.CXX

"$(INTDIR)\FTSARRAY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTSDISP.CXX

"$(INTDIR)\FTSDISP.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\FTVWTREE.CXX

"$(INTDIR)\FTVWTREE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\EnumObWs.cxx

"$(INTDIR)\EnumObWs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OBJWIN.CXX

"$(INTDIR)\OBJWIN.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ObjWins.cxx

"$(INTDIR)\ObjWins.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ObWarray.cxx

"$(INTDIR)\ObWarray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ObWdisp.cxx

"$(INTDIR)\ObWdisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OWinTree.cxx

"$(INTDIR)\OWinTree.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ARRAY.CXX

"$(INTDIR)\ARRAY.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\BILDOBJ.CPP

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\BILDOBJ.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

CPP_SWITCHES=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Oleauto4.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\BILDOBJ.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oleauto4.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\BILDOBJ.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\BScriptNotify.cpp

"$(INTDIR)\BScriptNotify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\Connect.cxx

"$(INTDIR)\Connect.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\Datahelp.cxx

"$(INTDIR)\Datahelp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\DLLDATAX.C

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\DLLDATAX.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

CPP_SWITCHES=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DLLDATAX.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\DLLDATAX.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DragDrop.cpp

"$(INTDIR)\DragDrop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ObjectProperty.cpp

"$(INTDIR)\ObjectProperty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\ObjectPropertyDual.cpp

"$(INTDIR)\ObjectPropertyDual.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\OLE2AUTO.CXX

"$(INTDIR)\OLE2AUTO.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch" ".\versio32.h"


SOURCE=.\Win32\Oleauto.RC

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"


"$(INTDIR)\Oleauto.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TRIASTLB.tlb" ".\WIN32\Res\CopyObjd.ebc" ".\olebsext.rc"
	$(RSC) /l 0x407 /fo"$(INTDIR)\Oleauto.res" /i "Win32" /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" $(SOURCE)


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"


"$(INTDIR)\Oleauto.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x407 /fo"$(INTDIR)\Oleauto.res" /i "Win32" /d "NDEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" $(SOURCE)


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"


"$(INTDIR)\Oleauto.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x407 /fo"$(INTDIR)\Oleauto.res" /i "Win32" /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO" $(SOURCE)


!ENDIF 

SOURCE=.\PICTURE.CPP

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\PICTURE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

CPP_SWITCHES=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Oleauto4.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\PICTURE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oleauto4.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\PICTURE.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PRECOMP.CXX

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yc"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\PRECOMP.OBJ"	"$(INTDIR)\OLEAUTOD.pch" : $(SOURCE) "$(INTDIR)" "..\..\Include\Triastlb.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

CPP_SWITCHES=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Oleauto4.pch" /Yc"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\PRECOMP.OBJ"	"$(INTDIR)\Oleauto4.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

CPP_SWITCHES=/nologo /MDd /W3 /WX /Gm /Gi- /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\OLEAUTOD.pch" /Yc"precomp.hxx" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\OLEAUTOD.pdb" /FD /c 

"$(INTDIR)\PRECOMP.OBJ"	"$(INTDIR)\OLEAUTOD.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Rgb_hsb.cxx

"$(INTDIR)\Rgb_hsb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\Strings.cpp

"$(INTDIR)\Strings.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\TRiASNotify.cpp

"$(INTDIR)\TRiASNotify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\TRiASNotifyDual.cpp

"$(INTDIR)\TRiASNotifyDual.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\WIN32\Triastlb.idl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

OutDir=.\Debug
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

"$(INTDIR)\TRIASTLB.tlb"	"..\..\Include\Triastlb_i.c"	"..\..\Include\Triastlb.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

OutDir=.\Release
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

"$(INTDIR)\Triastlb.tlb"	"..\..\Include\Triastlb_i.c"	"..\..\Include\Triastlb.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

OutDir=.\Oleauto___Win32_Debug_TrueTime
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

"$(INTDIR)\Triastlb.tlb"	"..\..\Include\Triastlb_i.c"	"..\..\Include\Triastlb.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\WrapperExtension.cpp

"$(INTDIR)\WrapperExtension.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OLEAUTOD.pch"


SOURCE=.\Win32\OLEBSEXT.RC
SOURCE=.\Documentation\CONTENTS.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Documentation\CONTENTS.TPL
USERDEP__CONTE="oleaut16.mak"	

".\Documentation\contents.hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__CONTE)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak .\Documentation\contents.hpj
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

SOURCE=.\Documentation\OleAutoFmt.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Documentation\OleAutoFmt.tpl
USERDEP__OLEAU="oleaut16.mak"	

".\Documentation\OleAuto.fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAU)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak .\Documentation\OleAuto.fmt
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

SOURCE=.\Documentation\OleAutotpl.cnt

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Documentation\OleAutotpl.cnt
USERDEP__OLEAUT="oleaut16.mak"	

".\Documentation\OleAuto.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUT)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak .\Documentation\OleAuto.cnt
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

SOURCE=.\Olbsextp.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Olbsextp.tpl
USERDEP__OLBSE="oleaut16.mak"	

".\olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLBSE)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak olebsext.rc
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputPath=.\Olbsextp.tpl
USERDEP__OLBSE="oleaut16.mak"	

".\olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLBSE)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak olebsext.rc
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

InputPath=.\Olbsextp.tpl
USERDEP__OLBSE="oleaut16.mak"	

".\olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLBSE)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak olebsext.rc
<< 
	

!ENDIF 

SOURCE=.\OLEAUTO.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\OLEAUTO.TPL
USERDEP__OLEAUTO="oleaut16.mak"	

".\oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTO)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.def
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputPath=.\OLEAUTO.TPL
USERDEP__OLEAUTO="oleaut16.mak"	

".\oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTO)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.def
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

InputPath=.\OLEAUTO.TPL
USERDEP__OLEAUTO="oleaut16.mak"	

".\oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTO)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.def
<< 
	

!ENDIF 

SOURCE=.\Oleautov.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Oleautov.tpl
USERDEP__OLEAUTOV="oleaut16.mak"	

".\oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTOV)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.rcv
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputPath=.\Oleautov.tpl
USERDEP__OLEAUTOV="oleaut16.mak"	

".\oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTOV)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.rcv
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

InputPath=.\Oleautov.tpl
USERDEP__OLEAUTOV="oleaut16.mak"	

".\oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__OLEAUTOV)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak oleauto.rcv
<< 
	

!ENDIF 

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\VERSIO32.TPL
USERDEP__VERSI="oleaut16.mak"	

".\versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__VERSI)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak versio32.h
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputPath=.\VERSIO32.TPL
USERDEP__VERSI="oleaut16.mak"	

".\versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__VERSI)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak versio32.h
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

InputPath=.\VERSIO32.TPL
USERDEP__VERSI="oleaut16.mak"	

".\versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__VERSI)
	<<tempfile.bat 
	@echo off 
	nmake -nologo -f oleaut16.mak versio32.h
<< 
	

!ENDIF 

SOURCE=.\WIN32\Res\CopyObj.Ebs

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

".\WIN32\Res\CopyObjd.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

".\Win32\Res\CopyObjr.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	bsl -c -n -o $(InputDir)\$(InputName)r.ebc -DNDEBUG $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

".\WIN32\Res\CopyObjd.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\Documentation\Contents.d

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

InputPath=.\Documentation\Contents.d
USERDEP__CONTEN="oleaut16.mak"	

".\Documentation\OLEAUTO.HLP" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__CONTEN)
	<<tempfile.bat 
	@echo off 
	nmake -f oleaut16.mak -nologo DEBUG=1 .\Documentation\OleAuto.hlp
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

InputPath=.\Documentation\Contents.d

".\Documentation\OLEAUTO.HLP" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	nmake -f oleaut16.mak -nologo NDEBUG=1 .\Documentation\OleAuto.hlp
<< 
	

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 


!ENDIF 

