// Gitternetzlinien -----------------------------------------------------------
class GitterObjekt : public ExtShapeObject {
private:
	Bool _GitterFlag;

protected:
	void Draw (void);		// Gitter zeichnen

public:
	GitterObjekt (Bool GFlag, pPen pP = NULL, pBrush pB = NULL) :
		ExtShapeObject (Point (0, 0), Dimension (), pP, pB)
			{ _GitterFlag = GFlag; }

	Bool & GitterFlag (void) { return _GitterFlag; }
	ObjTyp isTyp (void) { return O_GITTER; }
};

