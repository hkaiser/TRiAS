// TreeDisplay.java
// Copyright (c) 1998, Regents of the University of California
// $Id: TreeDisplay.java,v 1.2 1999/06/27 00:17:39 marcel Exp $

import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.border.*;
import java.awt.*;

public class TreeDisplay extends JComponent {

  public SuperNode root;
  public Font font;
  public FontMetrics fm;
  public boolean shownodes;
  public TreeView tv;
  public TreeDisplayUI ui;

  public TreeDisplay(TreeView tv) {
      //    this.root = root;
    fm = null;
    root = null;
    shownodes = false;
    
    this.tv = tv;

    setLayout(null);
    // add(root);

    ui = new TreeDisplayUI();

    setUI(ui);

    font = new Font("Dialog", Font.PLAIN, 10);
  }

  public void setRoot(SuperNode root) {
      
      this.root = root;
      add(root);
  }

}

    //    addSuperNodes(root);

    // setDebugGraphicsOptions(DebugGraphics.LOG_OPTION);
// public Dimension getMinimumSize() {
// return getPreferredSize();
// }
//   private void addSuperNodes(SuperNode root) {
//     add(root);
//   }


//  public EtchedBorder eborder;
    //    eborder = new EtchedBorder(EtchedBorder.RAISED);
    // setDebugGraphicsOptions(DebugGraphics.LOG_OPTION);

	//g.setClip((width - cwidth)/2, (height - cheight) /2 , 
	//	  cwidth, cheight);
	//g.translate((width - cwidth)/2, (height - cheight) /2);

	//UIManager.getUI(td.root).update(g,td.root);

	//td.root.paint(g);

	//SwingUtilities.paintComponent(g,td.root,td,
	//(width - cwidth)/2, 
	//			      (height - cheight)/2, 
	//			      cwidth, cheight);
