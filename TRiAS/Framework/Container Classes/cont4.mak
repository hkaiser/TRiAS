# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=cont32 - Win32 Container Release
!MESSAGE No configuration specified.  Defaulting to cont32 - Win32 Container\
 Release.
!ENDIF 

!IF "$(CFG)" != "cont32 - Win32 Container Release" && "$(CFG)" !=\
 "cont32 - Win32 Container Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "cont4.mak" CFG="cont32 - Win32 Container Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cont32 - Win32 Container Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cont32 - Win32 Container Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "cont32 - Win32 Container Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

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
# Begin Custom Macros
TargetName=containr
# End Custom Macros

ALL : "$(OUTDIR)\containr.dll" "c:\trias\trias.rel\containr.dll"

CLEAN : 
	-@erase "$(INTDIR)\ARRAY.OBJ"
	-@erase "$(INTDIR)\BINNODE.OBJ"
	-@erase "$(INTDIR)\cont32.res"
	-@erase "$(INTDIR)\cont4.pch"
	-@erase "$(INTDIR)\CONTAINR.OBJ"
	-@erase "$(INTDIR)\CONTASRT.OBJ"
	-@erase "$(INTDIR)\CONTPRE.OBJ"
	-@erase "$(INTDIR)\copttree.obj"
	-@erase "$(INTDIR)\CRSTART.OBJ"
	-@erase "$(INTDIR)\DCREATOR.OBJ"
	-@erase "$(INTDIR)\DEF.OBJ"
	-@erase "$(INTDIR)\DELTREE.OBJ"
	-@erase "$(INTDIR)\HASH.OBJ"
	-@erase "$(INTDIR)\HASHNODE.OBJ"
	-@erase "$(INTDIR)\HLISNODE.OBJ"
	-@erase "$(INTDIR)\KEYED.OBJ"
	-@erase "$(INTDIR)\KEYNODE.OBJ"
	-@erase "$(INTDIR)\LIST.OBJ"
	-@erase "$(INTDIR)\LOCK.OBJ"
	-@erase "$(INTDIR)\NAVIGATR.OBJ"
	-@erase "$(INTDIR)\NODE.OBJ"
	-@erase "$(INTDIR)\OPTTREE.OBJ"
	-@erase "$(INTDIR)\P5TICKER.OBJ"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\RING.OBJ"
	-@erase "$(INTDIR)\SEQ.OBJ"
	-@erase "$(INTDIR)\TABLE.OBJ"
	-@erase "$(INTDIR)\TRANSEX.OBJ"
	-@erase "$(INTDIR)\TREE.OBJ"
	-@erase "$(OUTDIR)\containr.dll"
	-@erase "$(OUTDIR)\containr.exp"
	-@erase "$(OUTDIR)\containr.lib"
	-@erase "c:\trias\trias.rel\containr.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/cont32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /Yu"contpre.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/cont32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cont4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"WinRel/containr.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/containr.pdb"\
 /machine:I386 /out:"$(OUTDIR)/containr.dll" /implib:"$(OUTDIR)/containr.lib"\
 /SUBSYSTEM:windows,4.0 
LINK32_OBJS= \
	"$(INTDIR)\ARRAY.OBJ" \
	"$(INTDIR)\BINNODE.OBJ" \
	"$(INTDIR)\cont32.res" \
	"$(INTDIR)\CONTAINR.OBJ" \
	"$(INTDIR)\CONTASRT.OBJ" \
	"$(INTDIR)\CONTPRE.OBJ" \
	"$(INTDIR)\copttree.obj" \
	"$(INTDIR)\CRSTART.OBJ" \
	"$(INTDIR)\DCREATOR.OBJ" \
	"$(INTDIR)\DEF.OBJ" \
	"$(INTDIR)\DELTREE.OBJ" \
	"$(INTDIR)\HASH.OBJ" \
	"$(INTDIR)\HASHNODE.OBJ" \
	"$(INTDIR)\HLISNODE.OBJ" \
	"$(INTDIR)\KEYED.OBJ" \
	"$(INTDIR)\KEYNODE.OBJ" \
	"$(INTDIR)\LIST.OBJ" \
	"$(INTDIR)\LOCK.OBJ" \
	"$(INTDIR)\NAVIGATR.OBJ" \
	"$(INTDIR)\NODE.OBJ" \
	"$(INTDIR)\OPTTREE.OBJ" \
	"$(INTDIR)\P5TICKER.OBJ" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RING.OBJ" \
	"$(INTDIR)\SEQ.OBJ" \
	"$(INTDIR)\TABLE.OBJ" \
	"$(INTDIR)\TRANSEX.OBJ" \
	"$(INTDIR)\TREE.OBJ"

