#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef pair< const long, TAG> tagPair;

typedef map< long, CString, less<long> > stringMap;
extern stringMap	dataTypeMap;

typedef enum {
	FMT_NDAT = -1,
	FMT_BYTE = 1,
	FMT_SHORT = 2,
	FMT_LONG = 3,
	FMT_BORS = 4,			// Byte or Short
	FMT_SORL = 5,			// Short or Long
	FMT_ASCII = 6,
	FMT_ARRY = 7,
	FMT_RATIO = 8,
	FMT_ANY = 9,			// any Data
	FMT_ENUM = 10,
	FMT_DOUBLE = 9,			// any Data
	FMT_MASK = 12,
} TIFFDATAFORMAT;

typedef map< DWORD, TIFFDATAFORMAT, less<DWORD> > CTagFmtMap;
extern CTagFmtMap	tagFormatMap;

typedef struct tagTAGINFO {
	PICT_PROPERTY	tag;
	long			subTag;
	long			primaryFormat;
	TIFFDATAFORMAT	secondaryFormat;	// wenn format == ENUM, dann siehe subInfo[]
	UINT			nID;				// Ressource-ID für Beschreibung
} TAGINFO;

#define	END_DATAMAP	{ PICT_PROP_UNKNOWN, 0, 0, FMT_NDAT, 0 },

