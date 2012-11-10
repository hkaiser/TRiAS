#ifndef _MYENUM_H
#define _MYENUM_H

class MyEnum : public NEnumWListElement
{
public:
	void InsertItem (const WListElement &item_after, const WListElement &item) { 
		list<WListElement>::iterator it = m_data.begin();
			while (*it != item_after && it != m_data.end()) it++;
			m_data.insert(it, item); 
	}
	void ClearItem (WListElement &item) { 
		list<WListElement>::iterator it = m_data.begin();
			while (*it != item) it++;
			m_data.erase (it); 
	}

	OS_POLY_FUNCTION((MyEnum*));
};

void os_write (os_bstream& stream, const MyEnum& Enum);
void os_read (os_bstream& stream, MyEnum& Enum);

OS_POLY_CLASS(MyEnum);
OS_STREAM_OPERATORS(MyEnum);

#endif //_MYENUM_H

