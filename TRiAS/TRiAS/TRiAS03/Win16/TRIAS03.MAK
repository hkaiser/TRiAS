# TRIAS03 - Erweiterungen zu CommonView 3.1

# Generierungsdatum (yymmdd) und Version
DATE = 960501
VERSION = 2
RELEASE = 10
BUILD = 034

COPYRIGHT = HK$(DATE)

PNAME = "Version für den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"

#PNAME = "Dr. Eckstein/Dr. Walkow"
#PADDRESS = "Landratsamt Bitterfeld"

DEFS = -DMSWIND -DDLL -D__XT

DEBUG=1

!IF $(DEBUG)==1
CXXOPT = -Zi -Od -G2s -Ob1 -D_DEBUG -DMSCC8
LINKFLAGS=/CO/F/NOE/MAP:FULL/SE:256/packc/onerror:noexe/align:16/nod
ASMF= /D?PLM=0 /D?WIN=1 /Zi 
!ELSE
CXXOPT = -O2 -G3s -DNDEBUG -DMSCC8
LINKFLAGS=/NOE/MAP:FULL/se:256/packc/onerror:noexe/align:16/nod/nopackf
ASMF= /D?PLM=0 /D?WIN=1
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -Alfw $(CXXOPT) -I..\include
CCREQ2 =-D__CV__ -DSTRICT $(DEFS) -W3 -D__XT -D__DEXPROCS
CCREQ3 =-DEXPORT03=__export -Ie:\cv.mvc\include

CCDYNREQ= trias03.rsp

LTEMP = link.tmp
LTEMPMAP = linkmap.tmp

LINK = link
LIB = lib
ASM = masm
CC = cl /nologo
CCXX = cl /nologo
RC = rc

RCFLAGS = -K
CCXXFLAGS = @$(CCDYNREQ) -Yutrias03p.hxx
CCXXPCOMPFLAGS = @$(CCDYNREQ) -Yctrias03p.hxx
CFLAGS = @$(CCDYNREQ) -Yutrias03p.hxx

PRECOMPHDRS = trias03p.hxx
PRECOMPRELS = $(PRECOMPHDRS) trias03p.pch
PCOMPOBJ = trias03p.obj

LIBS1 = e:\cv.mvc\lib16\ c:\msvc\lib\ e:\triasdev.mvc\lib\ oldnames
LIBS2 = freestor ldllcew trias02 trias01 muscroll framelib lstrdwd
LIBS3 = containr compobj ole2 storage commdlg lzexpand libw mmsystem
LIBS  = $(LIBS1) $(LIBS2) $(LIBS3)

NAME = trias03
STUB = rights

OUTDLL = $(NAME).dll
OUTLIB = $(NAME).lib
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
RIGHTS = $(STUB).exe
REPLACE = ersetz

LTMP = link.tmp
LTMPMAP = linkmap.tmp

LIBD = c:\triasdev.mvc\lib\

SYSOBJS = libmain3.obj 
OBJ1 = trias03p.obj timer.obj helptext.obj selidlst.obj 
OBJ2 = datatran.obj dataobj.obj idataobj.obj ienumfe.obj
OBJ3 = numedit.obj oddlgwin.obj owncombo.obj spinctrl.obj
OBJ4 = muscroll.obj prntpars.obj statimpl.obj status16.obj
OBJ5 = dblnumed.obj ownlist.obj ownliste.obj

OBJECTS = $(SYSOBJS) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)

# Alles neubilden
all:	$(CCDYNREQ) dll lib

# Nur Bibliothek neubilden
dll:	$(PCOMPOBJ) $(OUTDLL)

trias03p.pch:	$(PRECOMPHDRS) trias03p.cxx

trias03p.obj:	trias03p.cxx $(PRECOMPHDRS)
	$(CCXX) $(CCXXPCOMPFLAGS) -c trias03p.cxx
	
newexport:
	@del $(MAP) > nul
	@del $(LTMPMAP) > nul

$(CCDYNREQ):
	echo $(CCREQ1) > $(CCDYNREQ)
	echo $(CCREQ2) >> $(CCDYNREQ)
	echo $(CCREQ3) >> $(CCDYNREQ)

# am Anfang alles loeschen 
rmall:
	del *.obj
	del $(DEF)

$(NAME).res:	$(NAME).rc $(NAME).rcv
	$(RC) -r $(NAME).rc

$(OUTDLL):	$(OBJECTS) $(DEF) $(RIGHTS) $(LTMP) $(NAME).res
	$(LINK) /nol @$(LTEMP),$(DEF)
	$(RC) $(RCFLAGS) $(NAME).res $(OUTDLL)

