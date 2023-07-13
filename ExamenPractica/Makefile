OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o cluster.o ProcesosPendientes.o procesador.o proceso.o 
	g++ -o program.exe *.o
 
program.o: program.cc cluster.hh
	g++ -c program.cc $(OPCIONS)

cluster.o: cluster.cc cluster.hh BinTree.hh ProcesosPendientes.hh
	g++ -c cluster.cc $(OPCIONS)

procesador.o: procesador.cc procesador.hh proceso.hh	
	g++ -c procesador.cc $(OPCIONS)

proceso.o: proceso.cc proceso.hh
	g++ -c proceso.cc $(OPCIONS)

ProcesosPendientes.o: ProcesosPendientes.cc ProcesosPendientes.hh procesador.hh
	g++ -c ProcesosPendientes.cc $(OPCIONS)


practica.tar: BinTree.hh cluster.hh procesador.hh proceso.hh ProcesosPendientes.hh cluster.cc procesador.cc proceso.cc ProcesosPendientes.cc program.cc Makefile
	tar -cvf practica.tar BinTree.hh cluster.hh procesador.hh proceso.hh ProcesosPendientes.hh cluster.cc procesador.cc proceso.cc ProcesosPendientes.cc program.cc Makefile html.zip

clean:
	rm *.o
	rm *.exe

