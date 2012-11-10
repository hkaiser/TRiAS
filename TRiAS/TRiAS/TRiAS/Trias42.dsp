# Microsoft Developer Studio Project File - Name="Trias32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TRIAS32 - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Trias42.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias42.mak" CFG="TRIAS32 - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Trias32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS", AWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /Yu"triaspre.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG" /d "_GERMAN_RESOURCES" /d "_NEWORMENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ShFolder.Lib delayimp.lib TRiASTlb.lib trias323.lib trias322.lib trias321.lib tfrmlr.lib lol.lib tfrmwork.lib containr.lib ospace5r.lib shlwapi.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /machine:I386 /out:".\Release\TRiAS32.exe" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:crp32dll.dll /delay:unload /SUBSYSTEM:windows,4.0 /delayload:shlwapi.dll /delayload:shell32.dll /delayload:msvcirt.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\TRiAS32.exe
TargetName=TRiAS32
InputPath=.\Release\TRiAS32.exe
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /Fp".\Obj32\Debug\trias32d.pch" /Yu"triaspre.hxx" /Fo".\Obj32\Debug\\" /Fd".\Obj32\Debug\trias32d.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /fo".\Obj32\Debug\TRIAS32.res" /i ".." /d "_DEBUG" /d "_GERMAN_RESOURCES" /d "_NEWORMENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Obj32\Debug\Trias42.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 shlwapi.lib ShFolder.Lib delayimp.lib tfrmld.lib lol50d.lib trias33d.lib trias32d.lib trias31d.lib tfrm32d.lib cont50d.lib ospace5d.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /pdb:".\Obj32\Debug\trias32d.pdb" /debug /machine:I386 /out:".\Obj32\Debug\trias32d.exe" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll /delayload:crp32dll.dll /delay:unload /delayload:shlwapi.dll /SUBSYSTEM:windows,4.0 /WARN:1 /delayload:shell32.dll /delayload:msvcirtd.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Obj32\Debug
TargetPath=.\Obj32\Debug\trias32d.exe
TargetName=trias32d
InputPath=.\Obj32\Debug\trias32d.exe
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Trias32 - Win32 Release"
# Name "Trias32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\alloprop.cxx
# End Source File
# Begin Source File

SOURCE=.\APALWIND.CXX
# End Source File
# Begin Source File

SOURCE=.\AUSSCHN.CXX
# End Source File
# Begin Source File

SOURCE=.\BILDOBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\BMPBOX.CXX
# End Source File
# Begin Source File

SOURCE=.\CLIPBORD.CXX
# End Source File
# Begin Source File

SOURCE=.\COLORBOX.CXX
# End Source File
# Begin Source File

SOURCE=.\DataImport.cpp
# End Source File
# Begin Source File

SOURCE=.\DBOARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\DBObjCom.cpp
# End Source File
# Begin Source File

SOURCE=.\DBOBJEKT.CXX
# End Source File
# Begin Source File

SOURCE=.\DBOGETGI.CXX
# End Source File
# Begin Source File

SOURCE=.\DBOMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\DBOMetaData.cpp
# End Source File
# Begin Source File

SOURCE=.\DBProject.cpp
# End Source File
# Begin Source File

SOURCE=.\DCOLOR.CXX
# End Source File
# Begin Source File

SOURCE=.\DdORWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DELVIEWS.CXX
# End Source File
# Begin Source File

SOURCE=.\docprops.cxx
# End Source File
# Begin Source File

SOURCE=.\dragdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\Drawobj2.cxx
# End Source File
# Begin Source File

SOURCE=.\DRW_OBJ1.CXX
# End Source File
# Begin Source File

SOURCE=.\eallcprp.cxx
# End Source File
# Begin Source File

SOURCE=.\eallprop.cxx
# End Source File
# Begin Source File

SOURCE=.\EditObjProps.cpp
# End Source File
# Begin Source File

SOURCE=.\EDITTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\ENUMFNAM.CXX
# End Source File
# Begin Source File

SOURCE=.\enumobj.cxx
# End Source File
# Begin Source File

SOURCE=.\EXPORT.CXX
# End Source File
# Begin Source File

SOURCE=.\extmain3.cxx
# End Source File
# Begin Source File

SOURCE=.\FEATURE.CXX
# End Source File
# Begin Source File

SOURCE=.\frameevt.cxx
# End Source File
# Begin Source File

