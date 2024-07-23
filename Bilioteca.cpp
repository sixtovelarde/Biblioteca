#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<limits>
#include<cstdio>

using namespace std;

struct Persona{
    int id;
    string Nombre;
    string Apellido;
    string Email;
    string Clave;
    int libros_prestados;
    string status;
};

struct libros{
    int id;
    string titulo;
    string autor;
    string genero;
    string fecha_publicacion;
    string editorial;
    float precio;
    string disponibilidad_libros;
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

int main(){
string line;
Persona p;
int opcion, opcion2, opcion3,opcion4,opcion5;
bool opcionvalida = false;
bool continuar = true;

cout<<"Ingrese su correo: ";
getline(cin,p.Email);
cout<<"Ingrese su clave: ";
getline(cin,p.Clave);
ifstream people_file("Clients.csv");

while(getline(people_file,line)){
stringstream ss(line);
string id, nombre, apellido, search_email, password, borrowed_books,status;

getline(ss, id, ',');
getline(ss,nombre, ',');
getline(ss,apellido, ',');
getline(ss,search_email, ',');
getline(ss,password, ',');
getline(ss,borrowed_books, ',');
getline(ss,status,',');

if(search_email == p.Email && password == p.Clave){
        if(status == "admin"){
        cout<<"Bienvenido a la app de la biblioteca, que desea hacer hoy?"<<endl
        <<"1.- Administrar datos de clientes"<<endl
        <<"2.- Administrar datos de libros"<<endl
        <<"3.- Comprar o retirar libros"<<endl
        <<"4.- Suspender un usuario"<<endl;
        cin>>opcion;

        if(opcion>=1 && opcion<=4){
            opcionvalida = true;
        }else{
            cout<<"Opcion invalida, por favor ingrese una dentro del rango"<<endl;
        }
        while(!opcionvalida);
        people_file.close();
        switch(opcion){

            case 1:{
            cout<<"Que desea?"<<endl
            <<"1.- Agregar Cliente"<<endl
            <<"2.- Modificar Cliente"<<endl
            <<"3.- Eliminar Cliente"<<endl;
            cin>>opcion2;
            if(opcion2 == 1){
                AgregarDatosPersonas();
            }else if(opcion2 == 2){
                ModificarDatosPersonas();
            
            }else if(opcion2 == 3){
                EliminarDatosPersonas();
            }
            }
            break;

            case 2: {
            cout<<"Que desea?"<<endl
            <<"1.- Agregar Libro"<<endl
            <<"2.- Modificar Libro"<<endl
            <<"3.- Eliminar Libro"<<endl;
            cin>>opcion3;
            if(opcion3 == 1){
                AgregarDatosLibros();
            }else if(opcion3 == 2){
                ModificarDatosLibros();
            }else if(opcion3 == 3){
                EliminarDatosLibros();
            }
            }
            break;

            case 3: {

            }break;
            case 4:{
            SuspenderUsuario();
            }
        }
        }else if(status == "cliente"){
        cout<<"Que desea hacer?"<<endl
        <<"1.- Comprar un libro "<<endl
        <<"2.- Prestar un libro "<<endl;
        cin>>opcion4;
        
        switch(opcion4){

            case 1: {
        cout<<"funcion no disponible"<<endl;
            }break;
        
            case 2: {
        cout<<"funcion no disponible"<<endl;
            }break;
        }
        }
    }else{
        while(continuar){
        cout<<"Usuario incorrecto, al parecer aun no tienes una cuenta :("<<endl
        <<"Deseas registrarte?"<<endl
        <<"1.- Si "<<endl
        <<"2.- No "<<endl;
        cin>>opcion5;
        switch(opcion5){
            case 1:{
                RegistroNuevoUsuario();
                continuar = false;
            }break;
            case 2:{
                continuar = false;
            }break;
        }
        }
    }
}
}
void LeerDatosLibros(const string &filename, libros catalog[], int &catalogsize){
    ifstream booksfile(filename);
    string line;
    catalogsize = 0;

    getline(booksfile,line);
    while(getline(booksfile,line)){
        stringstream ss(line);

        ss>> catalog[catalogsize].id;
        ss.ignore();
        getline(ss, catalog[catalogsize].titulo,',');
        getline(ss, catalog[catalogsize].autor,',');
        getline(ss, catalog[catalogsize].genero,',');
        getline(ss, catalog[catalogsize].fecha_publicacion,',');
        getline(ss, catalog[catalogsize].editorial,',');
        ss >> catalog[catalogsize].precio;
        ss.ignore();

        catalogsize++;
    }
}
void LeerDatosPersonas(const string &filename, Persona catalog[], int &catalogsize){
    ifstream peopleFile(filename);
    string line;
    catalogsize = 0;

    getline(peopleFile, line);

    while(getline(peopleFile,line)){
        stringstream ss(line);

        ss>> catalog[catalogsize].id;
        ss.ignore();
        getline(ss, catalog[catalogsize].Nombre,',');
        getline(ss, catalog[catalogsize].Apellido,',');
        getline(ss, catalog[catalogsize].Email,',');
        getline(ss, catalog[catalogsize].Clave,',');
        ss >> catalog[catalogsize].libros_prestados;
        ss.ignore();
        getline(ss, catalog[catalogsize].status,',');

        catalogsize++;
    }
}
void AgregarDatosLibros(){
    ifstream bookfile2("Books.csv");
    string line;
    libros l;
    int new_id = 0;

    while(getline(bookfile2,line)){
        new_id++;
    }
    bookfile2.close();
    l.id=new_id;

    cout<<"Ingrese el titulo: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,l.titulo);
    cout<<"Ingrese el nombre del autor: ";
    getline(cin,l.autor);
    cout<<"Ingrese el genero: ";
    getline(cin,l.genero);
    cout<<"Ingrese la fecha de publicacion: ";
    getline(cin,l.fecha_publicacion);
    cout<<"Ingrese la editorial: ";
    getline(cin,l.editorial);
    cout<<"Ingrese el precio del libro: ";
    cin>>l.precio;

    ofstream bookfile("Books.csv", ios::app);

    bookfile<<l.id<<","<<l.titulo<<","<<l.autor<<","<<l.genero<<","<<l.fecha_publicacion<<","<<l.editorial<<","<<l.precio<<endl;
    bookfile.close();
}
void EliminarDatosLibros(){
    libros l;
    cout<<"Ingrese el id para saber que libro desea eliminar: ";
    cin>>l.id;
    ofstream temp("temp.csv",ios::out);
    ifstream bookfile("Books.csv",ios::in);
    string line;

    while(getline(bookfile,line)){
        int actual_id = atoi(line.substr(0,line.find(';')).c_str());
        if(actual_id != l.id){
            temp<<line<<endl;
        }
    }
    bookfile.close();
    temp.close();

    remove("Books.csv");
    rename("temp.csv", "Books.csv");
    cout<<"los datos fueron borrados exitosamente"<<endl;
}
void ModificarDatosLibros(){
    libros l;
    cout<<"Ingrese el id del libro que desea modificar: ";
    cin>>l.id;
    ofstream temp("temp.csv",ios::out);
    ifstream bookfile("Books.csv",ios::in);
    string line;

    while(getline(bookfile,line)){
        int actual_id = atoi(line.substr(0,line.find(',')).c_str());
        if(actual_id != l.id){
            temp<<line<<endl;
        }
        else{
            cout<<"Ingrese el titulo del libro: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,l.titulo);
            cout<<"Ingrese el nombre del autor: ";
            getline(cin,l.autor);
            cout<<"Ingrese el genero: ";
            getline(cin,l.genero);
            cout<<"Ingrese la fecha de publicacion del libro: ";
            getline(cin,l.fecha_publicacion);
            cout<<"Ingrese la editorial: ";
            getline(cin,l.editorial);
            cout<<"Ingrese el precio del libro: ";
            cin>>l.precio;

            temp<<l.id<<','<<l.titulo<<','<<l.autor<<','<<l.genero<<','<<l.fecha_publicacion<<','<<l.editorial<<','<<l.precio<<endl;
        }
    }
    bookfile.close();
    temp.close();

    remove("Books.csv");
    rename("temp.csv","Books.csv");
    cout<<"Los datos se modificaron correctamente"<<endl;
}

void AgregarDatosPersonas(){
    ifstream people_file2("Clients.csv");
    string line;
    Persona p;
    int new_id = 0;

    while(getline(people_file2, line)) {
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
    cout << "Ingrese la cantidad de libros prestados: ";
    cin >> p.libros_prestados;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el status de la persona: ";
    getline(cin, p.status);

    ofstream people_file("Clients.csv", ios::app);


    people_file << p.id << "," << p.Nombre << "," << p.Apellido << "," << p.Email << "," << p.Clave << "," << p.libros_prestados << "," << p.status << endl;
    people_file.close();
}


void EliminarDatosPersonas(){
    Persona p;
    cout<<"Ingrese el id para saber que persona desea eliminar: ";
    cin>>p.id;
    ofstream temp("temp.csv",ios::out);
    ifstream peoplefile("Clients.csv",ios::in);
    string line;

    while(getline(peoplefile,line)){
        int actual_id = atoi(line.substr(0,line.find(';')).c_str());
        if(actual_id != p.id){
            temp<<line<<endl;
        }
    }
    peoplefile.close();
    temp.close();

    remove("Clients.csv");
    rename("temp.csv","Clients.csv");
}

void ModificarDatosPersonas(){
    Persona p;
    cout<<"Ingrese el id de la persona que desea modificar: ";
    cin>>p.id;

    ofstream temp("temp.csv",ios::out);
    ifstream people_file("Clients.csv",ios::in);
    string line;

    while(getline(people_file,line)){
        int actual_id = atoi(line.substr(0,line.find(',')).c_str());
        if(actual_id != p.id){
            temp<<line<<endl;
        }
        else{
            cout<<"Ingrese el nombre de la persona: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,p.Nombre);
            cout<<"Ingrese el apellido de la persona: ";
            getline(cin,p.Apellido);
            cout<<"Ingrese el correo de la persona: ";
            getline(cin,p.Email);
            cout<<"Ingrese la clave de la persona: ";
            getline(cin,p.Clave);
            cout<<"Ingrese la cantidad de libros prestados de la persona: ";
            cin>>p.libros_prestados;
            cout<<"Ingrese el status de la persona: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,p.status);

            temp<<p.id<<','<<p.Nombre<<','<<p.Apellido<<','<<p.Email<<','<<p.Clave<<','<<p.libros_prestados<<','<<p.status<<endl;
        }
    }
    people_file.close();
    temp.close();

    remove("Clients.csv");
    rename("temp.csv","Clients.csv");
    cout<<"Los datos fueron modificados exitosamente"<<endl;
}

void RegistroNuevoUsuario(){
    ifstream people_file2("Clients.csv");
    string line;
    Persona p;
    int new_id = 0;

    while(getline(people_file2, line)) {
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


    people_file << p.id << "," << p.Nombre << "," << p.Apellido << "," << p.Email << "," << p.Clave << "," << "0" << "," << "cliente" << endl;
    people_file.close();
    cout<<"Usuario registrado, inicie sesion"<<endl;
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
            int id_actual = atoi(line.substr(0, line.find(',')).c_str());
            size_t lastDelimiterPos = line.find_last_of(',');

            if (id_actual == p.id) {
                encontrado = true;
                string status = line.substr(lastDelimiterPos + 1);
                if (status == "admin") {
                    es_admin = true;
                    cout << "No se puede suspender a un administrador." << endl;
                    temp << line << endl; // Mantener la línea sin cambios
                } else {
                    string updatedLine = line.substr(0, lastDelimiterPos) + ",suspendido";
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
            break; // Salir del bucle si se suspendió correctamente
        } else {
            remove("temp.csv");
            if (!encontrado) {
                cout << "Persona con ID " << p.id << " no encontrada." << endl;
            }
            cout << "Intente nuevamente." << endl;
        }
    }
}