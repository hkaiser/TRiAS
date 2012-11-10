/*
 *  XmFormLayout.java $Revision: 1.1 $ (a Java layout manager 
 *  for AWT 1.0 which was inspired by the Motif XmForm widget)
 *  Copyright (C) 1997 Softbear Inc.  (info@softbear.com)
 *  Latest version at http://www.softbear.com/java/xmformlm
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
*/

/*
 *  This layout manager WILL work with AWT 1.1 because AWT 1.1 is backward
 *  compatible with AWT 1.0.  However, if you compile with the -deprecated
 *  switch (or its equivalent) you will see that this layout manager does
 *  use some deprecated AWT 1.0 APIs.
 *
 *  Ben Hill (ben@opnsys.com) notes that you can port to pure AWT 1.1
 *  (which is incompatible with AWT 1.0) by performing the following
 *  substitutions (see lines marked with "AWT 1.1" in the code below):
 *
 *    preferredSize changed to getPreferredSize
 *    insets changed to getInsets
 *    size changed to getSize
 *    reshape changed to setBounds
 *    
*/



/*
 *	The XmFormLayout lays out components according to
 *	a list of constraints.
 *
 *	Example 1: Fixed coordinates (form-relative). 
 *	=============================================
 *	The following constraints will cause the component named "foo"
 *	to be positioned at the point (x=10, y=10).
 *
 *		String constraints[] = {
 *			"foo.top=form.top+10",
 *			"foo.left=form.left+10"
 *		};
 *
 *	Example 2: Relative coordinates
 *	===============================
 *	The following constraints will cause the component named
 *	"bar" to be positioned to the right of "foo" and made wide
 *	enough to reach the right side of the form.
 *
 *		String constraints[] = {
 *			"foo.top=form.top+10",
 *			"foo.left=form.left+10",
 *			"bar.top=foo.top",
 *			"bar.left=foo.right+10",
 *			"bar.right=form.right-10"
 *		};
 *
 *	Note: in order to understand the runtime operation (or errors)
 *	in the code below, you may need to uncomment-out debug statements.
*/

public class XmFormLayout implements java.awt.LayoutManager {

	/*
	 *	Component tuple constants, these must range from 0...9.
	 *	Attribute numbers must range from BOTTOM...TOP.
	*/
	private final static int	COMPONENT = 0;
	private final static int	BOTTOM = 1;
	private final static int	LEFT = 2;
	private final static int	HCENTER = 3;
	private final static int	VCENTER = 4;
	private final static int	RIGHT = 5;
	private final static int	TOP = 6;
	private final static int	BITSET = 7;
	private final static int	DIMENSION = 8;
	private final static int	NAME = 9;


	/*
	 *	Other constants.
	*/
	private final static int	FORM = -32765;
	private final static int	INVALID = -32766;
	private final static int	UNBOUND = -32767;
	private final static boolean	m_debug = false;
	private final static boolean	m_bigDebug = false;

	/*
	 *	The constraints and the results of the
	 *	last reshape() computations.
	*/
	private String			m_myName;
	private java.awt.Dimension	m_formDimensions; // (as of last reconstrain)
	private java.awt.Point		m_formLocation;	// (as of last reconstrain)
	private java.util.Vector	m_tuples;	// (4 attrs, component, bitset)
	private java.util.Hashtable	m_nameToIndex;
	private String			m_constraints[];
	private boolean			m_changedFlag;

	/*
	 *	Add a component.
	*/
	public void addLayoutComponent(String name, java.awt.Component component) {
		if (m_debug) {
			System.out.println(m_myName + "'addLayoutComponent('" + name + "')...\n");
		}
		Object tuple[] = new Object[10];
		tuple[XmFormLayout.COMPONENT] = component;
		tuple[XmFormLayout.BITSET] = new java.util.BitSet();
		tuple[XmFormLayout.NAME] = name;
		int componentNr = m_tuples.size();
		m_tuples.addElement(tuple);
		m_nameToIndex.put(name, new Integer(componentNr));
		m_changedFlag = true;
	}

