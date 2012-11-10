// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 11:27:37 
//
// @doc
// @module EPSG.h | Declaration of the <c CEPSG> class

#if !defined(_EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_)
#define _EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

cpp_quote("typedef struct { long code; LPCTSTR name; } CODENAME;")
cpp_quote("typedef struct { long code; long param; } CODEPARAM;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const CODENAME const *LPCCODENAME;")
cpp_quote("typedef const CODEPARAM const *LPCCODEPARAM;")
cpp_quote("const short tcsPP_SizeOfParameterSet = 35;")
cpp_quote("#else")
cpp_quote("typedef CODENAME const *LPCCODENAME;")
cpp_quote("typedef CODEPARAM const *LPCCODEPARAM;")
cpp_quote("#define tcsPP_SizeOfParameterSet 35")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("typedef struct PARAMETERSET { double p[tcsPP_SizeOfParameterSet];} PARAMETERSET;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const PARAMETERSET const *LPCPARAMETERSET;")
cpp_quote("typedef struct { long code; PARAMETERSET p; } CODEPARAMSET;")
cpp_quote("typedef const CODEPARAMSET const *LPCCODEPARAMSET;")
cpp_quote("#else")
cpp_quote("typedef PARAMETERSET const *LPCPARAMETERSET;")
cpp_quote("typedef struct { long code; PARAMETERSET p; } CODEPARAMSET;")
cpp_quote("typedef CODEPARAMSET const *LPCCODEPARAMSET;")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("extern CODENAME _CT_TRIASCSUNITOFANGLE[];")

