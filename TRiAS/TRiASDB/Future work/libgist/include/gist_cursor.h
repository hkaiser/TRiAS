// gist_cursor.h						-*- c++ -*-
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_cursor.h,v 1.14 1999/07/01 19:32:40 marcel Exp $


#ifndef GIST_CURSOR_H
#define GIST_CURSOR_H

#ifdef __GNUG__
#pragma interface "gist_cursor.h"
#endif

#include "gist_defs.h"		// for shpid_t
#include "gist_ext.h"		// for gist_penalty_t

#include <vector>
#include <stack>
#include <queue>
#include <functional>

/*
 * gist_lstk_entry (lookup stack entry)
 *
 * Either records a leaf item to be returned or a child page ID to be followed.
 * An entry for a child page ID also contains a pointer to the parent entry.
 */

class gist_lstk_entry {
public:
    enum eType { // type of stack entry
	eIllegal = 0, // shouldn't be used
        eNode, // internal node
	eItem // leaf item
    };

    ~gist_lstk_entry();
    gist_lstk_entry &operator=(const gist_lstk_entry &e);

    eType typ;
    union {
	// note that all 'key'/'data' values are copied by the
	// constructor and automatically freed by the destructor.
        struct {
	    shpid_t page; // this node's ID
#ifdef AMDB
	    shpid_t parent; // parent's ID
#endif // AMDB
	    // these are never used unless we're storing the predicate
	    // in a priority queue (to be used for some computation).
	    void* key; // ptr to key
	    smsize_t klen; // length of key in bytes
	} node; // for eNode
	struct {
	    void* key; // ptr to key
	    smsize_t klen; // length of key in bytes
	    void* data; // ptr to data
	    smsize_t dlen; // length of data in bytes
	    shpid_t page; // which leaf it was from
	    int idx; // which index on the leaf
	} item; // for eItem
    } val;

    // constructor for empty entry
    gist_lstk_entry() : typ(eIllegal) {}
    // constructor for internal node entry
    gist_lstk_entry(shpid_t page, shpid_t parent);
    // constructor for item entry, makes copy of key and data
    gist_lstk_entry(void* key, smsize_t klen, void* data, smsize_t dlen,
        shpid_t page, int idx);
};


/*
 * gist_prioq_entry (priority queue entry)
 *
 * Entries in a priority queue contain a 'penalty' (= distance to query) 
 * that determines their position in the queue.
 */

class gist_prioq_entry : public gist_lstk_entry {
public:

    gist_penalty_t penalty;

    // constructor for empty entry
    gist_prioq_entry() {}
    // constructor for node-type entry
    gist_prioq_entry(
	shpid_t page,
	shpid_t parent,
	const gist_penalty_t& p,
	const void* key = NULL,
	smsize_t klen = 0);
    // constructor for item-type entry
    gist_prioq_entry(void* key,
	smsize_t klen,
	void* data,
	smsize_t dlen,
        shpid_t page,
	int idx,
	const gist_penalty_t& p);

    // deletes key and data, if item-type entry
    ~gist_prioq_entry();

};


/*
 * gist_lstk (lookup stack)
 *
 * Contains entries for all the nodes/subtrees that have yet to be traversed and 
 * all of the items from the most recently visited leaf. 
 */

class gist_lstk {
private:
    enum { // MSVC 5.0 doesn't allow "const int ..." here
        lstk_chunk = 50
    };

    int2 _top;
    gist_lstk_entry _stk[lstk_chunk];
    gist_lstk_entry *_indirect[lstk_chunk];
    gist_lstk_entry* _push(
        gist_lstk_entry::eType	typ,
	shpid_t 		pid,
	shpid_t 		parent,
	void*			key,
	smsize_t		klen,
	void* 			data,
	smsize_t		dlen,
	int			idx);

public:	
    gist_lstk();
    ~gist_lstk();

    // push a node-type entry on the and return a pointer to it
    void push(
	shpid_t			pid,
	shpid_t			parent);

    // push an item-type entry on the stack, making copies of the key and data
    void push(
        void*		key,
	smsize_t	klen,
	void*		data,
	smsize_t	dlen,
        shpid_t		page,
	int		idx);

    // caller is reponsible for deallocating key and data 
    void pop(
        gist_lstk_entry&	e);

    void reset();
    bool is_full();
    bool is_empty();
};

class gist_prioq_t {

private:

    // '<' operator, STL style. We actually want them items to be sorted in order of 
    // increasing, not decreasing penalty, hence "<" is implemented as ">".
    // The template instantiation facility is not needed here.
    struct less_prioq_entry :
        std::binary_function<gist_prioq_entry *, gist_prioq_entry *, bool> {

	bool operator()(const gist_prioq_entry* x, const gist_prioq_entry* y) {
	    return x->penalty > y->penalty;
	}
    };
    less_prioq_entry comp;

    typedef std::vector<gist_prioq_entry *> Queue;

    Queue* queue;

public:

    gist_prioq_t();
    ~gist_prioq_t();
  
    bool empty() { return queue->empty(); }
    void push(gist_prioq_entry* e);
    void pop(gist_prioq_entry* e);
    void reset();

};

class gist_cursorext_t;

class gist_cursor_t {
public: 
    gist_cursor_t()
	: k(0), io(0), query(NULL), ext(NULL), cext(NULL),
	  iter(NULL), state(NULL) {}
    ~gist_cursor_t() {}
    
    void reset();

    int k;	// # of tuples yet to be retrieved
    int io;	// # of pages fetched

    const gist_query_t* query;
    gist_ext_t* ext;
    gist_cursorext_t* cext;
    void* iter;		// e.g., stack or queue
    void* state;	// computation state
};

#endif
