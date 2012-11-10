///////////////////////////////////////////////////////////////////////////
// @doc 
// @module COMHelper.h | Description goes here

#if !defined(_COMHELPER_H__3460D3E9_62C9_11D2_9EDE_006008447800__INCLUDED_)
#define _COMHELPER_H__3460D3E9_62C9_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/list>
using namespace ospace::std;

HRESULT InstantiateCOMObject(
	CLSID clsid,						// in:	ClassID des Objektes
	IUnknown **ppUnk);					// out:	Ptr auf IUnknown
HRESULT GetISPP(
	IUnknown * pUnk,					// in:	Ptr auf IUnknown-Interface des COM-Objektes
	ISpecifyPropertyPages **ppISPP);	// out:	Ptr auf ISpecifyPropertyPages-Interface des COM-Objektes
HRESULT GetIPP(
	IUnknown * pUnk,					// in:	Ptr auf IUnknown-Interface des COM-Objektes
	IPropertyPage **ppIPP);				// out:	Ptr auf IPropertyPage-Interface des COM-Objektes
HRESULT ClearUnkArray(
	unsigned long cObjects,				// in:	Anzahl der Objekte im Array
	IUnknown ** &ppUnk);				// out:	indirekter Ptr auf das leere Array
HRESULT	PrepareCAUUID(
	CAUUID * &pcaGUID);					// out:	Ptr auf CAUUID-Struktur
HRESULT	PrepareCAUUID(
	UINT cObjects,						// in:	Anzahl der PropertyPageObjekte
	CAUUID * &pcaGUID);					// out:	Ptr auf CAUUID-Struktur
HRESULT FreeCAUUID(
	CAUUID * &pcaGUID);					// out:	Ptr auf CAUUID-Struktur
void RegControl(CString path);
void UnregControl(CString path);
HINSTANCE GetHandleOfModule(CString path);
CString AssemblyHLMRegPath(CLSID clsid);
CString AssemblyHCRRegPath(CLSID clsid);
CString GetInprocServer32Value(CString regStr);
CString GetToolboxBitmap32Value(CString regStr);
long ExtractBitmapID(CString &regPathStr);
long StrToLong(CString str);
CString GetRegValue(CString regPathStr);
HRESULT PreparePROPPAGEINFO(
	PROPPAGEINFO * &pPropPageInfo);		//out:	Ptr auf PROPPAGEINFO-Struktur
void FreePROPPAGEINFO(
	PROPPAGEINFO * pPropPageInfo);		//in:	Ptr auf PROPPAGEINFO-Struktur
HRESULT GetPropsOfCOMObject(
	IUnknown * pUnk,					// in:	Ptr auf IUnknown-Interface
	CAUUID * &pPages);					// out:	Ptr auf CAUUID-Struktur der ermittelten PropertyPages
HRESULT GetCommonProps(
	list<CAUUID *> pps,					// in:	Liste von Ptr auf die zu prüfenden CAUUID-Strukturen
	CAUUID * &commonPPs);				// out:	Ptr auf CAUUID-Struktur der ermittelten PropertyPages
HRESULT ObjectWithNoPPExists(
	list<CAUUID *> objectPropIDs,		// in:	Liste von Ptr auf CAUUID-Strukturen der COM-Objekte
	BOOL &retVal);						// out:	TRUE, wenn eins der Objekte in objectPropIDs keine Property Pages hat

#endif // !defined(_COMHELPER_H__3460D3E9_62C9_11D2_9EDE_006008447800__INCLUDED_)