// @doc ENUM TRIASCS
// @enum TRIASCSUNITOFANGLE | TRIASCSUNITOFANGLE
typedef enum TRIASCSUNITOFANGLE {
	tcsUOA_Undefined = -1,		// @emem Wert ist nicht definiert
	tcsUOA_Radian = 9101,		// @emem radian
	tcsUOA_Degree = 9102,		// @emem degree
	tcsUOA_ArcMinute = 9103,	// @emem arc-minute
	tcsUOA_ArcSecond = 9104,	// @emem arc-second
	tcsUOA_Grad = 9105,			// @emem grad
	tcsUOA_Gon = 9106,			// @emem gon
	tcsUOA_DMS = 9107,			// @emem DMS
	tcsUOA_DMSH = 9108,			// @emem DMSH
	tcsUOA_Microradian = 9109,	// @emem microradian
	tcsUOA_DDDMMSSsss = 9110,	// @emem DDD.MMSSsss
	tcsUOA_Second = 32769,		// @emem Second
} TRIASCSUNITOFANGLE;
cpp_quote("extern CODENAME _CT_TRIASCSDTRANSALGORITHM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSDTRANSALGORITHM | TRIASCSDTRANSALGORITHM
typedef enum TRIASCSDTRANSALGORITHM {
	tcsDTA_Undefined = -1, // @emem Wert ist nicht definiert
	tcsDTA_LongitudeRotation = 9601, // @emem Longitude rotation
	tcsDTA_GeodeticGeocentricConversions = 9602, // @emem Geodetic/geocentric conversions
	tcsDTA_GeocentricTranslations = 9603, // @emem Geocentric translations
	tcsDTA_Molodenski = 9604, // @emem Molodenski
	tcsDTA_AbridgedMolodenski = 9605, // @emem Abridged Molodenski
	tcsDTA_PositionVector7ParamTransformation = 9606, // @emem Position Vector 7-param. transformation
	tcsDTA_CoordinateFrame7ParamTransformation = 9607, // @emem Coordinate Frame 7-param. transformation
	tcsDTA_SimilarityTransform = 9608, // @emem Similarity transform
	tcsDTA_2DimensionalAffineTransformation = 9609, // @emem 2-dimensional Affine transformation
	tcsDTA_2ndOrderPolynomialFunction = 9610, // @emem 2nd-order Polynomial function
	tcsDTA_3rdOrderPolynomialFunction = 9611, // @emem 3rd-order Polynomial function
	tcsDTA_4thOrderPolynomialFunction = 9612, // @emem 4th-order Polynomial function
	tcsDTA_NADCON = 9613, // @emem NADCON
	tcsDTA_CanadaNTv1 = 9614, // @emem Canada NTv1
	tcsDTA_CanadaNTv2 = 9615, // @emem Canada NTv2
	tcsDTA_VerticalOffset = 9616, // @emem Vertical Offset
} TRIASCSDTRANSALGORITHM;
cpp_quote("extern CODENAME _CT_TRIASCSELLIPSOID[];")

// @doc ENUM TRIASCS
// @enum TRIASCSELLIPSOID | TRIASCSELLIPSOID
typedef enum TRIASCSELLIPSOID {
	tcsEL_Undefined = -1, // @emem Wert ist nicht definiert
	tcsEL_Airy1830 = 7001, // @emem Airy 1830
	tcsEL_AiryModified1849 = 7002, // @emem Airy Modified 1849
	tcsEL_AustralianNationalSpheroid = 7003, // @emem Australian National Spheroid
	tcsEL_Bessel1841 = 7004, // @emem Bessel 1841
	tcsEL_BesselModified = 7005, // @emem Bessel Modified
	tcsEL_BesselNamibia = 7006, // @emem Bessel Namibia
	tcsEL_Clarke1858 = 7007, // @emem Clarke 1858
	tcsEL_Clarke1866 = 7008, // @emem Clarke 1866
	tcsEL_Clarke1866Michigan = 7009, // @emem Clarke 1866 Michigan
	tcsEL_Clarke1880Benoit = 7010, // @emem Clarke 1880 (Benoit)
	tcsEL_Clarke1880IGN = 7011, // @emem Clarke 1880 (IGN)
	tcsEL_Clarke1880RGS = 7012, // @emem Clarke 1880 (RGS)
	tcsEL_Clarke1880Arc = 7013, // @emem Clarke 1880 (Arc)
	tcsEL_Clarke1880SGA1922 = 7014, // @emem Clarke 1880 (SGA 1922)
	tcsEL_Everest18301937Adjustment = 7015, // @emem Everest 1830 (1937 Adjustment)
	tcsEL_Everest18301967Definition = 7016, // @emem Everest 1830 (1967 Definition)
	tcsEL_Everest18301975Definition = 7017, // @emem Everest 1830 (1975 Definition)
	tcsEL_Everest1830Modified = 7018, // @emem Everest 1830 Modified
	tcsEL_GRS1980 = 7019, // @emem GRS 1980
	tcsEL_Helmert1906 = 7020, // @emem Helmert 1906
	tcsEL_IndonesianNationalSpheroid = 7021, // @emem Indonesian National Spheroid
	tcsEL_International1924 = 7022, // @emem International 1924
	tcsEL_Krassowsky1940 = 7024, // @emem Krassowsky 1940
	tcsEL_NWL9D = 7025, // @emem NWL 9D
	tcsEL_NWL10D = 7026, // @emem NWL 10D
	tcsEL_Plessis1817 = 7027, // @emem Plessis 1817
	tcsEL_Struve1860 = 7028, // @emem Struve 1860
	tcsEL_WarOffice = 7029, // @emem War Office
	tcsEL_WGS84 = 7030, // @emem WGS 84
	tcsEL_GEM10C = 7031, // @emem GEM 10C
	tcsEL_OSU86F = 7032, // @emem OSU86F
	tcsEL_OSU91A = 7033, // @emem OSU91A
	tcsEL_Clarke1880 = 7034, // @emem Clarke 1880
	tcsEL_Sphere = 7035, // @emem Sphere
	tcsEL_GRS1967 = 7036, // @emem GRS 1967
	tcsEL_AverageTerrestrialSystem1977 = 7041, // @emem Average Terrestrial System 1977
	tcsEL_UserDefined = 32769,  // @emem User Defined
} TRIASCSELLIPSOID;
cpp_quote("extern CODENAME _CT_TRIASCSGEODETICDATUM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSGEODETICDATUM | TRIASCSGEODETICDATUM
typedef enum TRIASCSGEODETICDATUM {
	tcsGD_Undefined = -1, // @emem Wert ist nicht definiert
	tcsGD_NotSpecifiedBasedOnEllipsoid7001 = 6001, // @emem Not specified (based on ellipsoid 7001)
	tcsGD_NotSpecifiedBasedOnEllipsoid7002 = 6002, // @emem Not specified (based on ellipsoid 7002)
	tcsGD_NotSpecifiedBasedOnEllipsoid7003 = 6003, // @emem Not specified (based on ellipsoid 7003)
	tcsGD_NotSpecifiedBasedOnEllipsoid7004 = 6004, // @emem Not specified (based on ellipsoid 7004)
	tcsGD_NotSpecifiedBasedOnEllipsoid7005 = 6005, // @emem Not specified (based on ellipsoid 7005)
	tcsGD_NotSpecifiedBasedOnEllipsoid7006 = 6006, // @emem Not specified (based on ellipsoid 7006)
	tcsGD_NotSpecifiedBasedOnEllipsoid7007 = 6007, // @emem Not specified (based on ellipsoid 7007)
	tcsGD_NotSpecifiedBasedOnEllipsoid7008 = 6008, // @emem Not specified (based on ellipsoid 7008)
	tcsGD_NotSpecifiedBasedOnEllipsoid7009 = 6009, // @emem Not specified (based on ellipsoid 7009)
	tcsGD_NotSpecifiedBasedOnEllipsoid7010 = 6010, // @emem Not specified (based on ellipsoid 7010)
	tcsGD_NotSpecifiedBasedOnEllipsoid7011 = 6011, // @emem Not specified (based on ellipsoid 7011)
	tcsGD_NotSpecifiedBasedOnEllipsoid7012 = 6012, // @emem Not specified (based on ellipsoid 7012)
	tcsGD_NotSpecifiedBasedOnEllipsoid7013 = 6013, // @emem Not specified (based on ellipsoid 7013)
	tcsGD_NotSpecifiedBasedOnEllipsoid7014 = 6014, // @emem Not specified (based on ellipsoid 7014)
	tcsGD_NotSpecifiedBasedOnEllipsoid7015 = 6015, // @emem Not specified (based on ellipsoid 7015)
	tcsGD_NotSpecifiedBasedOnEllipsoid7016 = 6016, // @emem Not specified (based on ellipsoid 7016)
	tcsGD_NotSpecifiedBasedOnEllipsoid7017 = 6017, // @emem Not specified (based on ellipsoid 7017)
	tcsGD_NotSpecifiedBasedOnEllipsoid7018 = 6018, // @emem Not specified (based on ellipsoid 7018)
	tcsGD_NotSpecifiedBasedOnEllipsoid7019 = 6019, // @emem Not specified (based on ellipsoid 7019)
	tcsGD_NotSpecifiedBasedOnEllipsoid7020 = 6020, // @emem Not specified (based on ellipsoid 7020)
	tcsGD_NotSpecifiedBasedOnEllipsoid7021 = 6021, // @emem Not specified (based on ellipsoid 7021)
	tcsGD_NotSpecifiedBasedOnEllipsoid7022 = 6022, // @emem Not specified (based on ellipsoid 7022)
	tcsGD_NotSpecifiedBasedOnEllipsoid7024 = 6024, // @emem Not specified (based on ellipsoid 7024)
	tcsGD_NotSpecifiedBasedOnEllipsoid7025 = 6025, // @emem Not specified (based on ellipsoid 7025)
	tcsGD_NotSpecifiedBasedOnEllipsoid7026 = 6026, // @emem Not specified (based on ellipsoid 7026)
	tcsGD_NotSpecifiedBasedOnEllipsoid7027 = 6027, // @emem Not specified (based on ellipsoid 7027)
	tcsGD_NotSpecifiedBasedOnEllipsoid7028 = 6028, // @emem Not specified (based on ellipsoid 7028)
	tcsGD_NotSpecifiedBasedOnEllipsoid7029 = 6029, // @emem Not specified (based on ellipsoid 7029)
	tcsGD_NotSpecifiedBasedOnEllipsoid7030 = 6030, // @emem Not specified (based on ellipsoid 7030)
	tcsGD_NotSpecifiedBasedOnEllipsoid7031 = 6031, // @emem Not specified (based on ellipsoid 7031)
	tcsGD_NotSpecifiedBasedOnEllipsoid7032 = 6032, // @emem Not specified (based on ellipsoid 7032)
	tcsGD_NotSpecifiedBasedOnEllipsoid7033 = 6033, // @emem Not specified (based on ellipsoid 7033)
	tcsGD_NotSpecifiedBasedOnEllipsoid7034 = 6034, // @emem Not specified (based on ellipsoid 7034)
	tcsGD_NotSpecifiedBasedOnEllipsoid7035 = 6035, // @emem Not specified (based on ellipsoid 7035)
	tcsGD_NotSpecifiedBasedOnEllipsoid7036 = 6036, // @emem Not specified (based on ellipsoid 7036)
	tcsGD_Greek = 6120, // @emem Greek
	tcsGD_GreekGeodeticReferenceSystem1987 = 6121, // @emem Greek Geodetic Reference System 1987
	tcsGD_AverageTerrestrialSystem1977 = 6122, // @emem Average Terrestrial System 1977
	tcsGD_Kartastokoordinaattijarjestelma = 6123, // @emem Kartastokoordinaattijarjestelma
	tcsGD_RiketsKoordinatsystem1990 = 6124, // @emem Rikets koordinatsystem 1990
	tcsGD_Samboja = 6125, // @emem Samboja
	tcsGD_Lithuania1994ETRS89 = 6126, // @emem Lithuania 1994 (ETRS89)
	tcsGD_Pulkovo1995 = 6200, // @emem Pulkovo 1995
	tcsGD_Adindan = 6201, // @emem Adindan
	tcsGD_AustralianGeodeticDatum1966 = 6202, // @emem Australian Geodetic Datum 1966
	tcsGD_AustralianGeodeticDatum1984 = 6203, // @emem Australian Geodetic Datum 1984
	tcsGD_AinElAbd1970 = 6204, // @emem Ain el Abd 1970
	tcsGD_Afgooye = 6205, // @emem Afgooye
	tcsGD_Agadez = 6206, // @emem Agadez
	tcsGD_Lisbon = 6207, // @emem Lisbon
	tcsGD_Aratu = 6208, // @emem Aratu
	tcsGD_Arc1950 = 6209, // @emem Arc 1950
	tcsGD_Arc1960 = 6210, // @emem Arc 1960
	tcsGD_Batavia = 6211, // @emem Batavia
	tcsGD_Barbados = 6212, // @emem Barbados
	tcsGD_Beduaram = 6213, // @emem Beduaram
	tcsGD_Beijing1954 = 6214, // @emem Beijing 1954
	tcsGD_ReseauNationalBelge1950 = 6215, // @emem Reseau National Belge 1950
	tcsGD_Bermuda1957 = 6216, // @emem Bermuda 1957
	tcsGD_Bern1898 = 6217, // @emem Bern 1898
	tcsGD_Bogota = 6218, // @emem Bogota
	tcsGD_BukitRimpah = 6219, // @emem Bukit Rimpah
	tcsGD_Camacupa = 6220, // @emem Camacupa
	tcsGD_CampoInchauspe = 6221, // @emem Campo Inchauspe
	tcsGD_Cape = 6222, // @emem Cape
	tcsGD_Carthage = 6223, // @emem Carthage
	tcsGD_Chua = 6224, // @emem Chua
	tcsGD_CorregoAlegre = 6225, // @emem Corrego Alegre
	tcsGD_CoteDIvoire = 6226, // @emem Cote d'Ivoire
	tcsGD_DeirEzZor = 6227, // @emem Deir ez Zor
	tcsGD_Douala = 6228, // @emem Douala
	tcsGD_Egypt1907 = 6229, // @emem Egypt 1907
	tcsGD_EuropeanDatum1950 = 6230, // @emem European Datum 1950
	tcsGD_EuropeanDatum1987 = 6231, // @emem European Datum 1987
	tcsGD_Fahud = 6232, // @emem Fahud
	tcsGD_Gandajika1970 = 6233, // @emem Gandajika 1970
	tcsGD_Garoua = 6234, // @emem Garoua
	tcsGD_GuyaneFrancaise = 6235, // @emem Guyane Francaise
	tcsGD_HuTzuShan = 6236, // @emem Hu Tzu Shan
	tcsGD_HungarianDatum1972 = 6237, // @emem Hungarian Datum 1972
	tcsGD_IndonesianDatum1974 = 6238, // @emem Indonesian Datum 1974
	tcsGD_Indian1954 = 6239, // @emem Indian 1954
	tcsGD_Indian1975 = 6240, // @emem Indian 1975
	tcsGD_Jamaica1875 = 6241, // @emem Jamaica 1875
	tcsGD_Jamaica1969 = 6242, // @emem Jamaica 1969
	tcsGD_Kalianpur = 6243, // @emem Kalianpur
	tcsGD_Kandawala = 6244, // @emem Kandawala
	tcsGD_Kertau = 6245, // @emem Kertau
	tcsGD_KuwaitOilCompany = 6246, // @emem Kuwait Oil Company
	tcsGD_LaCanoa = 6247, // @emem La Canoa
	tcsGD_ProvisionalSouthAmericanDatum1956 = 6248, // @emem Provisional South American Datum 1956
	tcsGD_Lake = 6249, // @emem Lake
	tcsGD_Leigon = 6250, // @emem Leigon
	tcsGD_Liberia1964 = 6251, // @emem Liberia 1964
	tcsGD_Lome = 6252, // @emem Lome
	tcsGD_Luzon1911 = 6253, // @emem Luzon 1911
	tcsGD_HitoXVIII1963 = 6254, // @emem Hito XVIII 1963
	tcsGD_HeratNorth = 6255, // @emem Herat North
	tcsGD_Mahe1971 = 6256, // @emem Mahe 1971
	tcsGD_Makassar = 6257, // @emem Makassar
	tcsGD_EuropeanTerrestrialReferenceSystem89 = 6258, // @emem European Terrestrial Reference System 89
	tcsGD_Malongo1987 = 6259, // @emem Malongo 1987
	tcsGD_Manoca = 6260, // @emem Manoca
	tcsGD_Merchich = 6261, // @emem Merchich
	tcsGD_Massawa = 6262, // @emem Massawa
	tcsGD_Minna = 6263, // @emem Minna
	tcsGD_Mhast = 6264, // @emem Mhast
	tcsGD_MonteMario = 6265, // @emem Monte Mario
	tcsGD_MPoraloko = 6266, // @emem M'poraloko
	tcsGD_NorthAmericanDatum1927 = 6267, // @emem North American Datum 1927
	tcsGD_NADMichigan = 6268, // @emem NAD Michigan
	tcsGD_NorthAmericanDatum1983 = 6269, // @emem North American Datum 1983
	tcsGD_Nahrwan1967 = 6270, // @emem Nahrwan 1967
	tcsGD_Naparima1972 = 6271, // @emem Naparima 1972
	tcsGD_NewZealandGeodeticDatum1949 = 6272, // @emem New Zealand Geodetic Datum 1949
	tcsGD_NGO1948 = 6273, // @emem NGO 1948
	tcsGD_Datum73 = 6274, // @emem Datum 73
	tcsGD_NouvelleTriangulationFrancaise = 6275, // @emem Nouvelle Triangulation Francaise
	tcsGD_NSWC9Z2 = 6276, // @emem NSWC 9Z-2
	tcsGD_OSGB1936 = 6277, // @emem OSGB 1936
	tcsGD_OSGB1970SN = 6278, // @emem OSGB 1970 (SN)
	tcsGD_OSSN1980 = 6279, // @emem OS (SN) 1980
	tcsGD_Padang1884 = 6280, // @emem Padang 1884
	tcsGD_Palestine1923 = 6281, // @emem Palestine 1923
	tcsGD_PointeNoire = 6282, // @emem Pointe Noire
	tcsGD_GeocentricDatumOfAustralia1994 = 6283, // @emem Geocentric Datum of Australia 1994
	tcsGD_Pulkovo1942 = 6284, // @emem Pulkovo 1942
	tcsGD_Qatar = 6285, // @emem Qatar
	tcsGD_Qatar1948 = 6286, // @emem Qatar 1948
	tcsGD_Qornoq = 6287, // @emem Qornoq
	tcsGD_LomaQuintana = 6288, // @emem Loma Quintana
	tcsGD_Amersfoort = 6289, // @emem Amersfoort
	tcsGD_SouthAmericanDatum1969 = 6291, // @emem South American Datum 1969
	tcsGD_SapperHill1943 = 6292, // @emem Sapper Hill 1943
	tcsGD_Schwarzeck = 6293, // @emem Schwarzeck
	tcsGD_Segora = 6294, // @emem Segora
	tcsGD_Serindung = 6295, // @emem Serindung
	tcsGD_Sudan = 6296, // @emem Sudan
	tcsGD_Tananarive1925 = 6297, // @emem Tananarive 1925
	tcsGD_Timbalai1948 = 6298, // @emem Timbalai 1948
	tcsGD_TM65 = 6299, // @emem TM65
	tcsGD_TM75 = 6300, // @emem TM75
	tcsGD_Tokyo = 6301, // @emem Tokyo
	tcsGD_Trinidad1903 = 6302, // @emem Trinidad 1903
	tcsGD_TrucialCoast1948 = 6303, // @emem Trucial Coast 1948
	tcsGD_Voirol1875 = 6304, // @emem Voirol 1875
	tcsGD_VoirolUnifie1960 = 6305, // @emem Voirol Unifie 1960
	tcsGD_Bern1938 = 6306, // @emem Bern 1938
	tcsGD_NordSahara1959 = 6307, // @emem Nord Sahara 1959
	tcsGD_Stockholm1938 = 6308, // @emem Stockholm 1938
	tcsGD_Yacare = 6309, // @emem Yacare
	tcsGD_Yoff = 6310, // @emem Yoff
	tcsGD_Zanderij = 6311, // @emem Zanderij
	tcsGD_MilitarGeographischeInstitut = 6312, // @emem Militar-Geographische Institut
	tcsGD_ReseauNationalBelge1972 = 6313, // @emem Reseau National Belge 1972
	tcsGD_DeutscheHauptdreiecksnetz = 6314, // @emem Deutsche Hauptdreiecksnetz
	tcsGD_Conakry1905 = 6315, // @emem Conakry 1905
	tcsGD_DealulPiscului1933 = 6316, // @emem Dealul Piscului 1933
	tcsGD_DealulPiscului1970 = 6317, // @emem Dealul Piscului 1970
	tcsGD_NationalGeodeticNetwork = 6318, // @emem National Geodetic Network
	tcsGD_KuwaitUtility = 6319, // @emem Kuwait Utility
	tcsGD_WorldGeodeticSystem1972 = 6322, // @emem World Geodetic System 1972
	tcsGD_WGS72TransitBroadcastEphemeris = 6324, // @emem WGS 72 Transit Broadcast Ephemeris
	tcsGD_WorldGeodeticSystem1984 = 6326, // @emem World Geodetic System 1984
	tcsGD_AncienneTriangulationFrancaise = 6901, // @emem Ancienne Triangulation Francaise
	tcsGD_NordDeGuerre = 6902, // @emem Nord de Guerre

// #HK020228
// Dreiteilung des Festpunktnetzes (alte Bundesländer)
	tcsGD_DeutscheHauptdreiecksnetzAblN = 6903, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Nord (55°-52°20')
	tcsGD_DeutscheHauptdreiecksnetzAblM = 6904, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Mitte (52°20'-50°20')
	tcsGD_DeutscheHauptdreiecksnetzAblS = 6905, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Süd (50°20'-47°)

// Neue Bundesländer
	tcsGD_DeutscheHauptdreiecksnetzRd83 = 6906, // @emem Deutsche Hauptdreiecksnetz, neue Bundesländer 
	tcsGD_DeutscheHauptdreiecksnetzPd83 = 6907, // @emem Deutsche Hauptdreiecksnetz, Thüringen

// #HK020419
// Alle Festpunkte berücksichtigt
	tcsGD_DeutscheHauptdreiecksnetzRd83DHDN = 6908, // @emem Deutsche Hauptdreiecksnetz RD83 (neu)

// Zweiteilung des Festpunktnetzes (alte Bundesländer)
	tcsGD_DeutscheHauptdreiecksnetzAblN2 = 6909, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Nord (zweigeteilt) (55°-51°)
	tcsGD_DeutscheHauptdreiecksnetzAblS2 = 6910, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Süd (zweigeteilt) (51°-47°)

// Alte Bundesländer Gesamt
	tcsGD_DeutscheHauptdreiecksnetzDHDN = 6911, // @emem Alte Bundesländer gesamt RD83 (neu)

// Überbreite Zone für Deutschland (GeoStar)
	tcsGD_DeutscheHauptdreiecksnetzBesD = 6912, // @emem Überbreite Zone für Deutschland (GeoStar)

	tcsGD_UserDefined = 32769,  // @emem User Defined
} TRIASCSGEODETICDATUM;
cpp_quote("extern CODENAME _CT_TRIASCSUNITOFLENGTH[];")

// @doc ENUM TRIASCS
// @enum TRIASCSUNITOFLENGTH | TRIASCSUNITOFLENGTH
typedef enum TRIASCSUNITOFLENGTH {
	tcsUOL_Undefined = -1, // @emem Wert ist nicht definiert
	tcsUOL_Metre = 9001, // @emem metre
	tcsUOL_MilliMetre = 90011, // @emem metre
	tcsUOL_KiloMetre = 90012, // @emem metre
	tcsUOL_Foot = 9002, // @emem foot
	tcsUOL_USSurveyFoot = 9003, // @emem US survey foot
	tcsUOL_ModifiedAmericanFoot = 9004, // @emem modified American foot
	tcsUOL_ClarkeSFoot = 9005, // @emem Clarke's foot
	tcsUOL_IndianFootClarke = 9006, // @emem Indian foot (Clarke)
	tcsUOL_Link = 9007, // @emem link
	tcsUOL_LinkBenoit = 9008, // @emem link (Benoit)
	tcsUOL_LinkSears = 9009, // @emem link (Sears)
	tcsUOL_ChainBenoit = 9010, // @emem chain (Benoit)
	tcsUOL_ChainSears = 9011, // @emem chain (Sears)
	tcsUOL_YardSears = 9012, // @emem yard (Sears)
	tcsUOL_IndianYard = 9013, // @emem Indian yard
	tcsUOL_Fathom = 9014, // @emem fathom
	tcsUOL_NauticalMile = 9030, // @emem nautical mile
	tcsUOL_GermanLegalMetre = 9031, // @emem German legal metre
	tcsUOL_FootSears = 9032, // @emem foot (Sears)
	tcsUOL_USSurveyChain = 9033, // @emem US survey chain
	tcsUOL_USSurveyLink = 9034, // @emem US survey link
	tcsUOL_USSurveyMile = 9035, // @emem US survey mile
	tcsUOL_Inch = 90013,	// @emem inch
	tcsUOL_CentiMetre = 90014, // @emem centimetre
} TRIASCSUNITOFLENGTH;
cpp_quote("extern CODENAME _CT_TRIASCSPRIMEMERIDIAN[];")

// @doc ENUM TRIASCS
// @enum TRIASCSPRIMEMERIDIAN | TRIASCSPRIMEMERIDIAN
typedef enum TRIASCSPRIMEMERIDIAN {
	tcsPM_Undefined = -1, // @emem Wert ist nicht definiert
	tcsPM_Greenwich = 8901, // @emem Greenwich
	tcsPM_Lisbon = 8902, // @emem Lisbon
	tcsPM_Paris = 8903, // @emem Paris
	tcsPM_Bogota = 8904, // @emem Bogota
	tcsPM_Madrid = 8905, // @emem Madrid
	tcsPM_Rome = 8906, // @emem Rome
	tcsPM_Bern = 8907, // @emem Bern
	tcsPM_Jakarta = 8908, // @emem Jakarta
	tcsPM_Ferro = 8909, // @emem Ferro
	tcsPM_Brussels = 8910, // @emem Brussels
	tcsPM_Stockholm = 8911, // @emem Stockholm
	tcsPM_Athens = 8912, // @emem Athens
} TRIASCSPRIMEMERIDIAN;
cpp_quote("extern CODENAME _CT_TRIASCSPROJECTIONALGORITHM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSPROJECTIONALGORITHM | TRIASCSPROJECTIONALGORITHM
typedef enum TRIASCSPROJECTIONALGORITHM {
	tcsPA_Undefined = -1, // @emem Wert ist nicht definiert
	tcsPA_LambertConicConformal1SP = 9801, // @emem Lambert Conic Conformal (1SP)
	tcsPA_LambertConicConformal2SP = 9802, // @emem Lambert Conic Conformal (2SP)
	tcsPA_LambertConicConformal2SPBelgium = 9803, // @emem Lambert Conic Conformal (2SP Belgium)
	tcsPA_Mercator1SP = 9804, // @emem Mercator (1SP)
	tcsPA_Mercator2SP = 9805, // @emem Mercator (2SP)
	tcsPA_CassiniSoldner = 9806, // @emem Cassini-Soldner
	tcsPA_TransverseMercator = 9807, // @emem Transverse Mercator
	tcsPA_TransverseMercatorSouthOrientated = 9808, // @emem Transverse Mercator (South Orientated)
	tcsPA_ObliqueStereographic = 9809, // @emem Oblique Stereographic
	tcsPA_PolarStereographic = 9810, // @emem Polar Stereographic
	tcsPA_NewZealandMapGrid = 9811, // @emem New Zealand Map Grid
	tcsPA_HotineObliqueMercator = 9812, // @emem Hotine Oblique Mercator
	tcsPA_LabordeObliqueMercator = 9813, // @emem Laborde Oblique Mercator
	tcsPA_SwissObliqueCylindrical = 9814, // @emem Swiss Oblique Cylindrical
	tcsPA_ObliqueMercator = 9815, // @emem Oblique Mercator
	tcsPA_AffineTransformation = 32770,  // @emem Affine Transformation
	tcsPA_GaussKrueger = 32769,  // @emem Gauss Krüger
	tcsPA_CylindricEquirectangular = 32771,  // @emem Cylindric Equirectangular
} TRIASCSPROJECTIONALGORITHM;

// @doc ENUM TRIASCS
// @enum TRIASCSPROJECTIONPARAMETER | TRIASCSPROJECTIONPARAMETER
typedef enum TRIASCSPROJECTIONPARAMETER {
	tcsPP_Undefined = -1, // @emem Wert ist nicht definiert
// @xref <l Cassini-Soldner>
	tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Cassini-Soldner>
	tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Cassini-Soldner>
	tcsPP_CassiniSoldner_FalseEasting = 5, // @emem False easting <l Cassini-Soldner>
	tcsPP_CassiniSoldner_FalseNorthing = 6, // @emem False northing <l Cassini-Soldner>
// @xref <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_AngleFromRectifiedToSkewGrid = 3, // @emem Angle from Rectified to Skew Grid <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_FalseEasting = 5, // @emem False easting <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_FalseNorthing = 6, // @emem False northing <l Hotine Oblique Mercator>
// @xref <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_FalseEasting = 5, // @emem False easting <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_FalseNorthing = 6, // @emem False northing <l Laborde Oblique Mercator>
// @xref <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_FalseEasting = 5, // @emem False easting <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_FalseNorthing = 6, // @emem False northing <l Lambert Conic Conformal (1SP)>
// @xref <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfSecondStandardParallel = 1, // @emem Latitude of second standard parallel <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfFalseOrigin = 2, // @emem Latitude of false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LongitudeOfFalseOrigin = 3, // @emem Longitude of false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_EastingAtFalseOrigin = 5, // @emem Easting at false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_NorthingAtFalseOrigin = 6, // @emem Northing at false origin <l Lambert Conic Conformal (2SP)>
// @xref <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfSecondStandardParallel = 1, // @emem Latitude of second standard parallel <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfFalseOrigin = 2, // @emem Latitude of false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LongitudeOfFalseOrigin = 3, // @emem Longitude of false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_EastingAtFalseOrigin = 5, // @emem Easting at false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_NorthingAtFalseOrigin = 6, // @emem Northing at false origin <l Lambert Conic Conformal (2SP Belgium)>
// @xref <l Mercator (1SP)>
	tcsPP_Mercator1SP_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_FalseEasting = 5, // @emem False easting <l Mercator (1SP)>
	tcsPP_Mercator1SP_FalseNorthing = 6, // @emem False northing <l Mercator (1SP)>
// @xref <l Mercator (2SP)>
	tcsPP_Mercator2SP_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Mercator (2SP)>
	tcsPP_Mercator2SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Mercator (2SP)>
	tcsPP_Mercator2SP_FalseEasting = 5, // @emem False easting <l Mercator (2SP)>
	tcsPP_Mercator2SP_FalseNorthing = 6, // @emem False northing <l Mercator (2SP)>
// @xref <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_FalseEasting = 5, // @emem False easting <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_FalseNorthing = 6, // @emem False northing <l New Zealand Map Grid>
// @xref <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_FalseEasting = 5, // @emem False easting <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_FalseNorthing = 6, // @emem False northing <l Oblique Stereographic>
// @xref <l Polar Stereographic>
	tcsPP_PolarStereographic_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_FalseEasting = 5, // @emem False easting <l Polar Stereographic>
	tcsPP_PolarStereographic_FalseNorthing = 6, // @emem False northing <l Polar Stereographic>
// @xref <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_EastingAtProjectionCentre = 5, // @emem Easting at projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_NorthingAtProjectionCentre = 6, // @emem Northing at projection centre <l Swiss Oblique Cylindrical>
// @xref <l Transverse Mercator>
	tcsPP_TransverseMercator_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_FalseEasting = 5, // @emem False easting <l Transverse Mercator>
	tcsPP_TransverseMercator_FalseNorthing = 6, // @emem False northing <l Transverse Mercator>
	tcsPP_TransverseMercator_ZoneWidth = 7, // @emem Automatically calculate correct origin based on this zone width <l Transverse Mercator>
// @xref <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_FalseEasting = 5, // @emem False easting <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_FalseNorthing = 6, // @emem False northing <l Transverse Mercator (South Orientated)>
// @xref <l Oblique Mercator>
	tcsPP_ObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Oblique Mercator>
	tcsPP_ObliqueMercator_AngleFromRectifiedToSkewGrid = 3, // @emem Angle from Rectified to Skew Grid <l Oblique Mercator>
	tcsPP_ObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Oblique Mercator>
	tcsPP_ObliqueMercator_EastingAtProjectionCentre = 5, // @emem Easting at projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_NorthingAtProjectionCentre = 6, // @emem Northing at projection centre <l Oblique Mercator>
// @xref <l Affine Transformation>
	tcsPP_AffineTransformation_OffsetX = 15, // @emem OffsetX <l Affine Transformation>
	tcsPP_AffineTransformation_OffsetY = 16, // @emem OffsetY <l Affine Transformation>
	tcsPP_AffineTransformation_RotatePhi = 3, // @emem RotatePhi <l Affine Transformation>
	tcsPP_AffineTransformation_ScaleX = 0, // @emem ScaleX <l Affine Transformation>
	tcsPP_AffineTransformation_ScaleY = 1, // @emem ScaleY <l Affine Transformation>
// @xref <l Gauss Krüger>
	tcsPP_GaussKrueger_FalseEasting = tcsPP_TransverseMercator_FalseEasting, // @emem False easting <l Gauss Krüger>
	tcsPP_GaussKrueger_FalseNorthing = tcsPP_TransverseMercator_FalseNorthing, // @emem False northing <l Gauss Krüger>
	tcsPP_GaussKrueger_LatitudeOfNaturalOrigin = tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, // @emem Latitude of natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_LongitudeOfNaturalOrigin = tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, // @emem Longitude of natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin = tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin, // @emem Scale factor at natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_ZoneWidth = tcsPP_TransverseMercator_ZoneWidth, // @emem Automatically calculate correct origin based on this zone width <l Gauss Krüger>
// @xref <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_FalseEasting = tcsPP_TransverseMercator_FalseEasting, // @emem False easting <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_FalseNorthing = tcsPP_TransverseMercator_FalseNorthing, // @emem False northing <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin = tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, // @emem Latitude of natural origin <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin = tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, // @emem Longitude of natural origin <l Cylindric Equirectangular>
} TRIASCSPROJECTIONPARAMETER;

// @doc ENUM TRIASCS
// @enum TRIASCSDTRANSPARAMETER | TRIASCSDTRANSPARAMETER
typedef enum TRIASCSDTRANSPARAMETER {
	tcsDTP_Undefined = -1, // @emem Wert ist nicht definiert
// @xref <l Longitude rotation>
	tcsDTP_LongitudeRotation_LongitudeRotation = 0, // @emem Longitude rotation <l Longitude rotation>
// @xref <l Geodetic/geocentric conversions>
// @xref <l Geocentric translations>
	tcsDTP_GeocentricTranslations_XAxisTranslation = 0, // @emem X-axis translation <l Geocentric translations>
	tcsDTP_GeocentricTranslations_YAxisTranslation = 1, // @emem Y-axis translation <l Geocentric translations>
	tcsDTP_GeocentricTranslations_ZAxisTranslation = 2, // @emem Z-axis translation <l Geocentric translations>
// @xref <l Molodenski>
	tcsDTP_Molodenski_XAxisTranslation = 0, // @emem X-axis translation <l Molodenski>
	tcsDTP_Molodenski_YAxisTranslation = 1, // @emem Y-axis translation <l Molodenski>
	tcsDTP_Molodenski_ZAxisTranslation = 2, // @emem Z-axis translation <l Molodenski>
	tcsDTP_Molodenski_SemiMajorAxisLengthDifference = 3, // @emem Semi-major axis length difference <l Molodenski>
	tcsDTP_Molodenski_FlatteningDifference = 4, // @emem Flattening difference <l Molodenski>
// @xref <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_XAxisTranslation = 0, // @emem X-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_YAxisTranslation = 1, // @emem Y-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_ZAxisTranslation = 2, // @emem Z-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_SemiMajorAxisLengthDifference = 3, // @emem Semi-major axis length difference <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_FlatteningDifference = 4, // @emem Flattening difference <l Abridged Molodenski>
// @xref <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_XAxisTranslation = 0, // @emem X-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_YAxisTranslation = 1, // @emem Y-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ZAxisTranslation = 2, // @emem Z-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_XAxisRotation = 3, // @emem X-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_YAxisRotation = 4, // @emem Y-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ZAxisRotation = 5, // @emem Z-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ScaleDifference = 6, // @emem Scale difference <l Position Vector 7-param transformation>
// @xref <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_XAxisTranslation = 0, // @emem X-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_YAxisTranslation = 1, // @emem Y-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ZAxisTranslation = 2, // @emem Z-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_XAxisRotation = 3, // @emem X-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_YAxisRotation = 4, // @emem Y-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ZAxisRotation = 5, // @emem Z-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ScaleDifference = 6, // @emem Scale difference <l Coordinate Frame 7-param transformation>
// @xref <l Similarity transform>
	tcsDTP_SimilarityTransform_A1 = 0, // @emem A1 <l Similarity transform>
	tcsDTP_SimilarityTransform_A2M = 1, // @emem A2 * m <l Similarity transform>
	tcsDTP_SimilarityTransform_A3N = 2, // @emem A3 * n <l Similarity transform>
	tcsDTP_SimilarityTransform_B1 = 3, // @emem B1 <l Similarity transform>
	tcsDTP_SimilarityTransform_B2M = 4, // @emem B2 * m <l Similarity transform>
	tcsDTP_SimilarityTransform_B3N = 5, // @emem B3 * n <l Similarity transform>
// @xref <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A1 = 0, // @emem A1 <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A2M = 1, // @emem A2 * m <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A3N = 2, // @emem A3 * n <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B1 = 3, // @emem B1 <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B2M = 4, // @emem B2 * m <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B3N = 5, // @emem B3 * n <l 2-dimensional Affine transformation>
// @xref <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B1 = 10, // @emem B1 <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B2M = 11, // @emem B2 * m <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B3N = 12, // @emem B3 * n <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B4Mm = 13, // @emem B4 * mm <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A1 = 4, // @emem A1 <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B5Mn = 14, // @emem B5 * mn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B6Nn = 15, // @emem B6 * nn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 2nd-order Polynomial function>
// @xref <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B6Nn = 19, // @emem B6 * nn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A7Mmm = 10, // @emem A7 * mmm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A8Mmn = 11, // @emem A8 * mmn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B7Mmm = 20, // @emem B7 * mmm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B8Mmn = 21, // @emem B8 * mmn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A9Mnn = 12, // @emem A9 * mnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A10Nnn = 13, // @emem A10 * nnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B9Mnn = 22, // @emem B9 * mnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B10Nnn = 23, // @emem B10 * nnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B1 = 14, // @emem B1 <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B2M = 15, // @emem B2 * m <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B3N = 16, // @emem B3 * n <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B4Mm = 17, // @emem B4 * mm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B5Mn = 18, // @emem B5 * mn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A1 = 4, // @emem A1 <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 3rd-order Polynomial function>
// @xref <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B1 = 19, // @emem B1 <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A7Mmm = 10, // @emem A7 * mmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B11Mmmm = 29, // @emem B11 * mmmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A8Mmn = 11, // @emem A8 * mmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B2M = 20, // @emem B2 * m <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B3N = 21, // @emem B3 * n <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B12Mmmn = 30, // @emem B12 * mmmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A9Mnn = 12, // @emem A9 * mnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B13Mmnn = 31, // @emem B13 * mmnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A10Nnn = 13, // @emem A10 * nnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B4Mm = 22, // @emem B4 * mm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B5Mn = 23, // @emem B5 * mn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B14Mnnn = 32, // @emem B14 * mnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A11Mmmm = 14, // @emem A11 * mmmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B15Nnnn = 33, // @emem B15 * nnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A12Mmmn = 15, // @emem A12 * mmmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B6Nn = 24, // @emem B6 * nn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B7Mmm = 25, // @emem B7 * mmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A13Mmnn = 16, // @emem A13 * mmnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A14Mnnn = 17, // @emem A14 * mnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B8Mmn = 26, // @emem B8 * mmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B9Mnn = 27, // @emem B9 * mnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A15Nnnn = 18, // @emem A15 * nnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B10Nnn = 28, // @emem B10 * nnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A1 = 4, // @emem A1 <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 4th-order Polynomial function>
// @xref <l NADCON>
// @xref <l Vertical Offset>
	tcsDTP_VerticalOffset_VerticalOffset = 0, // @emem Vertical offset <l Vertical Offset>
// @xref <l Canada NTv1>
// @xref <l Canada NTv2>
} TRIASCSDTRANSPARAMETER;

cpp_quote("extern CODEPARAM _PT_ELLIPSFROMGD[];")
cpp_quote("extern CODEPARAMSET _PT_ELLIPSPARAM[];")
cpp_quote("typedef struct PA_ATTRIBUTESET { TRIASCSPROJECTIONALGORITHM pa; TRIASCSPROJECTIONPARAMETER pp; LPCTSTR value; } PA_ATTRIBUTESET;")
cpp_quote("typedef struct DT_ATTRIBUTESET { TRIASCSDTRANSALGORITHM ta; TRIASCSDTRANSPARAMETER tp; LPCTSTR value; } DT_ATTRIBUTESET;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const PA_ATTRIBUTESET const *LPCPA_ATTRIBUTESET;")
cpp_quote("typedef const DT_ATTRIBUTESET const *LPCDT_ATTRIBUTESET;")
cpp_quote("#else")
cpp_quote("typedef PA_ATTRIBUTESET const *LPCPA_ATTRIBUTESET;")
cpp_quote("typedef DT_ATTRIBUTESET const *LPCDT_ATTRIBUTESET;")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("extern DT_ATTRIBUTESET _DT_ATTRIBUTES[];")
cpp_quote("extern PA_ATTRIBUTESET _PA_ATTRIBUTES[];")

#endif // !defined(_EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_)
