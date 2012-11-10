# Microsoft Developer Studio Project File - Name="Odbcext" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Odbcext - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Odbcext.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Odbcext.mak" CFG="Odbcext - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Odbcext - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Odbcext - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Anzeige von ODBC-Daten", AXGAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Odbcext - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release"
# PROP Intermediate_Dir ".\release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__XT" /D "_WINDLL" /D "__MFC__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_AFXCTL" /D "_AFXEXT" /D "_WINDLL" /D "_MBCS" /D "__UseOGX__" /Yu"PHEADER.H" /Fd".\release/OdbcExt.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib containr.lib xtsnmfc.lib odbcinst.lib /nologo /subsystem:windows /dll /machine:IX86
# ADD LINK32 ixtmar50.lib containr.lib ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib largeint.lib triastlb.lib version.lib /nologo /dll /debug /machine:IX86 /out:"Release\odbcext.ext" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Release
TargetPath=.\Release\odbcext.ext
TargetName=odbcext
InputPath=.\Release\odbcext.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Odbcext - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\debugn"
# PROP Intermediate_Dir ".\debugn"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__XT" /D "_WINDLL" /D "__MFC__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_AFXCTL" /D "_AFXEXT" /D "_WINDLL" /D "_MBCS" /D "__UseOGX__" /Fr /Yu"PHEADER.H" /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib containr.lib xtsnmfc.lib odbcinst.lib /nologo /subsystem:windows /dll /debug /machine:IX86
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib largeint.lib version.lib /nologo /dll /debug /machine:IX86 /out:"Debugn\odbcextd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debugn
TargetPath=.\Debugn\odbcextd.ext
TargetName=odbcextd
InputPath=.\Debugn\odbcextd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Odbcext - Win32 Release"
# Name "Odbcext - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Abgleich.cpp
# End Source File
# Begin Source File

SOURCE=.\abglpge.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoListComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CHKLAUSL.CPP
# End Source File
# Begin Source File

SOURCE=.\COLLIST.CPP
# End Source File
# Begin Source File

SOURCE=.\COLUMNST.CPP
# End Source File
# Begin Source File

SOURCE=.\CONNECT.CPP
# End Source File
# Begin Source File

SOURCE=.\CREATEWH.CPP
# End Source File
# Begin Source File

SOURCE=.\DATABASE.CPP
# End Source File
# Begin Source File

SOURCE=.\Datahelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DerivedGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DISPATCH.CPP
# End Source File
# Begin Source File

SOURCE=.\dsnpage.cpp
# End Source File
# Begin Source File

SOURCE=.\fakename.cpp
# End Source File
# Begin Source File

SOURCE=.\FContDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\features.cpp
# End Source File
# Begin Source File

SOURCE=.\Feldin32.cpp
# End Source File
# Begin Source File

SOURCE=.\feldpage.cpp
# End Source File
# Begin Source File

SOURCE=.\Fieldinf.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\filtrpge.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeRelD.cpp
# End Source File
# Begin Source File

SOURCE=.\GETODBCI.CPP
# End Source File
# Begin Source File

SOURCE=.\HEADCTRL.CPP
# End Source File
# Begin Source File

SOURCE=.\Helptext.cpp
# End Source File
# Begin Source File

SOURCE=.\IMPORTPA.CPP
# End Source File
# Begin Source File

SOURCE=.\IMPORTSH.CPP
# End Source File
# Begin Source File

SOURCE=.\ImpRslt2.cpp
# End Source File
# Begin Source File

SOURCE=.\Menubitmapper.cpp
# End Source File
# Begin Source File

SOURCE=.\Merkmal.cp
# End Source File
# Begin Source File

SOURCE=.\MERKMAL.CPP
# End Source File
# Begin Source File

SOURCE=.\MERKMAL.L

!IF  "$(CFG)" == "Odbcext - Win32 Release"

USERDEP__MERKM="merkmal.sed"	
# Begin Custom Build
InputPath=.\MERKMAL.L

"merkmal.cp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l merkmal.l 
	sed -f merkmal.sed merkmal.c > merkmal.cp 
	del merkmal.c > nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Odbcext - Win32 Debug"

USERDEP__MERKM="merkmal.sed"	
# Begin Custom Build
InputPath=.\MERKMAL.L

