/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 17 18:44:53 1999
 */
/* Compiler settings for GMConstants.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __GMConstants_h__
#define __GMConstants_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __PClient_LIBRARY_DEFINED__
#define __PClient_LIBRARY_DEFINED__

/* library PClient */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PClient;


#ifndef __ConnectionConstants_MODULE_DEFINED__
#define __ConnectionConstants_MODULE_DEFINED__


/* module ConnectionConstants */
/* [helpstring] */ 

/* [helpstring] */ const long gmcModeReadWrite	=	1;

/* [helpstring] */ const long gmcModeReadOnly	=	0;

/* [helpstring] */ const long gmcStatusOpen	=	1;

/* [helpstring] */ const long gmcStatusClosed	=	0;

#endif /* __ConnectionConstants_MODULE_DEFINED__ */


#ifndef __GConstants_MODULE_DEFINED__
#define __GConstants_MODULE_DEFINED__


/* module GConstants */
/* [helpstring] */ 

/* [helpstring] */ const LPSTR gdbCoordSystem	=	"GCoordSystemTable";

/* [helpstring] */ const LPSTR gdbModifications	=	"GModifications";

/* [helpstring] */ const LPSTR gdbModifiedTables	=	"GModifiedTables";

/* [helpstring] */ const short gdbBasicQuery	=	1;

/* [helpstring] */ const short gdbPatternQuery	=	2;

/* [helpstring] */ const short gdbFullQuery	=	3;

/* [helpstring] */ const short gdbEntirelyContains	=	1;

/* [helpstring] */ const short gdbEntirelyContainedBy	=	2;

/* [helpstring] */ const short gdbTouches	=	3;

/* [helpstring] */ const short gdbNotTouches	=	4;

/* [helpstring] */ const short gdbIndexIntersect	=	5;

/* [helpstring] */ const short gdbPoint	=	10;

/* [helpstring] */ const short gdbLinear	=	1;

/* [helpstring] */ const short gdbAreal	=	2;

/* [helpstring] */ const short gdbAnySpatial	=	3;

/* [helpstring] */ const short gdbCoverage	=	4;

/* [helpstring] */ const short gdbGraphicsText	=	5;

/* [helpstring] */ const short gdbOpenDynaset	=	2;

/* [helpstring] */ const short gdbOpenSnapshot	=	4;

/* [helpstring] */ const short gdbEditNone	=	0;

/* [helpstring] */ const short gdbEditInProgress	=	1;

/* [helpstring] */ const short gdbEditAdd	=	2;

/* [helpstring] */ const short gdbDenyWrite	=	1;

/* [helpstring] */ const short gdbDenyRead	=	2;

/* [helpstring] */ const short gdbReadOnly	=	4;

/* [helpstring] */ const short gdbAppendOnly	=	8;

/* [helpstring] */ const short gdbForwardOnly	=	256;

/* [helpstring] */ const short gdbSeeChanges	=	512;

/* [helpstring] */ const short gdbFixedField	=	1;

/* [helpstring] */ const short gdbVariableField	=	2;

/* [helpstring] */ const short gdbAutoIncrField	=	16;

/* [helpstring] */ const short gdbUpdatableField	=	32;

/* [helpstring] */ const short gdbDescending	=	1;

/* [helpstring] */ const short gdbBoolean	=	1;

/* [helpstring] */ const short gdbByte	=	2;

/* [helpstring] */ const short gdbInteger	=	3;

/* [helpstring] */ const short gdbLong	=	4;

/* [helpstring] */ const short gdbCurrency	=	5;

/* [helpstring] */ const short gdbSingle	=	6;

/* [helpstring] */ const short gdbDouble	=	7;

/* [helpstring] */ const short gdbDate	=	8;

/* [helpstring] */ const short gdbText	=	10;

/* [helpstring] */ const short gdbLongBinary	=	11;

/* [helpstring] */ const short gdbMemo	=	12;

/* [helpstring] */ const short gdbGuid	=	15;

