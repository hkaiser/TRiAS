// ErgebnisDialog -------------------------------------------------------------
// File: PolygisDLG.CPP

#include "stdafx.h"
#include "PolygisPMFImpl.h"

#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <ctype.h>

#include <ERRINSTX.HXX>
#include <REGISTRX.HXX>

#if !defined(HUGE)
#if !defined(WIN32)
#define HUGE __huge
#else
#define HUGE
#endif // WIN32
#endif // HUGE

//  externe Variablen
extern ResourceFile *pRF;


#include "PolygisDLG.hxx"		// DialogKlasse

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ



#pragma warning (disable: 4355)

//////////////////////////////////////////////////////////////////////////////////////////////
CConfigDlg :: CConfigDlg (pWindow pW, char *pOberThema,char *pThema, char * pGruppe)
	    : DialogWindow (pW, ResID (IDD_THEMENDLG,pRF)),
	    m_OberThemenName (this, IDC_OBERTHEMENNAME),
	    m_ThemenName (this, IDC_THEMENNAME),
	    m_GruppenName (this, IDC_GRUPPENNAME)
{


	_pOberThema = NULL;
	_pThema = NULL;
	_pGruppe = NULL;

	if ( pOberThema && *pOberThema != '\0')
		m_ThemenName.SetText ( pThema);

	if ( pThema && *pThema != '\0')
		m_ThemenName.SetText ( pThema);

	if ( pGruppe && *pGruppe != '\0')
		m_GruppenName.SetText ( pGruppe);

	m_ThemenName.Disable();
	m_GruppenName.Disable();
}

#pragma warning (default: 4355)

CConfigDlg :: ~CConfigDlg (void)
{

	DELETE_OBJ(_pGruppe);
	DELETE_OBJ(_pThema);
	DELETE_OBJ(_pOberThema);

}

void CConfigDlg :: ButtonClick (ControlEvt CE)
{

	switch ((uint) CE.GetControlID ()) {

		case IDCANCEL:
			EndDlg (0);
			return;	
			
		case IDOK: 
			_pOberThema = new char [_MAX_PATH];
			m_OberThemenName.GetText (_pOberThema, 64);
			if ( *_pOberThema == '\0')
				DELETE_OBJ(_pOberThema);

			_pThema = new char [_MAX_PATH];
			m_ThemenName.GetText (_pThema, 64);
			if ( *_pThema == '\0')
				DELETE_OBJ(_pThema);

			_pGruppe = new char [_MAX_PATH];
			m_GruppenName.GetText (_pGruppe, 64);
			if ( *_pGruppe == '\0')
				DELETE_OBJ(_pGruppe);

			EndDlg(1);	// raus

			return;

		default:
			return;
	}       
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////