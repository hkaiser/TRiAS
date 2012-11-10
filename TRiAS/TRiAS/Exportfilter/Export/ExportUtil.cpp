#include "stdafx.h"
#include "ExportImpl.h"

#include <initguid.h>
#include <xtsnguid.h>

#include <trelguid.h>
#include <igeometr.hxx>
#include <Ristypes.hxx>
#include "ExportImpl.h"

// KK991126
#include <com/XMLHelpers.h>


#include "ExportUtil.h"
#include "ExportPropertyAction.h"
#include "ObjGeomW.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyInfo2);

//--------------------------------------------------------------------
char *ConvertFromNL (char *);
char *ConvertToNL (char *);
void ConvertKlammer(char *);
//--------------------------------------------------------------------

static LPCOLESTR	GetTypeNameFromTypeEnum (long t) {
	switch(t) {
	case OGPunkt	: return L"Point";		// 0
	case OGLinie	: return L"Line";		// 1
	case OGFlaeche	: return L"Area";		// 2
	case OGKreis	: return L"Circle";		// 3
	case OGKO		: return L"Complex";	// 4
	case OGText		: return L"Text";		// 5
	case OGUnknown	: return L"Unknown";	// 6
	case OGLabel	: return L"Label";		// 7
	default: return L"INTERNAL UNKNOWN GEOMETRY";
	}
}

