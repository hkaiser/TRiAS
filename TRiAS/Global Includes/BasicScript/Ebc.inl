///////////////////////////////////////////////////////////
// ebc.inl (draft 0.21)
//
// BasicScript Classes C++ library.
// Copyright (C) 1994-1995 Summit Software Company,
// All rights reserved.
//
// This source code is intended as a supplement to the
// BasicScript Classes Reference and the BasicScript 2.1 Programmer's Guide.
// See these sources for detailed information regarding the
// BasicScript Classes product.
//
///////////////////////////////////////////////////////////
//
// The inline version works with MSVC for Windows and Win32
// Borland C++, and Watcom C++.
// The .cpp version in the file ebc.cpp will work for other
// compilers.
// To activate the inline version, define _EBC_ENABLE_INLINES in ebc.h.

#include <string.h>

#ifdef EBWIN
#  ifndef _WINDLL
#    define _WINDLL
#    include <stdarg.h>
#    undef _WINDLL
#  else
#    include <stdarg.h>
#  endif
#else
#  include <stdarg.h>
#endif

/////////////////////////////////////////////////////////////////////
// Inlined CebObject methods
_EBC_INLINE CebObject::CebObject()
{
}

_EBC_INLINE CebObject::~CebObject()
{
}

/////////////////////////////////////////////////////////////////////
// Inlined CebMemory methods
_EBC_INLINE CebMemory::CebMemory(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hMem = NULL;
}

_EBC_INLINE CebMemory::CebMemory(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hMem = NULL;
}

_EBC_INLINE CebMemory::CebMemory(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hMem = NULL;
}

_EBC_INLINE CebMemory::~CebMemory()
{
	if (m_hMem) ::ebFreeBlk(m_hObject,m_hMem);
}

_EBC_INLINE ebBOOL CebMemory::Alloc(ebWORD wSize)
{
	m_hMem = ::ebAllocBlk(m_hObject,wSize);

	return (m_hMem) ? 1 : 0;
}

_EBC_INLINE ebBOOL CebMemory::ReAlloc(ebWORD wSize)
{
	return ::ebReAllocBlk(m_hObject,m_hMem,wSize);
}

_EBC_INLINE void CebMemory::Free()
{
//	delete this;
}

_EBC_INLINE ebLPVOID CebMemory::Lock()
{
	return ::ebLockBlk(m_hObject,m_hMem);
}

_EBC_INLINE void CebMemory::Unlock()
{
	::ebUnlockBlk(m_hObject,m_hMem);
}

