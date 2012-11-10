# Microsoft Developer Studio Project File - Name="Oleauto" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Oleauto - Win32 Debug TrueTime
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Oleauto4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Oleauto4.mak" CFG="Oleauto - Win32 Debug TrueTime"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Oleauto - Win32 Debug with BasicScript" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oleauto - Win32 Release with BasicScript" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oleauto - Win32 Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/OLE Automation", FYCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Oleauto_"
# PROP BASE Intermediate_Dir ".\Oleauto_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "EBWIN32" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /Fr /Fp"Debug/OLEAUTOD.pch" /Yu"precomp.hxx" /Fd"Debug/OLEAUTOD.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp".\Debug\OLEAUTOD.pch" /Yu"precomp.hxx" /Fd".\Debug\OLEAUTOD.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ixtmfd40.lib cont32d.lib stdcppd.lib ospaced.lib winmm.lib /nologo /dll /debug /machine:I386 /out:"Debug/oleautod.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib Triastld.lib delayimp.lib ebn.lib /nologo /dll /debug /machine:I386 /out:".\Debug\oleautod.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:olepro32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
InputDir=.\Debug
TargetDir=.\Debug
TargetPath=.\Debug\oleautod.ext
TargetName=oleautod
InputPath=.\Debug\oleautod.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	xcopy /F "$(InputDir)\..\Documentation\OleAuto.hlp" $(TRIASDIR_D) 
	xcopy /F "$(InputDir)\..\Documentation\OleAuto.cnt" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Oleauto0"
# PROP BASE Intermediate_Dir ".\Oleauto0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /Yu"precomp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Yu"precomp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"WinRel/oleauto.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ixtmar50.lib containr.lib ospace5r.lib Triastlb.lib delayimp.lib ebn.lib /nologo /dll /debug /machine:I386 /out:".\Release\oleauto.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:olepro32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Release
TargetPath=.\Release\oleauto.ext
TargetName=oleauto
InputPath=.\Release\oleauto.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Oleauto___Win32_Debug_TrueTime"
# PROP BASE Intermediate_Dir "Oleauto___Win32_Debug_TrueTime"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Oleauto___Win32_Debug_TrueTime"
# PROP Intermediate_Dir "Oleauto___Win32_Debug_TrueTime"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp".\Debug\OLEAUTOD.pch" /Yu"precomp.hxx" /Fd".\Debug\OLEAUTOD.pdb" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fp".\Oleauto___Win32_Debug_TrueTime\OLEAUTOD.pch" /Yu"precomp.hxx" /Fd".\Oleauto___Win32_Debug_TrueTime\OLEAUTOD.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d _MSC_VER=1100 /d "_NEWLOGO"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ixtmad50.lib cont50d.lib ospace5d.lib ebn.lib Triastld.lib /nologo /dll /debug /machine:I386 /out:".\Debug\oleautod.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib Triastld.lib delayimp.lib ebn.lib /nologo /dll /debug /machine:I386 /out:".\Oleauto___Win32_Debug_TrueTime\oleautod.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:olepro32.dll /delayload:advapi32.dll /delayload:sumnpb22.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Oleauto___Win32_Debug_TrueTime
TargetPath=.\Oleauto___Win32_Debug_TrueTime\oleautod.ext
TargetName=oleautod
InputPath=.\Oleauto___Win32_Debug_TrueTime\oleautod.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Oleauto - Win32 Debug with BasicScript"
# Name "Oleauto - Win32 Release with BasicScript"
# Name "Oleauto - Win32 Debug TrueTime"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "Basic Interface"

# PROP Default_Filter "cpp;c;cxx"
# Begin Source File

SOURCE=.\jumptab.cpp
# End Source File
# Begin Source File

SOURCE=.\OLEBSEXT.CXX

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# ADD BASE CPP /Gi-
# SUBTRACT BASE CPP /Gf
# ADD CPP /Gi-

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# ADD BASE CPP /Gi-
# ADD CPP /Gi-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PictureExt.cpp
# End Source File
# Begin Source File

SOURCE=.\PropActSeq.cpp
# End Source File
# Begin Source File

SOURCE=.\PropNamex.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusIndExt.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarExt.cpp
# End Source File
# Begin Source File

SOURCE=.\VisInfoExt.cpp
# End Source File
# End Group
# Begin Group "GeoObject, GeoObjects"

