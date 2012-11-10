# Makefile fuer DBNDLL
# File: MAKEFILE

# Generierungsdatum (yymmdd) und Version
DATE = 960501
VERSION = 4
RELEASE = 10
BUILD = 073

COPYRIGHT = HK$(DATE)

PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

# SU-Variante
#PNAME = "Версия для Центра Аэрокосмических"
#PADDRESS = "Исследований Земли"

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"

#PNAME = "Dr. Eckstein/Dr.Walkow"
#PADDRESS = "Landratsamt Bitterfeld"

DEFS = -DMSWIND -DDLL -D__XT

DEBUG=1

!IF $(DEBUG)==1
CXXOPT = -Zi -Od -G2 -Ob1 -D_DEBUG
LINKFLAGS=/CO/F/NOE/MAP:FULL/SE:256/packc/onerror:noexe/align:16
ASMF= /D?PLM=0 /D?WIN=1 /Zi
!ELSE
CXXOPT = -O2 -G3s -DNDEBUG
LINKFLAGS=/NOE/se:256/packc/onerror:noexe/align:16/nopackf
ASMF= /D?PLM=0 /D?WIN=1
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -Alfw $(CXXOPT) -I..\include
CCREQ2 =-D__CV__ -DSTRICT $(DEFS) -W3 -D__XT -D__DEXPROCS
CCREQ3 =-DEXPORT02=__export -Ie:\cv.mvc\include
ASMF= /D?PLM=0 /D?WIN=1 /Zi 

CCDYNREQ= trias02.rsp

LTEMP = link.tmp
LIBTMP = lib.tmp
LINK = link
LIB = lib
ASM = masm
CC = cl /nologo
CCXX = cl /nologo
RC = rc

RCFLAGS = -K
CCXXFLAGS = @$(CCDYNREQ) -Yutrias02p.hxx
CCXXPCOMPFLAGS = @$(CCDYNREQ) -Yctrias02p.hxx
CFLAGS = @$(CCDYNREQ) -Yutrias02p.hxx
CFLAGSWOCOMP = @$(CCDYNREQ)

PRECOMPHDRS = trias02p.hxx
PRECOMPRELS = $(PRECOMPHDRS) trias02p.pch
PCOMPOBJ = trias02p.obj

LIBS1 = e:\cv.mvc\lib16\ c:\msvc\lib\ e:\triasdev.mvc\lib\ +
LIBS2 = lstrdw freestor ldllcew trias01 framelib containr +
LIBS3 = ctl3dv2 commdlg libw shell compobj
LIBS  = $(LIBS1) $(LIBS2) $(LIBS3)

NAME = trias02
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

LIBD = c:\triasdev.mvc\lib
EXED = c:\trias.mvc\trias

# Objektmodule
SYSOBJS = libmain2.obj

OBJ1 = getgi.obj getgip.obj getgil.obj getgif.obj getkan.obj
OBJ2 = stinfl.obj igptnl.obj modid.obj getmerkl.obj
OBJ3 = fndgi.obj fndpu.obj fndka.obj fndli.obj puinfl.obj
OBJ4 = htfunc.obj qtfunc.obj fndma.obj iglage.obj
OBJ5 = mfind.obj mgettx.obj mgetkt.obj getmi.obj pbdids.obj
OBJ6 = mgetkm.obj mgetwm.obj getlongm.obj mputkm.obj mdelkm.obj
# mitst.obj readmk.obj girig.obj
OBJ7 = getdblm.obj mgetl.obj getlen.obj mgetkr.obj fndtxtn.obj
OBJ8 = getrig.obj getril.obj getrif.obj getrip.obj htmanr.obj
OBJ9 = rigin.obj rigkp.obj getapu.obj fndtxt.obj merkinfo.obj
OBJ10 = strutil.obj isalike.obj mdelkr.obj mputkr.obj
OBJ11 = datetime.obj drawrect.obj gettext.obj getmit.obj
OBJ12 = puttxtc.obj puttxtcn.obj gettextn.obj pbdtemp.obj
#putco.obj nket.obj 
OBJ13 = delmin.obj dellink.obj delid.obj del.obj delgip.obj
OBJ14 = delgi.obj delgil.obj delkan.obj delgif.obj delkanf.obj
OBJ15 = putlink.obj putmit.obj gettextl.obj putrel.obj 
OBJ16 = delrel.obj puttobj.obj putident.obj putpkt.obj
OBJ17 = putkobj.obj mdelki.obj freetext.obj mputkt.obj
OBJ18 = mputki.obj mputtx.obj putpobj.obj putlobj.obj 
OBJ19 = putfobj.obj ovlpobj.obj ovllobj.obj ovlfobj.obj
OBJ20 = puttempl.obj dbasrt02.obj registry.obj ole16.obj
#
# C++ Module
#
OBJ21 = getrel.obj getrcode.obj findrel.obj visinfo.obj
OBJ22 = db.obj dbgetgi.obj riginfo.obj giwindow.obj 
OBJ23 = geo_obj.obj geo_obj1.obj gerade.obj relatio.obj
OBJ24 = pbd.obj hdrentry.obj attribs.obj oliste.obj
OBJ25 = merkmal.obj ident.obj profdll.obj palette.obj
OBJ26 = geotext.obj rect.obj delrelko.obj komplex.obj
OBJ27 = viserror.obj efont.obj epen.obj commfil.obj
OBJ28 = objmtree.obj ctf.obj dllbind.obj evalkoef.obj
OBJ29 = trias02p.obj

