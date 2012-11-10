# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Tfrm32 - Win32 Framework DLL Debug
!MESSAGE No configuration specified.  Defaulting to Tfrm32 - Win32 Framework\
 DLL Debug.
!ENDIF 

!IF "$(CFG)" != "Tfrm32 - Win32 Framework DLL Release" && "$(CFG)" !=\
 "Tfrm32 - Win32 Framework DLL Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4.mak" CFG="Tfrm32 - Win32 Framework DLL Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tfrm32 - Win32 Framework DLL Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tfrm32 - Win32 Framework DLL Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Tfrm32 - Win32 Framework DLL Release"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release.207"
# PROP Intermediate_Dir "Release.207"
OUTDIR=.\Release.207
INTDIR=.\Release.207
# Begin Custom Macros
TargetName=Tfrmwork
# End Custom Macros

ALL : "$(OUTDIR)\Tfrmwork.dll" "$(OUTDIR)\Tfrm4.bsc"\
 "c:\trias\trias.rel\Tfrmwork.dll"

CLEAN : 
	-@erase "$(INTDIR)\_ACCEL.OBJ"
	-@erase "$(INTDIR)\_ACCEL.SBR"
	-@erase "$(INTDIR)\_ACCL_IM.OBJ"
	-@erase "$(INTDIR)\_ACCL_IM.SBR"
	-@erase "$(INTDIR)\_APP.OBJ"
	-@erase "$(INTDIR)\_APP.SBR"
	-@erase "$(INTDIR)\_APP_IM.OBJ"
	-@erase "$(INTDIR)\_APP_IM.SBR"
	-@erase "$(INTDIR)\_APPW_IM.OBJ"
	-@erase "$(INTDIR)\_APPW_IM.SBR"
	-@erase "$(INTDIR)\_APPWIND.OBJ"
	-@erase "$(INTDIR)\_APPWIND.SBR"
	-@erase "$(INTDIR)\_AUX1.OBJ"
	-@erase "$(INTDIR)\_AUX1.SBR"
	-@erase "$(INTDIR)\_AUX2.OBJ"
	-@erase "$(INTDIR)\_AUX2.SBR"
	-@erase "$(INTDIR)\_BITMAP.OBJ"
	-@erase "$(INTDIR)\_BITMAP.SBR"
	-@erase "$(INTDIR)\_BPRINT.OBJ"
	-@erase "$(INTDIR)\_BPRINT.SBR"
	-@erase "$(INTDIR)\_BRSH_IM.OBJ"
	-@erase "$(INTDIR)\_BRSH_IM.SBR"
	-@erase "$(INTDIR)\_BRUSH.OBJ"
	-@erase "$(INTDIR)\_BRUSH.SBR"
	-@erase "$(INTDIR)\_BTMP_IM.OBJ"
	-@erase "$(INTDIR)\_BTMP_IM.SBR"
	-@erase "$(INTDIR)\_CLIP_IM.OBJ"
	-@erase "$(INTDIR)\_CLIP_IM.SBR"
	-@erase "$(INTDIR)\_CLIPBRD.OBJ"
	-@erase "$(INTDIR)\_CLIPBRD.SBR"
	-@erase "$(INTDIR)\_CONTEXT.OBJ"
	-@erase "$(INTDIR)\_CONTEXT.SBR"
	-@erase "$(INTDIR)\_CONTROL.OBJ"
	-@erase "$(INTDIR)\_CONTROL.SBR"
	-@erase "$(INTDIR)\_CTLB_IM.OBJ"
	-@erase "$(INTDIR)\_CTLB_IM.SBR"
	-@erase "$(INTDIR)\_CUR_IM.OBJ"
	-@erase "$(INTDIR)\_CUR_IM.SBR"
	-@erase "$(INTDIR)\_CURSOR.OBJ"
	-@erase "$(INTDIR)\_CURSOR.SBR"
	-@erase "$(INTDIR)\_DCWD_IM.OBJ"
	-@erase "$(INTDIR)\_DCWD_IM.SBR"
	-@erase "$(INTDIR)\_DCWND.OBJ"
	-@erase "$(INTDIR)\_DCWND.SBR"
	-@erase "$(INTDIR)\_DEBUG.OBJ"
	-@erase "$(INTDIR)\_DEBUG.SBR"
	-@erase "$(INTDIR)\_DIALOG.OBJ"
	-@erase "$(INTDIR)\_DIALOG.SBR"
	-@erase "$(INTDIR)\_DISPATC.OBJ"
	-@erase "$(INTDIR)\_DISPATC.SBR"
	-@erase "$(INTDIR)\_DLG_IM.OBJ"
	-@erase "$(INTDIR)\_DLG_IM.SBR"
	-@erase "$(INTDIR)\_DRAWOBJ.OBJ"
	-@erase "$(INTDIR)\_DRAWOBJ.SBR"
	-@erase "$(INTDIR)\_EC_IM.OBJ"
	-@erase "$(INTDIR)\_EC_IM.SBR"
	-@erase "$(INTDIR)\_EDITWND.OBJ"
	-@erase "$(INTDIR)\_EDITWND.SBR"
	-@erase "$(INTDIR)\_EVENT.OBJ"
	-@erase "$(INTDIR)\_EVENT.SBR"
	-@erase "$(INTDIR)\_EWIN_IM.OBJ"
	-@erase "$(INTDIR)\_EWIN_IM.SBR"
	-@erase "$(INTDIR)\_FILELB.OBJ"
	-@erase "$(INTDIR)\_FILELB.SBR"
	-@erase "$(INTDIR)\_FLB_IM.OBJ"
	-@erase "$(INTDIR)\_FLB_IM.SBR"
	-@erase "$(INTDIR)\_FONT.OBJ"
	-@erase "$(INTDIR)\_FONT.SBR"
	-@erase "$(INTDIR)\_FONT_IM.OBJ"
	-@erase "$(INTDIR)\_FONT_IM.SBR"
	-@erase "$(INTDIR)\_HELP.OBJ"
	-@erase "$(INTDIR)\_HELP.SBR"
	-@erase "$(INTDIR)\_ICON.OBJ"
	-@erase "$(INTDIR)\_ICON.SBR"
	-@erase "$(INTDIR)\_ICON_IM.OBJ"
	-@erase "$(INTDIR)\_ICON_IM.SBR"
	-@erase "$(INTDIR)\_LINK.OBJ"
	-@erase "$(INTDIR)\_LINK.SBR"
	-@erase "$(INTDIR)\_MAIN.OBJ"
	-@erase "$(INTDIR)\_MAIN.SBR"
	-@erase "$(INTDIR)\_MDI.OBJ"
	-@erase "$(INTDIR)\_MDI.SBR"
	-@erase "$(INTDIR)\_MDI_IM.OBJ"
	-@erase "$(INTDIR)\_MDI_IM.SBR"
	-@erase "$(INTDIR)\_MENU.OBJ"
	-@erase "$(INTDIR)\_MENU.SBR"
	-@erase "$(INTDIR)\_MENU_IM.OBJ"
	-@erase "$(INTDIR)\_MENU_IM.SBR"
	-@erase "$(INTDIR)\_MESB_IM.OBJ"
	-@erase "$(INTDIR)\_MESB_IM.SBR"
	-@erase "$(INTDIR)\_MESSBOX.OBJ"
	-@erase "$(INTDIR)\_MESSBOX.SBR"
	-@erase "$(INTDIR)\_PEN.OBJ"
	-@erase "$(INTDIR)\_PEN.SBR"
	-@erase "$(INTDIR)\_PEN_IM.OBJ"
	-@erase "$(INTDIR)\_PEN_IM.SBR"
	-@erase "$(INTDIR)\_POIN_IM.OBJ"
	-@erase "$(INTDIR)\_POIN_IM.SBR"
	-@erase "$(INTDIR)\_POINTER.OBJ"
	-@erase "$(INTDIR)\_POINTER.SBR"
	-@erase "$(INTDIR)\_PRIN_IM.OBJ"
	-@erase "$(INTDIR)\_PRIN_IM.SBR"
	-@erase "$(INTDIR)\_PRINT.OBJ"
	-@erase "$(INTDIR)\_PRINT.SBR"
	-@erase "$(INTDIR)\_RECTANG.OBJ"
	-@erase "$(INTDIR)\_RECTANG.SBR"
	-@erase "$(INTDIR)\_RSTRING.OBJ"
	-@erase "$(INTDIR)\_RSTRING.SBR"
	-@erase "$(INTDIR)\_RUNTIME.OBJ"
	-@erase "$(INTDIR)\_RUNTIME.SBR"
	-@erase "$(INTDIR)\_SERVICE.OBJ"
	-@erase "$(INTDIR)\_SERVICE.SBR"
	-@erase "$(INTDIR)\_WIND_IM.OBJ"
	-@erase "$(INTDIR)\_WIND_IM.SBR"
	-@erase "$(INTDIR)\_WINDOW.OBJ"
	-@erase "$(INTDIR)\_WINDOW.SBR"
	-@erase "$(INTDIR)\animate.obj"
	-@erase "$(INTDIR)\animate.sbr"
	-@erase "$(INTDIR)\COLR31IM.OBJ"
	-@erase "$(INTDIR)\COLR31IM.SBR"
	-@erase "$(INTDIR)\Ctl3dw.obj"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.SBR"
	-@erase "$(INTDIR)\FILE31IM.OBJ"
	-@erase "$(INTDIR)\FILE31IM.SBR"
	-@erase "$(INTDIR)\imagectl.obj"
	-@erase "$(INTDIR)\imagectl.sbr"
	-@erase "$(INTDIR)\IMPPAGE.OBJ"
	-@erase "$(INTDIR)\IMPPAGE.SBR"
	-@erase "$(INTDIR)\IMPPSHET.OBJ"
	-@erase "$(INTDIR)\IMPPSHET.SBR"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\listview.sbr"
	-@erase "$(INTDIR)\notfyevt.obj"
	-@erase "$(INTDIR)\notfyevt.sbr"
	-@erase "$(INTDIR)\PROGBAR.obj"
	-@erase "$(INTDIR)\PROGBAR.sbr"
	-@erase "$(INTDIR)\PROPPAGE.OBJ"
	-@erase "$(INTDIR)\PROPPAGE.SBR"
	-@erase "$(INTDIR)\PROPSHET.OBJ"
	-@erase "$(INTDIR)\PROPSHET.SBR"
	-@erase "$(INTDIR)\statbar.obj"
	-@erase "$(INTDIR)\statbar.sbr"
	-@erase "$(INTDIR)\STDDLG.OBJ"
	-@erase "$(INTDIR)\STDDLG.SBR"
	-@erase "$(INTDIR)\Tfrm4.pch"
	-@erase "$(INTDIR)\TFRMPRE.OBJ"
	-@erase "$(INTDIR)\TFRMPRE.SBR"
	-@erase "$(INTDIR)\TFRMWORK.res"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\toolbar.sbr"
	-@erase "$(INTDIR)\tooltip.obj"
	-@erase "$(INTDIR)\tooltip.sbr"
	-@erase "$(INTDIR)\treelist.obj"
	-@erase "$(INTDIR)\treelist.sbr"
	-@erase "$(INTDIR)\updown.obj"
	-@erase "$(INTDIR)\updown.sbr"
	-@erase "$(INTDIR)\ZYZ3D.OBJ"
	-@erase "$(INTDIR)\ZYZ3D.SBR"
	-@erase "$(INTDIR)\ZYZGAUGE.OBJ"
	-@erase "$(INTDIR)\ZYZGAUGE.SBR"
	-@erase "$(OUTDIR)\Tfrm4.bsc"
	-@erase "$(OUTDIR)\Tfrmwork.dll"
	-@erase "$(OUTDIR)\Tfrmwork.exp"
	-@erase "$(OUTDIR)\Tfrmwork.lib"
	-@erase "c:\trias\trias.rel\Tfrmwork.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TFRM32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr /Yu"tfrmpre.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release.207/