	/*
	 *	Parses an expression 'a.b+c' (or 'a.b-c' or 'a.b' or
	 *	'+c' or '-c') into an rvalue 'a.b' and a signed
	 *	number 'c'.  If the rvalue is unbound then return
	 *	XmFormLayout.UNBOUND, otherwise return the value of
	 *	the expression.
	*/
	private final int evaluate(String expression) throws Exception {
		int i, s = 1, v = 0;
		if (m_debug) {
			System.out.println(m_myName + "'evaluate() expr: " +
				expression + "\n");
		}

		i = expression.indexOf('+');
		if (i == -1) {
			i = expression.indexOf('-');
			s = -1;
		}

		if (i == -1) {
			v = this.getAttr(expression);
		} else if (i > 1) {
			String rvalue = expression.substring(0, i);
			v = this.getAttr(rvalue);
		}

		if (i != -1 && v != XmFormLayout.UNBOUND) {
			String unicodeNumber = expression.substring(i+1);
			int number = Integer.parseInt(unicodeNumber, 10);
			v += (s*number);
		}

		return v;
	}

	/*
	 *	Enforce explicit constraints by binding lvalues and
	 *	also marking those lvalues which can't be bound.
	 *	Parses an explicit constraint 'a.b=c.d+e' into
	 *	an lvalue 'a.b' and an expression 'c.d+e'.
	 *	Returns true if all possible explicit lvalues are bound.
	*/
	private final boolean explicit(java.util.BitSet constraintBitset) throws Exception {

		if (m_debug) {
			System.out.println(m_myName + "'explicit()...\n");
		}

		boolean deferFlag = false;
		if (m_constraints == null || m_constraints.length == 0) {
			throw new Exception("no constraints (explicit)");
		}
		for (int i = 0; i < m_constraints.length; ++i) {
			if (constraintBitset.get(i)) {
				continue;
			}
			String constraint = m_constraints[i];

			if (m_debug) {
				System.out.println(m_myName + "'explicit() constraint: " + constraint + "\n"); 
			}

			int j = constraint.indexOf('=');
			if (j < 3) {
				throw new Exception("invalid constraint, expected '=': " + constraint + "(explicit)");
			}
			String lvalue =  constraint.substring(0, j);
			String expression =  constraint.substring(j+1);
			if (this.setAttr(lvalue, this.evaluate(expression))) {
				constraintBitset.set(i);
			} else {
				deferFlag = true;
			}
		}
		return !deferFlag;
	}

	/*
	 *	If the attribute is bound then return its'
	 *	value, otherwise return XmFormLayout.UNBOUND.
	*/
	private final int getAttr(int componentNr, int attrNr) {
/*
		if (m_bigDebug) {
			System.out.println(m_myName + "'getAttr(): c=" +
				componentNr + ", a=" + attrNr + "\n");
		}
*/
		int v = XmFormLayout.UNBOUND;
		if (componentNr == XmFormLayout.FORM) {
			if (attrNr == XmFormLayout.BOTTOM) {
				v = m_formLocation.y +
					m_formDimensions.height;
			} else if (attrNr == XmFormLayout.LEFT) {
				v = m_formLocation.x;
			} else if (attrNr == XmFormLayout.HCENTER) {
				v = m_formLocation.x + m_formDimensions.width/2;
			} else if (attrNr == XmFormLayout.VCENTER) {
				v = m_formLocation.y + m_formDimensions.height/2;
			} else if (attrNr == XmFormLayout.RIGHT) {
				v = m_formLocation.x +
					m_formDimensions.width;
			} else if (attrNr == XmFormLayout.TOP) {
				v = m_formLocation.y;
			}
		} else if (isBound(componentNr, attrNr)) {
			Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
			v = ((Integer) tuple[attrNr]).intValue();
		}
		return v;
	}

	/*
	 *	If the attribute is bound then return its'
	 *	value, otherwise return XmFormLayout.UNBOUND.
	*/
	private final int getAttr(String fqAttrName) throws Exception {
		int tuple[] = this.parseAttr(fqAttrName);
		int value = this.getAttr(tuple[0], tuple[1]);

		if (m_debug) {
			System.out.println(m_myName + "'getAttr(): fqAttr=" +
				fqAttrName + ", value=" + value + "\n");
		}

		return value;
	}

