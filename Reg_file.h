#include "systemc.h"
#include "Reg_128bits.h"

SC_MODULE(Reg_file){
sc_vector<Reg_128bits> myRegFile;
sc_in<sc_uint<5>> A_addr, B_addr; //2 addresses
sc_out<sc_bigint<128>> A_out , B_out; //output data from reg. file
sc_in<sc_bigint<128>> A_in , B_in; // input data for reg. file
sc_in<bool> w_r, enable, reset, clk; // write/read signal : w_r=1 (write), w_r=0 (read)

sc_signal<sc_bigint<128>> x;
Reg_file(): myRegFile("myRegFile", 32),A_addr("A_addr"),B_addr("B_addr"),A_out("A_out"),B_out("B_out"),A_in("A_in"),
B_in("B_in"),w_r("w_r"),clk("clk"),enable("enable"),reset("reset") {
	//R0 is always 0 (start with i = 1)

	for(int i=1; i<32; i++){
		myRegFile[i].clk(clk);
		myRegFile[i].en(enable);
		myRegFile[i].res(reset);
	}
}

void Reg_file_func(){
	x = 4;
	if(w_r == 0){ //read
		myRegFile[2].q(A_out);
		myRegFile[2].q(B_out);
	}else { //writes
		myRegFile[2].d(x);
		myRegFile[2].d(x);
	}

	/*if(w_r == 0){ //read
		myRegFile[A_addr].q(A_out);
		myRegFile[B_addr].q(B_out);
	}else { //writes
		myRegFile[A_addr].d(A_in);
		myRegFile[B_addr].d(B_in);
	}*/
};

SC_CTOR(Reg_file){
	//SC_METHOD(Reg_file_func);
	sensitive << reset << clk.pos();
}
};