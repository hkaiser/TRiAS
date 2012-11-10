# Microsoft Developer Studio Project File - Name="visobj32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=visobj32 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Visobj42.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Visobj42.mak" CFG="visobj32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "visobj32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "visobj32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "visobj32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "_WINDLL" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "EXTVIS" /Fp".\Release/Visobj50.pch" /Yu"visobjp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 triastlb.lib ixtatr50.lib ospace5r.lib containr.lib tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\Visobj.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\visobj.ext
TargetName=visobj
InputPath=.\Release\visobj.ext
SOURCE=$(InputPath)

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" $(TRIASDIR_R)

# End Custom Build

!ELSEIF  "$(CFG)" == "visobj32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_WINDLL" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "EXTVIS" /FR /Fp".\Debug\visobjd.pch" /Yu"visobjp.hxx" /Fd".\Debug\visobjd.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /i "." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Debug/Visobj50.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 triastld.lib ixtatd50.lib ospace5d.lib cont50d.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /debugtype:both /machine:I386 /out:".\Debug\visobjd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /map
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\visobjd.ext
TargetName=visobjd
InputPath=.\Debug\visobjd.ext
SOURCE=$(InputPath)

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" $(TRIASDIR_D) 
	copy "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "visobj32 - Win32 Release"
# Name "visobj32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BMPBOX.CXX
# End Source File
# Begin Source File

SOURCE=.\CHANGEVI.CXX
# End Source File
# Begin Source File

SOURCE=.\CIMPVIEW.CXX
# End Source File
# Begin Source File

SOURCE=.\COLCNTRL.CXX
# End Source File
# Begin Source File

SOURCE=.\Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\INITPARS.CXX
# End Source File
# Begin Source File

SOURCE=.\RANGENUM.CXX
# End Source File
# Begin Source File

SOURCE=.\RESETVIS.CXX
# End Source File
# Begin Source File

SOURCE=.\RGB_HSB.CXX
# End Source File
# Begin Source File

SOURCE=.\RSETHIDE.CXX
# End Source File
# Begin Source File

SOURCE=.\UIDOBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\VISERRDG.CXX
# End Source File
# Begin Source File

SOURCE=.\VISERROR.CXX
# End Source File
# Begin Source File

SOURCE=.\VISEXP.CXX
# End Source File
# Begin Source File

SOURCE=.\visidll.cxx
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\VISIDLL.LX
# End Source File
# Begin Source File

SOURCE=.\VISIDLLP.CXX
# End Source File
# Begin Source File

SOURCE=.\visidly.cxx
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\VISIDLY.Y
# End Source File
# Begin Source File

SOURCE=.\VISIDLYP.CXX
# End Source File
# Begin Source File

SOURCE=.\VISIMP.CXX
# End Source File
# Begin Source File

SOURCE=.\VISINFO.CXX
# End Source File
# Begin Source File

SOURCE=.\Visinfo.idl

!IF  "$(CFG)" == "visobj32 - Win32 Release"

# Begin Custom Build - Running MIDL ...
OutDir=.\.\Release
InputPath=.\Visinfo.idl
InputName=Visinfo

"$(OutDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /tlb $(OutDir)\$(InputName).tlb $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "visobj32 - Win32 Debug"

# Begin Custom Build - Running MIDL ...
OutDir=.\.\Debug
InputPath=.\Visinfo.idl
InputName=Visinfo

BuildCmds= \
	midl /tlb $(OutDir)\$(InputName).tlb /h \triasdev.mvc\include\$(InputName).h\
                /iid \triasdev.mvc\include\$(InputName)_i.c $(InputPath)

"\triasdev.mvc\include\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\include\$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VisInfoObj.cpp

!IF  "$(CFG)" == "visobj32 - Win32 Release"

!ELSEIF  "$(CFG)" == "visobj32 - Win32 Debug"

# ADD CPP /Od /Ob1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VISMTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\VISOBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\obj32\VISOBJ32.DEF
# End Source File
# Begin Source File

SOURCE=.\obj32\visobj32.RC

!IF  "$(CFG)" == "visobj32 - Win32 Release"

# ADD BASE RSC /l 0x407 /i "obj32"
# SUBTRACT BASE RSC /i ".."
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# SUBTRACT RSC /i ".."

!ELSEIF  "$(CFG)" == "visobj32 - Win32 Debug"

# ADD BASE RSC /l 0x407 /i "obj32"
# SUBTRACT BASE RSC /i ".." /i "."
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# SUBTRACT RSC /i ".." /i "."

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\visobjl.cxx
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\VISOBJL.LX
# End Source File
# Begin Source File

SOURCE=.\VISOBJLP.CXX
# End Source File
# Begin Source File

