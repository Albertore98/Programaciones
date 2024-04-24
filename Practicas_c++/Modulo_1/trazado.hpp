/******************************************************************************
 * Fichero trazado.hpp para la definición de atributos y métodos de la clase
 * Trazado, para la gestión de trazado entre una serie de lugares geográficos.
 *
 * Autor/a:
 * Fecha:
 * ***************************************************************************/

#ifndef __CLASE__TRAZADO__
#define __CLASE__TRAZADO__

#include "lugar.hpp"
#include <fstream>
#include <string>
#include <array>

namespace bblProgII
{

    const unsigned MAX_LUGARES = 100;

    // Lista de lugares geográficos
    struct ListaLugares
    {
        std::array<Lugar, MAX_LUGARES> lista_lugares;
        unsigned num_lugares;
    };

    // Orden de recorrido de la lista de lugares
    // geográficos (ej., 4, 1, 3, 5, 2)
    struct OrdenLugares
    {
        std::array<unsigned, MAX_LUGARES> orden_lugares;
        unsigned num_lugares;
    };

    // Resultado de las operaciones
    // (los valores de las constantes simbólicas son
    //  arbitrarios).
    typedef unsigned Resultado;
    const Resultado OK = 0, // Okay
        VAL_ERROR = 1,      // Error en los valores de los parámetros
        FIC_ERROR = 2,      // Error en la apertura de fichero
        NO_EXISTE = 3,      // El dato a consultar no existe
        YA_EXISTE = 4,      // El dato a insertar ya existe
        LISTA_LLENA = 5;    // El dato no puede insertarse: lista llena

    // Escribe por pantalla la cadena de caracteres
    // correspondiente al resultado de la operación.
    // Parámetros:
    // 		- res (E): código de error
    void escribir_resultado(const Resultado &res);

    // Tipo de distancia para el cálculo de longitud
    // (los valores de las constantes simbólicas son
    //  arbitrarios).
    typedef unsigned Distancia;
    const Distancia EUCLIDEA = 0, // Euclídea
        EUCLIDEA_KM = 1,          // Euclídea en kilómetros
        METROPOL = 2,             // Metropolitana
        METROPOL_KM = 3;          // Metropolitana en kilómetros

    class Trazado
    {
    public:
        // --------- CONSTRUCTORES

        // Constructor por defecto.
        // Inicializa la clase con un trazado vacío (sin lugares geográficos)
        Trazado();

        // Constructor de copia de la clase
        // PARÁMETROS:
        //  - otro_trazado (E): otro trazado a copiar al trazado actual.
        Trazado(const Trazado &otro_trazado);

        // Constructor extendido:
        // PARÁMETROS:
        //  - lugares_ini (E): lista de lugares geográficos
        //  - orden_ini (E): orden de recorrido del trazado por los lugares
        // PRECONDICIÓN:
        //  - lugares_ini.num_lugares == orden_ini.num_lugares
        //  - Para todo i>=0 && i<orden_ini.num_lugares,
        //    orden_ini.orden_lugares[i] >= 1 &&
        //    orden_ini.orden_lugares[i] <= orden_ini.num_lugares
        //  - No hay valores repetidos en orden_ini
        //  - No hay lugares repetidos en lugares_ini, es decir,
        //      lugares con latitud y longitud similares.
        //
        // Si se cumplen las precondiciones, el trazado está inicilizado
        //     con los 'lugares_ini' y el 'orden_ini' que se pasan como parámetro.
        Trazado(const ListaLugares &lugares_ini,
                const OrdenLugares &orden_ini);

        // Destructor
        ~Trazado();

        // MÉTODOS DE CONSULTA **********

        // Devuelve el lugar geográfico cuyo posición en el orden del
        //    trazado se indica.
        // PARÁMETROS:
        //  - posicion (E): posición en el orden del trazado
        //  - lugar (S): el lugar geográfico consultado
        // PRECONDICIÓN: posicion >= 1 && posicion<=número de lugares
        //
        // Si se cumple la precondición, devuelve el lugar de la posición
        //    del trazado que se consulta.
        void consultar_lugar(unsigned posicion, Lugar &lugar) const;

