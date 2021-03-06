/*
File: PUNKTLI.CPP
realiert die Verwaltung einer Punkt-Liste.

erarbeitet : J. Benkenstein		Stand vom 21. August 1995
*/

#include "pheader.hpp"		//	prec. Header
#include "dxfimp.h"			//	Ressource-Konstanten

#include <new>				//	bad_alloc ()
#include <assert.h>			//	assert ()
#include <math.h>			//	sqrt ()

#include <float.h>		// f. DBL_MAX

#include "punktli.hpp"  	// zugeh. Header-File

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

// externe Funktionen
void yyerror (short);

// PunnktListe ---------------------------------------------------------
PunktListe :: PunktListe (void)
	    	: CListContainer ()
{
	// nothing to do
}

void PunktListe :: UserDelete (void *pObj)
{
	((Punkt *) pObj) -> ~ Punkt ();
}

PunktListe :: ~ PunktListe (void)
{
	EveryDelete ();
}

// neuen Punkt in Liste aufnehmen
Bool PunktListe :: AddPunkt (double X, double Y)
{
	PunktCreator IDT (*this);
	Punkt *pID = ContCreate (IDT, Punkt) (X, Y);
	if (pID == NULL)
	{
		yyerror (EC_NOMEMORY);
		return False;
	}
	else
		return True;
}

// neuen Punkt in Liste aufnehmen
Bool PunktListe :: AddPunkt (Punkt *pPt)
{
	PunktCreator IDT (*this);
	Punkt *pID = ContCreate (IDT, Punkt) (pPt);
	if (pID == NULL)
	{
		yyerror (EC_NOMEMORY);		
		return False;
	}
	else
		return True;
}

// True, wenn neuer 1. Punkt an das akt. Ende der Liste kopiert, sonst False
Bool PunktListe :: AddFirstPunkt (void)
{
	Bool bRet = False;		// noch nichts getan
	CRing r (*this);		// Navigator init.
	r.First ();				// 1. Punkt suchen
	if (r.Valid ()) 		// wenn g�ltig
	{
		PunktLock l (r);	// verriegeln und
		if (l) 				// Zeiger pr�fen
		{
			PunktCreator IDT (*this);   // und Punkt kopieren
			Punkt *pID = ContCreate (IDT, Punkt) (l -> X(), l -> Y());
			if (pID != NULL)
				bRet = True;
		}
	}
				
//	Fehlerauswertung
	if (bRet == False)
		yyerror (IDS_SYSERROR);

	return bRet;
}

/*
// True, wenn H�he des 1. Punktes verschieden DBL_MAX, sonst False
Bool PunktListe :: _HoehenGueltig (void)
{
	CRing r (*this);						 	// Navigator init.
	r.First ();								 	// Test am 1. Punkt
	if (r.Valid ()) 						 	// wenn vorhanden
	{
		PunktLock l (r);					  	// verriegeln und
		if (l)
			return (l -> Z () != DBL_MAX); 		// auf g�ltigen Wert testen
		else
		{
			DEX_Error (RC_DxfImport, EC_LOCKERROR);
		}
	}

	return False;							  	// Punkt ist nicht vorhanden
}
*/

// alle Punkte in Speicher ausgeben
Bool PunktListe :: OutPunkte (double *&pX, double *&pY)
{
//	pr�fe Parameter
	if (!pX || !pY)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

//  X-Y-Koordinaten ausgeben
	CRing r (*this);			 // Navigator init.
	long i = 0;

	for (r.First(); r.Valid(); i++, r.Next()) 
	{
		PunktLock l (r);
		if (l) 
		{
			pX [i] = l -> X ();
			pY [i] = l -> Y ();
		}
		else
		{
			yyerror (IDS_SYSERROR);
			return False;
		}
	}

	return True;
}

// pr�fe, ob evtl. Punktfolge doch eine m�gliche Fl�che darstellt
Bool PunktListe :: isFlaeche (void)
{
	long lCnt = Count ();
	if (lCnt < 4)
		return False;
		
	Bool bRet = True;
	CRing r (*this);			 // Navigator init.
	Punkt Pa;
	{
		r.First ();
		if (r.Valid ())
		{
			PunktLock l (r);
			if (l)
				Pa = *l;
			else
				bRet = False;
		}
		else
			bRet = False;
	}
	
	if (bRet)  		// wenn 1. Pkt. gef.
	{			
		r.Last ();
		if (r.Valid ())
		{
			PunktLock l (r);			
			if (l)
				return Pa == *l;			
		}
	}

	return False;
}