# PROP Default_Filter "cpp;cxx;c"
# Begin Source File

SOURCE=.\CONMTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\CONRTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\ENUMOBJS.CXX
# End Source File
# Begin Source File

SOURCE=.\GEOMETRY.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJS.CXX
# End Source File
# Begin Source File

SOURCE=.\Objsdisp.cxx
# End Source File
# Begin Source File

SOURCE=.\OBJTREES.CXX
# End Source File
# Begin Source File

SOURCE=.\ObjTreesCache.cpp
# End Source File
# End Group
# Begin Group "GeoView, GeoViews"

# PROP Default_Filter "cpp;cxx;c"
# Begin Source File

SOURCE=.\ENUVIEWS.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEW.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEWARRY.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEWDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEWS.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEWSDSP.CXX
# End Source File
# Begin Source File

SOURCE=.\VIEWTREE.CXX
# End Source File
# End Group
# Begin Group "GeoDocument, GeoDocuments"

# PROP Default_Filter "cpp;cxx;c"
# Begin Source File

SOURCE=.\DOC.CXX
# End Source File
# Begin Source File

SOURCE=.\DOCARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\DOCDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\DocDragnDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\DocLink.cpp
# End Source File
# Begin Source File

SOURCE=.\DOCS.CXX
# End Source File
# Begin Source File

SOURCE=.\DOCSDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\DOCTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\ENUMDOCS.CXX
# End Source File
# End Group
# Begin Group "Application"

# PROP Default_Filter "cxx;cpp;c"
# Begin Source File

SOURCE=.\APP.CXX
# End Source File
# Begin Source File

SOURCE=.\APPCF.CXX
# End Source File
# Begin Source File

SOURCE=.\APPDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\APPNTFY.CXX
# End Source File
# End Group
# Begin Group "GeoClass, GeoClasses"

# PROP Default_Filter "cpp;cxx;c"
# Begin Source File

SOURCE=.\CLASS.CXX
# End Source File
# Begin Source File

SOURCE=.\CLASSES.CXX
# End Source File
# Begin Source File

SOURCE=.\CLIDTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\CLNMTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\CLSARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\CLSDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\CLSSDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\CLSTREES.CXX
# End Source File
# Begin Source File

SOURCE=.\ENUMCLSS.CXX
# End Source File
# End Group
# Begin Group "GeoFeature, GeoFeatures"

# PROP Default_Filter "cxx;cpp;c"
# Begin Source File

SOURCE=.\ENUMFTS.CXX
# End Source File
# Begin Source File

SOURCE=.\FEAT.CXX
# End Source File
# Begin Source File

SOURCE=.\FEATDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\FTCLTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\FTOBTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\FTS.CXX
# End Source File
# Begin Source File

SOURCE=.\FTSARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\FTSDISP.CXX
# End Source File
# Begin Source File

SOURCE=.\FTVWTREE.CXX
# End Source File
# End Group
# Begin Group "GeoObjectWin, GeoObjectWins"

# PROP Default_Filter "cxx;cpp;c"
# Begin Source File

SOURCE=.\EnumObWs.cxx
# End Source File
# Begin Source File

SOURCE=.\OBJWIN.CXX
# End Source File
# Begin Source File

SOURCE=.\ObjWins.cxx
# End Source File
# Begin Source File

SOURCE=.\ObWarray.cxx
# End Source File
# Begin Source File

SOURCE=.\ObWdisp.cxx
# End Source File
# Begin Source File

SOURCE=.\OWinTree.cxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\ARRAY.CXX
# End Source File
# Begin Source File

SOURCE=.\BILDOBJ.CPP
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\BScriptNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\Connect.cxx
# End Source File
# Begin Source File

SOURCE=.\Datahelp.cxx
# End Source File
# Begin Source File

SOURCE=.\DLLDATAX.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\HandleDragDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropertyDual.cpp
# End Source File
# Begin Source File

SOURCE=.\OLE2AUTO.CXX
# End Source File
# Begin Source File

SOURCE=.\oleauto.def
# End Source File
# Begin Source File

SOURCE=.\Win32\Oleauto.RC
# End Source File
# Begin Source File

