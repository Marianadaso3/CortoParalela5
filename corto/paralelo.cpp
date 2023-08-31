#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <omp.h>
#include <chrono>

int main() {
    int numNumbers;

    // Solicitar la cantidad de numeros aleatorios al usuario
    std::cout << "Por favor, ingrese la cantidad de numeros aleatorios a generar: ";
    std::cin >> numNumbers;

    // Comprobación defensiva
    if (numNumbers <= 0) {
        std::cerr << "[ERROR] La cantidad de numeros debe ser un valor positivo." << std::endl;
        return 1;
    }

    // Generar numeros aleatorios y escribirlos en un archivo
    const std::string OUTFILE = "randomResults/random_paralelo.txt";

    std::ofstream outputFile(OUTFILE);

    // Comprobación defensiva
    if (!outputFile) {
        std::cerr << "[ERROR] El archivo de salida no puede abrirse " << OUTFILE << std::endl;
        return 1;
    }

    // Semilla para la generación de numeros aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < numNumbers; i++) {
        int randomNumber = std::rand() % 10000;  // Genera numeros aleatorios entre 0 y 9999
        outputFile << randomNumber << ",";
    }

    // Cerrar el archivo de salida
    outputFile.close();

    std::cout << "[EXITOSO] Se han generado y escrito numeros aleatorios en el archivo " << OUTFILE << std::endl;

    // Leer los numeros desde el archivo y almacenarlos en memoria dinámica
    std::ifstream inputFile(OUTFILE);

    // Comprobación defensiva
    if (!inputFile) {
        std::cerr << "[ERROR] El archivo de entrada no puede abrirse " << OUTFILE << std::endl;
        return 1;
    }

    std::vector<int> numbers;

    int number;
    char comma;

    while (inputFile >> number >> comma) {
        numbers.push_back(number);
    }

    // Cerrar el archivo de entrada
    inputFile.close();

    // Medir el tiempo de inicio
    auto startTime = std::chrono::high_resolution_clock::now();

    // Ordenar los numeros en paralelo
    #pragma omp parallel
    {
        #pragma omp single
        {
            std::sort(numbers.begin(), numbers.end());
        }
    }

    // Medir el tiempo de finalización
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    std::chrono::duration<double> duration = endTime - startTime;
    double elapsedTime = duration.count();

    // Escribir los numeros ordenados en un segundo archivo
    const std::string SORTED_OUTFILE = "sortedResults/sorted_paralelo.txt";
    std::ofstream sortedOutputFile(SORTED_OUTFILE);

    if (!sortedOutputFile) {
        std::cerr << "[ERROR] El archivo de salida no puede abrirse " << SORTED_OUTFILE << std::endl;
        return 1;
    }

    for (int num : numbers) {
        sortedOutputFile << num << ",";
    }

    // Cerrar el archivo de salida
    sortedOutputFile.close();

    std::cout << "[EXITOSO] Los numeros se han clasificado y escrito en el archivo " << SORTED_OUTFILE << std::endl;

    // Imprimir el tiempo de ejecución
    std::cout << "Tiempo de ejecuciOn: " << elapsedTime << " segundos" << std::endl;

    return 0;
}
