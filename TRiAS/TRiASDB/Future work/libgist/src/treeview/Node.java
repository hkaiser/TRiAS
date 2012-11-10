// Node.java
// Copyright (c) 1998, Regents of the University of California
// $Id: Node.java,v 1.1 1999/06/21 00:34:22 marcel Exp $

import java.util.Vector;

public class Node {

public int stat;
public int childnum;
public Node[] children;
public int nodenum;
public int nonce;
public boolean open, onpath;
public NodeDump nDump;
public NodeView nView;

public NodeView topViews[]; // views that this node appears as top level
public Vector nViews;  // views that this node appears in.

public Node(int nodenum, int nonce) {
    stat = (nodenum) % 256;
    this.nodenum = nodenum;
    this.nonce   = nonce;
    onpath = false;
    childnum = -1;
    children = null;
    nDump = null;
    open = false;
    nViews = new Vector();
    topViews = new NodeView[Libgist.getLevel(nodenum)];
}

public void setChildren(Node[] children) {
    
    this.children = children;
}

public Node[] getChildren() {

    if (children != null)
	return children;

    // DbgOutput(1,"IN getChildren \n");
    
    int[] childnos;

    try {
	childnos = new int[Libgist.maxChildren()];
    } catch (Exception e) {
	System.out.println(e);
	return null;
    }

    try {
	// DbgOutput(1,"Nodenum: " + nodenum);
	childnum = Libgist.getChildren(nodenum,childnos);
    } catch (Exception e) {
	System.out.println(e);
	return null;
    }

    children = new Node[childnum];
    
    // DbgOutput(1,"GOT: " + childnum);

    try {
	for(int i=0; i < childnum; i++)
	    children[i] = new Node(childnos[i], Libgist.getNonce(childnos[i]));
    } catch (Exception e) {
	System.out.println(e);
	return null;
    }
    
    return children;
}

}
