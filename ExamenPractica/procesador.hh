/**
 * @file procesador.hh
 * @brief Especificación de la clase Procesador
*/

#ifndef _PROCESADOR_HH
#define _PROCESADOR_HH
using namespace std;
#include "proceso.hh"
#include <set>
#include <map>
/** @class Procesador
 * @brief Representa un procesador con un identificador, una memoria indexada a partir del 0 que está compuesta de varios procesos.
*/

class Procesador{

private: 
string id;
int capacidad;
int mem_libre;
map<int,int> pos; //indica la posición de memória de cada proceso con id como el primer parámetro
map<int,Proceso> mem; //primer parámetro: posición de Proceso
map<int, set<int>> space;  //primer parámetro:tamaño del hueco, segundo: set con las posiciones con ese tamaño


public:
     
     //CREADORAS

     /**
      * @brief Creadora de un procesador
      * \pre <em>mem<em> es la memória del procesador y <em>id<em> es su identificador
      * \post Crea un procesador con los parámetros indicados en la entrada
     */
     Procesador(int mem, string id);

     //CONSULTORAS
     
     /** @brief Consultora de la memória de un procesador
      * \pre <em>true<em>
      * \post Retorna un entero con la memória total del P.I.
     */
     int consultar_memoria_total()const;
          
     /** @brief Consultora hueco más ajustado
      * \pre <em>p<em> es un proceso con valores válidos
      * \post Retorna un entero con el tamaño del hueco que quedaría más ajustado al insertar <em>p<em>
     */
     int tamaño_hueco_ajustado(const Proceso& p) const;

     

     /** @brief Consultadora del identificador de un proceso
      * \pre <em>true<em>
      * \post Retorna un string con el identificador del P.I.
     */
     string consultar_identificador() const;


     /** @brief Consultora de memória libre
      * \pre El P.I. está inicializado
      * \post Retorna la memoria libre que le queda al P.I..
     */
     int consultar_memoria_libe() const;

     /** @brief Consultora de existencia del proceso
      * \pre <em>p<em> es un proceso inicializado yl el P.I. está inicializado.
      * \post comprueba si hay hay algún proceso del P.I. con el identificador del proceso.
     */
     bool tiene_proceso(const int& id) const;

     /** @brief Consultora de tenencia de espacio
      * \pre <em>p<em> es un proceso inicializado y el P.I. está inicializado
      * \post Comprueba que hay espacio suficiente en el procesador para acomodar al proceso p.
     */
     bool tiene_espacio(const Proceso& p) const;
     

     /** @brief Consultora de posición al insertar proceso
      * \pre <em>true<em>
      * \post Retorna la posición en la que debemos insertar el proceso <em>p<em> para que quede el hueco más apretado en la memória
     */
     int pos_nuevo_proceso(Proceso& p);


     //MODIFICADORAS

     /** @brief Modificadora de añanir proceso
      * \pre <em>p<em> es un proceso con datos válidos y el P.I. tiene espacio suficiente.
      * \post Se añade <em>p<em> al procesador .
     */
     void  añadir_proceso(Proceso& p) ;

     /** @brief Modificadora eliminadora de proceso
      * \pre <em>p<em> está en el procesador.
      * \post Se elimina <em>id<em> del P.I..
     */
     void eliminar_proceso(const int& id) ;

     /** @brief Modificadora avanzadora de tiempo
      * \pre <em>t<em> es un entero no negativo que representa un tiempo.
      * \post Avanza el tiempo de todos los procesos activos del P.I. en <em>t<em> unidades de tiempo.
     */
     void avanzar_tiempo_procesador(int t);


     /** @brief Modificadora compactadora de memória
      * \pre <em>true<em>
      * \post Compacta la memoria del P.I.
     */
    void compactar_memoria();
     

     //ENTRADA/SALIDA

     /** @brief Función impresora de procesador
      * \pre El P.I. tiene datos válidos
      * \post Se escriben por pantalla la posición de cada proceso y sus datos.
     */
     void imprimir_procesador();


     int num_procesos();
};

#endif
