BEGIN		{
		FS = "\t";
		OFS = ";";
		OFR = ";";
	}
$1 == "" 	{
		for (i = 1; i <= NF; i++) {
			iIndex = index ($i, "\"");
			while (iIndex != 0) {
				if (iIndex == 1)
					$i = substr ($i, 2, length($i));
				else if (iIndex == length($i))
					$i = substr ($i, 1, length($i)-1);
				iIndex = index ($i, "\"");
			} 
		}
		printf "%s;%s;%s;%s;%s;%s;%s;%s\n", $1,$2,$3,$4,$5,$6,$7,$8;
#		print $0;
	}
$1 != ""	{
		print $1,$2,$3,$4,$5,$6,$7,$8;
	}
