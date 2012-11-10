// --------------------------------------------------------------------------
// Description : several WTL utility classes for managing the layout of window children
// Author	   : Serge Weinstock
//
//	You are free to use, distribute or modify this code
//	as long as the header is not removed or modified.
// --------------------------------------------------------------------------
#if !defined(__layoutmgr_h__)
#define __layoutmgr_h__

#include <ospace/std/map>

const int	N_MAX_ITERATIONS = 100;

//=====================================================================
// RegisteredWindowMessage
//=====================================================================
//! Wrapper class around RegisterWindowMessage
class ATL_NO_VTABLE RegisteredWindowMessage
{
public:
	//! Constructor
	RegisteredWindowMessage(LPCTSTR msgName);
	//! Returns the message ID
	operator UINT () const;
private:
	UINT	_msgID;	//!< the message number
};

//=============================================================================
// Private messages
//=============================================================================
extern const RegisteredWindowMessage	WMU_PS_ATTACH_PAGE;
extern const RegisteredWindowMessage	WMU_PS_INIT;
extern const RegisteredWindowMessage	WMU_PS_ATTACH_PS;

//=====================================================================
// SizeGrip window
//=====================================================================
class SizeGrip : public CWindowImpl<SizeGrip>
{
public:
	typedef CWindowImpl<SizeGrip> inherited;

	DECLARE_WND_CLASS(_T("SizeGrip"))

	//! Creates a SizeGrip window
	bool Create(HWND parent);

	BEGIN_MSG_MAP(SizeGrip)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

protected:
	//! Don't erase the background
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//! paints the window
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

//=============================================================================
// LayoutMgr
//=============================================================================
//! This class is the base class for all resizable windows
/*!
	This class is inspired by the XmFormManager of Motif. 
	\p
	The layout of the children is based on relationships defined for every children and for some of their side.
	A children can have one side attached to another children or to one of the parent side.
	\p
	A constraint can be applied to one of the following side:
	<ul>
	<li>The left side (ATTACH_LEFT)</li>
	<li>The right side (ATTACH_RIGHT)</li>
	<li>The horizontal center(ATTACH_HCENTER)</li>
	<li>The top side (ATTACH_TOP)</li>
	<li>The bottom side (ATTACH_RIGHT)</li>
	<li>The vertical center(ATTACH_VCENTER)</li>
	</ul>
	The type of constraint can be:
	<ul>
	<li>No constraint (ATTACH_NONE)</li>
	<li>
	Attach the side to the opposited side of another children (ATTACH_WIDGET)
	\code
	 ---|    |---
	    |====|
	 ---|    |---
	\endcode
	</li>
	<li>
	Attach the side to the same side of another children (ATTACH_OPPOSITE_WIDGET)
	\code
	 ---|
	    |===
	 ---|   |
	        |
	        |
	 ---|   |
	    |===
	 ---|
	\endcode
	</li>
	<li>
	If the nb of position of the form has been set to N, the affected side will
	be at position/N th of the form (ATTACH_POSITION)
	\code
	 ---------------------
	 |   |   |   |   |   |
	 |   | |---  |   |   |
	 |   |=|     |   |   |
	 |   | |---  |   |   |
	 |   |   |   |   |   |
	 |--------------------
	\endcode
	</li>
	<li>
	Attach the side to the opposited side of the parent (ATTACH_FORM)
	\code
	 -------------
	 |    |---
	 |====|
	 |    |---
	 |------------
	\endcode
	</li>
	<li>
	Attach the side to the same side of the parent (ATTACH_OPPOSITE_FORM)
	\code
	 -------------
	 | ---|
	 |====|
	 | ---|
	 |------------
	\endcode
	</li>
	<li>
	Keeps the side to its initial position in the form (ATTACH_SELF)
	</li>
	</ul>
	
 */
template <class T>
class ATL_NO_VTABLE LayoutMgr {
public:
	//!
	enum Side {
		ATTACH_LEFT,		//!< left side
		ATTACH_RIGHT,		//!< right side
		ATTACH_HCENTER,		//!< horizontal center (works onky with ATTACH_OPPOSITE_WIDGET and ATTACH_FORM)
		ATTACH_TOP,			//!< top side
		ATTACH_BOTTOM,		//!< bottom side
		ATTACH_VCENTER,		//!< vertical center (works onky with ATTACH_OPPOSITE_WIDGET and ATTACH_FORM)
		ATTACH_MAX
		};

	enum ConstraintType {
		
		ATTACH_NONE = 0,		//!< no constraint
		ATTACH_WIDGET,			//!< the affected side is linked to the opposited side of the reference widget
		ATTACH_OPPOSITE_WIDGET,	//!< the affected side is linked to the same side of the reference widget
		ATTACH_POSITION,		//!< if the nb of position of the form has been set to N, the affected side will be at position/N th of the form
		ATTACH_FORM,			//!< the affected side will be attached to the corresponding border of the form
		ATTACH_OPPOSITE_FORM,	//!< the affected side will be attached to the opposite border of the form
		ATTACH_SELF				//!< the affected side will be attached to its initial position in the form
		};
public:
	//! Constructor
	LayoutMgr();
	//! Destructor
	~LayoutMgr();

	//! Sets the number of positions for the constraints of type ATTACH_POSITION
	void SetNPositions(unsigned nPos);
	void SetNPositionsX(unsigned nPos);
	void SetNPositionsY(unsigned nPos);

	//! Set the contraint to ATTACH_NONE
	void AttachNone(HWND child, Side side);
	//! Set the contraint to ATTACH_WIDGET
	void AttachWidget(HWND child, Side side, HWND reference);
	//! Set the contraint to ATTACH_OPPOSITE_WIDGET
	void AttachOppositeWidget(HWND child, Side side, HWND reference);
	//! Set the contraint to ATTACH_POSITION
	void AttachPosition(HWND child, Side side, unsigned pos);
	//! Set the contraint to ATTACH_FORM
	void AttachForm(HWND child, Side side);
	//! Set the contraint to ATTACH_OPPOSITE_FORM
	void AttachOppositeForm(HWND child, Side side);
	//! Set the contraint to ATTACH_SELF
	void AttachSelf(HWND child, Side side);

	//! Set the contraint to ATTACH_NONE
	void AttachNone(UINT childID, Side side);
	//! Set the contraint to ATTACH_WIDGET
	void AttachWidget(UINT childID, Side side, UINT refID);
	//! Set the contraint to ATTACH_OPPOSITE_WIDGET
	void AttachOppositeWidget(UINT childID, Side side, UINT refID);
	//! Set the contraint to ATTACH_POSITION
	void AttachPosition(UINT childID, Side side, unsigned pos);
	//! Set the contraint to ATTACH_FORM
	void AttachForm(UINT childID, Side side);
	//! Set the contraint to ATTACH_OPPOSITE_FORM
	void AttachOppositeForm(UINT childID, Side side);
	//! Set the contraint to ATTACH_SELF
	void AttachSelf(UINT childID, Side side);

