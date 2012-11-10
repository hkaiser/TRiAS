// MainWindow.java
// Copyright (c) 1998, Regents of the University of California
// $Id: MainWindow.java,v 1.3 1999/12/14 06:07:34 marcel Exp $

//import com.sun.java.swing.*;
import javax.swing.*;
import javax.swing.event.*;
//import com.sun.java.swing.event.*;
//import com.sun.java.swing.preview.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;
import java.lang.*;
import java.io.*;
import java.util.*;

/*
 * MainWindow - main amdb GUI window
 *
 * Contains menus, console window, etc.
 */

public class MainWindow extends JFrame //implements WindowListener
{

// GUI states w.r.t. status of menu items
static final int INITSTATE = 0;
static final int IDXOPENSTATE = 1;
static final int DEBUGSTATE = 2;
static final int ANLOPENSTATE = 3;
static final int STOPSTATE = 4;
// various stuff
JDesktopPane desktop;
public ConsoleWindow consoleFrame; // our text output window
boolean scriptWasCancelled; // set by 'Stop' button, read by execution thread
int guiState; // one of the above; determines which menu items are enabled
String idxName; // filename of currently open index
OpThread opThread; // thread to execute libgist operations (debugging fcts in separate thread)
Workload wkld; // profile we're currently working with
WkldStatsDlg wkldStatsDlg;
SplitStatsDlg splitStatsDlg;
PenaltyStatsDlg penaltyStatsDlg;
TreeView treeView; // internal frame subclass for display of tree structure
boolean isOpen; // true if some index is opened
LibgistCommand cmd; // passed to opThread for execution
boolean inWkld = false; // true if opThread is executing an analysis workload for us
StringBuffer echoBuffer = new StringBuffer();
public ResultProcessor echoResults = 
    new ResultProcessor() {
	public void processItem(String key, String data) {
	    if (!inWkld && showResultsItem.getState()) {
		consoleFrame.echoTuple(key + ": " + data);
	    }
	}
    };

// global GUI state, needed for enabling/disabling them
JMenuBar menuBar;
JMenu fileMenu, debugMenu, opsMenu, analysisMenu, windowsMenu, treeStatsMenu;
JMenuItem newItem, openItem, closeItem, flushItem, exitItem, settingsItem, optionsItem;
JMenuItem dumpItem;
JMenuItem insertItem, deleteItem, searchItem, executeItem;
JMenuItem breakpointsItem;
JCheckBoxMenuItem traceAllItem;
AbstractAction stepAction, nextAction, contAction, stopAction, cancelAction;
JMenuItem newAnalysisItem, openAnalysisItem, completeAnalysisItem, 
    wkldStatsItem, splitStatsItem, penaltyStatsItem;
JCheckBoxMenuItem showCmdsItem, showResultsItem, showTraceItem;
JCheckBoxMenuItem checkPenaltyItem;
JMenuItem utilItem, slotCntItem, predSzItem;
JMenuItem tileItem;

// analysis info
AnalysisInfo analysisInfo;

public void
windowActivated(WindowEvent e)
{
}

public void
windowClosed(WindowEvent e)
{
}

public void
windowClosing(WindowEvent e)
{
    try {
	Libgist.close();
    } catch (LibgistException exc) {
	// can't do very much at this point
	System.err.println("Could not close " + exc);
    }
    opThread.stopNow();
    System.exit(0);    
}

public void
windowDeactivated(WindowEvent e)
{
}

public void
windowDeiconified(WindowEvent e)
{
}

public void
windowIconified(WindowEvent e)
{
}

public void
windowOpened(WindowEvent e)
{
}

public TreeView
treeView()
{
    return treeView;
}

// returns the old state and applies the new state
// 'isScript' and 'enableCancel' are only relevant for debug mode
public int
setGuiState(int state)
{
    return setGuiState(state, false, false);
}

public int
setGuiState(int state, boolean isScript, boolean enableCancel)
{
    DbgOutput.println(2, "state: " + state);
    int oldState = guiState;
    guiState = state;
    switch (guiState) {
    case INITSTATE:
        enableInit();
	break;
    case IDXOPENSTATE:
        enableIndexOpened();
	break;
    case DEBUGSTATE:
        enableDebug(isScript, enableCancel);
	break;
    case ANLOPENSTATE:
        enableAnalysis();
	break;
    }
    return oldState;
}

// enable all menu items/menus for operations that require 
// a Gist to work on, excluding the debugging functions
private void
enableIndexOpened()
{
    DbgOutput.println(1, "enableIndexOpened()");
    setAllEnabled(true);
    // debugging operations only during operations
    stepAction.setEnabled(false);
    stopAction.setEnabled(false);
    cancelAction.setEnabled(false);
    nextAction.setEnabled(false);
    contAction.setEnabled(false);

    // no profile opened
    completeAnalysisItem.setEnabled(false);
    wkldStatsItem.setEnabled(false);
    splitStatsItem.setEnabled(false);
    penaltyStatsItem.setEnabled(false);
}

// enable startup menu items that don't require an index or profile to work with
private void
enableInit()
{
    setAllEnabled(false);

    // we can create and open indices
    fileMenu.setEnabled(true);
    newItem.setEnabled(true);
    openItem.setEnabled(true);

    // we can execute scripts
    opsMenu.setEnabled(true);
    executeItem.setEnabled(true);

    // we can open profile
    analysisMenu.setEnabled(true);
    openAnalysisItem.setEnabled(true);
}

// enable/disable all menu items/actions
private void
setAllEnabled(boolean enabled)
{
    DbgOutput.println(2, "enabled: " + enabled);
    fileMenu.setEnabled(enabled);
    newItem.setEnabled(enabled);
    openItem.setEnabled(enabled);
    closeItem.setEnabled(enabled);
    //dumpItem.setEnabled(enabled);
    flushItem.setEnabled(enabled);
    optionsItem.setEnabled(enabled);
    settingsItem.setEnabled(enabled);

    debugMenu.setEnabled(enabled);
    stepAction.setEnabled(enabled);
    stopAction.setEnabled(enabled);
    cancelAction.setEnabled(enabled);
    nextAction.setEnabled(enabled);
    contAction.setEnabled(enabled);
    breakpointsItem.setEnabled(enabled);

    opsMenu.setEnabled(enabled);
    insertItem.setEnabled(enabled);
    deleteItem.setEnabled(enabled);
    searchItem.setEnabled(enabled);
    executeItem.setEnabled(enabled);

    treeStatsMenu.setEnabled(enabled);
    utilItem.setEnabled(enabled);
    predSzItem.setEnabled(enabled);
    slotCntItem.setEnabled(enabled);

    analysisMenu.setEnabled(enabled);
    newAnalysisItem.setEnabled(enabled);
    openAnalysisItem.setEnabled(enabled);
    completeAnalysisItem.setEnabled(enabled);
    wkldStatsItem.setEnabled(enabled);
    splitStatsItem.setEnabled(enabled);
    penaltyStatsItem.setEnabled(enabled);

    // these are never disabled
    windowsMenu.setEnabled(true);
    showCmdsItem.setEnabled(true);
    showResultsItem.setEnabled(true);
    showTraceItem.setEnabled(true);
    tileItem.setEnabled(true);
}

// set all menu items related to debugging enabled, all else disabled;
// for insert, remove and fetch: continue, step
// additionally for scripts: next and sometimes cancel
private void
enableDebug(boolean isScript, boolean enableCancel)
{
    setAllEnabled(false);
    debugMenu.setEnabled(true);
    stepAction.setEnabled(true);
    cancelAction.setEnabled(enableCancel);
    nextAction.setEnabled(isScript);
    contAction.setEnabled(true);
    breakpointsItem.setEnabled(true);
    treeStatsMenu.setEnabled(true);
    utilItem.setEnabled(true);
    predSzItem.setEnabled(true);
    slotCntItem.setEnabled(true);
}

// set all menu items except for "stop" to disabled
private void
enableStop()
{
    setAllEnabled(false);
    debugMenu.setEnabled(true);
    stopAction.setEnabled(true);
}


///////////////////////////////////////////////////////////////////////////////
// enableAnalysis - enable menu items for analysis
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

private void
enableAnalysis()
{
    setAllEnabled(false);
    analysisMenu.setEnabled(true);

    // get info on state of analysis
    String scriptFile;
    Libgist.getAnalysisInfo(analysisInfo);

    // newAnalysisItem not enabled: can't create new profile, we just closed the index
    newAnalysisItem.setEnabled(false);
    openAnalysisItem.setEnabled(true);
    completeAnalysisItem.setEnabled(true);

    wkldStatsItem.setEnabled(analysisInfo.actualHasWkldStats);
    splitStatsItem.setEnabled(analysisInfo.actualHasSplitStats);
    penaltyStatsItem.setEnabled(analysisInfo.actualHasPenaltyStats);

    // general tree statistics are okay
    treeStatsMenu.setEnabled(true);
    utilItem.setEnabled(true);
    predSzItem.setEnabled(true);
    slotCntItem.setEnabled(true);

    // can always select another index or exit
    fileMenu.setEnabled(true);
    newItem.setEnabled(true);
    openItem.setEnabled(true);
    exitItem.setEnabled(true);
}

// saves the current configuration (breakpoints, window sizes and positions...)
private void
saveConfig()
{
    try {
	ObjectOutputStream out = new ObjectOutputStream(
	    new FileOutputStream(idxName + ".config"));
	Breakpoints.save(out);
	Properties.save(out);
	out.close();
    } catch (IOException exc) {
	consoleFrame.echoInfo("Could not save settings: " + exc);
    }
}

// reads the configuration (breakpoints, window sizes and positions...) for the current index
private void
restoreConfig()
{
    Breakpoints.reset();
    Properties.reset();
    try {
	ObjectInputStream in = new ObjectInputStream(
	    new FileInputStream(idxName + ".config"));
	Breakpoints.restore(in);
	Properties.restore(in);
	in.close();
    } catch (IOException exc) {
	// something went wrong - there probably was no .config file
	// ignore it
    }
}

// resets the configuration (breakpoints, window sizes and positions...)
private void
resetConfig()
{
    Breakpoints.reset();
    Properties.reset();
}


///////////////////////////////////////////////////////////////////////////////
// resetState - clean up when switching GUI state 
//
// Description:
//	- goes to INITSTATE and makes all open dialogs invisible
///////////////////////////////////////////////////////////////////////////////

private void
resetState()
{
    if (treeView != null) {
	treeView.dispose();
	treeView = null;
    }
    isOpen = false;
    idxName = null;
    setGuiState(INITSTATE);
    //setTitle("amdb");
    setTree("");
    wkldStatsDlg.setVisible(false);
    splitStatsDlg.setVisible(false);
    penaltyStatsDlg.setVisible(false);
}

// tiles treeView, globalView and consoleFrame
public void
tile()
{
    if (treeView != null) treeView.tile();
    consoleFrame.tile();
}


///////////////////////////////////////////////////////////////////////////////
// echoCmd - display command in console
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public void
echoCmd(LibgistCommand cmd)
{
    if (!showCmdsItem.getState()) {
        return;
    }

    echoBuffer.setLength(0); // reset
    switch (cmd.cmdType) {

    case LibgistCommand.INSERT:
	echoBuffer.append("insert \"").append(cmd.key);
	echoBuffer.append("\" \"").append(cmd.data).append("\"");
	break;
    
    case LibgistCommand.REMOVE:
	echoBuffer.append("delete \"").append(cmd.qual);
	echoBuffer.append("\"");
	break;
    
    case LibgistCommand.FETCH:
	echoBuffer.append("select ");
	 if (cmd.fetchLimit > 0) {
	     echoBuffer.append(cmd.fetchLimit).append(" ");
	 }
	 echoBuffer.append("\"").append(cmd.qual).append("\"");
	 break;
    
    case LibgistCommand.CREATE:
        echoBuffer.append("create ").append(cmd.indexName);
	echoBuffer.append(" ").append(cmd.extension);
	break;
    
    case LibgistCommand.OPEN:
        echoBuffer.append("open ").append(cmd.indexName);
	break;
    
    case LibgistCommand.CLOSE:
        echoBuffer.append("close");
	break;
    
    case LibgistCommand.FLUSH:
        echoBuffer.append("flush");
	break;
    
    case LibgistCommand.OPENANL:
        echoBuffer.append("openanl ").append(cmd.analysisFile.getPath());
	break;
    
    case LibgistCommand.CLOSEANL:
        echoBuffer.append("closeanl");
	break;
    
    case LibgistCommand.CREATEANL:
        echoBuffer.append("createanl");
	break;

    case LibgistCommand.SCRIPT:
        echoBuffer.append("executing script...");
	break;

    default: 
        // something wrong here
    }
    consoleFrame.echoCmd(echoBuffer.toString());
}


///////////////////////////////////////////////////////////////////////////////
// updateGuiState - update state of GUI after executed operation
//
// Description:
//	- if create/open/openanl was unsuccessful, go to INITSTATE
//	- insert, delete and search don't change the state, so we 
//	  restore the old state
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public void
updateGuiState(int priorState, LibgistCommand cmd, boolean success)
{
    switch(cmd.cmdType) {
    case LibgistCommand.CREATE:
    case LibgistCommand.OPEN:
	resetState();
	if (!success) return; // done
	setGuiState(IDXOPENSTATE);
	isOpen = true;
	idxName = cmd.indexName.toString();
	if (cmd.cmdType == LibgistCommand.CREATE) {
	    resetConfig();
	} else {
	    restoreConfig();
	}
	//setTitle("amdb: " + filename);
	setTree(idxName);
	try {
	    treeView = new TreeView(desktop); // creates a display of the opened index
	    desktop.add(treeView, JLayeredPane.PALETTE_LAYER);
	} catch (LibgistException e) {
	    // what to do now?
	    consoleFrame.echoInfo("new TreeView() failed");
	}
	break;

    case LibgistCommand.CLOSE:
	saveConfig();
	resetState();
	break;

    case LibgistCommand.OPENANL:
	resetState();
	if (!success) return; // done
	// enable menu items and open tree view
	setGuiState(ANLOPENSTATE);
	//setTitle("amdb: " + filename);
	setTree(idxName);
	try {
	    treeView = new TreeView(desktop); // creates a display of the opened index
	    desktop.add(treeView, JLayeredPane.PALETTE_LAYER);
	} catch (LibgistException e) {
	    // what to do now?
	    consoleFrame.echoInfo("new TreeView() failed");
	}

	// get ready to display dialogs
	if (analysisInfo.actualHasWkldStats) {
	    wkldStatsDlg.init(treeView);
	}
	if (analysisInfo.actualHasSplitStats) {
	    splitStatsDlg.init(treeView);
	}
	if (analysisInfo.actualHasPenaltyStats) {
	    penaltyStatsDlg.init(treeView);
	}
	break;

    case LibgistCommand.CLOSEANL:
	treeView.dispose();
	treeView = null;
	setGuiState(INITSTATE);
	setTree("");
        break;

    // if these didn't work, we don't care
    case LibgistCommand.INSERT:
    case LibgistCommand.REMOVE:
    case LibgistCommand.FETCH:
    case LibgistCommand.FLUSH:
    case LibgistCommand.CREATEANL:
    case LibgistCommand.SCRIPT:
        setGuiState(priorState);
	break;

    }
}


private int
strlen(char[] str)
{
    int len = 0;
    while (len < str.length && str[len] != '\0') len++;
    return len;
}


// ask user for script file and name of new profile
// return false if user cancelled operation
private boolean
getNewWkldInput(
    JFileChooser chooser,
    Object[] optionDlgMsg,
    StringBuffer name,
    StringBuffer scriptFile)
{
    // let user select script file with queries
    boolean fileOk = false;
    int retval;
    File file = null;
    FileReader reader = null;
    while (!fileOk) {
	if ((retval = chooser.showDialog(this, "Ok")) != 0) {
	    return false;
	}
	file = chooser.getSelectedFile();
	try {
	    reader = new FileReader(file.getPath());
	    fileOk = true;
	    scriptFile.append(file.getPath());
	} catch (FileNotFoundException e) {
	    JOptionPane.showMessageDialog(this, 
	        "Selected script file does not exist", "Error: New Profile",
		JOptionPane.ERROR_MESSAGE);
	} 
    }

    // let user select filename for profile
    int response = JOptionPane.showOptionDialog(this, optionDlgMsg, "New Profile",
	JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, null, null);
    if (response != JOptionPane.OK_OPTION) {
	return false;
    }
    JTextField textFld = (JTextField) optionDlgMsg[1];
    name.append(file.getParent() + "/" + textFld.getText());
    return true;
}

// create a new profile: read the script and possibly execute the queries,
// save the stats (if 'import' == true, we assume the profile already exists
// and don't run the queries)
public void
createWkld(String name, String scriptFile, boolean runQueries)
{
    System.gc();
    Workload wkld = new Workload(name);

    if (showCmdsItem.getState()) {
	consoleFrame.echoCmd((!runQueries ? "importprof " : "newwkld ")
	    + name + " " + scriptFile);
    }

    // construct the Workload object from the script;
    // first, check if the file exists
    try {
	FileReader reader = new FileReader(scriptFile);
	reader.close();
    } catch (FileNotFoundException e) {
	System.out.println("couldn't open " + scriptFile);
	return;
    } catch (IOException e) {
	System.out.println("couldn't close " + scriptFile);
    } 

    // now, check if it contains only queries
    int scriptId = 0;
    try {
	scriptId = Libgist.openScript(scriptFile);
    } catch (LibgistException e) {
	System.out.println("couldn't open (C) " + scriptFile);
        return;
    }
    char[] arg1 = new char[64*1024];
    StringBuffer arg1Buf = new StringBuffer();
    char[] arg2 = new char[64*1024];
    StringBuffer arg2Buf = new StringBuffer();
    //for (;;) {
        //int cmd = Libgist.getCommand(scriptId, arg1, arg2);
	//if (cmd == Libgist.EOF) break;
	//if (cmd != Libgist.FETCH) {
	    // there should only be queries
	    //System.out.println("Script file contains non-SELECT command");
	    //return;
	//}
    //}

    if (runQueries) {
	// turn profiling on and execute queries
	//Libgist.setProfilingEnabled(true);
	Libgist.disableBps(true); // we don't want to stop at breakpoints

	// rescan queries
	try {
	    scriptId = Libgist.openScript(scriptFile);
	} catch (LibgistException e) {
	    System.out.println("couldn't open (C) " + scriptFile);
	    return;
	}
	int cnt = 1;
	//for (;;) {
	    //int cmd = Libgist.getCommand(scriptId, arg1, arg2);
	    //if (cmd == Libgist.EOF) break;
	    //arg1Buf.setLength(0);
	    //arg1Buf.append(arg1, 0, strlen(arg1));
	    //arg2Buf.setLength(0);
	    //arg2Buf.append(arg2, 0, strlen(arg2));
	    //OpThread.execCmd(LibgistCommand.FETCH, arg1Buf.toString(),
	        //arg2Buf.toString(), false);
	    //System.out.print(cnt + " ");
	    //System.out.println(cnt + ": execute " + arg2Buf.toString() + " "
	    //+ arg1Buf.toString());
	    //cnt++;
	//}
	System.out.println();

	Libgist.disableBps(false);
	// compute optimal clustering and some more statistics
	//Libgist.computeMetrics(wkld.filename);
    }

    // save profile
    try {
	// we're saving Java and C++ data in separate files (filename and filename.prof)
        // the profile object only contains the filename, the queries will be 
        // read in from the file when the profile is opened (faster that way)
	ObjectOutputStream out =
	    new ObjectOutputStream(new FileOutputStream(wkld.filename));
	out.writeObject(wkld);
	out.close();
	System.out.println("copy query file");
	Runtime.getRuntime().exec("cp " + scriptFile + " " + wkld.filename + ".queries");
	System.out.println("saving tree and profile");
	Libgist.saveToFile(wkld.filename + ".idx");
	if (runQueries) {
	    //Libgist.saveProfile(wkld.filename + ".prof");
	}
    } catch (Exception e) {
	System.out.println("Error saving profile: " + e);
	return;
    }

    if (runQueries) {
	// turn profiling off (after the metrics were computed and
        // the profile saved)
	//Libgist.setProfilingEnabled(false);
    }
}


public
MainWindow()
{
    JMenuItem showTextItem, showContentItem, showStatsItem;
    JMenuItem consoleWinItem, treeWinItem, traceWinItem;

    // our libgist execution thread
    opThread = new OpThread(this);
    Libgist.setBreakHandler(opThread);
    opThread.start();
    cmd = new LibgistCommand();

    menuBar = new JMenuBar();
    setJMenuBar(menuBar);

    // create toolbar and console window with text area

    getContentPane().removeAll();
    getContentPane().setLayout(new BorderLayout());
    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());

