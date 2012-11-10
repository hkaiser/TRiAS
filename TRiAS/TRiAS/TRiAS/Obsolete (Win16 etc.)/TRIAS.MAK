# Makefile fuer TRIAS (C++ 2.0d2)
# File: MAKEFILE

# TRIAS: %W%	%E%

# CopyrightEintrag
# bei Copyright-Aenderungen 'make new' abarbeiten !
VERSION = 1
RELEASE = 30
BUILD = 133
COPYRIGHT = HK960501

# allgemeine Version
PNAME = "TRiAS\256  ist ein eingetragenes Warenzeichen"
PADDRESS = "der uve GmbH FEZ Potsdam"

#PNAME = "Version f\374r den internen Gebrauch"
#PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

# SU-Variante
#PNAME = "Âåðñèÿ äëÿ Öåíòðà Àýðîêîñìè÷åñêèõ"
#PADDRESS = "Èññëåäîâàíèé Çåìëè"

# Schlitter/Neef
#PNAME = "Version für die BVV Chemie GmbH"
#PADDRESS = ""

#PNAME = "Version für die Entwicklungsträgergesellschaft"
#PADDRESS = "Rummelsburger Bucht"

#PNAME = "Version für das Ministerium für Umwelt,"
#PADDRESS = "Naturschutz und Raumordnung Brandenburg"

#PADDRESS = "internen Gebrauch (uve Potsdam GmbH)"
#PADDRESS = "internen Gebrauch (uve GmbH Herne)"

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"
#PADDRESS = "GBG Berlin"

#PNAME = "Herr Simon"
#PADDRESS = "Treuhand-Liegenschaftsgesellschaft"

#PNAME = "Herrn Bock"
#PADDRESS = "Senat Berlin, Abteilung III"

#PNAME = "Herrn Schiller"
#PADDRESS = "Umweltverantwortlicher des RAW Schöneweide"

#PNAME = "Herrn Langenickel"
#PADDRESS = "EWU Engineering GmbH Berlin"

#PNAME = "Dr. Eckstein/Dr.Walkow"
#PNAME = "Version für das"
#PADDRESS = "Landratsamt Bitterfeld"

DEFS = -DMSWIND -DDLL
DEBUG=1
DUMP=0
DIAGS=0

!IF $(DIAGS)==1
DIAGFLAG=-DDIAGNOSTICS
!ELSE
DIAGFLAG=
!ENDIF
           	
!IF $(DEBUG)==1
CXXOPT = -O2 -G3 -D_DEBUG $(DIAGFLAG)
CXXOPT1 = -G2 -D_DEBUG -U_QC -U_FAST
CXXDEB = -Zi -Od -Ob1 -G2 -Gs -D_DEBUG $(DIAGFLAG) -U_QC -U_FAST
YXXFLAGS= -no_debug -table fast -ns -nl
ASMF= /D?PLM=0 /D?WIN=1 /Zi 
LFLAGS=/NOE/nod/SE:256/packc/align:16/onerror:noexe/packd/MAP:FULL/co
!ELSE
CXXOPT = -O2 -DNDEBUG -G3
CXXDEB = $(CXXOPT) -Zi -U_QC -U_FAST
YXXFLAGS= -no_debug -table fast -ns -nl
ASMF= /D?PLM=0 /D?WIN=1
LFLAGS=/NOE/se:256/packc/align:16/onerror:noexe/packd/nod
!ENDIF

!IF $(DUMP)==1
FPPDEFS = -D_DUMP
!ELSE
FPPDEFS = 
!ENDIF

CCREQ1 =-GA -Zl -Zp1 -AL -I..\include -Ie:\cv.mvc\include -Ie:\yxx20\inc.c8 -I.
CCREQ2 =-D__CV__ -DSTRICT $(DEFS) -W3 -Gx -Gt65500 -Gf
CCREQ3 = $(CXXDEB)
CCREQ4 = $(CXXOPT)
!IF $(DEBUG)==1
CCREQ5 = $(CXXOPT) -Zi
CCREQ6 = -Od -G2 -Gs -D_DEBUG $(DIAGFLAG) -U_QC -U_FAST
#-Ob1
!ELSE
CCREQ5 = $(CXXOPT) -Zi
CCREQ6 = -Od -G2 -Gs -DNDEBUG
!ENDIF
CCREQ7 = $(CXXOPT1)

