// Author: Kevin S. Van Horn (kevin.s.vanhorn@iname.com)
// This software may be freely copied and modified, under the following
// conditions:
//	 (1) The original author is identified in comments at the beginning of
//		 all source files.
//	 (2) If it has been modified from the original form, this is also noted
//		 in comments at the beginning of all source files.

#include <ospace/std/list>
#include <sys/types.h>
#include <assert.h>

#if !defined(OS_NO_NAMESPACE)
  namespace ospace
    {
    namespace std
      {
	  namespace stdex
	     {
#endif

template<class T>
class tree_node;

template<class T>
class tree_node_ch_iter;

template<class T>
class const_tree_node_ch_iter;

template<class T>
class tree_node_up_iter;

template<class T>
class const_tree_node_up_iter;

//General notes:  No storage is shared between trees.  If part of one
//tree t1 is assigned to or inserted into another tree t2, that part is either
//copied (constructors, assignment, insert) or removed from tree t1
//(assign_cut, insert_cut).

template <class T>
class vtree {
public:
	typedef vtree<T> self;
	typedef tree_node<T> node;
	typedef tree_node_ch_iter<T> ch_iter;
	typedef const_tree_node_ch_iter<T> const_ch_iter;
	typedef tree_node_up_iter<T> up_iter;
	typedef const_tree_node_up_iter<T> const_up_iter;

	vtree(); 				   // empty tree
	vtree(const vtree& t);	   // does a deep copy
	vtree(const node& x);	   // does a deep copy of subtree rooted at node
	vtree(const T& x);		   // tree with one node
	~vtree();

  vtree& operator=(const vtree& t);  // does a deep copy
  vtree& operator=(const node& x);  // does a deep copy of subtree
  vtree& operator=(const T& x);	   // tree with one node

  vtree& assign_cut(vtree& t);	  
	//Remove t's entire tree structure (setting t to empty tree) and
	//assign to this object.
  vtree& assign_cut(node& x, ch_iter p);
	//Remove subtree of node x pointed at by p, and assign it to this object.
	//REQUIRE: p points to child node of x

  node& root();
  const node& root() const;
	//Return ref to root node of tree.
	//REQUIRE: tree not empty.

  bool empty() const;			   // Test if tree is empty
  void swap(vtree& t);			   // O(1) time swap of values
  void erase(); 				   // Make tree empty

private:
  node * root_;
  void destruct(node *);
  friend class tree_node<T>;

#if !defined(OS_NO_STREAM_SUPPORT)
  friend void os_write (os_bstream& stream, const self& l);
  friend void os_read (os_bstream& stream, self& l);
#endif // OS_NO_STREAM_SUPPORT
};

template <class T>
class tree_node {
public:
  typedef tree_node_up_iter<T> up_iter;
  typedef const_tree_node_up_iter<T> const_up_iter;
  typedef tree_node_ch_iter<T> ch_iter;
  typedef const_tree_node_ch_iter<T> const_ch_iter;
  typedef tree_node<T> self;
  typedef list<self *>::size_type size_type;

  T value;

  up_iter up_begin();		 //Return iterator pointing at this node
  up_iter up_end(); 		//Return past-the-end value for ancestors
  ch_iter ch_begin();		//Return iterator pointing at first child
  ch_iter ch_end(); 		//Return past-the-end value for children

  const_up_iter up_begin() const;
  const_up_iter up_end() const;
  const_ch_iter ch_begin() const;
  const_ch_iter ch_end() const;

  void erase_child(ch_iter p);
  //Remove a child.  REQUIRE: p points to a child of this node.

  size_type num_children() const;  //Return number of children.

  ch_iter insert(ch_iter p, const vtree<T>& t);
  //Insert a copy of t as a child of this node at position p.
  //Return pointer to new child.
  //REQUIRE: !t.empty().
  //REQUIRE: p points at a child of the node or equals this->ch_end().

  ch_iter push_back(const vtree<T>& t)
	{ return insert(this->ch_end(), t); }
  ch_iter push_front(const vtree<T>& t)
	{ return insert(this->ch_begin(), t); }

  ch_iter insert(ch_iter p, const self& x);
  //Insert a copy of the subtree rooted at x as a child of this node at
  //position p.  Return a pointer to new child.
  //REQUIRE: p points at a child of the node or equals this->ch_end().

  ch_iter push_back(const self& x)
	{ return insert(this->ch_end(), x); }
  ch_iter push_front(const self& x)
	{ return insert(this->ch_begin(), x); }

  ch_iter insert(ch_iter p, const T& x);
	//Insert a single-node tree with value x as a child of this node at
	//position p.  Return a pointer to new child.
	//REQUIRE: p points at a child of the node or equals this->ch_end().
   
  ch_iter push_back(const T& x)
	{ return insert(this->ch_end(), x); }
  ch_iter push_front(const T& x)
	{ return insert(this->ch_begin(), x); }

  ch_iter insert_cut(ch_iter p, vtree<T>& t);
  //Make tree t be empty and insert its old value as a child of this
  //node at position p.  Return pointer to new child.
  //REQUIRE: !t.empty().
  //REQUIRE: p points at a child of the node or equals this->ch_end().

  ch_iter push_back_cut(vtree<T>& t)
	{ return insert_cut(this->ch_end(), t); }
  ch_iter push_front_cut(vtree<T>& t)
	{ return insert_cut(this->ch_begin(), t); }

  ch_iter insert_cut(ch_iter p, self&x, ch_iter q);
	//Remove subtree of node x pointed at by q, and insert it as a child
	//of this node at position p.  Returns pointer to new child.
	//REQUIRE: q points at a child of x.
	//REQUIRE: p points at a child of the node or equals this->ch_end().
   
  ch_iter push_back_cut(self& x, ch_iter q)
	{ return insert_cut(this->ch_end(), x, q); }
  ch_iter push_front_cut(self& x, ch_iter q)
	{ return insert_cut(this->ch_begin(), x, q); }

#if defined(OS_NO_STREAM_SUPPORT)
private:	// should be private, but streaming must access this function
#endif // OS_NO_STREAM_SUPPORT
  tree_node(void);				// for streaming purposes
  ~tree_node() { };				// users can't delete ptr to tree_node

private:

  self * parent;
  list<self *> children;

  tree_node(const T& v, self * par = 0);
  tree_node(const self& x); 			  // unimplemented
  tree_node& operator=(const self&);	  // unimplemented

  static void destruct(self * p);
  static self * copy(const self * p, self * par = 0);
  self * cut_out(ch_iter p, self * par = 0);
  bool has_ancestor(const self * p);
  friend class vtree<T>;
  friend class tree_node_ch_iter<T>;
  friend class const_tree_node_ch_iter<T>;
  friend class tree_node_up_iter<T>;
  friend class const_tree_node_up_iter<T>;

#if !defined(OS_NO_STREAM_SUPPORT)
  friend void os_write (os_bstream& stream, const self& l);
  friend void os_read (os_bstream& stream, self& l);
#endif // OS_NO_STREAM_SUPPORT
};

template <class T>
class tree_node_up_iter:
  public forward_iterator<tree_node<T>, ptrdiff_t>
{
public:
  typedef tree_node_up_iter<T> self;
  typedef tree_node<T> node;

  tree_node_up_iter();	// past-the-end iterator value
  // default copy and assign automatically generated

  self& operator++();
  self operator++(int);

  node& operator*() const;
  node * operator->() const;

  friend bool operator==(self x, self y);
  friend bool operator<(self x, self y);
  //STL templates provide !=, <=, >, >=

private:
  node * ptr;
  tree_node_up_iter(node * p);	// iterator pointing at *p
  friend class tree_node<T>;
  friend class const_tree_node_up_iter<T>;
};

template <class T>
class const_tree_node_up_iter:
  public forward_iterator<tree_node<T>, ptrdiff_t>
{
public:
  typedef const_tree_node_up_iter<T> self;
  typedef tree_node<T> node;
  typedef tree_node_up_iter<T> up_iter;

  const_tree_node_up_iter();  // past-the-end iterator value
  const_tree_node_up_iter(const up_iter&);	// conversion
  // default copy and assign automatically generated

  self& operator++();
  self operator++(int);

  const node& operator*() const;
  const node * operator->() const;

  friend bool operator==(self x, self y);
  friend bool operator<(self x, self y);
  //STL templates provide !=, <=, >, >=

private:
  const node * ptr;
  const_tree_node_up_iter(const node * p);	// iterator pointing at *p
  friend class tree_node<T>;
};

template <class T>
class tree_node_ch_iter:
   public bidirectional_iterator<tree_node<T>, ptrdiff_t>
{
public:
  typedef tree_node_ch_iter<T> self;
  typedef tree_node<T> node;

  tree_node_ch_iter();
  //generate default assignment, copy ctor

  self& operator++();
  self operator++(int);
  self& operator--();
  self operator--(int);
  node& operator*() const;
  node * operator->() const;
  friend bool operator==(self x, self y);
  friend bool operator<(self x, self y);
  //STL templates provide !=, <=, >, >=

private:
  typedef os_list_iterator<node *, int> iter_t;
//  typedef list<node *>::iterator iter_t;
//should be list<node *>::iterator, but compiler chokes on this
  iter_t it;
  tree_node_ch_iter(const iter_t& i);
  friend class tree_node<T>;
  friend class const_tree_node_ch_iter<T>;
};

template <class T>
class const_tree_node_ch_iter:
  public bidirectional_iterator<tree_node<T>, ptrdiff_t>
{
public:
  typedef const_tree_node_ch_iter<T> self;
  typedef tree_node_ch_iter<T> ch_iter;
  typedef tree_node<T> node;

  const_tree_node_ch_iter();
  const_tree_node_ch_iter(const ch_iter&);
  //generate default assignment, copy ctor

  self& operator++();
  self operator++(int);
  self& operator--();
  self operator--(int);
  const node& operator*() const;
  const node * operator->() const;
  friend bool operator==(self x, self y);
  friend bool operator<(self x, self y);
  //STL templates provide !=, <=, >, >=

private:
  typedef os_list_const_iterator<node *, ptrdiff_t> iter_t;
  //should be list<node *>::const_iterator, but compiler chokes on this
  iter_t it;
  const_tree_node_ch_iter(const iter_t& i);
  friend class tree_node<T>;
};


//tree<T> inlines

template <class T>
inline
vtree<T>::vtree()
: root_(0) { }

template <class T>
inline
vtree<T>::vtree(const self& t)
: root_(node::copy(t.root_)) { }

template <class T>
inline
vtree<T>::vtree(const node& x)
: root_(node::copy(&x)) { }

template <class T>
inline
vtree<T>::vtree(const T& x)
: root_(new node(x)) { }

template <class T>
inline
void vtree<T>::destruct(node * p)
{ tree_node<T>::destruct(p); }

template <class T>
inline
vtree<T>::~vtree()
{ destruct(root_); }

template <class T>
inline
vtree<T>& vtree<T>::operator=(const self& t)
{
  if (&t != this) {
	destruct(root_);
	root_ = node::copy(t.root_);
  }
  return *this;
}

template <class T>
inline
vtree<T>& vtree<T>::operator=(const node& x)
{
  node * tmp = root_;
  root_ = node::copy(&x);
  destruct(tmp);
  return *this;
}

template <class T>
inline
vtree<T>& vtree<T>::operator=(const T& x)
{
  node * tmp = root_;
  root_ = new node(x);
  destruct(tmp);
  return *this;
}

template <class T>
inline
vtree<T>& vtree<T>::assign_cut(self& t)
{
  if (&t != this) {
	destruct(root_);
	root_ = t.root_;
	t.root_ = 0;
	return *this;
  }
}

template <class T>
inline
vtree<T>& vtree<T>::assign_cut(node& x, ch_iter p)
{
  assert(p != x.ch_end() && p->parent == &x);
  node * tmp = x.cut_out(p);
  destruct(root_);
  root_ = tmp;
  return *this;
}

template <class T>
inline
void vtree<T>::erase()
{ destruct(root_); root_ = 0; }

template <class T>
inline
tree_node<T>& vtree<T>::root()
{ assert(root_); return *root_; }

template <class T>
inline
const tree_node<T>& vtree<T>::root() const
{ assert(root_); return *root_; }

template <class T>
inline
bool vtree<T>::empty() const
{ return root_ == 0; }

template <class T>
inline
void vtree<T>::swap(self& t)
{
  node * tmp = root_;
  root_ = t.root_;
  t.root_ = tmp;
}


//tree_node_up_iter<T> inlines

template <class T>
inline
tree_node_up_iter<T>::tree_node_up_iter()
: ptr(0) { }

template <class T>
inline
tree_node_up_iter<T>& tree_node_up_iter<T>::operator++()
{
  assert(ptr);
  ptr = ptr->parent;
  return *this;
}

template <class T>
inline
tree_node_up_iter<T> tree_node_up_iter<T>::operator++(int)
{
  assert(ptr);
  up_iter tmp = *this;
  ptr = ptr->parent;
  return tmp;
}

template <class T>
inline
tree_node<T>& tree_node_up_iter<T>::operator*() const
{ assert(ptr); return *ptr; }

template <class T>
inline
tree_node<T> * tree_node_up_iter<T>::operator->() const
{ assert(ptr); return ptr; }

template <class T>
//inline
bool operator==(tree_node_up_iter<T> x, tree_node_up_iter<T> y)
{ return x.ptr == y.ptr; }

template <class T>
inline
bool operator<(tree_node_up_iter<T> x, tree_node_up_iter<T> y)
{ return x.ptr < y.ptr; }

template <class T>
inline
tree_node_up_iter<T>::tree_node_up_iter(node * p)
: ptr(p) { }
	 

//const_tree_node_up_iter<T> inlines

template <class T>
inline
const_tree_node_up_iter<T>::const_tree_node_up_iter()
: ptr(0) { }

template <class T>
inline
const_tree_node_up_iter<T>::const_tree_node_up_iter(const up_iter& ui)
: ptr(ui.ptr) { }

template <class T>
inline
const_tree_node_up_iter<T>& const_tree_node_up_iter<T>::operator++()
{
  assert(ptr);
  ptr = ptr->parent;
  return *this;
}

template <class T>
inline
const_tree_node_up_iter<T> const_tree_node_up_iter<T>::operator++(int)
{
  assert(ptr);
  up_iter tmp = *this;
  ptr = ptr->parent;
  return tmp;
}

template <class T>
inline
const tree_node<T>& const_tree_node_up_iter<T>::operator*() const
{ assert(ptr); return *ptr; }

template <class T>
inline
const tree_node<T> * const_tree_node_up_iter<T>::operator->() const
{ assert(ptr); return ptr; }

template <class T>
//inline
bool operator==(const_tree_node_up_iter<T> x, const_tree_node_up_iter<T> y)
{ return x.ptr == y.ptr; }

template <class T>
inline
bool operator<(const_tree_node_up_iter<T> x, const_tree_node_up_iter<T> y)
{ return x.ptr < y.ptr; }

template <class T>
inline
const_tree_node_up_iter<T>::const_tree_node_up_iter(const node * p)
: ptr(p) { }
	 
   
//tree_node<T> inlines

template <class T>
inline
tree_node_up_iter<T> tree_node<T>::up_begin()
{ return up_iter(this); }

template <class T>
inline
const_tree_node_up_iter<T> tree_node<T>::up_begin() const
{ return const_up_iter(this); }

template <class T>
inline
tree_node_up_iter<T> tree_node<T>::up_end()
{ return up_iter(); }

template <class T>
inline
const_tree_node_up_iter<T> tree_node<T>::up_end() const
{ return up_iter(); }

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::ch_begin()
{ return ch_iter(children.begin()); }

template <class T>
inline
const_tree_node_ch_iter<T> tree_node<T>::ch_begin() const
{ return const_ch_iter(children.begin()); }

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::ch_end()
{ return ch_iter(children.end()); }

template <class T>
inline
const_tree_node_ch_iter<T> tree_node<T>::ch_end() const
{ return const_ch_iter(children.end()); }

template <class T>
inline
void tree_node<T>::erase_child(ch_iter p)
{
  assert(p != ch_end() && p->parent == this);
  destruct(&*p);
  children.erase(p.it);
}

template <class T>
inline
tree_node<T>::size_type tree_node<T>::num_children() const
{ return children.size(); }

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::insert(ch_iter p, const vtree<T>& t)
{
  assert(p == ch_end() || p->parent == this);
  assert(t.root_);
  return children.insert(p.it, copy(t.root_, this));
}

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::insert(ch_iter p, const self& x)
{
  assert(p == ch_end() || p->parent == this);
  return children.insert(p.it, copy(&x, this));
}

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::insert(ch_iter p, const T& x)
{
  assert(p == ch_end() || p->parent == this);
  return children.insert(p.it, new tree_node<T>(x, this));
}

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::insert_cut(ch_iter p, vtree<T>& t)
{
  assert(!t.empty());
  assert(p == ch_end() || p->parent == this);
  assert(!has_ancestor(t.root_));
  self * tmp = t.root_;
  tmp->parent = this;
  t.root_ = 0;
  return children.insert(p.it, tmp);
}

template <class T>
inline
tree_node_ch_iter<T> tree_node<T>::insert_cut(ch_iter p, self&x, ch_iter q)
{
  assert(p == ch_end() || p->parent == this);
  assert(!has_ancestor(&*q));
  if (p == q) return p;
  return children.insert(p.it, x.cut_out(q, this));
}

template <class T>
inline
tree_node<T>::tree_node(const T& v, self * par)
: parent(par), children(), value(v) { }

template <class T>
inline
tree_node<T>::tree_node(void)
: parent(NULL), children() { }

//tree_node_ch_iter<T> inlines

template <class T>
inline
tree_node_ch_iter<T>::tree_node_ch_iter()
{ }

template <class T>
inline
tree_node_ch_iter<T>& tree_node_ch_iter<T>::operator++()
{ return ++it, *this; }

template <class T>
inline
tree_node_ch_iter<T> tree_node_ch_iter<T>::operator++(int)
{ self tmp = *this; ++it; return tmp; }

template <class T>
inline
tree_node_ch_iter<T>& tree_node_ch_iter<T>::operator--()
{ return --it, *this; }

template <class T>
inline
tree_node_ch_iter<T> tree_node_ch_iter<T>::operator--(int)
{ self tmp = *this; --it; return tmp; }

template <class T>
inline
tree_node<T>& tree_node_ch_iter<T>::operator*() const
{ assert(*it); return **it; }

template <class T>
inline
tree_node<T> * tree_node_ch_iter<T>::operator->() const
{ return *it; }

template <class T>
//inline
bool operator==(tree_node_ch_iter<T> x, tree_node_ch_iter<T> y)
{ return x.it == y.it; }

template <class T>
inline
bool operator<(tree_node_ch_iter<T> x, tree_node_ch_iter<T> y)
{ return x.it < y.it; }

template <class T>
inline
tree_node_ch_iter<T>::tree_node_ch_iter(const iter_t& i)
: it(i) { }

//const_tree_node_ch_iter<T> inlines

template <class T>
inline
const_tree_node_ch_iter<T>::const_tree_node_ch_iter()
{ }

template <class T>
inline
const_tree_node_ch_iter<T>::const_tree_node_ch_iter(const ch_iter& ci)
: it(ci.it) { }

template <class T>
inline
const_tree_node_ch_iter<T>& const_tree_node_ch_iter<T>::operator++()
{ return ++it, *this; }

template <class T>
inline
const_tree_node_ch_iter<T> const_tree_node_ch_iter<T>::operator++(int)
{ self tmp = *this; ++it; return tmp; }

template <class T>
inline
const_tree_node_ch_iter<T>& const_tree_node_ch_iter<T>::operator--()
{ return --it, *this; }

template <class T>
inline
const_tree_node_ch_iter<T> const_tree_node_ch_iter<T>::operator--(int)
{ self tmp = *this; --it; return tmp; }

template <class T>
inline
const tree_node<T>& const_tree_node_ch_iter<T>::operator*() const
{ assert(*it); return **it; }

template <class T>
inline
const tree_node<T> * const_tree_node_ch_iter<T>::operator->() const
{ return *it; }

template <class T>
//inline
bool operator==(const_tree_node_ch_iter<T> x, const_tree_node_ch_iter<T> y)
{ return x.it == y.it; }

template <class T>
inline
bool operator<(const_tree_node_ch_iter<T> x, const_tree_node_ch_iter<T> y)
{ return x.it < y.it; }

template <class T>
inline
const_tree_node_ch_iter<T>::const_tree_node_ch_iter(const iter_t& i)
: it(i) { }


#if !defined(OS_NO_NAMESPACE)
	   }
    }
  }
#endif

#ifdef OS_NO_AUTO_INSTANTIATE
#include <ospace/stlex/vtree.cc>
#endif 

///////////////////////////////////////////////////////////////////////////////
// Traversieren durch diesen Baum
template<class FwIt, class pred>
bool __vtree_traverse (FwIt it, pred cb)
{
// diesen Node behandeln
	if (!cb (*it)) return false;	// nicht weitermachen

// alle SubNodes behandeln
	for (FwIt chit = it -> ch_begin(); chit != it -> ch_end(); ++chit)
	{
		if (!__vtree_traverse (chit, cb))
			return false;
	}
	return true;
}

template<class FwIt, class pred>
bool vtree_traverse (FwIt itbegin, FwIt itend, pred cb) 
{ 
	for (FwIt it = itbegin; it != itend; ++it) {
		if (!__vtree_traverse (it, cb))
			return false;
	}
	return true;
}

