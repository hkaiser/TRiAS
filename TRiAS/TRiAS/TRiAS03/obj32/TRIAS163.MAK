# Genrieren der Versionsinfo's für TRIAS323.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 041112
VERSION = 3
RELEASE = 30
BUILD = 619			# 300: 9.10.2000, 21:14
					# 400: 7.03.2001, 09:12
					# 500: 2.09.2002, 10:49
					# 600: 7.02.2003, 12:22

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = trias323
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
# CopyrightEinträge Generieren 
new:
	@del obj32\$(NAME).rcv
	@del obj32\trias33d.def
	@del obj32\trias323.def

formake:	obj32\trias323.def obj32\trias33d.def obj32\trias323.rcv 

# Personalisierungsinformation
obj32\trias323.rcv:	obj32\trias33v.tpl obj32\trias163.mak 
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			obj32\trias33v.tpl obj32\trias323.rcv
		
obj32\trias33d.def:	obj32\desc.tpl obj32\trias33d.tpl obj32\trias163.mak 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) obj32\desc.tpl obj32\trias33d.def
	cat obj32\trias33d.tpl >> obj32\trias33d.def

obj32\trias323.def:	obj32\desc.tpl obj32\trias323.tpl obj32\trias163.mak 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) obj32\desc.tpl obj32\trias323.def
	cat obj32\trias323.tpl >> obj32\trias323.def

