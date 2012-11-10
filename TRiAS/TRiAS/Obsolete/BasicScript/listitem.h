#ifndef _LISTITEM_H
#define _LISTITEM_H

#include <ospace/header.h>

class CListElement : public IListElement
{
private:
	DWORD m_dwRefCnt;
	bool FInit();

	class XPersistBStream : public IPersistBStream 
	{
	private:
		CListElement *m_pParent;

	public:
			XPersistBStream (CListElement *pParent);

	// *** IUnknown methods
		STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
		STDMETHOD_ (ULONG, AddRef) (THIS);
		STDMETHOD_ (ULONG, Release) (THIS);
		
	// *** IPersistBStream methods
		STDMETHOD (GetClassID) (THIS_ CLSID *pClassID);	
		STDMETHOD (Load) (THIS_ os_bstream *stream);
		STDMETHOD (Save) (THIS_ os_bstream *stream);
	};
	friend XPersistBStream;
	XPersistBStream *m_pBStream;

protected:
	CString m_strMenuName;
	UINT m_uiID;

public:
	CListElement();
	virtual ~CListElement();

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	
// *** IListElement methods
	STDMETHOD (Insert) (IListElement *pILE,
						IListElement *pILstEl_After);
	STDMETHOD (Insert) (LPCSTR strMenuName, UINT uiID);
	STDMETHOD (Get) (LPSTR strMenuName, int iLen, UINT *puiID);
	STDMETHOD (GetEnum) (IEnum<WListElement> ** ppIEn);
	STDMETHOD (SetMenu) (HMENU hMenu);
	STDMETHOD (GetMenu) (HMENU *phMenu);
	STDMETHOD (ClearItem) (IListElement *pILE);

	STDMETHOD (GetClassID) (THIS_ CLSID *pClassID) 
		{ return ResultFromScode(E_NOTIMPL); }	
	STDMETHOD (Load) (THIS_ os_bstream *stream) 
		{ return ResultFromScode(E_NOTIMPL); }
	STDMETHOD (Save) (THIS_ os_bstream *stream) 
		{ return ResultFromScode(E_NOTIMPL);}

	friend void os_write (os_bstream& stream, const CListElement& LE);
	friend void os_read (os_bstream& stream, CListElement& LE);

	OS_POLY_FUNCTION((CListElement *));
};

void os_write (os_bstream& stream, const CListElement& LE);
void os_read (os_bstream& stream, CListElement& LE);

OS_POLY_CLASS (CListElement);
OS_STREAM_OPERATORS (CListElement);

class CListItem : public CListElement 
{
private:
	MyEnum				m_EnumWListElement;
	HMENU				m_hMenu;

public:
	CListItem();
	~CListItem();
	
// *** IListElement methods
	STDMETHOD (Insert) (IListElement *pILE, IListElement *pILstEl_After);
	STDMETHOD (Insert) (LPCSTR strMenuName, UINT uiID);
	STDMETHOD (Get) (LPSTR strMenuName, int iLen, UINT *puiID);
	STDMETHOD (GetEnum) (IEnum<WListElement> ** ppIEn);
	STDMETHOD (SetMenu) (HMENU hMenu);
	STDMETHOD (GetMenu) (HMENU *phMenu);
	STDMETHOD (ClearItem) (IListElement *pILE);

	STDMETHOD (GetClassID) (THIS_ CLSID *pClassID);	
	STDMETHOD (Load) (THIS_ os_bstream *stream);
	STDMETHOD (Save) (THIS_ os_bstream *stream);

	friend void os_write (os_bstream& stream, const CListItem& LI);
	friend void os_read (os_bstream& stream, CListItem& LI);

	OS_POLY_FUNCTION((CListItem *));
};

void os_write (os_bstream& stream, const CListItem& LI);
void os_read (os_bstream& stream, CListItem& LI);

OS_POLY_CLASS (CListItem);
OS_STREAM_OPERATORS (CListItem);

class CIDItem : public CListElement 
{
private:

public:
	CIDItem();
	~CIDItem();

// *** IListElement methods
	STDMETHOD (Insert) (IListElement *pILE, IListElement *pILstEl_After);
	STDMETHOD (Insert) (LPCSTR strMenuName, UINT uiID);
	STDMETHOD (Get) (LPSTR strMenuName, int iLen, UINT *puiID);
	STDMETHOD (GetEnum) (THIS_ IEnum<WListElement> ** ppIEn);
	STDMETHOD (SetMenu) (HMENU hMenu);
	STDMETHOD (GetMenu) (HMENU *phMenu);
	STDMETHOD (ClearItem) (IListElement *pILE);

	STDMETHOD (GetClassID) (THIS_ CLSID *pClassID);	
	STDMETHOD (Load) (THIS_ os_bstream *stream);
	STDMETHOD (Save) (THIS_ os_bstream *stream);

	friend void os_write (os_bstream& stream, const CIDItem& IDI);
	friend void os_read (os_bstream& stream, CIDItem& IDI);

	OS_POLY_FUNCTION((CIDItem *));
};

OS_POLY_CLASS (CIDItem);
OS_STREAM_OPERATORS (CIDItem);

HRESULT CreateObject(CLSID *pClID, LPVOID *ppv);

#endif // _LISTITEM_H