    // desktop pane + console frame
    desktop = new JDesktopPane();
    desktop.setOpaque(true);
    desktop.setBackground(Color.lightGray);
    consoleFrame = new ConsoleWindow(200, desktop);
    desktop.add(consoleFrame, JLayeredPane.PALETTE_LAYER);

    // debugging actions for toolbar:
    // notify opThread of what to do when it hits a breakpoint
    stepAction = new AbstractAction("Step") {
        public void actionPerformed(ActionEvent e) {
	    opThread.step();
	}
    };
    cancelAction = new AbstractAction("Cancel") {
        public void actionPerformed(ActionEvent e) {
	    scriptWasCancelled = true; // don't call it after next line!
	    opThread.cancel();
	}
    };
    nextAction = new AbstractAction("Next") {
        public void actionPerformed(ActionEvent e) {
	    opThread.next();
	}
    };
    contAction = new AbstractAction("Continue") {
        public void actionPerformed(ActionEvent e) {
	    opThread.cont();
	}
    };

    // opThread is currently executing a script and we want it to stop:
    // tell libgist directly to suspend execution once opThread is done
    // with the current operation
    stopAction = new AbstractAction("Stop") {
        public void actionPerformed(ActionEvent e) {
	    Libgist.singleStep();
	}
    };

    // toolbar
    JToolBar toolbar = new JToolBar();
    toolbar.add(stepAction).setText("Step");
    toolbar.add(nextAction).setText("Next");
    toolbar.add(contAction).setText("Continue");
    toolbar.add(stopAction).setText("Stop");
    toolbar.add(cancelAction).setText("Cancel");

