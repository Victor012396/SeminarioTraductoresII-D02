#ifndef _PILA
#define _PILA
#include <list>
#include <iostream>
#include <string>

using namespace std;

/*class Alumno{
    protected:
    string codigo;

    public:
    virtual void muestra(){}
};

class Bachillerato: public Alumno{
    protected:
    string preparatoria;

    public:
    Bachillerato(string codigo, string preparatoria){
        this->codigo= codigo;
        this->preparatoria= preparatoria;
    }
    void muestra(){
        cout << "Alumno Bachillerato" << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Preparatoria: " << preparatoria << endl << endl;
    }
};

class Licenciatura: public Alumno{
    protected:
    string carrera;
    int creditos;

    public:
    Licenciatura(string codigo, string carrera, int creditos){
        this->codigo= codigo;
        this->carrera= carrera;
        this->creditos= creditos;
    }
    void muestra(){
        cout << "Alumno Licenciatura" << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Carrera: " << carrera << endl;
        cout << "Creditos: " << creditos << endl << endl;
    }
};*/
class Nodo{
    public:
        string simbolo;
        Nodo *pts;
        void muestraNodo()
        {
            cout << " ";
        }
        virtual void muestra() {};
};

class ElementoPila{
protected:
    string simbolo;

public:
    virtual void muestra(){}
    virtual string regresar(){ return "0"; }
};

class Terminal: public ElementoPila{
protected:

public:
    Terminal(string simbolo){
        this->simbolo = simbolo;
    }
    void muestra() {
        cout<<simbolo;
    }
    string regresar(){ return simbolo; }
};

class Noterminal: public ElementoPila {
protected:

public:
    Nodo* nodo;
    Noterminal(Nodo* simbolo){
        this->nodo = simbolo;
    }
    void muestra(){
        nodo->muestraNodo();
    }
    Nodo* getNodo(){ return nodo; }
    string regresar(){ return nodo->simbolo; }
};

class Estado: public ElementoPila{
public:
    Estado(string simbolo){
        this->simbolo = simbolo;
    }
    void muestra() {
        cout <<simbolo;
    }
    string regresar(){ return simbolo; }
};

class Pila{
    private:
        list <ElementoPila*> lista;

    public:
        void push(ElementoPila* x);
        ElementoPila* top();
        ElementoPila* pop();
        void muestra();
};

#endif
