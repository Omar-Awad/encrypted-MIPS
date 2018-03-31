/*#include "systemc.h"
#include <iostream>
int sc_main(int argc, char* argv[]){
	sc_uint<8> mixCol_matrix[4][4] = {{0x02, 0x03, 0x01, 0x01},
{0x01, 0x02, 0x03, 0x01},
{0x01, 0x01, 0x02, 0x03},
{0x03, 0x01, 0x01, 0x02}};
sc_uint<8> state[4][4] = {{0x00, 0x01, 0x02, 0x03},{0x04, 0x05, 0x06, 0x07},{0x08, 0x09, 0x0a, 0x0b},{0x0c, 0x0d, 0x0e, 0x0f}}; 

sc_uint<8> temp;
for(int i=0; i<4;i++)
	for(int j=0;j<4;j++)
		for(int k=0;k<4;k++){
			temp = (sc_uint<8>)state[j][i];
			state[j][i] = temp + temp * mixCol_matrix[j][k];
		}

for(int i=0; i<1;i++){
	for(int j=0;j<4;j++)
		cout << state[j][i] << " ";
	cout<< endl;
}

cout << state[0][1] << " " ;
sc_uint<8> temp = ((sc_uint<8>)state[0][1]);
cout << temp << " " ;
state[0][1] = temp + temp * mixCol_matrix[0][0];
cout << state[0][1];

sc_start();
return 0;
}
*/