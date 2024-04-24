#include <iostream>
#include <fstream>

using namespace std;

void leer_texto(ifstream &f, string &texto);

int main() {
  string texto;
  ifstream f;

  f.open("poema.txt");

  if (!f.fail()) {
    leer_texto(f, texto);
    f.close();
  }

  cout << endl << texto << endl;
}


void leer_texto(ifstream &f, string &texto) {
  string linea;

  texto = "";

  getline(f, linea);
  while (!f.eof()) {
    texto += linea + '\n';
    getline(f, linea);
  }
}
