# Microsoft Developer Studio Project File - Name="MapMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MapMgr - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "MapMgr.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "MapMgr.mak" CFG="MapMgr - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "MapMgr - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "MapMgr - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MapTools/MapMgr", CAZAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapMgr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\_Release"
# PROP Intermediate_Dir ".\_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "NDEBUG" /D "_WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\..\visobj\lpict42\\" /i "..\..\visobj\lmfcx42\\" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\MapMgr.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /debug
# Begin Custom Build - Copy Target
TargetPath=.\_Release\MapMgr.exe
TargetName=MapMgr
InputPath=.\_Release\MapMgr.exe
SOURCE="$(InputPath)"

"W:\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy        /F        $(TargetPath)        W:\bin\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "MapMgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\_Debug"
# PROP Intermediate_Dir ".\_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "_DEBUG" /D "_WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\..\visobj\lpict42\\" /i "..\..\visobj\lmfcx42\\" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\MapMgr.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\_Debug/MapMgrD.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copy Target
TargetPath=.\_Debug\MapMgrD.exe
TargetName=MapMgrD
InputPath=.\_Debug\MapMgrD.exe
SOURCE="$(InputPath)"

"w:\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy        /F        $(TargetPath)        w:\bin\ 

# End Custom Build

!ENDIF 

# Begin Target

# Name "MapMgr - Win32 Release"
# Name "MapMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AscRead.cpp
# End Source File
# Begin Source File

SOURCE=.\AscWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDocErrors.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileProp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMapProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMapSpecial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapMgrApp.cpp
# End Source File
# Begin Source File

SOURCE=.\MapMgrDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\maskedit.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBars.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackObject.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdtHint.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewMaplist.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewPict.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\dialogs.h
# End Source File
# Begin Source File

SOURCE=.\DlgDocErrors.h
# End Source File
# Begin Source File

SOURCE=.\dlgfileprop.h
# End Source File
# Begin Source File

SOURCE=.\DlgMapProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgMapSpecial.h
# End Source File
# Begin Source File

SOURCE=.\dlgnewdocument.h
# End Source File
# Begin Source File

SOURCE=.\FrameStatus.h
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\MapMgr.h
# End Source File
# Begin Source File

SOURCE=.\MapMgrApp.h
# End Source File
# Begin Source File

SOURCE=.\mapmgrdoc.h
# End Source File
# Begin Source File

SOURCE=.\maskedit.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBars.h
# End Source File
# Begin Source File

SOURCE=.\TrackObject.h
# End Source File
# Begin Source File

SOURCE=.\UpdtHint.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\viewmaplist.h
# End Source File
# Begin Source File

SOURCE=.\ViewPict.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\colorpal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\colorrgb.bmp
# End Source File
# Begin Source File

SOURCE=".\RES\DEFAULT.$IF"
# End Source File
# Begin Source File

SOURCE=.\RES\GCP.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\GCP_BL.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\GCP_BR.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\GCP_TL.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\GCP_TR.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\IDR_DEFA.BIN
# End Source File
# Begin Source File

SOURCE=.\RES\IDR_GEOM.ICO
# End Source File
# Begin Source File

SOURCE=.\res\idw_tb_m.bmp
# End Source File
# Begin Source File

SOURCE=.\res\last.ico
# End Source File
# Begin Source File

SOURCE=.\MapMgr.rc
# End Source File
# Begin Source File

SOURCE=.\res\open.ico
# End Source File
# Begin Source File

