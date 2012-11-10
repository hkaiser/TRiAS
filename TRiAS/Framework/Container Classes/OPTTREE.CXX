// Funktionen zur Optimierung (Ausgleichung) eines Binaerbaumes
// File: OPTTREE.CXX


#include "contpre.hxx"

#if !defined(NOOPTTREE)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void _DLLENTRY CTree :: Optimize (void) 
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

// Anfangstest
	if (Count() == 0) return;

	TX_ASSERT(ValidateTree(m_pRoot -> Left()));

// Linearisierung des Baumes
CBinaryNode *newRoot = Linear();

	TX_ASSERT(NULL != newRoot);

	newRoot -> SetParent (m_pRoot);
	m_pRoot -> SetRight (NULL);	// wird nicht mehr gebraucht

// Baum optimal falten, wenn mindestens 3 Knoten da sind
	if (Depth (newRoot, RECHTS_MAX3) > 1) {
		newRoot = Fold (newRoot, RECHTS);
		m_pRoot -> SetLeft (newRoot);
		newRoot -> SetParent (m_pRoot);
	} 

// linken und rechten Ast falten
long rDepth = Depth (newRoot, RECHTS_MAX3);  // Länge der SubBäume
long lDepth = Depth (newRoot, LINKS_MAX3);

	if (rDepth == 2 && lDepth == 2)
	// Spezialfall
		newRoot = Special (newRoot, RECHTS);
	else if (rDepth > 2 || lDepth > 2) {
	// Normalfall
		newRoot = Branch (newRoot, RECHTS);
		m_pRoot -> SetLeft (newRoot);
		newRoot -> SetParent (m_pRoot);
		newRoot = Branch (newRoot, LINKS);
	}

// Baum wieder in Container einhängen
	m_pRoot -> SetRight (NULL);
	m_pRoot -> SetLeft (newRoot);
	newRoot -> SetParent (m_pRoot);

	TX_ASSERT(ValidateTree(newRoot));		// Baum überprüfen
}

// Bestimmen der Länge eines Astes --------------------------------------------
long CTree :: Depth (CBinaryNode *bNode, Richtung R) 
{
long d = 0;      // LängenZähler

	switch (R) {
	case RECHTS:
		while (bNode -> Right() != NULL) {
			d++;
			bNode = bNode -> Right();
		}
		break;

	case LINKS:
		while (bNode -> Left() != NULL) {
			d++;
			bNode = bNode -> Left();
		}
		break;

	case RECHTS_MAX3:
		while (bNode -> Right() != NULL && d <= 3) {
			d++;
			bNode = bNode -> Right();
		}
		break;

	case LINKS_MAX3:
		while (bNode -> Left() != NULL && d <= 3) {
			d++;
			bNode = bNode -> Left();
		}
		break;

	default:
		TX_ASSERT(false);
		return 0L;
	}

return d;
}

// Funktion, für den Spezialfall, wenn beide Äste die Länge 2 haben
// Ausgangspunkt:	wird zu (RECHTS):	oder (LINKS):
//		3                     4              2
//	      /   \                 /   \          /   \ 
//	    2       4	           2     5        1     4
//        /           \          /   \                /   \ 
//      1		5       1     3              3     5
//
CBinaryNode *CTree :: Special (CBinaryNode *bNode, Richtung R) 
{
CBinaryNode *tNode, *newNode;    // temporäre Variablen

	switch (R) {
	case RECHTS:
		tNode = bNode -> Left(); 			// 2
		newNode = bNode -> Right();			// 4
		tNode -> SetRight (bNode);			// 2->R = 3
		tNode -> SetParent (newNode);			// 2->P = 4
		bNode -> SetLeft (NULL);			// 3->L = 0
		bNode -> SetRight (NULL);			// 3->R = 0
		newNode -> SetLeft (tNode);			// 4->L = 2
		newNode -> SetParent (bNode -> Parent());	// 4->P = 3->P
		if (bNode -> Parent()) {
			if (bNode -> Parent() -> Left() == bNode)
				bNode -> Parent() -> SetLeft (newNode);	// 4->P->L = 4
			else
				bNode -> Parent() -> SetRight (newNode);// 4->P->R = 4
		}
		bNode -> SetParent (tNode);			// 3->P = 2
		break;

	case LINKS:
		tNode = bNode -> Right();
		newNode = bNode -> Left();
		tNode -> SetLeft (bNode);
		tNode -> SetParent (newNode);
		bNode -> SetLeft (NULL);
		bNode -> SetRight (NULL);
		newNode -> SetRight (tNode);
		newNode -> SetParent (bNode -> Parent());
		if (bNode -> Parent()) {
			if (bNode -> Parent() -> Left() == bNode)
				bNode -> Parent() -> SetLeft (newNode);
			else
				bNode -> Parent() -> SetRight (newNode);
		}
		bNode -> SetParent (tNode);
		break;

	default:
		TX_ASSERT(false);
		newNode = bNode;
		break;
	}

return newNode;
}

