#include <iostream>
#include <fstream>
using namespace std;

#include "gist_defs.h"
#include "amdb_splitstats.h"

void main() {

	ifstream inStr;
	ifstream inStr2;
	ofstream outStr;

	/* 
	inStr.open("temp2", ios_base::in | ios_base::binary );
	outStr.open("blah1", ios_base::out | ios_base::binary );

	int klen = 0;

	inStr.read((char *) &klen, sizeof(klen));

	while (!inStr.eof()) {	
		outStr.write((char *) &klen, sizeof(klen));
		inStr.read((char *) &klen, sizeof(klen));
	}

	inStr.close();
	inStr.clear();

	outStr.close();

	inStr.open("blah1", ios_base::in | ios_base::binary );

	if (inStr2.eof())
		printf("I'm mad at Microsoft. \n");
	else
		printf("I'm very mad at Microsoft. \n"); */

	amdb_splitstats::SplitStats *stats;

	stats = new amdb_splitstats::SplitStats;

	stats->actualSplit.rightEntries = new int[50];

	int i;

	for (i = 0; i < 50; i++)
		stats->actualSplit.rightEntries[i] = 1974;

	delete stats;

	return;
}
