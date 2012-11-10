# Genrieren der Versionsinfo's fЃr BEGEOD.CTF/32

!include <triasver207.mak>

# Generierungsdatum (yymmdd) und Version
DATE=980630
VERSION = 4
RELEASE = 10
BUILD = 021

COPYRIGHT = HK$(DATE)

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

PNAME = $(TRIAS_NAME)
PADDRESS = $(TRIAS_PADDRESS)

# SU-Variante
#PNAME = "Версия для Центра Аэрокосмических"
#PADDRESS = "Исследований Земли"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"

#PNAME = "Dr.Eckstein/Dr. Walkow"
#PADDRESS = "Landratsamt Bitterfeld"

REPLACE = ersetz

STUB = rights
RIGHTS = $(STUB).exe
NAME = begeod
DEF = $(NAME).def

STUBKR = rightskr
RIGHTSKR = $(STUBKR).exe
NAMEKR = krgeod
DEFKR = $(NAMEKR).def

STUBETRS = rights89
RIGHTSETRS = $(STUBETRS).exe
NAMEETRS = etrsgeod
DEFETRS = $(NAMEETRS).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

$(STUBKR).exe:	$(STUBKR).asm
	$(ASM) $(ASMF) $(STUBKR) 
	$(LINK) /NOLOGO /KNOWEAS $(STUBKR);

$(STUBETRS).exe:	$(STUBETRS).asm
	$(ASM) $(ASMF) $(STUBETRS) 
	$(LINK) /NOLOGO /KNOWEAS $(STUBETRS);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(DEF) > nul
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEFKR) > nul
	@del $(STUBKR).asm
	@del $(NAMEKR).rcv
	@del $(DEFETRS) > nul
	@del $(STUBETRS).asm
	@del $(NAMEETRS).rcv

formake:	$(DEF) $(DEFKR) $(DEFETRS) \
		$(STUB).exe $(STUBKR).exe $(STUBETRS).exe \
		$(NAME).rcv $(NAMEKR).rcv $(NAMEETRS).rcv

$(DEF):		$(NAME).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

$(DEFKR):		$(NAMEKR).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAMEKR).tpl $(DEFKR)

$(DEFETRS):		$(NAMEETRS).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAMEETRS).tpl $(DEFETRS)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

$(STUBKR).asm:	$(STUBKR).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUBKR).tpl $(STUBKR).asm

$(STUBETRS).asm:	$(STUBETRS).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUBETRS).tpl $(STUBETRS).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(NAMEKR).rcv:	$(NAMEKR)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAMEKR)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAMEKR).rcv
	@del tmp.rcv > nul

$(NAMEETRS).rcv:	etrsgeov.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B etrsgeov.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAMEETRS).rcv
	@del tmp.rcv > nul