SOURCE=.\res\wizard.ico
# End Source File
# End Group
# End Target
# End Project
# Section MapMgr : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CMaskPicture
# 	2:10:HeaderFile:mskpicture.h
# 	2:8:ImplFile:mskpicture.cpp
# End Section
# Section OLE Controls
# 	{C932BA85-4374-101B-A56C-00AA003668DC}
# 	{1924955B-37D5-11D0-B4C2-00A024145748}
# 	{00028C00-0000-0000-0000-000000000046}
# 	{02A69B00-081B-101B-8933-08002B2F4F5A}
# End Section
# Section MapMgr : {C932BA86-4374-101B-A56C-00AA003668DC}
# 	2:5:Class:CMaskEdit
# 	2:10:HeaderFile:mskedit.h
# 	2:8:ImplFile:mskedit.cpp
# End Section
# Section MapMgr : {02A69B00-081B-101B-8933-08002B2F4F5A}
# 	0:8:Font.cpp:C:\TRIASDEV.MVC\MapMgr\Font.cpp
# 	0:9:Picture.h:C:\TRIASDEV.MVC\MapMgr\Picture.h
# 	0:6:Font.h:C:\TRIASDEV.MVC\MapMgr\Font.h
# 	0:11:Picture.cpp:C:\TRIASDEV.MVC\MapMgr\Picture.cpp
# 	0:11:Lbox1Ctrl.h:C:\TRIASDEV.MVC\MapMgr\Lbox1Ctrl.h
# 	0:13:Lbox1Ctrl.cpp:C:\TRIASDEV.MVC\MapMgr\Lbox1Ctrl.cpp
# 	2:21:DefaultSinkHeaderFile:lbox1ctrl.h
# 	2:16:DefaultSinkClass:CLbox1Ctrl
# End Section
# Section MapMgr : {19249559-37D5-11D0-B4C2-00A024145748}
# 	2:5:Class:CMaskEdit
# 	2:10:HeaderFile:maskedit.h
# 	2:8:ImplFile:maskedit.cpp
# End Section
# Section MapMgr : {1924955B-37D5-11D0-B4C2-00A024145748}
# 	0:8:Font.cpp:C:\TRIASDEV.MVC\MapMgr\Font.cpp
# 	0:6:Font.h:C:\TRIASDEV.MVC\MapMgr\Font.h
# 	0:10:MaskEdit.h:C:\TRIASDEV.MVC\MapMgr\MaskEdit.h
# 	0:12:MaskEdit.cpp:C:\TRIASDEV.MVC\MapMgr\MaskEdit.cpp
# 	2:21:DefaultSinkHeaderFile:maskedit.h
# 	2:16:DefaultSinkClass:CMaskEdit
# End Section
# Section MapMgr : {00028C00-0000-0000-0000-000000000046}
# 	0:9:Picture.h:C:\TRIASDEV.MVC\MapMgr\Picture.h
# 	0:8:Font.cpp:C:\TRIASDEV.MVC\MapMgr\Font.cpp
# 	0:6:Font.h:C:\TRIASDEV.MVC\MapMgr\Font.h
# 	0:11:Picture.cpp:C:\TRIASDEV.MVC\MapMgr\Picture.cpp
# 	0:13:MsDgridCtrl.h:C:\TRIASDEV.MVC\MapMgr\MsDgridCtrl.h
# 	0:15:MsDgridCtrl.cpp:C:\TRIASDEV.MVC\MapMgr\MsDgridCtrl.cpp
# 	2:21:DefaultSinkHeaderFile:msdgridctrl.h
# 	2:16:DefaultSinkClass:CMsDgridCtrl
# End Section
# Section MapMgr : {C932BA85-4374-101B-A56C-00AA003668DC}
# 	0:8:Font.cpp:C:\TRIASDEV.MVC\MapMgr\Font.cpp
# 	0:9:Picture.h:C:\TRIASDEV.MVC\MapMgr\Picture.h
# 	0:6:Font.h:C:\TRIASDEV.MVC\MapMgr\Font.h
# 	0:11:Picture.cpp:C:\TRIASDEV.MVC\MapMgr\Picture.cpp
# 	0:8:Msmask.h:C:\TRIASDEV.MVC\MapMgr\Msmask.h
# 	0:10:Msmask.cpp:C:\TRIASDEV.MVC\MapMgr\Msmask.cpp
# 	2:21:DefaultSinkHeaderFile:mskedit.h
# 	2:16:DefaultSinkClass:CMaskEdit
# End Section
# Section MapMgr : {51BB3DDF-0C38-11D2-8F6B-0060085FC1CE}
# 	2:21:DefaultSinkHeaderFile:maskedit.h
# 	2:16:DefaultSinkClass:CMaskEdit
# End Section
# Section MapMgr : {51BB3DDE-0C38-11D2-8F6B-0060085FC1CE}
# 	2:5:Class:CMaskEdit
# 	2:10:HeaderFile:maskedit.h
# 	2:8:ImplFile:maskedit.cpp
# End Section
# Section MapMgr : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:CMaskFont
# 	2:10:HeaderFile:mskfont.h
# 	2:8:ImplFile:mskfont.cpp
# End Section
# Section MapMgr : {00028C02-0000-0000-0000-000000000046}
# 	2:5:Class:CMsDgridCtrl
# 	2:10:HeaderFile:msdgridctrl.h
# 	2:8:ImplFile:msdgridctrl.cpp
# End Section
# Section MapMgr : {02A69B01-081B-101B-8933-08002B2F4F5A}
# 	2:5:Class:CLbox1Ctrl
# 	2:10:HeaderFile:lbox1ctrl.h
# 	2:8:ImplFile:lbox1ctrl.cpp
# End Section
