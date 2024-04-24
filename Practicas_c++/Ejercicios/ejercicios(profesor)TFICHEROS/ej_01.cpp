#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){ // Lee 5 números enteros desde fichero
	const unsigned CANT_NUMS = 5;
	const string fichero = "datos.in";
	int num;
	ifstream f_ent;
	f_ent.open(fichero.c_str());
	for (unsigned i = 0; i < CANT_NUMS; i++){
		f_ent >> num;
		cout << num << endl;
	}
	f_ent.close();
}
