# Generieren der Versionsinfo's für KOMPAKT.EXT

!include $(TRIASINCLUDE)\triasver.Mak

# Generierungsdatum (yymmdd) und Version
DATE=010831
VERSION = 4
RELEASE = 00
BUILD = 44

COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = kompias
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB)

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
#	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEF)
	@del about.src
	@del versio32.h

formake:	$(DEF) $(NAME).rcv about.src versio32.h	# $(STUB).exe 

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

about.src:	defabout.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defabout.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv about.src
	@del tmp.rcv > nul

versio32.h:	versio32.tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

