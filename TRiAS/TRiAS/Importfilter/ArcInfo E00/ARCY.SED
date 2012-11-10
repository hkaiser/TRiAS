s/yyerror("pcyacc internal stack overflow");/DEX_Error(RC_ArcTriasYacc,EC_SYSERROR);/
s/strcmp/lstrcmp/g
s/yyerror("syntax error");/DEX_Error(RC_ArcTriasYacc,EC_SYNTAX);/
s/fprintf(stderr, "Can\'t open t file: %s\\n", yytfilen);/\
DEX_Error(RC_ArcTriasYacc,EC_SYSERROR);/g
s/switch (m) {/if (pRechStat -> Break () ) return(0);\
switch (m) {/
