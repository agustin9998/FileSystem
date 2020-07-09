#include "PilaImp.h"
#include "ListaPosImp.h"
#include "Pila.h"

#ifndef PILAIMP_CPP
#define PILAIMP_CPP

template <class T>
inline ostream &operator<<(ostream& out, const PilaImp<T> &c) {
	c.Imprimir(out);
	return out;
}

template <class T>
PilaImp<T>::PilaImp() {
	this->lista = new ListaPosImp<T>();
}

template<class T>
PilaImp<T>::PilaImp(const Pila<T>& p) {
	*this = p;
}

template<class T>
PilaImp<T>::PilaImp(const PilaImp<T>& p) {
	*this = p;
}

template<class T>
Pila<T>& PilaImp<T>::operator=(const Pila<T>& p) {
	Pila<T>* aux = p.Clon();
	while (!(aux->EsVacia())) {
		this->Push(aux->Pop());
	}
	return *this;
}

template<class T>
Pila<T>& PilaImp<T>::operator=(const PilaImp<T>& p) {
	Pila<T>* aux = p.Clon();
	while (!(aux->EsVacia())) {
		this->push(aux->Pop());
	}
	return *this;
}

template<class T>
bool PilaImp<T>::operator==(const Pila<T> &p) const{
	Pila<T>* aux = p.Clon();
	if (this->CantidadElementos() != aux->CantidadElementos()) {
		return false;
	}
	else {
		for (int i = 0; i < this->CantidadElementos(); i++)
		{
			if (this->lista->ElementoPos(i) != aux->Pop()) {
				return false;
			}
		}
	}
	return true;
}

template<class T>
PilaImp<T>::~PilaImp() {
	delete lista;
}

template<class T>
Pila<T>* PilaImp<T>::CrearVacia() const {
	return new PilaImp<T>();
}

template<class T>
void PilaImp<T>::Push(const T& e) {
	lista->AgregarPpio(e);
}

template<class T>
T& PilaImp<T>::Top() const {
	return lista->ElementoPpio();
}

template<class T>
T PilaImp<T>::Pop() {
	T retorno = lista->ElementoPpio();
	lista->Borrar(retorno);
	return retorno;
}

template<class T>
void PilaImp<T>::Vaciar() {
	this->lista->Vaciar();
}

template<class T>
unsigned int PilaImp<T>::CantidadElementos() const {
	return this->lista->CantidadElementos();
}

template<class T>
bool PilaImp<T>::EsVacia() const {
	return this->lista->EsVacia();
}

template <class T>
bool PilaImp<T>::EsLlena() const{
	return false;
}

template<class T>
Pila<T>* PilaImp<T>::Clon() const {
	PilaImp<T>* ret = new PilaImp<T>();
	ret->lista = this->lista->Clon();
	return ret;
}

template<class T>
void PilaImp<T>::Imprimir(ostream & o) const
{
	this->lista->Imprimir(o);
}

#endif