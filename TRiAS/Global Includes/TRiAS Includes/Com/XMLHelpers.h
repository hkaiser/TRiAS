#if !defined(__TRIASXMLHELPERS_H_AA712F10_0DFA_11d3_9967_0060085FC1CE)
#define __TRIASXMLHELPERS_H_AA712F10_0DFA_11d3_9967_0060085FC1CE

////////////////////////////////////////////////////////////////////////////////
// @doc
// @module XMLHelpers.h | Wrapperfunktionen / -objekte für den Zugriff auf
//		XML-Dokumente

const int _XMLHelpersEnumChunk = 10;		// Anzahl Element die bei Enumeration abgefragt werden

#if defined(__IXMLElement2_FWD_DEFINED__)
typedef XMLELEM_TYPE xmlelemTYPE;
#endif // defined(__IXMLElement2_FWD_DEFINED__)

////////////////////////////////////////////////////////////////////////
// @doc |
// @class CXMLDocument | Basiswrapperklasse für XLM-Documente (MSXML.dll)

class CXMLDocument {
protected:
	WXMLDocument	m_pXMLDocument;
	//////////////////////////////////////////////////////////////////////////
	// "rohes" Hinzufügen eines benamten Elements zu einem anderen
	HRESULT RawAddElement( IXMLElement* pItemParent, xmlelemTYPE type, const VARIANT& vTag, IXMLElement** ppElement ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vTag), E_FAIL );
		RETURN_EXPR_TRUE( NULL == ppElement, E_POINTER );
		RETURN_FAILED_HRESULT( m_pXMLDocument->createElement( CComVariant(type), vTag, ppElement ) );
		_ASSERTE(*ppElement);
		RETURN_FAILED_HRESULT( pItemParent->addChild( *ppElement, -1, -1 ) );
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// "rohes" Hinzufügen eines leeren Elements zu einem anderen
	HRESULT RawAddElement( IXMLElement* pItemParent, xmlelemTYPE type, IXMLElement** ppElement ) {
		RETURN_EXPR_TRUE( NULL == ppElement, E_POINTER );
		CComVariant vTag;		// VT_EMPTY
		RETURN_FAILED_HRESULT( m_pXMLDocument->createElement( CComVariant(type), vTag, ppElement ) );
		_ASSERTE(*ppElement);
		RETURN_FAILED_HRESULT( pItemParent->addChild( *ppElement, -1, -1 ) );
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// Überprüfen, ob ein bestimmtes Element von einem bestimmten Typ ist
	HRESULT CheckItem( IXMLElement* pXMLElement, const VARIANT& vNeededParent ) {
		if( !m_bCheckParents )
			return S_OK;
		RETURN_EXPR_FALSE( V_ISBSTR(&vNeededParent), E_FAIL );
		CComBSTR	strName;
		RETURN_FAILED_HRESULT( pXMLElement->get_tagName( &strName ) );
		if( 0 != _wcsicmp( V_BSTR(&vNeededParent), strName ) ) {
			_ASSERTE( SUCCEEDED(E_FAIL) );		// ab zum Debugger...
			return E_FAIL;
		}
		return S_OK;
	}
	CComVariant	m_strNIL;
	CComVariant	m_strAttributesTag;
	CComVariant	m_strAttributeTag;
	CComVariant	m_strNameProp;
	CComVariant	m_strValueProp;
	HRESULT InitStrings() {
		m_strNIL = CComVariant(L"");
		m_strNameProp = CComVariant(L"name");
		m_strAttributesTag = CComVariant(L"attributes");
		m_strAttributeTag = CComVariant(L"attribute");
		m_strValueProp = CComVariant(L"value");
		return S_OK;
	}
public:
	bool	m_bCheckParents;		// public Datenmember; darf direkt manipuliert werden
	CXMLDocument( )
		: m_bCheckParents(true)
	{
		HRESULT	hr = ::CoCreateInstance( CLSID_XMLDocument, NULL, CLSCTX_ALL, m_pXMLDocument.GetIID(), m_pXMLDocument.ppv() );
		if( FAILED(hr) )
			throw(hr);
		{ HRESULT hr = InitStrings(); if(FAILED(hr)) {_com_issue_error(hr);} };
	}
	CXMLDocument( IXMLDocument* pXMLDocument )
		: m_pXMLDocument(pXMLDocument) {
		_ASSERTE( m_pXMLDocument.IsValid() );
		{ HRESULT hr = InitStrings(); if(FAILED(hr)) {_com_issue_error(hr);} };
	}
	operator IXMLDocument*() {
		return m_pXMLDocument;
	}
	IXMLDocument* operator->(void) {
		return m_pXMLDocument;
	}

	//////////////////////////////////////////////////////////////////////////
	// grundlegende Tag's / Attributnamen

	const CComVariant& NIL() { return m_strNIL; }
	const CComVariant& AttributesTag() { return m_strAttributesTag; }
	const CComVariant& AttributeTag() { return m_strAttributeTag; }
	const CComVariant& NameProp() { return m_strNameProp; }
	const CComVariant& ValueProp() { return m_strValueProp; }

	HRESULT GetRoot( IXMLElement** ppXMLElement ) {
		HRESULT	hr;
		RETURN_EXPR_FALSE( m_pXMLDocument.IsValid(), E_UNEXPECTED );
		RETURN_FAILED_HRESULT( hr = m_pXMLDocument->get_root(ppXMLElement) );
		return S_OK;
	}
	HRESULT LoadFromURL( const BSTR& strURL ) {
		HRESULT	hr;
		RETURN_EXPR_FALSE( m_pXMLDocument.IsValid(), E_FAIL );
		RETURN_FAILED_HRESULT( hr = m_pXMLDocument->put_URL( strURL ) );
		return S_OK;
	}
	HRESULT AddDocument( IXMLElement* pItemParent, const VARIANT& vTag, IXMLElement** ppElement ) {
		return RawAddElement( pItemParent, XMLELEMTYPE_DOCUMENT, vTag, ppElement );
	}
	HRESULT AddElement( IXMLElement* pItemParent, const VARIANT& vTag, IXMLElement** ppElement ) {
		return RawAddElement( pItemParent, XMLELEMTYPE_ELEMENT, vTag, ppElement );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines Kommentars (BSTR, UNICODE, ANSI)
	HRESULT AddComment( IXMLElement* pXMLElement, const BSTR& strComment ) {
		HRESULT	hr;
		WXMLElement	pComment;
		RETURN_FAILED_HRESULT( hr = RawAddElement( pXMLElement, XMLELEMTYPE_COMMENT, pComment.ppi() ) );
// KK000621
		BSTR eptr = wcsrchr (strComment,L'\0');
		if ( eptr) {
			eptr--;
			if ( *eptr == '-') {
				*eptr = '\0';
			}
			
		}

		RETURN_FAILED_HRESULT( hr = pComment->put_text( strComment ) );
		return S_OK;
	}
	HRESULT AddComment( IXMLElement* pXMLElement, LPCOLESTR lpszComment ) {
		return AddComment( pXMLElement, CComBSTR(lpszComment) );
	}
	HRESULT AddComment( IXMLElement* pXMLElement, LPCTSTR lpszComment ) {
		return AddComment( pXMLElement, CComBSTR(lpszComment) );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen von Text (BSTR, UNICODE, ANSI)
	HRESULT AddText( IXMLElement* pXMLElement, const BSTR& strText ) {
		HRESULT	hr;
		WXMLElement	pText;
		RETURN_FAILED_HRESULT( hr = RawAddElement( pXMLElement, XMLELEMTYPE_TEXT, pText.ppi() ) );
		RETURN_FAILED_HRESULT( hr = pText->put_text( strText ) );
		return S_OK;
	}
	HRESULT AddText( IXMLElement* pXMLElement, LPCOLESTR lpszText ) {
		return AddText( pXMLElement, CComBSTR(lpszText) );
	}
	HRESULT AddText( IXMLElement* pXMLElement, LPCTSTR lpszText ) {
		return AddText( pXMLElement, CComBSTR(lpszText) );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines Elements
	HRESULT AddItem( IXMLElement* pItemParent, const VARIANT& vTag, IXMLElement** ppElement ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vTag), E_FAIL );
		return RawAddElement( pItemParent, XMLELEMTYPE_ELEMENT, vTag, ppElement );
	}
	HRESULT AddItem( IXMLElement* pItemParent, LPCOLESTR lpszTag, IXMLElement** ppElement ) {
		return AddItem( pItemParent, CComVariant(lpszTag), ppElement );
	}
	HRESULT AddItem( IXMLElement* pItemParent, LPCTSTR lpszTag, IXMLElement** ppElement ) {
		return AddItem( pItemParent, CComVariant(lpszTag), ppElement );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines Tag mit einem bestimmten Namen: <TAGFoo NAME="NameBar">
	HRESULT AddNamedItem( IXMLElement* pItemParent, const VARIANT& vTag, const VARIANT& vName, IXMLElement** ppElement ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vTag), E_FAIL );
		RETURN_EXPR_FALSE( V_ISBSTR(&vName), E_FAIL );
		HRESULT	hr;
		RETURN_FAILED_HRESULT( hr = RawAddElement( pItemParent, XMLELEMTYPE_ELEMENT, vTag, ppElement ) );
		_ASSERTE(*ppElement);
		RETURN_FAILED_HRESULT( hr = (*ppElement)->setAttribute( V_BSTR(&NameProp()), vName ) );
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines Containers
	HRESULT AddContainer( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vParent, IXMLElement** ppElement ) {
		RETURN_FAILED_HRESULT( CheckItem( pItemParent, vParent ) );
		return RawAddElement( pItemParent, XMLELEMTYPE_ELEMENT, vName, ppElement );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines benamten Elements zu einem Container
	HRESULT AddContainerItem( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vParent, const VARIANT &vEntry, IXMLElement** ppElement ) {
		RETURN_FAILED_HRESULT( CheckItem( pItemParent, vParent ) );
		return AddNamedItem( pItemParent, vName, vEntry, ppElement );
	}
	//////////////////////////////////////////////////////////////////////////
	// Suchen eines Containers, anlegen wenn nicht vorhanden
	HRESULT GetOrCreateContainer( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vParent, IXMLElement** ppElement ) {
		HRESULT hr;
		RETURN_FAILED_HRESULT( hr = FindItem( pItemParent, vName, ppElement ) );
		if( S_FALSE == hr ) {
			RETURN_FAILED_HRESULT( hr = AddContainer( pItemParent, vName, vParent, ppElement ) );
			return S_OK;
		}
		return S_FALSE;		// nicht neu angelegt
	}
	//////////////////////////////////////////////////////////////////////////
	// Suchen eines Containerelements, anlegen wenn nicht vorhanden
	HRESULT GetOrCreateContainerItem( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vParent, const VARIANT& vEntry, IXMLElement** ppElement ) {
		HRESULT hr;
		RETURN_FAILED_HRESULT( hr = FindItem( pItemParent, vName, NameProp(), vEntry, ppElement ) );
		if( S_FALSE == hr ) {
			RETURN_FAILED_HRESULT( hr = AddContainerItem( pItemParent, vName, vParent, vEntry, ppElement ) );
			return S_OK;
		}
		return S_FALSE;		// nicht neu angelegt
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines einzelnen Attributes zu einem Tag
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const VARIANT& vAttr ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vAttr), E_FAIL );
		RETURN_EXPR_FALSE( V_ISBSTR(&vName), E_FAIL );
		HRESULT	hr;
		RETURN_FAILED_HRESULT( hr = pItem->setAttribute( V_BSTR(&vName), vAttr ) );
		return S_OK;
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const short& attr ) {
		CComVariant	vAttr(attr);
		vAttr.ChangeType( VT_BSTR );
		return AddAttribute( pItem, vName, vAttr );
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const LONG& attr ) {
		CComVariant	vAttr(attr);
		vAttr.ChangeType( VT_BSTR );
		return AddAttribute( pItem, vName, vAttr );
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const BYTE& attr ) {
		CComVariant	vAttr(attr);
		vAttr.ChangeType( VT_BSTR );
		return AddAttribute( pItem, vName, vAttr );
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const char& attr ) {
		CComVariant	vAttr(attr);
		vAttr.ChangeType( VT_BSTR );
		return AddAttribute( pItem, vName, vAttr );
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const double& attr ) {
		CComVariant	vAttr(attr);
		::VariantChangeTypeEx( &vAttr, &vAttr, MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US), 0, VT_BSTR );
		return AddAttribute( pItem, vName, vAttr );
	}
	HRESULT AddAttribute( IXMLElement* pItem, const VARIANT& vName, const BSTR& attr ) {
		CComVariant	vAttr(attr);
		return AddAttribute( pItem, vName, vAttr );
	}
	//////////////////////////////////////////////////////////////////////////
	// Erzeugen eines neuen Attributcontainers
	HRESULT GetOrCreateAttributes( IXMLElement* pItemParent, const VARIANT& vParent, IXMLElement** ppAttributes ) {
		HRESULT	hr;
		RETURN_FAILED_HRESULT( hr = GetOrCreateContainer( pItemParent, AttributesTag(), vParent, ppAttributes ) );
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines einzelnen Attributes zu einem Attributcontainer
	HRESULT AddAttributeItem( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vValuename, const VARIANT& vAttr, IXMLElement** ppAttribute ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vAttr), E_FAIL );
		RETURN_EXPR_FALSE( V_ISBSTR(&vValuename), E_FAIL );
		RETURN_EXPR_TRUE( NULL == ppAttribute, E_POINTER )
		HRESULT	hr;
		RETURN_FAILED_HRESULT( hr = AddContainerItem( pItemParent, vName, AttributesTag(), vValuename, ppAttribute ) );
		_ASSERTE(*ppAttribute);
		RETURN_FAILED_HRESULT( hr = (*ppAttribute)->setAttribute( V_BSTR(&vValuename), vAttr ) );
		return S_OK;
	}
	HRESULT AddAttributeItem( IXMLElement* pItemParent, const VARIANT& vName, const VARIANT& vValuename, const short& sVal, IXMLElement** ppAttribute ) {
		CComVariant	vAttr(sVal);
		vAttr.ChangeType(VT_BSTR);
		return AddAttributeItem( pItemParent, vName, vValuename, vAttr, ppAttribute );
	}
	//////////////////////////////////////////////////////////////////////////
	// Hinzufügen eines einzelnen Attributes zu einem Attributcontainer; Attribut
	// wird als Text angelegt
	HRESULT AddAttributeItem( IXMLElement* pItemParent, const VARIANT& vName, const BSTR& strText, IXMLElement** ppAttribute ) {
		RETURN_EXPR_FALSE( V_ISBSTR(&vName), E_FAIL );
		RETURN_EXPR_TRUE( NULL == ppAttribute, E_POINTER )
		HRESULT	hr;
		RETURN_FAILED_HRESULT( hr = GetOrCreateContainerItem( pItemParent, AttributeTag(), AttributesTag(), vName, ppAttribute ) );
		_ASSERTE(*ppAttribute);
		RETURN_FAILED_HRESULT( hr = AddText( (*ppAttribute), strText ) );
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// suchen eines bestimmten Parenttag 
	HRESULT FindSpecificParent( IXMLElement* pStart, const VARIANT& vSearchedTag, IXMLElement** ppParent ) {
		_ASSERTE( V_ISBSTR(&vSearchedTag) );
		HRESULT	hr;
		WXMLElement	pParent;
		hr = pStart->get_parent( pParent.ppi() );
		if( FAILED( hr ) )
			return S_FALSE;
		if( S_FALSE == hr )
			return S_FALSE;
		CComBSTR	strFoundTag;
		RETURN_FAILED_HRESULT( hr = pParent->get_tagName( &strFoundTag ) );
		if( 0 != wcsicmp( V_BSTR(&vSearchedTag), strFoundTag ) ) {
			return FindSpecificParent( pParent, vSearchedTag, ppParent );
		}
		*ppParent = pParent.Detach();
		return S_OK;
	}
	//////////////////////////////////////////////////////////////////////////
	// suchen nach einem bestimmten Tag
	HRESULT FindItem( IXMLElement* pParent, const VARIANT& vTagname, IXMLElement** ppXMLElement ) {
		HRESULT	hr;
		WXMLElementCollection	pXMLElementCollection;
		RETURN_FAILED_HRESULT( hr = pParent->get_children( pXMLElementCollection.ppi() ) );
		if( S_FALSE == hr ) return hr;
		_ASSERTE( pXMLElementCollection.IsValid() );
		WDispatch	pDispatch;
		WXMLElement	pXMLElement;

// KK991209
		if ( FAILED ( hr = pXMLElementCollection->item( vTagname, vtMissing, pDispatch.ppi() ) ) || hr == S_FALSE) 
			return S_FALSE;


//		if( FAILED( hr = pXMLElementCollection->item( vTagname, vtMissing, pDispatch.ppi() ) ) ) {
//			return S_FALSE;
//		}
		RETURN_FAILED_HRESULT( hr = pDispatch->QueryInterface( pXMLElement.GetIID(), pXMLElement.ppv() ) );
		*ppXMLElement = pXMLElement.Detach();
		return S_OK;
/*
		WEnumVARIANT	pEnum;
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get__newEnum( pEnum.ppu() ) );
		CComVariant	vItems[_XMLHelpersEnumChunk];
		ULONG		ulFetched;
		WXMLElement	pItem;
		WXMLElement	pFoundItem;
		RETURN_FAILED_HRESULT( hr = pEnum->Reset() );
		RETURN_FAILED_HRESULT( hr = pEnum->Next( _XMLHelpersEnumChunk, vItems, &ulFetched ) );
		while( ulFetched ) {
			for( ULONG lItem = 0; lItem != ulFetched; ++lItem ) {
				_ASSERTE(V_ISDISPATCH(&vItems[lItem]));
				if( !pFoundItem.IsValid() ) {		// bis jetzt noch nichts gefunden
					CComBSTR	strFoundTagname;
					hr = V_DISPATCH(&vItems[lItem])->QueryInterface( pItem.GetIID(), pItem.ppv() );
					pItem->get_tagName( &strFoundTagname );
					if( strFoundTagname && 0 == wcsicmp( strFoundTagname, V_BSTR(&vTagname) ) ) {
						pFoundItem = WXMLElement(V_DISPATCH(&vItems[lItem]));
					}
				}
				::VariantClear(&vItems[lItem]);		// VARIANT bereinigen
			}
			if( pFoundItem.IsValid() ) {
				*ppXMLElement = pFoundItem.Detach();
				return S_OK;
			}
			if( ulFetched < _XMLHelpersEnumChunk )
				break;
			RETURN_FAILED_HRESULT( hr = pEnum->Next( _XMLHelpersEnumChunk, vItems, &ulFetched ) );
		}
		return pFoundItem.IsValid() ? S_OK : S_FALSE;
*/
	}
	//////////////////////////////////////////////////////////////////////////
	// suchen nach einem Element 
	HRESULT FindItem( IXMLElement* pParent, const VARIANT& vTagname, const VARIANT& vPropname, const VARIANT& vPropValue, IXMLElement** ppXMLElement ) {
		HRESULT	hr;
		WXMLElementCollection	pXMLElementCollection;
		RETURN_FAILED_HRESULT( hr = pParent->get_children( pXMLElementCollection.ppi() ) );
		if( S_FALSE == hr ) return hr;
		WEnumVARIANT	pEnum;
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get__newEnum( pEnum.ppu() ) );
		CComVariant	vItems[_XMLHelpersEnumChunk];
		ULONG		ulFetched;
		WXMLElement	pItem;
		WXMLElement	pFoundItem;
		RETURN_FAILED_HRESULT( hr = pEnum->Reset() );
		RETURN_FAILED_HRESULT( hr = pEnum->Next( _XMLHelpersEnumChunk, vItems, &ulFetched ) );
		while( ulFetched ) {
			for( ULONG lItem = 0; lItem != ulFetched; ++lItem ) {
				_ASSERTE(V_ISDISPATCH(&vItems[lItem]));
				if( !pFoundItem.IsValid() ) {		// bis jetzt noch nichts gefunden
					CComBSTR	strFoundTagname;
					CComVariant	vPropertyvalue;
					hr = V_DISPATCH(&vItems[lItem])->QueryInterface( pItem.GetIID(), pItem.ppv() );
					pItem->get_tagName( &strFoundTagname );
					pItem->getAttribute( V_BSTR(&vPropname), &vPropertyvalue );
					vPropertyvalue.ChangeType( VT_BSTR );
					if( strFoundTagname && 0 == wcsicmp( strFoundTagname, V_BSTR(&vTagname) ) && 0 == wcsicmp( V_BSTR(&vPropertyvalue), V_BSTR(&vPropValue) ) ) {
						pFoundItem = WXMLElement(V_DISPATCH(&vItems[lItem]));
					}
				}
				::VariantClear(&vItems[lItem]);		// VARIANT bereinigen
			}
			if( pFoundItem.IsValid() ) {
				*ppXMLElement = pFoundItem.Detach();
				return S_OK;
			}
			if( ulFetched < _XMLHelpersEnumChunk )
				break;
			RETURN_FAILED_HRESULT( hr = pEnum->Next( _XMLHelpersEnumChunk, vItems, &ulFetched ) );
		}
		return S_FALSE;
	}
};

