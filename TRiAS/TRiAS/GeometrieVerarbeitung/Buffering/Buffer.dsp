# Microsoft Developer Studio Project File - Name="Buffer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Buffer - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Buffer.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Buffer.mak" CFG="Buffer - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Buffer - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Buffer - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Buffer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"bufferp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr50.lib ospace5r.lib tfrmwork.lib containr.lib triastlb.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\WinRel\Buffer.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\WinRel
TargetPath=.\WinRel\buffer.ext
TargetName=buffer
InputPath=.\WinRel\buffer.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Fp".\Debug\BUFFERD.pch" /Yu"bufferp.hxx" /Fd".\Debug\BUFFERD.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd50.lib ospace5d.lib tfrm32d.lib cont50d.lib triastld.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Debug\bufferd.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\bufferd.ext
TargetName=bufferd
InputPath=.\Debug\bufferd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Buffer - Win32 Release"
# Name "Buffer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BUFF_EIN.CXX
# End Source File
# Begin Source File

SOURCE=.\BUFFER.CXX
# End Source File
# Begin Source File

SOURCE=.\BUFFER.DEF
# End Source File
# Begin Source File

SOURCE=.\Buffer.rc
# End Source File
# Begin Source File

SOURCE=.\Buffering.cxx
# End Source File
# Begin Source File

SOURCE=.\BUFFERP.CXX
# ADD CPP /Yc"bufferp.hxx"
# End Source File
# Begin Source File

SOURCE=.\Buffext.cxx
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Buff_ein.hxx
# End Source File
# Begin Source File

SOURCE=.\Buffer.hxx
# End Source File
# Begin Source File

SOURCE=.\BufferConfig.h
# End Source File
# Begin Source File

SOURCE=.\Bufferm.hxx
# End Source File
# Begin Source File

SOURCE=.\Bufferp.hxx
# End Source File
# Begin Source File

SOURCE=.\Bufferr.h
# End Source File
# Begin Source File

SOURCE=.\Buffguid.h
# End Source File
# Begin Source File

SOURCE=.\Bufkonst.hxx
# End Source File
# Begin Source File

SOURCE=.\SmartInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\BUFFER.TPL

!IF  "$(CFG)" == "Buffer - Win32 Release"

USERDEP__BUFFE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\BUFFER.TPL

"buffer.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile buffer.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

USERDEP__BUFFE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\BUFFER.TPL

"buffer.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile buffer.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bufferv.tpl

!IF  "$(CFG)" == "Buffer - Win32 Release"

USERDEP__BUFFER="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\bufferv.tpl

"buffer.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile buffer.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

USERDEP__BUFFER="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\bufferv.tpl

"buffer.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile buffer.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Buffer - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
