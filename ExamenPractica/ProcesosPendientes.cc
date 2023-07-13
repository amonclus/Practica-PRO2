/** @file ProcesosPendientes.cc
 * @brief Implementación de la clase ProcesosPendientes
*/

#include "ProcesosPendientes.hh"

ProcesosPendientes::ProcesosPendientes(){}

//Coste constante
bool ProcesosPendientes::existe_prioridad(const string& prior) const{
     if(PP.find(prior) != PP.end()) return true;   //si al buscar apunta al elemento "end" es que no existe
     else return false;
}

//Coste constante
bool ProcesosPendientes::tiene_procesos_pendientes(const string& prior) const{
     map <string, queue<Proceso>>::const_iterator it;
     it = PP.find(prior);
     if(it->second.empty()) return false;
     else return true;
}

//Coste constante
bool ProcesosPendientes::existe_proceso(string& prior, int& id){
     map<string, queue<Proceso>>::iterator it = PP.find(prior);
     queue<Proceso> aux((*it).second);
     //recorremos una cola auxiliar que creamos a partir de dónde queremos buscar
     while(not aux.empty()){
          if(aux.front().consultar_identificador() == id) return true;
          else{
               aux.pop();
          }
     }
     return false;
}

//Coste constante
void ProcesosPendientes::alta_prioridad(string& newp, char& error){
     map<string, queue<Proceso>>::iterator it = PP.find(newp);
     error = '0';
     if(it != PP.end()){
          error = '1';
     }
     else{
          queue<Proceso> p;  //cola vacía
          PP.insert(make_pair(newp, p));
          pair<int, int>par;   //pair que representará los procesos añadidos y rechazados por el clúster
          par.first = 0;
          par.second = 0;
          intentos.insert(make_pair(newp, par));
     }
}

//Coste constante
void ProcesosPendientes::baja_prioridad(string& prior, char& error){
     map<string, queue<Proceso>>::iterator it = PP.find(prior);
     if(it == PP.end()) error = '1';
     else if(this->tiene_procesos_pendientes(prior)) error = '2';
     else{
          PP.erase(it);
          intentos.erase(prior);
     }
}

//Coste constante
void ProcesosPendientes::alta_proceso_espera(Proceso& p, string prior, char& error){
     map<string, queue<Proceso>>::iterator it = PP.find(prior);
     int s = p.consultar_identificador();
     if(it == PP.end()) error = '1';
     else if(this->existe_proceso(prior, s)) error = '2';
     else{
          error = '0';
          it->second.push(p);
     }
}

//Coste lineal, depende del tamaño de la lista de procesos de la prioridad del P.I
void ProcesosPendientes::eliminar_proceso(string prior, const int& p){
     map <string, queue<Proceso>>::iterator it = PP.find(prior);
     queue<Proceso> aux = it->second;
     queue<Proceso> aux2;
     //recorremos la cola auxiliar hasta encontrar el proceso con identificador "p"
     while(not aux.empty()){
          if(aux.front().consultar_identificador() != p){
               aux2.push(aux.front());
          }
          aux.pop();
     }
     it->second = aux2;       //sustituimos la cola anterior por la nueva cola sin el proceso eliminado
}

//Coste constante
void ProcesosPendientes::sumar_procesos_añadidos_cluster(string& prior, int n){
     map <string, pair<int, int>>::iterator it = intentos.find(prior);
     it->second.first += n;
}

//Coste constante
void ProcesosPendientes::sumar_procesos_rechazados(string& prior, int n){
     map <string, pair<int, int>>::iterator it = intentos.find(prior);
     it->second.second += n;
}
//Coste lineal: Depende del tamaño de la cola de procesos de la prioridad

void ProcesosPendientes::imprimir_prioridad(string prior, char& error){
     map<string, queue<Proceso>>::iterator it = PP.find(prior);
     if(it == PP.end()) error = '1';
     else{
          error = '0';
          queue<Proceso> aux(it->second);              //creamos una cola auxililar identica a la original
          for(int i = 0; i < it->second.size(); ++i){
               aux.front().imprimir_proceso();
               aux.pop();
          }
          map <string, pair<int, int>>::iterator it = intentos.find(prior);
          cout << it->second.first << ' ' <<  it->second.second << '\n';  //sacamos por pantalla los procesos aceptados y rechazados por el clúster
          
     }

}

//Coste lineal: Depende del tamaño del área de espera y el coste de la operación "imprimir_prioridad"
void ProcesosPendientes::imprimir_area_espera(){
     for(map<string, queue<Proceso>>::iterator it = PP.begin(); it != PP.end(); ++it){
          string s = it->first;
          map <string, pair<int, int>>::iterator itaux = intentos.find(s);
          char error = '0';
          if(it->second.empty()){
               cout << s << '\n';
               cout << itaux->second.first << ' ' << itaux->second.second << '\n';   //procesos aceptados y rechazados por el clúster
          }
          else {
               cout << s << '\n';
               this->imprimir_prioridad(s, error);
          }
          
     }
}
//Coste constante
map <string, queue<Proceso>> ProcesosPendientes::auxiliar(){
     return this->PP;
}