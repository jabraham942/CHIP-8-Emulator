# CHIP-8-Emulator
This program is a CHIP-8 emulator written in C++ which is intended for a Linux-based environment.


*Pong*
![Pong](screenshots/pong.png "Pong")

*Maze*
![Maze](screenshots/maze.png "Maze")

http://en.wikipedia.org/wiki/CHIP-8
> CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine. It was made to allow video games to be more easily programmed for these computers.



## Compilation

Make sure to install SDL2 and cmake:
```
sudo apt-get install libsdl2-dev cmake 
```

Compile the emulator:
```
- mkdir build_dir
- cd build_dir
- cmake ..
- make
```

## Execution
```
./chip8_emulator <CHIP-8 ROM file>
```

Various CHIP-8 ROMs can be found at the following link:
- https://github.com/dmatlack/chip8/tree/master/roms

## References
I used the following helpful resource while writing this emulator.
- http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
