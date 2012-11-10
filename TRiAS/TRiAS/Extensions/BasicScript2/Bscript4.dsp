# Microsoft Developer Studio Project File - Name="Bscriptn" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Bscriptn - Win32 Debug TrueTime
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Bscript4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Bscript4.mak" CFG="Bscriptn - Win32 Debug TrueTime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bscriptn - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bscriptn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bscriptn - Win32 Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\win32\Release"
# PROP Intermediate_Dir ".\win32\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /Fp".\win32\Release\Bscript.pch" /Yu"bscriptp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_NEWCATIDS" /d _WIN32_IE=0x0400
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar50.lib containr.lib ospace5r.lib stdstr5r.lib shfolder.lib delayimp.lib ebn.lib winmm.lib shlwapi.lib /delay:unload /nologo /dll /debug /machine:I386 /out:".\win32\Release\Bscript.ext" /delayload:shfolder.dll /delayload:shlwapi.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /subsystem:windows,4.0 /delayload:shlwapi.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\win32\Release
TargetPath=.\win32\Release\Bscript.ext
TargetName=Bscript
InputPath=.\win32\Release\Bscript.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\win32\Debug"
# PROP Intermediate_Dir ".\win32\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /D "_DEBUG" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /Fp".\win32\Debug\Bscript.pch" /Yu"bscriptp.hxx" /Fd".\win32\Debug\bscript.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /fo".\win32\Debug\Bscriptd.res" /d "_DEBUG" /d "_AFXDLL" /d "_NEWCATIDS" /d _WIN32_IE=0x0400
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib stdstr5d.lib shfolder.lib delayimp.lib ebn.lib winmm.lib shlwapi.lib /delay:unload /nologo /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /out:".\win32\Debug\bscriptd.ext" /delayload:shfolder.dll /delayload:shlwapi.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /SUBSYSTEM:windows,4.0 /delayload:shlwapi.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\win32\Debug
TargetPath=.\win32\Debug\bscriptd.ext
TargetName=bscriptd
InputPath=.\win32\Debug\bscriptd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Bscriptn___Win32_Debug_TrueTime"
# PROP BASE Intermediate_Dir "Bscriptn___Win32_Debug_TrueTime"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Bscriptn___Win32_Debug_TrueTime"
# PROP Intermediate_Dir "Bscriptn___Win32_Debug_TrueTime"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /D "_DEBUG" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /FR /Fp".\win32\Debug\Bscript.pch" /Yu"bscriptp.hxx" /Fd".\win32\Debug\bscript.pdb" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /D "_DEBUG" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /FR /Fp"Bscriptn___Win32_Debug_TrueTime\Bscript.pch" /Yu"bscriptp.hxx" /Fd"Bscriptn___Win32_Debug_TrueTime\bscript.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /fo".\win32\Debug\Bscriptd.res" /d "_DEBUG" /d "_AFXDLL" /d "_NEWCATIDS" /d _WIN32_IE=0x0400
# SUBTRACT BASE RSC /x
# ADD RSC /l 0x407 /fo".\win32\Debug\Bscriptd.res" /d "_DEBUG" /d "_AFXDLL" /d "_NEWCATIDS" /d _WIN32_IE=0x0400
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ixtmad50.lib cont50d.lib ebn.lib winmm.lib ospace5d.lib stdstr5d.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /out:".\win32\Debug\bscriptd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib stdstr5d.lib shfolder.lib delayimp.lib ebn.lib winmm.lib shlwapi.lib /delay:unload /nologo /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /out:"Bscriptn___Win32_Debug_TrueTime\bscriptd.ext" /delayload:shfolder.dll /delayload:shlwapi.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:shell32.dll /delayload:comctl32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /SUBSYSTEM:windows,4.0 /
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Bscriptn___Win32_Debug_TrueTime
TargetPath=.\Bscriptn___Win32_Debug_TrueTime\bscriptd.ext
TargetName=bscriptd
InputPath=.\Bscriptn___Win32_Debug_TrueTime\bscriptd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Bscriptn - Win32 Release"
# Name "Bscriptn - Win32 Debug"
# Name "Bscriptn - Win32 Debug TrueTime"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\addfdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AniTrayIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\bscrext.cxx
# End Source File
# Begin Source File

SOURCE=.\BSCREXTF.CPP
# End Source File
# Begin Source File

SOURCE=.\BSCRIPT.CXX
# End Source File
# Begin Source File

SOURCE=.\bscript.def
# End Source File
# Begin Source File

SOURCE=.\Win32\Bscript.rc
# ADD BASE RSC /l 0x407 /i "Win32"
# ADD RSC /l 0x407 /i "Win32" /i ".\Win32"
# End Source File
# Begin Source File

SOURCE=.\BSCRIPTP.CXX
# ADD CPP /Yc"bscriptp.hxx"
# End Source File
# Begin Source File

SOURCE=.\conststr.cpp
# End Source File
# Begin Source File