SOURCE=.\PICTURE.CPP
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\PRECOMP.CXX

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# ADD BASE CPP /Gi- /Yc"precomp.hxx"
# ADD CPP /Gi- /Yc"precomp.hxx"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# ADD BASE CPP /Yc"precomp.hxx"
# ADD CPP /Yc"precomp.hxx"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# ADD BASE CPP /Gi- /Yc"precomp.hxx"
# ADD CPP /Gi- /Yc"precomp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rgb_hsb.cxx
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNotifyDual.cpp
# End Source File
# Begin Source File

SOURCE=.\WIN32\Triastlb.idl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS=".\Documentation\OleAuto.hh"	
# Begin Custom Build - Running MIDL ...
OutDir=.\Debug
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

BuildCmds= \
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS=".\Documentation\OleAuto.hh"	
# Begin Custom Build - Running MIDL ...
OutDir=.\Release
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

BuildCmds= \
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
OutDir=.\Oleauto___Win32_Debug_TrueTime
InputPath=.\WIN32\Triastlb.idl
InputName=Triastlb

BuildCmds= \
	midl /Oicf /win32 /tlb $(OutDir)/$(InputName).tlb /h "$(TRIASINCLUDE)\$(InputName).h" /iid "$(TRIASINCLUDE)\$(InputName)_i.c" $(InputPath)

"$(OutDir)/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ViewDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\WrapperExtension.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "Basic Interface Header Files"

# PROP Default_Filter "h;hpp;hxx"
# Begin Source File

SOURCE=.\BScriptNotify.h
# End Source File
# Begin Source File

SOURCE=.\jumptab.h
# End Source File
# Begin Source File

SOURCE=.\OleAutoConfig.h
# End Source File
# Begin Source File

SOURCE=.\Olebsext.hxx
# End Source File
# End Group
# Begin Group "Application Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\App.hxx
# End Source File
# Begin Source File

SOURCE=.\APPCF.HXX
# End Source File
# Begin Source File

SOURCE=.\ARRAY.HXX
# End Source File
# End Group
# Begin Group "GeoClass Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\class.hxx
# End Source File
# Begin Source File

SOURCE=.\classes.hxx
# End Source File
# Begin Source File

SOURCE=.\clidtree.hxx
# End Source File
# Begin Source File

SOURCE=.\clidtree.inl
# End Source File
# Begin Source File

SOURCE=.\CLNMTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\CLNMTREE.INL
# End Source File
# Begin Source File

SOURCE=.\clsarray.hxx
# End Source File
# Begin Source File

SOURCE=.\clstrees.hxx
# End Source File
# Begin Source File

SOURCE=.\enumclss.hxx
# End Source File
# End Group
# Begin Group "GeoView Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\enuviews.hxx
# End Source File
# Begin Source File

SOURCE=.\view.hxx
# End Source File
# Begin Source File

SOURCE=.\viewarry.hxx
# End Source File
# Begin Source File

SOURCE=.\ViewDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\views.hxx
# End Source File
# Begin Source File

SOURCE=.\viewtree.hxx
# End Source File
# Begin Source File

SOURCE=.\viewtree.inl
# End Source File
# End Group
# Begin Group "GeoObject Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\conmtree.hxx
# End Source File
# Begin Source File

SOURCE=.\conmtree.inl
# End Source File
# Begin Source File

SOURCE=.\conrtree.hxx
# End Source File
# Begin Source File

SOURCE=.\conrtree.inl
# End Source File
# Begin Source File

SOURCE=.\enumobjs.hxx
# End Source File
# Begin Source File

SOURCE=.\obj.hxx
# End Source File
# Begin Source File

SOURCE=.\objarray.hxx
# End Source File
# Begin Source File

SOURCE=.\objs.hxx
# End Source File
# Begin Source File

SOURCE=.\objtrees.hxx
# End Source File
# Begin Source File

SOURCE=.\ObjTreesCache.h
# End Source File
# End Group
# Begin Group "GeoDocument Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\doc.hxx
# End Source File
# Begin Source File

SOURCE=.\docarray.hxx
# End Source File
# Begin Source File

SOURCE=.\docs.hxx
# End Source File
# Begin Source File

SOURCE=.\doctree.hxx
# End Source File
# Begin Source File

SOURCE=.\DOCTREE.INL
# End Source File
# Begin Source File

SOURCE=.\enumdocs.hxx
# End Source File
# End Group
# Begin Group "GeoFeature Header Files"

