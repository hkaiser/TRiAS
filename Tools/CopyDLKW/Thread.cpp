// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 10:59:30 
//
// @doc
// @module Thread.cpp | Definition of the <c CThread> class

/////////////////////////////////////////////////////////////////////////////
// Abstract Base CThread class for creating general Worker Thread Objects
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//@doc CTHREAD
//
//@module CThread.cpp |
//
//PROJECT		: CThread Class
//<nl>SUBSYSTEM	: CThread Base Class
//<nl>AUTHOR		: Dominik Filipp, <cp>1999, Slovakia, Europe
//
//<nl>DESCRIPTION:
//<nl>Abstract Base CThread Class implementation file.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CThread, CObject)

#define	INTERNAL_LOCK		if (s_InternalThreadSynchronization.m_pInternalCriticalSection != NULL) \
							::EnterCriticalSection(s_InternalThreadSynchronization.m_pInternalCriticalSection);
#define	INTERNAL_UNLOCK		if (s_InternalThreadSynchronization.m_pInternalCriticalSection != NULL) \
							::LeaveCriticalSection(s_InternalThreadSynchronization.m_pInternalCriticalSection);

/////////////////////////////////////////////////////////////////////////////
// CThread static members
CList<CThread::THREAD_SYNCHRONICITY, CThread::THREAD_SYNCHRONICITY&> CThread::s_synchronicityList;
CThread::CInternalSynchronization CThread::s_InternalThreadSynchronization;
LPCRITICAL_SECTION CThread::s_pProcessLockObject			= NULL;
CString CThreadException::s_strERROR_THREAD_ALREADY_STARTED	= "Thread is already started!";
/////////////////////////////////////////////////////////////////////////////

// @mfunc | CThreadException | CThreadException | CThreadException constructor.
// General CThreadException class intended to be used by CThread-derived classes.
// @parmopt CThread* | pThread | NULL | [in] CThread object causing an exception.
// @xref <mf CThreadException::SetThread>
CThreadException::CThreadException(CThread* pThread /*= NULL*/)
{
	m_pThread			= pThread;
	m_strErrorMsg		= _T("");
	m_nExceptionType	= CThreadException::UNKNOWN_ERROR;
}

// @mfunc | CThreadException | CThreadException | CThreadException constructor.
// General CThreadException class intended to be used by CThread-derived classes.
// CThread-derived methods should always throw CThreadException exceptions.
// To distinguish the origin of thrown exceptions the user should use the type of CThreadException exception.
// CThread methods use predefined CThreadException types but the user may define own types in CThread-derived class.
// Predefined types used in CThread class are described in 'Parameters' section.
// @parm CThread* | pThread | [in] CThread object causing an exception.
// @parm CString | strErrorMsg | [in] String describing an exception origin.
// @parmopt int | nExceptionType | CThreadException::UNKNOWN_ERROR | [in] Type of thrown exception.
// @flag CThreadException::UNKNOWN_ERROR  | Exception origin not known.
// @flag CThreadException::CANNOT_CREATE_THREAD  | WINDOWS Thread cannot be created.
// @flag CThreadException::THREAD_ALREADY_STARTED  | Thread is already started.
// @flag CThreadException::CANNOT_TERMINATE_THREAD  | Thread termination failed.
// @flag CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT  | Internal notification error.
// @flag CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT  | Internal notification error.
// @xref <mf CThreadException::SetThread>
// <nl><mf CThreadException::SetType>
CThreadException::CThreadException(CThread* pThread, CString strErrorMsg, int nExceptionType /*= CThreadException::UNKNOWN_ERROR*/)
{
	m_pThread			= pThread;
	m_strErrorMsg		= strErrorMsg;
	m_nExceptionType	= nExceptionType;
}

// @mfunc | CThreadException | CThreadException | CThreadException constructor.
// General CThreadException class intended to be used by CThread-derived classes.
// CThread-derived methods should always throw CThreadException exceptions.
// To distinguish the origin of thrown exceptions the user should use the type of CThreadException exception.
// CThread methods use predefined CThreadException types but the user may define own types in CThread-derived class.
// Predefined types used in CThread class are described in 'Parameters' section.
// @parm CThread* | pThread | [in] CThread object causing an exception.
// @parm UINT | nErrorMsgID | [in] Resource ID of the string describing an exception origin.
// @parmopt int | nExceptionType | CThreadException::UNKNOWN_ERROR | [in] Type of thrown exception.
// @flag CThreadException::UNKNOWN_ERROR  | Exception origin not known.
// @flag CThreadException::CANNOT_CREATE_THREAD  | WINDOWS Thread cannot be created.
// @flag CThreadException::THREAD_ALREADY_STARTED  | Thread is already started.
// @flag CThreadException::CANNOT_TERMINATE_THREAD  | Thread termination failed.
// @flag CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT  | Internal notification error.
// @flag CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT  | Internal notification error.
// @xref <mf CThreadException::SetThread>
// <nl><mf CThreadException::SetType>
CThreadException::CThreadException(CThread* pThread, UINT nErrorMsgID, int nExceptionType /*= CThreadException::UNKNOWN_ERROR*/)
{
	m_pThread			= pThread;
	m_strErrorMsg.Format(nErrorMsgID);
	m_nExceptionType	= nExceptionType;
}

// @mfunc | CThreadException | GetThread | Gets CThread object that caused an exception.
// @rdesc
// CThread object that caused an exception.
// @xref <mf CThreadException::SetThread>
CThread* CThreadException::GetThread() const
{
	return m_pThread;
}

// @mfunc void | CThreadException | SetThread | Sets CThread object that caused an exception.
// @parm CThread* | pThread | [in] CThread object that caused an exception.
// @xref <mf CThreadException::GetThread>
void CThreadException::SetThread(CThread* pThread)
{
	m_pThread = pThread;
}

// @mfunc int | CThreadException | ReportError | Displays an exception-error message in the standard Message Box.
// @parmopt UINT | nType | MB_OK | [in] Type of the Message Box to be displayed.
// @parmopt UINT | nMessageID | 0 | [in] Error message string resource ID.
// @rdesc
// Message Box return value.
int CThreadException::ReportError(UINT nType /*= MB_OK*/, UINT nMessageID /*= 0*/)
{
	CString strErrorMsg = m_strErrorMsg;
	if (nMessageID != 0) strErrorMsg.Format(nMessageID);
	return AfxMessageBox(strErrorMsg, nType);
}

// @mfunc void | CThreadException | SetErrorMsg | Sets an error message describing an exception origin.
// @parm CString | strErrorMsg | [in] Error message string.
// @xref <mf CThreadException::GetErrorMsg>
void CThreadException::SetErrorMsg(CString strErrorMsg)
{
	m_strErrorMsg = strErrorMsg;
}

// @mfunc void | CThreadException | SetErrorMsg | Sets an error message describing an exception origin.
// @parm UINT | nErrorMsgID | [in] Error message string resource ID.
// @xref <mf CThreadException::GetErrorMsg>
void CThreadException::SetErrorMsg(UINT nErrorMsgID)
{
	m_strErrorMsg.Format(nErrorMsgID);
}

// @mfunc CString | CThreadException | GetErrorMsg | Gets an error message describing an exception origin.
// @rdesc
// Error message string describing an exception.
// @xref <mf CThreadException::SetErrorMsg>
CString CThreadException::GetErrorMsg() const
{
	return m_strErrorMsg;
}

// @mfunc void | CThreadException | SetType | Sets the type of an exception.
// CThread-derived methods should always throw CThreadException exceptions.
// To distinguish the origin of thrown exceptions the user may define own types of
// CThreadException exceptions in the CThread-derived class.
// Predefined types used in CThread class are described in 'Parameters' section.
// @parm UINT | nErrorMsgID | [in] Exception type.
// @flag CThreadException::UNKNOWN_ERROR  | Exception origin not known.
// @flag CThreadException::CANNOT_CREATE_THREAD  | WINDOWS Thread cannot be created.
// @flag CThreadException::THREAD_ALREADY_STARTED  | Thread is already started.
// @flag CThreadException::CANNOT_TERMINATE_THREAD  | Thread termination failed.
// @flag CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT  | Internal notification error.
// @flag CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT  | Internal notification error.
// @xref <mf CThreadException::GetType>
void CThreadException::SetType(int nExceptionType)
{
	m_nExceptionType = nExceptionType;
}