OBJECTS = $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ9) $(OBJ10) \
	  $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(SYSOBJS) $(OBJ11) \
	  $(OBJ12) $(OBJ13) $(OBJ14) $(OBJ15) $(OBJ16) $(OBJ17) \
	  $(OBJ18) $(OBJ19) $(OBJ20) $(OBJ21) $(OBJ22) $(OBJ23) \
	  $(OBJ24) $(OBJ25) $(OBJ26) $(OBJ27) $(OBJ28) $(OBJ29)

# Target 
all:	$(CCDYNREQ) dll lib

dll:	$(PCOMPOBJ) $(OUTDLL)

trias02p.pch:	$(PRECOMPHDRS) trias02p.cxx

trias02p.obj:	trias02p.cxx $(PRECOMPHDRS)
	$(CCXX) $(CCXXPCOMPFLAGS) -c trias02p.cxx
	
$(OBJECTS):	$(PRECOMPRELS)

newexport:
	@del $(MAP) > nul
	@del $(LTMPMAP) > nul

$(CCDYNREQ):
	echo $(CCREQ1) > $(CCDYNREQ)
	echo $(CCREQ2) >> $(CCDYNREQ)
	echo $(CCREQ3) >> $(CCDYNREQ)

# Linkerlauf
$(NAME).res:	$(NAME).rc $(NAME).rcv
	rc -r -I..\include $(NAME).rc

$(OUTDLL):	$(OBJECTS) $(DEF) $(STUB).exe $(LTMP) $(NAME).res
	$(LINK) /nol @$(LTMP),$(NAME).def
	rc $(RCFLAGS) $(NAME).res $(OUTDLL)
	@copy $(OUTDLL) $(EXED)

$(MAP):	$(OBJECTS) $(STUB).exe $(LTMPMAP) $(NAME).tpl
	$(LINK) /nol @$(LTMPMAP),$(NAME).tpl
	@del $(OUTDLL) > nul