	private final int getAttrNr(String attrName) { 
/*
		if (m_bigDebug) {
			System.out.println(m_myName + "'getAttrNr() attr: " +
				attrName + "\n");
		}
*/
		int attrNr = XmFormLayout.INVALID; // invalid attr # (never happens)
		if (attrName.equals("bottom")) {
			attrNr = XmFormLayout.BOTTOM;
		} else if (attrName.equals("left") || attrName.equals("x")) {
			attrNr = XmFormLayout.LEFT;
		} else if (attrName.equals("hcenter") || attrName.equals("c")) {
			attrNr = XmFormLayout.HCENTER;
		} else if (attrName.equals("vcenter")) {
			attrNr = XmFormLayout.VCENTER;
		} else if (attrName.equals("right")) {
			attrNr = XmFormLayout.RIGHT;
		} else if (attrName.equals("top") || attrName.equals("y")) {
			attrNr = XmFormLayout.TOP;
		}
		return attrNr;
	}

	private final java.util.BitSet getBitset(int componentNr) {
		Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
		return (java.util.BitSet) tuple[XmFormLayout.BITSET];
	}

	private final java.awt.Component getComponent(int componentNr) {
		Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
		return (java.awt.Component) tuple[XmFormLayout.COMPONENT];
	}

	private final String getComponentName(int componentNr) {
		Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
		return (String) tuple[XmFormLayout.NAME];
	}

	private final int getComponentNr(String componentName) throws Exception {
/*
		if (m_bigDebug) {
			System.out.println(m_myName +
				"'getComponentNr() attr: " +
				componentName + "\n");
		}
*/
		Object n = m_nameToIndex.get(componentName);
		if (n == null) {
			/*
			 *	This exception occurs if there is a component
			 *	mentioned in the constraints that isn't
			 *	also in the form.  There are two common
			 *	reasons for this:
			 *
			 *	 1. The "add(name, component)" method was
			 *	 never called, or was called with the
			 *	 wrong name; or
			 *
			 *	 2. The same component was added twice but
			 *	 with a different name (the second name
			 *	 will automatically remove the first name).
			 *
			*/
			throw new Exception("component not found: '" +
				componentName + "' (getComponentNr)");
		}
		return ((Integer)n).intValue();
	}

	/*
	 *	Returns the preferred dimension of the specified
	 *	component.  Results are cached for greater efficiency.
	*/
	private final java.awt.Dimension getDimension(int componentNr) {
		Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
		java.awt.Dimension dimension;
		if (tuple[XmFormLayout.DIMENSION] == null) {
			java.awt.Component component = (java.awt.Component) tuple[XmFormLayout.COMPONENT];
			dimension = component.getPreferredSize(); // For AWT 1.1, use "component.getPreferredSize()"
			tuple[XmFormLayout.DIMENSION] = (Object) dimension; 
		} else {
			dimension = (java.awt.Dimension) tuple[XmFormLayout.DIMENSION];
		}
		return dimension;
	}

	/*
	 *	Returns the preferred offset (width or height)
	 *	between the specified attribute and its' opposite.
	*/
	private final int getOppsOffset(int componentNr, int attrNr) {
		int offset = XmFormLayout.INVALID; // invalid offset (never happens)
		java.awt.Dimension componentDimensions = this.getDimension(componentNr);

		if (attrNr == XmFormLayout.BOTTOM) {
			offset = -componentDimensions.height;
		} else if (attrNr == XmFormLayout.LEFT) {
			offset = componentDimensions.width;
		} else if (attrNr == XmFormLayout.RIGHT) {
			offset = -componentDimensions.width;
		} else if (attrNr == XmFormLayout.TOP) {
			offset = componentDimensions.height;
		}
		return offset;
	}

	/*
	 *	Returns the preferred offset (width or height)
	 *	between the specified attribute and its' relative.
	*/
	private final int getRelsOffset(int componentNr, int attrNr) {
		int offset = XmFormLayout.INVALID; // invalid offset (never happens)
		java.awt.Dimension componentDimensions = this.getDimension(componentNr);

		if (attrNr == XmFormLayout.HCENTER) {
			offset = -componentDimensions.width/2;
		} else if (attrNr == XmFormLayout.LEFT) {
			offset = componentDimensions.width/2;
		} else if (attrNr == XmFormLayout.TOP) {
			offset = componentDimensions.height/2;
		} else if (attrNr == XmFormLayout.VCENTER) {
			offset = -componentDimensions.height/2;
		}
		return offset;
	}


