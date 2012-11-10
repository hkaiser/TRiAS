// TRiAS-interne Merkmale als ReadWrite-Objekteigenschaft ---------------------
// File: OPRPFEAT.CXX

#include "trias03p.hxx"

#include "trias03.h"		// Resourcen

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

#include <xtsnguid.h>
#include <oprpguid.h>

#include <errinst.hxx>

#include "intoprop.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LONG g_cObj;	// globaler ObjektZähler

static const char *MCodeObjPropFuncName (long lMCode)
{
static char cbFuncName[_MAX_PATH];
ErrInstall EI (WC_NOMERKMAL);
PBDDATA pbdData;
ErrCode RC; 

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbFuncName;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = _MAX_PATH;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY) {
	string strFmt = ResString (IDM_MCODEFORMAT, 32);

		if (10 == DEX_GetMkBase()) {
			strFmt += "%ld";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		} else {
			strFmt += "%lx";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		}
	}

return cbFuncName;
}

static bool MCodeRO (long lMCode)
{
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMAL pbdData;

	INITSTRUCT (pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	if (EC_OKAY == DEX_GetPBDData (pbdData))
		return pbdData.ipbdMTyp & PBDMERKMAL_READONLY;

return false;
}

#pragma warning (disable:4355)

CObjPropMerkmal :: CObjPropMerkmal (LPFNDESTROYED pfnDestroy)
		 : CBaseObjectProperty (pfnDestroy, NULL, IDS_OBJPROPMCODEHELP),
		   m_Persist (this, this), m_Info (this, this),
		   m_Init (this, this), m_Template (this, this)
{
	m_lCum = 0L;

	INITSTRUCT(m_TM, TARGETMERKMAL);
	m_TM.lMCode = 0L;			// MerkmalsCode
	m_TM.iTTyp = TT_Objekt;

	m_fTemplateValid = false;
	m_fIsDirty = false;
	m_fInitialized = false;
}

// CopyConstruktor (für CloneTemplate) ----------------------------------------
CObjPropMerkmal :: CObjPropMerkmal (const CObjPropMerkmal &rOP)
		 : CBaseObjectProperty (rOP.m_pfnDestroy, NULL, IDS_OBJPROPMCODEHELP),
		   m_Persist (this, this), m_Init (this, this), m_Template (this, this),
		   m_Info (this, this)
{
	m_lCum = rOP.m_lCum;

	INITSTRUCT(m_TM, TARGETMERKMAL);
	m_TM.lMCode = rOP.m_TM.lMCode;		// MerkmalsCode
	m_TM.iTTyp = TT_Objekt;

	m_fTemplateValid = rOP.m_fTemplateValid;
	m_fIsDirty = rOP.m_fIsDirty;
	m_fInitialized = rOP.m_fInitialized;

	m_strTemplate = rOP.m_strTemplate;
}


#pragma warning (default:4355)

STDMETHODIMP CObjPropMerkmal :: Reset (void)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	m_lCum = 0L;
	m_strTemplate.remove();
	m_fTemplateValid = false;

return CBaseObjectProperty :: Reset();
}

STDMETHODIMP CObjPropMerkmal :: Eval(LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				     ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	m_TM.lTarget = (LPARAM)lONr;		// ObjektNummer
	m_TM.imaxLen = short(ulLen);
#if defined(WIN32)
	m_TM.pMText = pBuffer;
#else
	m_TM.pMText = s_cbOPBuffer;
#endif
	if (DEX_GetTextMerkmal (m_TM)) {		// MWert besorgen
#if defined(WIN32)
		if (pulWritten) *pulWritten = strlen (pBuffer);
		m_lCum += atol (pBuffer);
#else
	ULONG ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);
		if (pulWritten) *pulWritten = ul;
		m_lCum += atol (s_cbOPBuffer);
#endif
		m_ulCnt++;			// Merkmal existiert
	} else {
		*pBuffer = '\0';
		if (pulWritten) *pulWritten = 0;
		return ResultFromScode (E_FAIL);
	}

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal :: HelpInfo (LPSTR pBuffer, ULONG ulLen, 
					LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

ResString resHelp (m_resHelpID, _MAX_PATH);
string strT (2048, default_size);

	wsprintf ((char *)strT.c_str(), resHelp, GetName());
	strT.adjustlen(); 

ULONG ul = min(ulLen-1, ULONG(strT.length()));

	strncpy (pBuffer, strT.c_str(), ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0;

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal :: Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

#if defined(WIN32)
	ltoa (m_lCum, pBuffer, 10);
	if (pulWritten) *pulWritten = strlen (pBuffer);
#else
	ltoa (m_lCum, s_cbOPBuffer, 10);

ULONG ul = min (ulLen-1, hstrlen(s_cbOPBuffer));

	memcpy (pBuffer, s_cbOPBuffer, ul+1);
	if (pulWritten) *pulWritten = ul;
#endif

return NOERROR;
}

// normales Wegschreiben einer Objekteigenschaft ------------------------------
STDMETHODIMP CObjPropMerkmal :: Set (LONG lONr, LPCSTR pcBuffer)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	m_TM.lTarget = (LPARAM)lONr;		// ObjektNummer
	m_TM.imaxLen = (NULL !=  pcBuffer) ? strlen(pcBuffer) : 0;
	m_TM.pMText = (char *)pcBuffer;
	if (EC_OKAY != DEX_ModTextMerkmal(m_TM)) 	// MWert schreiben
		return ResultFromScode (E_FAIL);

return NOERROR;
}

