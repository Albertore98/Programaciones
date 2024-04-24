#include "lugar.hpp"
#include "trazado.hpp"

#include <iostream>
#include <random>

#ifdef __WIN32__
#include <chrono>
#endif

using namespace std;
using namespace bblProgII;

const unsigned NUM_INTENTOS = 100000;

void generar_orden_aleatorio_trazado(Trazado &trazado, uniform_int_distribution<unsigned> &dist, mt19937 &mt);

int main()
{
    Trazado trazado;
    OrdenLugares mejor_orden;
    Resultado res;

    double mejor_longitud;

    trazado.leer_trazado("localizacion.csv", res);
    escribir_resultado(res);

    if (res == OK)
    {
        cout << "TRAZADO CORRECTAMENTE LEÍDO DE DISCO..." << endl;
    }

    cout << "Trazado inicial:" << endl;
    trazado.escribir_trazado();

    mejor_longitud = trazado.longitud_trazado(METROPOL_KM);
    trazado.consultar_orden(mejor_orden);
    cout << endl
         << "Trazado inicial generado, con longitud "
         << mejor_longitud
         << " km."
         << endl;

    unsigned semilla;
    if (true) // Cambiar a true para semilla del sistema (ejecuciones diferentes)
    {
#ifdef __WIN32__
        semilla = chrono::high_resolution_clock::now().time_since_epoch().count();
#else
        random_device rd;
        semilla = rd();
#endif
    }
    else
    {
        semilla = 123;
    }

    mt19937 mt(semilla);
    uniform_int_distribution<unsigned> dist(0, trazado.consultar_num_lugares() - 1);

    // Generaciones
    for (unsigned int i = 0; i < NUM_INTENTOS; i++)
    {
        generar_orden_aleatorio_trazado(trazado, dist, mt);
        if (trazado.longitud_trazado(METROPOL_KM) < mejor_longitud)
        {
            mejor_longitud = trazado.longitud_trazado(METROPOL_KM);
            cout << endl
                 << "Orden mejorado! Longitud actual: "
                 << mejor_longitud
                 << " km."
                 << endl;
            trazado.consultar_orden(mejor_orden);
        }
    }

    cout << endl
         << "El mejor orden conseguido, con longitud "
         << mejor_longitud
         << " km, ha sido el siguiente:"
         << endl;

    trazado.escribir_trazado();

    cout << "Volcando el mejor trazado a fichero..." << endl;
    trazado.escribir_trazado("trazado_final.csv", res);

    return 0;
}

void generar_orden_aleatorio_trazado(Trazado &trazado, uniform_int_distribution<unsigned> &dist, mt19937 &mt)
{
    OrdenLugares orden;
    Resultado res;
    unsigned i, j, pos1, pos2;
    unsigned num_lugares = trazado.consultar_num_lugares();

    trazado.consultar_orden(orden);
    for (unsigned k = 0; k <= num_lugares / 2; k++)
    {
        i = dist(mt);
        pos1 = orden.orden_lugares[i];
        j = dist(mt);
        pos2 = orden.orden_lugares[j];
        orden.orden_lugares[i] = pos2;
        orden.orden_lugares[j] = pos1;
    }

    trazado.modificar_orden(orden, res);
}