"$(OUTDIR)\containr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\WinRel
TargetPath=.\WinRel\containr.dll
TargetName=containr
InputPath=.\WinRel\containr.dll
SOURCE=$(InputPath)

"c:\trias\trias.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F "$(TargetPath)" c:\trias\trias.rel
   xcopy /F "$(OutDir)\$(TargetName).lib" c:\trias\lib

# End Custom Build

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug4"
# PROP Intermediate_Dir "Debug4"
OUTDIR=.\Debug4
INTDIR=.\Debug4
# Begin Custom Macros
TargetName=containd
# End Custom Macros

ALL : "$(OUTDIR)\containd.dll" "$(OUTDIR)\cont4.bsc"\
 "c:\trias\trias.deb\containd.dll"

CLEAN : 
	-@erase "$(INTDIR)\ARRAY.OBJ"
	-@erase "$(INTDIR)\ARRAY.SBR"
	-@erase "$(INTDIR)\AssertDlg.obj"
	-@erase "$(INTDIR)\AssertDlg.sbr"
	-@erase "$(INTDIR)\BINNODE.OBJ"
	-@erase "$(INTDIR)\BINNODE.SBR"
	-@erase "$(INTDIR)\cont32.res"
	-@erase "$(INTDIR)\cont32d.pch"
	-@erase "$(INTDIR)\containd.idb"
	-@erase "$(INTDIR)\containd.pdb"
	-@erase "$(INTDIR)\CONTAINR.OBJ"
	-@erase "$(INTDIR)\CONTAINR.SBR"
	-@erase "$(INTDIR)\CONTASRT.OBJ"
	-@erase "$(INTDIR)\CONTASRT.SBR"
	-@erase "$(INTDIR)\CONTPRE.OBJ"
	-@erase "$(INTDIR)\CONTPRE.SBR"
	-@erase "$(INTDIR)\copttree.obj"
	-@erase "$(INTDIR)\copttree.sbr"
	-@erase "$(INTDIR)\CRSTART.OBJ"
	-@erase "$(INTDIR)\CRSTART.SBR"
	-@erase "$(INTDIR)\DCREATOR.OBJ"
	-@erase "$(INTDIR)\DCREATOR.SBR"
	-@erase "$(INTDIR)\DEF.OBJ"
	-@erase "$(INTDIR)\DEF.SBR"
	-@erase "$(INTDIR)\DELTREE.OBJ"
	-@erase "$(INTDIR)\DELTREE.SBR"
	-@erase "$(INTDIR)\DumpBuffer.obj"
	-@erase "$(INTDIR)\DumpBuffer.sbr"
	-@erase "$(INTDIR)\HASH.OBJ"
	-@erase "$(INTDIR)\HASH.SBR"
	-@erase "$(INTDIR)\HASHNODE.OBJ"
	-@erase "$(INTDIR)\HASHNODE.SBR"
	-@erase "$(INTDIR)\HLISNODE.OBJ"
	-@erase "$(INTDIR)\HLISNODE.SBR"
	-@erase "$(INTDIR)\KEYED.OBJ"
	-@erase "$(INTDIR)\KEYED.SBR"
	-@erase "$(INTDIR)\KEYNODE.OBJ"
	-@erase "$(INTDIR)\KEYNODE.SBR"
	-@erase "$(INTDIR)\LIST.OBJ"
	-@erase "$(INTDIR)\LIST.SBR"
	-@erase "$(INTDIR)\LOCK.OBJ"
	-@erase "$(INTDIR)\LOCK.SBR"
	-@erase "$(INTDIR)\NAVIGATR.OBJ"
	-@erase "$(INTDIR)\NAVIGATR.SBR"
	-@erase "$(INTDIR)\NODE.OBJ"
	-@erase "$(INTDIR)\NODE.SBR"
	-@erase "$(INTDIR)\OPTTREE.OBJ"
	-@erase "$(INTDIR)\OPTTREE.SBR"
	-@erase "$(INTDIR)\P5TICKER.OBJ"
	-@erase "$(INTDIR)\P5TICKER.SBR"
	-@erase "$(INTDIR)\PE_Debug.obj"
	-@erase "$(INTDIR)\PE_Debug.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\RING.OBJ"
	-@erase "$(INTDIR)\RING.SBR"
	-@erase "$(INTDIR)\SEQ.OBJ"
	-@erase "$(INTDIR)\SEQ.SBR"
	-@erase "$(INTDIR)\TABLE.OBJ"
	-@erase "$(INTDIR)\TABLE.SBR"
	-@erase "$(INTDIR)\TRANSEX.OBJ"
	-@erase "$(INTDIR)\TRANSEX.SBR"
	-@erase "$(INTDIR)\TREE.OBJ"
	-@erase "$(INTDIR)\TREE.SBR"
	-@erase "$(INTDIR)\VerbAssert.obj"
	-@erase "$(INTDIR)\VerbAssert.sbr"
	-@erase "$(OUTDIR)\cont4.bsc"
	-@erase "$(OUTDIR)\containd.dll"
	-@erase "$(OUTDIR)\containd.exp"
	-@erase "$(OUTDIR)\containd.lib"
	-@erase "c:\trias\trias.deb\containd.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/cont32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR /Fp"Debug4/cont32d.pch" /Yu"contpre.hxx" /Fd"Debug4/containd.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c 