	// show/hide the resizing handle
	bool ShowHandle(bool show);

	//!< All the information representing a constraint
	struct SideConstraint
		{
		ConstraintType	_type;		//!< Constraint type
		int				_offset;	//!< Offset used when applying the constraint
		HWND			_reference;	//!< the refrence widget used in constraint of type ATTACH_WIDGET
		int				_pos;		//!< the position used in contraint of type ATTACH_POSITION

		//!< Constructor
		SideConstraint()
			: _type(ATTACH_NONE), _offset(0), _reference(0), _pos(0) {}
		};
	//!< all the constraints applied to a children
	struct	Constraint
		{
		SideConstraint	_constraint[ATTACH_MAX];	//!< a map between a side and the corresponding constraint
		RECT			_pos;						//!< this rectangle is used during the computation of the layout for holding the temporary position of the children
		//!< Constructor
		Constraint()
			{ 
			_pos.left = _pos.top = _pos.right = _pos.bottom = 0; 
			::memset(_constraint, ATTACH_MAX*sizeof(SideConstraint), 0);
			}
		};

	// A map between children and their associated constraints
	typedef map<HWND , Constraint, less<HWND> >	ConstraintsMap;

	//! Compute the layout of the children without applying it to the children
	bool ComputeLayout();
	//! Moves and resizes the children according to the computed layout
	void DoLayout();

	// can be overridded by descendents
	//! Returns the client area of the container
	void GetDialogRect(LPRECT r);
	//! This method allows to define the layout constraints
	void DefineLayout();
	//! This methods returns the offset for positionning the controls in the client rect
	void GetOffset(LPPOINT offset);

	//! Common method called on WM_SIZE messages
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//! Common method called on WM_GETMINMAXINFO messages
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//! Common method called on WMU_PS_ATTACH_PS messages
	LRESULT OnAttachPropertySheet(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//! Common method called on WMU_ERASEBKG messages
	/*!
	This method excludes the control window rectangles defined in _controlsToClip from the DC clipping region
	\warning _controlsToClip must be an array of control IDs where the last element must be 0
	*/
	LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	ConstraintsMap	_constraints;		//!< all the constraints
	int				_nPosX;				//!< the total nb of positions for ATTACH_POSITION constraints (X-Axis)
	int				_nPosY;				//!< the total nb of positions for ATTACH_POSITION constraints (Y-Axis)
	SIZE			_minClientSize;		//!< the minimum client size of the container
	SIZE			_prevClientSize;	//!< the client size before resizing
	SIZE			_minWindowSize;		//!< the minimum window size of the mgr
	bool			_showHandle;		//!< show the resizing handle ?
	SizeGrip		_handle;			//!< the handle window
	const UINT		*_controlsToClip;	//!< the default _controlsToClip array
};

#ifdef __ATLWIN_H__
//=====================================================================
// CResizableDialogImplT
//=====================================================================
//! This class is the base class for resizable dialogs
template <class T, class TBase = CWindow, class DlgBase = CDialogImpl<T, TBase> >
class ATL_NO_VTABLE CResizableDialogImplT : public DlgBase, public LayoutMgr<T>
{
public:
	typedef CResizableDialogImplT<T, TBase, DlgBase> thisClass;

	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	*/
	CResizableDialogImpl(bool useHandle = false);

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<T>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<T>::OnEraseBackground)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, LayoutMgr<T>::OnGetMinMaxInfo)
		MESSAGE_HANDLER(WMU_PS_ATTACH_PS, LayoutMgr<T>::OnAttachPropertySheet)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()

protected:
	//! Initialisation of the dialog
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

//=====================================================================
// CResizableDialogImpl
//=====================================================================
template <class T, class TBase = CWindow>
class ATL_NO_VTABLE CResizableDialogImpl : public CResizableDialogImplT<T, TBase, CDialogImpl<T, TBase> >
{
public:
	typedef CResizableDialogImplT<T, TBase, CDialogImpl<T, TBase> > inherited;
	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	*/
	CResizableDialogImpl(bool useHandle = false);
};

#ifndef _ATL_NO_HOSTING

//=====================================================================
// CAxResizableDialogImpl
//=====================================================================
template <class T, class TBase = CWindow>
class ATL_NO_VTABLE CAxResizableDialogImpl : public CResizableDialogImplT<T, TBase, CAxDialogImpl<T, TBase> >
{
public:
	typedef CResizableDialogImplT<T, TBase, CAxDialogImpl<T, TBase> > inherited;
	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	*/
	CAxResizableDialogImpl(bool useHandle = false);
};

#endif // ifndef _ATL_NO_HOSTING

#endif // ifdef __ATLWIN_H__

#if defined(__ATLSCRL_H__) && defined(__ATLWIN_H__)
//=====================================================================
// CResizableFormViewImplT
//=====================================================================
//! This class is the base class for resizable form views
template <class T, class TBase = CWindow, class DlgBase = CDialogImpl<T, TBase> >
class ATL_NO_VTABLE CResizableFormViewImplT : 
	public DlgBase,
	public CScrollImpl<T>,
	public LayoutMgr<T>
{
public:

	typedef CResizableFormViewImplT<T, TBase, DlgBase>	thisClass;
	typedef CDialogImpl<T, TBase>						dialogBase;
	typedef CScrollImpl<T>								scrollBase;

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP(scrollBase)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<T>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<T>::OnEraseBackground)
		MESSAGE_HANDLER(WMU_PS_ATTACH_PS, LayoutMgr<T>::OnAttachPropertySheet)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()

	//! Paints the view
	void DoPaint(CDCHandle /*dc*/);
// LayoutMgr
	//! Returns the client area of the container
	void GetDialogRect(LPRECT r);
	//! This methods returns the offset for positionning the controls in the client rect
	void GetOffset(LPPOINT offset);
protected:

