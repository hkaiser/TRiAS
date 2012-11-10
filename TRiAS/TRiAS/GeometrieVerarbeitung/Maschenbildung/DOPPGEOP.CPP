// PropertyAction, welche Objekte gleicher Geometrie liefert
// File: Dppgeop.cpp

#include "pheader.h"		// vorübers. Header
#include "resource.h"		// Resource-Konstanten

//	TRIAS-Header
#include <ospace/com/iterenum.h>
#include <IGeometr.hxx>		// IObjektGeometrie
#include <triashelper.h>
#include <xtsnguid.h>
#include <objgguid.h>		//	CLSID_ObjektGeometrie, IID_IInitObjektGeometrie

//	allgem. Header
//#include <int64.h>			// LARGE

//	Projekt-Header
#include <hpp/progrsst.hpp>		// CProgressIndicator
#include <hpp/datahelp.hpp>		// Get/SetEnumLongData

#include <Com/PropertyActionBase.h>		// Basisklasse
#include <Com/PropertyActionBase.cpp>
//#include <dirisole.h>		//	CLSID_DataTransferObject

#include "tools.hpp"		// HasGeoError ()
#include "geoobjs.hpp"		// CGeometrieObject	

//	GUID-Header
#include <initguid.h>           
#include "doppguid.h"		//	zugeh. GUID

#include "doppgeop.hpp"		// zugeh. Header

//KK021217
#include <IPropSeq.hxx>


#if _MSC_VER >= 1100
#include <new>
using std::bad_alloc;
#endif // _MSC_VER >= 1100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//  externe Variablen
extern const char ExtensionName [];		// Name der Erweiterung

#define GI_DUPLICATE		0x100		// KK021217 - Doppelte Geometrie
#define GI_MULTI			0x200		//			  Mehrfache Geometrie

//////////////////////////////////////////////////////////////////////////////
// KK0212117
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);


// benötigte InterfaceWrapper
DefineSmartInterface(EnumObjectsByNumber);	
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

CDoppGeoPropAction :: CDoppGeoPropAction (void) :
	CPropertyActionImpl(PA_TYPEFLAGS, IDS_HELPDESC_DOPPGEO)
{
	m_hDex = NULL;
	m_bIsInitialized = FALSE;
	m_dTolerance = 0.0;
	m_bstrError = "";			//KK021217
		
	try {
	//	Erweiterung laden
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		if (m_hDex = DEX_ExternalLoadExtensionEx (le))
			VERIFY (m_strDesc.LoadString(IDS_HELPDESC_DOPPGEO)); 
	} 
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

CDoppGeoPropAction :: ~CDoppGeoPropAction (void)
{
}

void CDoppGeoPropAction :: FinalRelease (void)
{
	if (m_hDex) {
	//	Erweiterung entladen
	LOADEXTENSIONEX le;
	
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CDoppGeoPropAction::GetPropInfo (LPSTR pBuffer, WORD wLen, 
	DWORD *pdwFlags)
{
	COM_TRY {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && wLen > 0) {
		ULONG ulLen = min (wLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, ulLen);
			pBuffer[ulLen] = '\0';
		}

	} COM_CATCH;

//	wenn gewünscht, Flags übergeben
	if (pdwFlags) 
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;

	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::HelpInfo (LPSTR pBuffer, ULONG ulLen, 
	LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	COM_TRY {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && ulLen > 0) {
		// Beschreibung übergeben
		WORD wLen = min ((WORD) ulLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, wLen);
			pBuffer[ulLen] = '\0';
		}

	} COM_CATCH;

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CDoppGeoPropAction::AddConfigPages (LPFNADDPROPSHEETPAGE, LPARAM, LPCSTR, UINT *)
{
	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::PreConfigPages (IDataObject *, DWORD)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CDoppGeoPropAction::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_FindDoubledObjects;
	return S_OK;
}

//	IPersistStreamInit method
STDMETHODIMP CDoppGeoPropAction::InitNew (void)
{
	if (NULL == m_hDex)
		return E_FAIL;
	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_dTolerance = 0.0;
	m_bIsInitialized = TRUE;
	return S_OK;
}

// IPersistStream methods
STDMETHODIMP CDoppGeoPropAction::IsDirty (void)
{
	return S_FALSE;
}

STDMETHODIMP CDoppGeoPropAction::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyActionImpl::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

	pcbSize->QuadPart = cbSize.QuadPart + sizeof(double);
	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::Load (LPSTREAM pStm)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_dTolerance));

	m_bIsInitialized = TRUE;
	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	zuerst Bezeichner wegschreiben
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_dTolerance));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CDoppGeoPropAction::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == m_hDex)
		return E_FAIL;
	if (NULL == pcBuffer) 
		return E_INVALIDARG;

	m_strDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
