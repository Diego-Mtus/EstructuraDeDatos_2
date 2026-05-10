#include <iostream>
#include <cassert>
#include "tree.hpp"
#include "parser_datos.hpp"

int main()
{
    Tree miArbol;
    std::string rutaXml = "./dataset";

    ParserDatos::cargarCarpeta(rutaXml, miArbol);

    // PRUEBA DE BÚSQUEDA
    int idFinal = 142473;
    if (miArbol.search(miArbol.root(), idFinal) != nullptr)
    {
        std::cout << "ID " << idFinal << " encontrado ANTES de borrar." << std::endl;
    }

    // 3. PRUEBA DE PRECURSORES
    int idVisual = 142473;
    std::cout << "Evaluando precursores para ID " << idVisual << ":" << std::endl;
    miArbol.precursores(idVisual);

    miArbol.desplegar_datos(idVisual); // Mostrar datos

    double filtro = 4.6;
    miArbol.borrar_ratings(filtro);
    std::cout << "Nuevo tamaño tras borrar ratings <= 4.6: " << miArbol.size() << std::endl;

    miArbol.listar(); // Listar para verificar que se borraron los nodos correctos

    // Código para encontrar precursores en todo el árbol
    std::cout << "Buscando precursores en el dataset..." << std::endl;
    miArbol.listar_precursores(); //añadi este
    miArbol.desplegar_datos(280111); // Mostrar datos del ID 280111
    return 0;
}