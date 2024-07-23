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