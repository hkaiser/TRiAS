# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Oltxtext - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Oltxtext - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Oltxtext - Win32 Release" && "$(CFG)" !=\
 "Oltxtext - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Oltext4.mak" CFG="Oltxtext - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Oltxtext - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oltxtext - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Oltxtext - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
TargetName=Gentext
# End Custom Macros

ALL : "$(OUTDIR)\Gentext.ext" "c:\trias.mvc\trias200.rel\Gentext.ext"

CLEAN : 
	-@erase "$(INTDIR)\DEL.OBJ"
	-@erase "$(INTDIR)\DLGABH.OBJ"
	-@erase "$(INTDIR)\ENBXVOLL.OBJ"
	-@erase "$(INTDIR)\ENOBAB1.OBJ"
	-@erase "$(INTDIR)\ENOBMEN.OBJ"
	-@erase "$(INTDIR)\ENREL.OBJ"
	-@erase "$(INTDIR)\ENUMOBJ.OBJ"
	-@erase "$(INTDIR)\HELPER.OBJ"
	-@erase "$(INTDIR)\ITERATOR.OBJ"
	-@erase "$(INTDIR)\Oltext4.pch"
	-@erase "$(INTDIR)\OLTXTEXT.res"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\TEXTDLG1.OBJ"
	-@erase "$(INTDIR)\TEXTEX1.OBJ"
	-@erase "$(INTDIR)\TEXTP.OBJ"
	-@erase "$(INTDIR)\TXTRDLG1.OBJ"
	-@erase "$(OUTDIR)\Gentext.exp"
	-@erase "$(OUTDIR)\Gentext.ext"
	-@erase "$(OUTDIR)\Gentext.lib"
	-@erase "c:\trias.mvc\trias200.rel\Gentext.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32" /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32" /D\
 "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "_WINDOWS" /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Oltext4.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/OLTXTEXT.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Oltext4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmfr40.lib stdcppr.lib cont32r.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/Gentext.ext"
LINK32_FLAGS=ixtmfr40.lib stdcppr.lib cont32r.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/Gentext.pdb" /machine:I386\
 /def:".\OLTXTEXT.DEF" /out:"$(OUTDIR)/Gentext.ext"\
 /implib:"$(OUTDIR)/Gentext.lib" 
DEF_FILE= \
	".\OLTXTEXT.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DEL.OBJ" \
	"$(INTDIR)\DLGABH.OBJ" \
	"$(INTDIR)\ENBXVOLL.OBJ" \
	"$(INTDIR)\ENOBAB1.OBJ" \
	"$(INTDIR)\ENOBMEN.OBJ" \
	"$(INTDIR)\ENREL.OBJ" \
	"$(INTDIR)\ENUMOBJ.OBJ" \
	"$(INTDIR)\HELPER.OBJ" \
	"$(INTDIR)\ITERATOR.OBJ" \
	"$(INTDIR)\OLTXTEXT.res" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\TEXTDLG1.OBJ" \
	"$(INTDIR)\TEXTEX1.OBJ" \
	"$(INTDIR)\TEXTP.OBJ" \
	"$(INTDIR)\TXTRDLG1.OBJ"

"$(OUTDIR)\Gentext.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\Gentext.ext
TargetName=Gentext
InputPath=.\WinRel\Gentext.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=Gentextd
# End Custom Macros

ALL : ".\windebug\Gentextd.ext" "$(OUTDIR)\Oltext4.bsc"\
 "c:\trias.mvc\trias200\Gentextd.ext"