TAGINFO	info[] = {
	{ PICT_PROP_NEWSUBFILETYPE				, 0, PICT_DATA_LONG,		FMT_MASK,	IDS_TIFF_254	},
	{ PICT_PROP_SUBFILETYPE					, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_255	},
	{ PICT_PROP_IMAGEWIDTH					, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_256	},
	{ PICT_PROP_IMAGELENGTH					, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_257	},
	{ PICT_PROP_BITSPERSAMPLE				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_258	},
	{ PICT_PROP_COMPRESSION					, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_259	},
	{ PICT_PROP_COLORSPACE					, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_262	},
	{ PICT_PROP_THRESHOLDING				, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_263	},
//	{ 264	, 0, PICT_DATA_SHORT,	FMT_SHORT,	IDS_TIFF_264	},
//	{ 265	, 0, PICT_DATA_SHORT,	FMT_SHORT,	IDS_TIFF_265	},
	{ PICT_PROP_FILLORDER					, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_266	},
	{ PICT_PROP_DOCUMENTNAME				, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_269	},
	{ PICT_PROP_IMAGEDESCRIPTION			, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_270	},
	{ PICT_PROP_SCANNERMANUFACTURER			, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_271	},
	{ PICT_PROP_SCANNERMODEL				, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_272	},
	{ PICT_PROP_STRIPOFFSETS				, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_273	},
	{ PICT_PROP_ORIENTATION					, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_274	},
	{ PICT_PROP_SAMPLESPERPIXEL				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_277	},
	{ PICT_PROP_ROWSPERSTRIP				, 0, PICT_DATA_SHORT,		FMT_SORL,	IDS_TIFF_278	},
	{ PICT_PROP_STRIPBYTECOUNTS				, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_279	},
	{ PICT_PROP_MINSAMPLEVALUE				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_280	},
	{ PICT_PROP_MAXSAMPLEVALUE				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_281	},
	{ PICT_PROP_XRESOLUTION					, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_282	},
	{ PICT_PROP_YRESOLUTION					, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_283	},
	{ PICT_PROP_PLANARCONFIGURATION			, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_284	},
	{ PICT_PROP_PAGENAME					, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_285	},
	{ PICT_PROP_XPOSITION					, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_286	},
	{ PICT_PROP_YPOSITION					, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_287	},
//	{ 288	, 0, PICT_DATA_LONG,				FMT_LONG,	IDS_TIFF_288	},
//	{ 289	, 0, PICT_DATA_LONG,				FMT_LONG,	IDS_TIFF_289	},
	{ PICT_PROP_GRAYRESPONSEUNIT			, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_290	},
	{ PICT_PROP_GRAYRESPONSECURVE			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_291	},
	{ PICT_PROP_G3OPTIONS					, 0, PICT_DATA_LONG,		FMT_MASK,	IDS_TIFF_292	},
	{ PICT_PROP_G4OPTIONS					, 0, PICT_DATA_LONG,		FMT_MASK,	IDS_TIFF_293	},
	{ PICT_PROP_RESOLUTIONUNIT				, 0, PICT_DATA_SHORT,		FMT_ENUM,	IDS_TIFF_296	},
	{ PICT_PROP_PAGENUMBER					, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_297	},
	{ PICT_PROP_TRANSFERFUNCTION			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_301	},
	{ PICT_PROP_SOFTWARE					, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_305	},
	{ PICT_PROP_DATETIME					, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_306	},
	{ PICT_PROP_ARTIST						, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_315	},
	{ PICT_PROP_HOSTCOMPUTER				, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_316	},
	{ PICT_PROP_PREDICTOR					, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_317	},
	{ PICT_PROP_WHITEPOINT					, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_318	},
	{ PICT_PROP_PRIMARYCHROMATICS			, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_319	},
	{ PICT_PROP_COLORMAP					, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_320	},
	{ PICT_PROP_HALFTONEHINTS				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_321	},
	{ PICT_PROP_TILEWIDTH					, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_322	},
	{ PICT_PROP_TILELENGTH					, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_323	},
	{ PICT_PROP_TILEOFFSETS					, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_324	},
	{ PICT_PROP_TILEBYTECOUNTS				, 0, PICT_DATA_LONG,		FMT_SORL,	IDS_TIFF_325	},
	{ PICT_PROP_INKSET						, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_332	},
	{ PICT_PROP_INKNAMES					, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_333	},
	{ PICT_PROP_NUMBEROFINKS				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_334	},
	{ PICT_PROP_DOTRANGE					, 0, PICT_DATA_SHORT,		FMT_BORS,	IDS_TIFF_336	},
	{ PICT_PROP_TARGETPRINTER				, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_337	},
	{ PICT_PROP_EXTRASAMPLES				, 0, PICT_DATA_BYTE,		FMT_BYTE,	IDS_TIFF_338	},
	{ PICT_PROP_SAMPLEFORMAT				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_339	},
	{ PICT_PROP_SMINSAMPLEVALUE				, 0, PICT_DATA_LONG,		FMT_ANY,	IDS_TIFF_340	},
	{ PICT_PROP_SMAXSAMPLEVALUE				, 0, PICT_DATA_LONG,		FMT_ANY,	IDS_TIFF_341	},
	{ PICT_PROP_TRANSFERRANGE				, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_342	},
	{ PICT_PROP_JPEGPROC					, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_512	},
	{ PICT_PROP_JPEGINTERCHANGEFORMAT		, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_513	},
	{ PICT_PROP_JPEGINTERCHANGEFORMATLENGTH	, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_514	},
	{ PICT_PROP_JPEGRESTARTINTERVAL			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_515	},
	{ PICT_PROP_JPEGLOSSLESSPREDICTORS		, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_517	},
	{ PICT_PROP_JPEGPOINTTRANSFORMS			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_518	},
	{ PICT_PROP_JPEGQTABLES					, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_519	},
	{ PICT_PROP_JPEGDCTABLES				, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_520	},
	{ PICT_PROP_JPEGACTABLES				, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_521	},
	{ PICT_PROP_YCBCRCOEFFICIENTS			, 0, PICT_DATA_RATIONAL,	FMT_RATIO,	IDS_TIFF_529	},
	{ PICT_PROP_YCBCRSUBSAMPLING			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_530	},
	{ PICT_PROP_YCBCRPOSITIONING			, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_531	},
	{ PICT_PROP_REFERNCEBLACKWHITE			, 0, PICT_DATA_LONG,		FMT_LONG,	IDS_TIFF_532	},
	{ PICT_PROP_COPYRIGHT					, 0, PICT_DATA_LONG,		FMT_ASCII,	IDS_TIFF_33432	},

	////////////////////////////////////////////////////////////////////
	// Aldus - Photostyler

	{ PICT_PROP_ALDUSPHOTOSTYLERINFO1		, 0, PICT_DATA_BYTE,		FMT_BYTE,	IDS_TIFF_34391	},
	{ PICT_PROP_ALDUSPHOTOSTYLERINFO2		, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_34392	},

	////////////////////////////////////////////////////////////////////
	// Geokey - Tags

	{ PICT_PROP_GEOTIFF_MODELPIXELSCALE		, 0, PICT_DATA_DOUBLE,		FMT_DOUBLE,	IDS_TIFF_33550	},	// (Owner: SoftDesk)
	{ PICT_PROP_GEOTIFF_INTERGRAPHMATRIX	, 0, PICT_DATA_DOUBLE,		FMT_DOUBLE,	IDS_TIFF_33920	},	// (Owner: Intergraph)
	{ PICT_PROP_GEOTIFF_MODELTIEPOINT		, 0, PICT_DATA_DOUBLE,		FMT_DOUBLE,	IDS_TIFF_33922	},	// (Owner: Intergraph)
	{ PICT_PROP_GEOTIFF_MODELTRANSFORMATION	, 0, PICT_DATA_DOUBLE,		FMT_DOUBLE,	IDS_TIFF_34264	},	// (Owner: JPL Carto Group)

	{ PICT_PROP_GEOTIFF_GEOKEYDIRECTORY		, 0, PICT_DATA_SHORT,		FMT_SHORT,	IDS_TIFF_34735	},	// GeoKeyDirectoryTag (Owner: SPOT)
	{ PICT_PROP_GEOTIFF_GEOKEYDOUBLEPARAM	, 0, PICT_DATA_DOUBLE,		FMT_DOUBLE,	IDS_TIFF_34736	},	// GeoDoubleParamsTag (Owner: SPOT)
	{ PICT_PROP_GEOTIFF_GEOKEYASCIIPARAM	, 0, PICT_DATA_ASCII,		FMT_ASCII,	IDS_TIFF_34737	},	// GeoASCIIParamsTag (Owner: SPOT)
	END_DATAMAP
};

