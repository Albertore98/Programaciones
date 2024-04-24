#include "cuenta.hpp"

using namespace std;

void pintarMenu();

int main()
{

    string titular;
    unsigned numerocuenta;
    float saldos;

    /*cout << "introduzca el nombre de la cuenta" << endl; // hecho para probar constructores
    cin >> titular;

    cout << "introduzca  numero de cuenta" << endl;
    cin >> numerocuenta;

    cout << "introduzca  saldo" << endl;

    cin >> saldo;
*/
    Cuenta c1("Alberto", 2341, 123.4);

    unsigned opcion;
    do
    {
        pintarMenu();
        cout << " Introduzca la opcion" << endl;
        cin >> opcion;

        switch (opcion)
        {

        case 1:
            titular = c1.consultarNombre();
            cout << titular << endl;

            break;
        case 2:
            numerocuenta = c1.consultarCuenta();
            cout << numerocuenta << endl;

            break;

        case 3:
            saldos = c1.consultarSaldo();
            cout << saldos << endl;

            break;
        case 4:

            cout << "que nuevo titular desea" << endl;
            cin >> titular;
            c1.asignarNombre(titular);

            break;
        case 5:
            cout << "que nuevo numero desea" << endl;
            cin >> numerocuenta;
            c1.asignarNumero(numerocuenta);

            break;

        case 6:

            cout << "diga el ingreso" << endl;
            cin >> saldos;
            c1.realizarIngreso(saldos);
            break;

        case 7:

            cout << "diga el retiro" << endl;
            cin >> saldos;
            c1.sacarDinero(saldos);
            break;

        case 8:

            cout << "diga el interes" << endl;
            cin >> saldos;
            c1.anyadeInteres(saldos);

            break;

        case 9:

            c1.muestraEstadistica();
            break;
        }

    } while (opcion != 0);
}

void pintarMenu()
{
    cout << "MENU DE OPCIONES" << endl;
    cout << "1: Consultar el nombre de la cuenta" << endl;
    cout << "2: Consultar número de la cuenta" << endl;
    cout << "3: Consultar el saldo de la cuenta" << endl;
    cout << "4: Asignar nombre titular de la cuenta" << endl;
    cout << "5: Asignar nuevo número de cuenta" << endl;
    cout << "6: Realizar un ingreso" << endl;
    cout << "7: Retirar dinero" << endl;
    cout << "8: Aplicar intereses al saldo" << endl;
    cout << "9: Mostrar datos de la cuenta" << endl;
    cout << "0: Salir del programa" << endl;
}
