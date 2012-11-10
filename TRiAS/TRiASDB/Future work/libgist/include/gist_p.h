// gist_p.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_p.h,v 1.15 1999/06/20 21:13:20 marcel Exp $


#ifndef GIST_P_H
#define GIST_P_H

#ifdef __GNUG__
#pragma interface "gist_p.h"
#endif

#include "gist_defs.h"		// for shpid_t
#include "vec_t.h"		// for cvec_t
#include "gist_file.h"		// for gist_file::page_descr

class gist;

/*
 * Basic page structure for all pages.
 */
struct page_s {
    struct slot_t {
	int2 offset;		// -1 if vacant
	uint2 length;
    };

    class space_t {
    public:
	space_t()	{};
	~space_t()	{};

	void init(int);
	int nfree() const;
	
	int			usable();
				// slot_bytes means bytes for new slots
	rc_t			acquire(int amt, int slot_bytes);
	void 			release(int amt);

    private:
   
	void _check_reserve();
	
	int2	_nfree;		// free space counter
    };

    enum {
	data_sz = (SM_PAGESIZE 
		   - sizeof(shpid_t)
		   - sizeof(space_t)
		   - 3 * sizeof(int2)
		   - 1 * sizeof(int4)
		   - 2 * sizeof(slot_t)
		   - 2 * sizeof(int2)),
	max_slot = data_sz / sizeof(slot_t) + 2
    };

    shpid_t	pid;			// id of the page
    space_t 	space;			// space management
    uint2	end;			// offset to end of data area
    int2	nslots;			// number of slots
    int2	nvacant;		// number of vacant slots
    int4	fill1;			// make header multiple of 8 bytes
    char 	data[data_sz];		// must be aligned
    slot_t	reserved_slot[1];	// 2nd slot (declared to align
					// end of _data)
    slot_t	slot[1];		// 1st slot
};

class keyrec_t {
public:

    // note that a union for elen and child won't save any
    // space, because 'child' needs to be 4-byte aligned
    struct hdr_s {
	uint2	klen;
	uint2	elen;
	shpid_t	child;
    };

    const char* key() const;
    const char* elem() const;
    const char* sep() const;
    smsize_t klen() const; // key length
    smsize_t elen() const; // element length
    smsize_t slen() const; // key + element length
    smsize_t rlen() const; // full tuple length
    shpid_t child() const;
    
private:
    hdr_s 	_hdr;
    char*	_body()	const;
};


struct gistctrl_t {
    shpid_t	root;
    int2	level;	// leaf if 1, non-leaf if > 1

    gistctrl_t();
};



class gist_p {
public:
    
    typedef page_s::slot_t slot_t;

    enum {
	data_sz = page_s::data_sz,
	max_slot = data_sz / sizeof(slot_t) + 2
    };

    enum {
	max_tup_sz = data_sz / 2 - sizeof(slot_t) - sizeof(keyrec_t),
	    // 2 entries minimum
	max_scnt = (data_sz - sizeof(gistctrl_t)) / 
	    (sizeof(keyrec_t) + sizeof(slot_t)) + 1
	    // max # of slots on a page
    };

    gist_p();
    ~gist_p();

    rc_t 			format(
	const shpid_t 		    pid,
	const gistctrl_t	    *hdr);

    rc_t			insert(
        const keyrec_t		    &tup);

    rc_t			copy(gist_p& rsib);

    rc_t			set_hdr(const gistctrl_t& new_hdr);
    void			set_level(int2 level);
    int 			level() const;
    shpid_t			root() const;

    bool 			is_leaf() const;
    bool 			is_node() const;
    bool			is_root() const;

    
    const keyrec_t& 		rec(int idx) const;
    int 			rec_size(int idx) const;
    int 			nrecs() const;

    // compute size of record, storing given key and data lengths
    static int			rec_size(size_t klen, size_t dlen);

    // the slot index is automatically corrected if a BP is present on the page
    rc_t			insert(
	const cvec_t& 		    key, 
	const cvec_t& 		    el, 
	int 			    slot, 
	shpid_t 		    child = 0);
    rc_t			remove(int slot);

    bool 			is_fixed() const;
    gist_p& 			operator=(const gist_p& p);
    smsize_t			usable_space();
    shpid_t 			pid() const;

private:
    static const int _HDR_CORRECTION;
        // = 1: add to slot indices to compensate for hdr entry

    rc_t			_insert_expand(
	int 			    idx,
	int 			    cnt, 
	const cvec_t 		    tp[]);
    
    rc_t			_remove_compress(int idx, int cnt);
    rc_t			_overwrite(
	int 			    idx,
	int 			    start,
	const cvec_t& 		    data);

    // state
    page_s*                     _pp;
    gist_file::page_descr*	_descr;

    friend class gist;
    // what I really meant was:
    //friend rc_t gist::_fix_page(gist_p &page, shpid_t pageNo);
    //friend rc_t gist::_unfix_page(gist_p &page);

    void			_compress(int idx = -1);

    // formerly from page_p
    inline smsize_t		_used_space();
    smsize_t			_contig_space();
    
    smsize_t 			_tuple_size(int idx) const;
    void* 			_tuple_addr(int idx) const;
    inline bool 		_is_tuple_valid(int idx) const;
    const void* 		_get_hdr() const;


};

inline smsize_t 
gist_p::_used_space()
{
    return (data_sz + 2 * sizeof(slot_t) - _pp->space.usable()); 
}

inline bool
gist_p::_is_tuple_valid(int idx) const
{
    return idx >= 0 && idx < _pp->nslots && _pp->slot[-idx].offset >=0;
}

inline shpid_t
gist_p::root() const
{
    gistctrl_t* hdr = (gistctrl_t *) _get_hdr();
    return hdr->root;
}

inline int
gist_p::rec_size(size_t klen, size_t dlen)
{
    return int(align(klen + dlen + sizeof(keyrec_t::hdr_s)) + sizeof(slot_t));
}

#endif /*GIST_P_H*/