SOURCE=.\GeoDBArray.cpp
# End Source File
# Begin Source File

SOURCE=.\IdentCls.cpp
# End Source File
# Begin Source File

SOURCE=.\Identifikator.cpp
# End Source File
# Begin Source File

SOURCE=.\IDENTSEL.CXX
# End Source File
# Begin Source File

SOURCE=.\IENUMSTR.CXX
# End Source File
# Begin Source File

SOURCE=.\Irisevt2.cxx
# End Source File
# Begin Source File

SOURCE=.\Irismai2.cxx
# End Source File
# Begin Source File

SOURCE=.\Irisopn2.cxx
# End Source File
# Begin Source File

SOURCE=.\Irisuti2.cxx
# End Source File
# Begin Source File

SOURCE=.\LDROPSRC.CXX
# End Source File
# Begin Source File

SOURCE=.\LDROPTGT.CXX
# End Source File
# Begin Source File

SOURCE=.\LEGDINFO.CXX
# End Source File
# Begin Source File

SOURCE=.\LEGEND.CXX
# End Source File
# Begin Source File

SOURCE=.\LegendeCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\LEGMERKM.CXX
# End Source File
# Begin Source File

SOURCE=.\Legmerkm.yxx

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# Begin Custom Build - Generating Parser and Lexer Sources ...
InputPath=.\Legmerkm.yxx
InputName=Legmerkm

BuildCmds= \
	fpp -P $(InputPath) > obj32\$(InputName).ypp \
	yxx -ns -nl obj32\$(InputName).ypp \
	sed -e s/yy_export//g legmerkl.hxx > tmp \
	del legmerkl.hxx \
	ren tmp legmerkl.hxx \
	sed -e s/yy_export//g legmerky.hxx > tmp \
	del legmerky.hxx \
	ren tmp legmerky.hxx \
	sed -e s/yy_export//g yy_myref.h > tmp \
	del yy_myref.h \
	ren tmp yy_myref.h \
	

"legmerkl.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerkl.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerky.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerky.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"yy_myref.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

# Begin Custom Build - Generating Parser and Lexer Sources ...
InputPath=.\Legmerkm.yxx
InputName=Legmerkm

BuildCmds= \
	fpp -P $(InputPath) > obj32\$(InputName).ypp \
	yxx -ns -nl obj32\$(InputName).ypp \
	sed -e s/yy_export//g legmerkl.hxx > tmp \
	del legmerkl.hxx \
	ren tmp legmerkl.hxx \
	sed -e s/yy_export//g legmerky.hxx > tmp \
	del legmerky.hxx \
	ren tmp legmerky.hxx \
	sed -e s/yy_export//g yy_myref.h > tmp \
	del yy_myref.h \
	ren tmp yy_myref.h \
	

"legmerkl.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerkl.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerky.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"legmerky.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"yy_myref.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\legmrklp.cxx
# End Source File
# Begin Source File

SOURCE=.\legmrkyp.cxx
# End Source File
# Begin Source File

SOURCE=.\LEGTXTED.CXX
# End Source File
# Begin Source File

SOURCE=.\LEGUTILS.CXX
# End Source File
# Begin Source File

SOURCE=.\LEGWIND.CXX
# End Source File
# Begin Source File

SOURCE=.\license.cxx
# End Source File
# Begin Source File

SOURCE=.\LPALWIND.CXX
# End Source File
# Begin Source File

SOURCE=.\ManageExtDlg.cxx
# End Source File
# Begin Source File

SOURCE=.\masstab2.cpp
# End Source File
# Begin Source File

SOURCE=.\MENUITEM.CXX
# End Source File
# Begin Source File

SOURCE=.\MINITPBD.CXX
# End Source File
# Begin Source File

SOURCE=.\modifyid.cxx
# End Source File
# Begin Source File

SOURCE=.\Mru.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgDumper.cpp

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OBJEKTE.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJMENU.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJMENU1.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJOWNDR.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJPROP.CXX
# End Source File
# Begin Source File

SOURCE=.\OLISTEM.CXX
# End Source File
# Begin Source File

SOURCE=.\OPENDB.CXX
# End Source File
# Begin Source File

SOURCE=.\ORIDENTS.CXX
# End Source File
# Begin Source File

SOURCE=.\OVERVIEW.CXX
# End Source File
# Begin Source File

