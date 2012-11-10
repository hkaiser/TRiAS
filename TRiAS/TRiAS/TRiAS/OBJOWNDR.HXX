// Klasse, die hinter den RechercheListBoxItem haengt -------------------------
// File: OBJOWNDR.HXX

#include <COptTree.hxx>

#if !defined(_OBJOWNDR_HXX)
#define _OBJOWNDR_HXX

class ObjInfoItem 
{
private:
	INT_PTR _ONr;		// ObjektNummer ist Schlüssel
	short m_iOType;		// ObjektTyp
	char *_pStr;		// anzuzeigender Text
	char *m_pText;		// Objekteigenschaft
	Color _C;			// Farbe der Zeile (linker Teil)
	Color _ActC;		// Farbe der Markierung
	Color m_cObjProp;	// Farbe rechter Teil (Objekteigenschaft)
	bool _isSelected;	// ist derzeit selektiert
	bool _isActive;		// derzeit aktives Objekt
	bool m_fHideEntryIfHidden;		// ausgeblendetes Objekt wirklich ausblenden

	INT_PTR m_lIdent;
	bool m_fInitialized;	// ist bereits initialisiert

public:
	ObjInfoItem (INT_PTR lONr);		// nur für Suchzwecke
	ObjInfoItem (INT_PTR lONr, short iOTyp, const char *pStr, const char *pText, Color C, Color C2, Color C3);
	ObjInfoItem (INT_PTR lONr, INT_PTR lIdent, short iOTyp, Color cActC);

	~ObjInfoItem (void);

	INT_PTR GetIdent() { return m_lIdent; }

	bool IsInitialized() { return m_fInitialized; }
	void SetInitialized(bool fFlag) { m_fInitialized = fFlag; }

// nachinitialisieren
	HRESULT SetInfo (short iOTyp, const char *pStr, const char *pText, Color C, Color C3);

// accessors
	Color &StringColor (void) const { return (Color &)_C; }
	Color &ActColor (void) const { return (Color &)_ActC; }
	Color &ObjPropColor (void) const { return (Color &)m_cObjProp; }

	char * ItemText (void) const { return _pStr; }
	char * PropText (void) const { return m_pText; }
	INT_PTR & ONr (void) { return _ONr; }

	bool isSelected (void) { return _isSelected; }
	void isSelected (short newSel) { _isSelected = newSel; }
	void isActive (short newAct) { _isActive = newAct; }
	short GetOType (void) { return m_iOType; }

	Color ChangeActiveColor (Color newC);

	bool ObjPropExists (void) { return 0 == memcmp (&_C, &m_cObjProp, sizeof(Color)); }

	bool HiddenIfHidden() { return m_fHideEntryIfHidden; }
	void HideEntryIfHidden(bool fHideEntryIfHidden) { m_fHideEntryIfHidden = fHideEntryIfHidden; }

friend void *GetONr (void *);
friend int CmpONr (void *, void *);
};

///////////////////////////////////////////////////////////////////////////////
// Baum, der alle Elemente des ORFensters nach Objektnummern sortiert enthält
class ObjInfoItemTree : 
	public COptTree 
{
protected:
	void UserDelete (void *);

public:
		ObjInfoItemTree (void);
		~ObjInfoItemTree (void);

	string GetItemString (LONG lONr, class ObjektInfo &rORWnd);

	void SelectObject (LONG lONr, bool fSelect = true);
	void ActivateObject (LONG lONr);
};
DeclareOptLock (ObjInfoItemTree, ObjInfoItem);

#endif	// _OBJOWNDR_HXX