// IUnknown für MerkmalsObjProp -----------------------------------------------
STDMETHODIMP CObjPropMerkmal :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
bool fOK = false;

	if (riid == IID_IObjectProperty2) {
		*ppvObj = this;
		fOK = true;
	} else if (riid == IID_IPersistStream) {
		*ppvObj = &m_Persist;
		fOK = true;
	} else if (riid == IID_IInitObjPropMerkmal) {
		*ppvObj = &m_Init;
		fOK = true;
	} else if (riid == IID_IPropertyTemplate) {
		*ppvObj = &m_Template;
		fOK = true;
	} else if (riid == IID_IPropertyInfo) {
		*ppvObj = &m_Info;
		fOK = true;
	}

	if (fOK) {
		LPUNKNOWN (*ppvObj) -> AddRef();
		return NOERROR;
	}

return CBaseObjectProperty::QueryInterface (riid, ppvObj);
}

// *** IObjectProperty specific functions *** ---------------------------------
STDMETHODIMP CObjPropMerkmal :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

DWORD dwData = 0L;
HRESULT hr = CBaseObjectProperty::GetPropInfo (pBuffer, wLen, &dwData);

	if (pdwData) *pdwData = dwData | PROPCAPS_USEABLEASTEMPLATE;

return hr;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
CObjPropMerkmal:: 
CPersistObjPropMerkmal::CPersistObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pOProp = pOProp;
}

CObjPropMerkmal:: 
CPersistObjPropMerkmal::~CPersistObjPropMerkmal (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CPersistObjPropMerkmal::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}


STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CPersistObjPropMerkmal::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CObjPropMerkmal::
CPersistObjPropMerkmal::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IPersist methods *** ---------------------------------------------------
STDMETHODIMP CObjPropMerkmal:: 
CPersistObjPropMerkmal::GetClassID (CLSID *pClsID)
{
	*pClsID = CLSID_ObjPropFeature;
	return NOERROR;
}

// *** IPersistStream methods *** ---------------------------------------------
STDMETHODIMP CObjPropMerkmal:: 
CPersistObjPropMerkmal::IsDirty (void)
{
	return ResultFromScode (m_pOProp -> GetDirty() ? S_OK : S_FALSE);
}


STDMETHODIMP CObjPropMerkmal:: 
CPersistObjPropMerkmal::Load (IStream *pIStream)
{
	if (NULL == pIStream)
		return ResultFromScode (E_POINTER);

// Länge des OPropNamens einlesen
ULONG ulSize = 0L;
HRESULT hr = pIStream -> Read (&ulSize, sizeof(ULONG), NULL);
	
	if (FAILED(hr)) return hr;

// TargetmerkmalStruktur einlesen
TARGETMERKMAL &rTM = m_pOProp -> GetTM();

	hr = pIStream -> Read (&rTM, sizeof(TARGETMERKMAL), NULL);
	if (FAILED(hr)) return hr;

	if (ulSize > 0) {
	// Template selbst wieder einlesen
	char *pT = new char [ulSize+1];

		if (NULL == pT) return ResultFromScode (E_OUTOFMEMORY);

		hr = pIStream -> Read (pT, ulSize+1, NULL);
		if (FAILED(hr)) return hr;
	
		m_pOProp -> SetName (pT);
		delete [] pT;
	}

// TemplateLänge einlesen
	ulSize = 0L;
	hr = pIStream -> Read (&ulSize, sizeof(ULONG), NULL);
	if (FAILED(hr)) return hr;

	m_pOProp -> SetTemplateValid (false);	// für alle Fälle
	if (ulSize > 0) {
	// Template selbst wieder einlesen
	char *pT = new char [ulSize+1];

		if (NULL == pT) return ResultFromScode (E_OUTOFMEMORY);

		hr = pIStream -> Read (pT, ulSize+1, NULL);
		if (FAILED(hr)) return hr;
	
		m_pOProp -> GetTemplStr() = pT;
		delete [] pT;

		m_pOProp -> SetTemplateValid (true);
	} else 
		m_pOProp -> GetTemplStr().remove();

// Objekt ist vollständig initialisiert
	m_pOProp -> SetDirty (false);
	m_pOProp -> SetInitialized (true);

return NOERROR;
}


