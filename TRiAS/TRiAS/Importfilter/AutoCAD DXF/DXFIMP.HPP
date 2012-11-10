// Import aus dem DXF-Format ------------------------------------
// File: DXFIMP.HPP

#if !defined(_DXFIMP_HPP)
#define _DXFIMP_HPP

class CImportAutoCadDxf;

class CImpDxfExtension : public CTriasExtension 
{
private:
    CImportAutoCadDxf *m_pIImport;       // ImportInterface

public:
    CImpDxfExtension (void);
    ~CImpDxfExtension (void);

	STDMETHOD (QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj);

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

	IUnknown *get_CS() const { return m_pIImport->get_CS(); }
};

#endif // _DXFIMP_HPP


