// TSCryptSvr.cpp : Implementation von CTSCryptSvr
#include "stdafx.h"


#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) {if(x){delete (x); (x)=NULL;}}
#if defined(MSCC8) || _MSC_VER >= 800
#define DELETE_VEC(x)	{if(x){delete [] (x); (x)=NULL;}}
#else
#define DELETE_VEC(x,s)	{if(x){delete [(s)] (x); (x)=NULL;}}
#endif
#endif

#include "array.h"
#include "TSCrypt.h"
#include "TSCryptSvr.h"

/////////////////////////////////////////////////////////////////////////////
// CTSCryptSvr

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cderr.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <wincrypt.h>

#define CSO_IMPORT __declspec( dllimport ) 
#include "CryptoSealObjects.h"

//===========================================================================
#include "CRP.H"
#include "TABLE.H"


HCRYPTPROV					hMe;
ALG_ID						AlgidEncrypt;
ALG_ID						AlgidSign;
TCHAR						sPass[BUF_SIZE];
TCHAR						szPassName[BUF_SIZE];

/***************************************************************\
* ErrorMsg()
*
*   Displays a Message Box with a given error message.
*
\***************************************************************/

void ErrorMsg(LPTSTR szMsg)
{
    TCHAR szHold[DIRECTORY_STRING_SIZE + 1];

    lstrcpy( szHold, szMsg );
    lstrcat( szHold, TEXT("\n") );

   	OutputDebugString(szHold);
}

/************************************************************************\
* c2r64()
*
* input:
* i - integer value to be converted to a radix64 character
* c - address where character is to be stored
*
* purpose:
* converts an integer between 0 and 63 to a character.
* 0-25 -> A-Z
* 26 - 51 -> a-z
* 52 - 61 -> 0-9
* 62 -> +
* 63 -> _
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL c2r64(INT i, LPTSTR c) {
	if (!c) {
		ErrorMsg(TEXT("c2r64: c is NULL."));
		return FALSE;
	}
	
	if (0 <= i && i <= 25)
		*c = TEXT('A') + i;
	else if (26 <= i && i <= 51)
		*c = TEXT('a') + i - 26;
	else if (52 <= i && i <= 61)
		*c = TEXT('0') + i - 52;
	else if (i == 62)
		*c = TEXT('+');
	else if (i == 63)
		*c = TEXT('_');
	else {
		ErrorMsg(TEXT("c2r64: c is not between 0 and 63."));
		return FALSE;
	}
	return TRUE;
}

/************************************************************************\
* SHAtoRadix64 takes as input a SHA_SIZE-byte hash of the full 
* pathname of a file. It produces a 27-byte "Radix64" 
* representation of the hash, where each byte in the
* "Radix64" representation is between 0 and 2^6.
* It pretends that the SHZ_SIZE + 1st input byte is NULL.
\************************************************************************/

BOOL SHAtoRadix64(LPBYTE pbPathHash, LPTSTR szFileName) {
	INT i, j;
	TCHAR c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	
	if (!pbPathHash) {
		ErrorMsg(TEXT("SHAtoRadix64: pbPathHash is NULL."));
		return FALSE;
	}

	if (!szFileName) {
		ErrorMsg(TEXT("SHAtoRadix64: szFileName is NULL."));
		return FALSE;
	}
	
	for (i = 0, j = 0; i < 18 && j < 24; i += 3, j += 4) {
		c1 = c1 | (((pbPathHash[i + 0] >> 7) & 1) << 5);
		c1 = c1 | (((pbPathHash[i + 0] >> 6) & 1) << 4);
		c1 = c1 | (((pbPathHash[i + 0] >> 5) & 1) << 3);
		c1 = c1 | (((pbPathHash[i + 0] >> 4) & 1) << 2);
		c1 = c1 | (((pbPathHash[i + 0] >> 3) & 1) << 1);
		c1 = c1 | (((pbPathHash[i + 0] >> 2) & 1) << 0);
	
		c2 = c2 | (((pbPathHash[i + 0] >> 1) & 1) << 5);
		c2 = c2 | (((pbPathHash[i + 0] >> 0) & 1) << 4);
		c2 = c2 | (((pbPathHash[i + 1] >> 7) & 1) << 3);
		c2 = c2 | (((pbPathHash[i + 1] >> 6) & 1) << 2);
		c2 = c2 | (((pbPathHash[i + 1] >> 5) & 1) << 1);
		c2 = c2 | (((pbPathHash[i + 1] >> 4) & 1) << 0);

		c3 = c3 | (((pbPathHash[i + 1] >> 3) & 1) << 5);
		c3 = c3 | (((pbPathHash[i + 1] >> 2) & 1) << 4);
		c3 = c3 | (((pbPathHash[i + 1] >> 1) & 1) << 3);
		c3 = c3 | (((pbPathHash[i + 1] >> 0) & 1) << 2);
		c3 = c3 | (((pbPathHash[i + 2] >> 7) & 1) << 1);
		c3 = c3 | (((pbPathHash[i + 2] >> 6) & 1) << 0);

		c4 = c4 | (((pbPathHash[i + 2] >> 5) & 1) << 5);
		c4 = c4 | (((pbPathHash[i + 2] >> 4) & 1) << 4);
		c4 = c4 | (((pbPathHash[i + 2] >> 3) & 1) << 3);
		c4 = c4 | (((pbPathHash[i + 2] >> 2) & 1) << 2);
		c4 = c4 | (((pbPathHash[i + 2] >> 1) & 1) << 1);
		c4 = c4 | (((pbPathHash[i + 2] >> 0) & 1) << 0);

		c2r64(c1, &(szFileName[j + 0]));
		c2r64(c2, &(szFileName[j + 1]));
		c2r64(c3, &(szFileName[j + 2]));
		c2r64(c4, &(szFileName[j + 3]));

		c1 = 0; c2 = 0; c3 = 0; c4 = 0;
	}
	
	c1 = c1 | (((pbPathHash[18] >> 7) & 1) << 5);
	c1 = c1 | (((pbPathHash[18] >> 6) & 1) << 4);
	c1 = c1 | (((pbPathHash[18] >> 5) & 1) << 3);
	c1 = c1 | (((pbPathHash[18] >> 4) & 1) << 2);
	c1 = c1 | (((pbPathHash[18] >> 3) & 1) << 1);
	c1 = c1 | (((pbPathHash[18] >> 2) & 1) << 0);
		
	c2 = c2 | (((pbPathHash[18] >> 1) & 1) << 5);
	c2 = c2 | (((pbPathHash[18] >> 0) & 1) << 4);
	c2 = c2 | (((pbPathHash[19] >> 7) & 1) << 3);
	c2 = c2 | (((pbPathHash[19] >> 6) & 1) << 2);
	c2 = c2 | (((pbPathHash[19] >> 5) & 1) << 1);
	c2 = c2 | (((pbPathHash[19] >> 4) & 1) << 0);

	c3 = c3 | (((pbPathHash[19] >> 3) & 1) << 5);
	c3 = c3 | (((pbPathHash[19] >> 2) & 1) << 4);
	c3 = c3 | (((pbPathHash[19] >> 1) & 1) << 3);
	c3 = c3 | (((pbPathHash[19] >> 0) & 1) << 2);
	c3 = c3 | (((0              >> 7) & 1) << 1);
	c3 = c3 | (((0              >> 6) & 1) << 0);

	c2r64(c1, &(szFileName[24]));
	c2r64(c2, &(szFileName[25]));
	c2r64(c3, &(szFileName[26]));

	szFileName[27] = TEXT('\0');

	return TRUE;
};

/************************************************************************\
* Logon()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Creates a dialog box which says "Performing context acquisition."
* Calls CryptAcquireContext.
* Destroys the dialog box
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL Logon(HWND hWnd) {
	HWND			hwndDlg;
	TCHAR			pszName[64];

	pszName[0] = TEXT('\0');
	hwndDlg = CreateDialog(_Module.GetModuleInstance(), TEXT("ACQUIRE_CONTEXT"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		ErrorMsg(TEXT("Logon: CreateDialog failed."));
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptAcquireContext(&hMe, pszName, MS_DEF_PROV, PROV_RSA_FULL, 0))) {
		if (RCRYPT_FAILED(CryptAcquireContext(&hMe, 
						  pszName, 
						  TEXT(MS_DEF_PROV), 
						  PROV_RSA_FULL, 
						  CRYPT_NEWKEYSET))) {
			EndDialog(hwndDlg, FALSE);
			MessageBox(hWnd, TEXT("Logon: CryptAcquireContext failed."), NULL, MB_OK);
			return FALSE;
		}
	}

	EndDialog(hwndDlg, FALSE);
	return TRUE;

return FALSE;
}

/************************************************************************\
* Logoff()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Calls CryptReleaseContext.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL Logoff(HWND hWnd) 
{
	if (hMe) {
		if (RCRYPT_FAILED(CryptReleaseContext(hMe, 0))) {
        	ErrorMsg(TEXT("Logoff: CryptReleaseContext failed."));
        	return FALSE;
    	}
	}
	else {
		ErrorMsg(TEXT("Logoff: hMe is NULL."));
		return FALSE;
	}

	return TRUE;
}

/************************************************************************\
* GetEncryptPublicKey()
*
* input:
* hWnd - HWND specified by caller
* phEncryptPubKey - address to store key
*
* purpose: calls CryptGetUserKey to obtain the AT_KEYEXCHANGE public
* key.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetEncryptPublicKey(HWND hWnd, HCRYPTKEY *phEncryptPubKey) {
	if (!phEncryptPubKey) {
		ErrorMsg(TEXT("GetEncryptPubKey: phEncryptPubKey is NULL."));
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptGetUserKey(hMe, AT_KEYEXCHANGE, phEncryptPubKey))) {
		if (RCRYPT_FAILED(CryptGenKey(hMe, AT_KEYEXCHANGE, 0, phEncryptPubKey))) {
			ErrorMsg(TEXT("GetEncryptPublicKey: CryptGenKey failed."));
			return TRUE;
		}
	}	
	
	return TRUE;
}

/************************************************************************\
* GetfnKey()
*
* purpose:
* Retrieves fnKey from the registry.
* fnKey is used to encrypt and decrypt filenames.
* If fnKey does not exist in the registry, GetfnKey creates it.
*
* returns
* a valid key if successful
* 0 if unsuccessful.
\************************************************************************/

