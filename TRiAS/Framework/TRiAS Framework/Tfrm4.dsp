# Microsoft Developer Studio Project File - Name="Tfrm32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Tfrm32 - Win32 Framework DLL Debug TrueTime
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4.mak" CFG="Tfrm32 - Win32 Framework DLL Debug TrueTime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tfrm32 - Win32 Framework DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tfrm32 - Win32 Framework DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tfrm32 - Win32 Framework DLL Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/Framework/TRiAS Framework", YCAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"tfrmpre.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\Tfrmwork.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\Tfrmwork.dll
TargetName=Tfrmwork
InputPath=.\Release\Tfrmwork.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).lib" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Fr /Fp".\Debug/Tfrm50.pch" /Yu"tfrmpre.hxx" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5d.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\Tfrm32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetDir=.\Debug
TargetPath=.\Debug\Tfrm32d.dll
TargetName=Tfrm32d
InputPath=.\Debug\Tfrm32d.dll
InputName=Tfrm32d
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(InputName).pdb" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).lib" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(InputName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Tfrm32___Win32_Framework_DLL_Debug_TrueTime"
# PROP BASE Intermediate_Dir "Tfrm32___Win32_Framework_DLL_Debug_TrueTime"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Tfrm32___Win32_Framework_DLL_Debug_TrueTime"
# PROP Intermediate_Dir "Tfrm32___Win32_Framework_DLL_Debug_TrueTime"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Fr /Fp".\Debug/Tfrm50.pch" /Yu"tfrmpre.hxx" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Fr /Fp".\Tfrm32___Win32_Framework_DLL_Debug_TrueTime/Tfrm50.pch" /Yu"tfrmpre.hxx" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ospace5d.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\Tfrm32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ospace5d.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Tfrm32___Win32_Framework_DLL_Debug_TrueTime\Tfrm32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Tfrm32___Win32_Framework_DLL_Debug_TrueTime
TargetDir=.\Tfrm32___Win32_Framework_DLL_Debug_TrueTime
TargetPath=.\Tfrm32___Win32_Framework_DLL_Debug_TrueTime\Tfrm32d.dll
TargetName=Tfrm32d
InputPath=.\Tfrm32___Win32_Framework_DLL_Debug_TrueTime\Tfrm32d.dll
InputName=Tfrm32d
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(InputName).pdb" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).lib" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(InputName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Tfrm32 - Win32 Framework DLL Release"
# Name "Tfrm32 - Win32 Framework DLL Debug"
# Name "Tfrm32 - Win32 Framework DLL Debug TrueTime"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\_ACCEL.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_ACCL_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_APP.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_APP_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_APPW_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_APPWIND.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_AUX1.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_AUX2.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_BITMAP.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_BPRINT.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_BRSH_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_BRUSH.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_BTMP_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CLIP_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CLIPBRD.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CONTEXT.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CONTROL.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CTLB_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CUR_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_CURSOR.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DCWD_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DCWND.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DEBUG.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DIALOG.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DISPATC.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DLG_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_DRAWOBJ.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_EC_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_EDITWND.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_EVENT.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_EWIN_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_FILELB.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_FLB_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_FONT.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_FONT_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_HELP.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_ICON.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_ICON_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_LINK.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MAIN.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MDI.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MDI_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MENU.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MENU_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MESB_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_MESSBOX.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_PEN.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_PEN_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_POIN_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_POINTER.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_PRIN_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_PRINT.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_RECTANG.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_RSTRING.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_RUNTIME.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_SERVICE.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_WIND_IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\_WINDOW.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\animate.cpp
# End Source File
# Begin Source File

SOURCE=.\COLR31IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\Ctl3dw.cpp

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# SUBTRACT CPP /Fr

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DRAWRECT.CXX

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

# SUBTRACT CPP /Yu

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# SUBTRACT CPP /YX /Yu

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# SUBTRACT BASE CPP /YX /Yu
# SUBTRACT CPP /YX /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FILE31IM.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\HotKey.cpp
# End Source File
# Begin Source File

SOURCE=.\imagectl.cxx
# End Source File
# Begin Source File

SOURCE=.\IMPPAGE.CXX

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# ADD BASE CPP /Yu"tfrmpre.hxx"
# ADD CPP /Yu"tfrmpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IMPPSHET.CXX

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# ADD BASE CPP /Yu"tfrmpre.hxx"
# ADD CPP /Yu"tfrmpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LISTHSCR.CPP
# End Source File
# Begin Source File

SOURCE=.\listview.cxx
# End Source File
# Begin Source File

SOURCE=.\notfyevt.cxx
# End Source File
# Begin Source File

SOURCE=.\PROGBAR.cxx
# End Source File
# Begin Source File

SOURCE=.\PROPPAGE.CXX

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# ADD BASE CPP /Yu"tfrmpre.hxx"
# ADD CPP /Yu"tfrmpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PROPSHET.CXX

!IF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Release"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug"

# ADD CPP /Yu"tfrmpre.hxx"

!ELSEIF  "$(CFG)" == "Tfrm32 - Win32 Framework DLL Debug TrueTime"

# ADD BASE CPP /Yu"tfrmpre.hxx"
# ADD CPP /Yu"tfrmpre.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\statbar.cxx
# End Source File
# Begin Source File

SOURCE=.\STDDLG.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\TFRM50D.DEF
# End Source File
# Begin Source File

SOURCE=.\TFRMPRE.CXX
# ADD CPP /Yc"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\TFRMWORK.RC
# End Source File
# Begin Source File

SOURCE=.\toolbar.cxx
# End Source File
# Begin Source File

SOURCE=.\tooltip.cxx
# End Source File
# Begin Source File

SOURCE=.\treelist.cxx
# End Source File
# Begin Source File

SOURCE=.\updown.cxx
# End Source File
# Begin Source File

SOURCE=.\ZYZ3D.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# Begin Source File

SOURCE=.\ZYZGAUGE.CXX
# ADD CPP /Yu"tfrmpre.hxx"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CLIPDEF.H
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\CVRESID.H
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\DEBUGDEF.H
# End Source File
# Begin Source File

SOURCE=.\Tfrmpre.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\HELP2.CUR
# End Source File
# End Group
# End Target
# End Project
