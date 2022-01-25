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
                cad= "-1";
                break;
                
           case TipoSimbolo::IDENTIFICADOR:
                cad= "0";
                break;
                
           case TipoSimbolo::ENTERO:
                cad= "1";
                break;

           case TipoSimbolo::REAL:
                cad= "2";
                break;            

           case TipoSimbolo::CADENA:
                cad= "3";
                break;            

           case TipoSimbolo::TIPO:
                cad= "4";
                break;
                
           case TipoSimbolo::OPADIC:
                cad= "5";
                break;
                
           case TipoSimbolo::OPMULT:
                cad= "6";
                break;
                          
           case TipoSimbolo::OPRELAC:
                cad= "7";
                break;     

           case TipoSimbolo::OPOR:
                cad= "8";
                break;     

           case TipoSimbolo::OPAND:
                cad= "9";
                break;     

           case TipoSimbolo::OPNOT:
                cad= "10";
                break;     

           case TipoSimbolo::OPIGUALDAD:
                cad= "11";
                break;     

           case TipoSimbolo::PYC:
                cad= "12";
                break;     

           case TipoSimbolo::C:
                cad= "13";
                break;     

           case TipoSimbolo::PI:
                cad= "14";
                break;
           
           case TipoSimbolo::PD:
                cad= "15";
                break;     

           case TipoSimbolo::CI:
                cad= "16";
                break;     

           case TipoSimbolo::CD:
                cad= "17";
                break;     

           case TipoSimbolo::IGUAL:
                cad= "18";
                break;     

           case TipoSimbolo::IF:
                cad= "19";
                break;
                
           case TipoSimbolo::WHILE:
                cad= "20";
                break;     

           case TipoSimbolo::RETURN:
                cad= "21";
                break;     

           case TipoSimbolo::ELSE:
                cad= "22";
                break;     

           case TipoSimbolo::PESOS:
                cad= "23";
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
             if ( c == '+' || c=='-') aceptacion(5); 
             else
             if ( c == '*' ||c=='/') aceptacion(6);
             else
             if ( c == '<' || c == '>') sigEstado(4);
             else
             if ( c == '|' ) sigEstado(5);
             else
             if ( c == '&' ) sigEstado(6);
             else
             if ( c == '!' ) sigEstado(7);
             else
             if ( c == ';' ) aceptacion(12);
             else
             if ( c == ',' ) aceptacion(13);
             else
             if ( c == '(' ) aceptacion(14);
             else
             if ( c == ')' ) aceptacion(15);
             else
             if ( c == '}' ) aceptacion(16);
             else
             if ( c == '}' ) aceptacion(17);
             else
             if ( c == '=' ) sigEstado(8);
             else
             if ( c == '$' ) aceptacion(23);
             else
             if (esEspacio(c)) sigCaracter();
             
             break;
       case 1: 
             if (esDigito(c)){
              id=0;
              sigEstado(1);
              }  
             else
             if (esLetra(c)){
			  sigEstado(1);
			  if(simbolo == "int"||simbolo=="float"||simbolo=="void") aceptacion(4);
	             else
	             if (simbolo=="if") aceptacion(19);
	             else
	             if (simbolo=="while") aceptacion(20);
	             else
	             if (simbolo=="return") aceptacion(21);
	             else
	             if (simbolo =="else") aceptacion(22);
	             //else
	             //if(!isalpha(simbolo[]))aceptación(3);
			 }
             else
             
             if (id==0){
             retroceso();	
             this->estado = 0;
             id=0;
              }
             else{
              this->estado = 3; }
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
       case 4:
            if ( c != '=') aceptacion (7);
            else
            if ( c == '=' ) aceptacion(7);
            break;
       case 5:
            if ( c == '|' ) aceptacion(8);
            else
            if ( c != '|' ){
              retroceso();
              this->estado = -1;
            } 
            break;    
       case 6:
            if ( c == '&' ) aceptacion(9);
            else
            if ( c != '&' ){
              retroceso();
              this->estado = -1;           
            }  
            break;
       case 7: 
            if ( c != '=') aceptacion(10);
            else
            if ( c == '=') aceptacion(11);
            break;
       case 8: 
            if ( c != '=') aceptacion(18);
            else
            if ( c == '=') aceptacion(11);
            break;
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
              tipo= TipoSimbolo::CADENA; 
              break; 
         case 4:
              tipo= TipoSimbolo::TIPO; 
              break;        
         case 5:
              tipo= TipoSimbolo::OPADIC; 
              break;
         case 6:
              tipo= TipoSimbolo::OPMULT; 
              break;     
         case 7:
              tipo= TipoSimbolo::OPRELAC; 
              break;     
         case 8:
              tipo= TipoSimbolo::OPOR; 
              break; 
         case 9:
              tipo= TipoSimbolo::OPAND; 
              break;   
         case 10:
              tipo= TipoSimbolo::OPNOT; 
              break; 
         case 11:
              tipo= TipoSimbolo::OPIGUALDAD; 
              break;        
         case 12:
              tipo= TipoSimbolo::PYC; 
              break;
         case 13:
              tipo= TipoSimbolo::C; 
              break; 
         case 14:
              tipo= TipoSimbolo::PI; 
              break;     
         case 15:
              tipo= TipoSimbolo::PD; 
              break;     
         case 16:
              tipo= TipoSimbolo::CI;
              break; 
         case 17:
              tipo= TipoSimbolo::CD; 
              break;   
         case 18:
              tipo= TipoSimbolo::IGUAL; 
              break; 
         case 19:
              tipo= TipoSimbolo::IF; 
              break;        
         case 20:
              tipo= TipoSimbolo::WHILE; 
              break;
         case 21:
              tipo= TipoSimbolo::RETURN; 
              break;   
         case 22:
              tipo= TipoSimbolo::ELSE; 
              break;
         case 23:
              tipo= TipoSimbolo::PESOS; 
              break;               
        dafault:                 
              tipo= TipoSimbolo::ERROR; 
      }
    }  		
	return tipo;
}

 char Lexico::sigCaracter(){ 
      if (terminado())return '$';
      
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
