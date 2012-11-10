// Breakpoints.java
// Copyright (c) 1998, Regents of the University of California
// $Id: Breakpoints.java,v 1.3 1999/09/27 01:09:49 marcel Exp $

import javax.swing.*;
import javax.swing.table.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/* 
 * Breakpoints:
 *
 * Java interface to the C++ breakpoints for libgist. Manages the active set of breakpoints
 * and lets the user edit them.
 */

class Breakpoints
{

static public Hashtable bpIndex = new Hashtable(); // breakpoints, indexed on id
static Vector bps = new Vector(); // all breakpoints
static JTable tableView;
static JComboBox eventBox;
static JScrollPane scrollpane;
static JPanel btnPanel;
static JDialog frame;
static BpTableModel dataModel;
static JFrame parent;
static Vector deletedBps = new Vector();
    // collection of deleted breakpoints (put back by Cancel)
static Vector updatedBps = new Vector();
    // collection of updated breakpoints (restored by Cancel)

static public void
setParent(JFrame p)
{
    parent = p;
}

// return Breakpoint with given ID
static public Breakpoint
lookup(int id)
{
    return (Breakpoint) bpIndex.get(new Integer(id));
}

// save the current set of breakpoints
static public void
save(ObjectOutputStream s) throws IOException
{
    s.writeObject(bps);
}

// installs current breakpoints in the C++ layer
static private void
saveCppBps()
{
    bpIndex.clear();
    Libgist.deleteBps();
    Enumeration elems = bps.elements();
    while (elems.hasMoreElements()) {
	Breakpoint bp = (Breakpoint) elems.nextElement();
	if (bp.enabled.booleanValue()) {
	    Libgist.createBp(bp); // sets bp.id
	    bpIndex.put(new Integer(bp.id), bp);
	}
    }
}

// read set of breakpoints
static public void
restore(ObjectInputStream s) throws IOException
{
    try {
	bps = (Vector) s.readObject();

	// re-initialize hash table
	bpIndex.clear();
	Enumeration elems = bps.elements();
	while (elems.hasMoreElements()) {
	    Breakpoint bp = (Breakpoint) elems.nextElement();
	    bpIndex.put(new Integer(bp.id), bp);
	}

	if (dataModel != null) {
	    // redraw table, unless we don't have one yet
	    dataModel.reset(bps);
	}
	saveCppBps();
    } catch (ClassNotFoundException exc) {
        // this shouldn't happen
	DbgOutput.println(2, exc.toString());
	System.exit(1);
    }
}

// reset breakpoints
static public void
reset()
{
    bps.removeAllElements();
    if (dataModel != null) {
	dataModel.reset(null);
    }
    // reset hash table
}

// pop up editing window for breakpoints
static public void
edit()
{
    if (frame == null) {
	// create first installment of frame with JTable etc.
	dataModel = new BpTableModel(bps, updatedBps);
	tableView = new JTable(dataModel);
	tableView.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
	// create rest of frame with JTable etc.
	eventBox = new JComboBox();
	for (int i = 0; i < BreakInfo.NUMEVENTS; i++) {
	    eventBox.addItem(BreakInfo.eventDescrs[i]);
	}

	TableColumn eventCol = tableView.getColumn("Event");
	eventCol.setCellEditor(new DefaultCellEditor(eventBox));
	scrollpane = new JScrollPane(tableView);
	scrollpane.setPreferredSize(new Dimension(750, 200));

	String[] constraints = {
	    "newBtn.left=form.left+10",
	    "deleteBtn.left=newBtn.right+10",
	    "enableBtn.left=newBtn.right+10",
	    "disableBtn.left=enableBtn.right+10",
	    "cancelBtn.right=form.right-10",
	    "okBtn.right=cancelBtn.left-10"
	};
	//JPanel btnPanel = new JPanel(new XmFormLayout(constraints));
	btnPanel = new JPanel(new FlowLayout());
	JButton newBtn = new JButton("New");
	newBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		// create new breakpoint with dummy values
		Breakpoint bp = new Breakpoint();
		bp.id = 0;
		bp.event = BreakInfo.INSERT;
		bp.nodeId = 0;
		bp.param1 = new String("");
		bp.param2 = new String("");
		bp.trace = new Boolean(false);
		bp.enabled = new Boolean(true);
		bps.addElement(bp);
		dataModel.bpAdded();
		tableView.setEditingRow(bps.size()-1);
	    }
	});
	btnPanel.add(newBtn, "newBtn");
	JButton deleteBtn = new JButton("Delete");
	deleteBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		// more currently selected breakpoint to deletedBps
		int[] sel;
		sel = tableView.getSelectedRows();
		try {
		    for (int i = sel.length - 1; i >= 0; i--) {
			deletedBps.addElement(bps.elementAt(sel[i]));
			bps.removeElementAt(sel[i]);
			dataModel.bpDeleted(sel[i]);
		    }
		} catch (ArrayIndexOutOfBoundsException exc) {
		    // shouldn't happen
		}
	    }
	});
	btnPanel.add(deleteBtn, "deleteBtn");
	JButton enableBtn = new JButton("Enable All");
	enableBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		dataModel.setAllEnabled(true);
	    }
	});
	btnPanel.add(enableBtn, "enableBtn");
	JButton disableBtn = new JButton("Disable All");
	disableBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		dataModel.setAllEnabled(false);
	    }
	});
	btnPanel.add(disableBtn, "disableBtn");
	JButton okBtn = new JButton("Ok");
	okBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		saveCppBps();
		frame.setVisible(false);
	    }
	});
	btnPanel.add(okBtn, "okBtn");
	JButton cancelBtn = new JButton("Cancel");
	cancelBtn.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		// undo changes:
		// put deleted breakpoints back
		DbgOutput.println(2, "deleted: " + deletedBps.size());
		Enumeration elems = deletedBps.elements();
		while (elems.hasMoreElements()) {
		    Breakpoint bp = (Breakpoint) elems.nextElement();
		    if (bp.id != 0) {
			// hasn't been created in this editing session
			bps.addElement(bp);
		    }
		}
		// restore updated breakpoints:
		// first remove additions/changes...
		int pos = 0; // index into bps
		int i = 0;
		while (pos < bps.size()) {
		    Breakpoint bp = (Breakpoint) bps.elementAt(pos);
		    if (bp.updated || bp.id == 0) {
			DbgOutput.println(2, bp.toString());
			bps.removeElementAt(pos);
			i++;
		    } else {
			pos++;
		    }
		}
		DbgOutput.println(2, "added/changed: " + i);
		// ... then restore the original values
		DbgOutput.println(2, "restored: " + updatedBps.size());
		elems = updatedBps.elements();
		while (elems.hasMoreElements()) {
		    Breakpoint bp = (Breakpoint) elems.nextElement();
		    if (bp.id != 0) {
			// hasn't been created in this editing session
			bps.addElement(bp);
			DbgOutput.println(2, bp.toString());
		    }
		}
		frame.setVisible(false);
	    }
	});
	btnPanel.add(cancelBtn, "cancelBtn");

	frame = new JDialog(parent, "amdb: Breakpoints", false);
	frame.getContentPane().add(scrollpane);
	frame.getContentPane().add(btnPanel, BorderLayout.SOUTH);
	frame.pack();
    }

    // mark breakpoints non-updated before editing
    Enumeration elems = bps.elements();
    while (elems.hasMoreElements()) {
        Breakpoint bp = (Breakpoint) elems.nextElement();
	bp.updated = false;
    }
    updatedBps.removeAllElements();
    deletedBps.removeAllElements();
    frame.setVisible(true);
}

}
