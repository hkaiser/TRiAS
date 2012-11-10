// TreeView.java
// Copyright (c) 1998, Regents of the University of California
// $Id: TreeView.java,v 1.4 1999/12/14 06:08:13 marcel Exp $

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;

class FitAction extends AbstractAction {

//class FitAction extends ActionListener {

JDesktopPane desktop;
JComponent c;

public FitAction(JComponent c, JDesktopPane desktop) {

    this.c = c;
    this.desktop = desktop;
}

public void actionPerformed(ActionEvent e) {
    
    Insets i = desktop.getInsets();
    
    Rectangle bounds = c.getBounds();
    
    bounds.width = desktop.getSize().width - i.left - i.right;
    bounds.x = 0;
    c.setBounds(bounds);
    c.repaint();
}

}


// This is no longer used ... 05/27/98 ...

class TileAction extends AbstractAction {

// class TileAction extends ActionListener {

TreeView tv;

public TileAction(TreeView tv) {
    
    this.tv = tv;
}

public void actionPerformed(ActionEvent e) {
    
    // tv.tfitAction.actionPerformed( null );
//     tv.globalAction.actionPerformed( null );
//     tv.gfitAction.actionPerformed( null );

//     Point location = tv.getLocation();
//     Rectangle bounds = tv.gv.getBounds();

//     location.y = bounds.y  + bounds.height;

//     tv.setLocation(location);
//     tv.repaint();

    tv.tile();
}

}

