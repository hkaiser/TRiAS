# Microsoft Developer Studio Project File - Name="Tfrm32l" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Tfrm32l - Win32 Framework LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4l.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4l.mak" CFG="Tfrm32l - Win32 Framework LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tfrm32l - Win32 Framework LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Tfrm32l - Win32 Framework LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/Framework/TRiAS Framework/TRiAS Framework Startup Library", ZGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Fp".\Release\tfrmlr.pch" /Yu"tfrmpre.hxx" /Fd".\Release/tfrmlr.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Release\Tfrmlr.lib"
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\Tfrmlr.lib
TargetName=Tfrmlr
InputPath=.\Release\Tfrmlr.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Fp".\Debug\tfrmld.pch" /Yu"tfrmpre.hxx" /Fd".\Debug\tfrmld.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\tfrmld.lib"
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\tfrmld.lib
TargetName=tfrmld
InputPath=.\Debug\tfrmld.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Tfrm32l - Win32 Framework LIB Release"
# Name "Tfrm32l - Win32 Framework LIB Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\APPIDLE.CXX
# ADD CPP /Yu"tfrmlib.hxx"
# End Source File
# Begin Source File

SOURCE=.\APPINIT.CXX
# ADD CPP /Yu"tfrmlib.hxx"
# End Source File
# Begin Source File

SOURCE=.\APPSTART.CXX
# ADD CPP /Yu"tfrmlib.hxx"
# End Source File
# Begin Source File

SOURCE=.\APPSTRT2.CXX
# ADD CPP /Yu"tfrmlib.hxx"
# End Source File
# Begin Source File

SOURCE=.\COMMONVU.CXX
# ADD CPP /Yu"tfrmlib.hxx"
# End Source File
# Begin Source File

SOURCE=.\TFRMLIB.CXX
# ADD CPP /Yc"tfrmlib.hxx"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\TFRMWORK.INC\_comonvu.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\_DSFIX.HXX
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\_link.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\_runtime.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\Cv_imp.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\Cv_impi.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\Cvd.hxx
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\CVRESID.H
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\MESSAGES.H
# End Source File
# Begin Source File

SOURCE=.\TFRMLIB.HXX
# End Source File
# Begin Source File

SOURCE=C:\MSDEV\STDCPP.INC\TSTRING
# End Source File
# Begin Source File

SOURCE=C:\MSDEV\STDCPP.INC\TSTRING.HPP
# End Source File
# Begin Source File

SOURCE=..\TFRMWORK.INC\Winfns.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
