#include "systemc.h"
#include "Reg_file.h"
#include "ALU.h"
#include "MEM.h"
SC_MODULE(MIPS){
sc_in<bool> clk, reset;
sc_signal<sc_biguint<2>> pc; //program counter
sc_signal<sc_lv<128>> mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out;
//inputs from controller
//MEM
sc_in<sc_uint<5>> mem_addr; //addr for read/write in mem
sc_in<bool> mem_w_r, inst_data; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
//Reg_file
sc_in<sc_uint<5>> A_addr, B_addr; //2 addresses
sc_in<bool> regFile_w_r, enable, reset, clk; // write/read signal : w_r=1 (write), w_r=0 (read)
//ALU
sc_in<sc_logic> alu_sel,mux_sel;


void inc_pc(){
if(reset)
	pc = 1; // R0 always 0
else if(clk.event() && clk)
	if(pc == 4)
		pc = 1;
	else
		pc = pc + 1;
}

SC_CTOR(MIPS){
MEM mem("mem"); //  Inst/Data memory
mem(clk, pc, mem_addr, ALU_out, mem_w_r, inst_data, mem_out);

Reg_file myRegFile("myRegFile");
myRegFile(A_addr, B_addr, fetch_A, fetch_B, ALU_out, regFile_w_r, enable, reset, clk);

ALU myALU("myALU");
myALU(B_addr, fetch_A, fetch_B, ALU_out, alu_sel, mux_sel);

SC_METHOD(inc_pc);
sensitive << clk.pos() << reset;
}
};