# Aufbau der Linker-Kommandodatei, wenn 'makefile' geaendert wurde
$(LTMP):	makefile
	@echo $(SYSOBJS) + > $(LTMP)
	@echo $(OBJ1) + >> $(LTMP)
	@echo $(OBJ2) + >> $(LTMP)
	@echo $(OBJ3) + >> $(LTMP)
	@echo $(OBJ4) + >> $(LTMP)
	@echo $(OBJ5) + >> $(LTMP)
	@echo $(OBJ6) + >> $(LTMP)
	@echo $(OBJ7) + >> $(LTMP)
	@echo $(OBJ8) + >> $(LTMP)
	@echo $(OBJ9) + >> $(LTMP)
	@echo $(OBJ10) + >> $(LTMP)
	@echo $(OBJ11) + >> $(LTMP)
	@echo $(OBJ12) + >> $(LTMP)
	@echo $(OBJ13) + >> $(LTMP)
	@echo $(OBJ14) + >> $(LTMP)
	@echo $(OBJ15) + >> $(LTMP)
	@echo $(OBJ16) + >> $(LTMP)
	@echo $(OBJ17) + >> $(LTMP)
	@echo $(OBJ18) + >> $(LTMP)
	@echo $(OBJ19) + >> $(LTMP)
	@echo $(OBJ20) + >> $(LTMP)
	@echo $(OBJ21) + >> $(LTMP)
	@echo $(OBJ22) + >> $(LTMP)
	@echo $(OBJ23) + >> $(LTMP)
	@echo $(OBJ24) + >> $(LTMP)
	@echo $(OBJ25) + >> $(LTMP)
	@echo $(OBJ26) + >> $(LTMP)
	@echo $(OBJ27) + >> $(LTMP)
	@echo $(OBJ28) + >> $(LTMP)
	@echo $(OBJ29) + >> $(LTMP)
	@echo $(LINKFLAGS) >> $(LTMP)
	@echo $(OUTDLL) >> $(LTMP)
	@echo nul >> $(LTMP)
	@echo $(LIBS1) >> $(LTMP)
	@echo $(LIBS2) >> $(LTMP)
	@echo $(LIBS3) >> $(LTMP)

	
# Aufbau der Linker-Kommandodatei, wenn Exports ge„ndert wurden
$(LTMPMAP):	makefile
	@echo $(SYSOBJS) + > $(LTMPMAP)
	@echo $(OBJ1) + >> $(LTMPMAP)
	@echo $(OBJ2) + >> $(LTMPMAP)
	@echo $(OBJ3) + >> $(LTMPMAP)
	@echo $(OBJ4) + >> $(LTMPMAP)
	@echo $(OBJ5) + >> $(LTMPMAP)
	@echo $(OBJ6) + >> $(LTMPMAP)
	@echo $(OBJ7) + >> $(LTMPMAP)
	@echo $(OBJ8) + >> $(LTMPMAP)
	@echo $(OBJ9) + >> $(LTMPMAP)
	@echo $(OBJ10) + >> $(LTMPMAP)
	@echo $(OBJ11) + >> $(LTMPMAP)
	@echo $(OBJ12) + >> $(LTMPMAP)
	@echo $(OBJ13) + >> $(LTMPMAP)
	@echo $(OBJ14) + >> $(LTMPMAP)
	@echo $(OBJ15) + >> $(LTMPMAP)
	@echo $(OBJ16) + >> $(LTMPMAP)
	@echo $(OBJ17) + >> $(LTMPMAP)
	@echo $(OBJ18) + >> $(LTMPMAP)
	@echo $(OBJ19) + >> $(LTMPMAP)
	@echo $(OBJ20) + >> $(LTMPMAP)
	@echo $(OBJ21) + >> $(LTMPMAP)
	@echo $(OBJ22) + >> $(LTMPMAP)
	@echo $(OBJ23) + >> $(LTMPMAP)
	@echo $(OBJ24) + >> $(LTMPMAP)
	@echo $(OBJ25) + >> $(LTMPMAP)
	@echo $(OBJ26) + >> $(LTMPMAP)
	@echo $(OBJ27) + >> $(LTMPMAP)
	@echo $(OBJ28) + >> $(LTMPMAP)
	@echo $(OBJ29) + >> $(LTMPMAP)
	@echo $(LINKFLAGS) >> $(LTMPMAP)
	@echo $(OUTDLL) >> $(LTMPMAP)
	@echo $(MAP) /line /map >> $(LTMPMAP)
	@echo $(LIBS1) >> $(LTMPMAP)
	@echo $(LIBS2) >> $(LTMPMAP)
	@echo $(LIBS3) >> $(LTMPMAP)

# CopyrightEintraege Generieren 
lib:	$(OUTLIB)

$(OUTLIB):	$(DEF) $(LIBOBJS)
	implib $(OUTLIB) $(DEF)
	@copy $(OUTLIB) $(LIBD)

# C Quellen
getgi.obj:	getgi.cxx 
	$(CC) $(CFLAGS) -c getgi.cxx

getgip.obj:	getgip.cxx
	$(CC) $(CFLAGS) -c getgip.cxx

getgil.obj:	getgil.cxx
	$(CC) $(CFLAGS) -c getgil.cxx

