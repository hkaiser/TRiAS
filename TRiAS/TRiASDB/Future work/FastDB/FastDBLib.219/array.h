//-< ARRAY.H >-------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 20-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Array type for table record fields
//-------------------------------------------------------------------*--------*

#ifndef __ARRAY_H__
#define __ARRAY_H__

class dbAnyArray { 
  protected:
    size_t len;
  public:
    size_t length() const { return len; }
    void const* base() const { return *(void**)(this+1); }
};    

template<class T>
class dbArray : public dbAnyArray { 
  protected:
    T*     data;
    size_t allocated;
    
    static void arrayAllocator(dbAnyArray* aArray, void* data, size_t length)
    {
	dbArray* array = (dbArray*)aArray;
	array->len = length;
	if (array->allocated) { 
	    delete[] array->data;
	}
	if (data != NULL || length == 0) { 
	    array->data = (T*)data;
	    array->allocated = 0;
	} else { 
	    array->data = new T[length];
	    array->allocated = length;
	}
    }

  public:
    dbFieldDescriptor* dbDescribeComponents(dbFieldDescriptor* fd) { 
	fd->type = dbField::tpArray;
	fd->dbsSize = sizeof(dbVarying);
	fd->alignment = 4;
	fd->arrayAllocator = arrayAllocator;
	return dbDescribeField(new dbFieldDescriptor("[]", 0, sizeof(T), 0),
			       *(T*)fd); 
    }

    dbArray() { 
	data = NULL; 
	len = 0;
	allocated = 0;
    }

    dbArray(size_t size) { 
	if (size != 0) { 
	    data = new T[size]; 
	}
	len = size;
	allocated = size;
    }

    dbArray(T const* ptr, size_t size, size_t allocate = 0) { 
	len = size;
	allocated = allocate;
	if (allocate != 0) { 
	    assert(allocate >= size);
	    data = new T[allocate];
	    memcpy(data, ptr, sizeof(T)*size);	
	} else { 
	    data = (T*)ptr;
	}
    }

    dbArray(dbArray const& arr) { // copy constructor 
	allocated = arr.allocated;
	len = arr.len;
	if (allocated) { 
	    data = new T[allocated];
	    memcpy(data, arr.data, sizeof(T)*len);	
	} else { 
	    data = arr.data;
	}
    }

    ~dbArray() { 
	if (allocated) { 
	    delete[] data;
	}
    }

    dbArray& operator = (dbArray const& arr) { 
	if (this == &arr) { 
	    return *this;
	}
	if (allocated) { 
	    delete[] data;
	}
	if ((len = arr.len) != 0) { 
	    data = new T[len];
	    memcpy(data, arr.data, sizeof(T)*len);
	}
	allocated = len;
	return *this;
    }

    T const& last() {
	assert(len > 0);
	return data[len-1];
    }

    void assign(T const* ptr, size_t size, bool copy = true) { 
	if (allocated) { 
	    delete[] data;
	}
	len = size;
	if (copy && size != 0) { 
	    data = new T[size];
	    memcpy(data, ptr, sizeof(T)*size);	
	    allocated = size;
	} else { 
	    data = (T*)ptr;
	    allocated = 0;
	}
    }

    T const& operator [](size_t index) const { 
	assert(index < len);
	return data[index];
    }

    void putat(size_t index, T const& value) { 
	assert(index < len);
	if (!allocated) { 
	    T* copy = new T[len];
	    memcpy(copy, data, sizeof(T)*len);
	    data = copy;
	    allocated = len;
	}
	data[index] = value;
    }

    T const& getat(size_t index) const {
	assert(index < len);
	return data[index];
    }

    void clear() { 
        if (allocated) {
            delete[] data;
        }
	data = NULL;
	len = 0;
	allocated = 0;
    }

    void resize(size_t size) { 
	if (size > len && size > allocated) { 
	    T* p = new T[size];
	    memcpy(p, data, sizeof(T)*len);
	    if (allocated) { 
		delete[] data;
	    }
	    data = p;
	    allocated = size;
	}
	len = size;
    }

    void append(T const& value) { 
        insert(value, len);
    }

    void insert(T const& value, size_t index = 0) { 
	assert(index <= len);
	if (len >= allocated) {
	    size_t newSize = len == 0 ? 8 : len*2;
	    T* p = new T[newSize];
	    memcpy(p, data, index*sizeof(T));
	    p[index] = value;
	    memcpy(p+index+1, data+index, (len-index)*sizeof(T));
	    if (allocated) { 
		delete[] data;
	    }
	    data = p;
	    allocated = newSize;
	} else { 
	    memmove(data+index+1, data+index, (len-index)*sizeof(T));
	    data[index] = value;
	}
	len += 1;
    }
    
    void remove(size_t index) { 
	assert(index < len);
	len -= 1;
	if (index != len && !allocated) { 
	    T* p = new T[len];
	    memcpy(p, data, index*sizeof(T));
	    memcpy(p+index, data+index+1, (len-index)*sizeof(T));
	    allocated = len;
	    data = p;
	} else { 
	    memmove(data+index, data+index+1, (len-index)*sizeof(T));
	}
    }
    
    T const* get() const { return data; }
};

template<class T>
int index(dbArray<T> const& a, T value) { 
    for (int i = 0, n = a.length(); i < n; i++) { 
      if (a[i] == value) { 
          return i;
      }
    }
    return -1;
}
    
template<class T>
int rindex(dbArray<T> const& a, T value) { 
    int i = a.length(); 
    while (--i >= 0 && a[i] != value);
    return i;
}

#endif

