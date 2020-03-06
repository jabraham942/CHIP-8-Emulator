#include "chip8.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "SDL2/SDL.h"

using namespace std;


uint8_t keyboard_map[16] = {
    	SDLK_1,
    	SDLK_2,
    	SDLK_3,
    	SDLK_4,
    	SDLK_q,
   	SDLK_w,
    	SDLK_e,
    	SDLK_r,
    	SDLK_a,
    	SDLK_s,
    	SDLK_d,
    	SDLK_f,
    	SDLK_z,
    	SDLK_x,
    	SDLK_c,
    	SDLK_v,
};



int Chip8::init() {
this->pc = 0x200;
this->sp = 0;
this->I_reg = 0;
this->opcode = 0;
this->dt = 0;

    for (int i = 0; i < 16; i++) {
        this->V_reg[i] = 0;
	this->stack[i] = 0;
        this->keyboard[i] = 0;
    }


}
int Chip8::load_rom(std::string rom_name) {

	//cout << "Rom name is " + rom_name + "\n";
	
	ifstream rom_fh(rom_name, ios::in | ios::binary);
	
	if (rom_fh.fail()) {


		//cout << "There was an error opening ROM. Exiting\n";
		return -1;

	}



	rom_fh.seekg(0,std::ios_base::end);

	int rom_size = rom_fh.tellg();

	rom_fh.seekg (0, std::ios_base::beg);


	if (rom_size > 4096 - 512) {

		//cout << "ROM size is too large to store in memory\n";
		return -1;	
	}

	char * buffer = new char[rom_size];

	rom_fh.read(buffer, rom_size);



	for(int i=0;i< rom_size;i++) {


		this->memory[512+i] = buffer[i];


	}
	 

	//cout << "Stored " + std::to_string(rom_size) + " bytes into memory.\n";


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




void Chip8::execute_OpCode(){
	//SDL_Delay(5);	
	uint16_t opcode = this->opcode = (this->memory[this->pc] << 8) | this->memory[this->pc+1];

	//cout << "PC is at " + std::to_string(this->pc) + "\n";
	//cout << "OPCODE is " + std::to_string(opcode) + "\n";



	switch(0xF000 & (opcode)) {
		
		case 0x0000:
			switch(opcode) {
			case 0x00E0:
				clear_display_00e0();
				this->display_change_flag = 1;
				break;
			case 0x00EE:
		 		subroutine_return_00ee();	
				break;
			default:
				break;
			}
			break;
		case 0x1000:
			jp_addr_1nnn(0x0FFF & opcode);
			break;
		case 0x2000:
			call_addr_2nnn(0x0FFF & opcode);
			break;
		case 0x3000:

			se_Vx_byte_3xkk((0x0F00 & opcode) >> 8, 0x00FF & opcode);
			break;
		case 0x4000:
			sne_Vx_byte_4xkk((0x0F00 & opcode) >> 8, 0x00FF & opcode);
			break;
		case 0x5000:
			se_Vx_Vy_5xy0((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
			break;
		case 0x6000:
			ld_Vx_byte_6xkk((0x0F00 & opcode) >> 8, 0x00FF & opcode);
			break;
		case 0x7000:
			add_Vx_byte_7xkk((0x0F00 & opcode) >> 8, 0x00FF & opcode);
			break;
		case 0x8000:
			switch(0x000F & opcode) {
			
				case 0:
					ld_Vx_Vy_8xy0((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 1:
					or_Vx_Vy_8xy1((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 2:
					and_Vx_Vy_8xy2((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 3:
					xor_Vx_Vy_8xy3((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 4:
				       	add_Vx_Vy_8xy4((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);					       break;
				case 5:
					sub_Vx_Vy_8xy5((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 6:
					shr_Vx_8xy6((0x0F00 & opcode) >> 8);
					break;
				case 7:
					subn_Vx_Vy_8xy7((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
					break;
				case 0xE:
					shl_Vx_8xyE((0x0F00 & opcode) >> 8);
					break;
			}	
			break;


		case 0x9000:
			sne_Vx_Vy_9xy0((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4);
			break;
		case 0xA000:
			ld_I_addr_Annn(0x0FFF & opcode);
			break;
		case 0xB000:
			jp_v0_addr_Bnnn(0x0FFF & opcode);
			break;
		case 0xC000:
			rnd_Vx_byte_Cxkk((0x0F00 & opcode) >> 8, 0x00FF & opcode);
			break;
		case 0xD000:
			drw_Vx_Vy_nibble_Dxyn((0x0F00 & opcode) >> 8, (0x00F0 & opcode) >> 4, 0x000F & opcode);
			this->display_change_flag = 1;
			break;
		case 0xE000:
			switch(0x00FF & opcode) {

				case 0x9E:
					skp_Vx_Ex9E((0x0F00 & opcode) >> 8);
					break;
				case 0xA1:
					sknp_Vx_ExA1((0x0F00 & opcode) >> 8);
					break;

			}

			break;
		case 0xF000:
			switch(0x00FF & opcode) {

				case 0x7:
					ld_Vx_dt_Fx07((0x0F00 & opcode) >> 8);
					break;
				case 0x0A:
					ld_Vx_K_Fx0A((0x0F00 & opcode) >> 8);
					break;
				case 0x15:
					ld_dt_Vx_Fx15((0x0F00 & opcode) >> 8);
					break;
				case 0x18:
					ld_st_Vx_Fx18((0x0F00 & opcode) >> 8);
					break;
				case 0x1E:
					add_I_Vx_Fx1E((0x0F00 & opcode) >> 8);
					break;
				case 0x29:
					ld_F_Vx_Fx29((0x0F00 & opcode) >> 8);
					break;
				case 0x33:
					ld_B_Vx_Fx33((0x0F00 & opcode) >> 8);
					break;
				case 0x55:
					ld_I_Vx_Fx55((0x0F00 & opcode) >> 8);
					break;
				case 0x65:
					ld_Vx_I_Fx65((0x0F00 & opcode) >> 8);
					break;






			}
			break;


		











	}

	if(this->dt > 0) {

		this->dt--;

	}

	this->pc += 2;



}








void Chip8::clear_display_00e0() {

	//cout << "Clearing display\n";



	for(int i=0;i<2048;i++) {

		this->fb[i] = 0;

	}



}



void Chip8::subroutine_return_00ee() {

	this->sp--;	
	this->pc = this->stack[this->sp];

	//cout << "Returning from subroutine and setting PC to " + std::to_string(this->pc) + "\n";


}




void Chip8::jp_addr_1nnn(uint16_t addr ) {


	this->pc = (addr & 0x0FFF) - 2; //subtracting 2 to account for adding of pc at end of execute_cycle loop


	//cout << "Jumped to address " + std::to_string(this->pc) + "\n";
}



void Chip8::call_addr_2nnn(uint16_t addr ) {


	this->stack[this->sp] = this->pc;


	this->pc = (addr & 0x0FFF) - 2; //subtracting 2 to account for adding 2 at end of execute_cycle

	this->sp++;
	//cout << "Called subroutine at address " + std::to_string(this->pc) + "\n";	


}


void Chip8::se_Vx_byte_3xkk(uint8_t x, uint8_t kk) {
	//cout << "Checking if V_reg_x has value kk\n";
	//cout << "V_reg_x, kk : " + std::to_string(this->V_reg[x]) + "," + std::to_string(kk) + "\n";
	if(this->V_reg[x] == kk) {
	
		this->pc += 2;	
	}


}



void Chip8::sne_Vx_byte_4xkk(uint8_t x, uint8_t kk) {
        //cout << "Checking if V_reg_x does not have value kk\n";
        if(this->V_reg[x] != kk) {

        	this->pc += 2;
        }


}


void Chip8::se_Vx_Vy_5xy0(uint8_t x, uint8_t y) {

	//cout << "Checking if V_x and V_y have same value\n";


	if(this->V_reg[x] == this->V_reg[y]) {


		this->pc += 2;


	}





}



void Chip8::ld_Vx_byte_6xkk(uint8_t x, uint8_t kk) {


	//cout << "Setting V_x to value kk\n";


	this->V_reg[x] = kk;


}





void Chip8::add_Vx_byte_7xkk(uint8_t x, uint8_t kk)  {



	//cout << "Adding kk to Vx\n";


	this->V_reg[x] += kk;



}



void Chip8::ld_Vx_Vy_8xy0(uint8_t x, uint8_t y) {


	//cout << "Storing Vy in Vx\n";



	this->V_reg[x] = this->V_reg[y];



}



void Chip8::or_Vx_Vy_8xy1(uint8_t x, uint8_t y) {


	//cout << "Storing (Vx or Vy) in Vx\n";

	this ->V_reg[x] |= this->V_reg[y];


}



void Chip8::and_Vx_Vy_8xy2(uint8_t x, uint8_t y) {


	//cout << "Storing (Vx and Vy) in Vx\n";


	this->V_reg[x] &= this->V_reg[y];




}





void Chip8::xor_Vx_Vy_8xy3(uint8_t x, uint8_t y) {


	//cout << "Storing (Vx XOR Vy) in Vx\n";


	this->V_reg[x] ^=this->V_reg[y];



}



void Chip8::add_Vx_Vy_8xy4(uint8_t x, uint8_t y) {


	//cout << "Storing (Vx + Vy) in Vx\n";




	uint16_t tmp = this->V_reg[x] + this->V_reg[y];

	this->V_reg[x] = (uint8_t) tmp & 0x0FF; //Lower 8 bits of result
	this->V_reg[15] = (uint8_t) ((tmp &  0x100) >> 8); //Set VF = Overflow


	//cout << "Added value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";


}



void Chip8::sub_Vx_Vy_8xy5(uint8_t x, uint8_t y) {



	//cout << "Storing (Vx - Vy) in Vx\n";

	if(this->V_reg[x] < this->V_reg[y]) {

		this->V_reg[15] = 0;

	}
	else {

		this->V_reg[15] = 1;

	}

	this->V_reg[x] -= this->V_reg[y];

	//cout << "Subtracted value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";
}




void Chip8::shr_Vx_8xy6(uint8_t x) {

	//cout << "Storing Vx = Vx SHR 1\n";


	if(this->V_reg[x] & 0x01) {


		this->V_reg[15] = 1;
	}
	else {

		this->V_reg[15] = 0;
	}

	
	this->V_reg[x] = this->V_reg[x] >> 1;

}





void Chip8::subn_Vx_Vy_8xy7(uint8_t x, uint8_t y) {






	        //cout << "Storing (Vy - Vx) in Vx\n";

        if(this->V_reg[y] < this->V_reg[x]) {

                this->V_reg[15] = 0;

        }
        else {

                this->V_reg[15] = 1;

        }

        this->V_reg[x] = this->V_reg[y] - this->V_reg[x];

        //cout << "Subtracted value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";


	



}







void Chip8::shl_Vx_8xyE(uint8_t x) {


	//cout << "Shift left 1 for Vx.\n";



        if(this->V_reg[x] & 0x80) {


                this->V_reg[15] = 1;
        }
        else {

                this->V_reg[15] = 0;
        }


        this->V_reg[x] = this->V_reg[x] << 1;






}







void Chip8::sne_Vx_Vy_9xy0(uint8_t x, uint8_t y) {


	
        //cout << "Checking if V_x and V_y have different values\n";


        if(this->V_reg[x] != this->V_reg[y]) {


                this->pc += 2;


        }







}



void Chip8::ld_I_addr_Annn(uint16_t addr) {



	//cout << "Loading addr in I\n";



	this->I_reg = addr;






}



void Chip8::jp_v0_addr_Bnnn(uint16_t addr) {


	//cout << "Setting PC to V0 + addr\n";

	this->pc = addr + this->V_reg[0];




}





void Chip8::rnd_Vx_byte_Cxkk(uint8_t x, uint8_t kk) {


	//cout << "Setting Vx to random byte and kk\n";


	this->V_reg[x] = kk & (rand() % 0xFF);



}




void Chip8::drw_Vx_Vy_nibble_Dxyn( uint8_t x, uint8_t y, uint8_t n) {
	
	uint16_t start_memory = this->I_reg;
	uint8_t byte_row = 0;

	x = this->V_reg[x];
	y = this->V_reg[y];

	//cout << "Drawing n-byte sprite at memory location I, coordinate x,y (" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(n) + "," + std::to_string(start_memory) + ")\n";
	
	for (int i=0;i<n;i++) {
		
		
			
		byte_row = this->memory[start_memory+i];

		for (int j=0;j<8;j++) {


			if(this->fb[((x+j)) + ((y+i))*64] == 1) {
				this->V_reg[15] = 1;


			}
			


			this->fb[ ((x+j)) + ((y+i))*64 ] ^= (byte_row & (1 << (7-j))) >> (7-j);

		}
		
	}



}

int Chip8::update_keyboard_state() {
	SDL_Delay(5);
	//1234  =>  0123
	//qwer  =>  4567
	//asdf  =>  89AB
	//zxcv	=>  CDEF








SDL_Event e;


                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_KEYDOWN )
                    {	

			for(int i=0;i<16;i++) {

				if(e.key.keysym.sym == keyboard_map[i]) {

					//cout << "Key " + std::to_string(i) + " was pressed.\n";
					this->keyboard[i] = 1;
						
				}

			}
                    }
		    else  if(e.type == SDL_KEYUP) {


                        for(int i=0;i<16;i++) {

                                if(e.key.keysym.sym == keyboard_map[i]) {

                                        //cout << "Key " + std::to_string(i) + " was released.\n";
                                        this->keyboard[i] = 0;

                                }

                        }
                    }




		    
		    else if(e.type == SDL_QUIT) {

			return -1;	

		    }

		}

	return 0;
		
}	


void Chip8::skp_Vx_Ex9E(uint8_t x) {    


	//cout << "Skip next instruction if key with value " + std::to_string(this->V_reg[x]) + " is pressed\n";


	//this->check_keyboard(); REPLACE THIS

	if(this->keyboard[this->V_reg[x]] == 1) {
		this->pc += 2;

	}
	else {

		//cout << "0xEX9E: KEY " + std::to_string(this->V_reg[x]) + " IS PRESSED\n";
	}
}


void Chip8::sknp_Vx_ExA1(uint8_t x) {

	//cout << "Skip next instruction if key with value " + std::to_string(this->V_reg[x]) +" is not pressed\n";


        //this->check_keyboard(); REPLACE THIS

        if(this->keyboard[this->V_reg[x]] == 0) {
                this->pc += 2;

	}
	else {

		//cout << "0xEXA1: KEY " + std::to_string(this->V_reg[x]) + " IS PRESSED\n";
	}





}






void Chip8::ld_Vx_dt_Fx07(uint8_t x) {



	//cout << "Load delay timer value into Vx: " + std::to_string(this->dt) +"\n";




	this->V_reg[x] = this->dt;






}


void Chip8::ld_Vx_K_Fx0A(uint8_t x) {  


	//cout << "Waiting for key press\n";








		SDL_Event e;

		uint8_t key_pressed = 0;

		while(!key_pressed)
                {
                    //User presses a key
		    while( SDL_PollEvent( &e ) != 0 && (!key_pressed)) {
                    if( e.type == SDL_KEYDOWN )
                    {  
			
			this->V_reg[x] = e.key.keysym.sym;
			key_pressed = 1;
			

                    }

		    }

                }






























}






void Chip8::ld_dt_Vx_Fx15(uint8_t x) {


	//cout << "Storing value of Vx in delay timer\n";



	this->dt = this->V_reg[x];
	//cout << "DT HAS VALUE: " + std::to_string(this->dt) + "\n";

}





void Chip8::ld_st_Vx_Fx18(uint8_t x) {

	//cout << "Storing value of Vx in sound timer\n";


	this->st = this->V_reg[x];




}


void Chip8::add_I_Vx_Fx1E(uint8_t x) {


	//cout << "Storing I = I + Vx\n";




	this->I_reg += this->V_reg[x];



}



void Chip8::ld_F_Vx_Fx29(uint8_t x) {


	//cout << "Set I = location of sprite for digit Vx\n";


	this->I_reg = V_reg[x] * 5; 

}




void Chip8::ld_B_Vx_Fx33(uint8_t x) {

	//cout << "Store BCD representation of Vx in memory locations I, I+1, and I+2\n";

	uint8_t num;
	this->memory[this->I_reg] =      num / 100;
	this->memory[this->I_reg + 1] = (num % 100) / 10;
	this->memory[this->I_reg + 2] = ((num % 100) % 10);



}




void Chip8::ld_I_Vx_Fx55(uint8_t x) {

	//cout << "Stores V0 to Vx in memory address starting at I\n";

	uint16_t I_start = this->I_reg;
	
	for(int i=0; i<x+1;i++) {

		this->memory[I_start] = this->V_reg[i];
		I_start++;


	}






}




void Chip8::ld_Vx_I_Fx65(uint8_t x) {



        //cout << "Stores into V0 to Vx values in memory address starting at I\n";
	
	uint16_t I_start = this->I_reg;
        for(int i=0; i<x+1;i++) {

                this->V_reg[i] = this->memory[I_start];

               	I_start++;


        }






}
