/* Berechnung des CRC-Restkodes eines Datenblockes      */
/* File: CRC.C          last update: 07. Maerz 1988     */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)mycrypt.c   2.4  90/04/10";
#endif

#include "dbconfig.h"

static short FUNCTYPE resetcrc (void);
static short FUNCTYPE getcrc (char zeichen);
static short FUNCTYPE flushcrc (void);

/* CRC16 Polynom */
#define POLYNOM 0x8005
 
static union {
        struct {
                char l;
                char h;
        } byte;
        short hl;
} crc;
 
/* Berechnung des CRC-Restcodes fuer Datenblock */

short FUNCTYPE
mycrypt (ptr, n)
register unsigned char *ptr;
register int n;
{
        resetcrc ();
        while (n--) getcrc (*ptr++);
 
return (flushcrc ());
}
 
 
/* Ruecksetzen CRC-Generator */
 
static short FUNCTYPE
resetcrc ()
{
        return (crc.hl = 0);    /* Nullsetzen, da CRC16-Polynom */
}
 
 
/* CRC-Berechnung fuer ein Zeichen */
 
static short FUNCTYPE
getcrc (zeichen)
char zeichen;
{
register int i;
register unsigned int regcrc;
 
        crc.byte.h ^= zeichen;
        regcrc = crc.hl;
        for (i = 0; i < 8; i++) {
                if (regcrc & 0x8000)
                        regcrc = (regcrc << 1) ^ POLYNOM;
                else
                        regcrc <<= 1;
        }
 
return ((crc.hl = regcrc) & 0xffff);
}
 
 
/* Lesen CRC-Generator */
 
static short FUNCTYPE
flushcrc (void)
{
        return (crc.hl & 0xffff);
}
 
