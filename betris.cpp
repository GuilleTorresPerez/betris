#include "betris.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;
        }
    }
}

//Esta la he creado yo para hacerlo más legible
void mostrarCasilla(const int codigoDeColor) {
    cout << "\033[" << codigoDeColor << "m" << " " << "\033[0m";
}

void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]) {
    for(int i = 0; tablero.nfils; i++) {
        for(int j = 0; tablero.ncols; j++) {
            
        }
    }
}

int main() {
    tpTablero tablero;
    int vEntrada[MAXENTRADA];

    mostrarTablero(tablero, vEntrada);
    
    return 0;
}