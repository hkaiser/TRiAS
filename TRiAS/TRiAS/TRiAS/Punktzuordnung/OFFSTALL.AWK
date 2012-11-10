BEGIN	{
# Generieren der Zuordnungstabelle von PunktID zu BitmapIndex und
# Offsets dieses Symboles in den drei Bitmaps (15*15, 23*23 und 32*32)

		FS = ";";
	}
$1 == ""	{
		printf "%05ld;%03ld;%s;%s;%s\n", $4, $8, $5, $6, $7;
	}
$1 != ""	{
	}
