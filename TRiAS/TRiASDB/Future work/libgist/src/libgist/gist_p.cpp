// gist_p.cc
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_p.cc,v 1.11 1999/06/16 03:07:26 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_p.h"
#endif

#include "gist_defs.h"

#include "gist_p.h"

const int gist_p::_HDR_CORRECTION = 1;


/////////////////////////////////////////////////////////////////////////
// gistctrl_t - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

gistctrl_t::gistctrl_t()
{
}


/////////////////////////////////////////////////////////////////////////
// gist_p::format - format page
//
// Description:
// 	- overwrite memory and put header in slot 0
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t 		
gist_p::format(
    const shpid_t 	    pid,
    const gistctrl_t	    *hdr)
{
    (void) memset(_pp, '\017', sizeof(*_pp)); // trash the whole page

    _pp->pid = pid;
    _pp->space.init((int) (data_sz + 2*sizeof(slot_t)));
    _pp->end = _pp->nslots = _pp->nvacant = 0;
    cvec_t hdrV((void *) hdr, sizeof(*hdr));
    _insert_expand(0, 1, &hdrV);
    this->_descr->isDirty = true;

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::insert - insert keyrec_t on page
//
// Description:
//	- assemble key and data and call insert(key, el, slot, child)
//
// Return Values:
//      RCOK
//	eRECWONTFIT
/////////////////////////////////////////////////////////////////////////

rc_t		
gist_p::insert(const keyrec_t &tup)
{
    cvec_t key(tup.key(), tup.klen());
    cvec_t data(tup.elem(), tup.elen());
    shpid_t child = tup.child();
    return (insert(key, data, nrecs(), child));
}


/////////////////////////////////////////////////////////////////////////
// gist_p::insert - insert entry on page
//
// Description:
//	- assemble cvec_t (out of header, key and data) and call 
//	  _insert_expand()
//
// Return Values:
//      RCOK
//	eRECWONTFIT
/////////////////////////////////////////////////////////////////////////

rc_t	
gist_p::insert(
    const cvec_t& 	    key, 
    const cvec_t& 	    el, 
    int 		    slot, 
    shpid_t 		    child)
{
    keyrec_t::hdr_s hdr;
    hdr.klen = key.size();
    hdr.elen = el.size();
    hdr.child = child;
    cvec_t v(&hdr, sizeof(hdr));
    v.put(key);
    v.put(el);
    W_DO(_insert_expand(slot + _HDR_CORRECTION, 1, &v));
    this->_descr->isDirty = true;
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::is_root - return true if page is root
//
// Description:
//
// Return Values:
//      true/false
/////////////////////////////////////////////////////////////////////////

bool
gist_p::is_root() const
{
    gistctrl_t *hdr = (gistctrl_t *) _get_hdr();
    return (_pp->pid ==  hdr->root);
}


/////////////////////////////////////////////////////////////////////////
// gist_p::remove - remove entry from page
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t		
gist_p::remove(int slot)
{
    W_DO(_remove_compress(slot + _HDR_CORRECTION, 1));
    this->_descr->isDirty = true;
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::copy - copy this page
//
// Description:
//	- don't copy header
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t		
gist_p::copy(gist_p& rsib)
{
    // Copy the page content

    int n = nrecs(); // # of entries, excluding hdr
    cvec_t* tp = new cvec_t[n];
    assert(tp);
    
    for (int i = 0; i < n; i++) {
	tp[i].put(_tuple_addr(i + _HDR_CORRECTION), _tuple_size(i + _HDR_CORRECTION));
    }

    // Insert all of tp into slot 1 of rsib (slot 0 reserved for header).
    rc_t rc = rsib._insert_expand(1, n, tp);
    delete[] tp;
    this->_descr->isDirty = true;
    rsib._descr->isDirty = true;
    return rc;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::set_hdr - set page header
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t	
gist_p::set_hdr(const gistctrl_t& new_hdr)
{
    cvec_t hdrv(&new_hdr, sizeof(new_hdr));
    W_DO(_overwrite(0, 0, hdrv));
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::set_level - set page level
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
gist_p::set_level(int2 level)
{
    gistctrl_t *hdr = (gistctrl_t *) _get_hdr();
    hdr->level = level;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::is_leaf - return true if page is leaf
//
// Description:
//
// Return Values:
//      true/false
/////////////////////////////////////////////////////////////////////////

bool 		
gist_p::is_leaf() const
{
    return level() == 1;
}


/////////////////////////////////////////////////////////////////////////
// gist_p::is_node - return true if page is interior node
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

bool 	
gist_p::is_node() const
{
    return !is_leaf();
}


/////////////////////////////////////////////////////////////////////////
// gist_p::level - return page level
//
// Description:
//
// Return Values:
//      level
/////////////////////////////////////////////////////////////////////////

int 		
gist_p::level() const
{
    gistctrl_t *hdr = (gistctrl_t *) _get_hdr();
    return hdr->level;
}
    

int
gist_p::rec_size(int idx) const
{
    return _tuple_size(idx + _HDR_CORRECTION);
}

int 
gist_p::nrecs() const
{
    return _pp->nslots - _HDR_CORRECTION;
}


const keyrec_t& 
gist_p::rec(int idx) const
{
    return * (keyrec_t*) _tuple_addr(idx + _HDR_CORRECTION);
}

gist_p::~gist_p()
{
}

gist_p::gist_p() : _pp(0), _descr(NULL)
{
}

const void* 	
gist_p::_get_hdr() const
{
    return _tuple_addr(0);
}

int
page_s::space_t::nfree() const
{
    return _nfree;
}

int
page_s::space_t::usable()
{
    return _nfree;
}

rc_t		
page_s::space_t::acquire(int amt, int slot_bytes)
{
    int avail = usable();
    int total = amt + slot_bytes;

    if (avail < total)  {
	return eRECWONTFIT;
    }
    
    //  Consume the space
    assert(_nfree >= total);
    _nfree -= total;
    return RCOK;
}

void 		
page_s::space_t::release(int amt)
{
    _nfree += amt;
}

shpid_t
gist_p::pid() const
{
    return _pp->pid;
}

smsize_t
gist_p::usable_space()
{
    return _pp->space.usable(); 
}

gist_p& 		
gist_p::operator=(const gist_p& p)
{
    _pp = p._pp;
    _descr = p._descr;
    return *this;
}

rc_t		
gist_p::_insert_expand(
    int 			    idx,
    int 			    cnt, 
    const cvec_t 		    vec[])
{
    assert(idx >= 0 && idx <= _pp->nslots);
    assert(cnt > 0);

    //  Compute the total # bytes needed 
    uint4 total = 0;
    int i;
    for (i = 0; i < cnt; i++)  {
	total += int(align(vec[i].size()) + sizeof(slot_t));
    }

    //  Try to get the space ... could fail with eRECWONTFIT
    W_DO(_pp->space.acquire(total, 0));

    if (_contig_space() < total)  {
	_compress();
	assert(_contig_space() >= total);
    }

    if (idx != _pp->nslots)    {
	//  Shift left neighbor slots further to the left
	memcpy(&_pp->slot[-(_pp->nslots + cnt - 1)],
	       &_pp->slot[-(_pp->nslots - 1)], 
	       (_pp->nslots - idx) * sizeof(slot_t));
    }

    //  Fill up the slots and data
    register slot_t* p = &_pp->slot[-idx];
    for (i = 0; i < cnt; i++, p--)  {
	p->offset = _pp->end;
	p->length = vec[i].copy_to(_pp->data + p->offset);
	_pp->end += int(align(p->length));
    }

    _pp->nslots += cnt;
    
    return RCOK;
}
    
rc_t		
gist_p::_remove_compress(int idx, int cnt)
{
    assert(idx >= 0 && idx < _pp->nslots);
    assert(cnt > 0 && cnt + idx <= _pp->nslots);

    //	Compute space space occupied by tuples
    register slot_t* p = &_pp->slot[-idx];
    register slot_t* q = &_pp->slot[-(idx + cnt)];
    int amt_freed = 0;
    for ( ; p != q; p--)  {
	assert(p->length < gist_p::max_tup_sz);
	amt_freed += int(align(p->length) + sizeof(slot_t));
    }

    //	Compress slot array
    p = &_pp->slot[-idx];
    q = &_pp->slot[-(idx + cnt)];
    for (slot_t* e = &_pp->slot[-_pp->nslots]; q != e; p--, q--) {
	*p = *q;
    }
    _pp->nslots -= cnt;

    //  Free space occupied
    _pp->space.release(amt_freed);

    return RCOK;
}

rc_t		
gist_p::_overwrite(
    int 			    idx,
    int 			    start,
    const cvec_t& 		    vec)
{
    int vecsz = vec.size();
    assert(idx >= 0 && idx < _pp->nslots);
    assert(start >= 0 && vecsz >= 0);

    slot_t& s = _pp->slot[-idx];		// slot in question
    assert(start + vecsz <= s.length);

    //  Put data into the slot
    char* p = _pp->data + s.offset;
    if (vecsz > 0)  {
	assert((int)(s.offset + start + vec.size() <= data_sz));
	// make sure the slot table isn't getting overrun
	assert((char *)(p + start + vec.size()) <= (char *)&_pp->slot[-(_pp->nslots-1)]);
		
	vec.copy_to(p + start);
    }
    return RCOK;
}

void		
gist_p::_compress(int idx)
{

    assert(idx < 0 || idx < _pp->nslots);
    
    //  Copy data area over to scratch
    static char scratch[sizeof(_pp->data)];
    memcpy(&scratch, _pp->data, sizeof(_pp->data));

    //  Move data back without leaving holes
    register char* p = _pp->data;
    int nslots = _pp->nslots;
    int i;
    for (i = 0; i < nslots; i++) {
	if (i == idx)  continue; 	// ignore this slot for now
	slot_t& s = _pp->slot[-i];
	if (s.offset != -1)  {
	    assert(s.offset >= 0);
	    memcpy(p, scratch+s.offset, s.length);
	    s.offset = p - _pp->data;
	    p += align(s.length);
	}
    }

    //  Move specified slot
    if (idx >= 0)  {
	slot_t& s = _pp->slot[-idx];
	if (s.offset != -1) {
	    assert(s.offset >= 0);
	    memcpy(p, scratch + s.offset, s.length);
	    s.offset = p - _pp->data;
	    p += align(s.length);
	}
    }

    _pp->end = p - _pp->data;

    //  Page is now compressed with a hole after _pp->end.
}

void*
gist_p::_tuple_addr(int idx) const
{
    assert(idx >= 0 && idx < _pp->nslots);
    return (void*) (_pp->data + _pp->slot[-idx].offset);
}

smsize_t
gist_p::_tuple_size(int idx) const
{
    assert(idx >= 0 && idx < _pp->nslots);
    return _pp->slot[-idx].length;
}

void
page_s::space_t::init(int nfree) 
{ 
    _nfree = nfree;
}

smsize_t
gist_p::_contig_space()	
{ 
    return ((char*) &_pp->slot[-(_pp->nslots-1)]) - (_pp->data + _pp->end); 
}

const char*
keyrec_t::key() const
{
    return _body();
}

const char* 
keyrec_t::elem() const
{
    return _body() + _hdr.klen;
}

const char*
keyrec_t::sep() const
{
    return _body();
}

smsize_t
keyrec_t::klen() const 
{
    return _hdr.klen;
}

smsize_t 
keyrec_t::elen() const
{
    return _hdr.elen;
}

smsize_t 
keyrec_t::slen() const
{
    return _hdr.klen + _hdr.elen;
}

smsize_t
keyrec_t::rlen() const
{
    return _body() + slen() - (char*) this;
}

shpid_t
keyrec_t::child() const
{
    return _hdr.child;
}

bool
gist_p::is_fixed() const
{
    return _pp != 0;
}

char*
keyrec_t::_body() const
{
    return ((char*) &_hdr) + sizeof(_hdr);
}
