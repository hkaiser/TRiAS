// Geometrie auf dem Bildschirm
// File: ScreenGeometry.hxx
// W. Mörtl


#ifndef _SCREENGEOMETRY_HXX_
#define _SCREENGEOMETRY_HXX_


_GEOMETR_ENTRY SectScreen SegmentSegmentIntersection (Point APt1, Point EPt1, Point APt2,
		Point EPt2, Point& SectPt1, Point& SectPt2);
_GEOMETR_ENTRY SectScreen SegmentStraightIntersection (Point APt1, Point EPt1, Point APt2,
		Point EPt2, Point& SectPt1, Point& SectPt2);
_GEOMETR_ENTRY SectScreen SegmentCircleIntersection (Point APt, Point EPt, Point MPt, int iRad,
		bool& bTwice, Point& SectPt1, Point& SectPt2);
_GEOMETR_ENTRY SectScreen StraightStraightIntersection (Point APt1, Point EPt1, Point APt2,
		Point EPt2, Point& SectPt);
_GEOMETR_ENTRY SectScreen StraightCircleIntersection (Point APt, Point EPt, Point MPt,
		int iRad, bool& bTwice, Point& SectPt1, Point& SectPt2);
_GEOMETR_ENTRY SectScreen CircleCircleIntersection (Point MPt1, int iRad1, Point MPt2,
		int iRad2, bool& bTwice, Point& SectPt1, Point& SectPt2);

bool StraightsOverlapping (Point APt1, Point EPt1, Point APt2, Point EPt2, Point& SectPt1,
		Point& SectPt2);
SectScreen NotVerticalStraightCircle (double m, double n, double c, double d, double r,
		bool& bTwice, Point& SectPt1, Point& SectPt2);
SectScreen VerticalStraightCircle (double x, double c, double d, double r, bool& bTwice,
		Point& SectPt1, Point& SectPt2);
SectScreen IsPointInsideView (Point Pt);

#endif //_SCREENGEOMETRY_HXX_