TAGINFO subInfo[] = {
	////////////////////////////////////////////////////////////////////
	// TAGNEWSUBFILETYPE			254
	{ PICT_PROP_NEWSUBFILETYPE	, 1,	0,	FMT_NDAT,	IDS_TIFF_254_1 },
	{ PICT_PROP_NEWSUBFILETYPE	, 2,	0,	FMT_NDAT,	IDS_TIFF_254_2 },
	{ PICT_PROP_NEWSUBFILETYPE	, 4,	0,	FMT_NDAT,	IDS_TIFF_254_4 },
	////////////////////////////////////////////////////////////////////
	// TAGSUBFILETYPE				255		// obsolete in TIFF V.6
	{ PICT_PROP_SUBFILETYPE	, 1,	0,	FMT_NDAT,	IDS_TIFF_254_1 },
	{ PICT_PROP_SUBFILETYPE	, 2,	0,	FMT_NDAT,	IDS_TIFF_254_2 },
	{ PICT_PROP_SUBFILETYPE	, 3,	0,	FMT_NDAT,	IDS_TIFF_254_3 },
	////////////////////////////////////////////////////////////////////
	// TAGCOMPR				259
	{ PICT_PROP_COMPRESSION	, 1,	0,	FMT_NDAT,	IDS_TIFF_259_1     },
	{ PICT_PROP_COMPRESSION	, 2,	0,	FMT_NDAT,	IDS_TIFF_259_2     },
	{ PICT_PROP_COMPRESSION	, 3,	0,	FMT_NDAT,	IDS_TIFF_259_3     },
	{ PICT_PROP_COMPRESSION	, 4,	0,	FMT_NDAT,	IDS_TIFF_259_4     },
	{ PICT_PROP_COMPRESSION	, 5,	0,	FMT_NDAT,	IDS_TIFF_259_5     },
	{ PICT_PROP_COMPRESSION	, 6,	0,	FMT_NDAT,	IDS_TIFF_259_6     },
	{ PICT_PROP_COMPRESSION	, 32771,	0,	FMT_NDAT,	IDS_TIFF_259_32771 },
	{ PICT_PROP_COMPRESSION	, 32773,	0,	FMT_NDAT,	IDS_TIFF_259_32773 },
	{ PICT_PROP_COMPRESSION	, 32809,	0,	FMT_NDAT,	IDS_TIFF_259_32809 },
	{ PICT_PROP_COMPRESSION	, 32895,	0,	FMT_NDAT,	IDS_TIFF_259_32895 },
	{ PICT_PROP_COMPRESSION	, 32896,	0,	FMT_NDAT,	IDS_TIFF_259_32896 },
	{ PICT_PROP_COMPRESSION	, 32897,	0,	FMT_NDAT,	IDS_TIFF_259_32897 },
	{ PICT_PROP_COMPRESSION	, 32898,	0,	FMT_NDAT,	IDS_TIFF_259_32898 },
	{ PICT_PROP_COMPRESSION	, 32908,	0,	FMT_NDAT,	IDS_TIFF_259_32908 },
	{ PICT_PROP_COMPRESSION	, 32909,	0,	FMT_NDAT,	IDS_TIFF_259_32909 },
	{ PICT_PROP_COMPRESSION	, 32946,	0,	FMT_NDAT,	IDS_TIFF_259_32946 },
	{ PICT_PROP_COMPRESSION	, 32947,	0,	FMT_NDAT,	IDS_TIFF_259_32947 },
	{ PICT_PROP_COMPRESSION	, 34661,	0,	FMT_NDAT,	IDS_TIFF_259_34661 },
	////////////////////////////////////////////////////////////////////
	// TAGCOLORSPACE				262
	{ PICT_PROP_COLORSPACE	, 0,	0,	FMT_NDAT,	IDS_TIFF_262_0     },
	{ PICT_PROP_COLORSPACE	, 1,	0,	FMT_NDAT,	IDS_TIFF_262_1     },
	{ PICT_PROP_COLORSPACE	, 2,	0,	FMT_NDAT,	IDS_TIFF_262_2     },
	{ PICT_PROP_COLORSPACE	, 3,	0,	FMT_NDAT,	IDS_TIFF_262_3     },
	{ PICT_PROP_COLORSPACE	, 4,	0,	FMT_NDAT,	IDS_TIFF_262_4     },
	{ PICT_PROP_COLORSPACE	, 5,	0,	FMT_NDAT,	IDS_TIFF_262_5     },
	{ PICT_PROP_COLORSPACE	, 6,	0,	FMT_NDAT,	IDS_TIFF_262_6     },
	{ PICT_PROP_COLORSPACE	, 8,	0,	FMT_NDAT,	IDS_TIFF_262_8     },
	////////////////////////////////////////////////////////////////////
	//	TAGTHRESHOLDING				263
	{ PICT_PROP_THRESHOLDING	, 1,	0,	FMT_NDAT,	IDS_TIFF_263_1     },
	{ PICT_PROP_THRESHOLDING	, 2,	0,	FMT_NDAT,	IDS_TIFF_263_2     },
	{ PICT_PROP_THRESHOLDING	, 3,	0,	FMT_NDAT,	IDS_TIFF_263_3     },
	////////////////////////////////////////////////////////////////////
	//	TAGFILLORDER				266
	{ PICT_PROP_FILLORDER	, 1,	0,	FMT_NDAT,	IDS_TIFF_266_1    },
	{ PICT_PROP_FILLORDER	, 2,	0,	FMT_NDAT,	IDS_TIFF_266_2    },
	////////////////////////////////////////////////////////////////////
	// TAGORIENTATION				274
	{ PICT_PROP_ORIENTATION	, 1,	0,	FMT_NDAT,	IDS_TIFF_274_1    },
	{ PICT_PROP_ORIENTATION	, 2,	0,	FMT_NDAT,	IDS_TIFF_274_2    },
	{ PICT_PROP_ORIENTATION	, 3,	0,	FMT_NDAT,	IDS_TIFF_274_3    },
	{ PICT_PROP_ORIENTATION	, 4,	0,	FMT_NDAT,	IDS_TIFF_274_4    },
	{ PICT_PROP_ORIENTATION	, 5,	0,	FMT_NDAT,	IDS_TIFF_274_5    },
	{ PICT_PROP_ORIENTATION	, 6,	0,	FMT_NDAT,	IDS_TIFF_274_6    },
	{ PICT_PROP_ORIENTATION	, 7,	0,	FMT_NDAT,	IDS_TIFF_274_7    },
	{ PICT_PROP_ORIENTATION	, 8,	0,	FMT_NDAT,	IDS_TIFF_274_8    },
	////////////////////////////////////////////////////////////////////
	// TAGPLANARCONFIGURATION		284
	{ PICT_PROP_PLANARCONFIGURATION	, 1,	0,	FMT_NDAT,	IDS_TIFF_284_1    },
	{ PICT_PROP_PLANARCONFIGURATION	, 2,	0,	FMT_NDAT,	IDS_TIFF_284_2    },
	////////////////////////////////////////////////////////////////////
	// TAGGRAYRESPONSEUNIT			290
	{ PICT_PROP_GRAYRESPONSEUNIT	, 1,	0,	FMT_NDAT,	IDS_TIFF_290_1    },
	{ PICT_PROP_GRAYRESPONSEUNIT	, 2,	0,	FMT_NDAT,	IDS_TIFF_290_2    },
	{ PICT_PROP_GRAYRESPONSEUNIT	, 3,	0,	FMT_NDAT,	IDS_TIFF_290_3    },
	{ PICT_PROP_GRAYRESPONSEUNIT	, 4,	0,	FMT_NDAT,	IDS_TIFF_290_4    },
	{ PICT_PROP_GRAYRESPONSEUNIT	, 5,	0,	FMT_NDAT,	IDS_TIFF_290_5    },
	////////////////////////////////////////////////////////////////////
	// TAGRESOLUTIONUNIT			296
	{ PICT_PROP_RESOLUTIONUNIT	, 1,	0,	FMT_NDAT,	IDS_TIFF_296_1    },
	{ PICT_PROP_RESOLUTIONUNIT	, 2,	0,	FMT_NDAT,	IDS_TIFF_296_2    },
	{ PICT_PROP_RESOLUTIONUNIT	, 3,	0,	FMT_NDAT,	IDS_TIFF_296_3    },
	{ PICT_PROP_RESOLUTIONUNIT	, -2,	0,	FMT_NDAT,	IDS_TIFF_296_4    },
	////////////////////////////////////////////////////////////////////
	// TAGT4OPTIONS					292
	{ PICT_PROP_G3OPTIONS	, 0,	0,	FMT_NDAT,	IDS_TIFF_292_0    },
	{ PICT_PROP_G3OPTIONS	, 1,	0,	FMT_NDAT,	IDS_TIFF_292_1    },
	{ PICT_PROP_G3OPTIONS	, 2,	0,	FMT_NDAT,	IDS_TIFF_292_2    },
	////////////////////////////////////////////////////////////////////
	// TAGT6OPTIONS					293
	{ PICT_PROP_G4OPTIONS	, 0,	0,	FMT_NDAT,	IDS_TIFF_293_0    },
	END_DATAMAP
};

