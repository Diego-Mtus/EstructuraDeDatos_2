# EstructuraDeDatos_2
## Trabajo de: 
	Diego Matus, 20233900249
    Javiera Paris, 2023453170

## Compilacion:
```g++ -std=c++17 test.cpp tree.cpp parser_datos.cpp pugixml.cpp -o libreria_ap```

## Ejecucion: 
	./libreria_ap

## IMPORTANTE
los archivos XML en la carpeta `dataset`, para poder ser leídos en el main. Esta carpeta debe estar ubicada en el mismo directorio que los demas archivos

## Descripcion
Implementacion de un arbol en c++ el cual almacena informacion de 10.000 libros de GoodReads obtenida desde archivos XML
cada libro puede tener libros similares (libro que GoodReads recomienda en cada uno), los cuales se representan como hijos en el arbol

## Estructura del arbol
el nodo raiz tiene id=-1 y no representa ningun libro
cada hijo directo de la raiz es un libro principal del dataset
los hijos de cada libro principal son sus libros similares (<similar_books>)

## Datos almacenados por libro
ID, titulo, ISBN
Año de publicacion
Idioma
Descripcion
Rating promedio
Numero de paginas

## Decisiones de implementacion
Se ignoraron libros similares con año de publicacion 0 (dato no disponible en el XML)
Se ignoraros libros principales sin año de publicacion al evaluar precursores
la libreria PugiXML se uso para parsear los archivos XML