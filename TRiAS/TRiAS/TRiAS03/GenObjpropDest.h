// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.10.2000 20:39:28 
//
// @doc
// @module GenObjPropDest.h | Declaration of the <c CGenObjPropDest> class

#if !defined(_GENOBJPROPDEST_H__0E7B6660_5810_40E5_8389_1D00ECEDC248__INCLUDED_)
#define _GENOBJPROPDEST_H__0E7B6660_5810_40E5_8389_1D00ECEDC248__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Basisklasse fürs generieren der Objekteigenschaften
class CGenObjPropDest
{
public:
// allgemeiner Wrapper um alles
	STDMETHOD(Begin)(ULONG ulExpectedCnt) PURE;	// vor dem ersten Objekt der ersten Objekteigenschaft
	STDMETHOD(End)() PURE;						// nach dem letzten Objekt der letzten Objekteigenschaft
	STDMETHOD(Cancel)() PURE;
	
// Funktionen für die Ausgabe der Objekteiegnschaften eines Objektes
	STDMETHOD(BeginObject)(INT_PTR lONr) PURE;
	STDMETHOD(ObjectProperty)(INT_PTR lONr, ULONG ulNumber, LPCSTR pcValue) PURE;
	STDMETHOD(EndObject)(INT_PTR lONr) PURE;

// Kopfzeile ausgeben
	STDMETHOD(BeginHeadline)() PURE;
	STDMETHOD(Headline)(ULONG ulNumber, LPCSTR pcValue) PURE;
	STDMETHOD(EndHeadline)() PURE;

// kumulativen Index ausgeben
	STDMETHOD(BeginCumulation)() PURE;
	STDMETHOD(Cumulation)(ULONG ulNumber, LPCSTR pcValue) PURE;
	STDMETHOD(EndCumulation)() PURE;

// Zähler ausgeben
	STDMETHOD(BeginCount)() PURE;
	STDMETHOD(Count)(ULONG ulNumber, LPCSTR pcValue) PURE;
	STDMETHOD(EndCount)() PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in eine Zeichenkette (Basisklasse für Andere)
class CGenObjPropString :
	public CGenObjPropDest
{
public:
	CGenObjPropString(bool fGenObjProp = true, char cDelimiter = '\t', 
			char *pcEol = "\r\n") :
		m_strText(""), m_ulMaxProps(0), m_cDelimiter(cDelimiter), 
		m_strEol(pcEol), m_fGenObjProp(fGenObjProp)
	{
#if defined(_DEBUG)
		m_lONr = 0;
#endif // defined(_DEBUG)
	}
	~CGenObjPropString() {}

// allgemeiner Wrapper um alles
	STDMETHODIMP Begin(ULONG ulExpectedCnt);
	STDMETHODIMP End();
	STDMETHODIMP Cancel();
	
// Funktionen für die Ausgabe der Objekteiegnschaften eines Objektes
	STDMETHODIMP BeginObject(INT_PTR lONr);
	STDMETHODIMP ObjectProperty(INT_PTR lONr, ULONG ulNumber, LPCSTR pcValue);
	STDMETHODIMP EndObject(INT_PTR lONr);

// Kopfzeile ausgeben
	STDMETHODIMP BeginHeadline();
	STDMETHODIMP Headline(ULONG ulNumber, LPCSTR pcValue);
	STDMETHODIMP EndHeadline();

// kumulativen Index ausgeben
	STDMETHODIMP BeginCumulation();
	STDMETHODIMP Cumulation(ULONG ulNumber, LPCSTR pcValue);
	STDMETHODIMP EndCumulation();

// Zähler ausgeben
	STDMETHODIMP BeginCount();
	STDMETHODIMP Count(ULONG ulNumber, LPCSTR pcValue);
	STDMETHODIMP EndCount();

// zusätzliche Funktionen
	void ResetText() { m_strText.erase(); }
	void AddText (LPCSTR pcToAdd)  { _ASSERTE(NULL != pcToAdd); m_strText += pcToAdd; }
	void AddText (char cToAdd) { m_strText += cToAdd; }
	void AddDelimiter() { AddText(m_cDelimiter); }

	ULONG GetExpectedCount() { return m_ulMaxProps; }
	char GetDelimiter() { return m_cDelimiter; }
	const char *GetText() { return m_strText.c_str(); }
	
protected:
	os_string m_strText;
	os_string m_strEol;
	ULONG m_ulMaxProps;
	char m_cDelimiter;

	bool m_fGenObjProp;

#if defined(_DEBUG)
	INT_PTR m_lONr;
#endif // defined(_DEBUG)
};

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in die Zwischenablage
class CGenObjPropClipboard :
	public CGenObjPropString
{
public:
	CGenObjPropClipboard(bool fGenObjProp) 
	:	CGenObjPropString(fGenObjProp) {}
	~CGenObjPropClipboard() {}

// Ausgabe ins Clipboard
	STDMETHODIMP End();
};

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in eine Datei
class CGenObjPropFile :
	public CGenObjPropString
{
public:
	CGenObjPropFile(LPCSTR pcFileName, char cDel, bool fGenObjProp) : 
		CGenObjPropString(fGenObjProp, cDel), m_strFile(pcFileName)
	{
	}
	~CGenObjPropFile() {}

// Ausgabe in Datei
	STDMETHODIMP End();
	STDMETHODIMP Headline(ULONG ulNumber, LPCSTR pcValue);

protected:	
	os_string m_strFile;		// Dateiname
};

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in eine Objekteigenschaft
DefineSmartInterface(ObjectProperty2);

class CGenWriteObjProp :
	public CGenObjPropString
{
public:
	CGenWriteObjProp(IObjectProperty *pIOP, char cDel, bool fOutputCount) :
		CGenObjPropString(true, cDel, ""), 
		m_ObjProp(pIOP), m_fOutputCount(fOutputCount)
	{
	}
	~CGenWriteObjProp() {}

// Ausgabe in Objekteigenschaft
	STDMETHODIMP BeginObject(INT_PTR lONr);
	STDMETHODIMP EndObject(INT_PTR lONr);

private:
	WObjectProperty2 m_ObjProp;
	bool m_fOutputCount;
};

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in ein Fenster
class CGenObjPropWindow :
	public CGenObjPropString
{
public:
	CGenObjPropWindow(HWND hWnd, LPCSTR pcCaption, Point &rPt, bool fHeadline, 
			bool fGenObjProp) :
		CGenObjPropString(fGenObjProp), m_hWnd(hWnd), m_strCaption(pcCaption), 
		m_ptPos(rPt), m_fHeadline(fHeadline),
		m_ulCnt(0)
	{
	}
	~CGenObjPropWindow() {}

// Ausgabe ins Fenster
	STDMETHODIMP Begin(ULONG ulExpectedCnt);
	STDMETHODIMP BeginHeadline();
	STDMETHODIMP BeginObject(INT_PTR lONr);
	STDMETHODIMP BeginCumulation();
	STDMETHODIMP BeginCount();
	STDMETHODIMP End();

private:
	HWND m_hWnd;
	os_string m_strCaption;
	Point m_ptPos;
	bool m_fHeadline;
	ULONG m_ulCnt;
};

#endif // !defined(_GENOBJPROPDEST_H__0E7B6660_5810_40E5_8389_1D00ECEDC248__INCLUDED_)
