#include "systemc.h"
SC_MODULE(ALU){
sc_in<sc_int<5>> B_addr;
sc_in<sc_bigint<128>> A, B;
sc_out<sc_bigint<128>> out;
sc_in<sc_uint<3>> alu_sel;
sc_in<sc_logic> mux_sel;
sc_bigint<128> Imm, Z;

void ALU_function(){
	//sign extend
	Imm = B_addr;
	// alu MUX
	Z = (mux_sel == SC_LOGIC_0)? B : Imm;

	switch(sc_uint<3> (alu_sel)){
	case 0: out = A + Z; break;
	case 1: out = A - Z; break;
	case 2: out = A * Z; break;
	case 3: out = A / Z; break;
	case 4: out = A | Z; break; //wrong...need sign extend
	case 5: out = A & Z; break; //wrong...need sign extend
	case 6: out = A ^ Z; break; //wrong...need sign extend
	}
	return;
};

SC_CTOR(ALU){
	SC_METHOD(ALU_function);
	sensitive << A << B << B_addr << mux_sel << alu_sel; 
}
};