bool CExportPropertyActionWorker::operator() (LONG lONr) 
{
// KK000906
	if (m_bSelect) {
		if (0 == m_lContONr)
			return false;

		if (!GetActiveObjectSelection (m_lContONr, lONr)) {
		// weiterzählen
			m_rExportPropertyAction.Tick();				// ProgressIndikator weitersetzen
			m_rExportPropertyAction.UpdateStatus (++m_nObjects);
			if (FAILED(m_rExportPropertyAction.GoOn()))
				return false;		// abbrechen (#HK000211)
			return true;
		}
	}

HRESULT	hr;
WXMLElement	pObjects;
WXMLElement	pObject;

// 'ExportObject' enthält alle "nicht-COM" TRiAS-Spezifik
	if (SUCCEEDED (hr = ExportObject (lONr, pObjects, pObject)) ) {

	// KK000107
		hr = ExportDependants (lONr);
	//	THROW_FAILED_HRESULT (hr = ExportDependants (lONr));
		if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(
	} 
	else {
		if (pObjects.IsValid()) {
			if (pObject.IsValid()) {
			///////////////////////////////////////////////////////////////////////////////
			// Irgendwas im Objekt schiefgelaufen; selbiges also entfernen, zur Diagnose
			// aber noch im XML speichern
			WXMLElement	pDatasource;

			// KK000107
				hr = m_xmd.FindSpecificParent (pObjects, m_xmd.DatasourceTag(), pDatasource.ppi());
				if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(

				pObjects->removeChild (pObject);

				hr = m_xmd.GetOrCreateContainer (pDatasource, m_xmd.InvalidObjectsTag(), m_xmd.DatasourceTag(), pObjects.ppi());
				if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(

				hr = m_xmd.GetOrCreateContainer (pDatasource, m_xmd.InvalidObjectsTag(), m_xmd.DatasourceTag(), pObjects.ppi());
				if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(

				hr = pObjects->addChild (pObject, -1, -1);
				if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(

			} else {
				_ASSERTE(0);			// Das ist jetzt wirklich schlimm
			}
		} else {
			_ASSERTE(0);				// Das ist jetzt wirklich schlimm
		}
	}

	m_rOutIter++ = lONr;				// object is added to the output collections

// weiterzählen
	m_rExportPropertyAction.Tick();				// ProgressIndikator weitersetzen
	m_rExportPropertyAction.UpdateStatus (++m_nObjects);
	if (FAILED(m_rExportPropertyAction.GoOn()))
		return false;		// abbrechen (#HK000211)

// jetzt der eigentliche Export
// KK000131
HPROJECT hDatasource = DEX_GetObjectProject (lONr);

	if (m_ActiveHPR != hDatasource) {
	// KK000822
		if (m_rExportPropertyAction.m_bSeparate) {
			m_nCounter = 0;
			if(m_ActiveHPR != NULL) 
				ReInitialize();
		}
		m_ActiveHPR = hDatasource;
	}

	hr = m_rExportPropertyAction.ObjectDataExport(m_xmd, m_nCounter);
	if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return false; }	// dumm gelaufen :-(

// KK000906
	m_rExportPropertyAction.AddCounter();

// KK000214
// Projekt-Container
WXMLElement		pProject;

	hr = m_xmd.GetRoot (pProject.ppi());
	if (0 == m_nCounter) {
	WXMLElement	pHeader;

		hr = m_xmd.FindItem (pProject, m_xmd.HeaderTag(), pHeader.ppi());

		if (FAILED(hr) || S_FALSE == hr) {
			_ASSERTE(SUCCEEDED(hr));
			return false; 
		}	// dumm gelaufen :-(

	//	Header raus
		pProject->removeChild (pHeader);

		hr = m_xmd.FindItem (pProject, m_xmd.AttributesTag(), pHeader.ppi());
		if (FAILED(hr) || S_FALSE == hr) {
			_ASSERTE(SUCCEEDED(hr));
			return false; 
		}	// dumm gelaufen :-(

	//	attributes raus
		pProject->removeChild (pHeader);
		
		hr = m_xmd.FindItem (pProject, m_xmd.ViewsTag(), pHeader.ppi());
		if (FAILED(hr) || S_FALSE == hr) {
			_ASSERTE(SUCCEEDED(hr));
			return false; 
		}	// dumm gelaufen :-(

	//	views raus
		pProject->removeChild (pHeader);
	}

	m_nCounter++;

WXMLElement	pDatasources;
WXMLElement	pDatasource;

	hr = m_xmd.FindItem (pProject, m_xmd.DatasourcesTag(), pDatasources.ppi());
	if (FAILED(hr) || S_FALSE == hr) {
		_ASSERTE(SUCCEEDED(hr));
		return false; 
	}	// dumm gelaufen :-(

	hr = m_xmd.FindItem (pDatasources, m_xmd.DatasourceTag(), pDatasource.ppi());
	if (FAILED(hr) || S_FALSE == hr) {
		_ASSERTE(SUCCEEDED(hr));
		return false; 
	}	// dumm gelaufen :-(

	//	Daten raus
	pDatasources->removeChild (pDatasource);

// KK000215
	m_hCurrentDatasource = NULL;
	m_hCurrentClass = 0;
	m_lCurrentUIMCode = 0;
	m_lCurrentGUIDMCode = 0;

	return true;		// weitermachen
}

HRESULT GetGeoDBEntry (HPROJECT hDatasource, UINT nResrcID, CComBSTR& strEntry, 
	DWORD * dwFlags) 
{
	CComBSTR	strKey;
	if (!strKey.LoadString (nResrcID)) {
		_ASSERTE (NULL);	// geforderte Resourcen sollten schon da sein
		return E_FAIL;
	}

	USES_CONVERSION;
	LPCTSTR	lpszKey = W2A(strKey);

// KK991029
	GEODBHDRENTRYEX	H;
	char	_buf[HDRENTRYTEXTLEN];
	INITSTRUCT (H, H);

	memset (H.hdrKey, ' ', HDRKEYLENGTH);
	memcpy (H.hdrKey, lpszKey, __min (strlen (lpszKey) , HDRKEYLENGTH));
	H.lphdrText = _buf;
	H.hdrTextLen = HDRENTRYTEXTLEN;
	memset (H.lphdrText, '\0', HDRENTRYTEXTLEN);

	if (EC_OKAY != DEX_ReadGeoDBHdrEntryEx (hDatasource, H)) {
		ATLTRACE (_T("EXPORT: Unknown Headerentry %s\n"), W2A(strKey));
		return E_FAIL;
	}

	*dwFlags = H.dwFlags;

	CString sText = H.lphdrText;
	sText.AnsiToOem();

	strEntry = sText;
	return S_OK;
}

static 
HRESULT GetGeoDBEntry (HPROJECT hDatasource, UINT nResrcID, double& val, DWORD *dwFlags) 
{

	CComBSTR	strValue;

	if (FAILED (GetGeoDBEntry (hDatasource, nResrcID, strValue, dwFlags))) 
		return E_FAIL;

	USES_CONVERSION;
	val = atof (W2A(strValue));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Inverse Matrix für Koordinatentransformation berechnen
// gestohlen in TRiAS02\EVALKOEF.CXX

HRESULT EvalKoeffs (double& k11, double& k12, double& k21, double& k22) {
	double DetA = k11 * k22 - k12 * k21;

	if (DetA != 0.0) {
		double temp = k11;
		k11 = k22 / DetA;
		k22 = temp / DetA;
		k12 = -(k12 / DetA);
		k21 = -(k21 / DetA);
		return EC_OKAY;
	} else {
		return E_FAIL;
	}
	return S_OK;
}

typedef struct tagHEADERENTRY {
	UINT	m_nResrcID;
	DWORD	m_dwStyle;
} HEADERENTRY;

static 
HRESULT CreateHeaderEntry (CTRiASXMLDocument& doc, WXMLElement& rpEntries, 
	const CComBSTR& strKey, const CComBSTR& strValue, DWORD dwStyle) 
{
	HRESULT	hr;
	WXMLElement	pEntry;
	RETURN_FAILED_HRESULT (hr = doc.AddContainerItem (rpEntries, doc.EntryTag(), 
		doc.EntriesTag(), CComVariant(strKey), pEntry.ppi()));
	_ASSERTE (S_OK == hr);		// muß immer neu angelegt werden
	if (S_OK != hr) 
		return E_FAIL;

	doc.AddText (pEntry, strValue);
	CComBSTR	strStyle = HEADER_SYSTEM == dwStyle ? L"sys"
		: HEADER_READONLY == dwStyle ? L"ro"
		: HEADER_SYSTEMRO == dwStyle ? L"sysro"
		: HEADER_DYNAMIC == dwStyle ? L"sysro"
		: L""
		;

	if (strStyle.Length()) {
		pEntry->setAttribute (V_BSTR(&doc.TypeProp()), CComVariant(strStyle));
	}
	return S_OK;
}

static 
HRESULT CreateHeaderEntry (CTRiASXMLDocument& doc, WXMLElement& rpEntries, 
	UINT nResrcID, const CComBSTR& strValue, DWORD dwStyle) 
{
	CComBSTR	strKey;
	if (false == strKey.LoadString (nResrcID)) {
		_ASSERTE (NULL);	// geforderte Resourcen sollten schon da sein
		return E_FAIL;
	}
	return CreateHeaderEntry (doc, rpEntries, strKey, strValue, dwStyle);
}

static 
HRESULT ExportHeaderEntry (CTRiASXMLDocument& doc, HPROJECT hDatasource, 
	WXMLElement& rpEntries, HEADERENTRY* pHE) 
{
	CComBSTR strValue (HDRENTRYTEXTLEN, (LPCOLESTR)NULL);

	USES_CONVERSION;

// KK991029
	DWORD dwFlags = 0;
	if (FAILED (GetGeoDBEntry (hDatasource, pHE->m_nResrcID, strValue , &dwFlags))) 
		return S_FALSE;

	RETURN_FAILED_HRESULT (CreateHeaderEntry (doc, rpEntries, pHE->m_nResrcID, strValue, dwFlags));
	return S_OK;
}

inline 
HRESULT AppendHeaderEntry (const CComBSTR& strPart, CComBSTR& strHeader) 
{
	if (0 != strHeader.Length()) 
		strHeader.Append(L" ");

	strHeader.Append (strPart);
	return S_OK;
}

static 
HRESULT AppendHeaderEntry (HPROJECT hDatasource, UINT nID, CComBSTR& strValue) 
{
	CComBSTR	strPart;
// KK991029
	DWORD dwFlags = 0L;

	if (FAILED (GetGeoDBEntry (hDatasource, nID, strPart, &dwFlags))) 
		return S_FALSE;

	return AppendHeaderEntry (strPart, strValue);
}

HEADERENTRY globHEADERENTRIES[] = {
	{ IDS_CTFHEADER, HEADER_SYSTEMRO },
	{ IDS_CTFMERIDIAN, HEADER_SYSTEMRO },
	{ IDS_CTFMERIDIANV, HEADER_SYSTEMRO },		// KK991029
	{ IDS_COORDTRANSGUID, HEADER_SYSTEMRO },	// KK991029
	{ IDS_COORDSCALEATORIG, HEADER_SYSTEMRO },	// KK991029
	{ IDS_CSSGUID, HEADER_SYSTEMRO },			// KK991029
	{ IDS_CTFSTREIFEN, HEADER_SYSTEMRO },
	{ IDS_CTFSCALING, HEADER_SYSTEM },
	{ IDS_CTFPRECISION, HEADER_SYSTEM },
	{ IDS_COORDFALSEX, HEADER_SYSTEMRO },
	{ IDS_COORDFALSEY, HEADER_SYSTEMRO },
	{ IDS_COORDLATITUDE, HEADER_SYSTEMRO },
	{ IDS_SHOWGKCOORDS, HEADER_SYSTEM },
	{ IDS_COORDUNITOFANGLE, HEADER_SYSTEM },
	{ IDS_MASSTAB, 0 },							//??
	{ IDS_SCROLLMODE, 0 },						//??
	{ NULL, 0 }
};

//#pragma TODO(POINTSTYLE: ist der richtig hier?)

HEADERENTRY locHEADERENTRIES[] = {
//	{ IDS_TEXTOBJMCODE, HEADER_SYSTEMRO },		//??
	{ IDS_USEOLDPOINTSTYLE, HEADER_SYSTEM },	//??
	{ IDS_USENEWPOINTSTYLE, HEADER_SYSTEM },	//??
	{ IDS_COPYRIGHT, HEADER_SYSTEM },			// KK010110
	{ IDS_ALLOWLEADINGZEROS, 0 },				//??
	{ IDS_POSTEXTATBASELINE, 0 },				//??
	{ IDS_TKINFO, 0 },
	{ IDS_TKMCODE, 0 },
	{ IDS_TKVCODE, 0 },
	{ NULL, 0 }
};

HRESULT CExportPropertyActionWorker::BuildGeoDBHeader (WXMLElement& rpEntries, 
	HPROJECT hDatasource /*= (HPROJECT) -1*/) 
{
	CComBSTR	strKey;
	CComBSTR	strValue;
	USES_CONVERSION;

	if (-1 == (LONG) hDatasource) {
		///////////////////////////////////////////////////////////////////////////////
		// globalen Header exportieren
		for (HEADERENTRY* pHE = globHEADERENTRIES; pHE->m_nResrcID; ++pHE) 
			ExportHeaderEntry (m_xmd, hDatasource, rpEntries, pHE);

	double	k11, k12, k21, k22;
	// KK991029- dwFlags
	DWORD dwFlags = 0L;
	
		if (FAILED (GetGeoDBEntry (hDatasource, IDS_KOEFF11, k11 ,&dwFlags)) 
			|| FAILED (GetGeoDBEntry (hDatasource, IDS_KOEFF12, k12,&dwFlags)) 
			|| FAILED (GetGeoDBEntry (hDatasource, IDS_KOEFF21, k21,&dwFlags)) 
			|| FAILED (GetGeoDBEntry (hDatasource, IDS_KOEFF22, k22 ,&dwFlags)) 
			|| FAILED (EvalKoeffs (k11, k12, k21, k22)) 
			)
		{
			k11 = 1; k12 = 0; k21 = 0; k22 = 1;
		}
		sprintf (m_dblBuf.m_pABuf, _T("%.2lf %.2lf %.2lf %.2lf"), k11, k12, k21, k22);
		strValue = m_dblBuf.m_pABuf;
	
	WXMLElement	pEntry;
	
		RETURN_EXPR_FALSE (true == strKey.LoadString(IDS_SCALEKEY), E_FAIL);
		CreateHeaderEntry (m_xmd, rpEntries, strKey, strValue, dwFlags);
		strValue.Empty();

	double offX, offY;

		dwFlags = 0L;

	// KK991029
		if (FAILED (GetGeoDBEntry (hDatasource, IDS_OFFSETX, offX , &dwFlags)) 
			|| FAILED (GetGeoDBEntry (hDatasource, IDS_OFFSETY, offY, &dwFlags)) 
			)
		{
			offX = offY = 0;
		}
		sprintf (m_dblBuf.m_pABuf, _T("%.2lf %.2lf"), offX, offY);
		strValue = m_dblBuf.m_pABuf;
		RETURN_EXPR_FALSE (true == strKey.LoadString(IDS_OFFSETKEY), E_FAIL);
		CreateHeaderEntry (m_xmd, rpEntries, strKey, strValue, dwFlags);
	} 
	else {
	// Datenquellenspezifischen Header exportieren
		for (HEADERENTRY* pHE = locHEADERENTRIES; pHE->m_nResrcID; ++pHE) 
			ExportHeaderEntry (m_xmd, hDatasource, rpEntries, pHE);

		_ASSERTE (NULL != hDatasource);
		long	lMCode;

		lMCode = DEX_GetUniqueIdentMCodeEx(hDatasource);
	// KK000207
		wsprintf (m_dblBuf.m_pABuf, _T("%ld"), DEX_MapHandleToMCode(lMCode));

		RETURN_EXPR_FALSE (true == strKey.LoadString (IDS_UNIQUEIDENT) , E_FAIL);

		CreateHeaderEntry (m_xmd, rpEntries, strKey, CComBSTR(m_dblBuf.m_pABuf), HEADER_SYSTEMRO);

		lMCode = DEX_GetOldUniqueIdentMCodeEx(hDatasource);
	// KK000207
		wsprintf (m_dblBuf.m_pABuf, _T("%ld"), DEX_MapHandleToMCode(lMCode));

		RETURN_EXPR_FALSE (true == strKey.LoadString (IDS_OLDUNIQUEIDENT) , E_FAIL);
		CreateHeaderEntry (m_xmd, rpEntries, strKey, CComBSTR(m_dblBuf.m_pABuf), HEADER_SYSTEMRO);
	}
	return S_OK;
}

HRESULT CExportPropertyActionWorker::ExportHeader (WXMLElement& pParent, HPROJECT hDatasource) 
{
	HRESULT	hr;
	WXMLElement	pHeader;
	WXMLElement	pHeaderEntries;
	const VARIANT& strParent = -1 == (LONG) hDatasource ? m_xmd.ProjectTag() : m_xmd.DatasourceTag();
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainerItem (pParent, m_xmd.HeaderTag(), strParent, m_xmd.NIL(), pHeader.ppi()));
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pHeader, m_xmd.EntriesTag(), m_xmd.HeaderTag(), pHeaderEntries.ppi()));
	BuildGeoDBHeader (pHeaderEntries, hDatasource);
	return S_OK;
}

HRESULT CExportPropertyActionWorker::Initialize() 
{
	HRESULT	hr;
	m_xmd.m_bCheckParents = false;
	///////////////////////////////////////////////////////////////////////////////
	// Projekt-Container
	WXMLElement		pProject;

	RETURN_FAILED_HRESULT (hr = m_xmd.GetRoot (pProject.ppi()));

	CComBSTR	strComment;
	CComBSTR	S0, S1, S2, S3, S4;

	///////////////////////////////////////////////////////////////////////////////
	// vollen Pfadnamen des Projektes als Attribut
	if (NULL != DEX_GetActiveProject(m_dblBuf.m_pABuf)) {
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttribute (pProject, m_xmd.PathProp(), CComVariant(strComment)));

	}

	///////////////////////////////////////////////////////////////////////////////
	// einige zusätzliche Angaben als Kommentar
	RETURN_EXPR_FALSE(S0.LoadString (IDR_MSG00407 + 0) , E_FAIL);	// Modulversion
	RETURN_EXPR_FALSE(S1.LoadString (IDR_MSG00407 + 1) , E_FAIL);	// Modulname
	USES_CONVERSION;
	sprintf (m_dblBuf.m_pABuf, _T("%s %s V %s"), _T("TRiAS®"), W2A(S1), W2A(S0));
	strComment = m_dblBuf.m_pABuf;
	
	RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));

	if (TRUE == DEX_GetTRiASVersion (m_dblBuf.m_pABuf)) {
		strComment = g_szTRiAS;
		strComment.Append(L" ");
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));
	}
	if (TRUE == DEX_GetTRiASCaption (m_dblBuf.m_pABuf)) {
		strComment = L"Caption ";
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));
	}


	///////////////////////////////////////////////////////////////////////////////
	// zusätzliche Informationen über das Projekt als Attribut ablegen
	WXMLElement		pAttributes;

	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateAttributes (pProject, m_xmd.ProjectTag(), pAttributes.ppi()));


	if (NULL != DEX_GetActiveSight(m_dblBuf.m_pABuf)) {
		WXMLElement	pAttribute;
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttributeItem (pAttributes, m_xmd.CurrentVievProp(), CComBSTR(m_dblBuf.m_pABuf), pAttribute.ppi()));
	}

	///////////////////////////////////////////////////////////////////////////////
	// Datenbankheader
	RETURN_FAILED_HRESULT (hr = ExportHeader (pProject));
	///////////////////////////////////////////////////////////////////////////////

	// Sichten
	WXMLElement		pViews;
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pProject, m_xmd.ViewsTag(), m_xmd.ProjectTag(), pViews.ppi()));

	///////////////////////////////////////////////////////////////////////////////
	// Standardsicht
	WXMLElement		pView;
	CComVariant	vDefaultView(L"__DefaultVisInfo__");
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainerItem (pViews, m_xmd.ViewTag(), m_xmd.ViewsTag(), vDefaultView, pView.ppi()));

	ExportVisinfo (0, pView);		// Standardvisualisierung
	///////////////////////////////////////////////////////////////////////////////
	// uns interessiert nur der Teil unterhalb der Datenquellen;
	// diesen Container also als Root

	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pProject, m_xmd.DatasourcesTag(), m_xmd.ProjectTag(), m_pDatasources.ppi()));

	m_hCurrentDatasource = NULL;
	m_hCurrentClass = 0;
	m_lCurrentUIMCode = 0;
	m_lCurrentGUIDMCode = 0;
	///////////////////////////////////////////////////////////////////////////////
	// jetzt noch was für's Aussehen
	m_rExportPropertyAction.UpdateStatus (m_nObjects);

	// KK000204
	m_ActiveHPR = NULL;	// noch keine Datenquelle
	m_bSelect = false;	// Keine Selektion
	m_lContONr = 0L;

	// KK000225 
	if (m_dwCapabilitys & EXP_IDENTDESCRIPTION)
		m_rExportPropertyAction.ExportIdentifikator();	// ObjKlassendefinition an Filter

	if (m_dwCapabilitys & (EXP_MERKMALDESCRIPTION|EXP_OBJECTPROPERTIES)) 
		m_rExportPropertyAction.ExportMerkmal(m_dwCapabilitys & EXP_OBJECTPROPERTIES);		// Merkmalsdefinition an Filter

	return S_OK;
}
//----------------------------------------------------------------------------------------
// KK000215
HRESULT CExportPropertyActionWorker::DeleteActiveSelection (long lCounter) 
{
// KK000901
//	if (m_lContONr != 0) {
//		if (DEX_DeleteObject(m_lContONr))
//			m_lContONr = 0;
//	}
	if (-1 == lCounter)
		return S_OK;		// vom Destruktor aus gerufen

	if (0 == lCounter) {
	CString strMsg, strCap;

		VERIFY(strCap.LoadString (IDS_EXPORTCAP));
		VERIFY(strMsg.LoadString (IDS_INVALIDFILE));
		::MessageBox (AfxGetMainWnd()->GetSafeHwnd(), strMsg, strCap, MB_OK | MB_ICONEXCLAMATION);
	} 
//	else {
//		CString strForm;
//		VERIFY(strForm.LoadString (IDS_CONTAINEREXPORT));
//		strMsg.Format(strForm,lCounter);
//		::MessageBox (AfxGetMainWnd()->GetSafeHwnd(), strMsg, strCap, MB_OK | MB_ICONEXCLAMATION);
//	}
	return S_OK;
}
//----------------------------------------------------------------------------------------