        // Devuelve la posición, en el orden de recorrido del trazado,
        //  donde está un lugar cuya localización se pasa como parámetro.
        // PARÁMETROS:
        //  - latitud (E): latitud del lugar geográfico cuya posición quiere consultarse
        //  - longitud (E): longitud del lugar geográfico cuya posición quiere consultarse
        //  - pos (S): posición que ocupa el lugar en el orden de recorrido
        //  - res (S): resultado de la operación
        //
        // Si el lugar con esa localización existe en el trazado,
        //    se devuelve su posición en el
        //    orden de recorrido y OK a través de 'res'. Si no, se
        //    devuelve NO_EXISTE a través de 'res'.
        void consultar_pos_lugar(double latitud,
                                 double longitud,
                                 unsigned &pos,
                                 Resultado &res) const;

        // Devuelve todo el trazado: lugares y orden del recorrido por los mismos.
        // PARÁMETROS:
        //  - lug (S): la lista de lugares geográficos.
        //  - ord (S): la lista con el orden de recorrido de los lugares.
        void consultar_trazado(ListaLugares &lug,
                               OrdenLugares &ord) const;

        // Devuelve la lista de los lugars del trazado.
        // PARÁMETROS:
        //  - lug (S): lisdta de lugares del trazado.
        void consultar_lugares(ListaLugares &lugs) const;

        // Devuelve la lista con el orden de recorrido de los
        //    lugares del trazado.
        // PARÁMETROS:
        //  - ord (S): orden de los lugares en el recorrido del trazado.
        void consultar_orden(OrdenLugares &ord) const;

        // Devuelve el número de lugares del trazado
        unsigned consultar_num_lugares() const;

        // Devuelve la distancia entre los dos lugares del trazado
        //    que están en posiciones concretas en el orden del trazado…
        // PARÁMETROS:
        //  - ordinal1 (E): orden, en el trazado, que ocupa el lugar 1
        //  - ordinal2 (E): orden, en el trazado, que ocupa el lugar 2
        //  - resultado (S): indica si los ordinales son correctos
        //  - dis (E): tipo de distancia a calcular
        // PRECONDICIÓN: los ordinales son correctos, es decir >= 1 y
        //    <= número de lugares, y ordinal1 != ordinal2
        //
        // Si se cumple la precondición, devuelve la distancia
        //    entre los puntos cuyo ordinal se indica.
        double consultar_distancia(unsigned ordinal1, unsigned ordinal2, Distancia dis) const;

        // Devuelve la longitud total del trazado, es decir, la suma de las
        //    distancias entre los lugares por los que pasa el
        //    trazado, EN EL ORDEN de recorrido actual del trazado (se considera
        //    que el trazado es cerrado, es decir, que el último punto del
        //    trazado conecta con el primero).
        // PARÁMETROS:
        //  - dis (E): tipo de distancia a calcular
        double longitud_trazado(Distancia dis) const;

        // Escribe el trazado por pantalla, en el orden de recorrido del
        //    trazado.
        // Debe salir una línea por cada lugar del trazado, con el siguiente
        //    formato:
        //      [orden] "nombre", "dirección", longitud, latitud
        // Ejemplo:
        // [1] "E.T.S.I.T","Bulevar Louis Pasteur, 35, 29010 Malaga",36.716027,-4.478137
        // [2] "SCAI","Bulevar Louis Pasteur, 33, 29010 Malaga",36.716122,-4.473567
        // ...
        // [10] "Aulario","C/ Jimenez Fraud, 10, 29071 Malaga",36.718386,-4.475648
        void escribir_trazado() const;

        // MÉTODOS DE MODIFICACIÓN *********

        // Inserta un nuevo lugar en el trazado, al final del recorrido actual,
        //    es decir, en la posición final del orden de recorrido del
        //    trazado.
        // PARÁMETROS:
        //  - lugar (E): el lugar a insertar
        //  - resultado (S): resultado de la operación
        //
        // Si el lugar a insertar no existe en el recorrido actual y
        //    el nuevo lugar cabe en la lista, se inserta
        //    al final, en último lugar del orden de recorrido, y se devuelve
        //    OK a través de 'resultado'. Si no, si el lugar ya existía,
        //    se devuelve YA_EXISTE a través de 'resultado'. Si no, si no
        //    caben más lugares en la lista, se devuelve LISTA_LLENA a través
        //    de 'resultado'.
        void insertar_lugar(const Lugar &lugar, Resultado &resultado);

        // Elimina el lugar cuya posición, en el orden de recorrido del
        //    trazado, se pasa como parámetro.
        // PARÁMETROS:
        //  - pos (E): posición, en el orden de recorrio, que se
        //      quiere eliminar.
        // PRECONDICIÓN: pos >= 1 && pos <= consultar_num_lugares()
        //
        // Si se cumple la precondición, se elimina el lugar del recorrido
        //    y se reordenan todos los lugares que quedan, de manera que
        //    aquellos que tengan una posición mayor que 'pos', decrementen
        //    su posición en una unidad.
        void eliminar_lugar(unsigned pos);

