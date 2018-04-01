#include"systemc.h"
SC_MODULE(AES_DEC) {
sc_in<bool> clk;
sc_in<sc_logic> reset;
sc_in<sc_lv<128>> cipher;
sc_in<sc_lv<128>> keyIn;
sc_out<sc_lv<128>> text;
sc_lv<8> roundKey[11][4][4];
sc_lv<8> data[4][4];
void keyExpa();
sc_lv<8> getInvSBoxValue(sc_uint<8> i);
sc_lv<8> getSBoxValue(sc_uint<8> i);
sc_lv<8> getRcon(int i);
void invSubBytes();
void invShiftRows();
void invMixColumns();
void invAddRoundKey(int rnd);
void dec();
sc_lv<8> mult9(sc_uint<8> i);
sc_lv<8> mult11(sc_uint<8> i);
sc_lv<8> mult13(sc_uint<8> i);
sc_lv<8> mult14(sc_uint<8> i);
void print();
SC_CTOR(AES_DEC){
SC_METHOD(dec)
sensitive << reset << clk.pos();
 }
};

