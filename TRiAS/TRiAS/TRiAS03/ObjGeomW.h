// Wrapper für OBJGEOMETRIE
// OBJGEOMW.H

#if !defined(_OBJGEOMW_H)
#define _OBJGEOMW_H

class CObjGeometrie :
	public OBJGEOMETRIE
{
protected:
	void Tidy (void);

public:
	CObjGeometrie (void);
	~CObjGeometrie (void);

	enum OBJGEOMSTATE {
		OBJGEOMSTATE_Uninitialized = 1,
		OBJGEOMSTATE_Initialized = 2,
		OBJGEOMSTATE_Filled = 3,
	};

	bool InitObjGeometrie (bool fIsInitialized);
	bool FillObjGeometrie (HOBJECT lONrToFill);
	bool CreateNewObject (HPROJECT hPr, HOBJECTS lNewIdent, bool fUndo = true);

	OBJGEOMETRIE &operator= (const OBJGEOMETRIE &rOG);

    HRESULT AreaToLine();
    HRESULT LineToArea();

private:
	OBJGEOMSTATE m_rgState;
};

#endif // _OBJGEOMW_H
