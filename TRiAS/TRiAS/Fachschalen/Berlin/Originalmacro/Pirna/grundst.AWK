BEGIN { FS = " " }
$1 == "F" {
	printf "F\t%s\t\"1124\"\t%s\n",$2,$4;
	}
$1 != "F" {
	print $0;
	}