CPP_SBRS=.\Release.207/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TFRMWORK.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tfrm4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\_ACCEL.SBR" \
	"$(INTDIR)\_ACCL_IM.SBR" \
	"$(INTDIR)\_APP.SBR" \
	"$(INTDIR)\_APP_IM.SBR" \
	"$(INTDIR)\_APPW_IM.SBR" \
	"$(INTDIR)\_APPWIND.SBR" \
	"$(INTDIR)\_AUX1.SBR" \
	"$(INTDIR)\_AUX2.SBR" \
	"$(INTDIR)\_BITMAP.SBR" \
	"$(INTDIR)\_BPRINT.SBR" \
	"$(INTDIR)\_BRSH_IM.SBR" \
	"$(INTDIR)\_BRUSH.SBR" \
	"$(INTDIR)\_BTMP_IM.SBR" \
	"$(INTDIR)\_CLIP_IM.SBR" \
	"$(INTDIR)\_CLIPBRD.SBR" \
	"$(INTDIR)\_CONTEXT.SBR" \
	"$(INTDIR)\_CONTROL.SBR" \
	"$(INTDIR)\_CTLB_IM.SBR" \
	"$(INTDIR)\_CUR_IM.SBR" \
	"$(INTDIR)\_CURSOR.SBR" \
	"$(INTDIR)\_DCWD_IM.SBR" \
	"$(INTDIR)\_DCWND.SBR" \
	"$(INTDIR)\_DEBUG.SBR" \
	"$(INTDIR)\_DIALOG.SBR" \
	"$(INTDIR)\_DISPATC.SBR" \
	"$(INTDIR)\_DLG_IM.SBR" \
	"$(INTDIR)\_DRAWOBJ.SBR" \
	"$(INTDIR)\_EC_IM.SBR" \
	"$(INTDIR)\_EDITWND.SBR" \
	"$(INTDIR)\_EVENT.SBR" \
	"$(INTDIR)\_EWIN_IM.SBR" \
	"$(INTDIR)\_FILELB.SBR" \
	"$(INTDIR)\_FLB_IM.SBR" \
	"$(INTDIR)\_FONT.SBR" \
	"$(INTDIR)\_FONT_IM.SBR" \
	"$(INTDIR)\_HELP.SBR" \
	"$(INTDIR)\_ICON.SBR" \
	"$(INTDIR)\_ICON_IM.SBR" \
	"$(INTDIR)\_LINK.SBR" \
	"$(INTDIR)\_MAIN.SBR" \
	"$(INTDIR)\_MDI.SBR" \
	"$(INTDIR)\_MDI_IM.SBR" \
	"$(INTDIR)\_MENU.SBR" \
	"$(INTDIR)\_MENU_IM.SBR" \
	"$(INTDIR)\_MESB_IM.SBR" \
	"$(INTDIR)\_MESSBOX.SBR" \
	"$(INTDIR)\_PEN.SBR" \
	"$(INTDIR)\_PEN_IM.SBR" \
	"$(INTDIR)\_POIN_IM.SBR" \
	"$(INTDIR)\_POINTER.SBR" \
	"$(INTDIR)\_PRIN_IM.SBR" \
	"$(INTDIR)\_PRINT.SBR" \
	"$(INTDIR)\_RECTANG.SBR" \
	"$(INTDIR)\_RSTRING.SBR" \
	"$(INTDIR)\_RUNTIME.SBR" \
	"$(INTDIR)\_SERVICE.SBR" \
	"$(INTDIR)\_WIND_IM.SBR" \
	"$(INTDIR)\_WINDOW.SBR" \
	"$(INTDIR)\animate.sbr" \
	"$(INTDIR)\COLR31IM.SBR" \
	"$(INTDIR)\DRAWRECT.SBR" \
	"$(INTDIR)\FILE31IM.SBR" \
	"$(INTDIR)\imagectl.sbr" \
	"$(INTDIR)\IMPPAGE.SBR" \
	"$(INTDIR)\IMPPSHET.SBR" \
	"$(INTDIR)\listview.sbr" \
	"$(INTDIR)\notfyevt.sbr" \
	"$(INTDIR)\PROGBAR.sbr" \
	"$(INTDIR)\PROPPAGE.SBR" \
	"$(INTDIR)\PROPSHET.SBR" \
	"$(INTDIR)\statbar.sbr" \
	"$(INTDIR)\STDDLG.SBR" \
	"$(INTDIR)\TFRMPRE.SBR" \
	"$(INTDIR)\toolbar.sbr" \
	"$(INTDIR)\tooltip.sbr" \
	"$(INTDIR)\treelist.sbr" \
	"$(INTDIR)\updown.sbr" \
	"$(INTDIR)\ZYZ3D.SBR" \
	"$(INTDIR)\ZYZGAUGE.SBR"

