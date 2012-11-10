// Von TRIAS03 exportierte Funktionen -----------------------------------------
// File: FUNCS03.H

#if !defined(_FUNCS03_H)
#define _FUNCS03_H

#include <rotate.hxx>
#include <justify.hxx>
#include <DataHelp.h>

// C++ -Funktionen ////////////////////////////////////////////////////////////

// Funktion, über welche eine Instanz des Progressfensters erzeugt werden kann-
_TRIAS03_ENTRY HRESULT PiCreateInstance (REFIID riid, LPVOID *ppIPrInd);

// Externe Funktion, über welche eine Undo/Redo-Instanz erzeugt werden kann ---
_TRIAS03_ENTRY HRESULT UndoCreateInstance (REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT ObjPropCreateInstance (IUnknown *pIUnk, REFCLSID rClsID, 
							REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT DataObjectCreateInstance (IUnknown *pIUnk, REFIID riid, LPVOID *ppvObj);

///////////////////////////////////////////////////////////////////////////////
// Namen einer Objekteigenschaft aus ihrem MCode erzeugen
_TRIAS03_ENTRY LPCSTR MCodeObjPropFuncName (LPSTR pBuffer, long lMCode, short *piMTyp = NULL, short *piMLen = NULL);

///////////////////////////////////////////////////////////////////////////////
// PropertyActions erzeugen bzw. ausführen

///////////////////////////////////////////////////////////////////////////////
// Counted Array of LPCSTR's 
typedef struct tagCALPCSTR {
	ULONG cElems;
	LPCSTR *pElems;
} CALPCSTR;

typedef bool (* REGPROPACTPROC)(IClassProperty *, LPCSTR, DWORD);

///////////////////////////////////////////////////////////////////////////////
// 'klassische' Initialisierung einer PropertySequence
_TRIAS03_ENTRY HRESULT PActCreateInstance (LPCSTR pcDesc, REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT InitPropertyActionSequence (
		LPCSTR pcDesc, struct tagCALPCLSID *pcaClsIds, struct IPropertyActionSequence **ppISeq);
_TRIAS03_ENTRY HRESULT RunPropertyActionSequence (
		HWND hWnd, LPCSTR pcDesc, struct tagCALPCLSID *pcaClsIds, 
		struct IProgressIndicator *pIStatus = NULL,
		IDataObject *pIInData = NULL, IDataObject **ppIOutData = NULL, BOOL fInitNew = FALSE);

///////////////////////////////////////////////////////////////////////////////
// Initialisierung einer PropertySequence aus einer Xml-Resource
_TRIAS03_ENTRY HRESULT RunPropertyActionSequence (
		HWND hWnd, LPCSTR pcRsc, LPCSTR pcModule = NULL, 
		LPCSTR pcDesc = NULL, LPCSTR pcSaveAs = NULL,
		IProgressIndicator *pIStatus = NULL, IDataObject *pIInData = NULL, 
		IDataObject **ppIOutData = NULL, BOOL fInitNew = FALSE,
		IDataObject *pICtxData = NULL, BOOL fLoadFromFile = FALSE);

#if _TRiAS_VER < 0x0300
_TRIAS03_ENTRY HRESULT RegisterPropertyActions (REGPROPACTPROC, DWORD);
_TRIAS03_ENTRY HRESULT InitPropertyActionSequence (
		LPCSTR pcDesc, CALPCSTR *pcbActs, struct IPropertyActionSequence **ppISeq);
_TRIAS03_ENTRY HRESULT RunPropertyActionSequence (
		HWND hWnd, LPCSTR pcDesc, CALPCSTR *pcbActs, 
		struct IProgressIndicator *pIStatus = NULL,
		IDataObject *pIInData = NULL, IDataObject **ppIOutData = NULL);
#endif // _TRiAS_VER < 0x0300

///////////////////////////////////////////////////////////////////////////////
// Helper für IDataObject/IEnumLONG
template<class T> class IEnum;		// forward declaration only
_TRIAS03_ENTRY HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut = NULL);
_TRIAS03_ENTRY HRESULT SetEnumLONGData (IEnum<LONG> *pIEnum, IDataObject *pIDataObj);

_TRIAS03_ENTRY HRESULT GetEnumLONGData (IDataObject *pIDataObj, REFIID riid, LPVOID *ppv = NULL);

///////////////////////////////////////////////////////////////////////////////
// Helper für IDataObject/HWND
_TRIAS03_ENTRY HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd = NULL);
_TRIAS03_ENTRY HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj);

