#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node {
	string Data;
  //establish prev and next pointers
	Node *Prev;
	Node *Next;
	/*
	* Node struct
	* params:
	*     -string
	*/
	Node(string x){
		Data = x;
		Prev = NULL;
		Next = NULL;
	}
};



//all functions used 
class DBList{
private:
	Node *Head;
	Node *Tail;
	Node *Current;
public:
	DBList();
	void Load(string);
	void Load(Node*&);
	void Fill();
	void getNum();
	void lengthRand(int);	
	void Traverse(int, int, ofstream &);
	void RemRev(string, int, ofstream&);
};