// KK000831
HRESULT CExportPropertyActionWorker :: SetActiveSelection (void)
{
	m_bSelect = true;
	m_rExportPropertyAction.SetCounter();

// TRUE aktuelle Selektion / FALSE Bildauschnitt
long lCont[4];
BOOL iFlag = DEX_GetActiveSelection(lCont);

// Aus Container Objekt bilden
long *pX = new long [5];
long *pY = new long [5];
 
	if (pX == NULL || pY == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return E_FAIL;
	}

// Container verarbeiten
	*pX = *(pX + 3) = *(pX + 4) = lCont[0];		// XMin
	*(pX + 1) = *(pX + 2) = lCont[1];			// XMax
	*pY = *(pY + 1) = *(pY + 4) = lCont[2];		// YMin
	*(pY + 2) = *(pY + 3) = lCont[3];			// YMax

	m_lContONr = 0L;

OBJGEOMETRIE OG;
long lIdent = 0L;
long lCnt = 5;

	INITSTRUCT(OG, OBJGEOMETRIE);
	OG.lCnt = lCnt;
	OG.iKCnt = 1;
	OG.plCnt = &lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	
	OG.iObjTyp = OT_FLAECHE;

	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGNewObject|OGAddToView|OGIgnoreIdent|OGForceGeometry;

HPROJECT hPr = DEX_GetDataSourceHandle();
BOOL iCode = DEX_ModObjGeometrieEx (hPr, OG);

	m_lContONr = OG.lONr;

	if ( iCode)
		m_rExportPropertyAction.SetScreenContObj(OG.lONr);			// BildschirmContainerObjekt merken

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);
	return iCode ? S_OK : E_FAIL;
}

// KK000824

DefineSmartInterface (TriasXtensionSite);	//WTriasXtensionSite
DefineSmartInterface (ExtendTopRel2);		//WExtendTopRel2

bool CExportPropertyActionWorker :: GetActiveObjectSelection (long ONr,long lONr) {

	if (0 == ONr || 0 == lONr)
		return false;

	WTriasXtensionSite Site;
	WExtendTopRel2 Top(CLSID_Topologie);
	UINT Lage = LINN | LKONT;

	COM_TRY {

		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite (Site.ppi()));

		THROW_FAILED_HRESULT(Site -> GetXtension (CLSID_Topologie, IID_IExtendTopRel2, Top.ppv()));

	
		{
//			HRESULT hr = Top -> TopoRelationObjObj2_ONr (ONr, lONr,&Lage);
//			if (S_OK == hr) 
//				return true;

			Relat Rel;
			HRESULT hr = Top -> TopoRelationObjObj_ONr (ONr, lONr,&Rel);
			if (FAILED(hr))
				return false;

			if (REL_INN == Rel || REL_INAUS == Rel) 
				return true;

		}

	} COM_CATCH_RETURN(false);


	return false;
}
// KK000824