STDMETHODIMP CObjPropMerkmal:: 
CPersistObjPropMerkmal::Save (IStream *pIStream, BOOL fClearDirty)
{
	if (NULL == pIStream)
		return ResultFromScode (E_POINTER);

// Namen der Objekteigenschaft wegschreiben 
ULONG ulSize = m_pOProp -> GetNameStr().length();
HRESULT hr = pIStream -> Write (&ulSize, sizeof(ULONG), NULL);

	if (FAILED(hr)) return hr;
	
	hr = pIStream -> Write (m_pOProp -> GetName(), ulSize+1, NULL);
	if (FAILED(hr)) return hr;
	
// TargetMerkmalStruktur wegschreiben
	hr = pIStream -> Write (&(m_pOProp -> GetTM()), sizeof(TARGETMERKMAL), NULL);
	if (FAILED(hr)) return hr;

// PropertyTemplate wegschreiben
const char *pText = m_pOProp -> GetTemplStr().c_str();

	ulSize = m_pOProp -> GetTemplStr().length();
	hr = pIStream -> Write (&ulSize, sizeof(ULONG), NULL);
	if (FAILED(hr)) return hr;

	if (NULL != pText && ulSize > 0) {
		hr = pIStream -> Write (pText, ulSize+1, NULL);
		if (FAILED(hr)) return hr;
	}

// evtl. DirtyFlag löschen
	if (fClearDirty) m_pOProp -> SetDirty (false);

return NOERROR;
}


STDMETHODIMP CObjPropMerkmal:: 
CPersistObjPropMerkmal::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return ResultFromScode (E_POINTER);

// Die StreamGröße wird bestimmt durch die Anzahl der Objekte im Enumerator
// plus die Größe des Zählers.
DWORD dwSize = m_pOProp -> GetTemplStr().length() + m_pOProp -> GetTM().imaxLen +
	       sizeof(TARGETMERKMAL) + sizeof(ULONG) +1;

// Größe auf 4Byte-Grenzen aufrunden
	pcbSize -> LowPart = ((dwSize+sizeof(LONG)-1) / sizeof(LONG)) * sizeof(LONG);
	pcbSize -> HighPart = 0L;

return NOERROR;
}


// InitialisierungsInterface //////////////////////////////////////////////////
CObjPropMerkmal:: 
CInitObjPropMerkmal::CInitObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pOProp = pOProp;
}

CObjPropMerkmal:: 
CInitObjPropMerkmal::~CInitObjPropMerkmal (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CInitObjPropMerkmal::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}


STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CInitObjPropMerkmal::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CObjPropMerkmal::
CInitObjPropMerkmal::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IInitObjPropMerkmal method *** -----------------------------------------
STDMETHODIMP CObjPropMerkmal::
CInitObjPropMerkmal::Init (LONG lMCode, BOOL fReadOnly)
{
	m_pOProp -> SetMCode (lMCode);
	m_pOProp -> SetName (MCodeObjPropFuncName(lMCode));
	m_pOProp -> SetRO (MCodeRO(lMCode));
	m_pOProp -> SetDirty (true);

	m_pOProp -> SetInitialized (true);

return NOERROR;
}

// IPropertytemplate Interface ////////////////////////////////////////////////
CObjPropMerkmal:: 
CTemplateObjPropMerkmal::CTemplateObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pOProp = pOProp;
}

CObjPropMerkmal:: 
CTemplateObjPropMerkmal::~CTemplateObjPropMerkmal (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CTemplateObjPropMerkmal::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}


STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CTemplateObjPropMerkmal::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CObjPropMerkmal::
CTemplateObjPropMerkmal::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IPropertyTemplate specific methods *** ---------------------------------
// Template setzen ------------------------------------------------------------
STDMETHODIMP CObjPropMerkmal::
CTemplateObjPropMerkmal::SetTemplate (LPCSTR pcBuffer)
{
	return m_pOProp -> SetTemplate (pcBuffer);
}

STDMETHODIMP CObjPropMerkmal::
CTemplateObjPropMerkmal::GetTemplate (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return m_pOProp -> GetTemplate (pBuffer, ulLen, pulWritten);
}

