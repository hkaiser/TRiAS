// ResourceGuard.h

#ifndef __RESOURCE_GUARD_H__
#define __RESOURCE_GUARD_H__

//USAGE sample:
//1:s
//	resource_guard<int> value(0);
//2:
//	(*value.Guard())++;	
//3:
//	*value.Guard()=*value+1;
//4:
//	{
//		resource_guard<int>::guard 
//			test(value.Guard());
//		(*test)++;
//	}
//5:
//	resource_guard<CString> value(_T("Test"));
//  (*value.Guard()).MakeUpper();

// Note: do not use operator ->() when protecting scalar datatypes (like int, long and so one).
// (this operator override is usable only for structs or classes)

#pragma warning(disable:4284 4786)

template<class T, class CS = CComObjectThreadModel::AutoCriticalSection>
struct resource_guard
{
public:
	resource_guard(const T& rt) : t(rt) {}
	resource_guard() {}
	~resource_guard() {}
	typedef resource_guard<T> _resource_t;

private:
	resource_guard(const _resource_t& rg) {throw E_FAIL;}			//to disable default copy constructor;
	_resource_t &operator=(const _resource_t& rg) {throw E_FAIL;} 	//to disable default operator=();

public:
	struct guard 
	{
		friend resource_guard<T>;
	private:
		guard(const _resource_t &resource) {
			presource=&const_cast<_resource_t &>(resource);
			presource->cs.Lock();
		};

	public:
		guard(const guard &pg) {
			presource = pg.presource;
			presource->cs.Lock();
		}

	private:
		guard&operator=(const guard &pg){throw E_FAIL;}

	public:

		~guard() {
			if (presource) 
				presource->cs.Unlock();
		}
		T &operator*() {
			if (presource) 
				return presource->t;
			return *reinterpret_cast<T*>(NULL);
		}
		T *operator->() {
			if (presource) 
				return &presource->t;
			return reinterpret_cast<T*>(NULL);
		}
		bool operator!() {return !presource;}
	private:
		_resource_t *presource;
	};

	const T& operator*() const {
		return t;
	}
	const T* operator->() const {
		return &t;
	}

	guard Guard() {return guard(*this);};

private:
	CS cs;
	T t;

	friend struct guard;
};

#endif //__RESOURCE_GUARD_H__

