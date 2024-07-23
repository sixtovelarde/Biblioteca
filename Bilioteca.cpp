#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

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
};


void LeerDatosLibros(const string &filename, libros catalog[], int &catalogsize);
void LeerDatosPersonas(const string &filename, Persona catalog[], int &catalogsize);

void AgregarDatosLibros();
void EliminarDatosLibros();
void ModificarDatosLibros();

void AgregarDatosPersonas();
void EliminarDatosPersonas();
void ModificarDatosPersonas();

int main(){
int status = 0;
while(status!=1 and status!=2){
cout<<"Usted es un admin o un cliente?\n1.-Admin\n2.-Cliente"<<endl;
cin>>status;

if(status==1){
    cout<<"Usted es un admin"<<endl;
}
else if(status==2){
    cout<<"Usted es un cliente"<<endl;
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
    ofstream bookfile("Books.csv" , ios::app);
    ifstream bookfile2("Books.csv");
    string line;
    libros l;
    int new_id = 0;

    while(getline(bookfile2,line)){
        new_id++;
    }
    cout<<"Ingrese el titulo: ";
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

    bookfile<<l.id<<","<<l.titulo<<","<<l.autor<<","<<l.genero<<","<<l.fecha_publicacion<<","<<l.editorial<<","<<l.precio<<endl;
    bookfile.close();
    bookfile2.close();
}
void EliminarDatosLibros(){
    libros l;
    cout<<"Ingrese el id para saber que libro desea eliminar: ";
    cin>>l.id;
    ofstream temp("temp.csv");
    ifstream bookfile("Books.csv");
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

    ofstream temp("temp.csv");
    ifstream bookfile("Books.csv");
    string line;

    while(getline(bookfile,line)){
        int actual_id = atoi(line.substr(0,line.find(',')).c_str());
        if(actual_id == l.id){
            cout<<"Ingrese el titulo del libro: ";
            getline(cin,l.titulo);
            cout<<"Ingrese el nombre del autor: ";
            getline(cin,l.autor);
            cout<<"Ingrese el genero: ";
            getline(cin,l.genero);
            cout<<"Ingrese la fecha de publicacion del libro";
            getline(cin,l.fecha_publicacion);
            cout<<"Ingrese la editorial: ";
            getline(cin,l.editorial);
            cout<<"Ingrese el precio del libro: ";
            cin>>l.precio;
        }
        else{
            temp<<line<<endl;
        }
    }
    bookfile.close();
    temp.close();

    remove("Books.csv");
    rename("temp.csv","Books.csv");
    cout<<"Los datos se modificaron correctamente"<<endl;
}

void AgregarDatosPersonas(){
    ofstream people_file("People.csv", ios::app);
    ifstream people_file2("People.csv");
    string line;
    Persona p;
    int new_id = 0;

    while(getline(people_file2,line)){
        new_id++;
    }

    cout<<"Ingrese el nombre de la persona: ";
    getline(cin,p.Nombre);
    cout<<"Ingrese el apellido de la persona: ";
    getline(cin,p.Apellido);
    cout<<"Ingrese el correo de la persona: ";
    getline(cin,p.Email);
    cout<<"Ingrese la clave de la persona: ";
    getline(cin,p.Clave);
    cout<<"Ingrese la cantidad de libros prestados: ";
    cin>>p.libros_prestados;
    cout<<"Ingrese el status de la persona: ";
    getline(cin,p.status);

    people_file<<p.id<<","<<p.Nombre<<","<<p.Apellido<<","<<p.Email<<","<<p.Clave<<","<<p.libros_prestados<<","<<p.status<<endl;
    people_file.close();
    people_file2.close();
}

void EliminarDatosPersonas(){
    Persona p;

    cout<<"Ingrese el id de la persona que desea eliminar: ";
    cin>>p.id;
    ofstream temp("temp.csv");
    ifstream people_file("People.csv");
    string line;

    while(getline(people_file,line)){
        int actual_id = atoi(line.substr(0,line.find(',')).c_str());
        if(actual_id != p.id){
            temp<<line<<endl;
        }
    }
    people_file.close();
    temp.close();

    remove("People.csv");
    rename("temp.csv","People.csv");
    cout<<"Los datos fueron eliminados exitosamente"<<endl;
}

void ModificarDatosPersonas(){
    Persona p;
    cout<<"Ingrese el id de la persona que desea modificar: ";
    cin>>p.id;

    ofstream temp("temp.csv");
    ifstream people_file("People.csv");
    string line;

    while(getline(people_file,line)){
        int actual_id = atoi(line.substr(0,line.find(',')).c_str());
        if(actual_id == p.id){
            cout<<"Ingrese el nombre de la persona: ";
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
            getline(cin,p.status);
        }
        else{
            temp<<line<<endl;
        }
    }
    people_file.close();
    temp.close();

    remove("People.csv");
    rename("temp.csv","People.csv");
    cout<<"Los datos fueron modificados exitosamente"<<endl;
}