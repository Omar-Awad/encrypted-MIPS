#include "systemc.h"
#include "Reg_file.h"
#include "ALU.h"
#include "MEM.h"
SC_MODULE(MIPS){
sc_in<bool> reset1 , clk1;

//inputs from controller
//MEM
sc_in<sc_uint<5>> mem_addr1; //addr for read/write in mem
sc_in<bool> mem_w_r1, inst_data1; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
//Reg_file
sc_in<sc_uint<5>> A_addr1, B_addr1; //2 addresses
sc_in<bool> regFile_w_r1, enable1; // write/read signal : w_r=1 (write), w_r=0 (read)
//ALU
sc_in<sc_logic> alu_sel1, mux_sel1;

sc_out<sc_uint<3>> pc1;
sc_out<sc_lv<128>> mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out;

sc_signal<sc_uint<3>> sig_pc1; //program counter
sc_signal<sc_lv<128>> sig_mem_out, sig_fetch_A, sig_fetch_B, sig_Dec_A, sig_Dec_B, sig_Dec_Imm, sig_ALU_out;

void inc_pc(){
if(reset1)
	sig_pc1 = 1; // R0 always 0
else if(clk1.event() && clk1)
	if(sig_pc1.read() == 4)
		sig_pc1 = 1;
	else
		sig_pc1 = sig_pc1.read() + 1;
}

SC_CTOR(MIPS){
pc1 = sig_pc1;
mem_out = sig_mem_out;
fetch_A = sig_fetch_A;
fetch_B = sig_fetch_B;
Dec_A = sig_Dec_A;
Dec_B = sig_Dec_B;
Dec_Imm = sig_Dec_Imm;
ALU_out = sig_ALU_out;

//MEM mem("mem"); //  Inst/Data memory
//mem(clk1, sig_pc1, mem_addr1, sig_ALU_out, mem_w_r1, inst_data1, sig_mem_out);

//Reg_file myRegFile("myRegFile");
//myRegFile(A_addr1, B_addr1, sig_fetch_A, sig_fetch_B, sig_ALU_out, regFile_w_r1, enable1, reset1, clk1);

//ALU myALU("myALU");
//myALU(B_addr1, sig_fetch_A, sig_fetch_B, sig_ALU_out, alu_sel1, mux_sel1);

SC_METHOD(inc_pc);
sensitive << clk1.pos() << reset1;
}
};