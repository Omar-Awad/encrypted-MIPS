#include "systemc.h"
SC_MODULE(MEM){
sc_in<bool> clk;
sc_in<sc_uint<2>> pc; //4 instructions
sc_in<sc_uint<5>> mem_addr; //addr for read/write in mem
sc_in<sc_lv<128>> mem_wb;
sc_in<bool> w_r, inst_data; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
sc_out<sc_lv<128>> mem_out;
sc_lv<128> myMem[32]; // initialize it hear
void mem_func(){
	if(clk.event() && clk)
		if(inst_data == 1)
			mem_out = myMem[pc.read()];
		else if(w_r == 1)
			myMem[mem_addr.read()] = mem_wb;
		else
			mem_out = myMem[mem_addr.read()];
}
SC_CTOR(MEM){
SC_METHOD(mem_func);
sensitive << clk.pos();
}
};