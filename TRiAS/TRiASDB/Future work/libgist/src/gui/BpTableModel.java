// BpTableModel.java
// Copyright (c) 1998, Regents of the University of California
// $Header: /usr/local/devel/GiST/libgist/src/gui/BpTableModel.java,v 1.3 2000/03/15 00:23:57 mashah Exp $

import javax.swing.*;
import javax.swing.table.*;
import java.awt.event.*;
import java.awt.*;
import java.util.*;
import java.lang.String;

/* 
 * Implements a table model for the JTable in the breakpoint editing dialog
 */
class BpTableModel extends AbstractTableModel
{

static String[] colNames = {"ID", "Event", "Node", "Param 1", "Param 2", "Trace", "Enabled"};
    // for JTable
static Vector bps; // our data
static Vector updatedBps; // save original entries here if the user changes anything

public 
BpTableModel(Vector data, Vector updatedData)
{
    bps = data;
    updatedBps = updatedData;
}

// return the event belonging to the given descriptor
static private int
eventNo(String descr)
{
    int i = 0;
    while (i < BreakInfo.eventDescrs.length &&
            descr.compareTo(BreakInfo.eventDescrs[i]) != 0) {
        i++;
    }
    return i;
}


public int
getColumnCount()
{
    return colNames.length;
}

public int
getRowCount()
{
    return bps.size();
}

public Object
getValueAt(int row, int col)
{
    Breakpoint bp = (Breakpoint) bps.elementAt(row);
    if (col == 0) {
	return Integer.toString(bp.id);
    } else if (col == 1) {
	return BreakInfo.eventDescrs[bp.event];
    } else if (col == 2) {
	if (bp.nodeId == 0) {
	    return "";
	} else {
	    return Integer.toString(bp.nodeId);
	}
    } else if (col == 3) {
	return bp.param1;
    } else if (col == 4) {
	return bp.param2;
    } else if (col == 5) {
	return bp.trace;
    } else { 
	return bp.enabled;
    }
}

public String
getColumnName(int col)
{
    return colNames[col];
}

public Class
getColumnClass(int col)
{
    return getValueAt(0, col).getClass();
}

public boolean
isCellEditable(int row, int col)
{
    return (col == 0 ? false : true);
}

// change the data value and save the original breakpoint
public void
setValueAt(Object val, int row, int col)
{
    Breakpoint bp = (Breakpoint) bps.elementAt(row);
    if (!bp.updated) {
        // stash a copy of the original settings of this breakpoint away, just in case
	// the user decides to hit "Cancel" later on
	bp.updated = true;
	updatedBps.addElement(bp.deepCopy());
    }
    if (col == 1) {
	bp.event = eventNo((String) val);
    } else if (col == 2) { // JTextField returns a String
	if (((String) val).equals("")) {
	    bp.nodeId = 0; // no node = node 0
	}
	try {
	    bp.nodeId = Integer.parseInt((String) val);
	} catch (NumberFormatException e) {
	    // leave old value in place
	}
    } else if (col == 3) {
	bp.param1 = (String) val;
    } else if (col == 4) {
	bp.param2 = (String) val;
    } else if (col == 5) {
	bp.trace = (Boolean) val;
    } else if (col == 6) {
	bp.enabled = (Boolean) val;
    }
}

// new stuff
public void
setAllEnabled(boolean enabled)
{
    // set all breakpoints to enabled
    for (int row = 0; row < bps.size(); row++) {
        setValueAt(new Boolean(enabled), row, 6);
	fireTableCellUpdated(row, 6);
    }
}

public void
bpAdded()
{
    fireTableRowsInserted(bps.size()-1, bps.size()-1);
}

public void
bpDeleted(int row)
{
    fireTableRowsDeleted(row, row);
}

// everything changed
public void
reset(Vector data)
{
    if (data != null) {
	// there's a new set of breakpoints
        bps = data;
    }
    fireTableDataChanged();
}

}