// @mfunc int | CThreadException | GetType | Gets the type of an exception.
// Types used in the CThread class are described in 'Return Value' section.
// @rdesc
// Predefined types that may be thrown by CThread methods are as follows:
// @flag CThreadException::UNKNOWN_ERROR  | Exception origin not known.
// @flag CThreadException::CANNOT_CREATE_THREAD  | WINDOWS Thread cannot be created.
// @flag CThreadException::THREAD_ALREADY_STARTED  | Thread is already started.
// @flag CThreadException::CANNOT_TERMINATE_THREAD  | Thread termination failed.
// @flag CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT  | Internal notification error.
// @flag CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT  | Internal notification error.
// @xref <mf CThreadException::SetType>
int CThreadException::GetType() const
{
	return m_nExceptionType;
}

// @mfunc static CString | CThreadException | GetLastSystemErrorMsg | Static method which returns the message text
// corresponding to the system error code. This error code should be returned
// by GetLastError() WINDOWS function immediately after the system error occurs.
// @rdesc
// String representation of the system error code.
// @parm DWORD | dwSysErrorCode | [in] System error code returned by GetLastError() WINDOWS function.
CString CThreadException::GetLastSystemErrorMsg(DWORD dwSysErrorCode)
{
	CString strErrMsg("");
	LPVOID lpMsgBuf = NULL;

	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					dwSysErrorCode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL
					);

	if (lpMsgBuf != NULL)
	{
		strErrMsg = (LPCSTR)lpMsgBuf;
		::LocalFree(lpMsgBuf);
	};

	return strErrMsg;
}
/////////////////////////////////////////////////////////////////////////////

// Internal nested CThread Synchronization Class implementation /////////////
// Only one instance of this class is established
CThread::CInternalSynchronization::CInternalSynchronization()
{
	CThread::ResetSynchronizationList();
	m_pInternalCriticalSection = new CRITICAL_SECTION;
	::InitializeCriticalSection(m_pInternalCriticalSection);
}

CThread::CInternalSynchronization::~CInternalSynchronization()
{
	CThread::ResetSynchronizationList();
	::DeleteCriticalSection(m_pInternalCriticalSection);
	delete m_pInternalCriticalSection;
	m_pInternalCriticalSection = NULL;
}

/////////////////////////////////////////////////////////////////////////////

// Process Locking mechanism (Process locking ) ///////////////////////////////
// @mfunc static void | CThread | OpenProcessLocking | Static method that opens the process
// synchronization. After the first call the process synchronization is opened.
// Additional call of this method has no any effect - the synchronization remains opened.
// The synchronization itself is accomplished by calling <mf CThread::ProcessLock> and <mf CThread::ProcessUnlock> methods
// between which is the critical code that is to be executed process-exclusively.
// Opened process-synchronization should be finally closed by <mf CThread::CloseProcessLocking>
// method.
// <nl>This locking mechanism does not support an inter-process synchronization.
// <nl><nl>As a static method may be used wherever in the code without
// constructing any CThread object.
// @xref <mf CThread::CloseProcessLocking>
// <nl><mf CThread::ProcessLock>
// <nl><mf CThread::ProcessUnlock>
void CThread::OpenProcessLocking()
{
	if (CThread::s_pProcessLockObject == NULL)
	{
		CThread::s_pProcessLockObject = new CRITICAL_SECTION;
		::InitializeCriticalSection(CThread::s_pProcessLockObject);
	};
}

// Process Locking mechanism (Process locking ) ///////////////////////////////
// @mfunc static void | CThread | ProcessLock | Static method that marks the beginning of the
// critical code that is to be executed process-exclusively.
// <nl><mf CThread::ProcessUnlock> method is the counterpart of the ProcessLock() method which bounds the end of
// the critical code. Both methods should be used in a way to prevent
// eventual deadlocks. Before using the method the process-synchronization must be opened
// by <mf CThread::OpenProcessLocking> method.
// <nl>This locking mechanism does not support an inter-process synchronization.
// <nl><nl>As a static method may be used wherever in the code without
// constructing any CThread object.
// @xref <mf CThread::OpenProcessLocking>
// <nl><mf CThread::CloseProcessLocking>
// <nl><mf CThread::ProcessUnlock>
void CThread::ProcessLock()
{
	if (CThread::s_pProcessLockObject != NULL)
		::EnterCriticalSection(CThread::s_pProcessLockObject);
}

// Process Locking mechanism (Process locking ) ///////////////////////////////
// @mfunc static void | CThread | ProcessUnlock | Static method that marks the end of the
// critical code that is to be executed process-exclusively.
// <nl><mf CThread::ProcessLock> method is the counterpart of ProcessUnlock() method which bounds the start of
// the critical code. Both methods should be used in a way to prevent
// eventual deadlocks. Before using the method the process-synchronization must be opened
// by <mf CThread::OpenProcessLocking> method.
// <nl>This locking mechanism does not support an inter-process synchronization.
// <nl><nl>As a static method may be used wherever in the code without
// constructing any CThread object.
// @xref <mf CThread::OpenProcessLocking>
// <nl><mf CThread::CloseProcessLocking>
// <nl><mf CThread::ProcessLock>
void CThread::ProcessUnlock()
{
	if (CThread::s_pProcessLockObject != NULL)
		::LeaveCriticalSection(CThread::s_pProcessLockObject);
}

