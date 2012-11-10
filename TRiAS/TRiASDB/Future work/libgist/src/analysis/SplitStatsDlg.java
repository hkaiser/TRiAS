// SplitStats.java
// Copyright (c) 1998, Regents of the University of California
// $Id: SplitStatsDlg.java,v 1.2 1999/06/27 00:17:35 marcel Exp $

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/* 
 * SplitStats: 
 * Dialog box that displays amdb_splitstats
 */

class SplitStatsDlg extends JDialog
{

SplitStats splitStats = new SplitStats(); // amdb_splitstats of current leaf (or avg)
TreeView treeView; // what displays the stats
int[] splitLeaves; // numbers of split leaves, displayed in dialog
int splitLeavesIdx; // index into splitLeaves: currently selected leaf

ButtonGroup selectorGroup;
JRadioButton avgBtn;
JRadioButton leafBtn;
JTextField leafFld;
JButton plusBtn;
JButton minusBtn;
JComboBox statsTypeBox;
ButtonGroup absGroup, weightedGroup;
JRadioButton absBtn, deltaBtn;
JRadioButton fullBtn, weightedBtn;

JLabel clusteringLbl, excCovLbl;
JLabel preSplitLbl, optSplitLbl, actualSplitLbl;
JLabel lossLbl, ohLbl, successLbl;
JTextField preClustFld, preEcFld; // Ec: excess coverage
JTextField optClustFld, optEcFld;
JTextField actualClustFld, actualEcFld;
JTextField excCovLossFld, clustLossFld;
JTextField clustOhFld, excCovOhFld;
JTextField clustSuccessFld, excCovSuccessFld;



public
SplitStatsDlg(JFrame parent)
{
    super(parent, "Split Statistics", false);
    Font defaultFont = new Font("Dialog", Font.PLAIN, 12);
    Insets defaultInsets = new Insets(0, 0, 0, 0);
    getContentPane().setLayout(null);

    // some positioning variables/constants
    int leftMargin = 15; 
    int yPos = 10; // used for relative positioning

    // Totals/Query radio buttons
    avgBtn = new JRadioButton("Average");
    avgBtn.setFont(defaultFont);
    avgBtn.setBounds(leftMargin - 5, yPos, 60, 20);
    avgBtn.setActionCommand("avg");
    avgBtn.setSelected(true);
    avgBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    setLeaf(0);
	}
    });
    getContentPane().add(avgBtn);

    leafBtn = new JRadioButton("Leaf:");
    leafBtn.setFont(defaultFont);
    leafBtn.setBounds(75, yPos, 60, 20);
    leafBtn.setActionCommand("leaf");
    leafBtn.setSelected(false);
    leafBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    try {
		// XXX look for that leaf number in array
	        int leafNo = Integer.parseInt(leafFld.getText());
		if (leafNo < 1) {
		    leafNo = 1;
		}
		setLeaf(leafNo);
	    } catch (NumberFormatException e) {
		setLeaf(1); // user fucked up -> reset to query 1
	    }
	}
    });
    getContentPane().add(leafBtn);

    selectorGroup = new ButtonGroup();
    selectorGroup.add(avgBtn);
    selectorGroup.add(leafBtn);

    plusBtn = new JButton("+");
    plusBtn.setFont(defaultFont);
    plusBtn.setBounds(230, 5, 45, 15);
    plusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    if (!selectorGroup.getSelection().getActionCommand().equals("leaf")) {
	        return;
	    }
	    if (splitLeaves[splitLeavesIdx+1] != 0) {
		// next entry in splitLeaves is valid
		splitLeavesIdx++;
	    }
	    setLeaf(splitLeaves[splitLeavesIdx]);
	}
    });
    getContentPane().add(plusBtn);

    minusBtn = new JButton("-");
    minusBtn.setFont(defaultFont);
    minusBtn.setBounds(230,20,45,15);
    //minusBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    minusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    if (!selectorGroup.getSelection().getActionCommand().equals("leaf")) {
	        return;
	    }
	    if (splitLeavesIdx > 1) {
		// next entry in splitLeaves is valid
		splitLeavesIdx--;
	    }
	    setLeaf(splitLeaves[splitLeavesIdx]);
	}
    });
    getContentPane().add(minusBtn);

    leafFld = new JTextField("1", 5);
    leafFld.setFont(defaultFont);
    leafFld.setBounds(140, yPos, 84, 20);
    leafFld.setHorizontalAlignment(JTextField.RIGHT);
    leafFld.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    /*
	    try {
	        int leafNo = Integer.parseInt(leafFld.getText());
		if (leafNo < 1) {
		    leafNo = 1;
		}
		setLeaf(leafNo);
	    } catch (NumberFormatException e) {
		setLeaf(1); // user fucked up -> reset to query 1
	    }
	    */
	}
    });
    getContentPane().add(leafFld);


    yPos += 45;

    // display option panel
    JLabel displayLbl = new JLabel("Display: ");
    displayLbl.setFont(defaultFont);
    displayLbl.setBounds(leftMargin, yPos, 60, 15);
    getContentPane().add(displayLbl);

    statsTypeBox = new JComboBox();
    statsTypeBox.setFont(defaultFont);
    statsTypeBox.setBounds(75, yPos, 175, 20);
    statsTypeBox.addItem("Cluster Loss");
    statsTypeBox.addItem("Exc. Cov. Loss");
    statsTypeBox.addItem("Cluster Success");
    statsTypeBox.addItem("Exc. Cov. Success");
    statsTypeBox.addItem("Opt. Cluster Delta");
    statsTypeBox.addItem("Actual Cluster Delta");
    statsTypeBox.addItem("Exc. Cov. Delta");
    statsTypeBox.setEditable(false);
    statsTypeBox.setSelectedIndex(0);
    statsTypeBox.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different type of stats: update display
	    setLeaf();
	}
    });
    getContentPane().add(statsTypeBox);

    yPos += 35;

    JLabel valuesLbl = new JLabel("I/O Values:");
    valuesLbl.setFont(defaultFont);
    valuesLbl.setBounds(leftMargin, yPos, 100, 20);
    getContentPane().add(valuesLbl);

    absBtn = new JRadioButton("Absolute");
    absBtn.setFont(defaultFont);
    absBtn.setBounds(140, yPos, 150, 25);
    absBtn.setSelected(true);
    absBtn.setActionCommand("abs");
    absBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setLeaf();
	}
    });
    getContentPane().add(absBtn);

    fullBtn = new JRadioButton("Full");
    fullBtn.setFont(defaultFont);
    fullBtn.setBounds(230, yPos, 150, 25);
    fullBtn.setSelected(false);
    fullBtn.setActionCommand("full");
    fullBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setLeaf();
	}
    });
    getContentPane().add(fullBtn);

    yPos += 20;

    deltaBtn = new JRadioButton("Deltas");
    deltaBtn.setFont(defaultFont);
    deltaBtn.setBounds(140, yPos, 145, 25);
    deltaBtn.setSelected(false);
    deltaBtn.setActionCommand("delta");
    deltaBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setLeaf();
	}
    });
    getContentPane().add(deltaBtn);

    weightedBtn = new JRadioButton("Weighted");
    weightedBtn.setFont(defaultFont);
    weightedBtn.setBounds(230, yPos, 145, 25);
    weightedBtn.setSelected(true);
    weightedBtn.setActionCommand("weighted");
    weightedBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setLeaf();
	}
    });
    getContentPane().add(weightedBtn);

    absGroup = new ButtonGroup();
    absGroup.add(absBtn);
    absGroup.add(deltaBtn);

    weightedGroup = new ButtonGroup();
    weightedGroup.add(fullBtn);
    weightedGroup.add(weightedBtn);

    yPos += 40;
    clusteringLbl = new JLabel();
    clusteringLbl.setText("Clustering");
    clusteringLbl.setBounds(160, yPos, 32, 20);
    getContentPane().add(clusteringLbl);

    excCovLbl = new JLabel();
    excCovLbl.setText("Exc. Cov.");
    excCovLbl.setBounds(255, yPos, 60, 20);
    getContentPane().add(excCovLbl);

    yPos += 25;
    preSplitLbl = new JLabel();
    preSplitLbl.setText("Pre-Split:");
    preSplitLbl.setBounds(leftMargin, yPos, 100, 20);
    getContentPane().add(preSplitLbl);

    preClustFld = new JTextField();
    preClustFld.setMargin(defaultInsets);
    preClustFld.setHorizontalAlignment(SwingConstants.RIGHT);
    preClustFld.setEditable(false);
    preClustFld.setBounds(120, yPos, 105, 20);
    preClustFld.setBackground(Color.white);
    preClustFld.setFont(defaultFont);
    getContentPane().add(preClustFld);

    preEcFld = new JTextField();
    preEcFld.setMargin(defaultInsets);
    preEcFld.setHorizontalAlignment(SwingConstants.RIGHT);
    preEcFld.setEditable(false);
    preEcFld.setBounds(235, yPos, 105, 20);
    preEcFld.setBackground(Color.white);
    preEcFld.setFont(defaultFont);
    getContentPane().add(preEcFld);

    yPos += 25;

    optSplitLbl = new JLabel();
    optSplitLbl.setText("Opt. Split:");
    optSplitLbl.setBounds(leftMargin, yPos, 80, 20);
    getContentPane().add(optSplitLbl);

    optClustFld = new JTextField();
    optClustFld.setMargin(defaultInsets);
    optClustFld.setHorizontalAlignment(SwingConstants.RIGHT);
    optClustFld.setEditable(false);
    optClustFld.setBounds(120, yPos, 105, 20);
    optClustFld.setBackground(Color.white);
    optClustFld.setFont(defaultFont);
    getContentPane().add(optClustFld);

    optEcFld = new JTextField();
    optEcFld.setMargin(defaultInsets);
    optEcFld.setHorizontalAlignment(SwingConstants.RIGHT);
    optEcFld.setEditable(false);
    optEcFld.setBounds(235, yPos, 105, 20);
    optEcFld.setBackground(Color.white);
    optEcFld.setFont(defaultFont);
    getContentPane().add(optEcFld);

    yPos += 25;

    actualSplitLbl = new JLabel();
    actualSplitLbl.setText("Actual Split:");
    actualSplitLbl.setBounds(leftMargin, yPos, 95, 20);
    getContentPane().add(actualSplitLbl);

    actualClustFld = new JTextField();
    actualClustFld.setMargin(defaultInsets);
    actualClustFld.setHorizontalAlignment(SwingConstants.RIGHT);
    actualClustFld.setEditable(false);
    actualClustFld.setBounds(120, yPos, 105, 20);
    actualClustFld.setBackground(Color.white);
    actualClustFld.setFont(defaultFont);
    getContentPane().add(actualClustFld);

    actualEcFld = new JTextField();
    actualEcFld.setMargin(defaultInsets);
    actualEcFld.setHorizontalAlignment(SwingConstants.RIGHT);
    actualEcFld.setEditable(false);
    actualEcFld.setBounds(235, yPos, 105, 20);
    actualEcFld.setBackground(Color.white);
    actualEcFld.setFont(defaultFont);
    getContentPane().add(actualEcFld);

    yPos += 25;

    lossLbl = new JLabel();
    lossLbl.setText("Loss:");
    lossLbl.setBounds(leftMargin, yPos, 80, 20);
    getContentPane().add(lossLbl);

    excCovLossFld = new JTextField();
    excCovLossFld.setMargin(defaultInsets);
    excCovLossFld.setHorizontalAlignment(SwingConstants.RIGHT);
    excCovLossFld.setEditable(false);
    excCovLossFld.setBounds(235, yPos, 105, 20);
    excCovLossFld.setBackground(Color.white);
    excCovLossFld.setFont(defaultFont);
    getContentPane().add(excCovLossFld);

    clustLossFld = new JTextField();
    clustLossFld.setMargin(defaultInsets);
    clustLossFld.setHorizontalAlignment(SwingConstants.RIGHT);
    clustLossFld.setEditable(false);
    clustLossFld.setBounds(120, yPos, 105, 20);
    clustLossFld.setBackground(Color.white);
    clustLossFld.setFont(defaultFont);
    getContentPane().add(clustLossFld);

    yPos += 25;

    ohLbl = new JLabel();
    ohLbl.setText("Overheads:");
    ohLbl.setBounds(leftMargin, yPos, 70, 20);
    getContentPane().add(ohLbl);

    clustOhFld = new JTextField();
    clustOhFld.setMargin(defaultInsets);
    clustOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    clustOhFld.setEditable(false);
    clustOhFld.setBounds(120, yPos, 105, 20);
    clustOhFld.setBackground(Color.white);
    clustOhFld.setFont(defaultFont);
    getContentPane().add(clustOhFld);

    excCovOhFld = new JTextField();
    excCovOhFld.setMargin(defaultInsets);
    excCovOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    excCovOhFld.setEditable(false);
    excCovOhFld.setBounds(235, yPos, 105, 20);
    excCovOhFld.setBackground(Color.white);
    excCovOhFld.setFont(defaultFont);
    getContentPane().add(excCovOhFld);

    yPos += 25;

    successLbl = new JLabel();
    successLbl.setText("Success [%]:");
    successLbl.setBounds(leftMargin, yPos, 100, 20);
    getContentPane().add(successLbl);

    clustSuccessFld = new JTextField();
    clustSuccessFld.setMargin(defaultInsets);
    clustSuccessFld.setHorizontalAlignment(SwingConstants.RIGHT);
    clustSuccessFld.setEditable(false);
    clustSuccessFld.setBounds(120, yPos, 105, 20);
    clustSuccessFld.setBackground(Color.white);
    clustSuccessFld.setFont(defaultFont);
    getContentPane().add(clustSuccessFld);

    excCovSuccessFld = new JTextField();
    excCovSuccessFld.setMargin(defaultInsets);
    excCovSuccessFld.setHorizontalAlignment(SwingConstants.RIGHT);
    excCovSuccessFld.setEditable(false);
    excCovSuccessFld.setBounds(235, yPos, 105, 20);
    excCovSuccessFld.setBackground(Color.white);
    excCovSuccessFld.setFont(defaultFont);
    getContentPane().add(excCovSuccessFld);

    // quit button
    yPos += 35;
    JButton quitBtn = new JButton("Quit");
    quitBtn.setFont(defaultFont);
    quitBtn.setBounds(125, yPos, 80, 30);
    quitBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    SplitStatsDlg.this.setVisible(false);
	}
    });
    getContentPane().add(quitBtn);

    setBounds(0, 0, 400, yPos+90);
    setVisible(false);
    //getContentPane().setBounds(0, 0, 400, 600);

    //pack();
}


