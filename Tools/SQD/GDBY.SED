/^#line/ 	d
/yylval/ 	s/yylval/(*pyylval)/g
/yyval/  	s/yyval/(*pyyval)/g
/# define YYABORT return(1)/ {
a\
#ifdef YYIGNORE\
# define yyignore *(yypi+1) = 1\
#endif
}
/YYSTYPE \*yyv; \/\* where the values are stored \*\// {
a\
#ifdef YYIGNORE\
char yyi[YYMAXDEPTH+1] = { 0 };\
#endif
}
/	register short \*yyxi;/ {
a\
#ifdef YYIGNORE\
\	register char \*yypi;\
#endif
}
/	yypv= &yyv\[-1\];/ {
a\
#ifdef YYIGNORE\
\	yypi= &yyi[0];\
#endif
}
/		++yypv;/ {
i\
#ifdef YYIGNORE\
\		++yypi;\
\		*(yypi+1) = *yypi;\
#endif
}
/		yym=yyn;/ {
i\
#ifdef YYIGNORE\
\		yypi -= yyr2[yyn];\
\		*(yypi+1) = *yypi;\
#endif
}
/			   --yypv;/ {
a\
#ifdef YYIGNORE\
\			   --yypi;\
#endif
}
/		switch(yym){/ {
i\
\
\//		pCurrApp -> Exec (ExecWhileEvent);\
#ifdef YYIGNORE\
\	if(!*yypi)\
#endif
}
/ = yypv\[1\];/	d
/		goto yystack;  \/\* stack new state and value \*\// {
i\
\		(*pyyval) = yypv[1];
}
