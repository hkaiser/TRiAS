s/yyerror("pcyacc internal stack overflow");/yyerror (IDS_SYSERROR);/
s/strcmp/lstrcmp/g
s/yyerror("syntax error");/yyerror (IDS_SYNTAXERR);/
s/fprintf(stderr, "Can\'t open t file: %s\\n", yytfilen);/\
yyerror (IDS_OPENERROR);/g
s/switch (m) {/App :: Exec (ExecWhileEvent); if (pRechStat \&\& pRechStat -> Break () ) return(0);\
switch (m) {/

