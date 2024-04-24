/*****************************************************************************
 * Programa principal de prueba (pruebas unitarias) de la clase Cuenta
 ****************************************************************************/

#include <iostream>
#include <cassert>
#include <cmath>
#include "banco.hpp"
#include "cuenta.hpp"

using namespace std;


void test_constructor() {
	Banco b;

	assert(b.numero_cuentas() == 0);
}

void test_nueva_cuenta() {
	Banco b;
	bool res;

	b.nueva_cuenta("Ana", 111, res);
	assert(res);
	assert(b.numero_cuentas() == 1);
	b.nueva_cuenta("Juan", 222, res);
	assert(res);
	assert(b.numero_cuentas() == 2);
	b.nueva_cuenta("Maria", 333, res);
	assert(res);
	assert(b.numero_cuentas() == 3);

	//b.numero_cuentas();
}

void test_constructor_copia() {
	Banco org;
	bool res;

	assert(org == Banco(org)); // Constructor de copia

	org.nueva_cuenta("Ana", 111, res);
	org.nueva_cuenta("Juan", 222, res);
	org.nueva_cuenta("Maria", 333, res);

	assert(org == Banco(org)); // Constructor de copia
}

void test_consultar_cuenta() {
	Banco b;
	bool res;
	Cuenta c;

	b.nueva_cuenta("Ana", 111, res);
	b.nueva_cuenta("Juan", 222, res);
	b.nueva_cuenta("Maria", 333, res);

	b.consultar_cuenta(111, c, res);
	assert(res);
	assert(c.consultarNombre() == "Ana" &&
	       c.consultarCuenta() == 111 &&
	       c.consultarSaldo() == 0.0);

	b.consultar_cuenta(222, c, res);
	assert(res);
	assert(c.consultarNombre() == "Juan" &&
	       c.consultarCuenta() == 222 &&
	       c.consultarSaldo() == 0.0);

	b.consultar_cuenta(333, c, res);
	assert(res);
	assert(c.consultarNombre() == "Maria" &&
	       c.consultarCuenta() == 333 &&
	       c.consultarSaldo() == 0.0);

}

void test_consultar_saldo() {
	Banco b;
	bool res;
	double saldo;

	b.nueva_cuenta("Ana", 111, res);

	b.consultar_saldo(111, saldo, res);
	assert(res);
	assert(saldo == 0.0);
}

void test_consultar_titular() {
	Banco b;
	bool res;
	string titular;

	b.nueva_cuenta("Ana", 111, res);

	b.consultar_titular(111, titular, res);
	assert(res);
	assert(titular == "Ana");
}

void test_modificar_titular() {
	Banco b;
	bool res;
	string titular;

	b.nueva_cuenta("Ana", 111, res);

	b.modificar_titular(111, "Maria", res);
	assert(res);
	b.consultar_titular(111, titular, res);
	assert(titular == "Maria");
}

void test_eliminar_cuenta() {
	Banco b;
	bool res;
	Cuenta c;

	b.nueva_cuenta("Ana", 111, res);
	b.nueva_cuenta("Juan", 222, res);
	b.nueva_cuenta("Maria", 333, res);

	b.eliminar_cuenta(111, res);
	assert(res);
	b.consultar_cuenta(111, c, res);
	assert(!res);
	assert(b.numero_cuentas() == 2);
	b.eliminar_cuenta(222, res);
	assert(res);
	b.consultar_cuenta(222, c, res);
	assert(!res);
	assert(b.numero_cuentas() == 1);
	b.eliminar_cuenta(333, res);
	assert(res);
	b.consultar_cuenta(333, c, res);
	assert(!res);
	assert(b.numero_cuentas() == 0);
	assert(b == Banco());
}


void test_ingresar() {
	Banco b;
	bool res;
	Cuenta c;

	b.nueva_cuenta("Ana", 111, res);
	b.nueva_cuenta("Juan", 222, res);
	b.nueva_cuenta("Maria", 333, res);

	b.ingresar(100.0, 111, res);
	assert(res);
	b.consultar_cuenta(111, c, res);
	assert(c.consultarSaldo() == 100.0);
	b.ingresar(200.0, 222, res);
	assert(res);
	b.consultar_cuenta(222, c, res);
	assert(c.consultarSaldo() == 200.0);
}

