# Generieren der Versionsinfo's für GEOSTAT.DLL

!include $(TRIASINCLUDE)\triasver.Mak

# Generierungsdatum (yymmdd) und Version

DATE= 010207
VERSION = 4
RELEASE = 00
BUILD = 010


COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

#PNAME = "Version f\xfcr den internen Gebrauch"
#PADDRESS = "Fernerkundungszentrum Potsdam GmbH"

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = stat32
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del about.src
	@del versio32.h

formake:	$(DEF) $(NAME).rcv about.src versio32.h

# Personalisierungsinformation
$(NAME).rcv:	stat32v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D stat32v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv $(NAME).rcv
#	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

about.src:	about.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B about.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv about.src
	@del tmp.rcv > nul

versio32.h:		versio32.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

