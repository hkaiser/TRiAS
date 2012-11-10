# Genrieren der Versionsinfo's für MSGBLAST.EXT

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE=980922
VERSION = 2
RELEASE = 00
BUILD = 005

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = MsgBlast
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del version.h

formake:	$(DEF) $(NAME).rcv version.h

# Personalisierungsinformation
$(NAME).rcv:	MsgBlstv.tpl msgbls16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E MsgBlstv.tpl tmp
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp > nul
	@del tmp1 > nul

$(DEF):		$(NAME).tpl msgbls16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

version.h:	version.tpl msgbls16.mak
	$(REPLACE) $(VERSION) $(RELEASE) version.tpl version.h
