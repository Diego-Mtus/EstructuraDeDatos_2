#include <iostream>
#include <filesystem>
#include "tree.hpp"
#include "parser_datos.hpp"

Tree cargarArbolMain()
{
    Tree arbol;
    std::string ruta_carpeta = "./dataset";
    try
    {
        ParserDatos::cargarCarpeta(ruta_carpeta, arbol);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al cargar datos: " << e.what() << std::endl;
        return Tree(); // Retorna un árbol vacío en caso de error
    }

    return arbol;
}

int main()
{

    Tree arbolMain =  cargarArbolMain();
    // De aquí en adelante meter funciones para probar


    return 0;
}

