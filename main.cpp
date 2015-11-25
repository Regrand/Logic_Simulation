/* 
Author: Sneha Goenka
1st November 2015
CAD Project: Logic Simulation
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "computeOutput.cpp"

using namespace std;

//function to update the signal at each time instant
void update_signal(int n, std::vector<int>& signal , vector<vector<int> > &signalmem ,int time){
	int i=0;
	for(i=1;i<n;i++)
		signalmem[time][i]=signal[i];	
}

//creating the first list of signals from the node numbers and values in the priority queue - before start of simulation
void make_signal(tree_node * start, std::vector<int>& signal){

	signal[start->nodenum]=start->value;
	if(start->next_node_L!=0) make_signal(start->next_node_L,signal);
	if(start->next_node_R!=0) make_signal(start->next_node_R,signal);
}

//printing the signal value at any point of time
void print_signals(std::vector<int>& signal, int n){
	int i=0;
	for(i=1;i<n;i++){
		cout<<signal[i]<<" ";	
	}
	cout<<endl;
}

//function to print the adjacency matrix
void printMat(vector<vector<int> > &adj_matrix){
	int N=adj_matrix[0].size();
	int i,j=0;
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d ",adj_matrix[i][j]);		
		}	
		printf("\n");
	}
}
 
int main(int argc, char** argv) {

	// Number of node
	int NUM_NODES = 6;
	//adjacency matrix
	vector<vector<int> > adj_matrix(NUM_NODES, std::vector<int>(NUM_NODES));
	
	//signal vector
	vector<int> signal(NUM_NODES);
	//signal matrix to store the value at each point of time
	vector<vector<int> > signalmem(100, std::vector<int>(NUM_NODES));
	
	int times=0; // value of the time instants
	int val=0;// value found at each stage
	int i=0;
	int j=0;

	// Begin simulation
		

	srand(time(NULL));

	priority_queue asd;
	asd.priority_queue_init();
	cout<<asd.root->T<<endl;
	asd.insert(1,"xor", 1,3);
	asd.insert(3,"nor", 1,2);
	asd.insert(4,"nor", 1,1);
	asd.insert(8,"or", 1,4);
	asd.insert(2,"nand", 1,5);

	asd.print_tree(asd.root);

	adj_matrix[1][3]=1;
	adj_matrix[2][3]=1;
	adj_matrix[3][4]=1;
	adj_matrix[3][5]=1;
	adj_matrix[2][5]=1;

	//creating signal vector before beginning the simulation
	make_signal(asd.root,signal);
	update_signal(NUM_NODES,signal,signalmem,0);
	print_signals(signal,NUM_NODES);
	

	//start siluation
	while(asd.root->T!=-1){ //unless the priority queue gets empty
		cout<<endl;
		cout<<"time is "<<times<<endl;
		
		if(asd.root->T ==times){ //if the time = time for the evaluation of the signal 
			
			val=computeOutput(asd.root,adj_matrix,signal);
			cout<<"value is "<<val<<" for nodenum " <<asd.root->nodenum<<endl;
			signal[asd.root->nodenum]=val;	
			update_signal(NUM_NODES,signal,signalmem,times);		
			asd.remove();
		}

		else{
			cout<<"nothing now"<<endl;
		}
	
	print_signals(signal,NUM_NODES);
	times=times+1;	//updating time 
	}
		
	cout<<"total time is "<<times<<endl; //total simulation time
	
	for(i=1;i<NUM_NODES;i++){
		for(j=0;j<times;j++){
			if(signalmem[j][i]==0)
				cout<<"___|";		
			else if  (signalmem[j][i]==1)			
				cout<<"****|";
			else if  (signalmem[j][i]==-1)			
				cout<<"X";
		
		}	
		cout<<endl;	
	}
	
	return 0;
}
	
