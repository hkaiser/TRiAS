// Klassen für ObjFuncTree ----------------------------------------------------
// File: OBJPROPT.HXX

#if !defined(_OBJPROPT_HXX)
#define _OBJPROPT_HXX

// Basisklasse für alle Objektproperties --------------------------------------
class CImpObjectProperty : public IObjectPropery {
private:
	char *m_pFName;

public:
		CObjectProperty (const char *pFunc);
	virtual	~CObjectProperty (void);

// InterfaceMethoden
	
	LPSTR Name (LPSTR pBuffer, WORD wLen);
virtual LPSTR InvokeFunc (LONG lONr, LPSTR pBuffer, WORD wLen) = 0;

// Funktionen für den Tree
	char *& pFName (void) const { return m_pFName; }

friend void *GetObjPropKey (void *);
};

// PropertyFunction einer Erweiterung -----------------------------------------
class CObjectPropertyExt : public CImpObjectProperty {
private:
	short m_iFuncID;
	Extension &m_Ext;

public:
		CObjectPropertyExt (const char *pFunc, short iID, Extension *pExt);
		~CObjectPropertyExt (void);

	short iFuncID (void) { return m_iFuncID; }

// Interface
	LPSTR InvokeFunc (LONG lONr, LPSTR pBuffer, WORD wLen);
};

// Interne, vordefinierte PropertyFunction ------------------------------------
class CObjectPropertyInt : public CImpObjectProperty {
private:
	INTOBJPROPPROC m_pFunc;

public:
		CObjectPropertyInt (const char *pFunc, INTOBJPROPPROC pFunc);
		~CObjectPropertyInt (void);

// Interface
	LPSTR InvokeFunc (LONG lONr, LPSTR pBuffer, WORD wLen);
};

// Klasse für MerkmalsCodes ---------------------------------------------------
class CMCodeObjectPropertyInt : public CImpObjectProperty {
private:
	long m_lMCode;

public:
		CMCodeObjectPropertyInt (long lMCode);
		~CMCodeObjectPropertyInt (void);

// Interface
	LPSTR InvokeFunc (LONG lONr, LPSTR pBuffer, WORD wLen);
};


// Baum enthält alle im System gegenwärtig verfügbaren ObjectProperties -------
class CObjPropTree : public Tree {
protected:
	void UserDelete (void *);

public:
		CObjPropTree (void);
		~CObjPropTree (void);

	void ResetAll (void);
	void SetSelection (Bool isSel, char *pFName);
};
DeclareLock (ObjPropTree, ObjectProperty);

// Enumerator für ObjectProperties mit erweiterten Möglichkeiten (suchen) -----
class CImpEnumObjProp : public IEnumObjProp {

};


#endif // _OBJPROPT_HXX