SOURCE=.\visobjp.cxx

!IF  "$(CFG)" == "visobj32 - Win32 Release"

# ADD CPP /Yc"visobjp.hxx"

!ELSEIF  "$(CFG)" == "visobj32 - Win32 Debug"

# ADD CPP /Ob1 /Yc"visobjp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\visobjy.cxx
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\VISOBJY.Y
# End Source File
# Begin Source File

SOURCE=.\VISOBJYP.CXX
# End Source File
# Begin Source File

SOURCE=.\VSTATUS.CXX
# End Source File
# Begin Source File

SOURCE=.\XVISDLG.CXX
# End Source File
# Begin Source File

SOURCE=.\YY2STYPE.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CIMPVIEW.HXX
# End Source File
# Begin Source File

SOURCE=.\CIMPVIEW.INL
# End Source File
# Begin Source File

SOURCE=.\COLCNTRL.H
# End Source File
# Begin Source File

SOURCE=.\COLCNTRL.HXX
# End Source File
# Begin Source File

SOURCE=.\COPTTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\CPVisInfo.h
# End Source File
# Begin Source File

SOURCE=.\DEFABOUT.H
# End Source File
# Begin Source File

SOURCE=.\DEFABOUT.HXX
# End Source File
# Begin Source File

SOURCE=.\Helper.h
# End Source File
# Begin Source File

SOURCE=.\RESETVIS.H
# End Source File
# Begin Source File

SOURCE=.\RESETVIS.HXX
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\RSETHIDE.HXX
# End Source File
# Begin Source File

SOURCE=.\UIDOBJ.HXX
# End Source File
# Begin Source File

SOURCE=.\UIDOBJ.INL
# End Source File
# Begin Source File

SOURCE=.\VERSIO16.H
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# Begin Source File

SOURCE=.\VISERRDG.H
# End Source File
# Begin Source File

SOURCE=.\VISERRDG.HXX
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\VISERROR.HXX
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\VISERROR.INL
# End Source File
# Begin Source File

SOURCE=.\VISEXP.H
# End Source File
# Begin Source File

SOURCE=.\VISEXP.HXX
# End Source File
# Begin Source File

SOURCE=.\VISIMP.H
# End Source File
# Begin Source File

SOURCE=.\Visimp.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\visinfo.hxx
# End Source File
# Begin Source File

SOURCE=.\VisInfoObj.h
# End Source File
# Begin Source File

SOURCE=.\VISMTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\Vismtree.inl
# End Source File
# Begin Source File

SOURCE=.\VISOBJ.H
# End Source File
# Begin Source File

SOURCE=.\Visobj.hxx
# End Source File
# Begin Source File

SOURCE=.\visobjp.hxx
# End Source File
# Begin Source File

SOURCE=.\VSTATUS.H
# End Source File
# Begin Source File

SOURCE=.\VSTATUS.HXX
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtencatl.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnaux.hxx
# End Source File
# Begin Source File

SOURCE=.\XVISDLG.H
# End Source File
# Begin Source File

SOURCE=.\Xvisdlg.hxx
# End Source File
# Begin Source File

SOURCE=.\yvisidl.h
# End Source File
# Begin Source File

SOURCE=.\yvisobj.h
# End Source File
# Begin Source File

SOURCE=.\YY1STYPE.HXX
# End Source File
# Begin Source File

SOURCE=.\YY2STYPE.HXX
# End Source File
# Begin Source File

SOURCE=.\YYSTYPE.HXX
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\obj32\DEFABOUT.SRC
# End Source File
# Begin Source File

SOURCE=.\obj32\LUPE.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\VERROR.BMP
# End Source File
# Begin Source File

SOURCE=.\Debug\Visinfo.tlb
# End Source File
# Begin Source File

SOURCE=.\obj32\VISOBJ32.RCV
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\obj32\Res\AreaVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\Res\LineVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\Res\PointVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\Res\TextVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\Res\VisInfo.rgs
# End Source File
# End Group
# End Target
# End Project
# Section visobj32 : {C8D4E847-B8C8-11CF-BA6A-00AA0018497C}
# 	0:15:PVisInfoObj.cpp:E:\Triasdev.mvc\Xtension\Visobj\obj32\PVisInfoObj.cpp
# 	0:13:PVisInfoObj.h:E:\Triasdev.mvc\Xtension\Visobj\obj32\PVisInfoObj.h
# 	2:15:PVisInfoObj.cpp:PVisInfoObj.cpp
# 	2:13:PVisInfoObj.h:PVisInfoObj.h
# 	2:22:CLASS: CPVisInfoObject:CPVisInfoObject
# 	2:19:Application Include:visobj32.h
# End Section
