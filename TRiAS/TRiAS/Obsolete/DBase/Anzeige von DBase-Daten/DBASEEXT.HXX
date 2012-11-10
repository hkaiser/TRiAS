// File: DBASEEXT.HXX

#if !defined(_DBASEEXT_HXX)
#define _DBASEEXT_HXX

extern "C" {
// ObjektPropertyFunktionen
		char * __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, short iLen, DWORD eData);
		void __export PASCAL FreeFieldName (DWORD);
}

enum ParamType { FeldName, dBaseExpr, TagName};

#ifndef NODBASEEXTENSION
class CTableNameTree;
class CFeldInfos
{
public:       
	char *m_pFieldName;
	char *m_pTableName;
	
	CFeldInfos (void);
	~CFeldInfos (void);
};	

class CdBaseObjectProperties : public CObjectProperties 
{
protected:
	short InstallIdentPropertyFunctions (ulong ulIdent, 
										 CTableNameTree *pTableNameTree = NULL,
										 char *pAliasName = NULL);
public:
	static CdBaseObjectProperties *CreateInstance (LPUNKNOWN pIUnk, LPCSTR pcGroupName = NULL, 
												   DWORD dwFlags = PROPCAPS_NONE);

//	Konstruktor/Destruktor
	CdBaseObjectProperties (LPUNKNOWN pIUnk, LPCSTR pcGroupName, DWORD dwFlags);
	~CdBaseObjectProperties (void);

	STDMETHOD(OnNewReferenceObject) (THIS_ LONG lRefONr);
	short InstallActPropertyFunctions (long lObjNr);	// Objekt-Eigenschafts-Funktionen
};

class DBaseExtension : public CTriasExtension {
private:
	HWND _hWnd;			 	// ORFenster mit Fokus
	long _lONr;			 	// selektiertes Objekt
	long _lIdent;		   	// zugehöriger Ident
	short _Type;			// Typ eines Parameters in INI-Datei

	char *_pDBaseFile;
	char *_pDBaseField;
	char *_pDBaseKey;
	Bool m_bOemToAnsi;
	DBaseDispatchTree *_pDBaseDisp;
	CdBaseObjectProperties *m_pObjProp;

// 	überladene virtuelle Funktion(en)
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

protected:
//	weitere Funktionen
	LRESULT Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
	short ReadDBaseCodes (long lONr, long lIdent);
	Bool ValidMK (long MK);    // prüfe Wertebereich
	Bool ExistsMValue (long lONr, ulong MCode);
	Bool GetMerkmalsValue (long lONr, ulong MCode, char *pBuffer = 0, short iLen = 0);
	pchar _ExpandDBaseExpression (long ONr, pchar pExpr); // 	dBase-Expression expandieren

public:
// 	Konstruktor / Destruktor
	DBaseExtension (void);
	~DBaseExtension (void);

	Bool ShowDBaseInfo (void);
	Bool ToAnsi (void) { return m_bOemToAnsi; }
	short ParType (void) { return _Type; }
		
	friend char * __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, short iLen, DWORD eData);
	friend class CdBaseObjectProperties;
};
#endif  // NODBASEEXTENSION

#endif  // _DBASEEXT_HXX
