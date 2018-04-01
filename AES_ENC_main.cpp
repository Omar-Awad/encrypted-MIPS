#include"systemc.h"
#include"AES_ENC.h"
#include <iostream>
#include "AES_DEC.h"

int sc_main(int argc, char* argv[]){
	sc_clock clk("clk", 20, SC_NS);
	sc_signal<sc_logic> reset;
	sc_signal<sc_lv<128>> keyIn;
	sc_signal<sc_lv<128>> txt;
	sc_signal<sc_lv<128>> cipher;
	sc_signal<sc_lv<128>> txt_reversed;

	sc_signal<sc_lv<128>> cipher2;
    cipher2 = "0x3925841d02dc09fbdc118597196a0b32";
	txt = "0x3243f6a8885a308d313198a2e0370734";
    keyIn = "0x2b7e151628aed2a6abf7158809cf4f3c";
	reset = SC_LOGIC_0;
	//AES_ENC AES_ENC1("AES_ENC1");
	//AES_ENC1(clk, reset, txt, keyIn, cipher);
	AES_DEC AES_DEC1("AES_DEC1");
	AES_DEC1(clk, reset, cipher2, keyIn, txt_reversed);
	sc_start(20, SC_NS);
	//cout << "original txt= "<<std::hex << txt << endl;
	//cout << "Cipher= "<<std::hex << cipher << endl;
	//cout << "reversed txt= "<<std::hex << txt_reversed << endl;
	return 0;
}