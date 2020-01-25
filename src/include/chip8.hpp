#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>

class Chip8 {

	private:
		unsigned short opcode;
		unsigned char memory[4096];


	public:

		int load_rom(std::string rom_name);



		Chip8() {};




};



#endif // CHIP8_HPP
