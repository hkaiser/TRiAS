# Microsoft Developer Studio Project File - Name="gak" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gak - Win32 Debug Export
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gak.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gak.mak" CFG="gak - Win32 Debug Export"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gak - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gak - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "gak - Win32 Debug Export" (based on "Win32 (x86) Application")
!MESSAGE "gak - Win32 Release Export" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gak - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /D "_WITHPARAEXPORTED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /stub:"rights.exe"
# SUBTRACT LINK32 /incremental:yes /map /debug

!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /D "_WITHPARAEXPORTED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /stub:"rights.exe"

!ELSEIF  "$(CFG)" == "gak - Win32 Debug Export"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gak___Win32_Debug_Export"
# PROP BASE Intermediate_Dir "gak___Win32_Debug_Export"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "gak___Win32_Debug_Export"
# PROP Intermediate_Dir "gak___Win32_Debug_Export"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /D "_WITHPARAEXPORTED" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /D "_WITHPARAEXPORTED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /stub:"rights.exe"
# ADD LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /stub:"rights.exe"

!ELSEIF  "$(CFG)" == "gak - Win32 Release Export"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gak___Win32_Release_Export"
# PROP BASE Intermediate_Dir "gak___Win32_Release_Export"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "gak___Win32_Release_Export"
# PROP Intermediate_Dir "gak___Win32_Release_Export"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MDB_VERSION20" /D "_BRANDENBURG" /D "_WITHPARAEXPORTED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /stub:"rights.exe"
# SUBTRACT BASE LINK32 /incremental:yes
# ADD LINK32 crpe32m.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /stub:"rights.exe"
# SUBTRACT LINK32 /incremental:yes

!ENDIF 

# Begin Target

# Name "gak - Win32 Release"
# Name "gak - Win32 Debug"
# Name "gak - Win32 Debug Export"
# Name "gak - Win32 Release Export"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AbfallP.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfPage.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfView.cpp
# End Source File
# Begin Source File

SOURCE=.\about.cpp
# End Source File
# Begin Source File

SOURCE=.\Afidlg.cpp
# End Source File
# Begin Source File

SOURCE=.\anfpage.cpp
# End Source File
# Begin Source File

SOURCE=.\BetrPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BrancheP.cpp
# End Source File
# Begin Source File

SOURCE=.\BranPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeNr.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Compact.cpp
# End Source File
# Begin Source File

SOURCE=.\daotools.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumExt.cpp
# End Source File
# Begin Source File

SOURCE=.\DoImpPge.cpp
# End Source File
# Begin Source File

SOURCE=.\EnterNr.cpp
# End Source File
# Begin Source File

SOURCE=.\EntPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Entsorger1.cpp
# End Source File
# Begin Source File

SOURCE=.\Entspage.cpp
# End Source File
# Begin Source File

SOURCE=.\ErzFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ErzPar.cpp
# End Source File
# Begin Source File

SOURCE=.\ErzSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Exportre.cpp
# End Source File
# Begin Source File

SOURCE=.\FeldInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\firmpage.cpp
# End Source File
# Begin Source File

SOURCE=.\gak.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\gak.hpj

!IF  "$(CFG)" == "gak - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "gak - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo GAk hpj 
	"$(ProjDir)\makehelp.bat" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gak - Win32 Debug Export"

# Begin Custom Build - Making help file...
OutDir=.\gak___Win32_Debug_Export
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo GAk hpj 
	"$(ProjDir)\makehelp.bat" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gak - Win32 Release Export"

# Begin Custom Build - Making help file...
OutDir=.\gak___Win32_Release_Export
ProjDir=.
TargetName=Gak
InputPath=.\hlp\gak.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gak.rc
# End Source File
# Begin Source File

SOURCE=.\gakDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Gaksete.cpp
# End Source File
# Begin Source File

SOURCE=.\gakView.cpp
# End Source File
# Begin Source File

SOURCE=.\GebietP.cpp
# End Source File
# Begin Source File

SOURCE=.\Getodbci.cpp
# End Source File
# Begin Source File

SOURCE=.\Importty.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpParPg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpResPg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImprtDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImpSumPg.cpp
# End Source File
# Begin Source File

SOURCE=.\InTablPg.cpp
# End Source File
# Begin Source File

SOURCE=.\KreisSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Listext.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NewQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\Numedit.cpp
# End Source File
# Begin Source File

SOURCE=.\OutTbPg.cpp
# End Source File
# Begin Source File

SOURCE=.\PartPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Peplus.cpp
# End Source File
# Begin Source File

SOURCE=.\Progress.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryPar.cpp
# End Source File
# Begin Source File

SOURCE=.\querypr.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Recview.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultP.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchSe.cpp
# End Source File
# Begin Source File

SOURCE=.\SearRes.cpp
# End Source File
# Begin Source File

SOURCE=.\Selectex.cpp
# End Source File
# Begin Source File

