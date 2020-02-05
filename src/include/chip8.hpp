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
		uint8_t dt; //delay timer

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

		void ld_Vx_Vy_8xy0(uint8_t x, uint8_t y);
		void or_Vx_Vy_8xy1(uint8_t x, uint8_t y);
		void and_Vx_Vy_8xy2(uint8_t x, uint8_t y);
		void xor_Vx_Vy_8xy3(uint8_t x, uint8_t y);
		void add_Vx_Vy_8xy4(uint8_t x, uint8_t y);
		void sub_Vx_Vy_8xy5(uint8_t x, uint8_t y);
		void shr_Vx_8xy6(uint8_t x);
		void subn_Vx_Vy_8xy7(uint8_t x, uint8_t y);
		void shl_Vx_8xyE(uint8_t x);

		void sne_Vx_Vy_9xxy0(uint8_t x, uint8_t y);
		void ld_I_addr_Annn(uint16_t addr);
		void jp_v0_addr_Bnnn(uint16_t addr);	
		void rnd_Vx_byte_Cxkk(uint8_t x, uint8_t kk);

		void drw_Vx_Vy_nibble_Dxyn(uint8_t x, uint8_t y, uint8_t n); //TODO
		void skp_Vx_Ex9E(uint8_t x); //TODO
		void sknp_Vx_ExA1(uint8_t x); //TODO
		void ld_Vx_dt_Fx07(uint8_t x);
		void ld_Vx_K_Fx0A(uint8_t x); //TODO

		void ld_dt_Vx_Fx15(uint8_t x);
		void ld_st_Vx_Fx18(uint8_t x);
		
		void add_I_Vx_Fx1E(uint8_t x);
		void ld_F_Vx_Fx29(uint8_t x); //TODO
		void ld_B_Vx_Fx33(uint8_t x); //TODO

		void ld_I_Vx_Fx55(uint8_t x);

		Chip8() {};




};



#endif // CHIP8_HPP
