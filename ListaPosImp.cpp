#include "ListaPosImp.h"

#ifndef LISTAPOSIMP_CPP
#define LISTAPOSIMP_CPP

template <class T>
inline ostream & operator<<(ostream &out, const ListaPosImp<T> &l)
{
	l.Imprimir(out);
	return out;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::CrearVacia() const
{
	return new ListaPosImp<T>();
}

template <class T>
ListaPosImp<T>::ListaPosImp()
{
	this->tamVec = 10;
	this->vec = new T[this->tamVec]();
	cantElem = 0;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPos<T> &l)
{
	this->tamVec = l->CantidadElementos;
	this->cantElem = 0;
	this->vec = new T[this->tamVec];
	*this = l;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPosImp<T> &l)
{
	this->tamVec = l.tamVec;
	this->cantElem = 0;
	this->vec = new T[this->tamVec];
	*this = l;
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPos<T> &l)
{
	if (this != &l) {
		this->Vaciar();
		for (int i = 0; i < l.CantidadElementos(); i++)
		{
			this->AgregarFin(l.ElementoPos(i));
		}
	}
	return *this;
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPosImp<T> &l)
{
	if (this != &l) {
		for (int i = 0; i < l.CantidadElementos(); i++)
		{
			this->AgregarFin(l.ElementoPos(i));
		}
	}
	return *this;
}

template <class T>
ListaPosImp<T>::~ListaPosImp()
{
	this->cantElem = 0;
	this->tamVec = 0;
}

template <class T>
void ListaPosImp<T>::AgregarPpio(const T &e) 
{
	if (this->cantElem == this->tamVec) {
		this->duplicarSize();
	}
	for (int i = cantElem; i > 0; i--) {
		this->vec[i] = this->vec[i-1];
	}
	this->vec[0] = e;
	this->cantElem++;
}

template <class T>
void ListaPosImp<T>::AgregarFin(const T &e) 
{
	if (this->cantElem >= this->tamVec-1) {
		this->duplicarSize();
	}
	this->vec[cantElem] = e;
	this->cantElem++;
}

template <class T>
void ListaPosImp<T>::AgregarPos(const T &e, unsigned int pos)
{
	if (this->cantElem == this->tamVec) {
		this->duplicarSize();
	}
	for (int i = cantElem; i > pos; i--) {
		this->vec[i] = this->vec[i - 1];
	}
	this->vec[pos] = e;
	this->cantElem++;
}

template<class T>
void ListaPosImp<T>::duplicarSize()
{
	T* aux = new T[this->cantElem * 2];
	for (int i = 0; i < this->cantElem; i++) {
		aux[i] = this->vec[i];
	}
	delete[] this->vec;
	this->vec = aux;
	this->tamVec = this->cantElem * 2;
}

template <class T>
void ListaPosImp<T>::BorrarPpio()
{
	BorrarPos(0);
}

template <class T>
void ListaPosImp<T>::BorrarFin()
{
	BorrarPos(cantElem - 1);
}

template <class T>
void ListaPosImp<T>::BorrarPos(unsigned int pos)
{
	for (int i = pos; i < this->cantElem - 1; i++) {
		this->vec[i] = this->vec[i + 1];
	}
	this->cantElem--;
}

template <class T>
void ListaPosImp<T>::Borrar(const T &e)
{
	int i = 0;
	while (e != this->vec[i])
		i++;
	this->BorrarPos(i);
}

template <class T>
T& ListaPosImp<T>::ElementoPpio() const
{
	
	return this->vec[0];
}

template <class T>
T& ListaPosImp<T>::ElementoFin() const
{
	return this->vec[this->cantElem -1];
}

template <class T>
T& ListaPosImp<T>::ElementoPos(unsigned int pos) const
{
	return this->vec[pos];
}

template <class T>
unsigned int ListaPosImp<T>::Posicion(const T &e) const
{
	int pos = 0;
	for (int i = 0; i < cantElem; i++) {
		if (this->vec[i] == e) {
			pos = i;
			break;
		}
	}
	return pos;
}

template <class T>
bool ListaPosImp<T>::Existe(const T &e) const
{
	bool retorno = false;
	for (int i = 0; i < cantElem; i++) {
		if (this->vec[i] == e) {
			retorno = true;
			break;
		}
	}
	return retorno;
}

template <class T>
void ListaPosImp<T>::Vaciar()
{
	while (!(this->EsVacia()))
		this->BorrarPpio();
}

template <class T>
unsigned int ListaPosImp<T>::CantidadElementos() const
{ 
	return cantElem; 
}

template <class T>
bool ListaPosImp<T>::EsVacia() const
{
	return (cantElem == 0);
}

template <class T>
bool ListaPosImp<T>::EsLlena() const
{
	return false;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::Clon() const
{

	return new ListaPosImp<T>(*this);
}

template <class T>
Iterador<T> ListaPosImp<T>::GetIterador() const
{
	return IteradorListaPosImp<T>(*this);
}

template <class T>
void ListaPosImp<T>::Imprimir(ostream& o) const
{
	for (int i = 0; i < this->cantElem; i++) {
		o << this->vec[i];
		if (i < this->cantElem-1)
			o << " ";
	}
}

#endif