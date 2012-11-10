// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 10:59:25 
//
// @doc
// @module Thread.h | Declaration of the <c CThread> class

/////////////////////////////////////////////////////////////////////////////
// Abstract Base CThread class for creating general Worker Thread Objects
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//@doc CTHREAD
//
//@module CThread.h |
//
//PROJECT		: CThread Class
//<nl>SUBSYSTEM	: CThread Base Class
//<nl>AUTHOR		: Dominik Filipp, <cp>1999, Slovakia, Europe
//
//<nl>DESCRIPTION:
//<nl>Abstract Base CThread Class header file.
//
// @topic CThreadException Class |
// The base CException-derived class used in CThread-derived classes.
// @topic CThread Class |
// The base MFC CObject-derived class that encapsulates WINDOWS Worker Thread abilities.
// <nl>CThread class offers many features that are not implemented or supported
// by WINDOWS System. It allows to build up the full-fledged OOP Class hierarchy,
// supports several levels of safe Thread Synchronization as well as the Thread Notification.
// <nl><nl>Detailed information how do CThreads work, how should be managed or handled
// can be found in the 'Developer.doc' documentation in '\Doc' subdirectory of the main
// installation directory.
// @topic License Conditions |
// This software is a freeware and may be freely used or distributed without restriction.
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__23722BEF_CB24_11D2_BB7B_00104B654EDA__INCLUDED_)
#define AFX_THREAD_H__23722BEF_CB24_11D2_BB7B_00104B654EDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Thread.h : header file
//

#include <winbase.h>	// Synchronization functions
#include <afxtempl.h>	// MFC templates

// Internal CThread Interface macros ////////////////////////////////////////
#define	SUPPORT_THREAD_SYNCHRONIZATION(ClassName)	m_strThreadHandlerClassName = #ClassName; \
													m_bIsSynchronized = TRUE;
#define	SUPPORT_THREAD_NOTIFICATION					m_bSupportSignalNotification = TRUE;
/////////////////////////////////////////////////////////////////////////////

class CThread;
// @class CThreadException Class Members
// @base public | CException
class CThreadException : public CException
{
public:
// @access <nl>Public Members:
	static enum {UNKNOWN_ERROR						= 0,
				 CANNOT_CREATE_THREAD				= 1,
				 THREAD_ALREADY_STARTED				= 2,
				 CANNOT_TERMINATE_THREAD			= 3,
				 CANNOT_CREATE_NOTIFICATION_OBJECT	= 4,
				 CANNOT_SIGNAL_NOTIFICATION_OBJECT	= 5};

//	Default error message texts
	static CString s_strERROR_THREAD_ALREADY_STARTED;

// @cmember CThreadException Constructor
	CThreadException(CThread* pThread = NULL);
// @cmember CThreadException Constructor
	CThreadException(CThread* pThread, CString strErrorMsg, int nExceptionType = CThreadException::UNKNOWN_ERROR);
// @cmember CThreadException Constructor
	CThreadException(CThread* pThread, UINT nErrorMsgID, int nExceptionType = CThreadException::UNKNOWN_ERROR);

// @cmember Get CThread Object
	CThread*	GetThread() const;
// @cmember Get Error Message
	CString		GetErrorMsg() const;
// @cmember Get Type of Thrown Exception
	int			GetType() const;
// @cmember Report Error
	virtual int	ReportError(UINT nType = MB_OK, UINT nMessageID = 0);
// @cmember Get String Representation Corresponding to the System Error Code
	static CString GetLastSystemErrorMsg(DWORD dwSysErrorCode);

// Attributes & Operations & Overridables
protected:
// @access <nl>Protected Members:
	CThread*	m_pThread;
	CString		m_strErrorMsg;
	int			m_nExceptionType;

// @cmember Set CThread Object Throwing an Exception
	void	SetThread(CThread* pThread);
// @cmember Set Error Message
	void	SetErrorMsg(CString strErrorMsg);
// @cmember Set Error Message
	void	SetErrorMsg(UINT nErrorMsgID);
// @cmember Set Exception Type
	void	SetType(int nType);
};

// @class CThread Class Members
// @base public | CObject
class CThread : public CObject
{
public:
	DECLARE_DYNAMIC(CThread)

// Attributes
public:
// @access <nl>Public Members:
	static enum {DW_OK					= 0x00000000,
				 DW_ERROR				= 0xFFFFFFFF,
				 DW_UNDEFINED			= 0xFFFFFFFE,
				 DW_TIMEOUT_ELAPSED		= 0xFFFFFFFD,
				 DW_INFINITE			= INFINITE,
				 THREAD_CREATED			= 0,
				 THREAD_STOPPED			= 1,
				 THREAD_RUNNING			= 2,
				 THREAD_PAUSED			= 3,
				 THREAD_CONTINUING		= 4,
				 THREAD_PENDING			= 5,
				 THREAD_USER_ACTIVITY	= 6};

