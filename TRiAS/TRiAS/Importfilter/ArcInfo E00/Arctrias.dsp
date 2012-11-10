# Microsoft Developer Studio Project File - Name="Arctrias" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Arctrias - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Arctrias.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Arctrias.mak" CFG="Arctrias - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Arctrias - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Arctrias - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Importfilter/ArcInfo E00", BIGAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Arctrias - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MT /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /Yu"pheader.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib xtension.lib odbcinst.lib ctl3dv2.lib toolhelp.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 tfrmwork.lib containr.lib ospace5r.lib ixtnsr50.lib delayimp.lib winmm.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libcmt.lib" /out:".\WinRel\ARCTRIAS.ext" /delayload:crp32dll.dll /delayload:winmm.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\WinRel
TargetPath=.\WinRel\ARCTRIAS.ext
TargetName=ARCTRIAS
InputPath=.\WinRel\ARCTRIAS.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "_MBCS" /Yu"pheader.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib xtension.lib odbcinst.lib ctl3dv2.lib toolhelp.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 tfrm32d.lib ospace5d.lib ixtnsd50.lib cont50d.lib delayimp.lib winmm.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:IX86 /out:".\WinDebug\ArcTRiAD.ext" /delayload:crp32dll.dll /delayload:winmm.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
OutDir=.\WinDebug
TargetPath=.\WinDebug\ArcTRiAD.ext
TargetName=ArcTRiAD
InputPath=.\WinDebug\ArcTRiAD.ext
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_D) \
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) \
	

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_D)\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "Arctrias - Win32 Release"
# Name "Arctrias - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ARCIMP.CXX
# End Source File
# Begin Source File

SOURCE=.\ARCIMPIF.CXX
# End Source File
# Begin Source File

SOURCE=.\Arclx.cx
# End Source File
# Begin Source File

SOURCE=.\ARCLX.CXX
# End Source File
# Begin Source File

SOURCE=.\ARCTRIAS.DEF
# End Source File
# Begin Source File

SOURCE=.\ARCTRIAS.RC
# End Source File
# Begin Source File

SOURCE=.\ARCY.CXX
# End Source File
# Begin Source File

SOURCE=.\cpl_conv.cpp
# End Source File
# Begin Source File

SOURCE=.\cpl_error.cpp
# End Source File
# Begin Source File

SOURCE=.\cpl_vsisimple.cpp
# End Source File
# Begin Source File

SOURCE=.\e00read.cpp
# End Source File
# Begin Source File

SOURCE=.\e00write.cpp
# End Source File
# Begin Source File

SOURCE=.\FILEPOS.CXX
# End Source File
# Begin Source File

SOURCE=.\HEADER.CXX
# End Source File
# Begin Source File

SOURCE=.\HELPTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\IMPRESLT.CXX
# End Source File
# Begin Source File

SOURCE=.\Licenz.cpp
# End Source File
# Begin Source File

SOURCE=.\MERKMAL.CXX
# End Source File
# Begin Source File

SOURCE=.\NUMEDIT.CXX
# End Source File
# Begin Source File

SOURCE=.\OPTPARAM.CXX
# End Source File
# Begin Source File

SOURCE=.\PHEADER.CXX
# ADD CPP /Yc"pheader.h"
# End Source File
# Begin Source File

SOURCE=.\REALEDIT.CXX
# End Source File
# Begin Source File

SOURCE=.\RECHSTAT.CXX
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\TEXTCONN.CXX
# End Source File
# Begin Source File

SOURCE=.\TOOLS.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Arcguid.h
# End Source File
# Begin Source File

SOURCE=.\Arcimp.hxx
# End Source File
# Begin Source File

SOURCE=.\Arcimpif.hxx
# End Source File
# Begin Source File

SOURCE=.\Arctrias.hr
# End Source File
# Begin Source File

SOURCE=.\Filepos.hxx
# End Source File
# Begin Source File

SOURCE=.\Header.hxx
# End Source File
# Begin Source File

SOURCE=.\Helptext.hxx
# End Source File
# Begin Source File

SOURCE=.\Impreslt.hxx
# End Source File
# Begin Source File

SOURCE=.\Merkmal.hxx
# End Source File
# Begin Source File

SOURCE=.\Numedit.hxx
# End Source File
# Begin Source File

SOURCE=.\Optparam.hxx
# End Source File
# Begin Source File

SOURCE=.\Pheader.h
# End Source File
# Begin Source File

SOURCE=.\Realedit.hxx
# End Source File
# Begin Source File

SOURCE=.\Rechstat.hxx
# End Source File
# Begin Source File

SOURCE=.\Textconn.hxx
# End Source File
# Begin Source File

SOURCE=.\Tools.hxx
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\Yytab.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl"
# Begin Source File

SOURCE=.\ARCTRIAS.TPL

!IF  "$(CFG)" == "Arctrias - Win32 Release"

USERDEP__ARCTR="makefile"	
# Begin Custom Build
InputPath=.\ARCTRIAS.TPL

"arctrias.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile arctrias.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

USERDEP__ARCTR="makefile"	
# Begin Custom Build
InputPath=.\ARCTRIAS.TPL

"arctrias.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile arctrias.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ARCTRIAV.TPL

!IF  "$(CFG)" == "Arctrias - Win32 Release"

USERDEP__ARCTRI="makefile"	
# Begin Custom Build
InputPath=.\ARCTRIAV.TPL

"arctrias.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile arctrias.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

USERDEP__ARCTRI="makefile"	
# Begin Custom Build
InputPath=.\ARCTRIAV.TPL

"arctrias.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile arctrias.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "Arctrias - Win32 Release"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