# PROP Default_Filter "hpp;hxx;h;inl"
# Begin Source File

SOURCE=.\enumfts.hxx
# End Source File
# Begin Source File

SOURCE=.\feat.hxx
# End Source File
# Begin Source File

SOURCE=.\ftcltree.hxx
# End Source File
# Begin Source File

SOURCE=.\FTCLTREE.INL
# End Source File
# Begin Source File

SOURCE=.\ftobtree.hxx
# End Source File
# Begin Source File

SOURCE=.\FTOBTREE.INL
# End Source File
# Begin Source File

SOURCE=.\fts.hxx
# End Source File
# Begin Source File

SOURCE=.\ftsarray.hxx
# End Source File
# Begin Source File

SOURCE=.\FTVWTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\FTVWTREE.INL
# End Source File
# End Group
# Begin Group "GeoObjectWin Header Files"

# PROP Default_Filter "hpp;hxx;inl"
# Begin Source File

SOURCE=.\ENUMOBWS.HXX
# End Source File
# Begin Source File

SOURCE=.\Objwin.hxx
# End Source File
# Begin Source File

SOURCE=.\Objwins.hxx
# End Source File
# Begin Source File

SOURCE=.\Obwarray.hxx
# End Source File
# Begin Source File

SOURCE=.\OWINTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\OWINTREE.INL
# End Source File
# End Group
# Begin Source File

SOURCE=.\connect.hxx
# End Source File
# Begin Source File

SOURCE=.\COPTTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\CPTriasNfy.h
# End Source File
# Begin Source File

SOURCE=.\Defines.h
# End Source File
# Begin Source File

SOURCE=.\DropTargets.h
# End Source File
# Begin Source File

SOURCE=.\EBARRAY.HXX
# End Source File
# Begin Source File

SOURCE=.\GlobalFuncs.h
# End Source File
# Begin Source File

SOURCE=.\MenuCommands.h
# End Source File
# Begin Source File

SOURCE=.\MonikerStream.h
# End Source File
# Begin Source File

SOURCE=.\ObjectProperty.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropertyDual.h
# End Source File
# Begin Source File

SOURCE=.\ole2auto.h
# End Source File
# Begin Source File

SOURCE=.\Ole2auto.hxx
# End Source File
# Begin Source File

SOURCE=.\oleautor.h
# End Source File
# Begin Source File

SOURCE=.\olestr.h
# End Source File
# Begin Source File

SOURCE=.\precomp.hxx
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNotify.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNotifyDual.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# Begin Source File

SOURCE=.\WrapperExtension.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\WIN32\Res\catid_to.bmp
# End Source File
# Begin Source File

SOURCE=.\Win32\Res\catid_toold.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\Res\CopyObjd.ebc
# End Source File
# Begin Source File

SOURCE=.\Win32\Res\CopyObjr.ebc
# End Source File
# Begin Source File

SOURCE=.\WIN32\Res\oleauto.bmp
# End Source File
# Begin Source File

SOURCE=.\WIN32\Res\OLEAUTO.ICO
# End Source File
# Begin Source File

SOURCE=.\oleauto.rcv
# End Source File
# Begin Source File

SOURCE=.\Win32\Res\oleautoold.bmp
# End Source File
# Begin Source File

SOURCE=.\Win32\OLEBSEXT.RC

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Win32\Res\oledocum.ico
# End Source File
# Begin Source File

SOURCE=.\Win32\project.ico
# End Source File
# Begin Source File

SOURCE=.\DEBUG\TRIASTLB.tlb
# End Source File
# Begin Source File

SOURCE=.\Release\Triastlb.tlb
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Group "Help Versioning Templates"

# PROP Default_Filter "*.tpl"
# Begin Source File

SOURCE=.\Documentation\CONTENTS.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__CONTE="oleaut16.mak"	
# Begin Custom Build
InputPath=.\Documentation\CONTENTS.TPL

".\Documentation\contents.hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak .\Documentation\contents.hpj

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Documentation\OleAutoFmt.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__OLEAU="oleaut16.mak"	
# Begin Custom Build
InputPath=.\Documentation\OleAutoFmt.tpl

".\Documentation\OleAuto.fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak .\Documentation\OleAuto.fmt

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Documentation\OleAutotpl.cnt

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__OLEAUT="oleaut16.mak"	
# Begin Custom Build
InputPath=.\Documentation\OleAutotpl.cnt

