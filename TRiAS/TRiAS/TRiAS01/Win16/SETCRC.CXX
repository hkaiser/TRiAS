/* Berechnen des CRC-Restcodes von argv[1]                      */
/* File: SETCRC.C               last update: 8. Januar 1990     */

#include <stdio.h>
#include <string.h>
#include <process.h>

#include <dbconfig.h>
#include <dbtypes.h>
#include <protos.h>

#include "version.tmp"
 
extern "C" {
// 	unsigned short FUNCTYPE mycrypt (unsigned char *, short iLen);
}

static void replace (unsigned short arg);

void main (void)
{
unsigned char buffer[81];
char crcbuf[10];
FILE *fp;
 
 
        memset (buffer, '\0', 80);
        sprintf ((char *)buffer, "%s - %s%s %s\r\n\032", Copyright, Version, Release, Date);
        replace (mycrypt (buffer, 80));
 
exit (0);
}
 

static void replace (unsigned short arg)
{
register int c, c1;
 
        while ((c = getc (stdin)) != EOF) {
                if (c == '@') {
                        if ((c1 = getc (stdin)) == EOF) break;
                        if (c1 == 'A') {
                                printf ("0x%04x", arg);
                                continue;
                        } else
                                ungetc (c1, stdin);
                }
                putc (c, stdout);
        }
}
 
