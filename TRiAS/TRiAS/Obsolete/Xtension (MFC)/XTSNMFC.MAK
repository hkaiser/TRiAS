# Microsoft Visual C++ generated build script - Do not modify

PROJ = XTSNMFC
DEBUG = 0
PROGTYPE = 4
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\TRIASDEV\XTSNMFC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = OPROPEXT.CPP
RC = rc
CFLAGS_D_LIB = /nologo /G2 /Zp1 /W3 /Z7 /ALw /YX /Od /D "_DEBUG" /D "_AFXDLL" /D "__XT" /GD /Fp"XTSNMFC.PCH"
CFLAGS_R_LIB = /nologo /Gs /G2 /Zp1 /W3 /ALw /YX /Ox /D "NDEBUG" /D "__XT" /D "_USRDLL" /GD /Fp"XTSNMFC.PCH"
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_LIB)
LFLAGS = 
LIBS = 
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_LIB)
LFLAGS = 
LIBS = 
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = OPROPEXT.SBR \
		XTSNMFC.SBR


OPROPEXT_DEP = c:\triasdev\inc\xtension.h \
	c:\triasdev\inc\xtensnx.h \
	c:\triasdev\inc\xtensnxx.h \
	c:\triasdev\inc\protos.h \
	c:\triasdev\inc\resstrg.h \
	c:\triasdev\inc.hpp\xtsnmfc.hpp \
	c:\triasdev\inc\errcodes.hxx \
	c:\triasdev\inc.hpp\opropext.hpp


XTSNMFC_DEP = c:\triasdev\inc\xtension.h \
	c:\triasdev\inc\xtensnx.h \
	c:\triasdev\inc\protos.h \
	c:\triasdev\inc\resstrg.h \
	c:\triasdev\inc.hpp\xtsnmfc.hpp \
	c:\triasdev\inc\errcodes.hxx


all:	$(PROJ).LIB

OPROPEXT.OBJ:	OPROPEXT.CPP $(OPROPEXT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c OPROPEXT.CPP

XTSNMFC.OBJ:	XTSNMFC.CPP $(XTSNMFC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c XTSNMFC.CPP

$(PROJ).LIB::	OPROPEXT.OBJ XTSNMFC.OBJ $(OBJS_EXT)
	echo >NUL @<<$(PROJ).CRF
$@ /PAGESIZE:64
y
+OPROPEXT.OBJ &
+XTSNMFC.OBJ &
;
<<
	if exist $@ del $@
	lib @$(PROJ).CRF

$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