".\Documentation\OleAuto.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak .\Documentation\OleAuto.cnt

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning Templates"

# PROP Default_Filter "*.tpl"
# Begin Source File

SOURCE=.\Olbsextp.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__OLBSE="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Olbsextp.tpl

"olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak olebsext.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

USERDEP__OLBSE="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Olbsextp.tpl

"olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak olebsext.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

USERDEP__OLBSE="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Olbsextp.tpl

"olebsext.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak olebsext.rc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OLEAUTO.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__OLEAUTO="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\OLEAUTO.TPL

"oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

USERDEP__OLEAUTO="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\OLEAUTO.TPL

"oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

USERDEP__OLEAUTO="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\OLEAUTO.TPL

"oleauto.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Oleautov.tpl

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__OLEAUTOV="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Oleautov.tpl

"oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

USERDEP__OLEAUTOV="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Oleautov.tpl

"oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

USERDEP__OLEAUTOV="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Oleautov.tpl

"oleauto.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak oleauto.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__VERSI="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

USERDEP__VERSI="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

USERDEP__VERSI="oleaut16.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\VERSIO32.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f oleaut16.mak versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\OLEAUT16.MAK
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\Win32\Res\Document.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\Res\DocumentWithoutOle.rgs
# End Source File
# Begin Source File

SOURCE=.\WIN32\Res\OleAuto.rgs
# End Source File
# Begin Source File

SOURCE=.\Win32\Res\WrapperExtension.rgs
# End Source File
# End Group
# Begin Group "Basic Scripts"

# PROP Default_Filter "*.ebs"
# Begin Source File

SOURCE=.\WIN32\Res\CopyObj.Ebs

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

"$(InputDir)\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

"$(InputDir)\$(InputName)r.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(InputDir)\$(InputName)r.ebc -DNDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.\WIN32\Res
InputPath=.\WIN32\Res\CopyObj.Ebs
InputName=CopyObj

"$(InputDir)\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.d"
# Begin Group "Help Source Files"

# PROP Default_Filter "*.d"
# Begin Group "Bitmaps"

# PROP Default_Filter "*.bmp"
# Begin Source File

SOURCE=.\Documentation\Bitmaps\Crosses.bmp
# End Source File
# Begin Source File

SOURCE=.\Documentation\Bitmaps\Overlaps.bmp
# End Source File
# Begin Source File

SOURCE=.\Documentation\Bitmaps\STATIND.BMP
# End Source File
# Begin Source File

SOURCE=.\Documentation\Bitmaps\Touches.bmp
# End Source File
# Begin Source File

SOURCE=.\Documentation\Bitmaps\Within.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Documentation\Contents.d

!IF  "$(CFG)" == "Oleauto - Win32 Debug with BasicScript"

USERDEP__CONTEN="oleaut16.mak"	
# Begin Custom Build
InputPath=.\Documentation\Contents.d

".\Documentation\OleAuto.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f oleaut16.mak -nologo DEBUG=1 .\Documentation\OleAuto.hlp

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Release with BasicScript"

# Begin Custom Build
InputPath=.\Documentation\Contents.d

".\Documentation\OleAuto.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f oleaut16.mak -nologo NDEBUG=1 .\Documentation\OleAuto.hlp

# End Custom Build

!ELSEIF  "$(CFG)" == "Oleauto - Win32 Debug TrueTime"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Documentation\Dataobjects.d
# End Source File
# Begin Source File

SOURCE=.\Documentation\ObjectsInBasicScript.d
# End Source File
# Begin Source File

SOURCE=.\Documentation\Preface.d
# End Source File
# Begin Source File

SOURCE=.\Documentation\VariablesInBasicScript.d
# End Source File
# End Group
# Begin Group "Script Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Documentation\OleAutohh.awk
# End Source File
# Begin Source File

SOURCE=.\Documentation\OleAutohh.sed
# End Source File
# End Group
# Begin Source File

SOURCE=C:\MSDEV6\VC98\AUTODUCK\AUTODUCK.FMT
# End Source File
# Begin Source File

SOURCE=.\Documentation\OleAuto.hh
# End Source File
# Begin Source File

SOURCE=.\Documentation\OLEAUTO.HLP
# End Source File
# End Group
# End Target
# End Project
