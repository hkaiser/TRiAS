# Microsoft Developer Studio Project File - Name="GPSImport" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GPSImport - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "GPSImport.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "GPSImport.mak" CFG="GPSImport - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "GPSImport - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "GPSImport - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GPSImport - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GPSImport - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GPSImport - Win32 Release"
# Name "GPSImport - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BNALayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Boost\directory.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\GarminFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSImport.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSImport.odl
# End Source File
# Begin Source File

SOURCE=.\GPSImport.rc
# End Source File
# Begin Source File

SOURCE=.\GPSImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSImportThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Boost\boost.h
# End Source File
# Begin Source File

SOURCE=.\CoordSystems.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.h
# End Source File
# Begin Source File

SOURCE=.\Boost\directory.h
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.h
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.h
# End Source File
# Begin Source File

SOURCE=.\GarminFile.h
# End Source File
# Begin Source File

SOURCE=.\GPSImport.h
# End Source File
# Begin Source File

SOURCE=.\GPSImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GPSImport.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GPSImportW.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico146.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico264.ico
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GPSImport.reg
# End Source File
# Begin Source File

SOURCE=.\res\GPSImportv.tpl

!IF  "$(CFG)" == "GPSImport - Win32 Release"

!ELSEIF  "$(CFG)" == "GPSImport - Win32 Debug"

# Begin Custom Build
InputPath=.\res\GPSImportv.tpl

"res\GPSImport.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\GPSImport.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\GPSstrt.tpl

!IF  "$(CFG)" == "GPSImport - Win32 Release"

!ELSEIF  "$(CFG)" == "GPSImport - Win32 Debug"

# Begin Custom Build
InputPath=.\res\GPSstrt.tpl

"res\GPSstr.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\GPSstr.rc

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
