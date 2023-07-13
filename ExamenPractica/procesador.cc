/** @file procesador.cc
 * @brief Implementación de la clase procesador
*/

#include "procesador.hh"



Procesador::Procesador(int mem, string id){
     mem_libre = mem;
     capacidad = mem;
     this->id = id;
     set<int> s;
     s.insert(0);
     space.insert(make_pair(mem,s));
}

//Coste constante: únicamente consulta un parámetro y lo retorna.
int Procesador::consultar_memoria_total() const {
     return capacidad;
}

//Coste constante: únicamente consulta un parámetro y lo retorna + coste de la operación "lower_bound"
int Procesador::tamaño_hueco_ajustado(const Proceso& p) const {
     //lower bound indica el espacio immediatamente mayor que la mem de p
     map<int, set<int>>::const_iterator it = space.lower_bound(p.consultar_memoria());
     if(it == space.end()) return -1;
     else return it->first;
}

//Coste constante: únicamente consulta un parámetro y lo retorna.
string Procesador::consultar_identificador() const {
     return id;
}

//Coste constante: únicamente consulta un parámetro y lo retorna.
int Procesador::consultar_memoria_libe() const {
     return mem_libre;
}

//Coste constante: únicamente consulta un parámetro y lo retorna.
bool Procesador::tiene_proceso(const int& id) const{
     if(pos.find(id) == pos.end()) return false;            
     else return true;   
}

//Coste constante: únicamente consulta un parámetro y lo retorna + coste de la operación "lower_bound"
bool Procesador::tiene_espacio(const Proceso& p) const {
     //lower bound
     int p_mem = p.consultar_memoria();
     map<int, set<int>>::const_iterator it = space.lower_bound(p_mem);
     if(it == space.end()) return false;
     else return true;
}

//Coste constante
void Procesador::añadir_proceso(Proceso& p){
          int p_mem = p.consultar_memoria();
          map<int, set<int>>::iterator it = space.lower_bound(p_mem); //hueco más pequeño
          if(it != space.end()){
               set<int>::iterator itpos = it->second.end();
               --itpos; //space->end -1
               int i = *(itpos);   //i = última posición del set
               
               mem.insert(make_pair(i, p));
               pos.insert(make_pair(p.consultar_identificador(), i));

               if(it->first > p_mem){        //el proceso no ocupa el tamaño de todo el hueco
                    int new_tam = it->first - p_mem;
                    int new_pos = i + p_mem;
                    map<int, set<int>>::iterator it2 = space.find(new_tam);
                    if(it2 != space.end()) it2->second.insert(new_pos);    //el hueco con tamaño "new_tam" ya existe, así que aádimos la posición donde comienza el hueco nuevo de ese tamaño
                    else{
                         //no existe un hueco de ese tamaño así que creamos uno nuevo con una única posición "new_pos"
                         set<int>aux;
                         aux.insert(new_pos);
                         space.insert(make_pair(new_tam, aux));
                    }
               }
               it->second.erase(i);
               if(it->second.empty()) space.erase(it); //si está vacio eliminamos toda la pos del mapa
          
               mem_libre -= p_mem;
          }
}

//Coste constante
void Procesador::eliminar_proceso(const int& id){
     map<int, int>::iterator it = pos.find(id);
     int i = it -> second; //indica la posición
     map<int, Proceso>:: iterator it2 = mem.find(i); //Retorna un iterador al proceso

     int m = it2->second.consultar_memoria();
     mem_libre += m;
     map<int, Proceso>:: iterator itant = it2;
     map<int, Proceso>:: iterator itpost = it2;
     ++itpost;
     int first_ant = 0;
     int first_post = i + m;
     int last_pos = capacidad;
     
     if(itant != mem.begin()){
          --itant;
          first_ant = itant->first + itant->second.consultar_memoria();
     }
     int diffant = i - first_ant;
     if(itpost != mem.end()){
          last_pos = itpost->first;
     }

     int diffpost = last_pos - first_post;
     int diff = m + diffant + diffpost;
     int aux = first_ant;

    

     if(diffant > 0){
          map<int, set<int>>::iterator ant = space.find(diffant);
          ant->second.erase(first_ant);
          if(ant->second.empty()){
               ant = space.erase(ant);   //si queda vacío eliminamos el hueco
          }
     }

     if(diffpost > 0){
          map<int, set<int>>::iterator post = space.find(diffpost);
          post->second.erase(first_post);
          if(post->second.empty()){
               post = space.erase(post);
          }
     }
     
     if(space.find(diff) != space.end()){
          space.find(diff)->second.insert(aux);
     }
     else{
          set<int> auxs;
          auxs.insert(aux);
          space.insert(make_pair(diff, auxs));
     }
     
     mem.erase(it2);
     pos.erase(it);
     

}

//Coste lineal: Hará mem.size() iteraciones
void Procesador::avanzar_tiempo_procesador(int t){
     map<int, Proceso>::iterator it = mem.begin();
     map<int,Proceso>::iterator aux = it;
     //recorremos todos los procesos del procesador y avanzamos su tiempo de ejecución
     while(it != mem.end()){
          ++aux;
          it->second.avanzar_tiempo_proceso(t);
          if(it->second.consultar_tiempo_restante() <= 0){ 
               eliminar_proceso(it->second.consultar_identificador());
          }
          it = aux;
     }
}

//Coste lineal: Hará mem.size() iteraciones
void Procesador::compactar_memoria(){
     int i = 0;
     map<int, Proceso>::iterator it = mem.begin();
     map<int, int>::iterator it2;
     //comenzamos por la posición 0 y vamos moviendo todos los procesos sin dejar un espacio, sumandole a la i el tamaño del proceso en cada ejecución
     while(it != mem.end()){
          Proceso p = it->second;
          it = mem.erase(it);
          mem.insert(make_pair(i, p));
          it2 = pos.find(p.consultar_identificador());
          it2->second = i;
          i+= p.consultar_memoria();
     }
     space.clear();
     set<int> aux;
     aux.insert(i);
     space.insert(make_pair(mem_libre, aux));
}

//Coste lineal: Hará mem.size() iteraciones
void Procesador::imprimir_procesador() {
     map<int,Proceso>::iterator it = mem.begin();
     while(it != mem.end()){
          cout << it->first << ' ' ;
          it->second.imprimir_proceso();
          ++it;
     }
}

int Procesador::num_procesos(){
     return mem.size();
}    