BEGIN	{ 
		FS = " "; 
		fOutput = 0;
		lCnt = 0;
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
#			if (substr($3, 1, 3) == "Dll")
			if ($3 ~ "^Dll")
				printf ("\t%-60.256s\t@%ld\n", $3, $1);	
			else
				printf ("\t%-60.256s\t@%ld\tNONAME\n", $3, $1);
		}
	}
