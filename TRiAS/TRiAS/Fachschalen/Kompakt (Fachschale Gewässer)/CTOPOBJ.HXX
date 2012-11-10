// Klasse, die zu einem Flächenobjekt alle innenliegenden Objekte 
// einer vorgegeben Klasse liefert ------------------------
// File: CTOPOBJ.HXX

#if !defined(_CTOPOBJ_HXX)
#define _CTOPOBJ_HXX


class CTopObject {
private:
	OBJSTATISTIK m_osObj;	
	long * m_pOBJ;
	long * m_pInnen;
	long * m_pInMod;
	long * m_pOriginal;
	long ** _ppInnen;
	long ** _ppInAus;
	unsigned int m_fInitialized : 1;
	pWindow _pW;

//------Interface----------------------------

	IExtendTopRel2 * m_ifTop;
	IExtendObjOper * m_ifObjOp;

//protected:
//	bool FInit (void);

public:

	CTopObject (LONG lONr, long *pOBJ, long **ppInnen, long **ppInAus);
	virtual	~CTopObject (void);
	bool FInit (void);

	bool isObjOper ( void );
	bool isTopoRel ( void );
	void SetWindowHandle(pWindow);
	long * FlaechenTeile(void);
	long * LinienTeile ( void );
	long * ErgebnisVektor ( void );
	long * ZuModifizieren ( void ) { return m_pOriginal; };
	bool TopologieTest ( long, short);
	bool ObjektOperation ( long, short);
	bool SetPBDMCode ( ulong, IEnumLONG *);
	void SetObjektWert ( long, ulong );
};

// sonstige Funktionen --------------------------------------------------------
bool isSelected (HWND hWnd, LONG lONr);	// ist Objekt in ORFenster selektiert ?

#endif // _CTOPOBJ_HXX
