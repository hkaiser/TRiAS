// Collection der geöffneten Dokumente (ProgrammierInterface) -----------------
// File: DOCSDISP.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "docarray.hxx"		
#include "enumdocs.hxx"
#include "docs.hxx"			// Collection: Documents
#include "doc.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ProgrammierInterfaceFunktionen ---------------------------------------------
// Das StandardProperty Parent liefert das übergeordnete Objekt, über welches 
// diese DocumenCollection angelegt wurde.

STDMETHODIMP CGeoDocs::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_Documents;
	return NOERROR;
}

STDMETHODIMP CGeoDocs::get_Parent (IDispatch **ppIDisp)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Objekten übergeordnete)
STDMETHODIMP CGeoDocs::get_Application (IDispatch **ppIDisp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoDocs::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoDocs::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der geöffneten Projekte ---------------------------------
STDMETHODIMP CGeoDocs::get_Count (long *plCount)
{
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;
}


// only from collection	- GetDocDisp

// Liefert eine der enthaltenen Objektklassen, entweder über einen numerischen
// Index oder über den Kurztext der gesuchten Klasse
STDMETHODIMP CGeoDocs::Item (VARIANT vt, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

VARIANTARG vArg;

	VariantInit (&vArg);
	
// versuchen, Parameter auszuwerten
HRESULT hr = VariantChangeType (&vArg, &vt, 0, VT_I4);	// Zahl als Index

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist gültig: liefern der gesuchten Doc
			return GetDocDisp (V_I4(&vArg)-1, (DDocument **)ppIDisp);

		return DISP_E_BADINDEX;
	} 

// 2. Versuch vt als String interpretieren (Name ?)
	hr = VariantChangeType (&vArg, &vt, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	string str = AnsiString(V_BSTR(&vArg));

		VariantClear (&vArg);
		return GetDocDisp (str.c_str(), (DDocument **)ppIDisp);
	}

// 3. Versuch: evtl. ist Parameter nicht gegeben
	hr = VariantChangeType (&vArg, &vt, 0, VT_ERROR);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst
		hr = ((_DDocuments *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	VariantClear (&vArg);
	return hr;
}




// Dieses StandardInterface liefert einen neuen Enumerator IEnumVARIANT mit
// allen geöffneten Projekten.
// Dieses gelieferte Interface ist allerdings von VB3.0 aus schlecht verwendbar.
//
STDMETHODIMP CGeoDocs::_NewEnum (IUnknown **ppIUnk)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumDocs *pEDocs = CEnumDocs::CreateInstance (m_pEnumDocs -> m_pDocsArray);

	if (NULL == pEDocs) return E_OUTOFMEMORY;
	
HRESULT hr = pEDocs -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);

	pEDocs -> Release();

return hr;
}

// Only to collection - GetDocDisp
STDMETHODIMP CGeoDocs::Add (VARIANT vDoc, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
VARIANTARG vArg; VariantInit (&vArg);
INITDOCSTATUS rgIOS = INITDOCSTATUS_Error;
HRESULT	hr = VariantChangeType (&vArg, &vDoc, 0, VT_BSTR);

	if (FAILED(hr)) return hr;

string strName = AnsiString(V_BSTR(&vArg));
long lIndex = m_pEnumDocs -> m_pDocsArray -> hasDoc (strName.c_str());

	VariantClear(&vArg);
	if (lIndex == -1L) {
	CGeoDocCreator DocCr (*(m_pEnumDocs -> m_pDocsArray));
	
		rgIOS = m_pICProc (m_pUnk, m_pApp, DocCr, m_dwData, &strName);
		if (rgIOS == INITDOCSTATUS_Error) 
			return E_FAIL;
	} else 
		rgIOS = INITDOCSTATUS_Exists;
	
	if (rgIOS == INITDOCSTATUS_Created || rgIOS == INITDOCSTATUS_Exists) 
		return GetDocDisp (strName.c_str(), (DDocument **)ppIDisp);
	
	return E_UNEXPECTED;
}


