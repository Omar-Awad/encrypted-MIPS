#include "systemc.h"
SC_MODULE(MEM){
sc_in<bool> clk, bus_wb;
sc_in<sc_lv<3>> pc; //4 instructions (from cell 1 to 4)
sc_in<sc_lv<5>> mem_addr; //addr for read/write in mem
sc_in<sc_lv<128>> mem_wb;
sc_in<bool> w_r, inst_data; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
sc_out<sc_lv<128>> mem_out;
sc_in<sc_lv<5>> cell_addr; //AMBA
sc_in<sc_lv<2>> block_addr; //AMBA
sc_out<sc_lv<32>> AMBA_out;
sc_in<sc_lv<32>> AMBA_in;
sc_in<bool> amba_mem_w_r;
sc_lv<128> myMem[32];

void mem_func(){
	if(clk.event() && clk){ //write
		if(bus_wb == 0){
			if(w_r == 1)
				myMem[(sc_uint<5>)mem_addr] = mem_wb;
		}
		else {
			if(amba_mem_w_r == 1)
				myMem[(sc_uint<5>)cell_addr].range(32*(sc_uint<2>)block_addr+31,32*(sc_uint<2>)block_addr) = AMBA_in.read();
		}
	}
	else if(clk.event() && !clk){ //read
			if(bus_wb == 0){
				if(inst_data == 1)
					mem_out = myMem[(sc_uint<3>)pc];
				else if(w_r == 0) 
						mem_out = myMem[(sc_uint<5>)mem_addr];
			}
			else if(amba_mem_w_r == 0)
					AMBA_out = myMem[(sc_uint<5>)cell_addr].range(32*(sc_uint<2>)block_addr+31,32*(sc_uint<2>)block_addr);
	}
}

SC_CTOR(MEM){
	// initialize myMem here
	myMem[0] = "0x00000000000000000000000000000000"; //always 0
	myMem[1] = "0x00000000000000000000000000000000"; //inst. 1
	myMem[2] = "0x00000000000000000000000000000000"; //inst. 2
	myMem[3] = "0x00000000000000000000000000000000"; //inst. 3
	myMem[4] = "0x00000000000000000000000000000000"; //inst. 4
	myMem[5] = "0x3243f6a8885a308d313198a2e0370734";
	myMem[6] = "0x00000000000000000000000000000007";
	myMem[7] = "0x00000000000000000000000000000008";
	myMem[8] = "0x00000000000000000000000000000003";

SC_METHOD(mem_func);
sensitive << clk;
}
};