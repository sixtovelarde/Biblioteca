#include <iostream>
#include "../models/Persona.h"
#include "../models/Libro.h"

using namespace std;

void mostrarMenuPrincipal() {
    cout << "Menú Principal" << endl;
    cout << "1. Libros" << endl;
    cout << "2. Personas" << endl;
    cout << "3. Administración" << endl;
    cout << "4. Cliente" << endl;
    cout << "5. Salir" << endl;
}

void mostrarMenuLibros() {
    cout << "Menú Libros" << endl;
    cout << "1. Agregar libro" << endl;
    cout << "2. Eliminar libro" << endl;
    cout << "3. Modificar libro" << endl;
    cout << "4. Volver al menú principal" << endl;
}

void mostrarMenuPersonas() {
    cout << "Menú Personas" << endl;
    cout << "1. Agregar persona" << endl;
    cout << "2. Eliminar persona" << endl;
    cout << "3. Modificar persona" << endl;
    cout << "4. Volver al menú principal" << endl;
}

void mostrarMenuAdministracion() {
    cout << "Menú Administración" << endl;
    cout << "1. Registro nuevo usuario" << endl;
    cout << "2. Suspender usuario" << endl;
    cout << "3. Volver al menú principal" << endl;
}

void mostrarMenuCliente() {
    cout << "Menú Cliente" << endl;
    cout << "1. Comprar libro" << endl;
    cout << "2. Prestar libro" << endl;
    cout << "3. Devolver libro" << endl;
    cout << "4. Volver al menú principal" << endl;
}

void mostrarSesionActiva() {
    cout << "Sesión activa" << endl;
}

void mostrarMenuLibros();
void mostrarMenuPersonas();
void mostrarMenuAdministracion();
void mostrarMenuCliente();
void mostrarSesionActiva();
