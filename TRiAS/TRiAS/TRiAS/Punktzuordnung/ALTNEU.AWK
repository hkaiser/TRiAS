BEGIN	{
# Generiert aus einer CSV-Datei der Struktur ZURDPKN.TAB die Zuordnung
# der alten Punktsymbole zu den neuen.

		FS =";";
	}
$1 == "" 	{
		if ($3 != "") {
			iCnt = split ($3, aNumbers, ",")
			for (i = 1; i <= iCnt; i++) 
				printf "%03ld,%05ld\n", aNumbers[i], $4;
		}
	}
$1 != ""	{
	}