_EBC_INLINE void CebMemory::SetOwner(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebMemory::SetOwner(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebMemory::SetOwner(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

/////////////////////////////////////////////////////////////////////
// Inlined CebArray methods
_EBC_INLINE CebArray::CebArray(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hArray = NULL;
}

_EBC_INLINE CebArray::CebArray(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hArray = NULL;
}

_EBC_INLINE CebArray::CebArray(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hArray = NULL;
}

_EBC_INLINE CebArray::~CebArray()
{
	if (m_hArray) ::ebFreeBlk(m_hObject,m_hArray);
}

_EBC_INLINE ebBOOL CebArray::Create(ebBOOL bFixed, ebWORD wType, ebWORD wExtType, int nDims, ...)
{
	va_list	args;

	va_start(args,nDims);

	m_hArray = ::ebAllocArrayV(m_hObject,bFixed,wType,wExtType,nDims,&args);

	va_end(args);

	return (m_hArray) ? 1 : 0;
}

_EBC_INLINE void CebArray::Free()
{
//	delete this;
}

_EBC_INLINE void CebArray::Lock()
{
	m_pArray = (ebLPARRAY) ::ebLockBlk(m_hObject,m_hArray);
}

_EBC_INLINE void CebArray::Unlock()
{
	::ebUnlockBlk(m_hObject,m_hArray);
}

_EBC_INLINE ebLPVOID CebArray::LockData()
{
	return ::ebLockArrayData(m_hObject,m_pArray);
}

_EBC_INLINE void CebArray::UnlockData()
{
	::ebUnlockArrayData(m_hObject,m_pArray);
}

_EBC_INLINE int CebArray::Redim(ebWORD wElements)
{
	return ::ebRedimArray(m_hObject,m_hArray,wElements);
}

_EBC_INLINE void CebArray::SetOwner(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebArray::SetOwner(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebArray::SetOwner(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

/////////////////////////////////////////////////////////////////////
// Inlined CebString methods
_EBC_INLINE CebString::CebString(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hStr = NULL;
}

_EBC_INLINE CebString::CebString(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hStr = NULL;
}

_EBC_INLINE CebString::CebString(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
	m_hStr = NULL;
}

_EBC_INLINE CebString::~CebString()
{
	if (m_hStr) ::ebFreeString(m_hObject,m_hStr);
}

_EBC_INLINE ebBOOL CebString::Create(ebWORD wSize)
{
	m_hStr = ::ebAllocString(m_hObject,wSize);

	return (m_hStr) ? 1 : 0;
}

_EBC_INLINE ebBOOL CebString::Create(ebLPCSTR pStr)
{
#ifdef EBWIN
	ebWORD wlen = ::_fstrlen(pStr);
#else
	ebWORD wlen = ::strlen(pStr);
#endif // EBWIN

	m_hStr = ::ebAllocString(m_hObject,wlen);

	return (m_hStr) ? 1 : 0;
}

_EBC_INLINE void CebString::Free()
{
//	delete this;
}

_EBC_INLINE ebLPSTR CebString::Lock()
{
	return ::ebLockString(m_hObject,m_hStr);
}

_EBC_INLINE void CebString::Unlock()
{
	::ebUnlockString(m_hObject,m_hStr);
}

_EBC_INLINE void CebString::SetOwner(CebThread FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebString::SetOwner(CebScript FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

_EBC_INLINE void CebString::SetOwner(CebInstance FAR* pObject)
{
	m_hObject = (ebHOBJECT) pObject->GetHandle();
}

/////////////////////////////////////////////////////////////////////
// Inlined CebEntryInfo methods
_EBC_INLINE CebEntryInfo::CebEntryInfo()
{
	::strcpy(m_EntryInfo.szEntry,CebEntryInfo::pszMain); // "Main()"
	m_EntryInfo.dwEntry = 0;
	m_EntryInfo.wParms = 0;
	m_EntryInfo.lpParms = NULL;
	m_EntryInfo.RetParm.wType = 0;
	m_EntryInfo.isFunc = 0;	// Sub and not a Function
}

_EBC_INLINE CebEntryInfo::CebEntryInfo(ebLPENTRYINFO pEntryInfo)
{
	m_EntryInfo = *pEntryInfo;
}

_EBC_INLINE CebEntryInfo::~CebEntryInfo()
{
}

_EBC_INLINE void CebEntryInfo::SetEntryInfo(ebLPENTRYINFO pEntryInfo)
{
	m_EntryInfo = *pEntryInfo;
}

_EBC_INLINE void CebEntryInfo::GetEntryInfo(ebLPENTRYINFO pEntryInfo) const
{
	*pEntryInfo = m_EntryInfo;
}

_EBC_INLINE ebLPENTRYINFO CebEntryInfo::GetEntryInfo()
{
	return &m_EntryInfo;
}

_EBC_INLINE void CebEntryInfo::SetEntryName(ebLPCSTR pszName)
{
	::strcpy(m_EntryInfo.szEntry,pszName);
}

_EBC_INLINE void CebEntryInfo::GetEntryName(ebLPSTR pszName) const
{
	::strcpy(pszName,m_EntryInfo.szEntry);
}

_EBC_INLINE ebDWORD CebEntryInfo::SetEntryId(ebDWORD dwId)
{
	ebDWORD dwIdT = m_EntryInfo.dwEntry;
	
	m_EntryInfo.dwEntry = dwId;
	return dwIdT;
}

_EBC_INLINE ebDWORD CebEntryInfo::GetEntryId() const
{
	return m_EntryInfo.dwEntry;
}

_EBC_INLINE ebWORD CebEntryInfo::SetParamsCount(ebWORD wParams)
{
	ebWORD wparamT = m_EntryInfo.wParms;
	
	m_EntryInfo.wParms = wParams;
	return wparamT;
}

_EBC_INLINE ebWORD CebEntryInfo::GetParamsCount() const
{
	return m_EntryInfo.wParms;
}

_EBC_INLINE ebLPPARAM CebEntryInfo::SetParams(ebLPPARAM prgParams)
{
	ebLPPARAM paramsT = m_EntryInfo.lpParms;
	
	m_EntryInfo.lpParms = prgParams;
	return paramsT;
}
	
_EBC_INLINE ebLPPARAM CebEntryInfo::GetParams() const
{
	return m_EntryInfo.lpParms;
}
	
_EBC_INLINE void CebEntryInfo::SetRetType(ebLPPARAM pRetType)
{
	m_EntryInfo.RetParm = *pRetType;
}
	
_EBC_INLINE void CebEntryInfo::GetRetType(ebLPPARAM pRetType) const
{
	*pRetType = m_EntryInfo.RetParm;
}
	
_EBC_INLINE int CebEntryInfo::SetMethodType(int nType)
{
	int ntypeT = (int) m_EntryInfo.isFunc;
	
	m_EntryInfo.isFunc = (ebBOOL) nType;
	return ntypeT;
}
	
_EBC_INLINE int CebEntryInfo::GetMethodType() const
{
	return (int) m_EntryInfo.isFunc;
}

_EBC_INLINE ebBOOL CebEntryInfo::IsFunction() const
{
	return (m_EntryInfo.isFunc == 1);
}

_EBC_INLINE ebBOOL CebEntryInfo::IsSub() const
{
	return (m_EntryInfo.isFunc == 0);
}

/////////////////////////////////////////////////////////////////////
// Inlined CebCode methods
_EBC_INLINE CebCode::CebCode()
{
	Initialize();
}

_EBC_INLINE CebCode::~CebCode()
{
	if (m_hEnumMember) CloseMemberEnum();
	if (m_hEnumProc) CloseProcEnum();
	if (m_hEnumVar) CloseVarEnum();

	if (m_hCode) ::ebCode_Free(m_hCode);
}

_EBC_INLINE void CebCode::Initialize()
{
	CebCode::Initialize(&m_hCode);
	m_hEnumMember = NULL;
	m_hEnumProc = NULL;
	m_hEnumVar = NULL;
}

_EBC_INLINE void CebCode::Initialize(ebHCODE *phCode)
{
	*phCode = NULL;
}

_EBC_INLINE ebHCODE CebCode::Get()
{
	return m_hCode;
}

_EBC_INLINE void CebCode::Get(ebHCODE *phCode) const
{
	*phCode = m_hCode;
}

_EBC_INLINE void CebCode::Set(ebHCODE hCode)
{
	m_hCode = hCode;
}

_EBC_INLINE ebHCODE CebCode::Detach(ebHCODE hNewCode)
{
	ebHCODE hCode = m_hCode;	   

	m_hCode = hNewCode;
	return hCode;
}

_EBC_INLINE ebBOOL CebCode::IsEmpty() const
{
	return (m_hCode == NULL) ? true : false;
}

_EBC_INLINE void CebCode::FreeCode()
{
		if (m_hCode) ::ebCode_Free(m_hCode);
}

_EBC_INLINE void CebCode::FreeCode(ebHCODE hCode)
{
		if (hCode) ::ebCode_Free(hCode);
}

_EBC_INLINE int CebCode::CheckEntry(ebLPENTRYINFO pEntryInfo)
{
	return ::ebCheckEntry(m_hCode,pEntryInfo);
}

_EBC_INLINE ebBOOL CebCode::GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfo((ebHOBJECT)m_hCode,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfoEx((ebHOBJECT)m_hCode,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const
{
	return ::ebGetProcInfo((ebHOBJECT)m_hCode,pName,pProcInfo);
}

_EBC_INLINE ebBOOL CebCode::GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetVarInfo((ebHOBJECT)m_hCode,pName,dwContext,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfo((ebHOBJECT)m_hCode,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfoEx((ebHOBJECT)m_hCode,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetMemberInfo(ebWORD wExtType, ebLPCSTR pName, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetMemberInfo((ebHOBJECT)m_hCode,wExtType,pName,pVarInfo);
}

_EBC_INLINE void CebCode::GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const
{
	::ebGetMemberArrayHeader((ebHOBJECT)m_hCode,pVarInfo,pArray);
}

_EBC_INLINE ebHENUM CebCode::GetFirstProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetFirstProc((ebHOBJECT)m_hCode,pProcInfo);
}

_EBC_INLINE ebBOOL CebCode::GetNextProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetNextProc(m_hEnumProc,pProcInfo);
}

_EBC_INLINE void CebCode::CloseProcEnum()
{
	::ebEnumClose(m_hEnumProc);
	m_hEnumProc = NULL;
}

_EBC_INLINE ebHENUM CebCode::GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstMember((ebHOBJECT)m_hCode,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetNextMember(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextMember(m_hEnumMember,pVarInfo);
}

_EBC_INLINE void CebCode::CloseMemberEnum()
{
	::ebEnumClose(m_hEnumMember);
	m_hEnumMember = NULL;
}

_EBC_INLINE ebHENUM CebCode::GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstVar((ebHOBJECT)m_hCode,dwContext,pVarInfo);
}

_EBC_INLINE ebBOOL CebCode::GetNextVar(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextVar(m_hEnumVar,pVarInfo);
}

_EBC_INLINE void CebCode::CloseVarEnum()
{
	::ebEnumClose(m_hEnumVar);
	m_hEnumVar = NULL;
}

/////////////////////////////////////////////////////////////////////
// Inlined CebThread methods
_EBC_INLINE CebThread FAR* CebThread::GetThis(ebHTHREAD hThread)
{
	return (CebThread FAR*) ::ebSendMessage(hThread,ebTM_GETTHIS,0,0);
}

_EBC_INLINE void CebThread::SetThis()
{
	::ebSendMessage(m_hThread,ebTM_SETTHIS,(ebDWORD)this,0);
}

_EBC_INLINE CebThread::CebThread(CebScript FAR*	pScript,
				 ebLPENTRYINFO	pEntryInfo /* = NULL */)
{
	m_hThread = NULL;
	m_hEnumCall = NULL;
	m_hEnumMember = NULL;
	m_hEnumProc = NULL;
	m_hEnumVar = NULL;
	
	m_pScript = pScript;
	m_hScript = NULL;
	m_pEntryInfo = pEntryInfo;
}

_EBC_INLINE CebThread::CebThread(ebHSCRIPT	hScript,
				 ebLPENTRYINFO	pEntryInfo /* = NULL */)
{
	m_hThread = NULL;
	m_hEnumCall = NULL;
	m_hEnumMember = NULL;
	m_hEnumProc = NULL;
	m_hEnumVar = NULL;
	
	m_pScript = NULL;
	m_hScript = hScript;
	m_pEntryInfo = pEntryInfo;
}

_EBC_INLINE CebThread::~CebThread()
{
	if (m_hEnumCall) CloseMemberEnum();
	if (m_hEnumMember) CloseMemberEnum();
	if (m_hEnumProc) CloseProcEnum();
	if (m_hEnumVar) CloseVarEnum();

	if (m_hThread) ::ebDestroyThread(m_hThread);
}

_EBC_INLINE int CebThread::Create(int iExtraBuffer)
{
int	nerror;

	if (m_pScript) 
		m_hThread = ::ebCreateThread(m_pScript->GetHandle(),m_pEntryInfo,iExtraBuffer,&nerror);
	else
		m_hThread = ::ebCreateThread(m_hScript,m_pEntryInfo,iExtraBuffer,&nerror);

	if (nerror == 0) {
		SetThis();
	}
//	if (m_hThread == NULL) delete this;
	return nerror;
}

// set Value of Extrabuffer 
_EBC_INLINE void CebThread::SetLong(ebDWORD dwOffset, long lValue)
{
	ebThread_SetLong(m_hThread, dwOffset, lValue);
}

// get Value of Extrabuffer 
_EBC_INLINE long CebThread::GetLong(ebDWORD dwOffset) const
{
return 	ebThread_GetLong(m_hThread, dwOffset);
}

_EBC_INLINE ebHTHREAD CebThread::Attach (ebHTHREAD hThread)
{
ebHTHREAD hT = m_hThread;

	m_hThread = hThread;
	if (m_hThread) SetThis();
	
return hT;
}

_EBC_INLINE ebHTHREAD CebThread::Detach (void)
{
ebHTHREAD hT = m_hThread;

	m_hThread = NULL;

return hT;
}

_EBC_INLINE ebLPENTRYINFO CebThread::SetEntryInfo(ebLPENTRYINFO pEntryInfo)
{
	ebLPENTRYINFO pentryInfoT = m_pEntryInfo;
	
	m_pEntryInfo = pEntryInfo;
	return pentryInfoT;
}

_EBC_INLINE ebLPENTRYINFO CebThread::GetEntryInfo() const
{
	return m_pEntryInfo;
}

_EBC_INLINE ebHTHREAD CebThread::GetHandle() const
{
	return m_hThread;
}

_EBC_INLINE CebThread FAR* CebThread::FromHandle(ebHTHREAD hThread)
{
	return GetThis(hThread);
}

_EBC_INLINE CebScript FAR* CebThread::GetScript() const
{
	return m_pScript ? m_pScript : CebScript::FromHandle(m_hScript);
}

_EBC_INLINE CebInstance FAR* CebThread::GetInstance() const
{
	return (CebInstance FAR*) ::ebSendMessage((ebHOBJECT) m_hThread,ebTM_GETINSTANCE,0,0);
}

_EBC_INLINE ebLONG CebThread::GetErrorLine() const
{
	return ::ebSendMessage((ebHOBJECT)m_hThread,ebTM_GETERRORLINE,0,0);
}

_EBC_INLINE ebLONG CebThread::GetErrorNumber() const
{
	return ::ebSendMessage((ebHOBJECT)m_hThread,ebTM_GETERRORNUMBER,0,0);
}

#if defined(EBWIN) | defined(EBMAC)
_EBC_INLINE void CebThread::CheckMathError()
{
	::ebCheckMathError(m_hThread);
}
#endif // EBWIN | EBMAC

_EBC_INLINE ebBOOL CebThread::ClearBreakpoint(ebWORD wLineNo)
{
	return ::ebClearBreakPoint((ebHOBJECT)m_hThread,wLineNo);
}

_EBC_INLINE void CebThread::ClearBreakpoints()
{
	::ebClearBreakPoints((ebHOBJECT)m_hThread);
}

_EBC_INLINE ebBOOL CebThread::SetBreakpoint(ebWORD wLineNo)
{
	return ::ebSetBreakPoint((ebHOBJECT)m_hThread,wLineNo);
}

_EBC_INLINE void CebThread::ConfineDebugging(CebScript FAR* pScript)
{
	::ebConfine(m_hThread,pScript->GetHandle());
}

_EBC_INLINE ebBOOL CebThread::SetNextLine(ebWORD wLineNo)
{
	return ::ebSetNextLine(m_hThread,wLineNo);
}

_EBC_INLINE ebBOOL CebThread::StepOver()
{
	return ::ebStepLine(m_hThread);
}

_EBC_INLINE ebBOOL CebThread::TraceInto()
{
	return ::ebTraceLine(m_hThread);
}

_EBC_INLINE void CebThread::GetDebugInfo(ebLPDBGINFO pDebugInfo) const
{
	pDebugInfo -> wVersion = DI_VERSION;
	::ebDebugInfo(m_hThread,pDebugInfo);
}

_EBC_INLINE void CebThread::SetRuntimeErrorProc(ebERRORPROC pfnError, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETRUNTIMEERRORPROC,(ebDWORD)dwValue,(ebLONG)pfnError);
}

_EBC_INLINE void CebThread::SetPrintProc(ebPRINTPROC pfnPrint, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETPRINTPROC,(ebDWORD)dwValue,(ebLONG)pfnPrint);
}

_EBC_INLINE void CebThread::Start()
{
	::ebStartThread(m_hThread);
}

_EBC_INLINE void CebThread::EnableCtrlBreak(ebBOOL bEnabled /* = TRUE */)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_ENABLEBREAK,(ebDWORD) bEnabled,0);
}

_EBC_INLINE ebLONG CebThread::GetState() const
{
	return ::ebSendMessage((ebHOBJECT)m_hThread,ebTM_GETSTATE,0,0);
}

_EBC_INLINE void CebThread::Interrupt(int nInterruptCode, int nErrorCode)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_INTERRUPT,(ebDWORD)nInterruptCode,(ebLONG)nErrorCode);
}

_EBC_INLINE ebBOOL CebThread::IsInterrupted() const
{
	return (ebBOOL) ::ebSendMessage((ebHOBJECT)m_hThread,ebTM_ISINTERRUPTED,0,0);
}

_EBC_INLINE void CebThread::RuntimeError(ebWORD wErrorNo, ebLPCSTR pMsg, ebBOOL bFatal /* = TRUE */)
{
	::ebRuntimeError(m_hThread,bFatal,wErrorNo,pMsg);
}

_EBC_INLINE void CebThread::SetLinkOptions(ebDWORD dwOptions)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETLINKOPTIONS,(ebDWORD)dwOptions,0);
}

_EBC_INLINE void CebThread::SetStackSize(ebDWORD dwSize)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETSTACK,dwSize,0);
}

_EBC_INLINE void CebThread::SetCommandLine(ebLPCSTR pCommandLine)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETCOMMANDLINE,0,(ebLONG)pCommandLine);
}