	//! Initialisation of the dialog
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

//=====================================================================
// CResizableFormViewImpl
//=====================================================================
template <class T, class TBase = CWindow>
class ATL_NO_VTABLE CResizableFormViewImpl : public CResizableFormViewImplT<T, TBase, CDialogImpl<T, TBase> >
{
};

#ifndef _ATL_NO_HOSTING

//=====================================================================
// CAxResizableFormViewImpl
//=====================================================================
template <class T, class TBase = CWindow>
class ATL_NO_VTABLE CAxResizableFormViewImpl : public CResizableFormViewImplT<T, TBase, CAxDialogImpl<T, TBase> >
{
};

#endif // ifndef _ATL_NO_HOSTING

#endif // ifdef defined(__ATLSCRL_H__) && defined(__ATLWIN_H__)

#if defined(__ATLDLGS_H__) && defined(__ATLWIN_H__)
//=====================================================================
// CResizablePropertySheetImpl
//=====================================================================
//! This the base class for resizable property sheet
template <bool childWnd, class T, class TBase = CPropertySheetWindow>
class ATL_NO_VTABLE CResizablePropertySheetImpl : 
	public CPropertySheetImpl<T, TBase>,
	public LayoutMgr<T>
{
public:

	typedef CResizablePropertySheetImpl<childWnd, T, TBase>	thisClass;
	typedef CPropertySheetImpl<T, TBase>					dialogBase;

	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	*/
	CResizablePropertySheetImpl(_U_STRINGorID title = (LPCTSTR)NULL, UINT uStartPage = 0, HWND hWndParent = NULL, bool useHandle = false);
	//! Creates it
	HWND Create(HWND hWndParent = NULL);

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<T>::OnSize)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, LayoutMgr<T>::OnGetMinMaxInfo)
		MESSAGE_HANDLER(WMU_PS_ATTACH_PS, LayoutMgr<T>::OnAttachPropertySheet)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WMU_PS_ATTACH_PAGE, OnAttachPage)
		MESSAGE_HANDLER(WMU_PS_INIT, OnInit)
		CHAIN_MSG_MAP(dialogBase)
	END_MSG_MAP()

	//! Property sheet callback function
	static int CALLBACK PropSheetCallback(HWND hWnd, UINT uMsg, LPARAM lParam);
	//! Called at the intialisation of the property sheet
	void OnInitDialog();
	//! Common method called on WMU_ERASEBKG messages
	/*!
	This method excludes the tab control window from the area to refresh
	*/
	LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	//! Attach a page
	LRESULT OnAttachPage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//! Initialises the property sheet
	LRESULT OnInit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

//=============================================================================
// CChildResizablePropertySheetImpl
//=============================================================================
//! A resizable child property sheet
template <class T, class TBase = CPropertySheetWindow>
class ATL_NO_VTABLE CChildResizablePropertySheetImpl : 
	public CResizablePropertySheetImpl<true, T, TBase>
{
public:

	typedef CChildResizablePropertySheetImpl<T, TBase>	thisClass;
	typedef CResizablePropertySheetImpl<true, T, TBase>	dialogBase;

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP(dialogBase)
	END_MSG_MAP()

	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	\param placeHolderID : id of the control which will server as a reference for the position of the property sheet
	*/
	CChildResizablePropertySheetImpl(UINT placeHolderID, _U_STRINGorID title = (LPCTSTR)NULL, UINT uStartPage = 0, HWND hWndParent = NULL, bool useHandle = false);
	//! Specific intialisation depending on wether or not the property sheet is a child window
	void SpecificInit();
protected:

	UINT	m_ID_Place_Holder; // the ID of the placeHolder
};

//=============================================================================
// CPopupResizablePropertySheetImpl
//=============================================================================
//! A resizable popup property sheet
template <class T, class TBase = CPropertySheetWindow>
class ATL_NO_VTABLE CPopupResizablePropertySheetImpl : 
	public CResizablePropertySheetImpl<false, T, TBase>
{
public:

	typedef CPopupResizablePropertySheetImpl<T, TBase>		thisClass;
	typedef CResizablePropertySheetImpl<false, T, TBase>	dialogBase;

	//! Constructor
	/*!
	\param useHandle : if true a handle is shown on the bottom right corner of the dialog
	\param placeHolderID : id of the control which will server as a reference for the position of the property sheet
	*/
	CPopupResizablePropertySheetImpl(_U_STRINGorID title = (LPCTSTR)NULL, UINT uStartPage = 0, HWND hWndParent = NULL, bool useHandle = false);

	BEGIN_MSG_MAP(thisClass)
		CHAIN_MSG_MAP(dialogBase)
	END_MSG_MAP()

	//! Specific intialisation depending on wether or not the property sheet is a child window
	void SpecificInit();
};

//=====================================================================
// CResizablePropertyPageImpl
//=====================================================================
//! This class is the base class for resizable dialogs
template <class T, class TBase = CPropertyPageWindow, class dialogBase = CPropertyPageImpl<T, TBase> >
class ATL_NO_VTABLE CResizablePropertyPageImplT : public dialogBase, public LayoutMgr<T>
{
public:
	typedef CResizablePropertyPageImplT<T, TBase, dialogBase> thisClass;

	//! Constructor
	CResizablePropertyPageImplT(_U_STRINGorID title = (LPCTSTR)NULL);

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<T>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<T>::OnEraseBackground)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(dialogBase)
	END_MSG_MAP()

	//! Page Activation;
	BOOL OnSetActive();
	//! Initialisation of the dialog
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	bool	_init;
};

//=====================================================================
// CResizablePropertyPageImpl
//=====================================================================
template <class T, class TBase = CPropertyPageWindow>
class ATL_NO_VTABLE CResizablePropertyPageImpl : public CResizablePropertyPageImplT<T, TBase, CPropertyPageImpl<T, TBase> >
{
public:
	typedef CResizablePropertyPageImplT<T, TBase, CPropertyPageImpl<T, TBase> > inherited;

	//! Constructor
	CResizablePropertyPageImpl(_U_STRINGorID title = (LPCTSTR)NULL);
};

#ifndef _ATL_NO_HOSTING
//=====================================================================
// CAxResizablePropertyPageImpl
//=====================================================================
template <class T, class TBase = CPropertyPageWindow>
class ATL_NO_VTABLE CAxResizablePropertyPageImpl : public CResizablePropertyPageImplT<T, TBase, CAxPropertyPageImpl<T, TBase> >
{
public:
	typedef CResizablePropertyPageImplT<T, TBase, CAxPropertyPageImpl<T, TBase> > inherited;

	//! Constructor
	CAxResizablePropertyPageImpl(_U_STRINGorID title = (LPCTSTR)NULL);
};

#endif // ifndef _ATL_NO_HOSTING

#endif // ifdef defined(__ATLDLGS_H__) && defined(__ATLWIN_H__)

//=============================================================================
//=============================================================================
// Inlines
//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
// RegisteredWindowMessage
//-----------------------------------------------------------------------------
inline RegisteredWindowMessage::RegisteredWindowMessage(LPCTSTR msgName)
{
	ATLASSERT(msgName != 0);
	_msgID = ::RegisterWindowMessage(msgName);
}

inline RegisteredWindowMessage::operator UINT () const
{
	return _msgID;
}

//-----------------------------------------------------------------------------
// LayoutMgr
//-----------------------------------------------------------------------------
template <class T>
inline LayoutMgr<T>::LayoutMgr()
: _nPosX(100), _nPosY(100), _showHandle(false), _controlsToClip(0)
{
	_minWindowSize.cx = _minWindowSize.cy = 0;
	_minClientSize.cx = _minClientSize.cy = 0;
	_prevClientSize.cx = _prevClientSize.cy = 0;
}

