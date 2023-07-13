/** @file proceso.cc
 * @brief Implementación de la clase proceso
*/

#include "proceso.hh"

Proceso::Proceso(int id, int mem, int time){
     this->id = id;
     this->mem = mem;
     this->time_left = time;
}

int Proceso::consultar_identificador() const{
     return id;
}

int Proceso::consultar_memoria() const{
     return mem;
}

int Proceso::consultar_tiempo_restante()const {
     return time_left;
}

void Proceso::avanzar_tiempo_proceso(int t){
     time_left -= t;
}


void Proceso::imprimir_proceso(){
     cout << id << " " << mem << " " << time_left << '\n';
}