// ((double) ((int) x*1000)/1000): Java's way of printing 3 significant digits
private double
truncate(double d, int digits)
{
    double p = Math.pow(10.0, (double) digits);
    return ((double) ((int) (d * p))/p);
}

// ((double) ((int) x*1000)/1000): Java's way of printing 3 significant digits
private float
truncate(float d, int digits)
{
    float p = (float) Math.pow(10.0, (double) digits);
    return ((float) ((int) (d * p))/p);
}


///////////////////////////////////////////////////////////////////////////////
// setLeaf -  updates display of currently selected leaf (incl. tree view)
//
// Description:
//	- extracts currently selected leaf number from dialog
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setLeaf()
{
    int leafNo = 0; // avg
    if (selectorGroup.getSelection().getActionCommand().equals("leaf")) {
	// we don't want the avg
	leafNo = splitLeaves[splitLeavesIdx];
    }
    setLeaf(leafNo);
}


///////////////////////////////////////////////////////////////////////////////
// setLeaf -  updates display of query (incl. tree view)
//
// Description:
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setLeaf(int leafNo)
{
    boolean absValues = absGroup.getSelection().getActionCommand().equals("abs");
        // true if the user wants to see absolute I/O numbers, not deltas
    boolean weighted =
        weightedGroup.getSelection().getActionCommand().equals("weighted");
        // true if the user wants to see absolute I/O numbers, not deltas
    Libgist.getSplitStats(leafNo, weighted, splitStats);

    // load leafFld
    if (leafNo != 0) {
	// otherwise it's the total
	leafFld.setText(Integer.toString(leafNo));
    }

    preClustFld.setText(Float.toString(truncate(splitStats.preIos, 2)));
    preEcFld.setText(Float.toString(truncate(splitStats.preExcCovLoss, 3)));
    if (absValues) {
	optClustFld.setText(Float.toString(truncate(splitStats.optIos, 3)));
    } else {
	optClustFld.setText(Float.toString(truncate(splitStats.optClusterDelta, 3)));
    }
    optEcFld.setText("0");
    if (absValues) {
	actualClustFld.setText(Float.toString(truncate(splitStats.actualIos, 3)));
    } else {
	actualClustFld.setText(Float.toString(truncate(splitStats.actualClusterDelta, 3)));
    }
    if (absValues) {
	actualEcFld.setText(Float.toString(truncate(splitStats.actualExcCovLoss, 3)));
    } else {
	actualEcFld.setText(Float.toString(truncate(splitStats.excCovDelta, 3)));
    }
    clustLossFld.setText(Float.toString(truncate(splitStats.clusterLoss, 3)));
    excCovLossFld.setText(Float.toString(truncate(splitStats.excCovLoss, 3)));
    clustOhFld.setText(Float.toString(truncate(splitStats.clusterOh, 3)));
    excCovOhFld.setText(Float.toString(truncate(splitStats.excCovOh, 3)));
    clustSuccessFld.setText(Float.toString(truncate(
        splitStats.clusterSuccess * 100.0f, 3)));
    excCovSuccessFld.setText(Float.toString(truncate(
        splitStats.excCovSuccess * 100.0f, 3)));

    // display stats in treeview
    Libgist.getSplitNodeStats(statsTypeBox.getSelectedIndex(),
        absValues, weighted);
    treeView.showStats(Libgist.nodeCnt, Libgist.displayStats,
        (String) statsTypeBox.getSelectedItem());
}

// init dialog for user interaction:
// set querySlider range to # of queries
public void
init(TreeView treeView)
{
    this.treeView = treeView;

    // make splitLeaves big enough (we assume that the split stats
    // were computed on the currently opened tree)
    splitLeaves = new int[Libgist.getPageCount()];
    Libgist.getSplitLeaves(splitLeaves);
    splitLeavesIdx = 0;
    leafFld.setText(Integer.toString(splitLeaves[splitLeavesIdx]));

    setLeaf(0);
}

}
