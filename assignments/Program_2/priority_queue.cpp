/////////////////////////////////////////////////////////////////////////////////
//                   
// Title:            Program 2 - Priority Queue
// Files:            priority_queue.cpp, input_data.txt, 
//                   priority_out.txt, and animals.txt
//
// Semester:         1063 Data Structures - Spring 2018
//
// Author:           Elijah Portmann
// Email:            eliportmann09@gmail.com
// Description:      Program 2 creates a list based queue 
//                   with priority for word length and in
//                   the case of a tie, alphabetically. 
//                   It uses a class and methods to push
//                   and pop names of animals when told to.
//                   The program acheives the priority sorting  
//                   by running through the input file and using
//                   if and else statements to determine the 
//                   correct position in the queue. A list is 
//                   also made that shows the order of the words
//					         in which they were removed.
//
/////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node{
	string val;
	Node* next;
	Node(){
		val = " ";
		next = NULL;
	}
	Node(string v){
		val = v;
		next = NULL;
	}
};

/**
*Class Queue:
* the class creates a list based queue using nodes and 
* another list to pop and pull the queue
*
*Methods within this class:
*	-pop
*	-pop
*	-push
*	-empty
*	-print
*	-prioritySort
*	-priorityQueue
*	-getFirst
*/
class Queue{
private:
	Node* Front;
	Node* Rear;
public:
	/**
	* Queue
	* constructor
	* params:
	*      none
	*/
	Queue(){
		//initializes the front and rear to NULL
		Front = Rear = NULL;
	}


	/**
	* Method string pop:
	*      Pops name off the queue
	* Params:
	*      none
	* Returns:
	*      string
	*/
	string pop(){
		if (!empty()){
			Node* temp = Front;
			string v = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;          // give mem back to system
			return v;
		}
		else{
			cout << "error: cannot pop off empty queue." << endl;
			return " ";
		}
	}


	/**
	* Method bool pop:
	*      pops an animal name off of the queue
	* Params:
	*      string v 
	* Returns:
	*      void
	*/
	bool pop(string &v){
		if (!empty()){
			Node* temp = Front;   // temp pointer so we can delete node
			string t = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;          // give mem back to system
			v = t;
			return true;
		}
		else{
			cout << "error: cannot pop off empty queue." << endl;
			return false;
		}
	}


	/**
	* Method void push:
	*      Pushes an animal name on the queue
	* Params:
	*      string val
	* Returns:
	*      void
	*/
	void push(string v){
		Node* n = new Node(v);
		// handle the empty case
		if (empty()){
			Front = n;
			Rear = n;
		}
		// not empty add to rear
		else{	
			Rear->next = n;
			Rear = n;
		}
	}


	/**
	* Method bool empty:
	*      checks if queue is empty
	* Params:
	*      none
	* Returns:
	*      bool
	*/
	bool empty(){
		return (Front == NULL);
	}


	/**
	* Method void print:
	*      Prints every item still on the queue.
	* Params:
	*      none
	* Returns:
	*      void
	*/
	void print(){
		Node* temp = Front;
		while (temp){
			cout << temp->val << "->";
			temp = temp->next;
		}
		cout << '\n';
	}


	/**
	* Method void prioritySort:
	*       creates priority queue based on length and in the case of
	*		a tie based on alphabetcal order as well
	* Params:
	*		none
	* Returns:
	*       void
	*/
	void prioritySort(){
		Node *temp = Front;
		//case 1: handles empty queue with empty method
		if (empty()){
			return;
		}
		//makes swapping easier
		while (temp->next != NULL){
			string first = temp->val;
			string second = temp->next->val;

			//case 2: when the first is bigger, they swap so that
			//shorter words are first in the queue
			if (first.length()>second.length()){
				temp->val = second;
				temp->next->val = first;
			}

			//case 3: when the lengths are equal, if the first comes second
			//alphabetically then they swap
			else if (first.length() == second.length()){
				if (first>second){
					temp->val = second;
					temp->next->val = first;
				}
			}
			temp = temp->next;
		}
	}
	

	/**
	* Method void priorityQueue:
	*		makes priority queue based on word length
	* Params:
	*		outfile
	* Returns:
	*		void
	*/
	void priorityQueue(ofstream &outfile) {
		int queueCount = 1;
		Node *temp = Front;
		while (temp) {
			outfile << queueCount++ << " " << temp->val << '\n';
			temp = temp->next;
		}
	}


	/**
	* Method string getFirst:
	*      Returns first word in queue
	* Params:
	*      none
	* Returns:
	*      string
	*/
	string getFirst() {
		//If a word is in the queue, it returns that word, if not then nothing
		while (!empty()) 
			return Front->val;
		return "";
	}
};


int main(){
	Queue Q;
	string animal;
	//command refers to push/pull directions in input file
	string command;
	//nodeCount keeps track of number of animals in push queue
	int nodeCount = 0;	
	//popCount keeps track to number popped off list
	int popCount = 1;

	fstream infile;
	infile.open("input_data.txt");
	ofstream outfile;
	outfile.open("priority_out.txt");
	outfile << "Animals Popped off the Queue:" << "\n\n";

	//loops through input file
	while (infile >> command){
		//command 1: push animal name onto priority queue with push method
		if (command == "push"){
			infile >> animal;
			Q.push(animal);
			nodeCount++;
		}
		//command 2: pops animal name off queue using pop method
		else if (command == "pop"){
			if (Q.getFirst() != "")
				outfile << popCount++ << " " << Q.getFirst() << endl;
			Q.pop(animal);
			//removes nodeCount to keep up with number of words in queue
			nodeCount--;   
			if (nodeCount<0)
				nodeCount=0;
		}

		//prioritizes the words to help make the queue 
		if (nodeCount>1){
			for (int i=0; i<nodeCount-i; i++){
				Q.prioritySort();
			}
		}
	}
	//creates second list of the names not popped but in priority order
	outfile << '\n' << "Animals Remaining on the Queue (in order of priority): "
		<< endl;
	Q.priorityQueue(outfile);
	infile.close();
	outfile.close();
	return 0;
}
