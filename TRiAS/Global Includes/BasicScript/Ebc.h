///////////////////////////////////////////////////////////
// ebc.h (draft 0.21)
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
// READ ME
//
// Two features planned for the BasicScript 2.1 Classes C++ library are not 
// implemented in this release.
// 1.	The API function
//		::ebRegisterExtensionsV(m_hInstance,pName,pfnCallback,&args);
//		although defined in <eb.h> is not implemented in the BasicScript
//		library.
// 2.	The Runtime class determination for the classes
//			CebObject
//			CebCode
//			CebThread
//			CebScript
//			CebInstance
//		is not implemented. The actual need for this feature is
//		being considered.
//		Please note that the classes CebCode, CebThread,
//		CebScript, CebInstance are derived from CebObject.
//
// !!! Your feedback on the BasicScript classes design is
// !!! greatly welcomed.
// !!! Please contact Hisur Yu at Summit Software Company
// !!! by one of the following means:
//		Phone: 315/445-9000 ext. 25
//		E-mail: hsy@summsoft.com
//              Fax: 315/445-9567
//
///////////////////////////////////////////////////////////
// CHANGES
//	draft 0.1
//		created
//
//	draft 0.2
//	1.	Defined the following:
//		__EBC_H_
//		_EBC_ENABLE_INLINES
//		_EBC_INLINE
//	2.	Removed the body of ebc.cpp and replaced with #include <ebc.inl>
//	3.	Replaced CProto::AddEntry() methods with:
//		AddEntryCmd() and AddEntryFunction() methods

#ifndef __EBC_H_
#  define __EBC_H_

#include <eb.h>

#ifndef NULL
#include <stdio.h>
#endif

#ifdef EBOS2
#  undef ebCAPI
#  define ebCAPI
#endif // EBOS2

///////////////////////////////////////////////////////////
// Classes declared in this file
//	(in addition for standard primitive data types and
//	 various helper macros).

class FAR CebObject;
	class FAR CebCode;
	class FAR CebThread;
	class FAR CebScript;
	class FAR CebInstance;

class FAR CebMemory;
class FAR CebArray;
class FAR CebString;
class FAR CebEntryInfo;
class FAR CebArgs;
class FAR CebProto;
class FAR CebDebuggerDlg;
class FAR CebRecorder;
class FAR CebDialogEditor;
class FAR CebDebugDlgInfo;
class FAR CebDebuggerDlg;
class FAR CebDebugger;
class FAR CebCompiler;

/////////////////////////////////////////////////////////////////////
// CebObject - Root object
class FAR CebObject
{
public:
	CebObject();
	virtual ~CebObject();
};

/////////////////////////////////////////////////////////////////////
// CebMemory
class FAR CebMemory
{
private:
	ebHOBJECT	m_hObject;
	ebHSUB		m_hMem;

public:
	CebMemory(CebThread FAR* pObject);
	CebMemory(CebScript FAR* pObject);
	CebMemory(CebInstance FAR* pObject);
	virtual ~CebMemory();

public:
	ebBOOL	Alloc(ebWORD wSize);
	ebBOOL	ReAlloc(ebWORD wSize);
	void	Free();
	ebLPVOID	Lock();
	void	Unlock();
	void	SetOwner(CebThread FAR* pObject);
	void	SetOwner(CebScript FAR* pObject);
	void	SetOwner(CebInstance FAR* pObject);
};

/////////////////////////////////////////////////////////////////////
// CebArray
class FAR CebArray
{
private:
	ebHOBJECT	m_hObject;
	ebHSUB		m_hArray;
	ebLPARRAY	m_pArray;

public:
	CebArray(CebThread FAR* pObject);
	CebArray(CebScript FAR* pObject);
	CebArray(CebInstance FAR* pObject);
	virtual ~CebArray();

public:
	ebBOOL	Create(ebBOOL bFixed, ebWORD wType, ebWORD wExtType, int nDims,...);
	void	Free();
	void	Lock();
	void	Unlock();
	ebLPVOID	LockData();
	void	UnlockData();
	int		Redim(ebWORD wElements);
	void	SetOwner(CebThread FAR* pObject);
	void	SetOwner(CebScript FAR* pObject);
	void	SetOwner(CebInstance FAR* pObject);
};

/////////////////////////////////////////////////////////////////////
// CebString
class FAR CebString
{
private:
	ebHOBJECT	m_hObject;
	ebHSUB		m_hStr;

public:
	CebString(CebThread FAR* pObject);
	CebString(CebScript FAR* pObject);
	CebString(CebInstance FAR* pObject);
	virtual ~CebString();

public:
	ebBOOL	Create(ebWORD wSize);
	ebBOOL	Create(ebLPCSTR pStr);
	void	Free();
	ebLPSTR	Lock();
	void	Unlock();
	void	SetOwner(CebThread FAR* pObject);
	void	SetOwner(CebScript FAR* pObject);
	void	SetOwner(CebInstance FAR* pObject);
};

/////////////////////////////////////////////////////////////////////
// CebEntryInfo
class FAR CebEntryInfo {
private:
	ebENTRYINFO	m_EntryInfo;

public:
	CebEntryInfo();
	CebEntryInfo(ebLPENTRYINFO pEntryInfo);
	~CebEntryInfo();
	
	void SetEntryInfo(ebLPENTRYINFO pEntryInfo);
	void GetEntryInfo(ebLPENTRYINFO pEntryInfo) const;
	ebLPENTRYINFO GetEntryInfo();
	
