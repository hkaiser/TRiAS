BEGIN	{
		FS =","; 

		printf ("// BScript-Erweiterung (DaoLayer) ---------------------------------------------\n");
		printf ("// File: DAOEXTF.CPP\n\n");
		printf ("#if !defined(_DAOEXTF_H)\n");
		printf ("#define _DAOEXTF_H\n\n");
	}

	{
		printf ("void %s (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);\n", $1);
	}

END	{
		printf ("\n#endif // _BSCREXTF_H\n");
	}
