// GlobalView.java
// Copyright (c) 1998, Regents of the University of California
// $Id: GlobalView.java,v 1.2 1999/06/27 00:17:38 marcel Exp $

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import javax.swing.plaf.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;


class GlobalDisplayUI extends ComponentUI implements MouseListener {

public static int minwidth = 20;
public static int maxindwid = 10;

public static int height;
public static int skip = 2;

public static int minheight = 20;
public static int maxheight = 500;

public TreeView tv;
public GlobalView gv;
public Vector levels;
public int levelWid[];

public int wscale, hscale;

protected Dimension pSize = new Dimension(100,100);

public GlobalDisplayUI(TreeView tv, GlobalView gv) {

    try {
	this.tv = tv;
	this.gv = gv;

	wscale = 0;
	hscale = 0;
	
	levels = new Vector();
	
	int i,j,k,childnum;
	
	int[] childnos = new int[Libgist.maxChildren()];

	int[] currLevel = new int[1];
    
	currLevel[0] = tv.rootNode.nodenum;

	Vector nextLevel = new Vector();

	boolean moreChildren = true;

	do {

	    for (i=0; i < currLevel.length; i++) {
		
		childnum = Libgist.getChildren(currLevel[i], childnos);

		if (childnum == 0) {
		    
		    moreChildren = false;
		    break;
		}

		for (j=0; j < childnum; j++)
		    nextLevel.addElement(new Integer(childnos[j]));
		
	    }

	    int size;
	    size = nextLevel.size();
	    
	    levels.addElement(currLevel);

	    currLevel = new int[size];

	    for (i=0; i < size; i++) 
		currLevel[i] = ((Integer) nextLevel.elementAt(i)).intValue();
	    
	    nextLevel.removeAllElements();

	} while (moreChildren);

	DbgOutput.println(1,"Finished ... ");

    } catch (LibgistException ex) {

	DbgOutput.println(1,"Hmmm ... " + ex);

	return;
    }
	
}

public void paint(Graphics g, JComponent c) {


    int h = c.getPreferredSize().height - 10;
    int w = c.getPreferredSize().width -10;

    int i, lh, lw;

    int numlevels = levels.size();
    levelWid = new int[numlevels];

    // give a little slack ...
    g.translate(5,5);

    for (i = 0; i < numlevels; i++) {

	lh = (i+1) * (height + skip);

	
	lw = (int) Math.floor((double) (lh * w) / (double) h);
	lw = (lw > minwidth) ? lw : minwidth;
	
	levelWid[i] = lw;
	
	g.translate( (w - lw) / 2, 0 );

	paintLevel(g,lw,i,c);

	g.translate( -(w - lw) / 2, height + skip );
    }

}

public int smoothRange(int[] level, int start, int end) {

    int i, index;

    float avg;

    avg = 0;

    int nc = 0; // not counted ...

    for (i = start; i < end; i++)
	if (Float.isInfinite(tv.stats[level[i]]) ||
	    Float.isNaN(tv.stats[level[i]]))
	    nc++;
	else
	    avg += tv.stats[level[i]];

    avg = (float) avg / (float) (end - start - nc);

    if (tv.ratio > 0) {
	index = (int) Math.floor((float)(avg - tv.minStat) * tv.ratio);
	
	index = (index == 256) ? 255 : index;
    } else
	index = 0;

    return index;

}

public void paintLevel(Graphics g, int lw, int level, JComponent c) {

    int[] currLevel = (int [])(levels.elementAt(level));
    
    int length = currLevel.length;

    int i, istart = 0, iend, smooth;
    
    // Color back = g.getColor();

    Color back = c.getBackground();

    if (lw <= length) {
	
	double r = (double) length / (double) lw;
	
	for (i = 0; i < lw; i++) {
	    
	    iend = (int) Math.floor( r * (double)(i + 1));

	    iend = (iend > length) ? length : iend;

	    smooth = smoothRange(currLevel,istart,iend);
	    
	    // DbgOutput.println(1,currLevel[istart] + " " +
	    // 		currLevel[iend - 1] + " " + smooth);

	    g.setColor(tv.pallette[smooth]);
	    g.fillRect(i,0,1,height);

	    istart = iend;
	}
	
    } else {

	// lw > length;

	Color statColor = null;

	double r = (double) lw / (double) length;

	for (i = 0; i < length; i++) {

	    iend = (int) Math.ceil( r * (double)(i + 1));
	    
	    if (Float.isInfinite(tv.stats[currLevel[i]]) ||
		Float.isNaN(tv.stats[currLevel[i]]))
		statColor = back;
	    else {

		if (tv.ratio > 0) {
		    int index = (int) Math.floor(
			(double)(tv.stats[currLevel[i]] - tv.minStat) *
			tv.ratio);
		    
		    if (index >= 256)
			index = 255;
		    else if (index < 0)
			index = 0;

		    // index = (index >= 256) ? 255 : index;
		    
		    statColor =	(tv.pallette[ index ]);

		} else
		    statColor = tv.pallette[0];
	    }

	    // this is a hack ...
	    if (statColor == back) {
		g.clearRect(istart, 0, iend - istart, height);
		// g.drawRect(istart, 0, iend - istart, height);
	    } else {
		g.setColor(statColor);
		
		g.fillRect(istart, 0 , iend - istart, height);
	    }

	    istart = iend;
	}
    }

    // g.setColor(back);
}

public Dimension getPreferredSize(JComponent c) {

//     height = (int) Math.floor( (double) (maxheight - minheight) *
// 	(double) hscale / (double) 100) + minheight;


    int numlevels = levels.size();

    Insets in = gv.scroll.getViewport().getInsets();

    height = (int) Math.floor((double) 
	(gv.scroll.getViewport().getSize().height - 10 - in.top - in.bottom) / 
	(double) numlevels);
    
    height = (height < minheight) ? minheight : height;

    height -= skip;

    int h = (height + skip)*levels.size();
    
    int w = (int) Math.floor(((double) wscale / (double)100) * 
	(double) 
	(((int[])(levels.elementAt(numlevels - 1))).length * maxindwid - 
	    minwidth)) + minwidth;

    pSize.width = w + 10;
    pSize.height = h + 10;

    // DbgOutput.println(1,pSize);
    return pSize;
}

public Dimension getMinimumSize(JComponent c) {

    return getPreferredSize(c);

}

public void mouseClicked(MouseEvent e) {

    // DbgOutput.println(1,e.getX() + ", " + e.getY());

    Dimension size = getPreferredSize((JComponent) e.getSource());

    int y = e.getY() - 5; // remove top border ... 

    if ( y < 0 ) {	// in top border
	// DbgOutput.println(1,"NOTIN 1");
	return;
    }

    int h = size.height - 10; 
    // remove both  borders ...
    
    if ( y >= h ) {      // in bottom border
	// DbgOutput.println(1,"NOTIN 3");
	return;
    }

    int level = y / (height + skip);
   
    if ( (y - (level * (height + skip))) > height ) { // in gaps ...
	// DbgOutput.println(1,"NOTIN 2");
	return;
    }

    // DbgOutput.println(1,"LEVEL " + level);

    int lw = levelWid[level];

    int w = size.width - 10; // remove both borders

    
    int x = e.getX() - 5 - ((w - lw) / 2); // remove left border ...
    
    if ( x < 0 ) { // in left border
	// DbgOutput.println(1,"NOTIN L");
	return;
    }

    if ( x >= lw ) { // in right border
	// DbgOutput.println(1,"NOTIN R");
	return;
    }

    int[] currLevel = (int []) levels.elementAt(level);

    int length =  currLevel.length;
    
    //    if (lw <= length) {
	
    int istart = (int) Math.floor(((float) x / (float) lw) * (float) length);
    int iend   = (int) Math.floor(((float) (x + 1) / (float) lw) * 
	(float) length);
    
    // DbgOutput.println(1,"[" + istart + ", " + iend + ") :" + length);
    
    int i = istart;

    try {
	do {
	    tv.showPath(currLevel[i]);
	    i++;
	} while (i < iend);
    } catch (Exception ex) {
	System.out.println("Global Display - mouseClicked");
	System.out.println(ex);
    }

    return;
}

public void mouseEntered(MouseEvent e) {}
public void mouseExited(MouseEvent e) {}
public void mousePressed(MouseEvent e) {}
public void mouseReleased(MouseEvent e) {}

}

