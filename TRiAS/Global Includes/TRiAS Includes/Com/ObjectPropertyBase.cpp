// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.08.99 22:28:20
//
// @doc
// @module ObjectPropertyBase.cpp | Basisklasse für eine Objekteigenschaft
// (Declaration of the <c CObjectPropertyBase> class

#include <Com/ObjectPropertyBase.h>

#undef THIS_FILE
#define THIS_FILE __FILE__

///////////////////////////////////////////////////////////////////////////////
// Konstruktion
CObjectPropertyBase::CObjectPropertyBase (LPCSTR pcName, UINT uiHelpID, bool fRO)
	: m_uiHelpID(uiHelpID), m_fIsReadOnly(fRO)
{
	m_ulCnt = 0;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	if (pcName) 
		m_strName = pcName;
}

CObjectPropertyBase::CObjectPropertyBase (UINT uiNameID, UINT uiHelpID, bool fRO)
	: m_uiHelpID(uiHelpID), m_fIsReadOnly(fRO)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	m_ulCnt = 0;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	if (0 != uiNameID) {
	CString str;

		str.LoadString(uiNameID);
		_ASSERTE(str.GetLength() > 0);
		m_strName = str;
	}
}

CObjectPropertyBase::~CObjectPropertyBase()
{
}

// Funktion entscheidet, ob IObjectProperty2 verfügbar ist oder nicht
HRESULT WINAPI CObjectPropertyBase::_Choice (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
CObjectPropertyBase *pThis = (CObjectPropertyBase *)pv;

	if (pThis -> GetRO()) 
		return E_NOINTERFACE;		// 'Set' ist nicht verfügbar (schreibgeschützte Objekteigenschaft)

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis + dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectProperty specific functions
STDMETHODIMP CObjectPropertyBase::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	if (NULL != pBuffer && wLen > 0) {
	UINT uiLen = min((UINT)(wLen-1), m_strName.length());

		strncpy (pBuffer, m_strName.c_str(), uiLen);
		pBuffer[uiLen] = '\0';
	}

	if (pdwData) 
		*pdwData = m_fIsReadOnly ? PROPCAPS_NONE : PROPCAPS_NOTREADONLY;

	return NOERROR;
}

STDMETHODIMP CObjectPropertyBase::Reset (void)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	m_ulCnt = 0;
	return NOERROR;
}

STDMETHODIMP_(ULONG) CObjectPropertyBase::Count (void)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	return m_ulCnt;
}

STDMETHODIMP CObjectPropertyBase::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	_ASSERTE(NULL != pBuffer);
	_ASSERTE(0 != ulLen);

CString strHelp;

	strHelp.LoadString (m_uiHelpID);
	_ASSERTE(strHelp.GetLength() > 0);

ULONG ul = min(ulLen-1, ULONG(strHelp.GetLength()));

	strncpy (pBuffer, strHelp, ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// default: no cumulation 
STDMETHODIMP CObjectPropertyBase::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)

	_ASSERTE(NULL != pBuffer);
	_ASSERTE(0 != ulLen);

	*pBuffer = '\0';	// no cumulation here
	if (pulWritten) *pulWritten = 0;
	
	return S_OK;
}

STDMETHODIMP CObjectPropertyBase::Set (LONG, LPCSTR)
{
	return E_NOTIMPL;	// should be overridden 
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CObjectPropertyBase::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID) 
		return E_POINTER;
	return E_NOTIMPL;		// should be overidden
}

// IPersistStreamInit members
STDMETHODIMP CObjectPropertyBase::IsDirty (void)
{
	return GetDirty() ? S_OK : S_FALSE;
}

// IPersistStream methods 
STDMETHODIMP CObjectPropertyBase::Load (IStream *pIStream)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;
	if (NULL == pIStream) 
		return E_POINTER;

// Länge des ObjPropNamens einlesen
char *pT = NULL;

	COM_TRY {
	ULONG ulSize = 0L;
	
		THROW_FAILED_HRESULT(pIStream -> Read (&ulSize, sizeof(ULONG), NULL));
		if (ulSize > 0) {
			pT = new char [ulSize+1];		// Namen selbst wieder einlesen
			THROW_FAILED_HRESULT(pIStream -> Read (pT, ulSize+1, NULL));
			SetName (pT);
		}
	} COM_CATCH_OP(delete pT);
	if (pT) delete pT;

	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CObjectPropertyBase::Save (IStream *pIStream, BOOL fClearDirty)
{
	if (NULL == pIStream) return E_POINTER;

// Namen der Objekteigenschaft wegschreiben 
ULONG ulSize = GetNameStr().length();

	RETURN_FAILED_HRESULT(pIStream -> Write (&ulSize, sizeof(ULONG), NULL));
	RETURN_FAILED_HRESULT(pIStream -> Write (GetName(), ulSize+1, NULL));

	return S_OK;
}
	
STDMETHODIMP CObjectPropertyBase::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) 
		return E_POINTER;

	pcbSize -> QuadPart = sizeof(ULONG) + GetNameStr().length() +1;
	return S_OK;
}

STDMETHODIMP CObjectPropertyBase::InitNew()
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;
//
// nothing to to else
//
	m_fIsInitialized = true;
	return S_OK;
}

