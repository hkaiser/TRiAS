// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter.cpp
// Revision: public build 4, shipped on 29-Aug-98

#if !defined(CLASSICS_EXPORT)
#define CLASSICS_EXPORT __declspec(dllexport)
#endif // CLASSICS_EXPORT

#include "classics\atomic_counter.h"

STARTWRAP
namespace classics {
namespace internal {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xadd (volatile int*, int)
 {
 __asm {
    lock xadd dword ptr [ECX], EDX
    mov EAX, EDX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xadd (volatile short*, int)
 {
 __asm {
    lock xadd word ptr [ECX], DX
    mov AX, DX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xadd (volatile char*, int)
 {
 __asm {
    lock add byte ptr [ECX], DL
    mov AL, DL
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xexchange (volatile int*, int)
 {
 __asm {
    mov EAX, EDX
    xchg dword ptr [ECX], EAX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xexchange (volatile short*, int)
 {
 __asm {
    mov AX, DX
    xchg word ptr [ECX], AX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xexchange (volatile char*, int)
 {
 __asm {
    mov AL, DL
    xchg byte ptr [ECX], AL
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end internal
} // end classics
ENDWRAP

