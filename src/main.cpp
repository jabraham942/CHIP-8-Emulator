#include "include/chip8.hpp"
#include <string>
#include <iostream>
#include "SDL2/SDL.h"



using namespace std;

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << "Wrong number of arguments\n";

		return -1;
	}
	






	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

		cout << "Error initializing SDL library\n";



	}


	SDL_Window* window = SDL_CreateWindow("CHIP-8-Emulator",
					      SDL_WINDOWPOS_CENTERED,
					      SDL_WINDOWPOS_CENTERED,
					      900,900,0);




	


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
	chip8.ld_Vx_Vy_8xy0(3,4);
	
	chip8.or_Vx_Vy_8xy1(5,6);
	chip8.and_Vx_Vy_8xy2(2,3);
	
	chip8.xor_Vx_Vy_8xy3(3,7);
	
	cout << "-------------------\n";	
	chip8.ld_Vx_byte_6xkk(1,0xFF);
	chip8.ld_Vx_byte_6xkk(2,0xFF);
	
	chip8.ld_Vx_byte_6xkk(3,13);
        chip8.ld_Vx_byte_6xkk(4,24);




	chip8.add_Vx_Vy_8xy4(1,2);
	chip8.subn_Vx_Vy_8xy7(3,4);


	cout << "--------------------\n";

	chip8.shr_Vx_8xy6(2);
	
	chip8.shl_Vx_8xyE(4);

	chip8.sne_Vx_Vy_9xxy0(2,4);	

	chip8.ld_I_addr_Annn(0x149);
	chip8.jp_v0_addr_Bnnn(0x593);
	chip8.rnd_Vx_byte_Cxkk(2,0x43);

	chip8.drw_Vx_Vy_nibble_Dxyn(1,2,5);	
	chip8.skp_Vx_Ex9E(1);
	chip8.sknp_Vx_ExA1(4);
	chip8.ld_Vx_dt_Fx07(3);
	chip8.ld_Vx_K_Fx0A(4);
	chip8.ld_dt_Vx_Fx15(3);
	chip8.ld_st_Vx_Fx18(6);
	chip8.add_I_Vx_Fx1E(2);
	chip8.ld_F_Vx_Fx29(5);
	chip8.ld_B_Vx_Fx33(3);
	chip8.ld_I_Vx_Fx55(6);
	chip8.ld_Vx_I_Fx65(7);
	return 0;

}
