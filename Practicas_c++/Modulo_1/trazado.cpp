/******************************************************************************
 * Fichero trazado.cpp para la implementación de los métodos de la clase
 * Trazado, para la gestión de trazado entre una serie de lugares geográficos.
 *
 * Autor/a:
 * Fecha:
 * ***************************************************************************/

#include "lugar.hpp"
#include "trazado.hpp"
#include <fstream>
#include <string>
#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

namespace bblProgII
{

    // --------- CONSTRUCTORES

    // Constructor por defecto.
    // Inicializa la clase con un trazado vacío (sin lugares geográficos)
    Trazado::Trazado()
    {

        lugares.num_lugares = 0;
    }

    // Constructor de copia de la clase
    // PARÁMETROS:
    //  - otro_trazado (E): otro trazado a copiar al trazado actual.
    Trazado::Trazado(const Trazado &otro_trazado)
    {
        for (int i = 0; i<= otro_trazado.consultar_num_lugares(); i++)
        {

            lugares.num_lugares = otro_trazado.lugares.num_lugares;           // asigno el mismo numero de lugares en la lista de lugares
            lugares.lista_lugares[i] = otro_trazado.lugares.lista_lugares[i]; // copio el lugar de la lista que estoy recorriendo

            orden.num_lugares = otro_trazado.orden.num_lugares; // mismo procedimiento que arriba
            orden.orden_lugares[i] = otro_trazado.orden.orden_lugares[i];
        }
    }

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
    Trazado::Trazado(const ListaLugares &lugares_ini,
                     const OrdenLugares &orden_ini)

                     
    {
        assert(lugares_ini.num_lugares==orden_ini.num_lugares);
        assert(!hay_lugares_repetidos(lugares_ini));
        assert(!hay_ordinales_repetidos(orden_ini));
        for (int i=0;i<=lugares_ini.num_lugares;i++){
            lugares.lista_lugares[i]=lugares_ini.lista_lugares[i];
            lugares.num_lugares=lugares_ini.num_lugares;

            orden.orden_lugares[i]=orden_ini.orden_lugares[i];
            orden.num_lugares=orden_ini.num_lugares;
        }
    }

    // Destructor
    Trazado::~Trazado()
    {
    }

    // MÉTODOS DE CONSULTA **********

    // Devuelve el lugar geográfico cuyo posición en el orden de
    //    recorrido del trazado se indica.
    // PARÁMETROS:
    //  - posicion (E): posición en el orden de recorrido del trazado
    //  - lugar (S): el lugar geográfico consultado
    // PRECONDICIÓN: posicion >= 1 && posicion<=número de lugares
    //
    // Si se cumple la precondición, devuelve el lugar de la posición
    //    del trazado que se consulta.
    void Trazado::consultar_lugar(unsigned posicion, Lugar &lugar) const
    {
        if (posicion >= 1 && posicion <= lugares.num_lugares)
        {

            for (int i = 0; i <= orden.num_lugares; i++)
            {

                if (orden.orden_lugares[i] == posicion)
                {
                    lugar = lugares.lista_lugares[i];
                }
            }
        }
    }

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
    void Trazado::consultar_pos_lugar(double latitud,
                                      double longitud,
                                      unsigned &pos,
                                      Resultado &res) const
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        res = NO_EXISTE;

