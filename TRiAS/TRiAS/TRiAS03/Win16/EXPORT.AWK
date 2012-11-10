BEGIN	{
		fFlag=0;
		iCnt = 2;
		printf "\t%-56s\t@1\tRESIDENTNAME PRIVATE\n", "WEP";
	}
/Publics by Name/ {
		fFlag=0;
	}
fFlag==1 && $2 != "WEP"	&& $2 != "___ExportedStub" && $0 != "" {
			printf "\t%-56s\t@%d\n", $2, iCnt++;
	}
/Address   Export/ {
		fFlag=1;
		getline;
	}

