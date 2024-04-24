#include <iostream>
#include <fstream>
#include <array>

using namespace std;

typedef array<int, 10> Datos;

void escribir_fichero(ofstream &f, const Datos &datos);  

int main (){
	ofstream f;
	Datos vector = {{0,1,2,3,4,5,6,7,8,9}};
	const string nom_fic = "datos_salida.txt";

	f.open(nom_fic.c_str());

	if (!f.fail()){
		escribir_fichero(f, vector);
		f.close();
	} else{
		cout << "No puede abrirse el fichero" << endl;
	}
}

void escribir_fichero(ofstream &f, const Datos &datos){
	for (int i = 0; i < int(datos.size()); i++){
		f << datos[i] << endl;
	}
}