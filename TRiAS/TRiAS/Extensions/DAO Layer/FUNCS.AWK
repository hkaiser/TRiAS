BEGIN	{
		FS =","; 
	}
	{
		printf ("// -------------------------------------------------------------------------------\n");
		printf ("// %s\n", $1);
		printf ("// -------------------------------------------------------------------------------\n");
		printf ("void %s (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)\n", $1);
		printf ("{\n\tDao_not_supported (hThread, iNumArgs, lpArgs);\n}\n\n");
	}