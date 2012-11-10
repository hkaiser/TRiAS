# Microsoft Developer Studio Project File - Name="PictView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PictView - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "PictView.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "PictView.mak" CFG="PictView - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "PictView - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "PictView - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MapTools/PictView", CDZAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PictView - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\_Release"
# PROP Intermediate_Dir ".\_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /Gi /GX /Zi /Od /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "..\..\visobj\lpict42\\" /i "..\..\visobj\lmfcx42\\" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes /debug
# Begin Custom Build - Copy Target
TargetPath=.\_Release\PictView.exe
TargetName=PictView
InputPath=.\_Release\PictView.exe
SOURCE="$(InputPath)"

"d:\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy     /F     $(TargetPath)     D:\bin\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "PictView - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\_Debug"
# PROP Intermediate_Dir ".\_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "e:\entwickl\prj_lib\lpict" /I "..\..\visobj\lpict42\\" /I "..\..\visobj\lmfcx42\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "..\..\visobj\lpict42\\" /i "..\..\visobj\lmfcx42\\" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\_Debug/PictViewD.exe"
# Begin Custom Build - Copy Target
TargetPath=.\_Debug\PictViewD.exe
TargetName=PictViewD
InputPath=.\_Debug\PictViewD.exe
SOURCE="$(InputPath)"

"w:\bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy     /F     $(TargetPath)     w:\bin\ 

# End Custom Build

!ENDIF 

# Begin Target

# Name "PictView - Win32 Release"
# Name "PictView - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BasePpg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\colors.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\IpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PgBWPictures.cpp
# End Source File
# Begin Source File

SOURCE=.\PgOptDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\PictView.cpp
# End Source File
# Begin Source File

SOURCE=.\PictView.odl
# End Source File
# Begin Source File

SOURCE=.\PictView.rc
# End Source File
# Begin Source File

SOURCE=.\PictViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PictViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BasePpg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\colors.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.h
# End Source File
# Begin Source File

SOURCE=.\IpFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PgBWPictures.h
# End Source File
# Begin Source File

SOURCE=.\PgOptDraw.h
# End Source File
# Begin Source File

SOURCE=.\PictView.h
# End Source File
# Begin Source File

SOURCE=.\PictViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\PictViewView.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PictView.ico
# End Source File
# Begin Source File

SOURCE=.\res\PictView.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PictViewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
# Section OLE Controls
# 	{77472C73-3566-11D0-B4BF-00A024145748}
# End Section
# Section PictView : {77472C71-3566-11D0-B4BF-00A024145748}
# 	2:5:Class:CColors
# 	2:10:HeaderFile:colors.h
# 	2:8:ImplFile:colors.cpp
# End Section
# Section PictView : {77472C73-3566-11D0-B4BF-00A024145748}
# 	0:8:Colors.h:C:\LAFX\lpict\PictView\Colors.h
# 	0:10:Colors.cpp:C:\LAFX\lpict\PictView\Colors.cpp
# 	2:21:DefaultSinkHeaderFile:colors.h
# 	2:16:DefaultSinkClass:CColors
# End Section
