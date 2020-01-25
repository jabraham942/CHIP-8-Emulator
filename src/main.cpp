#include "include/chip8.hpp"
#include <string>

using namespace std;

int main(int argc, char **argv) {
	
	
	Chip8 chip8;
	std::string test_string = "Fake_ROM123";

	chip8.load_rom(test_string);
	

	return 0;

}
