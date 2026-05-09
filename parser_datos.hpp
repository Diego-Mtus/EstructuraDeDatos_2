#pragma once
#include <string>
#include <filesystem>
#include "pugixml.hpp"
#include "tree.hpp"

class ParserDatos {
public:
    static void cargarCarpeta(const std::string& ruta_carpeta, Tree& arbol);
private:
    static void procesarArchivo(const std::string& ruta_archivo, Tree& arbol);
};