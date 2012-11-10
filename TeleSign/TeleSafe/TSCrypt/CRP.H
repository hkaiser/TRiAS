// CRP.H

#ifndef CRYPTROUTINES_INCLUDED
#define CRYPTROUTINES_INCLUDED

#include <wincrypt.h>

#define BUF_SIZE 1000
#define PATH_SIZE 600
#define HEADER_SIZE 256
#define SHA_SIZE 20
#define RANDOM_NAME_LENGTH 8
//#define	EXPORTER
#define	TSC_ENCRYPT_DECRYPT 1
#define	TSC_SIGN			2
#define	TSC_VERIFY			3
#define MAXBLOBLEN		200

#define DIRECTORY_STRING_SIZE MAX_PATH  // Size of max allowable direcory path

WINAPI 		EnterPass					(HWND, UINT, UINT, LPARAM);
BOOL 		GetPass						(HWND);
WINAPI		CryptDlgProc			(HWND, UINT, UINT, LPARAM);
WINAPI		EncryptDlgProc		(HWND, UINT, UINT, LPARAM);
WINAPI		HashDlgProc			(HWND, UINT, UINT, LPARAM);
BOOL 		Logon						(HWND);
BOOL 		Logoff						(HWND);
BOOL 		EncryptFile				(HWND, LPTSTR, TCHAR szCryptedFileName );
BOOL 		DecryptFile					(HWND, LPTSTR);
BOOL 		GetEncryptPublicKey			(HWND, HCRYPTKEY *); 
BOOL 		GetSignaturePublicKey		(HWND, HCRYPTKEY *); 
HCRYPTKEY 	GetfnKey					(HWND);
BOOL 		SignFile					(HWND, LPTSTR, TCHAR szSigFileName[PATH_SIZE]);
BOOL 		VerifyFile					(HWND, LPTSTR, LPTSTR szSigFileName);
BOOL 		MakeHashDirectory			(VOID);
BOOL 		SHAtoRadix64				(LPBYTE, LPTSTR);
VOID 		Exit1						(HWND, LPTSTR, HANDLE, HANDLE);
VOID 		Exit2						(HWND, LPTSTR, HWND, HANDLE, HANDLE);
BOOL 		c2r64						(INT, LPTSTR);
//BOOL 		EncryptDir					(HWND, LPTSTR, LPCINFO lpCInfo);
//BOOL 		DecryptDir					(HWND, LPTSTR, LPCINFO lpCInfo);
BOOL		GenRandomName				(LPTSTR);
BOOL		GenRandomName2				(LPTSTR);
//BOOL		HasSignature				(LPTSTR, TABLE, BOOL *);
BOOL 		GetDecryptedFileName		(HWND, LPTSTR, LPTSTR, HANDLE *);
BOOL 		GetDecryptedDirName			(HWND, LPTSTR, LPTSTR, BOOL, HANDLE *);
BOOL 		HideSignatures				(VOID);
BOOL 		ShowSignatures				(VOID);
BOOL 		GetSigFileName				(LPTSTR, LPTSTR);
BOOL 		DeleteHashDirectory			(VOID);
BOOL 		GetSigDir					(LPTSTR);


#endif
