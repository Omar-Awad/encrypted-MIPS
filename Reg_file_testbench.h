#include "systemc.h"
#include <iostream>

SC_MODULE(Reg_file_testbench){
sc_out<sc_uint<5>> A_addr, B_addr; //sc_uint<5> //2 addresses
sc_in<sc_bigint<128>> A_out , B_out; //output data from reg. file
sc_out<sc_bigint<128>> A_in , B_in; // input data for reg. file
sc_out<bool> w_r,enable,reset; // write/read signal : w_r=1 (write), w_r=0 (read)
sc_in<bool> clk;

void process(){
sc_trace_file *wf = sc_create_vcd_trace_file("Reg_file_test_wave");
sc_trace(wf,A_addr,"A_addr");
sc_trace(wf,B_addr,"B_addr");
sc_trace(wf,A_out,"A_out");
sc_trace(wf,B_out,"B_out");
sc_trace(wf,A_in,"A_in");
sc_trace(wf,B_in,"B_in");
sc_trace(wf,w_r,"w_r");
sc_trace(wf,clk,"clk");
sc_trace(wf,enable,"enable");
sc_trace(wf,reset,"reset");

A_addr = 2; B_addr = 3; A_in = 5; B_in= 10; w_r = 1; enable = 1; reset = 0; wait(); print();
A_addr = 2; B_addr = 3; A_in = 5; B_in= 9; w_r = 0; enable = 1; reset = 0; wait(); print();
A_addr = 4; B_addr = 1; A_in = 4; B_in= 3; w_r = 1; enable = 1; reset = 0; wait(); print();
A_addr = 4; B_addr = 1; A_in = 5; B_in= 9; w_r = 0; enable = 1; reset = 0; wait(); print();
A_addr = 5; B_addr = 6; A_in = 7; B_in= 10; w_r = 1; enable = 1; reset = 0; wait(); print();
A_addr = 5; B_addr = 6; A_in = 5; B_in= 9; w_r = 0; enable = 1; reset = 0; wait(); print();
A_addr = 2; B_addr = 3; A_in = 5; B_in= 9; w_r = 0; enable = 1; reset = 0; wait(); print();
sc_stop();
sc_close_vcd_trace_file(wf);
}

void print(){
	
cout << "\n At time " << sc_time_stamp() << ":: ";
cout << "(A_addr,B_addr,A_in,B_in,w_r,enable,reset): " << A_addr.read() << B_addr.read() << A_in.read() << B_in.read() 
	<< w_r.read() << enable.read() << reset.read() << "\n";
cout << "(A_out,B_out): " << A_out.read() << B_out.read() << endl;
}
SC_CTOR(Reg_file_testbench){
	SC_THREAD(process);
	sensitive <<clk.pos() << reset;
}
};