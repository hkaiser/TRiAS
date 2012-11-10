// Breakpoint.java
// Copyright (c) 1998, Regents of the University of California
// $Header: /usr/local/devel/GiST/libgist/src/gui/Breakpoint.java,v 1.2 2000/03/15 00:23:58 mashah Exp $

import java.lang.*;
import java.io.Serializable;

/* A breakpoint contains a description of the break event that triggers it,
 * whether it's really a tracepoint and the ID of the C++ breakpoint. It's
 * declared to implement the Cloneable interface in order to enable
 * Object.clone(). Serialization takes place when the breakpoint settings are
 * saved. 
 */

class Breakpoint implements Cloneable, Serializable
{

// some instance variables are objects in order to facilitate display in a JTable
int id; // C++ ID
int event; // break event type
int nodeId; // at which node (only for NODESPLIT, ...); node = 0: not node-specific
String param1; // first event parameter (key for INSERT/REMOVE, thresh. for HIPENALTY)
String param2; // second event parameter (data for INSERT/REMOVE)

Boolean trace; // true if this is a tracepoint
Boolean enabled; // true if enabled

// for editing
boolean updated;

public Breakpoint
deepCopy()
{
    Breakpoint newBp;
    try {
	newBp = (Breakpoint) clone();
	newBp.id = id;
	newBp.event = event;
	newBp.nodeId = nodeId;
	newBp.param1 = param1;
	newBp.param2 = param2;
	return newBp;
    } catch (CloneNotSupportedException e) {
        return null;
    }
}

public String
toString()
{
    return "id: " + Integer.toString(id)
        + " trace: " + trace + " enabled: " + enabled + " updated: " + updated
	+ " event: " + event + " nodeId: " + nodeId
	+ " param1: " + param1 + " param2: " + param2;
}

}
