// Enumeration aller ObjektNummern einer gegebenen Liste ----------------------
// File: ENUMONR.HXX

#if !defined(_ENUMONR_HXX)
#define _ENUMONR_HXX

#include <ifndlong.h>
#include <triastlb.h>
#include <igeoobjs.h>

///////////////////////////////////////////////////////////////////////////////
// zusätzlich benötigte SmartIF's
#if !defined(_DEFINED_ENUMLONG)
#define _DEFINED_ENUMLONG
DefineSortingEnumerator(LONG);
DefineSmartEnumerator(LONG);
#endif // _DEFINED_ENUMLONG

///////////////////////////////////////////////////////////////////////////////
// BasisKlasse zur Enumeration von LONG's -------------------------------------
class CEnumObjectNumbers : 
	public SEnumLONG,
	public IFindLONG,
	public IPersistStreamInit,
	public IEnumObjectsByNumber,
	public IQueryGeoObjects,
	public CComObjectRoot,
	public CComCoClass<CEnumObjectNumbers, &CLSID_EnumObjectsByNumber>
{
private:
	bool		m_fIsInitialized;

public:
// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IPersistStream methods ***
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IPersistStreamInit methods ***
	STDMETHOD(InitNew)(THIS);

// *** IFindLONG specific members
	STDMETHOD(HasLONG) (THIS_ LONG lFind);

// *** IEnumObjectsByNumber members
	STDMETHOD(Next) (THIS_ ULONG celt, LONG *rgelt, ULONG *pceltFetched);
	STDMETHOD(Skip) (THIS_ ULONG dwSkip);
	STDMETHOD(Reset) (THIS);
	STDMETHOD(Clone) (THIS_ IEnumObjectsByNumber **ppenum);
	STDMETHOD(GetCount) (THIS_ ULONG *plCount);
	STDMETHOD(AddItem) (THIS_ LONG item);
	STDMETHOD(Clear) (THIS);

// *** IQueryGeoObjects specific functions ***
	STDMETHOD(GetGeoObjects) (THIS_ _DGeoObjects **ppIGeoObjs);

	BEGIN_COM_MAP(CEnumObjectNumbers)
		COM_INTERFACE_ENTRY2(IEnumLONG, IEnum<LONG>)
		COM_INTERFACE_ENTRY(IEnumObjectsByNumber)
		COM_INTERFACE_ENTRY(IFindLONG)
		COM_INTERFACE_ENTRY(IQueryGeoObjects)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CEnumObjectNumbers)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_ENUMOBJECTSBYNMUMBER)

protected:
	typedef SEnumLONG::cont_t CObjectNumbers;

// sonstige Funktionen
	bool FInit (void) { return true; }		// Initialisierungen

		CEnumObjectNumbers (void);	// nicht direkt rufen

public:
	void SetDirty (bool fDirty) { setdirty(fDirty); }
	bool GetDirty (void) { return isdirty(); }
	
	const CObjectNumbers &Objs (void) const { return m_data; }
	bool AddObject (LONG lONr);	// ObjektNummer hinzufügen

		~CEnumObjectNumbers (void) {}

static CComObject<CEnumObjectNumbers> *CreateInstance (void);

	void EveryDelete (void) { SEnumLONG::Clear(); }
};

#endif // _ENUMONR_HXX
