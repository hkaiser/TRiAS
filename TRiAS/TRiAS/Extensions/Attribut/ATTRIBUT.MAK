# Makefile für Erweiterung zur Sachdatenbehandlung
# Windows/DLL-Version
# MSVC V8.0c (Windows)

DEBUG = 1

# Generierungsdatum (yymmdd) und Version
DATE=960520
VERSION = 1
RELEASE = 30
BUILD = 004
COPYRIGHT = KK$(DATE)

PNAME = "Version für den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

LIBD = c:\triasdev.mvc\lib
WINDIR = c:\windows

DEFS = -DMSWIND -DDLL -D__XT

!IF $(DEBUG)==1
CXXOPT = -Zi -Od -G2 -Ob1 -D_DEBUG
LINKFLAGS=/CO/F/NOE/MAP:FULL/SE:256/packc/farc/onerror:noexe/nod
!ELSE
CXXOPT = -O2 -G3 -D_NODEBUG
LINKFLAGS=/F /NOE /MAP:FULL/se:256/packc/farc/onerror:noexe
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -Alfw -W3 $(CXXOPT) -Gx -Gt65500 -Gf
CCREQ2 =-Ic:\triasdev.mvc\include -Ic:\cv.mvc\include
CCREQ3 =-D__CV__ -DSTRICT -DMSWIND -DMSCC8 -DDLL -D__XT -D__DEXPROCS
ASM = masm
ASMF = /D?PLM=0 /D?WIN=1

LTEMP = link.tmp
LTMPMAP = linkmap.tmp
LINK = link
LIB1 = c:\triasdev.mvc\lib\ c:\cv.mvc\lib16\ c:\msvc\lib\ freestor 
LIB2 = lstrdwd ldllcew ixtnsd16 ctl3dv2 framelib containr oldnames libw mmsystem
LIB3 = shell compobj ole2 typelib ole2disp
LIBS = $(LIB1) $(LIB2) $(LIB3)

CC = cl
CCXX = cl

# ModuleNamen entsprechend ändern
NAME = attribut
STUB = rights
REPLACE = ersetz

OUTDIR = c:\trias\trias130

OUTDLL = $(NAME).ext
OUTLIB = $(NAME).lib
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
RIGHTS = $(STUB).exe
CCDYNREQ= $(NAME).rsp

CCXXFLAGS = @$(CCDYNREQ)
CFLAGS = @$(CCDYNREQ) -Yuattribp.hxx

OBJ1 =	attribp.obj auswahl.obj idkey.obj clstree.obj
OBJ2 =	attinfo.obj objkey.obj bilden.obj osorge.obj
OBJ3 = 	strutil.obj stohwnd.obj erben.obj asorge.obj
OBJ4 =	txtedit.obj mwerte.obj attribut.obj

OBJECTS = $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

# Alles neu bilden
all:	$(CCDYNREQ) formake dll

# DLL neu bilden
dll:	$(OUTDLL)

# neu Exporte dazugekommen
newexp:
	@del $(MAP) > nul
	@del $(LTMPMAP) > nul

# Compiler-ResponseFile generieren
$(CCDYNREQ):	$(NAME).mak
	@echo $(CCREQ1)    > 	$(CCDYNREQ)
	@echo $(CCREQ2)    >>  	$(CCDYNREQ)
	@echo $(CCREQ3)    >>  	$(CCDYNREQ)

# Resource compilieren
$(NAME).res:	$(NAME).rc
	rc -r $(NAME).rc

# entgültiges Linken und ResourceBinden
$(OUTDLL):	$(OBJECTS) $(DEF) $(STUB).exe $(LTEMP) $(NAME).res
	$(LINK) /nol @$(LTEMP),$(DEF)
	rc $(RCFLAGS) -K $(NAME).res $(OUTDLL)
	copy $(OUTDLL) $(OUTDIR)\$(OUTDLL)

# Linken, um MAP-Datei zu erzeugen, die für Extraktion der Exporte notwendig ist
$(MAP):		$(OBJECTS) $(STUB).exe $(LTMPMAP) $(NAME).tpl
	$(LINK) /nol @$(LTMPMAP),$(NAME).tpl
	@del $(OUTDLL) > nul

# Linker-ResponseFile für entgültiges Linken bilden
$(LTEMP):	$(NAME).mak
	@echo $(OBJ1) + > $(LTEMP)
	@echo $(OBJ2) + >> $(LTEMP)
	@echo $(OBJ3) + >> $(LTEMP)
	@echo $(OBJ4) + >> $(LTEMP)
	@echo $(LINKFLAGS) >> $(LTEMP)
	@echo $(OUTDLL) >> $(LTEMP)
	@echo nul >> $(LTEMP)
	@echo $(LIB1) + >> $(LTEMP)
	@echo $(LIB2) + >> $(LTEMP)
	@echo $(LIB3) >> $(LTEMP)

# LinkerResponseFile für MAP-Datei-Bilden generieren
$(LTMPMAP):	$(NAME).mak
	@echo $(OBJ1) + > $(LTMPMAP)
	@echo $(OBJ2) + >> $(LTMPMAP)
	@echo $(OBJ3) + >> $(LTMPMAP)
	@echo $(OBJ4) + >> $(LTMPMAP)
	@echo $(LINKFLAGS) >> $(LTMPMAP)
	@echo $(OUTDLL) >> $(LTMPMAP)
	@echo $(MAP) /map >> $(LTMPMAP)
	@echo $(LIB1) + >> $(LTMPMAP)
	@echo $(LIB2) + >> $(LTMPMAP)
	@echo $(LIB3) >> $(LTMPMAP)

# ImportBibliothek neu bilden
lib:	$(OUTLIB)

libmain.obj:	libmain.cxx
	$(CC) $(CFLAGS) -c libmain.cxx

wep.obj:	wep.c
	$(CC) $(CFLAGS) -c wep.c


attribp.obj:	attribp.cxx

attinfo.obj:	attinfo.cxx

stohwnd.obj:	stohwnd.cxx

strutil.obj:	strutil.cxx

txtedit.obj:	txtedit.cxx

erben.obj:	erben.cxx

auswahl.obj:	auswahl.cxx

bilden.obj:	bilden.cxx

mwerte.obj:	mwerte.cxx

objkey.obj:	objkey.cxx

idkey.obj:	idkey.cxx

clstree.obj:	clstree.cxx  

asorge.obj:	asorge.cxx

osorge.obj:	osorge.cxx

attribut.obj:	attribut.cxx 

.cxx.obj:
	$(CCXX) /nologo $(CCXXFLAGS) -c $*.cxx

# Versionskontrolle -----------------------------------------------------------
$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# alle versionsabhängien Datein löschen
new:
	@del $(DEF) > nul
	@del $(STUB).asm > nul
	@del $(NAME).rcv > nul
	@del about.src > nul
	@del versio16.h > nul

# nur Versionsabhängigkeiten auflösen
formake:	$(DEF) $(STUB).exe $(NAME).rcv about.src versio16.h

# ModulDefinitionsDatei mit allen Exporten generieren
$(DEF):		$(NAME).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

$(STUB).asm:	$(STUB).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

about.src:	about.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B about.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv about.src
	@del tmp.rcv > nul

versio16.h:	versio16.tpl
	$(REPLACE) $(VERSION) $(RELEASE) versio16.tpl versio16.h

# Personalisierungsinformation
$(NAME).rcv:	attribv.tpl
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B attribv.tpl tmp.rcv
	ersetz $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

