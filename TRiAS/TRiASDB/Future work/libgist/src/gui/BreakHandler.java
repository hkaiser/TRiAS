// BreakHandler.java
// Copyright (c) 1998, Regents of the University of California
// $Header: /usr/local/devel/GiST/libgist/src/gui/BreakHandler.java,v 1.2 2000/03/15 00:23:57 mashah Exp $

/*
 * BreakHandler:
 *
 * Breakpoint handler routine. Return value indicates to libgist how to carry on.
 */

interface BreakHandler {

int CONTINUE = 0;
int STEP = 1; // stop at next break-worthy point in execution
int NEXT = 2; // stop at next entry routine (insert, fetch, remove)
int CANCEL = 3; // don't execute the entry routine that was just started

public int
breakHandler(BreakInfo info);

}
