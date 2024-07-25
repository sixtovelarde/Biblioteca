#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "controllers/BibliotecaController.cpp"
#include "models/Libro.h"
#include "models/Persona.h"
#include "views/BibliotecaView.cpp"

using namespace std;

bool autenticarUsuario(const std::string& email, const std::string& clave, Persona* catalogo, int tamanoCatalogo, std::string& emailAutenticado) {
    for (int i = 0; i < tamanoCatalogo; ++i) {
        if (catalogo[i].Email == email && catalogo[i].Clave == clave) {
            emailAutenticado = email;
            return true;
        }
    }
    return false;
}

void cargarPersonas(const std::string& filename, Persona* &catalogo, int &tamanoCatalogo) {
    std::ifstream archivo(filename);
    std::string linea;
    tamanoCatalogo = 0;

    while (std::getline(archivo, linea)) {
        tamanoCatalogo++;
    }
    
    archivo.clear();
    archivo.seekg(0, std::ios::beg);

    catalogo = new Persona[tamanoCatalogo];
    int index = 0;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dato;
        int col = 0;
        
        while (std::getline(ss, dato, ',')) {
            switch (col) {
                case 0: catalogo[index].id = std::stoi(dato); break;
                case 1: catalogo[index].Nombre = dato; break;
                case 2: catalogo[index].Apellido = dato; break;
                case 3: catalogo[index].Email = dato; break;
                case 4: catalogo[index].Clave = dato; break;
                case 5: catalogo[index].libros_prestados_ids = dato; break;
                case 6: catalogo[index].libros_comprados_ids = dato; break;
                case 7: catalogo[index].estado = dato; break;
            }
            col++;
        }
        index++;
    }
}

void manejarMenuPrincipal(bool &continuar, bool &sesionActiva) {
    int opcion;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\\n');

    switch (opcion) {
        case 1:
            mostrarMenuLibros();
            break;
        case 2:
            mostrarMenuPersonas();
            break;
        case 3:
            mostrarMenuAdministracion();
            break;
        case 4:
            mostrarMenuCliente();
            break;
        case 5:
            continuar = false;
            sesionActiva = false;
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
    }
}

int main() {
    string linea;
    Persona p;
    int opcion, opcion2, opcion3, opcion4, opcion5, admin_cliente = 0;
    bool continuar = true;
    bool sesionActiva = false;
    string emailAutenticado;

    Libro* catalogoLibros = nullptr;
    int tamanoCatalogoLibros = 0;
    Persona* catalogoPersonas = nullptr;
    int tamanoCatalogoPersonas = 0;

    cargarPersonas("Clients.csv", catalogoPersonas, tamanoCatalogoPersonas);

    while (continuar) {
        if (!sesionActiva) {
            cout << "Ingrese su correo: ";
            getline(cin, p.Email);
            cout << "Ingrese su clave: ";
            getline(cin, p.Clave);

            if (autenticarUsuario(p.Email, p.Clave, catalogoPersonas, tamanoCatalogoPersonas, emailAutenticado)) {
                sesionActiva = true;
                cout << "Inicio de sesión exitoso." << endl;
            } else {
                cout << "Correo o clave incorrectos. Intente de nuevo." << endl;
            }
        } else {
            mostrarMenuPrincipal();
            manejarMenuPrincipal(continuar, sesionActiva);
        }
    }

    delete[] catalogoLibros;
    delete[] catalogoPersonas;

    return 0;
}