"$(OUTDIR)\Tfrm4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 stdcppr.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release.207/Tfrmwork.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /pdb:none
LINK32_FLAGS=stdcppr.lib comctl32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/Tfrmwork.pdb" /machine:I386 /def:".\TFRM32.DEF"\
 /out:"$(OUTDIR)/Tfrmwork.dll" /implib:"$(OUTDIR)/Tfrmwork.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\TFRM32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\_ACCEL.OBJ" \
	"$(INTDIR)\_ACCL_IM.OBJ" \
	"$(INTDIR)\_APP.OBJ" \
	"$(INTDIR)\_APP_IM.OBJ" \
	"$(INTDIR)\_APPW_IM.OBJ" \
	"$(INTDIR)\_APPWIND.OBJ" \
	"$(INTDIR)\_AUX1.OBJ" \
	"$(INTDIR)\_AUX2.OBJ" \
	"$(INTDIR)\_BITMAP.OBJ" \
	"$(INTDIR)\_BPRINT.OBJ" \
	"$(INTDIR)\_BRSH_IM.OBJ" \
	"$(INTDIR)\_BRUSH.OBJ" \
	"$(INTDIR)\_BTMP_IM.OBJ" \
	"$(INTDIR)\_CLIP_IM.OBJ" \
	"$(INTDIR)\_CLIPBRD.OBJ" \
	"$(INTDIR)\_CONTEXT.OBJ" \
	"$(INTDIR)\_CONTROL.OBJ" \
	"$(INTDIR)\_CTLB_IM.OBJ" \
	"$(INTDIR)\_CUR_IM.OBJ" \
	"$(INTDIR)\_CURSOR.OBJ" \
	"$(INTDIR)\_DCWD_IM.OBJ" \
	"$(INTDIR)\_DCWND.OBJ" \
	"$(INTDIR)\_DEBUG.OBJ" \
	"$(INTDIR)\_DIALOG.OBJ" \
	"$(INTDIR)\_DISPATC.OBJ" \
	"$(INTDIR)\_DLG_IM.OBJ" \
	"$(INTDIR)\_DRAWOBJ.OBJ" \
	"$(INTDIR)\_EC_IM.OBJ" \
	"$(INTDIR)\_EDITWND.OBJ" \
	"$(INTDIR)\_EVENT.OBJ" \
	"$(INTDIR)\_EWIN_IM.OBJ" \
	"$(INTDIR)\_FILELB.OBJ" \
	"$(INTDIR)\_FLB_IM.OBJ" \
	"$(INTDIR)\_FONT.OBJ" \
	"$(INTDIR)\_FONT_IM.OBJ" \
	"$(INTDIR)\_HELP.OBJ" \
	"$(INTDIR)\_ICON.OBJ" \
	"$(INTDIR)\_ICON_IM.OBJ" \
	"$(INTDIR)\_LINK.OBJ" \
	"$(INTDIR)\_MAIN.OBJ" \
	"$(INTDIR)\_MDI.OBJ" \
	"$(INTDIR)\_MDI_IM.OBJ" \
	"$(INTDIR)\_MENU.OBJ" \
	"$(INTDIR)\_MENU_IM.OBJ" \
	"$(INTDIR)\_MESB_IM.OBJ" \
	"$(INTDIR)\_MESSBOX.OBJ" \
	"$(INTDIR)\_PEN.OBJ" \
	"$(INTDIR)\_PEN_IM.OBJ" \
	"$(INTDIR)\_POIN_IM.OBJ" \
	"$(INTDIR)\_POINTER.OBJ" \
	"$(INTDIR)\_PRIN_IM.OBJ" \
	"$(INTDIR)\_PRINT.OBJ" \
	"$(INTDIR)\_RECTANG.OBJ" \
	"$(INTDIR)\_RSTRING.OBJ" \
	"$(INTDIR)\_RUNTIME.OBJ" \
	"$(INTDIR)\_SERVICE.OBJ" \
	"$(INTDIR)\_WIND_IM.OBJ" \
	"$(INTDIR)\_WINDOW.OBJ" \
	"$(INTDIR)\animate.obj" \
	"$(INTDIR)\COLR31IM.OBJ" \
	"$(INTDIR)\Ctl3dw.obj" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\FILE31IM.OBJ" \
	"$(INTDIR)\imagectl.obj" \
	"$(INTDIR)\IMPPAGE.OBJ" \
	"$(INTDIR)\IMPPSHET.OBJ" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\notfyevt.obj" \
	"$(INTDIR)\PROGBAR.obj" \
	"$(INTDIR)\PROPPAGE.OBJ" \
	"$(INTDIR)\PROPSHET.OBJ" \
	"$(INTDIR)\statbar.obj" \
	"$(INTDIR)\STDDLG.OBJ" \
	"$(INTDIR)\TFRMPRE.OBJ" \
	"$(INTDIR)\TFRMWORK.res" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\tooltip.obj" \
	"$(INTDIR)\treelist.obj" \
	"$(INTDIR)\updown.obj" \
	"$(INTDIR)\ZYZ3D.OBJ" \
	"$(INTDIR)\ZYZGAUGE.OBJ"

"$(OUTDIR)\Tfrmwork.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Release.207
TargetPath=.\Release.207\Tfrmwork.dll
TargetName=Tfrmwork
InputPath=.\Release.207\Tfrmwork.dll
SOURCE=$(InputPath)

"c:\trias\trias.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F "$(TargetPath)" c:\trias\trias.rel
   xcopy /F "$(OutDir)\$(TargetName).lib" c:\trias\lib

# End Custom Build

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

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
TargetName=TFRM32d
# End Custom Macros

ALL : "$(OUTDIR)\TFRM32d.dll" "$(OUTDIR)\Tfrm4.bsc"\
 "c:\trias\trias.deb\TFRM32d.dll"

CLEAN : 
	-@erase "$(INTDIR)\_ACCEL.OBJ"
	-@erase "$(INTDIR)\_ACCEL.SBR"
	-@erase "$(INTDIR)\_ACCL_IM.OBJ"
	-@erase "$(INTDIR)\_ACCL_IM.SBR"
	-@erase "$(INTDIR)\_APP.OBJ"
	-@erase "$(INTDIR)\_APP.SBR"
	-@erase "$(INTDIR)\_APP_IM.OBJ"
	-@erase "$(INTDIR)\_APP_IM.SBR"
	-@erase "$(INTDIR)\_APPW_IM.OBJ"
	-@erase "$(INTDIR)\_APPW_IM.SBR"
	-@erase "$(INTDIR)\_APPWIND.OBJ"
	-@erase "$(INTDIR)\_APPWIND.SBR"
	-@erase "$(INTDIR)\_AUX1.OBJ"
	-@erase "$(INTDIR)\_AUX1.SBR"
	-@erase "$(INTDIR)\_AUX2.OBJ"
	-@erase "$(INTDIR)\_AUX2.SBR"
	-@erase "$(INTDIR)\_BITMAP.OBJ"
	-@erase "$(INTDIR)\_BITMAP.SBR"
	-@erase "$(INTDIR)\_BPRINT.OBJ"
	-@erase "$(INTDIR)\_BPRINT.SBR"
	-@erase "$(INTDIR)\_BRSH_IM.OBJ"
	-@erase "$(INTDIR)\_BRSH_IM.SBR"
	-@erase "$(INTDIR)\_BRUSH.OBJ"
	-@erase "$(INTDIR)\_BRUSH.SBR"
	-@erase "$(INTDIR)\_BTMP_IM.OBJ"
	-@erase "$(INTDIR)\_BTMP_IM.SBR"
	-@erase "$(INTDIR)\_CLIP_IM.OBJ"
	-@erase "$(INTDIR)\_CLIP_IM.SBR"
	-@erase "$(INTDIR)\_CLIPBRD.OBJ"
	-@erase "$(INTDIR)\_CLIPBRD.SBR"
	-@erase "$(INTDIR)\_CONTEXT.OBJ"
	-@erase "$(INTDIR)\_CONTEXT.SBR"
	-@erase "$(INTDIR)\_CONTROL.OBJ"
	-@erase "$(INTDIR)\_CONTROL.SBR"
	-@erase "$(INTDIR)\_CTLB_IM.OBJ"
	-@erase "$(INTDIR)\_CTLB_IM.SBR"
	-@erase "$(INTDIR)\_CUR_IM.OBJ"
	-@erase "$(INTDIR)\_CUR_IM.SBR"
	-@erase "$(INTDIR)\_CURSOR.OBJ"
	-@erase "$(INTDIR)\_CURSOR.SBR"
	-@erase "$(INTDIR)\_DCWD_IM.OBJ"
	-@erase "$(INTDIR)\_DCWD_IM.SBR"
	-@erase "$(INTDIR)\_DCWND.OBJ"
	-@erase "$(INTDIR)\_DCWND.SBR"
	-@erase "$(INTDIR)\_DEBUG.OBJ"
	-@erase "$(INTDIR)\_DEBUG.SBR"
	-@erase "$(INTDIR)\_DIALOG.OBJ"
	-@erase "$(INTDIR)\_DIALOG.SBR"
	-@erase "$(INTDIR)\_DISPATC.OBJ"
	-@erase "$(INTDIR)\_DISPATC.SBR"
	-@erase "$(INTDIR)\_DLG_IM.OBJ"
	-@erase "$(INTDIR)\_DLG_IM.SBR"
	-@erase "$(INTDIR)\_DRAWOBJ.OBJ"
	-@erase "$(INTDIR)\_DRAWOBJ.SBR"
	-@erase "$(INTDIR)\_EC_IM.OBJ"
	-@erase "$(INTDIR)\_EC_IM.SBR"
	-@erase "$(INTDIR)\_EDITWND.OBJ"
	-@erase "$(INTDIR)\_EDITWND.SBR"
	-@erase "$(INTDIR)\_EVENT.OBJ"
	-@erase "$(INTDIR)\_EVENT.SBR"
	-@erase "$(INTDIR)\_EWIN_IM.OBJ"
	-@erase "$(INTDIR)\_EWIN_IM.SBR"
	-@erase "$(INTDIR)\_FILELB.OBJ"
	-@erase "$(INTDIR)\_FILELB.SBR"
	-@erase "$(INTDIR)\_FLB_IM.OBJ"
	-@erase "$(INTDIR)\_FLB_IM.SBR"
	-@erase "$(INTDIR)\_FONT.OBJ"
	-@erase "$(INTDIR)\_FONT.SBR"
	-@erase "$(INTDIR)\_FONT_IM.OBJ"
	-@erase "$(INTDIR)\_FONT_IM.SBR"
	-@erase "$(INTDIR)\_HELP.OBJ"
	-@erase "$(INTDIR)\_HELP.SBR"
	-@erase "$(INTDIR)\_ICON.OBJ"
	-@erase "$(INTDIR)\_ICON.SBR"
	-@erase "$(INTDIR)\_ICON_IM.OBJ"
	-@erase "$(INTDIR)\_ICON_IM.SBR"
	-@erase "$(INTDIR)\_LINK.OBJ"
	-@erase "$(INTDIR)\_LINK.SBR"
	-@erase "$(INTDIR)\_MAIN.OBJ"
	-@erase "$(INTDIR)\_MAIN.SBR"
	-@erase "$(INTDIR)\_MDI.OBJ"
	-@erase "$(INTDIR)\_MDI.SBR"
	-@erase "$(INTDIR)\_MDI_IM.OBJ"
	-@erase "$(INTDIR)\_MDI_IM.SBR"
	-@erase "$(INTDIR)\_MENU.OBJ"
	-@erase "$(INTDIR)\_MENU.SBR"
	-@erase "$(INTDIR)\_MENU_IM.OBJ"
	-@erase "$(INTDIR)\_MENU_IM.SBR"
	-@erase "$(INTDIR)\_MESB_IM.OBJ"
	-@erase "$(INTDIR)\_MESB_IM.SBR"
	-@erase "$(INTDIR)\_MESSBOX.OBJ"
	-@erase "$(INTDIR)\_MESSBOX.SBR"
	-@erase "$(INTDIR)\_PEN.OBJ"
	-@erase "$(INTDIR)\_PEN.SBR"
	-@erase "$(INTDIR)\_PEN_IM.OBJ"
	-@erase "$(INTDIR)\_PEN_IM.SBR"
	-@erase "$(INTDIR)\_POIN_IM.OBJ"
	-@erase "$(INTDIR)\_POIN_IM.SBR"
	-@erase "$(INTDIR)\_POINTER.OBJ"
	-@erase "$(INTDIR)\_POINTER.SBR"
	-@erase "$(INTDIR)\_PRIN_IM.OBJ"
	-@erase "$(INTDIR)\_PRIN_IM.SBR"
	-@erase "$(INTDIR)\_PRINT.OBJ"
	-@erase "$(INTDIR)\_PRINT.SBR"
	-@erase "$(INTDIR)\_RECTANG.OBJ"
	-@erase "$(INTDIR)\_RECTANG.SBR"
	-@erase "$(INTDIR)\_RSTRING.OBJ"
	-@erase "$(INTDIR)\_RSTRING.SBR"
	-@erase "$(INTDIR)\_RUNTIME.OBJ"
	-@erase "$(INTDIR)\_RUNTIME.SBR"
	-@erase "$(INTDIR)\_SERVICE.OBJ"
	-@erase "$(INTDIR)\_SERVICE.SBR"
	-@erase "$(INTDIR)\_WIND_IM.OBJ"
	-@erase "$(INTDIR)\_WIND_IM.SBR"
	-@erase "$(INTDIR)\_WINDOW.OBJ"
	-@erase "$(INTDIR)\_WINDOW.SBR"
	-@erase "$(INTDIR)\animate.obj"
	-@erase "$(INTDIR)\animate.sbr"
	-@erase "$(INTDIR)\COLR31IM.OBJ"
	-@erase "$(INTDIR)\COLR31IM.SBR"
	-@erase "$(INTDIR)\Ctl3dw.obj"
	-@erase "$(INTDIR)\Ctl3dw.sbr"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.SBR"
	-@erase "$(INTDIR)\FILE31IM.OBJ"
	-@erase "$(INTDIR)\FILE31IM.SBR"
	-@erase "$(INTDIR)\imagectl.obj"
	-@erase "$(INTDIR)\imagectl.sbr"
	-@erase "$(INTDIR)\IMPPAGE.OBJ"
	-@erase "$(INTDIR)\IMPPAGE.SBR"
	-@erase "$(INTDIR)\IMPPSHET.OBJ"
	-@erase "$(INTDIR)\IMPPSHET.SBR"
	-@erase "$(INTDIR)\listview.obj"
	-@erase "$(INTDIR)\listview.sbr"
	-@erase "$(INTDIR)\notfyevt.obj"
	-@erase "$(INTDIR)\notfyevt.sbr"
	-@erase "$(INTDIR)\PROGBAR.obj"
	-@erase "$(INTDIR)\PROGBAR.sbr"
	-@erase "$(INTDIR)\PROPPAGE.OBJ"
	-@erase "$(INTDIR)\PROPPAGE.SBR"
	-@erase "$(INTDIR)\PROPSHET.OBJ"
	-@erase "$(INTDIR)\PROPSHET.SBR"
	-@erase "$(INTDIR)\statbar.obj"
	-@erase "$(INTDIR)\statbar.sbr"
	-@erase "$(INTDIR)\STDDLG.OBJ"
	-@erase "$(INTDIR)\STDDLG.SBR"
	-@erase "$(INTDIR)\Tfrm4.pch"
	-@erase "$(INTDIR)\TFRMPRE.OBJ"
	-@erase "$(INTDIR)\TFRMPRE.SBR"
	-@erase "$(INTDIR)\TFRMWORK.res"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\toolbar.sbr"
	-@erase "$(INTDIR)\tooltip.obj"
	-@erase "$(INTDIR)\tooltip.sbr"
	-@erase "$(INTDIR)\treelist.obj"
	-@erase "$(INTDIR)\treelist.sbr"
	-@erase "$(INTDIR)\updown.obj"
	-@erase "$(INTDIR)\updown.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\ZYZ3D.OBJ"
	-@erase "$(INTDIR)\ZYZ3D.SBR"
	-@erase "$(INTDIR)\ZYZGAUGE.OBJ"
	-@erase "$(INTDIR)\ZYZGAUGE.SBR"
	-@erase "$(OUTDIR)\TFRM32d.dll"
	-@erase "$(OUTDIR)\TFRM32d.exp"
	-@erase "$(OUTDIR)\TFRM32d.lib"
	-@erase "$(OUTDIR)\TFRM32d.pdb"
	-@erase "$(OUTDIR)\Tfrm4.bsc"
	-@erase "c:\trias\trias.deb\TFRM32d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TFRM32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr /Yu"tfrmpre.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug.207/
