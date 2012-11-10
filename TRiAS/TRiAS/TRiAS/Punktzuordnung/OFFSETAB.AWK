BEGIN	{
# Generieren der Zuordnungstabelle von PunktID zu BitmapIndex

		FS = ";";
	}
$1 == ""	{
		printf "%03ld;%05ld\n", $8, $4;
	}
$1 != ""	{
	}