template <class T>
inline LayoutMgr<T>::~LayoutMgr()
{
	if (_handle.IsWindow()) { _handle.DestroyWindow(); }
}

template <class T>
inline void LayoutMgr<T>::SetNPositions(unsigned nPos)
{
	SetNPositionsX(nPos);
	SetNPositionsY(nPos);
}

template <class T>
inline void LayoutMgr<T>::SetNPositionsX(unsigned nPos)
{
	ATLASSERT(_nPosX>0);
	_nPosX = nPos;
}

// Definitions of the constraints from IDs
template <class T>
inline void LayoutMgr<T>::SetNPositionsY(unsigned nPos)
{
	ATLASSERT(_nPosY>0);
	_nPosY = nPos;
}

template <class T>
inline void LayoutMgr<T>::AttachNone(UINT childID, Side side)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	ATLASSERT(child != 0);
	AttachNone(child, side);
}


template <class T>
inline void LayoutMgr<T>::AttachWidget(UINT childID, Side side, UINT refID)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	HWND ref = pT->GetDlgItem(refID);
	ATLASSERT(child != 0);
	ATLASSERT(ref != 0);
	AttachWidget(child, side, ref);
}

template <class T>
inline void LayoutMgr<T>::AttachOppositeWidget(UINT childID, Side side, UINT refID)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	HWND ref = pT->GetDlgItem(refID);
	ATLASSERT(child != 0);
	ATLASSERT(ref != 0);
	AttachOppositeWidget(child, side, ref);
}

template <class T>
inline void LayoutMgr<T>::AttachPosition(UINT childID, Side side, unsigned pos)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	ATLASSERT(child != 0);
	AttachPosition(child, side, pos);
}

template <class T>
inline void LayoutMgr<T>::AttachForm(UINT childID, Side side)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	ATLASSERT(child != 0);
	AttachForm(child, side);
}

template <class T>
inline void LayoutMgr<T>::AttachOppositeForm(UINT childID, Side side)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	ATLASSERT(child != 0);
	AttachOppositeForm(child, side);
}

template <class T>
inline void LayoutMgr<T>::AttachSelf(UINT childID, Side side)
{
	T* pT = static_cast<T*>(this);
	HWND child = pT->GetDlgItem(childID);
	ATLASSERT(child != 0);
	AttachSelf(child, side);
}

//--------------------------------------------------------------
// Definitions of the constraints from HWND
//--------------------------------------------------------------
template <class T>
inline void LayoutMgr<T>::AttachNone(HWND child, Side side)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_NONE;
	s._reference = NULL;
	s._pos = 0;
	s._offset = 0;
	RECT rw;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
}

template <class T>
inline void LayoutMgr<T>::AttachWidget(HWND child, Side side, HWND reference)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_WIDGET;
	s._reference = reference;
	s._pos = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	::GetWindowRect(reference, &rr);
	pT->ScreenToClient(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-rr.right;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-rr.left;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-rr.bottom;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-rr.top;
			break;
		default:
			ATLASSERT(false);
		};
}

template <class T>
inline void LayoutMgr<T>::AttachOppositeWidget(HWND child, Side side, HWND reference)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_OPPOSITE_WIDGET;
	s._reference = reference;
	s._pos = 0;
	s._offset = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	::GetWindowRect(reference, &rr);
	pT->ScreenToClient(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-rr.left;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-rr.right;
			break;
		case ATTACH_HCENTER:
			s._offset = ((rw.left+rw.right)-(rr.left+rr.right))/2;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-rr.top;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-rr.bottom;
			break;
		case ATTACH_VCENTER:
			s._offset = ((rw.top+rw.bottom)-(rr.top+rr.bottom))/2;
			break;
		default:
			ATLASSERT(false);
		};
}

template <class T>
inline void LayoutMgr<T>::AttachPosition(HWND child, Side side, unsigned pos)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_POSITION;
	s._reference = NULL;
	s._pos = pos;
	s._offset = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	pT->GetDialogRect(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-(pos*(rr.right-rr.left))/_nPosX;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-(pos*(rr.right-rr.left))/_nPosX;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-(pos*(rr.bottom-rr.top))/_nPosY;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-(pos*(rr.bottom-rr.top))/_nPosY;
			break;
		default:
			ATLASSERT(false);
		};
}

template <class T>
inline void LayoutMgr<T>::AttachForm(HWND child, Side side)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_FORM;
	s._reference = NULL;
	s._pos = 0;
	s._offset = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	pT->GetDialogRect(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-rr.left;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-rr.right;
			break;
		case ATTACH_HCENTER:
			s._offset = ((rw.left+rw.right)-(rr.left+rr.right))/2;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-rr.top;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-rr.bottom;
			break;
		case ATTACH_VCENTER:
			s._offset = ((rw.top+rw.bottom)-(rr.top+rr.bottom))/2;
			break;
		default:
			ATLASSERT(false);
		};
}

template <class T>
inline void LayoutMgr<T>::AttachOppositeForm(HWND child, Side side)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_OPPOSITE_FORM;
	s._reference = NULL;
	s._pos = 0;
	s._offset = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	pT->GetDialogRect(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-rr.right;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-rr.left;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-rr.bottom;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-rr.top;
			break;
		default:
			ATLASSERT(false);
		};
}

template <class T>
inline void LayoutMgr<T>::AttachSelf(HWND child, Side side)
{
	SideConstraint &s = _constraints[child]._constraint[side];
	s._type = ATTACH_SELF;
	s._reference = NULL;
	s._pos = 0;
	s._offset = 0;
	RECT rw, rr;
	T	 *pT = static_cast<T*>(this);
	::GetWindowRect(child, &rw);
	pT->ScreenToClient(&rw);
	_constraints[child]._pos = rw;
	pT->GetDialogRect(&rr);
	switch (side)
		{
		case ATTACH_LEFT:
			s._offset = rw.left-rr.left;
			break;
		case ATTACH_RIGHT:
			s._offset = rw.right-rr.left;
			break;
		case ATTACH_TOP:
			s._offset = rw.top-rr.top;
			break;
		case ATTACH_BOTTOM:
			s._offset = rw.bottom-rr.top;
			break;
		default:
			ATLASSERT(false);
		};
}