void test_retirar() {
	Banco b;
	bool res;
	Cuenta c;

	b.nueva_cuenta("Ana", 111, res);
	b.nueva_cuenta("Juan", 222, res);
	b.nueva_cuenta("Maria", 333, res);

	b.ingresar(100.0, 111, res);
	assert(res);
	b.consultar_cuenta(111, c, res);
	assert(c.consultarSaldo() == 100.0);
	b.ingresar(200.0, 222, res);
	assert(res);
	b.consultar_cuenta(222, c, res);
	assert(c.consultarSaldo() == 200.0);

	b.retirar(50.0, 111, res);
	assert(res);
	b.consultar_cuenta(111, c, res);
	assert(c.consultarSaldo() == 50.0);
	b.retirar(300.0, 222, res);
	assert(res);
	b.consultar_cuenta(222, c, res);
	assert(c.consultarSaldo() == 200.0);
}


void test_leer_fichero() {
	const string nombre_fichero = "datos_banco.txt";
	Banco b;
	Cuenta c;
	bool res;

	b.leer_de_fichero(nombre_fichero);

	assert(b.numero_cuentas() == 5);

	b.consultar_cuenta(111, c, res);
	assert(res);
	assert(c == Cuenta("Ana Bolizante", 111, 1234.56));
	b.consultar_cuenta(222, c, res);
	assert(res);
	assert(c == Cuenta("Aitor Tilla", 222, 2345.67));
	b.consultar_cuenta(333, c, res);
	assert(res);
	assert(c == Cuenta("Juan Hete", 333, 54673.12));
	b.consultar_cuenta(444, c, res);
	assert(res);
	assert(c == Cuenta("Miguel Illo", 444, 2.5));
	b.consultar_cuenta(555, c, res);
	assert(res);
	assert(c == Cuenta("Mariano Recortes", 555, 89092.83));
}

void test_intereses(){
	const string nombre_fichero = "datos_banco.txt";
	Banco b;
	Cuenta c;
	bool res;

	b.leer_de_fichero(nombre_fichero);

	b.aplicar_interes(0.01);

	b.consultar_cuenta(111, c, res);
	assert(res);
	assert(c == Cuenta("Ana Bolizante", 111, 1234.56 + 1234.56 * 0.01));
	b.consultar_cuenta(222, c, res);
	assert(res);
	assert(c == Cuenta("Aitor Tilla", 222, 2345.67 + 2345.67 * 0.01));
	b.consultar_cuenta(333, c, res);
	assert(res);
	assert(c == Cuenta("Juan Hete", 333, 54673.12 + 54673.12 * 0.01));
	b.consultar_cuenta(444, c, res);
	assert(res);
	assert(c == Cuenta("Miguel Illo", 444, 2.50 + 2.50 * 0.01));
	b.consultar_cuenta(555, c, res);
	assert(res);
	assert(c == Cuenta("Mariano Recortes", 555, 89092.83 + 89092.83 * 0.01));
}

void test_escribir_fichero(){
	const string nombre_fichero_in = "datos_banco.txt";
	const string nombre_fichero_out = "copia_datos_banco.txt";
	Banco b;
	Cuenta c;
	bool res;

	b.leer_de_fichero(nombre_fichero_in);
	b.escribir_en_fichero(nombre_fichero_out);
	b = Banco();
	b.leer_de_fichero(nombre_fichero_out);

	assert(b.numero_cuentas() == 5);

	b.consultar_cuenta(111, c, res);
	assert(res);
	assert(c == Cuenta("Ana Bolizante", 111, 1234.56));
	b.consultar_cuenta(222, c, res);
	assert(res);
	assert(c == Cuenta("Aitor Tilla", 222, 2345.67));
	b.consultar_cuenta(333, c, res);
	assert(res);
	assert(c == Cuenta("Juan Hete", 333, 54673.12));
	b.consultar_cuenta(444, c, res);
	assert(res);
	assert(c == Cuenta("Miguel Illo", 444, 2.5));
	b.consultar_cuenta(555, c, res);
	assert(res);
	assert(c == Cuenta("Mariano Recortes", 555, 89092.83));
}

int main() {

	test_constructor();

	test_nueva_cuenta();

	test_constructor_copia();

	test_consultar_cuenta();

	test_consultar_saldo();

	test_consultar_titular();

	test_modificar_titular();

	test_eliminar_cuenta();

	test_ingresar();

	test_retirar();

	test_leer_fichero();

	test_intereses();

	test_escribir_fichero();

	cout << "--- OK." << endl;

	return 0;
}