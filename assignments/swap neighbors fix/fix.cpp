 void swapNeighbors(){
		node* prev = Head;
		node* temp = Head->next;
		int tempvar;

		//changed to temp from temp->next
		while (temp){
			tempvar = temp->data;
			temp->data = prev->data;
			prev->data = tempvar;
			//added if check so that we break from
			//the while loop before its too late
			if (temp->next == NULL){
				break;
			}
			prev = prev->next->next;
			temp = temp->next->next;
		}
	}
