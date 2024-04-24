#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string nombre_fich="prueba.txt";
void escribir_fichero (); // con este metodo escribimos en el fichero lo que queramos


int main(){


escribir_fichero();



    return 0;


}

void escribir_fichero(){

int prueba;
ifstream f_open;   

f_open.open (nombre_fich);

ofstream f_out;



f_open>>prueba;

while(!f_open.eof()){

    cout <<prueba<<endl;
    f_open>>prueba;
}
f_open.close();


f_out.open(nombre_fich);

for(int i=0;i<5;i++){

f_out<<i<<endl;


};

f_out.close();
};