        // Modifica el trazado con nuevos lugares y orden de recorrido
        //    de los mismos.
        // PARÁMETROS:
        //  - nuevos_lugares (E): lista de lugares geográficos
        //  - nuevo_orden (E): orden de recorrido del trazado por los lugares
        //  - resultado (S): resultado de la operación
        // Si se cumple que:
        //    - nuevos_lugares.num_lugares == nuevo_orden.num_lugares
        //    - Para todo i>=0 && i<nuevo_orden.num_lugares,
        //      nuevo_orden.orden_lugares[i] >= 1 &&
        //      nuevo_orden.orden_lugares[i] <= nuevo_orden.num_lugares,
        //    - No hay valores repetidos en nuevo_orden,
        //    - No hay lugares repetidos en nuevos_lugares, es decir, lugares
        //      con latitud y longitud similares,
        //  el trazado está inicilizado con los 'nuevos_lugares' y el
        //  'nuevo_orden' que se pasan como parámetro,
        //  y se devuelve OK a través de 'resultado'. Si no, se devuelve VAL_ERROR
        //  a través de 'resultado'.
        void modificar_trazado(const ListaLugares &nuevos_lugares,
                               const OrdenLugares &nuevo_orden,
                               Resultado &resultado);

        // Modifica los lugares del trazado.
        // PARÁMETROS:
        //  - nuevos_lugares (E): nuevos lugares del trazado
        //  - resultado (S): resultado de la operación
        // Si se cumple que:
        //    - nuevos_lugares.num_lugares coincide con el tamaño de
        //      la lista de lugares actual,
        //    - nuevos_lugares no contiene lugares repetidos, es deicir,
        //      lugares con latitud y longitud similares,
        //  se modifican los lugares
        //  del trazado actual y se devuelve OK a través de 'resultado'; si no,
        //  se devuelve VAL_ERROR a través de 'resultado'.
        void modificar_lugares(const ListaLugares &nuevos_lugares, Resultado &resultado);

        // Modifica el orden de recorrido de los lugares del trazado.
        // PARÁMETROS:
        //  - nuevo_orden (E): nuevo orden de recorrido de los lugares
        //  - resultado (S): resultado de la operación
        // Si se cumple que:
        //    - nuevo_orden.num_lugares coincide con el tamaño de
        //      la lista de lugares actual,
        //    - Para todo i>=0 && i<nuevo_orden.num_lugares,
        //      nuevo_orden.orden_lugares[i] >= 1 &&
        //      nuevo_orden.orden_lugares[i] <= nuevo_orden.num_lugares,
        //    - No hay valores repetidos en nuevo_orden,
        //  se modifica el orden de recorrido
        //  del trazado actual y se devuelve OK a través de 'resultado'; si no,
        //  se devuelve VAL_ERROR a través de 'resultado'.
        void modificar_orden(const OrdenLugares &nuevo_orden, Resultado &resultado);

        // OPERACIONES CON FICHEROS

        // Lee una lista de lugares desde fichero y los inserta en el
        //  trazado actual, eliminando previamente todos los lugares
        //  que hubiera previamente en el trazado.
        //
        // PARÁMETROS:
        //   - nombre_fic (E): nombre del fichero de entrada
        //   - res (S): resultado de la operación
        // Si es posible abrir el fichero, se leen los lugares y se insertan
        //  en el trazado actual, devolviéndose OK a través de 'res'.
        //  Si no, se devuelve FIC_ERROR a través de 'res'.
        //
        // El formato del fichero incluye una cabecera con los nombres de los
        //  cuatro campos de datos de cada lugar. Los datos de tipo cadena
        //  de caracteres contienend comillas dobles (véase el ejemplo).
        //  Los datos están separados por comas (comma separated values).
        //
        // Ejemplo de formato:
        //
        // nombre,direccion,latitud,longitud
        // "Lugar 1","Calle, numero, codigo, ciudad",36.716027,-4.478137
        // "Lugar 2","Calle, numero, codigo, ciudad",36.716122,-4.473567
        //  ...
        // "Lugar N","Calle, numero, codigo, ciudad",36.718386,-4.475648
        void leer_trazado(const std::string &nombre_fic, Resultado &res);