HCRYPTKEY GetfnKey(HWND hWnd) {
	BYTE 		pbFileKeyBlob[BUF_SIZE];
	DWORD 		dwFileBlobLen = BUF_SIZE;
	LONG		lRv;
	HKEY		hKey;
	DWORD		dwType;
	DWORD		dwSize;
	DWORD		dwDisposition;
	HCRYPTKEY	phEncryptPubKey;
	HCRYPTKEY	hfnKey;

	if (!GetEncryptPublicKey(hWnd, &phEncryptPubKey)) {
		ErrorMsg(TEXT("GetfnKey: GetEncryptPublicKey failed."));
		return (HCRYPTKEY)0;
	}

#ifdef WIN95

	lRv = RegOpenKeyEx(HKEY_CURRENT_USER, 
			 		   TEXT("SOFTWARE\\Microsoft\\Cryptfiler.ini"), 
					   0, 
					   KEY_ALL_ACCESS,
					   &hKey);

#else

	lRv = RegOpenKeyEx(HKEY_CURRENT_USER, 
			 		   TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\IniFileMapping\\Cryptfiler.ini"), 
					   0, 
					   KEY_ALL_ACCESS,
					   &hKey);
#endif

	if (lRv != ERROR_SUCCESS) {

		// not in registry; we must create.

#ifdef WIN95

		lRv = RegCreateKeyEx(HKEY_CURRENT_USER, 
				 			 TEXT("SOFTWARE\\Microsoft\\Cryptfiler.ini"), 
							 0, 
							 NULL, 
							 REG_OPTION_NON_VOLATILE,
							 KEY_ALL_ACCESS,
							 NULL,
							 &hKey,
							 &dwDisposition);
#else
		lRv = RegCreateKeyEx(HKEY_CURRENT_USER, 
				 			 TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\IniFileMapping\\Cryptfiler.ini"), 
							 0, 
							 NULL, 
							 REG_OPTION_NON_VOLATILE,
							 KEY_ALL_ACCESS,
							 NULL,
							 &hKey,
							 &dwDisposition);
#endif
	
		if (lRv != ERROR_SUCCESS) {
			ErrorMsg(TEXT("GetfnKey: RegCreateKeyEx failed."));
			return (HCRYPTKEY)0;
		}

		if (RCRYPT_FAILED(CryptGenKey(hMe, CALG_RC4, CRYPT_EXPORTABLE, &hfnKey))) {
			ErrorMsg(TEXT("GetfnKey: CryptGenKey failed."));
			return (HCRYPTKEY)0;
		} 
		
		//Export the key so that it can be stored in the registry.
		
		if (RCRYPT_FAILED(CryptExportKey(hfnKey, 
						  phEncryptPubKey, 
						  SIMPLEBLOB, 
						  0, 
						  pbFileKeyBlob, 
						  &dwFileBlobLen))) {
			ErrorMsg(TEXT("GetfnKey: CryptExportKey failed."));
			return (HCRYPTKEY)0;
		}

		// Store the key blob in the registry.
		
		if (RegSetValueEx(hKey,
						  TEXT("fnKey"),
						  0,
						  REG_BINARY,
						  pbFileKeyBlob,
						  dwFileBlobLen * sizeof(*pbFileKeyBlob)) != ERROR_SUCCESS) {
					
			ErrorMsg(TEXT("GetfnKey: RegSetValueEx failed."));
			return (HCRYPTKEY)0;
		}
	}	
	else {
		// in registry. We must extract.
		
		dwType = 0;
		dwFileBlobLen = 0;
		dwSize = BUF_SIZE;

		if (RegQueryValueEx(hKey, 
							TEXT("fnKey"),
							NULL, 
							&dwType, 
							pbFileKeyBlob, 
							&dwSize) != ERROR_SUCCESS)
		{
			MessageBox(hWnd, TEXT("GetfnKey: RegQueryValueEx failed querrying pbFileKeyBlob."), NULL, MB_OK);
			return (HCRYPTKEY)0;
		};

		// Read the key blob from the disk into a Buf.
		
		if (!dwSize || (dwSize > BUF_SIZE)) {
			ErrorMsg(TEXT("GetfnKey: dwSize is not in acceptable range."));
			return FALSE;
		}
		
		// Import the key whose blob is contained in the Buf pbDecryptBlob

		dwFileBlobLen = dwSize;

		if (RCRYPT_FAILED(CryptImportKey(hMe, 
						  pbFileKeyBlob, 
						  dwFileBlobLen, 
						  0, 
						  0,
						  &hfnKey))) {

			MessageBox(hWnd, TEXT("GetfnKey: CryptImportKey failed"), NULL, MB_OK);
			return (HCRYPTKEY)0;
		}
	}

	return hfnKey;
}

/************************************************************************\
* GetSigDir()
*
* in parameters
* szSigDir - buffer to hold result
*
* purpose: 
* stores in buffer szSigDir the name of the directory containing
* the signatures
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSigDir(LPTSTR szSigDir)
{
	TCHAR szSystemDirectory[PATH_SIZE];

	if (!szSigDir) {
		ErrorMsg(TEXT("GetSigDir: szSigDir is NULL."));
		return FALSE;
	}
		
	// [system directory drive]:\sig -> szSigDir
	
	GetSystemDirectory(szSystemDirectory, PATH_SIZE * sizeof(*szSystemDirectory));
	szSigDir[0] = szSystemDirectory[0];
	szSigDir[1] = TEXT('\0');
	lstrcat(szSigDir, TEXT(":\\sig"));
	
	return TRUE;
}

/*************************************************************************************\
* SeparatePathName()
*
* First parameter (in parameter): szFileName - full path name to be separated
*
* Second parameter (out parameter): szDir - buffer to hold full pathname of directory
*
* Third parameter (out parameter): szFile - buffer to hold filename (not full pathname)
*
* Example: C:\directory\[foo] -> C:\directory + [foo]
\*************************************************************************************/

BOOL SeparatePathName(LPTSTR szFileName, LPTSTR szDir, LPTSTR szFile) {
	INT		i, j, nLen, nFileOffset;

	if (!szFileName) {
		ErrorMsg(TEXT("SeparatePathName: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szDir) {
		ErrorMsg(TEXT("SeparatePathName: szDir is NULL."));
		return FALSE;
	}
	
	if (!szFile) {
		ErrorMsg(TEXT("SeparatePathName: szFile is NULL."));
		return FALSE;
	}
	
	lstrcpy(szDir, TEXT("\0"));
	lstrcpy(szFile, TEXT("\0"));
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 1] == TEXT('\\'))
		for (i = nLen - 1; szFileName[i] != TEXT('\\') && i; i--);
	else
		for (i = nLen; szFileName[i] != TEXT('\\') && i; i--);
	
	nFileOffset = i + 1;
    
    for (i = 0; i < nFileOffset - 1; i++)
    	szDir[i] = szFileName[i];
    szDir[i] = TEXT('\0');
    
    for (j = 0, i++; i < lstrlen(szFileName); i++, j++)
        szFile[j] = szFileName[i];
    szFile[j] = TEXT('\0');  
    
	return TRUE;
}

/*************************************************************************************\
* SeparatePathName2()
*
* First parameter (in parameter): szFileName - full path name to be separated
*
* Second parameter (out parameter): szDir - buffer to hold full pathname of directory
*
* Third parameter (out parameter): szFile - buffer to hold filename (not full pathname)
*
* brackets are stripped from the filename before the filename is inserted into szFile.
*
* C:\directory\[foo] -> C:\directory + foo
\*************************************************************************************/

BOOL SeparatePathName2(LPTSTR szFileName, LPTSTR szDir, LPTSTR szFile) {
	INT		i, j, nLen, nFileOffset;

	if (!szFileName) {
		ErrorMsg(TEXT("SeparatePathName2: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szDir) {
		ErrorMsg(TEXT("SeparatePathName2: szDir is NULL."));
		return FALSE;
	}
	
	if (!szFile) {
		ErrorMsg(TEXT("SeparatePathName2: szFile is NULL."));
		return FALSE;
	}
	
	lstrcpy(szDir, TEXT("\0"));
	lstrcpy(szFile, TEXT("\0"));
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 1] == TEXT('\\'))
		for (i = nLen - 1; szFileName[i] != TEXT('\\') && i; i--);
	else
		for (i = nLen; szFileName[i] != TEXT('\\') && i; i--);
		
	nFileOffset = i + 1;
    
    for (i = 0; i < nFileOffset - 1; i++)
    	szDir[i] = szFileName[i];
    szDir[i] = TEXT('\0');
    
    for (j = 0, i++; i < lstrlen(szFileName); ) {
    	if (szFileName[i] == TEXT('[') || szFileName[i] == TEXT(']'))
			i++;
    	else {
    		szFile[j] = szFileName[i];
    		i++;
			j++;
		}
	}

    szFile[j] = TEXT('\0');  
    
	return TRUE;
}

/*************************************************************************************\
* IsEncrypted()
* 
* input:
*
* szFileName - In parameter: buffer containing filename
*
* If szFileName has a .CRP extension, IsEncrypted() returns TRUE, FALSE otherwise
* or if failure.
\*************************************************************************************/

