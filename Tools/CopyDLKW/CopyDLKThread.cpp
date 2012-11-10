// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 10:59:02 
//
// @doc
// @module CopyDLKThread.cpp | Definition of the <c CCopyDLKThread> class

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD DERIVED CLASS - produced by Worker Thread Class Generator Rel. 1.0
// CopyDLKThread.cpp: Implementation of the CCopyDLKThread Class.
/////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CopyDLKThread.h"

#include <ospace/file/path.h>
#include "boost/directory.h"

using namespace boost::filesystem;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT WM_THREADCALLBACK = RegisterWindowMessage("WM_THREADCALLBACK");
const UINT WM_COPYDLKSTATUS = RegisterWindowMessage("WM_COPYDLKSTATUS");
const UINT WM_THREADERROR = RegisterWindowMessage("WM_THREADERROR");

IMPLEMENT_DYNAMIC(CCopyDLKThread, CThread)

/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////////////
CCopyDLKThread::CCopyDLKThread(void* pOwnerObject /*= NULL*/, LPARAM lParam /*= 0L*/)
	: CThread(pOwnerObject, lParam)
{
	// WORKER THREAD CLASS GENERATOR - Support Thread Synchronization ///////////////
	SUPPORT_THREAD_SYNCHRONIZATION(CCopyDLKThread)
	// WORKER THREAD CLASS GENERATOR - Support Thread Notification //////////////////
	SUPPORT_THREAD_NOTIFICATION
	// User Initialization here...

	m_fMustStop = FALSE;
}

CCopyDLKThread::~CCopyDLKThread()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// CCopyDLKThread diagnostics
#ifdef _DEBUG
void CCopyDLKThread::AssertValid() const
{
	CThread::AssertValid();
}

void CCopyDLKThread::Dump(CDumpContext& dc) const
{
	CThread::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////////////

// Unallocate all thread specific extra resources if needed while killing this thread
void CCopyDLKThread::OnKill()
{
	// Code here...

	// This line may be removed if not necessary...
	CThread::OnKill();
}

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
/////////////////////////////////////////////////////////////////////////////////////
DWORD CCopyDLKThread::ThreadHandler()
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
BOOL CCopyDLKThread::Stop()
{
DWORD dwExitCode;

	m_fMustStop = TRUE;
	return CThread::Stop(dwExitCode);
}

///////////////////////////////////////////////////////////////////////////////
// Threadinitialisierung
bool IsValidDLKName (os_path &rName)
{
string base (rName.base());

	if (8 != base.size())
		return false;		// falsche Länge
	if (os_npos != base.find_first_not_of("0123456789"))
		return false;		// darf nur Zahlen im Namen haben

	return true;
}

void FindFilesFromPattern (os_path &rPath, set<string> &rFiles, LPCSTR pcPattern)
{
dir_it end;

	for (dir_it it (string(rPath).c_str(), pcPattern); it != end; ++it) {
		if (get<is_directory>(it))
			continue;

	// Namenskonvention prüfen
	os_path file = *it;

		if (!IsValidDLKName(file))
			continue;

	// Datei speichern
		if (rPath.has_directory())
			file.directory(string(rPath));
		else if (rPath.has_drive())
			file.drive(rPath.drive()[0]);
		else if (rPath.has_unc())
			file.unc(rPath.server(), rPath.share());

		rFiles.insert(string(file));
	}
}

BOOL CCopyDLKThread::OnInitializeHandler()
{
	m_fMustStop = FALSE;

void *pOwner = NULL;
LPARAM lParam = 0;

	GetOwnerParams(pOwner, lParam);

// feststellen, welche Datein kopiert werden sollen
CCopyData *pCopyData = reinterpret_cast<CCopyData *>(lParam);

	_ASSERTE(pCopyData->m_strDestPath.GetLength() > 0 &&
			 pCopyData->m_strSourcePath.GetLength() > 0);

os_path src = (LPCSTR)pCopyData->m_strSourcePath;

	FindFilesFromPattern(src, m_vecFiles, "*.tif");
	FindFilesFromPattern(src, m_vecFiles, "*.tfw");
	FindFilesFromPattern(src, m_vecFiles, "*.x");

	if (0 == m_vecFiles.size())
		return FALSE;		// nothing to copy

// Progressbar initialisieren
	((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETRANGE, MAKELPARAM(0, m_vecFiles.size()));
	((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETPOS, 0);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Hier erfolgt das eigentliche Kopieren
bool CalculateDestinationPath (string const &rName, os_path &rRelPath)
{
os_path fullname = rName;
string base = fullname.base();
char cbBuffer[_MAX_PATH];

	if (!IsValidDLKName(os_path(base.c_str())))
		return false;

	wsprintf(cbBuffer, ".\\1_%c%c\\2_%c%c\\3_%c%c\\%s.%s",
		base[0], base[4], base[1], base[5], base[2], base[6], 
		base.c_str(), fullname.extension().c_str());
	rRelPath = cbBuffer;
	return true;
}

bool EnsureDestinationPath (os_path const &rPath, os_path const &rName, 
	os_path &rFullName)
{
	rFullName = string(rPath) + string(rName);
	rFullName.become_simplified();

string dir_to_create;

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

void CCopyDLKThread::OnRunHandler()
{
void *pOwner = NULL;
LPARAM lParam = 0;

	GetOwnerParams(pOwner, lParam);

CCopyData *pCopyData = reinterpret_cast<CCopyData *>(lParam);
os_path destpath = (LPCSTR)pCopyData->m_strDestPath;

	if (destpath.base().size() > 0)
		destpath.base("");
	if (destpath.has_extension())
		destpath.no_extension();

// hiergeht's richtig los
	Lock();

set<string>::iterator end = m_vecFiles.end();
int i = 0;

	for (set<string>::iterator it = m_vecFiles.begin(); it != end; ++it, ++i) {
	os_path dest, fulldest;

		if (CalculateDestinationPath (*it, dest) &&				// Zielpfad berechnen
			EnsureDestinationPath (destpath, dest, fulldest))	// Zielpfad physisch erzeugen
		{
		// Datei kopieren
			if (!CopyFile((*it).c_str(), string(fulldest).c_str(), FALSE)) {
				((CWnd *)pOwner)->SendMessage(WM_THREADERROR, GetLastError(), 
					reinterpret_cast<LPARAM>((*it).c_str()));
				m_fMustStop = TRUE;
				break;
			}
		}

	// Progressbar weitersetzen
		((CWnd *)pOwner) -> PostMessage(WM_COPYDLKSTATUS, PBM_SETPOS, i+1);
		if (m_fMustStop)
			break;		// wir sollen aufhören
	}
	Unlock();
}
