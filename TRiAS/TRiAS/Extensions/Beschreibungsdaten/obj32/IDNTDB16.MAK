# Generieren der Versionsinfo's für IDNTDB32.DLL

!include $(TRIASINCLUDE)\triasver.mak

# Generierungsdatum (yymmdd) und Version
DATE = 040905
VERSION = 4
RELEASE = 30
BUILD = 119		# 4.30.100, 9.01.2001, 11:12

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = idntdb32
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
	@del versio32.h

formake:	$(DEF) $(NAME).rcv defabout.src versio32.h

# Personalisierungsinformation
obj32\$(NAME).rcv:	obj32\idntdb3v.tpl obj32\idntdb16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
			obj32\idntdb3v.tpl obj32\$(NAME).rcv

obj32\$(DEF):		obj32\$(NAME).tpl obj32\idntdb16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			obj32\$(NAME).tpl obj32\$(DEF)

obj32\versio32.h:	obj32\versio32.tpl obj32\idntdb16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
			obj32\versio32.tpl obj32\versio32.h