	// Construction & Destruction
// @cmember CThread Constructor
	CThread(void* pOwnerObject = NULL, LPARAM lParam = 0L);
// @cmember CThread Destructor
	virtual ~CThread();
// @cmember Get Thread Attributes
	SECURITY_ATTRIBUTES GetAttributes() const;
// @cmember Get Thread Stack Size
	DWORD	GetStackSize() const;
// @cmember Get Thread Handle
	HANDLE	GetHandle() const;
// @cmember Get Thread ID
	DWORD	GetID() const;
// @cmember	Get Thread Exit Code
	DWORD	GetExitCode() const;
// @cmember Get Thread Activity Status
	int		GetActivityStatus() const;
// @cmember Get WINDOWS Thread Priority
	int		GetPriority() const;
// @cmember Check if Thread is Alive
	BOOL	IsAlive();

// Operations && Overridables
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// @cmember Start Thread
	void	Start();
// @cmember Fire Run Command
	void	Run();
// @cmember Fire Pause Command
	void	Pause();
// @cmember Fire Continue Command
	void	Continue();
// @cmember Fire Reset Command
	void	Reset();
// @cmember Fire Stop Command
	BOOL	Stop(DWORD& dwExitCode, DWORD dwTimeout = CThread::DW_INFINITE);
// @cmember Kill Thread
	void	Kill(DWORD dwExitCode = CThread::DW_OK, BOOL bCloseAnyway = FALSE);
// @cmember Post Command to Thread
	void	PostCommand(int nCommand);
// @cmember Cancel All Notification Commands
	void	ResetCommands();
// @cmember Set Owner Object Parameters
	void	SetOwnerParams(void* pOwnerObject, LPARAM lParam = 0L);
// @cmember Get Owner Object Parameters
	void	GetOwnerParams(void*& pOwnerObject, LPARAM& lParam) const;
// @cmember Set Thread Attributes
	void	SetAttributes(LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL);
// @cmember Set Thread Stack Size
	void	SetStackSize(DWORD dwStackSize = 0);
// @cmember Set WINDOWS Thread Priority
	BOOL	SetPriority(int nPriority = THREAD_PRIORITY_NORMAL);
// @cmember Wait For the Desired CThread Activity Status
	BOOL	WaitForActivityStatus(int nActivityStatus, DWORD dwTimeout = CThread::DW_INFINITE) const;
// @cmember Open Process Synchronization
	static void OpenProcessLocking();
// @cmember Close Process Synchronization
	static void CloseProcessLocking();
// @cmember Lock Critical Code in Process Synchronization Mode
	static void ProcessLock();
// @cmember Unlock Critical Code in Process Synchronization Mode
	static void ProcessUnlock();

// Attributes
public:
	static enum {CMD_NONE					= 0,
				 CMD_TIMEOUT_ELAPSED		= 1,
				 CMD_INITIALIZE				= 2,
				 CMD_RUN					= 3,
				 CMD_PAUSE					= 4,
				 CMD_CONTINUE				= 5,
				 CMD_RESET					= 6,
				 CMD_STOP					= 7,
				 CMD_USER_COMMAND			= 8,
				 BASE_DELAY_INTERVAL		= 100};

	BOOL	m_bSupportSignalNotification;
	BOOL	m_bIsSynchronized;
	CString	m_strThreadHandlerClassName;

// @access <nl>Protected Members:
// Operations
protected:
	// @cmember Set Thread Activity Status
	void	SetActivityStatus(int nActivityStatus);
	// @cmember Lock Critical Code in Thread-Handler-Oriented Synchronization Mode
	void	Lock();
	// @cmember Unlock Critical Code in Thread-Handler-Oriented Synchronization Mode
	void	Unlock();
	// @cmember Wait for Incoming Commands
	void	WaitForNotification(int& nIncomingCommand, DWORD dwDefaultTimeout = CThread::DW_INFINITE);
	// @cmember Handle Command Immediately Bypassing Other Pending Commands
	BOOL	HandleCommandImmediately(int nCommand);

// Overridables
protected:
	// Main virtual Thread task method implemented in CThread-derived classes...
	// The only method that must be implemented in some CThread-derived class.
	/////////////////////////////////////////////////////////////////////////////
	// @cmember Main Thread Task Handler (Abstract Declaration)
	virtual DWORD ThreadHandler() = 0;
	/////////////////////////////////////////////////////////////////////////////
	//@cmember Make Specific Unallocations After The Thread Has Been Killed
	virtual void OnKill();

// Attributes & Operations
private:
	class CInternalSynchronization
	{
	public:
		CInternalSynchronization();
		~CInternalSynchronization();
		LPCRITICAL_SECTION m_pInternalCriticalSection;
	};

