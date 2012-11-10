// File: TPMEMBER.CXX

#include "tprojp.hxx"

#include <shellapi.h>

#include "version.h"

#include "defproj.h"
#include "tproject.h"
#include "about.h"

#include "about.hxx"
#include "menukey.hxx"
#include "projprof.hxx" 
#include "txtedit.hxx"
#include "teprodef.hxx"
#include "tpmcode.hxx"
#include "tproject.hxx"		// Klasse für diese Erweiterung

//---------------------------------------------------------------------
//-------------MEMBER--------------------------------------------------
//--------------------------------------------------------------------

TPRJTree *CProjectExtension :: GetTPAktuell ( char *pProject)
{
	TPRJTree *pTPRJ = NULL;


	if ( !m_pPROJ || m_pPROJ->Count() == 0) {
		return pTPRJ;
	}

	if ( !pProject || *pProject == '\0')
		return pTPRJ;

	CTable t (*m_pPROJ);
	if ( t.Find ( pProject)) {
		PROJLock l(t);
		pTPRJ = l->pTPRJ();
	}


	return pTPRJ;

}
//------------------------------------------------------------------------

void CProjectExtension :: SetSightInformation ( void)
{
	if ( !m_pMainDir || !m_pLocDir)
		return;
	if ( m_pMainDir && strcmp ( m_pLocDir, m_pMainDir ) == 0 ) {
		if ( !m_pMainSight ) {
			m_pMainSight = new char [ _MAX_PATH];
			if ( m_pMainSight != NULL )
				DEX_GetActiveSight (m_pMainSight); 
		}
		if ( *m_pMainSight == '\0' )
			DEX_GetActiveSight (m_pMainSight); 

		m_iLevel = 0;
		m_iLowLevel = 0;
		m_iHighLevel = 0;

	}
	return;

}
//-----------------------------------------------------------------------

int CProjectExtension :: ReadProjectProFile ( void)
{
	int NumMenuPoints = 0;

	if (!m_pLocDir || ! m_pPROJ ) 
		return NumMenuPoints;
	
	{
	ProjectProFile PF (m_pLocDir, &RF(), m_pPROJ, m_iLevel);

	NumMenuPoints = PF.GetProjectFile();
	}
	return NumMenuPoints;
	
}
//-----------------------------------------------------------------------
//-----ENDE TPMEMBER.CXX ------------------------------------------------
