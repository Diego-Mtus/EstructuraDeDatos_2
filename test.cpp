#include <iostream>
#include <cassert>
#include "tree.hpp"
#include "parser_datos.hpp"

int main()
{
    Tree miArbol;
    std::string rutaXml = "./testds";

    ParserDatos::cargarCarpeta(rutaXml, miArbol);
    // Test de ejemplo hecho solo con "1.xml"
    // Para ejecutar el test se utiliza
    // g++ -std=c++17 test.cpp tree.cpp parser_datos.cpp pugixml.cpp -o test
    // ./test

    // IMPORTANTE: El test busca la carpeta "testds" en el mismo directorio que el ejecutable, 
    // dentro de esa carpeta debe estar el archivo 1.xml

    for(int id : miArbol.preOrder()) {
        miArbol.desplegar_datos(id);
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << miArbol.size() << std::endl;

    miArbol.listar();

    miArbol.borrar_ratings(4.2);

    for(int id : miArbol.preOrder()) {
        miArbol.desplegar_datos(id);
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << miArbol.size() << std::endl;

    miArbol.precursores();

    return 0;
}