// Gesetztes Template verwenden -----------------------------------------------
STDMETHODIMP CObjPropMerkmal::
CTemplateObjPropMerkmal::ApplyTemplate (LONG lONr)
{
	return m_pOProp -> ApplyTemplate (lONr);
}

// Kopie dieses Objektes anlegen ----------------------------------------------
STDMETHODIMP CObjPropMerkmal::
CTemplateObjPropMerkmal::CloneTemplate (IPropertyTemplate **ppITempl)
{
// neue Instanz anlegen
CObjPropMerkmal *pOProp = new CObjPropMerkmal (*m_pOProp);

	if (NULL == pOProp)
		return ResultFromScode (E_OUTOFMEMORY);

HRESULT hr = pOProp -> QueryInterface (IID_IPropertyTemplate, (LPVOID *)ppITempl);

	if (FAILED(hr))
		delete pOProp;
	else if (m_pOProp -> HasDeleteFcn())
		InterlockedIncrement (&g_cObj);

return hr;
}

// IPropertyInfo Interface ////////////////////////////////////////////////////
CObjPropMerkmal:: 
CObjPropMerkmalInfo::CObjPropMerkmalInfo (IUnknown *pIUnk, CObjPropMerkmal *pOProp)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pOProp = pOProp;
}

CObjPropMerkmal:: 
CObjPropMerkmalInfo::~CObjPropMerkmalInfo (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CObjPropMerkmalInfo::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CObjPropMerkmal:: 
CObjPropMerkmalInfo::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CObjPropMerkmal::
CObjPropMerkmalInfo::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IPropertyInfo specific functions ---------------------------------------
STDMETHODIMP CObjPropMerkmal:: 
CObjPropMerkmalInfo::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	return m_pOProp -> GetPropInfo (pBuffer, wLen, pdwFlags);
}

STDMETHODIMP CObjPropMerkmal:: 
CObjPropMerkmalInfo::GetHelpInfo (LPSTR pBuffer, ULONG ulLen, 
								  LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	return m_pOProp -> HelpInfo (pBuffer, ulLen, pHelpFile, pulHelpCtx);
}

STDMETHODIMP CObjPropMerkmal:: 
CObjPropMerkmalInfo::SetPropName (LPCSTR pcBuffer)
{
ErrInstall EI (WC_NOMERKMAL);
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = m_pOProp -> GetMCode();
	pbdData.pbdKText = (char *)pcBuffer;	// neuer Name
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = (NULL != pcBuffer) ? strlen(pcBuffer) : 0;
	pbdData.pbdLTextLen = 0;

	// PBD-Info setzen
	if (EC_OKAY == DEX_ModPBDData(pbdData)) {
		m_pOProp -> SetName (pcBuffer);
		return NOERROR;
	} else
		return ResultFromScode (E_FAIL);
}

STDMETHODIMP CObjPropMerkmal:: 
CObjPropMerkmalInfo::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, 
								  ULONG ulHelpCtx)
{
	return ResultFromScode (E_NOTIMPL);
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen für TemplateInterface -------------------------------------
HRESULT CObjPropMerkmal::ApplyTemplate (LONG lONr)
{
	if (!m_fInitialized || !m_fTemplateValid) 
		return ResultFromScode (E_FAIL);

	m_TM.lTarget = (LPARAM)lONr;			// ObjektNummer
	m_TM.imaxLen = m_strTemplate.length();
	m_TM.pMText = (0 == m_strTemplate.length()) ? NULL : (char *)m_strTemplate.c_str();
	if (EC_OKAY != DEX_ModTextMerkmal(m_TM)) 	// MWert schreiben
		return ResultFromScode (E_FAIL);

return NOERROR;
}

// Template setzen ------------------------------------------------------------
HRESULT CObjPropMerkmal::SetTemplate (LPCSTR pcBuffer)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

// Template bearbeiten
	if (NULL != pcBuffer) 
		m_strTemplate = pcBuffer;
	else
		m_strTemplate.remove();

	m_fTemplateValid = true;
	m_fIsDirty = true;

return NOERROR;
}

// Template abfragen ----------------------------------------------------------
HRESULT CObjPropMerkmal::GetTemplate (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	if (NULL != pBuffer && ulLen > 0) {
	ULONG ulT = min (ulLen-1, ULONG(m_strTemplate.length()));

		strncpy (pBuffer, m_strTemplate.c_str(), ulT);
		pBuffer[ulT] = '\0';

		if (pulWritten)	*pulWritten = ulT;
		return NOERROR;
	}

return ResultFromScode (E_FAIL);
}