	void SetEntryName(ebLPCSTR pszName);
	void GetEntryName(ebLPSTR pszName) const;

	ebDWORD SetEntryId(ebDWORD dwId);
	ebDWORD GetEntryId() const;
	
	ebWORD SetParamsCount(ebWORD wParams);
	ebWORD GetParamsCount() const;
	
	ebLPPARAM SetParams(ebLPPARAM prgParams);
	ebLPPARAM GetParams() const;
	
	void SetRetType(ebLPPARAM pRetType);
	void GetRetType(ebLPPARAM pRetType) const;
	
	int SetMethodType(int nType);
	int GetMethodType() const;

	ebBOOL IsFunction() const;
	ebBOOL IsSub() const;

private:
	static char FAR* pszMain;
};

/////////////////////////////////////////////////////////////////////
// CebCode

class FAR CebCode : public CebObject
{
private:
	ebHCODE		m_hCode;
	ebHENUM		m_hEnumMember;
	ebHENUM		m_hEnumProc;
	ebHENUM		m_hEnumVar;

public:
	CebCode();
	virtual ~CebCode();
	
	virtual void Initialize();
	virtual ebBOOL IsEmpty() const;
	
	static void Initialize(ebHCODE *phCode);
	static void FreeCode(ebHCODE hCode);
	
	ebHCODE Get();
	void Get(ebHCODE *phCode) const;
	void Set(ebHCODE hCode);
	ebHCODE Detach(ebHCODE hCode = NULL);
	void FreeCode();

public:
	int CheckEntry(ebLPENTRYINFO pEntryInfo);

	ebBOOL	GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;
	
	ebBOOL	GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const;
	
	ebBOOL	GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const;

	ebBOOL	GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;

	ebBOOL	GetMemberInfo(ebWORD wExtType, ebLPCSTR pMemberName, ebLPVARIABLEINFO pVarInfo) const;

	void	GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const;

	ebHENUM GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextMember(ebLPVARIABLEINFO pVarInfo);
	void	CloseMemberEnum();

	ebHENUM GetFirstProc(ebLPPROCINFO pProcInfo);
	ebBOOL	GetNextProc(ebLPPROCINFO pProcInfo);
	void	CloseProcEnum();

	ebHENUM GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextVar(ebLPVARIABLEINFO pvi);
	void	CloseVarEnum();
};

/////////////////////////////////////////////////////////////////////
// CebThread
class FAR CebThread : public CebObject
{
private:
	ebHTHREAD	m_hThread;
	ebHENUM		m_hEnumCall;
	ebHENUM		m_hEnumMember;
	ebHENUM		m_hEnumProc;
	ebHENUM		m_hEnumVar;

	CebScript FAR*	m_pScript;
	ebHSCRIPT	m_hScript;
	ebLPENTRYINFO	m_pEntryInfo;
	
private:
	// Methods for Get from and Set to CebThread object for hThread
	static CebThread FAR* GetThis(ebHTHREAD hThread);
	void SetThis();

public:
	CebThread(CebScript FAR* pScript, ebLPENTRYINFO	pEntryInfo = NULL);
	CebThread(ebHSCRIPT hScript, ebLPENTRYINFO pEntryInfo = NULL);
	virtual ~CebThread();

public:
	int Create(int iExtraBuffer);
	ebHTHREAD Attach (ebHTHREAD hThread);
	ebHTHREAD Detach (void);
	
	// Get/Set ebENTRYINFO
	ebLPENTRYINFO SetEntryInfo(ebLPENTRYINFO pEntryInfo);
	ebLPENTRYINFO GetEntryInfo() const;
	
public:
	// Retrieve the ebHTHREAD handle for ebThread object
	ebHTHREAD GetHandle() const;
	static CebThread FAR* FromHandle(ebHTHREAD hThread);

	CebScript FAR* GetScript() const;
	CebInstance FAR* GetInstance() const;
	
public:
	// Error retrieval methods
	ebLONG	GetErrorLine() const;
	ebLONG	GetErrorNumber() const;

#if defined(EBWIN) | defined(EBMAC)
	// Math error checking method
	void	CheckMathError();
#endif // EBWIN | EBMAC

	// Debugging/Breakpoint methods
	ebBOOL	ClearBreakpoint(ebWORD wLineNo);
	void	ClearBreakpoints();
	ebBOOL	SetBreakpoint(ebWORD wLineNo);
	void	ConfineDebugging(CebScript FAR* pScript);
	ebBOOL	SetNextLine(ebWORD wLineNo);
	ebBOOL	StepOver();
	ebBOOL	TraceInto();

	// Method for obtaining debugging environment information
	void	GetDebugInfo(ebLPDBGINFO pDebugInfo) const;

	// Installable Runtime error proc (ebERRORPROC) method
	void	SetRuntimeErrorProc(ebERRORPROC pfnError, ebDWORD dwValue);

	// Installable Print proc (ebPRINTPROC) method
	void	SetPrintProc(ebPRINTPROC pfnPrint, ebDWORD dwValue);

	// Thread runtime methods
	void	Start();
	void	EnableCtrlBreak(ebBOOL bEnabled = 1 /* TRUE */);
	ebLONG	GetState() const;
	void	Interrupt(int nInterruptCode, int nErrorCode);
	ebBOOL	IsInterrupted() const;
	void	RuntimeError(ebWORD wErrorNo, ebLPCSTR pMsg, ebBOOL bFatal = 1 /* TRUE */);
	void	SetLinkOptions(ebDWORD dwOptions);
	void	SetStackSize(ebDWORD dwSize);

