#ifndef PERSONA_H
#define PERSONA_H

#include <string>

struct Persona {
    int id;
    std::string Nombre;
    std::string Apellido;
    std::string Email;
    std::string Clave;
    std::string libros_prestados_ids;
    std::string libros_comprados_ids;
    std::string estado;
};

#endif // PERSONA_H
