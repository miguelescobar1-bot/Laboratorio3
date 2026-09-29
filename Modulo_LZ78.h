#ifndef Modulo_LZ78_H
#define Modulo_LZ78_H

struct EntradaDiccionario {
    int prefijo;
    char caracter;
};

struct ParLZ78 {
    int indice;
    char caracter;
};

ParLZ78* comprimirLZ78(const char* texto, int& cantidadPares);
char* descomprimirLZ78(ParLZ78* pares, int cantidadPares);

#endif