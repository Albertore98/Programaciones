/******************************************************************************
 * test_trazado.cpp
 *
 * Programa principal de prueba del módulo Trazado.
 *
 * Alumno/a:
 * Fecha:
 *****************************************************************************/

#include "lugar.hpp"
#include "trazado.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace bblProgII;

const string FIC_LUGARES = "localizacion.csv";

// Prueba del constructor por defecto
void test_constructor()
{
    Trazado tr;
    ListaLugares lgs;
    OrdenLugares od;

    assert(tr.consultar_num_lugares() == 0);

    tr.consultar_lugares(lgs);
    assert(lgs.num_lugares == 0);
    tr.consultar_orden(od);
    assert(od.num_lugares == 0);
}

// Prueba del constructor específico
void test_constructor_especifico()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs, lgs_aux;
    OrdenLugares ord, ord_aux;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    tr.consultar_lugares(lgs_aux);
    tr.consultar_orden(ord_aux);

    assert(lgs_aux.num_lugares == lgs.num_lugares);
    assert(lgs_aux.lista_lugares == lgs.lista_lugares);
    assert(ord_aux.num_lugares == ord.num_lugares);
    assert(ord_aux.orden_lugares == ord.orden_lugares);
}

// Prueba del constructor de copia
void test_constructor_copia()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    Trazado tr_copia(tr);

    assert(tr == tr_copia);
}

// Prueba de consultar_lugar
void test_consultar_lugar()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);
    Lugar lg_aux;

    tr.consultar_lugar(1, lg_aux);
    assert(lg_aux == lg1);
    tr.consultar_lugar(2, lg_aux);
    assert(lg_aux == lg2);
}

// Prueba de consultar_pos_lugar
void test_consultar_pos_lugar()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    unsigned pos;
    Resultado res;

    tr.consultar_pos_lugar(0.3, 0.4, pos, res);
    assert(pos == 2);
    assert(res == OK);

    tr.consultar_pos_lugar(0.1, 0.2, pos, res);
    assert(pos == 1);
    assert(res == OK);

    tr.consultar_pos_lugar(0.1, 0.1, pos, res);
    assert(res == NO_EXISTE);
}

// Prueba de consultar_trazado
void test_consultar_trazado()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs, lgs_aux;
    OrdenLugares ord, ord_aux;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    tr.consultar_trazado(lgs_aux, ord_aux);

    assert(lgs_aux.num_lugares == lgs.num_lugares);
    assert(lgs_aux.lista_lugares == lgs.lista_lugares);
    assert(ord_aux.num_lugares == ord.num_lugares);
    assert(ord_aux.orden_lugares == ord.orden_lugares);
}

// Prueba de consultar_lugares
void test_consultar_lugares()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs, lgs_aux;
    OrdenLugares ord;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    tr.consultar_lugares(lgs_aux);

    assert(lgs_aux.num_lugares == lgs.num_lugares);
    assert(lgs_aux.lista_lugares == lgs.lista_lugares);
}

// Prueba de consultar_orden
void test_consultar_orden()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs;
    OrdenLugares ord, ord_aux;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr(lgs, ord);

    tr.consultar_orden(ord_aux);

    assert(ord_aux.num_lugares == ord.num_lugares);
    assert(ord_aux.orden_lugares == ord.orden_lugares);
}

// Prueba de consultar_num_lugares
void test_consultar_num_lugares()
{
    Lugar lg1("_calle_1", "_direccion_1", 0.1, 0.2);
    Lugar lg2("_calle_2", "_direccion_2", 0.3, 0.4);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 2;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    ord.num_lugares = 2;
    ord.orden_lugares[0] = 1;
    ord.orden_lugares[1] = 2;

    Trazado tr1;
    assert(tr1.consultar_num_lugares() == 0);
    Trazado tr2(lgs, ord);
    assert(tr2.consultar_num_lugares() == 2);
}

