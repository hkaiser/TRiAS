//==============================================================================
//
//  LTDic : Header file.
//
//  Copyright (C) 1991-2000 LEAD Technologies, Inc.
//  All rights reserved.
//
//==============================================================================

#ifndef LTDIC_H_INCLUDED
#define LTDIC_H_INCLUDED

//============= INCLUDES =======================================================

//============= CONSTANTS ======================================================

#ifdef __cplusplus
   #ifdef _LEAD_DICOM_NO_EXP_IMP
      #define  DICOM_EXPORT      
   #else
   #ifdef _LEAD_DICOM_
      #if defined(FOR_LINUX) || defined(FOR_LIB)
         #define  DICOM_EXPORT 
      #else
         #define  DICOM_EXPORT __declspec(dllexport)
      #endif
   #else
      #if defined(FOR_LINUX) || defined(FOR_LIB)
         #define  DICOM_EXPORT 
      #else
         #define  DICOM_EXPORT __declspec(dllimport)
      #endif
   #endif   
   #endif //_LEAD_DICOM_NO_EXP_IMP

#endif

#include "ltfil.h"
#if !defined(_WIN32_WCE)
#include "ltann.h"
#endif /* _WIN32_WCE */

#define DICOM_SUCCESS                            0
#define DICOM_ERROR_LOCKED                       1
#define DICOM_ERROR_MEMORY                       2
#define DICOM_ERROR_OPEN                         3
#define DICOM_ERROR_READ                         4
#define DICOM_ERROR_WRITE                        5
#define DICOM_ERROR_SEEK                         6
#define DICOM_ERROR_END                          7
#define DICOM_ERROR_FORMAT                       8
#define DICOM_ERROR_PARAMETER                    9
#define DICOM_ERROR_IMAGE                       10
#define DICOM_ERROR_COMPRESSION                 11
#define DICOM_ERROR_PHOTOMETRIC                 12
#define DICOM_ERROR_CONVERSION                  13
#define DICOM_ERROR_RANGE                       14
#define DICOM_ERROR_BITSPERPIXEL                15
#define DICOM_ERROR_QFACTOR                     16
#define DICOM_ERROR_ELEMENT_LENGTH_ODD          100
#define DICOM_ERROR_DICOMDIR_FOLDER             200
#define DICOM_ERROR_FILE                        201
#define DICOM_ERROR_FILEID                      202
#define DICOM_ERROR_J2K_LOCKED                  203


#define DICOM_ERROR_PDU_TYPE                    17
#define DICOM_ERROR_PDU_LENGTH                  18
#define DICOM_ERROR_PDU_ID                      19

#define DICOM_ERROR_NET_FAILURE                 29
#define DICOM_ERROR_NET_ACCESS                  30  // The address is a broadcast address
#define DICOM_ERROR_NET_ADDRESS_IN_USE          31  // The address is already in use
#define DICOM_ERROR_NET_ADDRESS_NOT_AVAILABLE   32  // The address is not available from the local computer
#define DICOM_ERROR_NET_ADDRESS_NOT_SUPPORTED   33  // The address family is not supported
#define DICOM_ERROR_NET_CONNECTION_ABORTED      34  // The virtual circuit was aborted
#define DICOM_ERROR_NET_CONNECTION_REFUSED      35  // The attempt to connect was forcefully rejected
#define DICOM_ERROR_NET_CONNECTION_RESET        36  // The virtual circuit was reset by the remote side
#define DICOM_ERROR_NET_DESTINATION_REQUIRED    37  // A destination address is required
#define DICOM_ERROR_NET_ARGUMENT_INCORRECT      38  // The namelen argument is incorrect
#define DICOM_ERROR_NET_IN_PROGRESS             39  // A blocking operation is in progress
#define DICOM_ERROR_NET_BLOCKING_CANCELED       40  // The blocking call was canceled
#define DICOM_ERROR_NET_INVALID                 41  // The socket has not been bound with bind
#define DICOM_ERROR_NET_IS_CONNECTED            42  // The socket is already connected
#define DICOM_ERROR_NET_NO_MORE_FILE            43  // No more file descriptors are available
#define DICOM_ERROR_NET_MESSAGE_SIZE            44  // The datagram is larger than the maximum supported
#define DICOM_ERROR_NET_DOWN                    45  // The network subsystem has failed
#define DICOM_ERROR_NET_RESET                   46  // The connection must be reset
#define DICOM_ERROR_NET_UN_REACH                47  // The network can't be reached from this host at this time
#define DICOM_ERROR_NET_NO_BUFFERS              48  // No buffer space is available
#define DICOM_ERROR_NET_NOT_CONNECTED           49  // The socket is not connected
#define DICOM_ERROR_NET_NOT_SOCKET              50  // The descriptor is not a socket
#define DICOM_ERROR_NET_OPERATION_NOT_SUPPORTED 51  // The type does not support connection-oriented service
#define DICOM_ERROR_NET_PROTOCOL_NOT_SUPPORTED  52  // The specified protocol is not supported
#define DICOM_ERROR_NET_PROTOCOL_TYPE           53  // The specified protocol is the wrong type
#define DICOM_ERROR_NET_SHUTDOWN                54  // The socket has been shut down
#define DICOM_ERROR_NET_SOCKET_NOT_SUPPORTED    55  // The type is not supported in this address family
#define DICOM_ERROR_NET_TIME_OUT                56  // Attempt to connect timed out without establishing a connection
#define DICOM_ERROR_NET_WOULD_BLOCK             57  // The socket is marked as nonblocking and the requested operation would block
#define DICOM_ERROR_NET_HOST_NOT_FOUND          58  // Authoritative Answer Host not found
#define DICOM_ERROR_NET_NO_DATA                 59  // Valid name, no data record of requested type
#define DICOM_ERROR_NET_NO_RECOVERY             60  // Nonrecoverable errors
#define DICOM_ERROR_NET_NOT_INITIALISED         61  // The system was not initialized
#define DICOM_ERROR_NET_SYSTEM_NOT_READY        62  // Not ready for network communication
#define DICOM_ERROR_NET_TRY_AGAIN               63  // Non-Authoritative Host not found, or server faild
#define DICOM_ERROR_NET_VERSION_NOT_SUPPORTED   64  // The version requested is not provided by this implementation
// added for secure functionality
#define DICOM_ERROR_NET_SECURITY_BREACH         65  // There is an cryptographic error. 
      // Call LDicomNet::GetStatusISCL or LDicomNet::GetStatusTLS for the description of internal status
      // before error, and LDicomNet::GetErrorSecure for the description of the error
#define DICOM_ERROR_TLS                         66  // TLS internal error
#define DICOM_ERROR_SECURITY_LOCKED             67  // DICOM Security Features are locked
#define DICOM_ERROR_TLS_DLL_NOT_LOADED          68  // TLS and/or CRY DLL not loaded
#define DICOM_ERROR_BAD_SECURE_MODE             69  // if I do ISCL operations on TLS objects
#define DICOM_ERROR_ANN                         70
#define DICOM_ERROR_ANN_LOCKED                  71  // Annotation support is locked
#define DICOM_ERROR_ANN_MISSING                 72  // Annotation dll is missing
#define DICOM_ERROR_TAG_ALREADY_EXISTS          73  // LEAD private creator element already exists
#define DICOM_ERROR_ANN_NO_EXIST                74  // Requested annotation file or page does not exist


//For extended debug functionality
#define DEBUG_MODE_ONSEND_SHOW_EXTENDED_INFO    0x00000001
#define DEBUG_MODE_ONRECEIVE_SHOW_EXTENDED_INFO 0x00000002


// Added for 64-bit types - or 8 bytes values, used in encryption, as keys etc
// and for TLS primitive data
typedef unsigned __int64 L_UINT64;
typedef __int64 L_INT64;
struct ssl_st;
typedef struct ssl_st SSL;

struct ssl_ctx_st;
typedef struct ssl_ctx_st SSL_CTX;

struct x509_store_st;
typedef struct x509_store_ctx_st X509_STORE_CTX;
typedef int (*TLS_CERT_VERIFY_CALLBACK)(int ok,X509_STORE_CTX *ctx);

// end of added for 64bit types and TLS primitives


// added for secure extension

#define DICOM_SECURE_NONE  0xABCD0000
#define DICOM_SECURE_ISCL  0xABCD0001
#define DICOM_SECURE_TLS   0xABCD0002

// end of added for secure extension

// added for TLS complance

enum _L_CIPHERSUITE
{
   TLS_DHE_RSA_WITH_DES_CBC_SHA = 0x12,
   TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA = 0x13,  // mandatory standard
};

typedef enum _L_CIPHERSUITE L_CIPHERSUITE;

enum _L_ENCRYPTION_METHOD
{
   L_CRYPT_DES   = 0x01,
   L_CRYPT_3DES  = 0x02
};

typedef enum _L_ENCRYPTION_METHOD L_ENCRYPTION_METHOD;

enum _L_MAC_METHOD
{
   L_MAC_SHA1  = 0x10
};

typedef enum _L_MAC_METHOD L_MAC_METHOD;

enum _L_MUTUAL_AUTH_METHOD
{
   L_MUTUALAUTH_RSA = 0x20
};

typedef enum _L_MUTUAL_AUTH_METHOD L_MUTUAL_AUTH_METHOD;

enum _L_KEY_EXCHANGE_METHOD
{
   L_KEYEXCHANGE_RSA_SIGNED_DHE = 0x40
};

typedef enum _L_KEY_EXCHANGE_METHOD L_KEY_EXCHANGE_METHOD;


#define DICOM_ERROR_TLS_OK                      0
#define DICOM_ERROR_TLS_CLOSE_NOTIFY            128
#define DICOM_ERROR_TLS_UNEXPECTED_MESSAGE      129
#define DICOM_ERROR_TLS_BAD_RECORD_MAC          130
#define DICOM_ERROR_TLS_DECRYPT_FAILED          131
#define DICOM_ERROR_TLS_RECORD_OVERFLOW         132
#define DICOM_ERROR_TLS_DECOMPRESSION_FAILURE   133
#define DICOM_ERROR_TLS_HANDSHAKE_FAILURE       134
#define DICOM_ERROR_TLS_BAD_CERTIFICATE         135
#define DICOM_ERROR_TLS_UNSUPPORTED_CERTIFICATE 136
#define DICOM_ERROR_TLS_CERTIFICATE_REVOKED     137
#define DICOM_ERROR_TLS_CERTIFICATE_EXPIRED     138
#define DICOM_ERROR_TLS_CERTIFICATE_UNKNOWN     139
#define DICOM_ERROR_TLS_ILLEGAL_PARAMETER       140
#define DICOM_ERROR_TLS_UNKNOWN_CA              141
#define DICOM_ERROR_TLS_ACCESS_DENIED           142
#define DICOM_ERROR_TLS_DECODE_ERROR            143
#define DICOM_ERROR_TLS_DECRYPT_ERROR           144
#define DICOM_ERROR_TLS_EXPORT_RESTRICTION      145
#define DICOM_ERROR_TLS_PROTOCOL_VERSION        146
#define DICOM_ERROR_TLS_INSUFFICIENT_SECURITY   147
#define DICOM_ERROR_TLS_INTERNAL_ERROR          148
#define DICOM_ERROR_TLS_USER_CANCELED           149
#define DICOM_ERROR_TLS_NO_RENEGOTIATION        150
#define DICOM_ERROR_TLS_NO_KEEPALIVE            151
#define DICOM_ERROR_TLS_CLOSED_CONTROLLED       152

#ifndef FOR_BORLAND
typedef enum _DICOM_TLS_ERRORS DICOM_TLS_ERRORS;
#endif

#define L_TLS_FILETYPE_PEM    1
#define L_TLS_FILETYPE_ASN1   2

// use either SSL_VERIFY_NONE or SSL_VERIFY_PEER, the last 2 options
// are 'ored' with SSL_VERIFY_PEER if they are desired
#define L_TLS_VERIFY_NONE			0x00
#define L_TLS_VERIFY_PEER			0x01
#define L_TLS_VERIFY_FAIL_IF_NO_PEER_CERT	0x02
#define L_TLS_VERIFY_CLIENT_ONCE		0x04

extern L_INT nVerifyCertDepth;
extern L_INT nVerifyCertError;
// end of added for TLS


// added for ISCL compliance 

#define DC_MSG_IN_QUEUE    0xDC00

#define DESCBC_CHAIN_IVEC_OVER_SIGNATURE  1
#define DESCBC_CHAIN_IVEC_OVER_MESSAGES   1


// Magical constants:


#define DICOM_ISCL_MAX_PACKET_SIZE        (8160)     // set with manual values
#define DICOM_ISCL_MAX_MESSAGE_SIZE       (1048576)   // set with manual values


      // values specified in ISCL standard
#define DICOM_ISCL_ACK                    0x00000000
#define DICOM_ISCL_NAK                    0xFFFFFFFF

#define DICOM_ISCL_MUTUAL_AUTH_3P4W       0x00000000  // three pass four way mutual auth

#define DICOM_ISCL_ENCRYPT_NONE           0x00000000
#define DICOM_ISCL_ENCRYPT_DESCBC         0x00001212

#define DICOM_ISCL_MAC_NONE               0x00000000
#define DICOM_ISCL_MAC_MD5                0x00001441
#define DICOM_ISCL_MAC_DESMAC             0x00004001

#define DICOM_ISCL_LINE_CONNECTION_CHECK_RQ     0x00110001  // RQ - request, RP - response
#define DICOM_ISCL_LINE_CONNECTION_CHECK_RP     0x00110003
#define DICOM_ISCL_MUTUAL_AUTH_RQ               0x00120001
#define DICOM_ISCL_MUTUAL_AUTH_RP               0x00120003
#define DICOM_ISCL_MUTUAL_AUTH_PASS1_NOTIF      0x00130002
#define DICOM_ISCL_MUTUAL_AUTH_PASS2_NOTIF      0x00140002
#define DICOM_ISCL_MUTUAL_AUTH_PASS3_NOTIF      0x00150002
#define DICOM_ISCL_MUTUAL_AUTH_COMPLETION_NOTIF 0x00160002
#define DICOM_ISCL_MESSAGE_TRANSMISSION_RQ      0x00200001
#define DICOM_ISCL_MESSAGE_TRANSMISSION_RP      0x00200003
#define DICOM_ISCL_RNDNO_FOR_SESSION_KEY_RQ     0x00210001
#define DICOM_ISCL_RNDNO_FOR_SESSION_KEY_RP     0x00210003
#define DICOM_ISCL_MESSAGE_TRANSMISSION_NOTIF   0x00200002
#define DICOM_ISCL_MAC_TRANSMISSION_NOTIF       0x00230002
#define DICOM_ISCL_THROUGH_MODE_TRANSMISSION_NOTIF 0x00260002
#define DICOM_ISCL_LINE_DISCONNECTION_RQ        0x00FF0001
#define DICOM_ISCL_LINE_DISCONNECTION_RP        0x00FF0003


enum DICOM_ISCLAuthKeyPair
{
   DICOM_ISCL_AUTH_KEY_PAIR1 = 0x00000001,
   DICOM_ISCL_AUTH_KEY_PAIR2 = 0x00000002,
   DICOM_ISCL_AUTH_KEY_PAIR3 = 0x00000003,
   DICOM_ISCL_AUTH_KEY_PAIR4 = 0x00000004,
   DICOM_ISCL_AUTH_KEY_PAIR5 = 0x00000005,
   DICOM_ISCL_AUTH_KEY_PAIR6 = 0x00000006,
   DICOM_ISCL_AUTH_KEY_PAIR7 = 0x00000007,
   DICOM_ISCL_AUTH_KEY_PAIR8 = 0x00000008
};

enum DICOM_ISCLCryptKeyPair
{
   DICOM_ISCL_CRYPT_KEY_PAIR1 = 0x00000001,
   DICOM_ISCL_CRYPT_KEY_PAIR2 = 0x00000002,
   DICOM_ISCL_CRYPT_KEY_PAIR3 = 0x00000003,
   DICOM_ISCL_CRYPT_KEY_PAIR4 = 0x00000004,
   DICOM_ISCL_CRYPT_KEY_PAIR5 = 0x00000005,
   DICOM_ISCL_CRYPT_KEY_PAIR6 = 0x00000006,
   DICOM_ISCL_CRYPT_KEY_PAIR7 = 0x00000007,
   DICOM_ISCL_CRYPT_KEY_PAIR8 = 0x00000008,
   DICOM_ISCL_UNIQUE_SESSION_KEYS = 0x00000010
};

      // header of ISCL messages
struct DICOM_ISCLMessageHeader
{
   L_UINT32 Indicator;    // not used
   L_UINT32 MessageId;    // type of message
   L_UINT32 nDataLength;  // number of bytes in message (excluding header)
   L_UINT32 Option;       // options belonging to the message block
   L_UINT32 timeStamp;    // not used
   L_UINT32 nErrNo;       // not used
   L_UINT32 stuff1, stuff2;  // to align msg header to 32 bytes, not used
};


#define DICOM_ERROR_ISCL_OK                      0 // start of ISCL errors
#define DICOM_ERROR_ISCL_BAD_OPTION             100 // option not expected or unknown
#define DICOM_ERROR_ISCL_BAD_LENGTH             101 // the length of the message differ of the expected length
#define DICOM_ERROR_ISCL_LOCAL_ICCARD           102 // local error on Id card
#define DICOM_ERROR_ISCL_REMOTE_ICCARD          103 // error on Id card level at peer
#define DICOM_ERROR_ISCL_BAD_MSGID              104 // message id not expected or unknown
#define DICOM_ERROR_ISCL_BAD_VERSION            105 // not MEDIS-ISCL V1.00
#define DICOM_ERROR_ISCL_BAD_MUTUAL_AUTH_METHOD 106 // mutual auth not 3pass 4way
#define DICOM_ERROR_ISCL_BAD_COMMBLOCK_LENGTH   107 // if the comm block length is too big
#define DICOM_ERROR_ISCL_RECEIVED_NAK           108 // when the peer sent option = NAK in general cases, there are some special cases
#define DICOM_ERROR_ISCL_MSG_TRANSMISSION       109 // bad encryption method or MAC method
#define DICOM_ERROR_ISCL_PEER_SMALL_LENGTH      110 // message length of the peer is too small
#define DICOM_ERROR_ISCL_LOCAL_SMALL_LENGTH     111 // peer want to send a message bigger than local MaxMessageLength
#define DICOM_ERROR_ISCL_DECRYPT                112 // error during decryption - decryption generate bad result
#define DICOM_ERROR_ISCL_BAD_MAC                113 // wrong message authentication code
#define DICOM_ERROR_ISCL_RND_NO_FOR_SESSION_KEY_EXPECTED 114  // only when the receiver expect to receive a "Random number for session key" request
                                          // when appears, the sender must be set to "SetSecurity(DICOM_ISCL_UNIQUE_SESSION_KEYS)"
#define DICOM_ERROR_ISCL_PEER_REFUSE_CLOSE      115 // when the peer does not accept the closing of connection


// end of added for ISCL compliance


//============= TYPES ==========================================================

//============= VARIABLES ======================================================

//============= CLASS ==========================================================

#define DICOM_FILE_OPEN       0x0000
#define DICOM_FILE_CREATE     0x0001
#define DICOM_FILE_READ       0x0002
#define DICOM_FILE_WRITE      0x0004
#define DICOM_FILE_TEMPORARY  0x0008
#define DICOM_FILE_MEMORY     0x0010
#define DICOM_FILE_REDIRECT   0x0020
#define DICOM_FILE_CLOSE      0x0040
#define DICOM_FILE_DELETE     0x0080

#define DICOM_FILE_BEGIN      0
#define DICOM_FILE_CURRENT    1
#define DICOM_FILE_END        2

#ifdef __cplusplus

class DICOM_EXPORT LDicomFile
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   LDicomFile();
   ~LDicomFile();

   L_BOOL   Open      (L_TCHAR *pszName, L_UINT16 nMode);
   L_VOID   Close     (L_BOOL bComplete);
   L_BOOL   Read      (L_VOID *pBuffer, L_UINT32 nLength);
   L_BOOL   Write     (L_VOID *pBuffer, L_UINT32 nLength);
   L_BOOL   Seek      (L_INT32 nOffset, L_UINT16 nWhere);
   L_UINT32 Tell      ();
   L_VOID   SetHandle (L_INT hFile, L_UINT16 nMode);

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
private:
   L_TCHAR   m_szName[_MAX_PATH];
   L_INT     m_hFile;
   L_UINT16  m_nMode;
   L_UINT32  m_nLength;
   L_INT32   m_nOffset;
   L_CHAR   *m_pBuffer;
};

#endif

//============= CLASS ==========================================================

#define GENERICLINK  pDICOMLINK pParent;     \
                     pDICOMLINK pFirstChild; \
                     pDICOMLINK pLastChild;  \
                     pDICOMLINK pPrev;       \
                     pDICOMLINK pNext;       \

typedef struct _DICOMLINK *pDICOMLINK;

#ifdef __cplusplus

class DICOM_EXPORT LDicomTree
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   LDicomTree();
   ~LDicomTree();

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   pDICOMLINK  Insert    (pDICOMLINK pNeighbor, L_UINT32 nSize, L_UINT16 nFlags);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   L_VOID      Delete    (pDICOMLINK pLink);

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   pDICOMLINK  GetRoot   (pDICOMLINK pLink);
   pDICOMLINK  GetParent (pDICOMLINK pLink);
   pDICOMLINK  GetChild  (pDICOMLINK pLink);
   pDICOMLINK  GetFirst  (pDICOMLINK pLink, L_BOOL bTree);
   pDICOMLINK  GetLast   (pDICOMLINK pLink, L_BOOL bTree);
   pDICOMLINK  GetPrev   (pDICOMLINK pLink, L_BOOL bTree);
   pDICOMLINK  GetNext   (pDICOMLINK pLink, L_BOOL bTree);
   L_UINT32    GetLevel  (pDICOMLINK pLink);
   L_UINT32    GetCount  (pDICOMLINK pLink, L_BOOL bTree);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   pDICOMLINK  FindIndex (pDICOMLINK pLink, L_BOOL bTree, L_UINT32 nIndex);
   L_BOOL      Exists    (pDICOMLINK pLink);
   pDICOMLINK  Verify    ();

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
protected:
   pDICOMLINK m_pFirstChild;
   pDICOMLINK m_pLastChild;
};

#endif

#ifdef __cplusplus
class DICOM_EXPORT LDicomTreeEx : public LDicomTree
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   LDicomTreeEx();
   ~LDicomTreeEx();
   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   pDICOMLINK  Insert    (pDICOMLINK pNeighbor, L_UINT32 nSize, L_UINT16 nFlags);
   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   L_VOID      Delete    (pDICOMLINK pLink);
};
#endif

//============= CLASS ==========================================================

#define VR_AE   0x4145U    // Application Entity
#define VR_AS   0x4153U    // Age String
#define VR_AT   0x4154U    // Attribute Tag
#define VR_CS   0x4353U    // Code String
#define VR_DA   0x4441U    // Date
#define VR_DS   0x4453U    // Decimal String
#define VR_DT   0x4454U    // Date Time
#define VR_FD   0x4644U    // Floating Point Double
#define VR_FL   0x464CU    // Floating Point Single
#define VR_IS   0x4953U    // Integer String
#define VR_LO   0x4C4FU    // Long String
#define VR_LT   0x4C54U    // Long Text
#define VR_OB   0x4F42U    // Other Byte String
#define VR_OW   0x4F57U    // Other Word String
#define VR_PN   0x504EU    // Person Name
#define VR_SH   0x5348U    // Short String
#define VR_SL   0x534CU    // Signed Long
#define VR_SQ   0x5351U    // Sequence of Items
#define VR_SS   0x5353U    // Signed Short
#define VR_ST   0x5354U    // Short Text
#define VR_TM   0x544DU    // Time
#define VR_UI   0x5549U    // Unique Identifier
#define VR_UL   0x554CU    // Unsigned Long
#define VR_UN   0x554EU    // Unknown
#define VR_US   0x5553U    // Unsigned Short
#define VR_UT   0x5554U    // Unlimited Text
#define VR_OF   0x4F46U    // Other Float Strings

enum
{
   VR_FIXED = 0,           // DICOMVR.nLength bytes fixed
   VR_MAXIMUM,             // DICOMVR.nLength bytes maximum
   VR_MAXIMUM_GROUP,       // DICOMVR.nLength maximum per component group
   VR_ANY,                 // DICOMVR.nLength any length valid for any of the other DICOM Value Representations
   VR_NOT_APPLICABLE,      // DICOMVR.nLength not applicable
   VR_MAX,
};

#define VR_BINARY  0x0100  // Binary value
#define VR_STRING  0x0200  // String value (The character '\' is used as the delimiter between values for multiple data elements)
#define VR_TEXT    0x0400  // Text value (Data Elements with this VR shall not be multi-valued)

//typedef struct _DICOMVR DICOMVR, *pDICOMVR;
typedef struct _DICOMVR
{
   GENERICLINK             // Reserved - internally used only

   L_UINT16  nCode;        // Code (VR_AE, VR_AS, ...)
   L_CHAR   *pszName;      // Name ("Application Entity", "Age String", ...)
   L_UINT32  nLength;      // Length
   L_UINT16  nRestrict;    // Restriction applied to the length
   L_UINT16  nUnitSize;    // The size for the smallest item
} DICOMVR, *pDICOMVR;

#ifdef __cplusplus

class DICOM_EXPORT LDicomVR
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   static L_VOID   Default   ();

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   static pDICOMVR Insert    (L_UINT16 nCode, L_CHAR *pszName, L_UINT32 nLength, L_UINT16 nRestrict, L_UINT16 nUnitSize);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   static pDICOMVR Delete    (pDICOMVR pVR);
   static L_VOID   Reset     ();

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   static pDICOMVR GetFirst  ();
   static pDICOMVR GetLast   ();
   static pDICOMVR GetPrev   (pDICOMVR pVR);
   static pDICOMVR GetNext   (pDICOMVR pVR);
   static L_UINT32 GetCount  ();
   static L_BOOL   Exists    (pDICOMVR pVR);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   static pDICOMVR Find      (L_UINT16 nCode);
   static pDICOMVR FindIndex (L_UINT32 nIndex);

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------
   static L_BOOL   SetName   (pDICOMVR pVR, L_CHAR *pszName);

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
private:
   static LDicomTreeEx m_InfoVR;
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

//---------------------------------------------------------------------------
// Initializing Functions
//---------------------------------------------------------------------------
L_VOID   EXT_FUNCTION L_DicomDefaultVR   ();

//---------------------------------------------------------------------------
// Insertion Functions
//---------------------------------------------------------------------------
pDICOMVR EXT_FUNCTION L_DicomInsertVR    (L_UINT16 nCode, L_CHAR *pszName, L_UINT32 nLength, L_UINT16 nRestrict, L_UINT16 nUnitSize);

//---------------------------------------------------------------------------
// Deletion Functions
//---------------------------------------------------------------------------
pDICOMVR EXT_FUNCTION L_DicomDeleteVR    (pDICOMVR pVR);
L_VOID   EXT_FUNCTION L_DicomResetVR     ();

//---------------------------------------------------------------------------
// Iteration Functions
//---------------------------------------------------------------------------
pDICOMVR EXT_FUNCTION L_DicomGetFirstVR  ();
pDICOMVR EXT_FUNCTION L_DicomGetLastVR   ();
pDICOMVR EXT_FUNCTION L_DicomGetPrevVR   (pDICOMVR pVR);
pDICOMVR EXT_FUNCTION L_DicomGetNextVR   (pDICOMVR pVR);
L_UINT32 EXT_FUNCTION L_DicomGetCountVR  ();
L_BOOL   EXT_FUNCTION L_DicomExistsVR    (pDICOMVR pVR);

//---------------------------------------------------------------------------
// Searching Functions
//---------------------------------------------------------------------------
pDICOMVR EXT_FUNCTION L_DicomFindVR      (L_UINT16 nCode);
pDICOMVR EXT_FUNCTION L_DicomFindIndexVR (L_UINT32 nIndex);

//---------------------------------------------------------------------------
// Modification Functions
//---------------------------------------------------------------------------
L_BOOL   EXT_FUNCTION L_DicomSetNameVR   (pDICOMVR pVR, L_CHAR *pszName);

#ifdef __cplusplus
};
#endif

//============= CLASS ==========================================================

#define UID_MAX_SIZE   64

#define UID_VERIFICATION_CLASS                                     "1.2.840.10008.1.1"
#define UID_IMPLICIT_VR_LITTLE_ENDIAN                              "1.2.840.10008.1.2"
#define UID_EXPLICIT_VR_LITTLE_ENDIAN                              "1.2.840.10008.1.2.1"
#define UID_DEFLATED_EXPLICIT_VR_LITTLE_ENDIAN                     "1.2.840.10008.1.2.1.99"
#define UID_EXPLICIT_VR_BIG_ENDIAN                                 "1.2.840.10008.1.2.2"
#define UID_JPEG_BASELINE_1                                        "1.2.840.10008.1.2.4.50"
#define UID_JPEG_EXTENDED_2_4                                      "1.2.840.10008.1.2.4.51"
#define UID_JPEG_EXTENDED_3_5                                      "1.2.840.10008.1.2.4.52"
#define UID_JPEG_SPECTRAL_NONHIER_6_8                              "1.2.840.10008.1.2.4.53"
#define UID_JPEG_SPECTRAL_NONHIER_7_9                              "1.2.840.10008.1.2.4.54"
#define UID_JPEG_FULL_NONHIER_10_12                                "1.2.840.10008.1.2.4.55"
#define UID_JPEG_FULL_NONHIER_11_13                                "1.2.840.10008.1.2.4.56"
#define UID_JPEG_LOSSLESS_NONHIER_14                               "1.2.840.10008.1.2.4.57"
#define UID_JPEG_LOSSLESS_NONHIER_15                               "1.2.840.10008.1.2.4.58"
#define UID_JPEG_EXTENDED_HIER_16_18                               "1.2.840.10008.1.2.4.59"
#define UID_JPEG_EXTENDED_HIER_17_19                               "1.2.840.10008.1.2.4.60"
#define UID_JPEG_SPECTRAL_HIER_20_22                               "1.2.840.10008.1.2.4.61"
#define UID_JPEG_SPECTRAL_HIER_21_23                               "1.2.840.10008.1.2.4.62"
#define UID_JPEG_FULL_HIER_24_26                                   "1.2.840.10008.1.2.4.63"
#define UID_JPEG_FULL_HIER_25_27                                   "1.2.840.10008.1.2.4.64"
#define UID_JPEG_LOSSLESS_HIER_PROCESS_28                          "1.2.840.10008.1.2.4.65"
#define UID_JPEG_LOSSLESS_HIER_PROCESS_29                          "1.2.840.10008.1.2.4.66"
#define UID_JPEG_LOSSLESS_NONHIER_14B                              "1.2.840.10008.1.2.4.70"
#define UID_JPEG2000_LOSSLESS_ONLY                                 "1.2.840.10008.1.2.4.90" 
#define UID_JPEG2000                                               "1.2.840.10008.1.2.4.91"
#define UID_RLE_LOSSLESS                                           "1.2.840.10008.1.2.5"
#define UID_MEDIA_STORAGE_DIRECTORY                                "1.2.840.10008.1.3.10"
#define UID_BASIC_STUDY_NOTIFICATION_CLASS                         "1.2.840.10008.1.9"
#define UID_STORAGE_COMMITMENT_PUSH_MODEL_CLASS                    "1.2.840.10008.1.20.1"
#define UID_STORAGE_COMMITMENT_PUSH_MODEL_INSTANCE                 "1.2.840.10008.1.20.1.1"
#define UID_STORAGE_COMMITMENT_PULL_MODEL_CLASS                    "1.2.840.10008.1.20.2"
#define UID_STORAGE_COMMITMENT_PULL_MODEL_INSTANCE                 "1.2.840.10008.1.20.2.1"
#define UID_DICOM_CONTROLLED_TERMINOLOGY                           "1.2.840.10008.2.16.4"
#define UID_APPLICATION_CONTEXT_NAME                               "1.2.840.10008.3.1.1.1"
#define UID_DETACHED_PATIENT_CLASS                                 "1.2.840.10008.3.1.2.1.1"
#define UID_DETACHED_PATIENT_META_CLASS                            "1.2.840.10008.3.1.2.1.4"
#define UID_DETACHED_VISIT_CLASS                                   "1.2.840.10008.3.1.2.2.1"
#define UID_DETACHED_STUDY_CLASS                                   "1.2.840.10008.3.1.2.3.1"
#define UID_STUDY_COMPONENT_CLASS                                  "1.2.840.10008.3.1.2.3.2"
#define UID_MODALITY_PERFORMED_CLASS                               "1.2.840.10008.3.1.2.3.3"
#define UID_MODALITY_PERFORMED_RETRIEVE_CLASS                      "1.2.840.10008.3.1.2.3.4"
#define UID_MODALITY_PERFORMED_NOTIFICATION_CLASS                  "1.2.840.10008.3.1.2.3.5"
#define UID_DETACHED_RESULTS_CLASS                                 "1.2.840.10008.3.1.2.5.1"
#define UID_DETACHED_RESULTS_META_CLASS                            "1.2.840.10008.3.1.2.5.4"
#define UID_DETACHED_STUDY_META_CLASS                              "1.2.840.10008.3.1.2.5.5"
#define UID_DETACHED_INTERPRETATION_CLASS                          "1.2.840.10008.3.1.2.6.1"
#define UID_BASIC_FILM_SESSION_CLASS                               "1.2.840.10008.5.1.1.1"
#define UID_BASIC_FILM_BOX_CLASS                                   "1.2.840.10008.5.1.1.2"
#define UID_BASIC_GRAYSCALE_IMAGE_BOX_CLASS                        "1.2.840.10008.5.1.1.4"
#define UID_BASIC_COLOR_IMAGE_BOX_CLASS                            "1.2.840.10008.5.1.1.4.1"
#define UID_REFERENCED_IMAGE_BOX_CLASS_RETIRED                     "1.2.840.10008.5.1.1.4.2"
#define UID_BASIC_GRAYSCALE_PRINT_META_CLASS                       "1.2.840.10008.5.1.1.9"
#define UID_REFERENCED_GRAYSCALE_PRINT_META_CLASS_RETIRED          "1.2.840.10008.5.1.1.9.1"
#define UID_PRINT_JOB_CLASS                                        "1.2.840.10008.5.1.1.14"
#define UID_BASIC_ANNOTATION_BOX_CLASS                             "1.2.840.10008.5.1.1.15"
#define UID_PRINTER_CLASS                                          "1.2.840.10008.5.1.1.16"
#define UID_PRINTER_CONFIGURATION_RETRIEVAL_CLASS                  "1.2.840.10008.5.1.1.16.376"
#define UID_PRINTER_INSTANCE                                       "1.2.840.10008.5.1.1.17"
#define UID_PRINTER_CONFIGURATION_RETRIEVAL_INSTANCE               "1.2.840.10008.5.1.1.17.376"
#define UID_BASIC_COLOR_PRINT_META_CLASS                           "1.2.840.10008.5.1.1.18"
#define UID_REFERENCED_COLOR_PRINT_META_CLASS_RETIRED              "1.2.840.10008.5.1.1.18.1"
#define UID_VOI_LUT_BOX_CLASS_RETIRED                              "1.2.840.10008.5.1.1.22"
#define UID_PRESENTATION_LUT_CLASS                                 "1.2.840.10008.5.1.1.23"
#define UID_IMAGE_OVERLAY_BOX_CLASS_RETIRED                        "1.2.840.10008.5.1.1.24"
#define UID_BASIC_PRINT_IMAGE_OVERLAY_BOX_CLASS                    "1.2.840.10008.5.1.1.24.1"
#define UID_PRINT_QUEUE_INSTANCE                                   "1.2.840.10008.5.1.1.25"
#define UID_PRINT_QUEUE_CLASS                                      "1.2.840.10008.5.1.1.26"
#define UID_STORED_PRINT_STORAGE_CLASS                             "1.2.840.10008.5.1.1.27"
#define UID_HARDCOPY_GRAYSCALE_IMAGE_STORAGE_CLASS                 "1.2.840.10008.5.1.1.29"
#define UID_HARDCOPY_COLOR_IMAGE_STORAGE_CLASS                     "1.2.840.10008.5.1.1.30"
#define UID_PULL_PRINT_REQUEST_CLASS                               "1.2.840.10008.5.1.1.31"
#define UID_PULL_STORED_PRINT_META_CLASS                           "1.2.840.10008.5.1.1.32"
#define UID_CR_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.1"
#define UID_CT_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.2"
#define UID_US_MULTIFRAME_IMAGE_STORAGE_RETIRED                    "1.2.840.10008.5.1.4.1.1.3"
#define UID_US_MULTIFRAME_IMAGE_STORAGE                            "1.2.840.10008.5.1.4.1.1.3.1"
#define UID_MR_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.4"
#define UID_ENHANCED_MR_IMAGE_STORAGE                              "1.2.840.10008.5.1.4.1.1.4.1"
#define UID_MR_SPECTROSCOPY_STORAGE                                "1.2.840.10008.5.1.4.1.1.4.2"
#define UID_NM_IMAGE_STORAGE_RETIRED                               "1.2.840.10008.5.1.4.1.1.5"
#define UID_US_IMAGE_STORAGE_RETIRED                               "1.2.840.10008.5.1.4.1.1.6"
#define UID_US_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.6.1"
#define UID_SC_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.7"
#define UID_SC_MULTI_FRAME_SINGLE_BIT_IMAGE_STORAGE                "1.2.840.10008.5.1.4.1.1.7.1"
#define UID_SC_MULTI_FRAME_GRAYSCALE_BYTE_IMAGE_STORAGE            "1.2.840.10008.5.1.4.1.1.7.2"
#define UID_SC_MULTI_FRAME_GRAYSCALE_WORD_IMAGE_STORAGE            "1.2.840.10008.5.1.4.1.1.7.3"
#define UID_SC_MULTI_FRAME_TRUE_COLOR_IMAGE_STORAGE                "1.2.840.10008.5.1.4.1.1.7.4"
#define UID_STANDALONE_OVERLAY_STORAGE                             "1.2.840.10008.5.1.4.1.1.8"
#define UID_STANDALONE_CURVE_STORAGE                               "1.2.840.10008.5.1.4.1.1.9"
#define UID_STANDALONE_MODALITY_LUT_STORAGE                        "1.2.840.10008.5.1.4.1.1.10"
#define UID_STANDALONE_VOI_LUT_STORAGE                             "1.2.840.10008.5.1.4.1.1.11"
#define UID_XA_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.12.1"
#define UID_XRF_IMAGE_STORAGE                                      "1.2.840.10008.5.1.4.1.1.12.2"
#define UID_XA_BIPLANE_IMAGE_STORAGE_RETIRED                       "1.2.840.10008.5.1.4.1.1.12.3"
#define UID_NM_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.20"
#define UID_RAW_DATA_STORAGE                                       "1.2.840.10008.5.1.4.1.1.66" 
#define UID_PET_IMAGE_STORAGE                                      "1.2.840.10008.5.1.4.1.1.128"
#define UID_STANDALONE_PET_CURVE_STORAGE                           "1.2.840.10008.5.1.4.1.1.129"
#define UID_RT_IMAGE_STORAGE                                       "1.2.840.10008.5.1.4.1.1.481.1"
#define UID_RT_DOSE_STORAGE                                        "1.2.840.10008.5.1.4.1.1.481.2"
#define UID_RT_STRUCTURE_STORAGE                                   "1.2.840.10008.5.1.4.1.1.481.3"
#define UID_RT_BEAMS_TREATMENT_RECORD_STORAGE_CLASS                "1.2.840.10008.5.1.4.1.1.481.4"
#define UID_RT_PLAN_STORAGE                                        "1.2.840.10008.5.1.4.1.1.481.5"
#define UID_RT_BRACHY_TREATMENT_RECORD_STORAGE_CLASS               "1.2.840.10008.5.1.4.1.1.481.6"
#define UID_RT_TREATMENT_SUMMARY_RECORD_STORAGE_CLASS              "1.2.840.10008.5.1.4.1.1.481.7"

#define UID_PATIENT_ROOT_QUERY_FIND                                "1.2.840.10008.5.1.4.1.2.1.1"
#define UID_PATIENT_ROOT_QUERY_MOVE                                "1.2.840.10008.5.1.4.1.2.1.2"
#define UID_PATIENT_ROOT_QUERY_GET                                 "1.2.840.10008.5.1.4.1.2.1.3"
#define UID_STUDY_ROOT_QUERY_FIND                                  "1.2.840.10008.5.1.4.1.2.2.1"
#define UID_STUDY_ROOT_QUERY_MOVE                                  "1.2.840.10008.5.1.4.1.2.2.2"
#define UID_STUDY_ROOT_QUERY_GET                                   "1.2.840.10008.5.1.4.1.2.2.3"
#define UID_PATIENT_STUDY_QUERY_FIND                               "1.2.840.10008.5.1.4.1.2.3.1"
#define UID_PATIENT_STUDY_QUERY_MOVE                               "1.2.840.10008.5.1.4.1.2.3.2"
#define UID_PATIENT_STUDY_QUERY_GET                                "1.2.840.10008.5.1.4.1.2.3.3"
#define UID_MODALITY_WORKLIST_FIND                                 "1.2.840.10008.5.1.4.31"
#define UID_GENERAL_PURPOSE_WORKLIST_FIND                          "1.2.840.10008.5.1.4.32.1"

#define UID_GENERAL_PURPOSE_WORKLIST_MANAGEMENT_META_SOP_CLASS     "1.2.840.10008.5.1.4.32"
#define UID_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_SOP_CLASS     "1.2.840.10008.5.1.4.32.2"
#define UID_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEP_SOP_CLASS     "1.2.840.10008.5.1.4.32.3"



#define UID_DX_IMAGE_STORAGE_PRESENTATION                          "1.2.840.10008.5.1.4.1.1.1.1"
#define UID_DX_IMAGE_STORAGE_PROCESSING                            "1.2.840.10008.5.1.4.1.1.1.1.1"
#define UID_DX_MAMMOGRAPHY_IMAGE_STORAGE_PRESENTATION              "1.2.840.10008.5.1.4.1.1.1.2"
#define UID_DX_MAMMOGRAPHY_IMAGE_STORAGE_PROCESSING                "1.2.840.10008.5.1.4.1.1.1.2.1"
#define UID_DX_INTRAORAL_IMAGE_STORAGE_PRESENTATION                "1.2.840.10008.5.1.4.1.1.1.3"
#define UID_DX_INTRAORAL_IMAGE_STORAGE_PROCESSING                  "1.2.840.10008.5.1.4.1.1.1.3.1"

#define UID_VL_IMAGE_STORAGE_RETIRED                               "1.2.840.10008.5.1.4.1.1.77.1"
#define UID_VL_MULTIFRAME_IMAGE_STORAGE_RETIRED                    "1.2.840.10008.5.1.4.1.1.77.2"
#define UID_VL_ENDOSCOPIC_IMAGE_STORAGE_CLASS                      "1.2.840.10008.5.1.4.1.1.77.1.1"
#define UID_VL_MICROSCOPIC_IMAGE_STORAGE_CLASS                     "1.2.840.10008.5.1.4.1.1.77.1.2"
#define UID_VL_SLIDE_COORDINATES_MICROSCOPIC_IMAGE_STORAGE_CLASS   "1.2.840.10008.5.1.4.1.1.77.1.3"
#define UID_VL_PHOTOGRAPHIC_IMAGE_STORAGE_CLASS                    "1.2.840.10008.5.1.4.1.1.77.1.4"

#define UID_PAPYRUS_3_IMPLICIT_VR_LITTLE_ENDIAN                    "1.2.840.10008.1.20"
#define UID_WAVEFORM_STORAGE                                       "1.2.840.10008.5.1.4.1.1.9.1"
#define UID_12_LEAD_ECG_WAVEFORM_STORAGE                           "1.2.840.10008.5.1.4.1.1.9.1.1"
#define UID_GENERAL_ECG_WAVEFORM_STORAGE                           "1.2.840.10008.5.1.4.1.1.9.1.2"
#define UID_GE_MR_IMAGE                                            "1.2.840.113619.4.2"
#define UID_GE_CT_IMAGE                                            "1.2.840.113619.4.3"
#define UID_GE_DISPLAY_IMAGERMATION                                "1.2.840.113619.4.4"
#define UID_GE_ARM_MIGRATION                                       "1.2.840.113619.4.10"
#define UID_GE_ARM_MIGRATION_INSTANCE                              "1.2.840.113619.7.2"

#define UID_BASIC_TEXT_SR                                          "1.2.840.10008.5.1.4.1.1.88.11"
#define UID_ENHANCED_SR                                            "1.2.840.10008.5.1.4.1.1.88.22"
#define UID_COMPREHENSIVE_SR                                       "1.2.840.10008.5.1.4.1.1.88.33"
#define UID_MAMMOGRAPHY_CAD_SR                                     "1.2.840.10008.5.1.4.1.1.88.50"
#define UID_KEY_OBJECT_SELECTION_DOCUMENT                          "1.2.840.10008.5.1.4.1.1.88.59"
#define UID_CHEST_CAD_SR                                           "1.2.840.10008.5.1.4.1.1.88.65"


#define UID_JPEG_LS_LOSSLESS                                       "1.2.840.10008.1.2.4.80"
#define UID_JPEG_LS_LOSSY                                          "1.2.840.10008.1.2.4.81"

#define UID_AMBULATORY_ECG_WAVEFORM_STORAGE                        "1.2.840.10008.5.1.4.1.1.9.1.3"
#define UID_HEMODYNAMIC_WAVEFORM_STORAGE                           "1.2.840.10008.5.1.4.1.1.9.2.1"
#define UID_CARDIAC_ELECTROPHYSIOLOGY_WAVEFORM_STORAGE             "1.2.840.10008.5.1.4.1.1.9.3.1"
#define UID_BASIC_VOICE_AUDIO_WAVEFORM_STORAGE                     "1.2.840.10008.5.1.4.1.1.9.4.1"

#define UID_GRAYSCALE_SOFTCOPY_PRESENTATION_STATE_STORAGE          "1.2.840.10008.5.1.4.1.1.11.1"


enum
{
   UID_TYPE_OTHER,         // Unknown
   UID_TYPE_TRANSFER1,     // Transfer Syntax - Uncompressed Image
   UID_TYPE_TRANSFER2,     // Transfer Syntax - Compressed Image
   UID_TYPE_CLASS,         // SOP Class
   UID_TYPE_META_CLASS,    // Meta SOP Class
   UID_TYPE_INSTANCE,      // SOP Instance
   UID_TYPE_APPLICATION,   // Application Context Name
};

//typedef struct _DICOMUID DICOMUID, *pDICOMUID;
typedef struct _DICOMUID
{
   GENERICLINK          // Reserved - internally used only

   L_CHAR  *pszCode;    // Code
   L_CHAR  *pszName;    // Name
   L_INT    nType;      // Type
} DICOMUID, *pDICOMUID;

#ifdef __cplusplus

class DICOM_EXPORT LDicomUID
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   static L_VOID    Default   ();

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   static pDICOMUID Insert    (L_CHAR *pszCode, L_CHAR *pszName, L_INT nType);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   static pDICOMUID Delete    (pDICOMUID pUID);
   static L_VOID    Reset     ();

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   static pDICOMUID GetFirst  ();
   static pDICOMUID GetLast   ();
   static pDICOMUID GetPrev   (pDICOMUID pUID);
   static pDICOMUID GetNext   (pDICOMUID pUID);
   static L_UINT32  GetCount  ();
   static L_BOOL    Exists    (pDICOMUID pUID);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   static pDICOMUID Find      (L_CHAR *pszCode);
   static pDICOMUID FindIndex (L_UINT32 nIndex);

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------
   static L_BOOL    SetName   (pDICOMUID pUID, L_CHAR *pszName);

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
private:
   static LDicomTreeEx m_InfoUID;
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

//---------------------------------------------------------------------------
// Initializing Functions
//---------------------------------------------------------------------------
L_VOID    EXT_FUNCTION L_DicomDefaultUID   ();

//---------------------------------------------------------------------------
// Insertion Functions
//---------------------------------------------------------------------------
pDICOMUID EXT_FUNCTION L_DicomInsertUID    (L_CHAR *pszCode, L_CHAR *pszName, L_INT nType);

//---------------------------------------------------------------------------
// Deletion Functions
//---------------------------------------------------------------------------
pDICOMUID EXT_FUNCTION L_DicomDeleteUID    (pDICOMUID pUID);
L_VOID    EXT_FUNCTION L_DicomResetUID     ();

//---------------------------------------------------------------------------
// Iteration Functions
//---------------------------------------------------------------------------
pDICOMUID EXT_FUNCTION L_DicomGetFirstUID  ();
pDICOMUID EXT_FUNCTION L_DicomGetLastUID   ();
pDICOMUID EXT_FUNCTION L_DicomGetPrevUID   (pDICOMUID pUID);
pDICOMUID EXT_FUNCTION L_DicomGetNextUID   (pDICOMUID pUID);
L_UINT32  EXT_FUNCTION L_DicomGetCountUID  ();
L_BOOL    EXT_FUNCTION L_DicomExistsUID    (pDICOMUID pUID);

//---------------------------------------------------------------------------
// Searching Functions
//---------------------------------------------------------------------------
pDICOMUID EXT_FUNCTION L_DicomFindUID      (L_CHAR *pszCode);
pDICOMUID EXT_FUNCTION L_DicomFindIndexUID (L_UINT32 nIndex);

//---------------------------------------------------------------------------
// Modification Functions
//---------------------------------------------------------------------------
L_BOOL    EXT_FUNCTION L_DicomSetNameUID   (pDICOMUID pUID, L_CHAR *pszName);

#ifdef __cplusplus
};
#endif

//============= CLASS ==========================================================

//typedef struct _DICOMTAG DICOMTAG, *pDICOMTAG;
typedef struct _DICOMTAG
{
   GENERICLINK          // Reserved - internally used only

   L_UINT32  nCode;     // Code
   L_UINT32  nMask;     // Mask (for multiple-elements specifies the same entry in the table)
   L_CHAR   *pszName;   // Name
   L_UINT16  nVR;       // Value Representation
   L_UINT32  nMinVM;    // Minimum Value Multiplicity
   L_INT32   nMaxVM;    // Maximum Value Multiplicity
   L_UINT32  nDivideVM; // Value that should divide the Value Multiplicity
} DICOMTAG, *pDICOMTAG;

#ifdef __cplusplus

class DICOM_EXPORT LDicomTag
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   static L_VOID    Default   ();

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   static pDICOMTAG Insert    (L_UINT32 nCode, L_UINT32 nMask, L_CHAR *pszName, L_UINT16 nVR, L_UINT32 nMinVM, L_UINT32 nMaxVM, L_UINT32 nDivideVM);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   static pDICOMTAG Delete    (pDICOMTAG pTag);
   static L_VOID    Reset     ();

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   static pDICOMTAG GetFirst  ();
   static pDICOMTAG GetLast   ();
   static pDICOMTAG GetPrev   (pDICOMTAG pTag);
   static pDICOMTAG GetNext   (pDICOMTAG pTag);
   static L_UINT32  GetCount  ();
   static L_BOOL    Exists    (pDICOMTAG pTag);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   static pDICOMTAG Find      (L_UINT32 nCode);
   static pDICOMTAG FindIndex (L_UINT32 nIndex);

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------
   static L_BOOL    SetName   (pDICOMTAG pTag, L_CHAR *pszName);

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
private:
   static LDicomTreeEx m_InfoTag;
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

//---------------------------------------------------------------------------
// Initializing Functions
//---------------------------------------------------------------------------
L_VOID    EXT_FUNCTION L_DicomDefaultTag   ();

//---------------------------------------------------------------------------
// Insertion Functions
//---------------------------------------------------------------------------
pDICOMTAG EXT_FUNCTION L_DicomInsertTag    (L_UINT32 nCode, L_UINT32 nMask, L_CHAR *pszName, L_UINT16 nVR, L_UINT32 nMinVM, L_UINT32 nMaxVM, L_UINT32 nDivideVM);

//---------------------------------------------------------------------------
// Deletion Functions
//---------------------------------------------------------------------------
pDICOMTAG EXT_FUNCTION L_DicomDeleteTag    (pDICOMTAG pTag);
L_VOID    EXT_FUNCTION L_DicomResetTag     ();

//---------------------------------------------------------------------------
// Iteration Functions
//---------------------------------------------------------------------------
pDICOMTAG EXT_FUNCTION L_DicomGetFirstTag  ();
pDICOMTAG EXT_FUNCTION L_DicomGetLastTag   ();
pDICOMTAG EXT_FUNCTION L_DicomGetPrevTag   (pDICOMTAG pTag);
pDICOMTAG EXT_FUNCTION L_DicomGetNextTag   (pDICOMTAG pTag);
L_UINT32  EXT_FUNCTION L_DicomGetCountTag  ();
L_BOOL    EXT_FUNCTION L_DicomExistsTag    (pDICOMTAG pTag);

//---------------------------------------------------------------------------
// Searching Functions
//---------------------------------------------------------------------------
pDICOMTAG EXT_FUNCTION L_DicomFindTag      (L_UINT32 nCode);
pDICOMTAG EXT_FUNCTION L_DicomFindIndexTag (L_UINT32 nIndex);

//---------------------------------------------------------------------------
// Modification Functions
//---------------------------------------------------------------------------
L_BOOL    EXT_FUNCTION L_DicomSetNameTag   (pDICOMTAG pTag, L_CHAR *pszName);

#ifdef __cplusplus
};
#endif

#define TAG_COMMAND_LENGTH_TO_END                                                0x00000001UL
#define TAG_AFFECTED_SOP_CLASS_UID                                               0x00000002UL  // ***
#define TAG_REQUESTED_SOP_CLASS_UID                                              0x00000003UL  // ***
#define TAG_COMMAND_RECOGNITION_CODE                                             0x00000010UL
#define TAG_COMMAND_FIELD                                                        0x00000100UL  // ***
#define TAG_MESSAGE_ID                                                           0x00000110UL  // ***
#define TAG_MESSAGE_ID_BEING_RESPONDED_TO                                        0x00000120UL  // ***
#define TAG_INITIATOR                                                            0x00000200UL
#define TAG_RECEIVER                                                             0x00000300UL
#define TAG_FIND_LOCATION                                                        0x00000400UL
#define TAG_MOVE_DESTINATION                                                     0x00000600UL  // ***
#define TAG_PRIORITY                                                             0x00000700UL  // ***
#define TAG_DATA_SET_TYPE                                                        0x00000800UL  // ***
#define TAG_NUMBER_OF_MATCHES                                                    0x00000850UL
#define TAG_RESPONSE_SEQUENCE_NUMBER                                             0x00000860UL
#define TAG_STATUS                                                               0x00000900UL  // ***
#define TAG_OFFENDING_ELEMENT                                                    0x00000901UL
#define TAG_ERROR_COMMENT                                                        0x00000902UL
#define TAG_ERROR_ID                                                             0x00000903UL
#define TAG_AFFECTED_SOP_INSTANCE_UID                                            0x00001000UL  // ***
#define TAG_REQUESTED_SOP_INSTANCE_UID                                           0x00001001UL  // ***
#define TAG_EVENT_TYPE_ID                                                        0x00001002UL  // ***
#define TAG_ATTRIBUTE_IDENTIFIER_LIST                                            0x00001005UL  // ***
#define TAG_ACTION_TYPE_ID                                                       0x00001008UL  // ***
#define TAG_NUMBER_OF_REMAINING_SUBOPERATIONS                                    0x00001020UL  // ***
#define TAG_NUMBER_OF_COMPLETED_SUBOPERATIONS                                    0x00001021UL  // ***
#define TAG_NUMBER_OF_FAILED_SUBOPERATIONS                                       0x00001022UL  // ***
#define TAG_NUMBER_OF_WARNING_SUBOPERATIONS                                      0x00001023UL  // ***
#define TAG_MOVE_ORIGINATOR_APPLICATION_ENTITY_TITLE                             0x00001030UL  // ***
#define TAG_MOVE_ORIGINATOR_MESSAGE_ID                                           0x00001031UL  // ***
#define TAG_DIALOG_RECEIVER                                                      0x00004000UL
#define TAG_TERMINAL_TYPE                                                        0x00004010UL
#define TAG_MESSAGE_SET_ID                                                       0x00005010UL
#define TAG_END_MESSAGE_SET                                                      0x00005020UL
#define TAG_DISPLAY_FORMAT                                                       0x00005110UL
#define TAG_PAGE_POSITION_ID                                                     0x00005120UL
#define TAG_TEXT_FORMAT_ID                                                       0x00005130UL
#define TAG_NORMAL_REVERSE                                                       0x00005140UL
#define TAG_ADD_GRAY_SCALE                                                       0x00005150UL
#define TAG_BORDERS                                                              0x00005160UL
#define TAG_COPIES                                                               0x00005170UL
#define TAG_OLD_MAGNIFICATION_TYPE                                               0x00005180UL
#define TAG_ERASE                                                                0x00005190UL
#define TAG_PRINT                                                                0x000051A0UL
#define TAG_OVERLAYS                                                             0x000051B0UL
                                                                                 
#define TAG_FILE_META_INFORMATION_VERSION                                        0x00020001UL
#define TAG_MEDIA_STORAGE_SOP_CLASS_UID                                          0x00020002UL
#define TAG_MEDIA_STORAGE_SOP_INSTANCE_UID                                       0x00020003UL
#define TAG_TRANSFER_SYNTAX_UID                                                  0x00020010UL
#define TAG_IMPLEMENTATION_CLASS_UID                                             0x00020012UL
#define TAG_IMPLEMENTATION_VERSION_NAME                                          0x00020013UL
#define TAG_SOURCE_APPLICATION_ENTITY_TITLE                                      0x00020016UL
#define TAG_PRIVATE_INFORMATION_CREATOR_UID                                      0x00020100UL
#define TAG_PRIVATE_INFORMATION                                                  0x00020102UL
                                                                                 
#define TAG_FILE_SET_ID                                                          0x00041130UL
#define TAG_FILE_SET_DESCRIPTOR_FILE_ID                                          0x00041141UL
#define TAG_SPECIFIC_CHARACTER_SET_OF_FILE                                       0x00041142UL
#define TAG_OFFSET_FIRST_ROOT_DIRECTORY                                          0x00041200UL
#define TAG_OFFSET_LAST_ROOT_DIRECTORY                                           0x00041202UL
#define TAG_FILE_SET_CONSISTENCY_FLAG                                            0x00041212UL
#define TAG_DIRECTORY_RECORD_SEQUENCE                                            0x00041220UL
#define TAG_OFFSET_NEXT_DIRECTORY                                                0x00041400UL
#define TAG_RECORD_IN_USE_FLAG                                                   0x00041410UL
#define TAG_OFFSET_CHILD_DIRECTORY                                               0x00041420UL
#define TAG_DIRECTORY_RECORD_TYPE                                                0x00041430UL
#define TAG_PRIVATE_RECORD_UID                                                   0x00041432UL
#define TAG_REFERENCED_FILE_ID                                                   0x00041500UL
#define TAG_OFFSET_MRDR_DIRECTORY                                                0x00041504UL
#define TAG_REFERENCED_SOP_CLASS_UID_IN_FILE                                     0x00041510UL
#define TAG_REFERENCED_SOP_INSTANCE_UID_IN_FILE                                  0x00041511UL
#define TAG_REFERENCED_TRANSFER_SYNTAX_UID_IN_FILE                               0x00041512UL
#define TAG_NUMBER_OF_REFERENCES                                                 0x00041600UL
                                                                                 
#define TAG_SPECIFIC_CHARACTER_SET                                               0x00080005UL
#define TAG_IMAGE_TYPE                                                           0x00080008UL
#define TAG_INSTANCE_CREATION_DATE                                               0x00080012UL
#define TAG_INSTANCE_CREATION_TIME                                               0x00080013UL
#define TAG_INSTANCE_CREATOR_UID                                                 0x00080014UL
#define TAG_SOP_CLASS_UID                                                        0x00080016UL
#define TAG_SOP_INSTANCE_UID                                                     0x00080018UL
#define TAG_STUDY_DATE                                                           0x00080020UL
#define TAG_SERIES_DATE                                                          0x00080021UL
#define TAG_ACQUISITION_DATE                                                     0x00080022UL
#define TAG_CONTENT_DATE                                                         0x00080023UL
#define TAG_OVERLAY_DATE                                                         0x00080024UL
#define TAG_CURVE_DATE                                                           0x00080025UL
#define TAG_ACQUISITION_DATETIME                                                 0x0008002AUL
#define TAG_STUDY_TIME                                                           0x00080030UL
#define TAG_SERIES_TIME                                                          0x00080031UL
#define TAG_ACQUISITION_TIME                                                     0x00080032UL
#define TAG_CONTENT_TIME                                                         0x00080033UL
#define TAG_OVERLAY_TIME                                                         0x00080034UL
#define TAG_CURVE_TIME                                                           0x00080035UL
#define TAG_NUCLEAR_MEDICINE_SERIES_TYPE_RETIRED                                 0x00080042UL
#define TAG_ACCESSION_NUMBER                                                     0x00080050UL
#define TAG_QUERY_RETRIEVE_LEVEL                                                 0x00080052UL
#define TAG_RETRIEVE_AE_TITLE                                                    0x00080054UL
#define TAG_INSTANCE_AVAILABILITY                                                0x00080056UL
#define TAG_FAILED_SOP_INSTANCE_UID_LIST                                         0x00080058UL
#define TAG_MODALITY                                                             0x00080060UL
#define TAG_MODALITIES_IN_STUDY                                                  0x00080061UL
#define TAG_CONVERSION_TYPE                                                      0x00080064UL
#define TAG_PRESENTATION_INTENT_TYPE                                             0x00080068UL
#define TAG_MANUFACTURER                                                         0x00080070UL
#define TAG_INSTITUTION_NAME                                                     0x00080080UL
#define TAG_INSTITUTION_ADDRESS                                                  0x00080081UL
#define TAG_INSTITUTION_CODE_SEQUENCE                                            0x00080082UL
#define TAG_REFERRING_PHYSICIAN_NAME                                             0x00080090UL
#define TAG_REFERRING_PHYSICIAN_ADDRESS                                          0x00080092UL
#define TAG_REFERRING_PHYSICIAN_TELEPHONE_NUMBERS                                0x00080094UL
#define TAG_REFERRING_PHYSICIAN_IDENTIFICATION_SEQUENCE                          0x00080096UL
#define TAG_CODE_VALUE                                                           0x00080100UL
#define TAG_CODING_SCHEME_DESIGNATOR                                             0x00080102UL
#define TAG_CODE_MEANING                                                         0x00080104UL
#define TAG_CONTEXT_GROUP_LOCAL_VERSION                                          0x00080107UL
#define TAG_CONTEXT_GROUP_EXTENSION_FLAG                                         0x0008010BUL
#define TAG_CODING_SCHEME_UID                                                    0x0008010CUL
#define TAG_CONTEXT_GROUP_EXTENSION_CREATOR_UID                                  0x0008010DUL
#define TAG_CODING_SCHEME_IDENTIFICATION_SEQUENCE                                0x00080110UL
#define TAG_CODING_SCHEME_REGISTRY                                               0x00080112UL
#define TAG_CODING_SCHEME_EXTERNAL_ID                                            0x00080114UL
#define TAG_CODING_SCHEME_NAME                                                   0x00080115UL
#define TAG_RESPONSIBLE_ORGANIZATION                                             0x00080116UL
#define TAG_TIMEZONE_OFFSET_FROM_UTC                                             0x00080201UL
#define TAG_STATION_NAME                                                         0x00081010UL
#define TAG_STUDY_DESCRIPTION                                                    0x00081030UL
#define TAG_PROCEDURE_CODE_SEQUENCE                                              0x00081032UL
#define TAG_SERIES_DESCRIPTION                                                   0x0008103EUL
#define TAG_INSTITUTIONAL_DEPARTMENT_NAME                                        0x00081040UL
#define TAG_PHYSICIAN_OF_RECORD                                                  0x00081048UL
#define TAG_PHYSICIAN_OF_RECORD_IDENTIFICATION_SEQUENCE                          0x00081049UL
#define TAG_PERFORMING_PHYSICIAN_NAME                                            0x00081050UL
#define TAG_PERFORMING_PHYSICIAN_IDENTIFICATION_SEQUENCE                         0x00081052UL
#define TAG_NAME_OF_PHYSICIAN_READING_STUDY                                      0x00081060UL
#define TAG_PHYSICIAN_READING_STUDY_IDENTIFICATION_SEQUENCE                      0x00081062UL
#define TAG_OPERATORS_NAME                                                       0x00081070UL
#define TAG_OPERATOR_IDENTIFICATION_SEQUENCE                                     0x00081072UL
#define TAG_ADMITTING_DIAGNOSES_DESCRIPTION                                      0x00081080UL
#define TAG_ADMITTING_DIAGNOSIS_CODE_SEQUENCE                                    0x00081084UL
#define TAG_MANUFACTURER_MODEL_NAME                                              0x00081090UL
#define TAG_REFERENCED_RESULTS_SEQUENCE                                          0x00081100UL
#define TAG_REFERENCED_STUDY_SEQUENCE                                            0x00081110UL
#define TAG_REFERENCED_STUDY_COMPONENT_SEQUENCE                                  0x00081111UL
#define TAG_REFERENCED_SERIES_SEQUENCE                                           0x00081115UL
#define TAG_REFERENCED_PATIENT_SEQUENCE                                          0x00081120UL
#define TAG_REFERENCED_VISIT_SEQUENCE                                            0x00081125UL
#define TAG_REFERENCED_OVERLAY_SEQUENCE_0008                                     0x00081130UL
#define TAG_REFERENCED_WAVEFORM_SEQUENCE                                         0x0008113AUL
#define TAG_REFERENCED_IMAGE_SEQUENCE                                            0x00081140UL
#define TAG_REFERENCED_CURVE_SEQUENCE                                            0x00081145UL
#define TAG_REFERENCED_SOP_CLASS_UID                                             0x00081150UL
#define TAG_REFERENCED_SOP_INSTANCE_UID                                          0x00081155UL
#define TAG_SOP_CLASSES_SUPPORTED                                                0x0008115AUL
#define TAG_REFERENCED_FRAME_NUMBER                                              0x00081160UL
#define TAG_TRANSACTION_UID                                                      0x00081195UL
#define TAG_FAILURE_REASON                                                       0x00081197UL
#define TAG_FAILED_SOP_SEQUENCE                                                  0x00081198UL
#define TAG_REFERENCED_SOP_SEQUENCE                                              0x00081199UL
#define TAG_REFERENCED_INSTANCE_SEQUENCE                                         0x0008114AUL
#define TAG_LOSSY_IMAGE_COMPRESSION_RETIRED                                      0x00082110UL
#define TAG_DERIVATION_DESCRIPTION                                               0x00082111UL
#define TAG_SOURCE_IMAGE_SEQUENCE                                                0x00082112UL
#define TAG_STAGE_NAME                                                           0x00082120UL
#define TAG_STAGE_NUMBER                                                         0x00082122UL
#define TAG_NUMBER_OF_STAGES                                                     0x00082124UL
#define TAG_VIEW_NAME                                                            0x00082127UL
#define TAG_VIEW_NUMBER                                                          0x00082128UL
#define TAG_NUMBER_OF_EVENT_TIMERS                                               0x00082129UL
#define TAG_NUMBER_OF_VIEWS_IN_STAGE                                             0x0008212AUL
#define TAG_EVENT_ELAPSED_TIME                                                   0x00082130UL
#define TAG_EVENT_TIMER_NAME                                                     0x00082132UL
#define TAG_START_TRIM                                                           0x00082142UL
#define TAG_STOP_TRIM                                                            0x00082143UL
#define TAG_RECOMMENDED_DISPLAY_FRAME_RATE                                       0x00082144UL
#define TAG_TRANSDUCER_POSITION_RETIRED                                          0x00082200UL
#define TAG_TRANSDUCER_ORIENTATION_RETIRED                                       0x00082204UL
#define TAG_ANATOMIC_STRUCTURE_RETIRED                                           0x00082208UL
#define TAG_ANATOMIC_REGION_SEQUENCE                                             0x00082218UL
#define TAG_ANATOMIC_REGION_MODIFIER_SEQUENCE                                    0x00082220UL
#define TAG_PRIMARY_ANATOMIC_STRUCTURE_SEQUENCE                                  0x00082228UL
#define TAG_ANATOMIC_STRUCTURE_SPACE_OR_REGION_SEQUENCE                          0x00082229UL
#define TAG_PRIMARY_ANATOMIC_STRUCTURE_MODIFIER_SEQUENCE                         0x00082230UL
#define TAG_TRANSDUCER_POSITION_SEQUENCE                                         0x00082240UL
#define TAG_TRANSDUCER_POSITION_MODIFIER_SEQUENCE                                0x00082242UL
#define TAG_TRANSDUCER_ORIENTATION_SEQUENCE                                      0x00082244UL
#define TAG_TRANSDUCER_ORIENTATION_MODIFIER_SEQUENCE                             0x00082246UL
#define TAG_FRAME_TYPE                                                           0x00089007UL
#define TAG_REFERENCED_IMAGE_EVIDENCE_SEQUENCE                                   0x00089092UL
#define TAG_REFERENCED_RAW_DATA_SEQUENCE                                         0x00089121UL
#define TAG_CREATOR_VERSION_UID                                                  0x00089123UL
#define TAG_DERIVATION_IMAGE_SEQUENCE                                            0x00089124UL
#define TAG_SOURCE_IMAGE_EVIDENCE_SEQUENCE                                       0x00089154UL
#define TAG_PIXEL_PRESENTATION                                                   0x00089205UL
#define TAG_VOLUMETRIC_PROPERTIES                                                0x00089206UL
#define TAG_VOLUME_BASED_CALCULATION_TECHNIQUE                                   0x00089207UL
#define TAG_COMPLEX_IMAGE_COMPONENT                                              0x00089208UL
#define TAG_ACQUISITION_CONTRAST                                                 0x00089209UL
#define TAG_DERIVATION_CODE_SEQUENCE                                             0x00089215UL
#define TAG_REFERENCED_GRAYSCALE_PRESENTATION_STATE_SEQUENCE                     0x00089237UL
#define TAG_PATIENT_NAME                                                         0x00100010UL
#define TAG_PATIENT_ID                                                           0x00100020UL
#define TAG_ISSUER_OF_PATIENT_ID                                                 0x00100021UL
#define TAG_PATIENT_BIRTH_DATE                                                   0x00100030UL
#define TAG_PATIENT_BIRTH_TIME                                                   0x00100032UL
#define TAG_PATIENT_SEX                                                          0x00100040UL
#define TAG_PATIENT_INSURANCE_PLAN_CODE_SEQUENCE                                 0x00100050UL
#define TAG_PATIENT_PRIMARY_LANGUAGE_CODE_SEQUENCE                               0x00100101UL
#define TAG_PATIENT_PRIMARY_LANGUAGE_CODE_MODIFIER_SEQUENCE                      0x00100102UL
#define TAG_OTHER_PATIENT_IDS                                                    0x00101000UL
#define TAG_OTHER_PATIENT_NAMES                                                  0x00101001UL
#define TAG_PATIENT_BIRTH_NAME                                                   0x00101005UL
#define TAG_PATIENT_AGE                                                          0x00101010UL
#define TAG_PATIENT_SIZE                                                         0x00101020UL
#define TAG_PATIENT_WEIGHT                                                       0x00101030UL
#define TAG_PATIENT_ADDRESS                                                      0x00101040UL
#define TAG_PATIENT_MOTHER_BIRTH_NAME                                            0x00101060UL
#define TAG_MILITARY_RANK                                                        0x00101080UL
#define TAG_BRANCH_OF_SERVICE                                                    0x00101081UL
#define TAG_MEDICAL_RECORD_LOCATOR                                               0x00101090UL
#define TAG_MEDICAL_ALERTS                                                       0x00102000UL
#define TAG_CONTRAST_ALLERGIES                                                   0x00102110UL
#define TAG_COUNTRY_OF_RESIDENCE                                                 0x00102150UL
#define TAG_REGION_OF_RESIDENCE                                                  0x00102152UL
#define TAG_PATIENT_TELEPHONE_NUMBERS                                            0x00102154UL
#define TAG_ETHNIC_GROUP                                                         0x00102160UL
#define TAG_OCCUPATION                                                           0x00102180UL
#define TAG_SMOKING_STATUS                                                       0x001021A0UL
#define TAG_ADDITIONAL_PATIENT_HISTORY                                           0x001021B0UL
#define TAG_PREGNANCY_STATUS                                                     0x001021C0UL
#define TAG_LAST_MENSTRUAL_DATE                                                  0x001021D0UL
#define TAG_PATIENT_RELIGIOUS_PREFERENCE                                         0x001021F0UL
#define TAG_PATIENT_COMMENTS                                                     0x00104000UL
#define TAG_CLINICAL_TRIAL_SPONSOR_NAME                                          0x00120010UL  
#define TAG_CLINICAL_TRIAL_PROTOCOL_ID                                           0x00120020UL  
#define TAG_CLINICAL_TRIAL_PROTOCOL_NAME                                         0x00120021UL  
#define TAG_CLINICAL_TRIAL_SITE_ID                                               0x00120030UL  
#define TAG_CLINICAL_TRIAL_SITE_NAME                                             0x00120031UL  
#define TAG_CLINICAL_TRIAL_SUBJECT_ID                                            0x00120040UL  
#define TAG_CLINICAL_TRIAL_SUBJECT_READING_ID                                    0x00120042UL  
#define TAG_CLINICAL_TRIAL_TIME_POINT_ID                                         0x00120050UL  
#define TAG_CLINICAL_TRIAL_TIME_POINT_DESCRIPTION                                0x00120051UL  
#define TAG_CLINICAL_TRIAL_COORDINATING_CENTER_NAME                              0x00120060UL                                                                                   
#define TAG_CONTRAST_BOLUS_AGENT                                                 0x00180010UL
#define TAG_CONTRAST_BOLUS_AGENT_SEQUENCE                                        0x00180012UL
#define TAG_CONTRAST_BOLUS_ADMINISTRATION_ROUTE_SEQUENCE                         0x00180014UL
#define TAG_BODY_PART_EXAMINED                                                   0x00180015UL
#define TAG_SCANNING_SEQUENCE                                                    0x00180020UL
#define TAG_SEQUENCE_VARIANT                                                     0x00180021UL
#define TAG_SCAN_OPTIONS                                                         0x00180022UL
#define TAG_MR_ACQUISITION_TYPE                                                  0x00180023UL
#define TAG_SEQUENCE_NAME                                                        0x00180024UL
#define TAG_ANGIO_FLAG                                                           0x00180025UL
#define TAG_INTERVENTION_DRUG_INFORMATION_SEQUENCE                               0x00180026UL
#define TAG_INTERVENTION_DRUG_STOP_TIME                                          0x00180027UL
#define TAG_INTERVENTION_DRUG_DOSE                                               0x00180028UL
#define TAG_INTERVENTION_DRUG_CODE_SEQUENCE                                      0x00180029UL
#define TAG_ADDITIONAL_DRUG_SEQUENCE                                             0x0018002AUL
#define TAG_RADIONUCLIDE_RETIRED                                                 0x00180030UL
#define TAG_RADIOPHARMACEUTICAL                                                  0x00180031UL
#define TAG_ENERGY_WINDOW_CENTERLINE_RETIRED                                     0x00180032UL
#define TAG_ENERGY_WINDOW_TOTAL_WIDTH_RETIRED                                    0x00180033UL
#define TAG_INTERVENTION_DRUG_NAME                                               0x00180034UL
#define TAG_INTERVENTION_DRUG_START_TIME                                         0x00180035UL
#define TAG_INTERVENTIONAL_THERAPY_SEQUENCE                                      0x00180036UL
#define TAG_THERAPY_TYPE                                                         0x00180037UL
#define TAG_INTERVENTIONAL_STATUS                                                0x00180038UL
#define TAG_THERAPY_DESCRIPTION                                                  0x00180039UL
#define TAG_CINE_RATE                                                            0x00180040UL
#define TAG_SLICE_THICKNESS                                                      0x00180050UL
#define TAG_KVP                                                                  0x00180060UL
#define TAG_COUNTS_ACCUMULATED                                                   0x00180070UL
#define TAG_ACQUISITION_TERMINATION_CONDITION                                    0x00180071UL
#define TAG_EFFECTIVE_SERIES_DURATION                                            0x00180072UL
#define TAG_ACQUISITION_START_CONDITION                                          0x00180073UL
#define TAG_ACQUISITION_START_CONDITION_DATA                                     0x00180074UL
#define TAG_ACQUISITION_TERMINATION_CONDITION_DATA                               0x00180075UL
#define TAG_REPETITION_TIME                                                      0x00180080UL
#define TAG_ECHO_TIME                                                            0x00180081UL
#define TAG_INVERSION_TIME                                                       0x00180082UL
#define TAG_NUMBER_OF_AVERAGES                                                   0x00180083UL
#define TAG_IMAGING_FREQUENCY                                                    0x00180084UL
#define TAG_IMAGED_NUCLEUS                                                       0x00180085UL
#define TAG_ECHO_NUMBER                                                          0x00180086UL
#define TAG_MAGNETIC_FIELD_STRENGTH                                              0x00180087UL
#define TAG_SPACING_BETWEEN_SLICES                                               0x00180088UL
#define TAG_NUMBER_OF_PHASE_ENCODING_STEPS                                       0x00180089UL
#define TAG_DATA_COLLECTION_DIAMETER                                             0x00180090UL
#define TAG_ECHO_TRAIN_LENGTH                                                    0x00180091UL
#define TAG_PERCENT_SAMPLING                                                     0x00180093UL
#define TAG_PERCENT_PHASE_FIELD_OF_VIEW                                          0x00180094UL
#define TAG_PIXEL_BANDWIDTH                                                      0x00180095UL
#define TAG_IMAGE_TRIGGER_DELAY                                                  0x00181067UL
#define TAG_MULTIPLEX_GROUP_TIME_OFFSET                                          0x00181068UL
#define TAG_TRIGGER_TIME_OFFSET                                                  0x00181069UL
#define TAG_SYNCHRONIZATION_TRIGGER                                              0x0018106AUL
#define TAG_SYNCHRONIZATION_FRAME_OF_REFERENCE                                   0x0018106BUL
#define TAG_SYNCHRONIZATION_CHANNEL                                              0x0018106CUL
#define TAG_TRIGGER_SAMPLE_POSITION                                              0x0018106EUL
#define TAG_DEVICE_SERIAL_NUMBER                                                 0x00181000UL
#define TAG_PLATE_ID                                                             0x00181004UL
#define TAG_SECONDARY_CAPTURE_DEVICE_ID                                          0x00181010UL
#define TAG_HARDCOPY_CREATION_DEVICE_ID                                          0x00181011UL
#define TAG_DATE_OF_SECONDARY_CAPTURE                                            0x00181012UL
#define TAG_TIME_OF_SECONDARY_CAPTURE                                            0x00181014UL
#define TAG_SECONDARY_CAPTURE_DEVICE_MANUFACTURER                                0x00181016UL
#define TAG_HARDCOPY_DEVICE_MANUFACTURER                                         0x00181017UL
#define TAG_SECONDARY_CAPTURE_DEVICE_MANUFACTURER_MODEL_NAME                     0x00181018UL
#define TAG_SECONDARY_CAPTURE_DEVICE_SOFTWARE_VERSION                            0x00181019UL
#define TAG_HARDCOPY_DEVICE_SOFTWARE_VERSION                                     0x0018101AUL
#define TAG_HARDCOPY_DEVICE_MANFUACTURER_MODEL_NAME                              0x0018101BUL
#define TAG_SOFTWARE_VERSION                                                     0x00181020UL
#define TAG_VIDEO_IMAGE_FORMAT_ACQUIRED                                          0x00181022UL
#define TAG_DIGITAL_IMAGE_FORMAT_ACQUIRED                                        0x00181023UL
#define TAG_PROTOCOL_NAME                                                        0x00181030UL
#define TAG_CONTRAST_BOLUS_ROUTE                                                 0x00181040UL
#define TAG_CONTRAST_BOLUS_VOLUME                                                0x00181041UL
#define TAG_CONTRAST_BOLUS_START_TIME                                            0x00181042UL
#define TAG_CONTRAST_BOLUS_STOP_TIME                                             0x00181043UL
#define TAG_CONTRAST_BOLUS_TOTAL_DOSE                                            0x00181044UL
#define TAG_SYRINGE_COUNTS                                                       0x00181045UL
#define TAG_CONTRAST_FLOW_RATE                                                   0x00181046UL
#define TAG_CONTRAST_FLOW_DURATION                                               0x00181047UL
#define TAG_CONTRAST_BOLUS_INGREDIENT                                            0x00181048UL
#define TAG_CONTRAST_BOLUS_INGREDIENT_CONCENTRATION                              0x00181049UL
#define TAG_SPATIAL_RESOLUTION                                                   0x00181050UL
#define TAG_TRIGGER_TIME                                                         0x00181060UL
#define TAG_TRIGGER_SOURCE_OR_TYPE                                               0x00181061UL
#define TAG_NOMINAL_INTERVAL                                                     0x00181062UL
#define TAG_FRAME_TIME                                                           0x00181063UL
#define TAG_FRAMING_TYPE                                                         0x00181064UL
#define TAG_FRAME_TIME_VECTOR                                                    0x00181065UL
#define TAG_FRAME_DELAY                                                          0x00181066UL
#define TAG_RADIOPHARMACEUTICAL_ROUTE                                            0x00181070UL
#define TAG_RADIOPHARMACEUTICAL_VOLUME                                           0x00181071UL
#define TAG_RADIOPHARMACEUTICAL_START_TIME                                       0x00181072UL
#define TAG_RADIOPHARMACEUTICAL_STOP_TIME                                        0x00181073UL
#define TAG_RADIONUCLIDE_TOTAL_DOSE                                              0x00181074UL
#define TAG_RADIONUCLIDE_HALF_LIFE                                               0x00181075UL
#define TAG_RADIONUCLIDE_POSITRON_FRACTION                                       0x00181076UL
#define TAG_RADIOPHARMACEUTICAL_SPECIFIC_ACTIVITY                                0x00181077UL
#define TAG_BEAT_REJECTION_FLAG                                                  0x00181080UL
#define TAG_LOW_R_R_VALUE                                                        0x00181081UL
#define TAG_HIGH_R_R_VALUE                                                       0x00181082UL
#define TAG_INTERVALS_ACQUIRED                                                   0x00181083UL
#define TAG_INTERVALS_REJECTED                                                   0x00181084UL
#define TAG_PVC_REJECTION                                                        0x00181085UL
#define TAG_SKIP_BEATS                                                           0x00181086UL
#define TAG_HEART_RATE                                                           0x00181088UL
#define TAG_CARDIAC_NUMBER_OF_IMAGES                                             0x00181090UL
#define TAG_TRIGGER_WINDOW                                                       0x00181094UL
#define TAG_RECONSTRUCTION_DIAMETER                                              0x00181100UL
#define TAG_DISTANCE_SOURCE_TO_DETECTOR                                          0x00181110UL
#define TAG_DISTANCE_SOURCE_TO_PATIENT                                           0x00181111UL
#define TAG_ESTIMATED_RADIOGRAPHIC_MAGNIFICATION_FACTOR                          0x00181114UL
#define TAG_GANTRY_DETECTOR_TILT                                                 0x00181120UL
#define TAG_GANTRY_DETECTOR_SLEW                                                 0x00181121UL
#define TAG_TABLE_HEIGHT                                                         0x00181130UL
#define TAG_TABLE_TRAVERSE                                                       0x00181131UL
#define TAG_TABLE_MOTION                                                         0x00181134UL
#define TAG_TABLE_VERTICAL_INCREMENT                                             0x00181135UL
#define TAG_TABLE_LATERAL_INCREMENT                                              0x00181136UL
#define TAG_TABLE_LONGITUDINAL_INCREMENT                                         0x00181137UL
#define TAG_TABLE_ANGLE                                                          0x00181138UL
#define TAG_ROTATION_DIRECTION                                                   0x00181140UL
#define TAG_ANGULAR_POSITION                                                     0x00181141UL
#define TAG_RADIAL_POSITION                                                      0x00181142UL
#define TAG_SCAN_ARC                                                             0x00181143UL
#define TAG_ANGULAR_STEP                                                         0x00181144UL
#define TAG_CENTER_OF_ROTATION_OFFSET                                            0x00181145UL
#define TAG_ROTATION_OFFSET_RETIRED                                              0x00181146UL
#define TAG_FIELD_OF_VIEW_SHAPE                                                  0x00181147UL
#define TAG_FIELD_OF_VIEW_DIMENSION                                              0x00181149UL
#define TAG_EXPOSURE_TIME                                                        0x00181150UL
#define TAG_X_RAY_TUBE_CURRENT                                                   0x00181151UL
#define TAG_EXPOSURE                                                             0x00181152UL
#define TAG_EXPOSURE_IN_UAS                                                      0x00181153UL
#define TAG_AVERAGE_PULSE_WIDTH                                                  0x00181154UL
#define TAG_RADIATION_SETTING                                                    0x00181155UL
#define TAG_RADIATION_MODE                                                       0x0018115AUL
#define TAG_IMAGE_AREA_DOSE_PRODUCT                                              0x0018115EUL
#define TAG_FILTER_TYPE                                                          0x00181160UL
#define TAG_TYPE_OF_FILTERS                                                      0x00181161UL
#define TAG_INTENSIFIER_SIZE                                                     0x00181162UL
#define TAG_IMAGER_PIXEL_SPACING                                                 0x00181164UL
#define TAG_GRID                                                                 0x00181166UL
#define TAG_GENERATOR_POWER                                                      0x00181170UL
#define TAG_COLLIMATOR_GRID_NAME                                                 0x00181180UL
#define TAG_COLLIMATOR_TYPE                                                      0x00181181UL
#define TAG_FOCAL_DISTANCE                                                       0x00181182UL
#define TAG_X_FOCUS_CENTER                                                       0x00181183UL
#define TAG_Y_FOCUS_CENTER                                                       0x00181184UL
#define TAG_FOCAL_SPOT                                                           0x00181190UL
#define TAG_DATE_OF_LAST_CALIBRATION                                             0x00181200UL
#define TAG_TIME_OF_LAST_CALIBRATION                                             0x00181201UL
#define TAG_CONVOLUTION_KERNEL                                                   0x00181210UL
#define TAG_ACTUAL_FRAME_DURATION                                                0x00181242UL
#define TAG_COUNT_RATE                                                           0x00181243UL
#define TAG_PREFERRED_PLAYBACK_SEQUENCING                                        0x00181244UL
#define TAG_RECEIVING_COIL                                                       0x00181250UL
#define TAG_TRANSMITTING_COIL                                                    0x00181251UL
#define TAG_PLATE_TYPE                                                           0x00181260UL
#define TAG_PHOSPHOR_TYPE                                                        0x00181261UL
#define TAG_SCAN_VELOCITY                                                        0x00181300UL
#define TAG_WHOLE_BODY_TECHNIQUE                                                 0x00181301UL
#define TAG_SCAN_LENGTH                                                          0x00181302UL
#define TAG_ACQUISITION_MATRIX                                                   0x00181310UL
#define TAG_PHASE_ENCODING_DIRECTION                                             0x00181312UL
#define TAG_FLIP_ANGLE                                                           0x00181314UL
#define TAG_VARIABLE_FLIP_ANGLE_FLAG                                             0x00181315UL
#define TAG_SAR                                                                  0x00181316UL
#define TAG_DB_DT                                                                0x00181318UL
#define TAG_ACQUISITION_DEVICE_PROCESSING_DESCRIPTION                            0x00181400UL
#define TAG_ACQUISITION_DEVICE_PROCESSING_CODE                                   0x00181401UL
#define TAG_CASSETTE_ORIENTATION                                                 0x00181402UL
#define TAG_CASSETTE_SIZE                                                        0x00181403UL
#define TAG_EXPOSURES_ON_PLATE                                                   0x00181404UL
#define TAG_RELATIVE_X_RAY_EXPOSURE                                              0x00181405UL
#define TAG_COLUMN_ANGULATION                                                    0x00181450UL
#define TAG_TOMO_LAYER_HEIGHT                                                    0x00181460UL
#define TAG_TOMO_ANGLE                                                           0x00181470UL
#define TAG_TOMO_TIME                                                            0x00181480UL
#define TAG_POSITIONER_MOTION                                                    0x00181500UL
#define TAG_POSITIONER_TYPE                                                      0x00181508UL
#define TAG_POSITIONER_PRIMARY_ANGLE                                             0x00181510UL
#define TAG_POSITIONER_SECONDARY_ANGLE                                           0x00181511UL
#define TAG_POSITIONER_PRIMARY_ANGLE_INCREMENT                                   0x00181520UL
#define TAG_POSITIONER_SECONDARY_ANGLE_INCREMENT                                 0x00181521UL
#define TAG_DETECTOR_PRIMARY_ANGLE                                               0x00181530UL
#define TAG_DETECTOR_SECONDARY_ANGLE                                             0x00181531UL
#define TAG_SHUTTER_SHAPE                                                        0x00181600UL
#define TAG_SHUTTER_LEFT_VERTICAL_EDGE                                           0x00181602UL
#define TAG_SHUTTER_RIGHT_VERTICAL_EDGE                                          0x00181604UL
#define TAG_SHUTTER_UPPER_HORIZONTAL_EDGE                                        0x00181606UL
#define TAG_SHUTTER_LOWER_HORIZONTAL_EDGE                                        0x00181608UL
#define TAG_CENTER_OF_CIRCULAR_SHUTTER                                           0x00181610UL
#define TAG_RADIUS_OF_CIRCULAR_SHUTTER                                           0x00181612UL
#define TAG_VERTICES_OF_THE_POLYGONAL_SHUTTER                                    0x00181620UL
#define TAG_SHUTTER_PRESENTATION_VALUE                                           0x00181622UL
#define TAG_SHUTTER_OVERLAY_GROUP                                                0x00181623UL
#define TAG_COLLIMATOR_SHAPE                                                     0x00181700UL
#define TAG_COLLIMATOR_LEFT_VERTICAL_EDGE                                        0x00181702UL
#define TAG_COLLIMATOR_RIGHT_VERTICAL_EDGE                                       0x00181704UL
#define TAG_COLLIMATOR_UPPER_HORIZONTAL_EDGE                                     0x00181706UL
#define TAG_COLLIMATOR_LOWER_HORIZONTAL_EDGE                                     0x00181708UL
#define TAG_CENTER_OF_CIRCULAR_COLLIMATOR                                        0x00181710UL
#define TAG_RADIUS_OF_CIRCULAR_COLLIMATOR                                        0x00181712UL
#define TAG_VERTICES_OF_THE_POLYGONAL_COLLIMATOR                                 0x00181720UL
#define TAG_ACQUISITION_TIME_SYNCHRONIZED                                        0x00181800UL
#define TAG_TIME_DISTRIBUTION_PROTOCOL                                           0x00181802UL
#define TAG_TIME_SOURCE                                                          0x00181801UL
#define TAG_PAGE_NUMBER_VECTOR                                                   0x00182001UL   
#define TAG_FRAME_LABEL_VECTOR                                                   0x00182002UL   
#define TAG_FRAME_PRIMARY_ANGLE_VECTOR                                           0x00182003UL   
#define TAG_FRAME_SECONDARY_ANGLE_VECTOR                                         0x00182004UL   
#define TAG_SLICE_LOCATION_VECTOR                                                0x00182005UL   
#define TAG_DISPLAY_WINDOW_LABEL_VECTOR                                          0x00182006UL   
#define TAG_NOMINAL_SCANNED_PIXEL_SPACING                                        0x00182010UL   
#define TAG_DIGITIZING_DEVICE_TRANSPORT_DIRECTION                                0x00182020UL   
#define TAG_ROTATION_OF_SCANNED_FILM                                             0x00182030UL   
#define TAG_IVUS_ACQUISITION                                                     0x00183100UL   
#define TAG_IVUS_PULLBACK_RATE                                                   0x00183101UL   
#define TAG_IVUS_GATED_RATE                                                      0x00183102UL   
#define TAG_IVUS_PULLBACK_START_FRAME_NUMBER                                     0x00183103UL   
#define TAG_IVUS_PULLBACK_STOP_FRAME_NUMBER                                      0x00183104UL   
#define TAG_LESION_NUMBER                                                        0x00183105UL   
#define TAG_OUTPUT_POWER                                                         0x00185000UL
#define TAG_TRANSDUCER_DATA                                                      0x00185010UL
#define TAG_FOCUS_DEPTH                                                          0x00185012UL
#define TAG_PROCESSING_FUNCTION                                                  0x00185020UL
#define TAG_POSTPROCESSING_FUNCTION                                              0x00185021UL
#define TAG_MECHANICAL_INDEX                                                     0x00185022UL
#define TAG_THERMAL_INDEX                                                        0x00185024UL
#define TAG_CRANIAL_THERMAL_INDEX                                                0x00185026UL
#define TAG_SOFT_TISSUE_THERMAL_INDEX                                            0x00185027UL
#define TAG_SOFT_TISSUE_FOCUS_THERMAL_INDEX                                      0x00185028UL
#define TAG_SOFT_TISSUE_SURFACE_THERMAL_INDEX                                    0x00185029UL
#define TAG_DEPTH_OF_SCAN_FIELD                                                  0x00185050UL
#define TAG_PATIENT_POSITION                                                     0x00185100UL
#define TAG_VIEW_POSITION                                                        0x00185101UL
#define TAG_PROJECTION_EPONYMOUS_NAME_CODE_SEQUENCE                              0x00185104UL
#define TAG_IMAGE_TRANSFORMATION_MATRIX                                          0x00185210UL
#define TAG_IMAGE_TRANSLATION_VECTOR                                             0x00185212UL
#define TAG_SENSITIVITY                                                          0x00186000UL
#define TAG_SEQUENCE_OF_ULTRASOUND_REGIONS                                       0x00186011UL
#define TAG_REGION_SPATIAL_FORMAT                                                0x00186012UL
#define TAG_REGION_DATA_TYPE                                                     0x00186014UL
#define TAG_REGION_FLAGS                                                         0x00186016UL
#define TAG_REGION_LOCATION_MIN_X_0                                              0x00186018UL
#define TAG_REGION_LOCATION_MIN_Y_0                                              0x0018601AUL
#define TAG_REGION_LOCATION_MAX_X_1                                              0x0018601CUL
#define TAG_REGION_LOCATION_MAX_Y_1                                              0x0018601EUL
#define TAG_REFERENCE_PIXEL_X_0                                                  0x00186020UL
#define TAG_REFERENCE_PIXEL_Y_0                                                  0x00186022UL
#define TAG_PHYSICAL_UNITS_X_DIRECTION                                           0x00186024UL
#define TAG_PHYSICAL_UNITS_Y_DIRECTION                                           0x00186026UL
#define TAG_REFERENCE_PIXEL_PHYSICAL_VALUE_X                                     0x00186028UL
#define TAG_REFERENCE_PIXEL_PHYSICAL_VALUE_Y                                     0x0018602AUL
#define TAG_PHYSICAL_DELTA_X                                                     0x0018602CUL
#define TAG_PHYSICAL_DELTA_Y                                                     0x0018602EUL
#define TAG_TRANSDUCER_FREQUENCY                                                 0x00186030UL
#define TAG_TRANSDUCER_TYPE                                                      0x00186031UL
#define TAG_PULSE_REPETITION_FREQUENCY                                           0x00186032UL
#define TAG_DOPPLER_CORRECTION_ANGLE                                             0x00186034UL
#define TAG_STEERING_ANGLE                                                       0x00186036UL
#define TAG_DOPPLER_SAMPLE_VOLUME_X_POSITION                                     0x00186039UL 
#define TAG_DOPPLER_SAMPLE_VOLUME_Y_POSITION                                     0x0018603BUL
#define TAG_TM_LINE_POSITION_X_0                                                 0x0018603CUL
#define TAG_TM_LINE_POSITION_X0                                                  0x0018603DUL 
#define TAG_TM_LINE_POSITION_Y_0                                                 0x0018603FUL 
#define TAG_TM_LINE_POSITION_X_1                                                 0x00186041UL 
#define TAG_TM_LINE_POSITION_Y_1                                                 0x00186043UL 
#define TAG_PIXEL_COMPONENT_ORGANIZATION                                         0x00186044UL
#define TAG_PIXEL_COMPONENT_MASK                                                 0x00186046UL
#define TAG_PIXEL_COMPONENT_RANGE_START                                          0x00186048UL
#define TAG_PIXEL_COMPONENT_RANGE_STOP                                           0x0018604AUL
#define TAG_PIXEL_COMPONENT_PHYSICAL_UNITS                                       0x0018604CUL
#define TAG_PIXEL_COMPONENT_DATA_TYPE                                            0x0018604EUL
#define TAG_NUMBER_OF_TABLE_BREAK_POINTS                                         0x00186050UL
#define TAG_TABLE_OF_X_BREAK_POINTS                                              0x00186052UL
#define TAG_TABLE_OF_Y_BREAK_POINTS                                              0x00186054UL
#define TAG_NUMBER_OF_TABLE_ENTRIES                                              0x00186056UL
#define TAG_TABLE_OF_PIXEL_VALUES                                                0x00186058UL
#define TAG_TABLE_OF_PARAMETER_VALUES                                            0x0018605AUL
#define TAG_DETECTOR_CONDITIONS_NOMINAL_FLAG                                     0x00187000UL
#define TAG_DETECTOR_TEMPERATURE                                                 0x00187001UL
#define TAG_DETECTOR_TYPE                                                        0x00187004UL
#define TAG_DETECTOR_CONFIGURATION                                               0x00187005UL
#define TAG_DETECTOR_DESCRIPTION                                                 0x00187006UL
#define TAG_DETECTOR_MODE                                                        0x00187008UL
#define TAG_DETECTOR_ID                                                          0x0018700AUL
#define TAG_DATE_OF_LAST_DETECTOR_CALIBRATION                                    0x0018700CUL
#define TAG_TIME_OF_LAST_DETECTOR_CALIBRATION                                    0x0018700EUL
#define TAG_EXPOSURES_ON_DETECTOR_SINCE_LAST_CALIBRATION                         0x00187010UL
#define TAG_EXPOSURES_ON_DETECTOR_SINCE_MANUFACTURED                             0x00187011UL
#define TAG_DETECTOR_TIME_SINCE_LAST_EXPOSURE                                    0x00187012UL
#define TAG_DETECTOR_ACTIVE_TIME                                                 0x00187014UL
#define TAG_DETECTOR_ACTIVATION_OFFSET_FROM_EXPOSURE                             0x00187016UL
#define TAG_DETECTOR_BINNING                                                     0x0018701AUL
#define TAG_DETECTOR_ELEMENT_PHYSICAL_SIZE                                       0x00187020UL
#define TAG_DETECTOR_ELEMENT_SPACING                                             0x00187022UL
#define TAG_DETECTOR_ACTIVE_SHAPE                                                0x00187024UL
#define TAG_DETECTOR_ACTIVE_DIMENSIONS                                           0x00187026UL
#define TAG_DETECTOR_ACTIVE_ORIGIN                                               0x00187028UL
#define TAG_FIELD_OF_VIEW_ORIGIN                                                 0x00187030UL
#define TAG_FIELD_OF_VIEW_ROTATION                                               0x00187032UL
#define TAG_FIELD_OF_VIEW_HORIZONTAL_FLIP                                        0x00187034UL
#define TAG_GRID_ABSORBING_MATERIAL                                              0x00187040UL
#define TAG_GRID_SPACING_MATERIAL                                                0x00187041UL
#define TAG_GRID_THICKNESS                                                       0x00187042UL
#define TAG_GRID_PITCH                                                           0x00187044UL
#define TAG_GRID_ASPECT_RATIO                                                    0x00187046UL
#define TAG_GRID_PERIOD                                                          0x00187048UL
#define TAG_GRID_FOCAL_DISTANCE                                                  0x0018704CUL
#define TAG_FILTER_MATERIAL                                                      0x00187050UL
#define TAG_FILTER_THICKNESS_MINIMUM                                             0x00187052UL
#define TAG_FILTER_THICKNESS_MAXIMUM                                             0x00187054UL
#define TAG_EXPOSURE_CONTROL_MODE                                                0x00187060UL
#define TAG_EXPOSURE_CONTROL_MODE_DESCRIPTION                                    0x00187062UL
#define TAG_EXPOSURE_STATUS                                                      0x00187064UL
#define TAG_PHOTOTIMER_SETTING                                                   0x00187065UL
#define TAG_EXPOSURE_TIME_IN_NANO_S                                              0x00188150UL
#define TAG_XRAY_TUBE_CURRENT_IN_NANO_A                                          0x00188151UL
#define TAG_CONTENT_QUALIFICATION                                                0x00189004UL
#define TAG_PULSE_SEQUENCE_NAME                                                  0x00189005UL
#define TAG_MR_IMAGING_MODIFIER_SEQUENCE                                         0x00189006UL
#define TAG_ECHO_PULSE_SEQUENCE                                                  0x00189008UL
#define TAG_INVERSION_RECOVERY                                                   0x00189009UL 
#define TAG_FLOW_COMPENSATION                                                    0x00189010UL 
#define TAG_MULTIPLE_SPIN_ECHO                                                   0x00189011UL 
#define TAG_MULTI_PLANAR_EXCITATION                                              0x00189012UL 
#define TAG_PHASE_CONTRAST                                                       0x00189014UL 
#define TAG_TIME_OF_FLIGHT_CONTRAST                                              0x00189015UL 
#define TAG_SPOILING                                                             0x00189016UL 
#define TAG_STEADY_STATE_PULSE_SEQUENCE                                          0x00189017UL 
#define TAG_ECHO_PLANAR_PULSE_SEQUENCE                                           0x00189018UL 
#define TAG_TAG_ANGLE_FIRST_AXIS                                                 0x00189019UL 
#define TAG_MAGNETIZATION_TRANSFER                                               0x00189020UL 
#define TAG_T2_PREPARATION                                                       0x00189021UL 
#define TAG_BLOOD_SIGNAL_NULLING                                                 0x00189022UL 
#define TAG_SATURATION_RECOVERY                                                  0x00189024UL 
#define TAG_SPECTRALLY_SELECTED_SUPPRESSION                                      0x00189025UL 
#define TAG_SPECTRALLY_SELECTED_EXCITATION                                       0x00189026UL 
#define TAG_SPATIAL_PRE_SATURATION                                               0x00189027UL 
#define TAG_TAGGING                                                              0x00189028UL 
#define TAG_OVERSAMPLING_PHASE                                                   0x00189029UL 
#define TAG_TAG_SPACING_FIRST_DIMENSION                                          0x00189030UL 
#define TAG_GEOMETRY_OF_K_SPACE_TRAVERSAL                                        0x00189032UL 
#define TAG_SEGMENTED_K_SPACE_TRAVERSAL                                          0x00189033UL 
#define TAG_RECTILINEAR_PHASE_ENCODE_REORDERING                                  0x00189034UL 
#define TAG_TAG_THICKNESS                                                        0x00189035UL 
#define TAG_PARTIAL_FOURIER_DIRECTION                                            0x00189036UL 
#define TAG_CARDIAC_SYNCHRONIZATION_TECHNIQUE                                    0x00189037UL 
#define TAG_RECEIVE_COIL_MANUFACTURER_NAME                                       0x00189041UL 
#define TAG_MR_RECEIVE_COIL_SEQUENCE                                             0x00189042UL 
#define TAG_RECEIVE_COIL_TYPE                                                    0x00189043UL 
#define TAG_QUADRATURE_RECEIVE_COIL                                              0x00189044UL
#define TAG_MULTI_COIL_DEFINITION_SEQUENCE                                       0x00189045UL
#define TAG_MULTI_COIL_CONFIGURATION                                             0x00189046UL
#define TAG_MULTI_COIL_ELEMENT_NAME                                              0x00189047UL
#define TAG_MULTI_COIL_ELEMENT_USED                                              0x00189048UL  
#define TAG_MR_TRANSMIT_COIL_SEQUENCE                                            0x00189049UL  
#define TAG_TRANSMIT_COIL_MANUFACTURER_NAME                                      0x00189050UL  
#define TAG_TRANSMIT_COIL_TYPE                                                   0x00189051UL  
#define TAG_SPECTRAL_WIDTH                                                       0x00189052UL
#define TAG_CHEMICAL_SHIFT_REFERENCE                                             0x00189053UL  
#define TAG_VOLUME_LOCALIZATION_TECHNIQUE                                        0x00189054UL  
#define TAG_MR_ACQUISITION_FREQUENCY_ENCODING_STEPS                              0x00189058UL  
#define TAG_DE_COUPLING                                                          0x00189059UL  
#define TAG_DE_COUPLED_NUCLEUS                                                   0x00189060UL  
#define TAG_DE_COUPLING_FREQUENCY                                                0x00189061UL  
#define TAG_DE_COUPLING_METHOD                                                   0x00189062UL  
#define TAG_DE_COUPLING_CHEMICAL_SHIFT_REFERENCE                                 0x00189063UL  
#define TAG_K_SPACE_FILTERING                                                    0x00189064UL  
#define TAG_TIME_DOMAIN_FILTERING                                                0x00189065UL  
#define TAG_NUMBER_OF_ZERO_FILLS                                                 0x00189066UL  
#define TAG_BASELINE_CORRECTION                                                  0x00189067UL  
#define TAG_PARALLEL_REDUCTION_FACTOR_IN_PLANE                                   0x00189069UL  
#define TAG_CARDIAC_R_R_INTERVAL_SPECIFIED                                       0x00189070UL  
#define TAG_ACQUISITION_DURATION                                                 0x00189073UL  
#define TAG_FRAME_ACQUISITION_DATETIME                                           0x00189074UL  
#define TAG_DIFFUSION_DIRECTIONALITY                                             0x00189075UL  
#define TAG_DIFFUSION_GRADIENT_DIRECTION_SEQUENCE                                0x00189076UL  
#define TAG_PARALLEL_ACQUISITION                                                 0x00189077UL  
#define TAG_PARALLEL_ACQUISITION_TECHNIQUE                                       0x00189078UL  
#define TAG_INVERSION_TIMES                                                      0x00189079UL  
#define TAG_METABOLITE_MAP_DESCRIPTION                                           0x00189080UL  
#define TAG_PARTIAL_FOURIER                                                      0x00189081UL  
#define TAG_EFFECTIVE_ECHO_TIME                                                  0x00189082UL  
#define TAG_CHEMICAL_SHIFT_SEQUENCE                                              0x00189084UL
#define TAG_CARDIAC_SIGNAL_SOURCE                                                0x00189085UL
#define TAG_DIFFUSION_B_VALUE                                                    0x00189087UL
#define TAG_DIFFUSION_GRADIENT_ORIENTATION                                       0x00189089UL
#define TAG_VELOCITY_ENCODING_DIRECTION                                          0x00189090UL
#define TAG_VELOCITY_ENCODING_MINIMUM_VALUE                                      0x00189091UL
#define TAG_NUMBER_OF_K_SPACE_TRAJECTORIES                                       0x00189093UL
#define TAG_COVERAGE_OF_K_SPACE                                                  0x00189094UL
#define TAG_SPECTROSCOPY_ACQUISITION_PHASE_ROWS                                  0x00189095UL
#define TAG_TRANSMITTER_FREQUENCY                                                0x00189098UL
#define TAG_RESONANT_NUCLEUS                                                     0x00189100UL
#define TAG_FREQUENCY_CORRECTION                                                 0x00189101UL
#define TAG_MR_SPECTROSCOPY_FOV_GEOMETRY_SEQUENCE                                0x00189103UL
#define TAG_SLAB_THICKNESS                                                       0x00189104UL
#define TAG_SLAB_ORIENTATION                                                     0x00189105UL
#define TAG_MID_SLAB_POSITION                                                    0x00189106UL
#define TAG_MR_SPATIAL_SATURATION_SEQUENCE                                       0x00189107UL
#define TAG_MR_TIMING_AND_RELATED_PARAMETERS_SEQUENCE                            0x00189112UL
#define TAG_MR_ECHO_SEQUENCE                                                     0x00189114UL
#define TAG_MR_MODIFIER_SEQUENCE                                                 0x00189115UL
#define TAG_MR_DIFFUSION_SEQUENCE                                                0x00189117UL
#define TAG_CARDIAC_TRIGGER_SEQUENCE                                             0x00189118UL
#define TAG_MR_AVERAGES_SEQUENCE                                                 0x00189119UL
#define TAG_MR_FOV_GEOMETRY_SEQUENCE                                             0x00189125UL
#define TAG_VOLUME_LOCALIZATION_SEQUENCE                                         0x00189126UL
#define TAG_SPECTROSCOPY_ACQUISITION_DATA_COLUMNS                                0x00189127UL
#define TAG_DIFFUSION_ANISOTROPY_TYPE                                            0x00189147UL
#define TAG_FRAME_REFERENCE_DATETIME                                             0x00189151UL
#define TAG_MR_METABOLITE_MAP_SEQUENCE                                           0x00189152UL
#define TAG_PARALLEL_REDUCTION_FACTOR_OUT_OF_PLANE                               0x00189155UL
#define TAG_SPECTROSCOPY_ACQUISITION_OUT_OF_PLANE_PHASE_STEPS                    0x00189159UL
#define TAG_BULK_MOTION_STATUS                                                   0x00189166UL
#define TAG_PARALLEL_REDUCTION_FACTOR_SECOND_IN_PLANE                            0x00189168UL
#define TAG_CARDIAC_BEAT_REJECTION_TECHNIQUE                                     0x00189169UL
#define TAG_RESPIRATORY_MOTION_COMPENSATION_TECHNIQUE                            0x00189170UL
#define TAG_RESPIRATORY_SIGNAL_SOURCE                                            0x00189171UL
#define TAG_BULK_MOTION_COMPENSATION_TECHNIQUE                                   0x00189172UL
#define TAG_BULK_MOTION_SIGNAL_SOURCE                                            0x00189173UL
#define TAG_APPLICABLE_SAFETY_STANDARD_AGENCY                                    0x00189174UL
#define TAG_APPLICABLE_SAFETY_STANDARD_DESCRIPTION                               0x00189175UL
#define TAG_OPERATING_MODE_SEQUENCE                                              0x00189176UL
#define TAG_OPERATING_MODE_TYPE                                                  0x00189177UL
#define TAG_OPERATING_MODE                                                       0x00189178UL
#define TAG_SPECIFIC_ABSORPTION_RATE_DEFINITION                                  0x00189179UL
#define TAG_GRADIENT_OUTPUT_TYPE                                                 0x00189180UL
#define TAG_SPECIFIC_ABSORPTION_RATE_VALUE                                       0x00189181UL
#define TAG_GRADIENT_OUTPUT                                                      0x00189182UL
#define TAG_FLOW_COMPENSATION_DIRECTION                                          0x00189183UL
#define TAG_TAGGING_DELAY                                                        0x00189184UL
#define TAG_CHEMICAL_SHIFTS_MINIMUM_INTEGRATION_LIMIT                            0x00189195UL
#define TAG_CHEMICAL_SHIFTS_MAXIMUM_INTEGRATION_LIMIT                            0x00189196UL
#define TAG_MR_VELOCITY_ENCODING_SEQUENCE                                        0x00189197UL
#define TAG_FIRST_ORDER_PHASE_CORRECTION                                         0x00189198UL
#define TAG_WATER_REFERENCED_PHASE_CORRECTION                                    0x00189199UL
#define TAG_MR_SPECTROSCOPY_ACQUISITION_TYPE                                     0x00189200UL
#define TAG_RESPIRATORY_CYCLE_POSITION                                           0x00189214UL
#define TAG_VELOCITY_ENCODING_MAXIMUM_VALUE                                      0x00189217UL
#define TAG_TAG_SPACING_SECOND_DIMENSION                                         0x00189218UL
#define TAG_TAG_ANGLE_SECOND_AXIS                                                0x00189219UL
#define TAG_FRAME_ACQUISITION_DURATION                                           0x00189220UL
#define TAG_MR_IMAGE_FRAME_TYPE_SEQUENCE                                         0x00189226UL
#define TAG_MR_SPECTROSCOPY_FRAME_TYPE_SEQUENCE                                  0x00189227UL
#define TAG_MR_ACQUISITION_PHASE_ENCODING_STEPS_IN_PLANE                         0x00189231UL
#define TAG_MR_ACQUISITION_PHASE_ENCODING_STEPS_OUT_OF_PLANE                     0x00189232UL
#define TAG_SPECTROSCOPY_ACQUISITION_PHASE_COLUMNS                               0x00189234UL
#define TAG_CARDIAC_CYCLE_POSITION                                               0x00189236UL
#define TAG_SPECIFIC_ABSORPTION_RATE_SEQUENCE                                    0x00189239UL
#define TAG_CONTRIBUTING_EQUIPMENT_SEQUENCE                                      0x0018A001UL
#define TAG_CONTRIBUTION_DATETIME                                                0x0018A002UL
#define TAG_CONTRIBUTION_DESCRIPTION                                             0x0018A003UL 
#define TAG_STUDY_INSTANCE_UID                                                   0x0020000DUL
#define TAG_SERIES_INSTANCE_UID                                                  0x0020000EUL
#define TAG_STUDY_ID                                                             0x00200010UL
#define TAG_SERIES_NUMBER                                                        0x00200011UL
#define TAG_ACQUISITION_NUMBER                                                   0x00200012UL
#define TAG_INSTANCE_NUMBER                                                      0x00200013UL
#define TAG_ISOTOPE_NUMBER_RETIRED                                               0x00200014UL
#define TAG_PHASE_NUMBER_RETIRED                                                 0x00200015UL
#define TAG_INTERVAL_NUMBER_RETIRED                                              0x00200016UL
#define TAG_TIME_SLOT_NUMBER_RETIRED                                             0x00200017UL
#define TAG_ANGLE_NUMBER_RETIRED                                                 0x00200018UL
#define TAG_ITEM_NUMBER                                                          0x00200019UL
#define TAG_PATIENT_ORIENTATION                                                  0x00200020UL
#define TAG_OVERLAY_NUMBER                                                       0x00200022UL
#define TAG_CURVE_NUMBER                                                         0x00200024UL
#define TAG_LOOKUP_TABLE_NUMBER                                                  0x00200026UL
#define TAG_IMAGE_POSITION_PATIENT                                               0x00200032UL
#define TAG_IMAGE_ORIENTATION_PATIENT                                            0x00200037UL
#define TAG_FRAME_OF_REFERENCE_UID                                               0x00200052UL
#define TAG_LATERALITY                                                           0x00200060UL
#define TAG_IMAGE_LATERALITY                                                     0x00200062UL
#define TAG_TEMPORAL_POSITION_IDENTIFIER                                         0x00200100UL
#define TAG_NUMBER_OF_TEMPORAL_POSITIONS                                         0x00200105UL
#define TAG_TEMPORAL_RESOLUTION                                                  0x00200110UL
#define TAG_SYNCHRONIZATION_FRAME_OF_REFERENCE_UID                               0x00200200UL
#define TAG_SERIES_IN_STUDY                                                      0x00201000UL
#define TAG_IMAGES_IN_ACQUISITION                                                0x00201002UL
#define TAG_IMAGES_IN_SERIES                                                     0x00201003UL
#define TAG_ACQUISITIONS_IN_STUDY                                                0x00201004UL
#define TAG_POSITION_REFERENCE_INDICATOR                                         0x00201040UL
#define TAG_SLICE_LOCATION                                                       0x00201041UL
#define TAG_OTHER_STUDY_NUMBERS                                                  0x00201070UL
#define TAG_NUMBER_OF_PATIENT_RELATED_STUDIES                                    0x00201200UL
#define TAG_NUMBER_OF_PATIENT_RELATED_SERIES                                     0x00201202UL
#define TAG_NUMBER_OF_PATIENT_RELATED_INSTANCES                                  0x00201204UL
#define TAG_NUMBER_OF_STUDY_RELATED_SERIES                                       0x00201206UL
#define TAG_NUMBER_OF_STUDY_RELATED_INSTANCES                                    0x00201208UL
#define TAG_NUMBER_OF_SERIES_RELATED_INSTANCES                                   0x00201209UL
#define TAG_IMAGE_COMMENTS                                                       0x00204000UL
#define TAG_STACK_ID                                                             0x00209056UL
#define TAG_IN_STACK_POSITION_NUMBER                                             0x00209057UL
#define TAG_FRAME_ANATOMY_SEQUENCE                                               0x00209071UL
#define TAG_FRAME_LATERALITY                                                     0x00209072UL
#define TAG_FRAME_CONTENT_SEQUENCE                                               0x00209111UL
#define TAG_PLANE_POSITION_SEQUENCE                                              0x00209113UL
#define TAG_PLANE_ORIENTATION_SEQUENCE                                           0x00209116UL
#define TAG_TEMPORAL_POSITION_INDEX                                              0x00209128UL
#define TAG_TRIGGER_DELAY_TIME                                                   0x00209153UL
#define TAG_FRAME_ACQUISITION_NUMBER                                             0x00209156UL
#define TAG_DIMENSION_INDEX_VALUES                                               0x00209157UL
#define TAG_FRAME_COMMENTS                                                       0x00209158UL
#define TAG_CONCATENATION_UID                                                    0x00209161UL
#define TAG_IN_CONCATENATION_NUMBER                                              0x00209162UL
#define TAG_IN_CONCATENATION_TOTAL_NUMBER                                        0x00209163UL
#define TAG_DIMENSION_ORGANIZATION_UID                                           0x00209164UL
#define TAG_DIMENSION_INDEX_POINTER                                              0x00209165UL
#define TAG_FUNCTIONAL_GROUP_POINTER                                             0x00209167UL
#define TAG_DIMENSION_INDEX_PRIVATE_CREATOR                                      0x00209213UL
#define TAG_DIMENSION_ORGANIZATION_SEQUENCE                                      0x00209221UL
#define TAG_DIMENSION_INDEX_SEQUENCE                                             0x00209222UL
#define TAG_CONCATENATION_FRAME_OFFSET_NUMBER                                    0x00209228UL
#define TAG_FUNCTIONAL_GROUP_PRIVATE_CREATOR                                     0x00209238UL                                                                                 
#define TAG_SAMPLES_PER_PIXEL                                                    0x00280002UL
#define TAG_PHOTOMETRIC_INTERPRETATION                                           0x00280004UL
#define TAG_PLANAR_CONFIGURATION                                                 0x00280006UL
#define TAG_NUMBER_OF_FRAMES                                                     0x00280008UL
#define TAG_FRAME_INCREMENT_POINTER                                              0x00280009UL
#define TAG_ROWS                                                                 0x00280010UL
#define TAG_COLUMNS                                                              0x00280011UL
#define TAG_PLANES                                                               0x00280012UL
#define TAG_ULTRASOUND_COLOR_DATA_PRESENT                                        0x00280014UL
#define TAG_PIXEL_SPACING                                                        0x00280030UL
#define TAG_ZOOM_FACTOR                                                          0x00280031UL
#define TAG_ZOOM_CENTER                                                          0x00280032UL
#define TAG_PIXEL_ASPECT_RATIO                                                   0x00280034UL
#define TAG_CORRECTED_IMAGE                                                      0x00280051UL
#define TAG_BITS_ALLOCATED                                                       0x00280100UL
#define TAG_BITS_STORED                                                          0x00280101UL
#define TAG_HIGH_BIT                                                             0x00280102UL
#define TAG_PIXEL_REPRESENTATION                                                 0x00280103UL
#define TAG_SMALLEST_IMAGE_PIXEL_VALUE                                           0x00280106UL
#define TAG_LARGEST_IMAGE_PIXEL_VALUE                                            0x00280107UL
#define TAG_SMALLEST_PIXEL_VALUE_IN_SERIES                                       0x00280108UL
#define TAG_LARGEST_PIXEL_VALUE_IN_SERIES                                        0x00280109UL
#define TAG_SMALLEST_IMAGE_PIXEL_VALUE_IN_PLANE                                  0x00280110UL
#define TAG_LARGEST_IMAGE_PIXEL_VALUE_IN_PLANE                                   0x00280111UL
#define TAG_PIXEL_PADDING_VALUE                                                  0x00280120UL
#define TAG_BURNED_IN_ANNOTATION                                                 0x00280301UL
#define TAG_PIXEL_INTENSITY_RELATIONSHIP                                         0x00281040UL
#define TAG_PIXEL_INTENSITY_RELATIONSHIP_SIGN                                    0x00281041UL
#define TAG_WINDOW_CENTER                                                        0x00281050UL
#define TAG_WINDOW_WIDTH                                                         0x00281051UL
#define TAG_RESCALE_INTERCEPT                                                    0x00281052UL
#define TAG_RESCALE_SLOPE                                                        0x00281053UL
#define TAG_RESCALE_TYPE                                                         0x00281054UL
#define TAG_WINDOW_CENTER_WIDTH_EXPLANATION                                      0x00281055UL
#define TAG_RECOMMENDED_VIEWING_MODE                                             0x00281090UL
#define TAG_RED_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR                            0x00281101UL
#define TAG_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR                          0x00281102UL
#define TAG_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DESCRIPTOR                           0x00281103UL
#define TAG_PALETTE_COLOR_LOOKUP_TABLE_UID                                       0x00281199UL
#define TAG_RED_PALETTE_COLOR_LOOKUP_TABLE_DATA                                  0x00281201UL
#define TAG_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DATA                                0x00281202UL
#define TAG_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DATA                                 0x00281203UL
#define TAG_SEGMENTED_RED_PALETTE_COLOR_LOOKUP_TABLE_DATA                        0x00281221UL
#define TAG_SEGMENTED_GREEN_PALETTE_COLOR_LOOKUP_TABLE_DATA                      0x00281222UL
#define TAG_SEGMENTED_BLUE_PALETTE_COLOR_LOOKUP_TABLE_DATA                       0x00281223UL
#define TAG_PARTIAL_VIEW                                                         0x00281350UL
#define TAG_PARTIAL_VIEW_DESCRIPTION                                             0x00281351UL
#define TAG_LOSSY_IMAGE_COMPRESSION                                              0x00282110UL
#define TAG_LOSSY_IMAGE_COMPRESSION_RATIO                                        0x00282112UL
#define TAG_MODALITY_LUT_SEQUENCE                                                0x00283000UL
#define TAG_LUT_DESCRIPTOR                                                       0x00283002UL
#define TAG_LUT_EXPLANATION                                                      0x00283003UL
#define TAG_MODALITY_LUT_TYPE                                                    0x00283004UL
#define TAG_LUT_DATA                                                             0x00283006UL
#define TAG_VOI_LUT_SEQUENCE                                                     0x00283010UL
#define TAG_SOFTCOPY_VOI_LUT_SEQUENCE                                            0x00283110UL
#define TAG_BIPLANE_ACQUISITION_SEQUENCE                                         0x00285000UL
#define TAG_REPRESENTATIVE_FRAME_NUMBER                                          0x00286010UL
#define TAG_FRAME_NUMBERS_OF_INTEREST_FOI                                        0x00286020UL
#define TAG_FRAME_OF_INTEREST_DESCRIPTION                                        0x00286022UL
#define TAG_MASK_POINTER_RETIRED                                                 0x00286030UL
#define TAG_R_WAVE_POINTER                                                       0x00286040UL
#define TAG_MASK_SUBTRACTION_SEQUENCE                                            0x00286100UL
#define TAG_MASK_OPERATION                                                       0x00286101UL
#define TAG_APPLICABLE_FRAME_RANGE                                               0x00286102UL
#define TAG_MASK_FRAME_NUMBERS                                                   0x00286110UL
#define TAG_CONTRAST_FRAME_AVERAGING                                             0x00286112UL
#define TAG_MASK_SUB_PIXEL_SHIFT                                                 0x00286114UL
#define TAG_TID_OFFSET                                                           0x00286120UL
#define TAG_MASK_OPERATION_EXPLANATION                                           0x00286190UL
#define TAG_DATA_POINT_ROWS                                                      0x00289001UL
#define TAG_DATA_POINT_COLUMNS                                                   0x00289002UL
#define TAG_SIGNAL_DOMAIN_COLUMNS                                                0x00289003UL
#define TAG_LARGEST_MONOCHROME_PIXEL_VALUE                                       0x00289099UL
#define TAG_DATA_REPRESENTATION                                                  0x00289108UL
#define TAG_PIXEL_MEASURES_SEQUENCE                                              0x00289110UL
#define TAG_FRAME_VOI_LUT_SEQUENCE                                               0x00289132UL
#define TAG_PIXEL_VALUE_TRANSFORMATION_SEQUENCE                                  0x00289145UL
#define TAG_SIGNAL_DOMAIN_ROWS                                                   0x00289235UL                                                                                 
#define TAG_STUDY_STATUS_ID                                                      0x0032000AUL
#define TAG_STUDY_PRIORITY_ID                                                    0x0032000CUL
#define TAG_STUDY_ID_ISSUER                                                      0x00320012UL
#define TAG_STUDY_VERIFIED_DATE                                                  0x00320032UL
#define TAG_STUDY_VERIFIED_TIME                                                  0x00320033UL
#define TAG_STUDY_READ_DATE                                                      0x00320034UL
#define TAG_STUDY_READ_TIME                                                      0x00320035UL
#define TAG_SCHEDULED_STUDY_START_DATE                                           0x00321000UL
#define TAG_SCHEDULED_STUDY_START_TIME                                           0x00321001UL
#define TAG_SCHEDULED_STUDY_STOP_DATE                                            0x00321010UL
#define TAG_SCHEDULED_STUDY_STOP_TIME                                            0x00321011UL
#define TAG_SCHEDULED_STUDY_LOCATION                                             0x00321020UL
#define TAG_SCHEDULED_STUDY_LOCATION_AE_TITLE                                    0x00321021UL
#define TAG_REASON_FOR_STUDY                                                     0x00321030UL
#define TAG_REQUESTING_PHYSICIAN_IDENTIFICATION_SEQUENCE                         0x00321031UL 
#define TAG_REQUESTING_PHYSICIAN                                                 0x00321032UL
#define TAG_REQUESTING_SERVICE                                                   0x00321033UL
#define TAG_STUDY_ARRIVAL_DATE                                                   0x00321040UL
#define TAG_STUDY_ARRIVAL_TIME                                                   0x00321041UL
#define TAG_STUDY_COMPLETION_DATE                                                0x00321050UL
#define TAG_STUDY_COMPLETION_TIME                                                0x00321051UL
#define TAG_STUDY_COMPONENT_STATUS_ID                                            0x00321055UL
#define TAG_REQUESTED_PROCEDURE_DESCRIPTION                                      0x00321060UL
#define TAG_REQUESTED_PROCEDURE_CODE_SEQUENCE                                    0x00321064UL
#define TAG_REQUESTED_CONTRAST_AGENT                                             0x00321070UL
#define TAG_STUDY_COMMENTS                                                       0x00324000UL
                                                                                 
#define TAG_REFERENCED_PATIENT_ALIAS_SEQUENCE                                    0x00380004UL
#define TAG_VISIT_STATUS_ID                                                      0x00380008UL
#define TAG_ADMISSION_ID                                                         0x00380010UL
#define TAG_ISSUER_OF_ADMISSION_ID                                               0x00380011UL
#define TAG_ROUTE_OF_ADMISSIONS                                                  0x00380016UL
#define TAG_SCHEDULED_ADMISSION_DATE                                             0x0038001AUL
#define TAG_SCHEDULED_ADMISSION_TIME                                             0x0038001BUL
#define TAG_SCHEDULED_DISCHARGE_DATE                                             0x0038001CUL
#define TAG_SCHEDULED_DISCHARGE_TIME                                             0x0038001DUL
#define TAG_SCHEDULED_PATIENT_INSTITUTION_RESIDENCE                              0x0038001EUL
#define TAG_ADMITTING_DATE                                                       0x00380020UL
#define TAG_ADMITTING_TIME                                                       0x00380021UL
#define TAG_DISCHARGE_DATE                                                       0x00380030UL
#define TAG_DISCHARGE_TIME                                                       0x00380032UL
#define TAG_DISCHARGE_DIAGNOSIS_DESCRIPTION                                      0x00380040UL
#define TAG_DISCHARGE_DIAGNOSIS_CODE_SEQUENCE                                    0x00380044UL
#define TAG_SPECIAL_NEEDS                                                        0x00380050UL
#define TAG_CURRENT_PATIENT_LOCATION                                             0x00380300UL
#define TAG_PATIENT_INSTITUTION_RESIDENCE                                        0x00380400UL
#define TAG_PATIENT_STATE                                                        0x00380500UL
#define TAG_VISIT_COMMENTS                                                       0x00384000UL
                                                                                 
#define TAG_WAVEFORM_SEQUENCE                                                    0x003A0002UL
#define TAG_WAVEFORM_ORIGINALITY                                                 0x003A0004UL
#define TAG_NUMBER_OF_WAVEFORM_CHANNELS                                          0x003A0005UL
#define TAG_NUMBER_OF_WAVEFORM_SAMPLES                                           0x003A0010UL
#define TAG_SAMPLING_FREQUENCY                                                   0x003A001AUL
#define TAG_MULTIPLEX_GROUP_LABEL                                                0x003A0020UL
#define TAG_WAVEFORM_SAMPLE_VALUE_REPRESENTATION                                 0x003A0103UL
#define TAG_WAVEFORM_PADDING_VALUE                                               0x003A0122UL
#define TAG_CHANNEL_DEFINITION_SEQUENCE                                          0x003A0200UL
#define TAG_WAVEFORM_CHANNEL_NUMBER                                              0x003A0202UL
#define TAG_CHANNEL_LABEL                                                        0x003A0203UL
#define TAG_CHANNEL_STATUS                                                       0x003A0205UL
#define TAG_CHANNEL_SOURCE_SEQUENCE                                              0x003A0208UL
#define TAG_CHANNEL_SOURCE_MODIFIERS_SEQUENCE                                    0x003A0209UL
#define TAG_SOURCE_WAVEFORM_SEQUENCE                                             0x003A020AUL
#define TAG_DIFFERENTIAL_CHANNEL_SOURCE_MODIFIERS                                0x003A020BUL
#define TAG_CHANNEL_DERIVATION_DESCRIPTION                                       0x003A020CUL
#define TAG_CHANNEL_SENSITIVITY                                                  0x003A0210UL
#define TAG_CHANNEL_SENSITIVITY_UNITS_SEQUENCE                                   0x003A0211UL
#define TAG_CHANNEL_SENSITIVITY_CORRECTION_FACTOR                                0x003A0212UL
#define TAG_CHANNEL_BASELINE                                                     0x003A0213UL
#define TAG_CHANNEL_TIME_SKEW                                                    0x003A0214UL
#define TAG_CHANNEL_SAMPLE_SKEW                                                  0x003A0215UL
#define TAG_CHANNEL_MINIMUM_VALUE                                                0x003A0216UL
#define TAG_CHANNEL_MAXIMUM_VALUE                                                0x003A0217UL
#define TAG_CHANNEL_OFFSET                                                       0x003A0218UL
#define TAG_WAVEFORM_BITS_STORED                                                 0x003A021AUL
#define TAG_FILTER_LOW_FREQUENCY                                                 0x003A0220UL
#define TAG_FILTER_HIGH_FREQUENCY                                                0x003A0221UL
#define TAG_NOTCH_FILTER_FREQUENCY                                               0x003A0222UL
#define TAG_NOTCH_FILTER_BANDWIDTH                                               0x003A0223UL
#define TAG_WAVEFORM_DATA                                                        0x003A1000UL
                                                                                 
#define TAG_SCHEDULED_STATION_AE_TITLE                                           0x00400001UL
#define TAG_SCHEDULED_PROCEDURE_STEP_START_DATE                                  0x00400002UL
#define TAG_SCHEDULED_PROCEDURE_STEP_START_TIME                                  0x00400003UL
#define TAG_SCHEDULED_PROCEDURE_STEP_END_DATE                                    0x00400004UL
#define TAG_SCHEDULED_PROCEDURE_STEP_END_TIME                                    0x00400005UL
#define TAG_SCHEDULED_PERFORMING_PHYSICIAN_NAME                                  0x00400006UL
#define TAG_SCHEDULED_PROCEDURE_STEP_DESCRIPTION                                 0x00400007UL
#define TAG_SCHEDULED_ACTION_ITEM_CODE_SEQUENCE                                  0x00400008UL
#define TAG_SCHEDULED_PROCEDURE_STEP_ID                                          0x00400009UL
#define TAG_STAGE_CODE_SEQUENCE                                                  0x0040000AUL
#define TAG_SCHEDULED_PERFORMING_PHYSICIAN_IDENTIFICATION_SEQUENCE               0x0040000BUL

#define TAG_SCHEDULED_STATION_NAME                                               0x00400010UL
#define TAG_SCHEDULED_PROCEDURE_STEP_LOCATION                                    0x00400011UL
#define TAG_PRE_MEDICATION                                                       0x00400012UL
#define TAG_SCHEDULED_PROCEDURE_STEP_STATUS                                      0x00400020UL
#define TAG_SCHEDULED_PROCEDURE_STEP_SEQUENCE                                    0x00400100UL
#define TAG_REFERENCED_STANDALONE_SOP_INSTANCE_SEQUENCE                          0x00400220UL
#define TAG_PERFORMED_STATION_AE_TITLE                                           0x00400241UL
#define TAG_PERFORMED_STATION_NAME                                               0x00400242UL
#define TAG_PERFORMED_LOCATION                                                   0x00400243UL
#define TAG_PERFORMED_PROCEDURE_STEP_START_DATE                                  0x00400244UL
#define TAG_PERFORMED_PROCEDURE_STEP_START_TIME                                  0x00400245UL
#define TAG_PERFORMED_PROCEDURE_STEP_END_DATE                                    0x00400250UL
#define TAG_PERFORMED_PROCEDURE_STEP_END_TIME                                    0x00400251UL
#define TAG_PERFORMED_PROCEDURE_STEP_STATUS                                      0x00400252UL
#define TAG_PERFORMED_PROCEDURE_STEP_ID                                          0x00400253UL
#define TAG_PERFORMED_PROCEDURE_STEP_DESCRIPTION                                 0x00400254UL
#define TAG_PERFORMED_PROCEDURE_TYPE_DESCRIPTION                                 0x00400255UL
#define TAG_PERFORMED_ACTION_ITEM_SEQUENCE                                       0x00400260UL
#define TAG_SCHEDULED_STEP_ATTRIBUTES_SEQUENCE                                   0x00400270UL
#define TAG_REQUEST_ATTRIBUTES_SEQUENCE                                          0x00400275UL
#define TAG_COMMENTS_ON_THE_PERFORMED_PROCEDURE_STEPS                            0x00400280UL
#define TAG_PERFORMED_PROCEDURE_STEP_DISCONTINUATION_REASON_CODE_SEQUENCE        0x00400281UL
#define TAG_QUANTITY_SEQUENCE                                                    0x00400293UL
#define TAG_QUANTITY                                                             0x00400294UL
#define TAG_MEASURING_UNITS_SEQUENCE                                             0x00400295UL
#define TAG_BILLING_ITEM_SEQUENCE                                                0x00400296UL
#define TAG_TOTAL_TIME_OF_FLUOROSCOPY                                            0x00400300UL
#define TAG_TOTAL_NUMBER_OF_EXPOSURES                                            0x00400301UL
#define TAG_ENTRANCE_DOSE                                                        0x00400302UL
#define TAG_EXPOSED_AREA                                                         0x00400303UL
#define TAG_DISTANCE_SOURCE_TO_ENTRANCE                                          0x00400306UL
#define TAG_EXPOSURE_DOSE_SEQUENCE                                               0x0040030EUL 
#define TAG_COMMENTS_ON_RADIATION_DOSE                                           0x00400310UL
#define TAG_ORGAN_EXPOSED                                                        0x00400318UL
#define TAG_BILLING_PROCEDURE_STEP_SEQUENCE                                      0x00400320UL
#define TAG_FILM_CONSUMPTION_SEQUENCE                                            0x00400321UL
#define TAG_BILLING_SUPPLIES_AND_DEVICES_SEQUENCE_RETIRED                        0x00400324UL
#define TAG_REFERENCED_PROCEDURE_STEP_SEQUENCE                                   0x00400330UL
#define TAG_PERFORMED_SERIES_SEQUENCE                                            0x00400340UL
#define TAG_COMMENTS_ON_THE_SCHEDULED_PROCEDURE_STEP                             0x00400400UL
#define TAG_SPECIMEN_ACCESSION_NUMBER                                            0x0040050AUL
#define TAG_SPECIMEN_SEQUENCE                                                    0x00400550UL
#define TAG_ACQUISITION_CONTEXT_SEQUENCE                                         0x00400555UL
#define TAG_REQUESTED_PROCEDURE_ID                                               0x00401001UL
#define TAG_REASON_FOR_THE_REQUESTED_PROCEDURE                                   0x00401002UL
#define TAG_REQUESTED_PROCEDURE_PRIORITY                                         0x00401003UL
#define TAG_PATIENT_TRANSPORT_ARRANGEMENTS                                       0x00401004UL
#define TAG_REQUESTED_PROCEDURE_LOCATION                                         0x00401005UL
#define TAG_PLACER_ORDER_NUMBER_PROCEDURE_RETIRED                                0x00401006UL
#define TAG_FILLER_ORDER_NUMBER_PROCEDURE_RETIRED                                0x00401007UL
#define TAG_CONFIDENTIALITY_CODE                                                 0x00401008UL
#define TAG_REPORTING_PRIORITY                                                   0x00401009UL
#define TAG_NAMES_OF_INTENDED_RECIPIENTS_OF_RESULTS                              0x00401010UL
#define TAG_INTENDED_RECIPIENTS_OF_RESULTS_IDENTIFICATION_SEQUENCE               0x00401011UL
#define TAG_PERSON_IDENTIFICATION_CODE_SEQUENCE                                  0x00401101UL
#define TAG_PERSONS_ADDRESS                                                      0x00401102UL
#define TAG_PERSONS_TELEPHONE_NUMBERS                                            0x00401103UL
#define TAG_REQUESTED_PROCEDURE_COMMENTS                                         0x00401400UL
#define TAG_REASON_FOR_THE_IMAGING_SERVICE_REQUEST                               0x00402001UL
#define TAG_ISSUE_DATE_OF_IMAGING_SERVICE_REQUEST                                0x00402004UL
#define TAG_ISSUE_TIME_OF_IMAGING_SERVICE_REQUEST                                0x00402005UL
#define TAG_PLACER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST_RETIRED                  0x00402006UL
#define TAG_FILLER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST_RETIRED                  0x00402007UL
#define TAG_ORDER_ENTERED_BY                                                     0x00402008UL
#define TAG_ORDER_ENTERER_LOCATION                                               0x00402009UL
#define TAG_ORDER_CALLBACK_PHONE_NUMBER                                          0x00402010UL
#define TAG_PLACER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST                          0x00402016UL
#define TAG_FILLER_ORDER_NUMBER_IMAGING_SERVICE_REQUEST                          0x00402017UL
#define TAG_IMAGING_SERVICE_REQUEST_COMMENTS                                     0x00402400UL
#define TAG_CONFIDENTIALITY_CONSTRAINT_ON_PATIENT_DATA_DESCRIPTION               0x00403001UL

#define TAG_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_STATUS                      0x00404001UL    
#define TAG_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEP_STATUS                      0x00404002UL    
#define TAG_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_PRIORITY                    0x00404003UL    
#define TAG_SCHEDULED_PROCESSING_APPLICATIONS_CODE_SEQUENCE                      0x00404004UL    
#define TAG_SCHEDULED_PROCEDURE_STEP_START_DATE_AND_TIME                         0x00404005UL    
#define TAG_MULTIPLE_COPIES_FLAG                                                 0x00404006UL    
#define TAG_PERFORMED_PROCESSING_APPLICATIONS_CODE_SEQUENCE                      0x00404007UL    
#define TAG_HUMAN_PERFORMER_CODE_SEQUENCE                                        0x00404009UL    
#define TAG_EXPECTED_COMPLETION_DATE_AND_TIME                                    0x00404011UL    
#define TAG_RESULTING_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEPS_SEQUENCE         0x00404015UL    
#define TAG_REFERENCED_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_SEQUENCE         0x00404016UL    
#define TAG_SCHEDULED_WORKITEM_CODE_SEQUENCE                                     0x00404018UL    
#define TAG_PERFORMED_WORKITEM_CODE_SEQUENCE                                     0x00404019UL    
#define TAG_INPUT_AVAILABILITY_FLAG                                              0x00404020UL    
#define TAG_INPUT_INFORMATIONSEQUENCE                                            0x00404021UL    
#define TAG_RELEVANT_INFORMATION_SEQUENCE                                        0x00404022UL    
#define TAG_REFERENCED_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_TRANSACTION_UID  0x00404023UL    
#define TAG_SCHEDULED_STATION_NAME_CODE_SEQUENCE                                 0x00404025UL    
#define TAG_SCHEDULED_STATION_CLASS_CODE_SEQUENCE                                0x00404026UL    
#define TAG_SCHEDULED_STATION_GEOGRAPHIC_LOCATION_CODE_SEQUENCE                  0x00404027UL    
#define TAG_PERFORMED_STATION_NAME_CODE_SEQUENCE                                 0x00404028UL    
#define TAG_PERFORMED_STATION_CLASS_CODE_SEQUENCE                                0x00404029UL    
#define TAG_PERFORMED_STATION_GEOGRAPHIC_LOCATION_CODE_SEQUENCE                  0x00404030UL    
#define TAG_REQUESTED_SUBSEQUENT_WORKITEM_CODE_SEQUENCE                          0x00404031UL    
#define TAG_NON_DICOM_OUTPUT_CODE_SEQUENCE                                       0x00404032UL    
#define TAG_OUTPUT_INFORMATION_SEQUENCE                                          0x00404033UL    
#define TAG_SCHEDULED_HUMAN_PERFORMERS_SEQUENCE                                  0x00404034UL    
#define TAG_ACTUAL_HUMAN_PERFORMERS_SEQUENCE                                     0x00404035UL    
#define TAG_HUMAN_PERFORMER_ORGANIZATION                                         0x00404036UL    
#define TAG_HUMAN_PERFORMER_NAME                                                 0x00404037UL    
#define TAG_REAL_WORLD_VALUE_MAPPING_SEQUENCE                                    0x00409096UL
#define TAG_LUT_LABEL                                                            0x00409210UL
#define TAG_REAL_WORLD_VALUE_LAST_VALUE_MAPPED                                   0x00409211UL
#define TAG_REAL_WORLD_VALUE_LUT_DATA                                            0x00409212UL
#define TAG_REAL_WORLD_VALUE_FIRST_VALUE_MAPPED                                  0x00409216UL
#define TAG_REAL_WORLD_VALUE_INTERCEPT                                           0x00409224UL
#define TAG_REAL_WORLD_VALUE_SLOPE                                               0x00409225UL
#define TAG_PURPOSE_OF_REFERENCE_CODE_SEQUENCE                                   0x0040A170UL 
#define TAG_NUMERIC_VALUE_QUALIFIER_CODE_SEQUENCE                                0x0040A301UL
#define TAG_CALIBRATION_IMAGE                                                    0x00500004UL
#define TAG_DEVICE_SEQUENCE                                                      0x00500010UL
#define TAG_DEVICE_LENGTH                                                        0x00500014UL
#define TAG_DEVICE_DIAMETER                                                      0x00500016UL
#define TAG_DEVICE_DIAMETER_UNITS                                                0x00500017UL
#define TAG_DEVICE_VOLUME                                                        0x00500018UL
#define TAG_INTER_MARKER_DISTANCE                                                0x00500019UL
#define TAG_DEVICE_DESCRIPTION                                                   0x00500020UL

#define TAG_ENERGY_WINDOW_VECTOR                                                 0x00540010UL
#define TAG_NUMBER_OF_ENERGY_WINDOWS                                             0x00540011UL
#define TAG_ENERGY_WINDOW_INFORMATION_SEQUENCE                                   0x00540012UL
#define TAG_ENERGY_WINDOW_RANGE_SEQUENCE                                         0x00540013UL
#define TAG_ENERGY_WINDOW_LOWER_LIMIT                                            0x00540014UL
#define TAG_ENERGY_WINDOW_UPPER_LIMIT                                            0x00540015UL
#define TAG_RADIOPHARMACEUTICAL_INFORMATION_SEQUENCE                             0x00540016UL
#define TAG_RESIDUAL_SYRINGE_COUNTS                                              0x00540017UL
#define TAG_ENERGY_WINDOW_NAME                                                   0x00540018UL
#define TAG_DETECTOR_VECTOR                                                      0x00540020UL
#define TAG_NUMBER_OF_DETECTORS                                                  0x00540021UL
#define TAG_DETECTOR_INFORMATION_SEQUENCE                                        0x00540022UL
#define TAG_PHASE_VECTOR                                                         0x00540030UL
#define TAG_NUMBER_OF_PHASES                                                     0x00540031UL
#define TAG_PHASE_INFORMATION_SEQUENCE                                           0x00540032UL
#define TAG_NUMBER_OF_FRAMES_IN_PHASE                                            0x00540033UL
#define TAG_PHASE_DELAY                                                          0x00540036UL
#define TAG_PAUSE_BETWEEN_FRAMES                                                 0x00540038UL
#define TAG_ROTATION_VECTOR                                                      0x00540050UL
#define TAG_NUMBER_OF_ROTATIONS                                                  0x00540051UL
#define TAG_ROTATION_INFORMATION_SEQUENCE                                        0x00540052UL
#define TAG_NUMBER_OF_FRAMES_IN_ROTATION                                         0x00540053UL
#define TAG_R_R_INTERVAL_VECTOR                                                  0x00540060UL
#define TAG_NUMBER_OF_R_R_INTERVALS                                              0x00540061UL
#define TAG_GATED_INFORMATION_SEQUENCE                                           0x00540062UL
#define TAG_DATA_INFORMATION_SEQUENCE                                            0x00540063UL
#define TAG_TIME_SLOT_VECTOR                                                     0x00540070UL
#define TAG_NUMBER_OF_TIME_SLOTS                                                 0x00540071UL
#define TAG_TIME_SLOT_INFORMATION_SEQUENCE                                       0x00540072UL
#define TAG_TIME_SLOT_TIME                                                       0x00540073UL
#define TAG_SLICE_VECTOR                                                         0x00540080UL
#define TAG_NUMBER_OF_SLICES                                                     0x00540081UL
#define TAG_ANGULAR_VIEW_VECTOR                                                  0x00540090UL
#define TAG_TIME_SLICE_VECTOR                                                    0x00540100UL
#define TAG_NUMBER_OF_TIME_SLICES                                                0x00540101UL
#define TAG_START_ANGLE                                                          0x00540200UL
#define TAG_TYPE_OF_DETECTOR_MOTION                                              0x00540202UL
#define TAG_TRIGGER_VECTOR                                                       0x00540210UL
#define TAG_NUMBER_OF_TRIGGERS_IN_PHASE                                          0x00540211UL
#define TAG_VIEW_CODE_SEQUENCE                                                   0x00540220UL
#define TAG_VIEW_MODIFIER_CODE_SEQUENCE                                          0x00540222UL
#define TAG_RADIONUCLIDE_CODE_SEQUENCE                                           0x00540300UL
#define TAG_ADMINISTRATION_ROUTE_CODE_SEQUENCE                                   0x00540302UL
#define TAG_RADIOPHARMACEUTICAL_CODE_SEQUENCE                                    0x00540304UL
#define TAG_CALIBRATION_DATA_SEQUENCE                                            0x00540306UL
#define TAG_ENERGY_WINDOW_NUMBER                                                 0x00540308UL
#define TAG_IMAGE_ID                                                             0x00540400UL
#define TAG_PATIENT_ORIENTATION_CODE_SEQUENCE                                    0x00540410UL
#define TAG_PATIENT_ORIENTATION_MODIFIER_CODE_SEQUENCE                           0x00540412UL
#define TAG_PATIENT_GANTRY_RELATIONSHIP_CODE_SEQUENCE                            0x00540414UL
#define TAG_SERIES_TYPE                                                          0x00541000UL
#define TAG_UNITS                                                                0x00541001UL
#define TAG_COUNTS_SOURCE                                                        0x00541002UL
#define TAG_REPROJECTION_METHOD                                                  0x00541004UL
#define TAG_RANDOMS_CORRECTION_METHOD                                            0x00541100UL
#define TAG_ATTENUATION_CORRECTION_METHOD                                        0x00541101UL
#define TAG_DECAY_CORRECTION                                                     0x00541102UL
#define TAG_RECONSTRUCTION_METHOD                                                0x00541103UL
#define TAG_DETECTOR_LINES_OF_RESPONSE_USED                                      0x00541104UL
#define TAG_SCATTER_CORRECTION_METHOD                                            0x00541105UL
#define TAG_AXIAL_ACCEPTANCE                                                     0x00541200UL
#define TAG_AXIAL_MASH                                                           0x00541201UL
#define TAG_TRANSVERSE_MASH                                                      0x00541202UL
#define TAG_DETECTOR_ELEMENT_SIZE                                                0x00541203UL
#define TAG_COINCIDENCE_WINDOW_WIDTH                                             0x00541210UL
#define TAG_SECONDARY_COUNTS_TYPE                                                0x00541220UL
#define TAG_FRAME_REFERENCE_TIME                                                 0x00541300UL
#define TAG_PRIMARY_PROMPTS_COUNTS_ACCUMULATED                                   0x00541310UL
#define TAG_SECONDARY_COUNTS_ACCUMULATED                                         0x00541311UL
#define TAG_SLICE_SENSITIVITY_FACTOR                                             0x00541320UL
#define TAG_DECAY_FACTOR                                                         0x00541321UL
#define TAG_DOSE_CALIBRATION_FACTOR                                              0x00541322UL
#define TAG_SCATTER_FRACTION_FACTOR                                              0x00541323UL
#define TAG_DEAD_TIME_FACTOR                                                     0x00541324UL
#define TAG_IMAGE_INDEX                                                          0x00541330UL
#define TAG_COUNTS_INCLUDED                                                      0x00541400UL
#define TAG_DEAD_TIME_CORRECTION_FLAG                                            0x00541401UL
                                                                                 
#define TAG_HISTOGRAM_SEQUENCE                                                   0x00603000UL 
#define TAG_HISTOGRAM_NUMBER_OF_BINS                                             0x00603002UL 
#define TAG_HISTOGRAM_FIRST_BIN_VALUE                                            0x00603004UL 
#define TAG_HISTOGRAM_LAST_BIN_VALUE                                             0x00603006UL 
#define TAG_HISTOGRAM_BIN_WIDTH                                                  0x00603008UL 
#define TAG_HISTOGRAM_EXPLANATION                                                0x00603010UL 
#define TAG_HISTOGRAM_DATA                                                       0x00603020UL 
                                                                                 
#define TAG_STORAGE_MEDIA_FILE_SET_ID                                            0x00880130UL
#define TAG_STORAGE_MEDIA_FILE_SET_UID                                           0x00880140UL
#define TAG_ICON_IMAGE_SEQUENCE                                                  0x00880200UL
#define TAG_TOPIC_TITLE                                                          0x00880904UL
#define TAG_TOPIC_SUBJECT                                                        0x00880906UL
#define TAG_TOPIC_AUTHOR                                                         0x00880910UL
#define TAG_TOPIC_KEY_WORDS                                                      0x00880912UL

#define TAG_MAC_ID_NUMBER                                                        0x04000005UL 
#define TAG_MAC_CALCULATION_TRANSFER_SYNTAX_UID                                  0x04000010UL 
#define TAG_MAC_ALGORITHM                                                        0x04000015UL 
#define TAG_DATA_ELEMENTS_SIGNED                                                 0x04000020UL 
#define TAG_DIGITAL_SIGNATURE_UID                                                0x04000100UL 
#define TAG_DIGITAL_SIGNATURE_DATETIME                                           0x04000105UL    
#define TAG_CERTIFICATE_TYPE                                                     0x04000110UL 
#define TAG_CERTIFICATE_OF_SIGNER                                                0x04000115UL          
#define TAG_SIGNATURE                                                            0x04000120UL 
#define TAG_CERTIFIED_TIMESTAMP_TYPE                                             0x04000305UL          
#define TAG_CERTIFIED_TIMESTAMP                                                  0x04000310UL             
#define TAG_ENCRYPTED_ATTRIBUTES_SEQUENCE                                        0x04000500UL
#define TAG_ENCRYPTED_CONTENT_TRANSFER_SYNTAX_UID                                0x04000510UL
#define TAG_ENCRYPTED_CONTENT                                                    0x04000520UL
#define TAG_MODIFIED_ATTRIBUTES_SEQUENCE                                         0x04000550UL


                                                                                 
#define TAG_NUMBER_OF_COPIES                                                     0x20000010UL
#define TAG_PRINTER_CONFIGURATION_SEQUENCE                                       0x2000001EUL
#define TAG_PRINT_PRIORITY                                                       0x20000020UL
#define TAG_MEDIUM_TYPE                                                          0x20000030UL
#define TAG_FILM_DESTINATION                                                     0x20000040UL
#define TAG_FILM_SESSION_LABEL                                                   0x20000050UL
#define TAG_MEMORY_ALLOCATION                                                    0x20000060UL
#define TAG_MAXIMUM_MEMORY_ALLOCATION                                            0x20000061UL
#define TAG_COLOR_IMAGE_PRINTING_FLAG                                            0x20000062UL
#define TAG_COLLATION_FLAG                                                       0x20000063UL
#define TAG_ANNOTATION_FLAG                                                      0x20000065UL
#define TAG_IMAGE_OVERLAY_FLAG                                                   0x20000067UL
#define TAG_PRESENTATION_LUT_FLAG                                                0x20000069UL
#define TAG_IMAGE_BOX_PRESENTATION_LUT_FLAG                                      0x2000006AUL
#define TAG_MEMORY_BIT_DEPTH                                                     0x200000A0UL
#define TAG_PRINTING_BIT_DEPTH                                                   0x200000A1UL
#define TAG_MEDIA_INSTALLED_SEQUENCE                                             0x200000A2UL
#define TAG_OTHER_MEDIA_AVAILABLE_SEQUENCE                                       0x200000A4UL
#define TAG_SUPPORTED_IMAGE_DISPLAY_FORMATS_SEQUENCE                             0x200000A8UL
#define TAG_REFERENCED_FILM_BOX_SEQUENCE                                         0x20000500UL
#define TAG_REFERENCED_STORED_PRINT_SEQUENCE                                     0x20000510UL
                                                                                 
#define TAG_IMAGE_DISPLAY_FORMAT                                                 0x20100010UL
#define TAG_ANNOTATION_DISPLAY_FORMAT_ID                                         0x20100030UL
#define TAG_FILM_ORIENTATION                                                     0x20100040UL
#define TAG_FILM_SIZE_ID                                                         0x20100050UL
#define TAG_PRINTER_RESOLUTION_ID                                                0x20100052UL
#define TAG_DEFAULT_PRINTER_RESOLUTION_ID                                        0x20100054UL
#define TAG_MAGNIFICATION_TYPE                                                   0x20100060UL
#define TAG_SMOOTHING_TYPE                                                       0x20100080UL
#define TAG_DEFAULT_MAGNIFICATION_TYPE                                           0x201000A6UL
#define TAG_OTHER_MAGNIFICATION_TYPES_AVAILABLE                                  0x201000A7UL
#define TAG_DEFAULT_SMOOTHING_TYPE                                               0x201000A8UL
#define TAG_OTHER_SMOOTHING_TYPES_AVAILABLE                                      0x201000A9UL
#define TAG_BORDER_DENSITY                                                       0x20100100UL
#define TAG_EMPTY_IMAGE_DENSITY                                                  0x20100110UL
#define TAG_MIN_DENSITY                                                          0x20100120UL
#define TAG_MAX_DENSITY                                                          0x20100130UL
#define TAG_TRIM                                                                 0x20100140UL
#define TAG_CONFIGURATION_INFORMATION                                            0x20100150UL
#define TAG_CONFIGURATION_INFORMATION_DESCRIPTION                                0x20100152UL
#define TAG_MAXIMUM_COLLATED_FILMS                                               0x20100154UL
#define TAG_ILLUMINATION                                                         0x2010015EUL
#define TAG_REFLECTED_AMBIENT_LIGHT                                              0x20100160UL
#define TAG_PRINTER_PIXEL_SPACING                                                0x20100376UL
#define TAG_REFERENCED_FILM_SESSION_SEQUENCE                                     0x20100500UL
#define TAG_REFERENCED_IMAGE_BOX_SEQUENCE                                        0x20100510UL
#define TAG_REFERENCED_BASIC_ANNOTATION_BOX_SEQUENCE                             0x20100520UL
                                                                                 
#define TAG_IMAGE_POSITION                                                       0x20200010UL
#define TAG_POLARITY                                                             0x20200020UL
#define TAG_REQUESTED_IMAGE_SIZE                                                 0x20200030UL
#define TAG_REQUESTED_DECIMATE_CROP_BEHAVIOR                                     0x20200040UL
#define TAG_REQUESTED_RESOLUTION_ID                                              0x20200050UL
#define TAG_REQUESTED_IMAGE_SIZE_FLAG                                            0x202000A0UL
#define TAG_DECIMATE_CROP_RESULT                                                 0x202000A2UL
#define TAG_BASIC_GRAYSCALE_IMAGE_SEQUENCE                                       0x20200110UL
#define TAG_BASIC_COLOR_IMAGE_SEQUENCE                                           0x20200111UL
#define TAG_REFERENCED_IMAGE_OVERLAY_BOX_SEQUENCE_RETIRED                        0x20200130UL
#define TAG_REFERENCED_VOI_LUT_BOX_SEQUENCE_RETIRED                              0x20200140UL
                                                                                 
#define TAG_ANNOTATION_POSITION                                                  0x20300010UL
#define TAG_TEXT_STRING                                                          0x20300020UL
                                                                                 
#define TAG_REFERENCED_OVERLAY_PLANE_SEQUENCE                                    0x20400010UL
#define TAG_REFERENCED_OVERLAY_PLANE_GROUPS                                      0x20400011UL
#define TAG_OVERLAY_PIXEL_DATA_SEQUENCE                                          0x20400020UL
#define TAG_OVERLAY_MAGNIFICATION_TYPE                                           0x20400060UL
#define TAG_OVERLAY_SMOOTHING_TYPE                                               0x20400070UL
#define TAG_OVERLAY_OR_IMAGE_MAGNIFICATION                                       0x20400072UL
#define TAG_MAGNIFY_TO_NUMBER_OF_COLUMNS                                         0x20400074UL
#define TAG_OVERLAY_FOREGROUND_DENSITY                                           0x20400080UL
#define TAG_OVERLAY_BACKGROUND_DENSITY                                           0x20400082UL
#define TAG_OVERLAY_MODE_RETIRED                                                 0x20400090UL
#define TAG_THRESHOLD_DENSITY_RETIRED                                            0x20400100UL
#define TAG_REFERENCED_IMAGE_BOX_SEQUENCE_RETIRED                                0x20400500UL
                                                                                 
#define TAG_PRESENTATION_LUT_SEQUENCE                                            0x20500010UL
#define TAG_PRESENTATION_LUT_SHAPE                                               0x20500020UL
#define TAG_REFERENCED_PRESENTATION_LUT_SEQUENCE                                 0x20500500UL
                                                                                 
#define TAG_PRINT_JOB_ID                                                         0x21000010UL
#define TAG_EXECUTION_STATUS                                                     0x21000020UL
#define TAG_EXECUTION_STATUS_INFO                                                0x21000030UL
#define TAG_CREATION_DATE                                                        0x21000040UL
#define TAG_CREATION_TIME                                                        0x21000050UL
#define TAG_ORIGINATOR                                                           0x21000070UL
#define TAG_DESTINATION_AE                                                       0x21000140UL
#define TAG_OWNER_ID                                                             0x21000160UL
#define TAG_NUMBER_OF_FILMS                                                      0x21000170UL
#define TAG_REFERENCED_PRINT_JOB_SEQUENCE_2100                                   0x21000500UL
                                                                                 
#define TAG_PRINTER_STATUS                                                       0x21100010UL
#define TAG_PRINTER_STATUS_INFO                                                  0x21100020UL
#define TAG_PRINTER_NAME                                                         0x21100030UL
#define TAG_PRINT_QUEUE_ID                                                       0x21100099UL
                                                                                 
#define TAG_QUEUE_STATUS                                                         0x21200010UL
#define TAG_PRINT_JOB_DESCRIPTION_SEQUENCE                                       0x21200050UL
#define TAG_REFERENCED_PRINT_JOB_SEQUENCE_2120                                   0x21200070UL
                                                                                 
#define TAG_PRINT_MANAGEMENT_CAPABILITIES_SEQUENCE                               0x21300010UL
#define TAG_PRINTER_CHARACTERISTICS_SEQUENCE                                     0x21300015UL
#define TAG_FILM_BOX_CONTENT_SEQUENCE                                            0x21300030UL
#define TAG_IMAGE_BOX_CONTENT_SEQUENCE                                           0x21300040UL
#define TAG_ANNOTATION_CONTENT_SEQUENCE                                          0x21300050UL
#define TAG_IMAGE_OVERLAY_BOX_CONTENT_SEQUENCE                                   0x21300060UL
#define TAG_PRESENTATION_LUT_CONTENT_SEQUENCE                                    0x21300080UL
#define TAG_PROPOSED_STUDY_SEQUENCE                                              0x213000A0UL
#define TAG_ORIGINAL_IMAGE_SEQUENCE                                              0x213000C0UL
                                                                                 
#define TAG_RT_IMAGE_LABEL                                                       0x30020002UL
#define TAG_RT_IMAGE_NAME                                                        0x30020003UL
#define TAG_RT_IMAGE_DESCRIPTION                                                 0x30020004UL
#define TAG_REPORTED_VALUES_ORIGIN                                               0x3002000AUL
#define TAG_RT_IMAGE_PLANE                                                       0x3002000CUL
#define TAG_X_RAY_IMAGE_RECEPTOR_ANGLE                                           0x3002000EUL
#define TAG_RT_IMAGE_ORIENTATION                                                 0x30020010UL
#define TAG_IMAGE_PLANE_PIXEL_SPACING                                            0x30020011UL
#define TAG_RT_IMAGE_POSITION                                                    0x30020012UL
#define TAG_RADIATION_MACHINE_NAME                                               0x30020020UL
#define TAG_RADIATION_MACHINE_SAD                                                0x30020022UL
#define TAG_RADIATION_MACHINE_SSD                                                0x30020024UL
#define TAG_RT_IMAGE_SID                                                         0x30020026UL
#define TAG_SOURCE_TO_REFERENCE_OBJECT_DISTANCE                                  0x30020028UL
#define TAG_FRACTION_NUMBER                                                      0x30020029UL
#define TAG_EXPOSURE_SEQUENCE                                                    0x30020030UL
#define TAG_METERSET_EXPOSURE                                                    0x30020032UL
#define TAG_DIAPHRAGM_POSITION                                                   0x30020034UL
                                                                                 
#define TAG_DVH_TYPE                                                             0x30040001UL
#define TAG_DOSE_UNITS                                                           0x30040002UL
#define TAG_DOSE_TYPE                                                            0x30040004UL
#define TAG_DOSE_COMMENT                                                         0x30040006UL
#define TAG_NORMALIZATION_POINT                                                  0x30040008UL
#define TAG_DOSE_SUMMATION_TYPE                                                  0x3004000AUL
#define TAG_GRID_FRAME_OFFSET_VECTOR                                             0x3004000CUL
#define TAG_DOSE_GRID_SCALING                                                    0x3004000EUL
#define TAG_RT_DOSE_ROI_SEQUENCE                                                 0x30040010UL
#define TAG_DOSE_VALUE                                                           0x30040012UL
#define TAG_DVH_NORMALIZATION_POINT                                              0x30040040UL
#define TAG_DVH_NORMALIZATION_DOSE_VALUE                                         0x30040042UL
#define TAG_DVH_SEQUENCE                                                         0x30040050UL
#define TAG_DVH_DOSE_SCALING                                                     0x30040052UL
#define TAG_DVH_VOLUME_UNITS                                                     0x30040054UL
#define TAG_DVH_NUMBER_OF_BINS                                                   0x30040056UL
#define TAG_DVH_DATA                                                             0x30040058UL
#define TAG_DVH_REFERENCED_ROI_SEQUENCE                                          0x30040060UL
#define TAG_DVH_ROI_CONTRIBUTION_TYPE                                            0x30040062UL
#define TAG_DVH_MINIMUM_DOSE                                                     0x30040070UL
#define TAG_DVH_MAXIMUM_DOSE                                                     0x30040072UL
#define TAG_DVH_MEAN_DOSE                                                        0x30040074UL
                                                                                 
#define TAG_STRUCTURE_SET_LABEL                                                  0x30060002UL
#define TAG_STRUCTURE_SET_NAME                                                   0x30060004UL
#define TAG_STRUCTURE_SET_DESCRIPTION                                            0x30060006UL
#define TAG_STRUCTURE_SET_DATE                                                   0x30060008UL
#define TAG_STRUCTURE_SET_TIME                                                   0x30060009UL
#define TAG_REFERENCED_FRAME_OF_REFERENCE_SEQUENCE                               0x30060010UL
#define TAG_RT_REFERENCED_STUDY_SEQUENCE                                         0x30060012UL
#define TAG_RT_REFERENCED_SERIES_SEQUENCE                                        0x30060014UL
#define TAG_CONTOUR_IMAGE_SEQUENCE                                               0x30060016UL
#define TAG_STRUCTURE_SET_ROI_SEQUENCE                                           0x30060020UL
#define TAG_ROI_NUMBER                                                           0x30060022UL
#define TAG_REFERENCED_FRAME_OF_REFERENCE_UID                                    0x30060024UL
#define TAG_ROI_NAME                                                             0x30060026UL
#define TAG_ROI_DESCRIPTION                                                      0x30060028UL
#define TAG_ROI_DISPLAY_COLOR                                                    0x3006002AUL
#define TAG_ROI_VOLUME                                                           0x3006002CUL
#define TAG_RT_RELATED_ROI_SEQUENCE                                              0x30060030UL
#define TAG_RT_ROI_RELATIONSHIP                                                  0x30060033UL
#define TAG_ROI_GENERATION_ALGORITHM                                             0x30060036UL
#define TAG_ROI_GENERATION_DESCRIPTION                                           0x30060038UL
#define TAG_ROI_CONTOUR_SEQUENCE                                                 0x30060039UL
#define TAG_CONTOUR_SEQUENCE                                                     0x30060040UL
#define TAG_CONTOUR_GEOMETRIC_TYPE                                               0x30060042UL
#define TAG_CONTOUR_SLAB_THICKNESS                                               0x30060044UL
#define TAG_CONTOUR_OFFSET_VECTOR                                                0x30060045UL
#define TAG_NUMBER_OF_CONTOUR_POINTS                                             0x30060046UL
#define TAG_CONTOUR_DATA                                                         0x30060050UL
#define TAG_RT_ROI_OBSERVATIONS_SEQUENCE                                         0x30060080UL
#define TAG_OBSERVATION_NUMBER                                                   0x30060082UL
#define TAG_REFERENCED_ROI_NUMBER                                                0x30060084UL
#define TAG_ROI_OBSERVATION_LABEL                                                0x30060085UL
#define TAG_RT_ROI_IDENTIFICATION_CODE_SEQUENCE                                  0x30060086UL
#define TAG_ROI_OBSERVATION_DESCRIPTION                                          0x30060088UL
#define TAG_RELATED_RT_ROI_OBSERVATIONS_SEQUENCE                                 0x300600A0UL
#define TAG_RT_ROI_INTERPRETED_TYPE                                              0x300600A4UL
#define TAG_ROI_INTERPRETER                                                      0x300600A6UL
#define TAG_ROI_PHYSICAL_PROPERTIES_SEQUENCE                                     0x300600B0UL
#define TAG_ROI_PHYSICAL_PROPERTY                                                0x300600B2UL
#define TAG_ROI_PHYSICAL_PROPERTY_VALUE                                          0x300600B4UL
#define TAG_FRAME_OF_REFERENCE_RELATIONSHIP_SEQUENCE                             0x300600C0UL
#define TAG_RELATED_FRAME_OF_REFERENCE_UID                                       0x300600C2UL
#define TAG_FRAME_OF_REFERENCE_TRANSFORMATION_TYPE                               0x300600C4UL
#define TAG_FRAME_OF_REFERENCE_TRANSFORMATION_MATRIX                             0x300600C6UL
#define TAG_FRAME_OF_REFERENCE_TRANSFORMATION_COMMENT                            0x300600C8UL
                                                                                 
#define TAG_MEASURED_DOSE_REFERENCE_SEQUENCE                                     0x30080010UL
#define TAG_MEASURED_DOSE_DESCRIPTION                                            0x30080012UL
#define TAG_MEASURED_DOSE_TYPE                                                   0x30080014UL
#define TAG_MEASURED_DOSE_VALUE                                                  0x30080016UL
#define TAG_TREATMENT_SESSION_BEAM_SEQUENCE                                      0x30080020UL
#define TAG_CURRENT_FRACTION_NUMBER                                              0x30080022UL
#define TAG_TREATMENT_CONTROL_POINT_DATE                                         0x30080024UL
#define TAG_TREATMENT_CONTROL_POINT_TIME                                         0x30080025UL
#define TAG_TREATMENT_TERMINATION_STATUS                                         0x3008002AUL
#define TAG_TREATMENT_TERMINATION_CODE                                           0x3008002BUL
#define TAG_TREATMENT_VERIFICATION_STATUS                                        0x3008002CUL   
#define TAG_REFERENCED_TREATMENT_RECORD_SEQUENCE                                 0x30080030UL
#define TAG_SPECIFIED_PRIMARY_METERSET                                           0x30080032UL
#define TAG_SPECIFIED_SECONDARY_METERSET                                         0x30080033UL
#define TAG_DELIVERED_PRIMARY_METERSET                                           0x30080036UL
#define TAG_DELIVERED_SECONDARY_METERSET                                         0x30080037UL
#define TAG_SPECIFIED_TREATMENT_TIME                                             0x3008003AUL
#define TAG_DELIVERED_TREATMENT_TIME                                             0x3008003BUL
#define TAG_CONTROL_POINT_DELIVERY_SEQUENCE                                      0x30080040UL
#define TAG_SPECIFIED_METERSET                                                   0x30080042UL
#define TAG_DELIVERED_METERSET                                                   0x30080044UL
#define TAG_DOSE_RATE_DELIVERED                                                  0x30080048UL
#define TAG_TREATMENT_SUMMARY_CALCULATED_DOSE_REFERENCE_SEQUENCE                 0x30080050UL
#define TAG_CUMULATIVE_DOSE_TO_DOSE_REFERENCE                                    0x30080052UL
#define TAG_FIRST_TREATMENT_DATE                                                 0x30080054UL
#define TAG_MOST_RECENT_TREATMENT_DATE                                           0x30080056UL
#define TAG_NUMBER_OF_FRACTIONS_DELIVERED                                        0x3008005AUL
#define TAG_OVERRIDE_SEQUENCE                                                    0x30080060UL
#define TAG_OVERRIDE_PARAMETER_POINTER                                           0x30080062UL
#define TAG_MEASURED_DOSE_REFERENCE_NUMBER                                       0x30080064UL
#define TAG_OVERRIDE_REASON                                                      0x30080066UL
#define TAG_CALCULATED_DOSE_REFERENCE_SEQUENCE                                   0x30080070UL
#define TAG_CALCULATED_DOSE_REFERENCE_NUMBER                                     0x30080072UL
#define TAG_CALCULATED_DOSE_REFERENCE_DESCRIPTION                                0x30080074UL
#define TAG_CALCULATED_DOSE_REFERENCE_DOSE_VALUE                                 0x30080076UL
#define TAG_START_METERSET                                                       0x30080078UL
#define TAG_END_METERSET                                                         0x3008007AUL
#define TAG_REFERENCED_MEASURED_DOSE_REFERENCE_SEQUENCE                          0x30080080UL
#define TAG_REFERENCED_MEASURED_DOSE_REFERENCE_NUMBER                            0x30080082UL
#define TAG_REFERENCED_CALCULATED_DOSE_REFERENCE_SEQUENCE                        0x30080090UL
#define TAG_REFERENCED_CALCULATED_DOSE_REFERENCE_NUMBER                          0x30080092UL
#define TAG_BEAM_LIMITING_DEVICE_LEAF_PAIRS_SEQUENCE                             0x300800A0UL
#define TAG_RECORDED_WEDGE_SEQUENCE                                              0x300800B0UL
#define TAG_RECORDED_COMPENSATOR_SEQUENCE                                        0x300800C0UL
#define TAG_RECORDED_BLOCK_SEQUENCE                                              0x300800D0UL
#define TAG_TREATMENT_SUMMARY_MEASURED_DOSE_REFERENCE_SEQUENCE                   0x300800E0UL
#define TAG_RECORDED_SOURCE_SEQUENCE                                             0x30080100UL
#define TAG_SOURCE_SERIAL_NUMBER                                                 0x30080105UL
#define TAG_TREATMENT_SESSION_APPLICATION_SETUP_SEQUENCE                         0x30080110UL
#define TAG_APPLICATION_SETUP_CHECK                                              0x30080116UL
#define TAG_RECORDED_BRACHY_ACCESSORY_DEVICE_SEQUENCE                            0x30080120UL
#define TAG_REFERENCED_BRACHY_ACCESSORY_DEVICE_NUMBER                            0x30080122UL
#define TAG_RECORDED_CHANNEL_SEQUENCE                                            0x30080130UL
#define TAG_SPECIFIED_CHANNEL_TOTAL_TIME                                         0x30080132UL
#define TAG_DELIVERED_CHANNEL_TOTAL_TIME                                         0x30080134UL
#define TAG_SPECIFIED_NUMBER_OF_PULSES                                           0x30080136UL
#define TAG_DELIVERED_NUMBER_OF_PULSES                                           0x30080138UL
#define TAG_SPECIFIED_PULSE_REPETITION_INTERVAL                                  0x3008013AUL
#define TAG_DELIVERED_PULSE_REPETITION_INTERVAL                                  0x3008013CUL
#define TAG_RECORDED_SOURCE_APPLICATOR_SEQUENCE                                  0x30080140UL
#define TAG_REFERENCED_SOURCE_APPLICATOR_NUMBER                                  0x30080142UL
#define TAG_RECORDED_CHANNEL_SHIELD_SEQUENCE                                     0x30080150UL
#define TAG_REFERENCED_CHANNEL_SHIELD_NUMBER                                     0x30080152UL
#define TAG_BRACHY_CONTROL_POINT_DELIVERED_SEQUENCE                              0x30080160UL
#define TAG_SAFE_POSITION_EXIT_DATE                                              0x30080162UL
#define TAG_SAFE_POSITION_EXIT_TIME                                              0x30080164UL
#define TAG_SAFE_POSITION_RETURN_DATE                                            0x30080166UL
#define TAG_SAFE_POSITION_RETURN_TIME                                            0x30080168UL
#define TAG_CURRENT_TREATMENT_STATUS                                             0x30080200UL
#define TAG_TREATMENT_STATUS_COMMENT                                             0x30080202UL
#define TAG_FRACTION_GROUP_SUMMARY_SEQUENCE                                      0x30080220UL
#define TAG_REFERENCED_FRACTION_NUMBER                                           0x30080223UL
#define TAG_FRACTION_GROUP_TYPE                                                  0x30080224UL
#define TAG_BEAM_STOPPER_POSITION                                                0x30080230UL
#define TAG_FRACTION_STATUS_SUMMARY_SEQUENCE                                     0x30080240UL
#define TAG_TREATMENT_DATE                                                       0x30080250UL
#define TAG_TREATMENT_TIME                                                       0x30080251UL
                                                                                 
#define TAG_RT_PLAN_LABEL                                                        0x300A0002UL
#define TAG_RT_PLAN_NAME                                                         0x300A0003UL
#define TAG_RT_PLAN_DESCRIPTION                                                  0x300A0004UL
#define TAG_RT_PLAN_DATE                                                         0x300A0006UL
#define TAG_RT_PLAN_TIME                                                         0x300A0007UL
#define TAG_TREATMENT_PROTOCOLS                                                  0x300A0009UL
#define TAG_TREATMENT_INTENT                                                     0x300A000AUL
#define TAG_TREATMENT_SITES                                                      0x300A000BUL
#define TAG_RT_PLAN_GEOMETRY                                                     0x300A000CUL
#define TAG_PRESCRIPTION_DESCRIPTION                                             0x300A000EUL
#define TAG_DOSE_REFERENCE_SEQUENCE                                              0x300A0010UL
#define TAG_DOSE_REFERENCE_NUMBER                                                0x300A0012UL
#define TAG_DOSE_REFERENCE_STRUCTURE_TYPE                                        0x300A0014UL
#define TAG_NOMINAL_BEAM_ENERGY_UNIT                                             0x300A0015UL
#define TAG_DOSE_REFERENCE_DESCRIPTION                                           0x300A0016UL
#define TAG_DOSE_REFERENCE_POINT_COORDINATES                                     0x300A0018UL
#define TAG_NOMINAL_PRIOR_DOSE                                                   0x300A001AUL
#define TAG_DOSE_REFERENCE_TYPE                                                  0x300A0020UL
#define TAG_CONSTRAINT_WEIGHT                                                    0x300A0021UL
#define TAG_DELIVERY_WARNING_DOSE                                                0x300A0022UL
#define TAG_DELIVERY_MAXIMUM_DOSE                                                0x300A0023UL
#define TAG_TARGET_MINIMUM_DOSE                                                  0x300A0025UL
#define TAG_TARGET_PRESCRIPTION_DOSE                                             0x300A0026UL
#define TAG_TARGET_MAXIMUM_DOSE                                                  0x300A0027UL
#define TAG_TARGET_UNDERDOSE_VOLUME_FRACTION                                     0x300A0028UL
#define TAG_ORGAN_AT_RISK_FULL_VOLUME_DOSE                                       0x300A002AUL
#define TAG_ORGAN_AT_RISK_LIMIT_DOSE                                             0x300A002BUL
#define TAG_ORGAN_AT_RISK_MAXIMUM_DOSE                                           0x300A002CUL
#define TAG_ORGAN_AT_RISK_OVERDOSE_VOLUME_FRACTION                               0x300A002DUL
#define TAG_TOLERANCE_TABLE_SEQUENCE                                             0x300A0040UL
#define TAG_TOLERANCE_TABLE_NUMBER                                               0x300A0042UL
#define TAG_TOLERANCE_TABLE_LABEL                                                0x300A0043UL
#define TAG_GANTRY_ANGLE_TOLERANCE                                               0x300A0044UL
#define TAG_BEAM_LIMITING_DEVICE_ANGLE_TOLERANCE                                 0x300A0046UL
#define TAG_BEAM_LIMITING_DEVICE_TOLERANCE_SEQUENCE                              0x300A0048UL
#define TAG_BEAM_LIMITING_DEVICE_POSITION_TOLERANCE                              0x300A004AUL
#define TAG_PATIENT_SUPPORT_ANGLE_TOLERANCE                                      0x300A004CUL
#define TAG_TABLE_TOP_ECCENTRIC_ANGLE_TOLERANCE                                  0x300A004EUL
#define TAG_TABLE_TOP_VERTICAL_POSITION_TOLERANCE                                0x300A0051UL
#define TAG_TABLE_TOP_LONGITUDINAL_POSITION_TOLERANCE                            0x300A0052UL
#define TAG_TABLE_TOP_LATERAL_POSITION_TOLERANCE                                 0x300A0053UL
#define TAG_RT_PLAN_RELATIONSHIP                                                 0x300A0055UL
#define TAG_FRACTION_GROUP_SEQUENCE                                              0x300A0070UL
#define TAG_FRACTION_GROUP_NUMBER                                                0x300A0071UL
#define TAG_NUMBER_OF_FRACTIONS_PLANNED                                          0x300A0078UL
#define TAG_NUMBER_OF_FRACTIONS_PER_DAY                                          0x300A0079UL
#define TAG_REPEAT_FRACTION_CYCLE_LENGTH                                         0x300A007AUL
#define TAG_FRACTION_PATTERN                                                     0x300A007BUL
#define TAG_NUMBER_OF_BEAMS                                                      0x300A0080UL
#define TAG_BEAM_DOSE_SPECIFICATION_POINT                                        0x300A0082UL
#define TAG_BEAM_DOSE                                                            0x300A0084UL
#define TAG_BEAM_METERSET                                                        0x300A0086UL
#define TAG_NUMBER_OF_BRACHY_APPLICATION_SETUPS                                  0x300A00A0UL
#define TAG_BRACHY_APPLICATION_SETUP_DOSE_SPECIFICATION_POINT                    0x300A00A2UL
#define TAG_BRACHY_APPLICATION_SETUP_DOSE                                        0x300A00A4UL
#define TAG_BEAM_SEQUENCE                                                        0x300A00B0UL
#define TAG_TREATMENT_MACHINE_NAME                                               0x300A00B2UL
#define TAG_PRIMARY_DOSIMETER_UNIT                                               0x300A00B3UL
#define TAG_SOURCE_AXIS_DISTANCE                                                 0x300A00B4UL
#define TAG_BEAM_LIMITING_DEVICE_SEQUENCE                                        0x300A00B6UL
#define TAG_RT_BEAM_LIMITING_DEVICE_TYPE                                         0x300A00B8UL
#define TAG_SOURCE_TO_BEAM_LIMITING_DEVICE_DISTANCE                              0x300A00BAUL
#define TAG_NUMBER_OF_LEAF_JAW_PAIRS                                             0x300A00BCUL
#define TAG_LEAF_POSITION_BOUNDARIES                                             0x300A00BEUL
#define TAG_BEAM_NUMBER                                                          0x300A00C0UL
#define TAG_BEAM_NAME                                                            0x300A00C2UL
#define TAG_BEAM_DESCRIPTION                                                     0x300A00C3UL
#define TAG_BEAM_TYPE                                                            0x300A00C4UL
#define TAG_RADIATION_TYPE                                                       0x300A00C6UL
#define TAG_HIGHDOSE_TECHNIQUE_TYPE                                              0x300A00C7UL 
#define TAG_REFERENCE_IMAGE_NUMBER                                               0x300A00C8UL
#define TAG_PLANNED_VERIFICATION_IMAGE_SEQUENCE                                  0x300A00CAUL
#define TAG_IMAGING_DEVICE_SPECIFIC_ACQUISITION_PARAMETERS                       0x300A00CCUL
#define TAG_TREATMENT_DELIVERY_TYPE                                              0x300A00CEUL
#define TAG_NUMBER_OF_WEDGES                                                     0x300A00D0UL
#define TAG_WEDGE_SEQUENCE                                                       0x300A00D1UL
#define TAG_WEDGE_NUMBER                                                         0x300A00D2UL
#define TAG_WEDGE_TYPE                                                           0x300A00D3UL
#define TAG_WEDGE_ID                                                             0x300A00D4UL
#define TAG_WEDGE_ANGLE                                                          0x300A00D5UL
#define TAG_WEDGE_FACTOR                                                         0x300A00D6UL
#define TAG_WEDGE_ORIENTATION                                                    0x300A00D8UL
#define TAG_SOURCE_TO_WEDGE_TRAY_DISTANCE                                        0x300A00DAUL
#define TAG_NUMBER_OF_COMPENSATORS                                               0x300A00E0UL
#define TAG_MATERIAL_ID                                                          0x300A00E1UL
#define TAG_TOTAL_COMPENSATOR_TRAY_FACTOR                                        0x300A00E2UL
#define TAG_COMPENSATOR_SEQUENCE                                                 0x300A00E3UL
#define TAG_COMPENSATOR_NUMBER                                                   0x300A00E4UL
#define TAG_COMPENSATOR_ID                                                       0x300A00E5UL
#define TAG_SOURCE_TO_COMPENSATOR_TRAY_DISTANCE                                  0x300A00E6UL
#define TAG_COMPENSATOR_ROWS                                                     0x300A00E7UL
#define TAG_COMPENSATOR_COLUMNS                                                  0x300A00E8UL
#define TAG_COMPENSATOR_PIXEL_SPACING                                            0x300A00E9UL
#define TAG_COMPENSATOR_POSITION                                                 0x300A00EAUL
#define TAG_COMPENSATOR_TRANSMISSION_DATA                                        0x300A00EBUL
#define TAG_COMPENSATOR_THICKNESS_DATA                                           0x300A00ECUL
#define TAG_NUMBER_OF_BOLI                                                       0x300A00EDUL
#define TAG_COMPENSATOR_TYPE                                                     0x300A00EEUL
#define TAG_NUMBER_OF_BLOCKS                                                     0x300A00F0UL
#define TAG_TOTAL_BLOCK_TRAY_FACTOR                                              0x300A00F2UL
#define TAG_BLOCK_SEQUENCE                                                       0x300A00F4UL
#define TAG_BLOCK_TRAY_ID                                                        0x300A00F5UL
#define TAG_SOURCE_TO_BLOCK_TRAY_DISTANCE                                        0x300A00F6UL
#define TAG_BLOCK_TYPE                                                           0x300A00F8UL
#define TAG_BLOCK_DIVERGENCE                                                     0x300A00FAUL
#define TAG_BLOCK_MOUNTING_POSITION                                              0x300A00FBUL
#define TAG_BLOCK_NUMBER                                                         0x300A00FCUL
#define TAG_BLOCK_NAME                                                           0x300A00FEUL
#define TAG_BLOCK_THICKNESS                                                      0x300A0100UL
#define TAG_BLOCK_TRANSMISSION                                                   0x300A0102UL
#define TAG_BLOCK_NUMBER_OF_POINTS                                               0x300A0104UL
#define TAG_BLOCK_DATA                                                           0x300A0106UL
#define TAG_APPLICATOR_SEQUENCE                                                  0x300A0107UL
#define TAG_APPLICATOR_ID                                                        0x300A0108UL
#define TAG_APPLICATOR_TYPE                                                      0x300A0109UL
#define TAG_APPLICATOR_DESCRIPTION                                               0x300A010AUL
#define TAG_CUMULATIVE_DOSE_REFERENCE_COEFFICIENT                                0x300A010CUL
#define TAG_FINAL_CUMULATIVE_METERSET_WEIGHT                                     0x300A010EUL
#define TAG_NUMBER_OF_CONTROL_POINTS                                             0x300A0110UL
#define TAG_CONTROL_POINT_SEQUENCE                                               0x300A0111UL
#define TAG_CONTROL_POINT_INDEX                                                  0x300A0112UL
#define TAG_NOMINAL_BEAM_ENERGY                                                  0x300A0114UL
#define TAG_DOSE_RATE_SET                                                        0x300A0115UL
#define TAG_WEDGE_POSITION_SEQUENCE                                              0x300A0116UL
#define TAG_WEDGE_POSITION                                                       0x300A0118UL
#define TAG_BEAM_LIMITING_DEVICE_POSITION_SEQUENCE                               0x300A011AUL
#define TAG_LEAF_JAW_POSITIONS                                                   0x300A011CUL
#define TAG_GANTRY_ANGLE                                                         0x300A011EUL
#define TAG_GANTRY_ROTATION_DIRECTION                                            0x300A011FUL
#define TAG_BEAM_LIMITING_DEVICE_ANGLE                                           0x300A0120UL
#define TAG_BEAM_LIMITING_DEVICE_ROTATION_DIRECTION                              0x300A0121UL
#define TAG_PATIENT_SUPPORT_ANGLE                                                0x300A0122UL
#define TAG_PATIENT_SUPPORT_ROTATION_DIRECTION                                   0x300A0123UL
#define TAG_TABLE_TOP_ECCENTRIC_AXIS_DISTANCE                                    0x300A0124UL
#define TAG_TABLE_TOP_ECCENTRIC_ANGLE                                            0x300A0125UL
#define TAG_TABLE_TOP_ECCENTRIC_ROTATION_DIRECTION                               0x300A0126UL
#define TAG_TABLE_TOP_VERTICAL_POSITION                                          0x300A0128UL
#define TAG_TABLE_TOP_LONGITUDINAL_POSITION                                      0x300A0129UL
#define TAG_TABLE_TOP_LATERAL_POSITION                                           0x300A012AUL
#define TAG_ISOCENTER_POSITION                                                   0x300A012CUL
#define TAG_SURFACE_ENTRY_POINT                                                  0x300A012EUL
#define TAG_SOURCE_TO_SURFACE_DISTANCE                                           0x300A0130UL
#define TAG_CUMULATIVE_METERSET_WEIGHT                                           0x300A0134UL
#define TAG_PATIENT_SETUP_SEQUENCE                                               0x300A0180UL
#define TAG_PATIENT_SETUP_NUMBER                                                 0x300A0182UL
#define TAG_PATIENT_ADDITIONAL_POSITION                                          0x300A0184UL
#define TAG_FIXATION_DEVICE_SEQUENCE                                             0x300A0190UL
#define TAG_FIXATION_DEVICE_TYPE                                                 0x300A0192UL
#define TAG_FIXATION_DEVICE_LABEL                                                0x300A0194UL
#define TAG_FIXATION_DEVICE_DESCRIPTION                                          0x300A0196UL
#define TAG_FIXATION_DEVICE_POSITION                                             0x300A0198UL
#define TAG_SHIELDING_DEVICE_SEQUENCE                                            0x300A01A0UL
#define TAG_SHIELDING_DEVICE_TYPE                                                0x300A01A2UL
#define TAG_SHIELDING_DEVICE_LABEL                                               0x300A01A4UL
#define TAG_SHIELDING_DEVICE_DESCRIPTION                                         0x300A01A6UL
#define TAG_SHIELDING_DEVICE_POSITION                                            0x300A01A8UL
#define TAG_SETUP_TECHNIQUE                                                      0x300A01B0UL
#define TAG_SETUP_TECHNIQUE_DESCRIPTION                                          0x300A01B2UL
#define TAG_SETUP_DEVICE_SEQUENCE                                                0x300A01B4UL
#define TAG_SETUP_DEVICE_TYPE                                                    0x300A01B6UL
#define TAG_SETUP_DEVICE_LABEL                                                   0x300A01B8UL
#define TAG_SETUP_DEVICE_DESCRIPTION                                             0x300A01BAUL
#define TAG_SETUP_DEVICE_PARAMETER                                               0x300A01BCUL
#define TAG_SETUP_REFERENCE_DESCRIPTION                                          0x300A01D0UL
#define TAG_TABLE_TOP_VERTICAL_SETUP_DISPLACEMENT                                0x300A01D2UL
#define TAG_TABLE_TOP_LONGITUDINAL_SETUP_DISPLACEMENT                            0x300A01D4UL
#define TAG_TABLE_TOP_LATERAL_SETUP_DISPLACEMENT                                 0x300A01D6UL
#define TAG_BRACHY_TREATMENT_TECHNIQUE                                           0x300A0200UL
#define TAG_BRACHY_TREATMENT_TYPE                                                0x300A0202UL
#define TAG_TREATMENT_MACHINE_SEQUENCE                                           0x300A0206UL
#define TAG_SOURCE_SEQUENCE                                                      0x300A0210UL
#define TAG_SOURCE_NUMBER                                                        0x300A0212UL
#define TAG_SOURCE_TYPE                                                          0x300A0214UL
#define TAG_SOURCE_MANUFACTURER                                                  0x300A0216UL
#define TAG_ACTIVE_SOURCE_DIAMETER                                               0x300A0218UL
#define TAG_ACTIVE_SOURCE_LENGTH                                                 0x300A021AUL
#define TAG_SOURCE_ENCAPSULATION_NOMINAL_THICKNESS                               0x300A0222UL
#define TAG_SOURCE_ENCAPSULATION_NOMINAL_TRANSMISSION                            0x300A0224UL
#define TAG_SOURCE_ISOTOPE_NAME                                                  0x300A0226UL
#define TAG_SOURCE_ISOTOPE_HALF_LIFE                                             0x300A0228UL
#define TAG_REFERENCE_AIR_KERMA_RATE                                             0x300A022AUL
#define TAG_AIR_KERMA_RATE_REFERENCE_DATE                                        0x300A022CUL
#define TAG_AIR_KERMA_RATE_REFERENCE_TIME                                        0x300A022EUL
#define TAG_APPLICATION_SETUP_SEQUENCE                                           0x300A0230UL
#define TAG_APPLICATION_SETUP_TYPE                                               0x300A0232UL
#define TAG_APPLICATION_SETUP_NUMBER                                             0x300A0234UL
#define TAG_APPLICATION_SETUP_NAME                                               0x300A0236UL
#define TAG_APPLICATION_SETUP_MANUFACTURER                                       0x300A0238UL
#define TAG_TEMPLATE_NUMBER                                                      0x300A0240UL
#define TAG_TEMPLATE_TYPE                                                        0x300A0242UL
#define TAG_TEMPLATE_NAME                                                        0x300A0244UL
#define TAG_TOTAL_REFERENCE_AIR_KERMA                                            0x300A0250UL
#define TAG_BRACHY_ACCESSORY_DEVICE_SEQUENCE                                     0x300A0260UL
#define TAG_BRACHY_ACCESSORY_DEVICE_NUMBER                                       0x300A0262UL
#define TAG_BRACHY_ACCESSORY_DEVICE_ID                                           0x300A0263UL
#define TAG_BRACHY_ACCESSORY_DEVICE_TYPE                                         0x300A0264UL
#define TAG_BRACHY_ACCESSORY_DEVICE_NAME                                         0x300A0266UL
#define TAG_BRACHY_ACCESSORY_DEVICE_NOMINAL_THICKNESS                            0x300A026AUL
#define TAG_BRACHY_ACCESSORY_DEVICE_NOMINAL_TRANSMISSION                         0x300A026CUL
#define TAG_CHANNEL_SEQUENCE                                                     0x300A0280UL
#define TAG_CHANNEL_NUMBER                                                       0x300A0282UL
#define TAG_CHANNEL_LENGTH                                                       0x300A0284UL
#define TAG_CHANNEL_TOTAL_TIME                                                   0x300A0286UL
#define TAG_SOURCE_MOVEMENT_TYPE                                                 0x300A0288UL
#define TAG_NUMBER_OF_PULSES                                                     0x300A028AUL
#define TAG_PULSE_REPETITION_INTERVAL                                            0x300A028CUL
#define TAG_SOURCE_APPLICATOR_NUMBER                                             0x300A0290UL
#define TAG_SOURCE_APPLICATOR_ID                                                 0x300A0291UL
#define TAG_SOURCE_APPLICATOR_TYPE                                               0x300A0292UL
#define TAG_SOURCE_APPLICATOR_NAME                                               0x300A0294UL
#define TAG_SOURCE_APPLICATOR_LENGTH                                             0x300A0296UL
#define TAG_SOURCE_APPLICATOR_MANUFACTURER                                       0x300A0298UL
#define TAG_SOURCE_APPLICATOR_WALL_NOMINAL_THICKNESS                             0x300A029CUL
#define TAG_SOURCE_APPLICATOR_WALL_NOMINAL_TRANSMISSION                          0x300A029EUL
#define TAG_SOURCE_APPLICATOR_STEP_SIZE                                          0x300A02A0UL
#define TAG_TRANSFER_TUBE_NUMBER                                                 0x300A02A2UL
#define TAG_TRANSFER_TUBE_LENGTH                                                 0x300A02A4UL
#define TAG_CHANNEL_SHIELD_SEQUENCE                                              0x300A02B0UL
#define TAG_CHANNEL_SHIELD_NUMBER                                                0x300A02B2UL
#define TAG_CHANNEL_SHIELD_ID                                                    0x300A02B3UL
#define TAG_CHANNEL_SHIELD_NAME                                                  0x300A02B4UL
#define TAG_CHANNEL_SHIELD_NOMINAL_THICKNESS                                     0x300A02B8UL
#define TAG_CHANNEL_SHIELD_NOMINAL_TRANSMISSION                                  0x300A02BAUL
#define TAG_FINAL_CUMULATIVE_TIME_WEIGHT                                         0x300A02C8UL
#define TAG_BRACHY_CONTROL_POINT_SEQUENCE                                        0x300A02D0UL
#define TAG_CONTROL_POINT_RELATIVE_POSITION                                      0x300A02D2UL
#define TAG_CONTROL_POINT_3D_POSITION                                            0x300A02D4UL
#define TAG_CUMULATIVE_TIME_WEIGHT                                               0x300A02D6UL
#define TAG_COMPENSATOR_DIVERGENCE                                               0x300A02E0UL  
#define TAG_COMPENSATOR_MOUNTING_POSITION                                        0x300A02E1UL  
#define TAG_SOURCE_TO_COMPENSATOR_DISTANCE                                       0x300A02E2UL  

                                                                                 
#define TAG_REFERENCED_RT_PLAN_SEQUENCE                                          0x300C0002UL
#define TAG_REFERENCED_BEAM_SEQUENCE                                             0x300C0004UL
#define TAG_REFERENCED_BEAM_NUMBER                                               0x300C0006UL
#define TAG_REFERENCED_REFERENCE_IMAGE_NUMBER                                    0x300C0007UL
#define TAG_START_CUMULATIVE_METERSET_WEIGHT                                     0x300C0008UL
#define TAG_END_CUMULATIVE_METERSET_WEIGHT                                       0x300C0009UL
#define TAG_REFERENCED_BRACHY_APPLICATION_SETUP_SEQUENCE                         0x300C000AUL
#define TAG_REFERENCED_BRACHY_APPLICATION_SETUP_NUMBER                           0x300C000CUL
#define TAG_REFERENCED_SOURCE_NUMBER                                             0x300C000EUL
#define TAG_REFERENCED_FRACTION_GROUP_SEQUENCE                                   0x300C0020UL
#define TAG_REFERENCED_FRACTION_GROUP_NUMBER                                     0x300C0022UL
#define TAG_REFERENCED_VERIFICATION_IMAGE_SEQUENCE                               0x300C0040UL
#define TAG_REFERENCED_REFERENCE_IMAGE_SEQUENCE                                  0x300C0042UL
#define TAG_REFERENCED_DOSE_REFERENCE_SEQUENCE                                   0x300C0050UL
#define TAG_REFERENCED_DOSE_REFERENCE_NUMBER                                     0x300C0051UL
#define TAG_BRACHY_REFERENCED_DOSE_REFERENCE_SEQUENCE                            0x300C0055UL
#define TAG_REFERENCED_STRUCTURE_SET_SEQUENCE                                    0x300C0060UL
#define TAG_REFERENCED_PATIENT_SETUP_NUMBER                                      0x300C006AUL
#define TAG_REFERENCED_DOSE_SEQUENCE                                             0x300C0080UL
#define TAG_REFERENCED_TOLERANCE_TABLE_NUMBER                                    0x300C00A0UL
#define TAG_REFERENCED_BOLUS_SEQUENCE                                            0x300C00B0UL
#define TAG_REFERENCED_WEDGE_NUMBER                                              0x300C00C0UL
#define TAG_REFERENCED_COMPENSATOR_NUMBER                                        0x300C00D0UL
#define TAG_REFERENCED_BLOCK_NUMBER                                              0x300C00E0UL
#define TAG_REFERENCED_CONTROL_POINT_INDEX                                       0x300C00F0UL
                                                                                 
#define TAG_APPROVAL_STATUS                                                      0x300E0002UL
#define TAG_REVIEW_DATE                                                          0x300E0004UL
#define TAG_REVIEW_TIME                                                          0x300E0005UL
#define TAG_REVIEWER_NAME                                                        0x300E0008UL
                                                                                 
#define TAG_RESULTS_ID                                                           0x40080040UL
#define TAG_RESULTS_ID_ISSUER                                                    0x40080042UL
#define TAG_REFERENCED_INTERPRETATION_SEQUENCE                                   0x40080050UL
#define TAG_INTERPRETATION_RECORDED_DATE                                         0x40080100UL
#define TAG_INTERPRETATION_RECORDED_TIME                                         0x40080101UL
#define TAG_INTERPRETATION_RECORDER                                              0x40080102UL
#define TAG_REFERENCE_TO_RECORDED_SOUND                                          0x40080103UL
#define TAG_INTERPRETATION_TRANSCRIPTION_DATE                                    0x40080108UL
#define TAG_INTERPRETATION_TRANSCRIPTION_TIME                                    0x40080109UL
#define TAG_INTERPRETATION_TRANSCRIBER                                           0x4008010AUL
#define TAG_INTERPRETATION_TEXT                                                  0x4008010BUL
#define TAG_INTERPRETATION_AUTHOR                                                0x4008010CUL
#define TAG_INTERPRETATION_APPROVER_SEQUENCE                                     0x40080111UL
#define TAG_INTERPRETATION_APPROVAL_DATE                                         0x40080112UL
#define TAG_INTERPRETATION_APPROVAL_TIME                                         0x40080113UL
#define TAG_PHYSICIAN_APPROVING_INTERPRETATION                                   0x40080114UL
#define TAG_INTERPRETATION_DIAGNOSIS_DESCRIPTION                                 0x40080115UL
#define TAG_INTERPRETATION_DIAGNOSIS_CODE_SEQUENCE                               0x40080117UL
#define TAG_RESULTS_DISTRIBUTION_LIST_SEQUENCE                                   0x40080118UL
#define TAG_DISTRIBUTION_NAME                                                    0x40080119UL
#define TAG_DISTRIBUTION_ADDRESS                                                 0x4008011AUL
#define TAG_INTERPRETATION_ID                                                    0x40080200UL
#define TAG_INTERPRETATION_ID_ISSUER                                             0x40080202UL
#define TAG_INTERPRETATION_TYPE_ID                                               0x40080210UL
#define TAG_INTERPRETATION_STATUS_ID                                             0x40080212UL
#define TAG_IMPRESSIONS                                                          0x40080300UL
#define TAG_RESULTS_COMMENTS                                                     0x40084000UL
#define TAG_MAC_PARAMETERS_SEQUENCE                                              0x4FFE0001UL 
                                                                                 
#define TAG_CURVE_DIMENSIONS                                                     0x50000005UL
#define TAG_NUMBER_OF_POINTS                                                     0x50000010UL
#define TAG_TYPE_OF_DATA                                                         0x50000020UL
#define TAG_CURVE_DESCRIPTION                                                    0x50000022UL
#define TAG_AXIS_UNITS                                                           0x50000030UL
#define TAG_AXIS_LABELS                                                          0x50000040UL
#define TAG_DATA_VALUE_REPRESENTATION                                            0x50000103UL
#define TAG_MINIMUM_COORDINATE_VALUE                                             0x50000104UL
#define TAG_MAXIMUM_COORDINATE_VALUE                                             0x50000105UL
#define TAG_CURVE_RANGE                                                          0x50000106UL
#define TAG_CURVE_DATA_DESCRIPTOR                                                0x50000110UL
#define TAG_COORDINATE_START_VALUE                                               0x50000112UL
#define TAG_COORDINATE_STEP_VALUE                                                0x50000114UL
#define TAG_AUDIO_TYPE                                                           0x50002000UL
#define TAG_AUDIO_SAMPLE_FORMAT                                                  0x50002002UL
#define TAG_NUMBER_OF_CHANNELS                                                   0x50002004UL
#define TAG_NUMBER_OF_SAMPLES                                                    0x50002006UL
#define TAG_SAMPLE_RATE                                                          0x50002008UL
#define TAG_TOTAL_TIME                                                           0x5000200AUL
#define TAG_AUDIO_SAMPLE_DATA                                                    0x5000200CUL
#define TAG_AUDIO_COMMENTS                                                       0x5000200EUL
#define TAG_CURVE_LABEL                                                          0x50002500UL
#define TAG_REFERENCED_OVERLAY_SEQUENCE_50XX                                     0x50002600UL
#define TAG_REFERENCED_OVERLAY_GROUP                                             0x50002610UL
#define TAG_CURVE_DATA                                                           0x50003000UL

#define TAG_SHARED_FUNCTIONAL_GROUPS_SEQUENCE                                    0x52009229UL
#define TAG_PER_FRAME_FUNCTIONAL_GROUPS_SEQUENCE                                 0x52009230UL
                                                                                 
#define TAG_OVERLAY_ROWS                                                         0x60000010UL
#define TAG_OVERLAY_COLUMNS                                                      0x60000011UL
#define TAG_OVERLAY_PLANES                                                       0x60000012UL
#define TAG_NUMBER_OF_FRAMES_IN_OVERLAY                                          0x60000015UL
#define TAG_OVERLAY_DESCRIPTION                                                  0x60000022UL
#define TAG_OVERLAY_TYPE                                                         0x60000040UL
#define TAG_OVERLAY_SUBTYPE                                                      0x60000045UL
#define TAG_OVERLAY_ORIGIN                                                       0x60000050UL
#define TAG_IMAGE_FRAME_ORIGIN                                                   0x60000051UL
#define TAG_OVERLAY_PLANE_ORIGIN                                                 0x60000052UL
#define TAG_OVERLAY_BITS_ALLOCATED                                               0x60000100UL
#define TAG_OVERLAY_BIT_POSITION                                                 0x60000102UL
#define TAG_OVERLAY_DESCRIPTOR_GRAY_RETIRED                                      0x60001100UL
#define TAG_OVERLAY_DESCRIPTOR_RED_RETIRED                                       0x60001101UL
#define TAG_OVERLAY_DESCRIPTOR_GREEN_RETIRED                                     0x60001102UL
#define TAG_OVERLAY_DESCRIPTOR_BLUE_RETIRED                                      0x60001103UL
#define TAG_OVERLAYS_GRAY_RETIRED                                                0x60001200UL
#define TAG_OVERLAYS_RED_RETIRED                                                 0x60001201UL
#define TAG_OVERLAYS_GREEN_RETIRED                                               0x60001202UL
#define TAG_OVERLAYS_BLUE_RETIRED                                                0x60001203UL
#define TAG_ROI_AREA                                                             0x60001301UL
#define TAG_ROI_MEAN                                                             0x60001302UL
#define TAG_ROI_STANDARD_DEVIATION                                               0x60001303UL
#define TAG_OVERLAY_LABEL                                                        0x60001500UL
#define TAG_OVERLAY_DATA                                                         0x60003000UL
                                                                                 
#define TAG_PIXEL_DATA                                                           0x7FE00010UL
#define TAG_LEAD_BITMAP                                                          0x7FE00010UL
                                                                                 
#define TAG_DIGITAL_SIGNATURES_SEQUENCE                                          0xFFFAFFFAUL

#define TAG_DATA_SET_TRAILING_PADDING                                            0xFFFCFFFCUL
                                                                                 
#define TAG_ITEM                                                                 0xFFFEE000UL
#define TAG_ITEM_DELIMITATION_ITEM                                               0xFFFEE00DUL
#define TAG_SEQUENCE_DELIMITATION_ITEM                                           0xFFFEE0DDUL

//============= CLASS ==========================================================

enum
{
   IOD_TYPE_CLASS=0,             // Class type
   IOD_TYPE_MODULE,              // Module type
   IOD_TYPE_ELEMENT,             // Element type
   IOD_TYPE_MAX,
};

enum
{
   IOD_USAGE_M,                  // Mandatory IOD   - M - (U - Unique for key)
   IOD_USAGE_C,                  // Conditional IOD - C - (R - Required for key)
   IOD_USAGE_U,                  // Optional IOD    - U - (O - Optional for key)
   IOD_USAGE_1,                  // Mandatory IOD   - 1  (type 1)
   IOD_USAGE_1C,                 // Conditional IOD - 1C (type 1)
   IOD_USAGE_2,                  // Mandatory IOD   - 2  (type 2)
   IOD_USAGE_2C,                 // Conditional IOD - 2C (type 2)
   IOD_USAGE_3,                  // Optional IOD    - 3  (type 3)
   IOD_USAGE_MAX,
};

//typedef struct _DICOMIOD DICOMIOD, *pDICOMIOD;
typedef struct _DICOMIOD
{
   GENERICLINK                   // Reserved - internally used only

   L_UINT32  nCode;              // Code (CLASS_CR_IMAGE, MODULE_PATIENT, TAG_STUDY_TIME, ...)
   L_CHAR   *pszName;            // Name
   L_CHAR    nType;              // Type (IOD_TYPE_CLASS, IOD_TYPE_MODULE, IOD_TYPE_ELEMENT)
   L_UINT16  nUsage;             // Usage (IOD_USAGE_M, IOD_USAGE_C, ...) 
   L_CHAR   *pszDescription;     // Description
} DICOMIOD, *pDICOMIOD;

#ifdef __cplusplus

class DICOM_EXPORT LDicomIOD
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   static L_VOID    Default         ();

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   static pDICOMIOD Insert          (pDICOMIOD pNeighbor, L_BOOL bChild, L_UINT32 nCode, L_CHAR  *pszName, L_CHAR nType, L_UINT16 nUsage, L_CHAR *pszDescription);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   static pDICOMIOD Delete          (pDICOMIOD pIOD);
   static L_VOID    Reset           ();

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   static pDICOMIOD GetRoot         (pDICOMIOD pIOD);
   static pDICOMIOD GetParent       (pDICOMIOD pIOD);
   static pDICOMIOD GetChild        (pDICOMIOD pIOD);
   static pDICOMIOD GetFirst        (pDICOMIOD pIOD, L_BOOL bTree);
   static pDICOMIOD GetLast         (pDICOMIOD pIOD, L_BOOL bTree);
   static pDICOMIOD GetPrev         (pDICOMIOD pIOD, L_BOOL bTree);
   static pDICOMIOD GetNext         (pDICOMIOD pIOD, L_BOOL bTree);
   static L_UINT32  GetCountModule  (L_UINT32 nClass);
   static L_BOOL    Exists          (pDICOMIOD pIOD);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   static pDICOMIOD Find            (pDICOMIOD pIOD, L_UINT32 nCode, L_CHAR nType, L_BOOL bTree);
   static pDICOMIOD FindClass       (L_UINT32 nClass);
   static pDICOMIOD FindModule      (L_UINT32 nClass, L_UINT32 nModule);
   static pDICOMIOD FindIndexModule (L_UINT32 nClass, L_UINT32 nIndex);

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------
   static L_BOOL    SetName         (pDICOMIOD pIOD, L_CHAR *pszName);
   static L_BOOL    SetDescription  (pDICOMIOD pIOD, L_CHAR *pszDescription);

   //---------------------------------------------------------------------------
   // Private Functions
   //---------------------------------------------------------------------------
private:
   static LDicomTreeEx m_InfoIOD;
   
   static L_VOID    Default         (pDICOMIOD pIOD, L_VOID *pReference);
   static pDICOMIOD FindInClass     (pDICOMIOD pIOD, L_UINT32 nCode, L_CHAR nType);
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif


// For use with L_SetMemoryAllocation
#define MEMORY_FAIL   (0)
#define MEMORY_FAR    (1)
#define MEMORY_GLOBAL (2)


//---------------------------------------------------------------------------
// Initializing Functions
//---------------------------------------------------------------------------
L_VOID    EXT_FUNCTION L_DicomDefaultIOD         ();
L_UINT16  EXT_FUNCTION L_DicomSetMemoryAllocation(L_UINT16 nType);

//---------------------------------------------------------------------------
// Insertion Functions
//---------------------------------------------------------------------------
pDICOMIOD EXT_FUNCTION L_DicomInsertIOD          (pDICOMIOD pNeighbor, L_BOOL bChild, L_UINT32 nCode, L_CHAR  *pszName, L_CHAR nType, L_UINT16 nUsage, L_CHAR *pszDescription);

//---------------------------------------------------------------------------
// Deletion Functions
//---------------------------------------------------------------------------
pDICOMIOD EXT_FUNCTION L_DicomDeleteIOD          (pDICOMIOD pIOD);
L_VOID    EXT_FUNCTION L_DicomResetIOD           ();

//---------------------------------------------------------------------------
// Iteration Functions
//---------------------------------------------------------------------------
pDICOMIOD EXT_FUNCTION L_DicomGetRootIOD         (pDICOMIOD pIOD);
pDICOMIOD EXT_FUNCTION L_DicomGetParentIOD       (pDICOMIOD pIOD);
pDICOMIOD EXT_FUNCTION L_DicomGetChildIOD        (pDICOMIOD pIOD);
pDICOMIOD EXT_FUNCTION L_DicomGetFirstIOD        (pDICOMIOD pIOD, L_BOOL bTree);
pDICOMIOD EXT_FUNCTION L_DicomGetLastIOD         (pDICOMIOD pIOD, L_BOOL bTree);
pDICOMIOD EXT_FUNCTION L_DicomGetPrevIOD         (pDICOMIOD pIOD, L_BOOL bTree);
pDICOMIOD EXT_FUNCTION L_DicomGetNextIOD         (pDICOMIOD pIOD, L_BOOL bTree);
L_BOOL    EXT_FUNCTION L_DicomExistsIOD          (pDICOMIOD pIOD);
L_UINT32  EXT_FUNCTION L_DicomGetCountModuleIOD  (L_UINT32 nClass);

//---------------------------------------------------------------------------
// Searching Functions
//---------------------------------------------------------------------------
pDICOMIOD EXT_FUNCTION L_DicomFindIOD            (pDICOMIOD pIOD, L_UINT32 nCode, L_CHAR nType, L_BOOL bTree);
pDICOMIOD EXT_FUNCTION L_DicomFindClassIOD       (L_UINT32 nClass);
pDICOMIOD EXT_FUNCTION L_DicomFindModuleIOD      (L_UINT32 nClass, L_UINT32 nModule);
pDICOMIOD EXT_FUNCTION L_DicomFindIndexModuleIOD (L_UINT32 nClass, L_UINT32 nIndex);

//---------------------------------------------------------------------------
// Modification Functions
//---------------------------------------------------------------------------
L_BOOL    EXT_FUNCTION L_DicomSetNameIOD         (pDICOMIOD pIOD, L_CHAR *pszName);
L_BOOL    EXT_FUNCTION L_DicomSetDescriptionIOD  (pDICOMIOD pIOD, L_CHAR *pszDescription);

#ifdef __cplusplus
};
#endif

enum
{
   CLASS_CR_IMAGE_STORAGE=0,
   CLASS_CT_IMAGE_STORAGE,
   CLASS_MR_IMAGE_STORAGE,
   CLASS_NM_IMAGE_STORAGE,
   CLASS_NM_IMAGE_STORAGE_RETIRED,
   CLASS_US_IMAGE_STORAGE,
   CLASS_US_IMAGE_STORAGE_RETIRED,
   CLASS_US_MULTI_FRAME_IMAGE_STORAGE,
   CLASS_US_MULTI_FRAME_IMAGE_STORAGE_RETIRED,
   CLASS_SC_IMAGE_STORAGE,
   CLASS_STANDALONE_OVERLAY_STORAGE,
   CLASS_STANDALONE_CURVE_STORAGE,
   CLASS_BASIC_STUDY_DESCRIPTOR,
   CLASS_STANDALONE_MODALITY_LUT_STORAGE,
   CLASS_STANDALONE_VOI_LUT_STORAGE,
   CLASS_XA_IMAGE_STORAGE,
   CLASS_XA_BIPLANE_IMAGE_STORAGE_RETIRED,
   CLASS_XRF_IMAGE_STORAGE,
   CLASS_RT_IMAGE_STORAGE,
   CLASS_RT_DOSE_STORAGE,
   CLASS_RT_STRUCTURE_SET_STORAGE,
   CLASS_RT_PLAN_STORAGE,
   CLASS_PET_IMAGE_STORAGE,
   CLASS_STANDALONE_PET_CURVE_STORAGE,
   CLASS_STORED_PRINT_STORAGE,
   CLASS_HC_GRAYSCALE_IMAGE_STORAGE,
   CLASS_HC_COLOR_IMAGE_STORAGE,
   CLASS_DX_IMAGE_STORAGE_PRESENTATION,
   CLASS_DX_IMAGE_STORAGE_PROCESSING,
   CLASS_DX_MAMMOGRAPHY_IMAGE_STORAGE_PRESENTATION,
   CLASS_DX_MAMMOGRAPHY_IMAGE_STORAGE_PROCESSING,
   CLASS_DX_INTRAORAL_IMAGE_STORAGE_PRESENTATION,
   CLASS_DX_INTRAORAL_IMAGE_STORAGE_PROCESSING,
   CLASS_RT_BEAMS_TREATMENT_RECORD_STORAGE,
   CLASS_RT_BRACHY_TREATMENT_RECORD_STORAGE,
   CLASS_RT_TREATMENT_SUMMARY_RECORD_STORAGE,
   CLASS_VL_ENDOSCOPIC_IMAGE_STORAGE,
   CLASS_VL_MICROSCOPIC_IMAGE_STORAGE,
   CLASS_VL_SLIDE_COORDINATES_MICROSCOPIC_IMAGE_STORAGE,
   CLASS_VL_PHOTOGRAPHIC_IMAGE_STORAGE,
   
   CLASS_PATIENT,
   CLASS_VISIT,
   CLASS_STUDY,
   CLASS_STUDY_COMPONENT,
   CLASS_RESULTS,
   CLASS_INTERPRETATION,
   CLASS_BASIC_FILM_SESSION,
   CLASS_BASIC_FILM_BOX,
   CLASS_BASIC_GRAYSCALE_IMAGE_BOX,
   CLASS_BASIC_COLOR_IMAGE_BOX,
   CLASS_BASIC_ANNOTATION_BOX,
   CLASS_PRINT_JOB,
   CLASS_PRINTER,
   CLASS_VOI_LUT_BOX_RETIRED,
   CLASS_IMAGE_OVERLAY_BOX_RETIRED,
   CLASS_STORAGE_COMMITMENT_PUSH_MODEL,
   CLASS_STORAGE_COMMITMENT_PULL_MODEL,
   CLASS_PRINT_QUEUE,
   CLASS_MODALITY_PERFORMED_PROCEDURE_STEP,
   CLASS_PRESENTATION_LUT,
   CLASS_PULL_PRINT_REQUEST,
   CLASS_PATIENT_META,
   CLASS_STUDY_META,
   CLASS_RESULTS_META,
   CLASS_BASIC_GRAYSCALE_PRINT_META,
   CLASS_BASIC_COLOR_PRINT_META,
   CLASS_REFERENCED_GRAYSCALE_PRINT_META_RETIRED,
   CLASS_REFERENCED_COLOR_PRINT_META_RETIRED,
   CLASS_PULL_STORED_PRINT_META,
   CLASS_PRINTER_CONFIGURATION,
   CLASS_BASIC_PRINT_IMAGE_OVERLAY_BOX,

   CLASS_BASIC_DIRECTORY,

   CLASS_PATIENT_ROOT_QUERY_PATIENT,
   CLASS_PATIENT_ROOT_QUERY_STUDY,
   CLASS_PATIENT_ROOT_QUERY_SERIES,
   CLASS_PATIENT_ROOT_QUERY_IMAGE,
   CLASS_STUDY_ROOT_QUERY_STUDY,
   CLASS_STUDY_ROOT_QUERY_SERIES,
   CLASS_STUDY_ROOT_QUERY_IMAGE,
   CLASS_PATIENT_STUDY_QUERY_PATIENT,
   CLASS_PATIENT_STUDY_QUERY_STUDY,

   CLASS_BASIC_TEXT_SR,
   CLASS_ENHANCED_SR,
   CLASS_COMPREHENSIVE_SR,

   CLASS_MODALITY_WORKLIST,

   CLASS_GRAYSCALE_SOFTCOPY_PRESENTATION_STATE,
   CLASS_BASIC_VOICE_AUDIO,                    
   CLASS_12_LEAD_ECG,                          
   CLASS_GENERAL_ECG,                          
   CLASS_AMBULATORY_ECG,                       
   CLASS_HEMODYNAMIC,                          
   CLASS_BASIC_CARDIAC_EP,

   CLASS_ENHANCED_MR_IMAGE_STORAGE,
   CLASS_MR_SPECTROSCOPY_STORAGE,
   CLASS_RAW_DATA_STORAGE,
   CLASS_SC_MULTI_FRAME_SINGLE_BIT_IMAGE_STORAGE,
   CLASS_SC_MULTI_FRAME_GRAYSCALE_BYTE_IMAGE_STORAGE,
   CLASS_SC_MULTI_FRAME_GRAYSCALE_WORD_IMAGE_STORAGE,
   CLASS_SC_MULTI_FRAME_TRUE_COLOR_IMAGE_STORAGE,
   CLASS_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP,
   CLASS_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEP,
   CLASS_GENERAL_PURPOSE_WORKLIST_MANAGEMENT_META,
   CLASS_KEY_OBJECT_SELECTION_DOCUMENT,
   CLASS_MAMMOGRAPHY_CAD_SR,
   CLASS_CHEST_CAD_SR,
   CLASS_GENERAL_PURPOSE_WORKLIST,

   CLASS_MAX,
};

#define CLASS_UNKNOWN  65535

enum
{
   MODULE_PATIENT=0,
   MODULE_GENERAL_STUDY,
   MODULE_PATIENT_STUDY,
   MODULE_GENERAL_SERIES,
   MODULE_CR_SERIES,
   MODULE_GENERAL_EQUIPMENT,
   MODULE_GENERAL_IMAGE,
   MODULE_IMAGE_PIXEL,
   MODULE_CONTRAST_BOLUS,
   MODULE_CR_IMAGE,
   MODULE_OVERLAY_PLANE,
   MODULE_CURVE,
   MODULE_MODALITY_LUT,
   MODULE_VOI_LUT,
   MODULE_SOP_COMMON,
   MODULE_FRAME_OF_REFERENCE,
   MODULE_IMAGE_PLANE,
   MODULE_CT_IMAGE,
   MODULE_MR_IMAGE,
   MODULE_NM_PET_PATIENT_ORIENTATION,
   MODULE_NM_IMAGE_PIXEL,
   MODULE_MULTI_FRAME,
   MODULE_NM_MULTI_FRAME,
   MODULE_NM_IMAGE,
   MODULE_NM_ISOTOPE,
   MODULE_NM_DETECTOR,
   MODULE_NM_TOMO_ACQUISITION,
   MODULE_NM_MULTI_GATED_ACQUISITION,
   MODULE_NM_PHASE,
   MODULE_NM_RECONSTRUCTION,
   MODULE_MULTI_FRAME_OVERLAY,
   MODULE_US_FRAME_OF_REFERENCE,
   MODULE_PALETTE_COLOR_LOOCKUP_TABLE,
   MODULE_US_REGION_CALIBRATION,
   MODULE_US_IMAGE,
   MODULE_CURVE_IDENTIFICATION,
   MODULE_AUDIO,
   MODULE_CINE,
   MODULE_SC_EQUIPMENT,
   MODULE_SC_IMAGE,
   MODULE_OVERLAY_IDENTIFICATION,
   MODULE_PATIENT_SUMMARY,
   MODULE_STUDY_CONTENT,
   MODULE_LUT_IDENTIFICATION,
   MODULE_FRAME_POINTERS,
   MODULE_MASK,
   MODULE_DISPLAY_SHUTTER,
   MODULE_DEVICE,
   MODULE_THERAPY,
   MODULE_XA_IMAGE,
   MODULE_XA_ACQUISITION,
   MODULE_XA_COLLIMATOR,
   MODULE_XA_TABLE,
   MODULE_XA_POSITIONER,
   MODULE_BIPLANE_SEQUENCE,
   MODULE_BIPLANE_OVERLAY,
   MODULE_BIPLANE_IMAGE,
   MODULE_XRF_POSITIONER,
   MODULE_XRF_TOMO_ACQUISITION,
   MODULE_RT_SERIES,
   MODULE_RT_IMAGE,
   MODULE_APPROVAL,
   MODULE_RT_DOSE,
   MODULE_RT_DVH,
   MODULE_STRUCTURE_SET,
   MODULE_ROI_CONTOUR,
   MODULE_RT_DOSE_ROI,
   MODULE_RT_OBSERVATIONS,
   MODULE_RT_GENERAL_PLAN,
   MODULE_RT_PRESCRIPTION,
   MODULE_RT_TOLERANCE_TABLES,
   MODULE_RT_PATIENT_SETUP,
   MODULE_RT_FRACTION_SCHEME,
   MODULE_RT_BEAMS,
   MODULE_RT_BRACHY_APPLICATION_SETUPS,
   MODULE_PET_SERIES,
   MODULE_PET_ISOTOPE,
   MODULE_PET_MULTIGATED_ACQUISITION,
   MODULE_PET_IMAGE,
   MODULE_PET_CURVE,
   MODULE_PRINTER_CHARACTERISTICS,
   MODULE_FILM_BOX,
   MODULE_IMAGE_BOX_LIST,
   MODULE_ANNOTATION_LIST,
   MODULE_IMAGE_OVERLAY_BOX_LIST,
   MODULE_PRESENTATION_LUT_LIST,
   MODULE_HC_EQUIPMENT,
   MODULE_HC_GRAYSCALE_IMAGE,
   MODULE_HC_COLOR_IMAGE,
   MODULE_PATIENT_RELATIONSHIP,
   MODULE_PATIENT_IDENTIFICATION,
   MODULE_PATIENT_DEMOGRAPHIC,
   MODULE_PATIENT_MEDICAL,
   MODULE_VISIT_RELATIONSHIP,
   MODULE_VISIT_IDENTIFICATION,
   MODULE_VISIT_ADMISSION,
   MODULE_VISIT_STATUS,
   MODULE_VISIT_DISCHARGE,
   MODULE_VISIT_SCHEDULING,
   MODULE_STUDY_RELATIONSHIP,
   MODULE_STUDY_IDENTIFICATION,
   MODULE_STUDY_CLASSIFICATION,
   MODULE_STUDY_SCHEDULING,
   MODULE_STUDY_ACQUISITION,
   MODULE_STUDY_READ,
   MODULE_STUDY_COMPONENT_RELATIONSHIP,
   MODULE_STUDY_COMPONENT_ACQUISITION,
   MODULE_STUDY_COMPONENT,
   MODULE_RESULTS_RELATIONSHIP,
   MODULE_RESULTS_IDENTIFICATION,
   MODULE_RESULTS_IMPRESSIONS,
   MODULE_INTERPRETATION_RELATIONSHIP,
   MODULE_INTERPRETATION_IDENTIFICATION,
   MODULE_INTERPRETATION_STATE,
   MODULE_INTERPRETATION_RECORDING,
   MODULE_INTERPRETATION_TRANSCRIPTION,
   MODULE_INTERPRETATION_APPROVAL,
   MODULE_BASIC_FILM_SESSION_PRESENTATION,
   MODULE_BASIC_FILM_SESSION_RELATIONSHIP,
   MODULE_BASIC_FILM_BOX_PRESENTATION,
   MODULE_BASIC_FILM_BOX_RELATIONSHIP,
   MODULE_IMAGE_BOX_PRESENTATION_GRAYSCALE,
   MODULE_IMAGE_BOX_PRESENTATION_COLOR,
   MODULE_IMAGE_BOX_RELATIONSHIP,
   MODULE_BASIC_ANNOTATION_PRESENTATION,
   MODULE_PRINT_JOB,
   MODULE_PRINTER,
   MODULE_IMAGE_OVERLAY_BOX_PRESENTATION,
   MODULE_IMAGE_OVERLAY_BOX_RELATIONSHIP,
   MODULE_STORAGE_COMMITMENT,
   MODULE_GENERAL_QUEUE,
   MODULE_PRINT_QUEUE,
   MODULE_PERFORMED_PROCEDURE_STEP_RELATIONSHIP,
   MODULE_PERFORMED_PROCEDURE_STEP_INFORMATION,
   MODULE_IMAGE_ACQUISITION_RESULTS,
   MODULE_RADIATION_DOSE,
   MODULE_BILLING_AND_MATERIAL_MANAGEMENT_CODES,
   MODULE_PRESENTATION_LUT,
   MODULE_PRINT_REQUEST,
   MODULE_PATIENT_RELATIONSHIP_META,
   MODULE_NM_SERIES_RETIRED,                      
   MODULE_NM_EQUIPMENT_RETIRED,                   
   MODULE_NM_IMAGE_RETIRED,                               
   MODULE_NM_SPECT_ACQUISITION_IMAGE_RETIRED,     
   MODULE_NM_MULTI_GATED_ACQUISITION_IMAGE_RETIRED,
   MODULE_US_FRAME_OF_REFERENCE_RETIRED,
   MODULE_US_REGION_CALIBRATION_RETIRED,
   MODULE_US_IMAGE_RETIRED,             
   
   MODULE_FILESET_IDENTIFICATION,
   MODULE_DIRECTORY_INFORMATION,
   MODULE_PATIENT_KEY,
   MODULE_STUDY_KEY,
   MODULE_SERIES_KEY,
   MODULE_IMAGE_KEY,
   MODULE_OVERLAY_KEY,
   MODULE_MODALITY_LUT_KEY,
   MODULE_VOI_LUT_KEY,
   MODULE_CURVE_KEY,
   MODULE_STORED_PRINT_KEY,
   MODULE_RT_DOSE_KEY,
   MODULE_RT_STRUCTURE_SET_KEY,
   MODULE_RT_PLAN_KEY,
   MODULE_RT_TREATMENT_RECORD_KEY,
   MODULE_TOPIC_KEY,
   MODULE_VISIT_KEY,
   MODULE_RESULTS_KEY,
   MODULE_INTERPRETATION_KEY,
   MODULE_STUDY_COMPONENT_KEY,
   MODULE_PRIVATE_KEY,

   MODULE_SPECIMEN_IDENTIFICATION,
   MODULE_DX_SERIES,
   MODULE_DX_ANATOMY_IMAGED,
   MODULE_DX_IMAGE,         
   MODULE_DX_DETECTOR,      
   MODULE_DX_POSITIONING,
   MODULE_ACQUISITION_CONTEXT,
   MODULE_XA_ACQUISITION_DOSE,
   MODULE_XA_GENERATION,
   MODULE_XA_FILTRATION,
   MODULE_XA_GRID,
   MODULE_IMAGE_HISTOGRAM,
   MODULE_MAMMOGRAPHY_SERIES,
   MODULE_MAMMOGRAPHY_IMAGE,
   MODULE_INTRAORAL_SERIES,
   MODULE_INTRAORAL_IMAGE,

   MODULE_RT_GENERAL_TREATMENT_RECORD,
   MODULE_RT_TREATMENT_MACHINE_RECORD,
   MODULE_MEASURED_DOSE_REFERENCE_RECORD,
   MODULE_CALCULATED_DOSE_REFERENCE_RECORD,
   MODULE_RT_BEAMS_SESSION_RECORD,
   MODULE_RT_TREATMENT_SUMMARY_RECORD,
   MODULE_RT_BRACHY_SESSION_RECORD,

   MODULE_VL_IMAGE,
   MODULE_SLIDE_COORDINATES,

   MODULE_BASIC_PRINT_IMAGE_OVERLAY_BOX,
   MODULE_PRINTER_CONFIGURATION,

   MODULE_SR_DOCUMENT_SERIES,
   MODULE_SR_DOCUMENT_GENERAL,
   MODULE_SR_DOCUMENT_CONTENT,
   MODULE_SR_DOCUMENT_KEY,

   MODULE_SCHEDULED_PROCEDURE_STEP,
   MODULE_REQUESTED_PROCEDURE,
   MODULE_IMAGING_SERVICE_REQUEST,

   MODULE_PRESENTATION_SERIES,
   MODULE_PRESENTATION_STATE,
   MODULE_BITMAP_DISPLAY_SHUTTER,
   MODULE_OVERLAY_CURVE_ACTIVATION,
   MODULE_DISPLAYED_AREA,
   MODULE_GRAPHIC_ANNOTATION,
   MODULE_SPATIAL_TRANSFORMATION,
   MODULE_GRAPHIC_LAYER,
   MODULE_SOFTCOPY_VOI_LUT,
   MODULE_SOFTCOPY_PRESENTATION_LUT,
   MODULE_SYNCHRONIZATION,
   MODULE_WAVEFORM_IDENTIFICATION,
   MODULE_WAVEFORM,
   MODULE_WAVEFORM_ANNOTATION,
   MODULE_PRESENTATION_KEY,
   MODULE_WAVEFORM_KEY,

   MODULE_CLINICAL_TRIAL_SUBJECT,
   MODULE_CLINICAL_TRIAL_STUDY,
   MODULE_CLINICAL_TRIAL_SERIES,
   MODULE_MULTI_FRAME_FUNCTIONAL_GROUPS,
   MODULE_MULTI_FRAME_DIMENSION,
   MODULE_CARDIAC_SYNCHRONIZATION,
   MODULE_RESPIRATORY_SYNCHRONIZATION,
   MODULE_BULK_MOTION_SYNCHRONIZATION,
   MODULE_SUPPLEMENTAL_PALETTE_COLOR_LOOKUP_TABLE,
   MODULE_ENHANCED_MR_IMAGE,
   MODULE_MR_PULSE_SEQUENCE,
   MODULE_MR_SPECTROSCOPY,
   MODULE_MR_SPECTROSCOPY_PULSE_SEQUENCE,
   MODULE_MR_SPECTROSCOPY_DATA,
   MODULE_RAW_DATA,
   MODULE_SC_MULTI_FRAME_IMAGE,
   MODULE_SC_MULTI_FRAME_VECTOR,
   MODULE_KEY_OBJECT_DOCUMENT_SERIES,
   MODULE_KEY_OBJECT_DOCUMENT,
   MODULE_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_RELATIONSHIP,
   MODULE_GENERAL_PURPOSE_SCHEDULED_PROCEDURE_STEP_INFORMATION,
   MODULE_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEP_RELATIONSHIP,
   MODULE_GENERAL_PURPOSE_PERFORMED_PROCEDURE_STEP_INFORMATION,
   MODULE_GENERAL_PURPOSE_RESULTS,
   MODULE_KEY_OBJECT_DOCUMENT_KEY,

   MODULE_MAX,
};

//============= CLASS ==========================================================

#define MAKETAG(nGroup,nElement) ((L_UINT32)((((L_UINT32)nGroup) << 16) | nElement))
#define GETGROUP(nTag)           ((L_UINT16)(nTag >> 16))
#define GETELEMENT(nTag)         ((L_UINT16)(nTag & 0xFFFF))

#define DS_METAHEADER_PRESENT          0x0001U
#define DS_METAHEADER_ABSENT           0x0002U
#define DS_LITTLE_ENDIAN               0x0004U
#define DS_BIG_ENDIAN                  0x0008U
#define DS_IMPLICIT_VR                 0x0010U
#define DS_EXPLICIT_VR                 0x0020U
#define DS_GROUP_LENGTHS               0x0040U
#define DS_LENGTH_EXPLICIT             0x0080U
#define DS_EXCLUDE_METAHEADER_GROUP    0x0100U
#define DS_LOAD_CLOSE                  0x0200U
#define DS_KEEP_PIXEL_DATA_INTACT      0x0400U


enum
{
   IMAGE_COMPRESSION_NONE,
   IMAGE_COMPRESSION_RLE,
   IMAGE_COMPRESSION_JPEG_LOSSLESS,
   IMAGE_COMPRESSION_JPEG_LOSSY,
   IMAGE_COMPRESSION_JPEG_LS_LOSSLESS,
   IMAGE_COMPRESSION_JPEG_LS_LOSSY,
   IMAGE_COMPRESSION_J2K_LOSSLESS,
   IMAGE_COMPRESSION_J2K_LOSSY
};

enum
{
   IMAGE_PHOTOMETRIC_MONOCHROME1,
   IMAGE_PHOTOMETRIC_MONOCHROME2,
   IMAGE_PHOTOMETRIC_PALETTE_COLOR,
   IMAGE_PHOTOMETRIC_RGB,
   IMAGE_PHOTOMETRIC_ARGB,
   IMAGE_PHOTOMETRIC_CMYK,
   IMAGE_PHOTOMETRIC_YBR_FULL_422,
   IMAGE_PHOTOMETRIC_YBR_FULL,
   IMAGE_PHOTOMETRIC_YBR_RCT,
   IMAGE_PHOTOMETRIC_YBR_ICT
};



#define DS_PREAMBLE_LENGTH             128
#define DS_PREFIX_LENGTH               4
#define DS_PREFIX                      "DICM"

#define ELEMENT_LENGTH_MAX             0xFFFFFFFFUL
#define ELEMENT_INDEX_MAX              0xFFFFFFFFUL

//typedef struct _DICOMELEMENT DICOMELEMENT, *pDICOMELEMENT;
typedef struct _DICOMELEMENT
{
   GENERICLINK           // Reserved - internally used only

   L_UINT32   nTag;      // Data Element Tag
   L_UINT16   nVR;       // Value Representation
   L_UINT32   nLength;
   
   L_UINT32   nVM;       // Reserved - internally used only
   L_CHAR    *pValue;    // Reserved - internally used only
   L_UINT32   nAttach;   // Reserved - internally used only
   L_UINT32  *pOffset;   // Reserved - internally used only
   L_VOID   **pFile;     // Reserved - internally used only
   L_UINT32  *pSize;     // Reserved - internally used only
   L_UINT32   nCount;    // Reserved - internally used only
} DICOMELEMENT, *pDICOMELEMENT;

//typedef struct _DICOMMODULE DICOMMODULE, *pDICOMMODULE;
typedef struct _DICOMMODULE
{
   L_UINT32      nModule;         // Module code
   L_UINT32      nCount;          // Number of elements
   pDICOMELEMENT pElement[1000];  // Pointers to elements
} DICOMMODULE, *pDICOMMODULE;

#define VALUE_AGE_DAYS   'D'
#define VALUE_AGE_WEEKS  'W'
#define VALUE_AGE_MONTHS 'M'
#define VALUE_AGE_YEARS  'Y'

typedef struct _VALUEAGE
{
   L_UINT16 nNumber;       // A value
   L_CHAR   nReference;    // Reference of age (VALUE_AGE_DAYS, VALUE_AGE_WEEKS, ...)
} VALUEAGE, *pVALUEAGE;

typedef struct _VALUEDATE
{
   L_UINT16 nYear;         // Year
   L_UINT16 nMonth;        // Month
   L_UINT16 nDay;          // Day
} VALUEDATE, *pVALUEDATE;

#define VALUE_RANGE_NONE   0 //only Date1 is valid, represents single date, not a range
#define VALUE_RANGE_LOWER  1 //only Date1 is valid, represents lower range, "1/1/01-"
#define VALUE_RANGE_UPPER  2 //only Date1 is valid, represents upper range, "-9/9/01"
#define VALUE_RANGE_BOTH   3 //Date1 & Date2 valid, represents full range,  "1/1/01-9/9/01"


typedef struct _VALUETIME
{
   L_UINT16 nHours;        // Hours
   L_UINT16 nMinutes;      // Minutes
   L_UINT16 nSeconds;      // Seconds
   L_UINT32 nFractions;    // Fractional Second
} VALUETIME, *pVALUETIME;

typedef struct _VALUEDATETIME
{
   L_UINT16 nYear;         // Year
   L_UINT16 nMonth;        // Month
   L_UINT16 nDay;          // Day
   L_UINT16 nHours;        // Hours
   L_UINT16 nMinutes;      // Minutes
   L_UINT16 nSeconds;      // Seconds
   L_UINT32 nFractions;    // Fractional Second
   L_INT32  nOffset;       // Optional suffix for plus/minus offset from Coordinated Universal Time
} VALUEDATETIME, *pVALUEDATETIME;

typedef struct _VALUEDATERANGE
{
   L_UINT32 nFlags;        // Flags
   VALUEDATE Date1;        // Date1
   VALUEDATE Date2;        // Date2
} VALUEDATERANGE, *pVALUEDATERANGE;

typedef struct _VALUETIMERANGE
{
   L_UINT32 nFlags;        // Flags
   VALUETIME Time1;        // Time1
   VALUETIME Time2;        // Time2
} VALUETIMERANGE, *pVALUETIMERANGE;

typedef struct _VALUEDATETIMERANGE
{
   L_UINT32 nFlags;         // Flags
   VALUEDATETIME DateTime1; // DateTime1
   VALUEDATETIME DateTime2; // DateTime2
} VALUEDATETIMERANGE, *pVALUEDATETIMERANGE;

typedef struct _DICOMIMAGE
{
   L_INT32  nCompression;
   L_CHAR   szPhotometric[30];
   L_INT32  nPhotometric;
   L_UINT32 nSamplesPerPixel;
   L_INT32  nRows;
   L_INT32  nColumns;
   L_UINT32 nBitsAllocated;
   L_UINT32 nBitsStored;
   L_UINT32 nHighBit;
   L_INT32  nPixelRepresentation;
   L_INT32  nPlanarConfiguration;
   L_INT32  nResolutionX;
   L_INT32  nResolutionY;
   L_INT32  nSmallestImagePixelValue;
   L_BOOL   bSmallestImagePixelValue;
   L_INT32  nLargestImagePixelValue;
   L_BOOL   bLargestImagePixelValue;
   L_UINT32 nRedEntries;
   L_UINT32 nRedFirst;
   L_UINT32 nRedBits;
   L_UINT32 nGreenEntries;
   L_UINT32 nGreenFirst;
   L_UINT32 nGreenBits;
   L_UINT32 nBlueEntries;
   L_UINT32 nBlueFirst;
   L_UINT32 nBlueBits;
   L_UINT32 nPaletteEntries;
   L_UINT32 nPaletteFirst;
   L_INT32  nBitsPerPixel;
   L_BOOL   bGray;
   L_UINT32 nFrames;
} DICOMIMAGE, *pDICOMIMAGE;

typedef struct _IMAGEINFO IMAGEINFO, *pIMAGEINFO;

typedef struct _DICOMNETDEBUGINFOONSEND
{
   L_INT       nSize ;// The size of this structure
   L_INT       nError;// error code
   L_UCHAR     nType ;// type of message/data sent
   L_UINT32    nBytes;// number of bytes of data sent
   L_CHAR      *pSentData;//Data itself
}DICOMNETDEBUGINFOONSEND, *pDICOMNETDEBUGINFOONSEND;

// Data Commands
#define COMMAND_C_STORE           0x0001
#define COMMAND_C_FIND            0x0020
#define COMMAND_C_GET             0x0010
#define COMMAND_C_MOVE            0x0021
#define COMMAND_C_CANCEL          0x0FFF
#define COMMAND_C_ECHO            0x0030
#define COMMAND_N_REPORT          0x0100
#define COMMAND_N_GET             0x0110
#define COMMAND_N_SET             0x0120
#define COMMAND_N_ACTION          0x0130
#define COMMAND_N_CREATE          0x0140
#define COMMAND_N_DELETE          0x0150

#define COMMAND_REQUEST           0x0000
#define COMMAND_RESPONSE          0x8000

// Values for the element TAG_DATA_SET_TYPE
#define COMMAND_DATASET_PRESENT    0x0000
#define COMMAND_DATASET_IDENTIFIER 0x0102
#define COMMAND_DATASET_ABSENT     0x0101

// Values for the element TAG_STATUS
#define COMMAND_STATUS_SUCCESS                           0x0000   // Success
#define COMMAND_STATUS_CANCEL                            0xFE00   // Cancel
#define COMMAND_STATUS_ATTRIBUTE_LIST_ERROR              0x0107   // Attribute list error
#define COMMAND_STATUS_ATTRIBUTE_OUT_OF_RANGE            0x0116   // Attribute Value Out of Range
#define COMMAND_STATUS_CLASS_NOT_SUPPORTED               0x0122   // Class not supported
#define COMMAND_STATUS_CLASE_INSTANCE_CONFLICT           0x0119   // Class-instance conflict
#define COMMAND_STATUS_DUPLICATE_INSTANCE                0x0111   // Duplicate instance
#define COMMAND_STATUS_DUPLICATE_INVOCATION              0x0210   // Duplicate invocation
#define COMMAND_STATUS_INVALID_ARGUMENT_VALUE            0x0115   // Invalid argument value
#define COMMAND_STATUS_INVALID_ATTRIBUTE_VALUE           0x0106   // Invalid attribute value
#define COMMAND_STATUS_INVALID_OBJECT_INSTANCE           0x0117   // Ivalid object instance
#define COMMAND_STATUS_MISSING_ATTRIBUTE                 0x0120   // Missing attribute
#define COMMAND_STATUS_MISSING_ATTRIBUTE_VALUE           0x0121   // Missing attribute value
#define COMMAND_STATUS_MISTYPED_ARGUMENT                 0x0212   // Mistyped argument
#define COMMAND_STATUS_NO_SUCH_ARGUMENT                  0x0114   // No such argument
#define COMMAND_STATUS_NO_SUCH_ATTRIBUTE                 0x0105   // No such attribute
#define COMMAND_STATUS_NO_SUCH_EVENT_TYPE                0x0113   // No such event type
#define COMMAND_STATUS_NO_SUCH_OBJECT_INSTANCE           0x0112   // No such object instance
#define COMMAND_STATUS_NO_SUCH_CLASS                     0x0118   // No such class
#define COMMAND_STATUS_PROCESSING_FAILURE                0x0110   // Proccesing failure
#define COMMAND_STATUS_RESOURCE_LIMITATION               0x0213   // Resource limitation
#define COMMAND_STATUS_UNRECOGNIZED_OPERATION            0x0211   // Unrecognized operation
#define COMMAND_STATUS_REFUSED_UNABLE_CALCULATE_MATCHES  0xA701   // Out of Resources - unable to calculate number of matches
#define COMMAND_STATUS_REFUSED_UNABLE_PERFORM_SUB_OPS    0xA702   // Out of Resources - Unable to perform sub-operations
#define COMMAND_STATUS_REFUSED_MOVE_DESTINATION_UNKNOWN  0xA801   // Move Destination Unknown
#define COMMAND_STATUS_FAILURE                           0xC001   // Move Destination Unknown
#define COMMAND_STATUS_RESERVED2                         0xC002   //
#define COMMAND_STATUS_RESERVED3                         0xC003   //
#define COMMAND_STATUS_RESERVED4                         0xC004   //
#define COMMAND_STATUS_WARNING                           0xB000   // Sub-operations Complete - One or more failures
#define COMMAND_STATUS_PENDING                           0xFF00   // Matches are continuing - Current Match is supplied and any Optional Keys were supported in the same manner as Required Keys.
#define COMMAND_STATUS_PENDING_WARNING                   0xFF01   // Matches are continuing - Warning that one or more Optional Keys were not supported for existence and/or matching for this Identifier.

// Values for the element TAG_PRIORITY
#define COMMAND_PRIORITY_LOW            0x0002
#define COMMAND_PRIORITY_MEDIUM         0x0000
#define COMMAND_PRIORITY_HIGH           0x0001


// Values for CONFORMANCECALLBACK
#define CALLBACK_ERROR_UNKNOWN_CLASS    0x0001
#define CALLBACK_ERROR_UNKNOWN_TAG      0x0002
#define CALLBACK_ERROR_UNKNOWN_VR       0x0004
#define CALLBACK_ERROR_WRONG_VR         0x0008
#define CALLBACK_ERROR_MIN_VM           0x0010
#define CALLBACK_ERROR_MAX_VM           0x0020
#define CALLBACK_ERROR_DIVIDE_VM        0x0040
#define CALLBACK_ERROR_IMAGE            0x0080
#define CALLBACK_ERROR_ELEMENT          0x0100

#ifndef HANNOBJECT
typedef HANDLE HANNOBJECT;
#endif

#ifndef pHANNOBJECT
typedef HANNOBJECT L_FAR *pHANNOBJECT;
#endif

typedef L_BOOL (pEXT_CALLBACK CONFORMANCECALLBACK) (pDICOMELEMENT pElement, L_UINT16 nFlags, L_VOID *pUserData);

typedef L_VOID *HDICOMDS;

typedef L_INT ( pEXT_FUNCTION pL_ANNSAVEMEMORY )(HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               HGLOBAL L_FAR *phMem,
                               L_UINT32 L_FAR * puMemSize,
                               pSAVEFILEOPTION pSaveOptions);

typedef L_INT ( pEXT_FUNCTION pL_ANNLOADMEMORY )(L_UCHAR L_FAR * pMem,
                               L_UINT32 uMemSize,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);

typedef L_INT ( pEXT_FUNCTION pL_ANNDELETEPAGEMEMORY )(HGLOBAL hMem, L_UINT32 *puMemSize, L_INT32 nPage);


/*sb: these typedefs moved to LTFIL_.H
typedef L_INT (pEXT_FUNCTION FLTLOADBUFFER) (L_CHAR *pInput, L_UINT32 nLength, L_CHAR *pOutput, L_INT nFormat, L_INT32 nWidth, L_INT32 nHeight, L_UINT32 nBitsPerPixel, L_VOID *pLeadHdr, L_UINT   uFlags);
typedef L_INT (pEXT_FUNCTION FLTSAVEBUFFER) (L_UCHAR L_FAR*pInput, LPBITMAPINFOHEADER pbiInput, L_UCHAR L_FAR*pOutput, L_UINT32 L_FAR*pdwSize, L_INT32 nQFactor, L_UINT uFlags, L_UINT nFormat, L_UCHAR L_FAR*pTopBuffer, L_INT nTopBufferHeight);
*/

typedef enum tagDICOM_TRANSFER_SYNTAXES
{
   TRANSFER_SYNTAX_IMPLICIT_VR_LITTLE_ENDIAN ,//1.2.840.10008.1.2
   TRANSFER_SYNTAX_EXPLICIT_VR_LITTLE_ENDIAN ,//1.2.840.10008.1.2.1
   TRANSFER_SYNTAX_EXPLICIT_VR_BIG_ENDIAN    ,//1.2.840.10008.1.2.2
   TRANSFER_SYNTAX_RLE_LOSSLESS              ,//1.2.840.10008.1.2.5
   TRANSFER_SYNTAX_JPEG_BASELINE_1           ,//1.2.840.10008.1.2.4.50
   TRANSFER_SYNTAX_JPEG_EXTENDED_2_4         ,//1.2.840.10008.1.2.4.51
   TRANSFER_SYNTAX_JPEG_LOSSLESS_NONHIER_14  ,//1.2.840.10008.1.2.4.57
   TRANSFER_SYNTAX_JPEG_LOSSLESS_NONHIER_14B ,//1.2.840.10008.1.2.4.70
   TRANSFER_SYNTAX_JPEG2000_LOSSLESS_ONLY    ,//1.2.840.10008.1.2.4.90
   TRANSFER_SYNTAX_JPEG2000                   //1.2.840.10008.1.2.4.91  
}
DICOM_TRANSFER_SYNTAXES, *pDICOM_TRANSFER_SYNTAXES;



#ifdef __cplusplus

#if !defined(_WIN32_WCE)
class DICOM_EXPORT LDicomNet;
#endif /* _WIN32_WCE */


class DICOM_EXPORT LDicomDS
{
public:
   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   LDicomDS(L_TCHAR *pszPath=NULL);
   ~LDicomDS();
   L_VOID          InitDS            (L_UINT32 nClass, L_UINT16 nFlags);
   L_VOID          GetInfoDS         (L_UINT32 *pnClass, L_UINT16 *pnFlags);

   L_VOID          InitCS            (L_UINT16 nCommand, L_BOOL bRequest);
   L_VOID          GetInfoCS         (L_UINT16 *pnCommand, L_BOOL *pbRequest);

   //---------------------------------------------------------------------------
   // Input and Output Functions
   //---------------------------------------------------------------------------
   L_UINT16        LoadDS            (L_TCHAR *pszName, L_UINT16 nFlags);
   L_UINT16        SaveDS            (L_TCHAR *pszName, L_UINT16 nFlags);
   L_UINT16        CopyDS            (pDICOMELEMENT pDstParent, LDicomDS *pSrcDS, pDICOMELEMENT pSrcParent);

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   pDICOMELEMENT   InsertElement     (pDICOMELEMENT pNeighbor, L_BOOL bChild, L_UINT32 nTag, L_UINT16 nVR, L_BOOL bSequence, L_UINT32 nIndex);
   pDICOMMODULE    InsertModule      (L_UINT32 nModule, L_BOOL bOptional);
   pDICOMELEMENT   InsertKey         (pDICOMELEMENT pParent, L_CHAR *pszKey, L_BOOL bOptional);

   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   pDICOMELEMENT   DeleteElement     (pDICOMELEMENT pElement);
   L_VOID          DeleteModule      (L_UINT32 nModule);
   L_VOID          DeleteKey         (pDICOMELEMENT pElement);
   L_VOID          ResetDS           ();

   //---------------------------------------------------------------------------
   // Iteration Functions
   //---------------------------------------------------------------------------
   pDICOMELEMENT   GetRootElement    (pDICOMELEMENT pElement);
   pDICOMELEMENT   GetParentElement  (pDICOMELEMENT pElement);
   pDICOMELEMENT   GetChildElement   (pDICOMELEMENT pElement, L_BOOL bVolatile);
   pDICOMELEMENT   GetFirstElement   (pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
   pDICOMELEMENT   GetLastElement    (pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
   pDICOMELEMENT   GetPrevElement    (pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
   pDICOMELEMENT   GetNextElement    (pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
   L_UINT32        GetLevelElement   (pDICOMELEMENT pElement);
   L_UINT32        GetCountModule    ();
   L_BOOL          ExistsElement     (pDICOMELEMENT pElement);
   L_BOOL          IsVolatileElement (pDICOMELEMENT pElement);
   L_BOOL          ConformanceDS     (CONFORMANCECALLBACK pfnCallback, L_VOID *pUserData);
   L_VOID          SetDebugDS        (CONFORMANCECALLBACK pfnCallback, L_VOID *pUserData);

   pDICOMELEMENT   GetRootKey        (pDICOMELEMENT pElement);
   pDICOMELEMENT   GetParentKey      (pDICOMELEMENT pElement);
   pDICOMELEMENT   GetChildKey       (pDICOMELEMENT pElement);
   pDICOMELEMENT   GetFirstKey       (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMELEMENT   GetLastKey        (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMELEMENT   GetPrevKey        (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMELEMENT   GetNextKey        (pDICOMELEMENT pElement, L_BOOL bTree);
   L_CHAR         *GetValueKey       (pDICOMELEMENT pElement);

   //---------------------------------------------------------------------------
   // Searching Functions
   //---------------------------------------------------------------------------
   pDICOMELEMENT   FindFirstElement  (pDICOMELEMENT pElement, L_UINT32 nTag, L_BOOL bTree);
   pDICOMELEMENT   FindLastElement   (pDICOMELEMENT pElement, L_UINT32 nTag, L_BOOL bTree);
   pDICOMELEMENT   FindPrevElement   (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMELEMENT   FindNextElement   (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMMODULE    FindModule        (L_UINT32 nModule);
   pDICOMMODULE    FindIndexModule   (L_UINT32 nIndex);

   pDICOMELEMENT   FindFirstKey      (pDICOMELEMENT pElement, L_CHAR *pszKey, L_BOOL bTree);
   pDICOMELEMENT   FindLastKey       (pDICOMELEMENT pElement, L_CHAR *pszKey, L_BOOL bTree);
   pDICOMELEMENT   FindPrevKey       (pDICOMELEMENT pElement, L_BOOL bTree);
   pDICOMELEMENT   FindNextKey       (pDICOMELEMENT pElement, L_BOOL bTree);

   //---------------------------------------------------------------------------
   // Retrieval Functions
   //---------------------------------------------------------------------------
   L_VOID          GetPreamble       (L_CHAR *pPreamble, L_UINT16 nLength);
   L_UINT32        GetCountValue     (pDICOMELEMENT pElement);
   L_VOID          FreeValue         (pDICOMELEMENT pElement);
   L_BOOL          GetBinaryValue    (pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nLength);
   L_CHAR         *GetCharValue      (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_INT16        *GetShortValue     (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_INT32        *GetLongValue      (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_FLOAT        *GetFloatValue     (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_DOUBLE       *GetDoubleValue    (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_CHAR         *GetStringValue    (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   pVALUEAGE       GetAgeValue       (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   pVALUEDATE      GetDateValue      (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);

   L_INT           GetDateRangeValue (pDICOMELEMENT pElement, L_UINT32 nIndex, pVALUEDATERANGE pValue);
   L_INT16         GetTimeRangeValue (pDICOMELEMENT pElement, L_UINT32 nIndex, pVALUETIMERANGE pValue);
   L_INT16         GetDateTimeRangeValue (pDICOMELEMENT pElement, L_UINT32 nIndex, pVALUEDATETIMERANGE pValue);


   pVALUETIME      GetTimeValue      (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   pVALUEDATETIME  GetDateTimeValue  (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
   L_UINT32        GetConvertValue   (pDICOMELEMENT pElement, L_CHAR *pszText);
   L_UINT32        GetCountImage     (pDICOMELEMENT pElement);
   L_UINT16        GetInfoImage      (pDICOMELEMENT pElement, pDICOMIMAGE pInfo, L_UINT32 nIndex);
   L_UINT16        GetImage          (pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nBitsPerPixel, L_INT32 nOrder, FILEREADCALLBACK pfnCallback, L_VOID *pUserData);
   L_UINT16        GetImageList      (pDICOMELEMENT pElement, HBITMAPLIST hList, L_UINT32 nIndex, L_UINT32 nCount, L_INT32 nBitsPerPixel, L_INT32 nOrder);

   L_BOOL          GetKeepPixelDataIntactFlag();

   L_UINT16        GetJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );
   L_UINT16        GetDefaultJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------
   L_VOID          SetPreamble       (L_CHAR *pPreamble, L_UINT16 nLength);
   L_BOOL          SetBinaryValue    (pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nLength);
   L_BOOL          SetCharValue      (pDICOMELEMENT pElement, L_CHAR *pValue, L_UINT32 nCount);
   L_BOOL          SetShortValue     (pDICOMELEMENT pElement, L_INT16 *pValue, L_UINT32 nCount);
   L_BOOL          SetLongValue      (pDICOMELEMENT pElement, L_INT32 *pValue, L_UINT32 nCount);
   L_BOOL          SetFloatValue     (pDICOMELEMENT pElement, L_FLOAT *pValue, L_UINT32 nCount);
   L_BOOL          SetDoubleValue    (pDICOMELEMENT pElement, L_DOUBLE *pValue, L_UINT32 nCount);
   L_BOOL          SetStringValue    (pDICOMELEMENT pElement, L_CHAR *pValue, L_UINT32 nCount);
   L_BOOL          SetAgeValue       (pDICOMELEMENT pElement, pVALUEAGE pValue, L_UINT32 nCount);
   L_BOOL          SetDateValue      (pDICOMELEMENT pElement, pVALUEDATE pValue, L_UINT32 nCount);
   L_BOOL          SetTimeValue      (pDICOMELEMENT pElement, pVALUETIME pValue, L_UINT32 nCount);
   L_BOOL          SetDateTimeValue  (pDICOMELEMENT pElement, pVALUEDATETIME pValue, L_UINT32 nCount);
   L_BOOL          SetDateRangeValue      (pDICOMELEMENT pElement, pVALUEDATERANGE pValue, L_UINT32 nCount);
   L_BOOL          SetTimeRangeValue      (pDICOMELEMENT pElement, pVALUETIMERANGE pValue, L_UINT32 nCount);
   L_BOOL          SetDateTimeRangeValue  (pDICOMELEMENT pElement, pVALUEDATETIMERANGE pValue, L_UINT32 nCount);
   L_BOOL          SetConvertValue   (pDICOMELEMENT pElement, L_CHAR *pszText, L_UINT32 nCount);
   L_UINT16        InsertImage       (pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor, FILESAVECALLBACK pfnCallback, L_VOID *pUserData);
   L_UINT16        InsertImageList   (pDICOMELEMENT pElement, HBITMAPLIST hList, L_UINT32 nIndex, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor);
   L_UINT16        SetImage          (pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor, FILESAVECALLBACK pfnCallback, L_VOID *pUserData);
   L_UINT16        SetImageList      (pDICOMELEMENT pElement, HBITMAPLIST hList, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor);
   L_UINT16        DeleteImage       (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
#if !defined(_WIN32_WCE)
   L_UINT16        ChangeTransferSyntax(L_CHAR *pszUID,L_INT32 nQFactor/*For lossy*/,L_UINT32 uFlags);   
#endif /* _WIN32_WCE */
   L_VOID          SetKeepPixelDataIntactFlag(L_BOOL bSet);
   
   L_UINT16        SetJ2KOptions( const pFILEJ2KOPTIONS pOptions);




   //---------------------------------------------------------------------------
   // Annotation Functions
   //---------------------------------------------------------------------------

   L_UINT16        AnnSave           (HANNOBJECT      hAnnContainer,
                                      L_UINT          uFormat,
                                      L_BOOL          bSelected,
                                      pSAVEFILEOPTION pSaveOption,
                                      L_INT           nIndex,
                                      L_UINT32       *pnPrivateCreatorTag
                                      );

   L_UINT16        AnnLoad           (pHANNOBJECT     phAnnContainer,
                                      L_INT           nIndex,
                                      pLOADFILEOPTION pLoadOptions
                                     );


   L_UINT16        AnnCount         (L_INT *pFileIndices, L_UINT32 *pnPrivateCreatorTag);

   L_UINT16        AnnDelete        (L_INT nIndex, L_INT nPage); //nIndex: Pass -1 to delete the LEAD Private tag and all files
                                                                 //nPage:   Pass -1 to delete the entire file
                                                                 //         Pass >0 to delete the page


   //---------------------------------------------------------------------------
   // Private Functions (Internal use only)
   //---------------------------------------------------------------------------
   L_BOOL          IsBadPixelData(L_UINT32 * pBadCount,L_UINT32 * pGoodCount);
   L_UINT16        LoadDS            (LDicomFile *pFile, L_UINT16 nFlags, L_BOOL bVerify);
   L_UINT16        SaveDS            (LDicomFile *pFile, L_UINT16 nFlags);
   L_UINT32        FindGetValue      (pDICOMELEMENT pElement, L_UINT32 nTag, L_VOID *pValue, L_UINT32 nIndex, L_UINT32 nCount, L_INT16 nType);
   pDICOMELEMENT   FindSetValue      (pDICOMELEMENT Element, L_UINT32 nTag, L_VOID *pValue, L_UINT32 nCount, L_INT16 nType);
   friend L_BOOL EXT_FUNCTION L_DicomInsertUncompressedFrame(LDicomDS *pDS , pDICOMELEMENT pPixelDataElement, L_VOID *pFrameBuffer, L_UINT32 nLength,L_UINT32 nFrameIndex);
   static HINSTANCE    m_hInstance;

private:
   LDicomTree              m_Tree;
   L_UINT16                m_nFlags;
   L_VOID *                m_pPrivateData;
   L_CHAR                  m_szClass[UID_MAX_SIZE+1];
   L_CHAR                  m_pPreamble[DS_PREAMBLE_LENGTH];
   LDicomFile              *m_pInput;
   LDicomFile              m_MyInput;
   LDicomFile              m_MyScratch;
   L_BOOL                  m_bConformance;
   DICOMMODULE             m_Module;
   CONFORMANCECALLBACK     m_pfnDebug;
   L_VOID                  *m_pDebug;
   HINSTANCE               m_hCMP;
   FLTLOADBUFFER           fltLoadBuffer;
   FLTSAVEBUFFER           fltSaveBuffer;
   FLTJ2KDECOMPRESSFRAME   m_fltJ2KDecompressFrame;
   HINSTANCE               m_hANN;
   pL_ANNLOADMEMORY        pfnAnnLoadMemory;
   pL_ANNSAVEMEMORY        pfnAnnSaveMemory;
   pL_ANNDELETEPAGEMEMORY  pfnAnnDeletePageMemory;


   L_VOID        ResetDS                (L_BOOL bClose);
   L_UINT16      CopyTreeDS             (pDICOMELEMENT pDstParent, LDicomDS *pSrcDS, pDICOMELEMENT pSrcParent);
   
   L_UINT16      GetDefaultVR           (pDICOMELEMENT pElement, L_UINT32 nTag, L_BOOL bParent);
   L_UINT16      GetSizeVR              (L_UINT16 nVR);
   L_BOOL        VerifyVR               (pDICOMELEMENT pElement, L_UINT16 nType);
   L_BOOL        GetTS                  (L_UINT16 *pnFlags, L_INT32 *pnCompression, L_CHAR *pszValue);
   L_BOOL        SetTS                  (L_UINT16 nFlags, L_INT32 nCompression);
   L_BOOL        GetClass               (L_UINT32 *pnClass, L_CHAR *pszUID);
   L_BOOL        SetClass               (L_UINT32 nClass);

   L_BOOL        VerifyTypeValue        (pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 *pnCount, L_UINT16 nType);
   L_BOOL        GetTypeValue           (pDICOMELEMENT pElement);
   L_BOOL        SetTypeValue           (pDICOMELEMENT pElement, L_CHAR *pValue, L_UINT32 nCount, L_UINT32 uFlags=0);

   L_BOOL        GetFileBinaryValue     (pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nOffset, L_UINT32 nLength);
   L_BOOL        SetFileBinaryValue     (pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nOffset, L_UINT32 nLength);
   L_BOOL        InsertFileBinaryValue  (pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nOffset, L_UINT32 nLength);
   L_BOOL        DeleteFileBinaryValue  (pDICOMELEMENT pElement, L_UINT32 nOffset, L_UINT32 nLength);
   L_VOID        ConvertFileBinaryValue (L_VOID *pBuffer, L_UINT32 nLength, L_UINT16 nVR, L_BOOL bLittleEndian);
   L_UINT32      GetFileBinaryIndex     (pDICOMELEMENT pElement, L_UINT32 *nOffset);
   L_BOOL        CopyFileBinaryValue    (pDICOMELEMENT pElement, L_UINT32 nOffset1, L_UINT32 nLength, L_UINT16 nVR, L_BOOL bLittleEndian1, LDicomFile *pFile2, L_UINT32 nOffset2, L_BOOL bLittleEndian2);


   L_VOID        DelSpaces              (L_CHAR *pszText, L_UINT32 nLength);
   L_VOID        DelSpaces              (L_CHAR *pszText);

   L_UINT32      GetLengthSequence      (pDICOMELEMENT pElement, L_UINT16 nFlags);
   L_UINT32      GetLengthGroup         (pDICOMELEMENT pElement, L_UINT16 nFlags);
   L_UINT32      GetLengthElement       (L_UINT32 nTag, L_UINT16 nVR, L_UINT32 nLength, L_BOOL bLittleEndian, L_BOOL bExplicitVR);
   L_UINT32      GetOffsetElement       (pDICOMELEMENT pElement, L_UINT16 nFlags);

   L_UINT16      ReadSequence           (LDicomFile *pInput, pDICOMELEMENT hParent, L_UINT16 nFlags, L_UINT32 *pnLength);
   L_UINT16      WriteSequence          (LDicomFile *pOutput, pDICOMELEMENT pElement, L_UINT16 nFlags);

   L_UINT16      ReadElement            (LDicomFile *pInput, L_UINT32 *pnTag, L_UINT16 *pnVR, L_UINT32 *pnLength, L_BOOL bLittleEndian, L_BOOL bExplicitVR);
   L_UINT16      WriteElement           (LDicomFile *pOutput, L_UINT32 nTag, L_UINT16 nVR, L_UINT32 nLength, L_BOOL bLittleEndian, L_BOOL bExplicitVR);

   L_BOOL        Read                   (LDicomFile *pInput, L_VOID *pBuffer, L_UINT32 nLength, L_UINT16 nVR, L_BOOL bLittleEndian);
   L_BOOL        Write                  (LDicomFile *pOutput, L_VOID *pBuffer, L_UINT32 nLength, L_UINT16 nVR, L_BOOL bLittleEndian);

   L_BOOL        InsertModule           (pDICOMELEMENT pParent, L_UINT32 nModule, L_UINT32 nIndex, L_BOOL bOptional);
   L_VOID        InsertModule           (pDICOMELEMENT pParentElement, pDICOMIOD pParentIOD, L_BOOL bOptional);
   pDICOMIOD     VerifyModule           (pDICOMELEMENT pParent, L_UINT32 nModule);
   L_UINT32      GetCountElementIOD     (pDICOMIOD pIOD, L_BOOL bOptional);

   pDICOMELEMENT GetItemKey             (pDICOMELEMENT pElement);
   pDICOMELEMENT FindAttachKey          (pDICOMELEMENT pElement, L_UINT32 nTag);
   L_VOID        RefreshKeys            ();
   L_UINT32      GetAvailableKey        ();
   L_VOID        InsertModuleKey        (pDICOMELEMENT pParentElement, pDICOMIOD pParentIOD, L_BOOL bOptional);

   L_UINT16      GetInfoImage           (pDICOMELEMENT pElement, pIMAGEINFO pInfo, L_UINT32 nIndex, L_BOOL bPalette);
   L_UINT16      SetInfoImage           (pDICOMELEMENT pElement, pIMAGEINFO pInfo, pBITMAPHANDLE pBitmap, L_INT32 nPhotometric, L_BOOL bSave);
   L_VOID        FreeInfoImage          (pIMAGEINFO pInfo);
   L_UINT16      DecodeSegmentedPaletteColorLUTData(pIMAGEINFO pInfo);
   L_UINT16      DecodeSegmentedPaletteColorLUTData(L_UINT16 *pPaletteBuffer,L_UINT32  uNumEntries,L_UINT32  uSegmentedDataSize);   

   L_UINT16      LoadImage              (pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nBitsPerPixel, L_INT32 nOrder, FILEREADCALLBACK pfnCallback, L_VOID *pUserData);
   L_UINT16      SaveImage              (pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor, FILESAVECALLBACK pfnCallback, L_VOID *pUserData);
   L_UINT16      DeleteImage            (pDICOMELEMENT pElement, L_UINT32 nIndex);
   L_UINT16      RefreshImage           (pDICOMELEMENT pElement);

   L_UINT16      DecodeNONE             (pIMAGEINFO pInfo, L_UCHAR *pImage);
   L_UINT16      DecodeRLE              (pIMAGEINFO pInfo, L_UCHAR *pImage);
   L_UINT16      DecodeJPEG             (pIMAGEINFO pInfo, L_UCHAR *pImage);
   L_UINT16      DecodeJ2K              (pIMAGEINFO pInfo, L_UCHAR *pImage,L_UINT32 uImageBuffSize);
   L_UINT16      DecodeJustLibJ2K       (pIMAGEINFO pInfo, L_UCHAR *pImage,L_UINT32 uImageBuffSize);
   L_UINT16      EncodeNONE             (HANDLE *hImage, pBITMAPHANDLE pBitmap, L_UINT32 *pnLength);
   L_UINT16      EncodeRLE              (HANDLE *hImage, pBITMAPHANDLE pBitmap, L_UINT32 *pnLength);
   L_UINT16      EncodeJPEG             (HANDLE *hImage, pBITMAPHANDLE pBitmap, L_INT32 nQFactor, L_UINT32 *pnLength);
   L_UINT16      EncodeJ2K              (HANDLE *hImage, pBITMAPHANDLE pBitmap, L_INT32 nQFactor, L_UINT32 *pnLength,L_BOOL bLossless);

   L_VOID        ConvertYUVtoRGB        (L_UCHAR *pImage, L_UINT32 nPlaneSize, L_BOOL bPlanar);
   L_VOID        Convert12to16          (L_UCHAR *pImage, L_INT nWidth, L_INT nHeight);
   L_UINT16      GenerateGrayLUT        (pBITMAPHANDLE pBitmap, L_UINT32 nBitsStored, L_UINT32 nHighBit, L_UINT32 nMinVal, L_UINT32 nMaxVal);
   HPALETTE      CreateColorPalette     (L_RGBQUAD *pPalette, L_UINT32 nColors);
   HPALETTE      CreateGrayPalette      (L_UINT32 nBitsPerPixel);

   L_BOOL        CreatePrivateCreatorElement(pDICOMELEMENT pElement, L_UINT32 uTag);
   L_BOOL        IsAnnPrivateCreatorElement(pDICOMELEMENT pElement);
   pDICOMELEMENT FindAnnPrivateCreatorElement(L_CHAR *pszPrivateString);
   L_INT         GetXRangeValue(pDICOMELEMENT pElement, L_UINT32 nIndex, L_VOID * pValue, L_UINT16 nType, L_UINT32 nCount);
   L_UINT16      CompressPixelData(L_INT32 nCompression,L_INT32 nQFactor,L_BOOL bKeepPixelDataIntact);   
   L_UINT16      UncompressPixelDataElement(L_BOOL bKeepPixelDataIntact);
   L_UINT16      ChangeTransferSyntax(DICOM_TRANSFER_SYNTAXES NewTransferSyntax,L_INT32 nQFactor,L_BOOL bKeepPixelDataIntact,L_UINT32 uFlags);
   L_UINT16      FixBadElements();
   L_UINT16      ValidateJ2KOptions ( const pFILEJ2KOPTIONS pOptions );
public:
   // (LEAD's Internal use only)
   L_UINT16      GetFrameBinaryData(pDICOMELEMENT pPixelDataElement,L_INT nFrameIndex,L_UCHAR *pFrameDataBuffer,L_UINT *puFrameDataSize);
private:
};

#endif

#ifdef __cplusplus
extern "C"
{
#endif

//---------------------------------------------------------------------------
// Initializing Functions
//---------------------------------------------------------------------------
HDICOMDS        EXT_FUNCTION L_DicomCreateDS          (L_TCHAR *pszPath);
L_VOID          EXT_FUNCTION L_DicomFreeDS            (HDICOMDS hDS);

L_VOID          EXT_FUNCTION L_DicomInitDS            (HDICOMDS hDS, L_UINT32 nClass, L_UINT16 nFlags);
L_VOID          EXT_FUNCTION L_DicomGetInfoDS         (HDICOMDS hDS, L_UINT32 *pnClass, L_UINT16 *pnFlags);

L_VOID          EXT_FUNCTION L_DicomInitCS            (HDICOMDS hDS, L_UINT16 nCommand, L_BOOL bRequest);
L_VOID          EXT_FUNCTION L_DicomGetInfoCS         (HDICOMDS hDS, L_UINT16 *pnCommand, L_BOOL *pbRequest);

//---------------------------------------------------------------------------
// Input and Output Functions
//---------------------------------------------------------------------------
L_UINT16        EXT_FUNCTION L_DicomLoadDS            (HDICOMDS hDS, L_TCHAR *pszName, L_UINT16 nFlags);
L_UINT16        EXT_FUNCTION L_DicomSaveDS            (HDICOMDS hDS, L_TCHAR *pszName, L_UINT16 nFlags);
L_UINT16        EXT_FUNCTION L_DicomCopyDS            (HDICOMDS hDstDS, pDICOMELEMENT pDstParent, HDICOMDS hSrcDS, pDICOMELEMENT pSrcParent);

//---------------------------------------------------------------------------
// Insertion Functions
//---------------------------------------------------------------------------
pDICOMELEMENT   EXT_FUNCTION L_DicomInsertElement     (HDICOMDS hDS, pDICOMELEMENT pNeighbor, L_BOOL bChild, L_UINT32 nTag, L_UINT16 nVR, L_BOOL bSequence, L_UINT32 nIndex);
pDICOMMODULE    EXT_FUNCTION L_DicomInsertModule      (HDICOMDS hDS, L_UINT32 nModule, L_BOOL bOptional);
pDICOMELEMENT   EXT_FUNCTION L_DicomInsertKey         (HDICOMDS hDS, pDICOMELEMENT pParent, L_CHAR *pszKey, L_BOOL bOptional);

//---------------------------------------------------------------------------
// Deletion Functions
//---------------------------------------------------------------------------
pDICOMELEMENT   EXT_FUNCTION L_DicomDeleteElement     (HDICOMDS hDS, pDICOMELEMENT pElement);
L_VOID          EXT_FUNCTION L_DicomDeleteModule      (HDICOMDS hDS, L_UINT32 nModule);
L_VOID          EXT_FUNCTION L_DicomDeleteKey         (HDICOMDS hDS, pDICOMELEMENT pElement);
L_VOID          EXT_FUNCTION L_DicomResetDS           (HDICOMDS hDS);

//---------------------------------------------------------------------------
// Iteration Functions
//---------------------------------------------------------------------------
pDICOMELEMENT   EXT_FUNCTION L_DicomGetRootElement    (HDICOMDS hDS, pDICOMELEMENT pElement);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetParentElement  (HDICOMDS hDS, pDICOMELEMENT pElement);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetChildElement   (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bVolatile);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetFirstElement   (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetLastElement    (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetPrevElement    (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetNextElement    (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree, L_BOOL bVolatile);
L_UINT32        EXT_FUNCTION L_DicomGetLevelElement   (HDICOMDS hDS, pDICOMELEMENT pElement);
L_UINT32        EXT_FUNCTION L_DicomGetCountModule    (HDICOMDS hDS);
L_BOOL          EXT_FUNCTION L_DicomExistsElement     (HDICOMDS hDS, pDICOMELEMENT pElement);
L_BOOL          EXT_FUNCTION L_DicomIsVolatileElement (HDICOMDS hDS, pDICOMELEMENT pElement);
L_BOOL          EXT_FUNCTION L_DicomConformanceDS     (HDICOMDS hDS, CONFORMANCECALLBACK pfnCallback, L_VOID *pUserData);
L_VOID          EXT_FUNCTION L_DicomSetDebugDS        (HDICOMDS hDS, CONFORMANCECALLBACK pfnCallback, L_VOID *pUserData);

pDICOMELEMENT   EXT_FUNCTION L_DicomGetRootKey        (HDICOMDS hDS, pDICOMELEMENT pElement);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetParentKey      (HDICOMDS hDS, pDICOMELEMENT pElement);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetChildKey       (HDICOMDS hDS, pDICOMELEMENT pElement);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetFirstKey       (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetLastKey        (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetPrevKey        (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomGetNextKey        (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
L_CHAR         *EXT_FUNCTION L_DicomGetValueKey       (HDICOMDS hDS, pDICOMELEMENT pElement);

//---------------------------------------------------------------------------
// Searching Functions
//---------------------------------------------------------------------------
pDICOMELEMENT   EXT_FUNCTION L_DicomFindFirstElement  (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nTag, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindLastElement   (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nTag, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindPrevElement   (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindNextElement   (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMMODULE    EXT_FUNCTION L_DicomFindModule        (HDICOMDS hDS, L_UINT32 nModule);
pDICOMMODULE    EXT_FUNCTION L_DicomFindIndexModule   (HDICOMDS hDS, L_UINT32 nIndex);

pDICOMELEMENT   EXT_FUNCTION L_DicomFindFirstKey      (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pszKey, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindLastKey       (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pszKey, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindPrevKey       (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
pDICOMELEMENT   EXT_FUNCTION L_DicomFindNextKey       (HDICOMDS hDS, pDICOMELEMENT pElement, L_BOOL bTree);
L_BOOL          EXT_FUNCTION L_DicomIsBadPixelData    (HDICOMDS hDS,L_UINT32 * pBadCount,L_UINT32 * pGoodCount);

//---------------------------------------------------------------------------
// Retrieval Functions
//---------------------------------------------------------------------------
L_VOID          EXT_FUNCTION L_DicomGetPreamble       (HDICOMDS hDS, L_CHAR *pPreamble, L_UINT16 nLength);
L_UINT32        EXT_FUNCTION L_DicomGetCountValue     (HDICOMDS hDS, pDICOMELEMENT pElement);
L_VOID          EXT_FUNCTION L_DicomFreeValue         (HDICOMDS hDS, pDICOMELEMENT pElement);
L_BOOL          EXT_FUNCTION L_DicomGetBinaryValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nLength);
L_CHAR         *EXT_FUNCTION L_DicomGetCharValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_INT16        *EXT_FUNCTION L_DicomGetShortValue     (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_INT32        *EXT_FUNCTION L_DicomGetLongValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_FLOAT        *EXT_FUNCTION L_DicomGetFloatValue     (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_DOUBLE       *EXT_FUNCTION L_DicomGetDoubleValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_CHAR         *EXT_FUNCTION L_DicomGetStringValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
pVALUEAGE       EXT_FUNCTION L_DicomGetAgeValue       (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
pVALUEDATE      EXT_FUNCTION L_DicomGetDateValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
pVALUETIME      EXT_FUNCTION L_DicomGetTimeValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
pVALUEDATETIME  EXT_FUNCTION L_DicomGetDateTimeValue  (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_UINT32        EXT_FUNCTION L_DicomGetConvertValue   (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pszText);
L_UINT32        EXT_FUNCTION L_DicomGetCountImage     (HDICOMDS hDS, pDICOMELEMENT pElement);
L_UINT16        EXT_FUNCTION L_DicomGetInfoImage      (HDICOMDS hDS, pDICOMELEMENT pElement, pDICOMIMAGE pInfo, L_UINT32 nIndex);
L_UINT16        EXT_FUNCTION L_DicomGetImage          (HDICOMDS hDS, pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nBitsPerPixel, L_INT32 nOrder, FILEREADCALLBACK pfnCallback, L_VOID *pUserData);
L_UINT16        EXT_FUNCTION L_DicomGetImageList      (HDICOMDS hDS, pDICOMELEMENT pElement, HBITMAPLIST hList, L_UINT32 nIndex, L_UINT32 nCount, L_INT32 nBitsPerPixel, L_INT32 nOrder);
L_BOOL          EXT_FUNCTION L_DicomGetKeepPixelDataIntactFlag(HDICOMDS hDS);
L_UINT16        EXT_FUNCTION L_DicomGetJ2KOptions( HDICOMDS hDS,pFILEJ2KOPTIONS pOptions, L_INT nSize );
L_UINT16        EXT_FUNCTION L_DicomGetDefaultJ2KOptions( HDICOMDS hDS,pFILEJ2KOPTIONS pOptions, L_INT nSize );

//---------------------------------------------------------------------------
// Modification Functions
//---------------------------------------------------------------------------
L_VOID          EXT_FUNCTION L_DicomSetPreamble       (HDICOMDS hDS, L_CHAR *pPreamble, L_UINT16 nLength);
L_BOOL          EXT_FUNCTION L_DicomSetBinaryValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_VOID *pValue, L_UINT32 nLength);
L_BOOL          EXT_FUNCTION L_DicomSetCharValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetShortValue     (HDICOMDS hDS, pDICOMELEMENT pElement, L_INT16 *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetLongValue      (HDICOMDS hDS, pDICOMELEMENT pElement, L_INT32 *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetFloatValue     (HDICOMDS hDS, pDICOMELEMENT pElement, L_FLOAT *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetDoubleValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_DOUBLE *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetStringValue    (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetAgeValue       (HDICOMDS hDS, pDICOMELEMENT pElement, pVALUEAGE pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetDateValue      (HDICOMDS hDS, pDICOMELEMENT pElement, pVALUEDATE pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetTimeValue      (HDICOMDS hDS, pDICOMELEMENT pElement, pVALUETIME pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetDateTimeValue  (HDICOMDS hDS, pDICOMELEMENT pElement, pVALUEDATETIME pValue, L_UINT32 nCount);
L_BOOL          EXT_FUNCTION L_DicomSetConvertValue   (HDICOMDS hDS, pDICOMELEMENT pElement, L_CHAR *pszText, L_UINT32 nCount);
L_UINT16        EXT_FUNCTION L_DicomInsertImage       (HDICOMDS hDS, pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_UINT32 nIndex, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor, FILESAVECALLBACK pfnCallback, L_VOID *pUserData);
L_UINT16        EXT_FUNCTION L_DicomInsertImageList   (HDICOMDS hDS, pDICOMELEMENT pElement, HBITMAPLIST hList, L_UINT32 nIndex, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor);
L_UINT16        EXT_FUNCTION L_DicomSetImage          (HDICOMDS hDS, pDICOMELEMENT pElement, pBITMAPHANDLE pBitmap, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor, FILESAVECALLBACK pfnCallback, L_VOID *pUserData);
L_UINT16        EXT_FUNCTION L_DicomSetImageList      (HDICOMDS hDS, pDICOMELEMENT pElement, HBITMAPLIST hList, L_INT32 nCompression, L_INT32 nPhotometric, L_INT32 nBitsPerPixel, L_INT32 nQFactor);
L_UINT16        EXT_FUNCTION L_DicomDeleteImage       (HDICOMDS hDS, pDICOMELEMENT pElement, L_UINT32 nIndex, L_UINT32 nCount);
L_UINT16        EXT_FUNCTION L_DicomChangeTransferSyntax(HDICOMDS hDS, L_CHAR *pszUID,L_INT32 nQFactor/*For lossy*/,L_UINT32 uFlags);
L_VOID          EXT_FUNCTION L_DicomSetKeepPixelDataIntactFlag(HDICOMDS hDS, L_BOOL bSet);
L_UINT16        EXT_FUNCTION L_DicomSetJ2KOptions( HDICOMDS hDS,const pFILEJ2KOPTIONS pOptions);


//---------------------------------------------------------------------------
// Annotation Functions
//---------------------------------------------------------------------------

L_UINT16        EXT_FUNCTION L_DicomAnnSave           (HDICOMDS hDS,
                                                       HANNOBJECT      hAnnContainer,
                                                       L_UINT          uFormat,
                                                       L_BOOL          bSelected,
                                                       pSAVEFILEOPTION pSaveOption,
                                                       L_INT           nIndex,
                                                       L_UINT32       *pnPrivateCreatorTag
                                                       );

L_UINT16        EXT_FUNCTION L_DicomAnnLoad           (HDICOMDS hDS,
                                                       pHANNOBJECT     phAnnContainer,
                                                       L_INT           nIndex,
                                                       pLOADFILEOPTION pLoadOptions
                                                       );


L_UINT16        EXT_FUNCTION L_DicomAnnCount         (HDICOMDS hDS, L_INT *pFileIndices, L_UINT32 *pnPrivateCreatorTag);

L_UINT16        EXT_FUNCTION L_DicomAnnDelete        (HDICOMDS hDS, L_INT nIndex, L_INT nPage ); //nIndex: Pass -1 to delete the LEAD Private tag and all files
                                                                                                 //nPage:   Pass -1 to delete the entire file
                                                                                                 //         Pass >0 to delete the page

#ifdef __cplusplus
};
#endif

//============= CLASS ==========================================================
// Directory options structure
typedef struct tagDICOMDIROPTIONS
{
   L_INT    nSize;
   L_BOOL   bIncludeSubfolders;
   L_UINT32	uFlags;

} DICOMDIROPTIONS, * pDICOMDIROPTIONS;

// Flags of the Directory options structure
#define DICOMDIR_REJECT_INVALID_FILEID          0x01
#define DICOMDIR_INSERT_ICON_IMAGE_SEQUENCE     0x02

// A status code
#define DICOMDIR_INSERTDICOMFILE_PREADD   300


#ifdef __cplusplus

class DICOM_EXPORT LDicomDir : public LDicomDS
{
public:

   //---------------------------------------------------------------------------
   // Initializing Functions
   //---------------------------------------------------------------------------
   LDicomDir(L_TCHAR* pszDICOMDIRDstFolder = NULL, L_TCHAR* pszPath = NULL);
   virtual ~LDicomDir();

   //---------------------------------------------------------------------------
   // Input and Output Functions
   //---------------------------------------------------------------------------
   L_UINT16 LoadDS(L_TCHAR* pszName, L_UINT16 nFlags);
   L_UINT16 SaveDicomDir(L_UINT16 uFlags = 0);   
   //---------------------------------------------------------------------------
   // Deletion Functions
   //---------------------------------------------------------------------------
   L_UINT16 ResetDicomDir(const L_TCHAR* pszDICOMDIRDstFolder);

   //---------------------------------------------------------------------------
   // Insertion Functions
   //---------------------------------------------------------------------------
   L_UINT16 InsertDicomFile(L_TCHAR* pszFileName);
   L_UINT16 InsertDicomDS(LDicomDS& DataSet, L_TCHAR* pszFileName);

   //---------------------------------------------------------------------------
   // Modification Functions
   //---------------------------------------------------------------------------      
   L_UINT16 SetFileSetID(L_TCHAR* pszFileSetID);
   L_UINT16 SetDescriptorFile(L_TCHAR* pszFileName, L_TCHAR* pszCharSet);
   L_UINT16 SetOptions(const pDICOMDIROPTIONS pOptions);

   //---------------------------------------------------------------------------
   // Retrieval Functions
   //---------------------------------------------------------------------------
   L_UINT16 GetOptions(pDICOMDIROPTIONS pOptions, L_INT nSize) const;

   //---------------------------------------------------------------------------
   // Overridables
   //---------------------------------------------------------------------------   
   virtual L_UINT16 OnInsertDicomFile(const L_TCHAR* pszFileName,
                                      LDicomDS* pDataSet,
                                      L_UINT16 uStatus);

   //---------------------------------------------------------------------------
   // Private
   //---------------------------------------------------------------------------
private:
   L_TCHAR*        m_pszDICOMDIRDstFolder;
   DICOMDIROPTIONS m_Options;
   L_BOOL          m_bEnableSearchFolder;

   pDICOMELEMENT FindDirectoryRecord(pDICOMELEMENT pReferencingDR, L_INT nDRType,
                                     const L_CHAR* pszIdentifier);
   L_VOID        SetSelectionKey(pDICOMELEMENT pDR, LDicomDS& DataSet, L_UINT32 uTag,
                                 L_UINT16 uVR, L_BOOL bEnableDelete = FALSE);
   L_VOID        DeleteDRElement(pDICOMELEMENT pDR, L_UINT32 uTag);
   L_UINT16      GetRelativePath(const L_TCHAR* pszFileName, L_TCHAR** ppszFName) const;
   L_BOOL        CheckFileID(const L_TCHAR* pszFileID) const;
   L_VOID        ResetOptions();
   L_UINT16      SearchFolder(const L_TCHAR* pszFolderName, L_BOOL bIncludeSubfolders);
   L_UINT16      InsertIconImageSequence(pDICOMELEMENT pImageKey, LDicomDS& SourceDataSet);

};

#endif
//============= CLASS ==========================================================

#define PDU_UNKNOWN                     0x00

#define PDU_ASSOCIATE_REQUEST           0x01
#define PDU_ASSOCIATE_ACCEPT            0x02
#define PDU_ASSOCIATE_REJECT            0x03
#define PDU_DATA_TRANSFER               0x04
#define PDU_RELEASE_REQUEST             0x05
#define PDU_RELEASE_RESPONSE            0x06
#define PDU_ABORT                       0x07

#define PDU_ROLE_NON_SUPPORT               0
#define PDU_ROLE_SUPPORT                   1

#define PDU_MAX_UID_SIZE                  64
#define PDU_MAX_TITLE_SIZE                64
#define PDU_MAX_VERSION_SIZE              16
#define PDU_MIN_MAXIMUM_LENGTH             8

// Associate Accept
#define PDU_ACCEPT_RESULT_SUCCESS           0  // Acceptance
#define PDU_ACCEPT_RESULT_USER_REJECT       1  // User rejection
#define PDU_ACCEPT_RESULT_PROVIDER_REJECT   2  // No reason (provider rejection)
#define PDU_ACCEPT_RESULT_ABSTRACT_SYNTAX   3  // Abstract syntax not supported (provider rejection)
#define PDU_ACCEPT_RESULT_TRANSFER_SYNTAX   4  // Transfer syntaxes not supported (provider rejection)

// Associate Reject
#define PDU_REJECT_RESULT_PERMANENT         1  // Rejected permanent
#define PDU_REJECT_RESULT_TRANSIENT         2  // Rejected transient

#define PDU_REJECT_SOURCE_USER              1  // DICOM UL service-user
#define PDU_REJECT_SOURCE_PROVIDER1         2  // DICOM UL service-provider (ASCE related function)
#define PDU_REJECT_SOURCE_PROVIDER2         3  // DICOM UL service-provider (Presentation related function)

#define PDU_REJECT_REASON_UNKNOWN           1  // No reason given (User - Provider1)
#define PDU_REJECT_REASON_APPLICATION       2  // Application context name not supported (User)
#define PDU_REJECT_REASON_CALLING           3  // Calling AE Title not recognized (User)
#define PDU_REJECT_REASON_CALLED            7  // Called AE Title not recognized (User)

#define PDU_REJECT_REASON_VERSION           2  // Protocol version not supported (Provider1)

#define PDU_REJECT_REASON_CONGESTION        1  // Temporary congestion (Provider2)
#define PDU_REJECT_REASON_LIMIT             2  // Local limit exceeded (Provider2)

// Abort
#define PDU_ABORT_SOURCE_USER               0  // Service user
#define PDU_ABORT_SOURCE_PROVIDER           2  // Service provider

#define PDU_ABORT_REASON_UNKNOWN            0  // Reason no specified (Provider)
#define PDU_ABORT_REASON_UNRECOGNIZED       1  // Unrecognized PDU (Provider)
#define PDU_ABORT_REASON_UNEXPECTED         2  // Unexpected PDU (Provider)
#define PDU_ABORT_REASON_UNRECOGNIZED_PARAM 4  // Unrecognized PDU parameter (Provider)
#define PDU_ABORT_REASON_UNEXPECTED_PARAM   5  // Unexpected PDU parameter (Provider)
#define PDU_ABORT_REASON_INVALID_PARAM      6  // Invalid PDU parameter value (Provider)

//============= CLASS ==========================================================
#if !defined(_WIN32_WCE)

#ifdef __cplusplus

class DICOM_EXPORT LDicomAssociate
{
public:
   LDicomAssociate(L_BOOL bRequest);
   ~LDicomAssociate();

   L_VOID    Reset                  (L_BOOL bRequest);
   L_VOID    Default                ();

   L_BOOL    IsRequest              ();
   L_VOID    SetRequest             (L_BOOL bRequest);

   L_UINT16  GetVersion             ();
   L_INT     SetVersion             (L_UINT16 nVersion);

   L_CHAR   *GetCalled              ();
   L_INT     SetCalled              (L_CHAR *pszName);

   L_CHAR   *GetCalling             ();
   L_INT     SetCalling             (L_CHAR *pszName);

   L_CHAR   *GetApplication         ();
   L_INT     SetApplication         (L_CHAR *pszUID);

   L_INT     GetPresentationCount   ();
   L_UCHAR   GetPresentation        (L_INT nIndex);
   L_INT     SetPresentation        (L_INT nIndex, L_UCHAR nID);
   L_INT     AddPresentation        (L_UCHAR nID, L_UCHAR nResult, L_CHAR *pszAbstract);
   L_VOID    DelPresentation        (L_UCHAR nID);

   L_UCHAR   GetResult              (L_UCHAR nID);
   L_INT     SetResult              (L_UCHAR nID, L_UCHAR nResult);

   L_CHAR   *GetAbstract            (L_UCHAR nID);
   L_INT     SetAbstract            (L_UCHAR nID, L_CHAR *pszUID);
   L_UCHAR   FindAbstract           (L_CHAR *pszUID);

   L_INT     GetTransferCount       (L_UCHAR nID);
   L_CHAR   *GetTransfer            (L_UCHAR nID, L_INT nIndex);
   L_INT     SetTransfer            (L_UCHAR nID, L_INT nIndex, L_CHAR *pszUID);
   L_INT     AddTransfer            (L_UCHAR nID, L_CHAR *pszUID);
   L_VOID    DelTransfer            (L_UCHAR nID, L_INT nIndex);

   L_BOOL    IsRoleSelect           (L_UCHAR nID);
   L_UCHAR   GetUserRole            (L_UCHAR nID);
   L_UCHAR   GetProviderRole        (L_UCHAR nID);
   L_INT     SetRoleSelect          (L_UCHAR nID, L_BOOL bEnabled, L_UCHAR nUser, L_UCHAR nProvider);

   L_UINT32  GetLengthExtended      (L_UCHAR nID);
   L_UCHAR  *GetExtended            (L_UCHAR nID);
   L_INT     SetExtended            (L_UCHAR nID, L_UCHAR *pData, L_UINT32 nLength);

   L_BOOL    IsMaxLength            ();
   L_UINT32  GetMaxLength           ();
   L_INT     SetMaxLength           (L_BOOL bEnabled, L_UINT32 nLength);

   L_BOOL    IsImplementClass       ();
   L_CHAR   *GetImplementClass      ();
   L_INT     SetImplementClass      (L_BOOL bEnabled, L_CHAR *pszUID);

   L_BOOL    IsAsyncOperations      ();
   L_UINT16  GetInvokedOperations   ();
   L_UINT16  GetPerformedOperations ();
   L_INT     SetAsyncOperations     (L_BOOL bEnabled, L_UINT16 nInvoked, L_UINT16 nPerformed);

   L_BOOL    IsImplementVersion     ();
   L_CHAR   *GetImplementVersion    ();
   L_INT     SetImplementVersion    (L_BOOL bEnabled, L_CHAR *pszVersion);

   L_INT     GetUserInfoCount       ();
   L_UCHAR   GetTypeUserInfo        (L_INT nIndex);
   L_UINT16  GetLengthUserInfo      (L_INT nIndex);
   L_CHAR   *GetDataUserInfo        (L_INT nIndex);
   L_INT     SetUserInfo            (L_INT nIndex, L_UCHAR nType, L_CHAR *pData, L_UINT16 nLength);
   L_INT     AddUserInfo            (L_UCHAR nType, L_CHAR *pData, L_UINT16 nLength);
   L_VOID    DelUserInfo            (L_INT nIndex);
   
private:
   friend class LDicomNet;

   L_BOOL     m_bRequest;
   L_UINT16   m_nVersion;
   L_CHAR     m_szCalled[PDU_MAX_TITLE_SIZE+1];
   L_CHAR     m_szCalling[PDU_MAX_TITLE_SIZE+1];
   L_CHAR     m_szApplication[PDU_MAX_UID_SIZE+1];

   L_BOOL     m_bMaxLength;
   L_UINT32   m_nMaxLength;

   L_BOOL     m_bImplementClass;
   L_CHAR     m_szImplementClass[PDU_MAX_UID_SIZE+1];

   L_BOOL     m_bAsyncOperations;
   L_UINT16   m_nInvokedOperations;
   L_UINT16   m_nPerformedOperations;

   L_BOOL     m_bImplementVersion;
   L_CHAR     m_szImplementVersion[PDU_MAX_VERSION_SIZE+1];

   LDicomTree m_Presentation;
   LDicomTree m_RoleSelect;
   LDicomTree m_UserInfo;

   L_INT     GetBinary        (L_CHAR *pBuffer, L_UINT32 *pnLength);
   L_INT     SetBinary        (L_CHAR *pBuffer, L_UINT32 *pnLength);
   L_VOID   *FindPresentation (L_UCHAR nID);
   L_VOID    DelSpaces        (L_CHAR *pszText, L_UINT32 nLength);

};

#endif

typedef L_VOID *HDICOMPDU;

#ifdef __cplusplus
extern "C"
{
#endif

HDICOMPDU EXT_FUNCTION L_DicomCreateAssociate        (L_BOOL bRequest);
L_VOID    EXT_FUNCTION L_DicomFreeAssociate          (HDICOMPDU hPDU);

L_VOID    EXT_FUNCTION L_DicomResetAssociate         (HDICOMPDU hPDU, L_BOOL bRequest);
L_VOID    EXT_FUNCTION L_DicomDefaultAssociate       (HDICOMPDU hPDU);

L_BOOL    EXT_FUNCTION L_DicomIsRequest              (HDICOMPDU hPDU);
L_VOID    EXT_FUNCTION L_DicomSetRequest             (HDICOMPDU hPDU, L_BOOL bRequest);

L_UINT16  EXT_FUNCTION L_DicomGetVersion             (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetVersion             (HDICOMPDU hPDU, L_UINT16 nVersion);

L_CHAR   *EXT_FUNCTION L_DicomGetCalled              (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetCalled              (HDICOMPDU hPDU, L_CHAR *pszName);

L_CHAR   *EXT_FUNCTION L_DicomGetCalling             (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetCalling             (HDICOMPDU hPDU, L_CHAR *pszName);

L_CHAR   *EXT_FUNCTION L_DicomGetApplication         (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetApplication         (HDICOMPDU hPDU, L_CHAR *pszUID);

L_INT     EXT_FUNCTION L_DicomGetPresentationCount   (HDICOMPDU hPDU);
L_UCHAR   EXT_FUNCTION L_DicomGetPresentation        (HDICOMPDU hPDU, L_INT nIndex);
L_INT     EXT_FUNCTION L_DicomSetPresentation        (HDICOMPDU hPDU, L_INT nIndex, L_UCHAR nID);
L_INT     EXT_FUNCTION L_DicomAddPresentation        (HDICOMPDU hPDU, L_UCHAR nID, L_UCHAR nResult, L_CHAR *pszAbstract);
L_VOID    EXT_FUNCTION L_DicomDelPresentation        (HDICOMPDU hPDU, L_UCHAR nID);

L_UCHAR   EXT_FUNCTION L_DicomGetResult              (HDICOMPDU hPDU, L_UCHAR nID);
L_INT     EXT_FUNCTION L_DicomSetResult              (HDICOMPDU hPDU, L_UCHAR nID, L_UCHAR nResult);

L_CHAR   *EXT_FUNCTION L_DicomGetAbstract            (HDICOMPDU hPDU, L_UCHAR nID);
L_INT     EXT_FUNCTION L_DicomSetAbstract            (HDICOMPDU hPDU, L_UCHAR nID, L_CHAR *pszUID);
L_UCHAR   EXT_FUNCTION L_DicomFindAbstract           (HDICOMPDU hPDU, L_CHAR *pszUID);

L_INT     EXT_FUNCTION L_DicomGetTransferCount       (HDICOMPDU hPDU, L_UCHAR nID);
L_CHAR   *EXT_FUNCTION L_DicomGetTransfer            (HDICOMPDU hPDU, L_UCHAR nID, L_INT nIndex);
L_INT     EXT_FUNCTION L_DicomSetTransfer            (HDICOMPDU hPDU, L_UCHAR nID, L_INT nIndex, L_CHAR *pszUID);
L_INT     EXT_FUNCTION L_DicomAddTransfer            (HDICOMPDU hPDU, L_UCHAR nID, L_CHAR *pszUID);
L_VOID    EXT_FUNCTION L_DicomDelTransfer            (HDICOMPDU hPDU, L_UCHAR nID, L_INT nIndex);

L_BOOL    EXT_FUNCTION L_DicomIsRoleSelect           (HDICOMPDU hPDU, L_UCHAR nID);
L_UCHAR   EXT_FUNCTION L_DicomGetUserRole            (HDICOMPDU hPDU, L_UCHAR nID);
L_UCHAR   EXT_FUNCTION L_DicomGetProviderRole        (HDICOMPDU hPDU, L_UCHAR nID);
L_INT     EXT_FUNCTION L_DicomSetRoleSelect          (HDICOMPDU hPDU, L_UCHAR nID, L_BOOL bEnabled, L_UCHAR nUser, L_UCHAR nProvider);

L_UINT32  EXT_FUNCTION L_DicomGetLengthExtended      (HDICOMPDU hPDU, L_UCHAR nID);
L_UCHAR  *EXT_FUNCTION L_DicomGetExtended            (HDICOMPDU hPDU, L_UCHAR nID);
L_INT     EXT_FUNCTION L_DicomSetExtended            (HDICOMPDU hPDU, L_UCHAR nID, L_UCHAR *pData, L_UINT32 nLength);

L_BOOL    EXT_FUNCTION L_DicomIsMaxLength            (HDICOMPDU hPDU);
L_UINT32  EXT_FUNCTION L_DicomGetMaxLength           (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetMaxLength           (HDICOMPDU hPDU, L_BOOL bEnabled, L_UINT32 nLength);

L_BOOL    EXT_FUNCTION L_DicomIsImplementClass       (HDICOMPDU hPDU);
L_CHAR   *EXT_FUNCTION L_DicomGetImplementClass      (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetImplementClass      (HDICOMPDU hPDU, L_BOOL bEnabled, L_CHAR *pszUID);

L_BOOL    EXT_FUNCTION L_DicomIsAsyncOperations      (HDICOMPDU hPDU);
L_UINT16  EXT_FUNCTION L_DicomGetInvokedOperations   (HDICOMPDU hPDU);
L_UINT16  EXT_FUNCTION L_DicomGetPerformedOperations (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetAsyncOperations     (HDICOMPDU hPDU, L_BOOL bEnabled, L_UINT16 nInvoked, L_UINT16 nPerformed);

L_BOOL    EXT_FUNCTION L_DicomIsImplementVersion     (HDICOMPDU hPDU);
L_CHAR   *EXT_FUNCTION L_DicomGetImplementVersion    (HDICOMPDU hPDU);
L_INT     EXT_FUNCTION L_DicomSetImplementVersion    (HDICOMPDU hPDU, L_BOOL bEnabled, L_CHAR *pszVersion);

L_INT     EXT_FUNCTION L_DicomGetUserInfoCount       (HDICOMPDU hPDU);
L_UCHAR   EXT_FUNCTION L_DicomGetTypeUserInfo        (HDICOMPDU hPDU, L_INT nIndex);
L_UINT16  EXT_FUNCTION L_DicomGetLengthUserInfo      (HDICOMPDU hPDU, L_INT nIndex);
L_CHAR   *EXT_FUNCTION L_DicomGetDataUserInfo        (HDICOMPDU hPDU, L_INT nIndex);
L_INT     EXT_FUNCTION L_DicomSetUserInfo            (HDICOMPDU hPDU, L_INT nIndex, L_UCHAR nType, L_CHAR *pData, L_UINT16 nLength);
L_INT     EXT_FUNCTION L_DicomAddUserInfo            (HDICOMPDU hPDU, L_UCHAR nType, L_CHAR *pData, L_UINT16 nLength);
L_VOID    EXT_FUNCTION L_DicomDelUserInfo            (HDICOMPDU hPDU, L_INT nIndex);

#ifdef __cplusplus
};
#endif
#endif /* _WIN32_WCE */

//============= CLASS ==========================================================
#if !defined(_WIN32_WCE)

#define NET_MAX_ADDRESS_SIZE  16

typedef L_VOID *HDICOMNET;

typedef L_VOID (pEXT_CALLBACK CONNECTCALLBACK)                 (HDICOMNET hNet, L_INT nError, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK ACCEPTCALLBACK)                  (HDICOMNET hNet, L_INT nError, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK CLOSECALLBACK)                   (HDICOMNET hNet, L_INT nError, HDICOMNET hPeer, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECALLBACK)                 (HDICOMNET hNet, L_INT nError, L_UCHAR nType, L_CHAR *pBuffer, L_UINT32 nBytes, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK SENDCALLBACK)                    (HDICOMNET hNet, L_INT nError, L_UCHAR nType, L_UINT32 nBytes, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK SENDEXTCALLBACK)                 (HDICOMNET hNet, pDICOMNETDEBUGINFOONSEND pDicomNetDebugInfoOnsend, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEASSOCIATEREQUESTCALLBACK) (HDICOMNET hNet, HDICOMPDU hPDU, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEASSOCIATEACCEPTCALLBACK)  (HDICOMNET hNet, HDICOMPDU hPDU, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEASSOCIATEREJECTCALLBACK)  (HDICOMNET hNet, L_UCHAR nResult, L_UCHAR nSource, L_UCHAR nReason, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEDATACALLBACK)             (HDICOMNET hNet, L_UCHAR nPresentationID, HDICOMDS hCS, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVERELEASEREQUESTCALLBACK)   (HDICOMNET hNet, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVERELEASERESPONSECALLBACK)  (HDICOMNET hNet, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEABORTCALLBACK)            (HDICOMNET hNet, L_UCHAR nSource, L_UCHAR nReason, L_VOID *pUserData);

typedef L_VOID (pEXT_CALLBACK RECEIVECSTOREREQUESTCALLBACK)    (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nPriority, L_CHAR *pszMoveAE, L_UINT16 nMoveMessageID, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECSTORERESPONSECALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECFINDREQUESTCALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECFINDRESPONSECALLBACK)    (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECGETREQUESTCALLBACK)      (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECGETRESPONSECALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECMOVEREQUESTCALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, L_CHAR *pszMoveAE, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECMOVERESPONSECALLBACK)    (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECCANCELREQUESTCALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECECHOREQUESTCALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVECECHORESPONSECALLBACK)    (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENREPORTREQUESTCALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nEvent, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENREPORTRESPONSECALLBACK)  (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nEvent, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENGETREQUESTCALLBACK)      (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT32 *pnAttribute, L_UINT32 nCount, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENGETRESPONSECALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENSETREQUESTCALLBACK)      (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENSETRESPONSECALLBACK)     (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENACTIONREQUESTCALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nAction, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENACTIONRESPONSECALLBACK)  (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nAction, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENCREATEREQUESTCALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENCREATERESPONSECALLBACK)  (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENDELETEREQUESTCALLBACK)   (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVENDELETERESPONSECALLBACK)  (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_VOID *pUserData);
typedef L_VOID (pEXT_CALLBACK RECEIVEUNKNOWNCALLBACK)          (HDICOMNET hNet, L_UCHAR nPresentationID, HDICOMDS hCS, HDICOMDS hDS, L_VOID *pUserData);

typedef L_UINT32 (pEXT_CALLBACK GETCHALLENGECALLBACK)          (HDICOMNET hNet, L_UINT64 *nChallenge, L_UINT64 nParameter, L_VOID *pUserData);
typedef L_UINT32 (pEXT_CALLBACK INTERNALAUTHENTICATECALLBACK)  (HDICOMNET hNet, L_UINT64 nChallenge, L_UINT64 *nResponse, L_UINT64 nParameter, L_VOID *pUserData);
typedef L_UINT32 (pEXT_CALLBACK EXTERNALAUTHENTICATECALLBACK)  (HDICOMNET hNet, L_UINT64 nChallenge, L_UINT64 nResponse, L_UINT64 nParameter, L_VOID *pUserData);
typedef L_VOID   (pEXT_CALLBACK ONSECURELINKREADY)             (HDICOMNET hNet, L_UINT32 nError, L_VOID *pUserData);
typedef L_VOID   (pEXT_CALLBACK ONNONSECURESENDISCL)           (HDICOMNET hNet, L_INT nError, L_UCHAR nType, L_UINT32 nLength, L_VOID *pUserData);
typedef L_VOID   (pEXT_CALLBACK ONNONSECURERECEIVEDISCL)       (HDICOMNET hNet, L_INT nError, L_CHAR *nType, L_UINT32 nLength, L_VOID *pUserData);
//debug only
typedef L_VOID   (pEXT_CALLBACK RECEIVEDISCLPACKET)            (HDICOMNET hNet, L_INT nError, L_CHAR *pBuffer, L_UINT32 nBytes, L_VOID *pUserData);

typedef struct _DICOMNETCALLBACK
{
   CONNECTCALLBACK                  pfnConnect;
   ACCEPTCALLBACK                   pfnAccept; 
   CLOSECALLBACK                    pfnClose;  
   RECEIVECALLBACK                  pfnReceive;
   SENDCALLBACK                     pfnSend;      
   RECEIVEASSOCIATEREQUESTCALLBACK  pfnReceiveAssociateRequest;
   RECEIVEASSOCIATEACCEPTCALLBACK   pfnReceiveAssociateAccept; 
   RECEIVEASSOCIATEREJECTCALLBACK   pfnReceiveAssociateReject; 
   RECEIVEDATACALLBACK              pfnReceiveData;            
   RECEIVERELEASEREQUESTCALLBACK    pfnReceiveReleaseRequest;  
   RECEIVERELEASERESPONSECALLBACK   pfnReceiveReleaseResponse; 
   RECEIVEABORTCALLBACK             pfnReceiveAbort;           
   RECEIVECSTOREREQUESTCALLBACK     pfnReceiveCStoreRequest;   
   RECEIVECSTORERESPONSECALLBACK    pfnReceiveCStoreResponse;  
   RECEIVECFINDREQUESTCALLBACK      pfnReceiveCFindRequest;    
   RECEIVECFINDRESPONSECALLBACK     pfnReceiveCFindResponse;   
   RECEIVECGETREQUESTCALLBACK       pfnReceiveCGetRequest;     
   RECEIVECGETRESPONSECALLBACK      pfnReceiveCGetResponse;    
   RECEIVECMOVEREQUESTCALLBACK      pfnReceiveCMoveRequest;    
   RECEIVECMOVERESPONSECALLBACK     pfnReceiveCMoveResponse;   
   RECEIVECCANCELREQUESTCALLBACK    pfnReceiveCCancelRequest;  
   RECEIVECECHOREQUESTCALLBACK      pfnReceiveCEchoRequest;    
   RECEIVECECHORESPONSECALLBACK     pfnReceiveCEchoResponse;   
   RECEIVENREPORTREQUESTCALLBACK    pfnReceiveNReportRequest;  
   RECEIVENREPORTRESPONSECALLBACK   pfnReceiveNReportResponse; 
   RECEIVENGETREQUESTCALLBACK       pfnReceiveNGetRequest;     
   RECEIVENGETRESPONSECALLBACK      pfnReceiveNGetResponse;    
   RECEIVENSETREQUESTCALLBACK       pfnReceiveNSetRequest;     
   RECEIVENSETRESPONSECALLBACK      pfnReceiveNSetResponse;    
   RECEIVENACTIONREQUESTCALLBACK    pfnReceiveNActionRequest;  
   RECEIVENACTIONRESPONSECALLBACK   pfnReceiveNActionResponse; 
   RECEIVENCREATEREQUESTCALLBACK    pfnReceiveNCreateRequest;  
   RECEIVENCREATERESPONSECALLBACK   pfnReceiveNCreateResponse; 
   RECEIVENDELETEREQUESTCALLBACK    pfnReceiveNDeleteRequest;  
   RECEIVENDELETERESPONSECALLBACK   pfnReceiveNDeleteResponse; 
   RECEIVEUNKNOWNCALLBACK           pfnReceiveUnknown; 
   L_VOID                          *pUserData;
// added for ISCL compliance
   GETCHALLENGECALLBACK             pfnGetChallenge;
   INTERNALAUTHENTICATECALLBACK     pfnInternalAuthenticate;
   EXTERNALAUTHENTICATECALLBACK     pfnExternalAuthenticate;
   ONSECURELINKREADY                pfnOnSecureLinkReady;      // used by TLS also
   ONNONSECURESENDISCL              pfnOnNonSecureSendISCL;
   ONNONSECURERECEIVEDISCL          pfnOnNonSecureReceivedISCL;
// debug only
   RECEIVEDISCLPACKET               pfnOnReceivedISCLPacket;
// end of added for ISCL compliance
} DICOMNETCALLBACK, *pDICOMNETCALLBACK;

#ifdef __cplusplus

typedef struct _NETLINK NETLINK, *pNETLINK;
typedef struct _ISCLInternalData ISCLInternalData, *pISCLInternalData;

typedef struct _LDICOMNETPRIVATEDATA
{
   L_INT    nSize;
   L_BOOL   m_bEnable;

   // 0 - normal, 
   // or DEBUG_MODE_ONRECEIVE_SHOW_EXTENDED_INFO, 
   // or DEBUG_MODE_ONSEND_SHOW_EXTENDED_INFO
   L_UINT32 m_DebugModeFlags;

   L_BOOL   m_bUseExtendedOnSend;
   L_BOOL   m_bUseExtendedOnReceive;
   DICOMNETDEBUGINFOONSEND m_DebugInfoOnSend;
}LDICOMNETPRIVATEDATA , * pLDICOMNETPRIVATEDATA;

class DICOM_EXPORT LDicomNet
{
public:

   pNETLINK m_pNetMessageQueue;
   pISCLInternalData m_pISCLIntData;

// added for security - used by TLS and ISCL
   virtual L_VOID OnSecureLinkReady(L_UINT32 nError);  // can be 0 - OK and non-zero -  failure

// added for TLS compliance

   L_CIPHERSUITE  GetCipherFromIndexTLS(L_UINT32 nIndex);
   L_UINT32       SetCipherToIndexTLS(L_UINT32 nIndex, L_CIPHERSUITE cipher);

   L_CIPHERSUITE  GetCiphersuiteTLS();

   L_UINT32       GetEncryptionAlgorithmTLS(L_CIPHERSUITE cipher);
   L_UINT32       GetAuthenticationAlgorithmTLS(L_CIPHERSUITE cipher);
   L_UINT32       GetIntegrityAlgorithmTLS (L_CIPHERSUITE cipher);
   L_UINT32       GetKeyExchangeAlgorithmTLS(L_CIPHERSUITE cipher);

   L_UINT32       GetEncryptKeyLengthTLS (L_CIPHERSUITE cipher);
   L_UINT32       GetMutualAuthKeyLengthTLS (L_CIPHERSUITE cipher);
   L_UINT32       SetClientCertificateTLS(L_CHAR *pszPathToCertificate, L_UINT32 certType, L_CHAR *pszPathToKeyFile);
      // certType can be L_TLS_FILETYPE_PEM (clear text) or L_TLS_FILETYPE_ASN1 (binary)
      // the client have zero or one certificate
   L_UINT32       SetServerCertificateTLS(L_CHAR *pszPathToCertificate, L_UINT32 certType, L_CHAR *pszPathToKeyFile);
      // the server can have a chain of certificates in a single file
      // certType can be L_TLS_FILETYPE_PEM (clear text) or L_TLS_FILETYPE_ASN1 (binary)
      // AT LEAST ONE certificate is required for a TLS server

   virtual L_BOOL SetVerifyTLS(L_UINT32 nMode, TLS_CERT_VERIFY_CALLBACK verifyCallback);

// not to be documented
   L_UINT32       GetTLSStatus();
   L_VOID         SetTLSStatus(L_UINT32 nStatus);
      // 0 - non connected
      // 1 - client during TLS handshake
      // 2 - server during TLS_handshake
      // 3 - connected
// end of added for TLS

// added  for ISCL compliance - 18.09.2001
   // interface for ISCL operations:

   L_UINT32 SetMaxCommBlockLengthISCL(L_UINT32 nMaxCommBlockLength);   // maximum communication block size, there are performance
         // advantages if a comm block of ISCL is included into a TCP packet
   L_UINT32 GetCommBlockLengthISCL();     // return the comm block size negociated
   L_UINT32 SetMaxMessageLengthISCL(L_UINT32 nMsgLength);     // the maximum message length that can be processed - 1MB, 2MB and so on

   L_UINT32 SetMutualAuthAlgISCL(L_UINT32 mutualAuthMode);       // only 4way 3pass
   L_UINT32 SetDefaultEncryptionISCL(L_UINT32 EncryptionMode);   // bulk data encryption algorithm
   L_UINT32 SetDefaultSigningISCL(L_UINT32 SignMode);            // message authentication algorithm
   L_UINT32 GetPeerEncryptionISCL();   // can be checked to see what algorithm of communication the sender tries to use
   L_UINT32 GetPeerMACISCL();      // ATTN: if the crypt/MAC algorithm differs, the message is dropped and the GetPeerEncryption()/GetPeerMAC() will tell me
                                    // the algorithms of crypt/MAC used by the client

   L_UINT32 GetErrorSecure();       // returns the m_nISCLError in ISCL case, or m_nTLSError in case of TLS

   virtual L_UINT32 GetChallengeISCL(L_UINT64 *nChallenge, L_UINT64 nParameter);
   virtual L_UINT32 InternalAuthenticateISCL(L_UINT64 nChallenge, L_UINT64 *nResponse, L_UINT64 nParameter);
   virtual L_UINT32 ExternalAuthenticateISCL(L_UINT64 nChallenge, L_UINT64 nResponse, L_UINT64 nParameter);
         // functions described in ISO 7816-4


   L_UINT32 SetAuthDataISCL(L_VOID *pBuffer, L_UINT32 nLength);    // nLength = 1...128
   L_UINT32 GetPeerAuthDataISCL(L_VOID *pBuffer, L_UINT32 *nLength);
         // if nLength not between 1 and 128 bytes, error
         // used to set or obtain the authentication data exchanged during the mutual authentication (connectISCL/acceptISCL)

   L_UINT32 GetPeerRequestedMessageLengthISCL();      // used if local end refuse to receive
         // peer mesage because message size bigger than local end max
         // example: a server can use max 1MB message, but a client could try to send a 16 MB message

   L_UINT32 SetMutualAuthKeyISCL(L_UINT32 nIndex, L_UINT64 key);      // key used during mutual authentication
            // it looks unused for the V1.00 of ISCL
   L_UINT32 SetIndexForMutualAuthISCL(L_UINT32 nIndex);
            // index from 1 to 8 for the mutual auth key - see the remark 2 lines up
   L_UINT32 SetEncryptKeyISCL(L_UINT32 nIndex, L_UINT64 key);
            // index from 1 to 8 for the encryption key - used to load communication keys
   L_UINT32 SetIndexForEncryptISCL(L_UINT32 nIndex);
            // index from 1 to 8 to select the encryption key


   L_BOOL   IsISCLQueueEmpty();

   L_UINT32 GetIndexForEncryptISCL();
   L_UINT32 GetIndexForMutualAuthISCL();
   L_UINT32 GetStatusISCL();                          // return the internal status of the object.
         // Description of internal status will be added in docs, see also the source

   L_INT    CloseForced(L_BOOL bForced);

   L_INT32  SendNonSecureISCL(L_CHAR *pBuffer, L_UINT32 nBytes);
   virtual  L_VOID OnNonSecureSendISCL(L_INT nError, L_UCHAR nType, L_UINT32 nLength);
   virtual  L_VOID OnNonSecureReceivedISCL(L_UINT32 nError, L_CHAR *pBuffer, L_UINT32 nLength);

   virtual  L_VOID OnReceivedISCLPacket(L_INT nError, L_CHAR *pBuffer, L_UINT32 nBytes);  // error code, buffer and length

   L_UINT32 GetSecureMode();

// end of added for ISCL

   LDicomNet(L_CHAR *pszPath, L_INT32 nMode);
      // modified for security: Added L_INT32 nMode parameter of constructor.
      // Values for nMode: DICOM_SECURE_ISCL, DICOM_SECURE_TLS, DICOM_SECURE_NONE
      // if a bad value is supplied, security will be DICOM_SECURE_NONE

   virtual ~LDicomNet();

   static L_INT     StartUp                    ();
   static L_VOID    ShutDown                   ();

   L_INT            Connect                    (L_CHAR *pszHostAddress, L_UINT nHostPort, L_CHAR *pszPeerAddress, L_UINT nPeerPort);
   L_INT            Listen                     (L_CHAR *pszHostAddress, L_UINT nHostPort, L_INT nNbPeers);
   L_INT            Accept                     (LDicomNet *pNet);
   L_VOID           Close                      ();
   
   L_INT            SendAssociateRequest       (LDicomAssociate *pPDU);
   L_INT            SendAssociateAccept        (LDicomAssociate *pPDU);
   L_INT            SendAssociateReject        (L_UCHAR nResult, L_UCHAR nSource, L_UCHAR nReason);
   L_INT            SendData                   (L_UCHAR nPresentationID, LDicomDS *pCS, LDicomDS *pDS);
   L_INT            SendReleaseRequest         ();
   L_INT            SendReleaseResponse        ();
   L_INT            SendAbort                  (L_UCHAR nSource, L_UCHAR nReason);

   L_INT            SendCStoreRequest          (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nPriority, L_CHAR *pszMoveAE, L_UINT16 nMoveMessageID, LDicomDS *pDS);
   L_INT            SendCStoreResponse         (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);
   L_INT            SendCFindRequest           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, LDicomDS *pDS);
   L_INT            SendCFindResponse          (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, LDicomDS *pDS);
   L_INT            SendCGetRequest            (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, LDicomDS *pDS);
   L_INT            SendCGetResponse           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, LDicomDS *pDS);
   L_INT            SendCMoveRequest           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, L_CHAR *pszMoveAE, LDicomDS *pDS);
   L_INT            SendCMoveResponse          (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, LDicomDS *pDS);
   L_INT            SendCCancelRequest         (L_UCHAR nPresentationID, L_UINT16 nMessageID);
   L_INT            SendCEchoRequest           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass);
   L_INT            SendCEchoResponse          (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus);
   L_INT            SendNReportRequest         (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nEvent, LDicomDS *pDS);
   L_INT            SendNReportResponse        (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nEvent, LDicomDS *pDS);
   L_INT            SendNGetRequest            (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT32 *pnAttribute, L_UINT16 nCount);
   L_INT            SendNGetResponse           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   L_INT            SendNSetRequest            (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, LDicomDS *pDS);
   L_INT            SendNSetResponse           (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   L_INT            SendNActionRequest         (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nAction, LDicomDS *pDS);
   L_INT            SendNActionResponse        (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nAction, LDicomDS *pDS);
   L_INT            SendNCreateRequest         (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, LDicomDS *pDS);
   L_INT            SendNCreateResponse        (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   L_INT            SendNDeleteRequest         (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance);
   L_INT            SendNDeleteResponse        (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);

   L_BOOL           IsActivated                ();
   L_BOOL           IsConnected                ();
   L_BOOL           IsAssociated               ();

   L_UINT32         GetQueueSend               ();

   LDicomNet       *GetServer                  ();
   L_UINT32         GetClientCount             ();
   LDicomNet       *GetClient                  (L_UINT nIndex);

   L_INT            GetHostInfo                (L_CHAR *pszAddress, L_UINT *pnPort);
   L_INT            GetPeerInfo                (L_CHAR *pszAddress, L_UINT *pnPort);

   LDicomAssociate *GetAssociate               ();

   virtual L_VOID   OnConnect                  (L_INT nError);
   virtual L_VOID   OnAccept                   (L_INT nError);
   virtual L_VOID   OnClose                    (L_INT nError, LDicomNet *pNet);
   virtual L_VOID   OnReceive                  (L_INT nError, L_UCHAR nType, L_CHAR *pBuffer, L_UINT32 nBytes);
   virtual L_VOID   OnSend                     (L_INT nError, L_UCHAR nType, L_UINT32 nBytes);

   virtual L_VOID   OnReceiveAssociateRequest  (LDicomAssociate *pPDU);
   virtual L_VOID   OnReceiveAssociateAccept   (LDicomAssociate *pPDU);
   virtual L_VOID   OnReceiveAssociateReject   (L_UCHAR nResult, L_UCHAR nSource, L_UCHAR nReason);
   virtual L_VOID   OnReceiveData              (L_UCHAR nPresentationID, LDicomDS *pCS, LDicomDS *pDS);
   virtual L_VOID   OnReceiveReleaseRequest    ();
   virtual L_VOID   OnReceiveReleaseResponse   ();
   virtual L_VOID   OnReceiveAbort             (L_UCHAR nSource, L_UCHAR nReason);

   virtual L_VOID   OnReceiveCStoreRequest     (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nPriority, L_CHAR *pszMoveAE, L_UINT16 nMoveMessageID, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCStoreResponse    (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);
   virtual L_VOID   OnReceiveCFindRequest      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCFindResponse     (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCGetRequest       (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCGetResponse      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCMoveRequest      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, L_CHAR *pszMoveAE, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCMoveResponse     (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, LDicomDS *pDS);
   virtual L_VOID   OnReceiveCCancelRequest    (L_UCHAR nPresentationID, L_UINT16 nMessageID);
   virtual L_VOID   OnReceiveCEchoRequest      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass);
   virtual L_VOID   OnReceiveCEchoResponse     (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus);
   virtual L_VOID   OnReceiveNReportRequest    (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nEvent, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNReportResponse   (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nEvent, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNGetRequest       (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT32 *pnAttribute, L_UINT16 nCount);
   virtual L_VOID   OnReceiveNGetResponse      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNSetRequest       (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNSetResponse      (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNActionRequest    (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nAction, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNActionResponse   (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nAction, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNCreateRequest    (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNCreateResponse   (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, LDicomDS *pDS);
   virtual L_VOID   OnReceiveNDeleteRequest    (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance);
   virtual L_VOID   OnReceiveNDeleteResponse   (L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);
   virtual L_VOID   OnReceiveUnknown           (L_UCHAR nPresentationID, LDicomDS *pCS, LDicomDS *pDS);


   SSL_CTX * EXT_FUNCTION GetCTX();
   //---------------------------------------------------------------------------
   // Private Functions (Internal use only)
   //---------------------------------------------------------------------------
   L_VOID           SetCallback                (pDICOMNETCALLBACK pCallback);

   L_UINT32 SetDebugMode(L_UINT32 nDebugMode);  // returns the old debug mode
   virtual L_VOID   OnSendExt(pDICOMNETDEBUGINFOONSEND pDicomNetDebugInfoOnsend);
 
private:
   L_BOOL                  m_bConnected;
   L_BOOL                  m_bAssociated;
   pLDICOMNETPRIVATEDATA   m_pPrivateData;
   LDicomAssociate         m_AssociateRQ;
   LDicomAssociate         m_AssociateAC;
   LDicomFile              m_SendFile;
   LDicomDS                m_SendCS;
   LDicomFile              m_ReceiveFileCS;
   LDicomFile              m_ReceiveFileDS;
   LDicomDS                m_ReceiveCS;
   LDicomDS                m_ReceiveDS;
   L_CHAR                  m_szPath[_MAX_PATH];
   DICOMNETCALLBACK        m_Callback;
   static HINSTANCE        m_hLibrary;
   static HINSTANCE        m_hLibCry;
   static HINSTANCE        m_hLibTLS;

   L_UINT16 GetTS       (L_BOOL bCommand, L_CHAR *pszUID);
   L_INT    Send        (L_CHAR *pBuffer, L_UINT32 nBytes);
   L_VOID   Receive     (L_INT nError, L_UCHAR nType, L_CHAR *pBuffer, L_UINT32 nBytes);
   L_VOID   ReceiveData (L_UCHAR nPresentationID, LDicomDS *pCS, LDicomDS *pDS);
   L_INT    SendData    (L_BOOL bCommand, L_UCHAR nPresentationID, LDicomDS *pDS);

   static L_INT   GetError(L_UINT32 nError);
   friend LRESULT CALLBACK L_NetWindowCallback (HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);   
// added for ISCL compliance
   // private members:
   L_UINT32 m_nTLSError;
   L_BOOL   m_bInTransmission;    // set when a transmission is processed
                              // not set when the ISCL layer is ready to accept another job (send/receive)
         // differs from m_Status: m_Status keep his value after exiting (w/ error) from a transmit job)

//   L_BOOL   m_bIsServer;      // to know if I call OnAccept or OnConnect
   L_UINT32 m_SecurityStandard;     // choose between DICOM_ISCL, DICOM_TLS and DICOM_NO_SECURITY
   L_UCHAR  m_AuthData[128];
   L_UCHAR  m_PeerAuthData[128];
   L_UINT32 m_nAuthDataLength, m_nPeerAuthDataLength;
   L_UINT32 m_nDelay_ms;    // wait time before timeout error, in milliseconds - not usable w/ LEADtk


   L_UINT32 m_nMaxCommBlockLength;   // max acceptable, automagically = 8kB
   L_UINT32 m_nCommBlockLength;        // negociated block size
   L_UINT32 m_nMaxMessageLength;     // the size of the message the object (server or client) is able to send/receive
   L_UINT32 m_nPeerRequestedMsgLength; // the size the other comm end tried to send


   L_UINT32 m_CryptAlg, m_PeerCryptAlg;
   L_UINT32 m_MACAlg, m_PeerMACAlg;   // DESMAC or MD5 or none. MUST be the same for communication

   L_UINT32 m_Status, m_StatusOld;    // internal status (communication wise) and previous status

   L_UINT32 m_mutualAuthAlg; // only 4way 3pass is defined in standard
   L_UINT64 m_AuthKey[8];    // the keys for  mutual auth
   L_UINT64 m_EncryptKey[8]; // the keys used for encryption
   L_UINT32 m_nAuthKeyId, m_nEncryptKeyId;  // 0-based indexes
            // m_nEncryptKeyId is KEY_ONE to KEY_EIGHT or UNIQUE_KEYS
            // ATTN: if uniques keys, then every new message is sent with a key that is negociated at that moment
   L_UINT64 m_sessionKey;         // this is the key used for en/decryption. It is initialized to the correct key
         // or takes the value negociated during a "Random number for generating session key" request/response

   L_BOOL   m_bUseAutoChangeKeys;

   L_UINT32 m_nRequestedSendLength;
   L_UINT32 m_nCurrentSendLength;
   L_UCHAR  m_cCurrentType;

   L_UINT32 m_nISCLError;  // used because the function of treating messages does not return values
   L_UINT64 m_n64ServerChallenge, m_n64ServerResponse, m_n64ClientChallenge, m_n64ClientResponse;
         // even if looks weird, the server generates n64ChallengeServer and n64ResponseClient
         // so I check the n64ChServer and n64RespServer if match - it is a n64RespForServerChallenge



   L_UCHAR m_ivec[8];      // m_ivec is the initialisation vector for encryption with DES CBC
            // it is set at 0 in connect and accept. If the DESCBC_CHAIN_IVEC_OVER_SIGNATURE or DESCBC_CHAIN_IVEC_OVER_MAC are
            // NOT set, the ivec is set to 0 after every encrypt operation

   L_UCHAR m_sSignature[24];     // I don't use dynamic allocated memory
   L_UCHAR m_sEncryptedSignature[24];

   L_CHAR *m_pRecvEncryptedData, *m_pRecvDecryptedData;
   L_UINT32 m_nRequestedDataLength, m_nRecvDataIndex, m_nRecvDecryptedLength;

// private (implementation) methods:

   L_UINT32 Sign(L_VOID *pBuffer, L_UINT32 nLength, L_VOID *pSign, L_UINT32 *nOutLength);
         // generates a MAC code for the data from pBuffer using the current MAC method
         // the length of the MAc is 64 bits for DESMAC and 128 bits for MD5


   L_UINT32 CryptSendDataISCL(L_CHAR *pBuffer, L_UINT32 nLength);
         // gets data from pBuffer and sent it thu network, encrypted w/ current rypting algorithm
   L_UINT32 CryptSendMACISCL(L_CHAR *pBuffer, L_UINT32 nLength);
         // send a MAC for data in pBuffer, crypted w/ current algorithm

   L_UINT32 Get32bDataFromOffset(L_CHAR *pBuffer, L_UINT32 nOffset);
   L_UINT64 Get64bDataFromOffset(L_CHAR *pBuffer, L_UINT32 nOffset);

   L_INT32  SendRaw(L_CHAR *pBuffer, L_UINT32 nBytes); // just like Send in non secure mode

   L_UINT32 Encrypt (L_VOID *pBufferIn,
                        L_UINT32 nLength,
                        L_VOID *pBufferOut,
                        L_UINT32 *nLengthOut
                       );
         // add padding to pBufferIn, encrypt nLength bytes from pBufferIn
         // and write the crypted msg into pBufferOut. nLengthOut is the size of crypted msg
         // if called with pBufferOut == NULL, then return the required length
         // also when nLengthOut is too small
         // returns DICOM_SUCCES if OK, not 0 if nLengthLut too small
         // nLengthOut is updated to the necessary size
         // ivec is the initialisation vector. It is used to chain the previous state for the DES CBC encryption algorithm
         // ivec is a 8 bytes array

   L_UINT32 Decrypt (L_VOID *pBufferIn,
                        L_UINT32 nLength,
                        L_VOID *pBufferOut,
                        L_UINT32 *nLengthOut
                       );
         // ATTN: MiDecrypt uses an BufferOut capable to contain a number of
         // blocks (is longer with at most 8 bytes than the actual decrypted message)
         // returns DICOM_SUCCESS if data decrypted and padding removed. Update nLengthOut to correct length of decrypted message
         // return error if decryption failed (could not clear the padding from the end)
         // ivec is the initialisation vector. It is used to chain the previous state for the DES CBC encryption algorithm
         // ivec is a 8 bytes array

   L_UINT32 MD5Sign(L_VOID *pBuffer, L_UINT32 nLength, L_VOID *pSign);
      // creates a message authentication code of the L_VOID *pBuffer, put it
      //    into the pSign and returns the length of sign
      // ATTN: as I know the sign method, I know the length of MAC - 16 bytes
   L_UINT32 DESMACSign(L_VOID *pBuffer, L_UINT32 nLength, L_VOID *pSign);
      // this time only 64-bit (8 bytes) data
      // DESMAC use the default key for sign. MD5 does not use key for sign, but at the end
      // the message digest is encrypted with the current encryption key and algorithm (if any)


   L_INT32 LineReset();


   L_INT32  LineConnectionCheckRequest ();
   L_INT32  LineConnectionCheckResponse(L_UINT32 status, L_UINT32 nISCLCommBlockLength);

   L_INT32  MutualAuthRequest          (L_UINT32 mutualAuthMethod,
                                        L_UINT32 mutualKeyPairId
                                       );
   L_INT32  MutualAuthResponse(L_UINT32 status);
   L_INT32  MutualAuthPass1Notification(L_UINT32 status,
                                        L_UINT64 nChallenge,
                                        L_UINT32 nRetGCh
                                       );
   L_INT32  MutualAuthPass2Notification(
                                        L_UINT32 status,
                                        L_UINT64 nResponseCode,
                                        L_UINT64 nChallenge2,
                                        L_UINT32 nOption = 0   // result from GetCh or InternalAuth
                                                                // 0 is OK
                                       );
   L_INT32  MutualAuthPass3Notification(
                                        L_UINT32 status,
                                        L_UINT64 nResponseCode2,
                                        L_UINT32 nOption = 0   // result code from ExtAuth or IntAuth
                                                                // 0 is OK
                                       );
   L_INT32  MutualAuthCompletion(L_UINT32 nAuthCode);
   L_INT32  SendTransmissionRequest    (L_UINT32 EncryptMethod, 
                                        L_UINT32 nEncryptKeyId,
                                        L_UINT32 MessageAuthMethod,
                                        L_UINT32 nMessageLength
                                       );
   L_INT32  SendTransmissionResponse   (L_UINT32 acknoledgeCode,
                                        L_UINT32 nMessageLength
                                       );
   L_INT32  RandomNoForSessionKeyRequest(
                                        L_UINT64 nRndNoForSessionKey,
                                        L_UINT32 nResultCode
                                       );
   L_INT32  RandomNoForSessionKeyResponse(L_UINT32 nResultCode);

   L_INT32  MsgTransmitNotification    (L_VOID *rawData,
                                        L_UINT32 nSplitMsgLength
                                       );

   L_INT32  MsgAuthCode                (L_VOID *pAuthCode,
                                        L_UINT32 nAuthCodeLength
                                       );

   L_INT32  ThroughModeTransmission    (L_VOID *rawData,
                                        L_UINT32 nMessageLength  // is not limited by comm block size
                                       );

   L_INT32  LineDisconnectionRequest();
   L_INT32  LineDisconnectionResponse(L_UINT32 status);

   L_INT32  SetHeader                  (L_VOID *pBuffer,
                                        L_UINT32 indicator,
                                        L_UINT32 messageId,
                                        L_UINT32 nDataLength,
                                        L_UINT32 option,
                                        L_UINT32 timeStamp,
                                        L_UINT32 errNo,
                                        L_UINT32 stuff32_1 = 0,
                                        L_UINT32 stuff32_2 = 0
                                       );

   L_INT32  CreateEmptyMessage(L_VOID **pBuffer, L_UINT32 nLength);
      // allocates a area of size 32+nLength (header and data);

   L_INT32  CopyMessageData(L_VOID *pPacket, L_UINT32 nOffset, L_VOID *pData, L_UINT32 nLength);
      // copy raw data into message data area starting from offset bytes

   L_INT32  OnISCLPacketSend(L_INT nError, L_UINT32 nMsgId, L_UINT32 nLength);

// end of added for ISCL

// added for TLS compliance

   SSL_CTX *m_pCtx;
   L_CIPHERSUITE m_ciphersuites[16];
   L_CIPHERSUITE m_ActualCiphersuite;

public:
// not to be documented
   L_BOOL   m_bISCLConnected;
   L_UINT32 m_nTLSVerifyMode;
   SSL *m_TLSConn;
   static LDicomNet *m_pNetTLS[512];
   HWND             m_hWnd;
   L_VOID SetIsSecureConnected(L_BOOL bIsConnected);
   L_BOOL GetIsSecureConnected();

   L_VOID SetHandshakeDebug(L_BOOL isDebug, L_VOID (*myfn)(LDicomNet *pDic, const char *TLS_STATUS, int ret));

// end of not to be documented

// end of added for TLS

};

#endif

#ifdef __cplusplus
extern "C"
{
#endif
// modified for security
   // added parameter nMode
   HDICOMNET EXT_FUNCTION L_DicomCreateNet                  (L_CHAR *pszPath, L_INT32 nMode);
// end of modified for security


// added for ISCL compliance
   L_UINT32 EXT_FUNCTION L_DicomSetMaxCommBlockLengthISCL(HDICOMNET hNet, L_UINT32 nCommBlockLength);   // maximum communication block size, there are performance
         // advantages if a comm block of ISCL is included into a TCP packet
   L_UINT32 EXT_FUNCTION L_DicomGetCommBlockLengthISCL(HDICOMNET hNet);     // return the comm block size negociated
   L_UINT32 EXT_FUNCTION L_DicomSetMaxMessageLengthISCL(HDICOMNET hNet, L_UINT32 nMsgLength);     // the maximum message length that can be processed - 1MB, 2MB and so on

   L_UINT32 EXT_FUNCTION L_DicomSetMutualAuthAlgISCL(HDICOMNET hNet, L_UINT32 mutualAuthMode);       // only 4way 3pass
   L_UINT32 EXT_FUNCTION L_DicomSetDefaultEncryptionISCL(HDICOMNET hNet, L_UINT32 EncryptionMode);   // bulk data encryption algorithm
   L_UINT32 EXT_FUNCTION L_DicomSetDefaultSigningISCL(HDICOMNET hNet, L_UINT32 SignMode);            // message authentication algorithm
   L_UINT32 EXT_FUNCTION L_DicomGetPeerEncryptionISCL(HDICOMNET hNet);   // can be checked to see what algorithm of communication the sender tries to use
   L_UINT32 EXT_FUNCTION L_DicomGetPeerMACISCL(HDICOMNET hNet);      // ATTN: if the crypt/MAC algorithm differs, the message is dropped and the GetPeerEncryption()/GetPeerMAC() will tell me
                                    // the algorithms of crypt/MAC used by the client

   L_UINT32 EXT_FUNCTION L_DicomGetErrorSecure(HDICOMNET hNet);       // returns the m_nISCLError in ISCL case, or m_nTLSError in case of TLS



         // functions described in ISO 7816-4


   L_UINT32 EXT_FUNCTION L_DicomSetAuthDataISCL(HDICOMNET hNet, L_VOID *pBuffer, L_UINT32 nLength);    // nLength = 1...128
   L_UINT32 EXT_FUNCTION L_DicomGetPeerAuthDataISCL(HDICOMNET hNet, L_VOID *pBuffer, L_UINT32 *nLength);
         // if nLength not between 1 and 128 bytes, error
         // used to set or obtain the authentication data exchanged during the mutual authentication (connectISCL/acceptISCL)

   L_UINT32 EXT_FUNCTION L_DicomGetPeerRequestedMessageLengthISCL(HDICOMNET hNet);      // used if local end refuse to receive
         // peer mesage because message size bigger than local end max
         // example: a server can use max 1MB message, but a client could try to send a 16 MB message

   L_UINT32 EXT_FUNCTION L_DicomSetMutualAuthKeyISCL(HDICOMNET hNet, L_UINT32 nIndex, L_UINT64 nKey);      // key used during mutual authentication
            // it looks unused for the V1.00 of ISCL
   L_UINT32 EXT_FUNCTION L_DicomSetIndexForMutualAuthISCL(HDICOMNET hNet, L_UINT32 nIndex);
            // index from 1 to 8 for the mutual auth key - see the remark 2 lines up
   L_UINT32 EXT_FUNCTION L_DicomSetEncryptKeyISCL(HDICOMNET hNet, L_UINT32 nIndex, L_UINT64 key);
            // index from 1 to 8 for the encryption key - used to load communication keys
   L_UINT32 EXT_FUNCTION L_DicomSetIndexForEncryptISCL(HDICOMNET hNet, L_UINT32 nIndex);
            // index from 1 to 8 to select the encryption key
   L_UINT32 EXT_FUNCTION L_DicomGetIndexForEncryptISCL(HDICOMNET hNet);
   L_UINT32 EXT_FUNCTION L_DicomGetIndexForMutualAuthISCL(HDICOMNET hNet);

   L_UINT32 EXT_FUNCTION L_DicomGetStatusISCL(HDICOMNET hNet);                          // return the internal status of the object.
         // Description of internal status will be added in docs, see also the source

   L_BOOL   EXT_FUNCTION L_DicomIsISCLQueueEmpty(HDICOMNET hNet);

   L_INT    EXT_FUNCTION L_DicomCloseForced(HDICOMNET hNet, L_BOOL bForced);

   L_INT32  EXT_FUNCTION L_DicomSendNonSecureISCL(HDICOMNET hNet, L_CHAR *pBuffer, L_UINT32 nBytes);

   L_UINT32 EXT_FUNCTION L_DicomGetSecureMode(HDICOMNET hNet);
// end of added for ISCL compliance

// added for TLS compliance
   L_CIPHERSUITE EXT_FUNCTION L_DicomGetCipherFromIndexTLS(HDICOMNET hNet, L_UINT32 nIndex);
   L_UINT32      EXT_FUNCTION L_DicomSetCipherToIndexTLS(HDICOMNET hNet, L_UINT32 nIndex, L_CIPHERSUITE cipher);
   L_CIPHERSUITE EXT_FUNCTION L_DicomGetCiphersuiteTLS(HDICOMNET hNet);
   L_UINT32      EXT_FUNCTION L_DicomGetEncryptionAlgorithmTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);   
   L_UINT32      EXT_FUNCTION L_DicomGetAuthenticationAlgorithmTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);   
   L_UINT32      EXT_FUNCTION L_DicomGetIntegrityAlgorithmTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);   
   L_UINT32      EXT_FUNCTION L_DicomGetKeyExchangeAlgorithmTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);   
   L_UINT32      EXT_FUNCTION L_DicomGetEncryptKeyLengthTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);
   L_UINT32      EXT_FUNCTION L_DicomGetMutualAuthKeyLengthTLS(HDICOMNET hNet, L_CIPHERSUITE cipher);
   L_UINT32      EXT_FUNCTION L_DicomSetClientCertificateTLS(HDICOMNET hNet, L_CHAR *pszPathToCertificateFile, L_UINT32 nCertType, L_CHAR *pszPathToKeyFile);
   L_UINT32      EXT_FUNCTION L_DicomSetServerCertificateTLS(HDICOMNET hNet, L_CHAR *pszPathToCertificateFile, L_UINT32 nCertType, L_CHAR *pszPathToKeyFile);
// end of added for TLS compliance

   L_VOID    EXT_FUNCTION L_DicomFreeNet                    (HDICOMNET hNet);

   L_INT     EXT_FUNCTION L_DicomStartUp                    ();
   L_VOID    EXT_FUNCTION L_DicomShutDown                   ();

   L_INT     EXT_FUNCTION L_DicomConnect                    (HDICOMNET hNet, L_CHAR *pszHostAddress, L_UINT nHostPort, L_CHAR *pszPeerAddress, L_UINT nPeerPort);
   L_INT     EXT_FUNCTION L_DicomListen                     (HDICOMNET hNet, L_CHAR *pszHostAddress, L_UINT nHostPort, L_INT nNbPeers);
   L_INT     EXT_FUNCTION L_DicomAccept                     (HDICOMNET hNet, HDICOMNET hPeer);
   L_VOID    EXT_FUNCTION L_DicomClose                      (HDICOMNET hNet);
   
   L_INT     EXT_FUNCTION L_DicomSendAssociateRequest       (HDICOMNET hNet, HDICOMPDU hPDU);
   L_INT     EXT_FUNCTION L_DicomSendAssociateAccept        (HDICOMNET hNet, HDICOMPDU hPDU);
   L_INT     EXT_FUNCTION L_DicomSendAssociateReject        (HDICOMNET hNet, L_UCHAR nResult, L_UCHAR nSource, L_UCHAR nReason);
   L_INT     EXT_FUNCTION L_DicomSendData                   (HDICOMNET hNet, L_UCHAR nPresentationID, HDICOMDS hCS, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendReleaseRequest         (HDICOMNET hNet);
   L_INT     EXT_FUNCTION L_DicomSendReleaseResponse        (HDICOMNET hNet);
   L_INT     EXT_FUNCTION L_DicomSendAbort                  (HDICOMNET hNet, L_UCHAR nSource, L_UCHAR nReason);

   L_INT     EXT_FUNCTION L_DicomSendCStoreRequest          (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nPriority, L_CHAR *pszMoveAE, L_UINT16 nMoveMessageID, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCStoreResponse         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);
   L_INT     EXT_FUNCTION L_DicomSendCFindRequest           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCFindResponse          (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCGetRequest            (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCGetResponse           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCMoveRequest           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nPriority, L_CHAR *pszMoveAE, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCMoveResponse          (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus, L_UINT16 nRemaining, L_UINT16 nCompleted, L_UINT16 nFailed, L_UINT16 nWarning, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendCCancelRequest         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID);
   L_INT     EXT_FUNCTION L_DicomSendCEchoRequest           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass);
   L_INT     EXT_FUNCTION L_DicomSendCEchoResponse          (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_UINT16 nStatus);
   L_INT     EXT_FUNCTION L_DicomSendNReportRequest         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nEvent, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNReportResponse        (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nEvent, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNGetRequest            (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT32 *pnAttribute, L_UINT16 nCount);
   L_INT     EXT_FUNCTION L_DicomSendNGetResponse           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNSetRequest            (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNSetResponse           (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNActionRequest         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nAction, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNActionResponse        (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, L_UINT16 nAction, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNCreateRequest         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNCreateResponse        (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus, HDICOMDS hDS);
   L_INT     EXT_FUNCTION L_DicomSendNDeleteRequest         (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance);
   L_INT     EXT_FUNCTION L_DicomSendNDeleteResponse        (HDICOMNET hNet, L_UCHAR nPresentationID, L_UINT16 nMessageID, L_CHAR *pszClass, L_CHAR *pszInstance, L_UINT16 nStatus);

   L_BOOL    EXT_FUNCTION L_DicomIsActivated                (HDICOMNET hNet);
   L_BOOL    EXT_FUNCTION L_DicomIsConnected                (HDICOMNET hNet);
   L_BOOL    EXT_FUNCTION L_DicomIsAssociated               (HDICOMNET hNet);

   L_UINT32  EXT_FUNCTION L_DicomGetQueueSend               (HDICOMNET hNet);

   HDICOMNET EXT_FUNCTION L_DicomGetServer                  (HDICOMNET hNet);
   L_UINT32  EXT_FUNCTION L_DicomGetClientCount             (HDICOMNET hNet);
   HDICOMNET EXT_FUNCTION L_DicomGetClient                  (HDICOMNET hNet, L_UINT nIndex);

   L_INT     EXT_FUNCTION L_DicomGetHostInfo                (HDICOMNET hNet, L_CHAR *pszAddress, L_UINT *pnPort);
   L_INT     EXT_FUNCTION L_DicomGetPeerInfo                (HDICOMNET hNet, L_CHAR *pszAddress, L_UINT *pnPort);

   HDICOMPDU EXT_FUNCTION L_DicomGetAssociate               (HDICOMNET hNet);

   L_VOID    EXT_FUNCTION L_DicomSetCallback                (HDICOMNET hNet, pDICOMNETCALLBACK pCallback);

#ifdef __cplusplus
};
#endif
#endif /* _WIN32_WCE */

//============= END-OF-FILE ====================================================

#endif  // LTDIC_H_INCLUDED
