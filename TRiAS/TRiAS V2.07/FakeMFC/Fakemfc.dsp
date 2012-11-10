# Microsoft Developer Studio Project File - Name="fakemfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=fakemfc - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fakemfc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fakemfc.mak" CFG="fakemfc - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fakemfc - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fakemfc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/FakeMFC", ZJDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /Yu"fakemfcp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 stdcppr.lib ospace2r.lib netapi32.lib largeint.lib /nologo /dll /machine:I386 /out:".\Release\fakemfc.ext" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetPath=.\Release\fakemfc.ext
TargetName=fakemfc
InputPath=.\Release\fakemfc.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_ATL_SINGLETHREAD" /D "_AFXEXT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /FR /Yu"fakemfcp.hxx" /Fd".\Debug\fakemfcd.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 stdcppd.lib ospace2d.lib netapi32.lib largeint.lib /nologo /dll /debug /machine:I386 /out:".\Debug\fakemfcd.ext" /stub:"rights.exe" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetPath=.\Debug\fakemfcd.ext
TargetName=fakemfcd
InputPath=.\Debug\fakemfcd.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" c:\trias.mvc\trias200

# End Custom Build

!ENDIF 

# Begin Target

# Name "fakemfc - Win32 Release"
# Name "fakemfc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AuxUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\Bildobj.cpp
# End Source File
# Begin Source File

SOURCE=.\Cimpxtsn.cxx
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CoordStatics.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateNewParamWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateNewWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\DispUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\dllbindx.cpp
# End Source File
# Begin Source File

SOURCE=.\dllfloat.cpp
# End Source File
# Begin Source File

SOURCE=.\Dummy2.cxx
# End Source File
# Begin Source File

SOURCE=.\Dummy3.cxx
# End Source File
# Begin Source File

SOURCE=.\Dummy4.cxx
# End Source File
# Begin Source File

SOURCE=.\Extreg.cxx
# End Source File
# Begin Source File

SOURCE=.\Fakemfc.def
# End Source File
# Begin Source File

SOURCE=.\Fakemfc.rc
# End Source File
# Begin Source File

SOURCE=.\Fakemfcp.cxx
# ADD CPP /Yc"fakemfcp.hxx"
# End Source File
# Begin Source File

SOURCE=.\Fakemfcx.cxx

!IF  "$(CFG)" == "fakemfc - Win32 Release"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# ADD CPP /Gi-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hdrentrx.cpp
# End Source File
# Begin Source File

SOURCE=.\Impxtcf.cxx
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# ADD CPP /Gi-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectAdvancedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropActBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\Propset.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
# End Source File
# Begin Source File

SOURCE=.\SCROLTIP.CPP
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Statpage.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\summary.cxx
# End Source File
# Begin Source File

SOURCE=.\Summinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Summpage.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# ADD CPP /Gi-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Toolbar.idl

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# Begin Custom Build - Running MIDL ...
OutDir=.\.\Release
InputPath=.\Toolbar.idl
InputName=Toolbar

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /old /win32 /tlb $(OutDir)/$(InputName).tlb $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# Begin Custom Build - Running MIDL ...
OutDir=.\.\Debug
InputPath=.\Toolbar.idl
InputName=Toolbar

BuildCmds= \
	midl /old /win32 /tlb $(OutDir)/$(InputName).tlb /h\
                                 e:\triasdev.mvc\include\DToolBar.h /iid\
                                 "e:\triasdev.mvc\include\$(InputName)_i.c" $(InputPath)

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\include\DToolBar.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\include\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ToolBarButton.cpp
# ADD CPP /D "EBWIN32"
# End Source File
# Begin Source File

SOURCE=.\ToolbarsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASBarCont.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASBarObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASButtonCont.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCmdUI.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDoc.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASDocTempl.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\triasext.cxx
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Trias\Tips\triastip.hdr
# End Source File
# Begin Source File

SOURCE=..\..\Trias\Tips\Triastip.tpl
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASView.cpp

!IF  "$(CFG)" == "fakemfc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ViewComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.cpp
# End Source File
# Begin Source File

SOURCE=.\Xtencunk.cxx
# End Source File
# Begin Source File

SOURCE=.\ZoomComboBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\Bildobj.h
# End Source File
# Begin Source File

SOURCE=.\CIMPXTSN.HXX
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\CoordStatics.h
# End Source File
# Begin Source File

SOURCE=.\CreateNewParamWiz.h
# End Source File
# Begin Source File

SOURCE=.\CreateNewWiz.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ctf.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\ctfm.hxx
# End Source File
# Begin Source File

SOURCE=.\DispUIOwner.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\dllbindx.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Eonrguid.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Errcodes.hxx
# End Source File
# Begin Source File

SOURCE=.\fakemfc.hm
# End Source File
# Begin Source File

SOURCE=.\Fakemfc.hxx
# End Source File
# Begin Source File

SOURCE=.\Fakemfcp.hxx
# End Source File
# Begin Source File

SOURCE=.\fmfcguid.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Hdrentrx.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\ibscript.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ienumobj.hxx
# End Source File
# Begin Source File

SOURCE=.\Impxtcf.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ipropseq.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ixtensn.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\IXTNEXT.HXX
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\MainUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectAdvancedDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\OBJCONTX.HXX
# End Source File
# Begin Source File

SOURCE=.\PropActBase.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\propactn.h
# End Source File
# Begin Source File

SOURCE=.\propertychoice.h
# End Source File
# Begin Source File

