// Memberfunktionen fur MenuErweiterungsListe ---------------------------------
// File: MENUITEM.CXX

#include "triaspre.hxx"

#include "menuitem.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Memberfunktionen zu Elementen der Liste ------------------------------------
MenuItem :: MenuItem (char *pText, HDEX hDex, short ID, short iNum)
{
	TX_ASSERT(TIsValidString(pText));
	TX_ASSERT(NULL != hDex);

        _pMenuText = StrDup (pText, RC_ctMenuItem);
        _hDex = hDex;
        _iMenuID = ID;
        _iPopup = iNum;
}

MenuItem :: ~MenuItem (void)
{
        DELETE (_pMenuText);
}


// Memberfunktionen der Liste selbst ------------------------------------------
MenuItemList :: MenuItemList (void)
              : CListContainer ()
{
        // nothing to do
}

MenuItemList :: ~MenuItemList (void)
{
        EveryDelete();
}

bool MenuItemList :: RemoveMenuItem (short iMenuID)
{
CRing r(*this);

        for (r.First(); r.Valid(); ) {
        Bool toDelete = false;

                {
                MenuItemLock l(r);

			TX_ASSERT(NULL != (MenuItem *)l);
 
                        if (l -> _iMenuID == iMenuID)
                                toDelete = TRUE;
                }
                if (toDelete)   return r.Delete();
                else            r.Next();
        }

return false;
}

void EXPORTTRIAS MenuItemList :: UserDelete (void *pObj)
{
	TX_ASSERT_POINTER(pObj, MenuItem);

        ((MenuItem *)pObj) -> ~MenuItem();
}