/* [helpstring] */ const short gdbSpatial	=	32;

/* [helpstring] */ const short gdbGraphic	=	33;

/* [helpstring] */ const LPSTR gdbLangArabic	=	";LANGID=0x0401;CP=1256;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangCzech	=	";LANGID=0x0405;CP=1250;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangDutch	=	";LANGID=0x0413;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangGeneral	=	";LANGID=0x0409;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangGreek	=	";LANGID=0x0408;CP=1253;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangHebrew	=	";LANGID=0x040D;CP=1255;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangHungarian	=	";LANGID=0x040E;CP=1250;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangIcelandic	=	";LANGID=0x040F;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangNordic	=	";LANGID=0x041D;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangNorwDan	=	";LANGID=0x0414;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangPolish	=	";LANGID=0x0415;CP=1250;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangCyrillic	=	";LANGID=0x0419;CP=1251;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangSpanish	=	";LANGID=0x040A;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangSwedFin	=	";LANGID=0x040B;CP=1252;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangTurkish	=	";LANGID=0x041F;CP=1254;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangJapanese	=	";LANGID=0x0411;CP=932;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangChineseSimplified	=	";LANGID=0x0804;CP=936;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangChineseTraditional	=	";LANGID=0x0404;CP=950;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangKorean	=	";LANGID=0x040C;CP=494;COUNTRY=0";

/* [helpstring] */ const LPSTR gdbLangThai	=	";LANGID=0x101E;CP=874;COUNTRY=0";

/* [helpstring] */ const short gdbSortNeutral	=	1024;

/* [helpstring] */ const short gdbSortArabic	=	1025;

/* [helpstring] */ const short gdbSortCyrillic	=	1049;

/* [helpstring] */ const short gdbSortCzech	=	1029;

/* [helpstring] */ const short gdbSortDutch	=	1043;

/* [helpstring] */ const short gdbSortGeneral	=	1033;

/* [helpstring] */ const short gdbSortGreek	=	1032;

/* [helpstring] */ const short gdbSortHebrew	=	1037;

/* [helpstring] */ const short gdbSortHungarian	=	1038;

/* [helpstring] */ const short gdbSortIcelandic	=	1039;

/* [helpstring] */ const short gdbSortNorwdan	=	1030;

/* [helpstring] */ const short gdbSortPDXIntl	=	1033;

/* [helpstring] */ const short gdbSortPDXNor	=	1030;

/* [helpstring] */ const short gdbSortPDXSwe	=	1053;

/* [helpstring] */ const short gdbSortPolish	=	1045;

/* [helpstring] */ const short gdbSortSpanish	=	1034;

/* [helpstring] */ const short gdbSortSwedFin	=	1053;

/* [helpstring] */ const short gdbSortTurkish	=	1055;

/* [helpstring] */ const short gdbSortJapanese	=	1041;

/* [helpstring] */ const short gdbSortChineseSimplified	=	2052;

/* [helpstring] */ const short gdbSortChineseTraditional	=	1028;

/* [helpstring] */ const short gdbSortKorean	=	1036;

/* [helpstring] */ const short gdbSortThai	=	4126;

/* [helpstring] */ const short gdbSortUndefined	=	-1;

/* [helpstring] */ const short gdbUnknown	=	-1;

/* [helpstring] */ const short gdbInsert	=	1;

/* [helpstring] */ const short gdbUpdate	=	2;

/* [helpstring] */ const short gdbDelete	=	3;

#endif /* __GConstants_MODULE_DEFINED__ */


#ifndef __GCSGuidConstants_MODULE_DEFINED__
#define __GCSGuidConstants_MODULE_DEFINED__


/* module GCSGuidConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbgTransient	=	1;

/* [helpstring] */ const short gdbgPersistent	=	2;

#endif /* __GCSGuidConstants_MODULE_DEFINED__ */


#ifndef __GCSBaseStorageConstants_MODULE_DEFINED__
#define __GCSBaseStorageConstants_MODULE_DEFINED__


