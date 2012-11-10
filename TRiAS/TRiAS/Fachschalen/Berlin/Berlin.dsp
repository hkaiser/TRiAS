# Microsoft Developer Studio Project File - Name="Berlin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Berlin - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Berlin.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Berlin.mak" CFG="Berlin - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Berlin - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Berlin - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Fachschalen/Berlin", HUTAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Berlin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 GMObjects.lib ixtatr50.lib TRiASTlb.lib ospace5r.lib containr.lib tfrmwork.lib stdstr5r.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\Berlin.ext"
# Begin Custom Build - Copying Target to Destination...
OutDir=.\Release
TargetPath=.\Release\Berlin.ext
TargetName=Berlin
InputPath=.\Release\Berlin.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "BERLINUPDATE" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /D "OS_NO_WSTRING" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".\.." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 GMObjectsD.lib ixtatd50.lib triastld.lib ospace5d.lib stdstr5d.lib tfrm32d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\Berlind.ext"
# Begin Custom Build - Copying Target to Destination...
OutDir=.\Debug
TargetPath=.\Debug\Berlind.ext
TargetName=Berlind
InputPath=.\Debug\Berlind.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D) $(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Berlin - Win32 Release"
# Name "Berlin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\macro\Alb.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Alb.ebs
InputName=Alb

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\Alb.ebs
InputName=Alb

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\AuxUIOwner.cpp

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.CPP

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD /O1 /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.DEF
# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.RC
# End Source File
# Begin Source File

SOURCE=.\macro\BLINK.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\BLINK.EBS
InputName=BLINK

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\BLINK.EBS
InputName=BLINK

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\FNUMMER.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\FNUMMER.EBS
InputName=FNUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\FTeil.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\FTeil.ebs
InputName=FTeil

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\FTeil.ebs
InputName=FTeil

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\GiTest.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\GiTest.ebs
InputName=GiTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\GiTest.ebs
InputName=GiTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\IDENT.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\IDENT.EBS
InputName=IDENT

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\IDENT.EBS
InputName=IDENT

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\INSEL.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\INSEL.EBS
InputName=INSEL

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\INSEL.EBS
InputName=INSEL

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\Nummer.ebf
# End Source File
# Begin Source File

SOURCE=.\macro\NUMMER.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\NUMMER.EBS
InputName=NUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\NUMMER.EBS
InputName=NUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\ObjekteNummerieren.cpp

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\ObjekteNummerieren.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjekteNummerieren.ebs
InputName=ObjekteNummerieren

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\ObjekteNummerieren.ebs
InputName=ObjekteNummerieren

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjekteNummerieren.rgs
# End Source File
# Begin Source File

SOURCE=.\macro\ObjNummer.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjNummer.ebs
InputName=ObjNummer

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\ObjNummer.ebs
InputName=ObjNummer

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\OnlyOneObject.cpp
# End Source File
# Begin Source File

SOURCE=.\macro\OnlyOneObject.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\OnlyOneObject.ebs
InputName=OnlyOneObject

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\StdAfx.cpp

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# ADD CPP /Yc"stdafx.h"
# SUBTRACT CPP /D "OS_NO_WSTRING"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=..\Berlinext.h
# End Source File
# Begin Source File

SOURCE=..\ObjekteNummerieren.h
# End Source File
# Begin Source File

SOURCE=..\OnlyOneObject.h
# End Source File
# Begin Source File

SOURCE=..\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
