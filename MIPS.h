#include "systemc.h"
#include "Reg_file.h"
#include "ALU.h"
#include "MEM.h"
#include "AMBA.h"

SC_MODULE(MIPS){
sc_in<bool> reset , clk;
//inputs from controller
//MEM
sc_in<sc_lv<5>> mem_addr; //addr for read/write in mem  and can be also addr for AMBA bus, depending on operation
sc_in<bool> mem_w_r, inst_data; //w_r=1 (write), w_r=0 (read), inst_data=1(inst), inst_data=0(data)
//Reg_file
sc_in<sc_lv<5>> A_addr, B_addr; //2 addresses
sc_in<bool> regFile_w_r, enable, wb_mux; // write/read signal : w_r=1 (write), w_r=0 (read)
//ALU
sc_in<sc_logic> alu_sel, mux_sel;
//AMBA bus
sc_in<bool> enc_dec;
sc_in<sc_lv<2>> burst_op;
sc_in<bool> bus_wb; // current operation uses bus or wb, to prevent writing at same addr at same time
sc_in<bool> bus_trigger;

sc_inout<bool> amba_mem_w_r; // AMBA bus controlling mem
//sc_out<sc_lv<3>> pc;
//sc_out<sc_lv<128>> mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out;

sc_inout<sc_lv<3>> sig_pc; //program counter
sc_inout<sc_lv<128>> sig_mem_out, sig_fetch_A, sig_fetch_B, sig_Dec_A, sig_Dec_B, sig_Dec_Imm, sig_ALU_out;

sc_inout<sc_lv<2>> block_addr;
sc_inout<sc_lv<5>> cell_addr;
sc_inout<sc_lv<32>> AMBA_in, AMBA_out;

MEM *mem;
Reg_file *myRegFile;
ALU *myALU;
AMBA *bus;

void inc_pc(){ 
if(reset)
	sig_pc = 1; // R0 always 0
else if(clk.event() && clk && inst_data)
		if(sig_pc.read() == 4)
			sig_pc = 1;
		else
			sig_pc = (sc_uint<3>)sig_pc + 1;
/*
pc = sig_pc;
mem_out = sig_mem_out;
fetch_A = sig_fetch_A;
fetch_B = sig_fetch_B;
Dec_A = sig_Dec_A;
Dec_B = sig_Dec_B;
Dec_Imm = sig_Dec_Imm;
ALU_out = sig_ALU_out;*/
}

SC_CTOR(MIPS){
bus = new AMBA("bus");
(*bus)(clk, enc_dec, bus_trigger, mem_addr, cell_addr, block_addr, burst_op, AMBA_in, AMBA_out, amba_mem_w_r);

mem = new MEM("mem");
(*mem)(clk, bus_wb, sig_pc, mem_addr, sig_ALU_out, mem_w_r, inst_data, sig_mem_out, cell_addr, block_addr, AMBA_in, AMBA_out, amba_mem_w_r);

myRegFile = new Reg_file("myRegFile");
(*myRegFile)(A_addr, B_addr, sig_fetch_A, sig_fetch_B, sig_mem_out, sig_ALU_out, regFile_w_r, enable, reset, clk, wb_mux);

myALU = new ALU("myALU");
(*myALU)(B_addr, sig_fetch_A, sig_fetch_B, sig_ALU_out, alu_sel, mux_sel);

SC_METHOD(inc_pc);
sensitive << clk.pos() << reset;
}
};