CCREQDEB = triasdeb.rsp
CCREQOPT = triasopt.rsp
CCREQOPT1 = triasop1.rsp
CCREQSPEC = triasspc.rsp
CCREQOPTDEB = triasodg.rsp

LTMP = trias.lnk
LIBTMP = lib.tmp

LINK = link
LIB = lib
ASM = masm
CC = cl /nologo
CCXX = $(CC)
EMCCXX = $(CC)
RC = rc
REPLACE = ersetz
CVPACK = cvpack
IMPLIB = implib
YXX=yxx
FPP = fpp
AD = autodoc.exe
HC = hc31.exe

RCFLAGS = -K
CCXXFLAGS = @$(CCREQOPT) -Yutriaspre.hxx
CCXXFLAGS1 = @$(CCREQOPT1) -Yutriaspre.hxx
CCXXFLAGSDEB = @$(CCREQDEB) -Yutriaspre.hxx
CCXXFLAGSOPTDEB = @$(CCREQOPTDEB) -Yutriaspre.hxx
CCXXFLAGSSPEC = @$(CCREQSPEC) -Yutriaspre.hxx
CFLAGS = @$(CCREQOPT) -Yutriaspre.hxx
CCXXFLAGSWOHDR = @$(CCREQOPT)

!IF $(DEBUG)==1
#CCXXPCOMPFLAGS = @$(CCREQOPT1) -Yctriaspre.hxx
CCXXPCOMPFLAGS = @$(CCREQDEB) -Yctriaspre.hxx
!ELSE
CCXXPCOMPFLAGS = @$(CCREQDEB) -Yctriaspre.hxx
!ENDIF

LIBS1 = e:\cv.mvc\lib16\ e:\triasdev.mvc\lib\ c:\msvc\lib\ 
LIBS2 = trias03 trias02 trias01 shell toolhelp oldnames 
LIBS3 = ctl3dv2 framelib containr lzexpand lol lstrcw.lib
LIBS4 = ole2 ole2disp storage mmsystem commdlg ver llibcew libw
LIBS  = $(LIBS1) $(LIBS2) $(LIBS3) $(LIBS4)

NAME = trias
STUB = startup

APP = $(NAME)
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
LIB = $(NAME).lib
EXE = $(NAME).exe

RIGHTS = $(STUB).exe
MAKEKEY = makekey

DESTDIR = c:\trias.mvc\trias

# Header, die precompiliert werden --------------------------------------------
PRECOMPHDRS = draw_obj.hxx iris.hxx extmain2.hxx triaspre.hxx
PRECOMPRELS = $(PRECOMPHDRS) triaspre.pch

DIALOGS = 
#	  infodlg.src irisopen.dlg edithead.dlg objinfo.dlg \
#	  merkedit.dlg identsel.dlg coords.dlg mkrech.dlg \
#	  coords.dlg nomenkl.dlg prntabrt.dlg schrank.dlg \
#	  prntsel.dlg newid.dlg palwind.dlg visparam.dlg \
#	  objtype.dlg edittext.dlg masstab.dlg ausschn.dlg \
#	  expstat.dlg priority.dlg exptrans.dlg prntlayt.dlg \
#	  objprop.dlg

ICONS = iris.ico
CURSORS =
BITMAP1 = marker1.bmp marker2.bmp marker3.bmp marker4.bmp marker5.bmp 
BITMAP2 = marker6.bmp marker7.bmp marker8.bmp marker9.bmp marker10.bmp
BITMAP3 = marker11.bmp marker12.bmp arrow.bmp lupe.bmp schere.bmp stift.bmp
BITMAP4 = marker13.bmp logo.bmp info.bmp lineal.bmp
BITMAPS = $(BITMAP1) $(BITMAP2) $(BITMAP3) $(BITMAP4)

RESOURCES = $(ICONS) $(CURSORS) $(BITMAPS) $(DIALOGS)

