/*#include "systemc.h"
#include "Reg_file.h"
#include "Reg_file_testbench.h"

int sc_main(int argc, char* argv[]){
sc_signal<sc_uint<5>> A_addr, B_addr; //sc_uint<5> //2 addresses
sc_signal<sc_bigint<128>> A_out , B_out; //output data from reg. file
sc_signal<sc_bigint<128>> A_in , B_in; // input data for reg. file
sc_signal<bool> w_r,enable,reset; // write/read signal : w_r=1 (write), w_r=0 (read)

sc_clock clk("clk",20,SC_NS);
Reg_file_testbench test1("test1");
test1(A_addr,B_addr,A_out,B_out,A_in,B_in,w_r,enable,reset,clk);
Reg_file file1("file1");
file1(A_addr,B_addr,A_out,B_out,A_in,B_in,w_r,enable,reset,clk);
sc_start();
return 0;
}*/
