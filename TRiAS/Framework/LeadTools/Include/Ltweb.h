#ifndef _LTWEB_H_
#define _LTWEB_H_

#include "ltkrn.h"
#include "ltfil.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

typedef struct tagNAMEVALUE
{
   char  *pszName;
   char  *pszValue;
} NAMEVALUE, L_FAR * pNAMEVALUE;

typedef HGLOBAL HINET;
typedef HINET  L_FAR * pHINET;

typedef FILETIME L_FILETIME; //Specifies a FILETIME structure containing the time the file was created

typedef struct tagFTPINFO
{
   LPVOID hSession;
	LPVOID hFtpConnection;
} FTPINFO, L_FAR * pFTPINFO;

typedef HGLOBAL HFTP;
typedef HFTP 	L_FAR * pHFTP;

typedef struct tagFILEDATA
{
    L_UINT     uFileAttributes; 
    L_FILETIME ftCreationTime; 
    L_FILETIME ftLastAccessTime; 
    L_FILETIME ftLastWriteTime; 
    L_UINT32   uFileSize; 
} FILEDATA, L_FAR *pFILEDATA;


typedef L_INT (pEXT_CALLBACK FTPBROWSECALLBACK)(L_CHAR L_FAR *pszFile, pFILEDATA pFileData, L_VOID L_FAR *pUserData);

#define FTP_FILE_ATTRIBUTE_ARCHIVE         FILE_ATTRIBUTE_ARCHIVE
#define FTP_FILE_ATTRIBUTE_COMPRESSED      FILE_ATTRIBUTE_COMPRESSED
#define FTP_FILE_ATTRIBUTE_DIRECTORY       FILE_ATTRIBUTE_DIRECTORY
#define FTP_FILE_ATTRIBUTE_ENCRYPTED       FILE_ATTRIBUTE_ENCRYPTED
#define FTP_FILE_ATTRIBUTE_HIDDEN          FILE_ATTRIBUTE_HIDDEN
#define FTP_FILE_ATTRIBUTE_NORMAL          FILE_ATTRIBUTE_NORMAL
#define FTP_FILE_ATTRIBUTE_OFFLINE         FILE_ATTRIBUTE_OFFLINE
#define FTP_FILE_ATTRIBUTE_READONLY        FILE_ATTRIBUTE_READONLY
#define FTP_FILE_ATTRIBUTE_REPARSE_POINT   FILE_ATTRIBUTE_REPARSE_POINT
#define FTP_FILE_ATTRIBUTE_SPARSE_FILE     FILE_ATTRIBUTE_SPARSE_FILE
#define FTP_FILE_ATTRIBUTE_SYSTEM          FILE_ATTRIBUTE_SYSTEM
#define FTP_FILE_ATTRIBUTE_TEMPORARY       FILE_ATTRIBUTE_TEMPORARY

#define SENDAS_ASCII    0
#define SENDAS_BINARY   1

#define HTTP_GET        0
#define HTTP_PUT        1
#define HTTP_POST       2

#define L_HTTP_STATUS_OK                  200 // request completed
#define L_HTTP_STATUS_CREATED             201 // object created, reason = new URI
#define L_HTTP_STATUS_ACCEPTED            202 // async completion (TBS)
#define L_HTTP_STATUS_PARTIAL             203 // partial completion
#define L_HTTP_STATUS_NO_CONTENT          204 // no info to return
#define L_HTTP_STATUS_RESET_CONTENT       205 // request completed, but clear form
#define L_HTTP_STATUS_PARTIAL_CONTENT     206 // partial GET furfilled

#define L_HTTP_STATUS_AMBIGUOUS           300 // server couldn't decide what to return
#define L_HTTP_STATUS_MOVED               301 // object permanently moved
#define L_HTTP_STATUS_REDIRECT            302 // object temporarily moved
#define L_HTTP_STATUS_REDIRECT_METHOD     303 // redirection w/ new access method
#define L_HTTP_STATUS_NOT_MODIFIED        304 // if-modified-since was not modified
#define L_HTTP_STATUS_USE_PROXY           305 // redirection to proxy, location header specifies proxy to use
#define L_HTTP_STATUS_REDIRECT_KEEP_VERB  307 // HTTP/1.1: keep same verb

#define L_HTTP_STATUS_BAD_REQUEST         400 // invalid syntax
#define L_HTTP_STATUS_DENIED              401 // access denied
#define L_HTTP_STATUS_PAYMENT_REQ         402 // payment required
#define L_HTTP_STATUS_FORBIDDEN           403 // request forbidden
#define L_HTTP_STATUS_NOT_FOUND           404 // object not found
#define L_HTTP_STATUS_BAD_METHOD          405 // method is not allowed
#define L_HTTP_STATUS_NONE_ACCEPTABLE     406 // no response acceptable to client found
#define L_HTTP_STATUS_PROXY_AUTH_REQ      407 // proxy authentication required
#define L_HTTP_STATUS_REQUEST_TIMEOUT     408 // server timed out waiting for request
#define L_HTTP_STATUS_CONFLICT            409 // user should resubmit with more info
#define L_HTTP_STATUS_GONE                410 // the resource is no longer available
#define L_HTTP_STATUS_LENGTH_REQUIRED     411 // the server refused to accept request w/o a length
#define L_HTTP_STATUS_PRECOND_FAILED      412 // precondition given in request failed
#define L_HTTP_STATUS_REQUEST_TOO_LARGE   413 // request entity was too large
#define L_HTTP_STATUS_URI_TOO_LONG        414 // request URI too long
#define L_HTTP_STATUS_UNSUPPORTED_MEDIA   415 // unsupported media type