	// Thread environment methods
	void	SetCommandLine(ebLPCSTR pCommandLine);
	void	SetHomeDir(ebLPCSTR pHomeDir);
	
	// Thread Option base method
	int		GetOptionBase() const;
	
#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
	// OLE 2.0 Object methods
	ebDWORD	CreateObjectId(const LPDISPATCH pDispatch);
	void	FreeObjectId(ebDWORD dwId);
	LPDISPATCH	GetDispatch(ebDWORD dwId) const;
#endif // EBWIN | EBWIN32 | EBMAC

	// Method for obtaining object information
	ebBOOL	GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;

	// Method for proc/function information
	ebBOOL	GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const;
	
	// Method for obtaining variable information
	ebBOOL	GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const;
	// Method for Get/Set variable value
	ebINT GetVarValue(ebHINSTANCE hInst, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const;
	ebINT SetVarValue(ebHINSTANCE hInst, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar);

	// Method for obtaining structure information
	ebBOOL	GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure member information
	ebBOOL	GetMemberInfo(ebWORD wExtType, ebLPCSTR pMemberName, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure's array member information
	void	GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const;

	// Call enumeration methods
	ebHENUM GetFirstCall(ebLPPROCINFO pProcInfo, ebLPWORD pwLineNo = NULL);
	ebBOOL	GetNextCall(ebLPPROCINFO pProcInfo, ebLPWORD pwLineNo = NULL);
	void	CloseCallEnum();

	// Proc enumeration methods
	ebHENUM GetFirstProc(ebLPPROCINFO pProcInfo);
	ebBOOL	GetNextProc(ebLPPROCINFO pProcInfo);
	void	CloseProcEnum();

	// Structure member enumeration methods
	ebHENUM GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextMember(ebLPVARIABLEINFO pVarInfo);
	void	CloseMemberEnum();

	// Variable enumeration methods
	ebHENUM GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextVar(ebLPVARIABLEINFO pVarInfo);
	void	CloseVarEnum();

	// Thread parameter Get/Set methods
	ebLPVOID GetParamPtr(ebWORD wIndex) const;
	ebBOOL	GetParamArray(ebWORD wIndex, ebLPHSUB phArray) const;
	ebBOOL	GetParamBool(ebWORD wIndex, short FAR* pShort) const;
	ebBOOL	GetParamCurrency(ebWORD wIndex, ebLPCURRENCY pCurrency) const;
	ebBOOL	GetParamDate(ebWORD wIndex, double FAR* pDate) const;
	ebBOOL	GetParamDouble(ebWORD wIndex, double FAR* pDouble) const;
	ebBOOL	GetParamInt(ebWORD wIndex, ebLPWORD pWord) const;
	ebBOOL	GetParamLong(ebWORD wIndex, long FAR* pLong) const;
	ebBOOL	GetParamObject(ebWORD wIndex, ebLPDWORD pdwObject) const;
	ebBOOL	GetParamOleObject(ebWORD wIndex, ebLPDWORD pdwId) const;
	ebBOOL	GetParamSingle(ebWORD wIndex, float FAR* pFloat) const;
	ebBOOL	GetParamString(ebWORD wIndex, ebLPHSUB pStr) const;
	ebBOOL	GetParamStruct(ebWORD wIndex, ebLPSTR pStruct) const;
	ebBOOL	GetParamVariant(ebWORD wIndex, ebLPVARIANT pVariant) const;
	
	ebBOOL	SetParamBool(ebWORD wIndex, ebBOOL boolVal);
	ebBOOL	SetParamCurrency(ebWORD wIndex, ebCURRENCY cy);
	ebBOOL	SetParamDate(ebWORD wIndex, double date);
	ebBOOL	SetParamDouble(ebWORD wIndex, double d);
	ebBOOL	SetParamInt(ebWORD wIndex, short i);
	ebBOOL	SetParamLong(ebWORD wIndex, long l);
	ebBOOL	SetParamObject(ebWORD wIndex, ebDWORD dwObject);
	ebBOOL	SetParamOleObject(ebWORD wIndex, ebDWORD dwId);
	ebBOOL	SetParamSingle(ebWORD wIndex, float f);
	ebBOOL	SetParamString(ebWORD wIndex, ebHSUB hStr);
	ebBOOL	SetParamVariant(ebWORD wIndex, ebVARIANT Variant);

	// Variant methods
	int	VariantConvert(ebLPVARIANT pSource, ebLPVARIANT pDest, ebWORD wWantType);
	void	VariantFree(ebLPVARIANT pVariant);

	// Method for obtaining a formatted string for the specified data
	int	Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const;

	// Get/Set extension data methods
	ebDWORD	GetExtensionData() const;
	void	SetExtensionData(ebDWORD dwValue);

	// Get/Set methods for accessing Thread extra bytes
	ebWORD	GetWord(ebDWORD dwIndex) const;
	ebWORD	SetWord(ebDWORD dwIndex);
	ebLONG	SetLong(ebDWORD dwIndex);

	void	SetLong(ebDWORD dwOffset, long lValue);
	long	GetLong(ebDWORD dwOffset) const;

	// Send ebTM_* messages to Thread method
	ebLONG	SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam);
};

/////////////////////////////////////////////////////////////////////
// CebScript
class FAR CebScript : public CebObject
{
private:
	ebHSCRIPT	m_hScript;
	ebHENUM		m_hEnumMember;
	ebHENUM		m_hEnumProc;
	ebHENUM		m_hEnumVar;
		
	CebInstance FAR* m_pInstance;
	ebHCODE	m_hCode;
	ebLPSTR		m_pErrorBuffer;
	int		m_nBufferLength;

private:
	static CebScript FAR* GetThis(ebHSCRIPT hScript);
	void SetThis();

public:
	CebScript(CebInstance FAR* pInstance,
		  ebHCODE	hCode = NULL,
		  ebLPSTR	pErrorBuffer = NULL,
		  int		nBufferLength = 0);
	virtual ~CebScript();

public:
	int Create();
	ebHCODE SetCode(ebHCODE hCode);
	ebHCODE GetCode() const;
	
	// Set Error buffer
	void SetErrorBuffer(ebLPSTR pErrorBuffer, int nBufferLength);

public:
	// Retrieve the ebHSCRIPT handle for ebScript object
	ebHSCRIPT GetHandle() const;
	static CebScript FAR* FromHandle(ebHSCRIPT hScript);
	
	ebHSCRIPT Detach (void);

	CebInstance FAR* GetInstance() const;

	// Query external functions/subroutines resolved method
	ebBOOL Link(ebLPPROCINFO pProcInfo) const;

	// Debugging/Breakpoint methods
	ebBOOL	ClearBreakpoint(ebWORD wLineNo);
	void	ClearBreakpoints();
	ebBOOL	SetBreakpoint(ebWORD wLineNo);
	
	// Method for obtaining object information
	ebBOOL	GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;

	// Method for proc/function information
	ebBOOL	GetProcInfo(ebLPCSTR pName, ebLPPROCINFO pProcInfo) const;
	
	// Method for obtaining variable information
	ebBOOL	GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const;
	// Method for Get/Set variable value
	ebINT GetVarValue(ebHINSTANCE hInst, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const;
	ebINT SetVarValue(ebHINSTANCE hInst, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar);

	// Method for obtaining structure information
	ebBOOL	GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure member information
	ebBOOL	GetMemberInfo(ebWORD wExtType, ebLPCSTR pMemberName, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure's array member information
	void	GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const;

	// Proc enumeration methods
	ebHENUM GetFirstProc(ebLPPROCINFO pProcInfo);
	ebBOOL	GetNextProc(ebLPPROCINFO pProcInfo);
	void	CloseProcEnum();

	// Structure member enumeration methods
	ebHENUM GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextMember(ebLPVARIABLEINFO pVarInfo);
	void	CloseMemberEnum();

	// Variable enumeration methods
	ebHENUM GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextVar(ebLPVARIABLEINFO pVarInfo);
	void	CloseVarEnum();

	// Variant method
	void	VariantFree(ebLPVARIANT pVariant);

	// Method for obtaining a formatted string for the specified data
	int		Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const;
	
	// Send ebSM_* messages to Script method
	ebLONG	SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam);
};

/////////////////////////////////////////////////////////////////////
// CebInstance
class FAR CebInstance : public CebObject
{
private:
	ebHINSTANCE	m_hInstance;
	ebWORD	m_wFlags;
	ebEXTENUMPROC	m_pfnGetExtension;
	ebHENUM	m_hEnumMember;
	ebHENUM	m_hEnumVar;
	ebDWORD m_dwData;

	enum { nInitFlags = EBINIT_USECOMPILER | EBINIT_USERUNTIME | EBINIT_SEARCH_DIRECTORY };

private:
	static CebInstance FAR* GetThis(ebHINSTANCE hInstance);
	void SetThis();

public:
	CebInstance(ebWORD wFlags = nInitFlags, ebEXTENUMPROC pfnGetExtension = NULL, ebDWORD dwData = 0L);
	virtual ~CebInstance();

public:
	int Create();

public:
	// Retrieve the ebHINSTANCE handle for ebInstance object
	ebHINSTANCE GetHandle() const;
	static CebInstance FAR* FromHandle(ebHINSTANCE hInstance);

#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
	// Constant OLE object registeration function
	void	RegisterObject(ebDWORD dwConstId, const LPDISPATCH pDispatch);
#endif // EBWIN | EBWIN32 | EBMAC

	// Installable Compiler error proc (ebERRORPROC) methods
	void	GetCompilerErrorProc(ebERRORPROC FAR* ppfnError, ebDWORD FAR* pdwValue) const;
	void	SetCompilerErrorProc(ebERRORPROC pfnError, ebDWORD dwValue);

	// Installable Runtime error proc (ebERRORPROC) methods
	void	GetRuntimeErrorProc(ebERRORPROC FAR* ppfnError, ebDWORD FAR* pdwValue) const;
	void	SetRuntimeErrorProc(ebERRORPROC pfnError, ebDWORD dwValue);

	// Installable Runtime Pcode callback proc (ebPCODECALLBACKPROC) methods
	void	GetPcodeCallbackProc(ebPCODECALLBACKPROC FAR* ppfnCallback, ebDWORD FAR* pdwValue) const;
	void	SetPcodeCallbackProc(ebPCODECALLBACKPROC pfnCallback, ebDWORD dwValue);
	
