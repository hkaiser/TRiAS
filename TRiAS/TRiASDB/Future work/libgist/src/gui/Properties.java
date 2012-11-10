// Copyright (c) 1998, Regents of the University of California
// $Id: Properties.java,v 1.2 1999/06/27 00:17:37 marcel Exp $

import java.io.*;
import javax.swing.border.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


/*
 * Properties:
 *
 * Properties of an amdb session for a particular index. This class provides
 * an editing facility and serialization.
 */

class Properties
{

// clustering properties
static public int randClustRuns;
static public boolean randClustRetrOnly; // true: random clustering only for retrieved items
static public int clustNodeUtil; // target node utilization of clustering (in percent)

// tree view properties
static public int treeViewFontSize;
static public int treeViewMargin; // size of margin in box

static private JFrame parent = null;

// gui stuff
static private JDialog frame = null;
static private JTextField utilFld;
static private JTextField runsFld;
static private JRadioButton retrOnlyBtn;
static private JRadioButton allDataBtn;
static private ButtonGroup bGrp;
static private JTextField fontSizeFld;
static private JTextField marginFld;

static public void
setParent(JFrame p)
{
    parent = p;
}

// save properties
static public void
save(ObjectOutputStream s) throws IOException
{
    s.writeInt(randClustRuns);
    s.writeBoolean(randClustRetrOnly);
    s.writeInt(clustNodeUtil);
    s.writeInt(treeViewFontSize);
    s.writeInt(treeViewMargin);
}

// restore properties
static public void
restore(ObjectInputStream s) throws IOException
{
    randClustRuns = s.readInt();
    randClustRetrOnly = s.readBoolean();
    clustNodeUtil = s.readInt();
    treeViewFontSize = s.readInt();
    treeViewMargin = s.readInt();
}

// resets property value
static public void
reset()
{
    randClustRuns = 10;
    randClustRetrOnly = true;
    clustNodeUtil = 0;
    treeViewFontSize = 10;
    treeViewMargin = 1;
}

// copies the content of the edit fields back to the values
static private void
saveEdits()
{
    try {
        randClustRuns = Integer.parseInt(runsFld.getText());
    } catch(NumberFormatException e) {
        // values stays unchanged
    }
    randClustRetrOnly = bGrp.getSelection().getActionCommand().equals("retrieved"); 
    try {
	int oldUtil = clustNodeUtil;
        clustNodeUtil = Integer.parseInt(utilFld.getText());
	if (clustNodeUtil < 0 || clustNodeUtil > 100) clustNodeUtil = oldUtil;
    } catch(NumberFormatException e) {
        // values stays unchanged
    }
    try {
        treeViewFontSize = Integer.parseInt(fontSizeFld.getText());
    } catch(NumberFormatException e) {
        // values stays unchanged
    }
    try {
        treeViewMargin = Integer.parseInt(marginFld.getText());
    } catch(NumberFormatException e) {
        // values stays unchanged
    }
}

// copies the values to the edit fields
static private void
undoEdits()
{
    runsFld.setText(Integer.toString(randClustRuns));
    retrOnlyBtn.setSelected(randClustRetrOnly);
    allDataBtn.setSelected(!randClustRetrOnly);
    utilFld.setText(Integer.toString(clustNodeUtil));
    fontSizeFld.setText(Integer.toString(treeViewFontSize));
    marginFld.setText(Integer.toString(treeViewMargin));
}

static public void
edit()
{
    if (frame == null) {
	// create gui 
	JTabbedPane tabbedPane = new JTabbedPane();

	// clustering panel
	JPanel clusteringPanel = new JPanel(new BorderLayout());

	// random clustering panel: runs and data items used for computation
	String randClustConstraints[] = {
	    "runsLbl.left=form.left+10",
	    "runsLbl.top=form.top+10",
	    "runsFld.left=itemsLbl.right+10",
	    "runsFld.bottom=runsLbl.bottom",
	    "itemsLbl.left=runsLbl.left",
	    "itemsLbl.top=runsLbl.bottom+10",
	    "grpPanel.left=itemsLbl.left+10",
	    "grpPanel.bottom=itemsLbl.bottom"
	};
	//JPanel randClustPanel = new JPanel(new XmFormLayout(randClustConstraints));
	JPanel randClustPanel = new JPanel(new GridLayout(2, 2));
	randClustPanel.setBorder(new TitledBorder(new EtchedBorder(), "Random Clustering"));
	randClustPanel.add("runsLbl", new Label("Runs: "));
	runsFld = new JTextField(5);
	randClustPanel.add("runsFld", runsFld);
	randClustPanel.add("itemsLbl", new Label("Data Items: "));
	retrOnlyBtn = new JRadioButton("retrieved");
	retrOnlyBtn.setActionCommand("retrieved");
	allDataBtn = new JRadioButton("all");
	allDataBtn.setActionCommand("all");
	bGrp = new ButtonGroup();
	bGrp.add(retrOnlyBtn);
	bGrp.add(allDataBtn);
	String grpPanelConstraints[] = {
	    "roBtn.left=form.left",
	    "roBtn.top=form.top",
	    "adBtn.left=roBtn.right+10",
	    "adBtn.top=roBtn.top"
	    //,"adBtn.right=form.right"
	};
	Box grpBox = new Box(BoxLayout.X_AXIS);
	JPanel grpPanel = new JPanel(new FlowLayout());
	//JPanel grpPanel = new JPanel(new XmFormLayout(grpPanelConstraints));
	//grpPanel.add("roBtn", retrOnlyBtn);
	//grpPanel.add("adBtn", allDataBtn);
	grpBox.add(retrOnlyBtn);
	grpBox.add(allDataBtn);
	//randClustPanel.add("grpPanel", grpPanel);
	randClustPanel.add("grpBox", grpBox);
	clusteringPanel.add(BorderLayout.CENTER, randClustPanel);

	// general clustering parameters
	String genClustConstraints[] = {
	    "utilLbl.left=form.left+10",
	    "utilLbl.top=form.top+10",
	    "utilFld.left=utilLbl.right+10",
	    "utilFld.bottom=utilLbl.bottom"
	};
	//JPanel genClustPanel = new JPanel(new XmFormLayout(genClustConstraints));
	JPanel genClustPanel = new JPanel(new GridLayout(1, 2));
	genClustPanel.setBorder(new TitledBorder(new EtchedBorder(), "General"));
	genClustPanel.add("utilLbl", new JLabel("Node Utilization: "));
	utilFld = new JTextField(5);
	genClustPanel.add("utilFld", utilFld);
	clusteringPanel.add(BorderLayout.SOUTH, genClustPanel);

	tabbedPane.addTab("Clustering", clusteringPanel);

	// tree view panel
	String treeViewConstraints[] = {
	    "fontSizeLbl.left=form.left+10",
	    "fontSizeLbl.top=form.top+10",
	    "fontSizeFld.left=fontSizeLbl.right+10",
	    "fontSizeFld.bottom=fontSizeLbl.bottom",
	    "marginLbl.left=fontSizeLbl.left",
	    "marginLbl.top=fontSizeLbl.bottom+10",
	    "marginFld.bottom=marginLbl.bottom",
	    "marginFld.left=fontSizeLbl.right+10"
	};
	JPanel treeViewPanel = new JPanel(new XmFormLayout(treeViewConstraints));
	treeViewPanel.add("fontSizeLbl", new JLabel("Font Size: "));
	fontSizeFld = new JTextField(5);
	treeViewPanel.add("fontSizeFld", fontSizeFld);
	treeViewPanel.add("marginLbl", new JLabel("Margin: "));
	marginFld = new JTextField(5);
	treeViewPanel.add("marginFld", marginFld);
	tabbedPane.addTab("Tree View", treeViewPanel);

	// button panel
	JPanel btnPanel = new JPanel(new FlowLayout());
	JButton okButton = new JButton("OK");
	okButton.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		Properties.saveEdits();
		frame.setVisible(false);
	    }
	});
	btnPanel.add(okButton);

	JButton cancelButton = new JButton("Cancel");
	cancelButton.addActionListener(new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		Properties.undoEdits();
		frame.setVisible(false);
	    }
	});
	btnPanel.add(cancelButton);

	reset(); // set initial values
	undoEdits(); // copy to edit fields

	// dialog
	frame = new JDialog(parent, "amdb: Breakpoints", false);
	frame.getContentPane().add(tabbedPane);
	frame.getContentPane().add(btnPanel, BorderLayout.SOUTH);
	frame.pack();
    }
    frame.setVisible(true);
}


}

