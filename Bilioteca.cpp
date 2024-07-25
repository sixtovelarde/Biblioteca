#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdio>

using namespace std;

struct Persona {
    int id;
    string Nombre;
    string Apellido;
    string Email;
    string Clave;
    string libros_prestados_ids;
    string libros_comprados_ids;
    string estado;
};

struct Libro {
    int id;
    string titulo;
    string autor;
    string genero;
    string fecha_publicacion;
    string editorial;
    float precio;
    string disponibilidad;
    int cantidad;
};

void LeerDatosLibros(const string &filename, Libro* &catalogo, int &tamanoCatalogo);
void LeerDatosPersonas(const string &filename, Persona* &catalogo, int &tamanoCatalogo);

void AgregarDatosLibros(Libro* &catalogo, int &tamanoCatalogo);
void EliminarDatosLibros(Libro* &catalogo, int &tamanoCatalogo);
void ModificarDatosLibros(Libro* &catalogo, int tamanoCatalogo);

void AgregarDatosPersonas(Persona* &catalogo, int &tamanoCatalogo);
void EliminarDatosPersonas(Persona* &catalogo, int &tamanoCatalogo);
void ModificarDatosPersonas(Persona* &catalogo, int tamanoCatalogo);

void RegistroNuevoUsuario(Persona* &catalogo, int &tamanoCatalogo);
void SuspenderUsuario(Persona* &catalogo, int &tamanoCatalogo);

