# Microsoft Visual C++ generated build script - Do not modify

PROJ = TRIASED
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = -eSyntaxfehler
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\TRIASDEV\TRIASED\WIN16\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = /YcPHEADER.H
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = /YuPHEADER.H
CPPUSEPCHFLAG = 
FIRSTC = PHEADER.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /Zp1 /W3 /Zi /AM /Od /Ob1 /D "_DEBUG" /GA /Fd"TRIASED.PDB" 
CFLAGS_R_WEXE = /nologo /G2 /Zp1 /W3 /AM /Ox /Ob1 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mlibcew ctl3dv2 commdlg.lib 
LIBS_R_WEXE = oldnames libw mlibcew ctl3dv2 commdlg.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = TRIASED.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = PHEADER.SBR \
		TRIASED1.SBR \
		TRIASED2.SBR \
		TRIASED.SBR


TRIASED_RCDEP = d:\triasdev\triased\win16\triased.ico \
	d:\triasdev\triased\win16\defabout.dlg


PHEADER_DEP = d:\triasdev\triased\win16\pheader.h \
	d:\triasdev\triased\win16\triased.h


TRIASED1_DEP = d:\triasdev\triased\win16\pheader.h \
	d:\triasdev\triased\win16\triased.h


TRIASED2_DEP = d:\triasdev\triased\win16\pheader.h \
	d:\triasdev\triased\win16\triased.h


TRIASED_DEP = d:\triasdev\triased\win16\pheader.h \
	d:\triasdev\triased\win16\triased.h


all:	$(PROJ).EXE

TRIASED.RES:	TRIASED.RC $(TRIASED_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r TRIASED.RC

PHEADER.OBJ:	PHEADER.C $(PHEADER_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c PHEADER.C

TRIASED1.OBJ:	TRIASED1.C $(TRIASED1_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c TRIASED1.C

TRIASED2.OBJ:	TRIASED2.C $(TRIASED2_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c TRIASED2.C

TRIASED.OBJ:	TRIASED.C $(TRIASED_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c TRIASED.C


$(PROJ).EXE::	TRIASED.RES

$(PROJ).EXE::	PHEADER.OBJ TRIASED1.OBJ TRIASED2.OBJ TRIASED.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
PHEADER.OBJ +
TRIASED1.OBJ +
TRIASED2.OBJ +
TRIASED.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
F:\C8\MFC\LIB\+
F:\C8\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) TRIASED.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	TRIASED.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) TRIASED.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