SOURCE=.\cptvw.cpp
# End Source File
# Begin Source File

SOURCE=.\ctfgeogk.CXX
# End Source File
# Begin Source File

SOURCE=.\Datahelp.cpp
# End Source File
# Begin Source File

SOURCE=.\dbfrmvw.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DbFrmVw2.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DebCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\debfdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DUMMYPAR.CPP
# End Source File
# Begin Source File

SOURCE=.\EBARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\Ebc.cpp
# End Source File
# Begin Source File

SOURCE=.\editctrl.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\expall.cpp
# End Source File
# Begin Source File

SOURCE=.\Filtdlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\filtscr.cpp
# End Source File
# Begin Source File

SOURCE=.\FNDRPLD.CPP
# End Source File
# Begin Source File

SOURCE=.\MACRO.CPP
# End Source File
# Begin Source File

SOURCE=.\MacroIconsInTray.cpp
# End Source File
# Begin Source File

SOURCE=.\MacroIntroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MLONGSTR.CXX
# End Source File
# Begin Source File

SOURCE=.\MRU.CPP
# End Source File
# Begin Source File

SOURCE=.\MSTRSTR.CXX
# End Source File
# Begin Source File

SOURCE=.\myfiledg.cpp
# End Source File
# Begin Source File

SOURCE=.\NotifBar.cpp
# End Source File
# Begin Source File

SOURCE=.\objfeat.cpp
# End Source File
# Begin Source File

SOURCE=.\ofeatpp.cpp
# End Source File
# Begin Source File

SOURCE=.\projscr.cpp
# End Source File
# Begin Source File

SOURCE=.\Propactb.cxx
# End Source File
# Begin Source File

SOURCE=.\RegisterEbs.cpp
# End Source File
# Begin Source File

SOURCE=.\relscrpt.cpp
# End Source File
# Begin Source File

SOURCE=.\REXPSTR.CPP
# End Source File
# Begin Source File

SOURCE=.\runebobs.cpp
# End Source File
# Begin Source File

SOURCE=.\runerr.cpp
# End Source File
# Begin Source File

SOURCE=.\Runscorg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCRPTDLG.CPP

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# SUBTRACT CPP /WX

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# SUBTRACT BASE CPP /WX
# SUBTRACT CPP /WX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\split.cpp
# End Source File
# Begin Source File

SOURCE=.\splitter.cpp
# End Source File
# Begin Source File

SOURCE=.\spltree.cpp
# End Source File
# Begin Source File

SOURCE=.\Strinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\tmplman.cpp
# End Source File
# Begin Source File

SOURCE=.\Triasext.cxx
# End Source File
# Begin Source File

SOURCE=.\Wrapxt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\addfdlg.h
# End Source File
# Begin Source File

SOURCE=.\AniTrayIcon.h
# End Source File
# Begin Source File

SOURCE=.\Bscrext.hxx
# End Source File
# Begin Source File

SOURCE=.\Bscrextf.h
# End Source File
# Begin Source File

SOURCE=.\BSCRIPT.H
# End Source File
# Begin Source File

SOURCE=.\Bscript.hxx
# End Source File
# Begin Source File

SOURCE=.\Bscriptp.hxx
# End Source File
# Begin Source File

SOURCE=.\BSParam.h
# End Source File
# Begin Source File

SOURCE=.\Conststr.h
# End Source File
# Begin Source File

SOURCE=.\cptvw.h
# End Source File
# Begin Source File

SOURCE=.\Datahelp.h
# End Source File
# Begin Source File

SOURCE=.\dbfrmvw.h
# End Source File
# Begin Source File

SOURCE=.\DbFrmVw2.h
# End Source File
# Begin Source File

SOURCE=.\debctrl.h
# End Source File
# Begin Source File

SOURCE=.\debfdlg.h
# End Source File
# Begin Source File

SOURCE=.\Dummypar.h
# End Source File
# Begin Source File

SOURCE=.\EBARRAY.HXX
# End Source File
# Begin Source File

SOURCE=.\editctrl.h
# End Source File
# Begin Source File

SOURCE=.\expall.h
# End Source File
# Begin Source File

SOURCE=.\filtdlg2.h
# End Source File
# Begin Source File

SOURCE=.\Filtscr.h
# End Source File
# Begin Source File

SOURCE=.\FNDRPLD.H
# End Source File
# Begin Source File

SOURCE=.\iscrprop.h
# End Source File
# Begin Source File

SOURCE=.\Macrguid.h
# End Source File
# Begin Source File

SOURCE=.\Macro.h
# End Source File
# Begin Source File

SOURCE=.\MacroIntroDlg.h
# End Source File
# Begin Source File

SOURCE=.\MLONGSTR.HXX
# End Source File
# Begin Source File

SOURCE=.\MLONGSTR.INL
# End Source File
# Begin Source File

SOURCE=.\MRU.H
# End Source File
# Begin Source File

SOURCE=.\MSTRSTR.HXX
# End Source File
# Begin Source File

