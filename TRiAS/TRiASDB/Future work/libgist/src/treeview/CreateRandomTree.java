// CreateRandomTree.java
// Copyright (c) 1998, Regents of the University of California
// $Id: CreateRandomTree.java,v 1.1 1999/06/21 00:34:21 marcel Exp $

import java.util.Random;

public class CreateRandomTree {

  public static Random random = new Random();


  public static Node makeTree(int levels) {

    Node root = new Node((int)(random.nextDouble()*256));

    if (levels == 0)
      return root;

    int nchild = (int)(random.nextDouble()*4) + 1;
    
    Node[] children = new Node[nchild];

    for(int i=0; i < nchild; i++)
      children[i] = makeTree(levels - 1);

    root.children = children;
    
    return root;
  }
}
