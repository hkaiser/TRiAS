//-< PAGEPOOL.CPP >--------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:      6-Feb-98    K.A. Knizhnik  * / [] \ *
//                          Last update:  8-Feb-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Page pool implementation
//-------------------------------------------------------------------*--------*

#include "gigabase.h"

byte* dbPagePool::find(offs_t addr, int state)
{
    dbPageHeader* ph;
    assert(((int)addr & (dbPageSize-1)) == 0);
    int hashCode = (unsigned(addr) >> dbPageBits) & hashBits;
    int i, rc;
    mutex.lock();
    for (i = hashTable[hashCode]; i != 0; i = ph->collisionChain) { 
	ph = &pages[i];
	if (ph->offs == addr) { 
	    if (ph->accessCount++ == 0) {
		pages[ph->next].prev = ph->prev;
		pages[ph->prev].next = ph->next;
	    } else if (ph->state & dbPageHeader::psRaw) { 
		if (ph->wob == 0) { 
		    if (freeWobs == 0) { 
			int n = nWobs, k = n;
			dbPageEvent* newWobs = new dbPageEvent[n*2];
			freeWobs = n;
			while (--n >= 0) { 
			    newWobs[n] = wobs[n];
			    newWobs[k].open();
			    newWobs[k].next = k + 1;
			    k += 1;
			}
			newWobs[k-1].next = 0;
		    }
		    ph->wob = freeWobs;
		    freeWobs = wobs[freeWobs].next;
		    wobs[ph->wob].reset();
		    ph->state |= dbPageHeader::psWait;
		}
		wobs[ph->wob].count += 1;
		wobs[ph->wob].wait(mutex);
		if (--wobs[ph->wob].count == 0) { 
		    wobs[ph->wob].next = freeWobs;
		    freeWobs = ph->wob;
		    ph->wob = 0;
		}
	    }
	    if (!(ph->state & dbPageHeader::psDirty) &&
		(state & dbPageHeader::psDirty))
	    {
		dirtyPages[nDirtyPages] = ph;
		ph->writeQueueIndex = nDirtyPages++;
	    } 
	    ph->state |= state;
	    mutex.unlock();
	    return buffer + (i-1)*dbPageSize;
	}
    }
    i = freePages;
    if (i == 0) { 
	i = pages->prev;
	assert(((void)"unfixed page availabe", i != 0));
	ph = &pages[i];
	//printf("Throw page " INT8_FORMAT "\n", ph->offs);	    
	if (ph->state & dbPageHeader::psDirty) { 
            //printf("Write page " INT8_FORMAT "\n", ph->offs);	    
	    rc = file->write(ph->offs, buffer + (i-1)*dbPageSize, dbPageSize);
	    if (rc != dbFile::ok) { 
		db->handleError(dbDatabase::FileError, "Failed to write page",
				rc);
	    }
	    dirtyPages[ph->writeQueueIndex] = dirtyPages[--nDirtyPages];
	    dirtyPages[ph->writeQueueIndex]->writeQueueIndex = 
		ph->writeQueueIndex;
	    if (ph->offs >= fileSize) { 
		fileSize = ph->offs + dbPageSize;
	    }
	}
	unsigned h = (unsigned(ph->offs) >> dbPageBits) & hashBits;
	int* np;
	for (np = &hashTable[h]; *np != i; np = &pages[*np].collisionChain);
	*np = ph->collisionChain;
	pages[ph->next].prev = ph->prev;
	pages[ph->prev].next = ph->next;
    } else { 
	ph = &pages[i];
	freePages = ph->next;
	if (i >= nPages) { 
	    nPages = i+1;
	}
    }
    ph->accessCount = 1;
    ph->state = 0;
    ph->offs = addr;
    ph->wob = 0;
    ph->collisionChain = hashTable[hashCode];
    hashTable[hashCode] = i;
	
    if (state & dbPageHeader::psDirty) {
	dirtyPages[nDirtyPages] = ph;
	ph->writeQueueIndex = nDirtyPages++;
	ph->state |= dbPageHeader::psDirty;
    } 

    byte* p = buffer + (i-1)*dbPageSize;
    if (addr < fileSize) { 
	ph->state |= dbPageHeader::psRaw;
	mutex.unlock();
	rc = file->read(addr, p, dbPageSize);
	//printf("Read page " INT8_FORMAT "\n", addr);
	if (rc != dbFile::ok) { 
	    db->handleError(dbDatabase::FileError, "Failed to read page", rc);
	}
	mutex.lock();
	if (ph->state & dbPageHeader::psWait) { 
	    assert (ph->wob != 0);
	    wobs[ph->wob].signal();
	}
	ph->state &= ~(dbPageHeader::psWait|dbPageHeader::psRaw);
    } else { 
	memset(p, 0, dbPageSize);
    }
    mutex.unlock();
    return p;
}

