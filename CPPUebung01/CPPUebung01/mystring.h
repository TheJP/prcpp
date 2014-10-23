#pragma once
#include <memory>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <ostream>

using namespace std;

class String final
{
private:
	shared_ptr<char> _content;
	size_t _length;
	size_t _start;
public:
	String();
	String(const String & other);
	String(String && other);
	String(const char const * other);
	String & operator=(const String & other);
	String & operator=(String && other);
	//Standard destructor
	//~String();

	char charAt(size_t index) const;
	int compareTo(const String & s) const;
	bool operator==(const String & s) const;
	String concat(char c) const;
	String concat(const String & s) const;
	size_t length() const;
	String substring(size_t beg, size_t end) const;
	unique_ptr<char[]> toCString() const;

	friend ostream & operator<<(ostream & os, const String & s);
	static String valueOf(int i);
};

