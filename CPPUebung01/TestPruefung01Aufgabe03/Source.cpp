#include <iostream>
#include <memory>

using namespace std;

struct LNode
{
	int data;
	shared_ptr<LNode> next;

	LNode(int n) : data(n), next(){}
	void add_to_end(int n){
		if (next){ next->add_to_end(n); }
		else { next = unique_ptr<LNode>(new LNode(n)); }
	}
};

int main(void){
	struct LNode root(5);
	root.add_to_end(10);
	root.add_to_end(15);
	return 0;
}