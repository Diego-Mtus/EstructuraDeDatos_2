#include <iostream>
#include <filesystem>
#include "tree.hpp"
#include "parser_datos.hpp"

int main()
{

    // NO BORRAR, es para cargar el archivo.
    Tree arbol;
    std::string ruta_carpeta = "./dataset";
    try {
        ParserDatos::cargarCarpeta(ruta_carpeta, arbol);
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar datos: " << e.what() << std::endl;
        return 1;
    }

    // De aquí en adelante meter funciones para probar

    return 0;
}