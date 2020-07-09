#include "Archivo.h"


#ifndef ARCHIVO_CPP
#define ARCHIVO_CPP

Archivo::Archivo(Cadena nombre)
{
	this->nombre = nombre;
	this->text = new ListaPosImp<Cadena>();
	this->visibilidad = "";
}

Archivo::Archivo()
{
	this->nombre = Cadena();
	this->text = new ListaPosImp<Cadena>();
	this->visibilidad = "";
}

Archivo::~Archivo()
{
	delete text;
}

Archivo::Archivo(const Archivo &a)
{
	this->nombre = a.nombre;
	this->text = a.text->Clon();
}

Archivo &Archivo::operator=(const Archivo &a)
{
	if (this != &a)
	{
		this->nombre = a.nombre;
		this->text = a.text->Clon();
	}
	return *this;
}

bool Archivo::operator==(const Archivo &a) const
{
	bool ok = false;
	if (this->nombre == a.nombre) {
		ok = true;
	}
	return ok;
}

bool Archivo::operator<=(const Archivo &a) const {
	if (this->GetNombre() <= a.GetNombre())
		return true;
	else
		return false;
}

bool Archivo::operator<(const Archivo & a) const
{
	if (this->GetNombre() < a.GetNombre())
		return true;
	else
		return false;
}

void Archivo::ModificarVisibilidad(Cadena nuevaVisibilidad)
{
	this->visibilidad = nuevaVisibilidad;
}

void Archivo::InsertarTexto(unsigned int nroLinea, unsigned int posLinea, Cadena texto)
{
	while (nroLinea > this->text->CantidadElementos())
		this->text->AgregarFin("");
	this->text->ElementoPos(nroLinea).insertarTexto(posLinea, texto);
}

bool Archivo::TieneLineas() const
{
	return !(this->text->EsVacia());
}

bool Archivo::operator!=(const Archivo& a) const
{
	bool ok = false;
	if (this->nombre != a.nombre) {
		ok = true;
	}
	return ok;
}

void Archivo::EliminarTexto(unsigned int nroLinea, unsigned int posLinea, unsigned int k)
{
	if (this->text->ElementoPos(nroLinea).Length()< k+posLinea && this->text->ElementoPos(nroLinea).Length()>posLinea)
		this->text->ElementoPos(nroLinea).eliminarDesdeHasta(posLinea, (this->text->ElementoPos(nroLinea).Length()));
	else if (this->text->ElementoPos(nroLinea).Length() > posLinea)
		this->text->ElementoPos(nroLinea).eliminarDesdeHasta(posLinea, (k + posLinea));
}

void Archivo::MostrarContenido() const
{
	if (this->visibilidad == "-H")
		cout << "El archivo esta oculto" << endl;
	else if (this->text->CantidadElementos() == 0)
		cout << "El archivo no posee contenido" << endl;

	else{
		for (int i = 0; i <= this->text->CantidadElementos(); i++) {
			cout << i + 1 << ": " << text->ElementoPos(i) << endl;
		}
	}
}

bool Archivo::EstaOculto() const
{
	return this->visibilidad == "+H";
}

Cadena Archivo::GetNombre() const
{
	return this->nombre;
}

int Archivo::cantLineas() {
	return this->text->CantidadElementos();
}
#endif