# Objektmodule
OBJPRE = triaspre.obj
OBJ1 = irismain.obj irisopen.obj irisevts.obj prlayout.obj
OBJ2 = draw_obj.obj transfrm.obj edithead.obj cextreg.obj
OBJ3 = dbogetgi.obj newid.obj selident.obj modident.obj
OBJ4 = profile.obj legend.obj sights.obj pntmasks.obj
OBJ5 = pwdialog.obj gaugeo.obj menuitem.obj dboarray.obj
OBJ6 = mkrech.obj coords.obj nomenkl.obj legdinfo.obj
OBJ7 = feature.obj colorbox.obj oridents.obj legutils.obj
OBJ8 = tools.obj objekte.obj merkedit.obj rechres.obj
OBJ9 = prntabrt.obj printer.obj extfcns.obj license.obj
OBJ10 = export.obj expdlg.obj schrank.obj bildobj.obj
OBJ11 = drw_obj1.obj clipbord.obj impdlg.obj shiftovw.obj
#import.obj
OBJ12 = irisutil.obj objmenu.obj txtsrch.obj overview.obj
OBJ13 = identsel.obj dbobjekt.obj visparam.obj signon.obj
OBJ14 = palwind.obj ppalwind.obj lpalwind.obj renderdb.obj
OBJ15 = apalwind.obj palrect.obj dcolor.obj bmpbox.obj
OBJ16 = objtype.obj schrift.obj edittext.obj rgb_hsb.obj
OBJ17 = shift.obj masstab.obj textmenu.obj enumfnam.obj
OBJ18 = extmain2.obj ausschn.obj expstat2.obj ienumstr.obj
OBJ19 = priority.obj exptrans.obj prntlayt.obj resource.obj
OBJ20 = extmmsg.obj extload.obj objowndr.obj strfcns.obj
OBJ21 = relobj.obj extqnfy.obj objmenu1.obj bakkey.obj
OBJ22 = olistem.obj targetfi.obj ldroptgt.obj ldropsrc.obj	# dberrord.obj
OBJ23 = minitpbd.obj objprop.obj opendb.obj dbd.obj
OBJ24 = regtrias.obj legwind.obj justify.obj saveopt.obj
OBJ25 = prntprof.obj ienumonr.obj enumobj.obj delviews.obj
OBJ26 = legmerkm.obj legmerkl.obj legmerky.obj legtxted.obj
OBJ27 = viewtree.obj selnview.obj strings.obj

OBJECTS = $(OBJ1) $(OBJ12) $(OBJ13) $(OBJ11) \
	  $(OBJ10) $(OBJ8) $(OBJ26) \
	  $(OBJ4) $(OBJ2) $(OBJ3) $(OBJ4) \
	  $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ14) \
	  $(OBJ15) $(OBJ9) $(OBJ16) $(OBJ17) \
	  $(OBJ18) $(OBJ19) $(OBJ20) $(OBJ21) \
	  $(OBJ22) $(OBJ23) $(OBJ24) $(OBJ25) \
	  $(OBJ26) $(OBJ27)


# Generieren der WINDOW's - Anwendung
all:	$(CCREQOPT) $(CCREQOPT1) $(CCREQDEB) $(CCREQOPTDEB) $(CCREQSPEC) formake $(EXE) $(LIB)

$(CCREQOPT):	makefile
	echo $(CCREQ1) > $(CCREQOPT)
	echo $(CCREQ2) >> $(CCREQOPT)
	echo $(CCREQ4) >> $(CCREQOPT)

$(CCREQOPT1):	makefile
	echo $(CCREQ1) > $(CCREQOPT1)
	echo $(CCREQ2) >> $(CCREQOPT1)
	echo $(CCREQ7) >> $(CCREQOPT1)

$(CCREQDEB):	makefile
	echo $(CCREQ1) > $(CCREQDEB)
	echo $(CCREQ2) >> $(CCREQDEB)
	echo $(CCREQ3) >> $(CCREQDEB)

$(CCREQOPTDEB):	makefile
	echo $(CCREQ1) > $(CCREQOPTDEB)
	echo $(CCREQ2) >> $(CCREQOPTDEB)
	echo $(CCREQ5) >> $(CCREQOPTDEB)

