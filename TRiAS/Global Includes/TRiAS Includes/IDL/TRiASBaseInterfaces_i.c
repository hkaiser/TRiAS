/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.76 */
/* at Fri Feb 06 17:59:49 1998
 */
/* Compiler settings for TRiASBaseInterfaces.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_DTRiASBaseClass = {0x8DE4E3E0,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};


const IID IID_DTRiASCollection = {0x8DE4E3DF,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};


const IID IID_DTRiASProperty = {0x079638C1,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};


const IID IID_DTRiASProperties = {0x079638C2,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};


#ifdef __cplusplus
}
#endif

