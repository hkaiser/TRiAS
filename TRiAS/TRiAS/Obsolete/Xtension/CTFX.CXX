// Memberfunktionen fuer die Schnittstelle zu den Koordinaten-
// Transformations-DLL's (Extension)
// File: CTFX.CXX

#include "xtensnp.hxx"

#include <resstrg.h>
#include <dllbindx.hxx>
#include <objcontx.hxx>
#include <dblpair.hxx>
#include <ctfx.hxx>
#include <hdrentrx.hxx>

ErrCode EvalKoeffs (double *, double *, double *, double *);

// lokale Fehlerbehandlungsroutine --------------------------------------------
static inline ErrCode loc_db_error (int EC, int RC)
{
ErrCode locRC;

	DEXN_ErrorMessage (locRC, EC, RC, NULL);

return locRC;
}

// Konstruktor/Destruktor -----------------------------------------------------
CoordTransX :: CoordTransX (void)
{
HeaderEntryX HE (IDS_CTFHEADER);

	_pDLL = NULL;	// für alle Fälle NULL setzen

	if (HE.Status() != HE_INVALID) {
	char CTName[_MAX_FNAME];

		strcpy (CTName, HE.EntryText());
		strcat (CTName, ResString (IDS_CTFEXT, 5));
		_pDLL = new CDllBindX (CTName);
		if (_pDLL == NULL) {
			loc_db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
	} 
	if (_pDLL == NULL || _pDLL -> hLib() == 0) {	// Objekt ungültig
		DELETE (_pDLL);
		_pDLL = new CDllBindX (ResString (IDS_CTFDEFAULT, 13));
		if (_pDLL == NULL) {
			loc_db_error (EC_NOMEMORY, RC_ctCTF);
			return;
		}
	}

// SkalierungsKoeffizienten lesen
	{
	// Koeffizienten aus DB-Header lesen
		iK11 = K11 = HeaderEntryX (IDS_KOEFF11).EntryDouble(1.0);
		iK12 = K12 = HeaderEntryX (IDS_KOEFF12).EntryDouble(0.0);
		iK21 = K21 = HeaderEntryX (IDS_KOEFF21).EntryDouble(0.0);
		iK22 = K22 = HeaderEntryX (IDS_KOEFF22).EntryDouble(1.0);
		OX = HeaderEntryX (IDS_OFFSETX).EntryDouble(0.0);
		OY = HeaderEntryX (IDS_OFFSETY).EntryDouble(0.0);
	}

// Koeffizienten Matrix invertieren
	if (EvalKoeffs (&iK11, &iK12, &iK21, &iK22) != EC_OKAY)
		return;	// entartete TMatrix

// für Hin- und Rücktransformation Funktionen binden
	CTFTransFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFTRANSFORM, 30));
	CTFInvTransFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFINVTRANSFORM, 30));

// DLL informieren, daß sie aktiviert ist, FensterHandle mitteilen
	CoordTransLoad (pTE -> hWnd());

// überprüfen, ob CTF Config-Mode besitzt
	m_fConfig = (NULL != GetProcAddress (ResString (IDS_CTFMODE, 30)));
}

CoordTransX :: ~CoordTransX (void)
{
// DLL informieren, das jetzt alles vorbei ist
	CoordTransUnLoad();

// DLL freigeben
	DELETE (_pDLL);
}

// Funktionen, die nicht auf die CTF-DLL durchgreifen -------------------------
BOOL CoordTransX :: Scale (const double &pX, const double &pY, Punkt &outPt)
{
double tX = pX - OX;
double tY = pY - OY;

	outPt.X() = (KoOrd)(iK11 * tX + iK12 * tY);
	outPt.Y() = (KoOrd)(iK21 * tX + iK22 * tY);
	
return TRUE;
}

BOOL CoordTransX :: Scale (const double &X, const double &Y, 
			   KoOrd *pX, KoOrd *pY)
{
double tX = X - OX;
double tY = Y - OY;

	*pX = (KoOrd)(iK11 * tX + iK12 * tY);
	*pY = (KoOrd)(iK21 * tX + iK22 * tY);
	
return TRUE;
}

BOOL CoordTransX :: UnScale (const Punkt &Pt, double *pX, double *pY)
{
	*pX = K11 * (double)((Punkt &)Pt).X() + K12 * (double)((Punkt &)Pt).Y() + OX;
	*pY = K21 * (double)((Punkt &)Pt).X() + K22 * (double)((Punkt &)Pt).Y() + OY;
	
return TRUE;
}

BOOL CoordTransX :: UnScale (const KoOrd &inX, const KoOrd &inY, 
			     double *pX, double *pY)
{
	*pX = K11 * (double)inX + K12 * (double)inY + OX;
	*pY = K21 * (double)inX + K22 * (double)inY + OY;
	
return TRUE;
}


