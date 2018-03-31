#include"systemc.h"
SC_MODULE(AES_ENC) {
sc_in<bool> clk;
sc_in<sc_logic> reset;
sc_in<sc_lv<128>> txt;
sc_in<sc_lv<128>> keyIn;
sc_out<sc_lv<128>> cipher;
sc_lv<8> roundKey[11][4][4];
sc_lv<8> data[4][4] ;
void keyExpa() ;
sc_lv<8> getSBoxValue(sc_uint<8> i);
sc_lv<8> getRcon(int i);
void subBytes();
void shiftRows();
void mixColumns();
void addRoundKey(int rnd);
void enc();
SC_CTOR(AES_ENC){
SC_METHOD(enc)
	sensitive << reset << clk.pos();
 }
};