# Generieren der DIRIS01-Bibliothek fьr Elementar- und Key-IO- Operationen
# Windows/DLL-Version			last update: 24. November 1989
# MSVC V8.0c (Windows)

# Speichermodell (ggf. umdefinieren)
M=L

# Generierungsdatum (yymmdd) und Version
DBDATE=920727
DBVERSION = 5
DBRELEASE = 00
DBBUILD = 003

DATE=960501
VERSION = 5
RELEASE = 20
BUILD = 042

COPYRIGHT = HK$(DATE)

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

PNAME = "Version fьr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

# SU-Variante
#PNAME = "Версия для Центра Аэрокосмических"
#PADDRESS = "Исследований Земли"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"

#PNAME = "Dr.Eckstein/Dr. Walkow"
#PADDRESS = "Landratsamt Bitterfeld"

LIBD = c:\triasdev.mvc\lib
WINDIR = c:\win31

VERS = dbversio.h
DEFS = -DMSWIND -DDLL -D__XT

DEBUG = 1

!IF $(DEBUG)==1
CXXOPT = -Zi -Od -G2s -Ob1 -D_DEBUG
LINKFLAGS=/CO/F/NOE/MAP:FULL/SE:256/packc/farc/onerror:noexe/align:16
ASMF= /D?PLM=0 /D?WIN=1 /Zi 
!ELSE
CXXOPT = -O2 -G3 -DNDEBUG
LINKFLAGS=/NOE/se:256/packc/farc/onerror:noexe/align:16
ASMF= /D?PLM=0 /D?WIN=1
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -W3 -Alfw -Gx -Gt65500 -Gf $(CXXOPT) 
CCREQ2 =-I..\include -Ie:\cv.mvc\include
CCREQ3 =-D__CV__ -DSTRICT -DMSWIND -DMSCC8 -DDLL -D__XT -D__DEXPROCS
CCREQ4 =-DEXPORT01=__export -DNULLCMP

CCDYNREQ= trias01.rsp

LTEMP = link.tmp
LIBTMP = lib.tmp
LINK = link
LIB = lib
ASM = masm

RC = rc
RCFLAGS = -K $(CCREQ2)
CCXX = cl
CCXXFLAGS = @$(CCDYNREQ) -Yutrias01p.hxx
CCXXPCOMPFLAGS = @$(CCDYNREQ) -Yctrias01p.hxx

LIB1 = e:\cv.mvc\lib16\ c:\msvc\lib\ lstrdwd freestor ldllcew framelib 
LIB2 = ole2 storage toolhelp containr lzexpand oldnames libw
LIBS = $(LIB1) $(LIB2)

CC = cl /nologo

MODEL = -A$(M)
NAME = trias01
STUB = rights

OUTDLL = $(NAME).dll
OUTLIB = $(NAME).lib
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
RIGHTS = $(STUB).exe
REPLACE = ersetz

PRECOMPHDRS = 
PRECOMPRELS = $(PRECOMPHDRS) trias01p.pch
PCOMPOBJ = trias01p.obj

# Abhдngigkeiten --------------------------------------------------------------
DHEADERS = ..\include\dioexter.h ..\include\dbtypes.h 
KHEADERS = ..\include\keyexter.h $(DHEADERS)
HHEADERS = ..\include\htextern.h $(KHEADERS)
QHEADERS = ..\include\qtextern.h $(KHEADERS)

SYSOBJS = 	libmain1.obj wep.obj xceptasm.obj xception.obj strmhelp.obj stghelp.obj

# allgemeine DB-Kernroutinen
DOBJ1 = 	db_io.obj dbclose.obj dbopen.obj seterr.obj dio_init.obj
DOBJ2 =		fdbclose.obj fdbopen.obj inittab.obj pgzero.obj activate.obj
DOBJ3 =		key_io.obj bits.obj getdwnam.obj getdwent.obj zactiv.obj
DOBJ4 =		getpath.obj crypt.obj getdwuid.obj statist.obj version.obj
DOBJ5 =		mycrypt.obj errfkt.obj einvaddr.obj enomem.obj switchkc.obj
DOBJ6 =		reindex.obj newfile.obj eviserr.obj eexterr.obj enfnderr.obj
DOBJECTS = $(DOBJ1) $(DOBJ2) $(DOBJ3) $(DOBJ4) $(DOBJ5) $(DOBJ6)

