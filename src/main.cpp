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
	











        Chip8 chip8;
	chip8.init();

        std::string rom_name = argv[1];

        chip8.load_fonts();
        chip8.load_rom(rom_name);














        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event event;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, ": Error initializing video subsystem of SDL%s", SDL_GetError());
                return -1;
        }

        window = SDL_CreateWindow("CHIP-8 Emulator",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        1024, 512,
                        SDL_WINDOW_RESIZABLE);


        renderer = SDL_CreateRenderer(window, -1, 0);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);


        uint32_t pixels[64*32];

	int rc = 0;

	int k = 0;

        while (1) {
                chip8.execute_OpCode();
                int i = 0;



		
		if(chip8.display_change_flag == 1) {
		chip8.display_change_flag = 0;
		while(i < 2048) {

			if(chip8.fb[i] == 1){
			pixels[i] = 0xFFFFFF00;
			}
			else {
			pixels[i] = 0x00000000;
			}

			i++;

		}
                SDL_UpdateTexture(texture,
                                NULL,
                                pixels,
                                sizeof(Uint32)*64);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);


		}
    		rc = chip8.update_keyboard_state();

		if(rc == -1) {
			cout << "USER ENTERED QUIT\n";
			break;

		}

		k++;





        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
	
	
	
	
	return 0;

}
