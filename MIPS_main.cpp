/*#include "systemc.h"
#include "MIPS.h"
#include "MIPS_testbench.h"
#include <iostream>
#include <sstream>

int sc_main(int argc, char* argv[]){
sc_signal<bool> reset;
sc_signal<sc_lv<5>> mem_addr;
sc_signal<bool> mem_w_r, inst_data;
sc_signal<sc_lv<5>> A_addr, B_addr;
sc_signal<bool> regFile_w_r, enable, wb_mux;
sc_signal<sc_logic> alu_sel, mux_sel;
sc_signal<sc_lv<3>> pc;
sc_signal<sc_lv<128>> mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out;
sc_clock clk("clk", 10, SC_NS);

MIPS myMIPS("myMIPS");
myMIPS(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, wb_mux, alu_sel, mux_sel,
	   pc, mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out);

MIPS_testbench test("test");
test(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, wb_mux, alu_sel, mux_sel,
	   pc, mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out);

sc_start();
return 0;
}*/
