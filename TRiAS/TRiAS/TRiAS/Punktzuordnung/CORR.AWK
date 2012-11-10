# korrigiert die Felder $5 bis $7, wenn Excel den zweiten Wert
# entfernt hat
BEGIN	{
		FS =";";
		OFS = ";";
	}
$1 != ""	{
		print $0;
	}
$1 == ""	{
		iCnt = split ($5,aArray,",")
		if (iCnt == 1)
			aArray[2] = 0;
		$5 = aArray[1] "," aArray[2];

		iCnt = split ($6,aArray,",")
		if (iCnt == 1)
			aArray[2] = 0;
		$6 = aArray[1] "," aArray[2];

		iCnt = split ($7,aArray,",")
		if (iCnt == 1)
			aArray[2] = 0;
		$7 = aArray[1] "," aArray[2];

		print $0;
	}
