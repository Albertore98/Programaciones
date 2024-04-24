#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  const string FICHERO = "datoscar.in";
  char car;
  ifstream f_ent;

  f_ent.open(FICHERO.c_str());
  if (f_ent.fail()) {
    cout <<  "Imposible abrir el fichero de entrada" << endl;
  }
  else {
    f_ent.get(car);
    while (!f_ent.eof()) {
      cout << car;
      f_ent.get(car);
    }
    f_ent.close();
  }
}
