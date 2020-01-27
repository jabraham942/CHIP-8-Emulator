#include "chip8.hpp"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;



int Chip8::load_rom(std::string rom_name) {

	cout << "Rom name is " + rom_name + "\n";
	
	ifstream rom_fh(rom_name, ios::in | ios::binary);
	
	if (rom_fh.fail()) {


		cout << "There was an error opening ROM. Exiting\n";
		return -1;

	}



	rom_fh.seekg(0,std::ios_base::end);

	int rom_size = rom_fh.tellg();

	rom_fh.seekg (0, std::ios_base::beg);


	if (rom_size > 4096 - 512) {

		cout << "ROM size is too large to store in memory\n";
		return -1;	
	}

	char * buffer = new char[rom_size];

	rom_fh.read(buffer, rom_size);



	for(int i=0;i< rom_size;i++) {


		this->memory[512+i] = buffer[i];



	}
	 

	cout << "Stored " + std::to_string(rom_size) + " bytes into memory.\n";


	return 0;





}
