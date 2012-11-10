# Makefile fьr ErweiterungsTemplate -------------------------------------------
# Windows/DLL-Version
# MSC V8.0c (Windows)

.SUFFIXES:
.SUFFIXES: .y .cxx .c .asm .obj .exe .dll .ext

DEBUG = 0

# Erweiterte Visualisierung (Symbolisierung unterstьtzen) 
EXTVIS = 1

# Generierungsdatum (yymmdd) und Version
DATE=960410
VERSION = 2
RELEASE = 00
BUILD = 009

COPYRIGHT = HK$(DATE)

PADDRESS = " "
PNAME = " "

#PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"
#PNAME = "Version f\xfcr den internen Gebrauch"

# SU-Variante
#PNAME = "Версия для Центра Аэрокосмических"
#PADDRESS = "Исследований Земли"

LIBD = e:\triasdev.mvc\lib
WINDIR = c:\win95

!ifdef EXTVIS
DEFS = -DEXTVIS -DNODBIO -D__DEXPROCS
RCDEFS = -DEXTVIS
!else
DEFS =
RCDEFS = 
!endif

!IF $(DEBUG)==1
CXXOPT = -Zi -Od -G2 -Ob1 -D_DEBUG
LINKFLAGS=/CO/F/NOE/MAP:FULL/SE:256/packc/farc/onerror:noexe/nopackf/nod
!ELSE
CXXOPT = -O2 -G3 -DNDEBUG
LINKFLAGS=/F/NOE/se:256/packc/farc/onerror:noexe/nopackf/nod
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -Alfw $(CXXOPT) 
CCREQ2 =-Ie:\triasdev.mvc\include -Ie:\cv.mvc\include
CCREQ3 =-D__CV__ -DSTRICT -DMSWIND -DMSCC8 -DDLL -D__XT $(DEFS)
ASMF= -Zi -c

CCXXFLAGS = @$(CCDYNREQ) -Yuvisobjp.hxx
CCXXPCOMPFLAGS = @$(CCDYNREQ) -Ycvisobjp.hxx
CFLAGS = @$(CCDYNREQ) -Yuvisobjp.hxx
YACCFLAGS = -d
LEXFLAGS = 

LTEMP = link.tmp
LINK = link
ASM = ml

LIB1 = e:\triasdev.mvc\lib\ e:\cv.mvc\lib16\ c:\msvc\lib\ freestor 
LIB3 = ldllcew ixtnsr16 ctl3dv2 framelib containr oldnames libw

!ifdef EXTVIS
LIB2 = lstrdw shell compobj ole2 typelib ole2disp mmsystem
!else
LIB2 = lstrdwd shell mmsystem
!endif

LIBS = $(LIB1) $(LIB2) $(LIB3)

CC = cl
CCXX = cl
YACC = yacc
LEX = lex

MODEL = -A$(M)
NAME = visobj
STUB = rights

OUTDLL = $(NAME).ext
OUTLIB = $(NAME).lib
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
RIGHTS = $(STUB).exe

CCDYNREQ= $(NAME).rsp

OBJ1 =	visobjp.obj 
#libmain.obj 
OBJ2 =	visobj.obj visobjyp.obj visobjlp.obj rgb_hsb.obj
OBJ3 = 	visinfo.obj changevi.obj viserrdg.obj viserror.obj
OBJ4 =	bmpbox.obj resetvis.obj rsethide.obj visexp.obj
OBJ5 =	vstatus.obj visimp.obj visidlyp.obj visidllp.obj
OBJ6 =	yy2stype.obj initpars.obj cimpview.obj colcntrl.obj
OBJ7 =	rangenum.obj uidobj.obj copttree.obj
!ifdef EXTVIS
OBJ8 =	vismtree.obj xvisdlg.obj
!else
OBJ8 =
!endif

OBJECTS = $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8)

PRECOMPHDRS = visobjp.hxx
PRECOMPRELS = $(PRECOMPHDRS) visobjp.pch
PCOMPOBJ = visobjp.obj

# Alles neu bilden
all:	$(CCDYNREQ) formake dll 

# DLL neu bilden
dll:	$(OUTDLL)

visobjp.pch:	$(PRECOMPHDRS) visobjp.cxx visobjp.hxx

visobjp.obj:	visobjp.cxx visobjp.hxx $(PRECOMPHDRS)
	$(CCXX) $(CCXXPCOMPFLAGS) -c visobjp.cxx

$(OBJECTS):	$(PRECOMPHDRS) visobjp.pch

DLG1 =	visimp.dlg vstatus.dlg colcntrl.dlg
DLG2 =	defabout.src viserrdg.dlg resetvis.dlg visexp.dlg 
DIALOGS = $(DLG1) $(DLG2)

ICONS =	lupe.ico
BITMAPS = verror.bmp

RESOURCES = $(DIALOGS) $(ICONS) $(BITMAPS)

