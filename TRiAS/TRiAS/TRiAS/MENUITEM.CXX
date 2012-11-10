// Memberfunktionen fur MenuErweiterungsListe ---------------------------------
// File: MENUITEM.CXX

#include "triaspre.hxx"

#include "menuitem.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen zu Elementen der Liste 
CMenuItem::CMenuItem (char *pText, HDEX hDex, short ID, short iNum, short iMenuPos)
{
	TX_ASSERT(NULL != hDex);

	if (NULL != pText) {		// ggf. MF_SEPARATOR
		TX_ASSERT(-1 != ID);
		m_strMenuText = pText;
	}
    _hDex = hDex;
    _iMenuID = ID;
    _iPopup = iNum;
	_iMenuPos = iMenuPos;
	m_fIsTopLevel = false;
	m_fRemoveItem = false;
	m_hMenu = NULL;
}

CMenuItem::CMenuItem (char *pText, HDEX hDex, short iNum, HMENU hMenu, bool fIsTopLevel)
{
	TX_ASSERT(NULL != hDex);

	if (NULL != pText)		// ggf. MF_SEPARATOR
		m_strMenuText = pText;
    _hDex = hDex;
    _iMenuID = -1;
    _iPopup = iNum;
	_iMenuPos = -1;
	m_fIsTopLevel = fIsTopLevel;
	m_fRemoveItem = false;
	m_hMenu = hMenu;
}

// RemoveOrigItem
CMenuItem::CMenuItem (HDEX hDex, short ID, short iNum)
{
	TX_ASSERT(NULL != hDex);
	TX_ASSERT(-1 != ID);

    _hDex = hDex;
    _iMenuID = ID;
    _iPopup = iNum;
	_iMenuPos = -1;
	m_fIsTopLevel = false;
	m_fRemoveItem = true;
	m_hMenu = NULL;
}

CMenuItem::~CMenuItem (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen der Liste selbst 
CMenuItemList::CMenuItemList (void)
    : CListContainer ()
{
        // nothing to do
}

CMenuItemList::~CMenuItemList (void)
{
        EveryDelete();
}

bool CMenuItemList::RemoveMenuItem (short iMenuID)
{
CRing r(*this);

	for (r.First(); r.Valid(); /**/) {
	bool toDelete = false;

		{
		CMenuItemLock l(r);

			TX_ASSERT(NULL != (CMenuItem *)l);

			if (l -> _iMenuID == iMenuID)
				toDelete = TRUE;
		}
		if (toDelete)
			return r.Delete();
		else
			r.Next();
	}
	return false;
}

void EXPORTTRIAS CMenuItemList::UserDelete (void *pObj)
{
	TX_ASSERT_POINTER(pObj, CMenuItem);
	((CMenuItem *)pObj) -> ~CMenuItem();
}
