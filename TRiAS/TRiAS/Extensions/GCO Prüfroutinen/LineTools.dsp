# Microsoft Developer Studio Project File - Name="LineTools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LineTools - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LineTools.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LineTools.mak" CFG="LineTools - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LineTools - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LineTools - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/GCO Prüfroutinen", UYMBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LineTools - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 delayimp.lib containr.lib trias323.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Release/LineTools.ext"
# Begin Custom Build
OutDir=.\Release
TargetName=LineTools
InputPath=.\Release\LineTools.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "LineTools - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 delayimp.lib cont50d.lib trias33d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/LineToold.ext" /pdbtype:sept
# Begin Custom Build
OutDir=.\Debug
TargetName=LineToold
InputPath=.\Debug\LineToold.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "LineTools - Win32 Release"
# Name "LineTools - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCodeStat.cpp
# End Source File
# Begin Source File

SOURCE=.\CCodeStatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClsfyByCode.cpp
# End Source File
# Begin Source File

SOURCE=.\ClsfyByCodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeLine.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeLineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LineTools.cpp
# End Source File
# Begin Source File

SOURCE=.\LineTools.def
# End Source File
# Begin Source File

SOURCE=.\LineTools.idl

!IF  "$(CFG)" == "LineTools - Win32 Release"

!ELSEIF  "$(CFG)" == "LineTools - Win32 Debug"

# ADD MTL /h "LineTools.h" /iid "LineTools_i.c"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LineTools.rc
# End Source File
# Begin Source File

SOURCE=.\LineToolsExt.cpp
# End Source File
# Begin Source File

SOURCE=.\relkey.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCodeStat.h
# End Source File
# Begin Source File

SOURCE=.\CCodeStatDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClsfyByCode.h
# End Source File
# Begin Source File

SOURCE=.\ClsfyByCodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\CodeCheck.h
# End Source File
# Begin Source File

SOURCE=.\CodeLine.h
# End Source File
# Begin Source File

SOURCE=.\CodeLineDlg.h
# End Source File
# Begin Source File

SOURCE=.\errorcode.h
# End Source File
# Begin Source File

SOURCE=.\LineTools.h
# End Source File
# Begin Source File

SOURCE=.\LineToolsConfig.h
# End Source File
# Begin Source File

SOURCE=.\LineToolsExt.h
# End Source File
# Begin Source File

SOURCE=.\LineToolsUtil.h
# End Source File
# Begin Source File

SOURCE=.\relkey.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CCodeStat.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\ClassifyDataOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ClassifyDataORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\ClsfyByCode.rgs
# End Source File
# Begin Source File

SOURCE=.\CodeCheck.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckDataOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckDataORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckGIOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckGIORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckMultiOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CodeCheckMultiORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\CodeLine.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\GeoComponentSequence.dtd
# End Source File
# Begin Source File

SOURCE=.\Res\LineCheckDataOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\lineCheckdataORWnd.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\ClassifyWindowOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ClassifyWindowORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\LineTools.tpl

!IF  "$(CFG)" == "LineTools - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LineTools.tpl

"LineTools.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LineTools.def

# End Custom Build

!ELSEIF  "$(CFG)" == "LineTools - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LineTools.tpl

"LineTools.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LineTools.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LineToolsv.tpl

!IF  "$(CFG)" == "LineTools - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LineToolsv.tpl

"LineTools.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LineTools.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "LineTools - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LineToolsv.tpl

"LineTools.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LineTools.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "LineTools - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "LineTools - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
# Section LineTools : {00000000-0000-0000-0000-800000800000}
# 	1:27:IDS_DESCRIPTION_CLSFYBYCODE:116
# 	1:23:IDD_CLSFYBYCODE_OPTIONS:117
# 	1:15:IDR_CLSFYBYCODE:115
# End Section