void ComprarLibro(const string &emailAutenticado);
void PrestarLibro(const string &emailAutenticado);
void DevolverLibro(const string &emailAutenticado);

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

    while (continuar) {
        if (!sesionActiva) {
            cout << "Ingrese su correo: ";
            getline(cin, p.Email);
            cout << "Ingrese su clave: ";
            getline(cin, p.Clave);
            ifstream archivoPersonas("Clientes.csv");
            
            emailAutenticado = p.Email;
            string claveAutenticada = p.Clave;
            bool usuarioEncontrado = false;

            while (getline(archivoPersonas, linea)) {
                stringstream ss(linea);
                string id, nombre, apellido, emailBuscado, clave, libros_prestados_ids, libros_comprados_ids, estado;

                getline(ss, id, ',');
                getline(ss, nombre, ',');
                getline(ss, apellido, ',');
                getline(ss, emailBuscado, ',');
                getline(ss, clave, ',');
                getline(ss, libros_prestados_ids, ',');
                getline(ss, libros_comprados_ids, ',');
                getline(ss, estado, ',');

                if (emailBuscado == p.Email && clave == p.Clave) {
                    if (estado == "admin") {
                        admin_cliente = 1;
                    } else if (estado == "cliente") {
                        admin_cliente = 2;
                    }
                    usuarioEncontrado = true;
                    break;
                }
            }
            archivoPersonas.close();

            if (!usuarioEncontrado) {
                cout << "Correo o clave incorrectos. ¿Desea registrarse? (s/n): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 's' || respuesta == 'S') {
                    RegistroNuevoUsuario(catalogoPersonas, tamanoCatalogoPersonas);
                    cout << "Registro exitoso. Ahora puede iniciar sesión." << endl;
                    sesionActiva = false;
                } else {
                    sesionActiva = false;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
                    continue;
                }
            } else {
                sesionActiva = true;
            }
        }

        if (sesionActiva) {
            switch (admin_cliente) {
                case 1: {
                    cout << "¿Qué desea hacer hoy?\n1.-Gestionar datos de libros\n2.-Gestionar datos de personas\n3.-Suspender un usuario\n4.-Comprar, Prestar o Devolver un libro\n5.-Salir\n";
                    cin >> opcion;
                    switch (opcion) {
                        case 1: {
                            cout << "Seleccione una opción" << endl
                                 << "1.-Agregar un libro" << endl
                                 << "2.-Eliminar un libro" << endl
                                 << "3.-Modificar un libro" << endl;
                            cin >> opcion2;
                            switch (opcion2) {
                                case 1: AgregarDatosLibros(catalogoLibros, tamanoCatalogoLibros); break;
                                case 2: EliminarDatosLibros(catalogoLibros, tamanoCatalogoLibros); break;
                                case 3: ModificarDatosLibros(catalogoLibros, tamanoCatalogoLibros); break;
                            }
                            break;
                        }
                        case 2: {
                            cout << "Seleccione una opción" << endl
                                 << "1.-Agregar una persona" << endl
                                 << "2.-Eliminar una persona" << endl
                                 << "3.-Modificar los datos de una persona" << endl;
                            cin >> opcion3;
                            switch (opcion3) {
                                case 1: AgregarDatosPersonas(catalogoPersonas, tamanoCatalogoPersonas); break;
                                case 2: EliminarDatosPersonas(catalogoPersonas, tamanoCatalogoPersonas); break;
                                case 3: ModificarDatosPersonas(catalogoPersonas, tamanoCatalogoPersonas); break;
                            }
                            break;
                        }
                        case 3: {
                            SuspenderUsuario(catalogoPersonas, tamanoCatalogoPersonas);
                            break;
                        }
                        case 4: {
                            cout << "Seleccione una opción" << endl
                                 << "1.-Comprar un libro" << endl
                                 << "2.-Prestar un libro" << endl
                                 << "3.-Devolver un libro" << endl;
                            cin >> opcion4;
                            switch (opcion4) {
                                case 1: ComprarLibro(emailAutenticado); break;
                                case 2: PrestarLibro(emailAutenticado); break;
                                case 3: DevolverLibro(emailAutenticado); break;
                            }
                            break;
                        }
                        case 5: {
                            continuar = false;
                            sesionActiva = false;
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    cout << "¿Qué desea hacer hoy?" << endl
                         << "1.-Comprar un libro" << endl
                         << "2.-Prestar un libro" << endl
                         << "3.-Devolver un libro" << endl
                         << "4.-Salir\n";
                    cin >> opcion5;
                    switch (opcion5) {
                        case 1: ComprarLibro(emailAutenticado); break;
                        case 2: PrestarLibro(emailAutenticado); break;
                        case 3: DevolverLibro(emailAutenticado); break;
                        case 4: {
                            continuar = false;
                            sesionActiva = false;
                            break;
                        }
                    }
                    break;
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
        }
    }

    // Liberar memoria dinámica
    delete[] catalogoLibros;
    delete[] catalogoPersonas;

    return 0;
}

void LeerDatosLibros(const string &filename, Libro* &catalogo, int &tamanoCatalogo) {
    ifstream archivo(filename);
    string linea;
    tamanoCatalogo = 0;

    // Contar el número de libros
    while (getline(archivo, linea)) {
        tamanoCatalogo++;
    }
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Reservar memoria para los libros
    catalogo = new Libro[tamanoCatalogo];

    // Leer los datos
    int index = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, titulo, autor, genero, fecha_publicacion, editorial, precioStr, disponibilidad, cantidadStr;

        getline(ss, idStr, ',');
        getline(ss, titulo, ',');
        getline(ss, autor, ',');
        getline(ss, genero, ',');
        getline(ss, fecha_publicacion, ',');
        getline(ss, editorial, ',');
        getline(ss, precioStr, ',');
        getline(ss, disponibilidad, ',');
        getline(ss, cantidadStr, ',');

        catalogo[index].id = stoi(idStr);
        catalogo[index].titulo = titulo;
        catalogo[index].autor = autor;
        catalogo[index].genero = genero;
        catalogo[index].fecha_publicacion = fecha_publicacion;
        catalogo[index].editorial = editorial;
        catalogo[index].precio = stof(precioStr);
        catalogo[index].disponibilidad = disponibilidad;
        catalogo[index].cantidad = stoi(cantidadStr);

        index++;
    }
}

void LeerDatosPersonas(const string &filename, Persona* &catalogo, int &tamanoCatalogo) {
    ifstream archivo(filename);
    string linea;
    tamanoCatalogo = 0;

    // Contar el número de personas
    while (getline(archivo, linea)) {
        tamanoCatalogo++;
    }
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Reservar memoria para las personas
    catalogo = new Persona[tamanoCatalogo];

    // Leer los datos
    int index = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombre, apellido, email, clave, libros_prestados_ids, libros_comprados_ids, estado;

        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        getline(ss, clave, ',');
        getline(ss, libros_prestados_ids, ',');
        getline(ss, libros_comprados_ids, ',');
        getline(ss, estado, ',');

        catalogo[index].id = stoi(idStr);
        catalogo[index].Nombre = nombre;
        catalogo[index].Apellido = apellido;
        catalogo[index].Email = email;
        catalogo[index].Clave = clave;
        catalogo[index].libros_prestados_ids = libros_prestados_ids;
        catalogo[index].libros_comprados_ids = libros_comprados_ids;
        catalogo[index].estado = estado;

        index++;
    }
}

