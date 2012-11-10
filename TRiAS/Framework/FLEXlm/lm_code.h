/******************************************************************************

  	Module: $Id: blank_lm_code.h,v 1.2 2000/05/16 20:51:58 daniel Exp $

	    COPYRIGHT (c) 1990, 2000 by Globetrotter Software Inc.
	This software has been provided pursuant to a License Agreement
	containing restrictions on its use.  This software contains
	valuable trade secrets and proprietary information of 
	Globetrotter Software Inc and is protected by law.  It may 
	not be copied or distributed in any form or medium, disclosed 
	to third parties, reverse engineered or used in any manner not 
	provided for in said License Agreement except with the prior 
	written authorization from Globetrotter Software Inc.

 *****************************************************************************/
/*	
 *
 *	Description: 	Used to generate lm_new.o/.obj and by license-
 *			generators.
 *			
 *			Once the kit is "built" (using make or nmake)
 *			this file is no longer needed, but should be
 *			stored somewhere safe.
 *	
 *			Set the following values:
 *			LM_STRENGTH 	
 *				If using public-key, set to desired length
 *			ENCRYPTION_SEED1-4
 *				Make up 4 32-bit numbers, keep secret, safe, 
 *				and never change.
 *			VENDOR_NAME
 *				If not evaluating, set to vendor name.
 *			VENDOR_KEY1-5
 *				Provided by Globetrotter.
 *			
 */

#ifndef LM_CODE_H
#define LM_CODE_H
#include "lm_cro.h"

/*
 *	Pick an LM_STRENGTH.  
 *
 *		If you're not using CRO public-key, then leave this as 
 *		LM_STRENGTH_DEFAULT.
 *		If you're upgrading from pre-v7.1, and want no changes, 
 *	 	set this to LM_STRENGTH_LICENSE_KEY.
 */

#define LM_STRENGTH LM_STRENGTH_DEFAULT

/* 
 * LM_STRENGTH Options are
 * 	LM_STRENGTH_DEFAULT		Public key protection unused
 *					Use SIGN= attribute
 *					sign length = 12
 * Public key:
 *	 LM_STRENGTH_113BIT, LOW	sign length = 58 chars
 *	 LM_STRENGTH_163BIT, MEDIUM 	sign length = 84 chars
 *	 LM_STRENGTH_239BIT, HIGH	sign length = 120 chars
 *
 * Use pre-v7.1, non-CRO
 *	 LM_STRENGTH_LICENSE_KEY   	Use pre-v7.1 license-keys.
 *				   	Doesn't use SIGN= attribute.
 */

/*
 *	Vendor's private seeds, -- replace with 32-bit numbers that
 *				   you make up.
 */

//#define ENCRYPTION_SEED1 0x87654321 
//#define ENCRYPTION_SEED2 0x12345678
	
//#define ENCRYPTION_SEED3 0x11223344 /* only used if LM_CRO_STRENGTH is *BIT */
//#define ENCRYPTION_SEED4 0x55667788 /* only used if LM_CRO_STRENGTH > 2 */

#define ENCRYPTION_SEED1 0x07685353
#define ENCRYPTION_SEED2 0x05791992

#define ENCRYPTION_SEED3 0x03321767 /* only used if LM_CRO_STRENGTH is *BIT */
#define ENCRYPTION_SEED4 0x10609769 /* only used if LM_CRO_STRENGTH > 2 */

/*
 *	FLEXlm vendor keys -- enter as received from Globetrotter.
 *	Changing these keys has NO impact on license files (unlike 
 *	the ENCRYPTION_SEEDs).
 */
/*-
 *	Generate these keys with: lmvkey -v demo -d (+3 months) -p ALL -c DEMO
 *		(Use a date approx 3 months out)
 */
 
 
#define VENDOR_KEY1 0xfb165afe
#define VENDOR_KEY2 0xdadd87d1
#define VENDOR_KEY3 0x70b5ba2d
#define VENDOR_KEY4 0x821396c6
#define VENDOR_KEY5 0x711af0d2

#define CRO_KEY1 0x0 /* Used to enable CRO -- turned off by default */
#define CRO_KEY2 0x0 /* Be sure to reset LM_STRENGTH above if 
			CRO_KEY is non-zero */

/*
 *	FLEXlm vendor name.  Leave as "demo" if evaluating FLEXlm.  Otherwise
 *			     set to your vendor daemon name.
 */

#define VENDOR_NAME "TRIAS"


/*
 *	Older customers with newer versions may want to set
 *	behavior defaults to previous version, though this is usually
 *	discouraged.  Behaviors can be changed individually using
 *	LM_A_xxx in the flexible API.  New customers should use the 
 *	current default, as set below
 *	
 *	Valid settings include:
 *		LM_BEHAVIOR_V2, _V3, _V4, _V5, _V5_1, _V6, _V7, _V7_1
 */

#define LM_VER_BEHAVIOR LM_BEHAVIOR_V7_1
//#define LM_VER_BEHAVIOR LM_BEHAVIOR_V7

#endif /* LM_CODE_H */
