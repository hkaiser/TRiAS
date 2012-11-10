// PenaltyStats.java
// Copyright (c) 1998, Regents of the University of California
// $Id: PenaltyStatsDlg.java,v 1.2 1999/06/27 00:17:34 marcel Exp $

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/* 
 * PenaltyStats: 
 * Dialog box that displays amdb_penaltystats
 */

class PenaltyStatsDlg extends JDialog
{

PenaltyStats penaltyStats = new PenaltyStats(); // amdb_penaltystats of current leaf (or avg)
TreeView treeView; // what displays the stats
int numKeys; // total number of keys in penaltystats
int currKey; // currently selected key

ButtonGroup selectorGroup;
JRadioButton avgBtn;
JRadioButton keyBtn;
JTextField keyFld;
JButton plusBtn;
JButton minusBtn;
JComboBox statsTypeBox;
ButtonGroup absGroup, weightedGroup;
JRadioButton absBtn, deltaBtn;
JRadioButton fullBtn, weightedBtn;
JScrollPane keyPane;
JTextArea keyArea;

JLabel clusteringLbl, excCovLbl;
JLabel actualLeafLbl, optLeafLbl;
JLabel lossLbl, ohLbl, successLbl;
JTextField actualIosFld, excCovFld;
JTextField optIosFld;
JTextField clustLossFld;
JTextField excCovOhFld;
JTextField excCovSuccessFld;


public
PenaltyStatsDlg(JFrame parent)
{
    super(parent, "Penalty Statistics", false);
    Font defaultFont = new Font("Dialog", Font.PLAIN, 12);
    Insets defaultInsets = new Insets(0, 0, 0, 0);
    getContentPane().setLayout(null);

    // some positioning variables/constants
    int leftMargin = 15; 
    int yPos = 10; // used for relative positioning

    // Average/Key radio buttons
    avgBtn = new JRadioButton("Average");
    avgBtn.setFont(defaultFont);
    avgBtn.setBounds(leftMargin - 5, yPos, 60, 20);
    avgBtn.setActionCommand("avg");
    avgBtn.setSelected(true);
    avgBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    setKey(0);
	}
    });
    getContentPane().add(avgBtn);

    keyBtn = new JRadioButton("Key:");
    keyBtn.setFont(defaultFont);
    keyBtn.setBounds(75, yPos, 60, 20);
    keyBtn.setActionCommand("key");
    keyBtn.setSelected(false);
    keyBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    try {
	        int keyNo = Integer.parseInt(keyFld.getText());
		if (keyNo < 1) {
		    keyNo = 1;
		}
		setKey(keyNo);
	    } catch (NumberFormatException e) {
		setKey(1); // user fucked up -> reset to query 1
	    }
	}
    });
    getContentPane().add(keyBtn);

    selectorGroup = new ButtonGroup();
    selectorGroup.add(avgBtn);
    selectorGroup.add(keyBtn);

    plusBtn = new JButton("+");
    plusBtn.setFont(defaultFont);
    plusBtn.setBounds(230, 5, 45, 15);
    plusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    if (!selectorGroup.getSelection().getActionCommand().equals("key")) {
	        return;
	    }
	    if (currKey < numKeys) {
		currKey++;
		setKey(currKey);
	    }
	}
    });
    getContentPane().add(plusBtn);

    minusBtn = new JButton("-");
    minusBtn.setFont(defaultFont);
    minusBtn.setBounds(230,20,45,15);
    //minusBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    minusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    if (!selectorGroup.getSelection().getActionCommand().equals("key")) {
	        return;
	    }
	    if (currKey > 1) {
		currKey--;
		setKey(currKey);
	    }
	}
    });
    getContentPane().add(minusBtn);

    keyFld = new JTextField("1", 5);
    keyFld.setFont(defaultFont);
    keyFld.setBounds(140, yPos, 84, 20);
    keyFld.setHorizontalAlignment(JTextField.RIGHT);
    keyFld.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    try {
	        int keyNo = Integer.parseInt(keyFld.getText());
		if (keyNo < 1) {
		    keyNo = 1;
		}
		if (keyNo >= numKeys) {
		    keyNo = numKeys - 1;
		}
		currKey = keyNo;
		setKey(currKey);
	    } catch (NumberFormatException e) {
		setKey(1); // user fucked up -> reset to query 1
	    }
	}
    });
    getContentPane().add(keyFld);

    keyPane = new JScrollPane();
    keyPane.setOpaque(true);
    keyPane.setBounds(140,40,200,70);
    keyPane.setFont(defaultFont);
    getContentPane().add(keyPane);

    keyArea = new JTextArea();
    keyArea.setMargin(defaultInsets);
    keyArea.setBounds(0,0,200,70);
    keyArea.setFont(defaultFont);
    keyPane.getViewport().add(keyArea);


    yPos += 105;

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
	    setKey();
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
	    setKey();
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
	    setKey();
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
	    setKey();
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
    clusteringLbl.setBounds(120, yPos, 105, 20);
    clusteringLbl.setHorizontalAlignment(SwingConstants.CENTER);
    getContentPane().add(clusteringLbl);

    excCovLbl = new JLabel();
    excCovLbl.setText("Exc. Cov.");
    excCovLbl.setBounds(235, yPos, 105, 20);
    excCovLbl.setHorizontalAlignment(SwingConstants.CENTER);
    getContentPane().add(excCovLbl);

    yPos += 25;
    actualLeafLbl = new JLabel();
    actualLeafLbl.setText("Actual Leaf:");
    actualLeafLbl.setBounds(leftMargin, yPos, 100, 20);
    getContentPane().add(actualLeafLbl);

    actualIosFld = new JTextField();
    actualIosFld.setMargin(defaultInsets);
    actualIosFld.setHorizontalAlignment(SwingConstants.RIGHT);
    actualIosFld.setEditable(false);
    actualIosFld.setBounds(120, yPos, 105, 20);
    actualIosFld.setBackground(Color.white);
    actualIosFld.setFont(defaultFont);
    getContentPane().add(actualIosFld);

    excCovFld = new JTextField();
    excCovFld.setMargin(defaultInsets);
    excCovFld.setHorizontalAlignment(SwingConstants.RIGHT);
    excCovFld.setEditable(false);
    excCovFld.setBounds(235, yPos, 105, 20);
    excCovFld.setBackground(Color.white);
    excCovFld.setFont(defaultFont);
    getContentPane().add(excCovFld);

    yPos += 25;

    optLeafLbl = new JLabel();
    optLeafLbl.setText("Opt. Leaf:");
    optLeafLbl.setBounds(leftMargin, yPos, 80, 20);
    getContentPane().add(optLeafLbl);

    optIosFld = new JTextField();
    optIosFld.setMargin(defaultInsets);
    optIosFld.setHorizontalAlignment(SwingConstants.RIGHT);
    optIosFld.setEditable(false);
    optIosFld.setBounds(120, yPos, 105, 20);
    optIosFld.setBackground(Color.white);
    optIosFld.setFont(defaultFont);
    getContentPane().add(optIosFld);

    yPos += 25;

    lossLbl = new JLabel();
    lossLbl.setText("Loss:");
    lossLbl.setBounds(leftMargin, yPos, 80, 20);
    getContentPane().add(lossLbl);

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
    ohLbl.setText("Overhead:");
    ohLbl.setBounds(leftMargin, yPos, 70, 20);
    getContentPane().add(ohLbl);

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
	    PenaltyStatsDlg.this.setVisible(false);
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
// setKey -  updates display of currently selected leaf (incl. tree view)
//
// Description:
//	- extracts currently selected leaf number from dialog
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setKey()
{
    int keyNo = 0; // avg
    if (selectorGroup.getSelection().getActionCommand().equals("key")) {
	// we don't want the avg
	keyNo = currKey;
    }
    setKey(keyNo);
}


