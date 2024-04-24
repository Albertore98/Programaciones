#include <iostream>
#include "banco.hpp"
#include "cuenta.hpp"
using namespace std;
int main()
{
    Banco robobank;
    Cuenta una_cuenta;
    unsigned num_cuenta;
    bool res;
    string datos="datos_banco.txt";
    string datoss="datos_banco_con_interes.txt";
    // PASO 1: leer los datos del banco del fichero "datos_banco.txt"

    robobank.leer_de_fichero(datos);

    cout << "El banco tiene "<< robobank.numero_cuentas()<<
    // PASO 2: consultar el número de cuentas del banco
     " cuentas corrientes." << endl;
    cout << "Introduzca número de cuenta para consultar: ";
    cin >> num_cuenta;
    // PASO 3: consultar la cuenta corriente cuyo número se ha pedido al usuario

    robobank.consultar_cuenta(num_cuenta,una_cuenta,res);
    if (res)
    {
        cout << "Estos son los datos de la cuenta número " << num_cuenta << ":";
        // PASO 4: mostrar las estadísticas de la cuenta corriente consultada
        una_cuenta.muestraEstadistica();
    }   

    // PASO 5: aplicar una tasa de interés del 0.01 a todas las cuentas del banco
    robobank.aplicar_interes(0.01);
    // PASO 6: escribir el banco en el fichero "datos_banco_con_interes.txt"
    robobank.escribir_en_fichero(datoss);
}