"merkmal.cp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l merkmal.l 
	sed -f merkmal.sed merkmal.c > merkmal.cp 
	del merkmal.c > nul 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\myhelper.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJINFO.CPP
# End Source File
# Begin Source File

SOURCE=.\OBJPROPF.CPP
# End Source File
# Begin Source File

SOURCE=.\ODBCERR.CPP
# End Source File
# Begin Source File

SOURCE=.\ODBCEXT.CPP
# End Source File
# Begin Source File

SOURCE=.\ODBCEXT.DEF
# End Source File
# Begin Source File

SOURCE=.\ODBCEXT.RC
# End Source File
# Begin Source File

SOURCE=.\ODBCProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\PHEADER.CPP
# ADD BASE CPP /Yc"PHEADER.H"
# ADD CPP /Yc"PHEADER.H"
# End Source File
# Begin Source File

SOURCE=.\pktinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PROFILE.CPP
# End Source File
# Begin Source File

SOURCE=.\Propactb.cpp
# End Source File
# Begin Source File

SOURCE=.\RechStat.cpp
# End Source File
# Begin Source File

SOURCE=.\RECSET.CPP
# End Source File
# Begin Source File

SOURCE=.\RELDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\rsltpge.cpp
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CPP
# End Source File
# Begin Source File

SOURCE=.\Tabdlgs.cpp
# End Source File
# Begin Source File

SOURCE=.\TABLENAM.CPP
# End Source File
# Begin Source File

SOURCE=.\TABLESET.CPP
# End Source File
# Begin Source File

SOURCE=.\TABLINFO.CPP
# End Source File
# Begin Source File

SOURCE=.\TOOLBAR.CPP
# End Source File
# Begin Source File

SOURCE=.\TOOLS.CPP
# End Source File
# Begin Source File

SOURCE=.\Tooltipb.cpp
# End Source File
# Begin Source File

SOURCE=.\triaspge.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\V_DBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\V_DBASE1.CPP
# End Source File
# Begin Source File

SOURCE=.\V_LONGVR.CPP
# End Source File
# Begin Source File

SOURCE=.\WherePge.cpp
# End Source File
# Begin Source File

SOURCE=.\Whereprp.cpp
# End Source File
# Begin Source File

SOURCE=.\WhereSet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Abgleich.hpp
# End Source File
# Begin Source File

SOURCE=.\Abglpge.hpp
# End Source File
# Begin Source File

SOURCE=.\Actwind.hpp
# End Source File
# Begin Source File

SOURCE=.\AutoListComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Connect.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Biblio\TRiAS\INCLUDE\include50\hpp\CREATEWH.HPP
# End Source File
# Begin Source File

SOURCE=.\DerivedGrid.h
# End Source File
# Begin Source File

SOURCE=.\Dispatch.hpp
# End Source File
# Begin Source File

SOURCE=.\Dsnpage.hpp
# End Source File
# Begin Source File

SOURCE=.\features.h
# End Source File
# Begin Source File

SOURCE=.\Feldin32.hpp
# End Source File
# Begin Source File

SOURCE=.\Feldinfo.hpp
# End Source File
# Begin Source File

SOURCE=.\Feldpage.hpp
# End Source File
# Begin Source File

SOURCE=.\Filedlg.h
# End Source File
# Begin Source File

SOURCE=.\Filtrpge.hpp
# End Source File
# Begin Source File

SOURCE=.\Fld16pge.hpp
# End Source File
# Begin Source File

SOURCE=.\Freereld.hpp
# End Source File
# Begin Source File

SOURCE=.\HEADCTRL.H
# End Source File
# Begin Source File

SOURCE=.\Importpa.hpp
# End Source File
# Begin Source File

SOURCE=.\Importsh.hpp
# End Source File
# Begin Source File

SOURCE=.\Imprslt2.hpp
# End Source File
# Begin Source File

SOURCE=.\Menubitmapper.h
# End Source File
# Begin Source File

SOURCE=.\myhelper.h
# End Source File
# Begin Source File

SOURCE=.\OdbcConfig.h
# End Source File
# Begin Source File

SOURCE=.\Odbcext.hpp
# End Source File
# Begin Source File

SOURCE=.\Odbcext.hr
# End Source File
# Begin Source File

SOURCE=.\Odbcguid.h
# End Source File
# Begin Source File

