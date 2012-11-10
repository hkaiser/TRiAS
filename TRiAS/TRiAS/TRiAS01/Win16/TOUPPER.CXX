#include <stdio.h>
#include <ctype.h>

main () {
register int c;

	while ((c = fgetc (stdin)) != EOF) {
		if (islower (c))	fputc (toupper(c), stdout);
		else fputc (c, stdout);
	}
}