// EditControl fuer die Eingabe von Kurztexten
// File: TXTEDIT.CXX

#include "attribp.hxx"
#include "txtedit.hxx"
#include "attribut.h" 
#include "define.h"

#include <ctype.h>

// ----------------------------------------------------------------------------
// Ein Txtedit ist geeignet ein Kurztext kontrolliert einzulesen ----------------
// ----------------------------------------------------------------------------

// Konstruktoren --------------------------------------------------------------
TxtEdit :: TxtEdit (pDialogWindow p, ResID r) 
	 : ControlWindow (new SingleLineEdit (p, r))
{
	m_pKey = NULL;
	m_pPush = NULL;
	m_pCombo = NULL;
	m_pFirstKey = NULL;
	m_pFirstKey = new char [MAXKEY];
	if ( !m_pFirstKey)
		return;
	m_pKey = new char [MAXKEY];
	if ( !m_pKey)
		return;
	*m_pFirstKey = '\0';
}

TxtEdit :: TxtEdit (pWindow parent, uint id, Point p, Dimension d) 
	 : ControlWindow (new SingleLineEdit (parent, id, p, d)) 
{ 
	m_pKey = NULL;
	m_pPush = NULL;
	m_pCombo = NULL;
	m_pFirstKey = NULL;
	m_pFirstKey = new char [MAXKEY];
	if ( !m_pFirstKey)
		return;
	m_pKey = new char [MAXKEY];
	if ( !m_pKey)
		return;
	*m_pFirstKey = '\0';
}

// neue EventHandler für TxtEdits ---------------------------------------------
void _XTENSN_EXPORT TxtEdit :: KeyDown (KeyEvt e) 
{
char * pBuff = new char [MAXKEY];

	Default ((Event &)e); 
	if ( pBuff ) {
		GetText ( pBuff,MAXKEY-1);
		
		if ( *pBuff == '\0') {
			if ( m_pPush)
				m_pPush->Disable();
			if ( m_pCombo) {
				m_pCombo->Disable();
				m_pCombo->ChangeCurrentIndex(0);
			}
		}

		if ( m_pKey && strcmp ( pBuff,m_pKey) != 0 ) {
			if ( *pBuff != '\0' && m_pPush ) {
				m_pPush->Enable();
				if ( m_pCombo)
					m_pCombo->Enable();
			}

		}
		if ( *m_pFirstKey == '\0' && strlen(pBuff) == 1) {
			if ( m_pCombo )
				m_pCombo->ChangeCurrentIndex(2);
		}
		strcpy ( m_pFirstKey,pBuff);

		DELETE ( pBuff);
	}
}
// Destruktor -----------------------------------------------------------------
TxtEdit :: ~TxtEdit (void) 
{
	delete (SingleLineEdit *)GetControl();
	DELETE ( m_pKey);
	DELETE ( m_pFirstKey);
}

// diverse Memberfunktionen ---------------------------------------------------
void TxtEdit :: GetText (char *Buff, uint Len) 
{
	if ( Buff ) {
		if ( Len > MAXKEY-1 )
			Len = MAXKEY-1;
		GetEditControl() -> GetText (Buff, Len);
	}
	
}

void TxtEdit :: SetText (const char *Buff) 
{
	GetEditControl() -> SetText (Buff);
	if ( Buff) {
		if ( *Buff == '\0') {
			if ( m_pFirstKey )
				*m_pFirstKey = '\0';
		}
		if ( m_pKey)
			strcpy ( m_pKey,Buff);
	} else {
		if ( m_pFirstKey)
			*m_pFirstKey = '\0'; 
		if ( m_pKey)
			*m_pKey = '\0'; 
	}

	if ( m_pFirstKey && m_pKey ) {
		if ( strcmp ( m_pKey,m_pFirstKey) == 0 ) { 
			if ( m_pPush)
				m_pPush->Disable();
			if ( m_pCombo) {
				m_pCombo->Disable();
			}
		} else {
			if ( m_pPush)
				m_pPush->Enable();
			if ( m_pCombo)
				m_pCombo->Enable();
		}
	}

}

void TxtEdit :: SetButton (PushButton *p) 
{
	if (p)
		m_pPush = p;
	
}

void TxtEdit :: SetCombo (ComboBox *p) 
{
	if (p)
		m_pCombo = p;
	
}


void TxtEdit :: SetKey (char *pKey) 
{
	if ( !pKey)
		return;
	if ( !m_pFirstKey) {
		m_pFirstKey = new char [_MAX_PATH];
		if ( !m_pFirstKey )
			return;
		strcpy ( m_pFirstKey, pKey);
	}
	return;	
}

void TxtEdit :: SetTextLimit (uint nchars) 
{
	GetEditControl() -> SetTextLimit (nchars);
}

int TxtEdit :: GetTextLen (void) 
{
	return GetEditControl() -> GetTextLen ();
}
//---------------------TXTEDIT.CXX----------------------