SOURCE=.\OverviewCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\PALRECT.CXX
# End Source File
# Begin Source File

SOURCE=.\PALWIND.CXX
# End Source File
# Begin Source File

SOURCE=.\pntmasks.cxx
# End Source File
# Begin Source File

SOURCE=.\ppalwndr.cxx
# End Source File
# Begin Source File

SOURCE=.\PrintBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PRINTER.CXX
# End Source File
# Begin Source File

SOURCE=.\PrintLegendLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\PRLAYOUT.CXX

!IF  "$(CFG)" == "Trias32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

# ADD CPP /Ob0

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PRNTABRT.CXX
# End Source File
# Begin Source File

SOURCE=.\PRNTLAYT.CXX
# End Source File
# Begin Source File

SOURCE=.\PRNTPROF.CXX
# End Source File
# Begin Source File

SOURCE=.\PROFILE.CXX
# End Source File
# Begin Source File

SOURCE=.\RECHRES.CXX
# End Source File
# Begin Source File

SOURCE=.\RechResultORWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\RechSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\REGTRIAS.CXX
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\RELOBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\RENDERDB.CXX
# End Source File
# Begin Source File

SOURCE=.\RGB_HSB.CXX
# End Source File
# Begin Source File

SOURCE=.\SAVEOPT.CXX
# End Source File
# Begin Source File

SOURCE=.\SCHRIFT.CXX
# End Source File
# Begin Source File

SOURCE=.\Selectid.cxx
# End Source File
# Begin Source File

SOURCE=.\selectn.cxx
# End Source File
# Begin Source File

SOURCE=.\selnview.cxx
# End Source File
# Begin Source File

SOURCE=.\selprio.cxx
# End Source File
# Begin Source File

SOURCE=.\SHIFT.CXX
# End Source File
# Begin Source File

SOURCE=.\SHIFTOVW.CXX
# End Source File
# Begin Source File

SOURCE=.\SIGHTS.CXX
# End Source File
# Begin Source File

SOURCE=.\SignOnDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\strings.cxx
# End Source File
# Begin Source File

SOURCE=.\TEXTMENU.CXX
# End Source File
# Begin Source File

SOURCE=.\TRANSFRM.CXX
# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS32.DEF
# End Source File
# Begin Source File

SOURCE=.\obj32\Trias32.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# SUBTRACT BASE RSC /i ".."
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# SUBTRACT RSC /i ".."
# End Source File
# Begin Source File

SOURCE=.\TRIASPRE.CXX
# ADD CPP /Yc"triaspre.hxx"
# End Source File
# Begin Source File

SOURCE=.\TIPS\triastip.hdr
# End Source File
# Begin Source File

SOURCE=.\TIPS\Triastip.tpl
# End Source File
# Begin Source File

SOURCE=.\undodlg.cxx
# End Source File
# Begin Source File

SOURCE=.\UndoRedoDetails.cpp

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\viewdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\VIEWTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\Vispara3.cxx
# End Source File
# Begin Source File

SOURCE=.\XmlPropertySequences.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlPropertySequencesORWnd.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\alloprop.hxx
# End Source File
# Begin Source File

SOURCE=.\ARRAY.HXX
# End Source File
# Begin Source File

SOURCE=.\AUSSCHN.H
# End Source File
# Begin Source File

SOURCE=.\AUSSCHN.HXX
# End Source File
# Begin Source File

SOURCE=.\BILDOBJ.HXX
# End Source File
# Begin Source File

SOURCE=.\clbmpobj.hxx
# End Source File
# Begin Source File

SOURCE=.\CloseCommandWrapper.h
# End Source File
# Begin Source File

SOURCE=.\COLORBOX.HXX
# End Source File
# Begin Source File

SOURCE=.\cordprop.hxx
# End Source File
# Begin Source File

SOURCE=.\CPTriastlb.h
# End Source File
# Begin Source File

SOURCE=.\CPTriastlb2.h
# End Source File
# Begin Source File

SOURCE=..\Include\CSPoint.h
# End Source File
# Begin Source File

SOURCE=..\Include\CSRectGeom.h
# End Source File
# Begin Source File

SOURCE=.\Dboarray.hxx
# End Source File
# Begin Source File

SOURCE=.\dbobject.h
# End Source File
# Begin Source File

SOURCE=.\DBOContext.h
# End Source File
# Begin Source File

