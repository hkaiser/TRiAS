BEGIN	{
# Auffllen von fehlenden Bitmaps in einer Offsettabelle

		FS = ";";
		OFS = ";";
		iRec = 0;
	}
	{
		while ($1 > iRec + 1) {
			printf "%03ld;0,0\n", ++iRec;
		}
		print $0;
		++iRec;
	}