BOOL IsEncrypted(LPTSTR szFileName) {
	INT nLen;

	if (!szFileName) {
		ErrorMsg(TEXT("IsEncrypted: szFileName is NULL."));
		return FALSE;
	}
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 4] == TEXT('.') &&
  		szFileName[nLen - 3] == TEXT('C') &&
		szFileName[nLen - 2] == TEXT('R') &&
		szFileName[nLen - 1] == TEXT('P'))
		return TRUE;

	return FALSE;
}

/************************************************************************\
* GenRandomName()
*
* out parameters
* szRandomName - buffer to receive random filename
*
* purpose:
* Uses the random number generator to generate a random filename with
* a .CRP extension.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GenRandomName(LPTSTR szRandomName) {
	INT i;

	if (!szRandomName) {
		ErrorMsg(TEXT("GenRandomName: szRandomName is NULL."));
		return FALSE;
	}
	
	for (i = 0; i < RANDOM_NAME_LENGTH; i++)
		szRandomName[i] = rand() % 26 + TEXT('a');
	szRandomName[i] = TEXT('\0');

	lstrcat(szRandomName, TEXT(".CRP\0"));

	return TRUE;
}

/************************************************************************\
* GenRandomName2()
*
* out parameters
* szRandomName - buffer to receive random filename
*
* purpose:
* Uses the random number generator to generate a random filename without
* a .CRP extension.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GenRandomName2(LPTSTR szRandomName) {
	INT i;

	if (!szRandomName) {
		ErrorMsg(TEXT("GenRandomName: szRandomName is NULL."));
		return FALSE;
	}
	
	for (i = 0; i < RANDOM_NAME_LENGTH; i++)
		szRandomName[i] = rand() % 26 + TEXT('a');
	szRandomName[i] = TEXT('\0');

	return TRUE;
}

/************************************************************************\
* GetSigFileName()
*
* input
* in parameters:
* szFileName - full path of filename
* out parameters:
* szOutName - buffer containing name of signature file.
*
* purpose:
* obtains the name of the signature file that corresponds to szFileName.
* by hashing it and converting it to ascii.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSigFileName(LPTSTR szFileName, LPTSTR szOutName) {
	HCRYPTHASH hHash;
	BYTE pbHash[BUF_SIZE];
	DWORD dwHashLen;
	TCHAR szFileBuf[PATH_SIZE];
	TCHAR szSigDir[PATH_SIZE];

	if (!szFileName) {	
		ErrorMsg(TEXT("GetSigFileName: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szOutName) {
		ErrorMsg(TEXT("GetSigFileName: szOutName is NULL."));
		return FALSE;
	}
	
 	GetSigDir(szSigDir);
	
	// Hash szFileName.
	
	if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_SHA, 0, 0, &hHash))) {
		ErrorMsg(TEXT("GetSigFileName: CryptCreateHash failed."));
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)szFileName, lstrlen(szFileName) * sizeof(*szFileName), 0))) {
		ErrorMsg(TEXT("GetSigFileName: CryptHashData failed."));
		return FALSE;
	}

	dwHashLen = SHA_SIZE;
	
	if (RCRYPT_FAILED(CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))) {
		ErrorMsg(TEXT("GetSigFileName: CryptFinishHash failed."));
		return FALSE;
	}
	
	// Convert the hash to ascii
	
	if (!SHAtoRadix64(pbHash, szFileBuf)) {
		ErrorMsg(TEXT("DrvWndProc: FILLFILE: SHAtoRadix64 failed."));
		return 0;
	}
							
	lstrcpy(szOutName, szSigDir);
	lstrcat(szOutName, TEXT("\\"));
	lstrcat(szOutName, szFileBuf);

	CryptDestroyHash(hHash);
	return TRUE;
}

/************************************************************************\
* HasSignature()
*
* in parameters
* szFileName - full path of filename in question
* sigtable - pointer to a string table with displayed fields containing
* the filenames of all the files in the \sig directory, which is located
* on the same drive as the system directory.
*
* out parameters
* bHasSignature - flag specifying whether szFileName has a signature
*
* purpose:
* determines whether \sig\szFileName has a signature by calling
* GetSigFileName.
*
* returns
* TRUE if such a file exists
* FALSE otherwise or if unsuccessful
\************************************************************************/

BOOL HasSignature(LPTSTR szFileName, TABLE sigtable, BOOL *bHasSignature) {
	TCHAR szFileName2[PATH_SIZE];
	
	if (!szFileName) {	
		ErrorMsg(TEXT("HasSignature: szFileName is NULL."));
		return FALSE;
	}
	
	if (!bHasSignature) {
		ErrorMsg(TEXT("HasSignature: bHasSignature is NULL."));
		return FALSE;
	}
	
	if (!GetSigFileName(szFileName, szFileName2)) {
		ErrorMsg(TEXT("HasSignature: GetSigFileName failed."));
		return FALSE;
	}

	// Does this file exist?
/*//FJE	
	if (TableFind(sigtable, szFileName2))
		*bHasSignature = TRUE;
	else
		*bHasSignature = FALSE;
*/

	return TRUE;
}
				
/************************************************************************\
* GetDecryptedFileName()
*
* in parameters
* hWnd - HWND specified by caller
* szFileName - full path of file
* 
* out parameters
* szDecryptedFileName - buffer to hold full decrypted path
* hFileRead - pointer to file handle
*
* purpose:
* reads HEADER_SIZE bytes from szFileName, decrypts it with fnKey, and
* stores the result on szDecryptedFileName, the decrypted file name.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetDecryptedFileName(HWND hWnd, 
						  LPTSTR szFileName, 
						  LPTSTR szDecryptedFileName, 
						  HANDLE *hFileRead) {
	DWORD dwDataLen = HEADER_SIZE * sizeof(TCHAR);
	DWORD dwNumBytesRead;
	TCHAR szDir[PATH_SIZE];
	HCRYPTKEY hfnKey;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	if (!szDecryptedFileName) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: szDecryptedFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}

	// Open encrypted file.
	
	*hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   GetFileAttributes(szFileName),
						   0);

	if (*hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}
	
	// Read the encrypted filename from the disk.
						
	if (!ReadFile(*hFileRead, 
			 	  szDecryptedFileName, 
			 	  HEADER_SIZE * sizeof(*szDecryptedFileName), 
			 	  &dwNumBytesRead, 
			 	  0))
		return FALSE;
						
	if (dwNumBytesRead != HEADER_SIZE * sizeof(*szDecryptedFileName)) {
		SeparatePathName2(szFileName, szDir, szDecryptedFileName);
		return FALSE;
	}

	// Decrypt the filename.
						
	CryptDecrypt(hfnKey, 0, TRUE, 0, (LPBYTE)szDecryptedFileName, &dwDataLen);

	return TRUE;
}

/************************************************************************\
* EnterPass()
*
* Dialog procedure for the "PASSWORD" dialog box.
*
* Stores the password entered by the user into 
* the global buffer sPass
\************************************************************************/

WINAPI EnterPass(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam)  {
	TCHAR szMessage[BUF_SIZE];
	
	switch(wMsgID) {
		case WM_INITDIALOG:
			lstrcpy(szMessage, TEXT("Enter password: "));
			lstrcat(szMessage, szPassName);
			SetDlgItemText(hDlg, IDC_PASSTEXT, szMessage);
			SetDlgItemText(hDlg, IDC_EDIT1, TEXT("\0"));
			SetDlgItemText(hDlg, IDC_EDIT2, TEXT("\0"));

			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				TCHAR szVerify[BUF_SIZE];
				
				case IDOK:
					if (!GetDlgItemText(hDlg, IDC_EDIT1, sPass, BUF_SIZE)) {
	                	if (MessageBox(hDlg, TEXT("No password entered."), NULL, MB_OK) == IDOK) {
							EndDialog(hDlg, FALSE);
							return FALSE;
						}
					}
	                				
					SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
					
					if (!GetDlgItemText(hDlg, IDC_EDIT2, szVerify, BUF_SIZE)) {
						MessageBox(hDlg, TEXT("No password entered."), NULL, MB_OK);
						EndDialog(hDlg, FALSE);
						return FALSE;
					}
					
					if (lstrcmp(sPass, szVerify)) {
						MessageBox(hDlg, TEXT("Could not verify password."), NULL, MB_OK);
						EndDialog(hDlg, FALSE);
						return FALSE;
					}

					EndDialog(hDlg, TRUE);					
					
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, -1);
					return -1;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}	

/************************************************************************\
* CryptDlgProc()
*
* Dialog procedure for all dialog boxes of the
* application besides "PASSWORD", "ENCRYPTION_ALGORITHM,"
* and "HASH_ALGORITHM."
\************************************************************************/

WINAPI CryptDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDOK:
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* EncryptDlgProc()
*
* Dialog procedure for "ENCRYPTION_ALGORITHM" dialog box.
\************************************************************************/

WINAPI EncryptDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			if (AlgidEncrypt == CALG_RC4)
				CheckRadioButton(hDlg, IDC_RC2, IDC_RC4, IDC_RC4);
			else
				CheckRadioButton(hDlg, IDC_RC2, IDC_RC4, IDC_RC2);
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDC_RC2:
					AlgidEncrypt = CALG_RC2;
					return TRUE;

				case IDC_RC4:
					AlgidEncrypt = CALG_RC4;
					return TRUE;
			
				case IDOK:
					if (!AlgidEncrypt)
						AlgidEncrypt = CALG_RC2;
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* HashDlgProc()
*
* Dialog procedure for "HASH_ALGORITHM" dialog box
\************************************************************************/

