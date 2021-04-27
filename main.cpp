#include <iostream>
#include <math.h>

#define TOTAL_BITS 11       ///Definiciones del codigo hamming (33, 7) ejemplo del profe
#define DATA_BITS 7
#define PARIDAD_BITS 4      /// TOTAL_BITS - DATA_BITS

using namespace std;

bool isValidTrama(const string& data);  ///Validar que la entrada sea binaria
string getHammingCode();                ///Generar el codigo hamming

int main() {
    string trama;
    bool tramaFlag(false);         ///Bandera para no usar deteccion de errores sin generar Hamming
    int op;
    do {
        system("cls");
        cout << "Codigo de Hamming" << endl << endl;
        cout << "1. Generar codigo de Hamming." << endl;
        cout << "2. Deteccion de errores." << endl;
        cout << "0. Salir." << endl << endl;

        cout << "Selecciona una opcion -> " ;

        try {
            scanf("%d", &op);
            fflush(stdin);
            switch(op) {
            case 1:
                trama = getHammingCode();
                if (trama!="*") {
                    tramaFlag=true;
                }
                break;
            case 2:
                if (tramaFlag) {
                    continue;
                } else {
                    cout << endl << "Primero genere el codigo de Hamming.";
                    getchar();
                }
                break;
            case 0:
                cout << endl << "Gracias por usar este programa!" << endl;
                break;
            default:
                cout << endl << "Opcion no valida, intente de nuevo.";
                system("pause");
            }
        } catch(...) {
            fflush(stdin);
            cout << endl << "Opcion no valida, intente de nuevo.";
            system("pause");
        }
    } while(op != 0);
}

bool isValidTrama(const string& data) {
    if (data.length() != 7) {
        return false;
    }
    for (long long unsigned int i(0); i<data.length(); ++i) {
        if (data[i] != '1' && data[i] != '0') {
            return false;
        }
    }
    return true;
}

string getHammingCode() {
    string trama(""), hammingCode("");
    int cont, paridadPos(1), inc(2), raw(1), init(0);
    while (trama!="*") {
        system("cls");
        cout << "Generar codigo de Hamming" << endl << endl;
        cout << "Ingrese un valor binario de 7 bits, * para salir -> ";
        cin >> trama;
        if (trama=="*") {
            return trama;
        } else if(isValidTrama(trama)) {
            cont=0;
            hammingCode+="**";
            for (int i(3); i<=TOTAL_BITS; ++i) {                            ///Iniciamos en 3 porque los 2 primeros de antemano sabemos que son bits de paridad y para evitar probemas cone el log2
                if (log2(i) - (31- __builtin_clz(i)) == 0) {                ///Revisamos si la posicion es potencia de 2, de esta forma sabemos si es un bit de paridad, de ser asi usamos * para marcarlo
                    hammingCode+="*";
                } else {
                    hammingCode+=trama[cont++];
                }
            }
            for (int x(0); x<PARIDAD_BITS; ++x) {                               ///Ahora vamos a bucar el valor de cada bit de paridad
                cont=0;
                 ///En la matriz sindrome hay una separacion exponencial entre las distancias de los bits que vamos a contar, para eso usamos inc, init nos marcara en donde esta el primer bit a revisar
                 ///en cada fila
                for (int i(init); i<TOTAL_BITS; i+=inc) {
                    cout << init << endl;
                    for (int j(0); j<raw; j++) {            ///de acuerdo al numero de fila sera la cantidad de bits que leeremos antes de cada incremento
                        if (hammingCode[i+j] == '1') {
                            cont++;
                        }
                    }
                }
                if(cont%2==0) {                                 ///Contando la cantidad de 1 en la fila sabremos el valor del bit de paridad, recordemos que el bit de paridad se ubica en potencias de 2
                    hammingCode[paridadPos-1]='0';
                } else {
                    hammingCode[paridadPos-1]='1';
                }
                paridadPos*=2;
                inc*=2;
                init=paridadPos-1;
                raw++;
            }
            cout << endl << " -> " << hammingCode << " <- " << endl << endl;
            system("pause");
            return hammingCode;
        } else  {
            cout << endl << "Valor no valido :c" << endl;
            system("pause");
        }
    }
    return "*";
}
