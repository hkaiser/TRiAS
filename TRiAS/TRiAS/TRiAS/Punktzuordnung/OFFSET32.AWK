BEGIN	{
# Generieren der Offsets der Symboles in der dritten Bitmap (32*32) fr 
# einzelne Punktsymbole

		FS = ";";
	}
$1 == ""	{
		printf "%03ld;%s\n", $8, $7;
	}
$1 != ""	{
	}
