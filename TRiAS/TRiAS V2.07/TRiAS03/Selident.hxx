// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.HXX

#if !defined(_SELIDENT_HXX)
#define _SELIDENT_HXX

#include <selidlvc.hxx>
#include "propactb.hxx"	// JG 980915

typedef struct tagSELIDRESULT {
	LONG m_lIdent;
	short m_iOTyp;
} SELIDRESULT;

// Wrapper fürs automatische freigeben
class CCaSelIdResult 
{
public:
	void Tidy () 
	{ if (NULL != pElems) { CoTaskMemFree (pElems); pElems = NULL; } cElems = 0; }

// Datenmember
	ULONG cElems;
	SELIDRESULT *pElems;
	ULONG ulSelectFrom;

// notwendige Memberfunktionen
		CCaSelIdResult () 
		{ 
			ulSelectFrom = SELIDMODE_SINGLETYPE; 
			cElems = 0; 
			pElems = NULL; 
		}
		~CCaSelIdResult() { Tidy(); }
		
		CCaSelIdResult(const CCaSelIdResult &rToCopy) 
		{ 
			cElems = rToCopy.cElems; 
			if (0 != cElems) {
				pElems = (SELIDRESULT *)CoTaskMemAlloc (cElems*sizeof(SELIDRESULT)); 
				if (NULL == pElems) throw E_OUTOFMEMORY;
				memcpy (pElems, rToCopy.pElems, cElems*sizeof(SELIDRESULT));
			} else
				pElems = NULL;
		}
		CCaSelIdResult & operator = (const CCaSelIdResult &rToCopy)
		{ 
			Tidy();
			ulSelectFrom = rToCopy.ulSelectFrom;
			cElems = rToCopy.cElems; 
			if (0 != cElems) {
				pElems = (SELIDRESULT *)CoTaskMemAlloc (cElems*sizeof(SELIDRESULT)); 
				if (NULL == pElems) throw E_OUTOFMEMORY;
				memcpy (pElems, rToCopy.pElems, cElems*sizeof(SELIDRESULT));
			}
			return *this;
		}

	void SetData (ULONG ulCnt, SELIDRESULT *pSelIds)
	{
		Tidy();
		cElems = ulCnt;
		pElems = pSelIds;
	}
};

class CSelectIdentDlg 
	: public CPropertyPage,
	  public CPropertyActionExtUsage
{ 
private:
	DWORD m_dwFlags;
	CCaSelIdResult m_caSelIds;	// selektierte Einträge

	PushButton m_pbSelAll;
	CSelIdentListView *m_pIdents;

	class CSelIDPropAct *m_pParent;
	bool m_fResultPrepared;

	void AdjustOK (bool fDisableNext = false);

protected:
	void ButtonClick (ControlEvt);
	void WindowInit (Event);

	void OnItemChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);
	void OnClick (NotifyEvt);
	void HelpRequest(HelpRequestEvt);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp, int &riCnt);
	bool GetNextIdent (long &rlIdent, short &riOTyp, int &riCnt);

	int GetItemCount (void);
	int GetSelectedCount (void);

	bool PrepareResult (void);

// Konstruktor nicht direkt rufen
		CSelectIdentDlg (CSelIDPropAct *pParent, ResID uiRes, 
						 LPCSTR pcCaption);
	bool FInit (void);
	void SetDirty (bool fDirty = true);
		
// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	int SelectIdent (long lIdent, short iOTyp, bool fSel = true);

public:
// Destruktor/Initialisierung
		~CSelectIdentDlg (void);
		
static CSelectIdentDlg *CreateInstance (
			CSelIDPropAct *pParent, ResID resID, LPCSTR pcCaption);
	
// Fragt den Dialog nach seinen Daten 
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);

// Setzen und Abfragen der Dialoginformationen
	HRESULT GetSelectedInfo (CCaSelIdResult *pSelInfo);
	HRESULT SetSelectedInfo (CCaSelIdResult *pSelInfo, bool fNoShow = false);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
};


#endif // _SELIDENT_HXX