	friend class CInternalSynchronization;

	typedef struct _THREAD_SYNCHRONICITY_TAG
	{
		CString				strThreadHandlerClassName;
		LPCRITICAL_SECTION	pCriticalSection;
		DWORD				dwCountOfRunningThreads;
	} THREAD_SYNCHRONICITY;

	static	CList<THREAD_SYNCHRONICITY, THREAD_SYNCHRONICITY&> s_synchronicityList;
	static	CInternalSynchronization s_InternalThreadSynchronization;
	static	void ResetSynchronizationList();
	static	LPCRITICAL_SECTION s_pProcessLockObject;
	static	DWORD WINAPI ControllingFunction(LPVOID lpParameter);

	POSITION m_runtimeSynchronizationObjectPosition;
	SECURITY_ATTRIBUTES m_ThreadAttributes;
	LPSECURITY_ATTRIBUTES m_lpThreadAttributes;
	HANDLE	m_hThreadHandle;
	HANDLE	m_hSignalObject;
	DWORD	m_dwThreadID;
	DWORD	m_dwStackSize;
	DWORD	m_dwThreadExitCode;
	volatile int m_nActivityStatus;
	void*	m_pOwnerObject;
	LPARAM	m_lParam;
	CUIntArray m_nCommandList;

	BOOL	IsThreadAlive();
	BOOL	RegisterNotificationObject(CString& strError);
	void	UnregisterNotificationObject();
	BOOL	PostThreadCommand(int nCommand, CString& strError);
	BOOL	ReceiveCommand(int& nIncomingCommand);
	void	StoreThreadExitCode();
	void	ResetThreadObject(DWORD dwExitCode);

	void	ResetThreadRuntimeData();
	void	ResetSynchronizationObject(THREAD_SYNCHRONICITY& synchronizingObject);
	void	RegisterRuntimeSynchronization();
	void	UnregisterRuntimeSynchronization();
	void	UpdateRuntimeSynchronizationObject(THREAD_SYNCHRONICITY& synchronizingObject);
	void	DeleteRuntimeSynchronizationObject();
	BOOL	FindRuntimeSynchronizationObject();
	THREAD_SYNCHRONICITY GetRuntimeSynchronizationObject();
};

/////////////////////////////////////////////////////////////////////////////
// Just for AutoDuck purposes...
/////////////////////////////////////////////////////////////////////////////
// @enum CThreadException Predefined Types
// @emem UNKNOWN_ERROR | Exception origin not known.
// @emem CANNOT_CREATE_THREAD | WINDOWS Thread cannot be created.
// @emem THREAD_ALREADY_STARTED | Thread is already started.
// @emem CANNOT_TERMINATE_THREAD | Thread termination failed.
// @emem CANNOT_CREATE_NOTIFICATION_OBJECT | Internal notification error (not enough memory or access denied).
// @emem CANNOT_SIGNAL_NOTIFICATION_OBJECT | Internal notification error (not enough memory or access denied).

// @enum CThread General Predefined Values
// @emem DW_OK | Exception origin not known.
// @emem DW_ERROR | WINDOWS Thread cannot be created.
// @emem DW_UNDEFINED | Thread is already started.
// @emem DW_TIMEOUT_ELAPSED | Thread termination failed.
// @emem DW_INFINITE | Infinite Timeout Interval.

// @enum CThread Activity Status Predefined Values
// @emem THREAD_CREATED | Thread was successfully created (activity-status set by the Start() method).
// @emem THREAD_STOPPED | Thread is stopped.
// @emem THREAD_RUNNING | Thread is running.
// @emem THREAD_PAUSED | Thread is paused.
// @emem THREAD_CONTINUING | Thread is continuing.
// @emem THREAD_PENDING | Thread is pending.
// @emem THREAD_USER_ACTIVITY | Base offset for the user-defined activity status.

// @enum CThread Predefined Commands
// @emem CMD_NONE | No command received.
// @emem CMD_TIMEOUT_ELAPSED | Wait-timeout elapsed (not command).
// @emem CMD_INITIALIZE | Initialize thread task.
// @emem CMD_RUN | Run thread task.
// @emem CMD_PAUSE | Pause thread task.
// @emem CMD_CONTINUE | Continue thread task.
// @emem CMD_RESET | Reset thread task.
// @emem CMD_STOP | Stop thread task and leave controlling function.
// @emem CMD_USER_COMMAND | Base offset for the user-defined command.

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_H__23722BEF_CB24_11D2_BB7B_00104B654EDA__INCLUDED_)