CPP_SBRS=.\Debug.207/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TFRMWORK.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tfrm4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\_ACCEL.SBR" \
	"$(INTDIR)\_ACCL_IM.SBR" \
	"$(INTDIR)\_APP.SBR" \
	"$(INTDIR)\_APP_IM.SBR" \
	"$(INTDIR)\_APPW_IM.SBR" \
	"$(INTDIR)\_APPWIND.SBR" \
	"$(INTDIR)\_AUX1.SBR" \
	"$(INTDIR)\_AUX2.SBR" \
	"$(INTDIR)\_BITMAP.SBR" \
	"$(INTDIR)\_BPRINT.SBR" \
	"$(INTDIR)\_BRSH_IM.SBR" \
	"$(INTDIR)\_BRUSH.SBR" \
	"$(INTDIR)\_BTMP_IM.SBR" \
	"$(INTDIR)\_CLIP_IM.SBR" \
	"$(INTDIR)\_CLIPBRD.SBR" \
	"$(INTDIR)\_CONTEXT.SBR" \
	"$(INTDIR)\_CONTROL.SBR" \
	"$(INTDIR)\_CTLB_IM.SBR" \
	"$(INTDIR)\_CUR_IM.SBR" \
	"$(INTDIR)\_CURSOR.SBR" \
	"$(INTDIR)\_DCWD_IM.SBR" \
	"$(INTDIR)\_DCWND.SBR" \
	"$(INTDIR)\_DEBUG.SBR" \
	"$(INTDIR)\_DIALOG.SBR" \
	"$(INTDIR)\_DISPATC.SBR" \
	"$(INTDIR)\_DLG_IM.SBR" \
	"$(INTDIR)\_DRAWOBJ.SBR" \
	"$(INTDIR)\_EC_IM.SBR" \
	"$(INTDIR)\_EDITWND.SBR" \
	"$(INTDIR)\_EVENT.SBR" \
	"$(INTDIR)\_EWIN_IM.SBR" \
	"$(INTDIR)\_FILELB.SBR" \
	"$(INTDIR)\_FLB_IM.SBR" \
	"$(INTDIR)\_FONT.SBR" \
	"$(INTDIR)\_FONT_IM.SBR" \
	"$(INTDIR)\_HELP.SBR" \
	"$(INTDIR)\_ICON.SBR" \
	"$(INTDIR)\_ICON_IM.SBR" \
	"$(INTDIR)\_LINK.SBR" \
	"$(INTDIR)\_MAIN.SBR" \
	"$(INTDIR)\_MDI.SBR" \
	"$(INTDIR)\_MDI_IM.SBR" \
	"$(INTDIR)\_MENU.SBR" \
	"$(INTDIR)\_MENU_IM.SBR" \
	"$(INTDIR)\_MESB_IM.SBR" \
	"$(INTDIR)\_MESSBOX.SBR" \
	"$(INTDIR)\_PEN.SBR" \
	"$(INTDIR)\_PEN_IM.SBR" \
	"$(INTDIR)\_POIN_IM.SBR" \
	"$(INTDIR)\_POINTER.SBR" \
	"$(INTDIR)\_PRIN_IM.SBR" \
	"$(INTDIR)\_PRINT.SBR" \
	"$(INTDIR)\_RECTANG.SBR" \
	"$(INTDIR)\_RSTRING.SBR" \
	"$(INTDIR)\_RUNTIME.SBR" \
	"$(INTDIR)\_SERVICE.SBR" \
	"$(INTDIR)\_WIND_IM.SBR" \
	"$(INTDIR)\_WINDOW.SBR" \
	"$(INTDIR)\animate.sbr" \
	"$(INTDIR)\COLR31IM.SBR" \
	"$(INTDIR)\Ctl3dw.sbr" \
	"$(INTDIR)\DRAWRECT.SBR" \
	"$(INTDIR)\FILE31IM.SBR" \
	"$(INTDIR)\imagectl.sbr" \
	"$(INTDIR)\IMPPAGE.SBR" \
	"$(INTDIR)\IMPPSHET.SBR" \
	"$(INTDIR)\listview.sbr" \
	"$(INTDIR)\notfyevt.sbr" \
	"$(INTDIR)\PROGBAR.sbr" \
	"$(INTDIR)\PROPPAGE.SBR" \
	"$(INTDIR)\PROPSHET.SBR" \
	"$(INTDIR)\statbar.sbr" \
	"$(INTDIR)\STDDLG.SBR" \
	"$(INTDIR)\TFRMPRE.SBR" \
	"$(INTDIR)\toolbar.sbr" \
	"$(INTDIR)\tooltip.sbr" \
	"$(INTDIR)\treelist.sbr" \
	"$(INTDIR)\updown.sbr" \
	"$(INTDIR)\ZYZ3D.SBR" \
	"$(INTDIR)\ZYZGAUGE.SBR"