WINAPI HashDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			if (AlgidSign == CALG_SHA)
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_SHA);
			else if (AlgidSign == CALG_MD5)
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_MD5);
			else
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_MD4);
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDC_MD4:
					AlgidSign = CALG_MD4;
					return TRUE;

				case IDC_MD5:
					AlgidSign = CALG_MD5;
					return TRUE;

				case IDC_SHA:
					AlgidSign = CALG_SHA;
					return TRUE;

				case IDOK:
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* GetPass()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Creates a dialog box prompting the user to enter a password.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetPass(HWND hWnd) {
	INT bRet = 0;

	do {
		if (bRet == -1)
			break;

		// Prompt the user to enter a password.

		bRet = DialogBox(_Module.GetModuleInstance(), TEXT("PASSWORD"), hWnd, EnterPass);
	} while (!bRet || !lstrcmp(sPass, TEXT("\0")) || !lstrcmp(sPass, TEXT("")));

	AlgidEncrypt = 0;
	
	return TRUE;
}

/************************************************************************\
* Exit1 and Exit2 close handles, etc. for CFILEREncryptFile,
* CFILERDecryptFile, SignFile, and VerifyFile.
\************************************************************************/

void Exit1(HWND hWnd, LPTSTR message, HANDLE hFile1, HANDLE hFile2) {
	CloseHandle(hFile1);
	CloseHandle(hFile2);
	MessageBox(hWnd, message, NULL, MB_OK);
	return;
}

void Exit2(HWND hWnd, LPTSTR message, HWND hwndDlg, HANDLE hFile1, HANDLE hFile2) {
	CloseHandle(hFile1);
	CloseHandle(hFile2);
	EndDialog(hwndDlg, FALSE);
	MessageBox(hWnd, message, NULL, MB_OK);
	return;
}
/************************************************************************\
* CFILEREncryptFile()
*
* input:
* hWnd - HWND specified by caller
* szFileName - buffer containing full pathname of file to encrypt
*
* Opens a file to encrypt and saves the file in
* encrypted form in the same path as the plaintext file.
* It is saved as a hidden file with a random filename. Its filename is
* encrypted with fnKey and is stored in the header of the file.
* Deletes the plaintext file.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL EncryptFile(HWND hWnd, LPTSTR szFileName, TCHAR szCryptedFileName[PATH_SIZE] ) {
	TCHAR					szEncryptedFileName[PATH_SIZE];	
	TCHAR					szFileName2[PATH_SIZE];
	TCHAR					szRandomName[PATH_SIZE];
	TCHAR					szDirBuf[PATH_SIZE];
	BYTE					pEncryptBuf[2 * BUF_SIZE];
	DWORD					dwNumBytesRead = BUF_SIZE;
	DWORD					dwNumBytesWritten;
	DWORD					dwEncryptLen = BUF_SIZE;
	HWND					hwndDlg;
	HCRYPTKEY				hFileKey;
	HCRYPTKEY				phEncryptPubKey;
	HCRYPTKEY				hfnKey;
	BYTE 					pbFileKeyBlob[BUF_SIZE];
	DWORD 					dwFileBlobLen = BUF_SIZE;
	HANDLE					hFileRead = INVALID_HANDLE_VALUE;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTHASH				hHash;
	DWORD					dwBufLen = HEADER_SIZE * sizeof(TCHAR);
	DWORD					dwDataLen = HEADER_SIZE * sizeof(TCHAR);

	if (!szFileName) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}
	
	SeparatePathName2(szFileName, szDirBuf, szEncryptedFileName);
	
	GetEncryptPublicKey(hWnd, &phEncryptPubKey);
	GenRandomName(szRandomName);
	
	// Generate a key to encrypt this file only if the user
	// selected the password option

	if (!AlgidEncrypt) {
		if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_MD4, 0, 0, &hHash))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptCreateHash failed."), NULL, MB_OK);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)sPass, lstrlen(sPass), 0))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptHashData failed."), NULL, MB_OK);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptDeriveKey(hMe, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hFileKey))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptDeriveKey failed."), NULL, MB_OK);
			return FALSE;
		}
	
		CryptDestroyHash(hHash);
	}
	// Generate a key to encrypt this file only (not derived from password).
	else if (RCRYPT_FAILED(CryptGenKey(hMe, AlgidEncrypt, CRYPT_EXPORTABLE, &hFileKey))) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptGenKey failed."), NULL, MB_OK);
		return FALSE;
	} 

	dwFileBlobLen = MAXBLOBLEN;

	//Export the key so that it can be stored on the disk.

	if (RCRYPT_FAILED(CryptExportKey(hFileKey, 
					  phEncryptPubKey, 
					  SIMPLEBLOB, 
					  0, 
					  pbFileKeyBlob, 
					  &dwFileBlobLen))) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptExportKey failed."), NULL, MB_OK);
		return FALSE;
	}

   	if (!AlgidEncrypt)
   		dwFileBlobLen = 0;
   		
   	// Open a file to encrypt
	
	hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}
	      
	lstrcpy(szFileName2, szDirBuf);
	lstrcat(szFileName2, TEXT("\\"));
	lstrcat(szFileName2, szRandomName); 
	
	// Create a hidden .CRP file with a random filename.
	
	hFileWrite = CreateFile(szFileName2, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							0, 
							CREATE_NEW, 
							FILE_ATTRIBUTE_HIDDEN, 
							0);
	
	if (hFileWrite == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("Cannot write to media."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	
	}
	
	// Tell the user that the program is busy encrypting data
	hwndDlg = CreateDialog(_Module.GetModuleInstance(), TEXT("ENCRYPTING"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: CreateDialog failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptEncrypt(hfnKey, 0, TRUE, 0, (LPBYTE)szEncryptedFileName, &dwDataLen, dwBufLen))) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: CryptEncrypt failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}	

	// Write the original file's encrypted name to disk.
	
	if (RCRYPT_FAILED(WriteFile(hFileWrite, 
				      szEncryptedFileName, 
				      HEADER_SIZE * sizeof(*szEncryptedFileName), 
				      &dwNumBytesWritten, 
				      0))) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Write the key blob length to disk.	
	
	if (!WriteFile(hFileWrite, &dwFileBlobLen, sizeof(dwFileBlobLen), &dwNumBytesWritten, 0)) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Write the key blob to disk.
	
	if (dwFileBlobLen && !WriteFile(hFileWrite, 
									pbFileKeyBlob, 
									dwFileBlobLen, 
									&dwNumBytesWritten, 
									0)) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Encrypt the file by reading small amounts
	// of data from the disk, encrypting those Bufs, and saving the
	// encrypted Bufs to disk. The loop terminates as soon as there is
	// not enough data left on the disk to read a full Buf.

	for ( ; ; ) {

		if (!ReadFile(hFileRead, pEncryptBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: ReadFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
		
		if (dwNumBytesRead != BUF_SIZE)
			break;
			
		if (RCRYPT_FAILED(CryptEncrypt(hFileKey, 0, FALSE, 0, pEncryptBuf, &dwEncryptLen, BUF_SIZE))) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: CryptEncrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pEncryptBuf, dwEncryptLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		dwEncryptLen = BUF_SIZE;
	}

	// Encrypt the last block of data.

	if (0 < dwNumBytesRead && dwNumBytesRead < BUF_SIZE) {
		dwEncryptLen = dwNumBytesRead;

		if (RCRYPT_FAILED(CryptEncrypt(hFileKey, 0, TRUE, 0, pEncryptBuf, &dwEncryptLen, BUF_SIZE))) {
			Exit2(hWnd, TEXT("CryptEncrypt failed."), hwndDlg, hFileRead, hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pEncryptBuf, dwEncryptLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, TEXT("WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
	}

	if (RCRYPT_FAILED(CryptDestroyKey(hFileKey))) {
		Exit2(hWnd, TEXT("CryptDestroyKey failed."), hwndDlg, hFileRead,hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	CloseHandle(hFileRead);
	
	if (!DeleteFile(szFileName)) {
		EndDialog(hwndDlg, FALSE);
		MessageBox(hWnd, TEXT("File cannot be deleted: It is either in use by another process, or it is a system file."), NULL, MB_OK);
		CloseHandle(hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}
	
	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileWrite);
	SetFileAttributes(szFileName2, FILE_ATTRIBUTE_HIDDEN);
	
	return TRUE;
}

/************************************************************************\
* CFILERDecryptFile()
*
* input:
* hWnd - HWND specified by caller
* szFileName - buffer containing full pathname of file to decrypt.
*
* purpose:
* decrypts the file specified by szFileName and stores the file in
* the same directory. Deletes the encrypted file.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL DecryptFile(HWND hWnd, LPTSTR szFileName)
{
	TCHAR					szFileName2[PATH_SIZE];
	TCHAR					szDecryptedFileName[PATH_SIZE];
	TCHAR					szFile[PATH_SIZE];
	BYTE					pDecryptBuf[2 * BUF_SIZE];
	DWORD					dwNumBytesRead;
	DWORD					dwNumBytesWritten;
	DWORD					dwDecryptDataLen = BUF_SIZE;
	HCRYPTKEY				hFileKey;
	HCRYPTKEY				phEncryptPubKey;
	BYTE 					pbDecryptBlob[BUF_SIZE];
	DWORD 					dwDecryptBlobLen;			
	HWND					hwndDlg;
	HANDLE					hFileRead;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTHASH				hHash;
	DWORD					dwDataLen = HEADER_SIZE * sizeof(TCHAR);
//	BYTE					pHashData[BUF_SIZE];
	DWORD					HashDataLen;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	GetEncryptPublicKey(hWnd, &phEncryptPubKey);
	
	GetDecryptedFileName(hWnd, 
						 szFileName, 
						 szDecryptedFileName, 
						 &hFileRead);

	// Read the key blob length from the disk.	
	
	if (!ReadFile(hFileRead, &dwDecryptBlobLen, sizeof(dwDecryptBlobLen), &dwNumBytesRead, 0)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: ReadFile failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	}

	// Read the key blob from the disk into a Buf.
	
	if (dwDecryptBlobLen && !ReadFile(hFileRead, 
									  pbDecryptBlob, 
									  dwDecryptBlobLen, 
									  &dwNumBytesRead, 
									  0)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: ReadFile failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	} 

	// Import the key whose blob is contained in the Buf pbDecryptBlob
	
	if (dwDecryptBlobLen && !CryptImportKey(hMe, 
											pbDecryptBlob, 
											dwDecryptBlobLen, 
											0, 
											0, 
											&hFileKey)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptImportKey failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	}

	SeparatePathName(szFileName, szFileName2, szFile);
	
	lstrcat(szFileName2, TEXT("\\"));
	lstrcat(szFileName2, szDecryptedFileName);
	
	// Generate a key to decrypt this file if the user
	// selected the password option

	if (!dwDecryptBlobLen) {
		lstrcpy(szPassName, szFileName2);
			
		if (!GetPass(hWnd)) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: GetPass failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		lstrcpy(szPassName, TEXT("\0"));
		
		if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_MD4, 0, 0, &hHash))) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptCreateHash failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)sPass, lstrlen(sPass), 0))) {
			MessageBox(hWnd, TEXT("DecrypttFile: CryptHashData failed."), NULL, MB_OK);
			return FALSE;
		}

		HashDataLen = BUF_SIZE;

		if (RCRYPT_FAILED(CryptDeriveKey(hMe, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hFileKey))) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptDeriveKey failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		CryptDestroyHash(hHash);
		
		dwDecryptBlobLen = 0;
	}
	
	// Recreate the plaintext file
	
	hFileWrite = CreateFile(szFileName2, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							0, 
							CREATE_ALWAYS, 
							FILE_ATTRIBUTE_NORMAL, 
							0);

	if (hFileWrite == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILENAME_EXCED_RANGE) {
			TCHAR szEmergencyName[PATH_SIZE];
			TCHAR szEmergencyRandomName[PATH_SIZE];
			TCHAR szDir1[PATH_SIZE];
			TCHAR szFile1[PATH_SIZE];
			SeparatePathName(szFileName, szDir1, szFile1);
			GenRandomName2(szEmergencyRandomName);
			lstrcpy(szEmergencyName, szDir1);
			lstrcat(szEmergencyName, TEXT("\\recovered"));
			lstrcat(szEmergencyName, szEmergencyRandomName);
			hFileWrite = CreateFile(szEmergencyName, GENERIC_READ | GENERIC_WRITE,
										0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if (hFileWrite == INVALID_HANDLE_VALUE) {
				ErrorMsg(TEXT("Could not recover file."));
				return FALSE;
			}
		}
		else {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CreateFile failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}
	}
	
	// Create a dialog box to inform the user that the program is busy decrypting data.

	hwndDlg = CreateDialog(_Module.GetModuleInstance(), TEXT("DECRYPTING"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		Exit2(hWnd, TEXT("CFILERDecryptFile: CreateDialog failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// The following for loop decrypts the data in units of BUF_SIZE
	// at a time and stores the decrypted data into the file hFileWrite.
	// The loop terminates when fewer than BUF_SIZE have been read.

	for ( ; ; ) {
		if (!ReadFile(hFileRead, pDecryptBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: ReadFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (dwNumBytesRead != BUF_SIZE)
			break;
		
		if (RCRYPT_FAILED(CryptDecrypt(hFileKey, 0, FALSE, 0, pDecryptBuf, &dwDecryptDataLen))) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: CryptDecrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pDecryptBuf, dwDecryptDataLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		dwDecryptDataLen = BUF_SIZE;
	}

	// Decrypt the final block of data.
	
	if (0 < dwNumBytesRead && dwNumBytesRead < BUF_SIZE) {
		dwDecryptDataLen = dwNumBytesRead;
		
		if (RCRYPT_FAILED(CryptDecrypt(hFileKey, 0, TRUE, 0, pDecryptBuf, &dwDecryptDataLen))) {

			MessageBox(hWnd, TEXT("GetfnKey: CryptImportKey failed"), NULL, MB_OK);
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: CryptDecrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pDecryptBuf, dwDecryptDataLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
	}

	if (!CryptDestroyKey(hFileKey)) {
		Exit2(hWnd, 
				TEXT("CFILERDecryptFile: CryptDestroyKey failed."),
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileRead);
	CloseHandle(hFileWrite);
	
	if (!DeleteFile(szFileName)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: DeleteFile failed."), NULL, MB_OK);
		DeleteFile(szFileName2);
	}
	
	return TRUE;
}

/************************************************************************\
* SignFile:
* Opens a file, creates a hash value of the file,
* signs that hash value, and stores the result to disk.
\************************************************************************/

