// @doc 
// @module RecordsetGenerator.cpp | Implementation of the <c COKSRecordsetGenerator>
// class

#include "stdafx.h"

#include <ErrInst.hxx>
#include <NativeIdent.h>
#include <NativeObject.h>
#include <NativePbd.h>

#include <IExtendedPS.h>
#include <XGeomUtl.h>
#include <CSKGeomTypes.h>

#include "Strings.h"
#include "TRiASGM.h"
#include "RecordsetGenerator.h"

using namespace trias_nativeident;
using namespace trias_nativeobject;
using namespace trias_nativepbd;

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
os_string CorrectName (LPCSTR pcName);
long GetGeometryType (DWORD dwTypes, BOOL *pfHasTexts = NULL);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(GRecordset, IID_GRecordset);
DefineSmartInterface2(GField, IID_GField);
DefineSmartInterfaceEx2(ExtendedPropertySet, IID_ExtendedPropertySet);

/////////////////////////////////////////////////////////////////////////////
// COKSRecordsetGenerator
HRESULT COKSRecordsetGenerator::FinalConstruct()
{
	try {
	// helperobjekte erzeugen und initialisieren
		m_Pipe = WDGMAddFieldsPipe (CLSID_AddFieldsPipe);
		THROW_FAILED_HRESULT(m_Pipe -> putref_FieldProviderCallback((IRecordsetGenerator *)this));

		m_Table = WDGMBaseTable (CLSID_BaseTable);
		THROW_FAILED_HRESULT(m_Table -> putref_BaseTableCallback((IBaseTableCallback *)this));

	// required by AddFieldsPipe
		THROW_FAILED_HRESULT(m_Pipe -> put_PipeName(CComBSTR("RecordsetGenerator")));

	} catch (_com_error &e) {
		m_Pipe.Assign(NULL);
		m_Table.Assign(NULL);

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

void COKSRecordsetGenerator::FinalRelease()
{
	m_Pipe.Assign(NULL);
	m_Table.Assign(NULL);
	m_SrcInfo.Assign(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// IRecordsetGenerator

STDMETHODIMP COKSRecordsetGenerator::GetOutputRecordset (GRecordset** ppOutputRecordset)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppOutputRecordset)
		return E_POINTER;

	try {
	WGRecordset InputRS;

		THROW_FAILED_HRESULT(m_Pipe -> get_InputRecordset (InputRS.ppi()));
		if (!InputRS) {
			THROW_FAILED_HRESULT(m_Table -> get_OutputRecordset(InputRS.ppi()));
			THROW_FAILED_HRESULT(m_Pipe -> putref_InputRecordset (InputRS));
		}

		THROW_FAILED_HRESULT(ValidateProperties());
		THROW_FAILED_HRESULT(m_Pipe -> get_OutputRecordset(ppOutputRecordset));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::SetFeatureName (BSTR bsFeatureName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrFeatName = bsFeatureName;
	if (!m_bstrFeatName)
		return E_OUTOFMEMORY;
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::SetSourceInfo (VARIANT vSourceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComVariant v;

	if (FAILED(v.ChangeType (VT_UNKNOWN, &vSourceInfo)))
		return E_INVALIDARG;

HRESULT hr = V_UNKNOWN(&v) -> QueryInterface(IID_ITRiASSourceInfo, m_SrcInfo.ppv());

	if (SUCCEEDED(hr)) {
	// CScaleHeader initialisieren
	HPROJECT hPr = NULL;

		RETURN_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));
		m_Hdr.Initialize (hPr);
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IBaseTableCallback

STDMETHODIMP COKSRecordsetGenerator::AtEOF()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("COKSRecordsetGenerator::AtEOF");
}

STDMETHODIMP COKSRecordsetGenerator::RowDeleted()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("COKSRecordsetGenerator::RowDeleted");
}

/////////////////////////////////////////////////////////////////////////////
// IFieldProviderCallback

HRESULT CALLBACK COKSRecordsetGenerator::EnumObjectsCallBack (
	LONG lONr, DWORD dwType, DWORD dwData)
{
CEnumObjectsEntryCallback *pData = reinterpret_cast<CEnumObjectsEntryCallback *>(dwData);

	if (!(pData->m_dwTypes & dwType))
		return S_OK;		// gehört hier nicht her

	try {
		pData->m_pObjs->push_back(lONr);

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT CALLBACK COKSRecordsetGenerator::EnumMCodesCallBack (
	LONG lMCode, DWORD dwData)
{
CEnumMCodesCallback *pData = reinterpret_cast<CEnumMCodesCallback *>(dwData);

	try {
	ErrInstall EI (WC_NOMERKMAL);
	CNativePbdMerkmal Merkmal (pData->m_hPrPbd, lMCode, NULL, FALSE);

		if (!Merkmal || Merkmal.isSystem()) 
			return S_OK;		// weitermachen

	os_string str (CorrectName(Merkmal.GetKurzText()));

		if (str.size() > 0) {
		// doppelte Feldbezeichner verhindern
		CMCodes::iterator it = pData->m_pMCodes->find (str);
		os_string strCorr (str);
		int i = 1;

			while (it != pData->m_pMCodes->end()) {
			char cbBuffer[32];

				str = strCorr + "_" + ltoa (i++, cbBuffer, 10);
				it = pData->m_pMCodes->find (str);
			} 

		// CField erzeugen
		WGField Field;
		CComVariant vErr(DISP_E_PARAMNOTFOUND, VT_ERROR);

			THROW_FAILED_HRESULT(pData->m_pRSG->m_Pipe->AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
			THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(str.c_str())));
			THROW_FAILED_HRESULT(Field -> put_Type (gdbText));

		// und Zuordnung zu MCode merken
			pData->m_pMCodes->insert (CMCodes::value_type(str, lMCode));
		}

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

long GetGeometryType (DWORD dwTypes, BOOL *pfHasTexts)
{
long lType = -1;		// no geometry

	if (NULL != pfHasTexts)
		*pfHasTexts = FALSE;

// Texte gesondert behandeln
	if (dwTypes & OTText) {
		if (0 != (dwTypes & ~OTText)) {	// außer Texten noch was
			if (NULL != pfHasTexts)
				*pfHasTexts = TRUE;		// Sonderfall melden
		} else
			return gdbGraphicsText;		// nur Texte
	}

// alle anderen einfach sequentiell abfragen
	if (dwTypes & OTPunkt)		// Punkte
		lType = gdbPoint;

	if (dwTypes & OTLinie) {	// Linien
		if (-1 != lType) 
			return gdbAnySpatial;
		lType = gdbLinear;
	}

	if (dwTypes & OTFlaeche) {	// Flächen
		if (-1 != lType) 
			return gdbAnySpatial;
		lType = gdbAreal;
	}
	return lType;
}

STDMETHODIMP COKSRecordsetGenerator::SetupRecordset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_SrcInfo)		// noch nicht initialisiert
		return E_UNEXPECTED;

	try {
	// Parameter dieser Objektklasse besorgen
	LONG lIdent = 0L;
	DWORD dwTypes = 0L;
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));
		THROW_FAILED_HRESULT(m_SrcInfo -> get_Ident(&lIdent));
		THROW_FAILED_HRESULT(m_SrcInfo -> get_Types(&dwTypes));

	// zuerst alle Objekte dieses Idents aufsammeln
	ErrInstall EI (WC_NOIDENT);
	CNativeIdent Ident (hPr, lIdent, dwTypes);
	CEnumObjectsEntryCallback CallBackData;

		m_Objs.erase();
		CallBackData.m_pRSG = this;
		CallBackData.m_pObjs = &m_Objs;
		CallBackData.m_dwTypes = dwTypes;
		THROW_FAILED_HRESULT(Ident.EnumObjects (EnumObjectsCallBack, reinterpret_cast<DWORD>(&CallBackData)));

		THROW_FAILED_HRESULT(m_Table -> AppendRows (m_Objs.size()));

		{
		// Objektnummer als Feld
		WGField Field;
		CComVariant vErr(DISP_E_PARAMNOTFOUND, VT_ERROR);

			THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
			THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(g_cbObjektNummer)));
			THROW_FAILED_HRESULT(Field -> put_Type (gdbLong));

		// Geometrie hinzufügen
			if (0 != dwTypes) {
			BOOL fHasTexts = FALSE;
			long lgdbType = GetGeometryType(dwTypes, &fHasTexts);

				THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
				THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(g_cbGeometry)));

				if (fHasTexts) {
				// neben Texten noch anderer Typ, also separat Texte behandeln
					THROW_FAILED_HRESULT(Field -> put_Type (gdbGraphic));
					THROW_FAILED_HRESULT(Field -> put_SubType (gdbGraphicsText));
				}

			// alle übrigen als Feld hinzufügen
				THROW_FAILED_HRESULT(Field -> put_Type ((lgdbType == gdbGraphicsText) ? gdbGraphic : gdbSpatial));
				THROW_FAILED_HRESULT(Field -> put_SubType (lgdbType));

			CComVariant vCS;

				THROW_FAILED_HRESULT(m_SrcInfo -> get_CoordSystemType(&vCS))
				THROW_FAILED_HRESULT(Field -> put_CoordSystemGUID(vCS));

				if (gdbAnySpatial == lgdbType) {
				// zusätzlich Objekttyp anbieten
					THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
					THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(g_cbObjektTyp)));
					THROW_FAILED_HRESULT(Field -> put_Type (gdbText));
				}
			}
		}

	// Indexfeld setzen
	WGRecordset RSet;
	WExtendedPropertySet PropSet;

		THROW_FAILED_HRESULT(m_Pipe -> get_OutputRecordset (RSet.ppi()));
		THROW_FAILED_HRESULT(RSet -> GetExtension (CComBSTR("ExtendedPropertySet"), (IDispatch **)PropSet.ppi()))

	// Objektnummer ist Indexfeld
	CComVariant vName (g_cbObjektNummer);
	long lDummy = 0;

		THROW_FAILED_HRESULT(PropSet -> SetValue (CComBSTR("UniqueID"), vName, &lDummy));

	// jetzt alle Merkmale enumerieren
	HPROJECT hPrPbd = NULL;
	CEnumMCodesCallback CallBackMCodes;

		THROW_FAILED_HRESULT(GetRelatedProject (hPr, &hPrPbd));

		m_MCodes.erase();
		CallBackMCodes.m_pRSG = this;
		CallBackMCodes.m_pMCodes = &m_MCodes;
		CallBackMCodes.m_hPrPbd = hPrPbd;
		THROW_FAILED_HRESULT(CNativePbdMerkmal::EnumPBDData(hPrPbd, EnumMCodesCallBack, reinterpret_cast<DWORD>(&CallBackMCodes)));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::PopulateField (GField *AddedField)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	try {
	long lCurrRow = 0L;
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(m_Table -> get_CurrentRowNumber(&lCurrRow));
		THROW_FAILED_HRESULT(AddedField -> get_Name (&bstrName));

	// Felder füllen
		ASSERT(0 <= lCurrRow && lCurrRow < (long)m_Objs.size());

	long lONr = m_Objs[lCurrRow];	// zu betrachtendes Objekt
	CComVariant vValue;
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));

		if (!wcscmp (bstrName, A2OLE(g_cbObjektNummer))) {
		// Objektnummer gesucht
			THROW_FAILED_HRESULT(AddedField -> put_Value (CComVariant(lONr)));

		} else if (!wcscmp (bstrName, A2OLE(g_cbGeometry))) {
		// Geometrie
			THROW_FAILED_HRESULT(RetrieveGeometry (hPr, lONr, &vValue));
			THROW_FAILED_HRESULT(AddedField -> put_Value (vValue));

		} else if (!wcscmp (bstrName, A2OLE(g_cbObjektTyp))) {
		// Objekttyp
			THROW_FAILED_HRESULT(RetrieveObjectTypeStr (hPr, lONr, &vValue));
			THROW_FAILED_HRESULT(AddedField -> put_Value (vValue));

		} else {
		// Merkmal
		CMCodes::iterator it = m_MCodes.find (OLE2A(bstrName));

			if (it != m_MCodes.end()) {
			// gefunden
				if (SUCCEEDED(RetrieveObjectMerkmal (hPr, lONr, (*it).second, &vValue)))
					THROW_FAILED_HRESULT(AddedField -> put_Value (vValue));
			}
		}

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::ValidatePropertySet()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::RecordsetClosed()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Objs.erase();
	m_SrcInfo.Assign(NULL);
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::RecordsetUpdateCalled()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::RecordsetLoaded (DGMAddFieldsPipe *AddFieldsPipe)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::BeginCompletePass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP COKSRecordsetGenerator::EndCompletePass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Memberfunktionen
HRESULT COKSRecordsetGenerator::ValidateProperties()
{
	ASSERT(m_bstrFeatName);
	return S_OK;
}

