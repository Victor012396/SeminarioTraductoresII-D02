#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "lexico.h"
#include "pila.h"

using namespace std;

int tablaR1[5][4] = {
    2,0,0,1,
    0,0,-1,0,
    0,3,0,0,
    4,0,0,0,
    0,0,-2,0
};
int tablaR2[5][4] = {
    2,0,0,1,
    0,0,-1,0,
    0,3,-3,0,
    2,0,0,4,
    0,0,-2,0
};
Pila pila;
Pila memory;
int contadorinterno=0;
Lexico lexico;
vector <string>simbolo;
vector <int>tipo;
int fila, columna, accion;
bool aceptacion = false;
void r1(string c);
void pushR1();
void r2(string c);
string entrada1="hola+mundo";
string entrada2="a+b+c+d+e+f";
void SintacticoReglas(int arreglo2[95][46], string& cadena, string nombreRegla[], string idRegla[], string longRegla[]);
void Rules(int num, Pila& pila, string nombre, Nodo** head);
int main(int argc, char* argv[]) {
    
  //Responde a los dos ejercicios
  r1(entrada1);
  r2(entrada2);
  Lexico lexico;
  Pila pila;
  Sintactico sintactico;

  int tablaSintactico[96][46];
  int num, mat, filas, columnas;
  string idR[52]{}, longR[52]{}, nameR[52]{};
  string cadena1 = "hola+mundo$", cadena2 = "a+b+c+d+e+f$";
  string ejemplo = "int hola;", salida = "", save = "";

  ifstream file("compilador.lr");
  if (!file.is_open()) {
      cout << "Error." << endl;
  } else 
  if (file.is_open()){
      getline(file, save); 
      num = atoi(save.c_str());
      for (int i = 0; i < num; i++) {
          file >> idR[i];
          file >> longR[i];
          file >> nameR[i];
      }
      file >> save;
      file >> save;
      for (filas = 0;filas < 95; filas++) {
          for (columnas = 0;columnas < 46; columnas++) {
              file >> tablaSintactico[filas][columnas];
          }
      }
  }
  file.close();
  sintactico.SintacticoReglas(tablaSintactico, ejemplo, idR, longR, nameR);
  return 0;
}
void r1(string c) {
    int contadorinterno = 0;
  //Se inicia la pila que servirá de buffer
    Pila pila;
  ElementoPila* simbolo; 
  //Se introduce la entrada correspondiente
    lexico.entrada(entrada1);
  //Se aplica el $0
  pila.push(new Terminal("$")); 
  pila.push(new Estado("0")); 
  //Se empieza a recorrer la entrada
    lexico.sigSimbolo();
    //cout<<lexico.simbolo;

  
  simbolo=pila.top();
  fila = stoi(simbolo->regresar()); 
    columna=lexico.tipo;
    accion=tablaR1[fila][columna];
    //Se muestan los datos de la pila
    pila.muestra();
    cout<<"entrada: "<<lexico.simbolo<<endl;

    //contadorinterno++;
    //cout<< endl;
  //Basados en la regla de la tabla, se hace el recorrido por posiciones que no tienen E
    cout<<"accion: "<<accion<<endl;
    //lexico.sigSimbolo();
    //if(accion>0){
        //pushR1();
      while(contadorinterno!=3) {
      pila.push(new Terminal(lexico.simbolo));
      pila.push(new Estado(to_string(accion))); 
        lexico.sigSimbolo();
        
      simbolo=pila.top();
      fila = stoi(simbolo->regresar()); 
        columna=lexico.tipo;
        accion=tablaR1[fila][columna];
        
        pila.muestra();
        cout<<"entrada: "<<lexico.simbolo<<endl;
        cout<<"accion: "<<accion<<endl;
      contadorinterno++;
      }
    //}
  //En base a las acciones efectuadas se empiezan a hacer eliminaciones para completar el proceso
    if(accion<0){
        for(int i=0;i<6;i++){
            pila.pop();
        }
    }
    if(accion==0)
      cout << "Error"<<endl;
    else{
        pila.muestra(); 
      simbolo=pila.top(); 
      fila = stoi(simbolo->regresar()); 
        columna=3;
        accion=tablaR1[fila][columna];
      
        pila.push(new Noterminal("E"));
        pila.push(new Estado(to_string(accion)));
        pila.muestra();
      
        cout<<"entrada: "<<lexico.simbolo<<endl;
        cout<<"accion: "<<accion<<endl;
      
      simbolo=pila.top(); 
      fila = stoi(simbolo->regresar()); 
        columna=lexico.tipo;
        accion=tablaR1[fila][columna];
  }
    pila.muestra();
    cout<<"entrada: "<<lexico.simbolo<<endl;
    cout<<"accion: "<<accion<<endl;
  
    aceptacion=accion==-1;
    if(aceptacion)
        cout<<"Aceptacion"<<endl;
}