getgif.obj:	getgif.cxx
	$(CC) $(CFLAGS) -c getgif.cxx

getkan.obj:	getkan.cxx
	$(CC) $(CFLAGS) -c getkan.cxx

fndgi.obj:	fndgi.cxx
	$(CC) $(CFLAGS) -c fndgi.cxx

fndli.obj:	fndli.cxx
	$(CC) $(CFLAGS) -c fndli.cxx

fndpu.obj:	fndpu.cxx
	$(CC) $(CFLAGS) -c fndpu.cxx

fndma.obj:	fndma.cxx
	$(CC) $(CFLAGS) -c fndma.cxx

fndka.obj:	fndka.cxx
	$(CC) $(CFLAGS) -c fndka.cxx

puinfl.obj:	puinfl.cxx
	$(CC) $(CFLAGS) -DFNDTSK -c puinfl.cxx

stinfl.obj:	stinfl.cxx
	$(CC) $(CFLAGS) -c stinfl.cxx

igptnl.obj:	igptnl.cxx
	$(CC) $(CFLAGS) -c igptnl.cxx

girig.obj:	girig.cxx
	$(CC) $(CFLAGS) -c girig.cxx

gifnd.obj:	gifnd.cxx
	$(CC) $(CFLAGS) -c gifnd.cxx

htfunc.obj:	htfunc.cxx
	$(CC) $(CFLAGS) -c htfunc.cxx

qtfunc.obj:	qtfunc.cxx
	$(CC) $(CFLAGS) -c qtfunc.cxx

mfind.obj:	mfind.cxx
	$(CC) -c $(CFLAGS) mfind.cxx

mgettx.obj:	mgettx.cxx
	$(CC) -c $(CFLAGS) mgettx.cxx

mgetkt.obj:	mgetkt.cxx
	$(CC) -c $(CFLAGS) mgetkt.cxx

mgetkr.obj:	mgetkr.cxx
	$(CC) -c $(CFLAGS) mgetkr.cxx

getmi.obj:	getmi.cxx
	$(CCXX)  -c $(CCXXFLAGS) getmi.cxx

getlen.obj:	getlen.cxx
	$(CC) -c $(CFLAGS) getlen.cxx

mgetkm.obj:	mgetkm.cxx
	$(CC) -c $(CFLAGS) mgetkm.cxx

mgetwm.obj:	mgetwm.cxx
	$(CC) -c $(CFLAGS) mgetwm.cxx

mputkm.obj:	mputkm.cxx
	$(CC) -c $(CFLAGS) mputkm.cxx

mputkr.obj:	mputkr.cxx
	$(CC) -c $(CFLAGS) mputkr.cxx

mdelkm.obj:	mdelkm.cxx
	$(CC) -c $(CFLAGS) mdelkm.cxx

mdelkr.obj:	mdelkr.cxx
	$(CC) -c $(CFLAGS) mdelkr.cxx

mitst.obj:	mitst.cxx
	$(CC) -c $(CFLAGS) mitst.cxx

getrig.obj:	getrig.cxx
	$(CC) $(CFLAGS) -c getrig.cxx

getrip.obj:	getrip.cxx
	$(CC) $(CFLAGS) -c getrip.cxx

getril.obj:	getril.cxx
	$(CC) $(CFLAGS) -c getril.cxx

getrif.obj:	getrif.cxx
	$(CC) $(CFLAGS) -c getrif.cxx

htmanr.obj:	htmanr.cxx
	$(CC) $(CFLAGS) -c htmanr.cxx

rigin.obj:	rigin.cxx
	$(CC) $(CFLAGS) -c rigin.cxx

rigkp.obj:	rigkp.cxx
	$(CC) $(CFLAGS) -c rigkp.cxx

getapu.obj:	getapu.cxx
	$(CC) $(CFLAGS) -c getapu.cxx

getri.obj:	getri.cxx
	$(CC) $(CFLAGS) -c getri.cxx

strutil.obj:	strutil.cxx
	$(CC) -c $(CFLAGS) strutil.cxx

isalike.obj:	isalike.cxx
	$(CC) -c $(CFLAGS) isalike.cxx

