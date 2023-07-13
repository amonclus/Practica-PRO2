/**  @file ProcesosPendientes.hh
     @brief Especificación de la clase del área de los ProcesosPendientes
 */

#ifndef _PROCESOSPENDIENTES_HH
#define _PROCESOSPENDIENTES_HH

using namespace std;
#include <queue>
#include <map>
#include "procesador.hh"
#include <list>
/**
     @class ProcesosPendientes
     @brief Representa un área de ProcesosPendientes
     Esta contiene un área con diferentes prioridades donde cada prioridad contiene una cola de procesos que están pendientes de ser ejecutados.
     Las prioridades se representan con strings y se ordenan de manor a mayor
 */
class ProcesosPendientes{ 

private:
map <string, queue<Proceso>> PP;  //mapa cuyos valores son las colas de procesos y las llaves su prioridad
map <string, pair<int, int>> intentos; //indica los procesos añadidos y rechazados por el clúster
//primera pos: añadidos. segunda pos: rechazados
public:

     //CREADORAS
     /** @brief Creadora por defecto
      \pre <em>true<em>
      \post El resultado es un área de procesos pendientes vacía
     */
     ProcesosPendientes();

     //CONSULTORAS

       /** @brief Comprobadora de existencia de prioridad concreta
      \pre <em>prior<em> representa el identificador de una prioridad y el P.I. tiene valores válidos
      \post El resultado es un booleano que indica si dicha prioridad existe en el parámetro implícito
     */
     bool existe_prioridad(const string& prior) const;

       /** @brief Comprobadora de existencia de procesos pendientes
      \pre <em>prior<em> representa el identificador de una prioridad y el P.I. tiene valores válidos
      \post El resultado es un booleano que indica si dicha prioridad tiene algún proceso pendiente
     */
     bool tiene_procesos_pendientes(const string& prior) const;

     /** @brief Comprobadora de existencia de proceso en una prioridad
       \pre <em>prior<em> representa la prioridad en la que queremos buscar y <em>id<em> es el identificador de un proceso
       \post El resultado es un booleano que indica si dicha prioridad tiene un proceso con identificador <em>id<em>
     */
     bool existe_proceso(string& prior, int& id);

     //MODIFICADORAS

       /** @brief Dada de alta de una prioridad
      \pre En el parámetro implícito no hay una prioridad con prioridad <em>newp<em>, en el caso de que la haya, se imprime un mensaje de error
      \post Se añade al parámetro implícito la prioridad vacía <em>newp<em>
     */
     void alta_prioridad(string& newp, char& error);

       /** @brief Dada de baja de una prioridad
      \pre En el parámetro implícito hay una prioridad <em>prior<em>, si no la hay o esta tiene procesos pendientes, se imprime un mensaje de error
      \post Se elimina la prioridad <em>prior<em> del parámetro implícito
     */
     void baja_prioridad(string& prior, char& error);

       /** @brief Dada de alta de un proceso en el área de procesos pendientes
      \pre El identificador <em>prior<em> existe dentro del área de procesos y no hay ningún proceso en esa prioridad con el identificador de <em>p<em>. En caso contrario, 
      se imprime un mensaje de error.
      \post El proceso <em>p<em> se añade a la prioridad <em>prior<em> del parámetro implícito.
     */
     void alta_proceso_espera(Proceso& p, string prior, char& error);

     /** @brief Eliminadora de procesos del área de procesos pendientes
      * \pre <em>prior<em> es la prioridad de la que queremos borrar el proceso representado por el identificador <em>p<em>
      * \post Se borra el proceso representado por <em>p<em> de la prioridad representada por <em>prior<em>
     */
     void eliminar_proceso(string prior,const int& p);



     /** @brief Sumadora de los procesos añadidos a una prioridad
        \pre <em>prior<em> es el identificador de una prioridad del P.I. y n es un entero no negativo
        \post Suma n a la cantidad de procesos añadidos al clúster
     */
     void sumar_procesos_añadidos_cluster(string& prior, int n);

     /** @brief
        \pre <em>prior<em> es el identificador de una prioridad del P.I. y n es un entero no negativo
        \post Suma n a la cantidad de procesos rechazados al clúster
     */
     void sumar_procesos_rechazados(string& prior, int n);

     //ENTRADA/SALIDA

     /** @brief
         \pre <em>prior<em> es el identificador de la prioridad del P.I. que queremos imprimir
         \post Saca por pantalla los procesos pendientes de esta prioridad, además escribe el número de procesos enviados y rechazados al clúster. 
     */
     void imprimir_prioridad(string prior, char& error);

     /** @brief
      * \pre <em>true<em>
      * \post Se imprime cada prioridad del área de procesos pendientes en orden ascendente.
     */
     void imprimir_area_espera();

     /** @brief Función auxiliar utilizada para retornar el mapa de colas de procesos del área de procesos pendientes
      * \pre <em>true<em>
      * \post retorna el mapa de colas de procesos del área de procesos pendientes
     */
     map <string, queue<Proceso>> auxiliar();

     

};

#endif