	/*
	 *	Enforces implicit constraints by binding component
	 *	attributes which haven't an lvalue in ANY explicit
	 *	constraint and whose opposite attribute is already
	 *	bound, e.g. if foo.top isn't an lvalue in any explicit
	 *	constraint, and foo.bottom is bound, and foo has a
	 *	preferred height of 123, then enforce this implicit
	 *	constraint:
	 *		 "foo.top=foo.bottom-123"
	 *	Returns true if all possible implicit constraints are bound.
	*/
	private final boolean implicit() throws Exception {

		if (m_debug) {
			System.out.println(m_myName + "'implicit()...\n");
		}

		boolean deferFlag = false;
		for (int c = 0; c < m_tuples.size(); ++c) {
			for (int a = XmFormLayout.BOTTOM; a <= XmFormLayout.TOP; ++a) {
				if (this.isMarked(c, a) == false) {

					if (m_debug) {
						System.out.println(m_myName +
							"'implicit(): c=" +
							 c + ", a=" + a + "\n"); 
					}

					int r = this.relative(a);
					if (r != XmFormLayout.INVALID && this.isBound(c, r) == true) {
						// this also marks the attr 
						this.setAttr(c, a, this.getAttr(c, r) + this.getRelsOffset(c, r));
					} else {
						int o = this.opposite(a);
						if (o != XmFormLayout.INVALID && this.isBound(c, o) == true) {
							// this also marks the attr 
							this.setAttr(c, a, this.getAttr(c, o) + this.getOppsOffset(c, o));
						} else {
							deferFlag = true;
						}
					}
				}
			}
		}
		return !deferFlag;
	}

	/*
	 *	Returns true if this component's attribute was
	 *	bound; that is, if this.setAttr() was called.
	*/
	private final boolean isBound(int componentNr, int attributeNr) {
		java.util.BitSet bitset = this.getBitset(componentNr);
		return bitset.get(attributeNr);
	}

	/*
	 *	Returns true if this component's attribute is
	 *	an lvalue in any explicit constraint; that is,
	 *	if this.setMarked() was called.
	*/
	private final boolean isMarked(int componentNr, int attributeNr) {
		java.util.BitSet bitset = this.getBitset(componentNr);
		return bitset.get(attributeNr + (XmFormLayout.TOP+1));
	}

	/*
	 *	Reshape all components in the container.  Typically,
	 *	this causes a call to this.reconstrain() only the first time.
	*/
	public void layoutContainer(java.awt.Container parent) {
		java.awt.Dimension dummy = this.preferredLayoutSize(parent); // reconstrain if necessary

		if (m_debug) {
			System.out.println(m_myName +
				"'layoutContainer(): w=" + dummy.width +
				", h=" + dummy.height + ", changedFlag=" +
				m_changedFlag + " (should be false)\n");
		}

		if (!m_changedFlag) {
			for (int c = 0; c < m_tuples.size(); ++c) {
				Object tuple[] = (Object[]) m_tuples.elementAt(c);
				int x = ((Integer)tuple[XmFormLayout.LEFT]).intValue();
				int y = ((Integer)tuple[XmFormLayout.TOP]).intValue();
				int w = ((Integer)tuple[XmFormLayout.RIGHT]).intValue() - x;
				int h = ((Integer)tuple[XmFormLayout.BOTTOM]).intValue() - y;

				if (m_debug) {
					System.out.println(m_myName + "'layoutContainer(): c=" +
						(String)tuple[XmFormLayout.NAME] + ", x=" + x +
						", y=" + y + ", w=" + w + ", h=" + h + "\n");
				}

				java.awt.Component component = (java.awt.Component) tuple[XmFormLayout.COMPONENT];
				component.setBounds(x, y, w, h);  // For AWT 1.1, use "component.setBounds(...)"
			}
		}
	}

	/*
	 *	XmFormLayout knowns only one size (the preferred size).
	*/
	public java.awt.Dimension minimumLayoutSize(java.awt.Container parent) {
		return preferredLayoutSize(parent);
	}

