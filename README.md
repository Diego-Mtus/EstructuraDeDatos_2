# Estructura de Datos #2
## Trabajo de: 
	Diego Matus, 2023900249
    Javiera Paris, 2023453170

## Compilacion:
```g++ -std=c++17 main.cpp tree.cpp parser_datos.cpp pugixml.cpp -o main```

## Ejecucion: 
	./main

## IMPORTANTE
Los archivos XML deben estar en la carpeta `dataset` para poder ser leídos en el main. Esta carpeta debe estar ubicada en el mismo directorio que los demas archivos.

## Descripcion
Implementacion de un árbol en c++ el cual almacena informacion de 10.000 libros de GoodReads obtenida desde archivos XML,
cada libro puede tener libros similares (libro que GoodReads recomienda en cada uno), los cuales se representan como hijos en el árbol.

## Estructura del árbol
- El nodo raiz tiene id=-1 y no representa ningun libro.
- Cada hijo directo de la raiz es un libro principal del dataset.
- Los hijos de cada libro principal son sus libros similares (<similar_books>)

## Datos almacenados por libro
ID, titulo, ISBN,
Año de publicacion,
Idioma,
Descripcion,
Rating promedio.


## Decisiones de implementación
- Se ignoraron libros similares con año de publicacion 0 (cuando el dato no está disponible en el XML) al evaluar precursores, esto hará que los libros similares con esta condición no invaliden el estado de precursor.
- Se ignoraros libros principales sin año de publicacion al evaluar precursores
- Se usó la libreria PugiXML para parsear los archivos XML
- Se añadieron ejemplos de outputs obtenidos en pruebas, estos son los archivos `ejemplo_output_main.txt` y `ejemplo_output_test.txt`.
- No se considera el número de páginas porque hay varios libros donde ese dato no está disponible.
