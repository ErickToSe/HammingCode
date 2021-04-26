#include <iostream>

#define TOTAL_BITS 33       ///Definiciones del codigo hamming (33, 7) ejemplo del profe
#define DATA_BITS 7
#define PARIDAD_BITS 26

using namespace std;

int main() {
    matrix[PARIDAD_BITS][TOTAL_BITS];

    char op;
    do {
        system("cls");
        cout << "Codigo de Hamming" << endl << endl;
        cout << "1. Generar codigo de Hamming." << endl;
        cout << "2. Deteccion de errores." << endl;
        cout << "0. Salir." << endl << endl;

        cout << "Selecciona una opcion -> " ;

        cin >> op;
        fflush(stdin);

        switch(op) {
        case '1':
            break;
        case '2':
            break;
        case '0':
            cout << endl << "Gracias por usar este programa!" << endl;
            break;
        default:
            cout << endl << "Opcion no valida, intente de nuevo";
            getchar();
        }

    } while(op != '0');
}
