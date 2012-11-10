# Makefile für ErweiterungsLibrary

# Speichermodell (ggf. umdefinieren)
M=L

# Generierungsdatum (yymmdd) und Version
DATE=950214
VERSION = 1
RELAESE = 02
BUILD = 003

NAME = xtension

LIBD = c:\triasdev.mvc\lib

DEFS = -DMSWIND -DDLL -D__XT -D__DEXPROCS
DEBUG = 1

!IF $(DEBUG)==1
CXXOPT = -Z7 -Od -G2 -Ob1 -D_DEBUG
!ELSE
CXXOPT = -O2 -G3 -D_NODEBUG
!ENDIF

CCREQ1 =-GD -Zl -Zp1 -Alfw $(CXXOPT) 
CCREQ2 =-Ic:\triasdev.mvc\include -Ic:\cv.mvc\include
CCREQ3 =-D__CV__ -DSTRICT -DMSWIND -DMSCC8 -DDLL -D__XT -D__DEXPROCS
CCREQ4 =
ASMF= /D?PLM=0 /D?WIN=1 /Zi 
CCXXFLAGS = @$(CCDYNREQ)

CCDYNREQ= $(NAME).rsp

LTEMP = lib.tmp
LINK = link
LIB = lib

CC = cl
CCXX = cl

CCXXFLAGS = @$(CCDYNREQ)

OUTLIB = $(NAME).lib

OBJ1 =	textensn.obj opropext.obj multmenu.obj
OBJ2 = 	hdrentrx.obj objcontx.obj dllbind.obj ctfx.obj
OBJ3 =  numeditx.obj helptext.obj drawrect.obj
OBJECTS = $(OBJ1) $(OBJ2) $(OBJ3)

# Alles neu bilden
all:	$(CCDYNREQ) lib

# LIB neu bilden
lib:	$(OUTLIB)

$(CCDYNREQ):
	echo $(CCREQ1)    > 	$(CCDYNREQ)
	echo $(CCREQ2)    >>  	$(CCDYNREQ)
	echo $(CCREQ3)    >>  	$(CCDYNREQ)

$(OUTLIB):	$(OBJECTS) 
	@del $(OUTLIB) > nul
	@echo $(OUTLIB) > $(LTEMP)
	@echo y >> $(LTEMP)
	@echo $(OBJ1) & >> $(LTEMP)
	@echo $(OBJ2) & >> $(LTEMP)
	@echo $(OBJ3) >> $(LTEMP)
	@echo. >> $(LTEMP)
	$(LIB) $(LIBFLAGS) @$(LTEMP)
	@copy $(OUTLIB) $(LIBD) > nul

textensn.obj:	textensn.cxx 

opropext.obj:	opropext.cxx

multmenu.obj:	multmenu.cxx

dllbind.obj:	dllbind.cxx

hdrentrx.obj:	hdrentrx.cxx

ctfx.obj:	ctfx.cxx

objcontx.obj:	objcontx.cxx

visinfo.obj:	visinfo.cxx

helptext.obj:	helptext.cxx

numeditx.obj:	numeditx.cxx

drawrect.obj:	drawrect.cxx

.cxx.obj:
	$(CCXX) $(CCXXFLAGS) -c $*.cxx

