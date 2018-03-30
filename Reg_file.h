#include "systemc.h"
#include "Reg_128bits.h"

SC_MODULE(Reg_file){
Reg_128bits *myRegFile[32];
sc_signal<sc_bigint<128>> D_vec[32], Q_vec[32];
sc_in<sc_uint<5>> A_addr, B_addr; //2 addresses
sc_out<sc_bigint<128>> A_out , B_out; //output data from reg. file
sc_in<sc_bigint<128>> A_in , B_in; // input data for reg. file
sc_in<bool> w_r, enable, reset, clk; // write/read signal : w_r=1 (write), w_r=0 (read)
int i;
void Reg_file_func(){
	if(w_r == 0){ //read
		A_out = Q_vec[A_addr.read()];
		B_out = Q_vec[B_addr.read()];
	}else { //writes
		D_vec[A_addr.read()] = A_in;
		D_vec[B_addr.read()] = B_in;
	}
	return;
};


SC_CTOR(Reg_file){
	//R0 is always 0 
	for(int i=0; i<32; i++){
		myRegFile[i] = new Reg_128bits("");
		myRegFile[i] ->d(D_vec[i]);
		myRegFile[i] ->q(Q_vec[i]);
		myRegFile[i] ->clk(clk);
		myRegFile[i] ->en(enable);
		myRegFile[i] ->res(reset);
	}

	SC_METHOD(Reg_file_func);
	sensitive << reset << clk.pos();
}
};