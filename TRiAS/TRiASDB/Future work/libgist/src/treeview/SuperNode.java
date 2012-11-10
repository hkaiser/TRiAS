// SuperNode.java
// Copyright (c) 1998, Regents of the University of California
// $Id: SuperNode.java,v 1.3 2000/03/23 00:01:44 mashah Exp $

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

public class SuperNode extends JComponent implements ChangeListener,
    MouseListener, MouseMotionListener //, MouseMotionListener
{

    public int numPanels;

    public int ox, oy;

    public TreeDisplay td;
    public boolean open, onpath;
  public Node[]      nodes;
  public SuperNode[] children;

  public SuperNode sparent;
  public int spindex;    

  public int min, max; // range of nodes shown
  public int maxwidth;
  public int pathchild;

  public JPanel iPanel;

// change to use vector class here ...
  public NodePanel[] panels;

  public JScrollBar scroll;

  public boolean wcursor, ecursor, resize;
  public Rectangle resizeRect;
// public Panel mPanel;

  public boolean ad = false; // added to levels list ...
    public int widthbelow = 0;
  public int levelnum = -1;

    public SuperNode(Node[] nodes, int min, int max, TreeDisplay td) {
    
    this(nodes, min, max, td, null, -1);

}

    public SuperNode(Node[] nodes, int min, int max, TreeDisplay td,
      SuperNode sparent, int spindex ) {

    this.nodes = nodes;
    this.min   = min;
    this.max   = max;
    this.td    = td;
    this.sparent = sparent;
    this.spindex = spindex;

    numPanels   = 4;

    pathchild = -1;
    open = true;
    onpath = false;
    resize = false;
    resizeRect = new Rectangle();

    children = new SuperNode[nodes.length];

    panels = new NodePanel[numPanels];

    iPanel = new JPanel();

    FlowLayout fl = new FlowLayout();
    fl.setVgap(0);
    fl.setHgap(1);

    iPanel.setLayout(fl);

    maxwidth = 0;
    
    int i,w;
    double ln10 = Math.log(10);

    // Find max width of nodes ...
    for (i = 0; i < nodes.length; i++) {
	w = (int) Math.floor(Math.log(nodes[i].nodenum)/ln10) + 1;
	if (w > maxwidth)
	    maxwidth = w;
    }

    // Collect all enclosing views, by walking to root.
    Vector addvs = new Vector();
    NodeView[] tvs;
    NodeView av;

    int levelsup = 1;

    SuperNode pnode = sparent;
    int pind = spindex;
    
    while (pnode != null) {
	tvs = pnode.nodes[pind].topViews;
	for (i = 0; i < tvs.length; i++) {
	    av = (NodeView) tvs[i];
	    // Add view if it is deep enough
	    if (av != null)
		if ((av.levels > levelsup))
		    addvs.addElement(av);
	}
	levelsup++;
	pind  = pnode.spindex;
	pnode = pnode.sparent;
    }

    if (addvs.size() > 0) {
	// Add enclosing views to nodes ...
	for (i = 0; i < nodes.length; i++) {
	    for (int m = 0; m < addvs.size(); m++)
		nodes[i].nViews.addElement(addvs.elementAt(m));
	}
    }
    
    for(i=0; i < numPanels; i++) {
      if (min+i < nodes.length) {
	panels[i] = new NodePanel(nodes[min+i],this,min+i);
	iPanel.add(panels[i]);
	iPanel.invalidate();
      }
    }

    numPanels = (numPanels < nodes.length) ? numPanels : nodes.length;

    BorderLayout bl = new BorderLayout();
    bl.setVgap(0);
    setLayout(bl);
    add(iPanel, BorderLayout.CENTER);
    
    if (numPanels < nodes.length) {
	scroll = new JScrollBar(JScrollBar.HORIZONTAL,
	    min,numPanels,0,nodes.length);
	BoundedRangeModel m = scroll.getModel();
	m.addChangeListener(this);
	add(scroll, BorderLayout.NORTH);
	// numPanels = nodes.length;
    }

    //mPanel = new Panel();
    //mPanel.setSize(1,0);
    //add(mPanel, BorderLayout.EAST);
    //mPanel.addMouseMotionListener(this);

    max = min + numPanels;


    addMouseMotionListener(this);
    addMouseListener(this);
    setBorder(new EtchedBorder(EtchedBorder.RAISED));
    setSize(getPreferredSize());
    setVisible(true);
  }

public int resizePanels(boolean cursor) {

    return resizePanels(cursor, false);
}

public int resizePanels(boolean cursor, boolean fl) {
      
//       if (cursor) {
// 	  DbgOutput.println(1,"Don't handle west resizing...");
// 	  return;
//       }

      int i;

      int pw = panels[0].getBounds().width + 2 /* gap size */;

      if (resizeRect.width < pw)
	  return getPreferredSize().width;

      double np =  (double) resizeRect.width / (double) pw ;

      int npanels;
      
      if (fl)
	  npanels = (int) Math.floor(np);
      else
	  npanels = (int) Math.rint(np);

      if (npanels == numPanels)
	  return getPreferredSize().width;

      if (npanels > nodes.length)
	  npanels = nodes.length;

      if (npanels < numPanels) {
	  
	  for (i = numPanels - 1; i >= npanels; i--) {
	      if (panels[i].open)
		  closeSub(panels[i].id);
	      iPanel.remove(panels[i]);
	  }
	  
	  if (cursor)
	      min = min + numPanels - npanels;
	  
	  numPanels = npanels;
	  
	  if (cursor)
	      adjustPanels(min);

	  // hack ... don't think code has this integrity so I gotta 
	  // make a quick fix.

	  // NodePanel[] newPanels = new NodePanel[numPanels];
	  // 	  for (i = 0; i < numPanels; i++)
	  // 	      newPanels[i] = panels[i];
	  // 	  panels = newPanels;
	  
	  if (scroll == null) {
	      scroll = new JScrollBar(JScrollBar.HORIZONTAL,
		  min,numPanels,0,nodes.length);
	      BoundedRangeModel m = scroll.getModel();
	      m.addChangeListener(this);
	      add(scroll, BorderLayout.NORTH);
	      scroll.validate();
	  } else {
	      scroll.setValues(min, numPanels, 0,
		  nodes.length);
	      if (!isAncestorOf(scroll)) {
		  add(scroll, BorderLayout.NORTH);
		  scroll.validate();
		  scroll.repaint();
	      }
	      scroll.repaint();
	  }
      }


      if (npanels > numPanels) {
	 
	  if (npanels > panels.length) {

	      NodePanel[] newPanels = new NodePanel[npanels];
	      
	      if (npanels + min <= nodes.length) {

		  for (i = 0; i < numPanels; i++)
		      newPanels[i] = panels[i];
		  
		  for (i = numPanels; i < npanels; i++) {
		      newPanels[i] = new NodePanel(nodes[min+i],this,min+i);
		      iPanel.add(newPanels[i]);
		      newPanels[i].setVisible(true);
		      newPanels[i].validate();
		  }

		  panels = newPanels;

	      } else {
		  
		  int newmin = nodes.length - npanels;
		  int dist   = min - newmin;

		  for (i = 0; i < numPanels; i++)
		      newPanels[i] = panels[i];

		  for (i = numPanels; i < npanels; i++) {
		      newPanels[i] = 
			  new NodePanel(nodes[newmin+i],this,newmin+i);
		      iPanel.add(newPanels[i]);
		      newPanels[i].setVisible(true);
		      newPanels[i].validate();		      
		  }

// 		  for (i = 0; i < dist; i++) {
// 		      newPanels[i] = 
// 			  new NodePanel(nodes[newmin+i],this,newmin+i);
// 		      iPanel.add(newPanels[i]);
// 		      newPanels[i].setVisible(true);
// 		      newPanels[i].validate();
// 		  }
		  
// 		  for (i = 0; i < numPanels; i++)
// 		      newPanels[dist + i] = panels[i];
		  
// 		  for (i = numPanels + dist; i < npanels; i++) {
// 		      newPanels[i] = 
// 			  new NodePanel(nodes[newmin+i],this,newmin+i);
// 		      iPanel.add(newPanels[i]);
// 		      newPanels[i].setVisible(true);
// 		      newPanels[i].validate();
// 		  }
		  
		  min = newmin; 
		  numPanels = npanels;

		  panels = newPanels;
		  
		  adjustPanels(min);
	      }
	      
	      
	  } else {
	      
	      for (i = numPanels; i < npanels; i++) {
		  iPanel.add(panels[i]);
		  panels[i].validate();
		  panels[i].repaint();
	      }

	      numPanels = npanels;
	      
	      adjustPanels(min);

// 	      if (npanels + min > nodes.length)
// 		  min = nodes.length - npanels;

// 	      for (i = 0; i < npanels; i++) {
// 		  panels[i].setNode(nodes[min+i],this,min+i);
// 		  if (panels[i].open)
// 		      openSub
// 			  panels[i].dal.node = panels[i].node;
// 		  panels[i].val.node = panels[i].node;

// 	      }
	  }
	  
	  numPanels = npanels;
	  max = min + npanels;

	  if (scroll != null) {
	      scroll.setValues(min,numPanels,0,nodes.length);
	      scroll.invalidate();
	      scroll.validate();
	      scroll.repaint();
	  }

	  if (isAncestorOf(scroll)) {
	      if (numPanels >= nodes.length) {
		  remove(scroll);
	      }
	  }
      }

      iPanel.invalidate();
      invalidate();
      setSize(getPreferredSize());
      return getPreferredSize().width;
      // getTopLevelAncestor().validate();
  }

  public boolean openSub(int cnum) {
    
      // DbgOutput.println(1,"openSub: " + nodes[cnum].nodenum );

    // Check if it is a leaf
    if (nodes[cnum].childnum == 0)
      return false;

    // Set child to open if open before
    if (children[cnum] != null) {
      showChildren(children[cnum]);
      // children[cnum].setVisible(true);
      return (children[cnum].open = true);
    }

    // Create child
    Node[] offspring = nodes[cnum].getChildren();
    
    if (nodes[cnum].childnum == 0)
	return false;

    children[cnum] = new SuperNode(offspring,0,0,td, this, cnum);
    // children[cnum].td = td;
    td.add(children[cnum]);

    getTopLevelAncestor().setVisible(true);
    // getTopLevelAncestor().validate();
    // getTopLevelAncestor().repaint();
    return true;
  }

  public void showChildren(SuperNode root) {

    int nchild = root.nodes.length;
    int i;

    // DbgOutput.println(1,"showChildren: " + root.nodes[0].nodenum);

    // root.invalidate();
    Vector sibs = (Vector) td.ui.levels.elementAt(root.levelnum);
    sibs.addElement(root);
    root.ad = true;

    root.setVisible(true);

    for (i = 0; i < nchild; i++)
      if (root.children[i] != null)
	if (root.children[i].open)
	  showChildren(root.children[i]);

  }

  public boolean closeSub(int cnum) {

    children[cnum].open = false;
    hideChildren(children[cnum]);
    // children[cnum].setVisible(false);
    
    return false;
  }

  public void hideChildren(SuperNode root) {

    int nchild = root.nodes.length;
    int i;

    root.setVisible(false);
    
    // if (root.
    Vector sibs = (Vector) td.ui.levels.elementAt(root.levelnum);
    if (!sibs.removeElement(root));
	// DbgOutput.println(1,"hideChildren: didn't remove: " + 
// 	    root.nodes[0].nodenum);
    
    root.ad = false;

    for (i = 0; i < nchild; i++)
      if (root.children[i] != null)
	hideChildren(root.children[i]);
  }

  public void stateChanged(ChangeEvent e) {
      BoundedRangeModel m = (BoundedRangeModel) e.getSource();

      if (! m.getValueIsAdjusting()) {
	  int value = m.getValue();
	  
	  if (value != min) {
	      td.tv.centerhit = true;
	      td.tv.hitcomp = this;
	      adjustPanels(value);
	  }
// 	  validate();
// 	  repaint();
	  getTopLevelAncestor().validate();
	  getTopLevelAncestor().repaint();
      }
  }

  public synchronized void adjustPanels(int start) {
      
      int i;
      
      onpath = false;

      if (start + numPanels > nodes.length)
	  start = nodes.length - numPanels;

      // lets do this the slow way for now ...
      for (i = 0; i < numPanels; i++)
	  if (panels[i].open)
	      closeSub(panels[i].id);
      
      for (i = 0; i < numPanels; i++) {

	  // close children of old panel.
	  // if (panels[i].open)
	  // closeSub(panels[i].id);

	  panels[i].setNode(nodes[start+i], this, start+i);

	  panels[i].fontinit = false;
	  if (panels[i].node.onpath)
	      onpath = true;

	  // open children of new panel.
	  if (panels[i].open) {
	      // DbgOutput.println(1,"Open: " + panels[i].id + ": " + i);
	      openSub(panels[i].id);
	      //DbgOutput.println("HUH: " + nodes[0].nodenum + " " +
	      // panels[i].id + " " + children[panels[i].id].open);
	  }

	  panels[i].dal.node = panels[i].node;
	  panels[i].val.node = panels[i].node;

	  // panels[i].open = nodes[start+i].open;
	  // hideChildren(children[min+i])
      }
      min = start; max = min + numPanels;

      if (scroll != null)
	  scroll.setValue(min);
  }

  public void mouseDragged(MouseEvent e) {

      DbgOutput.println(1,"dragged");
      DbgOutput.println(1,"resize: " + resize);
      DbgOutput.println(1,"ecursor: " + ecursor);
      DbgOutput.println(1,"wcursor: " + wcursor);

      if (resize) {
	  resizeRect.setBounds(getBounds());
	  resizeRect.x--;
	  resizeRect.y--;
	  resizeRect.height++;
	  
	  if (ecursor) {	  
	      
	      resizeRect.width = e.getX();

	      DbgOutput.println(1,"dragged ... " + resizeRect + " " + e.getX());

	  } else if (wcursor) {
	      DbgOutput.println(1,"dragged ... " + resizeRect + " " + e.getX());
	      resizeRect.width -= e.getX() - 1;
	      resizeRect.x += e.getX();
	      DbgOutput.println(1,"dragged ... " + resizeRect + " " + e.getX());
	  }
	  getTopLevelAncestor().repaint(); 
      }
      
  }

  public void mouseMoved(MouseEvent e) {

      Insets i = this.getInsets();

      DbgOutput.println(1,"moved");
      DbgOutput.println(1,"e.getX: " + e.getX());
      DbgOutput.println(1,"e.getY: " + e.getY());
      DbgOutput.println(1,"left: " + i.left);
      DbgOutput.println(1,"right: " + i.right);
      if (e.getX() <= i.left + 4) {
	  setCursor(Cursor.getPredefinedCursor(Cursor.W_RESIZE_CURSOR));
	  wcursor = true;
	  ecursor = false;
      }
      else if (e.getX() >= getWidth() - i.right - 4) {
	  setCursor(Cursor.getPredefinedCursor(Cursor.E_RESIZE_CURSOR));
	  ecursor = true;
	  wcursor = false;
      }
      else {
	  setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	  wcursor = ecursor = false;
      }
  }

  public void mousePressed(MouseEvent e) {      
      DbgOutput.println(1,"presseed");
      if (wcursor || ecursor) {
	  DbgOutput.println(1,"pressed -- true");
	  resize = true;
      }
  }

  public void mouseReleased(MouseEvent e) {
      DbgOutput.println(1,"released");
      if (resize) {
	  resize = false;
	  getTopLevelAncestor().repaint();
	  td.tv.centerhit = true;
	  td.tv.hitcomp = this;
	  if (wcursor)
	      resizePanels(true);
	  else
	      resizePanels(false);
	  getTopLevelAncestor().validate();
      }
  }

  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {
      // DbgOutput.println(1,"exited.");
      // if (resize) {
      // resize = false;
      // }
  }
  public void mouseClicked(MouseEvent e) {}

}