// Move all the windows to their definitive positions
template <class T>
inline void LayoutMgr<T>::DoLayout()
{
	ConstraintsMap::iterator	wgt;
	HDWP						hdwp;
	POINT						offset;
	T							*pT = static_cast<T*>(this);

	pT->GetOffset(&offset);
	hdwp = ::BeginDeferWindowPos(_constraints.size());
	for (wgt = _constraints.begin(); wgt != _constraints.end(); wgt++)
		{
		RECT rc = (*wgt).second._pos;
		::DeferWindowPos(
			hdwp, (*wgt).first, NULL, 
			rc.left - offset.x, rc.top - offset.y,
			rc.right - rc.left, rc.bottom - rc.top,
			SWP_NOZORDER|SWP_NOREDRAW);
		}
	::EndDeferWindowPos(hdwp);
	pT->Invalidate();
}

// Layout management
template <class T>
inline bool LayoutMgr<T>::ComputeLayout()
{
	if (_constraints.empty())
		{
		return false;
		}
	
	// a very simple layout algorithm :
	// we apply the constraints until there's no more changes in the children layout
	int							i, ii;
	bool						change;
	ConstraintsMap::iterator	wgt;
	RECT						opos, formR;
	bool						doHLayout, doVLayout;
	T							*pT = static_cast<T *>(this);

	pT->GetDialogRect(&formR);

	doHLayout = ((formR.right - formR.left) > _minClientSize.cx) || (_prevClientSize.cx > _minClientSize.cx);
	doVLayout = ((formR.bottom - formR.top) > _minClientSize.cy) || (_prevClientSize.cy > _minClientSize.cy);

	if ((!doHLayout) && (!doVLayout))
		{
		return false;
		}

	for (i = 0; i < N_MAX_ITERATIONS; i++)
		{
		change = false;

		for (wgt = _constraints.begin(); wgt != _constraints.end(); wgt++)
			{
			RECT &pos = (*wgt).second._pos;
			opos = pos;
			if (doHLayout)
				//-----------------
				// left constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_LEFT];
				switch (c._type)
					{
					case ATTACH_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.left = _constraints[c._reference]._pos.right+c._offset;
						break;
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.left = _constraints[c._reference]._pos.left+c._offset;
						break;
					case ATTACH_FORM:
						pos.left = formR.left+c._offset;
						break;
					case ATTACH_OPPOSITE_FORM:
						pos.left = formR.right+c._offset;
						break;
					case ATTACH_POSITION:
						pos.left = (c._pos*(formR.right-formR.left))/_nPosX+c._offset;
						break;
					case ATTACH_SELF:
						pos.left = formR.left+c._offset;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			if (doHLayout)
				//-----------------
				// right constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_RIGHT];
				switch (c._type)
					{
					case ATTACH_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.right = _constraints[c._reference]._pos.left+c._offset;
						break;
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.right = _constraints[c._reference]._pos.right+c._offset;
						break;
					case ATTACH_FORM:
						pos.right = formR.right+c._offset;
						break;
					case ATTACH_OPPOSITE_FORM:
						pos.right = formR.left+c._offset;
						break;
					case ATTACH_POSITION:
						pos.right = (c._pos*(formR.right-formR.left))/_nPosX+c._offset;
						break;
					case ATTACH_SELF:
						pos.right = formR.left+c._offset;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			if (doVLayout)
				//-----------------
				// top constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_TOP];
				switch (c._type)
					{
					case ATTACH_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.top = _constraints[c._reference]._pos.bottom+c._offset;
						break;
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.top = _constraints[c._reference]._pos.top+c._offset;
						break;
					case ATTACH_FORM:
						pos.top = formR.top+c._offset;
						break;
					case ATTACH_OPPOSITE_FORM:
						pos.top = formR.bottom+c._offset;
						break;
					case ATTACH_POSITION:
						pos.top = (c._pos*(formR.bottom-formR.top))/_nPosY+c._offset;
						break;
					case ATTACH_SELF:
						pos.top = formR.top+c._offset;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			if (doVLayout)
				//-----------------
				// bottom constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_BOTTOM];
				switch (c._type)
					{
					case ATTACH_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.bottom = _constraints[c._reference]._pos.top+c._offset;
						break;
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						pos.bottom = _constraints[c._reference]._pos.bottom+c._offset;
						break;
					case ATTACH_FORM:
						pos.bottom = formR.bottom+c._offset;
						break;
					case ATTACH_OPPOSITE_FORM:
						pos.bottom = formR.top+c._offset;
						break;
					case ATTACH_POSITION:
						pos.bottom = (c._pos*(formR.bottom-formR.top))/_nPosY+c._offset;
						break;
					case ATTACH_SELF:
						pos.bottom = formR.top+c._offset;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			if (doHLayout)
				//-----------------
				// horizontal center constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_HCENTER];
				switch (c._type)
					{
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						ii = (pos.right-pos.left);
						pos.left = (_constraints[c._reference]._pos.left+_constraints[c._reference]._pos.right-(pos.right-pos.left))/2+c._offset;
						pos.right = pos.left + ii;
						break;
					case ATTACH_FORM:
						ii = (pos.right-pos.left);
						pos.left = (formR.left+formR.right-(pos.right-pos.left))/2+c._offset;
						pos.right = pos.left + ii;
						break;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			if (doVLayout)
				//-----------------
				// vertical center constraint
				//-----------------
				{
				SideConstraint &c = (*wgt).second._constraint[ATTACH_VCENTER];
				switch (c._type)
					{
					case ATTACH_OPPOSITE_WIDGET:
						ATLASSERT(_constraints.find(c._reference) != _constraints.end());
						ii = (pos.bottom-pos.top);
						pos.top = (_constraints[c._reference]._pos.top+_constraints[c._reference]._pos.bottom-(pos.bottom-pos.top))/2+c._offset;
						pos.bottom = pos.top + ii;
						break;
					case ATTACH_FORM:
						ii = (pos.bottom-pos.top);
						pos.top = (formR.top+formR.bottom-(pos.bottom-pos.top))/2+c._offset;
						pos.bottom = pos.top + ii;
						break;
					case ATTACH_NONE:
						break;
					default:
						ATLASSERT(false);
					}
				}
			// now process the ATTACH_NONE constraints
			if (doHLayout)
				{
				if ((*wgt).second._constraint[ATTACH_LEFT]._type == ATTACH_NONE)
					pos.left = pos.right - (opos.right-opos.left);
				if ((*wgt).second._constraint[ATTACH_RIGHT]._type == ATTACH_NONE)
					pos.right = pos.left + (opos.right-opos.left);
				}
			if (doVLayout)
				{
				if ((*wgt).second._constraint[ATTACH_TOP]._type == ATTACH_NONE)
					pos.top = pos.bottom - (opos.bottom-opos.top);
				if ((*wgt).second._constraint[ATTACH_BOTTOM]._type == ATTACH_NONE)
					pos.bottom = pos.top + (opos.bottom-opos.top);
				}
			// made some changes ?
			change = change || (::memcmp(&opos, &pos, sizeof(pos)) != 0);
			}

		if (!change)
			return true;
		}
	ATLTRACE(_T("LayoutMgr<T>::DoLayout: no convergence after %d iterations !!!!!!!!\n"), i);
	return true;
}

// show/hide the grip handle
template <class T>
inline bool LayoutMgr<T>::ShowHandle(bool show)
{
	bool oshow = _showHandle;

	if (_handle == 0)
		{
		T* pT = static_cast<T*>(this);
		_handle.Create(*pT);
		AttachForm(_handle, ATTACH_RIGHT);
		AttachForm(_handle, ATTACH_BOTTOM);
		}
	_showHandle = show;
	_handle.ShowWindow(_showHandle ? SW_SHOW : SW_HIDE);

	return oshow;
}

// Common method called on WM_SIZE messages
template <class T>
inline LRESULT LayoutMgr<T>::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	bHandled = false;
	if ((GET_X_LPARAM(lParam) != 0) && (GET_Y_LPARAM(lParam) != 0))
		{
		if (ComputeLayout())
			{
			DoLayout();
			}
		}
	_prevClientSize.cx = GET_X_LPARAM(lParam);
	_prevClientSize.cy = GET_Y_LPARAM(lParam);
	return 0;
}

// Common method called on WM_GETMINMAXINFO messages
template <class T>
inline LRESULT LayoutMgr<T>::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	MINMAXINFO	*lpMMI = (MINMAXINFO *)lParam;
    lpMMI->ptMinTrackSize.x = _minWindowSize.cx;
    lpMMI->ptMinTrackSize.y = _minWindowSize.cy;
	return 0;
}

// Common method called on WMU_PS_ATTACH_PS messages
template <class T>
inline LRESULT LayoutMgr<T>::OnAttachPropertySheet(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	T* pT = static_cast<T*>(this);

	pT->AttachOppositeWidget((HWND)wParam, ATTACH_LEFT, (HWND)lParam);
	pT->AttachOppositeWidget((HWND)wParam, ATTACH_RIGHT, (HWND)lParam);
	pT->AttachOppositeWidget((HWND)wParam, ATTACH_TOP, (HWND)lParam);
	pT->AttachOppositeWidget((HWND)wParam, ATTACH_BOTTOM, (HWND)lParam);
	return 0;
}

template <class T>
inline void LayoutMgr<T>::DefineLayout()
{
}

// Returns the client area of the container
template <class T>
inline void LayoutMgr<T>::GetDialogRect(LPRECT r)
{
	T* pT = static_cast<T*>(this);
    pT->GetClientRect(r);
}

// This methods returns the offset for positioning the controls in the client rect
template <class T>
inline void LayoutMgr<T>::GetOffset(LPPOINT offset)
{
	offset->x = offset->y = 0;
}

// Excludes the control window rectangles from the DC clipping region
template <class T>
inline LRESULT LayoutMgr<T>::OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = false;
	T* pT = static_cast<T*>(this);
	if (pT->_controlsToClip != 0)
		{
		HDC			dc = (HDC)wParam;
		const UINT	*c = _controlsToClip;
		RECT		rc;
		POINT		dcOffset;

		::GetViewportOrgEx(dc, &dcOffset);
		for(c = pT->_controlsToClip; *c > 0; c++)
			{
			HWND chwnd = pT->GetDlgItem(*c);
			if (chwnd != 0 && IsWindowVisible(chwnd))
				{
				::GetWindowRect(chwnd, &rc);
				pT->ScreenToClient(&rc);
				::OffsetRect(&rc, -dcOffset.x, -dcOffset.y);
				::ExcludeClipRect(dc, rc.left, rc.top, rc.right, rc.bottom);
				}
			}
		}
	return 0;
}

#ifdef __ATLWIN_H__
//-----------------------------------------------------------------------------
// CResizableDialogImplT
//-----------------------------------------------------------------------------
template <class T, class TBase, class DlgBase>
inline CResizableDialogImplT<T, TBase, DlgBase>::CResizableDialogImpl(bool useHandle)
{
	_showHandle = useHandle;
}

// Initalisation of the dialog
template <class T, class TBase, class DlgBase>
inline LRESULT CResizableDialogImplT<T, TBase, DlgBase>::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	T* pT = static_cast<T*>(this);
	if ((pT->GetStyle() & WS_CHILD) != 0)
		{
		// no min size
		_minWindowSize.cx = _minWindowSize.cy = 0;
		_minClientSize.cx = _minClientSize.cy = 0;
		}
	else
		{
		// make sure we have a resizable border
		pT->ModifyStyle(DS_MODALFRAME, WS_THICKFRAME);
		// add the handle
		if (_showHandle)
			{
			ShowHandle(true);
			}
		RECT r;
		bHandled = false;
		pT->GetClientRect(&r);
		_minClientSize.cx = (r.right-r.left);
		_minClientSize.cy = (r.bottom-r.top);
		_prevClientSize = _minClientSize;
		pT->GetWindowRect(&r);
		_minWindowSize.cx = (r.right-r.left);
		_minWindowSize.cy = (r.bottom-r.top);
		}
	pT->DefineLayout();

	return 0;
}

//-----------------------------------------------------------------------------
// CResizableDialogImpl
//-----------------------------------------------------------------------------
template <class T, class TBase>
inline CResizableDialogImpl<T, TBase>::CResizableDialogImpl(bool useHandle)
// Compiler bug : its doesn't support:
// inherited(useHandle) {}
// so we have to recopy the code of inherited(useHandle)
{
	_showHandle = useHandle;
}

#ifndef _ATL_NO_HOSTING
//-----------------------------------------------------------------------------
// CAxResizableDialogImpl
//-----------------------------------------------------------------------------
template <class T, class TBase>
inline CAxResizableDialogImpl<T, TBase>::CAxResizableDialogImpl(bool useHandle)
// Compiler bug : its doesn't support:
// inherited(useHandle) {}
// so we have to recopy the code of inherited(useHandle)
{
	_showHandle = useHandle;
}

#endif // ifndef _ATL_NO_HOSTING

#endif // __ATLWIN_H__

#if defined(__ATLSCRL_H__) && defined(__ATLWIN_H__)
//-----------------------------------------------------------------------------
// CResizableFormViewImpl
//-----------------------------------------------------------------------------
template <class T, class TBase, class DlgBase>
inline void CResizableFormViewImplT<T, TBase, DlgBase>::DoPaint(CDCHandle /*dc*/)
{
	// Just avoid the assertion
}

// Initalisation of the dialog
template <class T, class TBase, class DlgBase>
inline LRESULT CResizableFormViewImplT<T, TBase, DlgBase>::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	T* pT = static_cast<T*>(this);
    RECT r;
	bHandled = false;
    pT->GetClientRect(&r);
    _minClientSize.cx = (r.right-r.left);
    _minClientSize.cy = (r.bottom-r.top);
	_prevClientSize = _minClientSize;
    pT->GetWindowRect(&r);
    _minWindowSize.cx = (r.right-r.left);
    _minWindowSize.cy = (r.bottom-r.top);
	pT->DefineLayout();
	pT->SetScrollSize(_minClientSize);

	return 0;
}

