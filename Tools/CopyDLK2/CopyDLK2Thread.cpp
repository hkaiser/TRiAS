// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 22.11.2002 14:17:27 
//
// @doc
// @module CopyDLK2Thread.cpp | Definition of the <c CCopyDLK2Thread> class

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD DERIVED CLASS - produced by Worker Thread Class Generator Rel. 1.0
// CopyDLK2Thread.cpp: Implementation of the CCopyDLK2Thread Class.
/////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <ospace/std/set>
#include <ospace/file/path.h>

#include "DestList.h"
#include "CopyDLK2Thread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT WM_THREADCALLBACK = RegisterWindowMessage("WM_THREADCALLBACK");
const UINT WM_COPYDLKSTATUS = RegisterWindowMessage("WM_COPYDLKSTATUS");
const UINT WM_THREADERROR = RegisterWindowMessage("WM_THREADERROR");
const UINT WM_FILECOPIED = RegisterWindowMessage("WM_FILECOPIED");

IMPLEMENT_DYNAMIC(CCopyDLK2Thread, CThread)

/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////////////
CCopyDLK2Thread::CCopyDLK2Thread(void* pOwnerObject /*= NULL*/, LPARAM lParam /*= 0L*/)
	: CThread(pOwnerObject, lParam)
{
	// WORKER THREAD CLASS GENERATOR - Support Thread Synchronization ///////////////
	SUPPORT_THREAD_SYNCHRONIZATION(CCopyDLK2Thread)
	// WORKER THREAD CLASS GENERATOR - Support Thread Notification //////////////////
	SUPPORT_THREAD_NOTIFICATION
	// User Initialization here...

	m_fMustStop = FALSE;
}

CCopyDLK2Thread::~CCopyDLK2Thread()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// CCopyDLK2Thread diagnostics
#ifdef _DEBUG
void CCopyDLK2Thread::AssertValid() const
{
	CThread::AssertValid();
}

