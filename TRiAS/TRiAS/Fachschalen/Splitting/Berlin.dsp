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
# ADD CPP /nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".\.." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 GMObjects.lib ixtatr50.lib TRiASTlb.lib ospace5r.lib containr.lib tfrmwork.lib stdstr5r.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\Splitting.ext"
# SUBTRACT LINK32 /incremental:yes
# Begin Custom Build - Copying Target to Destination...
OutDir=.\Release
TargetPath=.\Release\Splitting.ext
TargetName=Splitting
InputPath=.\Release\Splitting.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /D "OS_NO_WSTRING" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".\.." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 GMObjectsD.lib ixtatd50.lib triastld.lib ospace5d.lib stdstr5d.lib tfrm32d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug/Splittid.ext"
# Begin Custom Build - Copying Target to Destination...
OutDir=.\Debug
TargetPath=.\Debug\Splittid.ext
TargetName=Splittid
InputPath=.\Debug\Splittid.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\Alb.ebs
InputName=Alb

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\Alb_Upd1.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Alb_Upd1.EBS
InputName=Alb_Upd1

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\Alb_Upd1.EBS
InputName=Alb_Upd1

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AuxUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\BERLIN.CPP
# End Source File
# Begin Source File

SOURCE=.\Berlin.def
# End Source File
# Begin Source File

SOURCE=.\Berlin.RC

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
# SUBTRACT RSC /i ".\.."

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\BLINK.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\BLINK.EBS
InputName=BLINK

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\BLINK.EBS
InputName=BLINK

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\FNUMMER.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\FNUMMER.EBS
InputName=FNUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\FNUMMER.EBS
InputName=FNUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

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
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\FTeil.ebs
InputName=FTeil

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

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
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\GiTest.ebs
InputName=GiTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

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
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\IDENT.EBS
InputName=IDENT

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\Ident_Upd1.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Ident_Upd1.ebs
InputName=Ident_Upd1

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\Ident_Upd1.ebs
InputName=Ident_Upd1

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\IDTest.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\IDTest.ebs
InputName=IDTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\IDTest.ebs
InputName=IDTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

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
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\INSEL.EBS
InputName=INSEL

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NoMultiObjekt.cpp
# End Source File
# Begin Source File

SOURCE=.\macro\NoMultiObjekt.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\NoMultiObjekt.ebs
InputName=NoMultiObjekt

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\NoMultiObjekt.ebs
InputName=NoMultiObjekt

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\NUMMER.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\NUMMER.EBS
InputName=NUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\NUMMER.EBS
InputName=NUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjekteNummerieren.cpp
# End Source File
# Begin Source File

SOURCE=.\macro\ObjekteNummerieren.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjekteNummerieren.ebs
InputName=ObjekteNummerieren

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\ObjekteNummerieren.ebs
InputName=ObjekteNummerieren

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\macro\ObjNummer.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjNummer.ebs
InputName=ObjNummer

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\ObjNummer.ebs
InputName=ObjNummer

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnlyOneObject.cpp
# End Source File
# Begin Source File

SOURCE=.\macro\OnlyOneObject.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\OnlyOneObject.ebs
InputName=OnlyOneObject

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\OnlyOneObject.ebs
InputName=OnlyOneObject

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\macro\Unbebaut.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Unbebaut.ebs
InputName=Unbebaut

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# Begin Custom Build
InputPath=.\macro\Unbebaut.ebs
InputName=Unbebaut

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\BerlinConfig.h
# End Source File
# Begin Source File

SOURCE=.\Berlinext.h
# End Source File
# Begin Source File

SOURCE=.\BLNGUID.H
# End Source File
# Begin Source File

SOURCE=.\MyNotify.h
# End Source File
# Begin Source File

SOURCE=.\NoMultiObjekt.h
# End Source File
# Begin Source File

SOURCE=.\Res\NoMultiObjekt.rgs
# End Source File
# Begin Source File

SOURCE=.\NoMultiObjektGuid.h
# End Source File
# Begin Source File

SOURCE=.\ObjekteNummerieren.h
# End Source File
# Begin Source File

SOURCE=.\Res\ObjekteNummerieren.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjektNummerierenGuid.h
# End Source File
# Begin Source File

SOURCE=.\OnlyOneObject.h
# End Source File
# Begin Source File

SOURCE=.\Res\OnlyOneObject.rgs
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\STRINGS.H
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\macro\Alb.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\BLINK.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\FNUMMER.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\FTeil.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\GiTest.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\IDENT.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\IDTest.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\INSEL.ebc
# End Source File
# Begin Source File

SOURCE=.\metadata.bmp
# End Source File
# Begin Source File

SOURCE=.\macro\NoMultiObjekt.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\NUMMER.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\ObjekteNummerieren.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\ObjNummer.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\OnlyOneObject.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\Unbebaut.ebc
# End Source File
# Begin Source File

SOURCE=.\upddata.bmp
# End Source File
# Begin Source File

SOURCE=..\upddata.bmp
# End Source File
# End Target
# End Project
