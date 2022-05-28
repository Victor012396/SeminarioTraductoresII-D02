#include "lexico.h"

Lexico::Lexico(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico() {
    ind = 0;
}

string Lexico::tipoAcad(int tipo) {
    string cad = "";

    switch (tipo) {
    case TipoSimbolo::ERROR:
        cad = "Error";
        break;

    case TipoSimbolo::IDENTIFICADOR:
        cad = "0. Identificador";
        texto.push_back(simbolo);
        break;

    case TipoSimbolo::ENTERO:
        cad = "1. Entero";
        break;

    case TipoSimbolo::REAL:
        cad = "2. Real";
        break;

    case TipoSimbolo::CADENA:
        cad = "3. Cadena";
        break;

    case TipoSimbolo::TIPODD:
        cad = "4. Tipo de dato";
        break;

    case TipoSimbolo::OPADIC:
        cad = "5. Operador de adicion";
        texto.push_back(simbolo);
        break;

    case TipoSimbolo::OPMULTIP:
        cad = "6. Operador de multiplicacion";
        break;

    case TipoSimbolo::OPRELAC:
        cad = "7. Operador relacional";
        break;

    case TipoSimbolo::OPOR:
        cad = "8. Operador Or";
        break;

    case TipoSimbolo::OPAND:
        cad = "9. Operador And";
        break;

    case TipoSimbolo::OPNOT:
        cad = "10. Operador Not";
        break;

    case TipoSimbolo::OPIGUALDAD:
        cad = "11. Operador de Igualdad";
        break;

    case TipoSimbolo::PUNTOYCOMA:
        cad = "12. Punto y coma ";
        break;

    case TipoSimbolo::COMA:
        cad = "13. Coma";
        break;

    case TipoSimbolo::PARENTI:
        cad = "14. Parentesis izquierdo";
        break;

    case TipoSimbolo::PARENTD:
        cad = "15. Parentesis derecho";
        break;

    case TipoSimbolo::CORCHETI:
        cad = "16. Corchete izquierdo";
        break;

    case TipoSimbolo::CORCHETD:
        cad = "17. Corchete derecho";
        break;

    case TipoSimbolo::OPIGUAL:
        cad = "18. Operador igual";
        break;

    case TipoSimbolo::IF:
        cad = "19. If";
        break;

    case TipoSimbolo::WHILE:
        cad = "20. While";
        break;

    case TipoSimbolo::RETURN:
        cad = "21. Return";
        break;

    case TipoSimbolo::ELSE:
        cad = "22. Else";
        break;

    case TipoSimbolo::PESOS:
        cad = "23. Fin del analizador lexico";
        break;
    }

    return cad;
}

void Lexico::entrada(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

int Lexico::sigSimbolo() {

    estado = 0;
    continua = true;
    simbolo = "";

    while (continua) {
    c = sigCaracter();
    switch (estado) {
        case 0:
            if (esLetra(c)) sigEstado(1);
            else
            if (esDigito(c)) sigEstado(2);
            else
            if (c == '+' || c == '-') aceptacion(1);
            else
            if (c == '*' || c == '/') aceptacion(6);
            else
            if (c == '<' || c == '>') sigEstado(4);
            else
            if (c == '|') sigEstado(5);
            else
            if (c == '&') sigEstado(6);
            else
            if (c == '!') sigEstado(7);
            else
            if (c == ';') aceptacion(12);
            else
            if (c == ',') aceptacion(13);
            else
            if (c == '(') aceptacion(14);
            else
            if (c == ')') aceptacion(15);
            else
            if (c == '{') aceptacion(16);
            else
            if (c == '}') aceptacion(17);
            else
            if (c == '=') sigEstado(8);
            else
            if (c == '$') aceptacion(2);
            else
            if (esEspacio(c)) this->estado = 0;
                break;
        case 1:
            if (esDigito(c)) {
                id = 1;
                sigEstado(1);
            }
            else
            if (esLetra(c)) {
                sigEstado(1);
                if (simbolo == "int" || simbolo == "float" || simbolo == "void") aceptacion2(4);
                else
                if (simbolo == "if") aceptacion2(19);
                else
                if (simbolo == "while") aceptacion2(20);
                else
                if (simbolo == "return") aceptacion2(21);
                else
                if (simbolo == "else") aceptacion2(22);
            }
            else
            if (id == 1) {
                retroceso();
                this->estado = 0;
                id = 0;
            }
            else {
                aceptacion2(0);    //aqui
                retroceso();
            }
            break;
        case 2:
            if (esDigito(c)) sigEstado(2);
            else
                if (c != '.') {
                    retroceso();
                    this->estado = 5;
                }
                else
                    if (c == '.') sigEstado(3);
            break;
        case 3:
            if (esDigito(c)) sigEstado(3);
            else
                if (!esDigito(c)) {
                    retroceso();
                    this->estado = 23;
                }
            break;
        case 4:
            if (c != '=') {
                retroceso();
                aceptacion2(7);
            }
            else
                if (c == '=') {
                    aceptacion(7);
                }
            break;
        case 5:
            if (c == '|') aceptacion(8);
            else
                if (c != '|') {
                    retroceso();
                    this->estado = -1;
                }
            break;
        case 6:
            if (c == '&') aceptacion(9);
            else
                if (c != '&') {
                    retroceso();
                    this->estado = -1;
                }
            break;
        case 7:
            if (c != '=') {
                retroceso();
                aceptacion2(10);
            }
            else
                if (c == '=') {
                    aceptacion(11);
                    
                }
            break;
        case 8:
            if (c != '=') {
                retroceso();
                aceptacion2(18);
               
            }
            else
                if (c == '=') {
                    aceptacion(11);
                   
                }
            break;
        }
    }
        //Fin del Automata

        switch (estado) {
        case -1:
            tipo = TipoSimbolo::ERROR;
            break;
        case 0:
            tipo = TipoSimbolo::IDENTIFICADOR;
            break;
        case 5:
            tipo = TipoSimbolo::ENTERO;
            break;
        case 23:
            tipo = TipoSimbolo::REAL;
            break;
        case 3:
            tipo = TipoSimbolo::CADENA;
            break;
        case 4:
            tipo = TipoSimbolo::TIPODD;
            break;
        case 1:
            tipo = TipoSimbolo::OPADIC;
            break;
        case 6:
            tipo = TipoSimbolo::OPMULTIP;
            break;
        case 7:
            tipo = TipoSimbolo::OPRELAC;
            break;
        case 8:
            tipo = TipoSimbolo::OPOR;
            break;
        case 9:
            tipo = TipoSimbolo::OPAND;
            break;
        case 10:
            tipo = TipoSimbolo::OPNOT;
            break;
        case 11:
            tipo = TipoSimbolo::OPIGUALDAD;
            break;
        case 12:
            tipo = TipoSimbolo::PUNTOYCOMA;
            break;
        case 13:
            tipo = TipoSimbolo::COMA;
            break;
        case 14:
            tipo = TipoSimbolo::PARENTI;
            break;
        case 15:
            tipo = TipoSimbolo::PARENTD;
            break;
        case 16:
            tipo = TipoSimbolo::CORCHETI;
            break;
        case 17:
            tipo = TipoSimbolo::CORCHETD;
            break;
        case 18:
            tipo = TipoSimbolo::OPIGUAL;
            break;
        case 19:
            tipo = TipoSimbolo::IF;
            break;
        case 20:
            tipo = TipoSimbolo::WHILE;
            break;
        case 21:
            tipo = TipoSimbolo::RETURN;
            break;
        case 22:
            tipo = TipoSimbolo::ELSE;
            break;
        case 2:
            tipo = TipoSimbolo::PESOS;
            break;
        dafault:
            tipo = TipoSimbolo::ERROR;
        }
    
    return tipo;
}

char Lexico::sigCaracter() {
    if (terminado())return '$';

    return fuente[ind++];

}

void Lexico::sigEstado(int estado) {//Checa al inicio los valores
    this->estado = estado;
    simbolo += c;
}

void Lexico::aceptacion(int estado) {
    tipos.push_back(estado);
    sigEstado(estado);
    continua = false;
}

void Lexico::aceptacion2(int estado) {
  tipos.push_back(estado);
    this->estado = estado;
    continua = false;
}

bool Lexico::terminado() {//fin de cadena
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c) {
    return isalpha(c) || c == '_';
}


bool Lexico::esDigito(char c) {
    return isdigit(c);
}

bool Lexico::esEspacio(char c) {
    return c == ' ' || c == '\t';
}

void Lexico::retroceso() {
    if (c != '$') ind--;
    continua = false;
}