// Only from collection - DeleteDoc
STDMETHODIMP CGeoDocs::Remove (VARIANT vDoc)
{
CComVariant vArg;
HRESULT	hr = vArg.ChangeType (VT_BSTR, &vDoc);

	if (SUCCEEDED(hr)) {
		m_pEnumDocs -> DeleteDoc (AnsiString(V_BSTR(&vArg)));
		return NOERROR;
	}
	return hr;
}

STDMETHODIMP CGeoDocs::Refresh (void)
{
// wenn Informationen über Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate()) 
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pEnumDocs -> m_pDocsArray -> Refresh();
}


// Projekt neu erzeugen und zur Liste der geöffneten Projekte hinzufügen ------
// Parameter:	vName	ProjektName (evtl. voller Pfad, sonst im StandardVerzeichnis)
// 		vUser	[optional] neu anzulegender Nutzer
//		vPassWd	[optional] für den Nutzer zu definierendes PassWord
//		vMode	[optional] OpenMode des neu erzeugten Projektes
//				s. enum OPENMODE
STDMETHODIMP CGeoDocs::New (BSTR bstrName,
	VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	TEST_E_POINTER("CGeoDocs::New", ppIDoc);

// Initialisierung der ArgumentVariants
CComVariant vArgUser; 
CComVariant vArgPassWd;
CComVariant vArgMode; 
	
// versuchen, Parameter auszuwerten
string strName = AnsiString(bstrName);
string strUser;					// default: kein NutzerName
string strPassWd;				// default: kein PassWort
short iMode = OPENMODE_Normal;	// default: normal eröffnen

	try {
	// 2. UserName
	HRESULT hr = VariantChangeType (&vArgUser, &vUser, 0, VT_BSTR);

		if (SUCCEEDED(hr)) 
			strUser = AnsiString(V_BSTR(&vArgUser));
		else {
			hr = VariantChangeType (&vArgUser, &vUser, 0, VT_ERROR);
			if (SUCCEEDED(hr) && V_ERROR(&vArgUser) == DISP_E_PARAMNOTFOUND) {
			// Parameter ausgelassen, defaultwert verwenden (== pName)
				strUser = get_name(strName);
				strlwr (&strUser[0]);
			} else
				_com_issue_error(hr);	// mit Fehler raus
		}

	// 3. PassWort
		hr = VariantChangeType (&vArgPassWd, &vPassWd, 0, VT_BSTR);
		if (SUCCEEDED(hr)) 
			strPassWd = AnsiString(V_BSTR(&vArgPassWd));

	// 4. Mode
		hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I2);
		if (SUCCEEDED(hr)) 
			iMode = V_I2(&vArgMode);

	// DatenBasis mit gegebenen Parametern anlegen und evtl. eröffnen
	CREATEDB cDB;
	CGeoDoc *pDoc = NULL;
	
		INITSTRUCT (cDB, CREATEDB);
		cDB.m_pName = (char *)strName.c_str();
		cDB.m_pUser = (char *)strUser.c_str();
		cDB.m_pPassWd = (char *)strPassWd.c_str();
		cDB.m_iMode = iMode;
		
	// GeoDB erzeugen
	ErrCode EC = DEX_CreateNewGeoDB(cDB);	// Projekt eröffnen

		if (EC != EC_OKAY) // Fehler aufgetreten
			_com_issue_error(ErrorFromErrCode (EC));
		
	// GeoDB eröffnen
		EC = DEX_OpenProject(cDB);	// Projekt eröffnen
		if (EC != EC_OKAY) // Fehler aufgetreten
			_com_issue_error(ErrorFromErrCode (EC));
	
// Add to Collection
	INITDOCSTATUS rgIOS = INITDOCSTATUS_Error;
	long lIndex = m_pEnumDocs -> m_pDocsArray -> hasDoc (strName.c_str());
	
		if (lIndex == -1L) {
		CGeoDocCreator DocCr (*(m_pEnumDocs -> m_pDocsArray));
		
			rgIOS = m_pICProc (m_pUnk, m_pApp, DocCr, m_dwData, &strName);
			if (rgIOS == INITDOCSTATUS_Error) 
				_com_issue_error(E_FAIL);
		} else 
			rgIOS = INITDOCSTATUS_Exists;
		
		if (rgIOS == INITDOCSTATUS_Created || rgIOS == INITDOCSTATUS_Exists) {
		// get IDispatch
			hr = GetDocDisp (strName.c_str(), ppIDoc);
			if (FAILED(hr)) _com_issue_error(hr);
			
			DEX_RePaintWait();
			return NOERROR;
		}

		_com_issue_error(E_UNEXPECTED);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	
return E_UNEXPECTED;
}


