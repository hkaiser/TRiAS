# Microsoft Developer Studio Project File - Name="linver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=linver - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Linver.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Linver.mak" CFG="linver - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "linver - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "linver - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath "..\..\..\VCPP"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "linver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "$(TRIASINCLUDE)\hpp" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"pheader.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar50.lib containr.lib ospace5r.lib triastlb.lib largeint.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\MaschBlr.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Release
TargetPath=.\Release\maschblr.ext
TargetName=maschblr
InputPath=.\Release\maschblr.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /I "$(TRIASINCLUDE)\hpp" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"pheader.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib triastld.lib largeint.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\maschbld.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\maschbld.ext
TargetName=maschbld
InputPath=.\Debug\maschbld.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "linver - Win32 Release"
# Name "linver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Datahelp.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Doppgeop.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeoObj.cpp
# End Source File
# Begin Source File

SOURCE=.\geoobjs.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\imaschen.cpp
# End Source File
# Begin Source File

SOURCE=.\Imaschen.idl

!IF  "$(CFG)" == "linver - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Creating type library ...
InputPath=.\Imaschen.idl
InputName=Imaschen

BuildCmds= \
	midl $(InputName).idl /win32 /h $(TRIASINCLUDE)\$(InputName).h  /tlb       $(InputName).tlb

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - create type library
InputPath=.\Imaschen.idl
InputName=Imaschen

BuildCmds= \
	midl $(InputName).idl /win32 /h $(TRIASINCLUDE)\$(InputName).h  /tlb       $(InputName).tlb

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\linver.cpp
# ADD CPP /Yu"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\Linver.def
# End Source File
# Begin Source File

SOURCE=.\Linver.rc
# End Source File
# Begin Source File

SOURCE=.\Linvprp.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\maschbil.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\objkante.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\objstat.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Objstatp.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Paramdlg.cpp
# ADD CPP /Yu"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\Pheader.cpp
# ADD CPP /Yc"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\Progress.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Propactb.cpp
# ADD CPP /Yu"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\Strutil.cpp
# ADD CPP /Yu"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\TOOLS.Cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Verparam.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Verschnt.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Doppgeop.hpp
# End Source File
# Begin Source File

SOURCE=.\DOPPGUID.H
# End Source File
# Begin Source File

SOURCE=.\GeoObj.h
# End Source File
# Begin Source File

SOURCE=.\Geoobjs.hpp
# End Source File
# Begin Source File

SOURCE=.\Imaschen.hpp
# End Source File
# Begin Source File

SOURCE=.\LINAGUID.H
# End Source File
# Begin Source File

SOURCE=.\LINVER.HPP
# End Source File
# Begin Source File

SOURCE=.\LINVGUID.H
# End Source File
# Begin Source File

SOURCE=.\Linvprp.hpp
# End Source File
# Begin Source File

SOURCE=.\Maschbil.hpp
# End Source File
# Begin Source File

SOURCE=.\OBJCONT.HPP
# End Source File
# Begin Source File

SOURCE=.\Objkante.hpp
# End Source File
# Begin Source File

SOURCE=.\Objstat.hpp
# End Source File
# Begin Source File

SOURCE=.\Objstatp.hpp
# End Source File
# Begin Source File

SOURCE=.\Paramdlg.hpp
# End Source File
# Begin Source File

SOURCE=.\PHEADER.H
# End Source File
# Begin Source File

SOURCE=.\RSLTGUID.H
# End Source File
# Begin Source File

SOURCE=.\Tools.hpp
# End Source File
# Begin Source File

SOURCE=.\VERGUID.H
# End Source File
# Begin Source File

SOURCE=.\Verparam.hpp
# End Source File
# Begin Source File

SOURCE=.\Verschnt.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Imaschen.tlb
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\Doppelt3.rgs
# End Source File
# Begin Source File

SOURCE=.\Imaschen.rgs
# End Source File
# Begin Source File

SOURCE=.\Maschen3.rgs
# End Source File
# Begin Source File

SOURCE=.\Result3.rgs
# End Source File
# Begin Source File

SOURCE=.\VERSCHNT3.RGS
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=..\..\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\LINVER.TPL

!IF  "$(CFG)" == "linver - Win32 Release"

USERDEP__LINVE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\LINVER.TPL

"linver.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile linver.def

# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

USERDEP__LINVE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\LINVER.TPL

"linver.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile linver.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LINVERV.TPL

!IF  "$(CFG)" == "linver - Win32 Release"

USERDEP__LINVER="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\LINVERV.TPL

"linver.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile linver.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

USERDEP__LINVER="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\LINVERV.TPL

"linver.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile linver.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "linver - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
