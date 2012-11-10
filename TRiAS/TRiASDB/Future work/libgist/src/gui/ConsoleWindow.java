// ConsoleWindow.java
// Copyright (c) 1998, Regents of the University of California
// $Id: ConsoleWindow.java,v 1.2 1999/06/27 00:17:37 marcel Exp $

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.lang.*;
import java.io.*;

/*
 * window with console output
 */
public class ConsoleWindow extends JInternalFrame
{

int numRows; // # of recorded rows
JDesktopPane desktop;
JTextArea consoleText; // output text area
Font cmdFont, infoFont;
int[] rowLengths; // circular array, containing current row lengths
int topRow; // index of first row of JTextArea

// create console window with capacity for specified # of rows
public ConsoleWindow(int rows, JDesktopPane desktop)
{
    super("Console", true, false, true, true);
    numRows = rows;
    this.desktop = desktop;
    rowLengths = new int[rows];
    topRow = 0;
    getContentPane().setLayout(new BorderLayout());
    //setTitle("Console");
    setBounds(20, 20, 300, 200);

    JPanel areaPanel = new JPanel(new BorderLayout());
    areaPanel.setAlignmentX(LEFT_ALIGNMENT);
    getContentPane().add(areaPanel, BorderLayout.CENTER);

    consoleText = new JTextArea("");
    JScrollPane scroller = new JScrollPane() {
	// do I really need these redefined?
	public Dimension getPreferredSize() {
	    return new Dimension(10,10);
	}
        public float getAlignmentX() {
	    return LEFT_ALIGNMENT;
	}
    };
    scroller.getViewport().add(consoleText);
    consoleText.setFont(new Font("Dialog", Font.PLAIN, 10));
    areaPanel.add(scroller, BorderLayout.CENTER);

    // create fonts
    //cmdFont = new Font("Dialog", Font.BOLD, 10);
    //infoFont = new Font("Dialog", Font.PLAIN, 10);
}

public void
setTree(String name)
{
    setTitle("Console: " + name);
}

// fill lower part of desktop
public void
tile()
{
    Rectangle bounds = desktop.getBounds();
    bounds.x = 0;
    bounds.y = bounds.height - 190;
    bounds.height = 150;
    setBounds(bounds);
}

private void
replaceRow(String newRow)
{
    if (rowLengths[topRow] != 0) {
        // remove that row from the display
	consoleText.replaceRange("", 0, rowLengths[topRow]);
    }
    rowLengths[topRow] = newRow.length();
    topRow = (topRow + 1) % numRows;
}


///////////////////////////////////////////////////////////////////////////////
// echoCmd - echo one command line (including \n) at bottom of console window
//
// Description:
//
// Exceptions:
//
// Return Values:
///////////////////////////////////////////////////////////////////////////////

public void
echoCmd(String line)
{
    String out = ">" + line + "\n";
    replaceRow(out);
    consoleText.setCaretPosition(consoleText.getText().length());
    consoleText.append(out);
}


///////////////////////////////////////////////////////////////////////////////
// echoInfo - echo one message line (including \n) at bottom of console window
//
// Description:
//
// Exceptions:
//
// Return Values:
///////////////////////////////////////////////////////////////////////////////

public void
echoInfo(String line)
{
    String out = line + "\n";
    replaceRow(out);
    consoleText.setCaretPosition(consoleText.getText().length());
    consoleText.append(out);
}


///////////////////////////////////////////////////////////////////////////////
// echoTuple - echo one returned tuple (including \n) at bottom of window
//
// Description:
//
// Exceptions:
//
// Return Values:
///////////////////////////////////////////////////////////////////////////////

public void
echoTuple(String line)
{
    String out = "-> " + line + "\n";
    replaceRow(out);
    consoleText.setCaretPosition(consoleText.getText().length());
    consoleText.append(out);
}

// change the # of recorded rows;
// if the number is decreased, delete the excess number of rows from the top of
// the JTextArea;
// if the number is increased, insert them at the bottom
public void
setRows(int rows)
{
    if (rows < numRows) {
        // throw away excess rows
	for (int i = 0; i < numRows - rows; i++) {
	    replaceRow("");
	}
    }
    int[] tmpLengths = rowLengths;
    int[] rowLengths = new int[rows];
    // copy row lengths over
    int min = (rows < numRows ? rows : numRows);
    for (int i = 0; i < min; i++) {
        rowLengths[i] = tmpLengths[topRow + i];
    }
    numRows = rows;
    topRow = 0;
}

}
