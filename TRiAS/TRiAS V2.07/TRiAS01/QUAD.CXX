/* Berechnen der Nummer des Quadranten der Laenge qc_len/2,     */
/* der w enthaelt                                               */
/* File: QUAD.C         last update: 11. Oktober 1989           */

#include "trias01p.hxx"
 
static short index[] = { 0,  1,  3,  2, };
 
short FUNCTYPE quad (register QUADRANT *qd, register QTPOINT *w, FLAG flag)
// register QUADRANT *qd;          /* Quadrant */
// register QTPOINT *w;      /* einzuordnender Container */
// FLAG flag;              /* TRUE: qd wird entsprechend korrigiert */
{
short value = 0;
INT halflen = qd->w.qd_len/2;
 
        if (w->x_min - qd->w.qd_x >= halflen) {
                value = 1;
                if (flag) qd->w.qd_x += halflen;
        }
        if (w->y_min - qd->w.qd_y >= halflen) {
                value += 2;
                if (flag) qd->w.qd_y += halflen;
        }
        if (flag) qd->w.qd_len = halflen;
 
return (index[value]);
}
 
