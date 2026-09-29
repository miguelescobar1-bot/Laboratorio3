#include "Encriptacion.h"

unsigned char rotarIzquierda(unsigned char byte, int n) {
    return (byte << n) | (byte >> (8 - n));
}

unsigned char rotarDerecha(unsigned char byte, int n) {
    return (byte >> n) | (byte << (8 - n));
}

void encriptar(unsigned char* datos, int tam, int n, unsigned char claveK) {
    for (int i = 0; i < tam; i++) {
        datos[i] = rotarIzquierda(datos[i], n) ^ claveK;
    }
}

void desencriptar(unsigned char* datos, int tam, int n, unsigned char claveK) {
    for (int i = 0; i < tam; i++) {
        datos[i] = rotarDerecha(datos[i] ^ claveK, n);
    }
}