fndtxt.obj:	fndtxt.cxx
	$(CC) -c $(CFLAGS) fndtxt.cxx

datetime.obj:	datetime.cxx
	$(CC) -c $(CFLAGS) datetime.cxx

puttxtc.obj:	puttxtc.cxx
	$(CC) -c $(CFLAGS) puttxtc.cxx

delmin.obj:	delmin.cxx
	$(CC) -c $(CFLAGS) delmin.cxx

dellink.obj:	dellink.cxx
	$(CC) -c $(CFLAGS) dellink.cxx

drawrect.obj:	drawrect.cxx
	$(CC) -c $(CFLAGSWOCOMP) drawrect.cxx

mdelki.obj:	mdelki.cxx
	$(CC) -c $(CFLAGS) mdelki.cxx

riginfo.obj:	riginfo.cxx riginfo.htp
	$(CCXX) $(CCXXFLAGS) -c riginfo.cxx

relatio.obj:	relatio.cxx relatio.htp
	$(CCXX) $(CCXXFLAGS) -c relatio.cxx

giwindow.obj:	giwindow.cxx giwindow.htp
	$(CCXX) $(CCXXFLAGS) -c giwindow.cxx

db.obj:		db.cxx db.htp
	$(CCXX) $(CCXXFLAGS) -c db.cxx

geo_obj.obj:	geo_obj.cxx geo_obj.htp
	$(CCXX) $(CCXXFLAGS) -c geo_obj.cxx

geo_obj1.obj:	geo_obj1.cxx geo_obj1.htp
	$(CCXX) -c $(CCXXFLAGS) geo_obj1.cxx

geotext.obj:	geotext.cxx geotext.htp
	$(CCXX) -c $(CCXXFLAGS) geotext.cxx

gerade.obj:	gerade.cxx geo_obj1.htp 
	$(CCXX) -c $(CCXXFLAGS) gerade.cxx

pbd.obj:	pbd.cxx pbd.htp
	$(CCXX)  $(CCXXFLAGS) -c pbd.cxx

dllbind.obj:	dllbind.cxx 
	$(CCXX)  $(CCXXFLAGS) -c dllbind.cxx

ctf.obj:	ctf.cxx 
	$(CCXX)  $(CCXXFLAGS) -c ctf.cxx

evlakoef.obj:	evalkoef.cxx 
	$(CCXX)  $(CCXXFLAGS) -c evalkoef.cxx

dbgetgi.obj:	dbgetgi.cxx dbgetgi.htp
	$(CCXX) $(CCXXFLAGS) -c dbgetgi.cxx

hdrentry.obj:	hdrentry.cxx hdrentry.htp
	$(CCXX) $(CCXXFLAGS) -c hdrentry.cxx

attribs.obj:	attribs.cxx attribs.htp
	$(CCXX) $(CCXXFLAGS) -c attribs.cxx

visinfo.obj:	visinfo.cxx 
	$(CCXX) $(CCXXFLAGS) -c visinfo.cxx

oliste.obj:	oliste.cxx oliste.htp
	$(CCXX)  $(CCXXFLAGS) -c oliste.cxx

merkmal.obj:	merkmal.cxx merkmal.htp
	$(CCXX) $(CCXXFLAGS) -c merkmal.cxx

ident.obj:	ident.cxx ident.htp
	$(CCXX) $(CCXXFLAGS) -c ident.cxx

profdll.obj:	profdll.cxx profdll.htp
	$(CCXX)  $(CCXXFLAGS) -c profdll.cxx

delid.obj:	delid.cxx
	$(CC) -c $(CFLAGS) delid.cxx

del.obj:	del.cxx
	$(CC) -c $(CFLAGS) del.cxx

delgi.obj:	delgi.cxx
	$(CC) -c $(CFLAGS) delgi.cxx

delgip.obj:	delgip.cxx
	$(CC) -c $(CFLAGS) delgip.cxx

delgil.obj:	delgil.cxx
	$(CC) -c $(CFLAGS) delgil.cxx

delkan.obj:	delkan.cxx
	$(CC) -c $(CFLAGS) delkan.cxx

delkanf.obj:	delkanf.cxx
	$(CC) -c $(CFLAGS) delkanf.cxx

delgif.obj:	delgif.cxx
	$(CC) -c $(CFLAGS) delgif.cxx