	// Installable Print proc (ebPRINTPROC) methods
	void	GetPrintProc(ebPRINTPROC FAR* ppfnPrint, ebDWORD FAR* pdwValue) const;
	void	SetPrintProc(ebPRINTPROC pfnPrint, ebDWORD dwValue);

	// Installable Requestor proc (ebREQUESTORPROC) method
	void	SetRequestorProc(ebREQUESTORPROC pfnRequestor, ebDWORD dwValue);

	// Extension register and unregister methods
	ebBOOL	RegisterExtensions(ebLPCSTR pName, ebLPCSTR pTable, ebCALLBACKPROC pfnCallback);
	ebBOOL ebCAPI RegisterExtensionsEx(ebLPCSTR pName, ebCALLBACKPROC pfnCallback, ...);
	void	UnRegisterExtensions(ebLPCSTR pName);
	
	// Instance runtime environment methods
	void	SetPublicSpace(ebDWORD dwSize);
	void	ResetPublicVariables();
	void	LoadProcessData();
	void	SetLinkOptions(ebDWORD dwOptions);

	// Instance environment methods
	void	SetCommandLine(ebLPCSTR pCommandLine);
	void	SetHomeDir(ebLPCSTR pHomeDir);

	// Country information methods
	void	GetCountryInfo(ebCOUNTRY FAR* pCountry) const;
	void	SetCountryInfo(ebCOUNTRY FAR* pCountry);

	// OS specific data methods
	ebLONG	GetOSValue(int index) const;
	void	SetOSValue(int index, ebLONG lValue);
// #HK950509 ------------------------------------------------------------------
	ebHWND	GetWindow (void) const;
	void	SetWindow (ebHWND hWnd);
	
	void	SetViewportParent(ebHWND hWnd);

// #HK950509 ------------------------------------------------------------------

	// Method for obtaining object information
	ebBOOL	GetObjectInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetObjectInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;
	
	// Method for obtaining variable information
	ebBOOL	GetVarInfo(ebLPCSTR pName, ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo) const;
	// Method for Get/Set variable value
	ebINT	GetVarValue(ebHSCRIPT hScript, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar, ebLPWORD pwType, ebLPWORD pwExtType) const;
	ebINT	SetVarValue(ebHSCRIPT hScript, ebHTHREAD hThread, ebLPCSTR pExpression, ebDWORD dwContext, ebLPVARIABLE pVar);

