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
			srand(time(NULL));
			int des = rand()%1;
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
	}
	

};


int main(){

	tree_node *qwe = new tree_node;
	cout<<qwe->next_node_L<<endl;
	cout<<qwe->next_node_R<<endl;
	cout<<qwe->parent<<endl;
	cout<<qwe->T<<endl;
	cout<<qwe->gate<<endl;
	cout<<qwe->value<<endl;

	priority_queue asd;
	asd.priority_queue_init();
	cout<<asd.root->T<<endl;
	asd.insert(0,123, 0);
	asd.insert(1,234, 1);
	asd.insert(4,123, 1);
	asd.insert(8,234, 1);
	asd.insert(9,123, 1);
	asd.insert(16,234, 1);
	





return 0;
}