// Process Locking mechanism (Process locking ) ///////////////////////////////
// @mfunc static void | CThread | CloseProcessLocking | Static method that closes the process
// synchronization that was previously opened by <mf CThread::OpenProcessLocking>.
// <nl>The synchronization itself is accomplished by calling <mf CThread::ProcessLock>
// and <mf CThread::ProcessUnlock> methods between which is the critical code that
// is to be executed process-exclusively.
// <nl><nl>As a static method may be used wherever in the code without
// constructing any CThread object.
// @xref <mf CThread::OpenProcessLocking>
// <nl><mf CThread::ProcessLock>
// <nl><mf CThread::ProcessUnlock>
void CThread::CloseProcessLocking()
{
	if (CThread::s_pProcessLockObject != NULL)
	{
		::DeleteCriticalSection(CThread::s_pProcessLockObject);
		delete CThread::s_pProcessLockObject;
		CThread::s_pProcessLockObject = NULL;
	};
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Worker Thread Class implementation ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Basic Data initialization.
// @mfunc | CThread | CThread | CThread constructor.
// User may pass a so-called 'Owner object' to the CThread class. The Owner object
// is an arbitrary object claimed to be an owner of CThread object.
// In such way the Owner object may be notified by CThread object while running the thread.
// Optional LPARAM parameter allows the user to pass an additional useful information.
// It's up to the developer's responsibility how to interpret and implement the
// Owner object parameters in CThread-derived class. CThread class itself
// just stores the passed values.The mentioned parameters may be also set up or read
// after CThread object construction by calling the <mf CThread::SetOwnerParams> and
// <mf CThread::GetOwnerParams> methods.
// <nl><nl>While constructing CThread object no any WINDOWS thread is being started.
// @parmopt void* | pOwnerObject | NULL | [in] CThread Owner object.
// @parmopt LPARAM | lParam | 0 | [in] General parameter passed to CThread object.
// @xref <mf CThread::SetOwnerParams>
// <nl><mf CThread::GetOwnerParams>
CThread::CThread(void* pOwnerObject /*= NULL*/, LPARAM lParam /*= 0L*/)
{
	m_pOwnerObject							= pOwnerObject;
	m_lParam								= lParam;
	m_lpThreadAttributes					= NULL;
	m_dwStackSize							= 0;
	m_bIsSynchronized						= FALSE;
	m_bSupportSignalNotification			= FALSE;
	m_runtimeSynchronizationObjectPosition	= NULL;
	m_hSignalObject							= NULL;
	m_dwThreadExitCode						= (DWORD)CThread::DW_UNDEFINED;
	m_strThreadHandlerClassName				= _T("");

	ResetThreadRuntimeData();
}

// Removing WINDOWS Thread (if it is not already stopped or killed)
// when last instance of CThread Object is being destructed.
// @mfunc | CThread | ~CThread | CThread destructor.
// CThread destructor kills the running WINDOWS thread that was not previously stopped
// and closes the CThread notification mode.
CThread::~CThread()
{
	if (IsAlive()) try {Kill((DWORD)CThread::DW_OK, TRUE);} catch (...) {};
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	UnregisterNotificationObject();
	ResetThreadRuntimeData();
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

// Basic Data initialization.
// @mfunc void | CThread | SetOwnerParams | Sets CThread Owner object parameters.
// User may pass a so-called 'Owner object' to the CThread class. The Owner object
// is an arbitrary object claimed to be an owner of CThread object.
// In such way the Owner object may be notified by CThread object while running the thread.
// Optional LPARAM parameter allows the user to pass an additional useful information.
// It's up to the developer's responsibility how to interpret and implement the
// Owner object parameters in CThread-derived class. CThread class itself
// just stores the passed values. The mentioned parameters can be read
// after the CThread object construction by calling the <mf CThread::GetOwnerParams> method.
// @parm void* | pOwnerObject | [in] CThread Owner object.
// @parmopt LPARAM | lParam | 0 | [in] General parameter passed to CThread object.
// @xref <mf CThread::GetOwnerParams>
void CThread::SetOwnerParams(void* pOwnerObject, LPARAM lParam /*= 0L*/)
{
	m_pOwnerObject	= pOwnerObject;
	m_lParam		= lParam;
}

// @mfunc void | CThread | GetOwnerParams | Retrieves the CThread Owner object parameters.
// @parm void*& | pOwnerObject | [out] Reference to the CThread Owner object being retrieved.
// @parm LPARAM& | lParam | [out] Reference to the LPARAM parameter being retrieved.
// @xref <mf CThread::SetOwnerParams>
void CThread::GetOwnerParams(void*& pOwnerObject, LPARAM& lParam) const
{
	pOwnerObject	= m_pOwnerObject;
	lParam			= m_lParam;
}

/////////////////////////////////////////////////////////////////////////////
// CThread diagnostics
#ifdef _DEBUG
void CThread::AssertValid() const
{
	CObject::AssertValid();
}

void CThread::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////

void CThread::ResetThreadRuntimeData()
{
	m_hThreadHandle		= NULL;
	m_dwThreadID		= 0;
	m_nActivityStatus	= CThread::THREAD_STOPPED;
	m_runtimeSynchronizationObjectPosition = NULL;

	m_nCommandList.RemoveAll();
	m_nCommandList.FreeExtra();
}

void CThread::ResetThreadObject(DWORD dwExitCode)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	UnregisterRuntimeSynchronization();
	if (m_hThreadHandle != NULL) ::CloseHandle(m_hThreadHandle);
	ResetThreadRuntimeData();
	m_dwThreadExitCode = dwExitCode;
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CThread Attributes and Operations

// Exact-Class specific Synchronization helper methods
void CThread::ResetSynchronizationList()
{
	if (CThread::s_synchronicityList.GetCount() > 0)
	{
		while (CThread::s_synchronicityList.GetHeadPosition() != NULL)
		{
			if (CThread::s_synchronicityList.GetHead().pCriticalSection != NULL)
			{
				::DeleteCriticalSection(CThread::s_synchronicityList.GetHead().pCriticalSection);
				delete CThread::s_synchronicityList.GetHead().pCriticalSection;
			};
			CThread::s_synchronicityList.RemoveHead();
		};
	};
}

void CThread::ResetSynchronizationObject(THREAD_SYNCHRONICITY& synchronizationObject)
{
	synchronizationObject.strThreadHandlerClassName	= _T("");
	synchronizationObject.pCriticalSection			= NULL;
	synchronizationObject.dwCountOfRunningThreads	= 0;
}

void CThread::UpdateRuntimeSynchronizationObject(THREAD_SYNCHRONICITY& synchronizationObject)
{
	CThread::s_synchronicityList.SetAt(m_runtimeSynchronizationObjectPosition, synchronizationObject);
}

void CThread::DeleteRuntimeSynchronizationObject()
{
	CThread::s_synchronicityList.RemoveAt(m_runtimeSynchronizationObjectPosition);
}

BOOL CThread::FindRuntimeSynchronizationObject()
{
	THREAD_SYNCHRONICITY synchronizationElement;
	POSITION currentPos = CThread::s_synchronicityList.GetHeadPosition(), newPos = currentPos;

	ResetSynchronizationObject(synchronizationElement);
	while (currentPos != NULL)
	{
		synchronizationElement = CThread::s_synchronicityList.GetNext(newPos);
		if (synchronizationElement.strThreadHandlerClassName == m_strThreadHandlerClassName)
		{
			m_runtimeSynchronizationObjectPosition = currentPos;
			return TRUE;
		}
		else
			currentPos = newPos;
	};

	return FALSE;
}

CThread::THREAD_SYNCHRONICITY CThread::GetRuntimeSynchronizationObject()
{
	return CThread::s_synchronicityList.GetAt(m_runtimeSynchronizationObjectPosition);
}

void CThread::RegisterRuntimeSynchronization()
{
	if (m_bIsSynchronized)
	{
		THREAD_SYNCHRONICITY runtimeSynchronizationObject;
		if (!FindRuntimeSynchronizationObject())
		{
			ResetSynchronizationObject(runtimeSynchronizationObject);
			runtimeSynchronizationObject.strThreadHandlerClassName = m_strThreadHandlerClassName;
			runtimeSynchronizationObject.dwCountOfRunningThreads++;
			runtimeSynchronizationObject.pCriticalSection = new CRITICAL_SECTION;
			m_runtimeSynchronizationObjectPosition = CThread::s_synchronicityList.AddTail(runtimeSynchronizationObject);
			::InitializeCriticalSection(runtimeSynchronizationObject.pCriticalSection);
		}
		else
		{
			runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
			runtimeSynchronizationObject.dwCountOfRunningThreads++;
			UpdateRuntimeSynchronizationObject(runtimeSynchronizationObject);
		};
	};
}

void CThread::UnregisterRuntimeSynchronization()
{
	if (m_bIsSynchronized)
	{
		if (m_runtimeSynchronizationObjectPosition != NULL)
		{
			THREAD_SYNCHRONICITY runtimeSynchronizationObject;
			runtimeSynchronizationObject = GetRuntimeSynchronizationObject();

			if (runtimeSynchronizationObject.dwCountOfRunningThreads > 1)
			{
				runtimeSynchronizationObject.dwCountOfRunningThreads--;
				UpdateRuntimeSynchronizationObject(runtimeSynchronizationObject);
			}
			else
			{
				::DeleteCriticalSection(runtimeSynchronizationObject.pCriticalSection);
				delete runtimeSynchronizationObject.pCriticalSection;
				DeleteRuntimeSynchronizationObject();
				m_runtimeSynchronizationObjectPosition = NULL;
			};
		};
	};
}
// End of Object-specific Synchronizing helper methods //////////////////////

// Lock critical code used in the main 'ThreadHandler' overriden method in the derived class.
// @mfunc void | CThread | Lock | Marks the beginning of the critical code to be
// 'Thread-Handler-Oriented' synchronized. This special synchronization mechanism
// allows to lock the critical code and make it exclusive for the first thread
// reaching this method. Consequently all other CThread objects that operate on the same
// <mf CThread::ThreadHandler> are blocked until the thread unlocks the critical code.
// Other threads operating on the different <mf CThread::ThreadHandler> are not blocked and are
// synchronized in exactly same way in their own group. Thus, CThreads objects can be
// splitted into the groups operating on the same <mf CThread::ThreadHandler> method. Each group
// is synchronized independently to each other.
// <nl>All managing concerning this kind of synchronization is done automatically, users do not
// care about any aspect of synchronization. All they have to do is to use the Lock() and <mf CThread::Unlock>
// methods to bound the critical code.
// <nl>Thread-Handler-Oriented synchronization is, however, not always usable. If the user needs to lock
// the shared common object that cannot be accessed simultaneously under any circumstances,
// he should use <mf CThread::ProcessLock> and <mf CThread::ProcessUnlock> methods. These methods guarantee
// the process-exclusive access to the critical code (but not an inter-process exclusive access).
// <nl>Lock() method must be followed by <mf CThread::Unlock> method in a way to prevent eventual deadlocks.
// <nl><nl>This kind of synchronization can be established by adding SUPPORT_THREAD_SYNCHRONIZATION(<ClassName>) macro
// to the user CThread-derived class constructor in which <mf CThread::ThreadHandler> method is implemented.
// <nl><nl>Important note:
// <nl>Both Lock() and Unlock() methods may be called from within the appropriate CThread thread
// only (represented by the ThreadHandler() method body). The methods should not be publiced
// and cannot be delegated to other threads - otherwise unpredictable deadlocks may arise.
// @xref <mf CThread::Unlock>
// <nl><mf CThread::ProcessLock>
// <nl><mf CThread::ProcessUnlock>
void CThread::Lock()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_bIsSynchronized && m_runtimeSynchronizationObjectPosition != NULL)
	{
		THREAD_SYNCHRONICITY runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		::EnterCriticalSection(runtimeSynchronizationObject.pCriticalSection);
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	};
}