CPP_OBJS=.\Debug4/
CPP_SBRS=.\Debug4/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/cont32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cont4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ARRAY.SBR" \
	"$(INTDIR)\AssertDlg.sbr" \
	"$(INTDIR)\BINNODE.SBR" \
	"$(INTDIR)\CONTAINR.SBR" \
	"$(INTDIR)\CONTASRT.SBR" \
	"$(INTDIR)\CONTPRE.SBR" \
	"$(INTDIR)\copttree.sbr" \
	"$(INTDIR)\CRSTART.SBR" \
	"$(INTDIR)\DCREATOR.SBR" \
	"$(INTDIR)\DEF.SBR" \
	"$(INTDIR)\DELTREE.SBR" \
	"$(INTDIR)\DumpBuffer.sbr" \
	"$(INTDIR)\HASH.SBR" \
	"$(INTDIR)\HASHNODE.SBR" \
	"$(INTDIR)\HLISNODE.SBR" \
	"$(INTDIR)\KEYED.SBR" \
	"$(INTDIR)\KEYNODE.SBR" \
	"$(INTDIR)\LIST.SBR" \
	"$(INTDIR)\LOCK.SBR" \
	"$(INTDIR)\NAVIGATR.SBR" \
	"$(INTDIR)\NODE.SBR" \
	"$(INTDIR)\OPTTREE.SBR" \
	"$(INTDIR)\P5TICKER.SBR" \
	"$(INTDIR)\PE_Debug.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\RING.SBR" \
	"$(INTDIR)\SEQ.SBR" \
	"$(INTDIR)\TABLE.SBR" \
	"$(INTDIR)\TRANSEX.SBR" \
	"$(INTDIR)\TREE.SBR" \
	"$(INTDIR)\VerbAssert.sbr"

"$(OUTDIR)\cont4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /debugtype:both /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"Debug4/containd.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/containd.pdb" /debug\
 /debugtype:both /machine:I386 /nodefaultlib:"msvcrt.lib"\
 /out:"$(OUTDIR)/containd.dll" /implib:"$(OUTDIR)/containd.lib"\
 /SUBSYSTEM:windows,4.0 