/* module GCSBaseStorageConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbbsProjected	=	0;

/* [helpstring] */ const short gdbbsGeographic	=	1;

/* [helpstring] */ const short gdbbsGeocentric	=	2;

#endif /* __GCSBaseStorageConstants_MODULE_DEFINED__ */


#ifndef __GCSHeightConstants_MODULE_DEFINED__
#define __GCSHeightConstants_MODULE_DEFINED__


/* module GCSHeightConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbhOrthometric	=	0;

/* [helpstring] */ const short gdbhGeometric	=	1;

/* [helpstring] */ const short gdbhUnspecified	=	2;

#endif /* __GCSHeightConstants_MODULE_DEFINED__ */


#ifndef __GCSLongitudeNormalizationConstants_MODULE_DEFINED__
#define __GCSLongitudeNormalizationConstants_MODULE_DEFINED__


/* module GCSLongitudeNormalizationConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdblnZeroTo360LeftInclude	=	0;

/* [helpstring] */ const short gdblnZeroTo360BothInclude	=	1;

/* [helpstring] */ const short gdblnMinus180ToPlus180LeftInclude	=	2;

/* [helpstring] */ const short gdblnMinus180ToPlus180BothInclude	=	3;

/* [helpstring] */ const short gdblnMinus360To0RightInclude	=	4;

/* [helpstring] */ const short gdblnMinus360To0BothInclude	=	5;

/* [helpstring] */ const short gdblnNoLongitudeNormalization	=	6;

#endif /* __GCSLongitudeNormalizationConstants_MODULE_DEFINED__ */


#ifndef __GCSGeodeticDatumConstants_MODULE_DEFINED__
#define __GCSGeodeticDatumConstants_MODULE_DEFINED__


/* module GCSGeodeticDatumConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbgdUserDefined	=	0;

/* [helpstring] */ const short gdbgdAFG	=	1;

/* [helpstring] */ const short gdbgdAustralian1966	=	2;

/* [helpstring] */ const short gdbgdAustralian1984	=	3;

/* [helpstring] */ const short gdbgdEuropean1950	=	4;

/* [helpstring] */ const short gdbgdEuropean1979	=	5;

/* [helpstring] */ const short gdbgdGeodDatum1949	=	6;

/* [helpstring] */ const short gdbgdIndian	=	7;

/* [helpstring] */ const short gdbgdIreland1965	=	8;

/* [helpstring] */ const short gdbgdNAD27	=	9;

/* [helpstring] */ const short gdbgdNAD83	=	10;

/* [helpstring] */ const short gdbgdOrdnanceSurveyGreatBritain	=	11;

/* [helpstring] */ const short gdbgdPulkovo1942	=	12;

/* [helpstring] */ const short gdbgdQornoq	=	13;

/* [helpstring] */ const short gdbgdTokyo	=	14;

/* [helpstring] */ const short gdbgdWGS66	=	15;

/* [helpstring] */ const short gdbgdWGS72	=	16;

/* [helpstring] */ const short gdbgdWGS84	=	17;

/* [helpstring] */ const short gdbgdSAD1956	=	18;

/* [helpstring] */ const short gdbgdSAD1969	=	19;

/* [helpstring] */ const short gdbgdIndonesian1974	=	20;

/* [helpstring] */ const short gdbgdWGS60	=	21;

/* [helpstring] */ const short gdbgdTananObservatory1925	=	22;

/* [helpstring] */ const short gdbgdKertau1948	=	23;

/* [helpstring] */ const short gdbgdPotsdam	=	24;

/* [helpstring] */ const short gdbgdUSStandard	=	25;

/* [helpstring] */ const short gdbgdMGICS	=	26;

#endif /* __GCSGeodeticDatumConstants_MODULE_DEFINED__ */


#ifndef __GCSEllipsoidConstants_MODULE_DEFINED__
#define __GCSEllipsoidConstants_MODULE_DEFINED__


