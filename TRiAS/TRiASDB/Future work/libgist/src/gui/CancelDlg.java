// CancelDlg.java
// Copyright (c) 1998, Regents of the University of California
// $Id: CancelDlg.java,v 1.2 1999/06/27 00:17:36 marcel Exp $

import javax.swing.*;
import java.lang.*;
import java.io.*;
import java.util.Vector;

/*
 * Thread to execute display progress dialog and allow user to cancel ongoing operation
 * (in OpThread).
 */

public class CancelDlg extends Thread
{

// returns true if user pressed "Cancel"
public boolean
isCancelled()
{
}

// updates the message text in the dialog
public void
setMsg(String msg)
{
}

// sets value of progress bar
public void
setProgressValue(int val)
{
}

// sets minimum of progress bar
public void
setProgressMin(int min)
{
}

// sets maximum of progress bar
public void
setProgressMax(int max)
{
}

// switches progress bar on/off
public void
setProgressEnabled(boolean enable)
{
}

}

