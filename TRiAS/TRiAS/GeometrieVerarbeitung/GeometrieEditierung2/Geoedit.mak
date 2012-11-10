# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Geoedit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Geoedit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Geoedit - Win32 Release" && "$(CFG)" !=\
 "Geoedit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Geoedit.mak" CFG="Geoedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Geoedit - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Geoedit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Geoedit - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Geoedit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
TargetName=GeoEdit
# End Custom Macros

ALL : "$(OUTDIR)\GeoEdit.ext" "..\..\TRIAS\TRIAS32R\GeoEdit.ext" ".\IGeoEdit.c"

CLEAN : 
	-@erase "$(INTDIR)\AreaPartition.obj"
	-@erase "$(INTDIR)\BmpBtn.obj"
	-@erase "$(INTDIR)\CrossObject.obj"
	-@erase "$(INTDIR)\DesignDlg.obj"
	-@erase "$(INTDIR)\Designing.obj"
	-@erase "$(INTDIR)\DragMultiLine.obj"
	-@erase "$(INTDIR)\EditBaseDlg.obj"
	-@erase "$(INTDIR)\EditCoordDlg.obj"
	-@erase "$(INTDIR)\EditDlg.obj"
	-@erase "$(INTDIR)\EnumObjektGeometrie.obj"
	-@erase "$(INTDIR)\FixPointsDlg.obj"
	-@erase "$(INTDIR)\GeoEdit.obj"
	-@erase "$(INTDIR)\Geoedit.pch"
	-@erase "$(INTDIR)\GeoEdit.res"
	-@erase "$(INTDIR)\GeoEditInterface.obj"
	-@erase "$(INTDIR)\GeoEditLib.obj"
	-@erase "$(INTDIR)\GeoEditOutside.obj"
	-@erase "$(INTDIR)\GeoEditP.obj"
	-@erase "$(INTDIR)\IntersectLineDlg.obj"
	-@erase "$(INTDIR)\IslandAdd.obj"
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\Kreis.obj"
	-@erase "$(INTDIR)\LineElongation.obj"
	-@erase "$(INTDIR)\MakeRectangular.obj"
	-@erase "$(INTDIR)\Marker.obj"
	-@erase "$(INTDIR)\NewArea.obj"
	-@erase "$(INTDIR)\NewLine.obj"
	-@erase "$(INTDIR)\NewPoint.obj"
	-@erase "$(INTDIR)\ObjectModify.obj"
	-@erase "$(INTDIR)\ObjectModifyFunc.obj"
	-@erase "$(INTDIR)\ObjectMove.obj"
	-@erase "$(INTDIR)\PropExt.obj"
	-@erase "$(INTDIR)\RestrictCursor.obj"
	-@erase "$(INTDIR)\RestrictLine.obj"
	-@erase "$(INTDIR)\SingleDesignDlg.obj"
	-@erase "$(INTDIR)\ToolBars.obj"
	-@erase "$(INTDIR)\TopicalObjects.obj"
	-@erase "$(INTDIR)\UIOwnerFunc.obj"
	-@erase "$(INTDIR)\VertexAdd.obj"
	-@erase "$(INTDIR)\VertexModDlg.obj"
	-@erase "$(INTDIR)\VertexMove.obj"
	-@erase "$(OUTDIR)\GeoEdit.exp"
	-@erase "$(OUTDIR)\GeoEdit.ext"
	-@erase "$(OUTDIR)\GeoEdit.lib"
	-@erase "..\..\TRIAS\TRIAS32R\GeoEdit.ext"
	-@erase ".\IGeoEdit.c"
	-@erase ".\IGeoEdit.h"
	-@erase ".\IGeoEdit.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/GEOEDIT.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2" /Yu"GeoEditP.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2"\
 /Fp"$(INTDIR)/Geoedit.pch" /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/GeoEdit.res" /i "..\Z_HXX" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Geoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtAtr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib ospace2r.lib ebn.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"WinRel/GeoEdit.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=geometr.lib ixtAtr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastlb.lib ospace2r.lib ebn.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/GeoEdit.pdb" /machine:I386 /nodefaultlib:"libcmtd.lib"\
 /def:".\GeoEdit.def" /out:"$(OUTDIR)/GeoEdit.ext"\
 /implib:"$(OUTDIR)/GeoEdit.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\GeoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\AreaPartition.obj" \
	"$(INTDIR)\BmpBtn.obj" \
	"$(INTDIR)\CrossObject.obj" \
	"$(INTDIR)\DesignDlg.obj" \
	"$(INTDIR)\Designing.obj" \
	"$(INTDIR)\DragMultiLine.obj" \
	"$(INTDIR)\EditBaseDlg.obj" \
	"$(INTDIR)\EditCoordDlg.obj" \
	"$(INTDIR)\EditDlg.obj" \
	"$(INTDIR)\EnumObjektGeometrie.obj" \
	"$(INTDIR)\FixPointsDlg.obj" \
	"$(INTDIR)\GeoEdit.obj" \
	"$(INTDIR)\GeoEdit.res" \
	"$(INTDIR)\GeoEditInterface.obj" \
	"$(INTDIR)\GeoEditLib.obj" \
	"$(INTDIR)\GeoEditOutside.obj" \
	"$(INTDIR)\GeoEditP.obj" \
	"$(INTDIR)\IntersectLineDlg.obj" \
	"$(INTDIR)\IslandAdd.obj" \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\Kreis.obj" \
	"$(INTDIR)\LineElongation.obj" \
	"$(INTDIR)\MakeRectangular.obj" \
	"$(INTDIR)\Marker.obj" \
	"$(INTDIR)\NewArea.obj" \
	"$(INTDIR)\NewLine.obj" \
	"$(INTDIR)\NewPoint.obj" \
	"$(INTDIR)\ObjectModify.obj" \
	"$(INTDIR)\ObjectModifyFunc.obj" \
	"$(INTDIR)\ObjectMove.obj" \
	"$(INTDIR)\PropExt.obj" \
	"$(INTDIR)\RestrictCursor.obj" \
	"$(INTDIR)\RestrictLine.obj" \
	"$(INTDIR)\SingleDesignDlg.obj" \
	"$(INTDIR)\ToolBars.obj" \
	"$(INTDIR)\TopicalObjects.obj" \
	"$(INTDIR)\UIOwnerFunc.obj" \
	"$(INTDIR)\VertexAdd.obj" \
	"$(INTDIR)\VertexModDlg.obj" \
	"$(INTDIR)\VertexMove.obj"

