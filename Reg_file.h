#include "systemc.h"
SC_MODULE(Reg_file){
sc_signal<sc_lv<128>> Q_vec[32];
sc_in<sc_lv<5>> A_addr, B_addr; //2 addresses
sc_out<sc_lv<128>> A_out , B_out; //output data from reg. file
sc_in<sc_lv<128>> A_in, regFile_wb; // input data for reg. file
sc_in<bool> w_r, enable, reset, clk, wb_mux; // write/read signal : w_r=1 (write), w_r=0 (read)

void Reg_file_func(){
	if(reset){ //asynchronous reset
		for(int i=0; i<32;i++)
			Q_vec[i] = 0;
	}
	else if(clk.event() && clk && enable){  //write
			if(wb_mux == 1)
				Q_vec[(sc_uint<5>)A_addr] = regFile_wb; //coming from alu
			else
				Q_vec[(sc_uint<5>)A_addr] = A_in; //coming from mem
	}
	else if(clk.event() && !clk){//read
			if(w_r == 0){ 
				A_out = Q_vec[(sc_uint<5>)A_addr];
				B_out = Q_vec[(sc_uint<5>)B_addr];
			}
	}
}

SC_CTOR(Reg_file){
SC_METHOD(Reg_file_func);
sensitive << clk << reset;
}
};