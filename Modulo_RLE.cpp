#include "modulo_rle.h"

using namespace std;

string comprimirRLE(string texto) {
    string resultado = "";
    int n = texto.length();

    for (int i = 0; i < n; i++) {
        int contador = 1;
        while (i + 1 < n && texto[i] == texto[i + 1]) {
            contador++;
            i++;
        }
        resultado += to_string(contador) + texto[i];
    }
    return resultado;
}

string descomprimirRLE(string textoComprimido) {
    string resultado = "";
    int n = textoComprimido.length();

    for (int i = 0; i < n; i++) {
        int contador = 0;
        while (i < n && isdigit(textoComprimido[i])) {
            contador = contador * 10 + (textoComprimido[i] - '0');
            i++;
        }
        char caracter = textoComprimido[i];
        for (int j = 0; j < contador; j++) {
            resultado += caracter;
        }
    }
    return resultado;
}