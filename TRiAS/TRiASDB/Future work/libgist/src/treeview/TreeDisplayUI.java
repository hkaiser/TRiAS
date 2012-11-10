// TreeDisplayUI.java
// Copyright (c) 1998, Regents of the University of California
// $Id: TreeDisplayUI.java,v 1.2 1999/06/27 00:17:39 marcel Exp $

import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.util.Vector;

public class TreeDisplayUI extends ComponentUI {

  // Paints all viewable descendants of tree ...
  
  public int sibDist = 10;
  public int parentDist = 20;
  public int w,h;
  public int kl = 0;

  public Vector levels;

  public TreeDisplayUI() {
      
      levels = new Vector();
  }

  public void paint(Graphics g, JComponent c) {
    
      //      DbgOutput.println(1,"PAINT" + " " + (kl++));
      
    Dimension vsize;
    Insets vinset;

    int ow, oh;
    
    Color back = g.getColor();

    TreeDisplay td = (TreeDisplay) c;

    ow = w; oh = h;

    w = 0; h = 0;

    vsize = td.tv.scroll.getSize();
    vinset = td.tv.scroll.getInsets();

    int expanse = ( vsize.width - vinset.left - vinset.right);
    int emptyspace = ( expanse ) / 2;

    calcNodePos(td.root,parentDist,emptyspace, 0);
    //vsize = ((JViewport)td.getParent()).getViewSize();

    //   if (w < (vsize.width - vinset.left - vinset.right))
    // 	w = vsize.width - vinset.left - vinset.right;
    if ( ( w - emptyspace) < ( expanse ))
	calcNodePos(td.root,parentDist, emptyspace + 
	    (expanse - (w  - emptyspace)) / 2, 0);

    w += emptyspace;
    
    if (h < (vsize.height - vinset.top - vinset.bottom - 20))
	h = vsize.height - vinset.top - vinset.bottom - 20;

    td.setSize(w,h);


    //td.getTopLevelAncestor().invalidate();
    //td.getTopLevelAncestor().setVisible(true);

    int oloc = 0;

    if (td.tv.centerhit)
	oloc = td.tv.hitcomp.getLocation().x;

    if (td.tv.centeroot) {
	td.tv.center();
	// td.tv.scroll.getViewport().repaint();
    }

    if (td.tv.centerhit) {
	td.tv.centerhitcomp(oloc);
	// td.tv.scroll.getViewport().repaint();
    }

    positionNodes(td.root, g, c);


    if ((ow != w) || (oh != h)) {
	td.getTopLevelAncestor().validate();
    }

    
    // td.getTopLevelAncestor().invalidate();
    // td.getTopLevelAncestor().validate();
  }

  public void positionNodes(SuperNode node, Graphics g, JComponent c) {
    
    int i, nchild;

    nchild = node.nodes.length;

    Color back = g.getColor();

//     for(i = 0; i < nchild; i++)
//       if (node.children[i] != null)
// 	if (node.children[i].open)
// 	    positionNodes(node.children[i],g,c);

    int x1, y1, x2, y2, id;

    node.panels[0].invalidate();
    node.setSize(node.getPreferredSize());

    node.reshape(node.ox, node.oy, 
		 node.getBounds().width, node.getBounds().height);

    if (node.resize) {
	// DbgOutput.println(1,"draw: " + node.resizeRect);
	g.setXORMode(Color.red);
	g.drawRect(node.resizeRect.x, node.resizeRect.y, 
	    node.resizeRect.width, node.resizeRect.height);
	g.setPaintMode();
    }

    for(i=0; i < node.numPanels ; i++)
      if (i < nchild)
	if(node.panels[i].open) {
	    id = node.panels[i].id;
	    // DbgOutput.println(1,node.nodes[id].nodenum + " " + id);
	    if (node.children[id] != null) 
		if (node.children[id].open) {
		    x1 = node.panels[i].getLocation().x + 
			(node.panels[i].getBounds().width / 2) + node.ox + 2;
		    y1 = node.oy + node.getBounds().height;
		    x2 = node.children[id].ox + 
			node.children[id].getBounds().width /2;
		    y2 = node.children[id].oy;
		    if (node.onpath && node.children[id].onpath)
			g.setColor(Color.red);
		    else
			g.setColor(Color.black);
		    // DbgOutput.println(1,"drawing small line");
		    g.drawLine(x1,y1,x2,y2);
		    g.setColor(back);
		    // DbgOutput.println(1,"Calling on child");
		    positionNodes(node.children[id],g,c);
	    }
	}
    
    
  }


