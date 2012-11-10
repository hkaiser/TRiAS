// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 16.10.2000 08:40:28 
//
// @doc
// @module GenObjPropDest.cpp | Definition of the <c CGenObjPropDest> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ClipBrd.hxx>
#include <Propname.hxx>

#include "GenObjPropDest.h"
#include "ObjPropDestWindow.h"

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern TCHAR g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in eine Zeichenkette
STDMETHODIMP CGenObjPropString::Begin(ULONG ulExpectedCnt)
{
	m_ulMaxProps = ulExpectedCnt;
	return S_OK;
}

STDMETHODIMP CGenObjPropString::End()
{
	return S_OK;
}

STDMETHODIMP CGenObjPropString::Cancel()
{
	return S_OK;
}

STDMETHODIMP CGenObjPropString::BeginObject(INT_PTR lONr)
{
#if defined(_DEBUG)
	m_lONr = lONr;
#endif // defined(_DEBUG)
	return S_OK;
}

STDMETHODIMP CGenObjPropString::ObjectProperty(INT_PTR lONr, ULONG ulNumber, LPCSTR pcValue)
{
	_ASSERTE(m_lONr == lONr);
	_ASSERTE(ulNumber < m_ulMaxProps);
	_ASSERTE(NULL != pcValue);

	if (m_fGenObjProp) {	
		if (0 != ulNumber && '\0' != m_cDelimiter)
			m_strText += m_cDelimiter;		// Trennzeichen einf¸gen
			
		m_strText += pcValue;
	}
	return S_OK;
}

STDMETHODIMP CGenObjPropString::EndObject(INT_PTR lONr)
{
	_ASSERTE(m_lONr == lONr);
#if defined(_DEBUG)
	m_lONr = 0;
#endif // defined(_DEBUG)

	if (m_fGenObjProp)
		m_strText += m_strEol;		// neue Zeile
	return S_OK;
}

STDMETHODIMP CGenObjPropString::BeginHeadline()
{
	return S_OK;
}

STDMETHODIMP CGenObjPropString::Headline(ULONG ulNumber, LPCSTR pcValue)
{
	_ASSERTE(ulNumber < m_ulMaxProps);
	_ASSERTE(NULL != pcValue);

	if (0 != ulNumber && '\0' != m_cDelimiter)
		m_strText += m_cDelimiter;		// Trennzeichen einf¸gen

CPropertyName Name (pcValue);

	if (Name.hasSubGroup()) {
		m_strText += Name.GetSubGroup().c_str();
		m_strText += "\\";
	}
	m_strText += Name.GetName().c_str();
	return S_OK;
}

STDMETHODIMP CGenObjPropString::EndHeadline()
{
	m_strText += m_strEol;		// neue Zeile
	return S_OK;
}

STDMETHODIMP CGenObjPropString::BeginCumulation()
{
	return S_OK;
}

STDMETHODIMP CGenObjPropString::Cumulation(ULONG ulNumber, LPCSTR pcValue)
{
	_ASSERTE(ulNumber < m_ulMaxProps);
	_ASSERTE(NULL != pcValue);

	if (0 != ulNumber && '\0' != m_cDelimiter)
		m_strText += m_cDelimiter;		// Trennzeichen einf¸gen
		
	m_strText += pcValue;
	return S_OK;
}

STDMETHODIMP CGenObjPropString::EndCumulation()
{
	m_strText += m_strEol;		// neue Zeile
	return S_OK;
}

STDMETHODIMP CGenObjPropString::BeginCount()
{
	return S_OK;
}

STDMETHODIMP CGenObjPropString::Count(ULONG ulNumber, LPCSTR pcValue)
{
	_ASSERTE(ulNumber < m_ulMaxProps);
	_ASSERTE(NULL != pcValue);

	if (0 != ulNumber && '\0' != m_cDelimiter)
		m_strText += m_cDelimiter;		// Trennzeichen einf¸gen
		
	m_strText += pcValue;
	return S_OK;
}

