#include "String.h"
bool String::isValidIndex(int index) const
{
	return (index >= 0 && index <= size);
}
void String::copyString(char* dest, const char* src) const
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
void String::mySwap(char& a, char& b)
{
	char temp = a;
	a = b;
	b = temp;
}
int String::getLength1(const char* p) const
{
	if (!p)
	{
		return 0;
	}
	int i = 0;
	while (p[i] != '\0')
	{
		i++;
	}
	return i;
}
int String::getSmallSize(int size1, int size2) const
{
	return size1 > size2 ? size2 : size1;
}
int String::getNumLength(int num)
{
	int len = 0;
	while (num > 0)
	{
		len++;
		num = num / 10;
	}
	return len;
}
String::String()
{
	data = nullptr;
	size = 0;
}
String::String(const char c)
{
	data = new char[2];
	data[0] = c;
	data[1] = '\0';
	size = 2;
}
String::String(const char* c)
{
	size = getLength1(c) + 1;
	data = new char[size];
	copyString(data, c);
}
String::String(const String& ref)
{
	size = ref.getLength() + 1;
	data = new char[size];
	copyString(data, ref.data);
}
String::String(String&& ref)
{
	if (ref.data == nullptr || this == &ref)
	{
		return;
	}
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
}
String& String::operator=(const String& ref)
{
	if (this == &ref)
	{
		return *this;
	}
	this->~String();
	size = ref.getLength() + 1;
	data = new char[size];
	copyString(data, ref.data);
	return *this;
}
String& String::operator=(String&& ref)
{
	if (ref.data == nullptr || this == &ref)
	{
		return *this;
	}
	this->~String();
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
	return *this;
}
String::~String()
{
	if (!data)
	{
		return;
	}
	delete[]data;
	data = nullptr;
	size = 0;
}
void String::input()
{
	if (!data || size <= 0)
	{
		resize(10);
	}
	char temp;
	int i = 0;
	while (cin.get(temp) && temp != '\n')
	{
		if (i == (size - 1))
		{
			resize(size + 10);
		}
		data[i] = temp;
		i++;
	}
	data[i] = '\0';
	shrink();
}
void String::shrink()
{
	resize(getLength() + 1);
}
char& String::operator [](const int index)
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}
const char& String::operator [](const int index) const
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}
bool String::isEmpty() const
{
	return (data == nullptr || data[0] == '\0');
}
bool String::operator !() const
{
	return isEmpty() ? true : false;
}
int String::getLength() const
{
	return getLength1(data);
}
int String::getSize() const
{
	return size;
}
void String::display() const
{
	if (data)
	{
		cout << data;
	}
}
int String::find(const String& subStr, const int start) const
{
	if (!(subStr.isEmpty()) && isValidIndex(start))
	{
		for (int i = start; i < getLength(); i++)
		{
			bool flag = true;
			if (subStr.data[0] == data[i])
			{
				int j = 1;
				while (j < subStr.getLength() && flag == true)
				{
					if (subStr.data[j] == data[i + 1])
					{
						j++;
						i++;
						flag = true;
					}
					else
					{
						flag = false;
					}
				}
				if (flag)
				{
					return i - (subStr.getLength() - 1);
				}
			}
		}
		return -1;
	}
}
void String::insert(const int index, const String& subStr)
{
	if (!(subStr.isEmpty()) && isValidIndex(index))
	{
		int newSize = getLength() + subStr.getLength() + 1;
		resize(newSize);
		char* temp = new char[newSize];
		for (int i = 0; i < index; i++)
		{
			temp[i] = data[i];
		}
		for (int i = 0; i < subStr.getLength(); i++)
		{
			temp[index + i] = subStr.data[i];
		}
		int j = index;
		for (int i = index + subStr.getLength(); i < newSize - 1; i++)
		{
			temp[i] = data[j];
			j++;
		}
		temp[getLength() + subStr.getLength()] = '\0';
		copyString(data, temp);
		delete[]temp;
	}
}
void String::remove(const int index, const int count)
{
	if (isValidIndex(index))
	{
		for (int i = index; i < getLength() - count; i++)
		{
			data[i] = data[i + count];
		}
		data[getLength() - count] = '\0';
	}
}
int String::replace(const String& old, const String& newSubStr)
{
	if (!(old.data) && !(newSubStr.data))
	{
		return -1;
	}
	int count = 0;
	for (int i = 0; i < getLength(); i++)
	{
		int j = find(old, i);
		if (j != -1)
		{
			remove(j, old.getLength());
			insert(j, newSubStr);
			count++;
			i = i + old.getLength();
		}
	}
	return count;
}
void String::trimLeft()
{
	int i = 0, count = 0;
	while (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
	{
		count++;
		i++;
	}
	remove(0, count);
}
void String::trimRight()
{
	int i = getLength() - 1, count = 0;
	while (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
	{
		count++;
		i--;
	}
	data[i + 1] = '\0';
}
void String::trim()
{
	trimLeft();
	trimRight();
}
void String::makeUpper()
{
	for (int i = 0; i < getLength(); i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - 32;
		}
	}
}
void String::makeLower()
{
	for (int i = 0; i < getLength(); i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] + 32;
		}
	}
}
void String::reverse()
{
	int i = 0, j = getLength() - 1;
	while (i < getLength() / 2)
	{
		mySwap(data[i], data[j]);
		i++;
		j--;
	}
}
void String::resize(int newSize)
{
	if (newSize <= 0)
	{
		this->~String();
		return;
	}
	char* temp = new char[newSize];
	int smallerSize = getSmallSize(size, newSize);
	for (int i = 0; i < smallerSize; i++)
	{
		temp[i] = data[i];
	}
	this->~String();
	data = temp;
	size = newSize;
}
int String::operator == (const String& s2) const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return 1;
			}
			else if (data[i] < s2.data[i])
			{
				return -1;
			}
		}
		return 0;
	}
	else if (getLength() > s2.getLength())
	{
		return 1;
	}
	else if (getLength() < s2.getLength())
	{
		return -1;
	}
}
bool String::operator > (const String& s2)const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return true;
			}
			else if (data[i] < s2.data[i])
			{
				return false;
			}
		}
		return false;
	}
	else if (getLength() > s2.getLength())
	{
		return true;
	}
	else if (getLength() < s2.getLength())
	{
		return false;
	}
}
bool String::operator < (const String& s2)const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return false;
			}
			else if (data[i] < s2.data[i])
			{
				return true;
			}
		}
		return false;
	}
	else if (getLength() > s2.getLength())
	{
		return false;
	}
	else if (getLength() < s2.getLength())
	{
		return true;
	}
}
bool String::operator >= (const String& s2)const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return true;
			}
			else if (data[i] < s2.data[i])
			{
				return false;
			}
		}
		return true;
	}
	else if (getLength() > s2.getLength())
	{
		return true;
	}
	else if (getLength() < s2.getLength())
	{
		return false;
	}
}
bool String::operator <= (const String& s2)const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return false;
			}
			else if (data[i] < s2.data[i])
			{
				return true;
			}
		}
		return true;
	}
	else if (getLength() > s2.getLength())
	{
		return false;
	}
	else if (getLength() < s2.getLength())
	{
		return true;
	}
}
bool String::operator != (const String& s2)const
{
	if (getLength() == s2.getLength())
	{
		for (int i = 0; i < getLength(); i++)
		{
			if (data[i] > s2.data[i])
			{
				return true;
			}
			else if (data[i] < s2.data[i])
			{
				return true;
			}
		}
		return false;
	}
	return true;
}
String String::left(const int count)
{
	if (count <= getLength())
	{
		String str;
		str.size = count + 1;
		str.data = new char[count];
		for (int i = 0; i < count; i++)
		{
			str.data[i] = data[i];
		}
		str.data[count] = '\0';
		return str;
	}
}
String String::right(const int count)
{
	if (count <= getLength())
	{
		String str;
		str.size = count;
		str.data = new char[count];
		int i = 0;
		for (int j = getLength() - count; j < getLength(); j++)
		{
			str.data[i] = data[j];
			i++;
		}
		str.data[i] = '\0';
		return str;
	}
}
String String::operator + (const String& s2) const
{
	if (!(s2.isEmpty()))
	{
		String str;
		str.size = getLength() + s2.getLength() + 1;
		str.data = new char[str.size];
		int i = 0;
		while (i < getLength())
		{
			str.data[i] = data[i];
			i++;
		}
		int j = 0;
		while (i < str.size)
		{
			str.data[i] = s2.data[j];
			i++;
			j++;
		}
		return str;
	}
}
void String::operator += (const String& s2)
{
	if (!(s2.isEmpty()))
	{
		int newSize = getLength() + s2.getLength() + 1;
		resize(newSize);
		int i = getLength();
		copyString(&data[i], s2.data);
	}
}
String& String::operator = (const long long int num)
{
	int num1 = num, i = 0;
	if (num < 0)
	{
		num1 = -num1;
	}
	String str;
	str.size = getNumLength(num1) + 1;
	str.data = new char[str.size];
	while (num1)
	{
		int digit = num1 % 10;
		str.data[i] = '0' + digit;
		num1 = num1 / 10;
		i++;
	}
	str.data[i] = '\0';
	str.reverse();
	if (num < 0)
	{
		str.insert(0, "-");
	}
	return str;
}
String::operator long long int()const
{
	int i = 0, digit, sign = 1;
	long long int num = 0;
	if (data[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (i < getLength())
	{
		digit = data[i] - '0';
		num = num * 10 + (digit);
		i++;
	}
	num = num * sign;
	return num;
}
String::operator double()const
{
	double value;
	double digit = 0;
	int i = 0;
	while (data[i] != '.')
	{
		if ((data[i] >= '0' && data[i] <= '9'))
		{
			value = data[i] - 48;
			digit = digit * 10 + ((double)value);
		}
		i++;
	}
	i++;
	double j = 0.1;
	for (i; i < getLength(); i++)
	{
		value = data[i] - 48;
		digit = digit + ((double)value * j);
		j = j / 10;
	}
	return digit;
}
String::operator bool()const
{
	return isEmpty() ? false : true;
}
istream& operator >> (istream& in, String& s)
{
	s.input();
	return in;
}
ostream& operator << (ostream& out, const String& s)
{
	s.display();
	return out;
}
