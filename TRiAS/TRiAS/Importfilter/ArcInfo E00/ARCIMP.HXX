// Import aus dem E00-Format ------------------------------------
// File: ARCIMP.HXX

#if !defined(_ARCIMP_HXX)
#define _ARCIMP_HXX

class CImpArcExtension 
:	public CTriasExtension 
{
private:
    CImportArcInfo *m_pIImport;       // ImportInterface

public:
    CImpArcExtension (void);
    ~CImpArcExtension (void);

	STDMETHOD (QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj);

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

	IUnknown *get_CS() const { return m_pIImport->get_CS(); }
};

#endif // _ARCIMP_HXX