// Unlock critical code used in the main 'ThreadHandler' overriden method in the derived class.
// @mfunc void | CThread | Unlock | Marks the end of the critical code in
// Thread-Handler-Oriented synchronization mode. This method must be preceded by
// <mf CThread::Lock> method.
// <nl><nl>Important note:
// <nl>Both Lock() and Unlock() methods may be called from within the appropriate CThread thread
// only (represented by the ThreadHandler() method body). The methods should not be publiced
// and cannot be delegated to other threads - otherwise unpredictable deadlocks may arise.
// @xref <mf CThread::Lock>
void CThread::Unlock()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_bIsSynchronized && m_runtimeSynchronizationObjectPosition != NULL)
	{
		THREAD_SYNCHRONICITY runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		::LeaveCriticalSection(runtimeSynchronizationObject.pCriticalSection);
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	};
}

// Set WINDOWS-Thread specific attributes.
// @mfunc void | CThread | SetAttributes | Sets the WINDOWS thread security attributes
// (see WINDOWS Threads in Microsoft MSDN documentation).
// <nl>Thread attributes - if necessary - should be set before CThread thread is started.
// @parmopt LPSECURITY_ATTRIBUTES | lpThreadAttributes | NULL | [in] Pointer to the security attributes structure.
// @flag SECURITY_ATTRIBUTES structure may be created temporarily. Passing its pointer
// to this method means copying the structure contents to the internal data space of CThread
// object. Therefore, thread attributes remain valid regardless the SECURITY_ATTRIBUTES structure (which
// 'lpThreadAttributes' parameter points to) exists or not.
// @xref <mf CThread::GetAttributes>
void CThread::SetAttributes(LPSECURITY_ATTRIBUTES lpThreadAttributes /*= NULL*/)
{
	m_lpThreadAttributes = lpThreadAttributes;
	if (m_lpThreadAttributes != NULL)
	{
		m_ThreadAttributes = *m_lpThreadAttributes;
		m_lpThreadAttributes = &m_ThreadAttributes;
	};
}

// Get the current WINDOWS-Thread handler
// @mfunc HANDLE | CThread | GetHandle | Gets the WINDOWS thread handle
// (see WINDOWS Threads in Microsoft MSDN documentation).
// @rdesc
// Handle of WINDOWS thread or NULL if the thread is not created.
HANDLE CThread::GetHandle() const
{
	return m_hThreadHandle;
}

// Get the current WINDOWS-Thread ID
// @mfunc DWORD | CThread | GetID | Gets the WINDOWS thread ID
// (see WINDOWS Threads in Microsoft MSDN documentation).
// @rdesc
// WINDOWS thread ID or 0 if the thread is not created.
DWORD CThread::GetID() const
{
	return m_dwThreadID;
}

// Get the current WINDOWS-Thread security attributes
// @mfunc SECURITY_ATTRIBUTES | CThread | GetAttributes | Gets the WINDOWS thread security attributes
// (see WINDOWS Threads in Microsoft MSDN documentation).
// @rdesc
// Fills up the SECURITY_ATTRIBUTES structure with valid data.
// If the WINDOWS thread is not created the SECURITY_ATTRIBUTES structure is null-reset.
// @xref <mf CThread::SetAttributes>
SECURITY_ATTRIBUTES CThread::GetAttributes() const
{
	return m_ThreadAttributes;
}

// Set WINDOWS-Thread stack size
// @mfunc void | CThread | SetStackSize | Sets the WINDOWS thread stack size
// (see WINDOWS Threads in Microsoft MSDN documentation).
// <nl>Thread stack size - if necessary - should be set before CThread thread is started.
// @parmopt DWORD | dwStackSize | 0 | [in] Desired WINDOWS thread stack size.
// @xref <mf CThread::GetStackSize>
void CThread::SetStackSize(DWORD dwStackSize /*= 0*/)
{
	m_dwStackSize = dwStackSize;
}

// Get the current WINDOWS-Thread stack size
// @mfunc DWORD | CThread | GetStackSize | Gets the WINDOWS thread stack size
// (see WINDOWS Threads).
// @rdesc
// WINDOWS thread stack size.
// @xref <mf CThread::SetStackSize>
DWORD CThread::GetStackSize() const
{
	return m_dwStackSize;
}

// Set the Thread activity status (see: Protected 'enum {}' values in 'CThread.h')
// @mfunc void | CThread | SetActivityStatus | Sets CThread activity status.
// CThread activity status describes the current CThread activity.
// This method should be meaningfully used in the <mf CThread::ThreadHandler> CThread-derived class method.
// to inform the owner thread about the current CThread object activity.
// Owner thread may call <mf CThread::GetActivityStatus> method to restore the current status.
// <nl>CThread class offers the predefined values as seen in the 'Parameters' section.
// <nl><nl>For more information how to use this method see 'Developer.doc' documentation.
// @parm int | nActivityStatus | [in] CThread activity status.
// @flag CThread::THREAD_CREATED  | Thread was successfully created (activity status set
// by the Start() method).
// @flag CThread::THREAD_STOPPED  | Thread is stopped.
// @flag CThread::THREAD_RUNNING  | Thread is running.
// @flag CThread::THREAD_PAUSED  | Thread is paused.
// @flag CThread::THREAD_CONTINUING  | Thread is continuing.
// @flag CThread::THREAD_PENDING  | Thread is pending.
// @flag CThread::THREAD_USER_ACTIVITY  | Base offset for user-defined activity statuses.
// @xref <mf CThread::GetActivityStatus>
void CThread::SetActivityStatus(int nActivityStatus)
{
	m_nActivityStatus = nActivityStatus;
}

// Get the current Thread activity status (see: Protected 'enum {}' values in 'CThread.h')
// User-defined Activity Status values in range: CThread::THREAD_USER_ACTIVITY and higher
// @mfunc int | CThread | GetActivityStatus | Gets the current CThread activity status.
// This method is normally called from within the owner thread to obtain the current
// activity of the owned thread.
// <nl>CThread class offers the predefined values as seen in the 'Return Value' section.
// @rdesc
// Current CThread activity status.
// @flag CThread::THREAD_CREATED  | Thread was successfully created (activity status set
// by the Start() method).
// @flag CThread::THREAD_STOPPED  | Thread is stopped.
// @flag CThread::THREAD_RUNNING  | Thread is running.
// @flag CThread::THREAD_PAUSED  | Thread is paused.
// @flag CThread::THREAD_CONTINUING  | Thread is continuing.
// @flag CThread::THREAD_PENDING  | Thread is pending.
// @flag CThread::THREAD_USER_ACTIVITY  | Base offset for user-defined activity statuses.
// @xref <mf CThread::SetActivityStatus>
int CThread::GetActivityStatus() const
{
	return m_nActivityStatus;
}