CLEAN : 
	-@erase "$(INTDIR)\DEL.OBJ"
	-@erase "$(INTDIR)\DEL.SBR"
	-@erase "$(INTDIR)\DLGABH.OBJ"
	-@erase "$(INTDIR)\DLGABH.SBR"
	-@erase "$(INTDIR)\ENBXVOLL.OBJ"
	-@erase "$(INTDIR)\ENBXVOLL.SBR"
	-@erase "$(INTDIR)\ENOBAB1.OBJ"
	-@erase "$(INTDIR)\ENOBAB1.SBR"
	-@erase "$(INTDIR)\ENOBMEN.OBJ"
	-@erase "$(INTDIR)\ENOBMEN.SBR"
	-@erase "$(INTDIR)\ENREL.OBJ"
	-@erase "$(INTDIR)\ENREL.SBR"
	-@erase "$(INTDIR)\ENUMOBJ.OBJ"
	-@erase "$(INTDIR)\ENUMOBJ.SBR"
	-@erase "$(INTDIR)\HELPER.OBJ"
	-@erase "$(INTDIR)\HELPER.SBR"
	-@erase "$(INTDIR)\ITERATOR.OBJ"
	-@erase "$(INTDIR)\ITERATOR.SBR"
	-@erase "$(INTDIR)\Oltext4.pch"
	-@erase "$(INTDIR)\OLTXTEXT.res"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\TEXTDLG1.OBJ"
	-@erase "$(INTDIR)\TEXTDLG1.SBR"
	-@erase "$(INTDIR)\TEXTEX1.OBJ"
	-@erase "$(INTDIR)\TEXTEX1.SBR"
	-@erase "$(INTDIR)\TEXTP.OBJ"
	-@erase "$(INTDIR)\TEXTP.SBR"
	-@erase "$(INTDIR)\TXTRDLG1.OBJ"
	-@erase "$(INTDIR)\TXTRDLG1.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Gentextd.exp"
	-@erase "$(OUTDIR)\Gentextd.lib"
	-@erase "$(OUTDIR)\Gentextd.pdb"
	-@erase "$(OUTDIR)\Oltext4.bsc"
	-@erase ".\windebug\Gentextd.ext"
	-@erase ".\windebug\Gentextd.ilk"
	-@erase "c:\trias.mvc\trias200\Gentextd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Oltext4.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/OLTXTEXT.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Oltext4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DEL.SBR" \
	"$(INTDIR)\DLGABH.SBR" \
	"$(INTDIR)\ENBXVOLL.SBR" \
	"$(INTDIR)\ENOBAB1.SBR" \
	"$(INTDIR)\ENOBMEN.SBR" \
	"$(INTDIR)\ENREL.SBR" \
	"$(INTDIR)\ENUMOBJ.SBR" \
	"$(INTDIR)\HELPER.SBR" \
	"$(INTDIR)\ITERATOR.SBR" \
	"$(INTDIR)\STDAFX.SBR" \
	"$(INTDIR)\TEXTDLG1.SBR" \
	"$(INTDIR)\TEXTEX1.SBR" \
	"$(INTDIR)\TEXTP.SBR" \
	"$(INTDIR)\TXTRDLG1.SBR"

"$(OUTDIR)\Oltext4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmfd40.lib stdcppd.lib cont32d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"windebug\Gentextd.ext"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtmfd40.lib stdcppd.lib cont32d.lib /nologo /subsystem:windows\
 /dll /incremental:yes /pdb:"$(OUTDIR)/Gentextd.pdb" /debug /machine:I386\
 /def:".\OLTXTEXT.DEF" /out:"windebug\Gentextd.ext"\
 /implib:"$(OUTDIR)/Gentextd.lib" 
DEF_FILE= \
	".\OLTXTEXT.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DEL.OBJ" \
	"$(INTDIR)\DLGABH.OBJ" \
	"$(INTDIR)\ENBXVOLL.OBJ" \
	"$(INTDIR)\ENOBAB1.OBJ" \
	"$(INTDIR)\ENOBMEN.OBJ" \
	"$(INTDIR)\ENREL.OBJ" \
	"$(INTDIR)\ENUMOBJ.OBJ" \
	"$(INTDIR)\HELPER.OBJ" \
	"$(INTDIR)\ITERATOR.OBJ" \
	"$(INTDIR)\OLTXTEXT.res" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\TEXTDLG1.OBJ" \
	"$(INTDIR)\TEXTEX1.OBJ" \
	"$(INTDIR)\TEXTP.OBJ" \
	"$(INTDIR)\TXTRDLG1.OBJ"

".\windebug\Gentextd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\windebug\Gentextd.ext
TargetName=Gentextd
InputPath=.\windebug\Gentextd.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200

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

