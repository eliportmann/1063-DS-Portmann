#include <iostream>
#include <string>
#include "DBList.h"

using namespace std;


DBList::DBList(){
	Head = NULL;
	Tail = NULL;
}



/*
* Function = void Load 
*     -Loads/creates room for the new nodes
* Params:
*     -string Data
*/
void DBList::Load(string Data){
	Node* Temp = new Node(Data);
	//passes node to next load function
	Load(Temp);
}



/*
* Function = void Load 
*     -Put the node in the list
* Params:
*     -Node *temp by address
*/
void DBList::Load(Node* &Temp){
	if (!Tail)
	{
		Tail = Temp;
		Head = Temp;
		Head->Prev = Tail;
		Current = Temp;
		Tail->Next = Temp->Next;
	}
	else{
	  //connects full circle
		Temp->Prev = Tail;
		Temp->Next = Head;
		Tail->Next = Temp;
		Head->Prev = Temp;
		Tail = Temp;
		Current = Head;
	}
}



/*
* Function = void Fill 
*     -Read in the names and reset the file
* Params:
*     -None
*/
void DBList::Fill(){
	string a;
	ifstream infile("animals.txt");
  //input animal name strings
	while (!infile.eof()){
		infile >> a;
		Load(a);
	}
	//resets the file for later
	infile.clear();
	infile.seekg(0);
}



/*
* Function = void getNum
*     -Gets a number from user input and checks if its in range
* Params:
*     -None
*/
void DBList::getNum(){
	int num = 0;
	cout << "Please enter a number between 1 and 13" << endl;
	cin >> num;
	//check the range of m
	if(num < 1 || num > 13){
	  cout << "try again" << endl;
	  cin >> num;
	}
  //further randomizes list using the name length
	lengthRand(num);
}



/*
* Function void lengthRand 
*     -Randomizes the movement by multiplying string length by the 
*     -user number and keeps a running count of loops
* Params:
*     -int num (from user)
*/
void DBList::lengthRand(int num){
	ifstream infile("animals.txt");
	ofstream outfile("eliminated.txt");
	string a;
	int count = 0;
	//store the lengths
	while (!infile.eof()){
		infile >> a;
		int move = a.length();
    //determines how many names we move on the circle
		move = move * num;
		Traverse(move, count++,outfile);
	}
}



/*
* Function void Traverse 
*	    -If m/move is odd it will go left and if even will go right
*     -and whoever it lands on it passes to RemRev
* Params:
*     -int m - movement amount
*	    -int n - animal count
*	    -outfile - result location
*/
void DBList::Traverse(int m, int n, ofstream &outfile){
	//handles even moves
	if (m % 2 == 0){
		for (int i = m; i > 0; i--){
			Current = Current->Next;
		}
	}
	//handles odd moves
	else{
		for (int i = m; i > 0; i--){
			Current = Current->Prev;
		}
	}
	RemRev(Current->Data,n,outfile); //will remove the Current node
}



/*
* Function void RemRev
*		   -removes animal from list and reveals which was removed
*      -as well as the winner when it reaches the last animal
* Params:
*      -string a - name of the animal being deleted from list
*	     -int winC - win check (if 0 then winner!)
*      -outfile - result location
*/
void DBList::RemRev(string a, int winC, ofstream &outfile){
  //win check
	if (a == Head->Data && a == Tail->Data){
		outfile << "The WINNER is.... " << Current->Data << " !!" << endl;
	}
	//handles if current is at tail
	else if(a == Tail->Data){
		if (winC == 0)
			outfile << "FIRST: " << Current->Data << endl;
		else
			outfile << "> " << Current->Data << endl;
		//delete and move pointers
		Node *temp = Tail;
		Tail = Tail->Prev;
		Tail->Next = temp->Next;
		delete temp;
		Current = Tail;
		Head->Prev = Tail;
	}	
	//handles if current is at node
	else if (a == Head->Data){
		if (winC == 0)
			outfile << "FIRST: " << Current->Data << endl;
		else
			outfile << "> " << Current->Data << endl;
		//delete and move pointers
		Node *temp = Head;
		Head = Head->Next;
		Head->Prev = temp->Prev;
		delete temp;
		Current = Head;
		Tail->Next = Head;
	}
	//handles if current is anywhere else
	else{
		if (winC == 0)
			outfile << "FIRST: " << Current->Data << endl;
		else
			outfile << "> " << Current->Data << endl;
		//find current 
		Node *temp = Head;
		while (temp != Current){
			temp = temp->Next;
		}
		//delete and move pointers
		Node *mid = temp;
		mid->Prev->Next = mid->Next;
		mid->Next->Prev = mid->Prev;
		Current = Current->Next;
		delete mid;
	}
}
