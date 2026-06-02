#include <iostream>
#include <filesystem>
#include "tree.hpp"
#include "parser_datos.hpp"

int main()
{

    Tree arbolMain;
    std::string rutaXml = "./dataset";
    ParserDatos::cargarCarpeta(rutaXml, arbolMain);

    // ------------------------------------------------
    // De aquí en adelante meter funciones para probar

    std::cout << "Tamaño del árbol inicial: " << arbolMain.size() << std::endl;

    std::cout << "Se borran los libros con rating promedio <= 4.4" << std::endl;

    arbolMain.borrar_ratings(4.4);

    arbolMain.precursores();

    arbolMain.listar();

    std::cout << "Tamaño del árbol: " << arbolMain.size() << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Ahora con un rating más alto: 4.7" << std::endl;

    arbolMain.borrar_ratings(4.7);
    arbolMain.precursores();
    arbolMain.listar();
    std::cout << "Tamaño del árbol: " << arbolMain.size() << std::endl;
    std::cout << "------------------------------" << std::endl;
    for(int id : arbolMain.preOrder()) {
        arbolMain.desplegar_datos(id);
        std::cout << "-----------------------------" << std::endl;
    }

    return 0;
}

