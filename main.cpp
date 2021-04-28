#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

#define TOTAL_BITS 11       ///Definiciones del codigo hamming (33, 7) ejemplo del profe
#define DATA_BITS 7
#define PARIDAD_BITS 4      /// TOTAL_BITS - DATA_BITS
#define REDUNDANCIA 3       ///Cantidad de veces que se repetira el bloque de datos

using namespace std;

bool isValidTrama(const string& data, long long unsigned int dataBits);  ///Validar que la entrada sea binaria
string getHammingCode();                ///Generar el codigo hamming
void getHammingErrors();

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
            //scanf("%d", &op);
            cin >> op;
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
                    getHammingErrors();
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

bool isValidTrama(const string& data, long long unsigned int dataBits) {
    if (data.length() != dataBits) {
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
    int cont, paridadPos(1), inc(2), raw(1);
    while (trama!="*") {
        system("cls");
        cout << "Generar codigo de Hamming" << endl << endl;
        cout << "Ingrese un valor binario de "<< DATA_BITS << " bits, * para salir -> ";
        cin >> trama;
        if (trama=="*") {
            return trama;
        } else if(isValidTrama(trama, DATA_BITS)) {
            cont=0;
            for (int i(1); i<=TOTAL_BITS; ++i) {                            ///Iniciamos en 3 porque los 2 primeros de antemano sabemos que son bits de paridad y para evitar probemas cone el log2
                if (i == paridadPos) {                ///Revisamos si la posicion es potencia de 2, de esta forma sabemos si es un bit de paridad, de ser asi usamos * para marcarlo
                    hammingCode+="*";
                    paridadPos*=2;
                } else {
                    hammingCode+=trama[cont++];
                }
            }
            paridadPos=1;
            for (int x(0); x<PARIDAD_BITS; ++x) {                               ///Ahora vamos a bucar el valor de cada bit de paridad
                cont=0;
                 ///En la matriz sindrome hay una separacion exponencial entre las distancias de los bits que vamos a contar, para eso usamos inc, siempre se empieza en un bit de paridad
                for (int i(paridadPos - 1); i<TOTAL_BITS; i+=inc) {
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
                raw++;
            }
            cout << endl << " -> ";
            for (int i(0); i<REDUNDANCIA; ++i) {
                cout << hammingCode;
            }
            cout << " <- " << endl << endl;
            system("pause");
            return hammingCode;
        } else  {
            cout << endl << "Valor no valido :c" << endl;
            system("pause");
        }
    }
    return "*";
}

void getHammingErrors(){
    string tramaInput(""), blockAux[REDUNDANCIA][TOTAL_BITS], blockFinal(""), blockFinalAux;
    int errorPos(-1), it(0);
    try {
         while (tramaInput!="*") {
            system("cls");
            cout << "Detectar errores" << endl << endl;
            cout << "Ingrese un valor binario de "<< TOTAL_BITS*REDUNDANCIA << " bits, * para salir -> ";   ///Multiplicamos el bloque por la cantidad de veces que repetiremos el bloque
            cin >> tramaInput;
            if (tramaInput=="*") {
                return;
            } else if(isValidTrama(tramaInput, TOTAL_BITS*REDUNDANCIA)) {
                for (int i(0); i<REDUNDANCIA; ++i) {                  ///Acomodamos el input en una matriz que nos permita analisar la redundancia
                    for (int j(0); j<TOTAL_BITS; ++j) {
                        blockAux[i][j]=tramaInput[it++];
                    }
                }

                ///Checamos y corregimos bits de acuerdo a la redundancia



                ///Solucionamos los errores de un bloque, el error, si lo hay se corrige en las tres tramas

                blockFinal+="0";
                for(int i(0); i<TOTAL_BITS; ++i) {
                    blockFinal+=tramaInput[i];
                }

                for (long long unsigned int i = 1; i < blockFinal.length(); ++i) {
                    if (blockFinal[i] == '1') {
                        if (errorPos == -1) {
                            errorPos = i;
                        }
                        else {
                            errorPos = errorPos ^ i;
                        }
                    }
                }

                for (int i(0); i<REDUNDANCIA; ++i) {
                    blockFinal[errorPos] = blockFinal[errorPos] == '1' ? '0' : '1';
                    errorPos+=TOTAL_BITS;
                }

                ///Imprimimos resultados

                for(int i(1); i<=TOTAL_BITS; ++i) {
                    blockFinalAux+=blockFinal[i];
                }

                cout << "Codigo corregido:\n-> ";
                for (int i(0); i<REDUNDANCIA; ++i) {
                    cout << blockFinalAux;
                }
                cout << " <- " << endl;

                system("pause");
                return;
            }
         }
    } catch(...) {
        cout << endl << "Valor no valido :c" << endl;
        system("pause");
    }
    /*
    111101001011111010010111110100101
    */
}
