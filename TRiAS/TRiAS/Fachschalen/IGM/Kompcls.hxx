// FlaechenAuswahl ------------------------------------------------------
// File: KOMPCLS.HXX

#if !defined(_KOMPCLS_HXX)
#define _KOMPCLS_HXX

#include <tstring>

// ospace stl
#include <tstring>
#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>

#include <string.h>

// Definieren von FlaechenKlassenFenstern ---------------------
class TriasFlaechen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	bool _isValid;
	class CTop_ObjTree *_pObj;
	long *_lClassIdent;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		TriasFlaechen (pWindow pW, uint res, ResourceFile &RF, long lIdent );
		~TriasFlaechen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillObjClassList (long);
	long *FlaechenCls();
	void ErfasseObjKlasse (int);
};    
/////////////////////////////////////////////////////////////////
// Definieren von KlassenFenstern ---------------------
class AlleTRiASKlassen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	bool _isValid;
	long *_lClassIdent;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		AlleTRiASKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent , TR_OCLTree *);
		~AlleTRiASKlassen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillObjClassList (long, TR_OCLTree *);
	long *TRiASCls(void) { return _lClassIdent; };
	void ErfasseObjKlasse (int);
};    
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Datenquellen füllen
struct CCompareNoCase :
//	binary_function<CString, CString, bool>
	binary_function<string, string, bool>
{
//	bool operator()(const CString& _X, const CString& _Y) const
	bool operator()(const string& _X, const string& _Y) const
	{
		return _stricmp( _X.c_str(), _Y.c_str() ) < 0;
//		return _X.CompareNoCase(_Y) < 0;
	}
};

//typedef map<CString, pair<DWORD, HPROJECT>, CCompareNoCase> CComboEntryMap; 
//typedef map<long, os_string, less<long> > CObjectMap;

//typedef map<CString, long, CCompareNoCase> CObjectMap; 
typedef map<string, long, CCompareNoCase> CObjectMap; 

/////////////////////////////////////////////////////////////////
// Definieren von KlassenFenstern ---------------------
class TRiASRechercheKlassen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	MultiSelListBox _InClass;
	MultiSelListBox _InAusClass;
	long *_lClassIdent;
	long *_lObjIn;
	long *_lObjInAus;
	long _lONNew;
	bool _isValid;
	FixedText _InText,_InAusText;
	PushButton OKButton, CancelButton,_NewButton;
	ResourceFile &_RF;
	TR_IDMTree *_pIDM;
	pWindow _pW;
	CObjectMap m_InClass;
	CObjectMap m_InAusClass;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		TRiASRechercheKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent , TR_IDMTree *pIDM);
		~TRiASRechercheKlassen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	long *Obj(void) { return _lClassIdent; };
	long *ObjIn(void) { return _lObjIn; };
	long *ObjInAus(void) { return _lObjInAus; };
	long Objekt(void) { return _lONNew;};
	bool FillObjClassList (void);
	bool FillRechercheList(void);
	bool FillErgebnisListe(TR_IDOTree *, MultiSelListBox*, CObjectMap *);
	void ErfasseObjKlasse (int);
	void ErfasseInKlasse (int, CObjectMap *);
	void ErfasseInAusKlasse (int ,CObjectMap * );
};    
//-----------------------------------------------------------------------------
#endif	//KOMPCLS.HXX

