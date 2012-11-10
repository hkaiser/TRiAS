// WkldStatsDlg.java
// Copyright (c) 1998, Regents of the University of California
// $Id: WkldStatsDlg.java,v 1.2 1999/06/27 00:17:35 marcel Exp $

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

/* 
 * WkldStatsDlg: 
 * Dialog box that displays amdb_wkldprofile and amdb_wkldstats data.
 */

class WkldStatsDlg extends JDialog
{

QueryStats queryStats; // amdb_profile::QueryStats of current query
AnalysisInfo analysisInfo;  // global parameters and state of analysis
TreeView treeView; // what displays the stats

ButtonGroup selectorGroup;
JRadioButton avgBtn;
JRadioButton queryBtn;
JTextField queryFld;
JButton plusBtn;
JButton minusBtn;
JScrollPane queryPane;
JTextArea queryArea;
JComboBox statsTypeBox;
ButtonGroup baseGroup;
JRadioButton minBtn;
JRadioButton optBtn;

// Parameters tab
JTextField numQueriesFld;
JTextField dataCovFld;
JTextField runsFld;
JRadioButton retrOnlyBtn;
JRadioButton allDataBtn;
JTextField utilFld;

// Leaves tab
JPanel leafPanel;
JLabel iosLbl, ohLbl;
JLabel minLbl, leafTotalLbl, optClustLbl, randClustLbl;
JLabel leafClLbl, leafUlLbl, leafElLbl;
JTextField minIoFld, minOhFld;
JTextField optClustIoFld, optClustOhFld;
JTextField randClustIoFld, randClustOhFld;
JTextField leafClOhFld, leafClIoFld;
JTextField leafUlIoFld, leafUlOhFld;
JTextField leafElIoFld, leafElOhFld;
JTextField leafTotalIoFld, leafTotalOhFld;
JLabel leafUtilLbl;
JTextField leafUtilFld;
JLabel itemsRetrLbl;
JTextField itemsRetrFld;


// internal/totals tab
JPanel internalPanel;
JLabel intLbl, totalsLbl;
JLabel clustLossLbl, utilLossLbl, excCovLossLbl, totalLbl;
JTextField intClFld, totalClFld;
JTextField intUlFld, totalUlFld;
JTextField intElFld, totalElFld;
JTextField intTotalFld, totalTotalFld;


public
WkldStatsDlg(JFrame parent)
{
    super(parent, "Workload Statistics", false);
    queryStats = new QueryStats();
    analysisInfo = new AnalysisInfo();
    Font defaultFont = new Font("Dialog", Font.PLAIN, 12);
    Insets defaultInsets = new Insets(0, 0, 0, 0);
    getContentPane().setLayout(null);

    // Totals/Query radio buttons
    avgBtn = new JRadioButton("Average:");
    avgBtn.setFont(defaultFont);
    avgBtn.setBounds(10, 10, 60, 20);
    avgBtn.setActionCommand("avg");
    avgBtn.setSelected(true);
    avgBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    setQuery(0);
	}
    });
    getContentPane().add(avgBtn);

    queryBtn = new JRadioButton("Query:");
    queryBtn.setFont(defaultFont);
    queryBtn.setBounds(75, 10, 60, 20);
    queryBtn.setActionCommand("query");
    queryBtn.setSelected(false);
    queryBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    try {
	        int queryNo = Integer.parseInt(queryFld.getText());
		if (!(queryNo >= 1 && queryNo <= analysisInfo.numQueries)) {
		    queryNo = 1;
		}
		setQuery(queryNo);
	    } catch (NumberFormatException e) {
		setQuery(1); // user fucked up -> reset to query 1
	    }
	}
    });
    getContentPane().add(queryBtn);

    selectorGroup = new ButtonGroup();
    selectorGroup.add(avgBtn);
    selectorGroup.add(queryBtn);

    plusBtn = new JButton("+");
    plusBtn.setFont(defaultFont);
    plusBtn.setBounds(230, 5, 45, 15);
    //plusBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    plusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    try {
	        int queryNo = Integer.parseInt(queryFld.getText());
		if (queryNo < analysisInfo.numQueries) {
		    setQuery(queryNo+1);
		}
	    } catch (NumberFormatException e) {
		// something went wrong, ignore this
	    }
	}
    });
    //selectorBox.add(plusBtn);
    getContentPane().add(plusBtn);

    minusBtn = new JButton("-");
    minusBtn.setFont(defaultFont);
    minusBtn.setBounds(230,20,45,15);
    //minusBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    minusBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent action) {
	    try {
	        int queryNo = Integer.parseInt(queryFld.getText());
		if (queryNo > 1) {
		    setQuery(queryNo-1);
		}
	    } catch (NumberFormatException e) {
		// something went wrong, ignore this
	    }
	}
    });
    //selectorBox.add(minusBtn);
    getContentPane().add(minusBtn);

    queryFld = new JTextField("1", 5);
    queryFld.setFont(defaultFont);
    queryFld.setBounds(140,10,84,20);
    //queryFld.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    queryFld.setHorizontalAlignment(JTextField.RIGHT);
    queryFld.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    try {
	        int queryNo = Integer.parseInt(queryFld.getText());
		if (!(queryNo >= 1 && queryNo <= analysisInfo.numQueries)) {
		    queryNo = 1;
		}
		setQuery(queryNo);
	    } catch (NumberFormatException e) {
		setQuery(1); // user fucked up -> reset to query 1
	    }
	}
    });
    //selectorBox.add(queryFld);
    //selectorBox.add(Box.createHorizontalGlue());
    getContentPane().add(queryFld);

    queryPane = new JScrollPane();
    queryPane.setOpaque(true);
    queryPane.setBounds(140,40,200,70);
    queryPane.setFont(defaultFont);
    getContentPane().add(queryPane);

    queryArea = new JTextArea();
    queryArea.setMargin(defaultInsets);
    queryArea.setBounds(0,0,200,70);
    queryArea.setFont(defaultFont);
    queryPane.getViewport().add(queryArea);

    //selectorBox.add(Box.createHorizontalGlue());
    //box.add(selectorBox);

    // display option panel
    //Box displayBox = new Box(BoxLayout.X_AXIS);
    //displayBox.setAlignmentX(Component.LEFT_ALIGNMENT);
    JLabel displayLbl = new JLabel("Display: ");
    displayLbl.setFont(defaultFont);
    displayLbl.setBounds(15, 125, 60, 15);
    getContentPane().add(displayLbl);

    statsTypeBox = new JComboBox();
    statsTypeBox.setFont(defaultFont);
    statsTypeBox.setBounds(75,125,175,20);
    //statsTypeBox.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    statsTypeBox.addItem("Traversals");
    statsTypeBox.addItem("Retrievals");
    statsTypeBox.addItem("Empty Subtrees");
    statsTypeBox.addItem("Cluster Loss");
    statsTypeBox.addItem("Cluster O/H");
    statsTypeBox.addItem("Utilization Loss");
    statsTypeBox.addItem("Utilization O/H");
    statsTypeBox.addItem("Excess Coverage Loss");
    statsTypeBox.addItem("Excess Coverage O/H");
    statsTypeBox.addItem("Pruned Exc. Cov. Loss");
    statsTypeBox.addItem("Pruned Exc. Cov. O/H");
    statsTypeBox.setEditable(false);
    statsTypeBox.setSelectedIndex(0);
    statsTypeBox.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different type of stats: update display
	    setQuery();
	}
    });
    //displayBox.add(statsTypeBox);
    getContentPane().add(statsTypeBox);

    JLabel baseLbl = new JLabel("Base of Metrics:");
    baseLbl.setFont(defaultFont);
    baseLbl.setBounds(15,160,100,20);
    //baseLbl.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    //displayBox.add(baseLbl);
    getContentPane().add(baseLbl);

    minBtn = new JRadioButton("Theoretical Minimum");
    minBtn.setFont(defaultFont);
    minBtn.setBounds(140,160,150,25);
    minBtn.setSelected(false);
    minBtn.setActionCommand("min");
    //minBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    minBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setQuery();
	}
    });
    getContentPane().add(minBtn);

    optBtn = new JRadioButton("Optimal Clustering");
    optBtn.setFont(defaultFont);
    optBtn.setBounds(140,180,145,25);
    optBtn.setSelected(true);
    optBtn.setActionCommand("opt");
    //optBtn.setAlignmentY(Component.BOTTOM_ALIGNMENT);
    optBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // switched to different base of stats: update display
	    setQuery();
	}
    });
    getContentPane().add(optBtn);

    baseGroup = new ButtonGroup();
    baseGroup.add(minBtn);
    baseGroup.add(optBtn);
    //displayBox.add(minBtn);
    //displayBox.add(optBtn);

    //displayBox.add(Box.createHorizontalGlue());
    //box.add(Box.createVerticalStrut(2));
    //box.add(displayBox);

    // tabbed display pane
    JTabbedPane tp = new JTabbedPane();
    tp.setFont(defaultFont);
    //tp.setBounds(15, 180, 325, 200);
    tp.setBounds(15, 215, 365, 310);
    getContentPane().add(tp);


    //////////////////////////////////////////////////////////////
    // parameters panel
    //////////////////////////////////////////////////////////////

    JPanel parametersPanel = new JPanel(null);

    // set up some position constants
    final int lblX = 15;
    final int lblHeight = 15;
    final int fldX = 145;
    final int fldWidth = 135;
    final int fldHeight = 20;

    JLabel numQueriesLbl = new JLabel("Number of Queries:");
    numQueriesLbl.setFont(defaultFont);
    numQueriesLbl.setBounds(lblX, 15, 110, lblHeight);
    parametersPanel.add(numQueriesLbl);
    numQueriesFld = new JTextField(5);
    numQueriesFld.setFont(defaultFont);
    numQueriesFld.setEditable(false);
    numQueriesFld.setMargin(defaultInsets);
    numQueriesFld.setBounds(fldX, 10, fldWidth, fldHeight);
    numQueriesFld.setHorizontalAlignment(SwingConstants.RIGHT);
    numQueriesFld.setBackground(Color.white);
    parametersPanel.add(numQueriesFld);

    JLabel dataCovLbl = new JLabel("Data Coverage:");
    dataCovLbl.setFont(defaultFont);
    dataCovLbl.setBounds(lblX, 45, 95, lblHeight);
    parametersPanel.add(dataCovLbl);
    dataCovFld = new JTextField(5);
    dataCovFld.setFont(defaultFont);
    dataCovFld.setEditable(false);
    dataCovFld.setMargin(defaultInsets);
    dataCovFld.setBounds(fldX, 40, fldWidth, fldHeight);
    dataCovFld.setHorizontalAlignment(SwingConstants.RIGHT);
    dataCovFld.setBackground(Color.white);
    parametersPanel.add(dataCovFld);

    JLabel runsLbl = new JLabel("Random Runs:");
    runsLbl.setFont(defaultFont);
    runsLbl.setBounds(lblX, 75, 85, lblHeight);
    parametersPanel.add(runsLbl);
    runsFld = new JTextField(5);
    runsFld.setFont(defaultFont);
    runsFld.setEditable(false);
    runsFld.setMargin(defaultInsets);
    runsFld.setBounds(fldX, 70, fldWidth, fldHeight);
    runsFld.setHorizontalAlignment(SwingConstants.RIGHT);
    runsFld.setBackground(Color.white);
    parametersPanel.add(runsFld);

    JLabel randDataLbl = new JLabel("Random Data:");
    randDataLbl.setFont(defaultFont);
    randDataLbl.setBounds(lblX, 110, 85, lblHeight);
    parametersPanel.add(randDataLbl);
    retrOnlyBtn = new JRadioButton("Retrieved");
    retrOnlyBtn.setFont(defaultFont);
    retrOnlyBtn.setBounds(fldX, 105, 80, 20);
    retrOnlyBtn.setActionCommand("retrieved");
    parametersPanel.add(retrOnlyBtn);
    allDataBtn = new JRadioButton("All");
    allDataBtn.setFont(defaultFont);
    allDataBtn.setBounds(fldX, 125, 80, 20);
    allDataBtn.setActionCommand("all");
    parametersPanel.add(allDataBtn);
    ButtonGroup randDataGroup = new ButtonGroup();
    randDataGroup.add(retrOnlyBtn);
    randDataGroup.add(allDataBtn);

    JLabel utilLbl = new JLabel("Target Utilization:");
    utilLbl.setFont(defaultFont);
    utilLbl.setBounds(lblX, 160, 120, lblHeight);
    parametersPanel.add(utilLbl);
    utilFld = new JTextField(5);
    utilFld.setFont(defaultFont);
    utilFld.setEditable(false);
    utilFld.setMargin(defaultInsets);
    utilFld.setBounds(fldX, 155, fldWidth, fldHeight);
    utilFld.setHorizontalAlignment(SwingConstants.RIGHT);
    utilFld.setBackground(Color.white);
    parametersPanel.add(utilFld);

    tp.addTab("Parameters", parametersPanel);


    //////////////////////////////////////////////////////////////
    // leaf-level panel
    //////////////////////////////////////////////////////////////

    leafPanel = new JPanel(null);
    leafPanel.setFont(defaultFont);
    getContentPane().add(leafPanel);

    iosLbl = new JLabel();
    iosLbl.setText("I/Os");
    iosLbl.setBounds(160,75,32,20);
    leafPanel.add(iosLbl);

    ohLbl = new JLabel();
    ohLbl.setText("Overhead");
    ohLbl.setBounds(255,75,60,20);
    leafPanel.add(ohLbl);

    minIoFld = new JTextField();
    minIoFld.setMargin(defaultInsets);
    minIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    minIoFld.setEditable(false);
    minIoFld.setBounds(120,100,105,20);
    minIoFld.setBackground(Color.white);
    minIoFld.setFont(defaultFont);
    leafPanel.add(minIoFld);

    minOhFld = new JTextField();
    minOhFld.setMargin(defaultInsets);
    minOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    minOhFld.setEditable(false);
    minOhFld.setBounds(235,100,105,20);
    minOhFld.setBackground(Color.white);
    minOhFld.setFont(defaultFont);
    leafPanel.add(minOhFld);

    optClustOhFld = new JTextField();
    optClustOhFld.setMargin(defaultInsets);
    optClustOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    optClustOhFld.setEditable(false);
    optClustOhFld.setBounds(235,125,105,20);
    optClustOhFld.setBackground(Color.white);
    optClustOhFld.setFont(defaultFont);
    leafPanel.add(optClustOhFld);

    optClustIoFld = new JTextField();
    optClustIoFld.setMargin(defaultInsets);
    optClustIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    optClustIoFld.setEditable(false);
    optClustIoFld.setBounds(120,125,105,20);
    optClustIoFld.setBackground(Color.white);
    optClustIoFld.setFont(defaultFont);
    leafPanel.add(optClustIoFld);

    randClustIoFld = new JTextField();
    randClustIoFld.setMargin(defaultInsets);
    randClustIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    randClustIoFld.setEditable(false);
    randClustIoFld.setBounds(120,150,105,20);
    randClustIoFld.setBackground(Color.white);
    randClustIoFld.setFont(defaultFont);
    leafPanel.add(randClustIoFld);

    randClustOhFld = new JTextField();
    randClustOhFld.setMargin(defaultInsets);
    randClustOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    randClustOhFld.setEditable(false);
    randClustOhFld.setBounds(235,150,105,20);
    randClustOhFld.setBackground(Color.white);
    randClustOhFld.setFont(defaultFont);
    leafPanel.add(randClustOhFld);

    leafClOhFld = new JTextField();
    leafClOhFld.setMargin(defaultInsets);
    leafClOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafClOhFld.setEditable(false);
    leafClOhFld.setBounds(235,175,105,20);
    leafClOhFld.setBackground(Color.white);
    leafClOhFld.setFont(defaultFont);
    leafPanel.add(leafClOhFld);

    leafClIoFld = new JTextField();
    leafClIoFld.setMargin(defaultInsets);
    leafClIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafClIoFld.setEditable(false);
    leafClIoFld.setBounds(120,175,105,20);
    leafClIoFld.setBackground(Color.white);
    leafClIoFld.setFont(defaultFont);
    leafPanel.add(leafClIoFld);

    leafUlIoFld = new JTextField();
    leafUlIoFld.setMargin(defaultInsets);
    leafUlIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafUlIoFld.setEditable(false);
    leafUlIoFld.setBounds(120,200,105,20);
    leafUlIoFld.setBackground(Color.white);
    leafUlIoFld.setFont(defaultFont);
    leafPanel.add(leafUlIoFld);

    leafUlOhFld = new JTextField();
    leafUlOhFld.setMargin(defaultInsets);
    leafUlOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafUlOhFld.setEditable(false);
    leafUlOhFld.setBounds(235,200,105,20);
    leafUlOhFld.setBackground(Color.white);
    leafUlOhFld.setFont(defaultFont);
    leafPanel.add(leafUlOhFld);

    leafElIoFld = new JTextField();
    leafElIoFld.setMargin(defaultInsets);
    leafElIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafElIoFld.setEditable(false);
    leafElIoFld.setBounds(120,225,105,20);
    leafElIoFld.setBackground(Color.white);
    leafElIoFld.setFont(defaultFont);
    leafPanel.add(leafElIoFld);

    leafElOhFld = new JTextField();
    leafElOhFld.setMargin(defaultInsets);
    leafElOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafElOhFld.setEditable(false);
    leafElOhFld.setBounds(235,225,105,20);
    leafElOhFld.setBackground(Color.white);
    leafElOhFld.setFont(defaultFont);
    leafPanel.add(leafElOhFld);

    leafTotalIoFld = new JTextField();
    leafTotalIoFld.setMargin(defaultInsets);
    leafTotalIoFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafTotalIoFld.setEditable(false);
    leafTotalIoFld.setBounds(120,250,105,20);
    leafTotalIoFld.setBackground(Color.white);
    leafTotalIoFld.setFont(defaultFont);
    leafPanel.add(leafTotalIoFld);

    leafTotalOhFld = new JTextField();
    leafTotalOhFld.setMargin(defaultInsets);
    leafTotalOhFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafTotalOhFld.setEditable(false);
    leafTotalOhFld.setBounds(235,250,105,20);
    leafTotalOhFld.setBackground(Color.white);
    leafTotalOhFld.setFont(defaultFont);
    leafPanel.add(leafTotalOhFld);

    minLbl = new JLabel();
    minLbl.setText("Theor. Min.:");
    minLbl.setBounds(15,100,100,20);
    leafPanel.add(minLbl);

    leafTotalLbl = new JLabel();
    leafTotalLbl.setText("Actual Clust.:");
    leafTotalLbl.setBounds(15,250,80,20);
    leafPanel.add(leafTotalLbl);

    optClustLbl = new JLabel();
    optClustLbl.setText("Opt. Clust.:");
    optClustLbl.setBounds(15,125,80,20);
    leafPanel.add(optClustLbl);

    randClustLbl = new JLabel();
    randClustLbl.setText("Random Clust.:");
    randClustLbl.setBounds(15,150,95,20);
    leafPanel.add(randClustLbl);

    leafClLbl = new JLabel();
    leafClLbl.setText("Clust. Loss:");
    leafClLbl.setBounds(15,175,80,20);
    leafPanel.add(leafClLbl);

    leafUlLbl = new JLabel();
    leafUlLbl.setText("Util. Loss:");
    leafUlLbl.setBounds(15,200,70,20);
    leafPanel.add(leafUlLbl);

    leafElLbl = new JLabel();
    leafElLbl.setText("Exc. Cov. Loss:");
    leafElLbl.setBounds(15,225,100,20);
    leafPanel.add(leafElLbl);

    leafUtilFld = new JTextField();
    leafUtilFld.setMargin(defaultInsets);
    leafUtilFld.setHorizontalAlignment(SwingConstants.RIGHT);
    leafUtilFld.setEditable(false);
    leafUtilFld.setBounds(120,35,105,20);
    leafUtilFld.setBackground(Color.white);
    leafUtilFld.setFont(defaultFont);
    leafPanel.add(leafUtilFld);

    itemsRetrFld = new JTextField();
    itemsRetrFld.setMargin(defaultInsets);
    itemsRetrFld.setHorizontalAlignment(SwingConstants.RIGHT);
    itemsRetrFld.setEditable(false);
    itemsRetrFld.setBounds(120,10,105,20);
    itemsRetrFld.setBackground(Color.white);
    itemsRetrFld.setFont(defaultFont);
    leafPanel.add(itemsRetrFld);
    
    leafUtilLbl = new JLabel();
    leafUtilLbl.setText("Avg. Util.:");
    leafUtilLbl.setBounds(15,35,95,20);
    leafPanel.add(leafUtilLbl);
    
    itemsRetrLbl = new JLabel();
    itemsRetrLbl.setText("Items Retrieved:");
    itemsRetrLbl.setBounds(15,10,105,20);
    leafPanel.add(itemsRetrLbl);
    
    tp.addTab("Leaves", leafPanel);

    //////////////////////////////////////////////////////////////
    // internal/totals panel
    //////////////////////////////////////////////////////////////

    internalPanel = new JPanel(null);
    internalPanel.setFont(new Font("Dialog", Font.PLAIN, 12));
    getContentPane().add(internalPanel);

    intLbl = new JLabel();
    intLbl.setText("Internal");
    intLbl.setHorizontalAlignment(SwingConstants.CENTER);
    intLbl.setBounds(120,10,105,20);
    internalPanel.add(intLbl);

    totalsLbl = new JLabel();
    totalsLbl.setText("All");
    totalsLbl.setHorizontalAlignment(SwingConstants.CENTER);
    totalsLbl.setBounds(235,10,105,20);
    internalPanel.add(totalsLbl);

    totalClFld = new JTextField();
    totalClFld.setMargin(defaultInsets);
    totalClFld.setHorizontalAlignment(SwingConstants.RIGHT);
    totalClFld.setEditable(false);
    totalClFld.setBounds(235,35,105,20);
    totalClFld.setBackground(Color.white);
    totalClFld.setFont(defaultFont);
    internalPanel.add(totalClFld);

    totalUlFld = new JTextField();
    totalUlFld.setMargin(defaultInsets);
    totalUlFld.setHorizontalAlignment(SwingConstants.RIGHT);
    totalUlFld.setEditable(false);
    totalUlFld.setBounds(235,60,105,20);
    totalUlFld.setBackground(Color.white);
    totalUlFld.setFont(defaultFont);
    internalPanel.add(totalUlFld);

    intClFld = new JTextField();
    intClFld.setMargin(defaultInsets);
    intClFld.setHorizontalAlignment(SwingConstants.RIGHT);
    intClFld.setEditable(false);
    intClFld.setBounds(120,35,105,20);
    intClFld.setBackground(Color.white);
    intClFld.setFont(defaultFont);
    internalPanel.add(intClFld);

    intUlFld = new JTextField();
    intUlFld.setMargin(defaultInsets);
    intUlFld.setHorizontalAlignment(SwingConstants.RIGHT);
    intUlFld.setEditable(false);
    intUlFld.setBounds(120,60,105,20);
    intUlFld.setBackground(Color.white);
    intUlFld.setFont(defaultFont);
    internalPanel.add(intUlFld);

    intElFld = new JTextField();
    intElFld.setMargin(defaultInsets);
    intElFld.setHorizontalAlignment(SwingConstants.RIGHT);
    intElFld.setEditable(false);
    intElFld.setBounds(120,85,105,20);
    intElFld.setBackground(Color.white);
    intElFld.setFont(defaultFont);
    internalPanel.add(intElFld);

    totalElFld = new JTextField();
    totalElFld.setMargin(defaultInsets);
    totalElFld.setHorizontalAlignment(SwingConstants.RIGHT);
    totalElFld.setEditable(false);
    totalElFld.setBounds(235,85,105,20);
    totalElFld.setBackground(Color.white);
    totalElFld.setFont(defaultFont);
    internalPanel.add(totalElFld);

    totalTotalFld = new JTextField();
    totalTotalFld.setMargin(defaultInsets);
    totalTotalFld.setHorizontalAlignment(SwingConstants.RIGHT);
    totalTotalFld.setEditable(false);
    totalTotalFld.setBounds(235,110,105,20);
    totalTotalFld.setBackground(Color.white);
    totalTotalFld.setFont(defaultFont);
    internalPanel.add(totalTotalFld);

    intTotalFld = new JTextField();
    intTotalFld.setMargin(defaultInsets);
    intTotalFld.setHorizontalAlignment(SwingConstants.RIGHT);
    intTotalFld.setEditable(false);
    intTotalFld.setBounds(120,110,105,20);
    intTotalFld.setBackground(Color.white);
    intTotalFld.setFont(defaultFont);
    internalPanel.add(intTotalFld);

    totalLbl = new JLabel();
    totalLbl.setText("Total:");
    totalLbl.setBounds(15,110,70,20);
    internalPanel.add(totalLbl);

    clustLossLbl = new JLabel();
    clustLossLbl.setText("Clust. Loss:");
    clustLossLbl.setBounds(15,35,80,20);
    internalPanel.add(clustLossLbl);

    utilLossLbl = new JLabel();
    utilLossLbl.setText("Util. Loss:");
    utilLossLbl.setBounds(15,60,70,20);
    internalPanel.add(utilLossLbl);

    excCovLossLbl = new JLabel();
    excCovLossLbl.setText("Exc. Cov. Loss:");
    excCovLossLbl.setBounds(15,85,100,20);
    internalPanel.add(excCovLossLbl);

    tp.addTab("Internal/Totals", internalPanel);

    // quit button
    JButton quitBtn = new JButton("Quit");
    quitBtn.setFont(defaultFont);
    quitBtn.setBounds(125, 540, 80, 30);
    quitBtn.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    WkldStatsDlg.this.setVisible(false);
	}
    });
    getContentPane().add(quitBtn);

    setBounds(0, 0, 400, 620);
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
// setQuery -  updates display of currently selected query (incl. tree view)
//
// Description:
//	- extracts currently selected query number from dialog
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setQuery()
{
    int queryNo = 0; // totals
    if (selectorGroup.getSelection().getActionCommand().equals("query")) {
	// we don't want the totals
	try {
	    queryNo = Integer.parseInt(queryFld.getText());
	} catch (NumberFormatException e) {
	    DbgOutput.println(2, "setQuery() w/o a queryno!");
	    // can't be 
	}
    }
    setQuery(queryNo);
}


