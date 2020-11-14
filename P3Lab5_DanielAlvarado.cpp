/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   P3Lab5_DanielAlvarado.cpp
 * Author: dalva
 *
 * Created on November 13, 2020, 12:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

//Prototipos
int menu();
int** genMatrizManual(int, int);
int** genMatrizAuto(int, int);
void freeHeapVector();
void imprimirMatriz();
bool sumarMatrices(string);
bool multMatrices(string);
bool restaMatrices(string);
int** crearArraySuma(int , int);
void printSinglMatrix(int**, int, int);

/*
 * 
 */

//variables de clase
vector<int**> matricesVector;
vector<int> filasMatrices;
vector<int> columnasMatrices;
vector<string> operaciones;
vector<int**> matrizTemp;

int main(int argc, char** argv) {

   

    int opcion = 0;

    while (opcion != 4) {

        switch ((opcion = menu())) {

            case 1:
            {
                //generacion manual de matriz
                cout << "Ingreso Manual de matriz" << endl << endl;

                int filas = 0;
                int columnas = 0;

                cout << "Ingrese las filas de la nueva matriz: ";
                cin >> filas;
                cout << endl;

                while (filas < 1) {
                    cout << "Ingrese un size valido: ";
                    cin >> filas;
                    cout << endl;
                }

                cout << "Ingrese las columnas de la matriz: ";
                cin >> columnas;
                cout << endl;

                while (columnas < 1) {
                    cout << "Ingrese un valor valido: ";
                    cin >> columnas;
                    cout << endl;
                }

                int** matriz = NULL;

                //llamado a metodo generador de matrices manuales
                matriz = genMatrizManual(filas, columnas);

                matricesVector.push_back(matriz);
                filasMatrices.push_back(filas);
                columnasMatrices.push_back(columnas);

                cout << "La matriz ha sido guardada exitosamente" << endl << endl;

                imprimirMatriz();
                break;

            }
            case 2:
            {
                //generacion de matriz automatica
                cout << "Ingreso automatico de matriz" << endl << endl;

                int filas = 0;
                int columnas = 0;

                cout << "Ingrese las filas de la nueva matriz: ";
                cin >> filas;
                cout << endl;

                while (filas < 1) {
                    cout << "Ingrese un size valido: ";
                    cin >> filas;
                    cout << endl;
                }

                cout << "Ingrese las columnas de la matriz: ";
                cin >> columnas;
                cout << endl;

                while (columnas < 1) {
                    cout << "Ingrese un valor valido: ";
                    cin >> columnas;
                    cout << endl;
                }

                int** matriz = NULL;

                //llamado a metodo generador de matrices manuales
                matriz = genMatrizAuto(filas, columnas);

                matricesVector.push_back(matriz);
                filasMatrices.push_back(filas);
                columnasMatrices.push_back(columnas);

                cout << "La matriz ha sido guardada exitosamente" << endl << endl;

                imprimirMatriz();

                break;

            }
            case 3:
            {
                //solucion 
                cout << "Operaciones con las matrices" << endl;

                string operacion = "";
                
                cout << "Estas son todas las matrices generadas" << endl;
                imprimirMatriz();

                cout << "Ingrese la operacion que desea realizar: ";
                cin >> operacion;
                cout << endl;


                for (int i = 0; i < operacion.length(); i++) {

                    char letter = operacion[i];

                    if (letter == '*') {
                        string calc = "";
                        calc += operacion[i-1] + operacion[i] + operacion[i+1];

                        operaciones.push_back(calc);
                    }
                }

                for (int i = 0; i < operacion.length(); i++) {

                    char letter = operacion[i];

                    if (letter == '+') {
                        string calc = "";
                        calc += operacion[i-1] + operacion[i] + operacion[i-1];

                        operaciones.push_back(calc);
                    }

                }

                for (int i = 0; i < operaciones.size(); i++) {

                    char letter = operacion[i];

                    if (letter == '-') {

                        string calc = "";
                        calc += operacion[i-1] + operacion[i] + operacion[i-1];

                        operaciones.push_back(calc);
                    }
                }

                bool terminoCalculo = false;
                bool result = false;
                while (!terminoCalculo) {

                    for (int i = 0; i < operaciones.size(); i++) {

                        string calc = operaciones.at(i);

                        if (calc.find('*') == true) {
                            
                            result = multMatrices(calc);

                            if(result == false){
                                terminoCalculo = true;
                            }

                        } else if (calc.find('+') == true) {
                            result = sumarMatrices(calc);
                            
                            if(result == false){
                                terminoCalculo = true;
                            }
                           
                        } else if (calc.find('-') == true) {\
                            //resta
                            
                            result = restaMatrices(calc);
                            
                            
                            if(result == false){
                                terminoCalculo = true;
                            }
                            
                            
                        }
                    }


                }

                break;

            }
            case 4:
            {
                freeHeapVector();
                cout << "Salio del programa... " << endl;

                break;
            }

        }
    }


    return 0;
}

