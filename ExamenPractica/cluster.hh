/**
 * @file cluster.hh
 * @brief Especificación de la clase Cluster
*/


#ifndef _CLUSTER_HH
#define _CLUSTER_HH

using namespace std;
#include "BinTree.hh"
#include "ProcesosPendientes.hh"
/** @class Cluster
 * @brief Representa un clúster de procesadores con la forma de un árbol binario. En todos los casos asumiremos que el cluster 
 * está inicializado y con valores válidos
 * 
*/

class Cluster{
     private:

     BinTree<string> iden;
     map<string, Procesador> arb;

     /** @brief Función privada lectora de un arbol
      * \pre <em>true<em>
      * \post Guarda en <em>t<em> los un árbol de string representando la estructura de los procesadores y guarda en <em>m<em> el valor de dichos procesadores
     */
    //Coste dependiente de los datos que entren, constante para todos ellos
     void leer_arb(BinTree<string>& t, map<string, Procesador>& m){   
          string id;
          cin >> id;
          if(id != "*"){
               int mem;
               cin >> mem;
               Procesador p(mem, id);
               m.insert(make_pair(id, p));
               BinTree <string>l, r;
               //al leer el nodo actual, debemos leer el hijo izquierdo y el derecho
               leer_arb(l, m);
               leer_arb(r, m);
               t = BinTree<string>(id, l, r);        //al leer el hijo izq y dcho, dejamos en el árbol t el árbol con raíz el primer nodo que hemos insertado y como hijos lo que viene después
          }
          //si se entra un *, es que no tiene sucesor, por lo tanto le ponemos un árbol vacío
          else{
               t = BinTree<string>();
          }

     }

     /** @brief Función privada impresora del clúster
      * \pre <em>t<em> es un árbol de strings inicializado
      * \post Saca por pantalla la estructura del árbol en preorden
     */
    //Coste dependiente del tamaño del árbol
     void ie(BinTree <string>& t){
          if(not t.empty()){
               cout << "(" << t.value();
               BinTree<string> left = t.left();
               BinTree<string> right = t.right();
               ie(left);
               ie(right);
               cout << ")";
          }
          else{
               cout << " ";
          }  
     }
     
     /** @brief Función privada modificadora del clúster
      * \pre  <em>true<em>
      * \post Elimina el proceso representado por <em>p<em> y añade los procesadores nuevos leidos por la operación "modificar_cluster"
     */
    //Coste lineal: Depende del tamaño del mapa "nuevo"
     void modificar_mapa_procesadores(map<string, Procesador>& m, const map<string, Procesador>&nuevo, string& p){
          m.erase(p);
          map<string,Procesador>::const_iterator it = nuevo.begin();
          //recorremos todo el mapa nuevo para insertar todos sus procesadores en el mapa "m".
          while(it != nuevo.end()){
               m.insert(make_pair(it->first, it->second));
               ++it;
          }
     }

     /** @brief Función privada modificadora del árbol del clúster
      * \pre <em>true<em>
      * \post Añade en el nodo representado por <em>id<em> el clúster nuevo
     */
     int modificar_tree(BinTree<string>& t, const BinTree<string>& nuevo, const string id){
          if(t.empty()) return 1;
          else if(t.value() == id){
               t = nuevo;     //sustituimos el nodo que buscamos por el árbol nuevo
               return 1;  
          }
          //si el nodo actual no es el buscado recorremos el hijo izquierdo y derecho
          else{
               BinTree<string> left = t.left();
               BinTree<string> right = t.right();
               modificar_tree(left, nuevo, id);        
               modificar_tree(right, nuevo, id);
               t = BinTree<string>(t.value(), left, right);
          }
          return 1; 
     }

     //Borra todos los procesadores de t del mapa m
     void borrar_mapa(BinTree<string>t, map<string,Procesador>& m, int& sum, int& sumpro){
          if(not t.empty()){
               string s = t.value();
               map<string, Procesador>::iterator it = m.find(s);
               sum += 1;
               sumpro += it->second.num_procesos();
               m.erase(it);
               BinTree<string> l = t.left();
               BinTree<string> r = t.right();
               borrar_mapa(l, m, sum, sumpro);
               borrar_mapa(r,m, sum, sumpro);
          }
     }


