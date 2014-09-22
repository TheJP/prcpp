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
	String(const String& other);
	String(const char const * other);
	//Standard destructor
	//~String();

	char charAt(size_t index) const;
	int compareTo(const String& s) const;
	bool operator==(const String& s) const;
	String concat(char c) const;
	String concat(const String& s) const;
	size_t length() const;
	// Substring des Bereichs [beg, end) // falls beg ≥ m_len oder end ≤ beg: gibt leeren String zurück 
	String substring(size_t beg, size_t end) const;
	// erzeugt 0-terminierten C-String, kopiert Inhalt und gibt Zeigerobjekt zurück
	unique_ptr<char[]> toCString() const;

	// Ausgabe-Operator für Output-Streams (Inline-Implementation schon gegeben) friend
	friend ostream& operator<<(ostream& os, const String& s);
// Klassen-Methode
	static String valueOf(int i); // erzeugt eine String-Repräsentation von i
};

