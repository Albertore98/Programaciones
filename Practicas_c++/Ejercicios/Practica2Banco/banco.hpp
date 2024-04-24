// *******************************************************************************
#ifndef _banco_hpp_
#define _banco_hpp_

#include "cuenta.hpp"
#include <fstream>

// *******************************************************************************


class Banco{

private:

static const int MaxCuenta=50;

int num_cuentas;

std::array<Cuenta,MaxCuenta> arraycuentas;

void abrirHueco(unsigned indice); 
void cerrarHueco(unsigned indice); 

public:

// Constructor por defecto: inicializa un banco a banco vacío, sin cuentas

Banco();

// Constructor de copia
Banco(const Banco&original);
// Destructor del Banco

~Banco();

// Devuelve el número de cuentas corrientes que tiene el banco
unsigned numero_cuentas();

// Consulta una cuenta corriente.
// Si la cuenta existe, la devuelve a través del segundo parámetro y
// devuelve 'true' a través de 'res'. Si no, devuelve 'false' a través
// de 'res'.
void consultar_cuenta(unsigned num_cuenta, Cuenta &cuenta, bool &res);

// Consulta el saldo de una cuenta corriente.
// Si la cuenta existe, devuelve su saldo a través del segundo parámetro y
// devuelve 'true' a través de 'res'. Si no, devuelve 'false' a través
// de 'res'.
void consultar_saldo(unsigned num_cuenta, double &saldo, bool &res);

// Consulta el titular de una cuenta corriente.
// Si la cuenta existe, devuelve su titular a través del segundo parámetro y
// devuelve 'true' a través de 'res'. Si no, devuelve 'false' a través
// de 'res'.
void consultar_titular(unsigned num_cuenta, std::string &titular, bool &res);

// Modifica el titular de una cuenta corriente.
// Si la cuenta existe, modifica su titular y
// devuelve 'true' a través de 'res'. Si no, devuelve 'false' a través
// de 'res'.
void modificar_titular(unsigned num_cuenta, const std::string &titular, bool &res);

// Inserta una nueva cuenta en el banco, con saldo 0.0 euros.
// Si el número de cuenta no existe, se inserta y se devuelve
// 'true' a través de 'res'. Si no, se devuelve 'false'.
void nueva_cuenta(const std::string &titular, unsigned num_cuenta, bool &res);

// Elimina una cuenta del banco.
// Si la cuenta existe, la elimina y devuelve 'true' a través de res.
// Si no existe, devuelve 'false'
void eliminar_cuenta(unsigned num_cuenta, bool &res);

// Ingresa dinero en una cuenta.
// Si la cuenta existe,
// incrementa su saldo con la cantidad indicada y devuelve 'true'
// a través de 'res'. Si no, devuelve 'false'.
// PRECONDICIÓN: cantidad > 0
void ingresar(double cantidad, unsigned num_cuenta, bool &res);

// Retirar dinero de una cuenta.
// Si la cuenta existe,
// decrementa su saldo con la cantidad indicada y devuelve 'true'
// a través de 'res'. Si no, devuelve 'false'.
// PRECONDICIÓN: cantidad > 0
void retirar(double cantidad, unsigned num_cuenta, bool &res);

// Lee desde fichero los datos de todas las cuentas corrientes (una cuenta por línea)
// del banco (de cada cuenta, lee su número, su saldo, y su titular).
void leer_de_fichero(const std::string &nom_fichero);

// Aplica la tasa de intereses bancarios a todas las cuentas del banco
// Precondicion: tasa_interes > 0.0 && tasa_interes <= 1.0
void aplicar_interes(double tasa_interes);

// Escribe en fichero los datos de todas las cuentas corrientes (una cuenta por línea)
// del banco (de cada cuenta, escribe su número, su saldo, y su titular).
void escribir_en_fichero(const std::string &nom_fichero);

// OPERADOR DE ASIGNACIÓN
// (Implementado on-line por el profesor)
Banco &operator=(const Banco &otro_banco)
{
      if (this != &otro_banco)
      {
            arraycuentas = otro_banco.arraycuentas;
            num_cuentas = otro_banco.num_cuentas;
      }

      return *this;
}

// OPERADOR DE COMPARACIÓN DE IGUALDAD
// (Implementado on-line por el profesor)
bool operator==(const Banco &otro_banco) const
{
      bool ok = num_cuentas == otro_banco.num_cuentas;

      int i = 0;

      while (ok && i < num_cuentas)
      {
            ok = arraycuentas[i] == otro_banco.arraycuentas[i];
            i++;
      }

      return ok;
}



};

#endif // !_banco_hpp_