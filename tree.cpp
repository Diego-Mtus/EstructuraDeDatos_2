#include "tree.hpp"
#include <algorithm>
#include <functional>

// Modificación de la implementación de árbol del lab 7
// El nodo raiz es especial y no representa un libro, tendrá id -1.
// Node
Tree::Node::Node(DatosLibro value, Node *p)
{
    data = value;
    parent = p;
}

// Constructor
Tree::Tree()
{
    DatosLibro nodo_base;
    nodo_base.id = -1;
    rootNode = new Node(nodo_base);
    treeSize = 0;
}

Tree::~Tree()
{
    deleteSubtree(rootNode);
}

bool Tree::isEmpty()
{
    return treeSize == 0;
}

int Tree::size()
{
    return treeSize;
}

Tree::Node *Tree::search(Node *node, int id_libro)
{
    if (!node)
        return nullptr;
    if (node->data.id == id_libro)
        return node;

    for (auto child : node->children)
    {
        Node *found = search(child, id_libro);
        if (found)
            return found;
    }
    return nullptr;
}

Tree::Node *Tree::root()
{
    return rootNode;
}

bool Tree::insert(int id_libro_padre, DatosLibro value)
{

    Node *parentNode = search(rootNode, id_libro_padre);
    if (!parentNode)
        return false;

    Node *newNode = new Node(value, parentNode);
    parentNode->children.push_back(newNode);
    treeSize++;
    return true;
}

int Tree::parent(int id_libro)
{
    Node *node = search(rootNode, id_libro);
    if (!node || node == rootNode || node->data.id == -1)
        throw std::runtime_error("No tiene padre");

    return node->parent->data.id;
}

std::vector<int> Tree::children(int id_libro_padre)
{
    Node *node = search(rootNode, id_libro_padre);
    std::vector<int> result;

    if (!node)
        return result;

    for (auto child : node->children)
        result.push_back(child->data.id);

    return result;
}

void Tree::deleteSubtree(Node *node)
{
    if (!node)
        return;
    for (auto child : node->children)
        deleteSubtree(child);

    if (node->data.id != -1)
        treeSize--;
    delete node;
}

bool Tree::remove(int id_libro)
{
    Node *node = search(rootNode, id_libro);
    if (!node)
        return false;

    if (node == rootNode)
    {
        deleteSubtree(rootNode);
        rootNode = nullptr;
        treeSize = 0;
        return true;
    }

    Node *parent = node->parent;
    auto &siblings = parent->children;

    siblings.erase(
        std::remove(siblings.begin(), siblings.end(), node),
        siblings.end());

    deleteSubtree(node);
    return true;
}

void Tree::preOrder(Node *node, std::vector<int> &result)
{
    if (!node)
        return;
    result.push_back(node->data.id);
    for (auto child : node->children)
        preOrder(child, result);
}

std::vector<int> Tree::preOrder()
{
    std::vector<int> result;
    preOrder(rootNode, result);
    return result;
}

void Tree::postOrder(Node *node, std::vector<int> &result)
{
    if (!node)
        return;
    for (auto child : node->children)
        postOrder(child, result);
    result.push_back(node->data.id);
}

std::vector<int> Tree::postOrder()
{
    std::vector<int> result;
    postOrder(rootNode, result);
    return result;
}

std::vector<int> Tree::inOrder()
{
    std::vector<int> result;

    std::function<void(Node *)> inorder = [&](Node *node)
    {
        if (!node)
            return;

        int half = node->children.size() / 2;

        for (int i = 0; i < half; i++)
            inorder(node->children[i]);

        result.push_back(node->data.id);

        for (size_t i = half; i < node->children.size(); i++)
            inorder(node->children[i]);
    };

    inorder(rootNode);
    return result;
}

// listar: Listar los IDs de los libros siguiendo un recorrido preorder.

