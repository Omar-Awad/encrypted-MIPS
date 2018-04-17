#include "systemc.h"
SC_MODULE(MEM){
sc_in<bool> clk;
sc_in<sc_lv<3>> pc; //4 instructions (from cell 1 to 4)
sc_in<sc_lv<5>> mem_addr; //addr for read/write in mem
sc_in<sc_lv<128>> mem_wb;
sc_in<bool> w_r, inst_data; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
sc_out<sc_lv<128>> mem_out;
sc_lv<128> myMem[32];

void mem_func(){
	if(clk.event() && clk)
		if(inst_data == 1)
			mem_out = myMem[(sc_uint<3>)pc];
		else if(w_r == 1)
			myMem[(sc_uint<5>)mem_addr] = mem_wb;
		else
			mem_out = myMem[(sc_uint<5>)mem_addr];
}

SC_CTOR(MEM){
	// initialize myMem here
	myMem[0] = 0x0000000;
	myMem[1] = 0x0000000;
	myMem[2] = 0x0000000;
	myMem[3] = 0x0000000;
	myMem[4] = 0x0000000;
	myMem[5] = 0x0000003;
	myMem[6] = 0x0000002;
	myMem[7] = 0x0000005;
	myMem[8] = 0x0000008;

SC_METHOD(mem_func);
sensitive << clk.pos();
}
};