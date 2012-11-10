// Dialogfenster fuer die Auswahl von Objekteigenschaften ---------------------
// File: OBJPROP.HXX

#if !defined(_OBJPROP_HXX)
#define _OBJPROP_HXX

class ObjectProperty;
class ObjectPropertyCreator;
class ObjPropTree;

const short OBJPROPFUNCNAMELEN = _MAX_PATH;
const short OBJPROPFUNCHELPLEN = _MAX_PATH;

#define OBJPROP_DESTCLIPBOARD	1
#define OBJPROP_DESTWINDOW	2
#define OBJPROP_DESTMCODE	3

#define OBJPROP_DESTFILE	4
// die nachfolgenden Werte entsprechen verschiedenen DateiFormaten
#define OBJPROP_DESTFILE_OPR	4
#define OBJPROP_DESTFILE_CSV	5

#define OBJPROP_DESTFILE_LAST	10

#if defined(WIN32)
template<class T> class IEnum;
#endif

class ObjectPropertyDlg : public DialogWindow {
private:
#if !defined(WIN32)
	PushButton m_HelpButton;
#endif // WIN32
	PushButton m_SelectFile;
	PushButton m_OKButton;
	PushButton m_pbSortEntries;
	
	RadioButton m_ClipButton;
	RadioButton m_FileButton;
	RadioButton m_WindowButton;
	RadioButton m_MCodeButton;

	SingleLineEdit m_FileName;
	MultiSelListBox m_ObjProps;
	CheckBox m_HeadLine;
	CheckBox m_Cumulation;
	CheckBox m_Count;
	CheckBox m_ObjPropData;

	ComboBox m_MCodes;
	FixedText m_ftHelpText;

	ExtensionList &m_EL;
	ObjPropTree *m_pObjPropTree;

#if defined(WIN32)
	IEnum<LONG> *m_pObjEnum;
#else
	LPENUMLONG m_pObjEnum;
#endif

	Font *m_pFont;
	char *m_pBuff;
	int m_iFileType;
	unsigned short m_fFontChanged : 1;
			
	void AdjustControls (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditChange (ControlEvt);

	class ObjPropTree *ResortObjProps (ObjPropTree *pOPT);

	HRESULT ObjPropInitProgress (LPPROGRESSINDICATOR *ppIProgInd);

public:
#if defined(WIN32)
		ObjectPropertyDlg (pWindow, ExtensionList *, 
				   IEnum<LONG> *pIEnum = NULL, LONG lRefONr = 0L);
#else
		ObjectPropertyDlg (pWindow, ExtensionList *, 
				   LPENUMLONG = NULL, LONG lRefONr = 0L);
#endif // WIN32
		~ObjectPropertyDlg (void);

	bool GenerateObjProps (short iDest = OBJPROP_DESTCLIPBOARD, long lMCode = -1L);
	bool GenerateIntObjPropFunc (ObjectPropertyCreator &, const char *, 
				     const char *,INTOBJPROPPROC);
	bool GenerateIntObjPropFuncText (pWindow pW, ObjectPropertyCreator &, short);
	bool GenerateMCodeIntObjPropFuncs (ObjectPropertyCreator &);
};

#if defined(WIN32)

class ObjPropDestWindow : public DialogWindow {
private:
	CListViewCtrl m_Result;
	PushButton m_pbCopy;
	LPCSTR m_pcText;		// Verweis auf angezeigten Text

protected:
	void ButtonClick (ControlEvt);

	bool InitListViewCtrl (LPCSTR pcText, bool fHeadline);

public:
		ObjPropDestWindow (pWindow, LPCSTR, bool fHeadline);
		~ObjPropDestWindow (void);
};

#else

class ObjPropDestWindow : public DialogWindow {
private:
	MultiLineEdit m_Result;

protected:
	void ButtonClick (ControlEvt);

public:
		ObjPropDestWindow (pWindow, char *, bool fToLarge);
		~ObjPropDestWindow (void);
};
#endif // WIN32

class CSortEntryDlg : public DialogWindow {
private:
	ListBox m_lbEntries;
	ObjPropTree &m_rOPT;
	
protected:
	void ButtonClick (ControlEvt);
	
