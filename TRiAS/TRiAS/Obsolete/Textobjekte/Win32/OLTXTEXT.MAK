# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "OLTXTEXT.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/OLTXTEXT.dll $(OUTDIR)/OLTXTEXT.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /WX /GX /YX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MT /W3 /WX /GX /YX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"OLTXTEXT.pch"\
 /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"OLTXTEXT.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"OLTXTEXT.bsc" 
BSC32_SBRS= \
	$(INTDIR)/ENOBAB1.SBR \
	$(INTDIR)/TEXTEX1.SBR \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/ENBXVOLL.SBR \
	$(INTDIR)/TEXTDLG1.SBR \
	$(INTDIR)/ENUMOBJ.SBR \
	$(INTDIR)/HELPER.SBR \
	$(INTDIR)/DEL.SBR \
	$(INTDIR)/ENOBMEN.SBR \
	$(INTDIR)/DLGABH.SBR \
	$(INTDIR)/ENREL.SBR \
	$(INTDIR)/TEXTP.SBR \
	$(INTDIR)/ITERATOR.SBR \
	$(INTDIR)/TXTRDLG1.SBR

$(OUTDIR)/OLTXTEXT.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"OLTXTEXT.pdb" /MACHINE:I386 /DEF:".\OLTXTEXT.DEF"\
 /OUT:$(OUTDIR)/"OLTXTEXT.dll" /IMPLIB:$(OUTDIR)/"OLTXTEXT.lib" 
DEF_FILE=.\OLTXTEXT.DEF
LINK32_OBJS= \
	$(INTDIR)/ENOBAB1.OBJ \
	$(INTDIR)/TEXTEX1.OBJ \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/ENBXVOLL.OBJ \
	$(INTDIR)/TEXTDLG1.OBJ \
	$(INTDIR)/ENUMOBJ.OBJ \
	$(INTDIR)/HELPER.OBJ \
	$(INTDIR)/DEL.OBJ \
	$(INTDIR)/ENOBMEN.OBJ \
	$(INTDIR)/DLGABH.OBJ \
	$(INTDIR)/ENREL.OBJ \
	$(INTDIR)/TEXTP.OBJ \
	$(INTDIR)/ITERATOR.OBJ \
	$(INTDIR)/TXTRDLG1.OBJ \
	$(INTDIR)/OLTXTEXT.res

$(OUTDIR)/OLTXTEXT.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/oltxtxtd.ext $(OUTDIR)/OLTXTEXT.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /I "c:\TRIASDEV\oltxtext" /D "_DEBUG" /D "_AFXDLL" /D "_AFXCTL" /D "_MBCS" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /I "c:\TRIASDEV\oltxtext" /D\
 "_DEBUG" /D "_AFXDLL" /D "_AFXCTL" /D "_MBCS" /D "EBWIN32" /D "MSWIND" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__"\
 /Fr$(INTDIR)/ /Fp$(OUTDIR)/"OLTXTEXT.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"OLTXTEXT.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".\\" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"OLTXTEXT.res" /i ".\\" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"OLTXTEXT.bsc" 
BSC32_SBRS= \
	$(INTDIR)/ENOBAB1.SBR \
	$(INTDIR)/TEXTEX1.SBR \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/ENBXVOLL.SBR \
	$(INTDIR)/TEXTDLG1.SBR \
	$(INTDIR)/ENUMOBJ.SBR \
	$(INTDIR)/HELPER.SBR \
	$(INTDIR)/DEL.SBR \
	$(INTDIR)/ENOBMEN.SBR \
	$(INTDIR)/DLGABH.SBR \
	$(INTDIR)/ENREL.SBR \
	$(INTDIR)/TEXTP.SBR \
	$(INTDIR)/ITERATOR.SBR \
	$(INTDIR)/TXTRDLG1.SBR

$(OUTDIR)/OLTXTEXT.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 ixtmfd32.lib stdcppd.lib cont32d.lib mfcans32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /OUT:"windebug\oltxtxtd.ext"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=ixtmfd32.lib stdcppd.lib cont32d.lib mfcans32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL\
 /INCREMENTAL:yes /PDB:$(OUTDIR)/"OLTXTEXT.pdb" /DEBUG /MACHINE:I386\
 /DEF:".\OLTXTEXT.DEF" /OUT:"windebug\oltxtxtd.ext"\
 /IMPLIB:$(OUTDIR)/"OLTXTEXT.lib" 
