#if !defined(_DEL_HPP)
#define _DEL_HPP 

class DelPointer
{
private:
	long* m_pX;
	long* m_pY;
	long* m_pK;
public:
	DelPointer();
	void Del(long* pX, long* pY, long* pK);
};               

#endif // _DEL_HPP