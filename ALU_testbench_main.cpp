/*#include "systemc.h"
#include "ALU_testbench.h"
#include "ALU.h"

int sc_main(int argc, char* argv[]){
sc_signal<sc_bigint<128>> A,B,out,Imm;
sc_signal<sc_biguint<3>> alu_sel;
sc_signal<sc_logic> mux_sel;

ALU_testbench test1("test1");
test1(A,B,Imm,out,alu_sel,mux_sel);
ALU alu1("alu1");
alu1(A,B,Imm,out,alu_sel,mux_sel);
sc_start();
return 0;
}*/
