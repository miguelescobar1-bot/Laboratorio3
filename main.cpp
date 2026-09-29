#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "modulo_rle.h"
#include "modulo_lz78.h"
#include "Encriptacion.h"

using namespace std;



string leerArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw runtime_error("Error: No se pudo abrir el archivo de entrada.");
    }
    string contenido = "", linea;
    while (getline(archivo, linea)) {
        contenido += linea + "\n";
    }
    archivo.close();
    if (contenido.empty()) {
        throw runtime_error("Error: El archivo de entrada esta vacio.");
    }
    return contenido;
}

void guardarArchivo(const string& ruta, const string& contenido) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        throw runtime_error("Error: No se pudo escribir en el archivo.");
    }
    archivo << contenido;
    archivo.close();
}

int main() {
    try {
        string rutaEntrada = "entrada.txt";
        string rutaSalida = "salida.txt";

        string textoOriginal = leerArchivo(rutaEntrada);
        cout << " Texto del Documento" << endl;
        cout << textoOriginal << endl;

        int opcion = 0;
        cout << "Seleccione el metodo de compresion:" << endl;
        cout << "1. RLE" << endl;
        cout << "2. LZ78" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail() || (opcion != 1 && opcion != 2)) {
            throw invalid_argument("Error: Opcion invalida.");
        }

        int nRotacion = 3;
        unsigned char claveK = 0x5A;
        string textoFinalRecuperado = "";

        if (opcion == 1) {
            string comprimidoRLE = comprimirRLE(textoOriginal);

            cout << "\nTexto comprimido por RLE: " << comprimidoRLE << endl;

            int tam = comprimidoRLE.length();

            unsigned char* datos = new unsigned char[tam + 1];
            for (int i = 0; i < tam; i++) datos[i] = comprimidoRLE[i];

            encriptar(datos, tam, nRotacion, claveK);
            desencriptar(datos, tam, nRotacion, claveK);

            string desencriptadoStr = "";
            for (int i = 0; i < tam; i++) desencriptadoStr += (char)datos[i];
            delete[] datos;

            textoFinalRecuperado = descomprimirRLE(desencriptadoStr);

        } else if (opcion == 2) {

            int cantidadPares = 0;

            ParLZ78* pares = comprimirLZ78(textoOriginal.c_str(), cantidadPares);

            string comprimidoLZ78Str = "";

            for (int i = 0; i < cantidadPares; i++) {

                comprimidoLZ78Str += to_string(pares[i].indice) + pares[i].caracter;

            }

            cout << "\nTexto comprimido por LZ78: " << comprimidoLZ78Str << endl;


            int tam = cantidadPares * sizeof(ParLZ78);

            unsigned char* datos = new unsigned char[tam];

            ParLZ78* ptrOriginal = (ParLZ78*)datos;

            for (int i = 0; i < cantidadPares; i++) {
                ptrOriginal[i] = pares[i];
            }
            delete[] pares;

            encriptar(datos, tam, nRotacion, claveK);
            desencriptar(datos, tam, nRotacion, claveK);

            ParLZ78* paresDesencriptados = (ParLZ78*)datos;
            char* textoDescomprimido = descomprimirLZ78(paresDesencriptados, cantidadPares);
            textoFinalRecuperado = string(textoDescomprimido);

            delete[] datos;
            delete[] textoDescomprimido;
        }

        guardarArchivo(rutaSalida, textoFinalRecuperado);

        cout << "\nTexto Final" << endl;
        cout << textoFinalRecuperado << endl;

        if (textoOriginal == textoFinalRecuperado) {
            cout << "\nCoincide el texto original." << endl;
        } else {
            cout << "\nNo coinciden." << endl;
        }

    } catch (const exception& e) {
        cerr << "\nExcepcion: " << e.what() << endl;
    }

    return 0;
}