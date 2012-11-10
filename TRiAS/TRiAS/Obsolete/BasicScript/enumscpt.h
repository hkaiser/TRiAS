// Enumerator der ObjektProperties einer Erweiterung --------------------------
// File ENUMPROP.HXX

#if !defined(_ENUMSCPT_H)
#define _ENUMSCPT_H

class CMacroHelper;
class CMacro;

// Enumerator aller Macroscripts -------------------
class CEnumMacroScripts : IEnumScripts  
{ 
private:
	DWORD m_dwRefCnt;		// reference count
	ULONG m_ulCurr;		

protected:
	CObArray m_ObArray;
	CMapStringToOb m_MapScript;

	bool FInit (CEnumMacroScripts *pEnum);
	CEnumMacroScripts (void);

public:                
	CObArray * GetArray(void) { return &m_ObArray; }
	ULONG GetCurr (void) { return m_ulCurr; }                  
	void SetCurr (ULONG ulCurr) { m_ulCurr = ulCurr; }
	CMacroHelper *GetAt (int i) { return (CMacroHelper *)m_ObArray.GetAt (i); }

	~CEnumMacroScripts (void);

static CEnumMacroScripts *CreateInstance (CEnumMacroScripts *pEnum = NULL);
	
	void ReleaseStreams();
	HRESULT AddScript (LPCSTR pcName, CMacro *pM);
	HRESULT AddScript (CMacroHelper *pHelper);
	HRESULT GetNextString (int i, CString *pstrNext);
	HRESULT FindByName (LPCSTR pName, CMacro ** ppM);
	HRESULT Next (ULONG celt, CMacro **ppM, ULONG *ppeltFetched);
	HRESULT DelItem (CString strName, bool *pfNew);

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	
// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched);
	STDMETHOD (Skip) (THIS_ ULONG celt);
	STDMETHOD (Reset) (THIS);
	STDMETHOD (Clone) (THIS_ IEnumScripts **ppenm);
	                                     
// *** EnumMacroScript methods
	STDMETHOD (FindByName) (LPCSTR pName, LPUNKNOWN *ppUnk);
};

#endif // _ENUMSCPT_H

