# Microsoft Developer Studio Project File - Name="Dxfimp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Dxfimp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Dxfimp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dxfimp.mak" CFG="Dxfimp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dxfimp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dxfimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Importfilter/AutoCAD DXF", RUGAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "D:\triasdev.mvc\inc.hpp" /I "D:\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /Yu"pheader.hpp" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr50.lib ospace5r.lib tfrmwork.lib containr.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinRel\dxfimp.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:msvcirt.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\WinRel
TargetPath=.\WinRel\dxfimp.ext
TargetName=dxfimp
InputPath=.\WinRel\dxfimp.ext
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_R) \
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASDIR_R) \
	

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_R)/$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "MSWIND" /Fr /Yu"pheader.hpp" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib ixtnsd50.lib ospace5d.lib cont50d.lib delayimp.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"ocs30d.lib" /nodefaultlib:"libcmt.lib" /out:".\WinDebug\dxfimpd.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:msvcp60d.dll /delayload:msvcirtd.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\WinDebug
TargetPath=.\WinDebug\dxfimpd.ext
TargetName=dxfimpd
InputPath=.\WinDebug\dxfimpd.ext
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_D) \
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASDIR_D) \
	

"$(TRIASDIR_D)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_D)/$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "Dxfimp - Win32 Release"
# Name "Dxfimp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\block.cpp
# End Source File
# Begin Source File

SOURCE=.\BOGEN.CPP
# End Source File
# Begin Source File

SOURCE=.\DGEO_OBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\DXFIMP.CPP
# End Source File
# Begin Source File

SOURCE=.\DXFIMP.DEF
# End Source File
# Begin Source File

SOURCE=.\DXFIMP.RC
# End Source File
# Begin Source File

SOURCE=.\DXFIMPIF.CPP
# End Source File
# Begin Source File

SOURCE=.\Dxflx.cp
# End Source File
# Begin Source File

SOURCE=.\DXFLX.CPP
# End Source File
# Begin Source File

SOURCE=.\DXFY.CPP
# End Source File
# Begin Source File

SOURCE=.\HEADER.CPP
# End Source File
# Begin Source File

SOURCE=.\HELPTEXT.CPP
# End Source File
# Begin Source File

SOURCE=.\IMPRESLT.CPP
# End Source File
# Begin Source File

SOURCE=.\layers.Cpp
# End Source File
# Begin Source File

SOURCE=.\Licenz.cpp
# End Source File
# Begin Source File

SOURCE=.\MERKMAL.CPP
# End Source File
# Begin Source File

SOURCE=.\NUMEDIT.CPP
# End Source File
# Begin Source File

SOURCE=.\OPTPARAM.CPP
# End Source File
# Begin Source File

SOURCE=.\OPTPRDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\PHEADER.CPP
# ADD CPP /Yc"pheader.hpp"
# End Source File
# Begin Source File

SOURCE=.\PUNKTLI.CPP
# End Source File
# Begin Source File

SOURCE=.\REALEDIT.CPP
# End Source File
# Begin Source File

SOURCE=.\RECHSTAT.CPP
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CPP
# End Source File
# Begin Source File

SOURCE=.\TMERKMAL.CPP
# End Source File
# Begin Source File

SOURCE=.\TOOLS.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Block.hpp
# End Source File
# Begin Source File

SOURCE=.\Bogen.hpp
# End Source File
# Begin Source File

SOURCE=.\Dgeo_obj.hpp
# End Source File
# Begin Source File

SOURCE=.\Dxfguids.h
# End Source File
# Begin Source File

SOURCE=.\Dxfimp.hpp
# End Source File
# Begin Source File

SOURCE=.\Dxfimp.hr
# End Source File
# Begin Source File

SOURCE=.\Dxfimpif.hpp
# End Source File
# Begin Source File

SOURCE=.\Header.hpp
# End Source File
# Begin Source File

SOURCE=.\Helptext.hpp
# End Source File
# Begin Source File

SOURCE=.\Impreslt.hpp
# End Source File
# Begin Source File

SOURCE=.\Layers.hpp
# End Source File
# Begin Source File

SOURCE=.\Lextypes.h
# End Source File
# Begin Source File

SOURCE=.\Merkmal.hpp
# End Source File
# Begin Source File

SOURCE=.\Numedit.hpp
# End Source File
# Begin Source File

SOURCE=.\Optparam.hpp
# End Source File
# Begin Source File

SOURCE=.\Optprdlg.hpp
# End Source File
# Begin Source File

SOURCE=.\Pheader.hpp
# End Source File
# Begin Source File

SOURCE=.\Punktli.hpp
# End Source File
# Begin Source File

SOURCE=.\Realedit.hpp
# End Source File
# Begin Source File

SOURCE=.\Rechstat.hpp
# End Source File
# Begin Source File

SOURCE=.\Tmerkmal.hpp
# End Source File
# Begin Source File

SOURCE=.\Tools.hpp
# End Source File
# Begin Source File

SOURCE=.\Versio32.h
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
# Begin Source File

SOURCE=.\DXFIMP.RCV
# End Source File
# End Group
# Begin Group "Parser/Lexer Sources"

# PROP Default_Filter "*.y;*.lx"
# Begin Source File

SOURCE=.\DXFLX.L

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

USERDEP__DXFLX="$(InputName).sed"	
# Begin Custom Build
InputPath=.\DXFLX.L
InputName=DXFLX

"$(InputName).cp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l $(InputPath) 
	sed -f $(InputName).sed $(InputName).c > $(InputName).cp 
	@del $(InputName).c 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

USERDEP__DXFLX="$(InputName).sed"	
# Begin Custom Build
InputPath=.\DXFLX.L
InputName=DXFLX

"$(InputName).cp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l $(InputPath) 
	sed -f $(InputName).sed $(InputName).c > $(InputName).cp 
	@del $(InputName).c 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DXFY.Y

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

USERDEP__DXFY_="$(InputName).sed"	
# Begin Custom Build
InputPath=.\DXFY.Y
InputName=DXFY

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -d $(InputPath) -C$(InputName).c 
	sed -f $(InputName).sed $(InputName).c > $(InputName).cpp 
	@del $(InputName).c 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

USERDEP__DXFY_="$(InputName).sed"	
# Begin Custom Build
InputPath=.\DXFY.Y
InputName=DXFY

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -d $(InputPath) -C$(InputName).c 
	sed -f $(InputName).sed $(InputName).c > $(InputName).cpp 
	@del $(InputName).c 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\DXFIMP.TPL

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

USERDEP__DXFIM="makefile"	
# Begin Custom Build
InputPath=.\DXFIMP.TPL

"dxfimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo dxfimp.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

USERDEP__DXFIM="makefile"	
# Begin Custom Build
InputPath=.\DXFIMP.TPL

"dxfimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo dxfimp.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DXFIMPV.TPL

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

USERDEP__DXFIMP="makefile"	
# Begin Custom Build
InputPath=.\DXFIMPV.TPL

"dxfimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo dxfimp.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

USERDEP__DXFIMP="makefile"	
# Begin Custom Build
InputPath=.\DXFIMPV.TPL

"dxfimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo dxfimp.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
