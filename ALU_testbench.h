#include "systemc.h"
#include <iostream>

SC_MODULE(ALU_testbench){
sc_out<sc_int<5>> B_addr;
sc_out<sc_bigint<128>> A, B;
sc_in<sc_bigint<128>> out;
sc_out<sc_uint<3>> alu_sel;
sc_out<sc_logic> mux_sel;

SC_CTOR(ALU_testbench){
	SC_THREAD(process);
	sensitive << A << B << B_addr << mux_sel << alu_sel;
}

void process(){
sc_trace_file *wf = sc_create_vcd_trace_file("ALU_test_wave");
sc_trace(wf,A,"A");
sc_trace(wf,B,"B");
sc_trace(wf,B_addr,"B_addr");
sc_trace(wf,out,"out");
sc_trace(wf,alu_sel,"alu_sel");
sc_trace(wf,mux_sel,"mux_sel");
B_addr = 1; mux_sel = SC_LOGIC_1; A = 2; B=4; alu_sel=0; wait(20, SC_NS); print();
B_addr = -1; mux_sel = SC_LOGIC_1; A = 2; B=4; alu_sel=1; wait(20, SC_NS); print();
B_addr = -1; mux_sel = SC_LOGIC_1; A = 2; B=4; alu_sel=2; wait(20, SC_NS); print();
B_addr = -1; mux_sel = SC_LOGIC_1; A = 2; B=4; alu_sel=3; wait(20, SC_NS); print();
B_addr = -1; mux_sel = SC_LOGIC_1; A = 20; B=4; alu_sel=4; wait(20, SC_NS); print();
B_addr = -1; mux_sel = SC_LOGIC_1; A = 20; B=4; alu_sel=5; wait(20, SC_NS); print();
B_addr = 1; mux_sel = SC_LOGIC_1; A = 20; B=4; alu_sel=6; wait(20, SC_NS); print();
sc_stop();
sc_close_vcd_trace_file(wf);
}

void print(){
cout << "\n At time " << sc_time_stamp() << ":: ";
cout << "(A,B,B_addr,alu_sel,mux_sel): " << A.read() << B.read() << B_addr.read() << alu_sel.read() << mux_sel.read() << "\n";
cout << "out = " << out.read() << endl;
}
};