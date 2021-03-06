// Reduzierung der St�tzpunkte von Linien- bzw. Fl�chenobjekten durch Polygonapproximation
// File: PA.CXX
// W. M�rtl


#include "GeoReinP.hxx"
                                    

// Untersuchung einer Punktfolge x[],y[] von Index j bis Index k auf eine verallgemeinerte Kollinearit�t;
// liegt Kollinearit�t vor, wird true zur�ckgegeben, sonst false; weitere R�ckgabewerte sind
//   a[]   Koeffizienten der Strecke zwischen x[j],y[j] und x[k],y[k]; dabei ist a[0] der Koeffizient
//         von x, a[1] der Koeffizient von y
//   m     Index des Punktes, bei dem die Maximalabweichung (als absoluter Wert) auftritt
//   L     L�nge der Strecke zwischen x[j],y[j] und x[k],y[k]
// (Quelle: Pavlidis, Th.: Algorithmen zur Grafik und Bildverarbeitung,
//  Verlag Heinz Heise, Hannover, 1990, S. 334 ff.)

//bool Collinear (double __huge x[], double __huge y[], long j, long k, long& m, double a[],
bool Collinear (double* x, double* y, long j, long k, long& m, double a[], double& L,
				double T0)
{
double ogw = 1.5;	// gilt La/L > ogw, kann Kollinearit�t ausgeschlossen werden

double T = 0;		// Gr��e der Maximalabweichung (als absoluter Wert)
double d;			// Gr��e der Abweichung an einem Punkt (als absoluter Wert)

	a[0] = y[j] - y[k];
	a[1] = x[k] - x[j];
	
	L = sqrt (a[0]*a[0] + a[1]*a[1]);
	if (L == 0)
		return true;    // Kollinearit�t, da Strecke L�nge 0 besitzt

	m = j;
	for (long i = j+1; i < k; i++)
	{
		d = fabs ((x[i]-x[j])*a[0] - (y[j]-y[i])*a[1]);
		if (d > T)
		{
			T = d; m = i;
		}
	}

	if (T == 0)     // gr��ter Abstand ist Null, dann liegt echte Kollinearit�t vor
		return true;

	if (T/L < T0)
	{
	// Es gibt Spezialf�lle (siehe S. 336) bei denen trotz eines geringen Abstandes aller Punkte
	// von der Ausgleichsstrecke keine Kollinearit�t angenommen werden kann. Deshalb noch der
	// Vergleich der L�nge dieser Strecke mit dem L�nge des vollst�ndigen Polygonzuges
	double La = 0;  // L�nge des Polygonzuges entlang der Punktefolge

		for (long i = j+1; i <= k; i++)
		{
		double dx = x[i] - x[i-1];
		double dy = y[i] - y[i-1];

			La += sqrt (dx*dx + dy*dy);     // L�nge des Polygonzuges
		}

		if (La/L > ogw)
			return false;    // Kollinearit�t kann ausgeschlossen werden
		return true;
	}
	else
		return false;

} // Collinear



// ------------------------------------------------------------------------------------------------
// Approximation einer Punktefolge pX/pY durch ein Polygon, wobei Punkte, die (in einem erweiterten
// Sinne) kollinear sind, nicht ber�cksichtigt werden;
//   T0   max. zul�ssiger Abstand bei der �berpr�fung auf Kollinearit�t
//   k0   Anzahl der auf Kollinearit�t untersuchten Strecken
// (Quelle: Pavlidis, Th.: Algorithmen zur Grafik und Bildverarbeitung,
//  Verlag Heinz Heise, Hannover, 1990, S. 339 ff.)