//////////////////////////////////////////////////////////////////////////////////
// @doc
// @normal Helfer zum Konvertieren eines VARIANT in einen definierten Typ
namespace VariantConvertHelper {
	class VT {
		VARIANT& m_v;
	public:
		VT( VARIANT& v) : m_v(v){};
		operator char() const	{ HRESULT hr = ::VariantChangeType( &m_v, &m_v, 0, VT_I1); if(FAILED(hr)) {_com_issue_error(hr);} return V_I1(&m_v); }
		operator short() const	{ HRESULT hr = ::VariantChangeType( &m_v, &m_v, 0, VT_I2); if(FAILED(hr)) {_com_issue_error(hr);} return V_I2(&m_v); }
		operator LONG() const	{ HRESULT hr = ::VariantChangeType( &m_v, &m_v, 0, VT_I4); if(FAILED(hr)) {_com_issue_error(hr);}; return V_I4(&m_v); }
		operator LPCOLESTR&() const	{ HRESULT hr = ::VariantChangeType( &m_v, &m_v, 0, VT_BSTR); if(FAILED(hr)) {_com_issue_error(hr);}; return V_BSTR(&m_v); }
	};
} // namespace

//////////////////////////////////////////////////////////////////////////////////
// @doc Auslesen eines Attributwertes aus einem Tag
// @ex |
// // In der XML-Datei möge das folgende Tag stehen:
// // <TAGFoo STRINGATTRIBUT="string" SHORTATTRIBUT="20">
// // Die Attributwerte können wie folg ausgelesen werden:
// short shortVal;
// CComBSTR strVal;
// RetrieveAttribute( pElement, L"SHORTATTRIBUT", shortVal );
// RetrieveAttribute( pElement, L"STRINGATTRIBUT", strVal );
template<class T>
inline HRESULT RetrieveAttribute( IXMLElement* pAttribute, const VARIANT& vName, T& val ) {
	RETURN_EXPR_FALSE( V_ISBSTR(&vName), E_FAIL );
	CComVariant	vValue;
	if( S_OK != pAttribute->getAttribute( V_BSTR(&vName), &vValue ) )
		return S_FALSE;
	using namespace VariantConvertHelper;
	VT	v(vValue);
	try { val = (T) v; } catch(...) { return E_FAIL; }
	return S_OK;
}