////////////////////////////////////////////////////////////////////
// nicht - inlines für TAG

TAG::TAG( const TAG& t_ ) {
	Init();
	m_strName = t_.m_strName;
	m_tt = t_.m_tt;
	m_tv.m_tt = t_.m_tv.m_tt;
	m_tv.m_extraSpace = t_.m_tv.m_extraSpace; 
	if( m_tv.m_extraSpace > 0 && PICT_DATA_RATIONAL != m_tv.m_tt && PICT_DATA_SRATIONAL != m_tv.m_tt ) {
		m_tv.m_pVal = new BYTE[ m_tv.m_extraSpace ];
		memcpy( (void*) m_tv.m_pVal, (void*) t_.m_tv.m_pVal, m_tv.m_extraSpace );
	}
}

TAG& TAG::operator=( const TAG& t_ ) {
	if( m_tv.m_extraSpace > 0 && PICT_DATA_RATIONAL != m_tv.m_tt && PICT_DATA_SRATIONAL != m_tv.m_tt )
		delete m_tv.m_pVal;
	Init();
	m_strName = t_.m_strName;
	m_tt = t_.m_tt;
	m_tv = t_.m_tv;
	m_tv.m_tt = t_.m_tv.m_tt;
	m_tv.m_extraSpace = t_.m_tv.m_extraSpace; 
	if( m_tv.m_extraSpace > 0 && PICT_DATA_RATIONAL != m_tv.m_tt && PICT_DATA_SRATIONAL != m_tv.m_tt ) {
		m_tv.m_pVal = new BYTE[ m_tv.m_extraSpace ];
		memcpy( (void*) m_tv.m_pVal, (void*) t_.m_tv.m_pVal, m_tv.m_extraSpace );
	}
	return *this;
}

