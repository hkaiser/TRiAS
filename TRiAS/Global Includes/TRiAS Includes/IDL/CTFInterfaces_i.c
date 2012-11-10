/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.76 */
/* at Tue May 05 20:39:08 1998
 */
/* Compiler settings for CTFInterfaces.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID__DGMPoint = {0xCE361C90,0xB00C,0x11CF,{0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69}};


const IID IID__DGMPoints = {0x4DBFC540,0xB33E,0x11CF,{0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69}};


const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};


const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};


#ifdef __cplusplus
}
#endif

