// Memberfunktionen fuer die DarstellungsStilAuswahl --------------------------
// File: FEATURE.CXX

#include "triaspre.hxx"

#include <owncombo.hxx>

#include "feature.hxx"

// DatenTyp, der in OwnerDrawListBox drinhängt --------------------------------
Feature :: Feature (unsigned int Style, char *Name) {

	_Style = Style;
	_StyleName = new char [strlen(Name)+1];
	if (_StyleName != NULL)
		strcpy (_StyleName, Name);
}

Feature :: ~Feature (void) 
{
	DELETE (_StyleName);
}
