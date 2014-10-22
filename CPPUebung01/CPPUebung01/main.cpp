#include <iostream>
#include "string.h"

using namespace std;

int main(void){
	cout << String("hi ") << String("Amig").concat('o') << endl;
	cout << String("How ").concat(String("are ").concat(String("you ")).concat(String("my friend"))) << endl;
	String abc;	for (char c = 'A'; c <= 'Z'; ++c){ abc = abc.concat(c); }
	cout << String("ABC: ") << abc << endl;
	cout << String("01: ") << abc.substring(2, 3) << endl;
	cout << String("02: ") << abc.substring(2, 8) << endl;
	cout << String("03: ") << abc.substring(2, 8).substring(1, 4) << endl;
	cout << String("04: ") << abc.substring(2, 8).substring(1, 4).substring(4, 5) << endl;
	cout << String("05: ") << abc.substring(1, 1) << endl;
	cout << String(String("copy")) << endl;
	cout << String(String("toCString test").toCString().get()) << endl;
	unique_ptr<char[]> cstring;
	{ cstring = String("toCString test2").toCString(); } //Create and destroy String
	cout << cstring.get() << endl;
	String mystring("toCString test3");
	{ unique_ptr<char[]> cstring2 = mystring.toCString(); } //Create and destroy C-String
	cout << mystring << endl;
	String outer1, outer2;
	{
		String inner1("12345");
		outer1 = inner1;
		String inner2("12345");
		outer2 = inner2.substring(1, 4);
	}
	cout << outer1 << endl;
	cout << outer2 << endl;
	cout << String("Press enter to close...");
	cin.ignore(); //Wait for any input
	return 0;
}