# Geometriezugriff HexTree
HTOBJ1 =	htprep.obj htsearch.obj htins.obj htsplit.obj htdel.obj
HTOBJ2 =	htshrink.obj cube.obj keyini.obj tlocslt.obj tputinl.obj
HTOBJ3 =	tzapslt.obj htwindow.obj listen.obj
HTOBJECTS = $(HTOBJ1) $(HTOBJ2) $(HTOBJ3)

# Geometriezugriff QuadTree
QTOBJ1 =	qtprep.obj qtsearch.obj qtins.obj qtsplit.obj qtdel.obj
QTOBJ2 =	qtshrink.obj qtwindow.obj quad.obj
QTOBJECTS = $(QTOBJ1) $(QTOBJ2)

# Keyzugriffsroutinen BTree
KOBJ1 =		keyins.obj insert.obj keycat.obj nodexp.obj parent.obj rootsp.obj
KOBJ2 =		nodspl.obj overfl.obj asmbuf.obj nodfil.obj keyloc.obj keyfrst.obj
KOBJ3 =		keylast.obj keyread.obj keynext.obj keyprev.obj keycmp.obj
KOBJ4 =		locate.obj locfrst.obj loclast.obj keydel.obj delete.obj
KOBJ5 =		combin.obj zapslt.obj putinl.obj locslt.obj shrink.obj
KOBJECTS = $(KOBJ1) $(KOBJ2) $(KOBJ3) $(KOBJ4) $(KOBJ5)

# Schnittstellenroutinen fuer ifnd/datver
IOBJ1 =		ngmc.obj ladrc.obj
IOBJECTS = $(IOBJ1) 

# Nutzerroutinen (entsprechend DIRIS01-Dokumentation)
ZOBJ1 =		zkeyfind.obj zkeyfrst.obj zkeylast.obj zkeynext.obj 
ZOBJ2 =		zkeyprev.obj zreadrec.obj zaccess.obj zsetfile.obj
ZOBJ3 =		zwritrec.obj zfillnew.obj zdispose.obj zsetpage.obj
ZOBJ4 =		zkeyread.obj 
ZOBJECTS = $(ZOBJ1) $(ZOBJ2) $(ZOBJ3) $(ZOBJ4)

# F77 Schnittstellenroutinen
FOBJ1 =		zact_f.obj
FOBJ2 =	#	zkread_f.obj zlast_f.obj znew_f.obj znext_f.obj
FOBJ3 =	#	zprev_f.obj zread_f.obj zwrite_f.obj z_find_f.obj
FOBJ4 =		htwind_f.obj qtwind_f.obj
# zclose_f.obj zopen_f.obj zdisp_f.obj zfirst_f.obj 
FOBJECTS = $(FOBJ1) $(FOBJ2) $(FOBJ3) $(FOBJ4)

# Utilities
UOBJ1 =		keyutil.obj nullcmp.obj strnchr.obj flex.obj genback.obj
UOBJ2 =		gethd_f.obj puthd_f.obj delhd_f.obj gethdlen.obj dbinitc.obj
UOBJ3 = 	dbcodb.obj htcont.obj qtcont.obj ztouch.obj zrestor.obj
UOBJECTS =	$(UOBJ1) $(UOBJ2) $(UOBJ3)

DBOBJECTS =	$(HTOBJECTS) $(DOBJECTS) $(QTOBJECTS) $(KOBJECTS) $(IOBJECTS) \
		$(ZOBJECTS) $(UOBJECTS) $(FOBJECTS) $(SYSOBJS)

LIBOBJS = dberrord.obj

# Alles neubilden
all:	$(CCDYNREQ) formake dll lib
	@del *.rsp
	@del $(LTEMP)

$(CCDYNREQ):
	echo $(CCREQ1)    > 	$(CCDYNREQ)
	echo $(CCREQ2)    >>  	$(CCDYNREQ)
	echo $(CCREQ3)    >>  	$(CCDYNREQ)
	echo $(CCREQ4)    >>  	$(CCDYNREQ)


# Nur Bibliothek neubilden
dll:	$(OUTDLL)

trias01p.pch:	$(PRECOMPHDRS) trias01p.cxx trias01p.hxx

trias01p.obj:	trias01p.cxx trias01p.hxx $(PRECOMPHDRS)
	$(CCXX) $(CCXXPCOMPFLAGS) -c trias01p.cxx

$(DBOBJECTS):	$(PRECOMPRELS)

# am Anfang alles loeschen 
rmall:
	del *.obj