	// Method for obtaining structure information
	ebBOOL	GetStructInfo(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo) const;
	ebBOOL	GetStructInfo(ebLPCSTR pType, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure member information
	ebBOOL	GetMemberInfo(ebWORD wExtType, ebLPCSTR pMemberName, ebLPVARIABLEINFO pVarInfo) const;
	// Method for obtaining structure's array member information
	void	GetMemberArrayHeader(ebLPVARIABLEINFO pVarInfo, ebLPARRAY pArray) const;

	// Variable enumeration methods
	ebHENUM GetFirstVar(ebDWORD dwContext, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextVar(ebLPVARIABLEINFO pVarInfo);
	void	CloseVarEnum();

	// Structure member enumeration methods
	ebHENUM GetFirstMember(ebWORD wExtType, ebLPVARIABLEINFO pVarInfo);
	ebBOOL	GetNextMember(ebLPVARIABLEINFO pVarInfo);
	void	CloseMemberEnum();

	// Method for obtaining a formatted string for the specified data
	int		Format(ebWORD wType, ebLPVOID pSource, ebLPCSTR pFormat, ebLPSTR pDest, int nSize) const;

	// Get/Set extension data methods
	ebDWORD	GetExtensionData() const;
	void	SetExtensionData(ebDWORD dwValue);
	
	// Send ebIM_* messages to Instance method
	ebLONG	SendMessage(ebUINT umsg, ebDWORD dwParam, ebLONG lParam);
};

/////////////////////////////////////////////////////////////////////
// CebArgs
class FAR CebArgs
{
private:
	ebARGS	m_pArgs;
	
public:
	CebArgs(ebARGS pArgs);
	~CebArgs();

public:
	ebHSUB	GetArray(ebWORD wIndex) const;
	short	GetBool(ebWORD wIndex) const;
	ebCURRENCY	GetCurrency(ebWORD wIndex) const;
	double	GetDate(ebWORD wIndex) const;
	double	GetDouble(ebWORD wIndex) const;
	ebWORD	GetInt(ebWORD wIndex) const;
	ebDWORD	GetLong(ebWORD wIndex) const;
	ebDWORD	GetObject(ebWORD wIndex) const;
#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
	ebDWORD	GetOleObject(ebWORD wIndex) const;
#endif // EBWIN | EBWIN32 | EBMAC
	float	GetSingle(ebWORD wIndex) const;
	ebHSUB	GetString(ebWORD wIndex) const;
	ebLPVOID GetStruct(ebWORD wIndex) const;
	ebVARIANT	GetVariant(ebWORD wIndex) const;
	
	void	SetBool(ebWORD wIndex, ebBOOL boolVal);
	void	SetCurrency(ebWORD wIndex, ebCURRENCY cy);
	void	SetDate(ebWORD wIndex, double date);
	void	SetDouble(ebWORD wIndex, double d);
	void	SetInt(ebWORD wIndex, short i);
	void	SetLong(ebWORD wIndex, long l);
	void	SetObject(ebWORD wIndex, ebDWORD dwObject);
#if defined(EBWIN) | defined(EBWIN32) | defined(EBMAC)
	void	SetOleObject(ebWORD wIndex, ebDWORD dwId);
#endif // EBWIN | EBWIN32 | EBMAC
	void	SetSingle(ebWORD wIndex, float f);
	void	SetString(ebWORD wIndex, ebHSUB hStr);
	void	SetVariant(ebWORD wIndex, ebLPVARIANT pVariant);
};

/////////////////////////////////////////////////////////////////////
// CebProto
class FAR CebProto
{
private:
	ebHPROTO	m_hTable;
	
public:
	CebProto();
	~CebProto();
	
	ebHPROTO GetHandle() const;

public:
	ebBOOL Create();
	ebBOOL Finish(ebLPVOID FAR* ppProto, ebLPDWORD pdwSize);

	static void FreeTable(ebLPSTR pProto);

public:
	void AddCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...);

	void AddConst(ebLPCSTR pName, ebWORD wType, ebLPSTR pExtType, ebLPCVOID pParams);
	void ebCAPI AddConst(ebLPCSTR pName, ebWORD wType, ebLPSTR pExtType, ...);
	
	void AddEntryCmd(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddEntryCmd(ebLPCSTR pName, ebWORD wMinArgs, ebWORD wMaxArgs, ...);

	void AddEntryFunction(ebLPCSTR pName, _ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddEntryFunction(ebLPCSTR pName, _ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...);
	
// #HK950508 ------------------------------------------------------------------
	void AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR lpExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...);
// #HK950508 ------------------------------------------------------------------
	
	void AddInline(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddInline(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...);
	
	void AddObject(ebLPCSTR pName, ebWORD wId, ebLPCSTR pBaseName);
	
	void AddObjCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddObjCmd(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wMinArgs, ebWORD wMaxArgs, ...);
	
	void AddObjFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR pExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ebLPCVOID pParams);
	void ebCAPI AddObjFunction(ebWORD wFlags, ebLPCSTR pName, ebWORD wId, ebWORD wType, ebLPCSTR pExtType, ebWORD wMinArgs, ebWORD wMaxArgs, ...);
	
	void AddObjProperty(ebWORD wFlags, ebLPCSTR pName, ebWORD wSetID, ebWORD wGetID, ebWORD wType, ebLPCSTR pExtType);

	void AddStruct(ebLPCSTR pName);
	
	void AddStructMember(ebLPCSTR pName, ebWORD wType, ebLPCSTR pExtType);
};


#ifdef EBWIN
/////////////////////////////////////////////////////////////////////
// CebRecorder
class FAR CebRecorder
{
private:
	HGLOBAL	m_hRecording;

	HWND	m_hWndParent;
	ebWORD	m_wOptions;
	ebWORD	m_wPasses;
	ebWORD	m_wCallerMsg;
	ebWORD	m_wKey1;
	ebWORD	m_wKey2;
	ebWORD	m_wKey3;
	ebLPCSTR	m_pDisabledList;
	ebCKPROC	m_pCKProc;

	enum { nOptions = RF_COLLAPSE | RF_HIGHLEVEL | RF_MOUSE | RF_KEYBOARD | RF_MOUSEMOVES };

public:
	// Constructor with default parameters
	CebRecorder(HWND hWndParent = NULL,
				ebWORD wOptions = nOptions,
				ebWORD wPasses = RF_PASSALL,
				ebWORD wCallerMsg = 0,
				ebWORD wKey1 = VK_MENU,
				ebWORD wKey2 = 0,
				ebWORD wKey3 = 0,
				ebLPCSTR pDisabledList = NULL,
				ebCKPROC pCKProc = NULL);
	
	virtual ~CebRecorder();

	virtual ebBOOL Start();
	virtual void Stop();
	virtual void Pause(ebBOOL bPause);

	void AddExternalText(ebLPCSTR pText);
	HGLOBAL GetRecording() const;
	HGLOBAL GetSafeHandle();

	HWND	GetParent() const;
	HWND	SetParent(HWND hWnd);
	ebWORD	GetOptions() const;
	ebWORD	SetOptions(ebWORD wOptions);
	ebWORD	GetPasses() const;
	ebWORD	SetPasses(ebWORD wPasses);
	ebWORD	GetCallerMsg() const;
	ebWORD	SetCallerMsg(ebWORD wCallerMsg);
	void	GetKeys(ebWORD FAR* rgKeys);
	void	SetKeys(ebWORD wKey1, ebWORD wKey2, ebWORD wKey3);
	ebLPSTR	GetDisabledList() const;
	ebLPSTR	SetDisabledList(ebLPCSTR pDisabledList);
	ebCKPROC	GetCKProc() const;
	ebCKPROC	SetCKProc(ebCKPROC pCKProc);

};
#endif // EBWIN

#if defined(EBWIN) || defined(EBWIN32)
/////////////////////////////////////////////////////////////////////
// CebDialogEditor
class FAR CebDialogEditor
{
private:
	ebDLGINFO FAR*	m_pDlgInfo;

public:
	CebDialogEditor();
	CebDialogEditor(ebLPDLGINFO pdi);
	virtual ~CebDialogEditor();

public:
	void SetDlgInfo(ebLPDLGINFO pdi);
	ebLPDLGINFO GetDlgInfo() const;
	int Start();

public:
	static int Start(ebLPDLGINFO pdi);
};
#endif // EBWIN || EBWIN32

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)
/////////////////////////////////////////////////////////////////////
// CebDebugDlgInfo
class FAR CebDebugDlgInfo {
friend class CebDebuggerDlg;
private:
	short	m_x;
	short	m_y;
	short	m_nWidth;
	short	m_nHeight;
	short	m_nWatchWindowHeight;
	HFONT	m_hFont;
	ebLPCSTR m_pszTitle;
	ebBOOL	m_bMatchCase;
	char	m_szFindText[DEBUGFINDTEXTSZ];
	char	m_szReplaceText[DEBUGFINDTEXTSZ];
	ebLPSTR	m_pWatches;
	ebLPSTR	m_pScript;
	ebHCODE m_hCode;

public:
	CebDebugDlgInfo::CebDebugDlgInfo(	ebHCODE hCode = NULL,
						short		x = (short)CW_USEDEFAULT,
						short		y = (short)CW_USEDEFAULT,
						short		nWidth = (short)CW_USEDEFAULT,
						short		nHeight = (short)CW_USEDEFAULT,
						short		nWatchWindowHeight = 0,
						ebBOOL		bMatchCase = FALSE,
						ebLPCSTR	pszFindText = NULL,
						ebLPCSTR	pszReplaceText = NULL);
	~CebDebugDlgInfo();

public:
	short GetX() const;
	short GetY() const;
	short GetWidth() const;
	short GetHeight() const;
	short GetWatchWindowHeight() const;
	ebBOOL GetMatchCase() const;
	ebLPSTR GetFindText() const;
	ebLPSTR GetReplaceText() const;
	ebLPSTR GetWatches() const;
	ebLPSTR DetachWatches();
	ebLPSTR GetScript() const;
	ebLPSTR DetachScript();
	ebHCODE GetCode() const;
	ebHCODE DetachCode();
};
#endif // EBWIN | EBWIN32 | EBOS2

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)
/////////////////////////////////////////////////////////////////////
// CebDebuggerDlg
class FAR CebDebuggerDlg
{
private:
	ebDEBUGGER	m_DebugInfo;
	CebDebugDlgInfo FAR* m_pDebugDlgInfo;
	int m_nScode;

public:
	CebDebuggerDlg(	CebDebugDlgInfo FAR*	pDebugDlgInfo,
			CebInstance FAR&	Instance,
			CebEntryInfo FAR&	EntryInfo,
			HWND			hWndParent,
			ebLPCSTR		pScript = NULL,
			const ebHCODE	hCode = NULL,
			ebLPCSTR		pWatches = NULL,
			ebLPCSTR		pszTitle = NULL,
			HFONT			hFont = NULL,
			ebDWORD			dwParam = 0);
	virtual ~CebDebuggerDlg();

public:
// Method to invoke the Debugger Dialog
	int    Invoke();

// Methods to get the Scode and categorize the Scode
	int    GetSCode() const;
	ebBOOL IsSave() const;
	ebBOOL IsCancel() const;
	ebBOOL IsError() const;

private:
	void SaveState();
	void SaveScript();
};
#endif // EBWIN | EBWIN32 | EBOS2

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)
/////////////////////////////////////////////////////////////////////
// CebDebugger
class FAR CebDebugger
{
private:
	HWND	m_hWndDebugger;
	HWND	m_hWndParent;
	int	m_X;
	int	m_Y;
	int	m_nWidth;
	int	m_nHeight;
	ebDWORD	m_dwStyle;
	ebWORD	m_wId;
#if defined(EBWIN) | defined(EBWIN32)
	HINSTANCE	m_hInstance;
#endif // EBWIN | EBWIN32

public:
	CebDebugger();
	CebDebugger(HWND	hWndParent,
		    int		x,
		    int		y,
		    int		width,
		    int		height,
		    ebDWORD	dwStyle,
		    ebWORD	wId,
#if defined(EBWIN) | defined(EBWIN32)
		    HINSTANCE	hInstance);
#else
		    ebUINT		uDummy = 0);
#endif
	virtual ~CebDebugger();

public:
	// Methods for specifying Debugger window properties
	HWND	GetParent() const;
	HWND	SetParent(HWND hWnd);
	void	GetRect(int FAR* px, int FAR* py, int FAR* pwidth, int FAR* pheight) const;
	void	SetRect(int x, int y, int width, int height);
	ebDWORD	GetStyle() const;
	ebDWORD	SetStyle(ebDWORD dwStyle);
	ebWORD	GetId() const;
	ebWORD	SetId(ebWORD wId);
#if defined(EBWIN) | defined(EBWIN32)
	void	SetInstance(HINSTANCE hInstance);
#endif // EBWIN | EBWIN32

// Set the Extrabuffer for Thread's SetLong(), GetLong(), SetWord()...	
	void SetThreadExtra(ebWORD iSz);

// Method to retrieve the Debugger control window
	HWND	GetWindow() const;
// Method to retrieve the Debugger control window, set ControlWindow NULL
	HWND	DetachWindow();
// Method to destroy the Debugger control window
	void	DestroyWindow() const;

public:
	// Debugger control window create method
	virtual ebBOOL	Create();
	// Method to check if the debugger control should be closed
	virtual ebBOOL	QueryClose() const;

//protected:
	// Method corresponding to commands under Edit menu
	virtual void EditUndo();
	virtual void EditClear();
	virtual void EditCopy();
	virtual void EditCut();
	virtual void EditPaste();

public:
	// Breakpoint methods
	void	ClearAllBreakpoints();
	ebBOOL	ToggleBreakpoint(ebWORD wLineNo);

