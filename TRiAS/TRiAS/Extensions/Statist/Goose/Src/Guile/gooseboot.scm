;; $Id: gooseboot.scm,v 1.4 1999/05/17 23:52:14 hp Exp $

;; gooseboot: load all of the other auxilliary code for our smobs

(for-each (lambda (x)
	    (load (string-append %goose-prefix "/share/guile/goose/" x ".scm")))
	  (list "Random_smob"
		"RealSet_smob"
	   ))
		  

;; $Id: gooseboot.scm,v 1.4 1999/05/17 23:52:14 hp Exp $