"$(OUTDIR)\Tfrm4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 stdcppd.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /debugtype:both /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug.207/TFRM32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=stdcppd.lib comctl32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/TFRM32d.pdb" /debug /debugtype:both /machine:I386\
 /nodefaultlib:"libcmtd.lib" /def:".\TFRM32D.DEF" /out:"$(OUTDIR)/TFRM32d.dll"\
 /implib:"$(OUTDIR)/TFRM32d.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\TFRM32D.DEF"
LINK32_OBJS= \
	"$(INTDIR)\_ACCEL.OBJ" \
	"$(INTDIR)\_ACCL_IM.OBJ" \
	"$(INTDIR)\_APP.OBJ" \
	"$(INTDIR)\_APP_IM.OBJ" \
	"$(INTDIR)\_APPW_IM.OBJ" \
	"$(INTDIR)\_APPWIND.OBJ" \
	"$(INTDIR)\_AUX1.OBJ" \
	"$(INTDIR)\_AUX2.OBJ" \
	"$(INTDIR)\_BITMAP.OBJ" \
	"$(INTDIR)\_BPRINT.OBJ" \
	"$(INTDIR)\_BRSH_IM.OBJ" \
	"$(INTDIR)\_BRUSH.OBJ" \
	"$(INTDIR)\_BTMP_IM.OBJ" \
	"$(INTDIR)\_CLIP_IM.OBJ" \
	"$(INTDIR)\_CLIPBRD.OBJ" \
	"$(INTDIR)\_CONTEXT.OBJ" \
	"$(INTDIR)\_CONTROL.OBJ" \
	"$(INTDIR)\_CTLB_IM.OBJ" \
	"$(INTDIR)\_CUR_IM.OBJ" \
	"$(INTDIR)\_CURSOR.OBJ" \
	"$(INTDIR)\_DCWD_IM.OBJ" \
	"$(INTDIR)\_DCWND.OBJ" \
	"$(INTDIR)\_DEBUG.OBJ" \
	"$(INTDIR)\_DIALOG.OBJ" \
	"$(INTDIR)\_DISPATC.OBJ" \
	"$(INTDIR)\_DLG_IM.OBJ" \
	"$(INTDIR)\_DRAWOBJ.OBJ" \
	"$(INTDIR)\_EC_IM.OBJ" \
	"$(INTDIR)\_EDITWND.OBJ" \
	"$(INTDIR)\_EVENT.OBJ" \
	"$(INTDIR)\_EWIN_IM.OBJ" \
	"$(INTDIR)\_FILELB.OBJ" \
	"$(INTDIR)\_FLB_IM.OBJ" \
	"$(INTDIR)\_FONT.OBJ" \
	"$(INTDIR)\_FONT_IM.OBJ" \
	"$(INTDIR)\_HELP.OBJ" \
	"$(INTDIR)\_ICON.OBJ" \
	"$(INTDIR)\_ICON_IM.OBJ" \
	"$(INTDIR)\_LINK.OBJ" \
	"$(INTDIR)\_MAIN.OBJ" \
	"$(INTDIR)\_MDI.OBJ" \
	"$(INTDIR)\_MDI_IM.OBJ" \
	"$(INTDIR)\_MENU.OBJ" \
	"$(INTDIR)\_MENU_IM.OBJ" \
	"$(INTDIR)\_MESB_IM.OBJ" \
	"$(INTDIR)\_MESSBOX.OBJ" \
	"$(INTDIR)\_PEN.OBJ" \
	"$(INTDIR)\_PEN_IM.OBJ" \
	"$(INTDIR)\_POIN_IM.OBJ" \
	"$(INTDIR)\_POINTER.OBJ" \
	"$(INTDIR)\_PRIN_IM.OBJ" \
	"$(INTDIR)\_PRINT.OBJ" \
	"$(INTDIR)\_RECTANG.OBJ" \
	"$(INTDIR)\_RSTRING.OBJ" \
	"$(INTDIR)\_RUNTIME.OBJ" \
	"$(INTDIR)\_SERVICE.OBJ" \
	"$(INTDIR)\_WIND_IM.OBJ" \
	"$(INTDIR)\_WINDOW.OBJ" \
	"$(INTDIR)\animate.obj" \
	"$(INTDIR)\COLR31IM.OBJ" \
	"$(INTDIR)\Ctl3dw.obj" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\FILE31IM.OBJ" \
	"$(INTDIR)\imagectl.obj" \
	"$(INTDIR)\IMPPAGE.OBJ" \
	"$(INTDIR)\IMPPSHET.OBJ" \
	"$(INTDIR)\listview.obj" \
	"$(INTDIR)\notfyevt.obj" \
	"$(INTDIR)\PROGBAR.obj" \
	"$(INTDIR)\PROPPAGE.OBJ" \
	"$(INTDIR)\PROPSHET.OBJ" \
	"$(INTDIR)\statbar.obj" \
	"$(INTDIR)\STDDLG.OBJ" \
	"$(INTDIR)\TFRMPRE.OBJ" \
	"$(INTDIR)\TFRMWORK.res" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\tooltip.obj" \
	"$(INTDIR)\treelist.obj" \
	"$(INTDIR)\updown.obj" \
	"$(INTDIR)\ZYZ3D.OBJ" \
	"$(INTDIR)\ZYZGAUGE.OBJ"

"$(OUTDIR)\TFRM32d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug.207
TargetPath=.\Debug.207\TFRM32d.dll
TargetName=TFRM32d
InputPath=.\Debug.207\TFRM32d.dll
SOURCE=$(InputPath)

"c:\trias\trias.deb\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F "$(TargetPath)" c:\trias\trias.deb
   xcopy /F "$(OutDir)\$(TargetName).pdb" c:\trias\trias.deb
   xcopy /F "$(OutDir)\$(TargetName).lib" c:\trias\lib
   xcopy /F "$(OutDir)\$(TargetName).pdb" c:\trias\lib

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