"$(OUTDIR)\GeoEdit.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\GeoEdit.ext
TargetName=GeoEdit
InputPath=.\WinRel\GeoEdit.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug
# Begin Custom Macros
TargetName=GeoEditD
# End Custom Macros

ALL : "$(OUTDIR)\GeoEditD.ext" "$(OUTDIR)\Geoedit.bsc"\
 "..\..\TRIAS\TRIAS32D\GeoEditD.ext" ".\IGeoEdit.c"

CLEAN : 
	-@erase "$(INTDIR)\AreaPartition.obj"
	-@erase "$(INTDIR)\AreaPartition.sbr"
	-@erase "$(INTDIR)\BmpBtn.obj"
	-@erase "$(INTDIR)\BmpBtn.sbr"
	-@erase "$(INTDIR)\CrossObject.obj"
	-@erase "$(INTDIR)\CrossObject.sbr"
	-@erase "$(INTDIR)\DesignDlg.obj"
	-@erase "$(INTDIR)\DesignDlg.sbr"
	-@erase "$(INTDIR)\Designing.obj"
	-@erase "$(INTDIR)\Designing.sbr"
	-@erase "$(INTDIR)\DragMultiLine.obj"
	-@erase "$(INTDIR)\DragMultiLine.sbr"
	-@erase "$(INTDIR)\EditBaseDlg.obj"
	-@erase "$(INTDIR)\EditBaseDlg.sbr"
	-@erase "$(INTDIR)\EditCoordDlg.obj"
	-@erase "$(INTDIR)\EditCoordDlg.sbr"
	-@erase "$(INTDIR)\EditDlg.obj"
	-@erase "$(INTDIR)\EditDlg.sbr"
	-@erase "$(INTDIR)\EnumObjektGeometrie.obj"
	-@erase "$(INTDIR)\EnumObjektGeometrie.sbr"
	-@erase "$(INTDIR)\FixPointsDlg.obj"
	-@erase "$(INTDIR)\FixPointsDlg.sbr"
	-@erase "$(INTDIR)\GeoEdit.obj"
	-@erase "$(INTDIR)\GeoEdit.res"
	-@erase "$(INTDIR)\GeoEdit.sbr"
	-@erase "$(INTDIR)\GEOEDITD.idb"
	-@erase "$(INTDIR)\GEOEDITD.pch"
	-@erase "$(INTDIR)\GEOEDITD.pdb"
	-@erase "$(INTDIR)\GeoEditInterface.obj"
	-@erase "$(INTDIR)\GeoEditInterface.sbr"
	-@erase "$(INTDIR)\GeoEditLib.obj"
	-@erase "$(INTDIR)\GeoEditLib.sbr"
	-@erase "$(INTDIR)\GeoEditOutside.obj"
	-@erase "$(INTDIR)\GeoEditOutside.sbr"
	-@erase "$(INTDIR)\GeoEditP.obj"
	-@erase "$(INTDIR)\GeoEditP.sbr"
	-@erase "$(INTDIR)\IntersectLineDlg.obj"
	-@erase "$(INTDIR)\IntersectLineDlg.sbr"
	-@erase "$(INTDIR)\IslandAdd.obj"
	-@erase "$(INTDIR)\IslandAdd.sbr"
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\Jumptab.sbr"
	-@erase "$(INTDIR)\Kreis.obj"
	-@erase "$(INTDIR)\Kreis.sbr"
	-@erase "$(INTDIR)\LineElongation.obj"
	-@erase "$(INTDIR)\LineElongation.sbr"
	-@erase "$(INTDIR)\MakeRectangular.obj"
	-@erase "$(INTDIR)\MakeRectangular.sbr"
	-@erase "$(INTDIR)\Marker.obj"
	-@erase "$(INTDIR)\Marker.sbr"
	-@erase "$(INTDIR)\NewArea.obj"
	-@erase "$(INTDIR)\NewArea.sbr"
	-@erase "$(INTDIR)\NewLine.obj"
	-@erase "$(INTDIR)\NewLine.sbr"
	-@erase "$(INTDIR)\NewPoint.obj"
	-@erase "$(INTDIR)\NewPoint.sbr"
	-@erase "$(INTDIR)\ObjectModify.obj"
	-@erase "$(INTDIR)\ObjectModify.sbr"
	-@erase "$(INTDIR)\ObjectModifyFunc.obj"
	-@erase "$(INTDIR)\ObjectModifyFunc.sbr"
	-@erase "$(INTDIR)\ObjectMove.obj"
	-@erase "$(INTDIR)\ObjectMove.sbr"
	-@erase "$(INTDIR)\PropExt.obj"
	-@erase "$(INTDIR)\PropExt.sbr"
	-@erase "$(INTDIR)\RestrictCursor.obj"
	-@erase "$(INTDIR)\RestrictCursor.sbr"
	-@erase "$(INTDIR)\RestrictLine.obj"
	-@erase "$(INTDIR)\RestrictLine.sbr"
	-@erase "$(INTDIR)\SingleDesignDlg.obj"
	-@erase "$(INTDIR)\SingleDesignDlg.sbr"
	-@erase "$(INTDIR)\ToolBars.obj"
	-@erase "$(INTDIR)\ToolBars.sbr"
	-@erase "$(INTDIR)\TopicalObjects.obj"
	-@erase "$(INTDIR)\TopicalObjects.sbr"
	-@erase "$(INTDIR)\UIOwnerFunc.obj"
	-@erase "$(INTDIR)\UIOwnerFunc.sbr"
	-@erase "$(INTDIR)\VertexAdd.obj"
	-@erase "$(INTDIR)\VertexAdd.sbr"
	-@erase "$(INTDIR)\VertexModDlg.obj"
	-@erase "$(INTDIR)\VertexModDlg.sbr"
	-@erase "$(INTDIR)\VertexMove.obj"
	-@erase "$(INTDIR)\VertexMove.sbr"
	-@erase "$(OUTDIR)\Geoedit.bsc"
	-@erase "$(OUTDIR)\GeoEditD.exp"
	-@erase "$(OUTDIR)\GeoEditD.ext"
	-@erase "$(OUTDIR)\GeoEditD.ilk"
	-@erase "$(OUTDIR)\GeoEditD.lib"
	-@erase "..\..\TRIAS\TRIAS32D\GeoEditD.ext"
	-@erase ".\IGeoEdit.c"
	-@erase ".\IGeoEdit.h"
	-@erase ".\IGeoEdit.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/GEOEDIT.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\Z_HXX" /D "_DEBUG" /D "_DRAGDROP" /D "OS_STL_ASSERT" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr /Fp"WinDebug/GEOEDITD.pch" /Yu"GeoEditP.h" /Fd"WinDebug/GEOEDITD.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\Z_HXX" /D "_DEBUG" /D\
 "_DRAGDROP" /D "OS_STL_ASSERT" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOEDITD.pch"\
 /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOEDITD.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/GeoEdit.res" /i "..\Z_HXX" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Geoedit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AreaPartition.sbr" \
	"$(INTDIR)\BmpBtn.sbr" \
	"$(INTDIR)\CrossObject.sbr" \
	"$(INTDIR)\DesignDlg.sbr" \
	"$(INTDIR)\Designing.sbr" \
	"$(INTDIR)\DragMultiLine.sbr" \
	"$(INTDIR)\EditBaseDlg.sbr" \
	"$(INTDIR)\EditCoordDlg.sbr" \
	"$(INTDIR)\EditDlg.sbr" \
	"$(INTDIR)\EnumObjektGeometrie.sbr" \
	"$(INTDIR)\FixPointsDlg.sbr" \
	"$(INTDIR)\GeoEdit.sbr" \
	"$(INTDIR)\GeoEditInterface.sbr" \
	"$(INTDIR)\GeoEditLib.sbr" \
	"$(INTDIR)\GeoEditOutside.sbr" \
	"$(INTDIR)\GeoEditP.sbr" \
	"$(INTDIR)\IntersectLineDlg.sbr" \
	"$(INTDIR)\IslandAdd.sbr" \
	"$(INTDIR)\Jumptab.sbr" \
	"$(INTDIR)\Kreis.sbr" \
	"$(INTDIR)\LineElongation.sbr" \
	"$(INTDIR)\MakeRectangular.sbr" \
	"$(INTDIR)\Marker.sbr" \
	"$(INTDIR)\NewArea.sbr" \
	"$(INTDIR)\NewLine.sbr" \
	"$(INTDIR)\NewPoint.sbr" \
	"$(INTDIR)\ObjectModify.sbr" \
	"$(INTDIR)\ObjectModifyFunc.sbr" \
	"$(INTDIR)\ObjectMove.sbr" \
	"$(INTDIR)\PropExt.sbr" \
	"$(INTDIR)\RestrictCursor.sbr" \
	"$(INTDIR)\RestrictLine.sbr" \
	"$(INTDIR)\SingleDesignDlg.sbr" \
	"$(INTDIR)\ToolBars.sbr" \
	"$(INTDIR)\TopicalObjects.sbr" \
	"$(INTDIR)\UIOwnerFunc.sbr" \
	"$(INTDIR)\VertexAdd.sbr" \
	"$(INTDIR)\VertexModDlg.sbr" \
	"$(INTDIR)\VertexMove.sbr"

