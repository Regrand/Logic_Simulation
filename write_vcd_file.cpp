
// Write singalmem to a gtkwave supported file format (vcd)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void write_vcd_file (int simulation_time, int NUM_NODES, vector<vector<int> > &signalmem,string name) {

	
	ofstream writefile;
  	writefile.open (name);
  	
	writefile << "$timescale 1ps $end" <<endl;
	writefile << "$scope module logic_simulation_project $end" <<endl;

	// Declare variables
	for (int i=0; i<NUM_NODES; i++){

		writefile << "$var wire 1 *" << std::to_string(i) << " node" << std::to_string(i) << " $end" <<endl;
	
	}
	
	writefile << "$upscope $end" <<endl;
	writefile << "$enddefinitions $end" <<endl;
	
	//Initialise all variables
	writefile << "$dumpvars" <<endl;
	for (int i=0; i<NUM_NODES; i++){

		writefile << "x*" << std::to_string(i) << endl;
	
	}
	writefile << "$end" <<endl;
	
	//Now set variables at each time instant
	for (int t=0; t<simulation_time; t++){
		
		writefile << "#" << std::to_string(t) <<endl;
		for (int i=0; i<NUM_NODES; i++){

			int temp = signalmem[t][i];
			// Dont care is a -1
			if(signalmem[t][i]==-1){
				writefile << "x*" << std::to_string(i) <<endl;
			}
			else{
				writefile << to_string(temp) << "*" << std::to_string(i) <<endl;
			}
		}
	}
	
	writefile.close();
  	return;
}	
