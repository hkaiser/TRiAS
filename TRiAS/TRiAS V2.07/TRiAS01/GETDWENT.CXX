/* Lesen eines Eintrages im DB-Passwordfile                     */
/* File: GETDWENT.C             last update: 28. September 1989 */

#include "trias01p.hxx"

#include <lzexpand.h>
#include <ctype.h>

#include "dwd.h"
 
static char NEAR db_dwd_file[_MAX_PATH+1];

#if !defined(MSWIND)
static FILE * NEAR dwf = NULL;
#endif

static char NEAR line[BUFSIZ+1];
static struct dbpasswd NEAR dbpasswd;

#if defined(MSWIND)
static int NEAR fh = -1;
static OFSTRUCT NEAR of;
char * NEAR pInFile = NULL;
long NEAR FileLen = 0L;
char * NEAR actPtr;	// aktuelle Position im EingabeFile
#endif // MSWIND

static char * FUNCTYPE dwskip (char *p);
static long FUNCTYPE xtoi (char *p);
static char *sgets (char *, short, char *);

#if defined(COMPRESS_PWD)
char temp[20];
char syscmd[120];
#endif

void FUNCTYPE replace_ext (char *name, char *new_ext);

#if defined(WIN32)
typedef INT (APIENTRY * LZOPENFILEPROC)(LPSTR, LPOFSTRUCT, WORD);
typedef LONG (APIENTRY * LZSSEEKPROC)(INT, LONG, INT);
typedef INT (APIENTRY * LZRREADPROC)(INT, LPSTR, INT);
typedef VOID (APIENTRY * LZCLOSEPROC)(INT);
#endif //WIN32

void FUNCTYPE setdwent (char *dwdfile) 
{
	if (dwdfile == NULL) return;

#if defined(MSWIND)
#if defined(WIN32)
// LZ32.DLL dynamisch binden
HINSTANCE hLZ32 = ::LoadLibrary (TEXT("LZ32.DLL"));

	if (NULL == hLZ32) return;

LZOPENFILEPROC pLZOpenFile = (LZOPENFILEPROC)GetProcAddress (hLZ32, TEXT("LZOpenFileA"));
LZSSEEKPROC pLZSeek = (LZSSEEKPROC)GetProcAddress (hLZ32, TEXT("LZSeek"));
LZRREADPROC pLZRead = (LZRREADPROC)GetProcAddress (hLZ32, TEXT("LZRead"));
LZCLOSEPROC pLZClose = (LZCLOSEPROC)GetProcAddress (hLZ32, TEXT("LZClose"));

	if (NULL == pLZOpenFile || NULL == pLZSeek ||
		NULL == pLZRead || NULL == pLZClose)
	{
		::FreeLibrary (hLZ32);
		return;
	}

	if (fh == -1) {
		strncpy (db_dwd_file, dwdfile, _MAX_PATH);
		replace_ext (db_dwd_file, PWD_EXTENSION);
		fh = pLZOpenFile (db_dwd_file, &of, OF_READ);
		if (fh >= 0) {
			FileLen = pLZSeek (fh, 0L, SEEK_END);
			pInFile = new char [FileLen+1];
			if (pInFile == NULL) {
				pLZClose (fh);
				::FreeLibrary (hLZ32);
				return;
			}
			memset (pInFile, '\0', (size_t)(FileLen+1));
			pLZSeek (fh, 0L, SEEK_SET);
			pLZRead (fh, pInFile, (int)FileLen);
			pLZClose (fh);
			fh = -1;

			::FreeLibrary (hLZ32);

		// Pointer Rücksetzen
			actPtr = pInFile;
		}
	} else
		actPtr = pInFile;
#else // WIN32
	if (fh == -1) {
		strncpy (db_dwd_file, dwdfile, _MAX_PATH);
		replace_ext (db_dwd_file, PWD_EXTENSION);
		fh = LZOpenFile (db_dwd_file, &of, OF_READ);
		if (fh >= 0) {
			FileLen = LZSeek (fh, 0L, SEEK_END);
			pInFile = new char [FileLen+1];
			memset (pInFile, '\0', (size_t)(FileLen+1));
			if (pInFile == NULL) {
				LZClose (fh);
				return;
			}
			LZSeek (fh, 0L, SEEK_SET);
			LZRead (fh, pInFile, (int)FileLen);
			LZClose (fh);
			fh = -1;
		// Pointer Rücksetzen
			actPtr = pInFile;
		}
	} else
		actPtr = pInFile;
#endif // WIN32
#else // DOS

        if (dwf == NULL) {
		strncpy (db_dwd_file, dwdfile, _MAX_PATH);
		strcat (db_dwd_file, PWD_EXTENSION);
#if defined(COMPRESS_PWD)
		strcpy (temp, ".\\aXXXXXX");
		tmpnam (temp);
		sprintf (syscmd, "expand %s %s > nul", db_dwd_file, temp);
		if (system (syscmd) < 0) {
//			db_error (S_SPAWN, RC_GETDWENT);
			return;
		}
		dwf = fopen (temp, "r");
#else
                dwf = fopen (db_dwd_file, "r");
#endif
        } else
                fseek (dwf, 0L, SEEK_SET);

#endif
}