// Prueba de consultar_distancia
void test_consultar_distancia()
{
    const double DIF_MAXIMA = 1e-6;

    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 2;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 3;

    Trazado tr(lgs, ord);
    // cout << setprecision(10);
    // cout << "Euclidea 1-2: " << tr.consultar_distancia(1, 2, EUCLIDEA) << endl;
    assert(abs(tr.consultar_distancia(1, 2, EUCLIDEA) - 1.414213562) < DIF_MAXIMA);
    // cout << "Euclidea 1-3: " << tr.consultar_distancia(1, 3, EUCLIDEA) << endl;
    assert(abs(tr.consultar_distancia(1, 3, EUCLIDEA) - 2.828427125) < DIF_MAXIMA);
    // cout << "Euclidea 2-3: " << tr.consultar_distancia(2, 3, EUCLIDEA) << endl;
    assert(abs(tr.consultar_distancia(2, 3, EUCLIDEA) - 4.242640687) < DIF_MAXIMA);
    // cout << "Euclidea km 1-2: " << tr.consultar_distancia(1, 2, EUCLIDEA_KM) << endl;
    assert(abs(tr.consultar_distancia(1, 2, EUCLIDEA_KM) - 157.398180) < DIF_MAXIMA);
    // cout << "Euclidea km 1-3: " << tr.consultar_distancia(1, 3, EUCLIDEA_KM) << endl;
    assert(abs(tr.consultar_distancia(1, 3, EUCLIDEA_KM) - 314.6285671) < DIF_MAXIMA);
    // cout << "Euclidea km 2-3: " << tr.consultar_distancia(2, 3, EUCLIDEA_KM) << endl;
    assert(abs(tr.consultar_distancia(2, 3, EUCLIDEA_KM) - 472.026613) < DIF_MAXIMA);
    // cout << "Manhattan 1-2: " << tr.consultar_distancia(1, 2, METROPOL) << endl;
    assert(abs(tr.consultar_distancia(1, 2, METROPOL) - 2.0) < DIF_MAXIMA);
    // cout << "Manhattan 1-3: " << tr.consultar_distancia(1, 3, METROPOL) << endl;
    assert(abs(tr.consultar_distancia(1, 3, METROPOL) - 4.0) < DIF_MAXIMA);
    // cout << "Manhattan 2-3: " << tr.consultar_distancia(2, 3, METROPOL) << endl;
    assert(abs(tr.consultar_distancia(2, 3, METROPOL) - 6.0) < DIF_MAXIMA);
    // cout << "Manhattan km 1-2: " << tr.consultar_distancia(1, 2, METROPOL_KM) << endl;
    double val12 = tr.consultar_distancia(1, 2, METROPOL_KM);
    double val13 = tr.consultar_distancia(1, 3, METROPOL_KM);
    double val23 = tr.consultar_distancia(2, 3, METROPOL_KM);
    // cout << "Manhattan km 1-2: " << val12 << endl;
    assert(abs(val12 - 222.6172448) < DIF_MAXIMA || abs(val12 - 222.5663863) < DIF_MAXIMA);
    // cout << "Manhattan km 1-3: " << val13 << endl;
    assert(abs(val13 - 444.7260182) < DIF_MAXIMA || abs(val13 - 445.1327623) < DIF_MAXIMA);
    // cout << "Manhattan km 2-3: " << val23 << endl;
    assert(abs(val23 - 667.0889243) < DIF_MAXIMA || abs(val23 - 667.8517241) < DIF_MAXIMA);
}

// Prueba longitud_trazado
void test_longitud_trazado()
{
    const double DIF_MAXIMA = 1e-2;

    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 3;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 2;

    Trazado tr(lgs, ord);

    // cout << tr.longitud_trazado(EUCLIDEA) << endl;
    assert(abs(tr.longitud_trazado(EUCLIDEA) - 8.48528) < DIF_MAXIMA);
    // cout << tr.longitud_trazado(EUCLIDEA_KM) << endl;
    assert(abs(tr.longitud_trazado(EUCLIDEA_KM) - 944.053) < DIF_MAXIMA);
    // cout << tr.longitud_trazado(METROPOL) << endl;
    assert(abs(tr.longitud_trazado(METROPOL) - 12.0) < DIF_MAXIMA);
    // cout << tr.longitud_trazado(METROPOL_KM) << endl;
    double val = tr.longitud_trazado(METROPOL_KM);
    assert(abs(val - 1335.144129) < DIF_MAXIMA || abs(val - 1334.838931) < DIF_MAXIMA || abs(val - 1335.194987) < DIF_MAXIMA || abs(val - 1334.788073) < DIF_MAXIMA );
}

// Prueba de void insertar_lugar
void test_insertar_lugar()
{
    Trazado tr;
    Resultado res;

    for (unsigned i = 0; i < MAX_LUGARES; i++)
    {
        Lugar lg("_calle_", "_direccion_", double(i), double(i));

        tr.insertar_lugar(lg, res);
        assert(tr.consultar_num_lugares() == i + 1);
        assert(res == OK);
    }

    Lugar lg1("_calle_", "_direccion_", 5.0, 5.0);
    tr.insertar_lugar(lg1, res);
    assert(tr.consultar_num_lugares() == MAX_LUGARES);
    assert(res == YA_EXISTE);

    Lugar lg2("_calle_", "_direccion_", double(MAX_LUGARES), double(MAX_LUGARES));
    tr.insertar_lugar(lg2, res);
    assert(tr.consultar_num_lugares() == MAX_LUGARES);
    assert(res == LISTA_LLENA);
}

