// Enumeration aller ObjektNummern einer gegebenen Liste ----------------------
// File: ENUMONR.HXX

#if !defined(_ENUMONR_HXX)
#define _ENUMONR_HXX

#include <iterenum.h>

///////////////////////////////////////////////////////////////////////////////
// zusätzlich benötigte SmartIF's
DefineSortingEnumerator(LONG);
DefineSmartEnumerator(LONG);

///////////////////////////////////////////////////////////////////////////////
// BasisKlasse zur Enumeration von LONG's -------------------------------------
class CEnumObjectNumbers : public SEnumLONG {
private:
	bool 		m_fIsDirty;

	class CPersistEnumLONG : public IPersistStream {
	friend class CEnumObjectNumbers;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CEnumObjectNumbers *m_pEnum;

	public:
			CPersistEnumLONG (IUnknown *pIUnk, CEnumObjectNumbers *pEnum);
			~CPersistEnumLONG (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IPersist methods ***
		STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

	// *** IPersistStream methods ***
		STDMETHOD(IsDirty)(THIS);
		STDMETHOD(Load)(THIS_ IStream *pStm);
		STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
		STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);
	};
	CPersistEnumLONG m_Persist;

protected:
	typedef SEnumLONG::cont_t CObjectNumbers;
	
// sonstige Funktionen
	bool FInit (void) { return true; }		// Initialisierungen

		CEnumObjectNumbers (void);	// nicht direkt rufen

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);

	void SetDirty (bool fDirty) { m_fIsDirty = fDirty ? true : false; }
	bool GetDirty (void) { return m_fIsDirty ? true : false; }
	
	const CObjectNumbers &Objs (void) const { return m_data; }
	bool AddObject (LONG lONr);	// ObjektNummer hinzufügen

		~CEnumObjectNumbers (void) {}

static CEnumObjectNumbers *CreateInstance (void);

	void EveryDelete (void) { Clear(); }
};

#endif // _ENUMONR_HXX
