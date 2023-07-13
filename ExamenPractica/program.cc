/** 
 * @file program.cc
 *  @brief Implementación del programa principal usando las clases
*/

using namespace std;
#include <iostream>
#include "cluster.hh"


int main(){
     Cluster c;
     ProcesosPendientes pp;

     c.configurar_cluster();
     
     int n;
     cin >> n;
     for(int i = 0; i < n; ++i){
          char error = '0';
          string s;
          cin >> s;
          pp.alta_prioridad(s, error);
          if(error == '1') cout << "error: ya existe prioridad" << '\n';
     }

     string comm;
     cin >> comm;

     while(comm != "fin"){
          char error = '0';
          if(comm == "cc" or comm == "configurar_cluster"){
               cout << "#" << comm << '\n';
               c.configurar_cluster();
          }

           else if(comm == "mc" or comm == "modificar_cluster"){
               string p;
               cin >> p;
               cout << "#" << comm << ' ' << p <<  '\n';
               Cluster nuevo;
               nuevo.configurar_cluster();
               c.modificar_cluster(p, nuevo, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
               else if(error == '2') cout << "error: procesador con procesos" << '\n';
               else if (error == '3') cout << "error: procesador con auxiliares" << '\n';
          }
          

          else if(comm == "ap" or comm == "alta_prioridad"){
               string prior;
               cin >> prior;
               cout << "#" << comm << ' ' << prior << '\n';
               pp.alta_prioridad(prior, error);
               if(error == '1') cout << "error: ya existe prioridad" << '\n';
          }

          else if(comm == "bp" or comm == "baja_prioridad"){
               string prior;
               cin >> prior;
               cout << "#" << comm << ' ' << prior << '\n';
               pp.baja_prioridad(prior, error);
               if(error == '1') cout << "error: no existe prioridad" << '\n';
               else if(error == '2') cout << "error: prioridad con procesos" << '\n';               
          }
          
          else if(comm == "ape" or comm == "alta_proceso_espera"){
               string  prior;
               int mem, time, id;
               cin >> prior >> id >> mem >> time;
               cout << "#" << comm << ' ' << prior << ' ' << id << '\n';
               Proceso p(id, mem, time);
               pp.alta_proceso_espera(p, prior, error);
               if(error == '1') cout << "error: no existe prioridad" << '\n';
               else if(error == '2') cout << "error: ya existe proceso" << '\n';
          }

          else if(comm == "app" or comm == "alta_proceso_procesador"){
               string id; //id es el identificador del procesador que buscamos
               int mem, time, idpro;
               cin >> id >> idpro >> mem >> time;
               cout << "#" << comm << ' ' << id << ' ' << idpro << '\n';
               Proceso p(idpro, mem, time);
               c.alta_proceso_procesador(id, p, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
               else if(error == '2') cout << "error: ya existe proceso" << '\n';
               else if(error == '3') cout << "error: no cabe proceso" << '\n';   
          }

          else if(comm == "bpp" or comm == "baja_proceso_procesador"){
               string procesador;
               int proceso;
               cin >> procesador >> proceso;
               cout << '#' << comm << ' ' << procesador << ' ' << proceso << '\n';
               c.baja_proceso_procesador(procesador, proceso, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
               else if(error == '2') cout << "error: no existe proceso" << '\n';
          }

          else if(comm == "epc" or comm == "enviar_procesos_cluster"){
               int n;
               cin >> n;
               cout << '#' << comm << ' ' << n << '\n';
               c.enviar_procesos_cluster(pp, n);
          }
          
          

          else if(comm == "at" or comm == "avanzar_tiempo"){
               int t;
               cin >> t;
               cout << '#' << comm <<  ' ' << t << '\n';
               c.avanzar_tiempo_cluster(t);
          }

          else if(comm == "ipri" or comm == "imprimir_prioridad"){
               string prior;
               cin >> prior;
               cout << '#' << comm << ' ' << prior << '\n';
               char error = '0';
               pp.imprimir_prioridad(prior, error);
               if(error == '1') cout << "error: no existe prioridad" << '\n';
          }
          
          else if(comm == "iae" or comm == "imprimir_area_espera"){
               cout << "#" << comm << '\n';
               pp.imprimir_area_espera();
          }

          else if(comm == "ipro" or comm == "imprimir_procesador"){
               string id;
               cin >> id;
               cout << "#" << comm << ' ' << id << '\n';
               c.imprimir_procesador(id, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
          }

          else if(comm == "ipc" or comm == "imprimir_procesadores_cluster"){ 
               cout << "#" << comm << '\n';         
               c.imprimir_procesadores_cluster();
          }

          else if(comm == "iec" or comm == "imprimir_estructura_cluster"){
               cout << "#" << comm << '\n';
               c.imprimir_estructura_cluster();
          }

          else if(comm == "cmp" or comm == "compactar_memoria_procesador"){
               string id;
               cin >> id;
               cout << '#' << comm << ' ' << id << '\n';
               c.compactar_memoria_procesador(id, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
          }

          else if(comm == "cmc" or comm == "compactar_memoria_cluster"){
               cout << "#" << comm << '\n';
               c.compactar_memoria_cluster();
          }
          
          else if(comm == "pc" or comm == "podar_cluster"){
               string id;
               cin >> id;
               cout << "#" << comm << " " << id << '\n';
               c.podar_cluster(id, error);
               if(error == '1') cout << "error: no existe procesador" << '\n';
               else if(error == '2') cout << "error: se intenta borrar la raiz" << '\n';
          }
          
         cin >> comm;    
     }
}