     int  podar(string id, BinTree<string>& t, map<string, Procesador>& m, int& sum, int& sumpro){
          if(not t.empty()){
               if(t.value() == id){
                    borrar_mapa(t,m, sum, sumpro);
                    BinTree<string>vacio;
                    t = vacio;
                    return 0;
               }
               else{
                    BinTree<string> l = t.left();
                    BinTree<string> r = t.right();
                    podar(id, l, m, sum, sumpro);
                    podar(id, r, m, sum, sumpro);
                    t = BinTree<string>(t.value(), l, r);
                    return 1;
               }    
          }
          return 0;

     }




     /** @brief Función privada procesos en ejecución
      * \pre <em>id<em> es un nodo de <em>t<em>
      * \post Retorna un booleano que indica si ese procesador tiene algún proceso en ejecución.
     */
    //Coste constante
     bool tiene_procesos_ejec( string& id, map<string, Procesador> m){
          map<string,Procesador>::iterator it = m.find(id);
          if(it->second.consultar_memoria_libe() < it->second.consultar_memoria_total()) return true;         //si la memória libre es menor que la total es que hay algún proceso
          else return false;
     }

     /** @brief Función privada subprocesadores
      * \pre <em>id<em> es un nodo de <em>t<em>
      * \post Retorna un booleano que indica si tiene subprocesadores 
     */
    //Coste dependiente de lo alejado que esté el nodo "id" de la raíz y cómo a la izquierda esté
     bool tiene_subprocesadores(BinTree<string>& t, string& id){
          //recorreremos hasta encontrar el nodo de "t" con valor "id" mientras el árbol no esté vacío
          if(not t.empty()){
               if(t.value() == id){
                    if(not t.left().empty() or not t.right().empty()) return true;
                    else return false;
               }
               else{
                    BinTree<string>left = t.left();
                    BinTree<string>right = t.right();
                    return tiene_subprocesadores(left, id) or tiene_subprocesadores(right, id);
               }
          }
          else return false;
          
     }
     
     /** @brief Función privada hueco ajustado
      * \pre <em>p<em> es un proceso con valores válidos
      * \post Retorna el identificador donde se debe colocar el proceso bajo los siguentes criterios: Busca el procesador
      * con el hueco más pequeño, si hay un empate, escoge el procesador con más memória libre, en caso de que se produzca otro empate,
      * escoje el procesador más cercano a la raí<, y en caso de otro empate, escoge el procesador más a la izquierda
     */
    //Coste alto ya que recorre varias veces un mismo árbol en las llamadas a función
     string hueco_mas_ajustado(BinTree<string>& t, map<string, Procesador>& m,const Proceso& p){
          map<string, Procesador>::iterator it = m.begin();
          string id = "-1";
          int diff;
          int size = p.consultar_memoria();
          int min = 2147483647; //nos aseguramos que es un valor que nunca tendremos 
          while(it != arb.end()){
               int tam = it->second.tamaño_hueco_ajustado(p);
               if(tam != -1){
                    if(not it->second.tiene_proceso(p.consultar_identificador())){
                         string idfirst = it->first;
                         diff = tam - size;
                         if(diff < min){
                              min = diff;
                              id = idfirst;
                         }
                         //escoger el que tenga mayor memoria libre
                         else if(diff == min){
                              map<string, Procesador>::iterator it2 = m.find(id);
                              int memlibre1 = it2->second.consultar_memoria_libe();
                              int memlibre2 = it->second.consultar_memoria_libe();
                              if(memlibre1 < memlibre2){
                                   id = idfirst;
                              }
                              //si tienen la misma memória libre se determina por cual está más cercano a la raíz
                              else if(memlibre1 == memlibre2){
                                   string id1 = idfirst;
                                   string id2 = it2->first;
                                   string aux = cercano_a_raiz(t, id1, id2);
                                   //si la función retorna un -1 es que ambos están a la misma distancia de la raíz, por lo tanto se escoge el que esté más a la izquierda
                                   if(aux == id1) id = id1;
                                   else if(aux == "-1"){
                                        id = mas_a_izquierda(t, id1, id2);
                                   }
                              }
                         }
                    }
               }
               ++it;
          }
          return id; //identificador del Procesador con el hueco mínimo que cumpla todas las condifiones especificadas
     }

     
     /** @brief Función privada nodo más cercano a la raíz
      * \pre <em>id1<em> y <em>id1<em> son nodos del árbol <em>t<em>
      * \post Escoge entre <em>id1<em> y <em>id2<em> según cual es el más cercano a la raíz y retorna ese string.
     */
     string cercano_a_raiz(BinTree<string>& t, string& id1,  string& id2){
          int one = depth(t, id1, 0);
          int two = depth(t, id2, 0);
          if( one > two ) return id2;
          else if(one == two) return "-1";
          else return id1;
     }

