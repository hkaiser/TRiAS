// Author: Kevin S. Van Horn (kevin.s.vanhorn@iname.com)
// This software may be freely copied and modified, under the following
// conditions:
//	 (1) The original author is identified in comments at the beginning of
//		 all source files.
//	 (2) If it has been modified from the original form, this is also noted
//		 in comments at the beginning of all source files.

#if !defined(OS_NO_NAMESPACE)
  namespace ospace
    {
    namespace std
      {
	  namespace stdex
	     {
#endif

template <class T>
void tree_node<T>::destruct(self * p)
{
  if (!p) return;
  ch_iter i;
  for (i = p->ch_begin(); !(i == p->ch_end()); ++i)
	destruct(&*i), delete &*i;
}

template <class T>
tree_node<T> *
tree_node<T>::copy(const self * p, self * par)
{
  if (!p) return 0;
  self * res = new self(p->value, par);
  list<self *>::const_iterator i, iend = p->children.end();
  for (i = p->children.begin(); i != iend; ++i)
	res->children.push_back(copy(*i, res));
  return res;
}

template <class T>
tree_node<T> *
tree_node<T>::cut_out(ch_iter p, self * par) {
  assert(!(p == ch_end()) && p->parent == this);
  self * res = &*p;
  children.erase(p.it);
  res->parent = par;
  return res;
}

template <class T>
bool tree_node<T>::has_ancestor(const self * p)
{
  const self * q = this;
  while (q)
	if (q == p)
	  return true;
	else
	  q = q->parent;
  return false;
}

#if !defined(OS_NO_NAMESPACE)
	   }
    }
  }
#endif