"$(OUTDIR)\Geoedit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtAtd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastld.lib ospace2d.lib ebn.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"WinDebug/GeoEditD.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /nodefaultlib
LINK32_FLAGS=geometd.lib ixtAtd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastld.lib ospace2d.lib ebn.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/GeoEditD.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd.lib"\
 /def:".\GeoEdit.def" /out:"$(OUTDIR)/GeoEditD.ext"\
 /implib:"$(OUTDIR)/GeoEditD.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\GeoEdit.def"
LINK32_OBJS= \
	"$(INTDIR)\AreaPartition.obj" \
	"$(INTDIR)\BmpBtn.obj" \
	"$(INTDIR)\CrossObject.obj" \
	"$(INTDIR)\DesignDlg.obj" \
	"$(INTDIR)\Designing.obj" \
	"$(INTDIR)\DragMultiLine.obj" \
	"$(INTDIR)\EditBaseDlg.obj" \
	"$(INTDIR)\EditCoordDlg.obj" \
	"$(INTDIR)\EditDlg.obj" \
	"$(INTDIR)\EnumObjektGeometrie.obj" \
	"$(INTDIR)\FixPointsDlg.obj" \
	"$(INTDIR)\GeoEdit.obj" \
	"$(INTDIR)\GeoEdit.res" \
	"$(INTDIR)\GeoEditInterface.obj" \
	"$(INTDIR)\GeoEditLib.obj" \
	"$(INTDIR)\GeoEditOutside.obj" \
	"$(INTDIR)\GeoEditP.obj" \
	"$(INTDIR)\IntersectLineDlg.obj" \
	"$(INTDIR)\IslandAdd.obj" \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\Kreis.obj" \
	"$(INTDIR)\LineElongation.obj" \
	"$(INTDIR)\MakeRectangular.obj" \
	"$(INTDIR)\Marker.obj" \
	"$(INTDIR)\NewArea.obj" \
	"$(INTDIR)\NewLine.obj" \
	"$(INTDIR)\NewPoint.obj" \
	"$(INTDIR)\ObjectModify.obj" \
	"$(INTDIR)\ObjectModifyFunc.obj" \
	"$(INTDIR)\ObjectMove.obj" \
	"$(INTDIR)\PropExt.obj" \
	"$(INTDIR)\RestrictCursor.obj" \
	"$(INTDIR)\RestrictLine.obj" \
	"$(INTDIR)\SingleDesignDlg.obj" \
	"$(INTDIR)\ToolBars.obj" \
	"$(INTDIR)\TopicalObjects.obj" \
	"$(INTDIR)\UIOwnerFunc.obj" \
	"$(INTDIR)\VertexAdd.obj" \
	"$(INTDIR)\VertexModDlg.obj" \
	"$(INTDIR)\VertexMove.obj"