    panel.add(toolbar, BorderLayout.NORTH);
    panel.add(desktop, BorderLayout.CENTER);
    getContentPane().add(panel);

    createFileMenu();
    createOpsMenu();
    createDebugMenu();
    createTreeStatsMenu();
    createAnalysisMenu();
    createWindowsMenu();

    setGuiState(INITSTATE); // nothing opened yet

    //addWindowListener(this); // So we do the right thing on window closing.
}


private void
createFileMenu()
{
    fileMenu = new JMenu("File");
    menuBar.add(fileMenu);

    newItem = new JMenuItem("New...");
    fileMenu.add(newItem);
    // construct components of option pane to input name and type of new AM
    final Object[] newMsg = new Object[3];
    newMsg[0] = "Name for new AM:";
    final JTextField newName = new JTextField("new-am");
    newMsg[1] = newName;
    final JComboBox cb = new JComboBox();
    for (int i = 0; i < Libgist.extInfo.length; i++) {
	cb.addItem(Libgist.extInfo[i].name);
    }
    newMsg[2] = cb;
    newItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // first close the currently opened index
	    int response = JOptionPane.showOptionDialog(MainWindow.this, newMsg, "New",
		JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE,
		null, null, null);
	    if (response != JOptionPane.OK_OPTION) {
		return;
	    }

	    // create new AM
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.CREATE;
	    cmd.indexName.append(newName.getText());
	    cmd.extension.append(Libgist.extInfo[cb.getSelectedIndex()]);
	    opThread.dispatchCmd(cmd);
	}
    });

    openItem = new JMenuItem("Open...");
    final JFileChooser openChooser = new JFileChooser(".");
    openChooser.setDialogTitle("Open Index");
    openChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    fileMenu.add(openItem);
    openItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    // first close currently opened index
	    // let user choose index file
	    int retval = openChooser.showOpenDialog(MainWindow.this);
	    if (retval != 0) {
		return;
	    }
	    String fileName = openChooser.getSelectedFile().getPath();

	    // open AM
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.OPEN;
	    cmd.indexName.append(fileName);
	    opThread.dispatchCmd(cmd);

	    enableIndexOpened();

	}
    });

    closeItem = new JMenuItem("Close");
    fileMenu.add(closeItem);
    closeItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    // close AM
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.CLOSE;
	    opThread.dispatchCmd(cmd);
	    //MainWindow.this.setTitle("amdb");
	}
    });

    flushItem = new JMenuItem("Flush");
    fileMenu.add(flushItem);
    flushItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    // open AM
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.FLUSH;
	    opThread.dispatchCmd(cmd);
	}
    });

    fileMenu.addSeparator();

    optionsItem = new JMenuItem("Properties...");
    fileMenu.add(optionsItem);
    optionsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    Properties.edit();
	}
    });

    settingsItem = new JMenuItem("Save Settings");
    fileMenu.add(settingsItem);
    settingsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    saveConfig();
	}
    });
    fileMenu.addSeparator();
    exitItem = new JMenuItem("Exit");
    fileMenu.add(exitItem);
    exitItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    // close AM
	    opThread.stopNow();
	    Libgist.cleanup();
	    System.exit(0);
	}
    });
}