SOURCE=.\dcbmpwnd.hxx
# End Source File
# Begin Source File

SOURCE=.\DCOLOR.HXX
# End Source File
# Begin Source File

SOURCE=.\DdORWnd.h
# End Source File
# Begin Source File

SOURCE=.\DELVIEWS.H
# End Source File
# Begin Source File

SOURCE=.\DELVIEWS.HXX
# End Source File
# Begin Source File

SOURCE=.\docprops.hxx
# End Source File
# Begin Source File

SOURCE=.\DragDropCallback.h
# End Source File
# Begin Source File

SOURCE=.\Draw_obj.hxx
# End Source File
# Begin Source File

SOURCE=.\DrawingStatusWrapper.h
# End Source File
# Begin Source File

SOURCE=.\Drw_obj1.hxx
# End Source File
# Begin Source File

SOURCE=.\eallcprp.hxx
# End Source File
# Begin Source File

SOURCE=.\EALLPROP.HXX
# End Source File
# Begin Source File

SOURCE=.\editro.hxx
# End Source File
# Begin Source File

SOURCE=.\EDITTEXT.H
# End Source File
# Begin Source File

SOURCE=.\EDITTEXT.HXX
# End Source File
# Begin Source File

SOURCE=.\ENUMFNAM.HXX
# End Source File
# Begin Source File

SOURCE=.\Expdlg.hxx
# End Source File
# Begin Source File

SOURCE=.\EXPORT.H
# End Source File
# Begin Source File

SOURCE=.\Export.hxx
# End Source File
# Begin Source File

SOURCE=.\EXPSTAT.HXX
# End Source File
# Begin Source File

SOURCE=.\EXPTRANS.H
# End Source File
# Begin Source File

SOURCE=.\EXPTRANS.HXX
# End Source File
# Begin Source File

SOURCE=.\EXTLOAD.H
# End Source File
# Begin Source File

SOURCE=.\FEATURE.HXX
# End Source File
# Begin Source File

SOURCE=.\IdentCls.h
# End Source File
# Begin Source File

SOURCE=.\Identifikator.h
# End Source File
# Begin Source File

SOURCE=.\IDENTSEL.H
# End Source File
# Begin Source File

SOURCE=.\IDENTSEL.HXX
# End Source File
# Begin Source File

SOURCE=.\IENUMSTR.HXX
# End Source File
# Begin Source File

SOURCE=.\impdlg.hxx
# End Source File
# Begin Source File

SOURCE=.\INFODLG.H
# End Source File
# Begin Source File

SOURCE=.\Iris.h
# End Source File
# Begin Source File

SOURCE=.\Iris.hxx
# End Source File
# Begin Source File

SOURCE=.\Iriswind.hxx
# End Source File
# Begin Source File

SOURCE=.\LayoutStyles.h
# End Source File
# Begin Source File

SOURCE=.\LDROPSRC.HXX
# End Source File
# Begin Source File

SOURCE=.\LDROPTGT.HXX
# End Source File
# Begin Source File

SOURCE=.\Legdinfo.hxx
# End Source File
# Begin Source File

SOURCE=.\LEGDINFO.INL
# End Source File
# Begin Source File

SOURCE=.\LEGENDE.H
# End Source File
# Begin Source File

SOURCE=.\Legende.hxx
# End Source File
# Begin Source File

SOURCE=.\LegendeCallback.h
# End Source File
# Begin Source File

SOURCE=.\LEGMERKA.HXX
# End Source File
# Begin Source File

SOURCE=.\LEGMERKM.HXX
# End Source File
# Begin Source File

SOURCE=.\LEGTXTED.HXX
# End Source File
# Begin Source File

SOURCE=.\LEGWIND.HXX
# End Source File
# Begin Source File

SOURCE=.\license.hxx
# End Source File
# Begin Source File

SOURCE=..\TRiASCFG\LoadXmlService.h
# End Source File
# Begin Source File

SOURCE=.\ManageExtDlg.h
# End Source File
# Begin Source File

SOURCE=.\MENUITEM.H
# End Source File
# Begin Source File

SOURCE=.\MENUITEM.HXX
# End Source File
# Begin Source File

SOURCE=.\MERKEDIT.H
# End Source File
# Begin Source File

SOURCE=.\Merkedit.hxx
# End Source File
# Begin Source File

SOURCE=.\Minitpbd.hxx
# End Source File
# Begin Source File