void CCopyDLK2Thread::Dump(CDumpContext& dc) const
{
	CThread::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////////////

// Unallocate all thread specific extra resources if needed while killing this thread
void CCopyDLK2Thread::OnKill()
{
	// Code here...

	// This line may be removed if not necessary...
	CThread::OnKill();
}

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
/////////////////////////////////////////////////////////////////////////////////////
DWORD CCopyDLK2Thread::ThreadHandler()
{
BOOL bContinue = TRUE;
int nIncomingCommand;

	do {
		WaitForNotification(nIncomingCommand/*, CCopyDLKThread::DEFAULT_TIMEOUT*/);

	/////////////////////////////////////////////////////////////////////////////
	//	Main Incoming Command Handling
	//
	//	This switch statement is just a basic skeleton showing the mechanism
	//	how to handle incoming commands. Developer may remove or rewrite
	//	necessary parts of this switch to fit his needs.
	/////////////////////////////////////////////////////////////////////////////
	void *pOwner = NULL;
	LPARAM lParam = 0;

		GetOwnerParams(pOwner, lParam);
		((CWnd *)pOwner) -> PostMessage(WM_THREADCALLBACK, nIncomingCommand, FALSE);

		switch (nIncomingCommand) {
		case CThread::CMD_TIMEOUT_ELAPSED:	// timeout-elapsing handling
			if (GetActivityStatus() != CThread::THREAD_PAUSED) {
				// UserSpecificTimeoutElapsedHandler();
				// HandleCommandImmediately(CMD_RUN);	// fire CThread::CMD_RUN command if needed
			}
			break;

		case CThread::CMD_INITIALIZE:		// initialize the thread task
		// this command should be handled; it is automatically fired when the thread starts
			if (OnInitializeHandler()) 
				HandleCommandImmediately(CMD_RUN);	// fire CThread::CMD_RUN command after proper initialization
			else
				HandleCommandImmediately(CMD_STOP);	// end thread (nothing to copy)
			break;

		case CThread::CMD_RUN:				// handle 'OnRun' command
			if (GetActivityStatus() != CThread::THREAD_PAUSED)
			{
				SetActivityStatus(CThread::THREAD_RUNNING);
				OnRunHandler();
				HandleCommandImmediately(CMD_STOP);		// end thread
			}
			break;

		case CThread::CMD_PAUSE:			// handle 'OnPause' command
			if (GetActivityStatus() != CThread::THREAD_PAUSED)
			{
				// UserSpecificOnPauseHandler();
				SetActivityStatus(CThread::THREAD_PAUSED);
			}
			break;

		case CThread::CMD_CONTINUE:			// handle 'OnContinue' command
			if (GetActivityStatus() == CThread::THREAD_PAUSED)
			{
				SetActivityStatus(CThread::THREAD_CONTINUING);
				// UserSpecificOnContinueHandler();
				HandleCommandImmediately(CMD_RUN);	// fire CThread::CMD_RUN command
			}
			break;

		/*
		case CCopyDLKThread::CMD_USER_SPECIFIC:	// handle the user-specific command
			UserSpecificOnUserCommandHandler();
			break;
		*/

		case CThread::CMD_STOP:				// handle 'OnStop' command
			// UserSpecificOnStopHandler();
			bContinue = FALSE;				// ... and leave the thread function finally
			m_fMustStop = FALSE;
			break;

		default:							// handle unknown commands...
			break;
		}
		((CWnd *)pOwner) -> PostMessage(WM_THREADCALLBACK, nIncomingCommand, TRUE);

	} while (bContinue);
	return (DWORD)CThread::DW_OK;			//... if the thread task completion OK
}

///////////////////////////////////////////////////////////////////////////////
// Thread anhalten
BOOL CCopyDLK2Thread::Stop()
{
DWORD dwExitCode;

	m_fMustStop = TRUE;
	return CThread::Stop(dwExitCode);
}

BOOL CCopyDLK2Thread::OnInitializeHandler()
{
	m_fMustStop = FALSE;

void *pOwner = NULL;
LPARAM lParam = 0;

	GetOwnerParams(pOwner, lParam);

// feststellen, welche Datein kopiert werden sollen
CCopyData *pCopyData = reinterpret_cast<CCopyData *>(lParam);

	_ASSERTE(pCopyData->m_strDestPath.GetLength() > 0 &&
			 pCopyData->m_strSourcePath.GetLength() > 0);

// TODO: Add init code here

// Progressbar initialisieren
	((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETRANGE, 
	    MAKELPARAM(0, pCopyData->m_setFilesToCopy.size()));
	((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETPOS, 0);

	return TRUE;
}

bool EnsureDestinationPath (ospace::file::os_path const &rPath, 
    ospace::file::os_path const &rName, ospace::file::os_path &rFullName)
{
	rFullName = std::string(rPath) + std::string(rName);
	rFullName.become_simplified();

std::string dir_to_create;

	if (rFullName.has_drive()) {
		dir_to_create = rFullName.drive() + rFullName.drive_separator() + 
			rFullName.default_path_separator();
	} else if (rFullName.has_unc()) {
		dir_to_create = string("\\\\") + rFullName.server() + 
			rFullName.default_path_separator() + rFullName.share() + 
			rFullName.default_path_separator();
	}

	for (int i = 0; i < rFullName.levels(); ++i) {
		dir_to_create += rFullName[i];
		dir_to_create += rFullName.default_path_separator();
		CreateDirectory(dir_to_create.c_str(), NULL);
	}
	return true;
}

namespace {

    inline
    long GetDlkType (char const *pcExt)
    {
        if (!strnicmp (pcExt, "tif", 3))
            return FILETYPE_TIF;
        else if (!stricmp (pcExt, "x"))
            return FILETYPE_X;
        else if (!stricmp (pcExt, "tfw"))
            return FILETYPE_TFW;
        return FILETYPE_UNKNOWN;
    }
}
    
void CCopyDLK2Thread::OnRunHandler()
{
void *pOwner = NULL;
LPARAM lParam = 0;

	GetOwnerParams(pOwner, lParam);

CCopyData *pCopyData = reinterpret_cast<CCopyData *>(lParam);
ospace::file::os_path destpath = (char const *)pCopyData->m_strDestPath;

	if (destpath.base().size() > 0)
		destpath.base("");
	if (destpath.has_extension())
		destpath.no_extension();

// hiergeht's richtig los
	Lock();

std::set<std::string>::iterator end = pCopyData->m_setFilesToCopy.end();
int i = 0;

	for (std::set<std::string>::iterator it = pCopyData->m_setFilesToCopy.begin(); 
	     it != end; ++it, ++i) 
	{
	ospace::file::os_path dest, fulldest;

        ::SetLastError(S_OK);
		if (EnsureDestinationPath (destpath, dest, fulldest)) 	// Zielpfad physisch erzeugen
		{
		// Datei kopieren, wenn verschieben fehlgeschlagen ist
		ospace::file::os_path filename(*it);
		long lDlkName = strtoul(filename.base().c_str(), NULL, 10);
		long lDlkType = GetDlkType(filename.extension().c_str());
		
		    fulldest.filename(filename.filename());
			if (!CopyFileEx((*it).c_str(), std::string(fulldest).c_str(), NULL, 0, &m_fMustStop, 0)) {
			long lIndex = pCopyData->m_Errors.AddErrorEntry(GetLastError(), lDlkName, (*it).c_str());
			
				((CWnd *)pOwner)->PostMessage(WM_THREADERROR, lIndex, lDlkType);
			}
			else {
			    ((CWnd *)pOwner)->PostMessage(WM_FILECOPIED, lDlkName, lDlkType);
            }
		}

	// Progressbar weitersetzen
		((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETPOS, i+1);
		if (m_fMustStop)
			break;		// wir sollen aufhören
	}

	Unlock();
}
