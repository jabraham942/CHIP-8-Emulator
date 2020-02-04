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
	
	chip8.load_fonts();
	chip8.load_rom(rom_name);
	chip8.clear_display_00e0();	
	chip8.subroutine_return_00ee();
	chip8.jp_addr_1nnn(0x1FEF);
	chip8.call_addr_2nnn(0x12FA);

	chip8.se_Vx_byte_3xkk(4, 0x43);
	chip8.sne_Vx_byte_4xkk(7,0x8F);
	chip8.se_Vx_Vy_5xy0(4,8);
	chip8.ld_Vx_byte_6xkk(3,0x32);

	chip8.add_Vx_byte_7xkk(5,0x24);


	return 0;

}
