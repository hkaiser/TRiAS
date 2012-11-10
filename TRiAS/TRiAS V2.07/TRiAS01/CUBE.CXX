/* Berechnen der Nummer des Hyperwuerfels der Laenge hc_len/2,  */
/* der w enthaelt                                               */
/* File: CUBE.C                                                 */

#include "trias01p.hxx"

static short index[] = { 0,  1,  3,  2,  7,  6,  4,  5, 
                        15, 14, 12, 13,  8,  9, 11, 10 };
 
short FUNCTYPE cube (register HYPERCUBE *hc, register CONTAINER *w, FLAG flag)
{
short value = 0;
INT halflen = hc->w.hc_len/2;
 
        if (w->x_min - hc->w.hc_w >= halflen) {
                value = 1;
                if (flag) hc->w.hc_w += halflen;
        }
        if (w->x_max - hc->w.hc_x >= halflen) {
                value += 2;
                if (flag) hc->w.hc_x += halflen;
        }
        if (w->y_min - hc->w.hc_y >= halflen) {
                value += 4;
                if (flag) hc->w.hc_y += halflen;
        }
        if (w->y_max - hc->w.hc_z >= halflen) {
                value += 8;
                if (flag) hc->w.hc_z += halflen;
        }
        if (flag) hc->w.hc_len = halflen;
 
return (index[value]);
}
 