public class TreeView extends JInternalFrame implements ActionListener {

public static 
Dimension initInternalSize = new Dimension(300,300); // internal frame size

public JDesktopPane desktop;
public TreeDisplay td;
public SuperNode   root;
public Node        rootNode;
public int         pathleaf;
public boolean     shownodes = false;
public boolean     showstats = false;
public boolean     showonlyleaf = false;

public Color[]     pallette;
public float[]       stats;

public float realMinStat, realMaxStat;
public float minStat, maxStat;
public double ratio;

public Component       legend;
public JScrollPane     scroll;

public final static String palettePath = "../treeview/palette/";

public String statTitle = "Nodenum (mod) 256";

public GlobalView gv;

public Dimension  minsize = new Dimension(50,50);

// public JToolBar toolbar;

public JMenuBar menubar;

public EventQueue eq;
public JButton cButton;
public Button tButton;
public ActionEvent ae;

public JCheckBoxMenuItem leafMenuItem;

public boolean centeroot = false;
public JComponent hitcomp;
public boolean centerhit = false;

public Vector nodeviews;
public Vector nodedumps;

public DisplayPredInfo[] predsA;
public DisplayPredInfo[] predsB;
// public int predMutex = 0;

AbstractAction nodeAction, pathAction, centerAction, statAction,
    paletteAction, globalAction, gfitAction, tfitAction, tileAction,
    cntrootAction, minAction, maxAction, onlyleafAction;

// ActionListener nodeAction, pathAction, centerAction, statAction,
//     paletteAction, globalAction, gfitAction, tfitAction, tileAction,
//     cntrootAction;

public void tile() {

    if (hitcomp == null)
	centeroot = true;
    else
	centerhit = true;

    tfitAction.actionPerformed( null );

    // Point location = getLocation();	
    Rectangle tbounds = getBounds();
    Rectangle dbounds = desktop.getBounds();

    if (!gv.isClosed() && !gv.isIcon() && gv.isShowing()) {
	// globalAction.actionPerformed( null );
	gfitAction.actionPerformed( null );

	Rectangle bounds = gv.getBounds();	
	tbounds.y = bounds.y  + bounds.height;
	// setLocation(location);
	setBounds(tbounds);
    }

    int i, j, k;

    Point tloc;
    NodeView nView;
    NodeDump nDump;

    j = 0; k = 0;

    for(i = 0; i < nodeviews.size(); i++) {
	
	nView = (NodeView) nodeviews.elementAt(i);
	if (!nView.isClosed() && !nView.isIcon() && nView.isShowing()) {
	    tloc = nView.getLocation();
	    tloc.x = j * 75;
	    if (tloc.x > dbounds.width - 10) {
		j = 0;
		tloc.x = j * 75;
		k++;
	    }
	    tloc.y = tbounds.y + tbounds.height + (k*20);
	    j++;
	    nView.setLocation(tloc);
	    nView.repaint();
	    nView.toFront();		    
	}

    }

    for(i = 0; i < nodedumps.size(); i++) {
	
	nDump = (NodeDump) nodedumps.elementAt(i);
	if (!nDump.isClosed() && !nDump.isIcon() && nDump.isShowing()) {
	    tloc = nDump.getLocation();
	    tloc.x = j * 75;
	    if (tloc.x > dbounds.width - 10) {
		j = 0;
		tloc.x = j * 75;
		k++;
	    }
	    tloc.y = tbounds.y + tbounds.height + (k*20);
	    j++;
	    nDump.setLocation(tloc);
	    nDump.repaint();
	    nDump.toFront();
	}

    }

    repaint();

}

public int ldColors(String filename) throws IOException {

    int[] r,g,b;

    int i;

    Color[] palette = new Color[256];
    
    FileInputStream filein = new FileInputStream(filename);

    r = new int[256];
    g = new int[256];
    b = new int[256];
    
    for (i=0; i < palette.length; i++)
	r[i] = filein.read();
    for (i=0; i < palette.length; i++)
	g[i] = filein.read();
    for (i=0; i < palette.length; i++)
	b[i] = filein.read();
    
    for (i=0; i < palette.length; i++) {
	palette[i] = new Color(r[i],g[i],b[i]);
	// DbgOutput.println(1,palette[i]);
    }

    pallette = palette;

    return (256);
}

public int ldColors() {

    JFileChooser chooser = new JFileChooser(palettePath);
    chooser.setDialogTitle("Choose Palette");
    chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    
    boolean fileOk = false;
    
    int result = 0;

    while (!fileOk) {
	
	try {
	    
	    if (chooser.showDialog(this, "Ok") != 0)
		return result;
	    
	    result = ldColors(chooser.getSelectedFile().getPath());

	    fileOk = true;

	} catch (Exception e) {
	    
	    JOptionPane.showMessageDialog(this,
		"Error loading selected palette: " + e, "Error: Load Palette",
		JOptionPane.ERROR_MESSAGE);
	    
	    e.printStackTrace();
	}
	
    }

    getTopLevelAncestor().repaint();

    return (result);
}

public void rStats() {

    for (int i=0; i < stats.length; i++)
	stats[i] = i % 256;

}

public TreeView (JDesktopPane desktop) throws LibgistException {

    super("Tree View");

    this.desktop = desktop;

    // initialize stats
    stats = new float[10000];
    rStats();

    // load pallette ...
    //try {
	// ldColors(palettePath + "earth.raw");
    
    // set default pallette to grayscale for now ...
    pallette = new Color[256];
    for (int i = 0; i < 256; i++)
	pallette[i] = new Color(i,i,i);
//     } catch (IOException e) {
// 	DbgOutput.println(1,"Couldn't find earth.raw: " + e);
//     }

    // Initialize preds to size 256 ..
    predsA = new DisplayPredInfo[256];
    predsB = new DisplayPredInfo[256];

    for (int i = 0; i < 256; i++)
	predsA[i] = new DisplayPredInfo();
    for (int i = 0; i < 256; i++)
	predsB[i] = new DisplayPredInfo();

    eq = Toolkit.getDefaultToolkit().getSystemEventQueue();
    
    legend = new JComponent() {
	
	public Dimension size = new Dimension(100,256 + 10);

	public Font font;
	public FontMetrics fm;

	public void paint(Graphics g) { 

	    if (font == null) {
		font = new Font("Dialog", Font.PLAIN, 10);
		g.setFont(font);
		fm = g.getFontMetrics();
	    }

	    int w,j;


	    // paint vert
	    
	    g.setFont(font);
	    
	    // i = PaintScale.vertical(g, fm, 14, 5, 260, minStat, maxStat, 10, 0);
	    w = PaintScale.vertical(g, fm, 2, 5, 260, minStat, maxStat, 10, 1);

	    for(j=0; j < pallette.length; j++) {
		g.setColor(pallette[j]);
		g.fillRect(w + 4, 260 - j, 10, 1);
	    }


	    if (size.width != w + 16) {
		DbgOutput.println(1,"RESIZING");
		size.width = w + 16;
		setSize(size);
		// reshape(
		// invalidate();
		// validate();
		td.tv.validate();
		//td.tv.repaint();
		// validate();
	    }
	}

	public Dimension getPreferredSize() {
 	    return size;
	}

 	public Dimension getMinimumSize() {
 	    return size;
 	}
    };

    pathleaf = -1;
    
    // Constructs internal frame for showing tree.
    setSize(initInternalSize);
    setResizable(true);
    setMaximizable(true);
    setIconifiable(true);
    // aFrame.setBorder(eBorder);

    // Testing TreeDisplay ...
    getContentPane().setLayout(new BorderLayout());
	    
    int rootNum;

    rootNode = new Node(/* rootNum = */ Libgist.getRoot(), 
	Libgist.getNonce(Libgist.getRoot()));

    // DbgOutput.println(1,"RootNum" + rootNum);

    Node[] nodes = new Node[1];
    nodes[0] = rootNode;

    td = new TreeDisplay(this);
    root = new SuperNode(nodes,0,0,td);
    
    td.setRoot(root);

    
    scroll = new JScrollPane(td);
    // scroll.getViewport().setBackingStoreEnabled(true);
    getContentPane().add(scroll, BorderLayout.CENTER);

    // toolbar = new JToolBar();
    menubar = new JMenuBar();

    statAction = new AbstractAction("Stat") {

	// statAction = new ActionListener("Stat") {

	public void actionPerformed(ActionEvent e) {
	    
	    if (showstats)
		hideStats();
	    else
		showStats(stats.length, stats, statTitle);

 	}

    };


    paletteAction = new AbstractAction("Pal") {

	//    paletteAction = new ActionListener("Pal") {

	public void actionPerformed(ActionEvent e) {
	    ldColors();
	    // for (int i = 0; i < 256; i++)
	    // DbgOutput.println(1,pallette[i]);
	}
    };

    gv = new GlobalView(td.tv);

    nodeviews = new Vector();
    nodedumps = new Vector();

    tfitAction =  (AbstractAction)  new FitAction(this, desktop);
    gfitAction =  (AbstractAction)  new FitAction(gv, desktop);
    tileAction =  (AbstractAction)  new TileAction(this);

    nodeAction = new AbstractAction("Node") {

	//    nodeAction = new ActionListener("Node") {

        public void actionPerformed(ActionEvent e) {
	    // DbgOutput.println(1,"NODE");
	    if (td.shownodes)
		td.shownodes = false;
	    else
		td.shownodes = true;

	    // td.root.panels[0].invalidate();
	    // td.root.invalidate();		    
	    // td.invalidate();
	    // getTopLevelAncestor().invalidate();
	    // getTopLevelAncestor().validate();
	    // getTopLevelAncestor().repaint();
	    //	    td.validate();
	    td.repaint();
	}
    };

    final JOptionPane pane = new JOptionPane("Node:", 
	JOptionPane.QUESTION_MESSAGE,
	JOptionPane.OK_CANCEL_OPTION, null,
	null, null);

    final JOptionPane maxPalPane = new JOptionPane("Max Value: " 
	+ realMaxStat,
	JOptionPane.QUESTION_MESSAGE,
	JOptionPane.OK_CANCEL_OPTION, null,
	null, null);
    
    final JOptionPane minPalPane = new JOptionPane("Min Value: "
	+ realMinStat,
	JOptionPane.QUESTION_MESSAGE,
	JOptionPane.OK_CANCEL_OPTION, null,
	null, null);

    pathAction = new AbstractAction("Path") {

	// pathAction = new ActionListener("Path") {
	
        public void actionPerformed(ActionEvent e) {
	    String          result;

	    Container j = (Container) e.getSource();

	    // 	    while (!(j instanceof TreeView))
	    // 		j = j.getParent();
	    
	    // TreeView        tv = (TreeView) j;

	    TreeView tv = TreeView.this;

	    int nodenum;
	   
	    if (pathleaf == -1)
		nodenum = 0;
	    else
		nodenum = pathleaf;

	    JDialog dialog = pane.createDialog(tv, "Show Path");

	    pane.setWantsInput(true);
	    pane.setInitialSelectionValue(Integer.toString(nodenum));
	    pane.selectInitialValue();
	    dialog.show();
	    
	    result = (String) pane.getInputValue();

	    int[] path = new int[100];

	    try {
		nodenum = Integer.valueOf(result).intValue();
	    } catch (NumberFormatException ne) {
		System.out.println("The node could not be located.");
		return;
	    }

	    try {
		Libgist.getPath(nodenum,path);
	    } catch (LibgistException ex) {
		System.out.println("Could not find path to: " + nodenum);
		System.out.println(ex);
		ex.printStackTrace();
		return;
	    }
	    
	    try {
		showPath(nodenum);
	    } catch (Exception ex) {
		System.out.println("Nope: " + ex);
		ex.printStackTrace();
		return;
	    }
	}
    };
    
    maxAction = new AbstractAction("ScaleMaxValue") {
	
	public void actionPerformed(ActionEvent e) {

	    String result;
	    
	    JDialog dialog = maxPalPane.createDialog(TreeView.this, 
		"Set Scale Max");

	    maxPalPane.setMessage("Max Value: " + realMaxStat);
	    maxPalPane.setWantsInput(true);
	    maxPalPane.setInitialSelectionValue(
		Float.toString(maxStat));
	    maxPalPane.selectInitialValue();
	    dialog.show();

	    result = (String) maxPalPane.getInputValue();
	    
	    try {
		float t = Float.valueOf(result).floatValue();
		if (t >= minStat) {
		    maxStat = t;
		    if ((maxStat - minStat) <= 0)
			ratio = -1;
		    else
			ratio = 
			    (double) 256.0 / (double)(maxStat - 
				minStat /* + 1 */);		    
		}
		else
		    System.out.println("Invalid entry");
		getTopLevelAncestor().repaint();
	    } catch (NumberFormatException ne) {
		System.out.println("Invalid entry");
		return;
	    }
	}
    };

    onlyleafAction = new AbstractAction("Shoe Only Leaf") {

	public void actionPerformed(ActionEvent e) {
	    //     if (showonlyleaf == false)
	    // 		showonlyleaf = true;
	    // 	    else
	    // 		showonlyleaf = false;
	    showStats(stats.length, stats, statTitle);
	}
    };

    minAction = new AbstractAction("ScaleMinValue") {
	
	public void actionPerformed(ActionEvent e) {

	    String result;
	    
	    JDialog dialog = minPalPane.createDialog(TreeView.this, 
		"Set Scale Min");

	    minPalPane.setMessage("Min Value: " + realMinStat);
	    minPalPane.setWantsInput(true);
	    minPalPane.setInitialSelectionValue(
		Float.toString(minStat));
	    minPalPane.selectInitialValue();
	    dialog.show();

	    result = (String) minPalPane.getInputValue();
	    
	    try {		
		float t = Float.valueOf(result).floatValue();
		if (t < maxStat) {
		    minStat = t;
		    if ((maxStat - minStat) <= 0)
			ratio = -1;
		    else
			ratio = 
			    (double) 256.0 / (double)(maxStat - 
				minStat /* + 1 */);
		}
		else
		    System.out.println("Invalid entry");
		getTopLevelAncestor().repaint();
	    } catch (NumberFormatException ne) {
		System.out.println("Invalid entry");
		return;
	    }
	}
    };

    // Center view on path ...
    centerAction = new AbstractAction("Center") {
	
	//    centerAction = new ActionListener("Center") {

        public void actionPerformed(ActionEvent e) {

	    Container j = (Container) e.getSource();

// 	    while (!(j instanceof TreeView))
// 		j = j.getParent();
	    
// 	    TreeView        tv = (TreeView) j;

	    TreeView  tv = TreeView.this;

	    try {
		if (pathleaf != -1)
		    showPath(tv.pathleaf);
	    } catch (LibgistException ex) {
		return;
	    }
	}
    };

    cntrootAction = new AbstractAction("Center - root") {

	// cntrootAction = new ActionListener("Center - root") {
	
	public void actionPerformed(ActionEvent e) {
	    
	    // DbgOutput.println(1,e);
	    center();
	    getTopLevelAncestor().repaint();
	}
    };
    
    final JDesktopPane fdesktop = desktop;

    globalAction = new AbstractAction("Global") {

	// globalAction = new ActionListner("Global") {

	public void actionPerformed(ActionEvent e) {
	    
	    // 	    if (gv == null) {
	    // 		gv = new GlobalView(td.tv);
	    // 	    }
	    
	    // DbgOutput.println(1,"GLOBAL");

	    if (!fdesktop.isAncestorOf(gv)) {
		fdesktop.add( gv, JLayeredPane.PALETTE_LAYER);
	    }

	    try {
		if (gv.isClosed()) {
		    
		    gv.setClosed( false );

		} else if (gv.isIcon()) {

		    gv.setIcon( false );

		} else
		    gv.setVisible( true );

	    } catch (Exception ex) {
		System.out.println("WHAT - global view: " + ex);
	    }

	}
    };
    
    JMenu navigatemenu = new JMenu("Navigate");
    JMenu filemenu = new JMenu("Legend");
    JMenu alignmenu = new JMenu("Align");

    JMenuItem menuItem;

    // File menu ...
    menuItem = new JMenuItem("Choose colors");
    menuItem.addActionListener(paletteAction);
    filemenu.add(menuItem);

    menuItem = new JMenuItem("Set Scale Max");
    menuItem.addActionListener(maxAction);
    filemenu.add(menuItem);

    menuItem = new JMenuItem("Set Scale Min");
    menuItem.addActionListener(minAction);
    filemenu.add(menuItem);

    leafMenuItem = new JCheckBoxMenuItem("Leaf Stats Only");
    leafMenuItem.addActionListener(onlyleafAction);
    filemenu.add(leafMenuItem);

    menubar.add(filemenu);

    // Navigate menu ...
    menuItem = new JMenuItem("Path to node");
    menuItem.addActionListener(pathAction);
    navigatemenu.add(menuItem);

    menuItem = new JMenuItem("Center on path");
    menuItem.addActionListener(centerAction);
    navigatemenu.add(menuItem);
    
    menuItem = new JMenuItem("Center on root");
    menuItem.addActionListener(cntrootAction);
    navigatemenu.add(menuItem);

    navigatemenu.addSeparator();

    menuItem = new JMenuItem("Show Global View");
    menuItem.addActionListener(globalAction);
    navigatemenu.add(menuItem);

    menubar.add(navigatemenu);

    // Align menu ...
    menuItem = new JMenuItem("Align Tree View");
    menuItem.addActionListener(tfitAction);
    alignmenu.add(menuItem);
    
    menuItem = new JMenuItem("Align Global View");
    menuItem.addActionListener(gfitAction);
    alignmenu.add(menuItem);

    alignmenu.addSeparator();
    
    menuItem = new JMenuItem("Tile all");
    menuItem.addActionListener(tileAction);
    alignmenu.add(menuItem);

    menubar.add(alignmenu);

    // toolbar.add(pathAction).setText("Path");
    // toolbar.add(nodeAction).setText("Node");
    // toolbar.add(centerAction).setText("Center");
    // toolbar.add(statAction).setText("Stat");
    // toolbar.add(paletteAction).setText("Pal");
    // toolbar.add(globalAction).setText("Global");
    // toolbar.add(tileAction).setText("Tile");
    // toolbar.add(tfitAction).setText("Fit-TV");
    // toolbar.add(gfitAction).setText("Fit-GV");

//     cButton = toolbar.add(cntrootAction);
//     cButton.setText("Center - root");
    // toolbar.addActionListener(this);

    // This button and action is so that levels can be aligned
    // correctly.
    tButton = new Button("Dummy button");
    tButton.addActionListener(this);
    // tButton.setText("Dummy button");

    ae = new ActionEvent(tButton, 
	ActionEvent.ACTION_PERFORMED, "fitlevels", 0);
    
    getRootPane().setJMenuBar(menubar);

    // toolbar.setFloatable(true);
    
    legend.setVisible(false);

    // getContentPane().add(toolbar, BorderLayout.NORTH);

    getContentPane().add(legend, BorderLayout.WEST);

    centeroot = true;

    setVisible(true);

}

public int getIndex(int num, Node[] nodes) {

    for(int i = 0; i < nodes.length; i++)
	if (nodes[i].nodenum == num)
	    return i;

    return (-1);
}

public void showPath(int nodenum) throws LibgistException {

    try {
	refresh();
	if ((pathleaf != nodenum) && (pathleaf >= 0))
	    undoPath(pathleaf);
	pathleaf = nodenum;

	centeroot = true; // must come before adjustPath ...

	adjustPath();
	
	eq.postEvent(ae);
	// getTopLevelAncestor().repaint(0);


	// ActionEvent ae = new ActionEvent(tButton, 
	//ActionEvent.ACTION_PERFORMED, "Center - root", 0);
	
	
// 	DbgOutput.println(1,);
// 	DbgOutput.println(1,ae);

// 	EventQueue eqs = Toolkit.getDefaultToolkit().getSystemEventQueue();
// 	eqs.postEvent(ae);
	


	//DbgOutput.println(1,eqs.peekEvent());
	
	// DbgOutput.println(1,eqs);
// 	DbgOutput.println(1,);
	// Thread.yield();
	// notifyAll();

    } catch (LibgistException e) {
	System.out.println(e);
	e.printStackTrace();

	throw e;
    }
}

public void centerhitcomp(int oldloc) {

    JViewport view   = scroll.getViewport();
    Dimension size   = scroll.getSize();
    int       newloc = ((SuperNode) hitcomp).ox;
    Point     npt    = view.getViewPosition();

    npt.x += newloc - oldloc;

    // DbgOutput.println(1,"new: " + newloc + " " + "old: " + oldloc);

    // view.setBackingStoreEnabled( true );
    view.setViewPosition(npt);

    // DbgOutput.println(1,view.isBackingStoreEnabled());
    // view.validate();
    
    centerhit = false;
}

public void center() {

    // Center on root ...
    JViewport view = scroll.getViewport();
    Dimension size = scroll.getSize();
    Insets in = scroll.getInsets();
    size.width -= in.left + in.right;
    size.height -= in.top + in.bottom;
    
    Point rl = new Point(root.ox,root.oy);
    Dimension rs = root.getSize();
    
    // DbgOutput.println(1,view.getViewPosition());
    // DbgOutput.println(1,size + " " + rl);
    rl.x -= (size.width - rs.width) / 2;
    rl.y = 0;
    // DbgOutput.println(1,size + " " + rl);

    // view.setBackingStoreEnabled( true );
    view.setViewPosition(rl);
    // view.validate();

    centeroot = false;

    // view.validate();
    // view.repaint();
    // scroll.validate();
    // scroll.repaint();
    // validate();
    // getTopLevelAncestor().repaint();
    
    // DbgOutput.println(1,root.getLocation());
    // DbgOutput.println(1,root.ox + ", " + root.oy);

    // DbgOutput.println(1,view.getViewPosition());
    // DbgOutput.println(1,);
    
}

public void fitlevels() {

    Dimension size = scroll.getSize();
    Insets in = scroll.getInsets();
    size.width -= in.left + in.right;

    int i,j,num;

    for (i = 0; i < td.ui.levels.size(); i++) {

	Vector sibs = (Vector) td.ui.levels.elementAt(i);

	num = sibs.size();

	DbgOutput.println(1,"level: " + i + " " + "size: " + num);

	SuperNode node;

	int leftover = 0;
	int istart = 0, iend, rwidth;

 	for (j = 0; j < num; j++) {
	    node = (SuperNode) sibs.elementAt(j);
	    node.resizeRect.setBounds(node.getBounds());

	    iend = (int) Math.floor(((float)( j + 1 ) * (float) size.width) / 
		(float) num);
	    
	    node.resizeRect.width = iend - istart - 4 /* border */  + leftover 
		- td.ui.sibDist;

	    rwidth = node.resizePanels(false, true);

	    if (rwidth < node.resizeRect.width)
		leftover = node.resizeRect.width - rwidth;
	    //	    else
	    // DbgOutput.println(1,"Over: " + (rwidth - node.resizeRect.width));
	    istart = iend;
	}
// 	    lw += ((SuperNode) sibs.elementAt(j)).widthbelow;

// 	if ( lw < size.width

	
    }
    
}

public void showStats(int count, float[] stats, String label) {

    statTitle = label;
    
    if (pallette == null) {
	JOptionPane.showMessageDialog(this,
	    "Error no palette selected", "Error: No Palette",
	    JOptionPane.ERROR_MESSAGE);
	return;
    }

    this.setTitle("Tree View: " + label);
    showStats(count, stats);
}

public void showStats(int count, float[] stats) {
    
    //    DbgOutput.println(1,"count: " + count);
    this.stats = stats;
    
    minStat = stats[1];
    maxStat = stats[1];

    int level;

    for (int i=1; i < stats.length; i++) {
	level = Libgist.getLevel(i);
	if (level == -1)
	    break;
	if (Float.isInfinite(stats[i]))
	    continue;
	if (Float.isNaN(stats[i]))
	    continue;
	if (leafMenuItem.getState() && (level != 1))
	    continue;
	if (minStat > stats[i])
	    minStat = stats[i];
	else if (maxStat < stats[i])
	    maxStat = stats[i];
    }

    if ((maxStat - minStat) <= 0)
	ratio = -1;
    else
	ratio = (double) 256.0 / (double)(maxStat - minStat /* + 1 */);

    realMinStat = minStat;
    realMaxStat = maxStat;

    showstats = true;
    legend.setVisible(true);

    Dimension sz = getSize();
    if (sz.height < getMinimumSize().height)
	sz.height = getMinimumSize().height;

    setSize(sz);
    validate();
    getTopLevelAncestor().repaint();
}

public void hideStats() {

    this.setTitle("Tree View");
    legend.setVisible(false);
    showstats = false;
    validate();
}

private void undoPath(int nodenum) throws LibgistException {

    // assuming the nodes on the path exist.

    int i;
    int[] path = new int[100];
    int pl = Libgist.getPath(nodenum, path);

    SuperNode sn = root;
    int nindex = 0;
    
    for (i=0; i < pl; i++) {
	nindex = getIndex(path[pl - i - 1],sn.nodes);
	sn.onpath = false;
	sn.pathchild = -1;
	sn.nodes[nindex].onpath = false;
	// sn.panels[nindex-sn.min].node.onpath = false;
	sn = sn.children[nindex];
    }

}

public int[] path = new int[100];
public int pl = 0;

public void adjustPath() throws LibgistException {

    NodeView tView;

    int i;
    
    pl = Libgist.getPath(pathleaf, path);
    Node[] offspring;

    SuperNode  sn  = root;
    int nindex = 0;

    Node tempNode;

    for (i = 0; i < pl; i++) {

	nindex = getIndex(path[pl - i - 1],sn.nodes);

	if ((nindex < sn.min) || (nindex >= sn.min + sn.numPanels))
	    sn.adjustPanels(nindex);

	if (i+1 != pl) {
	    sn.panels[nindex-sn.min].open = true;
	    sn.panels[nindex-sn.min].node.open = true;
	}
	
	sn.open   = true;
	sn.onpath = true;
	sn.panels[nindex-sn.min].node.onpath = true;
	
	// clean this up later ...
	tempNode = sn.panels[nindex-sn.min].node;

	for (int j=0; j < tempNode.topViews.length; j++) {
	    tView = tempNode.topViews[j];
	    if (tView != null) {
		tView.pl = pl;
		tView.showPathChild();
		tView.repaint();
	    }
	}
	

	for (int j = 0; j < sn.numPanels; j++)
	    if ((sn.panels[j].node.onpath == false) || (i+1 == pl))
		if (!sn.isVisible()) {
		    sn.panels[j].open = false;
		    if (sn.children[sn.panels[j].id] != null)
			sn.children[sn.panels[j].id].open = false;
		}

	sn.setVisible(true);

	if ((sn.children[nindex] == null) && (i+1 != pl)) {
	    offspring = sn.nodes[nindex].getChildren();
	    sn.children[nindex] = new SuperNode(offspring,0,0,td,sn,nindex);
	    sn.pathchild = nindex;

// 	    if (sn.pathchild == 0)
// 		DbgOutput.println(1,"HERE: " +
// 		    sn.panels[0].node.nodenum + " " + sn.pathchild);

	    sn = sn.children[nindex]; // new SuperNode(offspring,0,0,td);
	    td.add(sn);
	} else {
	    if (i+1 != pl) {
		sn.pathchild = nindex;
// 		if (sn.pathchild == 0)
// 		    DbgOutput.println(1,"HERE2: " +
// 			sn.panels[0].node.nodenum + " " + sn.pathchild +
// 				       " " + i + " " + pl + " " + path[pl - i - 1]);

	    }
	    sn = sn.children[nindex];
	}
    }
    
    validate();
    getTopLevelAncestor().repaint();
}

public void refresh() throws LibgistException {

    if (root.children[0] != null)
	refreshChildren(root.children[0], root.nodes[0]);
    else if (rootNode.nonce != Libgist.getNonce(rootNode.nodenum)) {
	rootNode = new Node(Libgist.getRoot(), 
	    Libgist.getNonce(Libgist.getRoot()));
	root.nodes[0] = rootNode;
	root.min = 0;
	if (rootNode.nDump != null) {
	    rootNode.nDump.refresh();
	    DbgOutput.println(1,"Refresh: " + rootNode.nodenum);
	}
    }

    validate();
    getTopLevelAncestor().repaint();
}

public void refreshChildren(SuperNode sn, Node parent) throws LibgistException {

    int i, j;
    int childnum = sn.nodes.length;

    // System.out.println("RefreshChildren: " + parent.nodenum);

    if (parent.nonce != Libgist.getNonce(parent.nodenum)) {
	
	parent.nonce = Libgist.getNonce(parent.nodenum);

	if (parent.nDump != null) {
	    parent.nDump.refresh();
	    DbgOutput.println(1,"Refresh: " + parent.nodenum);
	}

	if (parent.nViews != null) {
	    for (i=0; i < parent.nViews.size(); i++)
		((NodeView) parent.nViews.elementAt(i)).repaint();
	}

	int[]  childnos      = new int[Libgist.maxChildren()];
	Node[] nodes         = sn.nodes;
	SuperNode[] children = sn.children;
	childnum             = Libgist.getChildren(parent.nodenum, childnos);
	
	Node[] newnodes         = new Node[childnum];
	SuperNode[] newchildren = new SuperNode[childnum];
	
	for(i=0; i < childnum; i++) {
	    if ( (j = getIndex(childnos[i], nodes)) > 0) {
		newnodes[i]    = nodes[j];
		newchildren[i] = children[j];
	    } else {
		newnodes[i]    = new Node(childnos[i],
		    Libgist.getNonce(childnos[i]));
		newchildren[i] = null;
	    }
	}

	sn.nodes    = newnodes;
	sn.children = children;
	if (sn.min > childnum - sn.numPanels)
	    sn.min = childnum - sn.numPanels;
	sn.adjustPanels(sn.min);

	parent.childnum = childnum;
    }

    for(i=0; i < childnum; i++)
	if (sn.children[i] != null)
	    refreshChildren(sn.children[i], sn.nodes[i]);
	else {
	    // DbgOutput.println(1,"Checking leaf: " + sn.nodes[i].nodenum);
	    if (sn.nodes[i].nonce != Libgist.getNonce(sn.nodes[i].nodenum)) {
		sn.nodes[i].nonce = Libgist.getNonce(sn.nodes[i].nodenum);
		if (sn.nodes[i].nDump != null) {
		    sn.nodes[i].nDump.refresh();
		    DbgOutput.println(1,"Refresh: " + sn.nodes[i].nodenum);
		}
		if (sn.nodes[i].nViews != null) {
		    for (i=0; i < sn.nodes[i].nViews.size(); i++)
			((NodeView) sn.nodes[i].nViews.elementAt(i)).repaint();
		}
	    } 
	    // else {
// 		if (sn.nodes[i].nodenum == 2) {
// 		    System.out.println("Not refresh: " + sn.nodes[i].nodenum);
// 		    System.out.println("Nonce: " + sn.nodes[i].nonce);
// 		}
	    //	    }
	}
}


public void dispose() {

    if (gv != null) {
	gv.setVisible(false);
	gv.dispose();
    }

    int i;
    NodeView nView;
    NodeDump nDump;

    for (i = 0; i < nodeviews.size(); i++) {
	nView = (NodeView) nodeviews.elementAt(i);
	nView.setVisible(false);
	nView.dispose();
    }
    
    for (i = 0; i < nodedumps.size(); i++) {
	nDump = (NodeDump) nodedumps.elementAt(i);
	nDump.setVisible(false);
	nDump.dispose();
    }

    super.dispose();

}


public Dimension getMinimumSize() {

    if (showstats) {
	if (minsize.height < 
	    legend.getMinimumSize().height + 60) {
	    minsize.height = 
		legend.getMinimumSize().height + 60;
	}
    } else {
	minsize.width = minsize.height = 50;
    }

    return minsize;
}


public void actionPerformed(ActionEvent e) {

    //center();
    //repaint();
    centerhit = true;
    if (hitcomp == null)
	hitcomp = root;
    fitlevels();
    validate();
    repaint();
}

public DisplayPredInfo[] doublePredSize(DisplayPredInfo preds[]) {

    int size = preds.length;

    DisplayPredInfo[] newPreds = new DisplayPredInfo[2*size];

    int i;

    // copy objects from original array ...
    for (i = 0; i < size; i++)
	newPreds[i] = preds[i];

    // create a bunch of new entries ...
    for (i = size; i < 2*size; i++)
	newPreds[i] = new DisplayPredInfo();

    return newPreds;
}


}