private void
createOpsMenu()
{
    opsMenu = new JMenu("Ops");
    menuBar.add(opsMenu);

    insertItem = new JMenuItem("Insert...");
    opsMenu.add(insertItem);
    final Object[] insertMsg = new Object[4];
    insertMsg[0] = "Key:";
    final JTextField insertKey = new JTextField("");
    insertMsg[1] = insertKey;
    insertMsg[2] = "Data:";
    final JTextField insertData = new JTextField("");
    insertMsg[3] = insertData;
    insertItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    int response = JOptionPane.showOptionDialog(MainWindow.this, insertMsg, "Insert",
		JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE,
		null, null, null);
	    if (response != JOptionPane.OK_OPTION) {
	        return;
	    }

	    // insert new item
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.INSERT;
	    cmd.key.append(insertKey.getText());
	    cmd.data.append(insertData.getText());
	    opThread.dispatchCmd(cmd);
	}
    });

    deleteItem = new JMenuItem("Delete...");
    opsMenu.add(deleteItem);
    final Object[] deleteMsg = new Object[2];
    deleteMsg[0] = "Query:";
    final JTextField deleteQuery = new JTextField("");
    deleteMsg[1] = deleteQuery;
    deleteItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    int response = JOptionPane.showOptionDialog(MainWindow.this, deleteMsg,
	        "Delete", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE,
		null, null, null);
	    if (response != JOptionPane.OK_OPTION) {
	        return;
	    }

	    // delete item(s)
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.REMOVE;
	    cmd.qual.append(deleteQuery.getText());
	    opThread.dispatchCmd(cmd);
	}
    });

    searchItem = new JMenuItem("Search...");
    opsMenu.add(searchItem);
    final Object[] searchMsg = new Object[4];
    searchMsg[0] = "Query:";
    final JTextField searchQuery = new JTextField("");
    searchMsg[1] = searchQuery;
    searchMsg[2] = "Retrieval Limit:";
    final JTextField retrLimit = new JTextField("");
    searchMsg[3] = retrLimit;
    searchItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    int response = JOptionPane.showOptionDialog(MainWindow.this, searchMsg, "Search",
		JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE,
		null, null, null);
	    if (response != JOptionPane.OK_OPTION) {
	        return;
	    }
	    int limit = 0; // 0 means "get them all"
	    // if no limit is specified: we leave it at 0
	    if (retrLimit.getText() != null) {
		try {
		    limit = Integer.parseInt(retrLimit.getText());
		} catch (NumberFormatException e) {
		    // user typed junk
		    limit = 0;
		    retrLimit.setText("");
		}
	    }

	    // execute query
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.FETCH;
	    cmd.qual.append(searchQuery.getText());
	    cmd.fetchLimit = limit;
	    opThread.dispatchCmd(cmd);
	}
    });

    executeItem = new JMenuItem("Execute...");
    final JFileChooser executeChooser = new JFileChooser(".");
    executeChooser.setDialogTitle("Execute Script");
    executeChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    opsMenu.add(executeItem);
    executeItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    // let user choose script file
	    int retval = executeChooser.showDialog(MainWindow.this, "Execute");
	    if (retval != 0) {
	        return;
	    }

	    // execute script
	    cmd.reset();
	    cmd.cmdType = LibgistCommand.SCRIPT;
	    cmd.scriptFile.append(executeChooser.getSelectedFile().getPath());
	    opThread.dispatchCmd(cmd);
	}
    });
}

