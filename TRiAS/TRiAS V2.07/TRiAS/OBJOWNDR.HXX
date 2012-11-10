// Klasse, die hinter den RechercheListBoxItem haengt -------------------------
// File: OBJOWNDR.HXX


#if !defined(_OBJOWNDR_HXX)
#define _OBJOWNDR_HXX

class ObjInfoItem {
private:
	long _ONr;		// ObjektNummer ist Schlüssel
	short m_iOType;		// ObjektTyp
	char *_pStr;		// anzuzeigender Text
	char *m_pText;		// Objekteigenschaft
	Color _C;			// Farbe der Zeile (linker Teil)
	Color _ActC;		// Farbe der Markierung
	Color m_cObjProp;	// Farbe rechter Teil (Objekteigenschaft)
	short _isSelected;	// ist derzeit selektiert
	short _isActive;	// derzeit aktives Objekt

public:
		ObjInfoItem (long ONr);		// nur für Suchzwecke
		ObjInfoItem (long ONr, short iOTyp, const char *pStr, const char *pText,
					 Color C, Color C2, Color C3);
		~ObjInfoItem (void);

	Color &StringColor (void) const { return (Color &)_C; }
	Color &ActColor (void) const { return (Color &)_ActC; }
	Color &ObjPropColor (void) const { return (Color &)m_cObjProp; }

	char * ItemText (void) const { return _pStr; }
	char * PropText (void) const { return m_pText; }
	long & ONr (void) { return _ONr; }
	short isSelected (void) { return _isSelected; }
	void isSelected (short newSel) { _isSelected = newSel; }
	void isActive (short newAct) { _isActive = newAct; }
	short GetOType (void) { return m_iOType; }

	Color ChangeActiveColor (Color newC);

	bool ObjPropExists (void) { return 0 == memcmp(&_C, &m_cObjProp, sizeof(Color)); }

friend void *GetONr (void *);
friend int CmpONr (void *, void *);
};


class ObjInfoItemTree : public CTree {
protected:
	void UserDelete (void *);

public:
		ObjInfoItemTree (void);
		~ObjInfoItemTree (void);

	string GetItemString (LONG lONr);

	void SelectObject (LONG lONr, bool fSelect = true);
	void ActivateObject (LONG lONr);
};
DeclareLock (ObjInfoItemTree, ObjInfoItem);

#endif	// _OBJOWNDR_HXX