SOURCE=.\MKRECH.H
# End Source File
# Begin Source File

SOURCE=.\Mru.h
# End Source File
# Begin Source File

SOURCE=.\NEWID.H
# End Source File
# Begin Source File

SOURCE=.\NEWID.HXX
# End Source File
# Begin Source File

SOURCE=.\OBJEKTE.H
# End Source File
# Begin Source File

SOURCE=.\Objekte.hxx
# End Source File
# Begin Source File

SOURCE=.\OBJOWNDR.HXX
# End Source File
# Begin Source File

SOURCE=.\OBJPROP.H
# End Source File
# Begin Source File

SOURCE=.\Objprop.hxx
# End Source File
# Begin Source File

SOURCE=..\Xtension\Statist\ObjPropTree.h
# End Source File
# Begin Source File

SOURCE=.\OPENDB.H
# End Source File
# Begin Source File

SOURCE=.\Opendb.hxx
# End Source File
# Begin Source File

SOURCE=.\ORIDENTS.HXX
# End Source File
# Begin Source File

SOURCE=.\ORIDENTS.INL
# End Source File
# Begin Source File

SOURCE=.\OVERVIEW.H
# End Source File
# Begin Source File

SOURCE=.\OVERVIEW.HXX
# End Source File
# Begin Source File

SOURCE=.\OverviewCallback.h
# End Source File
# Begin Source File

SOURCE=.\PALRECT.HXX
# End Source File
# Begin Source File

SOURCE=.\PALWIND.H
# End Source File
# Begin Source File

SOURCE=.\PALWIND.HXX
# End Source File
# Begin Source File

SOURCE=.\PrintBase.h
# End Source File
# Begin Source File

SOURCE=.\PRIORITY.H
# End Source File
# Begin Source File

SOURCE=.\Prlayhlp.hxx
# End Source File
# Begin Source File

SOURCE=.\Prlayout.hxx
# End Source File
# Begin Source File

SOURCE=.\prlaytyp.hxx
# End Source File
# Begin Source File

SOURCE=.\PRNTABRT.H
# End Source File
# Begin Source File

SOURCE=.\PRNTABRT.HXX
# End Source File
# Begin Source File

SOURCE=.\PRNTLAYT.H
# End Source File
# Begin Source File

SOURCE=.\PRNTLAYT.HXX
# End Source File
# Begin Source File

SOURCE=.\PRNTPROF.HXX
# End Source File
# Begin Source File

SOURCE=.\punktstr.h
# End Source File
# Begin Source File

SOURCE=.\queryfld.hxx
# End Source File
# Begin Source File

SOURCE=.\RECHRES.H
# End Source File
# Begin Source File

SOURCE=.\RECHRES.HXX
# End Source File
# Begin Source File

SOURCE=.\RechResultORWnd.h
# End Source File
# Begin Source File

SOURCE=.\regprog.h
# End Source File
# Begin Source File

SOURCE=.\RELOBJ.HXX
# End Source File
# Begin Source File

SOURCE=.\RENDERDB.HXX
# End Source File
# Begin Source File

SOURCE=.\SAVEOPT.H
# End Source File
# Begin Source File

SOURCE=.\Saveopt.hxx
# End Source File
# Begin Source File

SOURCE=.\SCHRIFT.HXX
# End Source File
# Begin Source File

SOURCE=.\Selectid.hxx
# End Source File
# Begin Source File

SOURCE=.\selectn.hxx
# End Source File
# Begin Source File

SOURCE=.\SELIDENT.H
# End Source File
# Begin Source File

SOURCE=.\selnview.hxx
# End Source File
# Begin Source File

SOURCE=.\selprio.hxx
# End Source File
# Begin Source File

SOURCE=.\Shift.hxx
# End Source File
# Begin Source File

SOURCE=.\SHIFTOVW.HXX
# End Source File
# Begin Source File

SOURCE=.\SIGNON.H
# End Source File
# Begin Source File

SOURCE=.\Signon.hxx
# End Source File
# Begin Source File

SOURCE=.\SIGNON1.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\strings.h
# End Source File
# Begin Source File

SOURCE=.\TENUMS.H
# End Source File
# Begin Source File

SOURCE=.\TOOLS.HXX
# End Source File
# Begin Source File

SOURCE=.\TraceTRiAS.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMainConfig.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMainConfigVersion.h
# End Source File
# Begin Source File

