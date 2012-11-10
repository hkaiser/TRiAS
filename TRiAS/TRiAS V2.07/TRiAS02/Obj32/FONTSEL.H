/*****************************************************************************\
*                                                                             *
* selfont.h -   Common dialog's dialog element ID numbers                     *
*                                                                             *
*               Version 1.0                                                   *
*                                                                             *
*               Copyright (c) 1992, Microsoft Corp.  All rights reserved.     *
*                                                                             *
\*****************************************************************************/

#ifndef _INC_SELFONT
#define _INC_SELFONT

    /* Push buttons */
#define psh1        0x0400
#define psh3        0x0402
#define psh15       0x040e
#define pshHelp     psh15
    /* Checkboxes */
#define chx1        0x0410
#define chx2        0x0411
    /* Radio buttons */
    /* Groups, frames, rectangles, and icons */
#define grp1        0x0430
#define grp2        0x0431
    /* Static text */
#define stc1        0x0440
#define stc2        0x0441
#define stc3        0x0442
#define stc4        0x0443
#define stc5        0x0444
#define stc6        0x0445
    /* Listboxes */
    /* Combo boxes */
#define cmb1        0x0470
#define cmb2        0x0471
#define cmb3        0x0472
#define cmb4        0x0473
    /* Edit controls */
    /* Scroll bars */

/* These dialog resource ordinals really start at 0x0600, but the
 * RC Compiler can't handle hex for resource IDs, hence the decimal.
 */
#define FORMATDLGORD31   1543

// zusätzliche Controls 
#define IDCB_FONTFRAMED		1001
#define IDCB_FONTTRANSPARENT	1000
#define IDE_FONTORIENTATION	1003
#define IDE_FONTESCAPEMENT	1002
#define IDT_FONTORIENTATION	1004

#endif  /* !_INC_SELFONT */
