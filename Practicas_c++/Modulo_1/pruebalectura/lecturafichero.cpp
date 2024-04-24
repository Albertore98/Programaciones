#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string nombre_fic = "localizacion.csv";
int main()
{

    string nombre, direccion,aux,aux2;
     double latitud, longitud;
     string lat,longi;

    ifstream entrada;

    entrada.open(nombre_fic);

    if (!entrada.fail())
    {

        getline(entrada,aux);
        entrada.ignore();
        cout<<aux<<endl;
     //   while (!entrada.eof())
       // {
            getline(entrada, nombre, '"');
            cout<<nombre;
            entrada.ignore(2);
            getline(entrada,direccion,'"');
            cout<<direccion;
            entrada.ignore(1);
            getline(entrada,lat,',');
            latitud=stod(lat);
            cout<<latitud;
            entrada.ignore(1);
            getline(entrada,longi,',');
            longitud=stod(longi);
            cout<<longitud;
            entrada.ignore();

            
          /* entrada>>latitud;
            cout<<latitud;
            entrada.ignore(1);
            entrada>>longitud;
            cout<<longitud;
*/
      //  }
    }

    entrada.close();

    return 0;
}