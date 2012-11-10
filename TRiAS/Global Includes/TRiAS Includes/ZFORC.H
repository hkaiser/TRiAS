/* Anpassung der MS/DOS Fortran-Schnittstelle an 'C'		*/
/* File: ZFORC.H						*/

#ifdef sccs
static char SccsId[] = "ZIPEDB: %W%	%E%";
#endif

#ifndef _ZFORC_H
#define _ZFORC_H

#if !defined(__cplusplus)
extern "C" {
#endif 

#define ABS(v)	( (v) < 0 ? -(v) : (v) )
#define ADR(s,v)	((s)=(v),&s)
#define sign(a)		(((a)<0)?(-1):(+1))
#define ARITHIF(x)	(f_d_=(x),(f_d_ > 0. ? 1 : (f_d_ < 0. ? -1 : 0)) )
#define IARITHIF(x) 	(f_l_=(x),(f_l_ > 0 ? 1 : (f_l_ < 0 ? -1 : 0)))
#define DOCNT(i,t,n)	(_d_l=(n), (_d_m=(t-(i)+_d_l)/_d_l) > 0 ? _d_m : 0L )
#define ssign(a,b)	(short)( (b) < 0 ? -ABS(a) : ABS(a) )
#define isign(a,b)	(long)( (b) < 0 ? -ABS(a) : ABS(a) )

// Prototypen -----------------------------------------------------------------
#include <protos.h>
//#include <zprotos.h>

// DB- Funktionen -------------------------------------------------------------
#define zopen 	zopen_
#define zclose 	zclose_
#define zact 	zact_

// Datenbehandlung ------------------------------------------------------------
#define zread 	zread_
#define zwrite 	zwrite_
#define znew 	znew_
#define zdisp 	zdisp_

// Schlüsselfunktionen --------------------------------------------------------
#define zfind 	zfind_
#define zfirst 	zfirst_
#define zlast 	zlast_
#define znext 	znext_
#define zprev 	zprev_
#define zkread 	zkread_
#define htwind	htwind_
#define qtwind	qtwind_

// Inzidenztest ---------------------------------------------------------------
#define ngmini 	ngmini_
#define ngmc 	ngmc_

// sonstiges ------------------------------------------------------------------
#define puttxt	puttxt_
#define gettxt	gettxt_
#define puthd	puthd_
#define gethd	gethd_
#define lnblnk	lnblnk_
#define cblank	cblank_
#define ishft	ishft_
#define tlower	tlower_
#define tupper	tupper_
#define lowerc	lowerc_
#define fdate	fdate_
#define ladr	ladr_

// Fehlerbehandlung -----------------------------------------------------------
#define seterr	seterr_
#define errfkt	errfkt_

// Dynamische Felder ----------------------------------------------------------
#define feini	feini_
#define ferel	ferel_
#define feread	feread_
#define fewrit	fewrit_
#define feput	feput_
#define feget	feget_
#define felen	felen_
#define flqsrt	flqsrt_
#define flredn	flredn_

#if !defined(__cplusplus)
}
#endif 

#endif	// _ZFORC_H