// Wait for Activity Status
// @mfunc BOOL | CThread | WaitForActivityStatus | Waits until the desired CThread activity
// status is reached. Used in the owner thread.
// <nl>This is a "good-servant-but-bad-master" method. The owner thread may fire
// an arbitrary command to the CThread object by the <mf CThread::PostCommand> method.
// That means, the <mf CThread::PostCommand> method fires a command and returns immediately.
// However, in some cases the owner thread may want to wait until the command is
// actually handled. For this reason the process may use this method which waits until
// the desired activity status is set in the <mf CThread::ThreadHandler> method.
// In this case the user is responsible to set the desired activity status in the
// <mf CThread::ThreadHandler> by the <mf CThread::SetActivityStatus> method.
// <nl>Using of this method requires an implementation of the proper 'set-thread-activity-status'
// strategy. If, for example, the desired activity status is not properly set or is immediately
// rewritten by another value, the desired status is consequently never reached and
// the WaitForActivityStatus() method hangs. Sometimes the thread-synchronization locking
// mechanism is necessary.
// <nl>WaitForActivityStatus() method returns only in the case when the desired activity status
// was actually reached or timeout interval elapsed.
// <nl><nl>Note:
// <nl>The Start() and Stop() methods do not have to be checked by this method. These methods
// are executed synchronously and return when the CThread-thread actually starts or stops.
// <nl><nl>Important note:
// <nl>If the CThread thread utilizes the main application message queue be aware of using
// this method. WaitForActivityStatus() method blocks the application thread from which is called
// and may not allow the CThread thread to complete its task requiring the message queue handling.
// This may lead to a deadlock. For more information see 'Developers.doc' documentation.
// @parm int | nActivityStatus | [in] Desired CThread activity status that is to be reached.
// @parmopt DWORD | dwTimeout | CThread::DW_INFINITE | [in] Timeout interval in tenths of second.
// @rdesc
// TRUE if the desired acivity status is reached; FALSE if the timeout elapsed OR
// the thread has been prematurely terminated before the desired status was reached.
// Developers should always check this return value if there is no an explicit
// guaranty about the thread's lifetime.
// @xref <mf CThread::SetActivityStatus>
// <nl><mf CThread::PostCommand>
// <nl><mf CThread::ThreadHandler>
BOOL CThread::WaitForActivityStatus(int nActivityStatus, DWORD dwTimeout /*= CThread::DW_INFINITE*/) const
{
	DWORD dwCount = 0, dwMaxCount = 0;
	dwMaxCount = (dwTimeout * 100) / CThread::BASE_DELAY_INTERVAL;

	while (m_nActivityStatus != nActivityStatus	&&
		   m_hThreadHandle != NULL				&&
		   (dwTimeout == INFINITE || dwCount++ < dwMaxCount))
	{
		::Sleep(CThread::BASE_DELAY_INTERVAL);
	};

	return (BOOL)(m_nActivityStatus == nActivityStatus);
}

// @mfunc DWORD | CThread | SetPriority |
// This method sets the WINDOWS thread priority. The priority may be set after
// the WINDOWS thread has been started.
// <nl>SetPriority() just encapsulates the WINDOWS SetThreadPriority() function.
// For more information see Win32 SDK Programmer’s Reference.
// @rdesc
// TRUE - the priority was properly set.
// <nl>FALSE - the priority was not set or the thread is not runnning.
// @parmopt int | nPriority | THREAD_PRIORITY_NORMAL | [in] WINDOWS thread priority.
// Can be one of the following:
// <nl><nl>THREAD_PRIORITY_NORMAL
// <nl>THREAD_PRIORITY_ABOVE_NORMAL
// <nl>THREAD_PRIORITY_BELOW_NORMAL
// <nl>THREAD_PRIORITY_HIGHEST
// <nl>THREAD_PRIORITY_IDLE
// <nl>THREAD_PRIORITY_LOWEST
// <nl>THREAD_PRIORITY_TIME_CRITICAL
// @xref <mf CThread::GetPriority>
BOOL CThread::SetPriority(int nPriority /*= THREAD_PRIORITY_NORMAL*/)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_hThreadHandle != NULL)
	{
		BOOL bResult = ::SetThreadPriority(m_hThreadHandle, nPriority);
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return bResult;
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return FALSE;
	};
}

// @mfunc int | CThread | GetPriority |
// This method gets the WINDOWS thread priority.
// <nl><nl>GetPriority() just encapsulates the WINDOWS GetThreadPriority() function.
// For more information see Win32 SDK Programmer’s Reference.
// @rdesc
// Current WINDOWS thread priority or THREAD_PRIORITY_ERROR_RETURN if an error occurs.
// Can be one of the following:
// <nl><nl>THREAD_PRIORITY_NORMAL
// <nl>THREAD_PRIORITY_ABOVE_NORMAL
// <nl>THREAD_PRIORITY_BELOW_NORMAL
// <nl>THREAD_PRIORITY_HIGHEST
// <nl>THREAD_PRIORITY_IDLE
// <nl>THREAD_PRIORITY_LOWEST
// <nl>THREAD_PRIORITY_TIME_CRITICAL
// @xref <mf CThread::SetPriority>
int CThread::GetPriority() const
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_hThreadHandle != NULL)
	{
		int nPriority = ::GetThreadPriority(m_hThreadHandle);
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return nPriority;
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return THREAD_PRIORITY_ERROR_RETURN;
	};
}

void CThread::StoreThreadExitCode()
{
	DWORD dwThreadExitCode;
	if (m_hThreadHandle != NULL && ::GetExitCodeThread(m_hThreadHandle, &dwThreadExitCode))
		m_dwThreadExitCode = dwThreadExitCode;
}

// Get the current WINDOWS Thread exit code
// @mfunc DWORD | CThread | GetExitCode | Gets CThread thread exit code -
// a value that is returned by <mf CThread::ThreadHandler> method - or, generally, it's a
// return value of the thread controlling function.
// <nl>GetExitCode() method returns the valid exit code regardless the WINDOWS
// thread is alive or not.
// @rdesc
// CThread thread exit code.
DWORD CThread::GetExitCode() const
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	DWORD dwThreadExitCode;
	if (m_hThreadHandle == NULL || !::GetExitCodeThread(m_hThreadHandle, &dwThreadExitCode))
		dwThreadExitCode = m_dwThreadExitCode;
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
	return dwThreadExitCode;
}

// Post the Thread Command (internal version)
BOOL CThread::PostThreadCommand(int nCommand, CString& strError)
{
	strError.Empty();
	if (m_bSupportSignalNotification	&&
		m_hSignalObject != NULL			&&
		nCommand != CThread::CMD_NONE	)
	{
		if (m_nCommandList.GetSize() > 0 &&
			m_nCommandList.GetAt(m_nCommandList.GetSize() - 1) == (UINT)nCommand)
			return TRUE;

		try
		{
			m_nCommandList.Add((UINT)nCommand);
			if (!::SetEvent(m_hSignalObject))
			{
				strError = CThreadException::GetLastSystemErrorMsg(::GetLastError());
				return FALSE;
			}
			else
				return TRUE;
		}
		catch (...)
		{
			return FALSE;
		};
	}
	else
		return TRUE;
}

// Post the Thread Command (public version)
// User-defined Command values in range: <CMD_USER_COMMAND - MAX_INT> (0 - 7 are reserved)
// @mfunc void | CThread | PostCommand |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>PostCommand() method is the base method with which the owner thread may manage
// notificable CThread objects. By calling PostCommand() the owner thread fires desired commands
// to the thread belonging to CThread object. The thread consequently receives a signal to leave <mf CThread::WaitForNotification>
// method which is used in the <mf CThread::ThreadHandler> method (implemented in CThread-derived class) and restores the command fired
// from the owner thread. Obtained command is immediately executed in the thread body.
// Developer is responsible to handle the fired command in the <mf CThread::ThreadHandler> method.
// PostCommand() mechanism is the recommended way how to manage CThread objects. It's also the base
// concept for other command-oriented methods like Start(), Pause(), Continue(), Reset() or Stop().
// Each of these methods sets the appropriate command and sends a signal to the thread
// which handles the command. Using this paradigm the thread notifications
// coming from outside keep the synchronization features provided by CThread class.
// <nl>PostCommand() method supports so-called 'stackable commands' which allows the thread-owner
// process to pump all desired commands at one step. All such commands will be resolved
// in the thread task body in exactly the same order as they were pumped in the owner thread
// (cyclic stack mechanism).
// <nl>User may define an arbitrary count of user-specific commands. For this purpose the CThread
// class offers the start offset command ID: CThread::CMD_USER_COMMAND. All command IDs below
// this value is reserved by CThread class and should not be used. In this case
// the user is responsible to handle the user-specific command in the <mf CThread::ThreadHandler> method in the
// CThread-derived class.
// <nl><nl>This method is valid only if CThread-derived class supports Thread Notification. Thread
// Notification may be established by adding SUPPORT_THREAD_NOTIFICATION macro in the CThread-derived
// class constructor in which <mf CThread::ThreadHandler> method is actually implemented.
// Otherwise PostCommand() method has no any effect.
// <nl>This method is usable after the CThread thread has been successfully started.
// <nl><nl>PostCommand() returns immediately after the command has been actually fired.
// The owner thread may, however, wait for completion of the task corresponding
// to the fired command (implemented in the <mf CThread::ThreadHandler> method) by using
// the paradigm described in the <mf CThread::WaitForActivityStatus> method.
// <nl><nl>Detailed information how to use this method as well as how to manage fired commands in the
// thread task body can be found in the 'Developer.doc' documentation.
// @parm int | nCommand | [in] Desired command fired from within the owner thread
// that is to be executed in CThread task body - <mf CThread::ThreadHandler>.
// @xref <mf CThread::WaitForNotification>
// <nl><mf CThread::WaitForActivityStatus>
// <nl><mf CThread::HandleCommandImmediately>
// <nl><t CThread Predefined Commands>
void CThread::PostCommand(int nCommand)
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	CString strError;
	if (m_hThreadHandle != NULL && !PostThreadCommand(nCommand, strError))
	{
		CThreadException* pe = new CThreadException(this, strError, CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT);
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		throw pe;
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	};
}

