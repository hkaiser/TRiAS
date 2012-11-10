BEGIN	{

# Generieren von hierachischen PunktIdents, welche die Zugeh”rigkeit 
# eines Punktsymboles zu einer bestimmten Signaturgruppe festlegt.
# Dabei wird ausreichend Platz fr zuknftige Erweiterungen gelassen.
# Eingabedatei: ZUORDPKN.TAB (CSV mit ';')
		FS=";";
		OFS=";";
		iZT = 0;
		iT = -1;
		iH = -1;
		iZ = -1;
		iE = -1;
	}
$1 == ""	{
		if (iZ == -1) iZ = 0;
		if (iH == -1) iH = 0;
		if (iT == -1) iT = 0;
		if (iZT == -1) iZT = 0;
		if (iZ == 0 && iH == 0 && iT == 0 && iZT == 0 && iE == -1)
			iE = 0;
		iE++;
		$4 = iE + 10*iZ + 100*iH + 1000*iT + 10000*iZT;
		print $0;
	}
$1 != ""	{
		if ($1 != "#") {	# keine Kommentarzeile
			if ($1 == 1) {
				iZT++; 
				if (iE >= 10) iZ++;
				if (iZ >= 10) iH++;
				if (iH >= 10) iT++;
				if (iT >= 10) iZT++;
				iT = -1; iH = -1; iZ = -1; iE = -1;
			} else if ($1 == 2) {
				iT++; 
				if (iE >= 10) iZ++;
				if (iZ >= 10) iH++;
				if (iH >= 10) iT++;
				iH = -1; iZ = -1; iE = -1;
			} else if ($1 == 3) {
				iH++; 
				if (iE >= 10) iZ++;
				if (iZ >= 10) iH++;
				iZ = -1; iE = -1;
			} else if ($1 == 4) {
				iZ++; 
				if (iE >= 10) iZ++;
				if (iE >= 20) iZ++;
				iE = -1;
			} else
				print "Falsche Kennzahl" > "con";
		}
		print $0;
	}