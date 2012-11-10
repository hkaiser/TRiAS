BEGIN	{ 
		FS = " "; 
		fOutput = 0;
		lCnt = 0;
		print "DESCRIPTION     'Systems<Toolkit> V2.0, Copyright(c) 1994-1997 ObjectSpace, Inc.'\n";
		print "EXPORTS";
	}
/ordinal hint/	{
		fOutput = 1;
	}
/Summary/	{
		fOutput = 0;
	}
!/ordinal/	{
		if (fOutput != 0 && length($3) > 0) {
			printf ("\t%-60.256s\t@%ld\n", $3, $1);
		}
	}
