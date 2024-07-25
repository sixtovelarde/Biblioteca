#include <iostream>
#include <fstream>
#include <sstream>
#include "../models/Libro.h"
#include "../models/Persona.h"

using namespace std;

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
