#include <iostream>
#include <fstream>
#include <array>

using namespace std;

int main (){
	ofstream f;
	const string nom_fic = "datos_salida.txt";

	f.open(nom_fic.c_str());

	if (!f.fail()){
		f << "Ana Sanchez Gomez" << endl;
		f << "25555555W" << endl;
		f << 4 << ' ' << 12 << ' ' << 2004 << endl;
		f.close();
	} else{
		cout << "No puede abrirse el fichero" << endl;

	}
}