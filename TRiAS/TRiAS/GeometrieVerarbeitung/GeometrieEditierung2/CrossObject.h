// Klasse für ein achsenparalleles Kreuz
// File: CrossObject.h
// W. Mörtl

#ifndef _CROSSOBJECT_H
#define _CROSSOBJECT_H


class CrossObject : public DrawObject
{
protected:
	CoOrd		m_b;		// halbe Breite (Hälfte von dim.Width())
	CoOrd		m_h;		// halbe Höhe (Hälfte von dim.Height())
	pPen		m_pMyPen;

	void		DrawEx (DWORD dw);

public:
		CrossObject (Point ptCentre, Dimension dim, pPen pen = NULL);
		~CrossObject (void) {};

	Rectangle	BoundingBox (void);
	Point 		ChangePosition (Point NewCentr);
};

#endif	// _CROSSOBJECT_H
