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

	bool InitObjGeometrie (bool fIsInitialized);
	bool FillObjGeometrie (long lONrToFill);

	OBJGEOMETRIE &operator= (const OBJGEOMETRIE &rOG);
};

#endif // _OBJGEOMW_H
