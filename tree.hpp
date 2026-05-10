#pragma once

#include <vector>
#include <iostream>

struct DatosLibro {
    int id;
    std::string titulo;
    std::string isbn;
    int anio_publicacion;
    std::string idioma;
    std::string descripcion;
    double rating_promedio;
    int num_paginas;
};

class Tree {
private:
    struct Node {
        DatosLibro data;
        Node* parent;
        std::vector<Node*> children;

        Node(DatosLibro value, Node* p = nullptr);
    };

    Node* rootNode;
    int treeSize;

    void preOrder(Node* node, std::vector<int>& result);
    void postOrder(Node* node, std::vector<int>& result);
    void deleteSubtree(Node* node);
    void borrar_ratings_rec(Node* node, double rating);

public:
    Tree();
    ~Tree();

    bool isEmpty();
    int size();

    Node* root();


    int parent(int id_libro);
    std::vector<int> children(int id_libro);

    bool insert(int id_libro_padre, DatosLibro value);
    bool remove(int id_libro);
    
    Node* search(Node* node, int id_libro);

    std::vector<int> preOrder();
    std::vector<int> postOrder();
    std::vector<int> inOrder();

    void desplegar_datos(Node* node);
    void desplegar_datos(int id_libro);
    
    void listar();
    void borrar_ratings(double rating);
    bool precursores(int id_libro);
    void listar_precursores(); //esta es la que agrege
};