// KK021217 - Nullsetzen (BIT) der Info Doppelte GI
static void 
RestoreData (long lONr, CComBSTR bstrError)
{
	if (bstrError == "")
		return;

	if (0 == lONr || -1 == lONr)
		return;

	USES_CONVERSION;

// Test, ob OE bereits definiert
HPROJECT hPr = DEX_GetObjectProject(lONr);
long m_lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr, W2A(bstrError));

	if (0 == m_lErrorCode)
		return;

int iError = GI_DUPLICATE | GI_MULTI;
char buffer[_MAX_PATH];
TARGETMERKMAL TM;

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = m_lErrorCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = buffer;
	if (!DEX_GetTextMerkmal (TM)) 
		return;

int iRefError = atoi(buffer);
int iResult = iRefError & ~iError;

	itoa(iResult, buffer, 10);

	TM.lTarget = lONr;
	TM.lMCode = m_lErrorCode;
	TM.imaxLen = strlen(buffer);
	TM.iTTyp = TT_Objekt;
	TM.pMText = buffer;
	DEX_ModTextMerkmal ( TM );
}

//////////////////////////////////////////////////////////////////////////////////////
// KK021217 - Setzen Info Doppelte GI
static void 
SetConfigData(long lONr, CComBSTR bstrError, int iError)
{
	if (bstrError == "")
		return;

	if (0 == lONr || -1 == lONr)
		return;

	USES_CONVERSION;

// Test, ob OE bereits definiert
HPROJECT hPr = DEX_GetObjectProject(lONr);
long m_lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr,W2A(bstrError));

	if (0 == m_lErrorCode)
		return;

char buffer[_MAX_PATH];
TARGETMERKMAL TM;

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = m_lErrorCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = buffer;

	if (!DEX_GetTextMerkmal(TM)) {
		itoa(iError, buffer, 10);
	} 
	else {
	int iRefError = atoi(buffer);
	int iResult = iRefError | iError;

		itoa(iResult, buffer, 10);
	}

	TM.lTarget = lONr;
	TM.lMCode = m_lErrorCode;
	TM.imaxLen = strlen(buffer);
	TM.iTTyp = TT_Objekt;
	TM.pMText = buffer;
	DEX_ModTextMerkmal(TM);
}