	private final int opposite(int attrNr) {
		int oppositeAttrNr = XmFormLayout.INVALID; // attr doesn't have an opposite

		if (attrNr == XmFormLayout.BOTTOM) {
			oppositeAttrNr = XmFormLayout.TOP;
		} else if (attrNr == XmFormLayout.LEFT) {
			oppositeAttrNr = XmFormLayout.RIGHT;
		} else if (attrNr == XmFormLayout.RIGHT) {
			oppositeAttrNr = XmFormLayout.LEFT;
		} else if (attrNr == XmFormLayout.TOP) {
			oppositeAttrNr = XmFormLayout.BOTTOM;
		}
		return oppositeAttrNr;
	}


	/*
	 *	Parse a fully-qualified attribute name 'a.b' into
	 *	a component 'a' and an attribute 'b', and return
	 *	the component number and attribute number.
	*/
	private final int[] parseAttr(String fqAttrName) throws Exception {
		int i = fqAttrName.indexOf('.');
		if (i < 1) {
			throw new Exception(m_myName +
				"invalid attribute, expected '.': '" + fqAttrName + "' (parseAttr)");
		}
		String componentName = fqAttrName.substring(0, i);
		String attrName = fqAttrName.substring(i+1);
		int tuple[] = new int[2];
		if (componentName.equals("form")) {
			tuple[0] = XmFormLayout.FORM;
		} else {
			tuple[0] = this.getComponentNr(componentName);
		}
		tuple[1] = this.getAttrNr(attrName);
		return tuple;
	}

	public java.awt.Dimension preferredLayoutSize(java.awt.Container parent) {
		java.awt.Insets insets = parent.getInsets(); // For AWT 1.1, use "parent.getInsets()"
		int dx = insets.left + insets.right;
		int dy = insets.top + insets.bottom;

		if (m_debug) {
			System.out.println(m_myName +
				"'preferredLayoutSize(): dx=" +
				dx + ", dy=" + dy + "\n");
		}

		int x = insets.left;
		int y = insets.top;
		int w = parent.getSize().width - dx;  // For AWT 1.1, use "parent.getSize()"
		int h = parent.getSize().height - dy;  // For AWT 1.1, use "parent.getSize()"
		this.setBounds(x, y, w, h);

		return new java.awt.Dimension(m_formDimensions.width + dx,
			m_formDimensions.height + dy);
	}

	private final int relative(int attrNr) {
		int relativeAttrNr = XmFormLayout.INVALID; // attr doesn't have a relative

		if (attrNr == XmFormLayout.HCENTER) {
			relativeAttrNr = XmFormLayout.LEFT;
		} else if (attrNr == XmFormLayout.LEFT) {
			relativeAttrNr = XmFormLayout.HCENTER;
		} else if (attrNr == XmFormLayout.TOP) {
			relativeAttrNr = XmFormLayout.VCENTER;
		} else if (attrNr == XmFormLayout.VCENTER) {
			relativeAttrNr = XmFormLayout.TOP;
		}
		return relativeAttrNr;
	}


	/*
	 *	Removes a component.  This isn't particularly fast,
	 *	but it is rarely called, if ever.
	*/
	public void removeLayoutComponent(java.awt.Component oldComponent) {
		int nrComponents = m_tuples.size();
		for (int c = 0; c < nrComponents; ++c) {
			if (this.getComponent(c) == oldComponent) {
				String componentName = this.getComponentName(c);

				if (m_debug) {
					System.out.println(m_myName + "'removeLayoutComponent('" + componentName + "')...\n");
				}

				m_nameToIndex.remove(componentName);
				m_changedFlag = true;
			}
		}
	}

	/*
	 *	Layout the container according to constraints.
	 *	This may be time-consuming, so it should only be
	 *	done if changedFlag is true.
	*/
	private final void reconstrain() throws Exception {
		java.util.BitSet constraintBitset = new java.util.BitSet(); 
		for (int c = 0; c < m_tuples.size(); ++c) {
			Object tuple[] = (Object[]) m_tuples.elementAt(c);
			tuple[XmFormLayout.DIMENSION] = null; // component's preferred size may have changed
			java.util.BitSet componentBitset = (java.util.BitSet) tuple[XmFormLayout.BITSET];

			/*
			 *	The componentBitset has no clearAllBits()
			 *	method so AND with any blank bitset to clear it.
			*/
			componentBitset.and(constraintBitset);
		}
		boolean deferFlag;
		int nrTries = 0;
		do {

			if (m_debug) {
				System.out.println(m_myName + "'reconstrain(): iteration=" + (nrTries+1) + "*****\n");
			}

			deferFlag = false;
			if (! this.explicit(constraintBitset)) {
				deferFlag = true;
			}
			if (! this.implicit()) {
				deferFlag = true;
			}
		} while (deferFlag && ++nrTries < 30);

		if (deferFlag) {
			throw new Exception("possible cycle in constraints, failed after " +
				nrTries + " iterations (reconstrain)");
		}
		m_changedFlag = false;
	}

