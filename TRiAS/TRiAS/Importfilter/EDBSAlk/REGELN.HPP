///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			Regeln.h
//
//	Stand:			24.02.1995
//	Beschreibung:	Verwaltung der Regeln
//	Entwicklung:	24.02.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////


#ifndef _REGELN_H_
#define _REGELN_H_


class CMapRegeln : public CMapStringToPtr
{
public:
					CMapRegeln()		{}
					~CMapRegeln();
	void			AddRegel( const char* );
};

#endif