# Name "Oltxtext - Win32 Release"
# Name "Oltxtext - Win32 Debug"

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENOBAB1.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ENOBA=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ENOBAB1.OBJ" : $(SOURCE) $(DEP_CPP_ENOBA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ENOBA=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ENOBAB1.OBJ" : $(SOURCE) $(DEP_CPP_ENOBA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ENOBAB1.SBR" : $(SOURCE) $(DEP_CPP_ENOBA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTEX1.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_TEXTE=\
	".\..\DLGABH.H"\
	".\..\HELPER.H"\
	".\..\IGENTEXT.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\textdlg.h"\
	".\..\TEXTEX1.HPP"\
	".\..\TEXTGUID.H"\
	".\..\TEXTP.H"\
	".\..\txtredlg.h"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

"$(INTDIR)\TEXTEX1.OBJ" : $(SOURCE) $(DEP_CPP_TEXTE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_TEXTE=\
	".\..\DLGABH.H"\
	".\..\HELPER.H"\
	".\..\IGENTEXT.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\textdlg.h"\
	".\..\TEXTGUID.H"\
	".\..\TEXTP.H"\
	".\..\txtredlg.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TEXTEX1.OBJ" : $(SOURCE) $(DEP_CPP_TEXTE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\TEXTEX1.SBR" : $(SOURCE) $(DEP_CPP_TEXTE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\STDAFX.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_STDAF=\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "c:\TRIASDEV\oltxtext" /D "WIN32" /D\
 "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "_WINDOWS" /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Oltext4.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Oltext4.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_STDAF=\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/Oltext4.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Oltext4.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENBXVOLL.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ENBXV=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ENBXVOLL.OBJ" : $(SOURCE) $(DEP_CPP_ENBXV) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ENBXV=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ENBXVOLL.OBJ" : $(SOURCE) $(DEP_CPP_ENBXV) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ENBXVOLL.SBR" : $(SOURCE) $(DEP_CPP_ENBXV) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTDLG1.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_TEXTD=\
	".\..\HELPER.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\textdlg.h"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\..\waitcur.hpp"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\TEXTDLG1.OBJ" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_TEXTD=\
	".\..\HELPER.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\textdlg.h"\
	".\..\TEXTEX1.HPP"\
	".\..\waitcur.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TEXTDLG1.OBJ" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\TEXTDLG1.SBR" : $(SOURCE) $(DEP_CPP_TEXTD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENUMOBJ.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ENUMO=\
	".\..\DEL.HPP"\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ENUMOBJ.OBJ" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ENUMO=\
	".\..\DEL.HPP"\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ENUMOBJ.OBJ" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ENUMOBJ.SBR" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\HELPER.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_HELPE=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\..\waitcur.hpp"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\HELPER.OBJ" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_HELPE=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\waitcur.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\HELPER.OBJ" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\HELPER.SBR" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\DEL.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_DEL_C=\
	".\..\DEL.HPP"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\DEL.OBJ" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_DEL_C=\
	".\..\DEL.HPP"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DEL.OBJ" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\DEL.SBR" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENOBMEN.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ENOBM=\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ENOBMEN.OBJ" : $(SOURCE) $(DEP_CPP_ENOBM) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ENOBM=\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ENOBMEN.OBJ" : $(SOURCE) $(DEP_CPP_ENOBM) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ENOBMEN.SBR" : $(SOURCE) $(DEP_CPP_ENOBM) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\DLGABH.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_DLGAB=\
	".\..\DLGABH.H"\
	".\..\HELPER.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\..\waitcur.hpp"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\DLGABH.OBJ" : $(SOURCE) $(DEP_CPP_DLGAB) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_DLGAB=\
	".\..\DLGABH.H"\
	".\..\HELPER.H"\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\waitcur.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DLGABH.OBJ" : $(SOURCE) $(DEP_CPP_DLGAB) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\DLGABH.SBR" : $(SOURCE) $(DEP_CPP_DLGAB) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ENREL.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ENREL=\
	".\..\DEL.HPP"\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ENREL.OBJ" : $(SOURCE) $(DEP_CPP_ENREL) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ENREL=\
	".\..\DEL.HPP"\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ENREL.OBJ" : $(SOURCE) $(DEP_CPP_ENREL) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ENREL.SBR" : $(SOURCE) $(DEP_CPP_ENREL) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TEXTP.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_TEXTP=\
	".\..\HELPER.H"\
	".\..\IGENTEXT.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\TEXTP.H"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\TEXTP.OBJ" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_TEXTP=\
	".\..\HELPER.H"\
	".\..\IGENTEXT.H"\
	".\..\STDAFX.H"\
	".\..\TEXTP.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TEXTP.OBJ" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\TEXTP.SBR" : $(SOURCE) $(DEP_CPP_TEXTP) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\ITERATOR.CPP

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

DEP_CPP_ITERA=\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\ITERATOR.OBJ" : $(SOURCE) $(DEP_CPP_ITERA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

DEP_CPP_ITERA=\
	".\..\ITERATOR.HPP"\
	".\..\STDAFX.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ITERATOR.OBJ" : $(SOURCE) $(DEP_CPP_ITERA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\ITERATOR.SBR" : $(SOURCE) $(DEP_CPP_ITERA) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\OLTXTEXT\TXTRDLG1.CPP
DEP_CPP_TXTRD=\
	".\..\HELPER.H"\
	".\..\STDAFX.H"\
	".\..\TEXTEX1.HPP"\
	".\..\txtredlg.h"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\..\waitcur.hpp"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

!IF  "$(CFG)" == "Oltxtext - Win32 Release"


"$(INTDIR)\TXTRDLG1.OBJ" : $(SOURCE) $(DEP_CPP_TXTRD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TXTRDLG1.OBJ" : $(SOURCE) $(DEP_CPP_TXTRD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

"$(INTDIR)\TXTRDLG1.SBR" : $(SOURCE) $(DEP_CPP_TXTRD) "$(INTDIR)"\
 "$(INTDIR)\Oltext4.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OLTXTEXT.RC
DEP_RSC_OLTXT=\
	".\OLTXTEXT.RCV"\
	

"$(INTDIR)\OLTXTEXT.res" : $(SOURCE) $(DEP_RSC_OLTXT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OLTXTEXT.DEF

!IF  "$(CFG)" == "Oltxtext - Win32 Release"

!ELSEIF  "$(CFG)" == "Oltxtext - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
