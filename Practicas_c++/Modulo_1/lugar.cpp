/******************************************************************************
 * Fichero lugar.cpp para la implementación de los métodos de la clase
 * Lugar para la gestión de la información correspondiente con un punto
 * geográfico en el plano.
 *
 * Autor/a:
 * Fecha:
 * ***************************************************************************/

#include "lugar.hpp"
#include <string>
// #define _USE_MATH_DEFINES
#include <cmath>

// FUNCIONES AUXILIARES PARA LA PRÁCTICA
namespace
{
    const double PI = 4.0 * atan(1.0);
    double grados_a_radianes(double grados)
    {
        // return grados * M_PI / 180.0;
        return grados * PI / 180.0;
    }

    // Devuelve la distancia en kilómetros entre dos puntos
    //  cuya latitud y longitud se indica.
    double distancia_haversine(double latitud1, double longitud1, double latitud2, double longitud2)
    {
        const double RADIO_TERRESTRE = 6378.0; // Radio terrestre en el ecuador

        latitud1 = grados_a_radianes(latitud1);
        longitud1 = grados_a_radianes(longitud1);
        latitud2 = grados_a_radianes(latitud2);
        longitud2 = grados_a_radianes(longitud2);

        double dif_lat = latitud2 - latitud1;
        double dif_lon = longitud2 - longitud1;

        double a = pow(sin(dif_lat / 2.0), 2.0) + cos(latitud1) * cos(latitud2) * pow(sin(dif_lon / 2.0), 2.0);

        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

        return RADIO_TERRESTRE * c;
    }
} // namespace

using namespace std;

/// IMPLEMENTAR A PARTIR DE AQUÍ ************************

namespace bblProgII
{
    // Constructor por defecto.
    // Asigna cadenas vacías al nombre y dirección del lugar y
    // 0.0 a la latitud y la longitud del lugar.
    Lugar::Lugar()
    {
        nombre = "";
        direccion = "";
        longitud = 0.0;
        latitud = 0.0;
    }

    // Constructor de copia
    Lugar::Lugar(const Lugar &otro_lugar)
    {
        nombre = otro_lugar.consultar_nombre();
        direccion = otro_lugar.consultar_direccion();
        longitud = otro_lugar.consultar_longitud();
        latitud = otro_lugar.consultar_latitud();
    }

    // Constructor extendido.
    // PARÁMETROS:
    //  - nom (E): nombre del lugar
    //  - dir (E): dirección del lugar
    //  - lat (E): latitud del lugar
    //  - lon (E): longitud del lugar
    Lugar::Lugar(const string &nom,
                 const string &dir,
                 double lat,
                 double lon)
    {
        nombre = nom;
        direccion = dir;
        latitud = lat;
        longitud = lon;
    }

    // Destructor
    Lugar::~Lugar()
    {
        /* IMPLEMENTAR POR EL ALUMNADO (dejo por defecto) */
    }

    //----------- Métodos de asignación

    // Asigna un nuevo valor al nombre del lugar
    // PARÁMETROS:
    //  - nom (E): nuevo nombre del lugar
    void Lugar::asignar_nombre(const string &nom)
    {
        nombre = nom;
    }

    // Asigna un nuevo valor a la dirección del lugar
    // PARÁMETROS:
    //  - dir (E): nueva dirección del lugar
    void Lugar::asignar_direccion(const string &dir)
    {
        direccion = dir;
    }

    // Asigna un nuevo valor a la latitud del lugar
    // PARÁMETROS:
    //  - lat (E): nueva latitud del lugar
    void Lugar::asignar_latitud(double lat)
    {
        latitud = lat;
    }

    // Asigna un nuevo valor a la longitud del lugar
    // PARÁMETROS:
    //  - lon (E): nueva longitud del lugar
    void Lugar::asignar_longitud(double lon)
    {
        longitud = lon;
    }

    //----------- Métodos de consulta

    // Consulta el nombre del lugar
    // DEVUELVE:
    //  - nombre del lugar
    string Lugar::consultar_nombre() const
    {
        string n = nombre;

        return n;
    }

    // Consultar la dirección del lugar
    // DEVUELVE:
    //  - dirección del lugar
    string Lugar::consultar_direccion() const
    {
        string d = direccion;

        return d;
    }

    // Consulta la latitud del lugar
    // DEVUELVE:
    //  - latitud del lugar
    double Lugar::consultar_latitud() const
    {
        double la = latitud;

        return la;
    }

    // Consulta la longitud del lugar
    // DEVUELVE:
    //  - longitud del lugar
    double Lugar::consultar_longitud() const
    {
        double lon = longitud;

        return lon;
    }

    // ---------- Métodos específicos de la clase