$(CCREQSPEC):	makefile
	echo $(CCREQ1) > $(CCREQSPEC)
	echo $(CCREQ2) >> $(CCREQSPEC)
	echo $(CCREQ6) >> $(CCREQSPEC)

triaspre.pch triaspre.obj:	triaspre.cxx $(PRECOMPHDRS)
	$(CCXX) $(CCXXPCOMPFLAGS) -c triaspre.cxx

irismain.obj:	irismain.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c irismain.cxx

irisevts.obj:	irisevts.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c irisevts.cxx

irisopen.obj:	irisopen.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGSDEB) -c irisopen.cxx

opendb.obj:	opendb.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c  opendb.cxx

irisutil.obj:	irisutil.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c irisutil.cxx

edithead.obj:	edithead.cxx $(PRECOMPRELS)
	$(CCXX) -c $(CCXXFLAGS) edithead.cxx

hdrentry.obj:	hdrentry.cxx $(PRECOMPRELS)
	$(CCXX) -c $(CCXXFLAGS) hdrentry.cxx

dbogetgi.obj:	dbogetgi.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c  dbogetgi.cxx

draw_obj.obj:	draw_obj.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS1) -c draw_obj.cxx

drw_obj1.obj:	drw_obj1.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c drw_obj1.cxx

dbobjekt.obj:	dbobjekt.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGSDEB) -c dbobjekt.cxx

transfrm.obj:	transfrm.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c  transfrm.cxx

tools.obj:	tools.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c tools.cxx

objekte.obj:	objekte.cxx $(PRECOMPRELS) merkedit.hxx
	$(CCXX) $(CCXXFLAGS) -c objekte.cxx 

merkedit.obj:	merkedit.cxx $(PRECOMPRELS) merkedit.hxx 
	$(CCXX) $(CCXXFLAGS) -c merkedit.cxx

identsel.obj:	identsel.cxx identsel.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c identsel.cxx

objmenu.obj:	objmenu.cxx $(PRECOMPRELS) merkedit.hxx
	$(CCXX) $(CCXXFLAGS) -c objmenu.cxx

objmenu1.obj:	objmenu1.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c objmenu1.cxx

profile.obj:	profile.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c profile.cxx

pwdialog.obj:	pwdialog.cxx $(PRECOMPRELS) pwdialog.hxx 
	$(CCXX) $(CCXXFLAGS) -c pwdialog.cxx

sights.obj:	sights.cxx identsel.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c sights.cxx

txtsrch.obj:	textsrch.hxx $(PRECOMPRELS) txtsrch.cxx 
	$(CCXX) $(CCXXFLAGS) -c txtsrch.cxx

mkrech.obj:	mkrech.hxx $(PRECOMPRELS) mkrech.cxx 
	$(CCXX) $(CCXXFLAGS) -c mkrech.cxx

coords.obj:	coords.hxx $(PRECOMPRELS) coords.cxx 
	$(CCXX) $(CCXXFLAGS) -c coords.cxx

nomenkl.obj:	nomenkl.hxx $(PRECOMPRELS) nomenkl.cxx 
	$(CCXX) $(CCXXFLAGS) -c nomenkl.cxx

gaugeo.obj:	gaugeo.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c gaugeo.cxx

geogau.obj:	geogau.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c geogau.cxx

olistem.obj:	olistem.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c olistem.cxx

printer.obj:	printer.cxx prntabrt.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c printer.cxx

prntabrt.obj:	prntabrt.cxx $(PRECOMPRELS) prntabrt.hxx 
	$(CCXX) $(CCXXFLAGS) -c prntabrt.cxx

prntlayt.obj:	prntlayt.cxx $(PRECOMPRELS) prntlayt.hxx
	$(CCXX) $(CCXXFLAGS) -c prntlayt.cxx

schrank.obj:	schrank.hxx schrank.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c schrank.cxx

export.obj:	export.cxx export.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c export.cxx

expdlg.obj:	expdlg.cxx expdlg.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c expdlg.cxx

