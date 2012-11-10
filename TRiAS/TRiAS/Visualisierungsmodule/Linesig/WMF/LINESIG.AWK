BEGIN{
	FS="\t"
	ResName = "LINESIG DISCARDABLE FIXED"
	n=256
	nSig=56
	print "255 LINESIG LOADONCALL DISCARDABLE BEGIN \"" n ";" n+nSig "\" END"
	print n++ "\t" ResName "\t\"Wmf/uve_logo/logo_uve.wmf\""
	for( i = 1; i <= nSig; i++ )
		printf( "%d\t%s\t\"Wmf/s%02d.wmf\"\n", n++, ResName, i )
}
