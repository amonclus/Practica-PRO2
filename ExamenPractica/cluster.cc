/** @file cluster.cc
 * @brief Implementación de la clase cluster
*/


#include "cluster.hh"


Cluster::Cluster(){};  //crea un cluster vacío
//Coste dependiente del de la función "leer arb"
void Cluster::configurar_cluster(){
     this->arb.clear();
     leer_arb(this->iden, this->arb);
}

//Coste de "modificar_tree" + "modificar_mapa_procesadores"
void Cluster::modificar_cluster(string& p, Cluster& nuevo, char& error){
     map<string, Procesador>::iterator it = arb.find(p);
     if(it == arb.end()) error = '1';
     else if(tiene_procesos_ejec( p, this->arb)) error = '2';
     else if(tiene_subprocesadores(this->iden, p)) error = '3';
     else{
          //modificaremos el árbol (estructura) y el mapa (contenido de procesadores)
          modificar_tree(this->iden, nuevo.iden, p);
          modificar_mapa_procesadores(this->arb, nuevo.arb, p);
     }
}

//Coste constante (añadir elemento a un mapa y tres consultoras)
void Cluster::alta_proceso_procesador(string& id, Proceso& p, char& error){
     map<string, Procesador>::iterator it = arb.find(id);
     if(it == arb.end()) error = '1';
     else if(it->second.tiene_proceso(p.consultar_identificador())) error = '2';
     else if(not it->second.tiene_espacio(p)) error = '3';
     else{
          it->second.añadir_proceso(p);
     }
}
//Coste constante (eliminar elemento de un mapa y dows consultoras)
void Cluster::baja_proceso_procesador(string& id, int& idpro, char& error){
     map<string, Procesador>::iterator it = arb.find(id);
     if(it == arb.end()) error = '1';
     else if(not it->second.tiene_proceso(idpro)) error = '2';
     else{
          it->second.eliminar_proceso(idpro);
     }
}

//Coste lineal: Depende del tamaño del árbol
void Cluster::avanzar_tiempo_cluster(int t){
     //recorrido avanzado el tiempo de todos los procesadores del clúster
     for(map<string, Procesador>::iterator it = arb.begin(); it != arb.end(); ++it){
          it->second.avanzar_tiempo_procesador(t);
     }
}

//Coste dependiente de la función "imprimir_procesador"
void Cluster::imprimir_procesador(string& id, char& error){
     map<string, Procesador>::iterator it = arb.find(id);
     if(it == arb.end()) error = '1';
     else{
          it->second.imprimir_procesador();
     }
}

//Coste lineal: Dependiente del tamaño del árbol
void Cluster::imprimir_procesadores_cluster(){
     for(map<string, Procesador>::iterator it = arb.begin(); it != arb.end(); ++it){
          cout << it->first << '\n';
          it->second.imprimir_procesador();
     }
}

//Coste lineal: Dependiente del tamaño del árbol
void Cluster::imprimir_estructura_cluster(){
     ie(iden);
     cout << '\n';
}

//Coste de la funcióin "compactar_memoria"
void Cluster::compactar_memoria_procesador(string id, char& error){
     map<string, Procesador>::iterator it = arb.find(id);
     if(it == arb.end()) error = '1';
     else{
          it->second.compactar_memoria();
     }
}

//Coste lineal: Dependiente del tamaño del árbol + coste de "compactar_memória" en cada iteración"
void Cluster::compactar_memoria_cluster(){
     map<string, Procesador>::iterator it = arb.begin();
     while(it != arb.end()){
          it->second.compactar_memoria();
          ++it;
     }
}

//Coste dependiente del número de procesos a enviar o del tamaño del área de procesos (coste alto por culpa de la función "hueco_mas_ajustado")
void Cluster::enviar_procesos_cluster(ProcesosPendientes& pp, int n){
     map<string, queue<Proceso>> aux = pp.auxiliar(); //area de procesos
     map<string, queue<Proceso>>::iterator it = aux.begin(); //apunta a cada una de las prioridades
     int i = 0;
     if(it != aux.end()){ 
          queue<Proceso> auxq = it->second;
          while(i < n and it != aux.end()){
               //cola de los procesos a transferir
               if(not auxq.empty()){
                    Proceso p = auxq.front();
                    string id = hueco_mas_ajustado(iden, arb, p);
                    
                    //si no cabe en ningún procesador
                    if(id == "-1"){
                         string ida = it->first; //identificador de la priridad en la que estamos
                         pp.sumar_procesos_rechazados(ida, 1);
                    }
                    else{
                         string add = it->first;
                         pp.sumar_procesos_añadidos_cluster(add, 1);
                         map<string, Procesador>::iterator itpro = arb.find(id);
                         itpro->second.añadir_proceso(p); //añadimos el proceso al clúster
                         pp.eliminar_proceso(it->first, p.consultar_identificador());
                         ++i;
                    }
                    auxq.pop();
               }
               else{ 
                    ++it;
                    if(it != aux.end()){
                         auxq = it->second;
                    }
               }
          }
     }
}

void Cluster::podar_cluster(string id, char& error){
     map<string,Procesador>::iterator itarb = arb.find(id);
     if(itarb == arb.end()) error = '1';
     else if(id == iden.value()) error = '2';
     else{
          int sum = 0, sumpro = 0;
          podar(id, iden, arb, sum, sumpro);
          cout << "Poda " << sum << " " <<sumpro <<'\n';
     }
}
    