STDMETHODIMP CGenObjPropString::EndCount()
{
	m_strText += m_strEol;		// neue Zeile
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe ins Clipboard
STDMETHODIMP CGenObjPropClipboard::End()
{
CClipboard cb;

	cb.Clear();
	cb.Insert(m_strText.c_str());
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in eine Datei
STDMETHODIMP CGenObjPropFile::Headline(ULONG ulNumber, LPCSTR pcValue)
{
	_ASSERTE(ulNumber < m_ulMaxProps);
	_ASSERTE(NULL != pcValue);

	if (0 != ulNumber && '\0' != m_cDelimiter)
		m_strText += m_cDelimiter;		// Trennzeichen einf¸gen

CPropertyName Name (pcValue);

	if (Name.hasSubGroup()) {
		m_strText += Name.GetSubGroup().c_str();
		m_strText += "\\";
	}
	m_strText += "\"";
	m_strText += Name.GetName().c_str();
	m_strText += "\"";
	return S_OK;
}

STDMETHODIMP CGenObjPropFile::End()
{
FILE *fp = fopen (m_strFile.c_str(), "w+b");

	if (NULL == fp)
		return E_HANDLE;

	fwrite (m_strText.c_str(), m_strText.size(), sizeof(char), fp);
	fclose (fp);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in Objekteigenschaft
STDMETHODIMP CGenWriteObjProp::BeginObject(INT_PTR lONr)
{
	ResetText();
	if (m_fOutputCount) {
	char cbBuffer[32];

		ultoa (GetExpectedCount(), cbBuffer, 10);
		AddText(cbBuffer);
		AddText(GetDelimiter());
	}
	return CGenObjPropString::BeginObject(lONr);
}

STDMETHODIMP CGenWriteObjProp::EndObject(INT_PTR lONr)
{
	_ASSERTE(m_ObjProp.IsValid());

LPCSTR pcText = GetText();

	if (NULL != pcText && '\0' != pcText[0]) {
	// nur, wenn wenigstens ein Zeichen geschrieben werden soll
	HRESULT hr = m_ObjProp -> Set(lONr, GetText());

		if (SUCCEEDED(hr))
			hr = CGenObjPropString::EndObject(lONr);
		return hr;
	}
	return CGenObjPropString::EndObject(lONr);		// muﬂte nichts geschrieben werden
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in ein Fenster
STDMETHODIMP CGenObjPropWindow::Begin(ULONG ulExpectedCnt)
{
	m_ulCnt = 0;
	RETURN_FAILED_HRESULT(CGenObjPropString::Begin(ulExpectedCnt));
	return S_OK;
}

STDMETHODIMP CGenObjPropWindow::End()
{
ResourceFile RF (g_pDLLName);
Window Parent(m_hWnd);
CObjPropDestWindow Wnd (&Parent, ResID(IDD_OBJPROPDESTWINDOW, &RF), GetText(), m_fHeadline);

	Wnd.SetCaption(m_strCaption.c_str());
	Wnd.ChangePosition(m_ptPos);
	Wnd.Show(Centre);
	return Wnd.Result() ? S_OK : S_FALSE;
}

// zus‰tzliche erste Spalte hinzuzaubern
STDMETHODIMP CGenObjPropWindow::BeginHeadline()
{
ResourceFile RF (g_pDLLName);
ResString resNr (ResID(IDS_NUMMER, &RF), 32);

	AddText(resNr);	
	AddDelimiter();
	RETURN_FAILED_HRESULT(CGenObjPropString::BeginHeadline());
	return S_OK;
}

STDMETHODIMP CGenObjPropWindow::BeginObject(INT_PTR lONr)
{
	if (m_fGenObjProp) {
	char cbBuffer[32];

		AddText(ltoa (++m_ulCnt, cbBuffer, 10));
		AddDelimiter();
	}
	RETURN_FAILED_HRESULT(CGenObjPropString::BeginObject(lONr));
	return S_OK;
}

STDMETHODIMP CGenObjPropWindow::BeginCumulation()
{
ResourceFile RF (g_pDLLName);
ResString resIndex (ResID(IDS_INDEX, &RF), 32);

	AddText(resIndex);	
	AddDelimiter();
	RETURN_FAILED_HRESULT(CGenObjPropString::BeginCumulation());
	return S_OK;
}

STDMETHODIMP CGenObjPropWindow::BeginCount()
{
ResourceFile RF (g_pDLLName);
ResString resCnt (ResID(IDS_COUNT, &RF), 32);

	AddText(resCnt);	
	AddDelimiter();
	RETURN_FAILED_HRESULT(CGenObjPropString::BeginCount());
	return S_OK;
}


