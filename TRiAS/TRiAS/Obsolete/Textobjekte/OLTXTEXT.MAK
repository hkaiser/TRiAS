# Microsoft Visual C++ generated build script - Do not modify

PROJ = OLTXTEXT
DEBUG = 1
PROGTYPE = 1
CALLER = c:\trias\trias130\trias.exe /regserver
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG,_PORTABLE 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\TRIASDEV.MVC\XTENSION\OLTXTEXT\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /WX /Zi /ALw /Od /Ob1 /D "_DEBUG" /D "__XT" /D "_USRDLL" /D "_WINDLL" /D "__DEXPROCS" /D "__XTNSNDLL__" /GD /Fd"TEXTEX.PDB" 
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /D "_AFXDLL" /D "_AFXCTL" /D "_MBCS" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = ixtmfd16 lstrdwd lafxdwd ole2.lib storage.lib typelib ole2disp oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = ixtmfr16 lstrdw lafxdw ole2.lib storage.lib typelib oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = OLTXTEXT.DEF
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
SBRS = STDAFX.SBR \
		ITERATOR.SBR \
		DEL.SBR \
		ENREL.SBR \
		ENOBMEN.SBR \
		DLGABH.SBR \
		ENBXVOLL.SBR \
		ENUMOBJ.SBR \
		TEXTDLG1.SBR \
		TEXTEX1.SBR \
		TXTRDLG1.SBR \
		ENOBAB1.SBR \
		HELPER.SBR \
		TEXTP.SBR


STDAFX_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp


ITERATOR_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\iterator.hpp


DEL_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\del.hpp


ENREL_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\del.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


ENOBMEN_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp


DLGABH_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h \
	e:\triasdev.mvc\xtension\oltxtext\dlgabh.h \
	e:\triasdev.mvc\xtension\oltxtext\iterator.hpp


ENBXVOLL_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


ENUMOBJ_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\del.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


TEXTDLG1_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h \
	e:\triasdev.mvc\xtension\oltxtext\textdlg.h \
	e:\triasdev.mvc\xtension\oltxtext\iterator.hpp


TEXTEX1_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\include\xtsnguid.h \
	e:\triasdev.mvc\include\eonrguid.h \
	c:\msvc\include\olectlid.h \
	e:\triasdev.mvc\xtension\oltxtext\textguid.h \
	e:\triasdev.mvc\xtension\oltxtext\textdlg.h \
	e:\triasdev.mvc\xtension\oltxtext\iterator.hpp \
	e:\triasdev.mvc\xtension\oltxtext\txtredlg.h \
	e:\triasdev.mvc\xtension\oltxtext\dlgabh.h \
	e:\triasdev.mvc\xtension\oltxtext\igentext.h \
	e:\triasdev.mvc\xtension\oltxtext\helper.h \
	e:\triasdev.mvc\xtension\oltxtext\textp.h


TXTRDLG1_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\txtredlg.h \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


ENOBAB1_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


OLTXTEXT_RCDEP = e:\triasdev.mvc\xtension\oltxtext\oltxtext.rcv


HELPER_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h


TEXTP_DEP = e:\triasdev.mvc\xtension\oltxtext\stdafx.h \
	c:\msvc\include\string \
	e:\triasdev.mvc\include\dirisole.h \
	e:\triasdev.mvc\include\xtensnm.hxx \
	e:\triasdev.mvc\include\xtension.h \
	c:\msvc\include\pshpack1.h \
	c:\msvc\include\poppack.h \
	e:\triasdev.mvc\include\xtensnx.h \
	e:\triasdev.mvc\include\errcodes.hxx \
	e:\triasdev.mvc\include\ixtensn.hxx \
	e:\triasdev.mvc\include\ienumobj.hxx \
	e:\triasdev.mvc\include\istatus.h \
	e:\triasdev.mvc\include\xtencunk.hxx \
	e:\triasdev.mvc\include\xtsnaux.hxx \
	e:\triasdev.mvc\xtension\oltxtext\waitcur.hpp \
	e:\triasdev.mvc\xtension\oltxtext\version.h \
	e:\triasdev.mvc\xtension\oltxtext\win32/versio32.h \
	e:\triasdev.mvc\xtension\oltxtext\versio16.h \
	e:\triasdev.mvc\xtension\oltxtext\textex1.hpp \
	e:\triasdev.mvc\xtension\oltxtext\helper.h \
	e:\triasdev.mvc\xtension\oltxtext\igentext.h \
	e:\triasdev.mvc\xtension\oltxtext\textp.h


all:	$(PROJ).DLL

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

ITERATOR.OBJ:	ITERATOR.CPP $(ITERATOR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ITERATOR.CPP

DEL.OBJ:	DEL.CPP $(DEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DEL.CPP

ENREL.OBJ:	ENREL.CPP $(ENREL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENREL.CPP

ENOBMEN.OBJ:	ENOBMEN.CPP $(ENOBMEN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENOBMEN.CPP

DLGABH.OBJ:	DLGABH.CPP $(DLGABH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLGABH.CPP

ENBXVOLL.OBJ:	ENBXVOLL.CPP $(ENBXVOLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENBXVOLL.CPP

ENUMOBJ.OBJ:	ENUMOBJ.CPP $(ENUMOBJ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENUMOBJ.CPP

TEXTDLG1.OBJ:	TEXTDLG1.CPP $(TEXTDLG1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTDLG1.CPP

TEXTEX1.OBJ:	TEXTEX1.CPP $(TEXTEX1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTEX1.CPP

TXTRDLG1.OBJ:	TXTRDLG1.CPP $(TXTRDLG1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TXTRDLG1.CPP

ENOBAB1.OBJ:	ENOBAB1.CPP $(ENOBAB1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENOBAB1.CPP

OLTXTEXT.RES:	OLTXTEXT.RC $(OLTXTEXT_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r OLTXTEXT.RC

HELPER.OBJ:	HELPER.CPP $(HELPER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c HELPER.CPP

TEXTP.OBJ:	TEXTP.CPP $(TEXTP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTP.CPP


$(PROJ).DLL::	OLTXTEXT.RES

$(PROJ).DLL::	STDAFX.OBJ ITERATOR.OBJ DEL.OBJ ENREL.OBJ ENOBMEN.OBJ DLGABH.OBJ ENBXVOLL.OBJ \
	ENUMOBJ.OBJ TEXTDLG1.OBJ TEXTEX1.OBJ TXTRDLG1.OBJ ENOBAB1.OBJ HELPER.OBJ TEXTP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
ITERATOR.OBJ +
DEL.OBJ +
ENREL.OBJ +
ENOBMEN.OBJ +
DLGABH.OBJ +
ENBXVOLL.OBJ +
ENUMOBJ.OBJ +
TEXTDLG1.OBJ +
TEXTEX1.OBJ +
TXTRDLG1.OBJ +
ENOBAB1.OBJ +
HELPER.OBJ +
TEXTP.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
e:\cv.mvc\lib16\+
e:\triasdev.mvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) OLTXTEXT.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	OLTXTEXT.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) OLTXTEXT.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