void TAG::ReadArray( int sizeofItem, int nItems, void* pItems ) {
	if( m_tv.m_extraSpace > 0 )
		delete[] m_tv.m_pVal;
	int	tt = m_tv.m_tt;
	tt += 100;
	m_tv.m_tt = (PICT_DATATYPE) tt;
	m_tv.m_extraSpace = sizeofItem * nItems;
	m_tv.m_pVal = new BYTE[ m_tv.m_extraSpace ];
	memcpy( m_tv.m_pVal, pItems, (size_t) ( m_tv.m_extraSpace ) );
}

CTagMap		tagMasterMap;
CTagMap		tagSlaveMap;
CTagFmtMap	tagFormatMap;
stringMap	dataTypeMap;

BOOL InitMasterMap( HINSTANCE hInstance ) {
	CString S;
	static TCHAR szBuf[ 256 ];
	TAGINFO *pInfo;
	for( pInfo = info; -1 != pInfo->tag; ++pInfo ) {
		switch( pInfo->primaryFormat ) {
		case PICT_DATA_BYTE		: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (BYTE) 0 ); break;
		case PICT_DATA_SHORT	: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (WORD) 0 ); break;
		case PICT_DATA_LONG		: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (ULONG) 0 ); break;
		case PICT_DATA_FLOAT	: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (float) 0 ); break;
		case PICT_DATA_DOUBLE	: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (double) 0 ); break;
		case PICT_DATA_RATIONAL	: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, (ULONG) 0, (ULONG) 0 ); break;
		case PICT_DATA_ASCII	: tagMasterMap[pInfo->tag] = TAG( pInfo->tag, _T(""), 1 ); break;
		}
		VERIFY( ::LoadString( hInstance, pInfo->nID, szBuf, sizeof( szBuf ) ) > 0 );
		tagMasterMap[pInfo->tag].Name() = szBuf;
		tagFormatMap[pInfo->tag] = pInfo->secondaryFormat;
	}
	DWORD	dwKey;
	for( pInfo = subInfo; -1 != pInfo->tag; ++pInfo ) {
		dwKey = MAKELONG( pInfo->tag, pInfo->subTag );
		tagSlaveMap[(PICT_PROPERTY)dwKey] = TAG( pInfo->tag, (BYTE) 0 );
		VERIFY( ::LoadString( hInstance, pInfo->nID, szBuf, sizeof( szBuf ) ) > 0 );
		tagSlaveMap[(PICT_PROPERTY)dwKey].Name() = szBuf;
	}
	dataTypeMap[1]   = "BYTE";
	dataTypeMap[2]   = "*ASCII";
	dataTypeMap[3]   = "SHORT";
	dataTypeMap[4]   = "LONG";
	dataTypeMap[5]   = "RATIONAL";

	dataTypeMap[6]   = "SBYTE";
	dataTypeMap[7]   = "UNDEFINED";
	dataTypeMap[8]   = "SSHORT";
	dataTypeMap[9]   = "SLONG";
	dataTypeMap[10]  = "SRATIONAL";
	dataTypeMap[11]  = "FLOAT";
	dataTypeMap[12]  = "DOUBLE";

	dataTypeMap[101] = "*BYTE";
	dataTypeMap[103] = "*SHORT";
	dataTypeMap[104] = "*LONG";
	dataTypeMap[106] = "*SBYTE";
	dataTypeMap[108] = "*SSHORT";
	dataTypeMap[109] = "*SLONG";
	dataTypeMap[111] = "*FLOAT";
	dataTypeMap[112] = "*DOUBLE";

	return TRUE;
}

