# Genrieren der Versionsinfo's fЃr DEFAULT.CTF/32

# Generierungsdatum (yymmdd) und Version
DATE=970806
VERSION = 3
RELEASE = 10
BUILD = 010

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

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = default
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
	@del $(DEF) > nul
	@del $(STUB).asm
	@del $(NAME).rcv

formake:	$(DEF) $(STUB).exe default.rcv

$(DEF):		$(NAME).tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
default.rcv:	defaultv.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defaultv.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv default.rcv
	@del tmp.rcv > nul

