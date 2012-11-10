# Microsoft Visual C++ generated build script - Do not modify

PROJ = ERSETZ
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\TRIASDEV.MVC\TRIAS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = ERSETZ.CXX  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /Od /D "_DEBUG" /GA /Fd"ERSETZ.PDB"
CFLAGS_R_WEXE = /nologo /G3 /W3 /O1 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /ALIGN:16 /STACK:10240
LFLAGS_R_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /ALIGN:16 /STACK:10240
LIBS_D_WEXE = oldnames libw commdlg shell olecli olesvr slibcew
LIBS_R_WEXE = oldnames libw commdlg shell olecli olesvr slibcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = ERSETZ.DEF
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
SBRS = ERSETZ.SBR


ERSETZ_DEP = 

ERSETZ_RCDEP = c:\triasdev.mvc\trias\ersetz.ico


all:	$(PROJ).EXE

ERSETZ.OBJ:	ERSETZ.CXX $(ERSETZ_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ERSETZ.CXX

ERSETZ.RES:	ERSETZ.RC $(ERSETZ_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ERSETZ.RC


$(PROJ).EXE::	ERSETZ.RES

$(PROJ).EXE::	ERSETZ.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ERSETZ.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
c:\cv.mvc\lib\+
c:\triasdev.mvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) ERSETZ.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	ERSETZ.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ERSETZ.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