clipbord.obj:	clipbord.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c clipbord.cxx

newid.obj:	newid.hxx newid.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c newid.cxx

palwind.obj:	palwind.cxx palwind.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c palwind.cxx

ppalwind.obj:	ppalwind.cxx palwind.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c ppalwind.cxx

lpalwind.obj:	lpalwind.cxx palwind.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c lpalwind.cxx

apalwind.obj:	apalwind.cxx palwind.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c apalwind.cxx

palrect.obj:	palrect.cxx palrect.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c palrect.cxx

dcolor.obj:	dcolor.cxx dcolor.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c dcolor.cxx

colorbox.obj:	colorbox.cxx colorbox.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c colorbox.cxx

feature.obj:	feature.cxx feature.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c feature.cxx

visparam.obj:	visparam.cxx visparam.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c visparam.cxx

objtype.obj:	objtype.cxx objtype.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c objtype.cxx

schrift.obj:	schrift.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c schrift.cxx

edittext.obj:	edittext.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c edittext.cxx

shift.obj:	shift.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c shift.cxx

masstab.obj:	masstab.cxx masstab.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c masstab.cxx

textmenu.obj:	textmenu.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c textmenu.cxx

extmain2.obj:	extmain2.cxx extfcns.hxx extfcns.tab $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c extmain2.cxx

extmmsg.obj:	extmmsg.cxx extfcns.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c extmmsg.cxx

extload.obj:	extload.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c extload.cxx

ausschn.obj:	ausschn.cxx $(PRECOMPRELS) ausschn.hxx
	$(CCXX)  $(CCXXFLAGS) -c ausschn.cxx

expstat2.obj:	expstat2.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c expstat2.cxx

exptrans.obj:	exptrans.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c exptrans.cxx

priority.obj:	$(PRECOMPRELS) priority.hxx priority.cxx
	$(CCXX)  $(CCXXFLAGS) -c priority.cxx

objowndr.obj:	objowndr.cxx objowndr.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c objowndr.cxx

relobj.obj:	relobj.cxx relobj.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c relobj.cxx

extqnfy.obj:	extqnfy.hxx extqnfy.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c extqnfy.cxx

menuitem.obj:	menuitem.hxx menuitem.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c menuitem.cxx

minitpbd.obj:	minitpbd.cxx minitpbd.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c minitpbd.cxx

objprop.obj:	objprop.cxx objprop.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c objprop.cxx

regtrias.obj:	regtrias.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c regtrias.cxx

justify.obj:	justify.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c justify.cxx

prntprof.obj:	prntprof.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c prntprof.cxx

enumobj.obj:	enumobj.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c enumobj.cxx

ienumonr.obj:	ienumonr.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c ienumonr.cxx

delviews.obj:	delviews.cxx delviews.hxx  $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c delviews.cxx

saveopt.obj:	saveopt.cxx saveopt.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c saveopt.cxx

# DBDVerwaltung ---------------------------------------------------------------
dbd.obj:	dbd.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c dbd.cxx

targetfi.obj:	targetfi.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c targetfi.cxx

bakkey.obj:	bakkey.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c bakkey.cxx

strfcns.obj:	strfcns.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c strfcns.cxx

resource.obj:	resource.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c resource.cxx

import.obj:	import.cxx import.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c import.cxx

impdlg.obj:	impdlg.cxx impdlg.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c impdlg.cxx

ienumstr.obj:	ienumstr.cxx ienumstr.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c ienumstr.cxx

enumfnam.obj:	enumfnam.cxx enumfnam.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c enumfnam.cxx

rgb_hsb.obj:	rgb_hsb.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c rgb_hsb.cxx

bmpbox.obj:	bmpbox.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c bmpbox.cxx

renderdb.obj:	renderdb.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c renderdb.cxx

signon.obj:	signon.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c signon.cxx

overview.obj:	overview.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c overview.cxx

shiftovw.obj:	shiftovw.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c shiftovw.cxx

bildobj.obj:	bildobj.cxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS1) -c bildobj.cxx

extfcns.obj:	extfcns.cxx extfcns.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c extfcns.cxx

