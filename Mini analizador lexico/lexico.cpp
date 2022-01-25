#include "lexico.h"

  Lexico::Lexico(string fuente){
    ind= 0;
    this->fuente= fuente; 
  }

  Lexico::Lexico(){
    ind= 0;
  }

  string Lexico::tipoAcad(int tipo){
         string cad= "";

         switch (tipo){
           case TipoSimbolo::ERROR:
                cad= "-1\tError";
                break;

           case TipoSimbolo::IDENTIFICADOR:
                cad= "0\tIdentificador";
                break;

           case TipoSimbolo::ENTERO:
                cad= "1\tNumero Entero";
                break;

           case TipoSimbolo::REAL:
                cad= "2\tNumero Real";
                break;

           case TipoSimbolo::OPADIC:
                cad= "5\tOperador de adicion";
                break;

           case TipoSimbolo::OPMULT:
                cad= "6\tOperador de multiplicacion";
                break;

           case TipoSimbolo::PESOS:
                cad= "23\tFin del analisis";
                break;
         }

         return cad;
  }

  void Lexico::entrada(string fuente){
       ind= 0;
      this->fuente= fuente;
  }

int Lexico::sigSimbolo(){ 

    estado=0;
    continua= true;
    simbolo= "";


    while (continua){
      c= sigCaracter(); 

      switch (estado){ 
        case 0:
             if (esLetra(c)) sigEstado(1);
             else
             if (esDigito(c)) sigEstado(2);
             else
             if ( c == '+' || c=='-') aceptacion(3);
             else
              if ( c == '*' ) aceptacion(4);
             else
              if ( c == '$' ) aceptacion(5);
             break;
       case 1: 
             if (esDigito(c)) sigEstado(1);
             else
             if (esLetra(c)) sigEstado(1);
             else{
               retroceso();
               this->estado = 0; 
             }
             break;
       case 2: 
             if (esDigito(c)) sigEstado(2);
             else
             if (c != '.' ){
               retroceso();
               this->estado = 1; 
             }
             else
             if (c == '.') sigEstado(3); 
             break;
       case 3: 
             if (esDigito(c)) sigEstado(3);
             else
             if (!esDigito(c)){
               retroceso();
               this->estado = 2;
             }
             break;
      }

   }

      switch (estado){
         case 0:
              tipo= TipoSimbolo::IDENTIFICADOR; 
              break;
         case 1:
              tipo= TipoSimbolo::ENTERO; 
              break;
         case 2:
              tipo= TipoSimbolo::REAL; 
              break;
         case 3:
              tipo= TipoSimbolo::OPADIC; 
              break;
         case 4:
              tipo= TipoSimbolo::OPMULT; 
              break;
         case 5:
              cout << endl;
              tipo= TipoSimbolo::PESOS; 
              break;
        dafault:
              tipo= TipoSimbolo::ERROR; 
      }

	return tipo;
}

 char Lexico::sigCaracter(){ 
      if (terminado()) return '$';

      return fuente[ind++];
 }

  void Lexico::sigEstado(int estado){ 
       this->estado= estado;
       simbolo+= c;
  }

  void Lexico::aceptacion(int estado){
       sigEstado(estado);
       continua= false;
  }

  bool Lexico::terminado(){
         return ind >= fuente.length();
  }

   bool Lexico::esLetra(char c){
        return isalpha(c) || c=='_';
   }


   bool Lexico::esDigito(char c){ 
        return isdigit(c);
   }

   bool Lexico::esEspacio(char c){ 
        return c== ' ' || c== '\t';
   }


   void Lexico::retroceso(){
      if ( c != '$') ind--;
        continua= false;
    }
