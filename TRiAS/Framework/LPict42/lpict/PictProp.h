#ifndef PICT_PROPERTYCALL
#define PICT_PROPERTYCALL
#endif
typedef void (PICT_PROPERTYCALL CPicture::*PICT_PROPERTYFUNC)(void);

#ifdef _AFXDLL
#define BEGIN_PROPERTYMAP( theClass, baseClass ) \
	const PICT_PROPERTYMAP* PASCAL theClass::_GetBasePropertyMap() \
		{ return &theClass::propertyMap; } \
	const PICT_PROPERTYMAP* theClass::GetPropertyMap() const \
		{ return &theClass::propertyMap; } \
	AFX_DATADEF const PICT_PROPERTYMAP theClass::propertyMap = \
		{ &theClass::_GetBasePropertyMap, &theClass::propertyMapEntries[0] }; \
	const PICT_PROPERTYMAP_ENTRY theClass::propertyMapEntries[] = \
		{ \

#else
#define BEGIN_PROPERTYMAP( theClass, baseClass ) \
	const PICT_PROPERTYMAP* theClass::GetPropertyMap() const \
		{ return &theClass::propertyMap; } \
	AFX_DATADEF const PICT_PROPERTYMAPtheClass::propertyMap = \
		{ &baseClass::propertyMap, &theClass::propertyMapEntries[0] }; \
	const PICT_PROPERTYMAP_ENTRY theClass::propertyMapEntries[] = \
		{ \

#endif

#define	END_PROPERTYMAP() \
	{ NULL, 0, (PICT_PROPERTYFUNC) NULL } \
	};

enum HtmTagType {
	PpmTag_bv,			// BOOL (void)
	PpmTag_bs,			// BOOL (LPCTSTR)
	PpmTag_bw,			// BOOL (WORD)
	PpmTag_br,			// BOOL (CRect)
};

struct PICT_PROPERTYMAP_ENTRY {
	DWORD				ppm_PropName;
	UINT				ppm_Sig;
	PICT_PROPERTYFUNC	ppm_PropFunc;
};

union PropertyMapFunctions
{
	PICT_PROPERTYFUNC	pfn;

	void (PICT_PROPERTYCALL CPicture::*pfn_vv)();
	void (PICT_PROPERTYCALL CPicture::*pfn_vs)(LPCTSTR);
	BOOL (PICT_PROPERTYCALL CPicture::*pfn_bv)();
	BOOL (PICT_PROPERTYCALL CPicture::*pfn_bs)(LPCTSTR);
};