DEF_FILE=.\OLTXTEXT.DEF
LINK32_OBJS= \
	$(INTDIR)/ENOBAB1.OBJ \
	$(INTDIR)/TEXTEX1.OBJ \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/ENBXVOLL.OBJ \
	$(INTDIR)/TEXTDLG1.OBJ \
	$(INTDIR)/ENUMOBJ.OBJ \
	$(INTDIR)/HELPER.OBJ \
	$(INTDIR)/DEL.OBJ \
	$(INTDIR)/ENOBMEN.OBJ \
	$(INTDIR)/DLGABH.OBJ \
	$(INTDIR)/ENREL.OBJ \
	$(INTDIR)/TEXTP.OBJ \
	$(INTDIR)/ITERATOR.OBJ \
	$(INTDIR)/TXTRDLG1.OBJ \
	$(INTDIR)/OLTXTEXT.res

$(OUTDIR)/oltxtxtd.ext : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENOBAB1.CPP
DEP_ENOBA=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ENOBAB1.OBJ :  $(SOURCE)  $(DEP_ENOBA) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.CPP
DEP_TEXTE=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\INCLUDE\xtsnguid.h\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTGUID.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\textdlg.h\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\txtredlg.h\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\DLGABH.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\IGENTEXT.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTP.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	\TRIASDEV.MVC\INCLUDE\EONRGUID.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/TEXTEX1.OBJ :  $(SOURCE)  $(DEP_TEXTE) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.CPP
DEP_STDAF=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /WX /GX /YX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"OLTXTEXT.pch"\
 /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD CPP /Yc"stdafx.h"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /I "c:\TRIASDEV\oltxtext" /D\
 "_DEBUG" /D "_AFXDLL" /D "_AFXCTL" /D "_MBCS" /D "EBWIN32" /D "MSWIND" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__"\
 /Fr$(INTDIR)/ /Fp$(OUTDIR)/"OLTXTEXT.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"OLTXTEXT.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENBXVOLL.CPP
DEP_ENBXV=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ENBXVOLL.OBJ :  $(SOURCE)  $(DEP_ENBXV) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTDLG1.CPP
DEP_TEXTD=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\textdlg.h\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/TEXTDLG1.OBJ :  $(SOURCE)  $(DEP_TEXTD) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENUMOBJ.CPP
DEP_ENUMO=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\DEL.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ENUMOBJ.OBJ :  $(SOURCE)  $(DEP_ENUMO) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.CPP
DEP_HELPE=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/HELPER.OBJ :  $(SOURCE)  $(DEP_HELPE) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\DEL.CPP
DEP_DEL_C=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\DEL.HPP\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/DEL.OBJ :  $(SOURCE)  $(DEP_DEL_C) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENOBMEN.CPP
DEP_ENOBM=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ENOBMEN.OBJ :  $(SOURCE)  $(DEP_ENOBM) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\DLGABH.CPP
DEP_DLGAB=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\DLGABH.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.HPP\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/DLGABH.OBJ :  $(SOURCE)  $(DEP_DLGAB) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENREL.CPP
DEP_ENREL=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\DEL.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ENREL.OBJ :  $(SOURCE)  $(DEP_ENREL) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTP.CPP
DEP_TEXTP=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\IGENTEXT.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTP.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/TEXTP.OBJ :  $(SOURCE)  $(DEP_TEXTP) $(INTDIR) $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.CPP
DEP_ITERA=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.HPP\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/ITERATOR.OBJ :  $(SOURCE)  $(DEP_ITERA) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TXTRDLG1.CPP
DEP_TXTRD=\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\txtredlg.h\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.H\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\xtencunk.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnaux.hxx\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\WAITCUR.HPP\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSION.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.HPP\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\triasdev.mvc\include\istatus.h\
	.\VERSIO32.H\
	\TRIASDEV.MVC\XTENSION\OLTXTEXT\VERSIO16.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

$(INTDIR)/TXTRDLG1.OBJ :  $(SOURCE)  $(DEP_TXTRD) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OLTXTEXT.RC
DEP_OLTXT=\
	.\OLTXTEXT.RCV

$(INTDIR)/OLTXTEXT.res :  $(SOURCE)  $(DEP_OLTXT) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OLTXTEXT.DEF
# End Source File
# End Group
# End Project
################################################################################
