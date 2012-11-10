// NodeDump.java
// Copyright (c) 1998, Regents of the University of California
// $Id: NodeDump.java,v 1.3 1999/09/27 01:10:47 marcel Exp $

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class NodeDump extends JInternalFrame implements 
InternalFrameListener 

{


public JScrollPane scroll;
public JTextArea   textArea;
public Node        node;
public int         size;

public NodeDump(Node node, TreeView tv) {

    this.node = node;

    setTitle("Node Contents: " + node.nodenum);
    setSize(150,150);

    Rectangle tbounds = tv.getBounds();
    Point location = new Point();
    location.x = tbounds.x;
    location.y = tbounds.y + tbounds.height;
    
    setLocation(location);

    setResizable(true);
    setMaximizable(true);
    setIconifiable(true);
    setClosable(true);
    getContentPane().setLayout(new BorderLayout());

    textArea = new JTextArea();

    textArea.setFont(new Font("Dialog", Font.PLAIN, 10));

    try {
	size = Libgist.dump(textArea, node.nodenum);
    } catch (LibgistException ex) {
	System.out.println("NodeDump - Libgist.dump: " + ex);
    }

    scroll = new JScrollPane(/* can */ textArea);

    tv.nodedumps.addElement(this);

    getContentPane().add(scroll, BorderLayout.CENTER);
    
    AbstractAction saveAsAction = new AbstractAction("Pal") {

	public void actionPerformed(ActionEvent e) {
	    
	    saveTextArea();
	}
    };


    JMenuBar menubar = new JMenuBar();

    JMenu filemenu = new JMenu("File");

    JMenuItem menuItem = new JMenuItem("Save As ...");
    menuItem.addActionListener(saveAsAction);
    filemenu.add(menuItem);

    menubar.add(filemenu);

    getRootPane().setJMenuBar(menubar);

    addInternalFrameListener(this);
}

public void refresh() {
    
    DbgOutput.println(1,"In refresh ...");
    // null out the area ...
    textArea.replaceRange("",0,size);

    try {
	size = Libgist.dump(textArea, node.nodenum);
    } catch (LibgistException ex) {
	System.out.println("NodeDump - Libgist.dump: " + ex);
    }

}

public int dumpFile(String filename) throws IOException {

    textArea.write(new FileWriter(filename));

    return (1);
}

public int saveTextArea() {

    JFileChooser chooser = new JFileChooser("../");
    chooser.setDialogTitle("Save As ...");
    chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

    boolean fileOk = false;
    
    int result = 0;

    while (!fileOk) {
	
	try {
	    
	    if (chooser.showDialog(this, "Ok") != 0)
		return result;
	    
	    result = dumpFile(chooser.getSelectedFile().getPath());

	    fileOk = true;

	} catch (Exception e) {
	    
	    JOptionPane.showMessageDialog(this,
		"Error saving contents: " + e, "Error:Save As ...",
		JOptionPane.ERROR_MESSAGE);
	    
	    e.printStackTrace();
	}
	
    }

    return (result);
}

public void internalFrameActivated(InternalFrameEvent ie) {};

public void internalFrameClosed(InternalFrameEvent ie) {

    // DbgOutput.println(1,"THIS");
};

public void internalFrameClosing(InternalFrameEvent ie) {
    // DbgOutput.println(1,"WHAT");
    // setVisible(false);
}

public void internalFrameDeactivated(InternalFrameEvent ie) {};

public void internalFrameDeiconified(InternalFrameEvent ie) {};

public void internalFrameIconified(InternalFrameEvent ie) {};

public void internalFrameOpened(InternalFrameEvent ie) {
    refresh();
};

}

