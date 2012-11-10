BEGIN	{
# Generiert aus ZUORDPKN.IDS die Stringresource fr die Punktbezeichner und
# die zugeh”rige HeaderDatei.

		FS = ";";
		strtable = "punktstr.rc"
		deftable = "punktstr.h"

		printf ("STRINGTABLE MOVEABLE DISCARDABLE LOADONCALL\n") >>strtable;
		printf ("BEGIN\n") >> strtable;
		iBase = 15000;
	}
$1 != ""	{
	}
$1 == ""	{
		printf "\tIDS_PUNKTSYM%03ld\t\"%s\"\n", $8, $2 > strtable;
		printf "#define\tIDS_PUNKTSYM%03ld\t%ld\n", $8, ($8)+15000 > deftable;
	}
END	{
		print "END" >> strtable;
	}
