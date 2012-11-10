// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.06.99 22:53:05 
//
// @doc
// @module Objprop.hxx | Ausgabe von Objekteigenschaften

#if !defined(_OBJPROP_HXX__45F965D0_2CD2_11D3_94F6_0080C786297B__INCLUDED_)
#define _OBJPROP_HXX__45F965D0_2CD2_11D3_94F6_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_FORCE_LEGACY_CODE)

#include <bmpbtn.hxx>

class ObjectProperty;
class ObjectPropertyCreator;
class ObjPropTree;

const short OBJPROPFUNCNAMELEN = _MAX_PATH;
const short OBJPROPFUNCHELPLEN = _MAX_PATH;

#define OBJPROP_DESTCLIPBOARD	1
#define OBJPROP_DESTWINDOW		2
#define OBJPROP_DESTMCODE		3

// die nachfolgenden Werte entsprechen verschiedenen DateiFormaten
#define OBJPROP_DESTFILE		4
#define OBJPROP_DESTFILE_OPR	4
#define OBJPROP_DESTFILE_CSV	5

#define OBJPROP_DESTFILE_LAST	10

template<class T> class IEnum;
DefineSmartInterface(ObjectProperty);

class ObjectPropertyDlg : 
	public DialogWindow 
{
private:
	PushButton m_SelectFile;
	PushButton m_OKButton;
	PushButton m_pbSortEntries;
	PushButton m_pbConfigProp;
	
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

	IEnum<LONG> *m_pObjEnum;

	char *m_pBuff;
	int m_iFileType;

#if defined(ENABLE_WIN32S_CODE)
	pFont m_pFont;
	unsigned short m_fFontChanged : 1;
#endif // ENABLE_WIN32S_CODE
			
	void AdjustControls (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditChange (ControlEvt);

	class ObjPropTree *ResortObjProps (ObjPropTree *pOPT);

	HRESULT ObjPropInitProgress (LPPROGRESSINDICATOR *ppIProgInd);

public:
		ObjectPropertyDlg (pWindow pW, ExtensionList *pEL, IEnum<LONG> *pIEnum = NULL, LONG lRefONr = 0L);
		~ObjectPropertyDlg (void);

	bool GenerateObjProps (short iDest = OBJPROP_DESTCLIPBOARD, long lMCode = -1L);
};

class ObjPropDestWindow : 
	public DialogWindow 
{
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

class CSortEntryDlg : 
	public DialogWindow 
{
private:
	ListBox m_lbEntries;
	ObjPropTree &m_rOPT;
	CBmpButton m_pbUp;
	CBmpButton m_pbDown;
	
protected:
	void ButtonClick (ControlEvt);
	BOOL DrawEntireItem (DrawItemEvt e);
	BOOL DrawItemFocus (DrawItemEvt e);
	BOOL DrawItemSelect (DrawItemEvt e);
	
	void MoveEntry (bool fUp = true);
	
public:
		CSortEntryDlg (pWindow pW, ObjPropTree *pOPT);
		~CSortEntryDlg (void);

	bool FInit (void);
	ListBox &OPList (void) { return m_lbEntries; }
};

///////////////////////////////////////////////////////////////////////////////
// Klassen für ObjFuncTree 
class ObjectProperty 
{
private:
	WObjectProperty m_ObjProp;
	os_string m_strName;
	bool m_isSel;
	short m_iOrd;
	
	ObjectProperty &operator = (ObjectProperty &);	// blocken

public:
	ObjectProperty (IObjectProperty *pIObjProp);
	ObjectProperty (ObjectProperty &rOP, short iOrd);
	
	~ObjectProperty (void);

	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	ObjectProperty *Insert (class ObjectPropertyCreator &, short iOrd = 0);
	char *GetHelpText (char *pBuffer, short iLen);

	const char *pFName (void);
	bool isSel (void) { return m_isSel; }
	void SetSelection (bool newSel) { m_isSel = newSel; }
	short &FOrd (void) { return m_iOrd; }

	bool CanConfig();
	HRESULT ConfigProperty (Window *pWindow);

	friend void *GetObjPropKeyStr (void *);
	friend void *GetObjPropKeyInt (void *);
};

class ObjPropTree : 
	public CTree 
{
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


class ObjPropTreeStr : 
	public ObjPropTree 
{
public:
		ObjPropTreeStr (void);
		~ObjPropTreeStr (void) {}
};


class ObjPropTreeInt : 
	public ObjPropTree 
{
public:
		ObjPropTreeInt (void);
		~ObjPropTreeInt (void) {}
};

#endif // defined(_FORCE_LEGACY_CODE)

#endif // !defined(_OBJPROP_HXX__45F965D0_2CD2_11D3_94F6_0080C786297B__INCLUDED_)
