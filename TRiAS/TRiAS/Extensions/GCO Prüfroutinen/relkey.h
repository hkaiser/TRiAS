// Klassendefinitionen fuer Strassen-Baum ------------------------------------------
// File: RELKEY.HXX

#if !defined(_RELKEY_H)
#define _RELKEY_H

#include <containr.hxx>

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
class TR_OBJECTS
{
private:
	long m_lONr;
	int m_iErrorCode;
	bool m_bUnDef;
	
public:
// Konstruktor/Destruktor
	TR_OBJECTS (long lONr,int iErr);
	~TR_OBJECTS (void);

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetObjects (void *pObj);
	friend int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2);

	int ErrorCode(void) { return m_iErrorCode; }
	long &Object(void) { return m_lONr; }
	void SetUnDef(void) { m_bUnDef = true; }
	bool GetUnDef ( void) { return m_bUnDef; }
};

class TR_ObjTree : public CTree  
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_ObjTree (void);
	~TR_ObjTree (void);
};
DeclareLock (TR_ObjTree, TR_OBJECTS);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// StrassenKlassen
class TR_STREETS
{
private:
	string m_strKey;
	string m_strWert;
	long m_lONr;
	int m_iErrorCode;
//	long  *m_pDuplObjects;
	TR_ObjTree *m_pDupObj;
	
public:
// Konstruktor/Destruktor
	TR_STREETS (const char *pKey, const char *pWert, int lErrorCode, long lONr);
	~TR_STREETS (void);

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetStreets (void *pObj);

	char const *Wert(void) { return m_strWert.c_str(); }
	char const *Key(void) { return m_strKey.c_str(); }
	int ErrorCode(void) { return m_iErrorCode; }
	long Object(void) { return m_lONr; }

//	long *GetObjects(void) { return m_pDuplObjects; }

	TR_ObjTree *GetDupObj(void) { return m_pDupObj; }

	bool SetWert (const char *);
	void SetErrorCode (int iErrorCode) { m_iErrorCode = iErrorCode;}
	void SetObject(long lONr) { m_lONr = lONr; }
	bool AddObject(long lONr, int iErr);
};
//-----------------------------------------------------------------------------------------------------
class TR_STREETSTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_STREETSTree (void);
	~TR_STREETSTree (void);
};
DeclareLock (TR_STREETSTree, TR_STREETS);		// notwendige Klassendefinitionen

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// PunktWolken
class TR_MESH
{
private:
	string m_strKey;
	string m_strGlobalKey;
	long m_lONr;

	TR_ObjTree *m_pObj;
	
public:
// Konstruktor/Destruktor
	TR_MESH (const char *pKey, long lONr);
	~TR_MESH (void);

// ZugriffsFunktionen für OBJBaum
	friend void _XTENSN_EXPORT *GetMesh (void *pObj);

	char const *GlobalKey(void) { return m_strGlobalKey.c_str(); }
	char const *Key(void) { return m_strKey.c_str(); }
	long Object(void) { return m_lONr; }
	bool AddObject(long lONr);


	TR_ObjTree *GetObj(void) { return m_pObj; }

};
//-----------------------------------------------------------------------------------------------------
class TR_MESHTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	TR_MESHTree (void);
	~TR_MESHTree (void);
};
DeclareLock (TR_MESHTree, TR_MESH);		// notwendige Klassendefinitionen

///////////////////////////////////////////////////////////////////////////////////////////////////////
class CObjectPipe 
{
private:
	long m_lONr;
	string m_strLinkFeature;
	string m_strKey;
	int m_isValid;
	short m_iTyp;
	int m_iVar;
	int m_iIndex;
	
public:
// Konstruktor/Destruktor
	CObjectPipe (long lONr, string sLink, int iVar, int iIndex);
	~CObjectPipe (void);

	void FInit(void);
	void FInitTyp(void);
	void FInitGCS(void);

	string Key() { return m_strKey; }
	int isValid(void) { return m_isValid; }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class CObjectDefine 
{
private:
	long m_lONr;
	HPROJECT m_hPr;
	string m_strGuid;
	string m_strLinkFeature;
	string m_strOriginal;
	string m_strGCS;
	string m_strName;
	int m_iErrorCode;
	int m_iDlgCode;
	int m_isValid;
	short m_iTyp;
	
public:
// Konstruktor/Destruktor
	CObjectDefine (long lONr, int Code , string sLink, string sOriginal);
	~CObjectDefine (void);

	void FInit(void);
	void FInitTyp(void);
	void FInitGCS(void);
	void FInitGuid(void);
	short SetGCSErrorCode (const char *pC);
	bool SetEnumGCSErrorCode( const char *strGCS);
	bool ControlIsAlpha(const char *pGCSCode);
	bool FindOriginalCode (int *);

	long Object() { return m_lONr; }
	int ErrorCode() { return m_iErrorCode; }
	string Guid() { return m_strGuid; }
	string GCS() { return m_strGCS; }
	string Name() { return m_strName; }
	short Typ() { return m_iTyp; }
	int isValid(void) { return m_isValid; }
};
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

class CObjectStatus
{
private:
	long m_lONr;
	int m_iErrorCode;
	int m_isValid;
	short m_iTyp;
	CComBSTR m_bstrError;
	
public:
// Konstruktor/Destruktor
	CObjectStatus (long lONr, CComBSTR m_bstrError);
	~CObjectStatus (void);

	void FInit(void);

	long Object() { return m_lONr; }
	int ErrorCode() { return m_iErrorCode; }
	short Typ() { return m_iTyp; }
	int isValid(void) { return m_isValid; }
};
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

class CLineStatus
{
private:
	long m_lONr;
	long m_lIdent;
	int m_iErrorCode;
	int m_iError;
	int m_isValid;
	short m_iTyp;
	CComBSTR m_bstrErrorKey;
	
public:
// Konstruktor/Destruktor
	CLineStatus (long lONr, int iError, CComBSTR m_bstrErrorKey);
	~CLineStatus (void);

	void FInit(void);

	long Object() { return m_lONr; }
	long Ident() { return m_lIdent; }
	int ErrorCode() { return m_iError; }
	short Typ() { return m_iTyp; }
	int isValid(void) { return m_isValid; }
	void SelectLineObject (void) ;
	void GetNotControl (void); 
	void GetControlFeature (void); 
	bool GetControlIntern (void); 
	bool GetFeature ( char *pText);
	bool GetInternFeature ( char *pText);
	bool LineInternFeature ( char *pText);


};
//////////////////////////////////////////////////////////////////


#endif // _RELKEY_H