//----------------------------------------------------------------------------------------
// KK000215
HRESULT CExportPropertyActionWorker::ReInitialize() 
{
HRESULT	hr;

	// KK000216 - alte Datenquelle abschließen
	RETURN_FAILED_HRESULT(hr = End (ENDMODE_EndDataSource));

	m_xmd.m_bCheckParents = false;
	///////////////////////////////////////////////////////////////////////////////
	// Projekt-Container
	WXMLElement		pProject;

	RETURN_FAILED_HRESULT (hr = m_xmd.GetRoot (pProject.ppi()));


	CComBSTR	strComment;
	CComBSTR	S0, S1, S2, S3, S4;

	///////////////////////////////////////////////////////////////////////////////
	// vollen Pfadnamen des Projektes als Attribut
	if (NULL != DEX_GetActiveProject(m_dblBuf.m_pABuf)) {
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttribute (pProject, m_xmd.PathProp(), CComVariant(strComment)));

	}

	///////////////////////////////////////////////////////////////////////////////
	// einige zusätzliche Angaben als Kommentar
	RETURN_EXPR_FALSE (true == S0.LoadString (IDR_MSG00407 + 0) , E_FAIL);	// Modulversion
	RETURN_EXPR_FALSE (true == S1.LoadString (IDR_MSG00407 + 1) , E_FAIL);	// Modulname
	USES_CONVERSION;
	sprintf (m_dblBuf.m_pABuf, _T("%s %s V %s"), _T("TRiAS®"), W2A(S1), W2A(S0));
	strComment = m_dblBuf.m_pABuf;
	
	RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));

	if (TRUE == DEX_GetTRiASVersion (m_dblBuf.m_pABuf)) {
		strComment = g_szTRiAS;
		strComment.Append(L" ");
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));
	}
	if (TRUE == DEX_GetTRiASCaption (m_dblBuf.m_pABuf)) {
		strComment = L"Caption ";
		strComment.Append(m_dblBuf.m_pABuf);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddComment (pProject, strComment));
	}


	///////////////////////////////////////////////////////////////////////////////
	// zusätzliche Informationen über das Projekt als Attribut ablegen
	WXMLElement		pAttributes;

	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateAttributes (pProject, m_xmd.ProjectTag(), pAttributes.ppi()));


	if (NULL != DEX_GetActiveSight(m_dblBuf.m_pABuf)) {
		WXMLElement	pAttribute;
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttributeItem (pAttributes, m_xmd.CurrentVievProp(), CComBSTR(m_dblBuf.m_pABuf), pAttribute.ppi()));
	}

	///////////////////////////////////////////////////////////////////////////////
	// Datenbankheader
	RETURN_FAILED_HRESULT (hr = ExportHeader (pProject));
	///////////////////////////////////////////////////////////////////////////////

	// Sichten
	WXMLElement		pViews;
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pProject, m_xmd.ViewsTag(), m_xmd.ProjectTag(), pViews.ppi()));

	///////////////////////////////////////////////////////////////////////////////
	// Standardsicht
	WXMLElement		pView;
	CComVariant	vDefaultView(L"__DefaultVisInfo__");
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainerItem (pViews, m_xmd.ViewTag(), m_xmd.ViewsTag(), vDefaultView, pView.ppi()));

	ExportVisinfo (0, pView);		// Standardvisualisierung
	///////////////////////////////////////////////////////////////////////////////
	// uns interessiert nur der Teil unterhalb der Datenquellen;
	// diesen Container also als Root

	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pProject, m_xmd.DatasourcesTag(), m_xmd.ProjectTag(), m_pDatasources.ppi()));

	if (m_dwCapabilitys & EXP_IDENTDESCRIPTION)		// ObjKlassendefinition an Filter
		m_rExportPropertyAction.ExportIdentifikator();	

	if (m_dwCapabilitys & (EXP_MERKMALDESCRIPTION|EXP_OBJECTPROPERTIES))	// Merkmalsdefinition an Filter
		m_rExportPropertyAction.ExportMerkmal(m_dwCapabilitys & EXP_OBJECTPROPERTIES);	

	return S_OK;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// KK000215
HRESULT CExportPropertyActionWorker::End (ENDMODE rgMode) 
{
	RETURN_FAILED_HRESULT(m_rExportPropertyAction.ObjectDataExport (m_xmd, -1, rgMode));
	return S_OK;
}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#define	TIsValidAddress(lp,bytes,mode)	_CrtIsValidPointer((lp),(bytes),(mode))
inline 
bool TIsValidString(LPCSTR lpsz, int nLength = -1) 
{
	if (lpsz == NULL) return false;
	return ::IsBadStringPtrA(lpsz, nLength) == 0;
}

//#include <../FrameWrk/include/tassert.hxx>
#include <visinfo.hxx>
#include <defattr.h>

inline void GetDefault (PVISINFO& VI) {
	CDefaultPVisInfo	vi;
	vi.CopyTo (VI.m_VI);
}
inline void GetDefault (LVISINFO& VI) {
	CDefaultLVisInfo	vi;
	vi.CopyTo (VI.m_VI);
}
inline void GetDefault (FVISINFO& VI) {
	CDefaultFVisInfo	vi;
	vi.CopyTo (VI.m_VI);
}
inline void GetDefault (TVISINFO& VI) {
	CDefaultTVisInfo	vi;
	vi.CopyTo (VI.m_VI);
}

template<class V>
inline void GetClassVI (long lIdent, short iVTyp, V& vi) {
	HANDLEVISINFO	HVI;
	INITSTRUCT(HVI,HVI);
	HVI.m_lIdent = lIdent;
	HVI.m_iVTyp = iVTyp;
	HVI.m_pVI = &vi.m_VI;
	BOOL bRes = DEX_GetIdentVisInfo (HVI);
	if (FALSE == bRes) {
		//GetDefault (vi);
		vi.m_VI.dwSize = 0;	// nicht mit ausgeben
	}
}

HRESULT RetrieveClassVisinfo (long lIdent, PVISINFO& PVI, LVISINFO& LVI, FVISINFO& FVI, TVISINFO& TVI) {
	GetClassVI (lIdent, VT_Punkt, PVI);
	GetClassVI (lIdent, VT_Linie, LVI);
	GetClassVI (lIdent, VT_Flaeche, FVI);
	GetClassVI (lIdent, VT_Text, TVI);
	return S_OK;
}

HRESULT RetrieveDefaultVisinfo (PVISINFO& PVI, LVISINFO& LVI, FVISINFO& FVI, TVISINFO& TVI) {
	GetDefault (PVI);
	GetDefault (LVI);
	GetDefault (FVI);
	GetDefault (TVI);
	return S_OK;
}

HRESULT RetrieveVisinfo (long lIdent, PVISINFO& PVI, LVISINFO& LVI, FVISINFO& FVI, TVISINFO& TVI) {
	return 0 == lIdent ? RetrieveDefaultVisinfo (PVI, LVI, FVI, TVI) : RetrieveClassVisinfo (lIdent, PVI, LVI, FVI, TVI);
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines short - Attributes mit einem bestimmten Namen
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttributes, const VARIANT& vAttribute, const short& val) {
	HRESULT	hr;
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pAttributes, xmd.AttributeTag(), xmd.AttributesTag(), vAttribute, pAttribute.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, xmd.ValueProp(), val));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines SIZE - Attributes mit einem bestimmten Namen
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttributes, const VARIANT& vAttribute, const SIZE& val) {
	HRESULT	hr;
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pAttributes, xmd.AttributeTag(), xmd.AttributesTag(), vAttribute, pAttribute.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"size:cx"), val.cx));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"size:cy"), val.cy));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines LPCOLESTR - Attributes mit einem bestimmten Namen
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttributes, const VARIANT& vAttribute, const BSTR& val) {
	HRESULT	hr;
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pAttributes, xmd.AttributeTag(), xmd.AttributesTag(), vAttribute, pAttribute.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, xmd.ValueProp(), val));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines LPCTSTR - Attributes mit einem bestimmten Namen
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttributes, const VARIANT& vAttribute, LPCTSTR val) {
	HRESULT	hr;
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pAttributes, xmd.AttributeTag(), xmd.AttributesTag(), vAttribute, pAttribute.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, xmd.ValueProp(), CComBSTR(val)));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Setzen der Werte eines COLORREF-Attributes
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttribute, const COLORREF& c) {
	HRESULT	hr;
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"colorspace"), CComBSTR(L"rgb")));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"color:r"), GetRValue(c)));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"color:g"), GetGValue(c)));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pAttribute, CComVariant(L"color:b"), GetBValue(c)));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines COLORREF - Attributes mit einem bestimmten Namen
inline HRESULT ExportValue (CTRiASXMLDocument& xmd, WXMLElement& pAttributes, const VARIANT& vAttribute, const COLORREF& c) {
	HRESULT	hr;
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pAttributes, xmd.AttributeTag(), xmd.AttributesTag(), vAttribute, pAttribute.ppi()));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttribute, c));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exportieren der Standard-Visinfodaten
HRESULT ExportDefaultVI (CTRiASXMLDocument& xmd, WXMLElement& pVisinfos, const VARIANT& vName, VISINFO& VI, IXMLElement** ppAttributes) {
	HRESULT hr;
	WXMLElement	pVisinfo;
//	CComVariant	vAttr;
//	RETURN_FAILED_HRESULT (hr = xmd.GetOrCreateContainerItem (pVisinfos, xmd.VisinfoTag(), xmd.VisinfosTag(), vName, pVisinfo.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddContainerItem (pVisinfos, xmd.VisinfoTag(), xmd.VisinfosTag(), vName, pVisinfo.ppi()));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pVisinfo, CComVariant(L"locatable"), VI.m_fLocatable));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pVisinfo, CComVariant(L"visible"), VI.m_fVisible));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pVisinfo, CComVariant(L"style"), VI.m_Style));
	RETURN_FAILED_HRESULT (hr = xmd.AddAttribute (pVisinfo, CComVariant(L"priority"), VI.m_Priority));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pVisinfo, VI.m_C));

	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT (hr = xmd.GetOrCreateAttributes (pVisinfo, xmd.VisinfoTag(), pAttributes.ppi()));
	*ppAttributes = pAttributes.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Punktvisinfo