     /** @brief Función privada altura de un nodo
      * \pre <em>id<em> es un nodo de <em>t<em> 
      *\post Retorna la altura de este nodo
     */
     int depth(BinTree<string>& t, string& id, int d){
          if(not t.empty()){
               if(t.value() == id) return d;
               else{
                    BinTree<string>l = t.left();
                    BinTree<string>r = t.right();
                    return depth(l, id, d+1) + depth(r,id,d+1);
               }
          }
          else return 0;
     }

     /** @brief Función privada hijo más a la izquierda
      * \pre <em>id1<em> y <em>id1<em> son nodos del árbol <em>t<em>
      * \post Escoge entre <em>id1<em> y <em>id2<em> según cual es el más a la izquierda del árbol y retorna ese string.
     */
     string mas_a_izquierda(BinTree<string>& t, string& id1, string&id2){
          if(t.empty()){
               return "-1";
          }
          else if(t.value() == id1 or t.value() == id2){
               return t.value();
          }
          BinTree<string> l = t.left();
          BinTree<string> r = t.right();
          string left = mas_a_izquierda(l, id1, id2);
          string right = mas_a_izquierda(r, id1, id2);
          if(left != "-1") return left;
          else if(right != "-1") return right;

          return "-1";
     }


     
     public:
     //CREADORAS

     /** @brief Creadora por defecto de un clúster
      * \pre <em>true<em>
      * \post Construye un clúster vacío.
     */
     Cluster(); 


     /** @brief Función configuradora del clúster
          \pre <em>true<em> 
          \post Se leen los procesadores de un clúster, incluyendo su memória, en preorden.
     */
     void configurar_cluster();


     //MODIFICADORAS
     /** @brief Modificadora del clúster
     \pre: <em>nuevo<em> es un clúster inicializado inicializado y <em>p<em> es un identificador de un procesador existente.
     \post: Se inserta el cluster nuevo en el procesador p.
     */
     void modificar_cluster(string& p, Cluster& nuevo, char& error);

     /** @brief Función de añadir procesos a un procesador
     \pre: <em>id<em> es el identificador de un procesador y <em>p<em> es un proceso con valores válidos
     \post: Se ejecuta el proceso en ese procesador y la memoria que usa pasa a estar ocupada.
     */
     void alta_proceso_procesador(string& id, Proceso& p, char& error);
     
     /** @brief Función de baja de procesos de un procesador
     \pre: <em>id<em> es el identificador de un procesaodr y <em>idpro<em> representa el identificador del proceso a eliminar.
     \post: Se elimina el proceso con id <em>idpro<em> del procesador de identificador <em>id<em>
     */
     void baja_proceso_procesador(string& id, int& idpro, char&error);
     

    /** @brief Función enviadora de procesos del área de espera al clúster
     * \pre El área de procesos pendientes <em>pp<em> está inicializada
     * \post Se intentan enviar n procesos del área de procesos pendientes al clúster del parámetro implícito
    */
     void enviar_procesos_cluster(ProcesosPendientes& pp, int n);

     /** @brief Función de avanzar tiempo de todos los procesadores
      * \pre <em>t<em> es un entero no negativo que representa una cantidad de tiempo
      * \post Se avanza el tiempo de todos los procesadores en t unidades
     */
     void avanzar_tiempo_cluster(int t);

     /** @brief Función compactadora de memória de un procesador
      * \pre <em>id<em> representa el identificador de un procesador
      * \post Compacta la memoria del procesador representado por <em>id<em> sin dejar huecos entre proceso y proceso
     */
     void compactar_memoria_procesador(string id, char& error);

     /** @brief Compactadora de memória del clúster
     * \pre <em>true<em>
     * \post Compacta la memoria de todos los procesadores del clúster
     * */ 
     void compactar_memoria_cluster();


     //ENTRADA/SALIDA

     /** @brief Función impresora de un procesador
      * \pre <em>id<em> es un identificador de un procesador
      * \post Se busca dicho procesador y se imprime por pantalla
     */
     void imprimir_procesador(string& id, char& error);

     /** @brief Función impresora de todos los procesadores del clúster
      * \pre <em>true<em>
      * \post Escribe por pantalla en orden de identificador ascendiente todos los procesadores del cluster
     */
     void imprimir_procesadores_cluster();


     /** @brief Función impresora de la estructura del clúster
      * \pre <em>true<em>
      * \post Imprime la estructura de procesadores del clúster en preorden
     */
    void imprimir_estructura_cluster();


     void podar_cluster(string id, char& error);
};

#endif
