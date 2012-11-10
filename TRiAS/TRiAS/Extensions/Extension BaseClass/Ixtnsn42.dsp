# Microsoft Developer Studio Project File - Name="ixtnsn32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ixtnsn32 - Win32 Release ATL Base
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ixtnsn42.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ixtnsn42.mak" CFG="ixtnsn32 - Win32 Release ATL Base"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ixtnsn32 - Win32 Release New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Debug New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Debug ATL Base" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Release ATL Base" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Extension BaseClass (MFC)", EAEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ixtnsn32"
# PROP BASE Intermediate_Dir ".\ixtnsn32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Obj50\Release"
# PROP Intermediate_Dir ".\Obj50\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /Ob2 /D "NDEBUG" /D "DLL" /D "__CV__" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /Fp".\Obj50\Release/Ixtnsn50.pch" /Yu"xtensnp.hxx" /Fd".\Obj50\Release/ixtnsr50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Obj50\Release/Ixtnsn50.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj32/Release\ixtnsr40.lib"
# ADD LIB32 /nologo /out:".\Obj50\Release\ixtnsr50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Obj50\Release
TargetPath=.\Obj50\Release\ixtnsr50.lib
TargetName=ixtnsr50
InputPath=.\Obj50\Release\ixtnsr50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ixtnsn30"
# PROP BASE Intermediate_Dir ".\ixtnsn30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Obj50\Debug"
# PROP Intermediate_Dir ".\Obj50\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /FR /Fp"Obj32/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fd"Obj32/Debug/ixtnsd40.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "DLL" /D "__CV__" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /FR /Fp".\Obj50\Debug\ixtnsn50.pch" /Yu"xtensnp.hxx" /Fd".\Obj50\Debug\ixtnsd50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Obj50\Debug\IXTNSN50.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj32/Debug\ixtnsd40.lib"
# ADD LIB32 /nologo /out:".\Obj50\Debug\ixtnsd50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Obj50\Debug
TargetPath=.\Obj50\Debug\ixtnsd50.lib
TargetName=ixtnsd50
InputPath=.\Obj50\Debug\ixtnsd50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ixtnsn30"
# PROP BASE Intermediate_Dir ".\ixtnsn30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Atl50\Debug"
# PROP Intermediate_Dir ".\Atl50\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "__ATL_11_USED__" /FR /Fp"Obj42/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fd"Obj42/Debug/ixtnsd42.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "__ATL_XTENSION_BASE__" /D "DLL" /D "__CV__" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /FR /Fp".\Atl50\Debug\IxtAtd50.pch" /Yu"xtensnp.hxx" /Fd".\Atl50\Debug\IxtAtd50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Atl50\Debug/Ixtnsn50.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj42/Debug\ixtnsd42.lib"
# ADD LIB32 /nologo /out:".\Atl50\Debug\IxtAtd50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Atl50\Debug
TargetPath=.\Atl50\Debug\IxtAtd50.lib
TargetName=IxtAtd50
InputPath=.\Atl50\Debug\IxtAtd50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ixtnsn32"
# PROP BASE Intermediate_Dir ".\ixtnsn32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Atl50\Release"
# PROP Intermediate_Dir ".\Atl50\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "__ATL_11_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /Ob2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D "DLL" /D "__CV__" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /Fp".\Atl50\Release\IXtAtr50.pch" /Yu"xtensnp.hxx" /Fd".\Atl50\Release/IxtAtr50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\Atl50\Release/Ixtnsn50.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj42/Release\ixtnsr42.lib"
# ADD LIB32 /nologo /out:".\Atl50\Release\ixtAtr50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Atl50\Release
TargetPath=.\Atl50\Release\ixtAtr50.lib
TargetName=ixtAtr50
InputPath=.\Atl50\Release\ixtAtr50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb"  $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ixtnsn32 - Win32 Release New"
# Name "ixtnsn32 - Win32 Debug New"
# Name "ixtnsn32 - Win32 Debug ATL Base"
# Name "ixtnsn32 - Win32 Release ATL Base"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\cimpxtsn.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
# ADD CPP /Yu"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\DBLNUMED.CXX
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

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy6.cpp
# End Source File
# Begin Source File

SOURCE=.\dummy7.cpp
# End Source File
# Begin Source File

SOURCE=.\dummy8.cpp
# End Source File
# Begin Source File

SOURCE=.\dummy9.cpp
# End Source File
# Begin Source File

SOURCE=.\DUMPOUT.CXX
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

SOURCE=.\HDRENTRX.CXX
# End Source File
# Begin Source File

SOURCE=.\HELPTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\IENUMONR.CXX
# End Source File
# Begin Source File

SOURCE=.\IENUMSTR.CXX
# End Source File
# Begin Source File

SOURCE=.\IMPXTCF.CXX

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NUMEDITX.CXX
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

SOURCE=.\VALIDADD.CXX
# End Source File
# Begin Source File

SOURCE=.\XtencAtl.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Xtencunk.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XTENSNP.CXX

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# ADD BASE CPP /MD /Yc"xtensnp.hxx"
# ADD CPP /MD /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# ADD BASE CPP /MD /Yc"xtensnp.hxx"
# ADD CPP /MD /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xtsnatl.cpp
# End Source File
# Begin Source File

SOURCE=.\xtsnimp.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XtsnImpAtl.cpp

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xtsnprop.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XtsnPropAtl.cpp

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

!ENDIF 

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

SOURCE=.\IENUMSTR.HXX
# End Source File
# Begin Source File

SOURCE=.\objpropf.hxx
# End Source File
# Begin Source File

SOURCE=.\synccook.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtencatl.hxx
# End Source File
# Begin Source File

SOURCE=.\Xtensnp.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\XtsnPropAtl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