// Cancel all notification commands waiting in the process-queue
// @mfunc void | CThread | ResetCommands | Cancels all thread-notification commands
// fired by the <mf CThread::PostCommand> method and waiting in the queue to be processed.
// <nl>This method is useful when the last important command is intended to be sent
// to the CThread object. To ensure that no any other command is to be processed,
// the owner thread may cancel all such commands pending in the CThread command
// queue.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForNotification>
void CThread::ResetCommands()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	m_nCommandList.RemoveAll();
	m_nCommandList.FreeExtra();
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

// @mfunc void | CThread | HandleCommandImmediately |
// This helper method is used for immediate sending of CThread commands fired from within
// the <mf CThread::ThreadHandler> method in the actual Notificable CThread thread.
// <nl><nl>In Notificable CThread threads the <mf CThread::ThreadHandler> method contains
// the 'case' switch in which incoming commands are handled. In some cases the resolved
// and executed command has to immediately invoke (and handle) another internal command in this 'case' switch
// to properly complete its task. Users should not use the <mf CThread::PostCommand> oriented methods
// in such case because the command queue may not be empty. This queue may be namely filled up
// by another thread and, thus, an additional internal completion command will be just posted at
// the end of the queue. In consequence, the next handled command will be the first pending
// in the queue and not that one intended to be handled immediately.
// <nl>For this reason a special command-handling mechanism is desired and is supported
// by this method. Requested internal command to be handled immediately is stored in the
// standard CThread command queue as the first pending command bypassing all already stored commands.
// Restoring of internal commands is accomplished by the same method as other standard
// commands, by the <mf CThread::WaitForNotification> method. The difference is that an internal
// command is handled always as the first command.
// <nl><nl>As an example we may consider the starting of a notificable CThread thread.
// After starting the thread the CMD_INITIALIZE command is fired as the first command. This command
// is handled in the corresponding 'case' branch in the <mf CThread::ThreadHandler> method,
// in which the basic initialization is accomplished. As the next logical step after
// the initialization is to get run the main thread task immediately. Thus, before
// leaving the initialization 'case' branch the HandleCommandImmediately(CMD_RUN) method is called.
// CMD_RUN command fired in such manner bypasses all pending commands and is returned
// (via the <mf CThread::WaitForNotification> method) back to the 'case' switch as the following command.
// All pending commands will be resolved afterwards.
// <nl><nl>The term 'internal commands' means just another kind of firing and handling of standard commands.
// Users use the same commands (more precisely, command IDs) as in the <mf CThread::PostCommand> method.
// <nl><nl>This method is valid only if CThread-derived class supports Thread Notification
// and the CThread thread has been successfully started. Otherwise it has no any effect.
// <nl><nl>Important note:
// <nl>This method should be called only in the CThread thread (in the <mf CThread::ThreadHandler> method).
// @parm int | nCommand | [in] Desired command to be handled immediately.
// @rdesc
// TRUE if the command was inserted in the command queue.
// @xref <mf CThread::ThreadHandler>
// <nl><mf CThread::PostCommand>
// <nl><mf CThread::WaitForNotification>
BOOL CThread::HandleCommandImmediately(int nCommand)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_hThreadHandle != NULL		 &&
		m_bSupportSignalNotification &&
		nCommand != CMD_NONE			)
	{
		try
		{
			m_nCommandList.InsertAt(0, nCommand);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return TRUE;
		}
		catch (...)
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return FALSE;
		};
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return FALSE;
	};
}

// User-defined Command values in range: 6 and higher
BOOL CThread::ReceiveCommand(int& nIncomingCommand)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	nIncomingCommand = CThread::CMD_NONE;
	if (m_bSupportSignalNotification && m_hSignalObject != NULL)
	{
		if (m_nCommandList.GetSize() > 0)
		{
			nIncomingCommand = (int)m_nCommandList.GetAt(0);
			m_nCommandList.RemoveAt(0);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return TRUE;
		}
		else
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return FALSE;
		};
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return FALSE;
	};
}

BOOL CThread::RegisterNotificationObject(CString& strError)
{
	if (m_bSupportSignalNotification && m_hSignalObject == NULL)
	{
		if ((m_hSignalObject = ::CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
		{
			strError = CThreadException::GetLastSystemErrorMsg(::GetLastError());
			return FALSE;
		}
		else
			return TRUE;
	}
	else
		return TRUE;
}

void CThread::UnregisterNotificationObject()
{
	if (m_bSupportSignalNotification && m_hSignalObject != NULL)
	{
		::CloseHandle(m_hSignalObject);
		m_hSignalObject = NULL;
	};
}

// Wait until thread is notified or timeout interval (in miliseconds) elapses
// @mfunc void | CThread | WaitForNotification | The main <mf CThread::ThreadHandler> notification
// method. This method must be implemented inside the <mf CThread::ThreadHandler> method for Notificable CThread threads
// (see 'Developer.doc' documentation).
// <nl>The method waits for incoming notifications (commands) fired from the
// owner thread via <mf CThread::PostCommand> method and returns immediately after the command was received.
// Returned command has to be handled in <mf CThread::ThreadHandler> method.
// <nl>User may, however, set the timeout interval which forces the method to return after the timeout interval elapses.
// <nl><nl>This method is valid only if CThread-derived class supports Thread Notification.
// Thread Notification can be established by adding SUPPORT_THREAD_NOTIFICATION macro in CThread-derived
// class constructor in which <mf CThread::ThreadHandler> method is actually implemented.
// Otherwise it has no any effect and the method returns immediately.
// <nl>This method is usable after the CThread thread has been successfully started.
// <nl><nl>Detailed information how to use this method as well as how to manage fired commands in the
// thread task handler can be found in the 'Developer.doc' documentation.
// @parm int& | nIncomingCommand | [out] Reference to the Command ID that was fired from within
// the owner thread.
// @parmopt DWORD | dwDefaultTimeout | CThread::DW_INFINITE | [in] Timeout interval in 'miliseconds'.
// @xref <mf CThread::PostCommand>
// <nl><t CThread Predefined Commands>
void CThread::WaitForNotification(int& nIncomingCommand, DWORD dwDefaultTimeout /*= CThread::DW_INFINITE*/)
{
	if (m_bSupportSignalNotification && m_hSignalObject != NULL)
	{
		DWORD dwEvent;
		BOOL bExit = FALSE;

		do
		{
			if (!ReceiveCommand(nIncomingCommand))
			{
				dwEvent = ::WaitForSingleObject(m_hSignalObject, dwDefaultTimeout);

				switch (dwEvent)
				{
				case WAIT_OBJECT_0:
					break;

				case WAIT_TIMEOUT:
					nIncomingCommand = CThread::CMD_TIMEOUT_ELAPSED;
					bExit = TRUE;
					break;

				default:
					break;
				};
			}
			else
				break;
		} while (!bExit);
	}
	else
		nIncomingCommand = CThread::CMD_NONE;
}

// Run the current CThread thread.
// @mfunc void | CThread | Run |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>Fires CThread::CMD_RUN Command and notifies CThread object.
// Used in the owner thread. This method is valid only if CThread-derived class
// supports Thread Notification and CThread thread has been successfully started.
// Otherwise it has no any effect.
// <nl>To use the method properly the <mf CThread::ThreadHandler> method must be able to handle
// CThread::CMD_RUN Command as well as implement the specific task corresponding to this command.
// <nl>This method returns immediately after the command has been fired.
// The owner thread may, however, wait for completion of the corresponding task
// by using the paradigm described in the <mf CThread::WaitForActivityStatus> method.
// <nl><nl>This method is a helper method simplifying the semantic control of Notificable
// CThread threads acting in a 'scheduler' or 'service' - like manner. It's up to the developer's
// responsibility how to interpret and implement (or refuse at all) this method.
// <nl><nl>For more information see 'Developer.doc' documentation.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForActivityStatus>
// <nl><t CThread Predefined Commands>
void CThread::Run()
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	PostCommand(CThread::CMD_RUN);
}

// Pause the current Thread (used in the CThread-derived Class - in the 'ThreadHandler' method)
// @mfunc void | CThread | Pause |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>Fires CThread::CMD_PAUSE Command and notifies CThread object.
// Used in the owner thread. This method is valid only if CThread-derived class
// supports Thread Notification and CThread thread has been successfully started.
// Otherwise it has no any effect.
// <nl>To use the method properly the <mf CThread::ThreadHandler> method must be able to handle
// CThread::CMD_PAUSE Command as well as implement the specific task corresponding to this command.
// <nl>This method returns immediately after the command has been fired.
// The owner thread may, however, wait for completion of the corresponding task
// by using the paradigm described in the <mf CThread::WaitForActivityStatus> method.
// <nl><nl>This method is a helper method simplifying the semantic control of Notificable
// CThread threads acting in a 'scheduler' or 'service' - like manner. It's up to the developer's
// responsibility how to interpret and implement (or refuse at all) this method.
// <nl><nl>For more information see 'Developer.doc' documentation.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForActivityStatus>
// <nl><t CThread Predefined Commands>
void CThread::Pause()
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	PostCommand(CThread::CMD_PAUSE);
}

