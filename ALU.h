#include "systemc.h"
SC_MODULE(ALU){
sc_in<sc_bigint<128>> A, B, Imm;
sc_out<sc_bigint<128>> out;
sc_in<sc_biguint<3>> alu_sel;
sc_in<sc_logic> mux_sel;
sc_bigint<128> Z;

void ALU_function(){
	Z = (mux_sel == SC_LOGIC_0)? B : Imm;

	if(alu_sel == 0)
		out = A + Z;
	else if(alu_sel == 1)
		out = A - Z;
	else if(alu_sel == 2)
		out = A * Z;
	else if(alu_sel == 3)
		out = A / Z;
	else if(alu_sel == 4)
		out = A | Z;
	else if(alu_sel == 5)
		out = A & Z;
	else if(alu_sel == 6)
		out = A ^ Z;
	return;
};

SC_CTOR(ALU){
	SC_METHOD(ALU_function);
	sensitive << A << B << Imm << mux_sel << alu_sel; 
}
};