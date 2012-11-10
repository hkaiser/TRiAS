
/*
   L_OCRERR.h - LEAD OCR Errors header file
   Copyright (c) 1991-2001 by LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTOCR_ERR_H_
#define _LTOCR_ERR_H_

#include "ltsys.h"

/* The following are OCR ScanSoft error */
#define OCR_SUCCESS                          1   /* Operation completed successfully                                    */
#define OCR_SUCCESS_PRINTEDHIGHLIGHTS        2   /* Operation completed successfully and highlighters were printed      */
#define OCR_SUCCESS_NOTENOUGHINFO            3   /* There operation did not need to be performed                        */
#define OCR_SUCCESS_ENDOFLIST                4   /* The end of a list has been reached                                  */
#define OCR_SUCCESS_NOOP                     5   /* Operation was determined to be a no-op                              */

#define OCR_SUCCESS_MAX                      5   /* Last possible success return code                                   */

#define OCR_WARNING                          6   /* Operation completed but some portion was skipped                    */
#define OCR_WARNING_CODEPAGEUSED             7   /* The specified language can not be found on the system               */
#define OCR_WARNING_CANTSPLITPAGE            8   /* A split line could not be determined for the page                   */

#define OCR_FAILURE                          0   /* Function not successful                                             */

#define OCR_ERROR_BADPARAM                   -1 /* A bad parameter was encountered                                      */
#define OCR_ERROR_BADSEQUENCE                -2 /* Some other processing is required before calling this routine        */
#define OCR_ERROR_BADSEGMENTNUMBER           -3 /* The segment number is invalid                                        */

#define OCR_ERROR_INTERNALERROR              -4 /* An internal error occurred                                           */
#define OCR_ERROR_UNKNOWNERROR               -5 /* An unknown error occurred                                            */
#define OCR_ERROR_CANCEL                     -6 /* The operation was aborted because of user cancel                     */
#define OCR_ERROR_SELFCANCEL                 -7 /* The OCR engine or other internal process canceled itself             */
#define OCR_ERROR_NOLICENSE                  -8 /* Caller does not have a license for the requested functionality       */
#define OCR_ERROR_BUFFEROVERFLOW             -9 /* Given data was too large for internal buffers                        */

#define OCR_ERROR_BADLANG                    -10 /* The specified language is invalid                                   */
#define OCR_ERROR_ACCESSDENIED               -11 /* Client is not authorized to perform this action                     */
#define OCR_ERROR_SEGMENT_MISMATCH           -12 /* Invalid segment type                                                */
#define OCR_ERROR_NOVERIFIER                 -13 /* No client verification callback set                                 */
#define OCR_ERROR_NOTEXTPLANE                -14 /* There is no text plane in this image                                */
#define OCR_ERROR_BADPAGETYPE                -15 /* Operation not valid for this type of page                           */

#define OCR_ERROR_BADSEGINFO                 -16 /* Invalid segment information was encountered                         */
#define OCR_ERROR_BADIMGSEGINFO              -17 /* Invalid image segment information was encountered                   */
#define OCR_ERROR_UNMAPPEDOCRERROR           -18 /* Unmapped OCR error                                                  */
#define OCR_ERROR_APICONFIGERROR             -19 /* Some file or registry not set up properly                           */
#define OCR_ERROR_BADPAGEITEM                -20 /* An page item or usage was requested that does not exist             */
#define OCR_ERROR_TOOMANYRESOLUTIONS         -21 /* Too many resolution changes in a document                           */
#define OCR_ERROR_OCR_FATAL                  -22 /* An unrecoverable error has occurred in OCR                          */
#define OCR_ERROR_UNSUPPORTEDCODEPAGE        -23 /* An unsupported code page was used                                   */

#define OCR_ERROR_NO_MEMORY                  -24 /* An out of memory condition occurred                                 */
#define OCR_ERROR_DLL_NOT_LOADED             -25 /* ScanSoft DLLs are not loaded                                        */
#define OCR_ERROR_INV_HANDLE                 -26 /* Invalid OCR handle                                                  */
#define OCR_ERROR_INV_PAGE                   -27 /* There is no loaded page to OCR engine                               */
#define OCR_ERROR_INV_PAGE_INDEX             -28 /* The specified page doesn't exist                                    */
#define OCR_ERROR_INV_SEGMENT_FLAGS          -29 /* The segment flags that passed are invalid                           */
#define OCR_ERROR_NO_HIT_POINT               -30 /* The specified point doesn't hit any segment                         */
#define OCR_ERROR_INV_PARAMETER              -31 /* Invalid parameter passed                                            */
#define OCR_ERROR_NO_BITMAP                  -32 /* Invalid bitmap handle                                               */
#define OCR_ERROR_ADD_PAGE_FAILED            -33 /* Failure while trying to load bitmap(s) into OCR engine              */
#define OCR_ERROR_EXPORT_PAGE_FAILED         -34 /* Failure while trying to load page(s) from OCR engine into bitmap(s) */
#define OCR_ERROR_EXPORT_SEGMENT_FAILED      -35 /* Failure while trying to load segment from OCR engine into bitmap    */
#define OCR_ERROR_SET_TRAINING_FILE          -36 /* Can't set the passed file name as a training file                   */
#define OCR_EEROR_LOAD_TRAINING_FILE         -37 /* Can't load the specified training file                              */
#define OCR_ERROR_WRITE_TRAINING_FILE        -38 /* Error writing to a training file                                    */
#define OCR_ERROR_GET_NEXT_ALTWORD           -39 /* Error getting alternate spelling word                               */
#define OCR_ERROR_INV_CALLBACK_USAGE         -40 /* Invalid callback usage                                              */
#define OCR_ERROR_DLG_FAILED                 -41 /* An error occurred during creation of the verification dialog        */
#define OCR_ERROR_DLG_CANCELED               -42 /* The verification dialog was canceled by user                        */
#define OCR_ERROR_DLG_INV_STRING             -43 /* The length of passed string exceeds the maximum string limit        */
#define OCR_ERROR_LOCKED                     -44 /* The OCR toolkit is locked                                           */

#endif //_LTOCR_ERR_H_
