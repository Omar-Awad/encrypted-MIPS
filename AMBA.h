#include "systemc.h"
#include "AES_DEC.h"
#include "AES_ENC.h"

SC_MODULE(AMBA){
sc_in<bool> clk, enc_dec;
sc_in<sc_lv<5>> start_addr; //from controller
sc_out<sc_lv<5>> cell_addr; //to MEM
sc_out<sc_lv<2>> block_addr; //addr of the 4 32-bit blocks in each MEM cell
sc_in<sc_lv<2>> burst_op; // 0: burst 4, 1: burst 8, 2: burst 12, 3: burst 16
sc_in<sc_lv<32>> in; // from MEM
sc_out<sc_lv<32>> out; // to MEM
sc_signal<sc_lv<128>> sig_in, key, sig1_out, sig2_out;
sc_uint<2> sig_block_addr;
sc_uint<5> sig_cell_addr;
AES_ENC *enc;
AES_DEC *dec;
sc_uint<4> counter, max_count;
sc_signal<bool> start;
sc_lv<128> sig_in_temp;

void burst_mode(){
	if(clk.event() && clk){
		switch((sc_uint<2>) burst_op){
			case 0 : max_count = 4; break;
			case 1 : max_count = 8; break;
			case 2 : max_count = 12; break;
			case 3 : max_count = 16; 
		}	

		if(counter == 0){
			sig_cell_addr = start_addr.read();
			sig_block_addr = 0;
			start = 0;
			counter++;
		}
		else if(counter <= max_count){
				if(counter%4 == 0){
					sig_cell_addr++;
					sig_block_addr = 0;
					start = 1;
				}
				else{
					sig_block_addr++;
					start = 0;
				}
		}
		sig_in_temp.range(32*sig_block_addr+31,32*sig_block_addr) = in.read();
	}

sig_in = sig_in_temp;
block_addr = sig_block_addr;
cell_addr = sig_cell_addr;

for(int i=0; i< 4; i++)
	out = (enc_dec == 1)? sig1_out.read().range(32*i+31,32*i) : sig2_out.read().range(32*i+31,32*i);
}

SC_CTOR(AMBA){
key = "0x2b7e151628aed2a6abf7158809cf4f3c";
counter = 0;
enc = new AES_ENC("enc");
(*enc)(enc_dec, start, in, key, sig1_out);

dec =  new AES_DEC("dec");
(*dec)(enc_dec, start, in, key, sig2_out);

SC_METHOD(burst_mode);
sensitive << clk.pos();
}
};