modid.obj:	modid.cxx
	$(CC) -c $(CFLAGS) modid.cxx

palette.obj:	palette.cxx palette.hxx palette.htp
	$(CCXX) -c $(CCXXFLAGS) palette.cxx 

pbdtemp.obj:	pbdtemp.cxx 
	$(CCXX) -c $(CCXXFLAGS) pbdtemp.cxx

pbdids.obj:	pbdids.cxx 
	$(CCXX) -c $(CCXXFLAGS) pbdids.cxx

getmit.obj:	getmit.cxx
	$(CCXX)  -c $(CCXXFLAGS) getmit.cxx

gettext.obj:	gettext.cxx
	$(CC) -c $(CFLAGS) gettext.cxx

gettextl.obj:	gettextl.cxx
	$(CC) -c $(CFLAGS) gettextl.cxx

getlongm.obj:
	$(CC) -c $(CFLAGS) getlongm.cxx

getdblm.obj:
	$(CC) -c $(CFLAGS) getdblm.cxx

getmerkl.obj:
	$(CC) -c $(CFLAGS) getmerkl.cxx

merkinfo.obj:	merkinfo.cxx
	$(CCXX) -c $(CCXXFLAGS) merkinfo.cxx

putrel.obj:	putrel.cxx
	$(CC) -c $(CFLAGS) putrel.cxx

getrel.obj:	getrel.cxx
	$(CCXX) $(CCXXFLAGS) -c getrel.cxx

delrel.obj:	delrel.cxx
	$(CC) -c $(CFLAGS) delrel.cxx

getrcode.obj:	getrcode.hxx getrcode.cxx
	$(CCXX) $(CCXXFLAGS) -c getrcode.cxx

findrel.obj:	findrel.cxx
	$(CC) $(CFLAGS) -c findrel.cxx

puttobj.obj:	puttobj.cxx
	$(CC) $(CFLAGS) -c puttobj.cxx

ovlpobj.obj:	ovlpobj.cxx
	$(CC) $(CFLAGS) -c ovlpobj.cxx

ovllobj.obj:	ovllobj.cxx
	$(CC) $(CFLAGS) -c ovllobj.cxx

ovlfobj.obj:	ovlfobj.cxx
	$(CC) $(CFLAGS) -c ovlfobj.cxx

putpobj.obj:	putpobj.cxx
	$(CC) $(CFLAGS) -c putpobj.cxx

putlobj.obj:	putlobj.cxx
	$(CC) $(CFLAGS) -c putlobj.cxx

putfobj.obj:	putfobj.cxx
	$(CC) $(CFLAGS) -c putfobj.cxx

puttempl.obj:	puttempl.cxx
	$(CC) $(CFLAGS) -c puttempl.cxx

putkobj.obj:	putkobj.cxx
	$(CC) $(CFLAGS) -c putkobj.cxx

putident.obj:	putident.cxx
	$(CC) $(CFLAGS) -c putident.cxx

putpkt.obj:	putpkt.cxx
	$(CC) $(CFLAGS) -c putpkt.cxx

rect.obj:	rect.cxx 
	$(CCXX) $(CCXXFLAGS) -c rect.cxx

delrelko.obj:	delrelko.cxx
	$(CCXX) $(CCXXFLAGS) -c delrelko.cxx

komplex.obj:	komplex.cxx
	$(CCXX) $(CCXXFLAGS) -c komplex.cxx

viserror.obj:	viserror.cxx
	$(CCXX) $(CCXXFLAGS) -c viserror.cxx

registry.obj:	registry.cxx
	$(CCXX) $(CCXXFLAGS) -c registry.cxx

.cxx.obj:
	$(CCXX) $(CCXXFLAGS) -c $*.cxx

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(MAP)
	@del $(DEF)
	@del $(STUB).asm
	@del $(NAME).rcv

formake:	$(DEF) $(STUB).exe $(NAME).rcv

$(DEF):		$(NAME).tpl export.awk $(MAP)
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	awk -f export.awk $(NAME).map >> $(DEF)

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

# Internationalisierung
german:
	@copy tr02ger.rc trias02.rc > nul

russian:
	@copy tr02rus.rc trias02.rc > nul