private void
createDebugMenu()
{
    debugMenu = new JMenu("Debug");
    menuBar.add(debugMenu);
    debugMenu.add(stepAction);
    debugMenu.add(nextAction);
    debugMenu.add(contAction);
    debugMenu.add(stopAction);
    traceAllItem = new JCheckBoxMenuItem("Trace All");
    debugMenu.add(traceAllItem);
    debugMenu.addSeparator();
    breakpointsItem = new JMenuItem("Breakpoints...");
    debugMenu.add(breakpointsItem);
    breakpointsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    Breakpoints.edit();
	}
    });
    Breakpoints.setParent(this);
}

private void
createTreeStatsMenu()
{
    treeStatsMenu = new JMenu("Tree Stats");
    menuBar.add(treeStatsMenu);
    utilItem = new JMenuItem("Utilization");
    treeStatsMenu.add(utilItem);
    utilItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    Libgist.getWkldNodeStats(Libgist.NODEUTIL, 0, false);
	    treeView.showStats(Libgist.nodeCnt, Libgist.displayStats, utilItem.getText());
	}
    });
    slotCntItem = new JMenuItem("Slot Count");
    treeStatsMenu.add(slotCntItem);
    slotCntItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    Libgist.getWkldNodeStats(Libgist.SLOTCNT, 0, false);
	    treeView.showStats(Libgist.nodeCnt, Libgist.displayStats, slotCntItem.getText());
	}
    });
    predSzItem = new JMenuItem("Predicate Size");
    treeStatsMenu.add(predSzItem);
    predSzItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
	    Libgist.getWkldNodeStats(Libgist.PREDSIZE, 0, false);
	    treeView.showStats(Libgist.nodeCnt, Libgist.displayStats, predSzItem.getText());
	}
    });
}


