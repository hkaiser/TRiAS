# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=TRATIR - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TRATIR - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TRATIR - Win32 Release" && "$(CFG)" != "TRATIR - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRATIR.MAK" CFG="TRATIR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRATIR - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TRATIR - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "TRATIR - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRATIR - Win32 Release"

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

ALL : "$(OUTDIR)\TRATIR.exe"

CLEAN : 
	-@erase "$(INTDIR)\ALTPRSLP.OBJ"
	-@erase "$(INTDIR)\ALTPRSYP.OBJ"
	-@erase "$(INTDIR)\GINHED.OBJ"
	-@erase "$(INTDIR)\IGLAGED.OBJ"
	-@erase "$(INTDIR)\IGPPTED.OBJ"
	-@erase "$(INTDIR)\IGUMOED.OBJ"
	-@erase "$(INTDIR)\MTREE.OBJ"
	-@erase "$(INTDIR)\TRAT_ASC.OBJ"
	-@erase "$(INTDIR)\TRAT_ASM.OBJ"
	-@erase "$(INTDIR)\TRATASP.OBJ"
	-@erase "$(INTDIR)\TRATIR.pch"
	-@erase "$(INTDIR)\Tratir.res"
	-@erase "$(OUTDIR)\TRATIR.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TRATIR.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Yu"tratasp.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/TRATIR.pch" /Yu"tratasp.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Tratir.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRATIR.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/TRATIR.pdb" /machine:I386 /out:"$(OUTDIR)/TRATIR.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ALTPRSLP.OBJ" \
	"$(INTDIR)\ALTPRSYP.OBJ" \
	"$(INTDIR)\GINHED.OBJ" \
	"$(INTDIR)\IGLAGED.OBJ" \
	"$(INTDIR)\IGPPTED.OBJ" \
	"$(INTDIR)\IGUMOED.OBJ" \
	"$(INTDIR)\MTREE.OBJ" \
	"$(INTDIR)\TRAT_ASC.OBJ" \
	"$(INTDIR)\TRAT_ASM.OBJ" \
	"$(INTDIR)\TRATASP.OBJ" \
	"$(INTDIR)\Tratir.res"

"$(OUTDIR)\TRATIR.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TRATIR - Win32 Debug"

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

ALL : "$(OUTDIR)\tratir32.exe"

CLEAN : 
	-@erase "$(INTDIR)\ALTPRSLP.OBJ"
	-@erase "$(INTDIR)\ALTPRSYP.OBJ"
	-@erase "$(INTDIR)\GINHED.OBJ"
	-@erase "$(INTDIR)\IGLAGED.OBJ"
	-@erase "$(INTDIR)\IGPPTED.OBJ"
	-@erase "$(INTDIR)\IGUMOED.OBJ"
	-@erase "$(INTDIR)\MTREE.OBJ"
	-@erase "$(INTDIR)\TRAT_ASC.OBJ"
	-@erase "$(INTDIR)\TRAT_ASM.OBJ"
	-@erase "$(INTDIR)\TRATASP.OBJ"
	-@erase "$(INTDIR)\TRATIR.pch"
	-@erase "$(INTDIR)\Tratir.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\tratir32.exe"
	-@erase "$(OUTDIR)\tratir32.ilk"
	-@erase "$(OUTDIR)\tratir32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TRATIR.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Yu"tratasp.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/TRATIR.pch" /Yu"tratasp.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Tratir.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TRATIR.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"WinDebug/tratir32.exe"
LINK32_FLAGS=cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/tratir32.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/tratir32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ALTPRSLP.OBJ" \
	"$(INTDIR)\ALTPRSYP.OBJ" \
	"$(INTDIR)\GINHED.OBJ" \
	"$(INTDIR)\IGLAGED.OBJ" \
	"$(INTDIR)\IGPPTED.OBJ" \
	"$(INTDIR)\IGUMOED.OBJ" \
	"$(INTDIR)\MTREE.OBJ" \
	"$(INTDIR)\TRAT_ASC.OBJ" \
	"$(INTDIR)\TRAT_ASM.OBJ" \
	"$(INTDIR)\TRATASP.OBJ" \
	"$(INTDIR)\Tratir.res"

"$(OUTDIR)\tratir32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "TRATIR - Win32 Release"
# Name "TRATIR - Win32 Debug"

!IF  "$(CFG)" == "TRATIR - Win32 Release"

!ELSEIF  "$(CFG)" == "TRATIR - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ALTPRSLP.CPP
DEP_CPP_ALTPR=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\ATLPARSL.C"\
	".\TRATASP.H"\
	".\YTAB.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\ALTPRSLP.OBJ" : $(SOURCE) $(DEP_CPP_ALTPR) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ALTPRSYP.CPP
DEP_CPP_ALTPRS=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\ATLPARSY.C"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\ALTPRSYP.OBJ" : $(SOURCE) $(DEP_CPP_ALTPRS) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGUMOED.CPP
DEP_CPP_IGUMO=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\IGUMOED.OBJ" : $(SOURCE) $(DEP_CPP_IGUMO) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRAT_ASM.CPP
DEP_CPP_TRAT_=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\DBVERSIO.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\TRAT_ASM.OBJ" : $(SOURCE) $(DEP_CPP_TRAT_) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRAT_ASC.CPP
DEP_CPP_TRAT_A=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\TRAT_ASC.OBJ" : $(SOURCE) $(DEP_CPP_TRAT_A) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGLAGED.CPP
DEP_CPP_IGLAG=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\IGLAGED.OBJ" : $(SOURCE) $(DEP_CPP_IGLAG) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GINHED.CPP
DEP_CPP_GINHE=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\GINHED.OBJ" : $(SOURCE) $(DEP_CPP_GINHE) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGPPTED.CPP
DEP_CPP_IGPPT=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\IGPPTED.OBJ" : $(SOURCE) $(DEP_CPP_IGPPT) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRATASP.CPP
DEP_CPP_TRATA=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

!IF  "$(CFG)" == "TRATIR - Win32 Release"

# ADD CPP /Yc"tratasp.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/TRATIR.pch" /Yc"tratasp.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TRATASP.OBJ" : $(SOURCE) $(DEP_CPP_TRATA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TRATIR.pch" : $(SOURCE) $(DEP_CPP_TRATA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TRATIR - Win32 Debug"

# ADD CPP /Yc"tratasp.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/TRATIR.pch" /Yc"tratasp.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TRATASP.OBJ" : $(SOURCE) $(DEP_CPP_TRATA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TRATIR.pch" : $(SOURCE) $(DEP_CPP_TRATA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MTREE.CPP
DEP_CPP_MTREE=\
	"..\..\TRIASDEV.MVC\INCLUDE\DBCONFIG.H"\
	".\ATLERRS.H"\
	".\ATLPARS.H"\
	".\MTREE.HXX"\
	".\TRATASP.H"\
	{$(INCLUDE)}"\DBTYPES.H"\
	

"$(INTDIR)\MTREE.OBJ" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\TRATIR.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tratir.rc
DEP_RSC_TRATI=\
	".\icon1.ico"\
	

"$(INTDIR)\Tratir.res" : $(SOURCE) $(DEP_RSC_TRATI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
