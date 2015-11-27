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
				  out =p->value;
				}
				else{
				  out =out & signal[i];	
				  p->value=out;
				}
			}		
		}	
	}
	
	else if(p->gate.compare("or")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				 out =p->value;
				}
				else{
				  out =out | signal[i];	
				  p->value=out;
				}
			}
		}	
	}

	else if(p->gate.compare("nand")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				
				}
				else{
				  out =out | !signal[i];	
				  p->value=out;
				}
			//cout<<"in nand for node" << srno<<" with input node "<<i<<"which has value of "<<signal[i]<<" with out as "<<out<<endl;
			}
			
					
		}	
	}

	else if(p->gate.compare("nor")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				 out =p->value;
				}
				else{
				  out =out & !signal[i];	
				  p->value=out;
				}	
			}		
		}	
	}

	else if(p->gate.compare("xor")==0){
		out=0;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				 out =p->value;
				}
				else{
				  out =(out & !signal[i]) | (!out & signal[i]);
				  p->value=out;
				}  	
			}		
		}	
	}

	else if(p->gate.compare("not")==0){
		out=1;
		for(i=0;i<N;i++){
			if(adj_matrix[i][srno]==1){
				if(signal[i]==-1){
				 out =p->value;
				}
				else{
				  out =!signal[i];	
				  p->value=out;
				}

			}	 		
		}	
	}

	//if the input is a primary input with no gate; computation means the calue of the node is the input signal value
	else if(p->gate.compare("none")==0){
		out=p->value;
	}


	else{
		printf("%s \n" ,"gate not found in the default list");	
	}

	return out;				
}

int computeDelay(tree_node *p){ 
	int out,i,N=0;
	
	if((p->gate).compare("and")==0){		
		out=5;
	}
	
	else if(p->gate.compare("or")==0){
		out=6;
	}

	else if(p->gate.compare("nand")==0){
		out=6;	
	}

	else if(p->gate.compare("nor")==0){
		out=3;
	}

	else if(p->gate.compare("xor")==0){
		out=8;
	}

	else if(p->gate.compare("not")==0){
		out=6;
	}

	else{
		printf("%s \n" ,"gate not found in the default list");	
	}

	return out;				
}
