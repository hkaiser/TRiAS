// ResID's fuer die TortenResourcen -------------------------------------------
// FILE: TORTEN.H

#if !defined(_TORTEN_H)
#define _TORTEN_H

// BitmapID's -----------------------------------------------------------------
//#define IDBM_FULLCIRCLE		1	/* 0 */
//#define IDBM_UPPERHALF		2	/* 1 */
//#define IDBM_UPPERHALFOFFSET	258	/* 0x0101 */
//#define IDBM_LOWERHALF		3	/* 2 */
//#define IDBM_LOWERHALFOFFSET	259	/* 0x0102 */

// Typen der Diagramme, muﬂ 1000+TORTEN_... sein ------------------------------
#define IDS_FULLCIRCLE		1000
#define IDS_UPPERHALF		1001
#define IDS_LOWERHALF		1002

#define IDS_BALKENHOCHPOS	1010	// Balken hochkant nach oben
#define IDS_BALKENHOCHPOSLOG	1011	// Balken hochkant nach oben, logarithmisch
#define IDS_BALKENROT		1012	// Balken hochkant nach oben
#define IDS_BALKENROTLOG	1013	// Balken hochkant nach oben, logarithmisch

#define IDS_BALKENHOCHPOSEXP	1014	// Balken hochkant nach oben, exponentiell


#define IDS_BALKENHOCHNEG	1015	// Balken hochkant nach unten
#define IDS_BALKENQUERPOS	1016	// Balken quer nach rechts
#define IDS_BALKENQUERNEG	1017	// Balken quer nach links


// sonstige Strings -----------------------------------------------------------
#define IDS_CUSTFORMAT		1300

#define IDS_OBEN		1301
#define IDS_UNTEN		1302
#define IDS_TORTENPALETTEN	1303
#define IDS_VMDEXT		1304
#define IDS_SELECTCAPTION	1305
#define IDS_DEFAULTPALETTE	1306

#endif // _TORTEN_H