HRESULT CreateBlobBoundary (double *pPts, size_t lCnt, double *pVec, void **ppBlob, unsigned long *plSize)
{
	if (NULL == ppBlob || NULL == plSize)
		return E_POINTER;

	try {
		THROW_FAILED_HRESULT(GSUCreateBlobFromVertices(pPts, lCnt, pVec, CLSID_GMPolygonFactory, ppBlob, plSize, TRUE));
		*ppBlob = new char [*plSize];
		THROW_FAILED_HRESULT(GSUCreateBlobFromVertices(pPts, lCnt, pVec, CLSID_GMPolygonFactory, ppBlob, plSize, FALSE));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT COKSRecordsetGenerator::RetrieveGeometry (
	HPROJECT hPr, long lONr, VARIANT *pvValue)
{
	if (NULL == pvValue)
		return E_POINTER;

// Geometrie des Objektes liefern
CNativeObject Obj (hPr, lONr);
DWORD dwType = 0;
double vec[3] = { 0.0, 0.0, 1.0 };
SAFEARRAY *psaGeometry = NULL;

	if (!Obj)
		return E_INVALIDARG;

	try {
	CPoints pts;
	vector<double> vX, vY;

		THROW_FAILED_HRESULT(Obj.GetObjectType (&dwType));
		if (dwType & OTPunkt){
		// Punktobjekte
			THROW_FAILED_HRESULT(Obj.GetPointGeometry (g_cbGeometryField, vX, vY));
			ASSERT(vX.size() == vY.size() && 1 == vX.size());

			THROW_FAILED_HRESULT(m_Hdr.Scale (vX[0], vY[0], &pts));
			THROW_FAILED_HRESULT(GSUCreateSABlobFromVertices(&pts[0].x, 1, vec, CLSID_GMPointFactory, &psaGeometry));

		} else if (dwType & OTLinie) {
		// Linienobjekte
			THROW_FAILED_HRESULT(Obj.GetLineGeometry (g_cbGeometryField, vX, vY));
			ASSERT(vX.size() == vY.size());

			for (size_t i = 0; i < vX.size(); i++)
				THROW_FAILED_HRESULT(m_Hdr.Scale (vX[i], vY[i], &pts));
			THROW_FAILED_HRESULT(GSUCreateSABlobFromVertices(&pts[0].x, vX.size(), vec, CLSID_GMPolylineFactory, &psaGeometry));

		} else if (dwType & OTFlaeche) {
		// Flächenobjekte
		vector<unsigned long> vKnt;

			THROW_FAILED_HRESULT(Obj.GetAreaGeometry (g_cbGeometryField, vX, vY, vKnt));
			ASSERT(vX.size() == vY.size());
			ASSERT(vKnt.size() > 0);

			for (size_t i = 0; i < vX.size(); i++)
				THROW_FAILED_HRESULT(m_Hdr.Scale (vX[i], vY[i], &pts));

			if (1 == vKnt.size()) {
			// nur eine Kontur
				THROW_FAILED_HRESULT(GSUCreateSABlobFromVertices(&pts[0].x, vX.size(), vec, CLSID_GMPolygonFactory, &psaGeometry));
			
			} else {
			// Außenkontur mit Inseln
			vector<void *> vBlobs;
			vector<unsigned long> vSizes;
			size_t j = 0;

				for (size_t iKnt = 0; iKnt < vKnt.size(); iKnt++) {
				void *pBlob = NULL;
				unsigned long uiSize = 0L;

					THROW_FAILED_HRESULT(CreateBlobBoundary (&pts[j].x, vKnt[iKnt], vec, &pBlob, &uiSize));
					vBlobs.push_back (pBlob);
					vSizes.push_back (uiSize);
			
					j += vKnt[iKnt];	// nächste Kontur
				}
				ASSERT(vBlobs.size() == vKnt.size());
				ASSERT(vSizes.size() == vKnt.size());

				THROW_FAILED_HRESULT(GSUCreateSABlobBoundaryFromArray (vBlobs.begin(), vBlobs.size(), vSizes.begin(), &psaGeometry));

				for (size_t i = 0; i < vKnt.size(); i++) 
					delete vBlobs[i];	// Speicher wieder freigeben
			}

		} else if (dwType & OTText) {
		// Textobjekte
		os_string str;
		double dAngle = 0.0;

			THROW_FAILED_HRESULT(Obj.GetTextGeometryAndText (g_cbGeometryField, vX, vY, dAngle, str));
			ASSERT(vX.size() == vY.size() && 1 == vX.size());

		void *pBlob = NULL;
		unsigned long uiSize = 0;

			THROW_FAILED_HRESULT(m_Hdr.Scale (vX[0], vY[0], &pts));
//			THROW_FAILED_HRESULT(GSUCreateSABlobFromVertices(&pts[0].x, 1, vec, CLSID_GMPointFactory, &psaGeometry));
		
		unsigned char PropertiesBytes[4] = {0, 0, 0, 0};

			PropertiesBytes[3] = 0;		// Alignment
			PropertiesBytes[2] = 1;		// unformatted text

			ASSERT(sizeof(long) == sizeof(PropertiesBytes));
			THROW_FAILED_HRESULT(GSUFormatTextPointBlob(pts[0].x, pts[0].y, pts[0].z, dAngle, 0.0, 0.0, 1.0, *(long *)PropertiesBytes, str.size(), (void *)str.c_str(), &pBlob, &uiSize));
			THROW_FAILED_HRESULT(GSUBlobIntoSafeArray (pBlob, uiSize, &psaGeometry));
			CoTaskMemFree(pBlob);

		} else {
		// Komplexobjekte etc.
		CComVariant v (DISP_E_PARAMNOTFOUND, VT_ERROR);

			return v.Detach(pvValue);
		}

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	pvValue -> vt = VT_ARRAY|VT_UI1;
	pvValue -> parray = psaGeometry;
	return S_OK;
}

HRESULT COKSRecordsetGenerator::RetrieveObjectTypeStr (
	HPROJECT hPr, long lONr, VARIANT *pvValue)
{
	if (NULL == pvValue)
		return E_POINTER;

// Objekttyp als Zeichenkette liefern
DWORD dwType = 0;
CNativeObject Obj (hPr, lONr);

	if (!Obj)
		return E_INVALIDARG;
	RETURN_FAILED_HRESULT(Obj.GetObjectType (&dwType));

	if (dwType & OTPunkt) {
	CComVariant v (g_cbPunkt);

		return v.Detach (pvValue);
	}
	if (dwType & OTLinie) {
	CComVariant v (g_cbLinie);

		return v.Detach (pvValue);
	}
	if (dwType & OTFlaeche) {
	CComVariant v (g_cbFlaeche);

		return v.Detach (pvValue);
	}
	if (dwType & OTText) {
	CComVariant v (g_cbText);

		return v.Detach (pvValue);
	}
	return E_INVALIDARG;
}

HRESULT COKSRecordsetGenerator::RetrieveObjectMerkmal (
	HPROJECT hPr, long lONr, long lMCode, VARIANT *pvValue)
{
CNativeObject Obj (hPr, lONr);

	if (!Obj)
		return E_INVALIDARG;

// Merkmal einlesen
os_string str;

	RETURN_FAILED_HRESULT(Obj.GetTextMerkmal (lMCode, str));

CComVariant v(str.c_str());

	return v.Detach(pvValue);
}

