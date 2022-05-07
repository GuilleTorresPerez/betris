#include "betris.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <windows.h>

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;
        }
    }
}

void mostrarCasilla(const int codigoDeColor) {
    cout << "\033[" << codigoDeColor << "m" << " " << "\033[0m"; 
}

void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]) {
    for(int i = 0; tablero.nfils; i++) {
        for(int j = 0; tablero.ncols; j++) {
            mostrarCasilla(piezaAColor[vEntrada[tablero.matriz[i][j]]]);
        }
    }
}

/* 

    HAY QUE REEMPLAZARLO CON EL BUENO PORQUE ESTE NO SIRVE PARA LO QUE SE PRETENDE HACER

    Algoritmo de Backtracking: 
    - Se coge una pieza de las disponibles en un array de entrada
    - Se comprueba si esa pieza cabe en el tablero, en alguna parte
    - Se elimina la pieza del array de entrada
        - Si la pieza no cabe
            - Si se ha comprobado con todas las piezas, o ninguna de las dichas cabe más, se devuelve false y no se prueba más con esa rama
            - Si no se sigue comprobando el resto de las piezas
        - Si la pieza cabe en alguna parte
            - Se actualiza vSalida con la nueva pieza, así como vEntrada
            - Se comprueba si se ha cumplido el objetivo
                - Si se ha cumplido el objetivo se para de buscar y finaliza el programa
                - Si no se ha cumplido el objetivo se sigue buscando con el algoritmo de backtracking, habiendo eliminado la pieza que se ha colocado

    Hay que retirar las piezas usadas de alguna lista, entonces da igual hacer un for con columnas que con piezas, aunque me parece
    más intuitivo con piezas, esto ya lo haces tu como veas

*/

int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo = 0) {

    tpTablero aux = tablero;                                                //Creación tablero auxiliar para casos no exitosos

    int posicion[2];                                                        //

    bool esValido = comprobarEspacio(aux, vEntrada[n], posicion);

    insertarPieza(aux, vEntrada[n], n, posicion);

    mostrarTablero(aux, vEntrada);

    if (retardo == 0) {
        string ignorar;
        cin >> ignorar;
    } else {
        Sleep(retardo * 1000); // Encontrar funcion para hacer retardo
    }

    if (esValido) {
        return buscaSolucion(aux, vEntrada, vSalida, objetivo, n + 1, retardo); // Backtracking
    } else {
        return n; // Objetivo encontrado
    }
}
 
bool comprobarCondicion(const tpTablero &tp, const int objetivo) {
    
    for(int i = 0; i < objetivo; i++) {
        for(int j = 0; j < tp.ncols; j++) {
            if (tp.matriz[i][j] == -1) {
                return false;
            }
        }
    }

    return true;

}

bool comprobarEspacio(const tpTablero &tp, const int nPieza, int posicion[]) {

    const int objetivoY = tp.nfils - tamPiezas[nPieza][0]; // TODO: REDEFINIR VECTOR CON TAMAÑO MINIMO
    const int objetivoX = tp.ncols - tamPiezas[nPieza][1];

    tpPieza pieza = vPiezas[nPieza];

    for (int i = 0; i < objetivoX; i++) {
        for (int j = 0; j < objetivoY; j++) {
            
            posicion[0] = i;
            posicion[1] = j;

            if (comprobarPosicion(tp, pieza, posicion)) {
                return true;
            }
        }
    }

    return false; // Si no se ha encontrado espacio se devuelve falso

}

bool comprobarPosicion(const tpTablero &tp, const tpPieza &pieza, const int posicion[]) {

    for (int i = 0; i < TAMPIEZA; i++) {
        if (tp.matriz[pieza.forma[i][0] + posicion[0]][pieza.forma[i][1] + posicion[1]] != VACIO) {
            return false;
        }
    }

    return true;

}

void insertarPieza(tpTablero &tp, const int nPieza, const int index, const int posicion[]) {
    
    tpPieza pieza = vPiezas[nPieza];

    for (int i = 0; i < TAMPIEZA; i++) {
        const int xPosicion = posicion[0] + pieza.forma[i][0]; // Se almacenan las posiciones de las piezas
        const int yPosicion = posicion[1] + pieza.forma[i][1];

        tp.matriz[xPosicion][yPosicion] = index; // Se cambia la cuadricula a la del color de dicha pieza
    }
}

int main() {
    tpTablero tablero;
    int vEntrada[MAXENTRADA];

    mostrarTablero(tablero, vEntrada);
    
    return 0;
}