// NodePanel.java
// Copyright (c) 1998, Regents of the University of California
// $Id: NodePanel.java,v 1.2 1999/06/27 00:17:38 marcel Exp $

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class NodePanel extends JComponent implements MouseListener {

  public static int border   = 2;
  public static int inborder = 1;

  public Dimension panelSize = new Dimension(100,100);
  public Dimension npanelSz  = new Dimension(14,14);
  public Dimension borderSz;

  // font stuff ;
  public int sh, sw, bw, descent;

  public int id;
  public Node node;
// public boolean onpath;
  public boolean open, pagenos, fontinit;
  public SuperNode parent;

  public Color[] pallette;

  public JPopupMenu popup;


// This class handles the what happens when "dump" is selected
// from popup-menu.

class dumpActionListener implements ActionListener {

public JDesktopPane desktop;
public Node         node;

public dumpActionListener(JDesktopPane desktop, Node node) {
    this.desktop = desktop;
    this.node    = node;
}

public void actionPerformed(ActionEvent e) {
    
    // If the node doesn't have contents window associated ... add one.
    if (node.nDump == null) {
	node.nDump = new NodeDump(node, parent.td.tv);
	desktop.add(node.nDump, JLayeredPane.PALETTE_LAYER);
    }
    
    // If we removed the node window from the desktop ... add it.
    if (!desktop.isAncestorOf(node.nDump)) {
	// DbgOutput.println(1,"HEY5");			    
	desktop.add(node.nDump, JLayeredPane.PALETTE_LAYER);
	try {
	    node.nDump.setClosed(false);
	} catch (Exception ex) {
	    System.out.println("PROP: " + ex);
	}
    }
    
    try {
	if (node.nDump.isIcon())
	    node.nDump.setIcon(false);
	else
	    // If we hid the dump window, make is visible.
	    if (!node.nDump.isVisible())
		node.nDump.setVisible(true);
    } catch (Exception ex) {
	System.out.println("Couldn't deiconify: " + ex);
    }

    // Make sure the window pops to the front, otherwise
    // sometimes it is hard to find.
    node.nDump.toFront();
}

}

// This class handles the what happens when "view" is selected
// from popup-menu.

class viewActionListener implements ActionListener {
  
public JDesktopPane desktop;
public Node         node;
public NodePanel    panel;

public viewActionListener(JDesktopPane desktop, Node node, NodePanel panel) {
    this.desktop = desktop;
    this.node    = node;
    this.panel   = panel;
}

public void addToViewsBelow(NodeView aView, int numLevels, NodePanel aPanel) {

    // DbgOutput.println(1,"Level: " + numLevels);

    if (numLevels == 0)
	return;

    addViewToPanel(aPanel, aView);

    //    DbgOutput.println(1,"Node: " + aPanel.node.nodenum);

    SuperNode child = aPanel.parent.children[aPanel.id];

    int i;

//     if (child != null)
// 	DbgOutput.println(1,"Child: " + aPanel.node.nodenum);
//     else
// 	DbgOutput.println(1,"Null child");

    if (child != null && numLevels > 1) {
	for (i = 0; i < child.min; i++) {
	    child.nodes[i].nViews.addElement(aView);
	}

	for (i = 0; i < child.numPanels ; i++) {
	    if (child.panels[i] == null)
		DbgOutput.println(1,"Child of: " + aPanel.node.nodenum + 
				   " Panel: " + i + 
				   " numPanels: " + child.numPanels);

	    addToViewsBelow(aView, numLevels - 1, child.panels[i]);
	    // child.panels[i].node.nodeViews.addElement(aView);
	}

	for (i = child.min + child.panels.length; 
	     i < child.nodes.length; i++) {
	    child.nodes[i].nViews.addElement(aView);
	}
    }
}

public void addViewToPanel(NodePanel aPanel, NodeView aView) {

    // Since we are going to add the node view, we must enable
    // the menu.

    if (aPanel == null) {
	DbgOutput.println(1,"NULL PANEL: ");
	return;
    }

    if (aPanel.node.nViews.size() == 0)
	aPanel.hsub.setEnabled(true);

    // Add the menu item to the list for this node ...

    JMenuItem menuItem = 
	new JMenuItem(aView.getViewName());

    menuItem.addActionListener(aPanel.hsal);

    aPanel.hsub.add(menuItem);

    aPanel.node.nViews.addElement(aView);
}

public void actionPerformed(ActionEvent e) {

    // Same template as the dump class.

    String command;
    int viewIndex;

    command = e.getActionCommand();

    DbgOutput.println(1,node.nodenum + " : " + command);
    
    try {
	if (command.equals("all") || command.equals("Node View"))
	    viewIndex = 0;
	else
	    viewIndex = Integer.parseInt(command);
    } catch (Exception ex) {
	System.out.println("Didn't understand view command: " + command);
	System.out.println(ex);
	return;
    }

    if (node.topViews[viewIndex] == null) {
	
	int depth;

	if (command.equals("all") || command.equals("Node View"))
	    depth = Libgist.getLevel(node.nodenum);
	else
	    depth = viewIndex;

	node.topViews[viewIndex] = new NodeView(node, parent.td.tv, viewIndex);
	node.topViews[viewIndex].path = parent.td.tv.path;

	// Since we are going to add the node view, we must enable
	// the menu.
// 	if (node.nViews.size() == 0)
// 	    panel.hsub.setEnabled(true);

	// Add the menu item to the list for this node ...

// 	JMenuItem menuItem = 
// 	    new JMenuItem(node.topViews[viewIndex].getViewName());

// 	menuItem.addActionListener(panel.hsal);
	
// 	panel.hsub.add(menuItem);

// 	node.nViews.addElement(node.topViews[viewIndex]);

	// addViewToPanel(panel, node.topViews[viewIndex]);

	//
	// Make calls here to add the view to nodes below this view.
	//


	addToViewsBelow(node.topViews[viewIndex], depth, panel);

	desktop.add(node.topViews[viewIndex], JLayeredPane.PALETTE_LAYER);
    }

    if (!desktop.isAncestorOf(node.topViews[viewIndex])) {
	desktop.add(node.topViews[viewIndex], JLayeredPane.PALETTE_LAYER);
	try {
	    // If it was showing a node split before ... remove it
	    // and show the path.
	    if (node.topViews[viewIndex].can.showSplit)
		node.topViews[viewIndex].showPathChild();
	    node.topViews[viewIndex].setClosed(false);
	} catch (Exception ex) {
	    System.out.println("Couldn't add existing view: " + ex);
	}
    }

    try {
	if (node.topViews[viewIndex].isIcon())
	    node.topViews[viewIndex].setIcon(false);
	else if (!node.topViews[viewIndex].isVisible())
	    node.topViews[viewIndex].setVisible(true);
    } catch (Exception ex) {
	System.out.println("Couldn't deiconify: " + ex);
    }

    node.topViews[viewIndex].toFront();


    if (false) {
	if (node.nView == null) {
	    node.nView = new NodeView(node, parent.td.tv, 0);
	    node.nView.path = parent.td.tv.path;
	    desktop.add(node.nView, JLayeredPane.PALETTE_LAYER);
	}
	
	if (!desktop.isAncestorOf(node.nView)) {
	    // DbgOutput.println(1,"HEY5");			    
	    desktop.add(node.nView, JLayeredPane.PALETTE_LAYER);
	    try {
		if (node.nView.can.showSplit)
		    node.nView.showPathChild();
		node.nView.setClosed(false);
	    } catch (Exception ex) {
		DbgOutput.println(1,"PROP: " + ex);
	    }
	}
	
	if (!node.nView.isVisible())
	    node.nView.setVisible(true);
	
	node.nView.toFront();
    }
}
    
}

class hsubActionListener implements ActionListener {

public Node node;

public hsubActionListener(Node node) {

    this.node = node;
}

public void actionPerformed(ActionEvent e) {
    
    String viewName = e.getActionCommand();

    int i;
    NodeView view = null;

    for (i = 0; i < node.nViews.size(); i++) {
	view = (NodeView) node.nViews.elementAt(i);
	if (viewName.equals(view.getViewName()))
	    break;
    }

    if (view != null) {
	int nlevels;

	// this node's height is node.topViews.length
	// So the number of levels you want to show is
	
	nlevels = view.levels - (view.node.topViews.length - 
	    node.topViews.length);
	if (nlevels > 0) {
	    view.highlightSubtree(node.nodenum, nlevels);
	    view.repaint();
	}
	else
	    DbgOutput.println(1,"Not right number of levels: " + nlevels);
    } else 
	DbgOutput.println(1,"Don't understand command: " + viewName);
}

}


// This class handles the what happens when "split" is selected
// from popup-menu.

class splitActionListener implements ActionListener {

public NodePanel    panel;
public Node         node;
public int splitItems[];
private ActionEvent nodeViewAction;
private ActionEvent allViewAction;

public splitActionListener(Node node, NodePanel panel) {
    splitItems = new int[Libgist.maxChildren()];
    this.node = node;
    this.panel = panel;
    nodeViewAction = 
	new ActionEvent(panel.dump, ActionEvent.ACTION_PERFORMED, "1");
    allViewAction =
	new ActionEvent(panel.dump, ActionEvent.ACTION_PERFORMED, "all");
}

public void actionPerformed(ActionEvent e) {
    
    try {

	NodeView aView;
	
	int nl = Libgist.getLevel(node.nodenum);

	if (nl == 1)
	    aView = node.topViews[0]; // location should contain Node View
	else
	    aView = node.topViews[1];

	// If a view doesn't already exist, add one
	// for this node.
	if (aView == null) {
	    if (nl == 1) {
		panel.val.actionPerformed(allViewAction);	

		aView = node.topViews[0]; // location should contain Node View
	    }
	    else {
		panel.val.actionPerformed(nodeViewAction);
		aView = node.topViews[1];
	    }
	}

	if (aView.isClosed())
	    aView.setClosed(false);
	else if (aView.isIcon())
	    aView.setIcon(false);
	else
	    aView.setVisible(true);
	
	int num;
	
	final int nodenum = node.nodenum;
	
	num = Libgist.pickSplit(nodenum, splitItems);
	
	aView.showSplit(splitItems, num);
	
	aView.toFront();
	
	aView.repaint();
    } catch (Exception ex) {
	System.out.println("split action: " + ex);
    }
}

}

// This class handles the what happens when "path" is selected
// from popup-menu.

class pathActionListener implements ActionListener {

public SuperNode parent;
public Node node;

public pathActionListener(Node node, SuperNode parent) {
    
    this.node = node;
    this.parent = parent;
}

public void actionPerformed(ActionEvent e) {
    
    try {
	// DbgOutput.println(1,"PATH: " + node.nodenum);
	parent.td.tv.showPath(node.nodenum);
    } catch (LibgistException ex) {
	System.out.println("Error showing path: " + ex);
    }
    
}

}

public dumpActionListener dal;
public viewActionListener val;
public splitActionListener sal;
public pathActionListener pal;
public hsubActionListener hsal;

public JMenuItem dump, path, split, viewItem;
public JMenu view, hsub;

public NodePanel(Node anode, SuperNode parent, int id) {

    int i;

    this.node   = anode;
    this.parent = parent;
    this.id     = id;
    
    // setFont(new Font("Dialog", Font.PLAIN, 10));
    
    //     if (parent.children[id] != null)
    // 	open = parent.children[id].open;
    //     else
    // 	open = false;

    open = anode.open;

    // onpath = false;
    fontinit = false;
    pagenos = true;
    addMouseListener(this);
    if (parent.td.fm != null) {
	fontinit = true;
	initFontStuff(parent.td.fm);
    }

    
    dump = new JMenuItem("Node Contents");

    popup = new JPopupMenu();
    popup.add(dump);

    val = new viewActionListener(parent.td.tv.desktop, node, this);

    JMenuItem menuItem;

    // add as many options as there are levels ...
    // if only one level, don't add any options at all.
    int level = node.topViews.length;

    if (level > 1) {
	
	// add submenu if needed ...
	view = new JMenu("Subtree View");
	view.addActionListener(val);
	popup.add(view);

	menuItem = new JMenuItem("all");
	menuItem.addActionListener(val);
	view.add(menuItem);

    } else {

	// otherwise only add item ...
	viewItem = new JMenuItem("Node View");
	viewItem.addActionListener(val);
	popup.add(viewItem);

    }

    level--;

    for (i = 0; i < level; i++) {
	menuItem = new JMenuItem(Integer.toString(i+1));
	menuItem.addActionListener(val);
	view.add(menuItem);
    }

    hsub = new JMenu("Highlight Subtree");
    path = new JMenuItem("Highlight Path");
    split = new JMenuItem("Highlight Split");

    dal = new dumpActionListener(parent.td.tv.desktop, node);
    dump.addActionListener(dal);

    pal = new pathActionListener(node, parent);
    path.addActionListener(pal);

    sal = new splitActionListener(node, this);
    split.addActionListener(sal);

    hsal = new hsubActionListener(node);
    hsub.addActionListener(hsal);


    for (i = 0; i < node.nViews.size(); i++) {
	menuItem = new JMenuItem(
	    ((NodeView) node.nViews.elementAt(i)).getViewName());
	menuItem.addActionListener(hsal);
	hsub.add(menuItem);
    }

    if (node.nViews.size() == 0)
	hsub.setEnabled(false);

    //    popup.add(view);
    popup.add(hsub);
    popup.add(path);
    popup.add(split);

    popup.setInvoker(parent.td.tv);
}

public void setNode(Node anode, SuperNode parent, int id) {
      
    this.node   = anode;
    this.parent = parent;
    this.id     = id;
    
    //       if (parent.children[id] != null)
    // 	  open = parent.children[id].open;
    //       else
    // 	  open = false;
    
    open = anode.open;
    
    dal.node = anode;
    val.node = anode;
    pal.node = anode;
    sal.node = anode;
    hsal.node = anode;

    int i;

    JMenuItem menuItem;
    
    // Node we don't have to change anything in view because
    // this NodePanel only ever gets set to another node at the same
    // level.

    // Remove components in the menu ...
    hsub.removeAll();

    for (i = 0; i < node.nViews.size(); i++) {
	menuItem = 
	    new JMenuItem(((NodeView) node.nViews.elementAt(i)).getViewName());
	menuItem.addActionListener(hsal);
	hsub.add(menuItem);
    }

    if (node.nViews.size() == 0)
	hsub.setEnabled(false);
    else
	hsub.setEnabled(true);

}

public void paint(Graphics g) {
    
    int width  = getBounds().width;
    int height = getBounds().height;
    Color back = g.getColor();
    int x,y;
    float stat;
    Color statColor = null;
    
    pallette = parent.td.tv.pallette;
    
    if ((getPreferredSize().width != width) ||
	(getPreferredSize().height != height)) {

	setSize(getPreferredSize());
	// invalidate();
	getTopLevelAncestor().validate();
	// validate();
    }

    if (parent.td.shownodes) {
	
	String tipText = "node: " + node.nodenum;
	
	// DbgOutput.println(1,getBounds());
	x = (width) / 2 - 5;
	y = (height) / 2 - 5;
	
	if (node.onpath) 
	    g.setColor(Color.red);
	else
	    g.setColor(Color.white);
	
	//if (node.onpath)
	//g.setColor(new Color(255,0,node.stat));
	
	g.fillRect(x, y, 10, 10);
	
	if (parent.td.tv.showstats) {
	    stat = parent.td.tv.stats[node.nodenum];
	    if ((Float.isInfinite(stat)) || (Float.isNaN(stat)))
		statColor = back;
	    else {

		// make sure we don't have maxStat == minStat
		if (parent.td.tv.ratio > 0) {
		    
		    int index;
		    
		    index = (int) Math.floor(
			(double) (stat - parent.td.tv.minStat) *
			parent.td.tv.ratio);

		    if (index > 255)
			index = 255;
		    else if (index < 0)
			index = 0;

		    // index = (index == 256) ? 255 : index;

		    statColor = pallette[index];

		} else
		    // if so arbitrarily assign the color.
		    statColor = pallette[0];

	    }

	    g.setColor(statColor);
	    setToolTipText(tipText + " stat: " + stat);
	    g.fillRect(x+1,y+1,8,8);

	} else
	    setToolTipText(tipText);
	
	if (open)
	    g.drawLine(width/2, y + 10, width/2, height);
	
    } else {
	
	g.setFont(parent.td.font);
	
	if (!fontinit) {
	    initFontStuff(g.getFontMetrics());
	}
	
	setToolTipText(null);
	
	x = (width - 1 - bw - border) / 2;
	y = (height - 1 - sh - border) / 2;
	
	if (node.onpath) 
	    g.setColor(Color.red);
	else
	    g.setColor(Color.black);
	
	g.drawRect(x,y,bw + 2*inborder, sh + 2*inborder);
	// g.drawRect(0,0,width,height);
	
	stat = 0;
	
	if (!parent.td.tv.showstats)
	    g.setColor(Color.white);
	else {
	    stat = parent.td.tv.stats[node.nodenum];
	    if ((Float.isInfinite(stat)) || (Float.isNaN(stat)))
		statColor = back;
	    else {
		// make sure we don't have maxStat == minStat
		if (parent.td.tv.ratio > 0) {
		    
		    int index;
		    
		    index = (int) Math.floor(
			(double) (stat - parent.td.tv.minStat) *
			parent.td.tv.ratio);

		    if (index > 255)
			index = 255;
		    else if (index < 0)
			index = 0;

		    // index = (index == 256) ? 255 : index;
		    
		    statColor = pallette[index];
		    
		} else
		    // if so arbitrarily assign the color ...
		    statColor = pallette[0];
	    }
	    g.setColor(statColor);
	    
	    setToolTipText("stat: " + stat);
	}
	
	g.fillRect(x+1,y+1,bw + 2*inborder - 1, sh + 2*inborder - 1);
	
	if (parent.td.tv.showstats) {
	    
	    float[] hsb = new float[3];
	    int rgb = statColor.getRGB();
	    
	    Color.RGBtoHSB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF,
		rgb & 0xFF, hsb);
	    
	    if (hsb[2] >= 0.6) {
		if (hsb[1] <= 0.9)
		    g.setColor(Color.black);
		else 
		    g.setColor(Color.white);
	    }
	    else
		g.setColor(Color.white);
	} else
	    g.setColor(Color.black);
	
	g.drawString(Integer.toString(node.nodenum),
	    x + inborder + 1 + ((bw - sw) / 2), y + inborder + sh - descent);
	
	if (open)
	    g.drawLine(width/2, y + sh + 2*inborder, width/2, height);
    }
    
    g.setColor(back);
}

