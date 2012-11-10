BEGIN	{
# Berechnen der Seitenverh„ltnisse der Bitmaps

		FS = ";";
	}
$1 == ""	{
		printf "%03ld;", $8;

# Seitenverh„ltnis 15*15
		split ($5,aArray,",")
		printf "%6.3lf,", (15-2*aArray[1])/(15-2*aArray[2]);

# Seitenverh„ltnis 23*23
		split ($6,aArray,",")
		printf "%6.3lf,", (23-2*aArray[1])/(23-2*aArray[2]);

# Seitenverh„ltnis 32*32
		split ($7,aArray,",")
		printf "%6.3lf\n", (32-2*aArray[1])/(32-2*aArray[2]);
	}
$1 != ""	{
	}
