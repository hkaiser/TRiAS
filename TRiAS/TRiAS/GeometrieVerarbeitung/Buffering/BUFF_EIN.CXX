// Eingaben für Buffering
// File: BUFF_EIN.CXX
// W. Mörtl


#include "bufferp.hxx"

#include "BufferR.h"		// IDE_BUFBREITE, ...

#include <TRiASHelper.h>	// IProgressIndicator2 in SmartInterfaces.h
#include "SmartInterfaces.h"

#include "koord.hxx"		// NumEditToDouble()


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// von allen selektierten (markierten) Objekten den Objekttyp bestimmen; dabei wird bei
// geschlossenen Kanten der Objekttyp "OTFlaeche" signalisiert
BOOL _BUFFER_EXPORT FAR PASCAL AlleObjektTypen (long lONr, BOOL, void* piAllOT)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (0 == lONr || -1 == lONr) return false;	// Objektnummer fehlerhaft

int iObjTyp = DEX_GetObjectType (lONr);

    	if (OT_PUNKT == iObjTyp)
    		*((int*)piAllOT) |= OTPunkt;
    	else if (OT_KANTE == iObjTyp)
		{
		// Test, ob Kante offen oder geschlossen ist
		WObjektGeometrie wObj;	// (Interface auf) Objektgeometrie des zu puffernden Objektes

			if (FAILED(CreateInterfaceOG (wObj.ppi(), lONr)))
				return false;

		long lCnt;
		KoOrd* plXK; KoOrd* plYK;

			wObj->GetCnt (&lCnt);
			wObj->GetX ((void**)&plXK);
			wObj->GetY ((void**)&plYK);

			if (plXK[0] != plXK[lCnt-1] || plYK[0] != plYK[lCnt-1])
    			*((int*)piAllOT) |= OTLinie;
			else	// Kante geschlossen
	    		*((int*)piAllOT) |= OTFlaeche;
		}
    	else if (OT_FLAECHE == iObjTyp)
    		*((int*)piAllOT) |= OTFlaeche;
    	else 
    	{
    		_ASSERTE (iObjTyp == OT_PUNKT || iObjTyp == OT_KANTE ||
					   iObjTyp == OT_FLAECHE);
    		return false;	// sonst nur weitermachen
    	}

	return true;
}



// --------------------------------------------------------------------------------------------
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)		// Ausschalten von uninteressanten Warnungen (wegen "this" im Konstruktor)
#endif
Parameter :: Parameter (pWindow pW, ResID res)
		   : DialogWindow (pW, res),
			 m_BufBreite (this, IDE_BUFBREITE),
			 m_BufAnzahl (this, IDE_BUFANZAHL),
			 m_PufferRBttn (this, IDR_PUFFER),
			 m_KreisRBttn (this, IDR_KREIS),
			 m_RingCBox (this, IDC_RING),
			 m_SpitzeRBttn (this, IDR_SPITZE),
			 m_FlachRBttn (this, IDR_FLACH),
			 m_BogenRBttn (this, IDR_KREISBOGEN),
			 m_Prompt (this, IDT_PROMPT),
			 m_KantenLaenge (this, IDE_KANTENLAENGE),
			 m_OKBttn (this, IDOK)
{
	_pW = pW;
	StandardWerte();
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
Parameter :: ~Parameter (void)
{
}


// --------------------------------------------------------------------------------------------
// Überprüfung der Parametereingabe
void _BUFFER_EXPORT Parameter :: EditChange (ControlEvt e)
{
double b;

	NumEditToDouble (&m_BufBreite, b);

int a = ParameterEinlesen (&m_BufAnzahl);
double kl = 1.;		// hier ist für den Enable/Disable-Test irgendein Wert > 0 notwendig

	if (BUFF_ARC == m_cmMode)
		NumEditToDouble (&m_KantenLaenge, kl);

	if (b != 0. && a > 0 && kl > 0.)
		m_OKBttn.Enable();	// OK-Button nur bei sinnvoller
	else					//  Parametereingabe freigeben
		m_OKBttn.Disable();

	if (m_bIntern)	// programm-interne Modifikation des Editierfeldes m_KantenLaenge
		return;

	// bei Veränderung der Pufferbreite gleich die Kantenlänge nachziehen
	if (IDE_BUFBREITE == (uint)e.GetControlID())
	{
		m_dPrec = dFacEdgeLen * fabs(b);
		m_bIntern = true;
		m_KantenLaenge.SetValue (m_dPrec);
		m_bIntern = false;
	}

	if (b >= 0.)
		m_KreisRBttn.Enable();
	else								// bei negativer Pufferbreite ...
	{
		m_KreisRBttn.Disable();			// ... keine Kreispuffer zulassen und
		m_PufferRBttn.SetState (true);	// Button für echten Puffer auswählen
		m_KreisRBttn.SetState (false);
		m_SpitzeRBttn.Enable();
		m_FlachRBttn.Enable();
		m_BogenRBttn.Enable();
		m_Prompt.Enable();
		m_KantenLaenge.Enable();
	}

} // EditChange


// --------------------------------------------------------------------------------------------
// Reaktion auf Button-Click
void _BUFFER_EXPORT Parameter :: ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDC_RING:
			if (m_RingCBox.isChecked())
			{
				m_PBau = PBAU_RING;
				m_PBauSave = PBAU_RING;
			}
			else
			{
				m_PBau = PBAU_VOLL;
				m_PBauSave = PBAU_VOLL;
			}
			break;

		case IDR_SPITZE:
			m_PBau = m_PBauSave;
			m_RingCBox.Enable();
			m_KantenLaenge.Disable();
			break;

		case IDR_FLACH:
			m_KantenLaenge.Disable();
			// bei OFFENEN Linienobjekten ist die Kombination flach-ringförmig nicht möglich,
			// weil sich am Linienanfang und -ende die Innenkontur mit der Außenkontur
			// überlappen würde
			if (m_iAllOT & OTLinie)
			{
				m_RingCBox.Disable();
				m_PBauSave = m_PBau;	// m_PBau-Wert zwischenspeichern
				m_PBau = PBAU_VOLL;
			}
			break;

		case IDR_KREISBOGEN:
			m_PBau = m_PBauSave;
			m_RingCBox.Enable();
			m_KantenLaenge.Enable();
			break;

		case IDR_PUFFER:
			m_SpitzeRBttn.Enable();
			m_FlachRBttn.Enable();
			m_BogenRBttn.Enable();
			m_Prompt.Enable();
			m_KantenLaenge.Enable();
			break;

		case IDR_KREIS:
			m_SpitzeRBttn.Disable();
			m_FlachRBttn.Disable();
			m_BogenRBttn.Disable();
			m_Prompt.Disable();
			m_KantenLaenge.Disable();
			break;

		case IDOK:
			NumEditToDouble (&m_BufBreite, m_dWidth);
			m_iPuffAnzahl = ParameterEinlesen (&m_BufAnzahl);

			_bTyp = m_PufferRBttn.GetState();

			if (m_SpitzeRBttn.GetState()) m_cmMode = BUFF_TIP;
			else if (m_FlachRBttn.GetState()) m_cmMode = BUFF_PLAIN;
			else m_cmMode = BUFF_ARC;
			NumEditToDouble (&m_KantenLaenge, m_dPrec);

			EndDlg (1);	// Eingabe der Parameter beenden
			break;

		case IDCANCEL:
			EndDlg (0);
			break;
	}

	if (PBAU_RING == m_PBau) m_RingCBox.SetChecked (true);
	else m_RingCBox.SetChecked (false);

} // ButtonClick


