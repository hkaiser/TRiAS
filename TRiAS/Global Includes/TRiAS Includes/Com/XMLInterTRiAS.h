#if !defined(__XMLINTERTRIAS_H__B82CDCD1_2495_11d3_9982_0060085FC1CE)
#define __XMLINTERTRIAS_H__B82CDCD1_2495_11d3_9982_0060085FC1CE

////////////////////////////////////////////////////////////////////////////
// @doc 
// @module XMLInterTRiAS.h | Helferobjekt für die Erzeugung / das Lesen von
//		XML - Bäumen. Insbesondere werden hier alle(?) verwendeten Tag's und
//		Attributnamen bereitgestellt. Eine Hardcodierung dieser Namen sollte
//		damit obsolete sein.

#include <com/XMLHelpers.h>	// Basis-XML-Funktionalität
#include <stdio.h>		// sprintf

class CTRiASXMLDocument : public CXMLDocument {
	HRESULT CreateRootXML( ) {
//		LPCTSTR	lpszGeneric = "<project><header><entries></entries></header><views></views><datasources></datasources></project>";
		LPCTSTR	lpszGeneric = "<project></project>";
		HRESULT	hr;

		WStream	pStreamW;
		WStream	pStreamR;
		RETURN_FAILED_HRESULT( hr = ::CreateStreamOnHGlobal( NULL, true, pStreamW.ppi() ) );
		RETURN_FAILED_HRESULT( hr = pStreamW->Clone( pStreamR.ppi() ) );
		RETURN_FAILED_HRESULT( hr = pStreamW->Write( lpszGeneric, strlen(lpszGeneric), NULL ) );

		WPersistStreamInit	pPersistStreamInit;
		RETURN_FAILED_HRESULT( hr = ::CoCreateInstance( CLSID_XMLDocument, NULL, CLSCTX_ALL, m_pXMLDocument.GetIID(), m_pXMLDocument.ppv() ) );
		RETURN_FAILED_HRESULT( hr = m_pXMLDocument->QueryInterface( pPersistStreamInit.GetIID(), pPersistStreamInit.ppv() ) );
		RETURN_FAILED_HRESULT( hr = pPersistStreamInit->Load( pStreamR ) );

		WXMLElement	pRootElement;
//		RETURN_FAILED_HRESULT( hr = m_pXMLDocument->put_charset( CComBSTR("ISO-8859-1") ) );
		return S_OK;
	}
	HRESULT AddCoordinate( IXMLElement* pItemParent, const VARIANT& vName, double c ) {
		WXMLElement	pCoordValue;
		TCHAR	_buf[64];
		sprintf(_buf,_T("%.5lf"), c );
		CComBSTR	strCoordinate(_buf);
		RETURN_FAILED_HRESULT( pItemParent->setAttribute( V_BSTR(&vName), CComVariant(strCoordinate) ) );
		return S_OK;
	}
	CComVariant	m_strInvalidObjectsTag;
	CComVariant	m_strProjectTag;		// Project
	CComVariant	m_strHeaderTag;			// +-- Header
	CComVariant	m_strEntriesTag;		// |   +-- Entries
	CComVariant	m_strEntryTag;			// |       +-- Entry
	CComVariant	m_strViewsTag;			// +-- Views
	CComVariant	m_strViewTag;			// |   +-- View
	CComVariant	m_strVisinfosTag;		// |       +-- Visinfos
	CComVariant	m_strVisinfoTag;		// |           +-- Visinfo
	CComVariant	m_strDatasourcesTag;	// +-- Datasources
	CComVariant	m_strDatasourceTag;		//     +-- Datasource
	CComVariant	m_strClassesTag;		//         +-- Classes
	CComVariant	m_strClassTag;			//             +-- Class
	CComVariant	m_strObjectsTag;		//                 +-- Objects
	CComVariant	m_strObjectTag;			//                     +-- Object
	CComVariant	m_strFeaturesTag;		//                         +-- Features
	CComVariant	m_strFeatureTag;		//                         |   +-- Feature
	CComVariant	m_strGeometrysTag;		//                         +-- Geometrys
	CComVariant	m_strGeometryTag;		//                             +-- Geometry
	CComVariant	m_strCoordinateTag;		//                                 +-- Coordinate
	CComVariant	m_strContourTag;		//                                     +-- Contour
#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
	CComVariant	m_strCoordinatesTag;	//                                 +-- Coordinates
#endif // !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)

	CComVariant	m_strPointType;
	CComVariant	m_strLineType;
	CComVariant	m_strAreaType;
	CComVariant	m_strTextType;

	CComVariant	m_strPathProp;
	CComVariant	m_strPrimaryProp;
	CComVariant	m_strIdentProp;
	CComVariant	m_strNumberProp;
	CComVariant	m_strTypeProp;
	CComVariant	m_strGUIDProp;
	CComVariant	m_strCountProp;
	CComVariant	m_strCoordinateXProp;
	CComVariant	m_strCoordinateYProp;
	CComVariant	m_strCoordinateZProp;