$(CCDYNREQ):
	echo $(CCREQ1)    > 	$(CCDYNREQ)
	echo $(CCREQ2)    >>  	$(CCDYNREQ)
	echo $(CCREQ3)    >>  	$(CCDYNREQ)

$(NAME).res:	$(NAME).rc $(RESOURCES) $(NAME).rcv
	rc -r -Ie:\triasdev.mvc\include $(RCDEFS) $(NAME).rc

$(OUTDLL):	$(OBJECTS) $(DEF) $(NAME).res $(STUB).exe
	@echo $(OBJ1) + > $(LTEMP)
	@echo $(OBJ2) + >> $(LTEMP)
	@echo $(OBJ3) + >> $(LTEMP)
	@echo $(OBJ4) + >> $(LTEMP)
	@echo $(OBJ5) + >> $(LTEMP)
	@echo $(OBJ6) + >> $(LTEMP)
	@echo $(OBJ7) + >> $(LTEMP)
	@echo $(OBJ8) + >> $(LTEMP)
	@echo $(LINKFLAGS) >> $(LTEMP)
	@echo $(OUTDLL) >> $(LTEMP)
	@echo $(MAP) /map/line >> $(LTEMP)
	@echo $(LIB1) + >> $(LTEMP)
	@echo $(LIB2) + >> $(LTEMP)
	@echo $(LIB3) >> $(LTEMP)
	@echo $(DEF) >> $(LTEMP)
	$(LINK) /nol @$(LTEMP)
	rc -K $(NAME).res $(OUTDLL)

# ImportBibliothek neu bilden
lib:	$(OUTLIB)

yaccidl:	visidlyp.obj visidllp.obj

yaccobj:	visobjyp.obj visobjlp.obj

libmain.obj:	libmain.cxx
	$(CC) $(CFLAGS) -c libmain.cxx

wep.obj:	wep.c
	$(CC) $(CFLAGS) -c wep.c

visobj.obj:	visobj.cxx visobj.hxx

visobjyp.obj:	visobjyp.cxx visobjy.y visobjy.par visobjy.scr
	@copy visobjy.par c:\lib\yacc.par > nul
	$(YACC) $(YACCFLAGS) visobjy.y
	@del yvisobj.h > nul
	@ren ytab.h yvisobj.h > nul
	sed -f visobjy.scr ytab.c > visobjy.cxx
	@del ytab.c > nul
#	$(CCXX) -c $(CCXXFLAGS) visobjyp.cxx

visobjlp.obj:	visobjlp.cxx visobjl.lx visobjl.scr
	$(LEX) $(LEXFLAGS) visobjl.lx
	sed -f visobjl.scr lexyy.c > visobjl.cxx
	@del lexyy.c > nul
#	$(CCXX) -c $(CCXXFLAGS) visobjlp.cxx

visidlyp.obj:	visidlyp.cxx visidly.y visidly.par visidly.scr
	@copy visidly.par c:\lib\yacc.par > nul
	$(YACC) $(YACCFLAGS) visidly.y
	@del yvisidl.h > nul
	@ren ytab.h yvisidl.h > nul
	sed -f visidly.scr ytab.c > visidly.cxx
	@del ytab.c > nul
#	$(CCXX) -c $(CCXXFLAGS) visidlyp.cxx

visidllp.obj:	visidllp.cxx visidll.lx visidll.scr
	$(LEX) $(LEXFLAGS) visidll.lx
	sed -f visidll.scr lexyy.c > visidll.cxx
	@del lexyy.c > nul
#	$(CCXX) -c $(CCXXFLAGS) visidllp.cxx

.cxx.obj:
	$(CCXX) $(CCXXFLAGS) -c $*.cxx

# Versionskontrolle -----------------------------------------------------------
$(STUB).exe:	$(STUB).asm
	masm rights;
	link rights;

new:
	@del $(DEF) > nul
	@del $(STUB).asm > nul
	@del $(NAME).rcv > nul
	@del defabout.src > nul
	@del versio16.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv defabout.src versio16.h

$(DEF):		$(NAME).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

$(STUB).asm:	$(STUB).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

defabout.src:	defabout.dlg
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defabout.dlg tmp.src
	ersetz $(PNAME) $(PADDRESS) tmp.src defabout.src
	@del tmp.src > nul

versio16.h:	versio16.tpl 
	ersetz $(VERSION) $(RELEASE) versio16.tpl versio16.h

# Personalisierungsinformation
$(NAME).rcv:	visobjv.tpl
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B visobjv.tpl tmp.rcv
	ersetz $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

# Lokalisierung ---------------------------------------------------------------
german:
	@copy visobger.rc visobj.rc > nul
	@copy defabger.dlg defabout.dlg > nul

russian:
	@copy visobrus.rc visobj.rc > nul
	@copy defabrus.dlg defabout.dlg > nul