private void
createAnalysisMenu()
{
    analysisMenu = new JMenu("Analysis");
    menuBar.add(analysisMenu);

    // analysis-related variables
    analysisInfo = new AnalysisInfo();
    wkldStatsDlg = new WkldStatsDlg(this);
    splitStatsDlg = new SplitStatsDlg(this);
    penaltyStatsDlg = new PenaltyStatsDlg(this);

    newAnalysisItem = new JMenuItem("Create Analysis ...");
    analysisMenu.add(newAnalysisItem);
    newAnalysisItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    JOptionPane.showMessageDialog(MainWindow.this,
	        "Not implemented yet.\nUse command createanl in gistcmdline instead.");
	}
    });

    openAnalysisItem = new JMenuItem("Open Analysis ...");
    final JFileChooser openAnalysisChooser = new JFileChooser(".");
    openAnalysisChooser.setDialogTitle("Open Analysis");
    openAnalysisChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    analysisMenu.add(openAnalysisItem);
    openAnalysisItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    int retval = openAnalysisChooser.showOpenDialog(MainWindow.this);
	    if (retval != 0) {
		    return;
	    }
	    File f = openAnalysisChooser.getSelectedFile();

	    cmd.reset();
	    cmd.cmdType = LibgistCommand.OPENANL;
	    cmd.analysisFile = f;
	    opThread.dispatchCmd(cmd);
	}
    });

    completeAnalysisItem = new JMenuItem("Complete Analysis ...");
    analysisMenu.add(completeAnalysisItem);
    completeAnalysisItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    JOptionPane.showMessageDialog(MainWindow.this,
	        "Not implemented yet.\nUse commands wkldstats, splitstats and penaltystats\nin gistcmdline instead.");
	}
    });

    analysisMenu.addSeparator();

    wkldStatsItem = new JMenuItem("Workload Stats ...");
    analysisMenu.add(wkldStatsItem);
    wkldStatsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    wkldStatsDlg.setVisible(true);
	}
    });

    splitStatsItem = new JMenuItem("Split Stats ...");
    analysisMenu.add(splitStatsItem);
    wkldStatsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    splitStatsDlg.setVisible(true);
	}
    });

    penaltyStatsItem = new JMenuItem("Penalty Stats ...");
    analysisMenu.add(penaltyStatsItem);
    penaltyStatsItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent event) {
	    penaltyStatsDlg.setVisible(true);
	}
    });
}

