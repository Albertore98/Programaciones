#include <iostream>
#include <fstream>

using namespace std;

// Saca un fichero de texto por pantalla
// PARÁMETROS:
//  ff (referencia): flujo de fichero de entrada
// PRECONDICIÓN:
//  El flujo de entrada está previamente abierto
//  El fichero es un fichero de texto
// POSTCONDICIÓN:
//  Saca por pantalla el contenido del fichero
void volcarFichero(ifstream &ff);

int main()
{
  const string NOMBRE_FICHERO = "cadenas.in";
  ifstream f_ent;

  f_ent.open(NOMBRE_FICHERO.c_str());

  if (f_ent.fail()) {
    cout << "Imposible abrir el fichero de entrada" << endl;
  } else {
    volcarFichero(f_ent);
    f_ent.close();
  }
}

void volcarFichero(ifstream &ff) {
  char cc;

  ff.get(cc);
  while (!ff.eof()) {
    cout << cc;
    ff.get(cc);
  }
}