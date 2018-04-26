#include "systemc.h"

SC_MODULE(controller){
sc_in<bool> reset , clk;
sc_out<sc_lv<5>> mem_addr;
sc_out<bool> mem_w_r, inst_data;
sc_out<sc_lv<5>> A_addr, B_addr;
sc_out<bool> regFile_w_r, enable, wb_mux;
sc_out<sc_logic> alu_sel, mux_sel;
sc_out<bool> enc_dec;
sc_out<sc_lv<2>> burst_op;
sc_out<bool> bus_wb;
sc_out<bool> bus_trigger;
sc_out<sc_lv<3>> pc;
sc_in<sc_lv<128>> sig_mem_out;
bool flag1;
sc_lv<2> opcode;
sc_lv<128> sig_mem_out2;
sc_signal<sc_lv<5>> mem_addr2;

void inc_pc(){ 
if(reset)
	pc = 1; // R0 always 0
else if(clk.event() && clk && inst_data)
		if(pc.read() == 4)
			pc = 1;
		else
			pc = (sc_uint<3>)pc + 1;
}

void cont(){
	if(clk.event() && clk){
		if(reset)
			flag1 = 0;

		if(!flag1){
			inst_data = 1;
			inc_pc();
			mem_w_r = 0;
			bus_wb = 0; 
			flag1 = 1;
			sig_mem_out2 = sig_mem_out.read();
			opcode = sig_mem_out2.range(127,126);
		}
		else{
			if(opcode == "00"){
				enc_dec=1;
				inst_data = 0; 
				burst_op = 0;
				bus_wb = 1; 
				mem_addr = sig_mem_out2.range(125,121);
				bus_trigger = 1;
			}
			else if(opcode == "01"){
				enc_dec=0;
				inst_data = 0; 
				burst_op = 0;
				bus_wb = 1; 
				mem_addr = sig_mem_out2.range(125,121);
				bus_trigger = 1;
			}
		}
	}
}

SC_CTOR(controller){
	SC_METHOD(cont);
	sensitive << clk.pos() << reset;
}
};