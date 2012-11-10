
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_errmf.cpp
//
//  FILE DESCRIPTION:     error object support for MFC
//                        (for Microsoft C++ compiler -- Microsoft Foundation
//                         Classes Library)
//
//  MODIFICATION HISTORY:
//
//    04/09/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_errmf_c_
#define yy_errmf_c_ 1
#endif /* yy_errmf_c_ */

#include "yy_errmf.h"
#include "yy_asrt.h"
#include "yy_strng.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_mfc_obj::yy_err_mfc_obj(...)
//
//  This is the constructor for the MFC error object whose parameter 
//  list corresponds to the fields in the MFC error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_mfc_obj::yy_err_mfc_obj(
        CEdit               *yy_new_err_window,
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
    yy_err_window(yy_new_err_window)
{
}   // constructor for yy_err_mfc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_mfc_obj::~yy_err_mfc_obj()
//
//  This is the destructor for the MFC error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_mfc_obj::~yy_err_mfc_obj()
{
}  // destructor for yy_err_mfc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() converts newlines or carriage returns to carriage
//  return/line feed pairs and then displays a string onto the error window.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_mfc_obj::yy_err_puts(
    const char *yy_text)
{
    int     newlines_to_convert, newlines_converted;
    size_t  i, orig_len;
    int     window_text_length;
    char    *converted_text;

    if (yy_err_window == NULL) {
        return(0);
        }

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

        window_text_length = yy_err_window -> GetWindowTextLength();
        yy_err_window -> SetSel(window_text_length, window_text_length, TRUE);
        yy_err_window -> ReplaceSel(converted_text);

        delete [] converted_text;
        }

//  otherwise, just insert the original text into the error message window

    else {
        window_text_length = yy_err_window -> GetWindowTextLength();
        yy_err_window -> SetSel(window_text_length, window_text_length, TRUE);
        yy_err_window -> ReplaceSel((char *) yy_text);
        }

//  popup the error message window
 
    yy_err_window -> ShowWindow(SW_SHOWNORMAL);
    yy_err_window -> SetFocus();

    return(1);

}   // yy_err_puts
