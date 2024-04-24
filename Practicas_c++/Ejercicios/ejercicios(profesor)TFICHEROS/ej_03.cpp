/* cuenta números enteros de fichero de texto */
# include <iostream> // cout <<
# include <fstream>  // open, close, f >>
using namespace std;
int main ()
{
	ifstream f; // manejador fichero de entrada
	int numero, nlineas = 0;
	f.open("texto.txt");
	while ( f >> numero ) { // false si es fin de fic.
		nlineas++;
	}
	cout << "Número líneas: " << nlineas << endl;
	f.close();
}
