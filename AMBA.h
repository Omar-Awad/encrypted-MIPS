#include "systemc.h"
#include "AES_DEC.h"
#include "AES_ENC.h"

SC_MODULE(AMBA){
sc_in<bool> clk, enc_dec, bus_trigger; //trigger to stop AMBA after the inst. is done
sc_in<sc_lv<5>> start_addr; //from controller
sc_out<sc_lv<5>> cell_addr; //to MEM
sc_out<sc_lv<2>> block_addr; //addr of the 4 32-bit blocks in each MEM cell
sc_in<sc_lv<2>> burst_op; // 0: burst 4, 1: burst 8, 2: burst 12, 3: burst 16
sc_in<sc_lv<32>> in; // from MEM
sc_out<sc_lv<32>> out; // to MEM
sc_out<bool> mem_w_r;

sc_signal<sc_lv<128>> sig_in, key, sig1_out, sig2_out;
sc_uint<2> sig_block_addr;
sc_uint<3> inst_count;
sc_uint<5> sig_cell_addr;
sc_uint<3> counter1;
sc_signal<bool> start, flag, flag2, flag3;
sc_lv<128> sig_in_temp;

AES_ENC *enc;
AES_DEC *dec;

void burst_mode(){
	if(bus_trigger.event() && bus_trigger){
			flag2 = 1;
			sig_cell_addr = start_addr.read();
	}
		
	if(clk.event() && clk){
		switch((sc_uint<2>) burst_op){
			case 0 : inst_count = 1; break;
			case 1 : inst_count = 2; break;
			case 2 : inst_count = 3; break;
			case 3 : inst_count = 4; 
		}	

	if(flag2){
		if(counter1 < inst_count){
			if(!start){
				sig_in_temp.range(32*sig_block_addr+31,32*sig_block_addr) = in.read();
				if(sig_block_addr == 3)
					start = 1;
				else
					sig_block_addr++;
			}
			else if(sig_block_addr == 0){								
					if(inst_count - counter1 > 1){ 
						sig_cell_addr++;
					}
				start = 0;	
				counter1++;		
			}
		}	
		else
			flag2 = 0;
	}

	if(start)
		flag = 1;
		
	if(flag){
		flag3 = 1;
		mem_w_r = 1;
		if(flag3)
			if(sig_block_addr == 0){
				flag = 0;
				flag3 = 0;
				if(inst_count - counter1 > 0){ 
					mem_w_r = 0;
				}
			}
			else 
				 sig_block_addr--;
		out = (enc_dec == 1)? sig1_out.read().range(32*sig_block_addr+31,32*sig_block_addr) : sig2_out.read().range(32*sig_block_addr+31,32*sig_block_addr);


	}
}
sig_in = sig_in_temp;
block_addr = sig_block_addr;
cell_addr = sig_cell_addr;
}

SC_CTOR(AMBA){
key = "0x2b7e151628aed2a6abf7158809cf4f3c";
counter1 = 0;
enc = new AES_ENC("enc");
(*enc)(clk, enc_dec, start, sig_in, key, sig1_out);

dec =  new AES_DEC("dec");
(*dec)(clk, enc_dec, start, sig_in, key, sig2_out);

SC_METHOD(burst_mode);
sensitive << clk.pos()  << bus_trigger.pos();
}
};