void Sintactico::SintacticoReglas(int tablaSintactico[96][46], string& ejemplo, string idR[], string longR[], string nameR[]){
    int fila, columna, accion = 1, nterm = 0;
    int contador = 0;
    string nameA;
    Pila pila;
    ElementoPila* simbolo;
    Lexico lexico;
    lexico.entrada(ejemplo);
    //Se aplica el $0
    pila.push(new Terminal("$")); 
    pila.push(new Estado("0")); 
    list<Nodo> lista;
    Nodo* actual = NULL;

    while(accion != -1) {
        //lexico.sigSimbolo();
        //if(accion>0){
        //pushR1();
        if (contador == 0){
            contador = 0;
            //Se empieza a recorrer la entrada
            lexico.sigSimbolo(); 
        }

        simbolo = pila.top(); 
        fila = stoi(simbolo->regresar());
        columna = lexico.tipo; 
        accion = tablaSintactico[fila][columna]; 
        //Se muestan los datos de la pila

        if(accion > 0){
            contador = 0;
            pila.muestra(); 
            cout << "Entrada: " << lexico.simbolo << endl;
            //contadorinterno++;
            //cout<< endl;
            cout << "Accion: " << accion << endl;
            pila.push(new Terminal(lexico.simbolo)); 
            pila.push(new Estado(to_string(accion))); 
            pila.muestra(); 
        }
        else if(accion < 0 && accion != -1){
            int longA = 0;
           contador = 1;
            nterm++;
            cout << "Entrada: " << lexico.simbolo << endl;
            cout << "Accion: " << accion << endl;
            accion = abs(accion);
            longA = stoi(longR[accion - 2]);
            nameA = nameR[accion - 2];
            // cout << longA;
            Rules(accion, pila, nameA, &actual);

            pila.muestra();
            simbolo = pila.top();
            fila = stoi(simbolo->regresar());
            columna = stoi(idR[accion - 2]);
            pila.push(new Noterminal(actual));
            pila.muestra();
            accion = tablaSintactico[fila][columna];
            //Se muestan los datos de la pila
            pila.push(new Estado(to_string(accion)));
            pila.muestra();
            }
            else{ if (accion == 0){ break; } }
    }
    actual->muestra();
}

Nodo* Sintactico::push(Nodo** head_ref, string data)
{
    Nodo* new_node = new Nodo();
    new_node->simbolo = data;
    new_node->pts = (*head_ref);
    (*head_ref) = new_node;
    return new_node;
}