SOURCE=.\Triaspre.hxx
# End Source File
# Begin Source File

SOURCE=.\triasres.h
# End Source File
# Begin Source File

SOURCE=.\obj32\TRiASVersion.h
# End Source File
# Begin Source File

SOURCE=.\undodlg.hxx
# End Source File
# Begin Source File

SOURCE=.\UndoRedoDetails.h
# End Source File
# Begin Source File

SOURCE=.\updnedit.h
# End Source File
# Begin Source File

SOURCE=.\viewdrop.h
# End Source File
# Begin Source File

SOURCE=.\Viewtree.hxx
# End Source File
# Begin Source File

SOURCE=.\VIEWTREE.INL
# End Source File
# Begin Source File

SOURCE=.\vispara3.hxx
# End Source File
# Begin Source File

SOURCE=.\VISPARAM.H
# End Source File
# Begin Source File

SOURCE=.\WinMMWrap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BMP\15gesamt.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\20gesamt.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\32_blau.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\32_schwarz.ico
# End Source File
# Begin Source File

SOURCE=.\BMP\32gesamt.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\BLINKEL.BMP
# End Source File
# Begin Source File

SOURCE=.\obj32\BUCH.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\BUCHICON.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\Buchv2.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\Buchv3.ico
# End Source File
# Begin Source File

SOURCE=.\BMP\catid_se.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\catid_to.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\ccplugin.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\ConnectFilterDlg.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\ConnectFilterDlgMask.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\DIRISICO.ICO
# End Source File
# Begin Source File

SOURCE=.\BMP\down.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\down.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\downdis.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\downfoc.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\downfocs.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\downsel.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\downsel.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\header.bmp
# End Source File
# Begin Source File

SOURCE=C:\triasdev.mvc\trias\bmp\headerst.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\headerst.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\hourglass.ani
# End Source File
# Begin Source File

SOURCE=.\obj32\IDT1024.DBD
# End Source File
# Begin Source File

SOURCE=.\obj32\IDT1024C.DBD
# End Source File
# Begin Source File

SOURCE=.\obj32\INVPAT.BMP
# End Source File
# Begin Source File

SOURCE=.\obj32\Krone.bm_
# End Source File
# Begin Source File

SOURCE=.\obj32\legend.ico
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendeH.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendeQ.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendLayoutH1.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendLayoutH2.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendLayoutQ1.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\LegendLayoutQ2.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\license.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\LUPE.CUR
# End Source File
# Begin Source File

SOURCE=.\obj32\LUPE.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\MOVE.CUR
# End Source File
# Begin Source File

SOURCE=.\PKTZUORD\offset15.bin
# End Source File
# Begin Source File

SOURCE=..\TRIAS\PKTZUORD\offset15.bin
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\PKTZUORD\offset15.bin
# End Source File
# Begin Source File

SOURCE=.\PKTZUORD\offset23.bin
# End Source File
# Begin Source File

SOURCE=..\TRIAS\PKTZUORD\offset23.bin
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\PKTZUORD\offset23.bin
# End Source File
# Begin Source File

SOURCE=.\PKTZUORD\offset32.bin
# End Source File
# Begin Source File

SOURCE=..\TRIAS\PKTZUORD\offset32.bin
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\PKTZUORD\offset32.bin
# End Source File
# Begin Source File

SOURCE=.\PKTZUORD\offsetab.bin
# End Source File
# Begin Source File

SOURCE=..\TRIAS\PKTZUORD\offsetab.bin
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\PKTZUORD\offsetab.bin
# End Source File
# Begin Source File

SOURCE=.\obj32\overview.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\refresh.ico
# End Source File
# Begin Source File

SOURCE=..\TRIAS\obj32\refresh.ico
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\obj32\refresh.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\refresh_rot.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\RegServer.avi
# End Source File
# Begin Source File

SOURCE=.\obj32\RES\RegServer.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RIS2048.DBD
# End Source File
# Begin Source File

SOURCE=.\obj32\RIS2048C.011
# End Source File
# Begin Source File

SOURCE=.\obj32\RIS2048C.014
# End Source File
# Begin Source File

SOURCE=.\obj32\Search.avi
# End Source File
# Begin Source File

SOURCE=.\obj32\SHELL.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\SHELL3.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\SIGNON1.BMP
# End Source File
# Begin Source File

SOURCE=.\obj32\textcopy.cur
# End Source File
# Begin Source File

