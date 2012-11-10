#include <config.h>
#include <iostream>
#include "HoleSet.h"
#include "RealSet.h"

#define is_true(x) if (!(x)) abort();

bool test_holed_RealSet() {
  HoleSet<RealSet> s;
  is_true(s.support_missing())

  // Test of size(), empty() and count()

  s.contents();
  is_true(s.size() == 0);
  is_true(s.empty());
  is_true(s.dataset().size() == 0);
  is_true(s.dataset().empty());

  s.add_string("1.0");
  s.contents();
  is_true(s.size() == 1);
  is_true(!s.empty());
  is_true(s.dataset().size() == 1);
  is_true(!s.dataset().empty());
  is_true(s.as_string(0) == "1");

  s.add_string(string());
  s.contents();
  is_true(s.size() == 2);
  is_true(!s.empty());
  is_true(s.dataset().size() == 1);
  is_true(!s.dataset().empty());
  is_true(s.as_string(0) == "1");
  is_true(s.as_string(1).empty());

  s.pop_back();
  s.contents();
  is_true(s.size() == 1);
  is_true(!s.empty());
  is_true(s.dataset().size() == 1);
  is_true(!s.dataset().empty());
  is_true(s.as_string(0) == "1");

  s.pop_back();
  s.contents();
  is_true(s.size() == 0);
  is_true(s.empty());
  is_true(s.dataset().size() == 0);
  is_true(s.dataset().empty());

  // Test of resize();
  s.resize(4);
  s.contents();
  is_true(s.size() == 4);
  is_true(s.as_string(0).empty());
  is_true(s.as_string(1).empty());
  is_true(s.as_string(2).empty());
  is_true(s.as_string(3).empty());

  s.resize(2);
  s.contents();
  is_true(s.size() == 2);
  is_true(s.as_string(0).empty());
  is_true(s.as_string(1).empty());

  // Test of add_string(string);
  s.add_string("1.0");
  s.contents();
  is_true(s.size() == 3);
  is_true(s.as_string(0).empty());
  is_true(s.as_string(1).empty());
  is_true(s.as_string(2) == "1");

  s.add_string(string());
  s.contents();
  is_true(s.size() == 4);
  is_true(s.as_string(0).empty());
  is_true(s.as_string(1).empty());
  is_true(s.as_string(2) == "1");
  is_true(s.as_string(3).empty());

  s.add_string("1.0");
  s.contents();
  is_true(s.size() == 5);
  is_true(s.as_string(0).empty());
  is_true(s.as_string(1).empty());
  is_true(s.as_string(2) == "1");
  is_true(s.as_string(3).empty());
  is_true(s.as_string(4) == "1");

  // Test of add_string_at(i, string);
  s.add_string_at(0, "1.0");
  s.contents();
  is_true(s.size() == 6);
  is_true(s.as_string(0) == "1");
  is_true(s.as_string(1).empty());
  is_true(s.as_string(2).empty());
  is_true(s.as_string(3) == "1");
  is_true(s.as_string(4).empty());
  is_true(s.as_string(5) == "1");

  return true;
}

int main() {
  if (test_holed_RealSet()) {
    cout << "HoleSet<RealSet> ok" << endl;
  } else {
    cout << "HoleSet<RealSet> failed!" << endl;
  }

  return 0;
}


#if 0
  virtual void reserve(size_t N) {
  virtual void add_string(string const & str) {
  virtual void add_string_at(size_t i, string const & str) {
  virtual void set(size_t i, string const & str) {
  virtual string as_string(size_t i) const {
  virtual void remove(size_t i) {
  virtual void remove(size_t begin, size_t end) {
  virtual void clear() {
  virtual void erase(size_t i) { remove(i); }
  virtual void erase(size_t i, size_t j) { remove(i, j); }
  virtual void push_back(const string& s) { add_string(s); }
  virtual void pop_back() { if (!empty()) remove(size()-1); }
  vector<Set::value_type const *> const & data() const {
#endif
