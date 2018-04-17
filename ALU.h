#include "systemc.h"
SC_MODULE(ALU){
sc_in<sc_lv<5>> B_addr;
sc_in<sc_lv<128>> A, B;
sc_out<sc_lv<128>> out;
sc_in<sc_logic> alu_sel,mux_sel;
sc_bigint<128> Imm, Z;

void ALU_function(){
	//sign extend
	Imm = (B_addr.read() << 58) >> 58;    
	// alu MUX
	Z = (mux_sel == SC_LOGIC_0)? B.read() : Imm; //B_addr.read();  
	if(alu_sel == SC_LOGIC_0)
		out = sc_bigint<128>(A) + Z;
	else
		out = sc_bigint<128>(A) - Z;
}

SC_CTOR(ALU){
	SC_METHOD(ALU_function)
	sensitive << A << B << B_addr << mux_sel << alu_sel; 
}
};