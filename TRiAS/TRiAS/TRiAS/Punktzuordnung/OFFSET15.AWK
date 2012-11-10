BEGIN	{
# Generieren der Offsets der Symboles in der ersten Bitmap (15*15) fr 
# einzelne Punktsymbole

		FS = ";";
	}
$1 == ""	{
		printf "%03ld;%s\n", $8, $5;
	}
$1 != ""	{
	}