//bool PolygonApproximation (double __huge* pX, double __huge* pY, long& n, double T0, long k0)
bool PolygonApproximation (double* pX, double* pY, long& n, double T0, long k0)
{
long i = 1;	// Index von pX bzw. pY, bei dem ein alter Wert durch einen neuen (approximierten) Wert �berschrieben wird
long p = 0;	// Index der letzten Polygonspitze, d.h. eines Punktes, der f�r die reduzierte Punktefolge �bernommen wird
long j = 0;	// erster bzw.
long k;		//  letzter Index der Punkte, zwischen denen die Kollinearit�t �berpr�ft werden soll
double a [2];	// Koeffizienten der Strecke zwischen x[j],y[j] und x[k],y[k] als Ergebnis der Prozedur
				// Collinear; dabei ist a[0] der Koeffizient von x, a[1] der Koeffizient von y
double a1 [2];  // Koeffizienten der aktuellen Strecke L1
double a2 [2];  // Koeffizienten der neuen Strecke L2
long m = 0;     // Index des Punktes, bei dem die Maximalabweichung (als absoluter Wert) auftritt
double L = 0.;  // L�nge der Strecke zwischen x[j],y[j] und x[k],y[k]

	if (n <= k0 + 1)	// Sonderbehandlung bei kleiner St�tzpunktanzahl
		k0 = 1;
	k = k0;

	while (j < n-1)
	{
	bool Kolli = Collinear (pX, pY, j, k, m, a, L, T0);

		if (Kolli)      // Kollinearit�t liegt vor
		{                          
			// Definition einer neuen Strecke L2 durch die Koeffizienten, die von Collinear
			// zur�ckgegeben wurden
			a2[0] = a[0];
			a2[1] = a[1];

			// der 1. Punkt der Gruppe war ein Teilpunkt
			if (p == j)
			{
				a1[0] = a2[0];  // die neue Srecke L2 wird
				a1[1] = a2[1];  // zur aktuellen Strecke L1
			}

			// der 1. Punkt der Gruppe war kein Teilpunkt, deshalb werden die Strecken L1 und L2
			// verglichen, ob eine Zusammenfassung vorgenommen werden kann
			else
			{
				// Koeffizienten der Strecke, die vom L1-Anfangspunkt bis zum L2-Endpunkt geht
				a1[0] = pY [p] - pY [k];
				a1[1] = pX [k] - pX [p];

			// Abstand d des L1-Endpunktes (= L2-Anfangspunkt) von dieser Strecke und L�nge L
			// dieser Strecke
			double d = (pX[j] - pX[p])*a1[0] - (pY[p] - pY[j])*a1[1];
			double L = sqrt (a1[0]*a1[0] + a1[1]*a1[1]);

				// L1 und L2 k�nnen nicht zusammengefa�t werden, da deren gemeinsamer Punkt
				// zu weit von der eben gebildeten Strecke entfernt liegt
				if (L > 0 && fabs(d)/L > T0)
				{
					p = j;			// Punkt x[j],y[j] wird als Teilpunkt markiert
					a1[0] = a2[0];  // die neue Srecke L2 wird
					a1[1] = a2[1];  // zur aktuellen Strecke L1

					// weiteren Punkt der approximierten Punktfolge hinzuf�gen
					if (i != p && i < j)
					{
						pX [i] = pX [p];
						pY [i] = pY [p];
						i++;
					}
					else	// hier l�uft was schief !! (Selbst�berschreibung von pX und/oder pY)
					{
						if (i >= j && (i != j || i != p))
						{
							DEX_Error (RC_PolygonApproximation, EC_APPROXIMATION);
							return false;
						}
					}
				}
			}
			j = k;
			if (k+k0 < n)
				k += k0;
			else
				k = n-1;
		}
		else	    // Kollinearit�t liegt nicht vor
			k = m;
	} // while-Ende
	
	if (p != n-1)   // evtl. noch letzten Punkt hinzuf�gen
	{
		pX [i] = pX [n-1];
		pY [i] = pY [n-1];
		i++;
	}
	
	n = i;		// neue (reduzierte) Anzahl
	
	return true;

} // PolygonApproximation
