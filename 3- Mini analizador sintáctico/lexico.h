#ifndef _LEXICO
#define _LEXICO

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TipoSimbolo{
public:
 static const int ERROR= -10;
 static const int IDENTIFICADOR= 0;
 static const int ENTERO= 5;
 static const int REAL= 23;
 static const int CADENA= 3;
 static const int TIPODD= 4;
 static const int OPADIC= 1;
 static const int OPMULTIP= 6;
 static const int OPRELAC= 7;
 static const int OPOR= 8;
 static const int OPAND= 9;
 static const int OPNOT= 10;
 static const int OPIGUALDAD= 11;
 static const int PUNTOYCOMA= 12;
 static const int COMA= 13;
 static const int PARENTI= 14;
 static const int PARENTD= 15;
 static const int CORCHETI= 16;
 static const int CORCHETD= 17;
 static const int OPIGUAL= 18;
 static const int IF= 19;
 static const int WHILE= 20;
 static const int RETURN= 21;
 static const int ELSE= 22;
 static const int PESOS= 2;
};


class Lexico{
      private:
       string fuente;


       int ind;
       bool continua;
       char c;
       int estado;
       int digito;
       bool id;
       char sigCaracter();
       void sigEstado(int estado);
       void aceptacion(int estado);
       bool esLetra(char c);
       bool esDigito(char c);
       bool esEspacio(char c);
       void retroceso();
       void aceptacion2(int c);

      public:
       string simbolo;
       int tipo;
      vector<string>texto;
      vector<int>tipos;
       Lexico(string fuente);
       Lexico();

       void entrada(string fuente);
       string tipoAcad(int tipo);

       int sigSimbolo();
       bool terminado();

};


#endif