selident.obj:	selident.cxx selident.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c selident.cxx

modident.obj:	modident.cxx modident.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c modident.cxx

rechres.obj:	rechres.cxx rechres.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c rechres.cxx

oridents.obj:	oridents.cxx oridents.hxx oridents.inl $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c oridents.cxx

dboarray.obj:	dboarray.cxx dboarray.hxx $(PRECOMPRELS)
	$(CCXX)  $(CCXXFLAGS) -c dboarray.cxx

pntmasks.obj:	pntmasks.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c pntmasks.cxx

cextreg.obj:	cextreg.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c cextreg.cxx

# LegendenEintragsBeschreibung ------------------------------------------------
legmerkl.hxx legmerky.hxx legmerkl.cxx legmerky.cxx:	legmerkm.yxx
	@-fpp -P $(FPPDEFS) legmerkm.yxx > legmerkm.ypp
	$(YXX) $(YXXFLAGS) legmerkm.ypp
	@del legmerkm.ypp > nul
	sed -e s/yy_export//g legmerkl.hxx > tmp
	@del legmerkl.hxx
	@ren tmp legmerkl.hxx
	sed -e s/yy_export//g legmerky.hxx > tmp
	@del legmerky.hxx
	@ren tmp legmerky.hxx

legmerky.obj:	legmerky.cxx legmerky.hxx
	$(CCXX) $(CCXXFLAGSWOHDR) -c legmerky.cxx
	
legmerkl.obj:	legmerkl.cxx legmerkl.hxx
	$(CCXX) $(CCXXFLAGSWOHDR) -c legmerkl.cxx

legmerkm.obj:	legmerkm.cxx legmerkl.hxx legmerky.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legmerkm.cxx

legend.obj:	legend.cxx legende.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legend.cxx

legutils.obj:	legutils.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legutils.cxx
	
legdinfo.obj:	legdinfo.hxx legdinfo.inl legdinfo.cxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legdinfo.cxx
	
legwind.obj:	legwind.cxx legwind.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legwind.cxx

legtxted.obj:	legtxted.cxx legtxted.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c legtxted.cxx

ldroptgt.obj:	ldroptgt.cxx ldroptgt.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c ldroptgt.cxx

ldropsrc.obj:	ldropsrc.cxx ldropsrc.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c ldropsrc.cxx

license.obj:	license.cxx license.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c license.cxx

prlayout.obj:	prlayout.cxx prlayout.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c prlayout.cxx

viewtree.obj:	viewtree.cxx viewtree.inl viewtree.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c viewtree.cxx

selnview.obj:	selnview.cxx selnview.hxx $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c selnview.cxx

strings.obj:	strings.cxx strings.h $(PRECOMPRELS)
	$(CCXX) $(CCXXFLAGS) -c strings.cxx

# Ressourcendatei(en) ---------------------------------------------------------
$(APP).res:	$(APP).rc $(APP).rcv $(RESOURCES) iris.h pkeycode.h copystr.rc
	rc -r -I..\include $(APP).rc

# Linkerlauf ------------------------------------------------------------------
$(EXE):		$(OBJPRE) $(OBJECTS) $(DEF) $(APP).res $(STUB).exe $(LTMP)
	$(LINK) /nol @$(LTMP)
	rc $(RCFLAGS) $(APP).res
#	@copy $(APP).exe $(DESTDIR)
	@del *.rsp
	@del $(LTMP)
	
$(LIB):		$(DEF)
	$(IMPLIB) $(LIB) $(DEF)

# Aufbau der Linker-Kommandodatei, wenn 'makefile' geaendert wurde ------------
$(LTMP):	makefile
	@echo $(OBJPRE) + > $(LTMP)
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
	@echo $(LFLAGS) >> $(LTMP)
	@echo $(EXE) >> $(LTMP)
	@echo $(MAP) /map /line >> $(LTMP)
	@echo $(LIBS1) + >> $(LTMP)
	@echo $(LIBS2) + >> $(LTMP)
	@echo $(LIBS3) + >> $(LTMP)
	@echo $(LIBS4) >> $(LTMP)
	@echo $(DEF) >> $(LTMP)