//multiplica 2 matrices si fila de 1 es igual a columna de otra
bool multMatrices(string calc){
    
    int matriz = calc[0];
    int matriz2 = calc[2];
    
    if(matriz >= matricesVector.size() || matriz2 >= matricesVector.size()){
        cout << "Una de las matrices no existe en el vector" << endl;
        
        return false;
    }else{
        
        
        if(columnasMatrices.at(matriz) == filasMatrices.at(matriz2)){
            
            int fila = filasMatrices.at(matriz);
            int columna = columnasMatrices.at(matriz);
            int fila2 = filasMatrices.at(matriz2);
            int columna2 = columnasMatrices.at(matriz2);
            
            int** matrix = matricesVector.at(matriz);
            int** matrix2 = matricesVector.at(matriz2);
            
            int** multMatriz = crearArraySuma(columna, fila2);
            
            
            for(int i = 0; i < columna; i++){
                for(int j = 0; j < fila2; j++){
                    
                    int result = 0;
                    
                    for(int k = 0; k < columna; k++){
                        result += matrix[i][k] * matrix2[k][i];
                    }
                    
                    multMatriz[i][j] = result;
                }
            }
            
            cout << "Este es el resultado: ";
            printSinglMatrix(multMatriz, columna, fila2);
            
            matricesVector.push_back(multMatriz);
            return true;
            
        }else{
            cout << "Las matrices no tienen las dimensiones apropiadas" << endl;
            return false;
        }
    }
    
}


//resta dos matrices dadas si sus tam son iguales
bool restaMatrices(string calc){
    
    int matriz = calc[0];
    int matriz2 = calc[2];
    
    if(matriz > matricesVector.size() || matriz2 > matricesVector.size()){
        cout << "Las matrices ingresadas no son correctas" << endl;
        return false;
    }else{
        
        if(filasMatrices.at(matriz) == filasMatrices.at(matriz2) 
                && columnasMatrices.at(matriz) == columnasMatrices.at(matriz2)){
            
            
            int fila = filasMatrices.at(matriz);
            int columna = columnasMatrices.at(matriz);
            
            int** matrix = matricesVector.at(matriz);
            int** matrix2 = matricesVector.at(matriz2);
            
            int** restMatrices = NULL;
            restMatrices = crearArraySuma(fila, columna);
            
            for(int i = 0; i < fila ; i++){
                for(int j = 0; j < columna ; j++){
                    
                    int num = (-1 * matrix2[i][j]);
                    restMatrices[i][j] = matrix[i][j] + num;
                }
            }
            
            cout << "Este es el resultado: ";
            printSinglMatrix(restMatrices, fila, columna);
            
            
            matricesVector.push_back(restMatrices);
            
            
            return true;
            
        }else{
            cout << "Las matrices no son del mismo tam..." << endl; 
            return false;
        }
    }
}

