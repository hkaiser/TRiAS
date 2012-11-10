#include "pheader.h"
#include "odbcext.hr"				//	Resource-Konstanten

#include <hpp/tooltipb.h>				//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CToolTipButton, CButton)
  //{{AFX_MSG_MAP(CToolTipButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CToolTipButton::CToolTipButton(UINT uiResID)
{
	ASSERT (uiResID > 0);
	m_uiResID = uiResID;
	m_bFirstCall = TRUE;
	m_fTTCreated = FALSE;
}

BOOL CToolTipButton::Create() 
{
	m_ToolTip.Create(this);		// Fehler nicht fatal
	m_fTTCreated = TRUE;
	return TRUE;
}

BOOL CToolTipButton::PreTranslateMessage(MSG* pMsg) 
{                     
  //create the tooltip
  if (m_bFirstCall && m_fTTCreated)
  {
    m_ToolTip.Activate(TRUE);
	ASSERT (m_uiResID > 0);
    m_ToolTip.AddTool(this, m_uiResID);
    m_bFirstCall = FALSE;
  }
  
  //give the tooltip a chance to handle the message
	if (m_fTTCreated) 
		m_ToolTip.RelayEvent(pMsg);

  return CButton::PreTranslateMessage(pMsg);
}


