#include "systemc.h"
SC_MODULE(Reg_file){
sc_signal<sc_bigint<128>> Q_vec[32];
sc_in<sc_uint<5>> A_addr, B_addr; //2 addresses
sc_out<sc_bigint<128>> A_out , B_out; //output data from reg. file
sc_in<sc_bigint<128>> regFile_wb; // input data for reg. file
sc_in<bool> w_r, enable, reset, clk; // write/read signal : w_r=1 (write), w_r=0 (read)

void Reg_file_func(){
	if(reset){ //asynchronous reset
		for(int i=0; i<31;i++)
			Q_vec[i] = 0;
	}
	else if(w_r == 0){ //read
		A_out = Q_vec[(int)A_addr.read()];
		B_out = Q_vec[(int)B_addr.read()];
	}
	else if(clk.event() && clk && enable){  //writes
			Q_vec[(int)A_addr.read()] = regFile_wb; 
	}
}

SC_CTOR(Reg_file){
SC_METHOD(Reg_file_func);
sensitive << clk.pos() << reset;
}
};