static LPCTSTR szT1 = _T("\t");
static LPCTSTR szT2 = _T("\t\t");

ostream& operator<<( ostream& os, const TAG& t ) {
	os << t.Num();
	os << szT1 << (LPCTSTR) dataTypeMap[t.Type()];
	if( 0 != strlen( tagMasterMap[t.Num()].Name() ) )
		os << szT1 << tagMasterMap[t.Num()].Name();
	else
		os << szT1 << _T("<unbekannt>");
	os << szT1 << t.Count();
	os << szT1;
	if( FMT_ENUM == tagFormatMap[t.Num()] ) {
		os << _T('(') << tagSlaveMap[ (PICT_PROPERTY) MAKELONG( t.Num(), t.ssVal() ) ].Name() << _T(')');
	} else if( t.Type() > 100 || PICT_DATA_ASCII == t.Type() ) {
		os << _T('(') << t.pVal() << _T(',') << t.Space() << _T(')');
	}
	os << szT1;
	switch( t.Type() ) {
	case PICT_DATA_BYTE		: os << t.ubVal(); break;
	case PICT_DATA_SHORT	: os << t.usVal(); break;
	case PICT_DATA_LONG		: os << t.ulVal(); break;
	case PICT_DATA_RATIONAL	: os << t.urVal().num << "/" << t.urVal().denom; break;
	case PICT_DATA_ASCII	: os << t.strVal(); break;

	case PICT_DATA_SBYTE		: os << t.sbVal(); break;
	case PICT_DATA_SSHORT	: os << t.ssVal(); break;
	case PICT_DATA_SLONG		: os << t.slVal(); break;
	case PICT_DATA_SRATIONAL	: os << t.srVal().num << _T('/') << t.srVal().denom; break;
	case PICT_DATA_FLOAT		: os << t.fVal(); break;
	case PICT_DATA_DOUBLE	: os << t.dVal(); break;

	case PICT_DATA_PBYTE		:
	case PICT_DATA_PSHORT	:
	case PICT_DATA_PLONG		:
	case PICT_DATA_PSBYTE	:
	case PICT_DATA_PSSHORT	:
	case PICT_DATA_PFLOAT	:
	case PICT_DATA_PDOUBLE	:
		break;
	default			: os << "<undefiniert>"; break;
	}
	return os;
}