SOURCE=.\SelNum.cpp
# End Source File
# Begin Source File

SOURCE=.\SelNumberDlgUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\StatBarE.cpp
# End Source File
# Begin Source File

SOURCE=.\StatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strutil.cpp
# End Source File
# Begin Source File

SOURCE=.\TablNDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TestRS.cpp
# End Source File
# Begin Source File

SOURCE=.\textClipboard.cpp
# End Source File
# Begin Source File

SOURCE=.\TransPge.cpp
# End Source File
# Begin Source File

SOURCE=.\UserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\waitcext.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AbfallP.h
# End Source File
# Begin Source File

SOURCE=.\Abfdoc.h
# End Source File
# Begin Source File

SOURCE=.\Abfframe.h
# End Source File
# Begin Source File

SOURCE=.\AbfPage.h
# End Source File
# Begin Source File

SOURCE=.\Abfsetex.h
# End Source File
# Begin Source File

SOURCE=.\Abfsheet.h
# End Source File
# Begin Source File

SOURCE=.\AbfView.h
# End Source File
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\Afidlg.h
# End Source File
# Begin Source File

SOURCE=.\Anfpage.h
# End Source File
# Begin Source File

SOURCE=.\BetrPage.h
# End Source File
# Begin Source File

SOURCE=.\BrancheP.h
# End Source File
# Begin Source File

SOURCE=.\Branpage.h
# End Source File
# Begin Source File

SOURCE=.\Changenr.h
# End Source File
# Begin Source File

SOURCE=.\Childfrm.h
# End Source File
# Begin Source File

SOURCE=.\Compact.h
# End Source File
# Begin Source File

SOURCE=.\Daotools.h
# End Source File
# Begin Source File

SOURCE=.\Documext.h
# End Source File
# Begin Source File

SOURCE=.\Doimppge.h
# End Source File
# Begin Source File

SOURCE=.\Enternr.h
# End Source File
# Begin Source File

SOURCE=.\EntPage.h
# End Source File
# Begin Source File

SOURCE=.\Entsorger1.h
# End Source File
# Begin Source File

SOURCE=.\Entspage.h
# End Source File
# Begin Source File

SOURCE=.\Erzframe.h
# End Source File
# Begin Source File

SOURCE=.\ErzPar.h
# End Source File
# Begin Source File

SOURCE=.\Erzsheet.h
# End Source File
# Begin Source File

SOURCE=.\Exportre.h
# End Source File
# Begin Source File

SOURCE=.\FeldInfo.h
# End Source File
# Begin Source File

SOURCE=.\Firmpage.h
# End Source File
# Begin Source File

SOURCE=.\Gak.h
# End Source File
# Begin Source File

SOURCE=.\Gakdoc.h
# End Source File
# Begin Source File

SOURCE=.\Gaksete.h
# End Source File
# Begin Source File

SOURCE=.\gakView.h
# End Source File
# Begin Source File

SOURCE=.\GebietP.h
# End Source File
# Begin Source File

SOURCE=.\Getodbci.h
# End Source File
# Begin Source File

SOURCE=.\Importty.h
# End Source File
# Begin Source File

SOURCE=.\Impparpg.h
# End Source File
# Begin Source File

SOURCE=.\Impquery.h
# End Source File
# Begin Source File

SOURCE=.\Imprespg.h
# End Source File
# Begin Source File

SOURCE=.\Imprtdlg.h
# End Source File
# Begin Source File

SOURCE=.\Impsumpg.h
# End Source File
# Begin Source File

SOURCE=.\Intablpg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Newquery.h
# End Source File
# Begin Source File

SOURCE=.\numedit.h
# End Source File
# Begin Source File

SOURCE=.\Outtbpg.h
# End Source File
# Begin Source File

SOURCE=.\Partpage.h
# End Source File
# Begin Source File

SOURCE=.\peplus.h
# End Source File
# Begin Source File

SOURCE=.\Progress.h
# End Source File
# Begin Source File

SOURCE=.\Querydlg.h
# End Source File
# Begin Source File

SOURCE=.\Querypar.h
# End Source File
# Begin Source File

SOURCE=.\Queryres.h
# End Source File
# Begin Source File

SOURCE=.\Recview.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\resource.hm
# End Source File
# Begin Source File

SOURCE=.\ResultP.h
# End Source File
# Begin Source File

SOURCE=.\Searchse.h
# End Source File
# Begin Source File

SOURCE=.\Searres.h
# End Source File
# Begin Source File

SOURCE=.\Selectex.h
# End Source File
# Begin Source File

SOURCE=.\Selnum.h
# End Source File
# Begin Source File

SOURCE=.\SelNumberDlgUsage.h
# End Source File
# Begin Source File

SOURCE=.\Statbare.h
# End Source File
# Begin Source File

SOURCE=.\Statdlg.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TablNDlg.h
# End Source File
# Begin Source File

SOURCE=.\TestRS.h
# End Source File
# Begin Source File

