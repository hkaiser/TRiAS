// @doc 
// @module RecordsetGenerator.cpp | Implementation of the <c CViewRecordsetGenerator>
// class

#include "stdafx.h"

#include "TRiASGMR.h"

#include <ErrInst.hxx>
#include <NativeView.h>
#include <NativeIdent.h>
#include <HeaderEntry.h>

#include <IExtendedPS.h>

#include "Strings.h"
#include "TRiASGM.h"
#include "ViewRecordsetGenerator.h"

using namespace trias_nativeview;
using namespace trias_nativeident;
using namespace trias_nativeheader;

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
os_string CorrectName (LPCSTR pcName);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(GRecordset, IID_GRecordset);
DefineSmartInterface2(GField, IID_GField);
DefineSmartInterfaceEx2(ExtendedPropertySet, IID_ExtendedPropertySet);
DefineSmartInterface2(DVisInfo, IID_DVisInfo);
DefineSmartInterface2(DPointVisInfo, IID_DPointVisInfo);
DefineSmartInterface2(DLineVisInfo, IID_DLineVisInfo);
DefineSmartInterface2(DAreaVisInfo, IID_DAreaVisInfo);
DefineSmartInterface2(DTextVisInfo, IID_DTextVisInfo);

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
namespace 
{
	inline int PointsFrom100mm (int iCvt)
	{
		return (int)(iCvt/31.76);
	}

	inline CComBSTR StringFromDouble(double d)
	{
	CComVariant v (d);

		VERIFY(SUCCEEDED(v.ChangeType (VT_BSTR)));
		return CComBSTR (V_BSTR(&v));
	}

