#include "mystring.h"


String::String() : _length(0), _start(0) { }
String::String(const String& other){
	_content = other._content;
	_length = other._length;
	_start = other._start;
}
String::String(const char const * other){
	_start = 0;
	_length = strlen(other);
	_content = unique_ptr<char[]>(new char[_length]);
	memcpy(this->_content.get(), other, this->_length);
}

char String::charAt(size_t index) const {
	return _content.get()[index + this->_start];
}
int String::compareTo(const String& s) const {
	int i = 0; int lmin = min(this->_length, s._length);
	while (i < lmin && s.charAt(i) == this->charAt(i)){ ++i; }
	return i >= lmin ?
		(this->_length < s._length ? -1 : this->_length > s._length ? 1 : 0) :
		(tolower(this->charAt(i)) < tolower(s.charAt(i)) ? -1 : 1);
}
bool String::operator==(const String& s) const { return this->compareTo(s) == 0; }
String String::concat(char c) const {
	char tmpC[2] = {c, '\0'};
	return this->concat(String(tmpC));
}
String String::concat(const String& s) const {
	String tmp;
	tmp._start = 0;
	tmp._length = this->_length + s._length;
	tmp._content = unique_ptr<char[]>(new char[tmp._length]);
	//Copy existing chars from array
	memcpy(tmp._content.get(), this->_content.get() + this->_start, this->_length);
	memcpy(tmp._content.get() + this->_length, s._content.get() + s._start, s._length);
	return tmp;
}
size_t String::length() const {
	return this->_length;
}
String String::substring(size_t beg, size_t end) const {
	if (beg >= this->_length || end <= beg){ return String(); }
	String tmp(*this);
	tmp._length = end - beg;
	tmp._start += beg;
	return tmp;
}
unique_ptr<char[]> String::toCString() const {
	unique_ptr<char[]> tmp(new char[this->_length + 1]);
	memcpy(tmp.get(), this->_content.get() + this->_start, this->_length);
	tmp.get()[this->_length] = '\0';
	return tmp;
}
ostream& operator<<(ostream& os, const String& s){
	const size_t end = s._start + s._length;
	for (size_t i = s._start; i < end; ++i){ os << s._content.get()[i]; }
	return os;
}
String String::valueOf(int i){
	char c[50]; int k = 0;
	if (i == 0){ c[k] = '0'; ++k; }
	else {
		bool addM = i < 0;
		while (i != 0){
			c[k] = ('0' + abs((i % 10)));
			i /= 10;
			++k;
		}
		if (addM){ c[k] = '-'; ++k; }
	}
	c[k] = '\0';
	reverse(c, c + k);
	return String(c);
}