/* module GCSEllipsoidConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbeUndefined	=	0;

/* [helpstring] */ const short gdbeGRS80	=	1;

/* [helpstring] */ const short gdbeWGS72	=	2;

/* [helpstring] */ const short gdbeAussyNationalSAmerica69	=	3;

/* [helpstring] */ const short gdbeKrassovsky	=	4;

/* [helpstring] */ const short gdbeInternational	=	5;

/* [helpstring] */ const short gdbeWGS66	=	6;

/* [helpstring] */ const short gdbeClark1880	=	7;

/* [helpstring] */ const short gdbeClark1866	=	8;

/* [helpstring] */ const short gdbeHelmert1906	=	9;

/* [helpstring] */ const short gdbeBessel1841	=	10;

/* [helpstring] */ const short gdbeDanish	=	11;

/* [helpstring] */ const short gdbeStruve	=	12;

/* [helpstring] */ const short gdbeHough	=	13;

/* [helpstring] */ const short gdbeAiry1830	=	14;

/* [helpstring] */ const short gdbeEverest1830	=	15;

/* [helpstring] */ const short gdbeModAiry	=	16;

/* [helpstring] */ const short gdbeModEverest	=	17;

/* [helpstring] */ const short gdbeFischer1960Mercury	=	18;

/* [helpstring] */ const short gdbeModFischer1960SA	=	19;

/* [helpstring] */ const short gdbeFischer1968	=	20;

/* [helpstring] */ const short gdbeUserDefined	=	21;

/* [helpstring] */ const short gdbeWGS84	=	22;

/* [helpstring] */ const short gdbeIndoNational1974	=	23;

/* [helpstring] */ const short gdbeWGS60	=	24;

/* [helpstring] */ const short gdbeUnitSphere	=	25;

#endif /* __GCSEllipsoidConstants_MODULE_DEFINED__ */


#ifndef __GCSProjectionAlgorithmConstants_MODULE_DEFINED__
#define __GCSProjectionAlgorithmConstants_MODULE_DEFINED__


/* module GCSProjectionAlgorithmConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbpaUndefined	=	0;

/* [helpstring] */ const short gdbpaMercator	=	1;

/* [helpstring] */ const short gdbpaLambert	=	2;

/* [helpstring] */ const short gdbpaNorthPolar	=	3;

/* [helpstring] */ const short gdbpaSouthPolar	=	4;

/* [helpstring] */ const short gdbpaLinearElastic	=	5;

/* [helpstring] */ const short gdbpaTransverseMercator	=	6;

/* [helpstring] */ const short gdbpaUniversalTransverseMercator	=	8;

/* [helpstring] */ const short gdbpaIndonesianPoly	=	9;

/* [helpstring] */ const short gdbpaSPCS27	=	10;

/* [helpstring] */ const short gdbpaPolyconic	=	11;

/* [helpstring] */ const short gdbpaAlbers	=	12;

/* [helpstring] */ const short gdbpaObliqueMercator	=	13;

/* [helpstring] */ const short gdbpaNewZealand	=	14;

/* [helpstring] */ const short gdbpaVanDerGrinten	=	15;

/* [helpstring] */ const short gdbpaAzimuthalEquidistant	=	19;

/* [helpstring] */ const short gdbpaOrthographic	=	20;

/* [helpstring] */ const short gdbpaSPCS83	=	21;

/* [helpstring] */ const short gdbpaStereographic	=	22;

/* [helpstring] */ const short gdbpaGnomonic	=	23;

/* [helpstring] */ const short gdbpaRobinson	=	24;

/* [helpstring] */ const short gdbpaCassini	=	25;

/* [helpstring] */ const short gdbpaSinusoidal	=	26;

/* [helpstring] */ const short gdbpaLambertAzimuthalEqArea	=	27;

/* [helpstring] */ const short gdbpaMillerCyl	=	28;

/* [helpstring] */ const short gdbpaBonne	=	29;

/* [helpstring] */ const short gdbpaBritNGrid	=	30;

