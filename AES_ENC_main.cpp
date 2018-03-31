#include"systemc.h"
#include"AES_ENC.h"
int sc_main(int argc, char* argv[]){
	sc_clock clk("clk", 20, SC_NS);
	sc_signal<sc_logic> reset;
	sc_signal<sc_lv<128>> keyIn;
	sc_signal<sc_lv<128>> txt;
	sc_signal<sc_lv<128>> cipher;
	txt = "0x3243f6a8885a308d313198a2e0370734";
	keyIn = "0x02b7e151628aed2a6abf7158809cf4f3c";
	reset = SC_LOGIC_0;
	AES_ENC AES_ENC1("AES_ENC1");
	AES_ENC1(clk, reset, txt, keyIn, cipher);
	sc_start(40, SC_NS);
	cout << cipher;
	return 0;
}