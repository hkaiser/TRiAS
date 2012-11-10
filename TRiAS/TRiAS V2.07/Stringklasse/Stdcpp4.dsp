# Microsoft Developer Studio Project File - Name="Stdcpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Stdcpp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Stdcpp4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stdcpp4.mak" CFG="Stdcpp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stdcpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Stdcpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/Stringklasse", OYHAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe

!IF  "$(CFG)" == "Stdcpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\stdcppr"
# PROP Intermediate_Dir ".\stdcppr"
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Z7 /O2 /I "..\stdcpp.inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Fr
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\stdcppr\stdcppr.lib"

!ELSEIF  "$(CFG)" == "Stdcpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\stdcppd"
# PROP Intermediate_Dir ".\stdcppd"
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Z7 /Od /Ob1 /I "..\stdcpp.inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Fr
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\stdcppd\stdcppd.lib"

!ENDIF 

# Begin Target

# Name "Stdcpp - Win32 Release"
# Name "Stdcpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BADCAST.CPP
# End Source File
# Begin Source File

SOURCE=.\EXCEPTIO.CPP
# End Source File
# Begin Source File

SOURCE=.\fnamestr.cpp
# End Source File
# Begin Source File

SOURCE=.\INVALIDA.CPP
# End Source File
# Begin Source File

SOURCE=.\LENGTHER.CPP
# End Source File
# Begin Source File

SOURCE=.\NEW.CPP
# End Source File
# Begin Source File

SOURCE=.\OUTOFRAN.CPP
# End Source File
# Begin Source File

SOURCE=.\OVERFLOW.CPP
# End Source File
# Begin Source File

SOURCE=.\STRAPC.CPP
# End Source File
# Begin Source File

SOURCE=.\STRAPS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRAPX.CPP
# End Source File
# Begin Source File

SOURCE=.\STRASC.CPP
# End Source File
# Begin Source File

SOURCE=.\STRASS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRASX.CPP
# End Source File
# Begin Source File

SOURCE=.\STRCOC.CPP
# End Source File
# Begin Source File

SOURCE=.\STRCOPY.CPP
# End Source File
# Begin Source File

SOURCE=.\STRCOS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRCOX.CPP
# End Source File
# Begin Source File

SOURCE=.\STRFFNS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRFFS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRFIS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRFLNS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRFLS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRGET.CPP
# End Source File
# Begin Source File

SOURCE=.\strgline.cpp
# End Source File
# Begin Source File

SOURCE=.\STRINC.CPP
# End Source File
# Begin Source File

SOURCE=.\STRING.CPP
# End Source File
# Begin Source File

SOURCE=.\STRINS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRINX.CPP
# End Source File
# Begin Source File

SOURCE=.\STRPUT.CPP
# End Source File
# Begin Source File

SOURCE=.\STRREC.CPP
# End Source File
# Begin Source File

SOURCE=.\STRREM.CPP
# End Source File
# Begin Source File

SOURCE=.\STRRES.CPP
# End Source File
# Begin Source File

SOURCE=.\STRREX.CPP
# End Source File
# Begin Source File

SOURCE=.\STRRFIS.CPP
# End Source File
# Begin Source File

SOURCE=.\STRXSTR.CPP
# End Source File
# Begin Source File

SOURCE=.\TERMINAT.CPP
# End Source File
# Begin Source File

SOURCE=.\UNEXPECT.CPP
# End Source File
# Begin Source File

SOURCE=.\XDOMAIN.CPP
# End Source File
# Begin Source File

SOURCE=.\XLOGIC.CPP
# End Source File
# Begin Source File

SOURCE=.\XRANGE.CPP
# End Source File
# Begin Source File

SOURCE=.\XRUNTIME.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
