// Liste der von Erweiterungen geladenen MenuItems ----------------------------
// File: MENUITEM.HXX

#if !defined(_MENUITEM_HXX)
#define _MENUITEM_HXX

// dieser Baum enthält alle Menuerweiterungen der ORFenster
class CMenuItem 
{
public:
	string m_strMenuText;	// anzuzeigender MenuText
	HDEX _hDex;			// zuständige Erweiterung
	UINT _iMenuID;		// MenuItem (Key)
	int _iPopup;		// Nummer des PopupMenu 
	int _iMenuPos;		// Position im Menu (-1: am Ende)
	HMENU m_hMenu;		// einzuhängendes Popupmenu 
	bool m_fIsTopLevel;	// Popupmenu ganz oben einbauen
	bool m_fRemoveItem;	// Anweisung zum Entfernen eines Menuitems

		CMenuItem (char *pText, HDEX hDex, short ID, short iNum, short iMenuPos);
		CMenuItem (char *pText, HDEX hDex, short iNum, HMENU hMenu, bool fIsTopLevel = false);

		CMenuItem (HDEX hDex, short ID, short iNum);				// RemoveOrigItem
		~CMenuItem (void);
};

class CMenuItemList : 
	public CListContainer
{
protected:
	void UserDelete (void *pObj);

public:
		CMenuItemList (void);
		~CMenuItemList (void);

	bool RemoveMenuItem (short);
};
DeclareLock (CMenuItemList, CMenuItem);

#endif // _MENUITEM_HXX