	HRESULT GetTypeStr (CNativeView::VisType rgType, LPSTR pBuffer, size_t iLen)
	{
	os_string strRes;

		switch (rgType) {
		case CNativeView::VT_Punkt:
		case CNativeView::VT_PunktDef:
			strRes = g_cbPunkte;
			break;

		case CNativeView::VT_Linie:
		case CNativeView::VT_LinieDef:
			strRes = g_cbLinien;
			break;

		case CNativeView::VT_Flaeche:
		case CNativeView::VT_FlaecheDef:
			strRes = g_cbFlaechen;
			break;

		case CNativeView::VT_Text:
		case CNativeView::VT_TextDef:
			strRes = g_cbTexte;
			break;

		case CNativeView::VT_Default:
			return S_OK;		// nothing to do
		}

		strRes += ": ";
		strRes += pBuffer;
		strcpy (pBuffer, strRes.c_str());
		return S_OK;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewRecordsetGenerator
HRESULT CViewRecordsetGenerator::FinalConstruct()
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

void CViewRecordsetGenerator::FinalRelease()
{
	m_Pipe.Assign(NULL);
	m_Table.Assign(NULL);
	m_SrcInfo.Assign(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// IRecordsetGenerator

STDMETHODIMP CViewRecordsetGenerator::GetOutputRecordset (GRecordset** ppOutputRecordset)
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

STDMETHODIMP CViewRecordsetGenerator::SetFeatureName (BSTR bsFeatureName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrViewName = bsFeatureName;
	if (!m_bstrViewName)
		return E_OUTOFMEMORY;
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::SetSourceInfo (VARIANT vSourceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComVariant v;

	if (FAILED(v.ChangeType (VT_UNKNOWN, &vSourceInfo)))
		return E_INVALIDARG;

HRESULT hr = V_UNKNOWN(&v) -> QueryInterface(IID_ITRiASSourceInfo, m_SrcInfo.ppv());

	if (SUCCEEDED(hr)) {
	// IdentBase initialisieren
	HPROJECT hPr = NULL;

		RETURN_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));

	char cbBuffer[_MAX_PATH];
	CDBHeader Hdr (hPr, g_cbIdentBaseHdr);

		m_iIdBase = 16;
		if (SUCCEEDED(Hdr.GetHeaderEntry (cbBuffer, _countof(cbBuffer)))) 
			m_iIdBase = atol(cbBuffer);
		ASSERT(16 == m_iIdBase || 10 == m_iIdBase);
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IBaseTableCallback

STDMETHODIMP CViewRecordsetGenerator::AtEOF()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CViewRecordsetGenerator::AtEOF");
}

STDMETHODIMP CViewRecordsetGenerator::RowDeleted()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CViewRecordsetGenerator::RowDeleted");
}

/////////////////////////////////////////////////////////////////////////////
// IFieldProviderCallback

namespace 
{
///////////////////////////////////////////////////////////////////////////////
// Funktionen, um auf einzelne VisAttributes zuzugreifen

// vollen Visualisierungs-String liefern
	HRESULT GetVisString (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	CComVariant v;

		v.vt = VT_BSTR;
		RETURN_FAILED_HRESULT(pIVis -> get_VisString (&V_BSTR(&v)));
		return v.Detach (pvValue);
	}

// Darstellungsreihenfolge liefern
	HRESULT GetPriority (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	CComVariant v;

		v.vt = VT_I4;
		ASSERT(sizeof(int) == sizeof(long));
		RETURN_FAILED_HRESULT(pIVis -> get_Priority ((int *)&V_I4(&v)));
		return v.Detach (pvValue);
	}

// Darstellungstyp liefern
	HRESULT GetStyle (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	int iStyle = 0;

		RETURN_FAILED_HRESULT(pIVis -> get_Style (&iStyle));

	CComBSTR bstr;
	char cbBuffer[64];

		RETURN_FAILED_HRESULT(pIVis -> get_Name (&bstr));
		if (bstr.Length() > 0) 
			wsprintf (cbBuffer, "%d,\"%ls\"", iStyle, bstr);
		else
			wsprintf (cbBuffer, "%d", iStyle);

	CComVariant v (cbBuffer);

		return v.Detach (pvValue);
	}

// MainColor liefern
	HRESULT GetMainColor (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	TRIASCOLOR c;
	char cbBuffer[32];

		RETURN_FAILED_HRESULT(pIVis -> get_MainColor (&c));
		wsprintf(cbBuffer, "(%d, %d, %d)", GetRValue(c), GetGValue(c), GetBValue(c));

	CComVariant v (cbBuffer);

		return v.Detach (pvValue);
	}

// FillColor liefern
	HRESULT GetFillColor (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	TRIASCOLOR c;
	char cbBuffer[32];

		switch (rgType) {
		case CNativeView::VT_Punkt:
		case CNativeView::VT_PunktDef:
			RETURN_FAILED_HRESULT(WDPointVisInfo(pIVis) -> get_BkColor (&c));
			wsprintf(cbBuffer, "(%d, %d, %d)", GetRValue(c), GetGValue(c), GetBValue(c));
			break;

		case CNativeView::VT_Flaeche:
		case CNativeView::VT_FlaecheDef:
			RETURN_FAILED_HRESULT(WDAreaVisInfo(pIVis) -> get_BkColor (&c));
			wsprintf(cbBuffer, "(%d, %d, %d)", GetRValue(c), GetGValue(c), GetBValue(c));
			break;

		default:
			strcpy (cbBuffer, g_cbNil);
			break;
		}

	CComVariant v (cbBuffer);

		return v.Detach (pvValue);
	}

// Größe liefern
	HRESULT GetSize (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	int ix = 0;
	int iy = 0;
	char cbBuffer[32];

		switch (rgType) {
		case CNativeView::VT_Punkt:
		case CNativeView::VT_PunktDef:
			RETURN_FAILED_HRESULT(WDPointVisInfo(pIVis) -> get_SizeX (&ix));
			RETURN_FAILED_HRESULT(WDPointVisInfo(pIVis) -> get_SizeY (&iy));
			wsprintf(cbBuffer, "(%d, %d)[pt], (%ls, %ls)[mm]", PointsFrom100mm(ix), PointsFrom100mm(iy), (BSTR)StringFromDouble(ix/100.0), (BSTR)StringFromDouble(iy/100.0));
			break;

		case CNativeView::VT_Text:
		case CNativeView::VT_TextDef:
			RETURN_FAILED_HRESULT(WDTextVisInfo(pIVis) -> get_SizeX (&ix));
			RETURN_FAILED_HRESULT(WDTextVisInfo(pIVis) -> get_SizeY (&iy));
			wsprintf(cbBuffer, "(%d, %d)", ix, abs(iy));
			break;

		default:
			strcpy (cbBuffer, g_cbNil);
			break;
		}

	CComVariant v (cbBuffer);

		return v.Detach (pvValue);
	}

// Breite liefern
	HRESULT GetWidth (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue)
	{
	int iWidth = 0;
	char cbBuffer[32];
	CComVariant v(iWidth/100.0);

		v.ChangeType (VT_BSTR);
		switch (rgType) {
		case CNativeView::VT_Linie:
		case CNativeView::VT_LinieDef:
			RETURN_FAILED_HRESULT(WDLineVisInfo(pIVis) -> get_Width (&iWidth));
			wsprintf(cbBuffer, "%d [pt], %ls [mm]", PointsFrom100mm(iWidth), (BSTR)StringFromDouble(iWidth/100.0));
			break;

		case CNativeView::VT_Flaeche:
		case CNativeView::VT_FlaecheDef:
			RETURN_FAILED_HRESULT(WDAreaVisInfo(pIVis) -> get_Width (&iWidth));
			wsprintf(cbBuffer, "%d [pt], %ls [mm]", PointsFrom100mm(iWidth), (BSTR)StringFromDouble(iWidth/100.0));
			break;

		default:
			strcpy (cbBuffer, g_cbNil);
			break;
		}

	CComVariant vRes (cbBuffer);

		return vRes.Detach (pvValue);
	}

// Die folgende statische Tabelle wird zu Laufzeit in eine Map geladen 
	typedef HRESULT VISATTRFUNC (DVisInfo *pIVis, CNativeView::VisType rgType, VARIANT *pvValue);
	typedef VISATTRFUNC * VISATTRPROC;

	typedef struct tagVISFIELD {
		UINT m_uiName;
		short m_rgType;
		VISATTRPROC m_pFcn;
	} VISFIELD;

	VISFIELD g_VisFields[] = {
		{ IDS_VISTYPE, gdbText, GetStyle, },
		{ IDS_MAINCOLOR, gdbText, GetMainColor, },
		{ IDS_SECONDCOLOR, gdbText, GetFillColor, },
		{ IDS_SIZE, gdbText, GetSize, },
		{ IDS_WIDTH, gdbText, GetWidth, },
		{ IDS_VISASSTRING, gdbText, GetVisString, },
		{ IDS_PRIORITY, gdbLong, GetPriority, },
	};

// dynamische Map enthält Zuordnung von Namen zu Funktion
	typedef map<CComBSTR, VISATTRPROC, less<CComBSTR> > CVisAttrMap;
	inline bool operator< (const CComBSTR &rl, const CComBSTR &rr) throw()
	{
		return wcscmp (rl, rr) < 0 ? true : false;
	}

	class CVisAttrData
	{
	private:
		CVisAttrMap m_Data;
		bool m_fIsValid;

	public:
		CVisAttrData()
		{
			try {
			CString str;

				for (int i = 0; i < _countof(g_VisFields); i++) {
					VERIFY(str.LoadString(g_VisFields[i].m_uiName));

				CComBSTR bstr (str);

					m_Data.insert(CVisAttrMap::value_type(bstr, g_VisFields[i].m_pFcn));
				}
				m_fIsValid = true;

			} catch (...) {
				m_fIsValid = false;
			}
		}

		HRESULT GetVisAttr (DVisInfo *pIVis, BSTR bstrAttrName, CNativeView::VisType rgType, VARIANT *pvValue)
		{
			try {
			CVisAttrMap::iterator it = m_Data.find(bstrAttrName);

				if (it == m_Data.end())
					return E_UNEXPECTED;
				THROW_FAILED_HRESULT((*it).second (pIVis, rgType, pvValue));

			} catch (_com_error &e) {
				return _COM_ERROR(e);
			}
			return S_OK;
		}

		bool operator!() { return !m_fIsValid; }
	};
} // namespace

HRESULT CViewRecordsetGenerator::EnumIdentsCallBack (LONG lIdent, CNativeView::VisType rgType, DWORD dwData)
{
CEnumIdentEntryCallback *pData = reinterpret_cast<CEnumIdentEntryCallback *>(dwData);

	try {
		pData->m_pIdents->push_back(CIdentObjTyp(lIdent, rgType));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::SetupRecordset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_SrcInfo)		// noch nicht initialisiert
		return E_UNEXPECTED;

	USES_CONVERSION;
	try {
	// Parameter dieser Ansicht besorgen
	LONG lIdent = 0L;
	DWORD dwTypes = 0L;
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));

	// zuerst alle Objekte dieses Idents aufsammeln
	CNativeView View (hPr, OLE2A(m_bstrViewName));
	CEnumIdentEntryCallback CallBackData;

		m_Idents.erase();
		CallBackData.m_pRSG = this;
		CallBackData.m_pIdents = &m_Idents;
		THROW_FAILED_HRESULT(View.EnumEntries (EnumIdentsCallBack, reinterpret_cast<DWORD>(&CallBackData)));

		THROW_FAILED_HRESULT(m_Table -> AppendRows (m_Idents.size()));

	// Identifikator als Feld
	WGField Field;
	CComVariant vErr(DISP_E_PARAMNOTFOUND, VT_ERROR);

		THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
		THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(g_cbIdentifikator)));
		THROW_FAILED_HRESULT(Field -> put_Type (gdbText));

		THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
		THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(g_cbKurztext)));
		THROW_FAILED_HRESULT(Field -> put_Type (gdbText));

	// Visualisierungsinformationsfelder
	CString str;

		for (int i = 0; i < _countof(g_VisFields); i++) {
			THROW_FAILED_HRESULT(m_Pipe -> AddReadOnlyField (Field.ppi(), vErr, vErr, vErr, vErr))
			VERIFY(str.LoadString(g_VisFields[i].m_uiName));
			THROW_FAILED_HRESULT(Field -> put_Name (CComBSTR(str)));
			THROW_FAILED_HRESULT(Field -> put_Type (g_VisFields[i].m_rgType));
		}

	// Indexfeld setzen
	WGRecordset RSet;
	WExtendedPropertySet PropSet;

		THROW_FAILED_HRESULT(m_Pipe -> get_OutputRecordset (RSet.ppi()));
		THROW_FAILED_HRESULT(RSet -> GetExtension (CComBSTR("ExtendedPropertySet"), (IDispatch **)PropSet.ppi()))

	// Identifikator ist Indexfeld
	CComVariant vName (g_cbIdentifikator);
	long lDummy = 0;

//		THROW_FAILED_HRESULT(PropSet -> SetValue (CComBSTR("UniqueID"), vName, &lDummy));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::PopulateField (GField *AddedField)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	try {
	long lCurrRow = 0L;
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(m_Table -> get_CurrentRowNumber(&lCurrRow));
		THROW_FAILED_HRESULT(AddedField -> get_Name (&bstrName));

	// Felder füllen
		ASSERT(0 <= lCurrRow && lCurrRow < (long)m_Idents.size());

	CIdentObjTyp Ident (m_Idents[lCurrRow]);	// zu betrachtender Ident/ObjTyp
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(m_SrcInfo -> get_Handle(&hPr));

		if (!wcscmp (bstrName, A2OLE(g_cbIdentifikator))) {
		// Identifkator gesucht
		char cbBuffer[32];
		CComVariant vId (ultoa (Ident.GetIdent(), cbBuffer, m_iIdBase));

			THROW_FAILED_HRESULT(AddedField -> put_Value (vId));
		
		} else if (!wcscmp (bstrName, A2OLE(g_cbKurztext))) {
		// KurzText gesucht
		char cbBuffer[64];
		ErrInstall EI (WC_NOIDENT);
		CNativeIdent NatIdent (hPr, Ident.GetIdent()); 

			THROW_FAILED_HRESULT(NatIdent.GetName(cbBuffer, sizeof(cbBuffer)));
			THROW_FAILED_HRESULT(GetTypeStr (Ident.GetType(), cbBuffer, sizeof(cbBuffer)));
			THROW_FAILED_HRESULT(AddedField -> put_Value (CComVariant(cbBuffer)));

		} else {
		// alles andere ist VisInfo
		CComVariant vValue;
		WDVisInfo Vis;

			THROW_FAILED_HRESULT(RetrieveVisInfo (hPr, Ident.GetIdent(), Ident.GetType(), Vis.ppi()));
			THROW_FAILED_HRESULT(RetrieveVisInfoItem (Vis, bstrName, Ident.GetType(), &vValue));
			THROW_FAILED_HRESULT(AddedField -> put_Value (vValue));
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

STDMETHODIMP CViewRecordsetGenerator::ValidatePropertySet()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::RecordsetClosed()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Idents.erase();
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::RecordsetUpdateCalled()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::RecordsetLoaded (DGMAddFieldsPipe *AddFieldsPipe)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::BeginCompletePass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CViewRecordsetGenerator::EndCompletePass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Memberfunktionen
HRESULT CViewRecordsetGenerator::ValidateProperties()
{
	ASSERT(m_bstrViewName);
	return S_OK;
}

const CLSID *GetCLSIDFromType (CNativeView::VisType rgType)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return &CLSID_TRiASPointVisInfo;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return &CLSID_TRiASLineVisInfo;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return &CLSID_TRiASAreaVisInfo;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return &CLSID_TRiASTextVisInfo;

	default:
	case CNativeView::VT_Default:
	case CNativeView::VT_DontCare:
		break;
	}
	return &CLSID_TRiASDefaultVisInfo;
}

HRESULT CViewRecordsetGenerator::RetrieveVisInfo (
	HPROJECT hPr, long lIdent, CNativeView::VisType rgType, DVisInfo **ppIVis)
{
	ASSERT(!!m_bstrViewName);
	USES_CONVERSION;

CNativeView View (hPr, OLE2A(m_bstrViewName));

	return View.GetViewEntry (lIdent, rgType, ppIVis, GetCLSIDFromType(rgType));
}

HRESULT CViewRecordsetGenerator::RetrieveVisInfoItem (
	DVisInfo *pIVis, BSTR bstrName, CNativeView::VisType rgType, VARIANT *pvValue)
{
static CVisAttrData VisMap;		// wird on demand beim ersten Aufruf initialisert

	if (!VisMap)
		return E_UNEXPECTED;
	return VisMap.GetVisAttr (pIVis, bstrName, rgType, pvValue);
}