# CopyrightEintraege Generieren -----------------------------------------------
$(DEF):		$(APP).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(APP).tpl $(DEF)

infodlg.src:	infodlg.dlg 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) infodlg.dlg infodlg.src

signon1.src:	signon1.dlg 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B signon1.dlg tmp.src
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.src signon1.src
	@del tmp.src > nul

$(STUB).c:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).c

$(STUB).exe:	$(STUB).c exec.obj spawn.obj
	$(CC) -c $(STUB).c 
	@echo $(STUB).obj exec.obj spawn.obj > $(STUB).lnk
	@echo $(STUB).exe >> $(STUB).lnk
	@echo nul >> $(STUB).lnk
	@echo c:\msvc\lib\ ; >> $(STUB).lnk
	$(LINK) /nol @$(STUB).lnk

# Personalisierungsinformation ------------------------------------------------
#$(APP).rc:	$(APP)tpl.rc
#	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(APP)tpl.rc tmp.rc
#	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rc $(APP).rc
#	@del tmp.rc > nul

$(APP).rcv:	$(APP)rcv.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(APP)rcv.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(APP).rcv
	@del tmp.rcv > nul

pkeycode.h:	$(MAKEKEY).exe 
	$(MAKEKEY) $(PNAME) $(PADDRESS) > pkeycode.h

$(MAKEKEY).exe:	$(MAKEKEY).c mycrypt.c
	cl $(MAKEKEY).c mycrypt.c

copystr.rc:	copystrt.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B copystrt.rc tmp.rc
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rc copystr.rc
	@del tmp.rc > nul

# bei Copyright-Aenderungen 'make new' abarbeiten ! ---------------------------
new:	remove

remove:
	@del $(DEF)
	@del infodlg.src
	@del $(STUB).c
#	@del $(APP).rc
	@del $(APP).rcv
	@del pkeycode.h
	@del signon1.src
	@del copystr.rc

# Abhängigkeiten für Umgeleitete Dateien (für make)
formake:	$(DEF) infodlg.src $(STUB).c $(APP).rcv \
		pkeycode.h signon1.src copystr.rc
#		$(APP).rc

# Lokalisierung ---------------------------------------------------------------
german:
	@copy triasger.rc trias.rc > nul
	@copy infoger.dlg infodlg.dlg > nul
	@copy sign1ger.dlg signon1.dlg > nul

russian:
	@copy triasrus.rc trias.rc > nul
	@copy inforus.dlg infodlg.dlg > nul
	@copy sign1rus.dlg signon1.dlg > nul

# Dokumentaion generieren -----------------------------------------------------
document:	cleandoc copydoc triasdoc.log triasdoc.rtf triashlp.hlp
	@cd ..

cleandoc:
	@del .\triasdoc\triasdoc.rtf > nul
	@del .\triasdoc\triasdoc.log > nul
	@del .\triasdoc\triashlp.rtf > nul
	@del .\triasdoc\triashlp.hlp > nul
	@del .\triasdoc\triashlp.ph  > nul

copydoc:
	@copy ..\include\xtension.h .\triasdoc > nul
	@copy ..\include\xtensnx.h .\triasdoc > nul
	@copy ..\include\xtensnxx.h .\triasdoc > nul
	@copy ..\include\xtensnd.h .\triasdoc > nul
	@copy ..\include\xtensnn.h .\triasdoc > nul
	@copy ..\xtension\ole2auto.mfc\triastlb.odl .\triasdoc\triastlb.cxx > nul
	@copy extfcns.cxx .\triasdoc > nul
	@cd .\triasdoc	
	
triasdoc.log:	
	$(AD) /rd /ftriasdoc.fmt /ltriasdoc.log /n *.h *.cxx

triasdoc.rtf:	triasdoc.log
	$(AD) /rd /ftriasdoc.fmt /ctriasdoc.log /otriasdoc.rtf *.h *.cxx

triashlp.hlp:	triasdoc.log
	$(AD) /rh /ftriasdoc.fmt /ctriasdoc.log /otriashlp.rtf *.h *.cxx
	$(HC) triashlp
	@echo .
