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
	cout << String("Press enter to close...");
	cin.ignore(); //Wait for any input
	return 0;
}