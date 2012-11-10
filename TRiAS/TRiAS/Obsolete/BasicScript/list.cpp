#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include "macrguid.h"

#include <ospace/source.h>
#include <ospace/std/string>
#include <ospace/uss/std/string.h>

#include "imacorg.h"
#include "imacro.h"

#include "myenum.h"

#include "listitem.h"
#include "commimp.h"

HRESULT CreateObject(CLSID *pClID, LPVOID *ppv)
{
	ASSERT(pClID);
	ASSERT(ppv);

	*ppv = NULL;

	if (*pClID == CLSID_ListItem) 
		*ppv = new CListItem;
	else if (*pClID == CLSID_IDItem) 
		*ppv = new CIDItem;
	else if (*pClID == CLSID_MenuCommand) 
		*ppv = new CImpIMenu;
	else ASSERT(0);

	if (NULL == *ppv) return ResultFromScode(E_FAIL);

return NOERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// konkrete Listitem-Klassen zum "STREAMEN" instanzieren
////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int os_clistelement_id = os_user_start_id + 118;
OS_STREAMABLE_0( (CListElement *), os_clistelement_id);

void os_write (os_bstream& stream, const CListElement& LE) 
{	
	ASSERT(LE.m_uiID);
	ASSERT(!LE.m_strMenuName.IsEmpty());
	stream << LE.m_uiID << os_string(LE.m_strMenuName);
}

void os_read (os_bstream& stream, CListElement& LE) 
{
os_string str;		
	stream >> LE.m_uiID >> str;
	LE.m_strMenuName = str.c_str();
	
	ASSERT(LE.m_uiID);
	ASSERT(!LE.m_strMenuName.IsEmpty());
}


const int os_clistitem_id = os_user_start_id + 119;
OS_STREAMABLE_1( (CListItem *), os_clistitem_id, (CListElement *) );

void os_write (os_bstream& stream, const CListItem& LI) 
{
	os_write(stream, (const CListElement&) LI);
	stream << LI.m_EnumWListElement;
}

void os_read (os_bstream& stream, CListItem& LI) 
{
	os_read(stream, (CListElement&) LI);
	stream >> LI.m_EnumWListElement;
}


const int os_ciditem_id = os_user_start_id + 120;
OS_STREAMABLE_1( (CIDItem *), os_ciditem_id, (CListElement *) );

void os_write (os_bstream& stream, const CIDItem& IDI)
{
	os_write(stream, (const CListElement&) IDI);
}

void os_read (os_bstream& stream, CIDItem& IDI)
{
	os_read(stream, (CListElement&) IDI);
}


// Prüfvariablen Speicherfreigabe
int g_iLE = 0;
int g_iLI = 0;
int g_iIDI = 0;




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** Basisklasse der Listenelemente ***
////////////////////////////////////////////////////////////////////////////////////////////////////////////

CListElement :: CListElement()		
				:	m_strMenuName(),
					m_uiID(0)
{
	m_dwRefCnt = 0;
	AddRef();

	FInit();

	g_iLE++;

}

CListElement :: ~CListElement()
{
	g_iLE--;
	delete (m_pBStream); 
}

bool CListElement :: FInit()
{
	m_pBStream = new XPersistBStream(this);
	if (NULL == m_pBStream) return false;

return true;
}

STDMETHODIMP CListElement :: Insert (LPCSTR strMenuName, UINT uiID)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: Insert (IListElement *pILE, 
									 IListElement *pILstEl_After)
{	
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: Get (LPSTR strMenuName, int iLen, 
							  UINT *puiID)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: GetEnum(IEnum<WListElement> ** ppIEn)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: SetMenu(HMENU hMenu)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: GetMenu(HMENU *phMenu)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CListElement :: ClearItem (IListElement *pILE)
{
return ResultFromScode(E_NOTIMPL);
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CListElement :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown  || riid == IID_IListElement)
		*ppvObj = this;
	else if (riid == IID_IPersistBStream)
		*ppvObj = m_pBStream;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CListElement :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CListElement :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;	// freigeben
		return 0L;
	}

return m_dwRefCnt;
}



/// ///////////////////////////////////////////////////////////////////////////////
// *** in Basisklasse eingebettete Klasse 
/// ///////////////////////////////////////////////////////////////////////////////

CListElement :: XPersistBStream :: XPersistBStream (CListElement *pLE)
{
	ASSERT(pLE);
	m_pParent = pLE;
}

// alle methods delegiert 

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CListElement :: XPersistBStream :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pParent -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CListElement :: XPersistBStream :: AddRef (void)
{
return m_pParent -> AddRef();
}

STDMETHODIMP_(ULONG) CListElement :: XPersistBStream :: Release (void)
{
return m_pParent -> Release();
}

// *** IPersistBStream methods -------------------------------------------------------
STDMETHODIMP CListElement :: XPersistBStream :: GetClassID(CLSID *pClassID)
{
return m_pParent -> GetClassID(pClassID);
}

STDMETHODIMP CListElement :: XPersistBStream :: Load (os_bstream *pstream)
{
	ASSERT(pstream);
return m_pParent -> Load(pstream);
}

STDMETHODIMP CListElement :: XPersistBStream :: Save (os_bstream *pstream)
{
	ASSERT(pstream);
return m_pParent -> Save (pstream); 
}





//////////////////////////////////////////////////////////////////////
// *** Elementinstanz der Menüliste aus Menülisten ***
//////////////////////////////////////////////////////////////////////