// Prueba de eliminar_lugar
void test_eliminar_lugar()
{
    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 3;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 2;

    Trazado tr(lgs, ord), tr_copia(tr);

    tr.eliminar_lugar(2);
    assert(tr.consultar_num_lugares() == 2);
    tr.consultar_orden(ord);
    assert(ord.orden_lugares[0] == 2);
    assert(ord.orden_lugares[1] == 1);

    tr_copia.eliminar_lugar(1);
    assert(tr_copia.consultar_num_lugares() == 2);
    tr_copia.consultar_orden(ord);
    assert(ord.orden_lugares[0] == 2);
    assert(ord.orden_lugares[1] == 1);

    tr_copia.eliminar_lugar(1);
    assert(tr_copia.consultar_num_lugares() == 1);
    tr_copia.consultar_orden(ord);
    assert(ord.orden_lugares[0] == 1);

    tr_copia.eliminar_lugar(1);
    assert(tr_copia.consultar_num_lugares() == 0);
}

// Prueba de modificar_trazado
void test_modificar_trazado()
{
    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 3;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 2;

    Trazado tr;
    Resultado res;
    tr.modificar_trazado(lgs, ord, res);
    assert(res == OK);

    ord.num_lugares = 2;
    tr.modificar_trazado(lgs, ord, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    ord.num_lugares = 3;
    lgs.num_lugares = 2;
    tr.modificar_trazado(lgs, ord, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    lgs.num_lugares = 3;
    ord.orden_lugares[2] = 3;
    tr.modificar_trazado(lgs, ord, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    ord.orden_lugares[2] = 5;
    tr.modificar_trazado(lgs, ord, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    ord.orden_lugares[2] = 2;
    lgs.lista_lugares[0] = lgs.lista_lugares[1];
    tr.modificar_trazado(lgs, ord, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);
}

// Prueba de modificar_trazado
void test_modificar_lugares()
{
    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 3;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 2;

    Trazado tr(lgs, ord);
    Resultado res;
    tr.modificar_lugares(lgs, res);
    assert(res == OK);

    lgs.num_lugares = 2;
    tr.modificar_lugares(lgs, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lgs.lista_lugares[1];
    tr.modificar_lugares(lgs, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);
}

// Prueba de modificar_orden
void test_modificar_orden()
{
    Lugar lg1("_calle_1", "_direccion_1", 1.0, 1.0);
    Lugar lg2("_calle_2", "_direccion_2", 2.0, 2.0);
    Lugar lg3("_calle_2", "_direccion_2", 4.0, 4.0);
    ListaLugares lgs;
    OrdenLugares ord;

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lg1;
    lgs.lista_lugares[1] = lg2;
    lgs.lista_lugares[2] = lg3;
    ord.num_lugares = 3;
    ord.orden_lugares[0] = 3;
    ord.orden_lugares[1] = 1;
    ord.orden_lugares[2] = 2;

    Trazado tr(lgs, ord);
    Resultado res;
    tr.modificar_lugares(lgs, res);
    assert(res == OK);

    lgs.num_lugares = 2;
    tr.modificar_lugares(lgs, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);

    lgs.num_lugares = 3;
    lgs.lista_lugares[0] = lgs.lista_lugares[1];
    tr.modificar_lugares(lgs, res);
    assert(res == VAL_ERROR);
    assert(tr.consultar_num_lugares() == 3);
}

// Prueba de leer_trazado
void test_leer_trazado()
{
    Trazado tr;
    ListaLugares lgs;
    OrdenLugares ord;

    Resultado res;
    tr.leer_trazado("fichero_fake.csv", res);
    assert(res == FIC_ERROR);

    tr.leer_trazado(FIC_LUGARES, res);
    assert(res == OK);
    assert(tr.consultar_num_lugares() == 20);

    tr.consultar_trazado(lgs, ord);
    assert(lgs.lista_lugares[0].consultar_nombre() == "Facultad de Ciencias");
    assert(lgs.lista_lugares[0].consultar_direccion() == "Bulevar Louis Pasteur, 31, 29010 Malaga");
    assert(lgs.lista_lugares[0].consultar_latitud() == 36.715718);
    assert(lgs.lista_lugares[0].consultar_longitud() == -4.472966);
    assert(lgs.lista_lugares[19].consultar_nombre() == "The Green Ray - El rayo verde");
    assert(lgs.lista_lugares[19].consultar_direccion() == "Bulevar Louis Pasteur, 47, 29010 Malaga");
    assert(lgs.lista_lugares[19].consultar_latitud() == 36.718778);
    assert(lgs.lista_lugares[19].consultar_longitud() == -4.496998);
}

// Prueba de escribir_trazado (en disco)
void test_escribir_trazado()
{
    Trazado tr;
    ListaLugares lgs;
    OrdenLugares ord;

    Resultado res;

    tr.leer_trazado(FIC_LUGARES, res);
    tr.escribir_trazado("copia_localizacion.csv", res);
    assert(res == OK);
    tr = Trazado();
    tr.leer_trazado("copia_localizacion.csv", res);
    assert(tr.consultar_num_lugares() == 20);

    tr.consultar_trazado(lgs, ord);
    assert(lgs.lista_lugares[0].consultar_nombre() == "Facultad de Ciencias");
    assert(lgs.lista_lugares[0].consultar_direccion() == "Bulevar Louis Pasteur, 31, 29010 Malaga");
    assert(lgs.lista_lugares[0].consultar_latitud() == 36.715718);
    assert(lgs.lista_lugares[0].consultar_longitud() == -4.472966);
    assert(lgs.lista_lugares[19].consultar_nombre() == "The Green Ray - El rayo verde");
    assert(lgs.lista_lugares[19].consultar_direccion() == "Bulevar Louis Pasteur, 47, 29010 Malaga");
    assert(lgs.lista_lugares[19].consultar_latitud() == 36.718778);
    assert(lgs.lista_lugares[19].consultar_longitud() == -4.496998);
}

//**********************
int main()
{
    // Prueba del constructor por defecto
    cout << "testing... 'Trazado()'" << endl;
    test_constructor();
    cout << "   --- OK." << endl;

    // Prueba del constructor específico
    cout << "testing... 'Trazado(const ListaLugares &, const OrdenLugares &)'" << endl;
    test_constructor_especifico();
    cout << "   --- OK." << endl;

    // Prueba del constructor de copia
    cout << "testing... 'Trazado(const Trazado &)'" << endl;
    test_constructor_copia();
    cout << "   --- OK." << endl;

    // Prueba de consultar_lugar
    cout << "testing... 'void consultar_lugar(unsigned, Lugar &) const'" << endl;
    test_consultar_lugar();
    cout << "   --- OK." << endl;

    // Prueba de consultar_pos_lugar
    cout << "testing... 'void consultar_pos_lugar(double, double, unsigned &, Resultado &) const'" << endl;
    test_consultar_pos_lugar();
    cout << "   --- OK." << endl;

    // Prueba de consultar_trazado
    cout << "testing... 'void consultar_trazado(ListaLugares &, OrdenLugares &) const'" << endl;
    test_consultar_trazado();
    cout << "   --- OK." << endl;

    // Prueba de consultar_lugares
    cout << "testing... 'void consultar_lugares(ListaLugares &) const'" << endl;
    test_consultar_lugares();
    cout << "   --- OK." << endl;

    // Prueba de consultar_orden
    cout << "testing... 'void consultar_orden(OrdenLugares &) const'" << endl;
    test_consultar_orden();
    cout << "   --- OK." << endl;

    // Prueba de consultar_num_lugares
    cout << "testing... 'unsigned consultar_num_lugares() const'" << endl;
    test_consultar_num_lugares();
    cout << "   --- OK." << endl;

    // Prueba de consultar_distancia
    cout << "testing... 'double consultar_distancia(unsigned, unsigned, Distancia) const'" << endl;
    test_consultar_distancia();
    cout << "   --- OK." << endl;

    // Prueba de longitud_trazado
    cout << "testing... 'double longitud_trazado(Distancia) const'" << endl;
    test_longitud_trazado();
    cout << "   --- OK." << endl;

    // Prueba de insertar_lugar
    cout << "testing... 'void insertar_lugar(const Lugar &, Resultado &)'" << endl;
    test_insertar_lugar();
    cout << "   --- OK." << endl;

    // Prueba de eliminar_lugar
    cout << "testing... 'void eliminar_lugar(unsigned)'" << endl;
    test_eliminar_lugar();
    cout << "   --- OK." << endl;

    // Prueba de modificar_trazado
    cout << "testing... 'void modificar_trazado(const ListaLugares &, const OrdenLugares &, Resultado &)'" << endl;
    test_modificar_trazado();
    cout << "   --- OK." << endl;

    // Prueba de modificar_lugares
    cout << "testing... 'void modificar_lugares(const ListaLugares &, Resultado &)'" << endl;
    test_modificar_lugares();
    cout << "   --- OK." << endl;

    // Prueba de modificar_orden
    cout << "testing... 'void modificar_orden(const OrdenLugares &, Resultado &)'" << endl;
    test_modificar_orden();
    cout << "   --- OK." << endl;

    // Prueba de leer_trazado
    cout << "testing... 'void leer_trazado(const std::string &, Resultado &)'" << endl;
    test_leer_trazado();
    cout << "   --- OK." << endl;

    // Prueba de escribir_trazado
    cout << "testing... 'void escribir_trazado(const std::string &, Resultado &)'" << endl;
    test_escribir_trazado();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;

    return 0;
}
