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
!MESSAGE NMAKE /f "kompobj.mak" CFG="Win32 Debug"
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

ALL : $(OUTDIR)/kompobj.dll $(OUTDIR)/kompobj.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"kompobj.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"KOMPOBJ.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"kompobj.bsc" 
BSC32_SBRS= \
	$(INTDIR)/KOMPOBJX.SBR \
	$(INTDIR)/KOMPOBJP.SBR

$(OUTDIR)/kompobj.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"kompobj.pdb" /MACHINE:I386 /DEF:".\KOMPOBJ.DEF"\
 /OUT:$(OUTDIR)/"kompobj.dll" /IMPLIB:$(OUTDIR)/"kompobj.lib" 
DEF_FILE=.\KOMPOBJ.DEF
LINK32_OBJS= \
	$(INTDIR)/KOMPOBJ.res \
	$(INTDIR)/KOMPOBJX.OBJ \
	$(INTDIR)/KOMPOBJP.OBJ

$(OUTDIR)/kompobj.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : $(OUTDIR)/kompobjd.ext $(OUTDIR)/kompobj.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__XT" /D "__CV__" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "__XTNSNDLL__" /Fp"WinDebug/kompobjd.pch" /Yu"kompobjp.hxx" /Fd"WinDebug/kompobjd.pdb" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__XT" /D "__CV__" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D\
 "__XTNSNDLL__" /Fp"WinDebug/kompobjd.pch" /Yu"kompobjp.hxx" /Fo$(INTDIR)/\
 /Fd"WinDebug/kompobjd.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"KOMPOBJ.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"kompobj.bsc" 
BSC32_SBRS= \
	

$(OUTDIR)/kompobj.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 stdcppd.lib ixtnsd32.lib cont32d.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /DLL /PDB:"WinDebug/kompobjd.pdb" /DEBUG /MACHINE:I386 /OUT:"WinDebug/kompobjd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=stdcppd.lib ixtnsd32.lib cont32d.lib tfrm32d.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /DLL\
 /INCREMENTAL:yes /PDB:"WinDebug/kompobjd.pdb" /DEBUG /MACHINE:I386\
 /DEF:".\KOMPOBJ.DEF" /OUT:"WinDebug/kompobjd.ext"\
 /IMPLIB:$(OUTDIR)/"kompobj.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE=.\KOMPOBJ.DEF
LINK32_OBJS= \
	$(INTDIR)/KOMPOBJ.res \
	$(INTDIR)/KOMPOBJX.OBJ \
	$(INTDIR)/KOMPOBJP.OBJ

$(OUTDIR)/kompobjd.ext : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\KOMPOBJ.RC
DEP_KOMPO=\
	.\KOMPOBJ.RCV

$(INTDIR)/KOMPOBJ.res :  $(SOURCE)  $(DEP_KOMPO) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPOBJ.DEF
# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPOBJX.CXX
DEP_KOMPOB=\
	.\VERSION.H\
	.\CGOBJECT.HXX\
	.\VERSIO32.H

$(INTDIR)/KOMPOBJX.OBJ :  $(SOURCE)  $(DEP_KOMPOB) $(INTDIR)\
 $(INTDIR)/KOMPOBJP.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPOBJP.CXX

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/KOMPOBJP.OBJ :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"kompobj.pch" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD CPP /Yc"kompobjp.hxx"

$(INTDIR)/KOMPOBJP.OBJ :  $(SOURCE)  $(INTDIR)
   $(CPP) /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__XT" /D "__CV__" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D\
 "__XTNSNDLL__" /Fp"WinDebug/kompobjd.pch" /Yc"kompobjp.hxx" /Fo$(INTDIR)/\
 /Fd"WinDebug/kompobjd.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