private void
createWindowsMenu()
{
    windowsMenu = new JMenu("Windows");
    menuBar.add(windowsMenu);
    showCmdsItem = new JCheckBoxMenuItem("Show Commands");
    showCmdsItem.setState(true);
    windowsMenu.add(showCmdsItem);
    showResultsItem = new JCheckBoxMenuItem("Show Results");
    showResultsItem.setState(true);
    windowsMenu.add(showResultsItem);
    showTraceItem = new JCheckBoxMenuItem("Show Trace Output");
    showTraceItem.setState(true);
    windowsMenu.add(showTraceItem);
    tileItem = new JMenuItem("Tile");
    tileItem.addActionListener(new ActionListener() {
	public void actionPerformed(ActionEvent event) {
	    MainWindow.this.tile();
	}
    });
    windowsMenu.add(tileItem);
}

private void
setTree(String title)
{
    consoleFrame.setTree(title);
}

private void
open(String indexName)
{
    DbgOutput.println(1, "open() " + indexName);
    cmd.reset();
    cmd.cmdType = LibgistCommand.OPEN;
    cmd.indexName.append(indexName);
    opThread.dispatchCmd(cmd);
}

public static void
main(String[] argv)
{
    MainWindow win;

    DbgOutput.toStdout();
    win = new MainWindow();
    // process cmd line arguments
    int i;
    for (i = 0; i < argv.length; i++) {
	if (argv[i].equals("-D")) {
	    i++;
	    // try to interpret the next argument as the debug level
	    int dbgLvl = 1; // basic debug level
	    if (i >= argv.length) {
	        // no more arguments, we stick with debug level 1
		break;
	    }
	    try {
	        dbgLvl = Integer.parseInt(argv[i]);
	    } catch(NumberFormatException e) {
	        dbgLvl = 1; // didn't work, this is probably a filename
		win.open(argv[i]);
	    }
	    DbgOutput.setDbgLevel(dbgLvl);
	    Libgist.setDbgLevel(dbgLvl);

	} else if (argv[i].equals("-h")) { 
	    // print help message and exit
	    System.out.println("Usage: amdb [-D <dbglevel> | -h] [index]");
	    System.exit(0);

	} else {
	    // this is a name of an index, open it
	    //System.out.println("open " + argv[i]);
	    win.open(argv[i]);
	}

    }
    win.setTitle("amdb");
    win.setSize(800, 600);
    win.setLocation(50, 50);
    win.setVisible(true);

}

}

