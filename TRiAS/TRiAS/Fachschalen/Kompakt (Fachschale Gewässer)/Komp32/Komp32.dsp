# Microsoft Developer Studio Project File - Name="komp32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=komp32 - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Komp32.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Komp32.mak" CFG="komp32 - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "komp32 - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "komp32 - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "komp32 - Win32 Pseudodebug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Fachschalen/Kompakt (Fachschale Gewässer)/Komp32", HPJAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "komp32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /Yu"kompp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 GMObjects.lib ixtnsr50.lib ospace5r.lib containr.lib tfrmwork.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinRel\triasigm.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build - Copying Target to Destination. ..
OutDir=.\WinRel
TargetPath=.\WinRel\triasigm.ext
TargetName=triasigm
InputPath=.\WinRel\triasigm.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F  /Y $(TargetPath) $(TRIASDIR_R) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "__DOCUMENT_FWD_DEFINED__" /FR /Yu"kompp.hxx" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 GMObjectsD.lib ixtnsd50.lib ospace5d.lib cont50d.lib tfrm32d.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinDebug\triasigm.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build - Copying Target to Destination...
OutDir=.\WinDebug
TargetPath=.\WinDebug\triasigm.ext
TargetName=triasigm
InputPath=.\WinDebug\triasigm.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F /Y $(TargetPath) $(TRIASDIR_D) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\komp32__"
# PROP BASE Intermediate_Dir ".\komp32__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\komp32__"
# PROP Intermediate_Dir ".\komp32__"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /D "__DOCUMENT_FWD_DEFINED__" /Yu"kompp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ixtnsr40.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/kompias.ext"
# ADD LINK32 GMObjectsD.lib ixtnsr50.lib cont50r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\komp32__\kompias.ext"
# Begin Custom Build - Copying Target to Destination. ..
TargetPath=.\komp32__\kompias.ext
TargetName=kompias
InputPath=.\komp32__\kompias.ext
SOURCE="$(InputPath)"

"c:\programme\trias\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" c:\programme\trias\trias

# End Custom Build

!ENDIF 

# Begin Target

# Name "komp32 - Win32 Release"
# Name "komp32 - Win32 Debug"
# Name "komp32 - Win32 Pseudodebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\AuxUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=..\Cobjkomp.cxx
# End Source File
# Begin Source File

SOURCE=..\Cobjtree.cxx
# End Source File
# Begin Source File

SOURCE=.\macro\Color.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Color.ebs
InputName=Color

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Color.ebs
InputName=Color

".\macro\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName)d.ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# Begin Custom Build
InputPath=.\macro\Color.ebs
InputName=Color

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Ctopobj.cxx
# End Source File
# Begin Source File

SOURCE=..\Datahelp.cxx
# End Source File
# Begin Source File

SOURCE=..\Gewbaum.cxx
# End Source File
# Begin Source File

SOURCE=.\Komp32.rc

!IF  "$(CFG)" == "komp32 - Win32 Release"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407 /i ".."

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# ADD BASE RSC /l 0x407 /i ".."
# ADD RSC /l 0x407 /i ".."

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Res\KompaktPageExt.rgs
# End Source File
# Begin Source File

SOURCE=..\Kompcls.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompdll.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompgeo.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompgew.cxx
# End Source File
# Begin Source File

SOURCE=..\Komphead.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompias.cxx
# End Source File
# Begin Source File

SOURCE=.\KOMPIAS.DEF

!IF  "$(CFG)" == "komp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Kompifce.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompmem.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompmenu.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompp.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

# ADD CPP /Yc"kompp.hxx"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# ADD CPP /Yc"kompp.hxx"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# ADD CPP /MD /Yc"kompp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Komppage.cpp
# End Source File
# Begin Source File

SOURCE=..\Kompprof.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompsimu.cxx
# End Source File
# Begin Source File

SOURCE=..\Kompwin.cxx
# End Source File
# Begin Source File

