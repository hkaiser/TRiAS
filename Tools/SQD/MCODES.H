// Definition der verwendeteten MerkmalsKodes ---------------------------------
// File: MCODES.H

#if !defined(_MCODES_H)
#define _MCODES_H

// Identifikatoren, die den einzelnen Ebenen zugeordnet werden
#define	PUNKTEBENE0		1000
#define LINIENEBENE0		2000
#define FLAECHENEBENE0		3000
#define TEXTEBENE0		4000

// Offset fÅr verschiedene ObjektTypen
#define MKPUNKT		1000
#define MKLINIE		2000
#define MKFLAECHE	3000
#define MKTEXT		4000

#define DBASECODE		5000		// dBaseCode

// PunktAttribute
#define MKPKZ		MKPUNKT+1
#define MKPNR		MKPUNKT+2
#define MKPTEXT		MKPUNKT+3
#define MKPNAME		MKPUNKT+4
#define MKPCODE		DBASECODE

// LinienAttribute
#define MKLNAME		MKLINIE+1
#define MKLTEXT		MKLINIE+2
#define MKLCODE		DBASECODE

// TextAttribute
#define	MKTHOEHE	MKTEXT+1
#define	MKTLAENGE	MKTEXT+2
#define MKTMODUS	MKTEXT+3
#define MKTWINKEL	MKTEXT+4
#define MKTRICHT	MKTEXT+5
#define MKTTEXT		MKTEXT+6
#define MKTSWINKEL	MKTEXT+7
#define MKTVISINFO	MKTEXT+8
#define MKTCODE		DBASECODE

// FlÑchenattribute
#define MKFTEXT		MKFLAECHE+1
#define MKFXKOORD	MKFLAECHE+2
#define MKFYKOORD	MKFLAECHE+3
#define MKFSWINKEL	MKFLAECHE+4
#define MKFSABSTAND	MKFLAECHE+5
#define MKFNAME		MKFLAECHE+6
#define MKFPOINTER	MKFLAECHE+7
#define MKFCODE		DBASECODE

#endif // _MCODES
