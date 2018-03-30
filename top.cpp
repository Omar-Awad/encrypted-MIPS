/*#include <iostream>
#include <sstream>
#include "carry_ripple.h"
using namespace std;
int sc_main(int argc , char* argv[]){
	sc_vector<sc_signal<sc_logic>> I1,I2,O1,O2;
	sc_signal<sc_logic> I3;
	I1.init(128); I2.init(128); O1.init(128); O1.init(128); 
	carry_ripple x("dut");
	for(int i=0; i<128;i++){
		I1[i] = SC_LOGIC_1;
		I2[i] = SC_LOGIC_1;
	}
	I3 = SC_LOGIC_1;

	x.A_vec(I1);
	x.B_vec(I2);
	x.C_vec(I3);
	x.S_vec(O1);
	x.Cout_vec(O2);

	x.add_128bits();
	
	sc_start(1000,SC_NS);
	
	cout << "Sum: ";
	for(int i = 0;i<127;i++)
	cout << O1[i] << ", ";
	cout << O1[127] << ".\n";
	cout << "Carry out: " << O2[127];
	
	return 0;
}

*/