LINK32_OBJS= \
	"$(INTDIR)\ARRAY.OBJ" \
	"$(INTDIR)\AssertDlg.obj" \
	"$(INTDIR)\BINNODE.OBJ" \
	"$(INTDIR)\cont32.res" \
	"$(INTDIR)\CONTAINR.OBJ" \
	"$(INTDIR)\CONTASRT.OBJ" \
	"$(INTDIR)\CONTPRE.OBJ" \
	"$(INTDIR)\copttree.obj" \
	"$(INTDIR)\CRSTART.OBJ" \
	"$(INTDIR)\DCREATOR.OBJ" \
	"$(INTDIR)\DEF.OBJ" \
	"$(INTDIR)\DELTREE.OBJ" \
	"$(INTDIR)\DumpBuffer.obj" \
	"$(INTDIR)\HASH.OBJ" \
	"$(INTDIR)\HASHNODE.OBJ" \
	"$(INTDIR)\HLISNODE.OBJ" \
	"$(INTDIR)\KEYED.OBJ" \
	"$(INTDIR)\KEYNODE.OBJ" \
	"$(INTDIR)\LIST.OBJ" \
	"$(INTDIR)\LOCK.OBJ" \
	"$(INTDIR)\NAVIGATR.OBJ" \
	"$(INTDIR)\NODE.OBJ" \
	"$(INTDIR)\OPTTREE.OBJ" \
	"$(INTDIR)\P5TICKER.OBJ" \
	"$(INTDIR)\PE_Debug.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RING.OBJ" \
	"$(INTDIR)\SEQ.OBJ" \
	"$(INTDIR)\TABLE.OBJ" \
	"$(INTDIR)\TRANSEX.OBJ" \
	"$(INTDIR)\TREE.OBJ" \
	"$(INTDIR)\VerbAssert.obj"

"$(OUTDIR)\containd.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\containd.dll
TargetName=containd
InputPath=.\Debug4\containd.dll
SOURCE=$(InputPath)

