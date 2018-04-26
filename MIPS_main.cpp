#include "systemc.h"
#include "MIPS.h"
#include "MIPS_testbench.h"
#include "controller.h"
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
sc_signal<bool> enc_dec;
sc_signal<sc_lv<2>> burst_op;
sc_signal<bool> bus_wb;
sc_signal<bool> bus_trigger;
sc_signal<bool> amba_mem_w_r;
sc_signal<sc_lv<2>> block_addr;
sc_signal<sc_lv<5>> cell_addr;
sc_signal<sc_lv<32>> AMBA_in, AMBA_out;

sc_clock clk("clk", 10, SC_NS);

controller cntr("cntr");
cntr(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, wb_mux, alu_sel, mux_sel, enc_dec, burst_op, bus_wb,
	   bus_trigger, pc, mem_out);

MIPS myMIPS("myMIPS");
myMIPS(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, wb_mux, alu_sel, mux_sel, enc_dec, burst_op, bus_wb,
	   bus_trigger, amba_mem_w_r, pc, mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out, block_addr, cell_addr,AMBA_in, AMBA_out);

MIPS_testbench test("test");
test(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, wb_mux, alu_sel, mux_sel, enc_dec, burst_op, bus_wb,
	   bus_trigger, amba_mem_w_r, pc, mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out, block_addr, cell_addr,AMBA_in, AMBA_out);

sc_start();
return 0;
}