	CComVariant	m_strCurrentViewProp;

	HRESULT InitStrings() {
		m_strInvalidObjectsTag = CComVariant(L"InvalidObjects");
		m_strProjectTag = CComVariant(L"project");
		m_strHeaderTag = CComVariant(L"header");
		m_strEntriesTag = CComVariant(L"entries");
		m_strEntryTag = CComVariant(L"entry");
		m_strViewsTag = CComVariant(L"views");
		m_strViewTag = CComVariant(L"view");
		m_strVisinfosTag = CComVariant(L"visinfos");
		m_strVisinfoTag = CComVariant(L"visinfo");
		m_strDatasourcesTag = CComVariant(L"datasources");
		m_strDatasourceTag = CComVariant(L"datasource");
		m_strClassesTag = CComVariant(L"classes");
		m_strClassTag = CComVariant(L"class");
		m_strObjectsTag = CComVariant(L"objects");
		m_strObjectTag = CComVariant(L"object");
		m_strFeaturesTag = CComVariant(L"features");
		m_strFeatureTag = CComVariant(L"feature");
		m_strGeometrysTag = CComVariant(L"geometrys");
		m_strGeometryTag = CComVariant(L"geometry");
		m_strCoordinateTag = CComVariant(L"coordinate");
		m_strContourTag = CComVariant(L"contour");
#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
		m_strCoordinatesTag = CComVariant(L"coordinates");
#endif !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)

		m_strPointType = CComVariant(L"Point");
		m_strLineType = CComVariant(L"Line");
		m_strAreaType = CComVariant(L"Area");
		m_strTextType = CComVariant(L"Text");

		m_strPathProp = L"path";
		m_strPrimaryProp = CComVariant(L"primary");
		m_strIdentProp = CComVariant(L"ident");
		m_strNumberProp = CComVariant(L"number");
		m_strTypeProp = CComVariant(L"type");
		m_strCountProp = CComVariant(L"count");
		m_strGUIDProp = CComVariant(L"guid");
		m_strCoordinateXProp = CComVariant(L"X");
		m_strCoordinateYProp = CComVariant(L"Y");
		m_strCoordinateZProp = CComVariant(L"Z");

		m_strCurrentViewProp = CComVariant(L"currentview");
		return S_OK;
	}
public:
	CTRiASXMLDocument() {
		HRESULT	hr;
		THROW_FAILED_HRESULT( hr = InitStrings() );
		THROW_FAILED_HRESULT( hr = CreateRootXML() );
	}
	CTRiASXMLDocument( CTRiASXMLDocument& rSrc )
		: CXMLDocument(rSrc.m_pXMLDocument) {
		HRESULT	hr;
		THROW_FAILED_HRESULT( hr = InitStrings() );
	}
	CTRiASXMLDocument( IXMLDocument* pXMLDocument )
		: CXMLDocument( pXMLDocument )
	{
		HRESULT	hr;
		THROW_FAILED_HRESULT( hr = InitStrings() );
	}

	const CComVariant& InvalidObjectsTag() { return m_strInvalidObjectsTag; }
	const CComVariant& ProjectTag() { return m_strProjectTag; }
	const CComVariant& HeaderTag() { return m_strHeaderTag; }
	const CComVariant&	EntriesTag() { return m_strEntriesTag; }
	const CComVariant&	EntryTag() { return m_strEntryTag; }
	const CComVariant&	ViewsTag() { return m_strViewsTag; }
	const CComVariant&	ViewTag() { return m_strViewTag; }
	const CComVariant& VisinfosTag() { return m_strVisinfosTag; }
	const CComVariant& VisinfoTag() { return m_strVisinfoTag; }
	const CComVariant& DatasourcesTag() { return m_strDatasourcesTag; }
	const CComVariant& DatasourceTag() { return m_strDatasourceTag; }
	const CComVariant& ClassesTag() { return m_strClassesTag; }
	const CComVariant& ClassTag() { return m_strClassTag; }
	const CComVariant& ObjectsTag() { return m_strObjectsTag; }
	const CComVariant& ObjectTag() { return m_strObjectTag; }
	const CComVariant& FeaturesTag() { return m_strFeaturesTag; }
	const CComVariant& FeatureTag() { return m_strFeatureTag; }
	const CComVariant& GeometrysTag() { return m_strGeometrysTag; }
	const CComVariant& GeometryTag() { return m_strGeometryTag; }
	const CComVariant& CoordinateTag() { return m_strCoordinateTag; }
	const CComVariant& ContourTag() { return m_strContourTag; }
#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
	const CComVariant& CoordinatesTag() { return m_strCoordinatesTag; }
#endif !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)

	const CComVariant&	PointType() { return m_strPointType; }
	const CComVariant&	LineType() { return m_strLineType; }
	const CComVariant&	AreaType() { return m_strAreaType; }
	const CComVariant& TextType() { return m_strTextType; }

