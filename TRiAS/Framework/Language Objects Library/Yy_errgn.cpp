
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_errmf.cpp
//
//  FILE DESCRIPTION:     generic error object support 
//
//
//  MODIFICATION HISTORY:
//
//    04/09/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"

#ifndef yy_errgn_c_
#define yy_errgn_c_ 1
#endif /* yy_errgn_c_ */

#include <bool.h>
#include <tstring>

#pragma warning (disable: 4251)		// string needs __dll-interface
#include "yy_errgn.h"
#include "yy_asrt.h"
#include "yy_strng.h"

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_proc_obj::yy_err_proc_obj(...)
//
//  This is the constructor for the generic error object whose parameter 
//  list corresponds to the fields in the TriasFramework error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_proc_obj::yy_err_proc_obj(
	yy_err_procedure    yy_new_err_proc,	
        yy_errmsg_dflt_ptr  yy_new_err_tbl,
        int                 yy_new_err_tbl_max,
        yy_synamsg_dflt_ptr yy_new_syna_tbl,
        int                 yy_new_syna_tbl_max
    ) :
    yy_err_gen_obj(
        yy_new_err_tbl, 
        yy_new_err_tbl_max,
        yy_new_syna_tbl,
        yy_new_syna_tbl_max
        ),
    yy_err_proc (yy_new_err_proc),
	yy_out_string("")
{
}   // constructor for yy_err_proc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_proc_obj::~yy_err_proc_obj()
//
//  This is the destructor for the procedural error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_proc_obj::~yy_err_proc_obj()
{
}  // destructor for yy_err_proc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() converts newlines or carriage returns to carriage
//  return/line feed pairs and then displays a string onto the error window.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_proc_obj::yy_err_puts(
    const char *yy_text)
{
int     newlines_to_convert, newlines_converted;
size_t  i, orig_len;
char    *converted_text;

#if defined(_NODEBUG)
    if (yy_err_proc == NULL) {
        return(0);
    }
#endif // _NODEBUG

//  count the number of carriage return/newline conversions needed, if any

    orig_len = strlen(yy_text);
    newlines_to_convert = 0;

    for (i = 0; i < orig_len; ++i) {

        if (yy_text[i] == '\n') {  // change LF to CR/LF
            ++newlines_to_convert;
            }
        else if ((yy_text[i] == '\r') & (yy_text[i+1] != '\n')) {
                                   // change CR to CR/LF
            ++newlines_to_convert;
            }
        else if ((yy_text[i] == '\r') & (yy_text[i+1] == '\n')) { 
                                   // copy CR/LF to CR/LF
            ++i;                   // skip checking the next character
            // no need to convert
            }

        }  // for loop on original text

//  if there are conversions to do before doing a Windows display, change
//  newlines or carriage returns into pairs of carriage return/line feeds.

    if (newlines_to_convert != 0) {

        converted_text = new char[orig_len + newlines_to_convert + 1];

        if (converted_text == NULL) {  // new() failure
            yy_err_report(406);
            yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
            return(0);
            }

        newlines_converted = 0;

        for (i = 0; i < orig_len; ++i) {
            if (yy_text[i] == '\n') {  // change LF to CR/LF
                converted_text[i+newlines_converted] = '\r';
                ++newlines_converted;
                converted_text[i+newlines_converted] = '\n';
                }
            else if ((yy_text[i] == '\r') & (yy_text[i+1] != '\n')) {
                                       // change CR to CR/LF
                converted_text[i+newlines_converted] = '\r';
                ++newlines_converted;
                converted_text[i+newlines_converted] = '\n';
                }
            else if ((yy_text[i] == '\r') & (yy_text[i+1] == '\n')) { 
                                       // copy CR/LF to CR/LF
                 converted_text[i+newlines_converted] = '\r';
                 ++i;
                 converted_text[i+newlines_converted] = '\n';
                 }
            else {                    // just copy any other character
                 converted_text[i+newlines_converted] = yy_text[i];
                 }

            }  // for loop on original text

        converted_text[i+newlines_converted] = '\0';

        assert(newlines_converted == newlines_to_convert);

		if (yy_err_proc) {
			if (converted_text[0] == '\r' || converted_text[0] == '\n') {
				yy_err_proc (yy_out_string.c_str());
				yy_out_string = "";
			} else
				yy_out_string += converted_text;
		} else {
#if defined(_DEBUG)
		OutputDebugString (converted_text);
#endif // _DEBUG
		}
        delete [] converted_text;
	}
    else {
	// otherwise, just insert the original text into the error message window
    	if (yy_err_proc) {
			if (yy_text[0] == '\r' || yy_text[0] == '\n') {
				yy_err_proc (yy_out_string.c_str());
				yy_out_string = "";
			} else
				yy_out_string += yy_text;
		} else {
#if defined(_DEBUG)
		OutputDebugString (yy_text);
#endif // _DEBUG
		}
    }

return 1;
}   // yy_err_puts