	// Watch variable methods
	ebBOOL	AddWatch(ebLPCSTR pExpression);
	ebBOOL	DeleteWatch(ebLPCSTR pExpression);
	ebBOOL	CanDeleteWatch();
	// Watch variable enumeration methods
	ebBOOL GetFirstWatch(ebLPSTR pBuffer, ebINT iLen);
	ebBOOL	GetNextWatch(ebLPSTR pBuffer, ebINT iLen);

	// Debugger's script (text) methods
	ebWORD	GetTextLength() const;
	ebWORD	GetText(ebLPSTR pText, ebWORD wBufSize);
	ebBOOL  SetText(ebLPCSTR pText);
	ebLONG	FindText(ebLPCSTR pText, int nDirection = 1, ebBOOL bMatchCase = 0, ebBOOL bMatchWholeWord = 0);
	ebBOOL	GetModified() const;
	void	SetModified(ebBOOL bModified);
	ebBOOL	CanUndo() const;
	ebBOOL	GetCaretWord(ebLPSTR pBuffer, ebWORD wBufSize);

	// Script (text) editing and selecting methods
	ebBOOL	SetCaretPos(int x, int y, ebBOOL bExtend = 0 /* FALSE */);
	void	GetSelectionOffsets(int FAR* pnStart, int FAR* pnEnd);
	int		GetSelection(ebLPSTR pBuffer, ebWORD wBufSize);
	ebBOOL	HasSelection() const;
	ebBOOL	ReplaceSelection(ebLPCSTR pText, ebBOOL bSelect = 0 /* FALSE */);
	ebWORD	GetNumLines(void);

