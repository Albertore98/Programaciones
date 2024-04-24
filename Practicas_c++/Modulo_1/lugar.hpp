/******************************************************************************
 * Fichero lugar.hpp para la definición de atributos y métodos de la clase
 * Lugar para la gestión de la información correspondiente con un punto
 * geográfico en el plano.
 *
 * Autor/a:
 * Fecha:
 * ***************************************************************************/

#ifndef __CLASE__LUGAR__
#define __CLASE__LUGAR__

#include <string>

namespace bblProgII
{
    class Lugar
    {
    public:
        // Constructor por defecto.
        // Asigna cadenas vacías al nombre y dirección del lugar y
        // 0.0 a la latitud y la longitud del lugar.
        Lugar();

        // Constructor de copia
        Lugar(const Lugar &otro_lugar);

        // Constructor extendido.
        // PARÁMETROS:
        //  - nom (E): nombre del lugar
        //  - dir (E): dirección del lugar
        //  - lat (E): latitud del lugar
        //  - lon (E): longitud del lugar
        Lugar(const std::string &nom,
              const std::string &dir,
              double lat,
              double lon);

        // Destructor
        ~Lugar();

        //----------- Métodos de asignación

        // Asigna un nuevo valor al nombre del lugar
        // PARÁMETROS:
        //  - nom (E): nuevo nombre del lugar
        void asignar_nombre(const std::string &nom);

        // Asigna un nuevo valor a la dirección del lugar
        // PARÁMETROS:
        //  - dir (E): nueva dirección del lugar
        void asignar_direccion(const std::string &dir);

        // Asigna un nuevo valor a la latitud del lugar
        // PARÁMETROS:
        //  - lat (E): nueva latitud del lugar
        void asignar_latitud(double lat);

        // Asigna un nuevo valor a la longitud del lugar
        // PARÁMETROS:
        //  - lon (E): nueva longitud del lugar
        void asignar_longitud(double lon);

        //----------- Métodos de consulta

        // Consulta el nombre del lugar
        // DEVUELVE:
        //  - nombre del lugar
        std::string consultar_nombre() const;

        // Consultar la dirección del lugar
        // DEVUELVE:
        //  - dirección del lugar
        std::string consultar_direccion() const;

        // Consulta la latitud del lugar
        // DEVUELVE:
        //  - latitud del lugar
        double consultar_latitud() const;

        // Consulta la longitud del lugar
        // DEVUELVE:
        //  - longitud del lugar
        double consultar_longitud() const;

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
        double distancia_euclidea(const Lugar &otro_lugar) const;

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
        double distancia_euclidea_km(const Lugar &otro_lugar) const;

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
        double distancia_metro(const Lugar &otro_lugar) const;

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
        double distancia_metro_km(const Lugar &otro_lugar) const;

        // ---------- Operadores sobrecargados (IMPLEMENTADO POR EL PROFESOR)

        // Operador de comparación de lugares
        // (necesario para test_trazado)
        bool operator==(const Lugar &otro_lugar) const;

        // Operador de asignación
        Lugar &operator=(const Lugar &otro_lugar) = default;

    private:
        

        std::string nombre;
        std::string direccion;
        double latitud;
        double longitud;

        
    }; // class

} // namespace bblProgII

#endif