SOURCE=.\ODBCProperty.h
# End Source File
# Begin Source File

SOURCE=.\Pheader.h
# End Source File
# Begin Source File

SOURCE=.\Pktinfo.hpp
# End Source File
# Begin Source File

SOURCE=.\Profile.hpp
# End Source File
# Begin Source File

SOURCE=.\Rechstat.h
# End Source File
# Begin Source File

SOURCE=.\Recset.hpp
# End Source File
# Begin Source File

SOURCE=.\Reldlg.hpp
# End Source File
# Begin Source File

SOURCE=.\Rsltpge.hpp
# End Source File
# Begin Source File

SOURCE=.\Tablenam.hpp
# End Source File
# Begin Source File

SOURCE=.\Tablinfo.hpp
# End Source File
# Begin Source File

SOURCE=.\Tools.hpp
# End Source File
# Begin Source File

SOURCE=.\Triaspge.hpp
# End Source File
# Begin Source File

SOURCE=.\Trs16pge.hpp
# End Source File
# Begin Source File

SOURCE=.\Userdlg.h
# End Source File
# Begin Source File

SOURCE=.\V_dbase.hpp
# End Source File
# Begin Source File

SOURCE=.\V_longvr.hpp
# End Source File
# Begin Source File

SOURCE=.\Vers32.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\Wherepge.h
# End Source File
# Begin Source File

SOURCE=.\Whereprp.h
# End Source File
# Begin Source File

SOURCE=.\Whereprp.hpp
# End Source File
# Begin Source File

SOURCE=.\Whereset.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Addreld.bmp
# End Source File
# Begin Source File

SOURCE=.\Addrelf.bmp
# End Source File
# Begin Source File

SOURCE=.\Addrelu.bmp
# End Source File
# Begin Source File

SOURCE=.\Addrelx.bmp
# End Source File
# Begin Source File

SOURCE=.\Copy.bmp
# End Source File
# Begin Source File

SOURCE=.\Cut.bmp
# End Source File
# Begin Source File

SOURCE=.\Defabout.dlg
# End Source File
# Begin Source File

SOURCE=.\Delete.bmp
# End Source File
# Begin Source File

SOURCE=.\menuicon.bmp
# End Source File
# Begin Source File

SOURCE=.\Odbcext.rcv
# End Source File
# Begin Source File

SOURCE=.\Paste.bmp
# End Source File
# Begin Source File

SOURCE=.\Redo.bmp
# End Source File
# Begin Source File

SOURCE=.\Remreld.bmp
# End Source File
# Begin Source File

SOURCE=.\Remrelf.bmp
# End Source File
# Begin Source File

SOURCE=.\Remrelu.bmp
# End Source File
# Begin Source File

SOURCE=.\Remrelx.bmp
# End Source File
# Begin Source File

SOURCE=.\Sortasc.bmp
# End Source File
# Begin Source File

SOURCE=.\Sortdes.bmp
# End Source File
# Begin Source File

SOURCE=.\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Undo.bmp
# End Source File
# Begin Source File

SOURCE=.\Whereprp.rgs
# End Source File
# Begin Source File

SOURCE=.\Xtension.ico
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\ODBCEXT.TPL

!IF  "$(CFG)" == "Odbcext - Win32 Release"

USERDEP__ODBCE="makefile"	
# Begin Custom Build
InputPath=.\ODBCEXT.TPL

"odbcext.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile odbcext.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Odbcext - Win32 Debug"

USERDEP__ODBCE="makefile"	
# Begin Custom Build
InputPath=.\ODBCEXT.TPL

"odbcext.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile odbcext.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ODBCEXTV.TPL

!IF  "$(CFG)" == "Odbcext - Win32 Release"

USERDEP__ODBCEX="makefile"	
# Begin Custom Build
InputPath=.\ODBCEXTV.TPL

"odbcext.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile odbcext.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Odbcext - Win32 Debug"

USERDEP__ODBCEX="makefile"	
# Begin Custom Build
InputPath=.\ODBCEXTV.TPL

"odbcext.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile odbcext.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "Odbcext - Win32 Release"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"vers32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile vers32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Odbcext - Win32 Debug"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"vers32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile vers32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\fakename.txt
# End Source File
# End Target
# End Project