        for (int i = 0; i <= lugares.num_lugares; i++)
        {

            if (latitud == lugares.lista_lugares[i].consultar_latitud() && longitud == lugares.lista_lugares[i].consultar_longitud())
            {

                pos = orden.orden_lugares[i];

                res = OK;
            }
        }
    }

    // Devuelve todo el trazado: lugares y orden del recorrido por los mismos.
    // PARÁMETROS:
    //  - lug (S): la lista de lugares geográficos.
    //  - ord (S): la lista con el orden de recorrido de los lugares.
    void Trazado::consultar_trazado(ListaLugares &lug,
                                    OrdenLugares &ord) const
    {

        consultar_lugares(lug);
        consultar_orden(ord);
    }

    // Devuelve la lista de los lugares del trazado.
    // PARÁMETROS:
    //  - lug (S): lisdta de lugares del trazado.
    void Trazado::consultar_lugares(ListaLugares &lug) const
    {
        for (int i = 0; i <= lugares.num_lugares; i++)
        {

            lug.lista_lugares[i] = lugares.lista_lugares[i];
        }

        lug.num_lugares = lugares.num_lugares;
    }

    // Devuelve la lista con el orden de recorrido de los
    //    lugares del trazado.
    // PARÁMETROS:
    //  - ord (S): orden de los lugares en el recorrido del trazado.
    void Trazado::consultar_orden(OrdenLugares &ord) const
    {
        for (int i = 0; i < lugares.num_lugares; i++)
        {

            ord.orden_lugares[i] = orden.orden_lugares[i];
        }
        ord.num_lugares = orden.num_lugares;
    }

    // Devuelve el número de lugares del trazado
    unsigned Trazado::consultar_num_lugares() const
    {
        return lugares.num_lugares;
    }

    // Devuelve la distancia entre los dos lugares del trazado
    //    que están en posiciones concretas en el orden del trazado…
    // PARÁMETROS:
    //  - ordinal1 (E): orden, en el trazado, que ocupa el lugar 1
    //  - ordinal2 (E): orden, en el trazado, que ocupa el lugar 2
    //  - resultado (S): indica si los ordinales son correctos
    //  - dis (E): tipo de distancia a calcular
    // PRECONDICIÓN: los ordinales son correctos, es decir >= 1 y
    //    <= número de lugares, y ordinal1 != ordinal2.
    //
    // Si se cumple la precondición, devuelve la distancia
    //    entre los puntos cuyo ordinal se indica.
    double Trazado::consultar_distancia(unsigned ordinal1, unsigned ordinal2, Distancia dis) const
    {
        double distancia;
        if ((ordinal1 >= 1 && ordinal2 >= 1) && (ordinal1 < lugares.num_lugares && ordinal2 < lugares.num_lugares) && (ordinal1 != ordinal2))
        {

            switch (dis)
            {
            case 0:
                distancia = lugares.lista_lugares[buscar_logar_pos(ordinal1)].distancia_euclidea(lugares.lista_lugares[buscar_logar_pos(ordinal2)]);
                break;
            case 1:
                distancia = lugares.lista_lugares[buscar_logar_pos(ordinal1)].distancia_euclidea_km(lugares.lista_lugares[buscar_logar_pos(ordinal2)]);
                break;
            case 2:
                distancia = lugares.lista_lugares[buscar_logar_pos(ordinal1)].distancia_metro(lugares.lista_lugares[buscar_logar_pos(ordinal2)]);
                break;
            case 3:
                distancia = lugares.lista_lugares[buscar_logar_pos(ordinal1)].distancia_metro_km(lugares.lista_lugares[buscar_logar_pos(ordinal2)]);
                break;
            }

            return distancia;
        }
    }

    // Devuelve la longitud total del trazado, es decir, la suma de las
    //    distancias entre los lugares por los que pasa el
    //    trazado en su recorrido, EN EL ORDEN de recorrido actual del
    //    trazado (se considera que el trazado es cerrado, es decir,
    //    que el último lugar del trazado conecta con el primero).
    // PARÁMETROS:
    //  - dis (E): tipo de distancia a calcular
    double Trazado::longitud_trazado(Distancia dis) const
    {

        double suma = 0;

        for (int i = 0; i <= lugares.num_lugares - 1; i++)
        {

            suma += consultar_distancia(i, i + 1, dis);
        }

        suma += consultar_distancia(0, lugares.num_lugares, dis);

        return suma;
    }
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
    void Trazado::escribir_trazado() const
    {

        for (int i = 0; i <= lugares.num_lugares; i++)
        {

            cout << i << "''" << lugares.lista_lugares[buscar_logar_pos(i)].consultar_nombre() << "''"
                 << ","
                 << "''" << lugares.lista_lugares[buscar_logar_pos(i)].consultar_direccion() << "''"
                 << "," << lugares.lista_lugares[buscar_logar_pos(i)].consultar_longitud() << "," << lugares.lista_lugares[buscar_logar_pos(i)].consultar_latitud() << endl;
        }
    }

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
    void Trazado::insertar_lugar(const Lugar &lugar, Resultado &resultado)
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        resultado = YA_EXISTE;
        if (buscar_lugar_lat_lon(lugar.consultar_latitud(), lugar.consultar_longitud()) == lugares.num_lugares)
        {

            if (lugares.num_lugares == MAX_LUGARES)
            {

                resultado = LISTA_LLENA;
            }
            else
            {
                lugares.num_lugares++;
                lugares.lista_lugares[lugares.num_lugares] = lugar;

                resultado = OK;
            }
        }
    }

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
    void Trazado::eliminar_lugar(unsigned pos)
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        if (pos >= 1 && pos <= consultar_num_lugares())
        {

            for (int i = pos; i <=lugares.num_lugares - 1; i++)
            {

                lugares.lista_lugares[buscar_logar_pos(i)] = lugares.lista_lugares[buscar_logar_pos(i + 1)];
            }
        }
    }

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
    void Trazado::modificar_trazado(const ListaLugares &nuevos_lugares,
                                    const OrdenLugares &nuevo_orden,
                                    Resultado &resultado)
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        resultado = VAL_ERROR;
        if (nuevos_lugares.num_lugares == nuevo_orden.num_lugares)
        {

            for (int i = 0; i < nuevos_lugares.num_lugares; i++)
            {

                if ((nuevo_orden.orden_lugares[i] >= 1 && nuevo_orden.orden_lugares[i] <= nuevo_orden.num_lugares) && !hay_lugares_repetidos(nuevos_lugares) && !hay_ordinales_repetidos(nuevo_orden))
                {

                    lugares.lista_lugares[i] = nuevos_lugares.lista_lugares[i];
                    orden.orden_lugares[i] = nuevo_orden.orden_lugares[i];
                    lugares.num_lugares = nuevos_lugares.num_lugares;
                    orden.num_lugares = nuevo_orden.num_lugares;

                    resultado = OK;
                }
            }
        }
    }

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
    void Trazado::modificar_lugares(const ListaLugares &nuevos_lugares, Resultado &resultado)
    {

        resultado = VAL_ERROR;
        if (nuevos_lugares.num_lugares == lugares.num_lugares && !hay_lugares_repetidos(nuevos_lugares))
        {

            for (int i = 0; i < lugares.num_lugares; i++)
            {
                lugares.lista_lugares[i] = nuevos_lugares.lista_lugares[i];
            }

            resultado = OK;
        }
    }

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
    void Trazado::modificar_orden(const OrdenLugares &nuevo_orden, Resultado &resultado)
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        resultado = VAL_ERROR;
        if (nuevo_orden.num_lugares == orden.num_lugares && !hay_ordinales_repetidos(nuevo_orden))
        {

            for (int i = 0; i <= orden.num_lugares; i++)
            {
                orden.orden_lugares[i] = nuevo_orden.orden_lugares[i];
            }

            resultado = OK;
        }
    }

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
    void Trazado::leer_trazado(const std::string &nombre_fic, Resultado &res)
    {
        /* IMPLEMENTAR POR EL ALUMNADO */

        res = FIC_ERROR;
        ifstream entrada;
        entrada.open(nombre_fic);
        string aux1, aux2, linea, lat, longi;

        entrada.open(nombre_fic);

        if (!entrada.fail())
        {

            res = OK;
            lugares.num_lugares = 0;
            orden.num_lugares = 0;

            getline(entrada, linea);
            entrada.ignore();

            while (!entrada.eof())
            {
                getline(entrada, aux1, '"');
                lugares.lista_lugares[lugares.num_lugares].asignar_nombre(aux1);
                entrada.ignore(2);
                getline(entrada, aux2, '"');
                lugares.lista_lugares[lugares.num_lugares].asignar_direccion(aux2);
                entrada.ignore(1);
                getline(entrada, lat, ',');
                lugares.lista_lugares[lugares.num_lugares].asignar_latitud(stod(lat));
                entrada.ignore(1);
                getline(entrada, longi, ',');
                lugares.lista_lugares[lugares.num_lugares].asignar_longitud(stod(longi));
                entrada.ignore();

                lugares.num_lugares++;
                orden.num_lugares++;
            }
        }

        entrada.close();
    }

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
    void Trazado::escribir_trazado(const std::string &nombre_fic, Resultado &res) const
    {
        ofstream salida;

        int contador=0;;
        res=FIC_ERROR;

        salida.open(nombre_fic);

        if(!salida.fail()){
            res=OK;

            salida<<setprecision(15);
            salida<<"nombre,direccion,latitud,longitud"<<endl;

            while(contador<=orden.num_lugares){

                salida<<R"(double quotes)"<<lugares.lista_lugares[orden.orden_lugares[contador]].consultar_nombre()<<R"(double quotes)"<<',';
                salida<<R"(double quotes)"<<lugares.lista_lugares[orden.orden_lugares[contador]].consultar_direccion()<<R"(double quotes)"<<',';
                salida<<lugares.lista_lugares[orden.orden_lugares[contador]].consultar_latitud()<<',';
                salida<<lugares.lista_lugares[orden.orden_lugares[contador]].consultar_longitud()<<',';
                contador++;
            }


        }
    }

    // MÉTODOS PRIVADOS ACONSEJADOS *****************************

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
    unsigned Trazado::buscar_logar_pos(unsigned pos) const
    {
        unsigned posd;
        if (pos >= 1 && pos <= lugares.num_lugares)
        {
            for (int i = 0; i < orden.num_lugares; i++)
            {
                if (orden.orden_lugares[i] == pos)
                {
                    posd = pos;
                }
            }
        }

        return posd;
    }

    // Busca un lugar en el trazado actual.
    // PARÁMETROS:
    //  - latitud (E): latitud del lugar a buscar
    //  - longitud (E): longitud del lugar a buscar
    //
    // Si lo encuentra, devuelve la posición del lugar en la lista
    //    de lugares (es decir, en el array de lugares). Si no,
    //    devuelve lugares.num_lugares.
    unsigned Trazado::buscar_lugar_lat_lon(double latitud, double longitud) const
    {

        unsigned result = lugares.num_lugares;

        for (int i = 0; i < lugares.num_lugares; i++)
        {

            if (latitud == lugares.lista_lugares[i].consultar_latitud() && longitud == lugares.lista_lugares[i].consultar_longitud())
            {

                result = i;
            }
        }

        return result;
    }

    // A PARTIR DE AQUÍ, ESTÁ TODO IMPLEMENTADO POR EL PROFESORADO **********

    // Operador de comparación de igualdad.
    // (necesario para las pruebas unitarias).
    bool Trazado::operator==(const Trazado &otro_trazado) const
    {
        ListaLugares l1, l2;
        OrdenLugares o1, o2;
        consultar_trazado(l1, o1);
        otro_trazado.consultar_trazado(l2, o2);
        bool iguales = l1.num_lugares == l2.num_lugares && o1.num_lugares == o2.num_lugares;
        unsigned k = 0;
        while (iguales && k < l1.num_lugares)
        {
            iguales = l1.lista_lugares[k] == l2.lista_lugares[k];
            ++k;
        }
        k = 0;
        while (iguales && k < o1.num_lugares)
        {
            iguales = o1.orden_lugares[k] == o2.orden_lugares[k];
            ++k;
        }
        return iguales;
    }

    // Indica si hay lugares repetidos o no en un array de lugares.
    //    Dos lugares se consideran iguales si su longitud y latitud
    //    coinciden.
    // PARÁMETROS:
    //  - lug (E): lista de lugares
    // Devuelve true si hay lugares repetidos, false en
    //  caso contrario.
    bool Trazado::hay_lugares_repetidos(const ListaLugares &lug) const
    {
        bool repetidos = false;

        if (lug.num_lugares > 1)
        {
            unsigned i = 0;

            while (i < lug.num_lugares - 1 && !repetidos)
            {
                unsigned j = i + 1;
                while (j < lug.num_lugares && !repetidos)
                {
                    repetidos = (lug.lista_lugares[i].consultar_latitud() == lug.lista_lugares[j].consultar_latitud() &&
                                 lug.lista_lugares[i].consultar_longitud() == lug.lista_lugares[j].consultar_longitud());
                    ++j;
                }
                ++i;
            }
        }

        return repetidos;
    }

    // Indica si hay ordinales repetidos o no en un array de ordinales.
    // PARÁMETROS:
    //  - ord (E): lista de ordinales
    // Devuelve true si hay ordinales repetidos, false en
    //  caso contrario.
    bool Trazado::hay_ordinales_repetidos(const OrdenLugares &ord) const
    {
        bool repetidos = false;

        if (ord.num_lugares > 1)
        {
            unsigned i = 0;

            while (i < ord.num_lugares - 1 && !repetidos)
            {
                unsigned j = i + 1;
                while (j < ord.num_lugares && !repetidos)
                {
                    repetidos = (ord.orden_lugares[i] == ord.orden_lugares[j]);
                    ++j;
                }
                ++i;
            }
        }

        return repetidos;
    }

    // Indica si la lista de ordinales está en rango.
    // PARÁMETROS:
    //  - ord (E): lista de ordinales
    // Si todos los valores de la lista de ordinales están en rango,
    //    es decir, son mayores o iguales que 1 y menores o iguales
    //    que el tamaño de la lista de ordinales, devuelve verdadero.
    //    En otro caso, devuelve falso.

    bool Trazado::ordinales_en_rango(const OrdenLugares &ord) const
    {
        bool en_rango = true;
        unsigned i = 0;

        while (i < ord.num_lugares && en_rango)
        {
            en_rango = (ord.orden_lugares[i] >= 1 &&
                        ord.orden_lugares[i] <= ord.num_lugares);
            ++i;
        }

        return en_rango;
    }

    // Indica si el orden es correcto.
    // PARÁMETROS:
    //  - ord (E): array con un orden de recorrido del trazado
    // Devuelve verdadero si:
    // - Para todo i>=0 && i<ord.num_lugares,
    //   ord.orden_lugares[i] >= 1 &&
    //   ord.orden_lugares[i[ <= ord.num_lugares
    // - No hay valores repetidos en orden
    // Devuelve falso en caso contrario.
    bool Trazado::ordenacion_correcta(const OrdenLugares &ord) const
    {
        return (!hay_ordinales_repetidos(ord) && ordinales_en_rango(ord));
    }

    // Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Parámetros:
    // 		- res (E): código de error
    void escribir_resultado(const Resultado &res)
    {
        switch (res)
        {
        case OK:
            cout << " --- OK." << endl;
            break;
        case VAL_ERROR:
            cout << " --- ERROR DE VALOR." << endl;
            break;
        case FIC_ERROR:
            cout << " --- ERROR DE FICHERO. " << endl;
            break;
        case NO_EXISTE:
            cout << " --- NO EXISTE. " << endl;
            break;
        case YA_EXISTE:
            cout << " --- YA EXISTE. " << endl;
            break;
        case LISTA_LLENA:
            cout << " --- LISTA LLENA." << endl;
            break;
        default:
            cout << " --- CÓDIGO DE ERROR DESCONOCIDO." << endl;
        }
    }
} // namespace bblProgII