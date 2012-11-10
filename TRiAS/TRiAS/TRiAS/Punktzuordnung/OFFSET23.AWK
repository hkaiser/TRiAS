BEGIN	{
# Generieren der Offsets der Symboles in der zweiten Bitmap (23*23) fr 
# einzelne Punktsymbole

		FS = ";";
	}
$1 == ""	{
		printf "%03ld;%s\n", $8, $6;
	}
$1 != ""	{
	}