CListItem :: CListItem()
			:	CListElement(), m_EnumWListElement()
{
	g_iLI++;
	m_hMenu = NULL;
}

CListItem :: ~CListItem()
{
	g_iLI--;
}

STDMETHODIMP CListItem :: Insert (IListElement *pILE, 
								  IListElement *pILE_After)
{
	ASSERT(pILE);

WListElement ILE (pILE);
	if (NULL == pILE_After) {
		m_EnumWListElement.AddItem(ILE); 
		return NOERROR; 
	}

WListElement ILE_After (pILE_After);
	m_EnumWListElement.InsertItem(ILE_After, ILE);

return NOERROR;
}

STDMETHODIMP CListItem :: Insert (LPCSTR pcMenuName, UINT uiID)
{	
	ASSERT(pcMenuName);
	m_strMenuName = pcMenuName;
	m_uiID = uiID;

return NOERROR;
}

STDMETHODIMP CListItem :: Get (LPSTR pcMenuName, int iLen, UINT *puiID)
{	
	ASSERT(!m_strMenuName.IsEmpty()); 
	ASSERT(iLen > 0);
	ASSERT(NULL != pcMenuName || NULL != puiID);
	
	if (NULL != pcMenuName) {
		strncpy (pcMenuName, m_strMenuName, iLen);
		pcMenuName[iLen-1] = '\0';
	}
	if (NULL != puiID)
		*puiID =  m_uiID;

return NOERROR;
}

STDMETHODIMP CListItem :: GetEnum(IEnum<WListElement> ** ppIEn)
{
WEnumWListElement IEnLE (&m_EnumWListElement);

HRESULT hr = IEnLE -> Clone(ppIEn);
	if (FAILED(hr)) return hr;

return NOERROR;
}

STDMETHODIMP CListItem :: SetMenu(HMENU hMenu)
{
	ASSERT (hMenu);
	m_hMenu = hMenu;

return NOERROR;
}

STDMETHODIMP CListItem :: GetMenu(HMENU *phMenu)
{
	ASSERT(m_hMenu);
	*phMenu = m_hMenu;

return NOERROR;
}

STDMETHODIMP CListItem :: ClearItem (IListElement *pILE)
{
	if (NULL == pILE) {
		m_EnumWListElement.Clear();
		return NOERROR;
	}

WListElement ILE (pILE);
// pILE -> Release()
	m_EnumWListElement.ClearItem(ILE);

return NOERROR;
}

// *** IPersistStream methods
STDMETHODIMP CListItem :: GetClassID (CLSID *pClassID)
{
	*pClassID = CLSID_ListItem;
	return NOERROR;
}

STDMETHODIMP CListItem :: Load (os_bstream *pstream)
{
	ASSERT(pstream);
	os_read (*pstream, (CListElement &)(*this));
// Objekte selbst laden
	(*pstream) >> m_EnumWListElement;

return NOERROR;
}

STDMETHODIMP CListItem :: Save (os_bstream *pstream)
{
	ASSERT (pstream);
// erst Basisklasse
	os_write (*pstream, (const CListElement &)(*this));
// selbst
	(*pstream) << m_EnumWListElement;

return NOERROR;
}


//////////////////////////////////////////////////////////////////////
// *** Elementinstanz der Menüliste aus ID's ****
//////////////////////////////////////////////////////////////////////

CIDItem :: CIDItem()
			: CListElement()
{
	g_iIDI++;
}


CIDItem :: ~CIDItem()
{
	g_iIDI--;
}

STDMETHODIMP CIDItem :: Insert (LPCSTR pcMenuName, UINT uiID)
{
	ASSERT (pcMenuName);
	
	m_strMenuName = pcMenuName;
	m_uiID = uiID;

return NOERROR;
}

STDMETHODIMP CIDItem :: Insert (IListElement*pILE,
								IListElement *pILstEl_After)
{	
return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CIDItem :: Get (LPSTR pcMenuName, int iLen, UINT *puiID)
{
	ASSERT(!m_strMenuName.IsEmpty()); 
	ASSERT(iLen > 0);
	ASSERT(NULL != pcMenuName || NULL != puiID);
	
	if (NULL != pcMenuName) {
		strncpy (pcMenuName, m_strMenuName, iLen);
		pcMenuName[iLen-1] = '\0';
	}
	if (NULL != puiID)	
		*puiID = m_uiID;
	
return NOERROR;
}

STDMETHODIMP CIDItem :: GetEnum (IEnum<WListElement> ** ppIEn)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CIDItem :: SetMenu(HMENU hMenu)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CIDItem :: GetMenu(HMENU *phMenu)
{
return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CIDItem :: ClearItem (IListElement *pILE)
{
return ResultFromScode(E_NOTIMPL);
}

// *** IPersistStream methods
STDMETHODIMP CIDItem :: GetClassID (CLSID *pClassID)
{
	*pClassID = CLSID_IDItem;
	return NOERROR;
}

STDMETHODIMP CIDItem :: Load (os_bstream *pstream)
{
	ASSERT (pstream);
// erst Basisklasse
	os_read (*pstream, *(CListElement *)this);
// eigene Member in der Basisklasse

return NOERROR;
}

STDMETHODIMP CIDItem :: Save (os_bstream *pstream)
{
	ASSERT (pstream);
	os_write (*pstream, *(CListElement *)this);

return NOERROR;
}