void r2(string c){
    contadorinterno= 0;
    cout<<endl<<endl<<endl;
  ElementoPila* simbolo;  
  //Se introduce la entrada correspondiente al proceso
    lexico.entrada("a + b + c + d + e + f");
  //Se introduce el $0
  pila.push(new Terminal("$")); 
  pila.push(new Estado("0")); 
  //Se empieza a recorrer la entrada
    lexico.sigSimbolo();
  simbolo = pila.top();
  fila = stoi(simbolo->regresar()); 
    columna=lexico.tipo;
    accion=tablaR2[fila][columna];

  
    pila.muestra();
    cout<<"entrada: "<<lexico.simbolo<<endl;
    cout<<"accion: "<<accion<<endl;
    //Se empiezan a recorrer todas las posiciones
    while(contadorinterno!=16){
    if(accion>0){
      pila.push(new Terminal(lexico.simbolo)); 
      pila.push(new Estado(to_string(accion))); 
        lexico.sigSimbolo();
      simbolo=pila.top(); 
      fila = stoi(simbolo->regresar()); 
        columna=lexico.tipo;
        accion=tablaR2[fila][columna];
        pila.muestra();
        cout<<"entrada: "<<lexico.simbolo<<endl;
        cout<<"accion: "<<accion<<endl; 
    }
    //En base a las acciones definidad se empizan a realizar operaciones específicas
    if(accion<0){
        if(accion==-3)
        
        {
            pila.pop();
            pila.pop();
          simbolo=pila.top(); 
          fila = stoi(simbolo->regresar());
            columna=3; 
          
            accion=tablaR2[fila][columna]; 
          pila.push(new Noterminal("E")); 
          pila.push(new Estado(to_string(accion)));
            pila.muestra();
            cout<<"entrada: "<<lexico.simbolo<<endl;
            cout<<"accion: "<<accion<<endl;
          
        }
        if(accion==4){
            while(accion==4){
              for(int y=0;y<6;y++){
                pila.pop();
              }
          simbolo=pila.top(); 
          fila = stoi(simbolo->regresar()); 
                columna=3;
                accion=tablaR2[fila][columna];
            
              pila.push(new Noterminal("E")); 
              pila.push(new Estado(to_string(accion)));
                pila.muestra();
                cout<<"entrada: "<<lexico.simbolo<<endl;
                cout<<"accion: "<<accion<<endl;
              }
          }
      }
    }
    

    aceptacion=accion==-1;
    if(aceptacion)
        cout<<"Aceptacion"<<endl;

} 