	void MoveEntry (bool fUp = true);
	
public:
		CSortEntryDlg (pWindow pW, ObjPropTree *pOPT);
		~CSortEntryDlg (void);

	bool FInit (void);
	ListBox &OPList (void) { return m_lbEntries; }
};

#include "queryfld.hxx"		// Eingabefeld-Dialog 

// Klassen für ObjFuncTree ----------------------------------------------------
class ObjectProperty {
private:
	char *m_pFName;
	bool m_isSel;
	short m_iOrd;
	
	ObjectProperty &operator = (ObjectProperty &);	// blocken

public:
		ObjectProperty (const char *pFunc);
		ObjectProperty (ObjectProperty &, short);
		
	virtual	~ObjectProperty (void);

virtual char *InvokeFunc (long lONr, char *pBuffer, short iLen) = 0;
virtual ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd = 0) = 0;
virtual char *GetHelpText (char *pBuffer, short iLen) = 0;

	char *& pFName (void) const { return (char *&)m_pFName; }
	bool isSel (void) { return m_isSel; }
	void SetSelection (bool newSel) { m_isSel = newSel; }
	short &FOrd (void) { return m_iOrd; }

friend void *GetObjPropKeyStr (void *);
friend void *GetObjPropKeyInt (void *);
};

// PropertyFunction einer Erweiterung -----------------------------------------
class ObjectPropertyExt : public ObjectProperty {
private:
	short m_iFuncID;
	Extension &m_Ext;

public:
		ObjectPropertyExt (const char *pFunc, short iID, Extension *pExt);
		ObjectPropertyExt (ObjectPropertyExt &, short);
		~ObjectPropertyExt (void);

	short iFuncID (void) { return m_iFuncID; }
	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	char *GetHelpText (char *pBuffer, short iLen);
	
	ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd);
};

// Interne, vordefinierte PropertyFunction ------------------------------------
class ObjectPropertyInt : public ObjectProperty {
private:
	INTOBJPROPPROC m_pFunc;
	char *m_pHText;

public:
		ObjectPropertyInt (const char *pFName, 
				   const char *pHText,
				   INTOBJPROPPROC pFunc);
		ObjectPropertyInt (ObjectPropertyInt &, short);
		~ObjectPropertyInt (void);

	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	char *GetHelpText (char *pBuffer, short iLen);

	ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd);
};

// Klasse für MerkmalsCodes ---------------------------------------------------
class MCodeObjectPropertyInt : public ObjectProperty {
private:
	long m_lMCode;

public:
		MCodeObjectPropertyInt (long lMCode);
		MCodeObjectPropertyInt (MCodeObjectPropertyInt &, short);
		~MCodeObjectPropertyInt (void);

	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	char *GetHelpText (char *pBuffer, short iLen);

	ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd);
};


// Objekteigenschaft für die Eingabe von zusätzlichen Feldern -----------------
class CQueryFieldPropertyInt : public ObjectProperty {
private:
	char *m_pFText;		// eigegebener Text
	bool m_fUseForAll;	// für alle Objekte nutzen
	pWindow m_pW;		// ParentWindow
	short m_iCnt;		// lfde Nummer des Eingabefeldes
	long m_lCnt;		// Anzahl der generierten ObjProps
	long m_lCum;		// kumulativer Index
		
public:
		CQueryFieldPropertyInt (pWindow pW, short iCnt);
		CQueryFieldPropertyInt (CQueryFieldPropertyInt &, short);
		~CQueryFieldPropertyInt (void);

	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	char *GetHelpText (char *pBuffer, short iLen);

	ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd);
};

class ObjPropTree : public CTree {
protected:
	void UserDelete (void *);

public:
		ObjPropTree (pGetKeyFcn, pKeyCmpFcn);
	virtual	~ObjPropTree (void);

	void SetAll (bool fFlag = false);
	void SetSelection (bool isSel, char *pFName);

	long SelCount (void);		// zählen der selektierten ObjProps
};
DeclareLock (ObjPropTree, ObjectProperty);


class ObjPropTreeStr : public ObjPropTree {
public:
		ObjPropTreeStr (void);
		~ObjPropTreeStr (void) {}
};


class ObjPropTreeInt : public ObjPropTree {
public:
		ObjPropTreeInt (void);
		~ObjPropTreeInt (void) {}
};

#endif // _OBJPROP_HXX