SOURCE=.\MSTRSTR.INL
# End Source File
# Begin Source File

SOURCE=.\myfiledg.h
# End Source File
# Begin Source File

SOURCE=.\NotifBar.h
# End Source File
# Begin Source File

SOURCE=.\Objfeat.h
# End Source File
# Begin Source File

SOURCE=.\Objmanguid.h
# End Source File
# Begin Source File

SOURCE=.\ofeatpp.h
# End Source File
# Begin Source File

SOURCE=.\oftppxt.h
# End Source File
# Begin Source File

SOURCE=.\projscr.h
# End Source File
# Begin Source File

SOURCE=.\Propactb.hxx
# End Source File
# Begin Source File

SOURCE=.\proppext.h
# End Source File
# Begin Source File

SOURCE=.\RegisterEbs.h
# End Source File
# Begin Source File

SOURCE=.\REGISTRY.HXX
# End Source File
# Begin Source File

SOURCE=.\relscrpt.h
# End Source File
# Begin Source File

SOURCE=.\REXPSTR.H
# End Source File
# Begin Source File

SOURCE=.\runebobs.h
# End Source File
# Begin Source File

SOURCE=.\Runerr.h
# End Source File
# Begin Source File

SOURCE=.\Runscorg.h
# End Source File
# Begin Source File

SOURCE=.\scrptdlg.h
# End Source File
# Begin Source File

SOURCE=.\split.h
# End Source File
# Begin Source File

SOURCE=.\splitter.h
# End Source File
# Begin Source File

SOURCE=.\spltree.h
# End Source File
# Begin Source File

SOURCE=.\Strinfo.h
# End Source File
# Begin Source File

SOURCE=.\tmplman.h
# End Source File
# Begin Source File

SOURCE=.\Toolbarx.h
# End Source File
# Begin Source File

SOURCE=.\TRIASEXT.H
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# Begin Source File

SOURCE=.\Wrapxt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Win32\Azhelp.rc

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WIN32\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Win32\Bscript.rcv
# End Source File
# Begin Source File

SOURCE=.\Win32\Dd.rc

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Win32\Dg.rc

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WIN32\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Win32\Macro.ico
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroDefault.ico
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroIntro.bmp
# End Source File
# Begin Source File

SOURCE=.\Win32\Macros3.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroSequence0.ico
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroSequence1.ico
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroSequence2.ico
# End Source File
# Begin Source File

SOURCE=.\WIN32\MacroSequence3.ico
# End Source File
# Begin Source File

SOURCE=.\Win32\notif.not
# End Source File
# Begin Source File

SOURCE=.\WIN32\ObjProp.ico
# End Source File
# Begin Source File

SOURCE=.\Win32\projectt.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\PropAction.ico
# End Source File
# Begin Source File

SOURCE=.\Win32\propertyactiond.ebc
# End Source File
# Begin Source File

SOURCE=.\Win32\PropertyActionr.ebc
# End Source File
# Begin Source File

SOURCE=.\Win32\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\Win32\bswrapperextension.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\CreateObjectFeatureFileScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\CreateObjectFeatureScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\expimpscript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\FilterScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\MacroFileScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\MacroScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\oftppxt.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\RegisterEbs.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\RegisterScript.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\StreamInfo.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\BSCREXTP.TPL

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

USERDEP__BSCRE="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCREXTP.TPL

"bscrext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscrext.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

USERDEP__BSCRE="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCREXTP.TPL

"bscrext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscrext.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

USERDEP__BSCRE="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCREXTP.TPL

"bscrext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscrext.rc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BSCRIP16.MAK
# End Source File
# Begin Source File

SOURCE=.\BSCRIPT.TPL

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

USERDEP__BSCRI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPT.TPL

"bscript.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

USERDEP__BSCRI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPT.TPL

"bscript.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

USERDEP__BSCRI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPT.TPL

"bscript.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BSCRIPTV.TPL

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

USERDEP__BSCRIP="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPTV.TPL

"bscript.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

USERDEP__BSCRIP="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPTV.TPL

"bscript.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

USERDEP__BSCRIP="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\BSCRIPTV.TPL

"bscript.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak bscript.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

USERDEP__VERSI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

USERDEP__VERSI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

USERDEP__VERSI="bscrip16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f bscrip16.mak versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Basic Scripts"

# PROP Default_Filter "*.ebs"
# Begin Source File

SOURCE=.\PropertyAction.ebs

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.
InputPath=.\PropertyAction.ebs
InputName=PropertyAction

"$(InputDir)\Win32\$(InputName)r.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(InputDir)\Win32\$(InputName)r.ebc -DNDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.
InputPath=.\PropertyAction.ebs
InputName=PropertyAction

"$(InputDir)\Win32\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\Win32\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug TrueTime"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.
InputPath=.\PropertyAction.ebs
InputName=PropertyAction

"$(InputDir)\Win32\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\Win32\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