	const CComVariant& PathProp() { return m_strPathProp; }
	const CComVariant& PrimaryProp() { return m_strPrimaryProp; }
	const CComVariant& IdentProp() { return m_strIdentProp; }
	const CComVariant& NumberProp() { return m_strNumberProp; }
	const CComVariant& TypeProp() { return m_strTypeProp; }
	const CComVariant& GUIDProp() { return m_strGUIDProp; }
	const CComVariant& CountProp() { return m_strCountProp; }
	const CComVariant& CoordinateXProp() { return m_strCoordinateXProp; }
	const CComVariant& CoordinateYProp() { return m_strCoordinateYProp; }
	const CComVariant& CoordinateZProp() { return m_strCoordinateZProp; }

	const CComVariant& CurrentVievProp() { return m_strCurrentViewProp; }

	HRESULT GetItemName( IXMLElement* pElement, CComBSTR& strName ) {
		CComVariant	vName;
		RETURN_FAILED_HRESULT( pElement->getAttribute( V_BSTR(&NameProp()), &vName ) );
		RETURN_FAILED_HRESULT( vName.ChangeType(VT_BSTR) );
		strName = V_BSTR(&vName);
		return S_OK;
	}
	HRESULT GetItemType( IXMLElement* pElement, CComBSTR& strType ) {
		CComVariant	vType;
		RETURN_FAILED_HRESULT( pElement->getAttribute( V_BSTR(&TypeProp()), &vType ) );
		RETURN_FAILED_HRESULT( vType.ChangeType(VT_BSTR) );
		strType = V_BSTR(&vType);
		return S_OK;
	}
	HRESULT GetItemGUID( IXMLElement* pElement, CComBSTR& strGUID ) {
		CComVariant	vGUID;
		RETURN_FAILED_HRESULT( pElement->getAttribute( V_BSTR(&GUIDProp()), &vGUID ) );
		RETURN_FAILED_HRESULT( vGUID.ChangeType(VT_BSTR) );
		strGUID = V_BSTR(&vGUID);
		return S_OK;
	}

	HRESULT AddCoordinate( IXMLElement* pItemParent, int number, double x, double y, double z) {
		RETURN_FAILED_HRESULT( CheckItem( pItemParent, ContourTag() ) );
		WXMLElement	pCoordinate;
		CComVariant	vNumber(number);
		vNumber.ChangeType(VT_BSTR);
		RETURN_FAILED_HRESULT( AddNamedItem( pItemParent, CoordinateTag(), vNumber, pCoordinate.ppi() ) );
		RETURN_FAILED_HRESULT( AddCoordinate( pCoordinate, CoordinateXProp(), x ) );
		RETURN_FAILED_HRESULT( AddCoordinate( pCoordinate, CoordinateYProp(), y ) );
		RETURN_FAILED_HRESULT( AddCoordinate( pCoordinate, CoordinateZProp(), z ) );
		return S_OK;
	}

#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
// #HK000209: Koordinaten Konturweise schreiben
	HRESULT AddContourCoordinates (IXMLElement* pItemParent, int iCnt, double *pX, double *pY)
	{
		RETURN_FAILED_HRESULT(CheckItem (pItemParent, ContourTag()));	// parent muß eine Kontur sein

	WXMLElement	pCoords;
	CComVariant	vNumber (iCnt);

		vNumber.ChangeType(VT_BSTR);
		RETURN_FAILED_HRESULT(AddNamedItem (pItemParent, CoordinatesTag(), vNumber, pCoords.ppi()));

	// Koordinaten als eine Zeichenkette aufbereiten:
	// jede Zeile besteht aus: "(X/Y/Z),"
	LPOLESTR poleOut = NULL;
	int iCurr = 0;

		ATLTRY(poleOut = new OLECHAR[iCnt*3*32+5]);		// jede Doublezahl ist max. 32 Zeichen lang (?)
		if (NULL == poleOut) 
			return E_OUTOFMEMORY;

	// alle Koordinaten durchgehen
		for (int i = 0; i < iCnt; i++) {
			poleOut[iCurr++] = L'(';

		// X hinzufügen
		CComVariant vX (*pX++);

			RETURN_FAILED_HRESULT(vX.ChangeType (VT_BSTR));

		int iLenX = SysStringLen(V_BSTR(&vX));

			wcsncpy (&poleOut[iCurr], V_BSTR(&vX), iLenX);
			iCurr += iLenX;
			poleOut[iCurr++] = L'/';
		
		// Y hinzufügen
		CComVariant vY (*pY++);

			RETURN_FAILED_HRESULT(vY.ChangeType (VT_BSTR));

		int iLenY = SysStringLen(V_BSTR(&vY));

			wcsncpy (&poleOut[iCurr], V_BSTR(&vY), iLenY);
			iCurr += iLenY;

		// dummy Z hinzufügen
			wcscpy (&poleOut[iCurr], L"/0),");

		// aktuelle Position
			iCurr += 4;
		}
		RETURN_FAILED_HRESULT(AddText (pCoords, poleOut));
		delete poleOut;
		return S_OK;
	}
#endif // !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
};

#endif // __XMLINTERTRIAS_H__B82CDCD1_2495_11d3_9982_0060085FC1CE