/* [helpstring] */ const short gdbpaMollweide	=	31;

/* [helpstring] */ const short gdbpaLocalSpaceRect	=	32;

/* [helpstring] */ const short gdbpaUniversalPolarStereo	=	33;

/* [helpstring] */ const short gdbpaRectifiedSkewOrthomorphic	=	35;

/* [helpstring] */ const short gdbpaIMWModPolycon	=	36;

/* [helpstring] */ const short gdbpaObliqueLambert	=	37;

/* [helpstring] */ const short gdbpaChamberlinTrimetric	=	38;

/* [helpstring] */ const short gdbpaCylEquirect	=	39;

/* [helpstring] */ const short gdbpaGeneralPerspective	=	40;

/* [helpstring] */ const short gdbpaConic	=	41;

/* [helpstring] */ const short gdbpaStereo3Step	=	42;

/* [helpstring] */ const short gdbpaGaussKruger	=	43;

/* [helpstring] */ const short gdbpaBIPOCC	=	44;

/* [helpstring] */ const short gdbpaLaborde	=	45;

/* [helpstring] */ const short gdbpaEckertIV	=	46;

/* [helpstring] */ const short gdbpaSpaceObliqueMercator	=	47;

/* [helpstring] */ const short gdbpaSpaceObliqueMercatorPS	=	48;

/* [helpstring] */ const short gdbpaKrovak	=	49;

#endif /* __GCSProjectionAlgorithmConstants_MODULE_DEFINED__ */


#ifndef __GCSHemisphereConstants_MODULE_DEFINED__
#define __GCSHemisphereConstants_MODULE_DEFINED__


/* module GCSHemisphereConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbhNorthern	=	0;

/* [helpstring] */ const short gdbhSouthern	=	1;

#endif /* __GCSHemisphereConstants_MODULE_DEFINED__ */


#ifndef __GCSSatelliteConstants_MODULE_DEFINED__
#define __GCSSatelliteConstants_MODULE_DEFINED__


/* module GCSSatelliteConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbsLandsat1	=	0;

/* [helpstring] */ const short gdbsLandsat2	=	1;

/* [helpstring] */ const short gdbsLandsat3	=	2;

/* [helpstring] */ const short gdbsLandsat4	=	3;

/* [helpstring] */ const short gdbsLandsat5	=	4;

#endif /* __GCSSatelliteConstants_MODULE_DEFINED__ */


#ifndef __GCSLocalSpaceRectConstants_MODULE_DEFINED__
#define __GCSLocalSpaceRectConstants_MODULE_DEFINED__


/* module GCSLocalSpaceRectConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdblsrXAxisAzDefinedByDirect	=	0;

/* [helpstring] */ const short gdblsrXAxisAzDefinedByTwoPoints	=	1;

#endif /* __GCSLocalSpaceRectConstants_MODULE_DEFINED__ */


#ifndef __GCSObliqueMercatorConstants_MODULE_DEFINED__
#define __GCSObliqueMercatorConstants_MODULE_DEFINED__


/* module GCSObliqueMercatorConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbomByOnePointAndAzimuth	=	0;

/* [helpstring] */ const short gdbomByTwoPoints	=	1;

#endif /* __GCSObliqueMercatorConstants_MODULE_DEFINED__ */


#ifndef __GCSObliqueLambertConfConicConstants_MODULE_DEFINED__
#define __GCSObliqueLambertConfConicConstants_MODULE_DEFINED__


/* module GCSObliqueLambertConfConicConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbolccByRotatedNorthPole	=	0;

/* [helpstring] */ const short gdbolccByAzimuthOfCentralMeridian	=	1;

#endif /* __GCSObliqueLambertConfConicConstants_MODULE_DEFINED__ */


#ifndef __GCSSphericalModelConstants_MODULE_DEFINED__
#define __GCSSphericalModelConstants_MODULE_DEFINED__


/* module GCSSphericalModelConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbsmEquatorial	=	0;

/* [helpstring] */ const short gdbsmEqualSurface	=	1;

