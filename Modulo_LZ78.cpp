#include "modulo_lz78.h"

int longitudTexto(const char* texto) {
    int len = 0;
    while (texto[len] != '\0') len++;
    return len;
}

int buscarEnDiccionario(EntradaDiccionario* dic, int tam, int prefijo, char c) {
    for (int i = 1; i <= tam; i++) {
        if (dic[i].prefijo == prefijo && dic[i].caracter == c) return i;
    }
    return 0;
}

ParLZ78* comprimirLZ78(const char* texto, int& cantidadPares) {
    int n = longitudTexto(texto);
    EntradaDiccionario* dic = new EntradaDiccionario[n + 1];
    int tamDic = 0;

    ParLZ78* salida = new ParLZ78[n];
    cantidadPares = 0;
    int prefijoActual = 0;

    for (int i = 0; i < n; i++) {
        char c = texto[i];
        int idx = buscarEnDiccionario(dic, tamDic, prefijoActual, c);

        if (idx != 0) {
            prefijoActual = idx;
        } else {
            salida[cantidadPares].indice = prefijoActual;
            salida[cantidadPares].caracter = c;
            cantidadPares++;

            tamDic++;
            dic[tamDic].prefijo = prefijoActual;
            dic[tamDic].caracter = c;
            prefijoActual = 0;
        }
    }

    if (prefijoActual != 0) {
        salida[cantidadPares].indice = prefijoActual;
        salida[cantidadPares].caracter = '\0';
        cantidadPares++;
    }

    delete[] dic;
    return salida;
}

char* descomprimirLZ78(ParLZ78* pares, int cantidadPares) {
    int capMax = cantidadPares * 50 + 1;
    char* textoDescomprimido = new char[capMax];
    int posTexto = 0;

    EntradaDiccionario* dic = new EntradaDiccionario[cantidadPares + 1];
    int tamDic = 0;

    for (int i = 0; i < cantidadPares; i++) {
        int idx = pares[i].indice;
        char c = pares[i].caracter;

        char fraseTemp[200];
        int lenFrase = 0;

        if (c != '\0') fraseTemp[lenFrase++] = c;

        int p = idx;
        while (p > 0) {
            fraseTemp[lenFrase++] = dic[p].caracter;
            p = dic[p].prefijo;
        }

        for (int j = lenFrase - 1; j >= 0; j--) {
            textoDescomprimido[posTexto++] = fraseTemp[j];
        }

        tamDic++;
        dic[tamDic].prefijo = idx;
        dic[tamDic].caracter = c;
    }

    textoDescomprimido[posTexto] = '\0';
    delete[] dic;
    return textoDescomprimido;
}