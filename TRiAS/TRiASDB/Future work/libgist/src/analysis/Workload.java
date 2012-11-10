// Workload.java
// Copyright (c) 1998, Regents of the University of California
// $Id: Workload.java,v 1.1 1999/06/21 00:33:23 marcel Exp $

/*
 * Workload - 
 * Contains the Java-specific part of a workload (pretty much nothing).
 */

import java.io.Serializable;
import java.util.Vector;

public class Workload implements Serializable
{

String filename; // where to store the workload
Vector queries; // vector of query clauses
Vector limits; // vector of retrieval limits (as Strings)

public
Workload(String f)
{
    filename = f;
    queries = new Vector();
    limits = new Vector();
}

}