/* [helpstring] */ const short gdbsmEqualVolume	=	2;

/* [helpstring] */ const short gdbsmGaussian	=	3;

/* [helpstring] */ const short gdbsmUserSpecified	=	4;

#endif /* __GCSSphericalModelConstants_MODULE_DEFINED__ */


#ifndef __GCSChamberlinTrimetricConstants_MODULE_DEFINED__
#define __GCSChamberlinTrimetricConstants_MODULE_DEFINED__


/* module GCSChamberlinTrimetricConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbctOriginUserSpecified	=	0;

/* [helpstring] */ const short gdbctOriginAutomatic	=	1;

#endif /* __GCSChamberlinTrimetricConstants_MODULE_DEFINED__ */


#ifndef __GCSGeneralPerspectiveAngOrientationProjPlaneConstants_MODULE_DEFINED__
#define __GCSGeneralPerspectiveAngOrientationProjPlaneConstants_MODULE_DEFINED__


/* module GCSGeneralPerspectiveAngOrientationProjPlaneConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbgpaoppByRotations	=	0;

/* [helpstring] */ const short gdbgpaoppByTiltSwingAzimuth	=	1;

#endif /* __GCSGeneralPerspectiveAngOrientationProjPlaneConstants_MODULE_DEFINED__ */


#ifndef __GCSGeneralPerspectiveLocProjPlaneConstants_MODULE_DEFINED__
#define __GCSGeneralPerspectiveLocProjPlaneConstants_MODULE_DEFINED__


/* module GCSGeneralPerspectiveLocProjPlaneConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbgplppByHeightAboveEllipAtNadir	=	0;

/* [helpstring] */ const short gdbgplppByFocalLength	=	1;

#endif /* __GCSGeneralPerspectiveLocProjPlaneConstants_MODULE_DEFINED__ */


#ifndef __GCSGeneralPerspectiveRefCoordSysConstants_MODULE_DEFINED__
#define __GCSGeneralPerspectiveRefCoordSysConstants_MODULE_DEFINED__


/* module GCSGeneralPerspectiveRefCoordSysConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gdbgprcsByGeographic	=	0;

/* [helpstring] */ const short gdbgprcsByGeocentric	=	1;

/* [helpstring] */ const short gdbgprcsByLocalHorizon	=	2;

#endif /* __GCSGeneralPerspectiveRefCoordSysConstants_MODULE_DEFINED__ */


#ifndef __NotificationConstants_MODULE_DEFINED__
#define __NotificationConstants_MODULE_DEFINED__


/* module NotificationConstants */
/* [helpstring] */ 

/* [helpstring] */ const long gmnRowDeleted	=	1;

/* [helpstring] */ const long gmnRowModified	=	2;

/* [helpstring] */ const long gmnMemberAdded	=	3;

/* [helpstring] */ const long gmnMemberRemoved	=	4;

/* [helpstring] */ const long gmnUpToDate	=	1;

/* [helpstring] */ const long gmnStatusUnknown	=	2;

/* [helpstring] */ const long gmnStatusRecordsetOpen	=	1;

/* [helpstring] */ const long gmnStatusRowChanges	=	2;

/* [helpstring] */ const long gmnStatusMembershipChanges	=	4;

#endif /* __NotificationConstants_MODULE_DEFINED__ */


#ifndef __GeometryEditConstants_MODULE_DEFINED__
#define __GeometryEditConstants_MODULE_DEFINED__


/* module GeometryEditConstants */
/* [helpstring] */ 

/* [helpstring] */ const short gmgeMoveGeometry	=	0;

/* [helpstring] */ const short gmgeMoveKeypoint	=	1;

/* [helpstring] */ const short gmgeInsertVertex	=	2;

/* [helpstring] */ const short gmgeDeleteSelectedVertices	=	3;

#endif /* __GeometryEditConstants_MODULE_DEFINED__ */
#endif /* __PClient_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
