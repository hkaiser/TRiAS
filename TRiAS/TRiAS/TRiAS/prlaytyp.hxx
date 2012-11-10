// Typen für LegendenLayout ---------------------------------------------------
// File: PRLAYTYP.HXX

#if !defined(_PRLAYTYP_HXX)
#define _PRLAYTYP_HXX

enum LEGLAYOUT_FORMAT {
	LL_FORMAT_None = 0,
	LL_FORMAT_QuerFormat = 1,
	LL_FORMAT_HochFormat = 2,
	LL_FORMAT_MaxFormat = 3,
};
enum LEGLAYOUT_ITEM {
	LL_ITEM_None = 0,
	LL_ITEM_Kasten = 1,
	LL_ITEM_LegendeKopf = 2,
	LL_ITEM_Legende = 3,
	LL_ITEM_Leerzeile = 4,
	LL_ITEM_Masstab = 5,
	LL_ITEM_Meander = 6,
	LL_ITEM_Signatur = 7,
	LL_ITEM_Ueberschrift = 8,
	LL_ITEM_ZwischenUeberschrift = 9,
	LL_ITEM_Logo = 10,
	LL_ITEM_LogoBase = 10,	// Basis für LL_SUB_ITEM's
	LL_ITEM_LinksOben = 11,
	LL_ITEM_LinksUnten = 12,
	LL_ITEM_RechtsOben = 13,
	LL_ITEM_RechtsUnten = 14,
	LL_ITEM_MaxItem = 15,
};
enum LEGLAYOUT_SUB_ITEM {		// Positionen in LEGLAYOUT_ITEM
	LL_SUB_ITEM_LinksOben = 0,	// bezüglich LL_ITEM_LogoBase
	LL_SUB_ITEM_LinksUnten = 1,
	LL_SUB_ITEM_RechtsOben = 2,
	LL_SUB_ITEM_RechtsUnten = 3,
	LL_SUB_ITEM_MaxSubItem = 4,
};
enum LEGLAYOUT_POSITION {
	LL_POSITION_None = 0,
	LL_POSITION_Vor = 1,
	LL_POSITION_Nach = 2,
	LL_POSITION_Zwischen = 3, 
	LL_POSITION_MaxPosition = 4,
};
enum LEGLAYOUT_ATTRIBUTE {
	LL_ATTRIBUTE_None = 0,
	LL_ATTRIBUTE_Breite = 1,
	LL_ATTRIBUTE_Hoehe = 2,
	LL_ATTRIBUTE_Font = 3,
	LL_ATTRIBUTE_Desc = 4,
	LL_ATTRIBUTE_Typ = 5,
	LL_ATTRIBUTE_Opaque = 6,
	LL_ATTRIBUTE_MaxAttribute = 7,
};

#endif // _PRLAYTYP_HXX