template<class T>
inline HRESULT RetrieveAttribute( IXMLElement* pAttribute, const BSTR& strName, T& val ) {
	CComVariant	vValue;
	if( S_OK != pAttribute->getAttribute( strName, &vValue ) )
		return S_FALSE;
	using namespace VariantConvertHelper;
	VT	v(vValue);
	try { val = (T) v; } catch(...) { return E_FAIL; }
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////
// @doc Auslesen eines Attributwertes aus einem Attributcontainer
// @ex |
// // Eine XML-Datei möge die folgenden Tag's enthalten:
// // <attributes><attribute name="path" value="Thepathname"/></attributes>
// // Bei vorhandenem Zeiger auf den Attributcontainer kann der Wert von "path" wie
// // folgt ermittelt werden:
// CComBSTR strPath;
// RetrieveAttribute( doc, pAttributes, L"path", L"value", shortVal );
// 
template<class T>
inline HRESULT RetrieveAttribute( CXMLDocument& doc, WXMLElement& pAttributes, const VARIANT& vName, const VARIANT& vItem, T& val ) {
	WXMLElement	pAttribute;
	if( S_OK != doc.FindItem( pAttributes, doc.AttributeTag(), doc.NameProp(), vName, pAttribute.ppi() ) )
		return S_FALSE;
	return RetrieveAttribute( pAttribute, vItem, val );
}

////////////////////////////////////////////////////////////////////////
// Auslesen eines SIZE-Attributes
inline HRESULT RetrieveAttribute( IXMLElement* pAttribute, const VARIANT& vName, SIZE& val ) {
	RETURN_EXPR_FALSE( V_ISBSTR(&vName), E_FAIL );
	CComBSTR	s;
	short	cx, cy;
	s = V_BSTR(&vName); s.Append(L":cx"); RETURN_FAILED_HRESULT( RetrieveAttribute( pAttribute, s, cx ) );
	s = V_BSTR(&vName); s.Append(L":cy"); RETURN_FAILED_HRESULT( RetrieveAttribute( pAttribute, s, cy ) );
	val.cx = cx;
	val.cy = cy;
	return S_OK;
}

////////////////////////////////////////////////////////////////////////
// Auslesen eines COLORREF-Attributes
inline HRESULT RetrieveAttribute( IXMLElement* pAttribute, const VARIANT& vName, COLORREF& val ) {
	CComBSTR	s;
	short	r,g,b;
	s = V_BSTR(&vName); s.Append(L":r"); RETURN_FAILED_HRESULT( RetrieveAttribute( pAttribute, s, r ) );
	s = V_BSTR(&vName); s.Append(L":g"); RETURN_FAILED_HRESULT( RetrieveAttribute( pAttribute, s, g ) );
	s = V_BSTR(&vName); s.Append(L":b"); RETURN_FAILED_HRESULT( RetrieveAttribute( pAttribute, s, b ) );
	val = RGB(r,g,b);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////
// Traversieren eines XML - Baumes

template<class T, class X, class F>
class NodeFunc {
	IXMLElement*	m_pXMLElement;
	X&				m_XMLDocument;
	F				m_pFunc;
	T				*m_pT;
public:
	NodeFunc( T *pT, X& XMLDocument, IXMLElement* pXMLElement )
		: m_XMLDocument(XMLDocument)
		, m_pXMLElement(pXMLElement)
		, m_pFunc(NULL)
		, m_pT(pT)
	{}
	~NodeFunc() {
		if( m_pFunc ) {
// KK991209
//			{ HRESULT hr = (m_pT->*m_pFunc)( false, m_XMLDocument, m_pXMLElement ); if(FAILED(hr)) {_com_issue_error(hr);} }
			{ HRESULT hr = (m_pT->*m_pFunc)( false, m_XMLDocument, m_pXMLElement );  if(FAILED(hr)) _ASSERTE (hr == S_OK); }
		}
	}
	HRESULT Assign( F pFunc ) {
		HRESULT	hr;
		_ASSERTE( NULL == m_pFunc );
		m_pFunc = pFunc;
		{ /*HRESULT*/ hr = (m_pT->*m_pFunc)( true, m_XMLDocument, m_pXMLElement ); if(FAILED(hr)) {_com_issue_error(hr);} }
		return hr;
	}
};

////////////////////////////////////////////////////////////////////////
// @doc |
// @class CXMLTraverse | Templateklasse zum traversieren eines XML-Baumes
// @parm T | 
// @parm X | Eine von CXMLDocument abgeleitete Klasse

template<class T, class X>
class CXMLTraverse {
protected:
	typedef HRESULT (T::*XMLENTRYFUNC)(bool,X&,IXMLElement*);
	typedef struct { LPCOLESTR lpszTag; XMLENTRYFUNC pFunc; } XMLMAPENTRY, *LPXMLMAPENTRY;
	HRESULT	Traverse( X& doc ) {
		HRESULT	hr;
		WXMLElement	pXMLRoot;
		RETURN_FAILED_HRESULT( hr = doc.GetRoot( pXMLRoot.ppi() ) );
		RETURN_FAILED_HRESULT( hr = Traverse( doc, pXMLRoot, 0 ) );
		return S_OK;
	}
	HRESULT Traverse( X& doc, IXMLElement* pXMLElement, DWORD dwMapID = 0 ) {
		HRESULT	hr;
		T*	pT = static_cast<T*>(this);
		NodeFunc<T,X,XMLENTRYFUNC>	pFunc( pT, doc, pXMLElement );
		CComBSTR	strTag;
		pXMLElement->get_tagName( &strTag );
		if( !strTag ) {
			return S_FALSE;
		}
		LPXMLMAPENTRY	pXMLMAPENTRY = pT->GetXMLMap( dwMapID );
		register OLECHAR firstChar = tolower(*strTag);
		while( pXMLMAPENTRY->lpszTag ) {
			if( *pXMLMAPENTRY->lpszTag == firstChar && 0 == wcsicmp( pXMLMAPENTRY->lpszTag, strTag ) ) {
				if( NULL == pXMLMAPENTRY->pFunc )
					return S_FALSE;
				hr = pFunc.Assign( pXMLMAPENTRY->pFunc );
				if( S_FALSE == hr )
					return S_OK;
				break;
			}
			++pXMLMAPENTRY;
		}
		WXMLElementCollection	pXMLElementCollection;
		WEnumVARIANT	pEnum;
		long			lItems;
		RETURN_FAILED_HRESULT( hr = pXMLElement->get_children( pXMLElementCollection.ppi() ) );
		if( S_FALSE == hr ) return S_FALSE;			// kein Kindergarten vorhanden
		_ASSERTE( pXMLElementCollection.IsValid() );
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get_length( &lItems ) );
		if( 0 == lItems ) return S_FALSE;			// Kindergarten ja, aber keine Kinder
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get__newEnum(pEnum.ppu() ) );
		if( S_FALSE == hr ) return S_FALSE;			// komisch; dürfte es eigentlich nicht geben
		_ASSERTE( pEnum.IsValid() );
		CComVariant		vEntry;
		DWORD			dwFetched;
		WXMLElement		pChild;
		for( pEnum->Reset(); S_OK == pEnum->Next( 1, &vEntry, &dwFetched ); vEntry.Clear() ) {
			if( !V_ISDISPATCH(&vEntry) )
				continue;
			if( FAILED( hr = V_DISPATCH(&vEntry)->QueryInterface( pChild.GetIID(), pChild.ppv() ) ) || S_FALSE == hr )
				continue;
			Traverse( doc, pChild, dwMapID );
		}
		return S_OK;
	}
};

