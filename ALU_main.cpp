/*#include "systemc.h"
#include <iostream>
#include "ALU.h"
int sc_main(int argc, char* argv[]){
sc_signal<sc_lv<5>> B_addr;
sc_signal<sc_lv<128>> A, B;
sc_signal<sc_lv<128>> out;
sc_signal<sc_logic> alu_sel,mux_sel;

ALU myalu("myalu");
myalu(B_addr, A, B, out, alu_sel, mux_sel);
B_addr = "00001"; A = 0x0000003; B=0x0000001; alu_sel = SC_LOGIC_1; mux_sel = SC_LOGIC_0; 
sc_start(20,SC_NS);
cout << out << endl;
return 0;
}*/

//needs modifications