// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 03.02.2002 21:23:09 
//
// @doc
// @module ErrorCorrection.h | Declaration of the <c CErrorCorrection> class

#if !defined(_ERRORCORRECTION_H__3CC01AFA_2A63_4604_9C94_720C9B09ACFF__INCLUDED_)
#define _ERRORCORRECTION_H__3CC01AFA_2A63_4604_9C94_720C9B09ACFF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry  {

///////////////////////////////////////////////////////////////////////////////
// Routinen zur automatischen Geometrie-Fehler-Korrektur
template <typename KoOrdT>
void DblPointCorrection (WMObjekt<KoOrdT> *pEO, int iKInd, long lPInd, 
	double dSpEps);

template <typename KoOrdT>
void CollinearCorrection (WMObjekt<KoOrdT> *pEO, int iKInd, long lPInd);

template <typename KoOrdT>
bool AcuteAngleCorrection (WMObjekt<KoOrdT> *pEO, int iKInd, long lPInd, 
	bool bNull, double dDPEps, WMKoordinatenPaar<double> const &dpUF, bool bMetric);

template <typename KoOrdT>
void SpecialDblRemove (WMKante<KoOrdT> *pLine, long lLen, bool bClosed, 
	long lVorInd, long lPInd, double dDPEps, WMKoordinatenPaar<double> const &dpUF, 
	bool bMetric);

template <typename KoOrdT>
void SpecialAngleRemove (WMKante<KoOrdT> *pLine, long lPInd, double dSpEps);

template <typename KoOrdT>
bool DoublePointCleaning (WMKante<KoOrdT> *pKt);

template <typename KoOrdT>
bool PartialCleaningForLines (WMKante<KoOrdT> *pKt, int i = -1);

template <typename KoOrdT>
bool ExtraTestClosedLine (WMKante<KoOrdT> *pKt, int iKaNr, bool bMetric,
	double dDPEps, double dSpEps, WMKoordinatenPaar<double> const &dpUF);

} // namespace trias_wmgeometry  

#endif // !defined(_ERRORCORRECTION_H__3CC01AFA_2A63_4604_9C94_720C9B09ACFF__INCLUDED_)