void AgregarDatosLibros(Libro* &catalogo, int &tamanoCatalogo) {
    int nuevo_id = tamanoCatalogo + 1; // Nuevo ID basado en el tamaño actual
    Libro l;
    cout << "Ingrese el título: ";
    cin.ignore();
    getline(cin, l.titulo);
    cout << "Ingrese el nombre del autor: ";
    getline(cin, l.autor);
    cout << "Ingrese el género: ";
    getline(cin, l.genero);
    cout << "Ingrese la fecha de publicación: ";
    getline(cin, l.fecha_publicacion);
    cout << "Ingrese la editorial: ";
    getline(cin, l.editorial);
    cout << "Ingrese el precio del libro: ";
    cin >> l.precio;
    cout << "Ingrese la disponibilidad del libro: ";
    cin.ignore();
    getline(cin, l.disponibilidad);
    cout << "Ingrese la cantidad de libros disponibles: ";
    cin >> l.cantidad;

    // Abrir archivo en modo append
    ofstream archivoLibros("Books.csv", ios::app);
    if (!archivoLibros.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    archivoLibros << nuevo_id << "," << l.titulo << "," << l.autor << "," << l.genero << "," << l.fecha_publicacion << "," << l.editorial << "," << l.precio << "," << l.disponibilidad << "," << l.cantidad << endl;
    archivoLibros.close();
    tamanoCatalogo++;
}

void EliminarDatosLibros(Libro* &catalogo, int &tamanoCatalogo) {
    int id;
    cout << "Ingrese el ID del libro a eliminar: ";
    cin >> id;
    
    ifstream archivoLibros("Books.csv");
    ofstream archivoTemp("temp.csv");

    if (!archivoLibros.is_open() || !archivoTemp.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivoLibros, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');
        int idActual = stoi(idStr);
        if (idActual != id) {
            archivoTemp << linea << endl;
        }
    }

    archivoLibros.close();
    archivoTemp.close();
    remove("Books.csv");
    rename("temp.csv", "Books.csv");

    cout << "Libro eliminado exitosamente." << endl;
    tamanoCatalogo--;
}

void ModificarDatosLibros(Libro* &catalogo, int tamanoCatalogo) {
    int id;
    cout << "Ingrese el ID del libro a modificar: ";
    cin >> id;

    ifstream archivoLibros("Books.csv");
    ofstream archivoTemp("temp.csv");

    if (!archivoLibros.is_open() || !archivoTemp.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    bool libroEncontrado = false;

    while (getline(archivoLibros, linea)) {
        stringstream ss(linea);
        string idStr, titulo, autor, genero, fecha_publicacion, editorial, precioStr, disponibilidad, cantidadStr;
        getline(ss, idStr, ',');
        getline(ss, titulo, ',');
        getline(ss, autor, ',');
        getline(ss, genero, ',');
        getline(ss, fecha_publicacion, ',');
        getline(ss, editorial, ',');
        getline(ss, precioStr, ',');
        getline(ss, disponibilidad, ',');
        getline(ss, cantidadStr, ',');

        if (stoi(idStr) == id) {
            libroEncontrado = true;
            cout << "Ingrese el nuevo título (deje en blanco para mantener el actual): ";
            cin.ignore();
            getline(cin, titulo);
            cout << "Ingrese el nuevo nombre del autor (deje en blanco para mantener el actual): ";
            getline(cin, autor);
            cout << "Ingrese el nuevo género (deje en blanco para mantener el actual): ";
            getline(cin, genero);
            cout << "Ingrese la nueva fecha de publicación (deje en blanco para mantener la actual): ";
            getline(cin, fecha_publicacion);
            cout << "Ingrese la nueva editorial (deje en blanco para mantener la actual): ";
            getline(cin, editorial);
            cout << "Ingrese el nuevo precio (deje en blanco para mantener el actual): ";
            string precioStrNuevo;
            getline(cin, precioStrNuevo);
            cout << "Ingrese la nueva disponibilidad (deje en blanco para mantener la actual): ";
            getline(cin, disponibilidad);
            cout << "Ingrese la nueva cantidad (deje en blanco para mantener la actual): ";
            string cantidadStrNuevo;
            getline(cin, cantidadStrNuevo);

            float precio = precioStrNuevo.empty() ? stof(precioStr) : stof(precioStrNuevo);
            int cantidad = cantidadStrNuevo.empty() ? stoi(cantidadStr) : stoi(cantidadStrNuevo);

            archivoTemp << idStr << "," << (titulo.empty() ? titulo : titulo) << "," << (autor.empty() ? autor : autor) << "," << (genero.empty() ? genero : genero) << "," << (fecha_publicacion.empty() ? fecha_publicacion : fecha_publicacion) << "," << (editorial.empty() ? editorial : editorial) << "," << precio << "," << (disponibilidad.empty() ? disponibilidad : disponibilidad) << "," << cantidad << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivoLibros.close();
    archivoTemp.close();
    remove("Books.csv");
    rename("temp.csv", "Books.csv");

    if (libroEncontrado) {
        cout << "Libro modificado exitosamente." << endl;
    } else {
        cout << "No se encontró el libro con el ID especificado." << endl;
    }
}

void AgregarDatosPersonas(Persona* &catalogo, int &tamanoCatalogo) {
    int nuevo_id = tamanoCatalogo + 1; // Nuevo ID basado en el tamaño actual
    Persona p;
    cout << "Ingrese el nombre: ";
    cin.ignore();
    getline(cin, p.Nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, p.Apellido);
    cout << "Ingrese el correo: ";
    getline(cin, p.Email);
    cout << "Ingrese la clave: ";
    getline(cin, p.Clave);
    p.libros_prestados_ids = "";
    p.libros_comprados_ids = "";
    p.estado = "cliente";

    // Abrir archivo en modo append
    ofstream archivoPersonas("Clientes.csv", ios::app);
    if (!archivoPersonas.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    archivoPersonas << nuevo_id << "," << p.Nombre << "," << p.Apellido << "," << p.Email << "," << p.Clave << "," << p.libros_prestados_ids << "," << p.libros_comprados_ids << "," << p.estado << endl;
    archivoPersonas.close();
    tamanoCatalogo++;
}

void EliminarDatosPersonas(Persona* &catalogo, int &tamanoCatalogo) {
    int id;
    cout << "Ingrese el ID de la persona a eliminar: ";
    cin >> id;
    
    ifstream archivoPersonas("Clientes.csv");
    ofstream archivoTemp("temp.csv");

    if (!archivoPersonas.is_open() || !archivoTemp.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivoPersonas, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');
        int idActual = stoi(idStr);
        if (idActual != id) {
            archivoTemp << linea << endl;
        }
    }

    archivoPersonas.close();
    archivoTemp.close();
    remove("Clientes.csv");
    rename("temp.csv", "Clientes.csv");

    cout << "Persona eliminada exitosamente." << endl;
    tamanoCatalogo--;
}

void ModificarDatosPersonas(Persona* &catalogo, int tamanoCatalogo) {
    int id;
    cout << "Ingrese el ID de la persona a modificar: ";
    cin >> id;

    ifstream archivoPersonas("Clientes.csv");
    ofstream archivoTemp("temp.csv");

    if (!archivoPersonas.is_open() || !archivoTemp.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    bool personaEncontrada = false;

    while (getline(archivoPersonas, linea)) {
        stringstream ss(linea);
        string idStr, nombre, apellido, email, clave, libros_prestados_ids, libros_comprados_ids, estado;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        getline(ss, clave, ',');
        getline(ss, libros_prestados_ids, ',');
        getline(ss, libros_comprados_ids, ',');
        getline(ss, estado, ',');

        if (stoi(idStr) == id) {
            personaEncontrada = true;
            cout << "Ingrese el nuevo nombre (deje en blanco para mantener el actual): ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese el nuevo apellido (deje en blanco para mantener el actual): ";
            getline(cin, apellido);
            cout << "Ingrese el nuevo correo (deje en blanco para mantener el actual): ";
            getline(cin, email);
            cout << "Ingrese la nueva clave (deje en blanco para mantener la actual): ";
            getline(cin, clave);
            cout << "Ingrese los nuevos libros prestados IDs (deje en blanco para mantener los actuales): ";
            getline(cin, libros_prestados_ids);
            cout << "Ingrese los nuevos libros comprados IDs (deje en blanco para mantener los actuales): ";
            getline(cin, libros_comprados_ids);
            cout << "Ingrese el nuevo estado (deje en blanco para mantener el actual): ";
            getline(cin, estado);

            archivoTemp << idStr << "," << (nombre.empty() ? nombre : nombre) << "," << (apellido.empty() ? apellido : apellido) << "," << (email.empty() ? email : email) << "," << (clave.empty() ? clave : clave) << "," << (libros_prestados_ids.empty() ? libros_prestados_ids : libros_prestados_ids) << "," << (libros_comprados_ids.empty() ? libros_comprados_ids : libros_comprados_ids) << "," << (estado.empty() ? estado : estado) << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivoPersonas.close();
    archivoTemp.close();
    remove("Clientes.csv");
    rename("temp.csv", "Clientes.csv");

    if (personaEncontrada) {
        cout << "Persona modificada exitosamente." << endl;
    } else {
        cout << "No se encontró la persona con el ID especificado." << endl;
    }
}

void RegistroNuevoUsuario(Persona* &catalogo, int &tamanoCatalogo) {
    AgregarDatosPersonas(catalogo, tamanoCatalogo);
}

void SuspenderUsuario(Persona* &catalogo, int &tamanoCatalogo) {
    int id;
    cout << "Ingrese el ID del usuario a suspender: ";
    cin >> id;

    ifstream archivoPersonas("Clientes.csv");
    ofstream archivoTemp("temp.csv");

    if (!archivoPersonas.is_open() || !archivoTemp.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivoPersonas, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');
        int idActual = stoi(idStr);
        if (idActual == id) {
            archivoTemp << idStr << ","; // Mantener ID
            string nombre, apellido, email, clave, libros_prestados_ids, libros_comprados_ids, estado;
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, email, ',');
            getline(ss, clave, ',');
            getline(ss, libros_prestados_ids, ',');
            getline(ss, libros_comprados_ids, ',');
            getline(ss, estado, ',');

            // Modificar estado a "suspendido"
            archivoTemp << nombre << "," << apellido << "," << email << "," << clave << "," << libros_prestados_ids << "," << libros_comprados_ids << "," << "suspendido" << endl;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivoPersonas.close();
    archivoTemp.close();
    remove("Clientes.csv");
    rename("temp.csv", "Clientes.csv");

    cout << "Usuario suspendido exitosamente." << endl;
    tamanoCatalogo--;
}

void ComprarLibro(const string &authenticatedEmail) {
    string bookTitle;

    cout << "Ingrese el nombre del libro que quiere comprar: ";
    cin.ignore();
    getline(cin, bookTitle);

    ifstream fileIn("Books.csv");
    ofstream fileOut("Books_temp.csv");
    string line;
    bool bookFound = false;
    int bookId;

    while (getline(fileIn, line)) {
        stringstream ss(line);
        string idStr, title, author, genre, pubDate, publisher, priceStr, availability, quantityStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genre, ',');
        getline(ss, pubDate, ',');
        getline(ss, publisher, ',');
        getline(ss, priceStr, ',');
        getline(ss, availability, ',');
        getline(ss, quantityStr, ',');

        if (title == bookTitle) {
            int quantity = stoi(quantityStr);
            if (quantity > 0) {
                quantity--;
                fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantity << "\n";
                bookFound = true;
                bookId = stoi(idStr);
            } else {
                cout << "Lo siento, no hay suficientes copias disponibles.\n";
                fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantityStr << "\n";
            }
        } else {
            fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantityStr << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

    remove("Books.csv");
    rename("Books_temp.csv", "Books.csv");

    if (bookFound) {
        ifstream peopleFileIn("Clients.csv");
        ofstream peopleFileOut("Clients_temp.csv");
        string peopleLine;

        while (getline(peopleFileIn, peopleLine)) {
            stringstream ss(peopleLine);
            string id, nombre, apellido, email, clave, borrowedBooks, purchasedBooks, status;

            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, email, ',');
            getline(ss, clave, ',');
            getline(ss, borrowedBooks, ',');
            getline(ss, purchasedBooks, ',');
            getline(ss, status, ',');

            if (email == authenticatedEmail) {
                if (!purchasedBooks.empty()) {
                    purchasedBooks += ";" + to_string(bookId);
                } else {
                    purchasedBooks = to_string(bookId);
                }
            }

            peopleFileOut << id << "," << nombre << "," << apellido << "," << email << "," << clave << "," << borrowedBooks << "," << purchasedBooks << "," << status << "\n";
        }

        peopleFileIn.close();
        peopleFileOut.close();

        remove("Clients.csv");
        rename("Clients_temp.csv", "Clients.csv");

        cout << "Compra realizada con éxito!\n";
    } else {
        cout << "El libro no se encontró en el inventario.\n";
    }
}

void PrestarLibro(const string &authenticatedEmail) {
    string bookTitle;

    cout << "Ingrese el nombre del libro que quiere prestar: ";
    cin.ignore();
    getline(cin, bookTitle);

    ifstream fileIn("Books.csv");
    ofstream fileOut("Books_temp.csv");
    string line;
    bool bookFound = false;
    int bookId;

    while (getline(fileIn, line)) {
        stringstream ss(line);
        string idStr, title, author, genre, pubDate, publisher, priceStr, availability, quantityStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genre, ',');
        getline(ss, pubDate, ',');
        getline(ss, publisher, ',');
        getline(ss, priceStr, ',');
        getline(ss, availability, ',');
        getline(ss, quantityStr, ',');

        if (title == bookTitle) {
            int quantity = stoi(quantityStr);
            if (quantity > 0) {
                quantity--;
                fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantity << "\n";
                bookFound = true;
                bookId = stoi(idStr);
            } else {
                cout << "Lo siento, no hay suficientes copias disponibles.\n";
                fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantityStr << "\n";
            }
        } else {
            fileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantityStr << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

  
    remove("Books.csv");
    rename("Books_temp.csv", "Books.csv");

    if (bookFound) {
        ifstream peopleFileIn("Clients.csv");
        ofstream peopleFileOut("Clients_temp.csv");
        string peopleLine;

        while (getline(peopleFileIn, peopleLine)) {
            stringstream ss(peopleLine);
            string id, nombre, apellido, email, clave, borrowedBooks, purchasedBooks, status;

            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, email, ',');
            getline(ss, clave, ',');
            getline(ss, borrowedBooks, ',');
            getline(ss, purchasedBooks, ',');
            getline(ss, status, ',');

            if (email == authenticatedEmail) {
                if (!borrowedBooks.empty()) {
                    borrowedBooks += ";" + to_string(bookId);
                } else {
                    borrowedBooks = to_string(bookId);
                }
            }

            peopleFileOut << id << "," << nombre << "," << apellido << "," << email << "," << clave << "," << borrowedBooks << "," << purchasedBooks << "," << status << "\n";
        }

        peopleFileIn.close();
        peopleFileOut.close();

        remove("Clients.csv");
        rename("Clients_temp.csv", "Clients.csv");

        cout << "Préstamo realizado con éxito!\n";
    } else {
        cout << "El libro no se encontró en el inventario.\n";
    }
}

void DevolverLibro(const string &authenticatedEmail) {
    ifstream peopleFileIn("Clients.csv");
    string peopleLine;
    string borrowedBooks;

 
    while (getline(peopleFileIn, peopleLine)) {
        stringstream ss(peopleLine);
        string id, nombre, apellido, email, clave, borrowedBooksStr, purchasedBooks, status;

        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        getline(ss, clave, ',');
        getline(ss, borrowedBooksStr, ',');
        getline(ss, purchasedBooks, ',');
        getline(ss, status, ',');

        if (email == authenticatedEmail) {
            borrowedBooks = borrowedBooksStr;
            break;
        }
    }
    peopleFileIn.close();

    if (borrowedBooks.empty()) {
        cout << "No tienes libros prestados.\n";
        return;
    }


    cout << "Libros prestados:\n";
    stringstream ssBooks(borrowedBooks);
    string bookIdStr;
    while (getline(ssBooks, bookIdStr, ';')) {
        cout << "ID del libro: " << bookIdStr << endl;
    }

    int returnBookId;
    cout << "Ingrese el ID del libro que desea devolver: ";
    cin >> returnBookId;

 
    stringstream ssCheck(borrowedBooks);
    bool found = false;
    string newBorrowedBooks;
    while (getline(ssCheck, bookIdStr, ';')) {
        try {
            if (!bookIdStr.empty() && stoi(bookIdStr) == returnBookId) {
                found = true;
            } else {
                if (!newBorrowedBooks.empty()) {
                    newBorrowedBooks += ";";
                }
                newBorrowedBooks += bookIdStr;
            }
        } catch (const invalid_argument &e) {
            cout << "Error al convertir el ID del libro: " << bookIdStr << endl;
            continue;
        }
    }

    if (!found) {
        cout << "ID de libro no válido.\n";
        return;
    }

    ifstream peopleFileIn2("Clients.csv");
    ofstream peopleFileOut("Clients_temp.csv");
    while (getline(peopleFileIn2, peopleLine)) {
        stringstream ss(peopleLine);
        string id, nombre, apellido, email, clave, borrowedBooksStr, purchasedBooks, status;

        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        getline(ss, clave, ',');
        getline(ss, borrowedBooksStr, ',');
        getline(ss, purchasedBooks, ',');
        getline(ss, status, ',');

        if (email == authenticatedEmail) {
            peopleFileOut << id << "," << nombre << "," << apellido << "," << email << "," << clave << "," << newBorrowedBooks << "," << purchasedBooks << "," << status << "\n";
        } else {
            peopleFileOut << id << "," << nombre << "," << apellido << "," << email << "," << clave << "," << borrowedBooksStr << "," << purchasedBooks << "," << status << "\n";
        }
    }
    peopleFileIn2.close();
    peopleFileOut.close();
    remove("Clients.csv");
    rename("Clients_temp.csv", "Clients.csv");

    ifstream booksFileIn("Books.csv");
    ofstream booksFileOut("Books_temp.csv");
    string booksLine;

    if (getline(booksFileIn, booksLine)) {
        booksFileOut << booksLine << "\n";
    }

    while (getline(booksFileIn, booksLine)) {
        stringstream ss(booksLine);
        string idStr, title, author, genre, pubDate, publisher, priceStr, availability, quantityStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genre, ',');
        getline(ss, pubDate, ',');
        getline(ss, publisher, ',');
        getline(ss, priceStr, ',');
        getline(ss, availability, ',');
        getline(ss, quantityStr, ',');

        try {
            if (!idStr.empty() && stoi(idStr) == returnBookId) {
                int quantity = stoi(quantityStr) + 1;
                booksFileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantity << "\n";
            } else {
                booksFileOut << idStr << "," << title << "," << author << "," << genre << "," << pubDate << "," << publisher << "," << priceStr << "," << availability << "," << quantityStr << "\n";
            }
        } catch (const invalid_argument &e) {
            cout << "Error al convertir el ID del libro: " << idStr << endl;
            continue;
        }
    }
    booksFileIn.close();
    booksFileOut.close();
    remove("Books.csv");
    rename("Books_temp.csv", "Books.csv");

    cout << "Libro devuelto con éxito!\n";
}