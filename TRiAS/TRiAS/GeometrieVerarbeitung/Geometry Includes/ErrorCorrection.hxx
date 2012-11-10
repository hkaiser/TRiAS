// Bereinigung von Geometriefehlern
// File: ErrorCorrection.hxx
// W. Mörtl


#ifndef _ERRORCORRECTION_HXX
#define _ERRORCORRECTION_HXX


_GEOMETR_ENTRY void DblPointCorrection (EObjekt* pEO, int iKInd, long lPInd, double dSpEps);
_GEOMETR_ENTRY void CollinearCorrection (EObjekt* pEO, int iKInd, long lPInd);
_GEOMETR_ENTRY bool AcuteAngleCorrection (EObjekt* pEO, int iKInd, long lPInd, bool bNull,
										  double dDPEps, DoublePair dpUF, bool bMetric);
void SpecialDblRemove (EKante* pLine, long lLen, bool bClosed, long lVorInd, long lPInd,
					   double dDPEps, DoublePair dpUF, bool bMetric);
void SpecialAngleRemove (EKante* pLine, long lPInd, double dSpEps);
_GEOMETR_ENTRY bool DoublePointCleaning (EKante* pKt);
_GEOMETR_ENTRY bool PartialCleaningForLines (EKante* pKt, short i = -1);
bool ExtraTestClosedLine (EKante* pKt, int iKaNr, CoordTransX* pCT, bool bMetric,
						  double dDPEps, double dSpEps, DoublePair dpUF);
_GEOMETR_ENTRY bool SeparateEndLoop (EKante* pKt, KoOrd lTX, KoOrd lTY, long lPInd, EKante* pLoopKt);


#endif // _ERRORCORRECTION_HXX
