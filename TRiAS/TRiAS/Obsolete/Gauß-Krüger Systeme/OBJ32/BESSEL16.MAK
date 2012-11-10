# Genrieren der Versionsinfo's fЃr KRASSGK.CTF/32

# Generierungsdatum (yymmdd) und Version
DATE=970807
VERSION = 3
RELEASE = 10
BUILD = 019

COPYRIGHT = HK$(DATE)

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

# SU-Variante
#PNAME = "Версия для Центра Аэрокосмических"
#PADDRESS = "Исследований Земли"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"

#PNAME = "Dr.Eckstein/Dr. Walkow"
#PADDRESS = "Landratsamt Bitterfeld"

STUB = rightsbe
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = besselgk
DEF = $(NAME).def

STUBKR = rightskr
RIGHTSKR = $(STUBKR).exe
NAMEKR = krassgk
DEFKR = $(NAMEKR).def

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

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(DEF) > nul
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEFKR) > nul
	@del $(STUBKR).asm
	@del $(NAMEKR).rcv

formake:	$(DEF) $(STUB).exe $(NAME).rcv \
		$(DEFKR) $(STUBKR).exe $(NAMEKR).rcv

$(DEF):		$(NAME).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

$(DEFKR):	$(NAMEKR).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAMEKR).tpl $(DEFKR)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

$(STUBKR).asm:	$(STUBKR).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUBKR).tpl $(STUBKR).asm

# Personalisierungsinformation
$(NAME).rcv:	besselgv.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B besselgv.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(NAMEKR).rcv:	krassgkv.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B krassgkv.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAMEKR).rcv
	@del tmp.rcv > nul