////////////////////////////////////////////////////////////////////////
// @doc |
// @func BEGIN_XML_MAP | Beginn einer XML-Map
// @param theClass | [in] der Name der Klasse für die die XML-Map 
//		bereitgestellt wird
// @normal Eine XML-Map steuert die Traversierung eines XML-Baumes durch
//		CXMLTraverse<class T>.

#define BEGIN_XML_MAP(theClass)								\
	static LPXMLMAPENTRY GetXMLMap(DWORD dwXmlMapID = 0) {	\
		if( 0 == dwXmlMapID ) {								\
			static XMLMAPENTRY xmlMapEntries[] = {

////////////////////////////////////////////////////////////////////////
// @doc |
// @func ALT_XML_MAP | Beginn einer alternativen XML-Map
// @param xmlMapID | Identifikator für die alternative XML-Map
// @normal Markiert den Beginn einer alternativen XML-Map. Die Auteilung
//		einer XML-Map in verschiedene Teilmaps erlaubt den Traversierungsvorgang
//		differenzierter zu steuern.
// @ex Nutzung von ALT_XML_MAP |
//	BEGIN_XML_MAP(CFoo)
//		XML_ENTRY( L"datasource", OnDatasource )
//	ALT_XML_MAP(1)
//		XML_ENTRY( L"object", OnObject )
//	END_XML_MAP()
//	HRESULT OnDatasource( bool bStart, CXMLDocument& doc, IXMLElement* pDatasource ) {
//		if( bStart ) {
//			/////////////////////////////////////////////////////////////
//			// Traversiere und benutze die alternative Map Nummer 1
//			HRESULT hr = Traverse( doc, pDatasource, 1 );
//			/////////////////////////////////////////////////////////////
//			// S_FALSE => traversiere nicht weiter, d.h. tieferliegende 
//			// Knoten werden nicht durchforstet; mithin werden z.B \<object\>
//			// Tag's die unterhalb des \<datasource\>-Tags hängen nicht
//			// noch einmal durchlaufen (sie wurden ja schon im eben gerufenen
//			// Traverse( doc, pDatasource, 1 ) abgearbeitet.
//			return S_FALSE;
//		}
//		/////////////////////////////////////////////////////////////
//		// wenn nicht Eintritt in den Knoten ist der Rückkehrwert egal;
//		// S_OK ist eine gute Wahl
//		return S_OK;
//	}
//	HRESULT OnObject( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pObject ) {
//		if( bStart ) {
//			// irgendetwas mit pObject anstellen
//		} else {
//			// irgendetwas anderes mit pObject anstellen
//		}
//		return S_OK;
//	}

#define	ALT_XML_MAP(xmlMapID)		\
				{NULL,NULL}			\
			};						\
			return xmlMapEntries;	\
		} else if( xmlMapID == dwXmlMapID ) {	\
			static XMLMAPENTRY xmlMapEntries[] = {

////////////////////////////////////////////////////////////////////////
// @doc |
// @func XML_ENTRY | Definiert einen Eintrag in der XML-Map
// @parm entryTag | [in] Name des Tag's welches bearbeitet werden soll
// @parm entryFunc | [in] die Funktion welche für die Bearbeitung zuständig ist

#define	XML_ENTRY(entryTag,entryFunc) \
				{entryTag, entryFunc},

////////////////////////////////////////////////////////////////////////
// @doc |
// @func END_XML_MAP | Markiert das Ende einer XML-Map

#define END_XML_MAP() \
				{ NULL, NULL } \
			}; \
			return xmlMapEntries; \
		} \
		return NULL; \
	}

#endif // __TRIASXMLHELPERS_H_AA712F10_0DFA_11d3_9967_0060085FC1CE