HRESULT ExportVI (CTRiASXMLDocument& xmd, WXMLElement& pVisinfos, PVISINFO& PVI) {
	HRESULT	hr;
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT (hr = ExportDefaultVI (xmd, pVisinfos, CComVariant(L"point"), PVI.m_VI, pAttributes.ppi()));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"dimension"), PVI.m_Size));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"rotation"), PVI.m_iRot));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"color"), PVI.m_SecC));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Linienvisinfo
HRESULT ExportVI (CTRiASXMLDocument& xmd, WXMLElement& pVisinfos, LVISINFO& LVI) {
	HRESULT	hr;
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT (hr = ExportDefaultVI (xmd, pVisinfos, CComVariant(L"line"), LVI.m_VI, pAttributes.ppi()));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"width"), LVI.m_Width));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Flächenvisinfo
HRESULT ExportVI (CTRiASXMLDocument& xmd, WXMLElement& pVisinfos, FVISINFO& FVI) {
	HRESULT	hr;
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT (hr = ExportDefaultVI (xmd, pVisinfos, CComVariant(L"area"), FVI.m_VI, pAttributes.ppi()));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"width"), FVI.m_iWidth));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"color"), FVI.m_FC));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Textvisinfo
HRESULT ExportVI (CTRiASXMLDocument& xmd, WXMLElement& pVisinfos, TVISINFO& TVI) {
	HRESULT	hr;
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT (hr = ExportDefaultVI (xmd, pVisinfos, CComVariant(L"text"), TVI.m_VI, pAttributes.ppi()));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"type"), TVI.m_Type));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"font"), TVI.m_VI.m_VisName));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"size"), TVI.m_Size));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"rotation"), TVI.m_Rot));
	RETURN_FAILED_HRESULT (hr = ExportValue (xmd, pAttributes, CComVariant(L"orientation"), TVI.m_Orient));
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
// Visinfo an sich
HRESULT	CExportPropertyActionWorker::ExportVisinfo (long lIdent, WXMLElement& pObject) {
	HRESULT	hr;
//	LPTSTR		lpszView = NULL == lIdent ? _T("__DefaultVisInfo__") : NULL;
	PVISINFO		PVI;
	LVISINFO		LVI;
	FVISINFO		FVI;
	TVISINFO		TVI;
	RETURN_FAILED_HRESULT (hr = RetrieveVisinfo (lIdent, PVI, LVI, FVI, TVI));

	WXMLElement		pVisinfos;
	const VARIANT&	vParent = (0 == lIdent) ? m_xmd.ViewTag() : m_xmd.ClassTag();
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pObject, m_xmd.VisinfosTag(), vParent, pVisinfos.ppi()));
	if (0 != PVI.m_VI.dwSize) {
		RETURN_FAILED_HRESULT (hr = ExportVI (m_xmd, pVisinfos, PVI));
	}
	if (0 != LVI.m_VI.dwSize) {
		RETURN_FAILED_HRESULT (hr = ExportVI (m_xmd, pVisinfos, LVI));
	}
	if (0 != FVI.m_VI.dwSize) {
		RETURN_FAILED_HRESULT (hr = ExportVI (m_xmd, pVisinfos, FVI));
	}
	if (0 != TVI.m_VI.dwSize) {
		RETURN_FAILED_HRESULT (hr = ExportVI (m_xmd, pVisinfos, TVI));
	}
	return S_OK;
}

HRESULT CExportPropertyActionWorker::FindOrCreateDatasource (HPROJECT hDatasource, IXMLElement** ppDatasource) {
	HRESULT	hr;
	DEX_GetDataSourceShortName (hDatasource, m_DEXBUF);
	CComVariant	vDatasource (m_DEXBUF);
	DEX_GetDataSourceName (hDatasource, m_DEXBUF);
	CComBSTR	strDatasourcePath (m_DEXBUF);
	WXMLElement	pDatasource;
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainerItem (m_pDatasources, m_xmd.DatasourceTag(), m_xmd.DatasourcesTag(), vDatasource, pDatasource.ppi()));
	if (S_OK == hr) {		// Datenquelle wurde neu angelegt
		ExportHeader (pDatasource, hDatasource);
		WXMLElement	pAttributes;
		sprintf (m_DEXBUF, _T("0x%08lx"), hDatasource);
		RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateAttributes (pDatasource, m_xmd.DatasourceTag(), pAttributes.ppi()));
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttribute (pDatasource, m_xmd.IdentProp(), CComVariant (CComBSTR(m_DEXBUF))) );
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttribute (pDatasource, m_xmd.PathProp(), CComVariant (strDatasourcePath)) );
	}
	*ppDatasource = pDatasource.Detach();
	return S_OK;
}

HRESULT CExportPropertyActionWorker::FindOrCreateObjects (ULONG hClass, IXMLElement** ppObjects) {
	_ASSERTE (NULL != m_hCurrentDatasource);
	HRESULT	hr;
	ClassFromIdentX (m_hCurrentDatasource, hClass, m_DEXBUF, sizeof(m_DEXBUF));	// zugehöriger Klassenname
	CComVariant	vOKS(m_DEXBUF);
	WXMLElement	pClasses;
	WXMLElement	pClass;
	RETURN_EXPR_FALSE (m_pCurrentDatasource.IsValid(), E_FAIL);
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (m_pCurrentDatasource, m_xmd.ClassesTag(), m_xmd.DatasourceTag(), pClasses.ppi()));
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainerItem (pClasses, m_xmd.ClassTag(), m_xmd.ClassesTag(), vOKS, pClass.ppi()));
	if (S_OK == hr) {		// Objektklasse wurde neu angelegt
		WXMLElement	pAttributes;
		WXMLElement	pAttribute;
		sprintf (m_DEXBUF, _T("0x%08lx"), hClass);
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttribute (pClass, CComVariant(L"ident"), CComVariant (CComBSTR(m_DEXBUF))) );
		RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateAttributes (pClass, m_xmd.ClassTag(), pAttributes.ppi()));
		char	_buf1[_MAX_PATH];
		char	_buf2[_MAX_PATH];
// KK000127
		_buf1[0] = '\0';
		_buf2[0] = '\0';

		PBDMERKMAL	M;
		INITSTRUCT (M, M);

		M.pbdTyp  = 'i';
		M.pbdCode  = hClass;
		M.pbdReserved = FALSE;
		M.pbdKText  = _buf1;
		M.pbdLText  = _buf2;
		M.pbdKTextLen = sizeof(_buf1);
		M.pbdLTextLen = sizeof(_buf2);
		M.ipbdMTyp  = 'A';
		M.ipbdMLen  = 256;
		DEX_GetPBDDataEx (m_hCurrentDatasource, M);
// KK991028
// NL in Text (_buf1,_buf2) korrigieren
		char *pBuf = ConvertFromNL(&_buf2[0]);
		if (pBuf) {
			strncpy (_buf2,pBuf,sizeof(_buf2));
			DELETE_OBJ(pBuf);
		}

		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttributeItem (pAttributes, CComVariant(L"short"), CComBSTR(_buf1), pAttribute.ppi()));
		RETURN_FAILED_HRESULT (hr = m_xmd.AddAttributeItem (pAttributes, CComVariant(L"long"), CComBSTR(_buf2), pAttribute.ppi()));
		RETURN_FAILED_HRESULT (hr = ExportVisinfo (hClass, pClass));
	}
	WXMLElement	pObjects;
	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pClass, m_xmd.ObjectsTag(), m_xmd.ClassTag(), pObjects.ppi()));
	*ppObjects = pObjects.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objektcontainer der Objektklasse zu der ein Objekt gehört auffinden

