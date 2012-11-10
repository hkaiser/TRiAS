# Generieren der Versionsinfo's fЃr OBJCLP32.DLL

# Generierungsdatum (yymmdd) und Version
DATE=970121
VERSION = 3
RELEASE = 10
BUILD = 007

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
NAME = objclp32
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
	@del defabout.src
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv defabout.src versio32.h

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	objclpv.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B objclpv.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

defabout.src:	defabout.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defabout.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv defabout.src
	@del tmp.rcv > nul

versio32.h:     version.tpl
        $(REPLACE) $(VERSION) $(RELEASE) version.tpl versio32.h
