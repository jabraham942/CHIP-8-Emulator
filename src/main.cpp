#include "include/chip8.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << "Wrong number of arguments\n";

		return -1;
	}

	


	Chip8 chip8;
	std::string rom_name = argv[1];

	chip8.load_rom(rom_name);
	

	return 0;

}
