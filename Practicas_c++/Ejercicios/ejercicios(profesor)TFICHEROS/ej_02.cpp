#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  const string FICHERO = "datos.in";
  int num;

  ifstream f_ent;
  f_ent.open(FICHERO.c_str());
  if (f_ent.fail()) {
    cout << "Imposible abrir el fichero de entrada " <<  endl;
  }
  else {
    f_ent >> num; // LECTURA POR ADELANTADO PARA DETECTAR
    // FIN DE FICHERO
    while (!f_ent.eof()) {
      cout << num << endl;
      f_ent >> num;
    }
    f_ent.close();
  }
}
