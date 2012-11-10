BEGIN	{
# Auffllen von fehlenden BitmapIdizies in der PunktID-Tabelle

		FS = ";";
		OFS = ";";
		iRec = 0;
	}
	{
		while ($1 > iRec + 1) {
			printf "%03ld;00000\n", ++iRec;
		}
		print $0;
		++iRec;
	}
