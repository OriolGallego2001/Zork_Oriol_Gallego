// Zork.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "world.h"
int main()
{
    world* w = new world();

    while (true) {
        std::string input;

        std::cout << "Enter a string (one to three substrings separated by spaces, Enter to exit): ";
        std::getline(std::cin, input);

        // Check if the input is empty (Enter was pressed)
        if (input.empty()) {
            break; // Exit the loop if Enter was pressed
        }

        // Use a stringstream to parse the input
        if (!w->parse(input.c_str())) {
            std::cout << "Wrong input format or action" << std::endl;
        }
        
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
