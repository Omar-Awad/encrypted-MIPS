/*#include "systemc.h"
#include <iostream>
int sc_main(int argc, char* argv[]){
	sc_uint<8> mixCol_matrix[4][4] = {{0x02, 0x03, 0x01, 0x01},
{0x01, 0x02, 0x03, 0x01},
{0x01, 0x01, 0x02, 0x03},
{0x03, 0x01, 0x01, 0x02}};
sc_lv<8> state[4][4] = {{0x01, 0x01, 0x01, 0x01},{0x01, 0x01, 0x01, 0x01},{0x01, 0x01, 0x01, 0x01},{0x01, 0x01, 0x01, 0x01}}; 

sc_uint<8> temp;

for(int i=0; i<4;i++)
	for(int j=0;j<4;j++)
		for(int k=0;k<4;k++){
			//temp = (sc_uint<8>)state[k][i];
			state[j][i] += (sc_uint<8>)state[k][i] * mixCol_matrix[j][k];
		//	cout << state[j][i] << " " ;
		}


		for(int k=0;k<4;k++){
			temp += (sc_uint<8>)state[k][0] * mixCol_matrix[0][k];
		}
		state[0][0] = temp;
        cout << state[0][0] << " " ;


for(int i=0; i<4;i++){
	for(int j=0;j<4;j++)
		cout << state[i][j] << " ";
	cout<< endl;
}

sc_start();
return 0;
}
*/