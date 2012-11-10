# Generieren der Versionsinfo's für MMSALAYER.DLL

!include $(TRIASINCLUDE)\triasver.Mak

# Generierungsdatum (yymmdd) und Version
DATE=001114
VERSION = 1
RELEASE = 00
BUILD = 001

COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = MMSALAY
RES = SALAYER
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
	@del $(STUB).asm
	@del $(RES).rcv
	@del $(DEF)
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(RES).rcv versio32.h

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(RES).rcv:	$(RES).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(RES).tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv $(RES).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