HRESULT CExportPropertyActionWorker::GetXMLObjects (long lONr, IXMLElement** ppObjects) {
	WXMLElement	pObjects = m_pCurrentObjects;
	///////////////////////////////////////////////////////////////////////////////
	// Objektklasse für dieses Objekt
	ULONG		hClass = DEX_GetObjIdent (lONr);
	if (hClass != m_hCurrentClass) {
		///////////////////////////////////////////////////////////////////////////////
		// Datenquelle für dieses Objekt
		HPROJECT	hDatasource = DEX_GetObjectProject (lONr);
		if (hDatasource != m_hCurrentDatasource) {
			RETURN_FAILED_HRESULT (FindOrCreateDatasource (hDatasource, m_pCurrentDatasource.ppi()));
			m_hCurrentDatasource = hDatasource;
			m_lCurrentUIMCode = DEX_GetUniqueIdentMCodeEx (hDatasource);
		}
		RETURN_FAILED_HRESULT (FindOrCreateObjects (hClass, pObjects.ppi()));
		m_lCurrentGUIDMCode = DEX_GetObjGuidMCode (hClass);
		m_pCurrentObjects = pObjects;
		m_hCurrentClass = hClass;
	}
	RETURN_EXPR_FALSE (pObjects.IsValid(), E_FAIL);
	*ppObjects = pObjects.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Entry für ein bestimmtes Objekt in einer Klasse
HRESULT CExportPropertyActionWorker::GetXMLObjectEntry (long lONr, IXMLElement* pObjects, IXMLElement** ppObject) {
	HRESULT		hr;
	CComVariant	vObject(lONr);
	vObject.ChangeType(VT_UI4);
	vObject.ChangeType(VT_BSTR);
	WXMLElement	pObject;
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainerItem (pObjects, m_xmd.ObjectTag(), m_xmd.ObjectsTag(), vObject, pObject.ppi()));
	if (S_OK == hr) {
		pObject->setAttribute (V_BSTR(&m_xmd.NumberProp()), vObject);
	}
	*ppObject = pObject.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// die eigentlichen Exporteure
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ein einzelnes Objekt exportieren

HRESULT CExportPropertyActionWorker::ExportObject (long lONr, WXMLElement& pObjects, WXMLElement& pObject) {
	HRESULT	hr;
	WXMLElement	pFeatures;

	RETURN_FAILED_HRESULT (GetXMLObjects (lONr, pObjects.ppi()));
	_ASSERTE (pObjects.IsValid());			// muß jetzt bekannt sein...
	RETURN_FAILED_HRESULT (GetXMLObjectEntry (lONr, pObjects, pObject.ppi()));
	_ASSERTE (pObject.IsValid());			// muß jetzt bekannt sein...
//	RETURN_FAILED_HRESULT (hr = m_xmd.GetOrCreateContainer (pObject, m_xmd.FeaturesTag(), m_xmd.ObjectTag(), pFeatures.ppi()));
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainer (pObject, m_xmd.FeaturesTag(), m_xmd.ObjectTag(), pFeatures.ppi()));
	_ASSERTE (pFeatures.IsValid());		// muß jetzt bekannt sein...

	ELKDATAHOLDER	ELKDH(&m_dblBuf);
	ELKDH.m_lONr = lONr;
	ELKDH.m_xmd = &m_xmd;
	ELKDH.m_pFeatures = pFeatures;
	ELKDH.m_pObject = pObject;

	RETURN_FAILED_HRESULT (ExportBaseFeatures (pObject, ELKDH));
	RETURN_FAILED_HRESULT (ExportExtendedFeatures (pObject, ELKDH));
	RETURN_FAILED_HRESULT (ExportCoordinates (pObject, lONr));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// die Abhängigen eines Objektes exportieren
HRESULT CExportPropertyActionWorker::ExportDependants (long lONr) {
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// grundlegende Eigenschaften ermitteln
HRESULT CExportPropertyActionWorker::ExportBaseFeatures (WXMLElement& pObject, ELKDATAHOLDER& ELKDH) {
	HRESULT	hr;
	ULONG	lIdent = DEX_GetObjIdent (ELKDH.m_lONr);
	ELKDH.m_lObjnameMCode = DEX_GetObjNameMCode(lIdent);
	ELKDH.m_lUniqueIdentMCode = m_lCurrentUIMCode;
// KK000313
//	ELKDH.m_lGUIDMCode = m_lCurrentGUIDMCode;
	ELKDH.m_lGUIDMCode = DEX_GetObjGuidMCode (lIdent);

	OBJECTGUID OGUID;
	INITSTRUCT(OGUID, OGUID);
	OGUID.lONr = ELKDH.m_lONr;

	if (SUCCEEDED(DEX_GetObjectGuid(OGUID))) {
		CComBSTR	strGUID(OGUID.guid);

// KK000127 -Notvariante : falls kein GUID - GUID loeschen
//	{00000000-0000-0000-0000-000000000000}
		USES_CONVERSION;
		LPCTSTR	lpszGUID = W2A(strGUID);

		if (strcmp(lpszGUID ,"{00000000-0000-0000-0000-000000000000}") != 0) //Not !!!
		RETURN_FAILED_HRESULT (hr = pObject->setAttribute (V_BSTR(&m_xmd.GUIDProp()), CComVariant(strGUID)));
	}
	///////////////////////////////////////////////////////////////////////////////
	// Objekttyp ermitteln
	OBJSTATISTIK	OS;
	INITSTRUCT(OS,OS);
	OS.lONr = ELKDH.m_lONr;
	DEX_GetObjStatistik (OS);
	///////////////////////////////////////////////////////////////////////////////
	// Texte an Textobjekten als besonderes Feature
	if (OGText == OS.iObjTyp) {
		GETTEXTDATA GTD;
		INITSTRUCT(GTD,GTD);
		char _buf[_MAX_PATH];
	// KK000127
		_buf[0] = '\0';

		GTD.m_lONr = ELKDH.m_lONr;
		GTD.m_pText = _buf;
		GTD.m_iLen = sizeof(_buf) - 1;
		DEX_GetTextObjectText(GTD);

// KK991028
		if (_buf[0] == '\0')
			strcat (_buf,"?");
// NL in Text (_buf) korrigieren
		char *pBuf = ConvertFromNL(&_buf[0]);
		if (pBuf) {
//			ConvertKlammer(pBuf);
			strncpy (_buf,pBuf,sizeof(_buf));
			DELETE_OBJ(pBuf);
		}

		WXMLElement	pFeature;
		hr = m_xmd.GetOrCreateContainerItem (ELKDH.m_pFeatures, m_xmd.FeatureTag(), m_xmd.FeaturesTag(), CComVariant(L"-1"), pFeature.ppi());
		m_xmd.AddText (pFeature, CComBSTR(_buf));
	}
	CComBSTR	strType (GetTypeNameFromTypeEnum (OS.iObjTyp));
	RETURN_FAILED_HRESULT (hr = pObject->setAttribute (V_BSTR(&m_xmd.TypeProp()), CComVariant(strType)));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objekteigenschaften

BOOL FAR PASCAL OnEnumObjektMerkmale (long lMCode, BOOL bNotLast, void* pVoid) 
{
LPELKDATAHOLDER	pELKDH = (LPELKDATAHOLDER) pVoid;

	_ASSERTE (pELKDH->m_xmd);
	_ASSERTE (pELKDH->m_pFeatures);
	_ASSERTE (pELKDH->m_pObject);

// KK000203
	if (pELKDH->m_lGUIDMCode == lMCode) 
		return TRUE;		// GUID ist bereits Attribut am Objekt

// Systemmerkmal ausklinken
PBDMERKMAL Data;
char cbBuffer[64];

	INITSTRUCT(Data, PBDMERKMAL); 
	Data.pbdTyp = 'm';       // Merkmal
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer);
	
ErrCode EC = DEX_GetPBDData (Data);

	if (EC != EC_OKAY && EC != WC_RETURN)
		return TRUE;

short locMTyp = toupper(Data.ipbdMTyp & ~(PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY));
TARGETMERKMAL TM;

	if ('A' != locMTyp && 'I' != locMTyp && 'F' != locMTyp) {
		_ASSERTE('A' == locMTyp || 'I' == locMTyp || 'F' != locMTyp);
		return TRUE;	// unbekannter Datentyp
	}
	if (Data.ipbdMTyp & PBDMERKMAL_SYSTEMFLAG)
		return TRUE;	// keine systeminternen Attribute exportieren

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = pELKDH->m_lONr;
	TM.lMCode = lMCode;
	TM.iTTyp = TT_Objekt;		//nur von Objekten !!!
	TM.pMText = NULL;
	TM.imaxLen = 0;

// erstmal nur fragen wieviel Textspeicher wir brauchen...
// KK001116
	if (NULL ==	DEX_GetTextMerkmal(TM)) {

// KK030320 - UniqueIdent generieren
		if (pELKDH->m_lUniqueIdentMCode != lMCode) 

			return TRUE;
	}

// KK000107
HRESULT hro = pELKDH->m_pdblBuf->Check(TM.imaxLen + 1);

	if (FAILED(hro)) { _ASSERTE(SUCCEEDED(hro)); return FALSE; }	// dumm gelaufen :-(

	sprintf (pELKDH->m_pdblBuf->m_pABuf, _T("%ld"), DEX_MapHandleToMCode(lMCode));	// String schon hier anlegen, Puffer wird gleich überschrieben

CComVariant	vMCode(pELKDH->m_pdblBuf->m_pABuf);

//	THROW_FAILED_HRESULT (pELKDH->m_pdblBuf->Check(TM.imaxLen + 1));

///////////////////////////////////////////////////////////////////////////////
// ... und jetzt aber richtig ...
	pELKDH->m_pdblBuf->m_pABuf[0] = '\0';
	TM.pMText = pELKDH->m_pdblBuf->m_pABuf;
	TM.imaxLen = pELKDH->m_pdblBuf->m_nBufLen;
// KK001116
	if (NULL ==	DEX_GetTextMerkmal(TM)) {
		if (pELKDH->m_lUniqueIdentMCode != lMCode) 

			return TRUE;
	}

// KK991028
// NL in Text (pELKDH->m_pdblBuf->m_pABuf) korrigieren
char *pBuf = ConvertFromNL(pELKDH->m_pdblBuf->m_pABuf);

	if (NULL != pBuf) {
//		ConvertKlammer(pBuf);
		strcpy (pELKDH->m_pdblBuf->m_pABuf, pBuf);
		delete pBuf;
	} else {

		wsprintf ( cbBuffer,"NoUniq_%ld",pELKDH->m_lONr);
		strcpy (pELKDH->m_pdblBuf->m_pABuf, cbBuffer);

	}

CComBSTR strValue(pELKDH->m_pdblBuf->m_pABuf);
HRESULT	hr;

	if (pELKDH->m_lObjnameMCode == lMCode) {
	// Name zusätzlich als Name ausgeben
		hr = pELKDH->m_pObject->setAttribute (V_BSTR(&pELKDH->m_xmd->NameProp()), CComVariant(strValue));
		if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return FALSE; }	// dumm gelaufen :-(
	}

WXMLElement	pFeature;

	hr = pELKDH->m_xmd->AddContainerItem (pELKDH->m_pFeatures, pELKDH->m_xmd->FeatureTag(), pELKDH->m_xmd->FeaturesTag(), vMCode, pFeature.ppi());
	if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return FALSE; }	// dumm gelaufen :-(
	if (S_OK == hr) {
		hr = pELKDH->m_xmd->AddText (pFeature, strValue);
		if (FAILED(hr)) { _ASSERTE(SUCCEEDED(hr)); return FALSE; }	// ganz schön dumm gelaufen :-((
	}
	if (pELKDH->m_lUniqueIdentMCode == lMCode) {
		hr = pELKDH->m_xmd->AddAttribute (pFeature, pELKDH->m_xmd->PrimaryProp(), (short) 1);
	}
	return TRUE;
}
//-----------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// sämtliche COM-Objekteigenschaften ausgeben
BOOL CExportPropertyActionWorker::EnumObjectProperties(ELKDATAHOLDER& ELKDH)
{

	// Objekteigenschaften durchgehen
	bool ObjFlag = false;


	COM_TRY {
	WObjectProps Props;
	WEnumObjProps IEnum;

		GetObjectProps (Props.ppi(), ELKDH.m_lONr);
		Props->EnumObjectProps(IEnum.ppi());


// KK030320 _Map Code
	CComVariant vObjNameMCode (DEX_MapHandleToMCode(ELKDH.m_lObjnameMCode), VT_I4);
	CComVariant vObjUIMCode (DEX_MapHandleToMCode(ELKDH.m_lUniqueIdentMCode), VT_I4);

//	CComVariant vObjNameMCode (ELKDH.m_lObjnameMCode, VT_I4);
//	CComVariant vObjUIMCode (ELKDH.m_lUniqueIdentMCode, VT_I4);

		THROW_FAILED_HRESULT(vObjNameMCode.ChangeType(VT_BSTR));
		THROW_FAILED_HRESULT(vObjUIMCode.ChangeType(VT_BSTR));


	WObjectProperty IProp;
	char cbPropInfo[_MAX_PATH], cbBuffer[5*_MAX_PATH];

		for (IEnum -> Reset(); S_OK == IEnum -> Next (1, IProp.ppu(), NULL); /**/)
		{
		// vollständigen Namen und Flags geben lassen
		DWORD dwFlags = 0L;
		HRESULT hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);

			if (FAILED(hr) || !m_rExportPropertyAction.MustExportFeature(cbPropInfo))
				continue;

			if (dwFlags & (PROPCAPS_INTERACTIVE|PROPCAPS_INTERACTIVE_INIT))
				continue;		// keine interaktiven Attribute exportieren

			WPropertyInfo2 PropInfo2;
			CComVariant vMCode;


			if (S_OK != IProp->Eval(ELKDH.m_lONr, cbBuffer, sizeof(cbBuffer), NULL)) {	// Buffer leer

				if (SUCCEEDED(IProp->QueryInterface(PropInfo2.ppi())) &&
					SUCCEEDED(PropInfo2->GetConfigDataEx(DEX_GetObjIdent(ELKDH.m_lONr), &vMCode)))
				{
		// KK030320 - Merkmalscode korrigieren (Map)
					long lMCode = V_I4(&vMCode);
	
					vMCode = DEX_MapHandleToMCode(lMCode);

					THROW_FAILED_HRESULT(vMCode.ChangeType(VT_BSTR));
					if (!wcscmp(V_BSTR(&vObjUIMCode), V_BSTR(&vMCode))) 
						wsprintf ( cbBuffer,"NoUniq_%ld",ELKDH.m_lONr);
					else
						continue;

				} else

					continue;		// Wert nicht belegt
			}


			ObjFlag = true;

			if (SUCCEEDED(IProp->QueryInterface(PropInfo2.ppi())) &&
				SUCCEEDED(PropInfo2->GetConfigDataEx(DEX_GetObjIdent(ELKDH.m_lONr), &vMCode)))
			{
// KK030320 - Merkmalscode korrigieren (Map)
				long lMCode = V_I4(&vMCode);

				vMCode = DEX_MapHandleToMCode(lMCode);

				THROW_FAILED_HRESULT(vMCode.ChangeType(VT_BSTR));
			} 
			else {
			// den vergebenen MCode verwenden, wenn keiner da ist
			os_string strName (cbPropInfo);
			CFeatureCodes::iterator it = m_rExportPropertyAction.GetCodes().find(strName);

				if (it != m_rExportPropertyAction.GetCodes().end()) {
				CComVariant vT ((*it).second, VT_I4);

					THROW_FAILED_HRESULT(vT.ChangeType(VT_BSTR));
					THROW_FAILED_HRESULT(vT.Detach(&vMCode));
				}
			}
			_ASSERTE(SysStringLen(V_BSTR(&vMCode)) > 0);

		// NL in Text (pELKDH->m_pdblBuf->m_pABuf) korrigieren
		char *pBuf = ConvertFromNL(cbBuffer);

			if (NULL != pBuf) {
				strcpy (cbBuffer, pBuf);
				delete pBuf;
			}

		CComBSTR strValue(cbBuffer);

			if (!wcscmp(V_BSTR(&vObjNameMCode), V_BSTR(&vMCode))) {
			// Name zusätzlich als Namen ausgeben
				THROW_FAILED_HRESULT(ELKDH.m_pObject->setAttribute (
					V_BSTR(&ELKDH.m_xmd->NameProp()), CComVariant(strValue)));
			}

		WXMLElement	pFeature;

			THROW_FAILED_HRESULT(hr = ELKDH.m_xmd->AddContainerItem (
				ELKDH.m_pFeatures, ELKDH.m_xmd->FeatureTag(), 
				ELKDH.m_xmd->FeaturesTag(), vMCode, pFeature.ppi()));

			if (S_OK == hr) {
				THROW_FAILED_HRESULT(ELKDH.m_xmd->AddText (pFeature, strValue));
			}
			if (!wcscmp(V_BSTR(&vObjUIMCode), V_BSTR(&vMCode))) {
				THROW_FAILED_HRESULT(ELKDH.m_xmd->AddAttribute (pFeature, 
					ELKDH.m_xmd->PrimaryProp(), (short)1));
			}
		}



	} COM_CATCH_RETURN(FALSE);

	// KK030320
	if (!ObjFlag) {		// Kein einziges Merkmal existiert!

		char cbBuffer[5*_MAX_PATH];
		wsprintf ( cbBuffer,"NoUniq_%ld",ELKDH.m_lONr);

		CComBSTR strValue(cbBuffer);


		WXMLElement	pFeature;
		HRESULT hr;
		CComVariant vObjUIMCode (DEX_MapHandleToMCode(ELKDH.m_lUniqueIdentMCode), VT_I4);
		THROW_FAILED_HRESULT(vObjUIMCode.ChangeType(VT_BSTR));

			THROW_FAILED_HRESULT(hr = ELKDH.m_xmd->AddContainerItem (
				ELKDH.m_pFeatures, ELKDH.m_xmd->FeatureTag(), 
				ELKDH.m_xmd->FeaturesTag(), vObjUIMCode, pFeature.ppi()));

			if (S_OK == hr) {
				THROW_FAILED_HRESULT(ELKDH.m_xmd->AddText (pFeature, strValue));
			}

			THROW_FAILED_HRESULT(ELKDH.m_xmd->AddAttribute (pFeature, 
					ELKDH.m_xmd->PrimaryProp(), (short)1));
	
	}


	return TRUE;
}

