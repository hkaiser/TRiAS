# Microsoft Visual C++ generated build script - Do not modify

PROJ = FEATURE
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\TRIASDEV.MVC\XTENSION\FEATURE\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcFEATUREP.HXX
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuFEATUREP.HXX
FIRSTC =             
FIRSTCPP = FEATUREP.CXX
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /WX /Zi /ALw /Od /Ob1 /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /GD /Fd"FEATURE.PDB" 
CFLAGS_R_WDLL = /nologo /G3 /Gy /W3 /WX /Gf /ALw /O2 /Ox /Ob1 /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WDLL = ixtnsn16 framelib containr lstrdwd ole2 typelib oldnames libw ldllcew mmsystem.lib shell.lib 
LIBS_R_WDLL = ixtnsn16 framelib ole2 typelib lstrdw oldnames libw ldllcew shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = FEATURE.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = FEATUREP.SBR \
		FEATMENU.SBR \
		SELIDLST.SBR \
		SELIDENT.SBR \
		UIDOBJ.SBR \
		FEATUREX.SBR


FEATUREP_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx


FEATURE_RCDEP = c:\triasdev.mvc\xtension\feature\feature.rcv


FEATMENU_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx \
	c:\triasdev.mvc\xtension\feature\selidlst.hxx \
	c:\triasdev.mvc\xtension\feature\selident.hxx \
	c:\triasdev.mvc\xtension\feature\uidobj.hxx \
	c:\triasdev.mvc\xtension\feature\uidobj.inl


SELIDLST_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx \
	c:\triasdev.mvc\xtension\feature\selidlst.hxx


SELIDENT_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx \
	c:\triasdev.mvc\xtension\feature\selidlst.hxx \
	c:\triasdev.mvc\xtension\feature\selident.hxx


UIDOBJ_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx \
	c:\triasdev.mvc\xtension\feature\uidobj.hxx \
	c:\triasdev.mvc\xtension\feature\uidobj.inl


FEATUREX_DEP = c:\triasdev.mvc\xtension\feature\featurep.hxx \
	c:\msvc\include\string \
	c:\msvc\include\tchar.h \
	c:\cv.mvc\include\commonvu.hxx \
	c:\cv.mvc\include\cxxtypes.hxx \
	c:\cv.mvc\include\cv_types.hxx \
	c:\cv.mvc\include\cv_defs.h \
	c:\cv.mvc\include\cvinline.hxx \
	c:\cv.mvc\include\containr.hxx \
	c:\cv.mvc\include\ctrtypes.hxx \
	c:\cv.mvc\include\freestor.hxx \
	c:\cv.mvc\include\syncthrd.hxx \
	c:\cv.mvc\include\ctrlines.hxx \
	c:\triasdev.mvc\include\errcodes.hxx \
	c:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\triasdev.mvc\include\xtensnm.hxx \
	c:\msvc\include\poppack.h \
	c:\triasdev.mvc\include\xtensnx.h \
	c:\triasdev.mvc\include\strdupx.hxx \
	c:\triasdev.mvc\include\protos.h \
	c:\triasdev.mvc\include\trias01m.hxx \
	c:\triasdev.mvc\include\eieruhr.hxx \
	c:\triasdev.mvc\include\ixtensn.hxx \
	c:\triasdev.mvc\include\xtencunk.hxx \
	c:\triasdev.mvc\include\xtsnguid.h \
	c:\triasdev.mvc\include\xtsnaux.hxx \
	c:\triasdev.mvc\xtension\feature\feature.hxx \
	c:\triasdev.mvc\xtension\feature\featguid.h \
	c:\triasdev.mvc\xtension\feature\version.h


all:	$(PROJ).DLL

FEATUREP.OBJ:	FEATUREP.CXX $(FEATUREP_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c FEATUREP.CXX

FEATURE.RES:	FEATURE.RC $(FEATURE_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r FEATURE.RC

FEATMENU.OBJ:	FEATMENU.CXX $(FEATMENU_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FEATMENU.CXX

SELIDLST.OBJ:	SELIDLST.CXX $(SELIDLST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SELIDLST.CXX

SELIDENT.OBJ:	SELIDENT.CXX $(SELIDENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SELIDENT.CXX

UIDOBJ.OBJ:	UIDOBJ.CXX $(UIDOBJ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UIDOBJ.CXX

FEATUREX.OBJ:	FEATUREX.CXX $(FEATUREX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FEATUREX.CXX


$(PROJ).DLL::	FEATURE.RES

$(PROJ).DLL::	FEATUREP.OBJ FEATMENU.OBJ SELIDLST.OBJ SELIDENT.OBJ UIDOBJ.OBJ FEATUREX.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
FEATUREP.OBJ +
FEATMENU.OBJ +
SELIDLST.OBJ +
SELIDENT.OBJ +
UIDOBJ.OBJ +
FEATUREX.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
c:\cv.mvc\lib16\+
c:\triasdev.mvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) FEATURE.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	FEATURE.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) FEATURE.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
