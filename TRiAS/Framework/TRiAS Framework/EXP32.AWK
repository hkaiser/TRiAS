BEGIN	{ 
		FS = " "; 
		fOutput = 0;
		lCnt = 0;
		print "DESCRIPTION     'TRIAS® Framework'\n";
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
			printf ("\t%-60.256s\t@%ld\tNONAME\n", $3, $1);
		}
	}
