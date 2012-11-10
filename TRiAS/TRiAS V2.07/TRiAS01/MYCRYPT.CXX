/* Berechnung des CRC-Restkodes eines Datenblockes      */
/* File: CRC.C          last update: 07. Maerz 1988     */

#include "trias01p.hxx"

static unsigned short FUNCTYPE resetcrc (void);
static unsigned short FUNCTYPE getcrc (char zeichen);
static unsigned short FUNCTYPE flushcrc (void);

/* CRC16 Polynom */
#define POLYNOM 0x8005
 
typedef union tagCRC {
        struct tagBYTES {
                char l;
                char h;
        } byte;
        short hl;
} CRC;

static CRC __near crc;

#if !defined(MSWIND)
#define EXPORT01
#endif

/* Berechnung des CRC-Restcodes fuer Datenblock */
extern "C" unsigned short FUNCTYPE EXPORT01 mycrypt (unsigned char *ptr, short n)
{
        resetcrc ();
        while (n--) getcrc (*ptr++);
 
return (flushcrc ());
}
 
 
/* Ruecksetzen CRC-Generator */
 
static unsigned short FUNCTYPE resetcrc (void)
{
        return (crc.hl = 0);    /* Nullsetzen, da CRC16-Polynom */
}
 
 
/* CRC-Berechnung fuer ein Zeichen */
 
static unsigned short FUNCTYPE getcrc (char zeichen)
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
 
static unsigned short FUNCTYPE flushcrc (void)
{
        return (crc.hl & 0xffff);
}
 
