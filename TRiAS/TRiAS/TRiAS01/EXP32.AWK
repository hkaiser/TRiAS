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
                        printf ("\t%-60.256s\t@%ld", $3, $1);
                        if ($3 == "DllGetClassObject" ||
                            $3 == "DllCanUnloadNow" ||
                            $3 == "DllRegisterServer" ||
                            $3 == "DllUnregisterServer") {
                                printf("\tPRIVATE");
                        }
                        printf("\n");
                }
	}