void dbPagePool::copy(offs_t dst, offs_t src, size_t size)
{
    size_t dstOffs = (size_t)dst & (dbPageSize-1);
    size_t srcOffs = (size_t)src & (dbPageSize-1);
    dst -= dstOffs;
    src -= srcOffs;
    byte* dstPage = find(dst, dbPageHeader::psDirty);
    byte* srcPage = find(src, 0);
    size = (size + 3) >> 2;
    do { 
	if (dstOffs == dbPageSize) { 
	    unfix(dstPage);
	    dst += dbPageSize;
	    dstPage = find(dst, dbPageHeader::psDirty);
	    dstOffs = 0;
	}
	if (srcOffs == dbPageSize) { 
	    unfix(srcPage);
	    src += dbPageSize;
	    srcPage = find(src, 0);
	    srcOffs = 0;
	}
	*(int4*)(dstPage + dstOffs) = *(int4*)(srcPage + srcOffs);
	dstOffs += 4;
	srcOffs += 4;
    } while (--size != 0);

    unfix(dstPage);
    unfix(srcPage);
}

bool dbPagePool::open(dbFile* file, offs_t fileSize)
{
    int i;

    this->file = file;
    this->fileSize = fileSize;

    if (poolSize == 0) { // autodetect pool size
	size_t totalMem = dbFile::ramSize();
	for (poolSize = minPoolSize; 
	     poolSize*2*dbPageSize < totalMem; 
	     poolSize *= 2);
	if (long(totalMem - poolSize*dbPageSize) > long(maxUnusedMemory)) {
	    poolSize = (totalMem - maxUnusedMemory) / dbPageSize;
	}
    }

    size_t hashSize;
    for (hashSize = minHashSize; hashSize < poolSize; hashSize *= 2);
    hashTable = new int[hashSize];
    memset(hashTable, 0, sizeof(int)*hashSize);
    hashBits = hashSize-1;
    
    pages = new dbPageHeader[poolSize+1];
    pages->next = pages->prev = 0;
    for (i = poolSize+1; --i != 0;) { 
	pages[i].state = 0;
	pages[i].next = i + 1;
    }
    pages[poolSize].next = 0;
    freePages = 1;
    
    wobs = new dbPageEvent[initialWobArraySize];
    nWobs = initialWobArraySize;
    for (i = nWobs; --i != 0;) { 
	wobs[i].open();
	wobs[i].next = i + 1;
    }
    wobs[nWobs-1].next = 0;
    freeWobs = 1;

    nPages = 0;
    nDirtyPages = 0;
    dirtyPages = new dbPageHeader*[poolSize];
    
#if defined(__WATCOMC__)
    // reserve one more pages to allow access after and of page
    buffer = (byte*)dbFile::allocateBuffer((poolSize+1)*dbPageSize);
#else
    buffer = (byte*)dbFile::allocateBuffer(poolSize*dbPageSize);
#endif
    return buffer != NULL;
}


void dbPagePool::close() 
{
    delete[] wobs;
    delete[] hashTable;
    delete[] pages;
    delete[] dirtyPages;
    dbFile::deallocateBuffer(buffer);
    pages = NULL;
}

void dbPagePool::unfix(void* ptr)
{
    int i = (size_t((byte*)ptr - buffer) >> dbPageBits) + 1;
    mutex.lock();
    dbPageHeader* ph = &pages[i];
    assert(ph->accessCount > 0);
    if (--ph->accessCount == 0) { 
	ph->next = pages->next;
	ph->prev = 0;
	pages->next = pages[ph->next].prev = i;
    }
    mutex.unlock();
}

void dbPagePool::fix(void* ptr)
{
    int i = (size_t((byte*)ptr - buffer) >> dbPageBits) + 1;
    mutex.lock();
    dbPageHeader* ph = &pages[i];
    assert(ph->accessCount != 0);
    ph->accessCount += 1; 
    mutex.unlock();
}


void dbPagePool::modify(void* ptr)
{
    int i = (size_t((byte*)ptr - buffer) >> dbPageBits) + 1;
    mutex.lock();
    dbPageHeader* ph = &pages[i];
    assert(ph->accessCount != 0);
    if (!(ph->state & dbPageHeader::psDirty)) { 
	ph->state |= dbPageHeader::psDirty;
	dirtyPages[nDirtyPages] = ph;
	ph->writeQueueIndex = nDirtyPages++;
    }
    mutex.unlock();
}

