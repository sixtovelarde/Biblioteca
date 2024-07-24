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
    int id_libros_prestados;
    string status;
    int id_libros_comprados;
};

struct libros {
    int id;
    string titulo;
    string autor;
    string genero;
    string fecha_publicacion;
    string editorial;
    float precio;
    string disponibilidad_libros;
    int cantidad_libros;
};

void LeerDatosLibros(const string &filename, libros catalog[], int &catalogsize);
void LeerDatosPersonas(const string &filename, Persona catalog[], int &catalogsize);

void AgregarDatosLibros();
void EliminarDatosLibros();
void ModificarDatosLibros();

void AgregarDatosPersonas();
void EliminarDatosPersonas();
void ModificarDatosPersonas();

void RegistroNuevoUsuario();
void SuspenderUsuario();

void ComprarLibro(const string &authenticatedEmail);
void PrestarLibro(const string &authenticatedEmail);
void DevolverLibro(const string &authenticatedEmail);

int main() {
    string line;
    Persona p;
    int opcion, opcion2, opcion3, opcion4, opcion5, admin_cliente = 0;
    bool opcionvalida = false;
    bool continuar = true;

    cout << "Ingrese su correo: ";
    getline(cin, p.Email);
    cout << "Ingrese su clave: ";
    getline(cin, p.Clave);
    ifstream people_file("Clients.csv");

    string authenticatedEmail = p.Email;
    string authenticatedPassword = p.Clave;

    while (getline(people_file, line)) {
        stringstream ss(line);
        string id, nombre, apellido, search_email, password, borrowed_books_ids, purchased_books_ids, status;

        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, search_email, ',');
        getline(ss, password, ',');
        getline(ss, borrowed_books_ids, ',');
        getline(ss, purchased_books_ids, ',');
        getline(ss, status, ',');

        if (search_email == p.Email && password == p.Clave) {
            if (status == "admin") {
                admin_cliente = 1;
            } else if (status == "cliente") {
                admin_cliente = 2;
            }
            break;
        }
    }
    people_file.close();

    if (admin_cliente == 0) {
        cout << "Correo o clave incorrecta." << endl;
        return 1;
    }

    switch (admin_cliente) {
        case 1: {
            cout << "Que desea hacer hoy?\n1.-Gestionar datos libros\n2.-Gestionar datos personas\n3.-Suspender un usuario\n4.-Comprar, Prestar o Devolver un libro\n";
            cin >> opcion;
            switch (opcion) {
                case 1: {
                    cout << "Seleccione una opcion" << endl
                         << "1.-Agregar un libro" << endl
                         << "2.-Eliminar un libro" << endl
                         << "3.-Modificar un libro" << endl;
                    cin >> opcion2;
                    switch (opcion2) {
                        case 1: {
                            AgregarDatosLibros();
                            break;
                        }
                        case 2: {
                            EliminarDatosLibros();
                            break;
                        }
                        case 3: {
                            ModificarDatosLibros();
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    cout << "Seleccione una opcion" << endl
                         << "1.-Agregar una persona" << endl
                         << "2.-Eliminar una persona" << endl
                         << "3.-Modificar los datos de una persona" << endl;
                    cin >> opcion3;
                    switch (opcion3) {
                        case 1: {
                            AgregarDatosPersonas();
                            break;
                        }
                        case 2: {
                            EliminarDatosPersonas();
                            break;
                        }
                        case 3: {
                            ModificarDatosPersonas();
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    SuspenderUsuario();
                    break;
                }
                case 4: {
                    cout << "Seleccione una opcion" << endl
                         << "1.-Comprar un libro" << endl
                         << "2.-Prestar un libro" << endl
                         << "3.-Devolver un libro" << endl;
                    cin >> opcion4;
                    switch (opcion4) {
                        case 1: {
                            ComprarLibro(authenticatedEmail);
                            break;
                        }
                        case 2: {
                            PrestarLibro(authenticatedEmail);
                            break;
                        }
                        case 3: {
                            DevolverLibro(authenticatedEmail);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 2: {
            cout << "Que desea hacer hoy?" << endl
                 << "1.-Comprar un libro" << endl
                 << "2.-Prestar un libro" << endl
                 << "3.-Devolver un libro" << endl;
            cin >> opcion5;
            switch (opcion5) {
                case 1: {
                    ComprarLibro(authenticatedEmail);
                    break;
                }
                case 2: {
                    PrestarLibro(authenticatedEmail);
                    break;
                }
                case 3: {
                    DevolverLibro(authenticatedEmail);
                    break;
                }
            }
            break;
        }
    }
    return 0;
}

void AgregarDatosLibros() {
    ifstream bookfile2("Books.csv");
    string line;
    libros l;
    int new_id = 0;

    while (getline(bookfile2, line)) {
        new_id++;
    }
    bookfile2.close();
    l.id = new_id;

    cout << "Ingrese el titulo: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, l.titulo);
    cout << "Ingrese el nombre del autor: ";
    getline(cin, l.autor);
    cout << "Ingrese el genero: ";
    getline(cin, l.genero);
    cout << "Ingrese la fecha de publicacion: ";
    getline(cin, l.fecha_publicacion);
    cout << "Ingrese la editorial: ";
    getline(cin, l.editorial);
    cout << "Ingrese el precio del libro: ";
    cin >> l.precio;
    cout << "Ingrese la disponibilidad del libro: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, l.disponibilidad_libros);
    cout << "Ingrese la cantidad de libros disponibles: ";
    cin >> l.cantidad_libros;

    ofstream bookfile("Books.csv", ios::app);

    bookfile << l.id << "," << l.titulo << "," << l.autor << "," << l.genero << "," << l.fecha_publicacion << "," << l.editorial << "," << l.precio << "," << l.disponibilidad_libros << "," << l.cantidad_libros << endl;
    bookfile.close();
}

void EliminarDatosLibros() {
    libros l;
    cout << "Ingrese el id para saber que libro desea eliminar: ";
    cin >> l.id;
    ofstream temp("temp.csv", ios::out);
    ifstream bookfile("Books.csv", ios::in);
    string line;

    while (getline(bookfile, line)) {
        int actual_id = atoi(line.substr(0, line.find(';')).c_str());
        if (actual_id != l.id) {
            temp << line << endl;
        }
    }
    bookfile.close();
    temp.close();

    remove("Books.csv");
    rename("temp.csv", "Books.csv");
    cout << "Los datos fueron borrados exitosamente" << endl;
}

void ModificarDatosLibros() {
    libros l;
    cout << "Ingrese el id del libro que desea modificar: ";
    cin >> l.id;
    ofstream temp("temp.csv", ios::out);
    ifstream bookfile("Books.csv", ios::in);
    string line;

    while (getline(bookfile, line)) {
        int actual_id = atoi(line.substr(0, line.find(',')).c_str());
        if (actual_id != l.id) {
            temp << line << endl;
        } else {
            cout << "Ingrese el titulo del libro: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, l.titulo);
            cout << "Ingrese el nombre del autor: ";
            getline(cin, l.autor);
            cout << "Ingrese el genero: ";
            getline(cin, l.genero);
            cout << "Ingrese la fecha de publicacion del libro: ";
            getline(cin, l.fecha_publicacion);
            cout << "Ingrese la editorial: ";
            getline(cin, l.editorial);
            cout << "Ingrese el precio del libro: ";
            cin >> l.precio;
            cout << "Ingrese la disponibilidad del libro: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, l.disponibilidad_libros);
            cout << "Ingrese la cantidad de libros disponibles: ";
            cin >> l.cantidad_libros;

            temp << l.id << ',' << l.titulo << ',' << l.autor << ',' << l.genero << ',' << l.fecha_publicacion << ',' << l.editorial << ',' << l.precio << ',' << l.disponibilidad_libros << "," << l.cantidad_libros << endl;
        }
    }
    bookfile.close();
    temp.close();

    remove("Books.csv");
    rename("temp.csv", "Books.csv");
    cout << "Los datos se modificaron correctamente" << endl;
}

void AgregarDatosPersonas() {
    ifstream people_file2("Clients.csv");
    string line;
    Persona p;
    int new_id = 0;

    while (getline(people_file2, line)) {
        new_id++;
    }
    people_file2.close();
    p.id = new_id;
    cout << "Ingrese el nombre de la persona: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p.Nombre);
    cout << "Ingrese el apellido de la persona: ";
    getline(cin, p.Apellido);
    cout << "Ingrese el correo de la persona: ";
    getline(cin, p.Email);
    cout << "Ingrese la clave de la persona: ";
    getline(cin, p.Clave);
    cout << "Ingrese ids de libros prestados: ";
    cin >> p.id_libros_prestados;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el status de la persona: ";
    getline(cin, p.status);
    cout << "Ingrese ids de libros comprados: ";
    cin >> p.id_libros_comprados;

    ofstream people_file("Clients.csv", ios::app);

    people_file << p.id << "," << p.Nombre << "," << p.Apellido << "," << p.Email << "," << p.Clave << "," << p.id_libros_prestados << "," << p.status << "," << p.id_libros_comprados << endl;
    people_file.close();
}

void EliminarDatosPersonas() {
    Persona p;
    cout << "Ingrese el id para saber que persona desea eliminar: ";
    cin >> p.id;
    ofstream temp("temp.csv", ios::out);
    ifstream peoplefile("Clients.csv", ios::in);
    string line;

    while (getline(peoplefile, line)) {
        int actual_id = atoi(line.substr(0, line.find(',')).c_str());
        if (actual_id != p.id) {
            temp << line << endl;
        }
    }
    peoplefile.close();
    temp.close();

    remove("Clients.csv");
    rename("temp.csv", "Clients.csv");
}

void ModificarDatosPersonas() {
    Persona p;
    cout << "Ingrese el id de la persona que desea modificar: ";
    cin >> p.id;

    ofstream temp("temp.csv", ios::out);
    ifstream people_file("Clients.csv", ios::in);
    string line;

    while (getline(people_file, line)) {
        int actual_id = atoi(line.substr(0, line.find(',')).c_str());
        if (actual_id != p.id) {
            temp << line << endl;
        } else {
            cout << "Ingrese el nombre de la persona: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, p.Nombre);
            cout << "Ingrese el apellido de la persona: ";
            getline(cin, p.Apellido);
            cout << "Ingrese el correo de la persona: ";
            getline(cin, p.Email);
            cout << "Ingrese la clave de la persona: ";
            getline(cin, p.Clave);
            cout << "Ingrese la cantidad de libros prestados de la persona: ";
            cin >> p.id_libros_prestados;
            cout << "Ingrese el status de la persona: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, p.status);
            cout << "Ingrese ids de libros comprados: ";
            cin >> p.id_libros_comprados;
            temp << p.id << ',' << p.Nombre << ',' << p.Apellido << ',' << p.Email << ',' << p.Clave << ',' << p.id_libros_prestados << ',' << p.status << "," << p.id_libros_comprados << endl;
        }
    }
    people_file.close();
    temp.close();

    remove("Clients.csv");
    rename("temp.csv", "Clients.csv");
    cout << "Los datos fueron modificados exitosamente" << endl;
}

void RegistroNuevoUsuario() {
    ifstream people_file2("Clients.csv");
    string line;
    Persona p;
    int new_id = 0;

    while (getline(people_file2, line)) {
        new_id++;
    }
    people_file2.close();
    p.id = new_id;
    cout << "Ingrese su nombre: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p.Nombre);
    cout << "Ingrese su apellido: ";
    getline(cin, p.Apellido);
    cout << "Ingrese su correo: ";
    getline(cin, p.Email);
    cout << "Ingrese su clave: ";
    getline(cin, p.Clave);

    ofstream people_file("Clients.csv", ios::app);

    people_file << p.id << "," << p.Nombre << "," << p.Apellido << "," << p.Email << "," << p.Clave << "," << "0" << "," << "cliente" << "," << "0" << endl;
    people_file.close();
    cout << "Usuario registrado, inicie sesion" << endl;
}

void SuspenderUsuario() {
    while (true) {
        Persona p;
        cout << "Ingrese el id de la persona que desea suspender: ";
        cin >> p.id;

        ofstream temp("temp.csv");
        ifstream archivo_clientes("Clients.csv");
        string line;

        bool encontrado = false;
        bool es_admin = false;

        while (getline(archivo_clientes, line)) {
            stringstream ss(line);
            string id, nombre, apellido, email, clave, borrowedBooks, purchasedBooks, status;

            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, email, ',');
            getline(ss, clave, ',');
            getline(ss, borrowedBooks, ',');
            getline(ss, purchasedBooks, ',');
            getline(ss, status, ',');

            if (id == to_string(p.id)) {
                encontrado = true;
                if (status == "admin") {
                    es_admin = true;
                    cout << "No se puede suspender a un administrador." << endl;
                    temp << line << endl;
                } else {
                    string updatedLine = id + "," + nombre + "," + apellido + "," + email + "," + clave + "," + borrowedBooks + "," + purchasedBooks + ",suspendido";
                    temp << updatedLine << endl;
                    cout << "Cliente suspendido" << endl;
                }
            } else {
                temp << line << endl;
            }
        }
        archivo_clientes.close();
        temp.close();

        if (encontrado && !es_admin) {
            remove("Clients.csv");
            rename("temp.csv", "Clients.csv");
            break;
        } else {
            remove("temp.csv");
            if (!encontrado) {
                cout << "Persona con ID " << p.id << " no encontrada." << endl;
            }
            cout << "Intente nuevamente." << endl;
        }
    }
}

void ComprarLibro(const string &authenticatedEmail) {
    string bookTitle;

    // Solicitar el nombre del libro al usuario
    cout << "Ingrese el nombre del libro que quiere comprar: ";
    cin.ignore();
    getline(cin, bookTitle);

    ifstream fileIn("Books.csv");
    ofstream fileOut("Books_temp.csv");
    string line;
    bool bookFound = false;
    int bookId;

    // Leer el archivo de libros y actualizar la cantidad
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

    // Reemplazar el archivo original con el archivo temporal
    remove("Books.csv");
    rename("Books_temp.csv", "Books.csv");

    // Si el libro fue encontrado y actualizado, registrar la compra
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

        // Reemplazar el archivo original con el archivo temporal
        remove("Clients.csv");
        rename("Clients_temp.csv", "Clients.csv");

        cout << "Compra realizada con éxito!\n";
    } else {
        cout << "El libro no se encontró en el inventario.\n";
    }
}

void PrestarLibro(const string &authenticatedEmail) {
    string bookTitle;

    // Solicitar el nombre del libro al usuario
    cout << "Ingrese el nombre del libro que quiere prestar: ";
    cin.ignore();
    getline(cin, bookTitle);

    ifstream fileIn("Books.csv");
    ofstream fileOut("Books_temp.csv");
    string line;
    bool bookFound = false;
    int bookId;

    // Leer el archivo de libros y actualizar la cantidad
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

    // Reemplazar el archivo original con el archivo temporal
    remove("Books.csv");
    rename("Books_temp.csv", "Books.csv");

    // Si el libro fue encontrado y actualizado, registrar el préstamo
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

        // Reemplazar el archivo original con el archivo temporal
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

    // Buscar los libros prestados del usuario autenticado
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

    // Mostrar los libros prestados
    cout << "Libros prestados:\n";
    stringstream ssBooks(borrowedBooks);
    string bookIdStr;
    while (getline(ssBooks, bookIdStr, ';')) {
        cout << "ID del libro: " << bookIdStr << endl;
    }

    // Pedir el ID del libro a devolver
    int returnBookId;
    cout << "Ingrese el ID del libro que desea devolver: ";
    cin >> returnBookId;

    // Verificar si el ID ingresado está en la lista de libros prestados
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

    // Leer y actualizar el archivo de clientes
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

    // Leer y actualizar el archivo de libros
    ifstream booksFileIn("Books.csv");
    ofstream booksFileOut("Books_temp.csv");
    string booksLine;

    // Copiar la línea del encabezado
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

