#ifndef __TRACKOBJECT_H__
#define __TRACKOBJECT_H__

class CTrackObject : public CDPoint {
protected:
	BOOL	m_bTrackOn;
	virtual void Invert(CDC *pDC) = 0;
public:
	CTrackObject();
	virtual  ~CTrackObject();
	virtual void Attach(LPVOID pObject) = 0;

	virtual void StartTracking(CDC *pDC, LPPOINT point) = 0;
	virtual void Track(CDC *pDC, LPPOINT lpPoint) = 0;
	virtual void StopTracking(CDC *pDC, LPPOINT point) = 0;
	virtual void StopTracking(LPPOINT point) = 0;

	virtual CDPoint GetTrackPoint() = 0;
	virtual CDRect GetBoundingRect() = 0;
};

class CTrackPoint : public CTrackObject {
	LPDPOINT	m_pPoint;
	void Invert(CDC *pDC);
public:
	CTrackPoint();
	virtual ~CTrackPoint();
	virtual void Attach(LPVOID pObject);

	virtual void StartTracking(CDC *pDC, LPPOINT point);
	virtual void Track(CDC *pDC, LPPOINT lpPoint);
	virtual void StopTracking(CDC *pDC, LPPOINT point);
	virtual void StopTracking(LPPOINT point);

	virtual CDPoint GetTrackPoint();
	virtual CDRect GetBoundingRect();
};

#endif //__TRACKOBJECT_H__