static int compareOffs(void const* a, void const* b)
{
     dbPageHeader* pa = *(dbPageHeader**)a; 
     dbPageHeader* pb = *(dbPageHeader**)b;
     return pa->offs < pb->offs ? -1 : pa->offs == pb->offs ? 0 : 1;
}

void dbPagePool::flush()
{
    int rc;

    if (nDirtyPages != 0) { 
	qsort(dirtyPages, nDirtyPages, sizeof(dbPageHeader*), compareOffs);
	for (int i = 0, n = nDirtyPages; i < n; i++) { 
	    dbPageHeader* ph = dirtyPages[i];
	    assert (ph->state & dbPageHeader::psDirty);
	    //printf("Flush page " INT8_FORMAT "\n", ph->offs);	    
	    rc = file->write(ph->offs, buffer + (ph-pages-1)*dbPageSize, 
			     dbPageSize);
	    if (rc != dbFile::ok) { 
		db->handleError(dbDatabase::FileError, 
				"Failed to write page", rc);
	    }
	    ph->state &= ~dbPageHeader::psDirty;
	    if (ph->offs >= fileSize) { 
		fileSize = ph->offs + dbPageSize;
	    }
	}
	nDirtyPages = 0;
    }
    rc = file->flush();
    if (rc != dbFile::ok) { 
	db->handleError(dbDatabase::FileError, 
			"Failed to flush pages pool", rc);
    }    
}


void dbGetTie::set(dbPagePool& pool, offs_t pos)
{
    reset();
    int offs = (int)pos & (dbPageSize-1);
    byte* p = pool.get(pos - offs);
    size_t size = ((dbRecord*)(p + offs))->size;
    if (offs + size > dbPageSize) { 
	byte* dst = new byte[size];
	obj = dst;
	memcpy(dst, p + offs, dbPageSize - offs);
	pool.unfix(p);
	size -= dbPageSize - offs;
	pos += dbPageSize - offs;
	dst += dbPageSize - offs;
	while (size > dbPageSize) { 
	    p = pool.get(pos);
	    memcpy(dst, p, dbPageSize);
	    dst += dbPageSize;
	    size -= dbPageSize;
	    pos += dbPageSize;
	    pool.unfix(p);
	}
	p = pool.get(pos);
	memcpy(dst, p, size);
	pool.unfix(p);
	page = NULL;
    } else { 
	this->pool = &pool;
	page = p;
	obj = p + offs;
    }
}



void dbGetTie::reset()
{
    if (obj != NULL) { 
        if (page != NULL) { 
	    assert(!pool->destructed()); // hack: page pool should not be 
	    // destructed before any reference to the storage 
	    // (cursors, references),... 
	    pool->unfix(page);
	} else { 
	    delete[] obj;
	}
	obj = NULL;
    } 
}

void dbPutTie::set(dbPagePool& pool, offs_t pos, size_t size)
{
    reset();

    this->pool = &pool;

    int offs = (int)pos & (dbPageSize-1);
    byte* p = pool.put(pos - offs);
    if (offs + size > dbPageSize) { 
	this->size = size;
	this->pos = pos;
	byte* dst = new byte[size];
	obj = dst;
	memcpy(dst, p + offs, dbPageSize - offs);
	pool.unfix(p);
	size -= dbPageSize - offs;
	pos += dbPageSize - offs;
	dst += dbPageSize - offs;
	while (size > dbPageSize) { 
	    p = pool.get(pos);
	    memcpy(dst, p, dbPageSize);
	    dst += dbPageSize;
	    size -= dbPageSize;
	    pos += dbPageSize;
	    pool.unfix(p);
	}
	p = pool.get(pos);
	memcpy(dst, p, size);
	pool.unfix(p);
	page = NULL;
    } else { 
	page = p;
	obj = page + offs;
    }
}

void dbPutTie::reset()
{
    if (obj == NULL) { 
	return;
    }
    if (page == NULL) { 
	offs_t pos = this->pos;
	int offs = (int)pos & (dbPageSize-1);
	size_t size = this->size;
	assert(offs + size > dbPageSize);
	byte* p = pool->put(pos - offs);
	byte* src = obj;
	memcpy(p + offs, src, dbPageSize - offs);
	pool->unfix(p);
	src += dbPageSize - offs;
	size -= dbPageSize - offs;
	pos += dbPageSize - offs;
	while (size > dbPageSize) { 
	    p = pool->put(pos);
	    memcpy(p, src, dbPageSize);
	    pool->unfix(p);
	    src += dbPageSize;
	    pos += dbPageSize;
	    size -= dbPageSize;
	}
	p = pool->put(pos);
	memcpy(p, src, size);
	pool->unfix(p);
	delete[] obj;
    } else { 
	pool->unfix(page);
    }
    obj = NULL;
}







