#include <iostream>

using namespace std;

void f(const int& i){ cout << i << endl; }
void f(int&& i){ i++; cout << i << endl;  }

int main(void){
	int z = 100;
	f(z);
	f(move(z));
	cout << z << endl;
	getchar();
}