// Pause the current Thread (used in the CThread-derived Class - in the 'ThreadHandler' method)
// @mfunc void | CThread | Continue |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>Fires CThread::CMD_CONTINUE Command and notifies CThread object.
// Used in the owner thread. This method is valid only if CThread-derived class
// supports Thread Notification and CThread thread has been successfully started.
// Otherwise it has no any effect.
// <nl>To use the method properly the <mf CThread::ThreadHandler> method must be able to handle
// CThread::CMD_CONTINUE Command as well as implement the specific task corresponding to this command.
// <nl>This method returns immediately after the command has been fired.
// The owner thread may, however, wait for completion of the corresponding task
// by using the paradigm described in the <mf CThread::WaitForActivityStatus> method.
// <nl><nl>This method is a helper method simplifying the semantic control of Notificable
// CThread threads acting in a 'scheduler' or 'service' - like manner. It's up to the developer's
// responsibility how to interpret and implement (or refuse at all) this method.
// <nl><nl>For more information see 'Developer.doc' documentation.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForActivityStatus>
// <nl><t CThread Predefined Commands>
void CThread::Continue()
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	PostCommand(CThread::CMD_CONTINUE);
}

// Reset the current Thread (used in the CThread-derived Class - in the 'ThreadHandler' method)
// @mfunc void | CThread | Reset |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>Fires CThread::CMD_RESET Command and notifies CThread object.
// Used in the owner thread. This method is valid only if CThread-derived class
// supports Thread Notification and CThread thread has been successfully started.
// Otherwise it has no any effect.
// <nl>To use the method properly the <mf CThread::ThreadHandler> method must be able to handle
// CThread::CMD_RESET Command as well as implement the specific task corresponding to this command.
// <nl>This method returns immediately after the command has been fired.
// The owner thread may, however, wait for completion of the corresponding task
// by using the paradigm described in the <mf CThread::WaitForActivityStatus> method.
// <nl><nl>This method is a helper method simplifying the semantic control of Notificable
// CThread threads acting in a 'scheduler' or 'service' - like manner. It's up to the developer's
// responsibility how to interpret and implement (or refuse at all) this method.
// <nl><nl>For more information see 'Developer.doc' documentation.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForActivityStatus>
// <nl><t CThread Predefined Commands>
void CThread::Reset()
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	PostCommand(CThread::CMD_RESET);
}

// Check if the current Thread is still alive (internal version)
BOOL CThread::IsThreadAlive()
{
	if (m_hThreadHandle != NULL && ::GetExitCodeThread(m_hThreadHandle, &m_dwThreadExitCode))
		return (BOOL)(m_dwThreadExitCode == STILL_ACTIVE);
	else
		return FALSE;
}

// Check if the current Thread is still alive (public version)
// @mfunc BOOL | CThread | IsAlive | Checks if the current CThread thread is still alive.
// @rdesc
// TRUE if the thread is alive otherwise FALSE.
BOOL CThread::IsAlive()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (IsThreadAlive())
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return TRUE;
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return FALSE;
	};
}

/////////////////////////////////////////////////////////////////////////////
// Just for AutoDuck purposes...
/////////////////////////////////////////////////////////////////////////////
// @mfunc DWORD | CThread | ThreadHandler |
// Main CThread-handler virtual abstract method declaration.
// <nl><nl>This method is not implemented in the CThread class and must be implemented
// at least at one CThread-derived class in the CThread class hierarchy.
// <nl>ThreadHandler() method concentrates the whole task that CThread thread
// has to execute. The implementation itself varies according to the type of
// CThread thread operating on this method (Trivial or Notificable Threads).
// <nl><nl>For Notificable CThread threads the method contains a main loop with
// the <mf CThread::WaitForNotification> method resolving incoming commands fired
// from the owner thread.
// <nl><nl>Detailed information as well as the examples how to implement, manage and use
// this method for both Trivial and Notificable CThread threads can be found in
// the 'Developer.doc' documentation.
// @rdesc
// Thread task completion exit code. Developers may define an arbitrary exit code here
// except the WINDOWS predefined constant = STILL_ACTIVE (0x00000103L),
// which indicates the thread-is-alive status.
// @xref <mf CThread::PostCommand>
// <nl><mf CThread::WaitForNotification>
// <nl><mf CThread::HandleCommandImmediately>
// DWORD CThread::ThreadHandler(){}

// Main Thread Handler function /////////////////////////////////////////////
DWORD WINAPI CThread::ControllingFunction(LPVOID lpParameter)
{
	DWORD dwExitCode = ((CThread *)lpParameter)->ThreadHandler();
	((CThread *)lpParameter)->ResetThreadObject(dwExitCode);
	return dwExitCode;
}
/////////////////////////////////////////////////////////////////////////////

// Start the current Thread
// @mfunc void | CThread | Start |
// <tab><f throws CThreadException> of types:
// <nl><tab>CThreadException::CANNOT_CREATE_THREAD,
// <nl><tab>CThreadException::THREAD_ALREADY_STARTED,
// <nl><tab>CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT,
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>This method starts the WINDOWS thread connected to CThread object.
// Used in the owner thread. Once established the WINDOWS thread cannot be started
// again until it terminates.
// <nl>Before starting a thread user may set up WINDOWS thread attributes or thread stack size
// if necessary. This can be accomplished by calling the <mf CThread::SetAttributes> or
// <mf CThread::SetStackSize> methods.
// <nl>In notificable threads Start() method fires CThread::CMD_INITIALIZE Command
// immediately after the WINDOWS thread was being established. CThread::CMD_INITIALIZE Command must
// be handled in the <mf CThread::ThreadHandler> method.
// <nl><nl>This method is a synchronous method. It returns only if the WINDOWS thread has been
// successfully started or some significant error occurs. In this case the method returns
// immediately by throwing the appropriate CThreadException exception.
// @xref <mf CThread::Stop>
// <nl><mf CThread::SetAttributes>
// <nl><mf CThread::SetStackSize>
// <nl><mf CThread::PostCommand>
// <nl><mf CThread::WaitForNotification>
void CThread::Start()
//	throws CThreadException of types: CThreadException::CANNOT_CREATE_THREAD,
//									  CThreadException::THREAD_ALREADY_STARTED,
//									  CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT,
//									  CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (!IsThreadAlive())
	{
		CString strError;

		ResetThreadRuntimeData();

		if (!RegisterNotificationObject(strError))
		{
			CThreadException* pe = new CThreadException(this, strError, CThreadException::CANNOT_CREATE_NOTIFICATION_OBJECT);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			throw pe;
		};

		RegisterRuntimeSynchronization();
		m_hThreadHandle = ::CreateThread(m_lpThreadAttributes,
										 m_dwStackSize,
										 &ControllingFunction,
										 this,
										 0,
										 &m_dwThreadID);
		if (m_hThreadHandle != NULL)
		{
			if (!PostThreadCommand(CThread::CMD_INITIALIZE, strError))
			{
				::TerminateThread(m_hThreadHandle, (DWORD)CThread::DW_ERROR);
				::CloseHandle(m_hThreadHandle);
				UnregisterRuntimeSynchronization();
				ResetThreadRuntimeData();
				CThreadException* pe = new CThreadException(this, strError, CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT);
				// Unlock ///////////////////////////////////////////////////////
				INTERNAL_UNLOCK
				/////////////////////////////////////////////////////////////////
				throw pe;
			}
			else
			{
				SetActivityStatus(CThread::THREAD_CREATED);
				// Unlock ///////////////////////////////////////////////////////
				INTERNAL_UNLOCK
				/////////////////////////////////////////////////////////////////
				return;
			};
		}
		else
		{
			CThreadException* pe = new CThreadException(this, CThreadException::GetLastSystemErrorMsg(::GetLastError()), CThreadException::CANNOT_CREATE_THREAD);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			throw pe;
		};
	}
	else
	{
		CThreadException* pe = new CThreadException(this, CThreadException::s_strERROR_THREAD_ALREADY_STARTED, CThreadException::THREAD_ALREADY_STARTED);
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		throw pe;
	};
}