BOOL SignFile(HWND hWnd, LPTSTR szFileName,	TCHAR szSigFileName[PATH_SIZE]) {
	TCHAR 					szFilter1[] = TEXT("Signature Files (*.SGN)\0*.SGN\0");
	TCHAR 					szFilter2[] = TEXT("All Files (*.*)\0*.*\0");
	TCHAR					szFile[PATH_SIZE] = TEXT("\0");
	TCHAR					szFile2[PATH_SIZE] = TEXT("\0");
	TCHAR					szFileTitle[PATH_SIZE];
	DWORD					dwNumBytesRead = BUF_SIZE;
	DWORD					dwNumBytesWritten;
	HWND					hwndDlg;
	HANDLE					hFileRead = INVALID_HANDLE_VALUE;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTKEY				phSignaturePubKey;
	HCRYPTHASH				hHash;
	BYTE					pSignBuf[BUF_SIZE];
	BYTE					pbHash[BUF_SIZE];
	DWORD					dwHashLen;

	GetSignaturePublicKey(hWnd, &phSignaturePubKey);
	
	if (!szFileName) {
		MessageBox(hWnd, TEXT("SignFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	lstrcpy(szFile, TEXT(""));
	lstrcpy(szFileTitle, TEXT(""));
	
	// Open plaintext file
	
	hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("SignFile: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}

	// hash the full pathname of the file. This will be the name of
	// the signature file.
	
	if (!GetSigFileName(szFileName, szSigFileName)) {
		MessageBox(hWnd, TEXT("SignFile: GetSigFileName failed."), NULL, MB_OK);
		return FALSE;
	}

	// Create signature file.
	
	if (GetFileAttributes(szSigFileName) == 0xFFFFFFFF) {
		
		hFileWrite = CreateFile(szSigFileName, 
								GENERIC_READ | GENERIC_WRITE, 
								0, 
								0, 
								CREATE_NEW, 
								FILE_ATTRIBUTE_NORMAL, 
								0);
				
		if (hFileWrite == INVALID_HANDLE_VALUE) {
			Exit1(hWnd, TEXT("SignFile: CreateFile failed."), hFileRead, hFileWrite);
			return FALSE;
		} 
	}
	else {
		if (MessageBox(hWnd, 
					   TEXT("Delete signature?"), 
					   TEXT("Signature file already exists."), 
					   MB_OKCANCEL) == IDOK) {

			DeleteFile(szSigFileName);

			hFileWrite = CreateFile(szSigFileName,
									GENERIC_READ | GENERIC_WRITE,
									0,
									0,
									CREATE_NEW,
									FILE_ATTRIBUTE_HIDDEN,
									0);
		
			if (hFileWrite == INVALID_HANDLE_VALUE) {
				Exit1(hWnd, TEXT("SignFile: CreateFile failed."), hFileRead, hFileWrite);
				return FALSE;
			}
		}
		else {
			CloseHandle(hFileRead);
			
			return FALSE;
		}
	}
	
	// Create a dialog box to inform the user that the program is hashing data.
	
	hwndDlg = CreateDialog(_Module.GetModuleInstance(), TEXT("SIGNING"), hWnd, CryptDlgProc);
	
	if (RCRYPT_FAILED(CryptCreateHash(hMe, AlgidSign, 0, 0, &hHash))) {
		Exit2(hWnd, TEXT("SignFile: CryptCreateHash failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szSigFileName);
		return FALSE;
	}

	// The following for loop hashes the file in BUF_SIZE Bufs at a time.
	
	for (dwNumBytesRead = BUF_SIZE ; dwNumBytesRead == BUF_SIZE; ) {
		if (!ReadFile(hFileRead, pSignBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("SignFile: ReadFile failed."), 
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szSigFileName);
			return FALSE;
		}
		else if (RCRYPT_FAILED(CryptHashData(hHash, pSignBuf, dwNumBytesRead, 0))) {
			Exit2(hWnd, 
					TEXT("SignFile: CryptHashData failed."), 
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szSigFileName);
			return FALSE;
		}
	}

	dwHashLen = BUF_SIZE;

	if (RCRYPT_FAILED(CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbHash, &dwHashLen)))
	{

		MessageBox(hWnd, TEXT("SignFile: CryptSignHash failed"), NULL, MB_OK);

		Exit2(hWnd, 
				TEXT("SignFile: CryptSignHash failed."), 
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szSigFileName);
		return FALSE;
	} 

	// Write ALG_ID to disk
	
	if (!WriteFile(hFileWrite, &AlgidSign, sizeof(ALG_ID), &dwNumBytesWritten, 0)) {
		Exit2(hWnd, TEXT("SignFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		return FALSE;
	}
	
	// Write hash to disk.
	
	if (!WriteFile(hFileWrite, pbHash, dwHashLen, &dwNumBytesWritten, 0)) {
		Exit2(hWnd, 
				TEXT("SignFile: WriteFile failed."), 
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szSigFileName);
		return FALSE;
	}

	CryptDestroyHash(hHash);
	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileRead);
	CloseHandle(hFileWrite);
	
	return TRUE;
}

/************************************************************************\
* VerifyFile
* Opens a signature file and the original file.
* Hashes the original file and tries to verify
* the hash.
\************************************************************************/

BOOL VerifyFile(HWND hWnd, LPTSTR szFileName, LPTSTR szSigFileName) {
	TCHAR 					szFilter1[] = TEXT("Signature Files (*.SGN)\0*.SGN\0");
	TCHAR 					szFilter2[] = TEXT("All Files (*.*)\0*.*\0");
	TCHAR					szFile[PATH_SIZE] = TEXT("\0");
	TCHAR					szFile2[PATH_SIZE] = TEXT("\0");
	TCHAR					szFileTitle[PATH_SIZE];
	TCHAR					szFileName2[PATH_SIZE];
	DWORD					dwNumBytesRead;
	DWORD					dwNumBytesRead2;
	HWND					hwndDlg;
	HANDLE					hFileOrig = INVALID_HANDLE_VALUE;
	HANDLE					hFileSig = INVALID_HANDLE_VALUE;
	BYTE					pbSig[BUF_SIZE];
	BYTE					pVerifyBuf[BUF_SIZE];
	DWORD					dwSigLen;
	HCRYPTHASH				hHash;
	HCRYPTKEY				phSignaturePubKey;
	ALG_ID 					DiskAlgid;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("VerifyFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	GetSignaturePublicKey(hWnd, &phSignaturePubKey);
	
	// hash the full pathname of the file to determine the signature file
	// to open.
	
/*
	if (!GetSigFileName(szFileName, szFileName2)) {
		MessageBox(hWnd, TEXT("VerifyFile: GetSigFileName failed."), NULL, MB_OK);
		return FALSE;
	}
*/
	strcpy(szFileName2,szSigFileName);

	lstrcpy(szFile, TEXT(""));
	lstrcpy(szFileTitle, TEXT(""));

	// Open the plaintext file to hash it.
	
	hFileOrig = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileOrig == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("VerifyFile: CreateFile failed."), NULL, MB_OK);
		CloseHandle(hFileOrig);
		return FALSE;
	}

	// Automatically open the signature file if it 
	// exists in the same directory as the file to be verified.
	// Otherwise, prompt the user to browse the directory tree 
	// for the signature file.
	
	if (GetFileAttributes(szFileName2) != 0xFFFFFFFF) {
		
		hFileSig = CreateFile(szFileName2, 
							  GENERIC_READ, 
							  0, 
							  0, 
							  OPEN_EXISTING, 
							  FILE_ATTRIBUTE_READONLY, 
							  0);
		
		if (hFileSig == INVALID_HANDLE_VALUE) {
			Exit1(hWnd, TEXT("VerifyFile: CreateFile failed."), hFileOrig, hFileSig);
			return FALSE;
		} 
	}
	else {
		Exit1(hWnd, TEXT("Signature file does not exist."), hFileOrig, hFileSig);
		return FALSE;
	} 
	
	// Create a dialog box to tell the user that the program is busy hashing data.

	hwndDlg = CreateDialog(_Module.GetModuleInstance(), TEXT("VERIFYING"), hWnd, CryptDlgProc);
	
	// Read the ALG_ID
	
	if (!ReadFile(hFileSig, &DiskAlgid, sizeof(ALG_ID), &dwNumBytesRead2, 0)) {
		Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}
	
	// Read the hash
	
	if (!ReadFile(hFileSig, pbSig, BUF_SIZE, &dwSigLen, 0)) {
		Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptCreateHash(hMe, DiskAlgid, 0, 0, &hHash))) {
		Exit2(hWnd, TEXT("VerifyFile: CryptCreateHash failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}

	// hash the file in BUF_SIZE chunks
	
	for (dwNumBytesRead = BUF_SIZE; dwNumBytesRead == BUF_SIZE; ) {
		if (!ReadFile(hFileOrig, pVerifyBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
			return FALSE;
		}
		if (RCRYPT_FAILED(CryptHashData(hHash, pVerifyBuf, dwNumBytesRead, 0))) {
			Exit2(hWnd, 
					TEXT("VerifyFile: CryptHashData failed."), 
					hwndDlg, 
					hFileOrig, 
					hFileSig);
			return FALSE;
		}
	}


	if (RCRYPT_FAILED(CryptVerifySignature(hHash, pbSig, dwSigLen, phSignaturePubKey, 0, 0))) {
		EndDialog(hwndDlg, FALSE);
		MessageBox(hWnd, 
				   TEXT("Could not verify signature."), 
				   TEXT("Result"), 
				   MB_OK | MB_ICONINFORMATION);
		CloseHandle(hFileOrig);
		CloseHandle(hFileSig);
		return TRUE;
	}

	if (RCRYPT_FAILED(CryptDestroyHash(hHash))) {
		Exit2(hWnd, 
				TEXT("Could not destroy hash."), 
				hwndDlg, 
				hFileOrig, 
				hFileSig);
		return FALSE;
	}
	
	EndDialog(hwndDlg, FALSE);
	
/*	MessageBox(hWnd, 
			   TEXT("Signature verified."), 
			   TEXT("Result"), 
			   MB_OK | MB_ICONINFORMATION);
*/
	CloseHandle(hFileOrig);
	CloseHandle(hFileSig);
	
	return TRUE;
}

/************************************************************************\
* GetSignaturePublicKey()
*
* input:
* hWnd - HWND specified by caller
* phSignaturePubKey - address to store key
*
* purpose: calls CryptGetUserKey to obtain the AT_SIGNATURE public
* key.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSignaturePublicKey(HWND hWnd, HCRYPTKEY *phSignaturePubKey) {
	if (!phSignaturePubKey) {
		ErrorMsg(TEXT("GetSignaturePublicKey: phSignaturePubKey is NULL."));
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptGetUserKey(hMe, AT_SIGNATURE, phSignaturePubKey))) {
		if (RCRYPT_FAILED(CryptGenKey(hMe, AT_SIGNATURE, 0, phSignaturePubKey))) {
			ErrorMsg(TEXT("GetSignaturePublicKey: CryptGenKey failed."));
			return FALSE;
		}
	}
	
	return TRUE;
}

//=================================================================================================
CCryptoSealInterface * CryptoSeal;
CComBSTR bstrCryptoSealDatabase;
CComBSTR bstrCryptoSealPassword;
CCryptoSealCertificate * SCardCertificate;

const char* errordescriptions[] = 
{
	"CSOK",
	"CS_UNSPECIFIED",
	"CS_MEMORY",
	"CS_DB_PATHNAME",
	"CS_CANT_OPEN_PKCS11",
	"CS_TOKEN",
	"CS_CANT_OPEN_SESSION",
	"CS_PCSC",
	"CS_CARD_MISSING",
	"CS_PIN_INVALID",
	"CS_LOGIN_FAILED",
	"CS_CANT_CLOSE_PKCS11",
	"CS_CANT_LOAD_CERTIFICATES",
	"CS_NOT_INITIALIZED",
	"CS_PRIVATE_KEY_NOT_FOUND",
	"CS_OWN_CERTIFICATE_NOT_FOUND",
	"CS_PUBLIC_KEY_CANT_DELETE",
	"CS_FILE_CANT_CREATE",
	"CS_FILE_CANT_OPEN",
	"CS_FILE_CANT_READ",
	"CS_FILE_CANT_WRITE",
	"CS_FILE_CANT_SEEK",
	"CS_FILE_CANT_CLOSE",
	"CS_CERTIFICATE_CANT_ENTER",
	"CS_CERTIFICATE_CANT_RETRIEVE",
	"CS_CERTIFICATE_CANT_DELETE",
	"CS_CERTIFICATE_CANT_READ",
	"CS_CERTIFICATE_CANT_WRITE",
	"CS_CERTIFICATE_NOT_OWN",
	"CS_CERTIFICATE_NOT_VALID",
	"CS_CERTIFICATE_MULTIPLE_NOT_VALID",
	"CS_CERTIFICATE_CANT_EXTRACT_PUBLIC_KEY",
	"CS_CERTIFICATE_ISSUER_MISSING",
	"CS_CERTIFICATE_ALGORITHM_UNKNOWN",
	"CS_CERTIFICATE_OUT_OF_PERIOD",
	"CS_CERTIFICATE_DATA",
	"CS_CERTIFICATE_SIGNATURE_INVALID",
	"CS_CERTIFICATE_SELFSIGNED_NOT_TRUSTED",
	"CS_DOCUMENT_CANT_RETRIEVE",
	"CS_DOCUMENT_CANT_DELETE",
	"CS_DOCUMENT_HAS_CONTENTS",
	"CS_DOCUMENT_NO_CONTENTS",
	"CS_DOCUSER_CANT_ADD",
	"CS_DOCUSER_CANT_RETRIEVE",
	"CS_DOCUSER_NO_CERTIFICATE",
	"CS_DOCUSER_NO_SIGNATURE",
	"CS_SIGNATURE_LENGTH",
	"CS_SIGNATURE_CANT_CALC",
	"CS_SIGNATURE_CANT_LOAD",
	"CS_SIGNATURE_CANT_SET",
	"CS_SIGNATURE_NOT_VALID",
	"CS_SIGNATURE_ALGORITHM_UNKNOWN",
	"CS_SIGNATURE_NOT_SAME_ISSUER",
	"CS_SIGNATURE_NOT_SAME_CERTIFICATE_NO"
};

STDMETHODIMP CTSCryptSvr::GetErrorDescription(long lErrorCode, BSTR *strErrorDescription, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 long errorcode;
	if( TSERRBASE != (lErrorCode & TSERRBASE) ) {
		CComBSTR bstrErrorDescription("Unbekannter Fehlercode! (nicht von TSCrypt erzeugt)");
		*strErrorDescription = bstrErrorDescription.Detach();
	}
	else {
		errorcode = lErrorCode & ~TSERRBASE;
		if( 0 > errorcode || errorcode > CS_SIGNATURE_NOT_VALID ) {
			CComBSTR bstrErrorDescription("Unbekannter Fehlercode!");
			*strErrorDescription = bstrErrorDescription.Detach();
		}
		else {
			CComBSTR bstrErrorDescription(errordescriptions[errorcode]);
			*strErrorDescription = bstrErrorDescription.Detach();
		}
	}
	*pResult = 0;
	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetPassword(long hWnd, long* pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pResult = 0;
	AlgidEncrypt = 0;
	if (!GetPass((HWND)hWnd) || strlen(sPass) == 0) {
		AlgidEncrypt = CALG_RC2;
		*pResult = -1;
	}

	return S_OK;
}


STDMETHODIMP CTSCryptSvr::Logon(long hWnd, long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( ::Logon( (HWND)hWnd ) ) {
		*pResult = 0;
		AlgidSign = CALG_MD4;
	}
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::Logoff(long hWnd, long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( ::Logoff( (HWND)hWnd ) )
		*pResult = 0;
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::get_AlgID_Sign(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = AlgidSign;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::put_AlgID_Sign(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AlgidSign = newVal;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SignFile(long hWnd, BSTR strFileName, BSTR * strSigFileName, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	TCHAR szSigFileName[PATH_SIZE];

	if( ::SignFile( (HWND)hWnd, OLE2A(strFileName), szSigFileName )) {
		unsigned char *pBuffer = NULL;
		CComBSTR bstrSigFileName(szSigFileName);

		*strSigFileName = bstrSigFileName.Detach();
		*pResult = 0;
	}
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::VerifyFile( long hWnd, BSTR strFileName, BSTR strSigFileName, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( ::VerifyFile( (HWND)hWnd, OLE2A(strFileName), OLE2A(strSigFileName) ))
		*pResult = 0;
	else
		*pResult = -1;

	return S_OK;
}
/*
STDMETHODIMP CTSCryptSvr::SetPassword(BSTR strPassword, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	strcpy( sPass, OLE2A(strPassword) );

	*pResult = 0;

	return S_OK;
}
*/
STDMETHODIMP CTSCryptSvr::EncryptFile(long hWnd, BSTR strFileName, BSTR * strCryptedFileName, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	TCHAR szCryptedFileName[PATH_SIZE];

	if( ::EncryptFile( (HWND)hWnd, OLE2A(strFileName), szCryptedFileName )) {
		CComBSTR bstrCryptedFileName(szCryptedFileName);

		*strCryptedFileName = bstrCryptedFileName.Detach();
		*pResult = 0;
	}
	else
		*pResult = -1;

	return S_OK;
}


CTSCryptSvr::CTSCryptSvr(void) {
	
//	MessageBox(NULL, "Los Gehts!", "CTSCryptSvr", MB_OK);
};

/*
STDMETHODIMP CTSCryptSvr::Initialize_CS(long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CryptoSeal = CCryptoSealInterface::Initialize();
	if( NULL == CryptoSeal )
		*pResult = -1;
	else
		*pResult = 0;

	return S_OK;
}
*/
STDMETHODIMP CTSCryptSvr::SetDatabase(BSTR strDataBaseName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 HKEY hKey;
 
	bstrCryptoSealDatabase = strDataBaseName;
	hResult = RegCreateKey(HKEY_CURRENT_USER, "Software\\FAKTUM\\FAKTUM CryptoSeal", &hKey);
	if( ERROR_SUCCESS == hResult ) {
        hResult = RegSetValueEx(hKey, "ObjectsPathName", 0, REG_SZ, (const unsigned char*)OLE2A(strDataBaseName), bstrCryptoSealDatabase.Length());
        RegCloseKey(hKey);
	}

	*pResult = hResult;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SetPassword(BSTR strPassword, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	bstrCryptoSealPassword = strPassword;
	*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::Open(long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		CryptoSeal = CCryptoSealInterface::Initialize();
	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		if( 0 == bstrCryptoSealPassword.Length() ) 
			hResult = CryptoSeal->Open(NULL); 
		else
			hResult = CryptoSeal->Open(OLE2A(bstrCryptoSealPassword)); 
	}
//	if( CSOK == hResult ) {
//		SCardCertificate = CryptoSeal->GetOwnCertificate(0);
//		if( NULL == SCardCertificate )
//			hResult = 2;
//		else{
//			if( true == CryptoSeal->Find(SCardCertificate) )
//				hResult = CryptoSeal->Add(SCardCertificate);
//			hResult = CryptoSeal->ExportCertificates("C:\\TSCurUsr.der", &SCardCertificate);
//			if( !SCardCertificate->IsTrusted() ) {
//				hResult = SCardCertificate->SetTrusted(true);
//			}
//		}
//	}
	
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;
	return S_OK;
}

STDMETHODIMP CTSCryptSvr::Close(long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( NULL != CryptoSeal ){
		CryptoSeal->Close();
		CryptoSeal = NULL;
		*pResult = 0;
	}
	else
		*pResult = 1;

	return S_OK;
}


STDMETHODIMP CTSCryptSvr::GetSCardLabel_CS(BSTR *strLabel, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( NULL != SCardCertificate ) {
		CComBSTR bstrLabel(SCardCertificate->GetLabel());

		*strLabel = bstrLabel.Detach();
		*pResult = 0;
	}
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetSCardOwnerCommonName_CS(BSTR *strOwnerCommonName, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( NULL != SCardCertificate ) {
		CComBSTR bstrOwnerCommonName(SCardCertificate->GetOwnerCommonName());

		*strOwnerCommonName = bstrOwnerCommonName.Detach();
		*pResult = 0;
	}
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetSCardIssuerCommonName_CS(BSTR *strIssuerCommonName, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( NULL != SCardCertificate ) {
		CComBSTR bstrIssuerCommonName(SCardCertificate->GetIssuerCommonName());

		*strIssuerCommonName = bstrIssuerCommonName.Detach();
		*pResult = 0;
	}
	else
		*pResult = -1;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::ImportCertificates(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
	if( NULL == CryptoSeal ) 
		hResult = 0x1001;
	else
		hResult = CryptoSeal->ImportCertificates(OLE2A(strFileName)); 

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

CCryptoSealDocument* pCryptoSealDocument;

STDMETHODIMP CTSCryptSvr::LoadContent(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
	if( NULL == CryptoSeal ) 
		hResult = 0x1001;
	else {
		if( NULL != pCryptoSealDocument ) 
			hResult = CryptoSeal->Remove( pCryptoSealDocument );
		pCryptoSealDocument = CryptoSeal->GetNewDocument();
		if( NULL == pCryptoSealDocument )
			hResult = CryptoSeal->GetLastError();
		else
			hResult = pCryptoSealDocument->SetContents(OLE2A(strFileName));
	}
/*		
 HANDLE	hFileRead = INVALID_HANDLE_VALUE;
 DWORD dwFileSize;
 DWORD dwNumBytesRead;
 byte* baContent;
   	// Open a file to encrypt
	
	hFileRead = CreateFile(OLE2A(strFileName), 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("CFILEREncryptFile: CreateFile failed."), NULL, MB_OK);
		*pResult = -1;
		return S_OK;
	}
	dwFileSize = GetFileSize(hFileRead, NULL);
	baContent = new byte[dwFileSize];
	if (!ReadFile(hFileRead, baContent, dwFileSize, &dwNumBytesRead, 0)) {
		*pResult = -2;
	}
	else {
		pCryptoSealDocument = CryptoSeal->GetNewDocument();
		if( NULL == pCryptoSealDocument ) {
			*pResult = -3;
		}
		else {
			if( pCryptoSealDocument->SetContents((char*)baContent,dwFileSize) )
				*pResult = 0;
			else
				*pResult = -4;
		}
	}
	CloseHandle(hFileRead);
	delete baContent;
*/
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::LoadDocument(BSTR strFileName, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
 
 HRESULT hResult;
	if( NULL == CryptoSeal ) 
		hResult = 0x1001;
	else {
		if( NULL != pCryptoSealDocument ) 
			hResult = CryptoSeal->Remove( pCryptoSealDocument );
		pCryptoSealDocument = CryptoSeal->GetNewDocument();
		if( NULL == pCryptoSealDocument )
			hResult = CryptoSeal->GetLastError();
		else
			hResult = pCryptoSealDocument->SetDocument(OLE2A(strFileName));
	}
/* 		
 HANDLE	hFileRead = INVALID_HANDLE_VALUE;
 DWORD dwFileSize;
 DWORD dwNumBytesRead;
 byte* baDocument;
	
	hFileRead = CreateFile(OLE2A(strFileName), 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("CFILEREncryptFile: CreateFile failed."), NULL, MB_OK);
		hResult = 0x1001;
	}
	else {
		dwFileSize = GetFileSize(hFileRead, NULL);
		baDocument = new byte[dwFileSize];
		if (!ReadFile(hFileRead, baDocument, dwFileSize, &dwNumBytesRead, 0)) {
			hResult = 0x1002;
		}
		else {
			pCryptoSealDocument = CryptoSeal->GetNewDocument();
			if( NULL == pCryptoSealDocument )
				hResult = CryptoSeal->GetLastError();
			else
				hResult = pCryptoSealDocument->SetDocument((char*)baDocument,dwFileSize);
		}
		CloseHandle(hFileRead);
		delete baDocument;
	}
*/
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::Sign_CS(long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

 CCryptoSealCertificate* pCertificate;			

	hResult = 0;
	if( NULL == pCryptoSealDocument )
		hResult = 1;
	else {
		pCertificate = CryptoSeal->GetOwnCertificate(0);
		if( NULL == pCertificate )
			hResult = 2;
		else
			hResult = pCryptoSealDocument->Sign(true, pCertificate);
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;
	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetSignature(VARIANT * pvSignature, long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 CCryptoSealDocumentUser* pUser;
 CCryptoSealCertificate* pCertificate;			
 const char* pSignature;
 int iSignatureLength;

	pCertificate = CryptoSeal->GetOwnCertificate(0);
	if( NULL == pCertificate )
		*pResult = -1;
	else{
		if( NULL == pCryptoSealDocument )
			*pResult = -2;
		else {
			pUser = pCryptoSealDocument->GetUser( pCertificate );
			if( NULL == pUser )
				*pResult = -3;
			else {	
				pSignature = pUser->GetSignature( &iSignatureLength );
				if( NULL == pSignature )
					*pResult = -4;
				else {
					CSafeArray sa (VT_UI1, iSignatureLength);
					{
						CSafeArrayLock<BYTE> data(sa);
						memcpy (data, pSignature, data.Size());
					} // data geht out of scope (lock!)

					// Resultat verpacken
					::VariantInit(pvSignature);
					V_VT(pvSignature) = VT_UI1|VT_ARRAY;
					V_ARRAY(pvSignature) = sa.Detach();
					*pResult = 0;
				}
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SetSignature(VARIANT *pvSignature, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetContent(VARIANT *pvContent, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 const char *pContent;
 int iContentLength;

	if( NULL == pCryptoSealDocument )
		hResult = 0x1001;
	else{
		hResult = pCryptoSealDocument->GetContents( pContent, iContentLength );
		if( CSOK == hResult ) {
			CSafeArray sa (VT_UI1, iContentLength);
			{
				CSafeArrayLock<BYTE> data(sa);
				memcpy (data, pContent, data.Size());
			} // data geht out of scope (lock!)
			CryptoSeal->Delete( (void*)pContent );
			// Resultat verpacken
			::VariantInit(pvContent);
			V_VT(pvContent) = VT_UI1|VT_ARRAY;
			V_ARRAY(pvContent) = sa.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetDocument(VARIANT *pvDocument, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 const char *pDocument;
 int iDocumentLength;

	if( NULL == pCryptoSealDocument )
		hResult = 0x1001;
	else{
		hResult = pCryptoSealDocument->GetDocument( pDocument, iDocumentLength );
		if( CSOK == hResult ) {
			CSafeArray sa (VT_UI1, iDocumentLength);
			{
				CSafeArrayLock<BYTE> data(sa);
				memcpy (data, pDocument, data.Size());
			} // data geht out of scope (lock!)
			CryptoSeal->Delete( (void*)pDocument );
			// Resultat verpacken
			::VariantInit(pvDocument);
			V_VT(pvDocument) = VT_UI1|VT_ARRAY;
			V_ARRAY(pvDocument) = sa.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}


STDMETHODIMP CTSCryptSvr::GetFirstCertificate(long *ppCertificate, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCertificate;			

	if( NULL == CryptoSeal )
		hResult = 1;
	else {
		pCertificate = CryptoSeal->GetFirstCertificate(); 
		if( NULL == pCertificate ) {
			*ppCertificate = 0;
			hResult = 2;
		}
		else {
			*ppCertificate = (long)pCertificate;
			hResult = 0;
		}
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetNextCertificate(long *phCertificate, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCertificate;			

	if( NULL == CryptoSeal )
		hResult = 1;
	else {
		pCertificate = CryptoSeal->GetNextCertificate(); 
		if( NULL == pCertificate ) {
			*phCertificate = 0;
			hResult = 2;
		}
		else {
			*phCertificate = (long)pCertificate;
			hResult = 0;
		}
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetOwnerCommonName(long hCertificate, BSTR *strOwnerCommonName, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	pCert = (CCryptoSealCertificate*)hCertificate;

	if( NULL == pCert ) {
		hResult = 0x1001;
	}
	else {
		CComBSTR bstrOwnerCommonName(pCert->GetOwnerCommonName());

		*strOwnerCommonName = bstrOwnerCommonName.Detach();
		hResult = 0;
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}


STDMETHODIMP CTSCryptSvr::GetIssuerCommonName(long hCertificate, BSTR *strIssuerCommonName, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			CComBSTR bstrIssuerCommonName(pCert->GetIssuerCommonName());

			*strIssuerCommonName = bstrIssuerCommonName.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;


	return S_OK;
}

STDMETHODIMP CTSCryptSvr::ExportCertificate(BSTR strFileName, long hCertificate, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;
 CCryptoSealCertificate* Certificates[2];			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			Certificates[0] = pCert; 
			Certificates[1] = NULL;
			hResult = CryptoSeal->ExportCertificates( OLE2A(strFileName), Certificates );
		}
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetLabel(long hCertificate, BSTR *strLabel, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			CComBSTR bstrLabel(pCert->GetLabel());

			*strLabel = bstrLabel.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SetLabel(long hCertificate, BSTR strLabel, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else 
			hResult = pCert->SetLabel(OLE2A(strLabel));
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetNotAfter(long hCertificate, BSTR *strNotAfter, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			CComBSTR bstrNotAfter(pCert->GetNotAfter());
	
			*strNotAfter = bstrNotAfter.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;


	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetNotBefore(long hCertificate, BSTR *strNotBefore, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			CComBSTR bstrNotBefore(pCert->GetNotBefore());

			*strNotBefore = bstrNotBefore.Detach();
			hResult = 0;
		}
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::IsOwnCertificate(long hCertificate, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else {
			if( pCert->IsOwnCertificate() )
				hResult = 1;
			else
				hResult = 0;
		}
	}

	if(  0 != hResult && 1 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = hResult;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SaveDocument(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else
		hResult = pCryptoSealDocument->GetDocument(OLE2A(strFileName));

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SaveContent(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else
		hResult = pCryptoSealDocument->GetContents(OLE2A(strFileName));

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;
	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SetEncryptionType(long lType, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else {
		if( 0 <= lType && lType <= 3 ) {
			pCryptoSealDocument->EncryptionType = (CCryptoSealDocument::ENCRYPTIONTYPE)lType;
			hResult = 0;
		}
		else
			hResult = 0x1003;
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::AddUser(long hCertificate, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else {
		pCert = (CCryptoSealCertificate*)hCertificate;

		if( !CryptoSeal->FindAll(pCert) )
			hResult = 0x1002;
		else if( !CryptoSeal->Find(pCryptoSealDocument) )
			hResult = 0x1003;
		else
			hResult = pCryptoSealDocument->AddUser(pCert);
	}

	if(  0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = hResult;


	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetUserCount(long *lUserCount, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else {
		*lUserCount = pCryptoSealDocument->GetUserCount();
		hResult = 0;
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetSignerCount(long *lSignerCount, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else {
		*lSignerCount = pCryptoSealDocument->SignerCount();
		hResult = 0;
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetUser(long index, long *hUser, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else {
		*hUser = (long)pCryptoSealDocument->GetUser(index);
		if( 0 == *hUser )
			hResult = 0x1003;
		else
			hResult = 0;
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetUserCertificate(long hUser, long *hCertificate, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealDocumentUser* pUser;

	pUser = (CCryptoSealDocumentUser*)hUser;
	if( NULL == pUser )
		hResult = 0x1001;
	else {
		*hCertificate = (long)pUser->GetCertificate();
		if( 0 == *hCertificate )
			hResult = 0x1002;
		else
			hResult = 0;
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::ValidateSignature(long hUser, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealDocumentUser* pUser;

	pUser = (CCryptoSealDocumentUser*)hUser;
	if( NULL == pUser )
		hResult = 0x1001;
	else
		hResult = pUser->IsValidSignature(false);

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::SaveSignerInfo(long hUser, BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealDocumentUser* pUser;

	pUser = (CCryptoSealDocumentUser*)hUser;
	if( NULL == pUser )
		hResult = 0x1001;
	else
		hResult = pUser->GetSignerInfo(OLE2A(strFileName));

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::LoadSignerInfo(long hUser, BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealDocumentUser* pUser;

	pUser = (CCryptoSealDocumentUser*)hUser;
	if( NULL == pUser )
		hResult = 0x1001;
	else
		hResult = pUser->SetSignerInfo(OLE2A(strFileName));

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSCryptSvr::AddUserBySignerInfoFile(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	if( NULL == CryptoSeal )
		hResult = 0x1001;
	else if( NULL == pCryptoSealDocument )
		hResult = 0x1002;
	else {
		hResult = pCryptoSealDocument->AddUser(OLE2A(strFileName));
		if( hResult < 0 )
			hResult = pCryptoSealDocument->GetLastError();
	}

	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;


	return S_OK;
}

STDMETHODIMP CTSCryptSvr::GetOwnerEmailAddress(long hCertificate, BSTR *strOwnerEmailAddress, long *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CCryptoSealCertificate* pCert;			

	pCert = (CCryptoSealCertificate*)hCertificate;

	if( NULL == pCert ) {
		hResult = 0x1001;
	}
	else {
		CComBSTR bstrOwnerEmailAddress(pCert->GetOwnerEmailAddress());

		*strOwnerEmailAddress = bstrOwnerEmailAddress.Detach();
		hResult = 0;
	}
	if( 0 != hResult )
		*pResult = TSERRBASE | hResult;
	else
		*pResult = 0;

	return S_OK;

}
