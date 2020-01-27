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

void Chip8::load_fonts() {

	


uint8_t hardcoded_fonts[80] =
{
    		0xF0, 0x90, 0x90, 0x90, 0xF0,  //0
    		0x20, 0x60, 0x20, 0x20, 0x70,  //1
    		0xF0, 0x10, 0xF0, 0x80, 0xF0,  //2
    		0xF0, 0x10, 0xF0, 0x10, 0xF0,  //3
    		0x90, 0x90, 0xF0, 0x10, 0x10,  //4
    		0xF0, 0x80, 0xF0, 0x10, 0xF0,  //5
    		0xF0, 0x80, 0xF0, 0x90, 0xF0,  //6
    		0xF0, 0x10, 0x20, 0x40, 0x40,  //7
    		0xF0, 0x90, 0xF0, 0x90, 0xF0,  //8
    		0xF0, 0x90, 0xF0, 0x10, 0xF0,  //9
    		0xF0, 0x90, 0xF0, 0x90, 0x90,  //A
    		0xE0, 0x90, 0xE0, 0x90, 0xE0,  //B
    		0xF0, 0x80, 0x80, 0x80, 0xF0,  //C
    		0xE0, 0x90, 0x90, 0x90, 0xE0,  //D
    		0xF0, 0x80, 0xF0, 0x80, 0xF0,  //E
    		0xF0, 0x80, 0xF0, 0x80, 0x80   //F
	};



for(int i=0; i < 80; i++) {


	this->memory[i] = hardcoded_fonts[i];


}



}


void Chip8::clear_display_00e0() {



	for(int i = 0; i< 64; i++) {
		for(int j = 0; j < 32; j++) {





			this->fb[i][j] = 0;




		}



	}



}
