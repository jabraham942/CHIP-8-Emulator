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



void Chip8::subroutine_return_00ee() {


	if (this->stack_struct.size() == 0) {


		cout << "Stack is empty. Returning from function call\n";
	
		return;
	}	
	this->pc = this->stack_struct.top();
	this->sp--;




}




void Chip8::jp_addr_1nnn(uint16_t addr ) {


	this->pc = addr & 0x0FFF;


	cout << "Jumped to address " + std::to_string(this->pc) + "\n";
}



void Chip8::call_addr_2nnn(uint16_t addr ) {

	this->sp++;

	this->stack_struct.push(this->pc);

	this->pc = addr & 0x0FFF;


	cout << "Called subroutine at address " + std::to_string(this->pc) + "\n";	


}


void Chip8::se_Vx_byte_3xkk(uint8_t x, uint8_t kk) {
	cout << "Checking if V_reg_x has value kk\n";
	if(this->V_reg[x] == kk) {
	
		this->pc += 1;	
	}


}



void Chip8::sne_Vx_byte_4xkk(uint8_t x, uint8_t kk) {
        cout << "Checking if V_reg_x does not have value kk\n";
        if(this->V_reg[x] != kk) {

        	this->pc += 1;
        }


}


void Chip8::se_Vx_Vy_5xy0(uint8_t x, uint8_t y) {

	cout << "Checking if V_x and V_y have same value\n";


	if(this->V_reg[x] == this->V_reg[y]) {


		this->pc += 1;


	}





}



void Chip8::ld_Vx_byte_6xkk(uint8_t x, uint8_t kk) {


	cout << "Setting V_x to value kk\n";


	this->V_reg[x] = kk;


}





void Chip8::add_Vx_byte_7xkk(uint8_t x, uint8_t kk)  {



	cout << "Adding kk to Vx\n";


	this->V_reg[x] += kk;



}



void Chip8::ld_Vx_Vy_8xy0(uint8_t x, uint8_t y) {


	cout << "Storing Vy in Vx\n";



	this->V_reg[x] = this->V_reg[y];



}



void Chip8::or_Vx_Vy_8xy1(uint8_t x, uint8_t y) {


	cout << "Storing (Vx or Vy) in Vx\n";

	this ->V_reg[x] |= this->V_reg[y];


}



void Chip8::and_Vx_Vy_8xy2(uint8_t x, uint8_t y) {


	cout << "Storing (Vx and Vy) in Vx\n";


	this->V_reg[x] &= this->V_reg[y];




}





void Chip8::xor_Vx_Vy_8xy3(uint8_t x, uint8_t y) {


	cout << "Storing (Vx XOR Vy) in Vx\n";


	this->V_reg[x] ^=this->V_reg[y];



}



void Chip8::add_Vx_Vy_8xy4(uint8_t x, uint8_t y) {


	cout << "Storing (Vx + Vy) in Vx\n";




	uint16_t tmp = this->V_reg[x] + this->V_reg[y];

	this->V_reg[x] = (uint8_t) tmp & 0x0FF; //Lower 8 bits of result
	this->V_reg[15] = (uint8_t) ((tmp &  0x100) >> 8); //Set VF = Overflow


	cout << "Added value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";


}



void Chip8::sub_Vx_Vy_8xy5(uint8_t x, uint8_t y) {



	cout << "Storing (Vx - Vy) in Vx\n";

	if(this->V_reg[x] < this->V_reg[y]) {

		this->V_reg[15] = 1;

	}
	else {

		this->V_reg[15] = 0;

	}

	this->V_reg[x] -= this->V_reg[y];

	cout << "Subtracted value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";
}




void Chip8::shr_Vx_8xy6(uint8_t x) {

	cout << "Storing Vx = Vx SHR 1\n";


	if(this->V_reg[x] & 0x01) {


		this->V_reg[15] = 1;
	}
	else {

		this->V_reg[15] = 0;
	}

	
	this->V_reg[x] = this->V_reg[x] >> 1;

}





void Chip8::subn_Vx_Vy_8xy7(uint8_t x, uint8_t y) {






	        cout << "Storing (Vy - Vx) in Vx\n";

        if(this->V_reg[y] < this->V_reg[x]) {

                this->V_reg[15] = 1;

        }
        else {

                this->V_reg[15] = 0;

        }

        this->V_reg[x] = this->V_reg[y] - this->V_reg[x];

        cout << "Subtracted value = " + std::to_string(this->V_reg[x]) + " and VF = " + std::to_string(this->V_reg[15]) + "\n";


	



}







void Chip8::shl_Vx_8xyE(uint8_t x) {


	cout << "Shift left 1 for Vx.\n";



        if(this->V_reg[x] & 0x80) {


                this->V_reg[15] = 1;
        }
        else {

                this->V_reg[15] = 0;
        }


        this->V_reg[x] = this->V_reg[x] << 1;






}







void Chip8::sne_Vx_Vy_9xxy0(uint8_t x, uint8_t y) {


	
        cout << "Checking if V_x and V_y have different values\n";


        if(this->V_reg[x] != this->V_reg[y]) {


                this->pc += 1;


        }







}
