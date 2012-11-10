// Von TRIAS03 exportierte Funktionen -----------------------------------------
// File: FUNCS03.H

#if !defined(_FUNCS03_H)
#define _FUNCS03_H

#include <rotate.hxx>
#include <justify.hxx>

// C++ -Funktionen ////////////////////////////////////////////////////////////

// Funktion, über welche eine Instanz des Progressfensters erzeugt werden kann-
_TRIAS03_ENTRY HRESULT PiCreateInstance (REFIID riid, LPVOID *ppIPrInd);

#if defined(WIN32)

// Externe Funktion, über welche eine Undo/Redo-Instanz erzeugt werden kann ---
_TRIAS03_ENTRY HRESULT UndoCreateInstance (REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT ObjPropCreateInstance (IUnknown *pIUnk, REFCLSID rClsID, 
							REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT DataObjectCreateInstance (IUnknown *pIUnk, REFIID riid, LPVOID *ppvObj);

///////////////////////////////////////////////////////////////////////////////
// PropertyActions erzeugen bzw. ausführen

///////////////////////////////////////////////////////////////////////////////
// Counted Array of LPCSTR's 
typedef struct tagCALPCSTR {
	ULONG cElems;
	LPCSTR *pElems;
} CALPCSTR;

typedef bool (* REGPROPACTPROC)(IClassProperty *, LPCSTR, DWORD);

_TRIAS03_ENTRY HRESULT RegisterPropertyActions (REGPROPACTPROC, DWORD);
_TRIAS03_ENTRY HRESULT PActCreateInstance (LPCSTR pcDesc, REFIID riid, LPVOID *ppvObj);
_TRIAS03_ENTRY HRESULT InitPropertyActionSequence (
		LPCSTR pcDesc, CALPCSTR *pcbActs, struct IPropertyActionSequence **ppISeq);
_TRIAS03_ENTRY HRESULT InitPropertyActionSequence (
		LPCSTR pcDesc, struct tagCALPCLSID *pcaClsIds, struct IPropertyActionSequence **ppISeq);
_TRIAS03_ENTRY HRESULT RunPropertyActionSequence (
		HWND hWnd, LPCSTR pcDesc, CALPCSTR *pcbActs, 
		struct IProgressIndicator *pIStatus = NULL,
		IDataObject *pIInData = NULL, IDataObject **ppIOutData = NULL);
_TRIAS03_ENTRY HRESULT RunPropertyActionSequence (
		HWND hWnd, LPCSTR pcDesc, struct tagCALPCLSID *pcaClsIds, 
		struct IProgressIndicator *pIStatus = NULL,
		IDataObject *pIInData = NULL, IDataObject **ppIOutData = NULL);

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

///////////////////////////////////////////////////////////////////////////////
// Protoypes of the 'API' defined for horizontal scrolling of a listbox
_TRIAS03_ENTRY BOOL FInitListboxExtents(HWND);
_TRIAS03_ENTRY WORD WAddExtentEntry(HWND, LPCSTR);
_TRIAS03_ENTRY WORD WRemoveExtentEntry(HWND, LPCSTR);
_TRIAS03_ENTRY BOOL FFreeListboxExtents(HWND);
_TRIAS03_ENTRY void ResetListboxExtents(HWND);

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// sonstige globale Funktionen
const int MAX_OKS_LEN = 32;		// max. Länge eines OKS

_TRIAS03_ENTRY HRESULT ClassFromIdent (ULONG ulIdent, char *pBuffer, int iBuffLen = MAX_OKS_LEN);
_TRIAS03_ENTRY HRESULT IdentFromClass (LPCSTR pcClass, ULONG *pulIdent, bool fCreateNew = false);
_TRIAS03_ENTRY int CALLBACK CmpEntries (LPARAM lParam1, LPARAM lParam2, LPARAM dwData);

// C-Funktionen ///////////////////////////////////////////////////////////////
extern "C" {

// InitialisierungsFunktion für TRIAS03 ---------------------------------------
_TRIAS03_ENTRY void FUNCTYPE InitTrias03 (HWND, UINT, UINT, UINT);

} // extern "C"

#endif // _FUNCS03_H