// Projekt zur Liste der geöffneten Projekte hinzufügen -----------------------
// Parameter:	vName	ProjektName (evtl. voller Pfad, sonst im StandardVerzeichnis)
//		vUser	Projekt für diesen Nutzer eröffnen
//		vPassWd	[optional] NutzerPassWord
//		vMode	[optional] Modi beim Eröffnen des Projektes
STDMETHODIMP CGeoDocs::Open (BSTR bstrName,
	VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// Initialisierung der ArgumentVariants
CComVariant vArgUser; 
CComVariant vArgPassWd;
CComVariant vArgMode; 

// versuchen, Parameter auszuwerten
string strName (AnsiString(bstrName));
string strUser;				// default: kein NutzerName
string strPassWd;			// default: kein PassWort
short iMode = OM_Normal;	// default: normal eröffnen
	
	try {
	// 2. UserName
	HRESULT hr = VariantChangeType (&vArgUser, &vUser, 0, VT_BSTR);

		if (SUCCEEDED(hr)) 
			strUser = AnsiString(V_BSTR(&vArgUser));
		else {
			hr = VariantChangeType (&vArgUser, &vUser, 0, VT_ERROR);
			if (SUCCEEDED(hr) && V_ERROR(&vArgUser) == DISP_E_PARAMNOTFOUND) {
			// Parameter ausgelassen, defaultwert verwenden (== pName)
				strUser = get_name (strName);
				strlwr (&strUser[0]);
			} else
				_com_issue_error(hr);	// mit Fehler raus
		}

	// 3. PassWort
		hr = VariantChangeType (&vArgPassWd, &vPassWd, 0, VT_BSTR);
		if (SUCCEEDED(hr)) 
			strPassWd = AnsiString(V_BSTR(&vArgPassWd));
	
	// 4. Mode
		hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I2);
		if (SUCCEEDED(hr)) 
			iMode = V_I2(&vArgMode);

	// DatenBasis mit gegebenen Parametern eröffnen
		{
		TRIAS_OPEN TO;
		CGeoDoc *pDoc = NULL;
		
			INITSTRUCT (TO, TRIAS_OPEN);
			TO.lpProject = (char *)strName.c_str();
			TO.lpUser = (char *)strUser.c_str();
			TO.lpPassWord = (char *)strPassWd.c_str();
			TO.iMode = iMode;
			
		ErrCode EC = DEX_OpenProject(TO);	// Projekt eröffnen

			if (EC != EC_OKAY) 	// Fehler aufgetreten
				_com_issue_error(ErrorFromErrCode (EC));
			
	// Add to Collection
		INITDOCSTATUS rgIOS = INITDOCSTATUS_Error;
		long lIndex = m_pEnumDocs -> m_pDocsArray -> hasDoc (strName.c_str());
		
			if (lIndex == -1L) {
			CGeoDocCreator DocCr (*(m_pEnumDocs -> m_pDocsArray));
			
				rgIOS = m_pICProc (m_pUnk, m_pApp, DocCr, m_dwData, &strName);
				if (rgIOS == INITDOCSTATUS_Error)
					_com_issue_error(E_FAIL);
			} else 
				rgIOS = INITDOCSTATUS_Exists;
			
			if (rgIOS == INITDOCSTATUS_Created || rgIOS == INITDOCSTATUS_Exists) {
			// get IDispatch
				hr = GetDocDisp (strName.c_str(), ppIDoc);
				if (FAILED(hr)) _com_issue_error(hr);

				DEX_RePaintWait();
				return NOERROR;
			}

		// ansonsten durchfallen
		} 
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return E_UNEXPECTED;
}