SOURCE=.\TextClipboard.h
# End Source File
# Begin Source File

SOURCE=.\TransPge.h
# End Source File
# Begin Source File

SOURCE=.\Userinfo.h
# End Source File
# Begin Source File

SOURCE=.\Waitcext.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\artchad.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artchaf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artchau.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artchax.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artdeld.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artdelf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artdelu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artdelx.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ARTNEUD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artneuf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artneuu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\artneux.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gak.rc2
# End Source File
# Begin Source File

SOURCE=.\res\gakDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\imageli.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "RS Header"

# PROP Default_Filter "*.h,*.hpp"
# Begin Source File

SOURCE=.\Abfarset.h
# End Source File
# Begin Source File

SOURCE=.\AbfSet.h
# End Source File
# Begin Source File

SOURCE=.\Entsset.h
# End Source File
# Begin Source File

SOURCE=.\FirmaSet.h
# End Source File
# Begin Source File

SOURCE=.\Gakset.h
# End Source File
# Begin Source File

SOURCE=.\KreisSet.h
# End Source File
# Begin Source File

SOURCE=.\Selset.h
# End Source File
# Begin Source File

SOURCE=.\Transset.h
# End Source File
# End Group
# Begin Group "RS Source"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\AbfArSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AbfSetEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EntsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\FirmaSet.cpp
# End Source File
# Begin Source File

SOURCE=.\gakSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Selset.cpp
# End Source File
# Begin Source File

SOURCE=.\TransSet.cpp
# End Source File
# End Group
# Begin Group "Allg. Hilfe"

# PROP Default_Filter "*.h,*.hpp,*.cpp"
# Begin Source File

SOURCE=.\tmpswitch.h
# End Source File
# End Group
# Begin Group "Progspez. Helper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\progsetting.h
# End Source File
# End Group
# Begin Group "Abgl Source"

# PROP Default_Filter "*.cpp;*.c"
# Begin Source File

SOURCE=.\ABFALSET.CPP
# End Source File
# Begin Source File

SOURCE=.\ABFARMAP.CPP
# End Source File
# Begin Source File

SOURCE=.\ABFARSETODBC.CPP
# End Source File
# Begin Source File

SOURCE=.\ABFARTPA.CPP
# End Source File
# Begin Source File

SOURCE=.\ABFMAP.CPP
# End Source File
# Begin Source File

SOURCE=.\BGSSET.CPP
# End Source File
# Begin Source File

SOURCE=.\COLUMNST.CPP
# End Source File
# Begin Source File

SOURCE=.\DOABGLEI.CPP
# End Source File
# Begin Source File

SOURCE=.\error.cpp
# End Source File
# Begin Source File

SOURCE=.\ERZEUSET.CPP
# End Source File
# Begin Source File

SOURCE=.\ERZINFO.CPP
# End Source File
# Begin Source File

SOURCE=.\ERZLISTE.CPP
# End Source File
# Begin Source File

SOURCE=.\OUTSET.CPP
# End Source File
# Begin Source File

SOURCE=.\PARAMS.CPP
# End Source File
# Begin Source File

SOURCE=.\RECSET.CPP
# End Source File
# Begin Source File

SOURCE=.\REPTABLE.CPP
# End Source File
# Begin Source File

SOURCE=.\RESDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.CPP
# End Source File
# Begin Source File

SOURCE=.\seltable.cpp
# End Source File
# Begin Source File

SOURCE=.\TABLESET.CPP
# End Source File
# End Group
# Begin Group "Abgl Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ABFALSET.H
# End Source File
# Begin Source File

SOURCE=.\ABFARMAP.H
# End Source File
# Begin Source File

SOURCE=.\ABFARSETODBC.H
# End Source File
# Begin Source File

SOURCE=.\ABFARTPA.H
# End Source File
# Begin Source File

SOURCE=.\ABFMAP.H
# End Source File
# Begin Source File

SOURCE=.\BGSSET.H
# End Source File
# Begin Source File

SOURCE=.\COLUMNST.H
# End Source File
# Begin Source File

SOURCE=.\DOABGLEI.H
# End Source File
# Begin Source File

SOURCE=.\ERZEUSET.H
# End Source File
# Begin Source File

SOURCE=.\ERZINFO.H
# End Source File
# Begin Source File

SOURCE=.\ERZLISTE.H
# End Source File
# Begin Source File

SOURCE=.\OUTSET.H
# End Source File
# Begin Source File

SOURCE=.\PARAMS.H
# End Source File
# Begin Source File

SOURCE=.\RECSET.H
# End Source File
# Begin Source File

SOURCE=.\REPTABLE.H
# End Source File
# Begin Source File

SOURCE=.\RESDLG.H
# End Source File
# Begin Source File

SOURCE=.\SELTABLE.H
# End Source File
# End Group
# Begin Source File

SOURCE=.\bla.txt
# End Source File
# Begin Source File

SOURCE=.\Createta.qrt
# End Source File
# End Target
# End Project