//crea una matriz vacia de enteros
int** crearArraySuma(int fila, int columna){
    
    int** matrix = NULL;
    matrix = new int* [fila];
    
    for(int i = 0; i < fila; i++){
        matrix[i] = new int [columna];
    }
    
    return matrix;
}


//suma dos matrices dadas si su tam es igual

bool sumarMatrices(string calc) {

    int matriz = calc[0];
    int matriz2 = calc[2];


    if (matriz > matricesVector.size() || matriz2 > matricesVector.size()) {
        cout << "Las matrices ingresadas no existen en el vector" << endl;
        return false;
    } else {
        
        if (filasMatrices.at(matriz) == filasMatrices.at(matriz2)
                && columnasMatrices.at(matriz) == columnasMatrices.at(matriz2)) {

            int** matrizSuma = NULL;
            int fila = filasMatrices.at(matriz);
            int columna = columnasMatrices.at(matriz);
            
            int** matrix = matricesVector.at(matriz);
            int** matrix2 = matricesVector.at(matriz2);
            
            matrizSuma = crearArraySuma(fila, columna);
            
            
            for(int i = 0; i < fila; i++){
                for(int j = 0; j < columna; j++){
                    
                    matrizSuma[i][j] = matrix[i][j] + matrix2[i][j];
                }
            }

            matricesVector.push_back(matrizSuma);
            
            cout << "Este es el resultado: " << endl;
            printSinglMatrix(matrizSuma, fila, columna);
            
            return true;

        } else {
            cout << "Las dimensiones delas matrices no son iguales...";
            return false;
        }

    }

}


//libera la memoria del vector de matrices

void freeHeapVector() {

    for (int i = 0; i < matricesVector.size(); i++) {

        int** &matriz = matricesVector.at(i);


        for (int j = 0; j < filasMatrices.at(i); j++) {
            delete[] matriz[j];
        }

        delete[] matriz;

        matriz = NULL;
    }

    matricesVector.clear();
}


//genera una matriz aleatoria de tam n * m -50 a 50

int** genMatrizAuto(int filas, int columnas) {

    srand(time(0));

    int** matriz = NULL;
    matriz = new int* [filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int [columnas];
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {

            matriz[i][j] = 1 + (rand() % 101 - 49) ;
        }
    }

    return matriz;

}

//genera una matriz llenada por el usuario

int** genMatrizManual(int filas, int columnas) {

    int** matriz = NULL;

    matriz = new int* [filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int [columnas];
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {

            cout << "Ingrese la posicion: " << i << ", " << j << endl;
            cin >> matriz[i][j];
        }
    }

    return matriz;
}

//imprime solo 1 matriz
void printSinglMatrix(int** matrix, int fila, int columna){
    
    for(int i = 0; i < fila; i++){
        for(int j = 0; j < columna; j++){
            cout << "[" << matrix[i][j] << "] \t";
        }
        cout << endl;
    }
    
    cout << endl << endl;
}

//imprime todas las matrices en el vector

void imprimirMatriz() {

    for (int i = 0; i < matricesVector.size(); i++) {

        int fila = filasMatrices.at(i);
        int columna = columnasMatrices.at(i);
        int** matriz = matricesVector.at(i);

        cout << "Matriz #" << i << endl;

        for (int j = 0; j < fila; j++) {
            for (int k = 0; k < columna; k++) {
                cout << "[" << matriz[j][k] << "]\t";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}

//menu que valida el ingreso de la opcion del usuario

int menu() {

    int opcion = 0;

    do {

        cout << "       Menu        " << endl
                << "1. Ingresar Matriz" << endl
                << "2. Generar Matriz" << endl
                << "3. Realizar Operaciones entre Matrices" << endl
                << "4. Salir" << endl
                << "Ingrese una opcion: ";

        cin >> opcion;
        cout << endl;

        if (opcion > 4 || opcion < 1) {
            cout << "La opcion ingresada no es valida intente de nuevo... \n\n";
        }

    } while (opcion > 4 || opcion < 1);

    return opcion;
}
