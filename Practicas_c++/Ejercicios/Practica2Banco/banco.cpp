#include "banco.hpp"
#include <iomanip>
Banco::Banco() : num_cuentas(0){};

Banco::Banco(const Banco &original)
{

    num_cuentas = original.num_cuentas;
    for (int i = 0; i < num_cuentas; i++)
    {
        arraycuentas[i].operator=(original.arraycuentas[i]);
    }
};

Banco::~Banco(){};

unsigned Banco::numero_cuentas()
{
    unsigned n = num_cuentas;

    return n;
}

void Banco::abrirHueco(unsigned indice)
{

    for (unsigned pos = MaxCuenta; pos > indice; pos--)
    {
        arraycuentas[pos] = arraycuentas[pos - 1];
    }
}
void Banco::cerrarHueco(unsigned indice)
{

    for (unsigned pos = indice; pos < MaxCuenta; pos++)
    {
        arraycuentas[pos] = arraycuentas[pos + 1];
    }
}



void Banco::consultar_cuenta(unsigned num_cuenta, Cuenta &cuenta, bool &res)
{

    res = false;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            res = true;
            cuenta.operator=(arraycuentas[i]);
        };
    }
};

void Banco::consultar_saldo(unsigned num_cuenta, double &saldo, bool &res)
{
    res = false;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            res = true;
            saldo = (arraycuentas[i].consultarSaldo());
        };
    }
}

void Banco::consultar_titular(unsigned num_cuenta, std::string &titular, bool &res)
{
    res = false;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            res = true;
            titular = (arraycuentas[i].consultarNombre());
        };
    }
}

void Banco::modificar_titular(unsigned num_cuenta, const std::string &titular, bool &res)
{

    res = false;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            res = true;
            arraycuentas[i].asignarNombre(titular);
        };
    }
}

void Banco::nueva_cuenta(const std::string &titular, unsigned num_cuenta, bool &res)
{
    res = true;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            res = false;
        }
    }

    if (res)
    {
        abrirHueco(num_cuentas);
        arraycuentas[num_cuentas].asignarNombre(titular);
        arraycuentas[num_cuentas].asignarNumero(num_cuenta);
        arraycuentas[num_cuentas].asignarSaldo(0.0);
        
        num_cuentas++;
        
        
        res = true;
    }
};

void Banco::eliminar_cuenta(unsigned num_cuenta, bool &res)
{

    res = false;
    bool existe = false;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            existe = true;
        };
    }

    if (existe)
    {
        res = true;
        cerrarHueco(num_cuentas);
        num_cuentas--;
    }
}

void Banco::ingresar(double cantidad, unsigned num_cuenta, bool &res)
{

    bool existe = false;
    int indice;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            existe = true;
            indice = i;
        };
    }

    if (existe)
    {
        res = true;
        arraycuentas[indice].realizarIngreso(cantidad);
    }
}
void Banco::retirar(double cantidad, unsigned num_cuenta, bool &res)
{

    bool existe = false;
    int indice;

    for (int i = 0; i < MaxCuenta; i++)
    {
        if (num_cuenta == arraycuentas[i].consultarCuenta())
        {
            existe = true;
            indice = i;
        };
    }

    if (existe)
    {
        res = true;
        arraycuentas[indice].sacarDinero(cantidad);
    }
}

void Banco::aplicar_interes(double tasa_interes)
{

    for (int i = 0; i < MaxCuenta; i++)
    {
        arraycuentas[i].anyadeInteres(tasa_interes);
    }
}

void Banco::leer_de_fichero(const std::string &nom_fichero)
{

    std::ifstream entrada;
    entrada.open(nom_fichero);
    unsigned aux;
    float aux2;
    std::string aux3;

    if (!entrada.fail())
    {

        entrada >> std::ws;
        entrada >> aux >> aux2;
        arraycuentas[num_cuentas].asignarNumero(aux);
        arraycuentas[num_cuentas].asignarSaldo(aux2);
        std::getline(entrada, aux3);
        arraycuentas[num_cuentas].asignarNombre(aux3);
        num_cuentas++;

        while (!entrada.eof())
        {

            entrada >> aux >> aux2;
            arraycuentas[num_cuentas].asignarNumero(aux);
            arraycuentas[num_cuentas].asignarSaldo(aux2);
            std::getline(entrada, aux3);
            arraycuentas[num_cuentas].asignarNombre(aux3);
            num_cuentas++;
        }
    }
    else
    {

        std::cout << "error en el fichero" << std::endl;
    };

    entrada.close();
}

void Banco::escribir_en_fichero(const std::string &nom_fichero)
{
    std::ofstream salida;
    salida.open(nom_fichero);

    if (!salida.fail())
    {

        salida << arraycuentas[0].consultarCuenta() << " ";
        salida << arraycuentas[0].consultarSaldo() << " ";
        salida << arraycuentas[0].consultarNombre() << std::endl;

        for (int i = 1; i < num_cuentas; i++)
        {

            salida << arraycuentas[i].consultarCuenta() << " ";
            salida << arraycuentas[i].consultarSaldo() << " ";
            salida << arraycuentas[i].consultarNombre() << std::endl;
        }
    }
    else
    {

        std::cout << "error en el fichero" << std::endl;
    };

    salida.close();
}
