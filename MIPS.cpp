#include "MIPS.h"

void MIPS::inc_pc(){
if(reset)
	pc = 0;
else if(clk.event() && clk)
	pc = pc + 1;
}