//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CDoppGeoPropAction::DoAction (IDataObject *pIDataObj, DWORD)
{
	COM_TRY {
	WEnumObjectsByNumber EnumObjs;
	LONG lONr = 0;

		THROW_FAILED_HRESULT(GetConfigData());			//KK021217

		THROW_FAILED_HRESULT(GetEnumLONGData (pIDataObj, EnumObjs.ppi()));
		for (EnumObjs -> Reset(); S_OK == EnumObjs -> Next (1, &lONr, NULL); /**/)
		{
		CGObject Obj (lONr, m_dTolerance);

			if (!Obj.FInit())
				continue;

		RestoreData(lONr, m_bstrError);	//KK021217

		CGeometries::const_iterator it = m_Geoms.find (Obj);

			if (it != m_Geoms.end()) {
			// nicht erstes Vorkommen dieser Geometrie
				m_DupObjs.insert (Obj);
			}
			else {
				m_Geoms.insert (Obj);
				m_DupObjs.insert (Obj);
			}
		}

	// Iterator auf Anfang stellen, damit eine Abfrage an der richtigen Stelle 
	// beginnen kann
		m_GeomIt = m_Geoms.begin();
		m_lPacket = m_Geoms.size();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj)
		return E_POINTER;
	*ppDataObj = NULL;

	COM_TRY {
	WProgressIndicator2 PI(m_pProgressIndicator);
	CProgressIndicator Indicator (PI);	

		if (m_Geoms.size() > 0 && m_GeomIt == m_Geoms.end())
			return E_UNEXPECTED;

	// gibt's überhaupt mehrfache Geometrien
	CString strCaption;

		VERIFY(strCaption.LoadString(IDS_COMPARE_GEOMETRIES));
		if (0 == m_Geoms.size() || 0 == m_DupObjs.size()) {
			m_Geoms.erase();		// alles wieder freigeben
			m_DupObjs.erase();

		// PI schalten
			Indicator.InitStatusDialog(1, strCaption);
			Indicator.SetupStatus(1);
			return S_OK;
		}

		if (m_GeomIt == m_Geoms.begin()) {
		// JG980914 Anzahl der zu bearbeitenden Elemente bestimmen
		// aber nur beim ersten Aufruf
		// hier wird die Anzahl der verschiedenen Geometrien genommen, da 
		// über alles andere keine Informationen vorliegen
		long counter = m_Geoms.size();

			Indicator.InitStatusDialog(counter, strCaption);
		}

	long lPacket = 0;
	CDupGeometries::const_iterator it = m_DupObjs.lower_bound (*m_GeomIt);
	CDupGeometries::const_iterator itend = m_DupObjs.upper_bound (*m_GeomIt);

	// alle Objekte mit dieser ObjektEigenschaft in EnumLONG kopieren
		_ASSERTE(it != m_DupObjs.end());

	// alle Objekte mit dieser Geometrie speichern
	WEnumObjectsByNumber Enum (CLSID_EnumObjectsByNumber);
	bool fFirst = true;
	
		long lObject = -1;		//KK021217
		int iError = 0;

		while (it != itend) {

			if (fFirst) {
			// zugehörigen Wert speichern
				lPacket = m_lPacket--;				// Paketnummer rückwärts zählen
				fFirst = false;
			}

			if ( -1 != lObject)	{	// KK021217

				iError = GI_DUPLICATE;
				SetConfigData (lObject,m_bstrError,iError);
			}

			Enum -> AddItem ((*it).lONr());

			lObject = (*it).lONr();
			++it;
		}

		if (0 != iError)		// KK021217
			SetConfigData (lObject,m_bstrError, iError);


	// Daten und Formate im DataObjekt speichern
	WDataObject IDO (CLSID_DataTransferObject);
	
		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (Enum, IDO));
		PropActBase::SetPacketNumber(IDO, lPacket);

	// Resultat setzen
		*ppDataObj = IDO.detach();

		++m_GeomIt;									// beim nächsten weitermachen

		Indicator.IncrementPosition();
		if (Indicator.WasCanceled())
			return E_ABORT;

	} COM_CATCH;

// S_FALSE heißt hier, 'es kommen noch mehr, bitte noch mal rufen'
	if (m_GeomIt == m_Geoms.end()) {
		_ASSERTE(0 == m_lPacket);

		m_Geoms.erase();		// alles wieder freigeben
		m_DupObjs.erase();
		return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CDoppGeoPropAction::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// FuzzyTolerance=
CComVariant vTolerance;
HRESULT hr = pBag -> Read (CComBSTR(L"FuzzyTolerance"), &vTolerance, pLog);

	m_dTolerance = 0.0;
	if (S_OK == hr && SUCCEEDED(vTolerance.ChangeType(VT_R8))) 
		m_dTolerance = V_R8(&vTolerance);

	return S_OK;
}

STDMETHODIMP CDoppGeoPropAction::GetConfigData (void)
{
	CString sECF;

	sECF.LoadString(IDS_ERRORCODEFEATURE);

	COM_TRY {
	FORMATETC c_feSABiS = 	{
			RegisterClipboardFormat (sECF),	// CLIPFORMAT cf
			NULL,							// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,				// DWORD dwAspect
			-1,								// LONG lindex	
			TYMED_ISTREAM,					// DWORD tymed
		};

	WDataObject DO;
	WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(WObjectWithSite(GetUnknown()) -> GetSite (
			IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

	// ErrorFeld
	CComVariant vData;

		THROW_FAILED_HRESULT(GetVariantData (DO, &c_feSABiS, &vData));
		if (SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrError = V_BSTR(&vData);
		}

	} COM_CATCH;
	return S_OK;
}
