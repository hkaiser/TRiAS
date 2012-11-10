static char* usage = "\
\tanlinfo <analysisname>\n\
\tcheck <indexname>\n\
\tclose <indexname>\n\
\tcloseanl <analysis>\n\
\tcreate <indexname> <ext-name> <data-filename> <fill-factor>\n\
\tcreate <indexname> <ext-name>\n\
\tcreateanl <analysisname> <indexname> <scriptfile> <#random> <targetutil>\n\
\tdelete <indexname> \"<qualification>\"\n\
\tdump <indexname> [<pgno>]\n\
\thelp\n\
\tinsert <indexname> \"<key>\" \"<data>\"\n\
\topen <indexname>\n\
\topenanl <analysis>\n\
\tpenaltystats <analysisname> <loadfile> [opt|act=default]\n\
\tpredinfo <index> <subtree-root> <#levels> (internal command)\n\
\tquit\n\
\tselect <indexname> [<k>] [io(<limit>)] \"<qualification>\"\n\
\tset echo (0|1)\n\
\tset struct <indexname> (0|1) (internal command)\n\
\tsplit <indexname> <pgno> (internal command)\n\
\tsplitstats <analysisname> [opt|act=default]\n\
\twkldstats <analysisname>\n\
\twrite loadfile <indexname> <filename>\n\
";