	/*
	 *	If the container's location or shape has
	 *	changed, or if any of the component's have
	 *	changed, then re-compute the constraints;
	 *	otherwise use what was already computed.
	*/
	private final void setBounds(int x, int y, int w, int h) {
		if (m_formDimensions.width != w ||
				m_formDimensions.height != h) {

			if (m_debug) {
				System.out.println(m_myName +
					"'setBounds(): ***SIZE CHANGED*** w=" +
					w + ", h=" + h + " *******\n"); 
			}

			m_formDimensions.width = w;
			m_formDimensions.height = h;
			m_changedFlag = true;
		}
		if (m_formLocation.x != x ||
				m_formLocation.y != y) {
			m_formLocation.x = x;
			m_formLocation.y = y;
			m_changedFlag = true;
		}
		if (m_changedFlag) {
			try {
				this.reconstrain();
			} catch (Exception exception) {
				System.out.println(m_myName +
						" error: " +
						exception.getMessage() + "\n"); 
			}
		}
	}

	/*
	 *	Try to set a attribute; returns true if the was set
	 *	or false if it was deferred (the latter will happen
	 *	if the value is XmFormLayout.UNBOUND).
	*/
	private final boolean setAttr(int componentNr, int attrNr, int value) throws Exception {

		if (m_debug) {
			System.out.println(m_myName +
				"'setAttr(): c=" + componentNr + ", a=" +
				attrNr + ", v=" + value + "\n");
		}

		if (componentNr == XmFormLayout.FORM) {
			throw new Exception("invalid constraint, can't set attributes of form (setAtttr)");
		}
		this.setMarked(componentNr, attrNr);
		boolean boundFlag = false;
		if (value != XmFormLayout.UNBOUND) {
			Object tuple[] = (Object[]) m_tuples.elementAt(componentNr);
			tuple[attrNr] = new Integer(value);
			this.setBound(componentNr, attrNr);
			boundFlag = true;
		}
		return boundFlag;
	}

	/*
	 *	Try to set a attribute 'c.a'; returns true if the
	 *	was set or false if it was deferred (the latter
	 *	will happen if the value is XmFormLayout.UNBOUND).
	*/
	private final boolean setAttr(String fqAttrName, int value) throws Exception {

		if (m_debug) {
			System.out.println(m_myName + "'setAttr() fqAttr=" +
				fqAttrName + ", value=" + value + "\n");
		}

		int tuple[] = this.parseAttr(fqAttrName);
		return this.setAttr(tuple[0], tuple[1], value);
	}

	private final void setBound(int componentNr, int attrNr) {
/*
		if (m_bigDebug) {
			System.out.println(m_myName + "'setBound(): c=" +
				componentNr + ", a=" + attrNr + "\n");
		}
*/
		java.util.BitSet bitset = this.getBitset(componentNr);
		bitset.set(attrNr);
	}

	private final void setMarked(int componentNr, int attrNr) {
		java.util.BitSet bitset = this.getBitset(componentNr);
		bitset.set(attrNr + (XmFormLayout.TOP+1));
	}

	/*
	 *	The constructor.
	*/
	public XmFormLayout(String newConstraints[]) {
		m_myName = (((Object) this).getClass()).getName();

		if (m_debug && newConstraints == null) {
			System.out.println(m_myName +
				"'XmFormLayout() newConstraints is null!\n"); 
		}

		m_constraints = newConstraints;
		m_formDimensions = new java.awt.Dimension(0,0);
		m_formLocation = new java.awt.Point(0,0);
		m_nameToIndex = new java.util.Hashtable();
		m_tuples = new java.util.Vector();
		m_changedFlag = true;
	}
}