        // Escritura del trazado en fichero
        // PARÁMETROS:
        //   - nombre_fic (E): nombre del fichero de entrada
        //   - res (S): resultado de la operación
        //
        // Escribe el trazado actual (todos sus lugares) en fichero,
        //    en el orden de recorrido del trazado,
        //    en el mismo formato de la lectura de fichero (véase el
        //    método leer_trazado). Si ha podido abrirse el fichero
        //    para escritura, se escribe el trazado en él y se
        //    devuelve OK. Si no, se devuelve FIC_ERROR
        //
        // NOTA IMPORTANTE:
        //  Los números reales (latitud y longitud) deben escribirse con
        //  una presición suficiente para que no se redondeen los valores
        //  que tenemos en memoria. Para ello, debe incluirse la biblioteca
        //  iomanip de C++ e invocar al método setprecision con una precisión
        //  de, por ejemplo, 10 dígitos. Ejemplo: f << setprecision(10);
        //  (siendo f un objeto ofstream).
        void escribir_trazado(const std::string &nombre_fic, Resultado &res) const;

        // OPERADORES SOBRECARGADOS (IMPLEMENTADO POR EL PROFESOR) **********

        // ¡¡¡EL PROFESOR LO DA IMPLEMENTADO!!!!!!
        // Operador de comparación de igualdad.
        // (necesario para las pruebas unitarias).
        bool operator==(const Trazado &otro_trazado) const;

        // Operadopr de asignación
        Trazado &operator=(const Trazado &otro_trazado) = default;

    private:
        /* DEBEN DEFINIRSE AQUÍ LOS ATRIBUTOS DE LA CLASE*/

        ListaLugares lugares;
        OrdenLugares orden;
        // MÉTODOS PRIVADOS ACONSEJADOS (NO OBLIGATORIOS) ***********

        // Indica si hay lugares repetidos o no en un array de lugares.
        //    Dos lugares se consideran iguales si su longitud y latitud
        //    coinciden.
        // PARÁMETROS:
        //  - lug (E): lista de lugares
        // Devuelve true si hay lugares repetidos, false en
        //  caso contrario.
        bool hay_lugares_repetidos(const ListaLugares &lug) const;

        // Indica si hay ordinales repetidos o no en un array de ordinales.
        // PARÁMETROS:
        //  - ord (E): lista de ordinales
        // Devuelve true si hay ordinales repetidos, false en
        //  caso contrario.
        bool hay_ordinales_repetidos(const OrdenLugares &ord) const;

        // Indica si la lista de ordinales está en rango.
        // PARÁMETROS:
        //  - ord (E): lista de ordinales
        // Si todos los valores de la lista de ordinales están en rango,
        //    es decir, son mayores o iguales que 1 y menores o iguales
        //    que el tamaño de la lista de ordinales, devuelve verdadero.
        //    En otro caso, devuelve falso.
        bool ordinales_en_rango(const OrdenLugares &ord) const;

        // Indica si el orden es correcto.
        // PARÁMETROS:
        //  - ord (E): array con un orden de recorrido del trazado
        // Devuelve verdadero si:
        // - Para todo i>=0 && i<ord.num_lugares,
        //   ord.orden_lugares[i] >= 1 &&
        //   ord.orden_lugares[i] <= ord.num_lugares
        // - No hay valores repetidos en orden
        // Devuelve falso en caso contrario.
        bool ordenacion_correcta(const OrdenLugares &ord) const;

        // Busca un lugar cuya posicion en el orden de recorrido
        //  se pasa como parámetro.
        // PARÁMETROS:
        //  - pos (E): posición en el orden de recorrido
        // PRECONDICIÓN: pos >= 1 && pos <= lugares.num_lugares
        //
        // Si se cumple la precondición, devuelve la posición del array
        //    donde se encuentra el lugar cuyo posición en el orden
        //    de recorrido es 'pos'. Por ejemplo, si hay 5 lugares y el
        //    orden de recorrido del trazado es 4, 3, 1, 5, 2, y pos = 5,
        //    debe devolverse 3.
        unsigned buscar_logar_pos(unsigned pos) const;

        // Busca un lugar en el trazado actual.
        // PARÁMETROS:
        //  - latitud (E): latitud del lugar a buscar
        //  - longitud (E): longitud del lugar a buscar
        //
        // Si lo encuentra, devuelve la posición del lugar en la lista
        //    de lugares (es decir, en el array de lugares). Si no,
        //    devuelve lugares.num_lugares.
        unsigned buscar_lugar_lat_lon(double latitud, double longitud) const;

        
    }; // Fin de la clase Trazado
} // namespace bblProgII
#endif