SOURCE=..\TRIAS\obj32\textcopy.cur
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\obj32\textcopy.cur
# End Source File
# Begin Source File

SOURCE=.\obj32\textmove.cur
# End Source File
# Begin Source File

SOURCE=..\TRIAS\obj32\textmove.cur
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\obj32\textmove.cur
# End Source File
# Begin Source File

SOURCE=..\TRIAS\obj32\Res\Ting.wav
# End Source File
# Begin Source File

SOURCE=E:\Triasdev.mvc\TRIAS\obj32\RES\Ting.wav
# End Source File
# Begin Source File

SOURCE=.\obj32\trias42_256.bm_
# End Source File
# Begin Source File

SOURCE=.\obj32\trias4_256.bm_
# End Source File
# Begin Source File

SOURCE=.\obj32\trias5_256.bm_
# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS_Icon.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\TRiAS_Icon_Transparent.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\TSTART.WAV
# End Source File
# Begin Source File

SOURCE=.\BMP\UndoRedoDetails.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\up.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\updis.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\upfocs.bmp
# End Source File
# Begin Source File

SOURCE=.\BMP\upsel.bmp
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\obj32\COPYSTRT.tpl

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__COPYS="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\COPYSTRT.tpl

"obj32\copystr.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\copystr.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__COPYS="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\COPYSTRT.tpl

"obj32\copystr.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\copystr.rc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\History.h
# End Source File
# Begin Source File

SOURCE=.\obj32\INFODLG.DLG

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__INFOD="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\INFODLG.DLG

"obj32\infodlg.src" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\infodlg.src

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__INFOD="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\INFODLG.DLG

"obj32\infodlg.src" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\infodlg.src

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\SIGNON1.DLG

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__SIGNO="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\SIGNON1.DLG

"obj32\signon1.src" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\signon1.src

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__SIGNO="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\SIGNON1.DLG

"obj32\signon1.src" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\signon1.src

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS16.MAK

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__TRIAS="\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\TRIAS16.MAK

"obj32\pkeycode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\pkeycode.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__TRIAS="\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\TRIAS16.MAK

"obj32\pkeycode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\pkeycode.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\Trias32.tpl

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__TRIAS3="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\Trias32.tpl

"obj32\trias32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\trias32.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__TRIAS3="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\Trias32.tpl

"obj32\trias32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\trias32.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\Trias32v.tpl

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__TRIAS32="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\Trias32v.tpl

"obj32\trias32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\trias32.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__TRIAS32="obj32\trias16.mak"	"\triasdev.mvc\include\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\Trias32v.tpl

"obj32\trias32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\trias32.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\INCLUDE\TRIASVER.MAK
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\obj32\TRiASVersion.tpl

!IF  "$(CFG)" == "Trias32 - Win32 Release"

USERDEP__TRIASV="obj32\trias16.mak"	"$(TRIASINCLUDE)\TRiASVer.mak"	
# Begin Custom Build
InputPath=.\obj32\TRiASVersion.tpl

"obj32\TRiASVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\TRiASVersion.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

USERDEP__TRIASV="obj32\trias16.mak"	"$(TRIASINCLUDE)\triasver.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\TRiASVersion.tpl

"obj32\TRiASVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias16.mak obj32\TRiASVersion.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Message handling"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Extfcns.hxx
# End Source File
# Begin Source File

SOURCE=.\Extfcns.tab
# End Source File
# Begin Source File

SOURCE=.\Extfcns1.cxx
# End Source File
# Begin Source File

SOURCE=.\extfcns2.cxx
# End Source File
# Begin Source File

SOURCE=.\ExtFcns3.cpp
# End Source File
# Begin Source File

SOURCE=.\Extfcnsn.cxx
# End Source File
# Begin Source File

SOURCE=.\Extfcnsn.hxx
# End Source File
# Begin Source File

SOURCE=.\Extfcnsn.tab
# End Source File
# Begin Source File

SOURCE=.\Extmain3.hxx
# End Source File
# Begin Source File

SOURCE=.\Extmmsg2.cxx

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Extqnfy2.cxx

!IF  "$(CFG)" == "Trias32 - Win32 Release"

# ADD CPP /O2 /Ob0

!ELSEIF  "$(CFG)" == "Trias32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Extqnfy2.hxx
# End Source File
# End Group
# End Target
# End Project
