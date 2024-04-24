#ifndef _cuenta_
#define _cuenta_

#include <string>
#include <array>
#include<iostream>

class Cuenta{

private:

std::string nombre;
unsigned cuenta;
float saldo;

public:

Cuenta();
Cuenta(std::string nombrec,unsigned numeroc,float saldoc);
Cuenta(const Cuenta &cuentaoriginal);
~Cuenta();

std::string consultarNombre();
unsigned consultarCuenta();
float consultarSaldo();

void asignarNombre(const std::string nuevonombre);
void asignarNumero(unsigned nuevonumero);
void asignarSaldo(float saldos);

float realizarIngreso(float ingreso);
float sacarDinero(float retiro);
float anyadeInteres(float interes);

void muestraEstadistica();

Cuenta & operator=(const Cuenta &otra_cuenta) {
      if (this != &otra_cuenta) {
         nombre = otra_cuenta.nombre;
         cuenta = otra_cuenta.cuenta;
         saldo = otra_cuenta.saldo;
      }

      return *this;
   }

   // OPERADOR DE COMPARACIÓN DE IGUALDAD
   // Implementado on-line por el profesor
   bool operator==(const Cuenta &otra_cuenta) const{
      return (nombre == otra_cuenta.nombre &&
              cuenta == otra_cuenta.cuenta &&
              saldo == otra_cuenta.saldo);
   }



};

#endif // !_cuenta_