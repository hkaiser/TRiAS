//	File: HELPTEXT.CPP
//	Erabeitet: J. Benkenstein 			Stand vom 13.10.1994

#ifndef _HELP_TEXT_HPP
#define _HELP_TEXT_HPP

class CHelpText : public CEdit
{ 
        CFont m_Font;
	
public:
	CHelpText (void) {}
	~CHelpText (void) {}
	
	BOOL InitFont (void);			// Arial-Zeichensatz einstellen 
	BOOL Output (uint ResId);		// String ausgeben	

//	Beschreibung über Merkmal/Objektklasse ausgeben 
	BOOL OutputDescription (ulong lKode, char cType, uint ResId);
};

#endif		// _HELP_TEXT_HPP