#define L_HTTP_STATUS_SERVER_ERROR        500 // internal server error
#define L_HTTP_STATUS_NOT_SUPPORTED       501 // required not supported
#define L_HTTP_STATUS_BAD_GATEWAY         502 // error response received from gateway
#define L_HTTP_STATUS_SERVICE_UNAVAIL     503 // temporarily overloaded
#define L_HTTP_STATUS_GATEWAY_TIMEOUT     504 // timed out waiting for gateway
#define L_HTTP_STATUS_VERSION_NOT_SUP     505 // HTTP version not supported

// ftp functions

L_INT EXT_FUNCTION L_InetFtpConnect(L_CHAR L_FAR *pszServer,L_INT iPort,L_CHAR L_FAR *pszUserName,
												L_CHAR L_FAR *pszPassword,pHFTP pFtp);
L_INT EXT_FUNCTION L_InetFtpDisConnect(HFTP hFtp);
L_INT EXT_FUNCTION L_InetFtpSendFile(HFTP hFtp,L_CHAR L_FAR *pszLocal,L_CHAR L_FAR *pszRemote,L_UINT uSendAs);
L_INT EXT_FUNCTION L_InetFtpChangeDir(HFTP hFtp,L_CHAR L_FAR *pszDirectory);
L_INT EXT_FUNCTION L_InetFtpGetFile(HFTP hFtp, L_CHAR L_FAR *pszRemote,	L_CHAR L_FAR *pszLocal,
	                                 L_BOOL bOverwrite, L_UINT uSendAs);
L_INT EXT_FUNCTION L_InetFtpRenameFile(HFTP hFtp, L_CHAR L_FAR *pszOld, L_CHAR L_FAR *pszNew);
L_INT EXT_FUNCTION L_InetFtpDeleteFile(HFTP hFtp, L_CHAR L_FAR *pszRemote);
L_INT EXT_FUNCTION L_InetFtpCreateDir(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir);
L_INT EXT_FUNCTION L_InetFtpDeleteDir(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir);
L_INT EXT_FUNCTION L_InetFtpGetCurrentDir(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir, L_UINT32 ulSize);
L_INT EXT_FUNCTION L_InetFtpSendBitmap(HFTP hFtp, pBITMAPHANDLE pBitmap, L_INT nFormat, 
	                                    L_INT nBitsPerPixel, L_INT nQFactor, pSAVEFILEOPTION pSaveOptions,
                                       L_CHAR L_FAR *pszRemote, L_UINT uSendAs);
L_INT EXT_FUNCTION L_InetFtpBrowseDir(HFTP hFtp, L_CHAR L_FAR *pszSearch,FTPBROWSECALLBACK pfnCallback,
                                                                L_VOID L_FAR *pData);

// http functions

L_INT EXT_FUNCTION L_InetHttpConnect(L_CHAR L_FAR *pszServer,L_INT iPort,L_CHAR L_FAR *pszUserName,
                                     L_CHAR L_FAR *pszPassword,pHINET pHttp);
L_INT EXT_FUNCTION L_InetHttpDisconnect(HINET hHttp);
L_INT EXT_FUNCTION L_InetHttpOpenRequest(HINET hHttp,L_UINT uType,L_CHAR L_FAR *pszTarget,
                                         L_CHAR L_FAR *pszReferer,L_CHAR L_FAR *pszVersion,
                                         L_UINT32 dwReserved);
L_INT EXT_FUNCTION L_InetHttpOpenRequestEx(HINET hHttp,L_UINT uType,L_CHAR L_FAR *pszTarget,
                                           L_CHAR L_FAR *pszReferer,L_CHAR L_FAR *pszVersion,
                                           L_UINT32 dwReserved, L_UINT32 uFlags);
L_INT EXT_FUNCTION L_InetHttpCloseRequest(HINET hHttp);
L_INT EXT_FUNCTION L_InetHttpSendRequest(HINET hHttp,L_CHAR L_FAR *pszHeader,L_UINT32 ulHeaderSize,
                                         L_CHAR L_FAR *pszOptional,L_UINT32 ulOptionalSize);
L_INT EXT_FUNCTION L_InetHttpSendBitmap(HINET hHttp,pBITMAPHANDLE pBitmap,L_INT nFormat,
                              L_INT nBitsPerPixel,L_INT nQFactor,
                              L_CHAR L_FAR *pszContentType,pNAMEVALUE pNameValue,
                              pSAVEFILEOPTION pSaveOptions);
L_INT EXT_FUNCTION L_InetHttpSendData(HINET hHttp,L_CHAR L_FAR *pData, L_UINT32 uSize,
                             L_CHAR L_FAR *pszContentType,pNAMEVALUE pNameValue);
L_INT EXT_FUNCTION L_InetHttpSendForm(HINET hHttp,pNAMEVALUE pNameValue,L_UINT uCount);
L_INT EXT_FUNCTION L_InetHttpGetResponse(HINET hHttp,L_CHAR L_FAR *pszData,L_UINT32 L_FAR *ulSize);
L_INT EXT_FUNCTION L_InetHttpGetServerStatus(HINET hHttp,L_UINT L_FAR *uStatus);


#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif
