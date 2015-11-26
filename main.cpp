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
	for(i=0;i<n;i++)
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
	for(i=0;i<n;i++){
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
	int NUM_NODES = 3;

	//adjacency matrix
	vector<vector<int> > adj_matrix(NUM_NODES, std::vector<int>(NUM_NODES));
	for (int i=0;i<NUM_NODES;i++){
		for(int j=0;j<NUM_NODES;j++){
			adj_matrix[i][j]=0;
		}
	}
	
	//signal vector
	vector<int> signal(NUM_NODES);

	for(int j=0; j<NUM_NODES; j++){
		signal[j]=-1;
	}

	//signal matrix to store the value at each point of time
	vector<vector<int> > signalmem(130, std::vector<int>(NUM_NODES));
	
	for(int i=0;i<130; i++){
		for(int j=0; j<NUM_NODES; j++){
			signalmem[i][j]=-1;
		}
	}

	int times=0; // value of the time instants
	int val=0;// value found at each stage
	int i=0;
	int j=0;

	// Begin simulation
		

	/*srand(time(NULL));

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
	
	srand(time(NULL));

	priority_queue asd;
	asd.priority_queue_init();
	cout<<asd.root->T<<endl;
	asd.insert(0,"none", 0, 0);
	asd.insert(20,"none", 1, 0);
	asd.insert(50, "none", 0, 0);

	asd.print_tree(asd.root);

	adj_matrix[0][2]=1;
	adj_matrix[0][1]=1;
	adj_matrix[1][2]=1;	

	//creating signal vector before beginning the simulation
	make_signal(asd.root,signal);
	update_signal(NUM_NODES,signal,signalmem,0);*/

	srand(time(NULL));

	priority_queue asd;
	asd.priority_queue_init();
	//cout<<asd.root->T<<endl;
	asd.insert(0,"none", 0, 0);
	asd.insert(20,"none", 1,0);
	asd.insert(50, "none", 0,0);

	//asd.print_tree(asd.root);

	adj_matrix[0][2]=1;
	adj_matrix[0][1]=1;
	adj_matrix[1][2]=1;

	//in general each node can have multiple nodes sensitive to it
	vector<vector<string> > gate_list(NUM_NODES, std::vector<string>(NUM_NODES));
	gate_list[0][1] = "not";
	gate_list[0][2] = "nand";
	gate_list[1][2] = "nand";
	
	//start simulation
	while(asd.root->T!=-1){ //unless the priority queue gets empty

		if(asd.root->T ==times){ //if the time = time for the evaluation of the signal 
			cout<<endl;			
			cout<<"time is "<<times<<endl;
			//val=computeOutput(asd.root,adj_matrix,signal);
			cout<<"value changed is "<<asd.root->value<<" for node " <<asd.root->nodenum<<endl;
			signal[asd.root->nodenum]=asd.root->value;	
			print_signals(signal,NUM_NODES);
			
			for(int k=0;k<NUM_NODES;k++){
				if (adj_matrix[asd.root->nodenum][k]==1){
					tree_node *p;
					p->gate	= gate_list[asd.root->nodenum][k];
					p->nodenum=k;
					val=computeOutput(p,adj_matrix,signal);
					//signal[k]=val;	
					asd.insert(times+computeDelay(p),p->gate,val,k);		
				}			
			}	

			asd.remove();
		}

		else{
			//cout<<"nothing now"<<endl;
		}

	update_signal(NUM_NODES,signal,signalmem,times);	

	//print_signals(signal,NUM_NODES);
	if(asd.root->T>times)
	times=times+1;	//updating time 
	}
		
	cout<<"total time for simulation is "<<times<<endl; //total simulation time
	
	for(i=0;i<NUM_NODES;i++){
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
	
