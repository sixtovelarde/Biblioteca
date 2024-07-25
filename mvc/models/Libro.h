#ifndef LIBRO_H
#define LIBRO_H

#include <string>

struct Libro {
    int id;
    std::string titulo;
    std::string autor;
    std::string genero;
    std::string fecha_publicacion;
    std::string editorial;
    float precio;
    std::string disponibilidad;
    int cantidad;
};

#endif // LIBRO_H
