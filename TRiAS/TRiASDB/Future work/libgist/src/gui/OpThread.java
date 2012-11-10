// OpThread.java
// Copyright (c) 1998, Regents of the University of California
// $Id: OpThread.java,v 1.2 1999/06/27 00:17:37 marcel Exp $

import javax.swing.*;
import java.lang.*;
import java.io.*;
import java.util.Vector;

/*
 * Thread to execute libgist functions. These cannot be executed in main thread, because
 * the application must still process events (e.g., from stop button) while libgist hits
 * a breakpoint or a script is executed. 
 */
public class OpThread extends Thread implements BreakHandler
{

MainWindow mainWin; // we call back our mainWin to do the work

private LibgistCommand command; // passed in through dispatchCmd()
private LibgistCommand scriptCmd = new LibgistCommand(); // used in execScript()
private boolean stop = false;
private boolean penaltyChecksEnabled = false;
private int whatToDo; // step, next or continue?
private boolean inWkld; // true if command is executed as part of a workload
private boolean isScript; // true if we're executing a script
private boolean echoCmd = true; // if true, echo command to Console
private AnalysisInfo analysisInfo = new AnalysisInfo();

OpThread(MainWindow c)
{
    mainWin = c;
}

public void
setPenaltyChecksEnabled(boolean enabled)
{
    penaltyChecksEnabled = enabled;
}


///////////////////////////////////////////////////////////////////////////////
// execCmd - execute libgist function
//
// Description:
//	- only called from libgist execution thread itself
//	- first, echo the command on the console, then try to execute it
//	- echo error messages in console
//	- during execution of operation, disable mainWin (STOPSTATE), until
//	  it hits a breakpoint or the operation finishes; then, restore
//	  the prior state; call updateGuiState() only *after* the prior state
//	  has been restored
//
// Exceptions:
//
// Return Values:
///////////////////////////////////////////////////////////////////////////////

public boolean
execCmd(LibgistCommand cmd)
{
    boolean success = true;
    mainWin.echoCmd(cmd);
    int guiState = mainWin.setGuiState(MainWindow.STOPSTATE);
    //mainWin.setStopEnabled(true);

    try {
	switch (cmd.cmdType) {

	case LibgistCommand.INSERT:
	    Libgist.insert(cmd.key.toString(), cmd.data.toString());
	    mainWin.treeView.refresh();
	    break;

	case LibgistCommand.REMOVE:
	    Libgist.remove(cmd.qual.toString());
	    mainWin.treeView.refresh();
	    break;

	case LibgistCommand.CREATE:
	    // convert the extension name in arg2 to its ID
	    int i;
	    int id = 0;
	    for (i = 0; i < Libgist.extInfo.length; i++) {
	        if (Libgist.extInfo[i].name.compareTo(
		    cmd.extension.toString().toLowerCase()) == 0) {

		    // we found the extension
		    id = Libgist.extInfo[i].id;
		    break;
		}
	    }
	    if (i == Libgist.extInfo.length) {
		JOptionPane.showMessageDialog(mainWin, 
		    "Unknown extension: " + cmd.extension.toString(),
		    "Error", JOptionPane.ERROR_MESSAGE);
		return(false);
	    }
	    Libgist.create(cmd.indexName.toString(), id);
	    break;

	case LibgistCommand.OPEN:
	    Libgist.open(cmd.indexName.toString());
	    break;

	case LibgistCommand.CLOSE:
	    Libgist.close();
	    break;

	case LibgistCommand.FLUSH:
	    Libgist.flush();
	    break;

	case LibgistCommand.FETCH:
	    Libgist.fetch(cmd.qual.toString(), cmd.fetchLimit,
		mainWin.echoResults);
	    break;

	case LibgistCommand.SCRIPT:
	    execScript(cmd);
	    break;

	case LibgistCommand.OPENANL:
	    Libgist.openAnalysis(cmd.analysisFile.getPath());
	    Libgist.getAnalysisInfo(analysisInfo);
	    DbgOutput.println(2, "OpThread.execCmd: open " + analysisInfo.actualName);
	    Libgist.open(cmd.analysisFile.getParent() + File.separator +
	        analysisInfo.actualName);
	    DbgOutput.println(2, "opened");
	    break;

	case LibgistCommand.CLOSEANL:
	    Libgist.writeAnalysis();
	    Libgist.closeAnalysis();
	    Libgist.close();
	    break;

	default:
	    throw new LibgistException("Invalid operation");
	}

	// if we finished executing a script, don't reset the state,
	// because executing the script might have changed it
	if (cmd.cmdType != LibgistCommand.SCRIPT) {
	    // operation was successfully executed at this point,
	    // update GUI state, if necessary
	    mainWin.updateGuiState(guiState, cmd, true);
	} 

    } catch (Exception e) {
	success = false;
	mainWin.updateGuiState(guiState, cmd, false);
	// log error in console window
	mainWin.consoleFrame.echoInfo(e.toString());
    }

    yield();
    return(success);
}


///////////////////////////////////////////////////////////////////////////////
// execScript - parse and execute lines of script
//
// Description:
//
// Exceptions: LibgistException
///////////////////////////////////////////////////////////////////////////////

private void
execScript(LibgistCommand cmd) throws LibgistException
{
    int script = Libgist.openScript(cmd.scriptFile.toString());
    int cmdId;
    while ((cmdId = Libgist.getCommand(script, scriptCmd)) >= 0) {
        if (!execCmd(scriptCmd)) {
	    throw new LibgistException("abort script execution");
	}
    }
}


public synchronized void
run()
{
    while (!stop) {
	try {
	    wait();
	} catch (InterruptedException e) {
	}
	if (stop) break;
	isScript = (command.cmdType == LibgistCommand.SCRIPT);
	execCmd(command);
    }
    DbgOutput.println(1, "finishing opThread");
}


///////////////////////////////////////////////////////////////////////////////
// execOp - tell thread to execute libgist function
//
// Description:
//
// Exceptions: none
//
///////////////////////////////////////////////////////////////////////////////

public synchronized void
dispatchCmd(LibgistCommand cmd)
{
    command = cmd;
    notify();
}

private boolean
isInterruptableEvent(int event)
{
    if (event == BreakInfo.INSERT || event == BreakInfo.REMOVE ||
        event == BreakInfo.FETCH) {

        return true;
    } else {
        return false;
    }
}

// print break info on console
private void
printInfo(BreakInfo info)
{
    DbgOutput.println(1, "OpThread.printInfo(): id: " + info.id + " event: "
        + info.event + " node: " + info.nodeId);
    String msg = "";
    if (info.id != 0) {
        msg += info.id + ": ";
    }
    try {
	switch (info.event) {
	case BreakInfo.INSERT:
	    msg += "insert";
	    break;
	case BreakInfo.REMOVE:
	    msg += "remove";
	    break;
	case BreakInfo.FETCH:
	    msg += "fetch";
	    break;
	case BreakInfo.NODESPLIT:
	    msg += "split (node=" + info.nodeId + ")";
	    mainWin.treeView().showPath(info.nodeId);
	    break;
	case BreakInfo.TRAVERSAL:
	    msg += "traversal (node=" + info.nodeId + ")";
	    mainWin.treeView().showPath(info.nodeId);
	    break;
	case BreakInfo.NODEINSERT:
	    msg += "item insertion (node=" + info.nodeId + ")";
	    mainWin.treeView().showPath(info.nodeId);
	    break;
	case BreakInfo.NODEDELETE:
	    msg += "item deletion (node=" + info.nodeId + ")";
	    mainWin.treeView().showPath(info.nodeId);
	    break;
	case BreakInfo.BPUPDATE:
	    msg += "BP update (node=" + info.nodeId + ")";
	    mainWin.treeView().showPath(info.nodeId);
	    break;
	case BreakInfo.LOCATELEAF:
	    msg += "Located target leaf (node=" + info.nodeId;
	    if (penaltyChecksEnabled) {
		msg += ", targetPen=" + info.targetPenalty + ", minPen=" +
		    info.minPenalty + ", minLeaf=" + info.minLeaf + ")";
	    } else {
	       msg += ")";
	    }
	    mainWin.treeView().showPath(info.nodeId);
	    break;	
	case BreakInfo.NEWNODE:
	    msg += "new node (node =" + info.nodeId + ")";
	    mainWin.treeView().refresh();
	    break;
	case BreakInfo.NEWROOT:
	    msg += "new root (node =" + info.nodeId + ")";
	    mainWin.treeView().refresh();
	    break;
	case BreakInfo.ITEMINSERTED:
	    msg += "item inserted (node=" + info.nodeId + ")";
	    mainWin.treeView().refresh();
	    break;
	case BreakInfo.ITEMDELETED:
	    msg += "item deleted (node=" + info.nodeId + ")";
	    mainWin.treeView().refresh();
	    break;
	case BreakInfo.BPUPDATED:
	    msg += "BP updated (node=" + info.nodeId + ")";
	    mainWin.treeView().refresh();
	default:
	    msg += "unknown event";
	    break;
	}
    } catch (LibgistException e) {
	mainWin.consoleFrame.echoInfo(e.toString());
    }
    mainWin.consoleFrame.echoInfo(msg);
}


///////////////////////////////////////////////////////////////////////////////
// breakHandler - called by libgist when reaching breakpoint
//
// Description:
//
// Exceptions:
//
// Return Values:
//	value tells libgist how to proceed
///////////////////////////////////////////////////////////////////////////////

public synchronized int
breakHandler(BreakInfo info)
{
    DbgOutput.println(2, "starting breakHandler");
    // user can only cancel script if it doesn't corrupt the index;
    // in other words, we can't cancel an update operation in midstream
    printInfo(info);

    // if only tracepoint, continue
    Breakpoint bp = Breakpoints.lookup(info.id);
    if (bp != null && bp.trace.booleanValue()) {
        return BreakHandler.CONTINUE;
    }

    boolean enableCancel =  isInterruptableEvent(info.event);
    mainWin.setGuiState(MainWindow.DEBUGSTATE, isScript, enableCancel);
    try {
	wait();
    } catch (InterruptedException e) {
    }
    mainWin.setGuiState(MainWindow.STOPSTATE);
    DbgOutput.println(2, "finish breakHandler");
    yield();
    if (whatToDo == BreakHandler.CANCEL) {
        mainWin.consoleFrame.echoInfo("cancelled");
    }
    return whatToDo;
}


///////////////////////////////////////////////////////////////////////////////
// step - executed by Step button
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public synchronized void
step()
{
    whatToDo = BreakHandler.STEP;
    notify();
}


///////////////////////////////////////////////////////////////////////////////
// next - executed by Next button
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public synchronized void
next()
{
    whatToDo = BreakHandler.NEXT;
    notify();
}


///////////////////////////////////////////////////////////////////////////////
// cont - executed by Continue button
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public synchronized void
cont()
{
    whatToDo= BreakHandler.CONTINUE;
    notify();
}

///////////////////////////////////////////////////////////////////////////////
// cancel - executed by Cancel Script button
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

// executed by Cancel Script button
public synchronized void
cancel()
{
    whatToDo = BreakHandler.CANCEL;
    notify();
}

///////////////////////////////////////////////////////////////////////////////
// stopNow - tell thread to stop
//
// Description:
//
// Exceptions: none
///////////////////////////////////////////////////////////////////////////////

public synchronized void
stopNow()
{
    stop = true;
    DbgOutput.println(2, "opThread stopping");
    notify();
}

}