class GlobalDisplay extends JComponent {

public GlobalDisplayUI ui;

public GlobalDisplay(TreeView tv, GlobalView gv) {

    ui = new GlobalDisplayUI(tv, gv);
    setUI( ui);
    addMouseListener(ui);
}

}

public class GlobalView extends JInternalFrame implements ChangeListener {

public GlobalDisplay gd;
public JScrollPane scroll;
public JSlider    hslide;
public JSlider    vslide;

public GlobalView(TreeView tv) {

    
    // DbgOutput.println(1,"IN HERE");

    setTitle("Global View");
    setSize(200,150);
    setResizable( true );
    setClosable(true);
    setIconifiable(true);

    hslide = new JSlider(JSlider.HORIZONTAL, 0, 100, 0);
    hslide.setPaintTicks(true);
    hslide.setMajorTickSpacing(20);
    hslide.setMinorTickSpacing(5);
    //    hslide.setPaintLabels( true );

//     vslide = new JSlider(JSlider.VERTICAL, 0, 100, 0);
//     vslide.setInverted( true );
//     vslide.setPaintTicks(true);
//     vslide.setMajorTickSpacing(25);
//     vslide.setMinorTickSpacing(10);
//     vslide.setPaintLabels( true );
    
    hslide.addChangeListener(this);
//     vslide.addChangeListener(this);

    gd = new GlobalDisplay(tv, this);
    
    scroll = new JScrollPane(gd);

    getContentPane().setLayout(new BorderLayout());
    getContentPane().add(scroll, BorderLayout.CENTER);    
    // getContentPane().add(gd, BorderLayout.CENTER);
    getContentPane().add(hslide, BorderLayout.NORTH);
//     getContentPane().add(vslide, BorderLayout.WEST);
}

public void stateChanged(ChangeEvent e) {

    JSlider s1 = (JSlider)e.getSource();
    // DbgOutput.println(1,s1.getValue());
    if (s1 == hslide)
	gd.ui.wscale = s1.getValue();
//     else
// 	gd.ui.hscale = s1.getValue();

    gd.invalidate();
    gd.repaint();
    validate();

}

}
