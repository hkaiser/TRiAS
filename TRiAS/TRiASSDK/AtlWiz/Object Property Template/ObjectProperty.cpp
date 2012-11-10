[!if=(FileExists, "FALSE")]
// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: [!DateAndTime]
//
// @doc
// @module [!CPPName] | Implementation of the <c [!ClassName]> class

[!crlf]
#include "stdafx.h"

[!crlf]
#include "[!ProjectName].h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

[!crlf]
// IObjectProperty specifics
STDMETHODIMP [!ClassName]::Reset (void)
{
// TODO: Hier evtl. interen Zustand der Objekteigenschaft zurücksetzen
	return [!ClassName]::Reset();
}

[!crlf]
STDMETHODIMP [!ClassName]::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
// erstmal Basisklasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));

[!crlf]
// TODO: evtl. eigene Werte ergänzen: z.B. für Typ Integer:
//	if (pdwData)	
//		*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;	
	return S_OK;
}

[!crlf]
///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP [!ClassName]::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pBuffer) return E_POINTER;

[!crlf]
	_ASSERTE(0 != ulLen);

[!crlf]
// TODO: kumulativen Wert dieser Objekteigenschaft als Zeichenkette liefern
//	if (ulLen > ...) {
//		strcpy (pBuffer, ...);
//		if (pulWritten) 
//			*pulWritten = strlen (pBuffer);
//		return S_OK;
//	}
	return E_INVALIDARG;
}

[!crlf]
///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP [!ClassName]::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pBuffer) return E_POINTER;

[!crlf]
	_ASSERTE(0 != ulLen);

[!crlf]
// TODO: hier Wert der Objekteigenschaft für das Objekt lONr berechnen
// und als Zeichenkette in 'pBuffer' setzen und S_OK liefern.
//	if (ExistObjProp (lONr)) {
//		SetValueInBuffer (lONr, pBuffer, ulLen);
//		if (pulWritten) 
//			*pulWritten = strlen(pBuffer);
//
//	// Infos für Kumulation sammeln
//		IncrementCount();			// Zähler der erfolgreichen Aufrufe
//		return S_OK;
//	}

[!crlf]
// Wenn Objekteigenschaft für dieses Objekt nicht existiert, dann
// E_FAIL liefern.
	return E_FAIL;		// ObjeProperty existiert nicht
}

[!if=(ObjPropWritable, "TRUE")]
[!crlf]
// Neuen Wert für Objekteigenschaft setzen
STDMETHODIMP [!ClassName]::Set (LONG lONr, LPCSTR pcBuffer)
{
// TODO: Neuer (zuzuweisender Wert) ist in 'pcBuffer' enthalten. Diesen Wert der
// Objekteigenschaft des Objektes 'lONr' in geeigneter Weise zuweisen.
	return S_OK;
}
[!endif]

[!if=(IPERSISTSTREAMINIT, "TRUE")]
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP [!ClassName]::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP [!ClassName]::Load (IStream *pStm)
{
	if (GetInitialized())
		return E_UNEXPECTED;

[!crlf]
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Load (pStm));

[!crlf]
// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Save (pStm, fClearDirty));

[!crlf]
// TODO: Save your own data to the stream
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

[!crlf]
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetSizeMax (pcbSize));

[!crlf]
// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::InitNew()
{
	if (GetInitialized())
		return E_UNEXPECTED;

[!crlf]
// TODO: initialize your data
	SetInitialized();
	return S_OK;
}
[!endif]
