#include "systemc.h"
#include <iostream>
SC_MODULE(MIPS_testbench){
sc_out<bool> reset;
sc_in<bool> clk;
sc_out<sc_lv<5>> mem_addr;
sc_out<bool> mem_w_r, inst_data;
sc_out<sc_lv<5>> A_addr, B_addr;
sc_out<bool> regFile_w_r, enable, wb_mux;
sc_out<sc_logic> alu_sel, mux_sel;
sc_out<bool> enc_dec;
sc_out<sc_lv<2>> burst_op;
sc_out<bool> bus_wb;
sc_out<bool> bus_trigger;
sc_in<bool> amba_mem_w_r;
sc_in<sc_lv<3>> pc;
sc_in<sc_lv<128>> mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out;
sc_in<sc_lv<2>> block_addr;
sc_in<sc_lv<5>> cell_addr;
sc_in<sc_lv<32>> AMBA_in, AMBA_out;

void process(){
sc_trace_file *wf = sc_create_vcd_trace_file("MIPS_test_wave");
sc_trace(wf,reset,"reset");
sc_trace(wf,clk,"clk");
/*sc_trace(wf,mem_addr,"mem_addr");
sc_trace(wf,mem_w_r,"mem_w_r");
sc_trace(wf,inst_data,"inst_data");
sc_trace(wf,A_addr,"A_addr");
sc_trace(wf,B_addr,"B_addr");
sc_trace(wf,regFile_w_r,"regFile_w_r");
sc_trace(wf,enable,"enable");
sc_trace(wf,wb_mux,"wb_mux");
sc_trace(wf,alu_sel,"alu_sel");
sc_trace(wf,mux_sel,"mux_sel");
sc_trace(wf,pc,"pc");
sc_trace(wf,fetch_A,"fetch_A");
sc_trace(wf,fetch_B,"fetch_B");
sc_trace(wf,Dec_A,"Dec_A");
sc_trace(wf,Dec_B,"Dec_B");
sc_trace(wf,Dec_Imm,"Dec_Imm");
sc_trace(wf,ALU_out,"ALU_out");*/
sc_trace(wf,mem_out,"mem_out");
sc_trace(wf,enc_dec,"enc_dec");
sc_trace(wf,burst_op,"burst_op");
sc_trace(wf,bus_wb,"bus_wb");
sc_trace(wf,bus_trigger,"bus_trigger");
sc_trace(wf,block_addr,"block_addr");
sc_trace(wf,cell_addr,"cell_addr");
sc_trace(wf,AMBA_in,"AMBA_in");
sc_trace(wf,AMBA_out,"AMBA_out");
sc_trace(wf,amba_mem_w_r,"amba_mem_w_r");

reset = 1; wait(10, SC_NS); print();
/*reset = 0; mem_addr = 5; mem_w_r = 0; inst_data = 0; wait(10, SC_NS); print();
A_addr = 1; regFile_w_r = 1; enable = 1; wb_mux = 0; wait(10, SC_NS); print();
A_addr = 1; regFile_w_r = 0; enable = 1; wait(10, SC_NS); print();
B_addr = 2; regFile_w_r = 0; enable = 1; alu_sel = SC_LOGIC_0; mux_sel = SC_LOGIC_0; wait(10, SC_NS); print();
mem_addr = 6; mem_w_r = 1; inst_data = 0; wb_mux = 1; wait(10, SC_NS); print();
mem_addr = 6; mem_w_r = 0; inst_data = 0; wait(10, SC_NS); print();*/

//AMBA bus enc test

reset = 0; inst_data = 0; enc_dec = 1; burst_op = 3; bus_wb = 1; mem_addr = 5; bus_trigger = 1; 
wait(500, SC_NS); print();
bus_wb = 0; mem_w_r = 0; wait(200, SC_NS); print();

sc_stop();
sc_close_vcd_trace_file(wf);
}

void print(){
cout << "\n At time " << sc_time_stamp() << ":: ";

cout << "(reset, clk, mem_addr, mem_w_r, inst_data, A_addr, B_addr, regFile_w_r, enable, alu_sel, mux_sel, wb_mux, enc_dec, burst_op, bus_wb): " << reset.read() << clk.read()
	<< mem_addr.read() << mem_w_r.read() << inst_data.read() << A_addr.read() << B_addr.read() << regFile_w_r.read() <<
	enable.read() << alu_sel.read() << mux_sel.read() << wb_mux.read() << enc_dec.read() << burst_op.read() << bus_wb.read() << endl;

cout << "(pc, mem_out, fetch_A, fetch_B, Dec_A, Dec_B, Dec_Imm, ALU_out, block_addr, cell_addr, AMBA_in, AMBA_out, bus_trigger, amba_mem_w_r): " << pc.read() << mem_out.read() << fetch_A.read() 
	<< fetch_B.read() << Dec_A.read() << Dec_B.read() << Dec_Imm.read() << ALU_out.read() << block_addr.read() << cell_addr.read()
	<< AMBA_in.read() << AMBA_out.read() << bus_trigger.read() << amba_mem_w_r.read() << endl;
}
SC_CTOR(MIPS_testbench){
	SC_THREAD(process)
	sensitive << clk.pos() << reset;
}
};