// --------------------------------------------------------------------------------------------
// Einlesen der Pufferparameter
int Parameter :: ParameterEinlesen (NumEditX* pEingWert)
{
	_ASSERTE (pEingWert != NULL);

int iRet = 0;

	if (pEingWert->GetTextLen() > 0)
	{
	char pcInBuff [20];

		pEingWert->GetText (pcInBuff, sizeof(pcInBuff));
		iRet = atoi (pcInBuff);
	}
	return iRet;

} // ParameterEinlesen


// --------------------------------------------------------------------------------------------
// Einstellung von Standardwerten
void Parameter :: StandardWerte (void)
{
// NumEditX initialiseren
	m_BufBreite.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_KantenLaenge.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_bIntern = false;

// Objektnummern aller selektierten (markierten) Objekte bereitstellen
ENUMLONGKEY ELK;	// Struktur für Enumeration mit einem long-Key (hier: alle selektierten
					// Objekte)
	m_iAllOT = 0;
    ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) AlleObjektTypen;	// zu rufende Funktion
	ELK.ePtr = (void*) &m_iAllOT;					// durchgereichte Daten
	DEX_EnumSelectedObjects (ELK);

	// wenn sich unter den zu puffernden Objekten auch Punkte befinden, dann nur kreisförmigen
	// Puffer zulassen
	if (m_iAllOT & OTPunkt)
	{
		 m_SpitzeRBttn.Disable();
		 m_FlachRBttn.Disable();
	}
	else
	{
		 m_SpitzeRBttn.Enable();
		 m_FlachRBttn.Enable();
	}

} // StandardWerte


// --------------------------------------------------------------------------------------------
// Funktionen für die Wiederherstellung der vorhergehenden Einstellung
void Parameter :: VorigeEinstellung (double dWidth, int iPuffAnzahl, bool bTyp, PuffBau PBau,
									 ConvexMode cmMode, double dPrec)
{
	_ASSERTE (dWidth != 0);
	_ASSERTE (iPuffAnzahl > 0);

	m_dWidth = dWidth;
	m_iPuffAnzahl = iPuffAnzahl;
	_bTyp = bTyp;
	m_PBau = PBau;
	m_PBauSave = PBau;
	m_cmMode = cmMode;
	m_dPrec = dPrec;
	
	m_BufBreite.SetValue (m_dWidth);
	m_BufAnzahl.SetValue (m_iPuffAnzahl);
	
	if (_bTyp) m_PufferRBttn.SetState (true);
	else m_KreisRBttn.SetState (true);

	if (BUFF_TIP == cmMode) m_SpitzeRBttn.SetState (true);
	else if (BUFF_PLAIN == cmMode) m_FlachRBttn.SetState (true);
	if (BUFF_ARC == cmMode) m_BogenRBttn.SetState (true);

	m_KantenLaenge.SetValue (m_dPrec);

	switch (cmMode)
	{
		case BUFF_TIP:
			m_RingCBox.Enable();
//			m_PBau = m_PBauSave;
			m_KantenLaenge.Disable();
			break;

		case BUFF_PLAIN:
			m_KantenLaenge.Disable();
			if (m_iAllOT & OTLinie)
			{
				m_RingCBox.Disable();
				m_RingCBox.SetChecked (false);
//				m_PBauSave = m_PBau;	// m_PBau-Wert zwischenspeichern
//				m_PBau = PBAU_VOLL;
			}
			break;

		case BUFF_ARC:
			m_RingCBox.Enable();
//			m_PBau = m_PBauSave;
			m_KantenLaenge.Enable();
			break;

		default:
			_ASSERTE (false);

//			m_PBau = PBAU_VOLL;
	}

	if (PBAU_RING == m_PBau) m_RingCBox.SetChecked (true);
	else m_RingCBox.SetChecked (false);

	m_BufBreite.SetFocus();	 // 1. Eingabestelle soll bei BufBreite sein

} // VorigeEinstellung