#ifdef MSWIND
void FUNCTYPE replace_ext (char *name, char *new_ext) 
{
register char *cptr = &name[strlen (name)];

	while (cptr-- > name) {
		if (*cptr == '\\' || *cptr == ':') 
			break; 
		if (*cptr == '.') {
			*cptr = '\0';
			break;
		}
	}
	strcat (name, new_ext);
}

static char *sgets (char *Buff, short BuffSize, char *BegPtr) 
{
char *srcPtr = BegPtr;
char *destPtr = Buff;

	while (destPtr < Buff + BuffSize-1 && srcPtr < pInFile + FileLen && *srcPtr) {
		if (*srcPtr == '\n') {
			srcPtr++;
			break;
		}
		*destPtr++ = *srcPtr++;
	}
	*destPtr = '\0';
	if (srcPtr > pInFile + FileLen)
		return NULL;		// EOF

	actPtr = srcPtr;

return Buff;
}

#endif

void FUNCTYPE enddwent (void) 
{
#if defined(MSWIND)
	if (pInFile) {
		delete pInFile;
		pInFile = NULL;
	}
#else

        if (dwf != NULL) {
                fclose (dwf);
		dwf = NULL;
#if defined(COMPRESS_PWD)
		sprintf (syscmd, "compress %s %s > nul", temp, db_dwd_file);
		if (system (syscmd) < 0) {
//			db_error (S_SPAWN, RC_ENDDWENT);
			return;
		}
		remove (temp);
#endif
        }
#endif // MSWIND
}
 
static char * FUNCTYPE dwskip (register char *p) 
{
        while (*p && *p != ':')
                ++p;
        if (*p) *p++ = '\0';
        return (p);
}
 
struct dbpasswd * FUNCTYPE getdwent (void) 
{
register char *p;
 
#if defined(MSWIND)
	if (pInFile == NULL) return NULL;
	do {
		p = sgets (line, BUFSIZ, actPtr);
		if (p == NULL || *p == '\0') return NULL;
	} while (*p == '#');	// skip comment

#else

        if (dwf == NULL) return NULL;
        do {
                p = fgets (line, BUFSIZ, dwf);
                if (p == NULL) return (NULL);
        } while (*p == '#');    /* Kommentar ueberspringen */
#endif

        dbpasswd.dw_name = p;
        p = dwskip (p);
        dbpasswd.dw_passwd = p;
        p = dwskip (p);
        dbpasswd.dw_uid = atoi(p);
        p = dwskip (p);
	dbpasswd.dw_access = xtoi (p);
        p = dwskip (p);
        dbpasswd.dw_rw = xtoi (p);
        p = dwskip (p);
        dbpasswd.dw_comment = p;
        while (*p && *p != '\n') p++;
        *p = '\0';
 
return (&dbpasswd);
}
 
 
/* Konvertieren einer Binaerzahl (String) in int */
#if defined(WIN32)
#define __based(a)
#endif

extern "C" const char * __based(__segname("_CODE")) hexdigits = "0123456789abcdefABCDEF";
extern "C" const char __based(__segname("_CODE")) hexvalues[22] = 
			{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
			 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15 };
 
static long FUNCTYPE xtoi (register char *p) 
{
long result = 0L;
register char *cptr;
 
        if (*p == '0' && (*(p+1) == 'x' || *(p+1) == 'X'))
                p += 2; /* 0x... oder 0X... */
		while ((cptr = strchr (hexdigits, *p++)) != NULL)
		result = (result * 16) + hexvalues[cptr-hexdigits];
 
return result;
}


// Version für CompoundFiles
#if defined (MSWIND)

#include <resstrg.h>
#include <commonvu.hxx>

struct dbpasswd * FUNCTYPE GetPWDName (LPSTORAGE pIStorage, const char *pUser)
{
struct dbpasswd *pPwd = NULL;
LPSTREAM pIStream = NULL;
ResString resPWD (IDS_DBPWDSTREAM, 32);
HRESULT hr = pIStorage -> OpenStream (WideString(resPWD), 0, 
				      STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
				      0, &pIStream);
				      
	if (FAILED(hr)) return NULL;

// wenn kein User gegeben, dann ersten Eintrag liefern
	while ((pPwd = GetNextPWDEntry (pIStream)) && 
	       (pUser != NULL && strcmp (pUser, pPwd->dw_name)))
		;	// wenn User gegeben, solange bis User gefunden
	pIStream -> Release();	

return pPwd;
}

struct dbpasswd * FUNCTYPE GetNextPWDEntry (LPSTREAM pIStream)
{
// nächste Zeile einlesen
BYTE cb = '\0';
ULONG cbRead = 0;
char *pT = line;

	do {
		pIStream -> Read (&cb, sizeof(BYTE), &cbRead);
		if (cbRead == 0) return NULL;
		*pT++ = cb;		
	} while (cb != '\n');		
	*pT = '\0';		// letztes Zeichen
	
// Zeile auseinandernehmen
        dbpasswd.dw_name = line;
        pT = dwskip (line);
        dbpasswd.dw_passwd = pT;
        pT = dwskip (pT);
        dbpasswd.dw_uid = atoi(pT);
        pT = dwskip (pT);
	dbpasswd.dw_access = xtoi (pT);
        pT = dwskip (pT);
        dbpasswd.dw_rw = xtoi (pT);
        pT = dwskip (pT);
        dbpasswd.dw_comment = pT;
        while (*pT && *pT != '\n') pT++;
        *pT = '\0';
 
return &dbpasswd;
}

#endif // MSWIND