//	letzten Punkt lesen
Bool PunktListe :: GetLastPunkt (double &X, double&Y)
{
	CRing r (*this);			 // Navigator init.
	{
		r.Last ();
		if (r.Valid ())
		{
			PunktLock l (r);
			if (l)
			{
				X = l -> X ();
				Y = l -> Y ();
				return True;
			}
		}
	}

	yyerror (IDS_SYSERROR);
	return False;
}

//	1. Punkt lesen
Bool PunktListe :: GetFirstPunkt (double &X, double&Y)
{
	CRing r (*this);			 // Navigator init.
	{
		r.First ();
		if (r.Valid ())
		{
			PunktLock l (r);
			if (l)
			{
				X = l -> X ();
				Y = l -> Y ();
				return True;
			}
		}
	}

	yyerror (IDS_SYSERROR);
	return False;
}

//	f�hre Transformation auf alle Punkte der Liste durch
//	neue Liste ist explizit freizugeben
PunktListe *PunktListe :: Transform (double dXBasis, double dYBasis,
									 double dXInsert, double dYInsert,
									 double dXMasstab, double dYMasstab,
									 double dWinkel,
									 double dXOffset, double dYOffset)
{
	PunktListe *pListe = NULL;

//	pr�fe Parameter
	assert ((dXMasstab != 0) && (dYMasstab != 0));
	if ((0 == dXMasstab) || (0 == dYMasstab))
	{
		yyerror (IDS_PARAM_ERROR);
		return NULL;
	}		

	try
	{
	//	pr�fe interne Parameter
		if (Count () < 1)
		{
			yyerror (IDS_PARAM_ERROR);
			return NULL;
		}

	//	neue Liste anlegen
		pListe = new PunktListe;

	//	Variablen init.
		double dCosPhi, dSinPhi;
		if (0 != dWinkel)
		{
			double dPi = 2.0 * asin (1.0);			// Pi = 3.14...
			dCosPhi = cos (dPi * dWinkel / 180);
			dSinPhi = sin (dPi * dWinkel / 180);
		}
		else
			dCosPhi = dSinPhi = 0;

	//	akt. Koordinaten
		double dX, dY, dTemp;
		dX = dY = dTemp = 0;

	//	alle Koordinaten transformieren und in neue Liste speichern
		CRing r (*this);	
		for (r.First (); r.Valid (); r.Next ())
		{
			PunktLock l (r);
			if (l) 
			{
			//	1. Basispunkt ber�cksichtigen
				dX = l->X() - dXBasis;
				dY = l->Y() - dYBasis;

			//	2. Ma�stab ber�cksichtigen
				dX *= dXMasstab;
				dY *= dYMasstab;

			//	3. ggf. Drehwinkel ber�cksichtigen
				if (0 != dWinkel)
				{
					dX += dXOffset;
					dY += dYOffset;

					dTemp = dX;
					dX = (dX * dCosPhi) - (dY * dSinPhi);
					dY = (dTemp * dSinPhi) + (dY * dCosPhi);
				}
				else
				{
					dX += dXOffset;
					dY += dYOffset;
				}

			//	4. Verschiebung ber�cksichtigen
				dX += dXInsert;
				dY += dYInsert;

			//	Punkt in neue Liste ausgeben
				if (!pListe->AddPunkt (dX, dY))
				{
					DELETE_OBJ (pListe);
					return NULL;
				}
			}
			else
			{
				yyerror (IDS_SYSERROR);
				DELETE_OBJ (pListe);
				return NULL;
			}
		}
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
		DELETE_OBJ (pListe);
	}

	return pListe;
}

Bool PunktListe :: operator += (PunktListe& Liste)
{
//	pr�fe Parameter
	assert (&Liste != this);
	if (&Liste == this)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}			

//	pr�fe Anzahl Eintr�ge
	if (Liste.Count () < 1)
		return True;

//	Eintr�ge umkopieren
	CRing r (Liste);		
	for (r.First(); r.Valid(); r.Next()) 
	{
		PunktLock l (r);
		if (l) 
		{
			if (!AddPunkt (l -> X (), l -> Y ()))
				return False;
		}
		else
		{
			yyerror (IDS_SYSERROR);
			return False;
		}
	}

	return True;
}

Bool PunktListe :: operator = (PunktListe& Liste)
{
//	pr�fe Parameter
	assert (&Liste != this);
	if (&Liste == this)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}			

//	alle Eintr�ge l�schen
	EveryDelete ();

	return operator += (Liste);
}

