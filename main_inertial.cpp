/* 
Author: Sneha Goenka
1st November 2015
CAD Project: Logic Simulation with inertial delays
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "computeOutput.cpp"
#include <string>
#include "write_vcd_file.cpp"

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
 
	//total time for simulation
	int t0=100;

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

	//to count the number of current schedules for all signal
	vector<int> count(NUM_NODES);

	for(int j=0; j<NUM_NODES; j++){
		count[j]=0;
	}

	//signal matrix to store the value at each point of time
	vector<vector<int> > signalmem(130, std::vector<int>(NUM_NODES));
	
	for(int i=0;i<130; i++){
		for(int j=0; j<NUM_NODES; j++){
			signalmem[i][j]=-1;
		}
	}

	int times=0; // value of the time instants
	int val=0;// value found at each stage for future scheduling

	srand(time(NULL));
	
	priority_queue asd;
	asd.priority_queue_init();

	//primary input (shown by "none" schedule)
	asd.insert(0,"none", 0, 0);
	asd.insert(10,"none", 1,0);
	asd.insert(20, "none", 0,0);
	count[0]=3;

	adj_matrix[0][2]=1;
	adj_matrix[0][1]=1;
	adj_matrix[1][2]=1;

	//in general each node can have multiple nodes sensitive to it
	vector<string> gate_list(NUM_NODES);	
	gate_list[1] = "not";
	gate_list[2] = "xor";
		
	//start simulation
	times=0;	
	while(times<130){ 

		if(asd.root->T ==times){ //if the time = time for the evaluation of the signal 
			cout<<endl;			
			cout<<"time is "<<times<<endl;

			cout<<"value changed is "<<asd.root->value<<" for node " <<asd.root->nodenum<<endl;	
			//either a primary input of the last schedule
			if(asd.root->gate.compare("none")==0 || count[asd.root->nodenum]==1){
			signal[asd.root->nodenum]=asd.root->value;	
				//calculating the future schedule for the nodes affected by current change			
				for(int k=0;k<NUM_NODES;k++){
				
					if (adj_matrix[asd.root->nodenum][k]==1){
					tree_node *p = new tree_node();

					p->gate	= gate_list[k];
					p->nodenum=k;
					count[k]=count[k]+1;
					val=computeOutput(p,adj_matrix,signal);
					asd.insert(times+computeDelay(p),p->gate,val,k);		
					}			
				}	
			}
			
			else if(count[asd.root->nodenum]>1 && asd.root->gate.compare("none")!=0 ){
				cout<<"wipe out"<<endl;
			}

			count[asd.root->nodenum]--; //decrement the number of schedules
			asd.remove();
			print_signals(signal,NUM_NODES);
		}

		else{
			//cout<<"nothing now"<<endl;
		}

		update_signal(NUM_NODES,signal,signalmem,times);	

		if(asd.root->T>times || asd.root->T ==-1)
		times=times+1;	//updating time only if there is no node with the same transaction time
	}
			
	/*for(int i=0;i<NUM_NODES;i++){
		for(int j=0;j<times;j++){
			if(signalmem[j][i]==0)
				cout<<"__";		
			else if  (signalmem[j][i]==1)			
				cout<<"**";
			else if  (signalmem[j][i]==-1)			
				cout<<"X";	
		}	
		cout<<endl;
		cout<<endl;	
	}*/	
	
	//writing to a file supported by gtkwave
	write_vcd_file(t0, NUM_NODES, signalmem,"inertial.vcd");
	return 0;
}
