/*****************************************************************************
 * Programa principal de prueba (pruebas unitarias) de la clase Cuenta
 ****************************************************************************/

#include <iostream>
#include <string>
#include <cassert>

#include "cuenta.hpp"

using namespace std;


void test_constructor(){
	Cuenta c;

	assert(c.consultarNombre() == "");
	assert(c.consultarCuenta() == 0);
	assert(c.consultarSaldo() == 0.0);
}

void test_constructor_extendido(){
	Cuenta c("Ana", 111, 100.0);

	assert(c.consultarNombre() == "Ana");
	assert(c.consultarCuenta() == 111);
	assert(c.consultarSaldo() == 100.0);	
}

void test_constructor_copia(){
	Cuenta org("Ana", 111, 100.0), c(org);

	assert(c.consultarNombre() == "Ana");
	assert(c.consultarCuenta() == 111);
	assert(c.consultarSaldo() == 100.0);
	assert(c == org);
}

void test_asignar_consultar_nombre(){
	Cuenta c;

	c.asignarNombre("Ana");
	assert(c.consultarNombre() == "Ana");
}

void test_asignar_consultar_numero(){
	Cuenta c;

	c.asignarNumero(111);
	assert(c.consultarCuenta() == 111);
}

void test_anyadir_consultar_saldo(){
	Cuenta c;
	double saldo;

	assert(c.consultarSaldo() == 0.0);

	saldo = c.realizarIngreso(100.0);
	assert(c.consultarSaldo() == 100.0);
	assert(saldo == 100.0);
}

void test_sacar_consultar_saldo(){
	Cuenta c("Ana", 111, 100.0);
	double saldo;

	assert(c.consultarSaldo() == 100.0);

	saldo = c.sacarDinero(200.0);
	assert(c.consultarSaldo() == 100.0);
	assert(saldo == 100.0);

	saldo = c.sacarDinero(50.0);
	assert(c.consultarSaldo() == 50.0);
	assert(saldo == 50.0);
}

void test_anyade_interes(){
	Cuenta c("Ana", 111, 100.0);

	c.anyadeInteres(0.01);

	assert(c.consultarSaldo() == 101.0);
}


int main(){
	test_constructor();
	test_constructor_extendido();
	test_constructor_copia();
	test_asignar_consultar_nombre();
	test_asignar_consultar_numero();
	test_anyadir_consultar_saldo();
	test_sacar_consultar_saldo();
	test_anyade_interes();

	cout << "--- OK." << endl;

	return 0;
}