void Sintactico::Rules(int nRegla, Pila& pila, string nameA, Nodo** head)
{
    Nodo* nodo_ = new Nodo();
    switch(nRegla - 1)
    {
        case 1:
            {   R1 *r1 = new R1(pila); 
                r1->simbolo = nameA;
                r1->pts = (*head); (*head) = r1; }
            break;
        case 3:
            {   R3* r3 = new R3(pila); 
                r3->simbolo = nameA;
                r3->pts = (*head); (*head) = r3;
            }
            break;
        case 4:
            {   R4* r4 = new R4(pila); 
                r4->simbolo = nameA;
                r4->pts = (*head); (*head) = r4;
            }
            break;
        case 5:
            {   R5* r5 = new R5(pila); 
                r5->simbolo = nameA;
                r5->pts = (*head); (*head) = r5;
                break;
            }
        case 6:
            {   R6* r6 = new R6(pila); 
                r6->simbolo = nameA;
                r6->pts = (*head); (*head) = r6;
                break;
            }
        case 8:
            {   R8* r8 = new R8(pila); 
                r8->simbolo = nameA;
                r8->pts = (*head); (*head) = r8;
                break;
            }
        case 9:
            {   R9* r9 = new R9(pila); 
                r9->simbolo = nameA;
                r9->pts = (*head); (*head) = r9;
                break;
            }

        case 11:
            {   R11* r11 = new R11(pila); 
                r11->simbolo = nameA;
                r11->pts = (*head); (*head) = r11;
                break;
            }
        case 13:
            {   R13* r13 = new R13(pila); 
                r13->simbolo = nameA;
                r13->pts = (*head); (*head) = r13;
                break;
            }

        case 14:
            {   R14* r14 = new R14(pila); 
                r14->simbolo = nameA;
                r14->pts = (*head); (*head) = r14;
                break;
            }
        case 16:
            {   R16* r16 = new R16(pila); 
                r16->simbolo = nameA;
                r16->pts = (*head); (head) = r16;
                break;
            }
        case 17:
            {   R17* r17 = new R17(pila);
                r17->simbolo = nameA;
                r17->pts = (*head);
                (*head) = r17;
                break;
            }
        case 18:
            {   R18* r18 = new R18(pila); 
                r18->simbolo = nameA;
                r18->pts = (*head); (*head) = r18;
                break;
            }
        case 20:
            {   R20* r20 = new R20(pila); 
                r20->simbolo = nameA;
                r20->pts = (*head); (*head) = r20;
                break;
            }
        case 21:
            {   R21* r21 = new R21(pila); 
                r21->simbolo = nameA;
                r21->pts = (*head); (*head) = r21;
                break;
            }
        case 22:
            {   R22* r22 = new R22(pila); 
                r22->simbolo = nameA;
                r22->pts = (*head); (*head) = r22;
                break;
            }
        case 23:
            {   R23* r23 = new R23(pila); 
                r23->simbolo = nameA;
                r23->pts = (*head); (*head) = r23;
                break;
            }
        case 24:
            {   R24* r24 = new R24(pila); 
                r24->simbolo = nameA;
                r24->pts = (*head); (*head) = r24;
                break;
            }
        case 25:
            {   R25* r25 = new R25(pila); 
                r25->simbolo = nameA;
                r25->pts = (*head); (*head) = r25;
                break;
            }
        case 27:
            {   R27* r27 = new R27(pila); 
                r27->simbolo = nameA;
                r27->pts = (*head); (*head) = r27;
                break;
            }
        case 28:
            {   R28* r28 = new R28(pila); 
                r28->simbolo = nameA;
                r28->pts = (*head); (*head) = r28;
                break;
            }
        case 30:
            {   R30* r30 = new R30(pila); 
                r30->simbolo = nameA;
                r30->pts = (*head); (*head) = r30;
                break;
            }
        case 32:
            {   R32* r32 = new R32(pila); 
                r32->simbolo = nameA;
                r32->pts = (*head); (*head) = r32;
                break;
            }
        case 34:
            {
                R34* r34 = new R34(pila); 
                r34->simbolo = nameA;
                r34->pts = (*head); (*head) = r34;
                break;
            }
        case 35:
            {   R35* r35 = new R35(pila); 
                r35->simbolo = nameA;
                r35->pts = (*head); (*head) = r35;
                break;
            }
        case 36:
            {   R36* r36 = new R36(pila); 
                r36->simbolo = nameA;
                r36->pts = (*head); (*head) = r36;
                break;
            }
        case 37:
            {   R37* r37 = new R37(pila); 
                r37->simbolo = nameA;
                r37->pts = (*head); (*head) = r37;
                break;
            }
        case 38:
            {   R38* r38 = new R38(pila); 
                r38->simbolo = nameA;
                r38->pts = (*head); (*head) = r38;
                break;
            }
        case 39:
            {   R39* r39 = new R39(pila); 
                r39->simbolo = nameA;
                r39->pts = (*head); (*head) = r39;
                break;
            }
        case 40:
            {   R40* r40 = new R40(pila); 
                r40->simbolo = nameA;
                r40->pts = (*head); (*head) = r40;
                break;
            }
        case 41:
            {   R41* r41 = new R41(pila); 
                r41->simbolo = nameA;
                r41->pts = (*head); (*head) = r41;
                break;
            }
        case 42:
            {   R42* r42 = new R42(pila); 
                r42->simbolo = nameA;
                r42->pts = (*head); (*head) = r42;
                break;
            }
        case 43:
            {   R43* r43 = new R43(pila); 
                r43->simbolo = nameA;
                r43->pts = (*head); (*head) = r43;
                break;
            }
        case 44:
            {   R44* r44 = new R44(pila); 
                r44->simbolo = nameA;
                r44->pts = (*head); (*head) = r44;
                break;
            }
        case 45:
            {   R45* r45 = new R45(pila); 
                r45->simbolo = nameA;
                r45->pts = (*head); (*head) = r45;
                break;
            }
        case 46:
            {   R46* r46 = new R46(pila); 
                r46->simbolo = nameA;
                r46->pts = (*head); (*head) = r46;
                break;
            }
        case 47:
            {   R47* r47 = new R47(pila); 
                r47->simbolo = nameA;
                r47->pts = (*head); (*head) = r47;
                break;
            }
        case 48:
            {   R48* r48 = new R48(pila); 
                r48->simbolo = nameA;
                r48->pts = (*head); (*head) = r48;
                break;
            }
        case 49:
            {   R49* r49 = new R49(pila); 
                r49->simbolo = nameA;
                r49->pts = (*head); (*head) = r49;
                break;
            }
        case 50:
            {   R50* r50 = new R50(pila);   
                r50->simbolo = nameA;
                r50->pts = (*head); (*head) = r50;
                break;
            }
        case 51:
            {   R51* r51 = new R51(pila); 
                r51->simbolo = nameA;
                r51->pts = (*head); (*head) = r51;
                break;
            }
        case 52:
            {   R52* r52 = new R52(pila); 
                r52->simbolo = nameA;
                r52->pts = (*head); (*head) = r52;
                break;
            }

        default:
            RR* rr = new RR(); 
            rr->simbolo = name;
            rr->pts = (*head); (*head) = rr;
            break;
    }
}