# Name "Tfrm32 - Win32 Framework DLL Release"
# Name "Tfrm32 - Win32 Framework DLL Debug"

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\_BITMAP.CXX
DEP_CPP__BITM=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_BITMAP.OBJ" : $(SOURCE) $(DEP_CPP__BITM) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BITMAP.SBR" : $(SOURCE) $(DEP_CPP__BITM) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_BITMAP.OBJ" : $(SOURCE) $(DEP_CPP__BITM) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BITMAP.SBR" : $(SOURCE) $(DEP_CPP__BITM) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CURSOR.CXX
DEP_CPP__CURS=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CURSOR.OBJ" : $(SOURCE) $(DEP_CPP__CURS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CURSOR.SBR" : $(SOURCE) $(DEP_CPP__CURS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CURSOR.OBJ" : $(SOURCE) $(DEP_CPP__CURS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CURSOR.SBR" : $(SOURCE) $(DEP_CPP__CURS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CONTEXT.CXX
DEP_CPP__CONT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CONTEXT.OBJ" : $(SOURCE) $(DEP_CPP__CONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CONTEXT.SBR" : $(SOURCE) $(DEP_CPP__CONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CONTEXT.OBJ" : $(SOURCE) $(DEP_CPP__CONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CONTEXT.SBR" : $(SOURCE) $(DEP_CPP__CONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_BPRINT.CXX
DEP_CPP__BPRI=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_BPRINT.OBJ" : $(SOURCE) $(DEP_CPP__BPRI) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BPRINT.SBR" : $(SOURCE) $(DEP_CPP__BPRI) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_BPRINT.OBJ" : $(SOURCE) $(DEP_CPP__BPRI) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BPRINT.SBR" : $(SOURCE) $(DEP_CPP__BPRI) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_RUNTIME.CXX
DEP_CPP__RUNT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_RUNTIME.OBJ" : $(SOURCE) $(DEP_CPP__RUNT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RUNTIME.SBR" : $(SOURCE) $(DEP_CPP__RUNT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_RUNTIME.OBJ" : $(SOURCE) $(DEP_CPP__RUNT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RUNTIME.SBR" : $(SOURCE) $(DEP_CPP__RUNT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDDLG.CXX
DEP_CPP_STDDL=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\stddlg.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\WIN31IMP.HXX"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDDLG.OBJ" : $(SOURCE) $(DEP_CPP_STDDL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\STDDLG.SBR" : $(SOURCE) $(DEP_CPP_STDDL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\STDDLG.OBJ" : $(SOURCE) $(DEP_CPP_STDDL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\STDDLG.SBR" : $(SOURCE) $(DEP_CPP_STDDL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_WINDOW.CXX
DEP_CPP__WIND=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_WINDOW.OBJ" : $(SOURCE) $(DEP_CPP__WIND) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_WINDOW.SBR" : $(SOURCE) $(DEP_CPP__WIND) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_WINDOW.OBJ" : $(SOURCE) $(DEP_CPP__WIND) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_WINDOW.SBR" : $(SOURCE) $(DEP_CPP__WIND) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DEBUG.CXX
DEP_CPP__DEBU=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DEBUG.OBJ" : $(SOURCE) $(DEP_CPP__DEBU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DEBUG.SBR" : $(SOURCE) $(DEP_CPP__DEBU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DEBUG.OBJ" : $(SOURCE) $(DEP_CPP__DEBU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DEBUG.SBR" : $(SOURCE) $(DEP_CPP__DEBU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_EVENT.CXX
DEP_CPP__EVEN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_EVENT.OBJ" : $(SOURCE) $(DEP_CPP__EVEN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EVENT.SBR" : $(SOURCE) $(DEP_CPP__EVEN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_EVENT.OBJ" : $(SOURCE) $(DEP_CPP__EVEN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EVENT.SBR" : $(SOURCE) $(DEP_CPP__EVEN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_SERVICE.CXX
DEP_CPP__SERV=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_SERVICE.OBJ" : $(SOURCE) $(DEP_CPP__SERV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_SERVICE.SBR" : $(SOURCE) $(DEP_CPP__SERV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_SERVICE.OBJ" : $(SOURCE) $(DEP_CPP__SERV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_SERVICE.SBR" : $(SOURCE) $(DEP_CPP__SERV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MDI.CXX
DEP_CPP__MDI_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MDI.OBJ" : $(SOURCE) $(DEP_CPP__MDI_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MDI.SBR" : $(SOURCE) $(DEP_CPP__MDI_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MDI.OBJ" : $(SOURCE) $(DEP_CPP__MDI_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MDI.SBR" : $(SOURCE) $(DEP_CPP__MDI_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_APP.CXX
DEP_CPP__APP_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_APP.OBJ" : $(SOURCE) $(DEP_CPP__APP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APP.SBR" : $(SOURCE) $(DEP_CPP__APP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_APP.OBJ" : $(SOURCE) $(DEP_CPP__APP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APP.SBR" : $(SOURCE) $(DEP_CPP__APP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_LINK.CXX
DEP_CPP__LINK=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_LINK.OBJ" : $(SOURCE) $(DEP_CPP__LINK) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_LINK.SBR" : $(SOURCE) $(DEP_CPP__LINK) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_LINK.OBJ" : $(SOURCE) $(DEP_CPP__LINK) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_LINK.SBR" : $(SOURCE) $(DEP_CPP__LINK) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_FONT.CXX
DEP_CPP__FONT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_FONT.OBJ" : $(SOURCE) $(DEP_CPP__FONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FONT.SBR" : $(SOURCE) $(DEP_CPP__FONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_FONT.OBJ" : $(SOURCE) $(DEP_CPP__FONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FONT.SBR" : $(SOURCE) $(DEP_CPP__FONT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_POINTER.CXX
DEP_CPP__POIN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_POINTER.OBJ" : $(SOURCE) $(DEP_CPP__POIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_POINTER.SBR" : $(SOURCE) $(DEP_CPP__POIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_POINTER.OBJ" : $(SOURCE) $(DEP_CPP__POIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_POINTER.SBR" : $(SOURCE) $(DEP_CPP__POIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_PRINT.CXX
DEP_CPP__PRIN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_PRINT.OBJ" : $(SOURCE) $(DEP_CPP__PRIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PRINT.SBR" : $(SOURCE) $(DEP_CPP__PRIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_PRINT.OBJ" : $(SOURCE) $(DEP_CPP__PRIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PRINT.SBR" : $(SOURCE) $(DEP_CPP__PRIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MENU.CXX
DEP_CPP__MENU=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MENU.OBJ" : $(SOURCE) $(DEP_CPP__MENU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MENU.SBR" : $(SOURCE) $(DEP_CPP__MENU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MENU.OBJ" : $(SOURCE) $(DEP_CPP__MENU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MENU.SBR" : $(SOURCE) $(DEP_CPP__MENU) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MAIN.CXX
DEP_CPP__MAIN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MAIN.OBJ" : $(SOURCE) $(DEP_CPP__MAIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MAIN.SBR" : $(SOURCE) $(DEP_CPP__MAIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MAIN.OBJ" : $(SOURCE) $(DEP_CPP__MAIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MAIN.SBR" : $(SOURCE) $(DEP_CPP__MAIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_RSTRING.CXX
DEP_CPP__RSTR=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_RSTRING.OBJ" : $(SOURCE) $(DEP_CPP__RSTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RSTRING.SBR" : $(SOURCE) $(DEP_CPP__RSTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_RSTRING.OBJ" : $(SOURCE) $(DEP_CPP__RSTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RSTRING.SBR" : $(SOURCE) $(DEP_CPP__RSTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DISPATC.CXX
DEP_CPP__DISP=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DISPATC.OBJ" : $(SOURCE) $(DEP_CPP__DISP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DISPATC.SBR" : $(SOURCE) $(DEP_CPP__DISP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DISPATC.OBJ" : $(SOURCE) $(DEP_CPP__DISP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DISPATC.SBR" : $(SOURCE) $(DEP_CPP__DISP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DCWND.CXX
DEP_CPP__DCWN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DCWND.OBJ" : $(SOURCE) $(DEP_CPP__DCWN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DCWND.SBR" : $(SOURCE) $(DEP_CPP__DCWN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DCWND.OBJ" : $(SOURCE) $(DEP_CPP__DCWN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DCWND.SBR" : $(SOURCE) $(DEP_CPP__DCWN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CLIPBRD.CXX
DEP_CPP__CLIP=\
	".\Clipdef.h"\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CLIP_IM.HXX"\
	{$(INCLUDE)}"\Clipbrd.hxx"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CLIPBRD.OBJ" : $(SOURCE) $(DEP_CPP__CLIP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CLIPBRD.SBR" : $(SOURCE) $(DEP_CPP__CLIP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CLIPBRD.OBJ" : $(SOURCE) $(DEP_CPP__CLIP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CLIPBRD.SBR" : $(SOURCE) $(DEP_CPP__CLIP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DIALOG.CXX
DEP_CPP__DIAL=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DIALOG.OBJ" : $(SOURCE) $(DEP_CPP__DIAL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DIALOG.SBR" : $(SOURCE) $(DEP_CPP__DIAL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DIALOG.OBJ" : $(SOURCE) $(DEP_CPP__DIAL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DIALOG.SBR" : $(SOURCE) $(DEP_CPP__DIAL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MESSBOX.CXX
DEP_CPP__MESS=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MESSBOX.OBJ" : $(SOURCE) $(DEP_CPP__MESS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MESSBOX.SBR" : $(SOURCE) $(DEP_CPP__MESS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MESSBOX.OBJ" : $(SOURCE) $(DEP_CPP__MESS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MESSBOX.SBR" : $(SOURCE) $(DEP_CPP__MESS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_HELP.CXX
DEP_CPP__HELP=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_HELP.OBJ" : $(SOURCE) $(DEP_CPP__HELP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_HELP.SBR" : $(SOURCE) $(DEP_CPP__HELP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_HELP.OBJ" : $(SOURCE) $(DEP_CPP__HELP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_HELP.SBR" : $(SOURCE) $(DEP_CPP__HELP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DRAWOBJ.CXX
DEP_CPP__DRAW=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\DrawObj.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DRAWOBJ.OBJ" : $(SOURCE) $(DEP_CPP__DRAW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DRAWOBJ.SBR" : $(SOURCE) $(DEP_CPP__DRAW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DRAWOBJ.OBJ" : $(SOURCE) $(DEP_CPP__DRAW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DRAWOBJ.SBR" : $(SOURCE) $(DEP_CPP__DRAW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_AUX2.CXX
DEP_CPP__AUX2=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	{$(INCLUDE)}"\ZYZGAUGE.H"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_AUX2.OBJ" : $(SOURCE) $(DEP_CPP__AUX2) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_AUX2.SBR" : $(SOURCE) $(DEP_CPP__AUX2) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_AUX2.OBJ" : $(SOURCE) $(DEP_CPP__AUX2) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_AUX2.SBR" : $(SOURCE) $(DEP_CPP__AUX2) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_AUX1.CXX
DEP_CPP__AUX1=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_AUX1.OBJ" : $(SOURCE) $(DEP_CPP__AUX1) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_AUX1.SBR" : $(SOURCE) $(DEP_CPP__AUX1) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_AUX1.OBJ" : $(SOURCE) $(DEP_CPP__AUX1) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_AUX1.SBR" : $(SOURCE) $(DEP_CPP__AUX1) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_APPWIND.CXX
DEP_CPP__APPW=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_APPWIND.OBJ" : $(SOURCE) $(DEP_CPP__APPW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APPWIND.SBR" : $(SOURCE) $(DEP_CPP__APPW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_APPWIND.OBJ" : $(SOURCE) $(DEP_CPP__APPW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APPWIND.SBR" : $(SOURCE) $(DEP_CPP__APPW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_EDITWND.CXX
DEP_CPP__EDIT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_EDITWND.OBJ" : $(SOURCE) $(DEP_CPP__EDIT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EDITWND.SBR" : $(SOURCE) $(DEP_CPP__EDIT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_EDITWND.OBJ" : $(SOURCE) $(DEP_CPP__EDIT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EDITWND.SBR" : $(SOURCE) $(DEP_CPP__EDIT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_FILELB.CXX
DEP_CPP__FILE=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_FILELB.OBJ" : $(SOURCE) $(DEP_CPP__FILE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FILELB.SBR" : $(SOURCE) $(DEP_CPP__FILE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_FILELB.OBJ" : $(SOURCE) $(DEP_CPP__FILE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FILELB.SBR" : $(SOURCE) $(DEP_CPP__FILE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_PEN.CXX
DEP_CPP__PEN_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_PEN.OBJ" : $(SOURCE) $(DEP_CPP__PEN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PEN.SBR" : $(SOURCE) $(DEP_CPP__PEN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_PEN.OBJ" : $(SOURCE) $(DEP_CPP__PEN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PEN.SBR" : $(SOURCE) $(DEP_CPP__PEN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CONTROL.CXX
DEP_CPP__CONTR=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CONTROL.OBJ" : $(SOURCE) $(DEP_CPP__CONTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CONTROL.SBR" : $(SOURCE) $(DEP_CPP__CONTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CONTROL.OBJ" : $(SOURCE) $(DEP_CPP__CONTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CONTROL.SBR" : $(SOURCE) $(DEP_CPP__CONTR) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_ACCEL.CXX
DEP_CPP__ACCE=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_ACCEL.OBJ" : $(SOURCE) $(DEP_CPP__ACCE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ACCEL.SBR" : $(SOURCE) $(DEP_CPP__ACCE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_ACCEL.OBJ" : $(SOURCE) $(DEP_CPP__ACCE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ACCEL.SBR" : $(SOURCE) $(DEP_CPP__ACCE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_BRUSH.CXX
DEP_CPP__BRUS=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_BRUSH.OBJ" : $(SOURCE) $(DEP_CPP__BRUS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BRUSH.SBR" : $(SOURCE) $(DEP_CPP__BRUS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_BRUSH.OBJ" : $(SOURCE) $(DEP_CPP__BRUS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BRUSH.SBR" : $(SOURCE) $(DEP_CPP__BRUS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_RECTANG.CXX
DEP_CPP__RECT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_RECTANG.OBJ" : $(SOURCE) $(DEP_CPP__RECT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RECTANG.SBR" : $(SOURCE) $(DEP_CPP__RECT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_RECTANG.OBJ" : $(SOURCE) $(DEP_CPP__RECT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_RECTANG.SBR" : $(SOURCE) $(DEP_CPP__RECT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_ICON.CXX
DEP_CPP__ICON=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_ICON.OBJ" : $(SOURCE) $(DEP_CPP__ICON) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ICON.SBR" : $(SOURCE) $(DEP_CPP__ICON) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_ICON.OBJ" : $(SOURCE) $(DEP_CPP__ICON) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ICON.SBR" : $(SOURCE) $(DEP_CPP__ICON) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZYZGAUGE.CXX
DEP_CPP_ZYZGA=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	{$(INCLUDE)}"\ZYZ3D.H"\
	{$(INCLUDE)}"\ZYZGAUGE.H"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\ZYZGAUGE.OBJ" : $(SOURCE) $(DEP_CPP_ZYZGA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\ZYZGAUGE.SBR" : $(SOURCE) $(DEP_CPP_ZYZGA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\ZYZGAUGE.OBJ" : $(SOURCE) $(DEP_CPP_ZYZGA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\ZYZGAUGE.SBR" : $(SOURCE) $(DEP_CPP_ZYZGA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZYZ3D.CXX
DEP_CPP_ZYZ3D=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	{$(INCLUDE)}"\ZYZ3D.H"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\ZYZ3D.OBJ" : $(SOURCE) $(DEP_CPP_ZYZ3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\ZYZ3D.SBR" : $(SOURCE) $(DEP_CPP_ZYZ3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\ZYZ3D.OBJ" : $(SOURCE) $(DEP_CPP_ZYZ3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\ZYZ3D.SBR" : $(SOURCE) $(DEP_CPP_ZYZ3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAWRECT.CXX
DEP_CPP_DRAWR=\
	{$(INCLUDE)}"\bool.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# SUBTRACT CPP /Yu

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) $(DEP_CPP_DRAWR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DRAWRECT.SBR" : $(SOURCE) $(DEP_CPP_DRAWR) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# SUBTRACT CPP /YX /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) $(DEP_CPP_DRAWR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DRAWRECT.SBR" : $(SOURCE) $(DEP_CPP_DRAWR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROPSHET.CXX
DEP_CPP_PROPS=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"


BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PROPSHET.OBJ" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\PROPSHET.SBR" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PROPSHET.OBJ" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\PROPSHET.SBR" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROPPAGE.CXX
DEP_CPP_PROPP=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"


BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PROPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\PROPPAGE.SBR" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PROPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\PROPPAGE.SBR" : $(SOURCE) $(DEP_CPP_PROPP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\imagectl.cxx
DEP_CPP_IMAGE=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\imagectl.obj" : $(SOURCE) $(DEP_CPP_IMAGE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\imagectl.sbr" : $(SOURCE) $(DEP_CPP_IMAGE) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\treelist.cxx
DEP_CPP_TREEL=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\treelist.obj" : $(SOURCE) $(DEP_CPP_TREEL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\treelist.sbr" : $(SOURCE) $(DEP_CPP_TREEL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\notfyevt.cxx
DEP_CPP_NOTFY=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\notfyevt.obj" : $(SOURCE) $(DEP_CPP_NOTFY) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\notfyevt.sbr" : $(SOURCE) $(DEP_CPP_NOTFY) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\listview.cxx
DEP_CPP_LISTV=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\listview.obj" : $(SOURCE) $(DEP_CPP_LISTV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\listview.sbr" : $(SOURCE) $(DEP_CPP_LISTV) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\toolbar.cxx
DEP_CPP_TOOLB=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\toolbar.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\toolbar.sbr" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\statbar.cxx
DEP_CPP_STATB=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\statbar.obj" : $(SOURCE) $(DEP_CPP_STATB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\statbar.sbr" : $(SOURCE) $(DEP_CPP_STATB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROGBAR.cxx
DEP_CPP_PROGB=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\PROGBAR.obj" : $(SOURCE) $(DEP_CPP_PROGB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\PROGBAR.sbr" : $(SOURCE) $(DEP_CPP_PROGB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\updown.cxx
DEP_CPP_UPDOW=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\updown.obj" : $(SOURCE) $(DEP_CPP_UPDOW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\updown.sbr" : $(SOURCE) $(DEP_CPP_UPDOW) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tooltip.cxx
DEP_CPP_TOOLT=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\tooltip.obj" : $(SOURCE) $(DEP_CPP_TOOLT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\tooltip.sbr" : $(SOURCE) $(DEP_CPP_TOOLT) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\_ACCL_IM.CXX
DEP_CPP__ACCL=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_ACCL_IM.OBJ" : $(SOURCE) $(DEP_CPP__ACCL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ACCL_IM.SBR" : $(SOURCE) $(DEP_CPP__ACCL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_ACCL_IM.OBJ" : $(SOURCE) $(DEP_CPP__ACCL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ACCL_IM.SBR" : $(SOURCE) $(DEP_CPP__ACCL) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_APP_IM.CXX
DEP_CPP__APP_I=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_APP_IM.OBJ" : $(SOURCE) $(DEP_CPP__APP_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APP_IM.SBR" : $(SOURCE) $(DEP_CPP__APP_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_APP_IM.OBJ" : $(SOURCE) $(DEP_CPP__APP_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APP_IM.SBR" : $(SOURCE) $(DEP_CPP__APP_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_APPW_IM.CXX
DEP_CPP__APPW_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_APPW_IM.OBJ" : $(SOURCE) $(DEP_CPP__APPW_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APPW_IM.SBR" : $(SOURCE) $(DEP_CPP__APPW_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_APPW_IM.OBJ" : $(SOURCE) $(DEP_CPP__APPW_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_APPW_IM.SBR" : $(SOURCE) $(DEP_CPP__APPW_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_BRSH_IM.CXX
DEP_CPP__BRSH=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_BRSH_IM.OBJ" : $(SOURCE) $(DEP_CPP__BRSH) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BRSH_IM.SBR" : $(SOURCE) $(DEP_CPP__BRSH) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_BRSH_IM.OBJ" : $(SOURCE) $(DEP_CPP__BRSH) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BRSH_IM.SBR" : $(SOURCE) $(DEP_CPP__BRSH) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_BTMP_IM.CXX
DEP_CPP__BTMP=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_BTMP_IM.OBJ" : $(SOURCE) $(DEP_CPP__BTMP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BTMP_IM.SBR" : $(SOURCE) $(DEP_CPP__BTMP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_BTMP_IM.OBJ" : $(SOURCE) $(DEP_CPP__BTMP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_BTMP_IM.SBR" : $(SOURCE) $(DEP_CPP__BTMP) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CLIP_IM.CXX
DEP_CPP__CLIP_=\
	".\Clipdef.h"\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CLIP_IM.HXX"\
	{$(INCLUDE)}"\Clipbrd.hxx"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CLIP_IM.OBJ" : $(SOURCE) $(DEP_CPP__CLIP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CLIP_IM.SBR" : $(SOURCE) $(DEP_CPP__CLIP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CLIP_IM.OBJ" : $(SOURCE) $(DEP_CPP__CLIP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CLIP_IM.SBR" : $(SOURCE) $(DEP_CPP__CLIP_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CTLB_IM.CXX
DEP_CPP__CTLB=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	{$(INCLUDE)}"\ZYZGAUGE.H"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CTLB_IM.OBJ" : $(SOURCE) $(DEP_CPP__CTLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CTLB_IM.SBR" : $(SOURCE) $(DEP_CPP__CTLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CTLB_IM.OBJ" : $(SOURCE) $(DEP_CPP__CTLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CTLB_IM.SBR" : $(SOURCE) $(DEP_CPP__CTLB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_CUR_IM.CXX
DEP_CPP__CUR_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_CUR_IM.OBJ" : $(SOURCE) $(DEP_CPP__CUR_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CUR_IM.SBR" : $(SOURCE) $(DEP_CPP__CUR_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_CUR_IM.OBJ" : $(SOURCE) $(DEP_CPP__CUR_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_CUR_IM.SBR" : $(SOURCE) $(DEP_CPP__CUR_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DCWD_IM.CXX
DEP_CPP__DCWD=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DCWD_IM.OBJ" : $(SOURCE) $(DEP_CPP__DCWD) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DCWD_IM.SBR" : $(SOURCE) $(DEP_CPP__DCWD) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DCWD_IM.OBJ" : $(SOURCE) $(DEP_CPP__DCWD) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DCWD_IM.SBR" : $(SOURCE) $(DEP_CPP__DCWD) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_DLG_IM.CXX
DEP_CPP__DLG_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_DLG_IM.OBJ" : $(SOURCE) $(DEP_CPP__DLG_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DLG_IM.SBR" : $(SOURCE) $(DEP_CPP__DLG_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_DLG_IM.OBJ" : $(SOURCE) $(DEP_CPP__DLG_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_DLG_IM.SBR" : $(SOURCE) $(DEP_CPP__DLG_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_EC_IM.CXX
DEP_CPP__EC_I=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_EC_IM.OBJ" : $(SOURCE) $(DEP_CPP__EC_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EC_IM.SBR" : $(SOURCE) $(DEP_CPP__EC_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_EC_IM.OBJ" : $(SOURCE) $(DEP_CPP__EC_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EC_IM.SBR" : $(SOURCE) $(DEP_CPP__EC_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_EWIN_IM.CXX
DEP_CPP__EWIN=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_EWIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__EWIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EWIN_IM.SBR" : $(SOURCE) $(DEP_CPP__EWIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_EWIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__EWIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_EWIN_IM.SBR" : $(SOURCE) $(DEP_CPP__EWIN) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_FLB_IM.CXX
DEP_CPP__FLB_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_FLB_IM.OBJ" : $(SOURCE) $(DEP_CPP__FLB_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FLB_IM.SBR" : $(SOURCE) $(DEP_CPP__FLB_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_FLB_IM.OBJ" : $(SOURCE) $(DEP_CPP__FLB_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FLB_IM.SBR" : $(SOURCE) $(DEP_CPP__FLB_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_FONT_IM.CXX
DEP_CPP__FONT_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_FONT_IM.OBJ" : $(SOURCE) $(DEP_CPP__FONT_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FONT_IM.SBR" : $(SOURCE) $(DEP_CPP__FONT_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_FONT_IM.OBJ" : $(SOURCE) $(DEP_CPP__FONT_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_FONT_IM.SBR" : $(SOURCE) $(DEP_CPP__FONT_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_ICON_IM.CXX
DEP_CPP__ICON_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_ICON_IM.OBJ" : $(SOURCE) $(DEP_CPP__ICON_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ICON_IM.SBR" : $(SOURCE) $(DEP_CPP__ICON_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_ICON_IM.OBJ" : $(SOURCE) $(DEP_CPP__ICON_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_ICON_IM.SBR" : $(SOURCE) $(DEP_CPP__ICON_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MDI_IM.CXX
DEP_CPP__MDI_I=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MDI_IM.OBJ" : $(SOURCE) $(DEP_CPP__MDI_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MDI_IM.SBR" : $(SOURCE) $(DEP_CPP__MDI_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MDI_IM.OBJ" : $(SOURCE) $(DEP_CPP__MDI_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MDI_IM.SBR" : $(SOURCE) $(DEP_CPP__MDI_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MENU_IM.CXX
DEP_CPP__MENU_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MENU_IM.OBJ" : $(SOURCE) $(DEP_CPP__MENU_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MENU_IM.SBR" : $(SOURCE) $(DEP_CPP__MENU_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MENU_IM.OBJ" : $(SOURCE) $(DEP_CPP__MENU_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MENU_IM.SBR" : $(SOURCE) $(DEP_CPP__MENU_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_MESB_IM.CXX
DEP_CPP__MESB=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_MESB_IM.OBJ" : $(SOURCE) $(DEP_CPP__MESB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MESB_IM.SBR" : $(SOURCE) $(DEP_CPP__MESB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_MESB_IM.OBJ" : $(SOURCE) $(DEP_CPP__MESB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_MESB_IM.SBR" : $(SOURCE) $(DEP_CPP__MESB) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_PEN_IM.CXX
DEP_CPP__PEN_I=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_PEN_IM.OBJ" : $(SOURCE) $(DEP_CPP__PEN_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PEN_IM.SBR" : $(SOURCE) $(DEP_CPP__PEN_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_PEN_IM.OBJ" : $(SOURCE) $(DEP_CPP__PEN_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PEN_IM.SBR" : $(SOURCE) $(DEP_CPP__PEN_I) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_POIN_IM.CXX
DEP_CPP__POIN_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_POIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__POIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_POIN_IM.SBR" : $(SOURCE) $(DEP_CPP__POIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_POIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__POIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_POIN_IM.SBR" : $(SOURCE) $(DEP_CPP__POIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_PRIN_IM.CXX
DEP_CPP__PRIN_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_PRIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__PRIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PRIN_IM.SBR" : $(SOURCE) $(DEP_CPP__PRIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_PRIN_IM.OBJ" : $(SOURCE) $(DEP_CPP__PRIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_PRIN_IM.SBR" : $(SOURCE) $(DEP_CPP__PRIN_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\_WIND_IM.CXX
DEP_CPP__WIND_=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\_WIND_IM.OBJ" : $(SOURCE) $(DEP_CPP__WIND_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_WIND_IM.SBR" : $(SOURCE) $(DEP_CPP__WIND_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\_WIND_IM.OBJ" : $(SOURCE) $(DEP_CPP__WIND_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\_WIND_IM.SBR" : $(SOURCE) $(DEP_CPP__WIND_) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COLR31IM.CXX
DEP_CPP_COLR3=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\WIN31IMP.HXX"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\COLR31IM.OBJ" : $(SOURCE) $(DEP_CPP_COLR3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\COLR31IM.SBR" : $(SOURCE) $(DEP_CPP_COLR3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\COLR31IM.OBJ" : $(SOURCE) $(DEP_CPP_COLR3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\COLR31IM.SBR" : $(SOURCE) $(DEP_CPP_COLR3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILE31IM.CXX
DEP_CPP_FILE3=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\WIN31IMP.HXX"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\FILE31IM.OBJ" : $(SOURCE) $(DEP_CPP_FILE3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\FILE31IM.SBR" : $(SOURCE) $(DEP_CPP_FILE3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\FILE31IM.OBJ" : $(SOURCE) $(DEP_CPP_FILE3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\FILE31IM.SBR" : $(SOURCE) $(DEP_CPP_FILE3) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPPAGE.CXX
DEP_CPP_IMPPA=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"


BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\IMPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\IMPPAGE.SBR" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\IMPPAGE.OBJ" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\IMPPAGE.SBR" : $(SOURCE) $(DEP_CPP_IMPPA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPPSHET.CXX
DEP_CPP_IMPPS=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"


BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\IMPPSHET.OBJ" : $(SOURCE) $(DEP_CPP_IMPPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\IMPPSHET.SBR" : $(SOURCE) $(DEP_CPP_IMPPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\IMPPSHET.OBJ" : $(SOURCE) $(DEP_CPP_IMPPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\IMPPSHET.SBR" : $(SOURCE) $(DEP_CPP_IMPPS) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TFRMPRE.CXX
DEP_CPP_TFRMP=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# ADD CPP /Yc"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Tfrm4.pch"\
 /Yc"tfrmpre.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TFRMPRE.OBJ" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TFRMPRE.SBR" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tfrm4.pch" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yc"tfrmpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yc"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\TFRMPRE.OBJ" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TFRMPRE.SBR" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tfrm4.pch" : $(SOURCE) $(DEP_CPP_TFRMP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TFRMWORK.RC
DEP_RSC_TFRMW=\
	".\HELP2.CUR"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\Debugdef.h"\
	

"$(INTDIR)\TFRMWORK.res" : $(SOURCE) $(DEP_RSC_TFRMW) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TFRM32D.DEF

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ctl3dw.cpp
DEP_CPP_CTL3D=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# SUBTRACT CPP /Fr

"$(INTDIR)\Ctl3dw.obj" : $(SOURCE) $(DEP_CPP_CTL3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_TRIAS_OLDIMPLEMENTATION2" /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_TRIAS_OLDIMPLEMENTATION2" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Tfrm4.pch" /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Ctl3dw.obj" : $(SOURCE) $(DEP_CPP_CTL3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

"$(INTDIR)\Ctl3dw.sbr" : $(SOURCE) $(DEP_CPP_CTL3D) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TFRM32.DEF

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\animate.cpp
DEP_CPP_ANIMA=\
	".\Tfrmpre.hxx"\
	{$(INCLUDE)}"\_COMONVU.HXX"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\_RUNTIME.HXX"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\CommonVu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_debug.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\animate.obj" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"

"$(INTDIR)\animate.sbr" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\Tfrm4.pch"


# End Source File
# End Target
# End Project
################################################################################
