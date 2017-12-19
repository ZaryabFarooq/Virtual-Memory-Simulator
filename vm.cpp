#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class RAM {

public:
	unsigned long address;
	bool use;
	RAM(){
		address = 0;
		use = 0;
	}
};



int main(int argc, char* args[]){
	ifstream infile;
	ofstream out;

	infile.open(args[1]);
	out.open("vm-out.txt");

	RAM ram[32];
	
	unsigned long address;
	
	for (int i = 0; i < 32; i++){	// don't need first 32 addresses
		infile >> hex >> address;
	}

	int pos, current = 0;
	
	while(infile >> hex >> address){
		address = (address >> 10);
		address = address << 10;

		pos = 10;
		// Find address in the frame
		for (int i = 0; i < 4; i++){
			if (ram[i].address == address){
				pos = i;
				break;
			}
			pos = 10; // if address not in RAM, then return any number
		}
		
		if(pos == 10){ 	//if miss 
			if(!ram[current].use){	// if use bit not true
				ram[current].address = address;
				ram[current].use = true;
				current++;
				current = current % 4;
			}

			else{	// if use bit true
				while(ram[current].use){
					ram[current].use = false;
					current++;
					current = current % 4;
				}

				ram[current].address = address;
				ram[current].use = true;
				current++;
				current = current % 4;
			}
		}

		else{	//if hit
			ram[pos].use = true;
			// no need to incrememt current pointer
		}

		// Print
		for (int i = 0; i < 4; i++){
			if (ram[i].address != 0){
				if (i == 0){
					out << hex << ram[i].address;
				} 
				else {
					out << " " <<  hex << ram[i].address;
				}
			}
		}
		out << endl;

	}

	infile.close();
	out.close();
	
	return 0;
}
