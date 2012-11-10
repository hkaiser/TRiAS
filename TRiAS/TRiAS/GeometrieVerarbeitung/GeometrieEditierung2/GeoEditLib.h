// Deklarationen: Bibliothek für Erweiterung "Geometrie-Editierung"
// File: GeoEditLib.h
// W. Mörtl


#ifndef _GEOEDITLIB_H_
#define _GEOEDITLIB_H_


	void ScrollTest (HWND hWnd, WPARAM wParam);

	HRESULT IsCommonBorderAllowable (int& iGrabCnt, IEnumObjektGeometrie* pActGrabObjs,
									 IEnumObjektGeometrie* pGrabObjs, long& lComONr);

	HRESULT IsClosedLine (long lONr);
	HRESULT IsClosedLine (IObjektGeometrie* pIOG, short iOT);

	HRESULT ANDforEnumObjektGeometrie (IEnumObjektGeometrie* pEnumONr1,
									IEnumObjektGeometrie* pEnumONr2, IObjektGeometrie** ppIOG);

	Point DialogPosition (Point PLU, Point PRO, Dimension dimDlgSize);
	Point DialogPosition (IObjektGeometrie* pIOG, Dimension dimDlgSize);

	HRESULT SetObjectClassKey (IEnumObjektGeometrie* pIEnumOG, ulong& ulIdent);
	double DreieckInhalt (Point Pt, EPunkt& FirstPkt, EPunkt& LastPkt, CoordTransX* pCT);
	void FlInhaltNormieren (double dFlInhalt, string& sOutBuff);
	HRESULT EPunktAtCursor (LPARAM lParam, IRestrictLine* pIRL1, IRestrictLine* pIRL2,
							Point& CurPt, EPunkt& CurPkt);

	Rectangle GetDeleteRectangle (IObjektGeometrie* pIObj, ITopicalObjects* pITopObjs,
								  IRestrictCursor* pIRestrCursor, Point PtAdd);

	void RechWindowForNewObjects (LPCSTR pszCaption, POINT PT, long* plNeuObjNr, int iAnzNeuObj);
	bool TransformCoeffsDigitToReal (int iCnt, double* pdXD, double* pdYD, double* pdXR,
									 double* pdYR, double dT[2], double dM[2][2], double* pdErr);

#endif //_GEOEDITLIB_H_