// This methods returns the offset for positioning the controls in the client rect
template <class T, class TBase, class DlgBase>
inline void CResizableFormViewImplT<T, TBase, DlgBase>::GetOffset(LPPOINT offset)
{
	T* pT = static_cast<T*>(this);
	*offset = pT->m_ptOffset;
}

// Returns the client area of the container
template <class T, class TBase, class DlgBase>
inline void CResizableFormViewImplT<T, TBase, DlgBase>::GetDialogRect(LPRECT r)
{
	T* pT = static_cast<T*>(this);
	// NB : GetClientRect returns always a rectangle with left an top are set to 0
    pT->GetClientRect(r);	
	if (r->right < pT->m_sizeAll.cx)
		{
		r->right = pT->m_sizeAll.cx;
		}
	if (r->bottom < pT->m_sizeAll.cy)
		{
		r->bottom = pT->m_sizeAll.cy;
		}
}

#endif // defined(__ATLSCRL_H__) && defined(__ATLWIN_H__)

#if defined(__ATLDLGS_H__) && defined(__ATLWIN_H__)
//-----------------------------------------------------------------------------
// CResizablePropertySheetImpl
//-----------------------------------------------------------------------------
template <bool childWnd, class T, class TBase>
inline CResizablePropertySheetImpl<childWnd, T, TBase>::CResizablePropertySheetImpl(_U_STRINGorID title , UINT uStartPage, HWND hWndParent, bool useHandle)
: CPropertySheetImpl<T, TBase>(title, uStartPage, hWndParent)
{
	_showHandle = useHandle;
}