#	del version.tmp
#	del dbversio.h
#	del setcrc.exe
	del $(DEF)

$(NAME).res:	$(NAME).rc $(NAME).rcv
	rc -r $(NAME).rc

$(OUTDLL):	$(PCOMPOBJ) $(DBOBJECTS) $(DEF) $(RIGHTS) $(NAME).res
	@echo $(PCOMPOBJ) + > $(LTEMP)
	@echo $(SYSOBJS) + >> $(LTEMP)
	@echo $(DOBJ1) + >> $(LTEMP)
	@echo $(DOBJ2) + >> $(LTEMP)
	@echo $(DOBJ3) + >> $(LTEMP)
	@echo $(DOBJ4) + >> $(LTEMP)
	@echo $(DOBJ5) + >> $(LTEMP)
	@echo $(DOBJ6) + >> $(LTEMP)
	@echo $(KOBJ1) + >> $(LTEMP)
	@echo $(KOBJ2) + >> $(LTEMP)
	@echo $(KOBJ3) + >> $(LTEMP)
	@echo $(KOBJ4) + >> $(LTEMP)
	@echo $(KOBJ5) + >> $(LTEMP)
	@echo $(FOBJ1) + >> $(LTEMP)
	@echo $(FOBJ2) + >> $(LTEMP)
	@echo $(FOBJ3) + >> $(LTEMP)
	@echo $(FOBJ4) + >> $(LTEMP)
	@echo $(QTOBJ1) + >> $(LTEMP)
	@echo $(QTOBJ2) + >> $(LTEMP)
	@echo $(HTOBJ1) + >> $(LTEMP)
	@echo $(HTOBJ2) + >> $(LTEMP)
	@echo $(HTOBJ3) + >> $(LTEMP)
	@echo $(IOBJ1) + >> $(LTEMP)
	@echo $(UOBJ1) + >> $(LTEMP)
	@echo $(UOBJ2) + >> $(LTEMP)
	@echo $(UOBJ3) + >> $(LTEMP)
	@echo $(ZOBJ1) + >> $(LTEMP)
	@echo $(ZOBJ2) + >> $(LTEMP)
	@echo $(ZOBJ3) + >> $(LTEMP)
	@echo $(ZOBJ4) + >> $(LTEMP)
	@echo $(LINKFLAGS) >> $(LTEMP)
	@echo $(OUTDLL) >> $(LTEMP)
	@echo $(MAP) /line/map >> $(LTEMP)
	@echo $(LIB1) + >> $(LTEMP)
	@echo $(LIB2) >> $(LTEMP)
	@echo $(DEF) >> $(LTEMP)
	$(LINK) /nol @$(LTEMP)
	rc $(RCFLAGS) $(NAME).res $(OUTDLL)
	
lib:	$(OUTLIB)

$(OUTLIB):	$(DEF) 	# $(LIBOBJS)
	implib $(OUTLIB) $(DEF)
	@copy $(OUTLIB) $(LIBD)

$(DOBJECTS): $(DHEADERS)
$(KOBJECTS): $(KHEADERS)
$(HTOBJECTS): $(HHEADERS)
$(QTOBJECTS): $(QHEADERS)

dio_init.obj inittab.obj:	$(VERS)

version.tmp:	dbversio.msk 
	$(REPLACE) $(DBVERSION) $(DBRELEASE) $(DBBUILD) @A $(DBDATE) dbversio.msk version.tmp

$(VERS):	version.tmp 
	setcrc < version.tmp > $(VERS)

setcrc.exe:	setcrc.cxx mycrypt.cxx version.tmp
	$(CC) setcrc.cxx mycrypt.cxx /link c:\msvc\lib\ 
	@del mycrypt.obj

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) $(STUB);

.cxx.obj:
	$(CCXX) /nologo -c $(CCXXFLAGS) $*.cxx
	
errfkt.obj:	errfkt.cxx errfkt.hxx

newfile.obj:	newfile.cxx

xception.obj:	xception.cxx

xceptasm.obj:	xceptasm.asm
	ml -c -Zi xceptasm.asm

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(DEF)
	@del $(STUB).asm
	@del $(NAME).rcv

formake:	$(DEF) $(STUB).exe $(NAME).rcv

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	awk -f export.awk trias01.map >> $(DEF)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

# Internationalisierung
german:
	@copy tr01ger.rc trias01.rc > nul

russian:
	@copy tr01rus.rc trias01.rc > nul

