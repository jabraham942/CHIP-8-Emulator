#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>
#include <stack>
#include <cstdint>

class Chip8 {

	private:
		uint16_t opcode;

		uint8_t V_reg[16];
		uint16_t I_reg;

		
		uint8_t sp; //stack pointer
		//uint8_t stack[64];
		std::stack <uint8_t> stack_struct;
		uint8_t st; //sound timer
		uint16_t pc; //program cointer

		uint8_t fb[64][32]; //64x32 frame buffer

		uint8_t memory[4096];


	public:

		int load_rom(std::string rom_name);
		void load_fonts();
		
		void clear_display_00e0();
		void subroutine_return_00ee();
		
		void jp_addr_1nnn(uint16_t addr);
		void call_addr_2nnn(uint16_t addr);
		
		void se_Vx_byte_3xkk(uint8_t x, uint8_t kk);
		void sne_Vx_byte_4xkk(uint8_t x, uint8_t kk);
		void se_Vx_Vy_5xy0(uint8_t x, uint8_t y);
		
		void ld_Vx_byte_6xkk(uint8_t x, uint8_t kk);
		void add_Vx_byte_7xkk(uint8_t x, uint8_t kk);



		Chip8() {};




};



#endif // CHIP8_HPP