// Creation of the property sheet
template <bool childWnd, class T, class TBase>
inline void CResizablePropertySheetImpl<childWnd, T, TBase>::OnInitDialog()
{
}

// Creation of the property sheet
template <bool childWnd, class T, class TBase>
inline HWND CResizablePropertySheetImpl<childWnd, T, TBase>::Create(HWND hWndParent)
{
	if (CPropertySheetImpl< T, TBase >::Create(hWndParent) == 0)
		{
		return 0;
		}

	return m_hWnd;
}

// Property sheet callback function
template <bool childWnd, class T, class TBase>
inline int CALLBACK CResizablePropertySheetImpl<childWnd, T, TBase>::PropSheetCallback(HWND hWnd, UINT uMsg, LPARAM lParam)
{
	if(uMsg == PSCB_PRECREATE)
		{
		// Set the right window styles
		DLGTEMPLATE* dlg = (DLGTEMPLATE*) lParam;
		if (childWnd)
			{
			dlg->style &= ~(WS_POPUP|WS_CAPTION|WS_SYSMENU|DS_MODALFRAME);
			dlg->style |= (WS_CHILD|WS_VISIBLE|WS_TABSTOP|DS_CONTROL|DS_3DLOOK);
			dlg->dwExtendedStyle |= WS_EX_CONTROLPARENT;
			}
		else
			{
			dlg->style &= ~(WS_CHILD|DS_MODALFRAME|WS_CLIPCHILDREN);
			dlg->style |= (WS_THICKFRAME);
			}
		}
	else if (uMsg == PSCB_INITIALIZED)
		{
		::PostMessage(hWnd, WMU_PS_INIT, 0, 0);
		}
	return CPropertySheetImpl< T, TBase >::PropSheetCallback(hWnd, uMsg, lParam);
}

// Attach a page
template <bool childWnd, class T, class TBase>
inline LRESULT CResizablePropertySheetImpl<childWnd, T, TBase>::OnAttachPage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND page = (HWND)wParam;
	ATLASSERT(::IsWindow(page));
	// set the constraints for the page
	AttachForm(page, ATTACH_LEFT);
	AttachForm(page, ATTACH_RIGHT);
	AttachForm(page, ATTACH_TOP);
	AttachForm(page, ATTACH_BOTTOM);
	return 0;
}

// Init the property sheet
template <bool childWnd, class T, class TBase>
inline LRESULT CResizablePropertySheetImpl<childWnd, T, TBase>::OnInit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    RECT r;
	T* pT = static_cast<T*>(this);

	bHandled = false;
	if (!childWnd)
		{
		pT->GetClientRect(&r);
		_minClientSize.cx = (r.right-r.left);
		_minClientSize.cy = (r.bottom-r.top);
		_prevClientSize = _minClientSize;
		pT->GetWindowRect(&r);
		_minWindowSize.cx = (r.right-r.left);
		_minWindowSize.cy = (r.bottom-r.top);
		}
	
	pT->SpecificInit();

	// allow specific initialisation by the descendants
	pT->OnInitDialog();
	return 0;
}

// Excludes the control window rectangles and teh tab control from the DC clipping region
template <bool childWnd, class T, class TBase>
inline LRESULT CResizablePropertySheetImpl<childWnd, T, TBase>::OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LayoutMgr<T>::OnEraseBackground(uMsg, wParam, lParam, bHandled);
	
	T			*pT = static_cast<T*>(this);
	HDC			dc = (HDC)wParam;
	POINT		dcOffset;
	RECT		rc;
	HWND		tabwnd;

	bHandled = false;
	::GetViewportOrgEx(dc, &dcOffset);
	tabwnd = pT->GetTabControl();
	ATLASSERT(tabwnd != 0);
	::GetWindowRect(tabwnd, &rc);
	pT->ScreenToClient(&rc);
	::OffsetRect(&rc, -dcOffset.x, -dcOffset.y);
	::ExcludeClipRect(dc, rc.left, rc.top, rc.right, rc.bottom);
	return 0;
}
//=============================================================================
// CChildResizablePropertySheetImpl
//=============================================================================
template <class T, class TBase>
CChildResizablePropertySheetImpl<T, TBase>::CChildResizablePropertySheetImpl(UINT placeHolderID, _U_STRINGorID title, UINT uStartPage, HWND hWndParent, bool useHandle)
: CResizablePropertySheetImpl<true, T, TBase>(title, uStartPage, hWndParent, useHandle), m_ID_Place_Holder(placeHolderID)
{
}

