/*#include "systemc.h"
#include <iostream>
int sc_main(int argc, char* argv[]){
	sc_lv<8> x = 0x03;
	sc_lv<8> y;

    y = ((x<<1) ^ (((x>>7) & 1) ^ 0x1b));

	cout <<y;

sc_start();
return 0;
}*/