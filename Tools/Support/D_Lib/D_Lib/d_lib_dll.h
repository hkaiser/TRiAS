#ifndef __D_LIB_DLL_H__	/* { */
#define __D_LIB_DLL_H__

/*
 * *D_Lib* Copyright 1996-1999  Anatoly Kardash, anatoly-k@geocities.com
 *
 * Permission to use, copy, modify, and distribute, this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of the
 * copyright holders be used in advertising or publicity pertaining
 * to distribution of the software with specific, written prior
 * permission, and that no fee is charged for further distribution
 * of this software, or any modifications thereof. The copyright
 * holder make no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express
 * or implied warranty.
 *
 * THE COPYRIGHT HOLDER DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA, PROFITS, QPA OR GPA,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

/* if we are under MSVC */
#ifdef _MSC_VER	/* { */

/* If the library should be DLL - uncomment this: */
#define DLL_BUILD

#ifdef DLL_BUILD	/* { */

#ifdef INSIDE_DLIB_SOURCES
#define DLIB_EXPORTED	__declspec( dllexport)
#else
#define DLIB_EXPORTED	__declspec( dllimport)
#endif

#else	/* }{ DLL_BUILD */

#define DLIB_EXPORTED

#endif	/* } DLL_BUILD */

#else	/* }{ _MSC_VER */

#define DLIB_EXPORTED

#endif	/* } _MSC_VER */

#endif	/* } __D_LIB_DLL_H__ */
