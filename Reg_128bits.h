#include "systemc.h"
SC_MODULE(Reg_128bits){
sc_in<sc_bigint<128>> d;
sc_out<sc_bigint<128>> q;
sc_in<bool> clk, en, res;
void reg_function(){
	if(res) //asynchronous design
		q = 0;
	else if(clk.event() && clk && en)
		q = d;
	return;
};
SC_CTOR(Reg_128bits){
	SC_METHOD(reg_function);
	sensitive << res << clk.pos();
}
};