void CPicture::DumpTags( ostream& os, bool bRaw /*=false*/ ) {
	CTagMap::const_iterator i;
	int	idx = os.xalloc();
	for( i = TAGMAP.begin(); i != TAGMAP.end(); ++i ) {
		os << (*i).second;
		if( (*i).first > 30000 ) {
			if( PICT_DATA_PSHORT == (*i).second.Type() ) {
				LPWORD	pWord = (LPWORD) (*i).second.pVal();
				if( !bRaw )
					os << endl << szT1;
				for( int ii = 0; ii < (*i).second.Count(); ii++ ) {
					if( !bRaw && ii > 0 && ii % 4 == 0 )
						os << endl;
					if( ii > 0 )
						os << szT1;
					os << pWord[ii];
				}
			} else if( PICT_DATA_PDOUBLE == (*i).second.Type() ) {
				if( !bRaw )
					os << endl << szT1;
				int f = os.flags();
				os.flags( f | ios::fixed );
				os.precision( 5 );
				double	*pDbl = (double*) (*i).second.pVal();
				for( int ii = 0; ii < (*i).second.Count(); ii++ ) {
					if( !bRaw && ii > 0 && ii % 6 == 0 )
						os << endl;
					if( ii > 0 )
						os << szT1;
					os << pDbl[ii];
				}
				os.flags(f);
			} else if( PICT_DATA_PLONG == (*i).second.Type() ) {
				if( !bRaw )
					os << endl << szT1;
				long	*pLng = (long*) (*i).second.pVal();
				for( int ii = 0; ii < (*i).second.Count(); ii++ ) {
					if( !bRaw && ii > 0 && ii % 6 == 0 )
						os << endl;
					if( ii > 0 )
						os << szT1;
					os << pLng[ii];
				}
			}
		}
		os << endl;
	}
}

