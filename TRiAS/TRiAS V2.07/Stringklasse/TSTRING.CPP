// test <string>
#include <assert.h>
#include <string.h>
#include <string.hpp>
#include <iostream.h>

int main()
{
string s1, s2(30, reserve), s3(4, default_size);
string s4("s4"), s5("s5xxx", 2), s6('a', 3);
string s7((unsigned char)'b', 5), s8('c');

	s1.reserve(20);
	
	assert(s1.reserve() == 20 && s2.reserve() == 30);
	assert(strcmp(s1.c_str(), "") == 0);
	assert(strcmp(s2.c_str(), "") == 0);
	assert(memcmp(s3.c_str(), "\0\0\0\0", 5) == 0);
	assert(strcmp(s4.c_str(), "s4") == 0);
	assert(strcmp(s5.c_str(), "s5") == 0);
	assert(strcmp(s6.c_str(), "aaa") == 0);
	assert(strcmp(s7.c_str(), "bbbbb") == 0);
	assert(strcmp(s8.c_str(), "c") == 0);

// test assignments
	s1 = "hello", assert(strcmp(s1.c_str(), "hello") == 0);	
	s1 = 'x', assert (strcmp(s1.c_str(), "x") == 0);
	s1 = s4, assert (strcmp(s1.c_str(), "s4") == 0);
	s1.assign("AB"), assert (strcmp(s1.c_str(), "AB") == 0);
	s1.assign(s4), assert (strcmp(s1.c_str(), "s4") == 0);
	
// test appends
	s1 += "abc", assert(strcmp(s1.c_str(), "s4abc") == 0);
	s1 += 'd', assert(strcmp(s1.c_str(), "s4abcd") == 0);
	s1 += s4, assert(strcmp(s1.c_str(), "s4abcds4") == 0);
	s1 = "A", s1.append("BC");
	assert(strcmp(s1.c_str(), "ABC") == 0);
	s1.append('D'), assert (strcmp(s1.c_str(), "ABCD") == 0);
	s1.append(s4), assert (strcmp(s1.c_str(), "ABCDs4") == 0);
	assert(strcmp((s4 + s5).c_str(), "s4s5") == 0);	
	assert(strcmp((s4 + "s5").c_str(), "s4s5") == 0);	
	assert(strcmp(("s4" + s5).c_str(), "s4s5") == 0);	
	assert(strcmp((s4 + '5').c_str(), "s45") == 0);	
	assert(strcmp(('4' + s5).c_str(), "4s5") == 0);	
	
// test inserts
	s1 = "abc";
	s1.insert(3, "Dd").insert(1,"BC", 1).insert(0, "A");
	assert(strcmp(s1.c_str(), "AaBbcDd") == 0);
	s1.insert(7, 'E', 2).insert(4, 'C');
	assert(strcmp(s1.c_str(), "AaBbCcDdEE") == 0);
	s1.insert(10,s4).insert(0, s4, 1).insert(0, s4, 0, 1);
	assert(strcmp(s1.c_str(), "s4AaBbCcDdEEs4") == 0);
	
// test removes
	s1.remove(0, 2);
	assert(strcmp(s1.c_str(), "AaBbCcDdEEs4") == 0);
	s1.remove(8), assert(strcmp(s1.c_str(), "AaBbCcDd") == 0);
	s1.remove(), assert(strcmp(s1.c_str(), "") == 0);
	
// test replace
	s1.replace(0, 0, "123ab789"), s1.replace(3, 2, "45678", 3);
	assert(strcmp(s1.c_str(), "123456789") == 0);
	s1.replace(1, 3, 'x', 2).replace(0, 0, '0');
	assert(strcmp(s1.c_str(), "01xx56789") == 0);
	s1.replace(3, 1, s4, 1).replace(2, 1, s4);
	assert(strcmp(s1.c_str(), "01s4456789") == 0);

// test accesses
	s1.put_at (2, '2');
	assert(s1.get_at(1) == '1' && s1[2] == '2');
	assert((s1[3] = '3') == '3'), assert(s1.length() == 10);
	s1.resize(3), assert(strcmp(s1.c_str(), "012") == 0);
	s1.resize(5, 'X'), assert(strcmp(s1.c_str(), "012XX") == 0);
	s1.resize(6), assert(memcmp(s1.c_str(), "012XX\0", 7) == 0);
	
char buf[10];

	assert (s1.copy(buf, sizeof(buf)) == 6 && strcmp(buf, "012XX") == 0);
	assert (s1.copy(buf, 3, 1) == 3 && memcmp(buf, "12X", 3) == 0);
	
// test finds
	s1 = "s4s4";
	assert(s1.find(s4) == 0 && s1.find(s4, 1) == 2 && s1.find (s4, 3) == NPOS);
	assert(s1.find("s4") == 0 && s1.find("s4", 3) == NPOS && s1.find ("s4XX", 1, 2) == 2);
	assert(s1.find('s') == 0 && s1.find('s', 1) == 2 && s1.find ('x') == NPOS);

	assert(s1.rfind(s4) == 2 && s1.rfind(s4, 1) == 0 && s1.rfind (s5, 3) == NPOS);
	assert(s1.rfind("s4") == 2 && s1.rfind("s4", 3) == 2 && s1.rfind ("s4XX", 1, 3) == NPOS);
	assert(s1.rfind('s') == 2 && s1.rfind('s', 2) == 2 && s1.rfind ('x') == NPOS);

	assert(s1.find_first_of(s4) == 0 && s1.find_first_of(s4, 1) == 1 && 
	       s1.find_first_of(s4, 4) == NPOS);
	assert(s1.find_first_of("s4") == 0 && s1.find_first_of("s4", 3) == 3 && 
	       s1.find_first_of("abs", 1, 2) == NPOS);
	assert(s1.find_first_of('s') == 0 && s1.find_first_of('s', 1) == 2 && 
	       s1.find_first_of('x') == NPOS);

	assert(s1.find_last_of(s4) == 3 && s1.find_last_of(s4, 1) == 1 && 
	       s1.find_last_of(s6) == NPOS);
	assert(s1.find_last_of("s4") == 3 && s1.find_last_of("s4", 2) == 2 && 
	       s1.find_last_of("abs", 1, 2) == NPOS);
	assert(s1.find_last_of('s') == 2 && s1.find_last_of('s', 1) == 0 && 
	       s1.find_last_of('x') == NPOS);

	assert(s1.find_first_not_of(s5) == 1 && s1.find_first_not_of(s5, 2) == 3 && 
	       s1.find_first_not_of(s4) == NPOS);
	assert(s1.find_first_not_of("s5") == 1 && s1.find_first_not_of("s5", 2) == 3 && 
	       s1.find_first_not_of("s4a", 1, 2) == NPOS);
	assert(s1.find_first_not_of('s') == 1 && s1.find_first_not_of('s', 2) == 3 && 
	       s1.find_first_not_of('s', 4) == NPOS);

	assert(s1.find_last_not_of(s5) == 3 && s1.find_last_not_of(s5, 2) == 1 && 
	       s1.find_last_not_of(s4) == NPOS);
	assert(s1.find_last_not_of("s5") == 3 && s1.find_last_not_of("s5", 2) == 1 && 
	       s1.find_last_not_of("s4a", 1, 2) == NPOS);
	assert(s1.find_last_not_of('s') == 3 && s1.find_last_not_of('s', 2) == 1 && 
	       s1.find_last_not_of('s', 0) == NPOS);
	       
// test compares
	assert(s1.compare(s1) == 0 && s1.compare(s4, 2) == 0 &&
	       s1.compare(s4, 2, 2) == 0);
	assert(s1.compare("s4s4") == 0 && s1.compare("s4", 2) == 0 &&
	       s1.compare("s4xx", 2, 2) == 0);
	assert(s8.compare('c') == 0 && s1.compare('4', 3) == 0 &&
	       s6.compare('a', 0, 3) == 0);
	assert(s1.compare(s4) != 0 && s1.compare(s1, 1) != 0 &&
	       s1.compare(s4, 0, 2) != 0);
	assert(s1.compare("s4s5") != 0 && s1.compare("s44", 3) != 0 &&
	       s1.compare("s4xx", 0, 2) != 0);
	assert(s1.compare('c') != 0 && s1.compare('4', 2) != 0 &&
	       s6.compare('a', 0, 2) != 0);

	assert(s1 == s1 && s1 == "s4s4" && s8 == 'c' && "s4" == s4 && 'c' == s8);
	assert(s1 != s4 && s1 != "xx" && s1 != 's' && "s4" != s1 && 'a' != s6);

	cout << "SUCCESS testing <string>" << endl;
	
return 0;
}


	
	