"c:\trias\trias.deb\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F "$(TargetPath)" c:\trias\trias.deb
   xcopy /F "$(OutDir)\$(TargetName).pdb" c:\trias.deb
   xcopy /F "$(OutDir)\$(TargetName).lib" c:\trias\lib
   xcopy /F "$(OutDir)\$(TargetName).pdb" c:\trias\lib

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "cont32 - Win32 Container Release"
# Name "cont32 - Win32 Container Debug"

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NAVIGATR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_NAVIG=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\NAVIGATR.OBJ" : $(SOURCE) $(DEP_CPP_NAVIG) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_NAVIG=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\NAVIGATR.OBJ" : $(SOURCE) $(DEP_CPP_NAVIG) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\NAVIGATR.SBR" : $(SOURCE) $(DEP_CPP_NAVIG) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SEQ.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_SEQ_C=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\SEQ.OBJ" : $(SOURCE) $(DEP_CPP_SEQ_C) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_SEQ_C=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\SEQ.OBJ" : $(SOURCE) $(DEP_CPP_SEQ_C) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\SEQ.SBR" : $(SOURCE) $(DEP_CPP_SEQ_C) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OPTTREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_OPTTR=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\OPTTREE.OBJ" : $(SOURCE) $(DEP_CPP_OPTTR) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_OPTTR=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\OPTTREE.OBJ" : $(SOURCE) $(DEP_CPP_OPTTR) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\OPTTREE.SBR" : $(SOURCE) $(DEP_CPP_OPTTR) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYED.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_KEYED=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\KEYED.OBJ" : $(SOURCE) $(DEP_CPP_KEYED) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_KEYED=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KEYED.OBJ" : $(SOURCE) $(DEP_CPP_KEYED) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\KEYED.SBR" : $(SOURCE) $(DEP_CPP_KEYED) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TABLE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_TABLE=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\TABLE.OBJ" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_TABLE=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TABLE.OBJ" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\TABLE.SBR" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELTREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_DELTR=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DELTREE.HXX"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\DELTREE.OBJ" : $(SOURCE) $(DEP_CPP_DELTR) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_DELTR=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DELTREE.HXX"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DELTREE.OBJ" : $(SOURCE) $(DEP_CPP_DELTR) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\DELTREE.SBR" : $(SOURCE) $(DEP_CPP_DELTR) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BINNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_BINNO=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\BINNODE.OBJ" : $(SOURCE) $(DEP_CPP_BINNO) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_BINNO=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\BINNODE.OBJ" : $(SOURCE) $(DEP_CPP_BINNO) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\BINNODE.SBR" : $(SOURCE) $(DEP_CPP_BINNO) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARRAY.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_ARRAY=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\ARRAY.OBJ" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_ARRAY=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\ARRAY.OBJ" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\ARRAY.SBR" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_NODE_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\NODE.OBJ" : $(SOURCE) $(DEP_CPP_NODE_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_NODE_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\NODE.OBJ" : $(SOURCE) $(DEP_CPP_NODE_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\NODE.SBR" : $(SOURCE) $(DEP_CPP_NODE_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIST.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_LIST_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\LIST.OBJ" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_LIST_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\LIST.OBJ" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\LIST.SBR" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEF.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_DEF_C=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\DEF.OBJ" : $(SOURCE) $(DEP_CPP_DEF_C) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_DEF_C=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DEF.OBJ" : $(SOURCE) $(DEP_CPP_DEF_C) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\DEF.SBR" : $(SOURCE) $(DEP_CPP_DEF_C) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DCREATOR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_DCREA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DCREATOR.HXX"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\DCREATOR.OBJ" : $(SOURCE) $(DEP_CPP_DCREA) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_DCREA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DCREATOR.HXX"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DCREATOR.OBJ" : $(SOURCE) $(DEP_CPP_DCREA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\DCREATOR.SBR" : $(SOURCE) $(DEP_CPP_DCREA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HASH.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_HASH_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\HASH.OBJ" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_HASH_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\HASH.OBJ" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\HASH.SBR" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HLISNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_HLISN=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\HLISNODE.OBJ" : $(SOURCE) $(DEP_CPP_HLISN) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_HLISN=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\HLISNODE.OBJ" : $(SOURCE) $(DEP_CPP_HLISN) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\HLISNODE.SBR" : $(SOURCE) $(DEP_CPP_HLISN) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CONTAINR.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_CONTA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\CONTAINR.OBJ" : $(SOURCE) $(DEP_CPP_CONTA) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_CONTA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /MDd /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\CONTAINR.OBJ" : $(SOURCE) $(DEP_CPP_CONTA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\CONTAINR.SBR" : $(SOURCE) $(DEP_CPP_CONTA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HASHNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_HASHN=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\HASHNODE.OBJ" : $(SOURCE) $(DEP_CPP_HASHN) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_HASHN=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\HASHNODE.OBJ" : $(SOURCE) $(DEP_CPP_HASHN) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\HASHNODE.SBR" : $(SOURCE) $(DEP_CPP_HASHN) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RING.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_RING_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\RING.OBJ" : $(SOURCE) $(DEP_CPP_RING_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_RING_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\RING.OBJ" : $(SOURCE) $(DEP_CPP_RING_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\RING.SBR" : $(SOURCE) $(DEP_CPP_RING_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYNODE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_KEYNO=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\KEYNODE.OBJ" : $(SOURCE) $(DEP_CPP_KEYNO) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_KEYNO=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KEYNODE.OBJ" : $(SOURCE) $(DEP_CPP_KEYNO) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\KEYNODE.SBR" : $(SOURCE) $(DEP_CPP_KEYNO) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TREE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_TREE_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\TREE.OBJ" : $(SOURCE) $(DEP_CPP_TREE_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_TREE_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TREE.OBJ" : $(SOURCE) $(DEP_CPP_TREE_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\TREE.SBR" : $(SOURCE) $(DEP_CPP_TREE_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOCK.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_LOCK_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\LOCK.OBJ" : $(SOURCE) $(DEP_CPP_LOCK_) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_LOCK_=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\LOCK.OBJ" : $(SOURCE) $(DEP_CPP_LOCK_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\LOCK.SBR" : $(SOURCE) $(DEP_CPP_LOCK_) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CRSTART.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_CRSTA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\REGISTRY.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

"$(INTDIR)\CRSTART.OBJ" : $(SOURCE) $(DEP_CPP_CRSTA) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yu"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_CRSTA=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\REGISTRY.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yu"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\CRSTART.OBJ" : $(SOURCE) $(DEP_CPP_CRSTA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\CRSTART.SBR" : $(SOURCE) $(DEP_CPP_CRSTA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cont32.rc

"$(INTDIR)\cont32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CONTPRE.CXX

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 0
DEP_CPP_CONTP=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /GX /Yc"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__CTRDLL__" /Fp"$(INTDIR)/cont4.pch" /Yc"contpre.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\CONTPRE.OBJ" : $(SOURCE) $(DEP_CPP_CONTP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cont4.pch" : $(SOURCE) $(DEP_CPP_CONTP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_CONTP=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	
# ADD CPP /Yc"contpre.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yc"contpre.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\CONTPRE.OBJ" : $(SOURCE) $(DEP_CPP_CONTP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CONTPRE.SBR" : $(SOURCE) $(DEP_CPP_CONTP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cont32d.pch" : $(SOURCE) $(DEP_CPP_CONTP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CONTASRT.CPP

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_CONTAS=\
	".\ASSERTDLG.H"\
	".\contpre.hxx"\
	".\DUMPBUFFER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\CONTASRT.OBJ" : $(SOURCE) $(DEP_CPP_CONTAS) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_CONTAS=\
	".\ASSERTDLG.H"\
	".\contpre.hxx"\
	".\DUMPBUFFER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\CONTASRT.OBJ" : $(SOURCE) $(DEP_CPP_CONTAS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"

"$(INTDIR)\CONTASRT.SBR" : $(SOURCE) $(DEP_CPP_CONTAS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRANSEX.CPP

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_TRANS=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\TRANSEX.OBJ" : $(SOURCE) $(DEP_CPP_TRANS) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_TRANS=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TransEx.h"\
	

"$(INTDIR)\TRANSEX.OBJ" : $(SOURCE) $(DEP_CPP_TRANS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"

"$(INTDIR)\TRANSEX.SBR" : $(SOURCE) $(DEP_CPP_TRANS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VerbAssert.cpp
DEP_CPP_VERBA=\
	".\ASSERTDLG.H"\
	".\DUMPBUFFER.H"\
	".\PE_Debug.h"\
	
NODEP_CPP_VERBA=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\VerbAssert.obj" : $(SOURCE) $(DEP_CPP_VERBA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\VerbAssert.sbr" : $(SOURCE) $(DEP_CPP_VERBA) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DumpBuffer.cpp
DEP_CPP_DUMPB=\
	".\DUMPBUFFER.H"\
	
NODEP_CPP_DUMPB=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DumpBuffer.obj" : $(SOURCE) $(DEP_CPP_DUMPB) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\DumpBuffer.sbr" : $(SOURCE) $(DEP_CPP_DUMPB) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PE_Debug.cpp
DEP_CPP_PE_DE=\
	".\DUMPBUFFER.H"\
	".\PE_Debug.h"\
	
NODEP_CPP_PE_DE=\
	".\bscapi.h"\
	".\hungary.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\PE_Debug.obj" : $(SOURCE) $(DEP_CPP_PE_DE) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\PE_Debug.sbr" : $(SOURCE) $(DEP_CPP_PE_DE) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AssertDlg.cpp
DEP_CPP_ASSER=\
	".\ASSERTDLG.H"\
	".\DUMPBUFFER.H"\
	
NODEP_CPP_ASSER=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__CTRDLL__" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/cont32d.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/containd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\AssertDlg.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

"$(INTDIR)\AssertDlg.sbr" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Registry.cxx

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_REGIS=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\REGISTRY.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\Registry.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_REGIS=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\REGISTRY.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\Registry.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"

"$(INTDIR)\Registry.sbr" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\copttree.cxx

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_COPTT=\
	".\contpre.hxx"\
	".\p5ticker.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\copttree.obj" : $(SOURCE) $(DEP_CPP_COPTT) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_COPTT=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\P5TICKER.H"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\copttree.obj" : $(SOURCE) $(DEP_CPP_COPTT) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"

"$(INTDIR)\copttree.sbr" : $(SOURCE) $(DEP_CPP_COPTT) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P5TICKER.CPP

!IF  "$(CFG)" == "cont32 - Win32 Container Release"

DEP_CPP_P5TIC=\
	".\contpre.hxx"\
	".\p5ticker.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\P5TICKER.OBJ" : $(SOURCE) $(DEP_CPP_P5TIC) "$(INTDIR)"\
 "$(INTDIR)\cont4.pch"


!ELSEIF  "$(CFG)" == "cont32 - Win32 Container Debug"

DEP_CPP_P5TIC=\
	".\contpre.hxx"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\P5TICKER.H"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Syncthrdcs.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	

"$(INTDIR)\P5TICKER.OBJ" : $(SOURCE) $(DEP_CPP_P5TIC) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"

"$(INTDIR)\P5TICKER.SBR" : $(SOURCE) $(DEP_CPP_P5TIC) "$(INTDIR)"\
 "$(INTDIR)\cont32d.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
