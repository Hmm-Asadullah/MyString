#include<iostream>
using namespace std;
class String
{
	char* data;
	int size;
	bool isValidIndex(int index) const;
	void copyString(char* dest, const char* src) const;
	void mySwap(char& a, char& b);
	int getLength1(const char* p) const;
	int getSmallSize(int size1, int size2) const;
	int getNumLength(int num);
	bool isEmpty() const;
public:
	String();
	String(const char c);
	String(const char* c);
	String(const String& ref);
	String(String&& ref);
	String& operator=(const String& ref);
	String& operator=(String&& ref);
	~String();
	void input();
	void shrink();
	char& operator [] (const int index);
	const char& operator [] (const int index) const;
	bool operator ! () const;
	int getLength() const;
	int getSize() const;
	void display() const;
	int find(const String& subStr, const int start = 0) const;
	void insert(const int index, const String& subStr);
	void remove(const int index, const int count = 1);
	int replace(const String& old, const String& newSubStr);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	void reverse();
	void resize(int newSize);
	int operator == (const String& s2) const;
	bool operator > (const String& s2)const;
	bool operator < (const String& s2)const;
	bool operator >= (const String& s2)const;
	bool operator <= (const String& s2)const;
	bool operator != (const String& s2)const;
	String left(const int count);
	String right(const int count);
	String operator + (const String& s2) const;
	void operator += (const String& s2);
	String& operator = (const long long int num);
	explicit operator long long int()const;
	explicit operator double()const;
	explicit operator bool()const;
	friend istream& operator >> (istream& in, String& s);
	friend ostream& operator << (ostream& out, const String& s);
};