///////////////////////////////////////////////////////////////////////////////
// setKey -  updates display of query (incl. tree view)
//
// Description:
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setKey(int keyNo)
{
    boolean absValues = absGroup.getSelection().getActionCommand().equals("abs");
        // true if the user wants to see absolute I/O numbers, not deltas
    boolean weighted =
        weightedGroup.getSelection().getActionCommand().equals("weighted");
        // true if the user wants to see absolute I/O numbers, not deltas
    Libgist.getPenaltyStats(keyNo, weighted, penaltyStats);

    // load keyFld
    if (keyNo != 0) {
	// otherwise it's the total
	keyFld.setText(Integer.toString(keyNo));
	keyArea.setText(penaltyStats.key);
    }

    actualIosFld.setText(Float.toString(truncate(penaltyStats.actualAddIos, 3)));
    if (absValues) {
	excCovFld.setText(Float.toString(truncate(penaltyStats.actualExcCov, 3)));
    } else {
	excCovFld.setText(Float.toString(truncate(penaltyStats.excCovDelta, 3)));
    }
    optIosFld.setText(Float.toString(truncate(penaltyStats.optAddIos, 3)));
    clustLossFld.setText(Float.toString(truncate(penaltyStats.clusterLoss, 3)));
    excCovOhFld.setText(Float.toString(truncate(penaltyStats.excCovOh, 3)));
    excCovSuccessFld.setText(Float.toString(truncate(
        penaltyStats.excCovSuccess * 100.0f, 3)));

}

// init dialog for user interaction
public void
init(TreeView treeView)
{
    this.treeView = treeView;

    // set selected key
    numKeys = Libgist.getNumInsertions();
    currKey = 1;
    keyFld.setText(Integer.toString(currKey));

    setKey(0); // start with averages
}

}