// Funktionen, die auf die CTF-DLL durchgreifen -------------------------------
double CoordTransX :: CoordTransAspectRatio (ObjContainer &OC)
{
CTFASPECTPROC CTFAspectFunc = (CTFASPECTPROC)GetProcAddress (ResString (IDS_CTFASPECT, 30));

	if (CTFAspectFunc) {
	// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	double XOut = (long)(K11 * (double)OC.XMin() + K12 * (double)OC.YMax() + OX);
	double YOut = (long)(K21 * (double)OC.XMin() + K22 * (double)OC.YMax() + OY);
	DoublePair LO (XOut, YOut);

		XOut = (long)(K11 * (double)OC.XMax() + K12 * (double)OC.YMin() + OX);
		YOut = (long)(K21 * (double)OC.XMax() + K22 * (double)OC.YMin() + OY);

	DoublePair RU (XOut, YOut);

	// DLL-Funktion rufen
		return (*CTFAspectFunc)(&LO, &RU);
	}
	loc_db_error (EC_NODLLFUNCTION, RC_CTFAspect);

return 1.0;
}

double CoordTransX :: CoordTransDistance (const DoublePair *pP1, const DoublePair *pP2)
{
CTFDISTANCEPROC CTFDistanceFunc = (CTFDISTANCEPROC)GetProcAddress (ResString (IDS_CTFDISTANCE, 30));

	if (CTFDistanceFunc) {
	// DLL-Funktion rufen

		return (*CTFDistanceFunc)(pP1, pP2);
	}
	loc_db_error (EC_NODLLFUNCTION, RC_CTFDistance);

return 0.0;
}

