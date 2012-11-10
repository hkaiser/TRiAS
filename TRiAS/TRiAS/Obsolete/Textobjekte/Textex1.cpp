// Rudimente, die minimale Funktionsfaehigkeit einer Erweiterungs-DLL
// demonstrieren
// File: TEXTEX1.CPP

#include "stdafx.h"

#include <xtsnguid.h>

#ifdef WIN32
#include <olectlid.h>
#include <initguid.h>
#else // WIN32
#include <olectlid.h>
#include <initguid.h>
#endif // WIN32

#include "textguid.h"

#include "resource.h"
#include "textdlg.h"      // Klasse für Dialogfenster
#include "iterator.hpp"    // Klasse für Iteration
#include "txtredlg.h"      // Klasse für Recherchedialogfenster
#include "dlgabh.h"         // Klasse für Dlg. zum Abhängen der Textobjekte 
#include "igentext.h"
#include "helper.h"
#include "textp.h"
/************************************************************************************************/
// Diese Klasse ist von einer allgemeinen Basisklasse abgeleitet und hat eigenen ClassID.
// Zusätzlich bietet diese Klasse ein programmierbares Interface mit Grundfunktionalitaet 
// (Textobjekte erzeugen, loeschen) und InterfaceID an. Neben diesem Interface 
// hat diese  Klasse natuerlich ein IUnknownInterface bzw. IExtensionInterface mit fuer alle
// anderen Extensions gleichen InterfaceID, da ueber die Basisklasse gleiche Funktíonen aller
// Extensionen angeboten werden (InitExtension, UnloadExtension ...).
/*************************************************************************************************/

CHelper *g_pHelper;
extern BOOL g_bTrace, g_bTrace1, g_bTrace2;

CTextExt *g_pTextExt;
// extern "C"
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
CTriasExtension *NewExtension (void)
{
	return new CTextExt ();
}

// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_TextExtension, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.TextExtension.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_TextExtension, 
				TEXT("TRiAS.TextExtension.1"), IDS_LONGCLASSNAME,
				TEXTEXT_MAJORVERSION, TEXTEXT_MINORVERSION,
				EFUnLoadable|EFVisible|EFUnLoadable);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_TextExtension, 
					      TEXT("TRiAS.TextExtension.1"));
	}

return true;	// alles ok
}


// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuängeneden Menu's übergeben bekommt.
#pragma warning (disable: 4355)

CTextExt :: CTextExt (void)
	      : CTriasExtension (IDR_HMENU,IDR_ORMENU)	      
{                                 
	m_pHelper = new CHelper (this);  
	ASSERT( m_pHelper != NULL);
	m_pTextPro = new CTextPro (this, m_pHelper);
	ASSERT( m_pTextPro != NULL);
	m_dwRefCnt = 0;
	m_hWnd = 0;
	m_hMenu = 0;
	g_pTextExt = this;
	g_pHelper = m_pHelper;
}

#pragma warning (default: 4355)

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
// Destruktor -----------------------------------------------------------------
CTextExt :: ~CTextExt (void) 
{                          
	delete(m_pTextPro);
	delete(m_pHelper);
	// nothing to do
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen. Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CTextExt :: InitExtension (short iMode)
{                 
int i;
	i=0;
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

return true;
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CTextExt :: UnLoadExtension (void)
{
	return CTriasExtension :: UnLoadExtension();
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(bool) CTextExt :: MenuCommand (WPARAM MenuItemID, HWND hWnd)
{
m_hWnd = hWnd;
char cGeo;  

	switch (MenuItemID) 
	{	
	case IDM_CHOICE:		// (s. TEMPLATE.H)
		{
	        CTextDlg dlg (MWind (), m_pHelper);					  
			if (dlg.DoModal() == IDOK)// Aufruf des modalen Dialogfensters
				{
				DEX_RePaint();	
				return TRUE;
				}
		}
		break;
		
	case  IDM_OBRECH:	
		{
			CTxtReDlg redlg (MWind (), m_hWnd, m_hMenu, m_pHelper);
			if (redlg.DoModal() == IDOK)// Aufruf des Recherchefensters
				{
				DEX_RePaint();
				return TRUE;
				}
		}
		break;
		
	case IDM_OBABH:
		{
			CDlgAbh abdlg (MWind (), m_pHelper);
			if (abdlg.DoModal() == IDOK)
			{
				DEX_RePaint();
				return TRUE;
			}
		}
		break;       
		
	case IDM_OBREABH:
		{
			cGeo = '0';
			m_pHelper -> AbhaengTextObj ( m_hWnd, 0, FALSE, &cGeo);
			DEX_RePaint(); 
			return TRUE;
		}
		break;
	case IDM_ORLOESCH:
		{
			cGeo = '0';
			m_pHelper -> AbhaengTextObj ( m_hWnd, 0, TRUE, &cGeo);
			DEX_RePaint();
			return TRUE;
		}
		break;
	}
return FALSE;
}


STDMETHODIMP_(bool) CTextExt :: MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
m_hWnd = hWnd;
m_hMenu = hMenu;
short iType = 0;  

if (m_hWnd != 0) {
/*    
short iCnt = 0;                        
	ELK.eKey = (DWORD)(void *)m_hWnd;
	ELK.eFcn = (ENUMLONGKEYPROC) EnumSelObjectsFuerMenue;// alle selektierten Objekte
	ELK.ePtr = (void*)&iCnt;
		
	if (!DEX_EnumSelectedObjects(ELK)) return FALSE; 	if (iCnt > 0) 
*/

	DEXOR_QuerySelectedObjectTypes (m_hWnd, iType);

	if ( iType & OTText ) {
		EnableMenuItem (m_hMenu, UINT(IDM_OBRECH+MenuOffset()), MF_GRAYED);			
		EnableMenuItem (m_hMenu, UINT(IDM_OBREABH+MenuOffset()), MF_GRAYED);			
		EnableMenuItem (m_hMenu, UINT(IDM_ORLOESCH+MenuOffset()), MF_GRAYED);			
	}                                                                           
	else {
		EnableMenuItem (m_hMenu, UINT(IDM_OBRECH+MenuOffset()), MF_ENABLED);	
		EnableMenuItem (m_hMenu, UINT(IDM_OBREABH+MenuOffset()), MF_ENABLED);
		EnableMenuItem (m_hMenu, UINT(IDM_ORLOESCH+MenuOffset()), MF_ENABLED);		
	}
}                

return TRUE;                                      

}

// QueryInterface ist jetzt notwendig, da ein weiteres Interface unterstützt wird
STDMETHODIMP CTextExt :: QueryInterface (REFIID riid, LPVOID *ppv) 
{
// hier nur nach zusätzlichen Interfaces fragen
	if (riid == IID_IMaintainTexts) {
		*ppv = m_pTextPro;
		LPUNKNOWN (*ppv) -> AddRef();
		return NOERROR;
	}

// den Rest macht die BasisKlasse
return CTriasExtension :: QueryInterface (riid, ppv);
}

extern "C" {

char * PASCAL ExtObjNummer (long lONr, char *pBuffer, short)
{
	if (pBuffer)
		return ltoa (lONr, pBuffer, 10);

return NULL;
}

}


#if !defined(WIN32)
CExtDLL NEAR MyExtensionDLL (NULL);	
#endif // WIN32