SOURCE=.\Propset.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\registrx.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\SrChoice.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\statpage.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\summary.hxx
# End Source File
# Begin Source File

SOURCE=.\summcf.hxx
# End Source File
# Begin Source File

SOURCE=.\Summinfo.h
# End Source File
# Begin Source File

SOURCE=.\summpage.h
# End Source File
# Begin Source File

SOURCE=.\Syncthrd.hxx
# End Source File
# Begin Source File

SOURCE=.\ThisDll.h
# End Source File
# Begin Source File

SOURCE=.\tipdlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarButton.h
# End Source File
# Begin Source File

SOURCE=.\toolbarsdlg.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\TrCatIDs.h
# End Source File
# Begin Source File

SOURCE=.\TRiASBarCont.h
# End Source File
# Begin Source File

SOURCE=.\TRiASBarObj.h
# End Source File
# Begin Source File

SOURCE=.\TRiASButtonCont.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCmdUI.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDoc.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDocTempl.h
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\TRiASStatusObj.h
# End Source File
# Begin Source File

SOURCE=.\TRiASToolBar.h
# End Source File
# Begin Source File

SOURCE=.\TRiASView.h
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\ViewComboBox.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDlg.h
# End Source File
# Begin Source File

SOURCE=.\WelcomePage.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtencunk.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Xtension.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtensnm.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Xtensnn.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Xtensnx.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnaux.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnguid.h
# End Source File
# Begin Source File

SOURCE=.\zoomcombobox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Copy of Toolneu1.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\dataimpo.ico
# End Source File
# Begin Source File

SOURCE=.\Docbuch.ico
# End Source File
# Begin Source File

SOURCE=.\res\editnew.ico
# End Source File
# Begin Source File

SOURCE=.\res\fakemfc.ico
# End Source File
# Begin Source File

SOURCE=.\res\fullscrn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoclass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoobjec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\geoview.bmp
# End Source File
# Begin Source File

SOURCE=.\idc_newp.ico
# End Source File
# Begin Source File

SOURCE=.\idc_open.ico
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\macrobtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\objoper.bmp
# End Source File
# Begin Source File

SOURCE=.\res\standard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SteckBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tool1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool23.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool25.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool26.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool27.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool28.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool29.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool30.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool31.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool33.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool34.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool35.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool36.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool37.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool38.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool39.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool40.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool41.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool42.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool43.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool44.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool45.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool46.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool47.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool48.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tool9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tools.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Topkarte.bmp
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\res\PropertyChoice.rgs
# End Source File
# Begin Source File

SOURCE=.\res\ToolBarButton.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASBarObj.rgs
# End Source File
# Begin Source File

SOURCE=.\res\TRiASButtonCont.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\FAKEMFC.RCV
# End Source File
# Begin Source File

SOURCE=.\Debug\Toolbar.tlb
# End Source File
# Begin Source File

SOURCE=.\Release\Toolbar.tlb
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Idl\TRiASBaseInterfaces.idl

!IF  "$(CFG)" == "fakemfc - Win32 Release"

!ELSEIF  "$(CFG)" == "fakemfc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Ole2auto\WIN32\Triastlb.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Idl\TRiASToolbars.idl
# PROP Exclude_From_Build 1
# End Source File
# End Target
# End Project
# Section fakemfc : {2DCC3987-AA53-11CF-BA69-00AA0018497C}
# 	0:14:EnumToolBars.h:E:\Triasdev.mvc\Xtension\Fakemfc\EnumToolBars.h
# 	0:16:EnumToolBars.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\EnumToolBars.cpp
# 	2:14:EnumToolBars.h:EnumToolBars.h
# 	2:20:CLASS: CEnumToolBars:CEnumToolBars
# 	2:19:Application Include:fakemfc.h
# 	2:16:EnumToolBars.cpp:EnumToolBars.cpp
# End Section
# Section fakemfc : {16E349E0-702C-11CF-A3A9-00A0C9034920}
# 	0:11:PreLoader.h:E:\Triasdev.mvc\Xtension\Fakemfc\PreLoader.h
# 	0:13:PreLoader.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\PreLoader.cpp
# 	2:21:DefaultSinkHeaderFile:preloader.h
# 	2:16:DefaultSinkClass:CPreLoader
# End Section
# Section OLE Controls
# 	{16E349E0-702C-11CF-A3A9-00A0C9034920}
# End Section
# Section fakemfc : {146EA060-702C-11CF-A3A9-00A0C9034920}
# 	2:5:Class:CPreLoader
# 	2:10:HeaderFile:preloader.h
# 	2:8:ImplFile:preloader.cpp
# End Section
# Section fakemfc : {AC9258A4-3558-11CF-BA55-00AA0018497C}
# 	0:8:TipDlg.h:E:\Triasdev.mvc\Xtension\Fakemfc\TipDlg.h
# 	0:10:TipDlg.cpp:E:\Triasdev.mvc\Xtension\Fakemfc\TipDlg.cpp
# 	1:17:CG_IDS_DIDYOUKNOW:106
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:105
# 	1:18:CG_IDS_TIPOFTHEDAY:104
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:109
# 	1:19:CG_IDP_FILE_CORRUPT:108
# 	1:7:IDD_TIP:103
# 	1:13:IDB_LIGHTBULB:102
# 	1:18:CG_IDS_FILE_ABSENT:107
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
# Section fakemfc : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:26:CG_IDR_POPUP_TRIASTOOL_BAR:22115
# End Section
