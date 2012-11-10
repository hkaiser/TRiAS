// Klassendefinitionen fuer Identifikator-Baum ------------------------------------------
// File: RELKEY.HXX

#if !defined(_RELKEY_HXX)
#define _RELKEY_HXX

///////////////////////////////////////////////////////////////////////////////
// TRiAS - Objekte
class TR_OBJ 
{
private:
	string m_strKurzText;
	short _iTyp;
	
public:
// Konstruktor/Destruktor
	TR_OBJ (char const *pKurzText, short iTyp = 0);
	~TR_OBJ (void);

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetKText (void *pObj);
	friend int _XTENSN_EXPORT CmpKTexts (void *pObj1, void *pObj2);

	char const *KurzText() { return m_strKurzText.c_str(); }
	void SetTyp (short iTyp) { _iTyp = iTyp; }
};

class TR_OBJTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_OBJTree (void);
	~TR_OBJTree (void);
};
DeclareLock (TR_OBJTree, TR_OBJ);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////
// OKSKlassen
class TR_OKS
{
private:
	string m_strKey;
	string m_strWert;
	
public:
// Konstruktor/Destruktor
	TR_OKS (const char *pKey, const char *pWert);
	~TR_OKS (void);

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetOKS (void *pObj);
//	friend int _XTENSN_EXPORT CmpOKSs (void *pObj1, void *pObj2);

	char const *Wert() { return m_strWert.c_str(); }
	char const *Key() { return m_strKey.c_str(); }
	bool SetWert (const char *);
};

class TR_OKSTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_OKSTree (void);
	~TR_OKSTree (void);
};
DeclareLock (TR_OKSTree, TR_OKS);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////
// TRiAS - Objektklassen
class TR_Layer 
{
private:
	string m_strBNAText;
	string m_strKurzText[4];
	DWORD m_dwObjType;
	long _lIdent[4];

//	string m_strOKS;
//	bool _iAbgleich;
	bool m_fImportAttributes[4];

public:
// Konstruktor/Destruktor
	TR_Layer (const char *pBNAText, long lIdent, DWORD dwType, bool fImportAttributes);
	~TR_Layer();

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetLayer (void *pObj);
//	friend int _XTENSN_EXPORT CmpLayer (void *pObj1, void *pObj2);

	char const *KurzText(DWORD dwObjType) { return m_strKurzText[OTypToIndex(dwObjType)].c_str(); }
	char const *BNAText() { return m_strBNAText.c_str(); }
	long Ident(DWORD dwObjType) { return _lIdent[OTypToIndex(dwObjType)]; }

	int SetKurzText (DWORD dwObjType, const char *pKurzText, HPROJECT hPr);
	void ResetData (DWORD dwObjType) 
	{ 
	int iIndex = OTypToIndex(dwObjType);

		m_strKurzText[iIndex].erase(); 
		_lIdent[iIndex] = 0;
	} 

//	int SetOKS (const char *);
//	int SetIdent (long);
//	char const *OKS() { return m_strOKS.c_str(); }
//	int Abgleich() { return _iAbgleich; }

	void AddType (ULONG lIdent, DWORD dwType);
	DWORD GetTypes() { return m_dwObjType; }

	bool GetImportAttributes(DWORD dwType);
	void SetImportAttributes(bool fImportAttributes, DWORD dwType);

protected:
	static int OTypToIndex(DWORD dwObjType);
};

class TR_LayerTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_LayerTree (void);
	~TR_LayerTree (void);
};
DeclareLock (TR_LayerTree, TR_Layer);		// notwendige Klassendefinitionen

#endif // _RELKEY_HXX