	// Debugger text color display methods
	ebBOOL	EnableTextColors(ebBOOL bEnabled = 1 /* TRUE */);
	void	GetTextColors(ebLPTEXTCOLORS pColors);
	void	SetTextColors(ebLPTEXTCOLORS pColors);

	// Debugger text font methods
	ebHFONT	GetFont() const;
	void	SetFont(ebHFONT hFont);

	// Debugger Watch window methods
	ebWORD	GetWatchWindowHeight() const;
	ebWORD	SetWatchWindowHeight(ebWORD wHeight);

	// Debugging methods
	void	StepOver();
	void	TraceInto();
	ebWORD	GetCurrentLine() const;
	ebDWORD	GetCursorPos() const;
	ebBOOL	SetNextLine(ebWORD wLineNo);
	void	InvokeGotoLineDialogBox();
	void	InvokeModifyVarDialogBox(ebBOOL bUseSelectedItem = 1 /* TRUE */);
	void	InvokeCallsDialogBox();

	// User dialog methods
#if defined(EBWIN) || defined(EBWIN32)
	ebBOOL	IsDialogSelected() const;
	void	EditDialog();
	ebBOOL	InsertDialog();
#endif // EBWIN || EBWIN32

	// Execution and execution environment methods
	ebBOOL	EnableCtrlBreak(ebBOOL bEnabled = 1 /* TRUE */);
	void	StartScript();
	void	PauseScript();
	void	EndScript();
	CebThread FAR*	GetThread(ebBOOL isWantOwnership) const;
	CebScript FAR*	GetScript(ebBOOL isWantOwnership) const;
	void	SetInstance(CebInstance FAR* pInstance);
	void	SetNumericDisplayBase(ebWORD wBase);
	void	SetEntryPoint(ebLPENTRYINFO pEntryInfo);

	ebDWORD	GetScope();

	ebHCODE	GetCode(ebBOOL bWantOwnership = 1 /* TRUE */);
	void	SetCode(ebHCODE hCode);

	ebBOOL	Compile(ebBOOL bDisplayError = 1 /* TRUE */);
	ebBOOL	ConfineDebugging(ebBOOL bConfine);

	int	GetState() const;

#if defined(EBWIN) | defined(EBWIN32)
	void	SetHelpMode(ebBOOL bIsHelpMode, HCURSOR hCursor);
	ebBOOL SetAutoCase(ebBOOL fisAutoCase);
	ebBOOL SetAutoIndent(ebBOOL fisAutoIndent);
#endif // EBWIN | EBWIN32

	void SetNotificationData(long lData);
	void SetNotificationProc(ebNOTIFICATIONPROC lpfnNotifyProc);
	ebKEYBOARDFILTERPROC SetKeyboardFilter(ebKEYBOARDFILTERPROC pfnFilter);
};
#endif // EBWIN | EBWIN32 | EBOS2

class FAR CebCompiler
{
public:
	CebCompiler();
	virtual ~CebCompiler();

public:
	static ebWORD Compile(ebLPCOMPILESTRUCT pCompileStruct);
};

#ifdef EBOS2
#  undef ebCAPI
#  define ebCAPI EXPENTRY
#endif

///////////////////////////////////////////////////////////
// The inline version works with MSVC for Windows and Win32
// Borland C++, and Watcom.
// The .cpp version in the file ebc.cpp will work for other
// compilers.
// To activate the inline version, define EBC_INLINE.

#ifdef _EBC_ENABLE_INLINES
#  define _EBC_INLINE inline
#  include <ebc.inl>
#else
#  define _EBC_INLINE
#endif

#endif // __EBC_H_
