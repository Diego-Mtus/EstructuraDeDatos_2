#include "parser_datos.hpp"
#include <iostream>

void ParserDatos::cargarCarpeta(const std::string& ruta_carpeta, Tree& arbol) {

    // Se revisa si existe la ruta y si es carpeta.
   if(!std::filesystem::exists(ruta_carpeta) || !std::filesystem::is_directory(ruta_carpeta)) {
        throw std::runtime_error("No es una carpeta válida");
    }

    // Por cada elemento, si es xml se revisa.
    for (const auto& entry : std::filesystem::directory_iterator(ruta_carpeta)) {
        // std::cout << "Procesando archivo: " << entry.path() << std::endl;
        if (entry.path().extension() == ".xml") {
            procesarArchivo(entry.path().string(), arbol);
        }
    }
}



void ParserDatos::procesarArchivo(const std::string& ruta_archivo, Tree& arbol) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(ruta_archivo.c_str());

    if (!result) {
        std::cerr << "Error al cargar el archivo: " << ruta_archivo << std::endl;
        return;
    }

    pugi::xml_node libro = doc.child("GoodreadsResponse").child("book");
    
    DatosLibro datosPrincipal;
    datosPrincipal.id = libro.child("id").text().as_int();
    datosPrincipal.titulo = libro.child("title").text().as_string();
    datosPrincipal.isbn = libro.child("isbn").text().as_string();
    datosPrincipal.anio_publicacion = libro.child("publication_year").text().as_int();
    datosPrincipal.idioma = libro.child("language_code").text().as_string();
    datosPrincipal.descripcion = libro.child("description").text().as_string();
    datosPrincipal.rating_promedio = libro.child("average_rating").text().as_double();

    // Se inserta en el árbol con padre id -1 porque ese es el nodo raíz.
    arbol.insert(-1, datosPrincipal);

    pugi::xml_node similares = libro.child("similar_books");
    for (pugi::xml_node sim : similares.children("book")) {
        DatosLibro similar;
        similar.id = sim.child("id").text().as_int();
        similar.titulo = sim.child("title").text().as_string();
        similar.anio_publicacion = sim.child("publication_year").text().as_int();
        similar.isbn = sim.child("isbn").text().as_string();
        similar.rating_promedio = sim.child("average_rating").text().as_double();
        similar.idioma = "No disponible"; // No viene en el XML de similares
        similar.descripcion = "No disponible"; // No viene en el XML de similares
        
        arbol.insert(datosPrincipal.id, similar);
    }
}