    // Calcula y devuelve la distancia euclídea entre dos
    //      lugares: el lugar actual y el lugar que se recibe
    //      como parámetro.
    // La distancia euclídea entre dos puntos (x_1, y_1) y
    //      (x_2, y_2) se calcula como:
    //      sqrt((x_1 - x_2)^2 + (y_1 - y_2)^2).
    // Para los propósitos de esta función, se entiende que las
    //      coordenadas de ambos puntos se expresan en grados
    //      de latitud/longitud.
    // PARÁMETROS:
    //  - otro_lugar (E): otro lugar con el que calcular la
    //          distancia al punto actual.
    // DEVUELVE:
    //  - La distancia euclidea de otro_lugar con el lugar actual.
    double Lugar::distancia_euclidea(const Lugar &otro_lugar) const
    {   

        //latitud = x, longitud =y

        double distancia_euclidear;

        distancia_euclidear=sqrt((pow(latitud-otro_lugar.consultar_latitud(),2)+pow(longitud-otro_lugar.consultar_longitud(),2)));

        return distancia_euclidear;



    }

    // Calcula y devuelve la distancia euclídea en kilómetros entre dos
    //      lugares: el lugar actual y el lugar que se recibe
    //      como parámetro.
    // Para los propósitos de esta función, se entiende que la
    //      distancia euclídea en kilómetros es la mínima distancia entre
    //      ambos lugares medida sobre la superficie de la Tierra,
    //      suponiendo que la Tierra es esférica.
    // PARÁMETROS:
    //  - otro_lugar (E): otro lugar con el que calcular la
    //          distancia al punto actual.
    // DEVUELVE:
    //  - La distancia euclidea en km de otro_lugar con el lugar actual.
    // (Nota: llamada a la función distancia_haversine)
    double Lugar::distancia_euclidea_km(const Lugar &otro_lugar) const
    {   


        return distancia_haversine(consultar_latitud(),
                                   consultar_longitud(),
                                   otro_lugar.consultar_latitud(),
                                   otro_lugar.consultar_longitud());
    }

    // Calcula y devuelve la distancia metropolitana entre dos
    //      lugares: el lugar actual y el lugar que se recibe
    //      como parámetro.
    // La distancia metropolitana entre dos puntos (x_1, y_1) y
    //      (x_2, y_2) se calcula como:
    //      abs(x_1 - x_2) + abs(y_1 - y_2).
    // Para los propósitos de esta función, se entiende que las
    //      coordenadas de ambos puntos se expresan en grados
    //      de latitud/longitud.
    // Se puede considerar esta distancia como la suma de las
    //      distancias euclídeas entre los dos puntos cuando
    //      nos movemos entre los dos puntos siguiendo un camino
    //      en el que sólo nos podemos mover sucesivamente
    //      en alguno de los sentidos Norte-Sur/Sur-Norte y/o Este-Oeste/Oeste-Este,
    //      pero no en linea recta entre ambos puntos.
    // PARÁMETROS:
    //  - otro_lugar (E): otro lugar con el que calcular la
    //          distancia al punto actual.
    // DEVUELVE:
    //  - La distancia metropolitana de otro_lugar con el lugar actual.
    double Lugar::distancia_metro(const Lugar &otro_lugar) const
    {
       double distancia_metro= abs(latitud-otro_lugar.consultar_latitud())+abs(longitud-otro_lugar.consultar_longitud());

       return distancia_metro;
    }

    // Calcula y devuelve la distancia metropolitana en kilómetros entre dos
    //      lugares: el lugar actual y el lugar que se recibe
    //      como parámetro.
    // Se puede considerar esta distancia como la suma de las
    //      distancias euclídeas en kilómetros entre los dos puntos cuando
    //      nos movemos entre los dos puntos siguiendo un camino
    //      en el que sólo nos podemos mover sucesivamente
    //      en alguno de los sentidos Norte-Sur/Sur-Norte y/o Este-Oeste/Oeste-Este,
    //      pero no en linea recta entre ambos puntos.
    // PARÁMETROS:
    //  - otro_lugar (E): otro lugar con el que calcular la
    //          distancia al punto actual.
    // DEVUELVE:
    //  - La distancia metropolitana en km de otro_lugar con el lugar actual.
    // (Nota: debe implementarse mediante llamadas a la función
    //        distancia_haversine)
    double Lugar::distancia_metro_km(const Lugar &otro_lugar) const
    {
        double distancia;

        distancia = distancia_haversine(consultar_latitud(),
                                        consultar_longitud(),
                                        otro_lugar.consultar_latitud(),
                                        consultar_longitud());
        distancia += distancia_haversine(otro_lugar.consultar_latitud(),
                                         consultar_longitud(),
                                         otro_lugar.consultar_latitud(),
                                         otro_lugar.consultar_longitud());
        return distancia;
    }

    // ---------- Operadores sobrecargados (IMPLEMENTADO POR EL PROFESOR)

    // Operador de comparación de lugares
    bool Lugar::operator==(const Lugar &otro_lugar) const
    {
        return (consultar_nombre() == otro_lugar.consultar_nombre() &&
                consultar_direccion() == otro_lugar.consultar_direccion() &&
                consultar_latitud() == otro_lugar.consultar_latitud() &&
                consultar_longitud() == otro_lugar.consultar_longitud());
    }
} // namespace bblProgII