// Stop the current running Thread
// Parameter: dwTimeout - in 'Seconds'
// @mfunc BOOL | CThread | Stop |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
// <nl><nl>This method stops the WINDOWS running thread connected to CThread object.
// Used in the owner thread.
// In notificable threads Stop() method fires CThread::CMD_STOP Command
// immediately after the WINDOWS thread was asked to be stopped. CThread::CMD_STOP Command must
// be handled in <mf CThread::ThreadHandler> method to properly terminate the thread.
// If CThread object does not support Thread Notification, Stop() will wait until
// the WINDOWS thread actually terminates.
// In both modes the method returns only in the case when the WINDOWS thread actually terminates,
// the timeout interval elapses or some significant error occurs. Otherwise it waits (synchronous stopping).
// When an immediate return is required the user may set 'dwTimeout' variable to zero.
// In such case, however, the user is responsible to find out if the thread actually runs or is already stopped.
// @parm DWORD& | dwExitCode | [out] WINDOWS thread exit code.
// @parmopt DWORD | dwTimeout | CThread::DW_INFINITE | [in] Timeout interval in tenths of second.
// @rdesc Stop return status
// @flag TRUE | WINDOWS thread was properly stopped.
// @flag FALSE | WINDOWS thread was not stopped after the timeout interval elapsed.
// @xref <mf CThread::Start>
// <nl><mf CThread::PostCommand>
// <nl><mf CThread::WaitForNotification>
BOOL CThread::Stop(DWORD& dwExitCode, DWORD dwTimeout /*= CThread::DW_INFINITE*/)
//	throws CThreadException of type: CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (IsThreadAlive())
	{
		CString strError;
		int nAttemption = 0, nMaxAttemptions;
		nMaxAttemptions = (dwTimeout != (DWORD)CThread::DW_INFINITE) ? ((int)dwTimeout * 100)/CThread::BASE_DELAY_INTERVAL : -1;

		if (!PostThreadCommand(CThread::CMD_STOP, strError))
		{
			dwExitCode = m_dwThreadExitCode;
			CThreadException* pe = new CThreadException(this, strError, CThreadException::CANNOT_SIGNAL_NOTIFICATION_OBJECT);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			throw pe;
		}
		else
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
		};

		while (IsAlive() && (nMaxAttemptions == -1 || nAttemption++ < nMaxAttemptions))
		{
			::Sleep(CThread::BASE_DELAY_INTERVAL);
		};

		// Lock /////////////////////////////////////////////////////////////
		INTERNAL_LOCK
		/////////////////////////////////////////////////////////////////////
		dwExitCode = m_dwThreadExitCode;
		if (m_dwThreadExitCode != STILL_ACTIVE)
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return TRUE;
		}
		else
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return FALSE;
		};
	}
	else
	{
		if (m_hThreadHandle != NULL)
		{
			StoreThreadExitCode();
			::CloseHandle(m_hThreadHandle);
			UnregisterRuntimeSynchronization();
		};

		dwExitCode = m_dwThreadExitCode;
		ResetThreadRuntimeData();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return TRUE;
	};
}

// @mfunc void | CThread | OnKill |
// Virtual method that is invoked while the <mf CThread::Kill> method is being executed.
// OnKill() is called after the WINDOWS thread has been actually destroyed.
// Users may unallocate all extra resources that were needed in the CThread-derived instance object.
// <nl>Default version does nothing users may, however, implement this method in their CThread-derived class.
// <nl>All extra resources should be referenced through CThread-derived class member data,
// because in the moment of OnKill() execution all local variables in the <mf CThread::ThreadHandler> method
// are not more valid - thread is already destroyed and its controlling function is detached.
// <nl>OnKill() virtual method doesn't have to call the base CThread::OnKill() method.
// <nl><nl>Note 1:
// <nl>Users should unallocate (detach, close...) resources that rely only to the
// current instance of CThread-derived object that is being killed. Keep in mind that in some cases
// the same resources may be used by other running instances as well. In this situation the
// user is responsible to clean up such shared resources.
// <nl><nl>Note 2:
// <nl>OnKill() method doesn't have to be invoked under any circumstances. If the thread
// regularly finished before the <mf CThread::Kill> method has been called the <mf CThread::Kill>
// method does nothing, thus, OnKill() method is not invoked.
// OnKill() is normally used as a last chance emergency clean-up.
// @xref <mf CThread::Kill>
// <nl><mf CThread::ThreadHandler>
void CThread::OnKill()
{
	// Does nothing by default //////////////////////////////////////////////
}

// Kill the current running Thread (used in emergency cases only!)
// @mfunc void | CThread | Kill |
// <tab><f throws CThreadException> of type:
// <nl><tab>CThreadException::CANNOT_TERMINATE_THREAD
// <nl><nl>This method kills the WINDOWS thread connected to CThread object.
// Used in the owner thread.
// The method returns after the WINDOWS thread has been actually killed, or some significant error occurs.
// <nl>CThread threads should always terminate either by leaving the thread-controlling function attached
// to the WINDOWS thread or by calling <mf CThread::Stop> method in notificable threads.
// <nl>Killing threads is the last-chance stopping mechanism and should be used in emergency
// cases only. While killing the thread by using this method the <mf CThread::OnKill> virtual method
// is invoked to provide the last chance for making necessary unallocations specific to the
// thread being killed.
// <nl><nl>For more information see 'Terminating WINDOWS Threads' in Microsoft MSDN documentation.
// @parmopt DWORD | dwExitCode | CThread::DW_OK | [in] Suggested WINDOWS thread exit code.
// (see 'TerminateThread()' WINDOWS function in Microsoft MSDN documentation).
// @parmopt BOOL | bCloseAnyway | FALSE | [in] Closes the CThread-thread regardless the thread
// has been destroyed or not. By using this parameter the CThread-thread is correctly closed and
// unregistered even if the corresponding WINDOWS thread cannot be properly terminated. Users should call
// this method again (using 'bCloseAnyway = TRUE') if it's not possible to recover the termination
// failure - best way is to call it in the 'catch' clause for an exception thrown by this method.
// By enabling this parameter no any CThreadException exception is thrown.
// @xref <mf CThread::OnKill>
// <nl><mf CThread::Stop>
void CThread::Kill(DWORD dwExitCode /*= CThread::DW_OK*/, BOOL bCloseAnyway /*= FALSE*/)
//	throws CThreadException of type: CThreadException::CANNOT_TERMINATE_THREAD
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (IsThreadAlive() || m_hThreadHandle != NULL)
	{
		BOOL bIsTerminated = TRUE;
		DWORD dwError = ERROR_SUCCESS;

		if (m_hThreadHandle != NULL) bIsTerminated = ::TerminateThread(m_hThreadHandle, dwExitCode);
		if (!bIsTerminated) dwError = ::GetLastError();

		StoreThreadExitCode();

		if (bIsTerminated || bCloseAnyway)
		{
			// the thread has been successfully destroyed...
			// or ignore the terminate-thread operation at all
			if (bCloseAnyway) m_dwThreadExitCode = dwExitCode;
			if (m_hThreadHandle != NULL) ::CloseHandle(m_hThreadHandle);
			UnregisterRuntimeSynchronization();
			ResetThreadRuntimeData();

			// Do necessary cleanup after the thread has been actually destroyed
			OnKill();
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
		}
		else
		{
			// if an error occurs while terminating the thread just leave the method
			// by throwing an appropriate exception
			CThreadException* pe = new CThreadException(this, CThreadException::GetLastSystemErrorMsg(dwError), CThreadException::CANNOT_TERMINATE_THREAD);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			throw pe;
		};
	}
	else
	{
		m_dwThreadExitCode = dwExitCode;
		ResetThreadRuntimeData();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	};
}
