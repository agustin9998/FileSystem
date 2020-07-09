#include "Directorio.h"

#ifndef DIRECTORIO_CPP
#define DIRECTORIO_CPP

Directorio::Directorio()
{
	this->archivos = new ListaOrdImp<Archivo>();
	this->nombre = NULL;
}

Directorio::Directorio(Cadena nombreDirectorio)
{
	this->archivos = new ListaOrdImp<Archivo>();
	this->nombre = nombreDirectorio;
}

Directorio::~Directorio()
{
	delete archivos;
}

Directorio::Directorio(const Directorio &d)
{
	this->nombre = d.nombre;
	this->archivos = d.archivos->Clon();
}

bool Directorio::operator<(const Directorio &d) const
{
	return this->GetNombre() < d.GetNombre();
}

bool Directorio::operator==(const Directorio &d) const
{
	return (this->nombre == d.nombre) && (this->archivos == d.archivos);
}

Directorio &Directorio::operator=(const Directorio&d)
{
	if (this != &d)
	{
		this->nombre = d.nombre;
		this->archivos = d.archivos->Clon();
	}
	return *this;
}

void Directorio::AgregarArchivo(Cadena nombreArchivo)
{
	Archivo* aux = new Archivo(nombreArchivo);
	this->archivos->AgregarOrd(*aux);
}

void Directorio::AgregarArchivo(const Archivo &archivo)
{
	this->archivos->AgregarOrd(archivo);
}

void Directorio::EliminarArchivo(Cadena nombreArchivo)
{
	Archivo aux = Archivo(nombreArchivo);
	this->archivos->Borrar(aux);
}

void Directorio::EliminarArchivos()
{
	this->archivos->Vaciar();
}

bool Directorio::ExisteArchivo(Cadena nombreArchivo) const
{
	bool ret = false;
	Archivo archivo = Archivo(nombreArchivo);
	if (this->archivos->Existe(archivo))
		ret = true;
	return ret;
}

bool Directorio::ContieneArchivos() const
{
	return !(this->archivos->EsVacia());
}

Archivo &Directorio::BuscarArchivo(Cadena nombreArchivo) const
{
	Archivo aux = Archivo(nombreArchivo);
	Archivo* ret = &this->archivos->Recuperar(aux);
	return *ret;
}

Cadena Directorio::GetNombre() const
{
	return this->nombre;
}

void Directorio::SetNombre(Cadena nombre)
{
	this->nombre = nombre;
}

void Directorio::ListarArchivos(Cadena ruta, Cadena parametro) const
{
	ListaOrd<Archivo>* aux = this->archivos->Clon();
	if (parametro == "-H") {
		for (int i = 0; i < this->archivos->CantidadElementos(); i++) {
			if (aux->Minimo().EstaOculto())
				cout << ruta << aux->Minimo().GetNombre() << "(H)" << endl;
			else
				cout << ruta << aux->Minimo().GetNombre() << endl;
			aux->BorrarMinimo();
		}
	}
	else {
		for (int i = 0; i < this->archivos->CantidadElementos(); i++) {
			if (!(aux->Minimo().EstaOculto())) {
				cout << ruta << aux->Minimo().GetNombre() << endl;
			}
			aux->BorrarMinimo();
		}
	}
}

#endif