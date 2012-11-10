// ArrayContainer, der die Idents einer GeoObjs Collection hält -------------
// File: OBJARRAY.HXX

#if !defined(_OBJARRAY_HXX)
#define _OBJARRAY_HXX

class CGeoObject;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CGeoObjArrayBase;
typedef CRing CGeoObjArrayRing;
typedef CSyncThread CGeoObjArraySync;
typedef CLock CGeoObjectLock;
#else
typedef container_wrappers::CArrayOnStl<CGeoObject *> CGeoObjArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CGeoObjArray : 
	public CGeoObjArrayBase 
{
private:
	INITOBJCOLLECTIONPROC m_pICProc;

protected:
	void UserDelete (void *);
	
public:
		 CGeoObjArray (void);
		~CGeoObjArray (void) { EveryDelete(); }
		
static CGeoObjArray *CreateInstance (LPUNKNOWN pUnk, 
									 CTriasApp *pApp, 
									 CGeoDoc *pDoc,
									 INITOBJCOLLECTIONPROC pICProc, 
									 DWORD dwData);
	BOOL FInit (void);

	CGeoObjArray *Copy (void);	// Array kopieren
	
// sonstige Member
	LONG Value (LONG lIndex);		// liefert Ident eines Elements
	LONG Value (LPCSTR bstrName);	// liefert Ident über KurzText
	long hasObject (LONG lONr);		// returns valid index

	HRESULT GetObjectDisp (long lIndex, LPVOID *ppDisp);
	HRESULT GetObjectDisp (LPCSTR pObStr, LPVOID *ppDisp); 
	HRESULT GetObjectDispValue (LONG lONr, LPVOID *ppDisp);
	HRESULT Refresh();

	CGeoObject *GetGeoObject (LONG lONr);
	bool DeleteObject (LONG lONr);
	HOBJECT *GetObjectsAsArray (void);

	ULONG Count (void);			// returns number of valid GeoObjects
	HRESULT GetEnumLONG (IEnumLONG **pIEnum);		// IEnumLONG liefern
};

DeclareLockStl (CGeoObjArray, CGeoObject);

#endif // _OBJARRAY_HXX