BOOL CoordTransX :: Transform (double *pX, double *pY)
{
	if (CTFTransFunc) {
	DoublePair DP (*pX, *pY);

		if ((*CTFTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		}
	} else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
	
return FALSE;
}

BOOL CoordTransX :: Transform (DoublePair *pPoints, short iNum)
{
	if (CTFTransFunc) // DLL-Funktion rufen
		return (*CTFTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFTrans);
		
return FALSE;
}

BOOL CoordTransX :: InvTransform (double *pX, double *pY)
{
	if (CTFInvTransFunc) {
	// DLL-Funktion rufen
	DoublePair DP (*pX, *pY);

		if ((*CTFInvTransFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		}
	} else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
		
return FALSE;
}

BOOL CoordTransX :: InvTransform (DoublePair *pPoints, short iNum)
{
	if (CTFInvTransFunc) // DLL-Funktion rufen
		return (*CTFInvTransFunc)(pPoints, iNum);
	else 		  // Fehlermeldung
		loc_db_error (EC_NODLLFUNCTION, RC_CTFInvTrans);
		
return FALSE;
}

char *CoordTransX :: CoordTransDescription (char *, short)
{
	return NULL;
}

Bool CoordTransX :: CoordTransMode (pWindow pW)
{
CTFMODEPROC CTFHandlingFunc = (CTFMODEPROC)GetProcAddress (ResString (IDS_CTFMODE, 30));

	if (CTFHandlingFunc) {	// DLL Funktion rufen
	COORDTRANSMODE CTM;

		CTM.dwSize = sizeof(COORDTRANSMODE);
		CTM.hWnd = pW -> Handle (API_WINDOW_HWND);

		return (*CTFHandlingFunc)(&CTM);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return false;
}

Bool CoordTransX :: CoordTransLoad (HWND hWnd)
{
CTFLOADPROC CTFHandlingFunc = (CTFLOADPROC)GetProcAddress (ResString (IDS_CTFLOAD, 30));

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)(hWnd);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFLoad);

return FALSE;
}

Bool CoordTransX :: CoordTransUnLoad (void)
{
CTFUNLOADPROC CTFHandlingFunc = (CTFUNLOADPROC)GetProcAddress (ResString (IDS_CTFUNLOAD, 30));

	if (CTFHandlingFunc) {
	// DLL Funktion rufen

		return (*CTFHandlingFunc)();
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFUnLoad);

return FALSE;
}

char *CoordTransX :: CoordTransToString (double Value, 
					 BOOL isX,
					 char *pBuffer, 
					 short iLen)
{
CTFTOSTRINGPROC CTFFunc = (CTFTOSTRINGPROC)GetProcAddress (ResString (IDS_CTFTOSTRING, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		return (*CTFFunc)(Value, isX, pBuffer, iLen);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFToString);

return NULL;
}

double CoordTransX :: CoordTransToValue (char *pBuffer)
{
CTFTOVALUEPROC CTFFunc = (CTFTOVALUEPROC)GetProcAddress (ResString (IDS_CTFTOVALUE, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		return (*CTFFunc)(pBuffer);
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFToValue);

return NULL;
}

char * CoordTransX :: CoordTransToStringEx (double dX, double dY,
						    bool isX, char *pBuffer, 
						    short iLen)
{
CTFTOSTRINGEXPROC CTFFunc = (CTFTOSTRINGEXPROC)GetProcAddress (ResString (IDS_CTFTOSTRINGEX, 30));

	if (CTFFunc) {
	// DLL Funktion rufen
	DoublePair DP(dX, dY);

		if ((*CTFFunc)(pBuffer, iLen, isX, &DP))
			return pBuffer;
		else
			return NULL;
	} else {
		if (isX) 
			return CoordTransToString (dX, true, pBuffer, iLen);
		else
			return CoordTransToString (dY, false, pBuffer, iLen);
	}			
}

bool CoordTransX :: CoordTransToValueEx (const char *pBuffX, const char *pBuffY,
						 double &dX, double &dY)
{
CTFTOVALUEEXPROC CTFFunc = (CTFTOVALUEEXPROC)GetProcAddress (ResString (IDS_CTFTOVALUEEX, 30));

	if (CTFFunc) {
	// DLL Funktion rufen
	DoublePair DP;
	
		if ((*CTFFunc)(&DP, pBuffX, pBuffY)) {
			dX = DP.Width();
			dY = DP.Height();
			return true;
		} else
			return false;
	} else {
		dX = CoordTransToValue ((char *)pBuffX);
		dY = CoordTransToValue ((char *)pBuffY);
		return true;
	}
}

BOOL CoordTransX :: CoordTransRectangle (const DoublePair *pIn, 
					 const DoublePair *pDelta, 
					 DoublePair *pOut)
{
CTFRECTPROC CTFFunc = (CTFRECTPROC)GetProcAddress (ResString (IDS_CTFRECTANGLE, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		return (*CTFFunc)(pIn, pDelta, pOut);
	} else
		loc_db_error (EC_NODLLFUNCTION, RC_CTFRectangle);
		
return FALSE;
}


// Inverse Matrix für Koordinatentransformation berechnen ---------------------
ErrCode EvalKoeffs (double *k11, double *k12, double *k21, double *k22) 
{
double DetA = *k11 * *k22 - *k12 * *k21;

	if (DetA != 0.0) {
	double temp = *k11;

		*k11 = *k22/DetA;
		*k22 = temp/DetA;
		*k12 = -(*k12/DetA);
		*k21 = -(*k21/DetA);
		return EC_OKAY;
	} else {
		return (ErrCode)loc_db_error (EC_BadKoeffs, RC_MatrixEvalKoeffs);
	}
}


// Funktionen, die Koordinaten in metrische Einheiten konvertieren ------------
BOOL CoordTransX :: isMetric (void)
{
CTFISMETRICPROC CTFFunc = (CTFISMETRICPROC)GetProcAddress (ResString (IDS_CTFISMETRIC, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		return (*CTFFunc)();
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFisMetric);

return TRUE;	// metrisch annehmen
}

BOOL CoordTransX :: Native (const double &pX, const double &pY, Punkt &outPt)
{
CTFTRANSPROC CTFFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFNATIVE, 30));

	if (CTFFunc) {
	// DLL Funktion rufen
	DoublePair DP (pX, pY);

		if ((*CTFFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), outPt);
		else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return FALSE;	// Fehler
}

BOOL CoordTransX :: Native (const double &X, const double &Y, 
			   KoOrd *pX, KoOrd *pY)
{
CTFTRANSPROC CTFFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFNATIVE, 30));

	if (CTFFunc) {
	// DLL Funktion rufen
	DoublePair DP (X, Y);

		if ((*CTFFunc)(&DP, 1)) 
			return Scale (DP.X(), DP.Y(), pX, pY);
		else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFNative);

return FALSE;	// Fehler
}

BOOL CoordTransX :: Metric (const Punkt &Pt, double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (Pt, &DP.X(), &DP.Y())) return FALSE;

CTFTRANSPROC CTFFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFMETRIC, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		if ((*CTFFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		} else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return FALSE;	// Fehler
}

BOOL CoordTransX :: Metric (const KoOrd &inX, const KoOrd &inY, 
			   double *pX, double *pY)
{
DoublePair DP;

	if (!UnScale (inX, inY, &DP.X(), &DP.Y())) return FALSE;

CTFTRANSPROC CTFFunc = (CTFTRANSPROC)GetProcAddress (ResString (IDS_CTFMETRIC, 30));

	if (CTFFunc) {
	// DLL Funktion rufen

		if ((*CTFFunc)(&DP, 1)) {
			*pX = DP.X();
			*pY = DP.Y();
			return TRUE;
		} else
			return FALSE;
	} 
	loc_db_error (EC_NODLLFUNCTION, RC_CTFMetric);

return FALSE;	// Fehler
}


