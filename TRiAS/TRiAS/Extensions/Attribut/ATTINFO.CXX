// ----------------Datenbankübersicht -----------------------------
// File: ATTINFO.CXX

#include "attribp.hxx"
#include "attribut.h"
#include "define.h"

#include "idkey.hxx"
#include "objkey.hxx"
#include "attinfo.hxx"


//-----------------------------------------------------------------------
//------------------------INFO-Fenster-----------------------------------
//-----------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

IdentInformation :: IdentInformation (pWindow pW, uint res, ResourceFile &RF, pchar pCaption, short iRange)
	     : ModeLessDialog (pW, ResID ( res, &RF)),
	       _Status (this,IDG_SHOWSTATUSGAUGE),
	       _RF (RF),
	       CancelButton (this, IDCANCEL)

{
// Variablen initialisieren
	_fWasInterrupted = false;

	_pW = pW;

	pW -> Disable();

	_lIdents = 0;
	_Number =0;
	SetCaption ( pCaption);
	_iRangeAll = iRange;
	_iCurrVal = -1;
	_Status.SetRange ( iRange);
	_Status.SetPosition (0);
	_Status.SetDeltaPos(1);
	return;
}

#pragma warning (default: 4355)


IdentInformation :: ~IdentInformation (void)
{
	_pW -> Enable();

}

void IdentInformation :: SetStart ( void )
{
static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID( IDS_STARTRECHERCHE,&_RF),50));
	_Status.SetText (s_pTmp);

}

void IdentInformation :: SetText ( short iCnt )
{
static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID( IDS_OBJEKTRECHERCHE,&_RF),50),iCnt);
	_Status.SetText (s_pTmp);
	_Status.SetPosition (iCnt);

}

void IdentInformation :: ModifyWindow ( long Ident )
{

//char pNum[20];	

PBDDATA pbdData;
char *pKText = new char [MAXFCTNAME+1];
	if ( pKText == NULL )
		return;
	_Key = Ident;
	_Number++;
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = _Key;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = MAXFCTNAME;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID(IDS_GAUGEBOX,&_RF),50), pKText);
	_Status.SetText (s_pTmp);

	DELETE (pKText);
	return;
}

void _XTENSN_EXPORT IdentInformation :: ButtonClick (ControlEvt )
{
	_fWasInterrupted = true;		// Analyse abbrechen

}
//---------------------------------------------------------------------------
// Ende ATTINFO.CXX