SOURCE=..\Kparea.cxx
# End Source File
# Begin Source File

SOURCE=..\Kpbauw.cxx
# End Source File
# Begin Source File

SOURCE=..\Kpbigar.cxx
# End Source File
# Begin Source File

SOURCE=..\kpproject.cxx
# End Source File
# Begin Source File

SOURCE=..\Kpstatus.cxx
# End Source File
# Begin Source File

SOURCE=..\Kpsymb.cxx
# End Source File
# Begin Source File

SOURCE=..\Kpwinot.cxx
# End Source File
# Begin Source File

SOURCE=..\License.cpp
# End Source File
# Begin Source File

SOURCE=..\Strutil.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# ADD CPP /MDd

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\TOOLBAR.CPP
# End Source File
# Begin Source File

SOURCE=.\macro\Topolog.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName)d.ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# Begin Custom Build
InputPath=.\macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Trgeom.cxx
# End Source File
# Begin Source File

SOURCE=..\Txtedit.cxx
# End Source File
# Begin Source File

SOURCE=.\macro\UeberSchwemmung.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\UeberSchwemmung.ebs
InputName=UeberSchwemmung

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\UeberSchwemmung.ebs
InputName=UeberSchwemmung

".\macro\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -v -n -o.\macro\$(InputName)d.ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Vobjprop.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ABOUT.H
# End Source File
# Begin Source File

SOURCE=..\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=..\cobjtree.hxx
# End Source File
# Begin Source File

SOURCE=..\ctopobj.hxx
# End Source File
# Begin Source File

SOURCE=..\gewbaum.hxx
# End Source File
# Begin Source File

SOURCE=..\kompcls.hxx
# End Source File
# Begin Source File

SOURCE=..\KOMPDEF.H
# End Source File
# Begin Source File

SOURCE=..\kompdll.hxx
# End Source File
# Begin Source File

SOURCE=..\kompgew.hxx
# End Source File
# Begin Source File

SOURCE=..\komphead.hxx
# End Source File
# Begin Source File

SOURCE=.\KOMPIAS.H
# End Source File
# Begin Source File

SOURCE=..\kompias.h
# End Source File
# Begin Source File

SOURCE=..\kompias.hxx
# End Source File
# Begin Source File

SOURCE=..\kompp.hxx
# End Source File
# Begin Source File

SOURCE=..\komppage.h
# End Source File
# Begin Source File

SOURCE=..\kompprof.hxx
# End Source File
# Begin Source File

SOURCE=..\kompsimu.hxx
# End Source File
# Begin Source File

SOURCE=..\kompwin.hxx
# End Source File
# Begin Source File

SOURCE=..\kpmcode.hxx
# End Source File
# Begin Source File

SOURCE=..\KPPROJECT.HXX
# End Source File
# Begin Source File

SOURCE=..\kpstatus.hxx
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\Triasdec.h
# End Source File
# Begin Source File

SOURCE=..\TRIASDEF.H
# End Source File
# Begin Source File

SOURCE=..\txtedit.hxx
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# Begin Source File

SOURCE=..\vobjprop.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\macro\Color.ebc
# End Source File
# Begin Source File

SOURCE=.\Macro\Colord.ebc
# End Source File
# Begin Source File

SOURCE=.\KompaktPageExt.rgs
# End Source File
# Begin Source File

SOURCE=.\kompdata.bmp
# End Source File
# Begin Source File

SOURCE=.\KOMPIAS.ICO
# End Source File
# Begin Source File

SOURCE=.\KOMPIAS.RCV
# End Source File
# Begin Source File

SOURCE=.\macro\Topolog.ebc
# End Source File
# Begin Source File

SOURCE=.\Macro\Topologd.ebc
# End Source File
# Begin Source File

SOURCE=.\macro\UeberSchwemmung.ebc
# End Source File
# Begin Source File

SOURCE=.\Macro\UeberSchwemmungd.ebc
# End Source File
# End Group
# End Target
# End Project
