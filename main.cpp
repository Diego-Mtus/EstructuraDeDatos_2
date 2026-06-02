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

    arbolMain.borrar_ratings(4.4);

    arbolMain.precursores();

    arbolMain.listar();
    std::cout << "Tamaño del árbol: " << arbolMain.size() << std::endl;

    return 0;
}

