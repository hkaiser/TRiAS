///////////////////////////////////////////////////////////////////////////
//	CWaitCursor
///////////////////////////////////////////////////////////////////////////
//	Zeigt einen Wartecursor (Sanduhr) an.
//	Bei Zerstörung der Instanz dieser Klasse wird der ursprüngliche Cursor
//	wiederhergestellt.
//
//	(c) 1995 uve GmbH FEZ Potsdam
//
//	Stand:			#AD950326
//	Datei:			cwc.h
///////////////////////////////////////////////////////////////////////////

#ifndef _CWC_H
#define _CWC_H

class CWaitCur
{
	HCURSOR	m_hOldCursor;

public:
				CWaitCur();
				~CWaitCur();
};

#endif