// Stuff needed to be done so we can correctly format our text.

public void initFontStuff(FontMetrics fm) {
    
    if (!fontinit)
	parent.td.fm = fm;
    
    sw = fm.stringWidth(Integer.toString(node.nodenum));
    bw = fm.getMaxAdvance() * parent.maxwidth;
    sh = fm.getHeight();
    descent = fm.getDescent();
    
    panelSize = new Dimension(2*(border + inborder) + bw, 
	2*(border + inborder) + sh);
    
    setSize(panelSize);
    
    if (!fontinit) {
	getParent().getParent().setSize(
	    getParent().getParent().getPreferredSize());
	getParent().getParent().setVisible(false);
	getTopLevelAncestor().validate();
	getParent().getParent().setVisible(true);
    }
    
    fontinit = true;
}

public Dimension getPreferredSize() {
    
    if (parent.td.shownodes) 
	return npanelSz;
    else
	return panelSize;
}

public Dimension getMinimumSize() {
    
    if (parent.td.shownodes)
	return npanelSz;
    else
	return panelSize;
}

public void mouseClicked(MouseEvent e) {
    boolean result;
    

    if (SwingUtilities.isLeftMouseButton(e) && (e.getSource() == this)) {
	if (open)
	    result = parent.closeSub(id);
	else
	    result = parent.openSub(id);
	
	if (open != result) {
	    open = result;
	    node.open = open;
	    parent.td.tv.hitcomp = parent;
	    parent.td.tv.centerhit = true;
	    invalidate();

	    // getTopLevelAncestor().validate();
	    // getTopLevelAncestor().repaint();

	    parent.td.repaint();
	    parent.td.tv.eq.postEvent(parent.td.tv.ae);
	}
    } else if (SwingUtilities.isMiddleMouseButton(e)) {
	try {
	    parent.td.tv.showPath(node.nodenum);
	    // parent.td.tv.showPath(node.nodenum);
	    // parent.td.tv.center();
	    
	} catch (Exception ex) {
	    System.out.println("Couldn't show path to " + node.nodenum);
	    System.out.println(ex);
	}
    }
    
    
}

public void mouseEntered(MouseEvent e) {}
public void mouseExited(MouseEvent e) {}
public void mousePressed(MouseEvent e) {
    
    if (SwingUtilities.isRightMouseButton(e)) {
	Point p = e.getPoint();
	SwingUtilities.convertPointToScreen(p, this);
	popup.setLocation(p.x, p.y);
	popup.setVisible(true);
    }
    
}

public void mouseReleased(MouseEvent e) {
    //       if (SwingUtilities.isRightMouseButton(e)) {
    // 	  popup.setVisible(false);
    //       }
}

}
