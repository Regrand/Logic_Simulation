/* Author: Aniket Deshmukh
Priority queue data structure and related methods

Initial implementation: Min heap stored in a binary tree
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>

using namespace std;

struct tree_node{

	// Contains priority(T) and action(node to be updated)
	tree_node * next_node_L;
	tree_node * next_node_R;
	tree_node * parent;
	int T;
	int gate;
	int value;
	
	// Construct for tree_node
	tree_node(){
		next_node_L = 0;
		next_node_R = 0;
		parent = 0;
		T = -1;
		gate = -1;
		value = -1;
	}

	// Simple has_next
	bool has_next(){
		if((next_node_L==0)|(next_node_R==0))
			return 0;
		else{
			return 1;
		}
	}

	
};

struct priority_queue{

	tree_node *root;
	
	void priority_queue_init(){
		root = new tree_node;
	}
	
	// Insert a transaction
	void insert(int t, int out_gate, int out_val){
		
		tree_node *current_node = root;

		// If we are inserting for the first time,
		if(current_node->T==-1){
			root->T = t;
			root->gate = out_gate;
			root->value = out_val;
			return;
		}
		
				
		// Traverse the tree randomly until an empty spot is found 
		while(current_node->has_next()){
			
			int des = 0+(rand()%(int)(1-0+1));
			cout<<"\n"<<"rand_int:"<<des<<"\n";
			if (des==1){
				current_node = current_node->next_node_L;
			}
			else{
				current_node = current_node->next_node_R;
			}
		}

		// Now that we've found an empty spot, lets fit our node here
		tree_node *temp = new tree_node;
		temp->next_node_L = 0;
		temp->next_node_R = 0;
		temp->parent = current_node;
		temp->T = t;
		temp->gate = out_gate;
		temp->value = out_val;
			
		if(current_node->next_node_L==0){
			current_node->next_node_L = temp;
		}
		else if(current_node->next_node_R==0){
			current_node->next_node_R = temp;
		}
		else{	// Both nodes are free. Pick the left one then
			current_node->next_node_L = temp;
		}

		// Okay, we've found a spot for our node. But we now need to ensure that the prority of the parent is less than that of the new child
		
		tree_node *new_child = temp;
		
		// If parent has higher priority, switch nodes
		while((new_child->T)<(new_child->parent->T)){
			
			// If the parent is on the left node of it's own parent
			if((current_node->parent->next_node_L)==(new_child->parent)){
				current_node->parent->next_node_L = new_child;
			}	
			else{
				current_node->parent->next_node_R = new_child;
			}
			// Interchange parents
			new_child->parent = current_node->parent;
			current_node->parent = new_child;
			
			// Interchanging children	
			tree_node * temp_L = new_child->next_node_L;
			tree_node * temp_R = new_child->next_node_R;
			if(current_node->next_node_L==new_child){
				new_child->next_node_L = current_node;
				new_child->next_node_R = current_node->next_node_R;
				if(new_child->next_node_R!=0){
					new_child->next_node_R->parent = new_child;
				}
			}
			if(current_node->next_node_R==new_child){
				new_child->next_node_R = current_node;
				new_child->next_node_L = current_node->next_node_L;
				if(new_child->next_node_R!=0){
					new_child->next_node_L->parent = new_child;
				}
			}
			// Udate current node and its children 
			current_node->next_node_L = temp_L;
			current_node->next_node_R = temp_R;
			if(current_node->next_node_L!=0){
				current_node->next_node_L->parent = current_node;
			}
			if(current_node->next_node_R!=0){
				current_node->next_node_R->parent = current_node;
			}

			// Update current_node and new_child
			current_node = new_child->parent;
		}	
  
	}

	void print_tree(tree_node * start){

		cout<<start->T<<endl;
		if(start->next_node_L!=0) print_tree(start->next_node_L);
		if(start->next_node_R!=0) print_tree(start->next_node_R);
		cout<<endl;
		return;
		
	}

	void remove(){
		
		// First we remove the root 
		tree_node *current_node = root;
		bool first_in = 1;

		// Disjointed node. Intially arbitrary	
		tree_node *disjoint_node;
		

		// Recursively shift nodes if both children are assigned
		while((current_node->next_node_L!=0)&&(current_node->next_node_R!=0)){

			// Chose which node to shift up
			if((current_node->next_node_L->T)<=(current_node->next_node_R->T)){

				// Next disjoint node
				tree_node *temp_disjoint = current_node->next_node_R;
				
				// If removing the root, make the next node in line the root
				if(first_in){
					root = current_node->next_node_L;
					root->parent = 0;
					first_in = 0;
				}

				// Else shift node up
				else {
					// Join with disjoint node at same level (calculated in prev iteration)
					current_node->next_node_R = disjoint_node;
					current_node->next_node_R->parent = current_node;
				}
					
				current_node = current_node->next_node_L;
				disjoint_node = temp_disjoint; 
			}

			else{
				// Next disjoint node
				tree_node *temp_disjoint = current_node->next_node_L;
				
				// If removing the root, make the next node in line the root
				if(first_in){
					root = current_node->next_node_R;
					root->parent = 0;
					first_in = 0;
				}

				// Patch the node
				else {
					// Join with disjoint node at same level (calculated in prev iteration)
					current_node->next_node_L = disjoint_node;
					current_node->next_node_L->parent = disjoint_node;
				}
				
				// Shift up	
				current_node = current_node->next_node_R;
				disjoint_node = temp_disjoint; 
			
			}
		}
		
		// Now that we have taken care of the cases where both children exist, we cover the patching cases (when one or no children exist)	
	
		// If both nodes are empty
		if((current_node->next_node_L==0)&&(current_node->next_node_R==0)){
			// If removing the root, create new root 
			if(first_in){
				root = new tree_node;	// Alterntively set T=-1 fo the root if this doesn't work
				return;
			}
			// Else patch left node
			else{
				current_node->next_node_L = disjoint_node;
				current_node->next_node_L->parent = current_node;
				return;
			}
		}
		
		// If the left node is empty 
		else if(current_node->next_node_L==0){
			
			// If removing the root
			if(first_in){
				root = current_node->next_node_R;
				root->parent = 0;
				return;
			}
			// Else patch node
			else{
				current_node->next_node_L = disjoint_node;
				current_node->next_node_L->parent = current_node;
				return;
			}
		}				
		
		// If the right node is empty 
		else if(current_node->next_node_R==0){
			
			// If removing the root
			if(first_in){
				root = current_node->next_node_L;
				root->parent = 0;
				return;
			}
			// Else patch node
			else{
				current_node->next_node_R = disjoint_node;
				current_node->next_node_R->parent = current_node;
				return;
			}
		}				

	
	}
};


int main(){
	srand(time(NULL));

	priority_queue asd;
	asd.priority_queue_init();
	cout<<asd.root->T<<endl;
	asd.insert(0,123, 0);
	asd.insert(3,234, 1);
	asd.insert(4,123, 1);
	asd.insert(8,234, 1);
	asd.insert(9,123, 1);
	asd.insert(16,234, 1);
	asd.insert(2,1000,0);
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);

	cout<<"Removing top element"<<endl;	
	asd.remove();
	asd.print_tree(asd.root);


return 0;
}

