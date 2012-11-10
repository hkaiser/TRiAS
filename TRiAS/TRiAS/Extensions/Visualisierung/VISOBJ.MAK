# makefile fr VisObj Parser- und Lexer- Quellen

.SUFFIXES:
.SUFFIXES: .y .cxx .c .asm .obj .exe .dll .ext

YACC = yacc
LEX = lex

YACCFLAGS = -d
LEXFLAGS = 

all:	yaccidl yaccobj

yaccidl:	visidlyp.cxx visidllp.cxx

yaccobj:	visobjyp.cxx visobjlp.cxx

visobjyp.cxx:	visobjy.y visobjy.par visobjy.scr
	@-mkdir c:\lib > nul
	@copy visobjy.par c:\lib\yacc.par > nul
	$(YACC) $(YACCFLAGS) visobjy.y
	if exist yvisobj.h @del yvisobj.h > nul
	@ren ytab.h yvisobj.h > nul
	c:\cygnus\bin\sed.exe -f visobjy.scr ytab.c > visobjy.cxx
	@del ytab.c > nul

visobjlp.cxx:	visobjl.lx visobjl.scr
	$(LEX) $(LEXFLAGS) visobjl.lx
	c:\cygnus\bin\sed.exe -f visobjl.scr lexyy.c > visobjl.cxx
	@del lexyy.c > nul

visidlyp.cxx:	visidly.y visidly.par visidly.scr
	@-mkdir c:\lib > nul
	@copy visidly.par c:\lib\yacc.par > nul
	$(YACC) $(YACCFLAGS) visidly.y
	if exist yvisidl.h @del yvisidl.h > nul
	@ren ytab.h yvisidl.h > nul
	c:\cygnus\bin\sed.exe -f visidly.scr ytab.c > visidly.cxx
	@del ytab.c > nul

visidllp.cxx:	visidll.lx visidll.scr
	$(LEX) $(LEXFLAGS) visidll.lx
	c:\cygnus\bin\sed.exe -f visidll.scr lexyy.c > visidll.cxx
	@del lexyy.c > nul