_EBC_INLINE void CebThread::SetHomeDir(ebLPCSTR pHomeDir)
{
	::ebSendMessage((ebHOBJECT)m_hThread,ebTM_SETHOMEDIR,0,(ebLONG)pHomeDir);
}

_EBC_INLINE int CebThread::GetOptionBase() const
{
	return (int) ::ebSendMessage((ebHOBJECT)m_hThread,ebTM_GETOPTIONBASE,0,0);
}

#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
_EBC_INLINE ebDWORD CebThread::CreateObjectId(const LPDISPATCH pDispatch)
{
	return ::ebCreateOleId(m_hThread,pDispatch);
}

_EBC_INLINE void CebThread::FreeObjectId(ebDWORD dwId)
{
	::ebFreeOleId((ebHOBJECT)m_hThread, dwId);
}

_EBC_INLINE LPDISPATCH CebThread::GetDispatch(ebDWORD dwId) const
{
	return (LPDISPATCH) ::ebGetDispatch(m_hThread,dwId);
}
#endif // EBWIN | EBWIN32 | EBMAC
	
_EBC_INLINE ebBOOL CebThread::GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfo((ebHOBJECT)m_hThread,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfoEx((ebHOBJECT)m_hThread,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const
{
	return ::ebGetProcInfo((ebHOBJECT)m_hThread,pName,pProcInfo);
}

_EBC_INLINE ebBOOL CebThread::GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetVarInfo((ebHOBJECT)m_hThread,pName,dwContext,pVarInfo);
}

_EBC_INLINE ebINT CebThread::GetVarValue(ebHINSTANCE hInst, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const
{
return ::ebGetVarValue(hInst, m_hScript, m_hThread,dwContext,pExpression,
					pVar,pwType,pwExtType);
}

//ebGetVarValueA(ebHINSTANCE hInst,ebHSCRIPT hScript,ebHTHREAD hThread,ebDWORD context,ebLPCSTR lpExpression,ebLPVARIABLE lpVar,ebLPWORD lpwType,ebLPWORD lpwExtType);

_EBC_INLINE ebINT CebThread::SetVarValue(ebHINSTANCE hInst, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar)
{
return ::ebSetVarValue(hInst, m_hScript, m_hThread,dwContext,pExpression,pVar);
}

_EBC_INLINE ebBOOL CebThread::GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfo((ebHOBJECT)m_hThread,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfoEx((ebHOBJECT)m_hThread,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetMemberInfo(ebWORD wExtType, ebLPCSTR pName, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetMemberInfo((ebHOBJECT)m_hThread,wExtType,pName,pVarInfo);
}

_EBC_INLINE void CebThread::GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const
{
	::ebGetMemberArrayHeader((ebHOBJECT)m_hThread,pVarInfo,pArray);
}

_EBC_INLINE ebHENUM CebThread::GetFirstCall(ebLPPROCINFO pProcInfo, ebLPWORD pwLineNo)
{
	return ::ebGetFirstCall(m_hThread,pProcInfo,pwLineNo);
}

_EBC_INLINE ebBOOL CebThread::GetNextCall(ebLPPROCINFO pProcInfo, ebLPWORD pwLineNo)
{
	return ::ebGetNextCall(m_hEnumCall,pProcInfo,pwLineNo);
}

_EBC_INLINE void CebThread::CloseCallEnum()
{
	::ebEnumClose(m_hEnumCall);
	m_hEnumCall = NULL;
}

_EBC_INLINE ebHENUM CebThread::GetFirstProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetFirstProc((ebHOBJECT)m_hThread,pProcInfo);
}

_EBC_INLINE ebBOOL CebThread::GetNextProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetNextProc(m_hEnumProc,pProcInfo);
}

_EBC_INLINE void CebThread::CloseProcEnum()
{
	::ebEnumClose(m_hEnumProc);
	m_hEnumProc = NULL;
}

_EBC_INLINE ebHENUM CebThread::GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstMember((ebHOBJECT)m_hThread,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetNextMember(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextMember(m_hEnumMember,pVarInfo);
}

_EBC_INLINE void CebThread::CloseMemberEnum()
{
	::ebEnumClose(m_hEnumMember);
	m_hEnumMember = NULL;
}

_EBC_INLINE ebHENUM CebThread::GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstVar((ebHOBJECT)m_hThread,dwContext,pVarInfo);
}

_EBC_INLINE ebBOOL CebThread::GetNextVar(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextVar(m_hEnumVar,pVarInfo);
}

_EBC_INLINE void CebThread::CloseVarEnum()
{
	::ebEnumClose(m_hEnumVar);
	m_hEnumVar = NULL;
}

_EBC_INLINE ebLPVOID CebThread::GetParamPtr(ebWORD wIndex) const
{
	return ::ebParm(m_hThread,wIndex);
}

_EBC_INLINE ebBOOL CebThread::GetParamArray(ebWORD wIndex, ebLPHSUB phArray) const
{
	ebLPHSUB p = (ebLPHSUB) GetParamPtr(wIndex);
	if (p) {
		*phArray = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamBool(ebWORD wIndex, short FAR* pShort) const
{
	short FAR* p = (short FAR*) GetParamPtr(wIndex);
	if (p) {
		*pShort = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamCurrency(ebWORD wIndex, ebLPCURRENCY pCurrency) const
{
	ebLPCURRENCY p = (ebLPCURRENCY) GetParamPtr(wIndex);
	if (p) {
		*pCurrency = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamDate(ebWORD wIndex, double FAR* pDate) const
{
	double FAR* p = (double FAR*) GetParamPtr(wIndex);
	if (p) {
		*pDate = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamDouble(ebWORD wIndex, double FAR* pDouble) const
{
	double FAR* p = (double FAR*) GetParamPtr(wIndex);
	if (p) {
		*pDouble = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamInt(ebWORD wIndex, ebLPWORD pWord) const
{
	ebLPWORD p = (ebLPWORD) GetParamPtr(wIndex);
	if (p) {
		*pWord = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamLong(ebWORD wIndex, long FAR* pLong) const
{
	long FAR* p = (long FAR*) GetParamPtr(wIndex);
	if (p) {
		*pLong = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamObject(ebWORD wIndex, ebLPDWORD pdwObject) const
{
	ebLPDWORD p = (ebLPDWORD) GetParamPtr(wIndex);
	if (p) {
		*pdwObject = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamOleObject(ebWORD wIndex, ebLPDWORD pdwId) const
{
	ebLPDWORD p = (ebLPDWORD) GetParamPtr(wIndex);
	if (p) {
		*pdwId = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamSingle(ebWORD wIndex, float FAR* pFloat) const
{
	float FAR* p = (float FAR*) GetParamPtr(wIndex);
	if (p) {
		*pFloat = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamString(ebWORD wIndex, ebLPHSUB pStr) const
{
	ebLPHSUB p = (ebLPHSUB) GetParamPtr(wIndex);
	if (p) {
		*pStr = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamStruct(ebWORD wIndex, ebLPSTR pStruct) const
{
	ebLPSTR p = (ebLPSTR) GetParamPtr(wIndex);
	if (p) {
		*pStruct = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::GetParamVariant(ebWORD wIndex, ebLPVARIANT pVariant) const
{
	ebLPVARIANT p = (ebLPVARIANT) GetParamPtr(wIndex);
	if (p) {
		*pVariant = *p;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamBool(ebWORD wIndex, ebBOOL boolVal)
{
	short FAR* p = (short FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = boolVal;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamCurrency(ebWORD wIndex, ebCURRENCY cy)
{
	ebLPCURRENCY p = (ebLPCURRENCY) GetParamPtr(wIndex);
	if (p) {
		*p = cy;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamDate(ebWORD wIndex, double date)
{
	double FAR* p = (double FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = date;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamDouble(ebWORD wIndex, double d)
{
	double FAR* p = (double FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = d;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamInt(ebWORD wIndex, short i)
{
	short FAR* p = (short FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = i;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamLong(ebWORD wIndex, long l)
{
	long FAR* p = (long FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = l;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamObject(ebWORD wIndex, ebDWORD dwObject)
{
	ebLPDWORD p = (ebLPDWORD) GetParamPtr(wIndex);
	if (p) {
		*p = dwObject;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamOleObject(ebWORD wIndex, ebDWORD dwId)
{
	ebLPDWORD p = (ebLPDWORD) GetParamPtr(wIndex);
	if (p) {
		*p = dwId;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamSingle(ebWORD wIndex, float f)
{
	float FAR* p = (float FAR*) GetParamPtr(wIndex);
	if (p) {
		*p = f;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamString(ebWORD wIndex, ebHSUB hStr)
{
	ebLPHSUB p = (ebLPHSUB) GetParamPtr(wIndex);
	if (p) {
		*p = hStr;
		return 1;
	}
	return 0;
}

_EBC_INLINE ebBOOL CebThread::SetParamVariant(ebWORD wIndex, ebVARIANT Variant)
{
	ebLPVARIANT p = (ebLPVARIANT) GetParamPtr(wIndex);
	if (p) {
		*p = Variant;
		return 1;
	}
	return 0;
}

_EBC_INLINE int CebThread::VariantConvert(ebLPVARIANT pSource, ebLPVARIANT pDest, ebWORD wWantType)
{
	return ::ebVariantConvert(m_hThread,pSource,pDest,wWantType);
}

_EBC_INLINE void CebThread::VariantFree(ebLPVARIANT pVariant)
{
	::ebFreeVariant((ebHOBJECT)m_hThread,pVariant);
}

_EBC_INLINE int CebThread::Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const
{
	return ::ebFormat((ebHOBJECT)m_hThread,wType,pSource,pFormat,pDest,nSize);
}

_EBC_INLINE ebDWORD CebThread::GetExtensionData() const
{
	return ::ebGetExtData((ebHOBJECT)m_hThread);
}

_EBC_INLINE void CebThread::SetExtensionData(ebDWORD dwValue)
{
	::ebSetExtData((ebHOBJECT)m_hThread,dwValue);
}

_EBC_INLINE ebLONG CebThread::SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam)
{
	return ::ebSendMessage((ebHOBJECT)m_hThread,umsg,dwParam,lParam);
}

/////////////////////////////////////////////////////////////////////
// Inlined CebScript methods
_EBC_INLINE CebScript FAR* CebScript::GetThis(ebHSCRIPT hScript)
{
	return (CebScript FAR*) ::ebSendMessage(hScript,ebSM_GETTHIS,0,0);
}

_EBC_INLINE void CebScript::SetThis()
{
	::ebSendMessage(m_hScript,ebSM_SETTHIS,(ebDWORD)this,0);
}

_EBC_INLINE CebScript::CebScript(CebInstance FAR* pInstance,
				 ebHCODE	hCode,	/* = NULL */
				 ebLPSTR	pErrorBuffer,	/* = NULL */
				 int		nBufferLength	/* = 0 */)
{
	m_hScript = NULL;
	m_hEnumMember = NULL;
	m_hEnumProc = NULL;
	m_hEnumVar = NULL;
	
	m_pInstance = pInstance;
	m_hCode = hCode;
	m_pErrorBuffer = pErrorBuffer;
	m_nBufferLength = nBufferLength;
}

_EBC_INLINE CebScript::~CebScript()
{
	if (m_hEnumMember) CloseMemberEnum();
	if (m_hEnumProc) CloseProcEnum();
	if (m_hEnumVar) CloseVarEnum();

	if (m_hScript) ::ebDestroyScript(m_hScript);
}

_EBC_INLINE int CebScript::Create()
{
	int	nerror;

	m_hScript = ::ebCreateScriptEx(m_pInstance->GetHandle(),m_hCode,&nerror,m_pErrorBuffer,m_nBufferLength);
	if (nerror == 0)
		SetThis();
//	if (m_hScript == NULL) delete this;
	return nerror;
}

_EBC_INLINE ebHSCRIPT CebScript::Detach ()
{
ebHSCRIPT hS = m_hScript;

	m_hScript = NULL;

return hS;
}

_EBC_INLINE ebHCODE CebScript::SetCode(ebHCODE hNewCode)
{
ebHCODE hCode = m_hCode;
	
	m_hCode = hNewCode;
	return hCode;
}

_EBC_INLINE ebHCODE CebScript::GetCode() const
{
	return m_hCode;
}

_EBC_INLINE void CebScript::SetErrorBuffer(ebLPSTR pErrorBuffer, int nBufferLength)
{
	m_pErrorBuffer = pErrorBuffer;
	m_nBufferLength = nBufferLength;
}

_EBC_INLINE ebHSCRIPT CebScript::GetHandle() const
{
	return m_hScript;
}

_EBC_INLINE CebScript FAR* CebScript::FromHandle(ebHSCRIPT hScript)
{
	return GetThis(hScript);
}

_EBC_INLINE CebInstance FAR* CebScript::GetInstance() const
{
	return m_pInstance;
}

_EBC_INLINE ebBOOL CebScript::Link(ebLPPROCINFO pProcInfo) const
{
	return ::ebLink(m_hScript,pProcInfo);
}

_EBC_INLINE ebBOOL CebScript::ClearBreakpoint(ebWORD wLineNo)
{
	return ::ebClearBreakPoint((ebHOBJECT)m_hScript,wLineNo);
}

_EBC_INLINE void CebScript::ClearBreakpoints()
{
	::ebClearBreakPoints((ebHOBJECT)m_hScript);
}

_EBC_INLINE ebBOOL CebScript::SetBreakpoint(ebWORD wLineNo)
{
	return ::ebSetBreakPoint((ebHOBJECT)m_hScript,wLineNo);
}
	
_EBC_INLINE ebBOOL CebScript::GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfo((ebHOBJECT)m_hScript,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfoEx((ebHOBJECT)m_hScript,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const
{
	return ::ebGetProcInfo((ebHOBJECT)m_hScript,pName,pProcInfo);
}

_EBC_INLINE ebBOOL CebScript::GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetVarInfo((ebHOBJECT)m_hScript,pName,dwContext,pVarInfo);
}

_EBC_INLINE ebINT CebScript::GetVarValue(ebHINSTANCE hInst, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const
{
	return ::ebGetVarValue(hInst, m_hScript, hThread, dwContext,pExpression,pVar,pwType,pwExtType);
}

_EBC_INLINE ebINT CebScript::SetVarValue(ebHINSTANCE hInst, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar)
{
	return ::ebSetVarValue(hInst, m_hScript, hThread, dwContext,pExpression,pVar);
}

_EBC_INLINE ebBOOL CebScript::GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfo((ebHOBJECT)m_hScript,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfoEx((ebHOBJECT)m_hScript,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetMemberInfo(ebWORD wExtType, ebLPCSTR pName, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetMemberInfo((ebHOBJECT)m_hScript,wExtType,pName,pVarInfo);
}

_EBC_INLINE void CebScript::GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const
{
	::ebGetMemberArrayHeader((ebHOBJECT)m_hScript,pVarInfo,pArray);
}

_EBC_INLINE ebHENUM CebScript::GetFirstProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetFirstProc((ebHOBJECT)m_hScript,pProcInfo);
}

_EBC_INLINE ebBOOL CebScript::GetNextProc(ebLPPROCINFO pProcInfo)
{
	return ::ebGetNextProc(m_hEnumProc,pProcInfo);
}

_EBC_INLINE void CebScript::CloseProcEnum()
{
	::ebEnumClose(m_hEnumProc);
	m_hEnumProc = NULL;
}

_EBC_INLINE ebHENUM CebScript::GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstMember((ebHOBJECT)m_hScript,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetNextMember(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextMember(m_hEnumMember,pVarInfo);
}

_EBC_INLINE void CebScript::CloseMemberEnum()
{
	::ebEnumClose(m_hEnumMember);
	m_hEnumMember = NULL;
}

_EBC_INLINE ebHENUM CebScript::GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstVar((ebHOBJECT)m_hScript,dwContext,pVarInfo);
}

_EBC_INLINE ebBOOL CebScript::GetNextVar(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextVar(m_hEnumVar,pVarInfo);
}

_EBC_INLINE void CebScript::CloseVarEnum()
{
	::ebEnumClose(m_hEnumVar);
	m_hEnumVar = NULL;
}

_EBC_INLINE void CebScript::VariantFree(ebLPVARIANT pVariant)
{
	::ebFreeVariant((ebHOBJECT)m_hScript,pVariant);
}

_EBC_INLINE int CebScript::Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const
{
	return ::ebFormat((ebHOBJECT)m_hScript,wType,pSource,pFormat,pDest,nSize);
}

_EBC_INLINE ebLONG CebScript::SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam)
{
	return ::ebSendMessage((ebHOBJECT)m_hScript,umsg,dwParam,lParam);
}

/////////////////////////////////////////////////////////////////////
// Inlined CebInstance methods
_EBC_INLINE CebInstance FAR* CebInstance::GetThis(ebHINSTANCE hInstance)
{
	return (CebInstance FAR*) ::ebSendMessage(hInstance,ebIM_GETTHIS,0,0);
}

_EBC_INLINE void CebInstance::SetThis()
{
	::ebSendMessage(m_hInstance,ebIM_SETTHIS,(ebDWORD)this,0);
}

_EBC_INLINE CebInstance::CebInstance(
	ebWORD	wFlags,	ebEXTENUMPROC pfnGetExtension, ebDWORD dwData)
{
	m_wFlags = wFlags;
	m_pfnGetExtension = pfnGetExtension;
	m_dwData = dwData;

	m_hInstance = NULL;
	m_hEnumMember = NULL;
	m_hEnumVar = NULL;
}

_EBC_INLINE CebInstance::~CebInstance()
{
	if (m_hEnumMember) CloseMemberEnum();
	if (m_hEnumVar) CloseVarEnum();

// #HK950508 ------------------------------------------------------------------

	if (m_hInstance)
		::ebTerm(m_hInstance);
	m_hInstance = NULL;
//	::ebTerm(m_hInstance);
// #HK950508 ------------------------------------------------------------------
}

_EBC_INLINE int CebInstance::Create()
{
	int	nerror;

	m_hInstance = ::ebInit(m_wFlags,m_pfnGetExtension,&nerror, m_dwData, 0);
	if (nerror == 0) {
		SetThis();
	}
//	else delete this;
	return nerror;
}

_EBC_INLINE ebHINSTANCE CebInstance::GetHandle() const
{
	return m_hInstance;
}

_EBC_INLINE CebInstance FAR* CebInstance::FromHandle(ebHINSTANCE hInstance)
{
	return GetThis(hInstance);
}

#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
_EBC_INLINE void CebInstance::RegisterObject(ebDWORD dwConstId, const LPDISPATCH pDispatch)
{
	::ebRegisterOleObject(m_hInstance,dwConstId,pDispatch);
}
#endif // EBWIN | EBWIN32 | EBMAC

_EBC_INLINE void CebInstance::GetCompilerErrorProc(ebERRORPROC FAR* ppfnError, ebDWORD FAR* pdwValue) const
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETCOMPILERERRORPROC,(ebDWORD)pdwValue,(ebLONG)ppfnError);
}

_EBC_INLINE void CebInstance::SetCompilerErrorProc(ebERRORPROC pfnError, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETCOMPILERERRORPROC,(ebDWORD)dwValue,(ebLONG)pfnError);
}

_EBC_INLINE void CebInstance::GetRuntimeErrorProc(ebERRORPROC FAR* ppfnError, ebDWORD FAR* pdwValue) const
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETRUNTIMEERRORPROC,(ebDWORD)pdwValue,(ebLONG)ppfnError);
}

_EBC_INLINE void CebInstance::SetRuntimeErrorProc(ebERRORPROC pfnError, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETRUNTIMEERRORPROC,(ebDWORD)dwValue,(ebLONG)pfnError);
}

_EBC_INLINE void CebInstance::GetPcodeCallbackProc(ebPCODECALLBACKPROC FAR* ppfnCallback, ebDWORD FAR* pdwValue) const
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETPCODECALLBACKPROC,(ebDWORD)pdwValue,(ebLONG)ppfnCallback);
}

_EBC_INLINE void CebInstance::SetPcodeCallbackProc(ebPCODECALLBACKPROC pfnCallback, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETPCODECALLBACKPROC,(ebDWORD)dwValue,(ebLONG)pfnCallback);
}

_EBC_INLINE void CebInstance::GetPrintProc(ebPRINTPROC FAR* ppfnPrint, ebDWORD FAR* pdwValue) const
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETPRINTPROC,(ebDWORD)pdwValue,(ebLONG)ppfnPrint);
}

_EBC_INLINE void CebInstance::SetPrintProc(ebPRINTPROC pfnPrint, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETPRINTPROC,(ebDWORD)dwValue,(ebLONG)pfnPrint);
}

_EBC_INLINE void CebInstance::SetRequestorProc(ebREQUESTORPROC pfnRequestor, ebDWORD dwValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETREQUESTOR,(ebDWORD)dwValue,(ebLONG)pfnRequestor);
}

_EBC_INLINE ebBOOL CebInstance::RegisterExtensions(ebLPCSTR pName, ebLPCSTR pTable, ebCALLBACKPROC pfnCallback)
{
	return ::ebRegisterExtensions(m_hInstance,pName,pTable,pfnCallback);
}

_EBC_INLINE ebBOOL ebCAPI CebInstance::RegisterExtensionsEx(ebLPCSTR pName, ebCALLBACKPROC pfnCallback, ...)
{
	va_list args;
	ebBOOL brc;
	
	va_start(args,pfnCallback);

	brc = ::ebRegisterExtensionsExV(m_hInstance,pName,pfnCallback,&args);
	
    va_end(args);
    return brc;
}

_EBC_INLINE void CebInstance::UnRegisterExtensions(ebLPCSTR pName)
{
	::ebUnRegisterExtensions(m_hInstance,pName);
}

_EBC_INLINE void CebInstance::SetPublicSpace(ebDWORD dwSize)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETPUBLICSPACE,(ebDWORD)dwSize,0);
}

_EBC_INLINE void CebInstance::ResetPublicVariables()
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_RESETPUBLICS,0,0);
}

_EBC_INLINE void CebInstance::LoadProcessData()
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_LOADPROCESSDATA,0,0);
}

_EBC_INLINE void CebInstance::SetLinkOptions(ebDWORD dwOptions)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETLINKOPTIONS,(ebDWORD)dwOptions,0);
}

_EBC_INLINE void CebInstance::SetCommandLine(ebLPCSTR pCommandLine)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETCOMMANDLINE,0,(ebLONG)pCommandLine);
}

_EBC_INLINE void CebInstance::SetHomeDir(ebLPCSTR pHomeDir)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETHOMEDIR,0,(ebLONG)pHomeDir);
}

_EBC_INLINE void CebInstance::GetCountryInfo(ebCOUNTRY FAR* pCountry) const
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETCOUNTRY,0,(ebLONG)pCountry);
}

_EBC_INLINE void CebInstance::SetCountryInfo(ebCOUNTRY FAR* pCountry)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETCOUNTRY,0,(ebLONG)pCountry);
}

_EBC_INLINE ebLONG CebInstance::GetOSValue(int index) const
{
	return ::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_GETOSVALUE,(ebDWORD)index,0);
}

_EBC_INLINE void CebInstance::SetOSValue(int index, ebLONG lValue)
{
	::ebSendMessage((ebHOBJECT)m_hInstance,ebIM_SETOSVALUE,(ebDWORD)index,(ebLONG)lValue);
}

// #HK950509 ------------------------------------------------------------------
_EBC_INLINE ebHWND CebInstance::GetWindow (void) const
{
	return ebInstance_GetWindow ((ebHOBJECT)m_hInstance);
}

_EBC_INLINE void CebInstance::SetViewportParent(ebHWND hWnd)
{
	ebInstance_SetViewportParent(m_hInstance,hWnd);
}

_EBC_INLINE void CebInstance::SetWindow(ebHWND hWnd)
{
	ebInstance_SetWindow((ebHOBJECT)m_hInstance, hWnd);
}

// #HK950509 ------------------------------------------------------------------

_EBC_INLINE ebBOOL CebInstance::GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfo((ebHOBJECT)m_hInstance,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetObjectInfoEx((ebHOBJECT)m_hInstance,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetVarInfo((ebHOBJECT)m_hInstance,pName,dwContext,pVarInfo);
}

_EBC_INLINE ebINT CebInstance::GetVarValue(ebHSCRIPT hScript, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const
{
	return ::ebGetVarValue(m_hInstance, hScript, hThread, dwContext,pExpression,pVar,pwType,pwExtType);
}

_EBC_INLINE ebINT CebInstance::SetVarValue(ebHSCRIPT hScript, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar)
{
	return ::ebSetVarValue(m_hInstance, hScript, hThread, dwContext,pExpression,pVar);
}

_EBC_INLINE ebBOOL CebInstance::GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfo((ebHOBJECT)m_hInstance,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetStructInfoEx((ebHOBJECT)m_hInstance,pType,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetMemberInfo(ebWORD wExtType, ebLPCSTR pName, ebLPVARIABLEINFO pVarInfo) const
{
	return ::ebGetMemberInfo((ebHOBJECT)m_hInstance,wExtType,pName,pVarInfo);
}

_EBC_INLINE void CebInstance::GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const
{
	::ebGetMemberArrayHeader((ebHOBJECT)m_hInstance,pVarInfo,pArray);
}

_EBC_INLINE ebHENUM CebInstance::GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstVar((ebHOBJECT)m_hInstance,dwContext,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetNextVar(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextVar(m_hEnumVar,pVarInfo);
}

_EBC_INLINE void CebInstance::CloseVarEnum()
{
	::ebEnumClose(m_hEnumVar);
	m_hEnumVar = NULL;
}

_EBC_INLINE ebHENUM CebInstance::GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetFirstMember((ebHOBJECT)m_hInstance,wExtType,pVarInfo);
}

_EBC_INLINE ebBOOL CebInstance::GetNextMember(ebLPVARIABLEINFO pVarInfo)
{
	return ::ebGetNextMember(m_hEnumMember,pVarInfo);
}

_EBC_INLINE void CebInstance::CloseMemberEnum()
{
	::ebEnumClose(m_hEnumMember);
	m_hEnumMember = NULL;
}

_EBC_INLINE int CebInstance::Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const
{
	return ::ebFormat((ebHOBJECT)m_hInstance,wType,pSource,pFormat,pDest,nSize);
}

_EBC_INLINE ebDWORD CebInstance::GetExtensionData() const
{
	return ::ebGetExtData((ebHOBJECT)m_hInstance);
}

_EBC_INLINE void CebInstance::SetExtensionData(ebDWORD dwValue)
{
	::ebSetExtData((ebHOBJECT)m_hInstance,dwValue);
}

_EBC_INLINE ebLONG CebInstance::SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam)
{
	return ::ebSendMessage((ebHOBJECT)m_hInstance,umsg,dwParam,lParam);
}

/////////////////////////////////////////////////////////////////////
// Inlined CebArgs methods
_EBC_INLINE CebArgs::CebArgs(ebARGS pArgs)
{
	m_pArgs = pArgs;
}

_EBC_INLINE CebArgs::~CebArgs()
{
}

_EBC_INLINE ebHSUB CebArgs::GetArray(ebWORD wIndex) const
{
	return ::ebGetArray(m_pArgs,wIndex);
}

_EBC_INLINE short CebArgs::GetBool(ebWORD wIndex) const
{
	return ::ebGetBool(m_pArgs,wIndex);
}

_EBC_INLINE ebCURRENCY CebArgs::GetCurrency(ebWORD wIndex) const
{
	return ::ebGetCurrency(m_pArgs,wIndex);
}

_EBC_INLINE double CebArgs::GetDate(ebWORD wIndex) const
{
	return ::ebGetDate(m_pArgs,wIndex);
}
	
_EBC_INLINE double CebArgs::GetDouble(ebWORD wIndex) const
{
	return ::ebGetDouble(m_pArgs,wIndex);
}

_EBC_INLINE ebWORD CebArgs::GetInt(ebWORD wIndex) const
{
	return ::ebGetInt(m_pArgs,wIndex);
}

_EBC_INLINE ebDWORD CebArgs::GetLong(ebWORD wIndex) const
{
	return ::ebGetLong(m_pArgs,wIndex);
}

_EBC_INLINE ebDWORD CebArgs::GetObject(ebWORD wIndex) const
{
	return ::ebGetObject(m_pArgs,wIndex);
}

#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
_EBC_INLINE ebDWORD CebArgs::GetOleObject(ebWORD wIndex) const
{
// #HK950508 ------------------------------------------------------------------
	return ebGetOleObject(m_pArgs,wIndex);
//	return ::ebGetOleObject(m_pArgs,wIndex);
// #HK950508 ------------------------------------------------------------------
}
#endif // EBWIN | EBWIN32 | EBMAC

_EBC_INLINE float CebArgs::GetSingle(ebWORD wIndex) const
{
	return ::ebGetSingle(m_pArgs,wIndex);
}

_EBC_INLINE ebHSUB CebArgs::GetString(ebWORD wIndex) const
{
	return ::ebGetString(m_pArgs,wIndex);
}

_EBC_INLINE ebLPVOID CebArgs::GetStruct(ebWORD wIndex) const
{
	return ::ebGetStruct(m_pArgs,wIndex);
}

_EBC_INLINE ebVARIANT CebArgs::GetVariant(ebWORD wIndex) const
{
	return ::ebGetVariant(m_pArgs,wIndex);
}

_EBC_INLINE void CebArgs::SetBool(ebWORD wIndex, ebBOOL boolVal)
{
	::ebSetBool(m_pArgs,wIndex,boolVal);
}

_EBC_INLINE void CebArgs::SetCurrency(ebWORD wIndex, ebCURRENCY cy)
{
	::ebSetCurrency(m_pArgs,wIndex,cy);
}

_EBC_INLINE void CebArgs::SetDate(ebWORD wIndex, double date)
{
	::ebSetDate(m_pArgs,wIndex,date);
}

_EBC_INLINE void CebArgs::SetDouble(ebWORD wIndex, double d)
{
	::ebSetDouble(m_pArgs,wIndex,d);
}

_EBC_INLINE void CebArgs::SetInt(ebWORD wIndex, short i)
{
	::ebSetInt(m_pArgs,wIndex,i);
}

_EBC_INLINE void CebArgs::SetLong(ebWORD wIndex, long l)
{
	::ebSetLong(m_pArgs,wIndex,l);
}

_EBC_INLINE void CebArgs::SetObject(ebWORD wIndex, ebDWORD dwObject)
{
	::ebSetObject(m_pArgs,wIndex,dwObject);
}

#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
_EBC_INLINE void CebArgs::SetOleObject(ebWORD wIndex, ebDWORD dwId)
{
// #HK950508 ------------------------------------------------------------------
	ebSetOleObject(m_pArgs,wIndex,dwId);
//	::ebSetOleObject(m_pArgs,wIndex,dwId);
// #HK950508 ------------------------------------------------------------------
}
#endif // EBWIN | EBWIN32 | EBMAC

_EBC_INLINE void CebArgs::SetSingle(ebWORD wIndex, float f)
{
	::ebSetSingle(m_pArgs,wIndex,f);
}
	
_EBC_INLINE void CebArgs::SetString(ebWORD wIndex, ebHSUB hStr)
{
	::ebSetString(m_pArgs,wIndex,hStr);
}
	
_EBC_INLINE void CebArgs::SetVariant(ebWORD wIndex, ebLPVARIANT pVariant)
{
	::ebSetVariant(m_pArgs,wIndex,pVariant);
}

/////////////////////////////////////////////////////////////////////
// Inlined CebProto methods
_EBC_INLINE CebProto::CebProto()
{
	m_hTable = NULL;
}

_EBC_INLINE ebHPROTO CebProto::GetHandle() const
{
	return m_hTable;
}

_EBC_INLINE ebBOOL CebProto::Create()
{
	m_hTable = ::ebProtoBegin();
	return (m_hTable) ? 1 : 0;
}

_EBC_INLINE ebBOOL CebProto::Finish(ebLPVOID FAR* ppProto, ebLPDWORD pdwSize)
{
	return ::ebProtoEnd(m_hTable,ppProto,pdwSize);
}

_EBC_INLINE void CebProto::FreeTable(ebLPSTR pProto)
{
	::ebFreePtr(pProto);
}

_EBC_INLINE void CebProto::AddCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddCmdV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
    va_list args;

    va_start(args,wMaxArgs);

	::ebProtoAddCmdV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,&args);

    va_end(args);
}

_EBC_INLINE void CebProto::AddConst(ebLPCSTR pName, ebWORD wType, ebLPSTR pExtType, ebLPCVOID pParams)
{
	::ebProtoAddConstV(m_hTable,pName,wType,pExtType,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddConst(ebLPCSTR pName, ebWORD wType, ebLPSTR pExtType, ...)
{
	va_list args;

	va_start(args,pExtType);

	::ebProtoAddConstV(m_hTable,pName,wType,pExtType,&args);

	va_end(args);
}
	
_EBC_INLINE void CebProto::AddEntryCmd(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddEntryCmdV(m_hTable,pName,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddEntryCmd(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddEntryCmdV(m_hTable,pName,wMinArgs,wMaxArgs,&args);

	va_end(args);
}

// #HK950508 ------------------------------------------------------------------
_EBC_INLINE void CebProto::AddEntryFunction(ebLPCSTR pName, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
//_EBC_INLINE void CebProto::AddEntryFunction(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddEntryFuncV(m_hTable,pName,wType,lpExtType,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddEntryFunction(ebLPCSTR pName, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
// _EBC_INLINE void ebCAPI CebProto::AddEntryFunction(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddEntryFuncV(m_hTable,pName,wType,lpExtType,wMinArgs,wMaxArgs,&args);

	va_end(args);
}
	
_EBC_INLINE void CebProto::AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
// _EBC_INLINE void CebProto::AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddFuncV(m_hTable,wFlags,pName,wId,wType,lpExtType,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
// _EBC_INLINE void ebCAPI CebProto::AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddFuncV(m_hTable,wFlags,pName,wId,wType,lpExtType,wMinArgs,wMaxArgs,&args);

	va_end(args);
}
// #HK950508 ------------------------------------------------------------------

_EBC_INLINE void CebProto::AddInline(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddInlineV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddInline(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddInlineV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,&args);

	va_end(args);
}

_EBC_INLINE void CebProto::AddObject(ebLPCSTR pName, ebWORD wId, ebLPCSTR pBaseName)
{
	::ebProtoAddObj(m_hTable,pName,wId,pBaseName);
}	

_EBC_INLINE void CebProto::AddObjCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddObjCmdV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,pParams);
}

_EBC_INLINE void ebCAPI CebProto::AddObjCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddObjCmdV(m_hTable,wFlags,pName,wId,wMinArgs,wMaxArgs,&args);

	va_end(args);
}

_EBC_INLINE void CebProto::AddObjFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR pExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams)
{
	::ebProtoAddObjFuncV(m_hTable,wFlags,pName,wId,wType,pExtType,wMinArgs,wMaxArgs,pParams);
}	

_EBC_INLINE void ebCAPI CebProto::AddObjFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR pExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...)
{
	va_list args;

	va_start(args,wMaxArgs);

	::ebProtoAddObjFuncV(m_hTable,wFlags,pName,wId,wType,pExtType,wMinArgs,wMaxArgs,&args);

	va_end(args);
}

_EBC_INLINE void CebProto::AddObjProperty(ebWORD wFlags, ebLPCSTR pName, ebWORD wSetID, ebWORD wGetID, ebWORD wType, ebLPCSTR pExtType)
{
	::ebProtoAddObjProp(m_hTable,wFlags,pName,wSetID,wGetID,wType,pExtType);
}

_EBC_INLINE void CebProto::AddStruct(ebLPCSTR pName)
{
	::ebProtoAddStruct(m_hTable,pName);
}	

_EBC_INLINE void CebProto::AddStructMember(ebLPCSTR pName, ebWORD wType, ebLPCSTR pExtType)
{
	::ebProtoAddStructMember(m_hTable,pName,wType,pExtType);
}

#ifdef EBWIN
/////////////////////////////////////////////////////////////////////
// Inlined CebRecorder methods
_EBC_INLINE CebRecorder::CebRecorder(HWND hWndParent,
								ebWORD wOptions,
								ebWORD wPasses,
								ebWORD wCallerMsg,
								ebWORD wKey1,
								ebWORD wKey2,
								ebWORD wKey3,
								ebLPCSTR pDisabledList,
								ebCKPROC pCKProc)
{
	m_hRecording = NULL;

	m_hWndParent = hWndParent;
	m_wOptions = wOptions;
	m_wPasses = wPasses;
	m_wCallerMsg = wCallerMsg;
	m_wKey1 = wKey1;
	m_wKey2 = wKey2;
	m_wKey3 = wKey3;
	m_pDisabledList = pDisabledList;
	m_pCKProc = pCKProc;
}

_EBC_INLINE CebRecorder::~CebRecorder()
{
	if (m_hRecording) ::GlobalFree(m_hRecording);
}

_EBC_INLINE HWND CebRecorder::GetParent() const
{
	return m_hWndParent;
}

_EBC_INLINE HWND CebRecorder::SetParent(HWND hWnd)
{
	HWND hwnd = m_hWndParent;

	m_hWndParent = hWnd;
	return hwnd;
}

_EBC_INLINE ebWORD CebRecorder::GetOptions() const
{
	return m_wOptions;
}

_EBC_INLINE ebWORD CebRecorder::SetOptions(ebWORD wOptions)
{
	ebWORD woptions = m_wOptions;

	m_wOptions = wOptions;
	return woptions;
}

_EBC_INLINE ebWORD CebRecorder::GetPasses() const
{
	return m_wPasses;
}

_EBC_INLINE ebWORD CebRecorder::SetPasses(ebWORD wPasses)
{
	ebWORD wpasses = m_wPasses;

	m_wPasses = wPasses;
	return wpasses;
}

_EBC_INLINE ebWORD CebRecorder::GetCallerMsg() const
{
	return m_wCallerMsg;
}

_EBC_INLINE ebWORD CebRecorder::SetCallerMsg(ebWORD wCallerMsg)
{
	ebWORD wcallmsg = m_wCallerMsg;

	m_wCallerMsg = wCallerMsg;
	return wcallmsg;
}

_EBC_INLINE void CebRecorder::GetKeys(ebWORD FAR* rgKeys)
{
	rgKeys[0] = m_wKey1;
	rgKeys[1] = m_wKey2;
	rgKeys[2] = m_wKey3;
}

_EBC_INLINE void CebRecorder::SetKeys(ebWORD wKey1, ebWORD wKey2, ebWORD wKey3)
{
	m_wKey1 = wKey1;
	m_wKey2 = wKey2;
	m_wKey3 = wKey3;
}

_EBC_INLINE ebLPSTR CebRecorder::GetDisabledList() const
{
	return (ebLPSTR) m_pDisabledList;
}

_EBC_INLINE LPSTR CebRecorder::SetDisabledList(ebLPCSTR pDisabledList)
{
	ebLPSTR plist = (ebLPSTR) m_pDisabledList;

	m_pDisabledList = pDisabledList;
	return plist;
}

_EBC_INLINE ebCKPROC CebRecorder::GetCKProc() const
{
	return m_pCKProc;
}

_EBC_INLINE ebCKPROC CebRecorder::SetCKProc(ebCKPROC pCKProc)
{
	ebCKPROC pckproc = m_pCKProc;

	m_pCKProc = pCKProc;
	return pckproc;
}

_EBC_INLINE ebBOOL CebRecorder::Start()
{
	return ::ebStartRecorder(m_hWndParent,m_wOptions,m_wPasses,m_wCallerMsg,m_wKey1,m_wKey2,m_wKey3,m_pDisabledList,m_pCKProc);
}

_EBC_INLINE void CebRecorder::Stop()
{
	m_hRecording = ::ebStopRecorder();
}

_EBC_INLINE void CebRecorder::Pause(BOOL bPause)
{
	::ebPauseRecorder(bPause);
}

_EBC_INLINE void CebRecorder::AddExternalText(ebLPCSTR pText)
{
	::ebAddExternalText(pText);
}

_EBC_INLINE HGLOBAL CebRecorder::GetRecording() const
{
	return m_hRecording;
}

_EBC_INLINE HGLOBAL CebRecorder::GetSafeHandle()
{
	HGLOBAL hmem = m_hRecording;

	m_hRecording = NULL;
	return hmem;
}
#endif // EBWIN

#if defined(EBWIN) || defined(EBWIN32)
/////////////////////////////////////////////////////////////////////
// Inlined CebDialogEditor methods
_EBC_INLINE CebDialogEditor::CebDialogEditor()
{
	m_pDlgInfo = NULL;
}

_EBC_INLINE CebDialogEditor::CebDialogEditor(ebLPDLGINFO pdi)
{
	m_pDlgInfo = pdi;
}

_EBC_INLINE CebDialogEditor::~CebDialogEditor()
{
}

_EBC_INLINE void CebDialogEditor::SetDlgInfo(ebLPDLGINFO pdi)
{
	m_pDlgInfo = pdi;
}

_EBC_INLINE ebLPDLGINFO CebDialogEditor::GetDlgInfo() const
{
	return m_pDlgInfo;
}

_EBC_INLINE int CebDialogEditor::Start()
{
	return ::ebStartDlgEditor(m_pDlgInfo);
}
#endif // EBWIN || EBWIN32

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)
/////////////////////////////////////////////////////////////////////
// CebDebugDlgInfo
_EBC_INLINE CebDebugDlgInfo::CebDebugDlgInfo(	ebHCODE hCode,	/* = NULL */
						short		x,		/* = CW_USEDEFAULT */
						short		y,		/* = CW_USEDEFAULT */
						short		nWidth,		/* = CW_USEDEFAULT */
						short		nHeight,	/* = CW_USEDEFAULT */
						short		nWatchWindowHeight,	/* = 0 */
						ebBOOL		bMatchCase,	/* = FALSE */
						ebLPCSTR	pszFindText,	/* = NULL */
						ebLPCSTR	pszReplaceText	/* = NULL */ )
{
	m_x = x;
	m_y = y;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nWatchWindowHeight = nWatchWindowHeight;
	m_bMatchCase = bMatchCase;
	*m_szFindText = '\0';
	if (pszFindText) ::strcpy(m_szFindText,pszFindText);
	*m_szReplaceText = '\0';
	if (pszReplaceText) ::strcpy(m_szReplaceText,pszReplaceText);
	m_pWatches = NULL;
	m_pScript = NULL;
	m_hCode = hCode;
}

_EBC_INLINE CebDebugDlgInfo::~CebDebugDlgInfo()
{
	if (m_pWatches) ::ebFreePtr(m_pWatches);
	if (m_pScript) ::ebFreePtr(m_pScript);
}

_EBC_INLINE short CebDebugDlgInfo::GetX() const
{
	return m_x;
}

_EBC_INLINE short CebDebugDlgInfo::GetY() const
{
	return m_y;
}

_EBC_INLINE short CebDebugDlgInfo::GetWidth() const
{
	return m_nWidth;
}

_EBC_INLINE short CebDebugDlgInfo::GetHeight() const
{
	return m_nHeight;
}

_EBC_INLINE short CebDebugDlgInfo::GetWatchWindowHeight() const
{
	return m_nWatchWindowHeight;
}

_EBC_INLINE ebBOOL CebDebugDlgInfo::GetMatchCase() const
{
	return m_bMatchCase;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::GetFindText() const
{
	return (ebLPSTR)m_szFindText;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::GetReplaceText() const
{
	return (ebLPSTR)m_szReplaceText;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::GetWatches() const
{
	return m_pWatches;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::DetachWatches()
{
	ebLPSTR pwatches = m_pWatches;

	m_pWatches = NULL;
	return pwatches;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::GetScript() const
{
	return m_pScript;
}

_EBC_INLINE ebLPSTR CebDebugDlgInfo::DetachScript()
{
	ebLPSTR pscript = m_pScript;
	
	m_pScript = NULL;
	return pscript;
}

_EBC_INLINE ebHCODE CebDebugDlgInfo::GetCode() const
{
	return m_hCode;
}

_EBC_INLINE ebHCODE CebDebugDlgInfo::DetachCode()
{
	
	ebHCODE hcode = m_hCode;
	
	m_hCode = NULL;
	return hcode;
}

/////////////////////////////////////////////////////////////////////
// CebDebuggerDlg
//
// The following are NOT inlined:
//		CebDebuggerDlg()
//		Invoke()
//		SaveState()
//		SaveScript()

//_EBC_INLINE CebDebuggerDlg::~CebDebuggerDlg()
//{
//}

_EBC_INLINE int CebDebuggerDlg::GetSCode() const
{
	return m_nScode;
}

_EBC_INLINE ebBOOL CebDebuggerDlg::IsSave() const
{
	return (m_nScode == DRC_SAVED);
}

_EBC_INLINE ebBOOL CebDebuggerDlg::IsCancel() const
{
	return (m_nScode == DRC_CANCEL);
}

_EBC_INLINE ebBOOL CebDebuggerDlg::IsError() const
{
	return (m_nScode == DRC_OUTOFMEMORY ||
		m_nScode == DRC_CANTCREATEWINDOW ||
		m_nScode == DRC_CANTFINDLIBRARY) ? TRUE : FALSE;
}
#endif // EBWIN | EBWIN32 | EBOS2

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)
/////////////////////////////////////////////////////////////////////
// CebDebugger
_EBC_INLINE CebDebugger::CebDebugger()
{
	m_hWndDebugger = NULL;
	m_hWndParent = NULL;
	m_X = 0;
	m_Y = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_dwStyle = 0;
	m_wId = 0;
#if defined(EBWIN) | defined(EBWIN32)
	m_hInstance = NULL;
#endif // EBWIN | EBWIN32
}

_EBC_INLINE CebDebugger::CebDebugger(	HWND 		hWndParent,
					int		x,
					int		y,
					int		width,
					int		height,
					ebDWORD		dwStyle,
					ebWORD		wId,
#if defined(EBWIN) | defined(EBWIN32)
					HINSTANCE	hInstance)
#else
					ebUINT		uDummy)
#endif // EBWIN | EBWIN32
{
// #HK950508 ------------------------------------------------------------------
	m_hWndParent = hWndParent;
//	m_hWndParent = NULL;
// #HK950508 ------------------------------------------------------------------
	m_X = x;
	m_Y = y;
	m_nWidth = width;
	m_nHeight = height;
	m_dwStyle = dwStyle;
	m_wId = wId;
#if defined(EBWIN) | defined(EBWIN32)
// #HK950508 ------------------------------------------------------------------
	m_hInstance = hInstance;
//	m_hInstance = NULL;
// #HK950508 ------------------------------------------------------------------
#endif // EBWIN | EBWIN32
}

_EBC_INLINE CebDebugger::~CebDebugger()
{
	if (m_hWndDebugger && ::IsWindow(m_hWndDebugger)) {
#if defined(EBWIN) | defined(EBWIN32)
		::DestroyWindow(m_hWndDebugger);
#else
		::WinDestroyWindow(m_hWndDebugger);
#endif // EBWIN | EBWIN32
	}
}

_EBC_INLINE HWND CebDebugger::GetParent() const
{
	return m_hWndParent;
}

_EBC_INLINE HWND CebDebugger::SetParent(HWND hWnd)
{
	HWND hwndT = m_hWndParent;
	
	m_hWndParent = hWnd;
	return hwndT;
}

_EBC_INLINE void CebDebugger::GetRect(int FAR* px, int FAR* py, int FAR* pwidth, int FAR* pheight) const
{
	*px = m_X;
	*py = m_Y;
	*pwidth = m_nWidth;
	*pheight = m_nHeight;
}

_EBC_INLINE void CebDebugger::SetRect(int x, int y, int width, int height)
{
	m_X = x;
	m_Y = y;
	m_nWidth = width;
	m_nHeight = height;
}

_EBC_INLINE ebDWORD CebDebugger::GetStyle() const
{
	return m_dwStyle;
}

_EBC_INLINE ebDWORD CebDebugger::SetStyle(ebDWORD dwStyle)
{
	ebDWORD dwstyleT = m_dwStyle;

	m_dwStyle = dwStyle;
	return dwstyleT;
}

_EBC_INLINE ebWORD CebDebugger::GetId() const
{
	return m_wId;
}

_EBC_INLINE ebWORD CebDebugger::SetId(ebWORD wId)
{
	ebWORD wIdT = m_wId;

	m_wId = wId;
	return wIdT;
}

#if defined(EBWIN) | defined(EBWIN32)
_EBC_INLINE void CebDebugger::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}
#endif // EBWIN | EBWIN32

_EBC_INLINE HWND CebDebugger::GetWindow() const
{
	return m_hWndDebugger;
}

_EBC_INLINE HWND CebDebugger::DetachWindow() 
{
	if (m_hWndDebugger && ::IsWindow(m_hWndDebugger))
	{
		HWND hWnd = m_hWndDebugger;
		m_hWndDebugger = NULL;
		return hWnd;
	}
	return NULL;
}

_EBC_INLINE void CebDebugger::DestroyWindow() const
{
	if (m_hWndDebugger && ::IsWindow(m_hWndDebugger)) {
#if defined(EBWIN) | defined(EBWIN32)
		::DestroyWindow(m_hWndDebugger);
#else
		::WinDestroyWindow(m_hWndDebugger);
#endif // EBWIN | EBWIN32
	}
}

#if defined(_OLD_BASICEXT)
_EBC_INLINE ebBOOL CebDebugger::Create()
{
#if defined(EBWIN) | defined(EBWIN32)
	m_hWndDebugger = ebCreateDebugger(	m_hWndParent,
						m_X,m_Y,m_nWidth,m_nHeight,
						m_dwStyle,
						m_wId,
						0,
						(ebINT)m_hInstance);
#else
	m_hWndDebugger = ebCreateDebugger(	m_hWndParent,
						m_X,m_Y,m_nWidth,m_nHeight,
						m_dwStyle,
						m_wId,
						0);
#endif // EBWIN | EBWIN32

	if (m_hWndDebugger == NULL) {
//		delete this;	//#HK950508
		return 0;
	}
	else return 1;
}
#endif // _OLD_BASICEXT

_EBC_INLINE void CebDebugger::SetThreadExtra(ebWORD iSz)
{
	ebDebugger_SetThreadExtra(m_hWndDebugger, iSz);
}

_EBC_INLINE ebBOOL CebDebugger::QueryClose() const
{
	return 1;
}

_EBC_INLINE void CebDebugger::EditUndo()
{
	ebDebugger_EditUndo(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EditClear()
{
	ebDebugger_EditClear(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EditCopy()
{
	ebDebugger_EditCopy(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EditCut()
{
	ebDebugger_EditCut(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EditPaste()
{
	ebDebugger_EditPaste(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::ToggleBreakpoint(ebWORD wLineNo)
{
	return ebDebugger_ToggleBreakpoint(m_hWndDebugger,wLineNo);
}

_EBC_INLINE void CebDebugger::ClearAllBreakpoints()
{
	ebDebugger_ClearAllBreakpoints(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::AddWatch(ebLPCSTR pExpression)
{
	return ebDebugger_AddWatch(m_hWndDebugger,pExpression);
}

_EBC_INLINE ebBOOL CebDebugger::DeleteWatch(ebLPCSTR pExpression)
{
	return ebDebugger_DeleteWatch(m_hWndDebugger,pExpression);
}

_EBC_INLINE ebBOOL CebDebugger::CanDeleteWatch()
{
	return ebDebugger_CanDeleteWatch(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::GetFirstWatch(ebLPSTR pBuffer, ebINT iLen)
{
	return ebDebugger_GetFirstWatch(m_hWndDebugger,pBuffer, iLen);
}

_EBC_INLINE ebBOOL CebDebugger::GetNextWatch(ebLPSTR pBuffer, ebINT iLen)
{
	return ebDebugger_GetNextWatch(m_hWndDebugger,pBuffer,iLen);
}

_EBC_INLINE ebWORD CebDebugger::GetTextLength() const
{
	return ebDebugger_GetTextLength(m_hWndDebugger);
}

_EBC_INLINE ebWORD CebDebugger::GetText(ebLPSTR pText, ebWORD wBufSize)
{
	return ebDebugger_GetText(m_hWndDebugger,wBufSize,pText);
}

_EBC_INLINE ebBOOL CebDebugger::SetText(ebLPCSTR pText)
{
	return ebDebugger_SetText(m_hWndDebugger,pText);
}

_EBC_INLINE ebLONG CebDebugger::FindText(ebLPCSTR pText,
					int nDirection,		/* = 1, forward direction */
					ebBOOL bMatchCase,	/* = 0, case-insensitive */
					ebBOOL bMatchWholeWord)
{
	ebWORD wFlags = ebFIND_SELECT|ebFIND_VIEW;
		
		if(nDirection == 1) wFlags = wFlags|ebFIND_DOWN;
		else wFlags = wFlags|ebFIND_UP;

		if (bMatchCase) wFlags = wFlags|ebFIND_MATCHCASE;
		
		if (bMatchWholeWord) wFlags = wFlags|ebFIND_WHOLEWORD;

	return ebDebugger_Find(m_hWndDebugger,wFlags,pText);
}

_EBC_INLINE ebBOOL CebDebugger::GetModified() const
{
	return ebDebugger_GetDirty(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::SetModified(ebBOOL bModified)
{
	ebDebugger_SetDirty(m_hWndDebugger,bModified);
}

_EBC_INLINE ebBOOL CebDebugger::CanUndo() const
{
	return ebDebugger_CanUndo(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::GetCaretWord(ebLPSTR pBuffer, ebWORD wBufSize)
{
	return ebDebugger_GetWord(m_hWndDebugger,pBuffer,wBufSize);
}

_EBC_INLINE ebBOOL CebDebugger::SetCaretPos(int x, int y, ebBOOL bExtend /* = FALSE */)
{
	return ebDebugger_SetCursorPos(m_hWndDebugger,x,y,bExtend);
}

_EBC_INLINE ebWORD 	CebDebugger::GetNumLines(void)
{
	return ebDebugger_GetNumLines(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::GetSelectionOffsets(int FAR* pnStart, int FAR* pnEnd)
{
	ebSEL ebS;

	ebDebugger_GetSel(m_hWndDebugger, &ebS);
	*pnStart = (int)ebS.wStart;
	*pnEnd = (int)ebS.wEnd;
}

_EBC_INLINE int CebDebugger::GetSelection(ebLPSTR pBuffer, ebWORD wBufSize)
{
	return ebDebugger_GetSelText(m_hWndDebugger,pBuffer,wBufSize);
}

_EBC_INLINE ebBOOL CebDebugger::HasSelection() const
{
	return ebDebugger_IsSelection(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::ReplaceSelection(ebLPCSTR pText, ebBOOL bSelect /* = FALSE */ )
{
	return ebDebugger_ReplaceSel(m_hWndDebugger,pText,bSelect);
}

_EBC_INLINE ebBOOL CebDebugger::EnableTextColors(ebBOOL bEnabled /* = TRUE */)
{
	return ebDebugger_EnableTextColors(m_hWndDebugger,bEnabled);
}

_EBC_INLINE void CebDebugger::GetTextColors(ebLPTEXTCOLORS pColors)
{
	ebDebugger_GetTextColors(m_hWndDebugger,pColors);
}

_EBC_INLINE ebHFONT CebDebugger::GetFont() const
{
	return ebDebugger_GetFont(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::SetFont(ebHFONT hFont)
{
	ebDebugger_SetFont(m_hWndDebugger,hFont);
}

_EBC_INLINE ebWORD CebDebugger::GetWatchWindowHeight() const
{
	return ebDebugger_GetWatchWindowHeight(m_hWndDebugger);
}

_EBC_INLINE ebWORD CebDebugger::SetWatchWindowHeight(ebWORD wHeight)
{
	ebWORD wHeightT = GetWatchWindowHeight();

	ebDebugger_SetWatchWindowHeight(m_hWndDebugger,wHeight);
	return wHeightT;
}

_EBC_INLINE void CebDebugger::StepOver()
{
	ebDebugger_Step(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::TraceInto()
{
	ebDebugger_Trace(m_hWndDebugger);
}

_EBC_INLINE ebWORD CebDebugger::GetCurrentLine() const
{
	return ebDebugger_GetCurLine(m_hWndDebugger);
}

_EBC_INLINE ebDWORD CebDebugger::GetCursorPos() const
{
	return ebDebugger_GetCursorPos(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::SetNextLine(ebWORD wLineNo)
{
	return ebDebugger_SetNext(m_hWndDebugger,wLineNo);
}

_EBC_INLINE void CebDebugger::InvokeGotoLineDialogBox()
{
	ebDebugger_GotoLineDialog(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::InvokeModifyVarDialogBox(ebBOOL bUseSelectedItem /* = TRUE */)
{
	ebDebugger_ModifyDialog(m_hWndDebugger,bUseSelectedItem);
}

_EBC_INLINE void CebDebugger::InvokeCallsDialogBox()
{
	ebDebugger_CallsDialog(m_hWndDebugger);
}

#if defined(EBWIN) || defined(EBWIN32)
_EBC_INLINE ebBOOL CebDebugger::IsDialogSelected() const
{
	return ebDebugger_IsDialogSelected(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EditDialog()
{
	ebDebugger_EditDialog(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::InsertDialog()
{
	return ebDebugger_InsertDialog(m_hWndDebugger);
}
#endif // EBWIN || EBWIN32

_EBC_INLINE ebBOOL CebDebugger::EnableCtrlBreak(ebBOOL bEnabled /* = TRUE */)
{
	return ebDebugger_EnableBreak(m_hWndDebugger,bEnabled);
}

_EBC_INLINE void CebDebugger::StartScript()
{
	ebDebugger_Start(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::PauseScript()
{
	ebDebugger_Pause(m_hWndDebugger);
}

_EBC_INLINE void CebDebugger::EndScript()
{
	ebDebugger_End(m_hWndDebugger);
}

_EBC_INLINE CebScript FAR* CebDebugger::GetScript(ebBOOL isWantOwnership) const
{
ebHSCRIPT hScript = ebDebugger_GetScript(m_hWndDebugger, isWantOwnership);

	return (hScript) ? CebScript::FromHandle(hScript) : NULL;
}

_EBC_INLINE CebThread FAR* CebDebugger::GetThread(ebBOOL isWantOwnership) const
{
	ebHTHREAD hThread = ebDebugger_GetThread(m_hWndDebugger, isWantOwnership);

	return (hThread) ? CebThread::FromHandle(hThread) : NULL;
}

_EBC_INLINE void CebDebugger::SetInstance(CebInstance FAR* pInstance)
{
	ebDebugger_SetInstance(m_hWndDebugger,pInstance->GetHandle());
}

_EBC_INLINE void CebDebugger::SetNumericDisplayBase(ebWORD wBase)
{
	ebDebugger_SetDisplayFormat(m_hWndDebugger,wBase);
}

_EBC_INLINE void CebDebugger::SetEntryPoint(ebLPENTRYINFO pEntryInfo)
{
	ebDebugger_SetEntry(m_hWndDebugger,pEntryInfo);
}

_EBC_INLINE ebDWORD CebDebugger::GetScope()
{
	return ebDebugger_GetScope(m_hWndDebugger);
}

_EBC_INLINE ebHCODE CebDebugger::GetCode(ebBOOL	bWantOwnership /* = TRUE */)
{
	return ebDebugger_GetCode(m_hWndDebugger,bWantOwnership);
}

_EBC_INLINE void CebDebugger::SetCode(ebHCODE hCode)
{
	ebDebugger_SetCode(m_hWndDebugger,hCode);
}

_EBC_INLINE ebBOOL CebDebugger::Compile(ebBOOL bDisplayError /* = TRUE */)
{
	return ebDebugger_Compile(m_hWndDebugger,bDisplayError);
}

_EBC_INLINE ebBOOL CebDebugger::ConfineDebugging(ebBOOL bConfine)
{
	return ebDebugger_Confine(m_hWndDebugger,bConfine);
}

_EBC_INLINE int CebDebugger::GetState() const
{
	return ebDebugger_GetState(m_hWndDebugger);
}

_EBC_INLINE ebBOOL CebDebugger::SetAutoCase(ebBOOL fisAutoCase)
{	
return ebDebugger_SetAutoCase(m_hWndDebugger, fisAutoCase);
}

_EBC_INLINE ebBOOL CebDebugger::SetAutoIndent(ebBOOL fisAutoIndent)
{
return ebDebugger_SetAutoIndent(m_hWndDebugger, fisAutoIndent);
}

#if defined(EBWIN) | defined(EBWIN32)
_EBC_INLINE void CebDebugger::SetHelpMode(ebBOOL bIsHelpMode, HCURSOR hCursor)
{
	ebDebugger_SetHelpMode(m_hWndDebugger,bIsHelpMode,hCursor);
}
#endif // EBWIN | EBWIN32

_EBC_INLINE ebKEYBOARDFILTERPROC CebDebugger::SetKeyboardFilter(ebKEYBOARDFILTERPROC pfnFilter)
{
	return ebDebugger_SetKeyboardFilter(m_hWndDebugger,pfnFilter);
}

_EBC_INLINE void CebDebugger::SetNotificationProc(ebNOTIFICATIONPROC lpfnNotifyProc)
{
	ebDebugger_SetNotificationProc(m_hWndDebugger,lpfnNotifyProc);
}

_EBC_INLINE void CebDebugger::SetNotificationData(long lData)
{
	ebDebugger_SetNotificationData(m_hWndDebugger,lData);
}
#endif // EBWIN | EBWIN32 | EBOS2

/////////////////////////////////////////////////////////////////////
// Inlined CebCompiler methods
_EBC_INLINE CebCompiler::CebCompiler()
{
}

_EBC_INLINE CebCompiler::~CebCompiler()
{
}

_EBC_INLINE ebWORD CebCompiler::Compile(ebLPCOMPILESTRUCT pCompileStruct)
{
	return ::ebCompile(pCompileStruct);
}