const CString CPictCrack::Crack( PICT_PROPERTY tag, long subTag /*=-1*/ ) {
	return ( -1 == subTag ) ? tagMasterMap[tag].Name() : tagSlaveMap[(PICT_PROPERTY)MAKELONG(tag,subTag)].Name();
}

const CString CPictCrack::Crack( PICT_PROPERTY tag, const CPicture* pPicture ) {
	TAG	t;
	CString	S;
	VERIFY( S.LoadString( IDS_TIFF_UNKNOWN ) );
	if( pPicture->GetTag( tag, t ) ) {
		if( FMT_ENUM == tagFormatMap[t.Num()] ) {
			S =  tagSlaveMap[ (PICT_PROPERTY) MAKELONG( t.Num(), t.ssVal() ) ].Name();
		} else {
			switch( t.Type() ) {
			case PICT_DATA_BYTE		: S.Format( _T("0x%02x"), t.ubVal() ); break;
			case PICT_DATA_SHORT	: S.Format( _T("%d"), t.usVal() ); break;
			case PICT_DATA_LONG		: S.Format( _T("%ld"), t.ulVal() ); break;
			case PICT_DATA_RATIONAL	: {
					double	d = t.urVal().denom ? (double) t.urVal().num / (double) t.urVal().denom : -1;
					S.Format( _T("%.3lf (%ld / %ld)"), d, t.urVal().num, t.urVal().denom );
				}
				break;
			case PICT_DATA_ASCII	: S.Format( _T("%s"), t.strVal() ); break;

			case PICT_DATA_SBYTE	: S.Format( _T("0x%02x"), t.sbVal() ); break;
			case PICT_DATA_SSHORT	: S.Format( _T("%d"), t.ssVal() ); break;
			case PICT_DATA_SLONG	: S.Format( _T("%ld"), t.slVal() ); break;
			case PICT_DATA_SRATIONAL	: {
					double	d = t.srVal().denom ? (double) t.srVal().num / (double) t.srVal().denom : -1;
					S.Format( _T("%.3lf (%ld / %ld)"), d, t.srVal().num, t.srVal().denom );
				}
				break;
			case PICT_DATA_FLOAT	: S.Format( _T("%0.5lf"), (double) t.fVal() ); break;
			case PICT_DATA_DOUBLE	: S.Format( _T("%0.5lf"), t.dVal() ); break;
			}
		}
	}
	return S;
}
