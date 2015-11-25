/* 
Author: Sneha Goenka
17th October 2015
Computing the output at each time instant
*/

//function to calculate the output of a particular node(gate) and return the signal value computed

#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "priority_queue.cpp"

using namespace std;

//inputs - srno - serial number of the node
//inputs - adj_matrix - adjacency Matrix 
int computeOutput(tree_node *p,vector<vector<int> > &adj_matrix, std::vector<int>& signal){ 
	int out,i,N=0;
	N=adj_matrix[0].size();
	int srno = p->nodenum;
	if((p->gate).compare("and")==0){
		
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
	//in case the value is don't care the output will also be don't care 				
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
	
	else if(p->gate.compare("or")==0){
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
			}
		}	
	}

	else if(p->gate.compare("nand")==0){
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

	else if(p->gate.compare("nor")==0){
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

	else if(p->gate.compare("xor")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				  out =-1;
				  i=N;
				  break;
				}
				else{
				  out =(out & !signal[i]) | (!out & signal[i]);	
				}  	
			}		
		}	
	}

	else if(p->gate.compare("not")==0){
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