lib:	$(OUTLIB)

$(OUTLIB):	$(DEF) $(LIBOBJS)
	implib $(OUTLIB) $(DEF)
	@copy $(OUTLIB) $(LIBD)

$(MAP):	$(OBJECTS) $(STUB).exe $(LTMPMAP) $(NAME).tpl
	$(LINK) /nol @$(LTMPMAP),$(NAME).tpl
	@del $(OUTDLL) > nul

$(LTMP):	makefile
	@echo $(SYSOBJS) + > $(LTEMP)
	@echo $(OBJ1) + >> $(LTEMP)
	@echo $(OBJ2) + >> $(LTEMP)
	@echo $(OBJ3) + >> $(LTEMP)
	@echo $(OBJ4) + >> $(LTEMP)
	@echo $(OBJ5) + >> $(LTEMP)
	@echo $(LINKFLAGS) >> $(LTEMP)
	@echo $(OUTDLL) >> $(LTEMP)
	@echo nul >> $(LTEMP)
	@echo $(LIBS1) + >> $(LTEMP)
	@echo $(LIBS2) + >> $(LTEMP)
	@echo $(LIBS3) >> $(LTEMP)

$(LTMPMAP):	makefile
	@echo $(SYSOBJS) + > $(LTEMPMAP)
	@echo $(OBJ1) + >> $(LTEMPMAP)
	@echo $(OBJ2) + >> $(LTEMPMAP)
	@echo $(OBJ3) + >> $(LTEMPMAP)
	@echo $(OBJ4) + >> $(LTEMPMAP)
	@echo $(OBJ5) + >> $(LTEMPMAP)
	@echo $(LINKFLAGS) >> $(LTEMPMAP)
	@echo $(OUTDLL) >> $(LTEMPMAP)
	@echo $(MAP) /map/line >> $(LTEMPMAP)
	@echo $(LIBS1) + >> $(LTEMPMAP)
	@echo $(LIBS2) + >> $(LTEMPMAP)
	@echo $(LIBS3) >> $(LTEMPMAP)

# Objektabhängigkeiten -------------------------------------------------------
timer.obj:	timer.cxx 
	$(CCXX) -c $(CCXXFLAGS) timer.cxx

listbox.obj:	listbox.cxx 
	$(CCXX) -c $(CCXXFLAGS) listbox.cxx

opttree.obj:	opttree.cxx 
	$(CCXX) -c $(CCXXFLAGS) opttree.cxx

dcreator.obj:	dcreator.cxx
	$(CCXX) -c $(CCXXFLAGS) dcreator.cxx

deltree.obj:	deltree.cxx
	$(CCXX) -c $(CCXXFLAGS) deltree.cxx

numedit.obj:	numedit.cxx
	$(CCXX) -c $(CCXXFLAGS) numedit.cxx

dblnumed.obj:	dblnumed.cxx
	$(CCXX) -c $(CCXXFLAGS) dblnumed.cxx

commfil.obj:	commfil.cxx
	$(CCXX) -c $(CCXXFLAGS) commfil.cxx

efont.obj:	efont.cxx
	$(CCXX) -c $(CCXXD) efont.cxx

prntpars.obj:	prntpars.cxx 
	$(CCXX) -c $(CCXXFLAGS) prntpars.cxx

helptext.obj:	helptext.cxx 
	$(CCXX) -c $(CCXXFLAGS) helptext.cxx

selidlst.obj:	selidlst.cxx 
	$(CCXX) -c $(CCXXFLAGS) selidlst.cxx

epen.obj:	epen.cxx
	$(CCXX) -c $(CCXXFLAGS) epen.cxx

registry.obj:	registry.cxx
	$(CCXX) -c $(CCXXFLAGS) registry.cxx

statimpl.obj:	statimpl.cxx
	$(CCXX) -c $(CCXXFLAGS) statimpl.cxx

status16.obj:	status16.cpp
	$(CCXX) -c $(CCXXFLAGS) status16.cpp

.cxx.obj:
	$(CCXX) -c $(CCXXFLAGS) $*.cxx

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(MAP)
	@del $(DEF)
	@del $(STUB).asm
	@del $(NAME).rcv

formake:	$(DEF) $(STUB).exe $(NAME).rcv

$(DEF):		$(NAME).tpl $(MAP)
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	awk -f export.awk $(MAP) >> $(DEF)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

$(STUB).exe:	$(STUB).asm
	$(ASM) $(STUB) ;
	$(LINK) $(STUB) ;

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