_TRIAS03_ENTRY HRESULT GetHWND (IDataObject *pIDataObj, const FORMATETC *pcfe, HWND *phWnd = NULL);
_TRIAS03_ENTRY HRESULT SetHWND (HWND hWnd, IDataObject *pDataObj, const FORMATETC *pcfe);

///////////////////////////////////////////////////////////////////////////////
// Helper für IDataObject/VARIANT
_TRIAS03_ENTRY HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv = NULL);
_TRIAS03_ENTRY HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe);

// Paketnummer setzen/lesen
_TRIAS03_ENTRY HRESULT GetPacketNumber (IDataObject *pIDO, long *plNumber);
_TRIAS03_ENTRY HRESULT SetPacketNumber (IDataObject *pIDO, long lNumber);

// Funktionen, die eine Objekteigenschaft schreiben/lesen
_TRIAS03_ENTRY HRESULT GetObjectProperty (IDataObject *pIDO, IObjectProperty **ppIObjProp);
_TRIAS03_ENTRY HRESULT SetObjectProperty (IDataObject *pIDO, IObjectProperty *pIObjProp);
_TRIAS03_ENTRY HRESULT SetObjectProperty (IDataObject *pIDO, LPCSTR pcName);

///////////////////////////////////////////////////////////////////////////////
// Laden einer nutzerdefinierten Ressource
_TRIAS03_ENTRY BYTE *ReadResource (HINSTANCE hInstance, int iResID, DWORD &dwResSize); 

///////////////////////////////////////////////////////////////////////////////
// sonstige globale Funktionen
const int MAX_OKS_LEN = 32;		// max. Länge eines OKS

_TRIAS03_ENTRY HRESULT ClassFromIdent (ULONG ulIdent, char *pBuffer, int iBuffLen = MAX_OKS_LEN);
_TRIAS03_ENTRY HRESULT IdentFromClass (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, bool fCreateNew = false);
_TRIAS03_ENTRY int CALLBACK CmpEntries (LPARAM lParam1, LPARAM lParam2, LPARAM dwData);

_TRIAS03_ENTRY StdMessBoxReply VMessageBox (Window *pW, ResID uiCaption, StdMessBox rgType, ResID uiText, ...);
_TRIAS03_ENTRY StdMessBoxReply VMessageBox (Window *pW, LPCSTR pcCaption, StdMessBox rgType, ResID uiText, ...);
_TRIAS03_ENTRY StdMessBoxReply VMessageBox (Window *pW, ResID uiCaption, StdMessBox rgType, LPCSTR pcText, ...);
_TRIAS03_ENTRY StdMessBoxReply VMessageBox (Window *pW, LPCSTR pcCaption, StdMessBox rgType, LPCSTR pcText, ...);

_TRIAS03_ENTRY os_string FakeTRiASName (UINT resID, ...);
_TRIAS03_ENTRY os_string FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
// Objekt doppeln
_TRIAS03_ENTRY HRESULT CloneObject (HPROJECT hPr, INT_PTR lObjToCopy, INT_PTR lNewIdent, INT_PTR *plNewObj);

// C-Funktionen ///////////////////////////////////////////////////////////////
// InitialisierungsFunktion für TRIAS03 
extern "C" 
_TRIAS03_ENTRY void FUNCTYPE InitTrias03 (HWND, UINT, UINT, UINT);

///////////////////////////////////////////////////////////////////////////////
// Testen, ob der Nutzer Administratorrechte besitzt
_TRIAS03_ENTRY BOOL AmIAdministrator (void);

#endif // _FUNCS03_H
