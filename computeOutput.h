/* 
Author: Sneha Goenka
17th October 2015
CAD Project: Logic Simulation
*/

//function to calculate the output of a particular node(gate) and return the signal value computed

#include <string>
#include <stdio.h>
using namespace std;

struct node{
	string logic;	//logic name
	int delay;	//delay associated with each node
	//int srno;	//serial number 
};

//inputs - srno - serial number of the node
//inputs - adj_matrix - adjacency Matrix 
int computeOutput(int srno,node p,vector<vector<int> > &adj_matrix, std::vector<int>& signal){ 
	int out,i,N=0;
	N=adj_matrix[0].size();

	if(p.logic.compare("and")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
			//in case th value is don't care the output will also be don't care				
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =out & signal[i];	
			}		
		}	
	}
	
	else if(p.logic.compare("or")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =out | signal[i];	
				//printf("%d %d %d \n",i,signal[i],out);
			}
		}	
	}

	else if(p.logic.compare("nand")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =out | !signal[i];	
			}		
		}	
	}

	else if(p.logic.compare("nor")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =out & !signal[i];	
			}		
		}	
	}

	else if(p.logic.compare("xor")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =(out & !signal[i]) | (!out & signal[i]);	
			}  		
		}	
	}

	else if(p.logic.compare("not")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else
				  out =!signal[i];	
			}	 		
		}	
	}

	else{
		printf("%s \n" ,"gate not found in the default list");	
	}

	return out;				
}

