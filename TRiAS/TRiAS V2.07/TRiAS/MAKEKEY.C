// Berechnen des Schluesselcodes der Personalisierungsinformation
// File: MAKEKEY.C

#include <stdio.h>

#if defined(DLL)
#define FUNCTYPE _pascal
#else
#define FUNCTYPE _cdecl
#endif

short FUNCTYPE mycrypt (char *ptr, int n);

static char *ParseString (char *pStr)
{
static char cbBuffer[256];
int i = 0;

	cbBuffer[0] = '\0';
	while (pStr && *pStr) {
		if (*pStr == '\\') {
			switch (*++pStr) {
			case 'b':	cbBuffer[i] = '\b'; break;
			case 't':	cbBuffer[i] = '\t'; break;
			case 'n':	cbBuffer[i] = '\n'; break;
			case 'r':	cbBuffer[i] = '\r'; break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
				cbBuffer[i] = (char)(strtol (pStr, &pStr, 8));
				pStr--;
				break;

			default:	
				cbBuffer[i] = *pStr; 
				break;
			}
		} else
			cbBuffer[i] = *pStr;
		pStr++;
		i++;
	}
	cbBuffer[i] = '\0';

return cbBuffer;
}

void main (int argc, char *argv[]) 
{
char personal[129];

        if (argc < 3) {
                fprintf (stderr, "Usage: %s Name Address [ > outfile]\n", argv[0]);
                exit (1);
        }

	printf ("// Personalisierungsinformationskode\n");
	printf ("// Dieser Kode gilt fÅr: %s\n", ParseString(argv[1]));
	printf ("//                       %s\n", ParseString(argv[2]));

	strcpy (personal, ParseString(argv[1]));
	strcat (personal, ParseString(argv[2]));

// SchlÅssel berechnen
	printf ("#define PERSONALKEYCODE 0x%04x\n", mycrypt (personal, strlen(personal)));

exit (0);
}