// Rekursive Funktion, die einen linearisierten Baum faltet -------------------
CBinaryNode *CTree :: Branch (CBinaryNode *bNode, Richtung R) 
{
CBinaryNode *newNode;

	switch (R) {
	case RECHTS:
	// Spezialfall abtesten
		if (Depth (bNode, RECHTS_MAX3) == 2 && Depth (bNode, LINKS_MAX3) == 2)
			bNode = Special (bNode, RECHTS);
			// ElternKorrektur erfolgt in Special selbst
		else {
		// ansonsten rechten Ast falten
			newNode = Fold (bNode -> Right(), RECHTS);
			bNode -> SetRight (newNode);
			newNode -> SetParent (bNode);

		// mit rechtem Ast weitermachen, wenn er lang genug ist
			if (Depth (bNode -> Right(), RECHTS_MAX3) > 1) {
				newNode = Branch (bNode -> Right(), RECHTS);
				bNode -> SetRight (newNode);
				newNode -> SetParent (bNode);
			}

		// mit linkem Ast weitermachen, wenn er lang genug ist
			if (Depth (bNode -> Right(), LINKS_MAX3) > 2) {
				newNode = Branch (bNode -> Right(), LINKS);
				bNode -> SetRight (newNode);
				newNode -> SetParent (bNode);
			}
		}
		break;

	case LINKS:
	// Spezialfall abtesten
		if (Depth (bNode, LINKS_MAX3) == 2 && Depth (bNode, RECHTS_MAX3) == 2)
			bNode = Special (bNode, LINKS);
			// ElternKorrektur erfolgt in Special selbst
		else {
		// ansonsten linken Ast falten
			newNode = Fold (bNode -> Left(), LINKS);
			bNode -> SetLeft (newNode);
			newNode -> SetParent (bNode);

		// mit linkem Ast weitermachen, wenn er lang genug ist
			if (Depth (bNode -> Left(), LINKS_MAX3) > 1) {
				newNode = Branch (bNode -> Left(), LINKS);
				bNode -> SetLeft (newNode);
				newNode -> SetParent (bNode);
			}

		// mit rechtem Ast weitermachen, wenn er lang genug ist
			if (Depth (bNode -> Left(), RECHTS_MAX3) > 2) {
				newNode = Branch (bNode -> Left(), RECHTS);
				bNode -> SetLeft (newNode);
				newNode -> SetParent (bNode);
			}
		}
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return bNode;
}

// Einen Ast des Baumes in der vorgegebenen Richtung falten
CBinaryNode *CTree :: Fold (CBinaryNode *bNode, Richtung R) 
{
// temporäre Pointer
CBinaryNode *tRoot;
long nDepth;		// Astlänge
long loop;		// Laufvariable

	switch (R) {
	case RECHTS:
		nDepth = Depth (bNode, RECHTS);
		if (nDepth % 2)
			nDepth++;       // Überhang links lassen
		nDepth >>= 1;

	// das ElternNode wird zum linken KindNode für alle Nodes 
	// vom ersten bis zum mittleren
		for (loop = 0; loop < nDepth; loop++) {
			tRoot = bNode -> Right();
			tRoot -> SetLeft (bNode);
			bNode -> SetRight (NULL);
			tRoot -> SetParent (bNode -> Parent());
			bNode -> SetParent (tRoot);
			bNode = tRoot;
		}
		TX_ASSERT(loop == nDepth);
		break;

	case LINKS:
		nDepth = Depth (bNode, LINKS);
		if (nDepth % 2)
			nDepth++;       // Überhang links lassen
		nDepth >>= 1;

	// das ElternNode wird zum rechten KindNode für alle Nodes 
	// vom ersten bis zum mittleren
		for (loop = 0; loop < nDepth; loop++) {
			tRoot = bNode -> Left();
			tRoot -> SetRight (bNode);
			bNode -> SetLeft (NULL);
			tRoot -> SetParent (bNode -> Parent());
			bNode -> SetParent (tRoot);
			bNode = tRoot;
		}
		TX_ASSERT(loop == nDepth);
		break;

	default:
		TX_ASSERT(false);
		return NULL;
	}

return bNode;
}

#if 0
// Rekursive Funktion, die einen Binärbaum linearisiert, 
// liefert jeweils aktuelles oberes Ende (== Wurzel) des Baumes (der Liste)
CBinaryNode *CTree :: Linear (CBinaryNode *bNode, CBinaryNode *Last) 
{
// rechten Ast bearbeiten
	if (bNode -> Right() == NULL) {
	// rechts ist nichts mehr --> Schwanz anhängen
		bNode -> SetRight (Last);
		if (Last) Last -> SetParent (bNode);
	} else
	// rechts weitertauchen
		Last = Linear (bNode -> Right(), Last);

// linken Ast bearbeiten
	if (bNode -> Left() == NULL)
	// links nichts mehr --> ok, wieder auftauchen
		return bNode;
	else {
	// links weitertauchen
		Last = Linear (bNode -> Left(), Last);
		bNode -> SetLeft (NULL);	// linken Ast löschen
		return Last;
	}
}
#endif

// nichtrekursive Variante ----------------------------------------------------
CBinaryNode *CTree :: Linear (void) 
{
CBinaryNode *actNode = m_pRoot -> LeftMost();	// links unten anfangen
CBinaryNode *oldRoot = m_pRoot -> Left();
CBinaryNode *newRoot = actNode;			// neue Wurzel des Baumes setzen
CBinaryNode *Last = m_pRoot;

// Traversal nach dem InOrder - Prinzip
	while (TRUE) {
	// actNode bearbeiten: in linearen Teil einbinden
		Last -> SetRight (actNode);
		Last -> SetLeft (NULL);
		Last = actNode;

	// nächter Node
		if (actNode -> Right()) 
			actNode = actNode -> Right() -> LeftMost();
		else {
		// rechten SubBaum wieder hochhangeln
			while (actNode -> Parent() -> Left() != actNode) {
				if (actNode != oldRoot) {
					actNode = actNode -> Parent();
				} else {	
					CorrectParents();	// ParentPointer richten
					return newRoot;
				}
			}
			actNode = actNode -> Parent();
		}
	}
}

// ParentPointer entsprechend Linearisierung richten --------------------------
void CTree :: CorrectParents (void) 
{
CBinaryNode *bNode = m_pRoot;

	bNode -> SetParent (NULL);
	bNode -> SetLeft (NULL);
	while (bNode -> Right()) {
		bNode -> Right() -> SetParent (bNode);
		bNode = bNode -> Right();
		bNode -> SetLeft (NULL);
	}
}


#if defined(_DEBUG)
BOOL CTree :: ValidateTree (CBinaryNode *bNode) 
{
CBinaryNode *bN = bNode;
BOOL fError = true;

	while (TRUE) {
		if (bN -> Left()) {
			if (bN -> Left() -> Parent() != bN) {
/*				MessageBeep (0);
				MessageBox (NULL, "Linker SubBaum inkorrekt",
					    "Fehler im Baum", 
					    MB_OK|MB_ICONEXCLAMATION);
*/
				TX_ASSERT(/* Linker SubBaum inkorrekt */false);
				bN -> Left() -> SetParent (bN);
				fError = false;
			}
			bN = bN -> Left();
		} else if (bN -> Right()) {
			if (bN -> Right() -> Parent() != bN) {
/*				MessageBeep (0);
				MessageBox (NULL, "Rechter SubBaum inkorrekt",
					    "Fehler im Baum", 
					    MB_OK|MB_ICONEXCLAMATION);
*/
				TX_ASSERT(/* Rechter SubBaum inkorrekt */false);
				bN -> Right() -> SetParent (bN);
				fError = false;
			}
			bN = bN -> Right();
		} else {
			while (bN != bNode &&
				(bN -> Parent() -> Left() != bN || 
				!bN -> Parent() -> Right()))
					bN = bN -> Parent();
			if (bN != bNode)
				bN = bN -> Parent() -> Right();
			else
				return true;
		}
	}

return fError;
}
#else
BOOL CTree :: ValidateTree (CBinaryNode *) 
{
	return true;
}
#endif // _DEBUG

#endif // NOOPTTREE