//-----------------------------------------------------------------------------------------
HRESULT CExportPropertyActionWorker::ExportExtendedFeatures (
	WXMLElement& pObject, ELKDATAHOLDER& ELKDH) 
{
	_ASSERTE(-1 != ELKDH.m_lONr);

ENUMLONGKEY ELK;
BOOL bRet = TRUE;

	ELK.eKey = ELKDH.m_lONr;
	if (m_dwCapabilitys & EXP_OBJECTPROPERTIES) {
	// alle COM-Objekteigenschaften ausgeben
		bRet = EnumObjectProperties(ELKDH);
	}
	else if (m_dwCapabilitys & EXP_STANDARDMERKMALE) {
	// lediglich Objektnamen und Unique Ident ausgeben
		bRet = OnEnumObjektMerkmale (ELKDH.m_lObjnameMCode, TRUE, &ELKDH);
		if (bRet)
			bRet = OnEnumObjektMerkmale (ELKDH.m_lUniqueIdentMCode, TRUE, &ELKDH);
	} 
	else {
	// sämtliche Objekteigenschaften ausgeben
		ELK.eFcn = (ENUMLONGKEYPROC) OnEnumObjektMerkmale;
		ELK.ePtr = (void*) &ELKDH;
		bRet = DEX_EnumObjektMerkmale(ELK);		// Enumeration der Merkmalscodes eines Objektes
	}
	return bRet ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// die Koordinaten

static inline 
HRESULT CreateContour (CTRiASXMLDocument& doc, IXMLElement* pGeometry, long nContour, 
	long nCoordinates, IXMLElement** ppContour) 
{
HRESULT	hr;
CComVariant	vAttribute;
WXMLElement	pContour;

	RETURN_FAILED_HRESULT (hr = doc.AddItem (pGeometry, doc.ContourTag(), pContour.ppi()));

///////////////////////////////////////////////////////////////////////////////
// Nummer der Kontur erstmal als Name
	vAttribute = nContour;
	vAttribute.ChangeType(VT_BSTR);
	RETURN_FAILED_HRESULT (hr = pContour->setAttribute (V_BSTR(&doc.NameProp()), vAttribute));

///////////////////////////////////////////////////////////////////////////////
// Anzahl Stützpunkte
	vAttribute = nCoordinates;
	vAttribute.ChangeType(VT_BSTR);
	RETURN_FAILED_HRESULT (hr = pContour->setAttribute (V_BSTR(&doc.CountProp()), vAttribute));
	*ppContour = pContour.Detach();
	return S_OK;
}

const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

HRESULT CExportPropertyActionWorker::ExportCoordinates (WXMLElement& pObject, long lONr) 
{
	HRESULT	hr;
	CComVariant	vGeometryName(L"Primary");
	WXMLElement	pGeometrys;
	WXMLElement	pGeometry;

	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainer (pObject, m_xmd.GeometrysTag(), m_xmd.ObjectTag(), pGeometrys.ppi()));
	RETURN_FAILED_HRESULT (hr = m_xmd.AddContainerItem (pGeometrys, m_xmd.GeometryTag(), m_xmd.GeometrysTag(), vGeometryName, pGeometry.ppi()));

///////////////////////////////////////////////////////////////////////////////
// Geometrie holen
ITRiASCS *pICS = NULL;

	if (!(m_dwCapabilitys & EXP_RAWCOORDINATES))
		pICS = m_CS;

CObjGeometrie objGeometry(pICS);

	objGeometry.SetFlags(0);
	if (!(m_dwCapabilitys & EXP_RAWCOORDINATES)) 
		objGeometry.SetFlags(OGConverted);

	RETURN_EXPR_FALSE(objGeometry.FillObjGeometrie(lONr), E_FAIL);

// Objekttyp schreiben: type=...
CComBSTR strType (GetTypeNameFromTypeEnum (objGeometry.GetObjType()));

	RETURN_FAILED_HRESULT(hr = pGeometry->setAttribute (V_BSTR(&m_xmd.TypeProp()), CComVariant(strType)));

// Anzahl der Stützpunkte: count=...
CComVariant	vAttribute(objGeometry.GetCount());

	vAttribute.ChangeType(VT_BSTR);
	RETURN_FAILED_HRESULT(hr = pGeometry->setAttribute (V_BSTR(&m_xmd.CountProp()), vAttribute));

WXMLElement	pContour;
long nContour = 0;			// Nummer der Kontur
long nContourPoints = 0;	// Anzahl der Punkte einer Kontur

	if (OGLinie == objGeometry.GetObjType() || OGText == objGeometry.GetObjType() || 
		OGPunkt == objGeometry.GetObjType() || OGLabel == objGeometry.GetObjType()) 
	{
	// Punkte, Linien, Texte
		nContourPoints = objGeometry.GetCount();
	} 
	else {
	// Flächen
		nContourPoints = objGeometry.GetContourPoints();
	}

// eigentlicher Koordinatenexport
	if (m_dwCapabilitys & EXP_RAWCOORDINATES) {
	///////////////////////////////////////////////////////////////////////////////
	// Datenbankkoordinaten kommen als long
//#pragma TODO("Falsche Annahme: EXP_RAWCOODINATES gibt einfach die Datenbankkoordinaten aus.")
// In wirklichkeit müssen die skalierten Datenbankkoordinaten ausgegeben werden (BNA!). #HK000209
		long	*pX = objGeometry.GetXAsLong();
		long	*pY = objGeometry.GetYAsLong();
		RETURN_FAILED_HRESULT (CreateContour (m_xmd, pGeometry, nContour, nContourPoints, pContour.ppi()));
		for (int nCoord = 0; nCoord != objGeometry.GetCount(); ++nCoord, --nContourPoints) {
			if (0 == nContourPoints) {
				_ASSERTE (nContour < objGeometry.GetCountourCount());
				nContourPoints = objGeometry.GetContourPoints(++nContour);
				RETURN_FAILED_HRESULT (CreateContour (m_xmd, pGeometry, nContour, nContourPoints, pContour.ppi()));
			}
			double	X, Y;
			m_ctx.UnScale (*pX, *pY, &X, &Y);
			hr = m_xmd.AddCoordinate (pContour, nCoord, X, Y, 0);
			++pX;
			++pY;
		}
		_ASSERTE (0 == nContourPoints);		// Koordinaten müssen vollständig aufgebraucht sein
	} else {
	///////////////////////////////////////////////////////////////////////////////
	// konvertierte Koordinaten kommen als double
	double *pX = objGeometry.GetXAsDouble();
	double *pY = objGeometry.GetYAsDouble();

		RETURN_FAILED_HRESULT(CreateContour (m_xmd, pGeometry, nContour, nContourPoints, pContour.ppi()));

#if defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
		for (int nCoord = 0; nCoord != objGeometry.lCnt; ++nCoord, --nContourPoints) {
			if (0 == nContourPoints) {
				_ASSERTE (nContour < objGeometry.iKCnt);
				nContourPoints = objGeometry.plCnt[++nContour];
				RETURN_FAILED_HRESULT (CreateContour (m_xmd, pGeometry, nContour, nContourPoints, pContour.ppi()));
			}
			hr = m_xmd.AddCoordinate (pContour, nCoord, *pX++, *pY++, 0);
		}
		_ASSERTE (0 == nContourPoints);		// Koordinaten müssen vollständig aufgebraucht sein
#else
	// aus Geschwindigkeitsgründen werden die Einzelnen Koordniaten Konturweise ausgegeben
	int nCoord = 0;

		while (true) {
			RETURN_FAILED_HRESULT(m_xmd.AddContourCoordinates (pContour, nContourPoints, pX, pY));

		// evtl. nächste Kontur vorbereiten
			nCoord += nContourPoints;
			if (nCoord >= objGeometry.GetCount())
				break;		// Stützpunkte alle ausgegeben

			if (OGFlaeche == objGeometry.GetObjType() && 
				++nContour >= objGeometry.GetCountourCount()) 
			{
				break;		// das war die letzte Kontur
			}

			pX += nContourPoints;
			pY += nContourPoints;
			nContourPoints = objGeometry.GetContourPoints(nContour);
			RETURN_FAILED_HRESULT(CreateContour (m_xmd, pGeometry, nContour, nContourPoints, pContour.ppi()));
		}
#endif // defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
	}
	return S_OK;
}
