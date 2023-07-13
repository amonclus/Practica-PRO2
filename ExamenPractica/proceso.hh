/** @file proceso.hh
    @brief Especificación de la clase Proceso
 */


#ifndef _PROCESO_HH
#define _PROCESO__HH

using namespace std;
#include <iostream>

/** @class Proceso
    @brief Representa un proceso 
    Este proceso tiene un identificador (string), una memória que ocupa (int) y un tiempo de ejecución (int).
 * */
class Proceso {

private:
int id;
int mem; 
int time_left;

public:
     //CONSTRUCTORAS

      /** @brief Creadora de un proceso
      \pre <em>true<em>
      \post El resultado es un proceso con las características de los parámetros <em>id<em>, su identificador, <em>mem<em>, su memória y <em>time<em>, su tiempo de ejecución
     */
     Proceso(int id, int mem, int time);


     //CONSULTORAS:

      /** @brief Colsultadora de un identificador de un proceso
      \pre El parámetro implícito tiene valores válidos
      \post Retorna un entero que representa el identificador de la función implícita
     */
     int consultar_identificador() const;

      /** @brief Consultora de la memória de un proceso
      \pre El parámetro implícito tiene valores válidos
      \post Retorna un entero que representa la memória que opupa un proceso
     */
     int consultar_memoria() const;



     /** @brief Consultora del tiempo restante de ejecución
      * \pre El P.I. tiene valores válidos
      * \post Retorna un entero que representa el tiempo restante del P.I.
     */
     int consultar_tiempo_restante() const;
     //MODIFICADORAS


     /** @brief Modificadora del tiempo restante
      *  \pre El P.I. tiene valores válidos
      * \post Resta al tiempo restante <em>t<em> unidades
     */
     void avanzar_tiempo_proceso(int t);



     //ENTRADA SALIDA
     
     /** @brief Función impresora de un proceso
      * \pre El P.I. tiene valores válidos
      *  \post Saca por pantalla el identificador, memória y tiempo de ejecución restante, en ese mismo orden.
     */
     void imprimir_proceso();
};

#endif
