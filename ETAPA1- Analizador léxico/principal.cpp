//Seminario de Solucion de Problemas de Traductores de Lenguajes D02
// Velasco Hernandez Victor Manuel
#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"

using namespace std;

int main(int argc, char *argv[]){

    std::string cadena;
    cout << "\nMini generador lexico\n\nVelasco Hernandez, Victor Manuel\n\nEscribe la cadena a evaluar: " << endl;
    std::getline(std::cin,cadena);
    Lexico lexico;
    lexico.entrada(cadena);

    cout << "\n\nResultados del Analisis Lexico:" << endl << endl;
    cout << "Simbolo\t\tTipo" << endl;
    
    while ( lexico.simbolo.compare("$") != 0 ){
          lexico.sigSimbolo();
          
          cout <<  lexico.simbolo << "\t\t" << lexico.tipoAcad(lexico.tipo) << endl;          
    }
        
    cin.get();
  
    return 0;
}