///////////////////////////////////////////////////////////////////////////////
// setQuery -  updates display of query (incl. tree view)
//
// Description:
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

private void
setQuery(int queryNo)
{
    Libgist.getQueryStats(queryNo, queryStats);
    boolean minStats = baseGroup.getSelection().getActionCommand().equals("min");
        // true if the user wants to see metrics w.r.t. theoretical minimum;
	// otherwise w.r.t. to the optimal clustering

    // load queryFld and queryArea
    if (queryNo != 0) {
	// otherwise it's the total
	queryFld.setText(Integer.toString(queryNo));
	queryArea.setText(queryStats.qual.toString());
    } else {
	queryArea.setText("");
    }

    // load leaf-level panel
    itemsRetrFld.setText(Integer.toString(queryStats.resultSetSize));
    leafUtilFld.setText(Float.toString(truncate(queryStats.avgUtil * 100, 3)));
    minIoFld.setText(Integer.toString(queryStats.minIos));
    minOhFld.setText("N/A");
    optClustIoFld.setText(Integer.toString(queryStats.optimalIos));
    optClustOhFld.setText(Float.toString(truncate(queryStats.optimalOh, 3)));
    randClustIoFld.setText(Float.toString(truncate(queryStats.randomIos, 2))
        + " (" + Float.toString(truncate(queryStats.randomStdDev, 2)) + ")");
    if (minStats) {
	randClustOhFld.setText(Float.toString(truncate(queryStats.minRandomOh, 3)));
    } else {
	randClustOhFld.setText(Float.toString(truncate(queryStats.optRandomOh, 3)));
    }
    if (minStats) {
	leafClIoFld.setText(Float.toString(truncate(queryStats.minClusterLoss, 3)));
    } else {
	leafClIoFld.setText(Float.toString(truncate(queryStats.optClusterLoss, 3)));
    }
    if (minStats) {
	leafClOhFld.setText(Float.toString(truncate(queryStats.minClusterOh, 3)));
    } else {
	leafClOhFld.setText(Float.toString(truncate(queryStats.optClusterOh, 3)));
    }
    leafUlIoFld.setText(Float.toString(truncate(queryStats.leafUtilLoss, 3)));
    leafUlOhFld.setText(Float.toString(truncate(queryStats.utilOh, 3)));
    leafElIoFld.setText(Float.toString(truncate(queryStats.leafExcCovLoss, 3)));
    leafElOhFld.setText(Float.toString(truncate(queryStats.excCovOh, 3)));
    leafTotalIoFld.setText(Integer.toString(queryStats.totalLeafIos));
    if (minStats) {
	leafTotalOhFld.setText(Float.toString(truncate(
	    ((float) queryStats.totalLeafIos / (float) queryStats.minIos), 3)));
    } else {
	leafTotalOhFld.setText(Float.toString(truncate(
	    ((float) queryStats.totalLeafIos / (float) queryStats.optimalIos), 3)));
    }


    // load internal/totals panel
    intClFld.setText("N/A");
    totalClFld.setText(leafClIoFld.getText());
    intUlFld.setText(Float.toString(queryStats.internalUtilLoss));
    totalUlFld.setText(Float.toString(queryStats.internalUtilLoss +
        queryStats.leafUtilLoss));
    intElFld.setText(Float.toString(queryStats.internalExcCovLoss));
    totalElFld.setText(Float.toString(queryStats.internalExcCovLoss +
        queryStats.leafExcCovLoss));
    intTotalFld.setText(Integer.toString(queryStats.totalInternalIos));
    totalTotalFld.setText(Integer.toString(queryStats.totalLeafIos +
        queryStats.totalInternalIos));

    // display stats in treeview
    Libgist.getWkldNodeStats(statsTypeBox.getSelectedIndex(), queryNo, minStats);
    treeView.showStats(Libgist.nodeCnt, Libgist.displayStats,
        (String) statsTypeBox.getSelectedItem());
}

// init dialog for user interaction:
// set querySlider range to # of queries
public void
init(TreeView treeView)
{
    this.treeView = treeView;
    // load workload data
    Libgist.getAnalysisInfo(analysisInfo);
    numQueriesFld.setText(Integer.toString(analysisInfo.numQueries));
    float percCoverage = ((float) analysisInfo.numRetrieved) /
        ((float) analysisInfo.numItems);
    dataCovFld.setText(Integer.toString(analysisInfo.numRetrieved) + "/" +
        Integer.toString(analysisInfo.numItems) + " (" +
	Integer.toString((int) (percCoverage * 100.0)) + "%)");
    runsFld.setText(Integer.toString(analysisInfo.randomRuns));
    retrOnlyBtn.setSelected(true);
    allDataBtn.setSelected(false);
    utilFld.setText(Float.toString(analysisInfo.targetUtil));

    setQuery(0);
}

}