// Specific intialisation depending on whether or not the property sheet is a child window
template <class T, class TBase>
inline void CChildResizablePropertySheetImpl<T, TBase>::SpecificInit()
{
	const UINT stdIDs[] = {
		ID_WIZNEXT, ID_WIZFINISH, ID_WIZBACK, ID_WIZNEXT, ID_WIZFINISH+1,
		IDOK, IDCANCEL,	ID_APPLY_NOW, IDHELP,
		-1
		};

	const UINT	*id;
	T			*pT = static_cast<T*>(this);
	CWindow parent = pT->GetParent();
	CWindow tab = pT->GetTabControl();
	CWindow actPg = pT->GetActivePage();
	ATLASSERT(parent != 0);
	ATLASSERT(tab != 0);
	ATLASSERT(actPg != 0);
	// Allows tab navigation in the parent
	parent.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	// Destroy the standard buttons
	for(id = stdIDs; *id != -1; id++)
		{
		CWindow btn = pT->GetDlgItem(*id);
		if (btn != 0) { btn.DestroyWindow(); }
		}
	// Get relative position of the tab control and of the active page
	RECT rTC, rAP;
	tab.GetWindowRect(&rTC);
	actPg.GetWindowRect(&rAP);
	// Move and resize the window and the tab control
	CWindow ph = parent.GetDlgItem(m_ID_Place_Holder);
	ATLASSERT(ph.IsWindow());
	RECT cr;
	ph.GetWindowRect(&cr);
	parent.ScreenToClient(&cr);
	pT->SetWindowPos(0, &cr, SWP_NOZORDER|SWP_NOACTIVATE);
	// resize the tab control
	tab.SetWindowPos(0, 0, 0, cr.right-cr.left, cr.bottom-cr.top, SWP_NOZORDER|SWP_NOACTIVATE);
	// we can now set the constraints for the tabControl
	pT->AttachForm(tab, ATTACH_LEFT);
	pT->AttachForm(tab, ATTACH_RIGHT);
	pT->AttachForm(tab, ATTACH_TOP);
	pT->AttachForm(tab, ATTACH_BOTTOM);
	// and finally resize the active page
	actPg.SetWindowPos(0, 
		rAP.left-rTC.left,
		rAP.top-rTC.top,
		cr.right-cr.left-(rTC.right-rAP.right)-(rAP.left-rTC.left),
		cr.bottom-cr.top-(rTC.bottom-rAP.bottom)-(rAP.top-rTC.top),
		SWP_NOZORDER|SWP_NOACTIVATE);
	// we must reset the constraints
	pT->AttachForm(actPg, ATTACH_LEFT);
	pT->AttachForm(actPg, ATTACH_RIGHT);
	pT->AttachForm(actPg, ATTACH_TOP);
	pT->AttachForm(actPg, ATTACH_BOTTOM);
	// attach the PS to the prent
	parent.SendMessage(WMU_PS_ATTACH_PS, (WPARAM)pT->m_hWnd, (LPARAM)ph.m_hWnd);

}

//=============================================================================
// CPopupResizablePropertySheetImpl
//=============================================================================
template <class T, class TBase>
CPopupResizablePropertySheetImpl<T, TBase>::CPopupResizablePropertySheetImpl(_U_STRINGorID title, UINT uStartPage, HWND hWndParent, bool useHandle)
: CResizablePropertySheetImpl<false, T, TBase>(title, uStartPage, hWndParent, useHandle)
{
}

// Specific intialisation depending on whether or not the property sheet is a child window
template <class T, class TBase>
inline void CPopupResizablePropertySheetImpl<T, TBase>::SpecificInit()
{
	const UINT stdIDs[] = {
		ID_WIZNEXT, ID_WIZFINISH, ID_WIZBACK, ID_WIZNEXT, ID_WIZFINISH+1,
		IDOK, IDCANCEL,	ID_APPLY_NOW, IDHELP,
		-1
		};
	T			*pT = static_cast<T *>(this);
	CWindow		tab = pT->GetTabControl();
	// we can now set the constraints for the tabControl
	pT->AttachForm(tab, ATTACH_LEFT);
	pT->AttachForm(tab, ATTACH_RIGHT);
	pT->AttachForm(tab, ATTACH_TOP);
	pT->AttachForm(tab, ATTACH_BOTTOM);
	// set the constraints for the standard buttons
	const UINT	*id;
	HWND		lmW = 0;
	int			xmax = 0;
	RECT		r;
	for (id = stdIDs; *id != -1; id++)
		{
		HWND hwnd = pT->GetDlgItem(*id);
		// some buttons as the help button are created even if they are not used
		// to know if they are used, we look at he WS_VISIBLE style.
		if ((hwnd != 0) && ((::GetWindowLong(hwnd, GWL_STYLE) & WS_VISIBLE) != 0))
			{
			pT->AttachForm(hwnd, ATTACH_BOTTOM);
			pT->AttachForm(hwnd, ATTACH_RIGHT);
			::GetWindowRect(hwnd, &r);
			if (r.right >= xmax)
				{
				xmax = r.right;
				lmW = hwnd;
				}
			}
		}
	if (_showHandle)
		{
		// create the handle
		pT->ShowHandle(true);
		// and place the left most button over the handle
		if (lmW)
			::SetWindowPos(lmW, pT->_handle, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
		}
}

//-----------------------------------------------------------------------------
// CResizablePropertyPageImplT
//-----------------------------------------------------------------------------
template <class T, class TBase, class dialogBase>
inline CResizablePropertyPageImplT<T, TBase, dialogBase>::CResizablePropertyPageImplT(_U_STRINGorID title)
: dialogBase(title), _init(false)
{
}

// Initalisation of the dialog
template <class T, class TBase, class dialogBase>
inline LRESULT CResizablePropertyPageImplT<T, TBase, dialogBase>::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = false;
	T* pT = static_cast<T*>(this);
	pT->DefineLayout();
	return 0;
}

// Page Activation
template <class T, class TBase, class dialogBase>
inline BOOL CResizablePropertyPageImplT<T, TBase, dialogBase>::OnSetActive()
{
	if (!_init)
		{
		::SendMessage(GetParent(), WMU_PS_ATTACH_PAGE, (WPARAM)m_hWnd, 0);
		_init = true;
		}
	return true;
}

//-----------------------------------------------------------------------------
// CResizablePropertyPageImpl
//-----------------------------------------------------------------------------
template <class T, class TBase>
inline CResizablePropertyPageImpl<T, TBase>::CResizablePropertyPageImpl(_U_STRINGorID title)
: inherited(title)
{
}

#ifndef _ATL_NO_HOSTING
//-----------------------------------------------------------------------------
// CAxResizablePropertyPageImpl
//-----------------------------------------------------------------------------
template <class T, class TBase>
inline CAxResizablePropertyPageImpl<T, TBase>::CAxResizablePropertyPageImpl(_U_STRINGorID title)
: inherited(title)
{
}

#endif // ifndef _ATL_NO_HOSTING

#endif // defined(__ATLDLGS_H__) && defined(__ATLWIN_H__)

#endif // !defined(__layoutmgr_h__)
