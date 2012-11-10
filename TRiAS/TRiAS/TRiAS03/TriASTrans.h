// 
// TRiAS-TransaktionManagement
//
// Prog. : JG  TRiAS GmbH
// Start : 980918
// 
// Klasse zur Automatisierung von Transaktionen im TRiAS (Exceptionsafe)
// Start der Transaktion: Constructor mit Text(sonst Text = "Transaktion")
// Ende über End
// Abbruch über Destruktor / Break

#ifndef _TRIAS_TRANSACTIONS_MANAGEMENT_CLASS_980918
#define _TRIAS_TRANSACTIONS_MANAGEMENT_CLASS_980918

#include <ospace\std\memory>
					// den VC-Standard Auto_ptr nehmen
					// bei Bedarf auf ospace auto_ptr umschalten

// Textpuffergröße
const int NAMEBUFFERSIZE = 1024;	

class TRiASTransaktion
{
private:
	bool  m_bStarted;				// Flag : Transaktion läuft ?

	static long instcount;			// ein Static der die Anzahl der Klasseninstancen zählt

public:
	explicit TRiASTransaktion(const char* pcName = NULL)
	{
	// es läuft ja noch nichts
		m_bStarted = false;

	// einen leeren Text initialisieren
	char strNameBuffer[NAMEBUFFERSIZE];

		strNameBuffer[0] = '\0';

	// pcName kann ab hier ohne NULL Vergleich benutzt werden
		if (NULL == pcName)
			pcName = strNameBuffer;

		++instcount;	// damit jede derartige Transaction eine eigene Nummer hat(rein formell)

	// wenn kein Name, dann einen eigenen Namen erzeugen
		if (0 == strlen (pcName)) {
			wsprintf (strNameBuffer, g_cbTransaktion, instcount);
			pcName = strNameBuffer;
		}
		
	// und jetzt rein ins Vergnügen
		DEX_BeginUndoLevel(pcName);
		m_bStarted = true;
	}
	~TRiASTransaktion()
	{
	// wenn out of scope und nicht explizit beendet, dann rückgängig machen
	// entspricht dem Vorgehen bei Exceptionhandling
		Break();
	}

// Transaktion beenden
	HRESULT End()
	{
		// nur wenn gestartet
		if (m_bStarted)	{
			DEX_EndUndoLevel();
			m_bStarted = false;
		}
		return S_OK;	// evtl. noch differenzieren (aber wozu?)
	}
	// Transaktion abbrechen
	HRESULT Break()
	{
		// nur wenn gestartet
		if (m_bStarted)	{
			DEX_CancelUndoLevel(true);
			m_bStarted = false;
		}
		return S_OK;	// evtl. noch differenzieren (aber wozu?)
	}
};

typedef	auto_ptr<TRiASTransaktion> LPTRIASTRANSAKTION;

#endif // _TRIAS_TRANSACTIONS_MANAGEMENT_CLASS_980918