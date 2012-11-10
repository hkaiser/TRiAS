# Microsoft Developer Studio Project File - Name="ixtmfc32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ixtmfc32 - Win32 Release New
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ixtmfc50.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ixtmfc50.mak" CFG="ixtmfc32 - Win32 Release New"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ixtmfc32 - Win32 Release New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Debug New" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Extension BaseClass (MFC)", EAEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ixtmfc32"
# PROP BASE Intermediate_Dir ".\ixtmfc32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Mfc42\Release"
# PROP Intermediate_Dir ".\Mfc42\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /Yu"xtensnp.hxx" /Fd".\Mfc42\Release/Ixtmfr50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc32/Release\ixtmfr40.lib"
# ADD LIB32 /nologo /out:".\Mfc42\Release\ixtmfr50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Mfc42\Release
TargetPath=.\Mfc42\Release\ixtmfr50.lib
TargetName=ixtmfr50
InputPath=.\Mfc42\Release\ixtmfr50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ixtmfc30"
# PROP BASE Intermediate_Dir ".\ixtmfc30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Mfc42\Debug"
# PROP Intermediate_Dir ".\Mfc42\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /FR /Yu"xtensnp.hxx" /Fd"Mfc32/Debug/ixtmfd40.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /FR /Yu"xtensnp.hxx" /Fd".\Mfc42\Debug\ixtmfd50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc32/Debug\ixtmfd40.lib"
# ADD LIB32 /nologo /out:".\Mfc42\Debug\ixtmfd50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Mfc42\Debug
TargetPath=.\Mfc42\Debug\ixtmfd50.lib
TargetName=ixtmfd50
InputPath=.\Mfc42\Debug\ixtmfd50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ixtmfc32 - Win32 Release New"
# Name "ixtmfc32 - Win32 Debug New"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\cimpxtsn.cxx
# End Source File
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\CtfxmfcObsolete.cpp
# End Source File
# Begin Source File

SOURCE=.\dllbindx.cxx
# End Source File
# Begin Source File

SOURCE=.\dummy1.cxx
# End Source File
# Begin Source File

SOURCE=.\dummy2.cxx
# End Source File
# Begin Source File

SOURCE=.\dummy3.cxx
# End Source File
# Begin Source File

SOURCE=.\DUMMY4.CXX
# End Source File
# Begin Source File

SOURCE=.\dummy5.cxx
# End Source File
# Begin Source File

SOURCE=.\enmcprop.cxx
# End Source File
# Begin Source File

SOURCE=.\enumprop.cxx
# End Source File
# Begin Source File

SOURCE=.\EXTREG.CXX
# End Source File
# Begin Source File

SOURCE=.\Hdrentrx.cxx
# End Source File
# Begin Source File

SOURCE=.\IENUMONR.CXX
# End Source File
# Begin Source File

SOURCE=.\IMPXTCF.CXX
# End Source File
# Begin Source File

SOURCE=.\OBJCONTX.CXX
# End Source File
# Begin Source File

SOURCE=.\objpropf.cxx
# End Source File
# Begin Source File

SOURCE=.\REGISTRY.CXX
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\Xtencunk.cxx

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# ADD BASE CPP /Zi
# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XTENSNP.CXX
# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"
# End Source File
# Begin Source File

SOURCE=.\xtsnatl.cpp
# End Source File
# Begin Source File

SOURCE=.\xtsnimp.cxx
# End Source File
# Begin Source File

SOURCE=.\xtsnprop.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\cimpxtsn.hxx
# End Source File
# Begin Source File

SOURCE=.\enmcprop.hxx
# End Source File
# Begin Source File

SOURCE=.\enumprop.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Hdrentrx.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ienumobj.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\IENUMONR.HXX
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Ixtensn.hxx
# End Source File
# Begin Source File

SOURCE=.\objpropf.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\registrx.hxx
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\synccook.h
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

SOURCE=.\Xtensnp.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Xtensnx.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\Xtensnxx.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnaux.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnimp.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtsnprop.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