  public int calcNodePos(SuperNode node, int iy, int ix, int lvl) {

    int i, width, nchild;

    node.oy = iy;
    node.levelnum = lvl;
    nchild = node.nodes.length;

    if (!node.ad) {
	Vector sibs;
	// int num = levels.size();
	if (lvl >= levels.size()) {
	    // if ((sibs = (Vector) levels.elementAt(lvl)) == null) {
	    // DbgOutput.println(1,"Adding new sibs: " + lvl);
	    sibs = new Vector();
	    levels.addElement(sibs);
	    // levels.setElementAt(sibs,lvl);
	} else
	    sibs = (Vector) levels.elementAt(lvl);
	
	// DbgOutput.println(1,"Adding node to sibs at level: " + lvl);
	sibs.addElement(node);
	// DbgOutput.println(1,"Sibs NUM: " + sibs.size());
	// DbgOutput.println(1,"Levels NUM: " + levels.size());
	node.ad = true;
    }

    width = 0;
    for(i=0; i < nchild; i++) {
// 	if ((node.nodes[0].nodenum == 731) && ( i == 1 )) {
// 	    if (node.children[i] == null)
// 		DbgOutput.println(1,"NULL");
// 	    else if (node.children[i].open == false)
// 		DbgOutput.println(1,"FALSE");
// 	}

	if (node.children[i] != null) {

	    if (node.children[i].open) {
		width += calcNodePos(node.children[i],
		    iy + node.getBounds().height + parentDist, 
		    ix + width, lvl + 1);
	    }
	}
    }
    //node.children[i].ox + node.children[i].getBounds().width +
    //sibDist;

    if (h < node.oy + node.getBounds().height + parentDist)
      h = node.oy + node.getBounds().height + parentDist;

    boolean nochild = false;

    if ((width == 0) || (width < node.getBounds().width + sibDist)) {
	nochild = true;
	int ow = width;
	width = node.getBounds().width;
	node.ox = ix;
	
	// Could center children here if you wanted ...
// 	if (width != 0) {
// 	    int nw = 0;
// 	    for (i=0; i < nchild; i++)
// 		if ((node.children[i] != null) && node.children[i].open) 
// 		    nw += calcNodePos(node.children[i],
// 			iy + node.getBounds().height + parentDist, 
// 			ix + nw + ((width - ow) / 2));	
// 	}

	if (w < ix + node.getBounds().width + sibDist)
	    w = ix + node.getBounds().width + sibDist;

    } else if (node.onpath && (node.pathchild != -1)) { // Center node over pathchild

	SuperNode cn;
	int chcen;

	cn = node.children[node.pathchild];

	if (cn.isVisible()) {
	    if (cn == null) {
		
		DbgOutput.println(1,node.panels[0].node.nodenum + " " 
		    + node.pathchild);
	    }
	    
	    chcen = cn.ox + cn.getBounds().width  / 2;
	    
	    node.ox = chcen - node.getBounds().width / 2;
	    
	    if (node.ox < ix)
		node.ox = ix;
	    else if (node.ox + 
		node.getBounds().width + sibDist / 2 > ix + width)
		node.ox = ix + width - node.getBounds().width - sibDist / 2;
	} else {
	    // Center node above all children ....
	    node.ox = ix + (width - node.getBounds().width - sibDist)/2;
	    if (w < ix + width)
		w = ix + width;
	}
    } else { // Center node above all children ....
	node.ox = ix + (width - node.getBounds().width - sibDist)/2;
	if (w < ix + width)
	    w = ix + width;
    }  

//     DbgOutput.println(1,"Node: " + node.nodes[0].nodenum + " " + node.ox + 
// 	" " + node.oy);

    if (nochild) {
	
	node.widthbelow = width;
      return width + sibDist;

    }
    else {

	node.widthbelow = width;
      return width;

    }
  }

public Dimension getPreferredSize(JComponent c) {
    return c.getSize();
}

}

    // td.getTopLevelAncestor().setVisible(true);
//     int width  = td.getBounds().width;
//     int height = td.getBounds().height;
//     int cwidth = td.root.getBounds().width;
//     int cheight = td.root.getBounds().height;
    
//     td.root.reshape((width - cwidth)/2, (height - cheight) /2 , 
// 		    cwidth, cheight);



