// NodeView.java
// Copyright (c) 1998, Regents of the University of California
// $Id: NodeView.java,v 1.3 1999/12/14 06:08:13 marcel Exp $

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

class Rect {
  double x1, x2, y1, y2;
}

class Pt {
  double x, y;
}

class Circle {
  double x, y, r;
}

public class NodeView extends JInternalFrame implements 
InternalFrameListener 

{

public double minx, miny, maxx, maxy;
public Rect[]   rects;
public Pt[]     points;
public Circle[] circles;

public Node        node;

public int levels = 0;

class Inside extends JComponent {

public boolean showSubtree = false;
public boolean showSplit = false;
public boolean showPath  = false;

// Path information stored in treeview
// Split information
public int splitItems[] = null;
public int numSplit = 0;

// Highlight subtree information
public int subtreeRoot;
public int subtreeLevels;

public Font font = null;
public int numPreds = 0;
public Color[] hcolors = { Color.black, Color.red, Color.green, Color.yellow };

public void paint(Graphics g) {	    
    
    int width  = getBounds().width;
    int height = getBounds().height;
    
    DbgOutput.println(2, "w: " + width + ", h: " + height);
    
    try {
	if (font == null) {
	    font = new Font("Dialog", Font.PLAIN, 10);
	}
	g.setFont(font);

	Libgist.getPredInfo(node.nodenum, levels);
	if (showPath)  {
	    Libgist.highlightPath(node.nodenum, path[0], 1);
	} else if (showSplit) {
	    Libgist.highlightSplit(splitItems, numSplit, 3);
	} else if (showSubtree) {
	    Libgist.highlightSubtree(subtreeRoot, subtreeLevels, 2);
	}

	// Clear the screen if not already cleared ...
	g.setColor(getBackground());
	g.fillRect(0,0,width,height);

	Libgist.displayPreds(g, width, height, hcolors);
    } catch (LibgistException e) {
  	System.out.println("Libgist.displayPreds() messed up");
	System.out.println("Exception: " + e);
    }
}

}

public Inside can;

// Stuff from tree view ...
public TreeView tv;

public int path[];
public int pl;

public String getViewName() {
    
    return getTitle();
}

public void
showPathChild()
{
    can.showPath = true;

    // Turn off split visualization and subtree highlights ...
    can.showSplit = false;
    can.showSubtree = false;

}


public void showSplit(int splitItems[], int num) {
    
    can.splitItems = splitItems;
    can.numSplit = num;
    can.showSplit = true;

    // Turn off show subTree ...
    can.showSubtree = false;
    can.showPath = false;
}

public void highlightSubtree(int num, int nlevels) {

    can.showSubtree = true;

    can.subtreeRoot = num;
    can.subtreeLevels = nlevels;

    // Gotta turn off split visualization ...
    can.showSplit = false;
    can.showPath = false;
}

public void showSubtree() {
    can.showPath = false;
    can.showSplit = false;
    can.showSubtree = false;
}

public NodeView(Node node, TreeView tv, int levels) {
    
    this.node = node;

    if (levels == 0) {
	setTitle("Subtree View: " + node.nodenum + " : all");
	this.levels = Libgist.getLevel(node.nodenum);
    }
    else {
	setTitle("Subtree View: " + node.nodenum + " : " + levels);
	this.levels = levels;
    }

    setSize(150,150);

    Rectangle tbounds = tv.getBounds();
    Point location = new Point();
    location.x = tbounds.x;
    location.y = tbounds.y + tbounds.height;
    
    setLocation(location);

    setResizable(true);
    setMaximizable(true);
    setIconifiable(true);
    setClosable(true);
    getContentPane().setLayout(new BorderLayout());

    can = new Inside();

    path = tv.path;
    pl   = tv.pl;

    // Argh ... this is messy ... will clean later ..
    this.tv = tv;

    // showSubtree(node.nodenum);

    // add myself to the node 
    tv.nodeviews.addElement(this);    
    
    showSubtree();
    //showPathChild();

    can.repaint();

    getContentPane().add(can, BorderLayout.CENTER);

    addInternalFrameListener(this);
}

public void genPtsnRects(double x1, double x2, double y1, double y2, int num) {

    // DbgOutput.println(1,"gen : " + x1 + " " + y1 + " " + x2 + " " + y2);
    double rangex = x2 - x1;
    double rangey = y2 - y1;

    points  = new Pt[num];
    rects   = new Rect[num];
    circles = new Circle[num];

    Random random = new Random();

    int i;

    double t1, t2;

    for (i=0; i < num; i++) {

	points[i] = new Pt();
	points[i].x = (random.nextDouble() * rangex) + x1;
	points[i].y = (random.nextDouble() * rangey) + y1;

	rects[i] = new Rect();
	rects[i].x1 = (random.nextDouble() * rangex) + x1;
	rects[i].x2 = (random.nextDouble() * rangex) + x1;
	rects[i].y1 = (random.nextDouble() * rangex) + y1;
	rects[i].y2 = (random.nextDouble() * rangex) + y1;

	circles[i] = new Circle();
	t1 = circles[i].x = (random.nextDouble() * rangex) + x1;
	t2 = circles[i].y = (random.nextDouble() * rangey) + y1;
	t1 = Math.min(Math.abs(x2 - t1),Math.abs(x1 - t1));
	t2 = Math.min(Math.abs(y2 - t2),Math.abs(y1 - t2));
	t1 = Math.min(t1,t2);
	circles[i].r = (random.nextDouble() * t1);
    }
    
    minx = x1;

    miny = y1;

    maxx = x2;
    
    maxy = y2;
}

public void paintStuff(int nodenum, Graphics g, int width, int height) {
    double rangex = maxx - minx + 1;
    double rangey = maxy - miny + 1;
    
    double xr = (double) width / rangex;
    double yr = (double) height / rangey;
    
    int i;
    double x,y,x2,y2;
    
    g.setColor(Color.red);
    // draw Rectangles ...
    for (i = 0; i < rects.length; i++) {
	x = Math.floor((rects[i].x1 - minx) * xr);
	x2 = Math.ceil((rects[i].x2 - minx) * xr);
	y = Math.floor((rects[i].y1 - miny) * yr);
	y2 = Math.ceil((rects[i].y2 - miny) * yr);
	
	g.drawRect((int)x,(int)y,(int)(x2-x),(int)(y2-y));
    }
    
    g.setColor(Color.blue);
    for (i = 0; i < points.length; i++) {
	x = Math.floor((points[i].x - minx) * xr);
	y = Math.floor((points[i].y - miny) * yr);
	
	g.drawRect((int)x,(int)y,1,1);
    }

    double w, h;

    g.setColor(Color.green);
    for (i = 0; i < circles.length; i++) {
	x = Math.floor((circles[i].x - minx) * xr);
	y = Math.floor((circles[i].y - miny) * yr);
	
	w = Math.floor((circles[i].r) * xr);
	h = Math.floor((circles[i].r) * yr);

	g.drawOval((int) (x - w), (int) (y - h), (int) (2*w), (int) (2*h));
    }
}

public void internalFrameActivated(InternalFrameEvent ie) {};

public void internalFrameClosed(InternalFrameEvent ie) {
    // DbgOutput.println(1,"THIS");
};

public void internalFrameClosing(InternalFrameEvent ie) {
    // DbgOutput.println(1,"WHAT");
    // setVisible(false);
}

public void internalFrameDeactivated(InternalFrameEvent ie) {};

public void internalFrameDeiconified(InternalFrameEvent ie) {};

public void internalFrameIconified(InternalFrameEvent ie) {};

public void internalFrameOpened(InternalFrameEvent ie) {};

}

