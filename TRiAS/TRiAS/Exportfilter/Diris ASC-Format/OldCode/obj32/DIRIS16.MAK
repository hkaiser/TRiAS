# Genrieren der Versionsinfo's f�r DIRIS32.FLT

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE=971121
VERSION = 2
RELEASE = 10
BUILD = 011

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = diris32
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
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEF)

formake:	$(NAME).rcv $(DEF)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

$(DEF):		$(NAME).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

# Personalisierungsinformation
$(NAME).rcv:	diris32v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D diris32v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv diris32.rcv
	@del tmp.rcv > nul

