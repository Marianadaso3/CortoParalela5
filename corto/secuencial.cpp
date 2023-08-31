/*
Corto ------------------> De manera secuencial
Puntos que debe hacer:
- Pedir como parametro la cantidad de numeros aleatorios que quiere que genere
- Generar los numeros aleatorios y guardarlos en un archivo
- Tomar el arhcivo con los dumeros alearorios y que los sortee 
- Devolver los numeros aleatorios sorteados en un archivo
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono> // Incluir la biblioteca chrono para medir el tiempo

int main() {
    int numNumbers;

    // Solicitar la cantidad de numeros aleatorios al usuario
    std::cout << "Ingrese la cantidad de numeros aleatorios a generar: ";
    std::cin >> numNumbers;

    // Programacion defensiva
    if (numNumbers <= 0) {
        std::cerr << "[ERROR] La cantidad de numeros debe ser un valor positivo." << std::endl;
        return 1;
    }

    // Generar numeros aleatorios y escribirlos en un archivo
    const std::string OUTFILE = "randomResults/random_secuencial.txt";

    std::ofstream outputFile(OUTFILE);

    if (!outputFile) {
        std::cerr << "[ERROR] El archivo de salida no puede abrirse" << OUTFILE << std::endl;
        return 1;
    }

    // Semilla para la generación de numeros aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < numNumbers; i++) {
        int randomNumber = std::rand() % 1000;  // Genera numeros aleatorios entre 0 y 999
        outputFile << randomNumber << ",";
    }

    // Cerrar el archivo de salida
    outputFile.close();

    std::cout << "[EXITOSO] Se han generado y escrito numeros aleatorios en el archivo " << OUTFILE << std::endl;

    // Medir el tiempo de inicio
    auto startTime = std::chrono::high_resolution_clock::now();

    // Leer los numeros desde el archivo y almacenarlos en un arreglo dinámico
    std::ifstream inputFile(OUTFILE);

    if (!inputFile) {
        std::cerr << "[ERROR] El archivo de entrada no puede abrirse " << OUTFILE << std::endl;
        return 1;
    }

    int* numbers = nullptr;  // Puntero al arreglo dinámico
    int currentSize = 0;     // Tamaño actual del arreglo

    int number;
    char comma;

    while (inputFile >> number >> comma) {
        int* newNumbers = new int[currentSize + 1];  // Crear un nuevo arreglo con un elemento más

        // Copiar los numeros existentes al nuevo arreglo
        for (int i = 0; i < currentSize; i++) {
            newNumbers[i] = numbers[i];
        }

        // Agregar el nuevo número al final del arreglo
        newNumbers[currentSize] = number;

        // Liberar la memoria del arreglo anterior (si existe)
        delete[] numbers;

        // Actualizar el puntero al nuevo arreglo
        numbers = newNumbers;
        currentSize++;
    }

    // Cerrar el archivo de entrada
    inputFile.close();

    // Ordenar los numeros
    std::sort(numbers, numbers + currentSize);

    // Escribir los numeros ordenados en un segundo archivo
    const std::string SORTED_OUTFILE = "sortedResults/sorted_secuencial.txt";
    std::ofstream sortedOutputFile(SORTED_OUTFILE);

    if (!sortedOutputFile) {
        std::cerr << "[ERROR] El archivo de salida no puede abrirse " << SORTED_OUTFILE << std::endl;
        return 1;
    }

    for (int i = 0; i < currentSize; i++) {
        sortedOutputFile << numbers[i] << ",";
    }

    // Cerrar el archivo de salida
    sortedOutputFile.close();

    std::cout << "[EXITOSO] Los numeros se han clasificado y escrito en el archivo " << SORTED_OUTFILE << std::endl;

    // Medir el tiempo de finalización
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    std::chrono::duration<double> duration = endTime - startTime;
    double elapsedTime = duration.count();

    // Imprimir el tiempo de ejecución
    std::cout << "Tiempo de ejecucion: " << elapsedTime << " segundos" << std::endl;

    // Liberar la memoria del arreglo dinámico
    delete[] numbers;

    return 0;
}