void Tree::listar()
{
    std::vector<int> ids = preOrder();
    for (int id : ids)
    {
        if (id != -1) // Para no mostrar el nodo raiz
            std::cout << "ID: " << id << std::endl;
    }
}

// borrar_ratings(r): Eliminar del árbol todos los libros con rating promedio menor o igual al parámetro r.

void Tree::borrar_ratings(double rating)
{
    borrar_ratings_rec(rootNode, rating);
}

void Tree::borrar_ratings_rec(Node *node, double rating)
{
    if (!node)
        return;

    // Iteramos por los hijos manualmente porque se va a modificar el vector mientas se itera
    auto it = node->children.begin();
    while (it != node->children.end())
    {
        if ((*it)->data.rating_promedio <= rating)
        { // Se borra el nodo e hijos si el rating es menor o igual

            deleteSubtree(*it);
            it = node->children.erase(it);
        }
        else
        { // Si no, se revisan los hijos recursivamente
            borrar_ratings_rec(*it, rating);
            ++it;
        }
    }
}

// precursores(id): Listar los IDs de libros que sólo tengan libros similares publicados
// en años posteriores (Por ejemplo, si un libro con ID 001 fue publicado el año 2000 y todos
// sus libros similares fueron publicados luego del año 2000, entonces el ID 001 debe ser reportado)

// voy a modificar esta funcion porsiaca
bool Tree::precursor_por_id(int id_libro)
{
    Node *node = search(rootNode, id_libro);
    if (!node)
    {
        return false;
    }

    if (node->children.empty())
    {
        return false; // No tiene hijos, no es precursor.
    }

    int anio_padre = node->data.anio_publicacion;

    // Si el año del padre es 0, asumimos que es el nodo raíz o un nodo sin año válido, por lo que no puede ser precursor.
    if (anio_padre == 0)
    {
        return false;
    }
    bool esPrecursor = true;

    // Iteramos por los hijos, si alguno tiene un año de publicación menor o igual al padre, entonces el padre no es precursor.
    for (auto child : node->children)
    {

        if(child->data.anio_publicacion == 0) {
            continue; // Si el hijo no tiene año válido, lo ignoramos para la comparación.
        }
        
        if (child->data.anio_publicacion <= anio_padre)
        {
            esPrecursor = false;
            break;
        }
    }

    if (esPrecursor)
    {
        std::cout << "El ID " << node->data.id << " es un precursor." << std::endl;
    }
    return esPrecursor;
}

// Para ver si los datos se cargaron bien.
void Tree::desplegar_datos(Node *node)
{
    if (!node)
        return;

    if(node->data.id == -1) {

        return;
    }

    std::cout << "ID: " << node->data.id << std::endl;
    std::cout << "Título: " << node->data.titulo << std::endl;
    std::cout << "ISBN: " << node->data.isbn << std::endl;
    std::cout << "Año de Publicación: " << node->data.anio_publicacion << std::endl;
    std::cout << "Idioma: " << node->data.idioma << std::endl;
    std::cout << "Descripción: " << node->data.descripcion << std::endl;
    std::cout << "Rating Promedio: " << node->data.rating_promedio << std::endl;
}

void Tree::desplegar_datos(int id_libro)
{
    Node *node = search(rootNode, id_libro);
    if (!node)
    {
        std::cout << "No se encontró el libro con ID " << id_libro << "." << std::endl;
        return;
    }
    desplegar_datos(node);
}

// Para ver los precursores, se recorre el árbol y se llama a precursor_por_id para cada nodo, si es precursor se muestra su ID.
void Tree::precursores()
{
    std::vector<int> ids = preOrder();
    bool hayPrecursores = false;

    for (int id : ids)
    {
        if (id == -1)
        {
            continue;
        }
        if (precursor_por_id(id))
        {
            hayPrecursores = true;
        }
    }
    if (!hayPrecursores)
    {
        std::cout << "No se encontraron precursores" << std::endl;
    }
}