"$(OUTDIR)\GeoEditD.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\GeoEditD.ext
TargetName=GeoEditD
InputPath=.\WinDebug\GeoEditD.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32D\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32D

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

# Name "Geoedit - Win32 Release"
# Name "Geoedit - Win32 Debug"

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NewPoint.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_NEWPO=\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\NewPoint.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	
# ADD CPP /Yu"GeoEditP.h"

"$(INTDIR)\NewPoint.obj" : $(SOURCE) $(DEP_CPP_NEWPO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2"\
 /Fp"$(INTDIR)/Geoedit.pch" /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_NEWPO=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\NewPoint.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_NEWPO=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	
# ADD CPP /Yu"GeoEditP.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\Z_HXX" /D "_DEBUG" /D\
 "_DRAGDROP" /D "OS_STL_ASSERT" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOEDITD.pch"\
 /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\NewPoint.obj" : $(SOURCE) $(DEP_CPP_NEWPO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"
   $(BuildCmds)

"$(INTDIR)\NewPoint.sbr" : $(SOURCE) $(DEP_CPP_NEWPO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Kreis.cpp
DEP_CPP_KREIS=\
	"..\Z_HXX\BasicFunctions.hxx"\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_KREIS=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"

# ADD CPP /Yu"GeoEditP.h"

"$(INTDIR)\Kreis.obj" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2"\
 /Fp"$(INTDIR)/Geoedit.pch" /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"GeoEditP.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\Z_HXX" /D "_DEBUG" /D\
 "_DRAGDROP" /D "OS_STL_ASSERT" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOEDITD.pch"\
 /Yu"GeoEditP.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Kreis.obj" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"
   $(BuildCmds)

"$(INTDIR)\Kreis.sbr" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGeoEdit.idl

!IF  "$(CFG)" == "Geoedit - Win32 Release"

# Begin Custom Build
InputPath=.\IGeoEdit.idl

BuildCmds= \
	midl /Oicf /h IGeoEdit.h /iid IGeoEdit.c IGeoEdit.idl \
	

"IGeoEdit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# Begin Custom Build
InputPath=.\IGeoEdit.idl

BuildCmds= \
	midl /Oicf /h IGeoEdit.h /iid IGeoEdit.c IGeoEdit.idl \
	

"IGeoEdit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IGeoEdit.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewPoint.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEditP.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_GEOED=\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	
# ADD CPP /Yc"GeoEditP.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\Z_HXX" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "EBWIN32" /D "__ATL_11_USED__" /D "_TRIAS_OLDIMPLEMENTATION2"\
 /Fp"$(INTDIR)/Geoedit.pch" /Yc"GeoEditP.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\GeoEditP.obj" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Geoedit.pch" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_GEOED=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_GEOED=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	
# ADD CPP /Yc"GeoEditP.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\Z_HXX" /D "_DEBUG" /D\
 "_DRAGDROP" /D "OS_STL_ASSERT" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "EBWIN32" /D "__ATL_11_USED__" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOEDITD.pch"\
 /Yc"GeoEditP.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GeoEditP.obj" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 ".\IGeoEdit.h"
   $(BuildCmds)

"$(INTDIR)\GeoEditP.sbr" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 ".\IGeoEdit.h"
   $(BuildCmds)

"$(INTDIR)\GEOEDITD.pch" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 ".\IGeoEdit.h"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEdit.def

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEdit.rc
DEP_RSC_GEOEDI=\
	".\AreaPartition.rgs"\
	".\CloseContourDisabled.bmp"\
	".\CloseContourDown.bmp"\
	".\CloseContourFocus.bmp"\
	".\CloseContourUp.bmp"\
	".\CommonBorderDisabled.bmp"\
	".\CommonBorderDown.bmp"\
	".\CommonBorderFocus.bmp"\
	".\CommonBorderUp.bmp"\
	".\cross_m.cur"\
	".\delete.cur"\
	".\DeletePointDisabled.bmp"\
	".\DeletePointDown.bmp"\
	".\DeletePointFocus.bmp"\
	".\DeletePointUp.bmp"\
	".\Designing.rgs"\
	".\DesignToolbar.bmp"\
	".\DragMultiLine.rgs"\
	".\EditToolbar.bmp"\
	".\EnumObjektGeometrie.rgs"\
	".\GEOEDIT.RCV"\
	".\GeoEditOutside.rc"\
	".\IGeoEdit.tlb"\
	".\INNERH.CUR"\
	".\IslandAdd.rgs"\
	".\KreisBogenDisabled.bmp"\
	".\KreisBogenDown.bmp"\
	".\KreisBogenFocus.bmp"\
	".\KreisBogenUp.bmp"\
	".\LineElongation.rgs"\
	".\MakeRectangular.rgs"\
	".\move.cur"\
	".\NewArea.rgs"\
	".\NewLine.rgs"\
	".\NewPoint.rgs"\
	".\ObjectModify.rgs"\
	".\ObjectMove.rgs"\
	".\Palette.cur"\
	".\RestrictCursor.rgs"\
	".\RestrictLine.rgs"\
	".\split.cur"\
	".\TopicalObjects.rgs"\
	".\VertexAdd.rgs"\
	".\VertexMove.rgs"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\RESSTRG.H"\
	
NODEP_RSC_GEOEDI=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\GeoEdit.res" : $(SOURCE) $(DEP_RSC_GEOEDI) "$(INTDIR)"\
 ".\IGeoEdit.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEdit.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_GEOEDIT=\
	"..\Z_HXX\dragline.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\ProgressProxy.h"\
	"..\Z_HXX\progstat.h"\
	"..\Z_HXX\reinguid.h"\
	"..\Z_HXX\uiowner.h"\
	".\AreaPartition.h"\
	".\BmpBtn.h"\
	".\CrossObject.h"\
	".\Designing.h"\
	".\DragCrossObject.h"\
	".\DragMultiLine.h"\
	".\EditBaseDlg.h"\
	".\EditCoordDlg.h"\
	".\EditDlg.h"\
	".\EditGuid.h"\
	".\EnumObjektGeometrie.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\IslandAdd.h"\
	".\LineElongation.h"\
	".\MakeRectangular.h"\
	".\NewArea.h"\
	".\NewLine.h"\
	".\NewPoint.h"\
	".\ObjectModify.h"\
	".\ObjectMove.h"\
	".\PropExt.h"\
	".\RestrictCursor.h"\
	".\RestrictLine.h"\
	".\SmartInterfaces.h"\
	".\TopicalObjects.h"\
	".\version.h"\
	".\VertexAdd.h"\
	".\VertexMove.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\GeoEdit.obj" : $(SOURCE) $(DEP_CPP_GEOEDIT) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_GEOEDIT=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\ProgressProxy.h"\
	"..\Z_HXX\progstat.h"\
	"..\Z_HXX\reinguid.h"\
	"..\Z_HXX\uiowner.h"\
	".\AreaPartition.h"\
	".\BmpBtn.h"\
	".\CrossObject.h"\
	".\Designing.h"\
	".\DragCrossObject.h"\
	".\DragMultiLine.h"\
	".\EditBaseDlg.h"\
	".\EditCoordDlg.h"\
	".\EditDlg.h"\
	".\EnumObjektGeometrie.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\IslandAdd.h"\
	".\LineElongation.h"\
	".\MakeRectangular.h"\
	".\NewArea.h"\
	".\NewLine.h"\
	".\NewPoint.h"\
	".\ObjectModify.h"\
	".\ObjectMove.h"\
	".\PropExt.h"\
	".\RestrictCursor.h"\
	".\RestrictLine.h"\
	".\SmartInterfaces.h"\
	".\TopicalObjects.h"\
	".\version.h"\
	".\VertexAdd.h"\
	".\VertexMove.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

"$(INTDIR)\GeoEdit.obj" : $(SOURCE) $(DEP_CPP_GEOEDIT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\GeoEdit.sbr" : $(SOURCE) $(DEP_CPP_GEOEDIT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Marker.cpp
DEP_CPP_MARKE=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_MARKE=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Marker.obj" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Marker.obj" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\Marker.sbr" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditCoordDlg.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_EDITC=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\BmpBtn.h"\
	".\EditCoordDlg.h"\
	".\EditDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_EDITC=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\EditCoordDlg.obj" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_EDITC=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\BmpBtn.h"\
	".\EditCoordDlg.h"\
	".\EditDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_EDITC=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\EditCoordDlg.obj" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\EditCoordDlg.sbr" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditBaseDlg.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_EDITB=\
	".\BmpBtn.h"\
	".\EditBaseDlg.h"\
	".\EditDlg.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\Kreis.h"\
	".\PropExt.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

"$(INTDIR)\EditBaseDlg.obj" : $(SOURCE) $(DEP_CPP_EDITB) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_EDITB=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\BmpBtn.h"\
	".\EditBaseDlg.h"\
	".\EditDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Kreis.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_EDITB=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\EditBaseDlg.obj" : $(SOURCE) $(DEP_CPP_EDITB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\EditBaseDlg.sbr" : $(SOURCE) $(DEP_CPP_EDITB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditDlg.cpp
DEP_CPP_EDITD=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\BmpBtn.h"\
	".\EditBaseDlg.h"\
	".\EditDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_EDITD=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\EditDlg.obj" : $(SOURCE) $(DEP_CPP_EDITD) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\EditDlg.obj" : $(SOURCE) $(DEP_CPP_EDITD) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\EditDlg.sbr" : $(SOURCE) $(DEP_CPP_EDITD) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropExt.cpp
DEP_CPP_PROPE=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_PROPE=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\PropExt.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\PropExt.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\PropExt.sbr" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewLine.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_NEWLI=\
	"..\Z_HXX\dragline.hxx"\
	".\DragMultiLine.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\NewLine.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\NewLine.obj" : $(SOURCE) $(DEP_CPP_NEWLI) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_NEWLI=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\dragline.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DragMultiLine.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\NewLine.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_NEWLI=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\NewLine.obj" : $(SOURCE) $(DEP_CPP_NEWLI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\NewLine.sbr" : $(SOURCE) $(DEP_CPP_NEWLI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewLine.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewArea.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_NEWAR=\
	"..\Z_HXX\dragline.hxx"\
	".\DragMultiLine.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\NewArea.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\NewArea.obj" : $(SOURCE) $(DEP_CPP_NEWAR) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_NEWAR=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\dragline.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DragMultiLine.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\NewArea.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_NEWAR=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\NewArea.obj" : $(SOURCE) $(DEP_CPP_NEWAR) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\NewArea.sbr" : $(SOURCE) $(DEP_CPP_NEWAR) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewArea.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectModify.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectModify.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_OBJEC=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\reinguid.h"\
	"..\Z_HXX\strecke.hxx"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\ObjectModify.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\ObjectModify.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_OBJEC=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\reinguid.h"\
	"..\Z_HXX\strecke.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\ObjectModify.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_OBJEC=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\ObjectModify.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\ObjectModify.sbr" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VertexMove.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_VERTE=\
	"..\Z_HXX\objgguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	".\VertexMove.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\VertexMove.obj" : $(SOURCE) $(DEP_CPP_VERTE) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_VERTE=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	".\VertexMove.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_VERTE=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\VertexMove.obj" : $(SOURCE) $(DEP_CPP_VERTE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\VertexMove.sbr" : $(SOURCE) $(DEP_CPP_VERTE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VertexMove.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragMultiLine.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_DRAGM=\
	"..\Z_HXX\dragline.hxx"\
	".\DragMultiLine.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\DragMultiLine.obj" : $(SOURCE) $(DEP_CPP_DRAGM) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_DRAGM=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\dragline.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DragMultiLine.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_DRAGM=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\DragMultiLine.obj" : $(SOURCE) $(DEP_CPP_DRAGM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\DragMultiLine.sbr" : $(SOURCE) $(DEP_CPP_DRAGM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragMultiLine.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jumptab.cpp
DEP_CPP_JUMPT=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditOutside.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\JumpTab.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_JUMPT=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\Jumptab.sbr" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TopicalObjects.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TopicalObjects.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_TOPIC=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\strecke.hxx"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	".\TopicalObjects.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	

"$(INTDIR)\TopicalObjects.obj" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_TOPIC=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\strecke.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	".\TopicalObjects.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_TOPIC=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\TopicalObjects.obj" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\TopicalObjects.sbr" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEditOutside.cpp
DEP_CPP_GEOEDITO=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditOutside.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\JumpTab.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Bscrerr.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRACE.H"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_GEOEDITO=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\GeoEditOutside.obj" : $(SOURCE) $(DEP_CPP_GEOEDITO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\GeoEditOutside.obj" : $(SOURCE) $(DEP_CPP_GEOEDITO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\GeoEditOutside.sbr" : $(SOURCE) $(DEP_CPP_GEOEDITO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VertexAdd.cpp
DEP_CPP_VERTEX=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	".\VertexAdd.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_VERTEX=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\VertexAdd.obj" : $(SOURCE) $(DEP_CPP_VERTEX) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\VertexAdd.obj" : $(SOURCE) $(DEP_CPP_VERTEX) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\VertexAdd.sbr" : $(SOURCE) $(DEP_CPP_VERTEX) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VertexAdd.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MakeRectangular.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MakeRectangular.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_MAKER=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\strecke.hxx"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\MakeRectangular.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\MakeRectangular.obj" : $(SOURCE) $(DEP_CPP_MAKER) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_MAKER=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\strecke.hxx"\
	".\GeoEditP.h"\
	".\MakeRectangular.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	

"$(INTDIR)\MakeRectangular.obj" : $(SOURCE) $(DEP_CPP_MAKER) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\MakeRectangular.sbr" : $(SOURCE) $(DEP_CPP_MAKER) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEditInterface.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_GEOEDITI=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	".\EditGuid.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\GeoEditInterface.obj" : $(SOURCE) $(DEP_CPP_GEOEDITI) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_GEOEDITI=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditGuid.h"\
	".\EditKonst.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_GEOEDITI=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\GeoEditInterface.obj" : $(SOURCE) $(DEP_CPP_GEOEDITI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\GeoEditInterface.sbr" : $(SOURCE) $(DEP_CPP_GEOEDITI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LineElongation.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_LINEE=\
	"..\Z_HXX\objgguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\LineElongation.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\LineElongation.obj" : $(SOURCE) $(DEP_CPP_LINEE) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_LINEE=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\LineElongation.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_LINEE=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\LineElongation.obj" : $(SOURCE) $(DEP_CPP_LINEE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\LineElongation.sbr" : $(SOURCE) $(DEP_CPP_LINEE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LineElongation.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AreaPartition.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_AREAP=\
	"..\Z_HXX\operguid.h"\
	".\AreaPartition.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\IntersectLineDlg.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\AreaPartition.obj" : $(SOURCE) $(DEP_CPP_AREAP) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_AREAP=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\AreaPartition.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\IntersectLineDlg.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_AREAP=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\AreaPartition.obj" : $(SOURCE) $(DEP_CPP_AREAP) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\AreaPartition.sbr" : $(SOURCE) $(DEP_CPP_AREAP) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AreaPartition.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectMove.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_OBJECT=\
	"..\Z_HXX\objgguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\ObjectMove.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_OBJECT=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\ObjectMove.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_OBJECT=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\ProgressProxy.h"\
	"..\Z_HXX\progstat.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\ObjectMove.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_OBJECT=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\ObjectMove.obj" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\ObjectMove.sbr" : $(SOURCE) $(DEP_CPP_OBJECT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectMove.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntersectLineDlg.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_INTER=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\IntersectLineDlg.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_INTER=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\IntersectLineDlg.obj" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_INTER=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\IntersectLineDlg.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_INTER=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\IntersectLineDlg.obj" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\IntersectLineDlg.sbr" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VertexModDlg.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_VERTEXM=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	".\VertexModDlg.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_VERTEXM=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\VertexModDlg.obj" : $(SOURCE) $(DEP_CPP_VERTEXM) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_VERTEXM=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	".\VertexModDlg.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_VERTEXM=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\VertexModDlg.obj" : $(SOURCE) $(DEP_CPP_VERTEXM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\VertexModDlg.sbr" : $(SOURCE) $(DEP_CPP_VERTEXM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IslandAdd.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_ISLAN=\
	"..\Z_HXX\objgguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\IslandAdd.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\IslandAdd.obj" : $(SOURCE) $(DEP_CPP_ISLAN) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_ISLAN=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\IslandAdd.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_ISLAN=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\IslandAdd.obj" : $(SOURCE) $(DEP_CPP_ISLAN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\IslandAdd.sbr" : $(SOURCE) $(DEP_CPP_ISLAN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IslandAdd.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeoEditLib.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_GEOEDITL=\
	"..\Z_HXX\objgguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\GeoEditLib.obj" : $(SOURCE) $(DEP_CPP_GEOEDITL) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_GEOEDITL=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_GEOEDITL=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\GeoEditLib.obj" : $(SOURCE) $(DEP_CPP_GEOEDITL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\GeoEditLib.sbr" : $(SOURCE) $(DEP_CPP_GEOEDITL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjectModifyFunc.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_OBJECTM=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\reinguid.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\ObjectModify.h"\
	".\SmartInterfaces.h"\
	".\VertexModDlg.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\ObjectModifyFunc.obj" : $(SOURCE) $(DEP_CPP_OBJECTM) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_OBJECTM=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\reinguid.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\ObjectModify.h"\
	".\SmartInterfaces.h"\
	".\VertexModDlg.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_OBJECTM=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\ObjectModifyFunc.obj" : $(SOURCE) $(DEP_CPP_OBJECTM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\ObjectModifyFunc.sbr" : $(SOURCE) $(DEP_CPP_OBJECTM) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Designing.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Designing.cpp
DEP_CPP_DESIG=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DesignDlg.h"\
	".\Designing.h"\
	".\EditKonst.h"\
	".\FixPointsDlg.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SingleDesignDlg.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_DESIG=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Designing.obj" : $(SOURCE) $(DEP_CPP_DESIG) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Designing.obj" : $(SOURCE) $(DEP_CPP_DESIG) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\Designing.sbr" : $(SOURCE) $(DEP_CPP_DESIG) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleDesignDlg.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_SINGL=\
	".\DesignDlg.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\PropExt.h"\
	".\SingleDesignDlg.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

"$(INTDIR)\SingleDesignDlg.obj" : $(SOURCE) $(DEP_CPP_SINGL) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_SINGL=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DesignDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	".\SingleDesignDlg.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_SINGL=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\SingleDesignDlg.obj" : $(SOURCE) $(DEP_CPP_SINGL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\SingleDesignDlg.sbr" : $(SOURCE) $(DEP_CPP_SINGL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DesignDlg.cpp
DEP_CPP_DESIGN=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DesignDlg.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_DESIGN=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\DesignDlg.obj" : $(SOURCE) $(DEP_CPP_DESIGN) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\DesignDlg.obj" : $(SOURCE) $(DEP_CPP_DESIGN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\DesignDlg.sbr" : $(SOURCE) $(DEP_CPP_DESIGN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToolBars.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_TOOLB=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\uiowner.h"\
	".\EditGuid.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\ToolBars.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_TOOLB=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\uiowner.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditGuid.h"\
	".\EditKonst.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_TOOLB=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\ToolBars.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\ToolBars.sbr" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UIOwnerFunc.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_UIOWN=\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\uiowner.h"\
	".\EditGuid.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditP.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\UIOwnerFunc.obj" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_UIOWN=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\objgguid.h"\
	"..\Z_HXX\operguid.h"\
	"..\Z_HXX\uiowner.h"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditGuid.h"\
	".\EditKonst.h"\
	".\GeoEdit.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_UIOWN=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\UIOwnerFunc.obj" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\UIOwnerFunc.sbr" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CrossObject.cpp
DEP_CPP_CROSS=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\CrossObject.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_CROSS=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\CrossObject.obj" : $(SOURCE) $(DEP_CPP_CROSS) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\CrossObject.obj" : $(SOURCE) $(DEP_CPP_CROSS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\CrossObject.sbr" : $(SOURCE) $(DEP_CPP_CROSS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RestrictLine.cpp

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_RESTR=\
	"..\Z_HXX\ScreenGeometry.hxx"\
	"..\Z_HXX\strecke.hxx"\
	".\GeoEditP.h"\
	".\RestrictLine.h"\
	

"$(INTDIR)\RestrictLine.obj" : $(SOURCE) $(DEP_CPP_RESTR) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_RESTR=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\ScreenGeometry.hxx"\
	"..\Z_HXX\strecke.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\RestrictLine.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_RESTR=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

"$(INTDIR)\RestrictLine.obj" : $(SOURCE) $(DEP_CPP_RESTR) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\RestrictLine.sbr" : $(SOURCE) $(DEP_CPP_RESTR) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RestrictLine.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RestrictCursor.cpp
DEP_CPP_RESTRI=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\CrossObject.h"\
	".\DragCrossObject.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\RestrictCursor.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_RESTRI=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\RestrictCursor.obj" : $(SOURCE) $(DEP_CPP_RESTRI) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\RestrictCursor.obj" : $(SOURCE) $(DEP_CPP_RESTRI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\RestrictCursor.sbr" : $(SOURCE) $(DEP_CPP_RESTRI) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RestrictCursor.rgs

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FixPointsDlg.cpp
DEP_CPP_FIXPO=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\DesignDlg.h"\
	".\EditKonst.h"\
	".\FixPointsDlg.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\PropExt.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_FIXPO=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\FixPointsDlg.obj" : $(SOURCE) $(DEP_CPP_FIXPO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\FixPointsDlg.obj" : $(SOURCE) $(DEP_CPP_FIXPO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\FixPointsDlg.sbr" : $(SOURCE) $(DEP_CPP_FIXPO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EnumObjektGeometrie.cpp
DEP_CPP_ENUMO=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\EditKonst.h"\
	".\EnumObjektGeometrie.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_ENUMO=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\EnumObjektGeometrie.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\EnumObjektGeometrie.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\EnumObjektGeometrie.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BmpBtn.cpp
DEP_CPP_BMPBT=\
	"..\Z_HXX\ctfx.hxx"\
	"..\Z_HXX\ctfxmfc.h"\
	"..\Z_HXX\datbank.hxx"\
	"..\Z_HXX\errcodes.hxx"\
	"..\Z_HXX\FormatString.hxx"\
	"..\Z_HXX\geo_obj.hxx"\
	"..\Z_HXX\geokonst.hxx"\
	"..\Z_HXX\GeometrM.hxx"\
	"..\Z_HXX\identlst.hxx"\
	"..\Z_HXX\koord.hxx"\
	"..\Z_HXX\objgext.hxx"\
	"..\Z_HXX\zeichnen.hxx"\
	".\BmpBtn.h"\
	".\EditKonst.h"\
	".\GeoEditConfig.h"\
	".\GeoEditLib.h"\
	".\GeoEditM.h"\
	".\GeoEditP.h"\
	".\IGeoEdit.h"\
	".\Marker.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\DRAWOBJ.HXX"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_BMPBT=\
	"C:\MSDEV\EBN21\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\BmpBtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch" ".\IGeoEdit.h"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\BmpBtn.obj" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"

"$(INTDIR)\BmpBtn.sbr" : $(SOURCE) $(DEP_CPP_BMPBT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch" ".\IGeoEdit.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
